#include "SMSlib.h"
#include "inlib.h"

// Bits for port 3F.
#define PORTB_TH_HIGH	0x80
#define PORTB_TR_HIGH	0x40
#define PORTA_TH_HIGH	0x20
#define PORTA_TR_HIGH	0x10
#define PORTB_TH_INPUT	0x08
#define PORTB_TR_INPUT	0x04
#define PORTA_TH_INPUT	0x02
#define PORTA_TR_INPUT	0x01 // input when set

// https://www.smspower.org/Development/Paddle
// https://www.smspower.org/Development/PeripheralPorts
//
#define DETECT_MIN	0x60
#define DETECT_MAX	0xA0
#define READ_TIMEOUT	32

__sfr __at 0x3F port3F;
__sfr __at 0xDC portDC;
__sfr __at 0xDD portDD;


inlib_data inlib_port1, inlib_port2;

char SMS_detectPaddleA(void)
{
	unsigned char i,c;

	for (i=1, c=0; i; i++) {
		if (portDC & 0x20) {
			c++;
		}
	}
	if (c < DETECT_MIN) {
		return 0;
	}
	if (c > DETECT_MAX) {
		return 0;
	}

	return 1;
}

char SMS_detectPaddleB(void)
{
	unsigned char i,c;

	for (i=1, c=0; i; i++) {
		if (portDD & 0x08) {
			c++;
		}
	}
	if (c < DETECT_MIN) {
		return 0;
	}
	if (c > DETECT_MAX) {
		return 0;
	}

	return 1;

}

int SMS_paddleReadA(void)
{
	unsigned char val, tmp;
	unsigned int t = READ_TIMEOUT;

	/* First, synchronize by waiting until port A key 2 is high.
	 * Without this, the values occasionally glitches on real hardware.
	 *
	 * I think this happens when the low nibble gets read just
	 * when key 2 is just about to become high (or already rising).
	 *
	 * Since this solution works, I assume that the paddle updates
	 * the nibble first, and then sets key 2 to high. Or does
	 * both simultaneously.
	 */
	do {
		tmp = portDC;
		t--;
		if (!t) {
			return -1;
		}
	} while (!(tmp & 0x20));

	/* Now wait until key 2 is low, receive the low nibble. */
	do {
		tmp = portDC;
		t--;
		if (!t) {
			return -1;
		}
	} while (tmp & 0x20);

	val = tmp & 0xf;

	/* Now wait until key 2 is high to receive the high nibble. */
	do {
		tmp = portDC;
		t--;
		if (!t) {
			return -1;
		}
	} while (!(tmp & 0x20));

	val |= tmp << 4;

	return val;
}

int SMS_paddleReadB(void)
{
	unsigned char val, tmp;
	unsigned int t = READ_TIMEOUT;

	/* Sync */
	while (!(portDD & 0x08)) {
		t--;
		if (!t) {
			return -1;
		}
	}

	/* Wait for low nibble */
	while ((portDD & 0x08)) {
		t--;
		if (!t) {
			return -1;
		}
	}
	tmp = (portDC >> 6) | ((portDD & 3) << 2);
	val = tmp;

	/* Wait for high nibble */
	while (!(portDD & 0x08)) {
		t--;
		if (!t) {
			return -1;
		}
	}

	tmp = (portDC >> 6) | ((portDD & 3) << 2);
	val |= tmp << 4;

	return val;
}


static void SMS_paddle_meka_workaround(void)
{
	port3F = 0x55;
}

static void SMS_paddle_undo_meka_workaround(void)
{
	port3F = 0xFF;
}


static void TH_TR_outputmode()
{
	// Port A TH and TR pins output
	port3F = 0xFC;
}

#define GET_TL()	((portDC) & 0x10)

#define TH_LOW_TR_HIGH()	port3F = 0x1C
#define TH_LOW_TR_LOW()		port3F = 0x0C
#define TH_HIGH_TR_HIGH()	port3F = 0x3C

#define TH_HIGH_TR_LOW()	port3F = 0x20

static void _delayN(uint16_t c)
{
	volatile uint16_t r = c;

	while (r--) {
		__asm
		nop
		__endasm;
	}
}



static void sportsPad_read(uint8_t *dst)
{
	uint8_t tmp;
	const uint8_t TH_HIGH = 0x0D; // PORTA_TH_HIGH | PORTB_TR_INPUT | PORTB_TH_INPUT;
	const uint8_t TH_LOW = 0x2D; // PORTB_TR_INPUT | PORTB_TH_INPUT;

	port3F = TH_HIGH;
	_delayN(8);
	tmp = (portDC & 0xf) << 4;

	port3F = TH_LOW;
	_delayN(8);
	tmp |= (portDC & 0xf);

	dst[0] = tmp;

	port3F = TH_HIGH;
	_delayN(8);
	tmp = (portDC & 0xf) << 4;

	port3F = TH_LOW;
	_delayN(8);
	tmp |= (portDC & 0xf);

	dst[1] = tmp;

}

static char detectSportsPad()
{
	uint8_t data[2];
	uint8_t i, j;

	// TH as output on both ports
	port3F = PORTB_TH_HIGH | PORTA_TH_HIGH | PORTB_TR_INPUT | PORTB_TH_INPUT;

	for (j=0; j<10; j++) {

		SMS_waitForVBlank();
		SMS_waitForVBlank();

		sportsPad_read(data);

		// Not sure how to detect this... If the data appears to change between nibbles, assume it's a sports pad?
		// No, does not work. The sports pad returns zeros when there is no movement.
		for (i=1; i<2; i++) {
			if ((data[i] & 0xf) == (data[i] >> 4)) {
				return 0;
			}
		}

	}

	return 1;
}


static char detectMouse()
{
	uint16_t t;

	TH_LOW_TR_HIGH();

	// Handshake

	TH_LOW_TR_LOW();
	t = 1024;
	while (GET_TL()) {
		t--;
		if (!t) {
			port3F = 0xff;
			return 0;
		}
	}

	TH_LOW_TR_HIGH();
	t = 1024;
	while (!GET_TL()) {
		t--;
		if (!t) {
			port3F = 0xff;
			return 0;
		}
	}


	TH_HIGH_TR_HIGH();

	return 1;
}

static uint8_t detectGraphics2()
{
	uint8_t btns;

	SMS_waitForVBlank();

	btns = portDC & 0xf;

	TH_HIGH_TR_HIGH();

	return btns == 0x0;
}

static void readGraphics2(gfxv2_data *dst)
{
	unsigned char i;
	unsigned char tmp;
	uint8_t buf[3] = { 0, 0, 0 };
	uint8_t btn;
	uint8_t has_data;

	has_data = !GET_TL();

	// Read buttons
	TH_HIGH_TR_LOW();
	_delayN(8);
	btn = portDC & 0xf;

	if (has_data) {

		for (i=0; i<3; i++) {

			TH_LOW_TR_LOW();
			_delayN(8);
			tmp = portDC & 0xf;
			tmp <<= 4;

			// Receive lower nibble
			TH_HIGH_TR_LOW();
			_delayN(8);
			tmp |= portDC & 0xf;

			// Store
			buf[i] = tmp;
		}
	}

	dst->type = INLIB_TYPE_GFX_V2;
	dst->buttons = btn ^= 0xf;
	dst->pressure = buf[0];
	dst->x = buf[1];
	dst->y = buf[2];

	TH_HIGH_TR_HIGH();
}


static void readMouse(uint8_t *dst)
{
	unsigned char i;
	unsigned char tmp;

	TH_LOW_TR_HIGH();

	for (i=0; i<4; i++) {

		// Receive upper nibble
		TH_LOW_TR_LOW();
		while (GET_TL()) { }
		tmp = portDC & 0xf;
		tmp <<= 4;

		// Receive lower nibble
		TH_LOW_TR_HIGH();
		while (!GET_TL()) { }
		tmp |= portDC & 0xf;

		// Store
		dst[i] = tmp;
	}

	TH_HIGH_TR_HIGH();
}



void inlib_init()
{

	inlib_port1.type = INLIB_TYPE_SMS;
	inlib_port2.type = INLIB_TYPE_SMS;

	SMS_paddle_meka_workaround();

	// Step 1 : Japanese paddle detection (passive test)
	SMS_waitForVBlank();
	if (SMS_detectPaddleA()) {
		inlib_port1.type = INLIB_TYPE_PADDLE;
	}
	if (SMS_detectPaddleB()) {
		inlib_port2.type = INLIB_TYPE_PADDLE;
	}
	if (	(inlib_port1.type != INLIB_TYPE_PADDLE) &&
			(inlib_port2.type != INLIB_TYPE_PADDLE) ) {
		SMS_paddle_undo_meka_workaround();
	}
	SMS_waitForVBlank();

	if (detectMouse()) {
		inlib_port1.type = INLIB_TYPE_MD_MOUSE;
	}
}

void readLightPhaser1()
{
	uint8_t vc;
	uint8_t x = 0, y = 0;
	uint8_t trig = 0;
	uint8_t count = 0;
	uint8_t first = 1;

	SMS_paddle_undo_meka_workaround();
	trig = (portDC & 0x10) ? 0 : LIGHTPHASER_TRIG; // Port A TL

	if (trig) {

		// Normally called during vblank. Wait until vblank ends...
		do {
			vc = SMS_getVCount();
		} while ((vc > 192));

		// Monitor TH during the active display area
		do {
			vc = SMS_getVCount();

			if (!(portDD & 0x40)) { // Port A TH
				// Light detected!

				// Record the minimum x and y seen.
				if (first) {
					x = SMS_getHCount();
					y = vc;
					first = 0;
				} else {
					if (SMS_getHCount() < x) {
						x = SMS_getHCount();
					}
					if (vc < y) {
						y = vc;
					}
				}
			}

		} while (vc < 192);

	}

	// The H counter is 9 bits, and reading it returns the upper 8 bits. 
	if (x > 0x7f) {
		inlib_port1.phaser.x = 0xff;
	} else {
		inlib_port1.phaser.x = x << 1;
	}
	inlib_port1.phaser.y = y;
	inlib_port1.phaser.buttons = trig;
}

void inlib_poll()
{
	uint8_t tmpdata[4];
	uint8_t now;

	if (inlib_port1.type == INLIB_TYPE_LIGHT_PHASER) {
		readLightPhaser1();
		return;
	}

	if (inlib_port1.type == INLIB_TYPE_GFX_V2) {
		readGraphics2(&inlib_port1.gfx2);
		return;
	}

	if (inlib_port1.type == INLIB_TYPE_MD_MOUSE) {
		readMouse(tmpdata);
		inlib_port1.mdmouse.buttons = tmpdata[1] & 0xf;
		// TODO : In fact, tmpdata[1] & 1 is a 9th bit for X,
		// and tmpdata[1] & 2 is a 9th bit for Y!
		inlib_port1.mdmouse.x = tmpdata[2];
		inlib_port1.mdmouse.y = tmpdata[3];
		return;
	}

	if (inlib_port1.type == INLIB_TYPE_PADDLE) {
		now = (SMS_getKeysStatus() & PORT_A_KEY_1) ? PADDLE_BUTTON : 0;
		inlib_port1.paddle.pressed = now & ~inlib_port1.paddle.buttons;
		inlib_port1.paddle.buttons = now;
		inlib_port1.paddle.value = SMS_paddleReadA();
	} else if (inlib_port1.type == INLIB_TYPE_SPORTSPAD) {
		now = (SMS_getKeysStatus() >> 4) & 3;
		sportsPad_read(tmpdata);
		inlib_port1.spad.pressed = now & ~inlib_port1.spad.buttons;
		inlib_port1.spad.buttons = now;
		inlib_port1.spad.x = tmpdata[0];
		inlib_port1.spad.y = tmpdata[1];
	} else {
		now =  SMS_getKeysStatus();
		inlib_port1.sms.pressed = now & ~inlib_port1.sms.buttons;
		inlib_port1.sms.buttons = now;
	}

	if (inlib_port2.type == INLIB_TYPE_PADDLE) {
		now = (SMS_getKeysStatus() & PORT_B_KEY_1) ? PADDLE_BUTTON : 0;
		inlib_port2.paddle.pressed = now & ~inlib_port2.paddle.buttons;
		inlib_port2.paddle.buttons = now;
		inlib_port2.paddle.value = SMS_paddleReadB();
	} else {
		now =  SMS_getKeysStatus() >> 6;
		inlib_port2.sms.pressed = now & ~inlib_port2.sms.buttons;
		inlib_port2.sms.buttons = now;
	}

	return;
}

#ifndef _inlib_h__
#define _inlib_h__

#include <stdint.h>

#define INLIB_TYPE_SMS			0
#define INLIB_TYPE_PADDLE		1
#define INLIB_TYPE_MD_MOUSE		2
#define INLIB_TYPE_GFX_V2		3
#define INLIB_TYPE_SPORTSPAD	4
#define INLIB_TYPE_LIGHT_PHASER	5

typedef struct _sms_paddle_data {
	uint8_t type;
	uint8_t buttons;
	uint8_t pressed;
	uint8_t value;
} sms_paddle_data;

#define PADDLE_BUTTON	1

typedef struct _mdmouse_data {
	uint8_t type;
	uint8_t buttons;
	uint8_t pressed;
	int8_t x, y;
} mdmouse_data;

#define MDMOUSE_BTN_LEFT	0x01
#define MDMOUSE_BTN_RIGHT	0x02
#define MDMOUSE_BTN_MID		0x04
#define MDMOUSE_BTN_START	0x08

typedef struct _sms_pad_data {
	uint8_t type;
	uint8_t buttons;
	uint8_t pressed;
} sms_pad_data;

#define SMS_BTN_1	0x10
#define SMS_BTN_2	0x20
#define SMS_BTN_UP	0x01
#define SMS_BTN_DN	0x02
#define SMS_BTN_LF	0x04
#define SMS_BNT_RT	0x08

typedef struct _inlib_gfxv2 {
	uint8_t type;
	uint8_t buttons;
	uint8_t pressure;
	uint8_t x, y;
} gfxv2_data;

// Correct ? ? ?
#define GFX2_BTN1	0x01
#define GFX2_BTN2	0x02
#define GFX2_BTN3	0x04

typedef struct _inlib_sportspad {
	uint8_t type;
	uint8_t buttons;
	uint8_t pressed;
	int8_t x, y;
} sportspad_data;

typedef struct _inlib_lightphaser {
	uint8_t type;
	uint8_t buttons;
	uint8_t x, y;
} lightphaser_data;

#define LIGHTPHASER_TRIG	1

typedef struct _inlib_data {
	union {
		uint8_t type;
		sms_pad_data sms;
		sms_paddle_data paddle;
		mdmouse_data mdmouse;
		gfxv2_data gfx2;
		sportspad_data spad;
		lightphaser_data phaser;
	};
} inlib_data;

// Is this the correct order?
#define SPORTSPAD_BTN_1	0x01
#define SPORTSPAD_BTN_2	0x02


void inlib_init();
void inlib_poll();

extern inlib_data inlib_port1, inlib_port2;

#endif // _inlib_h__

#include <stdio.h>
#include "util.h"
#include "SMSlib.h"
#include "PSGlib.h"

#ifdef TARGET_GG
#define SMS_loadBGPalette	GG_loadBGPalette
#define SMS_loadSpritePalette	GG_loadSpritePalette

#define SMS_loadBGPaletteHalfBrightness	GG_loadBGPalette
#define SMS_loadSpritePaletteHalfBrightness	GG_loadSpritePalette
#define SMS_resetPauseRequest()	do { } while(0)
#endif

// Keeps a copy of last set palettes.
static void *s_bgpal = NULL, *s_sprpal = NULL;

static void util_fadeDelay(void)
{
	uint8_t i;
	for (i=0; i<10; i++) {
		SMS_waitForVBlank();
	}
}

void util_fadeOut(void)
{
	if (s_bgpal) {
		SMS_loadBGPaletteHalfBrightness(s_bgpal);
	}
	if (s_sprpal) {
		SMS_loadSpritePaletteHalfBrightness(s_sprpal);
	}
	util_fadeDelay();
	util_paletteZero();
}

void util_fadeIn(void)
{
	util_paletteHalfBrightness();
	util_fadeDelay();
	util_paletteFullBrightness();
}

void util_paletteZero(void)
{
	SMS_zeroBGPalette();
	SMS_zeroSpritePalette();
}

void util_paletteFullBrightness(void)
{
	if (s_bgpal) {
		SMS_loadBGPalette(s_bgpal);
	}
	if (s_sprpal) {
		SMS_loadSpritePalette(s_sprpal);
	}
}

void util_paletteHalfBrightness(void)
{
	if (s_bgpal) {
		SMS_loadBGPaletteHalfBrightness(s_bgpal);
	}
	if (s_sprpal) {
		SMS_loadSpritePaletteHalfBrightness(s_sprpal);
	}
}

void util_preparePalettes(const void *bgpal, const void *sprpal)
{
	s_bgpal = bgpal;
	s_sprpal = sprpal;
}

void util_smsClear(void)
{
	SMS_displayOff();
	SMS_waitForVBlank();
	SMS_mapROMBank(2);
	SMS_zeroBGPalette();
	SMS_zeroSpritePalette();
	SMS_VRAMmemset(0, 0, 16*1024);	// Clear VRAM
	SMS_setBGScrollX(0);
	SMS_setBGScrollY(0);
	SMS_initSprites();
	SMS_finalizeSprites();
	SMS_resetPauseRequest();
	SMS_waitForVBlank();
	SMS_copySpritestoSAT();
	SMS_waitForVBlank();
}

void util_fillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, int tile_id)
{
	uint16_t linebuf[32];
	int Y;

	for (Y=0; Y<w; Y++) {
		linebuf[Y] = tile_id;
	}

	for (Y=y; Y<y+h; Y++) {
		SMS_loadTileMapArea(x, Y, linebuf, w, 1);
	}
}

void util_fillScreen(int tile_id)
{
	util_fillRect(0,0,32,24,tile_id);
}

void util_drawBoxFilled(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t fill_tid)
{
	util_fillRect(x,y,w,h,fill_tid);
	drawBox(x,y,w,h);
}

void drawBox(uint8_t x, uint8_t y, uint8_t w, uint8_t h)
{
	uint8_t X, Y;

	if (!w || !h)
		return;

	w -= 1;
	h -= 1;

	// upper left
	SMS_setNextTileatXY(x,y);
	SMS_setTile(122);

	// upper right
	SMS_setNextTileatXY(x+w,y);
	SMS_setTile(124);

	// lower left
	SMS_setNextTileatXY(x,y+h);
	SMS_setTile(109);

	// lower right
	SMS_setNextTileatXY(x+w,y+h);
	SMS_setTile(111);

	// Vertical sides
	for (Y=y+1; Y<y+h; Y++) {
		SMS_setNextTileatXY(x,Y);
		SMS_setTile(106);
		SMS_setNextTileatXY(x+w,Y);
		SMS_setTile(107);
	}

	// Horizontal sides
	for (X=x+1; X<x+w; X++) {
		SMS_setNextTileatXY(X,y);
		SMS_setTile(123);
		SMS_setNextTileatXY(X,y+h);
		SMS_setTile(110);
	}
}

void blitTiles(uint8_t dst_x, uint8_t dst_y, uint8_t w, uint8_t h, int tile_id)
{
	uint8_t y, x;

	for (y=0; y<h; y++)
	{
		SMS_setNextTileatXY(dst_x, dst_y + y);
		for (x=0; x<w; x++) {
			SMS_setTile(tile_id++);
		}
	}

}
/*
uint8_t palTransition(const uint8_t *initial, const uint8_t *final, uint8_t *dst)
{
	uint8_t i;
	uint8_t tmp_i, tmp_f;
	uint8_t a, b;
	uint8_t tmp;
	uint8_t mc = 0;

	for (i=0; i<16; i++) {
		tmp_i = initial[i] & 0x3F;
		tmp_f = final[i] & 0x3F;
		tmp = 0;

		if (tmp_i == tmp_f) {
			mc++;
			continue;
		}

		// Red
		a = tmp_i & 0x03;
		b = tmp_f & 0x03;
		if (a > b) {
			tmp |= a-0x01;
		} else if (a < b) {
			tmp |= a+0x01;
		} else {
			tmp |= a;
		}

		// Green
		a = tmp_i & 0x0C;
		b = tmp_f & 0x0C;
		if (a > b) {
			tmp |= a-0x04;
		} else if (a < b) {
			tmp |= a+0x04;
		} else {
			tmp |= a;
		}

		// Blue
		a = tmp_i & 0x30;
		b = tmp_f & 0x30;
		if (a > b) {
			tmp |= a-0x10;
		} else if (a < b) {
			tmp |= a+0x10;
		} else {
			tmp |= a;
		}

		dst[i] = tmp;
	}

	// If all colors matches, return true
	return (mc == 16);
}
*/
void util_reserveSprites(uint8_t count)
{
	uint8_t i;

	for (i=0; i<count; i++)
		SMS_reserveSprite();
}

uint8_t util_converge(uint8_t target, uint8_t cur)
{
	if (cur < target) {
		cur += ((target - cur) >> 1) | 1;
	} else if (cur > target) {
		cur -= ((cur - target) >> 1) | 1;
	}

	return cur;
}

uint8_t util_converge_linear(uint8_t target, uint8_t cur)
{
	if (cur < target) {
		cur++;
	} else if (cur > target) {
		cur--;
	}

	return cur;
}

uint8_t util_converge_linear2(uint8_t target, uint8_t cur)
{
	cur = util_converge_linear(target, cur);
	return util_converge_linear(target, cur);
}

uint8_t util_absdiff(uint8_t a, uint8_t b)
{
	if (a > b)
		return a-b;
	return b-a;
}

void util_waitVBlankSatPSG()
{
	SMS_waitForVBlank();
	SMS_copySpritestoSAT();
	PSGFrame();
	PSGSFXFrame();
}


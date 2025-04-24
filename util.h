#include <stdint.h>

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(arr)	(sizeof(arr) / sizeof(arr[0]))
#endif


void util_smsClear(void);

void drawBox(uint8_t x1, uint8_t y1, uint8_t w, uint8_t h);
void util_drawBoxFilled(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t fill_tid);
void blitTiles(uint8_t dst_x, uint8_t dst_y, uint8_t w, uint8_t h, int tile_id);
uint8_t palTransition(const uint8_t *initial, const uint8_t *final, uint8_t *dst);

void util_fillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, int tile_id);
void util_fillScreen(int tile_id);

void util_fadeOut(void);
void util_fadeIn(void);
void util_preparePalettes(const void *bgpal, const void *sprpal);
void util_paletteZero(void);
void util_paletteFullBrightness(void);
void util_paletteHalfBrightness(void);

void util_reserveSprites(uint8_t count);

uint8_t util_converge(uint8_t target, uint8_t cur);
uint8_t util_converge_linear(uint8_t target, uint8_t cur);
uint8_t util_converge_linear2(uint8_t target, uint8_t cur);
uint8_t util_absdiff(uint8_t a, uint8_t b);

void util_waitVBlankSatPSG(void);

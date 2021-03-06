#include <stdint.h>
#include <stdio.h>
#include <png.h>

#define NUM_SPRITES	20
#define SPRITE_HEIGHT	26

#define USHORT	uint16_t
#define chip

USHORT chip AVSpriteData[20][56] = {
 /* lmanOneLeft */
 {0x0000,0x0000,
  0x001A,0x000F,
  0x00D1,0x002F,
  0x0103,0x02FF,
  0x04C7,0x033F,
  0x0906,0x06FE,
  0x1A86,0x057E,
  0x1E52,0x01AE,
  0x3FF3,0x000C,
  0x3F4D,0x00B2,
  0x37FB,0x0804,
  0x3D41,0x02BE,
  0x3A71,0x058E,
  0x0FB8,0x1047,
  0x1FC8,0x0037,
  0x0C88,0x0377,
  0x039B,0x0464,
  0x02DD,0x0122,
  0x0034,0x01CB,
  0x0034,0x000B,
  0x0000,0x0003,
  0x0000,0x0001,
  0x0000,0x0001,
  0x0000,0x0003,
  0x0003,0x0000,
  0x0003,0x0003,
  0x0007,0x0007,
  0x0000,0x0000},
 /* lmanOneRight */
 {0x0000,0x0000,
  0xC000,0xC000,
  0xC800,0xF800,
  0xF400,0xEC00,
  0x30F8,0x3EF8,
  0x1986,0x167E,
  0x1901,0x56FF,
  0x1FA1,0x005F,
  0x2A08,0xD5F7,
  0x3240,0xCDBE,
  0xF000,0x0FF8,
  0x3800,0x07C0,
  0x0E00,0x01C0,
  0x8380,0x0000,
  0xE000,0x0000,
  0x3800,0xC000,
  0xB600,0x4800,
  0x6000,0x9C00,
  0x0000,0xF800,
  0x0000,0xE000,
  0x0000,0x0000,
  0x0000,0x8000,
  0x0000,0x8000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x8000,0x8000,
  0xF800,0xF800,
  0x0000,0x0000},
 /* lmanTwoLeft */
 {0x0000,0x0000,
  0x001A,0x000F,
  0x00D1,0x002F,
  0x0103,0x02FF,
  0x04C7,0x033F,
  0x0906,0x06FE,
  0x1A86,0x057E,
  0x1E52,0x01AE,
  0x3FF3,0x000C,
  0x3F4D,0x00B2,
  0x37FB,0x0804,
  0x3D41,0x02BE,
  0x3A71,0x058E,
  0x0FB8,0x1047,
  0x1FC8,0x0037,
  0x0C88,0x0377,
  0x039B,0x0464,
  0x02DD,0x0122,
  0x0034,0x01CB,
  0x0034,0x000B,
  0x0000,0x0007,
  0x0000,0x000C,
  0x0010,0x0008,
  0x0030,0x0020,
  0x0070,0x0070,
  0x0018,0x0018,
  0x000C,0x000C,
  0x0000,0x0000},
 /* lmanTwoRight */
 {0x0000,0x0000,
  0xC000,0xC000,
  0xC800,0xF800,
  0xF400,0xEC00,
  0x30F8,0x3EF8,
  0x1986,0x167E,
  0x1901,0x56FF,
  0x1FA1,0x005F,
  0x2A08,0xD5F7,
  0x3240,0xCDBE,
  0xF000,0x0FF8,
  0x3800,0x07C0,
  0x0E00,0x01C0,
  0x8380,0x0000,
  0xE000,0x0000,
  0x3800,0xC000,
  0xB600,0x4800,
  0x6000,0x9C00,
  0x0000,0xF800,
  0x0000,0xE000,
  0x0000,0x8000,
  0x0000,0xC000,
  0x0000,0x6000,
  0x0000,0x6000,
  0x6000,0x0000,
  0x7000,0x7000,
  0xFF00,0xFF00,
  0x0000,0x0000},
 /* lmanThreeLeft */
 {0x0000,0x0000,
  0x001A,0x000F,
  0x00D1,0x002F,
  0x0103,0x02FF,
  0x04C7,0x033F,
  0x0906,0x06FE,
  0x1A86,0x057E,
  0x1E52,0x01AE,
  0x3FF3,0x000C,
  0x3F4D,0x00B2,
  0x37FB,0x0804,
  0x3D41,0x02BE,
  0x3A71,0x058E,
  0x0FB8,0x1047,
  0x1FC8,0x0037,
  0x0C88,0x0377,
  0x039B,0x0464,
  0x02DD,0x0122,
  0x0034,0x01CB,
  0x0034,0x000B,
  0x0000,0x0003,
  0x0000,0x0001,
  0x0000,0x0007,
  0x0018,0x0016,
  0x0038,0x0030,
  0x001C,0x001C,
  0x0007,0x0007,
  0x0000,0x0000},
 /* lmanThreeRight */
 {0x0000,0x0000,
  0xC000,0xC000,
  0xC800,0xF800,
  0xF400,0xEC00,
  0x30F8,0x3EF8,
  0x1986,0x167E,
  0x1901,0x56FF,
  0x1FA1,0x005F,
  0x2A08,0xD5F7,
  0x3240,0xCDBE,
  0xF000,0x0FF8,
  0x3800,0x07C0,
  0x0E00,0x01C0,
  0x8380,0x0000,
  0xE000,0x0000,
  0x3800,0xC000,
  0xB600,0x4800,
  0x6000,0x9C00,
  0x0000,0xF800,
  0x0000,0xE000,
  0x0000,0x0000,
  0x0000,0x8000,
  0x0000,0x8000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000},
 /* rmanOneLeft */
 {0x0000,0x0000,
  0x0000,0x0000,
  0x0003,0x0002,
  0x0007,0x0005,
  0x07CB,0x07C7,
  0x1FC2,0x183E,
  0x3F12,0x20EE,
  0x3628,0x29D6,
  0x3EFF,0x0100,
  0x1F7F,0x0080,
  0x07EE,0x0011,
  0x0070,0x000F,
  0x0070,0x000C,
  0x0000,0x0030,
  0x0000,0x0000,
  0x0000,0x0003,
  0x0001,0x000E,
  0x0007,0x0000,
  0x0003,0x0000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0003,0x0003,
  0x0000,0x0000},
 /* rmanOneRight */
 {0x0000,0x0000,
  0x7E00,0x6B00,
  0xF300,0xECE0,
  0xFF20,0xF0D0,
  0x3FD0,0x3828,
  0x1FE0,0x181C,
  0x9EC0,0x193E,
  0x1F60,0x109E,
  0x6010,0x9FEF,
  0xC0C8,0x3F37,
  0x0840,0xF7BF,
  0x0FD0,0x102F,
  0x0F82,0x107D,
  0x0DC0,0x323E,
  0x1E80,0xE17E,
  0x7820,0x87DC,
  0xA400,0x5BF8,
  0xF820,0x07D0,
  0xFA00,0x05E0,
  0xC800,0x3700,
  0x1800,0x0000,
  0x3000,0x0000,
  0x3000,0x0000,
  0x1800,0x0000,
  0x0000,0x1800,
  0x3800,0x3800,
  0xFC00,0xFC00,
  0x0000,0x0000},
 /* rmanTwoLeft */
 {0x0000,0x0000,
  0x0000,0x0000,
  0x0003,0x0002,
  0x0007,0x0005,
  0x07CB,0x07C7,
  0x1FC2,0x183E,
  0x3F12,0x20EE,
  0x3628,0x29D6,
  0x3EFF,0x0100,
  0x1F7F,0x0080,
  0x07EE,0x0011,
  0x0070,0x000F,
  0x0070,0x000C,
  0x0000,0x0030,
  0x0000,0x0000,
  0x0000,0x0003,
  0x0001,0x000E,
  0x0007,0x0000,
  0x0003,0x0000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0001,0x0001,
  0x001F,0x001F,
  0x0000,0x0000},
 /* rmanTwoRight */
 {0x0000,0x0000,
  0x7E00,0x6B00,
  0xF300,0xECE0,
  0xFF20,0xF0D0,
  0x3FD0,0x3828,
  0x1FE0,0x181C,
  0x9EC0,0x193E,
  0x1F60,0x109E,
  0x6010,0x9FEF,
  0xC0C8,0x3F37,
  0x0840,0xF7BF,
  0x0FD0,0x102F,
  0x0F82,0x107D,
  0x0DC0,0x323E,
  0x1E80,0xE17E,
  0x7820,0x87DC,
  0xA400,0x5BF8,
  0xF820,0x07D0,
  0xFA00,0x05E0,
  0xC800,0x3700,
  0x3C00,0x0000,
  0x6600,0x0000,
  0xC200,0x0100,
  0xC080,0x0180,
  0x01C0,0xC1C0,
  0xC300,0xC300,
  0xE600,0xE600,
  0x0000,0x0000},
 /* rmanThreeLeft */
 {0x0000,0x0000,
  0x0000,0x0000,
  0x0003,0x0002,
  0x0007,0x0005,
  0x07CB,0x07C7,
  0x1FC2,0x183E,
  0x3F12,0x20EE,
  0x3628,0x29D6,
  0x3EFF,0x0100,
  0x1F7F,0x0080,
  0x07EE,0x0011,
  0x0070,0x000F,
  0x0070,0x000C,
  0x0000,0x0030,
  0x0000,0x0000,
  0x0000,0x0003,
  0x0001,0x000E,
  0x0007,0x0000,
  0x0003,0x0000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000},
 /* rmanThreeRight */
 {0x0000,0x0000,
  0x7E00,0x6B00,
  0xF300,0xECE0,
  0xFF20,0xF0D0,
  0x3FD0,0x3828,
  0x1FE0,0x181C,
  0x9EC0,0x193E,
  0x1F60,0x109E,
  0x6010,0x9FEF,
  0xC0C8,0x3F37,
  0x0840,0xF7BF,
  0x0FD0,0x102F,
  0x0F82,0x107D,
  0x0DC0,0x323E,
  0x1E80,0xE17E,
  0x7820,0x87DC,
  0xA400,0x5BF8,
  0xF820,0x07D0,
  0xFA00,0x05E0,
  0xC800,0x3700,
  0x1800,0x0000,
  0x3000,0x0000,
  0x3C00,0x0000,
  0x0D00,0x0300,
  0x0180,0x0380,
  0x0700,0x0700,
  0x1C00,0x1C00,
  0x0000,0x0000},
 /* ballOneLeft */
 {0x0000,0x0000,
  0x00BF,0x00BF,
  0x0352,0x0352,
  0x07BF,0x07BF,
  0x17C0,0x17C0,
  0x1BEF,0x1BEF,
  0x3CEF,0x3CEF,
  0x3F6F,0x3F6F,
  0xDF9E,0xDF9E,
  0xEFDD,0xEFDD,
  0xB3BD,0xB3BD,
  0x5CBB,0x5CBB,
  0xCF77,0xCF77,
  0x56F7,0x56F7,
  0xD1EF,0xD1EF,
  0x57DF,0x57DF,
  0x1BBE,0x1BBE,
  0x2D79,0x2D79,
  0x16F7,0x16F7,
  0x052F,0x052F,
  0x03CE,0x03CE,
  0x0075,0x0075,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000},
 /* ballOneRight */
 {0x0000,0x0000,
  0x0000,0x0000,
  0xE000,0xE000,
  0x5000,0x5000,
  0xE800,0xE800,
  0x1C00,0x1C00,
  0x6A00,0x6A00,
  0x7500,0x7500,
  0xF300,0xF300,
  0xF580,0xF580,
  0xED80,0xED80,
  0xEE00,0xEE00,
  0xDC80,0xDC80,
  0xDD80,0xDD80,
  0xBA80,0xBA80,
  0x7B00,0x7B00,
  0xF700,0xF700,
  0xEE00,0xEE00,
  0x9400,0x9400,
  0x7800,0x7800,
  0x6000,0x6000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000},
 /* ballTwoLeft */
 {0x0000,0x0000,
  0x0075,0x0075,
  0x03CE,0x03CE,
  0x052F,0x052F,
  0x16F7,0x16F7,
  0x2D79,0x2D79,
  0x1BBE,0x1BBE,
  0x57DF,0x57DF,
  0xD1EF,0xD1EF,
  0x56F7,0x56F7,
  0xCF77,0xCF77,
  0x5CBB,0x5CBB,
  0xB3BD,0xB3BD,
  0xEFDD,0xEFDD,
  0xDF9E,0xDF9E,
  0x3F6F,0x3F6F,
  0x3CEF,0x3CEF,
  0x1BEF,0x1BEF,
  0x17C0,0x17C0,
  0x07BF,0x07BF,
  0x0352,0x0352,
  0x00BF,0x00BF,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000},
 /* ballTwoRight */
 {0x0000,0x0000,
  0x0000,0x0000,
  0x6000,0x6000,
  0x7800,0x7800,
  0x9400,0x9400,
  0xEE00,0xEE00,
  0xF700,0xF700,
  0x7B00,0x7B00,
  0xBA80,0xBA80,
  0xDD80,0xDD80,
  0xDC80,0xDC80,
  0xEE00,0xEE00,
  0xED80,0xED80,
  0xF580,0xF580,
  0xF300,0xF300,
  0x7500,0x7500,
  0x6A00,0x6A00,
  0x1C00,0x1C00,
  0xE800,0xE800,
  0x5000,0x5000,
  0xE000,0xE000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000},
 /* ballThreeLeft */
 {0x0000,0x0000,
  0x0057,0x0057,
  0x0339,0x0339,
  0x0F7A,0x0F7A,
  0x14F7,0x14F7,
  0x3BCF,0x3BCF,
  0x77BE,0x77BE,
  0x6F7D,0x6F7D,
  0xAEFB,0xAEFB,
  0xDDF7,0xDDF7,
  0x9DF7,0x9DF7,
  0x3BEE,0x3BEE,
  0xDBDE,0xDBDE,
  0xD7DD,0xD7DD,
  0x67BC,0x67BC,
  0x577B,0x577B,
  0x2B7B,0x2B7B,
  0x1C7B,0x1C7B,
  0x0B81,0x0B81,
  0x057E,0x057E,
  0x03A5,0x03A5,
  0x007E,0x007E,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000},
 /* ballThreeRight */
 {0x0000,0x0000,
  0x0000,0x0000,
  0xE000,0xE000,
  0x5000,0x5000,
  0xB400,0xB400,
  0x5A00,0x5A00,
  0xEC00,0xEC00,
  0xF500,0xF500,
  0xC580,0xC580,
  0xB500,0xB500,
  0x7980,0x7980,
  0x9D00,0x9D00,
  0xE680,0xE680,
  0xFB80,0xFB80,
  0xFD80,0xFD80,
  0x7E00,0x7E00,
  0x9E00,0x9E00,
  0xEC00,0xEC00,
  0xF400,0xF400,
  0xF000,0xF000,
  0x6000,0x6000,
  0x8000,0x8000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000},
 /* ballFourLeft */
 {0x0000,0x0000,
  0x007E,0x007E,
  0x03A5,0x03A5,
  0x057E,0x057E,
  0x0B81,0x0B81,
  0x1C7B,0x1C7B,
  0x2B7B,0x2B7B,
  0x577B,0x577B,
  0x67BC,0x67BC,
  0xD7DD,0xD7DD,
  0xDBDE,0xDBDE,
  0x3BEE,0x3BEE,
  0x9DF7,0x9DF7,
  0xDDF7,0xDDF7,
  0xAEFB,0xAEFB,
  0x6F7D,0x6F7D,
  0x77BE,0x77BE,
  0x3BCF,0x3BCF,
  0x14F7,0x14F7,
  0x0F7A,0x0F7A,
  0x0339,0x0339,
  0x0057,0x0057,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000},
 /* ballFourLeft */
 {0x0000,0x0000,
  0x8000,0x8000,
  0x6000,0x6000,
  0xF000,0xF000,
  0xF400,0xF400,
  0xEC00,0xEC00,
  0x9E00,0x9E00,
  0x7E00,0x7E00,
  0xFD80,0xFD80,
  0xFB80,0xFB80,
  0xE680,0xE680,
  0x9D00,0x9D00,
  0x7980,0x7980,
  0xB500,0xB500,
  0xC580,0xC580,
  0xF500,0xF500,
  0xEC00,0xEC00,
  0x5A00,0x5A00,
  0xB400,0xB400,
  0x5000,0x5000,
  0xE000,0xE000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000,
  0x0000,0x0000}
};


png_structp png_ptr;
png_infop info_ptr;
int width, height, bit_depth;

static png_color palette[256];


// Row pointers
static uint8_t *rows[NUM_SPRITES * SPRITE_HEIGHT];

static uint8_t data[SPRITE_HEIGHT][16 * NUM_SPRITES];





static int AVViewPort;

static void SetRGB4(int unused, int index, int r, int g, int b)
{
	palette[index].red = ((r + 1) << 4) - 1;
	palette[index].green = ((g + 1) << 4) - 1;
	palette[index].blue = ((b + 1) << 4) - 1;
}


 /*
 MoveSprite(AVViewPort,&AVSprites[4],tbx,tby);
 MoveSprite(AVViewPort,&AVSprites[5],tbx+16,tby);
 if (y[0]<173) {
  ChangeSprite(AVViewPort,&AVSprites[0],AVSpriteData[4]);
  ChangeSprite(AVViewPort,&AVSprites[1],AVSpriteData[5]);
 }
 else {
  ChangeSprite(AVViewPort,&AVSprites[0],AVSpriteData[((x[0]/8)&1)*2]);
  ChangeSprite(AVViewPort,&AVSprites[1],AVSpriteData[((x[0]/8)&1)*2+1]);
 }
 ChangeSprite(AVViewPort,&AVSprites[4],AVSpriteData[((tbx/16)&3)*2+12]);
 ChangeSprite(AVViewPort,&AVSprites[5],AVSpriteData[((tbx/16)&3)*2+13]);
 if (y[1]<173) {
  ChangeSprite(AVViewPort,&AVSprites[2],AVSpriteData[10]);
  ChangeSprite(AVViewPort,&AVSprites[3],AVSpriteData[11]);
 }
 else {
  ChangeSprite(AVViewPort,&AVSprites[2],AVSpriteData[((x[1]/8)&1)*2+6]);
  ChangeSprite(AVViewPort,&AVSprites[3],AVSpriteData[((x[1]/8)&1)*2+7]);
 }
 MoveSprite(AVViewPort,&AVSprites[0],x[0],y[0]);
 MoveSprite(AVViewPort,&AVSprites[1],x[0]+16,y[0]);
 MoveSprite(AVViewPort,&AVSprites[2],x[1],y[1]);
 MoveSprite(AVViewPort,&AVSprites[3],x[1]+16,y[1]);
	*/


static void convertSprite(int id)
{
	int y, i;
	uint16_t msb, lsb, b;
	int color_offset = 0;
	int c;

	if (id >= 0 && id <= 5) {
		// AVSpriteData 0-4 -> Sprites 0,1
		color_offset = 20;
	}
	if (id >= 6 && id <= 11) {
		// AVSpriteData 6-9 -> Sprites 2,3
		color_offset = 24;
	}
	// Ball
	if (id >= 12 && id <= 19) {
		color_offset = 28;
	}

	for (y=0; y<SPRITE_HEIGHT; y++) {
		//	https://wiki.amigaos.net/wiki/Hardware_Sprites
		//
		//
 /* Two words per line of Sprite height, first of the two words contains the MSB for
     * color selection, second word contains LSB (colors 0,1,2,3 from allowable color
     * register selection set).   Color '0' for any Sprite pixel makes it transparent.
     */

		msb = AVSpriteData[id][2 + y*2];
		lsb = AVSpriteData[id][2 + y*2 + 1];

		for (i=0, b=0x8000; i<16; i++, b >>= 1) {
			c = msb & b ? 2 : 0;
			c |= lsb & b ? 1 : 0;

			if (c) {
				data[y][id * 16 + i] = color_offset + c;
			}

		}
	}
}

int main(int argc, char **argv)
{
	const char *outfile = "sprites.png";
	FILE *fp = fopen(outfile, "wb");
	int i;

	SetRGB4(AVViewPort,0,0,0,0);
	SetRGB4(AVViewPort,1,0,0,0);
	SetRGB4(AVViewPort,2,0,0,0);
	SetRGB4(AVViewPort,21,8,15,8);
	SetRGB4(AVViewPort,22,6,12,6);
	SetRGB4(AVViewPort,23,12,13,12);
	SetRGB4(AVViewPort,25,15,8,8);
	SetRGB4(AVViewPort,26,12,6,6);
	SetRGB4(AVViewPort,27,13,12,12);
	SetRGB4(AVViewPort,29,12,12,12);
	SetRGB4(AVViewPort,30,12,12,12);
	SetRGB4(AVViewPort,31,12,12,12);
	SetRGB4(AVViewPort,6,6,8,12);
	SetRGB4(AVViewPort,7,5,7,8);

	// setup row pointers
	for (i=0; i<SPRITE_HEIGHT; i++) {
		rows[i] = data[i];
	}

	for (i=0; i<NUM_SPRITES; i++) {
		convertSprite(i);
	}


	if (!fp) {
		perror(outfile);
		return -1;
	}

	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr) {
		fprintf(stderr, "png_create_write_struct failed\n");
		return -1;
	}

	info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr) {
		png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
		fprintf(stderr, "png_create_info_struct failed\n");
		return -1;
	}

	if (setjmp(png_jmpbuf(png_ptr))) {
		fprintf(stderr, "Error\n");
		return -1;
	}

	width = 16 * NUM_SPRITES;
	height = SPRITE_HEIGHT;
	bit_depth = 8;

	png_init_io(png_ptr, fp);
	png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, PNG_COLOR_TYPE_PALETTE,
				PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
	png_set_PLTE(png_ptr, info_ptr, palette, 32);
	png_set_rows(png_ptr, info_ptr, rows);

	png_write_png(png_ptr, info_ptr, NULL, NULL);
}

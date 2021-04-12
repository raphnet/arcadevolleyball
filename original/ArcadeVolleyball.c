/*
   Arcade Volleyball
   Copyright 1989 COMPUTE! Publications, Inc.
   All rights reserved.

   Please excuse the unorthodox programming style presented in this code.
   With three separate programmers working on one game, things tend to 
   get a bit sloppy.
*/

#include <exec/types.h>
#include <exec/memory.h>
#include <devices/audio.h>
#include <stdio.h>
#include <intuition/intuition.h>
#include <graphics/gfx.h>
#include <graphics/sprite.h>

#define NUMSAMPLES 3
#define JIF1 75
#define PER1 500
#define JIF2 32
#define PER2 500

struct Screen   *OpenScreen();
struct Window   *OpenWindow();
struct ViewPort *ViewPortAddress();

void    OpenStuff();
void    InitShapes();
void    Quit();
USHORT *LoadSample();
USHORT *AllocateMem();
void    StartSound();
void    UpdateSounds();
void    GetPos();
int     DoMenu();
void    Delay();
void    InitGame();
void    CheckKeyboard();
void    Game();

struct IntuitionBase *IntuitionBase = NULL;
struct GfxBase *GfxBase = NULL;

struct TextAttr Font80 = {
 "topaz.font",
 TOPAZ_EIGHTY,
 0,
 FPF_ROMFONT
};

struct Screen *AVScreen = NULL;
struct NewScreen AVNewScreen = {
 0,0,
 320,200,
 3,
 3,0,
 SPRITES,
 CUSTOMSCREEN,
 &Font80,
 NULL,
 NULL,
 NULL
};

struct ViewPort *AVViewPort = NULL;
struct RastPort *AVRastPort = NULL;
struct RastPort *TitleRastPort = NULL;
struct Window *TitleWindow = NULL;
struct Window *AVWindow = NULL;
struct NewWindow NewTitleWindow = {
 0,2,
 280,10,
 0,0,
 NULL,
 NOCAREREFRESH | BACKDROP | BORDERLESS | RMBTRAP,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 0,0,
 0,0,
 CUSTOMSCREEN
};
struct NewWindow AVNewWindow = {
 4,13,
 308,187,
 0,7,
 VANILLAKEY,
 NOCAREREFRESH | BACKDROP | ACTIVATE | RMBTRAP,
 NULL,
 NULL,
 NULL,
 NULL,
 NULL,
 0,0,
 0,0,
 CUSTOMSCREEN
};

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
struct SimpleSprite AVSprites[] = {
 {NULL,26,0,0,0},
 {NULL,26,0,0,0},
 {NULL,26,0,0,0},
 {NULL,26,0,0,0},
 {NULL,26,0,0,0},
 {NULL,26,0,0,0}
};

struct {
 int left, right, up;
} keymove[2];

char *menu[5] = {
 {"    Human vs. Human    "},
 {"  Human vs. Computer   "},
 {"  Computer vs. Human   "},
 {" Computer vs. Computer "},
 {"         Quit          "}
};

char opts[2] = {
 {'C'},
 {'C'}
};

USHORT *waveform[NUMSAMPLES];
USHORT wavelength[NUMSAMPLES];
USHORT *dmaconw = (USHORT *)0xDFF096;
USHORT inuse[4];

int x[2], px[2], y[2], frame[2], frameindex[2], rebound[2], score[2],
    bx, by, pbx, pby, tbx, tby, bvelx, bvely, blogic, bframe, bindex,
    serve, server, servevel, compserve, hits, hitter, starter,
    gravity, sstage, bytop, rnd, endgame, xit, menuon, jflag,
    polecol[]={0,1,2,3,3,4,6,7,9,14},
    jump[]={-4,-4,-3,-3,-3,-3,-2,-2,-2,-2,-2,-1,-1,-1,-1,-1,-1, 0, 0,
             0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4};


int CXBRK()
{
 return(0);
}

void main()
{
 printf("\n");
 printf("\n");
 printf("          Arcade Volleyball\n");
 printf("  Copyright 1989 COMPUTE! Pub., Inc.\n");
 printf("         All Rights Reserved\n");
 OpenStuff();InitShapes();
 inuse[0]=inuse[1]=inuse[2]=inuse[3]=starter=xit=0;
 while (!xit) {
  Game();
  starter=starter^1;
 }
 Quit(0);
}

void OpenStuff()
{
 waveform[0]=LoadSample("samples/hit.sample",&wavelength[0]);
 waveform[1]=LoadSample("samples/loss.sample",&wavelength[1]);
 waveform[2]=LoadSample("samples/point.sample",&wavelength[2]);
 if ((IntuitionBase=
  (struct IntiutionBase *)OpenLibrary("intuition.library",0))==NULL)
  Quit(1);
 if ((GfxBase=(struct GfxBase *)OpenLibrary("graphics.library",0))==NULL)
  Quit(1);
 if ((AVScreen=OpenScreen(&AVNewScreen))==NULL)
  Quit(1);
 AVNewWindow.Screen=AVScreen;NewTitleWindow.Screen=AVScreen;
 if ((AVWindow=OpenWindow(&AVNewWindow))==NULL)
  Quit(1);
 if ((TitleWindow=OpenWindow(&NewTitleWindow))==NULL)
  Quit(1);
 ShowTitle(AVScreen,FALSE);
 AVViewPort=ViewPortAddress(AVWindow);
 AVRastPort=AVWindow->RPort;TitleRastPort=TitleWindow->RPort;
}

void InitShapes()
{
 BYTE i;

 for (i=2;i<8;i++) if (GetSprite(&AVSprites[i-2],i)!=i) Quit(1);
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
 SetAPen(AVRastPort,7);
 RectFill(AVRastPort,149,93,155,189);
 SetAPen(AVRastPort,6);
 RectFill(AVRastPort,150,94,154,188);
 SetAPen(TitleRastPort,3);
 Move(TitleRastPort,32,8);
 Text(TitleRastPort,"00     Arcade Volleyball     00",31);
}

void Quit(e)
int e;
{
 BYTE i;

 *dmaconw=0x000F;
 for (i=2;i<8;i++)
  if (AVSprites[i-2].num==i) FreeSprite(i);
 for (i=0;i<NUMSAMPLES;i++)
  if (waveform[i]) FreeMem(waveform[i],wavelength[i]<<1);
 if (TitleWindow) CloseWindow(TitleWindow);
 if (AVWindow) CloseWindow(AVWindow);
 if (AVScreen) CloseScreen(AVScreen);
 if (GfxBase) CloseLibrary(GfxBase);
 if (IntuitionBase) CloseLibrary(IntuitionBase);
 exit(e);
}

USHORT *LoadSample(filename,length)
char *filename;
USHORT *length;
{
  FILE *file;
  USHORT *buffer;
  ULONG size;

  if((file=fopen(filename,"r"))==NULL)
    return(NULL);
  fseek(file,0L,2);
  size = ftell(file) & ~1L;
  fseek(file,0L,0);
  if((buffer=AllocateMem(size,MEMF_CHIP))==NULL) {
    fclose(file);
    return(NULL);
  }
  *length=(USHORT)(fread((UBYTE *)buffer,1,(int)size,file)>>1);
  fclose(file);
  return(buffer);
}

USHORT *AllocateMem(size,requirements)
ULONG size, requirements;
{
  if(AvailMem(requirements)-size<=32000L)
    return(NULL);
  return((void *)AllocMem(size,requirements));
}

void StartSound(locat,len,jiffs,per,vol,chan)
USHORT *locat;
USHORT len;
int jiffs;
USHORT per,vol,chan;
{
 USHORT *dmaconw = (USHORT *)0xDFF096;
 ULONG *audioaddr[4] = {
  {(ULONG *)0xDFF0A0},
  {(ULONG *)0xDFF0B0},
  {(ULONG *)0xDFF0C0},
  {(ULONG *)0xDFF0D0},
 };
 USHORT *audiolen[4] = {
  {(USHORT *)0xDFF0A4},
  {(USHORT *)0xDFF0B4},
  {(USHORT *)0xDFF0C4},
  {(USHORT *)0xDFF0D4},
 };
 USHORT *audioper[4] = {
  {(USHORT *)0xDFF0A6},
  {(USHORT *)0xDFF0B6},
  {(USHORT *)0xDFF0C6},
  {(USHORT *)0xDFF0D6},
 };
 USHORT *audiovol[4] = {
  {(USHORT *)0xDFF0A8},
  {(USHORT *)0xDFF0B8},
  {(USHORT *)0xDFF0C8},
  {(USHORT *)0xDFF0D8},
 };
 if (locat!=NULL) {
  if (inuse[chan]==0) {
   inuse[chan]=jiffs;
   *audioaddr[chan]=(ULONG)locat;
   *audiolen[chan]=len;
   *audioper[chan]=per;
   *audiovol[chan]=vol;
   switch(chan) {
    case 0: *dmaconw=0x8201;break;
    case 1: *dmaconw=0x8202;break;
    case 2: *dmaconw=0x8204;break;
    case 3: *dmaconw=0x8208;break;
    default: break;
   }
  }
 }
}

void UpdateSounds()
{
 int i;

 for (i=0;i<4;i++) {
  if (inuse[i]!=0) {
   inuse[i]--;
   if (inuse[i]==0) {
    switch(i) {
     case 0: *dmaconw=0x1;break;
     case 1: *dmaconw=0x2;break;
     case 2: *dmaconw=0x4;break;
     case 3: *dmaconw=0x8;break;
    }
   }
  }
 }
}

int DoMenu()
{
 int i;
 static int opt=0;
 static int reprint=1;
 static int timer=0;
 static USHORT lastjoy = 0xFFFF;
 USHORT *joy = (USHORT *)0xDFF00C;
 USHORT *firereg = (USHORT *)0xBFE0FE;

 if ((timer++==10) || (lastjoy!=*joy)) {
  if (*joy&0x01) {
   opt++;if (opt>4) opt=0;
   reprint=1;
  }
  if (*joy&0x100) {
   opt--;if (opt<0) opt=4;
   reprint=1;
  }
  timer=0;
 }
 lastjoy=*joy;

 if (reprint) {
  for (i=0;i<5;i++) {
   if (i!=opt) {
    SetAPen(AVRastPort,7);
    SetBPen(AVRastPort,0);
   } else {
    SetAPen(AVRastPort,0);
    SetBPen(AVRastPort,7);
   }
   Move(AVRastPort,64,28+i*10);
   Text(AVRastPort,menu[i],23);
  }
  reprint=0;
 }

 if ((*firereg&(0x80))==0) {
  switch (opt) {
   case 0: opts[0]=opts[1]='H';break;
   case 1: opts[0]='H';opts[1]='C';jflag=1;break;
   case 2: opts[0]='C';opts[1]='H';break;
   case 3: opts[0]='C';opts[1]='C';break;
   case 4: endgame=xit=1;break;
   default: break;
  }
  if (!xit) {
   SetAPen(AVRastPort,0);
   RectFill(AVRastPort,64,22,248,72);
   InitGame();Delay(50);
   reprint=1;
  }
 }
 return(!reprint);
}

void joystick(pl)
int pl;
{
 USHORT *joy[2] = {
  {(USHORT *)0xDFF00A},
  {(USHORT *)0xDFF00C}
 };
 USHORT *firereg = (USHORT *)0xBFE0FE;

 keymove[pl].right=0;
 keymove[pl].left=0;
 keymove[pl].up=0;
 if ((*joy[pl^jflag]&0x0002)==0) keymove[pl].left=-2;
 if ((*joy[pl^jflag]&0x0200)==0) keymove[pl].right=2;
 if ((*firereg&(0x40<<(pl^jflag)))==0) keymove[pl].up=1;
}

void GetPos()
{
 int i, tx, velx, bnd;

 for (i=0;i<2;i++)
 {
  if (keymove[i].up && frameindex[i]==-1) frameindex[i]=0;
  tx=x[i]+(velx=keymove[i].left+keymove[i].right);
  bnd=3+i*155;
  if (velx>0) {
   if (tx<bnd+119)
    x[i]=tx;
   else
    x[i]=bnd+119;
  }
  else
   if (tx>bnd)
    x[i]=tx;
   else
    x[i]=bnd;
  if (frameindex[i]==-2) {
   y[i]=173;
   frame[i]=0;
   frameindex[i]=-1;
  }
  if (frameindex[i]==-1) {
   if (velx!=0) {
    if (abs(px[i]-x[i])>4) {
     frame[i]^=1;
     px[i]=x[i];
    }
   }
   else
    frame[i]=0;
  }
  else {
   frame[i]=2+(frameindex[i]>18);
   if (frameindex[i]==19) y[i]-=4;
   y[i]+=jump[frameindex[i]++];
   if (frameindex[i]>37) frameindex[i]=-2;
  }
 }
}

int moveball()
{
 int rbvelx, rbvely, hitfloor;

 rbvelx=bvelx;rbvely=bvely;
 if (rbvelx>319) rbvelx=319;
 if (rbvelx<-319) rbvelx=-319;
 if (rbvely>319) rbvely=319;
 if (rbvely<-319) rbvely=-319;
 pbx=tbx;pby=tby;
 bx+=rbvelx;by+=rbvely;
 if (bx<320) {
  bx=320;
  rbvelx=-rbvelx;
  rbvelx-=rbvelx>>4;
  rbvely-=rbvely>>4;
  if (hitter==1) {
   hitter=2;
   hits=0;
  }
 }
 if (bx>18112) {
  bx=18112;
  rbvelx=-rbvelx;
  rbvelx-=rbvelx>>4;
  rbvely-=rbvely>>4;
  if (hitter==0) {
   hitter=2;
   hits=0;
  }
 }
 if (by<832) {
  by=832;
  rbvely=-rbvely;
  rbvelx-=rbvelx>>4;
  rbvely-=rbvely>>4;
 }
 if (by>11392) {
  by=11392;
  rbvely=-rbvely;
  hitfloor=0;
 }
 else
  hitfloor=1;
 if (rbvely>0)
  rbvely+=1;
 else
  rbvely+=1;
 tbx=bx>>6;tby=by>>6;
 bvelx=rbvelx;bvely=rbvely;
 return(hitfloor);
}

void docollisions()
{
 int i, dx, dy, dist, rndoff, avy, jif, per;

 for (i=0;i<2;i++) {
  dx=tbx-x[i]-i*7;dy=tby-y[i]>>1;
  dist=(dx>>2)*dx+dy*dy;
  if (dist<110) {
   rndoff=8-(rnd&15);
   if (frameindex[i]>-1)
    bvely=-abs(bvely)+(jump[frameindex[i]]<<(3<<servevel));
   else
    bvely=-abs(bvely);
   bvely+=rndoff;
   bvelx+=dx*abs(dx)+(keymove[i].right+keymove[i].left<<(4+servevel))+rndoff;
   if (!rebound[i]) {
    if (!menuon) {
     avy=abs(320-abs(bvely));
     per=300+avy;jif=per>>5;
     StartSound(waveform[0],wavelength[0],jif,per,55,i); /* head hit */
    }
    bytop=200;
    serve=0;
    rebound[i]=1;
    if (hitter!=i) {
     hitter=i;
     hits=0;
    }
    else
     hits++;
   }
  }
  else
   if (rebound[i]) rebound[i]=servevel=0;
 }
 i=1;
 if (tby>91) {
  if (pbx<128 && tbx>127) {
   bvelx=-abs(bvelx)>>1;
   bx=127*64;
   i=0;
  }
  else
   if (pbx>159 && tbx<160) {
    bvelx=abs(bvelx)>>1;
    bx=160*64;
    i=0;
   }
 }
 if (i && tby>81 && tbx>127 && tbx<160) {
  if (tby>91) {
   if (tbx<148)
    bvelx=-abs(bvelx);
   else
    bvelx=abs(bvelx);
  }
  else
   if ((tbx>147 && 161-tbx>=polecol[91-tby]) ||
      (tbx<148 && tbx-133>=polecol[91-tby])) {
    if (bvely>0) {
     dx=tbx-145;
     if (dx<-5) bvelx=-abs(bvelx);
     if (dx>5) bvelx=abs(bvelx);
     bvely=-abs(bvely);
    }
    if (abs(bvelx)>32) bvelx=bvelx>>1;
    if (abs(bvely)>32) bvely=bvely>>1;
   }
 }
}

void putshapes()
{
 UpdateSounds();
 WaitBOVP(AVViewPort);
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
}

void resetpt()
{
 int i, j, tvelx, tvely;
 char *scrstr = "  ";

 if (hits>2)
 {
  i=1-hitter;
 }
 else
  i=tbx<150;
 putshapes();
 tvely=abs(bvely)>>3;tvelx=abs(bvelx)>>3;
 j=20;
 do {
  keymove[0].up=keymove[1].up=0;
  GetPos();
  if (abs(bvelx)>tvelx)
   if (bvelx<0)
    bvelx=-tvelx;
   else
    bvelx=tvelx;
  if (abs(bvely)>tvely)
   if (bvely<0)
    bvely=-tvely;
   else
    bvely=tvely;
  docollisions();
  moveball();
  putshapes();
 } while (j-->0 || frameindex[0]!=-1 || frameindex[1]!=-1);
 *dmaconw=0x000F;
 if (i==server) {
  if (!menuon)
   StartSound(waveform[2],wavelength[2],JIF2,PER2,63,3-i); /* point scored */
  score[i]++;
  if (score[i]>14 && score[i]-score[1-i]>1) endgame=1;
  sprintf(scrstr,"%02d",score[server]);
  Move(TitleRastPort,32+232*server,8);
  SetAPen(TitleRastPort,3);
  Text(TitleRastPort,scrstr,2);
 }
 else {
  if (!menuon)
   StartSound(waveform[1],wavelength[1],JIF1,PER1,63,2+i); /* serve lossed */
  server=i;
  SetAPen(TitleRastPort,6);
  if (server) {
   Move(TitleRastPort,48,8);Text(TitleRastPort," ",1);
   Move(TitleRastPort,256,8);Text(TitleRastPort,"*",1);
  }
  else {
   Move(TitleRastPort,48,8);Text(TitleRastPort,"*",1);
   Move(TitleRastPort,256,8);Text(TitleRastPort," ",1);
  }
  SetAPen(TitleRastPort,3);
 }
 if (!menuon) for (j=1;j<50;j++) putshapes();
 bx=(tbx=pbx=(64+i*165))<<6;by=(tby=pby=135)<<6;
 bframe=blogic=bvelx=bvely=hits=rebound[0]=rebound[1]=0;bindex=6;
 serve=servevel=1;hitter=2;
 compserve=abs(rnd)%5;
 if (score[server]==14) compserve=5;
 sstage=0;
}

int destination(int pl, int destx, int tol)
{
 int xp, *dir;

 dir=(int *)&keymove[pl];xp=x[pl];
 if (abs(xp-destx)<tol) {
  *dir=0;*(dir+1)=0;
  return(1);
 }
 if (xp<destx) {
  *dir=0;*(dir+1)=2;
 }
 else {
  *dir=-2;*(dir+1)=0;
 }
 return(0);
}

void computer0()
{
 int ystep, destx, dx, rndoff, dest;

 keymove[0].up=0;
 if (tby<bytop) bytop=tby;
 rndoff=5-rnd%10;
 if (serve && ((server&1)==0))
 {
  switch (compserve) {
   case 0: dest=destination(0,55,2);break;
   case 1: dest=destination(0,84,2);break;
   case 2: dest=destination(0,80,2);break;
   case 3: if (sstage==0) {
             if (dest=destination(0,44,2)) sstage=1;
           }
            else {
             destination(0,58,2);
             dest=1;
            }
            break;
   case 4 : if (sstage==0) {
             if (dest=destination(0,90,2)) sstage=1;
            }
            else {
             destination(0,58,2);
             dest=1;
            }
            break;
   case 5 : if (sstage==0) {
             if (destination(0,3,2)) sstage=1;
             dest=0;
            }
            else {
             destination(0,8+sstage++,1);
             dest=1;
            }
            break;
  }
  keymove[0].up=dest;
 }
 else
  if (bvely>0 && tbx<140) {
   if (bvely>>6==0)
    ystep=0;
   else
    ystep=(140-tby)/(bvely>>6);
    if (ystep<1 || (bvelx>>6)==0)
     destx=tbx;
    else
     destx=tbx+(bvelx>>6)*ystep-4;
   dx=x[0]-tbx;
   if (abs(bvelx)<128 && bytop<75) {
    if ((tby<158)^(bvelx<0))
     destination(0,tbx-15,3);
    else
     destination(0,tbx+15,3);
   }
   else {
    if (tby>130) {
     if (abs(dx)>6 && abs(bvelx)<1024)
      destination(0,tbx-(x[0]-60>>3),3);
     else {
      destination(0,tbx+rndoff+(x[0]-60>>3),10);
      keymove[0].up=x[0]<105 && (hitter!=0 || hits<2);
     }
    }
    else {
     if (destx<3)
      destx=6-destx;
     if (destx>123)
      destx=246-destx;
     destination(0,destx+rndoff,3);
    }
   }
  }
  else
   destination(0,56,8);
}

void computer1()
{
 int ystep, destx, dx, rndoff, dest;

 keymove[1].up=0;
 if (tby<bytop) bytop=tby;
 rndoff=5-rnd%10;
 if (serve && ((server&1)==1))
 {
  switch (compserve) {
   case 0: dest=destination(1,232,2);break;
   case 1: dest=destination(1,202,2);break;
   case 2: dest=destination(1,208,2);break;
   case 3: if (sstage==0) {
             if (dest=destination(1,250,2)) sstage=1;
            }
            else {
             destination(1,220,2);
             dest=1;
            }
            break;
   case 4 : if (sstage==0) {
             if (dest=destination(1,190,2)) sstage=1;
            }
            else {
             destination(1,230,2);
             dest=1;
            }
            break;
   case 5 : if (sstage==0) {
             if (destination(1,277,2)) sstage=1;
             dest=0;
            }
            else {
             destination(1,272-sstage++,1);
             dest=1;
            }
            break;
  }
  keymove[1].up=dest;
 }
 else
  if (bvely>0 && tbx>125) {
   if (bvely>>6==0)
    ystep=0;
   else
    ystep=(140-tby)/(bvely>>6);
    if (ystep<1 || (bvelx>>6)==0)
     destx=tbx;
    else
     destx=tbx+(bvelx>>6)*ystep-4;
   dx=x[1]-tbx;
   if (abs(bvelx)<128 && bytop<75) {
    if ((tby<158)^(bvelx<0))
     destination(1,tbx+15,3);
    else
     destination(1,tbx-15,3);
   }
   else {
    if (tby>130) {
     if (abs(dx)>6 && abs(bvelx)<1024)
      destination(1,tbx+(x[1]-218>>3),3);
     else {
      destination(1,tbx-rndoff-(x[1]-218>>3),10);
       keymove[1].up=x[1]>175 && (hitter!=1 || hits<2);
     }
    }
    else {
     if (destx<158)
      destx=316-destx;
     if (destx>277)
      destx=554-destx;
     destination(1,destx-rndoff,3);
    }
   }
  }
  else
   destination(1,211,8);
}

void CheckKeyboard()
{
 struct IntuiMessage *Msg;
 ULONG class;
 USHORT code;

 while(Msg=(struct IntuiMessage *)GetMsg(AVWindow->UserPort)) {
  class = Msg->Class;
  code = Msg->Code;
  ReplyMsg((struct Message *)Msg);
  if (class==VANILLAKEY && code==27)
   endgame=1;
  if (class==VANILLAKEY && code==32) {
   *dmaconw=0x000F;
   WaitPort(AVWindow->UserPort);
  }
 }
}

void InitGame()
{
 int i;

 *dmaconw=0x000F;
 hits=bframe=blogic=bvelx=bvely=tby=0;
 bindex=6;bytop=200;
 x[0]=64;x[1]=226;
 tbx=400;
 for (i=0;i<2;i++) {
  px[i]=x[i];y[i]=173;
  frameindex[i]=-1;
  rebound[i]=score[i]=keymove[i].right=0;
  keymove[i].left=keymove[i].up=frame[i]=0;
 }
 putshapes();
 bx=(tbx=pbx=64+starter*165)<<6;by=(tby=pby=135)<<6;
 server=2+starter;hitter=2;serve=servevel=1;
 Move(TitleRastPort,32,8);
 Text(TitleRastPort,"00     Arcade Volleyball     00",31);
}

void Game()
{
 int air;

 InitGame();
 opts[0]='C';opts[1]='C';
 jflag=0;menuon=1;endgame=0;
 while (!endgame)
 {
  rnd=rnd*5+1;
  if (menuon)
   menuon=DoMenu();
  else
   CheckKeyboard();
  if (opts[0]=='H')
   joystick(0);
  else
   computer0();
  if (opts[1]=='H')
   joystick(1);
  else
   computer1();
  GetPos();
  if (serve) {
   docollisions();
   putshapes();
   air=1;
  }
  else {
   if (air) {
    docollisions();
    air=moveball();
    putshapes();
   }
  }
  if (!air || hits>2)
   resetpt();
 }
 *dmaconw=0x000F;
 if (!menu) Delay(150);
}

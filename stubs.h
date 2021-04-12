#include <stdint.h>
#include "SMSlib.h"

typedef uint16_t USHORT;
typedef int16_t SHORT;
typedef uint32_t UWORD;
typedef uint8_t BYTE;

#define chip

struct SimpleSprite
{
    UWORD *posctldata;
    UWORD height;
    UWORD   x,y;    /* current position */
    UWORD   num;
};

#define XCNV(a)	((a) - ((a) >> 2) + ((a) >> 5) + 7)
//#define YCNV(a) ((a) > 191 ? 191 : (a))
//#define YCNV(a)	((a) - ((a) >> 2))
#define YCNV(a)	((a) - ((a) >> 4))

#define StartSound(...) do { } while(0)

#define SetAPen(...) do { } while(0)
#define SetBPen(...) do { } while(0)
#define Move(a, x, y) SMS_setNextTileatXY(XCNV(x) >> 3, YCNV(y) >> 3)
#define Text(a, txt, l) printf(txt)
#define RectFill(...) do { } while(0)
#define Delay(...) do { } while(0)

#define WaitBOVP(...)	SMS_waitForVBlank()

SHORT GetSprite(struct SimpleSprite *, SHORT);

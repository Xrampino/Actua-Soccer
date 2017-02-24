#ifndef _JIMLIB_H

#define _JIMLIB_H

// Structure for holding the palette
typedef struct
{
	unsigned char r;                             // RGB values for palette 
	unsigned char g;                             // From 0 to 63
	unsigned char b;										// (Or 256 from DPaint) 
} rgb;

// Structure used for real mode interrupts
struct rminfo
{
	long EDI;
	long ESI;
	long EBP;
	long reserved;
	long EBX;
	long EDX;
	long ECX;
	long EAX;
	short flags;
	short ES,DS,FS,GS,IP,CS,SP,SS;
};

// Structure for holding mouse status
typedef struct
{
	short	x,y,b;
} mouse_struct;

typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned long u_long;

// Prototypes for functions within jimlib.asm
void UpdatePalette(rgb *Buffer);
void SetPalette(unsigned char reg, unsigned char r, unsigned char g, unsigned char b);
unsigned short SetVideoMode(unsigned short mode);
unsigned short SSetVideoMode(unsigned short mode);
void SSetVideoBank(unsigned short mode);
void SSetVideoBankR(unsigned short mode);
void WaitVBlank(void);
void ClearVBanks(unsigned char banks);
unsigned short MouseClick(void);
void LongCopy(unsigned char *, unsigned char *, unsigned short);
void LongSet(unsigned char *, unsigned long, unsigned length);
#include "E:\jimlib\jimfunc.h"
						   
// DOS Text attributes
#define DOS_BLINK     128
#define DOS_INVERSE   119
#define DOS_BRIGHT    8
#define DOS_UNDERLINE 1

typedef enum
{
	DOS_BLACK,
	DOS_BLUE,
	DOS_GREEN,
	DOS_CYAN,
	DOS_RED,
	DOS_MAGENTA,
	DOS_BROWN,
	DOS_WHITE,
	DOS_GREY,
	DOS_LT_BLUE,
	DOS_LT_GREEN,
	DOS_LT_CYAN,
	DOS_LT_RED,
	DOS_LT_MAGENTA,
	DOS_YELLOW,
	DOS_BRIGHT_WHITE
} dos_colours;

// Some useful macros
#define SCROLL_UP   6
#define SCROLL_DOWN 7
#define limitRange(x,l,u) x=((x)<(l))?(l):((x)>(u))?(u):(x)
#define diff(x1,x2) (((x1)>(x2))?((x1)-(x2)):((x2)-(x1)))
#define JIM_SEG(_ptr) (((int)(_ptr))>>4)
#define JIM_OFF(_ptr) (((int)(_ptr))&0xF)
#define JIM_PTR(_seg,_off) ((((int)(_seg))<<4)+((int)(_off)))
#define clear(x) memset(&x,0,sizeof(x))
#define save_cursor() cursor_position_routine(0)
#define restore_cursor() cursor_position_routine(1)
#define WORD68(x) ( ((x&0x00ff)<<8) + (x>>8) )
#define LONG68(x) ( ((x&0x000000ff)<<24) + ((x&0x0000ff00)<<8)+((x&0x00ff0000)>>8)+(x>>24))

// ADPCM stuff for playstation
#define SUB_FORM1  (0)
#define SUB_FORM2  (1<<5)
#define SUB_AUDIO  (1<<2)
#define SUB_DATA   (1<<3)
#define SUB_RT     (1<<6)
#define SUB_EOF    (1<<7 | 1<<0)
#define SUB_STEREO (1<<0)
#define SUB_ADPCMC (1<<2)

#ifndef VGA_SCREEN
#define VGA_SCREEN ((unsigned char *)0xa0000)
#endif

#define DOS_SCREEN ((unsigned short *)0xb8000)

#endif /* _JIMLIB_H */

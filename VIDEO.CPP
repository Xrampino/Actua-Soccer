#include <iostream.h>
#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
#include <i86.h>
#include <dos.h>
#include <conio.h>
#include <float.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include "defines.h"
#include "3deng.h"
#include "video.h"
#include "gamedata.h"

int	gdv_gran;
extern	int	winrange,Vbytesperline;

#ifndef min
#define min(a,b)  (((a) < (b)) ? (a) : (b))
#endif

#ifndef abs
#define abs(a)		(((a) < 0) ? -(a) : (a))
#endif

struct RMI
{
	long			EDI;
	long			ESI;
	long			EBP;
	long			reserved;
	long			EBX;
	long			EDX;
	long			ECX;
	long			EAX;
	short			flags;
	short			ES, DS, FS, GS, IP, CS, SP, SS;
};

struct
{
	unsigned short					attributes;
	unsigned char					win_a_attr;
	unsigned char					win_b_attr;
	unsigned short					win_granularity;
	unsigned short					win_size;
	unsigned short					win_a_segment;
	unsigned short					win_b_segment;
	unsigned long					win_windor;
	unsigned short					bytes_per_scanline;

	unsigned short					x_resolution;
	unsigned short					y_resolution;
	unsigned char					x_char_size;
	unsigned char					y_char_size;
	unsigned char					mem_planes;
	unsigned char					bits_per_pixel;
	unsigned char					number_banks;
	unsigned char					mem_model;
	unsigned char					bank_size;
	unsigned char					number_images;
	unsigned char					reserved0;

	unsigned char					red_mask_size;
	unsigned char					red_field_pos;
	unsigned char					green_mask_size;
	unsigned char					green_field_pos;
	unsigned char					blue_mask_size;
	unsigned char					blue_field_pos;
	unsigned char					rsvd_mask_size;
	unsigned char					reserved1[216];
} ModeInfo;

int win_range;

void blank_pallette()
{
	outp( 0x3c8, 0 );

	for ( short loop = 0 ; loop < 768 ; loop++ )
		outp( 0x3c9, 0 );
}



void set_pallette( unsigned char *pallette )
{
	outp( 0x3c8, 0 );

	for ( short loop = 0 ; loop < 768 ; loop++ )
		outp( 0x3c9, pallette[loop] >> 3);
}



void set_pallette_entry( unsigned char color, unsigned char red, unsigned
	char blue, unsigned char green )
{
	outp( 0x3c8, color );
	outp( 0x3c9, red );
	outp( 0x3c9, green );
	outp( 0x3c9, blue );
}
//int set_vesa_mode( unsigned short mode_no, int checks )
//{
//
//	if 	( match_info.menu_res==HI )
//	{
//			
//		REGS			regs;
//		SREGS			sregs;
//	 	short			segment, off, result, selector;
//		char			far *ptr;
//		RMI			real_mode;
//
//		if (checks)
//		{
//			//	Create a temporary working space for real mode interrupts...
//			memset( &sregs, 0, sizeof( SREGS ) );
//
//			// Call the DPMI function to allocate 256 bytes of DOS memory
//			regs.w.ax = 0x0100;
//			regs.w.bx = (sizeof(ModeInfo) / 16) + 1;
//			int386x( 0x31, &regs, &regs, &sregs );
//
//			segment = regs.w.ax;
//			selector = regs.w.dx;
//
//			// Make use a far pointer to the base memory so we can reference it
//			ptr = (char far *) MK_FP( selector, 0 );
//
//			memset( &real_mode, 0, sizeof( RMI ) );
//			real_mode.EAX = 0x4f01;
//			real_mode.ECX = mode_no;
//			real_mode.EDI = 0;
//			real_mode.ES = segment;
//
//			regs.w.ax = 0x0300;
//			regs.h.bl = 0x10;
//			regs.h.bh = 0;
//			regs.w.cx = 0;
//			sregs.es = FP_SEG( &real_mode );
//			regs.x.edi = FP_OFF( &real_mode );
//
//			int386x( 0x31, &regs, &regs, &sregs );
//
//			_fmemcpy( &ModeInfo, ptr, sizeof( ModeInfo ) );
//
//			// Free the 256 byte base memory
//			regs.w.ax = 0x101;
//			regs.w.dx = selector;
//			int386( 0x31, &regs, &regs );
//
//			result = (short) real_mode.EAX;
//
//			if (result != 0x004f)
//				return VESA_MODE_NOT_SUPPORTED;
//
//		// Mode was ok to get info, so lets continue to actually set the mode...
//	}
//
//		regs.w.ax = 0x4f02;
//		regs.w.bx = mode_no;
//		int386( 0x10, &regs, &regs );
//
//	// last ditch effort
//
//		if (regs.h.ah != 0)
//		{
//			regs.h.ah = 0;
//			regs.h.al = (char) mode_no;
//			int386( 0x10, &regs, &regs );
//		}
//
//	//	Make sure the Window A pointer is set to 0
//
//		if (checks)
//		{
//			regs.w.ax = 0x4f05;
//			regs.w.bx = 0x0000;
//			regs.w.dx = 0x0000;
//			int386( 0x10, &regs, &regs );
//		}
//
//		win_range = (ModeInfo.win_granularity * 1024 );
//	}
//	return VESA_MODE_OK;
//}





void svgacopy(unsigned char *buffpt,short x,short y,short w,short h, short buff_wid)
{
	win_range	=	winrange;
	ModeInfo.bytes_per_scanline	=	Vbytesperline;

	if 	( match_info.menu_res==HI )
	{

		union REGS regs;

		short i,co;
		char *scrpt;
		int scrdisp=x +ModeInfo.bytes_per_scanline * y;
		char bank=scrdisp / win_range;

		scrdisp%=win_range;
		scrpt=(char *)0xa0000+scrdisp;
		regs.x.eax=0x4f05;
		regs.x.ebx=0;
		regs.x.edx=bank;
		int386(16,&regs,&regs);
		do
		{
			co=min((win_range-scrdisp)/ModeInfo.bytes_per_scanline,h);
			for (i=0;i<co;i++)
			{
				memcpy(scrpt,buffpt,w);
				scrpt+=ModeInfo.bytes_per_scanline;
				buffpt+= buff_wid;
				h--;
			}
			if (h)
			{
				scrdisp=(scrdisp+(co+1)*ModeInfo.bytes_per_scanline)%win_range;
				co=min(ModeInfo.bytes_per_scanline-scrdisp,w);
				memcpy(scrpt,buffpt,co);
	 			bank++;	 
	 			regs.x.eax=0x4f05;
	 			regs.x.ebx=0;
	 			regs.x.edx=bank;
	  			int386(16,&regs,&regs);
	 			if (co!=w) 
					memcpy((char *)0xa0000,buffpt+co,w-co);
				scrpt=(char *)0xa0000+scrdisp;
				buffpt+=buff_wid;
				h--;
		 	}
		} while (h);
	
		regs.x.eax=0x4f05;
		regs.x.ebx=0;
		regs.x.edx=0;
		int386(16,&regs,&regs);
	}

//	else
//	
//	{
//		SVGAxpos	=	x;
//		SVGAypos	=	y;
//		SVGAwidth	=	w;
//		SVGAheight	=	h;
//	 	svgacopy_LO();
//	}	
}

void svgaread(char *buffpt,short x,short y,short w,short h, short buff_wid)
{
	union REGS regs;
	short i,co;
	char *scrpt;
	int scrdisp=x + ModeInfo.bytes_per_scanline * y;
	char bank=scrdisp / win_range;

	scrdisp%=win_range;
	scrpt=(char *)0xa0000+scrdisp;
	regs.x.eax=0x4f05;
	regs.x.ebx=1;
	regs.x.edx=bank;
	int386(16,&regs,&regs);
	do
	{
		co=min((win_range-scrdisp)/ModeInfo.bytes_per_scanline,h);
		for (i=0;i<co;i++)
		{
			memcpy(buffpt,scrpt,w);
			scrpt+=ModeInfo.bytes_per_scanline;
			buffpt+= buff_wid;
			h--;
		}
		if (h)
		{
			scrdisp=(scrdisp+(co+1)*ModeInfo.bytes_per_scanline)%win_range;
			co=min(ModeInfo.bytes_per_scanline-scrdisp,w);
			memcpy(buffpt,scrpt,co);
 			bank++;	 
 			regs.x.eax=0x4f05;
 			regs.x.ebx=1;
 			regs.x.edx=bank;
  			int386(16,&regs,&regs);
 			if (co!=w) 
				memcpy(buffpt+co,(char *)0xa0000,w-co);
			scrpt=(char *)0xa0000+scrdisp;
			buffpt+=buff_wid;
			h--;
	 	}
	} while (h);

	regs.x.eax=0x4f05;
	regs.x.ebx=1;
	regs.x.edx=0;
	int386(16,&regs,&regs);
}

short get_curr_vmode()
{
	REGS				regs;

	regs.x.eax = 0x4f03;
	int386( 0x10, &regs, &regs );

	if (regs.w.ax == 0x004f)
		return regs.w.bx;
	
	return 0;
}

void draw_line(	short x1, short y1,
						short x2, short y2, 
						char col, buff_info *buffer )
{
	int		x, y, deltax, deltay, i, numpixels;
	int		d, dinc1, dinc2, xinc1, xinc2, yinc1, yinc2;

	deltax = abs(x2 - x1);
	deltay = abs(y2 - y1);

	if (deltax >= deltay)
	{
		numpixels = deltax + 1;
		d = (deltay << 1) - deltax;
		dinc1 = deltay << 1;
		dinc2 = (deltay - deltax) << 1;
		xinc1 = 1;
		xinc2	= 1;
		yinc1 = 0;
		yinc2 = 1;
	}
	else
	{
		numpixels = deltay + 1;
		d = (deltax << 1) - deltay;
		dinc1 = deltax << 1;
		dinc2 = (deltax - deltay) << 1;
		xinc1 = 0;
		xinc2 = 1;
		yinc1 = 1;
		yinc2 = 1;
	}

	if (x1 > x2)
	{
		xinc1 = -xinc1;
		xinc2 = -xinc2;
	}

	if (y1 > y2)
	{
		yinc1 = -yinc1;
		yinc2 = -yinc2;
	}

	x = x1;
	y = y1;

	for ( i = 0; i < numpixels; i++ )
	{
		if ((x >= 0) && (x < buffer->clip_wid) && 
			 (y >= 0) && (y < buffer->clip_hgt))
		{
			*(buffer->buff_start + (y * buffer->buff_wid) + x) = col;
		}

		if ( d < 0 )
		{
			d += dinc1;
			x += xinc1;
			y += yinc1;
		}
		else
		{
			d += dinc2;
			x += xinc2;
			y += yinc2;
		}
	}
}



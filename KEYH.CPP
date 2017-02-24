#include <dos.h>
#include <i86.h>
#include <bios.h>
#include <conio.h>
#include <string.h>
#include "defines.h"
#include "externs.h"

extern char debug;
extern char on_3d;
extern int counter;
char return_doskey=FALSE;
extern "C" int network_on;

void	(__interrupt __far *prev_int_9)();

/****************************************************************
/***************************************************************/

char anykey;

void	__interrupt __far key_handler()
{
	static l1=0,l2=0,l3=0;		//remember last 3 codes to check for pause.
	int a;
	char ret_int;

	a=inp(0x60);

	l1=l2;
	l2=l3;
	l3=a;
	if (l1==0xE1 && l2==0x1d && l3==0x45)
	{
		if (!network_on)
		{
			paused=!paused;
			ret_int=1;
		}
	}
	else
	{
		ret_int=0;
		if (debug)				// (Prnt Scr) for debug.
			if (key_togs[0x20])		// d
				ret_int=1;

		if (!on_3d)
			ret_int=1;

		if (return_doskey)
			ret_int=1;
	}

// Ignore 0xFA...
	if (a!=0xfa)
	{
		if (a!=0xe0)
		{
			if (a & 0x80)
			{
// key released...
				if (l2!=0xe0)			// not special header.
				{
					keys[a & 0x7f]=0;	// Normal key release!
				}
				else
				{
// special...
					keys[SPECIALK+(a & 0x7f)]=0;	// Special key release!
				}
			}
			else
			{
// new key...
				anykey=TRUE;
				if (l2!=0xe0 || a!=0x2a)
				{
// no special pre-codes...
					if (l2==0xe0)
					{
						if (!keys[SPECIALK+a])
						{
// new special...
							keys[SPECIALK+a]=1;	// Special key release!
							key_togs[SPECIALK+a]=!key_togs[SPECIALK+a];
						}
					}
					else
					{
// Normal key depress...
						if (!keys[a])
						{
// New norm. key...
							keys[a]=1;
							key_togs[a]=!key_togs[a];
						}
					}
				}
			}
		}
	}
			
	if (a!=0xE1)		//trash normal pause
	{
		if ((a & 0x7f)!=0x1d && (a & 0x7f)!=0x45)
			paused=0;
	}
	
	if (ret_int)
		_chain_intr(prev_int_9);
	else
		{
		//suspected pause - don't pass to normal key handler!
		outp(0x20,32);			//terminate int
		}
}

void	claim_key_int(void)
	{
	prev_int_9=_dos_getvect(0x9);
	_dos_setvect(0x9,key_handler);
	memset((void *)keys,0,128);
	}


void	release_key_int(void)
	{
	_dos_setvect(0x9,prev_int_9);
	}


#include <i86.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#include "eurodefs.h"
#include "euro_fxd.h"
#include "euro.equ"
#include "euro_sym.h"
#include "euro_def.h"
#include "euro_var.h"
#include "euro_grf.h"
#include "euro_dsk.h"
#include "euro_fix.h"
#include "euro_sel.h"
#include "euro_inf.h"

#include "defines.h"

//********************************************************************************************************************************

char	InitialiseUser( char user, char cntrl )
	{
		if ( EUROgameType == EURO_friendly )
		{
			UserList[user].control = cntrl;
			user++;
		}

		if ( EUROgameType == EURO_championship )
		{
			UserList[user].control = cntrl;
			user++;
		}


			
		if ( (EUROgameType == EURO_network_game || EUROgameType == EURO_wireplay )
			&& user==0 )
		{
			UserList[user].control = cntrl;
			user	=	1;
		}

	return(user);
	}

//********************************************************************************************************************************

char	CalculateMaxPlayers()
	{
		char	players	=	0;

		for ( char p=0; p<16 ; p++ )
		{
			if (CtrlFlags[p] == Usable)
				players++;		
		}

		return(players);
	}

//********************************************************************************************************************************

void	SetupMouseLimits( int Xmin, int Xmax, int Ymin, int Ymax )
	{
		if ( MouseDriverInstalled != 0 )
		{
			union REGS rg;
			rg.x.ecx = Xmin;
			rg.x.edx = Xmax;
			rg.x.eax = 7;
			int386(0x33,&rg,&rg);
			rg.x.ecx = Ymin;
			rg.x.edx = Ymax;
			rg.x.eax = 8;
			int386(0x33,&rg,&rg);
		}
	}

//********************************************************************************************************************************

char	SetupControlMethods()
	{
		for ( char m=0; m<16 ; m++ )
		{CtrlFlags[m]	=	Unusable;}	

		char	user = 0;

// ***> Configure KEYBOARD 1		
 
			CtrlFlags[EuroKeyboard1] = Usable;
			user = InitialiseUser( user, EuroKeyboard1 );		      	
			
			if (EUROverbose)
				printf	("þ Keyboard 1 initialised.\n");

// ***> Configure KEYBOARD 2

			CtrlFlags[EuroKeyboard2] = Usable;
			user = InitialiseUser( user, EuroKeyboard2 );		      	

			if (EUROverbose)
				printf	("þ Keyboard 2 initialised.\n");

// ***> Configure JOYSTICK 1
		
//			CtrlFlags[EuroJoystick1] = Usable;
//			user = InitialiseUser( user, EuroJoystick1 );		      	
//
//			if (EUROverbose)
//				printf	("þ Joystick 1 initialised.\n");
//
// ***> Configure JOYSTICK 2



// ***> Configure MOUSE
	
		union REGS rg;
		rg.x.eax = 0;
		int386(0x33,&rg,&rg);

		if ( (MouseDriverInstalled = rg.h.al) != 0 )
		{
			CtrlFlags[EuroMouse] = Usable;
			SetupMouseLimits( 0, 626, 1, 452 );
			user = InitialiseUser( user, EuroMouse);		      	
		}

		if ( MouseDriverInstalled == 0 )
		{
			if (EUROverbose)
				printf	("þ Mouse Driver not found.\n");
		}
		else
		{
			if (EUROverbose)
				printf	("þ Mouse Driver found and initialised.\n");
		}

// ***> Configure LOGITECH PAD

		return	( CalculateMaxPlayers() );
	}

//********************************************************************************************************************************

float 	WhichButton(short button, float var )
	{
		if ( button == LEFT_BUTTON )
			return(-var);
		else
			return(var);
	}

//********************************************************************************************************************************

void	GetConsoleInput()
	{
		if ( MouseDriverInstalled != 0 )
		{
			short	buttons;
			union REGS inregs, outregs;
			inregs.w.ax = 3;
			int386(0x33, &inregs, &outregs);
			SelectorXcoord	=	outregs.w.cx;
			SelectorYcoord	=	outregs.w.dx;
			buttons		=	outregs.w.bx;
			
			if ( DeBounce == 0 )
				ButtonState = buttons;
			else
			{
				ButtonState = 0;
				if ( buttons == 0 )
					DeBounce = 0;				
			}
		}
	}

//********************************************************************************************************************************

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
#include "euro_gen.h"
#include "euro_grf.h"
#include "euro_dsk.h"
#include "euro_fix.h"
#include "euro_sel.h"
#include "euro_inf.h"
#include "euro_cnt.h"
#include "euro_usr.h"
#include "euro_net.h"
#include "euro_inp.h"
#include "euro_spt.h"
#include "euro_int.h"

#include "defines.h"


//********************************************************************************************************************************

short	DisplayModemSetupPanel()
	{
		short	x;

		DisplayString( 36, 132,	GetTEXT( MODM_LBLS+Initialisation ), LARGE_FONT, 29, NO_BOX,
			&FrontendBackgroundDEFN, &FrontendTextureDEFN  );

		DisplayString( 36, 306,	GetTEXT( MODM_LBLS+Typeheading ), LARGE_FONT, 29, NO_BOX,
			&FrontendBackgroundDEFN, &FrontendTextureDEFN  );



		DisplayString( 36, 165,	GetTEXT( MODM_LBLS+Type ), MEDIUM_FONT, 22, MODEM_SELECT_BOX,
			&FrontendBackgroundDEFN, &FrontendTextureDEFN  );
	  
		Bounding_table[ MODEM_SELECT_BOX ].BoundingBoxRight = 400;
		x = NextXposn;

		DisplayString( 36, 209,	GetTEXT( MODM_LBLS+Dial ), MEDIUM_FONT, 22, DIAL_SELECT_BOX, 
			&FrontendBackgroundDEFN, &FrontendTextureDEFN  );
		Bounding_table[ DIAL_SELECT_BOX ].BoundingBoxRight = 400;

		if ( NextXposn > x )
			x = NextXposn;

		DisplayString( 36, 187,	GetTEXT( MODM_LBLS+Comport ), MEDIUM_FONT, 22, COM_SELECT_BOX, 
			&FrontendBackgroundDEFN, &FrontendTextureDEFN  );

		Bounding_table[ COM_SELECT_BOX ].BoundingBoxRight = 400;

		if ( NextXposn > x )
			x = NextXposn;

		DisplayString( 36, 231,	GetTEXT( MODM_LBLS+Initstring ), MEDIUM_FONT, 22, INIT_STRING_BOX, 
			&FrontendBackgroundDEFN, &FrontendTextureDEFN  );

		if ( NextXposn > x )
			x = NextXposn;

		DisplayString( 36, 253,	GetTEXT( MODM_LBLS+Phonenumber ), MEDIUM_FONT, 22, NO_BOX, 
			&FrontendBackgroundDEFN, &FrontendTextureDEFN  );

		if ( NextXposn > x )
			x = NextXposn;

		return(x+16);
	}

//********************************************************************************************************************************

void	DisplayModemList( char MODEM )

	{
		int	PAL;

		CopyFromBACKtoPSEUDObuffer(
			&FrontendPseudoDEFN, &FrontendBackgroundDEFN,
				48, 340, 290, 18*6 );

  		for ( char m=0; m < 6; m ++ )
		{
			if ( (MODEM+m) == EUROmodemType )
				PAL = 15;
			else			
				PAL = 22;

			DisplayString( 48, 340+(m*18),	
				(char *)Modems[ MODEM+m ], 
				SMALL_FONT, PAL, m, 
				&FrontendPseudoDEFN, &FrontendTextureDEFN  );
			Bounding_table[m].BoundingBoxRight = 360;
		}

		AddToDumpList( 48, 340, 290, 18*6 );
	}

//********************************************************************************************************************************

void	InitialiseInitString( signed short MODEM )
	{
		char	*m = (char *)ModemInitStrs[ ModemInitList[MODEM] ];
	 	strcpy( &InitStr[0], m );
	}
	
//********************************************************************************************************************************

void	DisplayInitString()
	{
		CopyFromBACKtoPSEUDObuffer(
			&FrontendPseudoDEFN, &FrontendBackgroundDEFN,
				ModemXposn, 234, INIT_LENGTH+16, 18 );

		DisplayString( ModemXposn, 234,	
			&InitStr[0], 
			SMALL_FONT, 15, NO_BOX, 
			&FrontendPseudoDEFN, &FrontendTextureDEFN  );

		AddToDumpList( ModemXposn, 234, INIT_LENGTH+16, 18 );
		Bounding_table[INIT_STRING_BOX].BoundingBoxRight = 36+ModemXposn+INIT_LENGTH;
	}

//********************************************************************************************************************************

void	DisplayModemType()
	{
		CopyFromBACKtoPSEUDObuffer(
			&FrontendPseudoDEFN, &FrontendBackgroundDEFN,
				ModemXposn, 168, 290, 18 );

		DisplayString( ModemXposn, 168,	
			(char *)Modems[ EUROmodemType], 
			SMALL_FONT, 15, MODEM_SELECT_BOX, 
			&FrontendPseudoDEFN, &FrontendTextureDEFN  );

		AddToDumpList( ModemXposn, 168, 290, 18 );
	}

//********************************************************************************************************************************

void	DisplayDialSetting()
	{
		CopyFromBACKtoPSEUDObuffer(
			&FrontendPseudoDEFN, &FrontendBackgroundDEFN,
				ModemXposn, 212, 100, 18 );
		DisplayString( ModemXposn, 212,	GetTEXT( DIAL_LBLS+EUROmodemDialType ), SMALL_FONT, 15, DIAL_SELECT_BOX, 
			&FrontendPseudoDEFN, &FrontendTextureDEFN  );
		AddToDumpList( ModemXposn, 212, 100, 18 );
	}

//********************************************************************************************************************************

void	DisplayCommSetting()
	{
		CopyFromBACKtoPSEUDObuffer(
			&FrontendPseudoDEFN, &FrontendBackgroundDEFN,
				ModemXposn, 190, 100, 18 );
		DisplayString( ModemXposn, 190,	GetTEXT( CMPT_LBLS+EUROmodemCommType ), SMALL_FONT, 15, COM_SELECT_BOX, 
			&FrontendPseudoDEFN, &FrontendTextureDEFN  );
		AddToDumpList( ModemXposn, 190, 100, 18 );
	}

//********************************************************************************************************************************

void	DisplayTelephoneNumber()
	{
		CopyFromBACKtoPSEUDObuffer(
			&FrontendPseudoDEFN, &FrontendBackgroundDEFN,
				ModemXposn, 256, DIAL_LENGTH+16, 18 );

		DisplayString( ModemXposn, 256,	
			&DialNumber[0], 
			SMALL_FONT, 15, DIAL_NUMBER_BOX, 
			&FrontendPseudoDEFN, &FrontendTextureDEFN  );

		AddToDumpList( ModemXposn, 256, DIAL_LENGTH+16, 23 );

		Bounding_table[DIAL_NUMBER_BOX].BoundingBoxRight = 36+ModemXposn+DIAL_LENGTH;
	}

//********************************************************************************************************************************

void	DoModemSetup( char MENU, signed char BOX )
	{
		if ( MENU == MODEM_SETUP && LogicState == RUN_FRONTEND)
		{
			char	ReprintList	=	No;

			short	oldpage	= ModemYpage;
				ModemSelectDEFN.elements = Modemcount;
				ModemYpage = ControlSlider( &ModemSelectDEFN, SelectorXcoord, SelectorYcoord, ButtonState );

			if ( oldpage != ModemYpage )
				ReprintList	=	Yes;

//			if ( ((BOX >= 0 && BOX <8) || ( BOX == MODEM_SELECT_BOX)) && ButtonState != 0 )


			if ( (BOX >= 0 && BOX <8) && ButtonState != 0 )
			{
				if ( (BOX >= 0 && BOX <8) )
					EUROmodemType = ModemYpage+BOX;
//			else
//				{
//		      			if ( ButtonState == LEFT_BUTTON )
//						EUROmodemType--;
//	      				if ( ButtonState == RIGHT_BUTTON )
//						EUROmodemType++;
//					if ( EUROmodemType < 0 )
//						EUROmodemType = 0;
//					if ( EUROmodemType >= Modemcount )
//						EUROmodemType = Modemcount-1;
//				}								 	

				DisplayModemType();
				InitialiseInitString( EUROmodemType );
				DisplayInitString();
				ReprintList	=	Yes;
			     	DeBounce  	= 	TRUE;
			}


			if ( ReprintList==Yes )
				DisplayModemList( ModemYpage );
			
	 		
			if ( BOX == DIAL_SELECT_BOX && ButtonState != 0 )
			{
					EUROmodemDialType^=	1;
					DisplayDialSetting();
				     	DeBounce  	= 	TRUE;
			}								 	
	 		
			if ( BOX == COM_SELECT_BOX && ButtonState != 0 )
			{
					if ( ButtonState != LEFT_BUTTON )
						EUROmodemCommType++;
					if ( ButtonState != RIGHT_BUTTON )
						EUROmodemCommType--;
					EUROmodemCommType&=	3;
					DisplayCommSetting();
				     	DeBounce  	= 	TRUE;
			}								 	




			if ( BOX == DIAL_NUMBER_BOX && ButtonState != 0 && EuroTextEditState == 0 )
			{
					DialX	=  strlen ( &DialNumber[0] );
					EuroTextEditState = EDIT_DIAL_NUMBER;
				     	DeBounce  	= 	TRUE;
			}								 	

			if ( BOX == INIT_STRING_BOX && ButtonState != 0 && EuroTextEditState == 0 )
			{
					InitX	=  strlen ( &InitStr[0] );
					EuroTextEditState = EDIT_INIT_STRING;
				     	DeBounce  	= 	TRUE;
			}								 	

						
			if ( EuroTextEditState == EDIT_DIAL_NUMBER )
			{
				char	f;
		
				if ( PixelLengthOfString(&DialNumber[0],SMALL_FONT) >= DIAL_LENGTH )
					f = DISABLE_INPUT;
				else							
					f = ENABLE_INPUT;
			
				DialX	=	DoTextINPUT( &DialNumber[0], DialX, 30, DIAL, f );
			       	strcpy( &DialNumber[0], TextEditBuffer );
				DisplayTelephoneNumber();
	
				if ( EuroTextEditState == EDIT_DIAL_NUMBER )
					DisplayTextInputCursor( ModemXposn, DialX, 256,
						&DialNumber[0],	SMALL_FONT, 15,	
							&FrontendPseudoDEFN, &FrontendTextureDEFN  );
			}

			if ( EuroTextEditState == EDIT_INIT_STRING )
			{
				char	f;
		
				if ( PixelLengthOfString(&InitStr[0],SMALL_FONT) >= INIT_LENGTH )
					f = DISABLE_INPUT;
				else							
					f = ENABLE_INPUT;
			
				InitX	=	DoTextINPUT( &InitStr[0], InitX, 64, NORMAL, f );
			       	strcpy( &InitStr[0], TextEditBuffer );
				DisplayInitString();
	
				if ( EuroTextEditState == EDIT_INIT_STRING )
					DisplayTextInputCursor( ModemXposn, InitX, 234,
						&InitStr[0], SMALL_FONT, 15,	
							&FrontendPseudoDEFN, &FrontendTextureDEFN  );
			}
		}
	}

//********************************************************************************************************************************

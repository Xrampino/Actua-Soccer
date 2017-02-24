#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>

#include "eurodefs.h"
#include "euro_fxd.h"
#include "euro.equ"
#include "euro_sym.h"
#include "euro_def.h"
#include "euro_var.h"
#include "euro_gen.h"
#include "euro_dsk.h"
#include "euro_int.h"

#include "3deng.h"
//#include "video.h"

extern	int		testVESA;
extern	int	 	VESAmode(int *);
extern  void near svgacpy( char unsigned near *, short, short, short, short, short );
extern	short		GetSwitch( char *buf );

//********************************************************************************************************************************

void straightcopy(int copyWidth, BYTE *dest, BYTE *srce)
	{
	int	x;
	BYTE pixel;
	for (x=0; x < copyWidth; x++)
		*dest++ = *srce++;
	}

void spritecopy(int copyWidth, BYTE *dest, BYTE *srce)
	{
	int	x;
	BYTE pixel;
	for (x=0; x < copyWidth; x++)
		{
		pixel = *srce++;

		if (pixel)
			*dest = pixel;
		dest++;
		}
	}

void flipsprcopy(int copyWidth, BYTE *dest, BYTE *srce)
	{
	int	x;
	BYTE pixel;
	srce+=	(copyWidth-1);
	
	for (x=0; x < copyWidth; x++)
		{
		pixel = *srce--;

		if (pixel)
			*dest = pixel;
		dest++;
		}
	}

void spriteinccopy(int copyWidth, BYTE *dest, BYTE *srce)
	{
	int	x;
	BYTE pixel;
	for (x=0; x < copyWidth; x++)
		{
		pixel = *srce++;
		if (pixel)
			*dest = (pixel+svalue);
		dest++;
		}
	}

void spriteareainccopy(int copyWidth, BYTE *dest, BYTE *srce)
	{							// if a pixel falls within 'pmin' & 'pmax' then 
	int	x;						// it is increased by 'svalue'.
	BYTE pixel;
	for (x=0; x < copyWidth; x++)
		{
		pixel = *srce++;
		if (pixel)
		{
			if ( pixel >= pmin && pixel < pmax )
				*dest = (pixel+svalue);
	     	   else
				*dest = pixel;
		}


		dest++;
		}
	}

void spritefilter(int copyWidth, BYTE *dest, BYTE *srce)
	{
	int	x;
	BYTE pixel;
	for (x=0; x < copyWidth; x++)
		{
		pixel = *srce++;
		if (pixel)
			{
			pixel = *dest;
			*dest = ftable[pixel];
			}
		dest++;
		}
	}

void pseudostore(int copyWidth, BYTE *dest, BYTE *srce)
	{
	int	x;
	BYTE pixel;
	for (x=0; x < copyWidth; x++)
		{
		pixel = *dest++;
		*srce = pixel;
		srce++;
		}
	}

//********************************************************************************************************************************
															     
void	DrawIMAGE( pseudo_info *pseudo, texture_info *texture, int image_no, int xpos, int ypos, signed char box, copyfunctiontype copyfunction )
	{

	BYTE *dest = pseudo->pseudo_start + (ypos * pseudo->pseudo_width) + xpos;
	BYTE *srce = texture->page_start + (texture->page_width*texture->page_height*Image_Pages[image_no] ) +
			( (texture->page_width * Image_Ycoords[image_no] ) + Image_Xcoords[image_no] );
		
	int copyWidth = Min( Image_Widths[image_no],  pseudo->window_width-xpos);
	int copyHigh  = Min( Image_Heights[image_no], pseudo->window_height-ypos);

	if ( copyWidth < 0 || copyHigh < 0 ) return;
		
		if ( box>=0 )
		{
			if ((xpos < Bounding_table[(box)].BoundingBoxLeft) || Bounding_table[(box)].BoundingBoxLeft == -1)
				Bounding_table[(box)].BoundingBoxLeft = (short) xpos;
			if ((ypos < Bounding_table[(box)].BoundingBoxTop) || Bounding_table[(box)].BoundingBoxTop == -1)
				Bounding_table[(box)].BoundingBoxTop = (short) ypos;
		}

	int destAddn  =	pseudo->pseudo_width;
	int srceAddn  =	texture->page_width;

	int y;

	for (y=0; y < copyHigh; y++)
		{
		copyfunction( copyWidth, dest, srce );
		dest+=	destAddn;		
		srce+=	srceAddn;		
		}

			if ( box>=0 )
			{
				if ( ( (xpos+Image_Widths[image_no]) > Bounding_table[(box)].BoundingBoxRight) || 
					Bounding_table[(box)].BoundingBoxRight == -1)
						Bounding_table[(box)].BoundingBoxRight = ( (short) xpos+Image_Widths[image_no] );

				if ( ( (ypos+Image_Heights[image_no]) > Bounding_table[(box)].BoundingBoxBottom) || 
					Bounding_table[(box)].BoundingBoxBottom == -1)
						Bounding_table[(box)].BoundingBoxBottom = ( (short) ypos+Image_Heights[image_no]);
			}

	}

//********************************************************************************************************************************

void	StorePSEUDObuffer( pseudo_info *pseudo, texture_info *texture, int image_no, int xpos, int ypos )
	{

	BYTE *srce = pseudo->pseudo_start + (ypos * pseudo->pseudo_width) + xpos;
	BYTE *dest = texture->page_start + (texture->page_width*texture->page_height*Image_Pages[image_no] ) +
			( (texture->page_width * Image_Ycoords[image_no] ) + Image_Xcoords[image_no] );
		
	int copyWidth = Image_Widths[image_no];
	int copyHigh  = Image_Heights[image_no];

	if ( copyWidth < 0 || copyHigh < 0 ) return;
		
	int srceAddn  =	pseudo->pseudo_width-copyWidth;
	int destAddn  =	texture->page_width-copyWidth;

	int y;

		for (y=0; y < copyHigh; y++)
		{
			int	x;
			BYTE pixel;

			for (x=0; x < copyWidth; x++)
				{
					pixel = *srce++;
					*dest = pixel;
					dest++;
				}

			srce+=	srceAddn;		
			dest+=	destAddn;		
		}
	}

//********************************************************************************************************************************

void	CopyFromBACKtoPSEUDObuffer( pseudo_info *pseudo, pseudo_info *background, int xpos, int ypos, short width, short height )
	{

	BYTE *dest = pseudo->pseudo_start + (ypos * pseudo->pseudo_width) + xpos;
	BYTE *srce = background->pseudo_start + (ypos * background->pseudo_width) + xpos;
		
	int srceAddn  =	background->pseudo_width-width;
	int destAddn  =	pseudo->pseudo_width-width;

	int y;

		for (y=0; y < height; y++)
		{
			int	x;
			BYTE pixel;

			for (x=0; x < width; x++)
				{
					pixel = *srce++;
					*dest = pixel;
					dest++;
				}

			srce+=	srceAddn;		
			dest+=	destAddn;		
		}
	}

//********************************************************************************************************************************

void	CopyDumpListToScreen()
{
	for (short d=0; d<MAX_DUMPS; d++)
	{
		if ( Dump_list[d].DumpFlag!=0 )
		{
			svgacpy( (unsigned char *) EuroPseudoBuffer+((640*Dump_list[d].DumpYpos)+
			Dump_list[d].DumpXpos),
			Dump_list[d].DumpXpos , Dump_list[d].DumpYpos,
			Dump_list[d].DumpWidth , Dump_list[d].DumpHeight,
			640);		
			Dump_list[d].DumpFlag =	0; 
		}
	}

}

//********************************************************************************************************************************

void	DisplayString( int xpos, int ypos, char *string, int font, int colour, signed char box, pseudo_info *pseudo, texture_info *texture )
	{
		int c;
		svalue	=	colour;

		while	( c=*(string++) ) 	
			{
				c =  ASCtoImageTBL[c];
				c+=  font;
			      	DrawIMAGE( pseudo, texture, c, xpos, ypos, box, spriteinccopy );
				xpos+=	(Image_Widths[c])+1;
			}

		NextXposn = xpos;
	}

//********************************************************************************************************************************

int	PixelLengthOfString( char *string, int font )
	{
		int c;
		int	len	=	0;

		while	( c=*(string++) ) 	
		{
	 		c =  	ASCtoImageTBL[c];
		 	c+=	font;
		 	len+=	(Image_Widths[c])+1;
	 	}

	return(len);

	}

//********************************************************************************************************************************

void	AddToDumpList(short X,short Y,short W,short H)
{
	for (short a=0; a<MAX_DUMPS; a++)
	{			
		if (Dump_list[a].DumpFlag==0 )
		{
			Dump_list[a].DumpXpos	=	X;
			Dump_list[a].DumpYpos	=	Y;
			Dump_list[a].DumpWidth	=	W;
			Dump_list[a].DumpHeight	=	H;
			Dump_list[a].DumpFlag   =       1;
			break;
		}
	}
}

//********************************************************************************************************************************

void	ClearDumpList()
{
	for (short c=0; c<MAX_DUMPS; c++)
		Dump_list[c].DumpFlag	=	0;
}

//********************************************************************************************************************************

void 	CreateFilter( BYTE *FilterTable, char fr, char fg, char fb, float mr, float mg, float mb )
	{
	signed short r1,g1,b1,r2,g2,b2;
	signed short x,s,c,l1,l2,d1,d2;
	if ((l1=sqrt(fr*fr+fg*fg+fb*fb))==0) l1=1;
	for (x=0;x<768;x+=3)	 
		{
		l2=sqrt(PaletteBuffer[x]*PaletteBuffer[x]+PaletteBuffer[x+1]*
			PaletteBuffer[x+1]+PaletteBuffer[x+2]*PaletteBuffer[x+2]);
		r1=PaletteBuffer[x]+mr*(fr*l2/l1-PaletteBuffer[x]);
		if (r1<0) r1=0;if (r1>255) r1=255;
		g1=PaletteBuffer[x+1]+mg*(fg*l2/l1-PaletteBuffer[x+1]);
		if (g1<0) g1=0;if (g1>255) g1=255;
		b1=PaletteBuffer[x+2]+mb*(fb*l2/l1-PaletteBuffer[x+2]);
		if (b1<0) b1=0;if (b1>255) b1=255;
		r1=(fr-PaletteBuffer[x])*mr+PaletteBuffer[x];
		g1=(fg-PaletteBuffer[x+1])*mg+PaletteBuffer[x+1];
		b1=(fb-PaletteBuffer[x+2])*mb+PaletteBuffer[x+2];
		d1=128;

		for (s=0;s<768-16*3;s+=3)
			{
		 	r2=(PaletteBuffer[s]-r1);
			g2=(PaletteBuffer[s+1]-g1);
			b2=(PaletteBuffer[s+2]-b1);
			d2=sqrt(r2*r2+g2*g2+b2*b2);
			if (d2<d1) d1=d2,c=s;
			}

		FilterTable[x/3]=c/3;
		}
	}

//********************************************************************************************************************************

void	ControlAnimations()
	{
	signed char BOX;
	int width, height;

		for ( short a=0; a < MAX_ANIMATIONS; a++ )
		{

		BOX	= Animation_table[a].Bounding_box;

			if ( Animation_table[a].StartFrame != -1 )
			{		   
				if ( Animation_table[a].Flags != 0 && BOX != NO_BOX )
				{
	     				width	= Bounding_table[BOX].BoundingBoxRight  - 
 						  Bounding_table[BOX].BoundingBoxLeft;
					height	= Bounding_table[BOX].BoundingBoxBottom - 
			 			  Bounding_table[BOX].BoundingBoxTop;

					CopyFromBACKtoPSEUDObuffer(
							&FrontendPseudoDEFN, &FrontendBackgroundDEFN,
							Bounding_table[BOX].BoundingBoxLeft,
							Bounding_table[BOX].BoundingBoxTop,
							width, height );
					AddToDumpList( 
							(short)Bounding_table[BOX].BoundingBoxLeft,
							(short)Bounding_table[BOX].BoundingBoxTop,
							(short)width, height );
				}

			Animation_table[a].Counter+=	Animation_table[a].AnimationSpeed;
      			
			if ( Animation_table[a].AnimationSpeed > 0 &&
				(Animation_table[a].StartFrame + Animation_table[a].Counter) > Animation_table[a].EndFrame )
			{
				if ( (Animation_table[a].Flags & CONT_ANIM) == CONT_ANIM )
				{
					Animation_table[a].Counter-=	(Animation_table[a].EndFrame-Animation_table[a].StartFrame);
				}
				
				else

				{
					Animation_table[a].Counter		=	0;
					Animation_table[a].AnimationSpeed	=	0;
				}
			}



			if ( Animation_table[a].AnimationSpeed < 0 &&
				(Animation_table[a].StartFrame + Animation_table[a].Counter) < Animation_table[a].StartFrame )

				{
					Animation_table[a].Counter+=	Animation_table[a].EndFrame-Animation_table[a].StartFrame;
				}
				
			if ( Animation_table[a].AnimationSpeed < 0 
				&& Animation_table[a].Counter > 0 
				&& Animation_table[a].Counter + Animation_table[a].AnimationSpeed < 0 
				&& ( (Animation_table[a].Flags & CONT_ANIM) == RUN_ONCE )
  				)
				{
					Animation_table[a].Counter		=	0;
					Animation_table[a].AnimationSpeed	=	0;
				}

			DrawIMAGE( 	&FrontendPseudoDEFN, &FrontendTextureDEFN, 
					((int)(Animation_table[a].StartFrame+Animation_table[a].Counter)),
					Animation_table[a].xposn,
					Animation_table[a].yposn,
					BOX,
					spritecopy );  	

			Animation_table[a].Flags|= 1;

			width	= Image_Widths[( (int) (Animation_table[a].StartFrame+Animation_table[a].Counter) )];
			height	= Image_Heights[( (int) (Animation_table[a].StartFrame+Animation_table[a].Counter) )];

			AddToDumpList( 	(short)Animation_table[a].xposn, 
					(short)Animation_table[a].yposn, 
					(short)width, (short)height );
			}
		}				
	}	

//********************************************************************************************************************************

	int	MenuBitmaps[32]={
		{BIN_MAIN},	{BIN_MAIN},	{BIN_TEAMSET},	{BIN_GRP_FIX}, 
		{BIN_TEAMSEL},	{BIN_EURODRAW},	{BIN_PLYRSTAT},	{BIN_PLYRSET},
		{BIN_TEAMSTAT},	{BIN_VENUEFLY},	{BIN_MODEMINI},	{BIN_NEXTMTCH},
		{BIN_QUALIFY}, 	{BIN_QUARTFIN}, {BIN_SEMIFINL},	{BIN_FINAL}, 
		{BIN_MAIN},	{BIN_MAIN},	{BIN_MAIN},	{BIN_MAIN},    
		{BIN_MAIN}, 	{BIN_MAIN}, 	{BIN_MAIN}, 	{BIN_MAIN}, 
		{BIN_MAIN},	{BIN_MAIN},	{BIN_MAIN},	{BIN_MAIN},    
		{BIN_MAIN}, 	{BIN_MAIN}, 	{BIN_MAIN}, 	{BIN_MAIN}, 
				   };
	int	MenuPalettes[32]={
		{BIN_MAINPAL},	{BIN_MAINPAL},	{BIN_TSETPAL},	{BIN_GFIXPAL},
		{BIN_TSELPAL},	{BIN_DRAWPAL},	{BIN_PSTATPAL},	{BIN_PSETPAL},
		{BIN_TSTATPAL},	{BIN_VNFLYPAL},	{BIN_MDSETPAL},	{BIN_NMTCHPAL},
		{BIN_QUALYPAL},	{BIN_QUTFNPAL},	{BIN_SEMFPAL},	{BIN_FINALPAL},
		{BIN_MAINPAL},	{BIN_MAINPAL},	{BIN_MAINPAL},	{BIN_MAINPAL},
		{BIN_MAINPAL},	{BIN_MAINPAL},	{BIN_MAINPAL},	{BIN_MAINPAL},
		{BIN_MAINPAL},	{BIN_MAINPAL},	{BIN_MAINPAL},	{BIN_MAINPAL},
		{BIN_MAINPAL},	{BIN_MAINPAL},	{BIN_MAINPAL},	{BIN_MAINPAL},
				   };

	int	FormationPalettes[16]={
		{BIN_FBGREEN},	{BIN_FDORAN},	{BIN_FRED},	{BIN_FRED},   
		{BIN_FBBLUE}, 	{BIN_FLBLUE}, 	{BIN_FRED}, 	{BIN_FBORAN},
		{BIN_FBBLUE},  	{BIN_FRED},   	{BIN_FRED}, 	{BIN_FBBLUE}, 
		{BIN_FBBLUE}, 	{BIN_FRED},   	{BIN_FRED}, 	{BIN_FRED},
				   };

	char	LeagueColourOffsets[16]={
		43, 78, 64, 64, 15, 71, 15, 57, 36, 64, 50, 15, 71, 64, 64, 15,
				   };

//********************************************************************************************************************************

void	DisplayBackground( int MENU )
	{
		LoadTexturePage( MenuBitmaps[ MENU ], 	       
				 &EuroDATfile[0], 
				 1, &FrontendTextureDEFN );

		LoadPalette( MenuPalettes[ MENU ],
				 &EuroDATfile[0], 0 );
		LoadPalette( BIN_MOUSEPAL,
				 &EuroDATfile[0], 0 );

		switch ( MENU )
		{
			case( SQUAD_SELECT ):
				LoadPalette( BIN_BUL_PAL+( 8*Team ),
				 &EuroDATfile[0], 16 );
				LoadPalette( FormationPalettes[Team],
				 &EuroDATfile[0], 32 );
				CreateFilter( &FilterBuffer[0], 16, 16, 16, .35, .35, .35 );
				ftable	=	FilterBuffer;
				break;
			case( PLAYER_STATS ):
				LoadPalette( BIN_BUL_PAL+( 8*Team ),
				 &EuroDATfile[0], 16 );
				LoadPalette( FormationPalettes[Team],
				 &EuroDATfile[0], 32 );
				break;

			case( TEAM_SELECT ):
				CreateFilter( &FilterBuffer[0],    40, 54, 60, .8, .8, .8);
				break;

			case( PLAYER_SETUP ):
				LoadPalette( BIN_BUL_PAL+( 8*EUROteamA ),
				 &EuroDATfile[0], 16 );
				LoadPalette( BIN_BUL_PAL+( 8*EUROteamB ),
				 &EuroDATfile[0], 32 );
				break;

			case( TEAM_STATS ):
				LoadPalette( BIN_TBUL_PAL+( 8*EUROstatTeam ),
				 &EuroDATfile[0], 37 );
				LoadPalette( BIN_CBUL_PAL+( 8*EUROstatTeam ),
				 &EuroDATfile[0], 132 );
				break;
		}

		DrawIMAGE(  &FrontendBackgroundDEFN, &FrontendTextureDEFN, BACKGROUNDimge, 0, 0, NO_BOX, straightcopy );
	}				   

//********************************************************************************************************************************

void	Set_palette_to_black()
	{
		for (short i=0;i<256;i++)
		{
			  outp	(0x3c8,i);
			  outp	(0x3c9,0);
			  outp	(0x3c9,0);
			  outp	(0x3c9,0);
		}
		memset( CurrentPalette, 0, 768 );
	}

//********************************************************************************************************************************

short	ControlSlider( slider_info *slider, short xposn, short yposn, short buttons )
	{
		float	offset;

		CopyFromBACKtoPSEUDObuffer(
			&FrontendPseudoDEFN, &FrontendBackgroundDEFN,
			slider->minx-6, slider->miny-9, 
				Image_Widths[SLDR_CURS], slider->maxy-slider->miny+Image_Heights[SLDR_CURS] );

		if ( xposn > (slider->minx-16)
		      && xposn < (slider->maxx+16)
		       && yposn > slider->miny-8
			&& yposn < slider->maxy+8 && buttons != 0 )
			{
			 	if ( yposn < slider->maxy )
				{
					if ( yposn < slider->miny )
						slider->windowposn = 0;					
					else
						slider->windowposn = yposn-slider->miny;
				}

				else
					slider->windowposn = slider->maxy-slider->miny;
			}

	  	DrawIMAGE( &FrontendPseudoDEFN, &FrontendTextureDEFN, SLDR_CURS, 
			(slider->minx-6), ( (slider->windowposn+slider->miny)-9), 
			NO_BOX, spritecopy );  	

		AddToDumpList( (slider->minx-6), (slider->miny-9), 
			Image_Widths[SLDR_CURS], slider->maxy-slider->miny+Image_Heights[SLDR_CURS] );

		offset	= (((float)(slider->elements-slider->page_elements))/ 
			  ((float)(slider->maxy-slider->miny)))* 
			  ((float)slider->windowposn);
		return( (short)offset );
	}

//********************************************************************************************************************************

void	Set_640x480_VideoMode()
	{
		// set the video mode to mode 101 (640x480).

		testVESA		=	0;	
		EuroVideoStatus		=	VESAmode( &EUROvideoMode[0] );
	}

//********************************************************************************************************************************

void	Test_640x480_VideoMode()
	{
		// tests for video mode 101 (640x480).

		testVESA		=	1;	
		EuroVideoStatus		=	VESAmode( &EUROvideoMode[0] );
		if ( EuroVideoStatus == -1 )
		      	printf("þ Video mode unavailable.\n");
		else
		      	printf("þ Video mode initialised.\n");
	}

//********************************************************************************************************************************
//
//	BUTTON HIGHLIGHT CONTROLLER:
//
//	Entry:		BOX		Normal BOX value. 		
//			CHKBOX1		First box to be checked (button box).
//			CHKBOX2		Second box to be checked (text display box).
//   			HIGH		Current highlight value ( -1, 15 or 29 ). A change in HIGH value from previous
//					HIGH value means string is to be reprinted.
//			BUTHANDLE	Handle variable used for this selection button.
//					
//					
//					
//	Returns:	New Highlight value.
//
//
//
//

#define	textxoff	52
#define	textyoff	8

char	ControlOptionHighlight( signed char BOX, signed char CHKBOX1, signed char CHKBOX2, 
				 char HIGH, short BUTHANDLE, short TEXT )
	{
 		char	PAL	=	-1;

 		if ( BOX == CHKBOX1 || BOX == CHKBOX2 )
 			PAL	=	OVERRIDEpal1;
 		else
 			PAL	=	OVERRIDEpal2;

 		if ( PAL != HIGH )
 		{
 			CopyFromBACKtoPSEUDObuffer( &FrontendPseudoDEFN, &FrontendBackgroundDEFN,
 				Bounding_table[ CHKBOX1 ].BoundingBoxRight,
				Animation_table[BUTHANDLE].yposn+textyoff,
				639-Bounding_table[ CHKBOX1 ].BoundingBoxRight, 28 );

	 		DisplayString(  
				Animation_table[BUTHANDLE].xposn+textxoff,
				Animation_table[BUTHANDLE].yposn+textyoff,
				GetTEXT ( TEXT ),
				MEDIUM_FONT, (int)PAL, CHKBOX2, &FrontendPseudoDEFN, &FrontendTextureDEFN  );

 			AddToDumpList( 
 				Bounding_table[ CHKBOX1 ].BoundingBoxRight,
				Animation_table[BUTHANDLE].yposn+textyoff,
				639-Bounding_table[ CHKBOX1 ].BoundingBoxRight, 28 );
 
		}

	Bounding_table[ CHKBOX2 ].BoundingBoxLeft =
		Bounding_table[ CHKBOX1 ].BoundingBoxRight;

	OVERRIDEpal1	=	15;
	OVERRIDEpal2	=	29;
	HIGH		= 	PAL;
	return(HIGH);
	}

//********************************************************************************************************************************

char	*LowerCaseString( char *string )
	{
		char	Searchlen	=	strlen(&string[0]);

		for ( char x=1; x<Searchlen ; x++ )
		{
			if ( *(string+(x-1))!=' ' )
				*(string+x) = ToLower[*(string+x)];
		}

	return(string);		
	}

//********************************************************************************************************************************

char	*GetTEAMname( char team, char maxlen )
	{
		char	*Name		=	GetTEXT( TEAM_NMES+team );
		char	Searchlen	=	strlen(&Name[0]);
		char	NAMEoffset	=	0;

		for ( char x=0; x<Searchlen ; x++ )
			{StringBuffer[x] 	= * (Name+x);}
		StringBuffer[x] 	= 0;

		if ( maxlen!=0 && Searchlen > maxlen )
			{
				StringBuffer[maxlen-1] = '.';
				StringBuffer[maxlen] = 0;
			}

	return	( &StringBuffer[0] );
	}

//********************************************************************************************************************************

short	GetTemplete( char *buf, short soff )
	{
		char	Toffset	= 0;					

		if ( buf[soff] == '?' )
		{
			soff++;
			
			while ( buf[soff]!=' ' )
			{
				Templete[Toffset] = buf[soff];
				if (Toffset<127)
					Toffset++;
				soff++;
			}

			Templete[Toffset] = 0;
			strupr( Templete );			
		}

	return(soff);
   	}

//********************************************************************************************************************************

char	*StringTemplete( short text, char flagA )
	{
		short soff 	= 0;		// input string.
		char *string 	= GetTEXT( text );
		char Build[128];
		BuildBuffer[0]	= 0;
		
		while ( string[soff]!=0 )
		{
			Build[0] = 0;

			if ( string[soff] == '?' )
			{
				soff = GetTemplete( &string[0], soff );				

				if ( !strcmp( Templete, "WINTEAM") )
					strcpy( Build, LowerCaseString(GetTEAMname( Results[flagA].WinningTeam, 11)));

				if ( !strcmp( Templete, "WINPENS") )
				{
					if ( Results[flagA].HomePens > Results[flagA].AwayPens )
				       		itoa( (int)Results[flagA].HomePens, Build, 10);
					else				      	
				       		itoa( (int)Results[flagA].AwayPens, Build, 10);
				}

				if ( !strcmp( Templete, "LOSEPENS") )
				{
					if ( Results[flagA].HomePens < Results[flagA].AwayPens )
				       		itoa( (int)Results[flagA].HomePens, Build, 10);
					else						
				       		itoa( (int)Results[flagA].AwayPens, Build, 10);
				}

				strcat( BuildBuffer, Build);
			}									
			
			else

			{
				Build[0] = * (string+soff);
				Build[1] = 0;
				strcat( BuildBuffer, Build);
				soff++;
			}

		}

	return( &BuildBuffer[0] );
	}

//********************************************************************************************************************************

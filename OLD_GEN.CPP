#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#include "euro.equ"
#include "euro_def.h"
#include "euro_var.h"
#include "euro_grf.h"
#include "euro_dsk.h"
#include "euro_fix.h"
#include "euro_sel.h"
#include "euro_inf.h"
#include "euro_cnt.h"
#include "euro_usr.h"

void	DisplayPositionLabels();
void	DisplaySquad();
void	DisplayFormation( char );
void	ClearFormationMarkers();
short	AddAnimation( int, int, float, float, float, signed char, signed char );
//void	DisplayCountrySelectImages();

#include "defines.h"
	extern	"C"	short	MouseBUTTONS;
	extern	int 	MouseFlags;
	extern	"C"	short	PaletteFlag;
	extern  int 	new_menu;
	extern	"C"	short	MouseDeBOUNCE;
	extern 	"C"	short MouseXminimum;	   	
	extern 	"C"	short MouseYminimum;	   	

//********************************************************************************************************************************

char	*GetTEXT( short StringNumber )
{
	return( (char *)Text[ StringNumber ] );
}

//********************************************************************************************************************************

char	*GetTEAMname( char team, char maxlen )
	{
		char	*Name		=	GetTEXT( COUNTRY_NAMES+team );
		char	Searchlen	=	strlen(&Name[0]);
		char	NAMEoffset	=	0;

		for ( char x=0; x<Searchlen ; x++ )
			{NameBuffer[x] 	= * (Name+x);}
		NameBuffer[x] 	= 0;

		if ( maxlen!=0 && Searchlen > maxlen )
			{
				NameBuffer[maxlen-1] = '.';
				NameBuffer[maxlen] = 0;
			}

	return	( &NameBuffer[0] );

	}



//********************************************************************************************************************************

char	*GetPLAYERSname( char player, char team, char format )
	{

		char	*Search		=	GetTEXT( ( PLAYER_NAMES+(team*20 )+player) );
		char	NAMEoffset	=	0;
		char	Searchlen	=	strlen(&Search[0]);
		
		if ( format == FULL_NAME )
		{	
			for ( char x=0; x < Searchlen ; x++ )
				{NameBuffer[x]	= *(Search+x);}
			NameBuffer[x]	= 0;
		}



		if ( format == INITIAL_SURNAME )
		{	
			// *** Get players initials ***
		
			for ( char x=0; x < Searchlen ; x++ )
				{
//					if ( ( *(Search+x) >= 'A' && *(Search+x) <='Z') && 
//						( *(Search+(x+1)) >= 'a' && *(Search+(x+1)) <='z') && NAMEoffset < (NAME_BUFFER_LEN-3) ) 

					if ( IsUpper[ *(Search+x) ] == up && 
					     IsUpper[ *(Search+(x+1)) ] == lw && 
						NAMEoffset < (NAME_BUFFER_LEN-3) ) 
					{
						NameBuffer[NAMEoffset] 	= *(Search+x);
						NAMEoffset++;
		
						if ((*(Search+x))=='-')
							NameBuffer[NAMEoffset] 	= '-';
						else									
							NameBuffer[NAMEoffset] 	= '.';
		
						NameBuffer[NAMEoffset+1] 	= 32;
						NAMEoffset+=	2;
					}
		
					if ((*(Search+x))=='-' && NAMEoffset >1 )
					{
							NameBuffer[NAMEoffset-2] 	= '-';
							NAMEoffset--;
					}
				}	
		}
		
		if ( format == INITIAL_SURNAME || format == SURNAME )
		{	
		
			// *** Get players surname ***
		
			for ( char y=0; y < Searchlen ; y++ )
				{
//					if ( ( *(Search+y) >= 'A' && *(Search+y) <='Z') && 
//						( *(Search+(y+1)) >= 'A' && *(Search+(y+1)) <='Z') && NAMEoffset < (NAME_BUFFER_LEN-3) ) 

					if ( IsUpper[ *(Search+y) ] == up && 
					     IsUpper[ *(Search+(y+1)) ] == up && 
						NAMEoffset < (NAME_BUFFER_LEN-3) ) 

					{
						NameBuffer[NAMEoffset] 	= *(Search+y);
		
//						if ( (*(Search+(y-1)) >= 'A' && *(Search+(y-1)) <='Z' && y>0) &&
//							(NameBuffer[NAMEoffset-1]!='c' || NameBuffer[NAMEoffset-2]!='M' && NAMEoffset>1 ) 
//									 ) 

						if ( (IsUpper[ *(Search+(y-1) ) ] == up && y>0) &&
							(NameBuffer[NAMEoffset-1]!='c' || NameBuffer[NAMEoffset-2]!='M' && NAMEoffset>1 ) )
							NameBuffer[NAMEoffset]+=	32;
						NAMEoffset++;
					}
		
					else
					
//					if ( ( *(Search+y) >= 'A' && *(Search+y) <='Z') && 
//						( *(Search+(y-1)) >= 'A' && *(Search+(y-1)) <='Z') && NAMEoffset < (NAME_BUFFER_LEN-3) && y>0 ) 

						if ( IsUpper[ *(Search+y) ] == up && 
						     IsUpper[ *(Search+(y-1)) ] == up && 
							NAMEoffset < (NAME_BUFFER_LEN-3) && y>0 ) 
						{
							NameBuffer[NAMEoffset] 	= *(Search+y);
		
//							if ( *(Search+(y-1)) >= 'A' && *(Search+(y-1)) <='Z' && y>0 ) 

							if ( IsUpper[ *(Search+(y-1)) ] == up && y>0 )
								NameBuffer[NAMEoffset]+=	32;
		
							NAMEoffset++;
					
				    			if ( (*(Search+(y+1)))==' ')
								{
								NameBuffer[NAMEoffset] 	= 32;
								NAMEoffset++;
								}
						}
				}	

			NameBuffer[NAMEoffset]	=	0;	// end of line.
		}

		return	( &NameBuffer[0] );
	}

//********************************************************************************************************************************

void	DisplayString( int xpos, int ypos, char *string, int font, int colour, signed char box, pseudo_info *pseudo, texture_info *texture )
	{
		int c;
		svalue	=	colour;

		while	( c=*(string++) ) 	
			{
				if ( c < 127 )
					c-=	32;
				else
		 			if ( c < 155 )
						c-=	33;
					else
	 					if ( c < 166 )
							c-=	38;
						else
		 					if ( c == 225 )
								c-=	97;
							else
			 					if ( c == 237 )
					 				c-=	108;
				c+=	font;

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
				if ( c < 127 )
					c-=	32;
				else
		 			if ( c < 155 )
						c-=	33;
					else
	 					if ( c < 166 )
							c-=	38;
						else
		 					if ( c == 225 )
								c-=	97;
							else
			 					if ( c == 237 )
					 				c-=	108;
				c+=	font;
				len+=	(Image_Widths[c])+1;
			}

	return(len);

	}

//********************************************************************************************************************************

void InitialiseMenuPage( char MENU )
	{
		switch ( MENU )
		{
			case( SQUAD_SELECT ):
				LoadTactics( ((int)FormationInfo[Team]), &EuroDATfile[0], &TeamTactics[0][0][0] );
				DisplaySquad();
				DisplayFormation( NULL );
				DisplayPositionLabels();
				MarkPlayer		=	-1;
				SquadBuffer1yposn	=	-1;
				QuestionHandle		=	 AddAnimation( 488, 16, 
								 ( (float)QUESTION_MARK ), ( (float)QUESTION_MARK+19.1 ),
								 0.40, QUESTION_BOX, CONT_ANIM );
				FormationHandle		=	 AddAnimation( NameBarXposn-16, 426,
								 ( (float)WHT_BLUE_BUTTON ), ( (float)WHT_BLUE_BUTTON+11.9 ),
								 0.0, FORMATION_BOX, RUN_ONCE );
				ReturnSqdHandle		=	 AddAnimation( 308, 426,
								 ( (float)WHT_BLUE_BUTTON ), ( (float)WHT_BLUE_BUTTON+11.9 ),
								 0.0, RETURN_SQUAD_BOX, RUN_ONCE );
				ViewTeamHandle		=	 AddAnimation( NameBarXposn-16, 106,
								 ( (float)WHT_BLUE_BUTTON ), ( (float)WHT_BLUE_BUTTON+11.9 ),
								 0.0, OPPONENT_TEAM_BOX, RUN_ONCE );
				break;

			case( GROUP_FIXTURES ):
				RedrawHandle		=	 AddAnimation( 509, 181, 
								 ( (float)WHT_BLUE_BUTTON ), ( (float)WHT_BLUE_BUTTON+11.9 ),
								 0.0, REDRAW_BOX, CONT_ANIM );
				break;

			case( TEAM_SELECT ):
				ClickBOX		=	 NO_BOX;
				PlayerSetupHandle 	=	 AddAnimation( 446, 180, 
								 ( (float)WHT_BLUE_BUTTON ), ( (float)WHT_BLUE_BUTTON+11.9 ),
								 0.0, PLAYER_SETUP_BOX, CONT_ANIM );
				FormationSetupHandle 	=	 AddAnimation( 446, 228, 
								 ( (float)WHT_BLUE_BUTTON ), ( (float)WHT_BLUE_BUTTON+11.9 ),
								 0.0, FORMATION_SETUP_BOX, CONT_ANIM );
				SelectionSpeed		=	0;
				SelectionFlag		=	-1;
				SelectionAim		=	AimTBL[EUROteamA];
				SelectionCounter	=	((float)SelectionAim)*4;
				DisplayGameType( EUROgameType );
				DisplayCountrySelectImages();
				DoFriendlyTeamSelection();
				break;

			case( EURO_REDRAW ):
				DisplayGroupHeadings();
				EuroDrawHandle		=	 AddAnimation( 179, 234, 
								 ( (float)EURO_DRAW_ANIM ), ( (float)EURO_DRAW_ANIM+55.0 ),
								 0.40, QUESTION_BOX, CONT_ANIM );
				EuroReDrawCounter	=	 30.0;
				EuroReDrawFlag		=	-1;
				break;

			case( PLAYER_STATS ):
				DisplaySquad();
				DisplayPositionLabels();
				QuestionHandle		=	 AddAnimation( 488, 16, 
								 ( (float)QUESTION_MARK ), ( (float)QUESTION_MARK+19.1 ),
								 0.40, QUESTION_BOX, CONT_ANIM );
				ReturnStatHandle	=	 AddAnimation( 308, 416,
								 ( (float)WHT_BLUE_BUTTON ), ( (float)WHT_BLUE_BUTTON+11.9 ),
								 0.0, RETURN_PSTATS_BOX, CONT_ANIM );
				DisplayPlayerStats();
				break;

			case( PLAYER_SETUP ):
				TeamSelectHandle 	=	 AddAnimation( 516, 434, 
								 ( (float)BLUE_BUTTON ), ( (float)WHT_BLUE_BUTTON+11.9 ),
								 0.0, TEAM_SELECT_BOX, CONT_ANIM );
				DisplayMatchTeam( EUROteamA, 87,  0,  16 );
				DisplayMatchTeam( EUROteamB, 352, 12, 32 );
				DisplayUserInfo(EUROplyrSetup);
				break;
				
			case( TEAM_STATS ):
				ReturnTeamHandle     	=	 AddAnimation( 512, 426,
								 ( (float)BLUE_BUTTON ), ( (float)WHT_BLUE_BUTTON+11.9 ),
								 0.0, RETURN_TSTATS_BOX, CONT_ANIM );
				ViewTeamHandle		=	 AddAnimation( NameBarXposn-16, 106,
								 ( (float)WHT_BLUE_BUTTON ), ( (float)WHT_BLUE_BUTTON+11.9 ),
								 0.0, OPPONENT_TEAM_BOX, RUN_ONCE );
				break;
		}

		SetupMouseLimits( 0, 626, 1, 452 );
	}

//********************************************************************************************************************************

void	OverlayStaticBackgroundImages( char MENU )
	{
		int	width;
		
		switch ( MENU )
		{
			case( SQUAD_SELECT ):

				DrawIMAGE( &FrontendBackgroundDEFN, &FrontendTextureDEFN, 
					   LION_KITS+Team, 550, 2, NO_BOX, spritecopy );  	
				width	   =	PixelLengthOfString( GetTEAMname( Team, 0 ),
									LARGE_FONT);
				Image_Widths[NAMEBAR_LEFT]	=	Image_Widths[NAMEBAR_RIGHT]+width;

				DrawIMAGE( &FrontendBackgroundDEFN, &FrontendTextureDEFN, 
					   NAMEBAR_LEFT, NameBarXposn, 
					   106, NO_BOX, spritecopy ); 
				DrawIMAGE( &FrontendBackgroundDEFN, &FrontendTextureDEFN, 
					   NAMEBAR_RIGHT, NameBarXposn+Image_Widths[NAMEBAR_LEFT], 
					   106, NO_BOX, spritecopy );    

				Image_Widths[NAMEBAR_LEFT]	=	FORMATION_BAR_WIDTH;

				DrawIMAGE( &FrontendBackgroundDEFN, &FrontendTextureDEFN, 
					   NAMEBAR_LEFT, NameBarXposn, 
					   426, NO_BOX, spritecopy );  
				DrawIMAGE( &FrontendBackgroundDEFN, &FrontendTextureDEFN, 
					   NAMEBAR_RIGHT, NameBarXposn+Image_Widths[NAMEBAR_LEFT], 
					   426, NO_BOX, spritecopy );  
				DisplayString( NameBarXposn+Image_Widths[NAMEBAR_RIGHT], 110,
			   	   	GetTEXT(Team+COUNTRY_NAMES),
					LARGE_FONT, 24, TEAM_BOX, &FrontendBackgroundDEFN, &FrontendTextureDEFN  );
				break;


			case( GROUP_FIXTURES ):
				CalculateLeagueTables();
				DisplayLeagueTables();
				DisplayLeagueFixtures( MatchNumber );
				DisplayVersusList();
				break;

			case( TEAM_SELECT ):
		  		DisplayLowerSelectionPanel( EUROgameType );		
				DisplayCountrySelectImages();
		      		ReadData( BIN_DRAWPAL, &EuroDATfile[0], &SparePaletteBuffer[0] );
				memcpy( &PaletteBuffer[44*3], &SparePaletteBuffer[ (LeagueColourOffsets[EUROteamA]*3)+3 ], 7*3 );
				memcpy( &PaletteBuffer[51*3], &SparePaletteBuffer[ (LeagueColourOffsets[EUROteamB]*3)+3 ], 7*3 );
				break;

			case( PLAYER_STATS ):
				DrawIMAGE( &FrontendBackgroundDEFN, &FrontendTextureDEFN, 
					   LION_KITS+Team, 550, 2, NO_BOX, spritecopy );  	
				break;
				
			case( PLAYER_SETUP ):

				EUROnoOfMatchPlyrs	=	2;
				DrawIMAGE( &FrontendBackgroundDEFN, &FrontendTextureDEFN, 
					   LION_KITS+EUROteamA, 192, 240, NO_BOX, spritecopy );  	
				svalue	=	16;
				pmin	=	16;
				pmax	=	32;
				DrawIMAGE( &FrontendBackgroundDEFN, &FrontendTextureDEFN, 
					   LION_KITS+EUROteamB, 456, 240, NO_BOX, spriteareainccopy );  	
				DisplayUserLabels(EUROplyrSetup);
				break;
								
			case( TEAM_STATS ):
				width	   =	PixelLengthOfString( GetTEAMname( EUROstatTeam, 0 ),
									LARGE_FONT);
				Image_Widths[TSTAT_NAMEBAR_LEFT] =	Image_Widths[TSTAT_NAMEBAR_RIGHT]+width;

				DrawIMAGE( &FrontendBackgroundDEFN, &FrontendTextureDEFN, 
					   TSTAT_NAMEBAR_LEFT, NameBarXposn, 
					   106, NO_BOX, spritecopy ); 
				DrawIMAGE( &FrontendBackgroundDEFN, &FrontendTextureDEFN, 
					   TSTAT_NAMEBAR_RIGHT, NameBarXposn+Image_Widths[TSTAT_NAMEBAR_LEFT], 
					   106, NO_BOX, spritecopy );    
				DisplayString( NameBarXposn+Image_Widths[TSTAT_NAMEBAR_RIGHT], 110,
			   	   	GetTEXT(EUROstatTeam+COUNTRY_NAMES),
					LARGE_FONT, 36, NO_BOX, &FrontendBackgroundDEFN, &FrontendTextureDEFN  );

				DrawIMAGE( &FrontendBackgroundDEFN, &FrontendTextureDEFN, 
					   BIG_COUNTRY_STAT_IMG+EUROstatTeam,
					   TSTATCountryPosnDEFN[EUROstatTeam].xposn,
					   TSTATCountryPosnDEFN[EUROstatTeam].yposn,
					   NO_BOX, spritecopy );    
				DisplayTeamStats();
				break;
		}
	}

//********************************************************************************************************************************

void	SetupExtraTexturePages( int MENU )
	{
		switch ( MENU )
		{
			case( SQUAD_SELECT ):
				LoadTexturePage( BIN_PAGE2,
				 &EuroDATfile[0],
				 2, &FrontendTextureDEFN );
				LoadTexturePage( BIN_PAGE3,
				 &EuroDATfile[0],
				 3, &FrontendTextureDEFN );
					break;

			case( TEAM_SELECT ):
				LoadTexturePage( BIN_PAGE4,
				 &EuroDATfile[0],
				 2, &FrontendTextureDEFN );
				LoadTexturePage( BIN_PAGE5,
				 &EuroDATfile[0],
				 3, &FrontendTextureDEFN );
				LoadTexturePage( BIN_PAGE6,
				 &EuroDATfile[0],
				 4, &FrontendTextureDEFN );
				LoadTexturePage( BIN_PAGE7,
				 &EuroDATfile[0],
				 5, &FrontendTextureDEFN );
				LoadTexturePage( BIN_PAGE8,
				 &EuroDATfile[0],
				 6, &FrontendTextureDEFN );
				LoadTexturePage( BIN_PAGE9,
				 &EuroDATfile[0],
				 7, &FrontendTextureDEFN );
					break;

			case( EURO_REDRAW ):
				LoadTexturePage( BIN_PAGE10,
				 &EuroDATfile[0],
				 2, &FrontendTextureDEFN );
				LoadTexturePage( BIN_PAGE11,
				 &EuroDATfile[0],
				 3, &FrontendTextureDEFN );
				LoadTexturePage( BIN_PAGE12,
				 &EuroDATfile[0],
				 4, &FrontendTextureDEFN );
					break;

			case( PLAYER_STATS ):
				LoadTexturePage( BIN_PAGE2,
				 &EuroDATfile[0],
				 2, &FrontendTextureDEFN );
				LoadTexturePage( BIN_PAGE13,
				 &EuroDATfile[0],
				 3, &FrontendTextureDEFN );
					break;

			case( PLAYER_SETUP ):
				LoadTexturePage( BIN_PAGE13,
				 &EuroDATfile[0],
				 3, &FrontendTextureDEFN );
					break;

			case( TEAM_STATS ):
				LoadTexturePage( BIN_PAGE14,
				 &EuroDATfile[0],
				 4, &FrontendTextureDEFN );
				LoadTexturePage( BIN_PAGE15,
				 &EuroDATfile[0],
				 5, &FrontendTextureDEFN );
				LoadTexturePage( BIN_PAGE16,
				 &EuroDATfile[0],
				 6, &FrontendTextureDEFN );
					break;
		}
	}

//********************************************************************************************************************************

void	__far EUROinterupt(void)

	{

	float	red, green, blue;

		if ( LogicState == PALETTE_FADEUP )
		{
			if ( FadeCounter < 1 || FadeCounter > FADE_COUNTER )
			{
				float		*a;
				BYTE 		*Palette;	
				a		=	&DivisionTable[0];
				Palette		=	&PaletteBuffer[0];

				FadeCounter  	=  	FADE_COUNTER;

				for ( int c=0; c < 256; c++ )
				{
					red		=	(*(Palette++));		
					green		=	(*(Palette++));		
					blue		=	(*(Palette++));		
					(*(a++))	=	red / FADE_COUNTER;
					(*(a++))	=	green / FADE_COUNTER;
					(*(a++))	=	blue / FADE_COUNTER;
				}

				memset( CurrentPalette, 0, 768 );
			}
	
			float	*a;
			float	*b;
			BYTE 	*Palette;	
		
			a		=	&CurrentPalette[0];
			b		=	&DivisionTable[0];

			for ( int c=0; c < 256; c++ )
			{
				red		=	(float) (*(a)) + (*(b++));
				(*(a++))	=	red;
				green		=	(float) (*(a)) + (*(b++));
				(*(a++))	=	green;
				blue		=	(float) (*(a)) + (*(b++));
				(*(a++))	=	blue;
				outp	( 0x3c8, c );
				outp    ( 0x3c9, (BYTE) red );
				outp    ( 0x3c9, (BYTE) green );
				outp    ( 0x3c9, (BYTE) blue );
			}
		
			FadeCounter--;
	
			if ( FadeCounter < 1 ) 
			{	      
				Palette		=	&PaletteBuffer[0];
				for ( int c=0; c < 256; c++ )
			   		{
						outp	( 0x3c8, c );
						outp    ( 0x3c9, (*( Palette++ ) ) );
						outp    ( 0x3c9, (*( Palette++ ) ) );
						outp    ( 0x3c9, (*( Palette++ ) ) );
					}

				float		*a;
				BYTE 		*Palette;	
				a		=	&CurrentPalette[0];
				Palette		=	&PaletteBuffer[0];

				for ( int d=0; d < 256; d++ )
					{
						red		=	(*(Palette++));		
						green		=	(*(Palette++));		
						blue		=	(*(Palette++));		
						(*(a++))	=	red;
						(*(a++))	=	green;
						(*(a++))	=	blue;
					}

				LogicState = RUN_FRONTEND;
				FadeCounter = 0;
			}
		}

		else

		if ( LogicState == PALETTE_FADEDOWN )
		{
			if ( FadeCounter < 1 || FadeCounter > FADE_COUNTER )
			{		      
				float		*a;
				float 		*Palette;	
				a		=	&DivisionTable[0];
				Palette		=	&CurrentPalette[0];

				FadeCounter  	=  	FADE_COUNTER;

				for ( int c=0; c < 256; c++ )
				{
					red		=	(*(Palette++));		
					green		=	(*(Palette++));		
					blue		=	(*(Palette++));		
					(*(a++))	=	red / FADE_COUNTER;
					(*(a++))	=	green / FADE_COUNTER;
					(*(a++))	=	blue / FADE_COUNTER;
				}
			}

			float	*a;
			float	*b;
			BYTE 	*Palette;	
		
			a		=	&CurrentPalette[0];
			b		=	&DivisionTable[0];

			for ( int c=0; c < 256; c++ )
			{
				red		=	(float) (*(a)) - (*(b++));
				(*(a++))	=	red;
				green		=	(float) (*(a)) - (*(b++));
				(*(a++))	=	green;
				blue		=	(float) (*(a)) - (*(b++));
				(*(a++))	=	blue;
				outp	( 0x3c8, c );
				outp    ( 0x3c9, (BYTE) red );
				outp    ( 0x3c9, (BYTE) green );
				outp    ( 0x3c9, (BYTE) blue );
			}
		
			FadeCounter--;
	
			if ( FadeCounter < 1 ) 
			{
				for ( int c=0; c < 256; c++ )
		   		{
					outp	( 0x3c8, c );
					outp    ( 0x3c9, 0 );
					outp    ( 0x3c9, 0 );
					outp    ( 0x3c9, 0 );
				}

				memset( CurrentPalette, 0, 768 );
				FadeCounter 	= 0;
				LogicState 	= BLANK_SCREEN;
				Finish++;
			}
		}

		if ( LogicState == RUN_FRONTEND )
				SelectFrame+=	.55;
		else
				SelectFrame =	0;
	}


//********************************************************************************************************************************

void	ResetAnimations()
	{
		for ( short a=0; a < MAX_ANIMATIONS; a++ )
		{
			Animation_table[a].StartFrame		=	-1;
			Animation_table[a].EndFrame		=	-1;
			Animation_table[a].Counter		=	0;
			Animation_table[a].AnimationSpeed	=	0;
			Animation_table[a].Bounding_box		=	0;
			Animation_table[a].Flags		=	0;
			Animation_table[a].xposn		=	0;
			Animation_table[a].yposn		=	0;
		}				
	}	

//********************************************************************************************************************************

short	AddAnimation( int xposn, int yposn, float StartFrame, float EndFrame, float Speed, signed char Box, signed char Flags )
	{
		short	handle	=	0;


		for ( short a=0; a < MAX_ANIMATIONS; a++ )
		{			
			if ( Animation_table[a].StartFrame==-1 )
			{
				Animation_table[a].StartFrame		=	StartFrame;
				Animation_table[a].EndFrame		=	EndFrame;
				Animation_table[a].AnimationSpeed	=	Speed;
				Animation_table[a].Bounding_box		=	Box;
				Animation_table[a].Flags		=	Flags;
				Animation_table[a].xposn		=	xposn;
				Animation_table[a].yposn		=	yposn;
				handle					=	a;
				break;
			 }
		}
	 	return(handle);
	}

//********************************************************************************************************************************

void	ResetBoundingBoxes()
	{
		for ( short b=0; b < MAX_BOUNDING_BOXES; b++ )
		{
			Bounding_table[b].BoundingBoxLeft	=	-1;
			Bounding_table[b].BoundingBoxRight	=	-1;
			Bounding_table[b].BoundingBoxTop	=	-1;
			Bounding_table[b].BoundingBoxBottom	=	-1;
		}				
	}	

//********************************************************************************************************************************

signed char GetBoundingBox( short xposn, short yposn )
	{

	signed char box	=	-1;

		for ( int b=0; b < MAX_BOUNDING_BOXES; b++ )
		{
		       	if ( xposn > Bounding_table[b].BoundingBoxLeft
			      && xposn < Bounding_table[b].BoundingBoxRight
		       	       && yposn > Bounding_table[b].BoundingBoxTop
			        && yposn < Bounding_table[b].BoundingBoxBottom)
				    	
					box	=	b;
		}

		return(box);
	}

			     
//********************************************************************************************************************************

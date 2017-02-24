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
#include "euro_sel.h"
#include "euro_int.h"

#include "defines.h"

//********************************************************************************************************************************

void	DisplayPlayerStats()
	{
		char	NumberString[5];
		short	stat;

		short	Plyr	  =	(Team*20)+ViewPlyrStats;
		short	PlyrIndex =	SquadInfo[ Plyr ];
		short	ActPlyrIx =	(Team*20)+PlyrIndex;		

		short	tpace	  =	Pace[ ActPlyrIx ]     - (50.0 / 100.0)*(100-Fitness[ ActPlyrIx ]);
		short	tacc	  =	Accuracy[ ActPlyrIx ] - (10.0 / 100.0)*(100-Fitness[ ActPlyrIx ]);
		short	tflair	  =	Flair[ ActPlyrIx ]    - (10.0 / 100.0)*(100-Fitness[ ActPlyrIx ]);
		short	tstam	  =	Stamina[ ActPlyrIx ]  - (50.0 / 100.0)*(100-Fitness[ ActPlyrIx ]);
		short	tpow	  =	Power[ ActPlyrIx ]    - (50.0 / 100.0)*(100-Fitness[ ActPlyrIx ]);


	// *** PLAYERS SQUAD FORMATION BALL ***

		DrawIMAGE( &FrontendPseudoDEFN, &FrontendTextureDEFN, 
			   ( SQUD_BALS + PlyrIndex ),
			   10, 104, NO_BOX,
			   spritecopy );  	// formation lotto balls.


	// *** PLAYERS NAME ***

		DisplayString( 44, 107,
		     ( GetPLAYERSname( SquadInfo[ PlyrIndex ], Team, FULL_NAME )) , 
			MEDIUM_FONT, 48, NO_BOX, &FrontendPseudoDEFN, &FrontendTextureDEFN  );


	// *** PLAYERS AGE ***

		DisplayString( 43, 136,
		     ( GetTEXT( PINF_LBLS+Age )) , 
			SMALL_FONT, 55, NO_BOX, &FrontendPseudoDEFN, &FrontendTextureDEFN  );

		char	age	=	EUROyear-DOByear[ ActPlyrIx ];
		
		if ( ( DOBmonth[ ActPlyrIx ] < EUROmonth ) || ( DOBmonth[ ActPlyrIx ] == EUROmonth && DOBday[ ActPlyrIx ] < EUROday ) )
			age--;
		
		itoa( age, NumberString, 10);

		DisplayString( NextXposn+10, 136,
			(char *)NumberString,
			SMALL_FONT, 62, NO_BOX, &FrontendPseudoDEFN, &FrontendTextureDEFN  );

	// *** PLAYERS CLUB ***


		DisplayString( 43, 158,
		     ( GetTEXT( PINF_LBLS+Club )) , 
			SMALL_FONT, 55, NO_BOX, &FrontendPseudoDEFN, &FrontendTextureDEFN  );
		
		DisplayString( NextXposn+10, 158,
			(char *)Clubnames[ ActPlyrIx ],
			SMALL_FONT, 62, NO_BOX, &FrontendPseudoDEFN, &FrontendTextureDEFN  );

	// *** PLAYERS CAPS ***

		itoa( PlayersCaps[ ActPlyrIx ] , NumberString, 10);

		DisplayString( 43, 180,
		     ( GetTEXT( PINF_LBLS+Caps )) , 
			SMALL_FONT, 55, NO_BOX, &FrontendPseudoDEFN, &FrontendTextureDEFN  );
		
		DisplayString( NextXposn+10, 180,
			(char *)NumberString,
			SMALL_FONT, 62, NO_BOX, &FrontendPseudoDEFN, &FrontendTextureDEFN  );

	// *** PLAYERS GOALS ***

		itoa( PlayersGoals[ ActPlyrIx ] , NumberString, 10);

		DisplayString( 43, 202,
		     ( GetTEXT( PINF_LBLS+Goals )) , 
			SMALL_FONT, 55, NO_BOX, &FrontendPseudoDEFN, &FrontendTextureDEFN  );

		DisplayString( NextXposn+10, 202,
			(char *)NumberString,
			SMALL_FONT, 62, NO_BOX, &FrontendPseudoDEFN, &FrontendTextureDEFN  );

	// *** PLAYERS POSITION ***

		DisplayString( 43, 224,
		     ( GetTEXT( PINF_LBLS+Posn )) , 
			SMALL_FONT, 55, NO_BOX, &FrontendPseudoDEFN, &FrontendTextureDEFN  );

		DisplayString( NextXposn+10, 224,
		     	( GetTEXT( POSN_LBLE+PlayerPosns[ ActPlyrIx ] )), 
			SMALL_FONT, 62, NO_BOX, &FrontendPseudoDEFN, &FrontendTextureDEFN  );


	// *** PLAYERS SPEED *** 	> 75% pace + 25% stamina

		DisplayString( 43, 278,
		     ( GetTEXT( STAT_LBLS+Spd )) , 
			SMALL_FONT, 48, NO_BOX, &FrontendPseudoDEFN, &FrontendTextureDEFN  );

		stat	=     	((75*Pace[ ActPlyrIx ])/100) +
				((25*Stamina[ ActPlyrIx ])/100);
					
		Image_Widths[PURP_FILL+Dull] = stat*1.14;

		if ( stat > 0 )
			DrawIMAGE( &FrontendPseudoDEFN, &FrontendTextureDEFN, 
			   PURP_FILL+Dull, 122, 281, NO_BOX, straightcopy );
		
		stat	=     	((75*tpace)/100) +
				((25*tstam)/100);

		Image_Widths[PURP_FILL+Bright] = stat*1.14;
		
		if ( stat > 0 )
			DrawIMAGE( &FrontendPseudoDEFN, &FrontendTextureDEFN, 
			   PURP_FILL+Bright, 122, 281, NO_BOX, straightcopy  );

		itoa( stat, NumberString, 10);

		DisplayString( 254-
				(PixelLengthOfString((char *)NumberString, SMALL_FONT)/2),
				278,
				(char *)NumberString,
				SMALL_FONT, 62, NO_BOX, &FrontendPseudoDEFN, &FrontendTextureDEFN  );


	// *** PLAYERS TACKLING ***	> 60% power + 40% discipline

		DisplayString( 43, 300,
		     ( GetTEXT( STAT_LBLS+Tackling )) , 
			SMALL_FONT, 48, NO_BOX, &FrontendPseudoDEFN, &FrontendTextureDEFN  );

		stat	=     	((60*Power[ ActPlyrIx ])/100) +
				((40*Discipline[ ActPlyrIx ])/100);
		
		Image_Widths[PURP_FILL+Dull] = stat*1.14;

		if ( stat > 0 )
			DrawIMAGE( &FrontendPseudoDEFN, &FrontendTextureDEFN, 
			   PURP_FILL+Dull, 122, 303, NO_BOX, straightcopy );

		stat	=     	((60*tpow)/100) +
				((40*Discipline[ ActPlyrIx ])/100);

		Image_Widths[PURP_FILL+Bright] = stat*1.14;
		
		if ( stat > 0 )
			DrawIMAGE( &FrontendPseudoDEFN, &FrontendTextureDEFN, 
			   PURP_FILL+Bright, 122, 303, NO_BOX, straightcopy  );

		itoa( stat, NumberString, 10);

		DisplayString( 254-
				(PixelLengthOfString((char *)NumberString, SMALL_FONT)/2),
				300,
				(char *)NumberString,
				SMALL_FONT, 62, NO_BOX, &FrontendPseudoDEFN, &FrontendTextureDEFN  );


	// *** PLAYERS PASSING ***	> 50% vision + 50% accuracy

		DisplayString( 43, 322,
		     ( GetTEXT( STAT_LBLS+Passing )) , 
			SMALL_FONT, 48, NO_BOX, &FrontendPseudoDEFN, &FrontendTextureDEFN  );

		stat	=     	((50*Vision[ ActPlyrIx ])/100) +
				((50*Accuracy[ ActPlyrIx ])/100);
		
		Image_Widths[PURP_FILL+Dull] = stat*1.14;

		if ( stat > 0 )
			DrawIMAGE( &FrontendPseudoDEFN, &FrontendTextureDEFN, 
			   PURP_FILL+Dull, 122, 325, NO_BOX, straightcopy );

		stat	=     	((50*Vision[ ActPlyrIx ])/100) +
				((50*tacc)/100);

		Image_Widths[PURP_FILL+Bright] = stat*1.14;
		
		if ( stat > 0 )
			DrawIMAGE( &FrontendPseudoDEFN, &FrontendTextureDEFN, 
			   PURP_FILL+Bright, 122, 325, NO_BOX, straightcopy  );

		itoa( stat, NumberString, 10);
					
		DisplayString( 254-
				(PixelLengthOfString((char *)NumberString, SMALL_FONT)/2),
				322,
				(char *)NumberString,
				SMALL_FONT, 62, NO_BOX, &FrontendPseudoDEFN, &FrontendTextureDEFN  );


	// *** PLAYERS SHOOTING ***	> 70% accuracy + 30% power

		DisplayString( 43, 344,
		     ( GetTEXT( STAT_LBLS+Shooting )) , 
			SMALL_FONT, 48, NO_BOX, &FrontendPseudoDEFN, &FrontendTextureDEFN  );

		stat	=     	((70*Accuracy[ ActPlyrIx ])/100) +
				((30*Power[ ActPlyrIx ])/100);
		
		Image_Widths[PURP_FILL+Dull] = stat*1.14;

		if ( stat > 0 )
			DrawIMAGE( &FrontendPseudoDEFN, &FrontendTextureDEFN, 
			   PURP_FILL+Dull, 122, 347, NO_BOX, straightcopy );

		stat	=     	((70*tacc)/100) +
				((30*tpow)/100);

		Image_Widths[PURP_FILL+Bright] = stat*1.14;
		
		if ( stat > 0 )
			DrawIMAGE( &FrontendPseudoDEFN, &FrontendTextureDEFN, 
			   PURP_FILL+Bright, 122, 347, NO_BOX, straightcopy  );

		itoa( stat, NumberString, 10);
					
		DisplayString( 254-
				(PixelLengthOfString((char *)NumberString, SMALL_FONT)/2),
				344,
				(char *)NumberString,
				SMALL_FONT, 62, NO_BOX, &FrontendPseudoDEFN, &FrontendTextureDEFN  );



	// *** PLAYERS SKILL ***	> 50% flair + 50% control

		DisplayString( 43, 366,
		     ( GetTEXT( STAT_LBLS+Skill )) , 
			SMALL_FONT, 48, NO_BOX, &FrontendPseudoDEFN, &FrontendTextureDEFN  );

		stat	=     	((50*Flair[ ActPlyrIx ])/100) +
				((50*Control[ ActPlyrIx ])/100);
		
		Image_Widths[PURP_FILL+Dull] = stat*1.14;

		if ( stat > 0 )
			DrawIMAGE( &FrontendPseudoDEFN, &FrontendTextureDEFN, 
			   PURP_FILL+Dull, 122, 369, NO_BOX, straightcopy );

		stat	=     	((50*tflair)/100) +
				((50*Control[ ActPlyrIx ])/100);

		Image_Widths[PURP_FILL+Bright] = stat*1.14;
		
		if ( stat > 0 )
			DrawIMAGE( &FrontendPseudoDEFN, &FrontendTextureDEFN, 
			   PURP_FILL+Bright, 122, 369, NO_BOX, straightcopy  );

		itoa( stat, NumberString, 10);
					
		DisplayString( 254-
				(PixelLengthOfString((char *)NumberString, SMALL_FONT)/2),
				366,
				(char *)NumberString,
				SMALL_FONT, 62, NO_BOX, &FrontendPseudoDEFN, &FrontendTextureDEFN  );


	// *** PLAYERS FITNESS ***

		DisplayString( 43, 421,
		     ( GetTEXT( STAT_LBLS+Fit )) , 
			SMALL_FONT, 48, NO_BOX, &FrontendPseudoDEFN, &FrontendTextureDEFN  );

		stat	=     	Fitness[ ActPlyrIx ];
		
		itoa( stat, NumberString, 10);
					
		Image_Widths[PURP_FILL+Bright] = stat*1.14;
		Image_Widths[BRED_FILL] = stat*1.14;

		if ( stat > Injured )
			DrawIMAGE( &FrontendPseudoDEFN, &FrontendTextureDEFN, 
			   PURP_FILL+Bright, 122, 424, NO_BOX, straightcopy );
		else

		if ( stat > 0 )
			DrawIMAGE( &FrontendPseudoDEFN, &FrontendTextureDEFN, 
			   BRED_FILL, 122, 424, NO_BOX, straightcopy );

		DisplayString( 254- (PixelLengthOfString((char *)NumberString, SMALL_FONT)/2), 421,
				(char *)NumberString, SMALL_FONT, 62, NO_BOX, &FrontendPseudoDEFN, &FrontendTextureDEFN  );
	}

//********************************************************************************************************************************

void	DoPlayerStats( char MENU, signed char BOX, short xposn, short yposn )
	{
		if ( MENU == PLAYER_STATS && LogicState == RUN_FRONTEND )
		{
			if ( BOX == RETURN_PSTATS_BOX && ButtonState!=0 )
			  {
				Team =	ConfigureTeamView();
				if ( ButtonState == LEFT_BUTTON )
					Animation_table[ReturnStatHandle].AnimationSpeed = -1.25;
				else
					Animation_table[ReturnStatHandle].AnimationSpeed = 1.25;

				ChangeMenu	=	SQUAD_SELECT;
			     	DeBounce  	= 	TRUE;
			  }								 	
		}
	}



//********************************************************************************************************************************

void	DisplayTeamStats()
	{

	short  wins		=	0;
	short  draws		=	0;
	short  loses		=	0;
	int  gls_for		=	0;
	int  gls_against	=	0;
	char ammount[5];	


      	for ( char h=0; h < 10; h++ )
	  {
		if ( PastScores[EUROstatTeam].history[h].scored == PastScores[EUROstatTeam].history[h].conceeded )
			draws++;		
		if ( PastScores[EUROstatTeam].history[h].scored > PastScores[EUROstatTeam].history[h].conceeded )
			wins++;		
		if ( PastScores[EUROstatTeam].history[h].scored < PastScores[EUROstatTeam].history[h].conceeded )
			loses++;		

		gls_for+=	(int)PastScores[EUROstatTeam].history[h].scored;
		gls_against+=	(int)PastScores[EUROstatTeam].history[h].conceeded;
	  }

	// *** LAST FIVE GAMES LABEL ***

		DisplayString( 260-(PixelLengthOfString(GetTEXT( TINF_LBLS+Last10 ), MEDIUM_FONT)/2), 412,
		     ( GetTEXT( TINF_LBLS+Last10 )) , 
		     MEDIUM_FONT, 29, NO_BOX, &FrontendBackgroundDEFN, &FrontendTextureDEFN  );

	// *** WINS ***

		DisplayString( 54-(PixelLengthOfString(GetTEXT( TINF_LBLS+Teamwins ), SMALL_FONT)/2), 441,
		     ( GetTEXT( TINF_LBLS+Teamwins )), 
		     SMALL_FONT, 22, NO_BOX, &FrontendBackgroundDEFN, &FrontendTextureDEFN  );

			itoa( wins, ammount, 10);

			DisplayString( 107 - (PixelLengthOfString( ammount, SMALL_FONT ) /2 ), 441,
				ammount, SMALL_FONT, 15, NO_BOX, 
				&FrontendBackgroundDEFN, &FrontendTextureDEFN  );

	// *** DRAWS ***

		DisplayString( 154-(PixelLengthOfString(GetTEXT( TINF_LBLS+Teamdraws ), SMALL_FONT)/2), 441,
		     ( GetTEXT( TINF_LBLS+Teamdraws )), 
		     SMALL_FONT, 22, NO_BOX, &FrontendBackgroundDEFN, &FrontendTextureDEFN  );

			itoa( draws, ammount, 10);

			DisplayString( 204 - (PixelLengthOfString( ammount, SMALL_FONT ) /2 ), 441,
				ammount, SMALL_FONT, 15, NO_BOX, 
				&FrontendBackgroundDEFN, &FrontendTextureDEFN  );

	// *** LOST ***

		DisplayString( 251-(PixelLengthOfString(GetTEXT( TINF_LBLS+Teamloses ), SMALL_FONT)/2), 441,
		     ( GetTEXT( TINF_LBLS+Teamloses )), 
		     SMALL_FONT, 22, NO_BOX, &FrontendBackgroundDEFN, &FrontendTextureDEFN  );

			itoa( loses, ammount, 10);

			DisplayString( 301 - (PixelLengthOfString( ammount, SMALL_FONT ) /2 ), 441,
				ammount, SMALL_FONT, 15, NO_BOX, 
				&FrontendBackgroundDEFN, &FrontendTextureDEFN  );

	// *** GOALS FOR ***

		DisplayString( 348-(PixelLengthOfString(GetTEXT( TINF_LBLS+Teamglsfor ), SMALL_FONT)/2), 441,
		     ( GetTEXT( TINF_LBLS+Teamglsfor )), 
		     SMALL_FONT, 22, NO_BOX, &FrontendBackgroundDEFN, &FrontendTextureDEFN  );

			itoa( gls_for, ammount, 10);

			DisplayString( 398 - (PixelLengthOfString( ammount, SMALL_FONT ) /2 ), 441,
				ammount, SMALL_FONT, 15, NO_BOX, 
				&FrontendBackgroundDEFN, &FrontendTextureDEFN  );

	// *** GOALS AGAINST ***

		DisplayString( 445-(PixelLengthOfString(GetTEXT( TINF_LBLS+Teamglsagn ), SMALL_FONT)/2), 441,
		     ( GetTEXT( TINF_LBLS+Teamglsagn )), 
		     SMALL_FONT, 22, NO_BOX, &FrontendBackgroundDEFN, &FrontendTextureDEFN  );

			itoa( gls_against, ammount, 10);

			DisplayString( 495 - (PixelLengthOfString( ammount, SMALL_FONT ) /2 ), 441,
				ammount, SMALL_FONT, 15, NO_BOX, 
				&FrontendBackgroundDEFN, &FrontendTextureDEFN  );

	// *** PRESIDENT ***

		DisplayString( 426-(PixelLengthOfString(GetTEXT( TINF_LBLS+President ), MEDIUM_FONT)/2), 282,
		     ( GetTEXT( TINF_LBLS+President )) , 
		     MEDIUM_FONT, 29, NO_BOX, &FrontendBackgroundDEFN, &FrontendTextureDEFN  );

		DisplayString( 426-(PixelLengthOfString(GetTEXT( PRES_NMES+EUROstatTeam ), SMALL_FONT)/2), 309,
		     ( GetTEXT( PRES_NMES+EUROstatTeam )) , 
		     SMALL_FONT, 15, NO_BOX, &FrontendBackgroundDEFN, &FrontendTextureDEFN  );

	// *** COACH ***

		DisplayString( 426-(PixelLengthOfString(GetTEXT( TINF_LBLS+Coach ), MEDIUM_FONT)/2), 339,
		     ( GetTEXT( TINF_LBLS+Coach )) , 
		     MEDIUM_FONT, 29, NO_BOX, &FrontendBackgroundDEFN, &FrontendTextureDEFN  );

		DisplayString( 426-(PixelLengthOfString(GetTEXT( COCH_NMES+EUROstatTeam ), SMALL_FONT)/2), 366,
		     ( GetTEXT( COCH_NMES+EUROstatTeam )) , 
		     SMALL_FONT, 15, NO_BOX, &FrontendBackgroundDEFN, &FrontendTextureDEFN  );

	// *** STAR PLAYERS ***

		DisplayString( 426-(PixelLengthOfString(GetTEXT( TINF_LBLS+Starplayr ), MEDIUM_FONT)/2), 164,
		     ( GetTEXT( TINF_LBLS+Starplayr )) , 
		     MEDIUM_FONT, 29, NO_BOX, &FrontendBackgroundDEFN, &FrontendTextureDEFN  );

	      	for ( char s=0; s < 3; s++ )
		  {

		DisplayString( 426-(PixelLengthOfString( GetPLAYERSname( StarPlayers[ (EUROstatTeam*3)+s ], EUROstatTeam, FULL_NAME ), 
		     SMALL_FONT)/2), 190+(s*22),
	     	     ( GetPLAYERSname( StarPlayers[ (EUROstatTeam*3)+s ], EUROstatTeam, FULL_NAME )) , 
		     SMALL_FONT, 15, NO_BOX, &FrontendBackgroundDEFN, &FrontendTextureDEFN  );
		  }

	// *** PREVIOUS YEARS ***

		DisplayString( 171-(PixelLengthOfString(GetTEXT( TINF_LBLS+Record ), MEDIUM_FONT)/2), 163,
		     ( GetTEXT( TINF_LBLS+Record )) , 
		     MEDIUM_FONT, 29, NO_BOX, &FrontendBackgroundDEFN, &FrontendTextureDEFN  );

		if ( PreviousEuroYearsTBL[EUROstatTeam] <= 0 )
		     DrawIMAGE( &FrontendBackgroundDEFN, &FrontendTextureDEFN, 
		     	TBAR_SPLT, 70, 188, NO_BOX, spritecopy );  	

		

	      	for ( char y=0; y < 9; y++ )
		  {

			if ( y >= PreviousEuroYearsTBL[EUROstatTeam] )
			{
			   DisplayString( 28, 187+(y*22),
			   	( GetTEXT( YEAR_LBLS+y )) , 
				   MEDIUM_FONT, 22, NO_BOX, &FrontendBackgroundDEFN, &FrontendTextureDEFN  );
  			   DisplayString( 84, 191+(y*22),
  			   	( GetTEXT( HIST_LBLS+(PreviousEuroHistory[(EUROstatTeam*9)+y]) )) , 
  				   SMALL_FONT, 15, NO_BOX, &FrontendBackgroundDEFN, &FrontendTextureDEFN  );
			}

			else
			
  			   DisplayString( 24, 191+(y*22),
  			   	( GetTEXT( HIST_LBLS+(PreviousEuroHistory[(EUROstatTeam*9)+y]) )) , 
  				   SMALL_FONT, 15, NO_BOX, &FrontendBackgroundDEFN, &FrontendTextureDEFN  );
		  }
	}

//********************************************************************************************************************************

void	DoTeamStats( char MENU, signed char BOX, short xposn, short yposn )
	{
		if ( MENU == TEAM_STATS && LogicState == RUN_FRONTEND )
		{
			if ( BOX == RETN_TSTATS_BOX && ButtonState!=0 )
			  {
				if ( ButtonState == LEFT_BUTTON )
					Animation_table[ReturnTeamHandle].AnimationSpeed = -1.25;
				else
					Animation_table[ReturnTeamHandle].AnimationSpeed = 1.25;

				ChangeMenu	=	PLAYER_STATS;
			     	DeBounce  	= 	TRUE;
			  }								 	


			if ( BOX == OPPONENT_TEAM_BOX && ButtonState!=0 )
				{
					if ( ButtonState == LEFT_BUTTON )
						{
						Animation_table[ViewTeamHandle].AnimationSpeed = -1.25;
						EUROstatTeam++;
						}
					else
						{
						Animation_table[ViewTeamHandle].AnimationSpeed = 1.25;
						EUROstatTeam--;
						}

					EUROstatTeam&=15;
					ChangeMenu	=	TEAM_STATS;
				     	DeBounce  	= 	TRUE;
				}								 	


		RetnTstatHighlight 	=  	ControlOptionHighlight( BOX, RETN_TSTATS_BOX,
				   	 	RETN_TSTATSdisp_BOX, RetnTstatHighlight, 
			 	   		ReturnTeamHandle, BUTN_LBLS+Done );


		}
	}

//********************************************************************************************************************************

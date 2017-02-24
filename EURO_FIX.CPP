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
#include "euro_cnt.h"
#include "euro_gen.h"
#include "euro_rnd.h"
#include "euro_int.h"
#include "defines.h"

//********************************************************************************************************************************

void	DisplayRedrawButton( char Match )
	{
	 	if ( Match == 0 )
		{
			RedrawHandle		=	 AddAnimation( 507, 180, 
							 ( (float)BUTN_WHBL ), ( (float)BUTN_WHBL+11.9 ),
							 0.0, REDRAW_BOX, CONT_ANIM );
			RedrawHighlight		= 	 ControlOptionHighlight( -1, REDRAW_BOX, REDRAWdisp_BOX, 
							 -1, RedrawHandle, BUTN_LBLS+Redraw );
		}
	}

//********************************************************************************************************************************

char FindNextFixtureTeam( char drawcode )
	{
		char	team	=	0;

		for ( char t=0; t < 16 ; t++ )
			{
		 		if ( GroupDrawInfo[t]	== drawcode )
				{
					team	=	t;
					break;
				}			
			}

		return (team);
	}

//********************************************************************************************************************************

char FindTeamInLeague( char posn )
	{
		char	team	=	0;

		for ( char t=0; t < 16 ; t++ )
			{
		 		if ( LeaguePositions[t]	== posn )
				{
					team	=	t;
					break;
				}			
			}

		return (team);
	}

//********************************************************************************************************************************

void	GroupFixturesPage( char MENU, signed char BOX )
	{
		if ( MENU == GROUP_FIXTURES && LogicState == RUN_FRONTEND )
		{
			if ( BOX == REDRAW_BOX && ButtonState != 0 )
			  {
				Animation_table[RedrawHandle].AnimationSpeed =
						WhichButton( ButtonState, 0.85);
				ChangeMenu	=	EURO_REDRAW;
			     	DeBounce  	= 	TRUE;
			  }								 	

			if ( BOX == NXT_MTCH_BOX && ButtonState != 0 )
			  {
      
			///	tempory transfer to next match....

				EUROteamA	=	FindNextFixtureTeam( Fixtures[MatchNumber].HomeTeam );
				EUROteamB	=	FindNextFixtureTeam( Fixtures[MatchNumber].AwayTeam );
			///
				Animation_table[NextMatchHandle].AnimationSpeed = 
						WhichButton( ButtonState, 0.85);
				
				if ( MatchNumber<24 )
					ChangeMenu	=	NEXT_MATCH;
				else
					ChangeMenu	=	QUALIFIERS;

			     	DeBounce 	 	= 	TRUE;
			  }								 	
	
		RedrawHighlight	   = ControlOptionHighlight( BOX, REDRAW_BOX, REDRAWdisp_BOX, RedrawHighlight, 
				 	RedrawHandle, BUTN_LBLS+Redraw );
		NextMatchHighlight = ControlOptionHighlight( BOX, NXT_MTCH_BOX, NXT_MTCHdisp_BOX, NextMatchHighlight,
					NextMatchHandle, BUTN_LBLS+NextMatch );
		}
	}	   		

//********************************************************************************************************************************

void CalculateLeagueTables()
	{
		//ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป 
		//บ                                                              บ
		//บ VERBOSE INFORMATION, DISPLAYS LEAGUE TABLE DATA IF REQUESTED บ
		//บ                                                              บ
		//ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ 

		
		if ( EUROverbose != 0 )
		{
			printf("\n  LEAGUE TABLE CALCULATION DATA:\n\n");
			fflush(stdout);				
			printf("    Points for a win:   %d\n", WinPts);
			fflush(stdout);				
			printf("    Points for a draw:  %d\n", DrawPts);
			fflush(stdout);				
		}


		for ( char t=0; t < 16 ; t++ )
		{
			LeaguePositions[t]	=	GroupDrawInfo[t];	//t;
			LeagueTable[t].points	=	
				((LeagueTable[t].won*WinPts) + (LeagueTable[t].drew*DrawPts));
			LeagueTable[t].goalDiff	=	
				(LeagueTable[t].goalsFor-LeagueTable[t].goalsAgainst);


		if ( EUROverbose != 0 )
  
			printf(" (%d)	  W: %d   D: %d   L: %d   Gf: %d   Ga: %d   Pts: %d       %s\n", 
						LeaguePositions[t],
						LeagueTable[t].won, LeagueTable[t].drew, LeagueTable[t].lost,
						LeagueTable[t].goalsFor, LeagueTable[t].goalsAgainst,
						LeagueTable[t].points,	GetTEXT(TEAM_NMES+t ) );
			fflush(stdout);				
		}



	char	SwapTemp;

	for ( char scans = 0; scans < 16; scans++ )
		{
     		for ( char teama = 0; teama < 16; teama++ )
			{

     			for ( char teamb = 0; teamb < 16; teamb++ )
				{

				if ( teama != teamb && 
					( (GroupDrawInfo[teama] & 12) == (GroupDrawInfo[teamb] & 12)) )
	 			    	{
				

				     if ( 
					( LeagueTable[ teama ].points < LeagueTable[ teamb ].points && 
					  LeaguePositions[ teama ] < LeaguePositions[ teamb ] )

					     ||	( LeagueTable[ teama ].points == LeagueTable[ teamb ].points && 
						  LeagueTable[ teama ].won < LeagueTable[ teamb ].won && 
						  LeaguePositions[ teama ] < LeaguePositions[ teamb ] )
						   
					     || ( LeagueTable[ teama ].points == LeagueTable[ teamb ].points && 
						  LeagueTable[ teama ].won == LeagueTable[ teamb ].won && 
						  LeagueTable[ teama ].goalDiff < LeagueTable[ teamb ].goalDiff && 
						  LeaguePositions[ teama ] < LeaguePositions[ teamb ] ) 
							)   	
						{

							SwapTemp = LeaguePositions[ teamb ];
							LeaguePositions[ teamb ] = 
								LeaguePositions[ teama ];
							LeaguePositions[ teama ] = 
								SwapTemp;

			       			}

					}
				}
			}
		}
	}

//********************************************************************************************************************************

void DisplayLeagueTables()
	{	

	char	PAL, PAL2;
	short team;
	char  *ammount;
	for ( char h=0; h < 16 ; h++ )
		{
			DisplayString(
				(GroupFixtureDEFN[h].xposn)-
					(PixelLengthOfString(GetTEXT( GroupFixtureDEFN[h].string), SMALL_FONT ) /2 ), 
				GroupFixtureDEFN[h].yposn,
		   	   	GetTEXT( GroupFixtureDEFN[h].string ),
				SMALL_FONT, 22, NO_BOX, 
				&FrontendBackgroundDEFN, &FrontendTextureDEFN  );

				team	=	(short)FindTeamInLeague(h);

			       	PAL	=	LeagueColourOffsets[team];
				PAL2	=	15;

				if ( MatchNumber > 23 && (h & 2) )
				{
					PAL	=	22;
					PAL2	=	22;
				}

				DisplayString( 
				LeaguePosnDEFN[h].xposn,
				LeaguePosnDEFN[h].yposn,
				GetTEAMname( team, 11 ),
				SMALL_FONT, PAL, NO_BOX, 
				&FrontendBackgroundDEFN, &FrontendTextureDEFN  );

				itoa( LeagueTable[team].won, ammount, 10);
				DisplayString( 
				WinPosnDEFN[h].xposn - 
					(PixelLengthOfString( ammount, SMALL_FONT ) /2 ), 
				WinPosnDEFN[h].yposn,
				ammount,
				SMALL_FONT, PAL2, NO_BOX, 
				&FrontendBackgroundDEFN, &FrontendTextureDEFN  );

				itoa( LeagueTable[team].drew, ammount, 10);
				DisplayString( 
				DrawPosnDEFN[h].xposn - 
					(PixelLengthOfString( ammount, SMALL_FONT ) /2 ), 
				DrawPosnDEFN[h].yposn,
				ammount,
				SMALL_FONT, PAL2, NO_BOX, 
				&FrontendBackgroundDEFN, &FrontendTextureDEFN  );
				itoa( LeagueTable[team].lost, ammount, 10);
				DisplayString( 
				LosePosnDEFN[h].xposn - 
					(PixelLengthOfString( ammount, SMALL_FONT ) /2 ), 
				LosePosnDEFN[h].yposn,
				ammount,
				SMALL_FONT, PAL2, NO_BOX, 
				&FrontendBackgroundDEFN, &FrontendTextureDEFN  );
				itoa( LeagueTable[team].points, ammount, 10);
				DisplayString( 
				PointsPosnDEFN[h].xposn - 
					(PixelLengthOfString( ammount, SMALL_FONT ) /2 ), 
				PointsPosnDEFN[h].yposn,
				ammount,
				SMALL_FONT, PAL2, NO_BOX, 
				&FrontendBackgroundDEFN, &FrontendTextureDEFN  );
		}
	}

//********************************************************************************************************************************

void DisplayLeagueFixtures( char Match )
	{		  
		char	NextMtch = Match;
		char	PAL;
		char    ammount[5];

		if ( Match>23)	   	// if displaying final tables then make slight alteration
			Match = 16;	// so fixtures don't zoom ahead....

		Match&=	(31-7);

		for ( char f=0; f < 8 ; f++ )
		{

			PAL	=	22;
		
			if ( Match == NextMtch )
	
				PAL = 15;


			if ( Match<NextMtch )
			{			
			
			char ResText[128];

			strcpy(ResText, GetTEAMname( FindNextFixtureTeam( Fixtures[Match].HomeTeam ), 11) );
			strcat(ResText, " ");
	       		itoa( (int)Results[Match].HomeScore, EUROammount, 10);
			strcat(ResText, EUROammount);

			DisplayString(
				Fixtures[Match].fixXposn-
			               (PixelLengthOfString( ResText,SMALL_FONT) /2 ),
				Fixtures[Match].fixYposn,
		   	   	ResText,
				SMALL_FONT, 29, NO_BOX, 
				&FrontendBackgroundDEFN, &FrontendTextureDEFN  );

			strcpy(ResText, GetTEAMname( FindNextFixtureTeam( Fixtures[Match].AwayTeam ), 11) );
			strcat(ResText, " ");
	       		itoa( (int)Results[Match].AwayScore, EUROammount, 10);
			strcat(ResText, EUROammount);

			DisplayString(
				(Fixtures[Match].fixXposn+116)-
			               (PixelLengthOfString( ResText,SMALL_FONT) /2 ),
				Fixtures[Match].fixYposn,
		   	   	ResText,
				SMALL_FONT, 29, NO_BOX, 
				&FrontendBackgroundDEFN, &FrontendTextureDEFN  );
			}
			
			else

			{

			DisplayString(
				Fixtures[Match].fixXposn-
		        	(PixelLengthOfString( 
				GetTEAMname( FindNextFixtureTeam( Fixtures[Match].HomeTeam ), 11), SMALL_FONT ) /2 ),
				Fixtures[Match].fixYposn,
		   	   	GetTEAMname( FindNextFixtureTeam( Fixtures[Match].HomeTeam ), 11), SMALL_FONT, 
				PAL, NO_BOX, 
				&FrontendBackgroundDEFN, &FrontendTextureDEFN  );

			DisplayString(
				(Fixtures[Match].fixXposn+116)-
		        	(PixelLengthOfString( 
				GetTEAMname( FindNextFixtureTeam( Fixtures[Match].AwayTeam), 11), SMALL_FONT ) /2 ),
				Fixtures[Match].fixYposn,
		   	   	GetTEAMname( FindNextFixtureTeam( Fixtures[Match].AwayTeam), 11), SMALL_FONT, 
				PAL, NO_BOX, 
				&FrontendBackgroundDEFN, &FrontendTextureDEFN  );

			DisplayString( 
				(Fixtures[Match].fixXposn+58)-
				(PixelLengthOfString(GetTEXT( VRUS_LBLE ), SMALL_FONT ) /2 ), 
				Fixtures[Match].fixYposn,
		   	   	GetTEXT( VRUS_LBLE ),
				SMALL_FONT, PAL, NO_BOX, 
				&FrontendBackgroundDEFN, &FrontendTextureDEFN  );
			}


			Match++;
		}
	}

//********************************************************************************************************************************
//
//void	DisplayVersusList( char Match )
//	{
//
//	char	NextMtch = Match;
//       	Match&=	(31-7);
//
//	for ( char v=0; v < 8 ; v++ )
//		{
//
//			if ( Match >= NextMtch )
//			{			
//
//			DisplayString( VersusPosnDEFN[v].xposn - (PixelLengthOfString(GetTEXT( VRUS_LBLE ), SMALL_FONT ) /2 ), 
//				VersusPosnDEFN[v].yposn,
//		   	   	GetTEXT( VRUS_LBLE ),
//				SMALL_FONT, 22, NO_BOX, 
//				&FrontendBackgroundDEFN, &FrontendTextureDEFN  );
//			}
//       
//		Match++;
//
//		}
//	}
//
//********************************************************************************************************************************


void EuroReDraw( char MENU, signed char BOX )
	{
		signed char DrawnTeam, venue;

		if ( MENU == EURO_REDRAW )
		{

		DefaultdrawHighlight =  ControlOptionHighlight( BOX, DEFAULT_BOX,
			   	DEFAULTdisp_BOX, DefaultdrawHighlight, 
		 	   	DefaultHandle, BUTN_LBLS+Default );

			if ( BOX == DEFAULT_BOX && ButtonState != 0 && LogicState == RUN_FRONTEND )
			  {
				memcpy( &GroupDrawInfo[0], &GroupDrawDefaultInfo[0], 16 );
				Animation_table[DefaultHandle].AnimationSpeed = 
						WhichButton( ButtonState, 0.85);
				ChangeMenu	=	GROUP_FIXTURES;
			     	DeBounce  	= 	TRUE;
			  }								 	

			if ( EuroReDrawCounter <= 0.0 )
			{

				if ( EuroReDrawFlag == 22 )
				{
					if ( BOX == GRP_FIX_BOX && ButtonState == LEFT_BUTTON && LogicState == RUN_FRONTEND )
					  {
						Animation_table[GrpFixHandle].AnimationSpeed = 
							WhichButton( ButtonState, 0.85);
						ChangeMenu	=	GROUP_FIXTURES;
					     	DeBounce  	= 	TRUE;
					  }								 	

				RedrawdoneHighlight =  ControlOptionHighlight( BOX, GRP_FIX_BOX,
					   GRP_FIXdisp_BOX, RedrawdoneHighlight, 
				 	   GrpFixHandle, BUTN_LBLS+Done );

				}
				
				if ( EuroReDrawFlag == 21 )
				{
					char c;
					for ( char t=0; t < 16 ; t++ )	    	 
						{
						c		 = GroupDrawInfo[t] / 4;
						GroupDrawInfo[t] = (GroupDrawInfo[t] & 3) +  (GroupVenues[c]*4);
						}						
					EuroReDrawFlag++;

					GrpFixHandle  =	 AddAnimation( 446, 425, 
						      	 ( (float)BUTN_WHBL ), ( (float)BUTN_WHBL+11.9 ),
					      	 	 0.0, GRP_FIX_BOX, RUN_ONCE );
					Animation_table[GrpFixHandle].Counter	=	6.0;
					Animation_table[GrpFixHandle].AnimationSpeed = 0.85;
					
					RedrawdoneHighlight =  ControlOptionHighlight( -1, GRP_FIX_BOX,
						   GRP_FIXdisp_BOX, -1, 
					 	   GrpFixHandle, BUTN_LBLS+Done );
				}

				if ( EuroReDrawFlag > 16 && EuroReDrawFlag < 21 )
				{
					if ( GroupVenues[ (EuroReDrawFlag-17) ] != -1 )
						EuroReDrawFlag++;
					else

					{						
						venue	= (char)( GetRnd2() & 3 );

						if ( GroupVenues[0] != venue &&  
						     GroupVenues[1] != venue &&
						     GroupVenues[2] != venue &&
						     GroupVenues[3] != venue )
						{
							char	v	=	(EuroReDrawFlag-17);
							
							GroupVenues[v]  = venue;

							CopyFromBACKtoPSEUDObuffer(
								&FrontendPseudoDEFN, &FrontendBackgroundDEFN,
								  ReDrawHeadPosnDEFN[v].xposn-84,
								  ReDrawHeadPosnDEFN[v].yposn-5,
								168, 28 );
		
						 	DisplayString(
							 	  ReDrawHeadPosnDEFN[v].xposn-
						 		  ((PixelLengthOfString( GetTEXT( VNUE_NMES+(venue*2) ), 
						 		  SMALL_FONT )) /2),
							 	  ReDrawHeadPosnDEFN[v].yposn-7,
								  GetTEXT( VNUE_NMES+(venue*2) ),
								  SMALL_FONT, 
								  15,
								  NO_BOX, 
								  &FrontendPseudoDEFN, &FrontendTextureDEFN  );

						 	DisplayString(
							 	  ReDrawHeadPosnDEFN[v].xposn-
							 	  ((PixelLengthOfString( GetTEXT( VNUE_NMES+Birmingham+(venue*2) ), 
							 	  SMALL_FONT )) /2),
							 	  ReDrawHeadPosnDEFN[v].yposn+8,
								  GetTEXT( VNUE_NMES+Birmingham+(venue*2) ),
								  SMALL_FONT, 
								  15,
								  NO_BOX, 
								  &FrontendPseudoDEFN, &FrontendTextureDEFN  );
	    			
							AddToDumpList( 
								  ReDrawHeadPosnDEFN[v].xposn-84,
								  ReDrawHeadPosnDEFN[v].yposn-7,
								  168, 32 );
	 	
							EuroReDrawFlag++;
							EuroReDrawCounter	=	25;
						}

					}

 				}



				if ( EuroReDrawFlag==16 )
				{
					venue	= GroupDrawInfo[England] /4;
					EuroReDrawFlag	=	17;

					for ( char v=0; v < 4 ; v++ )	    	 
					{GroupVenues[v] =	-1;}

					GroupVenues[venue] =	0;

					CopyFromBACKtoPSEUDObuffer(
						&FrontendPseudoDEFN, &FrontendBackgroundDEFN,
						  ReDrawHeadPosnDEFN[venue].xposn-84,
						  ReDrawHeadPosnDEFN[venue].yposn-5,
							168, 28 );
				 	DisplayString(
				 	  ReDrawHeadPosnDEFN[venue].xposn-
				 	  ((PixelLengthOfString( GetTEXT( VNUE_NMES ), 
				 	  SMALL_FONT )) /2),
				 	  ReDrawHeadPosnDEFN[venue].yposn-7,
					  GetTEXT( VNUE_NMES ),
					  SMALL_FONT, 
					  15,
					  NO_BOX, 
					  &FrontendPseudoDEFN, &FrontendTextureDEFN  );

				 	DisplayString(
				 	  ReDrawHeadPosnDEFN[venue].xposn-
				 	  ((PixelLengthOfString( GetTEXT( VNUE_NMES+Birmingham ), 
				 	  SMALL_FONT )) /2),
				 	  ReDrawHeadPosnDEFN[venue].yposn+8,
					  GetTEXT( VNUE_NMES+Birmingham ),
					  SMALL_FONT, 
					  15,
					  NO_BOX, 
					  &FrontendPseudoDEFN, &FrontendTextureDEFN  );
	    	
					AddToDumpList( 
					  ReDrawHeadPosnDEFN[venue].xposn-84,
					  ReDrawHeadPosnDEFN[venue].yposn-7,
					  168, 32 );

					EuroReDrawCounter	=	25;
				}					



				if ( EuroReDrawFlag > 11 && EuroReDrawFlag < 16 )
				{
					DrawnTeam	=	(char)( GetRnd2() & 15);


					if ( (DrawnTeam == England ||		
					     DrawnTeam == Spain ||
					     DrawnTeam == Denmark ||
					     DrawnTeam == Germany) &&
					     GroupDrawInfo[DrawnTeam] == -1 )
						{
							GroupDrawInfo[DrawnTeam] = GroupDrawCode[EuroReDrawFlag];

							DisplayString(
							  ReDrawPosnDEFN[EuroReDrawFlag].xposn-
						    	  ((PixelLengthOfString( GetTEAMname( DrawnTeam, 11 ), 
								MEDIUM_FONT )) /2),
							  ReDrawPosnDEFN[EuroReDrawFlag].yposn,
						    		GetTEAMname( DrawnTeam, 11 ),
								MEDIUM_FONT, 
								LeagueColourOffsets[DrawnTeam], 
								NO_BOX, 
								&FrontendPseudoDEFN, &FrontendTextureDEFN  );

							DisplayString(
							  ReDrawPosnDEFN[EuroReDrawFlag].xposn-
						    	  ((PixelLengthOfString( GetTEAMname( DrawnTeam, 11 ), 
								MEDIUM_FONT )) /2),
							  ReDrawPosnDEFN[EuroReDrawFlag].yposn,
						    		GetTEAMname( DrawnTeam, 11 ),
								MEDIUM_FONT, 
								LeagueColourOffsets[DrawnTeam], 
								NO_BOX, 
								&FrontendBackgroundDEFN, &FrontendTextureDEFN  );
								       
							AddToDumpList( 
								ReDrawPosnDEFN[EuroReDrawFlag].xposn-84,
								ReDrawPosnDEFN[EuroReDrawFlag].yposn,
								168, 20 );

							EuroReDrawFlag++;
							EuroReDrawCounter	=	25;
						}



				}

	
				if ( EuroReDrawFlag > -1 && EuroReDrawFlag < 12 )
				{
					DrawnTeam	=	(char)( GetRnd2() & 15);
					
					if ( DrawnTeam != England &&			
					     DrawnTeam != Spain &&
					     DrawnTeam != Denmark &&
					     DrawnTeam != Germany &&
					     GroupDrawInfo[DrawnTeam] == -1 )
						{
							GroupDrawInfo[DrawnTeam] = GroupDrawCode[EuroReDrawFlag];

							DisplayString(
							  	ReDrawPosnDEFN[EuroReDrawFlag].xposn-
							  	((PixelLengthOfString( GetTEAMname( DrawnTeam, 11 ), 
								MEDIUM_FONT )) /2),
							  	ReDrawPosnDEFN[EuroReDrawFlag].yposn,
							  	GetTEAMname( DrawnTeam, 11 ),
								MEDIUM_FONT, 
								LeagueColourOffsets[DrawnTeam], 
								NO_BOX, 
								&FrontendPseudoDEFN, &FrontendTextureDEFN  );

							DisplayString(
							  	ReDrawPosnDEFN[EuroReDrawFlag].xposn-
							  	((PixelLengthOfString( GetTEAMname( DrawnTeam, 11 ), 
								MEDIUM_FONT )) /2),
							  	ReDrawPosnDEFN[EuroReDrawFlag].yposn,
							  	GetTEAMname( DrawnTeam, 11 ),
								MEDIUM_FONT, 
								LeagueColourOffsets[DrawnTeam], 
								NO_BOX, 
								&FrontendBackgroundDEFN, &FrontendTextureDEFN  );

							AddToDumpList( 
								ReDrawPosnDEFN[EuroReDrawFlag].xposn-84,
								ReDrawPosnDEFN[EuroReDrawFlag].yposn,
								168, 20 );

							EuroReDrawFlag++;
							EuroReDrawCounter	=	25;
						}
				}
	

				if ( EuroReDrawFlag == -1 )
				{
					for ( char r=0; r < 16 ; r++ )	    	 
					{GroupDrawInfo[r]	=	-1;}
					EuroReDrawFlag		=	0;
					EuroReDrawCounter	=	25;
				}
			}

			if ( EuroReDrawCounter > 0.0 )
				EuroReDrawCounter-=	1.85;


		}
	}

//********************************************************************************************************************************

void DisplayGroupHeadings()
	{				
		for ( char h=0; h < 4 ; h++ )	    	 
		{
	 	  DisplayString(
		 	  ReDrawHeadPosnDEFN[h].xposn-
		 	  ((PixelLengthOfString( GetTEXT( DRGR_LBLE+h ), 
		 	  MEDIUM_FONT )) /2),
		 	  ReDrawHeadPosnDEFN[h].yposn,
			  GetTEXT( DRGR_LBLE+h ),
			  MEDIUM_FONT, 
			  29,
			  NO_BOX, 
			  &FrontendPseudoDEFN, &FrontendTextureDEFN  );

		  AddToDumpList( 
			  ReDrawHeadPosnDEFN[h].xposn-84,
			  ReDrawHeadPosnDEFN[h].yposn,
			  168, 20 );

		}
	}

//********************************************************************************************************************************

void DisplayQualifierGroupHeadings()
	{				
		for ( char h=0; h < 4 ; h++ )	    	 
		{
	 	  DisplayString(
		 	  QualifierHeadPosnDEFN[h].xposn,
		 	  QualifierHeadPosnDEFN[h].yposn,
			  GetTEXT( GRQU_LBLS+h ),
			  MEDIUM_FONT, 
			  29,
			  NO_BOX, 
			  &FrontendBackgroundDEFN, &FrontendTextureDEFN  );
		}
	}

//********************************************************************************************************************************

void DisplayQualifyingTeams()
	{		  
		short	team;

	 	DisplayString( 12, 92,
	 		GetTEXT (QULY_LBLE),
			LARGE_FONT, 36, NO_BOX, &FrontendBackgroundDEFN, &FrontendTextureDEFN  );
		
		for ( char q=0; q < 8 ; q++ )	    	 
		{
		
		  team	=	(short)FindTeamInLeague( qualifiers[q].team );

	 	  DisplayString( qualifiers[q].xposn-
			  (PixelLengthOfString(GetTEAMname( team, 11), LARGE_FONT ) /2 ),
				 qualifiers[q].yposn,
			  GetTEAMname( team, 11),
			  LARGE_FONT, 43+(7*q), NO_BOX, 
			  &FrontendBackgroundDEFN, &FrontendTextureDEFN  );

			LoadPalette( BIN_TBUL_PAL+( 8*team ),
			 &EuroDATfile[0], (44+(7*q)) );
		}

	}

//********************************************************************************************************************************


void	DoFinalRoundFixtures( char MENU, signed char BOX )
	{
		if ( MENU == QUALIFIERS && LogicState == RUN_FRONTEND )
		{
			if ( BOX == NXT_MTCH_BOX && ButtonState != 0 )
			  {
				Animation_table[NextMatchHandle].AnimationSpeed = 
						WhichButton( ButtonState, 0.85);
				ChangeMenu	=	QUARTER_FINALS;
			     	DeBounce  	= 	TRUE;
			  }								 	
	
			NextMatchHighlight = ControlOptionHighlight( BOX, NXT_MTCH_BOX, NXT_MTCHdisp_BOX, NextMatchHighlight,
						NextMatchHandle, BUTN_LBLS+NextMatch );
		}

		if ( ( MENU == QUARTER_FINALS || MENU == SEMI_FINALS || MENU == FINAL_MATCH ) 
				&& LogicState == RUN_FRONTEND )
		{
			if ( BOX == NXT_MTCH_BOX && ButtonState != 0 )
			  {
				EUROteamA	=	FindNextFixtureTeam( Fixtures[MatchNumber].HomeTeam );
				EUROteamB	=	FindNextFixtureTeam( Fixtures[MatchNumber].AwayTeam );
				Animation_table[NextMatchHandle].AnimationSpeed = 
						WhichButton( ButtonState, 0.85);

				if ( MatchNumber==28 && MENU==QUARTER_FINALS )
				{
				   	ChangeMenu	=	SEMI_FINALS;
				       	GroupDrawInfo[Results[24].WinningTeam] = TEAM_1q;
				       	GroupDrawInfo[Results[25].WinningTeam] = TEAM_2q;
				       	GroupDrawInfo[Results[26].WinningTeam] = TEAM_3q;
				       	GroupDrawInfo[Results[27].WinningTeam] = TEAM_4q;
				}

				else

				if ( MatchNumber==30 && MENU==SEMI_FINALS)
				{
					ChangeMenu	=	FINAL_MATCH;
				       	GroupDrawInfo[Results[28].WinningTeam] = TEAM_1s;
				       	GroupDrawInfo[Results[29].WinningTeam] = TEAM_2s;
				}

				else

		  			ChangeMenu	=	NEXT_MATCH;


			     	DeBounce 	= 	TRUE;
			  }								 	
	
			NextMatchHighlight = ControlOptionHighlight( BOX, NXT_MTCH_BOX, NXT_MTCHdisp_BOX, NextMatchHighlight,
						NextMatchHandle, BUTN_LBLS+NextMatch );
		}


	}

//********************************************************************************************************************************

void DisplayFinalRoundFixtures( char Match, char MENU )
	{		  
		char	n;
		char    ammount[5];
		char	NextMtch;
		char	*Outcome;

		NextMtch = Match;
		
		if ( MENU == QUARTER_FINALS )
		{
			Match 	= 24;
			n	= 4;
		}

		else

		if ( MENU == SEMI_FINALS )
		{
			Match 	= 28;
			n	= 2;
		}

		else
			n	= 1;


		for ( char f=0; f < n ; f++ )
		{

		LoadPalette( BIN_TBUL_PAL+( 8*FindNextFixtureTeam( Fixtures[Match].HomeTeam ) ),
		 &EuroDATfile[0], (44+(14*f)) );

		LoadPalette( BIN_TBUL_PAL+( 8*FindNextFixtureTeam( Fixtures[Match].AwayTeam ) ),
		 &EuroDATfile[0], (44+7+(14*f)) );

			if ( Match<NextMtch )
			{			
			
			char ResText[128];

			strcpy(ResText, GetTEAMname( FindNextFixtureTeam( Fixtures[Match].HomeTeam ), 11) );
			strcat(ResText, "   ");
	       		itoa( (int)Results[Match].HomeScore, EUROammount, 10);
			strcat(ResText, EUROammount);


			DisplayString(
				Fixtures[Match].fixXposn-
		        	(PixelLengthOfString( 
				ResText, LARGE_FONT ) /2 ),
				Fixtures[Match].fixYposn,
		   	   	ResText, LARGE_FONT, 
				(43+(14*f)), NO_BOX, 
				&FrontendBackgroundDEFN, &FrontendTextureDEFN  );


			strcpy(ResText, GetTEAMname( FindNextFixtureTeam( Fixtures[Match].AwayTeam ), 11) );
			strcat(ResText, "   ");
	       		itoa( (int)Results[Match].AwayScore, EUROammount, 10);
			strcat(ResText, EUROammount);

			DisplayString(
				(Fixtures[Match].fixXposn+188)-
		        	(PixelLengthOfString( 
				ResText, LARGE_FONT ) /2 ),
				Fixtures[Match].fixYposn,
		   	   	ResText, LARGE_FONT, 
				(50+(14*f)), NO_BOX, 
				&FrontendBackgroundDEFN, &FrontendTextureDEFN  );

			Outcome	= StringTemplete( RSLT_TEXT+Results[Match].Message, Match );

			DisplayString( 226-(PixelLengthOfString( Outcome, SMALL_FONT ) /2 ), 
				Fixtures[Match].fixYposn+39,
				Outcome, SMALL_FONT, 15, NO_BOX, 
				&FrontendBackgroundDEFN, &FrontendTextureDEFN  );
			}
			
			else

			{

			DisplayString(
				Fixtures[Match].fixXposn-
		        	(PixelLengthOfString( 
				GetTEAMname( FindNextFixtureTeam( Fixtures[Match].HomeTeam ), 11), LARGE_FONT ) /2 ),
				Fixtures[Match].fixYposn,
		   	   	GetTEAMname( FindNextFixtureTeam( Fixtures[Match].HomeTeam ), 11), LARGE_FONT, 
				(43+(14*f)), NO_BOX, 
				&FrontendBackgroundDEFN, &FrontendTextureDEFN  );

			DisplayString(
				(Fixtures[Match].fixXposn+188)-
		        	(PixelLengthOfString( 
				GetTEAMname( FindNextFixtureTeam( Fixtures[Match].AwayTeam), 11), LARGE_FONT ) /2 ),
				Fixtures[Match].fixYposn,
		   	   	GetTEAMname( FindNextFixtureTeam( Fixtures[Match].AwayTeam), 11), LARGE_FONT, 
				(50+(14*f)), NO_BOX, 
				&FrontendBackgroundDEFN, &FrontendTextureDEFN  );


		// date of match

			DisplayString( 
				Fixtures[Match].fixXposn-74,
				Fixtures[Match].fixYposn+39,
		   	   	GetTEXT( DATE_LBLS+Match ),
				SMALL_FONT, 15, NO_BOX, 
				&FrontendBackgroundDEFN, &FrontendTextureDEFN  );

		// venue of match

			DisplayString( 
				Fixtures[Match].fixXposn+260-
					(PixelLengthOfString(GetTEXT( VNUE_NMES+MatchVenues[Match] ), SMALL_FONT ) ), 
				Fixtures[Match].fixYposn+39,
		   	   	GetTEXT( VNUE_NMES+MatchVenues[Match] ),
				SMALL_FONT, 15, NO_BOX, 
				&FrontendBackgroundDEFN, &FrontendTextureDEFN  );

		// versus symbol

			DisplayString( 
				226-
				(PixelLengthOfString(GetTEXT( VRUS_LBLE ), LARGE_FONT ) /2 ), 
				Fixtures[Match].fixYposn,
		   	   	GetTEXT( VRUS_LBLE ),
				LARGE_FONT, 22, NO_BOX, 
				&FrontendBackgroundDEFN, &FrontendTextureDEFN  );
			}


			Match++;
		}
	}

//********************************************************************************************************************************

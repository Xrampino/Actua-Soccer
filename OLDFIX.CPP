#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

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
#include "defines.h"

//********************************************************************************************************************************

void	DisplayRedrawButton( char Match )
	{
	 	if ( Match == 0 )
		{
			RedrawHandle		=	 AddAnimation( 507, 180, 
							 ( (float)WHT_BLUE_BUTTON ), ( (float)WHT_BLUE_BUTTON+11.9 ),
							 0.0, REDRAW_BOX, CONT_ANIM );
			RedrawHighlight		= 	 ControlOptionHighlight( -1, REDRAW_BOX, REDRAWdisp_BOX, 
							 -1, RedrawHandle, BUTN_LBLS+Redraw );
		}
	}

//********************************************************************************************************************************

char FindTeamInLeague( char posn )
	{
		char	team	=	0;

		for ( char t=0; t < 16 ; t++ )
			{
		 		if ( GroupDrawInfo[t]	== posn )
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

				EUROteamA	=	FindTeamInLeague( Fixtures[MatchNumber].HomeTeam );
				EUROteamB	=	FindTeamInLeague( Fixtures[MatchNumber].AwayTeam );


				EUROteamA	=	0;
				EUROteamB	=	1;
				
			///
				Animation_table[NextMatchHandle].AnimationSpeed = 
						WhichButton( ButtonState, 0.85);
				RunMatch 	=	Yes;
				ChangeMenu	=	MAIN;
			     	DeBounce  	= 	TRUE;
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
			printf("    Points for a win:   %d\n", WinPts);
			printf("    Points for a draw:  %d\n", DrawPts);
		}


		for ( char t=0; t < 16 ; t++ )
		{
			LeaguePositions[t]	=	t;
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
		}



	char	SwapTemp;

	for ( char scans = 0; scans < 16; scans++ )
		{

//		for ( char group = 0; group < 4; group++ )
//			{

			for ( char teama = 0; teama < 16; teama++ )
				{

				for ( char teamb = 0; teamb < 16; teamb++ )
					{

			if ( teama != teamb && ( (GroupDrawInfo[teama] & 12) == (GroupDrawInfo[teamb] & 12)) )
 			    {
				

			     if ( ( LeagueTable[ ((group*4)+teama) ].points <  LeagueTable[ ((group*4)+teamb) ].points && 
				  LeaguePositions[ ((group*4)+teama) ]	< LeaguePositions[ ((group*4)+teamb) ] )

			     ||	( LeagueTable[ ((group*4)+teama) ].points == LeagueTable[ ((group*4)+teamb) ].points && 
				  LeagueTable[ ((group*4)+teama) ].won <  LeagueTable[ ((group*4)+teamb) ].won && 
				  LeaguePositions[ ((group*4)+teama) ]	< LeaguePositions[ ((group*4)+teamb) ] )
						   
			     || ( LeagueTable[ ((group*4)+teama) ].points == LeagueTable[ ((group*4)+teamb) ].points && 
				  LeagueTable[ ((group*4)+teama) ].won == LeagueTable[ ((group*4)+teamb) ].won && 
				  LeagueTable[ ((group*4)+teama) ].goalDiff <  LeagueTable[ ((group*4)+teamb) ].goalDiff && 
				  LeaguePositions[ ((group*4)+teama) ]	< LeaguePositions[ ((group*4)+teamb) ] ) 
				) )
							{

							SwapTemp = LeaguePositions[ ((group*4)+teamb) ];
							LeaguePositions[ ((group*4)+teamb) ] = 
								LeaguePositions[ ((group*4)+teama) ];
							LeaguePositions[ ((group*4)+teama) ] = 
								SwapTemp;

							}

						}
					}
				}
//			}
		}
	}

//********************************************************************************************************************************

void DisplayLeagueTables()
	{	

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

				DisplayString( 
				LeaguePosnDEFN[h].xposn,
				LeaguePosnDEFN[h].yposn,
				GetTEAMname( team, 11 ),
				SMALL_FONT, 
				LeagueColourOffsets[team], 
				NO_BOX, 
				&FrontendBackgroundDEFN, &FrontendTextureDEFN  );

				itoa( LeagueTable[team].won, ammount, 10);
				DisplayString( 
				WinPosnDEFN[h].xposn - 
					(PixelLengthOfString( ammount, SMALL_FONT ) /2 ), 
				WinPosnDEFN[h].yposn,
				ammount,
				SMALL_FONT, 
				15,
				NO_BOX, 
				&FrontendBackgroundDEFN, &FrontendTextureDEFN  );

				itoa( LeagueTable[team].drew, ammount, 10);
				DisplayString( 
				DrawPosnDEFN[h].xposn - 
					(PixelLengthOfString( ammount, SMALL_FONT ) /2 ), 
				DrawPosnDEFN[h].yposn,
				ammount,
				SMALL_FONT, 
				15,
				NO_BOX, 
				&FrontendBackgroundDEFN, &FrontendTextureDEFN  );
				itoa( LeagueTable[team].lost, ammount, 10);
				DisplayString( 
				LosePosnDEFN[h].xposn - 
					(PixelLengthOfString( ammount, SMALL_FONT ) /2 ), 
				LosePosnDEFN[h].yposn,
				ammount,
				SMALL_FONT, 
				15,
				NO_BOX, 
				&FrontendBackgroundDEFN, &FrontendTextureDEFN  );
				itoa( LeagueTable[team].points, ammount, 10);
				DisplayString( 
				PointsPosnDEFN[h].xposn - 
					(PixelLengthOfString( ammount, SMALL_FONT ) /2 ), 
				PointsPosnDEFN[h].yposn,
				ammount,
				SMALL_FONT, 
				15,
				NO_BOX, 
				&FrontendBackgroundDEFN, &FrontendTextureDEFN  );
		}
	}

//********************************************************************************************************************************

void DisplayLeagueFixtures( char Match )
	{		  
		char	NextMtch = Match;
		char	PAL;
		Match&=	(31-7);

		for ( char f=0; f < 8 ; f++ )
		{

			PAL	=	22;
		
			if ( Match == NextMtch )
	
				PAL = 15;

//			DisplayString(
//				Fixtures[Match].fixXposn,
//				Fixtures[Match].fixYposn,
//		   	   	GetTEAMname( (FindTeamInLeague( Fixtures[Match].HomeTeam) ) , 11),
//				SMALL_FONT, 22, NO_BOX, 
//				&FrontendBackgroundDEFN, &FrontendTextureDEFN  );
//
//			DisplayString(
//				Fixtures[Match].fixXposn+210-
//			        	(PixelLengthOfString( 
//						GetTEAMname(
//							FindTeamInLeague( Fixtures[Match].AwayTeam ), 11 
//							), SMALL_FONT )),
//				Fixtures[Match].fixYposn,
//		   	   	GetTEAMname( (FindTeamInLeague( Fixtures[Match].HomeTeam) ) , 0),
//				SMALL_FONT, 22, NO_BOX, 
//				&FrontendBackgroundDEFN, &FrontendTextureDEFN  );
//


			DisplayString(
				Fixtures[Match].fixXposn-
			        	(PixelLengthOfString( 
						GetTEAMname(
							FindTeamInLeague( Fixtures[Match].HomeTeam ), 11 
							), SMALL_FONT ) /2 ),
				Fixtures[Match].fixYposn,
		   	   	GetTEAMname( (FindTeamInLeague( Fixtures[Match].HomeTeam) ) , 11),
				SMALL_FONT, PAL, NO_BOX, 
				&FrontendBackgroundDEFN, &FrontendTextureDEFN  );

			DisplayString(
				(Fixtures[Match].fixXposn+116)-
			        	(PixelLengthOfString( 
						GetTEAMname(
							FindTeamInLeague( Fixtures[Match].AwayTeam ), 11 
							), SMALL_FONT ) /2 ),
				Fixtures[Match].fixYposn,
		   	   	GetTEAMname( (FindTeamInLeague( Fixtures[Match].AwayTeam) ) , 0),
				SMALL_FONT, PAL, NO_BOX, 
				&FrontendBackgroundDEFN, &FrontendTextureDEFN  );

			Match++;
		}
	}

//********************************************************************************************************************************

void	DisplayVersusList()
	{

	for ( char v=0; v < 8 ; v++ )
		{
			DisplayString(
				VersusPosnDEFN[v].xposn - 
					(PixelLengthOfString(GetTEXT( VRUS_LBLE ), SMALL_FONT ) /2 ), 
				VersusPosnDEFN[v].yposn,

		   	   	GetTEXT( VRUS_LBLE ),
				SMALL_FONT, 22, NO_BOX, 
				&FrontendBackgroundDEFN, &FrontendTextureDEFN  );
		}

	}

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
						      	 ( (float)WHT_BLUE_BUTTON ), ( (float)WHT_BLUE_BUTTON+11.9 ),
					      	 	 0.0, GRP_FIX_BOX, RUN_ONCE );
					Animation_table[GrpFixHandle].Counter	=	6.0;
					Animation_table[GrpFixHandle].AnimationSpeed = 0.85;
					
					RedrawdoneHighlight =  ControlOptionHighlight( -1, GRP_FIX_BOX,
						   GRP_FIXdisp_BOX, RedrawdoneHighlight, 
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

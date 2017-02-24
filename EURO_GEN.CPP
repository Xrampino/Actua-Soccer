#include <iostream.h>
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
#include "euro_cnt.h"
#include "euro_usr.h"
#include "euro_net.h"
#include "euro_mod.h"
#include "euro_sqd.h"
#include "euro_rnd.h"
#include "euro_mat.h"
#include "euro_int.h"

#include "defines.h"

//********************************************************************************************************************************
//
//char	*GetTEXT( short StringNumber )
//{
//	return( (char *)Text[ StringNumber ] );
//}
//
////********************************************************************************************************************************

char	*ToUPPER( char *string )
	{

	char	len = strlen(&string[0]);
	for ( char u=0; u < len; u++ )
	{ StringBuffer[u] = ToUpper[ *(string+u) ]; }		
	StringBuffer[u] 	= 0;
	return( &StringBuffer[0] );
	}

//********************************************************************************************************************************
//
//char	*GetTEAMname( char team, char maxlen )
//	{
//		char	*Name		=	GetTEXT( TEAM_NMES+team );
//		char	Searchlen	=	strlen(&Name[0]);
//		char	NAMEoffset	=	0;
//
//		for ( char x=0; x<Searchlen ; x++ )
//			{StringBuffer[x] 	= * (Name+x);}
//		StringBuffer[x] 	= 0;
//
//		if ( maxlen!=0 && Searchlen > maxlen )
//			{
//				StringBuffer[maxlen-1] = '.';
//				StringBuffer[maxlen] = 0;
//			}
//
//	return	( &StringBuffer[0] );
//	}
//
//
//
//********************************************************************************************************************************
//
//char	*GetPLAYERSname( char player, char team, char format )
//	{
//		short	Prefix		=	(team*20)+player;
//		char	*Search		=	GetTEXT( PLYR_NMES+Prefix );
//		char	NAMEoffset	=	0;
//		char	Searchlen	=	strlen(&Search[0]);
//		unsigned char 	c;
//		
//		if ( format == FULL_NAME )
//		{	
//			for ( char x=0; x < Searchlen ; x++ )
//				{StringBuffer[x]	= *(Search+x);}
//			StringBuffer[x]	= 0;
//		}
//
//
//		if ( format == INITIAL_SURNAME )
//		{	
//			// *** Get players initials ***
//		
//			for ( char x=0; x < Searchlen ; x++ )
//				{
//					if ( IsUpper[ *(Search+x) ] == up && 
//					     IsUpper[ *(Search+(x+1)) ] == lw && 
//						NAMEoffset < (NAME_BUFFER_LEN-3) ) 
//					{
//						StringBuffer[NAMEoffset] 	= *(Search+x);
//						NAMEoffset++;
//		
//						if ((*(Search+x))=='-')
//							StringBuffer[NAMEoffset] 	= '-';
//						else									
//							StringBuffer[NAMEoffset] 	= '.';
//		
//						StringBuffer[NAMEoffset+1] 	= 32;
//						NAMEoffset+=	2;
//					}
//		
//					if ((*(Search+x))=='-' && NAMEoffset >1 )
//					{
//			      			StringBuffer[NAMEoffset-2] 	= '-';
//			      			NAMEoffset--;
//					}
//				}	
//		}
//		
//		if ( format == INITIAL_SURNAME || format == SURNAME )
//		{	
//		
//			// *** Get players surname ***
//		
//			for ( char y=0; y < Searchlen ; y++ )
//				{
//					if ( IsUpper[ *(Search+y) ] == up && 
//					     IsUpper[ *(Search+(y+1)) ] == up && 
//						NAMEoffset < (NAME_BUFFER_LEN-3) ) 
//
//					{
//						StringBuffer[NAMEoffset] 	= *(Search+y);
//		
////						if ( (IsUpper[ *(Search+(y-1) ) ] == up && y>0) && 
////						     NamePREFIXtbl[Prefix] == 1 &&
////						     ( (StringBuffer[NAMEoffset-1]!='c' || 
////							StringBuffer[NAMEoffset-2]!='M' && NAMEoffset>1 ) ) )
////							{								
////								c = StringBuffer[NAMEoffset];
////								StringBuffer[NAMEoffset] = ToLower[c];
////							}
//
//
//
//						if ( (IsUpper[ *(Search+(y-1) ) ] == up && y>0) )
//						{
//							c = StringBuffer[NAMEoffset];
//
//							if ( ( StringBuffer[NAMEoffset-2]=='M' &&
//							       StringBuffer[NAMEoffset-1]=='c' && 
//							       NAMEoffset>1 && NamePREFIXtbl[Prefix] == 1 )
//							   )
//
//								c = StringBuffer[NAMEoffset];
//
//							else
//
//							   {								
//								c = StringBuffer[NAMEoffset];
//								StringBuffer[NAMEoffset] = ToLower[c];
//							   }
//
//						}
//						
//						NAMEoffset++;
//					}
//		
//					else
//					
//						if ( IsUpper[ *(Search+y) ] == up && 
//						     IsUpper[ *(Search+(y-1)) ] == up && 
//							NAMEoffset < (NAME_BUFFER_LEN-3) && y>0 ) 
//						{
//							StringBuffer[NAMEoffset] 	= *(Search+y);
//		
//							if ( IsUpper[ *(Search+(y-1)) ] == up && y>0 )
//							{								
//								c = StringBuffer[NAMEoffset];
//								StringBuffer[NAMEoffset] = ToLower[c];
//							}
//		
//							NAMEoffset++;
//					
//				    			if ( (*(Search+(y+1)))==' ')
//								{
//									StringBuffer[NAMEoffset] 	= 32;
//									NAMEoffset++;
//								}
//						}
//				}	
//
//			StringBuffer[NAMEoffset]	=	0;	// end of line.
//		}
//
//		return	( &StringBuffer[0] );
//	}
//
//********************************************************************************************************************************

void DisplayTextInputCursor( int xpos, short CursorPosn, int ypos, char *string, int font, int colour, pseudo_info *pseudo, texture_info *texture  )
	{
		if ( CursorDisplaySpeed	> f2L(.5) )
		{

			int	c;
	
			if ( CursorPosn>0 )
			{		
				for ( short x=0; x < CursorPosn; x++ )
				{
	  				c=*string;
	
					if ( c!=0 )								
					{					
						c = ASCtoImageTBL[c];
						c+=  font;
						string++;
						xpos+=	(Image_Widths[c])+1;
					}
				}
			}
	
			c = 63+font;
		      	DrawIMAGE( pseudo, texture, c, xpos, ypos, NO_BOX, spriteinccopy );
		}
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
			Animation_table[a].Bounding_box		=	NO_BOX;
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

void InitialiseMenuPage( char MENU )
	{
		switch ( MENU )
		{

			case( MAIN ):
				Euro96initialise();	// 	reinitialise game data.
		 		EUROuserSelection	=	0;
				break;

			case( SQUAD_SELECT ):
				LoadTactics( ((int)FormationInfo[Team]), &EuroDATfile[0], &TeamTactics[0][0][0] );
				DisplaySquad();
				DisplayFormation( NULL );
				DisplayPositionLabels();
				MarkPlayer		=	-1;
				SquadBuffer1yposn	=	-1;
				QuestionHandle		=	 AddAnimation( 488, 16, 
								 ( (float)QMRK_IMGS ), ( (float)QMRK_IMGS+19.1 ),
								 0.40, QUESTION_BOX, CONT_ANIM );
				FormationHandle		=	 AddAnimation( NameBarXposn-16, 426,
								 ( (float)BUTN_WHBL ), ( (float)BUTN_WHBL+11.9 ),
								 0.0, FORMATION_BOX, RUN_ONCE );
				ReturnSqdHandle		=	 AddAnimation( 308, 426,
								 ( (float)BUTN_WHBL ), ( (float)BUTN_WHBL+11.9 ),
								 0.0, RETURN_SQUAD_BOX, RUN_ONCE );
				ViewTeamHandle		=	 AddAnimation( NameBarXposn-16, 106,
								 ( (float)BUTN_WHBL ), ( (float)BUTN_WHBL+11.9 ),
								 0.0, OPPONENT_TEAM_BOX, RUN_ONCE );
				break;

			case( GROUP_FIXTURES ):
				DisplayRedrawButton( MatchNumber );
				NextMatchHandle		=	 AddAnimation( 507, 226, 
								 ( (float)BUTN_WHBL ), ( (float)BUTN_WHBL+11.9 ),
								 0.0, NXT_MTCH_BOX, CONT_ANIM );
				NextMatchHighlight	= 	 ControlOptionHighlight( -1, NXT_MTCH_BOX, NXT_MTCHdisp_BOX, 
								 -1, NextMatchHandle, BUTN_LBLS+NextMatch );
				break;

			case( TEAM_SELECT ):
				GetFirstLegalEuro96Team();
				ClickBOX		=	NO_BOX;
				SetupTeamSelectButtons( EUROgameType );
				SelectionSpeed		=	0;
				SelectionFlag		=	-1;
				SelectionAim		=	AimTBL[EUROteamA];
				SelectionCounter	=	((float)SelectionAim)*4;
				DisplayGameType( EUROgameType );
				DisplayCountrySelectImages();
				DisplaySelectedTeam();
				break;

			case( EURO_REDRAW ):
				DisplayGroupHeadings();
				EuroDrawHandle		=	AddAnimation( 179, 234, 
								( (float)EURO_RDRW ), ( (float)EURO_RDRW+55.0 ),
								0.40, QUESTION_BOX, CONT_ANIM );
				DefaultHandle  		=	AddAnimation( 446, 380, 
							      	( (float)BUTN_WHBL ), ( (float)BUTN_WHBL+11.9 ),
					      	 	 	0.0, DEFAULT_BOX, CONT_ANIM );
				DefaultdrawHighlight 	=  	ControlOptionHighlight( -1, DEFAULT_BOX,
						   	 	DEFAULTdisp_BOX, -1, 
					 	   		DefaultHandle, BUTN_LBLS+Default );
				EuroReDrawCounter	=	30.0;
				EuroReDrawFlag		=	-1;
				break;

			case( PLAYER_STATS ):
				DisplaySquad();
				DisplayPositionLabels();
				QuestionHandle		=	AddAnimation( 488, 16, 
								( (float)QMRK_IMGS ), ( (float)QMRK_IMGS+19.1 ),
								0.40, QUESTION_BOX, CONT_ANIM );
				ReturnStatHandle	=	AddAnimation( 308, 416,
								( (float)BUTN_WHBL ), ( (float)BUTN_WHBL+11.9 ),
								0.0, RETURN_PSTATS_BOX, CONT_ANIM );
				DisplayPlayerStats();
				break;

			case( PLAYER_SETUP ):
				DisplayUserSetupButtons( 0 );
				ClearNetUserList();
				InitNetUserSelection();
				EUROchampTeam	= 	UserList[EUROplyrSetup].team;

				if ( EUROgameType != EURO_championship )
				{
					DisplayMatchTeam( EUROteamA, 87,  0,  16, EUROmaxPlayers );
				      	DisplayUserTags( EUROteamA, 87,  0 );
					DisplayMatchTeam( EUROteamB, 352, 12, 32, EUROmaxPlayers );
				      	DisplayUserTags( EUROteamB, 352, 12 );
				}
				
				else

				{
					DisplayMatchTeam( EUROchampTeam, 87,  0,  16, EUROnoOfMatchPlyrs  );
				      	DisplayUserTags( EUROchampTeam, 87,  0 );
					LoadPalette( BIN_BUL_PAL+( 8*EUROchampTeam),
					 &EuroDATfile[0], 16 );
				}

				DisplayUserInfo(EUROplyrSetup);
				DisplayUserHeadings(EUROplyrSetup);
				DisplayNETinfo();
				break;
				
			case( TEAM_STATS ):
				ReturnTeamHandle     	=	 AddAnimation( 512, 426,
								 ( (float)BUTN_BLUE ), ( (float)BUTN_WHBL+11.9 ),
								 0.0, RETN_TSTATS_BOX, CONT_ANIM );
				RetnTstatHighlight 	=  	ControlOptionHighlight( -1, RETN_TSTATS_BOX,
						   	 	RETN_TSTATSdisp_BOX, -1, 
					 	   		ReturnTeamHandle, BUTN_LBLS+Done );


				ViewTeamHandle		=	 AddAnimation( NameBarXposn-16, 106,
								 ( (float)BUTN_WHBL ), ( (float)BUTN_WHBL+11.9 ),
								 0.0, OPPONENT_TEAM_BOX, RUN_ONCE );
				break;

			case( MODEM_SETUP ):
				DisplayModemType();
				DisplayDialSetting();
				DisplayCommSetting();
				InitialiseInitString( EUROmodemType );
				DisplayInitString();
				DisplayModemList( ModemYpage );
				DisplayTelephoneNumber();
				ModemYpage = ControlSlider( &ModemSelectDEFN, 0, 0, 0 );
				break;

			case( NEXT_MATCH ):
				DisplayNextMatchType( EUROgameType );
				DisplayNextMatchUsers( EUROgameType );
				DisplayExtMatchTeams();
				NextMatchSelectButtons( EUROgameType );
				SetupChampionshipCntrls( EUROgameType );
				break;

			case( QUALIFIERS ):
				NextMatchHandle		=	 AddAnimation( 446, 426, 
								 ( (float)BUTN_WHBL ), ( (float)BUTN_WHBL+11.9 ),
								 0.0, NXT_MTCH_BOX, CONT_ANIM );
				NextMatchHighlight	= 	 ControlOptionHighlight( -1, NXT_MTCH_BOX, NXT_MTCHdisp_BOX, 
								 -1, NextMatchHandle, BUTN_LBLS+NextMatch );
				break;

			case( QUARTER_FINALS ):
				NextMatchHandle		=	 AddAnimation( 446, 426, 
								 ( (float)BUTN_WHBL ), ( (float)BUTN_WHBL+11.9 ),
								 0.0, NXT_MTCH_BOX, CONT_ANIM );
				NextMatchHighlight	= 	 ControlOptionHighlight( -1, NXT_MTCH_BOX, NXT_MTCHdisp_BOX, 
								 -1, NextMatchHandle, BUTN_LBLS+NextMatch );
				break;

			case( SEMI_FINALS ):
				NextMatchHandle		=	 AddAnimation( 446, 426, 
								 ( (float)BUTN_WHBL ), ( (float)BUTN_WHBL+11.9 ),
								 0.0, NXT_MTCH_BOX, CONT_ANIM );
				NextMatchHighlight	= 	 ControlOptionHighlight( -1, NXT_MTCH_BOX, NXT_MTCHdisp_BOX, 
								 -1, NextMatchHandle, BUTN_LBLS+NextMatch );
				break;

			case( FINAL_MATCH ):
			    	
				DisplayString( 12, 98,
					GetTEXT ( FNAL_HEAD ),
					MEDIUM_FONT, 36, NO_BOX, &FrontendPseudoDEFN, &FrontendTextureDEFN  );

				SpinningCupHandle 	=	AddAnimation( 167, 129, 
								( (float)EUCP_IMGS ), ( (float)EUCP_IMGS+29.9 ),
								0.40, EUROCUP_BOX, CONT_ANIM );
				NextMatchHandle		=	 AddAnimation( 446, 426, 
								 ( (float)BUTN_WHBL ), ( (float)BUTN_WHBL+11.9 ),
								 0.0, NXT_MTCH_BOX, CONT_ANIM );
				NextMatchHighlight	= 	 ControlOptionHighlight( -1, NXT_MTCH_BOX, NXT_MTCHdisp_BOX, 
								 -1, NextMatchHandle, BUTN_LBLS+NextMatch );
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
					   SMLL_GOTH+Team, 550, 2, NO_BOX, spritecopy );  	
				width	   =	PixelLengthOfString( GetTEAMname( Team, 0 ),
									LARGE_FONT);
				Image_Widths[INFO_NBAR+Lft]	=	Image_Widths[INFO_NBAR+Rgt]+width;

				DrawIMAGE( &FrontendBackgroundDEFN, &FrontendTextureDEFN, 
					   INFO_NBAR+Lft, NameBarXposn, 
					   106, NO_BOX, spritecopy ); 
				DrawIMAGE( &FrontendBackgroundDEFN, &FrontendTextureDEFN, 
					   INFO_NBAR+Rgt, NameBarXposn+Image_Widths[INFO_NBAR+Lft], 
					   106, NO_BOX, spritecopy );    

				Image_Widths[INFO_NBAR+Lft]	=	FORMATION_BAR_WIDTH;

				DrawIMAGE( &FrontendBackgroundDEFN, &FrontendTextureDEFN, 
					   INFO_NBAR+Lft, NameBarXposn, 
					   426, NO_BOX, spritecopy );  
				DrawIMAGE( &FrontendBackgroundDEFN, &FrontendTextureDEFN, 
					   INFO_NBAR+Rgt, NameBarXposn+Image_Widths[INFO_NBAR+Lft], 
					   426, NO_BOX, spritecopy );  
				DisplayString( NameBarXposn+Image_Widths[INFO_NBAR+Rgt], 110,
			   	   	GetTEXT(Team+TEAM_NMES),
					LARGE_FONT, 24, TEAM_BOX, &FrontendBackgroundDEFN, &FrontendTextureDEFN  );
				break;


			case( GROUP_FIXTURES ):
				CalculateLeagueTables();
				DisplayLeagueTables();
				DisplayLeagueFixtures( MatchNumber );
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
					   SMLL_GOTH+Team, 550, 2, NO_BOX, spritecopy );  	
				break;
				
			case( PLAYER_SETUP ):
				DisplayUserPanels( EUROgameType );
				DisplayUserLabels(EUROplyrSetup);
				break;
								
			case( TEAM_STATS ):
				width	   =	PixelLengthOfString( GetTEAMname( EUROstatTeam, 0 ),
									LARGE_FONT);
				Image_Widths[TBAR_STAT+Lft] =	Image_Widths[TBAR_STAT+Rgt]+width;

				DrawIMAGE( &FrontendBackgroundDEFN, &FrontendTextureDEFN, 
					   TBAR_STAT+Lft, NameBarXposn, 
					   106, NO_BOX, spritecopy ); 
				DrawIMAGE( &FrontendBackgroundDEFN, &FrontendTextureDEFN, 
					   TBAR_STAT+Rgt, NameBarXposn+Image_Widths[TBAR_STAT+Lft], 
					   106, NO_BOX, spritecopy );    
				DisplayString( NameBarXposn+Image_Widths[TBAR_STAT+Rgt], 110,
			   	   	GetTEXT(EUROstatTeam+TEAM_NMES),
					LARGE_FONT, 36, NO_BOX, &FrontendBackgroundDEFN, &FrontendTextureDEFN  );

				DrawIMAGE( &FrontendBackgroundDEFN, &FrontendTextureDEFN, 
					   BCNT_IMGS+EUROstatTeam,
					   TSTATCountryPosnDEFN[EUROstatTeam].xposn,
					   TSTATCountryPosnDEFN[EUROstatTeam].yposn,
					   NO_BOX, spritecopy );    
				DisplayTeamStats();
				break;

			case( MODEM_SETUP ):

				ModemXposn	=	DisplayModemSetupPanel();
				break;

			case( NEXT_MATCH ):

				DrawIMAGE( &FrontendBackgroundDEFN, &FrontendTextureDEFN, 
					   LRGE_GOTH+EUROteamA,
					   24, 146,
					   NO_BOX, flipsprcopy );    

				DrawIMAGE( &FrontendBackgroundDEFN, &FrontendTextureDEFN, 
					   LRGE_GOTH+EUROteamB,
					   252, 146,
					   NO_BOX, spritecopy );    

				DisplayString( 237 - (PixelLengthOfString(GetTEXT( VRUS_LBLE ), LARGE_FONT))/2,
					   414, GetTEXT( VRUS_LBLE ),
					   LARGE_FONT, 22, NO_BOX, 
					   &FrontendBackgroundDEFN, &FrontendTextureDEFN  );

				     	   break;

			case( QUALIFIERS ):
				DisplayQualifierGroupHeadings();
				DisplayQualifyingTeams();
				break;

			case( QUARTER_FINALS ):
				DisplayFinalRoundFixtures( MatchNumber, Menu );
				break;

			case( SEMI_FINALS ):
				DisplayFinalRoundFixtures( MatchNumber, Menu );
				break;

			case( FINAL_MATCH ):
				DisplayFinalRoundFixtures( MatchNumber, Menu );
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
				LoadTexturePage( BIN_PAGE16,
				 &EuroDATfile[0],
				 4, &FrontendTextureDEFN );
				LoadTexturePage( BIN_PAGE20,
				 &EuroDATfile[0],
				 5, &FrontendTextureDEFN );
				LoadTexturePage( BIN_PAGE21,
				 &EuroDATfile[0],
				 6, &FrontendTextureDEFN );
				LoadTexturePage( BIN_PAGE22,
				 &EuroDATfile[0],
				 7, &FrontendTextureDEFN );
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

			case( NEXT_MATCH ):
				LoadTexturePage( BIN_PAGE17,
				 &EuroDATfile[0],
				 2, &FrontendTextureDEFN );
				LoadTexturePage( BIN_PAGE18,
				 &EuroDATfile[0],
				 3, &FrontendTextureDEFN );
				LoadTexturePage( BIN_PAGE19,
				 &EuroDATfile[0],
				 4, &FrontendTextureDEFN );
					break;

			case( FINAL_MATCH ):
				LoadTexturePage( BIN_PAGE23,
				 &EuroDATfile[0],
				 2, &FrontendTextureDEFN );
				LoadTexturePage( BIN_PAGE24,
				 &EuroDATfile[0],
				 3, &FrontendTextureDEFN );
				LoadTexturePage( BIN_PAGE25,
				 &EuroDATfile[0],
				 4, &FrontendTextureDEFN );
				LoadTexturePage( BIN_PAGE26,
				 &EuroDATfile[0],
				 5, &FrontendTextureDEFN );
					break;
		}
	}

//********************************************************************************************************************************

void	__far EUROinterupt(void)

	{

	fixed	red, green, blue;

		if ( LogicState == PALETTE_FADEUP )
		{
			if ( FadeCounter < 1 || FadeCounter > FADE_COUNTER )
			{
				fixed		*a;
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
	
			fixed	*a;
			fixed	*b;
			BYTE 	*Palette;	
		
			a		=	&CurrentPalette[0];
			b		=	&DivisionTable[0];

			for ( int c=0; c < 256; c++ )
			{
				red		=	(fixed) (*(a)) + (*(b++));
				(*(a++))	=	red;
				green		=	(fixed) (*(a)) + (*(b++));
				(*(a++))	=	green;
				blue		=	(fixed) (*(a)) + (*(b++));
				(*(a++))	=	blue;
				outp	( 0x3c8, c );
				outp    ( 0x3c9, (BYTE) red );
				outp    ( 0x3c9, (BYTE) green );
				outp    ( 0x3c9, (BYTE) blue );
			}
		
			FadeCounter = FadeCounter -1;
	
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

				fixed		*a;
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
				fixed		*a;
				fixed 		*Palette;	
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

			fixed	*a;
			fixed	*b;
			BYTE 	*Palette;	
		
			a		=	&CurrentPalette[0];
			b		=	&DivisionTable[0];

			for ( int c=0; c < 256; c++ )
			{
				red		=	(fixed) (*(a)) - (*(b++));
				(*(a++))	=	red;
				green		=	(fixed) (*(a)) - (*(b++));
				(*(a++))	=	green;
				blue		=	(fixed) (*(a)) - (*(b++));
				(*(a++))	=	blue;
				outp	( 0x3c8, c );
				outp    ( 0x3c9, (BYTE) red );
				outp    ( 0x3c9, (BYTE) green );
				outp    ( 0x3c9, (BYTE) blue );
			}
		
			FadeCounter = FadeCounter -1;
	
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
						    
				SelectFrame+=	f2L(.55); 
		else				     
				SelectFrame =	0;   

		CursorDisplaySpeed+=	f2L(.05);
		
		if ( CursorDisplaySpeed > 1 )
			CursorDisplaySpeed-=	f2L(1.0);
	}


//********************************************************************************************************************************

void	DisplayBoundingBoxes()
	{
		for ( int b=0; b < MAX_BOUNDING_BOXES; b++ )
		{
		       	if ( Bounding_table[b].BoundingBoxLeft != -1 )
				printf("%d used \n",b);
				fflush(stdout);				
		}
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
			        && yposn < Bounding_table[b].BoundingBoxBottom
				 && Bounding_table[b].BoundingBoxLeft>=0
					)
				    	
					box	=	b;
		}

		return(box);
	}

			     
//********************************************************************************************************************************

void StartingEURO_96( char gametype )
	{
		if ( gametype == EURO_network_game )
			EUROcommTYPE = 0;
		if ( gametype == EURO_serial_game )
			EUROcommTYPE = 1;
		if ( gametype == EURO_modem_game )
			EUROcommTYPE = 2;
		if ( gametype == EURO_wireplay )
			EUROcommTYPE = 3;

		if ( EUROcommOVERIDE <128 )
			EUROcommTYPE = EUROcommOVERIDE;

		if ( EUROverbose != 0 )
		{
			printf("þ Calling Set_Comm_Type with comm type: %d\n", EUROcommTYPE );
			fflush(stdout);				
		}

		Set_Comm_Type( EUROcommTYPE );			// 0 network 1 serial 2 modem 3 wireplay

		if ( EUROverbose != 0 )
		{
			printf("þ Calling Start_Network_Game.\n");
			fflush(stdout);				
		}

		if ( Start_Network_Game() != 0 )
		{			
			if ( gametype == EURO_wireplay )
			{				
				printf ("þ ERROR, cannot initialise WIREPLAY game.\n");
				fflush(stdout);
			}
			
			if ( gametype == EURO_network_game )
			{				
				printf ("þ ERROR, cannot initialise NETWORK game.\n");
				fflush(stdout);
			}
			
			if ( gametype == EURO_serial_game )
			{				
				printf ("þ ERROR, cannot initialise SERIAL game.\n");
				fflush(stdout);
			}
			
			if ( gametype == EURO_modem_game )
			{				
				printf ("þ ERROR, cannot initialise MODEM game.\n");
				fflush(stdout);
			}

			EUROgameType	      =	 EURO_friendly;
		}

			else		

		{
			EURO_NetSelectionMade	=	No;
			for (char t=0; t<20; t++)
			{TickPause();}
		}
	}

//********************************************************************************************************************************

void DoMainScreen( char MENU )
	{
		if ( MENU == MAIN && LogicState == RUN_FRONTEND )
		{
			if ( ButtonState != 0 )
			{
				ChangeMenu	=	TEAM_SELECT;
		     		DeBounce  	= 	TRUE;
				EUROoveride	=	0;

				if ( EUROgameType == EURO_network_game || 
					EUROgameType == EURO_modem_game ||
					EUROgameType == EURO_serial_game )
						StartingEURO_96( EUROgameType );
			}
		}
       	}

//********************************************************************************************************************************

char	ConfigureTeamView()
	{
		if ( EUROteamView&=1 )
			return(EUROteamB);
		else
			return(EUROteamA);
	}
				
//********************************************************************************************************************************

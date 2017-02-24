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
#include "euro_grf.h"
#include "euro_dsk.h"
#include "euro_gen.h"
#include "euro_grf.h"
#include "euro_cnt.h"
#include "euro_usr.h"
#include "euro_net.h"
#include "euro_int.h"

#include "defines.h"
#include "intronet.h"

	extern		int   MouseFlags;


void	DisplaySelectedTeam();
char	HaveNETteamsBeenChosen();




//********************************************************************************************************************************

void	SetupTeamSelectButtons( char GAMEtype )
	{
		if ( GAMEtype == EURO_friendly )
		{		
			PlayerSetupHandle 	=  AddAnimation( 446, 180, 
						 ( (float)BUTN_WHBL ), ( (float)BUTN_WHBL+11.9 ),
						 0.0, PLAYER_SETUP_BOX, CONT_ANIM );
			PlyrSetupHighlight 	=  ControlOptionHighlight( -1, PLAYER_SETUP_BOX,
						   PLAYER_SETUPdisp_BOX, -1, 
						   PlayerSetupHandle, BUTN_LBLS+PlayerSetup );


			TeamSetupHandle 	=  AddAnimation( 446, 228, 
						 ( (float)BUTN_WHBL ), ( (float)BUTN_WHBL+11.9 ),
						 0.0, FORMATION_SETUP_BOX, CONT_ANIM );
			TeamSetupHighlight 	=  ControlOptionHighlight( -1, FORMATION_SETUP_BOX,
						   FORMATION_SETUPdisp_BOX, -1, 
						   TeamSetupHandle, BUTN_LBLS+TeamSetup );

			StartMatchHandle 	=  AddAnimation( 446, 300, 
						 ( (float)BUTN_WHBL ), ( (float)BUTN_WHBL+11.9 ),
						 0.0, START_MATCH_BOX, CONT_ANIM );
			StartMatchHighlight 	=  ControlOptionHighlight( -1, START_MATCH_BOX,
						   START_MATCHdisp_BOX, -1, 
						   StartMatchHandle, BUTN_LBLS+StartMatch );

		}

		if ( GAMEtype == EURO_network_game )
		{		
			SelectTeamsHandle 	=  AddAnimation( 446, 300, 
						 ( (float)BUTN_WHBL ), ( (float)BUTN_WHBL+11.9 ),
						 0.0, SELECT_TEAM_BOX, CONT_ANIM );
			SelectTeamsHighlight 	=  ControlOptionHighlight( -1, SELECT_TEAM_BOX,
						   SELECT_TEAMdisp_BOX, -1, 
						   SelectTeamsHandle, BUTN_LBLS+SelectTeams );
		}

		if ( GAMEtype == EURO_championship )
		{		
			UserSelectTeamHandle 	=  AddAnimation( 446, 350, 
						 ( (float)BUTN_WHBL ), ( (float)BUTN_WHBL+11.9 ),
						 0.0, USER_TEAM_SELECT_BOX, CONT_ANIM );
			SelectHighlight		=  ControlOptionHighlight( -1, USER_TEAM_SELECT_BOX,
						   USER_TEAMdisp_BOX, -1,
					 	   UserSelectTeamHandle, BUTN_LBLS+Select );
							    
			if ( EUROuserSelection == 0 )
			{
				NoOfUsersHandle 	=  AddAnimation( 446, 300, 
							 ( (float)BUTN_WHBL ), ( (float)BUTN_WHBL+11.9 ),
							 0.0, NOofUSERS_BOX, RUN_ONCE );
				UserHighlight		= ControlOptionHighlight( -1, NOofUSERS_BOX,
							  NOofUSERSdsp_BOX, -1,
							  NoOfUsersHandle, USRS_LBLS+(EUROnoOfMatchPlyrs-1) );
			}
		}




	}
		
//********************************************************************************************************************************

void	DisplaySelectedTeam()
	{
		CopyFromBACKtoPSEUDObuffer( &FrontendPseudoDEFN, &FrontendBackgroundDEFN,
					52, 406, 366, 30 );

		if ( EUROgameType != EURO_championship )
		{

			DisplayString( 
				132-(PixelLengthOfString(GetTEAMname( EUROteamA, 11 ), LARGE_FONT)/2),
				406,
				GetTEAMname( EUROteamA, 11 ),
				LARGE_FONT, 
				43,
				EURO_TEAMa_BOX,
				&FrontendPseudoDEFN, &FrontendTextureDEFN  );

			DisplayString( 
				340-(PixelLengthOfString(GetTEAMname( EUROteamB, 11 ), LARGE_FONT)/2),
				406,
				GetTEAMname( EUROteamB, 11 ),
				LARGE_FONT, 
				50,
				EURO_TEAMb_BOX,
				&FrontendPseudoDEFN, &FrontendTextureDEFN  );
		}

		else
		

			DisplayString( 
				237-(PixelLengthOfString(GetTEAMname( EUROteamA, 11 ), LARGE_FONT)/2),
				406,
				GetTEAMname( EUROteamA, 11 ),
				LARGE_FONT, 
				43,
				EURO_TEAMa_BOX,
				&FrontendPseudoDEFN, &FrontendTextureDEFN  );

		AddToDumpList( 52, 406, 366, 30 );
	}

//********************************************************************************************************************************

signed	int	LegaliseEuro96UserSelection( int AimAddn, signed int SelectionAim )
	{
		char	a = 0;
		char	c;
		signed  int aim	= AimAddn;
		
	 	while	( a == 0 )
		{
			c = CountryTBL[((SelectionAim+AimAddn)&15)];

			if ( EURO96setup[c].NoOfUsers < 2 )
				a = 1;
			else
				AimAddn+= aim;
		}
		return(AimAddn);
	}

//********************************************************************************************************************************

void	GetFirstLegalEuro96Team()
	{
		if ( EUROgameType == EURO_championship )
		{
			if ( EUROuserSelection == 0 )
			{
				for ( char s=0; s < 16; s++ )
				{
				 	EURO96setup[s].NoOfUsers = 0;
				}
			}

			for ( char i = 0; i < 16; i++ )
	   		{
				if ( EURO96setup[i].NoOfUsers < 2 )
					break;				
			}
			
			EUROteamA 	 = i;
		       	SelectionCounter = AimTBL[EUROteamA];
			memcpy( &PaletteBuffer[44*3], &SparePaletteBuffer[ (LeagueColourOffsets[EUROteamA]*3)+3 ], 7*3 );
		}
	}

//********************************************************************************************************************************

void	UpdateSelectionPalettes()
	{
		fixed	*a;
		fixed	red, green, blue;
		BYTE 		  *DestPalette;	

		a		= &CurrentPalette[44*3];
 		DestPalette	= &PaletteBuffer[44*3];

		memcpy( &PaletteBuffer[44*3], &SparePaletteBuffer[ (LeagueColourOffsets[EUROteamA]*3)+3 ], 7*3 );
		memcpy( &PaletteBuffer[51*3], &SparePaletteBuffer[ (LeagueColourOffsets[EUROteamB]*3)+3 ], 7*3 );

		for ( short c = 44; c < 58; c++ )
   		{
		   	red		=	(*(DestPalette++));		
		   	green		=	(*(DestPalette++));		
		   	blue		=	(*(DestPalette++));		
		   	(*(a++))	=	red;
		   	(*(a++))	=	green;
		   	(*(a++))	=	blue;
			outp	( 0x3c8, c );
			outp    ( 0x3c9, (char)red);
			outp    ( 0x3c9, (char)green);
			outp    ( 0x3c9, (char)blue);
		}
	}

//********************************************************************************************************************************

void	DisplayLowerSelectionPanel( char GAMEtype )
	{
		if ( GAMEtype != EURO_championship )
		{
			DrawIMAGE( &FrontendBackgroundDEFN, &FrontendTextureDEFN, 
				GERL_SBAR, 28, 394, NO_BOX, spritecopy );  	
				
			VersusLength	=	PixelLengthOfString(GetTEXT( VRUS_LBLE ), LARGE_FONT);
			DisplayString( 237 - (VersusLength/2),
				406,
	 	 	   	GetTEXT( VRUS_LBLE ),
				LARGE_FONT, 22, NO_BOX, 
				&FrontendBackgroundDEFN, &FrontendTextureDEFN  );
		}


		else

		{
			DrawIMAGE( &FrontendBackgroundDEFN, &FrontendTextureDEFN, 
				EURO_SELC+Lft, 237-Image_Widths[EURO_SELC+Lft], 
				394, NO_BOX, spritecopy );  	
			DrawIMAGE( &FrontendBackgroundDEFN, &FrontendTextureDEFN, 
				EURO_SELC+Rgt, 237, 394, NO_BOX, spritecopy );  	
		}
	}

//********************************************************************************************************************************

void	DisplayGameType( char gametype )
	{
		if ( EUROgameType == EURO_championship )
			DisplayString( 12, 98,
				GetTEXT ( PICK_LBLS+EUROuserSelection ),
				LARGE_FONT, 36, NO_BOX, &FrontendPseudoDEFN, &FrontendTextureDEFN  );
		else
			DisplayString( 12, 98,
				GetTEXT (MTCH_LBLS+gametype),
				LARGE_FONT, 36, NO_BOX, &FrontendPseudoDEFN, &FrontendTextureDEFN  );
	}

//********************************************************************************************************************************

void	CalculateDir( int SelectionCounter, int SelectionAim)
	{
		SelectDir	=	1;

		for ( int i=0; i < 8; i++ )
		{
			if ( ((int)SelectionCounter&60) == ( ((SelectionAim+i)&15)*4) )
				SelectDir	=	-1;
		}
	}

//********************************************************************************************************************************

void	DoTeamSelection( char MENU, signed char BOX )
	{

	signed int 	SelectionCompare;

//		if ( MENU == TEAM_SELECT && ChangeMenu == -1 &&
//		     EUROgameType == EURO_network_game && 
//		     HaveNETteamsBeenChosen() == Yes )


		if ( MENU == TEAM_SELECT && LogicState == RUN_FRONTEND && //ChangeMenu == -1 
		     EUROgameType == EURO_network_game && 
		     HaveNETteamsBeenChosen() == Yes )
			ChangeMenu	=	PLAYER_SETUP;

		else

		if ( MENU == TEAM_SELECT && LogicState == RUN_FRONTEND )
		{
			if ( EUROgameType == EURO_friendly )
			{		
				StartMatchHighlight 	=  ControlOptionHighlight( BOX, START_MATCH_BOX,
							   START_MATCHdisp_BOX, StartMatchHighlight, 
							   StartMatchHandle, BUTN_LBLS+StartMatch );

				TeamSetupHighlight 	=  ControlOptionHighlight( BOX, FORMATION_SETUP_BOX,
							   FORMATION_SETUPdisp_BOX, TeamSetupHighlight, 
							   TeamSetupHandle, BUTN_LBLS+TeamSetup );

				PlyrSetupHighlight 	=  ControlOptionHighlight( BOX, PLAYER_SETUP_BOX,
							   PLAYER_SETUPdisp_BOX, PlyrSetupHighlight, 
							   PlayerSetupHandle, BUTN_LBLS+PlayerSetup );

			}

			if ( EUROgameType == EURO_championship )
			{		
				SelectHighlight	= ControlOptionHighlight( BOX, USER_TEAM_SELECT_BOX,
						  USER_TEAMdisp_BOX, SelectHighlight, 
						  UserSelectTeamHandle, BUTN_LBLS+Select );
				UserHighlight	= ControlOptionHighlight( BOX, NOofUSERS_BOX,
						  NOofUSERSdsp_BOX, UserHighlight, 
						  NoOfUsersHandle, USRS_LBLS+(EUROnoOfMatchPlyrs-1) );
			}

			
			if ( EUROgameType == EURO_network_game )
			{		

				SelectTeamsHighlight 	=  ControlOptionHighlight( BOX, SELECT_TEAM_BOX,
							   SELECT_TEAMdisp_BOX, SelectTeamsHighlight, 
							   SelectTeamsHandle, BUTN_LBLS+SelectTeams );

			}


	//-----------------------------------------------------------------------------------------------

		if ( BOX == START_MATCH_BOX && ButtonState != 0 )
		  {
			Animation_table[StartMatchHandle].AnimationSpeed = 
					WhichButton( ButtonState, 0.85);
			RunMatch 	=	Yes;
			ChangeMenu	=	MAIN;
		     	DeBounce  	= 	TRUE;
		  }								 	
	
		//ษอออออออออออออออออออออออออออออออออออออออออป 
		//บ                                         บ
		//บ Ready to start Championship competition บ
		//บ                                         บ
		//ศอออออออออออออออออออออออออออออออออออออออออผ 

		if ( BOX == USER_TEAM_SELECT_BOX && ButtonState != 0 && EUROuserSelection == (EUROnoOfMatchPlyrs-1) )
		  {
			UserList[EUROuserSelection].team = EUROteamA;
			Animation_table[StartEuro96Handle].AnimationSpeed = 
					WhichButton( ButtonState, 0.85);
			SelectHighlight = 	-1;

			ChangeMenu	=	GROUP_FIXTURES;

		     	DeBounce  	= 	TRUE;
		  }								 	

	//-----------------------------------------------------------------------------------------------

			{
				TranslateUserSelections();		
		
				if ( (int)SelectionCounter != (SelectionAim *4) )
					{
						if ( SelectDir == 1 )
							SelectionCounter+=	SelectionSpeed;
						if ( SelectDir == -1 )
							SelectionCounter-=	SelectionSpeed;
	
						if ( SelectionSpeed < 1.0 && SelectionSpeed > 0 )
					 		SelectionSpeed*=	2;
						if ( SelectionSpeed > 1.0 )
					 		SelectionSpeed =	1.0;
					}
	
				else
					{
						if ( ClickBOX == EURO_TEAMa_BOX )
							EUROteamA	=	CountryTBL[SelectionAim];
						if ( ClickBOX == EURO_TEAMb_BOX )
							EUROteamB	=	CountryTBL[SelectionAim];
						SelectionCounter=	SelectionAim*4;
						SelectionSpeed	=	0;
					}
	
				SelectionCounter = fmod( SelectionCounter+64, 64);				
	
				if ( SelectionSpeed == 0 && ( BOX == EURO_TEAMa_BOX || BOX == EURO_TEAMb_BOX ) )
				{
					if ( ButtonState != 0 )
					{
						ClickBOX	=	BOX;
						
						if ( BOX == EURO_TEAMa_BOX )
						{
							SelectionAim	=	AimTBL[EUROteamA];
							SelectionCompare=	AimTBL[EUROteamB];
						}
						else
						{
							SelectionAim	=	AimTBL[EUROteamB];
							SelectionCompare=	AimTBL[EUROteamA];
						}
						
						int	AimAddn;
		
						AimAddn = ((int)WhichButton( ButtonState, 1.0 ));
						
						if ( EUROgameType != EURO_championship )
						{						
							if ( ((SelectionAim+AimAddn)&15) == SelectionCompare )
								AimAddn*=	2;
						}

						else
							AimAddn = LegaliseEuro96UserSelection( AimAddn, SelectionAim );
						
						SelectionAim+=	AimAddn;
										
					 	SelectionSpeed	=	.2;
						SelectionAim&=		15;
						CalculateDir(SelectionCounter,SelectionAim);
					     	DeBounce  	= 	TRUE;
					}
				}
	


					//ษอออออออออออออออออออออออออออออออออออออออออออออออออออออป 
					//บ                                                     บ
					//บ User Selects team for Euro Championship competition บ
					//บ                                                     บ
					//ศอออออออออออออออออออออออออออออออออออออออออออออออออออออผ 

				if ( BOX == USER_TEAM_SELECT_BOX && ButtonState != 0 && EUROuserSelection != (EUROnoOfMatchPlyrs-1) )
				  {
					Animation_table[UserSelectTeamHandle].AnimationSpeed = 
							WhichButton( ButtonState, 0.85);
					UserList[EUROuserSelection].team = EUROteamA;
				 	EURO96setup[EUROteamA].NoOfUsers++;
					EUROuserSelection++;
					SelectHighlight = 	-1;
					ChangeMenu	=	TEAM_SELECT;
				     	DeBounce  	= 	TRUE;
				  }								 	

					//ษออออออออออออออออออออออออออออออออออป 
					//บ                                  บ
					//บ User wishes to add an extra user บ
					//บ                                  บ
					//ศออออออออออออออออออออออออออออออออออผ 
	
				if ( BOX == NOofUSERS_BOX && ButtonState != 0 )
				  {
					if ( ButtonState==LEFT_BUTTON && EUROnoOfMatchPlyrs > 1 )
					{
						UserHighlight 	=	-1;
						EUROnoOfMatchPlyrs--;
						Animation_table[NoOfUsersHandle].AnimationSpeed = -0.85;
					     	DeBounce  	= 	TRUE;
					}					

					char	users	= CalculateMaxPlayers();
						
					if ( ButtonState==RIGHT_BUTTON && EUROnoOfMatchPlyrs < 16 &&
					     (users > EUROnoOfMatchPlyrs || users >= 4 )
						)
					{
						UserHighlight 	=	-1;
						EUROnoOfMatchPlyrs++;
						Animation_table[NoOfUsersHandle].AnimationSpeed = 0.85;
					     	DeBounce  	= 	TRUE;
					}					
						
				  }								 	
	
	
				if ( BOX == PLAYER_SETUP_BOX && ButtonState != 0 )
				  {
					Animation_table[PlayerSetupHandle].AnimationSpeed = 
							WhichButton( ButtonState, 0.85);
					ChangeMenu	=	PLAYER_SETUP;
				     	DeBounce  	= 	TRUE;
				  }								 	
	
					//ษออออออออออออออออออออออออออออออออออออออออออออออออออป 
					//บ                                                  บ
					//บ User wishes to change to squad selection options บ
					//บ                                                  บ
					//ศออออออออออออออออออออออออออออออออออออออออออออออออออผ 

				if ( BOX == FORMATION_SETUP_BOX && ButtonState != 0 )
				  {
					Team =	ConfigureTeamView();
					Animation_table[TeamSetupHandle].AnimationSpeed = 
							WhichButton( ButtonState, 0.85);
       					ChangeMenu	=	SQUAD_SELECT;
			     		DeBounce  	= 	TRUE;
				  }								 	

				
				if ( EUROgameType == EURO_network_game && 
				   ( ( BOX == SELECT_TEAM_BOX && ButtonState != 0 ) || 
				   ( Team_A!=-1 && Team_B!=-1)) )
				  {
					Animation_table[PlayerSetupHandle].AnimationSpeed = 
							WhichButton( ButtonState, 0.85);
					ChangeMenu	= 	PLAYER_SETUP;

					if ( Team_A != -1 && Team_B != -1 )
						EURO_Did_I_ChooseTeams	=  No; 		// other user made team choice.
					else 
					{
						EURO_Did_I_ChooseTeams	=  Yes; 	// you made team choice.
						Team_A			=  EUROteamA;   // Send your choice of teams.
						Team_B			=  EUROteamB; 	// Send your choice of teams.
					 	SendTeamInfo();
						TickPause();
						TickPause();
						TickPause();
					     	DeBounce  		=  TRUE;
					}

					EURO_NetSelectionMade	=  No;		// player selection has not yet been made.
				  }								 	

			   	DisplayCountrySelectImages();
				DisplaySelectedTeam();
				UpdateSelectionPalettes();
	    		}

	//-----------------------------------------------------------------------------------------------

		}

	}
//********************************************************************************************************************************


void	DisplayCountrySelectImages()
	{
		int width, height;

		if ( SelectionFlag != -1 )
			CopyFromBACKtoPSEUDObuffer( &FrontendPseudoDEFN, &FrontendBackgroundDEFN,
						40, 219, 382, 102 );

		short	Outline	=	(short)SelectionCounter/4;
		short	index	=	(short)SelectionCounter*8;
	
		for ( int i=0; i < 8; i++ )
		{
			if ( CountryImageDEFN[ ( index+i) ].image_no != -1 )

				DrawIMAGE( &FrontendPseudoDEFN, &FrontendTextureDEFN, 
					CountryImageDEFN[ (index+i) ].image_no+TSEL_IMGS,
					CountryImageDEFN[ (index+i) ].xposn,
					CountryImageDEFN[ (index+i) ].yposn+26,
					NO_BOX, spritecopy );  
		}

			if ( SelectionSpeed == 0 )
			{
				ftable	=	FilterBuffer+(SelectFilterTBL[ (char)SelectFrame&31 ]);
				DrawIMAGE( &FrontendPseudoDEFN, &FrontendTextureDEFN, 
					CNTY_OUTS+Outline,
					CountryOutlinePosnDEFN[Outline].xposn,
					CountryOutlinePosnDEFN[Outline].yposn,
					NO_BOX, spritefilter );  
			}
	
  		SelectionFlag	=	0;
		AddToDumpList( 40, 219, 382, 102 );
	}

//********************************************************************************************************************************

char	HaveNETteamsBeenChosen()
	{
		char TeamsChosen = No;

		if ( Team_A!=-1 && Team_B!=-1 )		// If neither Team_A and Team_B are -1 (initial setting), then
							// another net-user has chosen teams and pressed continue button.
		{
			EURO_Did_I_ChooseTeams		=	NO;		// another user chose teams.
			EUROteamA			=	Team_A;		// Setup other users choice of teams.
			EUROteamB			=	Team_B;		// Setup other users choice of teams.
			TickPause();
			TeamsChosen = Yes;
		}
		return(TeamsChosen);
	}

//***********************************************************************************************************



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
#include "euro_cnt.h"
#include "euro_grf.h"
#include "euro_gen.h"
#include "euro_net.h"
#include "euro_int.h"

#include "defines.h"


char	LegaliseUserCntrlSelection( char, signed char );
char	LegaliseUserPlyrSelection( char, char);
void	DisplayNETinfo();
void	BuildNETuserTable();
void	DisplayUserTags( char, short, char );

//********************************************************************************************************************************

char	FindNumberOfMatchUsers()
	{
		char	users 	= 	0;

		for (char u=0; u<EUROnoOfMatchPlyrs; u++)
		{		
			if ( UserList[u].team == EUROteamA || UserList[u].team == EUROteamB )
				users++;
		}
		return(users);
	}

//********************************************************************************************************************************

void	DisplayUserPanels( char gametype )
	{
		if ( gametype != EURO_championship )
		{		
			DrawIMAGE( &FrontendBackgroundDEFN, &FrontendTextureDEFN, 
				   SMLL_GOTH+EUROteamA, 192, 240, NO_BOX, spritecopy );  	

			DrawIMAGE( &FrontendBackgroundDEFN, &FrontendTextureDEFN, 
				   PSBX_PANL, 278, 232, NO_BOX, spritecopy );  	
			svalue	=	16;
			pmin	=	16;
			pmax	=	32;
			DrawIMAGE( &FrontendBackgroundDEFN, &FrontendTextureDEFN, 
				   SMLL_GOTH+EUROteamB, 456, 240, NO_BOX, spriteareainccopy );  	
		}

		else

		{		
			EUROchampTeam	= 	UserList[EUROplyrSetup].team;

			DrawIMAGE( &FrontendBackgroundDEFN, &FrontendTextureDEFN, 
				   PLRG_GSHD, 337, 238, NO_BOX, spritecopy );  	
			DrawIMAGE( &FrontendBackgroundDEFN, &FrontendTextureDEFN, 
				   PLRG_GOTH+EUROchampTeam, 333, 234, NO_BOX, spritecopy );  	
		}

	}

//********************************************************************************************************************************

void	InitNetUserSelection()
	{
		if ( ( EUROgameType == EURO_network_game || EUROgameType == EURO_wireplay ) 
			&& EUROoveride == 0 ) 
				UserList[0].player	=	PLYR_NOT_CHOSEN;
	}

//********************************************************************************************************************************

void	ResetUsers()
	{
  		for ( char u=0; u < 16; u ++ )
		{
			UserList[u].team   	=	0;
			UserList[u].player 	=	AUTOPLAYER;
			UserList[u].control	= 	-1;
		}
	}

//********************************************************************************************************************************

void	ClearNetUserList()
	{
  		for ( char u=0; u < 24; u ++ )
		{ UserNetList[u] = 0; }
  		UserNetList[0]	= 1; 
  		UserNetList[12]	= 1;
	}

//********************************************************************************************************************************

void	DisplayUserSetupButtons( signed char n )
	{
		OVERRIDEpal1	    =	48;
		OVERRIDEpal2	    =	62;

		if ( EUROgameType == EURO_friendly || EUROgameType == EURO_championship )
		{
	 		TeamSelectHandle=	 AddAnimation( 516, 434, 
	 			 ( (float)BUTN_BLUE ), ( (float)BUTN_WHBL+11.9 ),
				 0.0, TEAM_SELECT_BOX, CONT_ANIM );
			TeamSelectHighlight =  ControlOptionHighlight( -1, TEAM_SELECT_BOX,
				 TEAM_SELECTdisp_BOX, -1, 
				  TeamSelectHandle, BUTN_LBLS+Done );
		}


		if ( EUROgameType == EURO_network_game || EUROgameType == EURO_wireplay )
				//&& n == PLYR_NOT_CHOSEN && UserList[0].player != PLYR_NOT_CHOSEN )
		{
	 		NetStartHandle 	  =  AddAnimation( 516, 300, 
	 				     ( (float)BUTN_BLUE ), ( (float)BUTN_WHBL+11.9 ),
					     0.0, NET_START_BOX, RUN_ONCE );
			NetStartHighlight =  ControlOptionHighlight( -1, NET_START_BOX,
				 	     NET_STARTdisp_BOX, -1, NetStartHandle, BUTN_LBLS+Done );
		}
	}

//********************************************************************************************************************************

void	TranslateUserSelections()
	{
		char	plyr;

		if ( EUROgameType != EURO_championship )
		{

	  		for ( char u=0; u < 16; u ++ )
		 	{
				if ( UserList[u].TeamHAflag == 0 )
					UserList[u].team =	EUROteamA;
				else
					UserList[u].team =	EUROteamB;
			}

		}

	  		for ( char p=0; p < EUROmaxPlayers; p ++ )
			{
				plyr	=	AUTOPLAYER;

		  		for ( char s=0; s < 11; s ++ )
				{
					if ( (SquadInfo[ (UserList[p].team*20)+s]) == UserList[p].player )	
						plyr	=	UserList[p].player;
				}

			UserList[p].player	=	plyr;
			}			
	}


//********************************************************************************************************************************

char	GetAutoPlayers( char Team )
	{
		char	autos	=	0;

 		for ( char p=0; p < EUROmaxPlayers; p ++ )
		{
			if	( UserList[p].team == Team &&
				UserList[p].player == AUTOPLAYER )
					autos++;		
		}		

	return(autos);

	}

//********************************************************************************************************************************

void	DisplayMatchTeam( char Team, short Xposn, char box_offset, int pal, char NoPlyrs )
	{
		int	PAL;
		char	plyr;
		
  		for ( char s=0; s < 11; s ++ )
		{
			plyr	=	SquadInfo[ (Team*20)+s ];
						
			PAL	=	48;
			
	  		for ( char p=0; p < NoPlyrs; p ++ )
			{
				if ( UserList[p].team == Team && 
					 UserList[p].player == plyr )
				{

					if	( UserList[ EUROplyrSetup ].team == Team &&
							UserList[EUROplyrSetup].player == plyr )
							PAL	=	62;
			
					else			
					
					{	
						DisplayString( (Xposn-42)-(PixelLengthOfString( GetTEXT( UTAG_LBLS+p ), SMALL_FONT) ) /2, 
						     (242+( s * 18)), ( GetTEXT ( UTAG_LBLS+p )) , 
						     SMALL_FONT, 55, NO_BOX, &FrontendBackgroundDEFN, &FrontendTextureDEFN  );
							PAL	=	55;
		      			}
				}
			}

				if ( UserNetList[s+box_offset]!=0 &&
					( UserList[ 0 ].team != Team || UserList[0].player != plyr ))
						PAL = 55;

			DisplayString( (Xposn-17)-(PixelLengthOfString( GetTEXT( SQUD_NMBS+plyr ) ,SMALL_FONT) ) /2, 
				     (242+(s*18)), ( GetTEXT ( SQUD_NMBS + plyr )) , 
				     SMALL_FONT, pal+8, s, &FrontendPseudoDEFN, &FrontendTextureDEFN  );

			DisplayString( Xposn,(242+(s*18)), 
				     ( GetPLAYERSname( plyr, Team, INITIAL_SURNAME )) , 
					SMALL_FONT, PAL, s+box_offset, &FrontendPseudoDEFN, &FrontendTextureDEFN  );
		}

		if	( UserList[ EUROplyrSetup ].team == Team &&
				UserList[EUROplyrSetup].player == AUTOPLAYER )
				PAL	=	62;
		else	
				PAL	=	48;
			
		DisplayString( Xposn,(242+(s*18)), 
			     ( GetTEXT( AUTO_LBLE)),	//AUTO_SYMB )) , 
				SMALL_FONT, PAL, box_offset+11, &FrontendPseudoDEFN, &FrontendTextureDEFN  );
	}

//********************************************************************************************************************************

void	DisplayUserHeadings(char user)
	{
		if ( EUROgameType == EURO_friendly || 
			EUROgameType == EURO_championship)
			{		
				DisplayString( 12, 98,
					GetTEXT ( PLYR_LBLS+user ),
					LARGE_FONT, 175, NO_BOX, &FrontendPseudoDEFN, &FrontendTextureDEFN  );
			  	AddToDumpList( 12, 98, 
					PixelLengthOfString( GetTEXT( PLYR_LBLS+user ), LARGE_FONT), 34 );
			}

		else

			{		
				DisplayString( 12, 98,
					GetTEXT ( PSET_HEAD+(EUROgameType-2) ),
					LARGE_FONT, 175, NO_BOX, &FrontendPseudoDEFN, &FrontendTextureDEFN  );
			  	AddToDumpList( 12, 98, 
					PixelLengthOfString( GetTEXT ( PSET_HEAD+(EUROgameType-2)), LARGE_FONT), 34 );
			}

	}

//********************************************************************************************************************************

void	DisplayUserLabels(char user)
	{

		DisplayString( 37, 173,
			GetTEXT ( USEL_LBLS+Country ),
			SMALL_FONT, 55, PLYR_COUNTRY_BOX, &FrontendBackgroundDEFN, &FrontendTextureDEFN  );
		DisplayString( 37, 195,
			GetTEXT ( USEL_LBLS+Cntrl ),
			SMALL_FONT, 55, PLYR_CNTRL_BOX, &FrontendBackgroundDEFN, &FrontendTextureDEFN  );


	// >>> Friendly match user option panel <<<


		if ( EUROgameType == EURO_friendly )
		{
			if ( EUROnoOfMatchPlyrs > 1 )
			{
				Image_Heights[UBAR_PANL+Top] =	 PlrSetupPanelHght[ EUROnoOfMatchPlyrs ];

		  		DrawIMAGE( &FrontendBackgroundDEFN, &FrontendTextureDEFN, 
	  				UBAR_PANL+Top, 277, 131, NO_BOX, spritecopy );  	
	  			DrawIMAGE( &FrontendBackgroundDEFN, &FrontendTextureDEFN, 
		  			UBAR_PANL+Btm, 277, 131+(Image_Heights[UBAR_PANL+Top]), NO_BOX, spritecopy );  	

				char	c = 0;

		  		for ( char p=0; p < EUROnoOfMatchPlyrs; p ++ )
				{
					UserSetupList[p]	=	-1;

					if ( p!=user )
					{					
						DisplayString( 406-(PixelLengthOfString( GetTEXT( PSET_LBLS+p ), SMALL_FONT) ) /2,
							(131+19)+(c*23), 
						     	( GetTEXT( PSET_LBLS+p )) , 
							SMALL_FONT, 62, USER_SETUP_BOX+c, &FrontendBackgroundDEFN, &FrontendTextureDEFN  );
						UserSetupList[c] =	p;
					      	c++;
					}
				}
			}
		}		


	// >>> Championship match user option panel <<<

		if ( EUROgameType == EURO_championship )
		{
			printf("EUROmatchUsers = %d\n", EUROmatchUsers);
			

			if (  EUROmatchUsers > 1 )
			{
				Image_Heights[UBAR_PANL+Top] =	 PlrSetupPanelHght[ EUROmatchUsers ];

		  		DrawIMAGE( &FrontendBackgroundDEFN, &FrontendTextureDEFN, 
	  				UBAR_PANL+Top, 277, 131, NO_BOX, spritecopy );  	
	  			DrawIMAGE( &FrontendBackgroundDEFN, &FrontendTextureDEFN, 
		  			UBAR_PANL+Btm, 277, 131+(Image_Heights[UBAR_PANL+Top]), NO_BOX, spritecopy );  	

				char	c = 0;

		  		for ( char p=0; p < EUROnoOfMatchPlyrs; p ++ )
				{
					UserSetupList[p]	=	-1;

					if ( p!=user && 
						( UserList[ p ].team == EUROteamA ||
							UserList[ p ].team == EUROteamB) )
					{					
						DisplayString( 406-(PixelLengthOfString( GetTEXT( PSET_LBLS+p ), SMALL_FONT) ) /2,
							(131+19)+(c*23), 
						     	( GetTEXT( PSET_LBLS+p )) , 
							SMALL_FONT, 62, USER_SETUP_BOX+c, &FrontendBackgroundDEFN, &FrontendTextureDEFN  );
						UserSetupList[c] =	p;
					      	c++;
					}
				}
			}
		}		

	// >>> Network game match user option panel <<<


		if ( EUROgameType == EURO_network_game || EUROgameType == EURO_wireplay)
		{
			Image_Heights[UBAR_PANL+Top] =	 56;
	  		DrawIMAGE( &FrontendBackgroundDEFN, &FrontendTextureDEFN, 
	  			UBAR_PANL+Top, 277, 131, NO_BOX, spritecopy );  	
  			DrawIMAGE( &FrontendBackgroundDEFN, &FrontendTextureDEFN, 
	  			UBAR_PANL+Btm, 277, 131+(Image_Heights[ UBAR_PANL+Top ]), NO_BOX, spritecopy );  	
		}




	}

//********************************************************************************************************************************

void	DisplayUserInfo(char user)
	{

	CopyFromBACKtoPSEUDObuffer(
		&FrontendPseudoDEFN, &FrontendBackgroundDEFN,
		12, 130, 240, 82 );

	// *** PLAYERS NAME ***

		if ( UserList[user].player == AUTOPLAYER )

			DisplayString( 40, 144,
			     ( GetTEXT( AUTO_LBLE )), 
				MEDIUM_FONT, 48, NO_BOX, &FrontendPseudoDEFN, &FrontendTextureDEFN  );
		else

		if ( UserList[user].player == PLYR_NOT_CHOSEN )

			DisplayString( 40, 144,
			     ( GetTEXT( SPCT_LBLS+Watch )), 
				MEDIUM_FONT, 48, NO_BOX, &FrontendPseudoDEFN, &FrontendTextureDEFN  );
		else

			DisplayString( 40, 144,
			     ( GetPLAYERSname( UserList[user].player, UserList[user].team, FULL_NAME )) , 
				MEDIUM_FONT, 48, NO_BOX, &FrontendPseudoDEFN, &FrontendTextureDEFN  );

	// *** PLAYERS COUNTRY ***

		int	PAL;

		if	( UserList[user].team == EUROteamA )
			PAL	=	16+8;
		else
			PAL	=	32+8;
		
		if ( UserList[user].player == PLYR_NOT_CHOSEN )
		
		DisplayString( 104,173, ToUPPER(GetTEXT( SPCT_LBLS+Watch )), SMALL_FONT, 
			       48, PLYR_COUNTRY_BOX, &FrontendPseudoDEFN, &FrontendTextureDEFN  );
		else

		DisplayString( 104,173, GetTEAMname( UserList[user].team, 11 ), SMALL_FONT, 
			       PAL, PLYR_COUNTRY_BOX, &FrontendPseudoDEFN, &FrontendTextureDEFN  );

	// *** PLAYERS CONTROL METHOD ***
		
		if ( UserList[user].player == PLYR_NOT_CHOSEN )

		DisplayString( 104,195, ToUPPER(GetTEXT( SPCT_LBLS+Nocntrl )), SMALL_FONT, 
			       62, PLYR_CNTRL_BOX, &FrontendPseudoDEFN, &FrontendTextureDEFN  );
		else

		DisplayString( 104,195, GetTEXT( CNTL_LBLS+UserList[user].control), SMALL_FONT, 
			       62, PLYR_CNTRL_BOX, &FrontendPseudoDEFN, &FrontendTextureDEFN  );

		AddToDumpList( 12, 130, 240, 82 );
	}

//********************************************************************************************************************************

void	DoUserSetup( char MENU, signed char BOX )
	{
		if ( MENU == PLAYER_SETUP && LogicState == RUN_FRONTEND)
		{

		OVERRIDEpal1	    =	48;
		OVERRIDEpal2	    =	62;

	//------- EURO FRIENDLY GAME USER SELECTION -----------------------------------------------------

			if ( EUROgameType == EURO_friendly )
			{
				TeamSelectHighlight =  ControlOptionHighlight( BOX, TEAM_SELECT_BOX,
						       TEAM_SELECTdisp_BOX, TeamSelectHighlight, 
						       TeamSelectHandle, BUTN_LBLS+Done );

				ClearNetUserList();

				if ( BOX == TEAM_SELECT_BOX
					&& ButtonState != 0 )
				  {
					Animation_table[TeamSelectHandle].AnimationSpeed = 
						WhichButton( ButtonState, 0.85);

					ChangeMenu	=	TEAM_SELECT;

				     	DeBounce  	= 	TRUE;
				  }								 	
	 		
				if ( BOX == PLYR_CNTRL_BOX && ButtonState != 0 )
				  {
					if ( ButtonState == LEFT_BUTTON )
						UserList[EUROplyrSetup].control	= 
							LegaliseUserCntrlSelection( UserList[EUROplyrSetup].control, -1 );

					if ( ButtonState == RIGHT_BUTTON )
						UserList[EUROplyrSetup].control	= 
							LegaliseUserCntrlSelection( UserList[EUROplyrSetup].control, 1 );
	
					DisplayUserInfo(EUROplyrSetup);
				     	DeBounce  	= 	TRUE;
				  }								 	

				if ( BOX == PLYR_COUNTRY_BOX && ButtonState != 0 )
				  {
					if ( UserList[EUROplyrSetup].team == EUROteamA )
						UserList[EUROplyrSetup].team = EUROteamB;
					else
						UserList[EUROplyrSetup].team = EUROteamA;

					UserList[EUROplyrSetup].player = AUTOPLAYER;
					DisplayUserInfo(EUROplyrSetup);

					DisplayMatchTeam( EUROteamA, 87,  0,  16, EUROmaxPlayers );
					DisplayMatchTeam( EUROteamB, 352, 12, 32, EUROmaxPlayers );
					AddToDumpList( 82, 241, 146, 216 );
					AddToDumpList( 347,241, 146, 216 );
					DisplayUserTags( EUROteamA, 87,  0 );
					DisplayUserTags( EUROteamB, 352, 12 );
				     	DeBounce  	= 	TRUE;
				  }								 	

				if ( BOX > 0 && BOX<24 && ButtonState != 0 )
				 {
				 	if ( BOX < 11 && ( LegaliseUserPlyrSelection(SquadInfo[ (EUROteamA*20)+BOX ], EUROteamA) == Usable) )
					 {
						UserList[EUROplyrSetup].team 	= EUROteamA;
						UserList[EUROplyrSetup].player  = SquadInfo[ (EUROteamA*20)+BOX ];	//BOX;
						UserList[EUROplyrSetup].TeamHAflag = 0;
						DisplayUserTags( EUROteamA, 87,  0 );
						DisplayUserTags( EUROteamB, 352, 12 );
					 }				    

					else

				 	if ( BOX == 11 )
					 {
						UserList[EUROplyrSetup].team 	= EUROteamA;
						UserList[EUROplyrSetup].player  = AUTOPLAYER;
						UserList[EUROplyrSetup].TeamHAflag = 0;
						DisplayUserTags( EUROteamA, 87,  0 );
						DisplayUserTags( EUROteamB, 352, 12 );
					 }				    

					else
			       
				 	if ( BOX > 12 && BOX < 23 && ( LegaliseUserPlyrSelection( SquadInfo[ (EUROteamB*20)+(BOX-12) ], EUROteamB) == Usable) )
					 {
						UserList[EUROplyrSetup].team 	= EUROteamB;
						UserList[EUROplyrSetup].player  = SquadInfo[ (EUROteamB*20)+(BOX-12) ];	//BOX-12;
						UserList[EUROplyrSetup].TeamHAflag = 1;
						DisplayUserTags( EUROteamA, 87,  0 );
						DisplayUserTags( EUROteamB, 352, 12 );
					 }				    

					else

				 	if ( BOX == 23 )
					 {
						UserList[EUROplyrSetup].team 	= EUROteamB;
						UserList[EUROplyrSetup].player  = AUTOPLAYER;
						UserList[EUROplyrSetup].TeamHAflag = 1;
						DisplayUserTags( EUROteamA, 87,  0 );
						DisplayUserTags( EUROteamB, 352, 12 );
					 }				    

					DisplayMatchTeam( EUROteamA, 87,  0,  16, EUROmaxPlayers );
					DisplayMatchTeam( EUROteamB, 352, 12, 32, EUROmaxPlayers );
					DisplayUserInfo(EUROplyrSetup);

					AddToDumpList( 82, 241, 146, 216 );
					AddToDumpList( 347,241, 146, 216 );

				     	DeBounce  	= 	TRUE;
				 }

	
				CopyFromBACKtoPSEUDObuffer(
					&FrontendPseudoDEFN, &FrontendBackgroundDEFN,
					277, 150,
					Image_Widths[ UBAR_PANL+Top ]-32,
					Image_Heights[ UBAR_PANL+Top ]-18);
				AddToDumpList( 277, 150,
					Image_Widths[ UBAR_PANL+Top ]-32,
					Image_Heights[ UBAR_PANL+Top ]-18);

				if ( BOX >= USER_SETUP_BOX && BOX < (USER_SETUP_BOX+3))
				 {			       
					char	c	=	BOX-USER_SETUP_BOX;

					if ( UserSetupList[c] >= 0 )
				 		DisplayString( 406-(PixelLengthOfString( 
							GetTEXT( PSET_LBLS+UserSetupList[c] ), 
							SMALL_FONT) ) /2,
						 	(131+19)+(c*23), 
						      	( GetTEXT( PSET_LBLS+UserSetupList[c])) , 
						 	SMALL_FONT, 48, USER_SETUP_BOX+c, 
							&FrontendPseudoDEFN, &FrontendTextureDEFN  );

				   	if ( ButtonState != 0 )
				     	{	
	       			   		ChangeMenu	=	PLAYER_SETUP;
				   		EUROplyrSetup	=	UserSetupList[BOX-USER_SETUP_BOX];
				   	     	DeBounce  	= 	TRUE;
		    		   	} 

		    		 }
			}



	//------- NETWORK USER SELECTION --------------------------------------------------------------------


			if ( EUROgameType == EURO_network_game || EUROgameType == EURO_wireplay )
			{
				signed char n;
				n = UserList[0].player;


				if ( TeamOveride )
				{
					ChangeMenu	=	PLAYER_SETUP;
					EUROoveride	=	1;
					TeamOveride	=	0;
					EUROteamA	=	Team_A;		// Setup other users choice of teams.
					EUROteamB	=	Team_B;		// Setup other users choice of teams.
				}

	     			if ( BOX == NET_START_BOX
					&& EURO_NetSelectionMade == No
					&& UserList[0].player != PLYR_NOT_CHOSEN
					&& ButtonState != 0 )
				{
				  	CopyFromBACKtoPSEUDObuffer(
				  		&FrontendPseudoDEFN, &FrontendBackgroundDEFN,
				  		12, 98,
						PixelLengthOfString( GetTEXT ( PSET_HEAD+(EUROgameType-2)), LARGE_FONT), 34 );

					if ( EUROgameType == EURO_network_game )
					{
					  	DisplayString( 12, 98, GetTEXT ( NWRK_LBLS+Netwait ),
					  		LARGE_FONT, 175, NO_BOX, 
					  		&FrontendPseudoDEFN, &FrontendTextureDEFN  );
					  	AddToDumpList( 12, 98, 
							PixelLengthOfString( GetTEXT( NWRK_LBLS+Netwait ), LARGE_FONT),	34 );
					}

			 		else

					if ( EUROgameType == EURO_wireplay )
					{
					  	DisplayString( 12, 98, GetTEXT ( WIRE_LBLS+Wirewait ),
					  		LARGE_FONT, 175, NO_BOX, 
					  		&FrontendPseudoDEFN, &FrontendTextureDEFN  );
				  		AddToDumpList( 12, 98, 
							PixelLengthOfString( GetTEXT( NWRK_LBLS+Netwait ), LARGE_FONT),	34 );
					}

				      	EURO_NetSelectionMade	=	Yes;
				      	Animation_table[NetStartHandle].AnimationSpeed = 0.85;
				      	     	DeBounce  	= 	TRUE;
					

				// run this section - ignores CD test and accepts your player choice...

					if	(TeamChoice < 2)
					{
						TeamChoice+=2;
						SendPlayerInfo();
						TickPause();
						TickPause();
						TickPause();
					}
	
//				// the following line was run if a CD was not found instead of the above...
//						SendNETTeamInfo();	
		    		} 




				if ( BOX == PLYR_CNTRL_BOX && 
				     UserList[0].player != PLYR_NOT_CHOSEN &&
						ButtonState != 0 )
				  {
					if ( ButtonState == LEFT_BUTTON )
						UserList[0].control	= 
							LegaliseUserCntrlSelection( UserList[0].control, -1 );

					if ( ButtonState == RIGHT_BUTTON )
						UserList[0].control	= 
							LegaliseUserCntrlSelection( UserList[0].control, 1 );
	
					DisplayUserInfo(EUROplyrSetup);
				     	DeBounce  	= 	TRUE;
				  }								 	



				if ( BOX>0 && BOX<24 && ButtonState != 0 && EURO_NetSelectionMade == No )
				{
				 	if ( BOX > 0 && BOX < 11 )	//&& ( LegaliseUserPlyrSelection(SquadInfo[ (EUROteamA*20)+BOX ], EUROteamA) == Usable) )
					 {
						UserList[0].team    	= 	EUROteamA;
						UserList[0].player  	= 	SquadInfo[ (EUROteamA*20)+BOX ];	//BOX;
						TeamChoice		=	0;
						PlayerChoice		=	BOX+1;	// because 0 is autoplayer in actua
						UserList[0].TeamHAflag 	= 	0;
						SendPlayerInfo();
						TickPause();
						TickPause();
						TickPause();
						DisplayUserTags( EUROteamA, 87,  0 );
						DisplayUserTags( EUROteamB, 352, 12 );
					 }				    

				 	else
				 
				 	if ( BOX == 11 && TeamA_AUTOplayers < 2 )
				 	 {
				 		UserList[0].team   	= 	EUROteamA;
				 		UserList[0].player 	= 	AUTOPLAYER;
				 		TeamChoice		=	0;
				 		PlayerChoice		=	1;
				 		UserList[0].TeamHAflag 	= 	0;
				 		SendPlayerInfo();
						TickPause();
						TickPause();
				 		TickPause();
				 		DisplayUserTags( EUROteamA, 87,  0 );
				 		DisplayUserTags( EUROteamB, 352, 12 );
				 	 }				    
				 
				 	else
			       	 
				 	if ( BOX > 12 && BOX < 23 )  //&& ( LegaliseUserPlyrSelection( SquadInfo[ (EUROteamB*20)+(BOX-12) ], EUROteamB) == Usable) )
				 	 {
				 		UserList[0].team    	= 	EUROteamB;
				 		UserList[0].player  	= 	SquadInfo[ (EUROteamB*20)+(BOX-12) ]; 
				 		TeamChoice		=	1;
				 		PlayerChoice		=	BOX-10;
				 		UserList[0].TeamHAflag 	= 	1;
				 		SendPlayerInfo();
						TickPause();
						TickPause();
				 		TickPause();
				 		DisplayUserTags( EUROteamA, 87,  0 );
				 		DisplayUserTags( EUROteamB, 352, 12 );
				 	 }				    
				 
				 	else
				 
				 	if ( BOX == 23 && TeamB_AUTOplayers < 2 )
				 	 {
				 		UserList[0].team    	= 	EUROteamB;
				 		UserList[0].player  	= 	AUTOPLAYER;
				 		TeamChoice		=	1;
				 		PlayerChoice		=	1;
				 		UserList[0].TeamHAflag 	= 	1;
				 		SendPlayerInfo();
						TickPause();
						TickPause();
				 		TickPause();
				 		DisplayUserTags( EUROteamA, 87,  0 );
				 		DisplayUserTags( EUROteamB, 352, 12 );
				 	 }				    

					DisplayUserInfo(0);
				     	DeBounce  	= 	TRUE;
				}
				
				if ( EURO_NetSelectionMade == Yes )
				{
					char	Starts	=	0;
					for ( int i=0; i < network_on; i++ )
					{if (NetTeams[i] >= 2) Starts++;}

					if	(Starts==network_on && network_on>1)			
					{
						End_Net_Init();
						EuroNETseed = 12345;
						for ( i=0; i<network_on; i++ )
							NetTeams[i]-=2;
						RunMatch 	=	Yes;
						//ChangeMenu	=	NEXT_MATCH;	//GROUP_FIXTURES;
						ChangeMenu	=	MAIN;
					}
				}

				NetStartHighlight =  ControlOptionHighlight( BOX, NET_START_BOX,
				 	     		NET_STARTdisp_BOX, NetStartHighlight, 
							NetStartHandle, BUTN_LBLS+Done );
				BuildNETuserTable();
				DisplayMatchTeam( EUROteamA, 87,  0,  16, EUROmaxPlayers );
				DisplayMatchTeam( EUROteamB, 352, 12, 32, EUROmaxPlayers );
				AddToDumpList( 82, 241, 146, 216 );
				AddToDumpList( 347,241, 146, 216 );

				if ( EUROgameType== EURO_network_game || EUROgameType == EURO_wireplay)
					DisplayNETinfo();

				if ( keys[1] )	// escape key pressed during selection
				{
					Initial_Quit();											
					ChangeMenu	= MAIN;
				}
			}

	//------- EURO CHAMPIONSHIP USER SELECTION --------------------------------------------------------------------

			if ( EUROgameType == EURO_championship )
			{
				ClearNetUserList();

				TeamSelectHighlight =  ControlOptionHighlight( BOX, TEAM_SELECT_BOX,
						       TEAM_SELECTdisp_BOX, TeamSelectHighlight, 
						       TeamSelectHandle, BUTN_LBLS+Done );

				if ( BOX == PLYR_CNTRL_BOX && ButtonState != 0 )
				  {
					if ( ButtonState == LEFT_BUTTON )
						UserList[EUROplyrSetup].control	= 
							LegaliseUserCntrlSelection( UserList[EUROplyrSetup].control, -1 );

					if ( ButtonState == RIGHT_BUTTON )
						UserList[EUROplyrSetup].control	= 
							LegaliseUserCntrlSelection( UserList[EUROplyrSetup].control, 1 );
	
					DisplayUserInfo(EUROplyrSetup);
				     	DeBounce  	= 	TRUE;
				  }								 	

				if ( BOX == TEAM_SELECT_BOX
					&& ButtonState != 0 )
				  {
					Animation_table[TeamSelectHandle].AnimationSpeed =
						WhichButton( ButtonState, 0.85);
					ChangeMenu	=	NEXT_MATCH;
				     	DeBounce  	= 	TRUE;
				  }								 	
	 		
				if ( BOX > 0 && BOX<12 && ButtonState != 0 )
				 {
				 	if ( BOX < 11 && ( LegaliseUserPlyrSelection( SquadInfo[ (EUROchampTeam*20)+BOX ], EUROchampTeam) == Usable) )
					 {
						UserList[EUROplyrSetup].team 	= EUROchampTeam;
						UserList[EUROplyrSetup].player  = SquadInfo[ (EUROchampTeam*20)+BOX ];
						DisplayUserTags( EUROchampTeam, 87,  0 );
					 }				    

					else

				 	if ( BOX == 11 )
					 {
						UserList[EUROplyrSetup].team 	= EUROchampTeam;
						UserList[EUROplyrSetup].player  = AUTOPLAYER;
						DisplayUserTags( EUROchampTeam, 87,  0 );
					 }				    

					DisplayMatchTeam( EUROchampTeam, 87,  0,  16, EUROnoOfMatchPlyrs );
					DisplayUserInfo(EUROplyrSetup);
					AddToDumpList( 82, 241, 146, 216 );
				     	DeBounce  	= 	TRUE;

				 }

				CopyFromBACKtoPSEUDObuffer(
					&FrontendPseudoDEFN, &FrontendBackgroundDEFN,
					277, 150,
					Image_Widths[ UBAR_PANL+Top ]-32,
					Image_Heights[ UBAR_PANL+Top ]-18);
				AddToDumpList( 277, 150,
					Image_Widths[ UBAR_PANL+Top ]-32,
					Image_Heights[ UBAR_PANL+Top ]-18);

				if ( BOX >= USER_SETUP_BOX && BOX < (USER_SETUP_BOX+3))
				{			       
					char	c	=	BOX-USER_SETUP_BOX;
						if ( UserSetupList[c] >= 0 )
				 		DisplayString( 406-(PixelLengthOfString( 
							GetTEXT( PSET_LBLS+UserSetupList[c] ), 
							SMALL_FONT) ) /2,
					 		(131+19)+(c*23), 
						      	( GetTEXT( PSET_LBLS+UserSetupList[c])) , 
						 	SMALL_FONT, 48, USER_SETUP_BOX+c, 
							&FrontendPseudoDEFN, &FrontendTextureDEFN  );

					   	if ( ButtonState != 0 )
					     	{	
	       				   		ChangeMenu	=	PLAYER_SETUP;
					   		EUROplyrSetup	=	UserSetupList[BOX-USER_SETUP_BOX];
					   	     	DeBounce  	= 	TRUE;
		    			   	} 
	    			}
			}

	//-----------------------------------------------------------------------------------------

    		}
	}

//********************************************************************************************************************************

void	BuildNETuserTable()
	{
		char	p;
		TeamA_AUTOplayers	=	0;
		TeamB_AUTOplayers	=	0;
		ClearNetUserList();

		for (char i=0; i<network_on; i++)
		{
			if	( NetTeams[i] != -1 )
			{
				p  =  (  ( (NetTeams[i] & 1)*11)+Players[i])-1;
				
				if ( p == 0 )
					TeamA_AUTOplayers++;
				if ( p == 11 )
					TeamB_AUTOplayers++;
				if (p!=0 && p!=11)
					UserNetList[p] = 1; 

				if ( TeamA_AUTOplayers > 1 )
					UserNetList[11]	= 1; 
			       	if ( TeamB_AUTOplayers > 1 )
			       		UserNetList[23]	= 1; 
			}		
		}

	}


//********************************************************************************************************************************

void	DisplayNETinfo()
	{

	char  ammount[5];
	char	*string1;

		if ( EUROgameType == EURO_network_game || EUROgameType == EURO_wireplay)
	 	{
			CopyFromBACKtoPSEUDObuffer(
				&FrontendPseudoDEFN, &FrontendBackgroundDEFN,
				277, 131, 258, 60);

			if ( EUROgameType == EURO_network_game )			
				string1  = GetTEXT( NWRK_LBLS+Netusers );
			else	
				string1  = GetTEXT( WIRE_LBLS+Netusers );

			char	*number1  = itoa( network_on, ammount, 10 );
			
			DisplayString( 406-
				( (PixelLengthOfString( string1, SMALL_FONT))+
				(  PixelLengthOfString( number1, SMALL_FONT)) ) /2, 150, 
				string1, SMALL_FONT, 48, NO_BOX, 
				&FrontendPseudoDEFN, &FrontendTextureDEFN  );

			DisplayString( NextXposn, 150, 
				number1, SMALL_FONT, 48, NO_BOX, 
				&FrontendPseudoDEFN, &FrontendTextureDEFN  );

			char	*string2    = GetTEXT( NWRK_LBLS+Tochoose );
			char	*number2  = itoa( CountNumberOfNETstarts(), ammount, 10 );

			DisplayString( 406-
				( (PixelLengthOfString( string2, SMALL_FONT))+
				(  PixelLengthOfString( number2, SMALL_FONT)) ) /2, 173, 
				string2, SMALL_FONT, 48, NO_BOX, 
				&FrontendPseudoDEFN, &FrontendTextureDEFN  );

			DisplayString( NextXposn, 173, 
				number2, SMALL_FONT, 48, NO_BOX, 
				&FrontendPseudoDEFN, &FrontendTextureDEFN  );

			AddToDumpList( 277, 131, 258, 60);
		}	
	}

//********************************************************************************************************************************

char	LegaliseUserPlyrSelection( char player, char team )
	{
	char	plyr      =  Usable;
	char	p;

		if ( EUROgameType != EURO_championship )
		{
			for ( p=0; p < EUROmaxPlayers; p ++ )
			{
				if ( p != EUROplyrSetup &&
					( UserList[p].team==team && UserList[p].player == player ) )
						plyr	= Unusable;
			}
		}

	else

		{
			for ( p=0; p < EUROnoOfMatchPlyrs; p ++ )
			{
				if ( p != EUROplyrSetup &&
					( UserList[p].team==team && UserList[p].player == player ) )
						plyr	= Unusable;
			}
		}
		 	
	return(plyr);

	}

//********************************************************************************************************************************

void	SetupChampionshipCntrls( char gametype)
	{
		if ( gametype == EURO_championship )
		{

			char	CntrlList[16];
			char	CntrlReset = 0;
			char 	FirstCntrl = 0;
			char	ScndMatchUser  = 0;

			memset( &CntrlList[0], 0, 16 );

	//--------------------------------------------------------------

		// we must first find out if any of the devises are being used by more than one player.			
			
		   	for ( char p=0; p < EUROnoOfMatchPlyrs; p ++ )
 			{
				if ( (UserList[p].team == EUROteamA || 
				      UserList[p].team == EUROteamB ) &&
					(UserList[p].control>=0 && 
					UserList[p].control < 17)   )
				{
						CntrlList[ UserList[p].control ]++;

					if ( CntrlList[ UserList[p].control ] > 1 )
						CntrlReset = 1;					
				}

				else

				if ( (UserList[p].team == EUROteamA || 
				      UserList[p].team == EUROteamB ) &&
					( UserList[p].control == -1 || 
					  CtrlFlags[ UserList[p].control ] != Usable) )
						CntrlReset    = 1;					
			}				

	//--------------------------------------------------------------

		// an illegal control method (too many of the same control devise) was found so legalise other users
		// control methods.

			if ( CntrlReset != 0 )
			{

				if (EUROverbose)
					printf("illegal control devise.\n");

				FirstCntrl    = 15;

			   	for ( char u = 0; u < EUROnoOfMatchPlyrs; u ++ )
				{
					if ( UserList[u].team == EUROteamA || 
					     UserList[u].team == EUROteamB )
					{
						FirstCntrl =  LegaliseUserCntrlSelection( FirstCntrl, 1 );
						UserList[u].control = FirstCntrl;
					}
				}
			}
	//--------------------------------------------------------------

		}
	}

//********************************************************************************************************************************

char	LegaliseUserCntrlSelection( char cntl, signed char dir )
	{
		char	control      =  Unusable;
		char	current_cntr =	cntl;
		
	 	while	( control == Unusable )
		{
			cntl+=	dir;			
			cntl&=	15;

			if ( ( CtrlFlags[ cntl ] == Usable) || cntl == current_cntr )
				control	= Usable;


				if ( EUROgameType != EURO_championship )
				{
					for ( char p=0; p < EUROmaxPlayers; p ++ )
					{
						if ( p != EUROplyrSetup && 
				       			cntl!= current_cntr &&
							UserList[p].control == cntl )

  							UserList[p].control = current_cntr;
				  	}
	 			}

				else

				{
		   			for ( char p=0; p < EUROnoOfMatchPlyrs; p ++ )
 					{
 						if ( p != EUROplyrSetup && 
							(UserList[p].team == EUROteamA || 
							 UserList[p].team == EUROteamB ) &&
 				       			cntl!= current_cntr &&
 							UserList[p].control == cntl )
  						
						UserList[p].control = current_cntr;
	 			  	}
				}			
		}

		return(cntl);		
	}

//********************************************************************************************************************************

void	DisplayUserTags( char Team, short Xposn, char box_offset )
	{
		char	plyr;
		short	x	= Xposn+PixelLengthOfString(GetTEXT( AUTO_LBLE ),SMALL_FONT)+32;
		short	y;
		short	autocnt	= 0;

	 	CopyFromBACKtoPSEUDObuffer(
			&FrontendPseudoDEFN, &FrontendBackgroundDEFN,
			Xposn-52, 243, 20, 195+34);
	 	CopyFromBACKtoPSEUDObuffer( &FrontendPseudoDEFN, &FrontendBackgroundDEFN,
			x, 440,	60, 34 );

  		for ( char s=0; s < 11; s ++ )
		{
			plyr	=	SquadInfo[ (Team*20)+s ];

			if ( EUROgameType == EURO_friendly )
			{

//		  		for ( char p=0; p < EUROmaxPlayers; p ++ )
		  		for ( char p=0; p < EUROnoOfMatchPlyrs; p ++ )
				{
					if ( (UserList[p].team == Team && 
					      UserList[p].player == plyr ) &&
						     (UserList[ EUROplyrSetup ].team == Team &&
					      UserList[EUROplyrSetup].player == plyr ) )
				      		DisplayString( (Xposn-42)-(PixelLengthOfString( GetTEXT( UTAG_LBLS+p ), SMALL_FONT) ) /2, 
					      	     (242+( s * 18)), ( GetTEXT ( UTAG_LBLS+p )) , 
					      	     SMALL_FONT, 62, NO_BOX, &FrontendPseudoDEFN, &FrontendTextureDEFN  );
				}
			}


			if ( ( EUROgameType == EURO_network_game || EUROgameType == EURO_wireplay ) &&
				(UserList[0].team == Team && 
				         ( UserList[0].player == plyr || UserList[0].player==AUTOPLAYER) ))
			{ 						
				        if ( UserList[0].player == plyr )
						y = 241+(s*18);
					else
						y = 438;			 		

   		      		DisplayString( (Xposn-37)-(PixelLengthOfString( GetTEXT( UTAG_LBLS+4 ), LARGE_FONT) ) /2, 
   			      	     y, ( GetTEXT ( UTAG_LBLS+Auto )), 
   			      	     LARGE_FONT, 62, NO_BOX, &FrontendPseudoDEFN, &FrontendTextureDEFN  );
			}
    		}




			if ( EUROgameType == EURO_friendly )
			{
//		  		for ( char a=0; a < EUROmaxPlayers; a ++ )
		  		for ( char a=0; a < EUROnoOfMatchPlyrs; a ++ )

				{
					if	( UserList[a].team == Team &&
						UserList[a].player == AUTOPLAYER )
			      		{
		      	
			      			if ( EUROplyrSetup == a )
			       			      	DisplayString( (Xposn-42)-(PixelLengthOfString( GetTEXT( UTAG_LBLS+a ), SMALL_FONT) ) /2, 
		      				      	     440, ( GetTEXT ( UTAG_LBLS+a )) , 
		      				      	     SMALL_FONT, 62, NO_BOX, &FrontendPseudoDEFN, &FrontendTextureDEFN  );

			      			else

			      			{
		      					x = Xposn+PixelLengthOfString(GetTEXT( AUTO_LBLE ),SMALL_FONT)+32;
			      
		      			  		DrawIMAGE( &FrontendPseudoDEFN, &FrontendTextureDEFN, 
		  	      					PLYR_TAGB, x-2+autocnt, 438, NO_BOX, straightcopy );  	
		      			
			      				DisplayString( x+10-((PixelLengthOfString( GetTEXT( UTAG_LBLS+a ), SMALL_FONT) ) /2)+autocnt, 
			      				     440, ( GetTEXT ( UTAG_LBLS+a )) , 
		      					     SMALL_FONT, 55, NO_BOX, &FrontendPseudoDEFN, &FrontendTextureDEFN  );
		      					autocnt+=20;
			      			}
			      		}
				}
			}



			AddToDumpList( Xposn-52, 243, 20, 195+34 );
			AddToDumpList( x, 440, 60, 34 );
	}

//********************************************************************************************************************************

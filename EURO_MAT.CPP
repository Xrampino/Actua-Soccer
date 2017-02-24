#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
#include <i86.h>
#include <dos.h>
#include <conio.h>
#include <float.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include "defines.h"
#include "data.equ"
#include "3deng.h"
#include "intronet.h"
#include "sos.h"
#include "audio.h"
#include "digi.h"
#include "midi.h"
#include "config.h"
#include "timer.h"
#include "mallocx.h"
#include "unmangle.h"
#include "gamedata.h"

#include "eurodefs.h"
#include "euro_fxd.h"
#include "euro.equ"
#include "euro_sym.h"
#include "euro_def.h"
#include "euro_var.h"
#include "euro_mem.h"
#include "euro_spt.h"
#include "euro_gen.h"
#include "euro_grf.h"
#include "euro_cnt.h"
#include "euro_dsk.h"
#include "euro_sqd.h"
#include "euro_sel.h"
#include "euro_fix.h"
#include "euro_usr.h"
#include "euro_inf.h"
#include "euro_gdv.h"
#include "euro_win.h"
#include "euro_net.h"
#include "euro_cmd.h"
#include "euro_rnd.h"
#include "euro_int.h"

extern	 char	suspend_audio;
extern	 int	music_state;
extern 	 void	init_keyboard();
extern 	 void 	init_users();
extern 	 void 	init_team();
extern 	 "C" 	char old_mf;
extern   "C"	int  x1ok;
extern   "C"	int  y1ok;
extern   "C"	int  x2ok;
extern   "C"	int  y2ok;
extern   "C"	int  bitaccept;
extern 	 match(int argc, char **argv);

struct passback_per{
	short per;
	short inj;
	char dpts;
	};

extern passback_per performance[40];

//********************************************************************************************************************************

void	setup_player_data(int team_no)
{
}							

//********************************************************************************************************************************

void	get_cup_venue()
{
}

//********************************************************************************************************************************

void	PlayMatch(int argc, char **argv)
	{
		char	CommsSetup;

		if ( EUROgameType == EURO_network_game || 
		     EUROgameType == EURO_wireplay ||
		     EUROgameType == EURO_serial_game ||
		     EUROgameType == EURO_modem_game )
			CommsSetup	=	Yes;
		else			
			CommsSetup	=	No;







// old actua		suspend_audio	=	1;
// old actua	   	StopSong();
// old actua	   	music_state	=	NULL;


		if (EUROverbose)
			printf("\n  DEALLOCATING MEMORY BEFORE RUNNING MATCH.\n\n");

		DeAllocateTexturePages();
		DeAllocateDisplayBuffers();
	   	init_keyboard();
	   	init_users();

	   	key_togs[0x2f] = match_info.vidi;
// old actua	   	setup.stadium  = 1;

	   	if (!network_on)
	   		old_mf	=	TRUE;
	   	else
	   		old_mf	=	FALSE;

		x1ok		=	NULL;
		x2ok		=	NULL;
		y1ok		=	NULL;
		y1ok		=	NULL;
		bitaccept	=	NULL;

// old actua		if (cal0!=NULL)
// old actua		{			
// old actua			x1ok 	  = 1;	
// old actua			y1ok 	  = 2;	
// old actua			bitaccept|= (x1ok+y1ok);
// old actua		}
// old actua
// old actua
// old actua		if (cal1!=NULL)
// old actua		{			
// old actua			x2ok 	  = 4;	
// old actua			y2ok 	  = 8;	
// old actua			bitaccept|= (x2ok+y2ok);
// old actua		}

		setup.stadium	=	match_info.venue;


// old actua		key1[UP_KEY]	=	InsertKey(batch_info.keys_used[UP_RED]);	//0x1e;	       
// old actua		key1[DN_KEY]	=	InsertKey(batch_info.keys_used[DN_RED]);	//0x2c;	       
// old actua		key1[LF_KEY]	=	InsertKey(batch_info.keys_used[LF_RED]);	//0x33;	       
// old actua		key1[RT_KEY]	=	InsertKey(batch_info.keys_used[RT_RED]);	//0x34;	       
// old actua		key1[F1_KEY]	=	InsertKey(batch_info.keys_used[F1_RED]);	//0x10;	       
// old actua		key1[F2_KEY]	=	InsertKey(batch_info.keys_used[F2_RED]);	//0x35;	      
// old actua
// old actua		key2[UP_KEY]	=	InsertKey(batch_info.keys_used[UP_RED+6]);	//-0x48;    
// old actua		key2[DN_KEY]	=	InsertKey(batch_info.keys_used[DN_RED+6]);	//-0x50;    
// old actua		key2[LF_KEY]	=	InsertKey(batch_info.keys_used[LF_RED+6]);	//-0x4b;    
// old actua		key2[RT_KEY]	=	InsertKey(batch_info.keys_used[RT_RED+6]);	//-0x4d;    
// old actua		key2[F1_KEY]	=	InsertKey(batch_info.keys_used[F1_RED+6]);	//0x52;	    
// old actua		key2[F2_KEY]	=	InsertKey(batch_info.keys_used[F2_RED+6]);	//0x53;	    
// old actua

// to add 		match_info.team_a_score		=	0;
// to add 		match_info.team_b_score		=	0;
// to add 		match_info.team_a_penalties	=	0;
// to add 		match_info.team_b_penalties	=	0;
// to add 		match_info.penalties		=	0;
// to add 		match_info.extra		=	0;

// old actua		if (keyboard==0)
// old actua	 		InitialiseMOUSE();


		//ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป 
		//บ                                                              บ
		//บ MATCH SETUP MODULE-> PASSING FRONTEND DATA TO ANDY's SECTION บ
		//บ                                                              บ
		//ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ 

			EUROmatch_info.GameType	=	EUROgameType;

			if ( CommsSetup == Yes )
				{
					EUROmatch_info.rand		=	1234;
					EUROmatch_info.offside		=	Off;
					EUROmatch_info.wind		=	Off;
					EUROmatch_info.substitutes	=	Off;
					EUROmatch_info.bookings		=	Off;
					EUROmatch_info.freekicks	=	Off;

					match_info.rand		=	1234;
					match_info.offside	=	Off;
					match_info.wind		=	Off;
					match_info.substitutes	=	Off;
					match_info.bookings	=	Off;
					match_info.freekicks	=	Off;

			   		old_mf				=	FALSE;
				}

			else

				{			
					EUROmatch_info.rand		=	GetRnd2();
					EUROmatch_info.offside		=	EUROoffside;
					EUROmatch_info.wind		=	EUROwind;
					EUROmatch_info.substitutes	=	EUROsubs;
					EUROmatch_info.bookings		=	EURObookings;
					EUROmatch_info.freekicks	=	EUROfouls;

					match_info.rand		=	GetRnd2();
					match_info.offside 	=	EUROoffside;
					match_info.wind		=	EUROwind;
					match_info.substitutes	=	EUROsubs;
					match_info.bookings 	=	EURObookings;
					match_info.freekicks	=	EUROfouls;

			   		old_mf				=	TRUE;
				}

			EUROmatch_info.camera		=	EUROcamera;
			EUROmatch_info.audio		=	EUROaudio;
			EUROmatch_info.crowd		=	EUROcrowd;
			EUROmatch_info.pitch		=	EUROpitch;
			EUROmatch_info.commentary	=	EUROcommentary;
			EUROmatch_info.music		=	EUROmusic;
			EUROmatch_info.master		=	EUROmaster;
			EUROmatch_info.timeit		=	EUROtimeit;
			EUROmatch_info.vidi		=	EUROvidi;
			EUROmatch_info.time		=	EUROtime;
			EUROmatch_info.tga_enable	=	EUROtga;
						
			match_info.camera		=	EUROcamera;
			match_info.audio		=	EUROaudio;
			match_info.crowd		=	EUROcrowd;
			match_info.pitch		=	EUROpitch;
			match_info.commentary		=	EUROcommentary;
			match_info.music		=	EUROmusic;
			match_info.master		=	EUROmaster;
			match_info.timeit		=	EUROtimeit;
			match_info.vidi			=	EUROvidi;
			match_info.time			=	EUROtime;
			match_info.tga_enable		=	EUROtga;

			EUROmatch_info.tac_1		=	0;
			EUROmatch_info.tac_2		=	0;

			match_info.tac_1		=	0;
			match_info.tac_2		=	0;

			EUROmatch_info.Team_A_goals  	=	0;		
			EUROmatch_info.Team_B_goals  	=	0;		
			EUROmatch_info.penalties     	=	0;
			EUROmatch_info.extra	     	=	0;
			EUROmatch_info.Team_A_penalties	=	0;
			EUROmatch_info.Team_B_penalties	=	0;
			EUROmatch_info.return_mins	=	0;
			EUROmatch_info.language		=	0;

			match_info.team_a_score  	=	0;		
			match_info.team_b_score  	=	0;		
			match_info.penalties     	=	0;
			match_info.extra	     	=	0;
			match_info.team_a_penalties	=	0;
			match_info.team_b_penalties	=	0;
			match_info.return_mins		=	0;
			match_info.language		=	0;


			setup.stadium		     	= 	EUROvenue;
			setup.detail.sky     		=	EUROsky;
			setup.detail.lines   		=	EUROlineDetail;
			setup.vidi_type      		=	EUROvidiType;
			setup.detail.players 		=	EUROplyrDetail;
			setup.detail.pitch   		=	EUROptchDetail;
			setup.start_res  		=	EUROresoln;
			setup.screen_size   		=	EUROscrSize;

			setup.team_a			=	EUROteamA;
			setup.team_b			=	EUROteamB;

			for (char c=0; c<4; c++)
			{EUROmatch_info.CntrlTypes[c] = -1;}

			EUROmatch_info.TeamA_users	=	0;
			EUROmatch_info.TeamB_users	=	0;
			char	UserFlag 	= 	1;
			char	CntrlCnt 	= 	0;


		// Euro Championship / Friendly / Practice games

			for (char u=0; u<EUROnoOfMatchPlyrs; u++)
			{		
		   	 	if (EUROverbose)
					printf("    User %d	%s\n", u,
						GetTEAMname( UserList[u].team, 11) );					
				
				if ( UserList[u].team == setup.team_a )
				{
					EUROmatch_info.TeamA_users|=	UserFlag;			
					EUROmatch_info.CntrlTypes[CntrlCnt] = UserList[u].control;
					EUROmatch_info.PlyrTypes[CntrlCnt] = UserList[u].player;
					UserFlag+=	UserFlag;
					CntrlCnt++;
				}

				if ( UserList[u].team == setup.team_b )
				{
					EUROmatch_info.TeamB_users|=	UserFlag;			
					EUROmatch_info.CntrlTypes[CntrlCnt] = UserList[u].control;
					EUROmatch_info.PlyrTypes[CntrlCnt] = UserList[u].player;
					UserFlag+=	UserFlag;
					CntrlCnt++;
				}
			}

		//ษอออออออออออออออออออออออออออออออออออออออออออออป 
		//บ                                             บ
		//บ COPY BOTH TEAMS PLAYER DATA INTO MATCH INFO บ
		//บ                                             บ
		//ศอออออออออออออออออออออออออออออออออออออออออออออผ 

		strcpy( &EUROmatch_info.TeamAname[0], GetTEAMname( EUROteamA, 11) );
		strcpy( &EUROmatch_info.TeamBname[0], GetTEAMname( EUROteamB, 11) );
		memcpy( &EUROmatch_info.TeamAsquad[0], &SquadInfo[ (EUROteamA*20) ], 20 );
		memcpy( &EUROmatch_info.TeamBsquad[0], &SquadInfo[ (EUROteamB*20) ], 20 );

		if (EUROverbose)
		{
			printf("\n  MATCH INTERFACE DATA:\n\n");
			printf("    Home Team:  %s\n",   &EUROmatch_info.TeamAname[0] );
			printf("    Away Team:  %s\n\n", &EUROmatch_info.TeamBname[0] );
		}

		short	PlyrIndex1, PlyrIndex2;		

			for (char p=0; p<20; p++)
			{		

				PlyrIndex1 = NormalisePlayer( p, EUROteamA );
				PlyrIndex2 = NormalisePlayer( p, EUROteamB );
				
				EUROmatch_info.TeamA[p].pace	   	=	Pace[ PlyrIndex1 ];
				EUROmatch_info.TeamA[p].power	   	=	Power[ PlyrIndex1 ];
				EUROmatch_info.TeamA[p].control	   	=	Control[ PlyrIndex1 ];
				EUROmatch_info.TeamA[p].flair	   	=	Flair[ PlyrIndex1 ];
				EUROmatch_info.TeamA[p].vision	   	=	Vision[ PlyrIndex1 ];
				EUROmatch_info.TeamA[p].accuracy   	=	Accuracy[ PlyrIndex1 ];
				EUROmatch_info.TeamA[p].stamina   	=	Stamina[ PlyrIndex1 ];
				EUROmatch_info.TeamA[p].discipline 	=	Discipline[ PlyrIndex1 ];
				EUROmatch_info.TeamA[p].fitness 	=	Fitness[ PlyrIndex1 ];

				if (EUROverbose)
				{
					printf("plyr %d	(%d)  pace: %d  power: %d  cntrl: %d  flair: %d  vision: %d  accry: %d  stam: %d  disc: %d  fit: %d\n",
						p, PlyrIndex1,		
						EUROmatch_info.TeamA[p].pace,
						EUROmatch_info.TeamA[p].power,	  
						EUROmatch_info.TeamA[p].control,	  
						EUROmatch_info.TeamA[p].flair,	  
						EUROmatch_info.TeamA[p].vision,	  
						EUROmatch_info.TeamA[p].accuracy,  
						EUROmatch_info.TeamA[p].stamina,   
						EUROmatch_info.TeamA[p].discipline,
						EUROmatch_info.TeamA[p].fitness);
				}
			
				EUROmatch_info.TeamB[p].pace		=	Pace[ PlyrIndex2 ];
				EUROmatch_info.TeamB[p].power		=	Power[ PlyrIndex2 ];
				EUROmatch_info.TeamB[p].control		=	Control[ PlyrIndex2 ];
				EUROmatch_info.TeamB[p].flair		=	Flair[ PlyrIndex2 ];
				EUROmatch_info.TeamB[p].vision		=	Vision[ PlyrIndex2 ];
				EUROmatch_info.TeamB[p].accuracy	=	Accuracy[ PlyrIndex2 ];
				EUROmatch_info.TeamB[p].stamina  	=	Stamina[ PlyrIndex2 ];
				EUROmatch_info.TeamB[p].discipline 	=	Discipline[ PlyrIndex2 ];
				EUROmatch_info.TeamB[p].fitness 	=	Fitness[ PlyrIndex2 ];

			}


		//ษอออออออออออออออออออออออออออออออออออออออออออออออออออออออป 
		//บ                                                       บ
		//บ VERBOSE INFORMATION, DISPLAYS MATCH DATA IF REQUESTED บ
		//บ                                                       บ
		//ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออผ 

		    	if (EUROverbose)
			{
				printf("    Number Of Users Playing Next Match:  %d\n",CntrlCnt);
				for (char u=0; u<CntrlCnt; u++)
				{printf("    User %d	%s\n", 
					u, GetTEXT( CNTL_LBLS+EUROmatch_info.CntrlTypes[u]) );}

			 	

			}


//		EUROmatch_info.EscKey = CntrlCnt;

		//ษอออออออออออออออป 
		//บ               บ
		//บ EXECUTE MATCH บ
		//บ               บ
		//ศอออออออออออออออผ 

		   	init_team();

//			setup.team_a			=	0;
//			setup.team_b			=	1;

			EUROmatch_info.referee_vision		=	EUROref_vision;
			EUROmatch_info.referee_discipline	=	EUROref_discipline;
			match_info.bookings		=	EURObookings;

			strcpy( &EUROmatch_info.RefsName[0], "TOM JONES" );

		    	if (EUROverbose)
			{
				printf("\n  MATCH AND ENVIRONMENT SETTINGS.\n\n");
					printf("    Bookings:		%s\n", GetTEXT( SETG_TEXT+(EUROmatch_info.bookings & 1) ) );
					printf("    Freekicks:		%s\n", GetTEXT( SETG_TEXT+(EUROmatch_info.freekicks & 1) ) );
			}


		



	 		EUROerror|=	match(argc,argv);

			Results[MatchNumber].HomeScore  = EUROmatch_info.Team_A_goals;
			Results[MatchNumber].AwayScore  = EUROmatch_info.Team_B_goals;


			if ( MatchNumber > 23 )
			{		
				Results[MatchNumber].AfterExtra = EUROmatch_info.extra;
				Results[MatchNumber].AfterPens  = EUROmatch_info.penalties;
				Results[MatchNumber].HomePens   = EUROmatch_info.Team_A_penalties;
				Results[MatchNumber].AwayPens   = EUROmatch_info.Team_B_penalties;
				Results[MatchNumber].WinningTeam = EUROteamA;
				Results[MatchNumber].Message 	= ProceedToNextRnd;

				if ( EUROmatch_info.extra == 0 && EUROmatch_info.penalties == 0 )
				{
					Results[MatchNumber].Message 	= ProceedToNextRnd;

					if ( EUROmatch_info.Team_A_goals > EUROmatch_info.Team_B_goals )
						Results[MatchNumber].WinningTeam = EUROteamA;
					else						
						Results[MatchNumber].WinningTeam = EUROteamB;
				}

				else

				if ( EUROmatch_info.extra != 0 && EUROmatch_info.penalties == 0 )
				{
					Results[MatchNumber].Message 	= ExtraTime;

					if ( EUROmatch_info.Team_A_goals > EUROmatch_info.Team_B_goals )
						Results[MatchNumber].WinningTeam = EUROteamA;
					else						
						Results[MatchNumber].WinningTeam = EUROteamB;
				}

				else

				if ( EUROmatch_info.extra != 0 && EUROmatch_info.penalties == 0 )
				{
					Results[MatchNumber].Message 	= Penalties;

					if ( EUROmatch_info.Team_A_penalties > EUROmatch_info.Team_B_penalties )
						Results[MatchNumber].WinningTeam = EUROteamA;
					else						
						Results[MatchNumber].WinningTeam = EUROteamB;
				}
			
			}
			



//			ProcessResultData(MatchNumber);	
					     
			for (p=0; p<20; p++)
			{		
				PlyrIndex1 = NormalisePlayer( p, EUROteamA );
				PlyrIndex2 = NormalisePlayer( p, EUROteamB );

//				printf("home index %d	=	%d\n", p, PlyrIndex1);
				
				if ( performance[p].inj > Fitness[PlyrIndex1] )
					Fitness[PlyrIndex1] = 1;
				else
					Fitness[PlyrIndex1]-=    performance[p].inj;				

				DiscPts[PlyrIndex1]+=    performance[p].dpts;				

				if ( performance[p+20].inj > Fitness[PlyrIndex2] )
					Fitness[PlyrIndex2] = 1;
				else
					Fitness[PlyrIndex2]-=    performance[p+20].inj;				

				DiscPts[PlyrIndex2]+=    performance[p+20].dpts;				

				if ( Fitness[PlyrIndex1] < 10 ) 
					Fitness[PlyrIndex1] = 10;
				if ( Fitness[PlyrIndex2] < 10 ) 
					Fitness[PlyrIndex2] = 10;

//				printf("     A dpts %d\n", performance[p].dpts );
//				printf("     B dpts %d\n", performance[p+20].dpts );
			}

			printf	("\n\n");
			
			DoInjuriesAndMatchBans( EUROgameType, EUROteamA );
			DoInjuriesAndMatchBans( EUROgameType, EUROteamB );

		//ษอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป 
		//บ                                                                   บ
		//บ RESET FRONTEND VARIABLES WHICH MAY HAVE BEEN ALTERED DURING MATCH บ
		//บ                                                                   บ
		//ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ 

			EUROcamera			=	EUROmatch_info.camera;
			EUROvidi			=	EUROmatch_info.vidi;
			EUROscrSize			=	setup.screen_size;
			EUROsky				=  	setup.detail.sky;
			EUROlineDetail			=	setup.detail.lines;
			EUROvidiType			=	setup.vidi_type;
			EUROplyrDetail			=	setup.detail.players;
			EUROptchDetail			=	setup.detail.pitch;
			EUROresoln			=	setup.start_res;
			EUROscrSize			=	setup.screen_size;

		    	if (EUROverbose)
				printf("\n  ALLOCATING MEMORY AFTER RUNNING MATCH AND RETURNING TO FRONTEND.\n\n");

			AllocateDisplayBuffers();     				// Allocates two 640x480 display buffers.

			TexturePageMemHandle =					// Set up memory handle.
				AllocateTexturePageMemory( 8, 			// Specify number of texture pages to allocate.
				&FrontendTextureDEFN );				// Allocate memory for frontend texture pages.
			LoadTexturePage( BIN_PAGE1, 	       			// Load texture page 1 into texture memory.
				 &EuroDATfile[0],
				 0, &FrontendTextureDEFN );
			Set_640x480_VideoMode();

			RunMatch 	= 	No;


			if ( EUROgameType == EURO_championship )
			{

				//ษอออออออออออออออป 
				//บ               บ
				//บ  GROUP MATCH  บ
				//บ               บ
				//ศอออออออออออออออผ 

				if ( MatchNumber < 24 )
				{
					LeagueTable[EUROteamA].goalsFor     = EUROmatch_info.Team_A_goals;
					LeagueTable[EUROteamA].goalsAgainst = EUROmatch_info.Team_B_goals;
					LeagueTable[EUROteamB].goalsFor     = EUROmatch_info.Team_B_goals;
					LeagueTable[EUROteamB].goalsAgainst = EUROmatch_info.Team_A_goals;

					if ( EUROmatch_info.Team_A_goals > EUROmatch_info.Team_B_goals )
					{
						LeagueTable[EUROteamA].won++;
						LeagueTable[EUROteamB].lost++;
					}

					else

					if ( EUROmatch_info.Team_A_goals < EUROmatch_info.Team_B_goals )
					{
						LeagueTable[EUROteamA].lost++;
						LeagueTable[EUROteamB].won++;
					}

					else

					if ( EUROmatch_info.Team_A_goals == EUROmatch_info.Team_B_goals )
					{
						LeagueTable[EUROteamA].drew++;
						LeagueTable[EUROteamB].drew++;
					}

				}

				MatchNumber++;


				//-----------------------------------------------------------------------
				// Were to go after a match has been played....

								//======================================
					if ( MatchNumber<25 )	// N.B. this is 29 so final tables
								//      are displayed before qualifiers.
							    	//======================================
					  	ChangeMenu	=	GROUP_FIXTURES;
				else
					if ( MatchNumber<29 )
					   	ChangeMenu	=	QUARTER_FINALS;
				else
					if ( MatchNumber<31 )
					   	ChangeMenu	=	SEMI_FINALS;

				else
				    		ChangeMenu	=	MAIN;

				//-----------------------------------------------------------------------


			}

			else

			if ( EUROgameType == EURO_wireplay )
 			      ChangeMenu = EXIT_FRONTEND;
			else				
			      ChangeMenu = MAIN;
	}

//********************************************************************************************************************************

void DisplayExtMatchTeams()
	{
	 	DisplayString( 
	 		132-(PixelLengthOfString(GetTEAMname( EUROteamA, 11 ), LARGE_FONT)/2),
	 		414,
	 		GetTEAMname( EUROteamA, 11 ),
	 		LARGE_FONT, 
	 		43,
	 		EURO_TEAMa_BOX,
	 		&FrontendPseudoDEFN, &FrontendTextureDEFN  );

	 	DisplayString( 
	 		340-(PixelLengthOfString(GetTEAMname( EUROteamB, 11 ), LARGE_FONT)/2),
	 		414,
	 		GetTEAMname( EUROteamB, 11 ),
	 		LARGE_FONT, 
	 		50,
	 		EURO_TEAMb_BOX,
	 		&FrontendPseudoDEFN, &FrontendTextureDEFN  );

		memcpy( &PaletteBuffer[44*3], &SparePaletteBuffer[ (LeagueColourOffsets[EUROteamA]*3)+3 ], 7*3 );
		memcpy( &PaletteBuffer[51*3], &SparePaletteBuffer[ (LeagueColourOffsets[EUROteamB]*3)+3 ], 7*3 );

	}


//********************************************************************************************************************************

void	DisplayNextMatchUsers( char gametype )
	{
		if ( gametype == EURO_championship )
		{
			char UserText[128];

			strcpy(UserText, GetTEXT ( MUSR_LBLS+ComputerUser) );
			char Uflag = 0;

			for (char u=0; u<EUROnoOfMatchPlyrs; u++)
			{		
				if ( UserList[u].team == EUROteamA )
				{
					if ( Uflag == 0 )
						strcpy(UserText, GetTEXT ( MUSR_LBLS+u) );
					else

					{
						strcat(UserText, " & ");
						strcat(UserText, GetTEXT ( MUSR_LBLS+u) );
					}

					Uflag++;
				}
		   	}

			DisplayString( 125-(PixelLengthOfString( UserText, SMALL_FONT) /2 ), 460, 
			   UserText,
			   SMALL_FONT, 36, NO_BOX, 
			   &FrontendPseudoDEFN, &FrontendTextureDEFN  );

			strcpy(UserText, GetTEXT ( MUSR_LBLS+ComputerUser) );
			Uflag = 0;

			for (u=0; u<EUROnoOfMatchPlyrs; u++)
			{		
				if ( UserList[u].team == EUROteamB )
				{
					if ( Uflag == 0 )
						strcpy(UserText, GetTEXT ( MUSR_LBLS+u) );
					else

					{
						strcat(UserText, " & ");
						strcat(UserText, GetTEXT ( MUSR_LBLS+u) );
					}

					Uflag++;
				}
		   	}

			DisplayString( 347-(PixelLengthOfString( UserText, SMALL_FONT) /2 ), 460, 
			   UserText,
			   SMALL_FONT, 36, NO_BOX, 
			   &FrontendPseudoDEFN, &FrontendTextureDEFN  );
		}

	}

//********************************************************************************************************************************

void	DisplayNextMatchType( char gametype )
	{
		if ( EUROgameType == EURO_championship )
		{
			char VenueText[32];

			if ( MatchNumber < 24 )

				DisplayString( 12, 98,
					GetTEXT ( GRUP_LBLS+( ( Fixtures[MatchNumber].HomeTeam & 12 )>>2 )),
					LARGE_FONT, 36, NO_BOX, &FrontendPseudoDEFN, &FrontendTextureDEFN  );
			else			     	
			    	
			if ( MatchNumber < 28 )

				DisplayString( 12, 98,
					GetTEXT ( MTCH_TYPE+QuarterFinal ),
					LARGE_FONT, 36, NO_BOX, &FrontendPseudoDEFN, &FrontendTextureDEFN  );
			else			     	
			    	
			if ( MatchNumber < 30 )

				DisplayString( 12, 98,
					GetTEXT ( MTCH_TYPE+SemiFinal ),
					LARGE_FONT, 36, NO_BOX, &FrontendPseudoDEFN, &FrontendTextureDEFN  );
			else			     	
			    	
				DisplayString( 12, 98,
					GetTEXT ( MTCH_TYPE+Final ),
					LARGE_FONT, 36, NO_BOX, &FrontendPseudoDEFN, &FrontendTextureDEFN  );
			    	

			strcpy(VenueText, ToUPPER(GetTEXT( VNUE_NMES+MatchVenues[MatchNumber] )) );

		// venue of match

			DisplayString( 
				430-(PixelLengthOfString( VenueText, MEDIUM_FONT )),
				98, VenueText, MEDIUM_FONT, 36, NO_BOX, 
				&FrontendPseudoDEFN, &FrontendTextureDEFN  );

		// date of match

			DisplayString( 
				430-(PixelLengthOfString( GetTEXT( DATE_LBLS+MatchNumber ), SMALL_FONT)),
				120, GetTEXT( DATE_LBLS+MatchNumber ), SMALL_FONT, 36, NO_BOX, 
				&FrontendPseudoDEFN, &FrontendTextureDEFN  );
		}
	}


//********************************************************************************************************************************

void	NextMatchSelectButtons( char GAMEtype )
	{
		if ( GAMEtype == EURO_championship )
		{
			StartMatchHandle 	=  AddAnimation( 446, 300, 
						 ( (float)BUTN_WHBL ), ( (float)BUTN_WHBL+11.9 ),
						 0.0, START_MATCH_BOX, CONT_ANIM );
			StartMatchHighlight 	=  ControlOptionHighlight( -1, START_MATCH_BOX,
						   START_MATCHdisp_BOX, -1, 
						   StartMatchHandle, BUTN_LBLS+StartMatch );

			TeamSetupHandle 	=  AddAnimation( 446, 228, 
						 ( (float)BUTN_WHBL ), ( (float)BUTN_WHBL+11.9 ),
						 0.0, FORMATION_SETUP_BOX, CONT_ANIM );
			TeamSetupHighlight 	=  ControlOptionHighlight( -1, FORMATION_SETUP_BOX,
						   FORMATION_SETUPdisp_BOX, -1, 
						   TeamSetupHandle, BUTN_LBLS+TeamSetup );

			if ( ( EUROmatchUsers = FindNumberOfMatchUsers() ) > 0 )
			{

				PlayerSetupHandle 	=  AddAnimation( 446, 180, 
							   ( (float)BUTN_WHBL ), ( (float)BUTN_WHBL+11.9 ),
							   0.0, PLAYER_SETUP_BOX, CONT_ANIM );
				PlyrSetupHighlight 	=  ControlOptionHighlight( -1, PLAYER_SETUP_BOX,
							   PLAYER_SETUPdisp_BOX, -1, 
							   PlayerSetupHandle, BUTN_LBLS+PlayerSetup );
			}
		}
	}


//********************************************************************************************************************************


void	DoNextMatchSelection( char MENU, signed char BOX )
	{
		if ( MENU == NEXT_MATCH && LogicState == RUN_FRONTEND )
		{
			if ( EUROgameType == EURO_championship )
			{		


//-------- console routine -------------------------------------------------------------------------------------------------------
 
				if ( EUROconsole != 0 && keys[1]==1 && KeyToggle[1]==0 )
				 {
					EUROmatch_info.EscKey^=	1;
					char	console[50];
					strcpy( &console[0], "Match Esc Key: ");
						strcat(console, GetTEXT( SETG_TEXT+(EUROmatch_info.EscKey & 1)) );
					
					CopyFromBACKtoPSEUDObuffer(
						&FrontendPseudoDEFN, &FrontendBackgroundDEFN,
						0, 0, 128, 24 );

						DisplayString( 0, 0,
						console, SMALL_FONT, 36, 
						NO_BOX,	&FrontendPseudoDEFN, &FrontendTextureDEFN  );

						AddToDumpList( 0, 0, 128, 24 );
				}

					KeyToggle[1] = keys[1];

//--------------------------------------------------------------------------------------------------------------------------------				

				if ( BOX == START_MATCH_BOX && ButtonState != 0 )
				  {
					Animation_table[StartMatchHandle].AnimationSpeed = 
						WhichButton( ButtonState, 0.85);
					RunMatch 	=	Yes;
					ChangeMenu	=	MAIN;
				     	DeBounce  	= 	TRUE;
				  }								 	
	
				if ( BOX == FORMATION_SETUP_BOX && ButtonState != 0 )
				  {
					Team =	ConfigureTeamView();
					Animation_table[TeamSetupHandle].AnimationSpeed = 
							WhichButton( ButtonState, 0.85);
       					ChangeMenu	=	SQUAD_SELECT;
			     		DeBounce  	= 	TRUE;
				  }								 	


			if ( EUROmatchUsers>0 && EUROgameType == EURO_championship )
			{
				PlyrSetupHighlight 	=  ControlOptionHighlight( BOX, PLAYER_SETUP_BOX,
							   PLAYER_SETUPdisp_BOX, PlyrSetupHighlight,
							   PlayerSetupHandle, BUTN_LBLS+PlayerSetup );

				if ( BOX == PLAYER_SETUP_BOX && ButtonState != 0 )
				  {
					signed char u	=	EUROnoOfMatchPlyrs;
					EUROplyrSetup   = 	0;

					while	( u>-1 )
					{								
						if ( UserList[u].team == EUROteamA || UserList[u].team == EUROteamB )
							EUROplyrSetup = u;
						u--;
					}

					Animation_table[PlayerSetupHandle].AnimationSpeed = 
							WhichButton( ButtonState, 0.85);
					ChangeMenu	=	PLAYER_SETUP;
				     	DeBounce  	= 	TRUE;
				  }								 	
			}

			StartMatchHighlight 	=  ControlOptionHighlight( BOX, START_MATCH_BOX,
						   START_MATCHdisp_BOX, StartMatchHighlight, 
						   StartMatchHandle, BUTN_LBLS+StartMatch );

			TeamSetupHighlight 	=  ControlOptionHighlight( BOX, FORMATION_SETUP_BOX,
						   FORMATION_SETUPdisp_BOX, TeamSetupHighlight, 
						   TeamSetupHandle, BUTN_LBLS+TeamSetup );
			}

		}

	}


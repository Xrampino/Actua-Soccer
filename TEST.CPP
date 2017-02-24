#include <iostream.h>
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
#include "results.h"
#include "video.h"
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
#include "euro_mod.h"
#include "euro_cmd.h"
#include "euro_mat.h"
#include "euro_rnd.h"
#include "euro_sym.h"

//ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป 
//บ                                                                                                                              บ
//บ  EURO '96	-	FRONT END 		                                                                                 บ
//บ                                                                                                                              บ
//บ  Start date:	14/12/1995                                                                                               บ
//บ  End date:									                                                 บ
//บ                                                                                                                              บ
//บ                                                                                                                              บ
//บ		Christine's new work number:	2784293                                                                          บ
//บ             My new mobile number:		0973 868837                                                                      บ
//บ             Caroline:			0589 665323                                                                      บ
//บ                                             2446227                                                                          บ
//บ             Andy Finlay:			2390248                                                                          บ
//บ             Justin Longden's mobile number: 0973 169931                                                                      บ
//บ 		Philip Durbidge work number:	2734391                                                                          บ
//บ             Jason Wragg's Home number:	2352544                                                                          บ
//บ                                                                                                                              บ
//บ                                                                                                                              บ
//บ                                                                                                                              บ
//บ  Changes to formation types:                                                                                                 บ
//บ                                                                                                                              บ
//บ  	England		4-4-2     done                                                                                           บ
//บ     Bulgaria	1-3-3-3                                                                                                  บ
//บ     Croatia		5-3-2     done                                                                                           บ
//บ     Czech Rep.	5-3-2     done                                                                                           บ
//บ     Denmark		5-4-1                                                                                                    บ
//บ     France		4-4-2     done                                                                                           บ
//บ     Germany		5-3-2     done                                                                                           บ
//บ     Holland		3-4-3                                                                                                    บ
//บ     Italy		4-4-2     done                                                                                           บ
//บ     Portugal	4-5-1                                                                                                    บ
//บ     Romania		5-4-1                                                                                                    บ
//บ     Russia		5-3-2     done                                                                                           บ
//บ     Scotland	5-3-2     done                                                                                           บ
//บ     Spain		4-5-1                                                                                                    บ
//บ     Switzerland	4-4-2     done                                                                                           บ
//บ     Turkey		5-3-2     done                                                                                           บ
//บ                                                                                                                              บ
//ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ 

	long		SndsValid	=	1;

	int		lookv;
	offset_file	load_offsets[256];
//	BYTE		*background_buffer;
	BYTE		*gremlin_buffer;
//	BYTE		*psudo_buffer;
	BYTE		*sprite_buffer;
	BYTE		*sfont_buffer;
	BYTE		*mfont_buffer;
	BYTE		*bfont_buffer;
	BYTE		*spool_buffer;
	BYTE		*unpack_buffer;
	BYTE		*texture_buffer;
	BYTE		*proptab_buffer;
	BYTE 		palette_buffer[768];
	BYTE 		work_buffer[768];
	extern		unsigned char pal[768];
	BYTE 		filter_buffer[256];
	BYTE		mouseBKGbuffer[30*30];
	BYTE		shirtBKGbuffer[51*62];
	short		OldMouseX,OldMouseY,OldMouseWidth,OldMouseHeight;

	int		key_velocity		=	0;
// old actua	int		InitialiseMan, InitialiseFlag;
	int		MouseFlags;
	int		Button_pressed		=	0;
	int		VIDEOstatus;
	int		array_test 		=	1;
	int		CursorXposn;
	char		wheelgoes		=	0;
	char		redefine_flag		=	255;
	char		CarryControl;
	int		keep_demo_time,keep_demo_Gtype;
	int		keep_demo_teama;
	int		keep_demo_teamb;
	int		keep_x_posn, keep_y_posn;
	int		keep_demo_comp;
	short		keep_demo_offside;
	short		keep_demo_subs;
	short		keep_demo_freekicks;
	short		keep_demo_bookings;
	short		keep_demo_wind;
	int		keep_demo_referee;

	char		german_man;
	char		wheel[18]		=	"";
	int		last_menu		=	NULL;
	int		selected_player		=	0;
	int		selected_team		=	0;
	short		selected_formation	=	0;
	short		display_formation  	=	selected_formation;
	char		*TextBuffer;
	int		quit			=	NULL;
	int		menu_update		=	NULL;
	char		rerun_menu		=	NULL;
	int		MarkSquadPlayer	   	=	NULL;
	int		MarkSlotNumber	   	=	NULL;
	int		MarkControlType	   	=	NULL;
	int		current_spool	    	=	NULL;
	int		proportional_change	=	0;
	int		music_state		=	0;
	char		suspend_audio		=	0;
	char		OldKEY			=	0;
	short		OldShirtX,OldShirtY,OldShirtWidth,OldShirtHeight;
	int		ClickXposn,ClickYposn;
	int		ShirtFlags;
	short		ShirtXposn,ShirtYposn;
	char		menu_initialised	=	OFF;
	char		keyboard		=	0;
	int		last_ticks;
	int		resolution,header_y;
	int		firstrun		=	NULL;
	int		NetworkType		=	NULL;
	int		NetworkType_toggle	=	NetworkType;
	int		Competition_limit;  
	int		NoOfTeamsFlag	    	=	NULL;
	int		Players_Team_Choice;
	short		TabX,lineY;
	int		Lastnetwork		=	-1;
	int		Laststarts		=	-1;
	int		WheelOuter,WheelInner,WindowNumber;
	char		OverlayFlag;
// old actua	int		DrawMan;
	int		formdata;
	int		pulsating_colour	=	0;
	int		formation_toggle;
	char		compute_a,compute_b;
	char		newgame;
	int		music_fade_flag,music_volume;
	int		ref_vision		=	50;
	int		ref_disc		=	50;
	int		ref_vision_add		=	1;
	int		ref_disc_add		=	-1;
	char		GDVavailable,StartGDVavailable;
	char		*time_message; 
	char		*slot_text[25];
	char		*slot_TITLE[25];
	char		RetestNet;
	float		angle	=	-PI/4;	//(3*PI)/4;
	float		anim	=	0.4;
	int 		PC_speed	=	34;
	char		tune;

	char		cal0,cal1;
	char		which_key_message;

	extern	void	write_config_file();
	extern 	int  	timing();

	extern	"C"	signed char key1[6];
	extern	"C"	signed char key2[6];

	extern 	"C"	volatile int hold_loop;
	extern	"C"	volatile int count;
	extern	"C"	int 	netsetup_on;		// In network setup
	extern	"C" 	int	network_on;
	extern	 	char	return_doskey;

	extern 		match(int argc, char **argv);
	extern	"C"	int	CheckFORnet();
	extern	"C"	void	DeinitialiseNET(int netflag);
	extern char	audio_version;
	extern void	claim_key_int(void);
	extern void	release_key_int(void);
	int		go_audio();
	char		team_a_okay, team_b_okay;
	extern void	init_keyboard();
	extern void 	init_users();
	extern void 	init_team();
	extern	"C"	volatile char net_half;
	extern "C" 	char joystick1_on;
	extern "C" 	char joystick2_on;
	extern "C" 	unsigned short joy1_cnt_x,joy1_cnt_y;
	extern "C" 	unsigned short joy2_cnt_x,joy2_cnt_y;
	extern "C" 	char old_mf;

	int	new_menu, current_menu;
	char		lastTGAstate;
	int		AutoSTARTgame;
	int		RESET_MEMORY;
	int		bomb_message	=	NULL;
	char		force_res;
	char		sub_version;

    	short		GDVtimer;
	int __far	criticalhandler(unsigned deverror,unsigned errcode, unsigned __far * devhdr);
	int		GetFirstCDDrive();
	int 		CheckCD(int CD);
	char		no_cd;
	char		keep_language;
	int		InsertKey(int SourceKEY);

	extern	int	gdv_gran;
	extern  "C"	int	x1ok;
	extern  "C"	int	y1ok;
	extern  "C"	int	x2ok;
	extern  "C"	int	y2ok;
	extern  "C"	int	bitaccept;

	extern	void 	PlayGDV();
	char	testfile[128];



//ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป 
//บ                                                                                                                              บ
//บ  Euro '96 addition.                                                                                                          บ
//บ												                                 บ
//ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ 

	extern	int	  testVESA;
	extern	int 	  VESAmode(int *);
	extern  void near svgacpy( char unsigned near *, short, short, short, short, short );


void	main(int argc, char **argv)
{
	version		=	1;
	sub_version	=	0;
	day		=	15;
	month 		=	12;
	year  		=	1995;
	EUROsymbol	=	0;
	EUROfrontend	=	1;

	printf	("\n\n\n\nEURO '96\n");
	fflush(stdout);
	printf	("\(C\) Gremlin Interactive 1995,96\n");
	fflush(stdout);
	printf	("þ Version: %d.%d         %d/%d/%d\n", version, sub_version, day, month, year);
	fflush(stdout);

	TestForWindows95();
	Test_640x480_VideoMode();

	LogicState	=	BLANK_SCREEN;
	Team		=	England;
	Menu		=	MAIN;
	NoOfSubs	=	4;
	UsableSubs	=	4;

	WinPts		=	3;
	DrawPts		=	1;
	MatchNumber	=	0;
  	ChangeMenu 	=    	-2;
	EUROday		=	2;
	EUROmonth	=	2;
	EUROyear	=	96;
	EUROgameType	=	EURO_championship;	//friendly;

	EUROteamA	=	0;	//England;
	EUROteamB	=	1;	//Scotland;
	EUROteamView	=	0;

	ResetUsers();
	EUROnoOfMatchPlyrs =	1;
	EUROplyrSetup	=	0;
	CommPort	=	2;
	BaudRate	=	9600;
	RunMatch	=	No;


	ProcessCommandLine( argc, argv);

	if ( EUROverbose != 0 )
	{
		printf ("þ Memory check: %d\n",get_mem_info() );
		fflush(stdout);
	}

	EUROmaxPlayers	=  	SetupControlMethods();


	InitEUROnet();
	if ( EUROnetInitialise == No && EUROgameType == EURO_network_game )
		EUROgameType = EURO_friendly;

//********************************************************************************************************************************












//ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป 
//บ                                                                                                                              บ
//บ  Checks to see make sure a mouse driver is present before continuing.                                                        บ
//บ												                                 บ
//ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ 

	bomb_message	=	0;

	_harderr(criticalhandler);
	GetFirstCDDrive();


//********************************************************************************************************************************

//ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป 
//บ                                                                                                                              บ
//บ  Euro '96 addition.                                                                                                          บ
//บ												                                 บ
//ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ 

		ReadDataOffsetFile( &EuroOFFSETfile[0] );		// Load data offset file. 

		Euro96_MemoryInitialise();				// Resets all Euro memory handles.

		TextStringMemHandle  =					// Set up memory handle.
			AllocateTextStringMemory();			// Allocate memory for text strings..

		printf	("þ %d Bytes allocated for script file text.\n", TEXT_STRING_BUFFER_LEN);
		fflush(stdout);

	// ------------------------------------


		if ( EUROsymbol == 1 )
		{
			fp2=fopen( "euro_sym.h", "wb" );
				if(fp2==NULL)
				{
					EUROsymbol = 0;
					printf	("þ Error trying to create symbol table.\n");
					fflush(stdout);
				}
		}

		process_script_file(&EuroSCRIPTfile[0]);		// Reads script file and compiles relevent data for game.

		if ( EUROsymbol == 1 )
		{
			fclose(fp2);						
		 	printf	("þ Symbol table created.\n");
			fflush(stdout);
			DeAllocateMemory(TextStringMemHandle);			// DeAllocates memory used previously for text strings.
			exit(-1);
		}				

	// ------------------------------------

		if ( EUROgameType == EURO_wireplay )
		{
			printf	("þ Wireplay Teams:    %s  V",
				GetTEAMname( EUROteamA, 11 ) );
			fflush(stdout);
			printf	("  %s\n",
				GetTEAMname( EUROteamB, 11 ) );
			fflush(stdout);
		}

		AllocateDisplayBuffers();     				// Allocates two 640x480 display buffers.

		TexturePageMemHandle =					// Set up memory handle.
			AllocateTexturePageMemory( 8, 			// Specify number of texture pages to allocate.
				&FrontendTextureDEFN );			// Allocate memory for frontend texture pages.

		FrontendTextureDEFN.page_start 	= (BYTE *)TexturePages;	// Specify memory address used for texture pages.

		LoadTexturePage( BIN_PAGE1, 	       			// Load texture page 1 into texture memory.
				 &EuroDATfile[0], 
				 0, &FrontendTextureDEFN );

		LoadPalette( BIN_TSELPAL, &EuroDATfile[0], 0 );		// creates special filters for team select section.
				 CreateFilter( &FilterBuffer[256],  40, 54, 60, .7, .7, .7);
				 CreateFilter( &FilterBuffer[512],  40, 54, 60, .6, .6, .6);
				 CreateFilter( &FilterBuffer[768],  40, 54, 60, .5, .5, .5);
				 CreateFilter( &FilterBuffer[1024], 40, 54, 60, .4, .4, .4);
				 CreateFilter( &FilterBuffer[1280], 40, 54, 60, .3, .3, .3);
				 CreateFilter( &FilterBuffer[1536], 40, 54, 60, .2, .2, .2);
				 CreateFilter( &FilterBuffer[1792], 40, 54, 60, .1, .1, .1);

//********************************************************************************************************************************
		



























//ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป 
//บ                                                                                                                              บ
//บ  Checks command line for verbose options.                                                                                    บ
//บ												                                 บ
//ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ 
		
		if(ReadConfigFile())
			bomb_message|=	CONFIG_ERROR;

		match_info.menu_res  	=       HI;
		batch_info.GDVres	=	HI;
		newgame			=	0;
		redefine_flag	 	=	255;
		CarryControl		=	NULL;
		x1ok			=	NULL;	
		y1ok			=	NULL;	
		x2ok			=	NULL;
		y2ok			=	NULL;	
		bitaccept		=	NULL; 
		match_info.tga_enable 	=	NULL;
		batch_info.cheat_mode 	=	OFF;
		match_info.menu_res  	=       HI;
		force_res   		=	NULL;
		match_info.language 	=	Language;
		no_cd			=	FALSE;
//		batch_info.floppy  	=  	FLOPPY;
		keyboard		=	0;

		batch_info.rolling_demo	=	ROLLING_DEMO;

		if (batch_info.rolling_demo!=Off)
			no_cd		=	TRUE;

//ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป 
//บ                                                                                                                              บ
//บ  Checks for PC memory and machine speed then sets up game and intro variables.                                               บ
//บ												                                 บ
//ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ 

		setup.detail.sky     	=	ON;	
		setup.detail.stadia  	=	HI;
		setup.detail.lines   	=	ON;
		setup.vidi_type      	=	HI;
		setup.detail.players 	=	HI;
		setup.detail.pitch   	=	MED;
		setup.start_res  	=	LO;
		setup.screen_size   	=	NULL;
		setup.stadium	     	= 	1;

		PC_speed		=	timing();
		setup.M8		=	1;	//DisplayFree();

		if (PC_speed>31)
			PC_speed = 31; 
		setup.detail.sky     =		detail_defaults[PC_speed].sky;	
		setup.detail.stadia  =		detail_defaults[PC_speed].stadia;
		setup.detail.pitch   =		detail_defaults[PC_speed].pitch;
		setup.detail.players =		detail_defaults[PC_speed].players;
		setup.detail.lines   =		detail_defaults[PC_speed].lines;
		setup.detail.shadows =		detail_defaults[PC_speed].shadows;
		setup.vidi_type      =		NULL;
		setup.start_res      =		NULL;
		match_info.camera    =		NULL;
		setup.screen_size    =		screen_defaults[PC_speed];

		music_fade_flag	 	 		=	NULL;			
	 	match_info.music			=	NULL;
		match_info.crowd			=	NULL;
		match_info.commentary			=	NULL;
		match_info.master			=	NULL;
		match_info.pitch			=	NULL;

		match_info.referee			=	16+16;
		match_info.CompetitionType		=	FRIENDLY;
		match_info.CompetitionType_toggle	=	FRIENDLY;
		match_info.NoOfPlayers			=	NULL;
		match_info.NoOfPlayers_toggle		=	NULL;
		
		if (batch_info.rolling_demo==Off)
		{
			match_info.GameType			=	SIMULATION;
			match_info.GameType_toggle		=	SIMULATION;
		}			
		else
		{
			match_info.GameType			=	ARCADE;
			match_info.GameType_toggle		=	ARCADE;
		}			
		batch_info.Port_toggle			=	NULL;
		match_info.control_methods[0]		=	0;
		match_info.control_methods[1]		=	1;
		match_info.control_methods[2]		=	2;
		match_info.control_methods[3]		=	3;

		match_info.time				=	0;
		match_info.time_toggle 			=	match_info.time;
		net_half				=	match_info.time;
		match_info.offside			=	0;
		match_info.offside_toggle		=	0;
		match_info.substitutes			=	1;
		match_info.substitutes_toggle		=	1;
		match_info.bookings			=	1;
		match_info.bookings_toggle 		=	1;
		match_info.wind				=	0;
		match_info.wind_toggle			=	0;
		match_info.freekicks			=	1;
		match_info.freekicks_toggle  		=	1;
		
		batch_info.match_number			=	-1;
		batch_info.round_up_page		=	0;
		batch_info.cup_match_number		=	-1;
		batch_info.number_of_cup_teams		=	32;

		batch_info.keys_used[UP_RED]		=	0x1e;		// A
		batch_info.keys_used[DN_RED]		=	0x2c;		// Z
		batch_info.keys_used[LF_RED]		=	0x33;		// <
		batch_info.keys_used[RT_RED]		=	0x34;		// >
		batch_info.keys_used[F1_RED]		=	0x10;		// Q
		batch_info.keys_used[F2_RED]		=	0x35;		// /

		batch_info.keys_used[UP_RED+6]		=	-0x48;		// Arrow Up
		batch_info.keys_used[DN_RED+6]		=	-0x50;		// Arrow Dn
		batch_info.keys_used[LF_RED+6]		=	-0x4b;		// Arrow Lf
		batch_info.keys_used[RT_RED+6]		=	-0x4d;		// Arrow Rt
		batch_info.keys_used[F1_RED+6] 		=	0x52;		// 0(num)
		batch_info.keys_used[F2_RED+6] 		=	0x53;		// .(num)
					
		cal0					=	NULL;
		cal1					=	NULL;
		net_game_no				=	0;
		cd_in					=	TRUE;
		suspend_audio				=	0;

		reset_league_teams();



//ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป 
//บ                                                                                                                              บ
//บ  Load DATA.DAT file offset table.                                                                                            บ
//บ												                                 บ
//ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ 
//
//			// The following lines check to see if DATA.DAT and DATA.OFF files are on C:

		audio_version=TRUE; 
		InitialiseTimer();			// Initialise timers for sound drivers	(see ANDY or LAURENT)..

			if (go_audio())
			{
				UnInitialiseTimer();
				bomb_message|=	SOUND_ERROR;
			}

		// Timer stuff

		ftick		=	0;
		tick		=	0;
		count		=	0;
		game_speed	=	REAL_SPEED;
		readptr=writeptr=	0;

		AddTimer(TIMER_SPEED,nethandler,NetworkHandle);
		AddTimer( 63, EUROinterupt, EuroHandle );
				       
		claim_key_int();

	//----------------------------------------------------------------------------------------------

		Set_palette_to_black();

		RESET_MEMORY	=	YES;
		OverlayFlag	=	NULL;

		if (newgame==0)

	while	( new_menu!=QUIT && new_menu!=NO_MOUSE )
	{
		return_doskey 	=	FALSE;

		if ( RESET_MEMORY==YES )
		{
			Set_palette_to_black();

// old actua		     	Initialise_environment();
// old actua			Allocate_memory();
// OLD ACTUA			mbuff.buff_start	=	(BYTE *)psudo_buffer-4-60;	
// old actua			sbuff.buff_start	=	(BYTE *)psudo_buffer-4-60;	

//********************************************************************************************************************************

//ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป 
//บ                                                                                                                              บ
//บ  Euro '96 addition.                                                                                                          บ
//บ												                                 บ
//ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ 

//		InitialiseSquadPositions();
		FrontendBackgroundDEFN.pseudo_start 	=	(BYTE *)EuroBackgroundBuffer;
		FrontendPseudoDEFN.pseudo_start 	=	(BYTE *)EuroPseudoBuffer;
		Set_640x480_VideoMode();
		Set_palette_to_black();

//********************************************************************************************************************************

			suspend_audio 	=	0;
			memset( palette_buffer, 0, 768 );
			memset( work_buffer, 0, 768 );
			RESET_MEMORY	=	NO;
		}	

	batch_info.PointsForWin	=	3;


	last_ticks	=	NULL;
	AutoSTARTgame 	=	NULL;
	suspend_audio	=	0;
	RetestNet	=	FALSE;

//********************************************************************************************************************************

//ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป 
//บ                                                                                                                              บ
//บ  Euro '96 addition.                                                                                                          บ
//บ												                                 บ
//ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ 
//
		EUROoveride	=	0;

	if ( EUROgameType == EURO_wireplay ) 
	{
		StartingEURO_96( EUROgameType );
		Euro96initialise();	// Initialise game data.
 		EUROuserSelection	=  0;
		Menu			=  PLAYER_SETUP;
		EURO_Did_I_ChooseTeams	=  Yes; 	// you made team choice.
		Team_A			=  EUROteamA;   // Send your choice of teams.
		Team_B			=  EUROteamB; 	// Send your choice of teams.
		SendTeamInfo();
		TickPause();
		TickPause();
		TickPause();
		EURO_NetSelectionMade	=  No;		// player selection has not yet been made.
     	}

//********************************************************************************************************************************




	


	while	( new_menu!=QUIT )
//	while   ( ChangeMenu!=EXIT_FRONTEND && LogicState!=BLANK_SCREEN )	// new loop.
	{

		ClearDumpList();
		hold_loop	=	NULL;






		while	(current_menu==new_menu)
			{
			do
		{
		} while	(count<TIMER_SPEED/30);

		count	=	0;

//***********************   NEW EURO '96 FRONTEND LOOP   *************************************************************************

//ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป 
//บ                                                                                                                              บ
//บ  Euro '96 addition.                                                                                                          บ
//บ												                                 บ
//ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ 

		unsigned short	r = GetRnd2();

		if ( LogicState == BLANK_SCREEN && ChangeMenu == -2 )
		{
			OVERRIDEpal1	=	15;
			OVERRIDEpal2	=	29;
			ResetAnimations();
			ResetBoundingBoxes();
			SetupExtraTexturePages( Menu );
			DisplayBackground( Menu );
			OverlayStaticBackgroundImages( Menu );
			memcpy( EuroPseudoBuffer, EuroBackgroundBuffer, 307200 );
			InitialiseMenuPage( Menu );
			svgacpy( (unsigned char *) EuroPseudoBuffer, 0, 0, 640, 480, 640);
			EuroTextEditState = 0;
			ChangeMenu =    -1;	
			LogicState = PALETTE_FADEUP;
			Finish	   =	0;
		}		

		GetConsoleInput();
		ControlAnimations();

		Bounding_box = GetBoundingBox( SelectorXcoord, SelectorYcoord );
		DoMainScreen( Menu );
       		DoSquadSelection( Menu, Bounding_box, SelectorXcoord, SelectorYcoord );
       		DoTeamSelection( Menu, Bounding_box );
       		DoUserSetup( Menu, Bounding_box );
       		DoModemSetup( Menu, Bounding_box );
		DoNextMatchSelection( Menu, Bounding_box );
		EuroReDraw( Menu, Bounding_box );
		GroupFixturesPage( Menu, Bounding_box );
		DoPlayerStats( Menu, Bounding_box, SelectorXcoord, SelectorYcoord );
		DoTeamStats( Menu, Bounding_box, SelectorXcoord, SelectorYcoord );
		DoFinalRoundFixtures( Menu, Bounding_box );

		if ( EuroTextEditState == 0 )
		{
			StorePSEUDObuffer( &FrontendPseudoDEFN, &FrontendTextureDEFN, MOUSE_STOREbuff, SelectorXcoord, SelectorYcoord );
			DrawIMAGE(  &FrontendPseudoDEFN, &FrontendTextureDEFN, MOUSEimages+NoButton, 
					SelectorXcoord, SelectorYcoord, NO_BOX, spritecopy );
			AddToDumpList( SelectorXcoord, SelectorYcoord, Image_Widths[MOUSEimages+NoButton], Image_Heights[MOUSEimages+NoButton] );
		}			

			CopyDumpListToScreen();     			

		if ( EuroTextEditState == 0 )
		{
		       	DrawIMAGE( &FrontendPseudoDEFN, &FrontendTextureDEFN, MOUSE_STOREbuff, 
					SelectorXcoord, SelectorYcoord, NO_BOX, straightcopy );
			AddToDumpList( SelectorXcoord, SelectorYcoord, Image_Widths[MOUSEimages+NoButton], Image_Heights[MOUSEimages+NoButton] );
		}

		ReplaceSquadBuffers( Menu );
//		DoStadiumFlythru( Menu );

		if ( ChangeMenu != -1 && ChangeMenu < 63 )
			{
			      {
			      	LogicState = PALETTE_FADEDOWN;
				ChangeMenu|=	64;
			      }
			}
		
	       	if ( ChangeMenu >= 64 && LogicState == BLANK_SCREEN )
			{
				if (EUROgameType==EURO_network_game && (ChangeMenu & 63)==TEAM_SELECT &&
					     HaveNETteamsBeenChosen() == Yes )
					Menu	=	PLAYER_SETUP;
				else					
					Menu		=	ChangeMenu & 63;
				ChangeMenu	=	-2;

				if ( RunMatch == Yes )
					PlayMatch( argc, argv );
			}			

		
//*** TEMPORY EXIT TO DOS ********************************************************************************************************

		if ( LogicState == RUN_FRONTEND )
		{

	  	 	if (keys[2])
				TeamOveride	=	1;
	  	 	if (keys[0x3b])
	  			{
				      ChangeMenu = EXIT_FRONTEND;
	  			      LogicState = PALETTE_FADEDOWN;
	  			}
		}

		if ( ChangeMenu == EXIT_FRONTEND && LogicState == BLANK_SCREEN )
		{
	  		new_menu 	= 	QUIT;
		}

//********************************************************************************************************************************

		hold_loop	=	NULL;

		}

	current_menu	=	new_menu;
	rerun_menu    	=	NULL;

	}

	}

MAJOR_ERROR:;

	if (new_menu==QUIT)
	{	
		UnInitEUROnet();	

// old actua 	DeinitialiseNET(Competition_limit);			// net game can be played.....

	release_key_int();
	RemoveTimer(EuroHandle);
	RemoveTimer(NetworkHandle);

	if (audio_version)
	{
		UnInitialiseDIGI();	// Uninitialise SOS

	    	if ( batch_info.floppy==YES )
			UnInitialiseMIDI();	
	}

	UnInitialiseTimer();
 	UnInitEUROnet();	

// old actua		DeinitialiseNET(Competition_limit);			// net game can be played.....

		union REGS r;
		r.x.eax = 0x0003;
		int386(0x10, &r, &r);
	}





//********************************************************************************************************************************

//ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป 
//บ                                                                                                                              บ
//บ  Euro '96 addition.                                                                                                          บ
//บ												                                 บ
//ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ 

 		if ( EUROverbose != 0 )
 		{
			printf("\n  DEALLOCATING MEMORY BEFORE EXITING TO DOS.\n\n");
			fflush(stdout);				
		}

		DeAllocateTexturePages();
		DeAllocateDisplayBuffers();
		DeAllocateMemory(TextStringMemHandle);			// DeAllocates memory used previously for text strings.

//********************************************************************************************************************************

//		if ((bomb_message & MOUSE_ERROR)!=0)
//			printf ( GetText(MOUSE_ERROR_TEXT) );
//		if ((bomb_message & SOUND_ERROR)!=0)
//			printf ( GetText(SOUND_ERROR_TEXT) );
//		if ((bomb_message & CONFIG_ERROR)!=0)
//			printf ( GetText(CONFG_ERROR_TEXT) );
//		if ((bomb_message & FILE_ERROR)!=0)
//			printf ( GetText(DFILE_ERROR_TEXT) );
//		if ((bomb_message & FILE_MISSING)!=0)
//			printf ( GetText(MFILE_ERROR_TEXT) );
//		if ((bomb_message & MATCH_ERROR)!=0)
//			printf ( GetText(INI3d_ERROR_TEXT) );
//		if ((bomb_message & MEMORY_PROBLEM)!=0)
//			printf ( GetText(MEMOY_ERROR_TEXT) );
//		if ((bomb_message & WHEEL_ERROR)!=0)
//			printf ( GetText(WHEEL_ERROR_TEXT) );

}



/******************************************************************************
*****************************************************************************/

int go_audio()
{
// Initialise Audio Config...
	

    	if ( batch_info.floppy==YES )
	{
		if(InitialiseMIDI())	
			return(EXIT_FAILURE);
	}

	if(InitialiseDIGI(22050,setup.verbose?IDF_VERBOSE:0))			// Initialise Digital Sound Drivers
	{
	    	if ( batch_info.floppy==YES )
			UnInitialiseMIDI();	

		return(EXIT_FAILURE);
	}



	return(FALSE);
}

/******************************************************************************
******************************************************************************/

//
// Software Piracy Protection Pumpkin Gobbler for ACTUA SOCCER
//

	int NumCDdrives;
	int FirstCDdrive;
	int file=0;

//*************************************************************************************************
//
// Checks for the Actua Soccer CD
//
//*************************************************************************************************
int CDPresent()
{
	if ( batch_info.floppy==NO )
	{

		int i=0;
		int CDfound=0;
			for(i=0;i<NumCDdrives;i++)
				if(!CDfound)
					CDfound=CheckCD(FirstCDdrive+i);
			return(CDfound);
	}

	else
			return(1);	// using floppy version.
}

//*************************************************************************************************
//
// Checks to see if there is a CD Drive connected.
//
// returns TRUE if CD Connected and fills in First CD Drive and NumCDdrives
//	        FALSE if nothing there
//
//*************************************************************************************************
int GetFirstCDDrive()
{
	int	drive;
	union REGS regs;
	
	regs.w.ax=0x1423;
	regs.w.ax+=0xdd;			// 0x1500
	regs.w.bx=0;
	int386(0x2f,&regs,&regs);

	if(regs.w.bx)
		{
		drive = (char)regs.w.cx;
		FirstCDdrive=drive;
		NumCDdrives=regs.w.bx;
		return(0);
		}
	else
		return(1);
}

//*************************************************************************************************
//
// Check for a single file on a drive
//
//*************************************************************************************************
int CheckCD(int CD)
{
	char filename[16];
	FILE *fp;

	filename[0]=CD+'A';						//check the last one we new about
	file^=1;


	if (match_info.language==English || match_info.language==French || match_info.language==Norwegian)
		strcpy(filename+1,file?":\\ACTREND.DAT":":\\DATA.DAT");

	if (match_info.language==German)
		strcpy(filename+1,file?":\\ACTREND.DAT":":\\RANDATA.DAT");

	if (match_info.language==American || match_info.language==Canadian)
		strcpy(filename+1,file?":\\ACTREND.DAT":":\\VRDATA.DAT");

	if(fp=fopen(filename,"rb"))
		{
		fread(&filename[0],1,16,fp);
		fclose(fp);
		return(1);
		}
	else
		return(0);
}

//*************************************************************************************************
//
// Critical Error Handle for Disk Errors
//
//*************************************************************************************************
int __far	criticalhandler(unsigned deverror,unsigned errcode, unsigned __far * devhdr)
{
	return(_HARDERR_FAIL);
}


int	InsertKey(int SourceKEY)
{
 	if (SourceKEY>127)
	{
	 	SourceKEY-=	128;
		SourceKEY=	-SourceKEY;
	}
	return	(SourceKEY);
}










//void	SearchForVIDEOmode()
//{
//	char	testgdv[128];
//	strcpy	(testgdv,SourcePath);
//	strcat	(testgdv,"\\VIDEO\\swhole_s.gdv");
//	GDVavailable		=	DoesFILEexist(testgdv);
//	if (match_info.language==German)
//		GDVavailable		=	1;
//	strcpy	(testgdv,SourcePath);
//	if (match_info.language==English || match_info.language==French || match_info.language==Norwegian)
//		strcat	(testgdv,"\\VIDEO\\sfull_s.gdv");
//	if (match_info.language==German)
//		strcat	(testgdv,"\\VIDEO\\dssintro.gdv");
//	if (match_info.language==American || match_info.language==Canadian)
//		strcat	(testgdv,"\\VIDEO\\sfull_s.gdv");
//
//	StartGDVavailable	=	1;	//DoesFILEexist(testgdv);	
//
//		if (StartGDVavailable==0 || batch_info.GDVres==LO)
//		{
//			strcpy	(testgdv,DestinationPath);
//
//			if (match_info.language==English || match_info.language==French || match_info.language==Norwegian)
//				strcat	(testgdv,"\\VIDEO\\vfull_s.gdv");
//			if (match_info.language==German)
//				strcat	(testgdv,"\\VIDEO\\dvsintro.gdv");
//			if (match_info.language==American || match_info.language==Canadian)
//				strcat	(testgdv,"\\VIDEO\\vfull_s.gdv");
//
//			StartGDVavailable	=	DoesFILEexist(testgdv);	
//
//
//				if (StartGDVavailable==0 && batch_info.floppy==NO)
//					bomb_message|=	FILE_MISSING;
//		}
//
//		if ( setup.verbose!=NULL && GDVavailable==NULL)
//			printf	("THE MAKING OF ACTUA MOVIE IS MISSING FROM SOURCE PATH...\n");
//		if ( setup.verbose!=NULL && StartGDVavailable==NULL)
//			printf	("THE ACTUA INTRO GDV IS MISSING FROM SOURCE PATH...\n");
//
//
//
//
//
//
//		DisplayWidth	=	640;
//	
//	// checks for GDV mode, only if GDV is on CD.
//			
//	       	if (GDVavailable!=NULL)
//			{
//			testVESA		=	1;	
//			VIDEOstatus 		=	VESAmode( &GDVvidmode[0] );
//			}
//
////		if (VIDEOstatus==-1 || GDVavailable==NULL)
////			batch_info.GDVres=LO;
//
//	// setup the video mode, mode 101 (640x480).
//
//		testVESA		=	1;	
//		VIDEOstatus 		=	VESAmode( &MENUvidmode[0] );
//										
//    		if (VIDEOstatus == -1)
//				match_info.menu_res=LO;
//}

//void	InitialiseCodeWheel()
//{
//	CursorXposn	=	0;
// 	WheelOuter	=	(Random_RS()&15);
// 	WheelInner	=	(Random_RS()&15);
// 	WindowNumber	=	(Random_RS()&31);
//	wheelgoes++;
//	
//	char	legal_manual	=	FALSE;
//
// 	while	( legal_manual==FALSE )
//	{	
//	  german_man	=	(Random_RS()&63);
//  	  if  ( german_man<50 )
//  		legal_manual	=	TRUE;
//	}
//}

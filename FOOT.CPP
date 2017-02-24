/******************************************************************************
******************************************************************************/
// 
// Actua Soccer.   (Token Main Routine) 1.9.94
//
//	Programmed by Andy Findlay.
//
/******************************************************************************
******************************************************************************/

#include <stdlib.h>
#include <stdio.h>

// Audio includes...
#include "config.h"							// Config file
#include "basemem.h"							//
#include "sos.h"								// SOS stuff
#include "timer.h"							// Timers for Audio
#include "digi.h"								// Digital Sound
#include "midi.h"								// MIDI Sound
#include "audio.h"							// SOS header

#include "global.h"
#include "3deng.h"
#include "defines.h"
#include "mouse.h"
#include "front.h"
#include "eurofrnt\euro_int.h"
#include "mallocx.h"

#ifdef ECTS
extern void write_config_file();
#endif

struct goal_info
{
	char used;
	int scorer;
	int time;
};

typedef struct
{
	goal_info goal_data;
} goal_table;

goal_table goals[3*32]={0,0,0};

extern void	claim_key_int(void);
extern void	release_key_int(void);
extern char practice;

// NETWORK.C
extern "C" void read_joystick(char j,int *x, int *y, int *sw);
extern "C" void read_joy1(int *x, int *y, int *sw);
extern "C" void read_joy2(int *x, int *y, int *sw);
extern "C" void calibrate_joy(char j,unsigned short *x,unsigned short *y);
extern "C" void calibrate_logpad(unsigned short *x,unsigned short *y);
extern "C" void get_joy_dir1(int *x,int *y,int *f);
extern "C" void get_joy_dir2(int *x,int *y,int *f);
extern "C" void get_user_inputs();
extern "C" void process_user_inputs();

extern "C" volatile int Teams[MAX_NET_USERS],Players[MAX_NET_USERS];
extern "C" volatile int net_quit;
extern "C" volatile char paused;
extern "C" volatile char pause_request;
extern "C" volatile char keys[256];
extern "C" volatile char key_togs[256];
extern "C" unsigned char machine_no;

extern "C" void NetTest(void);
extern "C" void Network_Play_Ready(void);
extern "C" void Quit_Network_Play(void);

extern "C" void __far nethandler(void);
extern "C" unsigned int NetworkHandle;
extern "C" short wConsoleNode;
extern "C" int network_on;
extern "C" volatile int count;
extern "C" volatile int tick;
extern "C" volatile int ftick;

extern "C" volatile int writeptr;
extern "C" volatile int readptr;

extern "C" int game_speed;		// Currently declared in network.c
extern "C" char old_mf;
extern "C" char logpad_on;
extern "C" char joystick1_on;
extern "C" char joystick2_on;
extern "C" unsigned short joy1_cnt_x,joy1_cnt_y;
extern "C" unsigned short joy2_cnt_x,joy2_cnt_y;
extern "C" int joy1_max_x,joy1_max_y,joy1_min_x,joy1_min_y;
extern "C" int joy2_max_x,joy2_max_y,joy2_min_x,joy2_min_y;

extern "C" char calibrated_1,calibrated_2;

// Externed game functions...
extern void add_team_user(short t,short c);
extern void add_fixed_user(short p,short c);
extern void init_keyboard();
extern void init_users();
extern void init_team();
extern short conv_conts_back(char c);

extern setup_info setup;
extern short rand_seed;
extern int match(int argc, char **argv);
match_data match_info;
extern team_info game_data[];

extern int players;
extern int avg1_rate,avg1_power,avg1_bcontrol,avg1_flair,
		avg1_vision,avg1_accuracy,avg1_fitness,avg1_disc;

extern int avg2_rate,avg2_power,avg2_bcontrol,avg2_flair,
 		avg2_vision,avg2_accuracy,avg2_fitness,avg2_disc;


extern char audio_version;
extern char need_result;
extern short injury_time;
extern "C" int num_of_users;	// Currently in network.c

extern char say_names;
extern "C" volatile char net_half;

extern "C" void foot_init_net();
extern "C" void foot_uninit_net();

extern int performance;

int w95;

short no_front_users;

/******************************************************************************
*****************************************************************************/

void mem_test()
{
	int i=get_mem_info();
	printf("Free memory = %d\n",i);
 	setup.M8=(i>=MEM8);
	if (setup.verbose)
		if (setup.M8)
			puts("Initialising 8 meg game");
		else
		{
			puts("Initialising 4 meg game");
			printf("Need to free %d more bytes to run 8 meg version\n",MEM8-i);
		}
}

/******************************************************************************
*****************************************************************************/

int go_audio()
{
// Initialise Audio Config...
	
	if(ReadConfigFile())
		{
		printf("Error! Cannot read Config File.\n");
		return(EXIT_FAILURE);
		}

	if(InitialiseDIGI(22050,IDF_VERBOSE))			// Initialise Digital Sound Drivers
		return(EXIT_FAILURE);

	return(FALSE);
}

/******************************************************************************
******************************************************************************/

// Process command line options...

void get_command_line(int argc, char **argv)
{
	short opt,id;

	for (int i=1;	i<argc;	i++)
	{
		opt=-1;
		id=100;

// Look for switch!
		if (!strcmp(argv[i],"-i"))
// Inputs...
		{
			if (!strcmp(argv[i+1],"j1"))
				opt=JOY1_CTRL;
			if (!strcmp(argv[i+1],"j2"))
				opt=JOY2_CTRL;
			if (!strcmp(argv[i+1],"k1"))
				opt=KEY1_CTRL;
			if (!strcmp(argv[i+1],"k2"))
				opt=KEY2_CTRL;
			if (!strcmp(argv[i+1],"m"))
				opt=MOUSE_CTRL;
			if (!strcmp(argv[i+1],"lp"))
				opt=LOGPAD_CTRL;
			if (!strcmp(argv[i+1],"g1"))
				opt=GRAV1_CTRL;
			if (!strcmp(argv[i+1],"g2"))
				opt=GRAV2_CTRL;
			if (!strcmp(argv[i+1],"n"))
				opt=NET_CTRL;

			if (opt>0)
// Look for user id!
			{
				if (!strcmp(argv[i+2],"a"))
					id=TEAM_A;
				else
					if (!strcmp(argv[i+2],"b"))
						id=TEAM_B;
					else
					{
						id=atoi(argv[i+2]);
						if ((id<1) || (id>players) || (id==1) || (id==12))
							id=100;
					}

				i+=2;
			}
			if (id==100)
				i=argc;
			else
			{
				if (id<0)
				{
					if (id==-1)
						game_data[setup.team_a].player_control+=1<<no_front_users;
					else
						game_data[setup.team_b].player_control+=1<<no_front_users;

					match_info.control_methods[no_front_users++]=conv_conts_back(opt);
				}
				else
					add_fixed_user(id,opt);

#ifndef FRONT_END
				if (opt==JOY1_CTRL)
					joystick1_on=TRUE;
				if (opt==JOY2_CTRL)
					joystick2_on=TRUE;
				if (opt==LOGPAD_CTRL)
					logpad_on=TRUE;
#endif
			}
		}
		
		if (!strcmp(argv[i],"-s"))
// Stats...
		{
			if (!strcmp(argv[i+1],"ds"))
				opt=0;
			if (!strcmp(argv[i+1],"vi"))
				opt=1;
			if (!strcmp(argv[i+1],"bc"))
				opt=2;
			if (!strcmp(argv[i+1],"sp"))
				opt=3;
			if (!strcmp(argv[i+1],"fl"))
				opt=4;
			if (!strcmp(argv[i+1],"ac"))
				opt=5;
			if (!strcmp(argv[i+1],"pp"))
				opt=6;
			if (!strcmp(argv[i+1],"st"))
				opt=7;

			if (opt>=0)
			{
				if (!strcmp(argv[i+2],"a"))
				{
					int avg=atoi(argv[i+3]);
					if (avg>0 && avg<129)
					{
						id=0;
						switch(opt)
						{
							case(0):
								avg1_disc=avg;
								break;

							case(1):
								avg1_vision=avg;
								break;

							case(2):
								avg1_bcontrol=avg;
								break;

							case(3):
								avg1_rate=avg;
								break;

							case(4):
								avg1_flair=avg;
								break;

							case(5):
								avg1_accuracy=avg;
								break;

							case(6):
								avg1_power=avg;
								break;

							case(7):
								avg1_fitness=avg;
								break;
						}
					}
				}
				else
				{
					if (!strcmp(argv[i+2],"b"))
					{
						int avg=atoi(argv[i+3]);
						if (avg>0 && avg<129)
						{
							id=0;
							switch(opt)
							{
								case(0):
									avg2_disc=avg;
									break;

								case(1):
									avg2_vision=avg;
									break;

								case(2):
									avg2_bcontrol=avg;
									break;

								case(3):
									avg2_rate=avg;
									break;

								case(4):
									avg2_flair=avg;
									break;

								case(5):
									avg2_accuracy=avg;
									break;

								case(6):
									avg2_power=avg;
									break;

								case(7):
									avg2_fitness=avg;
									break;

							}
						}
					}
				}
			}
			else
				id=100;

			if (id==100)
				i=argc;
			else
				i+=3;
		}

		if (!strcmp(argv[i],"-r"))
// Random seed...
		{
#ifdef ECTS
			machine_no=atoi(argv[i+1]);
#else
			rand_seed=atoi(argv[i+1]);
#endif
		}

		if (!strcmp(argv[i],"-a"))
// Choose team...
		{
			setup.team_a=atoi(argv[i+1]);
		}

		if (!strcmp(argv[i],"-b"))
// Choose team...
		{
			setup.team_b=atoi(argv[i+1]);
			setup.team_b_kit=atoi(argv[i+1]);
		}
	}
}

/*
void GOAL_SCORED(int t,int s,int tm)
{
}
*/

/******************************************************************************
*****************************************************************************/

void SubstituePlayers(int a,int b,int c)
{
}

/******************************************************************************
*****************************************************************************/

/* Front End Emulator */

extern char var_start,var_end;
extern void init_joys();

void	test_w95()
	{
	//
	union REGS regs;
	struct SREGS sregs;

	memset(&sregs,0,sizeof(sregs));		//clr sregs
	regs.w.ax=0x1600;
	int386x(0x2F,&regs,&regs,&sregs);

	w95=regs.w.ax & 0xff;

	if (w95==3 || w95==4)
		{
		//running in windows 95!!!
		if (setup.verbose)
			printf("Running windows 95 version\n");
		w95=TRUE;
		}
	else
		{
		if (setup.verbose)
			printf("Running DOS version\n");
		w95=FALSE;
		}
	}


int main(int argc, char **argv)
{
	w95=0;		// Windows flag!
	test_w95();

	no_front_users=0;
 	num_of_users=0;

	init_joys();

	performance=31;			// Pentium speed!
	setup.team_a=36;
	setup.team_b=1;
	setup.team_b_kit=1;
	setup.stadium=setup.team_b;
	setup.start_res=0;
	setup.vidi_type=0;		// 0=norm, 1=filtered
	setup.verbose=0;
	setup.screen_size=0;
	setup.detail.stadia=1;	// 0=simple,1=complex
	setup.detail.pitch=2;	// 0=simple,1=lo,2=hi
	setup.detail.sky=1;		// 0=off,1=on
	setup.detail.players=1;	// 0=simple,1=full
	setup.detail.lines=1;	// 0=simple,1=full
	setup.detail.shadows=1;	// 0=simple,1=full

#ifdef ONE_MACHINE
//	game_data[setup.team_a].player_control=1;
//	game_data[setup.team_b].player_control=2;
//	match_info.control_methods[0]=2;
//	match_info.control_methods[1]=0;
#else
	game_data[setup.team_a].player_control=0;
	game_data[setup.team_b].player_control=0;
#endif

#ifdef ECTS
	setup.M8=1;
#else
	mem_test();
#endif

#ifdef MEG4
	setup.M8=0;
#endif
//	setup.M8=0;

// Setup Subs...
	for (int i=11; i<15; i++)
	{
		game_data[setup.team_a].players[i].flags=1;
		game_data[setup.team_b].players[i].flags=1;
	}

	InitialiseTimer();			// Initialise timers for sound drivers
	EUROmatch_info.camera=0;
	EUROmatch_info.audio=FALSE;
	EUROmatch_info.timeit=FALSE;
	EUROmatch_info.offside=TRUE;
	EUROmatch_info.bookings=TRUE;
	EUROmatch_info.freekicks=TRUE;
	EUROmatch_info.substitutes=TRUE;

	EUROmatch_info.time=3;
	EUROmatch_info.tac_1=0;
	EUROmatch_info.tac_2=0;
	match_info.CompetitionType=2;
//	match_info.CompetitionType=PRACTICE;
//	match_info.CompetitionType=PENALTIES;
	EUROmatch_info.crowd=0x1fff;	// Crowd noise level!
	EUROmatch_info.pitch=0x7fff;	// Pitch noise level!
	EUROmatch_info.commentary=0x7fff;	// Commentary level!
	EUROmatch_info.master=0x7fff;	// Master noise level!
	EUROmatch_info.referee_vision=120;
	EUROmatch_info.referee_discipline=80;
 	EUROmatch_info.rand=3523;
	match_info.GameType=0;		// 0 Arcade 1 Simulation...
 	match_info.referee=0;
	EUROmatch_info.wind=0;
//	EUROmatch_info.tga_enable=TRUE;

	net_half=1;				// Network game time...

	say_names=TRUE;

	audio_version=EUROmatch_info.audio;
	if (audio_version)
	{
		if (go_audio())
		{
			UnInitialiseTimer();
			return(FALSE);
		}
	}

	network_on=0;
// Timer stuff...

	ftick=0;
	tick=0;
	count=0;
	game_speed=REAL_SPEED;
	readptr=writeptr=0;
	AddTimer(TIMER_SPEED,nethandler,NetworkHandle);

	injury_time=0;
	claim_key_int();
	init_users();
	init_team();

	machine_no=1;
	get_command_line(argc,argv);

	InitMouse();
	init_keyboard();
	if (logpad_on)
		calibrate_logpad(&joy1_cnt_x,&joy1_cnt_y);

	if (joystick1_on)
	{
		calibrate_joy(0,&joy1_cnt_x,&joy1_cnt_y);
		calibrated_1=TRUE;
#ifdef ECTS
		write_config_file();
#endif
	}

	if (joystick2_on)
	{
		calibrate_joy(1,&joy2_cnt_x,&joy2_cnt_y);
		calibrated_2=TRUE;
#ifdef ECTS
		write_config_file();
#endif
	}

#ifndef NET_GAME
	old_mf=TRUE;
#else
	old_mf=FALSE;
#endif

#ifdef NET_GAME
	foot_init_net();
#endif

/**** Call Game ****/
	match(argc,argv);

#ifdef NET_GAME
	foot_uninit_net();
#endif

	RemoveTimer(NetworkHandle);

	if (audio_version)
	{
		UnInitialiseDIGI();	// Uninitialise SOS
	}

	UnInitialiseTimer();

	release_key_int();

	return(0);
}


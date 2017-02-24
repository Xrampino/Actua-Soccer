#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include "c:\netnow\hmistd.h"
#include "c:\netnow\netnow.h"
#include "c:\netnow\vdata.h"
#include "c:\netnow\vchat.h"
#include "c:\sos\include\sosm.h"
#include "network.h"
#include "defines.h"
#include "mouse.h"

//#include <iostream.h>
//#include <dos.h>

unsigned char machine_no;

// Player vars

volatile int Team_A,Team_B;
volatile int Teams[MAX_NET_USERS],Players[MAX_NET_USERS];
int TeamChoice,PlayerChoice;


//	General vars

char old_mf;
int netsetup_on;		// In network setup
int network_on;		// Network on flag / No of network players
int onetwork_on;
short	wConsoleNode;	// Network ID for machine
short master;			// Network ID for master
volatile int active_nodes;
volatile int net_quit;
int num_of_users=0;


// Packet types

packet_header		in_header;
packet_header		p_header;
packet_data			p_data;
packet_seed			test_seed;
packet_single		test_single;
packet_multiple	test_multiple;

//volatile	packet_multiple copy_multiple[512];
volatile	int writeptr;
volatile	int readptr;

volatile packet_single user_inp;				// Temp input data


// Internal network vars

_NETNOW_NODE_ADDR address[MAX_NET_USERS];	// Station addresses that we know about.
_NETNOW_NODE_ADDR laddress;			 	// Local machines address
volatile	int net_players[16];
volatile int start_multiple; // No of players master has sent to
volatile	int received_seed;  //
volatile	int frame_number;
volatile int slave_pause=FALSE;
volatile	int NetDone;


// Timer vars

volatile int count;
volatile int tick;
volatile int ftick;
int game_speed;

// Richards
volatile int hold_loop;

// User input arrays

struct user_config{
	short type;
	short control;
	int inp_x;
	int inp_y;
	int inp_ox;
	int inp_oy;
	short inp_fb;
	char chng;
	signed char plr;
	};

volatile struct user_config users[MAX_NET_USERS];

struct user_vectors_i{
	short x_f1;
	short y_f2;
	};

volatile struct user_vectors_i users_dir_i[512][MAX_NET_USERS];

int icth,isth;			// viewing angle in integers


// Vars taken from Andy's code (mostly input stuff)

volatile char paused;
volatile char pause_request;
volatile char keys[256];
volatile char key_togs[256];

signed char key1[6];
signed char key2[6];

unsigned short joy1_cnt_x,joy1_cnt_y;
unsigned short joy2_cnt_x,joy2_cnt_y;

int joy1_max_x,joy1_max_y,joy1_min_x,joy1_min_y;
int joy2_max_x,joy2_max_y,joy2_min_x,joy2_min_y;

volatile int joy1_x=0;
volatile int joy1_y=0;
volatile int joy1_fire=0;

volatile int joy2_x=0;
volatile int joy2_y=0;
volatile int joy2_fire=0;

volatile char joy1_move=0;
volatile char joy2_move=0;

char joystick1_on=FALSE;
char joystick2_on=FALSE;

char digital_joy1=FALSE;
char digital_joy2=FALSE;

struct joy_struct {
	int FireA1,FireA2,JoyAX,JoyAY;
	int FireB1,FireB2,JoyBX,JoyBY;
};

/*
struct rjoy_struct {
	unsigned short x1;
	unsigned short y1;
	unsigned short x2;
	unsigned short y2;
	unsigned short sw;
};
	
volatile struct rjoy_struct rjoy_pos;
*/

volatile struct joy_struct joy_pos;

unsigned short dead_zone=25;			// percentage

volatile int ux1,ux2,wptr,rptr;

/********************/
/*  INPUT ROUTINES  */
/********************/


/////////////////
//  JOYSTICKS  //

//Function to gather joystick data and return in a joystick structure

int	x1ok=1;	// These values indicate whether the axes are connected or not...
int	y1ok=2;	// for calibration they should be initialised.
int	x2ok=4;
int	y2ok=8;	
int	bitaccept=15; // Above values OR'ed

#define JOY_TIMEOUT 65535

extern void __far JoyRead3(void *);
extern void __far JoyRead2(void *);
extern void __far JoyRead1(void *);


/******************************************************************************
******************************************************************************/

/*
void	ConvJoys()
{
	joy_pos.FireA1=!((rjoy_pos.sw>>4)&1);
	joy_pos.FireA2=!((rjoy_pos.sw>>5)&1);
	joy_pos.FireB1=!((rjoy_pos.sw>>6)&1);
	joy_pos.FireB2=!((rjoy_pos.sw>>7)&1);
	joy_pos.JoyAX=rjoy_pos.x1;
	joy_pos.JoyAY=rjoy_pos.y1;
	joy_pos.JoyBX=rjoy_pos.x2;
	joy_pos.JoyBY=rjoy_pos.y2;
}
*/

/******************************************************************************
******************************************************************************/
/*
void	ReadJoys()
{
	if (joystick1_on && joystick2_on)
// Two joysticks plugged in...
	{
		JoyRead3(&rjoy_pos);
		ConvJoys();
	}
	else
	{
		if (joystick1_on)
// Port 1 joystick only...
		{
			JoyRead1(&rjoy_pos);
			ConvJoys();
		}
		else
// Port 2 joystick only...
		{
			if (joystick2_on)
			{
				JoyRead2(&rjoy_pos);
				ConvJoys();
			}
		}
	}
}
*/

void	ReadJoys(struct joy_struct *JoyData)
	{
	//read joysticks for calibration - always returns!
	int XJA=-1,YJA=-1,XJB=-1,YJB=-1,Fire,FireA,FireB,j;
	int timecount=0;
	int x1read,y1read,x2read,y2read;
	Fire=((int)inp(0x201) ^ 255)>>4;
	FireA=Fire & 3;
	FireB=(Fire>>2) & 3;

	JoyData->FireA1=FireA & 1;
	JoyData->FireA2=FireA>>1;
	JoyData->FireB1=FireB & 1;
	JoyData->FireB2=FireB>>1;

	XJA=0;
	YJA=0;
	XJB=0;
	YJB=0;

	_disable();
	outp(0x201,255);    //Request a reading from the joystick port

	x1read=x1ok;
	y1read=y1ok;
	x2read=x2ok;
	y2read=y2ok;
	do
		{
		j=(int)inp(0x201);  //read the current port status

		if (x1ok)
			if (x1read=(j & 1)) XJA++;   //increase X counter
		if (y1ok)
			if (y1read=(j & 2)) YJA++;   //increase Y counter
		if (x2ok)
			if (x2read=(j & 4)) XJB++;   //increase X counter
		if (y2ok)
			if (y2read=(j & 8)) YJB++;   //increase Y counter

		timecount++;

		}
	while((j & bitaccept) && timecount<JOY_TIMEOUT);		//this will cause time out during calibration if not connected!
	_enable();

	if (!x1read)
		JoyData->JoyAX=XJA;
	else
		{
		JoyData->JoyAX=0;
		x1ok=0;																//timed out - stop reading!
		bitaccept=x1ok | y1ok | x2ok | y2ok;
		}

	if (!y1read)
		JoyData->JoyAY=YJA;
	else
		{
		JoyData->JoyAY=0;
		y1ok=0;
		bitaccept=x1ok | y1ok | x2ok | y2ok;
		}

	if (!x2read)
		JoyData->JoyBX=XJB;
	else
		{
		JoyData->JoyBX=0;
		x2ok=0;
		bitaccept=x1ok | y1ok | x2ok | y2ok;
		}

	if (!y2read)
		JoyData->JoyBY=YJB;
	else
		{
		JoyData->JoyBY=0;
		y2ok=0;
		bitaccept=x1ok | y1ok | x2ok | y2ok;
		}
	}

void read_joy1(unsigned short *x, unsigned short *y, unsigned char *sw)
{
	*x=joy_pos.JoyAX;
	*y=joy_pos.JoyAY;
	*sw=joy_pos.FireA1|(joy_pos.FireA2<<1);
}

void read_joy2(unsigned short *x, unsigned short *y, unsigned char *sw)
{
	*x=joy_pos.JoyBX;
	*y=joy_pos.JoyBY;
	*sw=joy_pos.FireB1|(joy_pos.FireB2<<1);
}

void read_joystick(char j, unsigned short *x, unsigned short *y, unsigned char *sw)
{
	ReadJoys(&joy_pos);
	if (!j)
		read_joy1(x,y,sw);
	else
		read_joy2(x,y,sw);
}

void get_joy_max_min(char j)
{
	int i;
	unsigned	short x,y;
	unsigned char butt;
	unsigned short max_x=0;
	unsigned short min_x=65535;
	unsigned short max_y=0;
	unsigned short min_y=65535;
	do
	{
		read_joystick(j,&x,&y,&butt);
		if (x>max_x)
			max_x=x;
		if (x<min_x)
			min_x=x;
		if (y>max_y)
			max_y=y;
		if (y<min_y)
			min_y=y;

// STRANGE????  Need this software loop to get normal range values from joystick!
// Shrug....
	for (i=0; i<200000; i++)
	{
		i+=1;
		i-=1;
	}

	}while(!(butt&3));

	if (!j)
	{
		joy1_max_x=max_x;
		joy1_max_y=max_y;
		joy1_min_x=min_x;
		joy1_min_y=min_y;
	}
	else
	{
		joy2_max_x=max_x;
		joy2_max_y=max_y;
		joy2_min_x=min_x;
		joy2_min_y=min_y;
	}
}

void calibrate_joy(char j,unsigned short *x,unsigned short *y)
{
	unsigned short left,right,up,down;
	unsigned char butt;
	unsigned short max_x,min_x,max_y,min_y;
	float dead_zone=0.6;			// 33% dead_zone!
	char str[40];
	printf("\nPlease circle joystick %d now...\n",j+1);
	get_joy_max_min(j);

	if (!j)
	{
		left=joy1_min_x;
		right=joy1_max_x;
		up=joy1_min_y;
		down=joy1_max_y;
	}
	else
	{
		left=joy2_min_x;
		right=joy2_max_x;
		up=joy2_min_y;
		down=joy2_max_y;
	}

	printf("Left %d\n",left);
	printf("Right %d\n",right);
	printf("Up %d\n",up);
	printf("Down %d\n",down);

	printf("\nNow centre joystick %d and press fire...\n",j+1);

	if (!j)
	{
		do
		{
			read_joystick(0,x,y,&butt);
		}while(butt&3);

		do
		{
			read_joystick(0,x,y,&butt);
		}while(!(butt&3));
	}
	else
	{
		do
		{
			read_joystick(1,x,y,&butt);
		}while(butt&3);

		do
		{
			read_joystick(1,x,y,&butt);
		}while(!(butt&3));
	}
}

int sqrt_i(int a)
{
	int x,d,b;
	int bt=0x80000000;
	
	if (a <= 0)	return (0);
	
	for (b=32; b>0; b--)
	{
		if (a&bt)
			break;
		else
			bt>>=1;
	}

	x=1<<(b>>1);

	while (d = ((((x * x - a) / x) + 1) >> 1)) 
		x-=d;
	return (x);
}

void normalise_joy_i(volatile int *x,volatile int *y)
{
	int d;
	d=(((*x)*(*x))+((*y)*(*y)));
	d<<=12;
	if (d>0)
	{
		d=sqrt_i(d);
		*x<<=21;
		*x/=d;
		*y<<=21;
		*y/=d;
	}
	else
	{
		*x=*y=0;
	}
}

int calc_dist_i(int x,int y)
{
	return (sqrt_i(x*x+y*y));
}

void get_joy_dir1(volatile int *x,volatile int *y,volatile int *f)
{
	unsigned short rx,ry;
	unsigned char sw;
	int d;
	*x=*y=0;
	read_joy1(&rx,&ry,&sw);

	*x=rx-joy1_cnt_x;
	*y=ry-joy1_cnt_y;

	ux1=*x;
	ux2=*y;



	d=calc_dist_i((joy1_max_x-joy1_min_x),(joy1_max_y-joy1_min_y))*dead_zone/200;

	if (calc_dist_i(*x,*y)<d)
	{
		joy1_move=FALSE;
		*x=*y=0;
	}
	else
	{
		joy1_move=TRUE;
		normalise_joy_i(x,y);
	}

	if (digital_joy1)
	{
		if (!joy1_move)
		{
			*x=*y=0;
		}
		else
		{
			int d=0;
			if (*y>=0)
			{
				if (*x>=0)
				{
					if (*x>*y)
					{
						if (*x>((*y)*2))
						{
							*x=TUNIT;
							*y=0;
						}
						else
						{
							*x=TDIAG;
							*y=TDIAG;
						}
					}
					else
					{
						if (*y>((*x)*2))
 						{
							*x=0;
							*y=TUNIT;
						}
						else
						{
							*x=TDIAG;
							*y=TDIAG;
						}
					}
				}
				else
				{
					if (-*x>*y)
					{
						if (-*x>((*y)*2))
						{
							*x=-TUNIT;
							*y=0;
						}
						else
						{
							*x=-TDIAG;
							*y=TDIAG;
						}
					}
					else
					{
						if (*y>(-(*x)*2))
 						{
							*x=0;
							*y=TUNIT;
						}
						else
						{
							*x=-TDIAG;
							*y=TDIAG;
						}
					}
				}
			}
			else
			{
				if (*x>=0)
				{
					if (*x>-*y)
					{
						if (x>(-(*y)*2))
						{
							*x=TUNIT;
							*y=0;
						}
						else
						{
							*x=TDIAG;
							*y=-TDIAG;
						}
					}
					else
					{
						if (-*y>((*x)*2))
 						{
							*x=0;
							*y=-TUNIT;
						}
						else
						{
							*x=TDIAG;
							*y=-TDIAG;
						}
					}
				}
				else
				{
					if (-*x>-*y)
					{
						if (-*x>(-*y*2))
						{
							*x=TUNIT;
							*y=0;
						}
						else
						{
							*x=-TDIAG;
							*y=-TDIAG;
						}
					}
					else
					{
						if (-*y>(-(*x)*2))
 						{
							*x=0;
							*y=-TUNIT;
						}
						else
						{
							*x=-TDIAG;
							*y=-TDIAG;
						}
					}
				}
			}
		}
	}
	*f=sw;
}


void get_joy_dir2(volatile int *x,volatile int *y,volatile int *f)
{
	unsigned short rx,ry;
	unsigned char sw;
	int d;
	*x=*y=0;
	read_joy2(&rx,&ry,&sw);

	*x=rx-joy2_cnt_x;
	*y=ry-joy2_cnt_y;
	d=calc_dist_i((joy2_max_x-joy2_min_x),(joy2_max_y-joy2_min_y))*dead_zone/200;

	if (calc_dist_i(*x,*y)<d)
	{
		joy2_move=FALSE;
		*x=*y=0;
	}
	else
	{
		joy2_move=TRUE;
		normalise_joy_i(x,y);
	}

	if (digital_joy2)
	{
		if (!joy2_move)
		{
			*x=*y=0;
		}
		else
		{
			int d=0;
			if (*y>=0)
			{
				if (*x>=0)
				{
					if (*x>*y)
					{
						if (*x>((*y)*2))
						{
							*x=TUNIT;
							*y=0;
						}
						else
						{
							*x=TDIAG;
							*y=TDIAG;
						}
					}
					else
					{
						if (*y>((*x)*2))
 						{
							*x=0;
							*y=TUNIT;
						}
						else
						{
							*x=TDIAG;
							*y=TDIAG;
						}
					}
				}
				else
				{
					if (-*x>*y)
					{
						if (-*x>((*y)*2))
						{
							*x=-TUNIT;
							*y=0;
						}
						else
						{
							*x=-TDIAG;
							*y=TDIAG;
						}
					}
					else
					{
						if (*y>(-(*x)*2))
 						{
							*x=0;
							*y=TUNIT;
						}
						else
						{
							*x=-TDIAG;
							*y=TDIAG;
						}
					}
				}
			}
			else
			{
				if (*x>=0)
				{
					if (*x>-*y)
					{
						if (x>(-(*y)*2))
						{
							*x=TUNIT;
							*y=0;
						}
						else
						{
							*x=TDIAG;
							*y=-TDIAG;
						}
					}
					else
					{
						if (-*y>((*x)*2))
 						{
							*x=0;
							*y=-TUNIT;
						}
						else
						{
							*x=TDIAG;
							*y=-TDIAG;
						}
					}
				}
				else
				{
					if (-*x>-*y)
					{
						if (-*x>(-*y*2))
						{
							*x=TUNIT;
							*y=0;
						}
						else
						{
							*x=-TDIAG;
							*y=-TDIAG;
						}
					}
					else
					{
						if (-*y>(-(*x)*2))
 						{
							*x=0;
							*y=-TUNIT;
						}
						else
						{
							*x=-TDIAG;
							*y=-TDIAG;
						}
					}
				}
			}
		}
	}
	*f=sw;
}



/////////////
//  MOUSE  //

void get_mouse_dir(volatile struct user_config *user)
{
	int x,y;
	ReportMouse();
	x=Mouse.x-160;
	y=Mouse.y-100;
	x<<=15;
	x/=160;
	y<<=15;
	y/=100;

	user->inp_fb=Mouse.b;
	user->inp_x=x;
	user->inp_y=y;

	MouseXYset(160,100);			// reset mouse origin.
}



////////////////
//  KEYBOARD  //

short get_key_code(signed char *ks)
{
	int i;
	short k=0;
	signed short ki;
	for (i=0; i<6; i++)
	{
		ki=*ks++;
		if (ki<0)
		{
			ki=SPECIALK-ki;
			if (keys[ki])
				k+=(1<<i);
		}
		else
			if (keys[ki])
				k+=(1<<i);
	}
	return(k);
}



void get_key_dir(volatile struct user_config *user,signed char *kb)
{
	short k;
	k=get_key_code(kb);
	user->inp_fb=FALSE;

	if (k>=32)			// Fire 2
	{
		user->inp_fb=2;
		k-=32;
	}

	if (k>=16)			// Fire 1
	{
		user->inp_fb+=1;
		k-=16;
	}

	switch(k)
	{
		case(0):
			user->inp_x=0;
			user->inp_y=0;
			break;

		case(1):
			user->inp_x=0;
			user->inp_y=-32768;
			break;

		case(2):
			user->inp_x=0;
			user->inp_y=32767;
			break;
			
		case(4):
			user->inp_x=-32768;
			user->inp_y=0;
			break;

		case(5):
			user->inp_x=-TDIAG;
			user->inp_y=-TDIAG;
			break;

		case(6):
			user->inp_x=-TDIAG;
			user->inp_y=TDIAG;
			break;

		case(7):
			user->inp_x=-32768;
			user->inp_y=0;
			break;

		case(8):
			user->inp_x=32767;
			user->inp_y=0;
			break;

		case(9):
			user->inp_x=TDIAG;
			user->inp_y=-TDIAG;
			break;

		case(10):
			user->inp_x=TDIAG;
			user->inp_y=TDIAG;
			break;

		case(11):
			user->inp_x=32767;
			user->inp_y=0;
			break;

		case(13):
			user->inp_x=0;
			user->inp_y=-32768;
			break;

		case(14):
			user->inp_x=0;
			user->inp_y=32767;
			break;

		default:
			user->inp_x=0;
			user->inp_y=0;
			break;
	}
}			



///////////////
//  GENERAL  //

void get_user_inputs()
{
	int i;

	ReadJoys(&joy_pos);

	for (i=0; i<num_of_users; i++)
	{
		switch(users[i].control)
		{
			case(JOY1_CTRL):
				get_joy_dir1(&joy1_x,&joy1_y,&joy1_fire);
				users[i].inp_x=joy1_x;
				users[i].inp_y=joy1_y;
				users[i].inp_fb=joy1_fire;
				break;
			
			case(JOY2_CTRL):
				get_joy_dir2(&joy2_x,&joy2_y,&joy2_fire);
				users[i].inp_x=joy2_x;
				users[i].inp_y=joy2_y;
				users[i].inp_fb=joy2_fire;
				break;
			
			case(KEY1_CTRL):
				get_key_dir(&users[i],key1);
				break;

			case(KEY2_CTRL):
				get_key_dir(&users[i],key2);
				break;

			case(MOUSE_CTRL):
				get_mouse_dir(&users[i]);
				break;
		}
	}
}

void process_user_inputs()
{
	int x,y,i,a,b;

	for (i=0; i<num_of_users; i++)
	{
		if (users[i].type && users[i].control!=NET_CTRL)		// Not computer or net guy
		{
			x=users[i].inp_x;
			y=users[i].inp_y;
			a=x*icth;
			b=y*isth;
			a=(a-b)>>15;

			if (a<-32767)
				a=-32767;
			if (a>32767)
				a=32767;

			users_dir_i[writeptr][i].x_f1=a;

			a=y*icth;
			b=x*isth;
			a=(a+b)>>15;

			if (a<-32767)
				a=-32767;
			if (a>32767)
				a=32767;

			users_dir_i[writeptr][i].y_f2=a;

			users_dir_i[writeptr][i].x_f1&=0xfffe;
			users_dir_i[writeptr][i].x_f1|=(users[i].inp_fb&1);
			users_dir_i[writeptr][i].y_f2&=0xfffe;
			users_dir_i[writeptr][i].y_f2|=((users[i].inp_fb&2)>>1);
			users[i].inp_ox=x;
			users[i].inp_oy=y;
		}
	}
}



/**************************/
/*  INTERRUPT TIMER CODE  */
/**************************/


unsigned int NetworkHandle; // Handle for this timer routine

void __far nethandler(void)
	{
	int i;
	count++;
	ftick+=game_speed;
	if (ftick>=TIMER_SPEED)
		{
		do	
			ftick-=TIMER_SPEED;
		while (ftick>TIMER_SPEED);
		tick++;
		hold_loop=1; //ACTIVE

		if (!old_mf)
		{
			if (netsetup_on)  					// If in network setup...
				{
				if (network_on)
					NetInitialisation();			// Scan for new nodes and player data
				}
			else
				{
				if (network_on)					// If a network game...
					{
					if (wConsoleNode==master)										// If master...
						{
						if ( start_multiple==network_on-1 )  					// If all data sent last frame
							{
							for (i=0;i<MAX_NET_USERS;i++)
								{
								users_dir_i[writeptr][i].x_f1=users_dir_i[(writeptr-1)&511][i].x_f1; // Copy all last input data for defaults
								users_dir_i[writeptr][i].y_f2=users_dir_i[(writeptr-1)&511][i].y_f2; // ...
								}
							get_user_inputs();  										// Read own input data..
							process_user_inputs();
							if (!(tick&7)) putch('.');
							receive_all_singles();									// Receive input data from all other machines
							}
						if (active_nodes==network_on)								// Only start transmitting when ready
							{
							if (start_multiple!=network_on-1 || !paused)		// Stop sending if paused, and block fully transmitted
								{
								send_multiple();
								if ( start_multiple==network_on-1 ) 			// If block fully transmitted, move to next
									{
									writeptr++;
									writeptr&=511;
									}
								}
							}
						}
					else								// If slave...
						{
						get_user_inputs();		// Read own input data
						process_user_inputs();

						for (i=0; i<network_on; i++)
							if (users[i].type && users[i].control!=NET_CTRL &&										// If local human user,... 
					      	(users_dir_i[writeptr][i].x_f1!=users_dir_i[(writeptr-1)&511][i].x_f1 ||	// and input has changed... 
					       	 users_dir_i[writeptr][i].y_f2!=users_dir_i[(writeptr-1)&511][i].y_f2) )
								send_single(i);																				// then send to master

						receive_multiple();  	// Receive all input data from master
						}
					}
				else  				// If not a network game...
					{
					if (!paused)	// and not paused...
						{
						get_user_inputs();
						process_user_inputs();
						writeptr++;
						writeptr&=511;				// Move to next block
						}
					}
				}
			}
		}
	}

// Wait for next interrupt
void TickPause()
{
	int tcount;
	tcount=count;
	while (count<=tcount+TIMER_FRAC);
}



/********************/
/*  RECEIVING DATA  */
/********************/

// Routine for master to receive all input data types.
void	receive_all_singles()
{
	packet_header	*header;
	packet_single	*data;
	packet_info		info;
	PSTR	pPacket;

	if (network_on)
	{
		header=&in_header;
		while (hmiNETNOWGetHeader((PSTR)header,sizeof(packet_header),&pPacket))
		{
			switch(header->type)
			{
				case NET_ONLINE:
					hmiNETNOWGetBlock(pPacket,(PSTR) &info,sizeof(packet_info));

					// Master receiving data

					break;

				case NET_SINGLE:
					data=&users_dir_i[writeptr][header->player];
					hmiNETNOWGetBlock(pPacket,(PSTR)data,sizeof(packet_single));
					break;

				case NET_READY:
		puts("NET_READY received.");
					active_nodes++;
					break;

				case NET_QUIT:
		 			hmiNETNOWPostListen();
					send_quit();	// All quit if anyone quits!
					break;

				case NET_PAUSE:
					slave_pause=TRUE;
					break;
			}
 			hmiNETNOWPostListen();
		}
	}
}

// Routine for slaves to receive all input data types.
void	receive_multiple()
{
	packet_header	*header;
	packet_multiple *data;
	packet_single	*sing;
	packet_seed		*seed;
	packet_info		info;
	packet_pause	pausep;
	PSTR	pPacket;
	if (network_on)
	{
		header=&in_header;
		sing=&test_single;
		seed=&test_seed;
		while (hmiNETNOWGetHeader((PSTR)header,sizeof(packet_header),&pPacket))
		{
			switch(header->type)
			{
				case NET_ONLINE:
					hmiNETNOWGetBlock(pPacket,(PSTR) &info,sizeof(packet_info));

					// Slave receiving data

					break;

				case NET_MULTIPLE:
					data=(packet_multiple *)users_dir_i[writeptr];
					hmiNETNOWGetBlock(pPacket,(PSTR)data,sizeof(packet_multiple));
					writeptr++;
					writeptr&=511;
					if (!net_quit) active_nodes=network_on;
					break;

				case NET_SEED:
					// Slave receiving seed
					hmiNETNOWGetBlock(pPacket,(PSTR)seed,sizeof(packet_seed));
					received_seed=seed->num?seed->num:1;
					break;

				case NET_QUIT:
					net_quit=TRUE;
					break;

				case NET_PAUSE:
					hmiNETNOWGetBlock(pPacket,(PSTR) &pausep,sizeof(packet_pause));
					paused=pausep.paused;
					break;
			}
 			hmiNETNOWPostListen();
		}
	}
}



/******************/
/*  SENDING DATA  */
/******************/

//Master transmits all input data, sends NET_MULTIPLE header and multiple packet
void	send_multiple()
{
	packet_header		*header;
	packet_multiple	*data;
	int	i,sent;

	if (network_on)
	{
		header=&p_header;
		data=&test_multiple;

		header->player=wConsoleNode;	
		header->type=NET_MULTIPLE;
		header->frame=frame_number;
		frame_number++;

//		data=(packet_single *)users_dir_i[writeptr];
		for (i=0;i<network_on;i++)
		{
			data->inp[i].x=users_dir_i[writeptr][i].x_f1;
			data->inp[i].y=users_dir_i[writeptr][i].y_f2;
		}

		i=abs(start_multiple);
		sent=TRUE;
		while (i>=0 && sent)
		{
			if (i!=master)
				sent=hmiNETNOWSendData((PSTR) header,sizeof(packet_header),(PSTR) data,sizeof(packet_multiple),i);
			else
				sent=TRUE;
			if (sent) i--;
		}

		if (sent) start_multiple=network_on-1;
		else start_multiple=-i;
	}
}


// Slave sends own input data, send NET_SINGLE header and input packet to master
void	send_single(int plyr)
{
	packet_header	*header;
	packet_single	*data;
	int	wait;

	if (network_on)
	{
		header=&p_header;
		data=&test_single;

		header->player=wConsoleNode;
		header->type=NET_SINGLE;
		data=(packet_single *)&users_dir_i[writeptr][plyr];

//		do
			wait=hmiNETNOWSendData((PSTR) header,sizeof(packet_header),(PSTR) data,sizeof(packet_single),master);
//		while( !wait );
	}
}


// Slave is ready to play, send NET_READY header and null data packet to master
void	send_ready()
{
	packet_header	*header;
	packet_data		*data;

	if (network_on)
	{
		header=&p_header;
		data=&p_data;

		header->player=wConsoleNode;	
		header->type=NET_READY;

		if (wConsoleNode==master)
			active_nodes++;			// If master just increase active nodes
		else
		{puts("NET_READY sent.");
		while( !hmiNETNOWSendData((PSTR) header,sizeof(packet_header),(PSTR) data,0,master) );
		}
	}
}


// Master sends a random seed, send NET_SEED header and seed packet to slaves
void	send_seed(int num)
{
	packet_header	*header;
	packet_seed		*data;
	int	i;

	if (network_on)
	{
		header=&p_header;
		data=&test_seed;

		header->player=wConsoleNode;	
		header->type=NET_SEED;
		data->num=num;

		for (i=0;i<network_on;i++)
			if (i!=master)
				while( !hmiNETNOWSendData((PSTR) header,sizeof(packet_header),(PSTR) data,sizeof(packet_seed),i) );

//		puts("Net_seed sent");
	}
}


// Send a message, send NET_MESSAGE header and message packet containing string (watch maximum length) to everyone
void	send_mes(char *m)
{
	packet_header	*header;
	packet_data		*data;
	WORD	head_size,data_size;
	int	i;

	if (network_on)
	{
		header=&p_header;
		data=&p_data;

		strcpy(data->mes,m);
		header->player=wConsoleNode;	
		header->type=NET_MESSAGE;

		for (i=0;i<network_on;i++)
		{
			if (i!=wConsoleNode)
				while( !hmiNETNOWSendData((PSTR) header,sizeof(packet_header),(PSTR) data,sizeof(packet_data),i) );
		}
	}
}


// Player is to quit, send NET_QUIT header and null data packet, if master quits, all nodes quit
void	send_quit()
{
	packet_header	*header;
	packet_data		*data;
	WORD				head_size,data_size;
	int				i;

	if (network_on)
	{
		header=&p_header;
		data=&p_data;

		header->player=wConsoleNode;	
		header->type=NET_QUIT;

		if (wConsoleNode==master)
		{
			for (i=0;i<network_on;i++)
				if (i!=wConsoleNode)
					while( !hmiNETNOWSendData((PSTR) header,sizeof(packet_header),(PSTR) data,0,i) );

			net_quit=TRUE;
		}
		else	while( !hmiNETNOWSendData((PSTR) header,sizeof(packet_header),(PSTR) data,0,master) );
	}
}


// Send pause request, send NET_PAUSE header and pause packet to master
void	send_pause()
	{
	packet_header header;
	packet_pause  data;

	if (network_on)
		{
		header.type=NET_PAUSE;
		data.paused=!paused;				//request to invert! (not used by master - simply inverts its copy!)
		while (!hmiNETNOWSendData((PSTR) &header,sizeof(packet_header),(PSTR) &data,sizeof(packet_pause),master));
		}
	}


// Transmit pause to slaves, send NET_PAUSE header and pause packet to all slaves
void	transmitpausetoslaves(void)
	{
	//transmit new pause status to slaves
	packet_header header;
	packet_pause  data;
	int	i;

	if (network_on)
		{
		header.type=NET_PAUSE;
		data.paused=paused;				//request to invert!
		for (i=0;i<network_on;i++)
			if (i!=master)
				while (!hmiNETNOWSendData((PSTR) &header,sizeof(packet_header),(PSTR) &data,sizeof(packet_pause),i));
		}
	}



/****************************/
/*  INITIALISE/SYNCHRONISE  */
/****************************/


// Send initialisation data to or from newly logged on node (broadcast message necessary, others must discard)
void	TransmitInit(void)
	{
	packet_header header;
	packet_info	  info;
	if (network_on)
		{
		// Send address & data
		info.address=laddress;
		info.Team_A=Team_A;
		info.Team_B=Team_B;
		info.Team=TeamChoice;
		info.Player=PlayerChoice;

		header.type=NET_ONLINE;
		while (!hmiNETNOWSendData((PSTR) &header,sizeof(packet_header),(PSTR) &info,sizeof(packet_info),_NETNOW_BROADCAST));
		}
	}


// Finds if supplied address is in address list
int FindAddress(_NETNOW_NODE_ADDR daddress)
{
	int	duplic=-1;
	int	i,j;
	char	diff;
	char	*a1,*a2;
	int	sizeaddress;

	sizeaddress=sizeof(_NETNOW_NODE_ADDR);
	for (i=0;i<network_on;i++)
		{
		diff=FALSE;
		for (j=0;j<sizeaddress;j++)
			{
			a1=(char *) &address[i];
			a2=(char *) &daddress;
			if (*(a1+j)!=*(a2+j)) diff=TRUE;
			}
		if (!diff) { duplic=i; break; }
		}
	return (duplic);
}


void	NetInitialisation()
{
	packet_header	header;
	packet_info		info;
	packet_seed		*seed;
	PSTR	pPacket;
	_NETNOW_NODE_ADDR taddress;
	int	error,Node;
int i;
	seed=&test_seed;
//	wNETNodes=network_on;
	while (hmiNETNOWGetHeader((PSTR) &header,sizeof(packet_header),&pPacket))
		{
		switch(header.type)
			{

			// Received online broadcast...
			case NET_ONLINE:
				hmiNETNOWGetBlock(pPacket,(PSTR) &info,sizeof(packet_info));

				// Have we already added this node (will happen a lot because this is a broadcast message)
				if (FindAddress(info.address)<0 && !NetDone)
				{	
					// This is a new node - add it in.
					error=hmiNETNOWAddNode(&info.address);
					switch(error)
					{
						case _NETNOW_ADD_COMPLETE:
							hmiNETNOWSortNodes();
							address[network_on]=info.address;
							if (info.Team_A>=0) Team_A=info.Team_A,Team_B=info.Team_B;
							Teams[network_on]=info.Team;
							Players[network_on]=info.Player;
							network_on++;

							// Send own data back through a NET_ONLINE message, those already on will ignore!!!
							TransmitInit();
							break;

						case _NETNOW_ADD_DUPLICATE:
							exit(1);
							break;
						case _NETNOW_ADD_LIST_FULL:
							exit(1);
							break;
						default:
							break;
					}
				}
				break;

			// Received go message, find node number; no more people can log on now.
			case	NET_GO:
				if (!net_players[header.player])
				{
					NetDone++;
					net_players[header.player]=TRUE;
//					if (NetDone<=1)
//					{
//						SendNetDone();
//						FoundNodes();
//						SendPlayerInfo();
//					}
				}
				break;

			// Received initialisation info (team or player choices)
			case NET_INFO:
				hmiNETNOWGetBlock(pPacket,(PSTR) &info,sizeof(packet_info));

				// Set up player data
				if (info.Team_A>=0)
					{
					Team_A=info.Team_A;
				   Team_B=info.Team_B;
					}
				else
					{
					Node=FindAddress(info.address);
					if (header.player>=0)
						{
						// Informant has sent his node value, swap own data structures to match...
						taddress=address[Node];
						address[Node]=address[header.player];
						address[header.player]=taddress;
						Teams[Node]=Teams[header.player];
						Players[Node]=Players[header.player];
						Node=header.player;
						}
					Teams[Node]=info.Team;
					Players[Node]=info.Player;
					}
				break;

			// Received seed from master
 			case NET_SEED:
//				puts("Net_seed found");
				hmiNETNOWGetBlock(pPacket,(PSTR)seed,sizeof(packet_seed));
				received_seed=seed->num?seed->num:1;
				break;

			// Received quit command from master
			case NET_QUIT:
				puts("Net_quit found");
	
				net_quit=TRUE;
				break;
			}
 		hmiNETNOWPostListen();
		}
}


// Finished waiting for new nodes, find no of nodes and own node number
void	FoundNodes()
{
	if (master!=0)
	{
		network_on=hmiNETNOWGetActiveNodes();		// Get active nodes
		wConsoleNode=hmiNETNOWGetConsoleNode();	// Get console node
		master=0;
//		num_of_users=network_on;
		start_multiple=network_on-1;
	}
}


// Player presses start
void	SendNetDone()
{
	packet_header header;
	packet_data	  data;
	int	i,node,tval;

	NetDone++;
	FoundNodes();

	node=FindAddress(laddress);
	address[node]=address[wConsoleNode];
	address[wConsoleNode]=laddress;
	tval=Teams[node];
	Teams[node]=Teams[wConsoleNode];
	Teams[wConsoleNode]=tval;
	tval=Players[node];
	Players[node]=Players[wConsoleNode];
	Players[wConsoleNode]=tval;
	net_players[wConsoleNode]=TRUE;

	header.player=wConsoleNode;
 	header.type=NET_GO;

	for (i=0;i<network_on;i++)
		if (i!=wConsoleNode)
		 	while (!hmiNETNOWSendData((PSTR) &header,sizeof(packet_header),(PSTR) &data,0,i));

	SendPlayerInfo();
}


void	SendTeamInfo()
{
	packet_header	*header;
	packet_info		info;
	int	i;

	if (network_on)
	{
		header=&p_header;

		// Set up team data
		info.Team_A=Team_A;
		info.Team_B=Team_B;

		header->type=NET_INFO;
		for (i=0;i<network_on;i++)
			if (i!=wConsoleNode)
				while (!hmiNETNOWSendData((PSTR) header,sizeof(packet_header),(PSTR) &info,sizeof(packet_info),i));
	}
}

void	SendPlayerInfo()
{
	packet_header	*header;
	packet_info		info;
	int	i;

	if (network_on)
	{
		header=&p_header;

		// Set up player data
		info.Team_A=info.Team_B=-1;
		info.Team=TeamChoice;
		info.Player=PlayerChoice;
		info.address=address[(wConsoleNode<0) ? 0 : wConsoleNode];

		header->player=wConsoleNode;	
		header->type=NET_INFO;

		for (i=0;i<network_on;i++)
			if (i!=wConsoleNode)
				while( !hmiNETNOWSendData((PSTR) header,sizeof(packet_header),(PSTR) &info,sizeof(packet_info),i) );
	}
}


void pausehandler()
	{
	if (pause_request)
		{
		if (!network_on)
			{
			paused=!paused;
			}
		else
			{
			if (wConsoleNode==master)
				{
				//master initiated pause.
				paused=!paused;
				transmitpausetoslaves();			//all machines will pause
				}
			else
				{
				send_pause();					//send pause to master
				}
			}
		pause_request=FALSE;
		}

	if (network_on && slave_pause && wConsoleNode==master)
		{
		//master received a request to pause from slave
		paused=!paused;
		transmitpausetoslaves();
		slave_pause=FALSE;
		}
	}



/*****************/
/* NETWORK SETUP */
/*****************/

int Initialise_Network()
{
	int i;
//	active_nodes=1;		// if no network 1 player.
	net_quit=FALSE;
	master=-1;
	wConsoleNode=-1;
	if (network_on)
	{
		received_seed=FALSE;
		frame_number=0;
		active_nodes=0;		//reset if network on.

//		puts ("INTIALIZING NETWORK.");

		if ( hmiNETNOWInitSystem( 16 ) != _NETNOW_NO_ERROR )
		{
//			puts( "ERROR: NetNOW! could not locate IPX or NetBIOS!" );
			network_on=FALSE;
			netsetup_on=FALSE;
			old_mf=TRUE;
			return(-1);				//...
		}
		else
		{
//			puts( "NetNOW! system initialized!" );
			// Check for information display
			if ( wNETInfoFlag )
				switch( hmiNETNOWGetNetworkType() )
				{
					case  _NETNOW_IPX    :
						// display type
//						puts( "Network is using a IPX based protocol." );
						break;
					case  _NETNOW_NETBIOS:
						// display type
//						puts( "Network is using a NetBIOS based protocol." );
						break;
				}

			while (hmiNETNOWPostListen());

			for (i=0;i<MAX_NET_USERS;i++)	net_players[i]=FALSE;

			hmiNETNOWGetNetworkAddr(&laddress);		//read this nodes address.
			address[0]=laddress;
			TransmitInit();								//send NET_ONLINE (with address) as a broadcast to other machines

			NetDone=0;
			network_on=onetwork_on=1;
		}	
	}
	return (0);
}


void	close_network()
{
	packet_header	*header;
	PSTR	pPacket;
	short	head_size;
	if (network_on)
	{
//		puts("Resetting network.");
		header=&in_header;
		hmiNETNOWPostListen();
		while (hmiNETNOWGetHeader((PSTR)header,sizeof(packet_header),&pPacket))	hmiNETNOWPostListen();
		hmiNETNOWUnInitSystem();
//		puts("Network removed.");
	}
	netsetup_on=FALSE;
	network_on=FALSE;
	old_mf=TRUE;
	master=-1;
}



int Poll_Network()
{
	static scount=0;
	int i,s;
//	if (!(count&127)) putch('.');
//	if (keys[0x13]) {close_network();exit(1);}
	if (NetDone<network_on)
	{
		return (-1);
		if (onetwork_on!=network_on)
		{
			for (i=onetwork_on;i<network_on;i++)
				printf("\nFound node %d\n",i);
			onetwork_on=network_on;
		}
		return (-1);
	}
	else
	{
		if (wConsoleNode==master)
			{
			if (!(s=clock()&0xffff)) s=1;
			send_seed(s);
			}
		else
			while(!(s=received_seed));
		return (s);
	}
}


int Start_Network_Game()
{
	int i;
	Team_A=-1;
	Team_B=-1;
	for (i=0; i<MAX_NET_USERS; i++)
	{
		Teams[i]=-1;
		Players[i]=-1;
	}
	TeamChoice=-1;
	PlayerChoice=-1;
	network_on=netsetup_on=TRUE;
	old_mf=FALSE;
	return (Initialise_Network());
}


void Network_Play_Ready()
{
	if (network_on) 
	{
		send_ready();
		while (active_nodes<network_on);	// escape key?
	}
}


void Quit_Network_Play()
{
	if (network_on)
	{
		send_quit();
		while (!net_quit); // Timeout??
		active_nodes=0;
	}
}


void End_Network_Game()
{
	if (network_on)
		close_network();
}

int NetTest()
{
	int i,Starts,Seed,stick;
	char TeamsSelected,ChoiceAltered,StartPressed;


	//...whatever front end stuff comes first...


	// There are variables Team_A & Team_B for teams playing, TeamChoice for this players choice from these
	// two, (value 0 or 1), PlayerChoice is the player in the team chosen, 1 to 11 (1 indicates auto-player).
	// The variable network_on is the number of players currently logged on to the game, and the arrays
	// Teams[] and Players[] give the current selections of all the players from 0 to network_on-1, (Note, which is
	// your entry in this array is NOT stored!), you may also want to use the local variable Starts (see below)


	if (Start_Network_Game()<0)	// Initialises Team_A, Team_B, TeamChoice & PlayerChoice and starts network
		{
		old_mf=1;
		return(-1);
		}
	TickPause();

	stick=tick;

	// Choose teams to play
	while (Team_A<0)  // Wait until they are chosen  (add escape key?)
	{
		TeamsSelected=1;	// Your condition

		// If local user sets Team_A & Team_B first send them using SendTeamInfo()
 		if (TeamsSelected)
		{
			Team_A=14;Team_B=0;
			SendTeamInfo();
		}
		TickPause();
Poll_Network();

	}

//printf("\nTeam %d plays team %d\n",Team_A,Team_B);


	// Teams are chosen, allow player to choose team to play for and player to control...
	// 2 is added to TeamChoice when player presses start 
//	puts("Choose team, 'A' or 'B', then press return");
	do 
	{
		// If start has been pressed, no further selection allowed
		if (TeamChoice<2)
		{

			// Your condition
			ChoiceAltered=machine_no;
//			if	(keys[0x1e]) ChoiceAltered=1;
//			if	(keys[0x30]) ChoiceAltered=2;

			// If local user alters TeamChoice or PlayerChoice then call SendPlayerInfo();
			// Must check Players and Teams arrays to make sure no-one else has chosen the same
			if (ChoiceAltered)
			{
				TeamChoice=ChoiceAltered-1;
//				if (TeamChoice==0) puts("Team A chosen");
//				else puts("Team B chosen");
				PlayerChoice=1;
				SendPlayerInfo();
			}

			// Your condition
			StartPressed=1;//(keys[0x1c]);
			
			// If the start button is pressed and team is chosen add 2 to TeamChoice...
			if (TeamChoice>=0 && PlayerChoice>=0 && StartPressed)
			{
//				puts("OK, now waiting for others to start");
				TeamChoice+=2;
				SendPlayerInfo();
			}
		}
		TickPause();
Poll_Network();

		// Condition indicating selection complete (player chosen + start button), perhaps Starts should be displayed
		Starts=0;
		for (i=0;i<network_on;i++)
			if (Teams[i]>=2) Starts++;
	} while ((Starts<network_on || Starts<=1) && tick<stick+10*20); // Must be more than one player!

	if (tick<stick+10*20)
		{
		// Final syncronisation (sorts nodes and sets random seed)
		SendNetDone();
		while ((Seed=Poll_Network())<0);  // (Add escape key?)
		netsetup_on=FALSE;

		// Remove start flags from team data
		for (i=0;i<network_on;i++)
			Teams[i]-=2;


		// Now set Andy's data structures from the network variables


//		printf("\nTeam %d plays team %d\n",Team_A,Team_B);
//		printf("This node is %d\n",wConsoleNode);
//		printf("This node chose team %d, player %d\n",TeamChoice,PlayerChoice);
//		for (i=0;i<network_on;i++)
//			printf("Node %d plays team %d, player %d\n",i,Teams[i],Players[i]);
//		printf("Seed is %d\n",Seed);
		}
	else
		{
		End_Network_Game();	// Cleans up network stuff
		old_mf=1;
		return (-1);
		}

	// ...call the game...

	// ...whetever front end stuff comes after...

	return (0);
}

void crap()
{
	printf(" net %d  %d \n",*(int *)&users[0].inp_x,&users[0].inp_x);
}

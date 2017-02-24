#include "c:\netnow\hmistd.h"
#include "c:\netnow\netnow.h"
#include "c:\netnow\vdata.h"
#include "c:\netnow\vchat.h"
//#include "digi.h"
#include "cgdv.h"
#include "c:\sos\include\sosm.h"


#define	YES					1
#define	NO						0
#define	FRIENDLY				0
#define	LEAGUE				1
#define	CUP					2
#define	PRACTICE				3
#define	NETWORK				4

extern 	int	x1ok;	
extern 	int	y1ok;	
extern 	int	x2ok;
extern 	int	y2ok;	
extern 	int	bitaccept; 

extern 	volatile int Team_A,Team_B;
extern  	unsigned short joy1_cnt_x,joy1_cnt_y;
extern  	unsigned short joy2_cnt_x,joy2_cnt_y;
extern	int joy1_max_x,joy1_max_y,joy1_min_x,joy1_min_y;
extern	int joy2_max_x,joy2_max_y,joy2_min_x,joy2_min_y;

short		DIGIdrvh;

char		calibrate_flag;
unsigned short max_x;
unsigned short min_x;
unsigned short max_y;
unsigned short min_y;
int	slide_x;	
int	slide_y;	
char	print_joy_message,print_red_message;

//ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป 
//บ                                                                                                                              บ
//บ  Checks to see if network is on and if so allows NETWORK option to appear as a competition type.                             บ
//บ																                                                                              บ
//ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ 

int	CheckFORnet()
{
		if ( ( hmiNETNOWInitSystem( 16 ) != _NETNOW_NO_ERROR) )
			return	(NETWORK-1);
		else
			return	(NETWORK);

}

//ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป 
//บ                                                                                                                              บ
//บ  Deinitialises netstuff if it was previously initialised...                                                                  บ
//บ																                                                                              บ
//ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ 

void	DeinitialiseNET(int netflag)
{
		if (netflag==NETWORK)
			hmiNETNOWUnInitSystem();
}


//ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป 
//บ                                                                                                                              บ
//บ  Sets up variables indicating that network game is to begin....                                                              บ
//บ																                                                                              บ
//ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ 

void	Init_Network_Game()
{
	Start_Network_Game();



//	printf("Initialises Team_A, Team_B, TeamChoice & PlayerChoice and starts network\n");
}

//ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป 
//บ                                                                                                                              บ
//บ  Tells network which two countries are to take part in netgame...                                                            บ
//บ																                                                                              บ
//ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ 

void	SendNETTeamInfo()
{
 	SendTeamInfo();
//	printf("\nTeam %d plays team %d\n",Team_A,Team_B);
}


//ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป 
//บ                                                                                                                              บ
//บ  Short delay before any more netinfo can be sent...                                                                          บ
//บ																                                                                              บ
//ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ 

void	TickerPause()
{
//		printf("ticker....delay\n");
		TickPause();
}


//ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป 
//บ                                                                                                                              บ
//บ  Send data indicating which player user is to control....                                                                    บ
//บ																                                                                              บ
//ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ 

void	SendPlayerChoice()
{
				SendPlayerInfo();
}

//ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป 
//บ                                                                                                                              บ
//บ  All users have selected teams and players....                                                                               บ
//บ																                                                                              บ
//ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ 
//
//void	SendNetOKAY()
//{
//				SendNetDone();
//}
//
//ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป 
//บ                                                                                                                              บ
//บ  Polls all network machines....                                                                                              บ
//บ																                                                                              บ
//ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ 
//
//int Polling_Network()
//{
//			return	(Poll_Network());
//}



void	InitCalibration(int j)
{
			max_x				=	0;		
			min_x				=	65535;
			max_y				=	0;
			min_y				=	65535;
			calibrate_flag	=	NULL;
			print_joy_message	=	1; 

			x1ok 	  = 1;	
			y1ok 	  = 2;	
			x2ok 	  = 4;	
			y2ok 	  = 8;	
			bitaccept = x1ok+y1ok+x2ok+y2ok;
}


void	CalibrateJoy(int j)	
{
		unsigned	short x,y;
		unsigned char butt;

//		x1ok			=	1;	  
//		y1ok			=	2;	  
//		x2ok			=	4;	  
//		y2ok			=	8;	  
//		bitaccept	=	15;  

		if (calibrate_flag==2 || calibrate_flag==3)
		{
			if (!j)
					read_joystick(0,&joy1_cnt_x,&joy1_cnt_y,&butt);
			else
					read_joystick(1,&joy2_cnt_x,&joy2_cnt_y,&butt);
		}




		
		if (calibrate_flag==3 && ( butt & 3)!=0 )
		{

//			if (!j)
//				{
//					joy1_cnt_x	=	x;
//					joy1_cnt_y	=	y;
//				}				
//			else
//				{
//					joy2_cnt_x	=	x;
//					joy2_cnt_y	=	y;
//				}				
//			
				print_joy_message	=	1; 
			 	calibrate_flag		=	8;		//255;
		}
	

		if (calibrate_flag==2 && ( butt & 3)==0 )
			 	calibrate_flag		=	3;

		if (calibrate_flag==NULL)
				calibrate_flag++;

		if (calibrate_flag==1)
		{	
			read_joystick(j,&x,&y,&butt);

			if (x>max_x)
				max_x	=	x;
			if (x<min_x)
				min_x	=	x;
			if (y>max_y)
				max_y	=	y;
			if (y<min_y)
				min_y	=	y;

			if ( ( butt & 3)!=0 )
			{
				print_joy_message	=	1; 
				calibrate_flag		=	2;

					if (!j)
					{
						joy1_max_x=max_x;
						joy1_max_y=max_y;
						joy1_min_x=min_x;
						joy1_min_y=min_y;
					}
							else
					{
						joy2_max_x	=	max_x;
						joy2_max_y	=	max_y;
						joy2_min_x	=	min_x;
						joy2_min_y	=	min_y;
					}
			}
		}
}


//void	setdigivar(short handle)
//{
//		DIGIdrvh		=	handle; 	
//}
//
//void	PLAYgdv()
//{
//	char	*GDV_MEMORY;
//	GDV_MEMORY = (BYTE *) malloc( GDV_MEM );  
//	cgdv("swhole_s.gdv",PL_SOUND,GDV_MEMORY);
//}

 					  
/********************************************************/														 
/*   3D ENGINE - Football object data header  14/04/95  */
/********************************************************/

#include "defs.h"

// Motion captures

#ifdef NEW
#define MC_NO 117			// No of captures
#else
#define MC_NO 108			// No of captures
#endif

extern mcap *mcaps;
extern mcap mcaps8[MC_NO];
extern mcap mcaps4[MC_NO];

// Footballer captures

//Goalie captures

#define MC_AFOOTB 0		// 23 Frames
#define MC_AFOOTC 1		// 86 Frames
#define MC_ABODYB 2		// 53 Frames
#define MC_ABODYC 3		// 43 Frames
#define MC_AHEADB 4		// 27 Frames
#define MC_AHEADC 5		// 46 Frames
#define MC_AJUMPB 6		// 28 Frames
#define MC_AJUMPC 7		// 38 Frames

#define MC_BFOOTBL 8 	// 21 Frames
#define MC_BFOOTBR 9 	// 21 Frames
#define MC_BFOOTCL 10 	// 42 Frames
#define MC_BFOOTCR 11 	// 42 Frames
#define MC_BBODYBL 12 	// 27 Frames
#define MC_BBODYBR 13 	// 27 Frames
#define MC_BBODYCL 14 	// 43 Frames
#define MC_BBODYCR 15 	// 43 Frames
#define MC_BHEADBL 16 	// 32 Frames
#define MC_BHEADBR 17 	// 32 Frames
#define MC_BHEADCL 18 	// 36 Frames
#define MC_BHEADCR 19 	// 36 Frames
#define MC_BJUMPBL 20 	// 36 Frames
#define MC_BJUMPBR 21 	// 36 Frames

#define MC_CFOOTBL 22 	// 49 Frames
#define MC_CFOOTBR 23 	// 49 Frames
#define MC_CFOOTCL 24 	// 50 Frames
#define MC_CFOOTCR 25 	// 50 Frames
#define MC_CBODYBL 26 	// 45 Frames
#define MC_CBODYBR 27 	// 45 Frames
#define MC_CBODYCL 28 	// 48 Frames
#define MC_CBODYCR 29 	// 48 Frames
#define MC_CHEADBL 30 	// 44 Frames
#define MC_CHEADBR 31 	// 44 Frames
#define MC_CJUMPBL 32 	// 47 Frames
#define MC_CJUMPBR 33 	// 47 Frames

#define MC_SHOOTR 34		// 36 Frames
#define MC_SHOOTL 35		// 36 Frames
#define MC_CHIPR 36		// 30 Frames
#define MC_CHIPL 37		// 30 Frames
#define MC_PASSR 38		// 33 Frames
#define MC_PASSL 39		// 33 Frames
#define MC_CROSSR 40		// 36 Frames
#define MC_CROSSL 41		// 36 Frames
#define MC_VOLLEYR 42	// 30 Frames
#define MC_VOLLEYL 43	// 30 Frames

#define MC_TOER 38		// 35 Frames .
#define MC_TOEL 39		// 35 Frames .
#define MC_DIAGPASSR 46	// 33 Frames
#define MC_DIAGPASSL 47	// 33 Frames
#define MC_DIAGBACKR 48	// 33 Frames
#define MC_DIAGBACKL 49	// 33 Frames
#define MC_SIDEPASSR 50	// 32 Frames
#define MC_SIDEPASSL 51	// 32 Frames
#define MC_BACKHEELR 52	// 32 Frames
#define MC_BACKHEELL 53	// 32 Frames
#define MC_TRAPR 54		// 20 Frames
#define MC_TRAPL 55		// 20 Frames

#define MC_STOSL 56		// 68 Frames
#define MC_STOSR 57		// 68 Frames
#define MC_STOSBL 58		// 95 Frames
#define MC_STOSBR 59		// 95 Frames
#define MC_RIDEL 60		// 28 Frames
#define MC_RIDER 61		// 28 Frames
#define MC_SOCKSR 62		// 68 Frames
#define MC_SOCKSL 63		// 68 Frames

#define MC_TROTB 64		// 27 Frames
#define MC_TROTH 65		// 27 Frames
#define MC_TROTG 66		// 28 Frames
#define MC_TROTC 67		// 28 Frames
#define MC_TROTD 68		// 25 Frames
#define MC_TROTF 69		// 25 Frames

#define MC_TROTA 70		// 32 Frames
#define MC_TROTE 71		// 26 Frames

#define MC_RUN 72			// 26 Frames
#define MC_JOG 73			// 29 Frames
#define MC_BARGE 74		// 27 Frames
#define MC_THROWW	75		// 13 Frames
#define MC_SHAMEW 76		// 33 Frames 
#define MC_LIE	78			// 26 Frames .

 #define MC_STAND 78		// 39 Frames
#define MC_S_HEAD 79		// 51 Frames
#define MC_J_HEAD 80 	// 52 Frames
#define MC_D_HEAD 81 	// 38 Frames
#define MC_U_HEAD 79 	// 38 Frames .
#define MC_DV_HEAD 83	// 36 Frames
#define MC_CHEST 84	 	// 49 Frames
#define MC_S_TACKLE 85	// 98 Frames

#define MC_STEAL 86	 	// 17 Frames
#define MC_OVERHEAD 87 	// 45 Frames
#define MC_THROWL 88 	// 43 Frames
#define MC_THROWS 89 	// 35 Frames
#define MC_FALLR 90 		// 34 Frames
#define MC_FALLS 90		// 44 Frames .
#define MC_CELEB 92	 	// 118 Frames
#define MC_SHAME 93		// 82 Frames
#define MC_GETUP 94 		// 82 Frames
#define MC_GETUPF 95 	// 87 Frames 

#define MC_STANDB 96	 	// 29 Frames
#define MC_BOUNCE 97 	// 43 Frames
#define MC_KICKOUT 98 	// 68 Frames
#define MC_HALFVOLL 99	// 68 Frames
#define MC_THROW 100   	// 59 Frames
#define MC_ROLL 101 		// 81 Frames
#define MC_RUNWITHB 102	// 30 Frames
#define MC_WAVEUP 103  	// 49 Frames
#define MC_PENALTY 104 	// 64 Frames 
#define MC_PLEAD 78		// 128 Frames .
#define MC_CRTOSTB 106	// 55 Frames
#define MC_PICKBALL 107	// 43 Frames

#define MC_PLANE 108		// 45 Frames
#define MC_FINGER 109	// 27 Frames
#define MC_KNEE 110		// 41 Frames
#define MC_DUCK 111		// 62 Frames
#define MC_MILLER 112	// 45 Frames
#define MC_BABY 113		// 40 Frames
#define MC_MOON 114		// 68 Frames
#define MC_PUMP 115		// 30 Frames
#define MC_REEVES 116	// 49 Frames

// Contact points within animations...

#define MCC_AFOOTB (29./69)
#define MCC_AFOOTC (48./259)
#define MCC_ABODYB (54./160)
#define MCC_ABODYC (39./131)
#define MCC_AHEADB (65./138)
#define MCC_AHEADC (65./138)
#define MCC_AJUMPB (44./86)
#define MCC_AJUMPC (62./116)

#define MCC_BFOOTB (52./63)
#define MCC_BFOOTC (86./128)
#define MCC_BBODYB (29./81)
#define MCC_BBODYC (57./130)
#define MCC_BHEADB (48./110)
#define MCC_BHEADC (48./110)
#define MCC_BJUMPB (60./109)

#define MCC_CFOOTB (89./147)
#define MCC_CFOOTC (109./150)
#define MCC_CBODYB (68./121)	
#define MCC_CBODYC (70./145)
#define MCC_CHEADB (89./132)
#define MCC_CJUMPB (82./142)

#define MCC_SHOOT (38./109)
#define MCC_CHIP (40./91)
#define MCC_PASS (48./99)
#define MCC_CROSS (42./110)
#define MCC_VOLLEY (41./91)

#define MCC_TOE (47./107)
#define MCC_DIAGPASS (48./101)
#define MCC_DIAGBACK (57./100)
#define MCC_SIDEPASS (46./96)
#define MCC_BACKHEEL (65./97)
#define MCC_TRAP (40./60)
			 
#define MCC_STOS 10
#define MCC_STOSB 0
#define MCC_RIDE 10
#define MCC_SOCKS 10

#define MCC_TROTB 10
#define MCC_TROTH 10
#define MCC_TROTG 10
#define MCC_TROTC 10
#define MCC_TROTD 10
#define MCC_TROTF 10

#define MCC_TROTA 10
#define MCC_TROTE 10

#define MCC_RUN 10
#define MCC_JOG 10
#define MCC_BARGE 10
#define MCC_THROWW 10
#define MCC_SHAMEW 10
#define MCC_LIE 10

#define MCC_STAND 10
#define MCC_S_HEAD (103./155)
#define MCC_J_HEAD (54./158)
#define MCC_D_HEAD (34./115)
#define MCC_U_HEAD (81./114)
#define MCC_DV_HEAD (36./109)
#define MCC_CHEST (50./149)
#define MCC_S_TACKLE 10

#define MCC_STEAL (28./53)
#define MCC_OVERHEAD (70./136)
#define MCC_THROWL (-86./129)
#define MCC_THROWS (-43./107)
#define MCC_FALLR 10
#define MCC_FALLS 10
#define MCC_CELEB 10
#define MCC_SHAME 10
#define MCC_GETUP 10
#define MCC_GETUPF 10

#define MCC_STANDB 0
#define MCC_BOUNCE 0
#define MCC_KICKOUT (-103./204)
#define MCC_HALFVOLL (-101./203)
#define MCC_THROW (-92./179)
#define MCC_ROLL (-88./245)
#define MCC_RUNWITHB 0
#define MCC_WAVEUP 0
#define MCC_PENALTY 10
#define MCC_PLEAD 10
#define MCC_CRTOSTB 0	
#define MCC_PICKBALL 0

#define MCC_DUCK 10
#define MCC_FINGER 10
#define MCC_KNEE 10	
#define MCC_PLANE 10	
#define MCC_MILLER 10
#define MCC_BABY 10	
#define MCC_MOON 10
#define MCC_PUMP 10
#define MCC_REEVES 10


// Players

#define NPLAYERS 25
#define PLYRPTS 28

extern obj player[NPLAYERS];

extern capfrm *player_p;

extern plyrtwdat *plyrtwtb;
extern capfrm twpts;

extern facelist player_f1;
extern facelist player_f2;
extern facelist player_fr;
extern facelist player_fl;
extern facelist player_fg;
extern facelist player_fw;

extern face playertypes[];


// Simple pitch

extern obj pitch;

extern ptlist pitch_p;
extern facelist pitch_f;


// Lines

#define LINEWIDTH 2.4

extern obj lines,l1,l2,l3,l4,l5,l6;

extern ptlist lines_p;
extern facelist lines_f;
extern ptlist l1_p1;
extern ptlist l1_p2;
extern ptlist l2_p1;
extern ptlist l2_p2;
extern ptlist l3_p1;
extern ptlist l3_p2;
extern ptlist l4_p1;
extern ptlist l4_p2;
extern ptlist l5_p1;
extern ptlist l5_p2;
extern ptlist l6_p1;
extern ptlist l6_p2;

extern facelist l_f1a;
extern facelist l_f1b;
extern facelist l_f1c;
extern facelist l_f2a;
extern facelist l_f2b;
extern facelist l_f3a;
extern facelist l_f3b;
extern facelist l_f3c;
extern facelist l_f4;

extern detlist l1_d;
extern detlist l2_d;
extern detlist l3_d;
extern detlist l4_d;
extern detlist l5_d;
extern detlist l6_d;


extern obj semi1,semi2;

extern ptlist s_circle_p1a;
extern ptlist s_circle_p2a;
extern ptlist s_circle_p1b;
extern ptlist s_circle_p2b;

extern facelist s_circle_f1a;
extern facelist s_circle_f2a;
extern facelist s_circle_fb;
extern facelist s_circle_fc;
extern facelist s_circle_fd;

extern detlist s_circle_d1;
extern detlist s_circle_d2;


extern obj circle;

extern ptlist circle_pa;
extern ptlist circle_pb;

extern facelist circle_fa;
extern facelist circle_fb;
extern facelist circle_fc;
extern facelist circle_fd;

extern detlist circle_d;

extern obj spot1,spot2,spot3;

extern ptlist spot_p;

extern facelist spot_f;


// Ball

extern obj ball;

extern ptlist footy_p;

extern facelist footy_f;

extern ptlist footys_p;

extern facelist footys_f;

extern detlist ball_d;


// Shadows/Highlights

extern obj ballshad;

extern ptlist ballshad_p;

extern facelist ballshad_f;


extern obj plhilight[7][6];

extern ptlist plshad_p;
extern ptlist plhi_p;
extern ptlist plhi_p1;
extern ptlist plhi_p2;
extern ptlist plhi_p3;

extern facelist plshad_f;
extern facelist plhi1_f1;
extern facelist plhi2_f1;
extern facelist plhi3_f1;
extern facelist plhi4_f1;
extern facelist plhi1_f2;
extern facelist plhi2_f2;
extern facelist plhi3_f2;
extern facelist plhi4_f2;
extern facelist plhi1_f3;
extern facelist plhi2_f3;
extern facelist plhi3_f3;
extern facelist plhi4_f3;
extern facelist plhi1_f4;
extern facelist plhi2_f4;
extern facelist plhi3_f4;
extern facelist plhi4_f4;
extern facelist plhi1_f5;
extern facelist plhi2_f5;
extern facelist plhi3_f5;
extern facelist plhi4_f5;
extern facelist plhi1_ff;
extern facelist plhi2_ff;
extern facelist plhi3_ff;
extern facelist plhi4_ff;


// Goals

extern obj goal1_1,goal1_2,goal2_1,goal2_2,goal3_1,goal3_2,goal4_1,goal4_2;

extern ptlist goal1a_p;
extern ptlist goal2a_p;
extern ptlist goal1ax_p;
extern ptlist goal2ax_p;
extern ptlist goal3a_p;

extern facelist goal_f1a;
extern facelist goal_f2a;
extern facelist goal_f1b;

extern ptlist goal1b_p;
extern ptlist goal2b_p;
extern ptlist goal3b_p;
extern ptlist goal1bx_p;
extern ptlist goal2bx_p;
extern ptlist goal3bx_p;

extern facelist goal_f1c;
extern facelist goal_f2c;

extern ptlist goal1c_p;
extern ptlist goal2c_p;
extern ptlist goal3c_p;
extern ptlist goal1cx_p;
extern ptlist goal2cx_p;
extern ptlist goal3cx_p;

extern facelist goal_f1d;
extern facelist goal_f2d;

extern detlist goal1_a,goal2_a,goal3_a,goal4_a;
extern detlist goal1_b,goal2_b,goal3_b,goal4_b;


// Flags
extern obj flag_1,flag_2,flag_3,flag_4;

extern ptlist flag_p;

extern facelist flag_f;

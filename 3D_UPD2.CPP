// 3D pitch test				30/9/94

extern "C" int icth,isth;

#include <conio.h>
#include <i86.h>
#include <stdlib.h>
#include <bios.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "defines.h"
#include "externs.h"
#include "mouse.h"
#include "3deng.h"
#include "data.h"
#include "front.h"
#include "eurofrnt\euro_int.h"
#include "audio.h"

int norm_font_col=157;

extern team_info game_data[];
extern setup_info setup;

extern "C" volatile int ux1,ux2,wptr,rptr;

extern int vidi_anim;
extern word scrmode;

extern int draw_string(buff_info *buff,int font_no,int x,int y,char *string,unsigned char col,short just);
extern "C" short wConsoleNode;

extern float log_factor;

int counter=0;

struct joy_struct {
	unsigned short x1;
	unsigned short y1;
	unsigned short x2;
	unsigned short y2;
	unsigned short sw;
};

extern joy_struct joy_pos;

float wayne_cam[2];

float set_camera_dist=260;
float set_camera_height=100;
char camera_fixed=0;

extern void init_off_int(match_player *player);

////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////

extern void get_face_xy(int d,float &x,float &y);

////////////////////////////////////////////////////////////
//// SCREEN PRIMITIVES
//

void
grmode(int md)
	{
	union REGS r;
	r.h.al=md;
	r.h.ah=0;
	int386(0x10,&r,&r);
	}
void
vbl()
{
	while(((inp(0x3da))&8)!=0);
	while(((inp(0x3da))&8)==0);
}

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

	extern stad_info stadlist[];

	float st_hm=360;

	plyrdat *poswr,pos[ncb];
	plyrdat *rep;

	filter filters[32];

	float spr_coord_tab[MAX_3D_SPRS*3+1];
	short spr_ref_tab[MAX_3D_SPRS];

	float null_tab[1]={0};
	short null2[1]={0};

	plyrdat coords_tab1[ncb];
	plyrdat coords_tab2[ncb];

	plyrdat *replay_tab;

	plyrdat *new_coords=coords_tab1;
	plyrdat *old_coords=coords_tab2;

	datapt tx,ty,tz,camera_x,camera_y,camera_z;
	int play_cam=1;

	datapt old_tx=pitch_len/2;
	datapt old_ty=pitch_wid/2;
	datapt old_tz=0;
	datapt old_camx=0;
	datapt old_camy=0;
	datapt old_camz=0;
	datapt cxs=0;
	datapt cys=0;
	datapt czs=0;
	datapt txs=0;
	datapt tys=0;
	datapt tzs=0;
	datapt prev_camx=0;
	datapt prev_camy=0;
	datapt prev_camz=0;

	float old_scale=INIT_SCALE;
	float css=0;

	float scale=INIT_SCALE;

	char prev_camera;
	short mode_change=0;

	const float camera_inertia=0.05;
	const float target_inertia=0.125;
	extern setup_info setup;
	extern match_data match_info;

	extern buff_info main_buff;
	extern buff_info vidi_buff;

	extern void options(buff_info *buffer,datapt viewx,datapt viewy,datapt viewz,datapt targx,datapt targy,
              datapt targz,datapt vdist,plyrdat *plyrtb,datapt *xyz_ptr,word *ref_ptr,int,int);

	extern void substitution(buff_info *buffer,datapt viewx,datapt viewy,datapt viewz,datapt targx,datapt targy,
              datapt targz,datapt vdist,plyrdat *plyrtb,datapt *xyz_ptr,word *ref_ptr,int);

	extern void switch_coords();

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

int init_3d()
{
//	grmode(19);
//	grmode(0x61);

	prev_camera=camera;
	mode_change=0;
	camera_dist=280;

// Make sure vectors are corrected...
	new_update_coords();				// Initialize old tab...
	new_update_coords();				// Initialize old tab...
	return(init3d());
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

////////////////////////////////////////////
// FUNCTIONS CALLED FROM IN-GAME MENUS... //
////////////////////////////////////////////

/******************************************************************************
*****************************************************************************/

void setup_replay()
{
	rep_camera=camera;
	if (camera==15)
		camera=old_cam;
}

/******************************************************************************
*****************************************************************************/

void reset_replay()
{
	camera=rep_camera;
}

/******************************************************************************
*****************************************************************************/

void sub_player(short t,short p,short s)
{
	p+=11*(t^(match_half&1));
	player_being_subbed=p+1;
	player_on_off=p+1;
	player_coming_on=s+1;
	init_off_int(&teams[p]);

	if (p>10)
		PlaySubstitutionMessage(team_b,p-11,s,FALSE);
	else
		PlaySubstitutionMessage(team_a,p,s,FALSE);
}

/******************************************************************************
*****************************************************************************/

void do_replay_render3d(float s)
{
	s+=(float)replay_pos/REAL_SPEED;
	if (s>=replay_seconds)
		s-=replay_seconds;

	int is1=(int)(s*REAL_SPEED);
	plyrdat *rep1=&replay_tab[is1*ncb];  // Replay Frame...

	int is2=(int)(s*REAL_SPEED)+1;
	if (is2>=replay_seconds*REAL_SPEED)
		is2-=replay_seconds*REAL_SPEED;

	plyrdat *rep2=&replay_tab[is2*ncb];  // Replay Frame...

	memcpy(old_coords,rep1,sizeof(plyrdat)*ncb);

	memcpy(new_coords,rep2,sizeof(plyrdat)*ncb);

	mf_scale=s*REAL_SPEED-is1;
	realtime_coords();

	replay_cnt=TRUE;
	update_3d();
	replay_cnt=FALSE;
}

/******************************************************************************
*****************************************************************************/

void process_replay()
{
	if (++replay_pos>=replay_seconds*REAL_SPEED)
		replay_pos=0;
}

/******************************************************************************
*****************************************************************************/

void plr_comments()
{
	plyrdat *ptr=pos;

	for (int i=0; i<players; i++)
	{
		if (teams[i].guy_on)
		{
			if (teams[i].tm_comm>0)
			{
				init_speech(i+1,teams[i].tm_comm,4);
			}
		}
	}
}

/******************************************************************************
*****************************************************************************/

void process_pitch_sprs()
{
	plr_comments();
}

/******************************************************************************
*****************************************************************************/

void init_replay()
{
// Fill all replay buffer with current coords etc...

	allow_replay=TRUE;
	plyrdat *dest=replay_tab;
	plyrdat *src=pos;
	short reps,n;

	for (reps=0; reps<replay_seconds*20; reps++)
	{
		for (short i=0; i<ncb; i++)
		{
			memcpy(dest++,src++,sizeof(plyrdat));
		}
		src-=ncb;
	}
}

/******************************************************************************
*****************************************************************************/

void draw_string_center(int x,int y,char *st,buff_info *buff)
{
	if (scrmode==0x13)
// Low res...
		draw_string(buff,1,x,y,st,norm_font_col,2);
	else
// Higher res...
		draw_string(buff,2,x,y,st,norm_font_col,2);
}

/******************************************************************************
*****************************************************************************/

void draw_string_left(int x,int y,char *st,buff_info *buff)
{
	if (scrmode==0x13)
// Low res...
		draw_string(buff,1,x,y,st,norm_font_col,0);
	else
// Higher res...
		draw_string(buff,2,x,y,st,norm_font_col,0);
}

/******************************************************************************
*****************************************************************************/

void draw_string_right(int x,int y,char *st,buff_info *buff)
{
	if (scrmode==0x13)
// Low res...
		draw_string(buff,1,x,y,st,norm_font_col,1);
	else
// Higher res...
		draw_string(buff,2,x,y,st,norm_font_col,1);
}

/******************************************************************************
*****************************************************************************/

void set_normal_color(int c)
{
	norm_font_col=c;
}

/******************************************************************************
*****************************************************************************/

void extra_info()
{
	char info_str_a[16];
	char info_str_b[16];

	for (short p=0; p<11; p++)
	{
		switch(xinfo)
		{
			case(1):
				sprintf(info_str_a,"SPD. %d. %d",(p+1),teams[p].tm_rate);
				sprintf(info_str_b,"SPD. %d. %d",(p+11),teams[p+11].tm_rate);
				break;
				
			case(2):
				sprintf(info_str_a,"POW. %d. %d",(p+1),teams[p].tm_pow);
				sprintf(info_str_b,"POW. %d. %d",(p+11),teams[p+11].tm_pow);
				break;

			case(3):
				sprintf(info_str_a,"CON. %d. %d",(p+1),teams[p].tm_cont);
				sprintf(info_str_b,"CON. %d. %d",(p+11),teams[p+11].tm_cont);
				break;

			case(4):
				sprintf(info_str_a,"FLR. %d. %d",(p+1),teams[p].tm_flair);
				sprintf(info_str_b,"FLR. %d. %d",(p+11),teams[p+11].tm_flair);
				break;

			case(5):
				sprintf(info_str_a,"VIS. %d. %d",(p+1),teams[p].tm_vis);
				sprintf(info_str_b,"VIS. %d. %d",(p+11),teams[p+11].tm_vis);
				break;

			case(6):
				sprintf(info_str_a,"ACC. %d. %d",(p+1),teams[p].tm_ac);
				sprintf(info_str_b,"ACC. %d. %d",(p+11),teams[p+11].tm_ac);
				break;

			case(7):
				sprintf(info_str_a,"STM. %d. %d",(p+1),teams[p].tm_stam);
				sprintf(info_str_b,"STM. %d. %d",(p+11),teams[p+11].tm_stam);
				break;

			case(8):
				sprintf(info_str_a,"DIS. %d. %d",(p+1),teams[p].tm_disc);
				sprintf(info_str_b,"DIS. %d. %d",(p+11),teams[p+11].tm_disc);
				break;

			case(9):
				sprintf(info_str_a,"PER. %d. %d",(p+1),performance[p]);
				sprintf(info_str_b,"PER. %d. %d",(p+11),performance[p+11]);
				break;
		}
		draw_string_left(64,32+(p*10),info_str_a,&main_buff);
		draw_string_left(192,32+(p*10),info_str_b,&main_buff);
	}
}
	
/******************************************************************************
*****************************************************************************/

extern "C" short state_checksum;
extern int logic_cnt;

void info_line()
{
	set_normal_color(WHITE);

	char info_str1[14];
	char info_str2[14];
	char info_str3[14];
	char info_str4[10];
	char info_str5[10];

	if (setp_taker)
	{
		sprintf(info_str3,"%d    ",teams[setp_taker-1].tm_ac);
		draw_string_center(50,60,info_str3,&main_buff);
		sprintf(info_str3,"%d    ",teams[setp_taker-1].tm_flair);
		draw_string_center(50,80,info_str3,&main_buff);
	}

	sprintf(info_str3,"1. %d    ",users[0].plr);
	draw_string_center(150,60,info_str3,&main_buff);
	sprintf(info_str3,"2. %d    ",users[1].plr);
	draw_string_center(150,80,info_str3,&main_buff);

	sprintf(info_str3,"3. %d    ",users[2].plr);
	draw_string_center(50,100,info_str3,&main_buff);
	sprintf(info_str3,"4. %d    ",users[3].plr);
	draw_string_center(50,120,info_str3,&main_buff);

	sprintf(info_str3,"%d    ",deb_is);
	draw_string_center(150,100,info_str3,&main_buff);
/*
	sprintf(info_str3,"%d    ",users[1].control);
	draw_string_center(150,120,info_str3,&main_buff);

	sprintf(info_str3,"%d    ",wConsoleNode);
	draw_string_center(100,140,info_str3,&main_buff);

	sprintf(info_str3,"%d    ",deb_a);
	draw_string_center(100,160,info_str3,&main_buff);

	sprintf(info_str3,"%1.3f    ",mf_scale);
	draw_string_center(100,180,info_str3,&main_buff);
*/
	sprintf(info_str3,"%d    ",good_poss);

	sprintf(info_str2,"%d : %d  ",frms_per_sec,game_speed);
//	sprintf(info_str2,"%d : %1.2f  ",frms_per_sec,poss_held);

#ifdef CROWD
 	switch(crowd_mood_a)
	{
		case(1):
			sprintf(info_str4,"NORMAL   ");
			break;

		case(2):
			sprintf(info_str4,"PENSIVE  ");
			break;

		case(3):
			sprintf(info_str4,"ENCOURAGE");
			break;

		case(4):
			sprintf(info_str4,"EXCITED  ");
			break;

		case(5):
			sprintf(info_str4,"CELEBRATE");
			break;

		case(6):
			sprintf(info_str4,"BOO...   ");
			break;

		case(7):
			sprintf(info_str4,"SAVE     ");
			break;

		case(8):
			sprintf(info_str4,"MISS     ");
			break;

		case(9):
			sprintf(info_str4,"LAUGH    ");
			break;
	}

	switch(crowd_mood_b)
	{
		case(1):
			sprintf(info_str5,"NORMAL   ");
			break;

		case(2):
			sprintf(info_str5,"PENSIVE  ");
			break;

		case(3):
			sprintf(info_str5,"ENCOURAGE");
			break;

		case(4):
			sprintf(info_str5,"EXCITED  ");
			break;

		case(5):
			sprintf(info_str5,"CELEBRATE");
			break;

		case(6):
			sprintf(info_str5,"BOO...   ");
			break;

		case(7):
			sprintf(info_str5,"SAVE     ");
			break;

		case(8):
			sprintf(info_str5,"MISS     ");
			break;

		case(9):
			sprintf(info_str5,"LAUGH    ");
			break;
	}
#endif

	if (replay_cnt)
		sprintf(info_str1,"REPLAY");
	else
	{
		if (match_mode)
		{
			switch(match_mode)
			{
				case(CORNER_TL):
				case(CORNER_TR):
				case(CORNER_BL):
				case(CORNER_BR):
					sprintf(info_str1,"CORNER"); 
					break;

				case(CENTRE_A):
				case(CENTRE_B):
					sprintf(info_str1,"CENTRE"); 
					break;

				case(GOAL_KICK_TL):
				case(GOAL_KICK_TR):
				case(GOAL_KICK_BL):
				case(GOAL_KICK_BR):
					sprintf(info_str1,"GOAL KICK"); 
					break;

				case(THROW_IN_A):
				case(THROW_IN_B):
					sprintf(info_str1,"THROW IN");
					break;

				case(IF_KICK_A):
				case(IF_KICK_B):
					if (offside_now)
						sprintf(info_str1,"OFFSIDE FK"); 
					else
						sprintf(info_str1,"INDIRECT FK"); 
					break;

				case(DF_KICK_A):
				case(DF_KICK_B):
					sprintf(info_str1,"DIRECT FK"); 
					break;

				default:
					sprintf(info_str1,"STOPPED"); 
					
			};
// Event...
			draw_string_center(50,4,info_str1,&main_buff);
		}
	}

	draw_string_center(270,4,info_str3,&main_buff);
	draw_string_center(160,4,":",&main_buff);
	draw_string_center(270,4,info_str3,&main_buff);

// Score...
	sprintf(info_str1,"%d - %d",team_a_goals,team_b_goals);
	draw_string_center(160,185,info_str1,&main_buff);

// Seconds...
	sprintf(info_str1,"%2.2d",(unsigned short)match_time.sec);
	draw_string_center(164,4,info_str1,&main_buff);

// Minutes...
	sprintf(info_str1,"%3d",match_time.min);
	draw_string_center(126,4,info_str1,&main_buff);
}

/******************************************************************************
*****************************************************************************/

// Switch off camera damping...

void damping_off()
{
		old_camx=camera_x;
		old_camy=camera_y;
		old_camz=camera_z;
}

/******************************************************************************
*****************************************************************************/

void add_message(char *t,short c,char force)
{
	if (force)
	{
// Instant display over-riding current message...
		message_buffer[current_mess].ptr=t;
		message_buffer[current_mess].col=c;
			new_text=MESSAGE_TIME;
		if (!message_cnt)
			message_cnt++;
	}
	else
	{
		if (message_cnt<MAX_MESSAGES)
		{
// Can provide message service...
			short m=message_cnt+current_mess;
			if (m>=MAX_MESSAGES)
				m-=MAX_MESSAGES;
			short lm=m-1;
			if (lm<0)
				lm=MAX_MESSAGES-1;
			if (!message_cnt || strcmp(t,message_buffer[lm].ptr))
			{
// New message...
				message_buffer[m].ptr=t;
				message_buffer[m].col=c;
				if (!message_cnt++)
					new_text=MESSAGE_TIME;
			}
		}
	}
}

/******************************************************************************
*****************************************************************************/

void display_messages()
{
	if (new_text)
	{
		set_normal_color(message_buffer[current_mess].col);
		draw_string_center(main_buff.clip_wid>>1,main_buff.clip_hgt/16,
								 message_buffer[current_mess].ptr,&main_buff);
	}
}

/******************************************************************************
*****************************************************************************/

void change_cam(short c)
{
	set_camera_dist=260;
	set_camera_height=100;
	camera=c;
	char *t;

	if (!camera)
		t="FAR";

	if (camera==1)
		t="PLAN";

	if (camera==2)
		t="G.LINE";

	if (camera==3)
		t="MANUAL";

	if (camera==4)
		t="PLAYER";

	if (camera==5)
		t="USER";

	if (camera==6)
		t="FOLLOW";

	if (camera==7)
		t="REF.";

	if (camera==8)
		t="WIRE";

	if (camera==14)
		t="ISO.";

	if ((camera<14 && camera>8) || (camera>14))
		t=" ";

	add_message(t,YELLOW,TRUE);
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

void update_3d()
{
	float targ_x,targ_y,targ_z;
	char use_fixed;
	scale=INIT_SCALE;
	char cam_limit=TRUE;
	char cam_buffer=TRUE;
	plyrdat *ptr=pos;			// Tweened object x,y,z and orientations...

	float x,y;

	if (!line_up)
	{
// Not in pre-match line-up (can use all available camera options)...
		
		if (!replay_cnt)
		{
// No celebration view during replay...

			if ((just_scored && just_scored<(SCORE_WAIT-30)) && (camera!=15))
			{
// Camera is forced to follow scorer!
				old_cam=camera;
#ifdef WAYNE
				camera=20;
				if (keys[0x11])	// w
				{
					wayne_cam[0]=set_camera_dist;
					wayne_cam[1]=set_camera_height;
					FILE *fp1=fopen("wayne","wb");
					fwrite(wayne_cam,sizeof(float),2,fp1);
					fclose(fp1);
					do_penalty_anim(0);
					do_penalty_menu(0);
				}

				if (keys[0x2c])	// z
				{
					FILE *fp1=fopen("wayne","rb");
					fread(wayne_cam,sizeof(float),2,fp1);
					fclose(fp1);
					set_camera_dist=wayne_cam[0];
					set_camera_height=wayne_cam[1];
				}
					
#else
				camera=15;			// Follow scorer.
#endif
			}
			else
			{
				if (!just_scored && camera==15)
					camera=old_cam;
			}
		}

		if (!EUROmatch_info.timeit)
		{

#ifdef SUPPORT_LP
			if (users_dir[lp_user-1].f&32 || users_dir[lp_user-1].f&16)
			{
				if ((keys[0x4b] || (users_dir[lp_user-1].f&4
					  && users_dir[lp_user-1].f&32)) && (set_camera_dist>10))			// keypad 4
					set_camera_dist-=4;

				if ((keys[0x4d] || (users_dir[lp_user-1].f&8
					  && users_dir[lp_user-1].f&32)) && (set_camera_dist<600))		// keypad 6
					set_camera_dist+=4;

				if ((keys[0x48] || (users_dir[lp_user-1].f&8
					  && users_dir[lp_user-1].f&16)) && (set_camera_height<600))		// keypad 8
					set_camera_height+=4;

				if ((keys[0x50] || (users_dir[lp_user-1].f&4
					  && users_dir[lp_user-1].f&16)) && (set_camera_height>10))		// keypad 2
					set_camera_height-=4;
			}
#endif

			if ((keys[0x4b]) && (set_camera_dist>10))			// keypad 4
				set_camera_dist-=4;
			if ((keys[0x4d]) && (set_camera_dist<600))		// keypad 6
				set_camera_dist+=4;

			if ((keys[0x48]) && (set_camera_height<600))		// keypad 8
				set_camera_height+=4;

			if ((keys[0x50]) && (set_camera_height>10))		// keypad 2
				set_camera_height-=4;

			if (keys[0x4c])											// keypad 5
			{
				set_camera_dist=260;
				set_camera_height=100;
			}

			if (replay_cnt || (!just_scored && match_mode!=SWAP_ENDS))
			{
// Don't allow user to change camera during celebration!

				if (keys[0x02])		// 1			// Autocam
					change_cam(0);		// camera=0

				if (keys[0x03])		// 2			// Plan
					change_cam(1);		// camera=1

				if (keys[0x04])		// 3			// 1/2 Plan
					change_cam(2);		// camera=2

				if (keys[0x05])		// 4
					change_cam(3);		// camera=3

				if (keys[0x06])		// 5			// Player
					change_cam(4);		// camera=4

				if (keys[0x07])		// 6			// Wire
					change_cam(8);		// camera=8

				if (keys[0x08])		// 7			// Referee
					change_cam(7);		// camera=7

				if (keys[0x09])		// 8			// Isometric
					change_cam(14);		// camera=14
			}

			if (debug)
			{
// don't use these views for normal game.

				if (keys[0x0a])		// 9
					change_cam(5);		// camera=5

				if (keys[0x0b])		// 0
					change_cam(6);		// camera=6
			}

			if (camera==4)
			{
				if ((keys[0x48]) && (play_cam<players))	//keypad 8
					play_cam+=1;

				if ((keys[0x50]) && (play_cam>1))			//keypad 2
					play_cam-=1;
			}

// If in network game and a fixed player has been chosen,
// then all camera views should treat the fixed player (not the ball)
// as the target...

			if (network_on && fixed_net_user)
			{
// Fixed player target...
				targ_x=teams[users[fixed_net_user-1].plr-1].tm_x;
				targ_y=teams[users[fixed_net_user-1].plr-1].tm_y;
				targ_z=teams[users[fixed_net_user-1].plr-1].tm_z;
				use_fixed=TRUE;
			}
			else
			{
				if (use_ball_limit)
				{
					targ_x=ballx_out;
					targ_y=bally_out;
					targ_z=ballz_out;
				}
				else
				{
					targ_x=eff_ballx;
					targ_y=eff_bally;
					targ_z=eff_ballz;
				}

				use_fixed=FALSE;
			}
		}

/***************************************/
//  FACE CELEBRATION
/***************************************/

		if (camera==15)
		{
			cam_buffer=TRUE;
			tx=teams[goal_scorer-1].tm_x;
			ty=teams[goal_scorer-1].tm_y;
			tz=24;
			camera_x=tx+teams[goal_scorer-1].tm_xdis*set_camera_dist/1.5;
			camera_y=ty+teams[goal_scorer-1].tm_ydis*set_camera_dist/1.5;
			camera_z=set_camera_height/1.5;
		}

/***************************************/
//  TUNNEL VEIW
/***************************************/

		if (camera==16)
		{
			cam_buffer=TRUE;
			tx=stadlist[setup.stadium].tunlx;
			ty=-stadlist[setup.stadium].tunlz;
			tz=stadlist[setup.stadium].tunly;

			camera_x=cntspot_x;
			camera_y=cntspot_y;
			camera_z=40;
		}

/***************************************/
// PLAYER ON/OFF VEIW
/***************************************/

		if (camera==17)
		{
			short p=player_on_off;

			if (player_on_off<0)
				p=-p;

			p-=1;

			cam_buffer=TRUE;
			if (-stadlist[setup.stadium].tunlz>cntspot_y)
				camera_y=teams[p].tm_y-(40+(teams[p].tm_y/2));
			else
				camera_y=teams[p].tm_y+(40+((pitch_wid-teams[p].tm_y)/2));

			camera_x=teams[p].tm_x;
			camera_z=80;

			tx=teams[p].tm_x;
			ty=teams[p].tm_y;
			tz=10;
		}

/***************************************/
//  MAN OF THE MATCH VEIW
/***************************************/

		if (camera==18)
		{
			cam_buffer=TRUE;
			tx=teams[man_of_match-1].tm_x;
			ty=teams[man_of_match-1].tm_y;
			tz=20;

			camera_x=tx+(teams[man_of_match-1].tm_xdis*set_camera_dist);
			camera_y=ty+(teams[man_of_match-1].tm_ydis*set_camera_dist);
			camera_z=set_camera_height/2;
		}


/***************************************/
//  GOAL-SCORER
/***************************************/

		if (camera==20)
		{
			cam_buffer=TRUE;
			cam_limit=FALSE;
			float x,y,z,d;

			if (last_goal==1)
			{
// B vidi...
				x=stadlist[setup.stadium].vid2x;
				y=-stadlist[setup.stadium].vid2z;
				z=stadlist[setup.stadium].vid2y;
			}
			else
			{
// A vidi...
				x=stadlist[setup.stadium].vid1x;
				y=-stadlist[setup.stadium].vid1z;
				z=stadlist[setup.stadium].vid1y;
			}

			tx=x+(teams[goal_scorer-1].tm_x-x)*just_scored/(SCORE_WAIT-30);
			ty=y+(teams[goal_scorer-1].tm_y-y)*just_scored/(SCORE_WAIT-30);
			tz=z+(teams[goal_scorer-1].tm_z-z)*just_scored/(SCORE_WAIT-30);

			x-=teams[goal_scorer-1].tm_x;
			y-=teams[goal_scorer-1].tm_y;
			z-=teams[goal_scorer-1].tm_z;

			d=calc_dist(x,y);

			x=(x*set_camera_dist*0.5/d);
			y=(y*set_camera_dist*0.5/d);
			z=15;

			camera_x=teams[goal_scorer-1].tm_x-x;
			camera_y=teams[goal_scorer-1].tm_y-y;
			camera_z=z;
		}

/***************************************/
//  AUTO-CAMERA
/***************************************/

		if (camera==0)
		{
			datapt over=((targ_x>cntspot_x) ? (targ_x-cntspot_x)/2:(cntspot_x-targ_x)/2);
			datapt target_x=(int)(targ_x);
			datapt target_y=(int)(pitch_wid/2)+((targ_y-cntspot_y)/2)-(targ_z/4)+60;
			datapt target_z=0; //(int)targ_z;
	
			tx=target_x;
			ty=target_y;
			tz=target_z;
	
			camera_x=(pitch_len/2)+((tx-pitch_len/2)/2);
			camera_y=(pitch_wid+60)+((targ_y-cntspot_y)/1.5)-(over);
			camera_z=180-(targ_y/12)+(over/3);
		}

/***************************************/
// PLAN ( Kick-off view )
/***************************************/

		if (camera==1)
		{
			static float dx=0;
			static float dy=0;
			float x,y,dcx,dcy,move_rate;
	
			cam_buffer=FALSE;		// Switch camera buffering off!
			cam_limit=FALSE;		// Switch camera limit off!
	
			if (game_speed)
				move_rate=(0.2*MF*REAL_SPEED)/game_speed;
			else
				move_rate=0.2;
			
			if (ball_still || use_fixed)
			{
				x=targ_x;
				y=targ_y;
			}
			else
			{
				dx+=((ballxdis*10)-dx)*0.8;
				dy+=((ballydis*10)-dy)*0.8;
	
				x=(eff_ballx+dx);
				y=(eff_bally+dy);
			}
	
			dcx=x-old_tx;
			dcy=y-old_ty;
	
			cxs+=(dcx*camera_inertia-cxs)*move_rate;
			cys+=(dcy*camera_inertia-cys)*move_rate;
	
			x=old_tx+cxs;
			y=old_ty+cys;
	
			int xhf=(set_camera_height/2.45)-prat*3;
			int yhf=(set_camera_height/1.6)-prat*2;
	
			if (x<xhf)
				x=xhf;
			if (x>pitch_len-xhf)
				x=pitch_len-xhf;
			if (y<yhf)
				y=yhf;
			if (y>pitch_wid-yhf)
				y=pitch_wid-yhf;
	
			tx=x;
			ty=y;
			tz=0;
	
			camera_x=x-1;
			camera_y=y;
			camera_z=prat*6+set_camera_height;
		}		

/***************************************/
// 1/2 PLAN ( Sensi style view )
/***************************************/

		if (camera==2)
		{
			static float dx=0;
			static float dy=0;
			float x,y,dcx,dcy,move_rate;
	
			cam_buffer=FALSE;		// Switch camera buffering off!
			cam_limit=FALSE;		// Switch camera limit off!

			if (game_speed)
				move_rate=(0.2*MF*REAL_SPEED)/game_speed;
			else
				move_rate=0.2;
			
			if (ball_still || use_fixed)
			{
				x=targ_x;
				y=targ_y;
			}
			else
			{
				dx+=((ballxdis*10)-dx)*0.4;
				dy+=((ballydis*10)-dy)*0.4;
	
				x=(eff_ballx+dx);
				y=(eff_bally+dy);
			}
	
			dcx=x-old_tx;
			dcy=y-old_ty;
	
			cxs+=(dcx*camera_inertia-cxs)*move_rate;
			cys+=(dcy*camera_inertia-cys)*move_rate;
	
			x=old_tx+cxs;
			y=old_ty+cys;
	
			int xhf=((set_camera_height+8)/2.45)-prat*3;
			int yhf=(calc_dist(set_camera_dist+(targ_x/6),(set_camera_height+8)/2)/1.6)-prat*3;
	
			if (x<xhf)
				x=xhf;
			if (x>pitch_len-xhf)
				x=pitch_len-xhf;
			if (y<yhf)
				y=yhf;
			if (y>pitch_wid-yhf)
				y=pitch_wid-yhf;
	
			tx=x;
			ty=y;
			tz=0;
	
			camera_x=x-set_camera_dist-(targ_x/6);
			camera_y=y;
			camera_z=(set_camera_height+8);
		}		

/***************************************/
// MANUAL
/***************************************/

		if (camera==3)
		{
			ReportMouse();
			camera_x=Mouse.x*2.125-40;
			camera_y=Mouse.y*4.4-40;
			camera_z=set_camera_height;

			tx=targ_x;
			ty=targ_y;
			tz=targ_z;
		}

/***************************************/
// PLAYER
/***************************************/

		if (camera==4)
		{
			cam_buffer=2;
			camera_x=(ptr+(play_cam-1))->x;
			camera_z=(ptr+(play_cam-1))->y+PLAYER_HEIGHT-3;
			camera_y=(ptr+(play_cam-1))->z;
	
			x=-(ptr+(play_cam-1))->crot;
			y=((ptr+(play_cam-1))->srot);
	
			tx=camera_x+x*100;
			ty=camera_y+y*100;
			tz=PLAYER_HEIGHT-3;
		}

/***************************************/
// USER
/***************************************/

		if (camera==5)
		{
			camera_x=(ptr+(ball_poss-1))->x;
			camera_z=(ptr+(ball_poss-1))->y+PLAYER_HEIGHT;
			camera_y=(ptr+(ball_poss-1))->z+2;
	
			x=-(ptr+(ball_poss-1))->crot;
			y=((ptr+(ball_poss-1))->srot);
	
			tx=camera_x+x*100;
			ty=camera_y+y*100;
			tz=PLAYER_HEIGHT;
	
			damping_off();
		}

/***************************************/
// FOLLOW BALL
/***************************************/

		if (camera==6)
		{
			float xd,yd;
	
			if (ball_poss)
			{
				xd=teams[ball_poss-1].tm_xdis;
				yd=teams[ball_poss-1].tm_ydis;
			}
			else
			{
				xd=ballxdis;
				yd=ballydis;
			}
	
			if ((ABS(xd)<.1) && (ABS(yd)<.1))
			{
				tx=old_tx;
				ty=old_ty;
				tz=old_tz;
				camera_x=old_camx;
				camera_y=old_camy;
				camera_z=targ_z+40;
			}
			else
			{
				float d=calc_dist(xd,yd);
				camera_x=targ_x-(120*xd/d);
				camera_y=targ_y-(120*yd/d);
				camera_z=targ_z+40;
	
				tx=targ_x;
				ty=targ_y;
				tz=targ_z;
			}
		}
	

/***************************************/
// REFEREE
/***************************************/

		if (camera==7)
		{
			cam_buffer=2;
			camera_x=(ptr+(players))->x;
			camera_z=(ptr+(players))->y+PLAYER_HEIGHT-3;
			camera_y=(ptr+(players))->z;
	
			x=-(ptr+(players))->crot;
			y=(ptr+(players))->srot;
	
			tx=camera_x+x*100;
			ty=camera_y+y*100;
			tz=PLAYER_HEIGHT-3;
			damping_off();
		}

/***************************************/
// WIRE
/***************************************/

		if (camera==8)
		{

			float bxd,byd,d,ox,oy,nx,ny;

			if ((!match_mode) || (match_mode==CENTRE_A) || (match_mode==CENTRE_B)
				|| (match_mode>=IF_KICK_A && match_mode<=PEN_KICK_B))
			{
// Normal Play...
				camera_dist=set_camera_dist;
	
				if (targ_x>cntspot_x)
// Right goal...
				{
					bxd=pitch_len-targ_x;
					byd=cntspot_y-targ_y;
				}
				else
				{
// Left goal...
					bxd=-targ_x;
					byd=cntspot_y-targ_y;
				}
	
				d=calc_dist(bxd,byd);
				bxd=bxd/d;
				byd=byd/d;
		
				ox=0;
				oy=-1;
	
// get difference (cos a).
				float dif=acos((bxd*ox)+(byd*oy));
				if (targ_x>cntspot_x)
					dif=(((targ_x-cntspot_x)/cntspot_x)*(dif));
				else
					dif=-(((cntspot_x-targ_x)/cntspot_x)*(dif));

// The closer to the goal-line, the more in line with ball to goal!
	
				nx=(ox*cos(dif))-(oy*sin(dif));
				ny=(oy*cos(dif))+(ox*sin(dif));
	
				tx=targ_x+(nx*(set_camera_dist+20)/3);
				ty=targ_y+(ny*(set_camera_dist+20)/3);
				tx=targ_x;
				ty=targ_y;
				tz=targ_z/2;
	
				camera_x=targ_x-(nx*(set_camera_dist+20));
				camera_y=targ_y-(ny*((set_camera_dist+20)
							-((set_camera_dist+20)*(targ_y/(pitch_wid*2)))));
				camera_z=(set_camera_height+20)-(((set_camera_height+20)*.8)*(ABS((targ_y-cntspot_y)/cntspot_y)));
	
				if (targ_y<cntspot_y)
					camera_y=camera_y+((cntspot_y-targ_y)/20);
	
// Now bring target in according to height...

				bxd=camera_x-tx;
				byd=camera_y-ty;
				d=calc_dist(bxd,byd);
				bxd=tx+(bxd*camera_z/(d*5));
				byd=ty+(byd*camera_z/(d*5));
	
				tx=bxd;
				ty=byd;
			}
			else
			{
				switch(match_mode)
				{
	
					case(GOAL_KICK_TL):
					case(GOAL_KICK_BL):
						camera=9;
						break;
	
					case(GOAL_KICK_TR):
					case(GOAL_KICK_BR):
						camera=10;
						break;
	
					case(CORNER_TL):
					case(CORNER_BL):
						camera=11;
						break;
	
					case(CORNER_TR):
					case(CORNER_BR):
						camera=12;
						break;
	
					case(THROW_IN_A):
					case(THROW_IN_B):
						camera=13;
						break;

				}
			}
		}

/***************************************/
/***************************************/

		if (camera==9)
// Goal kick from left...
		{
			camera_y=cntspot_y;
			camera_x=eff_ballx-set_camera_dist;
			camera_z=eff_ballz/2+set_camera_height;
			tx=eff_ballx+((cntspot_x-eff_ballx)/10);
			ty=eff_bally;
			tz=eff_ballz;
			if (match_mode!=GOAL_KICK_TL && match_mode!=GOAL_KICK_BL)
				camera=8;
		}

/***************************************/
/***************************************/

		if (camera==10)
// Goal kick from right...
		{
			camera_y=cntspot_y;
			camera_x=eff_ballx+set_camera_dist;
			camera_z=eff_ballz/2+set_camera_height;
			tx=eff_ballx-((eff_ballx-cntspot_x)/10);
			ty=eff_bally;
			tz=eff_ballz;
			if (match_mode!=GOAL_KICK_TR && match_mode!=GOAL_KICK_BR)
				camera=8;
		}

/***************************************/
/***************************************/

		if (camera==11)
// Corner kick at left goal...
 		{
			float bxd,byd,d;
			tx=prat*12;
			ty=cntspot_y;
			tz=0;
			bxd=eff_ballx-tx;
			byd=eff_bally-ty;
			d=calc_dist(bxd,byd);
			camera_x=eff_ballx+(bxd*set_camera_dist/d);
			camera_y=eff_bally+(byd*set_camera_dist/d);
			camera_z=set_camera_height/4;
			if ((!match_mode) && (last_touch!=corner_taker))
				camera=8;
		}

/***************************************/
/***************************************/

		if (camera==12)
// Corner kick at right goal...
		{
			float bxd,byd,d;
			tx=pitch_len-(prat*12);
			ty=cntspot_y;
			tz=0;
			bxd=eff_ballx-tx;
			byd=eff_bally-ty;
			d=calc_dist(bxd,byd);
			camera_x=eff_ballx+(bxd*set_camera_dist/d)/2;
			camera_y=eff_bally+(byd*set_camera_dist/d)/2;
			camera_z=set_camera_height/4;
			if ((!match_mode) && (last_touch!=corner_taker))
				camera=8;
		}

/***************************************/
/***************************************/

		if (camera==13)
// Throw in...
		{
			tx=eff_ballx;
			ty=eff_bally;
			tz=eff_ballz;
			camera_x=eff_ballx;
			camera_y=eff_bally;
	
			if (bally>cntspot_y)
				camera_y+=set_camera_dist/2;
			else
				camera_y-=set_camera_dist/2;
	
			camera_z=eff_ballz+set_camera_height/4;
	
			if ((!match_mode) && (last_touch!=throw_in_taker))
				camera=8;
		}

/***************************************/
// ISOMETRIC
/***************************************/

		if (camera==14)
		{
			tx=targ_x;
			ty=targ_y+((cntspot_y-targ_y)/4);
			tz=targ_z;
			
			camera_x=tx-20-set_camera_dist*1.4;
			camera_y=ty+20+set_camera_dist*1.4;
			camera_z=targ_z/3+(set_camera_height*2);
	
			scale=512*2;
			cam_limit=TRUE;
		}
	}

	else

	{
// Pre-match Line-up!!!

		if (first_update)
		{
			cam_buffer=FALSE;
			first_update=FALSE;
		}
		else
			cam_buffer=TRUE;

		if (line_up>=40)
		{
// Move camera...
			cam_limit=FALSE;

			float rad=((LINE_UP_DELAY+40-line_up)*(LINE_UP_DELAY+40-line_up))/90;
			float ang=(float)(line_up-40)/LINE_UP_DELAY*PI;
			tx=ballx;
			ty=bally;
			tz=ball_diam/2;
			camera_x=tx-(3*rad*sin(ang));
			camera_y=ty+(3*rad*cos(ang))-30;
			camera_z=20+rad;
/*
			y=(float)(line_up-40)/LINE_UP_DELAY;
			camera_z=prat*2+(y*y*y*y*(prat*60));
			camera_x=cntspot_x;
			camera_y=cntspot_y+80+(y*y*(prat*80));
			tx=cntspot_x;
			ty=cntspot_y+(y*y*(prat*30));
			tz=0;
*/
		}
	}		

/***************************************/
/***************************************/

#define PULL_BACK_FACTOR 1.

	if (prev_camera!=camera)
		mode_change=CAM_MODE_BUFFER;

	prev_camera=camera;

	float cur_camx,cur_camy,cur_camz,cur_tx,cur_ty,cur_tz;
	float dif_camx,dif_camy,dif_camz,dif_tx,dif_ty,dif_tz,dif_scale;
	static float move_rate=0.4;

	if (!line_up && camera==8 && camera==6)
	{
		float d=calc_dist(tx-camera_x,ty-camera_y);
		d=calc_dist(tz-camera_z,d);
		x=(camera_x-tx)/d;
		y=(camera_y-ty)/d;
		float z=(camera_z-tz)/d;
		float cam_dist=calc_dist(set_camera_dist,set_camera_height);

		float r=(d/cam_dist)*PULL_BACK_FACTOR;
		camera_x=tx+(r*d*x);
		camera_y=ty+(r*d*y);
		camera_z=tz+(r*d*z);
	}

// Stadium Perimeter as defined by 3d engine...
	int st_l=stadlist[setup.stadium].st_l;
	int st_w=stadlist[setup.stadium].st_w;
	int st_h=stadlist[setup.stadium].st_h;

	if (cam_limit)
	{
// Camera cannot go far off pitch...
		if (camera_x<-st_l/2)
			camera_x=-st_l/2;
		if (camera_x>pitch_len+(st_l/2))
			camera_x=pitch_len+(st_l/2);
		if (camera_y<-st_w/2)
			camera_y=-st_w/2;
		if (camera_y>pitch_wid+(st_w/2))
			camera_y=pitch_wid+(st_w/2);
		if (camera_z>st_hm)
			camera_z=st_hm;
	}

	if (cam_buffer)
	{
// Tween scale...
		dif_scale=scale-old_scale;

// Camera buffering...
		dif_camx=camera_x-old_camx;
		dif_camy=camera_y-old_camy;
		dif_camz=camera_z-old_camz;

		dif_tx=tx-old_tx;
		dif_ty=ty-old_ty;
		dif_tz=tz-old_tz;

		if (!replay_cnt)
		{
// Time Camera movement...
			if (count>old_count+(TIMER_SPEED/2))
// Half a second interval...
			{
				old_count+=(TIMER_SPEED/2);
				if (!updates)
					updates=1;

				if (camera==3)
					move_rate=1./updates;		// Mouse control disregards game speed!
				else
					move_rate=1./updates*game_speed/REAL_SPEED;

				updates=0;
			}
		}
		else
		{
// No need to time...
			move_rate=0.2;
		}

		if (dif_camx>MAX_CAM_DIF)
			dif_camx=MAX_CAM_DIF;

		if (dif_camy>MAX_CAM_DIF)
			dif_camy=MAX_CAM_DIF;

		if (dif_camz>MAX_CAM_DIF)
			dif_camz=MAX_CAM_DIF;

		if (dif_camx<-MAX_CAM_DIF)
			dif_camx=-MAX_CAM_DIF;

		if (dif_camy<-MAX_CAM_DIF)
			dif_camy=-MAX_CAM_DIF;

		if (dif_camz<-MAX_CAM_DIF)
			dif_camz=-MAX_CAM_DIF;

		if (dif_tx>MAX_CAM_DIF)
			dif_tx=MAX_CAM_DIF;

		if (dif_ty>MAX_CAM_DIF)
			dif_ty=MAX_CAM_DIF;

		if (dif_tz>MAX_CAM_DIF)
			dif_tz=MAX_CAM_DIF;

		if (dif_tx<-MAX_CAM_DIF)
			dif_tx=-MAX_CAM_DIF;

		if (dif_ty<-MAX_CAM_DIF)
			dif_ty=-MAX_CAM_DIF;

		if (dif_tz<-MAX_CAM_DIF)
			dif_tz=-MAX_CAM_DIF;

		cur_camx=old_camx+(dif_camx*move_rate);
		cur_camy=old_camy+(dif_camy*move_rate);
		cur_camz=old_camz+(dif_camz*move_rate);

		cur_tx=old_tx+(dif_tx*move_rate*1.5);
		cur_ty=old_ty+(dif_ty*move_rate*1.5);
		cur_tz=old_tz+(dif_tz*move_rate*1.5);
	}
	else
	{
		cur_camx=camera_x;
		cur_camy=camera_y;
		cur_camz=camera_z;
		cur_tx=tx;
		cur_ty=ty;
		cur_tz=tz;
	}

#ifndef DEMO
	if (opt_user && !replay_cnt)
	{
		plyrdat *buff=new_coords;

// In Game options menu(Formation,Subs,Replay)
		old_rep_pos=replay_pos;
		replay_pos++;	// In case of replay point to first frame...

		if (opt_user==100)
		{
// Substitution Menu...
			sub_camera=camera;
			camera=17;
			subbing_now=SUB_DELAY;
			substitution(&main_buff,cur_camx,cur_camz,cur_camy,
							cur_tx,cur_tz,cur_ty,
							scale,pos,&spr_coord_tab[0],&spr_ref_tab[0],opt_team);
			if (!player_being_subbed)
				camera=sub_camera;
			opt_user=FALSE;
		}
		else
		{
			options(&main_buff,cur_camx,cur_camz,cur_camy,
						cur_tx,cur_tz,cur_ty,
						scale,pos,&spr_coord_tab[0],&spr_ref_tab[0],--opt_user,opt_team);
		}

//		if (buff!=new_coords)
//			switch_coords();
		replay_pos=old_rep_pos;
		old_count=count;
		opt_user=0;
		stop_mf_time();
	}
	else
#endif
	{
		if (key_togs[0x0a] && !vidi_anim)				// 9
// Vidi screen on...
		{
			render3d(&vidi_buff,cntspot_x,cur_camz,pitch_wid+80,
					eff_ballx,eff_ballz,eff_bally,
					scale,pos,&spr_coord_tab[0],&spr_ref_tab[0]);
			vidi_buff.dump(0,0);
		}

// Straight to Vram...
//		main_buff.buff_start=(unsigned char *)0xa0000;

// Update display buffer...
  		render3d(&main_buff,cur_camx,cur_camz,cur_camy,
  					cur_tx,cur_tz,cur_ty,
  					scale,pos,&spr_coord_tab[0],&spr_ref_tab[0]);
  	}

// Overlaid sprites...
		if (debug)
		{
			info_line();
			if (xinfo)
				extra_info();
		}

// New Message...
	display_messages();

#ifdef EURO96
// Name of player in possession...
	if (last_touch && match_mode!=THROW_IN_A && match_mode!=THROW_IN_B)
	{
		short c;
		short p=last_touch;
		char name[20];

		if (p<12)
			c=(match_half&1 ? 1:0);
		else
			c=(match_half&1 ? 0:1);

		p=standard_player(p);
		itoa(teams[last_touch-1].shirt,name,10);

		char *n=&game_data[country(c)].players[p-1].name[game_data[country(c)].players[p-1].goal_index];
		strcat(name,". ");
		strcat(name,n);

		if (!c)
		{
			set_normal_color(TEAM1COL);
			draw_string_left(8,1,name,&main_buff);
		}
		else
		{
			set_normal_color(TEAM2COL);
			draw_string_right(main_buff.clip_wid-8,1,name,&main_buff);
		}
	}
#endif

/* Goal Sprite Out...
		if (just_scored>0 && !replay_cnt)
		{
// OUT
			shadow_sprite(160*2+6,100*2+8,0,&main_buff);
			overlay_sprite(160*2,100*2,0,&main_buff);
		}
*/

	main_buff.dump(0,0);

	old_tx=cur_tx;
	old_ty=cur_ty;
	old_tz=cur_tz;
	old_camx=cur_camx;
	old_camy=cur_camy;
	old_camz=cur_camz;
	old_scale=scale;
}

/******************************************************************************
*****************************************************************************/

void pass_coords(plyrdat *ptr)
{
	float x,y;
	plyrdat *rep=&replay_tab[replay_pos*ncb];  // Replay Frame...

	int col;
	if (replay_cnt && replay_seconds)
	{
// Replay On....
// Use Replay Table only...

		memcpy(ptr,rep,sizeof(plyrdat)*ncb);

	}
	else
	{
// Normal Game mode....
// Update Replay table also...

		for (int i=0; i<players+3; i++)
		{
			if (i>=players)
			{
// Officials

				ptr->x=(datapt)(refs[i-(players)].x); //x

				ptr->y=(datapt)(refs[i-(players)].z); //y

				ptr->z=(datapt)(refs[i-(players)].y); //z

				if (i==players)
					ptr->type=3; //referee colour
				else
					ptr->type=4; //linesman colour

				ptr->crot=refs[i-(players)].dir_x;

				ptr->srot=refs[i-(players)].dir_y;

				ptr->anim=refs[i-(players)].anim;			//anim seq.

				ptr->frame=refs[i-(players)].frm;			//anim frm.

				ptr->fstep=refs[i-(players)].fstep;			//anim fstep.

				ptr->htype=0;		// htype
				ptr->hcol=0;		// hcol

				if (speech_tab[i].cnt)
					ptr->sprite=speech_tab[i].say;
				else
					ptr->sprite=-1;

				ptr++;
			}
			else
			{
				ptr->x=(datapt)(teams[i].tm_x); //x

				ptr->y=(datapt)(teams[i].tm_z); //y

				ptr->z=(datapt)(teams[i].tm_y); //z

				if (!teams[i].guy_on)
// Not on field...
					ptr->type=FALSE;
				else
				{
					if (teams[i].draw_me)
					{
						if (match_half&1)
						{
							if (i>=players/2)
								col=1;
							else
								col=2;
							
						}
						else
						{
							if (i>=players/2)
								col=2;
							else
								col=1;
						}
					}
					else
						col=FALSE;		// Don't draw him!

					ptr->type=col; //colour
				}

				ptr->number=teams[i].shirt;

				x=(teams[i].tm_xdis); //x
				y=(teams[i].tm_ydis); //y

				ptr->crot=x;
				ptr->srot=y;

				ptr->anim=teams[i].tm_anim;
				ptr->frame=teams[i].tm_frm;
				ptr->fstep=teams[i].tm_fstep;

				ptr->htype=(float)teams[i].tm_htype;
				ptr->hcol=(float)teams[i].tm_hcol;

				if (speech_tab[i].cnt)
					ptr->sprite=speech_tab[i].say;
				else
					ptr->sprite=-1;

				ptr++;
			}
		}
		ptr->x=ballx;
		ptr->y=ballz;
//		ptr->y=ball_diam/2+ballz-0.5;
		ptr->z=bally;

		ptr->type=0; 			//ball type

		ptr->crot=cos(ball_horz_ang-PI/2);
		ptr->srot=sin(ball_horz_ang-PI/2);

		ptr->anim=0;
		ptr->frame=cos(ball_vert_ang);
		ptr->fstep=sin(ball_vert_ang);

		ptr->sprite=0;

		ptr++;

// Store in replay array...
		if (replay_seconds)
			memcpy(rep,ptr-ncb,sizeof(plyrdat)*ncb);

	}
}

/******************************************************************************
*****************************************************************************/

void switch_coords()
{
	if (new_coords==coords_tab1)
	{
		new_coords=coords_tab2;
		old_coords=coords_tab1;
	}
	else
	{
		new_coords=coords_tab1;
		old_coords=coords_tab2;
	}
}

/******************************************************************************
*****************************************************************************/

void new_update_coords()
{
	switch_coords();
	pass_coords(new_coords);
}

/******************************************************************************
*****************************************************************************/

void realtime_coords()
{
	double n;
	plyrdat *old=old_coords;
	plyrdat *newp=new_coords;
	plyrdat *ptr=pos;
	float ox,oy,nx,ny,dif;
	int col;

	if (tweening)
	{
		for (int i=0; i<players+3; i++)
		{
			if ((teams[i].guy_on) || (i>=players))
			{
				nx=newp->x;
				ox=old->x;
				nx=ox+((nx-ox)*mf_scale);
				ptr->x=nx;

				nx=newp->y;
				ox=old->y;
				nx=ox+((nx-ox)*mf_scale);
				ptr->y=nx;

				nx=newp->z;
				ox=old->z;
				nx=ox+((nx-ox)*mf_scale);
				ptr->z=nx;

				ptr->type=newp->type;		//col
				ptr->number=newp->number;	// shirt no.

				ox=(old->crot);
				oy=(old->srot);

				nx=(newp->crot);
				ny=(newp->srot);

// get difference...
				dif=((nx*ox)+(ny*oy));

				if (dif>1.0)
					dif=1;

				if (dif<-1.0)
					dif=-1;

				dif=acos(dif);

				dif=dif*mf_scale;

// Which way to turn?
				if ((nx*oy)<(ny*ox))
					dif=-dif;
	
				nx=(ox*cos(dif))+(oy*sin(dif));
				ny=(oy*cos(dif))-(ox*sin(dif));

				ptr->crot=-nx;	//xd
				ptr->srot=ny;	//yd

// Animation seq...
				ptr->anim=newp->anim;

// Animation frame...
				if ((i>=players && refs[i-players].newanim)
					 || (teams[i].tm_newanim && i<players))
				{
					nx=modf(newp->frame,&n);
					ptr->frame=nx;		// Initial frame...
					if (i>=players)
						refs[i-players].newanim=FALSE;
					else
						teams[i].tm_newanim=FALSE;
					old->frame=0;
				}
				else
				{
					nx=newp->frame;
					ox=old->frame;
					if (nx<ox)
// Prevent backwards tweening...(looks bad in slow motion!)
						nx+=1;

					nx=ox+((nx-ox)*mf_scale);
					nx=modf(nx,&n);
					ptr->frame=nx;
					if (i==11)
						deb_data=nx;
				}

				ptr->fstep=newp->fstep;

				ptr->htype=newp->htype;
				ptr->hcol=newp->hcol;

				ptr->sprite=newp->sprite;
			}
			else
			{
				ptr->type=0;		//Off!
			}

		ptr++;
		newp++;
		old++;

		}

// Ball...

		nx=newp->x;
		ox=old->x;
		nx=ox+((nx-ox)*mf_scale);
		ptr->x=nx;
		eff_ballx=nx;

		nx=newp->y;
		ox=old->y;
		nx=ox+((nx-ox)*mf_scale);
		ptr->y=nx;
		eff_ballz=nx;

		nx=newp->z;
		ox=old->z;
		nx=ox+((nx-ox)*mf_scale);
		ptr->z=nx;
		eff_bally=nx;

		ptr->type=0;

		ox=(old->crot);
		oy=(old->srot);

		nx=(newp->crot);
		ny=(newp->srot);

// get difference...
		dif=((nx*ox)+(ny*oy));

		if (dif>1.0)
			dif=1;

		if (dif<-1.0)
			dif=-1;

		dif=acos(dif);

		dif=dif*mf_scale;

// Which way to turn?
		if ((nx*oy)<(ny*ox))
			dif=-dif;
	
		nx=(ox*cos(dif))+(oy*sin(dif));
		ny=(oy*cos(dif))-(ox*sin(dif));

		ptr->crot=nx;
		ptr->srot=ny;

		ptr->anim=0;

		ox=(old->frame);
		oy=(old->fstep);

		nx=(newp->frame);
		ny=(newp->fstep);

// get difference...
		dif=((nx*ox)+(ny*oy));

		if (dif>1.0)
			dif=1;

		if (dif<-1.0)
			dif=-1;

		dif=acos(dif);

		dif=dif*mf_scale;

// Which way to turn?
		if ((nx*oy)<(ny*ox))
			dif=-dif;

		nx=(ox*cos(dif))+(oy*sin(dif));
		ny=(oy*cos(dif))-(ox*sin(dif));

		ptr->frame=nx;
		ptr->fstep=ny;
		ptr->sprite=0;

		ptr++;
		newp++;
		old++;

	}
	else
	{
		for (int i=0; i<players+3; i++)
		{
			if ((teams[i].guy_on) || (i>=players))
			{
				ptr->x=newp->x;
				ptr->y=newp->y;
				ptr->z=newp->z;

				ptr->type=newp->type;
				ptr->number=newp->number;	// shirt no.

				ptr->crot=-(newp->crot);
				ptr->srot=newp->srot;

				nx=newp->anim;
//				nx=modf(nx,&n);
				ptr->anim=nx;

				nx=newp->frame;
				nx=modf(nx,&n);
				ptr->frame=nx;

				ptr->fstep=newp->fstep;

				ptr->htype=newp->htype;
				ptr->hcol=newp->hcol;

				ptr->sprite=newp->sprite;

			}
			else
			{
				ptr->type=0;		//Off!
			}

		ptr++;
		newp++;

		}

// Ball...

		ptr->x=newp->x;
		ptr->y=newp->y;
		ptr->z=newp->z;
		ptr->crot=newp->crot;
		ptr->srot=newp->srot;
		ptr->frame=newp->frame;
		ptr->fstep=newp->fstep;
		ptr->sprite=newp->sprite;

		ptr++;
		newp++;
		old++;

	}
}

/******************************************************************************
*****************************************************************************/

void sprite3d(short x,short y,short ref)
{
	unsigned char *scr=main_buff.buff_start;
	scr+=(y*320/2)+x/2;
	if (y<400 && y>=0 && x<640 && x>=0)
	{
		if (!ref)
			*scr=31;
		else
			*scr=2;
	}

/*
// OUT
	switch(ref)
	{
		case(SAY_FOUL):
			speech_bubble(x,y,"FOUL!",&main_buff);
			break;

		case(SAY_PASS):
			speech_bubble(x,y,"To Me!",&main_buff);
			break;

		case(SAY_SHIT):
			speech_bubble(x,y,"Oh Dear!",&main_buff);
			break;

		case(SAY_CROSS):
			speech_bubble(x,y,"On me head!",&main_buff);
			break;

		case(SAY_OFFSIDE):
			speech_bubble(x,y,"OFFSIDE!",&main_buff);
			break;

		case(SAY_ADV):
			speech_bubble(x,y,"Play on...",&main_buff);
			break;

		case(SAY_REF):
			speech_bubble(x,y,"Ref!",&main_buff);
			break;

		case(SAY_PENALTY):
			speech_bubble(x,y,"PENALTY!",&main_buff);
			break;

		case(SAY_TIMEW):
			speech_bubble(x,y,"Time Wasting!",&main_buff);
			break;

		default:
			overlay_sprite(x,y,ref,&main_buff);
	}
*/
}







		

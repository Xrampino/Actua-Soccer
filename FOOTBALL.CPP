/******************************************************************************
******************************************************************************/
//
// Actua Soccer.    1.9.94
//
//	Programmed by Andy Findlay.
//
/******************************************************************************
******************************************************************************/

#include <malloc.h>
#include "global.h"

#include "3deng.h"
#include "mouse.h"
#include "editor.h"
#include "time.h"
#include "front.h"
#include "menu.h"
#include "defines.h"
#include "mallocx.h"
#include "eurofrnt\euro_int.h"

extern "C" net_var_start;
extern "C" net_var_end;

extern void init_foul(int fouler,char direct,char see=FALSE);

extern void set_normal_color(int c);
extern int draw_string(buff_info *buff,int font_no,int x,int y,char *string,unsigned char col,short just);
extern int winrange;
extern int Vbytesperline;

extern void mem_test();
extern void setpal();
extern int VESAmode(int *);
extern void VGAmode(unsigned char);
extern void svgacpy(unsigned char *,short,short, short,short);
extern setup_info setup;
extern buff_info main_buff,vidi_buff;

extern match_data match_info;
extern char return_doskey;

extern team_info game_data[];
extern setup_info setup;
extern match_data match_info;


short time_table[]={5,10,20,40,90};

extern unsigned char *readrawfile(char *filename,unsigned char *address);
extern unsigned char pal[768];

extern plyrdat *replay_tab;

//#define NET_A

#include "audio.h"							// SOS header

#ifdef ECTS
extern void read_config_file();
#endif

extern "C" volatile int ux1,ux2,wptr,rptr;
extern "C" volatile short net_error;

extern "C" volatile char net_half;

/******************************************************************************
******************************************************************************/

#include "defines.h"
#include "glob_var.h"

extern void init_off_int(match_player *player);

extern void opendebugfile();
extern void closedebugfile();
extern void writeplayerdata();
extern void writecontroldata(int i);

extern void do_ref_menu();

extern char anykey;

extern float set_camera_height;
extern float set_camera_dist;

extern void out_mcball_coords();

/******************************************************************************
*****************************************************************************/

void checksum()
{
	short *v=(short *)&var_start;
	short sum=0;
	do
	{
		sum^=*v;
		v++;
	}while(v<(short *)&var_end);

	sprintf(check_str,"%d",sum);
	add_message(check_str,WHITE,TRUE);
}

/******************************************************************************
******************************************************************************/

extern void force_penalty();

int pen_cnt=100;

void make_mtable(int t1,int t2)
{
	float d,min_d,x,y,gx;
	int p;

	for (int j=t2; j<t2+10; j++)
	{
		teams[j-1].tm_mark=FALSE;
	}

	if (t2<12)
// Team A goals...
		gx=0;
	else
// Team B goals...
		gx=pitch_len;

	for (int a=t1; a>t1-10; a--)
	{
// Can't mark guy on ball...
		if ((a!=main_man) && (teams[a-1].guy_on>0))
		{
			x=teams[a-1].tm_x;
			y=teams[a-1].tm_y;
			p=0;

			if (calc_dist(gx-x,cntspot_y-y)<MUST_MARK_DIST)
// Close enough to be a threat!!!
			{
				min_d=5000;
				for (int i=t2; i<t2+10; i++)
				{
					if ((teams[i-1].guy_on>0) && (!teams[i-1].tm_wall)
						&& (!teams[i-1].tm_mark))
					{
						if (i<12)
							d=calc_dist(x-match_tactics1[ball_zone1][i-2][0],
								   		y-match_tactics1[ball_zone1][i-2][1]);
						else
							d=calc_dist((pitch_len-x)-match_tactics2[ball_zone2][i-13][0],
								   		(pitch_wid-y)-match_tactics2[ball_zone2][i-13][1]);
						if (d<min_d)
						{
							min_d=d;
							p=i;
						}
					}
				}
			}

			if (p)
			{
				d=calc_dist(gx-x,cntspot_y-y);

// How tightly they mark depends on discipline...
				x+=(prat*(gx-x)*((192-teams[p-1].tm_disc)/64)/d);
				y+=(prat*(cntspot_y-y)*((192-teams[p-1].tm_disc)/64)/d);

				teams[p-1].tm_mark=a;

				if (p>11)
					p-=11;
				man2man[p-2][0]=(int)x;
				man2man[p-2][1]=(int)y;
			}
		}
	}
}

/******************************************************************************
******************************************************************************/

extern "C" int deb_x;
extern "C" int deb_y;

void player_stamina()
{
	short ir,p;
	if (match_time.min!=old_min)
	{
		old_min=match_time.min;

		for (short i=0; i<22; i++)
		{
			if (!match_info.GameType)
			{
				int rank;
				if ((i<11 && !(match_half&1)) || (i>10 && (match_half&1)))
					rank=game_data[setup.team_a].ranking;
				else
					rank=game_data[setup.team_b].ranking;

				ir=50+(1.4*(COUNTRIES-rank-1));		// 50 - 110
			}
			else
			{
				if ((i<11 && !(match_half&1)) || (i>10 && (match_half&1)))
				{
// Team A...
					if (!(match_half&1))
					{
						p=i;
					}
					else
					{
						p=i-11;
					}
					ir=game_data[setup.team_a].players[p].pace+28;
				}
				else
				{
// Team B...
					if (match_half&1)
					{
						p=i;
					}
					else
					{
						p=i-11;
					}
					ir=game_data[setup.team_b].players[p].pace+28;
				}
			}

			int st=teams[i].tm_stam;
			float f=(sin((PI*teams[i].tm_time/120)-(PI/2))+1)/2;
			float t=f*(129-st)/140*ir;
			teams[i].tm_rate=ir-t;
/*
			if ((i==1 && !(match_half&1)) || (i==12 && (match_half&1)))
				deb_x=teams[i].tm_rate;
			else
				if (i==1 || i==12)
					deb_y=teams[i].tm_rate;
*/
		}
	}
}

/******************************************************************************
******************************************************************************/

// Process Various control flags on each logic cycle...

void process_flags()
{
#ifdef EURO96
	player_stamina();
#endif

// Text message counter...
	if (message_cnt)
		if (!(--new_text))
			if (--message_cnt)
			{
				new_text=MESSAGE_TIME;
				if (++current_mess==MAX_MESSAGES)
					current_mess=0;
			}

// Used for offside rule...
	if (ball_released)
		if (ball_released>0)
			ball_released--;
		else
			ball_released++;

	if (play_advantage)
	{
// Referee has seen an indiscretion but is waiting to see who collects ball...
		if (ball_poss)
		{
// Some-one has collected ball!!!
			if ((ball_poss<12 && bad_guy>11) || (ball_poss>11 && bad_guy<12))
			{
// Favoured team has it!
				play_advantage=FALSE;
			}
			else
			{
// Fouling team has it! (no advantage gained!)
				retake_foul();
			}
		}
	}

	if (just_thrown)
		if (last_touch==throw_in_taker)
			just_thrown--;
		else
			just_thrown=FALSE;

	switch(match_mode)
	{
		case(IF_KICK_B):
		case(DF_KICK_B):
		case(CORNER_TL):
		case(CORNER_BL):
			man2man_a=TRUE;
			man2man_b=FALSE;
			break;

		case(IF_KICK_A):
		case(DF_KICK_A):
		case(CORNER_TR):
		case(CORNER_BR):
			man2man_b=TRUE;
			man2man_a=FALSE;
			break;

		default:
			man2man_a=FALSE;
			man2man_b=FALSE;
			break;
	}

	if (man2man_b)
// Team B marking table...
	{
		make_mtable(11,13);
	}
	else
	{
		if (man2man_a)
// Team A marking table...
		{
			make_mtable(22,2);
		}
	}
}

/******************************************************************************
*****************************************************************************/

void init_line_up()
{
	line_up=LINE_UP_DELAY+40;
}

/******************************************************************************
*****************************************************************************/

short convert_control(char c)
{
	switch(c)
	{
		case(0):
			return(KEY1_CTRL);
			break;

		case(1):
			return(KEY2_CTRL);
			break;

		case(2):
			return(JOY1_CTRL);
			break;

		case(3):
			return(JOY2_CTRL);
			break;

		case(4):
			return(MOUSE_CTRL);
			break;

		case(5):
			return(LOGPAD_CTRL);
			break;

	}
	return(0);
}

/******************************************************************************
*****************************************************************************/

short conv_conts_back(char c)
{
	switch(c)
	{
		case(JOY1_CTRL):
			return(2);
			break;

		case(JOY2_CTRL):
			return(3);
			break;

		case(KEY1_CTRL):
			return(0);
			break;

		case(KEY2_CTRL):
			return(1);
			break;

		case(MOUSE_CTRL):
			return(4);
			break;

		case(LOGPAD_CTRL):
			return(5);
			break;
	}
	return(0);
}

/******************************************************************************
*****************************************************************************/

void init_rand()
{
// Get it from front-end...
	srand(EUROmatch_info.rand);
}

/******************************************************************************
*****************************************************************************/

void get_performance()
{
	short p,max_p1,max_p2,min_p1,min_p2,min_p,sp,spa,spb;

	float clock=45./time_factor;

	for (short i=0; i<22; i++)
	{
		p=0;
		if (teams[i].tm_time>=15)
		{
			if (!i || i==(KP_B-1))
			{
// Keeper performance...
				p+=PER_KPSAVES*clock*teams[i].tm_kpsaves;
				p+=PER_GOALSIN*clock*(i<11 ? team_a_goals:team_b_goals);
			}

			p+=PER_BOOKINGS*clock*teams[i].tm_book;
			p+=PER_FOULS*clock*teams[i].tm_fouls;
			p+=PER_GOALS*clock*teams[i].tm_goals;
			p+=PER_OGS*clock*teams[i].tm_ogs;
			p+=PER_POSS*clock*teams[i].tm_posst;
			p+=PER_WORK*clock*teams[i].tm_work;

			if (teams[i].tm_tacks)
				p+=PER_TACKS*teams[i].tm_twon/(teams[i].tm_tacks+10/clock);

			if (teams[i].tm_shots)
				p+=PER_SHOTS*teams[i].tm_saved/(teams[i].tm_shots+10/clock);

			if (teams[i].tm_pass)
				p+=PER_PASSES*teams[i].tm_pwon/(teams[i].tm_pass+10/clock);
		}
		else
// Not been on field long enough...
			p=-2000;

		performance[i]=p;
	}

	max_p1=-1000;
	max_p2=-1000;
	min_p1=1000;
	min_p2=1000;

	for (i=0; i<22; i++)
	{
		p=performance[i];
		if (i>10)
		{
			if (p>max_p1)
			{
				max_p1=p;
				spa=i+1;
			}

			if (p<min_p1)
				min_p1=p;
		}

		if (i<11)
		{
			if (p>max_p2)
			{
				max_p2=p;
				spb=i+1;
			}

			if (p<min_p2)
				min_p2=p;
		}
	}

	if (max_p1>max_p2)
	{
		sp=max_p1;
		man_of_match=spa;
	}
	else
	{
		sp=max_p2;
		man_of_match=spb;
	}

	if (min_p1<min_p2)
		min_p=min_p1;
	else
		min_p=min_p2;

	sp-=min_p;

// Performance is a percentage of star players...
	 
	for (i=0; i<22; i++)
	{
		p=performance[i];
		performance[i]=100.*(p-min_p)/sp;
	}
}

/******************************************************************************
*****************************************************************************/

// Initialise zero vars...

extern char cross_on;
extern "C" short state_checksum;

void initialise_vars()
{
	int i;

	for (i=0; i<5; i++)
	{
		burst_timer[i]=0;
	}

	for (i=0; i<22; i++)
	{
		sel_circle[i]=0;
	}
#ifdef EURO96
	state_checksum=0;
	state_ptr=&state1;
	checksum_ptr=(short *)state_ptr;
#endif
	escape_pending=0;
	man_of_match=0;
	xinfo=0;
	message_cnt=0;
	current_mess=0;
	new_text=0;
	not_ahead=FALSE;
	kick_off=TRUE;
	forced=0;
	keep_timer=0;
	player_on_off=FALSE;
	player_being_subbed=FALSE;
	sub_pending=FALSE;
	booking=FALSE;

	stop_clock=FALSE;
	card_is_out=0;
	anykey=FALSE;
	demo_match=FALSE;
	rolling_clock=0;

	keep_dive=FALSE;
	hold_up_play=0;
	cross_on=FALSE;
	wall_is_up=FALSE;
	
	comsetp=0;

	init_rand();

// Timing Vars...

	updates=0;
	old_count=0;

	crowd_mood_a=0;
	crowd_mood_b=0;

	possession=0;
	poss_held=0;

	for (i=0; i<11; i++)
	{
		strike[i].t=0;
		strike[i].free=0;
		strike[i].ptype=0;
		strike[i].pplr=0;
		strike[i].gt=0;
		strike[i].x=0;
		strike[i].y=0;
		strike[i].atime=0;
		strike[i].stop=0;
	}

	first_time_it=FALSE;
	auto_select=FALSE;

	seconds=0;

	arrow_on=0;

	logic_cnt=0;

	ball_move=FALSE;

	first_bounce=0;
	swerve=0;
	spin_cnt=0;
	spin_ball=0;
	prediction=FALSE;
	set_xyspin=0;
	set_zspin=0;

	ball_horz_ang=0;
	ball_vert_ang=0;
	max_sw_factor=0;
	swerve_factor=0;
	rebound_ball=0;
	headed_ball=0;
	say_names=TRUE;
	fired_a_shot=0;
	comm_pass=0;
	comm_pass_type=0;

	keeper_spd=0;
	keeper_down=FALSE;
	save_direction=FALSE;
	keeper_will_save=FALSE;
	keeper_on_grnd=FALSE;
	keeper_contact=0;
	ball_in_goal=FALSE;
	ball_in_hands=FALSE;
	game_action=FALSE;
	throw_cnt=0;
	team_a_goals=0;
	team_b_goals=0;
	last_goal=0;
	scorer_running=FALSE;
	just_scored=0;
	just_thrown=0;
	goal_scorer=0;
	pass_type=0;
	kick_type=0;
	receiver=0;
	cross_now=0;
	must_face=FALSE;
	must_face_time=0;
	must_face_x=0;
	must_face_y=0;
	must_shoot=FALSE;
	chip_pass=FALSE;
	must_pass=FALSE;
	must_punt=FALSE;

	keeper_a_in_box=0;
	keeper_b_in_box=0;
	keeper_steps=0;
	save_block=0;
	save_xoff=0;
	save_yoff=0;
	save_zoff=0;
	shot_speed=0;
	scr_x=0;
	scr_y=0;
	ball_speed=0;
	ball_int_speed=0;
	interceptor_a=0;
	interceptor_b=0;
	in_cross_area=0;
	close_in_number=0;
	shooter=0;
	ball_inair=1;
	super_shot=0;
	opponents_near_holder=0;
	opponents_really_close=0;
	int ball_poss=0;
	sender_1_2=0;
	ball_still=0;
	last_touch=0;
	want_pass=0;
	before=0;
	support_me=0;
	pre_kp_touch=0;
	prev_touch=0;

	ball_limbo_p=0;
	ball_limbo_on=FALSE;
	ball_limbo_c=0;

	ball_released=0;
	cannot_pick_up=0;
	last_user_a=0;
	last_user_b=0;
	last_plr_a=0;
	last_plr_b=0;
	players_off_a=0;
	players_off_b=0;

	want_pass_stat=0;
	ball_zone1=0;
	ball_zone2=0;
	ball_out_of_play=0;

	receiver_a=0;
	receiver_b=0;

	ready_centre=0;
	shot_attempt=0;

	force_select=0;
	heading_ball=0;
	flag=0;

	rep_camera=0;
	sub_camera=0;
	allow_replay=0;

	replay_pos=0;
	old_rep_pos=0;
	replay_cnt=0;

	pitch_sprs=0;

	fixed_net_user=0;

	memset(&auto_users_list_a,0,sizeof(auto_users_list_a));
	memset(&auto_users_list_b,0,sizeof(auto_users_list_b));
	auto_users_a=0;
	auto_users_b=0;

	play_ball_a=0;
	play_ball_b=0;

	new_select=0;
	auto_intercept=0;
	closest=0;

	f1_down=0;
	f2_down=0;

	spec_kick_type=0;
	setp_hgt=0;
	setp_power=0;
	setp_kick_x=0;
	setp_kick_y=0;
	setp_bxd=0;
	setp_byd=0;
	setp_bzd=0;
		
	user_taker=0;
	user_controlled=0;
	user_plr=0;
	after_touch_on=FALSE;
	drive_shot=0;

	wallx=0;
	wally=0;
	men_in_wall=0;

	for (i=0; i<5; i++)
	{
		wguys[i].guy=0;
		wguys[i].x=0;
		wguys[i].y=0;
	}

	keeper_pos_x=0;
	keeper_pos_y=0;

	centre_guy_1=0;
	centre_guy_2=0;

	in_range=0;
	in_header_rng=0;
	in_shot_rng=0;
	taker_x=0;
	taker_y=0;

	bad_guy=0;
	direct_fk=FALSE;

	play_advantage=0;

	set_piece_on=0;

	shot_acknowledged=FALSE;
	shot_pending=FALSE;
	real_shot=FALSE;
	shot_missed=0;
	shot_saved=0;

	for (i=0; i<10; i++)
	{
		opp_dir_tab[i][0]=0;
		opp_dir_tab[i][1]=0;
		opp_dir_tab[i][2]=0;
	}

	offside_now=0;

	memset(&tussle_tab,0,sizeof(tussle_tab));

	ball_travel=0;
	select_cnt=10;
	in_game=1;
	analogue=1;

	ballxdis=12.0, ballydis=2.0, ballzdis=10.0;
	ballx=cntspot_x, bally=cntspot_y, ballz=ball_diam/2;
	prev_ballx=0.0*16, prev_bally=30.0*16, prev_ballz=ball_diam/2;
	ns_ballx=0.0, ns_bally=0.0, ns_ballz=ball_diam/2;
	ball_zspin=0;
	ball_xyspin=0;
	full_zspin=0;
	full_xyspin=0;
	shoot_x=0;
	shoot_y=0;

	nearest_a=0,nearest_b=0,old_ltouch=-1,old_ball_poss=-1;
	use_ball_limit=0;
	near_path_a=0;
	near_path_b=0;
	zone1_x=0;
	zone2_x=0;
	zone1_y=0;
	zone2_y=0;
	incident_x=0;
	incident_y=0;
	difficulty=0;
	match_mode=0;
	dead_ball_cnt=0;
	defense_a=0;
	defense_b=0;
	poss_mode=0;

	for (i=0; i<50; i++)
	{
		ball_pred_tab[i][0]=ballx;
		ball_pred_tab[i][1]=bally;
		ball_pred_tab[i][2]=ballz;
		ns_ball_pred_tab[i][0]=ballx;
		ns_ball_pred_tab[i][1]=bally;
		ns_ball_pred_tab[i][2]=ballz;
	}

	delay_cnt=40;
	play_nums_on=0;
	frame=FALSE;
	frames=0;
	frms_per_sec=0;
	last_second=0;

	old_clock=0;

}

/******************************************************************************
*****************************************************************************/

void init_user_controls()
{
#ifdef FRONT_END
	num_of_users=0;
#endif

	short home_plrs=EUROmatch_info.TeamA_users;
	short away_plrs=EUROmatch_info.TeamB_users;

/*
	short home_plrs=game_data[setup.team_a].player_control;
	short away_plrs=game_data[setup.team_b].player_control;
*/

	short plrs=0;
	short c;

	short pnum=0;

	for (short i=1; i<16; i<<=1)
	{
		pnum++;
		if (home_plrs&i)
		{
// User...
			plrs++;
			c=convert_control(EUROmatch_info.CntrlTypes[pnum-1]);
			add_team_user(-1,c);
		}

		if (away_plrs&i)
		{
// User...
			plrs++;
			c=convert_control(EUROmatch_info.CntrlTypes[pnum-1]);
			add_team_user(-2,c);
		}
	}
}

/******************************************************************************
*****************************************************************************/

// Copy buffer to current VESA screen
void svgacpy2(unsigned char *buffpt,short x,short y,short w,short h)
	{
	union REGS regs;
	short i,co;
	char *scrpt;
	int scrdisp=x+Vbytesperline*y;
	char bank=scrdisp/winrange;

	scrdisp%=winrange;
	scrpt=(char *)0xa0000+scrdisp;
	regs.x.eax=0x4f05;
	regs.x.ebx=0;
	regs.x.edx=bank;
	int386(16,&regs,&regs);
	do
		{
		co=MIN((winrange-scrdisp)/Vbytesperline,h);
		for (i=0;i<co;i++)
			{
			memcpy(scrpt,buffpt,640);
			scrpt+=Vbytesperline;
			buffpt+=640;
			h--;
			}
		if (h)
			{
			scrdisp=(scrdisp+(co+1)*Vbytesperline)%winrange;
			co=MIN(Vbytesperline-scrdisp,w);
			memcpy(scrpt,buffpt,co);
 			bank++;	 
 			regs.x.eax=0x4f05;
 			regs.x.ebx=0;
 			regs.x.edx=bank;
  			int386(16,&regs,&regs);
 			if (co!=w) 
				memcpy((char *)0xa0000,buffpt+co,w-co);
			scrpt=(char *)0xa0000+scrdisp;
			buffpt+=640;
			h--;
		 	}
		}while (h);
	regs.x.eax=0x4f05;
	regs.x.ebx=0;
	regs.x.edx=0;
	int386(16,&regs,&regs);
	}

/******************************************************************************
*****************************************************************************/

void display_endscr()
{
	int vesas[]={0x101,-1};
	unsigned char *scr=(unsigned char *)mallocx(640*480);

	readrawfile("rolling.pal",(unsigned char *)pal);		// Laurent's

	VESAmode(vesas);

	readrawfile("rolling.bm",scr);

	svgacpy2(scr,0,0,640,480);

	setpal();

	return_doskey=TRUE;

	getch();

	freex(scr);
}

/******************************************************************************
*****************************************************************************/

void display_screen()
{
	int vesas[]={0x101,-1};
	int svesas[]={0x100,-1};
	unsigned char spal[768];

	memcpy(spal,pal,768);

	readrawfile("andy.pal",(unsigned char *)pal);		// Laurent's

	unsigned short x,y;
	unsigned char sw;

	VESAmode(vesas);

	readrawfile("andy.bm",(unsigned char *)main_buff.buff_start);

	svgacpy2(main_buff.buff_start,0,0,640,480);

	setpal();

	count=1;
	
	do{
		read_joystick(0,&x,&y,&sw);
		if (!--count)
		{
			count=200;
			pal[768-6]--;
			pal[768-5]--;
			pal[768-4]--;
			setpal();
		}
	}while(!sw);

#ifndef ONE_MACHINE
	VGAmode(0x13);
#else
	VESAmode(svesas);
#endif

	memcpy(pal,spal,768);
	setpal();
}

/******************************************************************************
*****************************************************************************/

void load_new_tactics()
{
	FILE *fp1;

	if (tactics_a!=old_tac_a)
	{
// Load Match tactics...
		switch(tactics_a)
		{
			case(F_4_3_3):
				fp1=fopen("tac_433.tac","rb");
				break;
	
			case(F_5_3_2):
				fp1=fopen("tac_532.tac","rb");
				break;

			case(F_6_3_1):
				fp1=fopen("tac_631.tac","rb");
				break;

			case(F_4_2_4):
				fp1=fopen("tac_424.tac","rb");
				break;

			case(F_5_1_4):
				fp1=fopen("tac_514.tac","rb");
				break;

			case(F_4_0_6):
				fp1=fopen("tac_406.tac","rb");
				break;

			case(F_3_1_6):
				fp1=fopen("tac_316.tac","rb");
				break;

			case(F_4_1_5):
				fp1=fopen("tac_415.tac","rb");
				break;

			case(F_5_2_3):
				fp1=fopen("tac_523.tac","rb");
				break;

			case(F_4_4_2):
				fp1=fopen("tac_442.tac","rb");
				break;
		}

	// Team A tactics...
		if (!(match_half&1))
			fread(match_tactics1,sizeof(int),((32*2)+6)*10*2,fp1);
		else
			fread(match_tactics2,sizeof(int),((32*2)+6)*10*2,fp1);

		fclose(fp1);
	}

	if (tactics_b!=old_tac_b)
	{
// Load Match tactics...
		switch(tactics_b)
		{
			case(F_4_3_3):
				fp1=fopen("tac_433.tac","rb");
				break;
	
			case(F_5_3_2):
				fp1=fopen("tac_532.tac","rb");
				break;

			case(F_6_3_1):
				fp1=fopen("tac_631.tac","rb");
				break;

			case(F_4_2_4):
				fp1=fopen("tac_424.tac","rb");
				break;

			case(F_5_1_4):
				fp1=fopen("tac_514.tac","rb");
				break;

			case(F_4_0_6):
				fp1=fopen("tac_406.tac","rb");
				break;

			case(F_3_1_6):
				fp1=fopen("tac_316.tac","rb");
				break;

			case(F_4_1_5):
				fp1=fopen("tac_415.tac","rb");
				break;

			case(F_5_2_3):
				fp1=fopen("tac_523.tac","rb");
				break;

			case(F_4_4_2):
				fp1=fopen("tac_442.tac","rb");
				break;
		}

	// Team B tactics...
		if (!(match_half&1))
			fread(match_tactics2,sizeof(int),((32*2)+6)*10*2,fp1);
		else
			fread(match_tactics1,sizeof(int),((32*2)+6)*10*2,fp1);
		fclose(fp1);
	}
	old_tac_a=tactics_a;
	old_tac_b=tactics_b;
}


/******************************************************************************
*****************************************************************************/

void init_match()
{
	sub_pending=0;

	key_togs[0x0a]=EUROmatch_info.vidi;

// Initialise Penalty Shoot-out...
	penalties=0;
	home_pens_left=5;
	away_pens_left=5;
	penalty_game=FALSE;
	penalty_team=FALSE;
	penalty_counter=0;
	pen_taker_a=11;
	pen_taker_b=22;

	first_update=TRUE;

	reset_ball();

	opt_user=0;
	subbing_now=FALSE;

	if (setup.M8)
		replay_seconds=15;
	else
		replay_seconds=0;

	if (replay_seconds)
	{
		replay_tab=(plyrdat *)mallocx(replay_seconds*ncb*20*sizeof(plyrdat));
		if (replay_tab==NULL)
		{
			printf("Ooops... Can't malloc replay buffer!\n");
			exit(-1);
		}
	}

	auto_intercept=TRUE;
	end_game=FALSE;
	allow_replay=FALSE;
	match_time.min=0;
	match_time.sec=0;
	next_mins=0;

	just_scored=0;
	set_piece_on=0;
	team_a_goals=0;
	team_b_goals=0;

	if (!network_on)
		init_user_controls();

	need_result=(match_info.CompetitionType==2);
	clock_running=FALSE;
	team_a=0;
	team_b=1;
	match_half=0;
	last_centre=0;
	init_line_up();

// Ects show demo (head to head)...
#ifdef ECTS
	read_config_file();
	display_screen();
#endif

/*** Setup Tactics ***/
	tactics_a=EUROmatch_info.tac_1;
	tactics_b=EUROmatch_info.tac_2;
	old_tac_a=-1;		// Force new tactical load!
	old_tac_b=-1;
	load_new_tactics();

	ref_accuracy=EUROmatch_info.referee_vision;
	ref_strictness=EUROmatch_info.referee_discipline;

}

/******************************************************************************
******************************************************************************/

#define COUNTRIES 44

void init_player_stats(short p)
{
	p--;
	short ps;

	if ((!(match_half&1) && p<11)
		  || (match_half&1 && p>10))
	{
// Team A...
		if (!(match_half&1))
		{
			ps=p;
		}
		else
		{
			ps=p-11;
		}

		if (match_info.GameType)
		{
// Simulation Mode!!!
			teams[p].tm_rate=game_data[setup.team_a].players[ps].pace+28;
			teams[p].tm_pow=game_data[setup.team_a].players[ps].power+28;
			teams[p].tm_cont=game_data[setup.team_a].players[ps].control+28;
			teams[p].tm_flair=game_data[setup.team_a].players[ps].flair+28;
			teams[p].tm_vis=game_data[setup.team_a].players[ps].vision+28;
			teams[p].tm_ac=game_data[setup.team_a].players[ps].accuracy+28;
			teams[p].tm_stam=game_data[setup.team_a].players[ps].stamina+28;
			teams[p].tm_disc=game_data[setup.team_a].players[ps].discipline+28;
		}
		else
		{
// Arcade Mode!!!
			int rank=game_data[setup.team_a].ranking;
			short avg=50+(1.4*(COUNTRIES-rank-1));  // 50 - 110

			teams[p].tm_rate=30+(avg/2);
			teams[p].tm_pow=avg;
			teams[p].tm_cont=avg;
			teams[p].tm_flair=avg;
			teams[p].tm_vis=avg;
			teams[p].tm_ac=avg;
			teams[p].tm_stam=avg;
			teams[p].tm_disc=avg;
		}
	}
	else
	{
// Team B...
		if (match_half&1)
		{
			ps=p;
		}
		else
		{
			ps=p-11;
		}

		if (match_info.GameType)
		{
// Simulation Mode!!!
			teams[p].tm_rate=game_data[setup.team_b].players[ps].pace+28;
			teams[p].tm_pow=game_data[setup.team_b].players[ps].power+28;
			teams[p].tm_cont=game_data[setup.team_b].players[ps].control+28;
			teams[p].tm_flair=game_data[setup.team_b].players[ps].flair+28;
			teams[p].tm_vis=game_data[setup.team_b].players[ps].vision+28;
			teams[p].tm_ac=game_data[setup.team_b].players[ps].accuracy+28;
			teams[p].tm_stam=game_data[setup.team_b].players[ps].stamina+28;
			teams[p].tm_disc=game_data[setup.team_b].players[ps].discipline+28;
		}
		else
		{
// Arcade Mode!!!
			int rank=game_data[setup.team_b].ranking;
			short avg=50+(1.4*(COUNTRIES-rank-1));  // 50 - 110

			teams[p].tm_rate=30+(avg/2);
			teams[p].tm_pow=avg;
			teams[p].tm_cont=avg;
			teams[p].tm_flair=avg;
			teams[p].tm_vis=avg;
			teams[p].tm_ac=avg;
			teams[p].tm_stam=avg;
			teams[p].tm_disc=avg;
		}
	}
}

/******************************************************************************
******************************************************************************/

void process_subs()
{
	if (player_being_subbed)
	{
// Player has been selected and should come off!
		if (!teams[player_being_subbed-1].guy_on)
		{
// He's off the park... (Bring on new guy!)
			init_player_stats(player_being_subbed);
			teams[player_being_subbed-1].shirt=player_coming_on;
			teams[player_being_subbed-1].tm_trap=FALSE;
			teams[player_being_subbed-1].int_move=FALSE;
			teams[player_being_subbed-1].int_cnt=FALSE;
			reset_ideas(&teams[player_being_subbed-1]);
			player_being_subbed=FALSE;
			teams[player_on_off-1].guy_on=TRUE;
			player_on_off=-player_on_off;			// Coming on!
			init_off_int(&teams[(-player_on_off)-1]);
		}
	}
	else
	{
		if (!player_on_off && sub_pending && (match_mode>=CORNER_TL && match_mode<=DF_KICK_B)
			 && !kickoff)
		{
			opt_user=100;		// Substitute instead of options...

// Some-one is trying to make a substitution...(Who?)
			if (sub_pending&1)
				opt_team=0;
			else
				opt_team=1;
		}
	}
}

/******************************************************************************
******************************************************************************/

void save_state(save_data *save_it)
{
	memcpy(save_it->teams,teams,sizeof(teams));
	memcpy(&save_it->match_time,&match_time,sizeof(match_time));
	memcpy(save_it->refs,refs,sizeof(refs));
	memcpy(save_it->speech_tab,speech_tab,sizeof(speech_tab));
	memcpy(save_it->wguys,wguys,sizeof(wguys));
	memcpy(save_it->sel_circle,sel_circle,sizeof(sel_circle));
	memcpy(save_it->burst_timer,burst_timer,sizeof(burst_timer));
	memcpy(save_it->auto_users_list_a,auto_users_list_a,sizeof(auto_users_list_a));
	memcpy(save_it->auto_users_list_b,auto_users_list_b,sizeof(auto_users_list_b));
	memcpy(save_it->rand1_tab,rand1_tab,sizeof(rand1_tab));
	memcpy(save_it->rand2_tab,rand2_tab,sizeof(rand2_tab));
	memcpy(save_it->man2man,man2man,sizeof(man2man));
	memcpy(save_it->glob_str1,glob_str1,sizeof(glob_str1));
	memcpy(save_it->glob_str2,glob_str2,sizeof(glob_str2));

	save_it->sub_pending=sub_pending;

	save_it->return_12=return_12;
	save_it->shamed_player=shamed_player;
	save_it->old_min=old_min;
	save_it->users_left=users_left;
	save_it->setp_x=setp_x;
	save_it->setp_y=setp_y;
	save_it->setp_wait_cnt=setp_wait_cnt;
	save_it->frame=frame;
	save_it->kick_off=kick_off;
	save_it->keep_timer=keep_timer;
	save_it->stop_clock=stop_clock;
	save_it->keep_dive=keep_dive;
	save_it->hold_up_play=hold_up_play;
	save_it->wall_is_up=wall_is_up;
	save_it->card_is_out=card_is_out;
	save_it->crowd_mood_a=crowd_mood_a;
	save_it->crowd_mood_b=crowd_mood_b;
	save_it->possession=possession;
	save_it->poss_held=poss_held;
	save_it->arrow_on=arrow_on;
	save_it->logic_cnt=logic_cnt;
	save_it->ball_move=ball_move;
	save_it->first_bounce=first_bounce;
	save_it->swerve=swerve;
	save_it->spin_cnt=spin_cnt;
	save_it->spin_ball=spin_ball;
	save_it->prediction=prediction;
	save_it->set_xyspin=set_xyspin;
	save_it->set_zspin=set_zspin;
	save_it->ball_horz_ang=ball_horz_ang;
	save_it->ball_vert_ang=ball_vert_ang;
	save_it->max_sw_factor=max_sw_factor;
	save_it->swerve_factor=swerve_factor;
	save_it->rebound_ball=rebound_ball;
	save_it->headed_ball=headed_ball;
	save_it->say_names=say_names;
	save_it->fired_a_shot=fired_a_shot;
	save_it->comm_pass=comm_pass;
	save_it->comm_pass_type=comm_pass_type;
	save_it->keeper_spd=keeper_spd;
	save_it->keeper_down=keeper_down;
	save_it->save_direction=save_direction;
	save_it->keeper_will_save=keeper_will_save;
	save_it->keeper_on_grnd=keeper_on_grnd;
	save_it->keeper_contact=keeper_contact;
	save_it->ball_in_goal=ball_in_goal;
	save_it->ball_in_hands=ball_in_hands;
	save_it->game_action=game_action;
	save_it->throw_cnt=throw_cnt;
	save_it->team_a_goals=team_a_goals;
	save_it->team_b_goals=team_b_goals;
	save_it->last_goal=last_goal;
	save_it->scorer_running=scorer_running;
	save_it->just_scored=just_scored;
	save_it->just_thrown=just_thrown;
	save_it->goal_scorer=goal_scorer;
	save_it->pass_type=pass_type;
	save_it->kick_type=kick_type;
	save_it->receiver=receiver;
	save_it->cross_now=cross_now;
	save_it->auto_select=auto_select;
	save_it->must_face=must_face;
	save_it->must_face_time=must_face_time;
	save_it->must_face_x=must_face_x;
	save_it->must_face_y=must_face_y;
	save_it->must_shoot=must_shoot;
	save_it->chip_pass=chip_pass;
	save_it->must_pass=must_pass;
	save_it->must_punt=must_punt;
	save_it->keeper_a_in_box=keeper_a_in_box;
	save_it->keeper_b_in_box=keeper_b_in_box;
	save_it->keeper_steps=keeper_steps;
	save_it->save_block=save_block;
	save_it->save_xoff=save_xoff;
	save_it->save_yoff=save_yoff;
	save_it->save_zoff=save_zoff;
	save_it->shot_speed=shot_speed;
	save_it->scr_x=scr_x;
	save_it->scr_y=scr_y;
	save_it->ball_speed=ball_speed;
	save_it->ball_int_speed=ball_int_speed;
	save_it->interceptor_a=interceptor_a;
	save_it->interceptor_b=interceptor_b;
	save_it->in_cross_area=in_cross_area;
	save_it->close_in_number=close_in_number;
	save_it->shooter=shooter;
	save_it->ball_inair=ball_inair;
	save_it->super_shot=super_shot;
	save_it->opponents_near_holder=opponents_near_holder;
	save_it->opponents_really_close=opponents_really_close;
	save_it->ball_poss=ball_poss;
	save_it->sender_1_2=sender_1_2;
	save_it->ball_still=ball_still;
	save_it->last_touch=last_touch;
	save_it->want_pass=want_pass;
	save_it->before=before;
	save_it->support_me=support_me;
	save_it->pre_kp_touch=pre_kp_touch;
	save_it->prev_touch=prev_touch;
	save_it->ball_limbo_p=ball_limbo_p;
	save_it->ball_limbo_on=ball_limbo_on;
	save_it->ball_limbo_c=ball_limbo_c;
	save_it->ball_released=ball_released;
	save_it->cannot_pick_up=cannot_pick_up;
	save_it->forced=forced;
	save_it->last_user_a=last_user_a;
	save_it->last_user_b=last_user_b;
	save_it->last_plr_a=last_plr_a;
	save_it->last_plr_b=last_plr_b;
	save_it->players_off_a=players_off_a;
	save_it->players_off_b=players_off_b;
	save_it->want_pass_stat=want_pass_stat;
	save_it->ball_zone1=ball_zone1;
	save_it->ball_zone2=ball_zone2;
	save_it->ball_out_of_play=ball_out_of_play;
	save_it->receiver_a=receiver_a;
	save_it->receiver_b=receiver_b;
	save_it->ready_centre=ready_centre;
	save_it->shot_attempt=shot_attempt;
	save_it->force_select=force_select;
	save_it->heading_ball=heading_ball;
	save_it->flag=flag;
	save_it->rep_camera=rep_camera;
	save_it->sub_camera=sub_camera;
	save_it->allow_replay=allow_replay;
	save_it->replay_pos=replay_pos;
	save_it->old_rep_pos=old_rep_pos;
	save_it->replay_cnt=replay_cnt;
	save_it->pitch_sprs=pitch_sprs;
	save_it->lp_user=lp_user;
	save_it->fixed_net_user=fixed_net_user;
	save_it->auto_users_a=auto_users_a;
	save_it->auto_users_b=auto_users_b;
	save_it->play_ball_a=play_ball_a;
	save_it->play_ball_b=play_ball_b;
	save_it->new_select=new_select;
	save_it->auto_intercept=auto_intercept;
	save_it->closest=closest;
	save_it->f1_down=f1_down;
	save_it->f2_down=f2_down;
	save_it->spec_kick_type=spec_kick_type;
	save_it->setp_hgt=setp_hgt;
	save_it->setp_power=setp_power;
	save_it->setp_kick_x=setp_kick_x;
	save_it->setp_kick_y=setp_kick_y;
	save_it->setp_bxd=setp_bxd;
	save_it->setp_byd=setp_byd;
	save_it->setp_bzd=setp_bzd;
	save_it->user_taker=user_taker;
	save_it->user_taker2=user_taker2;
	save_it->user_controlled=user_controlled;
	save_it->user_plr=user_plr;
	save_it->after_touch_on=after_touch_on;
	save_it->drive_shot=drive_shot;
	save_it->newk_shot=newk_shot;
	save_it->wallx=wallx;
	save_it->wally=wally;
	save_it->men_in_wall=men_in_wall;
	save_it->keeper_pos_x=keeper_pos_x;
	save_it->keeper_pos_y=keeper_pos_y;
	save_it->centre_guy_1=centre_guy_1;
	save_it->centre_guy_2=centre_guy_2;
	save_it->in_range=in_range;
	save_it->in_header_rng=in_header_rng;
	save_it->in_shot_rng=in_shot_rng;
	save_it->taker_x=taker_x;
	save_it->taker_y=taker_y;
	save_it->penalty_shot=penalty_shot;
	save_it->penalties=penalties;
	save_it->penalty_game=penalty_game;
	save_it->home_pens_left=home_pens_left;
	save_it->away_pens_left=away_pens_left;
	save_it->penalty_counter=penalty_counter;
	save_it->pen_taker_a=pen_taker_a;
	save_it->pen_taker_b=pen_taker_b;
	save_it->penalty_team=penalty_team;
	save_it->penalty_taker=penalty_taker;
	save_it->penalty_taker_a=penalty_taker_a;
	save_it->penalty_taker_b=penalty_taker_b;
	save_it->setp_taker=setp_taker;
	save_it->fkick_taker=fkick_taker;
	save_it->fkick_taker_a=fkick_taker_a;
	save_it->fkick_taker_b=fkick_taker_b;
	save_it->gkick_taker=gkick_taker;
	save_it->goal_kicker_a=goal_kicker_a;
	save_it->goal_kicker_b=goal_kicker_b;
	save_it->corner_taker=corner_taker;
	save_it->corn_kicker_a=corn_kicker_a;
	save_it->corn_kicker_b=corn_kicker_b;
	save_it->ktaker=ktaker;
	save_it->bad_guy=bad_guy;
	save_it->direct_fk=direct_fk;
	save_it->play_advantage=play_advantage;
	save_it->set_piece_on=set_piece_on;
	save_it->throw_in_taker=throw_in_taker;
	save_it->main_man=main_man;
	save_it->player_num=player_num;
	save_it->savex=savex;
	save_it->savey=savey;
	save_it->savez=savez;
	save_it->shot_acknowledged=shot_acknowledged;
	save_it->shot_pending=shot_pending;
	save_it->real_shot=real_shot;
	save_it->shot_missed=shot_missed;
	save_it->shot_saved=shot_saved;
	save_it->drib_opps=drib_opps;
	save_it->stop_and_face=stop_and_face;
	save_it->x_face=x_face;
	save_it->y_face=y_face;
	save_it->offside_now=offside_now;
	save_it->can_be_offside=can_be_offside;
	save_it->ref_accuracy=ref_accuracy;
	save_it->ref_strictness=ref_strictness;
	save_it->ref_wait=ref_wait;
	save_it->tussle_ptr=tussle_ptr;
	save_it->crowd_a=crowd_a;
	save_it->crowd_b=crowd_b;
	save_it->kickoff=kickoff;
	save_it->end_game=end_game;
	save_it->team_a=team_a;
	save_it->team_b=team_b;
	save_it->last_centre=last_centre;
	save_it->need_result=need_result;
	save_it->injury_time=injury_time;
	save_it->special_move=special_move;
	save_it->match_half=match_half;
	save_it->opt_user=opt_user;
	save_it->opt_team=opt_team;
	save_it->options_on=options_on;
	save_it->line_up=line_up;
	save_it->player_being_subbed=player_being_subbed;
	save_it->player_on_off=player_on_off;
	save_it->player_coming_on=player_coming_on;
	save_it->booking=booking;
	save_it->subbing_now=subbing_now;
	save_it->first_update=first_update;
	save_it->newdx=newdx;
	save_it->newdy=newdy;
	save_it->wind_on=wind_on;
	save_it->wind_d_trend=wind_d_trend;
	save_it->wind_s_trend=wind_s_trend;
	save_it->wind_x=wind_x;
	save_it->wind_y=wind_y;
	save_it->wind_speed=wind_speed;
	save_it->init_wind_x=init_wind_x;
	save_it->init_wind_y=init_wind_y;
	save_it->init_wind_speed=init_wind_speed;
	save_it->wind_var_ang=wind_var_ang;
	save_it->tactics_a=tactics_a;
	save_it->tactics_b=tactics_b;
	save_it->old_tac_a=old_tac_a;
	save_it->old_tac_b=old_tac_b;
	save_it->afr1=afr1;
	save_it->afr2=afr2;
	save_it->man2man_a=man2man_a;
	save_it->man2man_b=man2man_b;
	save_it->next_mins=next_mins;
	save_it->time_factor=time_factor;
	save_it->clock_running=clock_running;
	save_it->demo_match=demo_match;
	save_it->rolling_clock=rolling_clock;
	save_it->arrow_guy=arrow_guy;
	save_it->rand_seed=rand_seed;
	save_it->seed=seed;
	save_it->man_down=man_down;
	save_it->launch_type=launch_type;
	save_it->launch_x=launch_x;
	save_it->launch_y=launch_y;
	save_it->ballxdis=ballxdis;
	save_it->ballydis=ballydis;
	save_it->ballzdis=ballzdis;
	save_it->ballx=ballx;
	save_it->bally=bally;
	save_it->ballz=ballz;
	save_it->ballx_out=ballx_out;
	save_it->bally_out=bally_out;
	save_it->ballz_out=ballz_out;
	save_it->b_xoff=b_xoff;
	save_it->b_yoff=b_yoff;
	save_it->b_zoff=b_zoff;
	save_it->save_ballx=save_ballx;
	save_it->save_bally=save_bally;
	save_it->save_ballz=save_ballz;
	save_it->save_ball_poss=save_ball_poss;
	save_it->good_poss=good_poss;
	save_it->eff_ballx=eff_ballx;
	save_it->eff_bally=eff_bally;
	save_it->eff_ballz=eff_ballz;
	save_it->prev_ballx=prev_ballx;
	save_it->prev_bally=prev_bally;
	save_it->prev_ballz=prev_ballz;
	save_it->ns_ballx=ns_ballx;
	save_it->ns_bally=ns_bally;
	save_it->ns_ballz=ns_ballz;
	save_it->ball_zspin=ball_zspin;
	save_it->ball_xyspin=ball_xyspin;
	save_it->full_zspin=full_zspin;
	save_it->full_xyspin=full_xyspin;
	save_it->shoot_x=shoot_x;
	save_it->shoot_y=shoot_y;
	save_it->nearest_a=nearest_a;
	save_it->nearest_b=nearest_b;
	save_it->old_ltouch=old_ltouch;
	save_it->old_ball_poss=old_ball_poss;
	save_it->use_ball_limit=use_ball_limit;
	save_it->near_path_a=near_path_a;
	save_it->near_path_b=near_path_b;
	save_it->zone1_x=zone1_x;
	save_it->zone1_y=zone1_y;
	save_it->zone2_x=zone2_x;
	save_it->zone2_y=zone2_y;
	save_it->incident_x=incident_x;
	save_it->incident_y=incident_y;
	save_it->difficulty=difficulty;
	save_it->match_mode=match_mode;
	save_it->dead_ball_cnt=dead_ball_cnt;
	save_it->defense_a=defense_a;
	save_it->defense_b=defense_b;
	save_it->poss_mode=poss_mode;
	save_it->ball_travel=ball_travel;
	save_it->select_cnt=select_cnt;
	save_it->already_there=already_there;
	save_it->reselection=reselection;
	save_it->offside_on=offside_on;

// "C" Vars...
	save_it->joy1_max_x=joy1_max_x;
	save_it->joy1_min_x=joy1_min_x;
	save_it->joy1_max_y=joy1_max_y;
	save_it->joy1_min_y=joy1_min_y;
	save_it->joy1_cnt_x=joy1_cnt_x;
	save_it->joy1_cnt_y=joy1_cnt_y;

	save_it->joy2_max_x=joy2_max_x;
	save_it->joy2_min_x=joy2_min_x;
	save_it->joy2_max_y=joy2_max_y;
	save_it->joy2_min_y=joy2_min_y;
	save_it->joy2_cnt_x=joy2_cnt_x;
	save_it->joy2_cnt_y=joy2_cnt_y;
}

/******************************************************************************
******************************************************************************/

void restore_state(save_data *save_it)
{
	memcpy(teams,save_it->teams,sizeof(teams));
	memcpy(&match_time,&save_it->match_time,sizeof(match_time));
	memcpy(refs,save_it->refs,sizeof(refs));
	memcpy(speech_tab,save_it->speech_tab,sizeof(speech_tab));
	memcpy(wguys,save_it->wguys,sizeof(wguys));
	memcpy(sel_circle,save_it->sel_circle,sizeof(sel_circle));
	memcpy(burst_timer,save_it->burst_timer,sizeof(burst_timer));
	memcpy(auto_users_list_a,save_it->auto_users_list_a,sizeof(auto_users_list_a));
	memcpy(auto_users_list_b,save_it->auto_users_list_b,sizeof(auto_users_list_b));
	memcpy(rand1_tab,save_it->rand1_tab,sizeof(rand1_tab));
	memcpy(rand2_tab,save_it->rand2_tab,sizeof(rand2_tab));
	memcpy(man2man,save_it->man2man,sizeof(man2man));
	memcpy(glob_str1,save_it->glob_str1,sizeof(glob_str1));
	memcpy(glob_str2,save_it->glob_str2,sizeof(glob_str2));

	sub_pending=save_it->sub_pending;

	return_12=save_it->return_12;
	shamed_player=save_it->shamed_player;
	old_min=save_it->old_min;
	users_left=save_it->users_left;
	setp_x=save_it->setp_x;
	setp_y=save_it->setp_y;
	setp_wait_cnt=save_it->setp_wait_cnt;
	frame=save_it->frame;
	kick_off=save_it->kick_off;
	keep_timer=save_it->keep_timer;
	stop_clock=save_it->stop_clock;
	keep_dive=save_it->keep_dive;
	hold_up_play=save_it->hold_up_play;
	wall_is_up=save_it->wall_is_up;
	card_is_out=save_it->card_is_out;
	crowd_mood_a=save_it->crowd_mood_a;
	crowd_mood_b=save_it->crowd_mood_b;
	possession=save_it->possession;
	poss_held=save_it->poss_held;
	arrow_on=save_it->arrow_on;
	logic_cnt=save_it->logic_cnt;
	ball_move=save_it->ball_move;
	first_bounce=save_it->first_bounce;
	swerve=save_it->swerve;
	spin_cnt=save_it->spin_cnt;
	spin_ball=save_it->spin_ball;
	prediction=save_it->prediction;
	set_xyspin=save_it->set_xyspin;
	set_zspin=save_it->set_zspin;
	ball_horz_ang=save_it->ball_horz_ang;
	ball_vert_ang=save_it->ball_vert_ang;
	max_sw_factor=save_it->max_sw_factor;
	swerve_factor=save_it->swerve_factor;
	rebound_ball=save_it->rebound_ball;
	headed_ball=save_it->headed_ball;
	say_names=save_it->say_names;
	fired_a_shot=save_it->fired_a_shot;
	comm_pass=save_it->comm_pass;
	comm_pass_type=save_it->comm_pass_type;
	keeper_spd=save_it->keeper_spd;
	keeper_down=save_it->keeper_down;
	save_direction=save_it->save_direction;
	keeper_will_save=save_it->keeper_will_save;
	keeper_on_grnd=save_it->keeper_on_grnd;
	keeper_contact=save_it->keeper_contact;
	ball_in_goal=save_it->ball_in_goal;
	ball_in_hands=save_it->ball_in_hands;
	game_action=save_it->game_action;
	throw_cnt=save_it->throw_cnt;
	team_a_goals=save_it->team_a_goals;
	team_b_goals=save_it->team_b_goals;
	last_goal=save_it->last_goal;
	scorer_running=save_it->scorer_running;
	just_scored=save_it->just_scored;
	just_thrown=save_it->just_thrown;
	goal_scorer=save_it->goal_scorer;
	pass_type=save_it->pass_type;
	kick_type=save_it->kick_type;
	receiver=save_it->receiver;
	cross_now=save_it->cross_now;
	auto_select=save_it->auto_select;
	must_face=save_it->must_face;
	must_face_time=save_it->must_face_time;
	must_face_x=save_it->must_face_x;
	must_face_y=save_it->must_face_y;
	must_shoot=save_it->must_shoot;
	chip_pass=save_it->chip_pass;
	must_pass=save_it->must_pass;
	must_punt=save_it->must_punt;
	keeper_a_in_box=save_it->keeper_a_in_box;
	keeper_b_in_box=save_it->keeper_b_in_box;
	keeper_steps=save_it->keeper_steps;
	save_block=save_it->save_block;
	save_xoff=save_it->save_xoff;
	save_yoff=save_it->save_yoff;
	save_zoff=save_it->save_zoff;
	shot_speed=save_it->shot_speed;
	scr_x=save_it->scr_x;
	scr_y=save_it->scr_y;
	ball_speed=save_it->ball_speed;
	ball_int_speed=save_it->ball_int_speed;
	interceptor_a=save_it->interceptor_a;
	interceptor_b=save_it->interceptor_b;
	in_cross_area=save_it->in_cross_area;
	close_in_number=save_it->close_in_number;
	shooter=save_it->shooter;
	ball_inair=save_it->ball_inair;
	super_shot=save_it->super_shot;
	opponents_near_holder=save_it->opponents_near_holder;
	opponents_really_close=save_it->opponents_really_close;
	ball_poss=save_it->ball_poss;
	sender_1_2=save_it->sender_1_2;
	ball_still=save_it->ball_still;
	last_touch=save_it->last_touch;
	want_pass=save_it->want_pass;
	before=save_it->before;
	support_me=save_it->support_me;
	pre_kp_touch=save_it->pre_kp_touch;
	prev_touch=save_it->prev_touch;
	ball_limbo_p=save_it->ball_limbo_p;
	ball_limbo_on=save_it->ball_limbo_on;
	ball_limbo_c=save_it->ball_limbo_c;
	ball_released=save_it->ball_released;
	cannot_pick_up=save_it->cannot_pick_up;
	forced=save_it->forced;
	last_user_a=save_it->last_user_a;
	last_user_b=save_it->last_user_b;
	last_plr_a=save_it->last_plr_a;
	last_plr_b=save_it->last_plr_b;
	players_off_a=save_it->players_off_a;
	players_off_b=save_it->players_off_b;
	want_pass_stat=save_it->want_pass_stat;
	ball_zone1=save_it->ball_zone1;
	ball_zone2=save_it->ball_zone2;
	ball_out_of_play=save_it->ball_out_of_play;
	receiver_a=save_it->receiver_a;
	receiver_b=save_it->receiver_b;
	ready_centre=save_it->ready_centre;
	shot_attempt=save_it->shot_attempt;
	force_select=save_it->force_select;
	heading_ball=save_it->heading_ball;
	flag=save_it->flag;
	rep_camera=save_it->rep_camera;
	sub_camera=save_it->sub_camera;
	allow_replay=save_it->allow_replay;
	replay_pos=save_it->replay_pos;
	old_rep_pos=save_it->old_rep_pos;
	replay_cnt=save_it->replay_cnt;
	pitch_sprs=save_it->pitch_sprs;
	lp_user=save_it->lp_user;
	fixed_net_user=save_it->fixed_net_user;
	auto_users_a=save_it->auto_users_a;
	auto_users_b=save_it->auto_users_b;
	play_ball_a=save_it->play_ball_a;
	play_ball_b=save_it->play_ball_b;
	new_select=save_it->new_select;
	auto_intercept=save_it->auto_intercept;
	closest=save_it->closest;
	f1_down=save_it->f1_down;
	f2_down=save_it->f2_down;
	spec_kick_type=save_it->spec_kick_type;
	setp_hgt=save_it->setp_hgt;
	setp_power=save_it->setp_power;
	setp_kick_x=save_it->setp_kick_x;
	setp_kick_y=save_it->setp_kick_y;
	setp_bxd=save_it->setp_bxd;
	setp_byd=save_it->setp_byd;
	setp_bzd=save_it->setp_bzd;
	user_taker=save_it->user_taker;
	user_taker2=save_it->user_taker2;
	user_controlled=save_it->user_controlled;
	user_plr=save_it->user_plr;
	after_touch_on=save_it->after_touch_on;
	drive_shot=save_it->drive_shot;
	newk_shot=save_it->newk_shot;
	wallx=save_it->wallx;
	wally=save_it->wally;
	men_in_wall=save_it->men_in_wall;
	keeper_pos_x=save_it->keeper_pos_x;
	keeper_pos_y=save_it->keeper_pos_y;
	centre_guy_1=save_it->centre_guy_1;
	centre_guy_2=save_it->centre_guy_2;
	in_range=save_it->in_range;
	in_header_rng=save_it->in_header_rng;
	in_shot_rng=save_it->in_shot_rng;
	taker_x=save_it->taker_x;
	taker_y=save_it->taker_y;
	penalty_shot=save_it->penalty_shot;
	penalties=save_it->penalties;
	penalty_game=save_it->penalty_game;
	home_pens_left=save_it->home_pens_left;
	away_pens_left=save_it->away_pens_left;
	penalty_counter=save_it->penalty_counter;
	pen_taker_a=save_it->pen_taker_a;
	pen_taker_b=save_it->pen_taker_b;
	penalty_team=save_it->penalty_team;
	penalty_taker=save_it->penalty_taker;
	penalty_taker_a=save_it->penalty_taker_a;
	penalty_taker_b=save_it->penalty_taker_b;
	setp_taker=save_it->setp_taker;
	fkick_taker=save_it->fkick_taker;
	fkick_taker_a=save_it->fkick_taker_a;
	fkick_taker_b=save_it->fkick_taker_b;
	gkick_taker=save_it->gkick_taker;
	goal_kicker_a=save_it->goal_kicker_a;
	goal_kicker_b=save_it->goal_kicker_b;
	corner_taker=save_it->corner_taker;
	corn_kicker_a=save_it->corn_kicker_a;
	corn_kicker_b=save_it->corn_kicker_b;
	ktaker=save_it->ktaker;
	bad_guy=save_it->bad_guy;
	direct_fk=save_it->direct_fk;
	play_advantage=save_it->play_advantage;
	set_piece_on=save_it->set_piece_on;
	throw_in_taker=save_it->throw_in_taker;
	main_man=save_it->main_man;
	player_num=save_it->player_num;
	savex=save_it->savex;
	savey=save_it->savey;
	savez=save_it->savez;
	shot_acknowledged=save_it->shot_acknowledged;
	shot_pending=save_it->shot_pending;
	real_shot=save_it->real_shot;
	shot_missed=save_it->shot_missed;
	shot_saved=save_it->shot_saved;
	drib_opps=save_it->drib_opps;
	stop_and_face=save_it->stop_and_face;
	x_face=save_it->x_face;
	y_face=save_it->y_face;
	offside_now=save_it->offside_now;
	can_be_offside=save_it->can_be_offside;
	ref_accuracy=save_it->ref_accuracy;
	ref_strictness=save_it->ref_strictness;
	ref_wait=save_it->ref_wait;
	tussle_ptr=save_it->tussle_ptr;
	crowd_a=save_it->crowd_a;
	crowd_b=save_it->crowd_b;
	kickoff=save_it->kickoff;
	end_game=save_it->end_game;
	team_a=save_it->team_a;
	team_b=save_it->team_b;
	last_centre=save_it->last_centre;
	need_result=save_it->need_result;
	injury_time=save_it->injury_time;
	special_move=save_it->special_move;
	match_half=save_it->match_half;
	opt_user=save_it->opt_user;
	opt_team=save_it->opt_team;
	options_on=save_it->options_on;
	line_up=save_it->line_up;
	player_being_subbed=save_it->player_being_subbed;
	player_on_off=save_it->player_on_off;
	player_coming_on=save_it->player_coming_on;
	booking=save_it->booking;
	subbing_now=save_it->subbing_now;
	first_update=save_it->first_update;
	newdx=save_it->newdx;
	newdy=save_it->newdy;
	wind_on=save_it->wind_on;
	wind_d_trend=save_it->wind_d_trend;
	wind_s_trend=save_it->wind_s_trend;
	wind_x=save_it->wind_x;
	wind_y=save_it->wind_y;
	wind_speed=save_it->wind_speed;
	init_wind_x=save_it->init_wind_x;
	init_wind_y=save_it->init_wind_y;
	init_wind_speed=save_it->init_wind_speed;
	wind_var_ang=save_it->wind_var_ang;
	tactics_a=save_it->tactics_a;
	tactics_b=save_it->tactics_b;
	old_tac_a=save_it->old_tac_a;
	old_tac_b=save_it->old_tac_b;
	afr1=save_it->afr1;
	afr2=save_it->afr2;
	man2man_a=save_it->man2man_a;
	man2man_b=save_it->man2man_b;
	next_mins=save_it->next_mins;
	time_factor=save_it->time_factor;
	clock_running=save_it->clock_running;
	demo_match=save_it->demo_match;
	rolling_clock=save_it->rolling_clock;
	arrow_guy=save_it->arrow_guy;
	rand_seed=save_it->rand_seed;
	seed=save_it->seed;
	man_down=save_it->man_down;
	launch_type=save_it->launch_type;
	launch_x=save_it->launch_x;
	launch_y=save_it->launch_y;
	ballxdis=save_it->ballxdis;
	ballydis=save_it->ballydis;
	ballzdis=save_it->ballzdis;
	ballx=save_it->ballx;
	bally=save_it->bally;
	ballz=save_it->ballz;
	ballx_out=save_it->ballx_out;
	bally_out=save_it->bally_out;
	ballz_out=save_it->ballz_out;
	b_xoff=save_it->b_xoff;
	b_yoff=save_it->b_yoff;
	b_zoff=save_it->b_zoff;
	save_ballx=save_it->save_ballx;
	save_bally=save_it->save_bally;
	save_ballz=save_it->save_ballz;
	save_ball_poss=save_it->save_ball_poss;
	good_poss=save_it->good_poss;
	eff_ballx=save_it->eff_ballx;
	eff_bally=save_it->eff_bally;
	eff_ballz=save_it->eff_ballz;
	prev_ballx=save_it->prev_ballx;
	prev_bally=save_it->prev_bally;
	prev_ballz=save_it->prev_ballz;
	ns_ballx=save_it->ns_ballx;
	ns_bally=save_it->ns_bally;
	ns_ballz=save_it->ns_ballz;
	ball_zspin=save_it->ball_zspin;
	ball_xyspin=save_it->ball_xyspin;
	full_zspin=save_it->full_zspin;
	full_xyspin=save_it->full_xyspin;
	shoot_x=save_it->shoot_x;
	shoot_y=save_it->shoot_y;
	nearest_a=save_it->nearest_a;
	nearest_b=save_it->nearest_b;
	old_ltouch=save_it->old_ltouch;
	old_ball_poss=save_it->old_ball_poss;
	use_ball_limit=save_it->use_ball_limit;
	near_path_a=save_it->near_path_a;
	near_path_b=save_it->near_path_b;
	zone1_x=save_it->zone1_x;
	zone1_y=save_it->zone1_y;
	zone2_x=save_it->zone2_x;
	zone2_y=save_it->zone2_y;
	incident_x=save_it->incident_x;
	incident_y=save_it->incident_y;
	difficulty=save_it->difficulty;
	match_mode=save_it->match_mode;
	dead_ball_cnt=save_it->dead_ball_cnt;
	defense_a=save_it->defense_a;
	defense_b=save_it->defense_b;
	poss_mode=save_it->poss_mode;
	ball_travel=save_it->ball_travel;
	select_cnt=save_it->select_cnt;
	already_there=save_it->already_there;
	reselection=save_it->reselection;
	offside_on=save_it->offside_on;

// "C" Vars...
	joy1_max_x=save_it->joy1_max_x;
	joy1_min_x=save_it->joy1_min_x;
	joy1_max_y=save_it->joy1_max_y;
	joy1_min_y=save_it->joy1_min_y;
	joy1_cnt_x=save_it->joy1_cnt_x;
	joy1_cnt_y=save_it->joy1_cnt_y;

	joy2_max_x=save_it->joy2_max_x;
	joy2_min_x=save_it->joy2_min_x;
	joy2_max_y=save_it->joy2_max_y;
	joy2_min_y=save_it->joy2_min_y;
	joy2_cnt_x=save_it->joy2_cnt_x;
	joy2_cnt_y=save_it->joy2_cnt_y;
}

#ifdef EURO96
/******************************************************************************
*****************************************************************************/

void checksum_state()
{
	short *ptr=(short *)state_ptr;
	ptr+=(sizeof(save_data)/sizeof(short));
	short lim=CHECKSUM_CHUNK;

	_disable();
// Must finish checksum before netsend...

	if (checksum_ptr<ptr)
	{
// Some data left to checksum...
		for (short i=0; i<lim; i++)
		{
			state_checksum^=*checksum_ptr++;
			if (checksum_ptr>=ptr)
				i=lim;
		}
	}
	logic_cnt++;
	_enable();
}

/******************************************************************************
******************************************************************************/

void process_state()
{
	checksum_state();

	if (!(logic_cnt%(REAL_SPEED*STATE_INTERVAL)))
	{
// Time for a save...
		if (state_ptr==&state1)
			state_ptr=&state2;
		else
			state_ptr=&state1;
		save_state(state_ptr);
		checksum_ptr=(short *)state_ptr;
	}
}

/******************************************************************************
******************************************************************************/

void reset_state(char buff)
{
// Buff indicates current (0) or previous state (1)!

	if (buff)
// Swap state_ptr...
		if (state_ptr==&state1)
			state_ptr=&state2;
		else
			state_ptr=&state1;

	restore_state(state_ptr);
	checksum_ptr=(short *)state_ptr;
	state_checksum=0xafaf;
}

#endif

/******************************************************************************
*****************************************************************************/

void variable_wind()
{
// Variable speed and direction around initial settings...

// Do dir.
	if (wind_d_trend>0)
	{
// Wind current dir gets further from initial setting...
		wind_d_trend--;
		if (wind_var_ang<0)
			wind_var_ang-=(MAX_WIND_CHANGE*seed/128);
		else
			wind_var_ang+=(MAX_WIND_CHANGE*seed/128);

		wind_x=(init_wind_x*cos(wind_var_ang))-(init_wind_y*sin(wind_var_ang));
		wind_y=(init_wind_y*cos(wind_var_ang))+(init_wind_x*sin(wind_var_ang));
	}
	else
	{
		if (wind_d_trend<0)
		{
// Wind current dir returns to initial setting...
			wind_d_trend++;
			if (wind_var_ang<0)
				wind_var_ang+=(MAX_WIND_CHANGE*seed/128);
			else
				wind_var_ang-=(MAX_WIND_CHANGE*seed/128);

			wind_x=(init_wind_x*cos(wind_var_ang))-(init_wind_y*sin(wind_var_ang));
			wind_y=(init_wind_y*cos(wind_var_ang))+(init_wind_x*sin(wind_var_ang));
		}
		else
		{
// New trend...
			if (ABS(wind_var_ang*128/PI)<seed)
				wind_d_trend=WIND_BLUSTERINESS;
			else
				wind_d_trend=-WIND_BLUSTERINESS;
		}
	}
	
	af_randomize();

// Do speed.
	if (wind_s_trend>0)
	{
// Increment difference in speed...
		wind_s_trend--;
		if ((wind_speed-init_wind_speed)<0)
		{
			wind_speed-=(MAX_WIND_S_CHANGE*seed/128);
			if (wind_speed<0)
				wind_speed=0;
		}
		else
		{
			wind_speed+=(MAX_WIND_S_CHANGE*seed/128);
			if (wind_speed>128)
				wind_speed=128;
		}
	}
	else
	{
		if (wind_s_trend<0)
		{
// Decrement difference in speed...
			wind_s_trend++;
			if ((wind_speed-init_wind_speed)<0)
			{
				wind_speed+=(MAX_WIND_S_CHANGE*seed/128);
				if (wind_speed>128)
					wind_speed=128;
			}
			else
			{
				wind_speed-=(MAX_WIND_S_CHANGE*seed/128);
				if (wind_speed<0)
					wind_speed=0;
			}
		}
		else
		{
// New trend...
			if (ABS(wind_speed-init_wind_speed)<(seed/2))
				wind_s_trend=WIND_GUSTINESS;
			else
				wind_s_trend=-WIND_GUSTINESS;
		}
	}
}

/******************************************************************************
******************************************************************************/

int coo=0;
char gkey=0;
	  
void do_logic()
{
	init_pitch_sprites();

#ifdef SAVE_GAME
	if (keys[0x11])	// w
	{
		save_game();
	}

	if (keys[0x2c])	// z
	{
		restore_game();
	}
#endif

#ifndef COVERDISK
	if (debug && key_togs[0x30])		// b
	{
// Move ball around with mouse.
		ReportMouse();
		ballx=Mouse.x*5-160;
		bally=Mouse.y*5-160;
		char key=0;
		float x,y;
	}
#endif

// Normal logic mode.
/*
	if (!match_mode)
	{
		if (!--pen_cnt)
			force_penalty();
	}
*/
	frame=(frame) ? 0:1;
	af_randomize();

	if (!on_3d)
	{
		ReportMouse();
	}

	process_subs();

	if (wind_on<0)
		variable_wind();		// Get current wind parameters...

	process_ball();

	match_rules();
	keeper_boxes();
	player_distances();
	get_nearest();		// near_path_a, near_path_b
	get_opp_near_ball(ball_poss);

	process_speech();
	process_comments();
	process_flags();
	process_teams();
	new_users();
	select_all_hlites();
	process_offs();

	if (!match_mode && comsetp)
		--comsetp;
}

/******************************************************************************
*****************************************************************************/

void stop_mf_time()
{
/*
	int cl=clock();
	int c=cl/CLOCKS_PER_SEC;
	last_second=c;
	old_clock=cl;
*/
	oldcnt=count-1;
}

/******************************************************************************
*****************************************************************************/

void pause_game()
{
	char key=0;

	do{
	}while (paused);

	stop_mf_time();
}

/******************************************************************************
*****************************************************************************/

extern "C" char calibrated_1,calibrated_2;

/******************************************************************************
*****************************************************************************/

void init_joy1()
{
	calibrated_1=FALSE;
 	joy1_min_x=20000;
 	joy1_max_x=0;
 	joy1_min_y=20000;
 	joy1_max_y=0;
}

/******************************************************************************
*****************************************************************************/

void init_joy2()
{
 	calibrated_2=FALSE;
 	joy2_min_x=20000;
 	joy2_max_x=0;
 	joy2_min_y=20000;
 	joy2_max_y=0;
}

/******************************************************************************
*****************************************************************************/

void init_joys()
{
 	init_joy1();
 	init_joy2();
}


void process_keys()
{
	if (!demo_match || debug)
	{
		while(escape_pending>0)
		{
			if (keys[0x15])	// Y
			{
				add_message("Leaving Match!",RED,TRUE);
				escape_pending=-1;
			}

			if (keys[0x31])	// N
			{
				add_message(" ",WHITE,TRUE);
				escape_pending=FALSE;
				stop_mf_time();
			}
		}

		if (paused)
			pause_game();

		if (keys[0x3b] && keys[0x1d] && joystick1_on)
		{
// Ctrl F1...
			calibrated_1=FALSE;
			init_joy1();
			add_message("Auto Calibrating Port 1",WHITE,TRUE);
		}

		if (keys[0x3c] && keys[0x1d] && joystick2_on)
		{
// Ctrl F2...
			calibrated_2=FALSE;
			init_joy2();
			add_message("Auto Calibrating Port 2",WHITE,TRUE);
		}

#ifdef NO_AUTO_SEL
		if (keys[0x43])			// f9
			if (key_togs[0x43])
				add_message("Manual Switching",WHITE,TRUE);
			else
				add_message("Automatic Switching",WHITE,TRUE);
#endif

#ifndef COVERDISK
		if (debug)
		{
			if (keys[0x11] && ball_poss && !match_mode)
			{
				short b=ball_poss;
				holder_lose_ball();
				init_foul((b<12 ? 13:2),TRUE,TRUE);	// pass no. of fouler.
			}

			if (keys[0x0f])
				delete_net_user(2);

/*
			if (keys[0x14])		// t
				if (key_togs[0x14])
					tweening=TRUE;
				else
					tweening=FALSE;
*/
			if (keys[0x14])		// t
			{
				do; while(keys[0x14]);
				if (++xinfo>8)
					xinfo=0;
			}
/*
			if (keys[0x0f])		// TAB
			{
				delete_net_user(2);
				while(keys[0x14]);
			}
*/
			if (keys[0x21])		// f
			{
// Fixed speed...
				mf_fixed=TRUE;
				mf_scale=1;
			}

			if (keys[0x22])		// g
			{
// Variable speed...
				mf_fixed=FALSE;
			}

			if (keys[0x4a])		// +
			{
// Game Faster...
				if (game_speed>0)
					game_speed--;
			}

			if (keys[0x4e])		// -
			{
// Game Slower...
				game_speed++;
			}
		}
#endif

		if (!network_on && !player_on_off && !line_up && match_mode!=SWAP_ENDS)
		{

#ifdef SUPPORT_LP
			if (keys[0x3b] || (users_dir[0].f&8 && users_dir[0].f&4 && !(users_dir[0].f&48)))		// LS + RS
			{
				if (num_of_users>=1)
				{
// User player 1 options...
					opt_user=1;
				}
				else
// No user players...
					opt_user=-1;
			}

			if ((keys[0x3c]  || (users_dir[1].f&8 && users_dir[1].f&4) && !(users_dir[0].f&48)) && num_of_users>=2)
			{
// User player 2 options...
				opt_user=2;
			}

			if ((keys[0x3d]  || (users_dir[2].f&8 && users_dir[2].f&4) && !(users_dir[0].f&48)) && num_of_users>=3)
			{
// User player 3 options...
				opt_user=3;
			}

			if ((keys[0x3e]  || (users_dir[3].f&8 && users_dir[3].f&4) && !(users_dir[0].f&48)) && num_of_users>=4)
			{
// User player 4 options...
				opt_user=4;
			}
#else
			if (keys[0x3b] && !keys[0x1d])				// F1
			{
				if (num_of_users>=1)
				{
// User player 1 options...
					opt_user=1;
				}
				else
// No user players...
					opt_user=-1;
			}

			if (keys[0x3c] && !keys[0x1d] && num_of_users>=2)	// F2
			{
// User player 2 options...
				opt_user=2;
			}

			if (keys[0x3d] && !keys[0x1d] && num_of_users>=3)	// F3
			{
// User player 3 options...
				opt_user=3;
			}

			if (keys[0x3e] && !keys[0x1d] && num_of_users>=4)	// F4
			{
// User player 4 options...
				opt_user=4;
			}
#endif
	
			if (opt_user)
			{
				if (users[opt_user-1].type==-1)
					opt_team=team_a;
				else
					if (users[opt_user-1].type==-2)
						opt_team=team_b;
					else
						if (users[opt_user-1].type<12)
							opt_team=team_a;
						else
							opt_team=team_b;
			}
		}
	}
	else
		if (anykey)
			end_game=TRUE;
}

/******************************************************************************
*****************************************************************************/

void animate_players()
{
	for (int i=0; i<players; i++)
	{
		teams[i].tm_frm+=teams[i].tm_fstep;
	}

	for (i=0; i<3; i++)
	{
	 	refs[i].frm+=refs[i].fstep;
	}
}

/******************************************************************************
*****************************************************************************/

void update_2d()
{
	if	(plot_buffer)
		plot_cnta=1;
	else
		plot_cntb=1;

	_setplotaction(_GPSET);
	process_butts();
	_setplotaction(_GXOR);
	if (Mouse.b&&1)
		mouse_fired();
	draw_ball();
	draw_team();
	draw_buffer();

	plot_buffer=!plot_buffer;
	draw_buffer();
	delay(delay_cnt);
	panel_data();
}

/******************************************************************************
*****************************************************************************/

void reset_possession()
{
	poss_held=0;
	possession=0;
}

/******************************************************************************
*****************************************************************************/

void accumulate_possession()
{
	if (ball_poss>11)
	{
// Team b. currently has possession...
		poss_held+=(0.0001+(ABS(poss_held)/30));
		if (poss_held>0.5)
			poss_held=0.5;
	}
	else
	{
		if (ball_poss)
// Team a. currently has possession...
		{
			poss_held-=(0.0001+(ABS(poss_held)/30));
			if (poss_held<-0.5)
				poss_held=-0.5;
		}
	}
	
	if (!ball_poss)
	{
// Ball is free...(tend slowly towards 0)
		poss_held+=(-poss_held/60);
	}

	possession+=poss_held;
	if (possession>1)
		possession=1;
	if (possession<-1)
		possession=-1;
}

/******************************************************************************
*****************************************************************************/

void process_crowd_noise()
{
	if (shot_missed)
	{
		if (shot_missed<0)
		{
// Missed by a long way...
			shot_missed++;
			if (last_touch<12)
			{
// team A shot...
				crowd_mood_a=CN_BOO;
				crowd_mood_b=CN_LAUGH;
			}
			else
			{
// team B shot...
				crowd_mood_a=CN_LAUGH;
				crowd_mood_b=CN_BOO;
			}
		}
		else
		{
// Near missed...
			shot_missed--;
			if (last_touch<12)
			{
// team A shot...
				crowd_mood_a=CN_MISS;
				crowd_mood_b=CN_PENSIVE;
			}
			else
			{
// team B shot...
				crowd_mood_a=CN_PENSIVE;
				crowd_mood_b=CN_MISS;
			}
		}
	}
	else
	{
		if (shot_saved)
		{
// Shot stopped...
			shot_saved--;
			if (last_touch<12)
			{
// team A save...
				crowd_mood_a=CN_SAVE;
				crowd_mood_b=CN_MISS;
			}
			else
			{
// team B save...
				crowd_mood_a=CN_MISS;
				crowd_mood_b=CN_SAVE;
			}
		}
		else	
		{
			if (card_is_out)
			{
				card_is_out--;
				crowd_mood_a=CN_FOWL;
				crowd_mood_b=CN_FOWL;
			}
			else
			{
				if (match_half>10)
				{
// End of Game...
					crowd_mood_a=CN_EXCITED;
					crowd_mood_b=CN_EXCITED;
				}
				else
				{
					switch(match_mode)
					{
						case(NORMAL_PLAY):
				
							if (shot_pending && shot_acknowledged)
							{
// Keeper is reacting to incoming ball...
								if (ballx<prat*40 && ballxdis<0 && last_touch>11)
								{
// Ball coming left (from team B)...
									crowd_mood_a=CN_PENSIVE;
									crowd_mood_b=CN_EXCITED;
								}
								if (ballx>(pitch_len-(prat*40)) && ballxdis>0 && last_touch<12)
								{
// Ball coming right (from team A)...
									crowd_mood_a=CN_EXCITED;
									crowd_mood_b=CN_PENSIVE;
								}
							}
							else
							{
								accumulate_possession();
					
								if (ball_in_hands && (ball_poss==KP_A || ball_poss==KP_B))
								{
// Keepers ball...(calm)
									crowd_mood_a=CN_NORMAL;
									crowd_mood_b=CN_NORMAL;
								}
								else
								{
									if ((ballx>(cntspot_x-prat*16)) && (ballx<(cntspot_x+prat*16)))
									{
// In mid-field...
										crowd_mood_a=CN_NORMAL;
										crowd_mood_b=CN_NORMAL;
									}
									else
									{
										if (ballx<=(cntspot_x-prat*16))
										{
// Near Goal A...
											if (possession>0.5)
											{
// Team B has good possession...
												crowd_mood_a=CN_PENSIVE;
												crowd_mood_b=CN_EXCITED;
											}
											else
											{
												if (possession<-0.5)
												{
// Defending team A has it under control...
													crowd_mood_a=CN_NORMAL;
													crowd_mood_b=CN_NORMAL;
												}
												else
												{
// No one team has it under control...
													crowd_mood_a=CN_NORMAL;
													crowd_mood_b=CN_ENCOURAGING;
												}
											}
										}
										else
										{
// Near Goal B...
											if (possession<-0.5)
											{
// Team A has good possession...
												crowd_mood_a=CN_EXCITED;
												crowd_mood_b=CN_PENSIVE;
											}
											else
											{
												if (possession>0.5)
												{
// Defending team B has it under control...
													crowd_mood_a=CN_NORMAL;
													crowd_mood_b=CN_NORMAL;
												}
												else
												{
// No one team has it under control...
													crowd_mood_a=CN_ENCOURAGING;
													crowd_mood_b=CN_NORMAL;
												}
											}
										}
									}
								}
		
								if (just_scored)
								{
// someone has scored a goal...
									if (ballx<cntspot_x)
									{
// Team A. goal...
										if (goal_scorer>11)
										{
// Team B scores good goal!
											crowd_mood_a=CN_PENSIVE;
											crowd_mood_b=CN_CELEBRATE;
										}
										else
										{
// Team A scores own goal!
											crowd_mood_a=CN_BOO;
											crowd_mood_b=CN_CELEBRATE;
										}						
									}
									else
									{
// Team B. goal...
										if (goal_scorer<12)
										{
// Team A scores good goal!
											crowd_mood_a=CN_CELEBRATE;
											crowd_mood_b=CN_PENSIVE;
										}
										else
										{
// Team B scores own goal!
											crowd_mood_a=CN_CELEBRATE;
											crowd_mood_b=CN_BOO;
										}						
									}
								}
							}
							break;
		
						case(DF_KICK_B):
							if (!men_in_wall)			// Not in shooting range!
							{
								if ((ballx>(cntspot_x-prat*16)) && (ballx<(cntspot_x+prat*16)))
								{
// In mid-field...
									crowd_mood_a=CN_NORMAL;
									crowd_mood_b=CN_NORMAL;
								}
								else
								{
									if (ballx<=(cntspot_x-prat*16))
									{
// Near Goal A...
										crowd_mood_a=CN_PENSIVE;
										crowd_mood_b=CN_ENCOURAGING;
									}
									else
									{
// Near Own Goal B...
										crowd_mood_a=CN_NORMAL;
										crowd_mood_b=CN_NORMAL;
									}
								}
								break;
							}
		
						case(CORNER_TL):	
						case(CORNER_BL):	
							crowd_mood_a=CN_PENSIVE;
							crowd_mood_b=CN_EXCITED;
							break;
					
						case(DF_KICK_A):
							if (!men_in_wall)			// Not in shooting range!
							{
								if ((ballx>(cntspot_x-prat*16)) && (ballx<(cntspot_x+prat*16)))
								{
// In mid-field...
									crowd_mood_a=CN_NORMAL;
									crowd_mood_b=CN_NORMAL;
								}
								else
								{
									if (ballx>=(cntspot_x+prat*16))
									{
// Near Goal B...
										crowd_mood_a=CN_ENCOURAGING;
										crowd_mood_b=CN_PENSIVE;
									}
									else
									{
// Near Own Goal A...
										crowd_mood_a=CN_NORMAL;
										crowd_mood_b=CN_NORMAL;
									}
								}
								break;
							}
						
						case(CORNER_TR):	
						case(CORNER_BR):	
							crowd_mood_a=CN_EXCITED;
							crowd_mood_b=CN_PENSIVE;
							break;
		
						case(GOAL_KICK_TL):
						case(GOAL_KICK_TR):
						case(GOAL_KICK_BL):
						case(GOAL_KICK_BR):
							crowd_mood_a=CN_NORMAL;
							crowd_mood_b=CN_NORMAL;
							reset_possession();
							break;
		
						case(IF_KICK_A):
						case(THROW_IN_A):
							if ((ballx>(cntspot_x-prat*16)) && (ballx<(cntspot_x+prat*16)))
							{
// In mid-field...
								crowd_mood_a=CN_NORMAL;
								crowd_mood_b=CN_NORMAL;
							}
							else
							{
								if (ballx>=(cntspot_x+prat*16))
								{
// Near Goal B...
									crowd_mood_a=CN_ENCOURAGING;
									crowd_mood_b=CN_PENSIVE;
								}
								else
								{
// Near Own Goal A...
									crowd_mood_a=CN_NORMAL;
									crowd_mood_b=CN_NORMAL;
								}
							}
							break;
		
						case(IF_KICK_B):
						case(THROW_IN_B):
							if ((ballx>(cntspot_x-prat*16)) && (ballx<(cntspot_x+prat*16)))
							{
// In mid-field...
								crowd_mood_a=CN_NORMAL;
								crowd_mood_b=CN_NORMAL;
							}
							else
							{
								if (ballx<=(cntspot_x-prat*16))
								{
// Near Goal A...
									crowd_mood_a=CN_PENSIVE;
									crowd_mood_b=CN_ENCOURAGING;
								}
								else
								{
// Near Own Goal B...
									crowd_mood_a=CN_NORMAL;
									crowd_mood_b=CN_NORMAL;
								}
							}
							break;
		
						case(PEN_KICK_A):
						case(PEN_KICK_B):
						case(SWAP_ENDS):
							crowd_mood_a=CN_EXCITED;
							crowd_mood_b=CN_EXCITED;
							break;
					
						case(CENTRE_A):
						case(CENTRE_B):
							reset_possession();
							if (kickoff)
							{
								crowd_mood_a=CN_EXCITED;
								crowd_mood_b=CN_EXCITED;
							}
							else
							{
								crowd_mood_a=CN_NORMAL;
								crowd_mood_b=CN_NORMAL;
							}
							break;
					}
				}
			}
		}
	}
}

/******************************************************************************
*****************************************************************************/

char nothing_happening()
{
	if (!match_mode && !just_scored)
	{
// In Play...
		play_fx(PS_FULLTIMEWHISTLE,refs[0].x,refs[0].y);



		if (shot_pending || dead_ball_cnt || game_action)
			return(FALSE);			// Crucial moment!
		else
			return(TRUE);
	}
	else
	{
		if (match_mode<=CORNER_BR || match_mode>=PEN_KICK_A)
			return(FALSE);			// Crucial moment!
		else
			if ((match_mode==DF_KICK_B || match_mode==DF_KICK_A) && men_in_wall)
				return(FALSE);			// Crucial moment!
			else
				return(TRUE);
	}
}

/******************************************************************************
*****************************************************************************/

void watch_match_time()
{
	if (golden_goal==2 && !just_scored)
	{
// End of sudden death...
		if (match_half<11)
		{
// Start leaving field!
			play_fx(PS_FULLTIMEWHISTLE,refs[0].x,refs[0].y);
			last_goal=0;
			match_mode=SWAP_ENDS;
			init_match_mode();
			do_full_time_anim(0);
			do_fulltime_menu();
			match_half=11;			// End game!
			PlayCommentaryMessage(TI_FULLTIME);
			next_mins=0;
#ifdef EURO96
			get_performance();
			xinfo=9;
			if (man_of_match)
				camera=18;
#endif
		}
	}
	else
	{
	if (match_info.CompetitionType==PENALTIES)
	{
// Practice penalties...
		if (!penalty_game)
		{
			if (team_a_goals!=team_b_goals)
			{
// Someone has won shoot-out...
				if (match_half<11)
				{
// Initialise end of penalty shoot-out...
					last_goal=0;
					match_mode=SWAP_ENDS;
					init_match_mode();
					do_full_time_anim(0);
					EUROmatch_info.Team_A_penalties=team_a_goals;
					EUROmatch_info.Team_B_penalties=team_b_goals;
					do_final_score_menu();
					match_half=11;			// End game!
					PlayCommentaryMessage(TI_FULLTIME);
					next_mins=0;
#ifdef EURO96
					get_performance();
					xinfo=9;
					if (man_of_match)
						camera=18;
#endif
				}
			}
			else
			{
// Initialise penalty shoot-out...
				EUROmatch_info.penalties=TRUE;
				penalty_game=TRUE;
				team_a_goals=0;
				team_b_goals=0;
				EUROmatch_info.Team_A_penalties=team_a_goals;
				EUROmatch_info.Team_B_penalties=team_b_goals;
				do_penalty_shootout_menu();
				next_mins=0;
			}
		}
	}
	else
	{
	 	if (match_time.min>=(45+injury_time) && !match_half && nothing_happening())
		{
// End of first half! (It's a game of two halves...)
#ifdef DEMO
			last_goal=0;
			match_mode=SWAP_ENDS;
			init_match_mode();
			play_fx(PS_FULLTIMEWHISTLE,refs[0].x,refs[0].y);
			do_full_time_anim(0);
			do_fulltime_menu();
			PlayCommentaryMessage(TI_FULLTIME);
			match_half=11;			// End game!
			next_mins=0;
#else
			match_mode=SWAP_ENDS;
			last_goal=0;
			init_match_mode();
			play_fx(PS_HALFTIMEWHISTLE,refs[0].x,refs[0].y);
			do_half_time_anim(0);
			do_halftime_menu();
			PlayCommentaryMessage(TI_HALFTIME);
			kickoff=TRUE;
			next_mins=45;

			if (practice)
				match_half=12;
#endif
		}
		else
		{
			if (match_time.min>=(90+injury_time) && match_half==1 && nothing_happening())
			{
// End of full time! (Not half mate...)
				last_goal=0;
				match_mode=SWAP_ENDS;
				init_match_mode();
				play_fx(PS_FULLTIMEWHISTLE,refs[0].x,refs[0].y);

				if (need_result && team_a_goals==team_b_goals)
				{
					do_extra_time_anim(0);
					do_extratime_menu();
					EUROmatch_info.extra=TRUE;
					kickoff=TRUE;
					next_mins=90;
				}
				else
				{
					do_full_time_anim(0);
					do_fulltime_menu();
					PlayCommentaryMessage(TI_FULLTIME);
					match_half=11;			// End game!
					next_mins=0;
#ifdef EURO96
					get_performance();
					xinfo=9;
					if (man_of_match)
						camera=18;
#endif
				}
			}
			else
			{
				if (need_result && match_time.min>=(90+15+injury_time)
				 	&& match_half==2 && nothing_happening())
// End of first half of extra time! (It's a game with more halves...)
				{
					last_goal=0;
					match_mode=SWAP_ENDS;
					init_match_mode();
					do_half_time_anim(0);
					do_halftime_menu();
					play_fx(PS_HALFTIMEWHISTLE,refs[0].x,refs[0].y);
					kickoff=TRUE;
					next_mins=105;
				}
				else
				{
					if (!penalty_game && need_result && match_time.min>=(90+30+injury_time)
					 	&& match_half==3 && nothing_happening())
// End of full extra time!
					{
						play_fx(PS_FULLTIMEWHISTLE,refs[0].x,refs[0].y);
						if (need_result && team_a_goals==team_b_goals)
						{
							EUROmatch_info.penalties=TRUE;
							penalty_game=TRUE;
							team_a_goals=0;
							team_b_goals=0;
							EUROmatch_info.Team_A_penalties=team_a_goals;
							EUROmatch_info.Team_B_penalties=team_b_goals;
							do_penalty_shootout_menu();
							next_mins=0;
						}
						else
						{
							last_goal=0;
							match_mode=SWAP_ENDS;
							init_match_mode();
							do_full_time_anim(0);
							if (EUROmatch_info.penalties)
							{
								EUROmatch_info.Team_A_penalties=team_a_goals;
								EUROmatch_info.Team_B_penalties=team_b_goals;
								do_final_score_menu();
							}
							else
								do_fulltime_menu();
							match_half=11;			// End game!
							PlayCommentaryMessage(TI_FULLTIME);
							next_mins=0;
#ifdef EURO96
							get_performance();
							xinfo=9;
							if (man_of_match)
								camera=18;
#endif
						}
					}
				}
			}
		}
	}
	}
}

/******************************************************************************
*****************************************************************************/

void setup_alarm()
{
	mf_fixed=FALSE;
	alarm=FALSE;					// Debug alarm on/off.
	watch=TRUE;
	stop_min=45;
	stop_sec=1;						// Debug alarm stop.
}

/******************************************************************************
*****************************************************************************/

void init_wind()
{
// Wind stuff...
	if (EUROmatch_info.wind)
	{
		init_wind_x=1;
		init_wind_y=0;
		wind_x=init_wind_x;
		wind_y=init_wind_y;
		init_wind_speed=EUROmatch_info.wind*30;   // (30,60,90)
		wind_speed=init_wind_speed;
		wind_var_ang=0;
		wind_d_trend=0;
		wind_s_trend=0;

		af_randomize();
		if (!(seed&3))
			wind_on=-TRUE;		// Variable wind!
		else
			wind_on=TRUE;

		wind_on=TRUE;
	}
	else
		wind_on=FALSE;
}

/******************************************************************************
*****************************************************************************/

// Get your grubby mits off these routines Andy!

void NetUserInit()
{	
	if (network_on)
	{
		// Network init users
		for (int i=0;i<network_on;i++)
		{
			int ctrl;
			if (i==wConsoleNode)
			{
				ctrl=convert_control(match_info.control_methods[0]);
//				ctrl=KEY1_CTRL;
//				calibrate_joy(0,&joy1_cnt_x,&joy1_cnt_y);
			}
			else
				ctrl=NET_CTRL;
			if (NetTeams[i]==0)
				if (Players[i]==1)
					add_team_user(TEAM_A,ctrl);
				else
					add_fixed_user(Players[i],ctrl);
			else
				if (Players[i]==1)
					add_team_user(TEAM_B,ctrl);
				else
					add_fixed_user(Players[i]+11,ctrl);
		}
	}
}

int otick;
void TimerInit()
{
	ftick=0;
	otick=tick=0;
	old_count=count;
/*
	if (!old_mf)
	{
		get_user_inputs();
		process_user_inputs();
		writeptr++;
	}
*/
	while(tick==otick);
}

/******************************************************************************
*****************************************************************************/

void reset_front()
{
	for (int i=0; i<sizeof(cam_array); i++)
	{
		if (camera==cam_array[i])
		{
			EUROmatch_info.camera=i;
			match_info.camera_toggle=i;
			break;
		}
	}
}

/******************************************************************************
*****************************************************************************/

int match(int argc, char **argv)
{
	int match_err=FALSE;

	initialise_vars();

#ifdef NET_GAME
// Pseudo net initialisation (not normally used)
	NetTest();
#endif

	if (network_on)
		old_mf=FALSE;
	else
		old_mf=TRUE;

	offside_on=EUROmatch_info.offside;

	if (match_info.CompetitionType==PRACTICE)
	{
		offside_on=FALSE;
	}

// Set up default camera...
	camera=cam_array[EUROmatch_info.camera];
	float cd=set_camera_dist;
	float ch=set_camera_height;
	change_cam(camera);
	set_camera_dist=cd;
	set_camera_height=ch;

// Set up audio...
	audio_version=(char)EUROmatch_info.audio;
// Vidi screen setup...
	vidi_wall_on=(char)EUROmatch_info.vidi;		// Vidi toggle!

// Debugging alarm...
	setup_alarm();
	
#ifndef FRONT_END
	time_factor=4;
//	debug=TRUE;											// Allows return keyboard to dos.
#else
	say_names=TRUE;
	if (network_on)
		time_factor=time_table[net_half];		// Real minutes duration.
	else
		time_factor=time_table[EUROmatch_info.time];	// Real minutes duration.

	debug=FALSE;										// Allows return keyboard to dos.
#endif

#ifdef ECTS
	time_factor=4;
#endif
//	debug=TRUE;
//	time_factor=10;

	init_wind();

	gravity=0.60;

	on_3d=TRUE;
	digital_joy1=FALSE;
	digital_joy2=FALSE;
	close_in_number=2;
	goal_kicker_a=1;
	goal_kicker_b=12;

	fkick_taker_a=0;
	fkick_taker_b=0;

	corn_kicker_a=0;
	corn_kicker_b=0;

//	_setvideomode(_MRES256COLOR);

	init_officials();

	init_match();
	
	if (!on_3d)
	{
		plot_buffer=TRUE;
		plot_cnta=0;
		plot_cntb=0;
		draw_pitch();

		pitch_markings();
		_setcolor(4);
		draw_buttons();
		_setcolor(50);
		_setplotaction(_GXOR);
		ShowMouse();
		MouseYlim(140,200-4);
		MouseXlim(160*2,(320-4)*2);
	}
	else
	{
		if (init_3d()<0)
			goto ERR_3D;

		MouseYlim(0,200);
		MouseXlim(0,320);
	}

	if (audio_version)
	{
		InitMatchAudio(rand_seed);
		if (!LoadPitchSamples())
			if (!LoadTeamSamples(setup.team_a,HOME_TEAM))
				if (!LoadTeamSamples(setup.team_b,AWAY_TEAM))
				{
					if (match_info.CompetitionType!=PRACTICE)
						LoadCommentarySamples();

					StartCrowd(HOME_TEAM);
					StartCrowd(AWAY_TEAM);
				}
	}

// Pseudo net user initialisation (not normally used)
	NetUserInit();
	users_left=num_of_users;

// Wait for everyone to get here, set timer & machine factor...
	readptr=writeptr=0;
	Network_Play_Ready();

	setscreen();
	if (audio_version)
		PlayWelcomeMessage();

// Various timing initialisations for network (DO NOT MOVE)
	TimerInit();
	mf_scale=omf_scale=0.5;
	MF=1;
	old_clock=clock();
	oldcnt=count;

// No Dos. keyboard chain!
	return_doskey=FALSE;

// Main program loop...

//	penalty_game=TRUE;

#ifdef NET_DEBUG
	if (network_on)
		opendebugfile();
#endif

	do_ref_menu();

#ifdef FRONT_END
	if (!num_of_users)
	{
// No Players... Rolling match...
		anykey=FALSE;
		rolling_clock=80*REAL_SPEED;
		demo_match=TRUE;
	}
#endif

//	out_mcball_coords();
//	old_mf=0;	
	while (in_game && !net_quit)
	{

/***********************************************/

		if (!old_mf)		// New logical loop
		{
			int ttick=tick;
			int tftick=ftick;
			int twriteptr=writeptr;

			if ((mf_fixed) || (!on_3d) || (!watch && alarm))
				ttick=tick=otick+1,tftick=ftick=0,mf_scale=omf_scale=0;

			mf_scale=(float)tftick/TIMER_SPEED;
			MF=(ttick+mf_scale)-(otick+omf_scale);
			omf_scale=mf_scale;
			log_factor=MF;						// Passed to 3d (Logic cycles/update)

			for (int i=readptr; i!=twriteptr; ++i&=511)
			{
				process_crowd_noise();
				if (audio_version)
 				{
					process_crowd_noise();
					UpdateCrowd(crowd_mood_a,team_a);
					UpdateCrowd(crowd_mood_b,team_b);
					UpdateCommentary();
				}

				wptr=writeptr;
				rptr=readptr;

				convert_inputs();
				readptr++;
				readptr&=511;
				if (!line_up)
				{
					do_logic();
				}
				else
				{
					line_up--;
					animate_players();
					if (!line_up)
					{
						match_mode=CENTRE_A;
						init_match_mode();
					}
				}
#ifdef EURO96
				process_state();
#else
				logic_cnt++;
#endif

#ifdef NET_DEBUG
				if (network_on)
				{
					writeplayerdata();
					writecontroldata(i);
				}
#endif

				new_update_coords();
				process_replay();
				watch_match_time();
			}
			otick=ttick;
		}
		else
		{
			if ((mf_fixed) || (!on_3d) || (!watch && alarm))
				MF=1;

			mf_scale+=MF;
			log_factor=MF;				// Passed to 3d(Logic cycles/update)

			for (float i=(mf_scale); (i>1); i=i-1)
			{
				process_crowd_noise();
				if (audio_version)
 				{
					process_crowd_noise();
					UpdateCrowd(crowd_mood_a,team_a);
					UpdateCrowd(crowd_mood_b,team_b);
					UpdateCommentary();
				}

				get_user_inputs();
				process_user_inputs();
				writeptr++;
				writeptr&=511;
				convert_inputs();
				readptr++;
				readptr&=511;
				if (!line_up)
				{
					do_logic();
				}
				else
				{
					line_up--;
					animate_players();
					if (!line_up)
					{
						match_mode=CENTRE_A;
						init_match_mode();
					}
				}

#ifdef EURO96
				process_state();
#else
				logic_cnt++;
#endif
				new_update_coords();
				process_replay();
				watch_match_time();
				mf_scale=mf_scale-1;
			}
		}

/***********************************************/

		if (!(!watch && alarm))
		{
			realtime_coords();
			process_pitch_sprs();

			if (keys[0x01] && !escape_pending)		// (Esc.)
			{
				escape_pending=TRUE;
				add_message("Quit Game Y or N",RED,TRUE);
			}

			if (on_3d)
				update_3d();
			else
				update_2d();

			if (on_3d)
			{
				if (old_mf)
				{
					frame_count();
				}
				else
					updates++;

				process_keys();
			}
		}

		if (demo_match && rolling_clock<=0)
			end_game=TRUE;
		if ((!on_3d) && (delay_cnt))
			delay(delay_cnt);

		if (!in_game && !on_3d)
		{
			editor_main();
			break;
		}

		if (escape_pending<0)
		{
// Quit Match...
			net_error=-1;
			break;
		}

		if (end_game)
			break;
	}

#ifdef NET_DEBUG
	if (network_on)
		closedebugfile();
#endif

// Remove network (if appropriate)
	Quit_Network_Play();

	if (audio_version)
	{
		StopAudio();
	}

	end3d();					// Goodbye Laurent's crappy heap of runny donkey shit code...
	freex(replay_tab);

#ifdef COVERDISK
	do{
	}while(keys[0x01]);

	display_endscr();
#endif

// Inform front end on times...
	if (end_game)
	{
// Played Full Match!!!
		EUROmatch_info.return_mins=-1;
	}
	else
	{
// Escaped from match!!!
		EUROmatch_info.return_mins=match_time.min;		
	}

	if (audio_version)
	{
		FreeCommentarySamples();
		FreeTeamSamples(AWAY_TEAM);
		FreeTeamSamples(HOME_TEAM);
		FreePitchSamples();
	}

// Give back front end enviroment stuff...
	reset_front();

// Give Dos. keyboard chain!
#ifdef MEG4
	release_key_int();
#endif
	return_doskey=TRUE;

	return(FALSE);		// No errors...


/************ ERRORS *************/

/*********/
ERR_3D:;
// Remove network (if appropriate)
	net_error=-1;
	Quit_Network_Play();

	match_err+=256;
	goto RETURN_ERR;

/*********/

RETURN_ERR:;
	return(match_err);
}


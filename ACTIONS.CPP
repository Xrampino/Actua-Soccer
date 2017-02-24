/******************************************************************************
*******************************************************************************

Player action routines...

******************************************************************************
*****************************************************************************/

#include "global.h"
#include "3deng.h"
#include "data.h"
#include "ball.dta"

#include "defines.h"
#include "externs.h"
#include "audio.h"							// Kev's audio calls.
#include "front.h"
#include "eurofrnt\euro_int.h"

extern team_info game_data[];
extern setup_info setup;
extern stad_info stadlist[];
extern match_data match_info;

extern short get_there_time(int p_num,float x,float y);

/******************************************************************************
*****************************************************************************/

// Converts Statistical speed to actual game speed (takes possession of ball into account!)...

float full_spd(match_player *p)
{
	float a;

	if (p->int_move==I_CELEB)
		a=MC_CELEB_SPD;
	else
		a=((float)pitch_len)/((18.-(((float)(p->tm_rate)/64)*4))*20);

	return(a);
}

/******************************************************************************
*****************************************************************************/

// Converts Statistical speed to actual game speed (takes possession of ball into account!)...

float actual_spd(match_player *p)
{
	float a;

	if (p->int_move==I_CELEB)
		a=MC_CELEB_SPD;
	else
		if (p->int_move==I_INTERCEPT && p->int_cnt)
// Chasing Ball (must run)...
			a=((float)pitch_len)/((18.-(((float)(p->tm_rate)/64)*4))*20);
		else
			if (p->go_step)
// Side stepping...
				a=((float)pitch_len)/((24.-(((float)(p->tm_rate)/64)*4))*20);
			else
				if (ball_poss==p->tm_player)
// Avg runs pitch length in 14 secs.
// Top run in 10 secs.
				{
					if (ball_in_hands && (p->tm_player==KP_A || p->tm_player==KP_B))
// Keeper with ball in his hands...(slow)
						a=((float)pitch_len)/((28.-(((float)(p->tm_rate)/64)*4))*20);
					else
						a=((float)pitch_len)/((20.-(((float)(p->tm_rate)/64)*4))*20);
				}
				else
// Avg runs pitch length in 16 secs.
// Top run in 12 secs.
					if (user_controlled && burst_timer[user_controlled-1]>0)
						a=((float)pitch_len)/(((18.-(float)burst_timer[user_controlled-1]/5)-(((float)(p->tm_rate)/64)*4))*20);
					else
						a=((float)pitch_len)/((18.-(((float)(p->tm_rate)/64)*4))*20);

	return(a);
}

/******************************************************************************
*****************************************************************************/

void init_officials()
{
	refs[0].x=cntspot_x;
	refs[1].x=cntspot_x;
	refs[2].x=cntspot_x;
	refs[0].goto_x=cntspot_x;
	refs[1].goto_x=cntspot_x;
	refs[2].goto_x=cntspot_x;

	refs[0].y=cntspot_y;
	refs[0].goto_y=cntspot_y;
	refs[1].y=-(prat*2);
	refs[1].goto_y=-(prat*2);
	refs[2].y=pitch_wid+(prat*2);
	refs[2].goto_y=pitch_wid+(prat*2);
	refs[0].z=0;
	refs[1].z=0;
	refs[2].z=0;
	refs[0].dir_x=0;
	refs[1].dir_x=0;
	refs[2].dir_x=0;
	refs[0].dir_y=1;
	refs[1].dir_y=1;
	refs[2].dir_y=-1;
	refs[0].anim=MC_PLEAD;
	refs[1].anim=MC_STAND;
	refs[2].anim=MC_STAND;
	refs[0].fstep=MC_PLEAD_FS;
	refs[1].fstep=MC_STAND_FS;
	refs[2].fstep=MC_STAND_FS;
	refs[0].frm=0.6;
	refs[1].frm=0;
	refs[2].frm=0;
	refs[0].act=0;
	refs[1].act=0;
	refs[2].act=0;

	refs[0].target=0;
	refs[1].target=0;
	refs[2].target=0;

	refs[0].go=0;
	refs[1].go=0;
	refs[2].go=0;

	refs[0].newanim=TRUE;
	refs[1].newanim=TRUE;
	refs[2].newanim=TRUE;

}

/******************************************************************************
*****************************************************************************/

void check_practice()
{
	if (match_info.CompetitionType==PRACTICE)
		practice=1;
	else
		practice=0;

	switch(practice)
	{
		case(0):
			team_a_on=TRUE;
			team_b_on=TRUE;
			break;

		case(1):
			team_a_on=TRUE;
			team_b_on=FALSE;
			break;

		case(-1):
			team_a_on=FALSE;
			team_b_on=TRUE;
			break;
	}
}

/******************************************************************************
*****************************************************************************/

void init_team()
{
	int i;

	check_practice();

	for (i=1; i<=22; i++)
	{
		init_player_stats(i);
		if (i==2)
		{
			teams[i-1].tm_rate=120;
			teams[i-1].tm_pow=120;
			teams[i-1].tm_cont=120;
			teams[i-1].tm_flair=120;
			teams[i-1].tm_vis=120;
			teams[i-1].tm_ac=120;
			teams[i-1].tm_stam=120;
			teams[i-1].tm_disc=120;
		}
	}

	for (i=0; i<(players/2); i++)
	{
		if (team_a_on)
		{
			teams[i].tm_player=i+1;
			teams[i].tm_x=cntspot_x-prat*2;
			teams[i].tm_y=(cntspot_y+10*24)-(i*24);
			teams[i].tm_z=0;

			teams[i].tm_xdis=1;
			teams[i].tm_ydis=0;
			teams[i].tm_zdis=0;

			teams[i].mface=0;
			teams[i].tm_dist=50;
			teams[i].tm_pos=1;
			teams[i].tm_limbo=0;

			teams[i].guy_on=TRUE;

			teams[i].control=0;
			teams[i].tm_srng=0;
			teams[i].tm_off=0;
			teams[i].tm_stopped=0;
			teams[i].tm_trap=0;
			teams[i].special=0;
			teams[i].tm_strike=0;
			teams[i].tm_stime=0;
			teams[i].tm_ftime=0;
			teams[i].ball_state=0;
			teams[i].tm_fpass_type=0;
			teams[i].tm_fpass_to=0;
			teams[i].draw_me=TRUE;

			teams[i].shirt=i+1;

			teams[i].tm_book=0;
			teams[i].tm_fouls=0;
			teams[i].tm_tacks=0;
			teams[i].tm_twon=0;
			teams[i].tm_shots=0;
			teams[i].tm_saved=0;
			teams[i].tm_goals=0;
			teams[i].tm_pass=0;
			teams[i].tm_pwon=0;
			teams[i].tm_inj=0;
			teams[i].tm_posst=0;
			teams[i].tm_work=0;
			teams[i].tm_kpsaves=0;
			teams[i].tm_ogs=0;
			teams[i].tm_time=0;
			
			teams[i].turn_dir=0;
			teams[i].face_dir=0;
			teams[i].dir_mode=0;
			teams[i].tm_frm=0;
			teams[i].tm_fstep=MC_STAND_FS;			// For intitialisation purposes.
			teams[i].tm_anim=MC_STAND;
			teams[i].tm_hcol=0;
			teams[i].tm_htype=0;
			teams[i].tm_mcspd=(float)(teams[i].tm_flair+teams[i].tm_rate)/128;
			teams[i].ls_anim=0;
			teams[i].ls_frm=0;
			teams[i].contact=-1;
			teams[i].tm_newanim=1;
			teams[i].tm_barge=0;

			teams[i].tm_act=0;
			teams[i].tm_poss=0;
			teams[i].tm_wall=0;
			teams[i].tm_leave=0;
			teams[i].tm_mark=0;
			teams[i].go_dist=0;
			teams[i].go_cnt=0;
			teams[i].go_txdis=0;
			teams[i].go_tydis=0;
			teams[i].go_tx=teams[i].tm_x;
			teams[i].go_ty=teams[i].tm_y;
			teams[i].go_xoff=0;
			teams[i].go_yoff=0;
			teams[i].tm_jump=PLAYER_HEIGHT+6+(teams[i].tm_pow/10);
			teams[i].go_stop=0;
			teams[i].go_step=0;
			teams[i].tm_notme=0;

			teams[i].int_move=0;
			teams[i].int_cnt=0;
			teams[i].mess_num=0;
			teams[i].mess_cnt=0;
			teams[i].tm_comm=0;
			teams[i].tm_ccnt=0;
		}
		else
			teams[i].guy_on=FALSE;
	}
	for (i=11; i<players; i++)
	{
		if (team_b_on || i==11)
//		if (team_b_on)
		{

			teams[i].tm_player=i+1;
			teams[i].tm_x=cntspot_x+prat*2;
			teams[i].tm_y=(cntspot_y+10*24)-((i-11)*24);
			teams[i].tm_z=0;

			teams[i].tm_xdis=-1;
			teams[i].tm_ydis=0;
			teams[i].tm_zdis=0;

			teams[i].mface=0;
			teams[i].tm_dist=50;
			teams[i].tm_pos=1;
			teams[i].tm_limbo=0;

			teams[i].guy_on=TRUE;

			teams[i].control=0;
			teams[i].tm_srng=0;
			teams[i].tm_off=0;
			teams[i].tm_stopped=0;
			teams[i].tm_trap=0;
			teams[i].special=0;
			teams[i].tm_strike=0;
			teams[i].tm_stime=0;
			teams[i].tm_ftime=0;
			teams[i].ball_state=0;
			teams[i].tm_fpass_type=0;
			teams[i].tm_fpass_to=0;
			teams[i].draw_me=TRUE;

			teams[i].shirt=i-10;

			teams[i].tm_book=0;
			teams[i].tm_fouls=0;
			teams[i].tm_tacks=0;
			teams[i].tm_twon=0;
			teams[i].tm_shots=0;
			teams[i].tm_saved=0;
			teams[i].tm_goals=0;
			teams[i].tm_pass=0;
			teams[i].tm_pwon=0;
			teams[i].tm_inj=0;
			teams[i].tm_posst=0;
			
			teams[i].turn_dir=0;
			teams[i].face_dir=0;
			teams[i].dir_mode=0;
			teams[i].tm_frm=0;
			teams[i].tm_fstep=MC_STAND_FS;			// For intitialisation purposes.
			teams[i].tm_anim=MC_STAND;
			teams[i].tm_hcol=0;
			teams[i].tm_htype=0;
			teams[i].tm_mcspd=(float)(teams[i].tm_flair+teams[i].tm_rate)/128;
			teams[i].ls_anim=0;
			teams[i].ls_frm=0;
			teams[i].contact=-1;
			teams[i].tm_newanim=1;
			teams[i].tm_barge=0;

			teams[i].tm_act=0;
			teams[i].tm_poss=0;
			teams[i].tm_wall=0;
			teams[i].tm_leave=0;
			teams[i].tm_mark=0;
			teams[i].go_dist=0;
			teams[i].go_cnt=0;
			teams[i].go_txdis=0;
			teams[i].go_tydis=0;
			teams[i].go_tx=teams[i].tm_x;
			teams[i].go_ty=teams[i].tm_y;
			teams[i].go_xoff=0;
			teams[i].go_yoff=0;
			teams[i].tm_jump=PLAYER_HEIGHT+6+(teams[i].tm_pow/10);
			teams[i].go_stop=0;
			teams[i].go_step=0;
			teams[i].tm_notme=0;

			teams[i].int_move=0;
			teams[i].int_cnt=0;
			teams[i].mess_num=0;
			teams[i].mess_cnt=0;
			teams[i].tm_comm=0;
			teams[i].tm_ccnt=0;

		}
		else
			teams[i].guy_on=FALSE;
	}
	reset_all_ideas();
	interceptor_a=0;
	interceptor_b=0;
}

/******************************************************************************
*****************************************************************************/

void taker_pass_f(float xp,float yp)
{
	short t;
	float dif,x,y,d,nx,ny;

	t=(setp_taker<12 ? 10:21);	// team-mates!
	pass_type=0;

	for (short i=t; i>t-11; i--)
	{
		if (setp_taker!=i+1)
// Not man on ball!
		{
			if ((teams[i].tm_act<=TURN_ACT) && (teams[i].guy_on>0))
// Not Busy!
			{
				x=teams[i].tm_x-ballx;
				y=teams[i].tm_y-bally;
				d=calc_dist(x,y);

				dif=((x*xp)+(y*yp))/d;
				if (dif>FACING_ANGLE)
				{
					pass_type=in_kicking_range(&teams[setp_taker-1],x,y);
				}

				if (pass_type)
				{
					make_pass(&teams[setp_taker-1],i+1,FALSE);
					ready_set_kick();
					break;
				}
			}
		}
	}

	if (!pass_type)
	{
		setp_kick_x=xp;
		setp_kick_y=yp;
		must_pass=10;
		nx=(xp*teams[setp_taker-1].tm_xdis)+(yp*teams[setp_taker-1].tm_ydis);
		ny=(yp*teams[setp_taker-1].tm_xdis)-(xp*teams[setp_taker-1].tm_ydis);
		pass_type=(1+get_dir(nx,ny));
		make_pass(&teams[setp_taker-1],0,FALSE);
		ready_set_kick();
	}
}

/******************************************************************************
*****************************************************************************/

void taker_pass_h(float xp,float yp)
{
	chip_pass=TRUE;
	short t;
	float dif,x,y,d,nx,ny;

	t=(setp_taker<12 ? 10:21);	// team-mates!
	pass_type=0;

	for (short i=t; i>t-11; i--)
	{
		if (setp_taker!=i+1)
// Not man on ball!
		{
			if ((teams[i].tm_act<=TURN_ACT) && (teams[i].guy_on>0))
// Not Busy!
			{
				x=teams[i].tm_x-ballx;
				y=teams[i].tm_y-bally;
				d=calc_dist(x,y);

				dif=((x*xp)+(y*yp))/d;
				if (dif>FACING_ANGLE)
				{
					pass_type=in_kicking_range(&teams[setp_taker-1],x,y);
					if (pass_type!=5 && pass_type!=-1)
						pass_type=0;
					else
						pass_type=-1;
				}

				if (pass_type)
				{
					make_pass(&teams[setp_taker-1],i+1,FALSE);
					ready_set_kick();
					break;
				}
			}
		}
	}
	if (!pass_type)
	{
		setp_kick_x=teams[setp_taker-1].tm_xdis;
		setp_kick_y=teams[setp_taker-1].tm_ydis;
		must_pass=TRUE;
		pass_type=-1;
		make_pass(&teams[setp_taker-1],0,FALSE);
		ready_set_kick();
	}
}

/******************************************************************************
*****************************************************************************/

void taker_tee_up(float x,float y)
{
	taker_pass_f(x,y);
	must_shoot=TRUE;
	must_punt=TRUE;
}

/******************************************************************************
*****************************************************************************/

void taker_kick(float x,float y)
{
	if (teams[setp_taker-1].tm_srng)
	{
// In shooting range...
		if (spec_kick_type==SPACT_DRIVE)
			drive_shot=TRUE;

		pass_type=-1;
		make_shoot(&teams[setp_taker-1]);
		ready_set_kick();
	}
	else
	{
		make_punt(&teams[setp_taker-1]);
		ready_set_kick();
	}
}

/******************************************************************************
*****************************************************************************/

void taker_chip(float x,float y)
{
	setp_kick_x=teams[setp_taker-1].tm_xdis;
	setp_kick_y=teams[setp_taker-1].tm_ydis;
	chip_pass=TRUE;
	must_pass=TRUE;
	pass_type=-1;
	make_pass(&teams[setp_taker-1],0,FALSE);
	ready_set_kick();
}

/******************************************************************************
*****************************************************************************/

void taker_grnd(float x,float y)
{
	setp_kick_x=teams[setp_taker-1].tm_xdis;
	setp_kick_y=teams[setp_taker-1].tm_ydis;
	chip_pass=FALSE;
	must_pass=TRUE;
	pass_type=5;
	make_pass(&teams[setp_taker-1],0,FALSE);
	ready_set_kick();
}

/******************************************************************************
*****************************************************************************/

#ifdef SUPPORT_LP

#define ROTATE_ANG (0.16)

void rotate_lp(match_player *player)
{
	float ox=player->tm_xdis;
	float oy=player->tm_ydis;

	float rot=0;

	short fire=users_dir[user_controlled-1].f;

	if (!(fire&LP_L && fire&LP_R))
	{
// Not both shoulder buttons...
		if (fire&LP_L)
			rot=-ROTATE_ANG;

		if (fire&LP_R)
			rot=ROTATE_ANG;

		player->tm_xdis=(ox*cos(rot))-(oy*sin(rot));
		player->tm_ydis=(oy*cos(rot))+(ox*sin(rot));
		player->tm_x=ballx-(player->tm_xdis*8);
		player->tm_y=bally-(player->tm_ydis*8);
	}
}
#endif

/******************************************************************************
*****************************************************************************/

void rotate_around_ball(match_player *player)
{
	if (um)
	{
		float x=ballx-(ux*8);
		float y=bally-(uy*8);
		player->tm_x=x;
		player->tm_y=y;
		player->tm_xdis=ux;
		player->tm_ydis=uy;
	}
}

/******************************************************************************
*****************************************************************************/

void taker_nkick()
{
	newk_shot=TRUE;
	teams[setp_taker-1].tm_xdis=setp_kick_x;
	teams[setp_taker-1].tm_ydis=setp_kick_y;
	pass_type=-1;
	make_shoot(&teams[setp_taker-1]);
	ready_set_kick();
}

/******************************************************************************
*****************************************************************************/

void draw_tracker(short mp,float x,float y)
{
	static float fract=0;
	float bspeed=get_power();
	ballxdis=x*bspeed;
	ballydis=y*bspeed;
	ballzdis=get_traj();
	ball_inair=TRUE;
	ball_poss=FALSE;

	predict_ball();
	ballxdis=0;
	ballydis=0;
	ballzdis=0;
	ball_inair=FALSE;
	ball_poss=setp_taker;

	float xp,yp,zp;

// Draw tracker...
	for (short i=0; (i<first_bounce || i<mp); i++)
	{
// Marker...
		xp=ball_pred_tab[i][0];
		yp=ball_pred_tab[i][1];
		zp=ball_pred_tab[i][2];
		xp=xp+(fract*(ball_pred_tab[i+1][0]-xp));
		yp=yp+(fract*(ball_pred_tab[i+1][1]-yp));
		zp=zp+(fract*(ball_pred_tab[i+1][2]-zp));

// Dot...
		add_pitch_sprite(xp,yp,zp,0);

// Shadow...
		add_pitch_sprite(xp,yp,0,1);
	}

	fract+=0.2;
	if (fract>=1)
		fract=0;
}

/******************************************************************************
*****************************************************************************/

void init_runup_act(match_player *player)
{
	init_run_act(player,ballx,bally,TRUE);
	player->int_move=I_RUNUP;
	player->int_cnt=player->go_cnt;
	if (player->int_cnt>0)
		player->int_cnt--;

}

/******************************************************************************
*****************************************************************************/

void user_runup(match_player *player)
{
	if (!player->int_cnt--)
	{
// End of runup...
		spec_kick_type=SPACT_NEWK;
		taker_nkick();
	}
	else
	{
		go_forward(player);
	}
}

/******************************************************************************
*****************************************************************************/

#define ROT_SPEED (0.05)

void new_user_spec_kick(match_player *player)
{
	if (player->int_move==I_RUNUP)
	{
		user_runup(player);
	}
	else
	{
		float x=setp_kick_x;
		float y=setp_kick_y;

// Player's maximum power of shot...
		short max_pow=(player->tm_pow/6)+8;

		float xd;
		short yd;

// Read unvectored user controls...
		if (users_dir[user_controlled-1].f&8)
			xd=-ROT_SPEED*((max_pow)/(setp_power+6));
		else
			if (users_dir[user_controlled-1].f&4)
				xd=ROT_SPEED*((max_pow)/(setp_power+6));
			else
				xd=0;

		if (users_dir[user_controlled-1].f&32)
			yd=1;
		else
			if (users_dir[user_controlled-1].f&16)
				yd=-1;
			else
				yd=0;

		if (!uf2)
		{
// Not trying pass...

// Rotate player based on (left,right action)...
			setp_kick_x=(x*cos(xd))-(y*sin(xd));
			setp_kick_y=(y*cos(xd))+(x*sin(xd));
			float d=calc_dist(setp_kick_x,setp_kick_y);
			setp_kick_x=setp_kick_x/d;
			setp_kick_y=setp_kick_y/d;

// Adjust run-up based on (up,down action)...
			setp_power+=yd;
			if (setp_power<0)
				setp_power=0;
			else
				if (setp_power>max_pow)
					setp_power=max_pow;
		}

// Where should he be...
		setp_x=ballx-(setp_kick_x*(setp_power+2)*2);
		setp_y=bally-(setp_kick_y*(setp_power+2)*2);

		init_run_act(player,setp_x,setp_y,TRUE);
		if (player->tm_act==RUN_ACT)
			go_forward(player);
		else
		{
			player->tm_x=setp_x;
			player->tm_y=setp_y;
			player->tm_xdis=setp_kick_x;
			player->tm_ydis=setp_kick_y;
		}

		if (uf1)
		{
// Shoot button held...
			if (++setp_hgt>30)
				setp_hgt--;
		}
		else
		{
			if (setp_hgt)
// Shoot button has been released...
				init_runup_act(player);

			if (uf2)
			{
				if (setp_power || calc_dist(player->tm_x-setp_x,player->tm_y-setp_y)>1)
					setp_power=0;
				else
				{
// At ball... Ready to pass...
					if (!f2_down)
					{
						f2_down=1;
					}
				}
			}
			else
			{
				if (f2_down)
				{
// uf2 released...
					if (um)
					{
// (uf2 + d)...
						if (uf1)
							spec_kick_type=SPACT_TEE_UP;	// Tee up for shot or punt!
						else
							spec_kick_type=SPACT_DPASS;	// Disguised Pass!
					}
					else
						spec_kick_type=SPACT_FPASS;	// Pass to feet!
				}
			}
		}
	
		if (!f2_down && setp_power)
			draw_tracker(max_pow/2,setp_kick_x,setp_kick_y);

		switch(spec_kick_type)
		{
			case(SPACT_FPASS):
				taker_pass_f(player->tm_xdis,player->tm_ydis);
				break;

			case(SPACT_HPASS):
				taker_pass_h(player->tm_xdis,player->tm_ydis);
				break;

			case(SPACT_TEE_UP):
				taker_tee_up(users_dir[user_controlled-1].x,users_dir[user_controlled-1].y);
				break;

			case(SPACT_DPASS):
				taker_pass_f(users_dir[user_controlled-1].x,users_dir[user_controlled-1].y);
				break;

			case(SPACT_GRND):
				taker_grnd(player->tm_xdis,player->tm_ydis);
				break;

			case(SPACT_CHIP):
				taker_chip(player->tm_xdis,player->tm_ydis);
				break;

			case(SPACT_DRIVE):
				taker_kick(player->tm_xdis,player->tm_ydis);
				break;

			case(SPACT_KICK):
				taker_kick(player->tm_xdis,player->tm_ydis);
				break;

			case(SPACT_NEWK):
				taker_nkick();
				break;
		}
	}
}

/******************************************************************************
*****************************************************************************/

void user_pen_kick(match_player *player,char user_guy)
{
	float ydif,racc;

	if (player->int_move==I_RUNUP)
	{
		user_runup(player);
	}
	else
	{
		if (player->tm_player<12)
			setp_bxd=pitch_len;
		else
			setp_bxd=0;

		float x,y,d;
		float acc=(128.-player->tm_ac)/4;
		float skill=(160.-player->tm_flair)/16;
		setp_power=(player->tm_pow/8)+10;

		if (f2_down<0)
		{
			setp_byd-=skill;
			if (setp_byd<(top_post_y-acc))
				f2_down=1;
		}
		else
		{
			setp_byd+=skill;
			if (setp_byd>(bot_post_y+acc))
				f2_down=-1;
		}

// Derive vector from point on goal-line...
		x=setp_bxd-ballx;
		y=setp_byd-bally;
		d=calc_dist(x,y);
		setp_kick_x=x/d;
		setp_kick_y=y/d;

		if (!user_guy)
		{
// Computer intelligence...
			if (!f1_down)
			{
// Not started kick yet...
				af_randomize();
				if (seed>(92+((128-player->tm_flair)/8)))
				{
// Decides to kick...
					af_randomize();
					if (seed>(player->tm_flair/2))
					{
// Aim low... (not very spectacular)
						setp_bzd=4;
					}
					else
					{
// Aim High... (Spectacular attempt)
						setp_bzd=16;
					}

					if (f2_down<0)
					{
// Targeter moving upward...
						ydif=setp_byd-(top_post_y+(ball_diam*2)+skill);
					}
					else
					{
// Targeter moving downward...
						ydif=(bot_post_y-(ball_diam*2)-skill)-setp_byd;
					}

					if (ABS((ydif/skill)-setp_bzd)<1)
					{
						uf1=TRUE;
						af_randomize();
						setp_bzd+=((acc-(acc*seed/64)))/2;
						if (setp_bzd<1)
							setp_bzd=1;
					}
				}
			}
			else
			{
				if (f1_down>(setp_bzd-1))
					uf1=FALSE;
				else
					uf1=TRUE;
			}
		}

// Under user control...
		if (uf1)
		{
			if ((++f1_down)>30)
			{
				f1_down=30;
			}
			setp_hgt=f1_down;
		}
		else
		{
			if (f1_down)
			{
				init_runup_act(player);
				penalty_shot=TRUE;
			}
		}
		draw_tracker(setp_power/2,setp_kick_x,setp_kick_y);
	}
}

/******************************************************************************
*****************************************************************************/

void user_spec_kick(match_player *player)
{
	setp_taker=player->tm_player;
	if (uf1 && uf2)
	{
// Both buttons held...
		if (um && !f1_down && !f2_down)
		{
// Both pressed together...(take F1!)
			spec_kick_type=SPACT_DRIVE;		// Driving shot or punt!
		}
	}
	else
	{
		if (f2_down && f1_down)
		{
// Both buttons held...
			if (!uf1)
			{
// Both buttons were held but f1 released...
				if (um)
				{
// Direction selected...
					spec_kick_type=SPACT_TEE_UP;	// Tee up for shot or punt!
				}
				else
				{
// No Direction...
					spec_kick_type=SPACT_CHIP;		// Power Chip into air!
				}
			}
			else
			{
				if (!uf2)
				{
// Both buttons were held but f2 released...
					if (um)
					{
// Direction selected...
						spec_kick_type=SPACT_DPASS;	// Disguised pass!
					}
					else
					{
// No Direction...
						spec_kick_type=SPACT_HPASS;	// Pass to head!
					}
				}
			}
		}
		else
		{
			if (f1_down)
			{
// F1 held down only...
				if (!uf1)
				{
// F1 now released...
					if (um)
					{
// Direction selected...
						spec_kick_type=SPACT_TEE_UP;	// Tee up for shot or punt!
					}
					else
					{
// No Direction...
	  					spec_kick_type=SPACT_DRIVE;	// Driving shot or punt(no swerve)!
					}
				}
			}
			else
			{
				if (f2_down)
				{
// F2 held down only...
					if (!uf2)
					{
// F2 now released...
						if (um)
						{
// Direction selected...
							spec_kick_type=SPACT_DPASS;	// Disguised Pass!
						}
						else
						{
// No Direction...
							spec_kick_type=SPACT_GRND;		// Power kick along ground!
						}
					}
				}
				else
				{
// No buttons held...
					if (uf1 && um)
					{
// F1 pressed initialy with dir...
						spec_kick_type=SPACT_KICK;		// Shoot or punt!
					}
					else
					{
						if (uf2 && um)
						{
// F2 pressed initialy with dir...
							spec_kick_type=SPACT_FPASS;	// Pass to feet!
						}
					}
				}
			}
		}
	}

	if (!um)
	{
		if (uf2)
		{
			if (!f2_down && f1_down)
				f2_down=1;

			if (++f2_down>30)
				f2_down=30;
		}

		if (uf1)
		{
			if (!f1_down && f2_down)
				f2_down=1;

			if (++f1_down>30)
				f1_down=30;
		}

		if (f1_down)
			setp_power=f1_down;
		else
			setp_power=f2_down;

		setp_bxd=(player->tm_xdis*(setp_power+4)*(128+teams[ball_poss-1].tm_pow))*.5/256;
		setp_byd=(player->tm_ydis*(setp_power+4)*(128+teams[ball_poss-1].tm_pow))*.5/256;
		setp_bzd=(setp_power/4)+4;

#ifdef SUPPORT_LP
		if (!uf1 && !uf2 && !f1_down && !f2_down && set_piece_on)
			rotate_lp(player);
#endif

	}
	else
	{
		if (!uf1 && !uf2 && !f1_down && !f2_down && set_piece_on)
			rotate_around_ball(player);
	}

	switch(spec_kick_type)
	{
		case(SPACT_FPASS):
			taker_pass_f(player->tm_xdis,player->tm_ydis);
			break;

		case(SPACT_HPASS):
			taker_pass_h(player->tm_xdis,player->tm_ydis);
			break;

		case(SPACT_TEE_UP):
			taker_tee_up(users_dir[user_controlled-1].x,users_dir[user_controlled-1].y);
			break;

		case(SPACT_DPASS):
			taker_pass_f(users_dir[user_controlled-1].x,users_dir[user_controlled-1].y);
			break;

		case(SPACT_GRND):
			taker_grnd(player->tm_xdis,player->tm_ydis);
			break;

		case(SPACT_CHIP):
			taker_chip(player->tm_xdis,player->tm_ydis);
			break;

		case(SPACT_DRIVE):
			taker_kick(player->tm_xdis,player->tm_ydis);
			break;

		case(SPACT_KICK):
			taker_kick(player->tm_xdis,player->tm_ydis);
			break;
	}
}

/******************************************************************************
*****************************************************************************/

void user_limited_kick(match_player *player)
{
// Limited for penalty...

	setp_taker=player->tm_player;

	if (um)
	{
// Directional...
		if (uf1)
		{
			spec_kick_type=SPACT_KICK;			// Shoot!
		}
	}
	else
	{
		if (uf1)
		{
			spec_kick_type=SPACT_DRIVE;		// Driving shot!
		}
	}

	setp_power=(player->tm_pow/6)+8;
	setp_bxd=(player->tm_xdis*(setp_power+4)*(128+teams[ball_poss-1].tm_pow))*.5/256;
	setp_byd=(player->tm_ydis*(setp_power+4)*(128+teams[ball_poss-1].tm_pow))*.5/256;
	setp_bzd=(setp_power/4)+4;

	if (!uf1 && !f1_down && set_piece_on)
		rotate_around_ball(player);

	switch(spec_kick_type)
	{
		case(SPACT_DRIVE):
			penalty_shot=TRUE;
			taker_kick(player->tm_xdis,player->tm_ydis);
			break;

		case(SPACT_KICK):
			penalty_shot=TRUE;
			taker_kick(player->tm_xdis,player->tm_ydis);
			break;
	}
}

/******************************************************************************
*****************************************************************************/

void comp_set_piece(match_player *player)
{
	if (refs[0].act==2)
		user_pen_kick(player,FALSE);
}

/******************************************************************************
*****************************************************************************/

void user_set_piece(match_player *player)
{
	user_conts(&teams[player_num-1]);

#ifdef STOP_TIME_WASTING
	if (ref_wait<0)
	{
// Force strike on ball (Time-up)...
		uf1=TRUE;
		uf2=TRUE;
		um=TRUE;
		ux=player->tm_xdis;
		uy=player->tm_ydis;
	}
#endif

	if (ref_wait)
	{

		switch(match_mode)
		{
			case(IF_KICK_A):
			case(IF_KICK_B):
			case(DF_KICK_A):
			case(DF_KICK_B):
			case(CORNER_TL):
			case(CORNER_BL):
			case(CORNER_TR):
			case(CORNER_BR):
			case(GOAL_KICK_TL):
			case(GOAL_KICK_BL):
			case(GOAL_KICK_TR):
			case(GOAL_KICK_BR):
			case(CENTRE_A):
			case(CENTRE_B):

#ifndef EURO96
				user_spec_kick(player);
#else
				new_user_spec_kick(player);
#endif
				break;

			case(PEN_KICK_A):
			case(PEN_KICK_B):
#ifdef EURO96
				user_pen_kick(player,TRUE);
#else
				user_limited_kick(player);
#endif
				break;	}
	}
}

/******************************************************************************
*****************************************************************************/

void init_throw_act(match_player *player)
{
	last_touch=player->tm_player;
	player->tm_anim=MC_THROWL;
	player->tm_newanim=TRUE;
	player->tm_frm=0;
	player->tm_fstep=MC_THROWL_FS;

	player->dir_mode=2;
	player->go_txdis=0;
	player->go_tydis=0;
	player->tm_act=THROW_ACT;
	player->tm_xdis=0;
	if (player->tm_player<12)
		player->turn_dir=1;
	else
		player->turn_dir=-1;

	if (bally<cntspot_y)
		player->tm_ydis=1;
	else
		player->tm_ydis=-1;
	throw_cnt=90;

	support_me=TRUE;
}

/******************************************************************************
*****************************************************************************/

void init_get_up(match_player *player,float fs)
{
	player->int_cnt=1+(1.0/fs);
	player->int_move=I_GET_UP;
	player->dir_mode=2;			// Don't turn!
}

/******************************************************************************
*****************************************************************************/

void init_pickup_act(match_player *player)
{
	reset_ideas(player);
	player->tm_act=PICKUP_ACT;
	init_anim(player,MC_PICKBALL);
	player->int_move=I_GET_UP;			// Look like he is busy!
	player->int_cnt=1/MC_PICKBALL_FS;
}

/******************************************************************************
*****************************************************************************/

void pickup_action(match_player *player)
{	
	if (!player->int_cnt)
	{
// end of animation...
		if (player->tm_anim==MC_PICKBALL)
		{
			init_anim(player,MC_STANDB);
			ball_in_hands=TRUE;
			if (player->tm_player==KP_A || player->tm_player==KP_B)
			{
				player->dir_mode=2;
				init_kphold_act(player);
			}
		}
	}
}

/******************************************************************************
*****************************************************************************/

void init_taunt_act(match_player *player)
{
// Stationary taunt...

	player->tm_act=CELEB_ACT;
	player->go_txdis=0;
	player->go_tydis=0;
	player->dir_mode=2;

	if (player->tm_player==goal_scorer)
	{
		scorer_running=FALSE;
// Choose Taunt...
		af_randomize();
		if (seed&2)
		{
// Knee slide...
			init_anim(player,MC_KNEE);
			player->go_txdis=player->tm_xdis*3;
			player->go_tydis=player->tm_ydis*3;
			player->go_cnt=1/MC_KNEE_FS;
		}
		else
		{
// Taunt...
			af_randomize();
			short r=0;
			if (user_scorer)
			{
// User selects celebration...
				while(((users_dir[user_scorer-1].f)>>2)&(1<<r));
				r--;
			}
			else
// Computer is random...
				r=rand_range(4);

			switch(rand_range(4))
			{
				case(0):
					init_anim(player,MC_REEVES);
					break;

				case(1):
					init_anim(player,MC_BABY);
					break;

				case(2):
					init_anim(player,MC_PUMP);
					break;

				case(3):
					init_anim(player,MC_MILLER);
					break;
			}
		}
	}
	else
	{
// Do whatever goal scorer is doing...
		if (teams[goal_scorer-1].tm_anim==MC_KNEE || teams[goal_scorer-1].tm_anim==MC_DUCK)
		{
			init_anim(player,MC_KNEE);
			player->go_txdis=player->tm_xdis*3;
			player->go_tydis=player->tm_ydis*3;
			player->go_cnt=1/MC_KNEE_FS;
		}
		else
			if (teams[goal_scorer-1].tm_anim>=MC_KNEE && teams[goal_scorer-1].tm_anim<=MC_REEVES)
			{
				init_anim(player,teams[goal_scorer-1].tm_anim);
				if (player->tm_anim==MC_MOON)
				{
					player->go_txdis=-player->tm_xdis;
					player->go_tydis=-player->tm_ydis;
				}
			}
			else
				init_anim(player,MC_CELEB);
	}
}

/******************************************************************************
*****************************************************************************/

void init_run_celeb(match_player *player,float tx,float ty)
{
// Moving celebration...
	player->int_move=I_CELEB;
	init_run_act(player,tx,ty,TRUE);
	if (player->tm_act!=RUN_ACT)
		init_taunt_act(player);
	else
	{
		af_randomize();
		if (player->tm_player==goal_scorer)
		{
			scorer_running=TRUE;
			switch(seed&1)
			{
				case(0):
					init_anim(player,MC_FINGER);
					break;

				case(1):
					init_anim(player,MC_PLANE);
					break;
			}
		}
		else
			init_anim(player,MC_FINGER);

		player->int_cnt=player->go_cnt+1;
	}
}		

/******************************************************************************
*****************************************************************************/

void init_stationary_celeb(match_player *player)
{
// Stationary celebration...
	player->tm_act=CELEB_ACT;
	player->go_txdis=player->tm_xdis;
	player->go_tydis=player->tm_ydis;
	player->go_txdis=0;
	player->go_tydis=0;
	player->dir_mode=2;
}

/******************************************************************************
*****************************************************************************/

#define CELEB_RUN_DIST (13*prat)

void init_celeb_act(match_player *player)
{
	reset_ideas(player);			// Stop interception etc.

	short celeb=seed&1;

#ifndef EURO96
	init_anim(player,MC_CELEB);
#endif

	if (player->tm_anim==MC_CELEB)
	{
		init_stationary_celeb(player);
	}
	else
	{
		if (player->tm_player==goal_scorer ||
			 (player->tm_player!=goal_scorer && teams[goal_scorer-1].tm_act==RUN_ACT))
		{
			if (player->tm_player!=goal_scorer)
			{
// Run towards goal scorer...
				float x=teams[goal_scorer-1].tm_x;
				float y=teams[goal_scorer-1].tm_y;
				af_randomize();
				x+=(seed-64)/2;
				af_randomize();
				y+=(seed-64)/2;
				init_run_celeb(player,x,y);
			}
			else
			{
				float a,b;
				float x=player->tm_x;
				float y=player->tm_y;
				af_randomize();
				random_vector(a,b);
				x+=(a*CELEB_RUN_DIST);
				y+=(b*CELEB_RUN_DIST);

				if (x<0)
					if (x<-CELEB_RUN_DIST)
						init_anim(player,MC_CELEB);
					else
						x=player->tm_x+(player->tm_x-x);

				if (x>pitch_len)
					if (x>(CELEB_RUN_DIST+pitch_len))
						init_anim(player,MC_CELEB);
					else
						x=player->tm_x+(player->tm_x-x);

				if (y<0)
					if (y<-CELEB_RUN_DIST)
						init_anim(player,MC_CELEB);
					else
						y=player->tm_y+(player->tm_y-y);

				if (y>pitch_wid)
					if (y>(CELEB_RUN_DIST+pitch_wid))
						init_anim(player,MC_CELEB);
					else
						y=player->tm_y+(player->tm_y-y);

				if (player->tm_anim==MC_CELEB)
					init_taunt_act(player);
				else
					init_run_celeb(player,x,y);
			}
		}
		else
		{
// Goal scorer will be doing his party piece! (follow suit)...
			init_taunt_act(player);
		}
	}
}

/******************************************************************************
*****************************************************************************/

void celeb_action(match_player *player)
{
	player->tm_x+=player->go_txdis;
	player->tm_y+=player->go_tydis;

	if (player->tm_anim==MC_KNEE)
	{
		player->go_txdis*=0.94;
		player->go_tydis*=0.94;

		if ((--player->go_cnt)<1)
		{
// Do the Duck!!!
			init_anim(player,MC_DUCK);
			player->go_txdis=player->tm_xdis*MC_DUCK_SPD;
			player->go_tydis=player->tm_ydis*MC_DUCK_SPD;
		}
	}

	if (!just_scored)
		init_stand_act(player);
}

/******************************************************************************
*****************************************************************************/

void init_stand_act(match_player *player)
{
	player->contact=-1;
	int ac=player->tm_act;
	if (ac==SAVE_ACT)
		keep_dive=FALSE;
	reset_ideas(player);			// Stop interception etc.
	player->ls_anim=ABS(player->tm_anim);	// last anim stored!
	player->ls_frm=player->tm_frm-player->tm_fstep;

	player->tm_act=STAND_ACT;
	player->go_txdis=player->tm_xdis;
	player->go_tydis=player->tm_ydis;
	player->go_txdis=0;
	player->go_tydis=0;
	player->dir_mode=1;

	if (player->tm_player==KP_A || player->tm_player==KP_B)
	{
		if (keeper_down && ac==SAVE_ACT)
		{
// This keeper is on ground...
			if (ball_in_hands && ball_poss==player->tm_player)
			{
// Guy has ball in hands...
				if (keeper_down<0)
// Keeper lying left...
				{
					init_anim(player,MC_STOSBL);
					player->tm_fstep*=(keeper_spd*2);
					init_kphold_act(player);
					init_get_up(player,player->tm_fstep);
				}
				else
				{
					if (keeper_down==1)
					{
// Keeper lying right...
						init_anim(player,MC_STOSBR);
						player->tm_fstep*=(keeper_spd*2);
						init_kphold_act(player);
						init_get_up(player,player->tm_fstep);
					}
					else
					{
// Keeper forward crouched...
						init_anim(player,MC_CRTOSTB);
						player->tm_fstep*=(keeper_spd*2);
						init_kphold_act(player);
						init_get_up(player,player->tm_fstep);
					}
				}
			}
			else
			{
// Doesn't have ball...
				if (keeper_down<0)
// Keeper lying left...
				{
					init_anim(player,MC_STOSL);
					player->tm_fstep*=(keeper_spd*2);
					init_get_up(player,player->tm_fstep);
				}
				else
				{
// Keeper lying right...
					init_anim(player,MC_STOSR);
					player->tm_fstep*=(keeper_spd*2);
					init_get_up(player,player->tm_fstep);
				}
			}

			keeper_down=0;
		}
		else
		{
// Keeper standing up...
			if (ball_in_hands && ball_poss==player->tm_player)
			{
// Has ball...
				init_anim(player,MC_STANDB);
				init_kphold_act(player);
			}
			else
			{
// Doesn't have ball...
				if (match_mode==PEN_KICK_A || match_mode==PEN_KICK_B)
					init_anim(player,MC_PENALTY);
				else						
					init_anim(player,MC_STAND);
			}
		}
	}
	else
	{
		init_anim(player,MC_STAND);
	}
}

/******************************************************************************
*****************************************************************************/

void init_steal_act(match_player *player)
{
	player->tm_act=STEAL_ACT;
	player->go_txdis=player->tm_xdis;
	player->go_tydis=player->tm_ydis;
	player->dir_mode=1;
	init_anim(player,MC_PASSL);
	reset_ideas(player);			// Stop interception etc.
}

/******************************************************************************
*****************************************************************************/

void init_kphold_act(match_player *player)
{
	keep_timer=6*REAL_SPEED;

	player->tm_act=KPHOLD_ACT;

	player->dir_mode=3;

	reset_ideas(player);			// Stop interception etc.
	keeper_steps=(1./MC_RUNWITHB_FS);
}

/******************************************************************************
*****************************************************************************/

float angle_to_target(match_player *player)
{
	float x=player->go_xoff;
	float y=player->go_yoff;

	float d=calc_dist(x,y);

// get new normalised vector.
	float nx=x/d;
	float ny=y/d;

	float ox=player->tm_xdis;
	float oy=player->tm_ydis;

// get difference (cos a).
	float dif=((nx*ox)+(ny*oy));

	if (dif>1.0)
		dif=1;

	if (dif<-1.0)
		dif=-1;

	return(dif);
}

/******************************************************************************
*****************************************************************************/

float angle_to_xy(float a,float b,float x,float y)
{
	float d=calc_dist(a,b);

// get new normalised vector.
	float nx=a/d;
	float ny=b/d;

	d=calc_dist(x,y);

	float ox=x/d;
	float oy=y/d;

// get difference (cos a).
	float dif=((nx*ox)+(ny*oy));

	if (dif>1.0)
		dif=1;

	if (dif<-1.0)
		dif=-1;

	return(dif);
}

/******************************************************************************
*****************************************************************************/

void init_stand_anims(match_player *player)
{
	short p=player->tm_player;
	if (p==KP_A || p==KP_B)
	{
// Goal-keeper...
		if (ball_in_hands && ball_poss==p)
		{
// In keeper's hands...
			init_anim(player,MC_STANDB);
		}
		else
			init_anim(player,MC_STAND);
	}
	else
		init_anim(player,MC_STAND);
}

/******************************************************************************
*****************************************************************************/

void init_trot_anims(match_player *player)
{
	init_anim(player,MC_TROTA);
}

/******************************************************************************
*****************************************************************************/

void init_run_anims(match_player *player)
{
	short p=player->tm_player;

	if (p==KP_A || p==KP_B)
	{
// Goal-keeper...
		if (ball_in_hands && ball_poss==p)
		{
// In keeper's hands...
			init_anim(player,MC_RUNWITHB);
		}
		else
			init_anim(player,MC_RUN);

	}
	else
		init_anim(player,MC_RUN);
}
	
/******************************************************************************
*****************************************************************************/

void init_run_act(match_player *player,float tx,float ty,char s)
{
	player->mface=FALSE;

// Setup target coords...
	player->go_tx=tx;
	player->go_ty=ty;

// Setup target offset...
	float x=tx-player->tm_x;
	float y=ty-player->tm_y;
	player->go_xoff=x;
	player->go_yoff=y;

	float d=calc_dist(x,y);		// How far is target!

	if (d<IM_THERE_DIST)
	{
// He is there already...
		player->tm_x=tx;
		player->tm_y=ty;
		init_stand_act(player);
	}
	else
	{
// Got to travel...

// Angle facing towards target...
		float a=angle_to_xy(x,y,player->tm_xdis,player->tm_ydis);
	
		if (a>=cos(MAX_TURN))
		{
// He is facing target??? (no need to side step!)
			player->go_step=FALSE;
			if (s)
				s=2;
		}

// Now! Should he be side-stepping???
		if (s && ((player->go_step && d<STEP_RANGE*2) || (!player->go_step && d<STEP_RANGE)))
		{
// Jog now!
			player->go_stop=FALSE;
			player->go_step=TRUE;
			player->go_cnt=d/actual_spd(player)+1;
			player->go_txdis=x/player->go_cnt;
			player->go_tydis=y/player->go_cnt;
			init_trot_anims(player);
			if (s==TRUE)
				player->dir_mode=1;		// Face ball.
			else
				player->dir_mode=0;		// Face target.
		}
		else
		{
// Run now!
			player->go_step=FALSE;
			player->go_cnt=get_there_time(player->tm_player,tx,ty);
			if (player->go_cnt>=2000)
				init_stand_act(player);
			else
				player->go_cnt-=must_face_time;

			player->mface_x=x_face;
			player->mface_y=y_face;		// Direction he will be facing at target point!

			if (must_face)
			{
// Must get to a target and then face in a certain dir...
				player->mface=TRUE;
				player->mface_time=must_face_time;
			}
	
			if (stop_and_face)
			{
// Quickest way to get to target is to stop and turn then run straight...
			
				player->go_stop=TRUE;
			
				short tt=ABS(acos(a)/MAX_TURN);		// time to turn!

// Displacement vectors after turning...
				player->go_txdis=x/(player->go_cnt-tt);
				player->go_tydis=y/(player->go_cnt-tt);
				init_stand_anims(player);
			}
			else
			{
				player->go_stop=FALSE;

// Displacement points to target... (not current though!)
				player->go_txdis=x/player->go_cnt;
				player->go_tydis=y/player->go_cnt;
				init_run_anims(player);
			}
	
			player->dir_mode=0;		// Face target.

			if (user_controlled && uf2)
			{
// Run Fast (user only!)...
				player->go_txdis=player->go_txdis*1.2;
				player->go_tydis=player->go_tydis*1.2;
			}
		}
		player->tm_act=RUN_ACT;
	}
}




/*
// How long to get there...
	player->go_cnt=get_there_time(player->tm_player,tx,ty);

// Face target coords mode...
	player->dir_mode=0;

	if ((ABS(x)<=.1) && (ABS(y)<=.1))
	{
		if ((user_controlled) && (ball_poss==player->tm_player))
			init_stand_act(player);
		else
			init_stand_act(player);
	}
	else
	{
		if (player->tm_player==3)
			player->tm_player=3;

		if (!shall_i_turn(player,x,y,s))		// Turn if need be (maybe step)!
		{
			float dist=calc_dist(x,y);
			player->go_dist=(int)dist;
			if (!player->go_step)
			{
// Player not trotting...
				if ((!ball_in_hands) && ((player->int_move==I_INTERCEPT) || (user_controlled) ||
					((dist>MUST_RUN_DIST) && (ABS(player->tm_anim)==MC_RUN)) ||
					((dist>(MUST_RUN_DIST*2)) && (ABS(player->tm_anim)!=MC_RUN)) ||
					(player->tm_player==ball_poss && !ball_in_hands) ||
					(plr_facing(x,y,player))))
				{
					player->go_cnt=((dist)/actual_spd(player));				//No. of steps till target.
					init_anim(player,MC_RUN);
				}
				else
				{
					if ((player->tm_player==KP_A) || (player->tm_player==KP_B))
					{
						if (ball_in_hands && ball_poss==player->tm_player)
						{
// kickout run up...
							player->go_cnt=((dist)/(actual_spd(player)/4));				//No. of steps till target.
							init_anim(player,MC_RUNWITHB);
						}
						else
						{
							player->go_cnt=((dist)/(actual_spd(player)/2));				//No. of steps till target.
							init_anim(player,MC_JOG);
						}
					}
					else
					{
						player->go_cnt=dist/(actual_spd(player)/2);				//half speed.
						init_anim(player,MC_JOG);
					}
				}
			}
			else
			{
// Trot away...
				player->go_cnt=dist/(actual_spd(player));				//half speed.
				init_anim(player,MC_TROTA);
				player->dir_mode=1;		// Face ball.
			}

			player->go_cnt++;
			player->go_txdis=x/player->go_cnt;
			player->go_tydis=y/player->go_cnt;
			player->tm_act=RUN_ACT;

			if (user_controlled && uf2)
			{
// Run Fast (user only!)...
				player->go_txdis=player->go_txdis*1.2;
				player->go_tydis=player->go_tydis*1.2;
			}
		}
	}
}
*/


/******************************************************************************
*****************************************************************************/

void init_fall(match_player *player)
{
	reset_ideas(player);
	if (ball_poss==player->tm_player)
		holder_lose_ball();

//	get_face_xy(player->face_dir,x,y);

	player->go_txdis=(player->tm_xdis*FALL_RATE);
	player->go_tydis=(player->tm_ydis*FALL_RATE);
	player->go_tx=player->tm_x+(player->go_txdis*100);
	player->go_ty=player->tm_y+(player->go_tydis*100);
	player->tm_z=0;
	player->go_cnt=(1/MC_FALLR_FS)-1;
	player->tm_act=FALL_ACT;
	player->dir_mode=0;
	init_anim(player,MC_FALLR);
	action="Fall";
}

/******************************************************************************
*****************************************************************************/

void init_jump_act(match_player *player,char dir,char ride)
{
	float t;

	reset_ideas(player);

	if (dir)
	{
		if (ride)
// Ride tackle... set zdis to length of animation...
		{
			player->dir_mode=0;
			player->tm_act=JUMP_ACT;
			action="Jump";
			init_anim(player,MC_RIDEL);
			player->tm_zdis=(((1.0-player->tm_frm)/player->tm_fstep)-2)*gravity/2;
		}
		else
// Jump as high as poss...
		{
			player->tm_zdis=1.0+(float)(player->tm_pow)/32;
			player->dir_mode=0;
			player->tm_act=JUMP_ACT;
			action="Jump";
			t=((player->tm_zdis/gravity)*2)+1;
			init_anim(player,MC_J_HEAD);
			player->tm_fstep=(float)1/t;
		}
	}
	else
	{
		if (player->tm_zdis!=0)
		{
			player->dir_mode=1;
			player->tm_act=JUMP_ACT;
			action="Header";
			player->go_txdis=0;
			player->go_tydis=0;
			t=((player->tm_zdis/gravity)*2)+1;
			init_anim(player,MC_J_HEAD);
			player->tm_fstep=(float)1/t;
		}
	}
}

/******************************************************************************
*****************************************************************************/

void jump_action(match_player *player)
{
	player->tm_z+=player->tm_zdis;
	player->tm_zdis-=gravity;
	go_toward_target(player);
	if (player->tm_z<=0)
	{
		player->tm_z=0;
		player->tm_zdis=0;

		init_stand_act(player);
	}
}

/******************************************************************************
*****************************************************************************/

void user_init_tackle(match_player *player)
{
	if (um)
	{
//		if (camera!=6)
// Flat mode!
			init_tackle_act(player,player->tm_x+(ux*256),player->tm_y+(uy*256));
/*
		else

// Follow mode!
		{
			if (player->tm_act==RUN_ACT)
				init_tackle_act(player,player->tm_x+(player->tm_xdis*256)
											 ,player->tm_y+(player->tm_ydis*256));
			else
			{
				float x,y;
				forward_joystick(player,x,y);
				init_tackle_act(player,player->tm_x+(x*256),player->tm_y+(y*256));
			}
		}
*/
	}
	else
	{
		float x,y;
//		get_face_xy(player->face_dir,x,y);
		x=player->tm_xdis;
		y=player->tm_ydis;
		init_tackle_act(player,player->tm_x+(x*256),player->tm_y+(y*256));
	}
}		

/******************************************************************************
*****************************************************************************/

void init_tackle_act(match_player *player,float tx,float ty)
{
	float x,y,d;
	x=tx-player->tm_x;
	y=ty-player->tm_y;

	d=calc_dist(x,y);
	player->go_tx=player->tm_x+(x/d*30*prat);
	player->go_ty=player->tm_y+(y/d*30*prat);

	x=tx-player->tm_x;
	y=ty-player->tm_y;

	player->go_xoff=x;
	player->go_yoff=y;

	float a=angle_to_xy(x,y,player->tm_xdis,player->tm_ydis);

	if (a>=cos(MAX_TURN))
	{
		inc_tack(player->tm_player);
		float d=calc_dist(x,y);
		player->go_cnt=(TACKLE_TURNS);	//no. of steps till target.
		player->go_txdis=((x)*((player->tm_rate+player->tm_pow+32)/20)/d);
		player->go_tydis=((y)*((player->tm_rate+player->tm_pow+32)/20)/d);
		player->tm_act=TACKLE_ACT;
		action="Tackle";
		player->dir_mode=0;
		init_anim(player,MC_S_TACKLE);
		player->go_cnt=1/MC_S_TACKLE_FS;	//no. of steps till target.
		play_fx(PS_SLIDING,player->tm_x,player->tm_y);
	}
}

/******************************************************************************
*****************************************************************************/

void rotate_offs(int an,float &x,float &y,float &z,float nx,float ny)
{
	float d=calc_dist(nx,ny);
	nx=nx/d;
	ny=ny/d;

// Calculate contact offsets with rotation in direction of facing...
	x=save_offs[((an-MC_AFOOTB)*3)];	 	//x
	y=-save_offs[((an-MC_AFOOTB)*3)+1];	//y
	z=save_offs[((an-MC_AFOOTB)*3)+2];	//z

// Normal of offset...
	float dof=calc_dist(x,y);
	if (dof>1)
	{

// Is there any offset present???
		x=x/dof;
		y=y/dof;

// get angle of rotation.
		float nsx=(x*nx)-(y*ny);
		float nsy=(y*nx)+(x*ny);
		x=nsx*dof;
		y=nsy*dof;
	}
	else
	{
		x=0;
		y=0;
		z=0;
	}
}

/******************************************************************************
*****************************************************************************/

void init_save_act(match_player *player,int tx,int ty,int tz,int an,int zone,int bp,int cont)
{
	float nx,ny,acc,cacc,sacc;

	if (!user_controlled && penalty_shot)
	{
// Penalty shot... (computer keeper can sometimes dive in wrong direction!)
		af_randomize();
		if (seed>(32+((player->tm_flair+player->tm_vis)/3)))
			ty=player->tm_y-(ty-player->tm_y);
	}

	keeper_down=0;

// Accuracy of 64 gives range of (20 to -20 degrees)...
	acc=((float)((rand_range(128-player->tm_ac))*(seed&1 ? 1:-1)))/183;
//	acc=0;
	cacc=cos(acc);
	sacc=sin(acc);

	af_randomize();
	
	float x=tx-player->tm_x;
	float y=ty-player->tm_y;

// Horz. vector to target...
	float d=calc_dist(x,y);
	x=x/d;
	y=y/d;

// Add inaccuracy based on stats...
	nx=(x*cacc)-(y*sacc);
	ny=(y*cacc)+(x*sacc);

	newdx=ny;
	newdy=nx;

	if ((an>MC_AJUMPC) && (an<=MC_CJUMPBR))
	{
// Is he going left or right???
		if ((nx*(player->tm_y-bally))>(ny*(player->tm_x-ballx)))
		{
			newdy=-newdy;
			an++;
		}
		else
			newdx=-newdx;
	}

// Face Ball...
	newdx=ballx-player->tm_x;
	newdy=bally-player->tm_y;
	float nd=calc_dist(newdx,newdy);
	newdx=newdx/nd;
	newdy=newdy/nd;

	if (an==MC_AFOOTC)
		keeper_down=2;

	if ((an>=MC_BFOOTCL && an<=MC_BBODYCR) || (an>=MC_CFOOTBL && an<=MC_CBODYCR))
	{
// Keeper will hit ground...
		if (an&1)
// Going right...
			keeper_down=1;
		else
			keeper_down=-1;
	}

// Calculate current mcap offsets for given direction (newdx,newdy)!
	float sx,sy,sz;
	rotate_offs(an,sx,sy,sz,newdx,newdy);
//	rotate_offs(an,sx,sy,sz,player->tm_xdis,player->tm_ydis);
	save_xoff=sx;
	save_yoff=sy;
	save_zoff=sz;

// Get horz. distance offset from target point to centre of body,
// based on motion capture animation...
/*WAIT for mcap data...*/
	x=(nx*d)-save_xoff;
	y=(ny*d)-save_yoff;

	reset_ideas(player);

	player->tm_act=SAVE_ACT;
	player->go_cnt=1/player->tm_fstep;
	if (keeper_on_grnd)
// Stay down for a bit after save...
		if (save_block)
			player->int_cnt=4+((128-player->tm_rate)/12)+1/player->tm_fstep;		// Time to get up!
		else
			player->int_cnt=18+1/player->tm_fstep;		// Time to get up!
	else
		player->int_cnt=2+1/player->tm_fstep;

	player->int_move=I_SAVE_WAIT;
	action="Save";
	init_anim(player,an);

	player->dir_mode=5;
//	player->dir_mode=2;

 	player->go_tx=player->tm_x+x;
	player->go_ty=player->tm_y+y;
	player->go_xoff=x;
	player->go_yoff=y;

	if (keeper_will_save)
	{
		player->go_txdis=x/bp;
		player->go_tydis=y/bp;
	}
	else
	{
		player->go_txdis=x/cont;
		player->go_tydis=y/cont;
	}

	d=calc_dist(player->go_txdis,player->go_tydis);
	if (d>(actual_spd(player)))
	{
		player->go_txdis=player->go_txdis*actual_spd(player)/d;
		player->go_tydis=player->go_tydis*actual_spd(player)/d;
	}
		
	player->tm_zdis=0;

}

/******************************************************************************
*****************************************************************************/

void go_toward_target(match_player *player)
{
	player->tm_x+=(player->go_txdis);
	player->tm_y+=(player->go_tydis);
}

/******************************************************************************
*****************************************************************************/

void go_forward(match_player *player)
{
	float rate=actual_spd(player);

	if (player->go_step)
	{
// Player is trotting facing ball...
		player->tm_x+=(player->go_txdis);
		player->tm_y+=(player->go_tydis);
		inc_work(player->tm_player);
	}
	else
	{
// Player is aiming to run straight at target...

		if (player->go_stop)
		{
// Player must wait until he faces target before moving on...

			float a=angle_to_xy(player->go_txdis,player->go_tydis,player->tm_xdis,player->tm_ydis);
						
			if (a>=cos(MAX_TURN))
			{
// Now facing target... (can move forward!)
				player->go_stop=FALSE;
				player->tm_x+=(player->go_txdis);
				player->tm_y+=(player->go_tydis);
				inc_work(player->tm_player);
				init_run_anims(player);
			}
			else
			{
// Stand on the spot...
			}
		}
		else
		{
// Run forward in present dir at turn speed...

			float a=angle_to_xy(player->go_tx-player->tm_x,player->go_ty-player->tm_y,player->tm_xdis,player->tm_ydis);
			float turn_spd=(1.0+a)/2;
			player->go_txdis=player->tm_xdis*turn_spd*rate;
			player->go_tydis=player->tm_ydis*turn_spd*rate;

			player->tm_x+=(player->go_txdis);
			player->tm_y+=(player->go_tydis);
			inc_work(player->tm_player);
		}
	}
}

/******************************************************************************
*****************************************************************************/

void scorer_go(match_player *player)
{
	init_celeb_act(player);
}

/*
	float xoff=cntspot_x-player->tm_x;
	float yoff=cntspot_y-player->tm_y;
	xoff+=64-seed;
	af_randomize();
	yoff+=64-seed;
	float step=(calc_dist(xoff,yoff)/actual_spd(player));
	player->go_txdis=xoff/step;
	player->go_tydis=yoff/step;
	init_jump_act(player,TRUE);
}
*/

/******************************************************************************
*****************************************************************************/

void player_shame(match_player *player)
{
	init_anim(player,MC_SHAME);
	init_get_up(player,MC_SHAME_FS);
}

/******************************************************************************
*****************************************************************************/

void go_to_scorer(match_player *player)
{
	int gs=goal_scorer;
	if (player->tm_act<TURN_ACT)
	{
		float x=teams[gs-1].tm_x;
		float y=teams[gs-1].tm_y;
		float d=calc_dist(x-player->tm_x,y-player->tm_y);
		short dp=(player->tm_player>11 ? (player->tm_player-11):(player->tm_player));
		dp=dp*6;
		if (d<8+dp)
			init_celeb_act(player);
		else
		{
			init_run_act(player,x,y,TRUE);
			{
				if (player->tm_act==RUN_ACT)
				{
					go_forward(player);
					player->go_cnt=0;
				}
			}
		}
	}
}

/******************************************************************************
*****************************************************************************/

void someone_has_scored(match_player *player)
{
	if (player->int_move!=I_CELEB && (goal_scorer==player->tm_player || (player->tm_player!=KP_A && player->tm_player!=KP_B)))
	{

		if (last_goal==1)
		{
// Goal for team A...
			if (goal_scorer<12)
			{
// Celebrate...
				if (goal_scorer==player->tm_player)
// He scored!
					scorer_go(player);
				else
					if (player->tm_player<12)
// His team-mate
						go_to_scorer(player);
					else
						init_stand_act(player);
			}
			else
			{
// Own goal( Shame!	)
				if (goal_scorer==player->tm_player)
// He scored!
					player_shame(player);
				else
					init_stand_act(player);
			}
		}
		else
		{
// Goal for team B...
			if (goal_scorer>11)
			{
// Celebrate...
				if (goal_scorer==player->tm_player)
// He scored!
					scorer_go(player);
				else
					if (player->tm_player>11)
// His team-mate
						go_to_scorer(player);
					else
						init_stand_act(player);
			}
			else
			{
// Own goal( Shame!	)
				if (goal_scorer==player->tm_player)
// He scored!
					player_shame(player);
				else
					init_stand_act(player);
			}
		}
	}
	else
		if (player->int_move!=I_CELEB)
			init_stand_act(player);
}

/******************************************************************************
*****************************************************************************/

void dont_run_off(match_player *player)
{
	if ((ballx<16) || (ballx>pitch_len-16) ||
		 (bally<16) || (bally>pitch_wid-16))
		init_stand_act(player);
}		

/******************************************************************************
*****************************************************************************/

void user_stand(match_player *player)
{
 
//	if (camera!=6)
// Flat mode!
		if (!f1_down && !f2_down)
// Not doing special...
			if (game_action==-1)
// Should take up zonal position...
				find_zonal_target(player,player->tm_x,player->tm_y);	//players x,y for comparison.
			else
				init_run_act(player,player->tm_x+ux*256,player->tm_y+uy*256,FALSE);
/*
	else

// Follow mode!
	{
		float x,y;
		forward_joystick(player,x,y);
		if (uy<0)
			if (!match_mode && game_action==1)
// Should take up zonal position...
				find_zonal_target(player,player->tm_x,player->tm_y);	//players x,y for comparison.
			else
				init_run_act(player,player->tm_x+x*256,player->tm_y+y*256,FALSE);
		else
		{
			player->go_txdis=x;
			player->go_tydis=y;
		}
	}
*/
	player->go_cnt=1;
}		

/******************************************************************************
*****************************************************************************/

/*
void check_for_header(match_player *player)
{
	if ((ball_inair) && (!ball_poss))
//		&& (player->int_move==I_INTERCEPT) && (player->int_cnt))
	{

		int meet=200;
		prev_d=5000;
		for (int i=0; i<24; i++)
		{
			x=ball_pred_tab[i][0];
			y=ball_pred_tab[i][1];
			z=ball_pred_tab[i][2];

			d=calc_dist(x-player->tm_x,y-player->tm_y);

// Volley???
			if (ballx>

			if (ballz>
			if (d<min_d)
			{
				min_d=d;
				meet=i;
			}
			else
				i=21;			// end loop (not getting closer to ball)

			prev_d=d;
		}
		if (meet!=200)
		{
// Ball has a closest point...
			x=ball_pred_tab[meet][0];
			y=ball_pred_tab[meet][1];
			z=ball_pred_tab[meet][2];



			z=z-PLAYER_HEIGHT+5;

//			float	zd=sqrt(z)-(gravity*gravity);			// Take-off speed for given max height!

			float zd=sqrt(2*z*gravity)-(gravity*gravity);					// Max. Height
			int jt=gravity+zd/gravity;			// Time to reach max height.

			jt=meet-jt;
			
			if (jt>=0)
			{
				reset_ideas(player);
				player->int_cnt=jt;
				player->int_move=I_HEADER;	// Wait for header.
				player->tm_zdis=zd;
			}
		}
	}
}
*/

/******************************************************************************
*****************************************************************************/

void kick_strike(match_player *player)
{
	if (player->tm_srng)
	{
// In Shooting Range!
		shoot_ball(player);
	}
	else
	{
		punt_ball(player);
	}
}

/******************************************************************************
*****************************************************************************/

void overhead_strike(match_player *player)
{
	player->tm_xdis=-player->tm_xdis;
	player->tm_ydis=-player->tm_ydis;		// Facing backwards...

	int p=player->tm_pow;
	player->tm_pow=p*2/3;			// 2 3rds power of kick!

	if (player->tm_srng)
	{
// In Shooting Range!
		shoot_ball(player);
	}
	else
	{
		punt_ball(player);
	}

	player->tm_xdis=-player->tm_xdis;
	player->tm_ydis=-player->tm_ydis;
	player->tm_pow=p;
}

/******************************************************************************
*****************************************************************************/

void chip_strike(match_player *player)
{
	pass_type=player->tm_fpass_type;
	receiver=player->tm_fpass_to;
	pass_ball(receiver,FALSE);
}

/******************************************************************************
*****************************************************************************/

void head_strike(match_player *player)
{
	heading_ball=TRUE;
	if (player->tm_fpass_type)
	{
		pass_type=player->tm_fpass_type;
		receiver=player->tm_fpass_to;
		pass_ball(receiver,FALSE);
	}
	else
	{
		int p=player->tm_pow;
		player->tm_pow=p/2;			// Half power of kick!

		if (player->tm_srng)
		{
// In Shooting Range!
			if (user_controlled)
			{
				if (uf1)		// Head down!
					heading_ball=3;
			}
			else
				if (seed<player->tm_ac)
					heading_ball=3;
			
			shoot_ball(player);
		}
		else
		{
			punt_ball(player);
		}

		player->tm_pow=p;
	}
	heading_ball=FALSE;
}

/******************************************************************************
*****************************************************************************/

void dvhead_strike(match_player *player)
{
	int p=player->tm_pow;
	player->tm_pow=p/2;			// Half power of kick!
	heading_ball=2;

	short ps=pass_decide(player,FALSE);
	if (ps && pass_type>=3)
	{
		pass_ball(ps,FALSE);
	}
	else
	{
		if (player->tm_srng)
		{
// In Shooting Range!
			shoot_ball(player);
		}
		else
		{
			punt_ball(player);
		}
	}
	player->tm_pow=p;
	heading_ball=FALSE;
}

/******************************************************************************
*****************************************************************************/

void strike_ball_off(match_player *player)
{
	add_comp_pass(player->tm_player);
	player->tm_ftime=-1;
	last_touch=player->tm_player;
	if (last_touch!=KP_A && last_touch!=KP_B)
		pre_kp_touch=last_touch;

	ball_poss=player->tm_player;
	int a=player->tm_anim;
	switch(a)
	{
		case(MC_OVERHEAD):
			overhead_strike(player);
			break;

		case(MC_DV_HEAD):
			dvhead_strike(player);
			break;

		case(MC_J_HEAD):
		case(MC_S_HEAD):
			head_strike(player);
			break;

		case(MC_CHIPL):
		case(MC_CHIPR):
			chip_strike(player);
			break;

		case(MC_SHOOTL):
		case(MC_SHOOTR):
		case(MC_VOLLEYL):
		case(MC_VOLLEYR):
			kick_strike(player);
			break;
	}

	standard_fstep(player);
}

/******************************************************************************
*****************************************************************************/

void fire_ball_off()
{
	reset_shot();
	if (kick_type==KT_PUNT)
	{
// Punt...
		punt_ball(&teams[ball_poss-1]);
	}
	else
	{
		if (kick_type==KT_SHOOT)
		{
// Shoot...
			shoot_ball(&teams[ball_poss-1]);
		}
		else
		{
			pass_ball(receiver,cross_now);
			cross_now=FALSE;
			chip_pass=FALSE;
			action="Pass";
		}
	}

	float sp;
	int fx;

	sp=calc_dist(ballxdis,ballydis);
	sp=calc_dist(sp,ballzdis);

	if (sp<10)
		fx=PS_SOFTKICK;
	else
		if (sp<14)
			fx=PS_MEDKICK;
		else
			fx=PS_HARDKICK;

	play_fx(fx,ballx,bally);

//	process_ball();
}

/******************************************************************************
*****************************************************************************/

void init_kick_act(match_player *player,int mc,float pc)
{
	init_anim(player,mc);
	player->tm_fstep=player->tm_fstep*player->tm_mcspd;
	player->contact=pc;
	if (!set_piece_on)
		player->dir_mode=0;
	else
		player->dir_mode=2;

	reset_ideas(player);			// Stop interception etc.
	player->int_move=I_KICKED;
	player->int_cnt=((1.0-player->tm_frm)/player->tm_fstep)+1;
	rotate_offs(ABS(player->tm_anim),b_xoff,b_yoff,b_zoff,teams[ball_poss-1].tm_xdis,teams[ball_poss-1].tm_ydis);
	player->go_txdis=MC_PASS_DIST*player->tm_fstep*player->tm_xdis;
	player->go_tydis=MC_PASS_DIST*player->tm_fstep*player->tm_ydis;
	player->go_tx=player->tm_x+player->tm_xdis*100;
	player->go_ty=player->tm_y+player->tm_ydis*100;
	player->tm_act=KICK_ACT;
}	

/******************************************************************************
*****************************************************************************/

void kick_action(match_player *player)
{
	if (player->tm_frm+player->tm_fstep>=1)
	{
// Finished kick animation...
		
		init_stand_act(player);
		player->contact=-1;
	}

	if (player->tm_frm>=player->contact && ball_poss==player->tm_player)
	{
// Contacted ball (release it)...
		fire_ball_off();
	}

	if (ball_poss!=player->tm_player && player->tm_frm<player->contact)
	{
// Ball stolen before kick!
		init_stand_act(player);
		player->contact=-1;
	}
	else
		go_toward_target(player);
}

/******************************************************************************
*****************************************************************************/

void steal_action(match_player *player)
{
	if (player->tm_frm<1.0)
	{
		if ((player->tm_frm>0.4) && (player->tm_frm<0.6)
			&& (ballz<1) && (ball_poss!=player->tm_player))
// Foot out frames...
		{
// Get foot coords...
			float x=player->tm_x+(player->tm_xdis*prat);
			float y=player->tm_y+(player->tm_ydis*prat);
			x=ballx-x;
			y=bally-y;
			float d=calc_dist(x,y);
			if (d<=STEAL_FOOT_DIST)
			{
				holder_lose_ball();
				collect_ball(player);
			}
		}
	}
	else
	{
		init_stand_act(player);
	}
}

/******************************************************************************
*****************************************************************************/

void stand_action(match_player *player)
{
	if (player->tm_strike>0 && player->int_move==I_INTERCEPT)
	{
// Waiting for first touch...
		if (--player->go_cnt<=0)
// Begin first touch animation...
			init_strike_act(player);
	}
	else
	{
		if (ABS(player->tm_anim)==MC_SOCKSL || ABS(player->tm_anim)==MC_SOCKSR)
// Pulling his socks up just now...
		{
			if (player->tm_frm>0.99)
				init_anim(player,MC_STAND);
		}
	
		player->ls_anim=ABS(player->tm_anim);		// Do not use last anim!
		player->ls_frm=player->tm_frm;		// Do not use last anim!

		if ((user_controlled) && (!match_mode)
			 && (!((player->tm_player==KP_A || player->tm_player==KP_B)
			 && ABS(player->tm_anim)>=MC_STOSL && ABS(player->tm_anim)<=MC_STOSBR)))
			user_stand(player);
		else
		{
			if (ABS(player->tm_anim)>=MC_STOSL && ABS(player->tm_anim)<=MC_STOSBR)
			{
// Keeper getting up!
				if (!player->int_cnt)
				{
					if (ball_in_hands)
						init_anim(player,MC_STANDB);
					else
						init_anim(player,MC_STAND);
				}
			}
			else
			{
				if (just_scored>0)
					someone_has_scored(player);
				else
				{
//				if (player->int_move!=I_HEADER)
//					check_for_header(player);
//				else
					if (player->int_move==I_HEADER)
					{
						if (player->int_cnt<=1)
						{
							player->int_cnt=-1;
							init_jump_act(player,FALSE);	// Jump straight up!
						}
					}
					else
					{
						if ((player->tm_player==KP_A && !(ballx<cntspot_x && shot_pending))
							|| (player->tm_player==KP_B && !(ballx>cntspot_x && shot_pending))
							|| (player->tm_player!=KP_A && player->tm_player!=KP_B))
						{
// Make sure that keeper isn't waiting to make save!
							if ((player->tm_act==STAND_ACT) && (!player->tm_stopped))
								find_zonal_target(player,player->tm_x,player->tm_y);	//players x,y for comparison.
						}
					}
				}
			}
		}

		if (ABS(player->tm_anim)==MC_STAND && player->tm_dist>(prat*50))
		{
// Standing far away from ball...
			if ((ball_poss>11 && player->tm_player>11) || (ball_poss 
				&& ball_poss<12 && player->tm_player<12))
// Team-mate has ball (safe!)...
			{
				if (seed<SOCKS_PROB)
				{
					if (seed&1)
						init_anim(player,MC_SOCKSL);
					else
						init_anim(player,MC_SOCKSR);
// Busy now...
					init_get_up(player,MC_SOCKS_FS);
				}
			}
		}				
	}
}

/******************************************************************************
*****************************************************************************/

void user_throw(match_player *player)
{
	char high=FALSE;
	float x,y;

	if (um)
// Joystick_dir...
	{
		if (bally>cntspot_y)
// Bottom line...
		{
			x=ux;
			y=uy;

			if (uy>0)
			{
				high=TRUE;
				y=-uy;
			}
			else
				high=FALSE;
		}
		else
// Top line...
		{
			x=ux;
			y=uy;

			if (uy<0)
			{
				high=TRUE;
				y=-uy;
			}
			else
				high=FALSE;
		}
			
		player->tm_xdis=x;
		player->tm_ydis=y;

		if (uf2)
// Pass to nearest team-mate...
		{
			must_pass=TRUE;
			throw_cnt=1;
			if (high)
				chip_pass=TRUE;

			int p=pass_decide(player,FALSE);
			make_pass(player,p,FALSE);
			dead_ball_cnt=0;
			game_action=0;
			just_thrown=20;
			match_mode=0;
			arrow_on=FALSE;
			already_there=FALSE;
			stop_clock=FALSE;
		}

		if (uf1)
// Throw straight...
		{
			float sx,sy,sz;
			float power=5+(player->tm_pow/16);
			ballxdis=player->tm_xdis*power;
			ballydis=player->tm_ydis*power;
			ballzdis=(high ? power:power/2);

			init_anim(player,MC_THROWL);
// Point at which ball leaves hand!
// Calculate current mcap offsets for given direction (newdx,newdy)!
			rotate_offs(MC_THROWL,sx,sy,sz,player->tm_xdis,player->tm_ydis);
			ballx=player->tm_x+sx;
			bally=player->tm_y+sy;
			ballz=player->tm_z+sz;
			ball_limbo(player->tm_player,MCC_THROWL);
			player->tm_limbo=1/MC_THROWL_FS;

			ball_inair=TRUE;
			holder_lose_ball();
			dead_ball_cnt=0;
			game_action=0;
			just_thrown=20;
			match_mode=0;
			arrow_on=FALSE;
			already_there=FALSE;
			stop_clock=FALSE;

			launch_ball(1);			// Set up spin vector.
		}
	}
}

/******************************************************************************
*****************************************************************************/

void throw_action(match_player *player)
{

// Lmen normal...
	refs[1].act=0;
	refs[2].act=0;

	if (refs[0].act!=2)
	{
// Referee wait for kick mode...
		refs[0].act=2;
		ktaker=player->tm_player;
		ref_wait=(160-ref_strictness)*REAL_SPEED/8;
		play_fx(PS_SHORTWHISTLE,refs[0].x,refs[0].y);
	}

	if (user_controlled)
		user_throw(player);
	else
	{
		if (player->dir_mode==2)
		{
// Scan in all directions for team-mate...
			float ang_add,nx,ny;
			float ox=player->go_txdis;
			float oy=player->go_tydis;

			if (player->turn_dir>0)
				ang_add=0.1047198; 		// 6 degrees (radians)
			else
				ang_add=-0.1047198;

			nx=(ox*cos(ang_add))-(oy*sin(ang_add));
			ny=(oy*cos(ang_add))+(ox*sin(ang_add));

			if (ny>1)
			{
				ny=1;
				nx=0;
			}

			if (ny<-1)
			{
				ny=-1;
				nx=0;
			}

			if ((bally<cntspot_y) && (ny<=0))
			{
				player->turn_dir=-player->turn_dir;
				ny=0;
				if (nx>0)
					nx=1;
				else
					nx=-1;
			}

			if ((bally>cntspot_y) && (ny>=0))
			{
				player->turn_dir=-player->turn_dir;
				ny=0;
				if (nx>0)
					nx=1;
				else
					nx=-1;
			}

			player->go_txdis=nx;
			player->go_tydis=ny;
	
			if (!(--throw_cnt))
	// Looked around long enough must pass now.
			{
				must_pass=TRUE;
				throw_cnt=1;
			}

			float tx=player->tm_xdis;
			float ty=player->tm_ydis;
			player->tm_xdis=player->go_txdis;
			player->tm_ydis=player->go_tydis;

			float x,y,d;

			int p=pass_decide(player,FALSE);
			if (p)
			{
				player->dir_mode=0;		// Face in move dir.
				player->turn_dir=p;		// store receiver.

				x=teams[p-1].tm_x-player->tm_x;
				y=teams[p-1].tm_y-player->tm_y;
				d=calc_dist(x,y);
				player->go_txdis=x/d;
				player->go_tydis=y/d;
				player->go_tx=teams[p-1].tm_x;
				player->go_ty=teams[p-1].tm_y;
				already_there=FALSE;
				stop_clock=FALSE;

			}
					
			player->tm_xdis=tx;
			player->tm_ydis=ty;
		}
		else
		{
// Wait for thrower to rotate to pass direction...
			
			float ox=player->tm_xdis;
			float oy=player->tm_ydis;

			float dif=((player->go_txdis*ox)+(player->go_tydis*oy));
			if (ABS(dif)>0.95)
			{
// He's facing receiver...
				make_pass(player,player->turn_dir,FALSE);
				dead_ball_cnt=0;
				game_action=0;
				just_thrown=20;
				match_mode=0;
				launch_ball(1);			// Set up spin vector.
				already_there=FALSE;
				stop_clock=FALSE;
			}
		}
	}
}

/******************************************************************************
*****************************************************************************/

// Moves player on journey to target (x,y).

void user_run(match_player *player)
{
	float px=player->tm_x;
	float py=player->tm_y;

	if ((px<-(prat*2) && ux<0)
		 || (px>pitch_len+(prat*2) && ux>0))
	{
		ux=0;
		if (ABS(uy)<0.05)
			init_stand_act(player);
		else
			if (uy>0)
				uy=1;
			else
				uy=-1;
	}

	if ((py<-(prat*2) && uy<0)
		|| (py>pitch_wid+(prat*2) && uy>0))
	{
		uy=0;
		if (ABS(ux)<0.05)
			init_stand_act(player);
		else
			if (ux>0)
				ux=1;
			else
				ux=-1;
	}
/*
	if (camera==6)
// Follow mode!
	{
		float x,y;
		forward_joystick(player,x,y);
		if (uy<0)
			init_run_act(player,player->tm_x+x*256,player->tm_y+y*256,FALSE);
		else
		{
			init_stand_act(player);
			user_stand(player);
		}
	}
	else
*/
		init_run_act(player,player->tm_x+ux*256,player->tm_y+uy*256,FALSE);

	go_forward(player);
	player->go_cnt=0;
}

/*****************************************************************************
*****************************************************************************/

// Keeper (holding ball) faces out then throws or kicks ball.

#define TOO_CLOSE_TO_GOAL (prat)

void kphold_action(match_player *player)
{
	int p=player->tm_player;
	game_action=-1;				// Force players to keep away!

	if (!player->int_cnt)
	{
		player->dir_mode=3;

// Added... Make keeper kick ball out if close to own goal line!
		char kickit=FALSE;
		if ((player->tm_player==KP_A && player->tm_x<TOO_CLOSE_TO_GOAL)
			 || (player->tm_player==KP_B && player->tm_x>(pitch_len-TOO_CLOSE_TO_GOAL)))
			kickit=TRUE;


		init_anim(player,MC_STANDB);

		if (keep_timer)
			keep_timer--;

		if (!opp_around(ballx,bally,player->tm_player) || !keep_timer)
		{
// No opposition near!
			if (seed&1 && seed&8 && !kickit)
			{
// Bounce the ball...
			  	init_anim(player,MC_BOUNCE);
				player->int_move=I_KP_BUSY;
				player->int_cnt=(1./MC_BOUNCE_FS);
			}
			else
			{
				if (seed&2 && seed&8 && !kickit)
				{
// Wave team-mates up-field...
			  		init_anim(player,MC_WAVEUP);
					player->int_move=I_KP_BUSY;
					player->int_cnt=(1./MC_WAVEUP_FS);
				}
				else
				{
					if (seed&4 && seed&8 && !kickit)
					{
// Stand for a bit...
						player->int_move=I_KP_BUSY;
						player->int_cnt=20;
					}
					else
					{
// Just run...
						if ((p==KP_A) && (player->tm_xdis>=0.95))
						{
							init_run_act(player,player->tm_x+(prat*15),player->tm_y,FALSE);
						}

						if ((p==KP_B) && (player->tm_xdis<=-0.95))
						{
							init_run_act(player,player->tm_x-(prat*15),player->tm_y,FALSE);
						}

						if (ABS(player->tm_anim)==MC_RUN)
	  						init_anim(player,MC_RUNWITHB);
					}
				}
			}
		}
	}
}

/******************************************************************************
*****************************************************************************/

void wait_action(match_player *player)
{
	if	((player->ball_state<0 && !ball_poss)
		 || (player->ball_state>0 && player->ball_state!=last_touch))
// Ball has changed trajectory!
		init_stand_act(player);
	else
	{
		if (!(--player->tm_ftime))
// No more waiting!
		{
			player->tm_strike=-player->tm_strike;
			init_strike_act(player);
		}
		else
		{
			player->tm_x+=player->go_txdis;
			player->tm_y+=player->go_tydis;
		}
	}
}

/******************************************************************************
*****************************************************************************/

void stop_action(match_player *player)
{
	if (player->int_move==I_INTERCEPT)
	{
		float	a=angle_to_xy(player->go_xoff,player->go_yoff,player->tm_xdis,player->tm_ydis);

		if (a>cos(MAX_TURN))
		{
// Facing target now...
			init_run_act(player,player->go_tx,player->go_ty,FALSE);
			go_toward_target(player);
		}
	}
	else
		init_stand_act(player);
}

/******************************************************************************
*****************************************************************************/

void init_stop_act(match_player *player,float x,float y)
{
	player->dir_mode=0;
	player->tm_act=STOP_ACT;
	player->go_tx=x;
	player->go_ty=y;
	player->go_xoff=x-player->tm_x;
	player->go_yoff=y-player->tm_y;
	init_anim(player,MC_STAND);
}
 	
/******************************************************************************
*****************************************************************************/

void init_wait_act(match_player *player,float x,float y)
{
	player->dir_mode=2;
	player->tm_act=WAIT_ACT;
	player->go_step=TRUE;	// Side step if needed!
	short m=player->int_move;
	player->int_move=0;
	float rate=actual_spd(player);
	player->int_move=m;

	float d=calc_dist(x,y);
	x=x/d;
	y=y/d;
	short t=player->tm_ftime;

	d=d/t;		// Magnitude of displacement!
	if (d>(rate+(player->tm_stime-1)))
		init_stand_act(player);
	else
	{
		player->tm_strike=-player->tm_strike;
		player->go_txdis=x*d;
		player->go_tydis=y*d;
//		player->go_tx=player->go_tx-player->tm_x+(player->go_txdis*(t+1));
//		player->go_ty=player->go_ty-player->tm_y+(player->go_tydis*(t+1));
		if (d>.5)
			init_anim(player,MC_TROTA);
		else
			init_anim(player,MC_STAND);
		player->int_cnt=player->tm_ftime+1;

		player->tm_x+=player->go_txdis;
		player->tm_y+=player->go_tydis;
	}
}

/******************************************************************************
*****************************************************************************/

void control_action(match_player *player)
{
	if (player->tm_frm>=1)
	{
// end of animation...
		ballz=0;
		init_stand_act(player);
		player->tm_ftime=-2;
		hold_ball(player);
		ball_limbo_on=FALSE;
	}
	else
	{
		if (player->tm_frm>=player->contact && ball_poss!=player->tm_player && player->tm_ftime>=0)
// Player should have ball now but doesn't....
		{
			init_stand_act(player);
		}
		else
		{
			player->tm_x+=player->go_txdis;
			player->tm_y+=player->go_tydis;
		}
	}
}

/******************************************************************************
*****************************************************************************/

void get_closest_pred(match_player *player,float &rt,float &x,float &y,float &z,float &d)
{
	float sx,sy,sz;
	rotate_offs(player->tm_anim,sx,sy,sz,player->mface_x,player->mface_y);

	x=ball_pred_tab[(int)(rt)][0]-sx;
	y=ball_pred_tab[(int)(rt)][1]-sy;
	z=ball_pred_tab[(int)(rt)][2]-sz;

	x=x-player->tm_x;
	y=y-player->tm_y;
	z=z-player->tm_z;

	d=calc_dist(x,y);
	d=calc_dist(z,d);

	float best_rt=rt;
	float min_d=d;
	float best_x=x;
	float best_y=y;
	float best_z=z;

// Check one forward...
	if (rt<49)
	{
		rt++;
		x=ball_pred_tab[(int)(rt)][0]-sx;
		y=ball_pred_tab[(int)(rt)][1]-sy;
		z=ball_pred_tab[(int)(rt)][2]-sz;

		x=x-player->tm_x;
		y=y-player->tm_y;
		z=z-player->tm_z;

		d=calc_dist(x,y);
		d=calc_dist(z,d);

		if (d<min_d)
		{
			min_d=d;
			best_rt=rt;
			best_x=x;
			best_y=y;
			best_z=z;
		}
	}

// Check one back...
	if (rt>=1)
	{
		rt-=2;
		x=ball_pred_tab[(int)(rt)][0]-sx;
		y=ball_pred_tab[(int)(rt)][1]-sy;
		z=ball_pred_tab[(int)(rt)][2]-sz;

		x=x-player->tm_x;
		y=y-player->tm_y;
		z=z-player->tm_z;

		d=calc_dist(x,y);
		d=calc_dist(z,d);

		if (d<min_d)
		{
			min_d=d;
			best_rt=rt;
			best_x=x;
			best_y=y;
			best_z=z;
		}
	}

	d=min_d;
	x=best_x;
	y=best_y;
	z=best_z;
	rt=best_rt;
}

/******************************************************************************
*****************************************************************************/

void init_control_act(match_player *player)
{
	float x,y,z,d,rt;

	switch(player->tm_strike)
	{
		case(1):
			init_anim(player,MC_TRAPL);
			player->contact=MCC_TRAP;
			z=save_offs[(MC_TRAPL*3)+2];
			break;

		case(2):
			init_anim(player,MC_CHEST);
			player->contact=MCC_CHEST;
			z=save_offs[(MC_CHEST*3)+2];
			break;

		case(3):
			init_anim(player,MC_D_HEAD);
			player->contact=MCC_D_HEAD;
			z=save_offs[(MC_D_HEAD*3)+2];
			break;
	}
	
// Real contact point with offset...
	float old_rt=player->tm_stime+player->tm_ftime;
	rt=old_rt;
	get_closest_pred(player,rt,x,y,z,d);

	player->tm_ftime+=rt-old_rt;		// Add difference in timing.

	if (player->tm_ftime>0)
	{
// Some free time... (lets stand and wait!)
		init_wait_act(player,x,y);
	}
	else
	{
// Need to run animation...
		player->tm_ftime=0;
		short ts=player->tm_strike;
		reset_ideas(player);

		if (player->tm_player>11)
			interceptor_b=player->tm_player;
		else
			interceptor_a=player->tm_player;

		player->tm_strike=ts;
		player->tm_act=CONTROL_ACT;
		player->int_move=I_RECEIVE;
		player->tm_fstep=player->contact/rt;
		player->tm_frm=player->tm_fstep+0.01;
		player->int_cnt=((1.0-player->tm_frm)/player->tm_fstep)+1;
	
		d=calc_dist(x,y);
		if (d/rt>1)
// Ball has changed direction... (cannot meet!)
			init_stand_act(player);
		else
		{
			if (abs(z)>prat)
// Ball has changed direction... (cannot meet!)
				init_stand_act(player);
			else
			{
// set displacement to meet ball at contact point!
				player->go_txdis=x/rt;
				player->go_tydis=y/rt;

// keep facing same direction!
				player->dir_mode=2;
			}

			player->tm_strike=-player->tm_strike;
		}
	}
}

/******************************************************************************
*****************************************************************************/

#define JUMP_POINT (0.1)

void strike_action(match_player *player)
{
	if (player->tm_frm+player->tm_fstep>=1)
	{
// end of animation...
		player->tm_ftime=-2;

		if (player->tm_anim==MC_OVERHEAD)
		{
// On the ground must get up ( on his back )...
			player->tm_limbo=1/MC_GETUP_FS;
			init_anim(player,MC_GETUP);
		}
		else
		{
			if (player->tm_anim==MC_DV_HEAD)
			{
// On the ground must get up ( on his front )...
				player->tm_limbo=1/MC_GETUPF_FS;
				init_anim(player,MC_GETUPF);
			}
			else
				init_stand_act(player);
		}
	}
	else
	{
		if (player->tm_anim==MC_J_HEAD)
		{
// Jumping header...
			if (player->tm_frm>JUMP_POINT)
			{
				player->tm_z+=player->tm_zdis;
				if (player->tm_z<0)
					player->tm_z=0;
				else
					player->tm_zdis-=gravity;
			}
		}

		if (player->tm_frm>=player->contact)
// Player can slow down now...
		{
			player->go_txdis=player->go_txdis*SAVE_DECEL;
			player->go_tydis=player->go_tydis*SAVE_DECEL;
		}

		player->tm_x+=player->go_txdis;
		player->tm_y+=player->go_tydis;
	}
}

/******************************************************************************
*****************************************************************************/

void init_first_time_act(match_player *player,int mc,float pc)
{
	float x,y,z,d,rt;

	init_anim(player,mc);

	player->tm_frm=0;
	
// Real contact point with offset...
	float old_rt=player->tm_stime+player->tm_ftime;
	rt=old_rt;
	get_closest_pred(player,rt,x,y,z,d);

	player->tm_ftime+=rt-old_rt;		// Add difference in timing.

	if (player->tm_ftime>0)
	{
// Some free time... (lets stand and wait!)
		init_wait_act(player,x,y);
	}
	else
	{
// Need to speed up animation...
		player->tm_ftime=0;
		short ts=player->tm_strike;
		reset_ideas(player);			// Stop interception etc.

		if (player->tm_player>11)
			interceptor_b=player->tm_player;
		else
			interceptor_a=player->tm_player;

		player->tm_strike=ts;
		player->tm_act=STRIKE_ACT;
		player->int_move=I_RECEIVE;
		player->contact=pc;
		float fs=player->tm_fstep;
		player->tm_fstep=player->contact/rt;
		player->tm_frm=player->tm_fstep+0.01;
		player->int_cnt=((1.0-player->tm_frm)/player->tm_fstep)+1;

		if (mc==MC_J_HEAD)
			player->tm_zdis=(gravity*((player->int_cnt-1)*.6)/2);

		d=calc_dist(x,y);
		if (d/rt>2)
// Ball has changed direction... (cannot meet!)
			init_stand_act(player);
		else
		{
			if (abs(z)>prat)
// Ball has changed direction... (cannot meet!)
				init_stand_act(player);
			else
			{

// set displacement to meet ball at contact point!
				player->go_txdis=x/rt;
				player->go_tydis=y/rt;

// keep facing same direction!
				player->dir_mode=2;
			}
			player->tm_strike=-player->tm_strike;
		}
	}
}

/******************************************************************************
*****************************************************************************/

void oinit_first_time_act(match_player *player,int mc,float pc)
{
	float x,y,z,d;

	init_anim(player,mc);

	float sx,sy,sz;

	rotate_offs(mc,sx,sy,sz,player->tm_xdis,player->tm_ydis);

// Real contact point with offset...
	float rt=player->tm_stime+player->tm_ftime;
	x=ball_pred_tab[(int)(rt)][0]-sx;
	y=ball_pred_tab[(int)(rt)][1]-sy;
	z=ball_pred_tab[(int)(rt)][2]-sz;

	x=x-player->tm_x;
	y=y-player->tm_y;
	z=z-player->tm_z;

	if (player->tm_ftime)
	{
// Some free time... (lets stand and wait!)
		init_wait_act(player,x,y);
	}
	else
	{
		player->tm_strike=-player->tm_strike;
		float fs=player->tm_fstep;		// Standard anim speed fstep!
		player->contact=pc;
		player->tm_fstep=(pc-player->tm_frm)/(player->tm_stime+player->tm_ftime);
		player->dir_mode=2;
		reset_ideas(player);			// Stop interception etc.
		player->int_move=I_RECEIVE;
		player->int_cnt=((pc-player->tm_frm)/player->tm_fstep)+(1-pc/fs)+1;
		player->tm_act=STRIKE_ACT;

		float d=calc_dist(x,y);
		if (d/rt>1)
	// Ball has changed direction... (cannot meet!)
			init_stand_act(player);
		else
		{
			if (abs(z)>prat)
	// Ball has changed direction... (cannot meet!)
				init_stand_act(player);
			else
			{
	// set displacement to meet ball at contact point!
				player->go_txdis=x/rt;
				player->go_tydis=y/rt;
			}
		}
	}
}

/******************************************************************************
*****************************************************************************/

void init_strike_act(match_player *player)
{
	short s;

	switch(player->tm_strike)
	{
		case(1):
		case(2):
		case(3):
			init_control_act(player);
			break;

		case(4):
			init_first_time_act(player,MC_OVERHEAD,MCC_OVERHEAD);
			headed_ball=FALSE;
			break;

		case(5):
			init_first_time_act(player,MC_VOLLEYL,MCC_VOLLEY);
			headed_ball=FALSE;
			break;

		case(6):
			init_first_time_act(player,MC_DV_HEAD,MCC_DV_HEAD);
			headed_ball=TRUE;
			break;

		case(7):
			init_first_time_act(player,MC_J_HEAD,MCC_J_HEAD);
			headed_ball=TRUE;
			break;

		case(8):
			init_first_time_act(player,MC_SHOOTL,MCC_SHOOT);
			headed_ball=FALSE;
			break;

		case(9):
			init_first_time_act(player,MC_S_HEAD,MCC_S_HEAD);
			headed_ball=TRUE;
			break;

		case(10):
			init_first_time_act(player,MC_CHIPL,MCC_CHIP);
			headed_ball=FALSE;
			break;
	}
}

/******************************************************************************
*****************************************************************************/

// Moves player on journey to target (x,y).

void orun_action(match_player *player)
{
	if ((player->tm_comm==SAY_PASS || player->tm_comm==SAY_CROSS)
		&& !player->tm_ccnt)
// He's asking for ball!
		go_toward_target(player);
	else
	{
		int player_ref=player->tm_player;

		if ((ball_poss || (!ball_poss && player->int_move!=I_INTERCEPT)) && (user_controlled) && (!match_mode))

			user_run(player);
		else
		{
			if (ball_poss!=player_ref)
			{
				if (sender_1_2!=player_ref)
				{
					if (player->tm_strike>0 && player->int_move==I_INTERCEPT
						 && ((player->ball_state<0 && !ball_poss)
						 || (player->ball_state>0 && player->ball_state!=last_touch)))
						 init_stand_act(player);
					else
					{
						--player->go_cnt;
						if (player->go_cnt<=0)
						{
							player->go_cnt=0;

							if (player->tm_strike>0 && player->int_move==I_INTERCEPT)
// Begin first touch animation...
							{
								go_toward_target(player);
								init_strike_act(player);
							}
							else
							{
								if ((player->tm_player==KP_A && !(ballx<cntspot_x && shot_pending))
									|| (player->tm_player==KP_B && !(ballx>cntspot_x && shot_pending))
									|| (player->tm_player!=KP_A && player->tm_player!=KP_B))
								{
// Make sure that keeper isn't waiting to make save!
									find_zonal_target(player,player->tm_x,player->tm_y);	//players x,y for comparison.
									if ((player->go_cnt) && (player->tm_act==RUN_ACT))
									{
										go_toward_target(player);
									}
									else
									{
										if (player->tm_act!=TURN_ACT)
											init_stand_act(player);
									}
								}
								else
								{
// Keeper waiting to make save!
									init_stand_act(player);
								}
							}
						}
						else
						{
							if (just_scored>0)
								someone_has_scored(player);		// Target is goal scorer!
							else					
							{
								go_toward_target(player);
							}
						}
					}
				}
			}
			else
// Running with ball!
			{
				--player->go_cnt;
				if (player->go_cnt<=0)
				{
					player->go_cnt=0;
					init_stand_act(player);
				}
				else
				{
					go_toward_target(player);
					if (ball_in_hands)
					{
						if (player->tm_player==KP_A)
						{
// Keeper A...
							if (keeper_a_in_box)
							{
// Can only take three steps...
								if (!(--keeper_steps))
									must_punt=TRUE;
							}
							else
							{
								must_punt=TRUE;
							}
						}
	 					else
						{
							if (player->tm_player==KP_B)
// Keeper B...
							{
								if (keeper_b_in_box)
								{
									if (!(--keeper_steps))
										must_punt=TRUE;
// Can only take three steps...
								}
								else
								{
									must_punt=TRUE;
								}
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

// Moves player on journey to target (x,y).

void run_action(match_player *player)
{
	if ((player->tm_comm==SAY_PASS || player->tm_comm==SAY_CROSS)
		&& !player->tm_ccnt)
// He's asking for ball!
		go_forward(player);
	else
	{
		int player_ref=player->tm_player;

		if (user_controlled && game_action!=-1 && !match_mode && (ball_poss || (!ball_poss && player->int_move!=I_INTERCEPT)))

			user_run(player);
		else
		{
			if (ball_poss!=player_ref)
			{
// Doesn't have ball...
				if (sender_1_2!=player_ref)
				{
// Not part of 1-2 move...
					if (player->tm_strike>0 && player->int_move==I_INTERCEPT
						 && ((player->ball_state<0 && !ball_poss)
						 || (player->ball_state>0 && player->ball_state!=last_touch)))

// Can't continue first touch action! (Ball trajectory has changed!)

						 init_stand_act(player);
					else
					{
						if (user_controlled && player->int_move==I_INTERCEPT && player->int_cnt
							 && !player->tm_strike && (uf1 || uf2))
							 go_to_path(player->tm_player);		// Forced to try special move next cycle...

						if (player->go_cnt && player->dir_mode!=6)
							go_forward(player);

						if (player->tm_trap && player_ref==player_on_off
							 && player->go_cnt<12)
							player->draw_me=FALSE;

						--player->go_cnt;
						if (player->go_cnt<=0)
						{
// Should be at target now!
							player->go_cnt=0;

	  						if (player->int_move==I_CELEB)
	  						{
// Celebration run finished...
	  							init_taunt_act(player);
	  						}
								
							if (player->tm_strike>0 && player->int_move==I_INTERCEPT)
// Begin first touch animation...
							{
								if (player->mface && player->dir_mode!=6)
								{
									player->dir_mode=6;
									player->go_cnt=player->mface_time;
									init_anim(player,MC_STAND);
								}
								else
									init_strike_act(player);
							}
							else
							{
								if ((player->tm_player==KP_A && !(ballx<cntspot_x && shot_pending))
									|| (player->tm_player==KP_B && !(ballx>cntspot_x && shot_pending))
									|| (player->tm_player!=KP_A && player->tm_player!=KP_B))
								{
// Make sure that keeper isn't waiting to make save!
									if (just_scored)
										someone_has_scored(player);
									else
										if (player->int_move==I_OFF)
										{
											player->tm_x=player->go_tx;
											player->tm_y=player->go_ty;
											init_stand_act(player);
										}
										else
										{
											if (player->int_cnt)
												init_stand_act(player);
											else
												find_zonal_target(player,player->tm_x,player->tm_y);	//players x,y for comparison.
	
												}
								}
								else
								{
// Keeper waiting to make save!
									init_stand_act(player);
								}
							}
						}
						else
						{
							if (just_scored>0 && player->int_move!=I_CELEB)
								someone_has_scored(player);		// Target is goal scorer!
						}
					}
				}
			}
			else
// Running with ball!
			{
				if (player->go_cnt)
					go_forward(player);

				--player->go_cnt;
				if (player->go_cnt<=0)
				{
					player->go_cnt=0;
					init_stand_act(player);
				}
				else
				{
					if (ball_in_hands)
					{
						if (player->tm_player==KP_A)
						{
// Keeper A...
							if (keeper_a_in_box)
							{
// Can only take three steps...
								if (!(--keeper_steps))
								{
									game_action=0;
									must_punt=TRUE;
								}
							}
							else
							{
								game_action=0;
								must_punt=TRUE;
							}
						}
	 					else
						{
							if (player->tm_player==KP_B)
// Keeper B...
							{
								if (keeper_b_in_box)
								{
									if (!(--keeper_steps))
									{
										game_action=0;
										must_punt=TRUE;
									}
// Can only take three steps...
								}
								else
								{
									game_action=0;
									must_punt=TRUE;
								}
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

void tackle_action(match_player *player)
{
	go_toward_target(player);
	player->go_txdis*=TACKLE_DECEL;
	player->go_tydis*=TACKLE_DECEL;
	if (!player->go_cnt--)
		init_stand_act(player);
}

/******************************************************************************
*****************************************************************************/

void save_action(match_player *player)
{
	if ((player->tm_player==KP_A && keeper_a_in_box)
		|| (player->tm_player==KP_B && keeper_b_in_box))
	{
		player->tm_x+=player->go_txdis;
		player->tm_y+=player->go_tydis;
	}
	else
	{
		seconds++;
	}

	if (player->tm_anim>=MC_AFOOTB && player->tm_anim<=MC_AJUMPC && player->tm_frm>keeper_contact)
	{
// Slow him down after ball contact in zone A...
		player->go_txdis=player->go_txdis*SAVE_DECEL;
		player->go_tydis=player->go_tydis*SAVE_DECEL;
	}

/*WAIT for mcap data*/
/* If keeper lands on ground slow him down...*/

	if (!player->go_cnt--)
	{
		player->go_txdis=player->go_txdis*SAVE_DECEL;
		player->go_tydis=player->go_tydis*SAVE_DECEL;
		player->go_cnt=0;
		player->tm_fstep=0;
		player->tm_frm=.9999;
		if ((!keeper_on_grnd) || (keeper_on_grnd && player->int_cnt<=1))
		{
			shot_acknowledged=FALSE;
			player->go_cnt=0;
			init_stand_act(player);
		}
	}
}

/******************************************************************************
*****************************************************************************/

void fall_action(match_player *player)
{
	go_toward_target(player);
	player->go_txdis*=TACKLE_DECEL;
	player->go_tydis*=TACKLE_DECEL;
	player->go_cnt--;

	if (player->go_cnt==1)
	{
		init_anim(player,MC_GETUPF);
		player->tm_fstep*=((float)(player->tm_rate+128)/128);
		player->tm_limbo=1/player->tm_fstep;
	}
	else
		if (!player->go_cnt)
			init_stand_act(player);
}

/******************************************************************************
*****************************************************************************/

void init_tussles()
{
	tussle_ptr=&tussle_tab[0];
	*tussle_ptr=0;
}

/******************************************************************************
*****************************************************************************/

void tussle_collision(match_player *p1,match_player *p2)
{
	float xoff,yoff,dist;

	xoff=(p2->tm_x)-(p1->tm_x);
	yoff=(p2->tm_y)-(p1->tm_y);

	dist=calc_dist(xoff,yoff);

	if (dist<prat*0.7)
	{

// Sub vectors to get force of collision!
		float ef_xd=((p1->tm_pow*p1->go_txdis)-(p2->tm_pow*p2->go_txdis));
		float ef_yd=((p1->tm_pow*p1->go_tydis)-(p2->tm_pow*p2->go_tydis));
		int force=ABS(ef_xd)+ABS(ef_yd);
		
// Add averaged vector!
		ef_xd=(p1->go_txdis)+(p2->go_txdis);
		ef_yd=(p1->go_tydis)+(p2->go_tydis);
		int power=(p1->tm_pow+(p1->tm_act==STEAL_ACT ? 32:0)+(p1->tm_act==SAVE_ACT ? 500:0))
					 -(p2->tm_pow+(p2->tm_act==STEAL_ACT ? 32:0)+(p2->tm_act==SAVE_ACT ? 500:0));

		if (power+(seed/2)-32<0)
// Player 1 is shoved!
		{
			if (p2->tm_anim==MC_RUN)
			{
// Player 2 can barge run!
				init_anim(p2,MC_BARGE);
				p2->tm_barge=20;
			}

			if (p2->tm_player==KP_B)
				force*=2;

			if (p2->tm_act==SAVE_ACT)
				force+=128*16;

// Update current movement!
			if (force/16>seed && (!(seed&3) || p2->tm_act==SAVE_ACT))
			{
				float d=calc_dist(ef_xd,ef_yd);
				p1->tm_xdis=ef_xd/d;
				p1->tm_ydis=ef_yd/d;
				init_fall(p1);
				if (p2->tm_act==SAVE_ACT && (p2->tm_poss+2)*32<((float)seed*ref_strictness/128))
				{
					man_down=TRUE;
					init_foul(p2->tm_player,TRUE);	// pass no. of fouler.
				}
				else
				{
					p1->tm_x+=(ef_xd);
					p1->tm_y+=(ef_yd);

					if ((p1->tm_act==RUN_ACT) || (p1->tm_act==JUMP_ACT))
					{
						p1->tm_x-=(p1->go_txdis);
						p1->tm_y-=(p1->go_tydis);
					}
				}
			}
			else
			{
				p1->tm_x+=(ef_xd);
				p1->tm_y+=(ef_yd);

				if ((p1->tm_act==RUN_ACT) || (p1->tm_act==JUMP_ACT))
				{
					p1->tm_x-=(p1->go_txdis);
					p1->tm_y-=(p1->go_tydis);
				}
			}
		}
		else
// Player 2 is shoved!
		{
			if (p1->tm_anim==MC_RUN)
			{
// Player 1 can barge run!
				init_anim(p1,MC_BARGE);
				p1->tm_barge=20;
			}

// Update current movement!
			if (force/16>seed && (!(seed&3) || p2->tm_act==SAVE_ACT))
			{
				float d=calc_dist(ef_xd,ef_yd);
				p2->tm_xdis=ef_xd/d;
				p2->tm_ydis=ef_yd/d;
				init_fall(p2);
				if (p1->tm_act==SAVE_ACT && (p1->tm_poss+2)*32<((float)seed*ref_strictness/128))
				{
					man_down=TRUE;
					init_foul(p1->tm_player,TRUE);	// pass no. of fouler.
				}
			}
			else
			{
				p2->tm_x+=(ef_xd);
				p2->tm_y+=(ef_yd);

				if ((p2->tm_act==RUN_ACT) || (p2->tm_act==JUMP_ACT))
				{
					p2->tm_x-=(p2->go_txdis);
					p2->tm_y-=(p2->go_tydis);
				}
			}
		}
	}
}

/******************************************************************************
*****************************************************************************/

void player_tussles()
{
	int p=0;
	int p1,p2,op;
	char same_team=FALSE;
	while ((tussle_ptr!=&tussle_tab[p]) && (!same_team))
	{
		p1=tussle_tab[p++];
		op=p;
		same_team=TRUE;
		while (tussle_ptr!=&tussle_tab[op])
		{
			p2=tussle_tab[op++];
			if (((p1<12) && (p2>11)) || ((p1>11) && (p2<12)))
			{
				same_team=FALSE;
				tussle_collision(&teams[p1-1],&teams[p2-1]);
			}
		}
	}
}

/******************************************************************************
*****************************************************************************/

void inline add_to_tussle_list(int pnum)
{
	*tussle_ptr++=pnum;
}

/******************************************************************************
*****************************************************************************/

void do_action()
{
	switch(teams[player_num-1].tm_act)
	{
		case STAND_ACT:
			stand_action(&teams[player_num-1]);
			break;

		case RUN_ACT:
			run_action(&teams[player_num-1]);
			break;
/*
		case TURN_ACT:
			turn_action(&teams[player_num-1]);
			break;
*/
		case TACKLE_ACT:
			tackle_action(&teams[player_num-1]);
			break;

		case FALL_ACT:
			fall_action(&teams[player_num-1]);
			break;

		case JUMP_ACT:
			jump_action(&teams[player_num-1]);
			break;

		case SAVE_ACT:
			save_action(&teams[player_num-1]);
			break;

		case THROW_ACT:
			throw_action(&teams[player_num-1]);
			break;

		case KPHOLD_ACT:
			kphold_action(&teams[player_num-1]);
			break;

		case STEAL_ACT:
			steal_action(&teams[player_num-1]);
			break;

		case KICK_ACT:
			kick_action(&teams[player_num-1]);
			break;

		case CELEB_ACT:
			celeb_action(&teams[player_num-1]);
			break;

		case CONTROL_ACT:
			control_action(&teams[player_num-1]);
			break;

		case STRIKE_ACT:
			strike_action(&teams[player_num-1]);
			break;

		case WAIT_ACT:
			wait_action(&teams[player_num-1]);
			break;

		case PICKUP_ACT:
			pickup_action(&teams[player_num-1]);
			break;

		case STOP_ACT:
			stop_action(&teams[player_num-1]);
			break;
	}
}

/******************************************************************************
*****************************************************************************/

void new_dir(match_player *player,float x,float y)
{
	float d=calc_dist(x,y);
	float max;

// get maximum turn.
	max=MAX_TURN;

// get new normalised vector.
	float nx=x/d;
	float ny=y/d;

	float ox=player->tm_xdis;
	float oy=player->tm_ydis;
		
// get difference (cos a).
	float dif=((nx*ox)+(ny*oy));

	if (dif<cos(max))
	{
			
// Which way to turn?
		if ((nx*oy)>(ny*ox))
			max=-max;
		
		nx=(ox*cos(max))-(oy*sin(max));
		ny=(oy*cos(max))+(ox*sin(max));

// Error Correction...
		d=calc_dist(nx,ny);
		nx=nx/d;
		ny=ny/d;

		if (ny>1)
		{
			ny=1;
			nx=0;
		}

		if (ny<-1)
		{
			ny=-1;
			nx=0;
		}

		if (nx>1)
		{
			nx=1;
			ny=0;
		}

		if (nx<-1)
		{
			nx=-1;
			ny=0;
		}
	}

	player->tm_xdis=nx;
	player->tm_ydis=ny;
	player->face_dir=get_dir(player->tm_xdis,player->tm_ydis);
}

/******************************************************************************
*****************************************************************************/

void dir_movement(match_player *player)
{
	float x,y;

	if (user_controlled && !player->tm_act && player->tm_player==ball_poss)
	{
		x=player->tm_xdis*10;
		y=player->tm_ydis*10;
	}
	else
	{
		x=player->go_tx-player->tm_x;
		y=player->go_ty-player->tm_y;
	}

	if ((x!=0) || (y!=0))
		new_dir(player,x,y);
}

/******************************************************************************
*****************************************************************************/

void dir_ball(match_player *player)
{
	float x=ballx-player->tm_x;
	float y=bally-player->tm_y;
	if ((x!=0) || (y!=0))
		new_dir(player,x,y);
}

/******************************************************************************
*****************************************************************************/

void dir_new_d(match_player *player)
{
	new_dir(player,newdx,newdy);
}

/******************************************************************************
*****************************************************************************/

void dir_must_face(match_player *player)
{
	new_dir(player,player->mface_x,player->mface_y);
}

/******************************************************************************
*****************************************************************************/

void dir_away(match_player *player)
{
	float x;
	float y=0;

	if (player->tm_player<12)
		x=1;
	else
		x=-1;

	new_dir(player,x,y);
}

/******************************************************************************
*****************************************************************************/

void select_hlite(match_player *player,short u)
{
	player->tm_hcol=u-1;				// Highlight colour.
	if (ball_poss==player->tm_player)
	{
		if (in_cross_area)
			player->tm_htype=HLITE_CROSS;
		else
			if (player->tm_srng)
				player->tm_htype=HLITE_SHOOT;
			else
				player->tm_htype=HLITE_BALL;
	}
	else
	{
		if (player->special>0 && player->int_move==I_INTERCEPT)
			player->tm_htype=HLITE_SPECIAL;
		else
			if (player->special<0 && player->int_move==I_INTERCEPT)
				player->tm_htype=HLITE_STAR;
			else
				player->tm_htype=HLITE_NORM;
	}
}

/******************************************************************************
*****************************************************************************/

void user_conts(match_player *player)
{
	short u=player->control;
	if (u)
	{
		ux=users_dir[u-1].x;
		uy=users_dir[u-1].y;
		um=users_dir[u-1].m;

		if (users_dir[u-1].f&1)
		{
			uf1=TRUE;
			if (player->tm_player==KP_B)
				uf1++;
		}
		else
			uf1=FALSE;

		if (users_dir[u-1].f&2)
		{
			uf2=TRUE;
		}
		else
		{
			uf2=FALSE;
		}

		if (uf1 || uf2)
		{
	// Any fire buttons pressed?
			if (users[u-1].chng)
	// Just been selected... wait for release of buttons...
			{
				uf1=FALSE;
				uf2=FALSE;
			}
		}
		else
		{
			if (users[u-1].chng)
	// Buttons released...
				users[u-1].chng=FALSE;
		}

#ifdef FORCE_SELECT

#ifdef EURO96
		if (uf2 && uf1 && player->tm_dist>FSELECT_DIST && users[u-1].type<0)
#endif

#ifndef EURO96
		if (uf2 && player->tm_dist>FSELECT_DIST && users[u-1].type<0)
#endif
		{
			uf1=FALSE;
			uf2=FALSE;

			if ((forced>>(u-1))&1)
	 			forced-=1<<(u-1);
			else
	 			forced+=1<<(u-1);
		}
		else
			if ((forced>>(u-1))&1)
		 		forced-=1<<(u-1);
#endif
	}
}
/******************************************************************************
*****************************************************************************/

void process_dir(match_player *player)
{
	switch(player->dir_mode)
	{
		case(0):
			dir_movement(player);
			break;

		case(-1):
			dir_movement(player);
			player->dir_mode=1;
			break;

		case(1):
			dir_ball(player);
			break;

		case(2):
			player->face_dir=get_dir(player->tm_xdis,player->tm_ydis);
			break;

		case(3):
			dir_away(player);
			break;

		case(4):
			player->face_dir=get_dir(player->tm_xdis,player->tm_ydis);
			player->dir_mode=0;
			break;

		case(5):
			dir_new_d(player);
			break;

		case(6):
			dir_must_face(player);
			break;

	};
}

/******************************************************************************
*****************************************************************************/

void init_stand_anim(match_player *player)
{
	player->tm_anim=MC_STAND;
	player->tm_newanim=TRUE;
	player->tm_frm=0;
	player->tm_fstep=MC_STAND_FS;
}

/******************************************************************************
*****************************************************************************/

void init_penalty_anim(match_player *player)
{
	if (player->tm_anim!=MC_PENALTY)
	{
		player->tm_anim=MC_PENALTY;
		player->tm_newanim=TRUE;
		player->tm_frm=0;
		player->tm_fstep=MC_PENALTY_FS;
	}
}

/******************************************************************************
*****************************************************************************/

void init_shame_anim(match_player *player)
{
	player->tm_anim=MC_SHAMEW;
	player->tm_newanim=TRUE;
	player->tm_frm=0;
	player->tm_fstep=MC_SHAMEW_FS;
}

/******************************************************************************
*****************************************************************************/

void init_standb_anim(match_player *player)
{
	player->tm_anim=MC_STANDB;
	player->tm_newanim=TRUE;
	player->tm_frm=0;
	player->tm_fstep=MC_STANDB_FS;
}

/******************************************************************************
*****************************************************************************/

void init_barge_anim(match_player *player)
{
// Always go from run animation to barge!

	player->tm_anim=MC_BARGE;
	player->tm_fstep=MC_BARGE_FS*(actual_spd(player)/MC_RUN_SPD);
	player->tm_frm+=0.5;
}

/******************************************************************************
*****************************************************************************/

void init_run_anim(match_player *player)
{
	if (!player->tm_barge || player->tm_anim!=MC_BARGE)
	{
// Not barging!!!
		if (user_controlled && uf2)
			player->tm_fstep=(MC_RUN_FS*(actual_spd(player)/MC_RUN_SPD))*1.2;
		else
			player->tm_fstep=MC_RUN_FS*(actual_spd(player)/MC_RUN_SPD);
	
		if (ABS((int)player->tm_anim)==MC_JOG)
		{
// Tween to run from jog....
			player->tm_anim=MC_RUN;
			player->tm_frm+=0.4;
		}
		else
		{
			if (ABS((int)player->tm_anim)!=MC_RUN)
			{
				player->tm_anim=MC_RUN;
				player->tm_newanim=TRUE;
				player->tm_frm=0;
			}
		}	
	}
}

/******************************************************************************
*****************************************************************************/

void init_jog_anim(match_player *player)
{
	player->tm_fstep=MC_JOG_FS*((actual_spd(player)/2)/MC_JOG_SPD);

	if (ABS((int)player->tm_anim)==MC_RUN)
	{
// Tween to jog from run....
		player->tm_anim=MC_JOG;
		player->tm_frm+=0.7;
	}
	else
	{
		if (ABS((int)player->tm_anim)==MC_BARGE)
		{
			player->tm_anim=MC_JOG;
		}
		else
		{
			if (ABS((int)player->tm_anim)!=MC_JOG)
			{
				player->tm_anim=MC_JOG;
				player->tm_newanim=TRUE;
				player->tm_frm=0;
			}
		}
	}
}

/******************************************************************************
*****************************************************************************/

void init_shoot_anim(match_player *player)
{
	player->tm_fstep=MC_SHOOT_FS;
	double n;

	if ((AFEQS(player->tm_anim,MC_RUN)) ||
		(AFEQS(player->tm_anim,MC_JOG)))
	{
		if (modf(player->tm_frm,&n)>0.5)
		{
// Left Footed Shot...
			player->tm_anim=MC_SHOOTL;
			player->tm_newanim=TRUE;
			player->tm_frm-=0.5;
		}
		else
		{
// Right Footed Shot...
			player->tm_anim=MC_SHOOTR;
			player->tm_newanim=TRUE;
		}
	}
	else
	{
// Right Footed Shot...
			player->tm_anim=MC_SHOOTR;
			player->tm_newanim=TRUE;
			player->tm_frm=0;
	}
}

/******************************************************************************
*****************************************************************************/

void init_kick_anim(match_player *player,int a)
{
	int an=a;
	double n;
	float t;
	float f;

	if (AFEQS(player->tm_anim,MC_RUN))
		t=modf(player->tm_frm,&n);
	else	
		if (AFEQS(player->tm_anim,MC_JOG) || AFEQS(player->tm_anim,MC_BARGE))
			t=modf((player->tm_frm+0.5),&n);

	if ((AFEQS(player->tm_anim,MC_JOG)) || (AFEQS(player->tm_anim,MC_RUN)) || (AFEQS(player->tm_anim,MC_BARGE)))
	{
		switch(a)
		{
			case(MC_PASSL):
			case(MC_CHIPL):
			case(MC_BACKHEELL):
				if (t>=0.3 && t<0.8)
				{
// Right Footed...
					t=(t-0.3);
					an-=1;
				}
				else
				{
// Left Footed...
					if (t<0.3)
						t=(t+0.2);
					else
						t=(t-0.8);
				}

				switch(a)
				{
					case(MC_TOEL):
						f=0.7;
						break;

					default:
						f=0.8;
						break;
				}

				player->tm_anim=ABS(an);
				player->tm_newanim=TRUE;
				player->tm_frm=(t*f);
				break;

			case(MC_SHOOTL):
			case(MC_CROSSL):
				if (t>=0.25 && t<0.75)
				{
// Right Footed...
					t=(t-0.25);
					an-=1;
				}
				else
				{
// Left Footed...
					if (t<0.25)
						t=(t+0.25);
					else
						t=(t-0.75);
				}

				switch(a)
				{
					case(MC_SHOOTL):
						f=0.6;
						break;

					case(MC_CROSSL):
						f=0.5;
						break;
				}

				player->tm_anim=ABS(an);
				player->tm_newanim=TRUE;
				player->tm_frm=(t*f);
				break;

		}
	}
	else
	{
// Right Footed...
		player->tm_anim=ABS(an);
		player->tm_newanim=TRUE;
		player->tm_frm=0;
	}

	switch(a)
	{
		case(MC_PASSL):
			player->tm_fstep=MC_PASS_FS;
			break;
		case(MC_CHIPL):
			player->tm_fstep=MC_CHIP_FS;
			break;
		case(MC_BACKHEELL):
			player->tm_fstep=MC_BACKHEEL_FS;
			break;
		case(MC_SHOOTL):
			player->tm_fstep=MC_SHOOT_FS;
			break;
		case(MC_CROSSL):
			player->tm_fstep=MC_CROSS_FS;
			break;
	}		
}

/******************************************************************************
*****************************************************************************/

void init_kick_l_anim(match_player *player,int a)
{
	int an=a;
	double n;
	float t;

	if (AFEQS(player->tm_anim,MC_RUN))
		t=modf(player->tm_frm,&n);
	else	
		if (AFEQS(player->tm_anim,MC_JOG))
			t=modf((player->tm_frm+0.5),&n);

	if ((AFEQS(player->tm_anim,MC_JOG)) || (AFEQS(player->tm_anim,MC_RUN)))
	{
// Left Footed...
		if (t<0.3)
			t=(t+0.2);
		else
			if (t>0.8)
				t=(t-0.8);
			else
				t=0;

		player->tm_frm=(t*0.8);
	}
	else
		player->tm_frm=0;

	player->tm_anim=ABS(an);
	player->tm_newanim=TRUE;

	switch(an)
	{
		case(MC_DIAGPASSL):
			player->tm_fstep=MC_DIAGPASS_FS;
			break;
		case(MC_DIAGBACKL):
			player->tm_fstep=MC_DIAGBACK_FS;
			break;
		case(MC_SIDEPASSL):
			player->tm_fstep=MC_SIDEPASS_FS;
			break;
	}
}

/******************************************************************************
*****************************************************************************/

void init_kick_r_anim(match_player *player,int a)
{
	int an=a;
	double n;
	float t;

	if (AFEQS(player->tm_anim,MC_RUN))
		t=modf(player->tm_frm,&n);
	else	
		if (AFEQS(player->tm_anim,MC_JOG))
			t=modf((player->tm_frm+0.5),&n);

	if ((AFEQS(player->tm_anim,MC_JOG)) || (AFEQS(player->tm_anim,MC_RUN)))
	{
		if (t>=0.3 && t<0.8)
		{
// Right Footed...
			t=(t-0.3);
		}
		else
			t=0;

		player->tm_frm=(t*0.8);
	}
	else
		player->tm_frm=0;

	player->tm_anim=ABS(an);
	player->tm_newanim=TRUE;

	switch(an)
	{
		case(MC_DIAGPASSR):
			player->tm_fstep=MC_DIAGPASS_FS;
			break;
		case(MC_DIAGBACKR):
			player->tm_fstep=MC_DIAGBACK_FS;
			break;
		case(MC_SIDEPASSR):
			player->tm_fstep=MC_SIDEPASS_FS;
			break;
	}
}

/******************************************************************************
*****************************************************************************/

void init_trap_anim(match_player *player)
{
	player->tm_fstep=MC_TRAP_FS*fstep_factor(player->tm_cont);
	player->tm_frm=0;
	player->tm_newanim=TRUE;
	double n;

	if (AFEQS(player->tm_anim,MC_RUN))
	{
		if (modf(player->tm_frm,&n)>=0.4 && modf(player->tm_frm,&n)<0.9)
		{
// Left Footed Trap...
			player->tm_anim=MC_TRAPL;
		}
		else
		{
// Right Footed Trap...
			player->tm_anim=MC_TRAPR;
		}
	}
	else
	{
// Right Footed Trap...
			player->tm_anim=MC_TRAPR;
	}
}

/******************************************************************************
*****************************************************************************/

void init_ride_anim(match_player *player)
{
	double n;
	float t;

	if (AFEQS(player->tm_anim,MC_RUN))
		t=modf(player->tm_frm,&n);
	else	
		if (AFEQS(player->tm_anim,MC_JOG))
			t=modf((player->tm_frm+0.5),&n);

	if ((AFEQS(player->tm_anim,MC_JOG)) || (AFEQS(player->tm_anim,MC_RUN)))
	{
		if (t>=0.35 && t<0.85)
		{
// Left Footed...
			player->tm_anim=MC_RIDEL;
			player->tm_newanim=TRUE;
			t=(t-0.35);
		}
		else
		{
// Right Footed...
			player->tm_anim=MC_RIDER;
			player->tm_newanim=TRUE;
			if (t>=0.85)
				t=t-0.85;
			else
				t=t+0.15;
		}
		player->tm_frm=(t*2/5);
	}
	else
	{
		player->tm_frm=0;
		player->tm_anim=MC_RIDEL;
		player->tm_newanim=TRUE;
	}

// Player's speed and flair determine how fast he rides tackle...
	float f=(player->tm_flair+player->tm_rate)/2;
	f=MC_RIDE_FS+(0.000536*f);
	player->tm_fstep=f;
}

/******************************************************************************
*****************************************************************************/

void init_tack_anim(match_player *player)
{
	player->tm_fstep=MC_S_TACKLE_FS;
	player->tm_anim=MC_S_TACKLE;
	player->tm_newanim=TRUE;
	player->tm_frm=0;
}

/******************************************************************************
*****************************************************************************/

void init_shdr_anim(match_player *player)
{
	if ((ABS((int)player->tm_anim)!=MC_S_HEAD) && (ABS((int)player->tm_anim)!=MC_J_HEAD))
	{
		player->tm_fstep=MC_S_HEAD_FS*fstep_factor(player->tm_flair);
		player->tm_anim=MC_S_HEAD;
		player->tm_newanim=TRUE;
		player->tm_frm=0;
	}
}

/******************************************************************************
*****************************************************************************/

void init_jhdr_anim(match_player *player)
{
	player->tm_fstep=MC_J_HEAD_FS*fstep_factor(player->tm_flair);
	player->tm_anim=MC_J_HEAD;
	player->tm_newanim=TRUE;
	player->tm_frm=0;
}

/******************************************************************************
*****************************************************************************/

void init_dhdr_anim(match_player *player)
{
	player->tm_fstep=MC_DV_HEAD_FS*fstep_factor(player->tm_flair);
	player->tm_anim=MC_DV_HEAD;
	player->tm_newanim=TRUE;
	player->tm_frm=0;
}

/******************************************************************************
*****************************************************************************/

void init_ohd_anim(match_player *player)
{
	player->tm_fstep=MC_OVERHEAD_FS*fstep_factor(player->tm_flair);
	player->tm_anim=MC_OVERHEAD;
	player->tm_newanim=TRUE;
	player->tm_frm=0;
}

/******************************************************************************
*****************************************************************************/

void init_voll_anim(match_player *player)
{
	player->tm_fstep=MC_VOLLEY_FS*fstep_factor(player->tm_flair);
	player->tm_anim=MC_VOLLEYL;
	player->tm_newanim=TRUE;
	player->tm_frm=0;
}

/******************************************************************************
*****************************************************************************/

void init_fallr_anim(match_player *player)
{
	player->tm_fstep=MC_FALLR_FS;
	player->tm_anim=MC_FALLR;
	player->tm_newanim=TRUE;
	player->tm_frm=0;
}

/******************************************************************************
*****************************************************************************/

void init_chest_anim(match_player *player)
{
	player->tm_fstep=MC_CHEST_FS*fstep_factor(player->tm_cont);
	player->tm_anim=MC_CHEST;
	player->tm_newanim=TRUE;
	player->tm_frm=0;
}

/******************************************************************************
*****************************************************************************/

void init_dnhead_anim(match_player *player)
{
	player->tm_fstep=MC_D_HEAD_FS*fstep_factor(player->tm_cont);
	player->tm_anim=MC_D_HEAD;
	player->tm_newanim=TRUE;
	player->tm_frm=0;
}

/******************************************************************************
*****************************************************************************/

void init_getupf_anim(match_player *player)
{
	player->tm_fstep=MC_GETUPF_FS;
	player->tm_anim=MC_GETUPF;
	player->tm_newanim=TRUE;
	player->tm_frm=0;
}

/******************************************************************************
*****************************************************************************/

void init_getup_anim(match_player *player)
{
	player->tm_fstep=MC_GETUP_FS;
	player->tm_anim=MC_GETUP;
	player->tm_newanim=TRUE;
	player->tm_frm=0;
}

/******************************************************************************
*****************************************************************************/

void init_save_anim(match_player *player,int an)
{
	player->tm_anim=ABS(an);
	player->tm_newanim=TRUE;
	player->tm_frm=0;
}

/******************************************************************************
*****************************************************************************/

void init_bounce_anim(match_player *player)
{
	player->tm_anim=MC_BOUNCE;
	player->tm_newanim=TRUE;
	player->tm_frm=0;
	player->tm_fstep=MC_BOUNCE_FS;
}

/******************************************************************************
*****************************************************************************/

void init_kout_anim(match_player *player)
{
	player->tm_anim=MC_KICKOUT;
	player->tm_newanim=TRUE;
	player->tm_frm=0;
	player->tm_fstep=MC_KICKOUT_FS;
}

/******************************************************************************
*****************************************************************************/

void init_hvoll_anim(match_player *player)
{
	player->tm_anim=MC_HALFVOLL;
	player->tm_newanim=TRUE;
	player->tm_frm=0;
	player->tm_fstep=MC_HALFVOLL_FS;
}

/******************************************************************************
*****************************************************************************/

void init_throw_anim(match_player *player)
{
	player->tm_anim=MC_THROW;
	player->tm_newanim=TRUE;
	player->tm_frm=0;
	player->tm_fstep=MC_THROW_FS;
}

/******************************************************************************
*****************************************************************************/

void init_roll_anim(match_player *player)
{
	player->tm_anim=MC_ROLL;
	player->tm_newanim=TRUE;
	player->tm_frm=0;
	player->tm_fstep=MC_ROLL_FS;
}

/******************************************************************************
*****************************************************************************/

void init_runb_anim(match_player *player)
{
	player->tm_anim=MC_RUNWITHB;
	player->tm_newanim=TRUE;
	player->tm_frm=0;
	player->tm_fstep=MC_RUNWITHB_FS;
}

/******************************************************************************
*****************************************************************************/

void init_waveup_anim(match_player *player)
{
	player->tm_anim=MC_WAVEUP;
	player->tm_newanim=TRUE;
	player->tm_frm=0;
	player->tm_fstep=MC_WAVEUP_FS;
}

/******************************************************************************
*****************************************************************************/

void init_throwl_anim(match_player *player)
{
	player->tm_anim=MC_THROWL;
	player->tm_newanim=TRUE;
	player->tm_frm=0.02;
	player->tm_fstep=MC_THROWL_FS;
}

/******************************************************************************
*****************************************************************************/

void init_throws_anim(match_player *player)
{
	player->tm_anim=MC_THROWS;
	player->tm_newanim=TRUE;
	player->tm_frm=0.02;
	player->tm_fstep=MC_THROWS_FS;
}

/******************************************************************************
*****************************************************************************/

void init_crtostb_anim(match_player *player)
{
	player->tm_anim=MC_CRTOSTB;
	player->tm_newanim=TRUE;
	player->tm_frm=0;
	player->tm_fstep=MC_CRTOSTB_FS;
}

/******************************************************************************
*****************************************************************************/

void init_crl_anim(match_player *player)
{
	player->tm_anim=MC_CROSSL;
	player->tm_newanim=TRUE;
	player->tm_frm=0;
	player->tm_fstep=MC_CROSS_FS;
}
/******************************************************************************
*****************************************************************************/

void init_crr_anim(match_player *player)
{
	player->tm_anim=MC_CROSSR;
	player->tm_newanim=TRUE;
	player->tm_frm=0;
	player->tm_fstep=MC_CROSS_FS;
}

/******************************************************************************
*****************************************************************************/

void init_tostand_anim(match_player *player,int an)
{
	player->tm_anim=ABS(an);
	player->tm_newanim=TRUE;
	player->tm_frm=0;
	player->tm_fstep=MC_STOS_FS;
}

/******************************************************************************
*****************************************************************************/

void init_tostandb_anim(match_player *player,int an)
{
	player->tm_anim=ABS(an);
	player->tm_newanim=TRUE;
	player->tm_frm=0;
	player->tm_fstep=MC_STOSB_FS;
}

/******************************************************************************
*****************************************************************************/

void init_socks_anim(match_player *player,int an)
{
	player->tm_anim=ABS(an);
	player->tm_newanim=TRUE;
	player->tm_frm=0;
	player->tm_fstep=MC_SOCKS_FS;
}

/******************************************************************************
*****************************************************************************/

void init_celeb_anim(match_player *player,int an)
{
	player->tm_anim=ABS(an);
	player->tm_newanim=TRUE;
	player->tm_frm=0;
	switch(an)
	{
		case(MC_CELEB):
			player->tm_fstep=MC_CELEB_FS;
			break;

		case(MC_PUMP):
			player->tm_fstep=MC_PUMP_FS;
			break;

		case(MC_BABY):
			player->tm_fstep=MC_BABY_FS;
			break;

		case(MC_REEVES):
			player->tm_fstep=MC_REEVES_FS;
			break;

		case(MC_MILLER):
			player->tm_fstep=MC_MILLER_FS;
			break;

		case(MC_PLANE):
			player->tm_fstep=MC_PLANE_FS;
			break;

		case(MC_FINGER):
			player->tm_fstep=MC_FINGER_FS;
			break;

		case(MC_KNEE):
			player->tm_fstep=MC_KNEE_FS;
			break;

		case(MC_MOON):
			player->tm_fstep=MC_MOON_FS;
			break;

		case(MC_DUCK):
			player->tm_fstep=MC_DUCK_FS;
			break;
	}
}

/******************************************************************************
*****************************************************************************/

void init_pickup_anim(match_player *player)
{
	player->tm_anim=MC_PICKBALL;
	player->tm_newanim=TRUE;
	player->tm_frm=0;
	player->tm_fstep=MC_PICKBALL_FS;
}

/******************************************************************************
*****************************************************************************/

void init_trot_anim(match_player *player)
{
	float x=player->go_tx-player->tm_x;
	float y=player->go_ty-player->tm_y;

	float d=calc_dist(x,y);
// d is effective speed!
	player->tm_fstep=actual_spd(player)*MC_TROTA_FS/2;

	x=x/d;
	y=y/d;

	float nx=(x*player->tm_xdis)+(y*player->tm_ydis);
	float ny=(y*player->tm_xdis)-(x*player->tm_ydis);

	if (player->tm_anim<MC_TROTB || player->tm_anim>MC_TROTE)
// Not currently in trot animation...
	{
		player->tm_frm=0;
		player->tm_newanim=TRUE;
	}
	
	switch((1+get_dir(nx,ny)))
	{
		case(8):
			player->tm_anim=MC_TROTF;
			break;

		case(7):
			player->tm_anim=MC_TROTG;
			break;

		case(6):
			player->tm_anim=MC_TROTH;
			break;

		case(5):
			player->tm_anim=MC_TROTA;
			break;

		case(4):
			player->tm_anim=MC_TROTB;
			break;

		case(3):
			player->tm_anim=MC_TROTC;
			break;

		case(2):
			player->tm_anim=MC_TROTD;
			break;

		case(1):
			player->tm_anim=MC_TROTE;
			break;
	}
}

/******************************************************************************
*****************************************************************************/

void init_anim(match_player *player,int an)
{
/*
	if (player->tm_act==STAND_ACT)
	{
// Prevent temporary jump to stand animation!
		player->tm_anim=player->ls_anim;
		player->tm_frm=player->ls_frm;
	}
*/	
	if (an>=MC_AFOOTB && an<=MC_CJUMPBR)
	{
		init_save_anim(player,an);
	}
	else
	{
		switch(an)
		{
			case(MC_PASSL):
			case(MC_CHIPL):
			case(MC_SHOOTL):
			case(MC_BACKHEELL):
				init_kick_anim(player,an);
				break;

			case(MC_DIAGPASSL):
			case(MC_DIAGBACKL):
			case(MC_SIDEPASSL):
				init_kick_l_anim(player,an);
				break;

			case(MC_CROSSL):
				init_crl_anim(player);
				break;

			case(MC_CROSSR):
				init_crr_anim(player);
				break;

			case(MC_DIAGPASSR):
			case(MC_DIAGBACKR):
			case(MC_SIDEPASSR):
				init_kick_r_anim(player,an);
				break;

			case(MC_STOSL):
			case(MC_STOSR):
				init_tostand_anim(player,an);
				break;

			case(MC_STOSBL):
			case(MC_STOSBR):
				init_tostandb_anim(player,an);
				break;

			case(MC_CRTOSTB):
				init_crtostb_anim(player);
				break;

			case(MC_STAND):
				init_stand_anim(player);
				break;

			case(MC_PENALTY):
#ifdef EURO96
				init_penalty_anim(player);
#else
				init_stand_anim(player);
#endif
				break;

			case(MC_SHAME):
				init_shame_anim(player);
				break;

			case(MC_TRAPL):
				init_trap_anim(player);
				break;

			case(MC_CHEST):
				init_chest_anim(player);
				break;

			case(MC_D_HEAD):
				init_dnhead_anim(player);
				break;

			case(MC_BARGE):
				init_barge_anim(player);
				break;

			case(MC_RUN):
				init_run_anim(player);
				break;

			case(MC_JOG):
				init_jog_anim(player);
				break;

			case(MC_TROTA):
				init_trot_anim(player);
				break;

			case(MC_S_TACKLE):
				init_tack_anim(player);
				break;

			case(MC_DV_HEAD):
				init_dhdr_anim(player);
				break;

			case(MC_S_HEAD):
				init_shdr_anim(player);
				break;

			case(MC_J_HEAD):
				init_jhdr_anim(player);
				break;

			case(MC_OVERHEAD):
				init_ohd_anim(player);
				break;

			case(MC_VOLLEYL):
				init_voll_anim(player);
				break;

			case(MC_FALLR):
				init_fallr_anim(player);
				break;

			case(MC_GETUPF):
				init_getupf_anim(player);
				break;

			case(MC_GETUP):
				init_getup_anim(player);
				break;

			case(MC_RIDEL):
				init_ride_anim(player);
				break;

			case(MC_SOCKSL):
			case(MC_SOCKSR):
				init_socks_anim(player,an);
				break;

			case(MC_CELEB):
			case(MC_KNEE):
			case(MC_DUCK):
			case(MC_MOON):
			case(MC_MILLER):
			case(MC_BABY):
			case(MC_PUMP):
			case(MC_REEVES):
			case(MC_FINGER):
			case(MC_PLANE):
				init_celeb_anim(player,an);
				break;

			case(MC_PICKBALL):
				init_pickup_anim(player);
				break;

// Keeper specific anims...

			case(MC_STANDB):
				init_standb_anim(player);
				break;

			case(MC_BOUNCE):
				init_bounce_anim(player);
				break;

			case(MC_KICKOUT):
				init_kout_anim(player);
				break;

			case(MC_HALFVOLL):
				init_hvoll_anim(player);
				break;

			case(MC_THROW):
				init_throw_anim(player);
				break;

			case(MC_ROLL):
				init_roll_anim(player);
				break;

			case(MC_RUNWITHB):
				init_runb_anim(player);
				break;

			case(MC_WAVEUP):
				init_waveup_anim(player);
				break;
/*
			case(MC_PENALTY):
				init_penalty_anim(player);
				break;
*/
			case(MC_THROWL):
				init_throwl_anim(player);
				break;

			case(MC_THROWS):
				init_throws_anim(player);
				break;
		}
	}
}

/******************************************************************************
*****************************************************************************/

void process_anims(match_player *player)
{
	if (!(ABS(player->tm_anim)==MC_THROWL && player->tm_frm<0.001))
// Initial throw-in animation is frozen...
		player->tm_frm+=player->tm_fstep;

	if (player->tm_anim==MC_BARGE && player->tm_act==RUN_ACT)
	{
		if (!(--player->tm_barge))
			init_anim(player,MC_RUN);
	}
	else
		player->tm_barge=0;

	if (player->tm_limbo)
	{
		if (!--player->tm_limbo)
		{
// Finished animation...
			int a=ABS(player->tm_anim);
 			switch(a)
			{
				case(MC_KICKOUT):
				case(MC_HALFVOLL):
				case(MC_THROW):
				case(MC_THROWL):
				case(MC_THROWS):
				case(MC_ROLL):
				case(MC_GETUPF):
				case(MC_GETUP):
					init_stand_act(player);
			}
		}
	}
}

/******************************************************************************
******************************************************************************/

// User controls player...

void user_play(int player_num)
{
	user_conts(&teams[player_num-1]);

	override(&teams[player_num-1]);

 	player_ints(&teams[player_num-1]);

 	user_intelligence(&teams[player_num-1]);

	if (!teams[player_num-1].tm_limbo && (ball_limbo_on<=0 || (ball_limbo_on>0 && ball_limbo_p!=player_num)))
	{
	 	player_comment(&teams[player_num-1]);

	 	do_action();
	}
}
	
/******************************************************************************
*****************************************************************************/

// Computer controls player...

void computer_play(int player_num)
{
#ifdef EURO96
	if (setp_taker==player_num && ((player_num<12 && !auto_users_a)
		 || (player_num>11 && !auto_users_b)) && already_there
		 && (match_mode==PEN_KICK_A || match_mode==PEN_KICK_B))
	{
		if (!allow_replay)
			init_replay();

		if (ball_poss!=setp_taker)
			collect_ball(&teams[setp_taker-1]);

// Must be a computer penalty kick...
		if (reselection)
		{
			setp_kick_x=teams[setp_taker-1].tm_xdis;
			setp_kick_y=teams[setp_taker-1].tm_ydis;
			setp_power=0;
			setp_hgt=0;
			setp_byd=cntspot_y;
			setp_bzd=0;
			reselection=FALSE;
		}
		comp_set_piece(&teams[player_num-1]);
	}
	else
#endif
	{
		teams[player_num-1].tm_htype=HLITE_OFF;			// Turn highlight off!

		override(&teams[player_num-1]);

		player_ints(&teams[player_num-1]);

		intelligence(&teams[player_num-1]);

		if (!teams[player_num-1].tm_limbo && (ball_limbo_on<=0 || (ball_limbo_on>0 && ball_limbo_p!=player_num)))
		{
			player_comment(&teams[player_num-1]);

			do_action();
		}
	}
}

/******************************************************************************
*****************************************************************************/

void go_team(int p)
{
	if ((p<12 && (team_a_on || p==KP_A)) || (p>=12 && (team_b_on || p==KP_B)))
	{
		for (player_num=p; player_num<p+players/2; player_num++)
		{
			if (teams[player_num-1].guy_on)
			{

// For debugging purposes...
				if (player_num==10)
				{
					player_num++;
					player_num--;
				}

				process_anims(&teams[player_num-1]);

				if (!teams[player_num-1].tm_limbo && (!ball_limbo_on || (ball_limbo_on && ball_limbo_p!=player_num)))
				{
// He is NOT bound up in animation!!!

					if (!just_thrown)
						ball_interact(&teams[player_num-1]);

					if (just_scored)
						user_controlled=FALSE;
					else
						user_controlled=teams[player_num-1].control;

					if (user_controlled)
					{
// User controls player...
						user_plr=player_num;

						if (match_mode && match_mode!=THROW_IN_A && match_mode!=THROW_IN_B)
						{
							if ((user_taker==user_controlled) && (already_there))
							{
								user_set_piece(&teams[player_num-1]);
								if (!ball_poss)
									teams[player_num-1].tm_leave=-TRUE;
							}
							else
								computer_play(player_num);
						}
						else
							user_play(player_num);
					}
					else
						computer_play(player_num);

					if (teams[player_num-1].tm_act<=TURN_ACT || teams[player_num-1].tm_act==SAVE_ACT)
						add_to_tussle_list(teams[player_num-1].tm_player);
			
					if (!teams[player_num-1].tm_limbo && (!ball_limbo_on || (ball_limbo_on && ball_limbo_p!=player_num)))
					{
						process_dir(&teams[player_num-1]);
					}
				}
			}
		}
	}
}

/******************************************************************************
*****************************************************************************/

void select_all_hlites()
{
	char u;
	short i;
	char hcol=1;
	for (short p=0; p<MAX_NET_USERS; p++)
	{
		if (users[p].control!=NET_CTRL && users[p].control && users[p].type)
		{
// Controlled by a user on this machine...
			if (users[p].type>0)
			{
// Fixed player...
				select_hlite(&teams[users[p].type-1],hcol);
				hcol++;
			}
			else
			{
// Auto-user...
				if (users[p].type==-1)
				{
// Team A...
					for (i=0; i<11; i++)
					{
						if (teams[i].control==(p+1))
						{
// This user...
							select_hlite(&teams[i],hcol);
							break;
						}
					}
					hcol++;
				}
				else
				{
// Team B...
					for (i=11; i<22; i++)
					{
						if (teams[i].control==(p+1))
						{
// This user...
							select_hlite(&teams[i],hcol);
							break;
						}
					}
					hcol++;
				}
			}
		}
	}
}

/******************************************************************************
*****************************************************************************/

void process_teams()
{

	int p;

	init_tussles();

	if (frame)
		p=1;
	else
		p=12;
 
	go_team(p);

	if (p==1)
		p=12;
	else
		p=1;

	go_team(p);

	if (!dead_ball_cnt && !just_scored)
		player_tussles();
}	






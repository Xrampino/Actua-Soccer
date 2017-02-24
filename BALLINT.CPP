/******************************************************************************
*******************************************************************************

Ball-Player interaction routines...

******************************************************************************
*****************************************************************************/

#include <stdio.h>

#include "audio.h"

#include "defines.h"
#include "externs.h"
#include "global.h"
#include "data.h"
#include "3deng.h"

extern capfrm *player_p;
extern mcap *mcaps;

/******************************************************************************
*****************************************************************************/

void out_mcball_coords()
{
	char str1[50];
	float x,y,z;
	short an,cp,frms;
	char ball_in;

	for (an=0; an<117; an++)
	{
		frms=mcaps[an].capfrms;
		ball_in=0;

		for (cp=0; cp<frms; cp++)
		{
			float *p=&player_p[mcaps[an].cappts+(cp)][(23*3)+1];
			if (*(p+1)<0)
			{
// Ball not included...
				if (ball_in)
				{
// Output last pos. of ball...
					sprintf(str1,"%d	Released	frms=%d	cp=%d	x=%1.3f	y=%1.3f	z=%1.3f\n",an,frms,cp,x,y,z);
					printf(str1);
					cp=frms;
				}
			}
			else
			{
				x=*p++;
				z=*p++;
				y=-*p++;
				if (!ball_in)
				{
// Contact...
					sprintf(str1,"%d	contact	frms=%d	cp=%d	x=%1.3f	y=%1.3f	z=%1.3f\n",an,frms,cp,x,y,z);
					printf(str1);
					ball_in=1;
				}
			}
		}

		if (!ball_in)
		{
// Haven't came across ball yet...
			sprintf(str1,"%d	Ball not included.\n",an);
			printf(str1);
		}
	}
}

/******************************************************************************
*****************************************************************************/

void get_mcball_coords(match_player *player)
{
	short an=player->ls_anim;
	float cp=player->ls_frm;
	float *p=&player_p[mcaps[an].cappts+(short)(cp*mcaps[an].capfrms)][(23*3)+1];
	float z=*(p+1);
	if (z>0)
	{
		float x=*p;
		float y=-*(p+2);
		float d=calc_dist(x,y);
		x=x/d;
		y=y/d;
		ballx=player->tm_x+d*((x*player->tm_xdis)-(y*player->tm_ydis));
		bally=player->tm_y+d*((y*player->tm_xdis)+(x*player->tm_ydis));
		ballz=z;
	}
	else
	{
		ballx=player->tm_x;
		bally=player->tm_y;
		ballz=ball_diam/2;
	}
}

/******************************************************************************
*****************************************************************************/

void user_header(match_player *player)
{
	float power;
	if ((uf1) && (!uf2) && (in_header_rng))
	{
		if (um)
		{
// Shoot header in joystick dir.
			power=(abs(angle_to_xy(ux,uy,ballxdis,ballydis)))
					*player->tm_pow/16+(MIN_HEADER_POW/16);

			ballxdis=ux*power;
			ballydis=uy*power;
			ballzdis=1;
			new_shot(player->tm_player);
			launch_ball(-1);			// Set up spin vector.
		}
		else
		{
// head in dir facing.
			power=(abs(angle_to_xy(player->tm_xdis,player->tm_ydis,ballxdis,ballydis)))
					*player->tm_pow/16+(MIN_HEADER_POW/16);

			ballxdis=player->tm_xdis*power;
			ballydis=player->tm_ydis*power;
			ballzdis=1;
			new_shot(player->tm_player);
			launch_ball(1);			// Set up spin vector.
		}
	}

	if ((uf1) && (!uf2) && (!in_header_rng))
	{
		if (um)
		{
// punt header in joystick dir.
			power=(abs(angle_to_xy(ux,uy,ballxdis,ballydis)))
					*player->tm_pow/16+(MIN_HEADER_POW/16);
			ballxdis=ux*power;
			ballydis=uy*power;
			ballzdis=4;
			launch_ball(1);			// Set up spin vector.
		}
		else
		{
// header vertical.
			ballxdis=ballxdis/(player->tm_cont/16);
			ballydis=ballydis/(player->tm_cont/16);
			ballzdis=4+(ball_speed/(player->tm_cont/12));
			launch_ball(0);			// Set up spin vector.
		}
	}

	if ((uf2) && (!uf1))
// Header pass...
	{
		if (um)
		{
// head in joystick dir.
			float x,y;
			x=player->tm_xdis;
			y=player->tm_ydis;
			player->tm_xdis=ux;
			player->tm_ydis=uy;						// Force joystick as orientation!

			int p=pass_decide(player,in_cross_area);
			make_pass(player,p,in_cross_area);

			player->tm_xdis=x;
			player->tm_ydis=y;						// Restore orientation!
			launch_ball(1);			// Set up spin vector.
		}
		else
		{
// head in dir facing.
			heading_ball=1;
			int p=pass_decide(player,in_cross_area);
			make_pass(player,p,in_cross_area);
			launch_ball(1);			// Set up spin vector.
		}
	}

	if ((!uf1) && (!uf2))
	{
// Head down to grnd...
		if (um)
		{
// downward header in joystick dir.
			ballxdis=ux*(128-player->tm_cont)/16;
			ballydis=uy*(128-player->tm_cont)/16;
			ballzdis=-1;
			launch_ball(-1);			// Set up spin vector.
		}
		else
		{
// downward header in dir facing.

			ballxdis=player->tm_xdis*(128-player->tm_cont)/16;
			ballydis=player->tm_ydis*(128-player->tm_cont)/16;
			ballzdis=-1;
			launch_ball(-1);			// Set up spin vector.
		}
	}

	holder_lose_ball();
	ball_inair=TRUE;
 	stop_ball_spin();

	init_anim(player,MC_S_HEAD);

//	float bd=calc_dist(ballxdis,ballydis);
//	ballx=player->tm_x+(ballxdis*(HEADER_CONTACT+1)/bd);
//	bally=player->tm_y+(ballydis*(HEADER_CONTACT+1)/bd);
//	ballz=PLAYER_HEIGHT+player->tm_z;

	action="Header";
}

/******************************************************************************
*****************************************************************************/

void head_ball(match_player *player)
{
	last_touch=player->tm_player;
	if (last_touch!=KP_A && last_touch!=KP_B)
		pre_kp_touch=last_touch;

	reset_shot();
	int p=0;
	set_pos_flags(player);

	if (!player->control)
		reselect();

	if (player->control)
		user_header(player);
	else
	{
		if ((keeper_a_in_box && player->tm_player==KP_A && (cannot_pick_up<1 || cannot_pick_up>11))
			|| (keeper_b_in_box && player->tm_player==KP_B && (cannot_pick_up<1 || cannot_pick_up<12)))
// Attempt to catch ball...
		{
			control_ball(player);		// attempt to bring ball under control.
			before=100;
		}
		else
		{
			if (!head_shoot_decide(player))
			{
				if (!head_punt_decide(player))
				{
					heading_ball=1;
					if (in_cross_area)
					{
						p=(pass_decide(player,TRUE));
						if (p)
							make_pass(player,p,TRUE);
					}
					if (!p)
					{
// PASS!
						p=(pass_decide(player,FALSE));
						if (p)
							make_pass(player,p,FALSE);
					}
					heading_ball=FALSE;

					if (!p)
					{
						if (opp_around(ballx,bally,player->tm_player))
						{
							ballxdis=-ballxdis/2;
							ballydis=-ballydis/2;
							ballxdis=ballxdis+(((((float)(seed&15))-7)/16)*ball_speed);
							ballydis=ballydis+(((((float)(seed&63))-31)/64)*ball_speed);
						}
						else
						{
// header vertical.
							ballxdis=ballxdis/(player->tm_cont/16);
							ballydis=ballydis/(player->tm_cont/16);
							ballzdis=4+(ball_speed/(player->tm_cont/12));
						}
					}
				}
			}
		}
		if (before!=100)
// Keeper doesn't have ball...
		{
			holder_lose_ball();
			action="Header";
		}
	}
}

/******************************************************************************
*****************************************************************************/

void ball_at_contact(match_player *player)
{
	float cx,cy,cz;
	rotate_offs(player->tm_anim,cx,cy,cz,player->tm_xdis,player->tm_ydis);
	ballx=player->tm_x+cx;
	bally=player->tm_y+cy;
	ballz=player->tm_z+cz;
}

/******************************************************************************
*****************************************************************************/

void rebound_off_plr(match_player *player)
{
	penalty_shot=FALSE;
	last_touch=player->tm_player;
	if (last_touch!=KP_A && last_touch!=KP_B)
		pre_kp_touch=last_touch;

	can_be_offside=TRUE;

	if (save_block<0)
	{
// Keeper block save...

// How close???
		float d=SAVE_CONTACT-calc_dist(ballx-(player->tm_x+save_xoff),bally-(player->tm_y+save_yoff));

		float skill=d*player->tm_flair/(SAVE_CONTACT*128);
		float bx,by;

// New ball displacement...
		bx=(-(1.-skill)*ballxdis)+(skill*player->go_txdis);
		by=(-(1.-skill)*ballydis)+(skill*player->go_tydis);
		ballxdis=bx;
		ballydis=by;

		if (ballz>SAVE_HEAD_HGT)
// Up!
			ballzdis=3+ballzdis*VERT_BALL_DAMP;
		else
// Damp!
			ballzdis=ballzdis*VERT_BALL_DAMP;

		action="Rebound";
		reset_shot();
	}
	else
	{
		ballxdis=-ballxdis/2;
		ballydis=-ballydis/2;
		ballxdis=ballxdis+(((((float)(seed&15))-7)/16)*ball_speed);
		ballydis=ballydis+(((((float)(seed&63))-31)/64)*ball_speed);
		float bd=calc_dist(ballxdis,ballydis);
		ballx=player->tm_x+(ballxdis*(TOUCHB_BOX+1)/bd);
		bally=player->tm_y+(ballydis*(TOUCHB_BOX+1)/bd);
		ballzdis=ballzdis*VERT_BALL_DAMP;
		action="Rebound";
		reset_shot();
	}
}

/******************************************************************************
*****************************************************************************/

void has_ball(match_player *player)
{
	if (comm_pass>=0 && !(seed&(32+16+8)))
	{
		if ((prev_touch>11 && player->tm_player>11)
			|| (prev_touch<12 && player->tm_player<12))
		{
			if (comm_pass_type==1)
// Backheel...
				if (comsetp)
				{
					PlayCommentaryMessage(CP_SETPIECE);
					comsetp=0;
				}
				else
					PlayCommentaryMessage(CP_NICEMOVE);
			else
				if (comm_pass_type==2)
// Cross...
					if (comsetp)
					{
						PlayCommentaryMessage(CP_SETPIECE);
						comsetp=0;
					}
					else
						PlayCommentaryMessage(CP_TARGET);
				else
// Normal...
				{
					float prx=teams[prev_touch-1].tm_x;
					float pry=teams[prev_touch-1].tm_y;
					float tx=player->tm_x;
					float ty=player->tm_y;
					short d=calc_dist(prx-tx,pry-ty);
					if (d>LONG_PASS_DIST)
						PlayCommentaryMessage(CP_LONG);
					else
						PlayCommentaryMessage(CP_SHORT);
				}
		}
/*
		else
		{
// Not guy aimed for...
			if ((prev_touch>11 && player->tm_player<12)
				|| (prev_touch<12 && player->tm_player>11))
// Bad pass...
				if (comm_pass || comm_pass_type==2)
// Long try...
					PlayCommentaryMessage(FP_LONG);
				else
					if (comm_pass_type==1)
// Backheel...
						PlayCommentaryMessage(FP_LOOSE);
					else
						PlayCommentaryMessage(FP_SHORT);
		}
*/
		comm_pass=-1;
	}
	else
	{
		if (say_names && !opponents_really_close)
		{
			short intone=0;
			if (ball_poss<12)
			{
				intone=ballx/cntspot_x;
			}
			else
			{
				intone=(pitch_len-ballx)/cntspot_x;
			}

			PlayTeamSample(real_player(ball_poss),intone);
		}
	}
}

/******************************************************************************
*****************************************************************************/
	
void hold_ball(match_player *player)
{
	if (!set_piece_on)
	{
// calculate position of ball at feet!
		float bx,by;
		bx=ballx;
		by=bally;

		player->tm_poss++;
		ballxdis=player->go_txdis;
		ballydis=player->go_tydis;
		ballzdis=0;							// Ground ball.
		ballz=ball_diam/2;

		float x=player->tm_xdis;
		float y=player->tm_ydis;

		last_touch=player->tm_player;
		if (last_touch!=KP_A && last_touch!=KP_B)
			pre_kp_touch=last_touch;

		if (ball_in_hands)
		{
			if (player->tm_act==THROW_ACT)
			{
// Ball above player's head!
				ballz=player->tm_z+(PLAYER_HEIGHT+4);
				ballx=player->tm_x;
				bally=player->tm_y;
				ball_in_hands=TRUE;
			}
			else
			{
				if (player->int_move!=I_GET_UP || !player->int_cnt)
				{
					if (player->tm_act==SAVE_ACT)
					{
						ballz=player->tm_z+save_zoff;
						ballx=player->tm_x+save_xoff;
						bally=player->tm_y+save_yoff;
						player->dir_mode=5;
					}
					else
					{
						ballz=player->tm_z+(PLAYER_HEIGHT/2);
						ballx=player->tm_x+(x*IN_HANDS_DIST);
						bally=player->tm_y+(y*IN_HANDS_DIST);
						if (player->tm_act!=KPHOLD_ACT)
							player->dir_mode=2;
						else
							player->dir_mode=3;
					}
				}
			}
		}
		else
		{
			if (player->tm_poss==HAS_BALL_DELAY)
				has_ball(player);

//			inc_poss(player->tm_player);
			double n;
			player->dir_mode=0;
			ball_inair=FALSE;
			if (player->tm_act==RUN_ACT)
			{
				bx=player->tm_x+(x*(AT_FEET_DIST+(4.*(modf(player->tm_frm,&n)-.5))));
				by=player->tm_y+(y*(AT_FEET_DIST+(4.*(modf(player->tm_frm,&n)-.5))));
			}
			else
			{
				if (!dead_ball_cnt)
				{
// If player is in a set-piece then no need to move position of ball...
					bx=player->tm_x+(x*AT_FEET_DIST);
					by=player->tm_y+(y*AT_FEET_DIST);
				}
			}

			if (player->tm_ftime<-1)
			{
// Just controlled ball... (so tween to held pos.)
// ftime (-2 to -10)...
				if (player->tm_ftime==-2)
					get_mcball_coords(player);
				else
				{
					ballx+=((bx-ballx)*(-2-player->tm_ftime)/8);
					bally+=((by-bally)*(-2-player->tm_ftime)/8);
				}
//				ballx=bx;
//				bally=by;
				if (--player->tm_ftime==-11)
					player->tm_ftime=0;
			}
			else
			{
// No tweening...
				ballx=bx;
				bally=by;
			}
		}

		if (((player->tm_player==KP_A) || (player->tm_player==KP_B))
			&& (player->tm_act==STAND_ACT) && (ball_in_hands))
			init_kphold_act(player);
	}
	else
	{
		last_touch=player->tm_player;
		if (last_touch!=KP_A && last_touch!=KP_B)
			pre_kp_touch=last_touch;
	}
}

/******************************************************************************
*****************************************************************************/

void init_specials()
{
	spec_kick_type=0;
	f1_down=FALSE;
	f2_down=FALSE;
}

/******************************************************************************
*****************************************************************************/

void collect_ball(match_player *player)
{
	add_comp_pass(player->tm_player);
	if (player->tm_act==TACKLE_ACT)
		inc_twon(player->tm_player);

	if (!player->tm_leave)
		reset_leaves();

//	comm_pass=-1;		//FIX
	prev_touch=last_touch;
	receiver_a=FALSE;
	receiver_b=FALSE;
	init_specials();

	if ((must_shoot) || (must_punt) || (must_pass))
	{
		must_shoot=-must_shoot;
		must_pass=-must_pass;
		must_punt=-must_punt;
	}

	if ((player->tm_player!=KP_A) && (player->tm_player!=KP_B))
		cannot_pick_up=player->tm_player;

// Keeper can pick up ball...

	hold_ball(player);
	if ((ball_in_hands) && (player->tm_act!=SAVE_ACT))
		reset_all_ideas();
	stop_ball_spin();
	ball_poss=player->tm_player;
	player->tm_poss=1;
	if ((player->int_cnt) && (player->int_move==I_INTERCEPT))
		reset_ideas(player);
	action="Collect";
	reset_shot();
	penalty_shot=FALSE;

	if (player->tm_act==CONTROL_ACT)
		ball_at_contact(player);

	reselect();
}

/******************************************************************************
*****************************************************************************/

void control_difficulty(match_player *player)

// Calculates difficulty factor (0 simple -> 128 impossible)!
{
	float x=ballx-ballxdis;		//take ball one step back!
	float y=bally-ballydis;
	x=x-player->tm_x;				//offset to player.
	y=y-player->tm_y;
	int cside=get_dir(x,y);		//contact side of player.
	cside=cside-player->face_dir;
	if (cside<0)
		cside=cside+8;
	if (cside>4)
		cside=8-cside;
	difficulty=cside*16;			//direction difficulty!
	int s=ball_speed*2;

	if (player->tm_act==RUN_ACT)
		if (want_pass==player->tm_player)
// He is expecting it so better chance of controlling ball!
			s+=2;
		else
			s+=4;							// speed factor.

	if (player->tm_act==TACKLE_ACT)
		s+=8;							// speed factor.
	if ((player->tm_act==SAVE_ACT) || (((player->tm_player==KP_A) || (player->tm_player==KP_B))
		&& (ballz>PLAYER_HEIGHT/3)))
		s-=4;							// Keeper saving!

	difficulty+=(6*s);				//add speed difficulty!
}

/******************************************************************************
*****************************************************************************/

void active_control(match_player *player)
{
	if (player->tm_ftime>=0)
	{
		float cx,cy,cz;
		rotate_offs(player->tm_anim,cx,cy,cz,player->tm_xdis,player->tm_ydis);
		ballx=player->tm_x+cx;
		bally=player->tm_y+cy;
		ballz=player->tm_z+cz;
		ballxdis=player->tm_xdis*(2+(ball_speed/(player->tm_cont/32)));
		ballydis=player->tm_ydis*(2+(ball_speed/(player->tm_cont/32)));
		ballzdis=1;
		last_touch=player->tm_player;
		if (last_touch!=KP_A && last_touch!=KP_B)
			pre_kp_touch=last_touch;
		player->tm_ftime=-1;				// Continue animation!
	}
}

/******************************************************************************
*****************************************************************************/

void standard_fstep(match_player *player)
{
	switch(player->tm_anim)
	{
		case(MC_D_HEAD):
			player->tm_fstep=MC_D_HEAD_FS;
			break;

		case(MC_CHEST):
			player->tm_fstep=MC_CHEST_FS;
			break;

		case(MC_TRAPL):
		case(MC_TRAPR):
			player->tm_fstep=MC_TRAP_FS;
			break;

		case(MC_SHOOTL):
		case(MC_SHOOTR):
			player->tm_fstep=MC_SHOOT_FS;
			break;

		case(MC_CHIPL):
		case(MC_CHIPR):
			player->tm_fstep=MC_CHIP_FS;
			break;

		case(MC_VOLLEYL):
		case(MC_VOLLEYR):
			player->tm_fstep=MC_VOLLEY_FS;
			break;

		case(MC_OVERHEAD):
			player->tm_fstep=MC_OVERHEAD_FS;
			break;

		case(MC_DV_HEAD):
			player->tm_fstep=MC_DV_HEAD_FS;
			break;

		case(MC_S_HEAD):
			player->tm_fstep=MC_S_HEAD_FS;
			break;

		case(MC_J_HEAD):
			player->tm_fstep=MC_J_HEAD_FS;
			break;

	}
}

/******************************************************************************
*****************************************************************************/

void control_ball(match_player *player)

// Having made contact with ball,
// the player must attempt to control it!

{
	can_be_offside=TRUE;

	if (player->tm_act==CONTROL_ACT)
	{
// Player has successfully controlled ball.
		if (player->tm_anim==MC_U_HEAD)
// Head Control...(Bounce ball upward!)
		{
			active_control(player);
		}
		else
		{

			holder_lose_ball();
			collect_ball(player);		//bring ball to feet!
			player->dir_mode=2;
			if (player->tm_anim!=MC_TRAPL && player->tm_anim!=MC_TRAPR)
			{
				standard_fstep(player);		// Normal speed anim...
				ball_limbo(player->tm_player,1-player->tm_fstep);		// Ball is motion captured to ground!
			}
		}
	}
	else
	{
		if (player->tm_act==TACKLE_ACT)
			player->go_step=TRUE;				// He has touched the ball (no foul)!
		control_difficulty(player);
		if ((((player->tm_act!=SAVE_ACT) && (player->tm_z<1))
			|| ((player->tm_act==SAVE_ACT) || (player->tm_player==KP_A)	
			|| (player->tm_player==KP_B) && (player->tm_z>PLAYER_HEIGHT/3)))
			&& (seed+player->tm_cont>difficulty))
		{
// Assume controlled ball is at feet level.
			holder_lose_ball();
			collect_ball(player);		//bring ball to feet!
		}
		else
			rebound_off_plr(player);		//could not control!
	}
}

/******************************************************************************
*****************************************************************************/

char control_interact(match_player *player)
{
	if (player->tm_frm>=player->contact)
	{
// Contact point exceeded...

		if (player->tm_anim!=MC_TRAPL && player->tm_anim!=MC_TRAPR)
		{
			player->tm_anim++;
			player->tm_anim--;
		}

		float px=player->tm_x;
		float py=player->tm_y;
		float pz=player->tm_z;

		float cx,cy,cz;
		rotate_offs(player->tm_anim,cx,cy,cz,player->tm_xdis,player->tm_ydis);
		
		px+=cx;
		py+=cy;
		pz+=cz;

		float d=calc_dist(ballx-px,bally-py);
		if (d>ball_speed+2 && d>8)
			return(FALSE);

		if	(abs(ballz-pz)>prat/2)
			return(FALSE);
	
// Good contact... (control ball)!
  		return(TRUE);
	}
	return(FALSE);
}

/******************************************************************************
*****************************************************************************/

void ball_interact(match_player *player)
{
	int act=player->tm_act;

	if (player->tm_poss<=0)
	{
		player->tm_poss=0;
		if (!((act==FALL_ACT) ||
			(act==RISE_ACT) || (act==RIDE_ACT) || (dead_ball_cnt)))	//player not out of game.
		{
			if ((!((player->int_cnt!=0) && (player->int_move==I_KICKED)))
				&& (!ball_in_hands))
			{
				if (act!=SAVE_ACT)
				{
// Normal player...
					if (!just_scored && ((!ball_poss) || (ball_poss && teams[ball_poss-1].tm_act!=PICKUP_ACT)))
					{

					if (!ball_poss || (ball_poss && ball_poss<12 && player->tm_player>11)
						|| (ball_poss>11 && player->tm_player<12))
					{
// Ball is free or the opponent has ball...

						if (act==CONTROL_ACT && player->tm_ftime>=0 && control_interact(player))
						{
// He has successfully controlled the ball!
							control_ball(player);
						}

						if (act==STRIKE_ACT && player->tm_ftime>=0 && control_interact(player))
						{
// He has successfully struck the ball!
							strike_ball_off(player);
						}

						if (player->tm_act!=CONTROL_ACT && player->tm_act!=STRIKE_ACT)
						{
							if (!player->tm_strike && TOUCHB_BOX>=calc_dist(ballx-player->tm_x,bally-player->tm_y)
								 && ballz<PLAYER_HEIGHT && (!penalty_game || player->tm_player==KP_A || player->tm_player==KP_B))
							{
// Contact is made...
								receiver_a=FALSE;
								receiver_b=FALSE;

								if (!practice && (player->tm_leave>0) && (last_touch==player->tm_player))
								{
									init_foul(player->tm_player,FALSE,TRUE);	// Indirect F.K. for touching ball again!
								}

								if ((ballz<player->tm_z+PLAYER_HEIGHT/2)
									&& (ballz-ballzdis<player->tm_z+PLAYER_HEIGHT/2))
								{
//Contact with ball at feet...
									if (act<=TURN_ACT || act==TACKLE_ACT || act==STEAL_ACT)
										control_ball(player);
								}
								else
								{
									if (ballz<player->tm_z+PLAYER_HEIGHT-3)
									{
// At head and body height...
										if (act<=TURN_ACT || act==TACKLE_ACT || act==STEAL_ACT)
											rebound_off_plr(player);
									}
								}
							}
						}
					}
					}

					if (player->tm_leave<0)
						player->tm_leave=TRUE;
				}
				else
				{
// Keeper save!
					if (player->tm_frm>(keeper_contact-0.00001))
					{
// Contact with ball reached...
						if (keeper_will_save>0 || keep_dive)
						{
// Keeper should connect with ball at contact point...
							if (keep_dive || (SAVE_CONTACT>calc_dist(ballx-(player->tm_x+save_xoff),bally-(player->tm_y+save_yoff))
								 && !ball_in_goal))
// Keeper has judged it well!
							{
								inc_saves(player->tm_player);
								shot_saved=25;
								keeper_will_save=-1;
								if (save_block && !keep_dive)
								{
									if (real_shot)
									{
										PlayCommentaryMessage(PM_BLOCK);
										inc_save(last_touch);
									}
									save_block=-1;						// Rebound properly from block!
									rebound_off_plr(player);		//could not control!
									ball_inair=TRUE;
									ballz=save_zoff;
									ballx=player->tm_x+player->go_txdis+save_xoff;
									bally=player->tm_y+player->go_tydis+save_yoff;
									save_block=0;						// Rebound properly from block!
								}
								else
								{
									if (real_shot)
									{
										PlayCommentaryMessage(PM_CATCH);
										inc_save(last_touch);
									}
									holder_lose_ball();
									ball_in_hands=TRUE;
									collect_ball(player);		//bring ball to feet!
								}
								keep_dive=FALSE;
							}
							else
							{
// Ball too far!!!
								keeper_will_save=0;		// Catch will change to block...
								if (!save_block)
								{
// Must become desperate block instead of catch...
									if (ABS(player->tm_anim)<MC_BFOOTBL)
									{
// Zone A save...(no right,left)
										player->tm_anim--;
									}
									else
									{
										player->tm_anim-=2;
									}

									player->go_cnt=(1-player->tm_frm)/player->tm_fstep;

									if (!player->tm_anim)		// AFOOTB
										keeper_on_grnd=FALSE;
									
									if (keeper_on_grnd)
										player->int_cnt=player->go_cnt+2;
									else
										player->int_cnt=player->go_cnt+2;
								}
							}
						}
					}
				}
			}
		}
	}
	else
	{
		if ((player->contact>0) && (player->tm_act==KICK_ACT))
		{
// Currently awaiting contact point in animation...
// He's kicking the ball just now...

			ballx+=((player->tm_x+b_xoff)-ballx)*player->tm_frm/player->contact;
			bally+=((player->tm_y+b_yoff)-bally)*player->tm_frm/player->contact;
			ballz+=((player->tm_z+b_zoff)-ballz)*player->tm_frm/player->contact;

		}
		else
		{
			if (((ballz>=player->tm_z) && (ballz<PLAYER_HEIGHT+player->tm_z))
				|| (act==THROW_ACT) || (act==SAVE_ACT) || (act=KPHOLD_ACT))
			{
				if (player->tm_player==ball_poss)
					hold_ball(player);
				else
					player->tm_poss=0;				// doesnt have ball any more.
			}
			else
			{
				holder_lose_ball();
			}
		}
	}
}

/******************************************************************************
*****************************************************************************/

// Predicts ball coords from now till 50 turns ahead!

void predict_ball()
{
	struct stack{
		float x; float y; float z;
		float xd; float yd; float zd;
		int ba; int bs; int sw; float xys; float zs;
		float f_xys; float f_zs; int sp_b;};

	struct stack sp;

	sp.x=ballx;
	sp.y=bally;
	sp.z=ballz;
	sp.xd=ballxdis;
	sp.yd=ballydis;
	sp.zd=ballzdis;
	sp.ba=ball_inair;
	sp.bs=ball_still;
	sp.sw=swerve;
	sp.xys=ball_xyspin;
	sp.zs=ball_zspin;
	sp.f_xys=full_xyspin;
	sp.f_zs=full_zspin;
	sp.sp_b=spin_cnt;

	ns_ballx=ballx;
	ns_bally=bally;
	ns_ballz=ballz;

	float *ptr1=&ball_pred_tab[0][0];
	float *ptr2=&ns_ball_pred_tab[0][0];

	first_bounce=-1;
	prediction=TRUE;
	for (int i=0; i<50; i++)
	{
// Ball with swerve!
		*ptr1++=ballx;
		*ptr1++=bally;
		*ptr1++=ballz;
		if (first_bounce<0 && ballz<=(ball_diam/2) && i>0)
			first_bounce=i;

// Ball without swerve!
		*ptr2++=ns_ballx;
		*ptr2++=ns_bally;
		*ptr2++=ns_ballz;

		if (!ball_poss)
			ball_trajectory();
		else
		{
			if (teams[ball_poss-1].tm_act==TACKLE_ACT)
			{
// Take into account deceleration of tackle action!
				ballx+=ballxdis*pow(TACKLE_DECEL,i);
				bally+=ballydis*pow(TACKLE_DECEL,i);
				ns_ballx+=ballxdis*pow(TACKLE_DECEL,i);
				ns_bally+=ballydis*pow(TACKLE_DECEL,i);
			}
			else
			{
				ballx+=ballxdis;
				bally+=ballydis;
				ns_ballx+=ballxdis;
				ns_bally+=ballydis;
			}
		}
	}

	spin_cnt=sp.sp_b;
	full_zspin=sp.f_zs;
	full_xyspin=sp.f_xys;
	ball_zspin=sp.zs;
	ball_xyspin=sp.xys;
	swerve=sp.sw;
	ball_still=sp.bs;
	ball_inair=sp.ba;
	ballzdis=sp.zd;
	ballydis=sp.yd;
	ballxdis=sp.xd;
	ballz=sp.z;
	bally=sp.y;
	ballx=sp.x;
}

/******************************************************************************
*****************************************************************************/

// Find no. of opponents near ball holder.

void get_opp_near_ball(int holder)
{
	opponents_near_holder=0;			// Initialise count.
	opponents_really_close=0;
	int p;
	if (holder)
	{
		if (holder>11)						// Get opposing team.
			p=0;
		else
			p=11;
		for (int i=p; i<p+11; i++)
		{
			if ((teams[i].guy_on>0) && (teams[i].tm_dist<=DRIB_DANGER_AREA))
			{
				opponents_near_holder++;
				if (teams[i].tm_dist<=MEGA_DANGER_AREA)
					opponents_really_close++;
			}
		}
	}
}

/******************************************************************************
*****************************************************************************/

void get_dist_pos(int pn)
{
	float d,lowest;
	int guy=pn;

	for (int pos=2; pos<5; pos++)
	{
		lowest=2000;

		for (int i=pn; i<pn+12; i++)
		{
			if (teams[i-1].guy_on>0)
			{
				d=teams[i-1].tm_dist;
				if ((d<lowest) && (!teams[i-1].tm_pos))
				{
					guy=i;
					lowest=d;
				}
			}
		}
		teams[guy-1].tm_pos=pos;
	}
}

/******************************************************************************
*****************************************************************************/

// Updates player distances.

#define SELECTION_CIRCLE (prat*10)

void player_distances()
{
	float px,py;
	float ad=2000;
	float bd=2000;
	float d;
	defense_a=cntspot_x;
	defense_b=cntspot_x;

	for (player_num=0; player_num<players; player_num++)
	{
		if (teams[player_num].guy_on>0)
		{
			px=teams[player_num].tm_x;

			if (player_num<11)
			{
				if (px<defense_a && player_num)
					defense_a=px;

 				d=calc_dist(pitch_len-teams[player_num].tm_x,cntspot_y-teams[player_num].tm_y);

				if (d<(MIN_SHOOT_DIST+((float)teams[player_num].tm_pow*3)))
					teams[player_num].tm_srng=TRUE;
				else
					teams[player_num].tm_srng=FALSE;
			}
			else
			{
				if  ((player_num!=11) && (px>defense_b))
					defense_b=px;

				d=calc_dist(teams[player_num].tm_x,cntspot_y-teams[player_num].tm_y);

				if (d<(MIN_SHOOT_DIST+((float)teams[player_num].tm_pow*3)))
					teams[player_num].tm_srng=TRUE;
				else
					teams[player_num].tm_srng=FALSE;
			}

			px-=ballx;
			py=teams[player_num].tm_y-bally;
			d=calc_dist(px,py);
			teams[player_num].tm_dist=d;
			teams[player_num].tm_pos=0;
			if (player_num>=players/2)
			{
				if (d<bd)
				{
					bd=d;
					nearest_b=player_num+1;
				}
			}
			else
			{
				if (d<ad)
				{
					ad=d;
					nearest_a=player_num+1;
				}
			}
			if (player_num!=(KP_A-1) && player_num!=(KP_B-1))
				sel_circle[player_num]=(d<SELECTION_CIRCLE ? TRUE:FALSE);
			else
				sel_circle[player_num]=FALSE;
		}
	}
	teams[nearest_a-1].tm_pos=1;
	teams[nearest_b-1].tm_pos=1;
	get_dist_pos(1);
	get_dist_pos(12);
}

/******************************************************************************
*****************************************************************************/

// Return closest guy to the ball (from one team) who is not busy!
// p_num = first player in team.

int get_nearest_guy(int p_num)
{
	int near_guy=0, closest=10000;
	for (int i=p_num; i<p_num+11; i++)
	{
		if (teams[i].tm_act<=TURN_ACT)				//player is not busy!
		{
			if (teams[i].tm_dist<closest)
			{
				near_guy=i+1;						//This guy is closer!
				closest=teams[i].tm_dist;
			}
		}
	}
	return(near_guy);
}

/******************************************************************************
*****************************************************************************/

void get_nearest()
{
	if (receiver_a)
		near_path_a=receiver_a;
	else
		near_path_a=get_near_path(0,TRUE);

	if (receiver_b)
		near_path_b=receiver_b;
	else
		near_path_b=get_near_path(11,TRUE);
}

/******************************************************************************
*****************************************************************************/

void holder_lose_ball()
{
	if (ball_poss)
	{
		reset_ideas(&teams[ball_poss-1]);
		if (ball_poss<12)
			ball_released=OFFSIDE_REL_CNT;
		else
			ball_released=-OFFSIDE_REL_CNT;

		short p=teams[ball_poss-1].tm_poss;
		teams[ball_poss-1].tm_posst+=p*p/50;	// Good dribbles will adjust performance.
		teams[ball_poss-1].tm_poss=0;
		ball_poss=0;
		in_cross_area=FALSE;
		ball_in_hands=FALSE;
		must_punt=FALSE;
		must_pass=FALSE;
		must_shoot=FALSE;
	}
}



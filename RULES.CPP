/******************************************************************************
*******************************************************************************

Match rules and control routines...

******************************************************************************
*****************************************************************************/

#include "global.h"
#include "defines.h"
#include "externs.h"
#include "data.h"
#include "audio.h"

#include "front.h"
#include "eurofrnt\euro_int.h"

extern match_data match_info;
extern team_info game_data[];
extern setup_info setup;
int timeout;

extern char old_tac_a,old_tac_b;
extern void load_new_tactics();

/******************************************************************************
*****************************************************************************/

void decide_set_kick()
{
	support_me=FALSE;
	int p;

	switch(set_piece_on)
	{
		case(SETP_CORNER):
			if (ref_wait<0)
				must_shoot=TRUE;
			p=pass_decide(&teams[setp_taker-1],TRUE);
			if (p)
				make_pass(&teams[setp_taker-1],p,TRUE);
			else
				if (shoot_decide(&teams[setp_taker-1]))
					make_shoot(&teams[setp_taker-1]);
				else
					support_me=TRUE;		// No action (help).
			break;

		case(SETP_CENTRE):
			must_pass=TRUE;
			p=centre_guy_2;
			pass_type=5;
			if (p)
				make_pass(&teams[setp_taker-1],p,FALSE);
			else
				support_me=TRUE;		// No action (help).
			must_pass=FALSE;
			break;

		case(SETP_IFKICK):
			if (ref_wait<0)
				must_punt=TRUE;
			p=pass_decide(&teams[setp_taker-1],FALSE);
			if (p)
				make_pass(&teams[setp_taker-1],p,FALSE);
			else
				if (punt_decide(&teams[setp_taker-1]))
					make_punt(&teams[setp_taker-1]);
				else
					support_me=TRUE;		// No action (help).
			break;

		case(SETP_GKICK):
			if (ref_wait<0)
				must_punt=TRUE;
			p=pass_decide(&teams[setp_taker-1],FALSE);
			if (p && p!=KP_A && p!=KP_B)
				make_pass(&teams[setp_taker-1],p,FALSE);
			else
			{
				if (!seed&3)
					must_punt=TRUE;
				if (punt_decide(&teams[setp_taker-1]))
					make_punt(&teams[setp_taker-1]);
				else
					support_me=TRUE;		// No action (help).
			}
			break;

		case(SETP_DFKICK):
			if (ref_wait<0)
				must_shoot=TRUE;
			p=pass_decide(&teams[setp_taker-1],FALSE);
			if (p)
				make_pass(&teams[setp_taker-1],p,FALSE);
			else
				if (punt_decide(&teams[setp_taker-1]))
					make_punt(&teams[setp_taker-1]);
				else
					if (shoot_decide(&teams[setp_taker-1]))
						make_shoot(&teams[setp_taker-1]);
					else
						support_me=TRUE;		// No action (help).
			break;

		case(SETP_PENALTY):
			must_shoot=TRUE;
			if (shoot_decide(&teams[setp_taker-1]))
			{
				penalty_shot=TRUE;
				make_shoot(&teams[setp_taker-1]);
			}
			else
				support_me=TRUE;		// No action (help).
			break;
	}
}

/******************************************************************************
*****************************************************************************/

char all_standing()
{
	int i=0;
	if (--setp_wait_cnt)
	{
		for (i=0; i<players; i++)
		{
			if (teams[i].guy_on>0 && teams[i].tm_act!=STAND_ACT && teams[i].tm_act!=PICKUP_ACT
			 	&& teams[i].dir_mode!=6 && (teams[i].tm_act!=RUN_ACT || teams[i].tm_off!=-2))
				i=100;
		}
	}
	else
		setp_wait_cnt=1;

	return((i<=players) ? TRUE:FALSE);
}

/******************************************************************************
*****************************************************************************/

void clear_wall()
{
	for (int j=0; j<men_in_wall; j++)
	{
		teams[wguys[j].guy-1].tm_wall=0;
	}
	men_in_wall=0;
}

/******************************************************************************
*****************************************************************************/

void ready_set_kick()
{
	if (set_piece_on)
	{
		if (men_in_wall && (match_mode==DF_KICK_A || match_mode==DF_KICK_B))
			clear_wall();

		arrow_on=FALSE;
		match_mode=0;
		offside_now=FALSE;
		dead_ball_cnt=0;
		game_action=0;
		teams[setp_taker-1].tm_leave=-TRUE;	// Not allowed to touch ball after kick!
		user_taker=0;
// Referee normal mode...
		refs[0].act=0;
		set_piece_on=FALSE;
		already_there=FALSE;
		reselect();
	}
}

/******************************************************************************
*****************************************************************************/

void go_set_kick(char type)
{
	short p;
	if (type)
	{
		ready_set_kick();

		switch(type)
		{
			case(PASS_FEET):
				must_pass=TRUE;
				p=pass_decide(&teams[setp_taker-1],FALSE);
				if (p)
					make_pass(&teams[setp_taker-1],p,FALSE);
				break;

			case(PASS_HEAD):
				must_pass=TRUE;
				chip_pass=TRUE;
				p=(pass_decide(&teams[setp_taker-1],FALSE));
				if (p)
					make_pass(&teams[setp_taker-1],p,FALSE);
				break;

			case(PUNT):
				must_punt=TRUE;
				if (punt_decide(&teams[setp_taker-1]))
					make_punt(&teams[setp_taker-1]);
				break;

			default:
				must_pass=TRUE;
				break;
		}
	}
}

/******************************************************************************
*****************************************************************************/

void ready_ckick()
{
	arrow_on=FALSE;
	match_mode=0;
	dead_ball_cnt=0;
	collect_ball(&teams[corner_taker-1]);
	game_action=0;
	teams[corner_taker-1].tm_leave=-TRUE;	// Not allowed to touch ball!
	user_taker=0;
}

/******************************************************************************
*****************************************************************************/

void go_ckick(char type)
{
	if (type)
	{
		ready_ckick();
		switch(type)
		{
			case(PASS_FEET):
				must_pass=TRUE;
				break;

			case(PASS_HEAD):
				must_pass=TRUE;
				break;

			case(PUNT):
				must_punt=TRUE;
				break;

			default:
				must_pass=TRUE;
				break;
		}
	}
}

/******************************************************************************
*****************************************************************************/

void await_set_kick()
{
	if (!hold_up_play)
	{
		if ((!player_on_off && (all_standing() && already_there) || (support_me)))
		{
			if (!allow_replay)
				init_replay();

			if (ball_poss!=setp_taker)
				collect_ball(&teams[setp_taker-1]);

			if (refs[0].act==4)
			{
// Referee wait for kick mode...
				refs[0].act=2;
				ktaker=setp_taker;
				ref_wait=(160-ref_strictness)*REAL_SPEED/8;
				play_fx(PS_SHORTWHISTLE,refs[0].x,refs[0].y);
				clock_running=TRUE;
				kickoff=FALSE;
			}

			if (user_taker)
			{
				if (reselection)
				{
					setp_kick_x=teams[setp_taker-1].tm_xdis;
					setp_kick_y=teams[setp_taker-1].tm_ydis;
					setp_power=0;
					setp_hgt=0;
					setp_byd=cntspot_y;
					reselection=FALSE;
					teams[setp_taker-1].dir_mode=1;
					teams[setp_taker-1].control=user_taker;
					users[user_taker-1].plr=setp_taker;
					
#ifdef EURO96
					if (match_mode==PEN_KICK_A && user_taker2)
					{
						teams[KP_B-1].control=user_taker2;
						users[user_taker2-1].plr=KP_B;
					}
					if (match_mode==PEN_KICK_B && user_taker2)
					{
						teams[KP_A-1].control=user_taker2;
						users[user_taker2-1].plr=KP_A;
					}
#endif

					reselect_all_users();
					arrow_on=TRUE;
					arrow_guy=setp_taker;
					if (match_mode>=GOAL_KICK_TL && match_mode<=GOAL_KICK_BR)
						support_me=FALSE;
					else
						support_me=TRUE;
				}
			}
			else
			{
				if (refs[0].act==2)
				{
#ifdef EURO96
					if (match_mode!=PEN_KICK_A && match_mode!=PEN_KICK_B)
#endif
					{
						decide_set_kick();
						if (!support_me)
// Doesnt need support....
							ready_set_kick();
					}
				}
			}
		}
	}
	else
		hold_up_play--;
}

/*****************************************************************************
*****************************************************************************/

void swap_users()
{

// Team A users now play Team B...

	short p;
	for (int u=0; u<num_of_users; u++)
	{
		if (users[u].type>0)
		{
// Fixed-player...
			if (users[u].type>11)
				users[u].type-=11;
			else
				users[u].type+=11;
		}
		else
		{
// Auto-player...
			if (users[u].type==-1)
				users[u].type=-2;
			else
				users[u].type=-1;
		}

		p=users[u].plr;
		if (p>11)
			users[u].plr=p-11;
		else
			if (p<12 && p>0)
				users[u].plr=p+11;
	}

	p=auto_users_a;
	auto_users_a=auto_users_b;
	auto_users_b=p;

	short t[10];
	memcpy(&t,&auto_users_list_a,sizeof(t));
	memcpy(&auto_users_list_a,&auto_users_list_b,sizeof(t));
	memcpy(&auto_users_list_b,&t,sizeof(t));
}

/*****************************************************************************
*****************************************************************************/

void swap_teams()
{
	match_half+=1;

	match_player a;

	swap_users();

	for (short p=0; p<11; p++)
	{
		memcpy(&a,&teams[p],sizeof(a));
		memcpy(&teams[p],&teams[p+11],sizeof(a));
		memcpy(&teams[p+11],&a,sizeof(a));

		teams[p].tm_player=p+1;
		teams[p+11].tm_player=p+12;
	}

	char t=team_a;
	team_a=team_b;
	team_b=t;

	p=players_off_a;
	players_off_a=players_off_b;
	players_off_b=p;

	old_tac_a=-1;
	old_tac_b=-1;
	load_new_tactics();
}

/*****************************************************************************
*****************************************************************************/

char in_tunnel()
{
	for(short p=0; p<players; p++)
	{
		if (teams[p].draw_me)
			return(FALSE);
	}
	return(TRUE);
}
	
/*****************************************************************************
*****************************************************************************/

void await_swap()
{
	if (in_tunnel() || !(timeout--))
	{
		if (match_half>=11)
			end_game=TRUE;
		else
			swap_teams();

		camera=old_cam;

		if (last_centre)
		{
// Team A had last kick off...(not including goal respots)
			last_centre=FALSE;
			match_mode=CENTRE_B;
			init_match_mode();
		}
		else
		{
// Team B had last kick off...(not including goal respots)
			last_centre=TRUE;
			match_mode=CENTRE_A;
			init_match_mode();
		}
	}
}

/*****************************************************************************
*****************************************************************************/

void remember_cam()
{
	if (camera!=15)
	{
		old_cam=camera;
	}
// old_cam is already remembered if camera=15!
}

/*****************************************************************************
*****************************************************************************/

void init_swap_ends()
{
	allow_replay=FALSE;
	remember_cam();
	timeout=20*15;
	clock_running=FALSE;
	camera=16;
	reset_ball();
	dead_ball_cnt=40;
	for (int i=0; i<players; i++)
	{
		init_stand_act(&teams[i]);
	}
}

/******************************************************************************
*****************************************************************************/

void await_throw()
{
	if (already_there && !player_on_off)
	{
		float x=teams[throw_in_taker-1].tm_x;
		float y=teams[throw_in_taker-1].tm_y;
		if (calc_dist(incident_x-x,incident_y-y)<prat*3)
		{
			if (user_taker)
			{
				if (reselection)
				{
					reselection=FALSE;
					teams[throw_in_taker-1].dir_mode=1;
					teams[throw_in_taker-1].control=user_taker;
					users[user_taker-1].plr=throw_in_taker;
					reselect_all_users();
					arrow_on=TRUE;
					arrow_guy=throw_in_taker;
				}
			}

			if (ball_in_hands)
			{
				match_mode=0;
				ball_in_hands=TRUE;
				init_throw_act(&teams[throw_in_taker-1]);
				collect_ball(&teams[throw_in_taker-1]);
				teams[throw_in_taker-1].tm_leave=-TRUE;	// Not allowed to touch ball!
			}
			else
			{
				if (teams[throw_in_taker-1].tm_act!=PICKUP_ACT)
					init_pickup_act(&teams[throw_in_taker-1]);
			}
		}
	}
}

/******************************************************************************
*****************************************************************************/

void ball_situation()
{
	if (match_mode)
	{
		if (match_mode==SWAP_ENDS)
// Half time or extra time.
			await_swap();
		else
			if (set_piece_on!=SETP_THROW)
				await_set_kick();
			else
				await_throw();
	}
}

/******************************************************************************
******************************************************************************/

void stop()
{
	alarm=FALSE;
	mf_fixed=TRUE;
	stop_min+=1000;
	watch=TRUE;
}

/******************************************************************************
******************************************************************************/

void add_player_time()
{
	for (int p=0; p<22; p++)
	{
		teams[p].tm_time++;
	}
}

/******************************************************************************
******************************************************************************/

void match_clock()
{
	if (demo_match)
		rolling_clock--;

	if (!match_mode && !penalty_game && !stop_clock && !just_scored)
	{
		match_time.sec+=90.0/(time_factor*REAL_SPEED);
		if (match_time.sec>=60)
		{
			match_time.sec-=60;
			match_time.min+=1;
			add_player_time();
		}

		if ((alarm) && (match_time.min>=stop_min) && (match_time.sec>=stop_sec))
			stop();
	}
}

/******************************************************************************
*****************************************************************************/

void kill_ball()
{
	reset_all_ideas();
	holder_lose_ball();
	stop_ball_spin();
	ballxdis=0;
	ballydis=0;
	ballzdis=0;
	ballx=incident_x;
	bally=incident_y;
	ballz=ball_diam/2;
	dead_ball_cnt=50;
}

/******************************************************************************
*****************************************************************************/

void pen_to_team_a()
{
	away_pens_left--;
// Team A penalty...

	match_mode=PEN_KICK_A;
	do{
		if (!(--pen_taker_a))
			pen_taker_a=10;

	}while(!teams[pen_taker_a].guy_on);

// Guy hasn't been sent off!

	user_taker=user_taker_a(pen_taker_a+1);

#ifdef EURO96
	user_taker2=user_keeper_b();
#endif

	penalty_taker=pen_taker_a+1;
}

/******************************************************************************
*****************************************************************************/

void pen_to_team_b()
{
	home_pens_left--;
// Team B penalty...

	match_mode=PEN_KICK_B;
	do{
		if ((--pen_taker_b)==11)
			pen_taker_b=21;

	}while(!teams[pen_taker_b].guy_on);

// Guy hasn't been sent off!

	user_taker=user_taker_b(pen_taker_b+1);

#ifdef EURO96
	user_taker2=user_keeper_a();
#endif

	penalty_taker=pen_taker_b+1;
}

/******************************************************************************
*****************************************************************************/

void do_penalties()
{
	if (!match_mode)
	{
// Normal play...
		if (!penalty_counter)
		{
// Next penalty...
			if (penalties>=10 && !(penalties&1))
			{
// If at least 5 penalties each and both taken same no...
				if (team_a_goals!=team_b_goals)
				{
					penalty_game=FALSE;
				}
			}
			else
			{
				if (penalties<10)
				{
					if (team_a_goals>team_b_goals)
					{
// Home team winning...
						if (away_pens_left<(team_a_goals-team_b_goals))
							penalty_game=FALSE;
					}
					else
					{
// Away team winning...
						if (home_pens_left<(team_b_goals-team_a_goals))
							penalty_game=FALSE;
					}
				}
			}
	
			if (penalty_game)
			{
				penalties++;
				penalty_counter=5*REAL_SPEED;
				kill_ball();
				game_action=2;		// gather outside box!
				if (!penalty_team)
				{
					penalty_team=TRUE;		// Setup next for team!
					if (match_half&1)
						pen_to_team_b();
					else
						pen_to_team_a();
				}
				else
				{
					penalty_team=FALSE;		// Setup next for team!
					if (match_half&1)
						pen_to_team_a();
					else
						pen_to_team_b();
				}
				init_match_mode();
			}
		}
		else
		{
			penalty_counter--;
		}
	}
}

/******************************************************************************
*****************************************************************************/

void match_rules()
{
	if (penalty_game)
	{
		if (match_mode!=PEN_KICK_A && match_mode!=PEN_KICK_B && match_mode!=SWAP_ENDS)
			match_mode=0;

		do_penalties();
	}

	match_clock();
	if (dead_ball_cnt)
		ball_situation();
}

/******************************************************************************
*****************************************************************************/

char bounds_rules()
{

	float xoff=0;
	float yoff=0;

/***********************/

	if (ballx<0)
	{
// Past Left Goal-line...
		xoff=-ballx;

		if (last_touch<12)
		{
// Corner!
			if (!team_b_on)
			{
				if (bally>cntspot_y)
					return(GOAL_KICK_BL);
				else
					return(GOAL_KICK_TL);
			}
			else
			{
				if (bally>cntspot_y)
					return(CORNER_BL);
				else
					return(CORNER_TL);
			}
		}
		else
		{
// Goal Kick!
			if (!team_a_on)
			{
				if (bally>cntspot_y)
					return(CORNER_BL);
				else
					return(CORNER_TL);
			}
			else
			{
				if (bally>cntspot_y)
					return(GOAL_KICK_BL);
				else
					return(GOAL_KICK_TL);
			}
		}
	}

/***********************/

	if (ballx>=pitch_len)
	{
// Past Right Goal-line...
		xoff=ballx-(pitch_len-1);

		if (last_touch>11)
		{
// Corner!
			if (!team_a_on)
			{
				if (bally>cntspot_y)
					return(GOAL_KICK_BR);
				else
					return(GOAL_KICK_TR);
			}
			else
			{
				if (bally>cntspot_y)
					return(CORNER_BR);
				else
					return(CORNER_TR);
			}
		}
		else
		{
// Goal Kick!
			if (!team_b_on)
			{
				if (bally>cntspot_y)
					return(CORNER_BR);
				else
					return(CORNER_TR);
			}
			else
			{
				if (bally>cntspot_y)
					return(GOAL_KICK_BR);
				else
					return(GOAL_KICK_TR);
			}
		}
	}

/***********************/

	if (bally<0)
		yoff=-bally;

	if (bally>=pitch_wid)
		yoff=bally-(pitch_wid-1);

	if (yoff>xoff)
	{
// Over top side-line...

		incident_x=ballx;
		incident_y=((bally<0) ? 0:pitch_wid-1);

		if (last_touch<12)
		
// Throw-in to team B!
			if (!team_b_on)
				return(THROW_IN_A);
			else
				return(THROW_IN_B);
		else
			if (!team_a_on)
				return(THROW_IN_B);
			else
				return(THROW_IN_A);
		
	}
	return(0);
}

/******************************************************************************
*****************************************************************************/
// INITIALISE MATCH SITUATIONS...
/******************************************************************************
*****************************************************************************/

/******************************************************************************
*****************************************************************************/

void throw_taker(int p)
{
// Decision is made on the closest tactical position at current ball_zone...

	int min_d=1000;
	int d;

	for (int pn=p; pn<p+10; pn++)
	{
		if (teams[pn-1].guy_on>0)
		{
			if (pn<12)
				d=calc_dist(ballx-match_tactics1[ball_zone1][pn-2][0],
							   bally-match_tactics1[ball_zone1][pn-2][1]);
			else
				d=calc_dist((pitch_len-ballx)-match_tactics2[ball_zone2][pn-13][0],
							   (pitch_wid-bally)-match_tactics2[ball_zone2][pn-13][1]);
		
			if (d<min_d)
			{
				min_d=d;
				throw_in_taker=pn;
			}
		}
	}
}

/******************************************************************************
*****************************************************************************/

int get_taker(int p)
{
// Decision is made on the closest tactical position at current ball_zone...

	int min_d=1000;
	int d,taker;

	for (int pn=p; pn<(p<12 ? 12:23); pn++)
	{
		if (teams[pn-1].guy_on>0)
		{
			if (pn==KP_A)
				d=calc_dist(ballx-0,bally-cntspot_y);
			else
				if (pn==KP_B)
					d=calc_dist(pitch_len,bally-cntspot_y);
				else
					if (pn<12)
						d=calc_dist(ballx-match_tactics1[ball_zone1][pn-2][0],
							   		bally-match_tactics1[ball_zone1][pn-2][1]);
					else
						d=calc_dist((pitch_len-ballx)-match_tactics2[ball_zone2][pn-13][0],
							   		(pitch_wid-bally)-match_tactics2[ball_zone2][pn-13][1]);

			if (d<min_d)
			{
				min_d=d;
				taker=pn;
			}
		}
	}
	return(taker);
}

/******************************************************************************
*****************************************************************************/

void centre_takers()
{
	int p;
	centre_guy_1=0;
	centre_guy_2=0;

	if (match_mode==CENTRE_A)
	{
		p=2;
		flag=TRUE;
	}
	else
	{
		p=13;
		flag=FALSE;
	}

	int d;
	int min_d=1000;

// Decide on which two players shall take centre.

// Decision is made on the two closest tactical positions...

	for (int pn=p; pn<p+10; pn++)
	{
		if (teams[pn-1].guy_on>0)
		{
			if (flag)
				d=calc_dist(cntspot_x-match_tactics1[68][pn-2][0],
							   cntspot_y-match_tactics1[68][pn-2][1]);
			else
				d=calc_dist(cntspot_x-match_tactics2[68][pn-13][0],
							   cntspot_y-match_tactics2[68][pn-13][1]);

			if (d<min_d)
			{
				min_d=d;
				centre_guy_1=pn;
			}
		}
	}

	min_d=1000;
	for (pn=p; pn<p+10; pn++)
	{
		if (teams[pn-1].guy_on>0)
		{
			if (flag)
				d=calc_dist(cntspot_x-match_tactics1[68][pn-2][0],
							   cntspot_y-match_tactics1[68][pn-2][1]);
			else
				d=calc_dist(cntspot_x-match_tactics2[68][pn-13][0],
							   cntspot_y-match_tactics2[68][pn-13][1]);

			if ((d<min_d) && (centre_guy_1!=pn))
			{
				min_d=d;
				centre_guy_2=pn;
			}
		}
	}
}

/******************************************************************************
*****************************************************************************/

void init_centre()
{
	if (kickoff && next_mins)
	{
		match_time.min=next_mins;
		match_time.sec=0;
		match_mode=CENTRE_A;
		last_goal=0;
	}
										
	reset_ball();
	dead_ball_cnt=40;
	ballx=cntspot_x;
	bally=cntspot_y;
	ballz=ball_diam/2;

	if (match_mode==CENTRE_A)
	{
// Team A centre.
		ball_zone1=68;
		ball_zone2=69;
		refs[0].goto_x=cntspot_x+5*prat;
		centre_takers();
		do_kickoff_menu(team_a);
	}
	else
	{
// Team B centre.
		ball_zone2=68;
		ball_zone1=69;
		refs[0].goto_x=cntspot_x-5*prat;
		centre_takers();
		do_kickoff_menu(team_b);
	}

	game_action=1;		// 10 Yards away!

// Referee go to spot behind incident...
	refs[0].act=1;
	refs[0].target=0;	// Ball!
	refs[0].goto_y=cntspot_y;

	main_man=centre_guy_1;

	user_taker=0;
/*
	if (centre_guy_1>11)
		user_taker=user_taker_b(centre_guy_1);
	else
		user_taker=user_taker_a(centre_guy_1);
*/
}

/******************************************************************************
*****************************************************************************/

void init_corner()
{
	PlayCommentaryMessage(SP_CORNER);

	comsetp=40;
	user_taker=0;
	dead_ball_cnt=20;
	switch(match_mode)
	{
		case(CORNER_TL):
			ballx=prat-1;
			bally=prat-1;
			ballz=ball_diam/2;
			ball_zone1=64;
			ball_zone2=67;
			last_touch=12;			// team b has possession.

			if ((corn_kicker_b) && (teams[corn_kicker_b-1].guy_on>0))
				corner_taker=corn_kicker_b;
			else
				corner_taker=get_taker(13);

			do_corner_menu(team_b);

			break;

		case(CORNER_BL):
			ballx=prat-1;
			bally=pitch_wid-prat+1;
			ballz=ball_diam/2;
			ball_zone1=66;
			ball_zone2=65;
			last_touch=12;			// team b has possession.

			if ((corn_kicker_b) && (teams[corn_kicker_b-1].guy_on>0))
				corner_taker=corn_kicker_b;
			else
				corner_taker=get_taker(13);

			do_corner_menu(team_b);

			break;

		case(CORNER_TR):
			ballx=pitch_len-prat+1;
			bally=prat-1;
			ballz=ball_diam/2;
			ball_zone1=65;
			ball_zone2=66;
			last_touch=1;			// team a has possession.

			if ((corn_kicker_a) && (teams[corn_kicker_a-1].guy_on>0))
				corner_taker=corn_kicker_a;
			else
				corner_taker=get_taker(2);

			do_corner_menu(team_a);

			break;

		case(CORNER_BR):
			ballx=pitch_len-prat+1;
			bally=pitch_wid-prat+1;
			ballz=ball_diam/2;
			ball_zone1=67;
			ball_zone2=64;
			last_touch=1;			// team a has possession.

			if ((corn_kicker_a) && (teams[corn_kicker_a-1].guy_on>0))
				corner_taker=corn_kicker_a;
			else
				corner_taker=get_taker(2);

			do_corner_menu(team_a);

			break;
	}

	incident_x=ballx+((ballx<cntspot_x) ? -4:4);
	incident_y=bally+((bally<cntspot_y) ? -8:8);
	game_action=1;		// 10 Yards away!

	if (corner_taker>11)
		user_taker=user_taker_b(corner_taker);
	else
		user_taker=user_taker_a(corner_taker);

	main_man=corner_taker;

// Referee go to spot between centre spot and ball...
	refs[0].act=1;
	refs[0].target=0;	// Ball!
	refs[0].goto_x=cntspot_x+((ballx-cntspot_x)/2);
	refs[0].goto_y=cntspot_y+((bally-cntspot_y)/2);
	last_touch=main_man;
	pre_kp_touch=last_touch;
	ball_in_hands=FALSE;
}

/******************************************************************************
*****************************************************************************/

void init_gkick()
{
	if (fired_a_shot)
	{
		if ((ABS(bally_out-cntspot_y)>prat*7) || (ballz_out>prat*4))
// Miles away...
			PlayCommentaryMessage(PM_WIDE);
		else
// Near miss..
			PlayCommentaryMessage(PM_CLOSE);
	}
	else
		PlayCommentaryMessage(SP_GOALKICK);

	dead_ball_cnt=100;
	switch(match_mode)
	{
		case(GOAL_KICK_TL):
			ballx=(5.8*prat);
			bally=cntspot_y-(5.0*prat);
			ballz=ball_diam/2;
			ball_zone1=11;
			ball_zone2=20;
			last_touch=1;			// team a has possession.

			if ((goal_kicker_a) && (teams[goal_kicker_a-1].guy_on>0))
				gkick_taker=goal_kicker_a;
			else
				gkick_taker=get_taker(1);

			do_goalkick_menu(team_a);
			break;

		case(GOAL_KICK_BL):
			ballx=(5.8*prat);
			bally=cntspot_y+(5.0*prat);
			ballz=ball_diam/2;
			ball_zone1=19;
			ball_zone2=12;
			last_touch=1;			// team a has possession.

			if ((goal_kicker_a) && (teams[goal_kicker_a-1].guy_on>0))
				gkick_taker=goal_kicker_a;
			else
				gkick_taker=get_taker(1);

			do_goalkick_menu(team_a);
			break;

		case(GOAL_KICK_TR):
			ballx=pitch_len-(5.8*prat);
			bally=cntspot_y-(5.0*prat);
			ballz=ball_diam/2;
			ball_zone1=12;
			ball_zone2=19;
			last_touch=12;			// team b has possession.

			if ((goal_kicker_b) && (teams[goal_kicker_b-1].guy_on>0))
				gkick_taker=goal_kicker_b;
			else
				gkick_taker=get_taker(12);

			do_goalkick_menu(team_b);
			break;

		case(GOAL_KICK_BR):
			ballx=pitch_len-(5.8*prat);
			bally=cntspot_y+(5.0*prat);
			ballz=ball_diam/2;
			ball_zone1=20;
			ball_zone2=11;
			last_touch=12;			// team b has possession.

			if ((goal_kicker_b) && (teams[goal_kicker_b-1].guy_on>0))
				gkick_taker=goal_kicker_b;
			else
				gkick_taker=get_taker(12);

			do_goalkick_menu(team_b);
			break;
	}
	incident_x=ballx;
	incident_y=bally;
	game_action=1;		// 10 Yards away!

	main_man=gkick_taker;

// Referee go to spot between centre spot and ball...
	refs[0].act=1;
	refs[0].target=0;	// Ball!
	refs[0].goto_x=cntspot_x+((ballx-cntspot_x)/2);
	refs[0].goto_y=cntspot_y+((bally-cntspot_y)/2);
	last_touch=main_man;
	pre_kp_touch=last_touch;

	user_taker=0;

	if (gkick_taker>11)
		user_taker=user_taker_b(gkick_taker);
	else
		user_taker=user_taker_a(gkick_taker);

	float ang=(64.-seed)*(PI/(8*64));

	if (match_mode<GOAL_KICK_TR)
	{
// Goal_kick to team A...
		taker_x=ballx-(cos(ang)*4);
		taker_y=bally+(sin(ang)*4);
	}
	else
	{
// Goal_kick to team B...
		taker_x=ballx+(cos(ang)*4);
		taker_y=bally+(sin(ang)*4);
	}
}

/******************************************************************************
*****************************************************************************/

void init_throw()
{
	stop_clock=TRUE;
	user_taker=0;
	dead_ball_cnt=100;
	if (match_mode==THROW_IN_A)
	{
		do_throw_menu(team_a);
		last_touch=1;		// Team A have possession...
		throw_taker(2);
		if (ballx_out>(pitch_len-(prat*20)))
			PlayCommentaryMessage(SP_LONGTHROWIN);
		else
			PlayCommentaryMessage(SP_THROWIN);

	}
	if (match_mode==THROW_IN_B)
	{
		do_throw_menu(team_b);
		last_touch=12;		// Team B have possession...
		throw_taker(13);
		if (ballx_out<(prat*20))
			PlayCommentaryMessage(SP_LONGTHROWIN);
		else
			PlayCommentaryMessage(SP_THROWIN);
	}

	teams[throw_in_taker-1].int_move=I_THROW;

	ballx=incident_x;
	bally=incident_y;

	ballz=ball_diam/2;
	game_action=1;		// 10 Yards away!

	if (throw_in_taker>11)
		user_taker=user_taker_b(throw_in_taker);
	else
		user_taker=user_taker_a(throw_in_taker);

// Linesman go to spot behind incident...
	if (bally>cntspot_y)
// Bottom linesman....
	{
		refs[2].act=1;
		refs[2].goto_y=refs[2].y;
		if (refs[2].x>ballx+prat*4)
			refs[2].goto_x=ballx+prat*4;
		else
			if (refs[2].x<ballx-prat*4)
				refs[2].goto_x=ballx-prat*4;
			else
				refs[2].act=0;
	}
	else
// Top linesman....
	{
		refs[1].act=1;				
		refs[1].goto_y=refs[1].y;
		if (refs[1].x>ballx+prat*4)
			refs[1].goto_x=ballx+prat*4;
		else
			if (refs[1].x<ballx-prat*4)
				refs[1].goto_x=ballx-prat*4;
			else
				refs[1].act=0;
	}
	main_man=throw_in_taker;
}

/******************************************************************************
*****************************************************************************/

char penalty(int fouler)
{
	if (ballx<cntspot_x)
	{
// Team A box...
		if ((fouler<12) && (ballx<prat*18) && (bally<cntspot_y+(prat*22)) && (bally>cntspot_y-(prat*22)))
			return(TRUE);
	}
	else
	{
// Team B box...
		if ((fouler>11) && (ballx>pitch_len-(prat*18)) && (bally<cntspot_y+(prat*22)) && (bally>cntspot_y-(prat*22)))
			return(TRUE);
	}
	return(FALSE);
}

/******************************************************************************
*****************************************************************************/

void init_offside(match_player *player)
{
	float d,x;

	if (player->tm_player>11)
// Top linesman...
	{
		x=defense_a-player->tm_x;		// How much offside.
		d=(pitch_wid-calc_dist(player->tm_x-refs[1].x,player->tm_y-refs[1].y))/prat;
	}
	else
// Bot linesman...
	{
		x=player->tm_x-defense_b;		// How much offside.
		d=(pitch_wid-calc_dist(player->tm_x-refs[2].x,player->tm_y-refs[2].y))/prat;
	}

	d=ref_accuracy/2+(ref_accuracy*((d*d*0.000740740)-(0.07*d)+1));
	if (d<1)
		d=1;

	if (seed<d/2+x)
	{

// The linesman sees the Offside...
		player->tm_off=TRUE;
	}
	else
	{
		short rel=(128-ref_accuracy)/4;
		player->tm_off=-TRUE;
		if (ball_released<0)
		{
			ball_released+=rel;
			if (ball_released>0)
				ball_released=0;
		}
		else
		{
			ball_released-=rel;
			if (ball_released<0)
				ball_released=0;
		}
	}
}

/******************************************************************************
*****************************************************************************/

void big_yeller(int plr)
{
	card_is_out=3*REAL_SPEED;
	int t;
	booking=TRUE;

	if (plr<12)
		t=team_a;
	else
		t=team_b;

	PlayCommentaryMessage(FU_YELLOWCARD);
	do_booked_menu(t,teams[plr-1].shirt-1);
	inc_yellow(plr);
}

/******************************************************************************
*****************************************************************************/

void ger_em_off(int plr)
{
// Off
	inc_red(plr);
	card_is_out=6*REAL_SPEED;
	booking=TRUE;
	if (plr<12)
		players_off_a++;
	else
		players_off_b++;

	player_on_off=plr;
	sub_camera=camera;
	camera=17;
	reset_ideas(&teams[plr-1]);
	init_off_int(&teams[plr-1]);
	PlayCommentaryMessage(FU_REDCARD);

	int t,p;

	if (plr<12)
	{
		t=team_a;
		game_data[team_a==0 ? setup.team_a:setup.team_b].players[plr-1].flags|=2;
	}
	else
	{
		t=team_b;
		game_data[team_b==0 ? setup.team_a:setup.team_b].players[plr-12].flags|=2;
	}

	do_off_menu(t,teams[plr-1].shirt-1);

//	teams[plr-1].guy_on=-1;			// Waiting to be sent off!

	if (corn_kicker_a==plr)
		corn_kicker_a=0;

	if (corn_kicker_b==plr)
		corn_kicker_b=0;

	if (goal_kicker_a==plr)
		if (plr<12)
			goal_kicker_a=KP_A;
		else
			goal_kicker_a=KP_B;

	if (goal_kicker_b==plr)
		if (plr<12)
			goal_kicker_a=KP_A;
		else
			goal_kicker_a=KP_B;

	if	(fkick_taker_a==plr)
		fkick_taker_a=0;

	if	(fkick_taker_b==plr)
		fkick_taker_b=0;
}

/******************************************************************************
*****************************************************************************/

void send_off_plr(int plr,float nasty)
{
	if (plr!=KP_A && plr!=KP_B && EUROmatch_info.bookings)
	{
		if (teams[plr-1].tm_book)
		{
// He's had a yellow card...
			if (nasty>seed)
			{
				if ((plr<12 && players_off_a<5) || (plr>11 && players_off_b<5))
					ger_em_off(plr);
			}
		}
		else
		{
		 	if (nasty>seed*4)
			{
				if ((plr<12 && players_off_a<5) || (plr>11 && players_off_b<5))
					ger_em_off(plr);
			}
			else
				if (nasty>seed)
					big_yeller(plr);
		}
	}
}

/******************************************************************************
*****************************************************************************/

void punish_foul(int fouler,char direct)
{
	user_taker=0;
	in_range=FALSE;
	reset_all_ideas();
	holder_lose_ball();
	stop_ball_spin();
	ballxdis=0;
	ballydis=0;
	ballzdis=0;
	ballx=incident_x;
	bally=incident_y;
	ballz=ball_diam/2;
	dead_ball_cnt=50;
	last_touch=fouler;

	float nastiness;

	booking=0;
	nastiness=sqrt(teams[last_touch-1].tm_dist*4)*ref_strictness/6;			// distance to ball. (how late was the challenge?)
	if (!man_down)
		nastiness/=3;

// Shall we send him off?
	if (direct)
		send_off_plr(last_touch,nastiness);

	if (direct && (penalty(fouler)))
	{
		inc_pfoul(fouler);

		if (seed&2 && !player_on_off)
			PlayCommentaryMessage(FU_DIVE);

		init_speech(players+1,SAY_PENALTY);
		game_action=2;		// gather outside box!
		if (fouler>11)
// Team A P.K.
		{
			match_mode=PEN_KICK_A;
			if ((penalty_taker_a) && (teams[penalty_taker_a-1].guy_on>0))
				penalty_taker=penalty_taker_a;
			else
				penalty_taker=get_taker(2);

			if (!booking)
				do_penalty_menu(team_a);

			user_taker=user_taker_a(penalty_taker);
#ifdef EURO96
			user_taker2=user_keeper_b();
#endif
		}
		else
// Team B P.K.
		{
			match_mode=PEN_KICK_B;
			if ((penalty_taker_b) && (teams[penalty_taker_b-1].guy_on>0))
				penalty_taker=penalty_taker_b;
			else
				penalty_taker=get_taker(13);

			if (!booking)
				do_penalty_menu(team_b);

			user_taker=user_taker_b(penalty_taker);
#ifdef EURO96
			user_taker2=user_keeper_a();
#endif
		}
	}
	else
	{
		game_action=1;		// 10 Yards away!
		if (fouler>11)
// Team A F.K.
		{
			if (!direct)
			{
// Not on the ball..(INDIRECT)
				inc_ifoul(fouler);
				init_speech(players+1,SAY_OFFSIDE);
				match_mode=IF_KICK_A;
				fkick_taker=get_taker(2);
				if (!booking)
					if (offside_now)
						do_offside_menu(team_a);
					else
						do_indirect_menu(team_a);
			}
			else
// On the ball..(DIRECT)
			{
				if (!player_on_off)
				{
					if (seed&64)
						PlayCommentaryMessage(FU_BADFOUL);
					else
						PlayCommentaryMessage(FU_FREEKICK);
				}

				inc_dfoul(fouler);
				init_speech(players+1,SAY_FOUL);
				match_mode=DF_KICK_A;
				if ((fkick_taker_a) && (teams[fkick_taker_a-1].guy_on>0))
					fkick_taker=fkick_taker_a;
				else
					fkick_taker=get_taker(2);
			}
				user_taker=user_taker_a(fkick_taker);
		}
		else
// Team B F.K.
		{
			if (!direct)
			{
// Not on the ball..(INDIRECT)
				inc_ifoul(fouler);
				init_speech(players+1,SAY_OFFSIDE);
				match_mode=IF_KICK_B;
				fkick_taker=get_taker(13);
				if (!booking)
					if (offside_now)
						do_offside_menu(team_b);
					else
						do_indirect_menu(team_a);
			}
			else
// On the ball..(DIRECT)
			{
				if (!player_on_off)
				{
					if (seed&64)
						PlayCommentaryMessage(FU_BADFOUL);
					else
						PlayCommentaryMessage(FU_FREEKICK);
				}

				inc_dfoul(fouler);
				init_speech(players+1,SAY_FOUL);
				match_mode=DF_KICK_B;
				if ((fkick_taker_b) && (teams[fkick_taker_b-1].guy_on>0))
					fkick_taker=fkick_taker_b;
				else
					fkick_taker=get_taker(13);
			}
				user_taker=user_taker_b(fkick_taker);
		}
	}
	init_match_mode();
}

/******************************************************************************
*****************************************************************************/

void retake_foul()
{
	punish_foul(bad_guy,direct_fk);
	play_advantage=FALSE;
}

/******************************************************************************
*****************************************************************************/

void init_foul(int fouler,char direct,char see)
{	
	play_advantage=FALSE;
	af_randomize();
	float x,y,d;
	d=calc_dist(ballx-refs[0].x,bally-refs[0].y)/prat;
	d=(ref_accuracy/d)*2*man_down;

	if (d>128)
		d=128;

	if (!just_scored && EUROmatch_info.freekicks && ((seed<d) || (see)))
	{
		incident_x=teams[fouler-1].tm_x;
		incident_y=teams[fouler-1].tm_y;

		direct_fk=direct;
	 	bad_guy=fouler;

// The referee sees the foul...
		if (offside_now)
// Cannot play advantage with offside rule...
			punish_foul(fouler,direct_fk);
		else
		{
			af_randomize();

// May play advantage...
			if (fouler<12)
// Team A commited foul...
			{
				if ((!ball_poss) && (seed>ref_strictness))
// Ball is free...play temporary advantage...
				{
					play_advantage=TRUE;
					init_speech(players+1,SAY_ADV);
				}
				else
					if (ball_poss<12)
						punish_foul(fouler,direct_fk);
			}
			else
// Team B commited foul...
			{
				if ((!ball_poss) && (seed>ref_strictness))
// Ball is free...play temporary advantage...
				{
					play_advantage=TRUE;
					init_speech(players+1,SAY_ADV);
				}
				else
					if (ball_poss>11 || !ball_poss)
						punish_foul(fouler,direct_fk);

			}
		}
	}
	else
	{
		if (seed&2 && !just_scored)
			PlayCommentaryMessage(FU_DIVE);
	}
}


/******************************************************************************
*****************************************************************************/

extern int pen_cnt;

void force_penalty()
{
	pen_cnt=100;
	holder_lose_ball();
	ball_poss=12;
	ballx=pitch_len-2;
	bally=cntspot_y;
	ballz=ball_diam/2;
	init_foul(13,TRUE,TRUE);
}
	
/******************************************************************************
*****************************************************************************/

void init_fkick()
{
	float x,y,d;

	if (last_touch<12)
		x=-ballx;
	else
		x=pitch_len-ballx;
	
	y=cntspot_y-bally;
	d=calc_dist(x,y);
	taker_x=ballx-(x*BESIDE_BALL/d);
	taker_y=bally-(y*BESIDE_BALL/d);

// Referee go to spot behind incident...
	refs[0].act=1;
	refs[0].target=0;	// Ball!
	float rx=refs[0].x-ballx;
	float ry=refs[0].y-bally;
	float rd=calc_dist(rx,ry);
	refs[0].goto_x=ballx+(rx*BESIDE_BALL*16/rd);
	refs[0].goto_y=bally+(ry*BESIDE_BALL*16/rd);
	main_man=fkick_taker;
	last_touch=fkick_taker;
	pre_kp_touch=last_touch;
}

/******************************************************************************
*****************************************************************************/

void find_wall_guys(int guys,float x,float y)
{
	int d,pn,min_d,wall_cnt;
	float dist=prat*0.9;
	float xd=x*dist;
	float yd=y*dist;
	float cx=wallx-xd;
	float cy=wally-yd;

	wall_cnt=0;

	for (int j=0; j<men_in_wall; j++)
	{
	 	min_d=2000;
		for (int i=guys; i<guys+10; i++)
		{
			if ((!teams[i-1].tm_wall) && (teams[i-1].guy_on>0))
			{
				if (i<12)
					d=calc_dist(ballx-match_tactics1[ball_zone1][i-2][0],
								   bally-match_tactics1[ball_zone1][i-2][1]);
				else
					d=calc_dist((pitch_len-ballx)-match_tactics2[ball_zone2][i-13][0],
								   (pitch_wid-bally)-match_tactics2[ball_zone2][i-13][1]);

				if (d<min_d)
				{
					min_d=d;
					pn=i;
				}
			}
		}
		if (min_d!=2000)
		{
// found an idiot...
			teams[pn-1].tm_wall=TRUE;
			wguys[j].guy=pn;
			wguys[j].x=cx;
			wguys[j].y=cy;
			cx=cx+xd;
			cy=cy+yd;
			wall_cnt++;
		}
	}
	men_in_wall=wall_cnt;

// Get keeper position...
	float gx,gy;
	x=wguys[wall_cnt-2].x-incident_x;		// 2nd last man in wall!
	y=wguys[wall_cnt-2].y-incident_y;
	if (guys>11)
// Team B's goal...
		gx=pitch_len-prat;
	else
// Team A's goal...
		gx=0+prat;
	
	gx=gx-incident_x;
	gy=y*gx/x;
	
	keeper_pos_x=gx+incident_x;
	keeper_pos_y=gy+incident_y;

}

/*****************************************************************************
*****************************************************************************/

void inc_pfoul(short p)
{
	teams[p-1].tm_fouls+=10;		// add giving penalty to foul list.
}

/*****************************************************************************
*****************************************************************************/

void inc_dfoul(short p)
{
	teams[p-1].tm_fouls+=3;		// add direct F.K. to foul list.
}

/*****************************************************************************
*****************************************************************************/

void inc_ifoul(short p)
{
	teams[p-1].tm_fouls++;		// add indirect F.K. to foul list.
}

/*****************************************************************************
*****************************************************************************/

void inc_pass(short p)
{
	teams[p-1].tm_pass++;		// Passes attempted.
}

/*****************************************************************************
*****************************************************************************/

void inc_work(short p)
{
	teams[p-1].tm_work++;		// Passes attempted.
}

/******************************************************************************
*****************************************************************************/

void inc_pwon(short p)
{
	teams[p-1].tm_pwon++;		// Passes won.
}

/******************************************************************************
*****************************************************************************/

void inc_tack(short p)
{
	teams[p-1].tm_tacks++;		// Tackles attempted.
}

/******************************************************************************
*****************************************************************************/

void inc_twon(short p)
{
	teams[p-1].tm_twon++;		// Tackles won.
}

/******************************************************************************
*****************************************************************************/

void inc_poss(short p)
{
	teams[p-1].tm_posst++;		// Possession time.
}

/******************************************************************************
*****************************************************************************/

void inc_inj(short p,short i)
{
	teams[p-1].tm_inj+=i;		// Injury.
}

/******************************************************************************
*****************************************************************************/

void inc_yellow(short p)
{
	teams[p-1].tm_book++;		// Yellow card.
}

/******************************************************************************
*****************************************************************************/

void inc_red(short p)
{
	teams[p-1].tm_book+=5;		// Red card.
}

/******************************************************************************
*****************************************************************************/

void inc_shot(short p)
{
	teams[p-1].tm_shots++;		// Shots attempted.
}

/******************************************************************************
*****************************************************************************/

void inc_goal(short p)
{
	teams[p-1].tm_goals++;		// Goals scored.
}

/******************************************************************************
*****************************************************************************/

void inc_ogs(short p)
{
	teams[p-1].tm_ogs++;		// Own goals scored.
}

/******************************************************************************
*****************************************************************************/

void inc_save(short p)
{
	teams[p-1].tm_saved++;		// shots saved.
}

/******************************************************************************
*****************************************************************************/

void inc_saves(short p)
{
	teams[p-1].tm_kpsaves++;		// Saved shot.
}

/******************************************************************************
*****************************************************************************/

void add_comp_pass(short plr)
{
	if (last_touch && ((last_touch<12 && plr<12)
		|| (last_touch>11 && plr>11)))
		inc_pwon(last_touch);
}

/******************************************************************************
*****************************************************************************/

void init_dfkick()
{
	comsetp=40;

	int taker;
	float d,x,y,range;

	if (!booking)
	{
		if (last_touch<12)
			do_direct_menu(team_b);
		else
			do_direct_menu(team_a);
	}

	if (last_touch<12)
// F.K. to Team B...

	{
		last_touch=12;		// Team B have possession...
		x=-ballx;
		y=cntspot_y-bally;
		d=calc_dist(x,y);
		taker_x=ballx-(x*BESIDE_BALL/d);
		taker_y=bally-(y*BESIDE_BALL/d);

// Referee go to spot behind incident...
		refs[0].act=1;
		refs[0].target=0;	// Ball!
		float rx=refs[0].x-ballx;
		float ry=refs[0].y-bally;
		float rd=calc_dist(rx,ry);
		refs[0].goto_x=ballx+(rx*BESIDE_BALL*16/rd);
		refs[0].goto_y=bally+(ry*BESIDE_BALL*16/rd);

		range=calc_dist(x,y);
		if (range>(MIN_SHOOT_DIST+((float)teams[fkick_taker-1].tm_pow*3)))
// Out of shooting range!
		{
			men_in_wall=0;		// No wall!
			taker=-1;
		}
		else
// In shooting range!
		{
			in_range=TRUE;
			if (incident_y<cntspot_y)
// Near post is top!
			{
				y=top_post_y-incident_y;
				range=calc_dist(incident_x,y);
			}
			else
// Near post is bottom!
			{
				y=bot_post_y-incident_y;
				range=calc_dist(incident_x,y);
			}

			y=y/range;											// horiz. vector to goal!
			x=-incident_x/range;

			men_in_wall=5.5-(ABS(y)*3);					// Team A make wall.
			taker=fkick_taker;
			wallx=incident_x+(prat*10*x);
			wally=incident_y+(prat*10*y);					// Wall coords...
			if (incident_y<cntspot_y)
				x=-x;
			else
				y=-y;
			find_wall_guys(2,y,x);			// x,y reversed for right angle!
			if (!player_on_off)
				PlayCommentaryMessage(FU_WALL);
		}
	}
	else
// F.K. to Team A...

	{
		last_touch=1;		// Team A have possession...
		x=pitch_len-ballx;
		y=cntspot_y-bally;
		d=calc_dist(x,y);
		taker_x=incident_x-(x*BESIDE_BALL/d);
		taker_y=incident_y-(y*BESIDE_BALL/d);

// Referee go to spot behind incident...
		refs[0].act=1;
		refs[0].target=0;	// Ball!
		float rx=refs[0].x-ballx;
		float ry=refs[0].y-bally;
		float rd=calc_dist(rx,ry);
		refs[0].goto_x=ballx+(rx*BESIDE_BALL*16/rd);
		refs[0].goto_y=bally+(ry*BESIDE_BALL*16/rd);

		range=calc_dist(x,y);
		if (range>(MIN_SHOOT_DIST+((float)teams[fkick_taker-1].tm_pow*3)))
// Out of shooting range!
		{
			men_in_wall=0;		// No wall!
			taker=0;				// Anybody can take F.K.
		}
		else
// In shooting range!
		{
			in_range=TRUE;
			if (incident_y<cntspot_y)
// Near post is top!
			{
				y=top_post_y-incident_y;
				range=calc_dist(pitch_len-incident_x,y);
			}
			else
// Near post is bottom!
			{
				y=bot_post_y-incident_y;
				range=calc_dist(pitch_len-incident_x,y);
			}

			y=y/range;				  						// horiz. vector to goal!
			x=(pitch_len-incident_x)/range;

			men_in_wall=5.5-(ABS(y)*3);				// Team B make wall.
			taker=fkick_taker;
			wallx=incident_x+(prat*10*x);
			wally=incident_y+(prat*10*y);				// Wall coords...
			if (incident_y<cntspot_y)
				y=-y;
			else
				x=-x;
			find_wall_guys(13,y,x);			// x,y reversed for right angle!
			if (!player_on_off)
				PlayCommentaryMessage(FU_WALL);
		}
	}

	if (taker<1)
// Not close enough to take shot so nearest can take!
	{
		int min_d=1000;
		int d;
		int p=(taker<0 ? 13:2);

		for (int pn=p; pn<p+10; pn++)
		{
			if (teams[pn-1].guy_on>0)
			{
				if (pn<12)
					d=calc_dist(ballx-match_tactics1[ball_zone1][pn-2][0],
						   		bally-match_tactics1[ball_zone1][pn-2][1]);
				else
					d=calc_dist((pitch_len-ballx)-match_tactics2[ball_zone2][pn-13][0],
						   		(pitch_wid-bally)-match_tactics2[ball_zone2][pn-13][1]);

				if (d<min_d)
				{
					min_d=d;
					fkick_taker=pn;
				}
			}
		}
	}

	main_man=fkick_taker;
	last_touch=fkick_taker;
	pre_kp_touch=last_touch;
}

/******************************************************************************
*****************************************************************************/

void init_penalty()
{
	if (!penalty_game)
		PlayCommentaryMessage(SP_PENALTY);

	float x,y,range;

	if (match_mode==PEN_KICK_A)
	{
		ballx=pitch_len-(prat*12);
#ifdef EURO96
		taker_x=ballx-PEN_RUNUP_DIST;
#else
		taker_x=ballx-8;
#endif
	}
	else
	{
		ballx=(prat*12);
#ifdef EURO96
		taker_x=ballx+PEN_RUNUP_DIST;
#else
		taker_x=ballx+8;
#endif
	}

	taker_y=cntspot_y;
	bally=cntspot_y;
	incident_x=ballx;
	incident_y=bally;

// Referee go to spot above penalty spot...
	refs[0].act=1;
	refs[0].target=0;	// Ball!
	refs[0].goto_x=ballx;
	refs[0].goto_y=cntspot_y-(prat*10);

	if ((!penalty_taker) || (!teams[penalty_taker-1].guy_on))
// No particular player chosen nearest can take!
	{
		int min_d=1000;
		int d;
		int p=(match_mode==PEN_KICK_B ? 13:2);

		for (int pn=p; pn<p+10; pn++)
		{
			if (pn<12)
				d=calc_dist(ballx-match_tactics1[ball_zone1][pn-2][0],
						   	bally-match_tactics1[ball_zone1][pn-2][1]);
			else
				d=calc_dist((pitch_len-ballx)-match_tactics2[ball_zone2][pn-13][0],
						   	(pitch_wid-bally)-match_tactics2[ball_zone2][pn-13][1]);

			if (d<min_d)
			{
				min_d=d;
				penalty_taker=pn;
			}
		}
	}

	main_man=penalty_taker;
/*
	if (main_man<12)
	{
// Team A penalty...
		user_keeper_b();
	}
	else		
	{
// Team B penalty...
		user_keeper_a();
	}
*/
}

/******************************************************************************
*****************************************************************************/

void init_match_mode()
{
	ref_wait=(160-ref_strictness)*REAL_SPEED/8;
	support_me=FALSE;
	spec_kick_type=0;
	already_there=FALSE;		// Taker is not in position.
	reselection=FALSE;		// When do I reselect auto users.
	clear_all_autos();		// Clear all auto selected players.

	if (match_mode)
	{
		play_advantage=FALSE;
		setp_wait_cnt=MAX_SETP_WAIT;
		if (ball_limbo_on)
		{
			ball_limbo_on=FALSE;
			teams[ball_limbo_p-1].tm_limbo=FALSE;
		}
		teams[KP_A-1].tm_limbo=0;
		teams[KP_B-1].tm_limbo=0;


		reset_all_ideas();
		holder_lose_ball();
		if (teams[KP_A-1].tm_act==KPHOLD_ACT)
			init_stand_act(&teams[KP_A-1]);

		if (teams[KP_B-1].tm_act==KPHOLD_ACT)
			init_stand_act(&teams[KP_B-1]);
	}

	switch(match_mode)
	{

// Normal Play.
		case(0):
			break;

// Corner.
		case(CORNER_TL):
		case(CORNER_BL):
		case(CORNER_TR):
		case(CORNER_BR):
			set_piece_on=SETP_CORNER;
			can_be_offside=FALSE;
			play_fx(PS_SHORTWHISTLE,refs[0].x,refs[0].y);
			init_corner();
			break;

// Centre.
		case(CENTRE_A):
			if (!team_a_on)
				match_mode=CENTRE_B;
		case(CENTRE_B):
			if (!team_b_on)
				match_mode=CENTRE_A;
			set_piece_on=SETP_CENTRE;
			can_be_offside=TRUE;
			play_fx(PS_SHORTWHISTLE,refs[0].x,refs[0].y);
			init_centre();
			break;

// Goal kick.
		case(GOAL_KICK_TL):
		case(GOAL_KICK_BL):
		case(GOAL_KICK_TR):
		case(GOAL_KICK_BR):
			set_piece_on=SETP_GKICK;
			can_be_offside=FALSE;
			play_fx(PS_SHORTWHISTLE,refs[0].x,refs[0].y);
			init_gkick();
			break;

// Throw in.
		case(THROW_IN_A):
		case(THROW_IN_B):
			set_piece_on=SETP_THROW;
			can_be_offside=FALSE;
			play_fx(PS_SHORTWHISTLE,refs[0].x,refs[0].y);
			init_throw();
			break;

// Indirect free kick.
		case(IF_KICK_A):
			if (!team_a_on)
				match_mode=IF_KICK_B;
		case(IF_KICK_B):
			if (!team_b_on)
				match_mode=IF_KICK_A;
			can_be_offside=TRUE;
			play_fx(PS_LONGWHISTLE,refs[0].x,refs[0].y);
			set_piece_on=SETP_IFKICK;
			init_fkick();
			break;

// Direct free kick.
		case(DF_KICK_A):
			if (!team_a_on)
				match_mode=DF_KICK_B;
		case(DF_KICK_B):
			if (!team_b_on)
				match_mode=DF_KICK_A;
			can_be_offside=TRUE;
			play_fx(PS_LONGWHISTLE,refs[0].x,refs[0].y);
			set_piece_on=SETP_DFKICK;
			init_dfkick();
			break;

// Penalty kick.
		case(PEN_KICK_A):
			if (!team_a_on)
				match_mode=PEN_KICK_B;
		case(PEN_KICK_B):
			if (!team_b_on)
				match_mode=PEN_KICK_A;
			can_be_offside=FALSE;
			play_fx(PS_LONGWHISTLE,refs[0].x,refs[0].y);
			set_piece_on=SETP_PENALTY;
			init_penalty();
			break;

		case(SWAP_ENDS):
			init_swap_ends();
			break;

	}
	setp_taker=main_man;
}

/******************************************************************************
*****************************************************************************/

char offc_thinking()
{
	int f=((129-ref_accuracy)/4)+1;
	int t=logic_cnt/f;
	int r=logic_cnt-(t*f);
	return(!r);
}

/******************************************************************************
*****************************************************************************/

void init_ref_stand(officials *lman)
{
	if (ABS(lman->anim)!=MC_STAND)
	{
		lman->anim=MC_STAND;
		lman->newanim=TRUE;
		lman->frm=0;
		lman->fstep=MC_STAND_FS;
	}
}

/******************************************************************************
*****************************************************************************/

void init_ref_run(officials *lman)
{
	if (ABS(lman->anim)==MC_JOG)
	{
// Tween to run from jog....
		lman->anim=MC_RUN;
		lman->fstep=MC_RUN_FS;
	}
	else
		if (ABS(lman->anim)!=MC_RUN)
		{
			lman->anim=MC_RUN;
			lman->newanim=TRUE;
			lman->frm=0;
			lman->fstep=MC_RUN_FS;
		}
}

/******************************************************************************
*****************************************************************************/

void init_ref_jog(officials *lman)
{
	if (ABS(lman->anim)==MC_RUN)
	{
// Tween to jog from run....
		lman->anim=MC_JOG;
		lman->fstep=MC_JOG_FS;
	}
	else
		if (ABS(lman->anim)!=MC_JOG)
		{
			lman->anim=MC_JOG;
			lman->newanim=TRUE;
			lman->frm=0;
			lman->fstep=MC_JOG_FS;
		}
}

/******************************************************************************
*****************************************************************************/

void init_rtrot_anim(officials *lman)
{
	float x=lman->goto_x-lman->x;
	float y=lman->goto_y-lman->y;

	float d=calc_dist(x,y);

	lman->fstep=MC_TROTA_FS;

	x=x/d;
	y=y/d;

	float nx=(x*lman->dir_x)+(y*lman->dir_y);
	float ny=(y*lman->dir_x)-(x*lman->dir_y);

	if (lman->anim<MC_TROTB || lman->anim>MC_TROTE)
// Not currently in trot animation...
	{
		lman->frm=0;
		lman->newanim=TRUE;
	}
	
	switch((1+get_dir(nx,ny)))
	{
		case(8):
			lman->anim=MC_TROTF;
			break;

		case(7):
			lman->anim=MC_TROTG;
			break;

		case(6):
			lman->anim=MC_TROTH;
			break;

		case(5):
			lman->anim=MC_TROTA;
			break;

		case(4):
			lman->anim=MC_TROTB;
			break;

		case(3):
			lman->anim=MC_TROTC;
			break;

		case(2):
			lman->anim=MC_TROTD;
			break;

		case(1):
			lman->anim=MC_TROTE;
			break;
	}
}

/******************************************************************************
*****************************************************************************/

void init_refs_anim(officials *lman,int an)
{
	switch(an)
	{
		case(MC_STAND):
			init_ref_stand(lman);
			break;

		case(MC_RUN):
			init_ref_run(lman);
			break;

		case(MC_JOG):
			init_ref_jog(lman);
			break;

		case(MC_TROTA):
			init_rtrot_anim(lman);
			break;
	}
}

/******************************************************************************
*****************************************************************************/

void lman_follow(officials *lman)
{
	if (match_mode)
	{
		init_refs_anim(lman,MC_STAND);
		lman->go=12+(129-ref_accuracy)/4;
	}
	else
	{
		float x;
		if (lman->go>0)
			lman->go--;
		else
		{
			if (lman->y<cntspot_y)
// Top Linesman...
			{
				lman->dir_x=0;
				lman->dir_y=1;

				if (ballx>cntspot_x)
					x=((ballx-defense_a)/1.25)*(pitch_wid-bally)/pitch_wid;
				else
					x=0;

				if (defense_a+x-2>lman->x)
				{
					lman->goto_x=lman->x+2;
					if (lman->anim!=MC_TROTG)
						init_refs_anim(lman,MC_TROTA);
					lman->x=lman->goto_x;
				}
				else
					if (defense_a+x+2<lman->x)
					{
						lman->goto_x=lman->x-2;
						if (lman->anim!=MC_TROTC)
							init_refs_anim(lman,MC_TROTA);
						lman->x=lman->goto_x;
					}
					else
					{
						init_refs_anim(lman,MC_STAND);
						lman->go=12+(129-ref_accuracy)/4;
					}
			}
			else
			{
// Bot. Linesman...
				lman->dir_x=0;
				lman->dir_y=-1;

				if (ballx<cntspot_x)
					x=((defense_b-ballx)/1.25)*bally/pitch_wid;
				else
					x=0;

				if (defense_b+x-2>lman->x)
				{
					lman->goto_x=lman->x+2;
					if (lman->anim!=MC_TROTC)
						init_refs_anim(lman,MC_TROTA);
					lman->x=lman->goto_x;
				}
				else
					if (defense_b+x+2<lman->x)
					{
						lman->goto_x=lman->x-2;
						if (lman->anim!=MC_TROTG)
							init_refs_anim(lman,MC_TROTA);
						lman->x=lman->goto_x;
					}
					else
					{
						init_refs_anim(lman,MC_STAND);
						lman->go=12+(129-ref_accuracy)/4;
					}
			}
		}
	}
}

/******************************************************************************
*****************************************************************************/

void await_kicker(officials *offc)
{
	init_refs_anim(&refs[0],MC_STAND);

	if ((!match_mode) && (teams[ktaker-1].tm_act!=THROW_ACT))
		offc->act=0;
	else
	{
		if (!(--ref_wait) && match_mode!=PEN_KICK_A && match_mode!=PEN_KICK_B)
		{
// Time-up!!!
#ifdef STOP_TIME_WASTING
			if (!practice)
#else
			if (!practice && teams[ktaker-1].tm_act!=THROW_ACT)
#endif
			{
				ref_wait=-1;
// Cannot be in practice mode...
				if (teams[ktaker-1].tm_act==THROW_ACT)
				{
// Give away a throw...
					if (ktaker>11)
// Team A gets Throw In...
					{
						match_mode=THROW_IN_A;
						init_match_mode();
						init_stand_act(&teams[ktaker-1]);
						holder_lose_ball();
					}
					else
// Team B gets Throw In...
					{
						match_mode=THROW_IN_B;
						init_match_mode();
						init_stand_act(&teams[ktaker-1]);
						holder_lose_ball();
					}
				}
/*
				else
				{
					if ((match_mode>=CORNER_TL) && (match_mode<=CORNER_BR))
					{
// Give opposing team a Goal Kick...
						match_mode+=6;
						init_match_mode();
						init_stand_act(&teams[setp_taker-1]);
						holder_lose_ball();
					}
					else
					{
// Opposing Team recieves Indirect Free Kick...
						init_foul(ktaker,FALSE,TRUE);
						init_stand_act(&teams[setp_taker-1]);
						holder_lose_ball();
					}
				}
				init_speech(players+1,SAY_TIMEW);
*/
			}
		}
	}
}

/******************************************************************************
*****************************************************************************/

void goto_target(officials *offc)
{
	float tx,ty,x,y,d,bd,nx,ny,ox,oy,dif,spd;

	tx=offc->goto_x-offc->x;
	ty=offc->goto_y-offc->y;

	d=calc_dist(tx,ty);
	tx=tx/d;
	ty=ty/d;

	offc->dir_x=tx;
	offc->dir_y=ty;

	if (d>2.6)
// Not there yet...
	{
		init_refs_anim(offc,MC_JOG);
		spd=2.6;
	}
	else
	{
		init_refs_anim(offc,MC_STAND);
		offc->act=3;	// Face target!
		spd=0;
	}

	offc->x+=tx*spd;
  	offc->y+=ty*spd;
}

/******************************************************************************
*****************************************************************************/

void at_target(officials *referee)
{
// Turns player to face object (ball or player!)

	float nx,ny,x,y,bd,xd,yd,dif;
	float max=(PI/12);

	if (!referee->target)
	{
// Face ball!
		x=ballx-referee->x;
		y=bally-referee->y;
	}
	else
	{
// Face Player!
		x=teams[referee->target-1].tm_x-referee->x;
		y=teams[referee->target-1].tm_x-referee->y;
	}

	bd=calc_dist(x,y);

	x=x/bd;
	y=y/bd;

	xd=referee->dir_x;
	yd=referee->dir_y;

	dif=((x*xd)+(y*yd));

	if (dif<cos(max))
	{
		if ((x*yd)>(y*xd))
			max=-max;

		nx=(xd*cos(max))-(yd*sin(max));
		ny=(yd*cos(max))+(xd*sin(max));
	}
	else
	{
		nx=x;
		ny=y;
		referee->act=4;		// Action complete!
	}

	bd=calc_dist(nx,ny);
	nx=nx/bd;
	ny=ny/bd;

	referee->dir_x=nx;
	referee->dir_y=ny;
}

/******************************************************************************
*****************************************************************************/

void follow_play(officials *referee)
{
	float tx,ty,x,y,d,bd,nx,ny,ox,oy,dif,spd;
	if (!match_mode)
	{
		x=ballx-referee->x;
		y=bally-referee->y;

		bd=calc_dist(x,y);

// Face Ball...
		if (bd>0.2)
		{
			referee->dir_x=x/bd;
			referee->dir_y=y/bd;
		}

		tx=cntspot_x+((ballx-cntspot_x)*0.5)+((last_touch<12) ? (prat*10):(prat*-10));
		ty=cntspot_y+((bally-cntspot_y)*0.5);

		tx=tx-referee->x;
		ty=ty-referee->y;

		d=calc_dist(tx,ty);

		if (d>prat*2)
		{

// Keep distance from ball..
			if ((bd>0.2) && (bd<prat*10) && (!dead_ball_cnt))
			{
				tx-=x*50/bd;
				ty-=y*50/bd;
				d=calc_dist(tx,ty);
			}

			if (d>prat*2)
			{
				referee->goto_x=referee->x+tx;
				referee->goto_y=referee->y+ty;

				tx=tx/d;
				ty=ty/d;

// Get angle of movement Vs facing...
				dif=((referee->dir_x*tx)+(referee->dir_y*ty));
				if (dif>1.0)
					dif=1;

				if (dif<-1.0)
					dif=-1;

				init_refs_anim(&refs[0],MC_TROTA);
				spd=2.2;

				referee->x+=tx*spd;
				referee->y+=ty*spd;
		
			}
			else
			{
					init_refs_anim(&refs[0],MC_STAND);
			}
		}
		else
		{
			init_refs_anim(&refs[0],MC_STAND);
		}
	}
}

/******************************************************************************
*****************************************************************************/

void process_ref(officials *offc)
{
	if (match_mode==SWAP_ENDS)
		init_refs_anim(&refs[0],MC_STAND);
	else
	{

		switch(offc->act)
		{
			case(0):				// Follow Play...
				follow_play(offc);
				break;

			case(1):				// Goto target..
				goto_target(offc);
				break;

			case(2):				// Wait for someone to kick ball..
				await_kicker(offc);
				break;

			case(3):				// Stand and turn...
				at_target(offc);
				break;

			case(4):				// Facing target now...
				at_target(offc);
				break;
		}
	}
}

/******************************************************************************
*****************************************************************************/

void process_lman(officials *offc)
{
	switch(offc->act)
	{
		case(0):				// Follow Play...
			lman_follow(offc);
			break;

		case(1):				// Follow Play...
			goto_target(offc);
			break;
	}
}

/******************************************************************************
*****************************************************************************/

void anim_officials(officials *offc)
{
	offc->frm+=offc->fstep;
}

/******************************************************************************
*****************************************************************************/

void process_offs()
{
	process_ref(&refs[0]);
	process_lman(&refs[1]);
	process_lman(&refs[2]);
	anim_officials(&refs[0]);
	anim_officials(&refs[1]);
	anim_officials(&refs[2]);
}

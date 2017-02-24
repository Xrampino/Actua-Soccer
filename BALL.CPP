/******************************************************************************
*******************************************************************************

Ball movement routines...

******************************************************************************
*****************************************************************************/

#include "global.h"

#include "defines.h"
#include "externs.h"
#include "audio.h"
#include "front.h"
#include "data.h"
#include "eurofrnt\euro_int.h"

extern match_data match_info;

extern setup_info setup;
extern stad_info stadlist[];

/******************************************************************************
*****************************************************************************/

/******************************************************************************
*****************************************************************************/

float get_angle(float x,float y,float d)
{
	float a=(acos(x/d))*180/PI;
	if (y<0)
		a=360-a;
	return(a);
}

/******************************************************************************
*****************************************************************************/

void get_xydis_from_ang(float a,float d)
{
	ballxdis=((float)(d)*cos(a*PI/180));
	ballydis=-((float)(d)*sin(a*PI/180));
}
	
/******************************************************************************
*****************************************************************************/

float get_s_angle(float z,float d)
{
	float a=(asin(z/d))*180/PI;
	return(a);
}

/******************************************************************************
*****************************************************************************/

void get_zdis_from_ang(float a,float d)
{
	ballzdis=((float)(d)*sin(a*PI/180));
}

/******************************************************************************
*****************************************************************************/

void stop_ball_spin()
{
	swerve=0;full_zspin=0;full_xyspin=0;
	ball_zspin=0;ball_xyspin=0;
	max_sw_factor=0;
	swerve_factor=0;
	rebound_ball=FALSE;
	headed_ball=FALSE;
}

/******************************************************************************
*****************************************************************************/

void swerve_xyz()
{
	float x,y,z,d,dz,dn;
	d=calc_dist(ballxdis,ballydis);
	x=ballxdis/d;
	y=ballydis/d;
	dz=calc_dist(ballzdis,d);
	z=ballzdis/dz;
	dn=d/dz;

	ballxdis=d*((x*cos(ball_xyspin))-(y*sin(ball_xyspin)));
	ballydis=d*((y*cos(ball_xyspin))+(x*sin(ball_xyspin)));
	ballzdis=d*((z*cos(ball_zspin))+(dn*sin(ball_zspin)));
}

/******************************************************************************
*****************************************************************************/

void inc_swerve()
{
	spin_cnt++;
  	ball_zspin=-(full_zspin*(SW_HOLD_FACTOR/(SW_HOLD_FACTOR+spin_cnt)));

	if (swerve<0)
		ball_xyspin=-(full_xyspin*(SW_HOLD_FACTOR/(SW_HOLD_FACTOR+spin_cnt)));
	else
		ball_xyspin=(full_xyspin*(SW_HOLD_FACTOR/(SW_HOLD_FACTOR+spin_cnt)));
}

/******************************************************************************
*****************************************************************************/

void get_aftert_spin()
{
	spin_cnt++;
	float xys,zs;
	float x,y,z,d,dz,dn;
	d=calc_dist(ballxdis,ballydis);
	x=ballxdis/d;
	y=ballydis/d;
	dz=calc_dist(ballzdis,d);
	z=ballzdis/dz;
	dn=d/dz;
	
	char u=after_touch_on-1;

#ifdef SUPPORT_LP
	if (users[u].control==LOGPAD_CTRL)
	{
		if (!prediction)
			xys=1;

		xys=0;
		if (users_dir[u].f&4 && !(users_dir[u].f&8))
			xys=1;

		if (users_dir[u].f&8 && !(users_dir[u].f&4))
			xys=-1;
	}
	else
	{
		xys=((users_dir[u].x*shoot_y)-(users_dir[u].y*shoot_x));
	}
#else
		xys=((users_dir[u].x*shoot_y)-(users_dir[u].y*shoot_x));
#endif

	zs=((users_dir[u].x*shoot_x)+(users_dir[u].y*shoot_y));

	ball_xyspin=-(xys*full_xyspin*(SW_HOLD_FACTOR/(SW_HOLD_FACTOR+spin_cnt)));
	ball_zspin=-(zs*full_zspin*(SW_HOLD_FACTOR/(SW_HOLD_FACTOR+spin_cnt)));
//	ball_zspin=0.05;
	ballxdis=d*((x*cos(ball_xyspin))-(y*sin(ball_xyspin)));
	ballydis=d*((y*cos(ball_xyspin))+(x*sin(ball_xyspin)));
	ballzdis=dz*((z*cos(ball_zspin))+(dn*sin(ball_zspin)));
	
	zs=0;
}

/******************************************************************************
*****************************************************************************/

void add_spin_fx()
{
//	if (!prediction)
	{
		if (swerve!=0)
		{
			float d=calc_dist(ballxdis,ballydis);
			if (d<1)
// Ball is hardly travelling (swerve OFF)

				stop_ball_spin();
			else
			{
				inc_swerve();
				swerve_xyz();
			}
		}
		else
		{
			if (after_touch_on)
				get_aftert_spin();
		}

		if (shot_pending)
		{
			swerve_factor=ABS(ball_xyspin);
			if (swerve_factor>max_sw_factor)
				max_sw_factor=swerve_factor;
		}
	}
}

/******************************************************************************
*****************************************************************************/

void move_ball()
{
	ballx+=ballxdis;
	bally+=ballydis;

	if (prediction)
	{
		ns_ballx=ballx;
		ns_bally=bally;
		ns_ballz=ballz;
	}

	if (ball_inair)
	{

		ballz+=ballzdis;
		
		if (ballz<ball_diam/2)
		{
			ballz=ball_diam/2;
			ballzdis=-ballzdis;
			ballzdis-=bounce_dis;
// Landing friction...
			ballxdis=ballxdis-(0.1*ballxdis);
			ballydis=ballydis-(0.1*ballydis);

			if (ballzdis<0)
			{
				ballzdis=0;
				ball_inair=0;
			}
			else
				if (!prediction)
				{
					if (ABS(ballzdis)>7)
						play_fx(PS_HARDBOUNCE,ballx,bally);
					else
						play_fx(PS_SOFTBOUNCE,ballx,bally);
				}
		}

		if (ball_inair)
		{
			add_spin_fx();
			if (!prediction)
			{
				ball_horz_ang+=ball_xyspin*40;

				float x,y,d;
				d=((cos(ball_horz_ang)*launch_x)+(sin(ball_horz_ang)*launch_y));

				if (d>1.0)
					d=1;

				if (d<-1.0)
					d=-1;

				ball_vert_ang+=d*(-ball_zspin*40);

				ball_vert_ang+=IN_AIR_SPIN*launch_type;
			}
		}
	}
}

/******************************************************************************
*****************************************************************************/

void grav_ball()
{
	if (ball_inair)
	{
		ballzdis-=gravity;
	}
}

/******************************************************************************
*****************************************************************************/

void ball_friction()
{
	float	friction_factor;

	if (ball_inair)
		friction_factor=AIR_FRICTION;
	else
		friction_factor=GRND_FRICTION;
		
	if (wind_on)
// Wind Fx...
	{
		float wf=wind_speed/(800-(ballz*2));
		if (wf>MAX_WIND)
			wf=MAX_WIND;

		ballxdis+=wind_x*wf;
		ballydis+=wind_y*wf;
	}

	ballxdis=(friction_factor*ballxdis);
	ballydis=(friction_factor*ballydis);

	if (!ball_inair)
	{
		if ((ballxdis>-0.25) && (ballxdis<0.25))
			ballxdis=0;
		
		if ((ballydis>-0.25) && (ballydis<0.25))
			ballydis=0;
	}
}

/******************************************************************************
*****************************************************************************/

void roll_ball()
{
	if ((!prediction) && (!ball_inair))
	{
// Roll ball...
		float x=ballxdis;
		float y=ballydis;
		float d=calc_dist(x,y);
		x=x/d;
		y=y/d;

		ball_horz_ang=acos(x);
		if (y<0)
			ball_horz_ang=(PI*2)-ball_horz_ang;

		ball_vert_ang+=d/ball_diam;
	}
}

/******************************************************************************
*****************************************************************************/

void ball_trajectory()
{
	if (!ball_poss)
	{
		if (game_action==-1)
			game_action=0;
		move_ball();
		grav_ball();
		ball_friction();
	}

	if (ballxdis || ballydis)
	{
		ball_still=0;
		if ((!ball_in_hands) || (!ball_poss))
			roll_ball();
	}
	else
		ball_still=1;
}

/******************************************************************************
*****************************************************************************/

void get_ball_zone()
{
	if ((!ball_out_of_play) && ((!match_mode) || (match_mode>GOAL_KICK_BR)))
	{
		if (ball_in_hands)
		{
			if (ball_poss==KP_A)
			{
// Pretend Goal kick for A...
				ball_zone1=11;
				ball_zone2=20;
			}
			else
			{
				if (ball_poss==KP_B)
				{
// Pretend Goal kick for B...
					ball_zone1=19;
					ball_zone2=12;
				}
			}
		}
		else
		{
			int bx1=ballx;
			int bx2=ballx;
			int by1=bally;
			int by2=bally;
			bx1=((bx1+(zone_wid/2))/(zone_wid));
			zone1_x=bx1*zone_wid;
			bx2=7-bx1;
			zone2_x=bx2*zone_wid;
			by1=((by1+(zone_hgt/2))/(zone_hgt));
			zone1_y=by1*zone_hgt;
			by2=3-by1;
			zone2_y=by2*zone_hgt;
			if (by2>=0)
			{
				ball_zone1=(by1*8)+bx1;
				ball_zone2=(by2*8)+bx2;
			}
		}
	}
}

/******************************************************************************
*****************************************************************************/

void launch_ball(int p)
{
	float d=calc_dist(ballxdis,ballydis);
	if (d>0.2)
	{
		launch_x=ballxdis/d;
		launch_y=ballydis/d;
		ball_horz_ang=acos(launch_x);
		if (launch_y<0)
			ball_horz_ang=(PI*2)-ball_horz_ang;
	  	launch_type=p;
	}
}

/******************************************************************************
*****************************************************************************/

void reset_shot()
{
	real_shot=FALSE;
	shot_acknowledged=FALSE;
	shot_pending=FALSE;
	after_touch_on=FALSE;
	swerve=FALSE;
}

/******************************************************************************
*****************************************************************************/

void new_shot(int p)
{
	if (men_in_wall>1)
		wall_is_up=TRUE;
	else
		wall_is_up=FALSE;

	float r;
	shot_acknowledged=FALSE;
	must_shoot=FALSE;
	shooter=p;
	if (ballx>cntspot_x || (ballx<=cntspot_x && ballxdis>ABS(ballydis)))
// Keeper B to see it...
	{
		r=teams[KP_B-1].tm_dist;
		shot_pending=-1-((128-teams[KP_B-1].tm_vis)/10);

		if (r<LONG_RANGE && shot_pending<-1)
			shot_pending=(((r*1.4)/LONG_RANGE)*(shot_pending+1))-1;

		if (penalty_shot && teams[KP_B-1].control)
			shot_pending=-1;
	}
	else
// Keeper A to see it...
		if (ballx<=cntspot_x || (ballx>cntspot_x && ballxdis<ABS(ballydis)))
		{
			r=teams[KP_A-1].tm_dist;
			shot_pending=-1-((128-teams[KP_A-1].tm_vis)/10);

			if (r<LONG_RANGE && shot_pending<-1)
				shot_pending=(((r*1.4)/LONG_RANGE)*(shot_pending+1))-1;

			if (penalty_shot && teams[KP_A-1].control)
				shot_pending=-1;
		}
}

/******************************************************************************
*****************************************************************************/

void reset_ball()
{
	holder_lose_ball();
	ballz=ball_diam/2;ballxdis=0;ballydis=0;ballzdis=0;
	ball_zspin=0;ball_xyspin=0;
	ball_inair=0;ball_still=1;super_shot=0;
	ball_in_goal=FALSE;
	last_touch=0;
	shot_attempt=0;
	stop_ball_spin();
	reset_all_ideas();
	reset_shot();
	use_ball_limit=FALSE;
}

/******************************************************************************
*****************************************************************************/

void respot_ball()
{
	if (shot_pending && match_mode>=GOAL_KICK_TL && match_mode<=GOAL_KICK_BR)
		fired_a_shot=TRUE;
	else
		fired_a_shot=FALSE;

	reset_ball();

	if (!penalty_game)
	{
		if (last_goal==1)	
		{
			match_mode=CENTRE_B;
			last_goal=0;
		}
	
		if (last_goal==2)
		{
			match_mode=CENTRE_A;
			last_goal=0;
		}
	
		if (match_mode)
			init_match_mode();		
	}
}

/******************************************************************************
*****************************************************************************/

void shot_passed()
{
	float d;
	if (ballx<0)
	{
// Left goal...
		d=calc_dist(ballx,bally-cntspot_y);
		if (d>prat*8)
			shot_missed=-25;		// Laughable attempt!
		else
			if (ballz>prat*5)
				shot_missed=-25;		// Laughable attempt!
			else
				shot_missed=25;		// good attempt!
	}
	else
	{
		if (ballx>pitch_len)
		{
// Right goal...
			d=calc_dist(ballx-pitch_len,bally-cntspot_y);
			if (d>prat*8)
				shot_missed=-15;		// Laughable attempt!
			else
				if (ballz>prat*5)
					shot_missed=-15;		// Laughable attempt!
				else
					shot_missed=15;		// good attempt!
		}
	}
}

/******************************************************************************
*****************************************************************************/

void stadium_bounds()
{
	if (ballx>(pitch_len+stadlist[setup.stadium].st_l))
	{
		ballx=(pitch_len+stadlist[setup.stadium].st_l);
		ballxdis=-ballxdis;
	}
	else
		if (ballx<-stadlist[setup.stadium].st_l)
		{
			ballx=-stadlist[setup.stadium].st_l;
			ballxdis=-ballxdis;
		}
		else
			if (bally>(pitch_wid+stadlist[setup.stadium].st_w))
			{
				bally=(pitch_wid+stadlist[setup.stadium].st_w);
				ballydis=-ballydis;
			}
			else
				if (bally<-stadlist[setup.stadium].st_w)
				{
					bally=-stadlist[setup.stadium].st_w;
					ballydis=-ballydis;
				}
}

/******************************************************************************
*****************************************************************************/

void pitch_bounds()
{
	if ((ballx<0) || (ballx>=pitch_len) || (bally<0) || (bally>=pitch_wid))
	{
		if ((!((ball_poss) && (teams[ball_poss-1].tm_act==THROW_ACT)))
			&& (just_thrown==FALSE))
		{
// Not taking throw in...
			if (play_advantage)
			{
				retake_foul();
			}
			else
			{
				use_ball_limit=TRUE;
				ballx_out=ballx;
				bally_out=bally;
				ballz_out=ballz;

				if (shot_pending)
					shot_passed();			// For crowd noise...
				ball_out_of_play=25;
				match_mode=bounds_rules();
			}
		}
	}
}

/******************************************************************************
*****************************************************************************/

void rebound_post()
{
// Ball strikes post and rebounds off maintaining zdis...
	shot_passed();			// For crowd noise...

	float x,y,d,ang;

	d=calc_dist(ballxdis,ballydis);
	x=ballxdis/d;
	y=ballydis/d;

// Get angle to come off ( favours 180 degrees )...

	ang=(float)(seed);
	af_randomize();
	ang+=(float)seed;
	af_randomize();			// Favour 128...

	ang=ang*PI/128;

	ballxdis=((x*cos(ang))-(y*sin(ang)))*d*REBOUND_FACTOR;
	ballydis=((y*cos(ang))+(x*sin(ang)))*d*REBOUND_FACTOR;

	rebound_ball=TRUE;

	if (shot_pending)
		PlayCommentaryMessage(PM_POST);
	
}

/******************************************************************************
*****************************************************************************/

void rebound_bar()
{
// Ball strikes cross-bar and rebounds off maintaining x,ydis...
	shot_passed();			// For crowd noise...

	float z,d,ndxy,dxy,ang;

	dxy=calc_dist(ballxdis,ballydis);
	d=calc_dist(dxy,ballzdis);
	z=ballzdis/d;

// Get angle to come off ( favours 180 degrees )...

	ang=(float)(seed);
	af_randomize();
	ang+=(float)seed;
	af_randomize();			// Favour 128...

	ang=ang*PI/128;

	ballzdis=((z*cos(ang))-(dxy/d*sin(ang)))*d*REBOUND_FACTOR;
	ndxy=ABS(((dxy/d*cos(ang))+(z*sin(ang)))*d*REBOUND_FACTOR);

	ballxdis=-ballxdis*(ndxy/dxy);
	ballydis=ballydis*(ndxy/dxy);

	rebound_ball=TRUE;

	if (shot_pending)
		PlayCommentaryMessage(PM_CROSSBAR);
}

/******************************************************************************
*****************************************************************************/

void own_goal()
{
	goal_scorer=last_touch;

	inc_ogs(goal_scorer);

	if (penalty_game)
		just_scored=PEN_SCORE_WAIT;
	else
		just_scored=SCORE_WAIT;

	reset_shot();
	holder_lose_ball();
	ball_out_of_play=25;	
	do_goal_anim(0);
	shamed_player=goal_scorer;
}

/******************************************************************************
*****************************************************************************/

void good_goal()
{
	inc_goal(goal_scorer);

	if (penalty_game)
		just_scored=PEN_SCORE_WAIT;
	else
		just_scored=SCORE_WAIT;

	reset_shot();
	holder_lose_ball();
	ball_out_of_play=25;
	do_goal_anim(0);
	shamed_player=0;
}

/******************************************************************************
*****************************************************************************/

void hit_goal_post()
{
	rebound_post();
	if (ballx>cntspot_x)
		ballx=pitch_len-1;
	else
		ballx=1;
	reset_shot();
}

/******************************************************************************
*****************************************************************************/

void hit_cross_bar()
{
	rebound_bar();
	if (ballx>cntspot_x)
		ballx=pitch_len-1;
	else
		ballx=1;
	reset_shot();
}

/******************************************************************************
*****************************************************************************/

void hit_high_side_net()
{
	if (swerve!=0)
		stop_ball_spin();
	ballzdis=ballzdis/2;
	ballxdis=ballxdis/2;
	ballydis=-ballydis/2;
	bally=top_post_y;
}

/******************************************************************************
*****************************************************************************/

void hit_low_side_net()
{
	if (swerve!=0)
		stop_ball_spin();
	ballzdis=ballzdis/2;
	ballxdis=ballxdis/2;
	ballydis=-ballydis/2;
	bally=bot_post_y;
}

/******************************************************************************
*****************************************************************************/

void hit_top_net()
{
	if (swerve!=0)
		stop_ball_spin();
	ballz=goal_height+1;
	ballzdis=0;

	if (ballxdis<0)
		ballxdis-=2;
	else
		ballxdis+=2;

	ballxdis=ballxdis/2;
	ballydis=ballydis/2;
}

/******************************************************************************
*****************************************************************************/

void hit_inside_back_net()
{
	if (swerve!=0)
		stop_ball_spin();
	ballzdis=ballzdis/2;
	ballxdis=-ballxdis/2;
	ballydis=ballydis/2;
	ballx=1-goal_depth;
}

/******************************************************************************
*****************************************************************************/

void hit_inside_back_net_r()
{
	if (swerve!=0)
		stop_ball_spin();
	ballzdis=ballzdis/2;
	ballxdis=-ballxdis/2;
	ballydis=ballydis/2;
	ballx=pitch_len+goal_depth-1;
}

/******************************************************************************
*****************************************************************************/

void hit_inside_top_net()
{
	if (swerve!=0)
		stop_ball_spin();
	ballz=goal_height-1;
	ballzdis=0;

	ballxdis=ballxdis/2;
	ballydis=ballydis/2;
}

/******************************************************************************
*****************************************************************************/

void hit_inside_high_side()
{
	if (swerve!=0)
		stop_ball_spin();
	ballzdis=ballzdis/2;
	ballxdis=ballxdis/2;
	ballydis=-ballydis/2;
	bally=top_post_y+1;
}

/******************************************************************************
*****************************************************************************/

void hit_inside_low_side()
{
	if (swerve!=0)
		stop_ball_spin();
	ballzdis=ballzdis/2;
	ballxdis=ballxdis/2;
	ballydis=-ballydis/2;
	bally=bot_post_y-1;
}

/******************************************************************************
*****************************************************************************/

short real_player(short p)
{
	if (match_half&1)
	{
// swapped...
		p=((p>11) ? p-11:p+11);
	}
	return(p);
}

/******************************************************************************
*****************************************************************************/

short standard_player(short p)
{
	if (p>11)
		p-=11;
	return(p);
}

/******************************************************************************
*****************************************************************************/

short country(char t)
{
	short p;
	if (t)
		p=setup.team_b;
	else
		p=setup.team_a;

	return(p);
}

/******************************************************************************
*****************************************************************************/

void go_right_goal()
{
	if (golden_goal && (match_half>1 && match_half<4))
	{
// Sudden death... Golden goal has been scored! (End of match)
		golden_goal=2;
	}

	if (!ball_out_of_play)
	{
		ball_in_goal=TRUE;
		last_goal=1;

		if (match_mode==NORMAL_PLAY)
		{
			if (match_half&1)
				team_b_goals++;
			else
				team_a_goals++;

			if (penalty_game)
				EUROmatch_info.Team_B_penalties++;

			if (last_touch>11)
// Deflection, own goal or keeper's poss...
			{
				if (last_touch==KP_B)
				{
// Keeper bad save...
					PlayCommentaryMessage(GL_KEEPER);
					goal_scorer=pre_kp_touch;
					if (goal_scorer<12)
					{
// Opposition scored...
						do_goal_menu(team_a,standard_player(goal_scorer)-1,match_time.min);
						if (!penalty_game)
							GOAL_SCORED(0,(int)real_player(goal_scorer)-1,(int)match_time.min+(penalty_shot ? 256:0));
						good_goal();
					}
					else
					{
// Own goal...
						do_owngoal_menu(team_b,standard_player(goal_scorer)-1,match_time.min);
						if (!penalty_game)
							GOAL_SCORED(0,(int)real_player(goal_scorer)-1,(int)match_time.min+512+(penalty_shot ? 256:0));
						own_goal();
					}
				}
				else
				{
					PlayCommentaryMessage(GL_DEFLECT);
					do_owngoal_menu(team_b,standard_player(last_touch)-1,match_time.min);
					if (!penalty_game)
						GOAL_SCORED(0,real_player(last_touch)-1,match_time.min+512+(penalty_shot ? 256:0));
					own_goal();
				}
			}
			else
			{
				if (headed_ball)
					PlayCommentaryMessage(GL_HEADER);
				else
					if (rebound_ball)
						PlayCommentaryMessage(GL_POST);
					else
						if (max_sw_factor>GOOD_SWERVE)
							if (wall_is_up)
								PlayCommentaryMessage(GL_CURVEWALL);
							else
								PlayCommentaryMessage(GL_CURVE);
						else
							if (shot_speed>18)
								PlayCommentaryMessage(GL_HARDKICK);
							else
								PlayCommentaryMessage(GL_GENERIC);

				do_goal_menu(team_a,standard_player(last_touch)-1,match_time.min);
				if (!penalty_game)
					GOAL_SCORED(0,real_player(last_touch)-1,match_time.min+(penalty_shot ? 256:0));

				goal_scorer=last_touch;
				good_goal();
			}
		}
	PauseCommentary();
	}
}

/******************************************************************************
*****************************************************************************/

void go_left_goal()
{
	if (golden_goal && (match_half>1 && match_half<4))
	{
// Sudden death... Golden goal has been scored! (End of match)
		golden_goal=2;
	}

	if (!ball_out_of_play)
	{
		ball_in_goal=TRUE;
		last_goal=2;

		if (match_mode==NORMAL_PLAY)
		{
			if (match_half&1)
				team_a_goals++;
			else
				team_b_goals++;

			if (penalty_game)
				EUROmatch_info.Team_A_penalties++;

			if (last_touch<12)
// Deflection, own goal or keeper's poss...
			{
				if (last_touch==KP_A)
				{
// Keeper bad save...
					PlayCommentaryMessage(GL_KEEPER);
					goal_scorer=pre_kp_touch;
					if (goal_scorer>11)
					{
// Opposition scored...
						do_goal_menu(team_b,standard_player(goal_scorer)-1,match_time.min);
						if (!penalty_game)
							GOAL_SCORED(0,(int)real_player(goal_scorer)-1,(int)match_time.min+(penalty_shot ? 256:0));
						good_goal();
					}
					else
					{
// Own goal...
						do_owngoal_menu(team_a,standard_player(goal_scorer)-1,match_time.min);
						if (!penalty_game)
							GOAL_SCORED(0,(int)real_player(goal_scorer)-1,(int)match_time.min+512+(penalty_shot ? 256:0));
						own_goal();
					}
				}
				else
				{
					PlayCommentaryMessage(GL_DEFLECT);
					do_owngoal_menu(team_a,standard_player(last_touch)-1,match_time.min);
					if (!penalty_game)
						GOAL_SCORED(0,real_player(last_touch)-1,match_time.min+512+(penalty_shot ? 256:0));
					own_goal();
				}
			}
			else
			{
				if (headed_ball)
					PlayCommentaryMessage(GL_HEADER);
				else
					if (rebound_ball)
						PlayCommentaryMessage(GL_POST);
					else
						if (max_sw_factor>GOOD_SWERVE)
							PlayCommentaryMessage(GL_CURVE);
						else
							if (shot_speed>16)
								PlayCommentaryMessage(GL_HARDKICK);
							else
								PlayCommentaryMessage(GL_GENERIC);

				do_goal_menu(team_b,standard_player(last_touch)-1,match_time.min);
				if (!penalty_game)
					GOAL_SCORED(0,real_player(last_touch)-1,match_time.min+(penalty_shot ? 256:0));

				goal_scorer=last_touch;
				good_goal();
			}
		}
	PauseCommentary();
	}
}

/******************************************************************************
*****************************************************************************/

void outside_of_net(float f,float y,float z)
{
	float dx=ballx-prev_ballx;
	float dy=bally-prev_bally;
	float dz=ballz-prev_ballz;
	float x;

	if ((ballx<0 && prev_ballx>=0) || (ballx>pitch_len && prev_ballx<=pitch_len))
	{
		if ((z>=goal_height) && (z<goal_height+post_width)
			&& (y>top_post_y-post_width) && (y<bot_post_y+post_width))
// Hit cross Bar...
		{
			hit_cross_bar();
		}
		else
		{
			if ((z<goal_height) && (y>top_post_y-post_width)
				&& (y<=top_post_y))
// Hit Top post...
			{
				hit_goal_post();
			}
			else
			{
				if ((z<goal_height) && (y<bot_post_y+post_width)
					&& (y>=bot_post_y))
// Hit Bot post...
				{
					hit_goal_post();
				}
				else
				{
// Try top-side netting...
					f=(top_post_y-prev_bally)/dy;
					z=prev_ballz+(f*dz);
					x=prev_ballx+(f*dx);

					if (((x>-goal_depth && x<0)
						|| (x<pitch_len+goal_depth && x>pitch_len))
		 				&& (z<goal_height))
// Hit high side netting...
					{
						hit_high_side_net();
					}
					else
// Try low-side netting...
					{
						f=(bot_post_y-prev_bally)/dy;
						z=prev_ballz+(f*dz);
						x=prev_ballx+(f*dx);

						if (((x>-goal_depth && x<0)
							|| (x<pitch_len+goal_depth && x>pitch_len))
							&& (z<goal_height))
// Hit low side netting...
						{
			 				hit_low_side_net();
						}
					}
 				}
			}
		}
	}
	else
	{
		if ((ballz<goal_height) && (prev_ballz>=goal_height))
// Falling... check top net...
		{
			f=(goal_height-prev_ballz)/dz;
			y=prev_bally+(f*dy);
			x=prev_ballx+(f*dx);

			if (((x>-goal_depth && x<0)
				|| (x<pitch_len+goal_depth && x>pitch_len))
				&& (y>top_post_y) && (y<bot_post_y))
// On top of net...
			{
				hit_top_net();
			}
			else
// Try top-side netting...
			{
				f=(top_post_y-prev_bally)/dy;
				z=prev_ballz+(f*dz);
				x=prev_ballx+(f*dx);

				if (((x>-goal_depth && x<0)
					|| (x<pitch_len+goal_depth && x>pitch_len))
				 	&& (z<goal_height))
// Hit high side netting...
				{
					hit_high_side_net();
				}
				else
// Try low-side netting...
				{
					f=(bot_post_y-prev_bally)/dy;
					z=prev_ballz+(f*dz);
					x=prev_ballx+(f*dx);

					if (((x>-goal_depth && x<0)
						|| (x<pitch_len+goal_depth && x>pitch_len))
						&& (z<goal_height))
// Hit low side netting...
					{
					 	hit_low_side_net();
					}
				}
			}
		}
	}
}

/******************************************************************************
*****************************************************************************/

void is_it_a_goal()
{
	float dx=ballx-prev_ballx;
	float dy=bally-prev_bally;
	float dz=ballz-prev_ballz;
	float f,x,y,z;

	if (!ball_in_goal)
// Not inside goal-net...
	{
		if (ballx<0)
// Crossed Left goal-line...
		{
			f=prev_ballx/dx;
			y=prev_bally-(f*dy);
			z=prev_ballz-(f*dz);

			if (prev_ballx>=0)
			{
// Just crossed goal-line...

				if ((z<goal_height) && (y>top_post_y) && (y<bot_post_y))
// Its a goal!!!!
				{
					go_left_goal();
				}
				else
				{
					outside_of_net(f,y,z);
				}
			}
			else
			{
			 	outside_of_net(f,y,z);
			}
		}
		else
// Behind Left goal-line...
		{
			if (ballx>pitch_len)
			{
				f=(pitch_len-prev_ballx)/dx;
				y=prev_bally+(f*dy);
				z=prev_ballz+(f*dz);

				if (prev_ballx<pitch_len)
				{
					if ((z<goal_height) && (y>top_post_y) && (y<bot_post_y))
// Its a goal!!!!
					{
						go_right_goal();
					}
					else
					{
						outside_of_net(f,y,z);
					}
				}
				else
				{
			 		outside_of_net(f,y,z);
				}
			}
		}
	}
	else
// Inside goal-net...
	{
		if (ballx<0)
// Inside left goal...
		{
			if (ballx<-goal_depth)
				hit_inside_back_net();
			if (bally<top_post_y)
				hit_inside_high_side();
			if (bally>bot_post_y)
				hit_inside_low_side();
			if (ballz>goal_height)
				hit_inside_top_net();
		}
		else
// Inside right goal...
		{
			if (ballx>pitch_len+goal_depth)
				hit_inside_back_net_r();
			if (bally<top_post_y)
				hit_inside_high_side();
			if (bally>bot_post_y)
				hit_inside_low_side();
			if (ballz>goal_height)
				hit_inside_top_net();
		}
	}
}


/******************************************************************************
*****************************************************************************/

void ball_collision()
{		
	is_it_a_goal();
		
	prev_ballx=ballx;
	prev_bally=bally;
	prev_ballz=ballz;
}

/******************************************************************************
*****************************************************************************/

void oball_collision()
{
	if (ballx<cntspot_x)
	{

// Left side
		if (!ball_in_goal)
		{

// Not in goal
			if (ballx<0)
			{
// Behind posts
				if (prev_ballx>=-goal_depth)
				{
					if ((prev_ballz<goal_height) || (ballz<goal_height))
					{
						if (bally<cntspot_y)
						{
// High side
							if ((bally>top_post_y) || (prev_bally>top_post_y))
								{
								if ((ballz-ballzdis)>=goal_height)
									hit_top_net();
								if ((bally-ballydis)<=top_post_y)
								{
									if ((ballx-ballxdis>post_width)
										&& (ABS(ballxdis)>ABS(ballydis)))
										hit_goal_post();
									else
										hit_high_side_net();
								}
								else
									go_left_goal();
								}
						}
						else
						{
// Low side
							if (bally<bot_post_y)
								{
								if ((ballz-ballzdis)>=goal_height)
									hit_top_net();
								if ((bally-ballydis)>=cntspot_y+(4*prat))
								{
									if ((ballx-ballxdis>post_width)
										&& (ABS(ballxdis)>ABS(ballydis)))
										hit_goal_post();
									else
										hit_low_side_net();
								}
								else
									go_left_goal();
								}
						}
					}
				}
			}
			else
			{
				if (ballx<=post_width)
// On goal line
				{
					if ((bally>top_post_y-post_width)
						&& (bally<=top_post_y)
						&& (ballz<=goal_height))
						hit_goal_post();
						
					if ((bally<bot_post_y+post_width)
						&& (bally>=bot_post_y)
						&& (ballz<=goal_height))
						hit_goal_post();

					if ((bally>top_post_y-post_width)
						&& (bally<bot_post_y+post_width)
						&& (ballz>=goal_height)
						&& (ballz<goal_height+post_width))
						hit_cross_bar();
				}	
			}
		}
		else
		{
// Inside Left goal
			if (ballx<-goal_depth)
				hit_inside_back_net();
			if (bally<top_post_y)
				hit_inside_high_side();
			if (bally>bot_post_y)
				hit_inside_low_side();
			if (ballz>goal_height)
				hit_inside_top_net();
		}
	}
	else
	{
// Right side
		if (!ball_in_goal)
		{

// Not in goal
			if (ballx>pitch_len)
			{
// Behind posts
				if (ballx<=pitch_len+goal_depth)
				{
					if (ballz<goal_height)
					{
						if (bally<cntspot_y)
						{
// High side
							if (bally>top_post_y)
								{
								if ((ballz-ballzdis)>=goal_height)
									hit_top_net();
								if ((bally-ballydis)<=top_post_y)
								{
									if ((ballx-ballxdis<pitch_len-post_width)
										&& (ABS(ballxdis)>ABS(ballydis)))
										hit_goal_post();
									else
										hit_high_side_net();
								}
								else
									go_right_goal();
								}
						}
						else
						{
// Low side
							if (bally<bot_post_y)
								{
								if ((ballz-ballzdis)>=goal_height)
									hit_top_net();
								if ((bally-ballydis)>=cntspot_y+(4*prat))
								{
									if ((ballx-ballxdis<pitch_len-post_width)
										&& (ABS(ballxdis)>ABS(ballydis)))
										hit_goal_post();
									else
										hit_low_side_net();
								}
								else
									go_right_goal();
								}
						}
					}
				}
			}
			else
			{
				if (ballx>=pitch_len-post_width)
// On goal line
				{
					if ((bally>top_post_y-post_width)
						&& (bally<=top_post_y)
						&& (ballz<=goal_height))
						hit_goal_post();
						
					if ((bally<bot_post_y+post_width)
						&& (bally>=bot_post_y)
						&& (ballz<=goal_height))
						hit_goal_post();

					if ((bally>top_post_y-post_width)
						&& (bally<bot_post_y+post_width)
						&& (ballz>=goal_height)
						&& (ballz<goal_height+post_width))
						hit_cross_bar();
				}	
			}
		}
		else
		{
// Inside Right goal
			if (ballx>pitch_len+goal_depth)
				hit_inside_back_net_r();
			if (bally<top_post_y)
				hit_inside_high_side();
			if (bally>bot_post_y)
				hit_inside_low_side();
			if (ballz>goal_height)
				hit_inside_top_net();
		}
	}
}

/******************************************************************************
*****************************************************************************/

void get_ball_speed()
{
	float tot=ABS(ballxdis)+ABS(ballydis)+ABS(ballzdis);
	ball_speed=sqrt(tot);
}

/******************************************************************************
*****************************************************************************/

void ball_limbo(int p,float c)
{
	ball_limbo_c=ABS(c);
	ball_limbo_p=p;
	ball_limbo_on=TRUE;
}

/******************************************************************************
*****************************************************************************/

void ball_possession()
{

// Calculate possession for audio...
	if (!just_scored && !match_mode && last_touch!=KP_A && last_touch!=KP_B)
	{
		good_poss+=(last_touch<12 ? ballx/20:-(pitch_len-ballx)/20);
	}

	if (ABS(good_poss)>MAX_GOOD_POSS)
	{
		if (audio_version)
			PlayPossessionSample((good_poss<0 ? team_b:team_a));

		good_poss=0;
	}
}

/******************************************************************************
*****************************************************************************/

void process_ball()
{
	ball_possession();

	if (ball_limbo_on>0)
	{

// Ball is bound to a player's animation and should not be processed
// until the contact point of animation is exceeded...

		if (teams[ball_limbo_p-1].tm_frm+teams[ball_limbo_p-1].tm_fstep>ball_limbo_c)
// Contact exceeded...
		{
			ball_limbo_on=FALSE;
			if (teams[ball_limbo_p-1].tm_anim==MC_KICKOUT)
				play_fx(PS_HARDKICK,ballx,bally);
		}				
	}

	if ((!ball_limbo_on) && (!ball_poss || (ball_poss && teams[ball_poss-1].contact<0)))
	{
		prediction=FALSE;

		if (shot_acknowledged)
			shot_acknowledged--;				// Counter for re-acknowledgement.

//	if ((shot_pending) && (shooter==last_touch))
		if (shot_pending)
		{
			if (!(++shot_pending))
				shot_pending=1;
		}
		else
		{
			shot_pending=0;
			real_shot=0;
		}

		get_ball_speed();
		if (ball_out_of_play)
		{
			ball_trajectory();
			ball_collision();
			if (just_scored)
			{
				if (!(--just_scored))
				{
					ResumeCommentary();
					PlayScoreSample(team_a_goals,team_b_goals);
				}
			}
			else
			{
				if (!--ball_out_of_play && match_mode!=SWAP_ENDS)
				{
					respot_ball();
					get_ball_zone();
					predict_ball();
				}
			}
			stadium_bounds();
		}
		else
		{
			ball_trajectory();
			ball_collision();
			if (!just_scored && match_mode!=SWAP_ENDS && match_half<=10)
			{
				pitch_bounds();
				get_ball_zone();
				predict_ball();
			}
		}
	}
}


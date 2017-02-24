/******************************************************************************
*******************************************************************************/

// Player intelligence and decision making routines...

/******************************************************************************
*****************************************************************************/

#include "global.h"
#include "defines.h"
#include "externs.h"
#include "data.h"
#include "audio.h"							// Kev's audio calls.
#include "front.h"
#include "eurofrnt\euro_int.h"

extern match_data match_info;
extern team_info game_data[];
extern float save_offs[];
extern setup_info setup;
extern stad_info stadlist[];
extern void reselect_a();
extern void reselect_b();

/******************************************************************************
*****************************************************************************/

//  Intelligence Flags and Variables...

char cross_on=FALSE;

/******************************************************************************
*****************************************************************************/

short get_there_time(int p_num,float x,float y)
{
	stop_and_face=FALSE;

	must_face_time=0;
	int t1=0;
	int t2=0;
	int mft1=0;
	int mft2=0;
	int t;
	int mft;
	float d;
	float rate=full_spd(&teams[p_num-1]);  // Running speed!
	float px,py;
	px=teams[p_num-1].tm_x;
	py=teams[p_num-1].tm_y;
	x=x-px;
	y=y-py;		// Offset.

	float sx=x;
	float sy=y;

	float xd=teams[p_num-1].tm_xdis;
	float yd=teams[p_num-1].tm_ydis; //Current facing dir.

	float max=MAX_TURN2;
	float old_max=max;
	float cmax=cos(max);
	float ox,oy,a,turn_spd,last_a;

// Player must have ball slightly

	if (teams[p_num-1].tm_act<=TURN_ACT)
	{
// Can i turn on the spot?
		a=angle_to_xy(x,y,xd,yd);
		t1=ABS(acos(a)/max);		// time to turn!

// Time to go straight to point...
		d=calc_dist(x,y);
		t1+=d/rate+1;

		if (must_face)
		{
// User forced to face in a particular direction (after getting to target)...
			a=angle_to_xy(must_face_x,must_face_y,x/d,y/d);
			mft1=ABS(acos(a)/max)+1;		// time to turn!
		}
	}
	else
		t1=2000;

	a=angle_to_xy(x,y,xd,yd);
	last_a=a;

	d=calc_dist(x,y);

// Time to get to target point...
	for (int i=0; i<50; i++)
	{

// Init run...
		if (d<IM_THERE_DIST)
			break;
		else
			t2++;

// Go forward...
		turn_spd=(1.0+a)/2;

		x-=xd*rate*turn_spd;		// Move on...
		y-=yd*rate*turn_spd;

// Turn...

		d=calc_dist(x,y);

		ox=xd;
		oy=yd;

		max=old_max;

		if (a<cmax)
		{
// Need to turn...

			if ((x*oy/d)>(y*ox/d))
				max=-max;

			xd=(ox*cos(max))-(oy*sin(max));
			yd=(oy*cos(max))+(ox*sin(max));
		}
		else
		{
// Final turn...
//			xd=x/d;
//			yd=y/d;
			t2+=d/rate;
			if (d-((t2-1)*rate)>.1)
				t2++;
			break;
		}

		last_a=a;
		a=angle_to_xy(x,y,xd,yd);

		if (last_a>a)
// Getting further forget it!
		{
			t2=2000;
			break;		// (exit)
		}
	}

	if (i>50)
		t=2000;		// Could not find intersection!

	if (must_face)
	{
// User forced to face in a particular direction (after getting to target)...
		a=angle_to_xy(must_face_x,must_face_y,xd,yd);
		mft2=ABS(acos(a)/max)+1;		// time to turn!
	}

	if ((t1+mft1)<(t2+mft2))
	{
// Rotate and run...
		t=t1+mft1;
		mft=mft1;
		d=calc_dist(sx,sy);
		x_face=sx/d;		// New dir...
		y_face=sy/d;
		stop_and_face=TRUE;
	}
	else
	{
// Turn and run...
		t=t2+mft2;
		mft=mft2;
		x_face=x/d;		// New dir...
		y_face=y/d;
	}

	if (must_face)
	{
		x_face=must_face_x;
		y_face=must_face_y;
		must_face_time=mft;
	}

	return(t);
}

/******************************************************************************
*****************************************************************************/

short get_facing_opp_dir(match_player *player)
{

/*

Output: 1 = Side On.
		 -1 = Behind.
		  0 = Face On.

*/

	int d=get_dir(ballx-player->tm_x,bally-player->tm_y);
// Direction to ball!

	int opp=teams[ball_poss-1].face_dir;
	if (opp==d)
		return(-1);

	d=d-opp;

	if (d<0)
		d+=8;

	if ((d==1) || (d==7))
		return(-1);
	
	if ((d==2) || (d==6))
		return(1);
	else
		return(0);
}

/******************************************************************************
*****************************************************************************/

char thinking(match_player *player)
{
	int f=(130-player->tm_flair)/2;
	int t=logic_cnt/f;
	int r=logic_cnt-(t*f);
	return(!r);
}

/******************************************************************************
*****************************************************************************/

char plr_facing(float x,float y,match_player *player)
{
	float xd=player->tm_xdis;
	float yd=player->tm_ydis;
	float d=calc_dist(x,y);
	float a=((x*xd)+(y*yd))/d;
	if (a>FACING_ANGLE)			// 5 degrees!
		return(TRUE);
	else
		return(FALSE);
}

/******************************************************************************
*****************************************************************************/

char plr_facing_goal(float x,float y,match_player *player)
{

// Is the player facing between the goal posts of goal(x,y)?

	float xd=player->tm_xdis;
	float yd=player->tm_ydis;

	if ((x>0 && xd<0) || (x<0 && xd>0))
		return(FALSE);

	float yt;
	if (user_controlled)
		yt=(top_post_y-prat*6)-player->tm_y;
	else
		yt=top_post_y-player->tm_y;

	float d=calc_dist(x,yt);
	float xt=x/d;
	yt=yt/d;

	float yb;
	if (user_controlled)
		yb=(bot_post_y+prat*6)-player->tm_y;
	else
		yb=bot_post_y-player->tm_y;

	d=calc_dist(x,yb);
	float xb=x/d;
	yb=yb/d;

	char dir=0;

	if ((xt*yd)>(yt*xd))
		dir=TRUE;

	if ((xb*yd)>(yb*xd))
	{
		if (dir)
			return(FALSE);
		else
			return(TRUE);
	}
	else
	{
		if (dir)
			return(TRUE);
		else
			return(FALSE);
	}
	return(FALSE);
}

/******************************************************************************
*****************************************************************************/

void run_back(match_player *player)
{
	player->tm_off=-2;
	if (player->tm_player<12)
// Team A...
	{
		init_run_act(player,defense_b-(prat*3),player->tm_y,TRUE);
	}
	else
// Team B...
	{
		init_run_act(player,defense_a+(prat*3),player->tm_y,TRUE);
	}
}

/******************************************************************************
*****************************************************************************/

void keeper_boxes()
{
	if ((teams[KP_A-1].tm_x>(prat*16)) || (teams[KP_A-1].tm_y>(cntspot_y+(19*prat)))
		|| (teams[KP_A-1].tm_y<(cntspot_y-(19*prat))) || (teams[KP_A-1].tm_x<0))

		keeper_a_in_box=FALSE;
	else
		keeper_a_in_box=TRUE;

	if ((teams[KP_B-1].tm_x<pitch_len-(prat*16)) || (teams[KP_B-1].tm_y>(cntspot_y+(19*prat)))
		|| (teams[KP_B-1].tm_y<(cntspot_y-(19*prat))) || (teams[KP_B-1].tm_x>pitch_len))

		keeper_b_in_box=FALSE;
	else
		keeper_b_in_box=TRUE;
}

/******************************************************************************
*****************************************************************************/

void reset_ideas(match_player *player)
{
	player->tm_strike=FALSE;
	player->special=FALSE;
	player->tm_z=0;

	if (player->int_move!=I_OFF)
	{
		if ((player->int_move==I_INTERCEPT) && (player->tm_act==RUN_ACT))
			player->go_cnt=1;			// Stop running!

		if (player->int_move==I_RUN_ON)
		{
			want_pass=0;
			player->int_move=0;
			player->int_cnt=0;
		}

		if (player->int_cnt)
		{
	  		if (player->tm_player==interceptor_a)
				interceptor_a=0;

			if (player->tm_player==interceptor_b)
				interceptor_b=0;

			player->int_move=0;
			player->int_cnt=0;
		}
	}
}

/******************************************************************************
*****************************************************************************/

void reset_all_ideas()
{
	for (int i=0; i<players; i++)
	{
		reset_ideas(&teams[i]);
		teams[i].tm_leave=FALSE;
	}
	keep_dive=FALSE;
}

/******************************************************************************
*****************************************************************************/

void reset_leaves()
{
	for (int i=0; i<players; i++)
	{
		teams[i].tm_leave=FALSE;
	}
}

/******************************************************************************
*****************************************************************************/

void save_in_zone_a(match_player *player,float x,float y,float z,int bp,char forced)
{
	float factor;
	keeper_on_grnd=FALSE;
	keeper_will_save=TRUE;
	int zone=1;
	if (z<SAVE_FEET_HGT)
// Feet level...
	{
		if (bp<=SAVE_AFOOTB_TIME/keeper_spd && !keep_dive)
		{
			keeper_contact=MCC_AFOOTB;

			factor=1./((float)bp/(SAVE_AFOOTB_TIME/keeper_spd));
			if (factor>max_kp_margin && !forced)
			{
// Ball is too fast!
				factor=max_kp_margin;
				keeper_will_save=FALSE;
				player->tm_fstep=MC_AFOOTB_FS*factor*keeper_spd;
			}
			else
				player->tm_fstep=keeper_contact/bp;

			if (player->tm_fstep>=1)
				player->tm_fstep=1;

			save_block=TRUE;
			init_save_act(player,x,y,z,MC_AFOOTB,zone,bp,(int)(SAVE_AFOOTB_TIME/keeper_spd));
		}
		else
			if (bp<=SAVE_AFOOTC_TIME/keeper_spd  || keep_dive)
			{
				keeper_contact=MCC_AFOOTC;

				factor=1./((float)bp/(SAVE_AFOOTC_TIME/keeper_spd));
				if (factor>max_kp_margin && !forced)
				{
// Ball is too fast!
					factor=max_kp_margin;
					keeper_will_save=FALSE;
					player->tm_fstep=MC_AFOOTC_FS*factor*keeper_spd;
				}
				else
					player->tm_fstep=keeper_contact/bp;

				if (player->tm_fstep>=1)
					player->tm_fstep=1;

				save_block=FALSE;
				keeper_on_grnd=TRUE;
				init_save_act(player,x,y,z,MC_AFOOTC,zone,bp,(int)(SAVE_AFOOTC_TIME/keeper_spd));
			}
			else
// Move to best position...
			{
				shot_acknowledged=1;
			}
	}
	else
		if (z<SAVE_CHEST_HGT)
// Chest level...
		{
		 	if (bp<=SAVE_ABODYB_TIME/keeper_spd && !keep_dive)
			{
				keeper_contact=MCC_ABODYB;

				factor=1./((float)bp/(SAVE_ABODYB_TIME/keeper_spd));
				if (factor>max_kp_margin && !forced)
				{
// Ball is too fast!
					factor=max_kp_margin;
					keeper_will_save=FALSE;
					player->tm_fstep=MC_ABODYB_FS*factor*keeper_spd;
				}
				else
					player->tm_fstep=keeper_contact/bp;

				if (player->tm_fstep>=1)
					player->tm_fstep=1;

				save_block=TRUE;
				init_save_act(player,x,y,z,MC_ABODYB,zone,bp,(int)(SAVE_ABODYB_TIME/keeper_spd));
			}
			else
			 	if (bp<=SAVE_ABODYC_TIME/keeper_spd  || keep_dive)
				{
					keeper_contact=MCC_ABODYC;

					factor=1./((float)bp/(SAVE_ABODYC_TIME/keeper_spd));
					if (factor>max_kp_margin && !forced)
					{
// Ball is too fast!
						factor=max_kp_margin;
						keeper_will_save=FALSE;
						player->tm_fstep=MC_ABODYC_FS*factor*keeper_spd;
					}
					else
						player->tm_fstep=keeper_contact/bp;

					if (player->tm_fstep>=1)
						player->tm_fstep=1;

					save_block=FALSE;
					init_save_act(player,x,y,z,MC_ABODYC,zone,bp,(int)(SAVE_ABODYC_TIME/keeper_spd));
				}
				else
// Move to best position...
				{
					shot_acknowledged=1;
				}
		}
		else
			if (z<SAVE_HEAD_HGT)
// Head level...
			{
			 	if (bp<=SAVE_AHEADB_TIME/keeper_spd && !keep_dive)
				{
					keeper_contact=MCC_AHEADB;

					factor=1./((float)bp/(SAVE_AHEADB_TIME/keeper_spd));
					if (factor>max_kp_margin && !forced)
					{
// Ball is too fast!
						factor=max_kp_margin;
						keeper_will_save=FALSE;
						player->tm_fstep=MC_AHEADB_FS*factor*keeper_spd;
					}
					else
						player->tm_fstep=keeper_contact/bp;

					if (player->tm_fstep>=1)
						player->tm_fstep=1;

					save_block=TRUE;
					init_save_act(player,x,y,z,MC_AHEADB,zone,bp,(int)(SAVE_AHEADB_TIME/keeper_spd));
				}
				else
				 	if (bp<=SAVE_AHEADC_TIME/keeper_spd  || keep_dive)
					{
						keeper_contact=MCC_AHEADC;

						factor=1./((float)bp/(SAVE_AHEADC_TIME/keeper_spd));
						if (factor>max_kp_margin && !forced)
						{
// Ball is too fast!
							factor=max_kp_margin;
							keeper_will_save=FALSE;
							player->tm_fstep=MC_AHEADC_FS*factor*keeper_spd;
						}
						else
							player->tm_fstep=keeper_contact/bp;

						if (player->tm_fstep>=1)
							player->tm_fstep=1;

						save_block=FALSE;
						init_save_act(player,x,y,z,MC_AHEADC,zone,bp,(int)(SAVE_AHEADC_TIME/keeper_spd));
					}
					else
// Move to best position...
					{
						shot_acknowledged=1;
					}
			}
			else
				if (z<SAVE_JUMP_HGT)
// Above head level...
				{
				 	if (bp<=SAVE_AJUMPB_TIME/keeper_spd && !keep_dive)
					{
						keeper_contact=MCC_AJUMPB;

						factor=1./((float)bp/(SAVE_AJUMPB_TIME/keeper_spd));
						if (factor>max_kp_margin && !forced)
						{
// Ball is too fast!
							factor=max_kp_margin;
							keeper_will_save=FALSE;
							player->tm_fstep=MC_AJUMPB_FS*factor*keeper_spd;
						}
						else
							player->tm_fstep=keeper_contact/bp;

						if (player->tm_fstep>=1)
							player->tm_fstep=1;

						save_block=TRUE;
						init_save_act(player,x,y,z,MC_AJUMPB,zone,bp,(int)(SAVE_AJUMPB_TIME/keeper_spd));
					}
					else
					 	if (bp<=SAVE_AJUMPC_TIME/keeper_spd  || keep_dive)
						{
							keeper_contact=MCC_AJUMPC;

							factor=1./((float)bp/(SAVE_AJUMPC_TIME/keeper_spd));
							if (factor>max_kp_margin && !forced)
							{
// Ball is too fast!
								factor=max_kp_margin;
								keeper_will_save=FALSE;
								player->tm_fstep=MC_AJUMPC_FS*factor*keeper_spd;
							}
							else
								player->tm_fstep=keeper_contact/bp;

							if (player->tm_fstep>=1)
								player->tm_fstep=1;

							save_block=FALSE;
							init_save_act(player,x,y,z,MC_AJUMPC,zone,bp,(int)(SAVE_AJUMPC_TIME/keeper_spd));
						}
						else
// Move to best position...
						{
							shot_acknowledged=1;
						}
				}
}

/******************************************************************************
*****************************************************************************/

void save_in_zone_b(match_player *player,float x,float y,float z,int bp,char forced)
{
	float factor;
	keeper_on_grnd=FALSE;
	keeper_will_save=TRUE;
	int zone=2;
	if (z<SAVE_FEET_HGT)
// Feet level...
	{
		if (bp<=SAVE_BFOOTB_TIME/keeper_spd && !keep_dive)
		{
			keeper_contact=MCC_BFOOTB;

			factor=1./((float)bp/(SAVE_BFOOTB_TIME/keeper_spd));
			if (factor>max_kp_margin && !forced)
			{
// Ball is too fast!
				factor=max_kp_margin;
				keeper_will_save=FALSE;
				player->tm_fstep=MC_BFOOTB_FS*factor*keeper_spd;
			}
			else
				player->tm_fstep=keeper_contact/bp;

			if (player->tm_fstep>=1)
				player->tm_fstep=1;

			save_block=TRUE;
			init_save_act(player,x,y,z,MC_BFOOTBL,zone,bp,(int)(SAVE_BFOOTB_TIME/keeper_spd));
		}
		else
			if (bp<=SAVE_BFOOTC_TIME/keeper_spd  || keep_dive)
			{
				keeper_contact=MCC_BFOOTC;

				factor=1./((float)bp/(SAVE_BFOOTC_TIME/keeper_spd));
				if (factor>max_kp_margin && !forced)
				{
// Ball is too fast!
					factor=max_kp_margin;
 					keeper_will_save=FALSE;
 					player->tm_fstep=MC_BFOOTC_FS*factor*keeper_spd;
 				}
 				else
 					player->tm_fstep=keeper_contact/bp;

				if (player->tm_fstep>=1)
					player->tm_fstep=1;

				save_block=FALSE;
				keeper_on_grnd=TRUE;
				init_save_act(player,x,y,z,MC_BFOOTCL,zone,bp,(int)(SAVE_BFOOTC_TIME/keeper_spd));
			}
			else
// Move to best position...
			{
				shot_acknowledged=1;
			}
	}
	else
		if (z<SAVE_CHEST_HGT)
// Chest level...
		{
		 	if (bp<=SAVE_BBODYB_TIME/keeper_spd && !keep_dive)
			{
				keeper_contact=MCC_BBODYB;
				factor=1./((float)bp/(SAVE_BBODYB_TIME/keeper_spd));
				if (factor>max_kp_margin && !forced)
				{
// Ball is too fast!
					factor=max_kp_margin;
					keeper_will_save=FALSE;
					player->tm_fstep=MC_BBODYB_FS*factor*keeper_spd;
				}
				else
 					player->tm_fstep=keeper_contact/bp;

				if (player->tm_fstep>=1)
					player->tm_fstep=1;

				save_block=TRUE;
				keeper_on_grnd=TRUE;
				init_save_act(player,x,y,z,MC_BBODYBL,zone,bp,(int)(SAVE_BBODYB_TIME/keeper_spd));
			}
			else
			 	if (bp<=SAVE_BBODYC_TIME/keeper_spd || keep_dive)
				{
					keeper_contact=MCC_BBODYC;
					factor=1./((float)bp/(SAVE_BBODYC_TIME/keeper_spd));
					if (factor>max_kp_margin && !forced)
					{
// Ball is too fast!
						factor=max_kp_margin;
						keeper_will_save=FALSE;
						player->tm_fstep=MC_BBODYC_FS*factor*keeper_spd;
					}
					else
	 					player->tm_fstep=keeper_contact/bp;

					if (player->tm_fstep>=1)
						player->tm_fstep=1;

					save_block=FALSE;
					keeper_on_grnd=TRUE;
					init_save_act(player,x,y,z,MC_BBODYCL,zone,bp,(int)(SAVE_BBODYC_TIME/keeper_spd));
				}
				else
// Move to best position...
				{
					shot_acknowledged=1;
				}
		}
		else
			if (z<SAVE_HEAD_HGT)
// Head level...
			{
			 	if (bp<=SAVE_BHEADB_TIME/keeper_spd && !keep_dive)
				{
					keeper_contact=MCC_BHEADB;
					factor=1./((float)bp/(SAVE_BHEADB_TIME/keeper_spd));
					if (factor>max_kp_margin && !forced)
					{
// Ball is too fast!
						factor=max_kp_margin;
						keeper_will_save=FALSE;
						player->tm_fstep=MC_BHEADB_FS*factor*keeper_spd;
					}
					else
	 					player->tm_fstep=keeper_contact/bp;

					if (player->tm_fstep>=1)
						player->tm_fstep=1;

					save_block=TRUE;
					init_save_act(player,x,y,z,MC_BHEADBL,zone,bp,(int)(SAVE_BHEADB_TIME/keeper_spd));
				}
				else
				 	if (bp<=SAVE_BHEADC_TIME/keeper_spd || keep_dive)
					{
						keeper_contact=MCC_BHEADC;
						factor=1./((float)bp/(SAVE_BHEADC_TIME/keeper_spd));
						if (factor>max_kp_margin && !forced)
						{
// Ball is too fast!
							factor=max_kp_margin;
							keeper_will_save=FALSE;
							player->tm_fstep=MC_BHEADC_FS*factor*keeper_spd;
						}
						else
		 					player->tm_fstep=keeper_contact/bp;

						if (player->tm_fstep>=1)
							player->tm_fstep=1;

						save_block=FALSE;
						init_save_act(player,x,y,z,MC_BHEADCL,zone,bp,(int)(SAVE_BHEADC_TIME/keeper_spd));
					}
					else
// Move to best position...
					{
						shot_acknowledged=1;
					}
			}
			else
				if (z<SAVE_JUMP_HGT)
// Above head level...
				{
				 	if (bp<=SAVE_BJUMPB_TIME/keeper_spd && !keep_dive)
					{
						keeper_contact=MCC_BJUMPB;
						factor=1./((float)bp/(SAVE_BJUMPB_TIME/keeper_spd));
						if (factor>max_kp_margin && !forced)
						{
// Ball is too fast!
							factor=max_kp_margin;
							keeper_will_save=FALSE;
							player->tm_fstep=MC_BJUMPB_FS*factor*keeper_spd;
						}
						else
		 					player->tm_fstep=keeper_contact/bp;

						if (player->tm_fstep>=1)
							player->tm_fstep=1;

						save_block=TRUE;
						init_save_act(player,x,y,z,MC_BJUMPBL,zone,bp,(int)(SAVE_BJUMPB_TIME/keeper_spd));
					}
					else
// Move to best position...
					{
						shot_acknowledged=1;
					}
				}
}

/******************************************************************************
*****************************************************************************/

void save_in_zone_c(match_player *player,float x,float y,float z,int bp,char forced)
{
	float factor;
	keeper_will_save=TRUE;
	keeper_on_grnd=FALSE;
	int zone=3;
	if (z<SAVE_FEET_HGT)
// Feet level...
	{
		if (bp<=SAVE_CFOOTB_TIME/keeper_spd && !keep_dive)
		{
			keeper_contact=MCC_CFOOTB;
			factor=1./((float)bp/(SAVE_CFOOTB_TIME/keeper_spd));
			if (factor>max_kp_margin && !forced)
			{
// Ball is too fast!
				factor=max_kp_margin;
				keeper_will_save=FALSE;
				player->tm_fstep=MC_CFOOTB_FS*factor*keeper_spd;
			}
			else
				player->tm_fstep=keeper_contact/bp;

			if (player->tm_fstep>=1)
				player->tm_fstep=1;

			save_block=TRUE;
			keeper_on_grnd=TRUE;
			init_save_act(player,x,y,z,MC_CFOOTBL,zone,bp,(int)(SAVE_CFOOTB_TIME/keeper_spd));
		}
		else
			if (bp<=SAVE_CFOOTC_TIME/keeper_spd || keep_dive)
			{
				keeper_contact=MCC_CFOOTC;
				factor=1./((float)bp/(SAVE_CFOOTC_TIME/keeper_spd));
				if (factor>max_kp_margin && !forced)
				{
// Ball is too fast!
					factor=max_kp_margin;
					keeper_will_save=FALSE;
					player->tm_fstep=MC_CFOOTC_FS*factor*keeper_spd;
				}
				else
					player->tm_fstep=keeper_contact/bp;

				if (player->tm_fstep>=1)
					player->tm_fstep=1;

				save_block=FALSE;
				keeper_on_grnd=TRUE;
				init_save_act(player,x,y,z,MC_CFOOTCL,zone,bp,(int)(SAVE_CFOOTC_TIME/keeper_spd));
			}
			else
// Move to best position...
			{
				shot_acknowledged=1;
			}
	}
	else
		if (z<SAVE_CHEST_HGT)
// Chest level...
		{
		 	if (bp<=SAVE_CBODYB_TIME/keeper_spd && !keep_dive)
			{
				keeper_contact=MCC_CBODYB;
				factor=1./((float)bp/(SAVE_CBODYB_TIME/keeper_spd));
				if (factor>max_kp_margin && !forced)
				{
// Ball is too fast!
					factor=max_kp_margin;
					keeper_will_save=FALSE;
					player->tm_fstep=MC_CBODYB_FS*factor*keeper_spd;
				}
				else
					player->tm_fstep=keeper_contact/bp;

				if (player->tm_fstep>=1)
					player->tm_fstep=1;

				save_block=TRUE;
				keeper_on_grnd=TRUE;
				init_save_act(player,x,y,z,MC_CBODYBL,zone,bp,(int)(SAVE_CBODYB_TIME/keeper_spd));
			}
			else
			 	if (bp<=SAVE_CBODYC_TIME/keeper_spd || keep_dive)
				{
					keeper_contact=MCC_CBODYC;
					factor=1./((float)bp/(SAVE_CBODYC_TIME/keeper_spd));
					if (factor>max_kp_margin && !forced)
					{
// Ball is too fast!
						factor=max_kp_margin;
						keeper_will_save=FALSE;
						player->tm_fstep=MC_CBODYC_FS*factor*keeper_spd;
					}
					else
						player->tm_fstep=keeper_contact/bp;

					if (player->tm_fstep>=1)
						player->tm_fstep=1;

					save_block=FALSE;
					keeper_on_grnd=TRUE;
					init_save_act(player,x,y,z,MC_CBODYCL,zone,bp,(int)(SAVE_CBODYC_TIME/keeper_spd));
				}
				else
// Move to best position...
				{
					shot_acknowledged=1;
				}
		}
		else
			if (z<SAVE_HEAD_HGT)
// Head level...
			{
			 	if (bp<=SAVE_CHEADB_TIME/keeper_spd && !keep_dive)
				{
					keeper_contact=MCC_CHEADB;
					factor=1./((float)bp/(SAVE_CHEADB_TIME/keeper_spd));
					if (factor>max_kp_margin && !forced)
					{
// Ball is too fast!
						factor=max_kp_margin;
						keeper_will_save=FALSE;
						player->tm_fstep=MC_CHEADB_FS*factor*keeper_spd;
					}
					else
						player->tm_fstep=keeper_contact/bp;

					if (player->tm_fstep>=1)
						player->tm_fstep=1;

					save_block=TRUE;
					init_save_act(player,x,y,z,MC_CHEADBL,zone,bp,(int)(SAVE_CHEADB_TIME/keeper_spd));
				}
				else
// Move to best position...
				{
					shot_acknowledged=1;
				}
			}
			else
				if (z<SAVE_JUMP_HGT)
// Above head level...
				{
				 	if (bp<=SAVE_CJUMPB_TIME/keeper_spd || keep_dive)
					{
						keeper_contact=MCC_CJUMPB;
						factor=1./((float)bp/(SAVE_CJUMPB_TIME/keeper_spd));
						if (factor>max_kp_margin && !forced)
						{
// Ball is too fast!
							factor=max_kp_margin;
							keeper_will_save=FALSE;
							player->tm_fstep=MC_CJUMPB_FS*factor*keeper_spd;
						}
						else
							player->tm_fstep=keeper_contact/bp;

						if (player->tm_fstep>=1)
							player->tm_fstep=1;

						save_block=TRUE;
						init_save_act(player,x,y,z,MC_CJUMPBL,zone,bp,(int)(SAVE_CJUMPB_TIME/keeper_spd));
					}
					else
// Move to best position...
					{
						shot_acknowledged=1;
					}
				}
}

/******************************************************************************
*****************************************************************************/

// Send keeper to point between centre of goal and ball!
// Point ratio between goal and ball varies with distance to ball.
// i.e. If opponent is close then point will be further from goal.

void close_angle(match_player *player,float d,float &x,float &y)
{
	float gx,gd,cd;

	cd=CLOSE_ANG_DIST+(prat*player->tm_vis)/8;

	if (player->tm_player<12)
// Keeper A...
		gx=0;
	else
// Keeper B...
		gx=pitch_len;

	gd=prat+(d*((cd-d)/cd));	//	How far target point is along line.
	x=gx+((ballx-gx)*gd/d);
	y=cntspot_y+((bally-cntspot_y)*gd/d);
}

/******************************************************************************
*****************************************************************************/

char target_towards_ball(float tx,float ty,float px,float py)
{
// Get distance of target to present ball pos.
	float d=calc_dist(tx-ballx,ty-bally);

	if (d<=calc_dist(px-ballx,py-bally))
		return(TRUE);		// Player is further from ball than target!

	return(FALSE);
}

/******************************************************************************
*****************************************************************************/

void init_user_save(match_player *player)
{
	int t;
	float dist=prat*1.4;
	keeper_will_save=FALSE;
	save_block=TRUE;
	reset_ideas(player);

	if (save_direction)
	{
// Direction selected...
		if (save_direction>0)
		{
// Raw Left...
			if (match_mode==PEN_KICK_A)
			{
// Dive Right and Up-field...
				init_anim(player,MC_CBODYBR);
				t=(SAVE_BBODYB_TIME/keeper_spd);
				dist=-dist;
			}
			else
			{
// Dive Right and Down-field...
				init_anim(player,MC_CBODYBR);
				t=(SAVE_BBODYB_TIME/keeper_spd);
			}
		}
		else
		{
// Raw Right...
			if (match_mode==PEN_KICK_A)
			{
// Dive Left and Down-field...
				init_anim(player,MC_CBODYBL);
				t=(SAVE_BBODYB_TIME/keeper_spd);
			}
			else
			{
// Dive Left and Up-field...
				init_anim(player,MC_CBODYBL);
				t=(SAVE_BBODYB_TIME/keeper_spd);
				dist=-dist;
			}
		}
	}
	else
	{
		init_anim(player,MC_ABODYB);
		t=(SAVE_ABODYB_TIME/keeper_spd);
		dist=0;
	}

	player->go_tx=player->tm_x;
	player->go_ty=player->tm_y+dist;
	player->go_txdis=0;
	player->go_tydis=dist/t;
	player->go_cnt=1/player->tm_fstep;
	player->dir_mode=5;
	player->tm_zdis=0;
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
	player->tm_act=SAVE_ACT;
	newdx=player->tm_xdis;
	newdy=player->tm_ydis;
}

/******************************************************************************
*****************************************************************************/

#define DIVE_POINT 3
#define DIVE_FEET_DIST (prat*4)

// Someone has shot...
// Send keeper to intersection with ball path.
// If he cannot meet ball then best try!

void go_to_save_path(match_player *player,char forced=FALSE)
{
	keeper_spd=((float)(player->tm_flair+player->tm_rate)/128)*(forced ? 2:1);

// Calculate next frame distance to the ball...
	float d=calc_dist(player->tm_x-(ballx+ballxdis),player->tm_y-(bally+ballydis));

	if (!forced)
	{
		if (d<player->tm_dist)
// Ball is getting closer...
		{
			if (player->tm_player==KP_A)
			{
// Keeper A
				if (ballx<cntspot_x)
					shot_acknowledged=1+((128-player->tm_vis)/8);
			}
			else
			{
// Keeper B
				if (ballx>cntspot_x)
					shot_acknowledged=1+((128-player->tm_vis)/8);
			}
		}
	}

	if (shot_acknowledged || forced)
	{
		int flag;
		int vision=((128-player->tm_vis)/2);

// Is shot on Target?
//	if (ABS(ballxdis)>0)
		{
			float kp_xoff;
			float x,y,z,ox,oy,oz;
			float xc,yc,zc;
			float xf,yf,zf;
			float xns,yns,zns;
			int bp,ob;
			float min_d=2000;
			float d,t,fd;
			float px=player->tm_x;
			float py=player->tm_y;
			float rate=actual_spd(player);	// Dive is 2 x rate.
			flag=FALSE;
			char in_area=FALSE;

			bp=1;
			ob=1;
			ox=ballx;
			oy=bally;
			oz=ballz;
			xc=ballx;
			yc=bally;
			zc=ballz;
			
			if (!keep_dive)
			{
				float see_swerve;

				see_swerve=(64.+(player->tm_vis/2))/128;

				for (int i=1; i<50; i++)
				{
// Coords without swerve...
					xns=ns_ball_pred_tab[i][0];
					yns=ns_ball_pred_tab[i][1];
					zns=ns_ball_pred_tab[i][2];

// Coords with swerve...
					x=ball_pred_tab[i][0];
					y=ball_pred_tab[i][1];
					z=ball_pred_tab[i][2];

// Coords seeing some swerve...
					x=xns+((x-xns)*see_swerve);
					y=yns+((y-yns)*see_swerve);
					z=zns+((z-zns)*see_swerve);

					in_area=FALSE;

					if (y>top_post_y && y<bot_post_y)
						kp_xoff=4;
					else
						kp_xoff=0;
// Try and stop keeper saving and carrying ball behind line...

					if (x>cntspot_x)
					{
// Team B goal-line...
						if (x>=pitch_len-kp_xoff)
						{
							i=60;
							if (ABS(y-cntspot_y)>((prat*4.5)+(128-player->tm_flair)/4))
// Too wide!
									flag=FALSE;			// Don't bother saving!
						}
					}
		
					if (x<=cntspot_x)
					{
// Team A goal-line...
						if (x<0+kp_xoff)
						{
							i=60;
							if (ABS(y-cntspot_y)>((prat*4.5)+(128-player->tm_flair)/4))
// Too wide!
								flag=FALSE;			// Don't bother saving!
						}
					}

					if (i!=60)
					{
						if (player->tm_player<12)
						{
							if (x<prat*18 && y>cntspot_y-(21*prat)
								&& (y<cntspot_y+(21*prat)))
								in_area=TRUE;
						}
						else
						{
							if (x>pitch_len-(prat*18) && y>cntspot_y-(21*prat)
								&& (y<cntspot_y+(21*prat)))
								in_area=TRUE;
						}
	
						if (in_area)
						{
							d=calc_dist(x-px,y-py);
//				  			if (d<min_d && z<SAVE_JUMP_HGT+prat && target_towards_ball(x,y,px,py))
				  			if (d<min_d && z<SAVE_JUMP_HGT+prat/2)
// Store closest ball!
				  			{
								ox=xc;
								oy=yc;
								oz=zc;
								ob=bp;
				  				min_d=d;
				  				bp=i;
								xc=x;
								yc=y;
								zc=z;
								flag=TRUE;
							}
							else
// Getting further away...
							{
								if (d-min_d>prat)
// Definately not getting any closer...
								{
									i=60;			// Quit.
								}
							}
						}
					}
				}
			}

			else
			{
				flag=TRUE;
				xc=ball_pred_tab[DIVE_POINT][0];
				yc=ball_pred_tab[DIVE_POINT][1];
				zc=ball_pred_tab[DIVE_POINT][2];
				d=calc_dist(xc-px,yc-py);
				x=(xc-px)/d;
				y=(yc-py)/d;
				if (keep_dive)
				{
					xc+=x*prat;
					yc+=y*prat;
				}
				ox=xc;
				oy=yc;
				oz=zc;
				ob=DIVE_POINT;
				bp=DIVE_POINT;
			}

			if (flag)
// Shot is in area...
			{
				x=ox+((xc-ox)/2);		// Between closest and one before...
				y=oy+((yc-oy)/2);
				z=oz+((zc-oz)/2);

				if (forced)			// Forced to dive at attackers feet...
				{
					fd=calc_dist(x-px,y-py);
					xf=(x-px)/fd;
					yf=(y-py)/fd;
					x+=xf*3;
					y+=yf*3;		// Dive beyond point of contact...
				}

//				bp=ob;

// Nearest ball coord.

				d=calc_dist(x-px,y-py);		// Distance to keeper...
	  
				char st=player->go_step;
				player->go_step=TRUE;
				t=d/actual_spd(player);	// Time to step there...
				player->go_step=st;

				max_kp_margin=1.5+(1.8*time_factor/90);

/*************************************************************/
/*************************************************************/
#ifdef EURO96
				if (penalty_shot && user_controlled)
				{
					if (users_dir[user_controlled-1].f&8)
						save_direction=-1;
					if (users_dir[user_controlled-1].f&4)
						save_direction=1;

					char good_choice=FALSE;
// User decides which way to dive...
					if (t<1 && !save_direction)
					{
// Straight on...(good choice!)
						good_choice=TRUE;
					}
					else
					{
						if (save_direction)
						{
// User has chosen a direction...
							if (save_direction<0)
							{
// Left selected...
								if ((x<cntspot_x && player->tm_y>(y+(SAVE_ZONE_A/2)))
									|| (x>cntspot_x && player->tm_y<(y-(SAVE_ZONE_A/2))))
								{
									good_choice=TRUE;
								}
							}
							else
							{
// Right selected...
								if ((x<cntspot_x && player->tm_y<(y-(SAVE_ZONE_A/2)))
									|| (x>cntspot_x && player->tm_y>(y+(SAVE_ZONE_A/2))))
								{
									good_choice=TRUE;
								}
							}
						}
						else
	   				{
							if (d<=SAVE_ZONE_A)
								good_choice=TRUE;
						}
					}

					if (good_choice)
					{
// Let computer save...
						if (t<1)
						{
							save_in_zone_a(player,x,y,z,bp,forced);
						}
						else
						{
							if (d<=SAVE_ZONE_A)
								save_in_zone_a(player,x,y,z,bp,forced);
							else
								if (d<=SAVE_ZONE_B)
									save_in_zone_b(player,x,y,z,bp,forced);
								else
									if (d<=(SAVE_ZONE_C+prat*2))
										save_in_zone_c(player,x,y,z,bp,forced);
									else
										keep_dive=FALSE;
						}
					}
					else
					{
// Save in the direction of user's choice...
						init_user_save(player);
					}
				}
				else
#endif
/*************************************************************/
/*************************************************************/
				{
					if (t<1)
/************************************/
// Already in preferred position... //
/************************************/

					{
						save_in_zone_a(player,x,y,z,bp,forced);
					}
					else
					{

						if (t<bp-SAVE_AHEADC_TIME)
/************************************************************/
// Can get body behind it and still have time to animate... //
/************************************************************/
						{
							reset_ideas(player);
							player->go_step=TRUE;
							if (player->tm_player<12)
								init_run_act(player,x-prat,y,TRUE);			//ball meet point
							else
								init_run_act(player,x+prat,y,TRUE);			//ball meet point
						}
						else
						{
							if (d<=SAVE_ZONE_A)
								save_in_zone_a(player,x,y,z,bp,forced);
							else
								if (d<=SAVE_ZONE_B)
									save_in_zone_b(player,x,y,z,bp,forced);
								else
									if (d<=(SAVE_ZONE_C+prat*2))
										save_in_zone_c(player,x,y,z,bp,forced);
									else
										keep_dive=FALSE;
						}
					}
				}
			}
		}
	}
}

/******************************************************************************
*****************************************************************************/

void fake_ball_poss(int p,float x,float y,float z)
{
	save_ball_poss=ball_poss;
	save_ballx=ballx;
	save_bally=bally;
	save_ballz=ballz;
	ballx=x;
	bally=y;
	ballz=z;
	ball_poss=p;
}

/******************************************************************************
*****************************************************************************/

void restore_ball_poss()
{
	ball_poss=save_ball_poss;
	ballx=save_ballx;
	bally=save_bally;
	ballz=save_ballz;
}

/******************************************************************************
*****************************************************************************/

char kick_straight()
{
 	if (pass_type==-1 || (pass_type>=4 && pass_type<=6))
		return(TRUE);
	else
		return(FALSE);
}

/******************************************************************************
*****************************************************************************/

char first_time_strike(int p,float x,float y,float z,float px,float py)
{
	float d;
	float obx=ballx;
	float oby=bally;

	char sr=teams[p-1].tm_srng;
	if (p<12)
		d=calc_dist(pitch_len-x,cntspot_y-y);
	else
		d=calc_dist(x,cntspot_y-y);

	if (d<(MIN_SHOOT_DIST+((float)teams[p-1].tm_pow*3)))
		teams[p-1].tm_srng=TRUE;
	else
		teams[p-1].tm_srng=FALSE;

	float xpd=teams[p-1].tm_xdis;
	float ypd=teams[p-1].tm_ydis;
	teams[p-1].tm_xdis=x_face;
	teams[p-1].tm_ydis=y_face;
	ballx=teams[p-1].tm_x;
	bally=teams[p-1].tm_y;
	
	pass_type=FALSE;
	receiver=FALSE;
	char allow=0;
	float gx,gy;

	if (p<12)
		gx=pitch_len;
	else
		gx=0;

	gy=cntspot_y;
	gx-=x;
	gy-=y;
	d=calc_dist(gx,gy);

	fake_ball_poss(p,x,y,z);

	if (auto_select)
	{
		if (ball_int_speed>6)
		{
// Ball is moving so he can trap...
			allow=128;		// Can control it...
		}

		if (shoot_decide(&teams[p-1]))
		{
			pass_type=0;
			allow+=3;					// Kick or volley!
			if (d<MIN_HEADER_RNG+(prat*teams[p-1].tm_pow/8))
// In head range also!
			{
				allow+=8+16;			// Standing or Jumping header!
				if (kick_straight())
// Target is forward!
					allow+=4;			// Diving header!
			}
		}
		else
		{
			teams[p-1].tm_xdis=-teams[p-1].tm_xdis;
			teams[p-1].tm_ydis=-teams[p-1].tm_ydis;		// Reverse face!

			if (shoot_decide(&teams[p-1]))
			{
				pass_type=0;
				allow+=32;				// Overhead!
			}
			else
			{
				if (punt_decide(&teams[p-1]))	// Overhead punt???
				{
					pass_type=0;
					allow+=32;				// Overhead!
				}
				else
				{
					teams[p-1].tm_xdis=-teams[p-1].tm_xdis;
					teams[p-1].tm_ydis=-teams[p-1].tm_ydis;		// Reverse face!
					if (punt_decide(&teams[p-1]))
					{
						pass_type=0;
						allow+=1+2+4+8+16;						// Kick or volley or any header!
					}
					else
					{
						receiver=pass_decide(&teams[p-1],FALSE);
						if (receiver)
						{
							if (pass_type==-1)
// Chip pass!
								allow+=64+8+16;		// Chip, S-head, J-head!
							else
							{
								if (kick_straight())
									allow+=8+16;		// S-head, J-head!
							}
						}
					}
				}
			}
		}
	}
	else
		allow=0;

	restore_ball_poss();

	teams[p-1].tm_srng=sr;			// Restore range flag!
	teams[p-1].tm_xdis=xpd;
	teams[p-1].tm_ydis=ypd;
	ballx=obx;
	bally=oby;

	return(allow);
}

/******************************************************************************
*****************************************************************************/

char user_pass_check(int p,float x,float y,float z,float px,float py)
{
	float d;
	float obx=ballx;
	float oby=bally;

	char sr=teams[p-1].tm_srng;
	if (p<12)
		d=calc_dist(pitch_len-x,cntspot_y-y);
	else
		d=calc_dist(x,cntspot_y-y);

	if (d<(MIN_SHOOT_DIST+((float)teams[p-1].tm_pow*3)))
		teams[p-1].tm_srng=TRUE;
	else
		teams[p-1].tm_srng=FALSE;

	float xpd=teams[p-1].tm_xdis;
	float ypd=teams[p-1].tm_ydis;
	teams[p-1].tm_xdis=x_face;
	teams[p-1].tm_ydis=y_face;
	ballx=teams[p-1].tm_x;
	bally=teams[p-1].tm_y;
	
	pass_type=FALSE;
	receiver=FALSE;
	char allow=0;
	float gx,gy;

	if (p<12)
		gx=pitch_len;
	else
		gx=0;

	gy=cntspot_y;
	gx-=x;
	gy-=y;
	d=calc_dist(gx,gy);

	fake_ball_poss(p,x,y,z);

	receiver=pass_decide(&teams[p-1],FALSE);
	if (receiver)
	{
		if (pass_type==-1)
// Chip pass!
			allow+=64+8+16;		// Chip, S-head, J-head!
		else
		{
			if (kick_straight())
				allow+=8+16;		// S-head, J-head!
		}
	}
	else
		allow=0;

	restore_ball_poss();

	teams[p-1].tm_srng=sr;			// Restore range flag!
	teams[p-1].tm_xdis=xpd;
	teams[p-1].tm_ydis=ypd;
	ballx=obx;
	bally=oby;

	return(allow);
}


/******************************************************************************
*****************************************************************************/

void decide_strike(match_player *p,short t,char c,char s)
{
	float x=ball_pred_tab[t][0];
	float y=ball_pred_tab[t][1];
	float z=ball_pred_tab[t][1];

	p->int_cnt=t;						// Flair factor.
	init_run_act(p,x,y,TRUE);
	p->tm_strike=TRUE;
}

/******************************************************************************
*****************************************************************************/

void strike_and_control(match_player *player,intercept_data *s,short action)
{
	player->tm_stime=s->atime+1;

//	player->int_cnt=player->tm_stime+alarm+free+1;	// Make sure he seems busy for the duration!

	float x=s->x;
	float y=s->y;

	switch(action)
	{
		case(7):
		case(9):
		case(10):
			if (player->tm_fpass_type=s->ptype)
// Equate pass type and test!
				player->tm_fpass_to=s->pplr;
			break;
	}

	short gt=get_there_time(player->tm_player,x,y);

	player->tm_ftime=s->free;
	player->tm_strike=action;
	init_run_act(player,x,y,FALSE);

	player->int_cnt=player->go_cnt+player->tm_ftime+player->tm_stime;
	if (must_face)
		player->int_cnt+=player->mface_time;

	if (user_controlled)
	{
		player->special=-TRUE;		// Special action decided!
/*
		if (player->go_cnt>1)
		{
			player->go_cnt=1;
			player->int_cnt=1;
		}
*/
	}
}

/******************************************************************************
*****************************************************************************/

void cancel_int(int p)
{
// should never get here!
	init_stand_act(&teams[p-1]);
}

/******************************************************************************
*****************************************************************************/

void intercept(int p)
{
	action="Intercept";

	reset_ideas(&teams[p-1]);

	if (p<12)
		interceptor_a=p;
	else
		interceptor_b=p;

// His intention is to intercept ball.
// Therefore his flair determines no. of turns before rethink!

	int ff=33-(teams[p-1].tm_flair/4);
	teams[p-1].int_move=I_INTERCEPT;		// Intercept ball!
	teams[p-1].int_cnt=ff;					// Intercept ball!

	float x,y;

	if (special_move)
	 	teams[p-1].special=TRUE;
	else
	 	teams[p-1].special=FALSE;

	{
		for (short i=10; i>=0; i--)
		{
			if (strike[i].t)
			{
				if (i>0)
				{
					if (user_controlled)
					{
// uf1 = strike, uf2 = control!
						if (uf1 && i>4)
						{
							strike_and_control(&teams[p-1],&strike[i],i);
							break;
						}
						else
						{
							if (uf2 && i<=4 && i)
							{
								strike_and_control(&teams[p-1],&strike[i],i);
								break;
							}
						}
					}
					else
					{
						strike_and_control(&teams[p-1],&strike[i],i);
						break;
					}
				}
				else
				{
// Run onto ball...
					if (strike[0].stop)
						init_stop_act(&teams[p-1],strike[0].x,strike[0].y);
					else
						init_run_act(&teams[p-1],strike[0].x,strike[0].y,FALSE);

					teams[p-1].go_cnt++;
					break;
				}
			}
		}
	}
}

/******************************************************************************
*****************************************************************************/

float fstep_factor(short c)
{
// Returns a range of 0.6(c=0) to 1.6(c=128)
	float f=0.6+((float)c/128);
	return(f);
}

/******************************************************************************
*****************************************************************************/

#ifdef EURO96
// Euro 96 has first time pass implemented...

char can_i_intercept(int p_num,float x,float y,float z,float px,float py,short i)
{
	if (z>=teams[p_num-1].tm_jump)
		return(FALSE);

	float cx,cy,cz,cx2,cy2,ang;
	float rate=full_spd(&teams[p_num-1]);
	float d=calc_dist(x-px,y-py);
	char can_strike;
	char do_it=FALSE;
	char stand;
	char strike_option=FALSE;
	char trap_option=FALSE;
	char pass_option=FALSE;

	short ff=1+teams[p_num-1].tm_flair/16;		// Reaction times.

	short gt=get_there_time(p_num,x,y);
	short t;

	if (gt<=i)
	{
// He can get to ball in time...

		if (ball_poss)
		{
// Opponent has ball... (No control or strike!)
/***** RUN ONTO BALL *****/
			t=i-gt;
			if (t>0 && t<strike[0].free && (teams[p_num-1].control || t<ff))
			{
	  			strike[0].t=i;
	  			strike[0].free=t;
				strike[0].x=x;
				strike[0].y=y;
				strike[0].stop=stop_and_face;
				do_it=TRUE;
			}
		}
		else
		{
			if (user_controlled)
			{
				can_strike=128+32+16+8+4+2+1;
				pass_type=0;
				strike_option=uf1&(!uf2);
				trap_option=uf2&(!uf1);
				pass_option=uf1&uf2;
				if (pass_option)
					can_strike=user_pass_check(p_num,x,y,z,px,py);
			}
			else
				can_strike=first_time_strike(p_num,x,y,z,px,py);

/***** RUN ONTO BALL *****/

			if (z<PLAYER_HEIGHT/3)
			{
// Feet level...
				ang=angle_to_xy(x-px,y-py,teams[p_num-1].tm_xdis,teams[p_num-1].tm_ydis);
				if (ang>0 || user_controlled)
				{
// Target is in front of player...
					t=i-gt;
					if (t>=0 && t<strike[0].free && (teams[p_num-1].control || t<ff))
					{
		  				strike[0].t=i;
		  				strike[0].free=t;
						strike[0].x=x;
						strike[0].y=y;
						strike[0].stop=stop_and_face;
						do_it=TRUE;
					}
				}
			}

//			if (plr_facing(x-px,y-py,&teams[p_num-1]) && target_towards_ball(x,y,px,py)
//			if ((target_towards_ball(x,y,px,py) || stop_and_face) &&
//			if (
//				 teams[p_num-1].tm_act<=TURN_ACT)
			
			if ((p_num!=KP_A && p_num!=KP_B)
				 || (p_num==KP_A && cannot_pick_up<12) || (p_num==KP_B && cannot_pick_up>11))
			{
// Keeper cannot pick ball up...

// Player must be running or standing...

				if (teams[p_num-1].tm_trap>=0)
				{
// Must control ball or may hit it first time...

/***** TRAP AND CONTROL *****/

					if (can_strike&128)
					{
						if (z<PLAYER_HEIGHT/2)
						{
// Feet level...
							rotate_offs(MC_TRAPL,cx,cy,cz,x_face,y_face);
							rotate_offs(MC_TRAPR,cx2,cy2,cz,x_face,y_face);
							cx=(cx+cx2)/2;
							cy=(cy+cy2)/2;
							gt=get_there_time(p_num,x-cx,y-cy);
							t=i-(gt+ft_ttm);
							if (t>=0 && t<strike[1].free && (teams[p_num-1].control || t<ff))
							{
// He has time to animate...
// Best so far!
								special_move=TRUE;
								if (trap_option || !user_controlled)
								{
				  					strike[1].t=i;
				  					strike[1].free=t;
									strike[1].atime=ft_ttm;
				  					strike[1].gt=gt;
									strike[1].x=x-cx;
									strike[1].y=y-cy;
									strike[1].stop=stop_and_face;
									do_it=TRUE;
								}
							}
						}
						else
						{
							if (z<(PLAYER_HEIGHT-2))
							{
// Chest level...
								rotate_offs(MC_CHEST,cx,cy,cz,x_face,y_face);
								gt=get_there_time(p_num,x-cx,y-cy);
								t=i-(gt+ft_ctm);
								if (t>=0 && t<strike[2].free && (teams[p_num-1].control || t<ff))
								{
// He has time to animate...
// Best so far!
									special_move=TRUE;
									if (trap_option || !user_controlled)
									{
							  			strike[2].t=i;
							  			strike[2].free=t;
										strike[2].atime=ft_ctm;
						  				strike[2].gt=gt;
										strike[2].x=x-cx;
										strike[2].y=y-cy;
										strike[2].stop=stop_and_face;
										do_it=TRUE;
									}
								}
							}
							else
							{
								if (z<(PLAYER_HEIGHT+4))
								{
// Head level...
									rotate_offs(MC_D_HEAD,cx,cy,cz,x_face,y_face);
									gt=get_there_time(p_num,x-cx,y-cy);
									t=i-(gt+ft_utm);
									if (t>=0 && t<strike[3].free && (teams[p_num-1].control || t<ff))
									{
// He has time to animate...
// Best so far!
										special_move=TRUE;
										if (trap_option || !user_controlled)
										{
							  				strike[3].t=i;
							  				strike[3].free=t;
											strike[3].atime=ft_utm;
							  				strike[3].gt=gt;
											strike[3].x=x-cx;
											strike[3].y=y-cy;
											strike[3].stop=stop_and_face;
											do_it=TRUE;
										}
									}
								}
							}
						}
					}
				}

				if (teams[p_num-1].tm_trap<=0)
				{
	
// May hit it first time...

/***** FIRST TIME STRIKE *****/

					if (z<PLAYER_HEIGHT/4)
					{
						if (can_strike&1)
						{
// Feet level...
							rotate_offs(MC_SHOOTL,cx,cy,cz,x_face,y_face);
							rotate_offs(MC_SHOOTR,cx2,cy2,cz,x_face,y_face);
							cx=(cx+cx2)/2;
							cy=(cy+cy2)/2;
							gt=get_there_time(p_num,x-cx,y-cy);
							t=i-(gt+ft_ktm);
							if (t>=0 && t<strike[8].free && (teams[p_num-1].control || t<ff))
							{
// He has time to animate...
// Best so far!
								special_move=TRUE;
								if (strike_option || !user_controlled)
								{
					  				strike[8].t=i;
					  				strike[8].free=t;
									strike[8].atime=ft_ktm;
					  				strike[8].gt=gt;
									strike[8].x=x-cx;
									strike[8].y=y-cy;
									strike[8].stop=stop_and_face;
									do_it=TRUE;
								}
							}
						}

						if (can_strike&64)
						{
// Feet level...
							rotate_offs(MC_CHIPL,cx,cy,cz,x_face,y_face);
							rotate_offs(MC_CHIPR,cx2,cy2,cz,x_face,y_face);
							cx=(cx+cx2)/2;
							cy=(cy+cy2)/2;
							gt=get_there_time(p_num,x-cx,y-cy);
							t=i-(gt+ft_ctm);
							if (t>=0 && t<strike[10].free && (teams[p_num-1].control || t<ff))
							{
// He has time to animate...
// Best so far!
								special_move=TRUE;
								if (strike_option || !user_controlled)
								{
					  				strike[10].t=i;
					  				strike[10].free=t;
									strike[10].ptype=pass_type;
									strike[10].pplr=receiver;
									strike[10].atime=ft_ctm;
					  				strike[10].gt=gt;
									strike[10].x=x-cx;
									strike[10].y=y-cy;
									strike[10].stop=stop_and_face;
									do_it=TRUE;
								}
							}
						}
					}
					else
					{
						if (z<PLAYER_HEIGHT*.5)
						{
// volley level...
							if (can_strike&2)
							{
								rotate_offs(MC_VOLLEYL,cx,cy,cz,x_face,y_face);
								gt=get_there_time(p_num,x-cx,y-cy);
								t=i-(gt+ft_vtm);
								if (t>=0 && t<strike[5].free && (teams[p_num-1].control || t<ff))
								{
// He has time to animate...
// Best so far!
									special_move=TRUE;
									if (strike_option || !user_controlled)
									{
						  				strike[5].t=i;
						  				strike[5].free=t;
										strike[5].atime=ft_vtm;
						  				strike[5].gt=gt;
										strike[5].x=x-cx;
										strike[5].y=y-cy;
										strike[5].stop=stop_and_face;
										do_it=TRUE;
									}
								}
							}
						}
						else
						{
							if (z<PLAYER_HEIGHT*.67)
							{
								if (can_strike&4)
								{
									rotate_offs(MC_DV_HEAD,cx,cy,cz,x_face,y_face);
									gt=get_there_time(p_num,x-cx,y-cy);
									t=i-(gt+ft_dtm);
									if (t>=0 && t<strike[6].free && (teams[p_num-1].control || t<ff))
									{
// He has time to animate...
// Best so far!
										special_move=TRUE;
										if (strike_option || !user_controlled)
										{
						  					strike[6].t=i;
						  					strike[6].free=t;
											strike[6].atime=ft_dtm;
						  					strike[6].gt=gt;
											strike[6].x=x-cx;
											strike[6].y=y-cy;
											strike[6].stop=stop_and_face;
											do_it=TRUE;
										}
									}
								}
							}
							else
							{
								if (z<PLAYER_HEIGHT+2)
								{
// head level...
									if (can_strike&32)
									{
										rotate_offs(MC_OVERHEAD,cx,cy,cz,x_face,y_face);
										gt=get_there_time(p_num,x-cx,y-cy);
										t=i-(gt+ft_otm);
										if (t>=0 && t<strike[4].free && (teams[p_num-1].control || t<ff))
										{
// He has time to animate...
// Best so far!
											special_move=TRUE;
											if (strike_option || !user_controlled)
											{
							  					strike[4].t=i;
							  					strike[4].free=t;
												strike[4].atime=ft_otm;
							  					strike[4].gt=gt;
												strike[4].x=x-cx;
												strike[4].y=y-cy;
												strike[4].stop=stop_and_face;
												do_it=TRUE;
											}
										}
									}

									if (can_strike&8)
									{
// He has time...
										rotate_offs(MC_S_HEAD,cx,cy,cz,x_face,y_face);
										gt=get_there_time(p_num,x-cx,y-cy);
										t=i-(gt+ft_stm);
										if (t>=0 && t<strike[9].free && (teams[p_num-1].control || t<ff))
										{
// He has time to animate...
// Best so far!
											special_move=TRUE;
											if (strike_option || !user_controlled)
											{
							  					strike[9].t=i;
							  					strike[9].free=t;
												strike[9].ptype=pass_type;
												strike[9].pplr=receiver;
												strike[9].atime=ft_stm;
							  					strike[9].gt=gt;
												strike[9].x=x-cx;
												strike[9].y=y-cy;
												strike[9].stop=stop_and_face;
												do_it=TRUE;
											}
										}
									}
								}
								else
								{
									if (z<teams[p_num-1].tm_jump)
									{
// Jump level...
										if (can_strike&16)
										{
// He has time...
											rotate_offs(MC_J_HEAD,cx,cy,cz,x_face,y_face);
											gt=get_there_time(p_num,x-cx,y-cy);
											t=i-(gt+ft_jtm);
											if (ABS(cz+prat-z)<8 && t>=0 && t<strike[7].free && (teams[p_num-1].control || t<ff))
											{
// He has time to animate...
// Best so far!
												special_move=TRUE;
												if (strike_option || !user_controlled)
												{
							  						strike[7].t=i;
							  						strike[7].free=t;
													strike[7].ptype=pass_type;
													strike[7].pplr=receiver;
													strike[7].atime=ft_jtm;
							  						strike[7].gt=gt;
													strike[7].x=x-cx;
													strike[7].y=y-cy;
													strike[7].stop=stop_and_face;
													do_it=TRUE;
												}
											}
										}
									}
								}
							}
			 			}
					}
				}
			}
		}
	}
	return(do_it);
}
#else

// No first-time passing...

char can_i_intercept(int p_num,float x,float y,float z,float px,float py,short i)
{
	if (z>=teams[p_num-1].tm_jump)
		return(FALSE);

	float cx,cy,cz,cx2,cy2,ang;
	float rate=full_spd(&teams[p_num-1]);
	float d=calc_dist(x-px,y-py);
	char can_strike;
	char do_it=FALSE;
	char stand;

	short ff=1+teams[p_num-1].tm_flair/16;		// Reaction times.

	short gt=get_there_time(p_num,x,y);
	short t;

	if (gt<=i)
	{
// He can get to ball in time...

		if (ball_poss)
		{
// Opponent has ball... (No control or strike!)
/***** RUN ONTO BALL *****/
			t=i-gt;
			if (t>0 && t<strike[0].free && (teams[p_num-1].control || t<ff))
			{
	  			strike[0].t=i;
	  			strike[0].free=t;
				strike[0].x=x;
				strike[0].y=y;
				strike[0].stop=stop_and_face;
				do_it=TRUE;
			}
		}
		else
		{
			if (user_controlled)
			{
				can_strike=128+32+16+8+4+2+1;
				pass_type=0;
			}
			else
				can_strike=first_time_strike(p_num,x,y,z,px,py);

/***** RUN ONTO BALL *****/

			if (z<PLAYER_HEIGHT/3)
			{
// Feet level...
				ang=angle_to_xy(x-px,y-py,teams[p_num-1].tm_xdis,teams[p_num-1].tm_ydis);
				if (ang>0 || user_controlled)
				{
// Target is in front of player...
					t=i-gt;
					if (t>=0 && t<strike[0].free && (teams[p_num-1].control || t<ff))
					{
		  				strike[0].t=i;
		  				strike[0].free=t;
						strike[0].x=x;
						strike[0].y=y;
						strike[0].stop=stop_and_face;
						do_it=TRUE;
					}
				}
			}

//			if (plr_facing(x-px,y-py,&teams[p_num-1]) && target_towards_ball(x,y,px,py)
//			if ((target_towards_ball(x,y,px,py) || stop_and_face) &&
//			if (
//				 teams[p_num-1].tm_act<=TURN_ACT)
			
			if ((p_num!=KP_A && p_num!=KP_B)
				 || (p_num==KP_A && cannot_pick_up<12) || (p_num==KP_B && cannot_pick_up>11))
			{
// Keeper cannot pick ball up...

// Player must be running or standing...

				if (teams[p_num-1].tm_trap>=0)
				{
// Must control ball or may hit it first time...

/***** TRAP AND CONTROL *****/

					if (can_strike&128)
					{
						if (z<PLAYER_HEIGHT/2)
						{
// Feet level...
							rotate_offs(MC_TRAPL,cx,cy,cz,x_face,y_face);
							rotate_offs(MC_TRAPR,cx2,cy2,cz,x_face,y_face);
							cx=(cx+cx2)/2;
							cy=(cy+cy2)/2;
							gt=get_there_time(p_num,x-cx,y-cy);
							t=i-(gt+ft_ttm);
							if (t>=0 && t<strike[1].free && (teams[p_num-1].control || t<ff))
							{
// He has time to animate...
// Best so far!
								special_move=TRUE;
								if ((user_controlled && uf2) || !user_controlled)
								{
				  					strike[1].t=i;
				  					strike[1].free=t;
									strike[1].atime=ft_ttm;
				  					strike[1].gt=gt;
									strike[1].x=x-cx;
									strike[1].y=y-cy;
									strike[1].stop=stop_and_face;
									do_it=TRUE;
								}
							}
						}
						else
						{
							if (z<(PLAYER_HEIGHT-2))
							{
// Chest level...
								rotate_offs(MC_CHEST,cx,cy,cz,x_face,y_face);
								gt=get_there_time(p_num,x-cx,y-cy);
								t=i-(gt+ft_ctm);
								if (t>=0 && t<strike[2].free && (teams[p_num-1].control || t<ff))
								{
// He has time to animate...
// Best so far!
									special_move=TRUE;
									if ((user_controlled && uf2) || !user_controlled)
									{
							  			strike[2].t=i;
							  			strike[2].free=t;
										strike[2].atime=ft_ctm;
						  				strike[2].gt=gt;
										strike[2].x=x-cx;
										strike[2].y=y-cy;
										strike[2].stop=stop_and_face;
										do_it=TRUE;
									}
								}
							}
							else
							{
								if (z<(PLAYER_HEIGHT+4))
								{
// Head level...
									rotate_offs(MC_D_HEAD,cx,cy,cz,x_face,y_face);
									gt=get_there_time(p_num,x-cx,y-cy);
									t=i-(gt+ft_utm);
									if (t>=0 && t<strike[3].free && (teams[p_num-1].control || t<ff))
									{
// He has time to animate...
// Best so far!
										special_move=TRUE;
										if ((user_controlled && uf2) || !user_controlled)
										{
							  				strike[3].t=i;
							  				strike[3].free=t;
											strike[3].atime=ft_utm;
							  				strike[3].gt=gt;
											strike[3].x=x-cx;
											strike[3].y=y-cy;
											strike[3].stop=stop_and_face;
											do_it=TRUE;
										}
									}
								}
							}
						}
					}
				}

				if (teams[p_num-1].tm_trap<=0)
				{
	
// May hit it first time...

/***** FIRST TIME STRIKE *****/

					if (z<PLAYER_HEIGHT/4)
					{
						if (can_strike&1)
						{
// Feet level...
							rotate_offs(MC_SHOOTL,cx,cy,cz,x_face,y_face);
							rotate_offs(MC_SHOOTR,cx2,cy2,cz,x_face,y_face);
							cx=(cx+cx2)/2;
							cy=(cy+cy2)/2;
							gt=get_there_time(p_num,x-cx,y-cy);
							t=i-(gt+ft_ktm);
							if (t>=0 && t<strike[8].free && (teams[p_num-1].control || t<ff))
							{
// He has time to animate...
// Best so far!
								special_move=TRUE;
								if ((user_controlled && uf1) || !user_controlled)
								{
					  				strike[8].t=i;
					  				strike[8].free=t;
									strike[8].atime=ft_ktm;
					  				strike[8].gt=gt;
									strike[8].x=x-cx;
									strike[8].y=y-cy;
									strike[8].stop=stop_and_face;
									do_it=TRUE;
								}
							}
						}

						if (can_strike&64)
						{
// Feet level...
							rotate_offs(MC_CHIPL,cx,cy,cz,x_face,y_face);
							rotate_offs(MC_CHIPR,cx2,cy2,cz,x_face,y_face);
							cx=(cx+cx2)/2;
							cy=(cy+cy2)/2;
							gt=get_there_time(p_num,x-cx,y-cy);
							t=i-(gt+ft_ctm);
							if (t>=0 && t<strike[10].free && (teams[p_num-1].control || t<ff))
							{
// He has time to animate...
// Best so far!
								special_move=TRUE;
								if ((user_controlled && uf1) || !user_controlled)
								{
					  				strike[10].t=i;
					  				strike[10].free=t;
									strike[10].ptype=pass_type;
									strike[10].pplr=receiver;
									strike[10].atime=ft_ctm;
					  				strike[10].gt=gt;
									strike[10].x=x-cx;
									strike[10].y=y-cy;
									strike[10].stop=stop_and_face;
									do_it=TRUE;
								}
							}
						}
					}
					else
					{
						if (z<PLAYER_HEIGHT*.5)
						{
// volley level...
							if (can_strike&2)
							{
								rotate_offs(MC_VOLLEYL,cx,cy,cz,x_face,y_face);
								gt=get_there_time(p_num,x-cx,y-cy);
								t=i-(gt+ft_vtm);
								if (t>=0 && t<strike[5].free && (teams[p_num-1].control || t<ff))
								{
// He has time to animate...
// Best so far!
									special_move=TRUE;
									if ((user_controlled && uf1) || !user_controlled)
									{
						  				strike[5].t=i;
						  				strike[5].free=t;
										strike[5].atime=ft_vtm;
						  				strike[5].gt=gt;
										strike[5].x=x-cx;
										strike[5].y=y-cy;
										strike[5].stop=stop_and_face;
										do_it=TRUE;
									}
								}
							}
						}
						else
						{
							if (z<PLAYER_HEIGHT*.67)
							{
								if (can_strike&4)
								{
									rotate_offs(MC_DV_HEAD,cx,cy,cz,x_face,y_face);
									gt=get_there_time(p_num,x-cx,y-cy);
									t=i-(gt+ft_dtm);
									if (t>=0 && t<strike[6].free && (teams[p_num-1].control || t<ff))
									{
// He has time to animate...
// Best so far!
										special_move=TRUE;
										if ((user_controlled && uf1) || !user_controlled)
										{
						  					strike[6].t=i;
						  					strike[6].free=t;
											strike[6].atime=ft_dtm;
						  					strike[6].gt=gt;
											strike[6].x=x-cx;
											strike[6].y=y-cy;
											strike[6].stop=stop_and_face;
											do_it=TRUE;
										}
									}
								}
							}
							else
							{
								if (z<PLAYER_HEIGHT+2)
								{
// head level...
									if (can_strike&32)
									{
										rotate_offs(MC_OVERHEAD,cx,cy,cz,x_face,y_face);
										gt=get_there_time(p_num,x-cx,y-cy);
										t=i-(gt+ft_otm);
										if (t>=0 && t<strike[4].free && (teams[p_num-1].control || t<ff))
										{
// He has time to animate...
// Best so far!
											special_move=TRUE;
											if ((user_controlled && uf1) || !user_controlled)
											{
							  					strike[4].t=i;
							  					strike[4].free=t;
												strike[4].atime=ft_otm;
							  					strike[4].gt=gt;
												strike[4].x=x-cx;
												strike[4].y=y-cy;
												strike[4].stop=stop_and_face;
												do_it=TRUE;
											}
										}
									}

									if (can_strike&8)
									{
// He has time...
										rotate_offs(MC_S_HEAD,cx,cy,cz,x_face,y_face);
										gt=get_there_time(p_num,x-cx,y-cy);
										t=i-(gt+ft_stm);
										if (t>=0 && t<strike[9].free && (teams[p_num-1].control || t<ff))
										{
// He has time to animate...
// Best so far!
											special_move=TRUE;
											if ((user_controlled && uf1) || !user_controlled)
											{
							  					strike[9].t=i;
							  					strike[9].free=t;
												strike[9].ptype=pass_type;
												strike[9].pplr=receiver;
												strike[9].atime=ft_stm;
							  					strike[9].gt=gt;
												strike[9].x=x-cx;
												strike[9].y=y-cy;
												strike[9].stop=stop_and_face;
												do_it=TRUE;
											}
										}
									}
								}
								else
								{
									if (z<teams[p_num-1].tm_jump)
									{
// Jump level...
										if (can_strike&16)
										{
// He has time...
											rotate_offs(MC_J_HEAD,cx,cy,cz,x_face,y_face);
											gt=get_there_time(p_num,x-cx,y-cy);
											t=i-(gt+ft_jtm);
											if (ABS(cz+prat-z)<8 && t>=0 && t<strike[7].free && (teams[p_num-1].control || t<ff))
											{
// He has time to animate...
// Best so far!
												special_move=TRUE;
												if ((user_controlled && uf1) || !user_controlled)
												{
							  						strike[7].t=i;
							  						strike[7].free=t;
													strike[7].ptype=pass_type;
													strike[7].pplr=receiver;
													strike[7].atime=ft_jtm;
							  						strike[7].gt=gt;
													strike[7].x=x-cx;
													strike[7].y=y-cy;
													strike[7].stop=stop_and_face;
													do_it=TRUE;
												}
											}
										}
									}
								}
							}
			 			}
					}
				}
			}
		}
	}
	return(do_it);
}
#endif

/*******************************************************************************
*****************************************************************************/

void clear_strike()

{
// Clear first time animation array...
	for (short i=0; i<11; i++)
	{
		strike[i].t=0;			// Init start time.
		strike[i].free=1000;	// Init wait time.
		strike[i].ptype=0;
		strike[i].pplr=0;
	}
}

/*******************************************************************************
*****************************************************************************/

void decide_on_face(match_player *p)
{
	float gx,gy,x,y,d;
	if (p->tm_player<12)
// Team A...
		gx=0;		// His goal...
	else
		gx=pitch_len;		// His goal...

	gy=cntspot_y;

	gx=gx-p->tm_x;
	gy=gy-p->tm_y;

	d=calc_dist(gx,gy);
	if (d<prat*30)
	{
// In Defense...

		if (p->tm_player<12)
			must_face_x=1;
		else
			must_face_x=-1;

		must_face=TRUE;
	}
	else
	{
// Not in defense...
		if (p->tm_player<12)
			gx=pitch_len;
		else
			gx=0;
		
		gx=gx-p->tm_x;

		d=calc_dist(gx,gy);
		if (d<(MIN_SHOOT_DIST+((float)p->tm_pow*3)))
		{
// In Shooting Range...			
			must_face_x=gx/d;
			must_face_y=gy/d;
			must_face=TRUE;

		}
	}
}

/*******************************************************************************
*****************************************************************************/

char go_to_path(int p_num)
// Send player(p_num) to intersection with ball path.
// If he cannot meet ball then best try!

{
	float spd_up;
	special_move=FALSE;

	teams[p_num-1].tm_fpass_type=0;
	teams[p_num-1].tm_fpass_to=0;

	float x,y,z;
	float px=teams[p_num-1].tm_x;
	float py=teams[p_num-1].tm_y;
	short i;
	char do_it=FALSE;

	first_time_it=TRUE;

	clear_strike();

/*** Capture Timings ***/
/* Release Ball */

	if (user_controlled)
// Allow user to animate faster for responsiveness...
		spd_up=1.3;
	else
		spd_up=1;

// Kick time...
	ft_ktm=MCC_SHOOT/(MC_SHOOT_FS*spd_up*fstep_factor(teams[p_num-1].tm_flair));

// Volley time...
	ft_vtm=MCC_VOLLEY/(MC_VOLLEY_FS*spd_up*fstep_factor(teams[p_num-1].tm_flair));

// Diving time...
	ft_dtm=MCC_DV_HEAD/(MC_DV_HEAD_FS*spd_up*fstep_factor(teams[p_num-1].tm_flair));

// Overhead time...
	ft_otm=MCC_OVERHEAD/(MC_OVERHEAD_FS*spd_up*fstep_factor(teams[p_num-1].tm_flair));

// Standing time...
	ft_stm=MCC_S_HEAD/(MC_S_HEAD_FS*spd_up*fstep_factor(teams[p_num-1].tm_flair));

// Jumping time...
	ft_jtm=MCC_J_HEAD/(MC_J_HEAD_FS*spd_up*fstep_factor(teams[p_num-1].tm_flair));
//		ft_jtm=MCC_J_HEAD/MC_J_HEAD_FS;

/* Keep Ball */

// Trapping time...
	ft_ttm=MCC_TRAP/(MC_TRAP_FS*spd_up*fstep_factor(teams[p_num-1].tm_cont));

// Chesting time...
	ft_ctm=MCC_CHEST/(MC_CHEST_FS*spd_up*fstep_factor(teams[p_num-1].tm_cont));

// Up head time...
	ft_utm=MCC_D_HEAD/(MC_D_HEAD_FS*spd_up*fstep_factor(teams[p_num-1].tm_cont));

	must_face=FALSE;

	auto_select=FALSE;

	if (user_controlled)
	{
		if (um && (uf1 || uf2))
// User.. Directional control...
		{
			must_face=TRUE;		// Forced to face in a particular dir...
			must_face_x=ux;
			must_face_y=uy;
		}
		else
			if (uf1 || uf2)
			{
// User.. No directional control...
				decide_on_face(&teams[p_num-1]);
			}
	}
	else
	{
		if ((p_num<12 && !auto_users_a) || p_num==KP_A
			 || (p_num>11 && !auto_users_b) || p_num==KP_B)
		{
// Computer player will try to face goal or away from defense...
			auto_select=TRUE;

			if (p_num==receiver_a || p_num==receiver_b)
			{
				decide_on_face(&teams[p_num-1]);
			}
		}
		else
		{
// Should be a user...
			auto_select=FALSE;		// Don't allow computer to select a move!
		}
	}

	for (i=1; i<50; i+=2)
	{
		x=ball_pred_tab[i][0];
		y=ball_pred_tab[i][1];
		z=ball_pred_tab[i][2];

		ball_int_speed=ABS(x-ball_pred_tab[i-1][0])
						  +ABS(y-ball_pred_tab[i-1][1])
						  +(ABS(z-ball_pred_tab[i-1][2])*2);

		if ((x<0) || (x>=pitch_len) || (y<0) || (y>=pitch_wid))
// Ball out of bounds
		{
			x=ball_pred_tab[i-1][0];
			y=ball_pred_tab[i-1][1];
			i=60;
		}
		else
		{
			do_it+=can_i_intercept(p_num,x,y,z,px,py,i);
		}
	}

	if (do_it)
	{
/*
		if ((p_num<12 && auto_users_a && !teams[p_num-1].control)
			|| (p_num>11 && auto_users_b && !teams[p_num-1].control))
		{
			reselect();
			user_conts(&teams[p_num-1]);
			user_controlled=teams[p_num-1].control;
		}
*/
		intercept(p_num);

		if (ball_poss)
			teams[p_num-1].ball_state=-ball_poss;
		else
			teams[p_num-1].ball_state=last_touch;
	}

	must_face=FALSE;
	first_time_it=FALSE;
	return(do_it);
}

/******************************************************************************
*****************************************************************************/

void ogo_to_path(int p_num,char header_only)

// Send player(p_num) to intersection with ball path.
// If he cannot meet ball then best try!

{
	float x,y,z,d;
	float px=teams[p_num-1].tm_x;
	float py=teams[p_num-1].tm_y;
	float rate=actual_spd(&teams[p_num-1]);
	action="Intercept";

	reset_ideas(&teams[p_num-1]);

	if (p_num<12)
		interceptor_a=p_num;
	else
		interceptor_b=p_num;

// His intention is to intercept ball.
// Therefore his flair determines no. of turns before rethink!

	int ff=33-(teams[p_num-1].tm_flair/4);
	teams[p_num-1].int_move=I_INTERCEPT;		// Intercept ball!
	teams[p_num-1].int_cnt=ff;						// Flair factor.

	char feet_hit=FALSE;
	char body_hit=FALSE;
	char head_hit=FALSE;

	float feet_x,feet_y,body_x,body_y,head_x,head_y;

	for (int i=1; i<50; i++)
	{
		x=ball_pred_tab[i][0];
		y=ball_pred_tab[i][1];
		z=ball_pred_tab[i][2];

		if ((x<0) || (x>=pitch_len) || (y<0) || (y>=pitch_wid))
// Ball out of bounds
		{
			x=ball_pred_tab[i-1][0];
			y=ball_pred_tab[i-1][1];
			i=60;
		}
		else
		{
			if (z<PLAYER_HEIGHT/2)
			{
			  	d=calc_dist(x-px,y-py);
				d=(int)(((float)d)/rate);					//How many steps?

				if (d<=i)
// He can get there in time!
// At feet...
				{
					feet_x=x;
					feet_y=y;
					feet_hit=TRUE;
					i=60;
				}
			}
			else
			{
				if ((z<=PLAYER_HEIGHT-4) && (!body_hit))
				{
				  	d=calc_dist(x-px,y-py);
					d=(int)(((float)d)/rate);					//How many steps?

					if (d<=i)
// He can get there in time!
// On body...
					{
						body_x=x;
						body_y=y;
						body_hit=TRUE;
					}

//					init_run_act(&teams[p_num-1],x,y,TRUE);				//Go to path point!
//					i=60;												// End For Loop!
				}
				else
				{
				  	if ((z>PLAYER_HEIGHT-4) && (z<=teams[p_num-1].tm_jump) && (!head_hit))
					{
						d=calc_dist(x-px,y-py);
						d=(int)(((float)d)/rate);					//How many steps?

						if (d+(sqrt(z-PLAYER_HEIGHT+5)/gravity)<=i)
// He can get there in time!
// On head...
						{
							head_x=x;
							head_y=y;
							head_hit=TRUE;
						}

//						init_run_act(&teams[p_num-1],x,y,TRUE);				//Go to path point!
//						i=60;
					}
				}
			}
		}
	}
	
	if ((!feet_hit) && (!head_hit) && (!body_hit))
// He cant intersect!
	{
		init_run_act(&teams[p_num-1],x,y,TRUE);			// run toward last.
	}
	else
	{
		if (header_only)
		{
			if (head_hit)
			{
				init_run_act(&teams[p_num-1],head_x,head_y,TRUE);	//Go to path point!
			}
		}
		else
		{
			if (feet_hit)
			{
				init_run_act(&teams[p_num-1],feet_x,feet_y,TRUE);	//pitch line point
			}
			else
				if (head_hit)
				{
					init_run_act(&teams[p_num-1],head_x,head_y,TRUE);	//Go to path point!
				}
				else
					if (body_hit)
					{
						init_run_act(&teams[p_num-1],body_x,body_y,TRUE);	//Go to path point!
					}
		}
	}
}

/******************************************************************************
*****************************************************************************/

void get_tack_path(match_player *player)

// Find players intersection with ball path.
// When tackling!

{
	if (teams[ball_poss-1].tm_poss>4)
	{
// Opponent has ball for a bit...

		flag=FALSE;
		float x,y,z;
		float d,s;
		float px=player->tm_x;
		float py=player->tm_y;
		float rate=player->tm_rate+player->tm_pow;
		float last_diff=2000;

		if (((ball_poss) && (teams[ball_poss-1].tm_act==STAND_ACT))
			|| ((!ball_poss) && (ball_still)))

// Ball is not moving!
			if (plr_facing(ballx,bally,player))
				init_tackle_act(player,ballx,bally);				//Go to path point!
			else
				go_to_path(player->tm_player);
		else
		{

			for (int i=1; i<TACKLE_TURNS/2; i++)
			{
				x=ball_pred_tab[i][0];
				y=ball_pred_tab[i][1];
				z=ball_pred_tab[i][2];

				if ((x<0) || (x>=pitch_len) || (y<0) || (y>=pitch_wid))
// Ball out of bounds (So don't tackle!)
					i=60;

				if (z<=PLAYER_HEIGHT/2)
// Tackling player is half height.
				{
					d=calc_dist(x-px,y-py);

// Now the tricky bit...
// Using S=a(1-r^n)/(1-r) (S=tackle distance over time (n))
// a=(rate/8), r=tackle_decel...

					s=(rate/20)*(1-pow(TACKLE_DECEL,i))/(1-TACKLE_DECEL);	//How far in time (i)!

					if (d-s>last_diff)
// Ball getting further away!
						i=60;												// End For Loop!
					else
						last_diff=d-s;

					if (last_diff<=0)
// He can get there in time!
					{

// Take accuracy into account...

						float acc_xoff=(seed*(128-player->tm_ac)/4)/128;
						af_randomize();
						float acc_yoff=(seed*(128-player->tm_ac)/4)/128;
						if (seed&32) 
							acc_xoff=-acc_xoff;
						if (seed&16)
							acc_yoff=-acc_yoff;
						if (player->tm_player!=KP_A && player->tm_player!=KP_B)
//							init_tackle_act(player,x+acc_xoff,y+acc_yoff);				//Go to path point!
							init_tackle_act(player,x,y);
						else
// Keeper more accurate to provide better defense...
							init_tackle_act(player,x,y);
						flag=TRUE;
						i=60;												// End For Loop!
					}
				}
			}
		}
	}
}

/******************************************************************************
*****************************************************************************/

void set_there_flags(short taker)
{
#ifdef EURO96
 	if ((teams[taker-1].tm_act==STAND_ACT && plr_facing(ballx-teams[taker-1].tm_x,bally-teams[taker-1].tm_y,&teams[taker-1]))
		 && (teams[taker-1].tm_dist<BESIDE_BALL*3
		 || ((match_mode==PEN_KICK_A || match_mode==PEN_KICK_B) && teams[taker-1].tm_dist<(PEN_RUNUP_DIST+4))))
#else
 	if ((teams[taker-1].tm_act==STAND_ACT && plr_facing(ballx-teams[taker-1].tm_x,bally-teams[taker-1].tm_y,&teams[taker-1]))
		 && (teams[taker-1].tm_dist<BESIDE_BALL*3))
#endif
 	{
	  	if (!already_there)
		{
			reselection=TRUE;
	 	  	already_there=TRUE;
		}
	}
}

/******************************************************************************
*****************************************************************************/

void centre_pos(char flag,int pn,char &flag2,float &x,float &y)
{
// Taking centre!
	{
		if (((pn+1==centre_guy_1) && (flag==1))
			|| ((pn+1==centre_guy_1-11) && (flag==2)))
		{
			x=cntspot_x;
			y=cntspot_y-10;
			flag2=TRUE;
			set_there_flags(centre_guy_1);
		}

		if (((pn+1==centre_guy_2) && (flag==1))
			|| ((pn+1==centre_guy_2-11) && (flag==2)))
		{
			if (flag==1)
				x=cntspot_x+5;
			else
				x=cntspot_x-5;			// Receiver stands over line...

			y=cntspot_y+10;
			flag2=TRUE;
		}
	}
}

/******************************************************************************
*****************************************************************************/

void gkick_pos(char flag,int pn,char &flag2,float &x,float &y,char &taker)
{
// Taking Goal kick!
	{
		if (((pn+1==gkick_taker) && (flag==1))
			|| ((pn+1==gkick_taker-11) && (flag==2)))
		{
			x=taker_x;
			y=taker_y;

			taker=TRUE;

			flag2=TRUE;
			if (flag==2)
			{
				x=pitch_len-x;
				y=pitch_wid-y;
			}

			set_there_flags(gkick_taker);
		}
	}
}

/******************************************************************************
*****************************************************************************/

void corner_pos(char flag,int pn,char &flag2,float &x,float &y,char &taker)
{
// Taking Corner!
	{
		if (((pn+1==corner_taker) && (flag==1))
			|| ((pn+1==corner_taker-11) && (flag==2)))
		{
			x=incident_x;
			y=incident_y;
			taker=TRUE;

			flag2=TRUE;
			if (flag==2)
			{
				x=pitch_len-x;
				y=pitch_wid-y;
			}
			set_there_flags(corner_taker);
		}
	}
}

/******************************************************************************
*****************************************************************************/

void throw_in_pos(char flag,int pn,char &flag2,float &x,float &y,char &taker)
{
// Taking throw!
	{
		if (flag==2)
			pn=pn+11;

		if (pn+1==throw_in_taker)
		{
			x=incident_x;
			y=incident_y+((incident_y<cntspot_y) ? -8:8);
			taker=TRUE;

			flag2=TRUE;
			if (flag==2)
			{
				x=pitch_len-x;
				y=pitch_wid-y;
			}
			set_there_flags(throw_in_taker);
		}
	}
}

/******************************************************************************
*****************************************************************************/

void dfkick_pos(char flag,int pn,char &flag2,float &x,float &y,char &taker)
{
// Taking F.K.!
	{
		if (flag==2)
			pn=pn+11;

		if (pn+1==fkick_taker)
		{
			x=taker_x;
			y=taker_y;
			taker=TRUE;
			flag2=TRUE;
			if (flag==2)
			{
				x=pitch_len-x;
				y=pitch_wid-y;
			}

			set_there_flags(fkick_taker);
		}
		else
		{
			if (teams[pn].tm_wall)
			{
				for (int i=0; i<men_in_wall; i++)
				{
					if (wguys[i].guy==pn+1)
					{
						x=wguys[i].x;
						y=wguys[i].y;
						flag2=TRUE;
						i=men_in_wall;
						if (flag==2)
						{
							x=pitch_len-x;
							y=pitch_wid-y;
						}
					}
				}
			}
		}
	}
}

/******************************************************************************
*****************************************************************************/

void fkick_pos(char flag,int pn,char &flag2,float &x,float &y,char &taker)
{
// Taking F.K.!
	{
		if (flag==2)
			pn=pn+11;

		if (pn+1==fkick_taker)
		{
			x=taker_x;
			y=taker_y;
			taker=TRUE;
			flag2=TRUE;
			if (flag==2)
			{
				x=pitch_len-x;
				y=pitch_wid-y;
			}
			set_there_flags(fkick_taker);
		}
	}
}

/******************************************************************************
*****************************************************************************/

void penalty_pos(char flag,int pn,char &flag2,float &x,float &y,char &taker)
{
// Taking F.K.!
	{
		if (flag==2)
			pn=pn+11;

		if (pn+1==penalty_taker)
		{
			x=taker_x;
			y=taker_y;
			taker=TRUE;
			flag2=TRUE;
			if (flag==2)
			{
				x=pitch_len-x;
				y=pitch_wid-y;
			}

			set_there_flags(penalty_taker);
		}
	}
}

/******************************************************************************
*****************************************************************************/

void tunnel_pos(char flag,int pn,float &x,float &y)
{
	float tx=stadlist[setup.stadium].tunlx;
	float ty=-stadlist[setup.stadium].tunlz;
	float tz=stadlist[setup.stadium].tunly;
	float d=GO_TO_POS_DIST;

	if (flag==2)
	{
// Team B...
		pn+=11;
		if (ABS(teams[pn].go_ty-ty)<prat || 
			(teams[pn].tm_x>=(tx+prat-d) && teams[pn].tm_x<=(tx+prat+d)))
		{
// In line with tunnel...
			x=pitch_len-(tx+prat);
			y=pitch_wid-(ty);

			if (ABS(teams[pn].tm_y-(pitch_wid-y))<prat*2)
			{
// At end of tunnel...(don't draw him!)
				teams[pn].draw_me=FALSE;
			}
		}
		else
		{
			x=pitch_len-(tx+prat);
			if (ty>cntspot_y)
// Which goal-line...
				y=0;
			else
				y=pitch_wid;
		}
	}
	else
	{
// Team A...
		if (ABS(teams[pn].go_ty-ty)<prat ||
			(teams[pn].tm_x>=(tx-prat-d) && teams[pn].tm_x<=(tx-prat+d)))
		{
// In line with tunnel...
			x=tx-prat;
			y=ty;

			if (ABS(teams[pn].tm_y-y)<prat*2)
			{
// At end of tunnel...(don't draw him!)
				teams[pn].draw_me=FALSE;
			}
		}
		else
		{
			x=tx-prat;
			if (ty>cntspot_y)
// Which goal-line...
				y=pitch_wid;
			else
				y=0;
		}
	}
	set_there_flags(pn+1);
}
		
/******************************************************************************
*****************************************************************************/

int get_tac(int *t)
{
//	(*t)++;
//	(*t)--;
	return(*t);
}

/******************************************************************************
*****************************************************************************/

void get_target(char flag,int bz,int zx,int zy,int pn,float &x,float &y,int tac[(32*2)+6][10][2])
{
	float ox,oy;
	char flag2=FALSE;
	char taker=FALSE;

	if (dead_ball_cnt)
	{
		if (match_mode==SWAP_ENDS)

// Into tunnel...

		{
			tunnel_pos(flag,pn,x,y);
			flag2=TRUE;
		}

		if (((match_mode==CENTRE_A) && (flag==1))
			|| ((match_mode==CENTRE_B) && (flag==2)))

// Centre takers...
 
 			centre_pos(flag,pn,flag2,x,y);

		if (((match_mode==GOAL_KICK_TL) || (match_mode==GOAL_KICK_BL) && (flag==1))
			|| ((match_mode==GOAL_KICK_TR) || (match_mode==GOAL_KICK_BR) && (flag==2)))

// Goal kick takers...

			gkick_pos(flag,pn,flag2,x,y,taker);

		if (((match_mode==CORNER_TL) || (match_mode==CORNER_BL) && (flag==2))
			|| ((match_mode==CORNER_TR) || (match_mode==CORNER_BR) && (flag==1)))

// Corner takers...

			corner_pos(flag,pn,flag2,x,y,taker);

		if ((match_mode==THROW_IN_A) || (match_mode==THROW_IN_B))

// Throw-in taker...

			throw_in_pos(flag,pn,flag2,x,y,taker);

		if ((match_mode==DF_KICK_A) || (match_mode==DF_KICK_B))

// Direct F.K....

			dfkick_pos(flag,pn,flag2,x,y,taker);

		if ((match_mode==IF_KICK_A) || (match_mode==IF_KICK_B))

// In-direct F.K....

			fkick_pos(flag,pn,flag2,x,y,taker);

		if ((match_mode==PEN_KICK_A) || (match_mode==PEN_KICK_B))

// Penalty Kick....

			penalty_pos(flag,pn,flag2,x,y,taker);

	}

	if (!flag2)
/**************************/
// Normal match play!
	{
		if ((man2man_b) && (flag==2) && (teams[pn+11].tm_mark))
		{
// Team B defends man-to-man...
			x=pitch_len-man2man[pn-1][0];
			y=pitch_wid-man2man[pn-1][1];
		}
		else
		{
			if ((man2man_a) && (flag==1) && (teams[pn].tm_mark))
			{
// Team A defends man-to-man...
				x=man2man[pn-1][0];
				y=man2man[pn-1][1];
			}
			else
			{
// Normal Zonal Position...
	 			x=get_tac(&tac[bz][pn-1][0]);
				y=get_tac(&tac[bz][pn-1][1]);

				if (flag==1 && bz==68 && pn==centre_guy_2-1)
				{
					x=cntspot_x+80;
					y=cntspot_y+10;
					flag=0;
				}

				if (flag==2 && bz==69 && pn==centre_guy_2-12)
				{
					x=cntspot_x-80;
					y=cntspot_y+10;
					flag=0;
				}

				if (flag)
				{
					float bx=LIMIT(ballx,0,pitch_len);
					float by=LIMIT(bally,0,pitch_wid);

					if ((analogue) && (!ball_out_of_play) &&
						((!dead_ball_cnt) || (match_mode<CORNER_TL) || (match_mode>THROW_IN_B)))
					{
						if (flag==1)
						{
							ox=bx-zx;	// offset from centre of zone!
							oy=by-zy;
						}
						else
						{
							ox=(pitch_len-bx)-zx;	// offset from centre of zone!
							oy=(pitch_wid-by)-zy;
						}

						float xa,xb,xc,ya,yb,yc;

						if (ox<=0)
						{
							int b=bz-1;
							if (b<0)
								b=0;

							xa=get_tac(&tac[b][pn-1][0]);					//left zone
							ya=get_tac(&tac[b][pn-1][1]);					//left zone

							if (oy<=0)
							{
								b=bz-8-1;
								if (b<0)
									b=0;
								xb=get_tac(&tac[b][pn-1][0]);			//top left zone
								yb=get_tac(&tac[b][pn-1][1]);			//top left zone
								xc=get_tac(&tac[b+1][pn-1][0]);				//top zone
								yc=get_tac(&tac[b+1][pn-1][1]);				//top zone
							}
							else
							{
								b=bz+8;
								if (b>31)
									b=31;
								xb=get_tac(&tac[b-1][pn-1][0]);			//bot left zone
								yb=get_tac(&tac[b-1][pn-1][1]);			//bot left zone
								xc=get_tac(&tac[b][pn-1][0]);				//bot zone
								yc=get_tac(&tac[b][pn-1][1]);				//bot zone
							}
						}	
						else
						{
							int b=bz+1;
							if (b>31)
								b=31;
							xa=get_tac(&tac[b][pn-1][0]);					//right zone
							ya=get_tac(&tac[b][pn-1][1]);					//right zone

							if (oy<=0)
							{
								b=bz-8;
								if (b<0)
									b=0;
								xb=get_tac(&tac[b+1][pn-1][0]);			//top right zone
								yb=get_tac(&tac[b+1][pn-1][1]);			//top right zone
								xc=get_tac(&tac[b][pn-1][0]);				//top zone
								yc=get_tac(&tac[b][pn-1][1]);				//top zone
							}
							else
							{
								b=bz+8+1;
								if (b>31)
									b=31;
								xb=get_tac(&tac[b][pn-1][0]);			//bot right zone
								yb=get_tac(&tac[b][pn-1][1]);			//bot right zone
								xc=get_tac(&tac[b-1][pn-1][0]);				//bot zone
								yc=get_tac(&tac[b-1][pn-1][1]);				//bot zone
							}
						}

						float xint_ab=xa+((xb-xa)*ABS(oy)/zone_hgt);
						float xint_hc=x+((xc-x)*ABS(oy)/zone_hgt);

						float yint_cb=yc+((yb-yc)*ABS(ox)/zone_wid);
						float yint_ha=y+((ya-y)*ABS(ox)/zone_wid);

						x=xint_hc+((xint_ab-xint_hc)*ABS(ox)/zone_wid);
						y=yint_ha+((yint_cb-yint_ha)*ABS(oy)/zone_hgt);
					}
				}
			}
		}

		float xoff,yoff;
		if (flag)
		{
			if (flag==1)
			{
				xoff=x-incident_x;
				yoff=y-incident_y;
			}
			else
			{
				xoff=(pitch_len-x)-incident_x;
				yoff=(pitch_wid-y)-incident_y;
			}
		}

		switch(game_action)
		{
			float dist;
// Team A and B must be 10 yards away from ball!
			case(-1):
			case(1):
				dist=calc_dist(xoff,yoff);
				if (dist<prat*10)
				{
					if (flag==1)
					{
						x=incident_x+(xoff*(INCIDENT_DIST)/dist);
						y=incident_y+(yoff*(INCIDENT_DIST)/dist);
					}
					else
					{
						x=pitch_len-(incident_x+(xoff*(INCIDENT_DIST)/dist));
						y=pitch_wid-(incident_y+(yoff*(INCIDENT_DIST)/dist));
					}
				}
				break;

// Team A and B must be 10 yards away from ball and outside penalty box!
			case(2):
				if (ballx<cntspot_x)
					if (flag==1)
						x=prat*19;
					else
						x=pitch_len-(prat*19);
				else
					if (flag==1)
						x=pitch_len-(prat*19);		// On edge of 18 yard box!
					else
						x=prat*19;

				if (flag==1)
				{
					xoff=x-incident_x;
					yoff=y-incident_y;
				}
				else
				{
					xoff=(pitch_len-x)-incident_x;
					yoff=(pitch_wid-y)-incident_y;
				}

				dist=calc_dist(xoff,yoff);
				if (dist<prat*10)
				{
					if (flag==1)
					{
						x=incident_x+(xoff*(INCIDENT_DIST)/dist);
						y=incident_y+(yoff*(INCIDENT_DIST)/dist);
					}
					else
					{
						x=pitch_len-(incident_x+(xoff*(INCIDENT_DIST)/dist));
						y=pitch_wid-(incident_y+(yoff*(INCIDENT_DIST)/dist));
					}
				}
				break;
		}
	}
}

/******************************************************************************
*****************************************************************************/

void find_zonal_target(match_player *player,float px,float py)
{
	if (!player->draw_me && player->tm_y>0 && player->tm_y<pitch_wid)
		player->draw_me=TRUE;

	int ball_zn;
	char f;
	float tx,ty,sx,sy;
	if ((player->tm_player==KP_A) || (player->tm_player==KP_B))
	{

/****************
** Goal-Keeper	**
****************/

		if (player->tm_player==KP_A)
		{
			if ((dead_ball_cnt) && (gkick_taker==KP_A) && 
				((match_mode==GOAL_KICK_TL) || (match_mode==GOAL_KICK_BL)))
			{
// Taking Goal Kick!
				tx=taker_x;
				ty=taker_y;
				set_there_flags(gkick_taker);
			}
			else
			{
				if (match_mode==DF_KICK_B && men_in_wall>2)
				{
// Get keeper in position behind last man in wall...
					tx=keeper_pos_x;
					ty=keeper_pos_y;
				}
				else
				{
					if (match_mode==SWAP_ENDS)
					{
						get_target(1,ball_zn,zone1_x,zone1_y,(player->tm_player)-1,tx,ty,match_tactics1);
					}
					else
					{
						if (ball_poss>=12 && match_mode!=PEN_KICK_B && !penalty_shot)
						{
// Opponent_has ball...
							float d=calc_dist(ballx,bally-cntspot_y);		// distance of centre of goal to ball!
							if ((keeper_a_in_box) && (d<CLOSE_ANG_DIST+(prat*player->tm_vis)/8))
// Shut the door...
								close_angle(player,d,tx,ty);			// Close down the angle of shot.
							else
							{
								tx=KP_OFFLINE;
								ty=cntspot_y-1;
							}
						}
						else
						{
							if (match_mode==PEN_KICK_B)
								tx=0;
							else
								if (shot_pending && penalty_shot)
									tx=0;
								else
									tx=KP_OFFLINE;

							ty=cntspot_y-1;
						}
					}
				}
			}
		}
		else			
		{
 			if ((dead_ball_cnt) && (gkick_taker==KP_B) && 
 			((match_mode==GOAL_KICK_TR) || (match_mode==GOAL_KICK_BR)))
 			{
// Taking Goal Kick!
				tx=taker_x;
				ty=taker_y;
				set_there_flags(gkick_taker);
			}
			else
			{
				if (match_mode==DF_KICK_A && men_in_wall>2)
				{
// Get keeper in position behind last man in wall...
					tx=keeper_pos_x;
					ty=keeper_pos_y;
				}
				else
				{
					if (match_mode==SWAP_ENDS)
					{
						get_target(2,ball_zn,zone2_x,zone2_y,(player->tm_player)-12,tx,ty,match_tactics2);
						tx=pitch_len-tx;
						ty=pitch_wid-ty;
					}
					else
					{
						if (ball_poss && ball_poss<12 && match_mode!=PEN_KICK_A && !penalty_shot)
						{
// Opponent_has ball...
							float d=calc_dist(pitch_len-ballx,bally-cntspot_y);		// distance of centre of goal to ball!
							if ((keeper_b_in_box) && (d<CLOSE_ANG_DIST+(prat*player->tm_vis)/8))
// Shut the door...
								close_angle(player,d,tx,ty);			// Close down the angle of shot.
							else
							{
								tx=pitch_len-KP_OFFLINE;
								ty=cntspot_y-1;
							}
						}
						else
						{
							if (match_mode==PEN_KICK_A)
								tx=pitch_len-1;
							else
								if (shot_pending && penalty_shot)
									tx=pitch_len-1;
								else
									tx=pitch_len-KP_OFFLINE;

							ty=cntspot_y-1;
						}
					}
				}
			}
		}

		tx=tx-px;
		ty=ty-py;
		char s;
		float d=calc_dist(tx,ty);
		if ((player->face_dir!=get_dir(tx,ty)) &&
			(((player->go_step) && (d<STEP_RANGE*2))
			|| ((!player->go_step) && (d<STEP_RANGE))))
// Calculate single move.
		{
			s=TRUE;
			if (player->tm_rate>=d*32)
			{
				sx=tx;
				sy=ty;
			}
			else
			{
				sx=(player->tm_rate/(d*32))*tx;
				sy=(player->tm_rate/(d*32))*ty;
			}
		}
		else
		{
// Calculate single move.
			if (player->tm_rate>=d*16)
			{
				sx=tx;
				sy=ty;
			}
			else
			{
				sx=(player->tm_rate/(d*16))*tx;
				sy=(player->tm_rate/(d*16))*ty;
			}
		}

		init_run_act(player,tx+px,ty+py,TRUE);
		if (player->tm_act==RUN_ACT)
		{
			go_forward(player);
			player->go_cnt=0;
		}					
	}
	else
	{

/***********
** PLAYER **		
***********/

		if (!player->int_cnt)
		{
			if (player->tm_player<12)			// Team A?
			{
				if ((ball_zone1<32) && (last_touch<12) && (last_touch!=0))	// Team A. in possession?
					ball_zn=32;
				else
					ball_zn=0;
				ball_zn+=ball_zone1;
				get_target(1,ball_zn,zone1_x,zone1_y,(player->tm_player)-1,tx,ty,match_tactics1);

				tx=tx-px;
				ty=ty-py;
				float d=calc_dist(tx,ty);
				if ((player->tm_act==RUN_ACT) ||
					(d>GO_TO_POS_DIST && player->tm_act!=RUN_ACT))
				{
					char s;
					float d=calc_dist(tx,ty);
					if ((player->face_dir!=get_dir(tx,ty)) &&
						(((player->go_step) && (d<STEP_RANGE*2))
						|| ((!player->go_step) && (d<STEP_RANGE))))

					{
						s=TRUE;
					}
					else
					{
						s=FALSE;
					}

					init_run_act(player,tx+px,ty+py,TRUE);
					if (player->tm_act==RUN_ACT)
					{
						go_forward(player);
  						player->go_cnt=0;
					}
				}
				else
				{
// There already!
					if (player->int_move==I_THROW)
					{
						player->int_cnt=1;
						reset_ideas(player);
					}
				}
			}
			else
			{
				if ((ball_zone2<32) && last_touch>11)								// Team B. in possession?
					ball_zn=32;
				else
					ball_zn=0;
				ball_zn+=ball_zone2;
				get_target(2,ball_zn,zone2_x,zone2_y,(player->tm_player)-12,tx,ty,match_tactics2);
				tx=(pitch_len-tx)-px;
				ty=(pitch_wid-ty)-py;
				float d=calc_dist(tx,ty);
				if ((player->tm_act==RUN_ACT) ||
					(d>GO_TO_POS_DIST && player->tm_act!=RUN_ACT))
				{
					char s;
					float d=calc_dist(tx,ty);

					if ((player->face_dir!=get_dir(tx,ty)) &&
						((player->go_step) && (d<STEP_RANGE*2))
						|| ((!player->go_step) && (d<STEP_RANGE)))

// Calculate single move.
					{
						s=TRUE;
					}
					else
					{
						s=FALSE;
					}
					init_run_act(player,tx+px,ty+py,TRUE);
					if (player->tm_act==RUN_ACT)
					{
						go_forward(player);
						player->go_cnt=0;
					}
				}
				else
				{
// There already!
					if (player->int_move==I_THROW)
					{
						player->int_cnt=1;
						reset_ideas(player);
					}
				}
			}
		}
	}
}

/******************************************************************************
*****************************************************************************/

// Return closest guy to the predicted path of ball who is not busy!
// p_num = first player in team.

int get_near_path(int p_num,int not_busy)
{
	int near_guy=0, closest=10000;
	int t=0;

// Get average position of ball...

	float x1=ball_pred_tab[t][0];
	float y1=ball_pred_tab[t][1];
	float z1=ball_pred_tab[t][2];

	float px,py;
	short points=0;
	float x=-1000;
	float y=0;
	float z=0;
	float	d;

	for (int b=1; b<40; b++)
	{
		if (x<-999 && ball_pred_tab[b][2]<PLAYER_HEIGHT+4)
		{
			x=ball_pred_tab[b][0]-x1;
			y=ball_pred_tab[b][1]-y1;
		}
		else
		{
			if (x>-999)
			{
				x+=ball_pred_tab[b][0]-x1;
				y+=ball_pred_tab[b][1]-y1;
				points++;
			}
		}
	}

	if (points)
	{
		x=x/points;
		y=y/points;
		x+=x1;
		y+=y1;
	}
	else
	{
		x=ball_pred_tab[40][0];
		y=ball_pred_tab[40][1];
	}

	for (int i=p_num+10; i>=p_num; i--)
	{
		if (teams[i].tm_notme)
			teams[i].tm_notme--;		// he can't get there!
		else
		{
			if ((teams[i].tm_act<=TURN_ACT || (teams[i].tm_act==TACKLE_ACT && teams[i].control))
				 && ball_poss!=p_num+1)		//player is not busy!
			{
				if ((!(teams[i].int_cnt)) || (not_busy))
				{
					px=teams[i].tm_x;
					py=teams[i].tm_y;

					d=calc_dist(px-x,py-y);

					if (i==(KP_A-1) || i==(KP_B-1))
					{
// Keeper only intercept if half as close as defender!

						if (d*2<closest && closest>prat*2)
						{
							near_guy=i+1;						//This guy is closer!
							closest=d;
						}
					}
					else
					{
						if (d<closest)
						{
							near_guy=i+1;						//This guy is closer!
							closest=d;
						}
					}
				}
			}
		}
	}
	return(near_guy);
}

/******************************************************************************
*****************************************************************************/

// Return closest guy to the predicted path of ball who is not busy!
// p_num = first player in team.

int oget_near_path(int p_num,int not_busy)
{
	int near_guy=0, closest=10000;
	int t=first_bounce;
	if (t<0)
		t=0;

// Get average position of ball...

	float x1=ball_pred_tab[t][0];
	float y1=ball_pred_tab[t][1];
	float z1=ball_pred_tab[t][2];

	float px,py;
	short points=0;
	float x=0;
	float y=0;
	float z=0;
	float	d;

	for (int b=t+1; b<40; b++)
	{
		if (ball_pred_tab[b][2]<PLAYER_HEIGHT+4)
		{
			x+=ball_pred_tab[b][0]-x1;
			y+=ball_pred_tab[b][1]-y1;
			points++;
		}
	}

	if (points)
	{
		x=x/points;
		y=y/points;
		x+=x1;
		y+=y1;
	}
	else
	{
		x=ball_pred_tab[40][0];
		y=ball_pred_tab[40][1];
	}

	for (int i=p_num+10; i>=p_num; i--)
	{
		if (teams[i].tm_notme)
			teams[i].tm_notme--;		// he can't get there!
		else
		{

			if (teams[i].tm_act<=TURN_ACT && ball_poss!=p_num+1)		//player is not busy!
			{
				if ((!(teams[i].int_cnt)) || (not_busy))
				{
					px=teams[i].tm_x;
					py=teams[i].tm_y;

					d=calc_dist(px-x,py-y);

					if (i==(KP_A-1) || i==(KP_B-1))
					{
// Keeper only intercept if half as close as defender!

						if (d*2<closest && closest>prat*2)
						{
							near_guy=i+1;						//This guy is closer!
							closest=d;
						}
					}
					else
					{
						if (d<closest)	
						{
							near_guy=i+1;						//This guy is closer!
							closest=d;
						}
					}
				}
			}
		}
	}
	return(near_guy);
}

/******************************************************************************
*****************************************************************************/

void forward_joystick(match_player *p,float &x,float &y)
{
	x=p->go_txdis;
	y=p->go_tydis;

	if (ux)
	{
// Turn!
		float ta=(PI/12)*ux;
		float nx=x*cos(ta)-y*sin(ta);
		float ny=y*cos(ta)+x*sin(ta);
		x=nx;
		y=ny;
	}
}

/******************************************************************************
 *****************************************************************************/

void get_face_xy(int d,float &x,float &y)
{
	switch(d)
	{
		case(0):
			x=-UNIT;
			y=0;
			break;
	
		case(1):
			x=-DIAG;
			y=DIAG;
			break;

		case(2):
			x=0;
			y=UNIT;
			break;
	
		case(3):
			x=DIAG;
			y=DIAG;
			break;

		case(4):
			x=UNIT;
			y=0;
			break;
	
		case(5):
			x=DIAG;
			y=-DIAG;
			break;

		case(6):
			x=0;
			y=-UNIT;
			break;
	
		case(7):
			x=-DIAG;
			y=-DIAG;
			break;
	}
}

/******************************************************************************
*****************************************************************************/

int get_dir(float x,float y)
{
	int d=0;
	if (y>=0)
	{
		if (x>=0)
		{
			if (x>y)
			{
				if (x>(y*2))
					d=4;
				else
					d=3;
			}
			else
			{
				if (y>(x*2))
 					d=2;
				else
					d=3;
			}
		}
		else
		{
			if (-x>y)
			{
				if (-x>(y*2))
					d=0;
				else
					d=1;
			}
			else
			{
				if (y>(-x*2))
					d=2;
				else
					d=1;
			}
		}
	}
	else
	{
		if (x>=0)
		{
			if (x>-y)
			{
				if (x>(-y*2))
					d=4;
				else
					d=5;
			}
			else
			{
				if (-y>(x*2))
 					d=6;
				else
					d=5;
			}
		}
		else
		{
			if (-x>-y)
			{
				if (-x>(-y*2))
					d=0;
				else
					d=7;
			}
			else
			{
				if (-y>(-x*2))
					d=6;
				else
					d=7;
			}
		}
	}
	return(d);
}

/******************************************************************************
*****************************************************************************/

int angle_of_vis(match_player *player,int x,int y,float d,char cross=FALSE)
{
  	float a;
	float xd=player->tm_xdis;
	float yd=player->tm_ydis;
	float d2=calc_dist(xd,yd);
	xd=xd/d2;
	yd=yd/d2;
	if (cross)
	{
		if (player->tm_player<12)
//	Team A...
		{
 			if ((d/2>(MIN_PASS_DIST+(float)player->tm_pow/3.6)) && (x+player->tm_x>pitch_len-(prat*18)))
				return(TRUE);
			else
				return(FALSE);
		}
		else
//	Team B...
		{
 			if ((d/2>(MIN_PASS_DIST+(float)player->tm_pow/3.6)) && (x+player->tm_x<(prat*18)))
				return(TRUE);
			else
				return(FALSE);
		}
	}
	if (set_piece_on)
		a=((x*setp_kick_x)+(y*setp_kick_y))/d;		// Joystick dir.
	else
		a=((x*xd)+(y*yd))/d;		// facing...

	if (a>=DIAG)
		return(TRUE);
	else
		return(FALSE);
}

/******************************************************************************
*****************************************************************************/

// Creates table of opponents round player within DRIB_DANGER_AREA.

void get_opp_dir_tab(int pnum)
{
	float dist=DRIB_DANGER_AREA+(prat*(((128-teams[pnum-1].tm_flair)/12)-5));
	drib_opps=0;
	int op=1;
	if (pnum<12)
		op=12;
	float x,y,d,dif;

	for (int p=op; p<op+11; p++)
	{
// Vectors for opp. to ball...

		x=(teams[p-1].tm_x-ballx)/teams[p-1].tm_dist;
		y=(teams[p-1].tm_y-bally)/teams[p-1].tm_dist;
		
// Calculate difference range of 2(ahead) to 0(behind)...
		dif=1+((teams[pnum-1].tm_xdis*x)+(teams[pnum-1].tm_ydis*y));
		d=dist/4+(dist*dif*3/8);

		if (teams[p-1].guy_on && teams[p-1].tm_dist<=d && teams[p-1].tm_act<TURN_ACT)
		{
//			if (!(teams[p-1].tm_act==TACKLE_ACT && ((teams[p-1].go_txdis*teams[p-1].go_tydis)<4)))
			{
				opp_dir_tab[drib_opps][0]=teams[p-1].tm_x;
				opp_dir_tab[drib_opps][1]=teams[p-1].tm_y;
				opp_dir_tab[drib_opps][2]=1-(teams[pnum-1].tm_dist/d);	// Attack potential
				drib_opps++;
			}
		}
	}
}

/******************************************************************************
*****************************************************************************/

// Count the number of opponents around player (pnum)!

int opp_around(int x,int y,int pnum)
{
	int op=1;
	int d;
	int opponents=0;
	if (pnum<12)
		op=12;
	for (int p=op; p<op+11; p++)
	{
		if (teams[p-1].guy_on)
		{
			d=calc_dist(teams[p-1].tm_x-x,teams[p-1].tm_y-y);
			if (ball_poss==KP_A || ball_poss==KP_B)
			{
				if (d<=(DANGER_AREA*1.6))
					opponents++;
			}
			else
			{
				if (d<=DANGER_AREA)
					opponents++;
			}
		}
	}
	return(opponents);
}

/******************************************************************************
*****************************************************************************/

// Count the number of opponents around player (pnum)!

// This function specific to keeper passing out...

int kopp_around(int x,int y,int pnum)
{
	int op=1;
	int d;
	int opponents=0;
	if (pnum<12)
		op=12;
	for (int p=op; p<op+11; p++)
	{
		if (teams[p-1].guy_on)
		{
			d=calc_dist(teams[p-1].tm_x-x,teams[p-1].tm_y-y);
			if (d<=(DANGER_AREA*2))
				opponents++;
		}
	}
	return(opponents);
}

/******************************************************************************
*****************************************************************************/

float facing_opp(match_player *player,short opp)
{
	float xd=player->tm_xdis;
	float yd=player->tm_ydis;
	float xo=teams[opp-1].tm_xdis;
	float yo=teams[opp-1].tm_ydis;
	float a=((xo*xd)+(yo*yd));
	return(a);
}

/******************************************************************************
*****************************************************************************/

void player_ints(match_player *player)
{
	if (((player->tm_act==TACKLE_ACT && player->go_cnt>EFFECTIVE_TACK)
		|| (player->tm_act==STEAL_ACT && player->tm_frm>0.4 && player->tm_frm<0.6))
		&& (!dead_ball_cnt) && (!just_scored))
	{
		float x,y,z;
		float dir;
		short chance;
		for (int i=1; i<=players; i++)
		{
			if (teams[i-1].tm_act<=TURN_ACT)
			{
				x=player->tm_x-teams[i-1].tm_x;
				y=player->tm_y-teams[i-1].tm_y;
				z=player->tm_y-teams[i-1].tm_y;
				if ((calc_dist(x,y)<=PLAYER_SIZE) && (z<PLAYER_HEIGHT/3))
				{
// If the tackling player comes in from behind or the side
// then he has a greater chance of bringing the opponent down!
					dir=facing_opp(player,i);
					chance=seed/(dir+2);

					if (chance<(42+((player->tm_pow-teams[i-1].tm_pow)/3)))
					{
// Crunching tackle...
						init_fall(&teams[i-1]);
//						if ((!player->go_step) && ((player_num<12 && i>11) || (player_num>11 && i<12)))
						if (((player_num<12 && i>11) || (player_num>11 && i<12)))
						{
// He is in opposing team!
// He hasn't made contact with ball...
// Therefore a foul has been commited...
							man_down=calc_dist(player->go_txdis,
													 player->go_tydis);

							init_foul(player->tm_player,TRUE);	// pass no. of fouler.

// Man appeals for f.k...
							init_speech(i,SAY_REF,REAL_SPEED);
						}
					}
					else
// Ride over tackle...
						if (player->tm_act!=STEAL_ACT)
							init_jump_act(&teams[i-1],TRUE,TRUE);
				}
			}
		}
	}
}

/*****************************************************************************
*****************************************************************************/

char cross_angle(float xd,float yd,float x,float y)
{
	float a=angle_to_xy(xd,yd,x,y);
	if (a>-0.174 && a<0.707)
// In 55 degree threshold (100 -> 45)...
	{
		if ((xd*y)>(yd*x))
			return(1);
		else
	 		return(2);
	}
	else
		return(0);
}

/*****************************************************************************
*****************************************************************************/

void new_interceptor(int p)
{
	if (p<12)
	{
// Team A...
		if (interceptor_a)
		{
			reset_ideas(&teams[interceptor_a-1]);
		}

		receiver_a=p;
		near_path_a=p;		// Fake passee as nearest!
	}
	else
	{
// Team B...
		if (interceptor_b)
		{
			reset_ideas(&teams[interceptor_b-1]);
		}

		receiver_b=p;
		near_path_b=p;		// Fake passee as nearest!
	}

#ifdef EURO96		// 1-2 Pass.
	if (uf1)
// Force receiver to return ball again to complete 1-2!
	{
		return_12=p;
	}
	else
	{
		return_12=FALSE;
		reselect();			// Can control receiver.
	}
#else
	reselect();
#endif
}

/*****************************************************************************
*****************************************************************************/

int pass_ahead(int ps,float &x,float &y,float &pass_speed,float &end_speed,char cross)
{
	int i=0;
	int t;
	float a,b,s;
	a=x;
	b=y;
	float xd,yd,dd;
	int extra;

	if (ball_limbo_on)
		extra=((ball_limbo_c-teams[ball_limbo_p-1].tm_frm)/teams[ball_limbo_p-1].tm_fstep)-1;
	else
		extra=0;

// Get Targets movement...
	xd=teams[ps-1].go_txdis;
	yd=teams[ps-1].go_tydis;

	for (i=1; i<40; i++)
	{
		a+=xd;
		b+=yd;		// Inc running time

		dd=calc_dist(a,b);

		if (cross || dd>LOW_PASS_DIST || chip_pass)
		{
// In air...
			pass_speed=end_speed+4+(dd*(1-AIR_FRICTION));
			t=(log((end_speed+4)/pass_speed))/(log(AIR_FRICTION));
		}
		else
		{
// On grnd...
			pass_speed=end_speed+(dd*(1-GRND_FRICTION));
			t=(log(end_speed/pass_speed))/(log(GRND_FRICTION));
		}

		if (t<=(i-extra))
			i=1000;						// Intersection with run here...
	}

	if (i>=1000)
	{
// successfull intersection....
		x=a+xd;
		y=b+yd;		// new offsets...

		if ((x+ballx)<0)
			x=prat-ballx;

		if ((x+ballx)>pitch_len)
			x=(pitch_len-prat)-ballx;

		if ((y+bally)<0)
			y=prat-bally;

		if ((y+bally)>pitch_wid)
			y=(pitch_wid-prat)-bally;

		if (dd>LOW_PASS_DIST)
			ball_inair=TRUE;
	}

	return(t);
}

/*****************************************************************************
*****************************************************************************/

void choose_pass(int ps,float &x,float &y,float &pass_speed,float &end_speed,char cross)
{
	float tx,ty,d;
	if (cross)
	{
// Cross it ahead of him towards opponents goal...
		if (ps<12)
// Team B's Goal!
		{
			tx=pitch_len-teams[ps-1].tm_x;
			ty=cntspot_y-teams[ps-1].tm_y;
		}
		else
// Team A's Goal!
		{
			tx=-teams[ps-1].tm_x;
			ty=cntspot_y-teams[ps-1].tm_y;
		}

		if ((tx<=prat && ps<12) || (tx>-prat && ps>11))
		{
// Close to goal-line (straight to him instead!)...
			init_stand_act(&teams[ps-1]);
			int t=pass_ahead(ps,x,y,pass_speed,end_speed,cross);			// Obviously he isn't moving so it will go straight to him!
		}
		else
		{
// Target aimed ahead of player towards goal...
			d=calc_dist(tx,ty);
			x+=tx*prat/d;
			y+=ty*prat/d;
			init_stand_act(&teams[ps-1]);
		  	pass_ahead(ps,x,y,pass_speed,end_speed,cross);
		}
	}
	else
	{
		if (((((ps<12 && teams[ps-1].go_txdis>0) || (ps>11 && teams[ps-1].go_txdis<0))
			 && teams[ps-1].tm_act==RUN_ACT)))
		{
// Pass ahead...
		  	pass_ahead(ps,x,y,pass_speed,end_speed,cross);
		}
		else
		{
			init_stand_act(&teams[ps-1]);
			int t=pass_ahead(ps,x,y,pass_speed,end_speed,cross);			// Obviously he isn't moving so it will go straight to him!
		}
	}
}

/*****************************************************************************
*****************************************************************************/

void pass_ball(int ps,char cross)
{
	inc_pass(ball_poss);

	receiver_a=FALSE;
	receiver_b=FALSE;

	float x,y;
	float d;
	int t;

// Speed of ball at target!
	
	float end_speed;
	float pass_speed;

	if (cross)
	{
		new_shot(ball_poss);		// Treat crosses as shots at goal!
// Hit it harder to cross it in...
		end_speed=7;
	}
	else
		end_speed=5;

	if (ps<=0)
	{
		comm_pass=0;		// Default short pass...

// Must pass but no-one to pass to!
		if (teams[ball_poss-1].tm_act==THROW_ACT)
		{
			x=teams[ball_poss-1].tm_xdis*140;		// Far forward!
			y=teams[ball_poss-1].tm_ydis*140;
		}
		else
		{
			if (!user_controlled)
			{
				switch(must_pass)
				{
					case(NORMAL_PLAY):
						x=teams[ball_poss-1].tm_xdis*10;		// Tap forward!
						y=teams[ball_poss-1].tm_ydis*10;
						end_speed=(actual_spd(&teams[ball_poss-1]))+0.8;
						break;

					case(CORNER_TR):
					case(CORNER_BR):
						x=pitch_len-(prat*15)-ballx;
						y=cntspot_y-bally;
						break;

					case(CORNER_TL):
					case(CORNER_BL):
						x=(prat*15)-ballx;
						y=cntspot_y-bally;
						break;

					case(CENTRE_A):
					case(CENTRE_B):
						x=cntspot_x-ballx;
						y=cntspot_y-bally;
						break;

					case(IF_KICK_A):
					case(IF_KICK_B):
					case(DF_KICK_A):
					case(DF_KICK_B):
						x=setp_kick_x*160;		// Pass forward!
						y=setp_kick_y*160;
						break;
				}
			}
			else
			{
				if (spec_kick_type==SPACT_HPASS || spec_kick_type==SPACT_DPASS
					 || spec_kick_type==SPACT_FPASS || spec_kick_type==SPACT_TEE_UP)
				{
// User set-piece actions which should have been for team-mates...
					if (chip_pass)
					{
		  				x=setp_kick_x*(prat*16);
		  				y=setp_kick_y*(prat*16);
					}
					else
					{
		  				x=setp_kick_x*(prat*14);
		  				y=setp_kick_y*(prat*14);
					}

					d=calc_dist(x,y);
				}

				if (spec_kick_type==SPACT_GRND)
				{
	  				x=setp_kick_x*(f2_down*prat);
	  				y=setp_kick_y*(f2_down*prat);
					d=calc_dist(x,y);
				}
			}
		}
		d=calc_dist(x,y);
	}

	if (ps>0)
	{
		x=teams[ps-1].tm_x-ballx;
		y=teams[ps-1].tm_y-bally;
		d=calc_dist(x,y);

		comm_pass=(int)(d/(LONG_PASS_DIST));

		if (want_pass==ps)
		{
// team-mate cannot stop!
			pass_ahead(ps,x,y,pass_speed,end_speed,cross);
		}
		else
		{
			choose_pass(ps,x,y,pass_speed,end_speed,cross);
		}

		d=calc_dist(x,y);
	}

// Get acuracy offsets!

	float ac1,ac2;

	af_randomize();

	if ((ps>0) && (ps!=KP_A) && (ps!=KP_B) && want_pass!=ps)
// He is passing to an on-the-field player...
	{
// ac1=Direction offset!
		ac1=((rand_range(128-teams[ball_poss-1].tm_ac))*PASS_ACC_ARC)*D2RAD;

// ac2=Power offset!
		ac2=((float)(rand_range(128-teams[ball_poss-1].tm_ac)))/32;

		if (seed&64)
			ac1=-ac1;
	}
	else
	{
		ac1=0;
		ac2=0;
	}

	if (!match_info.GameType)
	{
// Arcade Mode...(Passing is always accurate!)
		ac1=0;
		ac2=0;
	}

	float nx,ny,ox,oy;
	
	ox=x/d;
	oy=y/d;

	nx=(ox*cos(ac1))-(oy*sin(ac1));
	ny=(oy*cos(ac1))+(ox*sin(ac1));

// New Target (x,y)!
	x=nx*d;
	y=ny*d;

	end_speed-=ac2;

	ball_zspin=0;
	ball_xyspin=0;
	full_xyspin=0;
	swerve=FALSE;

	if ((pass_type!=9) && ((ball_in_hands) || (heading_ball)))
	{
// need to throw ball!
		heading_ball=FALSE;
		ball_inair=TRUE;
		pass_speed=end_speed+2+(d*(1-AIR_FRICTION));
		ballxdis=pass_speed*x/d;
		ballydis=pass_speed*y/d;

		t=(log((end_speed+2)/pass_speed))/(log(AIR_FRICTION));
		if (!t)
			t=1;

		if (chip_pass)
// Aim for head...
			ballzdis=((PLAYER_HEIGHT-ballz)/t)+(t/2)*gravity;
		else
			ballzdis=(t/2)*gravity-(ballz/t);

		ball_in_hands=FALSE;
// Stop run!
		if (teams[ball_poss-1].tm_act==RUN_ACT)
			teams[ball_poss-1].go_cnt=0;

		launch_ball(1);			// Set up spin vector.
		cannot_pick_up=-ball_poss;
	}
	else
	{
		if (pass_type==-1 || pass_type==16 || pass_type==17 ||
			chip_pass)
		{
// need to chip ball!
			ball_inair=TRUE;

			if ((ps<=0) && (chip_pass))
// Forced chip forward...
			{
				if (spec_kick_type==SPACT_CHIP)
				{
// Use user power setting...
					ballxdis=setp_bxd;
					ballydis=setp_byd;
					ballzdis=setp_bzd;
				}
				else
				{
					ballxdis=4*x/d;
					ballydis=4*y/d;
					ballzdis=6;
				}
				cannot_pick_up=ball_poss;
			}
			else
			{
// In air to team-mate...
				pass_speed=end_speed+4+(d*(1-AIR_FRICTION));
				t=(log((end_speed+4)/pass_speed))/(log(AIR_FRICTION));

				ballxdis=pass_speed*x/d;
				ballydis=pass_speed*y/d;
				if (t<0.1)
					t=1;

				cannot_pick_up=ball_poss;

				if (chip_pass)
// Aim for head...
					ballzdis=((PLAYER_HEIGHT-ballz)/t)+(t/2)*gravity;
				else
					ballzdis=(t/2)*gravity-(ballz/t);

				if (cross)
				{
					ballzdis=((PLAYER_HEIGHT-6-ballz)/t)+(t/2)*gravity;
				}

				if (ballzdis>14)
					ballzdis=14;
			}

			char angle=0;

			launch_ball(seed&1 ? -1:1);			// Set up spin vector.
		}
		else
		{
			ball_inair=FALSE;
			pass_speed=end_speed+(d*(1-GRND_FRICTION));
			ballxdis=pass_speed*x/d;
			ballydis=pass_speed*y/d;
			cannot_pick_up=ball_poss;

			ballzdis=0;
			ballz=ball_diam/2;
			ball_xyspin=0;
			ball_zspin=0;
		}
	}

	holder_lose_ball();
	must_pass=FALSE;

	if (ps>0)
		new_interceptor(ps);
}

/******************************************************************************
*****************************************************************************/

void make_pass(match_player *player,int p,char cross=FALSE)
{
	kick_type=KT_PASS;
	float sx,sy,sz;
	cross_now=cross;
	receiver=p;
	comm_pass_type=0;
	switch(pass_type)
	{
// Player kick along ground, ball tweens to contact point and is then released...
		case(3):
			init_kick_act(&teams[ball_poss-1],MC_SIDEPASSL,MCC_SIDEPASS);
			break;

		case(2):
			init_kick_act(&teams[ball_poss-1],MC_DIAGBACKL,MCC_DIAGBACK);
			comm_pass_type=1;
			break;

		case(1):
			init_kick_act(&teams[ball_poss-1],MC_BACKHEELL,MCC_BACKHEEL);
			comm_pass_type=1;
			break;

		case(8):
			init_kick_act(&teams[ball_poss-1],MC_DIAGBACKR,MCC_DIAGBACK);
			comm_pass_type=1;
			break;

		case(7):
			init_kick_act(&teams[ball_poss-1],MC_SIDEPASSR,MCC_SIDEPASS);
			break;

		case(6):
			init_kick_act(&teams[ball_poss-1],MC_DIAGPASSR,MCC_DIAGPASS);
			break;

		case(5):
			init_kick_act(&teams[ball_poss-1],MC_PASSL,MCC_PASS);
			break;

		case(4):
			init_kick_act(&teams[ball_poss-1],MC_DIAGPASSL,MCC_DIAGPASS);
			break;

		case(-1):
			init_kick_act(&teams[ball_poss-1],MC_CHIPL,MCC_CHIP);
			comm_pass_type=2;
			break;

		case(16):
			init_kick_act(&teams[ball_poss-1],MC_CROSSL,MCC_CROSS);
			comm_pass_type=2;
			break;

		case(17):
			init_kick_act(&teams[ball_poss-1],MC_CROSSR,MCC_CROSS);
			comm_pass_type=2;
			break;
/*
		case(12):
			init_kick_act(&teams[ball_poss-1],MC_THROWL,MCC_THROWL);
			comm_pass_type=2;
			break;

		case(13):
			init_kick_act(&teams[ball_poss-1],MC_THROWS,MCC_THROWS);
			break;
*/
// Keeper new animation start, ball in limbo until contact...
		case(11):
			init_anim(&teams[ball_poss-1],MC_HALFVOLL);
// Point at which ball leaves hand!
// Calculate current mcap offsets for given direction (newdx,newdy)!
			rotate_offs(MC_HALFVOLL,sx,sy,sz,teams[ball_poss-1].tm_xdis,teams[ball_poss-1].tm_ydis);
			ballx=teams[ball_poss-1].tm_x+sx;
			bally=teams[ball_poss-1].tm_y+sy;
			ballz=teams[ball_poss-1].tm_z+sz;
			ball_limbo(teams[ball_poss-1].tm_player,MCC_HALFVOLL);
			teams[ball_poss-1].tm_limbo=1/MC_HALFVOLL_FS;
			pass_ball(receiver,FALSE);
			comm_pass_type=2;
			break;

		case(10):
			init_anim(&teams[ball_poss-1],MC_THROW);
// Point at which ball leaves hand!
// Calculate current mcap offsets for given direction (newdx,newdy)!
			rotate_offs(MC_THROW,sx,sy,sz,teams[ball_poss-1].tm_xdis,teams[ball_poss-1].tm_ydis);
			ballx=teams[ball_poss-1].tm_x+sx;
			bally=teams[ball_poss-1].tm_y+sy;
			ballz=teams[ball_poss-1].tm_z+sz;
			ball_limbo(teams[ball_poss-1].tm_player,MCC_THROW);
			teams[ball_poss-1].tm_limbo=1/MC_THROW_FS;
			pass_ball(receiver,FALSE);
			break;

		case(9):
			init_anim(&teams[ball_poss-1],MC_ROLL);
// Point at which ball leaves hand!
// Calculate current mcap offsets for given direction (newdx,newdy)!
			rotate_offs(MC_ROLL,sx,sy,sz,teams[ball_poss-1].tm_xdis,teams[ball_poss-1].tm_ydis);
			ballx=teams[ball_poss-1].tm_x+sx;
			bally=teams[ball_poss-1].tm_y+sy;
			ballz=teams[ball_poss-1].tm_z+sz;
			ball_limbo(teams[ball_poss-1].tm_player,MCC_ROLL);
			teams[ball_poss-1].tm_limbo=1/MC_ROLL_FS;
			pass_ball(receiver,FALSE);
			break;

		case(12):
			init_anim(&teams[ball_poss-1],MC_THROWS);
// Point at which ball leaves hand!
// Calculate current mcap offsets for given direction (newdx,newdy)!
			rotate_offs(MC_THROWS,sx,sy,sz,teams[ball_poss-1].tm_xdis,teams[ball_poss-1].tm_ydis);
			ballx=teams[ball_poss-1].tm_x+sx;
			bally=teams[ball_poss-1].tm_y+sy;
			ballz=teams[ball_poss-1].tm_z+sz;
			ball_limbo(teams[ball_poss-1].tm_player,MCC_THROWS);
			teams[ball_poss-1].tm_limbo=1/MC_THROWS_FS;
			pass_ball(receiver,FALSE);
			break;

		case(13):
			init_anim(&teams[ball_poss-1],MC_THROWL);
// Point at which ball leaves hand!
// Calculate current mcap offsets for given direction (newdx,newdy)!
			rotate_offs(MC_THROWL,sx,sy,sz,teams[ball_poss-1].tm_xdis,teams[ball_poss-1].tm_ydis);
			ballx=teams[ball_poss-1].tm_x+sx;
			bally=teams[ball_poss-1].tm_y+sy;
			ballz=teams[ball_poss-1].tm_z+sz;
			ball_limbo(teams[ball_poss-1].tm_player,MCC_THROWL);
			teams[ball_poss-1].tm_limbo=1/MC_THROWL_FS;
			pass_ball(receiver,FALSE);
			break;

// Already in appropriate animation...
		case(15):
// Header!
			fire_ball_off();
			PlayCommentaryMessage(CP_HEAD);
			break;

		case(14):
// Volley!
			fire_ball_off();
			break;
	}
}	

/******************************************************************************
*****************************************************************************/

void dribble_dir(match_player *player,float &xd,float &yd)
{
	float x,y,d;
	float rate=actual_spd(player);
	int i;
	char go_that_way=FALSE;
	char a=((seed<64) ? TRUE:FALSE);

	float sina=sin(0.174);		// approx. 10 degrees!
	float cosa=cos(0.174);

	float xd1=xd;
	float yd1=yd;

	float xd2=xd;
	float yd2=yd;

	float xo,yo,dif;

	int cnt=0;

	while((!go_that_way) && (drib_opps))
	{

// Coords of future ball.
		x=ballx+(xd*DRIB_DANGER_AREA/4);
		y=bally+(yd*DRIB_DANGER_AREA/4);

		go_that_way=TRUE;

		for (i=0; i<drib_opps; i++)
		{
			xo=x-opp_dir_tab[i][0];
			yo=y-opp_dir_tab[i][1];		// offset to future ball!

			d=calc_dist(xo,yo);

			dif=(player->tm_xdis*xo/d)+(player->tm_ydis*yo/d);
			d=d*(2-dif);

			if (d<DRIB_DANGER_AREA/2)
			{
				go_that_way=FALSE;
				break;
			}
		}

		if	((x<16) || (x>pitch_len-16) || (y<16) || (y>pitch_wid-16) || (!go_that_way))
		{
			go_that_way=FALSE;
			if (a)
			{
				xd=(xd1*cosa)-(yd1*sina);
				yd=(yd1*cosa)+(xd1*sina);
				xd1=xd;
				yd1=yd;
				a=!a;
			}
			else
			{
				xd=(xd2*cosa)+(yd2*sina);
				yd=(yd2*cosa)-(xd2*sina);
				xd2=xd;
				yd2=yd;
				a=!a;
			}

			if (cnt++==36)
			{
// No-where to go, so go toward centre!
				xd=cntspot_x-ballx;
				yd=cntspot_y-bally;
				d=calc_dist(xd,yd);
				xd=xd/d;
				yd=yd/d;
				must_pass=TRUE;
				break;
			}
		}
	}
}

/******************************************************************************
*****************************************************************************/
/*
int omake_run_a(match_player *player)
{
	if (player->tm_y>=cntspot_y)
	{
// DIR 4
		if (ballx<pitch_len-32)
		{
			if ((opp_dir_tab[3]>=0) && (opp_dir_tab[5]>=0))
			{
				if (!opp_dir_tab[4])
					return(4);
			}
		}

// DIR 5
		if ((ballx<pitch_len-32) && (bally>32))
		{
			if ((opp_dir_tab[6]>=0) && (opp_dir_tab[4]>=0))
			{
				if (!opp_dir_tab[5])
					return(5);
			}
		}

// DIR 3
		if ((bally<pitch_wid-32) && (ballx<pitch_len-32))
		{
			if ((opp_dir_tab[2]>=0) && (opp_dir_tab[4]>=0))
			{
				if (!opp_dir_tab[3])
					return(3);
			}
		}

// DIR 6
		if (bally>32)
		{
			if ((opp_dir_tab[7]>=0) && (opp_dir_tab[5]>=0))
			{
				if (!opp_dir_tab[6])
					return(6);
			}
		}

// DIR 2
		if (bally<pitch_wid-32)
		{
			if ((opp_dir_tab[3]>=0) && (opp_dir_tab[1]>=0))
			{
				if (!opp_dir_tab[2])
					return(2);
			}
		}

// DIR 7
		if ((bally>32) && (ballx>32))
		{
			if ((opp_dir_tab[0]>=0) && (opp_dir_tab[6]>=0))
			{
				if (!opp_dir_tab[7])
					return(7);
			}
		}

// DIR 1
		if ((bally<pitch_wid-32) && (ballx>32))
		{
			if ((opp_dir_tab[2]>=0) && (opp_dir_tab[5]>=0))
			{
				if (!opp_dir_tab[1])
					return(1);
			}
		}

// DIR 0
		if (ballx>32)
		{
			if ((opp_dir_tab[1]>=0) && (opp_dir_tab[7]>=0))
			{
				if (!opp_dir_tab[0])
					return(0);
			}
		}
	}
	else
	{
// DIR 4
		if (ballx<pitch_len-32)
		{
			if ((opp_dir_tab[3]>=0) && (opp_dir_tab[5]>=0))
			{
				if (!opp_dir_tab[4])
					return(4);
			}
		}

// DIR 3
		if ((bally<pitch_wid-32) && (ballx<pitch_len-32))
		{
			if ((opp_dir_tab[2]>=0) && (opp_dir_tab[4]>=0))
			{
				if (!opp_dir_tab[3])
					return(3);
			}
		}

// DIR 5
		if ((ballx<pitch_len-32) && (bally>32))
		{
			if ((opp_dir_tab[6]>=0) && (opp_dir_tab[4]>=0))
			{
				if (!opp_dir_tab[5])
					return(5);
			}
		}

// DIR 2
		if (bally<pitch_wid-32)
		{
			if ((opp_dir_tab[3]>=0) && (opp_dir_tab[1]>=0))
			{
				if (!opp_dir_tab[2])
					return(2);
			}
		}

// DIR 6
		if (bally>32)
		{
			if ((opp_dir_tab[7]>=0) && (opp_dir_tab[5]>=0))
			{
				if (!opp_dir_tab[6])
					return(6);
			}
		}

// DIR 1
		if ((bally<pitch_wid-32) && (ballx>32))
		{
			if ((opp_dir_tab[2]>=0) && (opp_dir_tab[5]>=0))
			{
				if (!opp_dir_tab[1])
					return(1);
			}
		}

// DIR 7
		if ((bally>32) && (ballx>32))
		{
			if ((opp_dir_tab[0]>=0) && (opp_dir_tab[6]>=0))
			{
				if (!opp_dir_tab[7])
					return(7);
			}
		}

// DIR 0
		if (ballx>32)
		{
			if ((opp_dir_tab[1]>=0) && (opp_dir_tab[7]>=0))
			{
				if (!opp_dir_tab[0])
					return(0);
			}
		}
	}

// Go to right corners...
	int y;
	int x=(pitch_len-(prat*5))-ballx;
	if (bally>cntspot_y)
		y=(pitch_wid-(prat*5))-bally;
	else
		y=((prat*5))-bally;
	return(get_dir(x,y));
}
*/
/******************************************************************************
*****************************************************************************/
/*
int make_run_b(match_player *player)
{
	if (player->tm_y>=cntspot_y)
	{
// DIR 0
		if (ballx>32)
		{
			if ((opp_dir_tab[1]>=0) && (opp_dir_tab[7]>=0))
			{
				if (!opp_dir_tab[0])
					return(0);
			}
		}

// DIR 7
		if ((bally>32) && (ballx>32))
		{
			if ((opp_dir_tab[0]>=0) && (opp_dir_tab[6]>=0))
			{
				if (!opp_dir_tab[7])
					return(7);
			}
		}

// DIR 1
		if ((bally<pitch_wid-32) && (ballx>32))
		{
			if ((opp_dir_tab[2]>=0) && (opp_dir_tab[5]>=0))
			{
				if (!opp_dir_tab[1])
					return(1);
			}
		}

// DIR 6
		if (bally>32)
		{
			if ((opp_dir_tab[7]>=0) && (opp_dir_tab[5]>=0))
			{
				if (!opp_dir_tab[6])
					return(6);
			}
		}

// DIR 2
		if (bally<pitch_wid-32)
		{
			if ((opp_dir_tab[3]>=0) && (opp_dir_tab[1]>=0))
			{
				if (!opp_dir_tab[2])
					return(2);
			}
		}

// DIR 5
		if ((ballx<pitch_len-32) && (bally>32))
		{
			if ((opp_dir_tab[6]>=0) && (opp_dir_tab[4]>=0))
			{
				if (!opp_dir_tab[5])
					return(5);
			}
		}

// DIR 3
		if ((bally<pitch_wid-32) && (ballx<pitch_len-32))
		{
			if ((opp_dir_tab[2]>=0) && (opp_dir_tab[4]>=0))
			{
				if (!opp_dir_tab[3])
					return(3);
			}
		}

// DIR 4
		if (ballx<pitch_len-32)
		{
			if ((opp_dir_tab[3]>=0) && (opp_dir_tab[5]>=0))
			{
				if (!opp_dir_tab[4])
					return(4);
			}
		}
	}
	else
	{
// DIR 0
		if (ballx>32)
		{
			if ((opp_dir_tab[1]>=0) && (opp_dir_tab[7]>=0))
			{
				if (!opp_dir_tab[0])
					return(0);
			}
		}

// DIR 1
		if ((bally<pitch_wid-32) && (ballx>32))
		{
			if ((opp_dir_tab[2]>=0) && (opp_dir_tab[5]>=0))
			{
				if (!opp_dir_tab[1])
					return(1);
			}
		}

// DIR 7
		if ((bally>32) && (ballx>32))
		{
			if ((opp_dir_tab[0]>=0) && (opp_dir_tab[6]>=0))
			{
				if (!opp_dir_tab[7])
					return(7);
			}
		}

// DIR 2
		if (bally<pitch_wid-32)
		{
			if ((opp_dir_tab[3]>=0) && (opp_dir_tab[1]>=0))
			{
				if (!opp_dir_tab[2])
					return(2);
			}
		}

// DIR 6
		if (bally>32)
		{
			if ((opp_dir_tab[7]>=0) && (opp_dir_tab[5]>=0))
			{
				if (!opp_dir_tab[6])
					return(6);
			}
		}

// DIR 3
		if ((bally<pitch_wid-32) && (ballx<pitch_len-32))
		{
			if ((opp_dir_tab[2]>=0) && (opp_dir_tab[4]>=0))
			{
				if (!opp_dir_tab[3])
					return(3);
			}
		}

// DIR 5
		if ((ballx<pitch_len-32) && (bally>32))
		{
			if ((opp_dir_tab[6]>=0) && (opp_dir_tab[4]>=0))
			{
				if (!opp_dir_tab[5])
					return(5);
			}
		}

// DIR 4
		if (ballx<pitch_len-32)
		{
			if ((opp_dir_tab[3]>=0) && (opp_dir_tab[5]>=0))
			{
				if (!opp_dir_tab[4])
					return(4);
			}
		}
	}

// Go to left corners...
	int y;
	int x=(prat*5)-ballx;
	if (bally>cntspot_y)
		y=(pitch_wid-(prat*5))-bally;
	else
		y=((prat*5))-bally;
	return(get_dir(x,y));
}

*/

/******************************************************************************
*****************************************************************************/

void avoid_boundary(match_player *player)
{
// Just run toward opponents goal...
	float x;
	float y=cntspot_y;
	if (player->tm_player<12)
// Goal B...
		x=pitch_len;
	else
// Goal A...
		x=0;

	init_run_act(player,x,y,TRUE);
	action="Dribble";
}

/******************************************************************************
*****************************************************************************/

void go_dribble(match_player *player,float x,float y)
{
	x=player->tm_x+(x*500);
	y=player->tm_y+(y*500);

// Make target (x,y) greater than intention range!

	init_run_act(player,x,y,TRUE);
	action="Dribble";
}

/******************************************************************************
*****************************************************************************/

void make_run(match_player *player)
{
	float x,y,px;

	if (player->tm_player<12)
// Team A
	{
		px=player->tm_x-(pitch_len-prat*10);
		if (px>0)
		{
			if (px<prat*10)
				x=cos(px*PI/(prat*20));
			else
				x=0;

			y=sqrt(1-(x*x));

			if (player->tm_y>cntspot_y)
				y=-y;

		}
		else
		{
			x=1;
			y=0;
		}
		get_opp_dir_tab(player->tm_player);
		dribble_dir(player,x,y);
		go_dribble(player,x,y);
	}
	else			
// Team B
	{
		px=(prat*10)-player->tm_x;
		if (px>0)
		{
			if (px<prat*10)
				x=-cos(px*PI/(prat*20));
			else
				x=0;

			y=sqrt(1-(x*x));

			if (player->tm_y>cntspot_y)
				y=-y;

		}
		else
		{
			x=-1;
			y=0;
		}
		get_opp_dir_tab(player->tm_player);
		dribble_dir(player,x,y);
		go_dribble(player,x,y);
	}
	reset_ideas(player);
	player->int_move=I_DRIBBLE;
	player->int_cnt=18-(player->tm_flair/8);
	player->go_cnt=19-(player->tm_flair/8);
	
// Where will he be at end of run!
	x=player->tm_x+(player->go_txdis*player->go_cnt);
	y=player->tm_y+(player->go_tydis*player->go_cnt);
	if (x>pitch_len || x<0 || y<0 || y>pitch_wid)
	{
// Running off pitch!!!
		avoid_boundary(player);
	}
}

/******************************************************************************
*****************************************************************************/

int run_decide(match_player *player)
{
	int opps=(player->tm_flair)-(opponents_near_holder*16);
	if (opps<=0)
		opps=MIN_RUN_PROB;
	if (seed<opps)
		return(TRUE);
	else
		return(FALSE);
}	

/******************************************************************************
*****************************************************************************/

void make_punt(match_player *player)
{
	if (ball_in_hands && (player->tm_player==KP_A || player->tm_player==KP_B))
	{
		punt_ball(player);
	}
	else
	{
		kick_type=KT_PUNT;
		pass_type=100;
		init_kick_act(player,MC_SHOOTL,MCC_SHOOT);
	}
}

/*****************************************************************************
*****************************************************************************/

void punt_ball(match_player *player)
{
	inc_pass(ball_poss);

	receiver_a=FALSE;
	receiver_b=FALSE;

	cannot_pick_up=ball_poss;
	must_punt=FALSE;
	char inh=ball_in_hands;
	ball_inair=TRUE;
	int r=rand_range(129-player->tm_ac);

	ballxdis=player->tm_xdis*(6+player->tm_pow/8);
	ballydis=player->tm_ydis*(6+player->tm_pow/8);
	if (heading_ball==2)
		ballzdis=4;				// Diving Header!
	else
		if (heading_ball==1)
			ballzdis=6;			// Standing or jumping header!
		else
			if (heading_ball==3)
				ballzdis=8;
			else
			{
				if (player->tm_player!=KP_A && player->tm_player!=KP_B)
					ballzdis=10;		// Kick!
				else
					ballzdis=12;		// Kick!
			}

	action="Punt";
	new_shot(player->tm_player);							// Treat as shot just in case!

	if (inh && (player->tm_player==KP_A || player->tm_player==KP_B))
	{
		init_anim(player,MC_KICKOUT);
// Kick out ball from hands!
// Calculate current mcap offsets for given direction (newdx,newdy)!
		float sx,sy,sz;
		rotate_offs(MC_KICKOUT,sx,sy,sz,player->tm_xdis,player->tm_ydis);
		ballx=player->tm_x+sx;
		bally=player->tm_y+sy;
		ballz=player->tm_z+sz;
		ball_limbo(player->tm_player,MCC_KICKOUT);
		player->tm_limbo=1/MC_KICKOUT_FS;
		launch_ball(1);			// Set up spin vector.
	}
	holder_lose_ball();
}

/******************************************************************************
*****************************************************************************/

int punt_decide(match_player *player)
{
	float x,y,x_factor;
	int def;

	x=player->tm_xdis;
	y=player->tm_ydis;

	if (player->tm_player>11)
	{
		if (x<0 && (ballx<pitch_len && ballx>cntspot_x) && ((seed<-(x*128)) || must_punt))
			def=ballx-cntspot_x;
		else
			return(FALSE);
	}
	else
	{
		if (x>0 && (ballx>0 && ballx<cntspot_x) && ((seed<(x*128)) || must_punt))
			def=cntspot_x-ballx;
		else
			return(FALSE);
	}

	if (def>(cntspot_x-(10*prat)))
		def+=128;

//	if (((user_player1==player->tm_player) || (user_player2==player->tm_player)) && (def>prat*20))
	if (((player->control) && (def>prat*20)) || must_punt)
		def=128*4;
// User must punt!

	if (def/3>seed || (first_time_it && (def*((float)player->tm_cont/64)>seed)))
// His position is defensive.
	{
		int opps=(opponents_near_holder*40)-(player->tm_flair);
		if (opps<MIN_PUNT_PROB)
			opps=MIN_PUNT_PROB;

		if (user_controlled)
// User must punt!
			opps=128;

// Facing away from goal would help...
		if (player->tm_player<12)
			x_factor=(1+x)/2;
		else
			x_factor=-(x-1)/2;

		if (((seed<opps*x_factor) && (x_factor>0.5)) || must_punt)
			return(TRUE);
	}

	return(FALSE);
}

/******************************************************************************
*****************************************************************************/

int head_punt_decide(match_player *player)
{
	float x,y;
	int def;

	x=player->tm_xdis;
	y=player->tm_ydis;

	if (player->tm_player>11)
	{
		if (x<0)
			def=ballx-cntspot_x;
		else
			return(FALSE);
	}
	else
	{
		if (x>0)
			def=cntspot_x-ballx;
		else
			return(FALSE);
	}

	if (def>(cntspot_x-(10*prat)))
		def+=128;

	if (def/4>seed)
// His position is defensive.
	{
		cannot_pick_up=-player->tm_player;
		holder_lose_ball();
		ball_inair=TRUE;
		ballxdis=(((float)(player->tm_pow))/32.0)*x+(x*6);
		ballydis=0;
		ballzdis=10;

		action="Punt";
		init_anim(player,MC_S_HEAD);

		launch_ball(1);			// Set up spin vector.

		play_fx(PS_HARDHEAD,ballx,bally);

		return(TRUE);
	}
	return(FALSE);
}

/******************************************************************************
*****************************************************************************/

float get_power()
{
	return ((float)(setp_power+16)/2);
}

/******************************************************************************
*****************************************************************************/

float get_traj()
{
	return ((float)setp_hgt/3);
}

/******************************************************************************
*****************************************************************************/

void aim_shot_at_goal(match_player *player,float &xoff,float &yoff,int rng)
{
	float x,y,d;
	float gx,gy,area;
	int side;

	if (player->control && pass_type==-1)
	{
// User selects direction!
		x=player->tm_xdis;
		y=player->tm_ydis;

		float d=calc_dist(x*128,y*128);
		xoff=(x*rng*128)/d;
		yoff=(y*rng*128)/d;
	}
	else
	{
// Auto direction select based on (accuracy)!

		int keeper;
		if (player->tm_player<12)
		{
			keeper=12;
			gx=pitch_len;
		}
		else
		{
			keeper=1;
			gx=0;
		}

// get offset to keeper (x,y)!
		x=teams[keeper-1].tm_x-ballx;
		y=teams[keeper-1].tm_y-bally;

// get offset to goal line through keeper (gx,gy)!

		gx=gx-ballx;
		gy=y*gx/x;

		area=gy+bally-cntspot_y;

		if (area>0)
// More area above keeper!
		{
			if ((player->tm_flair/2)+63>seed)
// Aim above!
			{
				area=(cntspot_y+area)-top_post_y;
				side=-1;
			}
			else
// Aim below!
			{
				area=0;			// Doesn't aim for large gap!
				side=1;
			}
		}
		else
// More area below keeper!
		{
			if ((player->tm_flair/2)+63>seed)
// Aim below!
			{
				area=bot_post_y-(cntspot_y+area);
				side=1;
			}
			else
// Aim above!
			{
				area=0;			// Doesn't aim for large gap!
				side=-1;
			}
		}

		xoff=gx;

// Calculate Accuracy offset!
		int acc_off=(seed*(8+(128-player->tm_ac)))/128;
		if (seed&4)
			acc_off=-(acc_off*rng/(20.0*prat));
		else
			acc_off=(acc_off*rng/(20.0*prat));

// Now. Direct at chosen target.
		if (side>0)
			yoff=bot_post_y-bally-16+acc_off;
		else
			yoff=top_post_y-bally+16+acc_off;
	}

// Shot Speed...
	int shot_var=seed;
	af_randomize();
	shot_var=(shot_var+seed)/2;			// Favour 64.

	shot_speed=6+(4*rng/(prat*60))+(9.0*(player->tm_pow+shot_var)/150);

	if (pass_type>0 && pass_type<5 && pass_type>5)
// Just a tap in...
		shot_speed/=2;


// Initialise swerve on ball!
	af_randomize();
	ball_zspin=0;
//	full_zspin=(float)player->tm_ac/(rng-sqrt(rng*4));
	swerve=0;
	spin_ball=0;
	max_sw_factor=0;

#ifdef EURO96
	if (rng>=10.0*prat && !user_controlled && !penalty_shot)
#else
	if ((rng>=10.0*prat) && (!user_controlled))
#endif
	{
		af_randomize();
		full_xyspin=(float)(seed)/128*MAX_XY_CSW*player->tm_flair/128;
		full_zspin=((float)(seed)/128*MAX_Z_CSW*player->tm_flair/128);
		spin_ball=0;
		float d=calc_dist(xoff,yoff);
		
		af_randomize();

// Time to reach (xoff,yoff)...
		float t=(d/shot_speed*(1-AIR_FRICTION));
  		if (t>=1)
  			t=0.9998;
  		t=(log(1.0-t))/(log(AIR_FRICTION));	//	How long to go (d) dist!

		if (xoff<0)
// Going Left
		{
			if (side<0)
// Left top.
			{
				if (xoff<yoff)
					swerve=-1;
				else
					swerve=1;
			}
// Left bot.
			else
			{
				if (xoff<yoff)
					swerve=1;
				else
					swerve=-1;
			}
		}
		else
// Going Right
		{
			if (side<0)
// Right top.
			{
				if (xoff>yoff)
					swerve=1;
				else
					swerve=-1;
 			}
// Right bot.
			else
			{
				if (xoff>yoff)
					swerve=-1;
				else
					swerve=1;
			}
		}
// Calculate Offset swerve angle...
		float a=0;
		for (int n=1; n<=t; n++)
		{
			a+=full_xyspin*(SW_HOLD_FACTOR/(SW_HOLD_FACTOR+n));
		}

		a=(a/2.2)+(d/4800);
		x=xoff/d;
		y=yoff/d;

		if (swerve<0)
		{
			xoff=d*((x*cos(a))-(y*sin(a)));
			yoff=d*((y*cos(a))+(x*sin(a)));
		}
		else
		{
			xoff=d*((x*cos(a))+(y*sin(a)));
			yoff=d*((y*cos(a))-(x*sin(a)));
		}

		ballzdis=7.2+(rng/180)+(((float)seed/64)*(128-player->tm_ac)/128)
				+((float)(full_zspin)/2);
		spin_cnt=((ballzdis/gravity))+(ABS(full_zspin));
	}
	else
	{
		if (newk_shot)
		{
			shot_speed=get_power();
			ballzdis=get_traj();
			xoff=player->tm_xdis*10;
			yoff=player->tm_ydis*10;
			ballxdis=xoff;
			ballydis=yoff;
		}
		else
		{
			if (drive_shot)
			{
				shot_speed+=5;
				ballzdis=7-(shot_speed/10);
			}
			else
			{
				if ((area>prat*6) && (rng<prat*15))
// Goal-keeper has left a large gap and attacker is close in!
					ballzdis=1.8+(rng/180)+(((float)seed/64)*(128-player->tm_ac)/128);		// Place it low!
				else
					ballzdis=5.2+(rng/180)+(((float)seed/64)*(128-player->tm_ac)/128);
			}
		}
	}

	if (user_controlled)
	{
		if (drive_shot)
			after_touch_on=FALSE;
		else
			after_touch_on=user_controlled;

		full_xyspin=MAX_XY_USW*player->tm_flair/128;
		full_zspin=MAX_Z_USW*player->tm_flair/128;
		d=calc_dist(ballxdis,ballydis);
		shoot_x=ballxdis/d;
		shoot_y=ballydis/d;		// Shoot direction vectors(for after-touch).
	}
	spin_cnt=0;
}

/******************************************************************************
*****************************************************************************/

void make_shoot(match_player *player)
{
	kick_type=KT_SHOOT;
	switch(pass_type)
	{
// Straight-forward shot!
		case(-1):
			init_kick_act(player,MC_SHOOTL,MCC_SHOOT);
			break;

// Player kick along ground, ball tweens to contact point and is then released...
		case(3):
			init_kick_act(&teams[ball_poss-1],MC_SIDEPASSL,MCC_SIDEPASS);
			break;

		case(2):
			init_kick_act(&teams[ball_poss-1],MC_DIAGBACKL,MCC_DIAGBACK);
			break;

		case(1):
			init_kick_act(&teams[ball_poss-1],MC_BACKHEELL,MCC_BACKHEEL);
			break;

		case(8):
			init_kick_act(&teams[ball_poss-1],MC_DIAGBACKR,MCC_DIAGBACK);
			break;

		case(7):
			init_kick_act(&teams[ball_poss-1],MC_SIDEPASSR,MCC_SIDEPASS);
			break;

		case(6):
			init_kick_act(&teams[ball_poss-1],MC_DIAGPASSR,MCC_DIAGPASS);
			break;

		case(5):
			init_kick_act(&teams[ball_poss-1],MC_PASSL,MCC_PASS);
			break;

		case(4):
			init_kick_act(&teams[ball_poss-1],MC_DIAGPASSL,MCC_DIAGPASS);
			break;
	}
}

/******************************************************************************
*****************************************************************************/

void shoot_ball(match_player *player)
{
	receiver_a=FALSE;
	receiver_b=FALSE;

	if (say_names)
	{
		if (!ball_poss)
			PlayTeamSample(real_player(last_touch),2);
		else
			PlayTeamSample(real_player(ball_poss),2);
	}

// Fire shot!
	float goal_x;
	if (ball_poss<=11)
		goal_x=pitch_len;
	else
		goal_x=0;
	float xoff=goal_x-ballx;
	float yoff=cntspot_y-bally;
	float range=calc_dist(xoff,yoff);
	if (range<1)
		range=1;

	holder_lose_ball();
	ball_inair=TRUE;
	new_shot(player->tm_player);
	real_shot=TRUE;
	af_randomize();

	aim_shot_at_goal(player,xoff,yoff,range);

	if (heading_ball==2)
		ballzdis=ballzdis*.5;				// Diving Header!
	else
		if (heading_ball==3)
			ballzdis=1;

	if (ballzdis>0.6)
		ball_inair=TRUE;

	float d=calc_dist(xoff,yoff);

	ballxdis=shot_speed*xoff/d;
	ballydis=shot_speed*yoff/d;

	action="Shoot";
	cannot_pick_up=player->tm_player;

	drive_shot=FALSE;
	newk_shot=FALSE;
	launch_ball(0);			// Set up spin vector.
	inc_shot(player->tm_player);
	user_scorer=player->control;
}

/******************************************************************************
*****************************************************************************/

int shoot_decide(match_player *player)
{
	flag=FALSE;
	float goal_x;
	if (ball_poss<=11)
		goal_x=pitch_len;
	else
		goal_x=0;
	float xoff=goal_x-ballx;
	float yoff=cntspot_y-bally;
	int range=calc_dist(xoff,yoff);
	if (range<1)
		range=1;

	if (player->tm_srng)
	{
		if (user_controlled)
		{
// Big shot!
			flag=TRUE;			// in shooting range!
			pass_type=-1;
		}
		else
		{
			if (plr_facing_goal(xoff,yoff,player))
			{
// Big shot!
				flag=TRUE;			// in shooting range!
				pass_type=-1;
			}
			else
			{
				pass_type=in_kicking_range(player,xoff,yoff);
				if (user_controlled && pass_type==5)
					pass_type=-1;

				if (!pass_type)
					flag=FALSE;
				else
					flag=TRUE;			// any dir shot.
			}
		}
	}

	if (flag)
	{
// He's in range!

		if ((!user_controlled) && (!must_shoot))
		{
			int opps=(10000/range)+(opponents_near_holder*(16+((128-player->tm_flair)/4)))-(16+(player->tm_flair/3));
			if (opps<MIN_SHOOT_PROB)
				opps=MIN_SHOOT_PROB;
			if (seed>opps && !first_time_it)
				return(FALSE);
		}
		return(TRUE);
	}

	if (player->tm_leave)				// He cannot touch ball again!
		must_pass=TRUE;

	return(FALSE);
}

/******************************************************************************
*****************************************************************************/

int head_shoot_decide(match_player *player)
{
	flag=FALSE;
	float goal_x;

	if (player->tm_player<=11)
		goal_x=pitch_len;
	else
		goal_x=0;

	float xoff=goal_x-ballx;
	float yoff=cntspot_y-bally;
	int range=calc_dist(xoff,yoff);
	if (range<1)
		range=1;

	if (in_header_rng)
	{
// He's in range!

		int opps=(5000/range)+(opponents_near_holder*32);
		if (opps<MIN_SHOOT_PROB)
			opps=MIN_SHOOT_PROB;
		if (seed>opps)
			return(FALSE);

// Fire shot!
		cannot_pick_up=-ball_poss;
		holder_lose_ball();
		ball_inair=TRUE;
		new_shot(player->tm_player);
		aim_shot_at_goal(player,xoff,yoff,range);
		float d=calc_dist(xoff,yoff);
	 	stop_ball_spin();

		ballzdis=ballzdis-1.4;
		ballxdis=(xoff*(12+(player->tm_pow)/4))/(d*3.4);
		ballydis=(yoff*(12+(player->tm_pow)/4))/(d*3.4);

		init_anim(player,MC_S_HEAD);

		launch_ball(0);			// Set up spin vector.

		play_fx(PS_HARDHEAD,ballx,bally);
		return(TRUE);
	}
	return(FALSE);
}

/******************************************************************************
*****************************************************************************/

int sort_less_than(const void *op1, const void *op2)
{
	const int p1=*(const int *)op1;
	const int p2=*(const int *)op2;
	return(p1-p2);
}

/******************************************************************************
*****************************************************************************/

int sort_greater_than(const void *op1, const void *op2)
{
	const int p1=*(const int *)op1;
	const int p2=*(const int *)op2;
	return(p2-p1);
}

/******************************************************************************
*****************************************************************************/

int sort_soonest(const void *op1, const void *op2)
{
	const short p1=*(const short *)op1;
	const short p2=*(const short *)op2;
	return(p1-p2);
}

/******************************************************************************
*****************************************************************************/

float kicking_dist(match_player *player,float x,float y,float d)
{
// Calculate back-heel distance...
	float dist=MIN_PASS_DIST+(float)player->tm_pow/3.6;

// Calculate difference range of 2(ahead) to 1(behind)...
	float dif=(player->tm_xdis*x/d)+(player->tm_ydis*y/d);
	float kd=dist*(2.0+dif)/2;
	return(kd);
}

/******************************************************************************
*****************************************************************************/

int in_kicking_range(match_player *player,float x,float y)
{
	float d=calc_dist(x,y);
	x=x/d;
	y=y/d;

// Calculate back-heel distance...
	float dist=MIN_PASS_DIST+(float)player->tm_pow/3.6;

// Calculate difference range of 2(ahead) to 1(behind)...
	float dif=(player->tm_xdis*x)+(player->tm_ydis*y);
	float kd=dist*(1.5+(dif/2));

	if (dif>KICK_AHEAD_ANG)
	{
// Straight ahead...
		if (d>dist*4)
			return(0);
		else
			if (d>dist*2)
				return(-1);
			else
				return(5);
	}
	else
	{
// Different dir...
		if (d>kd)
			return(FALSE);
		else
		{
			float nx=(x*player->tm_xdis)+(y*player->tm_ydis);
			float ny=(y*player->tm_xdis)-(x*player->tm_ydis);
			return(1+get_dir(nx,ny));
		}
	}
}

/******************************************************************************
*****************************************************************************/

int can_i_pass(match_player *player)
{
	int p=pass_type;
	if (p>6 && p<9)
		p=p-6;
	else
		if (p>0 && p<4)
			p=4-p;
		else
			return(pass_type);		// Forward or diagonal pass requires no special ability!

	if (player->tm_flair>(p*seed*0.5))
		return(pass_type);			// Skillfull enough to see move!
	else
		return(FALSE);
}

/******************************************************************************
*****************************************************************************/

int pass_decide(match_player *player,char cross=FALSE)
{
	char angle;
	int passee_tab[10][3];
	int passees=0;
	int vm;
	if ((!player->tm_act==THROW_ACT) && (ball_inair))
		vm=VISION_MULT*2/3;
	else
		vm=VISION_MULT;

	int x,y,d,t;
	if (player->tm_player>11)
		t=22-1;		  		//team B
	else
		t=11-1;				//team A

/************/

	if (want_pass)
	{
// Try guy shouting for pass...
		int i=want_pass-1;

		if ((ball_poss!=KP_A && ball_poss!=KP_B)
			 || !kopp_around(teams[want_pass-1].tm_x,teams[want_pass-1].tm_y,want_pass))
		{
			if ((teams[i].control)
				|| (plr_facing(teams[i].tm_x-ballx,teams[i].tm_y-bally,player))
				|| (set_piece_on && player->tm_act!=THROW_ACT))
			{
				x=teams[i].tm_x-ballx;
				y=teams[i].tm_y-bally;
				d=calc_dist(x,y);
				if ((ball_in_hands) && (d<30.0*prat))
// In throwing range!
				{
					passee_tab[passees][1]=i+1;
					passee_tab[passees++][2]=pass_type;
// Add prospective passee!
 				}
				else
				{
					pass_type=in_kicking_range(player,x,y);
					pass_type=can_i_pass(player);

					if ((pass_type) && (!ball_in_hands))
// Can kick that distance...
					{
						passee_tab[passees][1]=i+1;
						passee_tab[passees++][2]=pass_type;
// Add prospective passee!
					}
					else
					{
						if (cross && !ball_in_hands && 
							d<=(player->tm_vis*vm*1.4) && d>(prat*8))
						{
							if ((ball_poss<12 && (teams[i].tm_x)>pitch_len-(prat*18))
								|| (ball_poss>11 && (teams[i].tm_x)<prat*18))
							{
// In eighteen yard box!
								angle=cross_angle(teams[ball_poss-1].tm_xdis,
													teams[ball_poss-1].tm_ydis,x,y);
			
								if (angle==1)
// Kicking at 90 degrees left...
								{
									pass_type=16;
									passee_tab[passees][1]=i+1;
									passee_tab[passees++][2]=pass_type;
								}
								else
								{
									if (angle==2)
// Kicking at 90 degrees right...
									{
										pass_type=17;
										passee_tab[passees][1]=i+1;
										passee_tab[passees++][2]=pass_type;
									}
								}
							}
						}
					}
				}
			}
		}
	}

/************/

	for (int i=t; i>t-11; i--)
	{
		if (player->tm_player!=i+1)
// Not man on ball!
		{
			if ((ball_poss!=KP_A && ball_poss!=KP_B)
				 || !kopp_around(teams[i].tm_x,teams[i].tm_y,i))
			{
				if ((teams[i].tm_act<=TURN_ACT) && (teams[i].guy_on>0) && (want_pass-1!=i))
// Not Busy!
				{
					x=teams[i].tm_x-ballx;
					y=teams[i].tm_y-bally;
					d=calc_dist(x,y);
					pass_type=in_kicking_range(player,x,y);
					pass_type=can_i_pass(player);

					if ((pass_type && !ball_in_hands) || ((ball_in_hands) && (d<20.0*prat)))
// Can kick reach him...
					{
						if (d<=(player->tm_vis*vm))
// In visible range!
						{
							if ((d/2<(MIN_PASS_DIST+(float)player->tm_pow/3.6) && !ball_in_hands) || angle_of_vis(player,x,y,teams[i].tm_dist,cross))
// Within angle of vision 90!
							{
								if (!(((i==KP_A-1) || (i==KP_B-1)) && (teams[i].tm_dist<KP_MIN_PASS_DIST)))
								{
									passee_tab[passees][1]=i+1;
									passee_tab[passees++][2]=pass_type;
								}
// Add prospective passee!
							}
						}
					}
					else
					{
						if (cross && !ball_in_hands && 
							d<=(player->tm_vis*vm*1.4) && d>(prat*8))
						{
							if ((ball_poss<12 && (teams[i].tm_x)>pitch_len-(prat*18))
								|| (ball_poss>11 && (teams[i].tm_x)<prat*18))
							{
								angle=cross_angle(teams[ball_poss-1].tm_xdis,
													teams[ball_poss-1].tm_ydis,x,y);

								if (angle==1)
// Kicking at 90 degrees left...
								{
									pass_type=16;
									passee_tab[passees][1]=i+1;
									passee_tab[passees++][2]=pass_type;
								}
								else
								{
									if (angle==2)
// Kicking at 90 degrees right...
									{
										pass_type=17;
										passee_tab[passees][1]=i+1;
										passee_tab[passees++][2]=pass_type;
									}
								}
							}
						}
					}
				}
			}
		}
	}

//********************************//
// Passee table has been created. //
//********************************//

// Give preference values to each candidate...
// Low being best!

	int pas=0;


	if (passees)
	{
		int team_mate;

		if (!user_controlled)
		{
// Computer decision only...

			int opps;
			float tmx;
			float px=player->tm_x;
	
			for (int p=0; p<passees; p++)
			{

				team_mate=passee_tab[p][1]-1;

// Get opponents near team-mate...
				opps=opp_around((int)teams[team_mate].tm_x,
									 (int)teams[team_mate].tm_y,team_mate);

// Passer takes this into consideration...
				opps=64+(opps*(64+(player->tm_flair/2)));

// Optimum passing distance is around 10 yards...
// Anything below should start to lessen likelyhood of passing...
				if (teams[team_mate].tm_dist<OPTIMUM_PASS)
					opps+=(OPTIMUM_PASS-teams[team_mate].tm_dist);
	
// But, am I under threat and have to get rid of ball???
				if (!set_piece_on && match_mode>GOAL_KICK_BR && match_mode<GOAL_KICK_TL)
					opps-=opponents_near_holder*(32+(player->tm_flair/2));
				else
					opps-=64;

// Is he making run???
				if (want_pass==(team_mate+1))
					opps-=teams[team_mate].tm_flair;
	
// If in shooting range then less chance of passing...(greed factor)!
				if (player->tm_srng)
					opps+=GREED_FACTOR;

				tmx=teams[team_mate].tm_x;

				if (team_mate>11)
// Team B...
					if (tmx>px)
// Passing back...
						opps+=(tmx-px)*player->tm_flair/128;
					else
// Passing forward, less difference...
						opps+=((tmx-px)/5)*player->tm_flair/128;
				else
// Team A...
					if (tmx<px)
// Passing back...
						opps+=(px-tmx)*player->tm_flair/128;
					else
// Passing forward, less difference...
						opps+=((px-tmx)/5)*player->tm_flair/128;

// The more flair less likelyhood of passing especially if opps near passee!

				int op_p;
				if (team_mate<11)
					op_p=11;
				else
					op_p=0;
	
// Get vectors for pass!
				float tx=teams[team_mate].tm_x-ballx;
				float ty=teams[team_mate].tm_y-bally;
				float td=teams[team_mate].tm_dist;
				float ang=0;
				float ox,oy,od,a;
				tx=tx/td;
				ty=ty/td;

// Any opponents in path off prospective passed ball?

				for (int o=op_p; o<op_p+11; o++)
				{
					if ((teams[o].guy_on) && (teams[o].tm_dist<td*1.25))				// Inside pass range!
					{
						ox=teams[o].tm_x-ballx;
						oy=teams[o].tm_y-bally;
						od=teams[o].tm_dist;
						ox=ox/od;
						oy=oy/od;
						a=((tx*ox)+(ty*oy));
						if (a>0)
						{
							a=a*a*(96+(player->tm_flair/2))*td/od;
//							ang+=a*(player->tm_flair/64);
							ang+=a*(player->tm_flair/32);
						}
					}
				}
	
				if (passee_tab[p][2]==16 || passee_tab[p][2]==17)
// Crossing over opps...
				{
					opps+=ang/5;
					opps=opps/4;
				}
				else
					opps+=ang;
	
				passee_tab[p][0]=opps;		// Set preference level!
	
				af_randomize();

// If straight ahead pass and need to chip...
				{
					if (passee_tab[p][2]==5 && (ang>seed/2 || (user_controlled && chip_pass)))
// Chip over...
	 					passee_tab[p][2]=-1;
	
				}
			}
		}
		else
		{
// User preference is for distance in facing direction only...

			float tx,ty,dif;
			float px=player->tm_x;
			float py=player->tm_y;
			float xf=player->tm_xdis;
			float yf=player->tm_ydis;
			float min_d=2000;
			short pr=-1;

			for (int p=0; p<passees; p++)
			{
			 	passee_tab[p][0]=100;
				team_mate=passee_tab[p][1]-1;

				tx=teams[team_mate].tm_x-px;
				ty=teams[team_mate].tm_y-py;

				if (plr_facing(tx,ty,player))
				{
// Facing towards team-mate...
					d=calc_dist(tx,ty);

					if (d<min_d)
					{
// Closest...
						min_d=d;
						pr=p;
					}
				}
			}

			if (pr>=0)
				passee_tab[pr][0]=0;
		}

// Sort passee table in order of preference...
		qsort(passee_tab,passees,sizeof(int)*3,sort_less_than);

		if (user_controlled)
		{
// Take first team-mate on table...
			pas=passee_tab[0][1];
			pass_type=passee_tab[0][2];
		}
		else
		{
// Random selection weighted towards first in table...

			int chance;

			pas=0;
			for (int p=0; p<passees; p++)
			{
				af_randomize();
				chance=passee_tab[p][0];
	
				if (chance<MAX_PASS_PROB)
					chance=MAX_PASS_PROB;
				else
					if (chance>MIN_PASS_PROB)
						chance=MIN_PASS_PROB;
	
				if (set_piece_on)
					chance=chance/2;
	
				if (seed>chance)
				{
// Choose this guy to pass to!
					pas=passee_tab[p][1];
					pass_type=passee_tab[p][2];
					p=passees+1;
				}
			}
		}

		if (!pas && (must_pass || user_controlled))
// Must choose!
		{
			pas=passee_tab[0][1];
			pass_type=passee_tab[0][2];
		}
	}
	else
// Absolutely no one to pass to...
	{
		if ((must_pass) || (user_controlled))
			pas=0;
	}

	must_pass=FALSE;

	if (pas>0)
	{
// He is passing to someone...

		d=calc_dist(teams[pas-1].tm_x-ballx,teams[pas-1].tm_y-bally);
		
		if (ball_in_hands && (player->tm_player==KP_A || player->tm_player==KP_B))
		{
			if (opp_around(teams[pas-1].tm_x,teams[pas-1].tm_y,pas))
// Don't pass it out... (opponents around!)
				pas=0;
			else
// Keeper must throw or something...
				if (d<prat*10)
					pass_type=9;		// Roll it.
				else
					if (d<prat*20)
						pass_type=10;		// Throw it.
					else
						pass_type=11;		// Halfvoll it.
		}
		else
		{
			if ((ball_in_hands) && (teams[ball_poss-1].tm_act==THROW_ACT))
			{
// Player must throw...
				if (d<prat*15)
					pass_type=12;		// Throw short.
				else
					pass_type=13;		// Throw Long.
			}
			else
			{
				if (heading_ball)
					pass_type=15;
			}
		}
	}
	return(pas);
}

/******************************************************************************
*****************************************************************************/

void process_comments()
{
	if (want_pass_stat!=last_touch)
	{
// His team_mate does not have ball anymore...
		if (want_pass)
		{
			teams[want_pass-1].tm_comm=0;		
			teams[want_pass-1].tm_ccnt=0;
			reset_ideas(&teams[want_pass-1]);
		}
	}
}

/******************************************************************************
*****************************************************************************/

void init_speech(int p,int comm,int t)
{
	speech_tab[p-1].say=comm;
	if (t)
		speech_tab[p-1].cnt=t;
	else
		speech_tab[p-1].cnt=SPEECH_SECS*game_speed;
}

/******************************************************************************
*****************************************************************************/

void process_speech()
{
	for (int i=1; i<players+3; i++)
	{
		if (speech_tab[i-1].cnt)
		{
			speech_tab[i-1].cnt--;
		}
	}
}

/******************************************************************************
*****************************************************************************/

void player_comment(match_player *player)
{
	if (player->tm_comm)
	{
		if ((!(--player->tm_ccnt)) || (player->tm_act>TURN_ACT))
		{
			player->tm_comm=0;
			if (want_pass==player->tm_player)
				want_pass=0;
		}
	}
}

/******************************************************************************
*****************************************************************************/

void tackle_decide(match_player *player)
{
}

/******************************************************************************
*****************************************************************************/

void steal_decide(match_player *player)
{
}

/******************************************************************************
*****************************************************************************/

void block_decide(match_player *player)
{
}

/******************************************************************************
*****************************************************************************/

void user_free_ball(match_player *player)
{
	player->tm_stopped=FALSE;
}

/******************************************************************************
*****************************************************************************/

void other_interceptor(match_player *player)
{
	if (receiver_a==player->tm_player)
		receiver_a=FALSE;
	if (receiver_b==player->tm_player)
		receiver_b=FALSE;

	player->tm_notme=1+player->tm_flair/16;
}

/******************************************************************************
*****************************************************************************/

void free_ball(match_player *player)
{
	player->tm_stopped=FALSE;
	if ((!dead_ball_cnt) && (!player->tm_leave))
	{
		if (!ball_out_of_play)
		{
			if ((player->tm_player==KP_A) || (player->tm_player==KP_B))
			{
// Goal Keeper...
		
				if ((player->tm_player==KP_A && keeper_a_in_box)
					|| (player->tm_player==KP_B && keeper_b_in_box))

					if (shot_pending>0 && !shot_acknowledged && player->tm_dist<prat*50)
					{
						if (cannot_pick_up<=0 || ((player->tm_player<12 && cannot_pick_up>11)
							 || (player->tm_player>11 && cannot_pick_up<12)))
#ifdef EURO96
// This looks silly but leave for time being...
							if (penalty_shot && user_controlled)
							{
								if (uf1 || uf2)
									go_to_save_path(player);
							}
							else
								go_to_save_path(player);
#else
							 go_to_save_path(player);
#endif

					}
					else
					{
						if (player->tm_dist<80 && ball_inair)
						{
// Ball is quite close...
							 go_to_save_path(player);
						}
					}
			}

			if ((!penalty_game) && (player->tm_act!=SAVE_ACT) && (player->int_move!=I_SAVE_WAIT))
			{
				if ((thinking(player)) && (player->tm_act<=TURN_ACT))
				{
					if (player->tm_off)
// In offside position, must get out...
					{
						run_back(player);
					}
				}

				if (!interceptor_a)
				{
					if (near_path_a==player->tm_player)
					{
						if (go_to_path(near_path_a))
//							other_interceptor(player);
//						else
						{
							if (auto_users_a && !player->control)
							{
								{
									reselect_a();
									user_conts(player);
								}
							}
						}
					}
				}

				if (!interceptor_b)
				{
					if (near_path_b==player->tm_player)
					{
						if (go_to_path(near_path_b))
//							other_interceptor(player);
//						else
						{
							if (auto_users_b && !player->control)
							{
								{
									reselect_b();
									user_conts(player);
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

void out_of_vis(match_player *player)
{
}

/******************************************************************************
*****************************************************************************/

void range_flags(match_player *player)
{
	float x=player->tm_x;
	float y=player->tm_y;
	float d;

	if (player->tm_player>11)
// B
	{
		d=calc_dist(x,cntspot_y-y);
	}
	else
// A
	{
		d=calc_dist(pitch_len-x,cntspot_y-y);
	}

	if (d<MIN_HEADER_RNG+(prat*player->tm_pow/8))
		in_header_rng=TRUE;
	else
		in_header_rng=FALSE;

	if (d<(MIN_SHOOT_DIST+((float)player->tm_pow*3)))
		in_shot_rng=TRUE;
	else
		in_shot_rng=FALSE;
}
					
/******************************************************************************
*****************************************************************************/

// Is guy with ball in "crossing area".
// Which is a diagonal line from goal post to nearest sideline.

void cross_pos(match_player *player)
{
	in_cross_area=FALSE;
	if (bally>bot_post_y)
	{
		if (player->tm_player>11)
		{
			if (ballx<(bally-bot_post_y))

// Within diagonal from bot. left post to sideline!
			
				in_cross_area=TRUE;
		}
		else
		{
			if ((pitch_len-ballx)<(bally-bot_post_y))

// Within diagonal from bot. right post to sideline!
			
				in_cross_area=TRUE;
		}
	}
	else
	{
		if (bally<top_post_y)
		{
			if (player->tm_player>11)
			{
				if (ballx<(top_post_y-bally))

// Within diagonal from top left post to sideline!
			
					in_cross_area=TRUE;
			}
			else
			{
				if ((pitch_len-ballx)<(top_post_y-bally))
	
// Within diagonal from top right post to sideline!
				
					in_cross_area=TRUE;
			}
		}
	}
}
					
/******************************************************************************
*****************************************************************************/

void set_pos_flags(match_player *player)
{
	cross_pos(player);
	range_flags(player);
}

/******************************************************************************
*****************************************************************************/

void user_got_ball(match_player *player)
{
	int p=0;
	set_pos_flags(player);

	if (player->tm_act==STAND_ACT)
		user_spec_kick(player);
	else
	{

	if (uf2 && um)
// Pass in dir!
	{
		int p=(pass_decide(player,in_cross_area));
		if (pass_type==16 || pass_type==17)
			make_pass(player,p,TRUE);
		else
		{
			if (!p)
				pass_type=5;	// Forward tap...
			spec_kick_type=SPACT_FPASS;
			setp_kick_x=player->tm_xdis;
			setp_kick_y=player->tm_ydis;
			make_pass(player,p,FALSE);
		}
	}
	else
	{
		if (uf1 && um)
// Try shooting...
		{
			if (shoot_decide(player))
				make_shoot(player);
			else
// Try punt...
			{
				if (punt_decide(player))
					make_punt(player);
				else
// Try high pass to head...
				{
					chip_pass=TRUE;
					int p=(pass_decide(player,FALSE));
					if (p && (pass_type==16 || pass_type==17 || pass_type==-1))
						make_pass(player,p,TRUE);
					else
					{
						p=0;
						chip_pass=FALSE;
						pass_type=-1;	// Forward tap...
						spec_kick_type=SPACT_FPASS;
						setp_kick_x=player->tm_xdis;
						setp_kick_y=player->tm_ydis;
						make_pass(player,p,FALSE);
					}
				}
			}
		}
	}

	}

/*
		else
		{
			if (must_punt)
				if (punt_decide(player))
					make_punt(player);
			else
			{
				if (uf1)
				{
// He has pressed front fire button (1)!
// PUNT!
					if (punt_decide(player))
						make_punt(player);
					else
					{
// SHOOT!
						if (player->tm_srng)
						{
							shoot_decide(player);
							make_shoot(player);
						}
						else
						{
							must_pass=TRUE;
							chip_pass=TRUE;
							int p=pass_decide(player,FALSE);
							make_pass(player,p,FALSE);
						}
					}
				}
				else
				{
					if (uf2)
					{
// He has pressed top fire button (2)!
						must_pass=TRUE;
// CROSS!
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
					}
				}
			}
		}
	}
*/

	set_piece_on=FALSE;
}

/******************************************************************************
*****************************************************************************/

void got_ball(match_player *player)
{
	int p=0;

	if ((player->tm_player==KP_A) || (player->tm_player==KP_B))
	{

/****************
** Goal-Keeper	**		
****************/

// PUNT!
		if (punt_decide(player))
			make_punt(player);
		else
		{
// PASS!
			int p=(pass_decide(player));
			if (p)
				make_pass(player,p);
			else
			{
				if ((player->tm_player==KP_A && keeper_a_in_box)
					|| (player->tm_player==KP_B && keeper_b_in_box))
				{
// Can pick ball up...

					if (!ball_in_hands)
					{
						if ((cannot_pick_up<=0)
							|| (cannot_pick_up<12 && ball_poss>11 && keeper_b_in_box)
							|| (cannot_pick_up>11 && ball_poss<12 && keeper_a_in_box))

						{
							if (opp_around(ballx,bally,player->tm_player))
							{
								holder_lose_ball();
								keep_dive=TRUE;
								go_to_save_path(player,TRUE);
							}
							else
								init_pickup_act(player);
						}
						else
						{
							if (player->tm_poss)
								must_punt=TRUE;
							if (punt_decide(player))
								make_punt(player);
							else
// RUN!
		  						make_run(player);
						}
					}
				}
				else
				{
// Can't touch ball with hands...
					must_punt=TRUE;
				}
			}
		}
	}

	else
	{

/***********
** PLAYER **		
***********/

// Not taking throw!

		set_pos_flags(player);
// SHOOT!
		if (shoot_decide(player))
			make_shoot(player);
		else
		{
// CROSS!
			if (in_cross_area)
			{
				p=(pass_decide(player,TRUE));
				if (p)
					if (pass_type==16 || pass_type==17)
						make_pass(player,p,TRUE);
					else
						make_pass(player,p,FALSE);
			}
			if (!p)
			{
// PASS!
				p=(pass_decide(player));
				if (p)
					make_pass(player,p);
				else
				{
// PUNT!
					if (punt_decide(player))
						make_punt(player);
					else
					{
// RUN!
  						make_run(player);
					}
				}
			}
		}
	}
	set_piece_on=FALSE;

}

/******************************************************************************
*****************************************************************************/

int help_chance(match_player *player)
{
	int f=64+(player->tm_flair/2);
	float r,xd;

// Less calculated range if pass is to be made up-field...
	if (player->tm_player>11)
// Team B...
	{
		xd=player->tm_x-ballx;
		if (xd>0)
			xd=xd*2;
	}
	else
// Team A...
	{
		xd=player->tm_x-ballx;
		if (xd<0)
			xd=xd*2;
	}

	r=calc_dist(xd,bally-player->tm_y)/(prat*2);
	int help;

	if (support_me)
		help=512-(r*r);
	else
		help=32+(opponents_near_holder*80*f/128)
					-(opp_around(player->tm_x,player->tm_y,player->tm_player)*64*f/128)
					-(r*r);

// Dead ball situation...

	return(help);
}

/******************************************************************************
*****************************************************************************/

void we_have_ball(match_player *player)
{
	if (player->tm_player!=KP_A && player->tm_player!=KP_B && !player->tm_stopped
		 && match_mode!=PEN_KICK_A && match_mode!=PEN_KICK_B)
	{
		if ((thinking(player)) && (player->tm_act<=TURN_ACT))
		{
			if (player->tm_off)
// In offside position, must get out...
			{
				run_back(player);
			}
			else
			{
				if (!want_pass)
				{
					int help=help_chance(player);
					if (help<MIN_HELP_CHANCE)
						help=MIN_HELP_CHANCE;
					if (seed<=help)
// Ask for Pass!
					{
						if (player->tm_dist<CALL_DIST)
//				if (angle_of_vis(player,ballx-player->tm_x,bally-player->tm_y,player->tm_dist,FALSE))
						{
							want_pass=player->tm_player;
							want_pass_stat=ball_poss;
							player->tm_ccnt=40;
							player->tm_comm=-SAY_PASS;
							reset_ideas(player);
							player->int_move=I_RUN_ON;
							player->int_cnt=40;

							if (in_cross_area)
							{
								float x=player->tm_x;
								float y=player->tm_y;
								int i=player->tm_player;

								if ((i<12) && (x>(pitch_len-(prat*15))) && (y>(cntspot_y-(prat*18)))
									&& (y<(cntspot_y+(prat*18)))
									&& (teams[i].tm_dist>(prat*20)))

									player->tm_comm=-SAY_CROSS;

								if ((i>11) && (x<(prat*15)) && (y>(cntspot_y-(prat*18)))
									&& (y<(cntspot_y+(prat*18)))
									&& (teams[i].tm_dist>(prat*20)))

									player->tm_comm=-SAY_CROSS;
							}
// Run towards opponents penalty spot...
							float x,y,d;
							if (player->tm_player<12)
								x=pitch_len-ballx;
							else
								x=-ballx;

							y=cntspot_y-bally;
					
							d=calc_dist(x,y);

// How far is half way to goal...

							float kd=kicking_dist(&teams[ball_poss-1],x,y,d)-(prat*2);
							if (d/2<kd)
								init_run_act(player,ballx+x/2,bally+y/2,FALSE);
							else
								init_run_act(player,ballx+(x/d*kd),bally+(y/d*kd),FALSE);
							player->int_cnt=player->go_cnt;
							player->tm_ccnt=player->go_cnt;
						}
						else
						{
							if (!support_me)
							{
	 							player->tm_ccnt=40;
								player->tm_comm=-SAY_GIVE;
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

int in_close(match_player *player)
{
	if (player->tm_dist<DRIB_DANGER_AREA)
		return(TRUE);
	else
		return(FALSE);
}

/*****************************************************************************
*****************************************************************************/

int can_close_down(match_player *player)
{
	int p=player->tm_player;
	if ((nearest_a==p) || (nearest_b==p))
		return(TRUE);
	else
		return(FALSE);
}

/*****************************************************************************
*****************************************************************************/

void close_him_down(match_player *player)
{
	player->int_move=I_CLOSE_DOWN;
	player->int_cnt=(player->tm_flair/4);
	if (!go_to_path(player->tm_player))
		other_interceptor(player);
	action="Close Down";
}	

/*****************************************************************************
*****************************************************************************/

void force_error(match_player *player)
{
	if ((player->tm_player<12 && !auto_users_a) 
		|| (player->tm_player>11 && !auto_users_b))
	{
// No team users so computer must control this guy...

		if (player->tm_dist<STEAL_DIST || teams[ball_poss-1].tm_act==TACKLE_ACT)
		{
			if (!go_to_path(player->tm_player))
				other_interceptor(player);
//			else
//				player->int_move=I_STEAL;
		}
		else
		{
			int chance=32;
			if (player->tm_player<12)

// The further up the park, the more chance of direct tackling!

				chance-=((pitch_len-player->tm_x)/48);
			else
				chance-=(player->tm_x/48);

			if (chance<=seed && teams[ball_poss-1].tm_act!=TACKLE_ACT
				 && teams[ball_poss-1].int_move!=I_GET_UP)
				get_tack_path(player);
			else
				go_to_between(player->tm_player);	// get yourself between him and goal!
		}
	}
}

/*****************************************************************************
*****************************************************************************/

void forceful_retrieve(match_player *player)
{
	if ((player->tm_player<12 && !auto_users_a) 
		|| (player->tm_player>11 && !auto_users_b))
	{
// No team users so computer must control this guy...
		get_tack_path(player);
	}
}

/******************************************************************************
*****************************************************************************/

void go_to_side(match_player *player)

// Send player to the side off opponent with ball...

{
// His intention is to intercept ball.
// Therefore his flair determines no. of turns before rethink!

	int ff=33-(player->tm_flair/4);
	player->int_move=I_INTERCEPT;		// Intercept ball!
	player->int_cnt=ff;						// Flair factor.

	float dx=teams[ball_poss-1].tm_xdis;
	float dy=teams[ball_poss-1].tm_ydis;

	float x=(ballx-player->tm_x)/player->tm_dist;			// vector to ball...
	float y=(bally-player->tm_y)/player->tm_dist;

// Which side to go to...???
	if ((x*dy)>(y*dx))
	{
		x=-dy;		// 90 degrees clockwise...
		y=dx;
	}
	else
	{
		x=dy;		// 90 degrees anti-clockwise...
		y=-dx;
	}

	x=ballx+(x*prat);
	y=bally+(y*prat);

	init_run_act(player,x,y,TRUE);				//Go to path point!
}

/******************************************************************************
*****************************************************************************/

void go_to_between(int p_num)

// Send player(p_num) to intersection point between ball path and goal centre.
// If he cannot meet ball then best try!

{
	int x,y,z,d;
	float px=teams[p_num-1].tm_x;
	float py=teams[p_num-1].tm_y;
	float goal_x;
	int rate=actual_spd(&teams[p_num-1]);

	action="Between";

	if (p_num<12)
		goal_x=0;
	else
		goal_x=pitch_len;

// His intention is to intercept ball.
// Therefore his flair determines no. of turns before rethink!

	int ff=33-(teams[p_num-1].tm_flair/4);
	teams[p_num-1].int_move=I_INTERCEPT;		// Intercept ball!
	teams[p_num-1].int_cnt=ff;						// Flair factor.

	for (int i=1; i<50; i++)
	{
		x=ball_pred_tab[i][0];
		y=ball_pred_tab[i][1];
		z=ball_pred_tab[i][2];
		d=calc_dist(goal_x-x,cntspot_y-y);
		if (d<1)
			d=1;
		
		x=x+(((goal_x-x)*BETWEEN_DIST)/d);
		y=y+(((cntspot_y-y)*BETWEEN_DIST)/d);

		if (z<=PLAYER_HEIGHT)
		{
			d=calc_dist(x-px,y-py);
//			d=(int)(((float)d)/rate);					//How many steps?
			d=get_there_time(p_num,x,y);					//How many steps?
			if (d<=i)
// He can get there in time!
			{
				init_run_act(&teams[p_num-1],x,y,TRUE);				//Go to path point!
				i=60;												// End For Loop!
			}
		}
	}
	if (i<60)
// He cant intersect!
		init_run_act(&teams[p_num-1],x,y,FALSE);			// run toward last.
}

/******************************************************************************
*****************************************************************************/

void user_opp_has_ball(match_player *player)
{
	if (uf1)
// Tackle opp.
	{
		user_init_tackle(player);
	}
	else
	{
		if (uf2)
// Steal from opp.
		{
			if (player->tm_dist<(STEAL_DIST/4))
			{
				init_steal_act(player);
			}
#ifdef EURO96
			else
// Burst_of_speed...
			{
				if (!burst_timer[user_controlled-1]--)
					burst_timer[user_controlled-1]=REAL_SPEED;
				else
					if (!burst_timer[user_controlled-1])
						burst_timer[user_controlled-1]=-1;
			}
#endif
		}
		else
		 	burst_timer[user_controlled-1]=0;
	}
}

/******************************************************************************
*****************************************************************************/

void opp_has_ball(match_player *player)
{
	if ((player->tm_player==KP_A) || (player->tm_player==KP_B))
	{

/****************
** Goal-Keeper	**		
****************/

		if (player->tm_player<12)
// KP_A...
		{
			if ((keeper_a_in_box) && (player->tm_dist<DIVE_FEET_DIST) && (seed>player->tm_flair))
// Can dive for ball...
			{
				keep_dive=TRUE;
				go_to_save_path(player,TRUE);
			}
		}
		else
// KP_B...
		{
			if ((keeper_b_in_box) && (player->tm_dist<DIVE_FEET_DIST) && (seed>player->tm_flair))
// Can dive for ball...
			{
				keep_dive=TRUE;
				go_to_save_path(player,TRUE);
			}
		}
	}

	{

/***********
** PLAYER **		
***********/

 		if ((ball_in_hands) || (ball_out_of_play))
// Don't tackle keeper directly!
		{

		}
		else
		{
			if ((player->tm_pos) && (player->tm_pos<=close_in_number)
				&& ((player->tm_player!=KP_A) && (player->tm_player!=KP_B))
				|| (player->tm_pos==1))
			{				
// There's not too many guys going for opponent with ball!

				if (in_close(player))
// I am close enough to hassle!
				{
					short d=get_facing_opp_dir(player);

					if (d==-1)
					{
// He has his back to me!
					 	if ((ball_speed<1) && ((seed&4)
							 || (player->tm_player>11 && ballx<cntspot_x)
							 || (player->tm_player<12 && ballx>cntspot_x)))

// Try and go round a bit...
							go_to_side(player);
						else
							if ((teams[ball_poss-1].tm_act==TACKLE_ACT && teams[ball_poss-1].go_cnt>EFFECTIVE_TACK)
								 || teams[ball_poss-1].int_move==I_GET_UP)
								force_error(player);
							else
								go_to_between(player->tm_player);	// get yourself between him and goal! 
					}
					else

// He is not shielding ball!
					{
						if (d==1)
						{
// He has his side to me!
							if	(seed&8 && (teams[ball_poss-1].tm_act==TACKLE_ACT || teams[ball_poss-1].int_move==I_GET_UP))
// Opponent is not able to turn and avoid... (So go directly to ball!)
								force_error(player);
							else
								if ((player->tm_player!=KP_A) && (player->tm_player!=KP_B))
// Not the keeper!
									forceful_retrieve(player);	// Tackle directly!
								else
									force_error(player);
						}
						else

// He is facing towards me!
							force_error(player);			// More patient style of attack!
					}
				}
				else
// Not in close enough!
				{
					if (can_close_down(player))

// I can close him down!
						close_him_down(player);
				}
			}
		}	
	}
}

/******************************************************************************
*****************************************************************************/

void user_intelligence(match_player *player)
{
	if (match_mode || !ball_poss)
		intelligence(player);
	else
	{
		char busy=0;
		if (player->int_cnt)				//Is he busy?
		{
			if (--(player->int_cnt))
				busy=1;
				else
			{
				player->int_cnt=-1;
				reset_ideas(player);
			}
		}

		if (player->tm_act<=TURN_ACT)	// Player is standing or running or turning!
		{
			if (!busy)
			{
				if (!ball_poss)
					user_free_ball(player);
				else
				{
					if (ball_poss==player->tm_player)
						user_got_ball(player);
					else
					{
						if (((ball_poss<12) && (player->tm_player>11))
							|| ((ball_poss>11) && (player->tm_player<12)))
							user_opp_has_ball(player);
					}
				}
			}
		}
	}
}

/******************************************************************************
*****************************************************************************/

void offside_rule(match_player *player)
{
	if (player->tm_player<12)
// Team A...
	{

		if ((!match_mode) && (!ball_poss && ball_released>0) && (last_touch<12)
			 && (last_touch!=player->tm_player) && (player->tm_off) && (!just_scored)
			 && (ballx<player->tm_x))
//			 && (ballx<player->tm_x) && receiver_a==player->tm_player)
// His team-mate has released ball and he is in an offside pos...

			init_offside(player);	// Does Linesman see it!
		else
			if ((ball_poss<12) && (player->tm_x>cntspot_x)
				 && (can_be_offside) && (player->tm_x>(defense_b+prat)) &&  (!just_scored))
// Player is in opponents half, his opponent doesn't have ball and
// in normal play, and no defenders behind.
			{
				if (!player->tm_off)	
					player->tm_off=-1;		// Potential Offside (get back).
			}
			else
				player->tm_off=FALSE;	// Not offside.
	}
	else
// Team B...
	{
		if ((!match_mode) && (!ball_poss && ball_released<0) && (last_touch>11)
			 && (last_touch!=player->tm_player) && (player->tm_off) && (!just_scored)
			 && (ballx>=player->tm_x))
//			 && (ballx>=player->tm_x) && receiver_b==player->tm_player)
// His team-mate has released ball and he is in an offside pos...

			init_offside(player);	// Does Linesman see it!
		else
			if ((ball_poss>11 || !ball_poss) && (player->tm_x<cntspot_x)
				 && (can_be_offside) && (player->tm_x<(defense_a-prat)) && (!just_scored))
// Player is in opponents half, his team mate has the ball
// in normal play, and no defenders behind.

			{
				if (!player->tm_off)	
					player->tm_off=-1;		// Potential Offside (get back).
			}
			else
				player->tm_off=FALSE;	// Not offside.

	}

	if ((player->tm_off==TRUE) && (!match_mode) && (!just_scored))
// Linesman has indicated offside...
	{
// Is he interfering with play...
		if (player->tm_dist<ref_strictness*1.1)
		{
			offside_now=TRUE;
			init_foul(player->tm_player,FALSE,TRUE);	// Indirect F.K. for offside!
			player->tm_off=FALSE;
		}
	}
}

/******************************************************************************
*****************************************************************************/

void override(match_player *player)
{
	if (offside_on)
		offside_rule(player);
}

/******************************************************************************
*****************************************************************************/

void remove_player(match_player *player)
{
	player->guy_on=FALSE;
	if (!player_being_subbed)
	{
		hold_up_play=4*REAL_SPEED;
		camera=sub_camera;
		player_on_off=FALSE;
		ref_wait=(160-ref_strictness)*REAL_SPEED/8;
	}
}

/******************************************************************************
*****************************************************************************/

void init_off_int(match_player *player)
{
	allow_replay=FALSE;
	float tx=stadlist[setup.stadium].tunlx;
	float ty=-stadlist[setup.stadium].tunlz;
	float tly;
	if (ty>cntspot_y)
		ty+=60;
	else
		ty-=60;

	if (player_on_off>0 && calc_dist(tx-player->tm_x,ty-player->tm_y)<prat*2)
	{
// In tunnel! (get off)!
		remove_player(player);
		player->tm_trap=0;
	}
	else
	{
		player->draw_me=TRUE;
		player->int_cnt=600;
		player->int_move=I_OFF;

		if (ty>cntspot_y)
			tly=pitch_wid;
		else
			tly=0;

		if (player->tm_trap || calc_dist(tx-player->tm_x,tly-player->tm_y)<prat*2)
// At touch-line...(send him into tunnel)!
		{
			if (player_on_off<0)
			{
// Coming on...
				player->int_move=0;
				reset_ideas(player);
				player_on_off=FALSE;
				camera=sub_camera;
				allow_replay=TRUE;
			}
			else
			{
				player->tm_trap=TRUE;
				init_run_act(player,tx,ty,0);
			}
		}
		else
// send him to touch-line...
			init_run_act(player,tx,tly,0);
	}
}

/******************************************************************************
*****************************************************************************/

void intelligence(match_player *player)
{
	if ((player->control) && (!match_mode) && (ball_poss))
	{
// Player has just collected ball and been auto selected...
		user_controlled=player->control;
		user_intelligence(player);
	}
	else
	{
		char busy=0;
		int pnum=player->tm_player;

		if ((player->tm_leave) && (last_touch!=player->tm_player))
			player->tm_leave=FALSE;												// he can touch ball again!

		if (player->int_cnt)				//Is he busy?
		{
			if (--(player->int_cnt))
			{
				if (((pnum==KP_A) || (pnum==KP_B)) && (player->int_move==I_INTERCEPT)
					&& (shot_pending>0))
					busy=0;
				else
				{
					busy=1;
/*
					if (player->int_move==I_INTERCEPT && user_controlled && player->tm_strike>0)
// User player is interecpting ball but hasn't chosen special move...
						go_to_path(player->tm_player);
*/
					if (player->int_move==I_OFF)
					{
// He is going off!
						if (player->tm_act==STAND_ACT)
							init_off_int(player);
					}
					else
					{
						if (player->int_move==I_RUN_ON)
// Calling for pass ahead...
						{
							if (plr_facing(player->go_xoff,player->go_yoff,player))
							{
								if (player->tm_comm<0)
									player->tm_comm=-player->tm_comm;
							}
							else
							{
								if (player->tm_comm>0)
								{
									player->tm_comm=FALSE;
									player->tm_ccnt=0;
									reset_ideas(player);
								}
							}
						}
						else
						{
							if (player->int_move==I_STEAL)
							{
								if (player->tm_dist<STEAL_BODY_DIST)
								{
									reset_ideas(player);
									init_steal_act(player);
								}
							}
						}
					}
				}
			}
			else
			{
				player->int_cnt=-1;
				if (player->int_move==I_SAVE_WAIT) 
				{
					if (player->tm_act==RUN_ACT)
						player->int_cnt=player->go_cnt+2;
				
					if (player->int_cnt>0)
					{
						player->int_move=I_INTERCEPT;
						busy=1;
					}
					else
						reset_ideas(player);
				}
				else
					reset_ideas(player);
			}
		}

		if (player->tm_act<=TURN_ACT)	// Player is standing or running or turning!
		{
			if (!busy && !just_scored)
			{
				if (player->guy_on<0)
				{
// He has to be sent off!
					init_off_int(player);
				}

				if (dead_ball_cnt==0)
// Are we in normal play...
				{
					if (!ball_poss)
						free_ball(player);
					else
					{
						if (ball_poss==pnum)
							got_ball(player);
						else
						{
							if ((pnum<12) && (ball_poss<12))
// My team A has ball!
								we_have_ball(player);
							else
							{
								if ((pnum>11) && (ball_poss>11))
// My team B has ball!
									we_have_ball(player);
								else
									opp_has_ball(player);
							}
						}
					}
				}
				else
				{
// Is ball holder looking for support...
					if (ball_poss!=pnum && support_me)
					{
						if ((pnum<12) && (ball_poss<12))
// My team A has ball!
							we_have_ball(player);
						else
							if ((pnum>11) && (ball_poss>11))
// My team B has ball!
								we_have_ball(player);
					}
				}
			}
		}
	}
}

/******************************************************************************
*****************************************************************************/
/*
void cant_block_opp(match_player *player,match_player *oplayer)
{
 	int vx=(int)(ballx+(oplayer->go_txdis*8));	 //look 8 turns ahead
 	int vy=(int)(bally+(oplayer->go_tydis*8));
 	vx-=player->tm_x;
 	vy-=player->tm_y;
 	if (calc_dist(vx,vy)<=tackle_range)

// In tackling range!

 	{
 		tackle_decide(player);
 		if (flag)
			go_tackle(player,oplayer);
 		else
 			cant_tack_opp(player);
 	}
 	else
 		cant_tack_opp(player);
}
*/


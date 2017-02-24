/******************************************************************************
******************************************************************************/

// User Interface routines...

/******************************************************************************
******************************************************************************/

#include <math.h>
#include <string.h>
#include <stdio.h>

#include "defines.h"
#include "mouse.h"
#include "externs.h"

extern char on_3d;
extern void editor_main();

/******************************************************************************
******************************************************************************/

void init_keyboard()
{
	key2[UP_KEY]=0x1e;		// A
	key2[DN_KEY]=0x2c;		// Z
	key2[LF_KEY]=0x33;		// <
	key2[RT_KEY]=0x34;		// >
	key2[F1_KEY]=0x10;		// Q
	key2[F2_KEY]=0x35;		// /

	key1[UP_KEY]=-0x48;		// Arrow Up
	key1[DN_KEY]=-0x50;		// Arrow Dn
	key1[LF_KEY]=-0x4b;		// Arrow Lf
	key1[RT_KEY]=-0x4d;		// Arrow Rt
	key1[F1_KEY]=0x52;		// 0(num)
	key1[F2_KEY]=0x53;		// .(num)
}

/******************************************************************************
******************************************************************************/

void delete_net_user(int u)
{
	users_left--;
	if (u==user_taker)
		user_taker=FALSE;

	short tm=0;

	int i;
	char copy=FALSE;

	short type=users[u-1].type;

	if (type<0)
	{
// Auto Player...
		if (type==-1)
		{
// Auto-user A.
			for (i=0; i<auto_users_a; i++)
			{
				if (auto_users_list_a[i]==u)
// Found user...
				{
/*
					if (last_user_a>=i && last_user_a)
						last_user_a--;

					if (play_ball_a>=i && play_ball_a)
						play_ball_a--;
*/
					copy=TRUE;
				}

				if (copy && i<auto_users_a)
					auto_users_list_a[i]=auto_users_list_a[i+1];
			}

			auto_users_a--;
		}
		else
		{
// Auto-user B.
			for (i=0; i<auto_users_b; i++)
			{
				if (auto_users_list_b[i]==u)
// Found user...
				{
/*
					if (last_user_b>=i && last_user_b)
						last_user_b--;

					if (play_ball_b>=i && play_ball_b)
						play_ball_b--;
*/
					copy=TRUE;
				}

				if (copy && i<auto_users_b)
					auto_users_list_b[i]=auto_users_list_b[i+1];
			}

			auto_users_b--;
		}
	}
	else
	{
// Fixed Player...
		if (fixed_net_user==u)
			fixed_net_user=0;
	}

	for (i=0; i<22; i++)
	{
		if (teams[i].control==u)
			teams[i].control=FALSE;		// No user control of player!
	}

	users[u-1].type=0;
	users[u-1].control=NO_CTRL;

	sprintf(glob_str1,"USER %d has quit!",u);
	add_message(&glob_str1[0],RED,TRUE);

	if (users_left==1)
		sprintf(glob_str2,"You are now the only user in the game!");
	else
		sprintf(glob_str2,"There are %d users left in the game!",users_left);

	add_message(&glob_str2[0],YELLOW);
}

/******************************************************************************
******************************************************************************/

// Add team user.

void add_team_user(short t,short c)
{
	users[num_of_users].type=t;						// User team.
	users[num_of_users].control=c;					// Control type.
	users[num_of_users++].plr=-1;						// Current player.

/*
	if (c==JOY1_CTRL)
		joystick1_on=TRUE;
	if (c==JOY2_CTRL)
		joystick2_on=TRUE;
*/
	if (t==-1)
		auto_users_list_a[auto_users_a++]=num_of_users;
	if (t==-2)
		auto_users_list_b[auto_users_b++]=num_of_users;

#ifdef SUPPORT_LP
	if (c==LOGPAD_CTRL)
		lp_user=num_of_users;
#endif
}

/******************************************************************************
******************************************************************************/

// Add User as fixed player.

void add_fixed_user(short p,short c)
{
	users[num_of_users].type=p;						// User fixed player.
	users[num_of_users].control=c;					// Control type.
	users[num_of_users++].plr=p;						// Current player.

/*
	if (c==JOY1_CTRL)
		joystick1_on=TRUE;
	if (c==JOY2_CTRL)
		joystick2_on=TRUE;
*/

	teams[p-1].control=num_of_users;					// Tag player as user controlled!

	if (c!=NET_CTRL && network_on)
		fixed_net_user=num_of_users;

#ifdef SUPPORT_LP
	if (c==LOGPAD_CTRL)
		lp_user=num_of_users;
#endif
}

/******************************************************************************
******************************************************************************/

// Initialise Fixed control players.

void clear_all_fixed()
{
	for (int i=0; i<players; i++)
	{
		teams[i].control=FALSE;
	}
}

/******************************************************************************
******************************************************************************/

// Initialise User Configuration Table...

void init_users()
{
	memset((void *)users,0,MAX_NET_USERS*(sizeof(user_config)));
	num_of_users=0;
	auto_users_a=0;
	auto_users_b=0;
	fixed_net_user=0;
	clear_all_fixed();

//	add_team_user(TEAM_A,MOUSE_CTRL);
//	add_team_user(TEAM_A,KEY1_CTRL);
//	add_team_user(TEAM_A,KEY2_CTRL);
//	add_team_user(TEAM_A,JOY1_CTRL);
//	add_team_user(TEAM_A,KEY2_CTRL);
//	add_fixed_user(15,JOY2_CTRL);
//	add_team_user(TEAM_A,KEY2_CTRL);
//	add_fixed_user(11,KEY1_CTRL);
}

/******************************************************************************
******************************************************************************/

void go_button()
{
	switch(button_lit)
	{
		case 1:
		{
			in_game=FALSE;
			break;
		}
		case 2:
		{
			grid_map();					//Draw zonal grid on pitch.
			MouseRelease();
			break;
		}
		case 3:
		{
			faster();					//Speed up.
			break;
		}
		case 4:
		{
			slower();					//Slow down.
			break;
		}
		case 5:
		{
  			show_nums();				//Show player nos.
  			MouseRelease();
			break;
		}
		case 6:
		{
  			set_xyspin++;				//Add clockwise swerve.
  			MouseRelease();
			break;
		}
		case 7:
		{
  			set_xyspin--;				//Add anti-clockwise swerve.
  			MouseRelease();
			break;
		}
		case 8:
		{
  			set_zspin++;				//Add Top-spin swerve.
  			MouseRelease();
			break;
		}
		case 9:
		{
  			set_zspin--;				//Add Back-spin swerve.
  			MouseRelease();
			break;
		}
		case 10:
		{
//  			on_3d=TRUE;					//Use 3d display.
			break;
		}

	}
}

/******************************************************************************
*****************************************************************************/

void mouse_fired()
{
	if (!on_3d)
	{
		if (button_lit)
			go_button();
	}
}

/******************************************************************************
*****************************************************************************/

void process_butts()
{
	int x,y,w;
	for (int i=0; i<max_butts; i++)
	{
		x=us_buttons[i].x;
		y=us_buttons[i].y;
		w=us_buttons[i].w;
		if ((Mouse.x/2>=x-4) && (Mouse.x/2<=x+(w*8)+4)
			&& (Mouse.y>=y-4) && (Mouse.y<=y+12))
		{
			if (!us_buttons[i].l)
			{
				light_button(i);			//Mouse will highlight button.
				us_buttons[i].l=1;
			}
		}
		else
		{
			if (us_buttons[i].l)
			{
				unlight_button(i);
				us_buttons[i].l=0;
			}
		}
	}
}		

/******************************************************************************
*****************************************************************************/


// Low level input code has moved to network.c...


/******************************************************************************
*****************************************************************************/

// Converts integer input from interrupts into expected data in users_dir array

void convert_inputs()
{
	short x,y;
	for (int i=0; i<num_of_users; i++)
	{
		x=users_dir_i[readptr][i].x_f1;
		y=users_dir_i[readptr][i].y_f2;

		if (x==12345&&y==12345)	// Magic quit data from master in network game
			delete_net_user(i+1);
		else
		{
			users_dir[i].f=(x&1)|((y&1)<<1);

#ifdef EURO96
			users_dir[i].f+=((x&6)<<1);
			users_dir[i].f+=((y&6)<<3);

			x&=0xfff8;
			y&=0xfff8;
#else

#ifdef SUPPORT_LP
			if (users[i].control==LOGPAD_CTRL)
			{
				users_dir[i].f+=((x&6)<<1);
				users_dir[i].f+=((y&6)<<3);
			}

			x&=0xfff8;
			y&=0xfff8;
#else
			x&=0xfffe;
			y&=0xfffe;
#endif

#endif
			users_dir[i].m=(x || y);
			users_dir[i].x=x/32768.;
			users_dir[i].y=y/32768.;

		}
	}
}


/******************************************************************************
*****************************************************************************/

// Reset Auto-selected User...

void clear_auto(short u)
{
	users[u-1].plr=0;

	for (int i=1; i<=players; i++)
	{
		if (teams[i-1].control==u)
		{
			teams[i-1].control=FALSE;
			teams[i-1].tm_htype=FALSE;
		}
	}
}

/******************************************************************************
*****************************************************************************/

// Reset All Auto-selected Users...

void clear_all_autos()
{
	for (short i=0; i<auto_users_a; i++)
	{
		clear_auto(auto_users_list_a[i]);
	}
	for (i=0; i<auto_users_b; i++)
	{
		clear_auto(auto_users_list_b[i]);
	}
}
		
/******************************************************************************
*****************************************************************************/

void reset_f_held()
{
	f1_down=FALSE;
	f2_down=FALSE;
}

/******************************************************************************
*****************************************************************************/

short user_keeper_a()
{
	short u=teams[KP_A-1].control;
	if (!u)
		if (auto_users_a)
		{
			if (++play_ball_a>=auto_users_a)
				play_ball_a=0;
			u=auto_users_list_a[play_ball_a];
			clear_auto(u);
		}
		else
			u=0;

	return(u);
}

/******************************************************************************
*****************************************************************************/

short user_keeper_b()
{
	short u=teams[KP_B-1].control;
	if (!u)
		if (auto_users_b)
		{
			if (++play_ball_b>=auto_users_b)
				play_ball_b=0;
			u=auto_users_list_b[play_ball_b];
			clear_auto(u);
		}
		else
			u=0;

	return(u);
}

/******************************************************************************
*****************************************************************************/

short user_taker_a(short p)
{
	reset_f_held();
	short u=teams[p-1].control;
	if (!u)
	{
		if (auto_users_a)
		{
			if (++play_ball_a>=auto_users_a)
				play_ball_a=0;
			u=auto_users_list_a[play_ball_a];
			clear_auto(u);
		}
		else
			u=0;
	}
	return(u);
}

/******************************************************************************
*****************************************************************************/

short user_taker_b(short p)
{
	reset_f_held();
	short u=teams[p-1].control;
	if (!u)
	{
		if (auto_users_b)
		{
			if (++play_ball_b>=auto_users_b)
				play_ball_b=0;
			u=auto_users_list_b[play_ball_b];
			clear_auto(u);
		}
		else
			u=0;
	}
	return(u);
}

/******************************************************************************
*****************************************************************************/

void auto_select_a(short u)
{
// Team A...
	closest=FALSE;

	last_plr_a=users[u-1].plr;

	if (!(ball_poss && u==teams[ball_poss-1].control))
// This guy doesn't have ball!
	{
		if (ball_poss!=KP_A && ball_poss<=players/2 && ball_poss
		 	&& !teams[ball_poss-1].control)
		{
// His team-mate has ball who isn't a user... (make him this user!)
			clear_auto(u);
			users[u-1].chng=TRUE;				// changed control.

			reset_ideas(&teams[ball_poss-1]);
			teams[ball_poss-1].control=u;
			users[u-1].plr=ball_poss;
		}
		else
// Get closest...
		{
			short main_guy;
			if (user_taker2==u)
				main_guy=KP_A;
			else
				if (receiver_a)
					main_guy=receiver_a;
				else
					if (interceptor_a)
						main_guy=interceptor_a;
					else
						if (near_path_a)
							main_guy=near_path_a;
						else
							main_guy=0;

			float d;
			int guy=0;
			float lowest=2000;

			for (int i=1; i<12; i++)
			{
				if ((i!=KP_A || match_mode==GOAL_KICK_BL || match_mode==GOAL_KICK_TL || user_taker2)
				 	&& teams[i-1].guy_on>0 && (!teams[i-1].control || teams[i-1].control==u))
				{
					if (teams[i-1].tm_act!=FALL_ACT)
					{
	 					if (i==main_guy)
	 						d=1;
	 					else
	 						d=teams[i-1].tm_dist;

						if (d<lowest)
						{
							guy=i;
							lowest=d;
						}
					}
				}
			}

			if (guy!=last_plr_a && guy && 
				(last_plr_a<=0 || (last_plr_a>0 && !sel_circle[last_plr_a-1]) || receiver_a))
			{
				clear_auto(u);
				teams[guy-1].control=u;
				users[u-1].chng=TRUE;				// changed control
				users[u-1].plr=guy;
			}
		}
	}
}


/******************************************************************************
*****************************************************************************/

void auto_select_b(short u)
{
// Team B...
	closest=FALSE;

	last_plr_b=users[u-1].plr;
		
	if (!(ball_poss && u==teams[ball_poss-1].control))
// This guy doesn't have ball!
	{
		if (ball_poss!=KP_B && ball_poss>players/2
			 && !teams[ball_poss-1].control)
		{
// His team-mate has ball who isn't a user... (make him this user!)
			clear_auto(u);
			users[u-1].chng=TRUE;				// changed control.

			reset_ideas(&teams[ball_poss-1]);
			teams[ball_poss-1].control=u;
			users[u-1].plr=ball_poss;
		}
		else
// Get closest...
		{
			short main_guy;
			if (user_taker2==u)
				main_guy=KP_B;
			else
				if (receiver_b)
					main_guy=receiver_b;
				else
					if (interceptor_b)
						main_guy=interceptor_b;
					else
						if (near_path_b)
							main_guy=near_path_b;
						else
							main_guy=0;

			float d;
			int guy=0;
			float lowest=2000;

			for (int i=12; i<=players; i++)
			{
				if ((i!=KP_B || match_mode==GOAL_KICK_BR || match_mode==GOAL_KICK_TR || user_taker2)
				 	&& teams[i-1].guy_on>0 && (!teams[i-1].control || teams[i-1].control==u))
				{
					if (teams[i-1].tm_act!=FALL_ACT)
					{
						if (i==main_guy)
							d=1;
						else
							d=teams[i-1].tm_dist;

						if (d<lowest)
						{
							guy=i;
							lowest=d;
						}
					}
				}
			}

			if (guy!=last_plr_b && guy &&
				(last_plr_b<=0 || (last_plr_b>0 && !sel_circle[last_plr_b-1]) || receiver_b))
			{
				clear_auto(u);
				teams[guy-1].control=u;
				users[u-1].chng=TRUE;				// changed control
				users[u-1].plr=guy;
			}
		}
	}
}

/******************************************************************************
*****************************************************************************/

void reselect_a()
{
// Team A!
	short user,maxu,au,max_au;
	signed char p;
	float max=-1;
	float d;

	if (auto_users_a)
	{
		if (last_user_a==auto_users_a)
			last_user_a=0;

		maxu=auto_users_list_a[last_user_a];

		if (++last_user_a==auto_users_a)
			last_user_a=0;

		au=last_user_a;
		max_au=au;

		for (short i=1; i<auto_users_a; i++)
		{
			if (au==auto_users_a)
				au=0;

			user=auto_users_list_a[au];
			p=users[user-1].plr;
			if (p<=0)
				d=1500;
			else
				d=(teams[p-1].tm_dist);

			if (d>max)
			{
				max=d;
				maxu=user;
				max_au=au;
			}
			au++;
		}
		auto_select_a(maxu);			// Team Control.
		if (!ball_poss)
			last_user_a=max_au;
	}
}

/******************************************************************************
*****************************************************************************/

void reselect_b()
{
// Team B!
	short user,maxu,au,max_au;
	signed char p;
	float max=-1;
	float d;

	if (auto_users_b)
	{
		if (last_user_b==auto_users_b)
			last_user_b=0;

		maxu=auto_users_list_b[last_user_b];

		if (++last_user_b==auto_users_b)
			last_user_b=0;

		au=last_user_b;
		max_au=au;

		for (short i=1; i<auto_users_b; i++)
		{
			if (au==auto_users_b)
				au=0;

			user=auto_users_list_b[au];
			p=users[user-1].plr;
			if (p<=0)
				d=1500;
			else
				d=(teams[p-1].tm_dist);

			if (d>max)
			{
				max=d;
				maxu=user;
				max_au=au;
			}
			au++;
		}
		auto_select_b(maxu);			// Team Control.
		if (!ball_poss)
			last_user_b=max_au;
	}
}

/******************************************************************************
*****************************************************************************/

void reselect()
{
	predict_ball();
	get_nearest();
	new_select=FALSE;		// Can be same player...
	closest=FALSE;
	reselect_a();
	reselect_b();
}

/******************************************************************************
*****************************************************************************/

void reselect_all_users()
{
	for (short i=0; i<num_of_users; i++)
	{
		reselect();
	}
}

/******************************************************************************
*****************************************************************************/

#ifdef FORCE_SELECT
void force_users()
{
	if (!match_mode && num_of_users)
	{
		short f_user;
		for (f_user=1; f_user<=MAX_USERS; f_user++)
		{
			if (!(forced&1))
				forced>>=1;
			else
				break;
		}

		short p=users[f_user-1].plr;
		short tm=(p<12 ? 12:23);
		for (short i=1; i<=10; i++)
		{
			if (++p==tm)
				p-=10;				// Can't be keeper!

			if (sel_circle[p-1] && !teams[p-1].control)
				break;
		}
		if (i!=11)
		{
// Successfull forced selection...
			if (p<12)
				last_plr_a=users[f_user-1].plr;
			else
				last_plr_b=users[f_user-1].plr;

			clear_auto(f_user);
			teams[p-1].control=f_user;
			users[f_user-1].chng=TRUE;				// changed control
			users[f_user-1].plr=p;
		}
	}
}
#endif

/******************************************************************************
*****************************************************************************/

void new_users()
{
#ifdef NO_AUTO_SEL
	if (!key_togs[0x43])
#endif

	if (ball_poss && num_of_users && !match_mode)
	{
// Normal play with users and some-one on ball!

		if (ball_travel++>select_cnt)
		{
			ball_travel=0;
			new_select=FALSE;		// Can be same player...
 			closest=TRUE;

  			reselect_a();
  			reselect_b();
		}
	}

#ifdef FORCE_SELECT
	if (forced)
		force_users();
#endif
}


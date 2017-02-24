#include <iostream.h>
#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
#include <i86.h>
#include <dos.h>
#include <conio.h>
#include <float.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include "defines.h"
#include "3deng.h"
#include "video.h"
#include "menu.h"
#include "control.h"
#include "unmangle.h"
#include "gamedata.h"
#include <math.h>

extern	int 		SelectedLEAGUEteam;
void			swapteamsPOSN();
void			randomize();
void 			initialise_matches();
void			CheckEndOfLine();
int			calculate_player_skill(int team_no, int position, int pitch_pos );
void			attemptGOAL( int team_a, int team_b, int time );
extern	void  		GOAL_SCORED( int team, int scorer, int time );
void			reset_scores();
char*			FindGOALSCORERSname( char credit, int player );
void			choose_cup_games();
extern			int formdata;
int 			rand_seed,seed;
int			TEAMa, TEAMb;
extern	int		Button_pressed;
extern	char		OverlayFlag;
extern	int		formation_toggle;
extern	int		selected_team;
extern	short		TabX,lineY;
extern	int		current_menu;
void	get_cup_venue();

//������������������������������������������������������������������������������������������������������������������������������ͻ 
//�                                                                                                                              �
//�  Resets teams division and position numbers when game is restarted.                                                          �
//�																 �
//������������������������������������������������������������������������������������������������������������������������������ͼ 
//
void	reset_league_teams()
{
}

//������������������������������������������������������������������������������������������������������������������������������ͻ 
//�                                                                                                                              �
//�  Sets up next fixture.                                                                                                       �
//�																 �
//������������������������������������������������������������������������������������������������������������������������������ͼ 
//
int	SortNEXTfixture(int match_number, int CompType)
{
	return	(match_number);
}


//������������������������������������������������������������������������������������������������������������������������������ͻ 
//�                                                                                                                              �
//�  Calculates neutral referee for network game.                                                                                �
//�																 �
//������������������������������������������������������������������������������������������������������������������������������ͼ 
//
void	recalc_referee()
{
}

//������������������������������������������������������������������������������������������������������������������������������ͻ 
//�                                                                                                                              �
//�  Initialises league program.                                                                                                 �
//�																 �
//������������������������������������������������������������������������������������������������������������������������������ͼ 
//
void initialise_matches()
{
}



//������������������������������������������������������������������������������������������������������������������������������ͻ 
//�                                                                                                                              �
//�  Choose cup fixtures.                                                                                                        �
//�																 �
//������������������������������������������������������������������������������������������������������������������������������ͼ 
//
void choose_cup_games()
{
}


//������������������������������������������������������������������������������������������������������������������������������ͻ 
//�                                                                                                                              �
//�  User pressed ESC while in match, we must now generate a result against the user.                                            �
//�																 �
//������������������������������������������������������������������������������������������������������������������������������ͼ 
//
void	quit_current_match()
{
}




//������������������������������������������������������������������������������������������������������������������������������ͻ 
//�                                                                                                                              �
//�  Calculates the result of a game between any two teams.                                                                      �
//�																 �
//������������������������������������������������������������������������������������������������������������������������������ͼ 
//
void	calculate_match()
{
}


//������������������������������������������������������������������������������������������������������������������������������ͻ 
//�                                                                                                                              �
//�  Sets up goal data after a goal has been scored, for later use when displaying scorers.                                      �
//�																 �
//������������������������������������������������������������������������������������������������������������������������������ͼ 
//
//void	GOAL_SCORED( int team, int scorer, int time )
//{
//	int	goal_slot	=	-1;
//	int	goal_count	=	0;
//
//		// FIND AN EMPTY GOAL SLOT WITHIN GOAL DATA...
//
//		while	( goal_slot==-1 )
//		{
//					
//			if ( goals[goal_count].goal_data.used == NULL )
//			{
//			 	goal_slot				=	goal_count;
//				goals[goal_slot].goal_data.used		=	ACTIVE;				
//			}
//		     	
//			else
//		
//			{
//			goal_count++;
//			
//				if ( goal_count>90 )
//				{
//					goals[0].goal_data.used	=	NULL;
//					goal_count		=	0;
//				}
//			}			
//		}
//
//
//	goals[goal_slot].goal_data.time		=	time+1;				
//
//		// CALCULATE NORMAL GOAL....
//
//
//		if	( (time & O_G)==0 )
//		{
//			
//			if ( scorer<11 )
//			{
//				goals[goal_slot].goal_data.scorer	=	game_data[setup.team_a].players[scorer].squad_number;	//was scorer-1
//				goals[goal_slot].goal_data.used|=		CREDIT_TEAMa;
//				match_info.team_a_score++;
//			}
//			else
//			{
//				goals[goal_slot].goal_data.scorer	=	game_data[setup.team_b].players[scorer-11].squad_number;   //was scorer-12
//				goals[goal_slot].goal_data.used|=		CREDIT_TEAMb;
//				match_info.team_b_score++;
//			}
//		}
//
//
//		// CALCULATE OWN GOAL....
//
//		if	( (time & O_G)!=0 )
//		{
//
//		goals[goal_slot].goal_data.used		=	O_G >> 8;				
//
//			if ( scorer<11 )     
//			{
//				goals[goal_slot].goal_data.scorer	=	game_data[setup.team_a].players[scorer].squad_number;	     //was scorer-1
//				goals[goal_slot].goal_data.used|=		CREDIT_TEAMb;
//				match_info.team_b_score++;
//			}
//
//			else
//			{
//				goals[goal_slot].goal_data.scorer	=	game_data[setup.team_b].players[scorer-11].squad_number;     //was scorer-12
//				goals[goal_slot].goal_data.used|=		CREDIT_TEAMa;
//				match_info.team_a_score++;
//			}
//		}
//}

//������������������������������������������������������������������������������������������������������������������������������ͻ 
//�                                                                                                                              �
//�  Calculates a players skill, depending on his stats and chosen position of play on field.                                    �
//�																 �
//������������������������������������������������������������������������������������������������������������������������������ͼ 
//
int	calculate_player_skill( int team_no, int position, int pitch_posn )
{
	return(NULL);
}

//������������������������������������������������������������������������������������������������������������������������������ͻ 
//�                                                                                                                              �
//�  Reset table holding data for goals and scorers.                                                                             �
//�																 �
//������������������������������������������������������������������������������������������������������������������������������ͼ 
//
void	reset_scores()
{
		// RESET BOTH TEAMS SCORES...

			match_info.team_a_score		=	NULL;
			match_info.team_b_score		=	NULL;

		// RESET TABLE HOLDING SCORERS...

			for (int table = 0; table < 91; table++)

			{
				goals[table].goal_data.used	=	NULL;
				goals[table].goal_data.time	=	NULL;
				goals[table].goal_data.scorer	=	NULL;
			}
}

//������������������������������������������������������������������������������������������������������������������������������ͻ 
//�                                                                                                                              �
//�  Display goal scorers for both teams.                                                                                        �
//�																 �
//������������������������������������������������������������������������������������������������������������������������������ͼ 
//

void	DisplayGOALscorers( char credit, int teams_goals )
{
}




//������������������������������������������������������������������������������������������������������������������������������ͻ 
//�                                                                                                                              �
//�  Checks for end of line and bottom bounding area when displaying scorers.                                                    �
//�																 �
//������������������������������������������������������������������������������������������������������������������������������ͼ 
//

void	CheckEndOfLine()
{
}

//������������������������������������������������������������������������������������������������������������������������������ͻ 
//�                                                                                                                              �
//�  Look for name of goal scorer using both players squad number and the team to whom the goal is credited.                     �
//�																 �
//������������������������������������������������������������������������������������������������������������������������������ͼ 
//
char*	FindGOALSCORERSname( char credit, int player )
{
	int	team;
	int	array_number	=	NULL;

 	if	( credit==CREDIT_TEAMa )
		team	=	setup.team_a;		
	else
		team	=	setup.team_b;		

	for (int playnum = 0; playnum < 22; playnum++)
	{
		if	( game_data[team].players[playnum].squad_number==player )	
     			array_number	=	playnum;
	}

	return	( game_data[team].players[array_number].name+game_data[team].players[array_number].goal_index );
}


//������������������������������������������������������������������������������������������������������������������������������ͻ 
//�                                                                                                                              �
//�  Control relegation and promotion stuff.                                                                                     �
//�																 �
//������������������������������������������������������������������������������������������������������������������������������ͼ 
//
void	SortNEWdivisions()
{
}

//������������������������������������������������������������������������������������������������������������������������������ͻ 
//�                                                                                                                              �
//�  Selects squad for computer controlled team.                                                                                 �
//�																 �
//������������������������������������������������������������������������������������������������������������������������������ͼ 
//
void	SortSQUAD(int team)
{
}



//������������������������������������������������������������������������������������������������������������������������������ͻ 
//�                                                                                                                              �
//�  Determins if user has selected arcade and auto game is required.                                                            �
//�																 �
//������������������������������������������������������������������������������������������������������������������������������ͼ 
//

void	SortARCADEleagueGAME()
{
}



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#include "eurodefs.h"
#include "euro_fxd.h"
#include "euro.equ"
#include "euro_sym.h"
#include "euro_def.h"
#include "euro_var.h"
#include "euro_grf.h"
#include "euro_dsk.h"
#include "euro_gen.h"
#include "euro_cnt.h"
#include "euro_int.h"


#include "defines.h"

void	RedrawSquadPanel();
void	ReplaceSquadBuffers( char );


//********************************************************************************************************************************

void	DisplayFormation( char AddToList )
	{
		int 	ball, shadow, player, width, height;
		float	x,y, snapx, shadx, shady;
		float	yscale, xscale, ysize, xdiff, wthscale;
		int	bscale;


		
	// *****  DISPLAY FORMATION TYPE AT FOOT OF SCREEN  ******

		char	*temp	=	GetTEXT( ((int)FormationInfo[Team] + FORM_LIST ));

		Image_Widths[INFO_NBAR+Lft]	=	Image_Widths[INFO_NBAR+Rgt]+FORMATION_BAR_WIDTH;


//		DrawIMAGE( &FrontendPseudoDEFN, &FrontendTextureDEFN, 
//				INFO_NBAR+Lft, NameBarXposn, 426, FORMATION_infoBOX, spritecopy );  
//		DrawIMAGE( &FrontendBackgroundDEFN, &FrontendTextureDEFN, 
//				INFO_NBAR+Lft, NameBarXposn, 426, FORMATION_infoBOX, spritecopy );  
//		DrawIMAGE( &FrontendPseudoDEFN, &FrontendTextureDEFN, 
//				INFO_NBAR+Rgt, NameBarXposn+Image_Widths[INFO_NBAR+Lft], 
//					426, FORMATION_infoBOX, spritecopy );  

//		if (Bounding_table[FORMATION_stringBOX].BoundingBoxLeft != -1 )
//
//			CopyFromBACKtoPSEUDObuffer(
//				&FrontendPseudoDEFN, &FrontendBackgroundDEFN,
//				Bounding_table[FORMATION_stringBOX].BoundingBoxLeft,
//				Bounding_table[FORMATION_stringBOX].BoundingBoxTop,
//		 		Bounding_table[FORMATION_stringBOX].BoundingBoxRight  - 
//		 		Bounding_table[FORMATION_stringBOX].BoundingBoxLeft,
//	 			Bounding_table[FORMATION_stringBOX].BoundingBoxBottom - 
// 				Bounding_table[FORMATION_stringBOX].BoundingBoxTop);
//

		DisplayString( NameBarXposn+38,			//Image_Widths[INFO_NBAR+Lft]-48,
				430, &temp[0],
				LARGE_FONT, 62, 
				FORMATION_stringBOX, 
				&FrontendPseudoDEFN, &FrontendTextureDEFN  );

		AddToDumpList( 	Bounding_table[FORMATION_stringBOX].BoundingBoxLeft,
				Bounding_table[FORMATION_stringBOX].BoundingBoxTop,
	 			Bounding_table[FORMATION_stringBOX].BoundingBoxRight  - 
	 			Bounding_table[FORMATION_stringBOX].BoundingBoxLeft,
		 		Bounding_table[FORMATION_stringBOX].BoundingBoxBottom - 
	 			Bounding_table[FORMATION_stringBOX].BoundingBoxTop);



	// ******  DISPLAY FORMATION LOTTO BALLS ONTO FORMATION PITCH  *****
	
  		for ( signed int s=9; s>-1; s -- )
		{
			player	=	(SquadInfo[(Team*20)+(s+1) ]);
			ball	=	player+FORM_IMGS;

				// get y-coord of ball.

			ysize	=	((float) PITCH_YPOS_BL-PITCH_YPOS_TL);   		// size of formation pitch in y.
			yscale	=	(1280/2) / ysize;					// scale down tactic y pos.
			y	=	(float) (TeamTactics[ (32*2)+5 ][s][0] / yscale ); 	// get actual formation y pos.

				// get x difference for each y pixel up formation pitch. (0.829114).

			xdiff	=	( (float) (((PITCH_XPOS_BR-PITCH_XPOS_BL) - (PITCH_XPOS_TR-PITCH_XPOS_TL)) / ysize));			 
			wthscale=	( (float) ( (PITCH_XPOS_BR-PITCH_XPOS_BL) - ((int)y) * xdiff) );					
				
				// calculate x scale for each pixel.
				
			xscale	=	( (float) ( (PITCH_XPOS_BR-PITCH_XPOS_BL) / wthscale) );

				// calculate converted formation x-coord.

			
			if ( (TeamTactics[ (32*2)+5 ][s][1] & 31) > 15 )
				snapx	=  ( (TeamTactics[ (32*2)+5 ][s][1] & 0xffe0) +32 );
			else
				snapx	=  (TeamTactics[ (32*2)+5 ][s][1] & 0xffe0);

			x	=	(float) ( (snapx / ( 800.0 / (PITCH_XPOS_BR-PITCH_XPOS_BL) ) )
							    / xscale );

			bscale	=	( (ysize-y) / (	( PITCH_YPOS_BL - PITCH_YPOS_TL ) /6) );
			ball+=  	(bscale*20);

			shadow	=	FBAL_SHDS+bscale;

			shady	=	( (ysize-y)+PITCH_YPOS_TL );
			y	=	shady - Image_Heights[ball];
			x	=	( x+PITCH_XPOS_BL) - (Image_Widths[ball] /2 );
			x	=	( x+ ((PITCH_XPOS_BR-PITCH_XPOS_BL) - (wthscale)) /2 );


			shady+=		(Image_Heights[shadow]/2);

			DrawIMAGE( &FrontendPseudoDEFN, &FrontendTextureDEFN, 
				   shadow, 
				   (int)x, (int)shady, s+21, 
				   spritefilter);  	// shadow filter for formation lotto balls.

			DrawIMAGE( &FrontendPseudoDEFN, &FrontendTextureDEFN, 
				   ball, 
				   (int)x, (int)y, s+21, 
				   spritecopy );  	// formation lotto balls.

			if ( AddToList != NULL )
			{
				width	= Bounding_table[s+21].BoundingBoxRight  - 
					Bounding_table[s+21].BoundingBoxLeft;
				height	= Bounding_table[s+21].BoundingBoxBottom - 
					Bounding_table[s+21].BoundingBoxTop;
				AddToDumpList( 
					Bounding_table[s+21].BoundingBoxLeft,
					Bounding_table[s+21].BoundingBoxTop,
					width, height );
			}
		}

	player	=	(SquadInfo[(Team*20)]);
	ball	=	player+FORM_IMGS+(5*20);

	DrawIMAGE( &FrontendPseudoDEFN, &FrontendTextureDEFN, 
		   FBAL_SHDS+5,
		   (int) ((PITCH_XPOS_BR-PITCH_XPOS_BL)/2) - (Image_Widths[ball] /2) + PITCH_XPOS_BL,
		   (int) PITCH_YPOS_BR-8+(Image_Heights[FBAL_SHDS+5]/2), 
		   32, 
		   spritefilter);

	DrawIMAGE( &FrontendPseudoDEFN, &FrontendTextureDEFN, 
		   ball, 
		   (int) ((PITCH_XPOS_BR-PITCH_XPOS_BL)/2) - (Image_Widths[ball] /2) + PITCH_XPOS_BL,
		   (int) PITCH_YPOS_BR-8-Image_Heights[ball], 
		   32, 
		   spritecopy );  	

	}

//********************************************************************************************************************************

void	ClearFormationMarkers()
	{
		short	width;
		short	height;
   
	      	for ( int b=21; b < 33; b++ )
		    {
			width	= Bounding_table[b].BoundingBoxRight  - 
					Bounding_table[b].BoundingBoxLeft;
			height	= Bounding_table[b].BoundingBoxBottom - 
					Bounding_table[b].BoundingBoxTop;
			CopyFromBACKtoPSEUDObuffer(
				&FrontendPseudoDEFN, &FrontendBackgroundDEFN,
				Bounding_table[b].BoundingBoxLeft,
				Bounding_table[b].BoundingBoxTop,
				width, height );

			AddToDumpList( 
				Bounding_table[b].BoundingBoxLeft,
				Bounding_table[b].BoundingBoxTop,
				width, height );

			Bounding_table[b].BoundingBoxLeft	=	-1;
			Bounding_table[b].BoundingBoxRight	=	-1;
			Bounding_table[b].BoundingBoxTop	=	-1;
			Bounding_table[b].BoundingBoxBottom	=	-1;
		    }

 		width	= Bounding_table[FORMATION_stringBOX].BoundingBoxRight  - 
 			  Bounding_table[FORMATION_stringBOX].BoundingBoxLeft;
 		height	= Bounding_table[FORMATION_stringBOX].BoundingBoxBottom - 
 			  Bounding_table[FORMATION_stringBOX].BoundingBoxTop;
		CopyFromBACKtoPSEUDObuffer(
			&FrontendPseudoDEFN, &FrontendBackgroundDEFN,
			Bounding_table[FORMATION_stringBOX].BoundingBoxLeft,
			Bounding_table[FORMATION_stringBOX].BoundingBoxTop,
			width, height );
		AddToDumpList( 
			Bounding_table[FORMATION_stringBOX].BoundingBoxLeft,
			Bounding_table[FORMATION_stringBOX].BoundingBoxTop,
			width, height );
	}
				
//********************************************************************************************************************************

	int FormationLabels[]={

	// 3-1-6

	FRPS_LBLE+Gk, FRPS_LBLE+Df, FRPS_LBLE+Df, FRPS_LBLE+Df, FRPS_LBLE+Md, FRPS_LBLE+Fw, FRPS_LBLE+Fw, FRPS_LBLE+Fw, FRPS_LBLE+Fw, FRPS_LBLE+Fw,  
	FRPS_LBLE+Fw, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, 
		
	// 4-0-6				     

	FRPS_LBLE+Gk, FRPS_LBLE+Df, FRPS_LBLE+Df, FRPS_LBLE+Df, FRPS_LBLE+Df, FRPS_LBLE+Fw, FRPS_LBLE+Fw, FRPS_LBLE+Fw, FRPS_LBLE+Fw, FRPS_LBLE+Fw,  
	FRPS_LBLE+Fw, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, 
		
	// 4-1-5				     

	FRPS_LBLE+Gk, FRPS_LBLE+Df, FRPS_LBLE+Df, FRPS_LBLE+Df, FRPS_LBLE+Df, FRPS_LBLE+Md, FRPS_LBLE+Fw, FRPS_LBLE+Fw, FRPS_LBLE+Fw, FRPS_LBLE+Fw,  
	FRPS_LBLE+Fw, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, 
		
	// 4-2-4				     

	FRPS_LBLE+Gk, FRPS_LBLE+Df, FRPS_LBLE+Df, FRPS_LBLE+Df, FRPS_LBLE+Df, FRPS_LBLE+Md, FRPS_LBLE+Md, FRPS_LBLE+Fw, FRPS_LBLE+Fw, FRPS_LBLE+Fw,  
	FRPS_LBLE+Fw, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, 
		
	// 4-3-3				     

	FRPS_LBLE+Gk, FRPS_LBLE+Df, FRPS_LBLE+Df, FRPS_LBLE+Df, FRPS_LBLE+Df, FRPS_LBLE+Md, FRPS_LBLE+Md, FRPS_LBLE+Md, FRPS_LBLE+Fw, FRPS_LBLE+Fw,  
	FRPS_LBLE+Fw, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, 
		
	// 4-4-2				     

	FRPS_LBLE+Gk, FRPS_LBLE+Df, FRPS_LBLE+Df, FRPS_LBLE+Df, FRPS_LBLE+Df, FRPS_LBLE+Md, FRPS_LBLE+Md, FRPS_LBLE+Md, FRPS_LBLE+Md, FRPS_LBLE+Fw,  
	FRPS_LBLE+Fw, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, 
		
	// 5-1-4				     

	FRPS_LBLE+Gk, FRPS_LBLE+Df, FRPS_LBLE+Df, FRPS_LBLE+Df, FRPS_LBLE+Df, FRPS_LBLE+Df, FRPS_LBLE+Md, FRPS_LBLE+Fw, FRPS_LBLE+Fw, FRPS_LBLE+Fw,  
	FRPS_LBLE+Fw, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, 
		
	// 5-2-3				     

	FRPS_LBLE+Gk, FRPS_LBLE+Df, FRPS_LBLE+Df, FRPS_LBLE+Df, FRPS_LBLE+Df, FRPS_LBLE+Df, FRPS_LBLE+Md, FRPS_LBLE+Md, FRPS_LBLE+Fw, FRPS_LBLE+Fw,  
	FRPS_LBLE+Fw, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, 
		
	// 5-3-2				     

	FRPS_LBLE+Gk, FRPS_LBLE+Df, FRPS_LBLE+Df, FRPS_LBLE+Df, FRPS_LBLE+Df, FRPS_LBLE+Df, FRPS_LBLE+Md, FRPS_LBLE+Md, FRPS_LBLE+Md, FRPS_LBLE+Fw,  
	FRPS_LBLE+Fw, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, 
		
	// 6-3-1				     

	FRPS_LBLE+Gk, FRPS_LBLE+Df, FRPS_LBLE+Df, FRPS_LBLE+Df, FRPS_LBLE+Df, FRPS_LBLE+Df, FRPS_LBLE+Df, FRPS_LBLE+Md, FRPS_LBLE+Md, FRPS_LBLE+Md,  
	FRPS_LBLE+Fw, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, FRPS_LBLE+Sb, 
		
				};

void	DisplayPositionLabels()
	{
		char	*string;
		short	PlyrIndex, Plyr;

  		for ( char s=0; s < 20; s ++ )
		{
			PlyrIndex = NormalisePlayer( s, Team );

		// get field position label if nessesary.

				string  =  GetTEXT ( FRPS_LBLE+Dr );

		// get substitute label if nessesary.

			if ( s < (11+NoOfSubs) )
			string	=  GetTEXT ( FormationLabels[ (s+(20*FormationInfo[Team])) ] );

		// get injured label if nessesary.

			if ( Fitness[PlyrIndex] < Injured )
				string  =  GetTEXT ( FRPS_LBLE+In );

		// get banned label if nessesary.

			if ( DiscPts[PlyrIndex] > 1 )
				string  =  GetTEXT ( FRPS_LBLE+Bn );

	   		DisplayString( 497-(PixelLengthOfString( string , SMALL_FONT) ) /2, 
   			     (103+(s*18)), string, 
   			     SMALL_FONT, SELECT_COLOUR, NO_BOX, &FrontendPseudoDEFN, &FrontendTextureDEFN  );
		}
      	}

//********************************************************************************************************************************

void	DisplaySquad()
	{
		int	PAL;
		short	PlyrIndex;

      		DisplayPositionLabels();

  		for ( char s=0; s < 20; s ++ )
		{
			PlyrIndex =	NormalisePlayer( s, Team );

			if ( DiscPts[PlyrIndex] > 1 || Fitness[PlyrIndex] < Injured )
				PAL	=  SELECT_COLOUR;
			else
				PAL	=	48;

			DisplayString( (500+21)-(PixelLengthOfString( GetTEXT( SQUD_NMBS+SquadInfo[ (Team*20)+s ]) ,SMALL_FONT) ) /2, 
			     (103+(s*18)), ( GetTEXT (SQUD_NMBS+SquadInfo[ (Team*20)+s ])) , 
			     SMALL_FONT, 24, s, &FrontendPseudoDEFN, &FrontendTextureDEFN  );

			DisplayString( (515+21),(103+(s*18)), 
				     ( GetPLAYERSname( SquadInfo[ (Team*20)+s ], Team, INITIAL_SURNAME )) , 
					SMALL_FONT, PAL, s, &FrontendPseudoDEFN, &FrontendTextureDEFN  );

			Bounding_table[s].BoundingBoxRight	=	639;

			MarkPlayer		=	-1;
			SquadBuffer1yposn	=	-1;
		}
	}

//********************************************************************************************************************************

void	DoSquadSelection( char MENU, signed char BOX, short xposn, short yposn )
	{
		if ( (MENU == SQUAD_SELECT || MENU == PLAYER_STATS) && LogicState == RUN_FRONTEND)
		{
				// display name of player being dragged into new position

			if (MarkPlayer!=-1)
			{
				SetupMouseLimits( 472, 626, 16, 452 );

				if ( ButtonState!=0 && ( BOX==MarkPlayer || BOX==-1 ) )
				{			
					RedrawSquadPanel();
				 	MarkPlayer	=	-1;
				     	DeBounce  	= 	TRUE;
				}
			}

			else
				SetupMouseLimits( 0, 626, 1, 452 );


			if ( MarkPlayer != -1 )
				{
				SquadBuffer1yposn	=	yposn-6;

				StorePSEUDObuffer( &FrontendPseudoDEFN, &FrontendTextureDEFN, DRAG_STOREbuff, 515, SquadBuffer1yposn );

				DisplayString( 515+21, SquadBuffer1yposn, 
				     ( GetPLAYERSname( SquadInfo[ (Team*20)+MarkPlayer ], Team, INITIAL_SURNAME )) , 
					SMALL_FONT, MOVE_COLOUR, NO_BOX, &FrontendPseudoDEFN, &FrontendTextureDEFN  );
						  
					AddToDumpList( 515, SquadBuffer1yposn,
					Image_Widths[DRAG_STOREbuff], Image_Heights[DRAG_STOREbuff] 
					);
			       	}

				// ***  choose a player from squad list.  ***
			
			if ( (MarkPlayer == -1) && (BOX != NO_BOX) && (BOX < 20) && (ButtonState==LEFT_BUTTON) )
				{
				 	MarkPlayer	=	BOX;

					DisplayString( 515+21, (103+(MarkPlayer*18)), 
					     ( GetPLAYERSname( SquadInfo[ (Team*20)+MarkPlayer ], Team, INITIAL_SURNAME )) , 
						SMALL_FONT, SELECT_COLOUR, MarkPlayer, &FrontendPseudoDEFN, &FrontendTextureDEFN  );
					AddToDumpList( 515+21, (103+(MarkPlayer*18)), 149, 18 );
				     	DeBounce  	= 	TRUE;
				}								 	
	   		
			else	

			if (MarkPlayer != -1 && ButtonState == RIGHT_BUTTON && BOX < 20 )

			{
				RedrawSquadPanel();
				MarkPlayer	  =  -1;
				SquadBuffer1yposn =  -1;
				ButtonState	  =  0;
			     	DeBounce  	  =  TRUE;
			}
				

		// Stop User From Viewing Stats Of Player Already Displayed

       			if ( MarkPlayer != -1 && (NormalisePlayer(MarkPlayer, Team)) == ViewPlyrStats 
				&& yposn<100 && MENU == PLAYER_STATS)
			{
					ReplaceSquadBuffers(Menu);
					RedrawSquadPanel();
					MarkPlayer	  =  -1;
			}			


			if ( MarkPlayer != -1  && 
			     BOX != NO_BOX     && 
			     BOX < 20 	       && 
			     BOX != MarkPlayer &&
			     ButtonState==LEFT_BUTTON )
			{
			     short PlyrIndex1 =	NormalisePlayer( BOX, Team );
			     short PlyrIndex2 =	NormalisePlayer( MarkPlayer, Team );
	
				if ( DiscPts[ PlyrIndex1 ] < 2 && 
				     DiscPts[ PlyrIndex2 ] < 2 &&
				     Fitness[ PlyrIndex1 ] > Injured &&	
				     Fitness[ PlyrIndex2 ] > Injured )
				{
					char p;
					p					=	SquadInfo[ (Team*20)+MarkPlayer ];
					SquadInfo[ (Team*20)+MarkPlayer ]	=	SquadInfo[ (Team*20)+BOX ];
					SquadInfo[ (Team*20)+BOX ]		=	p;
					RedrawSquadPanel();
					MarkPlayer		=	-1;
					SquadBuffer1yposn	=	-1;
				     	DeBounce  	= 	TRUE;

					if ( MENU == SQUAD_SELECT )
					{
						ClearFormationMarkers();
						DisplayFormation( NULL );
					}
				}
			}								 	

			
			if ( BOX == OPPONENT_TEAM_BOX && ButtonState!=0 && MENU == SQUAD_SELECT )
				{
					EUROteamView++;
					Team	=	ConfigureTeamView();

					if ( ButtonState != 0 )
						Animation_table[ViewTeamHandle].AnimationSpeed =
							WhichButton( ButtonState, 1.25);
					ChangeMenu	=	SQUAD_SELECT;
				     	DeBounce  	= 	TRUE;
				}								 	

			if ( (BOX == QUESTION_BOX && MarkPlayer != -1 && ButtonState!=0 && MENU == SQUAD_SELECT) ||
			     (BOX == QUESTION_BOX && MarkPlayer != -1 && 
			      (NormalisePlayer(MarkPlayer, Team)) != ViewPlyrStats && ButtonState!=0 
			       && MENU == PLAYER_STATS) )
			     
				{
					ViewPlyrStats 	=	NormalisePlayer( MarkPlayer, Team );
					ChangeMenu	=	PLAYER_STATS;
				     	DeBounce  	= 	TRUE;
				}								 	

 
			if ( (BOX == QUESTION_BOX && MarkPlayer == -1 && ButtonState!=0 && MENU == SQUAD_SELECT) ||
			     (BOX == QUESTION_BOX && MarkPlayer == -1 && ButtonState!=0 && MENU == PLAYER_STATS) )
				{
					EUROstatTeam	=	Team;
					ChangeMenu	=	TEAM_STATS;
				     	DeBounce  	= 	TRUE;
				}								 	
 
			if ( BOX == FORMATION_BOX && ButtonState != 0 && MENU == SQUAD_SELECT )
				{
					ClearFormationMarkers();

					if ( ButtonState == LEFT_BUTTON )
						FormationInfo[Team]--;
					else
						FormationInfo[Team]++;

					if ( FormationInfo[Team] < 0 )					
						FormationInfo[Team] = 9;
					if ( FormationInfo[Team] > 9 )					
						FormationInfo[Team] = 0;

					LoadTactics( ((int)FormationInfo[Team]), "..\\data\\euro.dat", &TeamTactics[0][0][0] );
					DisplayFormation( 1 );


					CopyFromBACKtoPSEUDObuffer(
						&FrontendPseudoDEFN, &FrontendBackgroundDEFN,
						484, 102, 25, 361 );
					AddToDumpList( 488, 102, 25, 361 );

					DisplayPositionLabels();
					
					if ( ButtonState == LEFT_BUTTON )
						Animation_table[FormationHandle].AnimationSpeed = -1.25;
					else
						Animation_table[FormationHandle].AnimationSpeed = 1.25;

				 	MarkPlayer	=	-1;
				     	DeBounce  	= 	TRUE;
				}								 	


			if ( BOX == RETURN_SQUAD_BOX && ButtonState != 0 && MENU == SQUAD_SELECT )
				{

					Animation_table[ReturnSqdHandle].AnimationSpeed = 
						WhichButton( ButtonState, 1.25);
				     	DeBounce  	= 	TRUE;

					if ( EUROgameType != EURO_championship )
						ChangeMenu	=	TEAM_SELECT;
					else
						ChangeMenu	=	NEXT_MATCH;

				}								 	
		}
	}

//********************************************************************************************************************************

void	RedrawSquadPanel()
	{
		CopyFromBACKtoPSEUDObuffer(
			&FrontendPseudoDEFN, &FrontendBackgroundDEFN,
			488+21, 100, 131, 364 );
		DisplaySquad();
		AddToDumpList( 488+21, 100, 131, 364 );
	}

//********************************************************************************************************************************

void	ReplaceSquadBuffers( char MENU )
	{
		if ( MENU == SQUAD_SELECT || MENU == PLAYER_STATS )
		{
			if ( SquadBuffer1yposn!=-1 )
			{

			      	DrawIMAGE( &FrontendPseudoDEFN, &FrontendTextureDEFN, DRAG_STOREbuff, 515, 
						SquadBuffer1yposn, NO_BOX, straightcopy );

				AddToDumpList(
				515,
				SquadBuffer1yposn,
				Image_Widths[DRAG_STOREbuff], 
				Image_Heights[DRAG_STOREbuff] 
				);
				SquadBuffer1yposn	=	-1;
			}
		}

	}

//********************************************************************************************************************************

void	DoInjuriesAndMatchBans( char GAMEtype, char Team )
	{
		char	LastPlyr, Swapped;
		short	PlyrIndex, Plyr;

//		if ( GAMEtype == EURO_championship )
		{
			LastPlyr = 19;
			Swapped	 = 1;
			
			while	( Swapped !=0 )
			{		

				// **** Find A Spot At The End Of The Squad List For Player To Be Swapped Into ****

				PlyrIndex =	NormalisePlayer( LastPlyr, Team );

				if ( DiscPts[PlyrIndex] > 1 || Fitness[PlyrIndex] < Injured )
				{
				  LastPlyr--;
				  if ( LastPlyr < 1 )	// **** checked all available players so bomb out and leave player 
				    Swapped = 0;	//      were he is ****
				}
			
				else


				{			
				  for ( char s=0; s < 11; s ++ )
				  {
				    Swapped = 0;
				    PlyrIndex =	NormalisePlayer( s, Team );

				    if ( DiscPts[PlyrIndex] > 1 || Fitness[PlyrIndex] < Injured )
				    {
				      char p = SquadInfo[ (Team*20)+s ];
				      SquadInfo[ (Team*20)+s ] = SquadInfo[ (Team*20)+LastPlyr ];
				      SquadInfo[ (Team*20)+LastPlyr ] =	p;
				      Swapped = 1;
										
				// **** Was This An Ideal Swap ****					

//				      if ( PlayerPosns[ (Team*20)+s ] != PlayerPosns[ (Team*20)+LastPlyr ] )
//				      {
//				      }




				    }						
				  }
				}
			}
		}
	}
	
//********************************************************************************************************************************


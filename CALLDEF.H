#ifndef _CALLDEF_H_INCLUDED
/*
 ษออออออออออออป
 บ AUTOHEADER บ
 ฬออออออออออออสออออออออออออออออออป
 บ Filename     CALLDEF.H        บ
 วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
 บ Creation     2/12/1994        บ
 ฬอออออออออออออออออออออออออออออออน
 บ                               บ
 บ Updated: Thu 31/8/1995 17:09  บ
 บ                               บ
 บ Version: 1.090                บ
 บ                               บ
 ศอออออออออออออออออออออออออออออออผ
 this is a file used by normality
 to access calls in 'rothlink.asm'
 the are "C" patches to my code plus extas
 functions.. if i need these functions
 they will be moved to rothcall.h
*/

#ifdef __cplusplus
extern "C" {
#endif
#ifndef ROTHLINK_H_INCLUDE
#include "rothlink.h"
#endif
#ifndef ROTHCALL_H_INCLUDE
#include "rothcall.h"
#endif
#ifndef _MEMSTRUC_H_INCLUDE
#include "memstruc.h"
#endif

// protocals for rothrend.lib


long int InitialiseRoth	(void);
void		FreeRoth		  	(void);

long int	AddRothObject	(_VIEW_Position *pos, char *DasName, char *AxxName);
void		RemoveRothObject(void);

void	   CleanUpRoth   	(void);
char *   GetRothErrorString	(long int);

void	   SetMovement   	(_MovementCTRL *);
void		GetXYZR 		  	(_VIEW_Position *);
void	   SetXYZR 		  	(_VIEW_Position *);
void	   SetR	 		  	(_VIEW_Position *);
void		SetWalkHight	( long int);
long int	DefineTilt		( long int);

void		SetScreen	  	(long int, long int);
void	   DefineScreen  	(long int, long int, long int, long int);
void	   DefineLens	  	(_LENS_Position *);

void		Add60HtzClock 	( void () );
void		Remove60HtzClock(void);

void		DOT_RequestWalkAbout( long int, long int);
void		RequestWalkAbout( signed long int, signed long int, long int);
long int	AreWeThereYet	(void);
long int	UpdateMovment	(void);
void		StopWalking		(void);
long int	WorkOnMovments (void);

long int DOT_Info      	(long int, _DOT_Info * , long *);
void	   DOT_MoveTo	  	(long int);
long int DOT_NameMyDOT 	(void);
long int DOT_Address 	(long int);
long int DOT_Locate		(long int);


long int Render 			(void);
void		CopyBuffer		(void);
void		RenderPart2		(void);
void		CopyBufferPart2(void);
void		SwitchPage		(long int);
void		WaitAtMost		(long int);
void		Display			(void);

long int	NameThatSegment(void);
long int	FreeASprite		(void);

void		LookXY			(long int, long int, _LookSee *);


void		DrawSprite		( long int,long int, _DrawObject *);
void		DrawSprite_Part2( long int,long int, _DrawObject *);

void		HideObject		( short int);
void		ShowObject		( short int);
char		ChangeObject	( short int,char);
short int LocateObject	( char );
short int LocateObjectI	( char );
short int LocateWall			( short int);
short int ConvertFaceWall	( short int);

char		ChangeWallTop	( short int, char );
char		ChangeWallMid	( short int, char );
char		ChangeWallBot	( short int, char );

void		ChangeGamma		( short int);

signed long int TiltView ( signed long int);

void		MySnapShot		( void);
void		MySaveBody		( void);
void		MyCloseSnap		( void);


void		SwitchRes	(void);
unsigned long int	ChangeFaceFlags ( long int ID, int on_flags, int off_flags);
unsigned long int	DistanceFromWall ( unsigned int WallOffset, unsigned int Distance);


long int	LocateSegment		( long int);
signed long int	EditSegment		( long int, signed long int, long int);


void 		PlayerWalk ( _WALK_List *, void * callback);
long int AddToWalkList( _WALK_List *, signed long int speed, signed long int angle);

_WALL_Block * 	ConvertWallAddress (unsigned short );
_FACE_Block * 	ConvertFaceAddress (unsigned short );
_SEG_Block * 	ConvertSegAddress (unsigned short );


void * GetDAN_GFXStart (_DAN_Image *);
int StopStartDAN (_DAN_Image *);
int NextDAN_File (_DAN_Image *);


void	SetImage_Callback(void *);


#ifdef __cplusplus
};
#endif






#define _CALLDEF_H_INCLUDED
#endif



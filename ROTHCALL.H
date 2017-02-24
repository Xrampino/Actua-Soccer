#ifndef ROTHCALL_H_INCLUDE
/*
 ษออออออออออออป
 บ AUTOHEADER บ
 ฬออออออออออออสออออออออออออออออออป
 บ Filename     ROTHCALL.H       บ
 วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
 บ Creation     12/8/1995        บ
 ฬอออออออออออออออออออออออออออออออน
 บ                               บ
 บ Updated: Tue 26/9/1995 13:35  บ
 บ                               บ
 บ Version: 1.037                บ
 บ                               บ
 ศอออออออออออออออออออออออออออออออผ
 these are direct calls to rothrend.lib
									mouseup.asm
*/

//#include "animlink.h"

#ifndef ROTHREND_H_INCLUDE
#include "rothrend.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

void		InstallDiv0	  	(long int, void *(cleanup)(void));
void		RemoveDiv0	  	(long int);

long int GetArrayFromSegID (unsigned short int segment, short int * list, long int max_list);
long int GetArrayFromSeg (long int segment_address, short int * list, long int max_list);
long int ChangeLightArray ( short int * list, signed long int light_adjust);


// these functions found in doorsupt.asm

_DoorStruct* IsDoorOpen ( short int );
_DoorStruct* OpenDoor 	( short int, void (*Door_CallBack)( _DoorStruct *) ,short Delay); // Delay=0 = Manual
_DoorStruct* CloseDoor 	( short int );

void		SetThePallete	( void);


long int InitMouse		( void );
void	   SetMouse			( _MOUSE * );
void		UpdateMouse		( void );
void		UpdateMouse_IRQ( void );
void		HideMouse		( void );
void		ShowMouse		( void );
void		SetMouseXY(short int,short int);


long int	SQROOT			(long int);

void		FrameCounter	(long int);


void		CreatePens		(int Many, RGB256_Pen *array, char *result);

void		DrawMap			(void * ScreenBuffer, int BufferYOffset, DrawMap_Table * );
void		GetScreenRatio (char * ratio_x, char * ration_y);

#ifdef __cplusplus
};
#endif


#define ROTHCALL_H_INCLUDE
#endif

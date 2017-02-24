#ifndef _ROTHLINK_H_INCLUDED
/*
 ษออออออออออออป
 บ AUTOHEADER บ
 ฬออออออออออออสออออออออออออออออออป
 บ Filename     ROTHLINK.H       บ
 วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
 บ Creation     23/11/1994       บ
 ฬอออออออออออออออออออออออออออออออน
 บ                               บ
 บ Updated: Sat 12/8/1995 00:32  บ
 บ                               บ
 บ Version: 1.097                บ
 บ                               บ
 ศอออออออออออออออออออออออออออออออผ
 this just contains data used by rothlink.asm
 rothrend.h contains rothrend.lib data strucs

*/



#ifndef ROTHREND_H_INCLUDE
#include "rothrend.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma PACK (1);
/* structure returned from AddRothObject */

typedef struct	_VIEW_Position { // Used by SetYZR,SetR,GetXYZR,AddRothObject
	signed long int XPos;  	//   Left <> Right
	signed long int YPos;	//     Up <> Down		(not forw/back)
	signed long int ZPos;	//Forward <> Backward
 unsigned long int Rotation;
} _VIEW_Position;

#define _SCM_ModeX	   12345
#define _SCM_Text			3
#define _SCM_VGA256		0x13

#define _SCF_Interlase	4
#define _SCF_Lores		0

#define _REQ_NoTurn		1	//RequestMove
#define _REQ_Turn			0


typedef struct	_LENS_Position { // Used by SetLens
  unsigned long int XAspect;
  unsigned long int YAspect;
  unsigned long int XCenter;
  unsigned long int YCenter;
  unsigned long int Flags;
  unsigned long int CamDist;
} _LENS_Position;

#define _LENF_Normal	   0
#define _LENF_Quad      0x03
#define _LENF_Double	   0x01
#define _LENF_Tall	   0x02
#define _LENF_Blur      0x100 //not imp yet.

#define Match_ID 0
#define Match_GFX 0x10000

typedef struct	_MovementCTRL { // Used by SetMovement();
  unsigned long int MaxWalkSpeed;
  unsigned long int MaxTurnSpeed;
  unsigned long int InitTurnSpeed;
  // this will get longer...
} _MovementCTRL;


// many = ( DOT_Info())		 // Used by DOT_Info
typedef struct	_DOT_Info {
  unsigned long  int Offset;		  
  unsigned short int Rotation;  //0-511
  unsigned short int ID;
} _DOT_Info;

// 								 // Used by DrawObject()
typedef struct	_DrawObject {
  unsigned char      ImageNo;	  	// Id see rothed	  
  unsigned char	   Dir;			// Direction .. zero normaly
  unsigned char	   Flags;	  	// see below
  unsigned char	   Info;	  		// see below
    signed short int EyeLevel;	// base of image (raise/lower)
} _DrawObject;

#define	DOF_Float	0x02		// DrawObject.Info contains hight



// flags for EditSegmnt
#define	ES_RoofHeightSet   	0x00000	// 
#define	ES_RoofHeightAdd   	0x08000	// 
#define	ES_FloorHeightSet   	0x00001	// 
#define	ES_FloorHeightAdd   	0x08001	// 
#define	ES_RoofGfxSet   	   0x00002	// 
#define	ES_FloorGfxSet   	   0x00003	// 

typedef struct	_WALK_Item {
  signed long int x;
  signed long int y;
} _WALK_Item;


typedef struct	_WALK_List {
  unsigned short int unused;
  unsigned short int many;
  			 _WALK_Item	adj[12];
} _WALK_List;

typedef struct	_Links {		 // offset in _LINK_AddressBase
    signed short int X;	    // x pos
    signed short int Y;     // y pos
  unsigned short int ID;    // ID of link dot
  unsigned short int Many;  // many connections followed by Many * _LinkItems
  // here are Many * LinkItems
} _Links;

typedef struct	_LinkItems {		 // Appears after _Links * Many
  unsigned short int Offset;	    // OFFSET16 to joining link base=_Link_AddressBase
    signed short int Angle;       // -Angle of line to it
} _LinkItems;




#pragma PACK ;

#define _ROTHLINK_H_INCLUDED
#ifdef __cplusplus
};
#endif
#endif


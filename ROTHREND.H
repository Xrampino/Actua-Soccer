#ifndef ROTHREND_H_INCLUDE
/*
 ษออออออออออออป
 บ AUTOHEADER บ
 ฬออออออออออออสออออออออออออออออออป
 บ Filename     ROTHREND.H       บ
 วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
 บ Creation     12/8/1995        บ
 ฬอออออออออออออออออออออออออออออออน
 บ                               บ
 บ Updated: Sat 12/8/1995 03:34  บ
 บ                               บ
 บ Version: 1.025                บ
 บ                               บ
 ศอออออออออออออออออออออออออออออออผ
*/

#ifdef __cplusplus
extern "C" {
#endif

#pragma PACK(1) ;



typedef struct	DrawMap_Table {
  signed long			center_x; // Player X << 16	(as in view pos struc)
  signed long			center_y; // Player Y << 16	(as in view pos struc)
  signed long			rot; 		// Player rotation	(as in view pos struc)
  unsigned short		size_x; 	// pixels across
  unsigned short		size_y; 	// pixels down

  unsigned short		scale; 	// 4096 = 1:1   4096/2 =1/2 size
  			  char		ratio_x;	// ratio of screen use GetScreenRatio(char *rationx, char*rationY)
   		  char		ratio_y;	// ratio of screen

  unsigned char      edge;	 	// colour for edge of map (BOLD)
  unsigned char      faint; 	// colour used for steps etc.
  unsigned char      doors; 	// doors are in this colour
  unsigned char      player; 	// colour of player
} DrawMap_Table;

typedef struct	RGB256_Pen {
  unsigned char      red;	// values 0-255
  unsigned char      green;
  unsigned char      blue;
} RGB256_Pen;

typedef struct	_LookSee { // Used by LookXY()					  / valid for types
  unsigned char      Filler;		//
  unsigned char      Type;			// see below					  /
  unsigned short int Image;		// image number or colour	  / 1-,2-,3-,4+
  unsigned short int ImageX;		// xpos in image				  / 1,2,3,4*
  unsigned short int ImageY;		// ypos in image				  / 1,2,3,4*
  unsigned short int WallOffset;	// use _ROOM_AddressBase	  / 3
  unsigned short int SegOffset;	// use _ROOM_AddressBase	  / 1,2,3,4
  unsigned short int Flags;		// see below					  / 1,2,3,4
  unsigned short int ObjOffset;	// use _OBJ_AddressBase		  / 4
  unsigned short int WallID;		//	ID if wall selected		  / 3
  unsigned short int SegID;		//	valid if not sky			  / 1,2,3,4
  unsigned short int ObjImage;	// image number of Object	  / 4
  unsigned char      ObjDir;		// direction of object		  / 4
  unsigned char      ObjFlags; 	// object flags see below	  / 4
  unsigned char		FaceInfo;		// Top Middle or bottom see below
  unsigned char      Filler00;		// even up to word size
  unsigned short int Filler01;		// even up to word size
} _LookSee;

typedef struct	_DoorStruct { // Used by LookXY()					  / valid for types
  unsigned short int Seg_Offset;	//	door segment
  unsigned char      Flags;		//
  signed   char      Dir;		   // rotation
  unsigned long int  Function;	// function address
  unsigned short int Timer;		// none manual door time
  signed   short int HVtxX;	   // X pos of hindge
  signed   short int HVtxY;    	// Y pos
  unsigned short int Bleed_Seg;	// segment door bleeds into
  unsigned short int View_Seg;	// segment towards player
  unsigned long int  Poly;		   //	Poly struct
  unsigned long int  Verts;		//	Vertices struct
  unsigned short int pad;
  unsigned short int ManyVerts;
} _DoorStruct;

// flags for _LookSee-->FaceInfo
#define face_middle 0
#define face_top 	  1
#define face_bottom 2

// - If image is an Janim etc.. then will = then anim frame image. 
//	  if Mono then image = colour	
//
//
// + Image of object +512, if ObjFlags = 3dobject then
//									image = image of the face
//									also, objects may show current anim frame
//									Use ObjImage for better result, as this is the
//									object number in rothed.
//
//	* If image is a 3dobject then will = X,Y of a single face.
//

// Type
#define LST_Nill		0				// image not found...
#define LST_Roof		1 				// image is a segment roof
#define LST_Floor		2				// image is a segment floor
#define LST_Wall		3				// image is a wall part
#define LST_Object	4				// image is an object
#define LST_Sky		5				// image is the sky

// Flags	(use bit test not compare)
#define LSF_NotMono		8		// Image Num = colour

// ObjFlags	(use bit test not compare)
#define LSOF_3DObj		1		// Image is a 3dObject


typedef struct	_ROOM_Block {			 // offset in ROOM_AddressBase_
  unsigned short int FileSize;	 // block size
  unsigned short int OffsetVert;// Vertex list
  unsigned short int OffsetSeg; // Segments (_SEG_Block)
  unsigned short int OffsetWall;// Walls
  unsigned short int OffsetFace;// Faces
  unsigned short int OffsetInfo;// Info
  unsigned short int OffsetLink;// Link (Map warp info)
} _ROOM_Block;

typedef struct	_OBJ_Block {			 // offset in _OBJ_AddressBase_
  signed   short int X;	//left right
  signed   short int Y; //near far
  unsigned char		ImageNo;
  unsigned char		Dir;
  unsigned char		Flags;
  unsigned char		ID;
  signed   short int Z; //up down
  unsigned short int ExtSeg;// Segment offset unknown
} _OBJ_Block;

// see Snd_Item in sounds.h for sound structs // offset in _SND_AddressBase_

// many segs = (_ROOM_Block.OffsetSeg)-2
typedef struct	_SEG_Block {	   // offset in ROOM_AddressBase_
    signed short int RoofHight;  //
    signed short int FloorHight; //
  unsigned short int Internal;   //	Internal work space
  unsigned char      RoofGfx;	   //	\ gfx stuff
  unsigned char      FloorGfx;   //	/
  unsigned char      Flags;      //	see below
  unsigned char      Glow;       //
  unsigned char      SuperLink;  //	Map number or Transparence drop
  unsigned char      Sides;      // number of walls
  unsigned short int WallOffset; //	offset (_WALL_Block)
  unsigned short int XYDispRoof; //	byte each for x and y
  unsigned short int XYDispFloor;//	""	  ""
  unsigned short int ID;			//
} _SEG_Block;

// Flags 
#define	SGF_SuperLinked	0x01	// map warp...
#define	SGF_Candle			0x02	// candle lit segment
#define	SGF_RoofScale		0x0c	// 0-3 roof scale
#define	SGF_FloorScale		0x30	// 0-3 floor scale



// many walls = (_ROOM_Block.OffsetWall)-2
typedef struct	_WALL_Block {	   // offset in _ROOM_AddressBase
  unsigned short int Vert1Offset;//	offset16 (_VERT_Block)
  unsigned short int Vert2Offset;//	offset16 (_VERT_Block)
  unsigned short int FaceOffset; //	offset16 (_FACE_Block)
  unsigned short int TSeg;       //	offset16 (_SEG_Block) (Inside(link back to seg))
  unsigned short int TSegBack;   //	offset16 (_SEG_Block) (behind wall)
  unsigned char  		Flags;   //	offset16 (_SEG_Block) (behind wall)
  unsigned char 		TriggerID;   //	offset16 (_SEG_Block) (behind wall)
} _WALL_Block;

#define WBF_StopPlayer 0x01




// many faces = (_ROOM_Block.OffsetFace)-2
typedef struct	_FACE_Block {	   // offset in _ROOM_AddressBase
  unsigned short int XSize;		//	BIT 15 = extended struc
  unsigned char      UpperGfx;	//	\
  unsigned char      LowerGfx;	//	Þ Gfx stuff
  unsigned char      WallGfx;		//	/
  unsigned char      Flags;		//	see below

  // extended struc only
  unsigned char      XShift;		//	image shift info
  unsigned char      YShift;		//
  unsigned short int ID; 			//
} _FACE_Block;

// flags
#define	FCF_Transparent		0x01	// 
#define	FCF_XFlip				0x02	// 
#define	FCF_ImageFit			0x04	// 
#define	FCF_TranFlag			0x08	// mono colour
#define	FCF_NoReflect			0x10	//
#define	FCF_HalfSize			0x20	//
#define	FCF_EdgeMap				0x40	//
#define	FCF_YEdge				0x80	//

// notes for face struct... 
// to save memory all duplicate FACE structs popint to the same address
// so if you know you are going to edit it, give it a unique ID, that way
// it cannot be packed.



// many verts = (_ROOM_Block.OffsetVert)-2
typedef struct	_VERT_Block {	   // offset in _ROOM_AddressBase
    signed long  int X;				// \after rotation
    signed long  int Z;				//	/
    signed short int StartX;		//
    signed short int StartZ;		//
} _VERT_Block;


typedef struct	_LINK_Block {	  // offset in _LINK_AddressBase
  unsigned short int FileSize;  // block size
  unsigned short int OffsetVert;// Vertex list
  unsigned short int ManyVert;  // many vertices
  unsigned short int InitVert;  // Where i start
  // this will get longer...
} _LINK_Block;

#pragma aux UserBreak="int 3";


typedef struct	_MOUSE {			 // offset in ROOM_AddressBase_
  unsigned  long int AddressPtrLo;		// Lores pointer \if same will dbl
  unsigned  long int AddressPtrHi;		// Hires pointer /hires version
  unsigned  long int HotSpotX; 			// coods into pointer
  unsigned  long int HotSpotY;			// "" ""
  unsigned  long int Speed;				// mouse speed 32=normal 16=*2 64=/2
} _MOUSE;




#pragma PACK ;



#ifdef __cplusplus
};
#endif


#define ROTHREND_H_INCLUDE
#endif


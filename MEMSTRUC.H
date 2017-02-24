#ifndef _MEMSTRUC_H_INCLUDED
/*
 ษออออออออออออป
 บ AUTOHEADER บ
 ฬออออออออออออสออออออออออออออออออป
 บ Filename     MEMSTRUC.H       บ
 วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
 บ Creation     28/7/1995        บ
 ฬอออออออออออออออออออออออออออออออน
 บ                               บ
 บ Updated: Thu 31/8/1995 11:07  บ
 บ                               บ
 บ Version: 1.031                บ
 บ                               บ
 ศอออออออออออออออออออออออออออออออผ
*/
#ifdef __cplusplus
extern "C" {
#endif

#define DASP_ID	'PSAD'
	//DASP in reverse

typedef struct	_DASP {
  char 	 				id_text[4];
  unsigned short int version;      
  unsigned short int size_sprite;
  unsigned long int  offset_sprite;
  unsigned long int  offset_palette;
  unsigned long int  offset_MONOcolours;
  unsigned long int  offset_names;
  unsigned short int size_names;
  unsigned short int size_anim;
  unsigned long int  offset_anim;
  unsigned short int filler00;
  unsigned short int skysprite;
  unsigned short int offset_object;
} _DASP;


typedef struct	_DASP_SPO {
  unsigned long int  offset;
  unsigned short int size;
  unsigned short int flags;
} _DASP_SPO;
#define SF2SPO_Packed		0x0001

#define MaxDasImages 4096
#define MaxDasObject 512


typedef struct	_DASP_COL {
  unsigned char 	 	palette[256*3];
  unsigned short int colblack;
  unsigned char 	 	shade1[256*32];
  unsigned char 	 	shade2[256*32];
  unsigned char 	 	tint[65536];
  unsigned char 	 	mirrorcon[256];
  unsigned char 	  	lightning[256];
} _DASP_COL;


// image structure callback
// there are 5 types of structure
// Test bits in (_Image.flags) in this order....
//
// 1) MemRef : if IF_MemRef;	(ANIM,DIR,DIR16), should never bee seen in callback
// 2) JANIM  : if IF_JANIM;   (JANIM,JDIR,JDIR16,JOINED)
// 3) DAN	 : if IF_Dan;
// 4) O3D	 : if IF_3dObj;
// 5) normal : if none of the above
//

typedef struct	_Image {
  unsigned char 	 	filler[8];
  unsigned short int segment;	 // allocated segment to refrence image
  unsigned short int flags;
  unsigned short int xsize;
  unsigned short int ysize;
} _Image;

// _Image.flags defines

#define	 IF_ShiftMask	0x000f
#define	 IF_Roof			0x0010
#define	 IF_MemRef		0x0020	// structure not define here
#define	 IF_JANIM		0x0040	// structure below
#define	 IF_HalfPix		0x0080
#define	 IF_Dan			0x0100	// structure below
#define	 IF_NotTran		0x0200
#define	 IF_Tint			0x0400
#define	 IF_Mirror		0x0800
#define	 IF_ImageBoost	0x6000
#define	 IF_3dObj		0x8000   // sturucture not define here
#define	 IF_ImageRot90	0x1000


typedef struct	_DAN_Image {
	_Image  header;
  unsigned long int filesize;
  unsigned short int HeadSize;	// offset to RAW sprite
  unsigned short int ManyFrames; 
  signed   short int CurrentFrame; // temp = CurrentFrame+2; if temp = ManyFrame then last frame in SEQ
  unsigned char      FrameClock;
  unsigned char      FrameSpeed;
  // now follows ManyFrames x dword offsets
} _DAN_Image;



typedef struct	_JANIM_Image {
	_Image  header;
  unsigned short int flags;
  // now follows ManyFrames x word offsets div 16
} _JANIM_Image;

//_JANIM_Images.flags defines

#define JIF_DIR	  0x8000
#define JIF_JOINED  0x4000
#define JIF_DIR16   0x2000
#define JIF_CntMask 0x0ffe	// cnt is always *2.. so add this for first frame


typedef struct	_Normal_Image {
	_Image  header;
   // image data start here
} _Normal_Image;


#define _MEMSTRUC_H_INCLUDED
#ifdef __cplusplus
};
#endif
#endif

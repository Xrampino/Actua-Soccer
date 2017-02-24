 					  
/********************************************************/														 
/*          3D ENGINE - Header File   17/01/95          */
/********************************************************/

#ifndef _3DENG_H_
#define _3DENG_H_


/**************/
/* DATA TYPES */

//Data size definitions
//use these as often as possible
typedef signed char byte;
typedef signed short word;
typedef signed int dword;
#ifndef BYTE
typedef unsigned char BYTE;
#endif
/*
#ifndef WORD
typedef unsigned short WORD;																 
#endif
#ifndef DWORD
typedef unsigned int DWORD;
#endif
*/
typedef float floatpt;

// Types used through 3D pipeline
typedef floatpt datapt;
typedef floatpt rotpt;
typedef dword scrpt;

// Word / Byte union
typedef union
	{
	struct {byte low,hiw;} d;
	word c;
	}
	dchar_u;

// DoubleWord / Word union
typedef union
	{
	struct {word low,hiw;} d;
	dword dw;
	}
	dword_u;



/**************/
/* MATH TYPES */

// General matrix type
typedef floatpt mat[4][4];

// Rotation matrix type (explicit for speed).
typedef union
	{
	mat arr;
	struct
		{
		floatpt r00,r01,r02,r03;
		floatpt r10,r11,r12,r13;
		floatpt r20,r21,r22,r23;
		}e;
	}
	qmat;



/*********************/
/* 3D GEOMETRY TYPES */

// 3D point & point-list types
typedef datapt *pt;
typedef datapt ptlist[];


// Face & face-list types
typedef word *face;
typedef word facelist[];


// Rotated point type
typedef rotpt *rpt;



/*********************/
/* 2D GEOMETRY TYPES */

// Screen point type
typedef struct
	{
	scrpt x,y;
	}
	pnt;

// Gourad screen point type
typedef struct
	{
	scrpt x,y,col;
	}
	ppnt;

// Screen point with z type (Bi-Quadratic mapping)
typedef struct
	{
	scrpt z,x,y;
	}
	zpnt;

// Screen polygon type (with average z for sort)
typedef struct
	{
	rotpt z;
	scrpt *pts;
	}
	pols;



/****************/
/* OBJECT TYPES */

// Object type
typedef struct
	{
	pt points;
	face faces;
	datapt x,y,z;
	floatpt crot,srot;
	}
	obj;

// Object list type
typedef struct
	{
	rotpt z;
	pols *polys;
	short nopols;
	}
	objs;

// Object detail level type
typedef struct
	{
	rotpt zscale; // min z/q for this detail level
	pt dpoints;
	face dfaces;
	}
	det;

// Object detail level list
typedef det detlist[];



/*****************/
/* SURFACE TYPES */

// Texture type
typedef dword texture[8]; // Assumes 4 pt textures, other nos of pts are padded out

// Polygon filter type
typedef BYTE filter[256];



/************************/
/* MOTION CAPTURE TYPES */

// Specific for players only
#define PLYRPTS 28

typedef datapt capfrm[PLYRPTS*3+1];

typedef struct
	{
	word cappts,capfrms;
	} mcap;



/*********************/
/* PLAYER INFO TYPES */

typedef struct
	{
	floatpt x,y,z,crot,srot,frame,fstep;
	short type,number,anim,sprite;
	BYTE htype,hcol;
	} plyrdat;

typedef struct
	{
	datapt *twnfrm;
	capfrm twnpts1,twnpts2;
	floatpt tween,tstep;
	short anim,animto;
	} plyrtwdat;



/**************/
/* MISC TYPES */

typedef struct
	{
	short sky;
	short stadia;
	short pitch;
	short players;
	short lines;
	short shadows;
	}
	detail_info;

// Setup data type
typedef struct
	{
	short M8;
	short team_a,team_b;
	short team_b_kit;
	short stadium;
	short vidi_type;
	short start_res;
	short screen_size;
	short verbose;
	detail_info detail; 
	}
	setup_info;

// Screen buffer info type
typedef struct
	{ 
	BYTE *buff_start;
	scrpt buff_wid,buff_hgt;
	scrpt clip_wid,clip_hgt;
	float scale_x,scale_y;
	void (*dump)(scrpt dispx,scrpt dispy);
	}
	buff_info;

// Extended screen buffer info type
typedef struct
	{ 
	BYTE *buff_start;
	BYTE *clip_end,*clip_endl;
	scrpt buff_wid,buff_hgt;
	scrpt clip_wid,clip_hgt,clip_widl,clip_hgtl;
	scrpt clip_xmid,clip_ymid;
	float scale_x,scale_y;
	void (*dump)(scrpt dispx,scrpt dispy);
	}
	buff_info_ext;

typedef struct {
	int pitchfile,pitchpfile;
	char skytypes[2];
	int tmdfile;
	int sb1file,sb2file;
	datapt s1x,s1y,s1z;
	int s1pfile,s1ffile;
	datapt s2x,s2y,s2z;
	int s2pfile,s2ffile;
	datapt s3x,s3y,s3z;
	int s3pfile,s3ffile;
	datapt s4x,s4y,s4z;
	int s4pfile,s4ffile;
	int st_w,st_l,st_h;
	short noloop;
	int loop[20];
	int vid1x,vid1y,vid1z;
	int vid2x,vid2y,vid2z;
	int tunlx,tunly,tunlz;
	int vmap;
	} 
	stad_info;

typedef struct {
	int headfile;
	int torsofile;
	int limbsfile;
	int nosfile;
	int palfile;
	int skinfile;
	int homepfile;
	int awaypfile;
	}
	teamk_info;



/***********************/
/* FUNCTION PROTOTYPES */

int init3d();
void setscreen();
void end3d();
void render3d(buff_info *buffer,datapt viewx,datapt viewy,datapt viewz,datapt targx,datapt targy,
              datapt targz,datapt vdist,plyrdat *plyrtb,datapt *xyz_ptr,word *ref_ptr);

#endif

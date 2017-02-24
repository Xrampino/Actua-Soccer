
/********************************************************/														 
/*           3D ENGINE - Football   13/04/95		        */
/********************************************************/

// By Laurent Noel

#include "defs.h"

/********************* HEADER FILES *********************/

#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <string.h>
#include <conio.h>
#include <i86.h>
#include <io.h>
#include <fcntl.h>
#include <direct.h>
#include <time.h>
#include <sys\stat.h>
#include "c:\sos\include\sos.h"
#include "c:\cgl\cgl.h"

#include "3deng.h"
#include "data.h"
#include "vesa.h"
#include "mallocx.h"

#ifdef BLASTER
#include "3dblast.h"
#else
#include "3dbnull.h"

#ifdef NEW
#include "eurodefs.h"
#include "euro_fxd.h"
#include "euro.equ"
#include "euro_sym.h"
#include "euro_def.h"
//#include "euro_var.h"
#include "euro_mem.h"
#include "euro_spt.h"
#include "euro_gen.h"
#include "euro_grf.h"
#include "euro_cnt.h"
#include "euro_dsk.h"
#include "euro_sqd.h"
#include "euro_sel.h"
#include "euro_fix.h"
#include "euro_usr.h"
#include "euro_inf.h"
#include "euro_gdv.h"
#include "euro_win.h"
//#include "euro_net.h"
#include "euro_cmd.h"
#include "euro_rnd.h"
#include "euro_int.h"
#endif

#define		TEMPa		0
#define		TEMPb		1



#endif

#ifdef JAPAN
#include "actrend.equ"
#include "fapj.equ"
#include "files.c"
#else
#ifndef FLOPPY
#include "actrend.equ"
#include "fap.equ"
#include "files.c"
#else
#ifndef BBS
#include "actrendf.equ"
#include "fapf.equ"
#include "filesf.c"
#else
#include "actrendb.equ"
#include "fapf.equ"
#include "filesb.c"
#endif
#endif
#endif

#include "fgfx.c"

#include "andydefs.h"
#include "defines.h"

										 
/***************** PRE-DEFINED CONSTANTS ****************/

#define SCREENDIST 15	// Screen clip plane z distance, set to avoid overflow
#define CUTOFFDIST 5		// Cutoff plane z distance (can be -ve!), set for nearest visibility

#define MAXOBJ	100		// Max number of objects in one sort
#define MAXPOL 1000		// Max number of polys in one sort
#define MAXPTS 500		// Max number of points in one object
#define MAXLOOP 100 		// Max number of looping maps

#define MAX_FILES 500

// Undefined in C++ (?!)
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))
#define abs(a) (((a)>=0)?(a):-(a))



/*********************** PROTOTYPES *********************/

// From render.c :

// Line Drawing
extern void line(pnt *pts,word col);					// Flat colour line
// Polygon drawing
extern void poly(pnt *pts,word np,word col);			// Flat colour overlapping
extern void polyb(pnt *pts,word np,word col);		// Flat colour
extern void polyf(pnt *pts,word np,filter col);		// Filtered
extern void polyg(ppnt *pts,word np);					// Gourad shading
extern void polym(pnt *pts,word np,word mapsel,		// Texture mapped
                  dword *startsx,dword *startsy);	
extern void polyl(pnt *pts,word np,word mapsel,		// Looping texture mapped
                  dword *startsx,dword *startsy);
extern void polyt(pnt *pts,word np,word mapsel,		// Transparent texture mapped
                  dword *startsx, dword *startsy);	
extern void polyq(zpnt *pts,word np,BYTE *map,		// Bi-Quadratic texture mapped
                  dword *startsx, dword *startsy); 
extern void sprite3d(short x,short y,short ref);	// Depth sorted sprites

// Dumps for various buffer types
void dumpMCGA(scrpt dispx,scrpt dispy);
void dumpMCGAs(scrpt dispx,scrpt dispy);
void dumpV256(scrpt dispx,scrpt dispy);
void dump3DB(scrpt dispx,scrpt dispy);
void dumpvidi1(scrpt dispx,scrpt dispy);
void dumpnull(scrpt dispx,scrpt dispy);

// Miscellaneous
extern int w95;				// Are we in Windows 95 (AAAARRRRRGGGGHHHHH!!!!)
extern float log_factor;	// No of logic frames/update
extern int testVESA;
extern char match_half;
extern char match_mode;


void draw_sprite(buff_info *buff,int sprite_no,int x,int y,BYTE col);
int draw_string(buff_info *buff,int font_no,int x,int y,char *string,BYTE col,short just);

#ifdef LINK
extern "C" char keys[128];		// Key pressed array (indexed by scan-code)
extern "C" char key_togs[128];// Key toggled array (indexed by scan-code)
extern "C" int icth,isth;		// Integer cos and sin of theta
extern "C" volatile int count;// Timer count
extern "C" network_on;			// Network game
#else
extern char keys[128];		// Key pressed array (indexed by scan-code)
extern char key_togs[128];	// Key toggled array (indexed by scan-code)
extern int icth,isth;		// Integer cos and sin of theta
extern volatile int count;	// Timer count
extern network_on;			// Network game
#endif

// Wind data
extern short wind_on;
extern float wind_x,wind_y;
extern float wind_speed;


/********************** GLOBAL VARS *********************/

// Setup data
setup_info setup;				// Initialisation data
int performance;		 		// Machine performance index

// Screen buffer info
buff_info main_buff;			// Current main screen buffer info
buff_info vidi_buff; 	   // Current vidi-buffer info
buff_info menu_buff; 	   // Current menu buffer info
buff_info_ext render_buff;	// Extended buffer info for rendering
word scrmode;					// (S)VGA mode number (including VESA)
word scrmode3DB;				// 3D Blaster mode number (-ve if not available)
CGL_COLOR_ST backcol={199,199,199,0};	// 3D Blaster background colour (temporary)
word menx3DB,meny3DB;		// Offset for menus on 3D Blastter
int mappages;					// No of texture-map pages being used

int texaddr3DB[16];			// Internal 3DB addresses for gfx
int skyaddr3DB,pitchaddr3DB;	// Internal 3DB addresses for gfx

BYTE *scr=(BYTE *)0xa0000;	// Address of (S)VGA display.

// Viewpoint vars
floatpt cth,sth,cph,sph;	// Cos & sin of theta and phi, the viewing angles
short q,oq;						// Perspective scaling
floatpt qr,qa;					// Precalculations derived from above
floatpt scrdr,persc;			// Used for 'alternative perspective scaling', see below
qmat rot,tran;					// Quick matrices for view and object rotation

// Object/polygon/point lists
objs *objlist;		// List of objects [object z, object polygon list]
objs *curobj;		// Current object pointer
pols *pollist;		// List of polygons [polygon z, polygon point list]
pols *curpol;		// Current polygon pointer
scrpt *ptslist;	// List of polygon point data [nsides, col, nsides*{x,y}]
scrpt *curpts;		// Current point pointer(!)
rotpt *rotlist;	// List of rotated pts for object
CGL_VERTEX2D_ST *curpts3DB;	// For 3D Blaster sprites
CGL_TEXTURE2D_ST *curtex3DB;	//         --"--

int clip_tex;		// Current clip texture map

plyrdat *ppt;

int timeit=0;

BYTE *dumplbm;
char dumpstr[]="dumpa.tga";

#ifdef COUNT
int numpols;	 	// Count for number of polygons drawn
#endif


floatpt mcap_ballx,mcap_bally,mcap_ballz;

/***************** INITIALISED STRUCTURES ***************/

// Unit matrix
mat unit=
	{
	{1.,0.,0.,0.},
	{0.,1.,0.,0.},
	{0.,0.,1.,0.},
	{0.,0.,0.,1.},
	};



//////////////////
// MEMORY AREAS //

// Texture map pages
#define X_BM 6  // Bitmap offset for extra maps
#define S_BM 8  // Bitmap offset for stand maps
#ifdef NEW
#define MAPPAGES (S_BM+8)
#else
#define MAPPAGES (S_BM+7)
#endif
#define MAPPAGES_4 (S_BM+2)

typedef BYTE mappage[256*256];

mappage *maps;

word mapsel[MAPPAGES+MAXLOOP+1];

BYTE *sky; // Sky map

BYTE pitch3DB[64*64]; // Pitch map (3D Blaster)


/////////////////
// SCREEN INFO //

// Space for main screen buffer
BYTE *scrb;

// VESA mode list
#define VESAMODES 2
int modelist[VESAMODES+1]={0x100,0x101,-1};

// Screen buffer information (w%8=0,h%2=0)
#define SCRSIZES 10
buff_info MCGA_buff[SCRSIZES]=
	{
	{NULL, 320,200, 320,200, 0.5,   0.5,   dumpMCGA},
	{NULL, 320,200, 296,184, 0.4625,0.46,  dumpMCGA},
	{NULL, 320,200, 320,158, 0.5,   0.3975,dumpMCGA},
	{NULL, 320,200, 264,166, 0.4125,0.4175,dumpMCGA},
	{NULL, 320,200, 296,142, 0.4625,0.355, dumpMCGA},
	{NULL, 320,200, 240,150, 0.375, 0.375, dumpMCGA},
	{NULL, 320,200, 264,124, 0.4125,0.3125,dumpMCGA},
	{NULL, 320,200, 216,132, 0.3375,0.3325,dumpMCGA},
	{NULL, 320,200, 240,108, 0.375, 0.2725,dumpMCGA},
	{NULL, 320,200, 216, 92, 0.3375,0.23,  dumpMCGA},
	};
buff_info VESA_buff[VESAMODES][SCRSIZES]=
	{
	 {
	  {NULL, 640,400, 640,400, 1,     1,     dumpV256},
	  {NULL, 640,400, 584,366, 0.9125,0.9175,dumpV256},
	  {NULL, 640,400, 640,316, 1,     0.79,  dumpV256},
	  {NULL, 640,400, 528,332, 0.825, 0.8325,dumpV256},
	  {NULL, 640,400, 584,284, 0.9125,0.71,  dumpV256},
	  {NULL, 640,400, 480,300, 0.75,  0.75,  dumpV256},
	  {NULL, 640,400, 528,250, 0.825, 0.625, dumpV256},
	  {NULL, 640,400, 424,266, 0.6625,0.6675,dumpV256},
	  {NULL, 640,400, 480,216, 0.75,  0.54,  dumpV256},
	  {NULL, 640,400, 424,184, 0.6625,0.46,  dumpV256},
	 },
	 {
	  {NULL, 640,480, 640,480, 1,     1.2, dumpV256},
	  {NULL, 640,480, 584,440, 0.9125,1.1, dumpV256},
	  {NULL, 640,480, 640,380, 1,     0.95,dumpV256},
	  {NULL, 640,480, 528,400, 0.825, 1,   dumpV256},
	  {NULL, 640,480, 584,340, 0.9125,0.85,dumpV256},
	  {NULL, 640,480, 480,360, 0.75,  0.9, dumpV256},
	  {NULL, 640,480, 528,300, 0.825, 0.75,dumpV256},
	  {NULL, 640,480, 424,320, 0.6625,0.8, dumpV256},
	  {NULL, 640,480, 480,260, 0.75,  0.65,dumpV256},
	  {NULL, 640,480, 424,220, 0.6625,0.55,dumpV256},
	 },
	};


#define MODES_3DB 6
#ifndef BLASTDEMO
int modelist3DB[MODES_3DB+1]={0,3,5,-1};
int modelist3DBh[MODES_3DB+1]={0,3,5,-1};
#else
int modelist3DB[MODES_3DB+1]={3,4,5,3,4,5,-1};
//int modelist3DB[MODES_3DB+1]={0,1,2,3,4,5,-1};
int modelist3DBh[MODES_3DB+1]={3,4,5,3,4,5,-1};
//int modelist3DBh[MODES_3DB+1]={3,4,5,0,1,2,-1};
#endif
buff_info buff_3DB[MODES_3DB]=
	{
 	 {NULL, 320,200, 320,200, 0.5,  0.5,   dump3DB},
 	 {NULL, 320,240, 320,240, 0.5,  0.6,   dump3DB},
	 {NULL, 640,350, 640,350, 1,    0.875, dump3DB},
  	 {NULL, 640,400, 640,400, 1,    1,     dump3DB},
	 {NULL, 640,480, 640,480, 1,    1.2,   dump3DB},
	 {NULL, 800,600, 800,600, 1.25, 1.5,   dump3DB},
	};

buff_info vidi_buff_1={NULL, 256,256, 128,80, 0.175,0.183, dumpnull};
buff_info vidi_buff_2={NULL, 256,256, 128,80, 0.175,0.183, dumpvidi1};

// Palette
BYTE pal[768];

// Polygon filters
#define FILTERS 2

filter *filters;



//////////////////////
// TEXTURE MAP INFO //


// Team players:
// Texture 13 (1+12): Head A (End 61 (1+5*12))
// Texture 73 (61+12): Head B (End 121 (61+5*12))
// Texture 133 (121+12): Torso A (End 181 (121+5*12))
// Texture 193 (181+12): Torso B (End 241 (181+5*12))
// Texture 244 (241+3): Lower Leg A (End 248 (241+7))
// Texture 251 (248+3): Upper Arm A (End 255 (248+7))
// Texture 258 (255+3): Upper Leg A (End 262 (255+7))
// Texture 265 (262+3): Lower Arm A (End 269 (262+7))
// Texture 272 (269+3): Lower Leg B (End 276 (269+7))
// Texture 279 (276+3): Upper Arm B (End 283 (276+7))
// Texture 286 (283+3): Upper Leg B (End 290 (283+7))
// Texture 293 (290+3): Lower Arm B (End 297 (290+7))
// Texture 309 (297+12): Foot (End 357 (297+5*12))


// Referee & keeper:
// Texture 369 (357+12): Torso Referee (End 417 (357+5*12))
// Texture 429 (417+12): Torso Keeper (End 477 (417+5*12))
// Texture 480 (477+3): Lower Leg Referee (End 484 (477+7))
// Texture 487 (484+3): Upper Arm Referee (End 491 (484+7))
// Texture 494 (491+3): Upper Leg Referee (End 498 (491+7))
// Texture 501 (498+3): Lower Arm Referee (End 505 (498+7))
// Texture 508 (505+3): Lower Leg Keeper (End 512 (505+7))
// Texture 515 (512+3): Upper Arm Keeper (End 519 (512+7))
// Texture 522 (519+3): Upper Leg Keeper (End 526 (519+7))
// Texture 529 (526+3): Lower Arm Keeper (End 533 (526+7))

#define X_TM 533		// Offset for extra maps
#define X_TM_NO (52+419)	// No of extra maps 
#define N_TM (X_TM+52)		// Alternate torsos
#define NT_TM (N_TM+412)	// Netting

#define S_TM X_TM+X_TM_NO	// Offset for stand maps
#define S_TM_MAX 500			// Maximum no of stadium maps

#define NOTEXTURES S_TM+S_TM_MAX


#define CLIP_TEXTURES 200

texture *textures;

// Misc looping textures
int noloop=6;
struct {
	int pos;
	texture tex;
	} texloop[]=
	{
	 {
	  0x1c040,
	  {0x000000,0x000000,0x3fff00,0x3fff00,
	   0x000000,0x3fff00,0x3fff00,0x000000}
	 },
	 {
	  0x1c040,
	  {0x000000,0x000000,0x1fff00,0x1fff00,
	   0x000000,0x3fff00,0x3fff00,0x000000}
	 },
	 {
	  0x1c040,
	  {0x000000,0x000000,0x7fff00,0x7fff00,
	   0x000000,0x7fff00,0x7fff00,0x000000}
	 },
	 {
	  0x1c080,
	  {0x000000,0x000000,0x3fff00,0x3fff00,
	   0x000000,0x7fff00,0x7fff00,0x000000}
	 },
	 {
	  0x1c040,
	  {0x000000,0x000000,0xbfff00,0xbfff00,
	   0x000000,0xbfff00,0xbfff00,0x000000}
	 },
	 {
	  0x1c0c0,
	  {0x000000,0x000000,0x5fff00,0x5fff00,
	   0x000000,0xbfff00,0xbfff00,0x000000}
	 },
	};


char *lang[6][29]=
{
	{
	"GOAL SCORED BY: ",
	"BOOKED, YELLOW CARD: ",
	"RED CARD, SENT OFF: ",
	"DIRECT FREE KICK",
	"INDIRECT FREE KICK",
	"PENALTY KICK",
	"CORNER KICK",
	"THROW IN",
	"GOAL KICK",
	"KICK OFF",
	"OFFSIDE",
	"PLAYER INJURED: ",
	"FULL TIME",
	"EXTRA TIME",
	"HALF TIME",
	"PENALTY SHOOTOUT",
	"FINAL SCORE AFTER PENALTIES",
	"OWN GOAL BY: ",
	"REPLAY",
	"SUBSTITUTION",
	"FORMATION",
	"CANCEL",
	"SELECT",
	"OFF",
	"SUBSTITUTE",
	"ON",
	"DONE",
	"OPTIONS",
	"REFEREE : ",
	},
	{
	"BUT DE: ",
	"AVERT., C. JAUNE: ",
	"C. ROUGE, RENV.: ",
	"COUP FR. DIRECT",
	"COUP FR. INDIR",
	"PENALTY",
	"CORNER",
	"TOUCHE",
	"TIR AU BUT",
	"CP. D<ENVOI",
	"HORS JEU",
	"JOUEUR BLESSE: ",
	"TPS TOTAL",
	"PROLONG.",
	"MI=TEMPS",
	"PENALTIES",
	"SCORE FINAL APRES PEN.",
	"BUT CTRE SOM CAMP DE: ",
	"REPLAY",
	"REMPLACEMENT",
	"FORMATION",
	"ANNULER",
	"SELECT",
	"OFF",
	"REMPLACANT",
	"ON",
	"FAIT",
	"OPTIONS",
	"ARBITRE : ",
	},
	{
	"TORSCHUETZE: ",
	"GELBE KARTE: ",
	"ROTE KARTE: ",
	"DIREKTER FREISTOSS",
	"FREISTOSS",
	"ELFMETER",
	"ECKBALL",
	"EINWURF",
	"ABSTOSS",
	"ANSTOSS",
	"ABSEITS",
	"SPIELER VERLETZT: ",
	"ABPFIFF",
	"VERLAENGERUNG",
	"HALBZEIT",
	"ELFMETERSCHIESSEN",
	"ERGEBNIS NACH ELFMETERSCHIESSEN",
	"EIGENTOR VON ",
	"WIEDERHOLUNG",
	"AUSWECHSLUNG",
	"AUFSTELLUNG",
	"ABBRUCH",
	"AUSWAEHLEN",
	"RAUS",
	"AUSWECHSELN",
	"REIN",
	"FERTIG",
	"OPTIONEN",
	"SCHIEDSRICHTER : ",
	},
	{
	"GOAL SCORED BY: ",
	"BOOKED, YELLOW CARD: ",
	"RED CARD, SENT OFF: ",
	"DIRECT FREE KICK",
	"INDIRECT FREE KICK",
	"PENALTY KICK",
	"CORNER KICK",
	"THROW IN",
	"GOAL KICK",
	"KICK OFF",
	"OFFSIDE",
	"PLAYER INJURED: ",
	"FULL TIME",
	"EXTRA TIME",
	"HALF TIME",
	"PENALTY SHOOTOUT",
	"FINAL SCORE AFTER PENALTIES",
	"OWN GOAL BY: ",
	"REPLAY",
	"SUBSTITUTION",
	"FORMATION",
	"CANCEL",
	"SELECT",
	"OFF",
	"SUBSTITUTE",
	"ON",
	"DONE",
	"OPTIONS",
	"REFEREE : ",
	},
	{
	"BUT DE: ",
	"AVERT., C. JAUNE: ",
	"C. ROUGE, RENV.: ",
	"COUP FR. DIRECT",
	"COUP FR. INDIR",
	"PENALTY",
	"CORNER",
	"TOUCHE",
	"TIR AU BUT",
	"CP. D<ENVOI",
	"HORS JEU",
	"JOUEUR BLESSE: ",
	"TPS TOTAL",
	"PROLONG.",
	"MI=TEMPS",
	"PENALTIES",
	"SCORE FINAL APRES PEN.",
	"BUT CTRE SOM CAMP DE: ",
	"REPLAY",
	"REMPLACEMENT",
	"FORMATION",
	"ANNULER",
	"SELECT",
	"OFF",
	"REMPLACANT",
	"ON",
	"FAIT",
	"OPTIONS",
	"ARBITRE : ",
	},
	{
	"M>L SCORET AV: ",
	"GULT KORT: ",
	"R&DT KORT, SENDT UT: ",
	"DIREKTE FRISPARK",
	"INDIREKTE FRISPARK",
	"STRAFFESPARK",
	"CORNER",
	"INNKAST",
	"UTSPILL FRA M>L",
	"AVSPARK",
	"OFFSIDE",
	"SKADD SPILLER: ",
	"FULL TID",
	"OVERTID",
	"HALVTID",
	"STRAFFEKONKURRANSE",
	"SLUTTRESULTAT ETTER STRAFFER",
	"SELVM>L VED: ",
	"REPRISE",
	"INNBYTTE",
	"FORMASJON",
	"AVBRYT",
	"VELG",
	"AV",
	"INNBYTTER",
	"P>",
	"FERDIG",
	"VALG",
	"DOMMER : ",
	},
};


// Stadia objects
#define MAX_STAD_PTS 400
#define MAX_STAD_FACES 400
obj stad1,stad2,stad3,stad4;
datapt stad1_p[MAX_STAD_PTS*3],stad2_p[MAX_STAD_PTS*3],stad3_p[MAX_STAD_PTS*3],stad4_p[MAX_STAD_PTS*3];
word stad1_f[MAX_STAD_FACES*6],stad2_f[MAX_STAD_FACES*6],stad3_f[MAX_STAD_FACES*6],stad4_f[MAX_STAD_FACES*6];
float st_w,st_l,st_h;


/********************* FUNCTION CODE ********************/

/*******************/
/* MATRIX ROUTINES */


void matcop(mat dest,mat src)
// Matrix copy
	{
	short i;
	floatpt *p0,*p1;
	p0=&dest[0][0];
	p1=&src[0][0];
	for (i=0;i<16;i++)
			*p0++=*p1++;

	}

void matmul(mat m1,mat m2)
// Matrix multiply
	{
	short i,j;

	mat res;
	floatpt *wr=&res[0][0];

	for (i=0;i<4;i++)
		for (j=0;j<4;j++)
			*wr++=m1[0][j]*m2[i][0]+
			      m1[1][j]*m2[i][1]+
			      m1[2][j]*m2[i][2]+
			      m1[3][j]*m2[i][3];

	matcop(m1,res);
	}

void matmultr(mat m1,mat m2)
// Reversed matrix multiply.
	{
	short i,j;

	mat res;
	floatpt *wr=&res[0][0];

	for (i=0;i<4;i++)
		for (j=0;j<4;j++)
			*wr++=m1[0][j]*m2[0][i]+
			      m1[1][j]*m2[1][i]+
			      m1[2][j]*m2[2][i]+
			      m1[3][j]*m2[3][i];

	matcop(m1,res);
	}



/*********************************************/
/* DRAW GROUND (SPECIALIZED TEXTURE MAPPING) */

//dword grtexx[]={0x00000000,0x003fffff,0x003fffff,0x00000000};
//dword grtexy[]={0x00000000,0x00000000,0x003fffff,0x003fffff};
dword grtexx[]={0x00000000,0x07ffffff,0x07ffffff,0x00000000};
dword grtexy[]={0x00000000,0x00000000,0x057fffff,0x057fffff};

void ground(float vr,float vwy,datapt vx,datapt vy,datapt vz)
	{
	scrpt y,ys[4],ye,yd;
	rotpt rx[4],ry[4],rz[4],ze;
	float t,d,z,tx,tz,dw1,dw2,sa,sw;

	BYTE *scr,*scrline,*cpyline;
	word w,flrsel,psh,pan;

	static dword td[5]={0,0,0,0,0};

	// Find highest pt of pitch
	ry[0]=-st_l*rot.e.r10+st_w*rot.e.r12+rot.e.r13;
	rz[0]=-st_l*rot.e.r20+st_w*rot.e.r22+rot.e.r23;
	ry[1]=(1280+st_l)*rot.e.r10+st_w*rot.e.r12+rot.e.r13;
	rz[1]=(1280+st_l)*rot.e.r20+st_w*rot.e.r22+rot.e.r23;
	ry[2]=(1280+st_l)*rot.e.r10-(800+st_w)*rot.e.r12+rot.e.r13;
	rz[2]=(1280+st_l)*rot.e.r20-(800+st_w)*rot.e.r22+rot.e.r23;
	ry[3]=-st_l*rot.e.r10-(800+st_w)*rot.e.r12+rot.e.r13;
	rz[3]=-st_l*rot.e.r20-(800+st_w)*rot.e.r22+rot.e.r23;

	if (scrmode3DB>=0)
		{
		rx[0]=-st_l*rot.e.r00+st_w*rot.e.r02+rot.e.r03;
		rx[1]=(1280+st_l)*rot.e.r00+st_w*rot.e.r02+rot.e.r03;
		rx[2]=(1280+st_l)*rot.e.r00-(800+st_w)*rot.e.r02+rot.e.r03;
		rx[3]=-st_l*rot.e.r00-(800+st_w)*rot.e.r02+rot.e.r03;

		CGL_VERTEX2D_ST *pts3d;
		CGL_TEXTURE3D_ST *tex3d;
		word np,p,pt,pl;
		short i,j,k;
		float fc,fc2;
		float tpts1[24];
		float tpts2[24];
		float ttex1[24];
		float ttex2[24];
		dword *polytexx,*polytexy;

		np=4;
		pt=0;
		for (j=0;j<np;j++)
			{
			k=j+1;
			if (k==np) k=0;
			if (rz[j]>=SCREENDIST)
				if (rz[k]>=SCREENDIST)
					{
					tpts2[pt]=rx[k];
					ttex2[pt++]=grtexx[k];
					tpts2[pt]=ry[k];
					ttex2[pt++]=grtexy[k];
					tpts2[pt++]=rz[k];
					}
				else
					{
					fc=(float)(rz[j]-SCREENDIST)/(rz[j]-rz[k]);
					tpts2[pt]=rx[j]+(fc*(rx[k]-rx[j]));
					ttex2[pt++]=grtexx[j]+(fc*(grtexx[k]-grtexx[j]));
					tpts2[pt]=ry[j]+(fc*(ry[k]-ry[j]));
					ttex2[pt++]=grtexy[j]+(fc*(grtexy[k]-grtexy[j]));
					tpts2[pt++]=SCREENDIST;
					}
			else
				if (rz[k]>=SCREENDIST)
					{
					fc=(float)(rz[k]-SCREENDIST)/(rz[k]-rz[j]);
					tpts2[pt]=rx[k]+(fc*(rx[j]-rx[k]));
					ttex2[pt++]=grtexx[k]+(fc*(grtexx[j]-grtexx[k]));
					tpts2[pt]=ry[k]+(fc*(ry[j]-ry[k]));
					ttex2[pt++]=grtexy[k]+(fc*(grtexy[j]-grtexy[k]));
					tpts2[pt++]=SCREENDIST;
					tpts2[pt]=rx[k];
					ttex2[pt++]=grtexx[k];
					tpts2[pt]=ry[k];
					ttex2[pt++]=grtexy[k];
					tpts2[pt++]=rz[k];
					}
			}
 

		for (j=0;j<pt;j+=3)
			{
			tpts2[j]=q*tpts2[j]/tpts2[j+2]+render_buff.clip_xmid;
			tpts2[j+1]=q*tpts2[j+1]/tpts2[j+2]+render_buff.clip_ymid;
			}

		SetPerspTextureQuadOutput3DB(texaddr3DB[0]);
		pts3d=&Vertex[0];
		tex3d=(CGL_TEXTURE3D_ST *)&Texture[0];

		p=0;
		for (j=0;j<pt;j+=3)
			{
			k=j+3;
			if (k==pt) k=0;
			if (tpts2[j]>=0)
				if (tpts2[k]>=0)
					{
					tpts1[p]=tpts2[k];
					ttex1[p++]=ttex2[k];
					tpts1[p]=tpts2[k+1];
					ttex1[p++]=ttex2[k+1];
					tpts1[p++]=tpts2[k+2];
					}
				else
					{
					fc=(float)tpts2[j]/(tpts2[j]-tpts2[k]);
					fc2=(float)tpts2[j+2]/(tpts2[k+2]*(float)-tpts2[k]/tpts2[j]+tpts2[j+2]);
					tpts1[p]=0;
					ttex1[p++]=ttex2[j]+(fc2*(ttex2[k]-ttex2[j]));
					tpts1[p]=tpts2[j+1]+(fc*(tpts2[k+1]-tpts2[j+1]));
					ttex1[p++]=ttex2[j+1]+(fc2*(ttex2[k+1]-ttex2[j+1]));
					tpts1[p++]=tpts2[j+2]+(fc2*(tpts2[k+2]-tpts2[j+2]));
					}
			else
				if (tpts2[k]>=0)
					{
					fc=(float)tpts2[k]/(tpts2[k]-tpts2[j]);
					fc2=(float)tpts2[k+2]/(tpts2[j+2]*(float)-tpts2[j]/tpts2[k]+tpts2[k+2]);
					tpts1[p]=0;
					ttex1[p++]=ttex2[k]+(fc2*(ttex2[j]-ttex2[k]));
					tpts1[p]=tpts2[k+1]+(fc*(tpts2[j+1]-tpts2[k+1]));
					ttex1[p++]=ttex2[k+1]+(fc2*(ttex2[j+1]-ttex2[k+1]));
					tpts1[p++]=tpts2[k+2]+(fc2*(tpts2[j+2]-tpts2[k+2]));
					tpts1[p]=tpts2[k];
					ttex1[p++]=ttex2[k];
					tpts1[p]=tpts2[k+1];
					ttex1[p++]=ttex2[k+1];
					tpts1[p++]=tpts2[k+2];
					}
			}
 
		pt=0;
		for (j=0;j<p;j+=3)
			{
			k=j+3;
			if (k==p) k=0;
			if (tpts1[j]<=render_buff.clip_wid)
				if (tpts1[k]<=render_buff.clip_wid)
					{
					tpts2[pt]=tpts1[k];
					ttex2[pt++]=ttex1[k];
					tpts2[pt]=tpts1[k+1];
					ttex2[pt++]=ttex1[k+1];
					tpts2[pt++]=tpts1[k+2];
					}
				else
					{
					fc=(float)(render_buff.clip_wid-tpts1[j])/(tpts1[k]-tpts1[j]);
					fc2=(float)tpts1[j+2]/(tpts1[k+2]*(float)(tpts1[k]-render_buff.clip_wid)/(render_buff.clip_wid-tpts1[j])+tpts1[j+2]);
					tpts2[pt]=render_buff.clip_wid;
					ttex2[pt++]=ttex1[j]+(fc2*(ttex1[k]-ttex1[j]));
					tpts2[pt]=tpts1[j+1]+(fc*(tpts1[k+1]-tpts1[j+1]));
					ttex2[pt++]=ttex1[j+1]+(fc2*(ttex1[k+1]-ttex1[j+1]));
					tpts2[pt++]=tpts1[j+2]+(fc2*(tpts1[k+2]-tpts1[j+2]));
					}
			else
				if (tpts1[k]<=render_buff.clip_wid)
					{
					fc=(float)(render_buff.clip_wid-tpts1[k])/(tpts1[j]-tpts1[k]);
					fc2=(float)tpts1[k+2]/(tpts1[j+2]*(float)(tpts1[j]-render_buff.clip_wid)/(render_buff.clip_wid-tpts1[k])+tpts1[k+2]);
					tpts2[pt]=render_buff.clip_wid;
					ttex2[pt++]=ttex1[k]+(fc2*(ttex1[j]-ttex1[k]));
					tpts2[pt]=tpts1[k+1]+(fc*(tpts1[j+1]-tpts1[k+1]));
					ttex2[pt++]=ttex1[k+1]+(fc2*(ttex1[j+1]-ttex1[k+1]));
					tpts2[pt++]=tpts1[k+2]+(fc2*(tpts1[j+2]-tpts1[k+2]));
					tpts2[pt]=tpts1[k];
					ttex2[pt++]=ttex1[k];
					tpts2[pt]=tpts1[k+1];
					ttex2[pt++]=ttex1[k+1];
					tpts2[pt++]=tpts1[k+2];
					}
			}

		p=0;
		for (j=0;j<pt;j+=3)
			{
			k=j+3;
			if (k==pt) k=0;
			if (tpts2[j+1]>=0)
				if (tpts2[k+1]>=0)
					{
					tpts1[p]=tpts2[k];
					ttex1[p++]=ttex2[k];
					tpts1[p]=tpts2[k+1];
					ttex1[p++]=ttex2[k+1];
					tpts1[p++]=tpts2[k+2];
					}
				else
					{
					fc=(float)tpts2[j+1]/(tpts2[j+1]-tpts2[k+1]);
					fc2=(float)tpts2[j+2]/(tpts2[k+2]*(float)-tpts2[k+1]/tpts2[j+1]+tpts2[j+2]);
					tpts1[p]=tpts2[j]+(fc*(tpts2[k]-tpts2[j]));
					ttex1[p++]=ttex2[j]+(fc2*(ttex2[k]-ttex2[j]));
					tpts1[p]=0;
					ttex1[p++]=ttex2[j+1]+(fc2*(ttex2[k+1]-ttex2[j+1]));
					tpts1[p++]=tpts2[j+2]+(fc2*(tpts2[k+2]-tpts2[j+2]));
					}
			else
				if (tpts2[k+1]>=0)
					{
					fc=(float)tpts2[k+1]/(tpts2[k+1]-tpts2[j+1]);
					fc2=(float)tpts2[k+2]/(tpts2[j+2]*(float)-tpts2[j+1]/tpts2[k+1]+tpts2[k+2]);
					tpts1[p]=tpts2[k]+(fc*(tpts2[j]-tpts2[k]));
					ttex1[p++]=ttex2[k]+(fc2*(ttex2[j]-ttex2[k]));
					tpts1[p]=0;
					ttex1[p++]=ttex2[k+1]+(fc2*(ttex2[j+1]-ttex2[k+1]));
					tpts1[p++]=tpts2[k+2]+(fc2*(tpts2[j+2]-tpts2[k+2]));
					tpts1[p]=tpts2[k];
					ttex1[p++]=ttex2[k];
					tpts1[p]=tpts2[k+1];
					ttex1[p++]=ttex2[k+1];
					tpts1[p++]=tpts2[k+2];
					}
			}

		pt=0;
		for (j=0;j<p;j+=3)
			{
			k=j+3;
			if (k==p) k=0;
			if (tpts1[j+1]<=render_buff.clip_hgtl)
				if (tpts1[k+1]<=render_buff.clip_hgtl)
					{
					pts3d[pt].x=(int)tpts1[k]<<16;
					tex3d[pt].s=ttex1[k];
					pts3d[pt].y=(int)tpts1[k+1]<<16;
					tex3d[pt].t=ttex1[k+1];
					tex3d[pt++].q=tpts1[k+2];
					}
				else
					{
					fc=(float)(render_buff.clip_hgtl-tpts1[j+1])/(tpts1[k+1]-tpts1[j+1]);
					fc2=(float)tpts1[j+2]/(tpts1[k+2]*(float)(tpts1[k+1]-render_buff.clip_hgt)/(render_buff.clip_hgt-tpts1[j+1])+tpts1[j+2]);
					pts3d[pt].x=(int)(tpts1[j]+(fc*(tpts1[k]-tpts1[j])))<<16;
					tex3d[pt].s=ttex1[j]+(int)(fc2*(ttex1[k]-ttex1[j]));
					pts3d[pt].y=render_buff.clip_hgtl<<16;
					tex3d[pt].t=ttex1[j+1]+(int)(fc2*(ttex1[k+1]-ttex1[j+1]));
					tex3d[pt++].q=tpts1[j+2]+(int)(fc2*(tpts1[k+2]-tpts1[j+2]));
					}
			else
				if (tpts1[k+1]<=render_buff.clip_hgtl)
					{
					fc=(float)(render_buff.clip_hgtl-tpts1[k+1])/(tpts1[j+1]-tpts1[k+1]);
					fc2=tpts1[k+2]/(tpts1[j+2]*(float)(tpts1[j+1]-render_buff.clip_hgt)/(render_buff.clip_hgt-tpts1[k+1])+tpts1[k+2]);
					pts3d[pt].x=(int)(tpts1[k]+(fc*(tpts1[j]-tpts1[k])))<<16;
					tex3d[pt].s=ttex1[k]+(int)(fc2*(ttex1[j]-ttex1[k]));
					pts3d[pt].y=render_buff.clip_hgtl<<16;
					tex3d[pt].t=ttex1[k+1]+(int)(fc2*(ttex1[j+1]-ttex1[k+1]));
					tex3d[pt++].q=tpts1[k+2]+(int)(fc2*(tpts1[j+2]-tpts1[k+2]));
					pts3d[pt].x=(int)tpts1[k]<<16;
					tex3d[pt].s=ttex1[k];
					pts3d[pt].y=(int)tpts1[k+1]<<16;
					tex3d[pt].t=ttex1[k+1];
					tex3d[pt++].q=tpts1[k+2];
					}
			}

		p=0;
		pl=pt;
		while (pl>4)
			{
			p+=4;
			pt+=2;
			pl-=2;
			for (j=pt-1;j>p;j--)
				{
				pts3d[j].x=pts3d[j-2].x;
				pts3d[j].y=pts3d[j-2].y;
				tex3d[j].s=tex3d[j-2].s;
				tex3d[j].t=tex3d[j-2].t;
				tex3d[j].q=tex3d[j-2].q;
				}
			pts3d[p].x=pts3d[0].x;
			pts3d[p].y=pts3d[0].y;
			tex3d[p].s=tex3d[0].s;
			tex3d[p].t=tex3d[0].t;
			tex3d[p].q=tex3d[0].q;
			}
		p+=pl;
		if (pl==3)
			{
			pts3d[p].x=pts3d[0].x;
			pts3d[p].y=pts3d[0].y;
			tex3d[p].s=tex3d[0].s;
			tex3d[p].t=tex3d[0].t;
			tex3d[p].q=tex3d[0].q;
			p++;
			}

		int mz;
		float tq;
		for (k=0;k<p;k+=4)
			{
			mz=tex3d[k].q;
			for (j=1;j<4;j++)
				if (tex3d[k+j].q<mz) mz=tex3d[k+j].q;
			for (j=0;j<4;j++)
				{
				tq=(float)mz/tex3d[k+j].q;
				tex3d[k+j].s*=tq;
				tex3d[k+j].t*=tq;
				tex3d[k+j].q=tq*65536;
				}
			}

		pts3d+=p;
		tex3d+=p;


		if ((p=pts3d-Vertex)>0)
			{
			SetPerspTextureQuadOutput3DB(pitchaddr3DB);
			Render3DB(p);
			}

		// Find lowest pt of sky
		#define ST_DP 200
		ry[0]=-(st_l+ST_DP)*rot.e.r10+st_h*rot.e.r11+(st_w+ST_DP)*rot.e.r12+rot.e.r13;
		rz[0]=-(st_l+ST_DP)*rot.e.r20+st_h*rot.e.r21+(st_w+ST_DP)*rot.e.r22+rot.e.r23;
		ry[1]=(1280+st_l+ST_DP)*rot.e.r10+st_h*rot.e.r11+(st_w+ST_DP)*rot.e.r12+rot.e.r13;
		rz[1]=(1280+st_l+ST_DP)*rot.e.r20+st_h*rot.e.r21+(st_w+ST_DP)*rot.e.r22+rot.e.r23;
		ry[2]=(1280+st_l+ST_DP)*rot.e.r10+st_h*rot.e.r11-(800+st_w+ST_DP)*rot.e.r12+rot.e.r13;
		rz[2]=(1280+st_l+ST_DP)*rot.e.r20+st_h*rot.e.r21-(800+st_w+ST_DP)*rot.e.r22+rot.e.r23;
		ry[3]=-(st_l+ST_DP)*rot.e.r10+st_h*rot.e.r11-(800+st_w+ST_DP)*rot.e.r12+rot.e.r13;
		rz[3]=-(st_l+ST_DP)*rot.e.r20+st_h*rot.e.r21-(800+st_w+ST_DP)*rot.e.r22+rot.e.r23;

		if (rz[0]>0)
			ye=q*ry[0]/rz[0],ze=rz[0];
		else 
			ye=render_buff.clip_ymid,ze=0;
		if (rz[1]>ze) ye=q*ry[1]/rz[1],ze=rz[1];
		if (rz[2]>ze) ye=q*ry[2]/rz[2],ze=rz[2];
		if (rz[3]>ze) ye=q*ry[3]/rz[3],ze=rz[3];
		if (ye<=-render_buff.clip_ymid) ye=-render_buff.clip_ymid+1;

		if (ye<render_buff.clip_ymid)
			{
			SetRectangleOutput3DBx(skyaddr3DB);
			Vertex[0].x=render_buff.clip_widl<<16;
			Vertex[0].y=render_buff.clip_hgt<<16;
			Vertex[1].x=0;
			Vertex[1].y=(ye+render_buff.clip_ymid)<<16;

			sa=atan(512/(q*512/(640*((render_buff.scale_x+render_buff.scale_y)/2))));
			if (sth<0)
				{
				Texture[0].s=((int)(512*acos((double)cth)/sa)%512)<<16;
				Texture[1].s=(511+((int)(512*acos((double)cth)/sa)%512))<<16;
				}
			else
				{
				Texture[0].s=-((int)(512*acos((double)cth)/sa)%512)<<16;
				Texture[1].s=(511-((int)(512*acos((double)cth)/sa)%512))<<16;
				}
			Texture[0].t=((256*(ye+render_buff.clip_ymid))/render_buff.clip_hgt)<<16;
			Texture[1].t=255<<16;
			Render3DB(2);
			}

		return;
		}

	if (setup.detail.pitch)
		{	
		if (rz[0]>0)
			ye=q*ry[0]/rz[0],ze=rz[0];
		else 
			ye=-render_buff.clip_ymid,ze=0;
		if (rz[1]>ze) ye=q*ry[1]/rz[1],ze=rz[1];
		if (rz[2]>ze) ye=q*ry[2]/rz[2],ze=rz[2];
		if (rz[3]>ze) ye=q*ry[3]/rz[3],ze=rz[3];
		if (ye>render_buff.clip_ymid) ye=render_buff.clip_ymid;

		scrline=render_buff.clip_end+render_buff.clip_wid;
		y=-render_buff.clip_ymid;
		t=q*sph+y*cph;						// Repeated divisor & incrementor

		while (t<0 && y<ye)
			{				 
			d=vy/t;								// Depth (unscaled)
			z=d*(q*cph-y*sph);				// Floor depth
			tx=vx-z*sth;						// X pos of pt
			tz=-vz-z*cth;						// Z pos of pt

			dw2=-d*sth;
			dw1=d*cth;
			if (setup.detail.pitch==1)
				{
				psh=15;
				pan=0x1f1f;
				flrsel=mapsel[mappages+noloop];
				}
			else
				{
				psh=16;
				pan=0x3f3f;
				flrsel=mapsel[mappages+noloop+1];
				}
			td[1]=(dword)((tz-dw2*render_buff.clip_xmid)*(1<<psh));
			td[2]=(dword)((tx-dw1*render_buff.clip_xmid)*(1<<psh));
			td[3]=(dword)(dw2*(1<<psh))&0xffffff;
			td[4]=(dword)(dw1*(1<<psh))&0xffffff;

			y++;
			t+=cph;

			scr=scrline;
			w=render_buff.clip_wid;
			//Assembly burst for pitch scan line
			extern void hlinp1(void);
			#pragma aux hlinp1=\
				".486"\
  				"push	ebp"\
				"push	ds"\
				"mov	esi,td[2]"\
				"mov	si,pan"\
				"mov	edx,td[10]"\
				"mov	bx,word ptr td[18]"\
				"mov	ecx,td[14]"\
				"mov	ch,bl"\
				"and	cx,si"\
				"mov	ebx,td[6]"\
				"mov	bh,dl"\
				"mov	dx,0"\
				"mov	di,w"\
				"mov	ax,flrsel"\
				"mov	ds,ax"\
				"mov	ebp,scr";
			extern void hlinp2(void);
			#pragma aux hlinp2=\
				"lpp:"\
				"and	bx,si"\
				"mov	al,[bx]"\
				"add 	esi,edx"\
				"adc	ebx,ecx"\
				"adc	bh,dh"\
				"and	bx,si"\
				"mov	ah,[bx]"\
				"add 	esi,edx"\
				"adc	ebx,ecx"\
				"adc	bh,dh"\
				"and	bx,si"\
				"bswap eax"\
				"mov	ah,[bx]"\
				"add 	esi,edx"\
				"adc	ebx,ecx"\
				"adc	bh,dh"\
				"and	bx,si"\
				"mov	al,[bx]"\
				"add 	esi,edx"\
				"adc	ebx,ecx"\
				"adc	bh,dh"\
				"mov	-4[ebp],eax"\
				"and	bx,si"\
				"mov	al,[bx]"\
				"add 	esi,edx"\
				"adc	ebx,ecx"\
				"adc	bh,dh"\
				"and	bx,si"\
				"mov	ah,[bx]"\
				"add 	esi,edx"\
				"adc	ebx,ecx"\
				"adc	bh,dh"\
				"and	bx,si"\
				"bswap eax"\
				"mov	ah,[bx]"\
				"add 	esi,edx"\
				"adc	ebx,ecx"\
				"adc	bh,dh"\
				"and	bx,si"\
				"mov	al,[bx]"\
				"add 	esi,edx"\
				"adc	ebx,ecx"\
				"adc	bh,dh"\
				"sub	ebp,8"\
				"mov	[ebp],eax"\
				"sub	di,8"\
				"jne	short lpp"\
				"pop	ds"\
				"pop	ebp"\
				modify [eax ebx ecx edx esi edi];
			hlinp1();
			hlinp2();

			scrline-=render_buff.buff_wid;
			}
		}


	// Find lowest pt of sky
	#define ST_DP 200
	ry[0]=-(st_l+ST_DP)*rot.e.r10+st_h*rot.e.r11+(st_w+ST_DP)*rot.e.r12+rot.e.r13;
	rz[0]=-(st_l+ST_DP)*rot.e.r20+st_h*rot.e.r21+(st_w+ST_DP)*rot.e.r22+rot.e.r23;
	ry[1]=(1280+st_l+ST_DP)*rot.e.r10+st_h*rot.e.r11+(st_w+ST_DP)*rot.e.r12+rot.e.r13;
	rz[1]=(1280+st_l+ST_DP)*rot.e.r20+st_h*rot.e.r21+(st_w+ST_DP)*rot.e.r22+rot.e.r23;
	ry[2]=(1280+st_l+ST_DP)*rot.e.r10+st_h*rot.e.r11-(800+st_w+ST_DP)*rot.e.r12+rot.e.r13;
	rz[2]=(1280+st_l+ST_DP)*rot.e.r20+st_h*rot.e.r21-(800+st_w+ST_DP)*rot.e.r22+rot.e.r23;
	ry[3]=-(st_l+ST_DP)*rot.e.r10+st_h*rot.e.r11-(800+st_w+ST_DP)*rot.e.r12+rot.e.r13;
	rz[3]=-(st_l+ST_DP)*rot.e.r20+st_h*rot.e.r21-(800+st_w+ST_DP)*rot.e.r22+rot.e.r23;

	if (rz[0]>0)
		ye=q*ry[0]/rz[0],ze=rz[0];
	else 
		ye=render_buff.clip_ymid,ze=0;
	if (rz[1]>ze) ye=q*ry[1]/rz[1],ze=rz[1];
	if (rz[2]>ze) ye=q*ry[2]/rz[2],ze=rz[2];
	if (rz[3]>ze) ye=q*ry[3]/rz[3],ze=rz[3];
	if (ye<-render_buff.clip_ymid) ye=-render_buff.clip_ymid;


	#define PI 3.1415
	sa=atan((double)render_buff.clip_wid/q);
	sw=3;//(int)(0.5+2*PI/sa);
	sa=2*PI/sw;

	if (setup.M8&&setup.detail.sky)
		{
		if ((yd=ye+q*sph/cph)<0) yd=0;
		if (479-yd<240-ye) yd=240+ye;
		if (sth<0)
			cpyline=sky+640*(480-yd)-(int)(640*acos((double)cth)/sa)%640;
		else
			cpyline=sky+640*(479-yd)+(int)(640*acos((double)cth)/sa)%640;
		y=render_buff.clip_ymid-ye-1;
		scrline=render_buff.buff_start+y*render_buff.buff_wid;
		while (y-->=0)
			{
			memcpy(scrline,cpyline,render_buff.clip_wid);
			scrline-=render_buff.buff_wid;
			cpyline-=640;
			}
		}
	else
		{
	#if 0
		if ((yd=ye+q*sph/cph)<0) yd=0;
		if (199-yd<100-ye) yd=100+ye;
		if (sth<0)
			cpyline=sky+320*(200-yd)-(int)(render_buff.clip_wid*acos((double)cth)/sa)%320;
		else
			cpyline=sky+320*(199-yd)+(int)(render_buff.clip_wid*acos((double)cth)/sa)%320;
		y=render_buff.clip_ymid-ye-1;
		scrline=render_buff.buff_start+y*render_buff.buff_wid;
		while (y-->=0)
			{
			memcpy(scrline,cpyline,render_buff.clip_wid);
			cpyline-=320;
			scrline-=render_buff.buff_wid;
			}
	#else
		y=render_buff.clip_ymid-ye-1;
		scrline=render_buff.buff_start+y*render_buff.buff_wid;
		while (y-->=0)
			{
			memset(scrline,204,render_buff.clip_wid);
			scrline-=render_buff.buff_wid;
			}
	#endif
		}
	}



/******************************/
/* GET OBJECT DEPTH STRUCTURE */

// Macro for objects with no detail levels
#define objdep(ob) ((ob).x*rot.e.r20+(ob).y*rot.e.r21+(ob).z*rot.e.r22+rot.e.r23)

// Routine for objects with detail levels
float objdepd(obj *ob, det *detail)
	{
	rotpt oz,zq;
	if ((oz=ob->x*rot.e.r20+ob->y*rot.e.r21+ob->z*rot.e.r22+rot.e.r23)<0)
		zq=0;
	else
		zq=oz/q;
	while (detail->zscale>zq) detail++;
	ob->points=detail->dpoints;
	ob->faces=detail->dfaces;
	return oz;
	}



/*************************************/
/* ADD ROTATED FACES TO POLYGON LIST */

// Add ordinary polygon to list
void
addpoly(face obf,word np,word col)
	{
	word p;
	rotpt dx1,dy1,dx2,dy2,tz1,tz2;
	rpt tpt1,tpt2,tpt3;

	// Unroll first three face points in subsequent code
	tpt1=&rotlist[obf[0]<<2];
	tpt2=&rotlist[obf[1]<<2];
	tpt3=&rotlist[obf[2]<<2];

	// Find min z
	tz2=tpt1[0];
	if (tpt2[0]<tz2) tz2=tpt2[0];
	if (tpt3[0]<tz2) tz2=tpt3[0];
	for (p=3;p<np;p++)
		if ((tz1=rotlist[obf[p]<<2])<tz2) tz2=tz1;

	// If visible...
	if (tz2>=CUTOFFDIST)
		{
		// Facing check
		dx1=dx2=tpt1[1];
		dy1=dy2=tpt1[2];
		dx1-=tpt2[1];
		dy1-=tpt2[2];
		dx2-=tpt3[1];
		dy2-=tpt3[2];

		if (dx1*dy2<dx2*dy1)
			{
			// Transfer rotated points to polygon list
			// and calculate average z
			curpol->pts=curpts;
			curpts[0]=np;
			curpts[1]=col;

/*
if (col>=256)
	{
 	tz1=tpt1[0];
	curpts[2]=max(tz1,CUTOFFDIST);
	curpts[3]=tpt1[1];
	curpts[4]=tpt1[2];
	tz1+=tpt2[0];
	curpts[5]=max(tpt2[0],CUTOFFDIST);
	curpts[6]=tpt2[1];
	curpts[7]=tpt2[2];
	tz1+=tpt3[0];
	curpts[8]=max(tpt3[0],CUTOFFDIST);
	curpts[9]=tpt3[1];
	curpts[10]=tpt3[2];
	curpts+=11;
	for (p=3;p<np;p++)
		{
		tpt1=&rotlist[obf[p]<<2];
		tz1+=tpt1[0];
		curpts[0]=max(tpt1[0],CUTOFFDIST);
  		curpts[1]=tpt1[1];
		curpts[2]=tpt1[2];
		curpts+=3;
		}
	}
else
	{
	}
*/
			tz1=tpt1[0];
			curpts[2]=tpt1[1];
			curpts[3]=tpt1[2];
			tz1+=tpt2[0];
			curpts[4]=tpt2[1];
			curpts[5]=tpt2[2];
			tz1+=tpt3[0];
			curpts[6]=tpt3[1];
			curpts[7]=tpt3[2];
			curpts+=8;
			for (p=3;p<np;p++)
				{
				tpt1=&rotlist[obf[p]<<2];
				tz1+=tpt1[0];
				curpts[0]=tpt1[1];
				curpts[1]=tpt1[2];
				curpts+=2;
				}
			curpol->z=tz1/np;
			curpol++;
			}
		}
	}

	
// Add line to list
void
addline(face obf,word col)
	{
	rotpt tz;
	rpt tpt1,tpt2;

	// Find min z
	tpt1=&rotlist[obf[0]<<2];
	tpt2=&rotlist[obf[1]<<2];
	tz=min(tpt1[0],tpt2[0]); 

	// If visible...
	if (tz>=CUTOFFDIST)
		{
		// Transfer rotated line points to polygon
		// list and calculate average z
		curpol->pts=curpts;
		curpol->z=(tpt1[0]+tpt2[0])/2;
		curpts[0]=2;
		curpts[1]=col;
		curpts[2]=tpt1[1];
		curpts[3]=tpt1[2];
		curpts[4]=tpt2[1];
		curpts[5]=tpt2[2];
		curpts+=6;
  		curpol++;		          
		}
	}


// Add 3d cylinder map to list
void
add3dcmap(face obf,word col)
	{
	rotpt dx1,dy1,dx2,dy2,tz1,tz2;
	rpt tpt1,tpt2,tpt3;

	// Find min z
	tpt1=&rotlist[obf[0]<<2];
	tpt2=&rotlist[obf[1]<<2];
	tz1=min(tpt1[0],tpt2[0]); 

	// If visible...
	if (tz1>=CUTOFFDIST)
		{
		curpts[0]=4;
		curpol->pts=curpts;
		curpol->z=(tpt1[0]+tpt2[0])/2;

		// Calculate bounding rectangle for cylinder texture map

		/*
		tpt1[0]=0;
		tpt1[1]=0;
		tpt1[2]=0;
		tpt2[0]=0;
		tpt2[1]=0;
		tpt2[2]=0;
		obf[2]=0;
		obf[3]=0;
		*/

		dx1=tpt1[1]-tpt2[1];
		dy1=tpt1[2]-tpt2[2];
		if ((dx2=dx1*dx1+dy1*dy1)==0) dx1=dx2=1;
		tz2=obf[2]*qa/(sqrt(dx2)*(tpt1[0]+tpt2[0]));
		tz1=100*(tpt2[0]-tpt1[0])/obf[3];
		if (tz1>=0)
			{				   
			if (tz1>0.78062475)
				if (tz1>0.92702481) col-=3;
				else col-=2;
			else
				if (tz1>0.48412292) col--;
//			if (tz1>0.78062475)
//				if (tz1>0.92702481) col-=3;
//				else col-=2;
//			else
//				if (tz1>0.48412292) col--;
//			col-=(int)((1-sqrt(1-tz1*tz1))*4.3);
			tz1*=tz2;
			dy2=tz2*dy1;
			dx2=tz2*dx1;
			dy1*=tz1;
			dx1*=tz1;
			curpts[1]=col;
			curpts[2]=tpt1[1]+dx1-dy2;
			curpts[3]=tpt1[2]+dy1+dx2;
			curpts[4]=tpt1[1]+dx1+dy2;
			curpts[5]=tpt1[2]+dy1-dx2;
			curpts[6]=tpt2[1]-dx1+dy2;
			curpts[7]=tpt2[2]-dy1-dx2;
			curpts[8]=tpt2[1]-dx1-dy2;
			curpts[9]=tpt2[2]-dy1+dx2;
			}
		else
			{
			if (tz1<-0.78062475)
				if (tz1<-0.92702481) col+=3;
				else col+=2;
			else
				if (tz1<-0.48412292) col++;
//			col+=(int)((1-sqrt(1-tz1*tz1))*4.3);
			tz1*=tz2;
			dy2=tz2*dy1;
			dx2=tz2*dx1;
			dy1*=tz1;
			dx1*=tz1;
			curpts[1]=col;
			curpts[2]=tpt1[1]-dx1-dy2;
			curpts[3]=tpt1[2]-dy1+dx2;
			curpts[4]=tpt1[1]-dx1+dy2;
			curpts[5]=tpt1[2]-dy1-dx2;
			curpts[6]=tpt2[1]+dx1+dy2;
			curpts[7]=tpt2[2]+dy1-dx2;
			curpts[8]=tpt2[1]+dx1-dy2;
			curpts[9]=tpt2[2]+dy1+dx2;
			}
		curpts+=10;
  		curpol++;		          
		}
	}


// Add 3d eliptical cylinder map to list
void
add3demap(face obf,word col)
	{
	rotpt dx1,dy1,dx2,dy2,tz1,tz2,rx,ry,rz;
	rpt tpt1,tpt2,tpt3;

	// Find min z
	tpt1=&rotlist[obf[0]<<2];
	tpt2=&rotlist[obf[1]<<2];
	tz1=min(tpt1[0],tpt2[0]); 

	// If visible...
	if (tz1>=CUTOFFDIST)
		{
		curpts[0]=4;
		curpol->pts=curpts;
		curpol->z=(tpt1[0]+tpt2[0])/2;

		// Calculate bounding rectangle for elliptical cylinder texture map
//		tpt3=&rotlist[obf[2]<<2];
//		dx1=tpt1[1]-tpt2[1];
//		dy1=tpt1[2]-tpt2[2];
//		rx=((tpt3[1]-render_buff.clip_xmid)*tpt3[0]-(tpt2[1]-render_buff.clip_xmid)*tpt2[0])/q;
//		ry=((tpt3[2]-render_buff.clip_ymid)*tpt3[0]-(tpt2[2]-render_buff.clip_ymid)*tpt2[0])/q;
//		if ((dx2=dx1*dx1+dy1*dy1)<2) return;
//		dx2=sqrt(dx2);
//		dy2=100*(tpt1[0]-tpt2[0])/obf[5];
//		tz1=(rx*dy1-ry*dx1)/dx2;
//		tz2=qa/(dx2*(tpt1[0]+tpt2[0]));

		tpt3=&rotlist[obf[2]<<2];
		dx1=tpt1[1]-tpt2[1];
		dy1=tpt1[2]-tpt2[2];
		rx=(tpt3[1]-tpt2[1])*tpt3[0]/q;
		ry=(tpt3[2]-tpt2[2])*tpt3[0]/q;
		if ((dx2=dx1*dx1+dy1*dy1)==0) dx1=dx2=1;
		dy2=sqrt(dx2);
		tz2=qa/(dy2*(tpt1[0]+tpt2[0]));

		tz1=(rx*dy1-ry*dx1)/dy2;

if (tz1<-1) tz1=-1;
if (tz1>1) tz1=1;

		if (tpt3[0]>tpt2[0])
//		if (rx*dx1<ry*dy1)
			if (tz1>-.2588)
				if (tz1<=.7071)
					if (tz1<=.2588)
						col-=9;
					else
						col-=10;
				else
					{
					if (tz1<=.9659)
						col-=11;
					}
			else				
				if (tz1>-.7071)
					col-=8;
				else
					if (tz1>-.9659)
						col-=7;
					else
						col-=6;
		else
			if (tz1<=.2588)
				if (tz1>-.7071)
					if (tz1>-.2588)
						col-=3;
					else
						col-=4;
				else
					if (tz1>-.9659)
						col-=5;
					else
						col-=6;
			else
				if (tz1<=.7071)
					col-=2;
				else
					if (tz1<=.9659)
						col-=1;

//		tz1*=tz1;
//		tz1*=(obf[3]-obf[4])*(obf[3]+obf[4]);
//		dx2=tz2*sqrt(tz1+obf[4]*obf[4]);

		tz1*=tz1;
		tz1*=(obf[3]-obf[4])*(obf[3]+obf[4]);
		dx2=tz2*sqrt(tz1+obf[4]*obf[4]);
		dy2=100*(tpt1[0]-tpt2[0])/obf[5];

		if (dy2>=0)
			{				   
			if (dy2>0.555570233)
				if (dy2>0.836286155) col-=36;
				else col-=24;
			else
				if (dy2>0.195090322) col-=12;
			dy2*=tz2*sqrt(obf[3]*obf[3]-tz1);
			tz1=dy2*dx1;
			tz2=dy2*dy1;
			dx1*=dx2;
			dy1*=dx2;
			curpts[1]=col;
			curpts[2]=tpt2[1]+dy1-tz1;
			curpts[3]=tpt2[2]-dx1-tz2;
			curpts[4]=tpt2[1]-dy1-tz1;
			curpts[5]=tpt2[2]+dx1-tz2;
			curpts[6]=tpt1[1]-dy1+tz1;
			curpts[7]=tpt1[2]+dx1+tz2;
			curpts[8]=tpt1[1]+dy1+tz1;
			curpts[9]=tpt1[2]-dx1+tz2;
			}
		else
			{
			if (dy2<-0.258819045)
				if (dy2<-0.707106781) col+=12;
				else col+=12;
			dy2*=tz2*sqrt(obf[3]*obf[3]-tz1);
			tz1=dy2*dx1;
			tz2=dy2*dy1;
			dx1*=dx2;
			dy1*=dx2;
			curpts[1]=col;
			curpts[2]=tpt2[1]+dy1+tz1;
			curpts[3]=tpt2[2]-dx1+tz2;
			curpts[4]=tpt2[1]-dy1+tz1;
			curpts[5]=tpt2[2]+dx1+tz2;
			curpts[6]=tpt1[1]-dy1-tz1;
			curpts[7]=tpt1[2]+dx1-tz2;
			curpts[8]=tpt1[1]+dy1-tz1;
			curpts[9]=tpt1[2]-dx1-tz2;
			}
		curpts+=10;
  		curpol++;		          
		}
	}

// Add polygon to list, with clipping, (note: optimised for unclipped objects)
void
addpolyc(face obf,word np,word col)
	{
	word p,pc,tp,i;
	dword *texx,*texy,*texs;
	rotpt dx1,dy1,dx2,dy2,tz1,tz2,qrz,qrz2;
	rpt tpt1,tpt2,tpt3;

	// Unroll first three face points in subsequent code
	tpt1=&rotlist[obf[0]<<2];
	tpt2=&rotlist[obf[1]<<2];
	tpt3=&rotlist[obf[2]<<2];

	// If any of first 3 pts need clipping, facing check is invalid, so go to clipping code now
	if ((tz1=tpt1[0])<SCREENDIST||tpt2[0]<SCREENDIST||tpt3[0]<SCREENDIST)
		{
		p=0;tz1=0;
		curpol->pts=curpts;
		curpts[0]=np;
		curpts[1]=col;
		curpts+=2;
		goto pclip;
		}

	// Facing check
	dx1=dx2=tpt1[1];
	dy1=dy2=tpt1[2];
	dx1-=tpt2[1];
	dy1-=tpt2[2];
	dx2-=tpt3[1];
	dy2-=tpt3[2];
	if (dx1*dy2<dx2*dy1)
		{
		// Transfer rotated points to polygon list and 
		// calculate average z. Go to clipping code if necessary
		curpol->pts=curpts;
		curpts[0]=np;
		curpts[1]=col;
		curpts[2]=tpt1[1];
		curpts[3]=tpt1[2];
		curpts[4]=tpt2[1];
		curpts[5]=tpt2[2];
		tz1+=tpt2[0];
		curpts[6]=tpt3[1];
		curpts[7]=tpt3[2];
		tz1+=tpt3[0];
		curpts+=8;
		for (p=3;p<np;p++)
			{
			tpt1=&rotlist[obf[p]<<2];
			if ((tz2=tpt1[0])<SCREENDIST) goto pclip; 
			tz1+=tz2;
			curpts[0]=tpt1[1];
			curpts[1]=tpt1[2];
			curpts+=2;
			}
		curpol->z=tz1/np;
		curpol++;
		}
	return;

	// Polygon needs clipping 
	pclip:;
	if (col<0)
		{
		// Texture map...
		if (col<-2000)
			{
			texs=(dword *)&textures[-col-2000];
			col=-2000-clip_tex;
			}
		else
			{
			texs=(dword *)&textures[-col];
			col=-clip_tex;
			}
		*(curpol->pts+1)=col;
		texy=(dword *)&textures[clip_tex];
		texx=(dword *)&textures[++clip_tex];
		for (i=0;i<p;i++)
			texy[i]=texs[i];
		for (i=0;i<p;i++)
			texx[i]=texs[np+i];

		tp=(p+np-1)%np;
		tpt2=&rotlist[obf[tp]<<2];
		pc=p;
		do
			{
			tz1+=tpt1[0];
			if (tpt1[0]>=SCREENDIST)
				{
				if (tpt2[0]<SCREENDIST)
					{
					qrz=(SCREENDIST-tpt2[0])/(tpt1[0]-tpt2[0]);
					qrz2=tpt1[0]/SCREENDIST;
					curpts[0]=tpt2[1]+qrz*((tpt1[1]-render_buff.clip_xmid)*qrz2-tpt2[1])+render_buff.clip_xmid;
					curpts[1]=tpt2[2]+qrz*((tpt1[2]-render_buff.clip_ymid)*qrz2-tpt2[2])+render_buff.clip_ymid;
					curpts+=2;

					texy[pc]=texs[tp]+qrz*(texs[p]-texs[tp]);
					texx[pc]=texs[tp+np]+qrz*(texs[p+np]-texs[tp+np]);

					if (++pc==3)
						{
						dx1=dx2=curpts[-6];
						dy1=dy2=curpts[-5];
						dx1-=curpts[-4];
						dy1-=curpts[-3];
						dx2-=curpts[-2];
						dy2-=curpts[-1];
						if (dx1*dy2>=dx2*dy1)
							{
							curpts=curpol->pts;
							return;
							}
						}
					}
				curpts[0]=tpt1[1];
				curpts[1]=tpt1[2];
				curpts+=2;

				texy[pc]=texs[p];
				texx[pc]=texs[p+np];

				if (++pc==3)
					{
					dx1=dx2=curpts[-6];
					dy1=dy2=curpts[-5];
					dx1-=curpts[-4];
					dy1-=curpts[-3];
					dx2-=curpts[-2];
					dy2-=curpts[-1];
					if (dx1*dy2>=dx2*dy1)
						{
						curpts=curpol->pts;
						return;
						}
					}
				}
			else
				if (tpt2[0]>=SCREENDIST)
					{
					qrz=(SCREENDIST-tpt1[0])/(tpt2[0]-tpt1[0]);
					qrz2=tpt2[0]/SCREENDIST;
					curpts[0]=tpt1[1]+qrz*((tpt2[1]-render_buff.clip_xmid)*qrz2-tpt1[1])+render_buff.clip_xmid;
					curpts[1]=tpt1[2]+qrz*((tpt2[2]-render_buff.clip_ymid)*qrz2-tpt1[2])+render_buff.clip_ymid;
					curpts+=2;

					texy[pc]=texs[p]+qrz*(texs[tp]-texs[p]);
					texx[pc]=texs[p+np]+qrz*(texs[tp+np]-texs[p+np]);

					if (++pc==3)
						{
						dx1=dx2=curpts[-6];
						dy1=dy2=curpts[-5];
						dx1-=curpts[-4];
						dy1-=curpts[-3];
						dx2-=curpts[-2];
						dy2-=curpts[-1];
						if (dx1*dy2>=dx2*dy1)
							{
							curpts=curpol->pts;
							return;
							}
						}
					}
			tpt2=tpt1;
			tp=p;
			tpt1=&rotlist[obf[(++p)%np]<<2];
			}while (p<np);
		p%=np;
		if (tpt1[0]>=SCREENDIST && tpt2[0]<SCREENDIST)
			{
			qrz=(SCREENDIST-tpt2[0])/(tpt1[0]-tpt2[0]);
			qrz2=tpt1[0]/SCREENDIST;
			curpts[0]=tpt2[1]+qrz*((tpt1[1]-render_buff.clip_xmid)*qrz2-tpt2[1])+render_buff.clip_xmid;
			curpts[1]=tpt2[2]+qrz*((tpt1[2]-render_buff.clip_ymid)*qrz2-tpt2[2])+render_buff.clip_ymid;
			curpts+=2;

			texy[pc]=texs[tp]+qrz*(texs[p]-texs[tp]);
			texx[pc]=texs[tp+np]+qrz*(texs[p+np]-texs[tp+np]);

			if (++pc==3)
				{
				dx1=dx2=curpts[-6];
				dy1=dy2=curpts[-5];
				dx1-=curpts[-4];
				dy1-=curpts[-3];
				dx2-=curpts[-2];
				dy2-=curpts[-1];
				if (dx1*dy2>=dx2*dy1)
					{
					curpts=curpol->pts;
					return;
					}
				}
			}

		for (i=0;i<pc;i++)
			texy[pc+i]=texx[i];
		if (pc>4) clip_tex++;

		}
	else
		{
		tpt2=&rotlist[obf[(p+np-1)%np]<<2];
		pc=p;
		do
			{
			tz1+=tpt1[0];
			if (tpt1[0]>=SCREENDIST)
				{
				if (tpt2[0]<SCREENDIST)
					{
					qrz=(SCREENDIST-tpt2[0])/(tpt1[0]-tpt2[0]);
					qrz2=tpt1[0]/SCREENDIST;
					curpts[0]=tpt2[1]+qrz*((tpt1[1]-render_buff.clip_xmid)*qrz2-tpt2[1])+render_buff.clip_xmid;
					curpts[1]=tpt2[2]+qrz*((tpt1[2]-render_buff.clip_ymid)*qrz2-tpt2[2])+render_buff.clip_ymid;
					curpts+=2;
					if (++pc==3)
						{
						dx1=dx2=curpts[-6];
						dy1=dy2=curpts[-5];
						dx1-=curpts[-4];
						dy1-=curpts[-3];
						dx2-=curpts[-2];
						dy2-=curpts[-1];
						if (dx1*dy2>=dx2*dy1)
							{
							curpts=curpol->pts;
							return;
							}
						}
					}
				curpts[0]=tpt1[1];
				curpts[1]=tpt1[2];
				curpts+=2;
				if (++pc==3)
					{
					dx1=dx2=curpts[-6];
					dy1=dy2=curpts[-5];
					dx1-=curpts[-4];
					dy1-=curpts[-3];
					dx2-=curpts[-2];
					dy2-=curpts[-1];
					if (dx1*dy2>=dx2*dy1)
						{
						curpts=curpol->pts;
						return;
						}
					}
				}
			else
				if (tpt2[0]>=SCREENDIST)
					{
					qrz=(SCREENDIST-tpt1[0])/(tpt2[0]-tpt1[0]);
					qrz2=tpt2[0]/SCREENDIST;
					curpts[0]=tpt1[1]+qrz*((tpt2[1]-render_buff.clip_xmid)*qrz2-tpt1[1])+render_buff.clip_xmid;
					curpts[1]=tpt1[2]+qrz*((tpt2[2]-render_buff.clip_ymid)*qrz2-tpt1[2])+render_buff.clip_ymid;
					curpts+=2;
					if (++pc==3)
						{
						dx1=dx2=curpts[-6];
						dy1=dy2=curpts[-5];
						dx1-=curpts[-4];
						dy1-=curpts[-3];
						dx2-=curpts[-2];
						dy2-=curpts[-1];
						if (dx1*dy2>=dx2*dy1)
							{
							curpts=curpol->pts;
							return;
							}
						}
					}
			tpt2=tpt1;
			tpt1=&rotlist[obf[(++p)%np]<<2];
			}while (p<np);
		if (tpt1[0]>=SCREENDIST && tpt2[0]<SCREENDIST)
			{
			qrz=(SCREENDIST-tpt2[0])/(tpt1[0]-tpt2[0]);
			qrz2=tpt1[0]/SCREENDIST;
			curpts[0]=tpt2[1]+qrz*((tpt1[1]-render_buff.clip_xmid)*qrz2-tpt2[1])+render_buff.clip_xmid;
			curpts[1]=tpt2[2]+qrz*((tpt1[2]-render_buff.clip_ymid)*qrz2-tpt2[2])+render_buff.clip_ymid;
			curpts+=2;
			if (++pc==3)
				{
				dx1=dx2=curpts[-6];
				dy1=dy2=curpts[-5];
				dx1-=curpts[-4];
				dy1-=curpts[-3];
				dx2-=curpts[-2];
				dy2-=curpts[-1];
				if (dx1*dy2>=dx2*dy1)
					{
					curpts=curpol->pts;
					return;
					}
				}
			}
		}
   // All pts clipped?
	if (pc==0)
		curpts=curpol->pts;
	else
		{
		*(curpol->pts)=pc;
		curpol->z=tz1/np;
		curpol++;
		}
 	}


// Add line to list, with clipping
void
addlinec(face obf,word col)
	{
	rotpt qrz,qrz2;
	rpt tpt1,tpt2;

	// Transfer rotated (/clipped) points to polygon list
	// and calculate average z
	tpt1=&rotlist[obf[0]<<2];
	tpt2=&rotlist[obf[1]<<2];
	if (tpt1[0]<SCREENDIST)
		{
		if (tpt2[0]<SCREENDIST) return;
		qrz=(SCREENDIST-tpt1[0])/(tpt2[0]-tpt1[0]);
		qrz2=tpt2[0]/SCREENDIST;
		curpts[2]=tpt1[1]+qrz*((tpt2[1]-render_buff.clip_xmid)*qrz2-tpt1[1])+render_buff.clip_xmid;
		curpts[3]=tpt1[2]+qrz*((tpt2[2]-render_buff.clip_ymid)*qrz2-tpt1[2])+render_buff.clip_ymid;
		}
	else
		{
		curpts[2]=tpt1[1];
		curpts[3]=tpt1[2];
		}
	if (tpt2[0]<SCREENDIST)
		{
		qrz=(SCREENDIST-tpt2[0])/(tpt1[0]-tpt2[0]);
		qrz2=tpt1[0]/SCREENDIST;
		curpts[4]=tpt2[1]+qrz*((tpt1[1]-render_buff.clip_xmid)*qrz2-tpt2[1])+render_buff.clip_xmid;
		curpts[5]=tpt2[2]+qrz*((tpt1[2]-render_buff.clip_ymid)*qrz2-tpt2[2])+render_buff.clip_ymid;
		}
	else
		{
		curpts[4]=tpt2[1];
		curpts[5]=tpt2[2];
		}
	curpol->pts=curpts;
	curpts[0]=2;
	curpts[1]=col;
	curpts+=6;
	curpol->z=(tpt1[0]+tpt2[0])/2;
	curpol++;
	}


// Add faces to polygon list, with no z clipping
void addpols(obj *ob)
	{
	face obf=ob->faces;
	word f=*obf++;
	word np,col;

#ifdef COUNT
	numpols+=f;
#endif

	while(f--)
		{
		np=obf[0];
		col=obf[1];
		obf+=2;

		if (np>2)
			{
			addpoly(obf, np, col); 
			obf+=np;
			}
		else
			if (np==2)
				{
				addline(obf, col);
				obf+=2;
				}
			else
			 	if (np==0)
					{
					add3dcmap(obf, col);
					obf+=4;
					}
				else
					{
					add3demap(obf, col);
					obf+=6;
					}
		}
	}


// Add faces to polygon list, with z clipping
void addpolsc(obj *ob)
	{
	face obf=ob->faces;
	word f=*obf++;	
	word np,col;

#ifdef COUNT
	numpols+=f;
#endif

	while(f--)
		{
		np=obf[0];
		col=obf[1];
		obf+=2;

		if (np>2) // Deal with polygons...
			{
			addpolyc(obf,np,col);
			obf+=np;
			}
		else	
			{
			addlinec(obf,col);
			obf+=2;
			}
		}
	}



/******************************************/
/* ROTATE OBJECTS AND ADD TO POLYGON LIST */

// Several routines here, for various cases:
// addobjxy	: objects with x & y axis rotation and no z-clipping
// addobjy	: objects with y-axis rotation only and no z-clipping
// addobjyc	: objects with y-axis rotation only with z-clipping
// addobjn	: objects with no rotation and no z-clipping
// addobjnc	: objects with no rotation with z-clipping
// addobjf	: objects with no rotation, all y=0, and no z-clipping
// addobjfc	: objects with no rotation, all y=0, with z-clipping


// Routine for objects with x & y axis rotation, no z-clipping
void addobjxy(obj *ob,floatpt cxrot,floatpt sxrot)
	{
	pt inpt=ob->points;
	rpt outpt=rotlist;
	word p=(word)*inpt++; // No of pts currently stored as datapt type!
	datapt x,y,z;
	floatpt crot,srot;
	rotpt	rx,ry,rz,qrz;

	// Get object depth
	if ((curobj->z=objdep(*ob))>CUTOFFDIST)
	{
	curobj->polys=curpol;

	// Transform matrix derived from view rotation and object rotation
	// Assumes r01=0 in view rotation
	crot=ob->crot;
	srot=ob->srot;
	x=ob->x;		  
	y=ob->y;
	z=ob->z;
/*
	tran.e.r00=rot.e.r00*crot-rot.e.r02*srot*cxrot; // Rotate in x then y
	tran.e.r01=rot.e.r02*sxrot;
	tran.e.r02=rot.e.r00*srot+rot.e.r02*crot*cxrot;
	tran.e.r03=rot.e.r00*x+rot.e.r01*y+rot.e.r02*z+rot.e.r03;
	tran.e.r10=rot.e.r10*crot-rot.e.r11*srot*sxrot-rot.e.r12*srot*cxrot;
	tran.e.r11=rot.e.r11*cxrot+rot.e.r12*sxrot;
	tran.e.r12=rot.e.r10*srot-rot.e.r11*crot*sxrot+rot.e.r12*crot*cxrot;
	tran.e.r13=rot.e.r10*x+rot.e.r11*y+rot.e.r12*z+rot.e.r13;
	tran.e.r20=rot.e.r20*crot-rot.e.r21*srot*sxrot-rot.e.r22*srot*cxrot;
	tran.e.r21=rot.e.r21*cxrot+rot.e.r22*sxrot;
	tran.e.r22=rot.e.r20*srot-rot.e.r21*crot*sxrot+rot.e.r22*crot*cxrot;
	tran.e.r23=rot.e.r20*x+rot.e.r21*y+rot.e.r22*z+rot.e.r23;
*/
	tran.e.r00= rot.e.r00*crot-rot.e.r02*srot;		// Rotate in y then x
	tran.e.r01=-rot.e.r00*srot*sxrot-rot.e.r02*crot*sxrot;
	tran.e.r02= rot.e.r00*srot*cxrot+rot.e.r02*crot*cxrot;
	tran.e.r03= rot.e.r00*x+rot.e.r01*y+rot.e.r02*z+rot.e.r03;
	tran.e.r10= rot.e.r10*crot-rot.e.r12*srot;
	tran.e.r11=-rot.e.r10*srot*sxrot+rot.e.r11*cxrot-rot.e.r12*crot*sxrot;
	tran.e.r12= rot.e.r10*srot*cxrot+rot.e.r11*sxrot+rot.e.r12*crot*cxrot;
	tran.e.r13= rot.e.r10*x+rot.e.r11*y+rot.e.r12*z+rot.e.r13;
	tran.e.r20= rot.e.r20*crot-rot.e.r22*srot;
	tran.e.r21=-rot.e.r20*srot*sxrot+rot.e.r21*cxrot-rot.e.r22*crot*sxrot;
	tran.e.r22= rot.e.r20*srot*cxrot+rot.e.r21*sxrot+rot.e.r22*crot*cxrot;
	tran.e.r23= rot.e.r20*x+rot.e.r21*y+rot.e.r22*z+rot.e.r23;

	// Rotate all points of object
	for (;p;p--)
		{
		x=inpt[0];
		y=inpt[1];
		z=inpt[2];
		inpt+=3;
		rx=x*tran.e.r00+y*tran.e.r01+z*tran.e.r02+tran.e.r03;
		ry=x*tran.e.r10+y*tran.e.r11+z*tran.e.r12+tran.e.r13;
		rz=x*tran.e.r20+y*tran.e.r21+z*tran.e.r22+tran.e.r23;

		// Get perspective scaling of point
		if (rz<SCREENDIST)
			{
			qrz=1.5-rz*scrdr; 	// Alternative perspective scaling...
			qrz*=qrz; 		 		//	mimics proper perspective for small...	
			qrz=persc*(qrz+.75);	// and negative z values.
			}
		else
			qrz=q/rz;	// Normal scaling

		//Add screen points to output list (with z values)
		outpt[0]=rz;
		outpt[1]=rx*qrz+render_buff.clip_xmid;
		outpt[2]=ry*qrz+render_buff.clip_ymid;
		outpt+=4;	// add 4 so indexing can be done with shifts
		}
	addpols(ob);
	curobj->nopols=curpol-curobj->polys;
	curobj++;
	}
	}


// Routine for objects with y axis rotation, no z-clipping
void addobjy(obj *ob)
	{
	pt inpt=ob->points;
	rpt outpt=rotlist;
	word p=(word)*inpt++; // No of pts currently stored as datapt type!
	datapt x,y,z;
	floatpt crot,srot;
	rotpt	rx,ry,rz,qrz;


	// Get object depth
	if ((curobj->z=objdep(*ob))>CUTOFFDIST)
	{
	curobj->polys=curpol;

	// Transform matrix derived from view rotation and object rotation
	// Assumes r01=0 in view rotation and that r11 & r21 remain the same
	crot=ob->crot;
	srot=ob->srot;
	x=ob->x;
	y=ob->y;
	z=ob->z;
	tran.e.r00=rot.e.r00*crot-rot.e.r02*srot;
	tran.e.r02=rot.e.r00*srot+rot.e.r02*crot;
	tran.e.r03=rot.e.r00*x+rot.e.r01*y+rot.e.r02*z+rot.e.r03;
	tran.e.r10=rot.e.r10*crot-rot.e.r12*srot;
	tran.e.r12=rot.e.r10*srot+rot.e.r12*crot;
	tran.e.r13=rot.e.r10*x+rot.e.r11*y+rot.e.r12*z+rot.e.r13;
	tran.e.r20=rot.e.r20*crot-rot.e.r22*srot;
	tran.e.r22=rot.e.r20*srot+rot.e.r22*crot;
	tran.e.r23=rot.e.r20*x+rot.e.r21*y+rot.e.r22*z+rot.e.r23;

	// Rotate all points of object
	for (;p;p--)
		{
		x=inpt[0];
		y=inpt[1];
		z=inpt[2];
		inpt+=3;
		rx=x*tran.e.r00+z*tran.e.r02+tran.e.r03; // r01 is 0
		ry=x*tran.e.r10+y*rot.e.r11+z*tran.e.r12+tran.e.r13;
		rz=x*tran.e.r20+y*rot.e.r21+z*tran.e.r22+tran.e.r23;

		// Get perspective scaling of point
		if (rz<SCREENDIST)
			{
			qrz=1.5-rz*scrdr; 	// Alternative perspective scaling...
			qrz*=qrz; 		 		//	mimics proper perspective for small...	
			qrz=persc*(qrz+.75);	// and negative z values.
/*
			qrz=2-rz*scrdr;		// Improved alternative perspective..
			qrz=qrz*qrz*qrz;	   // slightly higher complexity.
			qrz=persc*(qrz+2);
			qrz/=3;
*/			}
		else
			qrz=q/rz;	// Normal scaling

		//Add screen points to output list (with z values)
		outpt[0]=rz;
		outpt[1]=rx*qrz+render_buff.clip_xmid;
		outpt[2]=ry*qrz+render_buff.clip_ymid;
		outpt+=4;	// add 4 so indexing can be done with shifts
		}
	addpols(ob);
	curobj->nopols=curpol-curobj->polys;
	curobj++;
	}
	}

// Routine for objects with y axis rotation, no z-clipping, z flipped (only players)
void addobjyf(obj *ob)
	{
	pt inpt=ob->points;
	rpt outpt=rotlist;
	word p=(word)*inpt++; // No of pts currently stored as datapt type!
	datapt x,y,z;
	floatpt crot,srot;
	rotpt	rx,ry,rz,qrz;


	// Get object depth
	if ((curobj->z=objdep(*ob))>CUTOFFDIST)
	{
	curobj->polys=curpol;

	// Transform matrix derived from view rotation and object rotation
	// Assumes r01=0 in view rotation and that r11 & r21 remain the same
	crot=ob->crot;
	srot=ob->srot;
	x=ob->x;
	y=ob->y;
	z=ob->z;
	tran.e.r00=rot.e.r00*crot-rot.e.r02*srot;
	tran.e.r02=rot.e.r00*srot+rot.e.r02*crot;
	tran.e.r03=rot.e.r00*x+rot.e.r01*y+rot.e.r02*z+rot.e.r03;
	tran.e.r10=rot.e.r10*crot-rot.e.r12*srot;
	tran.e.r12=rot.e.r10*srot+rot.e.r12*crot;
	tran.e.r13=rot.e.r10*x+rot.e.r11*y+rot.e.r12*z+rot.e.r13;
	tran.e.r20=rot.e.r20*crot-rot.e.r22*srot;
	tran.e.r22=rot.e.r20*srot+rot.e.r22*crot;
	tran.e.r23=rot.e.r20*x+rot.e.r21*y+rot.e.r22*z+rot.e.r23;

	// Rotate all points of object
	for (;p;p--)
		{
		x=inpt[0];
		y=inpt[1];
		z=-inpt[2];
		inpt+=3;
		rx=x*tran.e.r00+z*tran.e.r02+tran.e.r03; // r01 is 0
		ry=x*tran.e.r10+y*rot.e.r11+z*tran.e.r12+tran.e.r13;
		rz=x*tran.e.r20+y*rot.e.r21+z*tran.e.r22+tran.e.r23;

		// Get perspective scaling of point
		if (rz<SCREENDIST)
			{
			qrz=1.5-rz*scrdr; 	// Alternative perspective scaling...
			qrz*=qrz; 		 		//	mimics proper perspective for small...	
			qrz=persc*(qrz+.75);	// and negative z values.
/*
			qrz=2-rz*scrdr;		// Improved alternative perspective..
			qrz=qrz*qrz*qrz;	   // slightly higher complexity.
			qrz=persc*(qrz+2);
			qrz/=3;
*/			}
		else
			qrz=q/rz;	// Normal scaling

		//Add screen points to output list (with z values)
		outpt[0]=rz;
		outpt[1]=rx*qrz+render_buff.clip_xmid;
		outpt[2]=ry*qrz+render_buff.clip_ymid;
		outpt+=4;	// add 4 so indexing can be done with shifts
		}
	addpols(ob);
	curobj->nopols=curpol-curobj->polys;
	curobj++;
	}
	}


// Routine for objects with y axis rotation & z-clipping
void addobjyc(obj *ob)
	{
	pt inpt=ob->points;
	rpt outpt=rotlist;
	word p=(word)*inpt++; // No of pts currently stored as datapt type!
	datapt x,y,z;
	floatpt crot,srot;
	rotpt	rx,ry,rz,qrz;

	// Get object depth
	curobj->z=objdep(*ob);
	curobj->polys=curpol;

	// Transform matrix derived from view rotation and object rotation
	// Assumes r01=0 in view rotation and that r11 & r21 remain the same
	crot=ob->crot;
	srot=ob->srot;
	x=ob->x;
	y=ob->y;
	z=ob->z;
	tran.e.r00=rot.e.r00*crot-rot.e.r02*srot;
	tran.e.r02=rot.e.r00*srot+rot.e.r02*crot;
	tran.e.r03=rot.e.r00*x+rot.e.r01*y+rot.e.r02*z+rot.e.r03;
	tran.e.r10=rot.e.r10*crot-rot.e.r12*srot;
	tran.e.r12=rot.e.r10*srot+rot.e.r12*crot;
	tran.e.r13=rot.e.r10*x+rot.e.r11*y+rot.e.r12*z+rot.e.r13;
	tran.e.r20=rot.e.r20*crot-rot.e.r22*srot;
	tran.e.r22=rot.e.r20*srot+rot.e.r22*crot;
	tran.e.r23=rot.e.r20*x+rot.e.r21*y+rot.e.r22*z+rot.e.r23;

	// Rotate all points of object
	for (;p;p--)
		{
		x=inpt[0];
		y=inpt[1];
		z=inpt[2];
		inpt+=3;
		rx=x*tran.e.r00+z*tran.e.r02+tran.e.r03; // r01 is 0
		ry=x*tran.e.r10+y*rot.e.r11+z*tran.e.r12+tran.e.r13;
		rz=x*tran.e.r20+y*rot.e.r21+z*tran.e.r22+tran.e.r23;

		// Get perspective scaling & add screen points to output list (with z values)
		outpt[0]=rz;
		if (rz<SCREENDIST)
			{
			outpt[1]=rx*persc;	//These values used in clip calculation
			outpt[2]=ry*persc;
			}
		else
			{
			qrz=q/rz;	// Normal scaling
			outpt[1]=rx*qrz+render_buff.clip_xmid;
			outpt[2]=ry*qrz+render_buff.clip_ymid;
			}
		outpt+=4;	// add 4 so indexing can be done with shifts
		}
	addpolsc(ob);
	curobj->nopols=curpol-curobj->polys;
	curobj++;
	}


// Routine for objects with no rotation, no z-clipping
void addobjn(obj *ob)
	{
	pt inpt=ob->points;
	rpt outpt=rotlist;
	word p=(word)*inpt++; // No of pts currently stored as datapt type!
	datapt x,y,z,tranx,trany,tranz;
	rotpt	rx,ry,rz,qrz;

	// Get object depth
	if ((curobj->z=objdep(*ob))>CUTOFFDIST)
	{
	curobj->polys=curpol;

	tranx=ob->x;
	trany=ob->y;
	tranz=ob->z;
	// Rotate all points of object
	for (;p;p--)
		{
		x=tranx+inpt[0];
		y=trany+inpt[1];
		z=tranz+inpt[2];
		inpt+=3;
		rx=x*rot.e.r00+z*rot.e.r02+rot.e.r03; // r01 is 0
		ry=x*rot.e.r10+y*rot.e.r11+z*rot.e.r12+rot.e.r13;
		rz=x*rot.e.r20+y*rot.e.r21+z*rot.e.r22+rot.e.r23;

		// Get perspective scaling of point
		if (rz<SCREENDIST)
			{
			qrz=1.5-rz*scrdr; 	// Alternative perspective scaling...
			qrz*=qrz; 		 		//	mimics proper perspective for small...	
			qrz=persc*(qrz+.75);	// and negative z values.
			}
		else
			qrz=q/rz;	// Normal scaling

		//Add screen points to output list (with z values)
		outpt[0]=rz;
		outpt[1]=rx*qrz+render_buff.clip_xmid;
		outpt[2]=ry*qrz+render_buff.clip_ymid;
		outpt+=4;	// add 4 so indexing can be done with shifts
		}
	addpols(ob);
	curobj->nopols=curpol-curobj->polys;
	curobj++;
	}
	}


// Routine for sprite objects (no rotation, no z-clipping)
void addobjsp(datapt *sprpt, word *refpt)
	{
	word p=(word)*(sprpt++); // No of sprites currently stored as datapt type!
	datapt x,y,z;
	rotpt	rx,ry,rz,qrz;

	// Rotate all sprite points and add to polygon list for sorting
	for (;p;p--)
		{
		curobj->polys=curpol;
		x=sprpt[0];
		y=sprpt[1];
		z=sprpt[2];
		sprpt+=3;
		rx=x*rot.e.r00+z*rot.e.r02+rot.e.r03; // r01 is 0
		ry=x*rot.e.r10+y*rot.e.r11+z*rot.e.r12+rot.e.r13;
		rz=x*rot.e.r20+y*rot.e.r21+z*rot.e.r22+rot.e.r23;

		// Get perspective scaling of point
		if (rz<SCREENDIST)
			{
			qrz=1.5-rz*scrdr; 	// Alternative perspective scaling...
			qrz*=qrz; 		 		//	mimics proper perspective for small...	
			qrz=persc*(qrz+.75);	// and negative z values.
			}
		else
			qrz=q/rz;	// Normal scaling

		rx=rx*qrz+render_buff.clip_xmid;
		if (rz<CUTOFFDIST)
			if (rx>=0)
			 	rx=render_buff.clip_wid<<1;
			else
				rx=-render_buff.clip_wid;

 		curpol->pts=curpts;
		curobj->z=curpol->z=rz; 
		curpts[0]=1;
		curpts[1]=*(refpt++);
		curpts[2]=rx;
		curpts[3]=ry*qrz+render_buff.clip_ymid;
		curpts+=4;
		curpol++;
		curobj->nopols=1;
		curobj++;
		}
	}


// Routine for objects with no rotation & z-clipping
void addobjnc(obj *ob)
	{
	pt inpt=ob->points;
	rpt outpt=rotlist;
	word p=(word)*inpt++; // No of pts currently stored as datapt type!
	datapt x,y,z,tranx,trany,tranz;
	rotpt	rx,ry,rz,qrz;

	// Get object depth
	curobj->z=objdep(*ob);
	curobj->polys=curpol;

	tranx=ob->x;
	trany=ob->y;
	tranz=ob->z;
	// Rotate all points of object
	for (;p;p--)
		{
		x=tranx+inpt[0];
		y=trany+inpt[1];
		z=tranz+inpt[2];
		inpt+=3;
		rx=x*rot.e.r00+z*rot.e.r02+rot.e.r03; // r01 is 0
		ry=x*rot.e.r10+y*rot.e.r11+z*rot.e.r12+rot.e.r13;
		rz=x*rot.e.r20+y*rot.e.r21+z*rot.e.r22+rot.e.r23;

		// Get perspective scaling & add screen points to output list (with z values)
		outpt[0]=rz;
		if (rz<SCREENDIST)
			{
			outpt[1]=rx*persc;	//These values used in clip calculation
			outpt[2]=ry*persc;
			}
		else
			{
			qrz=q/rz;	// Normal scaling
			outpt[1]=rx*qrz+render_buff.clip_xmid;
			outpt[2]=ry*qrz+render_buff.clip_ymid;
			}
		outpt+=4;	// add 4 so indexing can be done with shifts
		}
	addpolsc(ob);
	curobj->nopols=curpol-curobj->polys;
	curobj++;
	}


// Routine for objects with no rotation and all y=0, no z-clipping
void addobjf(obj *ob)
	{
	pt inpt=ob->points;
	rpt outpt=rotlist;
	word p=(word)*inpt++; // No of pts currently stored as datapt type!
	datapt x,z,tranx,tranz;
	rotpt	rx,ry,rz,qrz;

	// Get object depth
	if ((curobj->z=objdep(*ob))>CUTOFFDIST)
	{
	curobj->polys=curpol;

	tranx=ob->x;
	tranz=ob->z;
	// Rotate all points of object
	for (;p;p--)
		{
		x=tranx+inpt[0];
		z=tranz+inpt[2];
		inpt+=3;
		rx=x*rot.e.r00+z*rot.e.r02+rot.e.r03;
		ry=x*rot.e.r10+z*rot.e.r12+rot.e.r13;
		rz=x*rot.e.r20+z*rot.e.r22+rot.e.r23;

		// Get perspective scaling of point
		if (rz<SCREENDIST)
			{
			qrz=1.5-rz*scrdr; 	// Alternative perspective scaling...
			qrz*=qrz; 		 		//	mimics proper perspective for small...	
			qrz=persc*(qrz+.75);	// and negative z values.
			}
		else
			qrz=q/rz;	// Normal scaling

		//Add screen points to output list (with z values)
		outpt[0]=rz;
		outpt[1]=rx*qrz+render_buff.clip_xmid;
		outpt[2]=ry*qrz+render_buff.clip_ymid;
		outpt+=4;	// add 4 so indexing can be done with shifts
		}
	addpols(ob);
	curobj->nopols=curpol-curobj->polys;
	curobj++;
	}
	}


// Routine for objects with no rotation and all y=0, with z-clipping
void addobjfc(obj *ob)
	{
	pt inpt=ob->points;
	rpt outpt=rotlist;
	word p=(word)*inpt++; // No of pts currently stored as datapt type!
	datapt x,z,tranx,tranz;
	rotpt	rx,ry,rz,qrz;

	// Get object depth
	curobj->z=objdep(*ob);
	curobj->polys=curpol;

	tranx=ob->x;
	tranz=ob->z;
	// Rotate all points of object
	for (;p;p--)
		{
		x=tranx+inpt[0];
		z=tranz+inpt[2];
		inpt+=3;
		rx=x*rot.e.r00+z*rot.e.r02+rot.e.r03;
		ry=x*rot.e.r10+z*rot.e.r12+rot.e.r13;
		rz=x*rot.e.r20+z*rot.e.r22+rot.e.r23;

		// Get perspective scaling & add screen points to output list (with z values)
  		outpt[0]=rz;
		if (rz<SCREENDIST)
			{
			outpt[1]=rx*persc;	//These values used in clip calculation
			outpt[2]=ry*persc;
			}
		else
			{
			qrz=q/rz;	// Normal scaling
			outpt[1]=rx*qrz+render_buff.clip_xmid;
			outpt[2]=ry*qrz+render_buff.clip_ymid;
			}
		outpt+=4;	// add 4 so indexing can be done with shifts
		}
	addpolsc(ob);
	curobj->nopols=curpol-curobj->polys;
	curobj++;
	}




/************************************************/
/* SORT, DISPLAY AND RESET OBJECT/POLYGON LISTS */

// Macro to reset object/polygon/point lists
#define clearlists curobj=objlist,curpol=pollist,curpts=ptslist;


// Object depth comparison for qsort
int objcmp(void const *obj1, void const *obj2)
	{
	// Avoids unnessecary float to int conversions, assumes true=1
	return (((objs *)obj1)->z<=((objs *)obj2)->z ? ((objs *)obj1)->z<((objs *)obj2)->z : -1);
	}


// Polygon depth comparison for qsort
int polcmp(void const *pol1, void const *pol2)
	{
	// Avoids unnessecary float to int conversions, assumes true=1
	return (((pols *)pol1)->z<=((pols *)pol2)->z ? ((pols *)pol1)->z<((pols *)pol2)->z : -1);
	}


// Sort the polygons within a single object
#define sortobj(ob) qsort((ob)->polys,(ob)->nopols,sizeof(pols),polcmp);


// Draw polygons after sorting
void
dispols()
	{
	objs *cobj=objlist;
	short i,n;
	word np,col;
	dword *polytex;

	// Sort objects from z value
	qsort(objlist,curobj-objlist,sizeof(objs),objcmp);

	// Draw the polygons associated with the sorted list
	while (cobj!=curobj)
		{
		n=cobj->nopols;
		curpol=cobj++->polys;
		for (i=0;i<n;i++)
			{
			curpts=curpol++->pts;
			np=(word)curpts[0];
			col=(word)curpts[1];
			curpts+=2;

if (col>=512) col=257;

			// Choose routine to use from np & col
			if (col<-2000)
 				{
				polytex=(dword *)&textures[-col-2000];
				polyt((pnt *)curpts,np,mapsel[*(((BYTE *)polytex)+3)],polytex+np,polytex);
				continue;
				}
			if (col<0)
 				{
				polytex=(dword *)&textures[-col];
				polym((pnt *)curpts,np,mapsel[*(((BYTE *)polytex)+3)],polytex+np,polytex);
				continue;
				}
			if (col>=512)
	 			{
				polytex=(dword *)&texloop[(col&255)].tex;
//				polytex=(dword *)&textures[(col&255)+S_TM];
				polyl((pnt *)curpts,np,mapsel[mappages-2+(col&255)],polytex+np,polytex);
//				polyl((pnt *)curpts,np,mapsel[mappages-2+(col>>8)],polytex+np,polytex);
				continue;
				}
			if (col>=256)
 				{
				polyf((pnt *)curpts,np,filters[col&255]);
				continue;
				}
			if (np<=2)				     
				if (np==1)
					{sprite3d(curpts[0]/render_buff.scale_x,(render_buff.clip_hgt-curpts[1])/render_buff.scale_y,col);curpts+=2;}
				else		   
					line((pnt *)curpts,col);
			else
				polyb((pnt *)curpts,np,col);
			}
	 
		}
		clearlists
	}


// Draw flat polys on 3D Blaster
void dispols3DB()
	{
	objs *cobj=objlist;
	short i,j,k,n;
	word np,p,pt,pl,col;
	CGL_VERTEX2D_ST *pts3d,*lpts3d;
	CGL_COLOR_ST *col3d,*lcol3d;
	int tpts1[24];
	int tpts2[24];
	int cp;

	pts3d=&Vertex[0];
	col3d=&Colour[0];
	lpts3d=&lVertex[0];
	lcol3d=&lColour[0];

	// Draw the polygons associated with the sorted list
	while (cobj!=curobj)
		{
		n=cobj->nopols;
		curpol=cobj++->polys;
		for (i=0;i<n;i++)
			{
			curpts=curpol++->pts;
			np=(word)curpts[0]<<1;
			col=(word)curpts[1];
			curpts+=2;

			p=0;
			for (j=0;j<np;j+=2)
				{
				k=j+2;
				if (k==np) k=0;
				if (curpts[j]>=0)
					if (curpts[k]>=0)
						{
						tpts1[p++]=curpts[k];
						tpts1[p++]=curpts[k+1];
						}
					else
						{
						tpts1[p++]=0;
						tpts1[p++]=curpts[j+1]+((curpts[k+1]-curpts[j+1])*curpts[j])/(curpts[j]-curpts[k]);
						}
				else
					if (curpts[k]>=0)
						{
						if (np!=4)
							{
							tpts1[p++]=0;
							tpts1[p++]=curpts[k+1]+((curpts[j+1]-curpts[k+1])*curpts[k])/(curpts[k]-curpts[j]);
							}
						tpts1[p++]=curpts[k];
						tpts1[p++]=curpts[k+1];
						}
				}

			pt=0;
			for (j=0;j<p;j+=2)
				{
				k=j+2;
				if (k==p) k=0;
				if (tpts1[j]<=render_buff.clip_wid)
					if (tpts1[k]<=render_buff.clip_wid)
						{
						tpts2[pt++]=tpts1[k];
						tpts2[pt++]=tpts1[k+1];
						}
					else
						{
						tpts2[pt++]=render_buff.clip_wid;
						tpts2[pt++]=tpts1[j+1]+((tpts1[k+1]-tpts1[j+1])*(render_buff.clip_wid-tpts1[j]))/(tpts1[k]-tpts1[j]);
						}
				else
					if (tpts1[k]<=render_buff.clip_wid)
						{
						if (np!=4)
							{
							tpts2[pt++]=render_buff.clip_wid;
							tpts2[pt++]=tpts1[k+1]+((tpts1[j+1]-tpts1[k+1])*(render_buff.clip_wid-tpts1[k]))/(tpts1[j]-tpts1[k]);
							}
						tpts2[pt++]=tpts1[k];
						tpts2[pt++]=tpts1[k+1];
						}
				}
 
			cp=((np==4)?1:0);
			p=0;
			for (j=0;j<pt;j+=2)
				{
				k=j+2;
				if (k==pt) k=0;
				if (tpts2[j+1]>=cp)
					if (tpts2[k+1]>=cp)
						{
						tpts1[p++]=tpts2[k];
						tpts1[p++]=tpts2[k+1];
						}
					else
						{
						tpts1[p++]=tpts2[j]+((tpts2[k]-tpts2[j])*tpts2[j+1])/(tpts2[j+1]-tpts2[k+1]);
						tpts1[p++]=cp;
						}
				else
					if (tpts2[k+1]>=cp)
						{
						if (np!=4)
							{
							tpts1[p++]=tpts2[k]+((tpts2[j]-tpts2[k])*tpts2[k+1])/(tpts2[k+1]-tpts2[j+1]);
							tpts1[p++]=cp;
							}
						tpts1[p++]=tpts2[k];
						tpts1[p++]=tpts2[k+1];
						}
				}

			pt=0;
			for (j=0;j<p;j+=2)
				{
				k=j+2;
				if (k==p) k=0;
				if (tpts1[j+1]<=render_buff.clip_hgtl)
					if (tpts1[k+1]<=render_buff.clip_hgtl)
						{
						pts3d[pt].x=tpts1[k]<<16;
						pts3d[pt++].y=tpts1[k+1]<<16;
						}
					else
						{
						pts3d[pt].x=(tpts1[j]+((tpts1[k]-tpts1[j])*(render_buff.clip_hgt-tpts1[j+1]))/(tpts1[k+1]-tpts1[j+1]))<<16;
						pts3d[pt++].y=render_buff.clip_hgtl<<16;
						}
				else
					if (tpts1[k+1]<=render_buff.clip_hgtl)
						{
						if (np!=4)
							{
							pts3d[pt].x=(tpts1[k]+((tpts1[j]-tpts1[k])*(render_buff.clip_hgt-tpts1[k+1]))/(tpts1[j+1]-tpts1[k+1]))<<16;
							pts3d[pt++].y=render_buff.clip_hgtl<<16;
							}
						pts3d[pt].x=tpts1[k]<<16;
						pts3d[pt++].y=tpts1[k+1]<<16;
						}
				}

			p=0;
			pl=pt;
			while (pl>4)
				{
				p+=4;
				pt+=2;
				pl-=2;
				for (j=pt-1;j>p;j--)
					{
					pts3d[j].x=pts3d[j-2].x;
					pts3d[j].y=pts3d[j-2].y;
					}
				pts3d[p].x=pts3d[0].x;
				pts3d[p].y=pts3d[0].y;
				}
			p+=pl;
			if (pl<=3)
				{
				if (pl==3)
					{
					pts3d[p].x=pts3d[0].x;
					pts3d[p].y=pts3d[0].y;
					p++;
					}
				else
					if (pl==2)
						{
						if (pts3d[0].y<0x20000) pts3d[0].y=0x20000;
						if (pts3d[1].y<0x20000) pts3d[1].y=0x20000;
						lpts3d[0].x=pts3d[0].x;
						lpts3d[0].y=pts3d[0].y;
						lpts3d[1].x=pts3d[1].x;
						lpts3d[1].y=pts3d[1].y;
						lcol3d->bRed=col;
						lcol3d+=2;
						lpts3d+=2;
						goto dpline;
						}
				}
			while (p)
				{
				col3d->bRed=col;
				col3d+=4;
				pts3d+=4;
				p-=4;
				}
			dpline:;
			}
		}

	SetLineOutput3DB();
	if ((p=lpts3d-lVertex)>0)
		Render3DB(p);

	SetFlatQuadOutput3DB();
	if ((p=pts3d-Vertex)>0)
		Render3DB(p);

	clearlists
	}


// Draw polygons without sorting
void dispolsn()
	{
	objs *cobj=objlist;
	short i,n;
	word np,col;
	dword *polytex;

	while (cobj!=curobj)
		{
		n=cobj->nopols;
		curpol=cobj++->polys;
		for (i=0;i<n;i++)
			{
			curpts=curpol++->pts;
			np=(word)curpts[0];
			col=(word)curpts[1];
			curpts+=2;

if (col>=512) col=257;

			// Choose routine to use from np & col
			if (col<-2000)
 				{
				polytex=(dword *)&textures[-col-2000];
				polyt((pnt *)curpts,np,mapsel[*(((BYTE *)polytex)+3)],polytex+np,polytex);
				continue;
				}
			if (col<0)
 				{
				polytex=(dword *)&textures[-col];
				polym((pnt *)curpts,np,mapsel[*(((BYTE *)polytex)+3)],polytex+np,polytex);
				continue;
				}
			if (col>=512)
	 			{
				polytex=(dword *)&texloop[(col&255)].tex;
//				polytex=(dword *)&textures[(col&255)+S_TM];
				polyl((pnt *)curpts,np,mapsel[mappages-2+(col&255)],polytex+np,polytex);
//	 			polyl((pnt *)curpts,np,mapsel[mappages-2+(col>>8)],polytex+np,polytex);
				continue;
				}
			if (col>=256)
 				{
				polyf((pnt *)curpts,np,filters[col&255]);
				continue;
				}
			if (np<=2)
				if (np==1)
					{sprite3d(curpts[0]/render_buff.scale_x,(render_buff.clip_hgt-curpts[1])/render_buff.scale_y,col);curpts+=2;}
				else		   
					line((pnt *)curpts,col);
			else
				polyb((pnt *)curpts,np,col);
			}
 
		}
		clearlists
	}


// Draw sorted texture maps on 3D Blaster
void dispolst3DB()
	{
	objs *cobj=objlist;
	short i,j,k,n;
	word np,p,pt,pl,col;
	float fc;
	CGL_VERTEX2D_ST *pts3d;
	CGL_TEXTURE2D_ST *tex3d;
	CGL_COLOR_ST *col3d;
	int tpts1[16];
	int tpts2[16];
	int ttex1[16];
	int ttex2[16];
	dword *polytexx,*polytexy,pmx;

	pts3d=&Vertex[0];
	tex3d=&Texture[0];
	// Draw the polygons associated with the sorted list
	while (cobj!=curobj)
		{
		n=cobj->nopols;
		curpol=cobj++->polys;
		for (i=0;i<n;i++)
			{
			curpts=curpol++->pts;
			if ((np=(word)curpts[0])<3) goto errpol;
			col=(word)curpts[1];
			curpts+=2;

			if (col<0)
				{
				if (col<-2000) col+=2000;
				polytexy=(dword *)&textures[-col];
				polytexx=polytexy+np;
				pmx=(*polytexy&0xc000000)>>2;
				np<<=1;		
				p=0;
				for (j=0;j<np;j+=2)
					{
					k=j+2;
					if (k==np) k=0;
					if (curpts[j]>=0)
						if (curpts[k]>=0)
							{
							tpts1[p]=curpts[k];
							ttex1[p++]=(polytexx[k>>1]|pmx);
							tpts1[p]=curpts[k+1];
							ttex1[p++]=polytexy[k>>1]&0x3ffffff;
							}
						else
							{
							fc=(float)curpts[j]/(curpts[j]-curpts[k]);
							tpts1[p]=0;
							ttex1[p++]=((polytexx[j>>1]+(int)(fc*(polytexx[k>>1]-polytexx[j>>1])))|pmx);
							tpts1[p]=curpts[j+1]+(int)(fc*(curpts[k+1]-curpts[j+1]));
							ttex1[p++]=(polytexy[j>>1]+(int)(fc*(polytexy[k>>1]-polytexy[j>>1])))&0x3ffffff;
							}
					else
						if (curpts[k]>=0)
							{
							fc=(float)curpts[k]/(curpts[k]-curpts[j]);
							tpts1[p]=0;
							ttex1[p++]=((polytexx[k>>1]+(int)(fc*(polytexx[j>>1]-polytexx[k>>1])))|pmx);
							tpts1[p]=curpts[k+1]+(int)(fc*(curpts[j+1]-curpts[k+1]));
							ttex1[p++]=(polytexy[k>>1]+(int)(fc*(polytexy[j>>1]-polytexy[k>>1])))&0x3ffffff;
							tpts1[p]=curpts[k];
							ttex1[p++]=(polytexx[k>>1]|pmx);
							tpts1[p]=curpts[k+1];
							ttex1[p++]=polytexy[k>>1]&0x3ffffff;
							}
					}
				}
			else
				{
if (col>=512) col=257;
				if (col==256) col=9;
				if (col==257) col=24;
				if (!col) col=2;
				pmx=0x1008000|(col<<16);
				np<<=1;		
				p=0;
				for (j=0;j<np;j+=2)
					{
					k=j+2;
					if (k==np) k=0;
					if (curpts[j]>=0)
						if (curpts[k]>=0)
							{
							tpts1[p]=curpts[k];
							ttex1[p++]=pmx;
							tpts1[p]=curpts[k+1];
							ttex1[p++]=0x3508000;
							}
						else
							{
							fc=(float)curpts[j]/(curpts[j]-curpts[k]);
							tpts1[p]=0;
							ttex1[p++]=pmx;
							tpts1[p]=curpts[j+1]+(int)(fc*(curpts[k+1]-curpts[j+1]));
							ttex1[p++]=0x3508000;
							}
					else
						if (curpts[k]>=0)
							{
							fc=(float)curpts[k]/(curpts[k]-curpts[j]);
							tpts1[p]=0;
							ttex1[p++]=pmx;
							tpts1[p]=curpts[k+1]+(int)(fc*(curpts[j+1]-curpts[k+1]));
							ttex1[p++]=0x3508000;
							tpts1[p]=curpts[k];
							ttex1[p++]=pmx;
							tpts1[p]=curpts[k+1];
							ttex1[p++]=0x3508000;
							}
					}
				}
 
			pt=0;
			for (j=0;j<p;j+=2)
				{
				k=j+2;
				if (k==p) k=0;
				if (tpts1[j]<=render_buff.clip_wid)
					if (tpts1[k]<=render_buff.clip_wid)
						{
						tpts2[pt]=tpts1[k];
						ttex2[pt++]=ttex1[k];
						tpts2[pt]=tpts1[k+1];
						ttex2[pt++]=ttex1[k+1];
						}
					else
						{
						fc=(float)(render_buff.clip_wid-tpts1[j])/(tpts1[k]-tpts1[j]);
						tpts2[pt]=render_buff.clip_wid;
						ttex2[pt++]=ttex1[j]+(int)(fc*(ttex1[k]-ttex1[j]));
						tpts2[pt]=tpts1[j+1]+(int)(fc*(tpts1[k+1]-tpts1[j+1]));
						ttex2[pt++]=ttex1[j+1]+(int)(fc*(ttex1[k+1]-ttex1[j+1]));
						}
				else
					if (tpts1[k]<=render_buff.clip_wid)
						{
						fc=(float)(render_buff.clip_wid-tpts1[k])/(tpts1[j]-tpts1[k]);
						tpts2[pt]=render_buff.clip_wid;
						ttex2[pt++]=ttex1[k]+(int)(fc*(ttex1[j]-ttex1[k]));
						tpts2[pt]=tpts1[k+1]+(int)(fc*(tpts1[j+1]-tpts1[k+1]));
						ttex2[pt++]=ttex1[k+1]+(int)(fc*(ttex1[j+1]-ttex1[k+1]));
						tpts2[pt]=tpts1[k];
						ttex2[pt++]=ttex1[k];
						tpts2[pt]=tpts1[k+1];
						ttex2[pt++]=ttex1[k+1];
						}
				}

			p=0;
			for (j=0;j<pt;j+=2)
				{
				k=j+2;
				if (k==pt) k=0;
				if (tpts2[j+1]>=0)
					if (tpts2[k+1]>=0)
						{
						tpts1[p]=tpts2[k];
						ttex1[p++]=ttex2[k];
						tpts1[p]=tpts2[k+1];
						ttex1[p++]=ttex2[k+1];
						}
					else
						{
						fc=(float)tpts2[j+1]/(tpts2[j+1]-tpts2[k+1]);
						tpts1[p]=tpts2[j]+(int)(fc*(tpts2[k]-tpts2[j]));
						ttex1[p++]=ttex2[j]+(int)(fc*(ttex2[k]-ttex2[j]));
						tpts1[p]=0;
						ttex1[p++]=ttex2[j+1]+(int)(fc*(ttex2[k+1]-ttex2[j+1]));
						}
				else
					if (tpts2[k+1]>=0)
						{
						fc=(float)tpts2[k+1]/(tpts2[k+1]-tpts2[j+1]);
						tpts1[p]=tpts2[k]+(int)(fc*(tpts2[j]-tpts2[k]));
						ttex1[p++]=ttex2[k]+(int)(fc*(ttex2[j]-ttex2[k]));
						tpts1[p]=0;
						ttex1[p++]=ttex2[k+1]+(int)(fc*(ttex2[j+1]-ttex2[k+1]));
						tpts1[p]=tpts2[k];
						ttex1[p++]=ttex2[k];
						tpts1[p]=tpts2[k+1];
						ttex1[p++]=ttex2[k+1];
						}
				}

			pt=0;
			for (j=0;j<p;j+=2)
				{
				k=j+2;
				if (k==p) k=0;
				if (tpts1[j+1]<=render_buff.clip_hgtl)
					if (tpts1[k+1]<=render_buff.clip_hgtl)
						{
						pts3d[pt].x=tpts1[k]<<16;
						tex3d[pt].s=ttex1[k];
						pts3d[pt].y=tpts1[k+1]<<16;
						tex3d[pt++].t=ttex1[k+1];
						}
					else
						{
						fc=(float)(render_buff.clip_hgtl-tpts1[j+1])/(tpts1[k+1]-tpts1[j+1]);
						pts3d[pt].x=(tpts1[j]+(int)(fc*(tpts1[k]-tpts1[j])))<<16;
						tex3d[pt].s=ttex1[j]+(int)(fc*(ttex1[k]-ttex1[j]));
						pts3d[pt].y=render_buff.clip_hgtl<<16;
						tex3d[pt++].t=ttex1[j+1]+(int)(fc*(ttex1[k+1]-ttex1[j+1]));
						}
				else
					if (tpts1[k+1]<=render_buff.clip_hgtl)
						{
						fc=(float)(render_buff.clip_hgtl-tpts1[k+1])/(tpts1[j+1]-tpts1[k+1]);
						pts3d[pt].x=(tpts1[k]+(int)(fc*(tpts1[j]-tpts1[k])))<<16;
						tex3d[pt].s=ttex1[k]+(int)(fc*(ttex1[j]-ttex1[k]));
						pts3d[pt].y=render_buff.clip_hgtl<<16;
						tex3d[pt++].t=ttex1[k+1]+(int)(fc*(ttex1[j+1]-ttex1[k+1]));
						pts3d[pt].x=tpts1[k]<<16;
						tex3d[pt].s=ttex1[k];
						pts3d[pt].y=tpts1[k+1]<<16;
						tex3d[pt++].t=ttex1[k+1];
						}
				}

			p=0;
			pl=pt;
			while (pl>4)
				{
				p+=4;
				pt+=2;
				pl-=2;
				for (j=pt-1;j>p;j--)
					{
					pts3d[j].x=pts3d[j-2].x;
					pts3d[j].y=pts3d[j-2].y;
					tex3d[j].s=tex3d[j-2].s;
					tex3d[j].t=tex3d[j-2].t;
					}
				pts3d[p].x=pts3d[0].x;
				pts3d[p].y=pts3d[0].y;
				tex3d[p].s=tex3d[0].s;
				tex3d[p].t=tex3d[0].t;
				}
			p+=pl;
			if (pl==3)
				{
				pts3d[p].x=pts3d[0].x;
				pts3d[p].y=pts3d[0].y;
				tex3d[p].s=tex3d[0].s;
				tex3d[p].t=tex3d[0].t;
				p++;
				}
			pts3d+=p;
			tex3d+=p;
			errpol:;
			}
		}

	SetTextureQuadOutput3DB(texaddr3DB[0]);
	if ((p=pts3d-Vertex)>0)
		Render3DB(p);
	clearlists
	}



// Draw polygons without sorting (overlapping polys)
void dispolsnx()
	{
	objs *cobj=objlist;
	short i,n;
	word np,col;
	dword *polytex;

	while (cobj!=curobj)
		{
		n=cobj->nopols;
		curpol=cobj++->polys;
		for (i=0;i<n;i++)
			{
			curpts=curpol++->pts;
			np=(word)curpts[0];
			col=(word)curpts[1];
			curpts+=2;

if (col>=512) col=257;
			
			// Choose routine to use from np & col
			if (col<-2000)
 				{
				polytex=(dword *)&textures[-col-2000];
				polyt((pnt *)curpts,np,mapsel[*(((BYTE *)polytex)+3)],polytex+np,polytex);
				continue;
				}
			if (col<0)
 				{
				polytex=(dword *)&textures[-col];
				polym((pnt *)curpts,np,mapsel[*(((BYTE *)polytex)+3)],polytex+np,polytex);
				continue;
				}
			if (col>=512)
	 			{
				polytex=(dword *)&texloop[(col&255)].tex;
//				polytex=(dword *)&textures[(col&255)+S_TM];
				polyl((pnt *)curpts,np,mapsel[mappages-2+(col&255)],polytex+np,polytex);
//	 			polyl((pnt *)curpts,np,mapsel[mappages-2+(col>>8)],polytex+np,polytex);
				continue;
				}
			if (col>=256)
 				{
				polyf((pnt *)curpts,np,filters[col&255]);
				continue;
				}
			if (np<=2)
				if (np==1)
					{sprite3d(curpts[0]/render_buff.scale_x,(render_buff.clip_hgt-curpts[1])/render_buff.scale_y,col);curpts+=2;}
				else		   
					line((pnt *)curpts,col);
			else
				poly((pnt *)curpts,np,col);
			}
 
		}
		clearlists
	}



/********************/
/* PALETTE ROUTINES */

/*
// Set palette
void setpal()
	{
	short i;
	unsigned char *p=pal;
	for (i=0;i<256;i++)
		{
		outp(0x3c8,i);
		outp(0x3c9,*p++);
		outp(0x3c9,*p++);
		outp(0x3c9,*p++);
		}
	}

// Get palette
void getpal()
	{
	short i;
	unsigned char *p=pal;
	for (i=0;i<256;i++)
		{
		outp(0x3c7,i);
		*p++=inp(0x3c9);
		*p++=inp(0x3c9);
		*p++=inp(0x3c9);
		}
	}
*/

void setpal()
	{
	union REGS regs;
	struct SREGS sregs;
	memset(&sregs,0,sizeof(sregs));
	regs.w.ax=0x1012;
	regs.w.bx=0;
	regs.w.cx=256;
	regs.x.edx=FP_OFF(&pal[0]);
	sregs.es=FP_SEG(&pal[0]);
	int386x(0x10,&regs,&regs,&sregs);
	}

/*
void getpal()
	{
	union REGS regs;
	struct SREGS sregs;
	memset(&sregs,0,sizeof(sregs));
	regs.w.ax=0x1017;
	regs.w.bx=0;
	regs.w.cx=256;
	regs.x.edx=FP_OFF(&pal[0]);
	sregs.es=FP_SEG(&pal[0]);
	int386x(0x10,&regs,&regs,&sregs);
	}

void readcolour(unsigned short c,unsigned char r,unsigned char g,unsigned char b)
	{
	union REGS regs;
	regs.w.ax=0x1010;
	regs.w.bx=c;
	regs.h.ch=g;
	regs.h.cl=b;
	regs.h.dh=r;
	int386(0x10,&regs,&regs);
	}

void writecolour(unsigned short c,unsigned char *r,unsigned char *g,unsigned char *b)
	{
	union REGS regs;
	regs.w.ax=0x1015;
	regs.w.bx=c;
	int386(0x10,&regs,&regs);
	*g=regs.h.ch;
	*b=regs.h.cl;
	*r=regs.h.dh;
	}
*/

// Make a filter array for polygon filters
void makefilter(filter filt,byte fr,byte fg,byte fb,float mr,float mg,float mb)
	{
	word r1,g1,b1,r2,g2,b2;
	word x,s,c,l1,l2,d1,d2;
	if ((l1=sqrt(fr*fr+fg*fg+fb*fb))==0) l1=1;
	for (x=0;x<768;x+=3)	 
		{
		l2=sqrt(pal[x]*pal[x]+pal[x+1]*pal[x+1]+pal[x+2]*pal[x+2]);
		r1=pal[x]+mr*(fr*l2/l1-pal[x]);
		if (r1<0) r1=0;if (r1>255) r1=255;
		g1=pal[x+1]+mg*(fg*l2/l1-pal[x+1]);
		if (g1<0) g1=0;if (g1>255) g1=255;
		b1=pal[x+2]+mb*(fb*l2/l1-pal[x+2]);
		if (b1<0) b1=0;if (b1>255) b1=255;
		r1=(fr-pal[x])*mr+pal[x];
		g1=(fg-pal[x+1])*mg+pal[x+1];
		b1=(fb-pal[x+2])*mb+pal[x+2];
		d1=128;
		for (s=0;s<768-16*3;s+=3)
			{
		 	r2=(pal[s]-r1);
			g2=(pal[s+1]-g1);
			b2=(pal[s+2]-b1);
			d2=sqrt(r2*r2+g2*g2+b2*b2);
			if (d2<d1) d1=d2,c=s;
			}
		filt[x/3]=c/3;
		}
	}


void makehilite(filter filt,short add)
	{
	short s;
	for (s=0;s<256;s++)
		filt[s]=(s&15)+add;
	}


/*******************/
/* (S)VGA ROUTINES */

// Set standard VGA mode
void VGAmode(BYTE mode)
	{
 	union REGS r;
	r.h.al=(char)mode;
	r.h.ah=0;
	int386(0x10,&r,&r);
	}


// Switch screen mode through VESAmode list & MCGA (0x13)
//  or through 3dBlaster modes
void switchmode()
	{
	short i;
	if (scrmode3DB<0)
		{
		if (scrmode==0x13)
 			{
			testVESA=0;
			scrmode=VESAmode(&modelist[i=0]);
			while (scrmode!=modelist[i] && ++i!=VESAMODES);
			if (i!=VESAMODES)
				main_buff=VESA_buff[i][setup.screen_size];
			else
				scrmode=0x13;
			}
		else
			{
  			VGAmode(0x13);
			main_buff=MCGA_buff[setup.screen_size];
			scrmode=0x13;
			}
		setpal();
		}
	else
		{
#ifdef BLASTDEMO
		if (++scrmode3DB==MODES_3DB||(scrmode3DB=ChangeScreenMode3DB(modelist3DB+scrmode3DB))<0)
			scrmode3DB=ChangeScreenMode3DB(modelist3DB);
#else
		switch (scrmode3DB)
			{
			case 0: scrmode3DB=ChangeScreenMode3DB(&modelist3DB[1]);break;
			case 3: scrmode3DB=ChangeScreenMode3DB(&modelist3DB[2]);break;
			case 5: scrmode3DB=ChangeScreenMode3DB(&modelist3DB[0]);break;
			}
#endif
		main_buff=buff_3DB[scrmode3DB];
		pal[3]=pal[4]=pal[5]=63;
		pal[191*3]=pal[191*3+1]=pal[191*3+2]=0;
	  	SetPalette3DB(pal);
		}
	}

// Clear virtual buffer
void vclear(BYTE *buffpt,short w,short h,short bw,char fill)
	{
	short i;
	for (i=0;i<h;i++)
		{
		memset(buffpt,fill,w);
		buffpt+=bw;
		}
	}

// Clear buffer
void clearbuffer(buff_info *buffer,char fill)
	{
	vclear(buffer->buff_start,buffer->clip_wid,buffer->clip_hgt,buffer->buff_wid,fill);
	}
	
// Copy buffer to current MCGA screen
void mcgacpy(BYTE *buffpt,short x,short y,short w,short h,short bw)
	{
	short i;
	char *scrpt;
	scrpt=(char *)0xa0000+x+320*y;
	for (i=0;i<h;i++)
		memcpy(scrpt,buffpt,w),buffpt+=bw,scrpt+=320;
	}


// Copy buffer to current VESA screen
void svgacpy(BYTE *buffpt,short x,short y,short w,short h,short bw)
	{
	union REGS regs;
	short i,co;
	char *scrpt;
	int scrdisp=x+Vbytesperline*y;
	char bank=scrdisp/winrange;

	if (w<1||h<1) return;
	scrdisp%=winrange;
	scrpt=(char *)0xa0000+scrdisp;
	regs.x.eax=0x4f05;
	regs.x.ebx=0;
	regs.x.edx=bank;
	int386(16,&regs,&regs);
	do
		{
		co=min((winrange-scrdisp)/Vbytesperline,h);
		for (i=0;i<co;i++)
			{
			memcpy(scrpt,buffpt,w);
			scrpt+=Vbytesperline;
			buffpt+=bw;
			h--;
			}
		if (h)
			{
			scrdisp=(scrdisp+(co+1)*Vbytesperline)%winrange;
			co=min(Vbytesperline-scrdisp,w);
			memcpy(scrpt,buffpt,co);
 			bank++;	 
 			regs.x.eax=0x4f05;
 			regs.x.ebx=0;
 			regs.x.edx=bank;
  			int386(16,&regs,&regs);
 			if (co!=w) 
				memcpy((char *)0xa0000,buffpt+co,w-co);
			scrpt=(char *)0xa0000+scrdisp;
			buffpt+=bw;
			h--;
		 	}
		}while (h);
	regs.x.eax=0x4f05;
	regs.x.ebx=0;
	regs.x.edx=0;
	int386(16,&regs,&regs);
	}



/***********************/
/* BINARY SAVE ROUTINE */
	
int writebin(char *BinFile, BYTE *fPtr, int fLen)
{
	int fHandle, fCount;
	short fDone, fTry;

	if ((fHandle = open((char *)BinFile, O_CREAT | O_RDWR | O_BINARY, S_IWRITE)) != -1)
	{
		fCount = fDone = fTry = 0;
		while (fCount != fLen && fDone == fTry)
		{
			fTry = min(fLen - fCount, 32766);
			fDone = write(fHandle, fPtr + fCount, fTry);
			fCount += fDone;
		}
		if (fDone != fTry)
			fCount = -1;
		close(fHandle);
	}
	else
		fCount = -1;
	return (fCount);
}


BYTE *readbin(char *BinFile, BYTE *fPtr, dword *fLen)
{
	int fHandle, fCount;
	short fDone, fTry;
	BYTE *fRes = fPtr;

	if ((fHandle = open((char *)BinFile, O_RDONLY | O_BINARY)) != -1)
	{
		*fLen = filelength(fHandle);
 		if (fPtr != NULL || (fPtr = (BYTE *)mallocx(*fLen)) != NULL)
		{
			fCount = fDone = fTry = 0;
			while (fCount != *fLen && fDone == fTry)
			{
				fTry = min(*fLen - fCount, 32766);
				fDone = read(fHandle, fPtr + fCount, fTry);
				fCount += fDone;
			}
			if (fDone != fTry)
			{
				if (fRes == NULL)
					freex(fPtr);
					fPtr = NULL;
			}
		}
		close(fHandle);
	}
	else
		fPtr = NULL;
	return (fPtr);
}

BYTE *readrawfile(char *filename, BYTE *address)
	{
	BYTE *ptr;
	dword len;
	if ((ptr=readbin(filename, address, &len))==NULL)
		printf("Error loading file %s\n",filename);
	return (ptr);
	}

#ifdef JAPAN
char datafile[]="actrend.dat";
char dataoffs[]="actrend.off";
char fapfile[]="fapj.dat";
char fapoffs[]="fapj.off";
#else
#ifndef FLOPPY
char datafile[]="actrend.dat";
char dataoffs[]="actrend.off";
char fapfile[]="fap.dat";
char fapoffs[]="fap.off";
#else
#ifndef BBS
char datafile[]="actrendf.dat";
char dataoffs[]="actrendf.off";
char fapfile[]="fapf.dat";
char fapoffs[]="fapf.off";
#else
char datafile[]="actrendb.dat";
char dataoffs[]="actrendb.off";
char fapfile[]="fapf.dat";
char fapoffs[]="fapf.off";
#endif
#endif
#endif

struct {	int offset,size; } load_offsets[MAX_FILES];
FILE *fd;

int opendatafile(char *datafile)
	{
	fd=fopen(datafile, "rb");
	if (fd==NULL)
		{
		puts("Can't find data file.");
		return(-1);
		}
	return(0);
	}

void closedatafile()
	{
	if (fd!=NULL)
		fclose(fd);
	fd=NULL;
	}

BYTE *readdatafile(int fileno, BYTE *address)
{
	BYTE *ptr;
	int seek_pos,file_size;
	seek_pos=load_offsets[fileno/8].offset;
	file_size=load_offsets[fileno/8].size;
	fseek(fd,seek_pos,SEEK_SET);
	if (address==NULL) 
		{ if ((ptr=(BYTE *)mallocx(file_size*sizeof(BYTE)))==NULL) return(NULL); }
	else
		ptr=address;
	fread(ptr, sizeof(BYTE), file_size, fd);
	return(ptr);
}

BYTE *readfile(int fileno, BYTE *address)
	{
	BYTE *ptr;
	if ((ptr=readdatafile(fileno, address))==NULL)
		printf("Error loading data file %d\n",fileno);
	return (ptr);
	}

BYTE *readdatafilesection(int fileno, BYTE *address, int start_offset, int section_size)
{
	int seek_pos;
	seek_pos=load_offsets[fileno/8].offset+start_offset;
	fseek(fd,seek_pos,SEEK_SET);
	fread(address, sizeof(BYTE), section_size, fd);
	return (address);
}


BYTE *readfileblock(int fileno, int blockno, int blocks, BYTE *address)
	{
	int flen;
	BYTE *ptr;
	flen=load_offsets[fileno/8].size;
	if ((ptr=readdatafilesection(fileno,address+flen*blockno/blocks,flen*blockno/blocks,flen*(blockno+1)/blocks-flen*blockno/blocks))==NULL)
		printf("Error loading data file %d\n",fileno);
	return (ptr);
	}



#define FRM_WID 128
#define FRM_HGT 80
#define FRM_LEN (FRM_WID*FRM_HGT)
#define ANIM_SPACE 280000
//#define ANIM_SPACE 172000

char *anim_data;
int anim_start[]={0,10241,10241,10241,10241,10241,10241,10241,10241+91600,10241,10241+126777,10241,10241+127983};

char *buff_ptr;

typedef struct { int no,time;char *frmptr; } anim_info;
anim_info vidi;
int vidi_in,vidi_anim,vcount;


void
init_anim(anim_info &anim,int no)
	{
	int i;
//	char *buffp=buff_ptr;
	char *buffp=(char *)(maps[S_BM])+stadlist[setup.stadium].vmap;
	char *animp;

	anim.no=no;
	anim.time=count;
	animp=anim.frmptr=anim_data+anim_start[no];

	for (i=0;i<FRM_HGT;i++)
		{
		memcpy(buffp,animp,FRM_WID);
		buffp+=256;
		animp+=FRM_WID;
		}
	anim.frmptr=animp;

	}


void
stop_anim(anim_info &anim)
	{
#ifdef AMERICA
	readfile(COL_VR,(BYTE *)&pal[240*3]);
#else
	readfile(COL_VIDI,(BYTE *)&pal[240*3]);
#endif
	setpal();
	init_anim(anim,0);
	vidi_anim=0;
	}


void
do_anim(anim_info &anim)
	{
	int i,j,ttime,tval,tlen;
	int buffd=256-FRM_WID;
//	char *buffp=buff_ptr;
	char *buffp=(char *)(maps[S_BM])+stadlist[setup.stadium].vmap;
	char *animp;

	if (anim.no && (ttime=count)>anim.time+10)
		if (!*anim.frmptr)
		 	{
			if (vidi_anim==7||vidi_anim==9||vidi_anim==11)
				vidi_anim++;
			init_anim(anim,vidi_anim);
		 	}
		else
			{
			if (--vcount<=0)
				stop_anim(anim);
			else
				{
				animp=anim.frmptr;
				anim.time=ttime;

				tlen=FRM_WID;
				while (tval=*animp++)
					{

					while (tlen<tval)	
						{
						tval-=tlen;
						while (tlen--) (*buffp++) = (*animp++);
						tlen=FRM_WID,buffp+=buffd;
						}
					tlen-=tval;
					while (tval--) (*buffp++) = (*animp++);

					tval=*animp++;
					while (tlen<tval)	
						{
						tval-=tlen;
						while (tlen--) buffp++;
						tlen=FRM_WID,buffp+=buffd;
						}
					tlen-=tval;
					while (tval--) buffp++;
					}

				anim.frmptr=animp;
				}
	  		}
	}


int spool;

void
do_extra_time_anim(int sp)
	{
#ifdef FLOPPY
	return;
#else
	if (!setup.M8) return;
	vidi_anim=1;
	spool=sp;
	if (spool==10||vidi_in==1)
		{
		spool=0;
		readfile(COL_XET,(BYTE *)&pal[240*3]);
		setpal();
		vidi_in=1;
		vcount=200;
		init_anim(vidi,1);
		return;
		}
	readfileblock(FAP_XET,spool,10,(BYTE *)anim_data+10241);
	spool++;
#endif
	}

void
do_foul_anim(int sp)
	{
#ifdef FLOPPY
	return;
#else
	if (!setup.M8) return;
	vidi_anim=2;
	spool=sp;
	if (spool==10||vidi_in==2)
		{
		spool=0;
		readfile(COL_XFOU,(BYTE *)&pal[240*3]);
		setpal();
		vidi_in=2;
		vcount=100;
		init_anim(vidi,2);
		return;
		}
	readfileblock(FAP_XFOU,spool,10,(BYTE *)anim_data+10241);
	spool++;
#endif
	}

void
do_full_time_anim(int sp)
	{
#ifdef FLOPPY
	return;
#else
	if (!setup.M8) return;
	vidi_anim=3;
	spool=sp;
	if (spool==10||vidi_in==3)
		{
		spool=0;
		readfile(COL_XFT,(BYTE *)&pal[240*3]);
		setpal();
		vidi_in=3;
		vcount=200;
		init_anim(vidi,3);
		return;
		}
	readfileblock(FAP_XFT,spool,10,(BYTE *)anim_data+10241);
	spool++;
#endif
	}

void
do_half_time_anim(int sp)
	{
#ifdef FLOPPY
	return;
#else
	if (!setup.M8) return;
	vidi_anim=4;
	spool=sp;
	if (spool==10||vidi_in==4)
		{
		spool=0;
		readfile(COL_XHT,(BYTE *)&pal[240*3]);
		setpal();
		vidi_in=4;
		vcount=300;
		init_anim(vidi,4);
		return;
		}
	readfileblock(FAP_XHT,spool,10,(BYTE *)anim_data+10241);
	spool++;
#endif
	}

void
do_penalty_anim(int sp)
	{
#ifdef FLOPPY
	return;
#else
	if (!setup.M8) return;
	vidi_anim=5;
	spool=sp;
	if (spool==10||vidi_in==5)
		{
		spool=0;
		readfile(COL_XPEN,(BYTE *)&pal[240*3]);
		setpal();
		vidi_in=5;
		vcount=100;
		init_anim(vidi,5);
		return;
		}
	readfileblock(FAP_XPEN,spool,10,(BYTE *)anim_data+10241);
	spool++;
#endif
	}

/*
void
do_goal_anim(int sp)
	{
	if (!setup.M8) return;
	if (vidi_in!=6) readfile(FAP_XGOA,(BYTE *)anim_data+10241);
	readfile(COL_XGOA,(BYTE *)&pal[240*3]);
	setpal();
	vidi_anim=vidi_in=6;
	vcount=200;
	init_anim(vidi,6);
	}
*/
void
do_goal_anim(int sp)
	{
	if (!setup.M8) return;
	vidi_anim=6;
	spool=sp;
	if (spool==10||vidi_in==6)
		{
		spool=0;
//#ifndef BBS
//		readfile(COL_BOOST,(BYTE *)&pal[240*3]);
//#else
		readfile(COL_XGOA,(BYTE *)&pal[240*3]);
//#endif
		setpal();
		vidi_in=6;
		vcount=200;
		init_anim(vidi,6);
		return;
		}
//#ifndef BBS
//	readfileblock(FAP_BOOST,spool,10,(BYTE *)anim_data+10241);
//#else
	readfileblock(FAP_XGOA,spool,10,(BYTE *)anim_data+10241);
//#endif
	spool++;
	}

void
do_win_f_anim(int sp)
	{
#ifdef FLOPPY
	return;
#else
	if (!setup.M8) return;
	vidi_anim=7;
	spool=sp;
	if (spool==10||vidi_in==7)
		{
		spool=0;
		readfile(COL_XWNF,(BYTE *)&pal[240*3]);
		setpal();
		vidi_in=7;
		vcount=100000;
		init_anim(vidi,7);
		return;
		}
	readfileblock(FAP_XWNF1,spool,10,(BYTE *)anim_data+10241);
	readfileblock(FAP_XWNF2,spool,10,(BYTE *)anim_data+10241+91600);
	spool++;
#endif
	}

void
do_win_g_anim(int sp)
	{
#ifdef FLOPPY
	return;
#else
	if (!setup.M8) return;
	vidi_anim=9;
	spool=sp;
	if (spool==10||vidi_in==9)
		{
		spool=0;
		readfile(COL_XWNG,(BYTE *)&pal[240*3]);
		setpal();
		vidi_in=9;
		vcount=100000;
		init_anim(vidi,9);
		return;
		}
	readfileblock(FAP_XWNG1,spool,10,(BYTE *)anim_data+10241);
	readfileblock(FAP_XWNG2,spool,10,(BYTE *)anim_data+10241+126777);
	spool++;
#endif
	}

void
do_win_s_anim(int sp)
	{
#ifdef FLOPPY
	return;
#else
	if (!setup.M8) return;
	vidi_anim=11;
	spool=sp;
	if (spool==10||vidi_in==11)
		{
		spool=0;
		readfile(COL_XWNS,(BYTE *)&pal[240*3]);
		setpal();
		vidi_in=11;
		vcount=100000;
		init_anim(vidi,11);
		return;
		}
	readfileblock(FAP_XWNS1,spool,10,(BYTE *)anim_data+10241);
	readfileblock(FAP_XWNS2,spool,10,(BYTE *)anim_data+10241+127983);
	spool++;
#endif
	}



/*********************/
/* IN-GAME FRONT END */

#if 0

texture_info 	IngameTextureDEFN={NULL,256,256};
pseudo_info 	IngamePseudoDEFN;

void InitSprites()
	{
	ReadDataOffsetFile(dataoffs);			 	// Load data offset file. 

	Euro96_MemoryInitialise();					// Resets all Euro memory handles.

	TextStringMemHandle  =						// Set up memory handle.
		AllocateTextStringMemory(); 			// Allocate memory for text strings..

	process_script_file("ingame.spt");		// Reads script file and compiles relevent data for game.

	TexturePageMemHandle =				 	 	// Set up memory handle.
		AllocateTexturePageMemory( 1,   		// Specify number of texture pages to allocate.
			&IngameTextureDEFN );		  		// Allocate memory for frontend texture pages.

	IngameTextureDEFN.page_start 	= (BYTE *)TexturePages;	// Specify memory address used for texture pages.
	}

void LoadPage()
	{
	LoadTexturePage( BM_EXTRA1, 	 	  	// Load texture page 1 into texture memory.
			 datafile, 0,
			 &IngameTextureDEFN );
	}



void UninitSprites()
	{
	DeAllocateMemory(TexturePageMemHandle);  		// DeAllocates memory used previously for textures.
	DeAllocateMemory(TextStringMemHandle);			// DeAllocates memory used previously for text strings.
	}

#endif


#define NO_MENUS 24
buff_info menu_buff_l[NO_MENUS]=
	{
	 {NULL, 320,64, 320,64, 0, 0, dumpnull},
	 {NULL, 320,64, 320,64, 0, 0, dumpnull},
	 {NULL, 320,64, 320,64, 0, 0, dumpnull},
	 {NULL, 320,64, 224,64, 0, 0, dumpnull},
	 {NULL, 320,64, 224,64, 0, 0, dumpnull},
	 {NULL, 320,64, 192,64, 0, 0, dumpnull},
	 {NULL, 320,64, 192,64, 0, 0, dumpnull},
	 {NULL, 320,64, 192,64, 0, 0, dumpnull},
	 {NULL, 320,64, 192,64, 0, 0, dumpnull},
	 {NULL, 320,64, 192,64, 0, 0, dumpnull},
	 {NULL, 320,64, 224,64, 0, 0, dumpnull},
	 {NULL, 320,64, 320,64, 0, 0, dumpnull},
	 {NULL, 320,128, 288,128, 0, 0, dumpnull},
	 {NULL, 320,128, 288,128, 0, 0, dumpnull},
	 {NULL, 320,128, 288,128, 0, 0, dumpnull},
	 {NULL, 320,128, 288,128, 0, 0, dumpnull},
	 {NULL, 320,128, 288,128, 0, 0, dumpnull},
	 {NULL, 320,64, 320,64, 0, 0, dumpnull},
	 {NULL, 320,128, 160,128, 0, 0, dumpnull},
	 {NULL, 320,112, 160,112, 0, 0, dumpnull},
	 {NULL, 320,128, 224,128, 0, 0, dumpnull},
	 {NULL, 320,80, 288,80, 0, 0, dumpnull},
//	 {NULL, 320,64, 224,64, 0, 0, dumpnull},
	 {NULL, 320,64, 320,64, 0, 0, dumpnull},
	 {NULL, 320,160, 256,160, 0, 0, dumpnull},
	};
buff_info menu_buff_h[NO_MENUS]=
	{
	 {NULL, 640,128, 640,128, 0, 0, dumpnull},
	 {NULL, 640,128, 640,128, 0, 0, dumpnull},
	 {NULL, 640,128, 640,128, 0, 0, dumpnull},
	 {NULL, 640,128, 448,128, 0, 0, dumpnull},
	 {NULL, 640,128, 448,128, 0, 0, dumpnull},
	 {NULL, 640,128, 384,128, 0, 0, dumpnull},
	 {NULL, 640,128, 384,128, 0, 0, dumpnull},
	 {NULL, 640,128, 384,128, 0, 0, dumpnull},
	 {NULL, 640,128, 384,128, 0, 0, dumpnull},
	 {NULL, 640,128, 384,128, 0, 0, dumpnull},
	 {NULL, 640,128, 448,128, 0, 0, dumpnull},
	 {NULL, 640,128, 640,128, 0, 0, dumpnull},
	 {NULL, 640,256, 576,256, 0, 0, dumpnull},
	 {NULL, 640,256, 576,256, 0, 0, dumpnull},
	 {NULL, 640,256, 576,256, 0, 0, dumpnull},
	 {NULL, 640,256, 576,256, 0, 0, dumpnull},
	 {NULL, 640,256, 576,256, 0, 0, dumpnull},
	 {NULL, 640,128, 640,128, 0, 0, dumpnull},
	 {NULL, 640,256, 320,256, 0, 0, dumpnull},
	 {NULL, 640,224, 320,224, 0, 0, dumpnull},
	 {NULL, 640,256, 448,256, 0, 0, dumpnull},
	 {NULL, 640,160, 576,160, 0, 0, dumpnull},
//	 {NULL, 640,128, 448,128, 0, 0, dumpnull},
	 {NULL, 640,128, 640,128, 0, 0, dumpnull},
	 {NULL, 640,320, 512,320, 0, 0, dumpnull},
	};

struct mtime {
  	unsigned short min;
	float secs;
};

extern mtime match_time;
extern int team_a_goals;
extern int team_b_goals;

extern goal_table	goals[];
extern team_info	game_data[2];
//extern match_data match_info;
extern match_player teams[22];

float slco;
int slide,oslide,mcount,menu,mhgt,rdmenu;
int mdata1,mdata2,mdata3;

void
draw_sprite(buff_info *buff,int sprite_no,int x,int y,BYTE col)
	{
	int sd;
	if (scrmode3DB>=0)
		{
			x+=menx3DB;
			y+=meny3DB;
			curpts3DB->x=x<<16;
			curpts3DB->y=((render_buff.clip_hgtl-(y+spr_data[sprite_no].hgt))<<16);
			if (curpts3DB->y<0x10000)
				{
				sd=curpts3DB->y-0x10000;
				curpts3DB->y=0x10000;
				}
			else
				sd=0;
			curpts3DB++;
			curpts3DB->x=((x+spr_data[sprite_no].wid)<<16);
			curpts3DB->y=(render_buff.clip_hgtl-y)<<16;
			if (curpts3DB->y<0) {curpts3DB--;return;}
			curpts3DB++;
			curtex3DB++;
			(curtex3DB-1)->s=0x1000000+((spr_data[sprite_no].x)<<16);
			curtex3DB->t=0x2000000+(spr_data[sprite_no].page<<24)+((spr_data[sprite_no].y)<<16);
			curtex3DB->s=(curtex3DB-1)->s+((spr_data[sprite_no].wid+1)<<16);
			(curtex3DB-1)->t=curtex3DB->t+((spr_data[sprite_no].hgt+1)<<16)+sd;
			curtex3DB++;
		}
	else
		{
		BYTE *spt=buff->buff_start+y*buff->buff_wid+x;
		BYTE *spd=maps[X_BM+spr_data[sprite_no].page]+spr_data[sprite_no].y*256+spr_data[sprite_no].x;
		int w=min(spr_data[sprite_no].wid,buff->clip_wid-x);
		int h=min(spr_data[sprite_no].hgt,buff->clip_hgt-y);
		int ts=buff->buff_wid-w;
		int ds=256-w;
		int i,j;
		BYTE c;
		if (w<0||h<0) return;
		for (i=0;i<h;i++)
			{
			for (j=0;j<w;j++)
				{
				c=*spd++;
				if (c) if (!--c) *spt=col; else *spt=c;
				spt++;
				}
			spt+=ts;
			spd+=ds;
			}
		}
	}

void
draw_sprite_d(buff_info *buff,int sprite_no,int x,int y,BYTE col)
	{
	int sd;
	if (scrmode3DB>=0)
		{
			x+=menx3DB;
			y+=meny3DB;
			curpts3DB->x=x<<16;
			curpts3DB->y=(render_buff.clip_hgtl-(y+(spr_data[sprite_no].hgt<<1)))<<16;
			if (curpts3DB->y<0x10000)
				{
				sd=curpts3DB->y-0x10000;
				curpts3DB->y=0x10000;
				}
			else
				sd=0;
			curpts3DB++;
			curpts3DB->x=(x+(spr_data[sprite_no].wid<<1))<<16;
			curpts3DB->y=(render_buff.clip_hgtl-y)<<16;
			if (curpts3DB->y<0) {curpts3DB--;return;}
			curpts3DB++;
			curtex3DB++;
			(curtex3DB-1)->s=0x1000000+((spr_data[sprite_no].x)<<16);
			curtex3DB->t=0x2000000+(spr_data[sprite_no].page<<24)+((spr_data[sprite_no].y)<<16);
			curtex3DB->s=(curtex3DB-1)->s+((spr_data[sprite_no].wid+1)<<16);
			(curtex3DB-1)->t=curtex3DB->t+((spr_data[sprite_no].hgt+1)<<16)+sd;
			curtex3DB++;
		}
	else
		{						 
		BYTE *spt=buff->buff_start+y*buff->buff_wid+x;
		BYTE *spd=maps[X_BM+spr_data[sprite_no].page]+spr_data[sprite_no].y*256+spr_data[sprite_no].x;
		int w=min(spr_data[sprite_no].wid,buff->clip_wid-x);
		int h=min(spr_data[sprite_no].hgt,buff->clip_hgt-y);
		int ts=buff->buff_wid-(w<<1);
		int ds=256-w;
		int i,j;
		BYTE c;
		if (w<0||h<0) return;
		for (i=0;i<h;i++)
			{
			for (j=0;j<w;j++)
				{
				c=*spd++;
				if (c) if (!--c) *spt=col; else *spt=c;
				spt++;
				if (c) if (!--c) *spt=col; else *spt=c;
				spt++;
				}
			spt+=ts;
			spd-=w;
			for (j=0;j<w;j++)
				{
				c=*spd++;
				if (c) if (!--c) *spt=col; else *spt=c;
				spt++;
				if (c) if (!--c) *spt=col; else *spt=c;
				spt++;
				}
			spt+=ts;
			spd+=ds;
			}
		}
	}

void
draw_sprite_s(buff_info *buff,int sprite_no,int x,int y,BYTE col)
	{
	int sd;
	if (scrmode3DB>=0)
		{
			x+=menx3DB;
			y+=meny3DB;
			curpts3DB->x=x<<16;
			curpts3DB->y=(render_buff.clip_hgtl-(y+spr_data[sprite_no].hgt))<<16;
			if (curpts3DB->y<0x10000)
				{
				sd=curpts3DB->y-0x10000;
				curpts3DB->y=0x10000;
				}
			else
				sd=0;
			curpts3DB++;
			curpts3DB->x=(x+spr_data[sprite_no].wid)<<16;
			curpts3DB->y=(render_buff.clip_hgtl-y)<<16;
			if (curpts3DB->y<0) {curpts3DB--;return;}
			curpts3DB++;
			curtex3DB++;
			(curtex3DB-1)->s=0x1000000+((spr_data[sprite_no].x)<<16);
			curtex3DB->t=0x2000000+(spr_data[sprite_no].page<<24)+((spr_data[sprite_no].y)<<16);
			curtex3DB->s=(curtex3DB-1)->s+((spr_data[sprite_no].wid+1)<<16);
			(curtex3DB-1)->t=curtex3DB->t+((spr_data[sprite_no].hgt+1)<<16)+sd;
			curtex3DB++;
		}
	else
		{
		BYTE *spt=buff->buff_start+y*buff->buff_wid+x;
		BYTE *spd=maps[X_BM+spr_data[sprite_no].page]+spr_data[sprite_no].y*256+spr_data[sprite_no].x;
		int w=min(spr_data[sprite_no].wid,buff->clip_wid-x);
		int h=min(spr_data[sprite_no].hgt,buff->clip_hgt-y);
		int ts=buff->buff_wid-w;
		int ds=256-w;
		int i,j;
		BYTE c;
		if (w<0||h<0) return;
		for (i=0;i<h;i++)
			{
			for (j=0;j<w;j++)
				{
				c=*spd++;
				if (--c) *spt=c;
				spt++;
				}
			spt+=ts;
			spd+=ds;
			}
		}
	}

void
draw_sprite_vf(buff_info *buff,int sprite_no,int x,int y,BYTE col)
	{
	int sd;
	if (scrmode3DB>=0)
		{
			x+=menx3DB;
			y+=meny3DB;
			curpts3DB->x=x<<16;
			curpts3DB->y=(render_buff.clip_hgtl-(y+spr_data[sprite_no].hgt))<<16;
			if (curpts3DB->y<0x10000)
				{
				sd=curpts3DB->y-0x10000;
				curpts3DB->y=0x10000;
				}
			else
				sd=0;
			curpts3DB++;
			curpts3DB->x=(x+spr_data[sprite_no].wid)<<16;
			curpts3DB->y=(render_buff.clip_hgtl-y)<<16;
			if (curpts3DB->y<0) {curpts3DB--;return;}
			curpts3DB++;
			curtex3DB++;
			(curtex3DB-1)->s=0x1000000+((spr_data[sprite_no].x)<<16);
			(curtex3DB-1)->t=0x2000000+(spr_data[sprite_no].page<<24)+((spr_data[sprite_no].y-1)<<16)-sd;
			curtex3DB->s=(curtex3DB-1)->s+((spr_data[sprite_no].wid+1)<<16);
			curtex3DB->t=(curtex3DB-1)->t+((spr_data[sprite_no].hgt)<<16)+sd;
			curtex3DB++;
		}
	else
		{
		BYTE *spt=buff->buff_start+y*buff->buff_wid+x;
		BYTE *spd=maps[X_BM+spr_data[sprite_no].page]+spr_data[sprite_no].y*256+spr_data[sprite_no].x+(spr_data[sprite_no].hgt-1)*256;
		int w=min(spr_data[sprite_no].wid,buff->clip_wid-x);
		int h=min(spr_data[sprite_no].hgt,buff->clip_hgt-y);
		int ts=buff->buff_wid-w;
		int ds=256+w;
		int i,j;
		BYTE c;
		for (i=0;i<h;i++)
			{
			for (j=0;j<w;j++)
				{
				c=*spd++;
				if (c) if (!--c) *spt=col; else *spt=c;
				spt++;
				}
			spt+=ts;
			spd-=ds;
			}
		}
	}

void
draw_sprite_r(buff_info *buff,int sprite_no,int x,int y,BYTE col)
	{
	int sd;
	if (scrmode3DB>=0)
		{
			x+=menx3DB;
			y+=meny3DB;
			curpts3DB->x=(x+spr_data[sprite_no].wid)<<16;
			curpts3DB->y=(render_buff.clip_hgtl-(y+spr_data[sprite_no].hgt))<<16;
			curpts3DB++;
			curpts3DB->x=x<<16;
			curpts3DB->y=(render_buff.clip_hgtl-y)<<16;
			curpts3DB++;
			curtex3DB++;
			(curtex3DB-1)->s=0x1000000+((spr_data[sprite_no].x)<<16);
			curtex3DB->t=0x2000000+(spr_data[sprite_no].page<<24)+((spr_data[sprite_no].y+1)<<16);
			curtex3DB->s=(curtex3DB-1)->s+((spr_data[sprite_no].wid+1)<<16);
			(curtex3DB-1)->t=curtex3DB->t+((spr_data[sprite_no].hgt+1)<<16);
			curtex3DB++;
		}
	else
		{
		BYTE *spt=buff->buff_start+y*buff->buff_wid+x;
		BYTE *spd=maps[X_BM+spr_data[sprite_no].page]+spr_data[sprite_no].y*256+spr_data[sprite_no].x;
		BYTE *tspd;
		int w=min(spr_data[sprite_no].wid,buff->clip_wid-x);
		int h=min(spr_data[sprite_no].hgt,buff->clip_hgt-y);
		int ts=buff->buff_wid-w;
		int ds=256-w;
		int i,j;
		BYTE c;
		if (w<0||h<0) return;
		for (i=0;i<h;i++)
			{
			tspd=spd;
			for (j=0;j<w;j++)
				{
				c=*spd;
				spd+=256;
				if (c) if (!--c) *spt=col; else *spt=c;
				spt++;
				}
			spt+=ts;
			spd=tspd+1;
			}
		}
	}

void
draw_sprite_hf(buff_info *buff,int sprite_no,int x,int y,BYTE col)
	{
	int sd;
	if (scrmode3DB>=0)
		{
			x+=menx3DB;
			y+=meny3DB;
			curpts3DB->x=x<<16;
			curpts3DB->y=(render_buff.clip_hgtl-(y+spr_data[sprite_no].hgt))<<16;
			if (curpts3DB->y<0x10000)
				{
				sd=curpts3DB->y-0x10000;
				curpts3DB->y=0x10000;
				}
			else
				sd=0;
			curpts3DB++;
			curpts3DB->x=(x+spr_data[sprite_no].wid)<<16;
			curpts3DB->y=(render_buff.clip_hgtl-y)<<16;
			if (curpts3DB->y<0) {curpts3DB--;return;}
			curpts3DB++;
			curtex3DB++;
			curtex3DB->s=0x1000000+((spr_data[sprite_no].x-1)<<16);
			curtex3DB->t=0x2000000+(spr_data[sprite_no].page<<24)+((spr_data[sprite_no].y)<<16);
			(curtex3DB-1)->s=curtex3DB->s+((spr_data[sprite_no].wid)<<16);
			(curtex3DB-1)->t=curtex3DB->t+((spr_data[sprite_no].hgt+1)<<16)+sd;
			curtex3DB++;
		}
	else
		{
		BYTE *spt=buff->buff_start+y*buff->buff_wid+x;
		BYTE *spd=maps[X_BM+spr_data[sprite_no].page]+spr_data[sprite_no].y*256+spr_data[sprite_no].x+spr_data[sprite_no].wid-1;
		int w=min(spr_data[sprite_no].wid,buff->clip_wid-x);
		int h=min(spr_data[sprite_no].hgt,buff->clip_hgt-y);
		int ts=buff->buff_wid-w;
		int ds=256+w;
		int i,j;
		BYTE c;
		for (i=0;i<h;i++)
			{
			for (j=0;j<w;j++)
				{
				c=*spd--;
				if (c) if (!--c) *spt=col; else *spt=c;
				spt++;
				}
			spt+=ts;
			spd+=ds;
			}
		}
	}

void
draw_sprite_vhf(buff_info *buff,int sprite_no,int x,int y,BYTE col)
	{
	int sd;
	if (scrmode3DB>=0)
		{
			x+=menx3DB;
			y+=meny3DB;
			curpts3DB->x=x<<16;
			curpts3DB->y=(render_buff.clip_hgtl-(y+spr_data[sprite_no].hgt))<<16;
			if (curpts3DB->y<0x10000)
				{
				sd=curpts3DB->y-0x10000;
				curpts3DB->y=0x10000;
				}
			else
				sd=0;
			curpts3DB++;
			curpts3DB->x=(x+spr_data[sprite_no].wid)<<16;
			curpts3DB->y=(render_buff.clip_hgtl-y)<<16;
			if (curpts3DB->y<0) {curpts3DB--;return;}
			curpts3DB++;
			curtex3DB++;
			curtex3DB->s=0x1000000+((spr_data[sprite_no].x-1)<<16);
			(curtex3DB-1)->t=0x2000000+(spr_data[sprite_no].page<<24)+((spr_data[sprite_no].y-1)<<16)-sd;
			(curtex3DB-1)->s=curtex3DB->s+((spr_data[sprite_no].wid)<<16);
			curtex3DB->t=(curtex3DB-1)->t+((spr_data[sprite_no].hgt)<<16)+sd;
			curtex3DB++;
		}
	else
		{
		BYTE *spt=buff->buff_start+y*buff->buff_wid+x;
		BYTE *spd=maps[X_BM+spr_data[sprite_no].page]+spr_data[sprite_no].y*256+spr_data[sprite_no].x+(spr_data[sprite_no].hgt-1)*256+spr_data[sprite_no].wid-1;
		int w=min(spr_data[sprite_no].wid,buff->clip_wid-x);
		int h=min(spr_data[sprite_no].hgt,buff->clip_hgt-y);
		int ts=buff->buff_wid-w;
		int ds=256-w;
		int i,j;
		BYTE c;
		for (i=0;i<h;i++)
			{
			for (j=0;j<w;j++)
				{
				c=*spd--;
				if (c) if (!--c) *spt=col; else *spt=c;
				spt++;
				}
			spt+=ts;
			spd-=ds;
			}
		}
	}

int
string_len(int font_no,char *string)
	{
	BYTE c;
	int len=0;
	while (c=*string++)
		{
		if (c==' ') c=';';
		if (c=='.') c='@';
		if (c==',') c='?';
		if (c=='>')	c='A';
		if (c>='a'&&c<='z') c-=32;
		if (c=='O') c='0';
		if (c=='&') c='O';
		c-=48;
		len+=font_data[font_no].prp[c]+1;
		}
	return(len);
	}

int
draw_string(buff_info *buff,int font_no,int x,int y,char *string,BYTE col,short just)
	{
	BYTE c,ec;
	int len;
	len=string_len(font_no,string);
	switch (just)
		{
		case 1:
			x-=len;
			break;
		case 2:
			x-=len>>1;
			break;
		}
	while (c=*string++)
		{
		if (c==' ') c=';';
		if (c=='.') c='@';
		if (c==',') c='?';
		if (c=='>')
			{
			c-=48;
			ec=c+font_data[font_no].off;
			spr_data[0].page=font_data[font_no].page;
			spr_data[0].x=font_data[font_no].x+font_data[font_no].wid*(ec%font_data[font_no].n);
			spr_data[0].y=font_data[font_no].y+font_data[font_no].hgt*(ec/font_data[font_no].n);
			spr_data[0].wid=font_data[font_no].prp[c];
			spr_data[0].hgt=font_data[font_no].hgt;
			draw_sprite(buff,0,x,y-font_data[font_no].hgt,col);
			c='A';
			}
		if (c>='a'&&c<='z') c-=32;
		if (c=='O') c='0';
		if (c=='&') c='O';
		c-=48;
		ec=c+font_data[font_no].off;
		spr_data[0].page=font_data[font_no].page;
		spr_data[0].x=font_data[font_no].x+font_data[font_no].wid*(ec%font_data[font_no].n);
		spr_data[0].y=font_data[font_no].y+font_data[font_no].hgt*(ec/font_data[font_no].n);
		spr_data[0].wid=font_data[font_no].prp[c];
		spr_data[0].hgt=font_data[font_no].hgt;
		draw_sprite(buff,0,x,y,col);
		x+=font_data[font_no].prp[c]+1;
		}
		return (len);
	}

void rectshadow3DB(buff_info *buff,int x,int y,int w,int h)
	{
	int tx,tw,i,j,c,d;
	while (h>=62)
		{
		tx=x;
		tw=w;
		while (w>=64)
			{
			draw_sprite(buff,93,x,y,0);
			x+=64;
			w-=64;
			}
		for (i=0,c=32;i<5;i++,c>>=1)
			if (w&c)
				{
				draw_sprite(buff,94+i,x,y,0);
				x+=c;
				}
		x=tx;
		w=tw;
		h-=62;
		y+=62;
		}
	for (i=0,c=32;i<5;i++,c>>=1)
		if (h&c)
			{
			tx=x;
			tw=w;
			while (w>=64)
				{
				draw_sprite(buff,99+i*6,x,y,0);
				x+=64;
				w-=64;
				}
			for (j=0,d=32;j<5;j++,d>>=1)
				if (w&d)
					{
					draw_sprite(buff,100+i*6+j,x,y,0);
					x+=d;
					}
			x=tx;
			w=tw;
			h-=c;
			y+=c;
			}
	}


void
draw_menu_box(buff_info *buff)
	{
	short f,w,wd,hd;
	BYTE *col=filters[0];
	BYTE *sc;
	if (scrmode!=0x13)
		{
		if ((hd=min(buff->buff_hgt-(19+32)*2,buff->clip_hgt-19-32))>0)
			if (scrmode3DB<0)
				{
				wd=buff->clip_wid-20*2;
				sc=buff->buff_start+(19+32)*buff->buff_wid+20;
				for (f=hd;f;f--)
					{
					w=wd;
					do {*sc=col[*sc];sc++;} while (--w);
					sc+=render_buff.buff_wid-wd;
					}
				}
			else
				rectshadow3DB(buff,20,19+32,buff->clip_wid-20*2,hd);
		draw_sprite(buff,21,11,10+32,0);
		draw_sprite_hf(buff,21,buff->clip_wid-32,10+32,0);
		draw_sprite_vhf(buff,21,buff->clip_wid-32,buff->buff_hgt-32-32,0);
		draw_sprite_vf(buff,21,11,buff->buff_hgt-32-32,0);
		for (f=32;f<buff->clip_wid-32;f+=32)
			{
			draw_sprite(buff,22,f,10+32,0);
			draw_sprite(buff,22,f,buff->buff_hgt-19-32,0);
			}
		for (f=32+32;f<buff->buff_hgt-32-32;f+=32)
			{
			draw_sprite(buff,23,11,f,0);
			draw_sprite(buff,23,buff->clip_wid-20,f,0);
			}
		}
	else
		{
		if ((hd=min(buff->buff_hgt-(10+16)*2,buff->clip_hgt-10-16))>0)
			if (scrmode3DB<0)
				{
				wd=buff->clip_wid-10*2;
				sc=buff->buff_start+(10+16)*buff->buff_wid+10;
				for (f=hd;f;f--)
					{
					w=wd;
					do {*sc=col[*sc];sc++;} while (--w);
					sc+=render_buff.buff_wid-wd;
					}
				}
			else
				rectshadow3DB(buff,10,10+16,buff->clip_wid-10*2,hd);
		draw_sprite(buff,32,5,5+16,0);
		draw_sprite_hf(buff,32,buff->clip_wid-16,5+16,0);
		draw_sprite_vhf(buff,32,buff->clip_wid-16,buff->buff_hgt-16-16,0);
		draw_sprite_vf(buff,32,5,buff->buff_hgt-16-16,0);
		for (f=16;f<buff->clip_wid-16;f+=32)
			{
			draw_sprite(buff,33,f,5+16,0);
			draw_sprite(buff,33,f,buff->buff_hgt-10-16,0);
			}
		for (f=16+16;f<buff->buff_hgt-32-16;f+=32)
			{
			draw_sprite(buff,34,5,f,0);
			draw_sprite(buff,34,buff->clip_wid-10,f,0);
			}
		if (f<buff->buff_hgt-16-16)
			{
			draw_sprite(buff,83,5,f,0);
			draw_sprite(buff,83,buff->clip_wid-10,f,0);
			}
		}
	}


void 
goal_menu(buff_info *buff, int team, int player, int time)
	{
	int shirt;
	if (!team)
		shirt=ppt[player+((match_half&1)?11:0)].number-1;
	else
		shirt=ppt[player+((match_half&1)?0:11)].number-1;
	draw_menu_box(buff);
	if (scrmode==0x13)
		{
		draw_sprite(buff,30+team,10,11,0);
		draw_sprite(buff,2+shirt,16,21,0);
		draw_string(buff,0,160,30, GetTEXT( GLSC_TEXT ) ,207,1);
		if (!team)
			draw_string(buff,0,160,30,
					GetPLAYERSname( EUROmatch_info.TeamAsquad[player], setup.team_a, INITIAL_SURNAME ),
					31,0);

		else
			draw_string(buff,0,160,30,
					GetPLAYERSname( EUROmatch_info.TeamBsquad[player], setup.team_b, INITIAL_SURNAME ),
					31,0);

		draw_sprite(buff,40,278,18,0);
		}
	else
		{
		draw_sprite(buff,19+team,20,24,0);
		draw_string(buff,2,320,56, GetTEXT( GLSC_TEXT ),207,1);

		if (!team)
			{
			draw_sprite_s(buff,53+shirt,42,51,0);
			draw_string(buff,2,320,56,
				GetPLAYERSname( EUROmatch_info.TeamAsquad[player], setup.team_a, INITIAL_SURNAME ),
				31,0);
			}
		else
			{
			draw_sprite_s(buff,68+shirt,42,51,0);
			draw_string(buff,2,320,56,
				GetPLAYERSname( EUROmatch_info.TeamBsquad[player], setup.team_b, INITIAL_SURNAME ),
				31,0);
			}
		draw_sprite(buff,29,556,38,0);
		}
	}

void 
booked_menu(buff_info *buff, int team, int player)
	{
	int shirt;
	if (!team)
		shirt=ppt[player+((match_half&1)?11:0)].number-1;
	else
		shirt=ppt[player+((match_half&1)?0:11)].number-1;
	draw_menu_box(buff);
	if (scrmode==0x13)
		{
		draw_sprite(buff,30+team,10,11,0);
		draw_sprite(buff,2+shirt,16,21,0);
		draw_string(buff,0,160,30,GetTEXT( YLCD_TEXT ),157,1);
		if (!team)
			draw_string(buff,0,160,30,
				GetPLAYERSname( EUROmatch_info.TeamAsquad[player], setup.team_a, INITIAL_SURNAME ),
				31,0);
		else
			draw_string(buff,0,160,30,
				GetPLAYERSname( EUROmatch_info.TeamBsquad[player], setup.team_b, INITIAL_SURNAME ),
				31,0);
		draw_sprite(buff,51,276,9,0);
		draw_sprite(buff,52,276,11,0);
		}
	else
		{
		draw_sprite(buff,19+team,20,24,0);
		draw_string(buff,2,320,56,GetTEXT( YLCD_TEXT ),157,1);
		if (!team)
			{
			draw_sprite_s(buff,53+shirt,42,51,0);
			draw_string(buff,2,320,56,
				GetPLAYERSname( EUROmatch_info.TeamAsquad[player], setup.team_a, INITIAL_SURNAME ),
				31,0);
			}
		else
			{
			draw_sprite_s(buff,68+shirt,42,51,0);
			draw_string(buff,2,320,56,
				GetPLAYERSname( EUROmatch_info.TeamBsquad[player], setup.team_b, INITIAL_SURNAME ),
				31,0);
			}
		draw_sprite(buff,45,552,18,0);
		draw_sprite(buff,46,552,24,0);
		}
	}

void 
off_menu(buff_info *buff, int team, int player)
	{
	int shirt;
	if (!team)
		shirt=ppt[player+((match_half&1)?11:0)].number-1;
	else
		shirt=ppt[player+((match_half&1)?0:11)].number-1;
	draw_menu_box(buff);
	if (scrmode==0x13)
		{
		draw_sprite(buff,30+team,10,11,0);
		draw_sprite(buff,2+shirt,16,21,0);
		draw_string(buff,0,160,30,GetTEXT( RDCD_TEXT ),127,1);
		if (!team)
			draw_string(buff,0,160,30,
				GetPLAYERSname( EUROmatch_info.TeamAsquad[player], setup.team_a, INITIAL_SURNAME ),
				31,0);
		else
			draw_string(buff,0,160,30,
				GetPLAYERSname( EUROmatch_info.TeamBsquad[player], setup.team_b, INITIAL_SURNAME ),
				31,0);
		draw_sprite(buff,50,276,9,0);
		draw_sprite(buff,52,276,11,0);
		}
	else
		{
		draw_sprite(buff,19+team,20,24,0);
		draw_string(buff,2,320,56,GetTEXT( RDCD_TEXT ),127,1);
		if (!team)
			{
			draw_sprite_s(buff,53+shirt,42,51,0);
			draw_string(buff,2,320,56,
				GetPLAYERSname( EUROmatch_info.TeamAsquad[player], setup.team_a, INITIAL_SURNAME ),
				31,0);
			}
		else							
			{
			draw_sprite_s(buff,68+shirt,42,51,0);
			draw_string(buff,2,320,56,
				GetPLAYERSname( EUROmatch_info.TeamBsquad[player], setup.team_b, INITIAL_SURNAME ),
				31,0);
			}
		draw_sprite(buff,44,552,18,0);
		draw_sprite(buff,46,552,24,0);
		}
	}

void 
direct_menu(buff_info *buff, int team)
	{
	draw_menu_box(buff);
	if (scrmode==0x13)
		{
		draw_sprite(buff,30+team,10,11,0);
		draw_string(buff,0,112,30,GetTEXT( DRKC_TEXT ),31,2);
		draw_sprite(buff,52,188,11,0);
		}
	else
		{
		draw_sprite(buff,19+team,20,24,0);
		draw_string(buff,2,224,56,GetTEXT( DRKC_TEXT ),31,2);
		draw_sprite(buff,46,376,24,0);
		}
	}

void 
indirect_menu(buff_info *buff, int team)
	{
	draw_menu_box(buff);
	if (scrmode==0x13)
		{
		draw_sprite(buff,30+team,10,11,0);
		draw_string(buff,0,112,30,GetTEXT( IDKC_TEXT ),31,2);
		draw_sprite(buff,52,188,11,0);
		}
	else
		{
		draw_sprite(buff,19+team,20,24,0);
		draw_string(buff,2,224,56,GetTEXT( IDKC_TEXT ),31,2);
		draw_sprite(buff,46,376,24,0);
		}
	}

void 
penalty_menu(buff_info *buff, int team)
	{
	draw_menu_box(buff);
	if (scrmode==0x13)
		{
		draw_sprite(buff,30+team,10,11,0);
		draw_string(buff,0,96,30,GetTEXT( PENK_TEXT ),31,2);
		draw_sprite(buff,52,151,11,0);
		}
	else
		{
		draw_sprite(buff,19+team,20,24,0);
		draw_string(buff,2,192,56,GetTEXT( PENK_TEXT ),31,2);
		draw_sprite(buff,46,302,24,0);
		}
	}

void 
corner_menu(buff_info *buff, int team)
	{
	draw_menu_box(buff);
	if (scrmode==0x13)
		{
		draw_sprite(buff,30+team,10,11,0);
		draw_string(buff,0,96,30,GetTEXT( CORK_TEXT ),31,2);
		draw_sprite(buff,40,151,18,0);
		}
	else
		{
		draw_sprite(buff,19+team,20,24,0);
		draw_string(buff,2,192,56,GetTEXT( CORK_TEXT ),31,2);
		draw_sprite(buff,29,302,38,0);
		}
	}

void 
throw_menu(buff_info *buff, int team)
	{
	draw_menu_box(buff);
	if (scrmode==0x13)
		{
		draw_sprite(buff,30+team,10,11,0);
		draw_string(buff,0,96,30,GetTEXT( THIN_TEXT ),31,2);
		draw_sprite(buff,40,151,18,0);
		}
	else
		{
		draw_sprite(buff,19+team,20,24,0);
		draw_string(buff,2,192,56,GetTEXT( THIN_TEXT ),31,2);
		draw_sprite(buff,29,302,38,0);
		}
	}

void 
goalkick_menu(buff_info *buff, int team)
	{
	draw_menu_box(buff);
	if (scrmode==0x13)
		{
		draw_sprite(buff,30+team,10,11,0);
		draw_string(buff,0,96,30,GetTEXT( GKIK_TEXT ),31,2);
		draw_sprite(buff,40,151,18,0);
		}
	else
		{
		draw_sprite(buff,19+team,20,24,0);
		draw_string(buff,2,192,56,GetTEXT( GKIK_TEXT ),31,2);
		draw_sprite(buff,29,302,38,0);
		}
	}

void 
kickoff_menu(buff_info *buff, int team)
	{
	draw_menu_box(buff);
	if (scrmode==0x13)
		{
		draw_sprite(buff,30+team,10,11,0);
		draw_string(buff,0,96,30,GetTEXT( KIOF_TEXT ),31,2);
		draw_sprite(buff,40,151,18,0);
		}
	else
		{
		draw_sprite(buff,19+team,20,24,0);
		draw_string(buff,2,192,56,GetTEXT( KIOF_TEXT ),31,2);
		draw_sprite(buff,29,302,38,0);
		}
	}

void 
offside_menu(buff_info *buff, int team)
	{
	draw_menu_box(buff);
	if (scrmode==0x13)
		{
		draw_sprite(buff,30+team,10,11,0);
		draw_string(buff,0,112,30,GetTEXT( OFFS_TEXT ),31,2);
		draw_sprite(buff,52,188,11,0);
		}
	else
		{
		draw_sprite(buff,19+team,20,24,0);
		draw_string(buff,2,224,56,GetTEXT( OFFS_TEXT ),31,2);
		draw_sprite(buff,46,376,24,0);
		}
	}

void 
injured_menu(buff_info *buff, int team, int player)
	{
	int shirt;
	if (!team)
		shirt=ppt[player+((match_half&1)?11:0)].number-1;
	else
		shirt=ppt[player+((match_half&1)?0:11)].number-1;
	draw_menu_box(buff);
	if (scrmode==0x13)
		{
		draw_sprite(buff,30+team,10,11,0);
		draw_sprite(buff,2+shirt,16,21,0);
		draw_string(buff,0,160,30,GetTEXT( PLIN_TEXT ),127,1);
		if (!team)
			draw_string(buff,0,160,30,
				GetPLAYERSname( EUROmatch_info.TeamAsquad[player], setup.team_a, INITIAL_SURNAME ),
				31,0);
		else
			draw_string(buff,0,160,30,
				GetPLAYERSname( EUROmatch_info.TeamBsquad[player], setup.team_b, INITIAL_SURNAME ),
				31,0);
		draw_sprite(buff,52,280,11,0);
		}
	else
		{
		draw_sprite(buff,19+team,20,24,0);
		draw_string(buff,2,320,56,GetTEXT( PLIN_TEXT ),127,1);
		if (!team)
			{
			draw_sprite_s(buff,53+shirt,42,51,0);
			draw_string(buff,2,320,56,
				GetPLAYERSname( EUROmatch_info.TeamAsquad[player], setup.team_a, INITIAL_SURNAME ),
				31,0);
			}
		else							
			{
			draw_sprite_s(buff,68+shirt,42,51,0);
			draw_string(buff,2,320,56,
				GetPLAYERSname( EUROmatch_info.TeamBsquad[player], setup.team_b, INITIAL_SURNAME ),
				31,0);
			}
		draw_sprite(buff,46,560,24,0);
		}
	}

extern referee_info referee_data[];

void 
ref_menu(buff_info *buff)
	{
	char tlstr[50];
	int ln;
	draw_menu_box(buff);
	if (scrmode==0x13)
		{
		draw_sprite(buff,52,13,11,0);
		draw_string(buff,0,160,30,GetTEXT( RFRE_TEXT ),207,1);
		strcpy(tlstr, EUROmatch_info.RefsName );
//		strcat(tlstr," = ");
//		strcat(tlstr,game_data[ referee_data[match_info.match_referee].country ].Nickname);
		draw_string(buff,0,160,30,tlstr,31,0);
		draw_sprite(buff,52,284,11,0);
		}
	else
		{
		draw_sprite(buff,46,26,24,0);
		draw_string(buff,2,320,56,GetTEXT( RFRE_TEXT ),207,1);
		strcpy(tlstr, EUROmatch_info.RefsName );
//		strcat(tlstr," = ");
//		strcat(tlstr,game_data[ referee_data[match_info.match_referee].country ].Nickname);
		draw_string(buff,2,320,56,tlstr,31,0);
		draw_sprite(buff,46,578,24,0);
		}
	}

void	GOAL_SCORED( int team, int scorer, int time )
{
	int	goal_slot	=	-1;
	int	goal_count	=	0;

		// FIND AN EMPTY GOAL SLOT WITHIN GOAL DATA...

		while	( goal_slot==-1 )
		{
					
			if ( goals[goal_count].goal_data.used == NULL )
			{
			 	goal_slot				=	goal_count;
				goals[goal_slot].goal_data.used		=	ACTIVE;				
			}
		     	
			else
		
			{
			goal_count++;
			
				if ( goal_count>90 )
				{
					goals[0].goal_data.used	=	NULL;
					goal_count		=	0;
				}
			}			
		}


	goals[goal_slot].goal_data.time		=	time+1;				

		// CALCULATE NORMAL GOAL....


		if	( (time & O_G)==0 )
		{
			
			if ( scorer<11 )
			{
				goals[goal_slot].goal_data.scorer	=	game_data[TEMPa].players[scorer].squad_number;	//was scorer-1
				goals[goal_slot].goal_data.used|=		CREDIT_TEAMa;
				EUROmatch_info.Team_A_goals++;
			}
			else
			{
				goals[goal_slot].goal_data.scorer	=	game_data[TEMPb].players[scorer-11].squad_number;   //was scorer-12
				goals[goal_slot].goal_data.used|=		CREDIT_TEAMb;
				EUROmatch_info.Team_B_goals++;
			}
		}


		// CALCULATE OWN GOAL....

		if	( (time & O_G)!=0 )
		{

		goals[goal_slot].goal_data.used		=	O_G >> 8;				

			if ( scorer<11 )     
			{
				goals[goal_slot].goal_data.scorer	=	game_data[TEMPa].players[scorer].squad_number;	     //was scorer-1
				goals[goal_slot].goal_data.used|=		CREDIT_TEAMb;
				EUROmatch_info.Team_B_goals++;
			}

			else
			{
				goals[goal_slot].goal_data.scorer	=	game_data[TEMPb].players[scorer-11].squad_number;     //was scorer-12
				goals[goal_slot].goal_data.used|=		CREDIT_TEAMa;
				EUROmatch_info.Team_A_goals++;
			}
		}
}


void
score_breakdown_l(buff_info *buff)
	{
	int g,gc;
	int l;
	int m;
	char tstr[50];

	g=0;
	m=52;
	while (goals[g].goal_data.used)
		{
		if ((goals[g].goal_data.used&5)==4)
			{
			l=0;
			if (!(goals[g].goal_data.time&512))
				{
				for (int sf=0;sf<22;sf++)
					if (game_data[TEMPa].players[sf].squad_number==goals[g].goal_data.scorer) break;
				sprintf(tstr,"%s ",
//					&game_data[setup.team_a].players[sf].name[game_data[setup.team_a].players[sf].goal_index]);
					&GetPLAYERSname( EUROmatch_info.TeamAsquad[sf], setup.team_a, INITIAL_SURNAME )[0]);
					

				}
			else
				{
				for (int sf=0;sf<22;sf++)
					if (game_data[TEMPb].players[sf].squad_number==goals[g].goal_data.scorer) break;
				sprintf(tstr,"%s ",
//					&game_data[setup.team_b].players[sf].name[game_data[setup.team_b].players[sf].goal_index]);
					&GetPLAYERSname( EUROmatch_info.TeamBsquad[sf], setup.team_b, INITIAL_SURNAME )[0]);
				}
			l+=draw_string(buff,0,l+40,m,tstr,157,0);
			gc=g;
			do	{
				if (goals[gc].goal_data.time&768)
					{
					if (l>=50)	if ((m+=8,l=0)>52+5*8) goto mend1;


//-------------------------------------------------------------------------------
//					if (EUROmatch_info.language!=2)
//						if (goals[gc].goal_data.time&256)
//							sprintf(tstr,"%d PEN",goals[gc].goal_data.time&255);
//						else
//							sprintf(tstr,"%d O.G",goals[gc].goal_data.time&255);
//					else
//						if (goals[gc].goal_data.time&256)
//							sprintf(tstr,"%d ELF",goals[gc].goal_data.time&255);
//						else
//							sprintf(tstr,"%d ET",goals[gc].goal_data.time&255);
//-------------------------------------------------------------------------------


		// replaces above code... Forget about translations, new code will handle it.

						if (goals[gc].goal_data.time&256)
							sprintf(tstr,"%d %s",goals[gc].goal_data.time&255, GetTEXT( PENS_TEXT ) );
						else
							sprintf(tstr,"%d %s",goals[gc].goal_data.time&255, GetTEXT( OWNG_TEXT ) );

					}
				else
					{
					if (l>=78)	if ((m+=8,l=0)>52+5*8) goto mend1;
					sprintf(tstr,"%d",goals[gc].goal_data.time);
					}
				l+=draw_string(buff,0,l+40,m,tstr,157,0);
				goals[gc].goal_data.used|=1;
				do {
					gc++;
					if ((goals[gc].goal_data.used&5)==4 && goals[gc].goal_data.scorer==goals[g].goal_data.scorer && (goals[gc].goal_data.time&512)==(goals[g].goal_data.time&512))
						{
						l+=draw_string(buff,0,l+40,m,",",157,0);
						break;
						}
					} while (goals[gc].goal_data.used);
				} while (goals[gc].goal_data.used);
			if ((m+=8)>52+5*8) goto mend1;
			}
		g++;
		}
	mend1:;
	mhgt=((m+40)>>4)<<4;

	g=0;
	m=52;
	while (goals[g].goal_data.used)
		{
		if ((goals[g].goal_data.used&9)==8)
			{
			l=0;
			if (!(goals[g].goal_data.time&512))
				{
				for (int sf=0;sf<22;sf++)
					if (game_data[TEMPb].players[sf].squad_number==goals[g].goal_data.scorer) break;

				sprintf(tstr,"%s ",
//					&game_data[setup.team_b].players[sf].name[game_data[setup.team_b].players[sf].goal_index]);
					&GetPLAYERSname( EUROmatch_info.TeamBsquad[sf], setup.team_b, INITIAL_SURNAME )[0]);
				}
			else
				{
				for (int sf=0;sf<22;sf++)
					if (game_data[TEMPa].players[sf].squad_number==goals[g].goal_data.scorer) break;
				sprintf(tstr,"%s ",
//					&game_data[setup.team_a].players[sf].name[game_data[setup.team_a].players[sf].goal_index]);
					&GetPLAYERSname( EUROmatch_info.TeamAsquad[sf], setup.team_a, INITIAL_SURNAME )[0]);
				}
			l+=draw_string(buff,0,l+178,m,tstr,157,0);
			gc=g;
			do	{
				if (goals[gc].goal_data.time&768)
					{
					if (l>=50)	if ((m+=8,l=0)>52+5*8) goto mend2;

//-------------------------------------------------------------------------------
//					if (match_info.language!=2)
//						if (goals[gc].goal_data.time&256)
//							sprintf(tstr,"%d PEN",goals[gc].goal_data.time&255);
//						else
//							sprintf(tstr,"%d O.G",goals[gc].goal_data.time&255);
//					else
//						if (goals[gc].goal_data.time&256)
//							sprintf(tstr,"%d ELF",goals[gc].goal_data.time&255);
//						else
//							sprintf(tstr,"%d ET",goals[gc].goal_data.time&255);
//-------------------------------------------------------------------------------

		// replaces above code... Forget about translations, new code will handle it.

						if (goals[gc].goal_data.time&256)
							sprintf(tstr,"%d %s",goals[gc].goal_data.time&255, GetTEXT( PENS_TEXT ) );
						else
							sprintf(tstr,"%d %s",goals[gc].goal_data.time&255, GetTEXT( OWNG_TEXT ) );

					


					}
				else
					{
					if (l>=78)	if ((m+=8,l=0)>52+5*8) goto mend2;
					sprintf(tstr,"%d",goals[gc].goal_data.time);
					}
				l+=draw_string(buff,0,l+178,m,tstr,157,0);
				goals[gc].goal_data.used|=1;
				do {
					gc++;
					if ((goals[gc].goal_data.used&9)==8 && goals[gc].goal_data.scorer==goals[g].goal_data.scorer && (goals[gc].goal_data.time&512)==(goals[g].goal_data.time&512))
						{
						l+=draw_string(buff,0,l+178,m,",",157,0);
						break;
						}
					} while (goals[gc].goal_data.used);
				} while (goals[gc].goal_data.used);
			if ((m+=8)>52+5*8) goto mend2;
			}
		g++;
		}
	mend2:;
	if (mhgt<((m+40)>>4)<<4) mhgt=((m+40)>>4)<<4;

	gc=0;
	while (goals[gc].goal_data.used)
		goals[gc++].goal_data.used&=0xfe;
	}


void
score_breakdown_h(buff_info *buff)
	{
	int g,gc;
	int l;
	int m;
	char tstr[50];

	g=0;
	m=104;
	while (goals[g].goal_data.used)
		{
		if ((goals[g].goal_data.used&5)==4)
			{
			l=0;
			if (!(goals[g].goal_data.time&512))
				{
				for (int sf=0;sf<22;sf++)
					if (game_data[TEMPa].players[sf].squad_number==goals[g].goal_data.scorer) break;
				sprintf(tstr,"%s ",
//					&game_data[setup.team_a].players[sf].name[game_data[setup.team_a].players[sf].goal_index]);
					&GetPLAYERSname( EUROmatch_info.TeamAsquad[sf], setup.team_a, INITIAL_SURNAME )[0]);
				}
			else
				{
				for (int sf=0;sf<22;sf++)
					if (game_data[TEMPb].players[sf].squad_number==goals[g].goal_data.scorer) break;
				sprintf(tstr,"%s ",
//					&game_data[setup.team_b].players[sf].name[game_data[setup.team_b].players[sf].goal_index]);
					&GetPLAYERSname( EUROmatch_info.TeamBsquad[sf], setup.team_b, INITIAL_SURNAME )[0]);
				}
			l+=draw_string(buff,2,l+80,m,tstr,157,0);
			gc=g;
			do	{
				if (goals[gc].goal_data.time&768)
					{
					if (l>=120)	if ((m+=13,l=0)>52+6*13) goto mend3;



//-------------------------------------------------------------------------------
//
//					if (match_info.language!=2)
//						if (goals[gc].goal_data.time&256)
//							sprintf(tstr,"%d PEN",goals[gc].goal_data.time&255);
//						else
//							sprintf(tstr,"%d O.G",goals[gc].goal_data.time&255);
//					else
//						if (goals[gc].goal_data.time&256)
//							sprintf(tstr,"%d ELF",goals[gc].goal_data.time&255);
//						else
//							sprintf(tstr,"%d ET",goals[gc].goal_data.time&255);
//
//-------------------------------------------------------------------------------

		// replaces above code... Forget about translations, new code will handle it.

						if (goals[gc].goal_data.time&256)
							sprintf(tstr,"%d %s",goals[gc].goal_data.time&255, GetTEXT( PENS_TEXT ) );
						else
							sprintf(tstr,"%d %s",goals[gc].goal_data.time&255, GetTEXT( OWNG_TEXT ) );

					


					}
				else
					{
					if (l>=176)	if ((m+=13,l=0)>52+6*13) goto mend3;
					sprintf(tstr,"%d",goals[gc].goal_data.time);
					}
				l+=draw_string(buff,2,l+80,m,tstr,157,0);
				goals[gc].goal_data.used|=1;
				do {
					gc++;
					if ((goals[gc].goal_data.used&5)==4 && goals[gc].goal_data.scorer==goals[g].goal_data.scorer && (goals[gc].goal_data.time&512)==(goals[g].goal_data.time&512))
						{
						l+=draw_string(buff,2,l+80,m,",",157,0);
						break;
						}
					} while (goals[gc].goal_data.used);
				} while (goals[gc].goal_data.used);
			if ((m+=13)>104+6*13) goto mend3;
			}
		g++;
		}
	mend3:;
	mhgt=((m+84)>>5)<<4;

	g=0;
	m=104;
	while (goals[g].goal_data.used)
		{
		if ((goals[g].goal_data.used&9)==8)
			{
			l=0;
			if (!(goals[g].goal_data.time&512))
				{
				for (int sf=0;sf<22;sf++)
					if (game_data[TEMPb].players[sf].squad_number==goals[g].goal_data.scorer) break;
				sprintf(tstr,"%s ",
//					&game_data[setup.team_b].players[sf].name[game_data[setup.team_b].players[sf].goal_index]);
					&GetPLAYERSname( EUROmatch_info.TeamBsquad[sf], setup.team_b, INITIAL_SURNAME )[0]);
				}
			else
				{
				for (int sf=0;sf<22;sf++)
					if (game_data[TEMPa].players[sf].squad_number==goals[g].goal_data.scorer) break;
				sprintf(tstr,"%s ",
//					&game_data[setup.team_a].players[sf].name[game_data[setup.team_a].players[sf].goal_index]);
					&GetPLAYERSname( EUROmatch_info.TeamAsquad[sf], setup.team_a, INITIAL_SURNAME )[0]);
				}
			l+=draw_string(buff,2,l+356,m,tstr,157,0);
			gc=g;
			do	{
				if (goals[gc].goal_data.time&768)
					{
					if (l>=120)	if ((m+=13,l=0)>104+6*13) goto mend4;



//-------------------------------------------------------------------------------
//
//					if (match_info.language!=2)
//						if (goals[gc].goal_data.time&256)
//							sprintf(tstr,"%d PEN",goals[gc].goal_data.time&255);
//						else
//							sprintf(tstr,"%d O.G",goals[gc].goal_data.time&255);
//					else
//						if (goals[gc].goal_data.time&256)
//							sprintf(tstr,"%d ELF",goals[gc].goal_data.time&255);
//						else
//							sprintf(tstr,"%d ET",goals[gc].goal_data.time&255);
//
//-------------------------------------------------------------------------------

		// replaces above code... Forget about translations, new code will handle it.

						if (goals[gc].goal_data.time&256)
							sprintf(tstr,"%d %s",goals[gc].goal_data.time&255, GetTEXT( PENS_TEXT ) );
						else
							sprintf(tstr,"%d %s",goals[gc].goal_data.time&255, GetTEXT( OWNG_TEXT ) );

					}
				else
					{
					if (l>=176)	if ((m+=13,l=0)>104+6*13) goto mend4;
					sprintf(tstr,"%d",goals[gc].goal_data.time);
					}
				l+=draw_string(buff,2,l+356,m,tstr,157,0);
				goals[gc].goal_data.used|=1;
				do {
					gc++;
					if ((goals[gc].goal_data.used&9)==8 && goals[gc].goal_data.scorer==goals[g].goal_data.scorer && (goals[gc].goal_data.time&512)==(goals[g].goal_data.time&512))
						{
						l+=draw_string(buff,2,l+356,m,",",157,0);
						break;
						}
					} while (goals[gc].goal_data.used);
				} while (goals[gc].goal_data.used);
			if ((m+=13)>104+6*13) goto mend4;
			}
		g++;
		}
	mend4:;
	if (mhgt<((m+84)>>5)<<4) mhgt=((m+84)>>5)<<4;

	gc=0;
	while (goals[gc].goal_data.used)
		goals[gc++].goal_data.used&=0xfe;
	}


void 
fulltime_menu(buff_info *buff)
	{
	char tstr[50];
	draw_menu_box(buff);
	if (scrmode==0x13)
		{
		draw_sprite(buff,30,10,11,0);
		draw_sprite(buff,31,243,11,0);
		draw_string(buff,1,144,30,GetTEXT( FLTM_TEXT ),207,2);
		draw_string(buff,0,110,42, EUROmatch_info.TeamAname, 31,1);
		sprintf(tstr,"%d",team_a_goals);
		draw_string(buff,0,131,42,tstr,31,1);
		sprintf(tstr,"%d",team_b_goals);
		draw_string(buff,0,157,42,tstr,31,0);
		draw_string(buff,0,178,42,EUROmatch_info.TeamBname,31,0);
//		draw_sprite(buff,49,134,38,0);
		score_breakdown_l(buff);
		}
	else
		{
		draw_sprite(buff,19,20,24,0);
		draw_sprite(buff,20,486,24,0);
		draw_string(buff,2,288,56,GetTEXT( FLTM_TEXT ),207,2);
		draw_string(buff,2,220,80,EUROmatch_info.TeamAname,31,1);
		sprintf(tstr,"%d",team_a_goals);
		draw_string(buff,2,262,80,tstr,31,1);
		sprintf(tstr,"%d",team_b_goals);
		draw_string(buff,2,314,80,tstr,31,0);
		draw_string(buff,2,356,80,EUROmatch_info.TeamBname,31,0);
//		draw_sprite(buff,43,268,72,0);
		score_breakdown_h(buff);
		}
	}

void 
extratime_menu(buff_info *buff)
	{
	char tstr[50];
	draw_menu_box(buff);
	if (scrmode==0x13)
		{
		draw_sprite(buff,30,10,11,0);
		draw_sprite(buff,31,243,11,0);
		draw_string(buff,1,144,30,GetTEXT( EXTM_TEXT ),207,2);
		draw_string(buff,0,110,42,EUROmatch_info.TeamAname,31,1);
		sprintf(tstr,"%d",team_a_goals);
		draw_string(buff,0,131,42,tstr,31,1);
		sprintf(tstr,"%d",team_b_goals);
		draw_string(buff,0,157,42,tstr,31,0);
		draw_string(buff,0,178,42,EUROmatch_info.TeamBname,31,0);
//		draw_sprite(buff,49,134,38,0);
		score_breakdown_l(buff);
		}
	else
		{
		draw_sprite(buff,19,20,24,0);
		draw_sprite(buff,20,486,24,0);
		draw_string(buff,2,288,56,GetTEXT( EXTM_TEXT ),207,2);
		draw_string(buff,2,220,80,EUROmatch_info.TeamAname,31,1);
		sprintf(tstr,"%d",team_a_goals);
		draw_string(buff,2,262,80,tstr,31,1);
		sprintf(tstr,"%d",team_b_goals);
		draw_string(buff,2,314,80,tstr,31,0);
		draw_string(buff,2,356,80,EUROmatch_info.TeamBname,31,0);
//		draw_sprite(buff,43,268,72,0);
		score_breakdown_h(buff);
		}
	}

void 
halftime_menu(buff_info *buff)
	{
	char tstr[50];
	draw_menu_box(buff);
	if (scrmode==0x13)
		{
		draw_sprite(buff,30,10,11,0);
		draw_sprite(buff,31,243,11,0);
		draw_string(buff,1,144,30,GetTEXT( HFTM_TEXT ),207,2);
		draw_string(buff,0,110,42,EUROmatch_info.TeamAname,31,1);
		sprintf(tstr,"%d",team_a_goals);
		draw_string(buff,0,131,42,tstr,31,1);
		sprintf(tstr,"%d",team_b_goals);
		draw_string(buff,0,157,42,tstr,31,0);
		draw_string(buff,0,178,42,EUROmatch_info.TeamBname,31,0);
//		draw_sprite(buff,49,134,38,0);
		score_breakdown_l(buff);
		}
	else
		{
		draw_sprite(buff,19,20,24,0);
		draw_sprite(buff,20,486,24,0);
		draw_string(buff,2,288,56,GetTEXT( HFTM_TEXT ),207,2);
		draw_string(buff,2,220,80,EUROmatch_info.TeamAname,31,1);
		sprintf(tstr,"%d",team_a_goals);
		draw_string(buff,2,262,80,tstr,31,1);
		sprintf(tstr,"%d",team_b_goals);
		draw_string(buff,2,314,80,tstr,31,0);
		draw_string(buff,2,356,80,EUROmatch_info.TeamBname,31,0);
//		draw_sprite(buff,43,268,72,0);
		score_breakdown_h(buff);
		}
	}


void 
penalty_shootout_menu(buff_info *buff)
	{
	char tstr[50];
	draw_menu_box(buff);
	if (scrmode==0x13)
		{
		draw_sprite(buff,30,10,11,0);
		draw_sprite(buff,31,243,11,0);
		draw_string(buff,1,144,30,GetTEXT( PNST_TEXT ),207,2);
		draw_string(buff,0,110,42,EUROmatch_info.TeamAname,31,1);
		sprintf(tstr,"%d",team_a_goals);
		draw_string(buff,0,131,42,tstr,31,1);
		sprintf(tstr,"%d",team_b_goals);
		draw_string(buff,0,157,42,tstr,31,0);
		draw_string(buff,0,178,42,EUROmatch_info.TeamBname,31,0);
//		draw_sprite(buff,49,134,38,0);
		score_breakdown_l(buff);
		}
	else
		{
		draw_sprite(buff,19,20,24,0);
		draw_sprite(buff,20,486,24,0);
		draw_string(buff,2,288,56,GetTEXT( PNST_TEXT ),207,2);
		draw_string(buff,2,220,80,EUROmatch_info.TeamAname,31,1);
		sprintf(tstr,"%d",team_a_goals);
		draw_string(buff,2,262,80,tstr,31,1);
		sprintf(tstr,"%d",team_b_goals);
		draw_string(buff,2,314,80,tstr,31,0);
		draw_string(buff,2,356,80,EUROmatch_info.TeamBname,31,0);
//		draw_sprite(buff,43,268,72,0);
		score_breakdown_h(buff);
		}
	}


void 
final_score_menu(buff_info *buff)
	{
	char tstr[50];
	draw_menu_box(buff);
	if (scrmode==0x13)
		{
		draw_sprite(buff,30,10,11,0);
		draw_sprite(buff,31,243,11,0);
		draw_string(buff,1,144,30,GetTEXT( FNSP_TEXT ),207,2);
		draw_string(buff,0,110,42,EUROmatch_info.TeamAname,31,1);
		sprintf(tstr,"%d",team_a_goals);
		draw_string(buff,0,131,42,tstr,31,1);
		sprintf(tstr,"%d",team_b_goals);
		draw_string(buff,0,157,42,tstr,31,0);
		draw_string(buff,0,178,42,EUROmatch_info.TeamBname,31,0);
//		draw_sprite(buff,49,134,38,0);
		score_breakdown_l(buff);
		}
	else
		{
		draw_sprite(buff,19,20,24,0);
		draw_sprite(buff,20,486,24,0);
		draw_string(buff,2,288,56,GetTEXT( FNSP_TEXT ),207,2);
		draw_string(buff,2,220,80,EUROmatch_info.TeamAname,31,1);
		sprintf(tstr,"%d",team_a_goals);
		draw_string(buff,2,262,80,tstr,31,1);
		sprintf(tstr,"%d",team_b_goals);
		draw_string(buff,2,314,80,tstr,31,0);
		draw_string(buff,2,356,80,EUROmatch_info.TeamBname,31,0);
//		draw_sprite(buff,43,268,72,0);
		score_breakdown_h(buff);
		}
	}

void 
owngoal_menu(buff_info *buff, int team, int player, int time)
	{
	int shirt;
	if (!team)
		shirt=ppt[player+((match_half&1)?11:0)].number-1;
	else
		shirt=ppt[player+((match_half&1)?0:11)].number-1;
	draw_menu_box(buff);
	if (scrmode==0x13)
		{
		draw_sprite(buff,30+team,10,11,0);
		draw_sprite(buff,2+shirt,16,21,0);
		draw_string(buff,0,160,30,GetTEXT( OWGL_TEXT ),207,1);
		if (!team)
			draw_string(buff,0,160,30,
				GetPLAYERSname( EUROmatch_info.TeamAsquad[player], setup.team_a, INITIAL_SURNAME ),
				31,0);
		else
			draw_string(buff,0,160,30,
				GetPLAYERSname( EUROmatch_info.TeamBsquad[player], setup.team_b, INITIAL_SURNAME ),
				31,0);
		draw_sprite(buff,40,278,18,0);
		}
	else
		{
		draw_sprite(buff,19+team,20,24,0);
		draw_string(buff,2,320,56,GetTEXT( OWGL_TEXT ),207,1);
		if (!team)
			{
			draw_sprite_s(buff,53+shirt,42,51,0);
			draw_string(buff,2,320,56,
				GetPLAYERSname( EUROmatch_info.TeamAsquad[player], setup.team_a, INITIAL_SURNAME ),
				31,0);
			}
		else
			{
			draw_sprite_s(buff,68+shirt,42,51,0);
			draw_string(buff,2,320,56,
				GetPLAYERSname( EUROmatch_info.TeamBsquad[player], setup.team_b, INITIAL_SURNAME ),
				31,0);
			}
		draw_sprite(buff,29,556,38,0);
		}
	}

#define M_WIDTH 256
extern short stat_sheet[11][2];

void 
stats_menu(buff_info *buff)
	{
	draw_menu_box(buff);
	if (scrmode==0x13)
		{
		draw_sprite(buff,30,8,8,0);	// Kit
		draw_sprite(buff,31,256-48,8,0);	// Kit
		draw_string(buff,0,M_WIDTH/2,32,"MATCH STATISTICS",207,2);
		draw_string(buff,0,M_WIDTH/2,54,"Tackling",31,2);
		draw_string(buff,0,M_WIDTH/2,61,"Passing",31,2);
		draw_string(buff,0,M_WIDTH/2,68,"Shooting",31,2);
		draw_string(buff,0,M_WIDTH/2,75,"Possession",31,2);
		draw_string(buff,0,M_WIDTH/2,82,"Work",31,2);
		draw_string(buff,0,M_WIDTH/2,89,"Corners",31,2);
		draw_string(buff,0,M_WIDTH/2,96,"Direct Free-kicks",31,2);
		draw_string(buff,0,M_WIDTH/2,103,"Penalties",31,2);
		draw_string(buff,0,M_WIDTH/2,110,"Offsides committed",31,2);
		draw_string(buff,0,M_WIDTH/2,117,"Yellow cards",31,2);
		draw_string(buff,0,M_WIDTH/2,124,"Red cards",31,2);

		char str1[20],str2[20];
		for (short i=0; i<11; i++)
			{
			if (i<4)
				{
				sprintf(str1,"%d%%",stat_sheet[i][0]);
				sprintf(str2,"%d%%",stat_sheet[i][1]);
				}
			else
				{
				sprintf(str1,"%d",stat_sheet[i][0]);
				sprintf(str2,"%d",stat_sheet[i][1]);
				}
			
			draw_string(buff,0,16,54+(i*7),str1,31,0);
			draw_string(buff,0,256-32,54+(i*7),str2,31,1);
			}

		}
	else
		{
		draw_string(buff,2,192,56,GetTEXT( KIOF_TEXT ),31,2);
		}
	}


void draw_m_butt(buff_info *buff,int x,int y,char *string,BYTE col,char *legend)
	{
	if (scrmode==0x13)
		{
		draw_sprite(buff,36,x,y,0);
		draw_string(buff,0,x+23,y+5,string,col,2);
		if (legend!=NULL) draw_string(buff,0,x+2,y-1,legend,157,2);
		}
	else
		{
		draw_sprite(buff,25,x,y,0);
		draw_string(buff,2,x+45,y+8,string,col,2);
		if (legend!=NULL) draw_string(buff,2,x+4,y-2,legend,157,2);
		}
	}

void draw_l_butt(buff_info *buff,int x,int y,char *string,BYTE col,char *legend)
	{
	if (scrmode==0x13)
		{
		draw_sprite(buff,35,x,y,0);
		draw_string(buff,0,x+41,y+5,string,col,2);
		if (legend!=NULL) draw_string(buff,0,x+2,y-1,legend,157,2);
		}
	else
		{
		draw_sprite(buff,24,x,y,0);
		draw_string(buff,2,x+82,y+8,string,col,2);
		if (legend!=NULL) draw_string(buff,2,x+4,y-2,legend,157,2);
		}
	}

void draw_s_butt(buff_info *buff,int x,int y,char *string,BYTE col,char *legend)
	{
	if (scrmode==0x13)
		{
		draw_sprite(buff,37,x,y,0);
		draw_string(buff,0,x+15,y+5,string,col,2);
		if (legend!=NULL) draw_string(buff,0,x,y-1,legend,157,2);
		}
	else
		{
		draw_sprite(buff,26,x,y,0);
		draw_string(buff,2,x+29,y+8,string,col,2);
		if (legend!=NULL) draw_string(buff,2,x,y-2,legend,157,2);
		}
	}

struct
	{
	int formation;
	int sub_off,sub_on;
	}option_info;
int sub_c;

extern short replay_seconds;
extern char allow_replay;

int opt_b;
void 
options_menu(buff_info *buff, int team, int user_no)
	{
	char tstr[50];
	if (scrmode==0x13)
		{
		if (opt_b!=0) draw_l_butt(buff,62,32,GetTEXT( RPLY_TEXT ),(replay_seconds==0||!allow_replay)?2:31,"F1");
		if (opt_b!=1) draw_l_butt(buff,62,48,GetTEXT( SBTN_TEXT ),(match_mode||!EUROmatch_info.substitutes||sub_c<2||user_no<=0)?2:31,"F2");
		if (opt_b!=2) draw_l_butt(buff,62,64,GetTEXT( FRMN_TEXT ),user_no<=0?2:31,"F3");
		if (opt_b!=3) draw_l_butt(buff,62,80,GetTEXT( CANL_TEXT ),31,"F4");
		draw_menu_box(buff);
		if (opt_b==0) draw_l_butt(buff,62,32,GetTEXT( RPLY_TEXT ),31,"F1");
		if (opt_b==1) draw_l_butt(buff,62,48,GetTEXT( SBTN_TEXT ),31,"F2");
		if (opt_b==2) draw_l_butt(buff,62,64,GetTEXT( FRMN_TEXT ),31,"F3");
		if (opt_b==3) draw_l_butt(buff,62,80,GetTEXT( CANL_TEXT ),31,"F4");
		if (user_no>0)
			{
	 		draw_sprite(buff,30+team,18,38,0);
			sprintf(tstr,"PLAYER %d",user_no);
			draw_string(buff,0,36,87,tstr,157,2);
			}
		else
	 		draw_sprite(buff,52,22,45,0);
		}
	else
		{
		if (opt_b!=0) draw_l_butt(buff,124,64,GetTEXT( RPLY_TEXT ),(replay_seconds==0||!allow_replay)?2:31,"F1");
		if (opt_b!=1) draw_l_butt(buff,124,96,GetTEXT( SBTN_TEXT ),(match_mode||!EUROmatch_info.substitutes||sub_c<2||user_no<=0)?2:31,"F2");
		if (opt_b!=2) draw_l_butt(buff,124,128,GetTEXT( FRMN_TEXT ),user_no<=0?2:31,"F3");
		if (opt_b!=3) draw_l_butt(buff,124,160,GetTEXT( CANL_TEXT ),31,"F4");
		draw_menu_box(buff);
		if (opt_b==0) draw_l_butt(buff,124,64,GetTEXT( RPLY_TEXT ),31,"F1");
		if (opt_b==1) draw_l_butt(buff,124,96,GetTEXT( SBTN_TEXT ),31,"F2");
		if (opt_b==2) draw_l_butt(buff,124,128,GetTEXT( FRMN_TEXT ),31,"F3");
		if (opt_b==3) draw_l_butt(buff,124,160,GetTEXT( CANL_TEXT ),31,"F4");
		if (user_no>0)
			{
			draw_sprite(buff,19+team,36,76,0);
			sprintf(tstr,"PLAYER %d",user_no);
			draw_string(buff,2,72,174,tstr,157,2);
			}
		else
	 		draw_sprite(buff,46,45,90,0);
		}
	}

char forms[10][6]=
	{
	"4=3=3",
	"5=3=2",
	"6=3=1",
	"4=2=4",
	"5=1=4",
	"4=0=6",
	"3=1=6",
	"4=1=5",
	"5=2=3",
	"4=4=2",
	};

int for_b;
void 
formation_menu(buff_info *buff, int team, int user_no)
	{
	char tstr[50];
	if (scrmode==0x13)
		{
		if (for_b!=0) draw_l_butt(buff,62,32,forms[option_info.formation],31,"F1");
		if (for_b!=1) draw_l_butt(buff,62,48,GetTEXT( SLCT_TEXT ),31,"F2");
		if (for_b!=2) draw_l_butt(buff,62,64,GetTEXT( CANL_TEXT ),31,"F3");
		draw_menu_box(buff);
		if (for_b==0) draw_l_butt(buff,62,32,forms[option_info.formation],31,"F1");
		if (for_b==1) draw_l_butt(buff,62,48,GetTEXT( SLCT_TEXT ),31,"F2");
		if (for_b==2) draw_l_butt(buff,62,64,GetTEXT( CANL_TEXT ),31,"F3");
		draw_sprite(buff,30+team,18,34,0);
		}
	else
		{
		if (for_b!=0) draw_l_butt(buff,124,64,forms[option_info.formation],31,"F1");
		if (for_b!=1) draw_l_butt(buff,124,96,GetTEXT( SLCT_TEXT ),31,"F2");
		if (for_b!=2) draw_l_butt(buff,124,128,GetTEXT( CANL_TEXT ),31,"F3");
		draw_menu_box(buff);
		if (for_b==0) draw_l_butt(buff,124,64,forms[option_info.formation],31,"F1");
		if (for_b==1) draw_l_butt(buff,124,96,GetTEXT( SLCT_TEXT ),31,"F2");
		if (for_b==2) draw_l_butt(buff,124,128,GetTEXT( CANL_TEXT ),31,"F3");
		draw_sprite(buff,19+team,36,68,0);
		}
	}

int sub_b;
void 
substitution_menu(buff_info *buff, int team, int user_no)
	{
	char tstr[50];
	if (scrmode==0x13)
		{
		if (sub_b!=0) draw_m_butt(buff,88,32,GetTEXT( SOFF_TEXT ),31,"F1");
		if (sub_b!=1) draw_l_butt(buff,70,48,GetTEXT( SUBT_TEXT ),31,"F2");
		if (sub_b!=2) draw_l_butt(buff,70,64,GetTEXT( CANL_TEXT ),31,"F3");
		if (sub_b!=3) draw_m_butt(buff,88,80,GetTEXT( SBON_TEXT ),31,"F4");
		draw_menu_box(buff);
		if (sub_b==0) draw_m_butt(buff,88,32,GetTEXT( SOFF_TEXT ),31,"F1");
		if (sub_b==1) draw_l_butt(buff,70,48,GetTEXT( SUBT_TEXT ),31,"F2");
		if (sub_b==2) draw_l_butt(buff,70,64,GetTEXT( CANL_TEXT ),31,"F3");
		if (sub_b==3) draw_m_butt(buff,88,80,GetTEXT( SBON_TEXT ),31,"F4");
		draw_sprite(buff,30+team,23,48,0);
		draw_sprite(buff,30+team,166,38,0);
		if (!team)
			{
			draw_string(buff,0,41,37,
//				&game_data[setup.team_a].players[option_info.sub_off].name[game_data[setup.team_a].players[option_info.sub_off].goal_index],
				&GetPLAYERSname( EUROmatch_info.TeamAsquad[option_info.sub_off], setup.team_a, INITIAL_SURNAME )[0],
				157,2);
			draw_sprite(buff,2+teams[option_info.sub_off+((match_half&1)?11:0)].shirt-1,29,58,0);
			draw_string(buff,0,183,85,
//				&game_data[setup.team_a].players[option_info.sub_on].name[game_data[setup.team_a].players[option_info.sub_on].goal_index],
				&GetPLAYERSname( EUROmatch_info.TeamAsquad[option_info.sub_on], setup.team_a, INITIAL_SURNAME )[0],
				157,2);
			draw_sprite(buff,2+option_info.sub_on,172,48,0);
			}
		else
			{
			draw_string(buff,0,41,37,
//				&game_data[setup.team_b].players[option_info.sub_off].name[game_data[setup.team_b].players[option_info.sub_off].goal_index],
				&GetPLAYERSname( EUROmatch_info.TeamBsquad[option_info.sub_off], setup.team_b, INITIAL_SURNAME )[0],
				157,2);
			draw_sprite(buff,2+teams[option_info.sub_off+((match_half&1)?0:11)].shirt-1,29,58,0);
			draw_string(buff,0,183,85,
//				&game_data[setup.team_b].players[option_info.sub_on].name[game_data[setup.team_b].players[option_info.sub_on].goal_index],
				&GetPLAYERSname( EUROmatch_info.TeamBsquad[option_info.sub_on], setup.team_b, INITIAL_SURNAME )[0],
				157,2);
			draw_sprite(buff,2+option_info.sub_on,172,48,0);
			}
		}
	else
		{
		if (sub_b!=0) draw_m_butt(buff,176,64,GetTEXT( SOFF_TEXT ),31,"F1");
		if (sub_b!=1) draw_l_butt(buff,140,96,GetTEXT( SUBT_TEXT ),31,"F2");
		if (sub_b!=2) draw_l_butt(buff,140,128,GetTEXT( CANL_TEXT ),31,"F3");
		if (sub_b!=3) draw_m_butt(buff,176,160,GetTEXT( SBON_TEXT ),31,"F4");
		draw_menu_box(buff);
		if (sub_b==0) draw_m_butt(buff,176,64,GetTEXT( SOFF_TEXT ),31,"F1");
		if (sub_b==1) draw_l_butt(buff,140,96,GetTEXT( SUBT_TEXT ),31,"F2");
		if (sub_b==2) draw_l_butt(buff,140,128,GetTEXT( CANL_TEXT ),31,"F3");
		if (sub_b==3) draw_m_butt(buff,176,160,GetTEXT( SBON_TEXT ),31,"F4");
		draw_sprite(buff,19+team,46,96,0);
		draw_sprite(buff,19+team,332,76,0);
		if (!team)
			{
			draw_string(buff,2,81,72,
//				&game_data[setup.team_a].players[option_info.sub_off].name[game_data[setup.team_a].players[option_info.sub_off].goal_index],
				&GetPLAYERSname( EUROmatch_info.TeamAsquad[option_info.sub_off], setup.team_a, INITIAL_SURNAME )[0],
				157,2);
			draw_sprite_s(buff,53+teams[option_info.sub_off+((match_half&1)?11:0)].shirt-1,68,123,0);
			draw_string(buff,2,366,168,
//				&game_data[setup.team_a].players[option_info.sub_on].name[game_data[setup.team_a].players[option_info.sub_on].goal_index],
				&GetPLAYERSname( EUROmatch_info.TeamAsquad[option_info.sub_on], setup.team_a, INITIAL_SURNAME )[0],
				157,2);
			draw_sprite_s(buff,53+option_info.sub_on,354,103,0);
			}
		else
			{
			draw_string(buff,2,81,72,
//				&game_data[setup.team_b].players[option_info.sub_off].name[game_data[setup.team_b].players[option_info.sub_off].goal_index],
				&GetPLAYERSname( EUROmatch_info.TeamBsquad[option_info.sub_off], setup.team_b, INITIAL_SURNAME )[0],
				157,2);
			draw_sprite_s(buff,68+teams[option_info.sub_off+((match_half&1)?0:11)].shirt-1,68,123,0);
			draw_string(buff,2,366,168,
//				&game_data[setup.team_b].players[option_info.sub_on].name[game_data[setup.team_b].players[option_info.sub_on].goal_index],
				&GetPLAYERSname( EUROmatch_info.TeamBsquad[option_info.sub_on], setup.team_b, INITIAL_SURNAME )[0],
				157,2);
			draw_sprite_s(buff,68+option_info.sub_on,354,103,0);
			}
		}
	}

int rep_b;
int play,speed;
float reppos;
void 
replay_menu(buff_info *buff, int user_no)
	{
	char tstr[50];
	if (scrmode==0x13)
		{
		if (rep_b!=0) 
			{
			draw_s_butt(buff,112,32,"",31,"F1");
			draw_sprite_hf(buff,39,121,35,0);
			draw_sprite_hf(buff,39,127,35,0);
			}
		if (rep_b!=1) 
			{
			draw_s_butt(buff,146,32,"",31,"F2");
			draw_sprite(buff,39,155,35,0);
			draw_sprite(buff,39,161,35,0);
			}
		if (rep_b!=2) draw_s_butt(buff,185,32,"",31,"F3");
		if (!play) draw_sprite(buff,39,197,35,0);
		if (rep_b!=3) draw_m_butt(buff,225,32,GetTEXT( DONE_TEXT ),31,"F4");
		draw_menu_box(buff);
		sprintf(tstr,"%.2f",reppos);
		draw_m_butt(buff,17,32,tstr,157,NULL);
		sprintf(tstr,"%d",speed);
		draw_s_butt(buff,69,32,tstr,31,NULL);
		if (rep_b==0) 
			{
			draw_s_butt(buff,112,32,"",31,"F1");
			draw_sprite_hf(buff,39,121,35,0);
			draw_sprite_hf(buff,39,127,35,0);
			}
		if (rep_b==1) 
			{
			draw_s_butt(buff,146,32,"",31,"F2");
			draw_sprite(buff,39,155,35,0);
			draw_sprite(buff,39,161,35,0);
			}
		if (rep_b==2) draw_s_butt(buff,185,32,"",31,"F3");
		if (play||rep_b==2) draw_sprite(buff,39,197,35,0);
		if (rep_b==3) draw_m_butt(buff,225,32,GetTEXT( DONE_TEXT ),31,"F4");
		}
	else
		{
		if (rep_b!=0) 
			{
			draw_s_butt(buff,224,64,"",31,"F1");
			draw_sprite_hf(buff,28,240,70,0);
			draw_sprite_hf(buff,28,252,70,0);
			}
		if (rep_b!=1) 
			{
			draw_s_butt(buff,292,64,"",31,"F2");
			draw_sprite(buff,28,310,70,0);
			draw_sprite(buff,28,322,70,0);
			}
		if (rep_b!=2) draw_s_butt(buff,370,64,"",31,"F3");
		if (!play) draw_sprite(buff,28,394,70,0);
		if (rep_b!=3) draw_m_butt(buff,447,64,GetTEXT( DONE_TEXT ),31,"F4");
		draw_menu_box(buff);
		sprintf(tstr,"%.2f",reppos);
		draw_m_butt(buff,34,64,tstr,157,NULL);
		sprintf(tstr,"%d",speed);
		draw_s_butt(buff,138,64,tstr,31,NULL);
		if (rep_b==0) 
			{
			draw_s_butt(buff,224,64,"",31,"F1");
			draw_sprite_hf(buff,28,240,70,0);
			draw_sprite_hf(buff,28,252,70,0);
			}
		if (rep_b==1) 
			{
			draw_s_butt(buff,292,64,"",31,"F2");
			draw_sprite(buff,28,310,70,0);
			draw_sprite(buff,28,322,70,0);
			}
		if (rep_b==2) draw_s_butt(buff,370,64,"",31,"F3");
		if (play||rep_b==2) draw_sprite(buff,28,394,70,0);
		if (rep_b==3) draw_m_butt(buff,447,64,GetTEXT( DONE_TEXT ),31,"F4");
		}
	}


void 
do_goal_menu(int team, int player, int time)
	{
	mdata1=team;
	mdata2=player;
	mdata3=time;
	slco=0;
	slide=oslide=44;
	mcount=240;
	if (menu) rdmenu=1;
	menu=1;
	}

void 
do_booked_menu(int team, int player)
	{
	mdata1=team;
	mdata2=player;
	slco=0;
	slide=oslide=44;
	mcount=240;
	if (menu) rdmenu=1;
	menu=2;
	}

void 
do_off_menu(int team, int player)
	{
	mdata1=team;
	mdata2=player;
	slco=0;
	slide=oslide=44;
	mcount=240;
	if (menu) rdmenu=1;
	menu=3;
	}

void 
do_direct_menu(int team)
	{
	mdata1=team;
	slco=0;
	slide=oslide=44;
	mcount=240;
	if (menu) rdmenu=1;
	menu=4;
	}

void 
do_indirect_menu(int team)
	{
	mdata1=team;
	slco=0;
	slide=oslide=44;
	mcount=240;
	if (menu) rdmenu=1;
	menu=5;
	}

void 
do_penalty_menu(int team)
	{
	mdata1=team;
	slco=0;
	slide=oslide=44;
	mcount=240;
	if (menu) rdmenu=1;
	menu=6;
	}

void 
do_corner_menu(int team)
	{
	mdata1=team;
	slco=0;
	slide=oslide=44;
	mcount=240;
	if (menu) rdmenu=1;
	menu=7;
	}

void 
do_throw_menu(int team)
	{
	mdata1=team;
	slco=0;
	slide=oslide=44;
	mcount=240;
	if (menu) rdmenu=1;
	menu=8;
	}

void 
do_goalkick_menu(int team)
	{
	mdata1=team;
	slco=0;
	slide=oslide=44;
	mcount=240;
	if (menu) rdmenu=1;
	menu=9;
	}

void 
do_kickoff_menu(int team)
	{
	mdata1=team;
	slco=0;
	slide=oslide=44;
	mcount=240;
	if (menu) rdmenu=1;
	menu=10;
	}

void 
do_offside_menu(int team)
	{
	mdata1=team;
	slco=0;
	slide=oslide=44;
	mcount=240;
	if (menu) rdmenu=1;
	menu=11;
	}

void 
do_injured_menu(int team, int player)
	{
	mdata1=team;
	mdata2=player;
	slco=0;
	slide=oslide=44;
	mcount=240;
	if (menu) rdmenu=1;
	menu=12;
	}

void 
do_fulltime_menu()
	{
	slco=0;
	slide=oslide=108;
	mcount=240000;
	if (menu) rdmenu=1;
	menu=13;
	mhgt=128;
	}

void 
do_extratime_menu()
	{
	slco=0;
	slide=oslide=108;
	mcount=240000;
	if (menu) rdmenu=1;
	menu=14;
	mhgt=128;
	}

void 
do_halftime_menu()
	{
	slco=0;
	slide=oslide=108;
	mcount=240000;
	if (menu) rdmenu=1;
	menu=15;
	mhgt=128;
	}

void 
do_penalty_shootout_menu()
	{
	slco=0;
	slide=oslide=108;
	mcount=340;
	if (menu) rdmenu=1;
	menu=16;
	mhgt=128;
	}

void 
do_final_score_menu()
	{
	slco=0;
	slide=oslide=108;
	mcount=240;
	if (menu) rdmenu=1;
	menu=17;
	mhgt=128;
	}

void 
do_owngoal_menu(int team, int player, int time)
	{
	mdata1=team;
	mdata2=player;
	mdata3=time;
	slco=0;
	slide=oslide=44;
	mcount=240;
	if (menu) rdmenu=1;
	menu=18;
	}

void 
do_options_menu(int team,int user_no)
	{
	mdata1=team;
	mdata2=user_no+1;
	slco=0;
	slide=oslide=108;
	mcount=1000000;
	if (menu) rdmenu=1;
	menu=19;
	}

void 
do_formation_menu(int team,int user_no)
	{
	mdata1=team;
	mdata2=user_no+1;
	slco=0;
	slide=oslide=92;
	mcount=1000000;
	if (menu) rdmenu=1;
	menu=20;
	}

void 
do_substitution_menu(int team,int user_no)
	{
	mdata1=team;
	mdata2=user_no+1;
	slco=0;
	slide=oslide=108;
	mcount=1000000;
	if (menu) rdmenu=1;
	menu=21;
	}

void 
do_replay_menu(int user_no)
	{
	mdata1=user_no+1;
	slco=0;
	slide=oslide=34;
	mcount=1000000;
	if (menu) rdmenu=1;
	menu=22;
	}

void 
do_ref_menu()
	{
	slco=0;
	slide=oslide=44;
	mcount=240;
	if (menu) rdmenu=1;
	menu=23;
	}

void 
do_stats_menu()
	{
	slco=0;
	slide=oslide=140;
	mcount=200*6;
	if (menu) rdmenu=1;
	menu=24;
	}


struct user_vectors{
	float x;
	float y;
	char m;
	char f;
	};

extern user_vectors users_dir[20];
extern void convert_inputs();
#ifndef LINK
extern void get_user_inputs();
extern void process_user_inputs();
extern volatile int readptr;
extern volatile int writeptr;
#else
extern "C" void get_user_inputs();
extern "C" void process_user_inputs();
extern "C" volatile int readptr;
extern "C" volatile int writeptr;
#endif

#define RIGHT_DIR 1
#define LEFT_DIR 2
#define DOWN_DIR 4
#define UP_DIR 8
#define FIRE1_DIR 16
#define FIRE2_DIR 32
#define F1_DIR 64
#define F2_DIR 128
#define F3_DIR 256
#define F4_DIR 512
#define BUTT_WAIT 65
static int count_ur;
static int count_ul;
static int count_ud;
static int count_uu;
static int count_uf1;
static int count_uf2;
static int uf1_p;
static int uf2_p;
static int uf3_p;
static int uf4_p;
int
get_dir(int user_no)
	{
	int out;
#ifdef LINK
	if (user_no>=0)
		{
		icth=32767;
		isth=0;
		get_user_inputs();
		process_user_inputs();
		writeptr++;
		writeptr&=511;
		convert_inputs();
		readptr++;
		readptr&=511;
		}
	else
#endif
		{
		users_dir[0].x=0;
		users_dir[0].y=0;
		users_dir[0].f=0;
#ifdef LINK
		if (keys[0xcd]) users_dir[0].x=1;
		if (keys[0xcb]) users_dir[0].x=-1;
		if (keys[0xd0]) users_dir[0].y=1;
		if (keys[0xc8]) users_dir[0].y=-1;
#else
		if (keys[0x4d]) users_dir[0].x=1;
		if (keys[0x4b]) users_dir[0].x=-1;
		if (keys[0x50]) users_dir[0].y=1;
		if (keys[0x48]) users_dir[0].y=-1;
#endif
		if (keys[0x52]) users_dir[0].f=1;
		if (keys[0x53]) users_dir[0].f=1;
		user_no=0;
		}

	out=0;
	if (users_dir[user_no].x>0.1) 
		{if (count>count_ur+50) out|=RIGHT_DIR,count_ur=count+100;}
	else
		if (users_dir[user_no].x<-0.1)
			{if (count>count_ul+50) out|=LEFT_DIR,count_ul=count+100;}
		else
			count_ul=count_ur=0;
	if (users_dir[user_no].y>0.1) 
		{if (count>count_ud+50) out|=DOWN_DIR,count_ud=count+100;}
	else
		if (users_dir[user_no].y<-0.1)
			{if (count>count_uu+50) out|=UP_DIR,count_uu=count+100;}
		else
			count_uu=count_ud=0;
	if (users_dir[user_no].f&1)
			{if (count>count_uf1+50) out|=FIRE1_DIR,count_uf1=count+100;}
		else
			count_uf1=0;
	if (users_dir[user_no].f&2)
			{if (count>count_uf2+50) out|=FIRE2_DIR,count_uf2=count+100;}
		else
			count_uf2=0;
	if (!keys[0x3b]) uf1_p=0; else if (!uf1_p) out|=F1_DIR|FIRE1_DIR,uf1_p=1;
	if (!keys[0x3c]) uf2_p=0; else if (!uf2_p) out|=F2_DIR|FIRE1_DIR,uf2_p=1;
	if (!keys[0x3d]) uf3_p=0; else if (!uf3_p) out|=F3_DIR|FIRE1_DIR,uf3_p=1;
	if (!keys[0x3e]) uf4_p=0; else if (!uf4_p) out|=F4_DIR|FIRE1_DIR,uf4_p=1;

	return(out);
	}


extern void do_replay_render3d(float pos);
extern void setup_replay();
extern void reset_replay();
extern void frame_count();

void
replay(buff_info *buffer,datapt viewx,datapt viewy,datapt viewz,datapt targx,datapt targy,
        datapt targz,datapt vdist,plyrdat *plyrtb,datapt *xyz_ptr,word *ref_ptr,int user_no)
	{
	int dir,repcount;
	float repstep;
	rep_b=3;
	uf1_p=uf2_p=uf3_p=uf4_p=1;
	play=1;
	speed=5;
	reppos=0;
	setup_replay();
	do_replay_menu(user_no);
	do
		{
		render3d(buffer,viewx,viewy,viewz,targx,targy,targz,vdist,plyrtb,xyz_ptr,ref_ptr);
		main_buff.dump(0,0);
		frame_count();
		} while (slide>0);
	do
		{
		dir=get_dir(user_no);
		if (dir&F1_DIR) rep_b=0;
		if (dir&F2_DIR) rep_b=1;
		if (dir&F3_DIR) rep_b=2;
		if (dir&F4_DIR) rep_b=3;
		if (dir&LEFT_DIR) (rep_b+=3)%=4;
		if (dir&RIGHT_DIR) ++rep_b%=4;
		repcount=count;
		do_replay_render3d(reppos);
		frame_count();
#ifndef LINK
		render3d(buffer,viewx,viewy,viewz,targx,targy,targz,vdist,plyrtb,xyz_ptr,ref_ptr);
		main_buff.dump(0,0);
#endif
		repstep=(count-repcount)/200.;
		if (dir&(FIRE1_DIR|FIRE2_DIR))
			{
			switch(rep_b)
				{
				case 0:
					if (speed>0) --speed;
					break;
				case 1:
					if (speed<5) ++speed;
					break;
				case 2:
					if (speed)
						play=!play;
					else
						reppos+=repstep*3/5.;
					break;
				case 3:
					goto re_exit;
				}
			}
			if (play) reppos+=repstep*speed/5.;
			if (reppos>=replay_seconds) reppos=0,play=0;
		} while (!keys[1]);
	keys[1]=0;
	re_exit:;
	if (user_no>=0) 
		while (users_dir[user_no].f&3)
			get_dir(user_no);
	keys[0x3b]=keys[0x3c]=keys[0x3d]=keys[0x3e]=0;
	reset_replay();
	mcount=1;
	}

extern void	SubstituePlayers(int team_no, int player1, int player2);
extern void	sub_player(short team_no, short player1, short player2);

char sub_pending;
int sub_p_a,sub_p_b;

void
substitution(buff_info *buffer,datapt viewx,datapt viewy,datapt viewz,datapt targx,datapt targy,
        datapt targz,datapt vdist,plyrdat *plyrtb,datapt *xyz_ptr,word *ref_ptr,int team)
	{
	int dir;
	int user_no;
	user_no=(team==0)?sub_p_a:sub_p_b;
	option_info.sub_off=0;
	option_info.sub_on=11;
	while (game_data[(team==0)?TEMPa:TEMPb].players[option_info.sub_off].flags&2)
		option_info.sub_off++;
	while (!game_data[(team==0)?TEMPa:TEMPb].players[option_info.sub_on].flags&1)
		option_info.sub_on++;
	sub_b=0;
	uf1_p=uf2_p=uf3_p=uf4_p=1;
	do_substitution_menu(team, user_no);
	do
		{
		render3d(buffer,viewx,viewy,viewz,targx,targy,targz,vdist,plyrtb,xyz_ptr,ref_ptr);
		main_buff.dump(0,0);
		frame_count();
		} while (slide>0);
	do
		{
		dir=get_dir(user_no);
		if (dir&F1_DIR) sub_b=0;
		if (dir&F2_DIR) sub_b=1;
		if (dir&F3_DIR) sub_b=2;
		if (dir&F4_DIR) sub_b=3;
		if (dir&UP_DIR) (sub_b+=3)%=4;
		if (dir&DOWN_DIR) ++sub_b%=4;
		render3d(buffer,viewx,viewy,viewz,targx,targy,targz,vdist,plyrtb,xyz_ptr,ref_ptr);
		main_buff.dump(0,0);
		frame_count();
		if (dir&(FIRE1_DIR|FIRE2_DIR))
			{
			switch(sub_b)
				{
				case 0:
					do
						{
						if (dir&FIRE1_DIR) (++option_info.sub_off%=11);
						else (option_info.sub_off+=10)%=11;
						} while (game_data[(team==0)?TEMPa:TEMPb].players[option_info.sub_off].flags&2);
					break;
				case 1:
					sub_player(team,option_info.sub_off,option_info.sub_on);
					SubstituePlayers((team==0)?setup.team_a:setup.team_b,option_info.sub_off,option_info.sub_on);
					goto su_exit;
				case 2:
					goto su_exit;
				case 3:
					do
						{
						if (dir&FIRE1_DIR) { if (++option_info.sub_on>14) option_info.sub_on=11; }
						else { if (--option_info.sub_on<11) option_info.sub_on=14; }
						} while (!game_data[(team==0)?TEMPa:TEMPb].players[option_info.sub_on].flags&1);
					break;
				}
			}
		} while (!keys[1]);
	keys[1]=0;
	su_exit:;
	if (user_no>=0) 
		while (users_dir[user_no].f&3)
			get_dir(user_no);
	keys[0x3b]=keys[0x3c]=keys[0x3d]=keys[0x3e]=0;
	sub_pending&=((team==0)?2:1);
	mcount=1;
	}

extern char tactics_a,tactics_b;
extern void load_new_tactics();

void
formation(buff_info *buffer,datapt viewx,datapt viewy,datapt viewz,datapt targx,datapt targy,
        datapt targz,datapt vdist,plyrdat *plyrtb,datapt *xyz_ptr,word *ref_ptr,int user_no,int team)
	{
	int dir;
	int oform=option_info.formation;
	for_b=0;
	uf1_p=uf2_p=uf3_p=uf4_p=1;
	do_formation_menu(team, user_no);
	do
		{
		render3d(buffer,viewx,viewy,viewz,targx,targy,targz,vdist,plyrtb,xyz_ptr,ref_ptr);
		main_buff.dump(0,0);
		frame_count();
		} while (slide>0);
	do
		{
		dir=get_dir(user_no);
		if (dir&F1_DIR) for_b=0;
		if (dir&F2_DIR) for_b=1;
		if (dir&F3_DIR) for_b=2;
		if (dir&UP_DIR) (for_b+=2)%=3;
		if (dir&DOWN_DIR) ++for_b%=3;
		render3d(buffer,viewx,viewy,viewz,targx,targy,targz,vdist,plyrtb,xyz_ptr,ref_ptr);
		main_buff.dump(0,0);
		frame_count();
		if (dir&(FIRE1_DIR|FIRE2_DIR))
			{
			switch(for_b)
				{
				case 0:
					if (dir&FIRE1_DIR) (++option_info.formation%=10);
					else (option_info.formation+=9)%=10;
					break;
				case 1:
					if (team==0) tactics_a=option_info.formation;
					else tactics_b=option_info.formation;
					load_new_tactics();
					goto fo_exit;
				case 2:
					option_info.formation=oform;
					goto fo_exit;
				}
			}
		} while (!keys[1]);
	keys[1]=0;
	if (user_no>=0) 
		while (users_dir[user_no].f&3)
			get_dir(user_no);
	keys[0x3b]=keys[0x3c]=keys[0x3d]=keys[0x3e]=0;
	fo_exit:;
	mcount=1;
	}

void
options(buff_info *buffer,datapt viewx,datapt viewy,datapt viewz,datapt targx,datapt targy,
        datapt targz,datapt vdist,plyrdat *plyrtb,datapt *xyz_ptr,word *ref_ptr,int user_no,int team)
	{
	int dir;
	opt_b=0;
	uf1_p=uf2_p=uf3_p=uf4_p=1;
	if (replay_seconds==0||!allow_replay) opt_b=3;
	if (user_no<0)
		{
		if (replay_seconds==0||!allow_replay) return;
		sub_c=0;
		}
	else
		{
		sub_c=(game_data[(team==0)?TEMPa:TEMPb].players[11].flags&1);
		sub_c+=(game_data[(team==0)?TEMPa:TEMPb].players[12].flags&1);
		sub_c+=(game_data[(team==0)?TEMPa:TEMPb].players[13].flags&1);
		sub_c+=(game_data[(team==0)?TEMPa:TEMPb].players[14].flags&1);
		}
	option_info.formation=(team==0)?tactics_a:tactics_b;
	op_loop:
	do_options_menu(team, user_no);
	do
		{
		render3d(buffer,viewx,viewy,viewz,targx,targy,targz,vdist,plyrtb,xyz_ptr,ref_ptr);
		main_buff.dump(0,0);
		frame_count();
		} while (slide>0);
	do
		{
		dir=get_dir(user_no);
		if (dir&F1_DIR) if (replay_seconds==0||!allow_replay) dir^=FIRE1_DIR; else opt_b=0;
		if (dir&F2_DIR) if (match_mode||!EUROmatch_info.substitutes||sub_c<2) dir^=FIRE1_DIR; else opt_b=1;
		if (dir&F3_DIR) if (user_no<0) dir^=FIRE1_DIR; else opt_b=2;
		if (dir&F4_DIR) opt_b=3;
		re_opt:;
		if (dir&UP_DIR) 
			{
			if (user_no<0 && opt_b==3) { opt_b=2;goto re_opt; }
			if ((match_mode||!EUROmatch_info.substitutes||sub_c<2) && opt_b==2) { opt_b=1;goto re_opt; }
			if ((replay_seconds==0||!allow_replay) && opt_b==1) { opt_b=0;goto re_opt; }
			(opt_b+=3)%=4;
			}
		if (dir&DOWN_DIR)
			{
			if (user_no<0 && opt_b==1) { opt_b=2;goto re_opt; }
			if ((match_mode||!EUROmatch_info.substitutes||sub_c<2) && opt_b==0) { opt_b=1;goto re_opt; }
			if ((replay_seconds==0||!allow_replay) && opt_b==3) { opt_b=0;goto re_opt; }
			++opt_b%=4;
			}
		render3d(buffer,viewx,viewy,viewz,targx,targy,targz,vdist,plyrtb,xyz_ptr,ref_ptr);
		main_buff.dump(0,0);
		frame_count();
		if (dir&(FIRE1_DIR|FIRE2_DIR))
			{
			switch(opt_b)
				{
				case 0:
					replay(buffer,viewx,viewy,viewz,targx,targy,targz,vdist,plyrtb,xyz_ptr,ref_ptr,user_no);
					goto op_exit;
				case 1:
					if (team==0)
						{
						sub_pending^=1;
						sub_p_a=user_no;
						}
					else
						{
						sub_pending^=2;
						sub_p_b=user_no;
						}
//					substitution(buffer,viewx,viewy,viewz,targx,targy,targz,vdist,plyrtb,xyz_ptr,ref_ptr,user_no,team);
  					goto op_exit;
				case 2:
					formation(buffer,viewx,viewy,viewz,targx,targy,targz,vdist,plyrtb,xyz_ptr,ref_ptr,user_no,team);
					if (for_b==2)
						goto op_loop;
					else
						goto op_exit;
				case 3:
					goto op_exit;
				}
			}
		} while (!keys[1]);
	keys[1]=0;
	op_exit:;
	if (user_no>=0) 
		while (users_dir[user_no].f&3)
			get_dir(user_no);
	keys[0x3b]=keys[0x3c]=keys[0x3d]=keys[0x3e]=0;
	mcount=1;
	}

void
adjust_menu()
	{
	menu_buff_l[menu-1].buff_hgt=menu_buff_l[menu-1].clip_hgt=mhgt;
	menu_buff_h[menu-1].buff_hgt=menu_buff_h[menu-1].clip_hgt=mhgt<<1;
	menu_buff_l[menu-1].buff_start=MCGA_buff[0].buff_start+(MCGA_buff[0].clip_hgt-menu_buff_l[menu-1].buff_hgt)*MCGA_buff[0].buff_wid+((MCGA_buff[0].clip_wid-menu_buff_l[menu-1].clip_wid)>>1);
	menu_buff_h[menu-1].buff_start=VESA_buff[scrmode-0x100][0].buff_start+(VESA_buff[scrmode-0x100][0].clip_hgt-menu_buff_h[menu-1].buff_hgt)*VESA_buff[scrmode-0x100][0].buff_wid+((VESA_buff[scrmode-0x100][0].clip_wid-menu_buff_h[menu-1].clip_wid)>>1);
	if (scrmode3DB>=0) 
		{
		if (scrmode3DB>1)
			menu_buff_l[menu-1].buff_start=buff_3DB[scrmode3DB].buff_start+(buff_3DB[scrmode3DB].clip_hgt-menu_buff_l[menu-1].buff_hgt)*buff_3DB[scrmode3DB].buff_wid+((buff_3DB[scrmode3DB].clip_wid-menu_buff_l[menu-1].clip_wid)>>1);
		else
			menu_buff_h[menu-1].buff_start=buff_3DB[scrmode3DB].buff_start+(buff_3DB[scrmode3DB].clip_hgt-menu_buff_h[menu-1].buff_hgt)*buff_3DB[scrmode3DB].buff_wid+((buff_3DB[scrmode3DB].clip_wid-menu_buff_h[menu-1].clip_wid)>>1);
		}
	if (slide>mhgt-20) slide=oslide=mhgt-20;
	}


// Remapping gfx for transparency
remapgfx(int d)
	{
	BYTE *tptr;
	int i;
	tptr=maps[0];
	for (i=0;i<X_BM*65536;i++) *(tptr++)+=d;
	if (setup.M8)
		{
		tptr=maps[S_BM+2];
#ifdef NEW
		for (i=0;i<6*65536;i++) *(tptr++)+=d;
#else
		for (i=0;i<5*65536;i++) *(tptr++)+=d;
#endif
		}
	}

remapxgfx(int d)
	{
	BYTE *tptr;
	int i,j;
	tptr=maps[X_BM];
	for (i=0;i<116*256;i++) *(tptr++)+=d;
	for (i=116;i<143;i++)
		{
		tptr+=256-188;
		for (j=0;j<188;j++) 
			*(tptr++)+=d;
		}
	for (i=143;i<171;i++) 
		{
		tptr+=256-79;
		for (j=0;j<79;j++) 
			*(tptr++)+=d;
		}
	tptr=maps[X_BM]+180*256;
	for (i=0;i<(76+256)*256;i++) 
		{
		if (*tptr>1) *(tptr)+=d;
		tptr++;
		}
	if (setup.stadium>=45&&setup.stadium<90)
		{
		tptr=maps[S_BM]+100*256+197;
		for (j=0;j<90;j++)
			{
			for (i=0;i<59;i++)
				*(tptr++)+=d;
			tptr+=256-59;
			}
		tptr=maps[S_BM]+190*256+220;
		for (j=0;j<35;j++)
			{
			for (i=0;i<36;i++)
				*(tptr++)+=d;
			tptr+=256-36;
			}
		}
	tptr=maps[X_BM+1]+80*256;
	for (i=0;i<256;i++) 
		*tptr++=i;
	}


extern int coo;
double null;
obj hd;
ptlist hdp={ 4, -50,0,-50, 50,0,-50, 50,0,50, -50,0,50 };
facelist hdf={ 1, 4,-X_TM-2000, 0,3,2,1};


/************************/
/* MAIN DISPLAY ROUTINE */

void render3d(buff_info *buffer,datapt viewx,datapt viewy,datapt viewz,datapt targx,datapt targy,
              datapt targz,datapt vdist,plyrdat *plyrtb,datapt *xyz_ptr,word *ref_ptr)
	{
	short i,j;
	double hr,r;
	mat tmp;
	obj *thisobj;
	objs *oldobj;
	plyrdat *plyrpt;
	plyrtwdat *plyrpto;
	mcap *mc1,*mc2;
	datapt *tw,*tw1,*tw2;
	floatpt twnstp,pt1,pt2;
	short plyrhi;
	static char vidi_l;
	static short balld;
	short an,ano,xf,xfo;
	static short kco=0;
	static short wire=0;
	static float hcoo=0;
	static float fcoo=0;
	float fs,fx,fy;
	BYTE v,ra,rb,*vrnd;

	rotpt rxa[4],rya[4],rza[4];
	rotpt rxb[4],ryb[4],rzb[4];
	float dx1,dy1,dx2,dy2,dz1,dz2;
	float vn,vm,vs1,vs2,vs3,vs4;

	if (vidi_anim&&buffer==&vidi_buff) return;

	if (!kco&buffer!=&vidi_buff)
		{

		if (keys[0x44]&&setup.M8)
			{
			short oscrmode;
			oscrmode=scrmode;
			switchmode();
			if (scrmode3DB<0 && scrmode!=oscrmode)
				{
				++setup.start_res&=1;
				switch(scrmode)
					{
					case 0x13:
						vclear(scrb+320,320,200,320,5);
						mcgacpy(scrb+320,0,0,320,200,320);
						break;
					case 0x100:
						vclear(scrb+640,640,400,640,5);
						svgacpy(scrb+640,0,0,640,400,640);
						break;
					case 0x101:
						vclear(scrb+640,640,480,640,5);
						svgacpy(scrb+640,0,0,640,480,640);
						break;
					}
				}
				else
#ifdef BLASTDEMO
					scrmode=(setup.start_res=(scrmode3DB>1)?1:0)?0x100:0x13;
#else
					scrmode=(setup.start_res=(scrmode3DB>0)?1:0)?0x100:0x13;
#endif
			kco=8;
			}

		if (keys[0xc]&&setup.screen_size<SCRSIZES-1&&scrmode3DB<0)
			{
			clearbuffer(buffer,5);
//			buffer->dump(0,0);
			rdmenu=1;
			setup.screen_size++;
			if (scrmode==0x13)
				*buffer=main_buff=MCGA_buff[setup.screen_size];
			else
				{
				i=0;
				while (scrmode!=modelist[i] && ++i!=VESAMODES);
				if (i!=VESAMODES)
					*buffer=main_buff=VESA_buff[i][setup.screen_size];
				}
			kco=8;
			}

		if (keys[0xd]&&setup.screen_size>0)
			{
			clearbuffer(buffer,5);
//			buffer->dump(0,0);
			rdmenu=1;
			setup.screen_size--;
			if (scrmode==0x13)
				*buffer=main_buff=MCGA_buff[setup.screen_size];
			else
				{
				i=0;
				while (scrmode!=modelist[i] && ++i!=VESAMODES);
				if (i!=VESAMODES)
					*buffer=main_buff=VESA_buff[i][setup.screen_size];
				}
			kco=8;
			}

#ifdef BLASTDEMO
		if (keys[0x0e])
			{
			if (scrmode3DB<0)
				{
				if ((scrmode3DB=Init3DB(setup.start_res==0?modelist3DB:modelist3DBh))>=0)
					{
#ifdef BLASTDEMO
					scrmode=(setup.start_res=(scrmode3DB>1)?1:0)?0x100:0x13;
#else
					scrmode=(setup.start_res=(scrmode3DB>0)?1:0)?0x100:0x13;
#endif
					remapgfx(-1);
					remapxgfx(-1);
					main_buff=buff_3DB[scrmode3DB];
					pal[3]=pal[4]=pal[5]=63;
					pal[191*3]=pal[191*3+1]=pal[191*3+2]=0;
					SetPalette3DB(pal);
					}
				}
			else
				{
				Close3DB();
				scrmode3DB=-1;
				remapgfx(1);
				remapxgfx(1);
				if (setup.start_res==0)
					{
					scrmode=0x13;
					VGAmode(scrmode);
					main_buff=MCGA_buff[setup.screen_size];
					}
				else
					{
					testVESA=0;
					scrmode=VESAmode(&modelist[0]);
					switch(scrmode)
						{
						case 0x100:main_buff=VESA_buff[0][setup.screen_size];break;
						case 0x101:main_buff=VESA_buff[1][setup.screen_size];break;
						default:VGAmode(0x13);main_buff=MCGA_buff[setup.screen_size];scrmode=0x13;
						}
					}
		
				setup.start_res=(scrmode==0x13)?0:1;
		
				// Set palette
				setpal();
		
				// Clear screen
				switch(scrmode)
					{
					case 0x13:
						vclear(scrb+320,320,200,320,5);
						mcgacpy(scrb+320,0,0,320,200,320);
						break;
					case 0x100:
						vclear(scrb+640,640,400,640,5);
						svgacpy(scrb+640,0,0,640,400,640);
						break;
					case 0x101:
						vclear(scrb+640,640,480,640,5);
						svgacpy(scrb+640,0,0,640,480,640);
						break;
					}
				}
			kco=8;
			}
#endif

		if (scrmode3DB<0)
			{
			if (keys[0x3f]) ++setup.detail.pitch%=3,kco=8;
			if (setup.detail.pitch==0&&setup.start_res==1) setup.detail.pitch=1;
			if (keys[0x40]) ++setup.detail.lines&=1,kco=8;
			if (keys[0x41]) ++setup.detail.sky&=1,kco=8;
			if (keys[0x42]) ++setup.detail.players&=1,kco=8;
//			if (keys[0x3f]) ++setup.detail.shadows&=1,kco=8;

//			if (keys[0x10])
//				wire=!wire,kco=8;

			if (EUROmatch_info.tga_enable&&keys[0x43]&&setup.M8)
				{
				for (i=0;i<400;i++)
					memcpy(dumplbm+0x312+(399-i)*640,render_buff.buff_start+640*i,640);
				writebin(dumpstr,dumplbm,640*400+0x312);
				dumpstr[4]++;
				kco=8;
				}
			}
		}
	else
		if (kco&&buffer!=&vidi_buff) kco--;

	// Set extended buffer info
	render_buff.buff_start=buffer->buff_start;
	render_buff.buff_wid=buffer->buff_wid;
	render_buff.buff_hgt=buffer->buff_hgt;
	render_buff.clip_wid=buffer->clip_wid;
	render_buff.clip_hgt=buffer->clip_hgt;
	render_buff.scale_x=buffer->scale_x;
	render_buff.scale_y=buffer->scale_y;
	render_buff.dump=buffer->dump;
	render_buff.clip_endl=buffer->buff_start+buffer->clip_hgt*buffer->buff_wid;
	render_buff.clip_end=render_buff.clip_endl-buffer->buff_wid;
	render_buff.clip_widl=buffer->clip_wid-1;
	render_buff.clip_hgtl=buffer->clip_hgt-1;
	render_buff.clip_xmid=buffer->clip_wid>>1;
	render_buff.clip_ymid=buffer->clip_hgt>>1;

	// Set perspective based info
	oq=vdist;
	q=vdist*((buffer->scale_x+buffer->scale_y)/2);
	qr=(floatpt)1/q; 
	qa=(floatpt)q*2/100;
	scrdr=(float)1/SCREENDIST;
	persc=q*scrdr;

	// Prepare viewing vector vars
	viewz=-viewz,targz=-targz;
	targx-=viewx;
	targy-=viewy;
	targz-=viewz;

	hr=targx*targx+targz*targz;
	if (hr<1) hr=1,targz=1;
	r=sqrt(hr+targy*targy);
	hr=sqrt(hr);
	cth=targz/hr;sth=targx/hr;
	cph=hr/r;sph=targy/r;
	if (buffer!=&vidi_buff)
		{
		icth=32767*cth;
		isth=32767*sth;
		}

	// Make global rotation matrix
	matcop(rot.arr,unit);
	matcop(tran.arr,unit);
	matcop(tmp,unit);
	rot.arr[0][3]=-viewx;
	rot.arr[1][3]=-viewy;
  	rot.arr[2][3]=-viewz;
	tmp[0][0]=cth;
	tmp[0][2]=-sth;				             
	tmp[1][0]=-sth*sph;
	tmp[1][1]=cph;
	tmp[1][2]=-cth*sph;
	tmp[2][0]=sth*cph;			 
	tmp[2][1]=sph;
	tmp[2][2]=cth*cph;
	matmul(rot.arr,tmp);

	clip_tex=NOTEXTURES+1;

	ppt=plyrtb;

#ifdef COUNT
	numpols=0;	 
#endif


//// Now render all objects from furthest to nearest

	clearlists


//// GRASS

	if (scrmode3DB<0)
		{
		ground(hr,targy,viewx,viewy,-viewz);
		if (!setup.detail.pitch)
			addobjfc(&pitch);
		}
	else
		{
		ground(hr,targy,viewx,viewy,-viewz);
//		addobjfc(&pitch);
//		dispols3DB();
		}

//goto hd1;

//// FAR STANDS


	vn=st_w*rot.e.r22+rot.e.r23;
	vs1=vn*rot.e.r00-(st_w*rot.e.r02+rot.e.r03)*rot.e.r20;
	vn=(-800-st_w)*rot.e.r22+rot.e.r23;
	vs2=vn*rot.e.r00-((-800-st_w)*rot.e.r02+rot.e.r03)*rot.e.r20;

	vn=-st_l*rot.e.r20+rot.e.r23;
	vs3=vn*rot.e.r02-(-st_l*rot.e.r00+rot.e.r03)*rot.e.r22;
	vn=(1280+st_l)*rot.e.r20+rot.e.r23;
	vs4=vn*rot.e.r02-((1280+st_l)*rot.e.r00+rot.e.r03)*rot.e.r22;

	if (setup.stadium<90)
		{
		if (vs3>=0)
			addobjnc(&stad3),numpols+=1000;
		if (vs4<0)
			addobjnc(&stad1),numpols+=1000;
		if (vs1>=0)
			addobjnc(&stad2),numpols+=1000;
		if (vs2<0)
			addobjnc(&stad4),numpols+=1000;
		}
	else
		{
		if (vs1>=0)
			addobjnc(&stad2);
		if (vs2<0)
			addobjnc(&stad4);
		if (vs3>=0)
			addobjnc(&stad3);
		if (vs4<0)
			addobjnc(&stad1);
		}

	if (scrmode3DB<0)
		dispolsn();
	else
		dispolst3DB();


//// PITCH MARKINGS

	objdepd(&l1,l1_d);
	addobjfc(&l1);
	objdepd(&l2,l2_d);
	addobjfc(&l2);
	objdepd(&l3,l3_d);
	addobjfc(&l3);
	objdepd(&l4,l4_d);
	addobjfc(&l4);
	objdepd(&l5,l5_d);
	addobjfc(&l5);
	objdepd(&l6,l6_d);
	addobjfc(&l6);

	if (setup.detail.lines)
		{
		objdepd(&circle,circle_d);
		addobjfc(&circle);
		objdepd(&semi1,s_circle_d1);
		addobjfc(&semi1);
		objdepd(&semi2,s_circle_d2);
		addobjfc(&semi2);
		}
	addobjfc(&spot1);
	addobjfc(&spot2);
	addobjfc(&spot3);


//// SHADOWS/HIGHLIGHTS

	// Player shadows
	plyrpt=(plyrdat *)plyrtb;
	for (i=0;i<NPLAYERS;i++)
		{
		if (plyrpt->type&&!plyrpt->htype&&setup.detail.players)
			{
			plhilight[0][0].x=plyrpt->x;
			plhilight[0][0].z=-plyrpt->z;
			addobjfc(&plhilight[0][0]);
			}
		plyrpt++;
		}

	// Ball shadow
	if (!balld) 
		{
		ballshad.x=plyrpt->x;
		ballshad.z=-plyrpt->z;
		}
	else
		{
		ballshad.x=mcap_ballx;
		ballshad.z=mcap_bally;
		}
	addobjfc(&ballshad);
		

	// Draw lines & shadows in order given (no sort).
	if (scrmode3DB<0)
		dispolsnx();
	else
		dispols3DB();


	// Player hilights 
	hcoo+=log_factor;
	while (hcoo>=4) hcoo-=4;
	plyrpt=(plyrdat *)plyrtb;
	for (i=0;i<NPLAYERS;i++)
		{
		if (plyrpt->type&&plyrpt->htype)
			{
			if ((plyrpt->htype!=4 && plyrpt->htype!=6) || hcoo>=2)
				{
				plhilight[plyrpt->htype][plyrpt->hcol].x=plyrpt->x;
				plhilight[plyrpt->htype][plyrpt->hcol].z=-plyrpt->z;
				if (plyrpt->htype==3 || plyrpt->htype==4)
					{
					plhilight[plyrpt->htype][plyrpt->hcol].crot=plyrpt->crot;
  					plhilight[plyrpt->htype][plyrpt->hcol].srot=-plyrpt->srot;
	  				addobjyc(&plhilight[plyrpt->htype][plyrpt->hcol]);
					}
				else
  					addobjfc(&plhilight[plyrpt->htype][plyrpt->hcol]);
				}
			}
		plyrpt++;
		}

objs *objtemp=curobj;


//// PLAYERS

coo++;

	balld=0;
	thisobj=player;
	plyrpt=plyrtb;
	plyrpto=plyrtwtb;
	for (i=0;i<NPLAYERS;i++)
		{

		// Saying something
		if (plyrpt->sprite>=0)
			{
//			*(xyz_ptr+(int)*xyz_ptr*3+1)=plyrpt->x;
//			*(xyz_ptr+(int)*xyz_ptr*3+2)=plyrpt->y+30;
//			*(xyz_ptr+(int)*xyz_ptr*3+3)=-plyrpt->z;
//			*(ref_ptr+(int)*xyz_ptr)=plyrpt->sprite;
//			(*xyz_ptr)++;
			}

		// Is he on?
		if (plyrpt->type)
			{

			// Set object data
			thisobj->x=plyrpt->x;			
			thisobj->y=plyrpt->y;
			thisobj->z=-plyrpt->z;
 			thisobj->crot=-plyrpt->crot;
			thisobj->srot=plyrpt->srot;

			// Tweening
			an=plyrpt->anim;
			ano=plyrpto->anim;
			if (xf=(an&1 && an>=MC_BFOOTBL && an<=MC_TROTF))
				mc1=&mcaps[an-1];
			else
				mc1=&mcaps[an];
			if (an!=ano||plyrpto->tween>=0)
				{
				xfo=(ano&1 && ano>=MC_BFOOTBL && ano<=MC_TROTF);
				if (plyrpto->tween<0)
					{
					plyrpto->tween=0;
					plyrpto->tstep=plyrpt->fstep*2*log_factor;
					plyrpto->animto=an;
					}
				else if (plyrpto->animto!=an)
					{
					tw=(plyrpto->twnfrm=plyrpto->twnpts2)+1;
					tw1=plyrpto->twnpts1+1;
					for (j=PLYRPTS*3;j;j--)
						*(tw++)=*(tw1++);
					plyrpto->tween=0;
					plyrpto->tstep=plyrpt->fstep*2*log_factor;
					plyrpto->anim=ano=plyrpto->animto;
					plyrpto->animto=an;
					xfo=(ano&1 && ano>=MC_BFOOTBL && ano<=MC_TROTF);
					}
				plyrpto->tween+=plyrpto->tstep;
				if (plyrpto->tween>=1)
					{
					plyrpto->tween=-1;
					thisobj->points=player_p[mc1->cappts+(short)(plyrpt->frame*mc1->capfrms)];
					plyrpto->twnfrm=thisobj->points;
					plyrpto->anim=plyrpto->animto;
					}
				else
					{
					tw1=player_p[mc1->cappts+(short)(plyrpt->frame*mc1->capfrms)]+1;
					tw2=plyrpto->twnfrm+1;
					tw=(thisobj->points=plyrpto->twnpts1)+1;
					if ((xf&&!xfo)||(!xf&&xfo))
						{
						pt1=plyrpto->tween;
						pt2=1-pt1;
						tw[0*3]  =tw1[0*3]  *pt1+tw2[0*3]  *pt2;
						tw[0*3+1]=tw1[0*3+1]*pt1+tw2[0*3+1]*pt2;
						tw[0*3+2]=tw1[0*3+2]*pt1-tw2[0*3+2]*pt2;
						tw[1*3]  =tw1[1*3]  *pt1+tw2[1*3]  *pt2;
						tw[1*3+1]=tw1[1*3+1]*pt1+tw2[1*3+1]*pt2;
						tw[1*3+2]=tw1[1*3+2]*pt1-tw2[1*3+2]*pt2;
						tw[2*3]  =tw1[2*3]  *pt1+tw2[2*3]  *pt2;
						tw[2*3+1]=tw1[2*3+1]*pt1+tw2[2*3+1]*pt2;
						tw[2*3+2]=tw1[2*3+2]*pt1-tw2[2*3+2]*pt2;
						tw[3*3]  =tw1[3*3]  *pt1+tw2[3*3]  *pt2;
						tw[3*3+1]=tw1[3*3+1]*pt1+tw2[3*3+1]*pt2;
						tw[3*3+2]=tw1[3*3+2]*pt1-tw2[3*3+2]*pt2;
						tw[4*3]  =tw1[4*3]  *pt1+tw2[4*3]  *pt2;
						tw[4*3+1]=tw1[4*3+1]*pt1+tw2[4*3+1]*pt2;
						tw[4*3+2]=tw1[4*3+2]*pt1-tw2[4*3+2]*pt2;
						tw[5*3]  =tw1[5*3]  *pt1+tw2[8*3]  *pt2;
						tw[5*3+1]=tw1[5*3+1]*pt1+tw2[8*3+1]*pt2;
						tw[5*3+2]=tw1[5*3+2]*pt1-tw2[8*3+2]*pt2;
						tw[6*3]  =tw1[6*3]  *pt1+tw2[9*3]  *pt2;
						tw[6*3+1]=tw1[6*3+1]*pt1+tw2[9*3+1]*pt2;
						tw[6*3+2]=tw1[6*3+2]*pt1-tw2[9*3+2]*pt2;
						tw[7*3]  =tw1[7*3]  *pt1+tw2[10*3]  *pt2;
						tw[7*3+1]=tw1[7*3+1]*pt1+tw2[10*3+1]*pt2;
						tw[7*3+2]=tw1[7*3+2]*pt1-tw2[10*3+2]*pt2;
						tw[8*3]  =tw1[8*3]  *pt1+tw2[5*3]  *pt2;
						tw[8*3+1]=tw1[8*3+1]*pt1+tw2[5*3+1]*pt2;
						tw[8*3+2]=tw1[8*3+2]*pt1-tw2[5*3+2]*pt2;
						tw[9*3]  =tw1[9*3]  *pt1+tw2[6*3]  *pt2;
						tw[9*3+1]=tw1[9*3+1]*pt1+tw2[6*3+1]*pt2;
						tw[9*3+2]=tw1[9*3+2]*pt1-tw2[6*3+2]*pt2;
						tw[10*3]  =tw1[10*3]  *pt1+tw2[7*3]  *pt2;
						tw[10*3+1]=tw1[10*3+1]*pt1+tw2[7*3+1]*pt2;
						tw[10*3+2]=tw1[10*3+2]*pt1-tw2[7*3+2]*pt2;
						tw[11*3]  =tw1[11*3]  *pt1+tw2[12*3]  *pt2;
						tw[11*3+1]=tw1[11*3+1]*pt1+tw2[12*3+1]*pt2;
						tw[11*3+2]=tw1[11*3+2]*pt1-tw2[12*3+2]*pt2;
						tw[12*3]  =tw1[12*3]  *pt1+tw2[11*3]  *pt2;
						tw[12*3+1]=tw1[12*3+1]*pt1+tw2[11*3+1]*pt2;
						tw[12*3+2]=tw1[12*3+2]*pt1-tw2[11*3+2]*pt2;
						tw[13*3]  =tw1[13*3]  *pt1+tw2[17*3]  *pt2;
						tw[13*3+1]=tw1[13*3+1]*pt1+tw2[17*3+1]*pt2;
						tw[13*3+2]=tw1[13*3+2]*pt1-tw2[17*3+2]*pt2;
						tw[14*3]  =tw1[14*3]  *pt1+tw2[18*3]  *pt2;
						tw[14*3+1]=tw1[14*3+1]*pt1+tw2[18*3+1]*pt2;
						tw[14*3+2]=tw1[14*3+2]*pt1-tw2[18*3+2]*pt2;
						tw[15*3]  =tw1[15*3]  *pt1+tw2[19*3]  *pt2;
						tw[15*3+1]=tw1[15*3+1]*pt1+tw2[19*3+1]*pt2;
						tw[15*3+2]=tw1[15*3+2]*pt1-tw2[19*3+2]*pt2;
						tw[17*3]  =tw1[17*3]  *pt1+tw2[13*3]  *pt2;
						tw[17*3+1]=tw1[17*3+1]*pt1+tw2[13*3+1]*pt2;
						tw[17*3+2]=tw1[17*3+2]*pt1-tw2[13*3+2]*pt2;
						tw[18*3]  =tw1[18*3]  *pt1+tw2[14*3]  *pt2;
						tw[18*3+1]=tw1[18*3+1]*pt1+tw2[14*3+1]*pt2;
						tw[18*3+2]=tw1[18*3+2]*pt1-tw2[14*3+2]*pt2;
						tw[19*3]  =tw1[19*3]  *pt1+tw2[15*3]  *pt2;
						tw[19*3+1]=tw1[19*3+1]*pt1+tw2[15*3+1]*pt2;
						tw[19*3+2]=tw1[19*3+2]*pt1-tw2[15*3+2]*pt2;
						tw[16*3]  =tw1[16*3]  *pt1+tw2[20*3]  *pt2;
						tw[16*3+1]=tw1[16*3+1]*pt1+tw2[20*3+1]*pt2;
						tw[16*3+2]=tw1[16*3+2]*pt1-tw2[20*3+2]*pt2;
						tw[20*3]  =tw1[20*3]  *pt1+tw2[16*3]  *pt2;
						tw[20*3+1]=tw1[20*3+1]*pt1+tw2[16*3+1]*pt2;
						tw[20*3+2]=tw1[20*3+2]*pt1-tw2[16*3+2]*pt2;
						tw[21*3]  =tw1[21*3]  *pt1+tw2[22*3]  *pt2;
						tw[21*3+1]=tw1[21*3+1]*pt1+tw2[22*3+1]*pt2;
						tw[21*3+2]=tw1[21*3+2]*pt1-tw2[22*3+2]*pt2;
						tw[22*3]  =tw1[22*3]  *pt1+tw2[21*3]  *pt2;
						tw[22*3+1]=tw1[22*3+1]*pt1+tw2[21*3+1]*pt2;
						tw[22*3+2]=tw1[22*3+2]*pt1-tw2[21*3+2]*pt2;
						if (tw2[23*3+1]<0)
							{
							tw[23*3]  =tw1[23*3];
							tw[23*3+1]=tw1[23*3+1];
							tw[23*3+2]=tw1[23*3+2];
							}
						else
							{
							tw[23*3]  =tw1[23*3]  *pt1+tw2[23*3]  *pt2;
							tw[23*3+1]=tw1[23*3+1]*pt1+tw2[23*3+1]*pt2;
							tw[23*3+2]=tw1[23*3+2]*pt1-tw2[23*3+2]*pt2;
							}
						tw[24*3]  =tw1[24*3]  *pt1+tw2[25*3]  *pt2;
						tw[24*3+1]=tw1[24*3+1]*pt1+tw2[25*3+1]*pt2;
						tw[24*3+2]=tw1[24*3+2]*pt1-tw2[25*3+2]*pt2;
						tw[25*3]  =tw1[25*3]  *pt1+tw2[24*3]  *pt2;
						tw[25*3+1]=tw1[25*3+1]*pt1+tw2[24*3+1]*pt2;
						tw[25*3+2]=tw1[25*3+2]*pt1-tw2[24*3+2]*pt2;
						tw[26*3]  =tw1[26*3]  *pt1+tw2[27*3]  *pt2;
						tw[26*3+1]=tw1[26*3+1]*pt1+tw2[27*3+1]*pt2;
						tw[26*3+2]=tw1[26*3+2]*pt1-tw2[27*3+2]*pt2;
						tw[27*3]  =tw1[27*3]  *pt1+tw2[26*3]  *pt2;
						tw[27*3+1]=tw1[27*3+1]*pt1+tw2[26*3+1]*pt2;
						tw[27*3+2]=tw1[27*3+2]*pt1-tw2[26*3+2]*pt2;
						}
					else
						{
						pt1=plyrpto->tween;
						pt2=1-pt1;
						for (j=PLYRPTS*3;j;j--)
							*(tw++)=*(tw1++)*pt1+*(tw2++)*pt2;
						}
					}
				}
			else
				// No tween
				{
				thisobj->points=player_p[mc1->cappts+(short)(plyrpt->frame*mc1->capfrms)];
				plyrpto->twnfrm=thisobj->points;
				plyrpto->anim=an;
				}

			// Motion captured ball
			if (thisobj->points[1+23*3+1]>=0)
				{
				ball.y=-thisobj->points[1+23*3];
				if (xf)
					ball.z=-thisobj->points[1+23*3+2];
				else
					ball.z=thisobj->points[1+23*3+2];
				ball.x=-ball.y*thisobj->crot+ball.z*thisobj->srot+thisobj->x;
				ball.z=ball.y*thisobj->srot+ball.z*thisobj->crot+thisobj->z;
				ball.y=thisobj->points[1+23*3+1]+thisobj->y;
				balld=1;

// (ANDYF) Grab motion capture coordinates of ball...
				mcap_ballx=0;//ball.x;
				mcap_bally=0;//ball.z;
				mcap_ballz=0;//ball.y;

				}

			// Wire frame mode
			if (wire)
				thisobj->faces=playertypes[11];
			else
				{

				// Is he a goalie
				if (xf)
					if (i==0||i==11)
						{ thisobj->faces=playertypes[(plyrpt->type==1||!setup.M8)?10:20]; }
					else
						if (game_data[plyrpt->type==1?TEMPa:TEMPb].players[i%11].skin_tone&&setup.M8)
							thisobj->faces=playertypes[(short)plyrpt->type+15];
						else
							thisobj->faces=playertypes[(short)plyrpt->type+5];
				else
					if (i==0||i==11)
						{ thisobj->faces=playertypes[(plyrpt->type==1||!setup.M8)?5:15]; }
					else
						if (game_data[plyrpt->type==1?TEMPa:TEMPb].players[i%11].skin_tone&&setup.M8)
							thisobj->faces=playertypes[(short)plyrpt->type+10];
						else
							thisobj->faces=playertypes[(short)plyrpt->type];
				if (thisobj->faces==player_fl&&!setup.M8) 
					thisobj->faces=player_fr;

				// Player number
	 			if (i<22)
					if (setup.detail.players)
						{
						thisobj->faces[0]=13;
						if (plyrpt->type==1)
							thisobj->faces[82]=-X_TM-2016-(plyrpt->number-1);
						else
							thisobj->faces[82]=-X_TM-2016-15-(plyrpt->number-1);
						}
					else
						thisobj->faces[0]=12;
				}

//plyrpt->frame=modf(plyrpt->frame+(float)1/mc1->capfrms,&null);
  
			// Draw object
			if (objdep(*thisobj)>15)
				{
				oldobj=curobj;
				if (xf)
					addobjyf(thisobj);
				else
					addobjy(thisobj);
				if (oldobj!=curobj) sortobj(oldobj);
				}
			thisobj++;
			}
		plyrpt++;
		plyrpto++;
		}						


//// BALL

	if (!balld)
		{
		ball.x=plyrpt->x;
		ball.y=plyrpt->y;
		ball.z=-plyrpt->z;
		}
	ball.crot=plyrpt->crot;
	ball.srot=plyrpt->srot;
	objdepd(&ball,ball_d);
	addobjxy(&ball,plyrpt->frame,plyrpt->fstep);
	plyrpt++;



//// GOALS

	oldobj=curobj;
	objdepd(&goal1_1,goal1_a);
	addobjnc(&goal1_1);
	if (oldobj!=curobj) {sortobj(oldobj);oldobj++;}
	objdepd(&goal2_1,goal2_a);
	addobjnc(&goal2_1);
	if (oldobj!=curobj) {sortobj(oldobj);oldobj++;}
	objdepd(&goal3_1,goal3_a);
	addobjnc(&goal3_1);
	if (oldobj!=curobj) {sortobj(oldobj);oldobj++;}
	objdepd(&goal4_1,goal4_a);
	addobjnc(&goal4_1);

	oldobj=curobj;
	objdepd(&goal1_2,goal1_b);
	addobjnc(&goal1_2);
	if (oldobj!=curobj) {sortobj(oldobj);oldobj++;}
	objdepd(&goal2_2,goal2_b);
	addobjnc(&goal2_2);
	if (oldobj!=curobj) {sortobj(oldobj);oldobj++;}
	objdepd(&goal3_2,goal3_b);
	addobjnc(&goal3_2);
	if (oldobj!=curobj) {sortobj(oldobj);oldobj++;}
	objdepd(&goal4_2,goal4_b);
	addobjnc(&goal4_2);


//// FLAGS

	if (setup.detail.lines)
		{
		oldobj=curobj;
		addobjnc(&flag_1);
		if (oldobj!=curobj) {sortobj(oldobj);oldobj++;}
		addobjnc(&flag_2);
		if (oldobj!=curobj) {sortobj(oldobj);oldobj++;}
		addobjnc(&flag_3);
		if (oldobj!=curobj) {sortobj(oldobj);oldobj++;}
		addobjnc(&flag_4);
		if (oldobj!=curobj) {sortobj(oldobj);oldobj++;}
	}


//// SPRITES

	if (buffer==&main_buff)
		addobjsp(xyz_ptr,ref_ptr);		
	

	// Sort objects from z value
	qsort(objtemp,curobj-objtemp,sizeof(objs),objcmp);

// Sort and render players, ball, goals and sprites.
	if (scrmode3DB<0)
		dispolsn();
	else
		dispolst3DB();


// Set up pt lists for 3D Blaster
	curpts3DB=&Vertex[0];
	curtex3DB=&Texture[0];

//// SCANNER

	if (key_togs[0xf]&&buffer!=&vidi_buff)
		if (scrmode==0x13)
			{
			scrpt scanner_l[]={8,56, 44,56, 44,8, 8,8};
			if (scrmode3DB<0)
				polyf((pnt *)scanner_l,4,filters[0]);
			else
				rectshadow3DB(buffer,8,render_buff.clip_hgt-56,36,48);
			draw_sprite(buffer,88,9,buffer->clip_hgt-55,0);
			plyrpt=(plyrdat *)plyrtb;
			for (i=0;i<22;i++)
				{
				if (plyrpt->type)
					draw_sprite(buffer,89+(((i<11&&(!(match_half&1)))||(i>=11&&(match_half&1)))?0:2),8+(plyrpt->z*34)/800,buffer->clip_hgt-10-(plyrpt->x*46)/1280,0);
				plyrpt++;					  
				}
			plyrpt+=3;
  			draw_sprite(buffer,89,8+(plyrpt->z*34)/800,buffer->clip_hgt-10-(ball.x*46)/1280,31);
			}
		else
			{
			scrpt scanner_h[]={16,112, 88,112, 88,16, 16,16};
			if (scrmode3DB<0)
				polyf((pnt *)scanner_h,4,filters[0]);
			else
				rectshadow3DB(buffer,16,render_buff.clip_hgt-112,72,96);
			draw_sprite_d(buffer,88,18,buffer->clip_hgt-110,0);
			plyrpt=(plyrdat *)plyrtb;
			for (i=0;i<22;i++)
				{
				if (plyrpt->type)
					draw_sprite(buffer,90+(((i<11&&(!(match_half&1)))||(i>=11&&(match_half&1)))?0:2),15+2*(plyrpt->z*34)/800,buffer->clip_hgt-21-2*(plyrpt->x*46)/1280,0);
				plyrpt++;
				}
			plyrpt+=3;
			draw_sprite(buffer,89,16+2*(plyrpt->z*34)/800,buffer->clip_hgt-20-2*(ball.x*46)/1280,31);
			}


//// ANIMATE TEXTURES

	if (0)//setup.M8&&vidi_anim) 
//	if (setup.M8&&vidi_anim) 
		if (spool)
			switch(vidi_anim)
				{
				case 1: do_extra_time_anim(spool); break;
				case 2: do_foul_anim(spool); break;
				case 3: do_full_time_anim(spool); break;
				case 4: do_half_time_anim(spool); break;
				case 5: do_penalty_anim(spool); break;
				case 6: do_goal_anim(spool); break;
				case 7: do_win_f_anim(spool); break;
				case 9: do_win_g_anim(spool); break;
				case 11: do_win_s_anim(spool); break;
				}
		else
			do_anim(vidi);

	if (wind_on)
		{
		fcoo+=log_factor;
		if (fcoo>=(128-wind_speed)/10)
			{
			if (flag_f[1+5*6+1]==-X_TM-2048)
				flag_f[1+5*6+1]=flag_f[1+5*6+6]=-X_TM-2046;
			else
				flag_f[1+5*6+1]=--flag_f[1+5*6+6];
			fcoo=0;
			}
		fs=(PI/2)*(wind_speed+16)/144;
		fx=8.5*sin(fs)+1;
		fy=8.5*cos(fs);
		flag_p[1+8*3]=fx*wind_x;
		flag_p[1+8*3+1]=15-fy;
		flag_p[1+8*3+2]=fx*wind_y;
		}
	else
		{
		flag_p[1+8*3]=1.751;
		flag_p[1+8*3+1]=6.629;
		flag_p[1+8*3+2]=1.751;
		}


	if (menu&&buffer!=&vidi_buff)
		{
		slco+=log_factor*5;
		if (mcount>0) 
			if (slide>0) while (slco>=1&&slide>0) slco--,slide--;
			else while (slco>=1) slco--,mcount--;
		else
			{
			while (slco>=1&&slide<oslide) slco--,slide++;
			if (slide>=oslide) menu=0,rdmenu=1;
			}
		if (scrmode==0x13)
			{
			menx3DB=menu_buff_l[menu-1].scale_x;
			meny3DB=menu_buff_l[menu-1].scale_y+(slide+12+(menu==22?10:0));
#ifdef BLASTDEMO
			if (scrmode3DB==1) meny3DB+=40;
#endif
			menu_buff.buff_start=menu_buff_l[menu-1].buff_start+MCGA_buff[0].buff_wid*(slide+12+(menu==22?10:0));
			menu_buff.buff_wid=menu_buff_l[menu-1].buff_wid;
			menu_buff.buff_hgt=menu_buff_l[menu-1].buff_hgt;
			menu_buff.clip_wid=menu_buff_l[menu-1].clip_wid;
			menu_buff.clip_hgt=menu_buff_l[menu-1].clip_hgt-(slide+12);
			}
		else
			{
			menx3DB=menu_buff_h[menu-1].scale_x+(scrmode3DB==5?80:0);
			meny3DB=menu_buff_h[menu-1].scale_y+((slide+12+(menu==22?10:0))<<1);
			if (scrmode3DB>=0)
				{
				switch (scrmode3DB)
					{
					case 2:meny3DB-=50;break;
					case 4:meny3DB+=80;break;
					case 5:meny3DB+=200;break;
					}
				menu_buff.buff_start=menu_buff_h[menu-1].buff_start+VESA_buff[scrmode==0x100?0:1][0].buff_wid*((slide+12+(menu==22?10:0))<<1);
				}
			else
				if (scrmode!=0x101)
					menu_buff.buff_start=menu_buff_h[menu-1].buff_start+VESA_buff[scrmode==0x100?0:1][0].buff_wid*((slide+12+(menu==22?10:0))<<1);
				else
					menu_buff.buff_start=menu_buff_h[menu-1].buff_start+VESA_buff[scrmode==0x100?0:1][0].buff_wid*((slide+12+(menu==22?10:0))<<1);
			menu_buff.buff_wid=menu_buff_h[menu-1].buff_wid;
			menu_buff.buff_hgt=menu_buff_h[menu-1].buff_hgt;
			menu_buff.clip_wid=menu_buff_h[menu-1].clip_wid;
			menu_buff.clip_hgt=menu_buff_h[menu-1].clip_hgt-((slide+12)<<1);
			}
		switch (menu)
			{
			case 1:	
				goal_menu(&menu_buff, mdata1, mdata2, mdata3);
				break;
			case 2:	
				booked_menu(&menu_buff, mdata1, mdata2);
				break;
			case 3:	
				off_menu(&menu_buff, mdata1, mdata2);
				break;
			case 4:	
				direct_menu(&menu_buff, mdata1);
				break;
			case 5:	
				indirect_menu(&menu_buff, mdata1);
				break;
			case 6:	
				penalty_menu(&menu_buff, mdata1);
				break;
			case 7:	
				corner_menu(&menu_buff, mdata1);
				break;
			case 8:	
				throw_menu(&menu_buff, mdata1);
				break;
			case 9:	
				goalkick_menu(&menu_buff, mdata1);
				break;
			case 10:	
				kickoff_menu(&menu_buff, mdata1);
				break;
			case 11:	
				offside_menu(&menu_buff, mdata1);
				break;
			case 12:	
				injured_menu(&menu_buff, mdata1, mdata2);
				break;
			case 13:	
				fulltime_menu(&menu_buff);
				adjust_menu();
				break;
			case 14:	
				extratime_menu(&menu_buff);
				adjust_menu();
				break;
			case 15:
				halftime_menu(&menu_buff);
				adjust_menu();
				break;
			case 16:	
				penalty_shootout_menu(&menu_buff);
				adjust_menu();
				break;
			case 17:	
				final_score_menu(&menu_buff);
				adjust_menu();
				break;
			case 18:	
				owngoal_menu(&menu_buff, mdata1, mdata2, mdata3);
				break;
			case 19:	
				options_menu(&menu_buff, mdata1, mdata2);
				break;
			case 20:	
				formation_menu(&menu_buff, mdata1, mdata2);
				break;
			case 21:	
				substitution_menu(&menu_buff, mdata1, mdata2);
				break;
			case 22:	
				replay_menu(&menu_buff, mdata1);
				break;
			case 23:	
				ref_menu(&menu_buff);
				break;
			case 24:	
				stats_menu(&menu_buff);
				break;
			}
		}

	if (key_togs[0x0a])
		vidi_l=1;
	else
		{
		if (vidi_l)
			stop_anim(vidi);
		vidi_l=0;
		}

	if (buffer!=&vidi_buff)
		{
		char tstr[50];
		int mid=buffer->clip_wid>>1;
		int end=buffer->clip_hgt;
		menx3DB=meny3DB=0;
		if (menu<19||menu>22)
			if (match_time.secs<10)
				sprintf(tstr,"%d:0%d",match_time.min,(int)match_time.secs);
			else
				sprintf(tstr,"%d:%2d",match_time.min,(int)match_time.secs);
		else
			switch(menu)
				{
				case 19:	sprintf(tstr,GetTEXT( OPTN_TEXT )); break;
				case 20:	sprintf(tstr,GetTEXT( FRMN_TEXT )); break;
				case 21:	sprintf(tstr,GetTEXT( SBTN_TEXT )); break;
				case 22:	sprintf(tstr,GetTEXT( RPLY_TEXT )); break;
				}
		if (scrmode==0x13)
			{
			draw_string(buffer,1,mid,1,tstr,31,2);
			if (!menu)
				{
//				draw_string(&MCGA_buff[0],end-8,140,0,EUROmatch_info.TeamAname,31,1);
				i=draw_string(buffer,1,mid-20,end-8,EUROmatch_info.TeamAname,32,1);
				if (sub_pending&1) draw_sprite(buffer,84,mid-20-i-16,end-16,0);
				sprintf(tstr,"%d=%d",team_a_goals,team_b_goals);
				draw_string(buffer,1,mid,end-8,tstr,31,2);
				i=draw_string(buffer,1,mid+20,end-8,EUROmatch_info.TeamBname,56,0);
				if (sub_pending&2) draw_sprite(buffer,85,mid+20+i+2,end-16,0);
				}
			}
		else
			{							  
			draw_string(buffer,2,mid,1,tstr,31,2);
			if (!menu)
				{
//				draw_string(&VESA_buff[0][0],end-14,mid-40,0,EUROmatch_info.TeamAname,31,1);
				i=draw_string(buffer,2,mid-40,end-14,EUROmatch_info.TeamAname,32,1);
				if (sub_pending&1) draw_sprite(buffer,86,mid-40-i-20,end-20,0);
				sprintf(tstr,"%d=%d",team_a_goals,team_b_goals);
				draw_string(buffer,2,mid,end-14,tstr,31,2);
				i=draw_string(buffer,2,mid+40,end-14,EUROmatch_info.TeamBname,56,0);
				if (sub_pending&2) draw_sprite(buffer,87,mid+40+i+4,end-20,0);
				}
			}
#ifdef BLASTDEMO
		char prbuf[20];
		static float cl=0;
		static int cnt,clk,oldclk;
		cnt++;
		if (20==cnt)
			{
			cnt=0;
			clk=clock();
			cl=(20.*CLOCKS_PER_SEC)/(clk-oldclk);
			oldclk=clock();
			}
		draw_string(&main_buff,2,0,0,gcvt(cl,3,prbuf),31,0);
#endif
		}

	if (scrmode3DB>=0&&curpts3DB!=Vertex)
		{
		SetRectangleOutput3DB(texaddr3DB[0]);
		Render3DB(curpts3DB-Vertex);
		}
	}



/************************/
/* BUFFER DUMP ROUTINES */


int spin=25;

void dumpMCGAs(scrpt dispx,scrpt dispy)
{
int x;
int y;

char* scr_=(char*) 0xa0000,*scr_end;
char* scr_buf=(char *)render_buff.buff_start;

float scr_off,scr_stp;

scr_stp=100*cos(spin*3.1416/50);
scr_+=32000-((int)scr_stp)*320;
if (!scr_stp) scr_stp=200;
else scr_stp=100/scr_stp;

if (scr_stp>=0)
	{
	scr_end=(char *)0xa0000;
	while (scr_end<scr_)
		{
		memset(scr_end,0,320);
		scr_end+=320;
		}
	while ((y=(int)scr_off)<200) 
		{
		for (x=0;x<320;x++)
			*(scr_++)=*(scr_buf+y*320+x);
		scr_off+=scr_stp;
		}
	while (scr_<(char *)0xafa00)
		{
		memset(scr_,0,320);
		scr_+=320;
		}
	}
else
	{
	scr_end=(char *)0xafa00;
	while (scr_end!=scr_)
		{
		scr_end-=320;
		memset(scr_end,0,320);
		}
	while ((y=(int)scr_off)>-200) 
		{
		for (x=0;x<320;x++)
			*(scr_++)=*(scr_buf-y*320+x);
		scr_-=640;
		scr_off+=scr_stp;
		}
	while (scr_>=(char *)0xa0000)
		{
		memset(scr_,0,320);
		scr_-=320;
		}
	}
spin++;
}


// Dump main buffer to MCGA 
void dumpMCGA(scrpt dispx,scrpt dispy)
	{
	int mx,my,mw,mh;
	BYTE *tptr;
	if (!rdmenu)
		{
		dispx=(320-render_buff.clip_wid)>>1;
		dispy=(200-render_buff.clip_hgt)>>1;
		mcgacpy(render_buff.buff_start,dispx,dispy,render_buff.clip_wid,render_buff.clip_hgt,render_buff.buff_wid);
		}
	else
		{
		mcgacpy(scrb+320,0,0,320,200,320);
		rdmenu=0;
		}
	if (menu && setup.screen_size)
		{
		mx=(320-menu_buff.clip_wid)>>1;
		my=((menu_buff.buff_start-mx)-MCGA_buff[0].buff_start)/320;
		if (menu_buff.clip_wid>render_buff.clip_wid)
			{
				mw=(menu_buff.clip_wid-render_buff.clip_wid)>>1;
				mh=menu_buff.clip_hgt;
				mcgacpy(menu_buff.buff_start,mx,my,mw,mh,320);
		  		vclear(menu_buff.buff_start,mw,mh,320,5);
				mcgacpy(menu_buff.buff_start+menu_buff.clip_wid-mw,mx+menu_buff.clip_wid-mw,my,mw,mh,320);
				vclear(menu_buff.buff_start+menu_buff.clip_wid-mw,mw,mh,320,5);
			}
		mw=render_buff.clip_wid;
		mh=(200-render_buff.clip_hgt)>>1;
		mx=(320-render_buff.clip_wid)>>1;
		my=200-mh;
		tptr=MCGA_buff[0].buff_start+my*320+mx;
		mcgacpy(tptr,mx,my,mw,mh,320);
		vclear(tptr,mw,mh,320,5);
		}
	}


// Dump general VESA 256-colour buffer to SVGA 
void dumpV256(scrpt dispx,scrpt dispy)
	{
	int mx,my,mw,mh;
	BYTE *tptr;
	if (!rdmenu)
		{
		dispx=(render_buff.buff_wid-render_buff.clip_wid)>>1;
		dispy=(render_buff.buff_hgt-render_buff.clip_hgt)>>1;
		svgacpy(render_buff.buff_start,dispx,dispy,render_buff.clip_wid,render_buff.clip_hgt,render_buff.buff_wid);
		}
	else
		{
		if (scrmode==0x100)
			svgacpy(scrb+640,0,0,640,400,640);
		else
			svgacpy(scrb+640,0,0,640,480,640);
		rdmenu=0;
		}
	if (menu && setup.screen_size)
		{
		mx=(640-menu_buff.clip_wid)>>1;
		my=((menu_buff.buff_start-mx)-VESA_buff[scrmode==0x100?0:1][0].buff_start)/640;
		if (menu_buff.clip_wid>render_buff.clip_wid)
			{
				mw=(menu_buff.clip_wid-render_buff.clip_wid)>>1;
				mh=menu_buff.clip_hgt;
				svgacpy(menu_buff.buff_start,mx,my,mw,mh,640);
				vclear(menu_buff.buff_start,mw,mh,640,5);
				svgacpy(menu_buff.buff_start+menu_buff.clip_wid-mw,mx+menu_buff.clip_wid-mw,my,mw,mh,640);
				vclear(menu_buff.buff_start+menu_buff.clip_wid-mw,mw,mh,640,5);
			}
		mw=render_buff.clip_wid;
		mh=(VESA_buff[scrmode==0x100?0:1][0].clip_hgt-render_buff.clip_hgt)>>1;
		mx=(640-render_buff.clip_wid)>>1;
		my=VESA_buff[scrmode==0x100?0:1][0].clip_hgt-mh;
		tptr=VESA_buff[scrmode==0x100?0:1][0].buff_start+my*640+mx;
		svgacpy(tptr,mx,my,mw,mh,640);
		vclear(tptr,mw,mh,640,5);
		}
	}


// Null dump routine
void dumpnull(scrpt dispx,scrpt dispy) {}


// 3d Blaster dump routine
void dump3DB(scrpt dispx,scrpt dispy)
	{
	SwapBuffer3DB();	
//	ClearBuffer3DB();	
	}


// Dump vidi buffer to map page through filter (already there)
void dumpvidi1(scrpt dispx,scrpt dispy)
	{
	BYTE *scrpt;
	short i,j;
	if (vidi_anim) return;
	scrpt=render_buff.buff_start;
	for (i=0;i<render_buff.clip_hgt;i++)
		{
		for (j=0;j<render_buff.clip_wid;j++)
			{
			*scrpt=filters[1][*scrpt];
			scrpt++;
			}
		scrpt+=render_buff.buff_wid-render_buff.clip_wid;
		}
	}



/********************************/
/* INITIALISE DISPLAY & OBJECTS */

word getselectors(word noselectors)
	{
	union REGS regs;
	regs.w.cx=noselectors;
	regs.w.ax=0;
	int386(0x31,&regs,&regs);
	if (regs.w.cflag&1)
		{
		puts("Error allocating selectors");
		return(-1);						            
		}
	return(regs.w.ax);
	}

int setselector(word selector, BYTE *address, dword length)
	{
	union REGS regs;
	if (w95) address-=0x10000;
	regs.w.dx=(dword)address%65536;
	regs.w.cx=(dword)address/65536;
	regs.w.bx=selector;
	regs.w.ax=7;
	int386(0x31,&regs,&regs);
	if (regs.w.cflag&1)
		{
		puts("Error preparing selectors");
		return(-1);						            
		}
	regs.w.dx=(length-1)%65536;
	regs.w.cx=(length-1)/65536;
	regs.w.bx=selector;
	regs.w.ax=8;
	int386(0x31,&regs,&regs);
	if (regs.w.cflag&1)
		{
		printf("Error preparing selectors");
		return(-1);						            
		}
	return(0);
	}

int freeselector(word selector)
	{
	union REGS regs;
	regs.w.bx=selector;
	regs.w.ax=1;
	int386(0x31,&regs,&regs);
	if (regs.w.cflag&1)
		{
		puts("Error freeing selectors");
		return(-1);						            
		}
	return(0);
	}

word nextselectordisp(word selector)
	{
	union REGS regs;
	regs.w.ax=3;
	int386(0x31,&regs,&regs);
	return(regs.w.ax);
	}								

// Object 'constructor' function
void initobj(obj *object,ptlist points,facelist faces,datapt x,datapt y,datapt z,floatpt crot,floatpt srot)
	{
	object->points=points;
	object->faces=faces;
	object->x=x;
	object->y=y;
	object->z=z;
	object->crot=crot;
	object->srot=srot;
	};


int skyno;

int init3d()
	{
	int i,j,mc_tot;
	word selector;
	BYTE *seg;
	BYTE *tptr,*tptr2;
	word *stp;
	dword *tlptr;

	maps=NULL,scrb=NULL,sky=NULL,textures=NULL,filters=NULL,player_p=NULL,plyrtwtb=NULL;
	objlist=NULL,pollist=NULL,ptslist=NULL,rotlist=NULL,anim_data=NULL;
	fd=NULL;
	for (i=0;i<MAPPAGES+noloop+2;i++)
		mapsel[i]=-1;

	// Free memory?
	if (setup.verbose) {printf("Free memory = %d\n",get_mem_info());fflush(stdout);}

	// Malloc data areas
	if (setup.verbose) {puts("Preparing memory areas...");fflush(stdout);}
	if (setup.M8)
		mcaps=mcaps8;
	else
		mcaps=mcaps4;
	mc_tot=0;
	for (i=0;i<MC_NO;i++)
		{
		mcaps[i].cappts=mc_tot;
		mc_tot+=mcaps[i].capfrms;
		}
	if (setup.verbose) {printf("Motion capture frames: %d\n",mc_tot);fflush(stdout);}
	if (setup.M8)
		{
		if (
			 (maps=(mappage *)mallocx((mappages=MAPPAGES)*65536)) == NULL ||
			 (scrb=(BYTE *)mallocx(640*482)) == NULL ||
			 (sky=(BYTE *)mallocx(640*482)) == NULL ||
			 (textures=(texture *)mallocx((NOTEXTURES+CLIP_TEXTURES+1)*sizeof(texture))) == NULL ||
			 (filters=(filter *)mallocx(FILTERS*sizeof(filter))) == NULL ||
			 (player_p=(capfrm *)mallocx(mc_tot*sizeof(capfrm))) == NULL ||
			 (plyrtwtb=(plyrtwdat *)mallocx(NPLAYERS*sizeof(plyrtwdat))) == NULL ||
			 (objlist=(objs *)mallocx(MAXOBJ*sizeof(objs))) == NULL ||
			 (pollist=(pols *)mallocx(MAXPOL*sizeof(pols))) == NULL ||
			 (ptslist=(scrpt *)mallocx(MAXPOL*10*sizeof(scrpt))) == NULL ||
			 (rotlist=(rotpt *)mallocx(MAXPTS*4*sizeof(rotpt))) == NULL ||
			 (anim_data=(char *)mallocx(ANIM_SPACE)) == NULL )
			{
			puts("Error reserving memory");
 			goto init3d_error;
			}
		}
	else
		{
		setup.start_res=0;
		if (
			 (maps=(mappage *)mallocx((mappages=MAPPAGES_4)*65536)) == NULL ||
			 (scrb=(BYTE *)mallocx(320*202)) == NULL ||
			 (textures=(texture *)mallocx((NOTEXTURES+CLIP_TEXTURES+1)*sizeof(texture))) == NULL ||
			 (filters=(filter *)mallocx(FILTERS*sizeof(filter))) == NULL ||
			 (player_p=(capfrm *)mallocx(mc_tot*sizeof(capfrm))) == NULL ||
			 (plyrtwtb=(plyrtwdat *)mallocx(NPLAYERS*sizeof(plyrtwdat))) == NULL ||
			 (objlist=(objs *)mallocx(MAXOBJ*sizeof(objs))) == NULL ||
			 (pollist=(pols *)mallocx(MAXPOL*sizeof(pols))) == NULL ||
			 (ptslist=(scrpt *)mallocx(MAXPOL*10*sizeof(scrpt))) == NULL ||
			 (rotlist=(rotpt *)mallocx(MAXPTS*4*sizeof(rotpt))) == NULL )
			{
			puts("Error reserving memory");
 			goto init3d_error;
			}
		}


	// Load texture maps and other files
	if (setup.verbose) {puts("Reading data files...");fflush(stdout);}
  	if (readrawfile(dataoffs,(BYTE *)load_offsets) == NULL) goto init3d_error;
	if (opendatafile(datafile) < 0 ) goto init3d_error;


	if (setup.detail.stadia||network_on) 
		{
		if (network_on)
			{
			setup.detail.stadia=1;
			setup.stadium+=45;
			}
		else
			if (stadlist[setup.stadium+90].tmdfile==-1||performance<=18)
				setup.stadium+=45;
			else
				setup.stadium+=90;
		}


#ifdef LINK
	skyno=stadlist[setup.stadium].skytypes[(count&1)?1:0];
#else
	skyno=stadlist[setup.stadium].skytypes[(rand()&1)?1:0];
#endif

	if (setup.M8)
	{
		if (
	    	readfile(PAL_FOOTY,pal) == NULL ||
		 	readfile(TMD_TEXDATA,(BYTE *)&textures[1]) == NULL
			)
 			goto init3d_error;
		if (
	    	readfile(teamlist[setup.team_a].headfile,maps[0]) == NULL ||
	    	readfile(teamlist[setup.team_b].headfile,maps[0]+128*256) == NULL ||
	    	readfile(teamlist[setup.team_a].torsofile,maps[1]) == NULL ||
	    	readfile(teamlist[setup.team_b_kit].torsofile,maps[2]) == NULL ||
	    	readfile(teamlist[setup.team_a].limbsfile,maps[3]) == NULL ||
	    	readfile(teamlist[setup.team_b_kit].limbsfile,maps[3]+80*256) == NULL ||
	    	readfile(BM_FEET,maps[3]+158*256) == NULL ||
	    	readfile(BM_REFKPTOR,maps[4]) == NULL ||
	    	readfile(BM_EXTRA1,maps[X_BM]) == NULL ||
		   readfile(teamlist[setup.team_a].nosfile,maps[X_BM]+62*256) == NULL ||
	    	readfile(BM_EXTRA3,maps[X_BM+1]) == NULL ||
			readfile(stadlist[setup.stadium].sb1file,maps[S_BM]) == NULL ||
		   readfile(stadlist[setup.stadium].sb2file,maps[S_BM+1]) == NULL ||
			readfile(teamlist[setup.team_a].torsofile,maps[S_BM+2]) == NULL ||
			readfile(teamlist[setup.team_b_kit].torsofile,maps[S_BM+3]) == NULL ||
	    	readfile(BM_XLIMBS,maps[S_BM+4]) == NULL ||
	    	readfile(teamlist[setup.team_a].limbsfile,maps[S_BM+4]) == NULL ||
	    	readfile(teamlist[setup.team_b_kit].limbsfile,maps[S_BM+4]+80*256) == NULL ||
	    	readfile(BM_XRFKPLIM,maps[S_BM+5]) == NULL ||
	    	readfile(BM_REFKPTOR,maps[S_BM+6]) == NULL ||
#ifdef NEW
			readfile(BM_NETS,maps[S_BM+7]) == NULL ||
#endif
	    	readfile(teamlist[setup.team_a].palfile,&pal[3*32]) == NULL ||
	    	readfile(teamlist[setup.team_b_kit].palfile,&pal[3*56]) == NULL ||
	    	readfile(teamlist[setup.team_a].skinfile,&pal[3*80]) == NULL ||
	    	readfile(teamlist[setup.team_b].skinfile,&pal[3*88]) == NULL ||
	    	readfile(stadlist[setup.stadium].pitchpfile,&pal[3*128]) == NULL ||
	    	readfile(teamlist[setup.team_a].homepfile,&pal[3*224]) == NULL ||
	    	readfile(teamlist[setup.team_b].awaypfile,&pal[3*232]) == NULL ||
	    	readfile(skylist[skyno].skypfile,&pal[3*208]) == NULL ||
	   	readfile(skylist[skyno].skyfile,sky) == NULL
			)
 			goto init3d_error;

		int st_a0;
		int st_b0_kit;
//		st_a0=14;//setup.team_a?36:14;
//		st_b0_kit=36;//setup.team_b_kit?36:14;
		st_a0=setup.team_a;
		st_b0_kit=setup.team_b_kit;

		switch(st_a0/42)
			{
			case 0: if (readfile(BM_KGRIDS1,maps[5])==NULL) goto init3d_error; break;
#ifndef BBS
			case 1: if (readfile(BM_KGRIDS2,maps[5])==NULL) goto init3d_error; break;
#endif
			}
		j=st_a0%42;
		tptr=maps[5]+((j/7)*42+1)*256+(j%7)*36+1;
		tptr2=maps[X_BM+1]+111*256+220;
		for (i=0;i<40;i++)
			{
			memcpy(tptr2,tptr,35);
			tptr+=256;
			tptr2+=256;
			}
		switch(st_b0_kit/42)
			{
			case 0: if (readfile(BM_KGRIDS1,maps[5])==NULL) goto init3d_error; break;
#ifndef BBS
			case 1: if (readfile(BM_KGRIDS2,maps[5])==NULL) goto init3d_error; break;
#endif
			}
		j=st_b0_kit%42;
		tptr=maps[5]+((j/7)*42+1)*256+(j%7)*36+1;
		tptr2=maps[X_BM+1]+151*256+220;
		for (i=0;i<40;i++)
			{
			memcpy(tptr2,tptr,35);
			tptr+=256;
			tptr2+=256;
			}
		switch(st_a0/9)
			{
			case 0: if (readfile(BM_KGRID1,maps[5])==NULL) goto init3d_error; break;
#ifndef BBS
			case 1: if (readfile(BM_KGRID2,maps[5])==NULL) goto init3d_error; break;
			case 2: if (readfile(BM_KGRID3,maps[5])==NULL) goto init3d_error; break;
			case 3: if (readfile(BM_KGRID4,maps[5])==NULL) goto init3d_error; break;
			case 4: if (readfile(BM_KGRID5,maps[5])==NULL) goto init3d_error; break;
			case 5: if (readfile(BM_KGRID6,maps[5])==NULL) goto init3d_error; break;
#endif
			}
		j=st_a0%9;
		tptr=maps[5]+((j/3)*83+2)*256+(j%3)*70+1;
		tptr2=maps[X_BM+1];
		for (i=0;i<79;i++)
			{
			memcpy(tptr2,tptr,69);
			tptr+=256;
			tptr2+=256;
			}
		switch(st_b0_kit/9)
			{
			case 0: if (readfile(BM_KGRID1,maps[5])==NULL) goto init3d_error; break;
#ifndef BBS
			case 1: if (readfile(BM_KGRID2,maps[5])==NULL) goto init3d_error; break;
			case 2: if (readfile(BM_KGRID3,maps[5])==NULL) goto init3d_error; break;
			case 3: if (readfile(BM_KGRID4,maps[5])==NULL) goto init3d_error; break;
			case 4: if (readfile(BM_KGRID5,maps[5])==NULL) goto init3d_error; break;
			case 5: if (readfile(BM_KGRID6,maps[5])==NULL) goto init3d_error; break;
#endif
			}
		j=st_b0_kit%9;
		tptr=maps[5]+((j/3)*83+2)*256+(j%3)*70+1;
		tptr2=maps[X_BM+1]+69;
		for (i=0;i<79;i++)
			{
			memcpy(tptr2,tptr,69);
			tptr+=256;
			tptr2+=256;
			}
    	if (readfile(BM_REFKPLIM,maps[5]) == NULL) goto init3d_error;

		tptr=maps[X_BM]+89*256+161;
		for (i=0;i<27;i++)
			{
			memcpy(tptr+91*256,tptr,92);
			tptr+=256;
			}
	   if (readfile(teamlist[setup.team_b_kit].nosfile,maps[X_BM]+89*256) == NULL) exit (1);
		tptr=maps[X_BM]+116*256+161;
		for (i=0;i<27;i++)
			{
			memcpy(tptr+64*256-92,tptr,92);
			tptr+=256;
			}
    	if (readfile(stadlist[setup.stadium].pitchfile,maps[X_BM]+116*256) == NULL) exit (1);
		tptr=maps[X_BM]+180*256+69;
		for (i=0;i<27;i++)
			{
			memcpy(tptr-64*256,tptr,184);
			tptr+=256;
			}
    	if (readfile(BM_EXTRA2,maps[X_BM]+180*256) == NULL) exit (1);
		if (
			readfile(stadlist[setup.stadium].tmdfile,(BYTE *)&textures[S_TM]) == NULL ||
		 	readfile(stadlist[setup.stadium].s1pfile,(BYTE *)&stad1_p) == NULL ||
		 	readfile(stadlist[setup.stadium].s1ffile,(BYTE *)&stad1_f) == NULL ||
		 	readfile(stadlist[setup.stadium].s2pfile,(BYTE *)&stad2_p) == NULL ||
		 	readfile(stadlist[setup.stadium].s2ffile,(BYTE *)&stad2_f) == NULL ||
		 	readfile(stadlist[setup.stadium].s3pfile,(BYTE *)&stad3_p) == NULL ||
		 	readfile(stadlist[setup.stadium].s3ffile,(BYTE *)&stad3_f) == NULL ||
		 	readfile(stadlist[setup.stadium].s4pfile,(BYTE *)&stad4_p) == NULL ||
		 	readfile(stadlist[setup.stadium].s4ffile,(BYTE *)&stad4_f) == NULL
			)
 			goto init3d_error;
		if (
			readfile(MPB_AFOOTB,(BYTE *)&player_p[mcaps[MC_AFOOTB].cappts]) == NULL ||
	    	readfile(MPB_AFOOTC,(BYTE *)&player_p[mcaps[MC_AFOOTC].cappts]) == NULL ||
	    	readfile(MPB_ABODYB,(BYTE *)&player_p[mcaps[MC_ABODYB].cappts]) == NULL ||
	    	readfile(MPB_ABODYC,(BYTE *)&player_p[mcaps[MC_ABODYC].cappts]) == NULL ||
	    	readfile(MPB_AHEADB,(BYTE *)&player_p[mcaps[MC_AHEADB].cappts]) == NULL ||
	    	readfile(MPB_AHEADC,(BYTE *)&player_p[mcaps[MC_AHEADC].cappts]) == NULL ||
	    	readfile(MPB_AJUMPB,(BYTE *)&player_p[mcaps[MC_AJUMPB].cappts]) == NULL ||
	    	readfile(MPB_AJUMPC,(BYTE *)&player_p[mcaps[MC_AJUMPC].cappts]) == NULL ||
	    	readfile(MPB_BFOOTB,(BYTE *)&player_p[mcaps[MC_BFOOTBL].cappts]) == NULL ||
	    	readfile(MPB_BFOOTC,(BYTE *)&player_p[mcaps[MC_BFOOTCL].cappts]) == NULL ||
	    	readfile(MPB_BBODYB,(BYTE *)&player_p[mcaps[MC_BBODYBL].cappts]) == NULL ||
	    	readfile(MPB_BBODYC,(BYTE *)&player_p[mcaps[MC_BBODYCL].cappts]) == NULL ||
	    	readfile(MPB_BHEADB,(BYTE *)&player_p[mcaps[MC_BHEADBL].cappts]) == NULL ||
	    	readfile(MPB_BHEADC,(BYTE *)&player_p[mcaps[MC_BHEADCL].cappts]) == NULL ||
	    	readfile(MPB_BJUMPB,(BYTE *)&player_p[mcaps[MC_BJUMPBL].cappts]) == NULL ||
	    	readfile(MPB_CFOOTB,(BYTE *)&player_p[mcaps[MC_CFOOTBL].cappts]) == NULL || 
	    	readfile(MPB_CFOOTC,(BYTE *)&player_p[mcaps[MC_CFOOTCL].cappts]) == NULL || 
	    	readfile(MPB_CBODYB,(BYTE *)&player_p[mcaps[MC_CBODYBL].cappts]) == NULL ||
	    	readfile(MPB_CBODYC,(BYTE *)&player_p[mcaps[MC_CBODYCL].cappts]) == NULL ||
	    	readfile(MPB_CHEADB,(BYTE *)&player_p[mcaps[MC_CHEADBL].cappts]) == NULL ||
	    	readfile(MPB_CJUMPB,(BYTE *)&player_p[mcaps[MC_CJUMPBL].cappts]) == NULL || 
	    	readfile(MPB_SHOOT1,(BYTE *)&player_p[mcaps[MC_SHOOTR].cappts]) == NULL ||
	    	readfile(MPB_CHIP1,(BYTE *)&player_p[mcaps[MC_CHIPR].cappts]) == NULL ||
	    	readfile(MPB_SPASS1,(BYTE *)&player_p[mcaps[MC_PASSR].cappts]) == NULL ||
	    	readfile(MPB_CROSS1,(BYTE *)&player_p[mcaps[MC_CROSSR].cappts]) == NULL ||
	    	readfile(MPB_VOLLEY,(BYTE *)&player_p[mcaps[MC_VOLLEYR].cappts]) == NULL ||
//	    	readfile(MPB_TOE2,(BYTE *)&player_p[mcaps[MC_TOER].cappts]) == NULL ||
	    	readfile(MPB_DIAGPASS,(BYTE *)&player_p[mcaps[MC_DIAGPASSR].cappts]) == NULL ||
	    	readfile(MPB_DIAGBACK,(BYTE *)&player_p[mcaps[MC_DIAGBACKR].cappts]) == NULL ||
	    	readfile(MPB_SIDEPASS,(BYTE *)&player_p[mcaps[MC_SIDEPASSR].cappts]) == NULL ||
	    	readfile(MPB_BACKHEEL,(BYTE *)&player_p[mcaps[MC_BACKHEELR].cappts]) == NULL ||
	    	readfile(MPB_SVTOSTD,(BYTE *)&player_p[mcaps[MC_STOSL].cappts]) == NULL ||
	    	readfile(MPB_SVTOSTB,(BYTE *)&player_p[mcaps[MC_STOSBL].cappts]) == NULL ||
	    	readfile(MPB_TRAP,(BYTE *)&player_p[mcaps[MC_TRAPR].cappts]) == NULL ||
			readfile(MPB_RIDE4,(BYTE *)&player_p[mcaps[MC_RIDEL].cappts]) == NULL ||
	    	readfile(MPB_SOCKS2,(BYTE *)&player_p[mcaps[MC_SOCKSR].cappts]) == NULL ||
			readfile(MPB_TROTB,(BYTE *)&player_p[mcaps[MC_TROTB].cappts]) == NULL ||
			readfile(MPB_TROTG,(BYTE *)&player_p[mcaps[MC_TROTG].cappts]) == NULL ||
	    	readfile(MPB_TROTD1,(BYTE *)&player_p[mcaps[MC_TROTD].cappts]) == NULL ||
	    	readfile(MPB_TROTA,(BYTE *)&player_p[mcaps[MC_TROTA].cappts]) == NULL ||
	    	readfile(MPB_TROTE,(BYTE *)&player_p[mcaps[MC_TROTE].cappts]) == NULL ||
	    	readfile(MPB_RUN2,(BYTE *)&player_p[mcaps[MC_RUN].cappts]) == NULL ||
	    	readfile(MPB_JOG1,(BYTE *)&player_p[mcaps[MC_JOG].cappts]) == NULL ||
	    	readfile(MPB_BARGE,(BYTE *)&player_p[mcaps[MC_BARGE].cappts]) == NULL ||
	    	readfile(MPB_THROWW,(BYTE *)&player_p[mcaps[MC_THROWW].cappts]) == NULL ||
//	    	readfile(MPB_SHAMEW,(BYTE *)&player_p[mcaps[MC_SHAMEW].cappts]) == NULL ||
//	    	readfile(MPB_LIE1,(BYTE *)&player_p[mcaps[MC_LIE].cappts]) == NULL ||
			readfile(MPB_STAND1,(BYTE *)&player_p[mcaps[MC_STAND].cappts]) == NULL  ||
	    	readfile(MPB_SHEADER,(BYTE *)&player_p[mcaps[MC_S_HEAD].cappts]) == NULL ||
	    	readfile(MPB_JHEADER,(BYTE *)&player_p[mcaps[MC_J_HEAD].cappts]) == NULL ||
	    	readfile(MPB_HDOWN1,(BYTE *)&player_p[mcaps[MC_D_HEAD].cappts]) == NULL ||
//	    	readfile(MPB_HEADUP,(BYTE *)&player_p[mcaps[MC_U_HEAD].cappts]) == NULL ||
	    	readfile(MPB_DHEADER,(BYTE *)&player_p[mcaps[MC_DV_HEAD].cappts]) == NULL ||
	    	readfile(MPB_CHEST1,(BYTE *)&player_p[mcaps[MC_CHEST].cappts]) == NULL ||
			readfile(MPB_STACKLE,(BYTE *)&player_p[mcaps[MC_S_TACKLE].cappts]) == NULL ||
			readfile(MPB_STEAL2,(BYTE *)&player_p[mcaps[MC_STEAL].cappts]) == NULL ||
	    	readfile(MPB_OVERHEAD,(BYTE *)&player_p[mcaps[MC_OVERHEAD].cappts]) == NULL ||
			readfile(MPB_THROWL,(BYTE *)&player_p[mcaps[MC_THROWL].cappts]) == NULL ||
	    	readfile(MPB_THROWS,(BYTE *)&player_p[mcaps[MC_THROWS].cappts]) == NULL ||
	    	readfile(MPB_FALLR,(BYTE *)&player_p[mcaps[MC_FALLR].cappts]) == NULL ||
//	    	readfile(MPB_FALLS,(BYTE *)&player_p[mcaps[MC_FALLS].cappts]) == NULL ||
	    	readfile(MPB_CELEB,(BYTE *)&player_p[mcaps[MC_CELEB].cappts]) == NULL ||
//	    	readfile(MPB_SHAME1,(BYTE *)&player_p[mcaps[MC_SHAME].cappts]) == NULL ||
	    	readfile(MPB_GETUP,(BYTE *)&player_p[mcaps[MC_GETUP].cappts]) == NULL ||
	    	readfile(MPB_GETUPF,(BYTE *)&player_p[mcaps[MC_GETUPF].cappts]) == NULL ||
			readfile(MPB_STANDB,(BYTE *)&player_p[mcaps[MC_STANDB].cappts]) == NULL ||
	    	readfile(MPB_BOUNCE,(BYTE *)&player_p[mcaps[MC_BOUNCE].cappts]) == NULL ||
	    	readfile(MPB_KICKOUT,(BYTE *)&player_p[mcaps[MC_KICKOUT].cappts]) == NULL ||
	    	readfile(MPB_HALFVOLL,(BYTE *)&player_p[mcaps[MC_HALFVOLL].cappts]) == NULL ||
	    	readfile(MPB_THROW,(BYTE *)&player_p[mcaps[MC_THROW].cappts]) == NULL ||
	    	readfile(MPB_ROLL,(BYTE *)&player_p[mcaps[MC_ROLL].cappts]) == NULL || 
	    	readfile(MPB_RUNWITHB,(BYTE *)&player_p[mcaps[MC_RUNWITHB].cappts]) == NULL || 
	    	readfile(MPB_WAVEUP,(BYTE *)&player_p[mcaps[MC_WAVEUP].cappts]) == NULL || 
//	    	readfile(MPB_PENALTY,(BYTE *)&player_p[mcaps[MC_PENALTY].cappts]) == NULL ||
//	    	readfile(MPB_PLEAD,(BYTE *)&player_p[mcaps[MC_PLEAD].cappts]) == NULL ||
	    	readfile(MPB_CRTOSTB1,(BYTE *)&player_p[mcaps[MC_CRTOSTB].cappts]) == NULL ||
	    	readfile(MPB_PICKBALL,(BYTE *)&player_p[mcaps[MC_PICKBALL].cappts]) == NULL
#ifdef NEW
	   || readfile(MPB_DUCK,(BYTE *)&player_p[mcaps[MC_DUCK].cappts]) == NULL ||
	    	readfile(MPB_FINGER,(BYTE *)&player_p[mcaps[MC_FINGER].cappts]) == NULL ||
	    	readfile(MPB_KNEE,(BYTE *)&player_p[mcaps[MC_KNEE].cappts]) == NULL ||
	    	readfile(MPB_PLANE,(BYTE *)&player_p[mcaps[MC_PLANE].cappts]) == NULL ||
	    	readfile(MPB_MILLER,(BYTE *)&player_p[mcaps[MC_MILLER].cappts]) == NULL ||
	    	readfile(MPB_BABY,(BYTE *)&player_p[mcaps[MC_BABY].cappts]) == NULL ||
	    	readfile(MPB_MOON,(BYTE *)&player_p[mcaps[MC_MOON].cappts]) == NULL ||
	    	readfile(MPB_PUMP,(BYTE *)&player_p[mcaps[MC_PUMP].cappts]) == NULL ||
	    	readfile(MPB_REEVES,(BYTE *)&player_p[mcaps[MC_REEVES].cappts]) == NULL
#endif
			)
 			goto init3d_error;
	}
	else				
		{
		if (
	    	readfile(PAL_FOOTY,pal) == NULL ||
		 	readfile(TMD_TEXDATA,(BYTE *)&textures[1]) == NULL
			)
 			goto init3d_error;
		if (
	    	readfile(teamlist[setup.team_a].headfile,maps[0]) == NULL ||
	    	readfile(teamlist[setup.team_b].headfile,maps[0]+128*256) == NULL ||
	    	readfile(teamlist[setup.team_a].torsofile,maps[1]) == NULL ||
	    	readfile(teamlist[setup.team_b_kit].torsofile,maps[2]) == NULL ||
	    	readfile(teamlist[setup.team_a].limbsfile,maps[3]) == NULL ||
	    	readfile(teamlist[setup.team_b_kit].limbsfile,maps[3]+80*256) == NULL ||
	    	readfile(BM_FEET,maps[3]+158*256) == NULL ||
	    	readfile(BM_REFKPTOR,maps[4]) == NULL ||
	    	readfile(BM_EXTRA1,maps[X_BM]) == NULL ||
		   readfile(teamlist[setup.team_a].nosfile,maps[X_BM]+62*256) == NULL ||
	    	readfile(BM_EXTRA3,maps[X_BM+1]) == NULL ||
		   readfile(stadlist[setup.stadium].sb1file,maps[S_BM]) == NULL ||
		   readfile(stadlist[setup.stadium].sb2file,maps[S_BM+1]) == NULL ||
	    	readfile(teamlist[setup.team_a].palfile,&pal[3*32]) == NULL ||
	    	readfile(teamlist[setup.team_b_kit].palfile,&pal[3*56]) == NULL ||
	    	readfile(teamlist[setup.team_a].skinfile,&pal[3*80]) == NULL ||
	    	readfile(teamlist[setup.team_b].skinfile,&pal[3*88]) == NULL ||
	    	readfile(stadlist[setup.stadium].pitchpfile,&pal[3*128]) == NULL ||
	    	readfile(teamlist[setup.team_a].homepfile,&pal[3*224]) == NULL ||
	    	readfile(teamlist[setup.team_b].awaypfile,&pal[3*232]) == NULL
			)
 			goto init3d_error;

		int st_a1;
		int st_b1_kit;
//		st_a1=14;//setup.team_a?36:14;
//		st_b1_kit=36;//setup.team_b_kit?36:14;
		st_a1=setup.team_a;
		st_b1_kit=setup.team_b_kit;

		switch(st_a1/42)
			{
			case 0: if (readfile(BM_KGRIDS1,maps[5])==NULL) goto init3d_error; break;
#ifndef BBS
			case 1: if (readfile(BM_KGRIDS2,maps[5])==NULL) goto init3d_error; break;
#endif
			}
		j=st_a1%42;
		tptr=maps[5]+((j/7)*42+1)*256+(j%7)*36+1;
		tptr2=maps[X_BM+1]+111*256+220;
		for (i=0;i<40;i++)
			{
			memcpy(tptr2,tptr,35);
			tptr+=256;
			tptr2+=256;
			}
		switch(st_b1_kit/42)
			{
			case 0: if (readfile(BM_KGRIDS1,maps[5])==NULL) goto init3d_error; break;
#ifndef BBS
			case 1: if (readfile(BM_KGRIDS2,maps[5])==NULL) goto init3d_error; break;
#endif
			}
		j=st_b1_kit%42;
		tptr=maps[5]+((j/7)*42+1)*256+(j%7)*36+1;
		tptr2=maps[X_BM+1]+151*256+220;
		for (i=0;i<40;i++)
			{
			memcpy(tptr2,tptr,35);
			tptr+=256;
			tptr2+=256;
			}
		switch(st_a1/9)
			{
			case 0: if (readfile(BM_KGRID1,maps[5])==NULL) goto init3d_error; break;
#ifndef BBS
			case 1: if (readfile(BM_KGRID2,maps[5])==NULL) goto init3d_error; break;
			case 2: if (readfile(BM_KGRID3,maps[5])==NULL) goto init3d_error; break;
			case 3: if (readfile(BM_KGRID4,maps[5])==NULL) goto init3d_error; break;
			case 4: if (readfile(BM_KGRID5,maps[5])==NULL) goto init3d_error; break;
			case 5: if (readfile(BM_KGRID6,maps[5])==NULL) goto init3d_error; break;
#endif
			}
		j=st_a1%9;
		tptr=maps[5]+((j/3)*83+2)*256+(j%3)*70+1;
		tptr2=maps[X_BM+1];
		for (i=0;i<79;i++)
			{
			memcpy(tptr2,tptr,69);
			tptr+=256;
			tptr2+=256;
			}
		switch(st_b1_kit/9)
			{
			case 0: if (readfile(BM_KGRID1,maps[5])==NULL) goto init3d_error; break;
#ifndef BBS
			case 1: if (readfile(BM_KGRID2,maps[5])==NULL) goto init3d_error; break;
			case 2: if (readfile(BM_KGRID3,maps[5])==NULL) goto init3d_error; break;
			case 3: if (readfile(BM_KGRID4,maps[5])==NULL) goto init3d_error; break;
			case 4: if (readfile(BM_KGRID5,maps[5])==NULL) goto init3d_error; break;
			case 5: if (readfile(BM_KGRID6,maps[5])==NULL) goto init3d_error; break;
#endif
			}
		j=st_b1_kit%9;
		tptr=maps[5]+((j/3)*83+2)*256+(j%3)*70+1;
		tptr2=maps[X_BM+1]+69;
		for (i=0;i<79;i++)
			{
			memcpy(tptr2,tptr,69);
			tptr+=256;
			tptr2+=256;
			}
    	if (readfile(BM_REFKPLIM,maps[5]) == NULL) goto init3d_error;

		tptr=maps[X_BM]+89*256+161;
		for (i=0;i<27;i++)
			{
			memcpy(tptr+91*256,tptr,92);
			tptr+=256;
			}
	   if (readfile(teamlist[setup.team_b_kit].nosfile,maps[X_BM]+89*256) == NULL) exit (1);
  		tptr=maps[X_BM]+116*256+161;
		for (i=0;i<27;i++)
			{
			memcpy(tptr+64*256-92,tptr,92);
			tptr+=256;
			}
    	if (readfile(stadlist[setup.stadium].pitchfile,maps[X_BM]+116*256) == NULL) exit (1);
		tptr=maps[X_BM]+180*256+69;
		for (i=0;i<27;i++)
			{
			memcpy(tptr-64*256,tptr,184);
			tptr+=256;
			}
    	if (readfile(BM_EXTRA2,maps[X_BM]+180*256) == NULL) exit (1);
		if (
			readfile(stadlist[setup.stadium].tmdfile,(BYTE *)&textures[S_TM]) == NULL ||
		 	readfile(stadlist[setup.stadium].s1pfile,(BYTE *)&stad1_p) == NULL ||
		 	readfile(stadlist[setup.stadium].s1ffile,(BYTE *)&stad1_f) == NULL ||
		 	readfile(stadlist[setup.stadium].s2pfile,(BYTE *)&stad2_p) == NULL ||
	 	 	readfile(stadlist[setup.stadium].s2ffile,(BYTE *)&stad2_f) == NULL ||
		 	readfile(stadlist[setup.stadium].s3pfile,(BYTE *)&stad3_p) == NULL ||
		 	readfile(stadlist[setup.stadium].s3ffile,(BYTE *)&stad3_f) == NULL ||
		 	readfile(stadlist[setup.stadium].s4pfile,(BYTE *)&stad4_p) == NULL ||
		 	readfile(stadlist[setup.stadium].s4ffile,(BYTE *)&stad4_f) == NULL
			)
 			goto init3d_error;
		if (
			readfile(MP4_AFOOTB,(BYTE *)&player_p[mcaps[MC_AFOOTB].cappts]) == NULL ||
	    	readfile(MP4_AFOOTC,(BYTE *)&player_p[mcaps[MC_AFOOTC].cappts]) == NULL ||
	    	readfile(MP4_ABODYB,(BYTE *)&player_p[mcaps[MC_ABODYB].cappts]) == NULL ||
	    	readfile(MP4_ABODYC,(BYTE *)&player_p[mcaps[MC_ABODYC].cappts]) == NULL ||
	    	readfile(MP4_AHEADB,(BYTE *)&player_p[mcaps[MC_AHEADB].cappts]) == NULL ||
	    	readfile(MP4_AHEADC,(BYTE *)&player_p[mcaps[MC_AHEADC].cappts]) == NULL ||
	    	readfile(MP4_AJUMPB,(BYTE *)&player_p[mcaps[MC_AJUMPB].cappts]) == NULL ||
	    	readfile(MP4_AJUMPC,(BYTE *)&player_p[mcaps[MC_AJUMPC].cappts]) == NULL ||
	    	readfile(MP4_BFOOTB,(BYTE *)&player_p[mcaps[MC_BFOOTBL].cappts]) == NULL ||
	    	readfile(MP4_BFOOTC,(BYTE *)&player_p[mcaps[MC_BFOOTCL].cappts]) == NULL ||
	    	readfile(MP4_BBODYB,(BYTE *)&player_p[mcaps[MC_BBODYBL].cappts]) == NULL ||
	    	readfile(MP4_BBODYC,(BYTE *)&player_p[mcaps[MC_BBODYCL].cappts]) == NULL ||
	    	readfile(MP4_BHEADB,(BYTE *)&player_p[mcaps[MC_BHEADBL].cappts]) == NULL ||
	    	readfile(MP4_BHEADC,(BYTE *)&player_p[mcaps[MC_BHEADCL].cappts]) == NULL ||
	    	readfile(MP4_BJUMPB,(BYTE *)&player_p[mcaps[MC_BJUMPBL].cappts]) == NULL ||
	    	readfile(MP4_CFOOTB,(BYTE *)&player_p[mcaps[MC_CFOOTBL].cappts]) == NULL || 
	    	readfile(MP4_CFOOTC,(BYTE *)&player_p[mcaps[MC_CFOOTCL].cappts]) == NULL || 
	    	readfile(MP4_CBODYB,(BYTE *)&player_p[mcaps[MC_CBODYBL].cappts]) == NULL ||
	    	readfile(MP4_CBODYC,(BYTE *)&player_p[mcaps[MC_CBODYCL].cappts]) == NULL ||
	    	readfile(MP4_CHEADB,(BYTE *)&player_p[mcaps[MC_CHEADBL].cappts]) == NULL ||
	    	readfile(MP4_CJUMPB,(BYTE *)&player_p[mcaps[MC_CJUMPBL].cappts]) == NULL || 
	    	readfile(MP4_SHOOT1,(BYTE *)&player_p[mcaps[MC_SHOOTR].cappts]) == NULL ||
	    	readfile(MP4_CHIP1,(BYTE *)&player_p[mcaps[MC_CHIPR].cappts]) == NULL ||
	    	readfile(MP4_SPASS1,(BYTE *)&player_p[mcaps[MC_PASSR].cappts]) == NULL ||
	    	readfile(MP4_CROSS1,(BYTE *)&player_p[mcaps[MC_CROSSR].cappts]) == NULL ||
	    	readfile(MP4_VOLLEY,(BYTE *)&player_p[mcaps[MC_VOLLEYR].cappts]) == NULL ||
//	    	readfile(MP4_TOE2,(BYTE *)&player_p[mcaps[MC_TOER].cappts]) == NULL ||
	    	readfile(MP4_DIAGPASS,(BYTE *)&player_p[mcaps[MC_DIAGPASSR].cappts]) == NULL ||
	    	readfile(MP4_DIAGBACK,(BYTE *)&player_p[mcaps[MC_DIAGBACKR].cappts]) == NULL ||
	    	readfile(MP4_SIDEPASS,(BYTE *)&player_p[mcaps[MC_SIDEPASSR].cappts]) == NULL ||
	    	readfile(MP4_BACKHEEL,(BYTE *)&player_p[mcaps[MC_BACKHEELR].cappts]) == NULL ||
	    	readfile(MP4_SVTOSTD,(BYTE *)&player_p[mcaps[MC_STOSL].cappts]) == NULL ||
	    	readfile(MP4_SVTOSTB,(BYTE *)&player_p[mcaps[MC_STOSBL].cappts]) == NULL ||
	    	readfile(MP4_TRAP,(BYTE *)&player_p[mcaps[MC_TRAPR].cappts]) == NULL ||
			readfile(MP4_RIDE4,(BYTE *)&player_p[mcaps[MC_RIDEL].cappts]) == NULL ||
	    	readfile(MP4_SOCKS2,(BYTE *)&player_p[mcaps[MC_SOCKSR].cappts]) == NULL ||
			readfile(MP4_TROTB,(BYTE *)&player_p[mcaps[MC_TROTB].cappts]) == NULL ||
			readfile(MP4_TROTG,(BYTE *)&player_p[mcaps[MC_TROTG].cappts]) == NULL ||
	    	readfile(MP4_TROTD1,(BYTE *)&player_p[mcaps[MC_TROTD].cappts]) == NULL ||
	    	readfile(MP4_TROTA,(BYTE *)&player_p[mcaps[MC_TROTA].cappts]) == NULL ||
	    	readfile(MP4_TROTE,(BYTE *)&player_p[mcaps[MC_TROTE].cappts]) == NULL ||
	    	readfile(MP4_RUN2,(BYTE *)&player_p[mcaps[MC_RUN].cappts]) == NULL ||
	    	readfile(MP4_JOG1,(BYTE *)&player_p[mcaps[MC_JOG].cappts]) == NULL ||
	    	readfile(MP4_BARGE,(BYTE *)&player_p[mcaps[MC_BARGE].cappts]) == NULL ||
	    	readfile(MP4_THROWW,(BYTE *)&player_p[mcaps[MC_THROWW].cappts]) == NULL ||
//	    	readfile(MP4_SHAMEW,(BYTE *)&player_p[mcaps[MC_SHAMEW].cappts]) == NULL ||
//	    	readfile(MP4_LIE1,(BYTE *)&player_p[mcaps[MC_LIE].cappts]) == NULL ||
			readfile(MP4_STAND1,(BYTE *)&player_p[mcaps[MC_STAND].cappts]) == NULL  ||
	    	readfile(MP4_SHEADER,(BYTE *)&player_p[mcaps[MC_S_HEAD].cappts]) == NULL ||
	    	readfile(MP4_JHEADER,(BYTE *)&player_p[mcaps[MC_J_HEAD].cappts]) == NULL ||
	    	readfile(MP4_HDOWN1,(BYTE *)&player_p[mcaps[MC_D_HEAD].cappts]) == NULL ||
//	    	readfile(MP4_HEADUP,(BYTE *)&player_p[mcaps[MC_U_HEAD].cappts]) == NULL ||
	    	readfile(MP4_DHEADER,(BYTE *)&player_p[mcaps[MC_DV_HEAD].cappts]) == NULL ||
	    	readfile(MP4_CHEST1,(BYTE *)&player_p[mcaps[MC_CHEST].cappts]) == NULL ||
			readfile(MP4_STACKLE,(BYTE *)&player_p[mcaps[MC_S_TACKLE].cappts]) == NULL ||
			readfile(MP4_STEAL2,(BYTE *)&player_p[mcaps[MC_STEAL].cappts]) == NULL ||
	    	readfile(MP4_OVERHEAD,(BYTE *)&player_p[mcaps[MC_OVERHEAD].cappts]) == NULL ||
			readfile(MP4_THROWL,(BYTE *)&player_p[mcaps[MC_THROWL].cappts]) == NULL ||
	    	readfile(MP4_THROWS,(BYTE *)&player_p[mcaps[MC_THROWS].cappts]) == NULL ||
	    	readfile(MP4_FALLR,(BYTE *)&player_p[mcaps[MC_FALLR].cappts]) == NULL ||
//	    	readfile(MP4_FALLS,(BYTE *)&player_p[mcaps[MC_FALLS].cappts]) == NULL ||
	    	readfile(MP4_CELEB,(BYTE *)&player_p[mcaps[MC_CELEB].cappts]) == NULL ||
//	    	readfile(MP4_SHAME1,(BYTE *)&player_p[mcaps[MC_SHAME].cappts]) == NULL ||
	    	readfile(MP4_GETUP,(BYTE *)&player_p[mcaps[MC_GETUP].cappts]) == NULL ||
	    	readfile(MP4_GETUPF,(BYTE *)&player_p[mcaps[MC_GETUPF].cappts]) == NULL ||
			readfile(MP4_STANDB,(BYTE *)&player_p[mcaps[MC_STANDB].cappts]) == NULL ||
	    	readfile(MP4_BOUNCE,(BYTE *)&player_p[mcaps[MC_BOUNCE].cappts]) == NULL ||
	    	readfile(MP4_KICKOUT,(BYTE *)&player_p[mcaps[MC_KICKOUT].cappts]) == NULL ||
	    	readfile(MP4_HALFVOLL,(BYTE *)&player_p[mcaps[MC_HALFVOLL].cappts]) == NULL ||
	    	readfile(MP4_THROW,(BYTE *)&player_p[mcaps[MC_THROW].cappts]) == NULL ||
	    	readfile(MP4_ROLL,(BYTE *)&player_p[mcaps[MC_ROLL].cappts]) == NULL || 
	    	readfile(MP4_RUNWITHB,(BYTE *)&player_p[mcaps[MC_RUNWITHB].cappts]) == NULL || 
	    	readfile(MP4_WAVEUP,(BYTE *)&player_p[mcaps[MC_WAVEUP].cappts]) == NULL || 
//	    	readfile(MP4_PENALTY,(BYTE *)&player_p[mcaps[MC_PENALTY].cappts]) == NULL ||
//	    	readfile(MP4_PLEAD,(BYTE *)&player_p[mcaps[MC_PLEAD].cappts]) == NULL ||
	    	readfile(MP4_CRTOSTB1,(BYTE *)&player_p[mcaps[MC_CRTOSTB].cappts]) == NULL ||
	    	readfile(MP4_PICKBALL,(BYTE *)&player_p[mcaps[MC_PICKBALL].cappts]) == NULL
			)
 			goto init3d_error;
		}
	closedatafile();


	// Making simple pitch
	st_w=stadlist[setup.stadium].st_w;
	st_l=stadlist[setup.stadium].st_l;
	st_h=stadlist[setup.stadium].st_h;
	for (i=0;i<19;i++)
		{
		pitch_p[1+i*3+2]=st_w;
		pitch_p[1+(i+19)*3+2]=-800-st_w;
		}
	pitch_p[1]=-st_l;
	pitch_p[1+19*3]=-st_l;
	pitch_p[1+18*3]=1280+st_l;
	pitch_p[1+37*3]=1280+st_l;

								 
	// Remapping textures
	if (setup.verbose) {puts("Remapping textures...");fflush(stdout);}
	tlptr=(dword *)&textures[0];
	for (i=0;i<(NOTEXTURES+1)*8;i++) *tlptr++&=0xffffff00; // Correct unchecked carry in texture mapping (not a bug!)
	tptr=maps[0]+128*256;
	for (i=0;i<128*256;i++)
		{
		if (*tptr>=80 && *tptr<88) *tptr+=8;
		tptr++;
		}
	tptr=maps[2];
	for (i=0;i<65536;i++)
		{
		if (*tptr>=32 && *tptr<56) *tptr+=24;
		if (*tptr>=80 && *tptr<88) *tptr+=8;
		tptr++;
		}
	tptr=maps[3]+80*256;
	for (i=0;i<80*256;i++)
		{
		if (*tptr>=32 && *tptr<56) *tptr+=24;
		if (*tptr>=80 && *tptr<88) *tptr+=8;
		tptr++;
		}
	tptr=maps[X_BM]+89*256;
	for (i=0;i<27*256;i++)
		{
		if (*tptr>32 && *tptr<=56) *tptr+=24;
		if (*tptr>80 && *tptr<=88) *tptr+=8;
		tptr++;
		}
	tptr=maps[X_BM]+116*256+69;
	for (i=0;i<27;i++)
		{
		for (j=0;j<92;j++)
			{
			if (*tptr>32 && *tptr<=56) *tptr+=24;
			if (*tptr>80 && *tptr<=88) *tptr+=8;
			tptr++;
			}
		tptr+=164;
		}
	if (setup.M8)
		{
		tptr=maps[S_BM+2];
		for (i=0;i<65536;i++)
			{
			if (*tptr>=80 && *tptr<88) *tptr+=16;
			tptr++;
			}
		tptr=maps[S_BM+3];
		for (i=0;i<65536;i++)
			{
			if (*tptr>=32 && *tptr<56) *tptr+=24;
			if (*tptr>=80 && *tptr<88) *tptr+=16;
			tptr++;
			}
		tptr=maps[S_BM+4];
		for (i=0;i<(78*256);i++)
			{
			if (*tptr>=80 && *tptr<88) *tptr+=16;
			tptr++;
			}
		tptr=maps[S_BM+4]+80*256;
		for (i=0;i<(78*256);i++)
			{
			if (*tptr>=32 && *tptr<56) *tptr+=24;
			if (*tptr>=80 && *tptr<88) *tptr+=16;
			tptr++;
			}
		tptr=maps[S_BM+5];
		for (i=0;i<2*65536;i++)
			{
			if (*tptr>=80 && *tptr<88) *tptr+=8;
			tptr++;
			}
		}


  	// Screen dump (640X400)
	if (EUROmatch_info.tga_enable&&setup.M8) 
		{
		if ((dumplbm=readrawfile("hires.tga",NULL)) == NULL) exit (1);
		for (i=0;i<256;i++)
			{
			*(dumplbm+0x12+i*3)=pal[i*3+2]<<2;
			*(dumplbm+0x12+i*3+1)=pal[i*3+1]<<2;
			*(dumplbm+0x12+i*3+2)=pal[i*3]<<2;
			}
		}


	// Prepare segment selectors for texture maps
	if (setup.verbose) {puts("Preparing segment selectors...");fflush(stdout);}
//	if ((selector=getselectors(mappages+stadlist[setup.stadium].noloop+2)) < 0)
	if ((selector=getselectors(mappages+noloop+2)) < 0)
		{
		puts("Error preparing selectors");
		goto init3d_error;
		}
	for (i=0;i<mappages;i++)
		{
		mapsel[i]=selector;
		seg=maps[i];
		if (setselector(selector,seg,65536) < 0)
			{
			puts("Error setting selectors");
			goto init3d_error;
			}
		selector+=nextselectordisp(selector);
		}

	for (i=mappages;i<mappages+noloop;i++)
		{
		mapsel[i]=selector;
		seg=maps[X_BM+(texloop[i-mappages].pos>>16)]+(texloop[i-mappages].pos&0xffff);
		if (setselector(selector,seg,65536) < 0)
			{
			puts("Error setting selectors");
			goto init3d_error;
			}
		selector+=nextselectordisp(selector);
		}
	/*
	for (i=mappages;i<mappages+stadlist[setup.stadium].noloop;i++)
		{
		mapsel[i]=selector;
		seg=maps[S_BM+(stadlist[setup.stadium].loop[i-mappages]>>16)]+(stadlist[setup.stadium].loop[i-mappages]&0xffff);
		if (setselector(selector,seg,65536) < 0)
			{
			puts("Error setting selectors");
			goto init3d_error;
			}
		selector+=nextselectordisp(selector);
		}
	*/
  	mapsel[i]=selector;
  	seg=maps[X_BM]+148*256+64;
  	if (setselector(selector,seg,65536) < 0)
  		{
  		puts("Error setting selectors");
		goto init3d_error;
  		}
	selector+=nextselectordisp(selector);
  	mapsel[i+1]=selector;
  	seg=maps[X_BM]+116*256;
  	if (setselector(selector,seg,65536) < 0)
  		{
  		puts("Error setting selectors");
		goto init3d_error;
  		}

	// Free memory?
	if (setup.verbose) {printf("Free memory = %d\n",get_mem_info());fflush(stdout);}
	
	// Prepare filters
	if (setup.verbose) {puts("Making colour filters...");fflush(stdout);}
	makefilter(filters[0],0,0,0,0.5,0.5,0.5);
	makefilter(filters[1],48,48,48,.5,.5,.5);


	// Initialise objects
	if (setup.verbose) {puts("Intialising data objects...");fflush(stdout);}

	// Set players  
	for (i=0;i<11;i++)	
		initobj(&player[i],player_p[0],player_f1,0,0,0,1,0);
										            
	for (i=11;i<22;i++)
		initobj(&player[i],player_p[0],player_f2,0,0,0,1,0);

	initobj(&player[22],player_p[0],player_fr,0,0,0,1,0);
	initobj(&player[23],player_p[0],player_fl,0,0,0,1,0);
	initobj(&player[24],player_p[0],player_fl,0,0,0,1,0);

	// Prepare player tweening
	for (i=0;i<NPLAYERS;i++)
		{
		plyrtwtb[i].anim=MC_STAND;
		plyrtwtb[i].tween=-1;
		plyrtwtb[i].twnfrm=player[0].points;
		*plyrtwtb[i].twnpts1=*plyrtwtb[i].twnpts2=PLYRPTS;
		}

	// Set player shadows/highlights
	initobj(&plhilight[0][0],plshad_p,plshad_f,0,0,0,1,0);
	initobj(&plhilight[1][0],plhi_p,plhi1_f1,0,0,0,1,0);
	initobj(&plhilight[2][0],plhi_p,plhi2_f1,0,0,0,1,0);
	initobj(&plhilight[3][0],plhi_p,plhi3_f1,0,0,0,1,0);
	initobj(&plhilight[4][0],plhi_p,plhi3_f1,0,0,0,1,0);
	initobj(&plhilight[5][0],plhi_p,plhi4_f1,0,0,0,1,0);
	initobj(&plhilight[6][0],plhi_p,plhi4_f1,0,0,0,1,0);
	initobj(&plhilight[0][1],plshad_p,plshad_f,0,0,0,1,0);
	initobj(&plhilight[1][1],plhi_p,plhi1_f2,0,0,0,1,0);
	initobj(&plhilight[2][1],plhi_p,plhi2_f2,0,0,0,1,0);
	initobj(&plhilight[3][1],plhi_p,plhi3_f2,0,0,0,1,0);
	initobj(&plhilight[4][1],plhi_p,plhi3_f2,0,0,0,1,0);
	initobj(&plhilight[5][1],plhi_p,plhi4_f2,0,0,0,1,0);
	initobj(&plhilight[6][1],plhi_p,plhi4_f2,0,0,0,1,0);
	initobj(&plhilight[0][2],plshad_p,plshad_f,0,0,0,1,0);
	initobj(&plhilight[1][2],plhi_p,plhi1_f3,0,0,0,1,0);
	initobj(&plhilight[2][2],plhi_p,plhi2_f3,0,0,0,1,0);
	initobj(&plhilight[3][2],plhi_p,plhi3_f3,0,0,0,1,0);
	initobj(&plhilight[4][2],plhi_p,plhi3_f3,0,0,0,1,0);
	initobj(&plhilight[5][2],plhi_p,plhi4_f3,0,0,0,1,0);
	initobj(&plhilight[6][2],plhi_p,plhi4_f3,0,0,0,1,0);
	initobj(&plhilight[0][3],plshad_p,plshad_f,0,0,0,1,0);
	initobj(&plhilight[1][3],plhi_p,plhi1_f4,0,0,0,1,0);
	initobj(&plhilight[2][3],plhi_p,plhi2_f4,0,0,0,1,0);
	initobj(&plhilight[3][3],plhi_p,plhi3_f4,0,0,0,1,0);
	initobj(&plhilight[4][3],plhi_p,plhi3_f4,0,0,0,1,0);
	initobj(&plhilight[5][3],plhi_p,plhi4_f4,0,0,0,1,0);
	initobj(&plhilight[6][3],plhi_p,plhi4_f4,0,0,0,1,0);
	initobj(&plhilight[0][4],plshad_p,plshad_f,0,0,0,1,0);
	initobj(&plhilight[1][4],plhi_p,plhi1_f5,0,0,0,1,0);
	initobj(&plhilight[2][4],plhi_p,plhi2_f5,0,0,0,1,0);
	initobj(&plhilight[3][4],plhi_p,plhi3_f5,0,0,0,1,0);
	initobj(&plhilight[4][4],plhi_p,plhi3_f5,0,0,0,1,0);
	initobj(&plhilight[5][4],plhi_p,plhi4_f5,0,0,0,1,0);
	initobj(&plhilight[6][4],plhi_p,plhi4_f5,0,0,0,1,0);
	initobj(&plhilight[0][5],plshad_p,plshad_f,0,0,0,1,0);
	initobj(&plhilight[1][5],plhi_p,plhi1_ff,0,0,0,1,0);
	initobj(&plhilight[2][5],plhi_p,plhi2_ff,0,0,0,1,0);
	initobj(&plhilight[3][5],plhi_p,plhi3_ff,0,0,0,1,0);
	initobj(&plhilight[4][5],plhi_p,plhi3_ff,0,0,0,1,0);
	initobj(&plhilight[5][5],plhi_p,plhi4_ff,0,0,0,1,0);
	initobj(&plhilight[6][5],plhi_p,plhi4_ff,0,0,0,1,0);

	// Set ball
	initobj(&ball,footy_p,footy_f,640,0,-400,1,0);

	// Set ball shadow 
	initobj(&ballshad,ballshad_p,ballshad_f,640,0,-400,1,0);

	// Set simple pitch
	initobj(&pitch,pitch_p,pitch_f,0,0,0,1,0);
	
	// Set pitch lines
	initobj(&l1,l1_p1,l_f1a,210,0,-200,1,0);
	initobj(&l2,l2_p1,l_f1a,1070,0,-200,1,0);
	initobj(&l3,l3_p1,l_f1a,1070,0,-600,1,0);
	initobj(&l4,l4_p1,l_f1a,210,0,-600,1,0);
	initobj(&l5,l5_p1,l_f3a,640,0,-200,1,0);
	initobj(&l6,l6_p1,l_f3a,640,0,-600,1,0);
	initobj(&circle,circle_pa,circle_fa,640,0,-400,1,0);
	initobj(&semi1,s_circle_p1a,s_circle_f1a,123,0,-400,1,0);
	initobj(&semi2,s_circle_p2a,s_circle_f2a,1157,0,-400,1,0);
	initobj(&spot1,spot_p,spot_f,640,0,-400,1,0);
	initobj(&spot2,spot_p,spot_f,128,0,-400,1,0);
	initobj(&spot3,spot_p,spot_f,1152,0,-400,1,0);

	// Set goals
	initobj(&goal1_1,goal1a_p,goal_f1a,0,0,-443.5,1,0);
	initobj(&goal2_1,goal1a_p,goal_f1a,0,0,-356.5,1,0);
	initobj(&goal3_1,goal1a_p,goal_f1a,0,37,-400,1,0);
	initobj(&goal4_1,goal1a_p,goal_f1a,-28,0,-400,1,0);
	initobj(&goal1_2,goal1a_p,goal_f1a,1280,0,-443.5,1,0);
	initobj(&goal2_2,goal1a_p,goal_f1a,1280,0,-356.5,1,0);
	initobj(&goal3_2,goal1a_p,goal_f1a,1280,37,-400,1,0);
	initobj(&goal4_2,goal1a_p,goal_f1a,1308,0,-400,1,0);

	// Set flags
	initobj(&flag_1,flag_p,flag_f,0,0,0,1,0);
	initobj(&flag_2,flag_p,flag_f,1280,0,0,1,0);
	initobj(&flag_3,flag_p,flag_f,0,0,-800,1,0);
	initobj(&flag_4,flag_p,flag_f,1280,0,-800,1,0);

	// Set stands
	initobj(&stad1,stad1_p,stad1_f, stadlist[setup.stadium].s1x,stadlist[setup.stadium].s1y,stadlist[setup.stadium].s1z,1,0);
	initobj(&stad2,stad2_p,stad2_f, stadlist[setup.stadium].s2x,stadlist[setup.stadium].s2y,stadlist[setup.stadium].s2z,1,0);
	initobj(&stad3,stad3_p,stad3_f, stadlist[setup.stadium].s3x,stadlist[setup.stadium].s3y,stadlist[setup.stadium].s3z,1,0);
	initobj(&stad4,stad4_p,stad4_f, stadlist[setup.stadium].s4x,stadlist[setup.stadium].s4y,stadlist[setup.stadium].s4z,1,0);
	stp=stad1_f;
	i=*stp++;
	for(;i;i--)
	{
		j=*stp++;
		if (*stp<0) *stp-=S_TM-1;
		stp++;
		for (;j;j--) stp++;
	}
	stp=stad2_f;
	i=*stp++;
	for(;i;i--)
	{
		j=*stp++;
		if (*stp<0) *stp-=S_TM-1;
		stp++;
		for (;j;j--) stp++;
	}
	stp=stad3_f;
	i=*stp++;
	for(;i;i--)
	{
		j=*stp++;
		if (*stp<0) *stp-=S_TM-1;
		stp++;
		for (;j;j--) stp++;
	}
	stp=stad4_f;
	i=*stp++;
	for(;i;i--)
	{
		j=*stp++;
		if (*stp<0) *stp-=S_TM-1;
		stp++;
		for (;j;j--) stp++;
	}

	// Initialise animations
	buff_ptr=(char *)(maps[S_BM])+stadlist[setup.stadium].vmap;
	vidi_anim=0;
	vidi_in=0;
  	if (readrawfile(fapoffs,(BYTE *)load_offsets) == NULL) goto init3d_error;
	if (opendatafile(fapfile) < 0) goto init3d_error;
	if (setup.M8) 
		{
#ifdef JAPAN
		readfile(FAP_VIJAP,(BYTE *)anim_data);
#else
#ifdef AMERICA
		readfile(FAP_VR,(BYTE *)anim_data);
#else
		readfile(FAP_VIDI,(BYTE *)anim_data);
#endif
#endif
		init_anim(vidi,0);
		}
#ifdef AMERICA
	readfile(COL_VR,(BYTE *)&pal[240*3]);
#endif


	// Prepare miscellaneous data
	if (setup.verbose) {puts("Preparing miscellaneous data...");fflush(stdout);}
	

	// Set screen mode and set buffer info
	if (setup.verbose) {puts("Geting VESA information...");fflush(stdout);}
//	MCGA_buff.buff_start=(BYTE *)0xa0000;
	for (i=0;i<SCRSIZES;i++)
		{
		MCGA_buff[i].buff_start=scrb+320+((320-MCGA_buff[i].clip_wid)>>1)+((200-MCGA_buff[i].clip_hgt)>>1)*320;
		for (j=0;j<VESAMODES;j++)
			VESA_buff[j][i].buff_start=scrb+640+((VESA_buff[j][i].buff_wid-VESA_buff[j][i].clip_wid)>>1)+((VESA_buff[j][i].buff_hgt-VESA_buff[j][i].clip_hgt)>>1)*VESA_buff[j][i].buff_wid;
		}
	for (i=0;i<MODES_3DB;i++)
 		buff_3DB[i].buff_start=scrb;
	if (setup.stadium>=90)
		{
		vidi_buff_1.buff_start=maps[S_BM]+7*256+10;
		vidi_buff_2.buff_start=maps[S_BM]+7*256+10;
		}
	else
		{
		vidi_buff_1.buff_start=maps[S_BM]+14*256+51;
		vidi_buff_2.buff_start=maps[S_BM]+14*256+51;
		}
	if (setup.vidi_type==0)
		vidi_buff=vidi_buff_1;
	else
		vidi_buff=vidi_buff_2;
	for (i=0;i<NO_MENUS;i++)
		{
		menu_buff_l[i].scale_x=(MCGA_buff[0].clip_wid-menu_buff_l[i].clip_wid)>>1;
		menu_buff_l[i].scale_y=MCGA_buff[0].clip_hgt-menu_buff_l[i].buff_hgt;
		menu_buff_l[i].buff_start=MCGA_buff[0].buff_start+(int)menu_buff_l[i].scale_y*MCGA_buff[0].buff_wid+(int)menu_buff_l[i].scale_x;
		menu_buff_h[i].scale_x=(VESA_buff[0][0].clip_wid-menu_buff_h[i].clip_wid)>>1;
		menu_buff_h[i].scale_y=VESA_buff[0][0].clip_hgt-menu_buff_h[i].buff_hgt;
		menu_buff_h[i].buff_start=VESA_buff[0][0].buff_start+(int)menu_buff_h[i].scale_y*VESA_buff[0][0].buff_wid+(int)menu_buff_h[i].scale_x;
		}

	return (0);

	init3d_error:;
	end3d();
	return (-1);

	}


void
setscreen()
	{
	int i,j,k,pf;
	int taddr,taddr1;

#ifdef BLASTER
	if ((scrmode3DB=Init3DB(modelist3DB))<0)
#else
	if (1)
#endif
		{
		init3DB_error:;
		scrmode3DB=-1;
		remapgfx(1);
		if (setup.start_res==0)
			{
			scrmode=0x13;
			VGAmode(scrmode);
			main_buff=MCGA_buff[setup.screen_size];
			}
		else
			{
			testVESA=0;
			scrmode=VESAmode(&modelist[0]);
			switch(scrmode)
				{
				case 0x100:main_buff=VESA_buff[0][setup.screen_size];break;
				case 0x101:main_buff=VESA_buff[1][setup.screen_size];break;
				default:VGAmode(0x13);main_buff=MCGA_buff[setup.screen_size];scrmode=0x13;
				}
			}

		setup.start_res=(scrmode==0x13)?0:1;

		// Set palette
		setpal();

		// Clear screen
		switch(scrmode)
			{
			case 0x13:
				vclear(scrb+320,320,200,320,5);
				mcgacpy(scrb+320,0,0,320,200,320);
				break;
			case 0x100:
				vclear(scrb+640,640,400,640,5);
				svgacpy(scrb+640,0,0,640,400,640);
				break;
			case 0x101:
				vclear(scrb+640,640,480,640,5);
				svgacpy(scrb+640,0,0,640,480,640);
				break;
			}
		}
#ifdef BLASTER
	else
		{
  		if (readrawfile(dataoffs,(BYTE *)load_offsets) == NULL) goto init3DB_error;
		if (opendatafile(datafile) < 0 ) goto init3DB_error;
		switch(stadlist[setup.stadium].pitchfile)
			{
			case BM_PA: pf=BM_PT1;break;
			case BM_PB: pf=BM_PT2;break;
			case BM_PC: pf=BM_PT3;break;
			case BM_PD: pf=BM_PT4;break;
			}
		if (
	    	readfile(skylist[skyno].skypfile3DB,&pal[3*208]) == NULL ||
	   	readfile(skylist[skyno].skyfile3DB,sky) == NULL ||
    		readfile(pf,pitch3DB) == NULL
			)
			goto init3DB_error;
		closedatafile();
#ifdef BLASTDEMO
		scrmode=(setup.start_res=(scrmode3DB>1)?1:0)?0x100:0x13;
#else
		scrmode=(setup.start_res=(scrmode3DB>0)?1:0)?0x100:0x13;
#endif
		main_buff=buff_3DB[scrmode3DB];
		pal[3]=pal[4]=pal[5]=63;
		pal[191*3]=pal[191*3+1]=pal[191*3+2]=0;
		SetPalette3DB(pal);

		// Load 3D Blaster textures
		remapxgfx(-1);
		for (i=0;i<mappages;i+=4)
			{
#ifdef RENDITION
			MapAddress3DB=i*64;
#else
			MapAddress3DB=-i*64;
#endif
			for (j=0;j<4&&(i+j)!=mappages;j++)
				{
				taddr=MapAddress3DB;
				if ((texaddr3DB[i+j]=LoadTexture3DB((char *)maps[i+j],1024,256,256))<0)
					goto init3DB_error;
				MapAddress3DB=taddr+1024*256;
				}
			}
//		MapAddress3DB=1024*1024;
		if ((skyaddr3DB=LoadTexture3DB((char *)sky,512,512,128))<0)
			goto init3DB_error;
		MapAddress3DB=1024*1024+128*512;
		if ((pitchaddr3DB=LoadTexture3DB((char *)pitch3DB,64,64,64))<0)
			goto init3DB_error;
		}
#endif
	}


void end3d()
	{
	int i;
	closedatafile();
	for (i=0;i<mappages+noloop+2;i++)
		{
		if (mapsel[i]!=-1)
			if (freeselector(mapsel[i]) < 0)
				{
				puts("Error freeing selectors");
//				exit(1);
				}
		}
	if (EUROmatch_info.tga_enable&&setup.M8) freex(dumplbm);
	if (setup.M8) freex(anim_data);
	freex(rotlist);
	freex(ptslist);
	freex(pollist);
	freex(objlist);
	freex(plyrtwtb);
	freex(player_p);
	freex(filters);
	freex(textures);
	if (setup.M8) freex(sky);
	freex(scrb);
	freex(maps);

	if (scrmode3DB>=0)
		Close3DB();

	}



/****************/
/* TIME MACHINE */

void __far timetest(void) {performance++;};

/*
int timing()
	{
	float t;
	int c=0;

	performance=0;
	sosTIMERInitSystem(_TIMER_DOS_RATE,_SOS_DEBUG_NORMAL);
	sosTIMERRegisterEvent(100,timetest,&TimerHandle);

	for (i=0;i<100000;i++)
		{
		t=sin(c++);
		*(char *)0xa0000=(char)t;
		}

	sosTIMERRemoveEvent(TimerHandle);
	sosTIMERUnInitSystem(0);
	performance=2000/performance;
	}
*/


int timing()
	{
	int i,j;
	word selector;
	BYTE *seg;
	word *stp;
	plyrdat *plyrwr,plyr[NPLAYERS+2];
	unsigned int TimerHandle;
	datapt dp[1]={0};

	timeit=1;

	setup.M8=0;
	setup.team_a=0;
	setup.team_b=setup.team_b_kit=1;
	setup.stadium=45;
	setup.vidi_type=0;
	setup.start_res=0;
	setup.screen_size=0;
	setup.detail.stadia=1;
	setup.detail.pitch=1;
	setup.detail.lines=1;
	setup.detail.sky=1;
	setup.detail.players=1;
	setup.detail.shadows=1;

	if (
		 (maps=(mappage *)mallocx((mappages=MAPPAGES_4)*65536)) == NULL ||
		 (scrb=(BYTE *)mallocx(320*202)) == NULL ||
		 (textures=(texture *)mallocx((NOTEXTURES+CLIP_TEXTURES+1)*sizeof(texture))) == NULL ||
		 (filters=(filter *)mallocx(FILTERS*sizeof(filter))) == NULL ||
		 (player_p=(capfrm *)mallocx(100*sizeof(capfrm))) == NULL ||
		 (plyrtwtb=(plyrtwdat *)mallocx(NPLAYERS*sizeof(plyrtwdat))) == NULL ||
		 (objlist=(objs *)mallocx(MAXOBJ*sizeof(objs))) == NULL ||
		 (pollist=(pols *)mallocx(MAXPOL*sizeof(pols))) == NULL ||
		 (ptslist=(scrpt *)mallocx(MAXPOL*10*sizeof(scrpt))) == NULL ||
		 (rotlist=(rotpt *)mallocx(MAXPTS*4*sizeof(rotpt))) == NULL )
		{
		puts("Error reserving memory");
		exit(-1);
		}
	mcaps=mcaps4;

	if (readrawfile(dataoffs,(BYTE *)load_offsets) == NULL)	exit(1);
	if (opendatafile(datafile)<0) return(-1);

	if (readfile(TMD_TEXDATA,(BYTE *)&textures[1]) == NULL) exit(1);
	if (
		readfile(stadlist[setup.stadium].tmdfile,(BYTE *)&textures[S_TM]) == NULL ||
	 	readfile(stadlist[setup.stadium].s1pfile,(BYTE *)&stad1_p) == NULL ||
	 	readfile(stadlist[setup.stadium].s1ffile,(BYTE *)&stad1_f) == NULL ||
	 	readfile(stadlist[setup.stadium].s2pfile,(BYTE *)&stad2_p) == NULL ||
	 	readfile(stadlist[setup.stadium].s2ffile,(BYTE *)&stad2_f) == NULL ||
	 	readfile(stadlist[setup.stadium].s3pfile,(BYTE *)&stad3_p) == NULL ||
	 	readfile(stadlist[setup.stadium].s3ffile,(BYTE *)&stad3_f) == NULL ||
	 	readfile(stadlist[setup.stadium].s4pfile,(BYTE *)&stad4_p) == NULL ||
	 	readfile(stadlist[setup.stadium].s4ffile,(BYTE *)&stad4_f) == NULL
		)
		exit(1);
	if (readfile(MP4_STAND1,(BYTE *)&player_p[0]) == NULL) exit(1);
	closedatafile();

	// Prepare segment selectors for texture maps
	if ((selector=getselectors(mappages+noloop+2)) < 0)
		{
		puts("Error preparing selectors");
		exit(2);
		}
	for (i=0;i<mappages;i++)
		{
		mapsel[i]=selector;
		seg=maps[i];
		if (setselector(selector,seg,65536) < 0)
			{
			puts("Error setting selectors");
			exit(3);
			}
		selector+=nextselectordisp(selector);
		}

	for (i=mappages;i<mappages+noloop;i++)
		{
		mapsel[i]=selector;
		seg=maps[X_BM+(texloop[i-mappages].pos>>16)]+(texloop[i-mappages].pos&0xffff);
		if (setselector(selector,seg,65536) < 0)
			{
			puts("Error setting selectors");
			exit(3);
			}
		selector+=nextselectordisp(selector);
		}
  	mapsel[i]=selector;
  	seg=maps[X_BM]+148*256+64;
  	if (setselector(selector,seg,65536) < 0)
  		{
  		puts("Error setting selectors");
  		exit(3);
  		}
	selector+=nextselectordisp(selector);
  	mapsel[i+1]=selector;
  	seg=maps[X_BM]+116*256;
  	if (setselector(selector,seg,65536) < 0)
  		{
  		puts("Error setting selectors");
  		exit(3);
  		}

	// Prepare filters
	makefilter(filters[0],0,0,0,0.5,0.5,0.5);
	makefilter(filters[1],48,48,48,.5,.5,.5);


	// Initialise objects
	// Set players  
	for (i=0;i<11;i++)	
		initobj(&player[i],player_p[0],player_f1,0,0,0,1,0);
										            
	for (i=11;i<22;i++)
		initobj(&player[i],player_p[0],player_f2,0,0,0,1,0);

	initobj(&player[22],player_p[0],player_fr,0,0,0,1,0);
	initobj(&player[23],player_p[0],player_fl,0,0,0,1,0);
	initobj(&player[24],player_p[0],player_fl,0,0,0,1,0);

	// Prepare player tweening
	for (i=0;i<NPLAYERS;i++)
		{
		plyrtwtb[i].anim=0;
		plyrtwtb[i].tween=-1;
		plyrtwtb[i].twnfrm=player[0].points;
		*plyrtwtb[i].twnpts1=*plyrtwtb[i].twnpts2=PLYRPTS;
		}

	// Set player shadows/highlights
	initobj(&plhilight[0][0],plshad_p,plshad_f,0,0,0,1,0);
	initobj(&plhilight[1][0],plhi_p,plhi1_f1,0,0,0,1,0);
	initobj(&plhilight[2][0],plhi_p,plhi2_f1,0,0,0,1,0);
	initobj(&plhilight[3][0],plhi_p,plhi3_f1,0,0,0,1,0);
	initobj(&plhilight[4][0],plhi_p,plhi3_f1,0,0,0,1,0);
	initobj(&plhilight[5][0],plhi_p,plhi4_f1,0,0,0,1,0);
	initobj(&plhilight[0][1],plshad_p,plshad_f,0,0,0,1,0);
	initobj(&plhilight[1][1],plhi_p,plhi1_f2,0,0,0,1,0);
	initobj(&plhilight[2][1],plhi_p,plhi2_f2,0,0,0,1,0);
	initobj(&plhilight[3][1],plhi_p,plhi3_f2,0,0,0,1,0);
	initobj(&plhilight[4][1],plhi_p,plhi3_f2,0,0,0,1,0);
	initobj(&plhilight[5][1],plhi_p,plhi4_f2,0,0,0,1,0);
	initobj(&plhilight[0][2],plshad_p,plshad_f,0,0,0,1,0);
	initobj(&plhilight[1][2],plhi_p,plhi1_f3,0,0,0,1,0);
	initobj(&plhilight[2][2],plhi_p,plhi2_f3,0,0,0,1,0);
	initobj(&plhilight[3][2],plhi_p,plhi3_f3,0,0,0,1,0);
	initobj(&plhilight[4][2],plhi_p,plhi3_f3,0,0,0,1,0);
	initobj(&plhilight[5][2],plhi_p,plhi4_f3,0,0,0,1,0);
	initobj(&plhilight[0][3],plshad_p,plshad_f,0,0,0,1,0);
	initobj(&plhilight[1][3],plhi_p,plhi1_f4,0,0,0,1,0);
	initobj(&plhilight[2][3],plhi_p,plhi2_f4,0,0,0,1,0);
	initobj(&plhilight[3][3],plhi_p,plhi3_f4,0,0,0,1,0);
	initobj(&plhilight[4][3],plhi_p,plhi3_f4,0,0,0,1,0);
	initobj(&plhilight[5][3],plhi_p,plhi4_f4,0,0,0,1,0);
	initobj(&plhilight[0][4],plshad_p,plshad_f,0,0,0,1,0);
	initobj(&plhilight[1][4],plhi_p,plhi1_f5,0,0,0,1,0);
	initobj(&plhilight[2][4],plhi_p,plhi2_f5,0,0,0,1,0);
	initobj(&plhilight[3][4],plhi_p,plhi3_f5,0,0,0,1,0);
	initobj(&plhilight[4][4],plhi_p,plhi3_f5,0,0,0,1,0);
	initobj(&plhilight[5][4],plhi_p,plhi4_f5,0,0,0,1,0);
	initobj(&plhilight[0][5],plshad_p,plshad_f,0,0,0,1,0);
	initobj(&plhilight[1][5],plhi_p,plhi1_ff,0,0,0,1,0);
	initobj(&plhilight[2][5],plhi_p,plhi2_ff,0,0,0,1,0);
	initobj(&plhilight[3][5],plhi_p,plhi3_ff,0,0,0,1,0);
	initobj(&plhilight[4][5],plhi_p,plhi3_ff,0,0,0,1,0);
	initobj(&plhilight[5][5],plhi_p,plhi4_ff,0,0,0,1,0);

	// Set ball
	initobj(&ball,footy_p,footy_f,640,0,-400,1,0);

	// Set ball shadow 
	initobj(&ballshad,ballshad_p,ballshad_f,640,0,-400,1,0);
	
	// Set pitch lines
	initobj(&l1,l1_p1,l_f1a,210,0,-200,1,0);
	initobj(&l2,l2_p1,l_f1a,1070,0,-200,1,0);
	initobj(&l3,l3_p1,l_f1a,1070,0,-600,1,0);
	initobj(&l4,l4_p1,l_f1a,210,0,-600,1,0);
	initobj(&l5,l5_p1,l_f3a,640,0,-200,1,0);
	initobj(&l6,l6_p1,l_f3a,640,0,-600,1,0);
	initobj(&circle,circle_pa,circle_fa,640,0,-400,1,0);
	initobj(&semi1,s_circle_p1a,s_circle_f1a,123,0,-400,1,0);
	initobj(&semi2,s_circle_p2a,s_circle_f2a,1157,0,-400,1,0);
	initobj(&spot1,spot_p,spot_f,640,0,-400,1,0);
	initobj(&spot2,spot_p,spot_f,128,0,-400,1,0);
	initobj(&spot3,spot_p,spot_f,1152,0,-400,1,0);

	// Set goals
	initobj(&goal1_1,goal1a_p,goal_f1a,0,0,-443.5,1,0);
	initobj(&goal2_1,goal1a_p,goal_f1a,0,0,-356.5,1,0);
	initobj(&goal3_1,goal1a_p,goal_f1a,0,37,-400,1,0);
	initobj(&goal4_1,goal1a_p,goal_f1a,-28,0,-400,1,0);
	initobj(&goal1_2,goal1a_p,goal_f1a,1280,0,-443.5,1,0);
	initobj(&goal2_2,goal1a_p,goal_f1a,1280,0,-356.5,1,0);
	initobj(&goal3_2,goal1a_p,goal_f1a,1280,37,-400,1,0);
	initobj(&goal4_2,goal1a_p,goal_f1a,1308,0,-400,1,0);

	// Set flags
	initobj(&flag_1,flag_p,flag_f,0,0,0,1,0);
	initobj(&flag_2,flag_p,flag_f,1280,0,0,1,0);
	initobj(&flag_3,flag_p,flag_f,0,0,-800,1,0);
	initobj(&flag_4,flag_p,flag_f,1280,0,-800,1,0);

	// Set stands
	initobj(&stad1,stad1_p,stad1_f, stadlist[setup.stadium].s1x,stadlist[setup.stadium].s1y,stadlist[setup.stadium].s1z,1,0);
	initobj(&stad2,stad2_p,stad2_f, stadlist[setup.stadium].s2x,stadlist[setup.stadium].s2y,stadlist[setup.stadium].s2z,1,0);
	initobj(&stad3,stad3_p,stad3_f, stadlist[setup.stadium].s3x,stadlist[setup.stadium].s3y,stadlist[setup.stadium].s3z,1,0);
	initobj(&stad4,stad4_p,stad4_f, stadlist[setup.stadium].s4x,stadlist[setup.stadium].s4y,stadlist[setup.stadium].s4z,1,0);
	stp=stad1_f;
	i=*stp++;
	for(;i;i--)
	{
		j=*stp++;
		if (*stp<0) *stp-=S_TM-1;
		stp++;
		for (;j;j--) stp++;
	}
	stp=stad2_f;
	i=*stp++;
	for(;i;i--)
	{
		j=*stp++;
		if (*stp<0) *stp-=S_TM-1;
		stp++;
		for (;j;j--) stp++;
	}
	stp=stad3_f;
	i=*stp++;
	for(;i;i--)
	{
		j=*stp++;
		if (*stp<0) *stp-=S_TM-1;
		stp++;
		for (;j;j--) stp++;
	}
	stp=stad4_f;
	i=*stp++;
	for(;i;i--)
	{
		j=*stp++;
		if (*stp<0) *stp-=S_TM-1;
		stp++;
		for (;j;j--) stp++;
	}

	MCGA_buff[0].buff_start=scrb+320+((320-MCGA_buff[0].clip_wid)>>1)+((200-MCGA_buff[0].clip_hgt)>>1)*320;
	scrmode=0x13;
	scrmode3DB=-1;
	VGAmode(scrmode);
	main_buff=MCGA_buff[0];
	for (i=0;i<768;i++) pal[i]=0;
	setpal();

	plyrwr=plyr;            
	for (i=0;i<11;i++)
		{
		plyrwr->x=640;
		plyrwr->y=0;
		plyrwr->z=400;
		plyrwr->type=1;
		plyrwr->number=i+1;
		plyrwr->htype=plyrwr->hcol=0;
		plyrwr->crot=1;
		plyrwr->srot=0;
		plyrwr->anim=0;
		plyrwr->frame=0;
		plyrwr->fstep=0.5;
		plyrwr->sprite=-1;
		plyrwr++;
		}

	for (i=0;i<11;i++)
		{
		plyrwr->x=640;
		plyrwr->y=0;
		plyrwr->z=400;
		plyrwr->type=2;
		plyrwr->number=i+1;
		plyrwr->htype=plyrwr->hcol=0;
		plyrwr->crot=1;
		plyrwr->srot=0;
		plyrwr->anim=0;
		plyrwr->frame=0;
		plyrwr->fstep=0.5;
		plyrwr->sprite=-1;
		plyrwr++;
		}

	plyrwr->x=640;
	plyrwr->y=0;
	plyrwr->z=400;
	plyrwr->type=3;
	plyrwr->number=i+1;
	plyrwr->htype=plyrwr->hcol=0;
	plyrwr->crot=1;
	plyrwr->srot=0;
	plyrwr->anim=0;
	plyrwr->frame=0;
	plyrwr->fstep=0.5;
	plyrwr->sprite=-1;
	plyrwr++;

	for (i=0;i<2;i++)
		{
		plyrwr->x=640;
		plyrwr->y=0;
		plyrwr->z=400;
		plyrwr->type=4;
		plyrwr->number=i+1;
		plyrwr->htype=plyrwr->hcol=0;
		plyrwr->crot=1;
		plyrwr->srot=0;
		plyrwr->anim=0;
		plyrwr->frame=0;
		plyrwr->fstep=0.5;
		plyrwr->sprite=-1;
		plyrwr++;
		}

	plyrwr->x=640;
	plyrwr->y=20;
	plyrwr->z=400;
 	plyrwr->crot=1;
 	plyrwr->srot=0;
 	plyrwr->frame=1;
 	plyrwr->fstep=0;
	plyrwr->sprite=-1;
	plyrwr++;

	performance=0;
	sosTIMERInitSystem(_TIMER_DOS_RATE,_SOS_DEBUG_NORMAL);
	sosTIMERRegisterEvent(100,timetest,&TimerHandle);

	for (i=0;i<20;i++)
		{
		render3d(&main_buff,0,20,0,1280,20,800,256,plyr,dp,NULL);
		main_buff.dump(0,0);
		}

	sosTIMERRemoveEvent(TimerHandle);
	sosTIMERUnInitSystem(0);
	performance=2000/performance;

	for (i=0;i<mappages+noloop+2;i++)
		{
		if (freeselector(mapsel[i]) < 0)
			{
			puts("Error freeing selectors");
			exit(3);
			}
		}

	freex(rotlist);
	freex(ptslist);
	freex(pollist);
	freex(objlist);
	freex(plyrtwtb);
	freex(player_p);
	freex(filters);
	freex(textures);
	freex(sky);
	freex(scrb);
	freex(maps);

	timeit=0;

//	return (performance);
	return (31);
	}



/****************/
/* JUGGLING MAN */

float balla;
float balld;
float ballly;
float ballld;
int jno;

void drawman(buff_info *buffer, float anim, float angle, int dist)
	{
	datapt targx,targy,targz,viewx,viewy,viewz,vdist;

	short i,j;
	objs *oldobj;
	double hr,r;
	mat tmp;

	targx=targz=0;
	targy=10;
	viewx=dist*cos(angle);
	viewy=40;
	viewz=dist*sin(angle);
	vdist=buffer->buff_wid;

	// Set extended buffer info
	render_buff.buff_start=buffer->buff_start;
	render_buff.buff_wid=buffer->buff_wid;
	render_buff.buff_hgt=buffer->buff_hgt;
	render_buff.clip_wid=buffer->clip_wid;
	render_buff.clip_hgt=buffer->clip_hgt;
	render_buff.scale_x=buffer->scale_x;
	render_buff.scale_y=buffer->scale_y;
	render_buff.dump=buffer->dump;
	render_buff.clip_endl=buffer->buff_start+buffer->clip_hgt*buffer->buff_wid;
	render_buff.clip_end=render_buff.clip_endl-buffer->buff_wid;
	render_buff.clip_widl=buffer->clip_wid-1;
	render_buff.clip_hgtl=buffer->clip_hgt-1;
	render_buff.clip_xmid=buffer->clip_wid>>1;
	render_buff.clip_ymid=buffer->clip_hgt>>1;

	// Set perspective based info
	oq=vdist;
	q=vdist*((buffer->scale_x+buffer->scale_y)/2);
	qr=(floatpt)1/q; 
	qa=(floatpt)q*2/100;
	scrdr=(float)1/SCREENDIST;
	persc=q*scrdr;

	// Prepare viewing vector vars
	viewz=-viewz,targz=-targz;
	targx-=viewx;
	targy-=viewy;
	targz-=viewz;

	hr=targx*targx+targz*targz;
	if (hr<1) hr=1,targz=1;
	r=sqrt(hr+targy*targy);
	hr=sqrt(hr);
	cth=targz/hr;sth=targx/hr;
	cph=hr/r;sph=targy/r;

	// Make global rotation matrix
	matcop(rot.arr,unit);
	matcop(tran.arr,unit);
	matcop(tmp,unit);
	rot.arr[0][3]=-viewx;
	rot.arr[1][3]=-viewy;
  	rot.arr[2][3]=-viewz;
	tmp[0][0]=cth;
	tmp[0][2]=-sth;				             
	tmp[1][0]=-sth*sph;
	tmp[1][1]=cph;
	tmp[1][2]=-cth*sph;
	tmp[2][0]=sth*cph;			 
	tmp[2][1]=sph;
	tmp[2][2]=cth*cph;
	matmul(rot.arr,tmp);

	clearlists

	player[0].points=player_p[(short)(anim*jno)];
	oldobj=curobj;
	addobjy(&player[0]);
	if (oldobj!=curobj) sortobj(oldobj);

	ball.y=-player[0].points[1+23*3];
	ball.z=player[0].points[1+23*3+2];
	ball.x=-ball.y*player[0].crot+ball.z*player[0].srot+player[0].x;
	ball.z=ball.y*player[0].srot+ball.z*player[0].crot+player[0].z;
	ball.y=player[0].points[1+23*3+1]+player[0].y;
	addobjxy(&ball,cos(balla),sin(balla));

	if (anim<0.88)
		{
		balla+=balld;
		balld*=0.89;
		if (ball.y-ballly>0 && ballld<=0) balld+=0.16;
		ballld=ball.y-ballly;
		ballly=ball.y;
		}

	dispols();

	}

int initman(int team, int capture)
	{
	int i,nheadfile;
	word selector;
	BYTE *seg;
	BYTE *tptr;

	if ( (maps=(mappage *)mallocx((mappages=4)*65536)) == NULL ) goto err1;
	if ( (textures=(texture *)mallocx(600*sizeof(texture))) == NULL ) goto err2;
	if ( (player_p=(capfrm *)mallocx(300*sizeof(capfrm))) == NULL ) goto err3;
	if ( (objlist=(objs *)mallocx(5*sizeof(objs))) == NULL ) goto err4;
	if ( (pollist=(pols *)mallocx(60*sizeof(pols))) == NULL ) goto err5;
	if ( (ptslist=(scrpt *)mallocx(400*10*sizeof(scrpt))) == NULL ) goto err6;
	if ( (rotlist=(rotpt *)mallocx(200*4*sizeof(rotpt))) == NULL ) goto err7;

  	if (readrawfile(dataoffs,(BYTE *)load_offsets) == NULL) goto err8;
	if (opendatafile(datafile)<0) return(-1);

#ifndef BBS
	if (teamlist[team].headfile==BM_XCAUCASB || teamlist[team].headfile==BM_XNORDIC)
		nheadfile=BM_XCAUCASA;
	else
#endif
		nheadfile=teamlist[team].headfile;

	if (
		readfile(TMD_MANDATA,(BYTE *)&textures[1]) == NULL ||
	   readfile(PAL_FOOTY,pal) == NULL ||
	   readfile(nheadfile,maps[0]) == NULL ||
	   readfile(teamlist[team].torsofile,maps[1]) == NULL ||
	   readfile(teamlist[team].limbsfile,maps[3]) == NULL ||
	   readfile(BM_FEET,maps[3]+158*256) == NULL ||
	   readfile(teamlist[team].palfile,&pal[3*32]) == NULL ||
	  	readfile(teamlist[team].skinfile,&pal[3*80]) == NULL
		)
		goto err8;
	switch(capture)
		{
		case 0:
			if (readfile(MPB_JUGGLE,(BYTE *)&player_p[0]) == NULL) goto err8;
			jno=300;
			break;
		case 1:
			if (readfile(MPB_CELEB,(BYTE *)&player_p[0]) == NULL) goto err8;
			jno=118;
			break;
		}
	closedatafile();

	tptr=maps[0];
	for (i=0;i<4*65536;i++) ++(*tptr++);

	if ((selector=getselectors(mappages)) < 0)
		{
		puts("Error preparing selectors");
		goto err8;
		}
	for (i=0;i<mappages;i++)
		{
		mapsel[i]=selector;
		seg=maps[i];
		if (setselector(selector,seg,65536) < 0)
			{
			puts("Error setting selectors");
			goto err9;
			}
		selector+=nextselectordisp(selector);
		}

	initobj(&player[0],player_p[0],player_f1,0,0,0,1,0);
	player[0].faces[0]=12;
	initobj(&ball,footy_p,footy_f,0,0,0,1,0);

	balla=0;
	balld=0;
	ballly=0;
	ballld=0;

//	setpal();
//	testVESA=0;
//	scrmode=VESAmode(&modelist[0]);
	return (0);

	err9:;
	for (i=0;i<mappages;i++)
		freeselector(mapsel[i]);
	err8:;
	freex(rotlist);
	err7:;
	freex(ptslist);
	err6:;
	freex(pollist);
	err5:;
	freex(objlist);
	err4:;
	freex(player_p);
	err3:;
	freex(textures);
	err2:;
	freex(maps);
	err1:;
	return (-1);

	}


void endman()
	{
	int i;
	for (i=0;i<mappages;i++)
		{
		if (freeselector(mapsel[i]) < 0)
			{
			puts("Error freeing selectors");
			exit(3);
			}
		}
	freex(rotlist);
	freex(ptslist);
	freex(pollist);
	freex(objlist);
	freex(player_p);
	freex(textures);
	freex(maps);
	}



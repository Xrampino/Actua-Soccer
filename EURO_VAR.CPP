#include <string.h>
#include "eurodefs.h"
#include "euro_fxd.h"
#include "euro_sym.h"
#include "euro_def.h"

#define	WIP	1

#ifndef WIP
	char		*EuroDATfile		=	"..\\data\\euro.dat";
	char		*EuroOFFSETfile		=	"..\\data\\euro.off";
	char		*EuroSCRIPTfile		=	"..\\script\\script.96";
#else	
	char		*EuroDATfile		=	"euro.dat";
	char		*EuroOFFSETfile		=	"euro.off";
	char		*EuroSCRIPTfile		=	"script.96";
#endif

	char		version;
	char		sub_verion;
	char		day;
	char		month;
	short		year; 
	char		EUROsymbol;
	int		EUROerror		=	0;
	char		EUROverbose		=	0;
	char		EUROfrontend		=	0;
	char		EUROconsole		=	0;

	char		*EuroGDVfile		=	"..\\makegdv\\wembley.gdv";
	volatile	char	LogicState;
	unsigned int 	EuroHandle;
	BYTE 		*EuroPseudoBuffer;
	BYTE		*EuroBackgroundBuffer;
	char		TexturePagesAvailable	=	0;
	BYTE		*TexturePages;
	BYTE		*TexturePageMemHandle;
	BYTE		*TextStrings;
	BYTE		*TextStringMemHandle;
	int		Image_Xcoords[4096];
	int		Image_Ycoords[4096];
	int		Image_Widths[4096];
	int		Image_Heights[4096];
	char		Image_Pages[4096];
	BYTE		*Text[2048];
	BYTE		*Clubnames[16*20];
	BYTE		*SPEECH_identifier[16*20];
	char		PlayerPosns[16*20];
 	char		StarPlayers[3*16];
 	char		LinkPlayers[11*16];
	char		DOBday[16*20];
	char		DOBmonth[16*20];
	char		DOByear[16*20];
	char		NamePREFIXtbl[16*20];

	offset_defn	Offset_table[512];

	texture_info 	FrontendTextureDEFN	=	{ NULL, 640, 480 };
	pseudo_info 	FrontendBackgroundDEFN	=	{ NULL, 640, 480, 640, 480 };
	pseudo_info 	FrontendPseudoDEFN	=	{ NULL, 640, 480, 640, 480 };
	slider_info	ModemSelectDEFN		=	{ 0, 427, 338, 436, 446, 0, 6 };

	char 		StringBuffer[NAME_BUFFER_LEN+1];
	char		Templete[128];
	char 		BuildBuffer[128];
	char		EUROammount[5];

	char		KeyInput[2];
	char		TextEditBuffer[256];
	short		TextEditXposn		=	0;	
 	char		EuroTextEditState	=	0;

        BYTE 		PaletteBuffer[768];

        BYTE 		FilterBuffer[256*8];

        BYTE 		SparePaletteBuffer[768];
        fixed		DivisionTable[768];
        fixed		CurrentPalette[768];
	fixed 		FadeCounter = 0;
	char 		svalue;
	unsigned char	pmin, pmax;
	BYTE 		*ftable;

	char		Team;
	char		Menu;
	signed char	MarkPlayer;
	signed char	ViewPlyrStats;
	signed short 	SquadBuffer1yposn;
	float		EuroReDrawCounter;
	signed	char 	EuroReDrawFlag;

	int		TeamTactics[(32*2)+6][10][2];

	box_info	Bounding_table[ (MAX_BOUNDING_BOXES+1) ];
	signed char  	Bounding_box;
	signed char	ClickBOX;
	dump_info	Dump_list[ (MAX_DUMPS+1) ];
	animation_info	Animation_table[ (MAX_ANIMATIONS+1) ];

	short		QuestionHandle;
	short		EuroDrawHandle;
	short		RedrawHandle;
	short		GrpFixHandle;
	short		FormationHandle;
	short		TeamHandle;
	short		PlayerSetupHandle;
	short		TeamSelectHandle;
	short		TeamSetupHandle;
	short		ReturnSqdHandle;
	short		ReturnStatHandle;
	short		ViewTeamHandle;
	short		ReturnTeamHandle;
	short		NetSelectionHandle;
	short		NetStartHandle;
	short		StartMatchHandle;
	short		UserSelectTeamHandle;
	short		StartEuro96Handle;
	short		NoOfUsersHandle;
	short 		DefaultHandle;
	short		NextMatchHandle;
	short		SpinningCupHandle;
	short		SelectTeamsHandle;

	char		UserHighlight;
	char		SelectHighlight;
	char		RedrawHighlight;
	char		RedrawdoneHighlight;
	char		DefaultdrawHighlight;
	char		TeamSelectHighlight;
	char		StartMatchHighlight;
	char		TeamSetupHighlight;
	char		PlyrSetupHighlight;
	char		RetnTstatHighlight;
	char		NextMatchHighlight;
	char  		SelectTeamsHighlight;
	char		NetStartHighlight;

	char		OVERRIDEpal1;
	char		OVERRIDEpal2;

	short		VersusLength;
	float		SelectionCounter;
	float		SelectionSpeed;
	signed char 	SelectionFlag;
	signed int 	SelectionAim;
	signed char	SelectDir;


	fixed		SelectFrame;

	fixed		CursorDisplaySpeed;

	char		EuroVideoStatus;
	int		EUROvideoMode[2]={
			0x0101,
			-1,	  };

	short		SelectFilterTBL[32]=
		{ 1792, 1536, 1280, 1024, 768, 512, 256, 0,
		  0, 0, 0, 0, 0, 256, 256, 512, 512, 768, 768, 1024,
		  1024, 1280, 1280, 1536, 1536, 1792, 1792,
		  1792,1792,1792,1792,1792,};

  	Coord_info	LeaguePosnDEFN[16]=	
		{ 33,  139,
		  33,  161,
		  33,  183,
		  33,  205,
		  284, 139,
		  284, 161,	
		  284, 183,
		  284, 205,
		  33,  331,								
		  33,  353,
		  33,  375,
		  33,  397,
		  284, 331,
		  284, 353,
		  284, 375,
		  284, 397,
		 };

  	Coord_info	WinPosnDEFN[16]	=
		{ 144, 139,
		  144, 161,
		  144, 183,
		  144, 205,
		  395, 139,
		  395, 161,	
		  395, 183,
		  395, 205,
		  144, 331,								
		  144, 353,
		  144, 375,
		  144, 397,
		  395, 331,
		  395, 353,
		  395, 375,
		  395, 397,
		 };

  	Coord_info	DrawPosnDEFN[16] =
		{ 173, 139,
		  173, 161,
		  173, 183,
		  173, 205,
		  424, 139,
		  424, 161,	
		  424, 183,
		  424, 205,
		  173, 331,								
		  173, 353,
		  173, 375,
		  173, 397,
		  424, 331,
		  424, 353,
		  424, 375,
		  424, 397,
		 };

  	Coord_info	LosePosnDEFN[16] =
		{ 202, 139,
		  202, 161,
		  202, 183,
		  202, 205,
		  453, 139,
		  453, 161,	
		  453, 183,
		  453, 205,
		  202, 331,								
		  202, 353,
		  202, 375,
		  202, 397,
		  453, 331,
		  453, 353,
		  453, 375,
		  453, 397,
		 };

  	Coord_info	PointsPosnDEFN[16] =
		{ 231, 139,
		  231, 161,
		  231, 183,
		  231, 205,
		  482, 139,
		  482, 161,	
		  482, 183,
		  482, 205,
		  231, 331,								
		  231, 353,
		  231, 375,
		  231, 397,
		  482, 331,
		  482, 353,
		  482, 375,
		  482, 397,
		 };

  	Coord_info	VersusPosnDEFN[16] =
		{ 138, 227,
		  138, 249,
		  138, 419,
		  138, 441,
		  389, 227,
		  389, 249,	
		  389, 419,
		  389, 441,
		 };


  	Coord_info	ReDrawPosnDEFN[16] =
		{ 47+84,  224,
		  259+84, 224,
		  47+84,  415,
		  259+84, 415,
		  47+84,  199, 
		  259+84, 199,	
		  47+84,  390,
		  259+84, 390,
		  47+84,  173,								
		  259+84, 173,
		  47+84,  364,
		  259+84, 364,
		  47+84,  148,
		  259+84, 148,
		  47+84,  339,
		  259+84, 339,
		 };

  	Coord_info	ReDrawHeadPosnDEFN[4] =
		{ 47+84,  143-24,
		  259+84, 143-24,
		  47+84,  334-24,
		  259+84, 334-24,
		 };

  	Coord_info	QualifierHeadPosnDEFN[4] =
		{ 64,  133,
		  64,  221,
		  64,  309,
		  64,  398,
		 };

  	Coord_info	CountryOutlinePosnDEFN[16] =	
		{ 185, 239,
		  188, 220,
		  177, 227,
		  187, 232,
		  181, 222,
		  180, 233,
		  203, 220,
		  179, 234,
		  186, 222,
		  186, 221,
		  193, 222,
		  190, 222,
		  184, 223,
		  185, 241,
		  204, 222,
		  179, 238,
		};								   	


  	Coord_info	TSTATCountryPosnDEFN[16] =
		{ 422, 13,   	// bulgaria
	 	  428, 11,	// croatia
	 	  419, 27,	// czech	     
	 	  486, 5,	// denmark
	 	  485, 1,	// england						
	 	  438, 4,	// france
	 	  477, 2,	// germany
	 	  471, 6,	// holland
	 	  448, 1,	// italy
	 	  504, 6,	// portugal
	 	  432, 7,	// romania
	 	  398, 9,	// russia
	 	  458, 7,	// scotland
	 	  445, 24,	// spain
	 	  417, 19,	// switzerland
	 	  402, 26,	// turkey
	 	};								   	


  	TeamSel_Info	CountryImageDEFN[8*64]	=
		{  0,   133-88,	219,				// 0
		   1,	184-88,	201,				// 1			  
		   2,	203-88,	278,				// 2			  
		   3,	276-88, 216,				// 3
		   4,	375-88,	219,				// 4
		   5,	462-88,	214,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7

		   6,	132-88,	217,		// 1		// 0
		   7,	204-88,	200,				// 1
		   8,	304-88,	215,				// 2
		   9,	398-88,	220,				// 3
		   10,	473-88, 216,				// 4
		  -1,	NULL,	NULL,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7
	
		  11,	132-88,	214,		// 2		// 0
		  12,	226-88,	199,				// 1
		  13,	330-88,	216,				// 2
		  14,	419-88,	219,				// 3
		  -1,	NULL,	NULL,				// 4
		  -1,	NULL,	NULL,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7

		  15,	132-88,	212,		// 3		// 0
		  16,	251-88,	198,				// 1
		  17,	356-88,	216,				// 2
		  18,	465-88,	221,				// 3
		  -1,	NULL,	NULL,				// 4
		  -1,	NULL,	NULL,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7

		  19,	132-88,	210,		// 4		// 0
		  20,	246-88,	247,				// 1
		  21,	279-88,	198,				// 2
		  22,	381-88,	217,				// 3
		  23,	486-88,	223,				// 4
		  -1,	NULL,	NULL,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7
							    
		  24,	133-88,	219,		// 5		// 0
		  25,	198-88,	208,				// 1
		  26,	306-88,	199,				// 2
		  27,	404-88,	218,				// 3
		  -1,	NULL,	NULL,				// 4
		  -1,	NULL,	NULL,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7
							    
		  28,	132-88,	217,		// 6		// 0
		  29,	217-88,	207,				// 1
		  30,	296-88,	241,				// 2
		  31,	332-88,	200,				// 3
		  32,	424-88,	219,				// 4
		  -1,	NULL,	NULL,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7

		  33,	130-88,	214,		// 7		// 0
		  34,	169-88,	216,				// 1
		  35,	242-88,	206,				// 2
		  36,	358-88,	201,				// 3
		  37,	442-88,	221,				// 4
		  -1,	NULL,	NULL,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7

		  38,	131-88,	212,		// 8		// 0
		  39,	184-88,	214,				// 1
		  40,	268-88,	205,				// 2
		  41,	326-88,	269,				// 3
		  42,	383-88,	203,				// 4
		  43,	457-88,	223,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7

		  44,	132-88,	209,		// 9		// 0
		  45,	204-88,	212,				// 1
		  46,	266-88,	218,				// 2
		  47,	295-88,	205,				// 3
		  48,	406-88,	204,				// 4
		  49,	469-88,	225,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7

		  50,	130-88,	224,		// 10		// 0
		  51,	157-88,	207,				// 1
		  52,	227-88,	211,				// 2
		  53,	321-88,	205,				// 3
		  54,	426-88,	207,				// 4
		  55,	478-88,	227,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7

		  56,	131-88,	221,		// 11		// 0
		  57,	167-88,	205,				// 1
		  58,	252-88,	210,				// 2
		  59,	348-88,	205,				// 3
		  60,	444-88,	209,				// 4
		  61,	487-88,	229,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7

		  62,	133-88,	219,		// 12		// 0
		  63,	180-88,	203,				// 1
		  64,	279-88,	209,				// 2
		  65,	372-88,	207,				// 3
		  66,	458-88,	211,				// 4
		  -1,	NULL,	NULL,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7

		  67,	132-88,	217,		// 13		// 0
		  68,	199-88,	201,				// 1
		  69,	306-88,	209,				// 2
		  70,	396-88,	208,				// 3
		  71,	470-88,	214,				// 4
		  -1,	NULL,	NULL,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7

		  72,	129-88,	216,		// 14		// 0
		  73,	158-88,	215,				// 1
		  74,	221-88,	200,				// 2
		  75,	332-88,	209,				// 3
		  76,	417-88,	210,				// 4
		  77,	477-88,	217,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7
							   
		  78,	128-88,	213,		// 15		// 0
		  79,	165-88,	213,				// 1
		  80,	246-88,	199,				// 2
		  81,	314-88,	212,				// 3
		  82,	357-88,	210,				// 4
		  83,	436-88,	212,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7

		  84,	130-88,	211,		// 16		// 0
		  85,	177-88,	212,				// 1
		  86,	272-88,	199,				// 2
		  87,	382-88,	211,				// 3
		  88,	452-88,	214,				// 4
		  -1,	NULL,	NULL,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7

		  89,	130-88,	208,		// 17		// 0
		  90,	196-88,	210,				// 1
		  91,	272-88,	245,				// 2
		  92,	300-88,	200,				// 3
		  93,	404-88,	212,				// 4
		  94,	466-88,	217,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7

		  95,	129-88,	227,		// 18		// 0
		  96,	163-88,	206,				// 1
		  97,	218-88,	209,				// 2
		  98,	291-88,	249,				// 3
		  99,	326-88,	213,				// 4
		  100,	361-88,	200,				// 5
		  101,	424-88,	214,				// 6
		  102,	477-88,	219,				// 7

		  103,	129-88,	224,		// 19		// 0
		  104,	177-88,	204,				// 1
		  105,	243-88,	209,				// 2
		  106,	352-88,	212,				// 3
		  107,	387-88,	202,				// 4
		  109,	442-88,	216,				// 6
		  -1,	NULL,	NULL,				// 7
		  -1,	NULL,	NULL,				// 7

		  110,	133-88,	222,		// 20		// 0
		  111,	195-88,	202,				// 1
		  112,	270-88,	209,				// 2
		  113,	293-88,	209,				// 3
		  114,	376-88,	203,				// 4
		  115,	457-88,	218,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7

		  116,	133-88,	220,		// 21		// 0
		  117,	183-88,	233,		// 21		// 0
		  118,	216-88,	200,				// 1
		  119,	297-88,	209,				// 2
		  120,	399-88,	205,				// 3
		  121,	470-88,	220,				// 4
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7

		  122,	132-88,	218,		// 22		// 0
		  123,	240-88,	199,				// 1
		  124,	324-88,	210,				// 2
		  125,	420-88,	207,				// 3
		  -1,	NULL,	NULL,				// 4
		  -1,	NULL,	NULL,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7

		  126,	131-88,	215,		// 23		// 0
		  127,	266-88,	198,				// 1
		  128,	308-88,	198,				// 2
		  129,	350-88,	211,				// 3
		  130,	438-88,	210,				// 4
		  -1,	NULL,	NULL,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7

		  131,	130-88,	213,		// 24		// 0
		  132,	177-88,	214,				// 1
		  133,	294-88,	197,				// 2
		  134,	375-88,	213,				// 3
		  135,	455-88,	212,				// 4
		  -1,	NULL,	NULL,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7
							    
		  136,	130-88,	210,		// 25		// 0
		  137,	161-88,	210,				// 1
		  138,	195-88,	213,				// 2
		  139,	320-88,	198,				// 3
		  140,	361-88,	198,				// 4
		  141,	399-88,	215,				// 5
		  142,	471-88,	215,				// 6
		  -1,	NULL,	NULL,				// 7
							    
		  143,	129-88,	208,		// 26		// 0
		  144,	218-88,	212,				// 1
		  145,	302-88,	240,				// 2
		  146,	346-88,	198,				// 3
		  147,	420-88,	217,				// 4
		  -1,	NULL,	NULL,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7
							    
		  148,	130-88,	212,		// 27		// 0
		  149,	168-88,	205,				// 1
		  150,	243-88,	211,				// 2
		  151,	371-88,	199,				// 3
		  152,	411-88,	199,				// 4
		  153,	438-88,	219,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7
							    
		  154,	133-88,	209,		// 28		// 0
		  155,	184-88,	203,				// 1
		  156,	270-88,	211,				// 2
		  157,	394-88,	201,				// 3
		  158,	454-88,	221,				// 4
		  -1,	NULL,	NULL,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7
							    
		  159,	133-88,	206,		// 29		// 0
		  160,	203-88,	201,				// 1
		  161,	268-88,	249,				// 2
		  162,	298-88,	211,				// 3
		  163,	298-88,	271,				// 4
		  164,	415-88,	203,				// 5
		  165,	468-88,	223,				// 6
		  -1,	NULL,	NULL,				// 7
							    
		  166,	134-88,	204,		// 30		// 0
		  167,	226-88,	200,				// 1
		  168,	262-88,	281,				// 2
		  169,	325-88,	212,				// 3
		  170,	434-88,	205,				// 4
		  171,	478-88,	225,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7
							    
		  172,	132-88,	215,		// 31		// 0
		  173,	168-88,	202,				// 1
		  174,	251-88,	199,				// 2
		  175,	293-88,	284,				// 3
		  176,	351-88,	213,				// 4
		  177,	450-88,	207,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7
							    
		  178,	132-88,	212,		// 32		// 0
		  179,	181-88,	200,				// 1
		  180,	277-88,	199,				// 2
		  181,	376-88,	214,				// 3
		  182,	463-88,	210,				// 4
		  -1,	NULL,	NULL,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7
							    
		  183,	132-88,	210,		// 33		// 0
		  184,	201-88,	199,				// 1
		  185,	240-88,	280,				// 2
		  186,	304-88,	199,				// 3
		  187,	400-88,	215,				// 4
		  188,	474-88,	213,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7
							    
		  189,	131-88,	217,		// 34		// 0
		  190,	159-88,	207,				// 1
		  191,	224-88,	198,				// 2
		  192,	330-88,	199,				// 3
		  193,	421-88,	215,				// 4
		  -1,	NULL,	NULL,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7
							    
		  194,	132-88,	214,		// 35		// 0
		  195,	174-88,	205,				// 1
		  196,	250-88,	198,				// 2
		  197,	356-88,	200,				// 3
		  198,	440-88,	218,				// 4
		  -1,	NULL,	NULL,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7
							    
		  199,	132-88,	212,		// 36		// 0
		  200,	190-88,	203,				// 1
		  201,	196-88,	277,				// 2
		  202,	277-88,	198,				// 3
		  203,	380-88,	202,				// 4
		  204,	456-88,	220,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7
							    
		  205,	134-88,	209,		// 37		// 0
		  206,	210-88,	202,				// 1
		  207,	305-88,	198,				// 2
		  208,	402-88,	204,				// 3
		  209,	469-88,	222,				// 4
		  -1,	NULL,	NULL,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7
							    
		  210,	132-88,	217,		// 38		// 0
		  211,	160-88,	207,				// 1
		  212,	160-88,	237,				// 2
		  213,	232-88,	200,				// 3
		  214,	332-88,	200,				// 4
		  215,	332-88,	250,				// 5
		  216,	422-88,	206,				// 6
		  217,	479-88,	225,				// 7
							    
		  218,	131-88,	215,		// 39		// 0
		  219,	131-88,	245,				// 1
		  220,	170-88,	204,				// 2
		  221,	258-88,	199,				// 3
		  222,	359-88,	201,				// 4
		  223,	440-88,	208,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7
							    
		  224,	132-88,	213,		// 40		// 0
		  225,	186-88,	202,				// 1
		  226,	284-88,	199,				// 2
		  227,	383-88,	203,				// 3
		  228,	455-88,	211,				// 4
		  -1,	NULL,	NULL,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7
							    
		  229,	133-88,	210,		// 41		// 0
		  230,	207-88,	201,				// 1
		  231,	207-88,	261,				// 2
		  232,	311-88,	199,				// 3
		  233,	311-88,	229,				// 4
		  234,	407-88,	205,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7
							    
		  235,	133-88,	208,		// 42		// 0
		  236,	230-88,	199,				// 1
		  237,	337-88,	199,				// 2
		  238,	337-88,	229,				// 3
		  239,	427-88,	208,				// 4
		  -1,	NULL,	NULL,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7
							    
		  240,	134-88,	222,		// 43		// 0
		  241,	169-88,	206,				// 1
		  242,	255-88,	199,				// 2
		  243,	255-88,	219,				// 3
		  244,	363-88,	200,				// 4
		  245,	445-88,	210,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7
							    
		  246,	135-88,	220,		// 44		// 0
		  247,	183-88,	204,				// 1
		  248,	282-88,	199,				// 2
		  249,	387-88,	202,				// 3
		  250,	460-88,	213,				// 4
		  -1,	NULL,	NULL,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7
							    
		  251,	134-88,	217,		// 45		// 0
		  252,	202-88,	202,				// 1
		  253,	310-88,	199,				// 2
		  254,	409-88,	204,				// 3
		  255,	473-88,	216,				// 4
		  -1,	NULL,	NULL,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7
							    
		  256,	133-88,	215,		// 46		// 0
		  257,	160-88,	225,				// 1
		  258,	224-88,	201,				// 2
		  259,	336-88,	200,				// 3
		  260,	429-88,	206,				// 4
		  261,	479-88,	218,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7
							    
		  262,	132-88,	212,		// 47		// 0
		  263,	168-88,	223,				// 1
		  264,	249-88,	200,				// 2
		  265,	362-88,	201,				// 3
		  266,	446-88,	208,				// 4
		  -1,	NULL,	NULL,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7
							    
		  267,	133-88,	210,		// 48		// 0
		  268,	183-88,	222,				// 1
		  269,	275-88,	200,				// 2
		  270,	386-88,	202,				// 3
		  271,	460-88,	211,				// 4
		  -1,	NULL,	NULL,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7
							    
		  272,	133-88,	230,		// 49		// 0
		  273,	156-88,	207,				// 1
		  274,	203-88,	221,				// 2
		  275,	302-88,	200,				// 3
		  276,	409-88,	204,				// 4
		  277,	471-88,	213,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7
							    
		  278,	131-88,	228,		// 50		// 0
		  279,	165-88,	205,				// 1
		  280,	225-88,	220,				// 2
		  281,	328-88,	201,				// 3
		  282,	429-88,	207,				// 4
		  -1,	NULL,	NULL,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7
							    
		  283,	132-88,	226,		// 51		// 0
		  284,	180-88,	203,				// 1
		  285,	249-88,	219,				// 2
		  286,	354-88,	202,				// 3
		  287,	446-88,	209,				// 4
		  -1,	NULL,	NULL,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7
							    
		  288,	133-88,	224,		// 52		// 0
		  289,	198-88,	201,				// 1
		  290,	276-88,	219,				// 2
		  291,	378-88,	204,				// 3
		  292,	460-88,	212,				// 4
		  -1,	NULL,	NULL,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7
							    
		  293,	132-88,	222,		// 53		// 0
		  294,	219-88,	200,				// 1
		  295,	303-88,	219,				// 2
		  296,	401-88,	206,				// 3
		  297,	401-88,	246,				// 4
		  298,	472-88,	214,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7
							    
		  299,	131-88,	220,		// 54		// 0
		  300,	242-88,	199,				// 1
		  301,	329-88,	219,				// 2
		  302,	422-88,	208,				// 3
		  -1,	NULL,	NULL,				// 4
		  -1,	NULL,	NULL,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7
							    
		  303,	132-88,	219,		// 55		// 0
		  304,	132-88,	277,				// 1
		  305,	268-88,	199,				// 2
		  306,	355-88,	220,				// 3
		  307,	439-88,	210,				// 4
		  -1,	NULL,	NULL,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7
							    
		  308,	133-88,	220,		// 56		// 0
		  309,	183-88,	218,				// 1
		  310,	295-88,	199,				// 2
		  311,	380-88,	221,				// 3
		  312,	457-88,	213,				// 4
		  -1,	NULL,	NULL,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7
							    
		  313,	132-88,	218,		// 57		// 0				       
		  314,	199-88,	216,				// 1
		  315,	321-88,	200,				// 2
		  316,	402-88,	222,				// 3
		  317,	467-88,	215,				// 4
		  -1,	NULL,	NULL,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7
							    
		  318,	132-88,	215,		// 58		// 0
		  319,	162-88,	221,				// 1
		  320,	219-88,	215,				// 2
		  321,	347-88,	201,				// 3
		  322,	347-88,	241,				// 4
		  323,	423-88,	218,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7
							    
		  324,	131-88,	213,		// 59		// 0
		  325,	166-88,	220,				// 1
		  326,	244-88,	215,				// 2
		  327,	371-88,	202,				// 3
		  328,	441-88,	220,				// 4
		  -1,	NULL,	NULL,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7
							    
		  329,	132-88,	210,		// 60		// 0
		  330,	183-88,	220,				// 1
		  331,	270-88,	215,				// 2
		  332,	395-88,	204,				// 3
		  333,	456-88,	223,				// 4
		  -1,	NULL,	NULL,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7
							    
		  334,	133-88,	208,		// 61		// 0
		  335,	202-88,	218,				// 1
		  336,	298-88,	215,				// 2
		  337,	416-88,	206,				// 3
		  338,	469-88,	225,				// 4
		  -1,	NULL,	NULL,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7
							    
		  339,	132-88,	205,		// 62		// 0
		  340,	224-88,	217,				// 1
		  341,	324-88,	216,				// 2
		  342,	434-88,	209,				// 3
		  343,	477-88,	227,				// 4
		  -1,	NULL,	NULL,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7
							    
		  344,	132-88,	221,		// 63		// 0
		  345,	170-88,	203,				// 1
		  346,	249-88,	217,				// 2
		  347,	350-88,	217,				// 3
		  348,	450-88,	211,				// 4
		  -1,	NULL,	NULL,				// 5
		  -1,	NULL,	NULL,				// 6
		  -1,	NULL,	NULL,				// 7

			 };


	header_info 	GroupFixtureDEFN[16]	=	
		{ 144, 112, TBLE_LBLS+Wins,
		  173, 112, TBLE_LBLS+Draws,
		  202, 112, TBLE_LBLS+Loses,
		  231, 112, TBLE_LBLS+Points,
		  395, 112, TBLE_LBLS+Wins,								
		  424, 112, TBLE_LBLS+Draws,
		  453, 112, TBLE_LBLS+Loses,
		  482, 112, TBLE_LBLS+Points,
		  144, 304, TBLE_LBLS+Wins,
		  173, 304, TBLE_LBLS+Draws,
		  202, 304, TBLE_LBLS+Loses,
		  231, 304, TBLE_LBLS+Points,
		  395, 304, TBLE_LBLS+Wins,		
		  424, 304, TBLE_LBLS+Draws,
		  453, 304, TBLE_LBLS+Loses,
		  482, 304, TBLE_LBLS+Points,
		 };

	fixture_info	Fixtures[32]		=	{ 

		TEAM_1a, TEAM_2a,   138-58, 227,   // match 1
		TEAM_1b, TEAM_2b,   389-58, 227,   // match 2
		TEAM_1c, TEAM_2c,   138-58, 419,   // match 3
		TEAM_1d, TEAM_2d,   389-58, 419,   // match 4
							    
		TEAM_3a, TEAM_4a,   138-58, 249,   // match 5
		TEAM_3b, TEAM_4b,   389-58, 249,   // match 6
		TEAM_3c, TEAM_4c,   138-58, 441,   // match 7
		TEAM_3d, TEAM_4d,   389-58, 441,   // match 8
							    
		TEAM_2b, TEAM_3b,   389-58, 227,   // match 9
		TEAM_2a, TEAM_3a,   138-58, 227,   // match 10
		TEAM_2d, TEAM_3d,   389-58, 419,   // match 11
		TEAM_2c, TEAM_3c,   138-58, 419,   // match 12
							    
		TEAM_4a, TEAM_1a,   138-58, 249,   // match 13
		TEAM_4b, TEAM_1b,   389-58, 249,   // match 14
		TEAM_4c, TEAM_1c,   138-58, 441,   // match 15
		TEAM_4d, TEAM_1d,   389-58, 441,   // match 16
							    
		TEAM_4b, TEAM_2b,   389-58, 227,   // match 17
		TEAM_3b, TEAM_1b,   389-58, 249,   // match 18
		TEAM_3a, TEAM_1a,   138-58, 249,   // match 19
		TEAM_4a, TEAM_2a,   138-58, 227,   // match 20
							    
		TEAM_4d, TEAM_2d,   389-58, 419,   // match 21
		TEAM_3d, TEAM_1d,   389-58, 441,   // match 22
		TEAM_4c, TEAM_2c,   138-58, 419,   // match 23
		TEAM_3c, TEAM_1c,   138-58, 441,   // match 24

		// Quarter Finals

		TEAM_1a, TEAM_2b,   94+40, 133+6,  // match 25
		TEAM_1b, TEAM_2a,   94+40, 221+6,  // match 26
		TEAM_1c, TEAM_2d,   94+40, 309+6,  // match 27
		TEAM_1d, TEAM_2c,   94+40, 398+6,  // match 28

		// Semi Finals

		TEAM_1q, TEAM_4q,   94+40, 133+47, // match 29
		TEAM_2q, TEAM_3q,   94+40, 221+80, // match 30

		// Final

		TEAM_1s, TEAM_2s,   94+40, 396,	   // match 31

			 };

	char	MatchVenues[32]=
		{ London,		// match 1
		  Leeds,		// match 2
		  Manchester,		// match 3
		  Sheffield,		// match 4

		  Birmingham,		// match 5
		  Newcastle,		// match 6
		  Liverpool,		// match 7
		  Nottingham,		// match 8

		  Newcastle,		// match 9
		  Birmingham,		// match 10
		  Nottingham,		// match 11
		  Liverpool,		// match 12

		  London,		// match 13
		  Leeds,		// match 14
		  Manchester,		// match 15
		  Sheffield,		// match 16

		  Newcastle,		// match 17
		  Leeds,		// match 18
		  London,		// match 19
		  Birmingham,		// match 20

		  Nottingham,		// match 21
		  Sheffield,		// match 22
		  Liverpool,		// match 23
		  Manchester,		// match 24

		// Quarter Finals
		   			
		  London,		// match 25
		  Liverpool,		// match 26
		  Manchester,		// match 27
		  Birmingham,		// match 28
		  				   
		// Semi Finals

		  Manchester,		// match 29
		  London,		// match 30

		// Final

		  London,		// match 31
		  };


	qualify_info	qualifiers[8] =
		{
		TEAM_1a,	95+40, 159+4,
		TEAM_2a,       284+40, 159+4,
		TEAM_1b,	95+40, 247+4,
		TEAM_2b,       284+40, 247+4,
		TEAM_1c,	95+40, 335+4,
		TEAM_2c,       284+40, 335+4,
		TEAM_1d,	95+40, 424+4,
		TEAM_2d,       284+40, 424+4,
		};


	char		LeaguePositions[16];

	char		GroupDrawCode[16] =
		{
		TEAM_4a,
		TEAM_4b,
		TEAM_4c,
		TEAM_4d,
												
		TEAM_3a,
		TEAM_3b,
		TEAM_3c,
		TEAM_3d,
												
		TEAM_2a,
		TEAM_2b,
		TEAM_2c,
		TEAM_2d,
					
	// SEEDED TEAMS
												
		TEAM_1a,
		TEAM_1b,
		TEAM_1c,
		TEAM_1d,
			 };
							

	char	CountryTBL[16]={
		Bulgaria, Scotland, Turkey, Spain, France, Romania, Portugal, Russia,
		Italy, Holland, Germany, England, Croatia, Czech, Denmark, Switzerland,
					};
	char	AimTBL[16]={ 0, 12, 13, 14, 11, 4, 10, 9, 8, 6, 5, 7, 1, 3, 15, 2, };

	char	CtrlFlags[16]={ 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, };

	char	PlrSetupPanelHght[5]={ 0, 0, 34, 56, 78};	

	char	PreviousEuroYearsTBL[16]={
			y1960, never, never, y1960, y1960, y1960, y1960, y1960,	
                        y1960, y1960, y1960, never, y1960, y1960, y1960, y1960 };

	
	char	PreviousEuroHistory[9*16]={
			Line01, Line01, Line02, Line01, Line01, Line01, Line01, Line01, Line01,  // Bulgaria
			Line11, Line12, Line13, Line14, Line15, Line16, Line17, Line18, Line19,	 // Croatia
			Line20, Line21, Line22, Line23, Line24, Line25, Line26, Line27, Line28,	 // Czechs
			Line01, Line03, Line01, Line01, Line01, Line01, Line04, Line06, Line05,	 // Denmark
			Line07, Line01, Line08, Line02, Line01, Line06, Line01, Line06, Line06,	 // England
			Line03, Line02, Line02, Line01, Line01, Line01, Line05, Line01, Line06,	 // France
			Line07, Line07, Line01, Line05, Line09, Line05, Line06, Line04, Line09,	 // Germany
			Line07, Line01, Line01, Line01, Line08, Line06, Line01, Line05, Line04,	 // Holland
			Line07, Line01, Line05, Line02, Line01, Line03, Line01, Line04, Line01,	 // Italy
			Line02, Line01, Line01, Line01, Line01, Line01, Line04, Line01, Line01,	 // Portugal					  
			Line02, Line01, Line01, Line02, Line01, Line01, Line06, Line01, Line01,	 // Romania
			Line29, Line30, Line31, Line32, Line33, Line34, Line35, Line36, Line37,	 // Russia
			Line07, Line01, Line01, Line01, Line01, Line01, Line01, Line01, Line06,	 // Scotland
			Line02, Line05, Line02, Line01, Line02, Line06, Line09, Line06, Line01,	 // Spain
			Line07, Line01, Line01, Line01, Line01, Line01, Line01, Line01, Line01,	 // Switzerland
			Line01, Line01, Line01, Line01, Line01, Line01, Line01, Line01, Line01,	 // Turkey
				};



	int		MouseDriverInstalled;
	char		EUROmaxPlayers;
	char		EUROplyrSetup;
	char		EUROteamView;
	char		EUROstatTeam;
	char		EUROuserSelection;		// player to choose his team 0 - 15
	euro_info	EURO96setup[16];		// one entry per country.
	signed char	GroupVenues[4];
	int		NextXposn;
	char		RunMatch;	
	char		EUROmatchUsers;

	// ---> Frontend Vars to be linked with main game <---

	unsigned char	EUROcamera		=	CAMwire;
	short		EUROaudio		=	0;
	int		EUROcrowd		=	0;
	int		EUROpitch		=	0;
	int		EUROcommentary		=	0;
	int		EUROmusic		=	0;
	int		EUROmaster		=	0;
	short		EUROtimeit		=	0;
	short		EUROvidi		=	0;
	char		EUROoffside		=	Off;
	char		EUROsubs		=	Off;
	char		EUROfouls		=	On;
	char		EUROtime		=	TIME_5mins;
	char		EURObookings		=	On;
	char		EUROwind		=	Off;
	char		EUROref_vision		=	100;
	char		EUROref_discipline	=	100;
	char		EUROtga			=	Off;
	short		EUROscrSize		=	Scrn_100;
	short		EUROvenue		=	London;
	short		EUROsky			=	On;
	short		EUROstadia		=	1;
	short		EUROlineDetail		=	On;
	short		EUROvidiType		=	1;
	short		EUROplyrDetail		=	1;
	short		EUROptchDetail		=	1;
	short		EUROresoln		=	0;

	// ---> Frontend Random number variables <---

	long 		EUROseed1;
	unsigned short 	EUROseed3;

	// ---> Network / Serial / Wireplay / Modem specific variables <---

	char		EUROcommTYPE	=	0;	// 0 network 1 serial 2 modem 3 wireplay
	char		EUROcommOVERIDE	=	128;
	char		EURO_Did_I_ChooseTeams;
	char		EURO_NetSelectionMade;
	char		UserNetList[24];
	char		TeamA_AUTOplayers;
	char		TeamB_AUTOplayers;
	char		EUROoveride;

	char		ModemInitList[255];
	BYTE		*Modems[255];
	BYTE		*ModemInitStrs[255];
	int		EuroNETseed;
	short		ModemXposn;
	char		ModemYpage	  =	0;
	signed short 	EUROmodemType	  =	0;
	char		EUROmodemDialType =	0;
	char		EUROmodemCommType =	0;
	char		DialNumber[64]	  =	"01142475549";
	char		InitStr[64]	  =	"";
	short		DialX;
	short		InitX;


	// ---> Selector Variables <---

	short		ButtonState;
	short		SelectorXcoord;
	short		SelectorYcoord;
	short		DeBounce;

	// ---> Windows '95 variables <---

	int		w95 = No;

//********************************************************************************************************************************

   //ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป 
   //บ                                                          บ
   //บ  DATA IN THIS AREA SHOULD BE SAVED OUT DURING SAVE GAME  บ
   //บ                                                          บ
   //ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ 

	char		SquadInfo[16*20];
	signed char 	FormationInfo[16];
	signed char 	GroupDrawInfo[16];
	signed char	GroupDrawDefaultInfo[16];
	League_info	LeagueTable[16];
	short		PlayersCaps[16*20];
	short		PlayersGoals[16*20];

	char		Pace[16*20];
	char		Power[16*20];
	char		Control[16*20];
	char		Flair[16*20];
	char		Vision[16*20];
	char		Accuracy[16*20];
	char		Stamina[16*20];
	char		Discipline[16*20];
	char		Fitness[16*20];
	char		FitnessDefault[16*20];
	char		DiscPts[16*20];

	user_info	UserList[16];
	signed char 	UserSetupList[16];

	char		NoOfSubs, UsableSubs;
	char		WinPts;
	char		DrawPts;

	char		MatchNumber;	

	char		EUROday;
	char		EUROmonth;
	char		EUROyear;
	char		EUROgameType;

	char 		EUROnoOfMatchPlyrs;

	char		EUROteamA, EUROteamB, EUROchampTeam;

	history_info	PastScores[16]={

		// bulgaria
			 {3,0,  1,4,  3,1,  0,0,  3,0,  3,2,  1,1,  3,0,  1,2,  1,3,},
		// croatia
			 {2,0,  2,0,  2,1,  4,0,  0,0,  2,0,  0,1,  7,1,  1,1,  2,1,},
		// czech. rep.
			 {0,0,  4,1,  4,2,  3,1,  1,1,  0,1,  1,1,  2,0,  2,0,  3,0,},
		// denmark
			 {1,0,  0,1,  1,1,  1,0,  1,0,  4,0,  2,0,  3,1,  1,1,  3,1,},
		// england
			 {1,1,  1,0,  0,0,  2,1,  3,3,  1,3,  0,0,  0,0,  3,1,  1,1,},   
		// france
			 {0,0,  0,0,  2,0,  1,0,  0,0,  4,0,  1,1,  10,0, 3,1,  2,0,},
		// germany
			 {1,1,  2,3,  2,0,  2,1,  2,1,  4,1,  6,1,  2,1,  3,1,  0,0,},
		// holland
			 {5,0,  0,1,  0,1,  4,0,  1,3,  0,1,  1,0,  4,0,  3,0,  2,0,},
		// italy
			 {3,1,  4,1,  2,0,  1,0,  1,0,  0,2,  1,0,  1,1,  3,1,  4,0,},
		// portugal
			 {1,1,  1,0,  1,0,  0,1,  3,2,  7,0,  1,1,  1,1,  3,0,  1,1,},
		// romania
			 {1,1,  0,1,  0,1,  1,1,  2,1,  4,1,  2,1,  0,0,  1,3,  2,0,},
		// russia
			 {0,0,  3,0,  3,0,  2,1,  7,0,  2,3,  6,0,  5,2,  2,1,  3,1,},
		// scotland
			 {0,1,  0,0,  2,0,  0,0,  2,1,  2,0,  1,0,  1,0,  0,2,  5,0,},
		// spain
			 {4,1,  2,2,  0,0,  1,1,  2,0,  1,0,  6,0,  2,1,  1,1,  3,0,},
		// switzerland
			 {2,1,  1,1,  2,2,  1,2,  0,1,  1,2,  2,0,  0,0,  3,0,  1,3,},
		// turkey
			 {3,1,  3,0,  1,0,  0,0,  2,1,  0,0,  2,0,  0,0,  0,0,  2,2,},
				};

	results_info	Results[32] = { 

		   0, 0,	0, 0, 0,	0,
		   0, 0,	0, 0, 0,	0,
		   0, 0,	0, 0, 0,	0,
		   0, 0,	0, 0, 0,	0,

		   0, 0,	0, 0, 0,	0,
		   0, 0,	0, 0, 0,	0,
		   0, 0,	0, 0, 0,	0,
		   0, 0,	0, 0, 0,	0,

		   0, 0,	0, 0, 0,	0,
		   0, 0,	0, 0, 0,	0,
		   0, 0,	0, 0, 0,	0,
		   0, 0,	0, 0, 0,	0,

		   0, 0,	0, 0, 0,	0,
		   0, 0,	0, 0, 0,	0,
		   0, 0,	0, 0, 0,	0,
		   0, 0,	0, 0, 0,	0,

		   0, 0,	0, 0, 0,	0,
		   0, 0,	0, 0, 0,	0,
		   0, 0,	0, 0, 0,	0,
		   0, 0,	0, 0, 0,	0,

		   0, 0,	0, 0, 0,	0,
		   0, 0,	0, 0, 0,	0,
		   0, 0,	0, 0, 0,	0,
		   0, 0,	0, 0, 0,	0,

		   0, 0,	0, 0, 0,	0,
		   0, 0,	0, 0, 0,	0,
		   0, 0,	0, 0, 0,	0,
		   0, 0,	0, 0, 0,	0,

		   0, 0,	0, 0, 0,	0,
		   0, 0,	0, 0, 0,	0,
		   0, 0,	0, 0, 0,	0,
		   0, 0,	0, 0, 0,	0,
			 };

//********************************************************************************************************************************








	char		Finish	   =  0;
	signed	char	ChangeMenu = -1;

	char KeyToggle[128];


	signed char IsUpper[255]={

		//	-    -    -    -    -    -    -    -
		       na,  na,  na,  na,  na,  na,  na,  na,		

		//	-    -    -    -    -    -    -    -
		       na,  na,  na,  na,  na,  na,  na,  na,		

		//	-    -    -    -    -    -    -    -
		       na,  na,  na,  na,  na,  na,  na,  na,		

		//	-    -    -    -    -    -    -    -
		       na,  na,  na,  na,  na,  na,  na,  na,		

		//	     !    "    #    $    %    &    '     
		       na,  na,  na,  na,  na,  na,  na,  na,		

		//	(    )    *    +    ,    -    .    / 
		       na,  na,  na,  na,  na,  na,  na,  na,		

		//	0    1    2    3    4    5    6    7  
		       na,  na,  na,  na,  na,  na,  na,  na,		

		//	8    9    :    ;    <    =    >    ?  
		       na,  na,  na,  na,  na,  na,  na,  na,		
		
		//	@    A    B    C    D    E    F    G  
		       na,  up,  up,  up,  up,  up,  up,  up,

 		//	H    I    J    K    L    M    N    O  
		       up,  up,  up,  up,  up,  up,  up,  up,
		
		//	P    Q    R    S    T    U    V    W  
		       up,  up,  up,  up,  up,  up,  up,  up,
		
		//	X    Y    Z    [    \    ]    ^    _  
		       up,  up,  up,  na,  na,  na,  na,  na,	

		//	`    a    b    c    d    e    f    g  
		       na,  lw,  lw,  lw,  lw,  lw,  lw,  lw,

		//	h    i    j    k    l    m    n    o  
		       lw,  lw,  lw,  lw,  lw,  lw,  lw,  lw,

		//	p    q    r    s    t    u    v    w  
		       lw,  lw,  lw,  lw,  lw,  lw,  lw,  lw,

		//	x    y    z    {    |    }    ~     
		       lw,  lw,  lw,  na,  na,  na,  na,  na,

		//	€                    …         
		       up,  lw,  lw,  lw,  lw,  lw,  lw,  lw,

		//                                   
		       lw,  lw,  lw,  lw,  lw,  lw,  up,  up,

		//          ‘    ’    “    ”    •    –    — 
		       up,  lw,  up,  lw,  lw,  lw,  lw,  lw,

		//                                   
		       lw,  up,  up,  na,  na,  na,  na,  na,

		//  	     ก    ข    ฃ    ค    ฅ    ฆ    ง 
		       lw,  up,  lw,  lw,  lw,  up,  na,  na, 

		//	จ    ฉ    ช    ซ    ฌ    ญ    ฎ    ฏ   
		       na,  na,	 na,  na,  na,	na,  na,  na,

		//	ฐ    ฑ    ฒ    ณ    ด    ต    ถ    ท   
		       na,  na,	 na,  na,  na,	na,  na,  na,

		//	ธ    น    บ    ป    ผ    ฝ    พ    ฟ   
		       na,  na,	 na,  na,  na,	na,  na,  na,

		//	ภ    ม    ย    ร    ฤ    ล    ฦ    ว 
		       na,  na,	 na,  na,  na,	na,  na,  na,

		//	ศ    ษ    ส    ห    ฬ    อ    ฮ    ฯ      
		       na,  na,	 na,  na,  na,	na,  na,  na,

		//	ะ    ั    า    ำ    ิ    ี    ึ    ื      
		       na,  na,	 na,  na,  na,	na,  na,  na,

		//	ุ    ู    ฺ    Û    Ü    Ý    Þ    ฿      
		       na,  na,	 na,  na,  na,	na,  na,  na,

		//	เ    แ    โ    ใ    ไ    ๅ    ๆ    ็      
		       na,  up,  na,  na,  na,	na,  na,  na,

		//	่    ้    ๊    ๋    ์    ํ
		       na,  na,	 na,  na,  na,	up,

			};


	unsigned char ToLower[255]={ 

		//	-    -    -    -    -    -    -    -
		        0,   0,   0,   0,   0,   0,   0,   0,		

		//	-    -    -    -    -    -    -    -
		        0,   0,   0,   0,   0,   0,   0,   0,		

		//	-    -    -    -    -    -    -    -
		        0,   0,   0,   0,   0,   0,   0,   0,		

		//	-    -    -    -    -    -    -    -
		        0,   0,   0,   0,   0,   0,   0,   0,		

		//	     !    "    #    $    %    &    '     
		       32,  33,  34,  35,  36,  37,  38,  39,   

		//	(    )    *    +    ,    -    .    / 
		       40,  41,  42,  43,  44,  45,  46,  47,

		//	0    1    2    3    4    5    6    7  
		       '0', '1', '2', '3', '4', '5', '6', '7',

		//	8    9    :    ;    <    =    >    ?  
		       '8', '9', 58,  59,  60,	61,  62,  63,
		
		//	@    A    B    C    D    E    F    G  
		       64,  'a', 'b', 'c', 'd', 'e', 'f', 'g',	

 		//	H    I    J    K    L    M    N    O  
		       'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
		
		//	P    Q    R    S    T    U    V    W  
		       'p', 'q', 'r', 's', 't', 'u', 'v', 'w',
		
		//	X    Y    Z    [    \    ]    ^    _  
		       'x', 'y', 'z', 91,  92,  93,  94,  95,	

		//	`    a    b    c    d    e    f    g  
		       96,  'a', 'b', 'c', 'd', 'e', 'f', 'g',

		//	h    i    j    k    l    m    n    o  
		       'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',

		//	p    q    r    s    t    u    v    w  
		       'p', 'q', 'r', 's', 't', 'u', 'v', 'w',

		//	x    y    z    {    |    }    ~     
		       'x', 'y', 'z', 123, 124, 125, 126, 127,

		//	€                    …         
		       '', '', '', '', '', '…', '', '',

		//                                   
		       '', '', '', '', '', '', '', '',
								 
		//          ‘    ’    “    ”    •    –    — 
		       '', '‘', '‘', '“', '”', '•', '–', '—',			

		//                                   
		       '', '”', '',  0,   0,	 0,   0,   0,

		//  	     ก    ข    ฃ    ค    ฅ    ฆ    ง 
		       ' ', 'ก', 'ข', 'ฃ', 'ค', 'ค',  0,   0,

		//	จ    ฉ    ช    ซ    ฌ    ญ    ฎ    ฏ   
		        0,   0,	  0,   0,   0,	 0,   0,   0,

		//	ฐ    ฑ    ฒ    ณ    ด    ต    ถ    ท   
		        0,   0,	  0,   0,   0,	 0,   0,   0,

		//	ธ    น    บ    ป    ผ    ฝ    พ    ฟ   
		        0,   0,	  0,   0,   0,	 0,   0,   0,

		//	ภ    ม    ย    ร    ฤ    ล    ฦ    ว 
		        0,   0,	  0,   0,   0,	 0,   0,   0,

		//	ศ    ษ    ส    ห    ฬ    อ    ฮ    ฯ      
		        0,   0,	  0,   0,   0,	 0,   0,   0,

		//	ะ    ั    า    ำ    ิ    ี    ึ    ื      
		        0,   0,	  0,   0,   0,	 0,   0,   0,

		//	ุ    ู    ฺ    Û    Ü    Ý    Þ    ฿      
		        0,   0,	  0,   0,   0,	 0,   0,   0,

		//	เ    แ    โ    ใ    ไ    ๅ    ๆ    ็      
		        0,  'แ',  0,   0,   0,	 0,   0,   0,

		//	่    ้    ๊    ๋    ์    ํ
		        0,   0,	  0,   0,   0,	'ํ', 

			};

	unsigned char ToUpper[255]={ 

		//	-    -    -    -    -    -    -    -
		        0,   0,   0,   0,   0,   0,   0,   0,		

		//	-    -    -    -    -    -    -    -
		        0,   0,   0,   0,   0,   0,   0,   0,		

		//	-    -    -    -    -    -    -    -
		        0,   0,   0,   0,   0,   0,   0,   0,		

		//	-    -    -    -    -    -    -    -
		        0,   0,   0,   0,   0,   0,   0,   0,		

		//	     !    "    #    $    %    &    '     
		       32,  33,  34,  35,  36,  37,  38,  39,   

		//	(    )    *    +    ,    -    .    / 
		       40,  41,  42,  43,  44,  45,  46,  47,

		//	0    1    2    3    4    5    6    7  
		       '0', '1', '2', '3', '4', '5', '6', '7',

		//	8    9    :    ;    <    =    >    ?  
		       '8', '9', 58,  59,  60,	61,  62,  63,
		
		//	@    A    B    C    D    E    F    G  
		       64,  'A', 'B', 'C', 'D', 'E', 'F', 'G',	

 		//	H    I    J    K    L    M    N    O  
		       'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
		
		//	P    Q    R    S    T    U    V    W  
		       'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W',
		
		//	X    Y    Z    [    \    ]    ^    _  
		       'X', 'Y', 'Z', 91,  92,  93,  94,  95,	

		//	`    a    b    c    d    e    f    g  
		       96,  'A', 'B', 'C', 'D', 'E', 'F', 'G',

		//	h    i    j    k    l    m    n    o  
		       'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',

		//	p    q    r    s    t    u    v    w  
		       'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W',

		//	x    y    z    {    |    }    ~     
		       'X', 'Y', 'Z', 123, 124, 125, 126, 127,

		//	€                    …         
		       '€', '', '', '', '', '…', '', '€',

		//                                   
		       '', '', '', '', '', '', '', '',
								 
		//          ‘    ’    “    ”    •    –    — 
		       '', '’', '’', '“', '', '•', '–', '—',			

		//                                   
		       '', '', '',  0,   0,	 0,   0,   0,

		//  	     ก    ข    ฃ    ค    ฅ    ฆ    ง 
		       ' ', 'ก', 'ข', 'ฃ', 'ฅ', 'ฅ',  0,   0,

		//	จ    ฉ    ช    ซ    ฌ    ญ    ฎ    ฏ   
		        0,   0,	  0,   0,   0,	 0,   0,   0,

		//	ฐ    ฑ    ฒ    ณ    ด    ต    ถ    ท   
		        0,   0,	  0,   0,   0,	 0,   0,   0,

		//	ธ    น    บ    ป    ผ    ฝ    พ    ฟ   
		        0,   0,	  0,   0,   0,	 0,   0,   0,

		//	ภ    ม    ย    ร    ฤ    ล    ฦ    ว 
		        0,   0,	  0,   0,   0,	 0,   0,   0,

		//	ศ    ษ    ส    ห    ฬ    อ    ฮ    ฯ      
		        0,   0,	  0,   0,   0,	 0,   0,   0,

		//	ะ    ั    า    ำ    ิ    ี    ึ    ื      
		        0,   0,	  0,   0,   0,	 0,   0,   0,

		//	ุ    ู    ฺ    Û    Ü    Ý    Þ    ฿      
		        0,   0,	  0,   0,   0,	 0,   0,   0,

		//	เ    แ    โ    ใ    ไ    ๅ    ๆ    ็      
		        0,  'แ',  0,   0,   0,	 0,   0,   0,

		//	่    ้    ๊    ๋    ์    ํ
		        0,   0,	  0,   0,   0,	'ํ', 

			};



	unsigned char ASCtoImageTBL[255]={ 
		
		//	-    -    -    -    -    -    -    -
		       na,  na,  na,  na,  na,  na,  na,  na,		

		//	-    -    -    -    -    -    -    -
		       na,  na,  na,  na,  na,  na,  na,  na,		

		//	-    -    -    -    -    -    -    -
		       na,  na,  na,  na,  na,  na,  na,  na,		

		//	-    -    -    -    -    -    -    -
		       na,  na,  na,  na,  na,  na,  na,  na,		

		//	     !    "    #    $    %    &    '     
			0,   1,   2,   3,   4,   5,   6,   7,   

		//	(    )    *    +    ,    -    .    / 
		        8,   9,  10,  11,  12,  13,  14,  15,

		//	0    1    2    3    4    5    6    7  
		       16,  17,	 18,  19,  20,  21,  22,  23,

		//	8    9    :    ;    <    =    >    ?  
		       24,  25,  26,  27,  28,	29,  30,  31,
		
		//	@    A    B    C    D    E    F    G  
		       32,  33,  34,  35,  36,  37,  38,  39,	

 		//	H    I    J    K    L    M    N    O  
		       40,  41,  42,  43,  44,  45,  46,  47,
		
		//	P    Q    R    S    T    U    V    W  
		       48,  49,  50,  51,  52,  53,  54,  55,
		
		//	X    Y    Z    [    \    ]    ^    _  
		       56,  57,  58,  59,  60,  61,  62,  63,	

		//	`    a    b    c    d    e    f    g  
		       64,  65,  66,  67,  68,  69,  70,  71,

		//	h    i    j    k    l    m    n    o  
		       72,  73,  74,  75,  76,  77,  78,  79,

		//	p    q    r    s    t    u    v    w  
		       80,  81,  82,  83,  84,  85,  86,  87,

		//	x    y    z    {    |    }    ~     
		       88,  89,  90,  91,  92,  93,  94,   0,

		//	€                    …         
		       95,  96,  97,  98,  99, 100, 101, 102,

		//                                   
		      103, 104, 105, 106, 107, 108, 109, 110,	

		//          ‘    ’    “    ”    •    –    — 
		      111, 112, 113, 114, 115, 116, 117, 118,

		//                                   
		      119, 120, 121,   0,   0,   0,   0,   0,

		//  	     ก    ข    ฃ    ค    ฅ    ฆ    ง 
		      122, 123, 124, 125, 126, 127,   0,   0,

		//	จ    ฉ    ช    ซ    ฌ    ญ    ฎ    ฏ   
			0,   0,   0,   0,   0,   0,   0,   0, 

		//	ฐ    ฑ    ฒ    ณ    ด    ต    ถ    ท   
			0,   0,   0,   0,   0,   0,   0,   0, 

		//	ธ    น    บ    ป    ผ    ฝ    พ    ฟ   
			0,   0,   0,   0,   0,   0,   0,   0, 

		//	ภ    ม    ย    ร    ฤ    ล    ฦ    ว 
			0,   0,   0,   0,   0,   0,   0,   0, 

		//	ศ    ษ    ส    ห    ฬ    อ    ฮ    ฯ      
			0,   0,   0,   0,   0,   0,   0,   0,    

		//	ะ    ั    า    ำ    ิ    ี    ึ    ื      
			0,   0,   0,   0,   0,   0,   0,   0,    

		//	ุ    ู    ฺ    Û    Ü    Ý    Þ    ฿      
			0,   0,   0,   0,   0,   0,   0,   0,    

		//	เ    แ    โ    ใ    ไ    ๅ    ๆ    ็      
			0, 128,   0,   0,   0,   0,   0,   0,    

		//	่    ้    ๊    ๋    ์    ํ
       			0,   0,   0,   0,   0, 129, 

			};


	unsigned char LegalDial[255]={

		//	-    -    -    -    -    -    -    -
		        0,   0,	  0,   0,   0,	 0,   0,   0,

		//	-    -    -    -    -    -    -    -
		        0,   0,	  0,   0,   0,	 0,   0,   0,

		//	-    -    -    -    -    -    -    -
		        0,   0,	  0,   0,   0,	 0,   0,   0,

		//	-    -    -    -    -    -    -    -
		        0,   0,	  0,   0,   0,	 0,   0,   0,

		//	     !    "    #    $    %    &    '     
		        0,   0,	  0,   0,   0,	 0,   0,   0,

		//	(    )    *    +    ,    -    .    / 
		        0,   0,	  0,   0,   0,	 0,   0,   0,

		//	0    1    2    3    4    5    6    7  
		        0,   0,	  0,   0,   0,	 0,   0,   0,

		//	8    9    :    ;    <    =    >    ?  
		        0,   0,	  0,   0,   0,	 0,   0,   0,
		
		//	@    A    B    C    D    E    F    G  
		        0,   0,	  0,   0,   0,	 0,   0,   0,

 		//	H    I    J    K    L    M    N    O  
		        0,   0,	  0,   0,   0,	 0,   0,   0,
		
		//	P    Q    R    S    T    U    V    W  
		        0,   0,	  0,   0,   0,	 0,   0,   0,
		
		//	X    Y    Z    [    \    ]    ^    _  
		        0,   0,	  0,   0,   0,	 0,   0,   0,

		//	`    a    b    c    d    e    f    g  
		        0,   0,	  0,   0,   0,	 0,   0,   0,

		//	h    i    j    k    l    m    n    o  
		        0,   0,	  0,   0,   0,	 0,   0,   0,

		//	p    q    r    s    t    u    v    w  
		        0,   0,	  0,   0,   0,	 0,   0,   0,

		//	x    y    z    {    |    }    ~     
		        0,   0,	  0,   0,   0,	 0,   0,   0,

		//	€                    …         
		        0,   0,	  0,   0,   0,	 0,   0,   0,

		//                                   
		        0,   0,	  0,   0,   0,	 0,   0,   0,

		//          ‘    ’    “    ”    •    –    — 
		        0,   0,	  0,   0,   0,	 0,   0,   0,

		//                                   
		        0,   0,	  0,   0,   0,	 0,   0,   0,

		//  	     ก    ข    ฃ    ค    ฅ    ฆ    ง 
		        0,   0,	  0,   0,   0,	 0,   0,   0,

		//	จ    ฉ    ช    ซ    ฌ    ญ    ฎ    ฏ   
		        0,   0,	  0,   0,   0,	 0,   0,   0,

		//	ฐ    ฑ    ฒ    ณ    ด    ต    ถ    ท   
		        0,   0,	  0,   0,   0,	 0,   0,   0,

		//	ธ    น    บ    ป    ผ    ฝ    พ    ฟ   
		        0,   0,	  0,   0,   0,	 0,   0,   0,

		//	ภ    ม    ย    ร    ฤ    ล    ฦ    ว 
		        0,   0,	  0,   0,   0,	 0,   0,   0,

		//	ศ    ษ    ส    ห    ฬ    อ    ฮ    ฯ      
		        0,   0,	  0,   0,   0,	 0,   0,   0,

		//	ะ    ั    า    ำ    ิ    ี    ึ    ื      
		        0,   0,	  0,   0,   0,	 0,   0,   0,

		//	ุ    ู    ฺ    Û    Ü    Ý    Þ    ฿      
		        0,   0,	  0,   0,   0,	 0,   0,   0,

		//	เ    แ    โ    ใ    ไ    ๅ    ๆ    ็      
		        0,   0,	  0,   0,   0,	 0,   0,   0,

		//	่    ้    ๊    ๋    ์    ํ
		        0,   0,	  0,   0,   0,	 0,

			};


	//ษอออออออออออออออออออออออออออป 
	//บ                           บ
	//บ  RESET EURO 96 VARIABLES  บ
	//บ                           บ
	//ศอออออออออออออออออออออออออออผ 

void	Euro96initialise()
	{
		memcpy( &GroupDrawInfo[0], &GroupDrawDefaultInfo[0], 16 );		// Reset fixtures to EURO 96 draw.

		for ( char t=0; t < 16; t++ )						// Reset all squads, making team
		{for ( char p=0; p < 20; p++ ){SquadInfo[ (t*20)+p ] = p;}}		// lists run from plyr 1 to 20.

		memset( &DiscPts, 0, 16*20 );						// Reset all players disciplinary pts.
		memcpy( &Fitness[0], &FitnessDefault[0], 16*20 );			// Reset all players fitnesses.

		for ( char r=0; r < 32 ; r++ )						// Reset Previous Results.
		{					     
			Results[r].HomeScore	=	0;
			Results[r].AwayScore	=	0;
			Results[r].AfterExtra	=	0;
			Results[r].AfterPens	=	0;
			Results[r].HomePens	=	0;
			Results[r].AwayPens	=	0;
			Results[r].WinningTeam	=	0;
		}

		for ( t=0; t < 16 ; t++ )						// Reset Group/League table data.
		{
			LeagueTable[t].played		=	0;
			LeagueTable[t].won		=	0;
			LeagueTable[t].lost		=	0;
			LeagueTable[t].drew		=	0;
			LeagueTable[t].goalsFor		=	0;
			LeagueTable[t].goalsAgainst	=	0;
			LeagueTable[t].goalDiff		=	0;
			LeagueTable[t].points		=	0;
		}

		MatchNumber	=	0;						// Reset Euro Championship match no.
	}
		       

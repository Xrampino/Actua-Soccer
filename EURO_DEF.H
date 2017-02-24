

#define		NULL						0
#define		LF 						10
#define		MAX_STRING_LENGTH		50
#define		REDRAW					0
#define		LEGALDRAW 				1
#define		NOT_FOUND				-1
#define		No							0
#define		Yes						1
#define		Off						0
#define		On							1
#define		JUSTIFY_FROM_POINT	0
#define		CENTRE_ON_POINT		1

#define		FADE_COUNTER			25

#define		BLANK_SCREEN			0
#define		PALETTE_FADEUP			1
#define		RUN_FRONTEND			2
#define		PALETTE_FADEDOWN		3

#define		na						  	-1		// neither upper-case or lower-case character.
#define		lw							0		// lower-case character.
#define		up							1		// upper-case character.

//#define		EURO_friendly			0
//#define		EURO_championship		1
//#define		EURO_network_game		2
//#define		EURO_serial_game		3
//#define		EURO_modem_game		4
//#define		EURO_demomode			5
//#define		EURO_simulation		6
//#define		EURO_practice			7
//#define		EURO_wireplay			8

#ifndef BYTE
typedef 		unsigned char BYTE;
#endif

#define 		Max(a,b) (((a)>=(b)) ? (a):(b))
#define 		Min(a,b) (((a)>=(b)) ? (b):(a))


// [ Control Type Definitions ]					     


#define	Unusable						0
#define	Usable						128

#define	EuroKeyboard1 				0
#define	EuroKeyboard2				1
#define	EuroJoystick1				2
#define	EuroJoystick2				3
#define	EuroMouse					4
#define	EuroLogictechPad			5

#define	NO_OF_CONTROL_METHODS	6

// [ Keyboard Input Data ]

#define 	B_SPACE						0x08
#define 	DELETE						0x53
#define 	RETURN						0x0D
#define	L_ARROW						0x4B 	// ext
#define	R_ARROW						0x4D 	// ext 
#define	HOME							0x47 	// ext
#define	END							0x4f 	// ext

#define	NORMAL						0
#define	DIAL							1

#define	ENABLE_INPUT				0
#define	DISABLE_INPUT				1

#define	DIAL_LENGTH					280
#define	INIT_LENGTH 				280

#define	EDIT_DIAL_NUMBER			1
#define	EDIT_INIT_STRING			2

// [ Modem Data ]

#define	MAX_MODEM_TYPES			88
#define	MAX_MODEM_STRINGS			34

// [ Image Data ]

#define		SMALL_FONT				GEOFONT16
#define		MEDIUM_FONT				GEOFONT22
#define		LARGE_FONT				GEOFONT30

// [ Text String Data ]					     

#define		ANDYF_TEXT_START			1600
#define		LAURENT_TEXT_START 		ANDYF_TEXT_START+100
#define		TEXT_STRING_BUFFER_LEN	24576

// [ Mouse Cursor Image Offsets ]					     

#define		NoButton					0
#define		LeftButton 				1
#define		RightButton				2

// [ Country Data ]					     
//
//#define		Bulgaria					0
//#define		Croatia					1
//#define  	Czech						2
//#define		Denmark					3
//#define		England					4
//#define		France					5
//#define		Germany					6
//#define		Holland					7
//#define		Italy						8
//#define		Portugal					9
//#define		Romania					10
//#define		Russia					11
//#define		Scotland					12
//#define		Spain						13
//#define		Switzerland				14
//#define		Turkey					15
//
// [ Venue Offsets ]					     
//
//#define		London					0		
//#define		Birmingham				1
//#define		Leeds						2
//#define		Newcastle				3
//#define		Manchester				4
//#define		Liverpool				5
//#define		Sheffield				6
//#define		Nottingham				7
//
// [ League table Offsets ]					     

#define		Wins						0		
#define		Draws						1
#define		Loses						2
#define		Points					3

// [ Next Match Types ]					     

#define		QuarterFinal			0		
#define		SemiFinal				1
#define		Final						2

// [ Result Text ]

#define		ProceedToNextRnd		0
#define		ExtraTime				1
#define		Penalties				2

// [ Player information Offsets ]					     

#define		Age						0
#define		Club						1
#define		Caps						2
#define		Goals						3
#define		Posn						4

// [ Formation Field Position Offsets ]					     

#define		Gk				 			0
#define		Df				 			1
#define		Md				 			2
#define		Fw				 			3
#define		Sb			 				4
#define		Dr			 				5
#define		Bn							6
#define		In							7

#define		Injured					25		// this value determines when a player is no longer fit enough to play.

// [ Player Statistic Lable Offsets ]

#define		Spd						0
#define		Tackling					1
#define		Passing					2
#define		Shooting					3
#define		Skill						4
#define		Fit						5

// [ User Tag Label Offsets ]					     

#define		P1	 						0
#define		P2							1
#define		P3							2
#define		P4							3
#define		P5							4 
#define		P6							5 
#define		P7							6 
#define		P8							7 
#define		P9							8 
#define		P10						9 
#define		P11						10
#define		P12						11
#define		P13						12
#define		P14						13
#define		P15						14
#define		P16						15
#define		Auto						16
#define		Dash						17

// [ Match User Label Offset ]					     

#define		ComputerUser			16

// [ User Selection Labels ]					     

#define		Country					0
#define		Cntrl						1

// [ Network Information Labels ]					     

#define		Netusers					0
#define		Tochoose					1
#define		Netwait					2

// [ Wireplay Information Labels ]					     

#define		Wireusers				0
#define		Wirewait					1

// [ Spectator Label Offsets ]

#define		Watch						0
#define		Nocntrl					1

// [ Team Information Label Offsets ]

#define		Record					0
#define		President				1
#define		Coach						2
#define		Starplayr				3
#define		Last10					4
#define		Teamwins					5
#define		Teamdraws				6
#define		Teamloses				7
#define		Teamglsfor				8
#define		Teamglsagn				9
					     
// [ Button Text Label Offsets ]

#define		Select					0
#define		Redraw					1
#define		Done						2
#define		Default					3
#define		StartMatch				4
#define		PlayerSetup				5
#define		TeamSetup				6
#define		NextMatch				7
#define		SelectTeams				8

// [ Modem Heading Label Offsets ]

#define		Initialisation			0
#define		Typeheading				1
#define		Type						2
#define		Dial						3
#define		Comport					4
#define		Initstring				5
#define		Phonenumber				6

// [ Camera types ]

#define		CAMwire					0
#define		CAMfar					1
#define		CAMplan					2
#define		CAMgline					3
#define		CAMiso					4
#define		CAMplyr					5
#define		CAMref					6

// [ Match Length types ]

#define		TIME_5mins				0
#define		TIME_10mins				1
#define		TIME_20mins				2
#define		TIME_40mins				3
#define		TIME_90mins				4

// [ Screen size types ]

#define		Scrn_100					0
#define		Scrn_85					1
#define		Scrn_85w					2
#define		Scrn_75					3
#define		Scrn_75w					4
#define		Scrn_65					5
#define		Scrn_65w					6
#define		Scrn_50					7
#define		Scrn_50w					8
#define		Scrn_40w					9

// [ Variable Statistic Bar Definitions ]

#define	Lft	0
#define	Rgt	1
#define	Top	0
#define	Btm	1

// [ Variable Purple Filling Offsets ]

#define	Dull		0
#define	Bright	1

// [ Wind types ]

#define 		LowWIND					1
#define 		MediumWIND				2
#define 		HighWIND					3

// [ Player name Data ]					     

#define		NAME_BUFFER_LEN 		128
//#define		INITIAL_SURNAME		0
//#define		SURNAME					1
//#define		FULL_NAME				2

// [ Menu Pages ]

#define		MAIN						0
#define		SQUAD_SELECT			2
#define		GROUP_FIXTURES			3
#define		TEAM_SELECT				4
#define		EURO_REDRAW				5
#define		PLAYER_STATS			6
#define		PLAYER_SETUP			7
#define		TEAM_STATS				8
#define		VENUE_FLYTHRU			9
#define		MODEM_SETUP			  	10
#define		NEXT_MATCH			  	11
#define		QUALIFIERS				12
#define		QUARTER_FINALS			13
#define		SEMI_FINALS				14
#define		FINAL_MATCH				15
#define		EXIT_FRONTEND		  	63

// [ Bounding Box Type Definitions ]					     

#define		MAX_BOUNDING_BOXES	52
#define		NO_BOX					-1

#define		TEAM_BOX					20
#define		FORMATION_infoBOX		33
#define		QUESTION_BOX			34
#define		FORMATION_BOX			35
#define		FORMATION_stringBOX	36
#define		EURO_TEAMa_BOX			1
#define		EURO_TEAMb_BOX			2
#define		RETURN_SQUAD_BOX		37
#define		RETURN_PSTATS_BOX		35
//
// euro_sel.cpp
//
//
#define		PLAYER_SETUP_BOX			3
#define		FORMATION_SETUP_BOX		4
#define		CHOOSE_NET_TEAMS_BOX		5
#define		START_MATCH_BOX			6
#define		USER_TEAM_SELECT_BOX 	7
#define		USER_TEAMdisp_BOX			8
#define		NOofUSERS_BOX				9
#define		NOofUSERSdsp_BOX			10
#define		START_MATCHdisp_BOX		11
#define		FORMATION_SETUPdisp_BOX	12
#define		PLAYER_SETUPdisp_BOX		13
#define		SELECT_TEAM_BOX			14
#define		SELECT_TEAMdisp_BOX		15
//
// euro_usr.cpp
//
//				user control			 0   >...24
#define		TEAM_SELECT_BOX		43
#define		PLYR_CNTRL_BOX			44
#define		PLYR_COUNTRY_BOX		45
#define		USER_SETUP_BOX			46	//>...49
#define		NET_START_BOX			26
#define		NET_INFO_BOX			25
#define		TEAM_SELECTdisp_BOX	26
#define		NET_STARTdisp_BOX		27
//
//	euro_mod.cpp
//
//
#define		MODEM_SELECT_BOX		10
#define		DIAL_SELECT_BOX		11
#define		COM_SELECT_BOX			12
#define		DIAL_NUMBER_BOX		13
#define		INIT_STRING_BOX		14
//
//	euro_fix.cpp
//
//
#define	 	REDRAW_BOX				0
#define		GRP_FIX_BOX				1
#define		REDRAWdisp_BOX			2
#define		GRP_FIXdisp_BOX		3
#define		DEFAULT_BOX				4
#define		DEFAULTdisp_BOX		5
#define	 	NXT_MTCH_BOX 			6
#define	 	NXT_MTCHdisp_BOX		7
#define		EUROCUP_BOX				8
//
// euro_inf.cpp
//
#define		OPPONENT_TEAM_BOX		38
#define		RETN_TSTATS_BOX		35
#define		RETN_TSTATSdisp_BOX	39


// [ General Defines ]

#define		PITCH_XPOS_BL			(28.0)			
#define		PITCH_YPOS_BL			(350.0)		
#define		PITCH_XPOS_TL			(93.0)			
#define		PITCH_YPOS_TL			(192.0)		
#define		PITCH_XPOS_BR			(28.0+414.0)	
#define		PITCH_YPOS_BR			(350.0)		
#define		PITCH_XPOS_TR			(376.0)		
#define		PITCH_YPOS_TR			(192.0)
#define		FORMATION_BAR_WIDTH	96

// [ Co-ordinate Defines ]

#define		NameBarXposn  			34
												
// [ Colour Defines ]

#define	SELECT_COLOUR				55
#define	MOVE_COLOUR					62

// [ Team Marker Defines ]

#define	TEAM_1a						0
#define	TEAM_2a						1
#define	TEAM_3a						2
#define	TEAM_4a						3
#define	TEAM_1b						4
#define	TEAM_2b						5
#define	TEAM_3b						6
#define	TEAM_4b						7
#define	TEAM_1c						8
#define	TEAM_2c						9
#define	TEAM_3c						10
#define	TEAM_4c						11
#define	TEAM_1d						12
#define	TEAM_2d						13
#define	TEAM_3d						14
#define	TEAM_4d						15

#define	TEAM_1q						16
#define	TEAM_2q						17
#define	TEAM_3q						18
#define	TEAM_4q						19

#define	TEAM_1s						20
#define	TEAM_2s						21

// [ Information definitions ]

#define	never							-1
#define	y1960							0
#define	Line01						0
#define	Line02						1
#define	Line03						2
#define	Line04						3
#define	Line05						4
#define	Line06						5
#define	Line07						6
#define	Line08						7
#define	Line09						8
#define	Line10						9
#define	Line11						10
#define	Line12						11
#define	Line13						12
#define	Line14						13
#define	Line15						14
#define	Line16						15
#define	Line17						16
#define	Line18						17 
#define	Line19						18 
#define	Line20						19 
#define	Line21						20 
#define	Line22						21
#define	Line23						22
#define	Line24						23
#define	Line25						24
#define	Line26						25
#define	Line27						26
#define	Line28						27 
#define	Line29					  	28 
#define	Line30					  	29 
#define	Line31						30 
#define	Line32						31
#define	Line33						32
#define	Line34						33
#define	Line35						34
#define	Line36						35
#define	Line37						36
											 
typedef 		void (*copyfunctiontype)(int copyWidth, BYTE *srce, BYTE *dest);

// Pseudo buffer info type
//typedef struct
//	{ 
//	BYTE  *pseudo_start;
//	long  pseudo_width;
//	long  pseudo_height;
//	long	window_width;
//	long	window_height;
//	}
//	pseudo_info;
//
// Texture page info type
//typedef struct
//	{ 
//	BYTE  *page_start;
//	unsigned int page_width;
//	unsigned int page_height;
//	}
//	texture_info;
//
// DAT offset file format type
//typedef struct {
//	unsigned	long	offset;
//	unsigned	long	size;
//	}
//	offset_defn;
//
// Bounding Box info type
//typedef struct {
//	signed	short 		BoundingBoxLeft;
//	signed	short 		BoundingBoxTop;
//	signed	short 		BoundingBoxRight;
//	signed	short 		BoundingBoxBottom;
//	}
//	box_info;
//
//#define	MAX_ANIMATIONS			8
//#define	CONT_ANIM				2
//#define	RUN_ONCE					0
//
// Animating sprites info type
//typedef struct {
//	float						StartFrame;
//	float						EndFrame;
//	float						Counter;
//	float						AnimationSpeed;
//	signed 	char  		Bounding_box;
//	unsigned char			Flags;
//	int						xposn, yposn;
//	}
//	animation_info;
//
//#define	MAX_DUMPS		128
//
//// Screen Dump info type
//typedef struct {
//	char	DumpFlag;
//	short	DumpXpos;
//	short	DumpYpos;
//	short	DumpWidth;
//	short	DumpHeight;
//		       	}dump_info;
//
//// String and coordinates for headings on tables.
//typedef struct {
//	int	xposn;
//	int	yposn;
//	short	string;
//		       	}header_info;
//
//// Coordinates for team names within group tables.
//typedef struct {
//	int	xposn;
//	int	yposn;
//		       	}Coord_info;
//
//// Coordinates and image data for country select images.
//typedef struct {
//	int	image_no;
//	int	xposn;
//	int	yposn;
//		       	}TeamSel_Info;
//
//// League table information.
//typedef struct {
//	char	played;
//	char	won;
//	char	drew;
//	char	lost;
//	short	goalsFor;
//	short	goalsAgainst;
//	signed short goalDiff;
//	char	points;
//		       	}League_info;
//
//// Euro Champioship fixture info.
//typedef struct {
//	char	HomeTeam;
//	char	AwayTeam;
//	int	fixXposn;
//	int	fixYposn;
//					}fixture_info;
//
//// Euro Champioship scores info.
//typedef struct {
//	short	HomeScore;
//	short	AwayScore;
//					}results_info;
//
//
//#define	AUTOPLAYER			-1
//#define	PLYR_NOT_CHOSEN	12
//
//// User info.
//typedef struct {
//	char			team;			
//	signed char	player;
//	char			control;
//	char			TeamHAflag;
//					}user_info;
//
//// User championship info.
//typedef struct {
//	char			NoOfUsers;			
//					}euro_info;
//
//typedef struct {
//	short			scored;
//	short			conceeded;
//				}result_data;
//
//// Past History info.
//typedef struct {
//	result_data	history[10];
//					}history_info;
//
// Slider bar info type
//typedef struct
//	{ 
//	short	windowposn;			// internal ypos value.
//	short	minx;					// top left of inner section of bar.
//	short miny;					// top left of inner	section of bar.
//	short	maxx;					// bottom right of inner section of bar.
//	short maxy;					// bottom right of inner section of bar.
//	short elements;			// number of elements in list.
//	short page_elements;		// number of elements displayed on screen.
//	}
//	slider_info;
//
//
// Slider bar info type
//typedef struct
//	{ 
//	char	team;
//	short xposn;
//	short yposn;
//	}
//	qualify_info;



#ifndef BYTE
typedef 		unsigned char BYTE;
#endif


#define		EURO_friendly			0
#define		EURO_championship		1
#define		EURO_network_game		2
#define		EURO_serial_game		3
#define		EURO_modem_game		4
#define		EURO_demomode			5
#define		EURO_simulation		6
#define		EURO_practice			7
#define		EURO_wireplay			8

// [ Country Data ]					     

#define		Bulgaria					0
#define		Croatia					1
#define  	Czech						2
#define		Denmark					3
#define		England					4
#define		France					5
#define		Germany					6
#define		Holland					7
#define		Italy						8
#define		Portugal					9
#define		Romania					10
#define		Russia					11
#define		Scotland					12
#define		Spain						13
#define		Switzerland				14
#define		Turkey					15

// [ Venue Offsets ]					     

#define		London					0		
#define		Birmingham				1
#define		Leeds						2
#define		Newcastle				3
#define		Manchester				4
#define		Liverpool				5
#define		Sheffield				6
#define		Nottingham				7

// [ Player name Data ]					     

#define		INITIAL_SURNAME		0
#define		SURNAME					1
#define		FULL_NAME				2


// Pseudo buffer info type
typedef struct
	{ 
	BYTE  *pseudo_start;
	long  pseudo_width;
	long  pseudo_height;
	long	window_width;
	long	window_height;
	}
	pseudo_info;

// Texture page info type
typedef struct
	{ 
	BYTE  *page_start;
	unsigned int page_width;
	unsigned int page_height;
	}
	texture_info;

// DAT offset file format type
typedef struct {
	unsigned	long	offset;
	unsigned	long	size;
	}
	offset_defn;

// Bounding Box info type
typedef struct {
	signed	short 		BoundingBoxLeft;
	signed	short 		BoundingBoxTop;
	signed	short 		BoundingBoxRight;
	signed	short 		BoundingBoxBottom;
	}
	box_info;

#define	MAX_ANIMATIONS			8
#define	CONT_ANIM				2
#define	RUN_ONCE					0

// Animating sprites info type
typedef struct {
	float						StartFrame;
	float						EndFrame;
	float						Counter;
	float						AnimationSpeed;
	signed 	char  		Bounding_box;
	unsigned char			Flags;
	int						xposn, yposn;
	}
	animation_info;

#define	MAX_DUMPS		128

// Screen Dump info type
typedef struct {
	char	DumpFlag;
	short	DumpXpos;
	short	DumpYpos;
	short	DumpWidth;
	short	DumpHeight;
		       	}dump_info;

// String and coordinates for headings on tables.
typedef struct {
	int	xposn;
	int	yposn;
	short	string;
		       	}header_info;

// Coordinates for team names within group tables.
typedef struct {
	int	xposn;
	int	yposn;
		       	}Coord_info;

// Coordinates and image data for country select images.
typedef struct {
	int	image_no;
	int	xposn;
	int	yposn;
		       	}TeamSel_Info;

// League table information.
typedef struct {
	char	played;
	char	won;
	char	drew;
	char	lost;
	short	goalsFor;
	short	goalsAgainst;
	signed short goalDiff;
	char	points;
		       	}League_info;

// Euro Champioship fixture info.
typedef struct {
	char	HomeTeam;
	char	AwayTeam;
	int	fixXposn;
	int	fixYposn;
					}fixture_info;

// Euro Champioship scores info.
typedef struct {
	short	HomeScore;
	short	AwayScore;
	
	char	AfterExtra;
	char	AfterPens;
	char	HomePens;	
	char	AwayPens;	
	char	WinningTeam;	
	char	Message;	

					}results_info;


#define	AUTOPLAYER			-1
#define	PLYR_NOT_CHOSEN	12

// User info.
typedef struct {
	char			team;			
	signed char	player;
	char			control;
	char			TeamHAflag;
					}user_info;

// User championship info.
typedef struct {
	char			NoOfUsers;			
					}euro_info;

typedef struct {
	short			scored;
	short			conceeded;
				}result_data;

// Past History info.
typedef struct {
	result_data	history[10];
					}history_info;

// Slider bar info type
typedef struct
	{ 
	short	windowposn;			// internal ypos value.
	short	minx;					// top left of inner section of bar.
	short miny;					// top left of inner	section of bar.
	short	maxx;					// bottom right of inner section of bar.
	short maxy;					// bottom right of inner section of bar.
	short elements;			// number of elements in list.
	short page_elements;		// number of elements displayed on screen.
	}
	slider_info;


// Slider bar info type
typedef struct
	{ 
	char	team;
	short xposn;
	short yposn;
	}
	qualify_info;

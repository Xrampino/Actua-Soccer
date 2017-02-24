#define	YES					1
#define	NO						0
#define	English				0
#define	French				1
#define	German				2
#define	American				3
#define	Canadian				4
#define	Norwegian			5

#define	ROLLING_DEMO		Off		   // can be 	Off, German, English, American
#define	REAL_NAMES			NO				// can be	YES or NO  (used specifically for USA/Canadian versions).

#define 	ON 	 				1
#define 	OFF 					0
#define	DEMO_TIME			1000
#define	FILE_ERROR			1
#define	SOUND_ERROR			2
#define	CONFIG_ERROR		4
#define	MOUSE_ERROR			8
#define	MEMORY_PROBLEM		16
#define	FILE_MISSING		32
#define	WHEEL_ERROR			64
#define	MATCH_ERROR			256

#define	KEYS					0xff

#define	UP_KEY		0
#define	DN_KEY		1
#define	LF_KEY		2
#define	RT_KEY		3
#define	F1_KEY		4
#define	F2_KEY		5

#define	LF_RED		0
#define	RT_RED		1
#define	UP_RED		2
#define	DN_RED		3
#define	F1_RED		4
#define	F2_RED		5


#define 	PI	 					3.1415

#define	SEQU_ADDR			0x3c4
#define	CRTC_ADDR 			0x3d4

#define	REAL_SPEED			20
#define	MAX_USERS			20
#define	TIMER_FRAC			10
#define	TIMER_SPEED			(TIMER_FRAC*REAL_SPEED)

#define	MEG4					0
#define	MEG8					1

#define	LO						0
#define	HI						1
#define	MED					1
#define	HIGH					2

#define	FRIENDLY				0
#define	LEAGUE				1
#define	CUP					2
#define	PRACTICE				3
#define	NETWORK				4

#define 	MEM8 					3500000
#define 	FRAG 					1000000

#define	ARCADE				0
#define	SIMULATION			1

#define	PLAYER1				1
#define	PLAYER2				2
#define	PLAYER3				4
#define	PLAYER4				8

#define	PEN			  		256
#define	O_G					512
#define	CREDIT_TEAMa	 	4
#define	CREDIT_TEAMb	 	8
#define	GOAL_DISPLAYED		16

#define	USA 					0
#define	RUS					1
#define	SPN					2
#define	BUL					3
#define	BEL					4
#define	DEN					5
#define	NIR					6
#define	TUN					7
#define	ZAM					8
#define	SWZ					9
#define	CAM					10
#define	SKR					11
#define	ITA					12
#define	MOR					13
#define	ENG					14
#define	SCO					15
#define	WAL					16
#define	EGY					17
#define	COL					18
#define	SWE					19
#define	ARG					20
#define	EIR					21
#define	HOL					22
#define	FIN					23
#define	SLV					24
#define	IVR					25
#define	GHA					26
#define	ROM					27
#define	GER					28
#define	GRE					29
#define	NOR					30
#define	SAU					31
#define	FRA					32
#define	POL					33
#define	JAP					34
#define	URU					35
#define	BRA					36
#define	NIG					37
#define	MEX					38
#define	CZE					39
#define	ICE					40
#define	POR					41
#define	CHI					42
#define	BOL					43
#define  GRM					44

#define	WHT			  		45
#define	BLU			  		46

#define	F_4_3_3				0
#define	F_5_3_2				1
#define	F_6_3_1				2
#define	F_4_2_4				3
#define	F_5_1_4				4
#define	F_4_0_6				5
#define	F_3_1_6				6
#define	F_4_1_5				7
#define	F_5_2_3				8
#define	F_4_4_2				9

#define TRUE 					1
#define FALSE 					0
#define LARGE					0
#define SMALL					8
#define SHADOW					2

#define 	ACTIVE				1
#define 	INACTIVE				0
#define 	DELETE_OLD_SPRITE	2
#define 	OLD_SPRITE_FLAG	4
#define 	FREEZE				16*2
#define	REMOVE				32*2	
#define	INVISIBLE			64*2
#define	HALF_SPIN			128*2
#define	START_SPIN			256*2
#define	SINGLE_SPIN		 	512*2
#define	BACK_SPIN		 	1024*2
#define	MINI_BUTTON			2048*2
#define	STANDARD_BUTTON	4096*2
#define	SpriteON				8192*2

#define  PALETTE_FADE_UP	1
#define  PALETTE_FADE_DOWN	3

#define  REPL_BKG				1
#define  EDIT_TEXT			2
#define	MOUSE_OFF			4
#define  MARK_TEXT			16
#define	ENTER_NUMBER		32

#define  LEFT_BUTTON			1
#define  RIGHT_BUTTON 		2

#define SHADOWtextOFF			0
#define SHADOWtextON				1
#define RIGHTjustifyTEXT		2
#define SFONT						4
#define MFONT						8
#define BFONT						16
#define CAPS						32
#define TIGHTEN					64
#define CHISEL			  	   	128
#define SILVER_TEXTURE	   	512
#define COPY_TO_BACK		   	1024
#define CENTREjustifyTEXT		4096
#define BUTTONcentreJUSTIFY	32768

									
#define SHADOWimageON  			1
#define SHADOWimageOFF			0

#define MENU_1						1
#define MENU_2						2
#define MENU_3						3
#define MENU_4						4
#define MENU_5						5
#define MENU_6						6
#define MENU_7						7
#define MENU_8						8
#define MENU_9						9
#define MENU_10					10

#define	CURSOR_COLOUR		((9*16)+0)
#define	BLACK					((0*16)+1)
#define	GREY					(((1*16)+0)-6)
#define	CYAN					((11*16)+12)
#define	GREEN					((11*16)+10)
#define	GREEN2				((4*16)+4)
#define	BRIGHTER_GREEN2	((4*16)+10)

#define	BRIGHT_WHITE		((1*16)+15)
#define	DULL_WHITE			((1*16)+10)
#define	BRIGHT_GRAY			((1*16)+5)
#define	DULL_GRAY			((1*16)+0)
#define	BRIGHT_GREEN		((11*16)+9)
#define	DULL_GREEN			((11*16)+10)

#define	BRIGHT_GREY			((1*16)+0)
#define	BRIGHT_YELLOW	 	((11*16)+7)
#define	BRIGHT_CYAN			((11*16)+11)

#define	BRIGHT_GREEN		((11*16)+9)
#define	BRIGHT_RED			((7*16)+12)

#define	RED_TEXT						130
#define	GREEN_STAR					75
#define	YELW_STAR					146
#define	RED_STAR						111
#define	MARK_TEXT_COLOUR			20
#define	SELECTED_TEXT_COLOUR		BRIGHT_CYAN
#define	MAX_IMAGES					18
#define	MAX_STRINGS					44
#define	MAX_LABELS					40
#define	MAX_BUTTONS					11
#define	MAX_SPRITES					44
#define	MAX_FORMATIONS				10
#define	MAX_COPIES 					128
 
#define	COACH_TEXT					1
#define	FLAIR_TEXT					2
#define	ACCURACY_TEXT				3
#define	CNTRL_TEXT					4
#define	PACE_TEXT					5
#define	VISION_TEXT					6
#define	POWER_TEXT					7
#define	STAMINA_TEXT				8
#define	DISCIPLINE_TEXT  			9
#define	PLAY_STATS_TEXT			10
#define	SKILL_TEXT					11
#define	PERC_0_TEXT					12
#define	PERC_50_TEXT				13
#define	PERC_100_TEXT				14
#define	EDIT_DATA_TEXT				15
#define	SQUAD_CHOOSE_TEXT			16
#define	ONE_TXT						17
#define	TWO_TXT						18
#define	THREE_TXT					19
#define	FOUR_TXT						20
#define	FIVE_TXT						21
#define	SIX_TXT						22
#define	SEVEN_TXT					23
#define	EIGHT_TXT					24
#define	NINE_TXT						25
#define	TEN_TXT						26
#define	ELEVEN_TXT					27
#define	TWELVE_TXT					28
#define	THIRTEEN_TXT				29
#define	FOURTEEN_TXT				30
#define	FIFTEEN_TXT					31
#define	SIXTEEN_TXT					32
#define	SEVENTEEN_TXT 				33
#define	EIGHTEEN_TXT	 			34
#define	NINETEEN_TXT	 			35
#define	TWENTY_TXT		 			36
#define	TWENTYONE_TXT	 			37
#define	TWENTYTWO_TXT	 			38
#define	ENVIRONMENT_TEXT			39
#define	PLY1_SELECT_TEXT			40
#define	PLY2_SELECT_TEXT			41
#define	PLY3_SELECT_TEXT			42
#define	PLY4_SELECT_TEXT			43
#define	COMMENTARY_TEXT 			44
#define	PARTICIPATING_TEXT		45
#define	NO_TEAMS_TEXT				46	
#define	SKY_TXT						47
#define	STADIUM_TXT					48
#define	LINE_TXT						49		
#define	VIDEO_TXT					50
#define	PLY_DET_TEXT				51
#define	PTCH_DET_TEXT				52
#define	RES_TXT						53
#define	CAM_TEXT						54
#define	SCRN_TEXT					55
#define	CROWD_TEXT					56
#define	COMM_TEXT					57
#define	MSTR_TEXT					58
#define	PITCH_TXT					59
#define	MUSIC_TXT					60
#define	AUDIO_TXT					61
#define	AUDIO_SND_TEXT				62
#define	MATCH_TEXT					63
#define	VENUE_TXT					64
#define	LGE_TBL_TEXT				65
#define	RANK_A_TEXT					66
#define	RANK_B_TEXT					67
#define	RANK_C_TEXT					68
#define	RESULT_TEXT					69
#define	END_SEASON_TEXT			70
#define	CHAMPS_TEXT					71
#define	RELIGATED_TEXT				72
#define	PROMOTED_TEXT				73
#define	REL_B_TEXT					74
#define	PRO_C_TEXT					75
#define	NO_NET_PLAYS_TEXT			76
#define	CHOOSE_TEXT					77
#define	CUP_WINNERS_TEXT			78
#define	RUNNERS_UP_TEXT			79
#define	CONTROLS_TEXT				80
#define	MEDIA_TEXT					81
#define	RULES_TEXT					82
#define	CALIBRATION_TEXT			83
#define	OFFSIDE_TXT					84
#define	SUBS_TXT						85
#define	FREEKICKS_TXT				86
#define	GAME_LEN_TEXT				87
#define	BOOKING_TXT					88
#define	WIND_TXT						89
//#define	QUIT_TEXT 					90
#define	DETAIL_TEXT					91
#define	START_TEXT					92
#define	CUSTOM_TEXT					93

#define	SAVE_TEXT 					94
#define	LOAD_TEXT 					95
#define	MATCH_SETUP_TXT			96
#define	CONTROL_TEXT				97
#define	SELECTION_TEXT				98
#define	NEXT_TEXT					99
#define	SETUP_TXT					101
#define	AUTOMAN_TEXT				102
#define	GROUP_A_TEXT				103
#define	GROUP_B_TEXT				104
#define	GROUP_C_TEXT				105
#define	SOUND_TEXT					106
#define	RANDOM_TEXT					107
#define	FRIENDLY_TEXT				108
#define	EXTRA_TIME_TEXT			109
#define	WON_TEXT						110
#define	ON_PENS_TEXT				111
#define	NETWORK_GAME_TEXT			112
#define	COMPUTER_TEXT				113
#define	PLAYER_ONE_TEXT 			114
#define	PLAYER_TWO_TEXT		   115
#define	PLAYER_THREE_TEXT			116
#define	PLAYER_FOUR_TEXT			117
#define	OFF_TEXT						118
#define	ON_TEXT						119
#define	LOW_TEXT						120
#define	HIGH_TEXT					121
#define	MED_TEXT						122
#define	WIRE_TEXT					123
#define	FAR_TEXT						124
#define	PLAN_TEXT  					125
#define	GLINE_TEXT					126
#define	ISO_TEXT						127
#define	PLYR_TEXT					128
#define	REF_TEXT						129
#define	MONO_TEXT					130
#define	THREEd_TEXT					131
#define	ARCADE_TEXT					132
#define	SIMULATION_TEXT			133
#define	LEAGUE_TEXT					134
#define	CUP_TEXT						135
#define	DONE_TEXT2					136
#define	WAITING_TEXT				137
#define	KEY1_TEXT					138
#define	KEY2_TEXT					139
#define	JOY1_TEXT					140
#define	JOY2_TEXT					141
#define	MOUSE_TEXT					142
#define	GRAV1_TEXT					143
#define	GRAV2_TEXT					144
#define	RND1_TEXT					145
#define	RND2_TEXT					146
#define	QUTR_TEXT					147
#define	SEMI_TEXT					148
#define	FINAL_TEXT					149
#define	DIVISION1_TEXT				150
#define	DIVISION2_TEXT				151
#define	DIVISION3_TEXT				152
#define	After_Extra_TEXT			153
#define	Pd_TEXT						154
#define	Won_TEXT						155
#define	Drew_TEXT					156
#define	Lost_TEXT					157
#define	For_TEXT						158
#define	Against_TEXT				159
#define	Pts_TEXT						160
#define	GoalDiff_TEXT				161
#define	TEXT1							162							
#define	TEXT2							163
#define	TEXT3							164
#define	TEXT4							165
#define	TEXT5							166
#define	TEXT6							167
#define	TEXT7							168
#define	TEXT8							169
#define	TEXT9							170
#define	TEXT10						171
#define	TEXT11						172
#define	COACH_TEXT2					173
#define	TEAM_SELECT_TEXT			174
#define	SLOT_TITLE_TEXT			175
#define	PLAYR_TEXT					176
#define	CONTROL_METHOD_TEXT		177
#define	ROUND_UP_TEXT				178
#define	NET_SELECT_TEXT			179
#define	CENTRE_TEXT					180
#define	NEW_TEXT						181
#define	ON_PENALTIES_TEXT 		182
#define	ON_PENALTIES_TEXT2 		183
#define	CUP_WINNERS_TEXTa			184
#define	CUP_WINNERS_TEXTb			185
#define	NOT_USED_TEXT				186
#define	UNTITLED_TEXT				187
#define	NETWORK_ABORT_TEXT		188
#define	NETWORK_SYNC_TEXT			189
#define	LOADING_TEXT				190
#define	PRACTICE_TEXT				191
#define	REQUEST_DIR_TEXT			192	// 6 entries here
#define	CD_TEXT						198
#define	OVER10PEN_TEXT				199
#define	OVER10PEN_TEXT2 			200

#define	MOUSE_ERROR_TEXT			201
#define	SOUND_ERROR_TEXT			202
#define	CONFG_ERROR_TEXT			203
#define	DFILE_ERROR_TEXT			204
#define	MFILE_ERROR_TEXT			205
#define	INI3d_ERROR_TEXT			206
#define	MEMOY_ERROR_TEXT			207
#define	REDEF_TEXT					208
#define	OG_TEXT						209
#define	PEN_TEXT						210

#define	DEMO1_TEXT 					211
#define	DEMO2_TEXT					212
#define	DEMO3_TEXT					213
#define	DEMO4_TEXT					214
#define	DEMO5_TEXT					215
#define	DEMO6_TEXT					216
#define	DEMO7_TEXT					217
#define	DEMO8_TEXT					218
#define	DEMO9_TEXT					219
#define	DEMO10_TEXT					220
#define	DEMO11_TEXT					221
#define	DEMO12_TEXT					222
#define	DEMO13_TEXT					223
#define	DEMO14_TEXT					224
#define	DEMO15_TEXT					225
#define	DEMO16_TEXT					226
#define	DEMO17_TEXT					227
#define	DEMO18_TEXT					228
#define	DEMO19_TEXT					229
#define	WHEEL1_TEXT					230
#define	WHEEL2_TEXT					231
#define	WHEEL3_TEXT					232
#define	SECURITY_TEXT				233
#define	WHEEL_ERROR_TEXT			234
#define	MANUAL_PAGE_TEXT 			235




#define	NoOfPLAYERS_TEXT		  	241
#define	GAMEtype_TEXT		  		242
#define	COMPETITION_TEXT		  	244
#define	TEAM_NAMEa			 		243		
#define	TEAM_NAMEb			 		245
#define	VENUE_TEXT				  	246
#define	TEAM_NAMEa_SCORE	 		255
#define	TEAM_NAMEb_SCORE			256
#define	TEAMa_SCORER 				257
#define	TEAMb_SCORER				258
#define	GAMETYPE_TEXT	  			259
#define	TEAM_SEASON_END		 	260
#define	PLAYER_NAME_TEAMa			261
#define	PLAYER_NAME_TEAMb			262
#define	NETWORK_TEXT		  		264
#define	WINNERS_NAME		 		265
#define	RUNNERS_UP_NAME	 		266
											
#define  ONE_TEXT                267
#define  TWO_TEXT                268
#define  THREE_TEXT              269
#define  FOUR_TEXT               270
#define  CONTROL_1_TEXT          271
#define  CONTROL_2_TEXT				272
#define  CONTROL_3_TEXT				273
#define  CONTROL_4_TEXT				274
#define  JOYSTICK_TEXT				276
#define  OFFSIDE_TEXT				277
#define  SUBS_TEXT					278
#define  FREEKICKS_TEXT				279
#define  TIME_TEXT					280
#define  BOOKING_TEXT				281
#define  WIND_TEXT					282
#define	REFEREE_NAME			 	283
#define	REFEREE_COUNTRY		 	284
#define	SLOT_NAME					285
#define	SLOT_STATE					286
#define	SLOT_TITLE					287
#define	PLAYER_LABEL		 		288
#define	CONTROL_STATE	 			289
#define	CALIBRATE_TEXT				290		  		
#define	PLAYER_NAME					291
#define	KEY_TYPE					 	292
#define	COACH_NAME					293
#define	REQUEST_TEXT				294
#define	CHOSEN_KEY					295
#define	REDEFINE_TEXT				296
#define	RESULT_TEAM_NAMEa			297
#define	RESULT_TEAM_NAMEb			298
#define	RESULT_TEAMa			  	299
#define	RESULT_TEAMb			  	300
#define	ROUNDUP_CONCLUSION 		301
#define	PLAYER_NAME_WITH_POSN	302
#define	PLAYER_STAT					303
#define	SELECTED_PLAYER_NAME		304
#define	SELECTED_TEAM_NAME		305
#define	PLAYER_FORMATION			306
#define	LEAGUE_TEAM					307
#define	PARTICIPATING_TEAM_NAME	308
#define	CHOOSE_TEAM_NAME			309
#define	FORMATION_TEXT		 		310
#define	SKY_TEXT						311
#define	STADIUM_TEXT	  			312
#define	PITCH_TEXT	  				313
#define	PLAYER_TEXT		  			314
#define	LINE_TEXT	  				315
#define	VIDI_TEXT	  				316
#define	RES_TEXT	  					317
#define	CAMERA_TEXT	  				318
#define	SIZE_TEXT	  				319
#define	AUDIO_TEXT	  				320
#define	WINDOW1_TEXT				321
#define	WINDOW2_TEXT				322
#define	WINDOW3_TEXT				323
#define	WHEEL_NUMBER				324
#define	MANUAL1_TEXT				325
#define	MANUAL2_TEXT				326
#define	MANUAL3_TEXT				327
#define	MANUAL4_TEXT				328
#define	MANUAL_NO1		 			329
#define	MANUAL_NO2		 			330
#define	MANUAL_NO3		 			331
#define	MANUAL_WORD					332
#define	RANK_HEADING				333
#define	DOS_TEXT						334
#define	CUSTOMISE_TEXT				335


#define	HIGHLIGHTED_TEXT			1
#define	EDITABLE_TEXT				2
#define	REPRINT_TEXT 				4
#define	SELECTABLE_TEXT			8
#define	SKIP_PSUDO_RESTORE		16
#define	SKIP_COPY_DOWN				32
#define	TOGGLE_FLAG			 		64
#define	HOVERING_OVER_TEXT	 	128
#define	NET_FLAG						512

// definitions used for special print stuff!!!

#define	LEAGUE_DATA				16384		//128
#define	SCORER_DATA				8192		//128

#define	PLAYER_NAME_LEN				19
#define	COACH_NAME_LEN					18+5
#define	PLAYER_MAX_PIXEL_LEN			(240-28)
#define	COACH_MAX_PIXEL_LEN			(300-18)+32
#define	TEAM_NAME_LEN					22
#define	NickNAME_LEN					12

#define	MAX_TEAMS						45
#define 	MAX_GOALS						91	
#define	MAX_LINES				  		5
												
#define	KIT_BUTTON						100
#define	ACTUA_BUTTON					101
#define	WAVE_BUTTON						102
#define	FLAG_BUTTON	 					103
#define	CLICK_BUTTON	 				104
#define	SILVER_CUP_BUTTON				105
#define	TEAMS_BUTTON					106
#define	TEST_BUTTON						107
#define	SLIDE_BAR	 					108
#define	SPIN_BUTTON	 					109
#define	UP_ARROW_BUTTON				110
#define	DOWN_ARROW_BUTTON				111
#define	SELECTION_BUTTON				112
#define	REF_BUTTON						113



#define	DEBOUNCE_BUTTONS					128

#define	NO_MOUSE								254
#define	QUIT									255
#define	UPDATE_DISPLAY						1

struct button_info {
	int			button_type;
	int			button_index;
	int			button_flags;
	short			button_xposn;
	short			button_yposn;
	short			buttonShadow_xposn;
	short			buttonShadow_yposn;
	int			button_left_select;
	int			button_right_select;
	short 		BoundingBoxLeft;
	short 		BoundingBoxTop;
	short 		BoundingBoxRight;
	short 		BoundingBoxBottom;
	int			FrameCounter;
	int			FrameSpeed;
	int			NoOfFrames;
	short			CopyWidth;
	short			CopyHeight;
	int			LastButtonNo;
	int			border_frame;
	int			button_text;
	
            		 };

struct sprite_info {
	int			sprite_state;
	int			sprite_flags;
	int			sprite_type;
	short			sprite_xposn;
	short			sprite_yposn;
	short			spriteShadow_xposn;
	short			spriteShadow_yposn;
	short			CopyAreaX;
	short			CopyAreaY;
	short			CopyWidth;
	short			CopyHeight;
	int			LastSpriteNo;
	int			FrameCounter;
	int			FrameSpeed;
	int			NoOfFrames;
	int			NewSpriteFrame;
            		 };



struct string_info	{
					int	string_type;
					int	string_array;
					int	stat_array;
					int	string_flags;
					short	string_xposn;
					short	string_yposn;
					short	string_colour;
					short string_mark_colour;
					int	string_shadow;
					int	max_string_chars;
					int	max_string_size;
					short BoundingBoxLeft;
					short BoundingBoxTop;
					short BoundingBoxRight;
					short BoundingBoxBottom;
					short	CopyAreaX;
					short	CopyAreaY;
					short	CopyWidth;
					short	CopyHeight;
	     					};

typedef struct {

	int				BkgBITMAPfile;
	int				HeaderBITMAPfile;
	short				HeaderXposn;
	short				HeaderYposn;
	int				PaletteDATAfile;
	short				ImageLIST[MAX_IMAGES];
	short				LabelLIST[MAX_LABELS];
	string_info		StringLIST[MAX_STRINGS];
	button_info		ButtonLIST[MAX_BUTTONS];
	sprite_info		SpriteTABLE[MAX_SPRITES];	
					}menu;


struct control_data	{
	int				control_type;
	short				control_yoff;
	char				control_mask;
						};

typedef	struct	{
	control_data	 controlLIST[4];
					}controls;


typedef struct {
	unsigned	long	offset;
	unsigned	long	size;
					}offset_file;

typedef struct {

	short			LabelXposn;
	short			LabelYposn;
	short			LabelColour;
	char			TextLabel;
	int			LabelShadow;

            	}label;

typedef struct {

	short			ImageXposn;
	short			ImageYposn;
	short			ImageShadowXposn;
	short			ImageShadowYposn;
	int			ImageNumber;
	int			ImageState;

            	}image;


typedef struct {

	int			spriteWidth;
	int			spriteHeight;
	long			spriteOffset;

            	}sprite;

#define	PACE					0
#define	POWER					1
#define	CONTROL				2
#define	FLAIR					3
#define	VISION				4
#define	ACCURACY				5
#define	STAMINA				6
#define	DISCIPLINE			7
#define	REFS_VISION			8
#define	REFS_DISCIPLINE	9

#define	SUBSTITUTE 			1
#define	DISCIPLINARY_PTS	2


typedef	struct 
{
	char			name[PLAYER_NAME_LEN+1];
	char			goal_index;

	char			pace;
	char			power;
	char			control;
	char			flair;
	char			vision;
	char			accuracy;
	char			stamina;
	char			discipline;

	char 			flags;

	char			squad_number;
	char			position;	
	char			skin_tone;
}player_info;

struct referee_info
{
	char			name[PLAYER_NAME_LEN+1];
	char			vision;
	char			discipline;
	short 		country;
};

struct	restore_data
{
	int			division;
	int			position;	
};	

struct	demo_struct
{
	int			team_a;
	int			team_b;	
	int			random;	
	int			stadium;	
	int			referee;	
};	


struct team_info
{
	char 			name[TEAM_NAME_LEN+1];
	char 			coachname[COACH_NAME_LEN+1];
	int			division;
	int			position;	
	int			played;
	int			won;
	int			drew;
	int			lost;
	int			goals_for;
	int			goals_against;
	int			points;
	int			goal_diff;
	int			team_no;		
	char 			Nickname[NickNAME_LEN+1];
	int			ranking,team_number;
	char			player_control,fixture_no;
	int			big_flag;
	int			formation;
	int			auto_formation;
	int			cup_key;
	char 			country_code[3];	// Country Code for Samples
	int			computer_formation;
	player_info	players[22];

};

#define	PITCH_WID		269
#define	PITCH_HI			169

struct formation_info
{
	char 			formation_no[3];
	short			formation_xposn;
	short			formation_yposn;
	int			formation_flags;
	char			position_type;
};

#define			GK			0
#define			DF			1
#define			MD			2
#define			FD			3

struct team_formation
{
	formation_info	formations[22];
};


struct	swap_player_buffer
{
	player_info	players[1];
};	


struct 	redefine_info
{
					short	string_xposn;
					short	string_yposn;
};



//#define		sprite1width		14
//#define		sprite1height		28
//#define		sprite1Bitmap		0
//
//#define		sprite1awidth		14
//#define		sprite1aheight		28
//#define		sprite1aBitmap		(sprite1width*sprite1height)+sprite1Bitmap
//
//#define		sprite1bwidth		14
//#define		sprite1bheight		28
//#define		sprite1bBitmap		(sprite1awidth*sprite1aheight)+sprite1aBitmap
//
//#define		sprite2width		21
//#define		sprite2height		21
//#define		sprite2Bitmap		(sprite1bwidth*sprite1bheight)+sprite1bBitmap
//
//#define		sprite3width		21
//#define		sprite3height		19
//#define		sprite3Bitmap		(sprite2width*sprite2height)+sprite2Bitmap
//
//#define		sprite4width		21
//#define		sprite4height		19
//#define		sprite4Bitmap		(sprite3width*sprite3height)+sprite3Bitmap
//
//#define		sprite5width		21
//#define		sprite5height		19
//#define		sprite5Bitmap		(sprite4width*sprite4height)+sprite4Bitmap
//
//#define		sprite6width		21
//#define		sprite6height		19
//#define		sprite6Bitmap		(sprite5width*sprite5height)+sprite5Bitmap
//
//#define		sprite7width		21
//#define		sprite7height		19
//#define		sprite7Bitmap		(sprite6width*sprite6height)+sprite6Bitmap
//
//#define		sprite8width		21
//#define		sprite8height		19
//#define		sprite8Bitmap		(sprite7width*sprite7height)+sprite7Bitmap
//
//#define		sprite9width		23
//#define		sprite9height		19
//#define		sprite9Bitmap		(sprite8width*sprite8height)+sprite8Bitmap
//
//
//#define		sprite10width		571
//#define		sprite10height		29
//#define		sprite10Bitmap		(sprite9width*sprite9height)+sprite9Bitmap
//
//#define		sprite11width		69
//#define		sprite11height		82
//#define		sprite11Bitmap		(sprite10width*sprite10height)+sprite10Bitmap
//
//#define		sprite12width		69
//#define		sprite12height		82
//#define		sprite12Bitmap		(sprite11width*sprite11height)+sprite11Bitmap
//
//#define		sprite13width		69
//#define		sprite13height		82
//#define		sprite13Bitmap		(sprite12width*sprite12height)+sprite12Bitmap
//
//#define		sprite14width		69
//#define		sprite14height		82
//#define		sprite14Bitmap		(sprite13width*sprite13height)+sprite13Bitmap
//
//#define		sprite15width		69
//#define		sprite15height		82
//#define		sprite15Bitmap		(sprite14width*sprite14height)+sprite14Bitmap
//
//#define		sprite16width		69
//#define		sprite16height		82
//#define		sprite16Bitmap		(sprite15width*sprite15height)+sprite15Bitmap
//
//#define		sprite17width		69
//#define		sprite17height		82
//#define		sprite17Bitmap		(sprite16width*sprite16height)+sprite16Bitmap
//
//#define		sprite18width		69
//#define		sprite18height		82
//#define		sprite18Bitmap		(sprite17width*sprite17height)+sprite17Bitmap
//
//#define		sprite19width		69
//#define		sprite19height		82
//#define		sprite19Bitmap		(sprite18width*sprite18height)+sprite18Bitmap
//
//#define		sprite20width		69
//#define		sprite20height		82
//#define		sprite20Bitmap		(sprite19width*sprite19height)+sprite19Bitmap
//
//#define		sprite21width		69
//#define		sprite21height		82
//#define		sprite21Bitmap		(sprite20width*sprite20height)+sprite20Bitmap
//
//#define		sprite22width		69
//#define		sprite22height		82
//#define		sprite22Bitmap		(sprite21width*sprite21height)+sprite21Bitmap
//
//#define		sprite23width		69
//#define		sprite23height		82
//#define		sprite23Bitmap		(sprite22width*sprite22height)+sprite22Bitmap
//
//#define		sprite24width		69
//#define		sprite24height		82
//#define		sprite24Bitmap		(sprite23width*sprite23height)+sprite23Bitmap
//
//#define		sprite25width		69
//#define		sprite25height		82
//#define		sprite25Bitmap		(sprite24width*sprite24height)+sprite24Bitmap
//
//#define		sprite26width		69
//#define		sprite26height		82
//#define		sprite26Bitmap		(sprite25width*sprite25height)+sprite25Bitmap
//
//#define		sprite27width		69
//#define		sprite27height		82
//#define		sprite27Bitmap		(sprite26width*sprite26height)+sprite26Bitmap
//
//#define		sprite28width		69
//#define		sprite28height		82
//#define		sprite28Bitmap		(sprite27width*sprite27height)+sprite27Bitmap
//
//#define		sprite29width		69
//#define		sprite29height		82
//#define		sprite29Bitmap		(sprite28width*sprite28height)+sprite28Bitmap
//
//#define		sprite30width		69
//#define		sprite30height		82
//#define		sprite30Bitmap		(sprite29width*sprite29height)+sprite29Bitmap
//
//#define		sprite31width		69
//#define		sprite31height		82
//#define		sprite31Bitmap		(sprite30width*sprite30height)+sprite30Bitmap
//
//#define		sprite32width		69
//#define		sprite32height		82
//#define		sprite32Bitmap		(sprite31width*sprite31height)+sprite31Bitmap
//
//#define		sprite33width		69
//#define		sprite33height		82
//#define		sprite33Bitmap		(sprite32width*sprite32height)+sprite32Bitmap
//
//#define		sprite34width		69
//#define		sprite34height		82
//#define		sprite34Bitmap		(sprite33width*sprite33height)+sprite33Bitmap
//
//#define		sprite35width		69
//#define		sprite35height		82
//#define		sprite35Bitmap		(sprite34width*sprite34height)+sprite34Bitmap
//
//#define		sprite36width		69
//#define		sprite36height		82
//#define		sprite36Bitmap		(sprite35width*sprite35height)+sprite35Bitmap
//
//#define		sprite37width		69
//#define		sprite37height		82
//#define		sprite37Bitmap		(sprite36width*sprite36height)+sprite36Bitmap
//
//#define		sprite38width		69
//#define		sprite38height		82
//#define		sprite38Bitmap		(sprite37width*sprite37height)+sprite37Bitmap
//
//#define		sprite39width		69
//#define		sprite39height		82
//#define		sprite39Bitmap		(sprite38width*sprite38height)+sprite38Bitmap
//
//#define		sprite40width		69
//#define		sprite40height		82
//#define		sprite40Bitmap		(sprite39width*sprite39height)+sprite39Bitmap
//
//#define		sprite41width		69
//#define		sprite41height		82
//#define		sprite41Bitmap		(sprite40width*sprite40height)+sprite40Bitmap
//
//#define		sprite42width		69
//#define		sprite42height		82
//#define		sprite42Bitmap		(sprite41width*sprite41height)+sprite41Bitmap
//
//#define		sprite43width		69
//#define		sprite43height		82
//#define		sprite43Bitmap		(sprite42width*sprite42height)+sprite42Bitmap
//
//#define		sprite44width		69
//#define		sprite44height		82
//#define		sprite44Bitmap		(sprite43width*sprite43height)+sprite43Bitmap
//
//#define		sprite45width		69
//#define		sprite45height		82
//#define		sprite45Bitmap		(sprite44width*sprite44height)+sprite44Bitmap
//
//#define		sprite46width		69
//#define		sprite46height		82
//#define		sprite46Bitmap		(sprite45width*sprite45height)+sprite45Bitmap
//
//#define		sprite47width		69
//#define		sprite47height		82
//#define		sprite47Bitmap		(sprite46width*sprite46height)+sprite46Bitmap
//
//#define		sprite48width		69
//#define		sprite48height		82
//#define		sprite48Bitmap		(sprite47width*sprite47height)+sprite47Bitmap
//
//#define		sprite49width		69
//#define		sprite49height		82
//#define		sprite49Bitmap		(sprite48width*sprite48height)+sprite48Bitmap
//
//#define		sprite50width		69
//#define		sprite50height		82
//#define		sprite50Bitmap		(sprite49width*sprite49height)+sprite49Bitmap
//
//#define		sprite51width		69
//#define		sprite51height		82
//#define		sprite51Bitmap		(sprite50width*sprite50height)+sprite50Bitmap
//
//#define		sprite52width		69
//#define		sprite52height		82
//#define		sprite52Bitmap		(sprite51width*sprite51height)+sprite51Bitmap
//
//#define		sprite53width		69
//#define		sprite53height		82
//#define		sprite53Bitmap		(sprite52width*sprite52height)+sprite52Bitmap
//
//#define		sprite54width		69
//#define		sprite54height		82
//#define		sprite54Bitmap		(sprite53width*sprite53height)+sprite53Bitmap
//
//#define		sprite55width		69
//#define		sprite55height		82
//#define		sprite55Bitmap		(sprite54width*sprite54height)+sprite54Bitmap
//
//#define		sprite55Bwidth		69
//#define		sprite55Bheight	82
//#define		sprite55BBitmap	(sprite55width*sprite55height)+sprite55Bitmap
//
//#define		sprite55Cwidth		69
//#define		sprite55Cheight	82
//#define		sprite55CBitmap	(sprite55Bwidth*sprite55Bheight)+sprite55BBitmap
//
//#define		sprite56width		571
//#define		sprite56height		29
//#define		sprite56Bitmap		(sprite55Cwidth*sprite55Cheight)+sprite55CBitmap
//
//#define		sprite57width		192	//161
//#define		sprite57height		75		//51
//#define		sprite57Bitmap		(sprite56width*sprite56height)+sprite56Bitmap
//
//#define		sprite58width		272
//#define		sprite58height		176
//#define		sprite58Bitmap		(sprite57width*sprite57height)+sprite57Bitmap
//
//#define		sprite59width		138
//#define		sprite59height		75
//#define		sprite59Bitmap		(sprite58width*sprite58height)+sprite58Bitmap
//
//#define		sprite60width		1
//#define		sprite60height		1
//#define		sprite60Bitmap		(sprite59width*sprite59height)+sprite59Bitmap
//
//#define		sprite61width		541
//#define		sprite61height		5
//#define		sprite61Bitmap		(sprite60width*sprite60height)+sprite60Bitmap
//
//#define		sprite62width		1
//#define		sprite62height		1
//#define		sprite62Bitmap		(sprite61width*sprite61height)+sprite61Bitmap
//
//#define		sprite63width		64
//#define		sprite63height		88
//#define		sprite63Bitmap		(sprite62width*sprite62height)+sprite62Bitmap
//
//#define		sprite64width		64
//#define		sprite64height		88
//#define		sprite64Bitmap		(sprite63width*sprite63height)+sprite63Bitmap
//
//#define		sprite65width		64
//#define		sprite65height		88
//#define		sprite65Bitmap		(sprite64width*sprite64height)+sprite64Bitmap
//
//#define		sprite66width		64
//#define		sprite66height		88
//#define		sprite66Bitmap		(sprite65width*sprite65height)+sprite65Bitmap
//
//#define		sprite67width		64
//#define		sprite67height		88
//#define		sprite67Bitmap		(sprite66width*sprite66height)+sprite66Bitmap
//
//#define		sprite68width		64
//#define		sprite68height		88
//#define		sprite68Bitmap		(sprite67width*sprite67height)+sprite67Bitmap
//
//#define		sprite69width		64
//#define		sprite69height		88
//#define		sprite69Bitmap		(sprite68width*sprite68height)+sprite68Bitmap
//
//#define		sprite70width		64
//#define		sprite70height		88
//#define		sprite70Bitmap		(sprite69width*sprite69height)+sprite69Bitmap
//
//#define		sprite71width		64
//#define		sprite71height		88
//#define		sprite71Bitmap		(sprite70width*sprite70height)+sprite70Bitmap
//
//#define		sprite72width		64
//#define		sprite72height		88
//#define		sprite72Bitmap		(sprite71width*sprite71height)+sprite71Bitmap
//
//#define		sprite73width		64
//#define		sprite73height		88
//#define		sprite73Bitmap		(sprite72width*sprite72height)+sprite72Bitmap
//
//#define		sprite74width		64
//#define		sprite74height		88
//#define		sprite74Bitmap		(sprite73width*sprite73height)+sprite73Bitmap
//
//#define		sprite75width		64
//#define		sprite75height		88
//#define		sprite75Bitmap		(sprite74width*sprite74height)+sprite74Bitmap
//
//
//#define		sprite76width		133
//#define		sprite76height		144
//#define		sprite76Bitmap		(sprite75width*sprite75height)+sprite75Bitmap
//
//#define		sprite77width		133
//#define		sprite77height		144
//#define		sprite77Bitmap		(sprite76width*sprite76height)+sprite76Bitmap
//
//#define		sprite78width		133
//#define		sprite78height		144
//#define		sprite78Bitmap		(sprite77width*sprite77height)+sprite77Bitmap
//
//#define		sprite79width		133
//#define		sprite79height		144
//#define		sprite79Bitmap		(sprite78width*sprite78height)+sprite78Bitmap
//
//#define		sprite80width		31
//#define		sprite80height		33
//#define		sprite80Bitmap		(sprite79width*sprite79height)+sprite79Bitmap
//
//#define		sprite81width		31
//#define		sprite81height		35
//#define		sprite81Bitmap		(sprite80width*sprite80height)+sprite80Bitmap
//
//#define		sprite82width		51
//#define		sprite82height		33
//#define		sprite82Bitmap		(sprite81width*sprite81height)+sprite81Bitmap
//
//#define		sprite83width		60
//#define		sprite83height		35
//#define		sprite83Bitmap		(sprite82width*sprite82height)+sprite82Bitmap
//
//#define		sprite84width		180
//#define		sprite84height		45
//#define		sprite84Bitmap		(sprite83width*sprite83height)+sprite83Bitmap
//
//#define		sprite85width		180
//#define		sprite85height		45
//#define		sprite85Bitmap		(sprite84width*sprite84height)+sprite84Bitmap
//
//#define		sprite86width		180
//#define		sprite86height		45
//#define		sprite86Bitmap		(sprite85width*sprite85height)+sprite85Bitmap
//
//#define		sprite87width		180
//#define		sprite87height		45
//#define		sprite87Bitmap		(sprite86width*sprite86height)+sprite86Bitmap
//
//#define		sprite88width		180
//#define		sprite88height		45
//#define		sprite88Bitmap		(sprite87width*sprite87height)+sprite87Bitmap
//
//#define		sprite89width		180
//#define		sprite89height		45
//#define		sprite89Bitmap		(sprite88width*sprite88height)+sprite88Bitmap
//
//#define		sprite90width		180
//#define		sprite90height		45
//#define		sprite90Bitmap		(sprite89width*sprite89height)+sprite89Bitmap
//
//#define		sprite91width		180
//#define		sprite91height		45
//#define		sprite91Bitmap		(sprite90width*sprite90height)+sprite90Bitmap
//
//#define		sprite92width		180
//#define		sprite92height		45
//#define		sprite92Bitmap		(sprite91width*sprite91height)+sprite91Bitmap
//
//#define		sprite93width		180
//#define		sprite93height		45
//#define		sprite93Bitmap		(sprite92width*sprite92height)+sprite92Bitmap
//
//#define		sprite94width		180
//#define		sprite94height		45
//#define		sprite94Bitmap		(sprite93width*sprite93height)+sprite93Bitmap
//
//#define		sprite95width		180
//#define		sprite95height		45
//#define		sprite95Bitmap		(sprite94width*sprite94height)+sprite94Bitmap
//
//#define		sprite96width		180
//#define		sprite96height		45
//#define		sprite96Bitmap		(sprite95width*sprite95height)+sprite95Bitmap
//
//#define		sprite97width		180
//#define		sprite97height		45
//#define		sprite97Bitmap		(sprite96width*sprite96height)+sprite96Bitmap
//
//#define		sprite98width		180
//#define		sprite98height		45
//#define		sprite98Bitmap		(sprite97width*sprite97height)+sprite97Bitmap
//
//#define		sprite99width		96
//#define		sprite99height		44
//#define		sprite99Bitmap		(sprite98width*sprite98height)+sprite98Bitmap
//
//#define		sprite100width		96
//#define		sprite100height	44
//#define		sprite100Bitmap	(sprite99width*sprite99height)+sprite99Bitmap
//
//#define		sprite101width		96
//#define		sprite101height	44
//#define		sprite101Bitmap	(sprite100width*sprite100height)+sprite100Bitmap
//
//#define		sprite102width		96
//#define		sprite102height	44
//#define		sprite102Bitmap	(sprite101width*sprite101height)+sprite101Bitmap
//
//#define		sprite103width		96
//#define		sprite103height	44
//#define		sprite103Bitmap	(sprite102width*sprite102height)+sprite102Bitmap
//
//#define		sprite104width		96
//#define		sprite104height  	44
//#define		sprite104Bitmap  	(sprite103width*sprite103height)+sprite103Bitmap
//
//#define		sprite105width		96
//#define		sprite105height 	44
//#define		sprite105Bitmap 	(sprite104width*sprite104height)+sprite104Bitmap
//
//#define		sprite106width		96
//#define		sprite106height 	44
//#define		sprite106Bitmap 	(sprite105width*sprite105height)+sprite105Bitmap
//
//#define		sprite107width		96
//#define		sprite107height	44
//#define		sprite107Bitmap	(sprite106width*sprite106height)+sprite106Bitmap
//
//#define		sprite108width		96
//#define		sprite108height 	44
//#define		sprite108Bitmap 	(sprite107width*sprite107height)+sprite107Bitmap
//
//#define		sprite109width		96
//#define		sprite109height	44
//#define		sprite109Bitmap	(sprite108width*sprite108height)+sprite108Bitmap
//
//#define		sprite110width		96
//#define		sprite110height	44
//#define		sprite110Bitmap	(sprite109width*sprite109height)+sprite109Bitmap
//
//#define		sprite111width		96
//#define		sprite111height  	44
//#define		sprite111Bitmap  	(sprite110width*sprite110height)+sprite110Bitmap
//
//#define		sprite112width		96
//#define		sprite112height 	44
//#define		sprite112Bitmap 	(sprite111width*sprite111height)+sprite111Bitmap
//
//#define		sprite113width		96
//#define		sprite113height 	44
//#define		sprite113Bitmap 	(sprite112width*sprite112height)+sprite112Bitmap
//
//#define		sprite114width		180
//#define		sprite114height 	43
//#define		sprite114Bitmap 	(sprite113width*sprite113height)+sprite113Bitmap
//
//#define		sprite115width		233
//#define		sprite115height 	44
//#define		sprite115Bitmap 	(sprite114width*sprite114height)+sprite114Bitmap
//						  
//#define		sprite116width		9
//#define		sprite116height 	20
//#define		sprite116Bitmap 	(sprite115width*sprite115height)+sprite115Bitmap
//
//#define		sprite117width		15
//#define		sprite117height 	15
//#define		sprite117Bitmap 	(sprite116width*sprite116height)+sprite116Bitmap
//						  
//#define		sprite118width		15
//#define		sprite118height 	15
//#define		sprite118Bitmap 	(sprite117width*sprite117height)+sprite117Bitmap
//						  
//#define		sprite119width		15
//#define		sprite119height 	15
//#define		sprite119Bitmap 	(sprite118width*sprite118height)+sprite118Bitmap
//						  
//#define		sprite120width		15
//#define		sprite120height 	15
//#define		sprite120Bitmap 	(sprite119width*sprite119height)+sprite119Bitmap
//						  
//#define		sprite121width		166
//#define		sprite121height 	167
//#define		sprite121Bitmap 	(sprite120width*sprite120height)+sprite120Bitmap
//						  
//#define		sprite122width		126
//#define		sprite122height 	163
//#define		sprite122Bitmap 	(sprite121width*sprite121height)+sprite121Bitmap
//						  
//#define		sprite123width		101
//#define		sprite123height 	100
//#define		sprite123Bitmap 	(sprite122width*sprite122height)+sprite122Bitmap
//						  
//#define		sprite124width		118
//#define		sprite124height 	164
//#define		sprite124Bitmap 	(sprite123width*sprite123height)+sprite123Bitmap
//																								
//#define		sprite125width		33
//#define		sprite125height 	36
//#define		sprite125Bitmap 	(sprite124width*sprite124height)+sprite124Bitmap
//						  
//#define		sprite126width		33
//#define		sprite126height 	36
//#define		sprite126Bitmap 	(sprite125width*sprite125height)+sprite125Bitmap
//						  
//#define		sprite127width		33
//#define		sprite127height 	33
//#define		sprite127Bitmap 	(sprite126width*sprite126height)+sprite126Bitmap
//						  
//#define		sprite128width		58
//#define		sprite128height	87
//#define		sprite128Bitmap	(sprite127width*sprite127height)+sprite127Bitmap
//
//#define		sprite129width		58
//#define		sprite129height	87
//#define		sprite129Bitmap	(sprite128width*sprite128height)+sprite128Bitmap
//
//#define		sprite130width		58
//#define		sprite130height	87
//#define		sprite130Bitmap	(sprite129width*sprite129height)+sprite129Bitmap
//
//#define		sprite131width		58
//#define		sprite131height	87
//#define		sprite131Bitmap	(sprite130width*sprite130height)+sprite130Bitmap
//
//#define		sprite132width		58
//#define		sprite132height	87
//#define		sprite132Bitmap	(sprite131width*sprite131height)+sprite131Bitmap
//
//#define		sprite133width		58
//#define		sprite133height	87
//#define		sprite133Bitmap	(sprite132width*sprite132height)+sprite132Bitmap
//
//#define		sprite134width		58
//#define		sprite134height	87
//#define		sprite134Bitmap	(sprite133width*sprite133height)+sprite133Bitmap
//
//#define		sprite135width		58
//#define		sprite135height	87
//#define		sprite135Bitmap	(sprite134width*sprite134height)+sprite134Bitmap
//
//#define		sprite136width		58
//#define		sprite136height	87
//#define		sprite136Bitmap	(sprite135width*sprite135height)+sprite135Bitmap
//
//#define		sprite137width		58
//#define		sprite137height	87
//#define		sprite137Bitmap	(sprite136width*sprite136height)+sprite136Bitmap
//
//#define		sprite138width		58
//#define		sprite138height	87
//#define		sprite138Bitmap	(sprite137width*sprite137height)+sprite137Bitmap
//
//#define		sprite139width		58
//#define		sprite139height	87
//#define		sprite139Bitmap	(sprite138width*sprite138height)+sprite138Bitmap
//
//#define		sprite140width		58
//#define		sprite140height	87
//#define		sprite140Bitmap	(sprite139width*sprite139height)+sprite139Bitmap
//
//#define		sprite141width		58
//#define		sprite141height	87
//#define		sprite141Bitmap	(sprite140width*sprite140height)+sprite140Bitmap
//
//#define		sprite142width		240
//#define		sprite142height	57
//#define		sprite142Bitmap	(sprite141width*sprite141height)+sprite141Bitmap
//						  
//#define		sprite143width		75
//#define		sprite143height	76
//#define		sprite143Bitmap	(sprite142width*sprite142height)+sprite142Bitmap
//						  
//#define		sprite144width		75
//#define		sprite144height	80
//#define		sprite144Bitmap	(sprite143width*sprite143height)+sprite143Bitmap
//						  
//#define		sprite145width		115
//#define		sprite145height	96
//#define		sprite145Bitmap	(sprite144width*sprite144height)+sprite144Bitmap
//						  
//#define		sprite146width		64
//#define		sprite146height	48
//#define		sprite146Bitmap	(sprite145width*sprite145height)+sprite145Bitmap
//						  
//#define		sprite147width		80
//#define		sprite147height	46
//#define		sprite147Bitmap	(sprite146width*sprite146height)+sprite146Bitmap
//						  
//#define		sprite148width		78
//#define		sprite148height	86
//#define		sprite148Bitmap	(sprite147width*sprite147height)+sprite147Bitmap
//						  
//#define		sprite149width		69
//#define		sprite149height	82
//#define		sprite149Bitmap	(sprite148width*sprite148height)+sprite148Bitmap
//						  
//#define		sprite150width		451
//#define		sprite150height	29
//#define		sprite150Bitmap	(sprite149width*sprite149height)+sprite149Bitmap
//						  
////#define		sprite151width		136
////#define		sprite151height	74
////#define		sprite151Bitmap	(sprite150width*sprite150height)+sprite150Bitmap
////#define		sprite152width		71
////#define		sprite152height	73
////#define		sprite152Bitmap	(sprite151width*sprite151height)+sprite151Bitmap
//						  
//
//
//
//
//
//
//
//#define		sprite1width_s		14
//#define		sprite1height_s	28
//#define		sprite1Bitmap_s	0
//
//#define		sprite1awidth_s	14
//#define		sprite1aheight_s	28
//#define		sprite1aBitmap_s	(sprite1width_s*sprite1height_s)+sprite1Bitmap_s
//
//#define		sprite1bwidth_s	14
//#define		sprite1bheight_s	28
//#define		sprite1bBitmap_s	(sprite1awidth_s*sprite1aheight_s)+sprite1aBitmap_s
//
//#define		sprite2width_s		10
//#define		sprite2height_s	10
//#define		sprite2Bitmap_s	(sprite1bwidth_s*sprite1bheight_s)+sprite1bBitmap_s
//
//#define		sprite3width_s		10
//#define		sprite3height_s	9
//#define		sprite3Bitmap_s	(sprite2width_s*sprite2height_s)+sprite2Bitmap_s
//
//#define		sprite4width_s		10
//#define		sprite4height_s	9
//#define		sprite4Bitmap_s	(sprite3width_s*sprite3height_s)+sprite3Bitmap_s
//
//#define		sprite5width_s		10
//#define		sprite5height_s	9
//#define		sprite5Bitmap_s	(sprite4width_s*sprite4height_s)+sprite4Bitmap_s
//
//#define		sprite6width_s		10
//#define		sprite6height_s	9
//#define		sprite6Bitmap_s	(sprite5width_s*sprite5height_s)+sprite5Bitmap_s
//
//#define		sprite7width_s		10
//#define		sprite7height_s	9
//#define		sprite7Bitmap_s	(sprite6width_s*sprite6height_s)+sprite6Bitmap_s
//
//#define		sprite8width_s		10
//#define		sprite8height_s	9
//#define		sprite8Bitmap_s	(sprite7width_s*sprite7height_s)+sprite7Bitmap_s
//
//#define		sprite9width_s		11
//#define		sprite9height_s	9
//#define		sprite9Bitmap_s	(sprite8width_s*sprite8height_s)+sprite8Bitmap_s
//
//#define		sprite10width_s	285
//#define		sprite10height_s	14
//#define		sprite10Bitmap_s	(sprite9width_s*sprite9height_s)+sprite9Bitmap_s
//
//#define		sprite11width_s	35
//#define		sprite11height_s	42
//#define		sprite11Bitmap_s	(sprite10width_s*sprite10height_s)+sprite10Bitmap_s
//
//#define		sprite12width_s	35
//#define		sprite12height_s	42
//#define		sprite12Bitmap_s	(sprite11width_s*sprite11height_s)+sprite11Bitmap_s
//
//#define		sprite13width_s	35
//#define		sprite13height_s	42
//#define		sprite13Bitmap_s	(sprite12width_s*sprite12height_s)+sprite12Bitmap_s
//
//#define		sprite14width_s	35
//#define		sprite14height_s	42
//#define		sprite14Bitmap_s	(sprite13width_s*sprite13height_s)+sprite13Bitmap_s
//
//#define		sprite15width_s	35
//#define		sprite15height_s	42
//#define		sprite15Bitmap_s	(sprite14width_s*sprite14height_s)+sprite14Bitmap_s
//
//#define		sprite16width_s	35
//#define		sprite16height_s	42
//#define		sprite16Bitmap_s	(sprite15width_s*sprite15height_s)+sprite15Bitmap_s
//
//#define		sprite17width_s	35
//#define		sprite17height_s	42
//#define		sprite17Bitmap_s	(sprite16width_s*sprite16height_s)+sprite16Bitmap_s
//
//#define		sprite18width_s	35
//#define		sprite18height_s	42
//#define		sprite18Bitmap_s	(sprite17width_s*sprite17height_s)+sprite17Bitmap_s
//
//#define		sprite19width_s	35
//#define		sprite19height_s	42
//#define		sprite19Bitmap_s	(sprite18width_s*sprite18height_s)+sprite18Bitmap_s
//
//#define		sprite20width_s	35
//#define		sprite20height_s	42
//#define		sprite20Bitmap_s	(sprite19width_s*sprite19height_s)+sprite19Bitmap_s
//
//#define		sprite21width_s	35
//#define		sprite21height_s	42
//#define		sprite21Bitmap_s	(sprite20width_s*sprite20height_s)+sprite20Bitmap_s
//
//#define		sprite22width_s	35
//#define		sprite22height_s	42
//#define		sprite22Bitmap_s	(sprite21width_s*sprite21height_s)+sprite21Bitmap_s
//
//#define		sprite23width_s	35
//#define		sprite23height_s	42
//#define		sprite23Bitmap_s	(sprite22width_s*sprite22height_s)+sprite22Bitmap_s
//
//#define		sprite24width_s	35
//#define		sprite24height_s	42
//#define		sprite24Bitmap_s	(sprite23width_s*sprite23height_s)+sprite23Bitmap_s
//
//#define		sprite25width_s	35
//#define		sprite25height_s	42
//#define		sprite25Bitmap_s	(sprite24width_s*sprite24height_s)+sprite24Bitmap_s
//
//#define		sprite26width_s	35
//#define		sprite26height_s	42
//#define		sprite26Bitmap_s	(sprite25width_s*sprite25height_s)+sprite25Bitmap_s
//
//#define		sprite27width_s	35
//#define		sprite27height_s	42
//#define		sprite27Bitmap_s	(sprite26width_s*sprite26height_s)+sprite26Bitmap_s
//
//#define		sprite28width_s	35
//#define		sprite28height_s	42
//#define		sprite28Bitmap_s	(sprite27width_s*sprite27height_s)+sprite27Bitmap_s
//
//#define		sprite29width_s	35
//#define		sprite29height_s	42
//#define		sprite29Bitmap_s	(sprite28width_s*sprite28height_s)+sprite28Bitmap_s
//
//#define		sprite30width_s	35
//#define		sprite30height_s	42
//#define		sprite30Bitmap_s	(sprite29width_s*sprite29height_s)+sprite29Bitmap_s
//
//#define		sprite31width_s	35
//#define		sprite31height_s	42
//#define		sprite31Bitmap_s	(sprite30width_s*sprite30height_s)+sprite30Bitmap_s
//
//#define		sprite32width_s	35
//#define		sprite32height_s	42
//#define		sprite32Bitmap_s	(sprite31width_s*sprite31height_s)+sprite31Bitmap_s
//
//#define		sprite33width_s	35
//#define		sprite33height_s	42
//#define		sprite33Bitmap_s	(sprite32width_s*sprite32height_s)+sprite32Bitmap_s
//
//#define		sprite34width_s	35
//#define		sprite34height_s	42
//#define		sprite34Bitmap_s	(sprite33width_s*sprite33height_s)+sprite33Bitmap_s
//
//#define		sprite35width_s	35
//#define		sprite35height_s	42
//#define		sprite35Bitmap_s	(sprite34width_s*sprite34height_s)+sprite34Bitmap_s
//
//#define		sprite36width_s	35
//#define		sprite36height_s	42
//#define		sprite36Bitmap_s	(sprite35width_s*sprite35height_s)+sprite35Bitmap_s
//
//#define		sprite37width_s	35
//#define		sprite37height_s	42
//#define		sprite37Bitmap_s	(sprite36width_s*sprite36height_s)+sprite36Bitmap_s
//
//#define		sprite38width_s	35
//#define		sprite38height_s	42
//#define		sprite38Bitmap_s	(sprite37width_s*sprite37height_s)+sprite37Bitmap_s
//
//#define		sprite39width_s	35
//#define		sprite39height_s	42
//#define		sprite39Bitmap_s	(sprite38width_s*sprite38height_s)+sprite38Bitmap_s
//
//#define		sprite40width_s	35
//#define		sprite40height_s	42
//#define		sprite40Bitmap_s	(sprite39width_s*sprite39height_s)+sprite39Bitmap_s
//
//#define		sprite41width_s	35
//#define		sprite41height_s	42
//#define		sprite41Bitmap_s	(sprite40width_s*sprite40height_s)+sprite40Bitmap_s
//
//#define		sprite42width_s	35
//#define		sprite42height_s	42
//#define		sprite42Bitmap_s	(sprite41width_s*sprite41height_s)+sprite41Bitmap_s
//										
//#define		sprite43width_s	35
//#define		sprite43height_s	42
//#define		sprite43Bitmap_s	(sprite42width_s*sprite42height_s)+sprite42Bitmap_s
//
//#define		sprite44width_s	35
//#define		sprite44height_s	42
//#define		sprite44Bitmap_s	(sprite43width_s*sprite43height_s)+sprite43Bitmap_s
//
//#define		sprite45width_s	35
//#define		sprite45height_s	42
//#define		sprite45Bitmap_s	(sprite44width_s*sprite44height_s)+sprite44Bitmap_s
//
//#define		sprite46width_s	35
//#define		sprite46height_s	42
//#define		sprite46Bitmap_s	(sprite45width_s*sprite45height_s)+sprite45Bitmap_s
//
//#define		sprite47width_s	35
//#define		sprite47height_s	42
//#define		sprite47Bitmap_s	(sprite46width_s*sprite46height_s)+sprite46Bitmap_s
//
//#define		sprite48width_s	35
//#define		sprite48height_s	42
//#define		sprite48Bitmap_s	(sprite47width_s*sprite47height_s)+sprite47Bitmap_s
//
//#define		sprite49width_s	35
//#define		sprite49height_s	42
//#define		sprite49Bitmap_s	(sprite48width_s*sprite48height_s)+sprite48Bitmap_s
//
//#define		sprite50width_s	35
//#define		sprite50height_s	42
//#define		sprite50Bitmap_s	(sprite49width_s*sprite49height_s)+sprite49Bitmap_s
//
//#define		sprite51width_s	35
//#define		sprite51height_s	42
//#define		sprite51Bitmap_s	(sprite50width_s*sprite50height_s)+sprite50Bitmap_s
//
//#define		sprite52width_s	35
//#define		sprite52height_s	42
//#define		sprite52Bitmap_s	(sprite51width_s*sprite51height_s)+sprite51Bitmap_s
//
//#define		sprite53width_s	35
//#define		sprite53height_s	42
//#define		sprite53Bitmap_s	(sprite52width_s*sprite52height_s)+sprite52Bitmap_s
//
//#define		sprite54width_s	35
//#define		sprite54height_s	42
//#define		sprite54Bitmap_s	(sprite53width_s*sprite53height_s)+sprite53Bitmap_s
//
//#define		sprite55width_s	35
//#define		sprite55height_s	42
//#define		sprite55Bitmap_s	(sprite54width_s*sprite54height_s)+sprite54Bitmap_s
//
//#define		sprite55Bwidth_s	35
//#define		sprite55Bheight_s	42
//#define		sprite55BBitmap_s	(sprite55width_s*sprite55height_s)+sprite55Bitmap_s
//
//#define		sprite55Cwidth_s	35
//#define		sprite55Cheight_s	42
//#define		sprite55CBitmap_s	(sprite55Bwidth_s*sprite55Bheight_s)+sprite55BBitmap_s
//
//#define		sprite56width_s	285
//#define		sprite56height_s	14
//#define		sprite56Bitmap_s	(sprite55Cwidth_s*sprite55Cheight_s)+sprite55CBitmap_s
//
//#define		sprite57width_s	96	
//#define		sprite57height_s	37	
//#define		sprite57Bitmap_s	(sprite56width_s*sprite56height_s)+sprite56Bitmap_s
//
//#define		sprite58width_s	136
//#define		sprite58height_s	88
//#define		sprite58Bitmap_s	(sprite57width_s*sprite57height_s)+sprite57Bitmap_s
//
//#define		sprite59width_s	68
//#define		sprite59height_s	37
//#define		sprite59Bitmap_s	(sprite58width_s*sprite58height_s)+sprite58Bitmap_s
//
//#define		sprite60width_s	1
//#define		sprite60height_s	1
//#define		sprite60Bitmap_s	(sprite59width_s*sprite59height_s)+sprite59Bitmap_s
//
//#define		sprite61width_s	271
//#define		sprite61height_s	3
//#define		sprite61Bitmap_s	(sprite60width_s*sprite60height_s)+sprite60Bitmap_s
//
//#define		sprite62width_s	1
//#define		sprite62height_s	1
//#define		sprite62Bitmap_s	(sprite61width_s*sprite61height_s)+sprite61Bitmap_s
//
//#define		sprite63width_s	32
//#define		sprite63height_s	44
//#define		sprite63Bitmap_s	(sprite62width_s*sprite62height_s)+sprite62Bitmap_s
//
//#define		sprite64width_s	32
//#define		sprite64height_s	44
//#define		sprite64Bitmap_s	(sprite63width_s*sprite63height_s)+sprite63Bitmap_s
//
//#define		sprite65width_s	32
//#define		sprite65height_s	44
//#define		sprite65Bitmap_s	(sprite64width_s*sprite64height_s)+sprite64Bitmap_s
//
//#define		sprite66width_s	32
//#define		sprite66height_s	44
//#define		sprite66Bitmap_s	(sprite65width_s*sprite65height_s)+sprite65Bitmap_s
//
//#define		sprite67width_s	32
//#define		sprite67height_s	44
//#define		sprite67Bitmap_s	(sprite66width_s*sprite66height_s)+sprite66Bitmap_s
//
//#define		sprite68width_s	32
//#define		sprite68height_s	44
//#define		sprite68Bitmap_s	(sprite67width_s*sprite67height_s)+sprite67Bitmap_s
//
//#define		sprite69width_s	32
//#define		sprite69height_s	44
//#define		sprite69Bitmap_s	(sprite68width_s*sprite68height_s)+sprite68Bitmap_s
//
//#define		sprite70width_s	32
//#define		sprite70height_s	44
//#define		sprite70Bitmap_s	(sprite69width_s*sprite69height_s)+sprite69Bitmap_s
//
//#define		sprite71width_s	32
//#define		sprite71height_s	44
//#define		sprite71Bitmap_s	(sprite70width_s*sprite70height_s)+sprite70Bitmap_s
//
//#define		sprite72width_s	32
//#define		sprite72height_s	44
//#define		sprite72Bitmap_s	(sprite71width_s*sprite71height_s)+sprite71Bitmap_s
//
//#define		sprite73width_s	32
//#define		sprite73height_s	44
//#define		sprite73Bitmap_s	(sprite72width_s*sprite72height_s)+sprite72Bitmap_s
//
//#define		sprite74width_s	32
//#define		sprite74height_s	44
//#define		sprite74Bitmap_s	(sprite73width_s*sprite73height_s)+sprite73Bitmap_s
//
//#define		sprite75width_s	32
//#define		sprite75height_s	44
//#define		sprite75Bitmap_s	(sprite74width_s*sprite74height_s)+sprite74Bitmap_s
//
//#define		sprite76width_s	66
//#define		sprite76height_s	72
//#define		sprite76Bitmap_s	(sprite75width_s*sprite75height_s)+sprite75Bitmap_s
//
//#define		sprite77width_s	66
//#define		sprite77height_s	72
//#define		sprite77Bitmap_s	(sprite76width_s*sprite76height_s)+sprite76Bitmap_s
//
//#define		sprite78width_s	66
//#define		sprite78height_s	72
//#define		sprite78Bitmap_s	(sprite77width_s*sprite77height_s)+sprite77Bitmap_s
//
//#define		sprite79width_s	66
//#define		sprite79height_s	72
//#define		sprite79Bitmap_s	(sprite78width_s*sprite78height_s)+sprite78Bitmap_s
//
//#define		sprite80width_s	16
//#define		sprite80height_s	17
//#define		sprite80Bitmap_s	(sprite79width_s*sprite79height_s)+sprite79Bitmap_s
//
//#define		sprite81width_s	15
//#define		sprite81height_s	17
//#define		sprite81Bitmap_s	(sprite80width_s*sprite80height_s)+sprite80Bitmap_s
//
//#define		sprite82width_s	25
//#define		sprite82height_s	17
//#define		sprite82Bitmap_s	(sprite81width_s*sprite81height_s)+sprite81Bitmap_s
//
//#define		sprite83width_s	29
//#define		sprite83height_s	17
//#define		sprite83Bitmap_s	(sprite82width_s*sprite82height_s)+sprite82Bitmap_s
//
//#define		sprite84width_s	90
//#define		sprite84height_s	22
//#define		sprite84Bitmap_s	(sprite83width_s*sprite83height_s)+sprite83Bitmap_s
//
//#define		sprite85width_s	90
//#define		sprite85height_s	22
//#define		sprite85Bitmap_s	(sprite84width_s*sprite84height_s)+sprite84Bitmap_s
//
//#define		sprite86width_s	90
//#define		sprite86height_s	22
//#define		sprite86Bitmap_s	(sprite85width_s*sprite85height_s)+sprite85Bitmap_s
//
//#define		sprite87width_s	90
//#define		sprite87height_s	22
//#define		sprite87Bitmap_s	(sprite86width_s*sprite86height_s)+sprite86Bitmap_s
//
//#define		sprite88width_s	90
//#define		sprite88height_s	22
//#define		sprite88Bitmap_s	(sprite87width_s*sprite87height_s)+sprite87Bitmap_s
//
//#define		sprite89width_s	90
//#define		sprite89height_s	22
//#define		sprite89Bitmap_s	(sprite88width_s*sprite88height_s)+sprite88Bitmap_s
//
//#define		sprite90width_s	90
//#define		sprite90height_s	22
//#define		sprite90Bitmap_s	(sprite89width_s*sprite89height_s)+sprite89Bitmap_s
//
//#define		sprite91width_s	90
//#define		sprite91height_s	22
//#define		sprite91Bitmap_s	(sprite90width_s*sprite90height_s)+sprite90Bitmap_s
//
//#define		sprite92width_s	90
//#define		sprite92height_s	22
//#define		sprite92Bitmap_s	(sprite91width_s*sprite91height_s)+sprite91Bitmap_s
//
//#define		sprite93width_s	90
//#define		sprite93height_s	22
//#define		sprite93Bitmap_s	(sprite92width_s*sprite92height_s)+sprite92Bitmap_s
//
//#define		sprite94width_s	90
//#define		sprite94height_s	22
//#define		sprite94Bitmap_s	(sprite93width_s*sprite93height_s)+sprite93Bitmap_s
//
//#define		sprite95width_s	90
//#define		sprite95height_s	22
//#define		sprite95Bitmap_s	(sprite94width_s*sprite94height_s)+sprite94Bitmap_s
//
//#define		sprite96width_s	90
//#define		sprite96height_s	22
//#define		sprite96Bitmap_s	(sprite95width_s*sprite95height_s)+sprite95Bitmap_s
//
//#define		sprite97width_s	90
//#define		sprite97height_s	22
//#define		sprite97Bitmap_s	(sprite96width_s*sprite96height_s)+sprite96Bitmap_s
//
//#define		sprite98width_s	90
//#define		sprite98height_s	22
//#define		sprite98Bitmap_s	(sprite97width_s*sprite97height_s)+sprite97Bitmap_s
//
//
//#define		sprite99width_s	48
//#define		sprite99height_s	22
//#define		sprite99Bitmap_s	(sprite98width_s*sprite98height_s)+sprite98Bitmap_s
//
//#define		sprite100width_s	48
//#define		sprite100height_s	22
//#define		sprite100Bitmap_s	(sprite99width_s*sprite99height_s)+sprite99Bitmap_s
//
//#define		sprite101width_s	48
//#define		sprite101height_s	22
//#define		sprite101Bitmap_s (sprite100width_s*sprite100height_s)+sprite100Bitmap_s
//
//#define		sprite102width_s	48
//#define		sprite102height_s	22
//#define		sprite102Bitmap_s (sprite101width_s*sprite101height_s)+sprite101Bitmap_s
//
//#define		sprite103width_s	48
//#define		sprite103height_s	22
//#define		sprite103Bitmap_s (sprite102width_s*sprite102height_s)+sprite102Bitmap_s
//
//#define		sprite104width_s	48
//#define		sprite104height_s 22
//#define		sprite104Bitmap_s (sprite103width_s*sprite103height_s)+sprite103Bitmap_s
//
//#define		sprite105width_s	48
//#define		sprite105height_s	22
//#define		sprite105Bitmap_s	(sprite104width_s*sprite104height_s)+sprite104Bitmap_s
//
//#define		sprite106width_s	48
//#define		sprite106height_s	22
//#define		sprite106Bitmap_s	(sprite105width_s*sprite105height_s)+sprite105Bitmap_s
//
//#define		sprite107width_s	48
//#define		sprite107height_s	22
//#define		sprite107Bitmap_s (sprite106width_s*sprite106height_s)+sprite106Bitmap_s
//
//#define		sprite108width_s	48
//#define		sprite108height_s	22
//#define		sprite108Bitmap_s	(sprite107width_s*sprite107height_s)+sprite107Bitmap_s
//
//#define		sprite109width_s	48
//#define		sprite109height_s	22
//#define		sprite109Bitmap_s (sprite108width_s*sprite108height_s)+sprite108Bitmap_s
//
//#define		sprite110width_s 	48
//#define		sprite110height_s	22
//#define		sprite110Bitmap_s (sprite109width_s*sprite109height_s)+sprite109Bitmap_s
//
//#define		sprite111width_s	48
//#define		sprite111height_s 22
//#define		sprite111Bitmap_s (sprite110width_s*sprite110height_s)+sprite110Bitmap_s
//
//#define		sprite112width_s	48
//#define		sprite112height_s	22
//#define		sprite112Bitmap_s	(sprite111width_s*sprite111height_s)+sprite111Bitmap_s
//
//#define		sprite113width_s	48
//#define		sprite113height_s	22
//#define		sprite113Bitmap_s	(sprite112width_s*sprite112height_s)+sprite112Bitmap_s
//
//
//
//
//#define		sprite114width_s	90
//#define		sprite114height_s	22
//#define		sprite114Bitmap_s	(sprite113width_s*sprite113height_s)+sprite113Bitmap_s
//
//#define		sprite115width_s	115
//#define		sprite115height_s	22
//#define		sprite115Bitmap_s	(sprite114width_s*sprite114height_s)+sprite114Bitmap_s
//						  
//#define		sprite116width_s	4
//#define		sprite116height_s	10
//#define		sprite116Bitmap_s	(sprite115width_s*sprite115height_s)+sprite115Bitmap_s
//
//#define		sprite117width_s	9
//#define		sprite117height_s	9
//#define		sprite117Bitmap_s	(sprite116width_s*sprite116height_s)+sprite116Bitmap_s
//						  
//#define		sprite118width_s	9
//#define		sprite118height_s	9
//#define		sprite118Bitmap_s	(sprite117width_s*sprite117height_s)+sprite117Bitmap_s
//						  
//#define		sprite119width_s	9
//#define		sprite119height_s	9
//#define		sprite119Bitmap_s	(sprite118width_s*sprite118height_s)+sprite118Bitmap_s
//						  
//#define		sprite120width_s	9
//#define		sprite120height_s	9
//#define		sprite120Bitmap_s	(sprite119width_s*sprite119height_s)+sprite119Bitmap_s
//						  
//#define		sprite121width_s	82
//#define		sprite121height_s	83
//#define		sprite121Bitmap_s	(sprite120width_s*sprite120height_s)+sprite120Bitmap_s
//						  
//#define		sprite122width_s	63
//#define		sprite122height_s	82
//#define		sprite122Bitmap_s	(sprite121width_s*sprite121height_s)+sprite121Bitmap_s
//						  
//#define		sprite123width_s	52
//#define		sprite123height_s	53
//#define		sprite123Bitmap_s	(sprite122width_s*sprite122height_s)+sprite122Bitmap_s
//						  
//#define		sprite124width_s	59
//#define		sprite124height_s	82
//#define		sprite124Bitmap_s	(sprite123width_s*sprite123height_s)+sprite123Bitmap_s
//																								
//#define		sprite125width_s	17
//#define		sprite125height_s	17
//#define		sprite125Bitmap_s	(sprite124width_s*sprite124height_s)+sprite124Bitmap_s
//						  
//#define		sprite126width_s	17
//#define		sprite126height_s	17
//#define		sprite126Bitmap_s	(sprite125width_s*sprite125height_s)+sprite125Bitmap_s
//						  
//#define		sprite127width_s	17
//#define		sprite127height_s	17
//#define		sprite127Bitmap_s	(sprite126width_s*sprite126height_s)+sprite126Bitmap_s
//
//						  
//#define		sprite128width_s	29
//#define		sprite128height_s	43
//#define		sprite128Bitmap_s (sprite127width_s*sprite127height_s)+sprite127Bitmap_s
//
//#define		sprite129width_s	29
//#define		sprite129height_s	43
//#define		sprite129Bitmap_s (sprite128width_s*sprite128height_s)+sprite128Bitmap_s
//
//#define		sprite130width_s	29
//#define		sprite130height_s	43
//#define		sprite130Bitmap_s (sprite129width_s*sprite129height_s)+sprite129Bitmap_s
//
//#define		sprite131width_s	29
//#define		sprite131height_s	43
//#define		sprite131Bitmap_s (sprite130width_s*sprite130height_s)+sprite130Bitmap_s
//
//#define		sprite132width_s	29
//#define		sprite132height_s	43
//#define		sprite132Bitmap_s (sprite131width_s*sprite131height_s)+sprite131Bitmap_s
//
//#define		sprite133width_s	29
//#define		sprite133height_s	43
//#define		sprite133Bitmap_s (sprite132width_s*sprite132height_s)+sprite132Bitmap_s
//
//#define		sprite134width_s	29
//#define		sprite134height_s	43
//#define		sprite134Bitmap_s (sprite133width_s*sprite133height_s)+sprite133Bitmap_s
//
//#define		sprite135width_s	29
//#define		sprite135height_s	43
//#define		sprite135Bitmap_s (sprite134width_s*sprite134height_s)+sprite134Bitmap_s
//
//#define		sprite136width_s	29
//#define		sprite136height_s	43
//#define		sprite136Bitmap_s (sprite135width_s*sprite135height_s)+sprite135Bitmap_s
//
//#define		sprite137width_s	29
//#define		sprite137height_s	43
//#define		sprite137Bitmap_s (sprite136width_s*sprite136height_s)+sprite136Bitmap_s
//
//#define		sprite138width_s	29
//#define		sprite138height_s	43
//#define		sprite138Bitmap_s (sprite137width_s*sprite137height_s)+sprite137Bitmap_s
//
//#define		sprite139width_s	29
//#define		sprite139height_s	43
//#define		sprite139Bitmap_s (sprite138width_s*sprite138height_s)+sprite138Bitmap_s
//
//#define		sprite140width_s	29
//#define		sprite140height_s	43
//#define		sprite140Bitmap_s (sprite139width_s*sprite139height_s)+sprite139Bitmap_s
//
//#define		sprite141width_s	29
//#define		sprite141height_s	43
//#define		sprite141Bitmap_s (sprite140width_s*sprite140height_s)+sprite140Bitmap_s
//
//
//
//
//#define		sprite142width_s	1
//#define		sprite142height_s	1
//#define		sprite142Bitmap_s (sprite141width_s*sprite141height_s)+sprite141Bitmap_s
//						  
//#define		sprite143width_s	35
//#define		sprite143height_s	36
//#define		sprite143Bitmap_s (sprite142width_s*sprite142height_s)+sprite142Bitmap_s
//						  
//#define		sprite144width_s	36
//#define		sprite144height_s	38
//#define		sprite144Bitmap_s (sprite143width_s*sprite143height_s)+sprite143Bitmap_s
//						  
//#define		sprite145width_s	57
//#define		sprite145height_s	46
//#define		sprite145Bitmap_s (sprite144width_s*sprite144height_s)+sprite144Bitmap_s
//						  
//#define		sprite146width_s	1
//#define		sprite146height_s	1
//#define		sprite146Bitmap_s (sprite145width_s*sprite145height_s)+sprite145Bitmap_s
//						  
//#define		sprite147width_s	1 
//#define		sprite147height_s	1
//#define		sprite147Bitmap_s (sprite146width_s*sprite146height_s)+sprite146Bitmap_s
//						  
//#define		sprite148width_s	38
//#define		sprite148height_s	42
//#define		sprite148Bitmap_s (sprite147width_s*sprite147height_s)+sprite147Bitmap_s
//						  
//#define		sprite149width_s	35
//#define		sprite149height_s	42
//#define		sprite149Bitmap_s (sprite148width_s*sprite148height_s)+sprite148Bitmap_s
//						  
//#define		sprite150width_s	225
//#define		sprite150height_s	14
//#define		sprite150Bitmap_s (sprite149width_s*sprite149height_s)+sprite149Bitmap_s
//
//
//#define		sprite_S62width		100
//#define		sprite_S62height		60
//#define		sprite_S62Bitmap		0	 
//
//#define		sprite_S63width		100
//#define		sprite_S63height		60
//#define		sprite_S63Bitmap		(sprite_S62width*sprite_S62height)+sprite_S62Bitmap
//
//#define		sprite_S64width		100
//#define		sprite_S64height		60
//#define		sprite_S64Bitmap		(sprite_S63width*sprite_S63height)+sprite_S63Bitmap
//
//#define		sprite_S65width		100
//#define		sprite_S65height		60
//#define		sprite_S65Bitmap		(sprite_S64width*sprite_S64height)+sprite_S64Bitmap
//									  	
//#define		sprite_S66width		100
//#define		sprite_S66height		60
//#define		sprite_S66Bitmap		(sprite_S65width*sprite_S65height)+sprite_S65Bitmap
//
//#define		sprite_S67width		100
//#define		sprite_S67height		60
//#define		sprite_S67Bitmap		(sprite_S66width*sprite_S66height)+sprite_S66Bitmap
//
//#define		sprite_S68width		100
//#define		sprite_S68height		60
//#define		sprite_S68Bitmap		(sprite_S67width*sprite_S67height)+sprite_S67Bitmap
//
//#define		sprite_S69width		100
//#define		sprite_S69height		60
//#define		sprite_S69Bitmap		(sprite_S68width*sprite_S68height)+sprite_S68Bitmap
//
//#define		sprite_S70width		100
//#define		sprite_S70height		60
//#define		sprite_S70Bitmap		0	 
//
//#define		sprite_S71width		100
//#define		sprite_S71height		60
//#define		sprite_S71Bitmap		(sprite_S70width*sprite_S70height)+sprite_S70Bitmap
//
//#define		sprite_S72width		100
//#define		sprite_S72height		60
//#define		sprite_S72Bitmap		(sprite_S71width*sprite_S71height)+sprite_S71Bitmap
//
//#define		sprite_S73width		100
//#define		sprite_S73height		60
//#define		sprite_S73Bitmap		(sprite_S72width*sprite_S72height)+sprite_S72Bitmap
//
//#define		sprite_S74width		100
//#define		sprite_S74height		60
//#define		sprite_S74Bitmap		(sprite_S73width*sprite_S73height)+sprite_S73Bitmap
//
//#define		sprite_S75width		100
//#define		sprite_S75height		60
//#define		sprite_S75Bitmap		(sprite_S74width*sprite_S74height)+sprite_S74Bitmap
//
//#define		sprite_S76width		100
//#define		sprite_S76height		60
//#define		sprite_S76Bitmap		(sprite_S75width*sprite_S75height)+sprite_S75Bitmap
//
//#define		sprite_S77width		100
//#define		sprite_S77height		60
//#define		sprite_S77Bitmap		(sprite_S76width*sprite_S76height)+sprite_S76Bitmap
//
//#define		sprite_S78width		100
//#define		sprite_S78height		60
//#define		sprite_S78Bitmap		0	 
//
//#define		sprite_S79width		100
//#define		sprite_S79height		60
//#define		sprite_S79Bitmap		(sprite_S78width*sprite_S78height)+sprite_S78Bitmap
//
//#define		sprite_S80width		100
//#define		sprite_S80height		60
//#define		sprite_S80Bitmap		(sprite_S79width*sprite_S79height)+sprite_S79Bitmap
//
//#define		sprite_S81width		100
//#define		sprite_S81height		60
//#define		sprite_S81Bitmap		(sprite_S80width*sprite_S80height)+sprite_S80Bitmap
//
//#define		sprite_S82width		100
//#define		sprite_S82height		60
//#define		sprite_S82Bitmap		(sprite_S81width*sprite_S81height)+sprite_S81Bitmap
//
//#define		sprite_S83width		100
//#define		sprite_S83height		60
//#define		sprite_S83Bitmap		(sprite_S82width*sprite_S82height)+sprite_S82Bitmap
//
//#define		sprite_S84width		100
//#define		sprite_S84height		60
//#define		sprite_S84Bitmap		(sprite_S83width*sprite_S83height)+sprite_S83Bitmap
//
//#define		sprite_S85width		100
//#define		sprite_S85height		60
//#define		sprite_S85Bitmap		(sprite_S84width*sprite_S84height)+sprite_S84Bitmap
//
//#define		sprite_S86width		100
//#define		sprite_S86height		60
//#define		sprite_S86Bitmap		0	 
//
//#define		sprite_S87width		100
//#define		sprite_S87height		60
//#define		sprite_S87Bitmap		(sprite_S86width*sprite_S86height)+sprite_S86Bitmap
//
//#define		sprite_S88width		100
//#define		sprite_S88height		60
//#define		sprite_S88Bitmap		(sprite_S87width*sprite_S87height)+sprite_S87Bitmap
//
//#define		sprite_S89width		100
//#define		sprite_S89height		60
//#define		sprite_S89Bitmap		(sprite_S88width*sprite_S88height)+sprite_S88Bitmap
//
//#define		sprite_S90width		100
//#define		sprite_S90height		60
//#define		sprite_S90Bitmap		(sprite_S89width*sprite_S89height)+sprite_S89Bitmap
//
//#define		sprite_S91width		100
//#define		sprite_S91height		60
//#define		sprite_S91Bitmap		(sprite_S90width*sprite_S90height)+sprite_S90Bitmap
//
//#define		sprite_S92width		100
//#define		sprite_S92height		60
//#define		sprite_S92Bitmap		(sprite_S91width*sprite_S91height)+sprite_S91Bitmap
//
//#define		sprite_S93width		100
//#define		sprite_S93height		60
//#define		sprite_S93Bitmap		(sprite_S92width*sprite_S92height)+sprite_S92Bitmap
//
//#define		sprite_S94width		100
//#define		sprite_S94height		60
//#define		sprite_S94Bitmap		0	 
//
//#define		sprite_S95width		100
//#define		sprite_S95height		60
//#define		sprite_S95Bitmap		(sprite_S94width*sprite_S94height)+sprite_S94Bitmap
//
//#define		sprite_S96width		100
//#define		sprite_S96height		60
//#define		sprite_S96Bitmap		(sprite_S95width*sprite_S95height)+sprite_S95Bitmap
//
//#define		sprite_S97width		100
//#define		sprite_S97height		60
//#define		sprite_S97Bitmap		(sprite_S96width*sprite_S96height)+sprite_S96Bitmap
//
//#define		sprite_S98width		100
//#define		sprite_S98height		60
//#define		sprite_S98Bitmap		(sprite_S97width*sprite_S97height)+sprite_S97Bitmap
//
//#define		sprite_S99width		100
//#define		sprite_S99height		60
//#define		sprite_S99Bitmap		(sprite_S98width*sprite_S98height)+sprite_S98Bitmap
//
//#define		sprite_S100width		100
//#define		sprite_S100height		60
//#define		sprite_S100Bitmap		(sprite_S99width*sprite_S99height)+sprite_S99Bitmap
//
//#define		sprite_S101width		100
//#define		sprite_S101height		60
//#define		sprite_S101Bitmap		(sprite_S100width*sprite_S100height)+sprite_S100Bitmap
//
//#define		sprite_S102width		100
//#define		sprite_S102height		60
//#define		sprite_S102Bitmap		0
//
//#define		sprite_S103width		100
//#define		sprite_S103height		60
//#define		sprite_S103Bitmap		(sprite_S102width*sprite_S102height)+sprite_S102Bitmap
//
//#define		sprite_S104width		100
//#define		sprite_S104height		60
//#define		sprite_S104Bitmap		(sprite_S103width*sprite_S103height)+sprite_S103Bitmap
//
//#define		sprite_S105width		100
//#define		sprite_S105height		60
//#define		sprite_S105Bitmap		(sprite_S104width*sprite_S104height)+sprite_S104Bitmap	
//
//#define		sprite_S106width		100
//#define		sprite_S106height		60
//#define		sprite_S106Bitmap		(sprite_S105width*sprite_S105height)+sprite_S105Bitmap	
//
//#define		sprite_S107width		100
//#define		sprite_S107height		60
//#define		sprite_S107Bitmap		(sprite_S106width*sprite_S106height)+sprite_S106Bitmap	
//
//#define		sprite_S108width		100
//#define		sprite_S108height		60
//#define		sprite_S108Bitmap		(sprite_S107width*sprite_S107height)+sprite_S107Bitmap	
//
//#define		sprite_S109width		100
//#define		sprite_S109height		60
//#define		sprite_S109Bitmap		(sprite_S108width*sprite_S108height)+sprite_S108Bitmap	
//
//#define		sprite_S110width		100
//#define		sprite_S110height		60
//#define		sprite_S110Bitmap		0
//
//#define		sprite_S111width		100
//#define		sprite_S111height		60
//#define		sprite_S111Bitmap		(sprite_S110width*sprite_S110height)+sprite_S110Bitmap	
//
//#define		sprite_S112width		100
//#define		sprite_S112height		60
//#define		sprite_S112Bitmap		(sprite_S111width*sprite_S111height)+sprite_S111Bitmap	
//
//#define		sprite_S113width		100
//#define		sprite_S113height		60
//#define		sprite_S113Bitmap		(sprite_S112width*sprite_S112height)+sprite_S112Bitmap	
//
//#define		sprite_S114width		100
//#define		sprite_S114height		60
//#define		sprite_S114Bitmap		(sprite_S113width*sprite_S113height)+sprite_S113Bitmap	
//
//#define		sprite_S115width		100
//#define		sprite_S115height		60
//#define		sprite_S115Bitmap		(sprite_S114width*sprite_S114height)+sprite_S114Bitmap	
//
//#define		sprite_S116width		100
//#define		sprite_S116height		60
//#define		sprite_S116Bitmap		(sprite_S115width*sprite_S115height)+sprite_S115Bitmap	
//
//#define		sprite_S117width		100
//#define		sprite_S117height		60
//#define		sprite_S117Bitmap		(sprite_S116width*sprite_S116height)+sprite_S116Bitmap	
//
//#define		sprite_S118width		100
//#define		sprite_S118height		60
//#define		sprite_S118Bitmap		0
//
//#define		sprite_S119width		100
//#define		sprite_S119height		60
//#define		sprite_S119Bitmap		(sprite_S118width*sprite_S118height)+sprite_S118Bitmap	
//
//#define		sprite_S120width		100
//#define		sprite_S120height		60
//#define		sprite_S120Bitmap		(sprite_S119width*sprite_S119height)+sprite_S119Bitmap	
//
//#define		sprite_S121width		100
//#define		sprite_S121height		60
//#define		sprite_S121Bitmap		(sprite_S120width*sprite_S120height)+sprite_S120Bitmap	
//
//#define		sprite_S122width		100
//#define		sprite_S122height		60
//#define		sprite_S122Bitmap		(sprite_S121width*sprite_S121height)+sprite_S121Bitmap	
//
//#define		sprite_S123width		100
//#define		sprite_S123height		60
//#define		sprite_S123Bitmap		(sprite_S122width*sprite_S122height)+sprite_S122Bitmap	
//
//#define		sprite_S124width		100
//#define		sprite_S124height		60
//#define		sprite_S124Bitmap		(sprite_S123width*sprite_S123height)+sprite_S123Bitmap	
//
//#define		sprite_S125width		100
//#define		sprite_S125height		60
//#define		sprite_S125Bitmap		(sprite_S124width*sprite_S124height)+sprite_S124Bitmap	
//
//#define		sprite_S126width		100
//#define		sprite_S126height		60
//#define		sprite_S126Bitmap		0
//
//#define		sprite_S127width		100
//#define		sprite_S127height		60
//#define		sprite_S127Bitmap		(sprite_S126width*sprite_S126height)+sprite_S126Bitmap	
//
//#define		sprite_S128width		100
//#define		sprite_S128height		60
//#define		sprite_S128Bitmap		(sprite_S127width*sprite_S127height)+sprite_S127Bitmap	
//
//#define		sprite_S129width		100
//#define		sprite_S129height		60
//#define		sprite_S129Bitmap		(sprite_S128width*sprite_S128height)+sprite_S128Bitmap	
//
//#define		sprite_S130width		100
//#define		sprite_S130height		60
//#define		sprite_S130Bitmap		(sprite_S129width*sprite_S129height)+sprite_S129Bitmap	
//
//#define		sprite_S131width		100
//#define		sprite_S131height		60
//#define		sprite_S131Bitmap		(sprite_S130width*sprite_S130height)+sprite_S130Bitmap	
//
//#define		sprite_S132width		100
//#define		sprite_S132height		60
//#define		sprite_S132Bitmap		(sprite_S131width*sprite_S131height)+sprite_S131Bitmap	
//
//#define		sprite_S133width		100
//#define		sprite_S133height		60
//#define		sprite_S133Bitmap		(sprite_S132width*sprite_S132height)+sprite_S132Bitmap	
//
//#define		sprite_S134width		100
//#define		sprite_S134height		60
//#define		sprite_S134Bitmap		0
//
//#define		sprite_S135width		100
//#define		sprite_S135height		60
//#define		sprite_S135Bitmap		(sprite_S134width*sprite_S134height)+sprite_S134Bitmap	
//
//#define		sprite_S136width		100
//#define		sprite_S136height		60
//#define		sprite_S136Bitmap		(sprite_S135width*sprite_S135height)+sprite_S135Bitmap	
//
//#define		sprite_S137width		100
//#define		sprite_S137height		60
//#define		sprite_S137Bitmap		(sprite_S136width*sprite_S136height)+sprite_S136Bitmap	
//
//#define		sprite_S138width		100
//#define		sprite_S138height		60
//#define		sprite_S138Bitmap		(sprite_S137width*sprite_S137height)+sprite_S137Bitmap	
//
//#define		sprite_S139width		100
//#define		sprite_S139height		60
//#define		sprite_S139Bitmap		(sprite_S138width*sprite_S138height)+sprite_S138Bitmap	
//
//#define		sprite_S140width		100
//#define		sprite_S140height		60
//#define		sprite_S140Bitmap		(sprite_S139width*sprite_S139height)+sprite_S139Bitmap	
//
//#define		sprite_S141width		100
//#define		sprite_S141height		60
//#define		sprite_S141Bitmap		(sprite_S140width*sprite_S140height)+sprite_S140Bitmap	
//
//#define		sprite_S142width		100
//#define		sprite_S142height		60
//#define		sprite_S142Bitmap		0
//
//#define		sprite_S143width		100
//#define		sprite_S143height		60
//#define		sprite_S143Bitmap		(sprite_S142width*sprite_S142height)+sprite_S142Bitmap	
//
//#define		sprite_S144width		100
//#define		sprite_S144height		60
//#define		sprite_S144Bitmap		(sprite_S143width*sprite_S143height)+sprite_S143Bitmap	
//
//#define		sprite_S145width		100
//#define		sprite_S145height		60
//#define		sprite_S145Bitmap		(sprite_S144width*sprite_S144height)+sprite_S144Bitmap	
//
//#define		sprite_S146width		100
//#define		sprite_S146height		60
//#define		sprite_S146Bitmap		(sprite_S145width*sprite_S145height)+sprite_S145Bitmap	
//
//#define		sprite_S147width		100
//#define		sprite_S147height		60
//#define		sprite_S147Bitmap		(sprite_S146width*sprite_S146height)+sprite_S146Bitmap	
//
//#define		sprite_S148width		100
//#define		sprite_S148height		60
//#define		sprite_S148Bitmap		(sprite_S147width*sprite_S147height)+sprite_S147Bitmap	
//
//#define		sprite_S149width		100
//#define		sprite_S149height		60
//#define		sprite_S149Bitmap		(sprite_S148width*sprite_S148height)+sprite_S148Bitmap	
//
//#define		sprite_S150width		100
//#define		sprite_S150height		60
//#define		sprite_S150Bitmap		0
//
//#define		sprite_S151width		100
//#define		sprite_S151height		60
//#define		sprite_S151Bitmap		(sprite_S150width*sprite_S150height)+sprite_S150Bitmap	
//
//#define		sprite_S152width		100
//#define		sprite_S152height		60
//#define		sprite_S152Bitmap		(sprite_S151width*sprite_S151height)+sprite_S151Bitmap	
//
//#define		sprite_S153width		100
//#define		sprite_S153height		60
//#define		sprite_S153Bitmap		(sprite_S152width*sprite_S152height)+sprite_S152Bitmap	
//
//#define		sprite_S154width		100
//#define		sprite_S154height		60
//#define		sprite_S154Bitmap		(sprite_S153width*sprite_S153height)+sprite_S153Bitmap	
//
//#define		sprite_S155width		100
//#define		sprite_S155height		60
//#define		sprite_S155Bitmap		(sprite_S154width*sprite_S154height)+sprite_S154Bitmap	
//
//#define		sprite_S156width		100
//#define		sprite_S156height		60
//#define		sprite_S156Bitmap		(sprite_S155width*sprite_S155height)+sprite_S155Bitmap	
//
//#define		sprite_S157width		100
//#define		sprite_S157height		60
//#define		sprite_S157Bitmap		(sprite_S156width*sprite_S156height)+sprite_S156Bitmap	
//
//#define		sprite_S158width		100
//#define		sprite_S158height		60
//#define		sprite_S158Bitmap		0
//
//#define		sprite_S159width		100
//#define		sprite_S159height		60
//#define		sprite_S159Bitmap		(sprite_S158width*sprite_S158height)+sprite_S158Bitmap	
//
//#define		sprite_S160width		100
//#define		sprite_S160height		60
//#define		sprite_S160Bitmap		(sprite_S159width*sprite_S159height)+sprite_S159Bitmap	
//
//#define		sprite_S161width		100
//#define		sprite_S161height		60
//#define		sprite_S161Bitmap		(sprite_S160width*sprite_S160height)+sprite_S160Bitmap	
//
//#define		sprite_S162width		100
//#define		sprite_S162height		60
//#define		sprite_S162Bitmap		(sprite_S161width*sprite_S161height)+sprite_S161Bitmap	
//
//#define		sprite_S163width		100
//#define		sprite_S163height		60
//#define		sprite_S163Bitmap		(sprite_S162width*sprite_S162height)+sprite_S162Bitmap	
//
//#define		sprite_S164width		100
//#define		sprite_S164height		60
//#define		sprite_S164Bitmap		(sprite_S163width*sprite_S163height)+sprite_S163Bitmap	
//
//#define		sprite_S165width		100
//#define		sprite_S165height		60
//#define		sprite_S165Bitmap		(sprite_S164width*sprite_S164height)+sprite_S164Bitmap	
//
//#define		sprite_S166width		100
//#define		sprite_S166height		60
//#define		sprite_S166Bitmap		0
//
//#define		sprite_S167width		100
//#define		sprite_S167height		60
//#define		sprite_S167Bitmap		(sprite_S166width*sprite_S166height)+sprite_S166Bitmap	
//
//#define		sprite_S168width		100
//#define		sprite_S168height		60
//#define		sprite_S168Bitmap		(sprite_S167width*sprite_S167height)+sprite_S167Bitmap	
//
//#define		sprite_S169width		100
//#define		sprite_S169height		60
//#define		sprite_S169Bitmap		(sprite_S168width*sprite_S168height)+sprite_S168Bitmap	
//
//#define		sprite_S170width		100
//#define		sprite_S170height		60
//#define		sprite_S170Bitmap		(sprite_S169width*sprite_S169height)+sprite_S169Bitmap	
//
//#define		sprite_S171width		100
//#define		sprite_S171height		60
//#define		sprite_S171Bitmap		(sprite_S170width*sprite_S170height)+sprite_S170Bitmap	
//
//#define		sprite_S172width		100
//#define		sprite_S172height		60
//#define		sprite_S172Bitmap		(sprite_S171width*sprite_S171height)+sprite_S171Bitmap	
//
//#define		sprite_S173width		100
//#define		sprite_S173height		60
//#define		sprite_S173Bitmap		(sprite_S172width*sprite_S172height)+sprite_S172Bitmap	
//
//#define		sprite_S174width		100
//#define		sprite_S174height		60
//#define		sprite_S174Bitmap		0
//
//#define		sprite_S175width		100
//#define		sprite_S175height		60
//#define		sprite_S175Bitmap		(sprite_S174width*sprite_S174height)+sprite_S174Bitmap	
//
//#define		sprite_S176width		100
//#define		sprite_S176height		60
//#define		sprite_S176Bitmap		(sprite_S175width*sprite_S175height)+sprite_S175Bitmap	
//
//#define		sprite_S177width		100
//#define		sprite_S177height		60
//#define		sprite_S177Bitmap		(sprite_S176width*sprite_S176height)+sprite_S176Bitmap	
//
//#define		sprite_S178width		100
//#define		sprite_S178height		60
//#define		sprite_S178Bitmap		(sprite_S177width*sprite_S177height)+sprite_S177Bitmap	
//
//#define		sprite_S179width		100
//#define		sprite_S179height		60
//#define		sprite_S179Bitmap		(sprite_S178width*sprite_S178height)+sprite_S178Bitmap	
//
//#define		sprite_S180width		100
//#define		sprite_S180height		60
//#define		sprite_S180Bitmap		(sprite_S179width*sprite_S179height)+sprite_S179Bitmap	
//
//#define		sprite_S181width		100
//#define		sprite_S181height		60
//#define		sprite_S181Bitmap		(sprite_S180width*sprite_S180height)+sprite_S180Bitmap	
//
//#define		sprite_S182width		100
//#define		sprite_S182height		60
//#define		sprite_S182Bitmap		0
//
//#define		sprite_S183width		100
//#define		sprite_S183height		60
//#define		sprite_S183Bitmap		(sprite_S182width*sprite_S182height)+sprite_S182Bitmap	
//
//#define		sprite_S184width		100
//#define		sprite_S184height		60
//#define		sprite_S184Bitmap		(sprite_S183width*sprite_S183height)+sprite_S183Bitmap	
//
//#define		sprite_S185width		100
//#define		sprite_S185height		60
//#define		sprite_S185Bitmap		(sprite_S184width*sprite_S184height)+sprite_S184Bitmap	
//
//#define		sprite_S186width		100
//#define		sprite_S186height		60
//#define		sprite_S186Bitmap		(sprite_S185width*sprite_S185height)+sprite_S185Bitmap	
//
//#define		sprite_S187width		100
//#define		sprite_S187height		60
//#define		sprite_S187Bitmap		(sprite_S186width*sprite_S186height)+sprite_S186Bitmap	
//
//#define		sprite_S188width		100
//#define		sprite_S188height		60
//#define		sprite_S188Bitmap		(sprite_S187width*sprite_S187height)+sprite_S187Bitmap	
//
//#define		sprite_S189width		100
//#define		sprite_S189height		60
//#define		sprite_S189Bitmap		(sprite_S188width*sprite_S188height)+sprite_S188Bitmap	
//
//#define		sprite_S190width		100
//#define		sprite_S190height		60
//#define		sprite_S190Bitmap		0
//
//#define		sprite_S191width		100
//#define		sprite_S191height		60
//#define		sprite_S191Bitmap		(sprite_S190width*sprite_S190height)+sprite_S190Bitmap	
//
//#define		sprite_S192width		100
//#define		sprite_S192height		60
//#define		sprite_S192Bitmap		(sprite_S191width*sprite_S191height)+sprite_S191Bitmap	
//
//#define		sprite_S193width		100
//#define		sprite_S193height		60
//#define		sprite_S193Bitmap		(sprite_S192width*sprite_S192height)+sprite_S192Bitmap	
//
//#define		sprite_S194width		100
//#define		sprite_S194height		60
//#define		sprite_S194Bitmap		(sprite_S193width*sprite_S193height)+sprite_S193Bitmap	
//
//#define		sprite_S195width		100
//#define		sprite_S195height		60
//#define		sprite_S195Bitmap		(sprite_S194width*sprite_S194height)+sprite_S194Bitmap	
//
//#define		sprite_S196width		100
//#define		sprite_S196height		60
//#define		sprite_S196Bitmap		(sprite_S195width*sprite_S195height)+sprite_S195Bitmap	
//
//#define		sprite_S197width		100
//#define		sprite_S197height		60
//#define		sprite_S197Bitmap		(sprite_S196width*sprite_S196height)+sprite_S196Bitmap	
//
//#define		sprite_S198width		100
//#define		sprite_S198height		60
//#define		sprite_S198Bitmap		0
//
//#define		sprite_S199width		100
//#define		sprite_S199height		60
//#define		sprite_S199Bitmap		(sprite_S198width*sprite_S198height)+sprite_S198Bitmap	
//
//#define		sprite_S200width		100
//#define		sprite_S200height		60
//#define		sprite_S200Bitmap		(sprite_S199width*sprite_S199height)+sprite_S199Bitmap	
//
//#define		sprite_S201width		100
//#define		sprite_S201height		60
//#define		sprite_S201Bitmap		(sprite_S200width*sprite_S200height)+sprite_S200Bitmap	
//
//#define		sprite_S202width		100
//#define		sprite_S202height		60
//#define		sprite_S202Bitmap		(sprite_S201width*sprite_S201height)+sprite_S201Bitmap	
//
//#define		sprite_S203width		100
//#define		sprite_S203height		60
//#define		sprite_S203Bitmap		(sprite_S202width*sprite_S202height)+sprite_S202Bitmap	
//
//#define		sprite_S204width		100
//#define		sprite_S204height		60
//#define		sprite_S204Bitmap		(sprite_S203width*sprite_S203height)+sprite_S203Bitmap	
//
//#define		sprite_S205width		100
//#define		sprite_S205height		60
//#define		sprite_S205Bitmap		(sprite_S204width*sprite_S204height)+sprite_S204Bitmap	
//
//												 
//												 
//												 
//												 
//												 
//												 
//												 
//#define		sprite_S206width		100
//#define		sprite_S206height		60
//#define		sprite_S206Bitmap		0
//
//#define		sprite_S207width		100
//#define		sprite_S207height		60
//#define		sprite_S207Bitmap		(sprite_S206width*sprite_S206height)+sprite_S206Bitmap	
//
//#define		sprite_S208width		100
//#define		sprite_S208height		60
//#define		sprite_S208Bitmap		(sprite_S207width*sprite_S207height)+sprite_S207Bitmap	
//
//#define		sprite_S209width		100
//#define		sprite_S209height		60
//#define		sprite_S209Bitmap		(sprite_S208width*sprite_S208height)+sprite_S208Bitmap	
//
//#define		sprite_S210width		100
//#define		sprite_S210height		60
//#define		sprite_S210Bitmap		(sprite_S209width*sprite_S209height)+sprite_S209Bitmap	
//
//#define		sprite_S211width		100
//#define		sprite_S211height		60
//#define		sprite_S211Bitmap		(sprite_S210width*sprite_S210height)+sprite_S210Bitmap	
//
//#define		sprite_S212width		100
//#define		sprite_S212height		60
//#define		sprite_S212Bitmap		(sprite_S211width*sprite_S211height)+sprite_S211Bitmap	
//
//#define		sprite_S213width		100
//#define		sprite_S213height		60
//#define		sprite_S213Bitmap		(sprite_S212width*sprite_S212height)+sprite_S212Bitmap	
//
//#define		sprite_S214width		100
//#define		sprite_S214height		60
//#define		sprite_S214Bitmap		0
//
//#define		sprite_S215width		100
//#define		sprite_S215height		60
//#define		sprite_S215Bitmap		(sprite_S214width*sprite_S214height)+sprite_S214Bitmap	
//
//#define		sprite_S216width		100
//#define		sprite_S216height		60
//#define		sprite_S216Bitmap		(sprite_S215width*sprite_S215height)+sprite_S215Bitmap	
//
//#define		sprite_S217width		100
//#define		sprite_S217height		60
//#define		sprite_S217Bitmap		(sprite_S216width*sprite_S216height)+sprite_S216Bitmap	
//
//#define		sprite_S218width		100
//#define		sprite_S218height		60
//#define		sprite_S218Bitmap		(sprite_S217width*sprite_S217height)+sprite_S217Bitmap	
//
//#define		sprite_S219width		100
//#define		sprite_S219height		60
//#define		sprite_S219Bitmap		(sprite_S218width*sprite_S218height)+sprite_S218Bitmap	
//
//#define		sprite_S220width		100
//#define		sprite_S220height		60
//#define		sprite_S220Bitmap		(sprite_S219width*sprite_S219height)+sprite_S219Bitmap	
//
//#define		sprite_S221width		100
//#define		sprite_S221height		60
//#define		sprite_S221Bitmap		(sprite_S220width*sprite_S220height)+sprite_S220Bitmap	
//
//#define		sprite_S222width		100
//#define		sprite_S222height		60
//#define		sprite_S222Bitmap		0
//
//#define		sprite_S223width		100
//#define		sprite_S223height		60
//#define		sprite_S223Bitmap		(sprite_S222width*sprite_S222height)+sprite_S222Bitmap	
//
//#define		sprite_S224width		100
//#define		sprite_S224height		60
//#define		sprite_S224Bitmap		(sprite_S223width*sprite_S223height)+sprite_S223Bitmap	
//
//#define		sprite_S225width		100
//#define		sprite_S225height		60
//#define		sprite_S225Bitmap		(sprite_S224width*sprite_S224height)+sprite_S224Bitmap	
//
//#define		sprite_S226width		100
//#define		sprite_S226height		60
//#define		sprite_S226Bitmap		(sprite_S225width*sprite_S225height)+sprite_S225Bitmap	
//
//#define		sprite_S227width		100
//#define		sprite_S227height		60
//#define		sprite_S227Bitmap		(sprite_S226width*sprite_S226height)+sprite_S226Bitmap	
//
//#define		sprite_S228width		100
//#define		sprite_S228height		60
//#define		sprite_S228Bitmap		(sprite_S227width*sprite_S227height)+sprite_S227Bitmap	
//
//#define		sprite_S229width		100
//#define		sprite_S229height		60
//#define		sprite_S229Bitmap		(sprite_S228width*sprite_S228height)+sprite_S228Bitmap	
//
//
//
//
//#define		sprite_S230width			100
//#define		sprite_S230height			60
//#define		sprite_S230Bitmap			0
//
//#define		sprite_S231width			100
//#define		sprite_S231height			60
//#define		sprite_S231Bitmap			(sprite_S230width*sprite_S230height)+sprite_S230Bitmap	
//
//#define		sprite_S232width			100
//#define		sprite_S232height			60
//#define		sprite_S232Bitmap			(sprite_S231width*sprite_S231height)+sprite_S231Bitmap	
//
//#define		sprite_S233width			100
//#define		sprite_S233height			60
//#define		sprite_S233Bitmap			(sprite_S232width*sprite_S232height)+sprite_S232Bitmap	
//
//#define		sprite_S234width			100
//#define		sprite_S234height			60
//#define		sprite_S234Bitmap			(sprite_S233width*sprite_S233height)+sprite_S233Bitmap	
//
//#define		sprite_S235width			100
//#define		sprite_S235height			60
//#define		sprite_S235Bitmap			(sprite_S234width*sprite_S234height)+sprite_S234Bitmap	
//
//#define		sprite_S236width			100
//#define		sprite_S236height			60
//#define		sprite_S236Bitmap			(sprite_S235width*sprite_S235height)+sprite_S235Bitmap	
//
//#define		sprite_S237width			100
//#define		sprite_S237height			60
//#define		sprite_S237Bitmap			(sprite_S236width*sprite_S236height)+sprite_S236Bitmap	
//
//#define		sprite_S238width			100
//#define		sprite_S238height			60
//#define		sprite_S238Bitmap			0
//
//#define		sprite_S239width			100
//#define		sprite_S239height			60
//#define		sprite_S239Bitmap			(sprite_S238width*sprite_S238height)+sprite_S238Bitmap	
//
//#define		sprite_S240width			100
//#define		sprite_S240height			60
//#define		sprite_S240Bitmap			(sprite_S239width*sprite_S239height)+sprite_S239Bitmap	
//
//#define		sprite_S241width			100
//#define		sprite_S241height			60
//#define		sprite_S241Bitmap			(sprite_S240width*sprite_S240height)+sprite_S240Bitmap	
//
//#define		sprite_S242width			100
//#define		sprite_S242height			60
//#define		sprite_S242Bitmap			(sprite_S241width*sprite_S241height)+sprite_S241Bitmap	
//
//#define		sprite_S243width			100
//#define		sprite_S243height			60
//#define		sprite_S243Bitmap			(sprite_S242width*sprite_S242height)+sprite_S242Bitmap	
//
//#define		sprite_S244width			100
//#define		sprite_S244height			60
//#define		sprite_S244Bitmap			(sprite_S243width*sprite_S243height)+sprite_S243Bitmap	
//
//#define		sprite_S245width			100
//#define		sprite_S245height			60
//#define		sprite_S245Bitmap			(sprite_S244width*sprite_S244height)+sprite_S244Bitmap	
//
//#define		sprite_S246width			100
//#define		sprite_S246height			60
//#define		sprite_S246Bitmap			0
//
//#define		sprite_S247width			100
//#define		sprite_S247height			60
//#define		sprite_S247Bitmap			(sprite_S246width*sprite_S246height)+sprite_S246Bitmap	
//
//#define		sprite_S248width			100
//#define		sprite_S248height			60
//#define		sprite_S248Bitmap			(sprite_S247width*sprite_S247height)+sprite_S247Bitmap	
//
//#define		sprite_S249width			100
//#define		sprite_S249height			60
//#define		sprite_S249Bitmap			(sprite_S248width*sprite_S248height)+sprite_S248Bitmap	
//
//#define		sprite_S250width			100
//#define		sprite_S250height			60
//#define		sprite_S250Bitmap			(sprite_S249width*sprite_S249height)+sprite_S249Bitmap	
//
//#define		sprite_S251width			100
//#define		sprite_S251height			60
//#define		sprite_S251Bitmap			(sprite_S250width*sprite_S250height)+sprite_S250Bitmap	
//
//#define		sprite_S252width			100
//#define		sprite_S252height			60
//#define		sprite_S252Bitmap			(sprite_S251width*sprite_S251height)+sprite_S251Bitmap	
//
//#define		sprite_S253width			100
//#define		sprite_S253height			60
//#define		sprite_S253Bitmap			(sprite_S252width*sprite_S252height)+sprite_S252Bitmap	
//
//#define		sprite_S254width			100
//#define		sprite_S254height			60
//#define		sprite_S254Bitmap			0
//
//#define		sprite_S255width			100
//#define		sprite_S255height			60
//#define		sprite_S255Bitmap			(sprite_S254width*sprite_S254height)+sprite_S254Bitmap	
//
//#define		sprite_S256width			100
//#define		sprite_S256height			60
//#define		sprite_S256Bitmap			(sprite_S255width*sprite_S255height)+sprite_S255Bitmap	
//
//#define		sprite_S257width			100
//#define		sprite_S257height			60
//#define		sprite_S257Bitmap			(sprite_S256width*sprite_S256height)+sprite_S256Bitmap	
//
//#define		sprite_S258width			100
//#define		sprite_S258height			60
//#define		sprite_S258Bitmap			(sprite_S257width*sprite_S257height)+sprite_S257Bitmap	
//
//#define		sprite_S259width			100
//#define		sprite_S259height			60
//#define		sprite_S259Bitmap			(sprite_S258width*sprite_S258height)+sprite_S258Bitmap	
//
//#define		sprite_S260width			100
//#define		sprite_S260height			60
//#define		sprite_S260Bitmap			(sprite_S259width*sprite_S259height)+sprite_S259Bitmap	
//
//#define		sprite_S261width			100
//#define		sprite_S261height			60
//#define		sprite_S261Bitmap			(sprite_S260width*sprite_S260height)+sprite_S260Bitmap	
//
//#define		sprite_S262width			100
//#define		sprite_S262height			60
//#define		sprite_S262Bitmap			0
//
//#define		sprite_S263width			100
//#define		sprite_S263height			60
//#define		sprite_S263Bitmap			(sprite_S262width*sprite_S262height)+sprite_S262Bitmap	
//
//#define		sprite_S264width			100
//#define		sprite_S264height			60
//#define		sprite_S264Bitmap			(sprite_S263width*sprite_S263height)+sprite_S263Bitmap	
//
//#define		sprite_S265width			100
//#define		sprite_S265height			60
//#define		sprite_S265Bitmap			(sprite_S264width*sprite_S264height)+sprite_S264Bitmap	
//
//#define		sprite_S266width			100
//#define		sprite_S266height			60
//#define		sprite_S266Bitmap			(sprite_S265width*sprite_S265height)+sprite_S265Bitmap	
//
//#define		sprite_S267width			100
//#define		sprite_S267height			60
//#define		sprite_S267Bitmap			(sprite_S266width*sprite_S266height)+sprite_S266Bitmap	
//
//#define		sprite_S268width			100
//#define		sprite_S268height			60
//#define		sprite_S268Bitmap			(sprite_S267width*sprite_S267height)+sprite_S267Bitmap	
//
//#define		sprite_S269width			100
//#define		sprite_S269height			60
//#define		sprite_S269Bitmap			(sprite_S268width*sprite_S268height)+sprite_S268Bitmap	
//
//#define		sprite_S270width			100
//#define		sprite_S270height			60
//#define		sprite_S270Bitmap			0
//
//#define		sprite_S271width			100
//#define		sprite_S271height			60
//#define		sprite_S271Bitmap			(sprite_S270width*sprite_S270height)+sprite_S270Bitmap	
//
//#define		sprite_S272width			100
//#define		sprite_S272height			60
//#define		sprite_S272Bitmap			(sprite_S271width*sprite_S271height)+sprite_S271Bitmap	
//
//#define		sprite_S273width			100
//#define		sprite_S273height			60
//#define		sprite_S273Bitmap			(sprite_S272width*sprite_S272height)+sprite_S272Bitmap	
//
//#define		sprite_S274width			100
//#define		sprite_S274height			60
//#define		sprite_S274Bitmap			(sprite_S273width*sprite_S273height)+sprite_S273Bitmap	
//
//#define		sprite_S275width			100
//#define		sprite_S275height			60
//#define		sprite_S275Bitmap			(sprite_S274width*sprite_S274height)+sprite_S274Bitmap	
//
//#define		sprite_S276width			100
//#define		sprite_S276height			60
//#define		sprite_S276Bitmap			(sprite_S275width*sprite_S275height)+sprite_S275Bitmap	
//
//#define		sprite_S277width			100
//#define		sprite_S277height			60
//#define		sprite_S277Bitmap			(sprite_S276width*sprite_S276height)+sprite_S276Bitmap	
//
//#define		sprite_S278width			100
//#define		sprite_S278height			60
//#define		sprite_S278Bitmap			0
//
//#define		sprite_S279width			100
//#define		sprite_S279height			60
//#define		sprite_S279Bitmap			(sprite_S278width*sprite_S278height)+sprite_S278Bitmap	
//
//#define		sprite_S280width			100
//#define		sprite_S280height			60
//#define		sprite_S280Bitmap			(sprite_S279width*sprite_S279height)+sprite_S279Bitmap	
//
//#define		sprite_S281width			100
//#define		sprite_S281height			60
//#define		sprite_S281Bitmap			(sprite_S280width*sprite_S280height)+sprite_S280Bitmap	
//
//#define		sprite_S282width			100
//#define		sprite_S282height			60
//#define		sprite_S282Bitmap			(sprite_S281width*sprite_S281height)+sprite_S281Bitmap	
//
//#define		sprite_S283width			100
//#define		sprite_S283height			60
//#define		sprite_S283Bitmap			(sprite_S282width*sprite_S282height)+sprite_S282Bitmap	
//
//#define		sprite_S284width			100
//#define		sprite_S284height			60
//#define		sprite_S284Bitmap			(sprite_S283width*sprite_S283height)+sprite_S283Bitmap	
//
//#define		sprite_S285width			100
//#define		sprite_S285height			60
//#define		sprite_S285Bitmap			(sprite_S284width*sprite_S284height)+sprite_S284Bitmap	
//
//#define		sprite_S286width			100
//#define		sprite_S286height			60
//#define		sprite_S286Bitmap			0
//
//#define		sprite_S287width			100
//#define		sprite_S287height			60
//#define		sprite_S287Bitmap			(sprite_S286width*sprite_S286height)+sprite_S286Bitmap	
//
//#define		sprite_S288width			100
//#define		sprite_S288height			60
//#define		sprite_S288Bitmap			(sprite_S287width*sprite_S287height)+sprite_S287Bitmap	
//
//#define		sprite_S289width			100
//#define		sprite_S289height			60
//#define		sprite_S289Bitmap			(sprite_S288width*sprite_S288height)+sprite_S288Bitmap	
//
//#define		sprite_S290width			100
//#define		sprite_S290height			60
//#define		sprite_S290Bitmap			(sprite_S289width*sprite_S289height)+sprite_S289Bitmap	
//
//#define		sprite_S291width			100
//#define		sprite_S291height			60
//#define		sprite_S291Bitmap			(sprite_S290width*sprite_S290height)+sprite_S290Bitmap	
//
//#define		sprite_S292width			100
//#define		sprite_S292height			60
//#define		sprite_S292Bitmap			(sprite_S291width*sprite_S291height)+sprite_S291Bitmap	
//
//#define		sprite_S293width			100
//#define		sprite_S293height			60
//#define		sprite_S293Bitmap			(sprite_S292width*sprite_S292height)+sprite_S292Bitmap	
//
//#define		sprite_S294width			100
//#define		sprite_S294height			60
//#define		sprite_S294Bitmap			0
//
//#define		sprite_S295width			100
//#define		sprite_S295height			60
//#define		sprite_S295Bitmap			(sprite_S294width*sprite_S294height)+sprite_S294Bitmap	
//
//#define		sprite_S296width			100
//#define		sprite_S296height			60
//#define		sprite_S296Bitmap			(sprite_S295width*sprite_S295height)+sprite_S295Bitmap	
//
//#define		sprite_S297width			100
//#define		sprite_S297height			60
//#define		sprite_S297Bitmap			(sprite_S296width*sprite_S296height)+sprite_S296Bitmap	
//
//#define		sprite_S298width			100
//#define		sprite_S298height			60
//#define		sprite_S298Bitmap			(sprite_S297width*sprite_S297height)+sprite_S297Bitmap	
//
//#define		sprite_S299width			100
//#define		sprite_S299height			60
//#define		sprite_S299Bitmap			(sprite_S298width*sprite_S298height)+sprite_S298Bitmap	
//
//#define		sprite_S300width			100
//#define		sprite_S300height			60
//#define		sprite_S300Bitmap			(sprite_S299width*sprite_S299height)+sprite_S299Bitmap	
//
//#define		sprite_S301width			100
//#define		sprite_S301height			60
//#define		sprite_S301Bitmap			(sprite_S300width*sprite_S300height)+sprite_S300Bitmap	
//
//#define		sprite_S302width			100
//#define		sprite_S302height			60
//#define		sprite_S302Bitmap			0
//
//#define		sprite_S303width			100
//#define		sprite_S303height			60
//#define		sprite_S303Bitmap			(sprite_S302width*sprite_S302height)+sprite_S302Bitmap	
//
//#define		sprite_S304width			100
//#define		sprite_S304height			60
//#define		sprite_S304Bitmap			(sprite_S303width*sprite_S303height)+sprite_S303Bitmap	
//
//#define		sprite_S305width			100
//#define		sprite_S305height			60
//#define		sprite_S305Bitmap			(sprite_S304width*sprite_S304height)+sprite_S304Bitmap	
//												 
//#define		sprite_S306width			100
//#define		sprite_S306height			60
//#define		sprite_S306Bitmap			(sprite_S305width*sprite_S305height)+sprite_S305Bitmap	
//
//#define		sprite_S307width			100
//#define		sprite_S307height			60
//#define		sprite_S307Bitmap			(sprite_S306width*sprite_S306height)+sprite_S306Bitmap	
//
//#define		sprite_S308width			100
//#define		sprite_S308height			60
//#define		sprite_S308Bitmap			(sprite_S307width*sprite_S307height)+sprite_S307Bitmap	
//
//#define		sprite_S309width			100
//#define		sprite_S309height			60
//#define		sprite_S309Bitmap			(sprite_S308width*sprite_S308height)+sprite_S308Bitmap	
//
//
//#define		sprite_S310width			100
//#define		sprite_S310height			60
//#define		sprite_S310Bitmap			0
//
//#define		sprite_S311width			100
//#define		sprite_S311height			60
//#define		sprite_S311Bitmap			(sprite_S310width*sprite_S310height)+sprite_S310Bitmap	
//
//#define		sprite_S312width			100
//#define		sprite_S312height			60
//#define		sprite_S312Bitmap			(sprite_S311width*sprite_S311height)+sprite_S311Bitmap	
//
//#define		sprite_S313width			100
//#define		sprite_S313height			60
//#define		sprite_S313Bitmap			(sprite_S312width*sprite_S312height)+sprite_S312Bitmap	
//
//#define		sprite_S314width			100
//#define		sprite_S314height			60
//#define		sprite_S314Bitmap			(sprite_S313width*sprite_S313height)+sprite_S313Bitmap	
//
//#define		sprite_S315width			100
//#define		sprite_S315height			60
//#define		sprite_S315Bitmap			(sprite_S314width*sprite_S314height)+sprite_S314Bitmap	
//
//#define		sprite_S316width			100
//#define		sprite_S316height			60
//#define		sprite_S316Bitmap			(sprite_S315width*sprite_S315height)+sprite_S315Bitmap	
//
//#define		sprite_S317width			100
//#define		sprite_S317height			60
//#define		sprite_S317Bitmap			(sprite_S316width*sprite_S316height)+sprite_S316Bitmap	
//
//#define		sprite_S318width			100
//#define		sprite_S318height			60
//#define		sprite_S318Bitmap			0
//
//#define		sprite_S319width			100
//#define		sprite_S319height			60
//#define		sprite_S319Bitmap			(sprite_S318width*sprite_S318height)+sprite_S318Bitmap	
//
//#define		sprite_S320width			100
//#define		sprite_S320height			60
//#define		sprite_S320Bitmap			(sprite_S319width*sprite_S319height)+sprite_S319Bitmap	
//
//#define		sprite_S321width			100
//#define		sprite_S321height			60
//#define		sprite_S321Bitmap			(sprite_S320width*sprite_S320height)+sprite_S320Bitmap	
//
//#define		sprite_S322width			100
//#define		sprite_S322height			60
//#define		sprite_S322Bitmap			(sprite_S321width*sprite_S321height)+sprite_S321Bitmap	
//
//#define		sprite_S323width			100
//#define		sprite_S323height			60
//#define		sprite_S323Bitmap			(sprite_S322width*sprite_S322height)+sprite_S322Bitmap	
//
//#define		sprite_S324width			100
//#define		sprite_S324height			60
//#define		sprite_S324Bitmap			(sprite_S323width*sprite_S323height)+sprite_S323Bitmap	
//
//#define		sprite_S325width			100
//#define		sprite_S325height			60
//#define		sprite_S325Bitmap			(sprite_S324width*sprite_S324height)+sprite_S324Bitmap	
//
//#define		sprite_S326width			100
//#define		sprite_S326height			60
//#define		sprite_S326Bitmap			0
//
//#define		sprite_S327width			100
//#define		sprite_S327height			60
//#define		sprite_S327Bitmap			(sprite_S326width*sprite_S326height)+sprite_S326Bitmap	
//
//#define		sprite_S328width			100
//#define		sprite_S328height			60
//#define		sprite_S328Bitmap			(sprite_S327width*sprite_S327height)+sprite_S327Bitmap	
//
//#define		sprite_S329width			100
//#define		sprite_S329height			60
//#define		sprite_S329Bitmap			(sprite_S328width*sprite_S328height)+sprite_S328Bitmap	
//
//#define		sprite_S330width			100
//#define		sprite_S330height			60
//#define		sprite_S330Bitmap			(sprite_S329width*sprite_S329height)+sprite_S329Bitmap	
//
//#define		sprite_S331width			100
//#define		sprite_S331height			60
//#define		sprite_S331Bitmap			(sprite_S330width*sprite_S330height)+sprite_S330Bitmap	
//
//#define		sprite_S332width			100
//#define		sprite_S332height			60
//#define		sprite_S332Bitmap			(sprite_S331width*sprite_S331height)+sprite_S331Bitmap	
//
//#define		sprite_S333width			100
//#define		sprite_S333height			60
//#define		sprite_S333Bitmap			(sprite_S332width*sprite_S332height)+sprite_S332Bitmap	
//
//
//
//#define		sprite_S334width			100
//#define		sprite_S334height			60
//#define		sprite_S334Bitmap			0
//
//#define		sprite_S335width			100
//#define		sprite_S335height			60
//#define		sprite_S335Bitmap			(sprite_S334width*sprite_S334height)+sprite_S334Bitmap	
//
//#define		sprite_S336width			100
//#define		sprite_S336height			60
//#define		sprite_S336Bitmap			(sprite_S335width*sprite_S335height)+sprite_S335Bitmap	
//
//#define		sprite_S337width			100
//#define		sprite_S337height			60
//#define		sprite_S337Bitmap			(sprite_S336width*sprite_S336height)+sprite_S336Bitmap	
//
//#define		sprite_S338width			100
//#define		sprite_S338height			60
//#define		sprite_S338Bitmap			(sprite_S337width*sprite_S337height)+sprite_S337Bitmap	
//
//#define		sprite_S339width			100
//#define		sprite_S339height			60
//#define		sprite_S339Bitmap			(sprite_S338width*sprite_S338height)+sprite_S338Bitmap	
//
//#define		sprite_S340width			100
//#define		sprite_S340height			60
//#define		sprite_S340Bitmap			(sprite_S339width*sprite_S339height)+sprite_S339Bitmap	
//
//#define		sprite_S341width			100
//#define		sprite_S341height			60
//#define		sprite_S341Bitmap			(sprite_S340width*sprite_S340height)+sprite_S340Bitmap	
//
//#define		sprite_S342width			100
//#define		sprite_S342height			60
//#define		sprite_S342Bitmap			0
//
//#define		sprite_S343width			100
//#define		sprite_S343height			60
//#define		sprite_S343Bitmap			(sprite_S342width*sprite_S342height)+sprite_S342Bitmap	
//
//#define		sprite_S344width			100
//#define		sprite_S344height			60
//#define		sprite_S344Bitmap			(sprite_S343width*sprite_S343height)+sprite_S343Bitmap	
//
//#define		sprite_S345width			100
//#define		sprite_S345height			60
//#define		sprite_S345Bitmap			(sprite_S344width*sprite_S344height)+sprite_S344Bitmap	
//
//#define		sprite_S346width			100
//#define		sprite_S346height			60
//#define		sprite_S346Bitmap			(sprite_S345width*sprite_S345height)+sprite_S345Bitmap	
//
//#define		sprite_S347width			100
//#define		sprite_S347height			60
//#define		sprite_S347Bitmap			(sprite_S346width*sprite_S346height)+sprite_S346Bitmap	
//
//#define		sprite_S348width			100
//#define		sprite_S348height			60
//#define		sprite_S348Bitmap			(sprite_S347width*sprite_S347height)+sprite_S347Bitmap	
//
//#define		sprite_S349width			100
//#define		sprite_S349height			60
//#define		sprite_S349Bitmap			(sprite_S348width*sprite_S348height)+sprite_S348Bitmap	
//
//#define		sprite_S350width			100
//#define		sprite_S350height			60
//#define		sprite_S350Bitmap			0
//
//#define		sprite_S351width			100
//#define		sprite_S351height			60
//#define		sprite_S351Bitmap			(sprite_S350width*sprite_S350height)+sprite_S350Bitmap	
//
//#define		sprite_S352width			100
//#define		sprite_S352height			60
//#define		sprite_S352Bitmap			(sprite_S351width*sprite_S351height)+sprite_S351Bitmap	
//
//#define		sprite_S353width			100
//#define		sprite_S353height			60
//#define		sprite_S353Bitmap			(sprite_S352width*sprite_S352height)+sprite_S352Bitmap	
//
//#define		sprite_S354width			100
//#define		sprite_S354height			60
//#define		sprite_S354Bitmap			(sprite_S353width*sprite_S353height)+sprite_S353Bitmap	
//
//#define		sprite_S355width			100
//#define		sprite_S355height			60
//#define		sprite_S355Bitmap			(sprite_S354width*sprite_S354height)+sprite_S354Bitmap	
//
//#define		sprite_S356width			100
//#define		sprite_S356height			60
//#define		sprite_S356Bitmap			(sprite_S355width*sprite_S355height)+sprite_S355Bitmap	
//
//#define		sprite_S357width			100
//#define		sprite_S357height			60
//#define		sprite_S357Bitmap			(sprite_S356width*sprite_S356height)+sprite_S356Bitmap	
//
//#define		sprite_S358width			100
//#define		sprite_S358height			60
//#define		sprite_S358Bitmap			0
//
//#define		sprite_S359width			100
//#define		sprite_S359height			60
//#define		sprite_S359Bitmap			(sprite_S358width*sprite_S358height)+sprite_S358Bitmap	
//
//#define		sprite_S360width			100
//#define		sprite_S360height			60
//#define		sprite_S360Bitmap			(sprite_S359width*sprite_S359height)+sprite_S359Bitmap	
//
//#define		sprite_S361width			100
//#define		sprite_S361height			60
//#define		sprite_S361Bitmap			(sprite_S360width*sprite_S360height)+sprite_S360Bitmap	
//
//#define		sprite_S362width			100
//#define		sprite_S362height			60
//#define		sprite_S362Bitmap			(sprite_S361width*sprite_S361height)+sprite_S361Bitmap	
//
//#define		sprite_S363width			100
//#define		sprite_S363height			60
//#define		sprite_S363Bitmap			(sprite_S362width*sprite_S362height)+sprite_S362Bitmap	
//
//#define		sprite_S364width			100
//#define		sprite_S364height			60
//#define		sprite_S364Bitmap			(sprite_S363width*sprite_S363height)+sprite_S363Bitmap	
//
//#define		sprite_S365width			100
//#define		sprite_S365height			60
//#define		sprite_S365Bitmap			(sprite_S364width*sprite_S364height)+sprite_S364Bitmap	
//
//#define		sprite_S366width			100
//#define		sprite_S366height			60
//#define		sprite_S366Bitmap			0
//
//#define		sprite_S367width			100
//#define		sprite_S367height			60
//#define		sprite_S367Bitmap			(sprite_S366width*sprite_S366height)+sprite_S366Bitmap	
//
//#define		sprite_S368width			100
//#define		sprite_S368height			60
//#define		sprite_S368Bitmap			(sprite_S367width*sprite_S367height)+sprite_S367Bitmap	
//
//#define		sprite_S369width			100
//#define		sprite_S369height			60
//#define		sprite_S369Bitmap			(sprite_S368width*sprite_S368height)+sprite_S368Bitmap	
//
//#define		sprite_S370width			100
//#define		sprite_S370height			60
//#define		sprite_S370Bitmap			(sprite_S369width*sprite_S369height)+sprite_S369Bitmap	
//
//#define		sprite_S371width			100
//#define		sprite_S371height			60
//#define		sprite_S371Bitmap			(sprite_S370width*sprite_S370height)+sprite_S370Bitmap	
//
//#define		sprite_S372width			100
//#define		sprite_S372height			60
//#define		sprite_S372Bitmap			(sprite_S371width*sprite_S371height)+sprite_S371Bitmap	
//
//#define		sprite_S373width			100
//#define		sprite_S373height			60
//#define		sprite_S373Bitmap			(sprite_S372width*sprite_S372height)+sprite_S372Bitmap	
//
//#define		sprite_S374width			100
//#define		sprite_S374height			60
//#define		sprite_S374Bitmap			0
//
//#define		sprite_S375width			100
//#define		sprite_S375height			60
//#define		sprite_S375Bitmap			(sprite_S374width*sprite_S374height)+sprite_S374Bitmap	
//
//#define		sprite_S376width			100
//#define		sprite_S376height			60
//#define		sprite_S376Bitmap			(sprite_S375width*sprite_S375height)+sprite_S375Bitmap	
//
//#define		sprite_S377width			100
//#define		sprite_S377height			60
//#define		sprite_S377Bitmap			(sprite_S376width*sprite_S376height)+sprite_S376Bitmap	
//
//#define		sprite_S378width			100
//#define		sprite_S378height			60
//#define		sprite_S378Bitmap			(sprite_S377width*sprite_S377height)+sprite_S377Bitmap	
//
//#define		sprite_S379width			100
//#define		sprite_S379height			60
//#define		sprite_S379Bitmap			(sprite_S378width*sprite_S378height)+sprite_S378Bitmap	
//
//#define		sprite_S380width			100
//#define		sprite_S380height			60
//#define		sprite_S380Bitmap			(sprite_S379width*sprite_S379height)+sprite_S379Bitmap	
//
//#define		sprite_S381width			100
//#define		sprite_S381height			60
//#define		sprite_S381Bitmap			(sprite_S380width*sprite_S380height)+sprite_S380Bitmap	
//
//#define		sprite_S382width			100
//#define		sprite_S382height			60
//#define		sprite_S382Bitmap			0
//
//#define		sprite_S383width			100
//#define		sprite_S383height			60
//#define		sprite_S383Bitmap			(sprite_S382width*sprite_S382height)+sprite_S382Bitmap	
//
//#define		sprite_S384width			100
//#define		sprite_S384height			60
//#define		sprite_S384Bitmap			(sprite_S383width*sprite_S383height)+sprite_S383Bitmap	
//
//#define		sprite_S385width			100
//#define		sprite_S385height			60
//#define		sprite_S385Bitmap			(sprite_S384width*sprite_S384height)+sprite_S384Bitmap	
//
//#define		sprite_S386width			100
//#define		sprite_S386height			60
//#define		sprite_S386Bitmap			(sprite_S385width*sprite_S385height)+sprite_S385Bitmap	
//
//#define		sprite_S387width			100
//#define		sprite_S387height			60
//#define		sprite_S387Bitmap			(sprite_S386width*sprite_S386height)+sprite_S386Bitmap	
//
//#define		sprite_S388width			100
//#define		sprite_S388height			60
//#define		sprite_S388Bitmap			(sprite_S387width*sprite_S387height)+sprite_S387Bitmap	
//
//#define		sprite_S389width			100
//#define		sprite_S389height			60
//#define		sprite_S389Bitmap			(sprite_S388width*sprite_S388height)+sprite_S388Bitmap	
//
//#define		sprite_S390width			100
//#define		sprite_S390height			60
//#define		sprite_S390Bitmap			0
//
//#define		sprite_S391width			100
//#define		sprite_S391height			60
//#define		sprite_S391Bitmap			(sprite_S390width*sprite_S390height)+sprite_S390Bitmap	
//
//#define		sprite_S392width			100
//#define		sprite_S392height			60
//#define		sprite_S392Bitmap			(sprite_S391width*sprite_S391height)+sprite_S391Bitmap	
//
//#define		sprite_S393width			100
//#define		sprite_S393height			60
//#define		sprite_S393Bitmap			(sprite_S392width*sprite_S392height)+sprite_S392Bitmap	
//
//#define		sprite_S394width			100
//#define		sprite_S394height			60
//#define		sprite_S394Bitmap			(sprite_S393width*sprite_S393height)+sprite_S393Bitmap	
//
//#define		sprite_S395width			100
//#define		sprite_S395height			60
//#define		sprite_S395Bitmap			(sprite_S394width*sprite_S394height)+sprite_S394Bitmap	
//
//#define		sprite_S396width			100
//#define		sprite_S396height			60
//#define		sprite_S396Bitmap			(sprite_S395width*sprite_S395height)+sprite_S395Bitmap	
//
//#define		sprite_S397width			100
//#define		sprite_S397height			60
//#define		sprite_S397Bitmap			(sprite_S396width*sprite_S396height)+sprite_S396Bitmap	
//
//#define		sprite_S398width			100
//#define		sprite_S398height			60
//#define		sprite_S398Bitmap			0
//
//#define		sprite_S399width			100
//#define		sprite_S399height			60
//#define		sprite_S399Bitmap			(sprite_S398width*sprite_S398height)+sprite_S398Bitmap	
//
//#define		sprite_S400width			100
//#define		sprite_S400height			60
//#define		sprite_S400Bitmap			(sprite_S399width*sprite_S399height)+sprite_S399Bitmap	
//
//#define		sprite_S401width			100
//#define		sprite_S401height			60
//#define		sprite_S401Bitmap			(sprite_S400width*sprite_S400height)+sprite_S400Bitmap	
//
//#define		sprite_S402width			100
//#define		sprite_S402height			60
//#define		sprite_S402Bitmap			(sprite_S401width*sprite_S401height)+sprite_S401Bitmap	
//
//#define		sprite_S403width			100
//#define		sprite_S403height			60
//#define		sprite_S403Bitmap			(sprite_S402width*sprite_S402height)+sprite_S402Bitmap	
//
//#define		sprite_S404width			100
//#define		sprite_S404height			60
//#define		sprite_S404Bitmap			(sprite_S403width*sprite_S403height)+sprite_S403Bitmap	
//
//#define		sprite_S405width			100
//#define		sprite_S405height			60
//#define		sprite_S405Bitmap			(sprite_S404width*sprite_S404height)+sprite_S404Bitmap	
//
//#define		sprite_S406width			100
//#define		sprite_S406height			60
//#define		sprite_S406Bitmap			0
//
//#define		sprite_S407width			100
//#define		sprite_S407height			60
//#define		sprite_S407Bitmap			(sprite_S406width*sprite_S406height)+sprite_S406Bitmap	
//
//#define		sprite_S408width			100
//#define		sprite_S408height			60
//#define		sprite_S408Bitmap			(sprite_S407width*sprite_S407height)+sprite_S407Bitmap	
//
//#define		sprite_S409width			100
//#define		sprite_S409height			60
//#define		sprite_S409Bitmap			(sprite_S408width*sprite_S408height)+sprite_S408Bitmap	
//
//#define		sprite_S410width			100
//#define		sprite_S410height			60
//#define		sprite_S410Bitmap			(sprite_S409width*sprite_S409height)+sprite_S409Bitmap	
//
//#define		sprite_S411width			100
//#define		sprite_S411height			60
//#define		sprite_S411Bitmap			(sprite_S410width*sprite_S410height)+sprite_S410Bitmap	
//
//#define		sprite_S412width			100
//#define		sprite_S412height			60
//#define		sprite_S412Bitmap			(sprite_S411width*sprite_S411height)+sprite_S411Bitmap	
//
//#define		sprite_S413width			100
//#define		sprite_S413height			60
//#define		sprite_S413Bitmap			(sprite_S412width*sprite_S412height)+sprite_S412Bitmap	
//
//#define		sprite_S414width			100
//#define		sprite_S414height			60
//#define		sprite_S414Bitmap			0	
//
//#define		sprite_S415width			100
//#define		sprite_S415height			60
//#define		sprite_S415Bitmap			(sprite_S414width*sprite_S414height)+sprite_S414Bitmap	
//
//#define		sprite_S416width			100
//#define		sprite_S416height			60
//#define		sprite_S416Bitmap			(sprite_S415width*sprite_S415height)+sprite_S415Bitmap	
//
//#define		sprite_S417width			100
//#define		sprite_S417height			60
//#define		sprite_S417Bitmap			(sprite_S416width*sprite_S416height)+sprite_S416Bitmap	
//
//#define		sprite_S418width			100
//#define		sprite_S418height			60
//#define		sprite_S418Bitmap			(sprite_S417width*sprite_S417height)+sprite_S417Bitmap	
//
//#define		sprite_S419width			100
//#define		sprite_S419height			60
//#define		sprite_S419Bitmap			(sprite_S418width*sprite_S418height)+sprite_S418Bitmap	
//
//#define		sprite_S420width			100
//#define		sprite_S420height			60
//#define		sprite_S420Bitmap			(sprite_S419width*sprite_S419height)+sprite_S419Bitmap	
//
//#define		sprite_S421width			100
//#define		sprite_S421height			60
//#define		sprite_S421Bitmap			(sprite_S420width*sprite_S420height)+sprite_S420Bitmap	
//
//#define		sprite_999width			190
//#define		sprite_999height			107
//#define		sprite_999Bitmap			0
//
//
//
//
//#define		spool_index1		0
//#define		spool_index2		(spool_index1+0x53F4)
//#define		spool_index3		(spool_index2+0x21E8)
//#define		spool_index4		(spool_index3+0x225E)
//#define		spool_index5		(spool_index4+0x26AF)
//#define		spool_index6		(spool_index5+0x29FE)
//#define		spool_index7		(spool_index6+0x293C)
//#define		spool_index8		(spool_index7+0x2AAB)
//#define		spool_index9		(spool_index8+0x3253)
//#define		spool_index10		(spool_index9+0x2EAC)
//#define		spool_index11		(spool_index10+0x2622)
//#define		spool_index12		(spool_index11+0x2C8F)
//#define		spool_index13		(spool_index12+0x49A5)
//#define		spool_index14		(spool_index13+0x274F)
//#define		spool_index15		(spool_index14+0x20D1)
//#define		spool_index16		(spool_index15+0x2AAB)
//#define		spool_index17		(spool_index16+0x360C)
//#define		spool_index18		(spool_index17+0x47B6)
//#define		spool_index19		(spool_index18+0x23CB)
//#define		spool_index20		(spool_index19+0x2BF4)
//#define		spool_index21		(spool_index20+0x2D3A)
//#define		spool_index22		(spool_index21+0x1DEB)
//#define		spool_index23		(spool_index22+0x2AD6)
//#define		spool_index24		(spool_index23+0x26DF)
//#define		spool_index25		(spool_index24+0x2CAE)
//#define		spool_index26		(spool_index25+0x32AF)
//#define		spool_index27		(spool_index26+0x2940)
//#define		spool_index28		(spool_index27+0x2756)
//#define		spool_index29		(spool_index28+0x2AFD)
//#define		spool_index30		(spool_index29+0x22EC)
//#define		spool_index31		(spool_index30+0x42B2)
//#define		spool_index32		(spool_index31+0x381E)
//#define		spool_index33		(spool_index32+0x3E92)
//#define		spool_index34		(spool_index33+0x2C63)
//#define		spool_index35		(spool_index34+0x21B9)
//#define		spool_index36		(spool_index35+0x268F)
//#define		spool_index37		(spool_index36+0x49E2)
//#define		spool_index38		(spool_index37+0x3A64)
//#define		spool_index39		(spool_index38+0x2684)
//#define		spool_index40		(spool_index39+0x3184)
//#define		spool_index41		(spool_index40+0x2B05)
//#define		spool_index42		(spool_index41+0x32C0)
//#define		spool_index43		(spool_index42+0x2D77)
//#define		spool_index44		(spool_index43+0x21F6)
//#define		spool_index45		(spool_index44+0x2579)
//
//												 
//#define		spool_index1s		0
//#define		spool_index2s		(spool_index1s+6949)
//#define		spool_index3s		(spool_index2s+3358)
//#define		spool_index4s		(spool_index3s+3146)
//#define		spool_index5s		(spool_index4s+3615)
//#define		spool_index6s		(spool_index5s+4083)
//#define		spool_index7s		(spool_index6s+3856)
//#define		spool_index8s		(spool_index7s+4131)
//#define		spool_index9s		(spool_index8s+4347)
//#define		spool_index10s		(spool_index9s+4176)
//#define		spool_index11s		(spool_index10s+3459)
//#define		spool_index12s		(spool_index11s+4099)
//#define		spool_index13s		(spool_index12s+6110)
//#define		spool_index14s		(spool_index13s+3834)
//#define		spool_index15s		(spool_index14s+2969)
//#define		spool_index16s		(spool_index15s+4131)
//#define		spool_index17s		(spool_index16s+4736)
//#define		spool_index18s		(spool_index17s+5856)
//#define		spool_index19s		(spool_index18s+3328)
//#define		spool_index20s		(spool_index19s+4091)
//#define		spool_index21s		(spool_index20s+4140)
//#define		spool_index22s		(spool_index21s+3045)
//#define		spool_index23s		(spool_index22s+4178)
//#define		spool_index24s		(spool_index23s+3541)
//#define		spool_index25s		(spool_index24s+4163)
//#define		spool_index26s		(spool_index25s+4535)
//#define		spool_index27s		(spool_index26s+3962)
//#define		spool_index28s		(spool_index27s+3572)
//#define		spool_index29s		(spool_index28s+4163)
//#define		spool_index30s		(spool_index29s+3420)
//#define		spool_index31s		(spool_index30s+6003)
//#define		spool_index32s		(spool_index31s+4915)
//#define		spool_index33s		(spool_index32s+4844)
//#define		spool_index34s		(spool_index33s+4245)
//#define		spool_index35s		(spool_index34s+3059)
//#define		spool_index36s		(spool_index35s+3553)
//#define		spool_index37s		(spool_index36s+6339)
//#define		spool_index38s		(spool_index37s+4843)
//#define		spool_index39s		(spool_index38s+3731)
//#define		spool_index40s		(spool_index39s+4504)
//#define		spool_index41s		(spool_index40s+4058)
//#define		spool_index42s		(spool_index41s+4719)
//#define		spool_index43s		(spool_index42s+3964)
//#define		spool_index44s		(spool_index43s+3055)
//#define		spool_index45s		(spool_index44s+3422)
//
//												 
//#define		sprite_S62width_s		50
//#define		sprite_S62height_s	30
//#define		sprite_S62Bitmap_s	0	 
//
//#define		sprite_S63width_s		50
//#define		sprite_S63height_s	30
//#define		sprite_S63Bitmap_s	(sprite_S62width_s*sprite_S62height_s)+sprite_S62Bitmap_s
//
//#define		sprite_S64width_s		50
//#define		sprite_S64height_s	30
//#define		sprite_S64Bitmap_s	(sprite_S63width_s*sprite_S63height_s)+sprite_S63Bitmap_s
//
//#define		sprite_S65width_s		50
//#define		sprite_S65height_s	30
//#define		sprite_S65Bitmap_s	(sprite_S64width_s*sprite_S64height_s)+sprite_S64Bitmap_s
//									  	
//#define		sprite_S66width_s		50
//#define		sprite_S66height_s	30
//#define		sprite_S66Bitmap_s	(sprite_S65width_s*sprite_S65height_s)+sprite_S65Bitmap_s
//
//#define		sprite_S67width_s		50
//#define		sprite_S67height_s	30
//#define		sprite_S67Bitmap_s	(sprite_S66width_s*sprite_S66height_s)+sprite_S66Bitmap_s
//
//#define		sprite_S68width_s		50
//#define		sprite_S68height_s	30
//#define		sprite_S68Bitmap_s	(sprite_S67width_s*sprite_S67height_s)+sprite_S67Bitmap_s
//
//#define		sprite_S69width_s		50
//#define		sprite_S69height_s	30
//#define		sprite_S69Bitmap_s	(sprite_S68width_s*sprite_S68height_s)+sprite_S68Bitmap_s
//
//#define		sprite_S70width_s		50
//#define		sprite_S70height_s	30
//#define		sprite_S70Bitmap_s	0	 
//
//#define		sprite_S71width_s		50
//#define		sprite_S71height_s	30
//#define		sprite_S71Bitmap_s	(sprite_S70width_s*sprite_S70height_s)+sprite_S70Bitmap_s
//
//#define		sprite_S72width_s		50
//#define		sprite_S72height_s	30
//#define		sprite_S72Bitmap_s	(sprite_S71width_s*sprite_S71height_s)+sprite_S71Bitmap_s
//
//#define		sprite_S73width_s		50
//#define		sprite_S73height_s	30
//#define		sprite_S73Bitmap_s	(sprite_S72width_s*sprite_S72height_s)+sprite_S72Bitmap_s
//
//#define		sprite_S74width_s		50
//#define		sprite_S74height_s	30
//#define		sprite_S74Bitmap_s	(sprite_S73width_s*sprite_S73height_s)+sprite_S73Bitmap_s
//
//#define		sprite_S75width_s		50
//#define		sprite_S75height_s	30
//#define		sprite_S75Bitmap_s	(sprite_S74width_s*sprite_S74height_s)+sprite_S74Bitmap_s
//
//#define		sprite_S76width_s		50
//#define		sprite_S76height_s	30
//#define		sprite_S76Bitmap_s	(sprite_S75width_s*sprite_S75height_s)+sprite_S75Bitmap_s
//
//#define		sprite_S77width_s		50
//#define		sprite_S77height_s	30
//#define		sprite_S77Bitmap_s	(sprite_S76width_s*sprite_S76height_s)+sprite_S76Bitmap_s
//
//#define		sprite_S78width_s		50
//#define		sprite_S78height_s	30
//#define		sprite_S78Bitmap_s	0	 
//
//#define		sprite_S79width_s		50
//#define		sprite_S79height_s	30
//#define		sprite_S79Bitmap_s	(sprite_S78width_s*sprite_S78height_s)+sprite_S78Bitmap_s
//
//#define		sprite_S80width_s		50
//#define		sprite_S80height_s	30
//#define		sprite_S80Bitmap_s	(sprite_S79width_s*sprite_S79height_s)+sprite_S79Bitmap_s
//
//#define		sprite_S81width_s		50
//#define		sprite_S81height_s	30
//#define		sprite_S81Bitmap_s	(sprite_S80width_s*sprite_S80height_s)+sprite_S80Bitmap_s
//
//#define		sprite_S82width_s		50
//#define		sprite_S82height_s	30
//#define		sprite_S82Bitmap_s	(sprite_S81width_s*sprite_S81height_s)+sprite_S81Bitmap_s
//
//#define		sprite_S83width_s		50
//#define		sprite_S83height_s	30
//#define		sprite_S83Bitmap_s	(sprite_S82width_s*sprite_S82height_s)+sprite_S82Bitmap_s
//
//#define		sprite_S84width_s		50
//#define		sprite_S84height_s	30
//#define		sprite_S84Bitmap_s	(sprite_S83width_s*sprite_S83height_s)+sprite_S83Bitmap_s
//
//#define		sprite_S85width_s		50
//#define		sprite_S85height_s	30
//#define		sprite_S85Bitmap_s	(sprite_S84width_s*sprite_S84height_s)+sprite_S84Bitmap_s
//
//#define		sprite_S86width_s		50
//#define		sprite_S86height_s	30
//#define		sprite_S86Bitmap_s	0	 
//
//#define		sprite_S87width_s		50
//#define		sprite_S87height_s	30
//#define		sprite_S87Bitmap_s	(sprite_S86width_s*sprite_S86height_s)+sprite_S86Bitmap_s
//
//#define		sprite_S88width_s		50
//#define		sprite_S88height_s	30
//#define		sprite_S88Bitmap_s	(sprite_S87width_s*sprite_S87height_s)+sprite_S87Bitmap_s
//
//#define		sprite_S89width_s		50
//#define		sprite_S89height_s	30
//#define		sprite_S89Bitmap_s	(sprite_S88width_s*sprite_S88height_s)+sprite_S88Bitmap_s
//
//#define		sprite_S90width_s		50
//#define		sprite_S90height_s	30
//#define		sprite_S90Bitmap_s	(sprite_S89width_s*sprite_S89height_s)+sprite_S89Bitmap_s
//
//#define		sprite_S91width_s		50
//#define		sprite_S91height_s	30
//#define		sprite_S91Bitmap_s	(sprite_S90width_s*sprite_S90height_s)+sprite_S90Bitmap_s
//
//#define		sprite_S92width_s		50
//#define		sprite_S92height_s	30
//#define		sprite_S92Bitmap_s	(sprite_S91width_s*sprite_S91height_s)+sprite_S91Bitmap_s
//
//#define		sprite_S93width_s		50
//#define		sprite_S93height_s	30
//#define		sprite_S93Bitmap_s	(sprite_S92width_s*sprite_S92height_s)+sprite_S92Bitmap_s
//
//#define		sprite_S94width_s		50
//#define		sprite_S94height_s	30
//#define		sprite_S94Bitmap_s	0	 
//
//#define		sprite_S95width_s		50
//#define		sprite_S95height_s	30
//#define		sprite_S95Bitmap_s	(sprite_S94width_s*sprite_S94height_s)+sprite_S94Bitmap_s
//
//#define		sprite_S96width_s		50
//#define		sprite_S96height_s	30
//#define		sprite_S96Bitmap_s	(sprite_S95width_s*sprite_S95height_s)+sprite_S95Bitmap_s
//
//#define		sprite_S97width_s		50
//#define		sprite_S97height_s	30
//#define		sprite_S97Bitmap_s	(sprite_S96width_s*sprite_S96height_s)+sprite_S96Bitmap_s
//
//#define		sprite_S98width_s		50
//#define		sprite_S98height_s	30
//#define		sprite_S98Bitmap_s	(sprite_S97width_s*sprite_S97height_s)+sprite_S97Bitmap_s
//
//#define		sprite_S99width_s		50
//#define		sprite_S99height_s	30
//#define		sprite_S99Bitmap_s	(sprite_S98width_s*sprite_S98height_s)+sprite_S98Bitmap_s
//
//#define		sprite_S100width_s	50
//#define		sprite_S100height_s	30
//#define		sprite_S100Bitmap_s	(sprite_S99width_s*sprite_S99height_s)+sprite_S99Bitmap_s
//
//#define		sprite_S101width_s	50
//#define		sprite_S101height_s	30
//#define		sprite_S101Bitmap_s	(sprite_S100width_s*sprite_S100height_s)+sprite_S100Bitmap_s
//
//#define		sprite_S102width_s	50
//#define		sprite_S102height_s	30
//#define		sprite_S102Bitmap_s	0
//
//#define		sprite_S103width_s	50
//#define		sprite_S103height_s	30
//#define		sprite_S103Bitmap_s	(sprite_S102width_s*sprite_S102height_s)+sprite_S102Bitmap_s
//
//#define		sprite_S104width_s	50
//#define		sprite_S104height_s	30
//#define		sprite_S104Bitmap_s	(sprite_S103width_s*sprite_S103height_s)+sprite_S103Bitmap_s
//
//#define		sprite_S105width_s	50
//#define		sprite_S105height_s	30
//#define		sprite_S105Bitmap_s	(sprite_S104width_s*sprite_S104height_s)+sprite_S104Bitmap_s	
//
//#define		sprite_S106width_s	50
//#define		sprite_S106height_s	30
//#define		sprite_S106Bitmap_s	(sprite_S105width_s*sprite_S105height_s)+sprite_S105Bitmap_s	
//
//#define		sprite_S107width_s	50
//#define		sprite_S107height_s	30
//#define		sprite_S107Bitmap_s	(sprite_S106width_s*sprite_S106height_s)+sprite_S106Bitmap_s	
//
//#define		sprite_S108width_s	50
//#define		sprite_S108height_s	30
//#define		sprite_S108Bitmap_s	(sprite_S107width_s*sprite_S107height_s)+sprite_S107Bitmap_s	
//
//#define		sprite_S109width_s	50
//#define		sprite_S109height_s	30
//#define		sprite_S109Bitmap_s	(sprite_S108width_s*sprite_S108height_s)+sprite_S108Bitmap_s	
//
//#define		sprite_S110width_s	50
//#define		sprite_S110height_s	30
//#define		sprite_S110Bitmap_s	0
//
//#define		sprite_S111width_s	50
//#define		sprite_S111height_s	30
//#define		sprite_S111Bitmap_s	(sprite_S110width_s*sprite_S110height_s)+sprite_S110Bitmap_s	
//
//#define		sprite_S112width_s	50
//#define		sprite_S112height_s	30
//#define		sprite_S112Bitmap_s	(sprite_S111width_s*sprite_S111height_s)+sprite_S111Bitmap_s	
//
//#define		sprite_S113width_s	50
//#define		sprite_S113height_s	30
//#define		sprite_S113Bitmap_s	(sprite_S112width_s*sprite_S112height_s)+sprite_S112Bitmap_s	
//
//#define		sprite_S114width_s	50
//#define		sprite_S114height_s	30
//#define		sprite_S114Bitmap_s	(sprite_S113width_s*sprite_S113height_s)+sprite_S113Bitmap_s	
//
//#define		sprite_S115width_s	50
//#define		sprite_S115height_s	30
//#define		sprite_S115Bitmap_s	(sprite_S114width_s*sprite_S114height_s)+sprite_S114Bitmap_s	
//
//#define		sprite_S116width_s	50
//#define		sprite_S116height_s	30
//#define		sprite_S116Bitmap_s	(sprite_S115width_s*sprite_S115height_s)+sprite_S115Bitmap_s	
//
//#define		sprite_S117width_s	50
//#define		sprite_S117height_s	30
//#define		sprite_S117Bitmap_s	(sprite_S116width_s*sprite_S116height_s)+sprite_S116Bitmap_s	
//
//#define		sprite_S118width_s	50
//#define		sprite_S118height_s	30
//#define		sprite_S118Bitmap_s	0
//
//#define		sprite_S119width_s	50
//#define		sprite_S119height_s	30
//#define		sprite_S119Bitmap_s	(sprite_S118width_s*sprite_S118height_s)+sprite_S118Bitmap_s	
//
//#define		sprite_S120width_s	50
//#define		sprite_S120height_s	30
//#define		sprite_S120Bitmap_s	(sprite_S119width_s*sprite_S119height_s)+sprite_S119Bitmap_s	
//
//#define		sprite_S121width_s	50
//#define		sprite_S121height_s	30
//#define		sprite_S121Bitmap_s	(sprite_S120width_s*sprite_S120height_s)+sprite_S120Bitmap_s	
//
//#define		sprite_S122width_s	50
//#define		sprite_S122height_s	30
//#define		sprite_S122Bitmap_s	(sprite_S121width_s*sprite_S121height_s)+sprite_S121Bitmap_s	
//
//#define		sprite_S123width_s	50
//#define		sprite_S123height_s	30
//#define		sprite_S123Bitmap_s	(sprite_S122width_s*sprite_S122height_s)+sprite_S122Bitmap_s	
//
//#define		sprite_S124width_s	50
//#define		sprite_S124height_s	30
//#define		sprite_S124Bitmap_s	(sprite_S123width_s*sprite_S123height_s)+sprite_S123Bitmap_s	
//
//#define		sprite_S125width_s	50
//#define		sprite_S125height_s	30
//#define		sprite_S125Bitmap_s	(sprite_S124width_s*sprite_S124height_s)+sprite_S124Bitmap_s	
//
//#define		sprite_S126width_s	50
//#define		sprite_S126height_s	30
//#define		sprite_S126Bitmap_s	0
//
//#define		sprite_S127width_s	50
//#define		sprite_S127height_s	30
//#define		sprite_S127Bitmap_s	(sprite_S126width_s*sprite_S126height_s)+sprite_S126Bitmap_s	
//
//#define		sprite_S128width_s	50
//#define		sprite_S128height_s	30
//#define		sprite_S128Bitmap_s	(sprite_S127width_s*sprite_S127height_s)+sprite_S127Bitmap_s	
//
//#define		sprite_S129width_s	50
//#define		sprite_S129height_s	30
//#define		sprite_S129Bitmap_s	(sprite_S128width_s*sprite_S128height_s)+sprite_S128Bitmap_s	
//
//#define		sprite_S130width_s	50
//#define		sprite_S130height_s	30
//#define		sprite_S130Bitmap_s	(sprite_S129width_s*sprite_S129height_s)+sprite_S129Bitmap_s	
//
//#define		sprite_S131width_s	50
//#define		sprite_S131height_s	30
//#define		sprite_S131Bitmap_s	(sprite_S130width_s*sprite_S130height_s)+sprite_S130Bitmap_s	
//
//#define		sprite_S132width_s	50
//#define		sprite_S132height_s	30
//#define		sprite_S132Bitmap_s	(sprite_S131width_s*sprite_S131height_s)+sprite_S131Bitmap_s	
//
//#define		sprite_S133width_s	50
//#define		sprite_S133height_s	30
//#define		sprite_S133Bitmap_s	(sprite_S132width_s*sprite_S132height_s)+sprite_S132Bitmap_s	
//
//#define		sprite_S134width_s	50
//#define		sprite_S134height_s	30
//#define		sprite_S134Bitmap_s	0
//
//#define		sprite_S135width_s	50
//#define		sprite_S135height_s	30
//#define		sprite_S135Bitmap_s	(sprite_S134width_s*sprite_S134height_s)+sprite_S134Bitmap_s	
//
//#define		sprite_S136width_s	50
//#define		sprite_S136height_s	30
//#define		sprite_S136Bitmap_s	(sprite_S135width_s*sprite_S135height_s)+sprite_S135Bitmap_s	
//
//#define		sprite_S137width_s	50
//#define		sprite_S137height_s	30
//#define		sprite_S137Bitmap_s	(sprite_S136width_s*sprite_S136height_s)+sprite_S136Bitmap_s	
//
//#define		sprite_S138width_s	50
//#define		sprite_S138height_s	30
//#define		sprite_S138Bitmap_s	(sprite_S137width_s*sprite_S137height_s)+sprite_S137Bitmap_s	
//
//#define		sprite_S139width_s	50
//#define		sprite_S139height_s	30
//#define		sprite_S139Bitmap_s	(sprite_S138width_s*sprite_S138height_s)+sprite_S138Bitmap_s	
//
//#define		sprite_S140width_s	50
//#define		sprite_S140height_s	30
//#define		sprite_S140Bitmap_s	(sprite_S139width_s*sprite_S139height_s)+sprite_S139Bitmap_s	
//
//#define		sprite_S141width_s	50
//#define		sprite_S141height_s	30
//#define		sprite_S141Bitmap_s	(sprite_S140width_s*sprite_S140height_s)+sprite_S140Bitmap_s	
//
//#define		sprite_S142width_s	50
//#define		sprite_S142height_s	30
//#define		sprite_S142Bitmap_s	0
//
//#define		sprite_S143width_s	50
//#define		sprite_S143height_s	30
//#define		sprite_S143Bitmap_s	(sprite_S142width_s*sprite_S142height_s)+sprite_S142Bitmap_s	
//
//#define		sprite_S144width_s	50
//#define		sprite_S144height_s	30
//#define		sprite_S144Bitmap_s	(sprite_S143width_s*sprite_S143height_s)+sprite_S143Bitmap_s	
//
//#define		sprite_S145width_s	50
//#define		sprite_S145height_s	30
//#define		sprite_S145Bitmap_s	(sprite_S144width_s*sprite_S144height_s)+sprite_S144Bitmap_s	
//
//#define		sprite_S146width_s	50
//#define		sprite_S146height_s	30
//#define		sprite_S146Bitmap_s	(sprite_S145width_s*sprite_S145height_s)+sprite_S145Bitmap_s	
//
//#define		sprite_S147width_s	50
//#define		sprite_S147height_s	30
//#define		sprite_S147Bitmap_s	(sprite_S146width_s*sprite_S146height_s)+sprite_S146Bitmap_s	
//
//#define		sprite_S148width_s	50
//#define		sprite_S148height_s	30
//#define		sprite_S148Bitmap_s	(sprite_S147width_s*sprite_S147height_s)+sprite_S147Bitmap_s	
//
//#define		sprite_S149width_s	50
//#define		sprite_S149height_s	30
//#define		sprite_S149Bitmap_s	(sprite_S148width_s*sprite_S148height_s)+sprite_S148Bitmap_s	
//
//#define		sprite_S150width_s	50
//#define		sprite_S150height_s	30
//#define		sprite_S150Bitmap_s	0
//
//#define		sprite_S151width_s	50
//#define		sprite_S151height_s	30
//#define		sprite_S151Bitmap_s	(sprite_S150width_s*sprite_S150height_s)+sprite_S150Bitmap_s	
//
//#define		sprite_S152width_s	50
//#define		sprite_S152height_s	30
//#define		sprite_S152Bitmap_s	(sprite_S151width_s*sprite_S151height_s)+sprite_S151Bitmap_s	
//
//#define		sprite_S153width_s	50
//#define		sprite_S153height_s	30
//#define		sprite_S153Bitmap_s	(sprite_S152width_s*sprite_S152height_s)+sprite_S152Bitmap_s	
//
//#define		sprite_S154width_s	50
//#define		sprite_S154height_s	30
//#define		sprite_S154Bitmap_s	(sprite_S153width_s*sprite_S153height_s)+sprite_S153Bitmap_s	
//
//#define		sprite_S155width_s	50
//#define		sprite_S155height_s	30
//#define		sprite_S155Bitmap_s	(sprite_S154width_s*sprite_S154height_s)+sprite_S154Bitmap_s	
//
//#define		sprite_S156width_s	50
//#define		sprite_S156height_s	30
//#define		sprite_S156Bitmap_s	(sprite_S155width_s*sprite_S155height_s)+sprite_S155Bitmap_s	
//
//#define		sprite_S157width_s	50
//#define		sprite_S157height_s	30
//#define		sprite_S157Bitmap_s	(sprite_S156width_s*sprite_S156height_s)+sprite_S156Bitmap_s	
//
//#define		sprite_S158width_s	50
//#define		sprite_S158height_s	30
//#define		sprite_S158Bitmap_s	0
//
//#define		sprite_S159width_s	50
//#define		sprite_S159height_s	30
//#define		sprite_S159Bitmap_s	(sprite_S158width_s*sprite_S158height_s)+sprite_S158Bitmap_s	
//
//#define		sprite_S160width_s	50
//#define		sprite_S160height_s	30
//#define		sprite_S160Bitmap_s	(sprite_S159width_s*sprite_S159height_s)+sprite_S159Bitmap_s	
//
//#define		sprite_S161width_s	50
//#define		sprite_S161height_s	30
//#define		sprite_S161Bitmap_s	(sprite_S160width_s*sprite_S160height_s)+sprite_S160Bitmap_s	
//
//#define		sprite_S162width_s	50
//#define		sprite_S162height_s	30
//#define		sprite_S162Bitmap_s	(sprite_S161width_s*sprite_S161height_s)+sprite_S161Bitmap_s	
//
//#define		sprite_S163width_s	50
//#define		sprite_S163height_s	30
//#define		sprite_S163Bitmap_s	(sprite_S162width_s*sprite_S162height_s)+sprite_S162Bitmap_s	
//
//#define		sprite_S164width_s	50
//#define		sprite_S164height_s	30
//#define		sprite_S164Bitmap_s	(sprite_S163width_s*sprite_S163height_s)+sprite_S163Bitmap_s	
//
//#define		sprite_S165width_s	50
//#define		sprite_S165height_s	30
//#define		sprite_S165Bitmap_s	(sprite_S164width_s*sprite_S164height_s)+sprite_S164Bitmap_s	
//
//#define		sprite_S166width_s	50
//#define		sprite_S166height_s	30
//#define		sprite_S166Bitmap_s	0
//
//#define		sprite_S167width_s	50
//#define		sprite_S167height_s	30
//#define		sprite_S167Bitmap_s	(sprite_S166width_s*sprite_S166height_s)+sprite_S166Bitmap_s	
//
//#define		sprite_S168width_s	50
//#define		sprite_S168height_s	30
//#define		sprite_S168Bitmap_s	(sprite_S167width_s*sprite_S167height_s)+sprite_S167Bitmap_s	
//
//#define		sprite_S169width_s	50
//#define		sprite_S169height_s	30
//#define		sprite_S169Bitmap_s	(sprite_S168width_s*sprite_S168height_s)+sprite_S168Bitmap_s	
//
//#define		sprite_S170width_s	50
//#define		sprite_S170height_s	30
//#define		sprite_S170Bitmap_s	(sprite_S169width_s*sprite_S169height_s)+sprite_S169Bitmap_s	
//
//#define		sprite_S171width_s	50
//#define		sprite_S171height_s	30
//#define		sprite_S171Bitmap_s	(sprite_S170width_s*sprite_S170height_s)+sprite_S170Bitmap_s	
//
//#define		sprite_S172width_s	50
//#define		sprite_S172height_s	30
//#define		sprite_S172Bitmap_s	(sprite_S171width_s*sprite_S171height_s)+sprite_S171Bitmap_s	
//
//#define		sprite_S173width_s	50
//#define		sprite_S173height_s	30
//#define		sprite_S173Bitmap_s	(sprite_S172width_s*sprite_S172height_s)+sprite_S172Bitmap_s	
//
//#define		sprite_S174width_s	50
//#define		sprite_S174height_s	30
//#define		sprite_S174Bitmap_s	0
//
//#define		sprite_S175width_s	50
//#define		sprite_S175height_s	30
//#define		sprite_S175Bitmap_s	(sprite_S174width_s*sprite_S174height_s)+sprite_S174Bitmap_s	
//
//#define		sprite_S176width_s	50
//#define		sprite_S176height_s	30
//#define		sprite_S176Bitmap_s	(sprite_S175width_s*sprite_S175height_s)+sprite_S175Bitmap_s	
//
//#define		sprite_S177width_s	50
//#define		sprite_S177height_s	30
//#define		sprite_S177Bitmap_s	(sprite_S176width_s*sprite_S176height_s)+sprite_S176Bitmap_s	
//
//#define		sprite_S178width_s	50
//#define		sprite_S178height_s	30
//#define		sprite_S178Bitmap_s	(sprite_S177width_s*sprite_S177height_s)+sprite_S177Bitmap_s	
//
//#define		sprite_S179width_s	50
//#define		sprite_S179height_s	30
//#define		sprite_S179Bitmap_s	(sprite_S178width_s*sprite_S178height_s)+sprite_S178Bitmap_s	
//
//#define		sprite_S180width_s	50
//#define		sprite_S180height_s	30
//#define		sprite_S180Bitmap_s	(sprite_S179width_s*sprite_S179height_s)+sprite_S179Bitmap_s	
//
//#define		sprite_S181width_s	50
//#define		sprite_S181height_s	30
//#define		sprite_S181Bitmap_s	(sprite_S180width_s*sprite_S180height_s)+sprite_S180Bitmap_s	
//
//#define		sprite_S182width_s	50
//#define		sprite_S182height_s	30
//#define		sprite_S182Bitmap_s	0
//
//#define		sprite_S183width_s	50
//#define		sprite_S183height_s	30
//#define		sprite_S183Bitmap_s	(sprite_S182width_s*sprite_S182height_s)+sprite_S182Bitmap_s	
//
//#define		sprite_S184width_s	50
//#define		sprite_S184height_s	30
//#define		sprite_S184Bitmap_s	(sprite_S183width_s*sprite_S183height_s)+sprite_S183Bitmap_s	
//
//#define		sprite_S185width_s	50
//#define		sprite_S185height_s	30
//#define		sprite_S185Bitmap_s	(sprite_S184width_s*sprite_S184height_s)+sprite_S184Bitmap_s	
//
//#define		sprite_S186width_s	50
//#define		sprite_S186height_s	30
//#define		sprite_S186Bitmap_s	(sprite_S185width_s*sprite_S185height_s)+sprite_S185Bitmap_s	
//
//#define		sprite_S187width_s	50
//#define		sprite_S187height_s	30
//#define		sprite_S187Bitmap_s	(sprite_S186width_s*sprite_S186height_s)+sprite_S186Bitmap_s	
//
//#define		sprite_S188width_s	50
//#define		sprite_S188height_s	30
//#define		sprite_S188Bitmap_s	(sprite_S187width_s*sprite_S187height_s)+sprite_S187Bitmap_s	
//
//#define		sprite_S189width_s	50
//#define		sprite_S189height_s	30
//#define		sprite_S189Bitmap_s	(sprite_S188width_s*sprite_S188height_s)+sprite_S188Bitmap_s	
//
//#define		sprite_S190width_s	50
//#define		sprite_S190height_s	30
//#define		sprite_S190Bitmap_s	0
//
//#define		sprite_S191width_s	50
//#define		sprite_S191height_s	30
//#define		sprite_S191Bitmap_s	(sprite_S190width_s*sprite_S190height_s)+sprite_S190Bitmap_s	
//
//#define		sprite_S192width_s	50
//#define		sprite_S192height_s	30
//#define		sprite_S192Bitmap_s	(sprite_S191width_s*sprite_S191height_s)+sprite_S191Bitmap_s	
//
//#define		sprite_S193width_s	50
//#define		sprite_S193height_s	30
//#define		sprite_S193Bitmap_s	(sprite_S192width_s*sprite_S192height_s)+sprite_S192Bitmap_s	
//
//#define		sprite_S194width_s	50
//#define		sprite_S194height_s	30
//#define		sprite_S194Bitmap_s	(sprite_S193width_s*sprite_S193height_s)+sprite_S193Bitmap_s	
//
//#define		sprite_S195width_s	50
//#define		sprite_S195height_s	30
//#define		sprite_S195Bitmap_s	(sprite_S194width_s*sprite_S194height_s)+sprite_S194Bitmap_s	
//
//#define		sprite_S196width_s	50
//#define		sprite_S196height_s	30
//#define		sprite_S196Bitmap_s	(sprite_S195width_s*sprite_S195height_s)+sprite_S195Bitmap_s	
//
//#define		sprite_S197width_s	50
//#define		sprite_S197height_s	30
//#define		sprite_S197Bitmap_s	(sprite_S196width_s*sprite_S196height_s)+sprite_S196Bitmap_s	
//
//#define		sprite_S198width_s	50
//#define		sprite_S198height_s	30
//#define		sprite_S198Bitmap_s	0
//
//#define		sprite_S199width_s	50
//#define		sprite_S199height_s	30
//#define		sprite_S199Bitmap_s	(sprite_S198width_s*sprite_S198height_s)+sprite_S198Bitmap_s	
//
//#define		sprite_S200width_s	50
//#define		sprite_S200height_s	30
//#define		sprite_S200Bitmap_s	(sprite_S199width_s*sprite_S199height_s)+sprite_S199Bitmap_s	
//
//#define		sprite_S201width_s	50
//#define		sprite_S201height_s	30
//#define		sprite_S201Bitmap_s	(sprite_S200width_s*sprite_S200height_s)+sprite_S200Bitmap_s	
//
//#define		sprite_S202width_s	50
//#define		sprite_S202height_s	30
//#define		sprite_S202Bitmap_s	(sprite_S201width_s*sprite_S201height_s)+sprite_S201Bitmap_s	
//
//#define		sprite_S203width_s	50
//#define		sprite_S203height_s	30
//#define		sprite_S203Bitmap_s	(sprite_S202width_s*sprite_S202height_s)+sprite_S202Bitmap_s	
//
//#define		sprite_S204width_s	50
//#define		sprite_S204height_s	30
//#define		sprite_S204Bitmap_s	(sprite_S203width_s*sprite_S203height_s)+sprite_S203Bitmap_s	
//
//#define		sprite_S205width_s	50
//#define		sprite_S205height_s	30
//#define		sprite_S205Bitmap_s	(sprite_S204width_s*sprite_S204height_s)+sprite_S204Bitmap_s	
//
//												 
//												 
//												 
//												 
//												 
//												 
//												 
//#define		sprite_S206width_s	50
//#define		sprite_S206height_s	30
//#define		sprite_S206Bitmap_s	0
//
//#define		sprite_S207width_s	50
//#define		sprite_S207height_s	30
//#define		sprite_S207Bitmap_s	(sprite_S206width_s*sprite_S206height_s)+sprite_S206Bitmap_s	
//
//#define		sprite_S208width_s	50
//#define		sprite_S208height_s	30
//#define		sprite_S208Bitmap_s	(sprite_S207width_s*sprite_S207height_s)+sprite_S207Bitmap_s	
//
//#define		sprite_S209width_s	50
//#define		sprite_S209height_s	30
//#define		sprite_S209Bitmap_s	(sprite_S208width_s*sprite_S208height_s)+sprite_S208Bitmap_s	
//
//#define		sprite_S210width_s	50
//#define		sprite_S210height_s	30
//#define		sprite_S210Bitmap_s	(sprite_S209width_s*sprite_S209height_s)+sprite_S209Bitmap_s	
//
//#define		sprite_S211width_s	50
//#define		sprite_S211height_s	30
//#define		sprite_S211Bitmap_s	(sprite_S210width_s*sprite_S210height_s)+sprite_S210Bitmap_s	
//
//#define		sprite_S212width_s	50
//#define		sprite_S212height_s	30
//#define		sprite_S212Bitmap_s	(sprite_S211width_s*sprite_S211height_s)+sprite_S211Bitmap_s	
//
//#define		sprite_S213width_s	50
//#define		sprite_S213height_s	30
//#define		sprite_S213Bitmap_s	(sprite_S212width_s*sprite_S212height_s)+sprite_S212Bitmap_s	
//
//#define		sprite_S214width_s	50
//#define		sprite_S214height_s	30
//#define		sprite_S214Bitmap_s	0
//
//#define		sprite_S215width_s	50
//#define		sprite_S215height_s	30
//#define		sprite_S215Bitmap_s	(sprite_S214width_s*sprite_S214height_s)+sprite_S214Bitmap_s	
//
//#define		sprite_S216width_s	50
//#define		sprite_S216height_s	30
//#define		sprite_S216Bitmap_s	(sprite_S215width_s*sprite_S215height_s)+sprite_S215Bitmap_s	
//
//#define		sprite_S217width_s	50
//#define		sprite_S217height_s	30
//#define		sprite_S217Bitmap_s	(sprite_S216width_s*sprite_S216height_s)+sprite_S216Bitmap_s	
//
//#define		sprite_S218width_s	50
//#define		sprite_S218height_s	30
//#define		sprite_S218Bitmap_s	(sprite_S217width_s*sprite_S217height_s)+sprite_S217Bitmap_s	
//
//#define		sprite_S219width_s	50
//#define		sprite_S219height_s	30
//#define		sprite_S219Bitmap_s	(sprite_S218width_s*sprite_S218height_s)+sprite_S218Bitmap_s	
//
//#define		sprite_S220width_s	50
//#define		sprite_S220height_s	30
//#define		sprite_S220Bitmap_s	(sprite_S219width_s*sprite_S219height_s)+sprite_S219Bitmap_s	
//
//#define		sprite_S221width_s	50
//#define		sprite_S221height_s	30
//#define		sprite_S221Bitmap_s	(sprite_S220width_s*sprite_S220height_s)+sprite_S220Bitmap_s	
//
//#define		sprite_S222width_s	50
//#define		sprite_S222height_s	30
//#define		sprite_S222Bitmap_s	0
//
//#define		sprite_S223width_s	50
//#define		sprite_S223height_s	30
//#define		sprite_S223Bitmap_s	(sprite_S222width_s*sprite_S222height_s)+sprite_S222Bitmap_s	
//
//#define		sprite_S224width_s	50
//#define		sprite_S224height_s	30
//#define		sprite_S224Bitmap_s	(sprite_S223width_s*sprite_S223height_s)+sprite_S223Bitmap_s	
//
//#define		sprite_S225width_s	50
//#define		sprite_S225height_s	30
//#define		sprite_S225Bitmap_s	(sprite_S224width_s*sprite_S224height_s)+sprite_S224Bitmap_s	
//
//#define		sprite_S226width_s	50
//#define		sprite_S226height_s	30
//#define		sprite_S226Bitmap_s	(sprite_S225width_s*sprite_S225height_s)+sprite_S225Bitmap_s	
//
//#define		sprite_S227width_s	50
//#define		sprite_S227height_s	30
//#define		sprite_S227Bitmap_s	(sprite_S226width_s*sprite_S226height_s)+sprite_S226Bitmap_s	
//
//#define		sprite_S228width_s	50
//#define		sprite_S228height_s	30
//#define		sprite_S228Bitmap_s	(sprite_S227width_s*sprite_S227height_s)+sprite_S227Bitmap_s	
//
//#define		sprite_S229width_s	50
//#define		sprite_S229height_s	30
//#define		sprite_S229Bitmap_s	(sprite_S228width_s*sprite_S228height_s)+sprite_S228Bitmap_s	
//
//
//
//
//#define		sprite_S230width_s		50
//#define		sprite_S230height_s		30
//#define		sprite_S230Bitmap_s		0
//
//#define		sprite_S231width_s		50
//#define		sprite_S231height_s		30
//#define		sprite_S231Bitmap_s		(sprite_S230width_s*sprite_S230height_s)+sprite_S230Bitmap_s	
//
//#define		sprite_S232width_s		50
//#define		sprite_S232height_s		30
//#define		sprite_S232Bitmap_s		(sprite_S231width_s*sprite_S231height_s)+sprite_S231Bitmap_s	
//
//#define		sprite_S233width_s		50
//#define		sprite_S233height_s		30
//#define		sprite_S233Bitmap_s		(sprite_S232width_s*sprite_S232height_s)+sprite_S232Bitmap_s	
//
//#define		sprite_S234width_s		50
//#define		sprite_S234height_s		30
//#define		sprite_S234Bitmap_s		(sprite_S233width_s*sprite_S233height_s)+sprite_S233Bitmap_s	
//
//#define		sprite_S235width_s		50
//#define		sprite_S235height_s		30
//#define		sprite_S235Bitmap_s		(sprite_S234width_s*sprite_S234height_s)+sprite_S234Bitmap_s	
//
//#define		sprite_S236width_s		50
//#define		sprite_S236height_s		30
//#define		sprite_S236Bitmap_s		(sprite_S235width_s*sprite_S235height_s)+sprite_S235Bitmap_s	
//
//#define		sprite_S237width_s		50
//#define		sprite_S237height_s		30
//#define		sprite_S237Bitmap_s		(sprite_S236width_s*sprite_S236height_s)+sprite_S236Bitmap_s	
//
//#define		sprite_S238width_s		50
//#define		sprite_S238height_s		30
//#define		sprite_S238Bitmap_s		0
//
//#define		sprite_S239width_s		50
//#define		sprite_S239height_s		30
//#define		sprite_S239Bitmap_s		(sprite_S238width_s*sprite_S238height_s)+sprite_S238Bitmap_s	
//
//#define		sprite_S240width_s		50
//#define		sprite_S240height_s		30
//#define		sprite_S240Bitmap_s		(sprite_S239width_s*sprite_S239height_s)+sprite_S239Bitmap_s	
//
//#define		sprite_S241width_s		50
//#define		sprite_S241height_s		30
//#define		sprite_S241Bitmap_s		(sprite_S240width_s*sprite_S240height_s)+sprite_S240Bitmap_s	
//
//#define		sprite_S242width_s		50
//#define		sprite_S242height_s		30
//#define		sprite_S242Bitmap_s		(sprite_S241width_s*sprite_S241height_s)+sprite_S241Bitmap_s	
//
//#define		sprite_S243width_s		50
//#define		sprite_S243height_s		30
//#define		sprite_S243Bitmap_s		(sprite_S242width_s*sprite_S242height_s)+sprite_S242Bitmap_s	
//
//#define		sprite_S244width_s		50
//#define		sprite_S244height_s		30
//#define		sprite_S244Bitmap_s		(sprite_S243width_s*sprite_S243height_s)+sprite_S243Bitmap_s	
//
//#define		sprite_S245width_s		50
//#define		sprite_S245height_s		30
//#define		sprite_S245Bitmap_s		(sprite_S244width_s*sprite_S244height_s)+sprite_S244Bitmap_s	
//
//#define		sprite_S246width_s		50
//#define		sprite_S246height_s		30
//#define		sprite_S246Bitmap_s		0
//
//#define		sprite_S247width_s		50
//#define		sprite_S247height_s		30
//#define		sprite_S247Bitmap_s		(sprite_S246width_s*sprite_S246height_s)+sprite_S246Bitmap_s	
//
//#define		sprite_S248width_s		50
//#define		sprite_S248height_s		30
//#define		sprite_S248Bitmap_s		(sprite_S247width_s*sprite_S247height_s)+sprite_S247Bitmap_s	
//
//#define		sprite_S249width_s		50
//#define		sprite_S249height_s		30
//#define		sprite_S249Bitmap_s		(sprite_S248width_s*sprite_S248height_s)+sprite_S248Bitmap_s	
//
//#define		sprite_S250width_s		50
//#define		sprite_S250height_s		30
//#define		sprite_S250Bitmap_s		(sprite_S249width_s*sprite_S249height_s)+sprite_S249Bitmap_s	
//
//#define		sprite_S251width_s		50
//#define		sprite_S251height_s		30
//#define		sprite_S251Bitmap_s		(sprite_S250width_s*sprite_S250height_s)+sprite_S250Bitmap_s	
//
//#define		sprite_S252width_s		50
//#define		sprite_S252height_s		30
//#define		sprite_S252Bitmap_s		(sprite_S251width_s*sprite_S251height_s)+sprite_S251Bitmap_s	
//
//#define		sprite_S253width_s		50
//#define		sprite_S253height_s		30
//#define		sprite_S253Bitmap_s		(sprite_S252width_s*sprite_S252height_s)+sprite_S252Bitmap_s	
//
//#define		sprite_S254width_s		50
//#define		sprite_S254height_s		30
//#define		sprite_S254Bitmap_s		0
//
//#define		sprite_S255width_s		50
//#define		sprite_S255height_s		30
//#define		sprite_S255Bitmap_s		(sprite_S254width_s*sprite_S254height_s)+sprite_S254Bitmap_s	
//
//#define		sprite_S256width_s		50
//#define		sprite_S256height_s		30
//#define		sprite_S256Bitmap_s		(sprite_S255width_s*sprite_S255height_s)+sprite_S255Bitmap_s	
//
//#define		sprite_S257width_s		50
//#define		sprite_S257height_s		30
//#define		sprite_S257Bitmap_s		(sprite_S256width_s*sprite_S256height_s)+sprite_S256Bitmap_s	
//
//#define		sprite_S258width_s		50
//#define		sprite_S258height_s		30
//#define		sprite_S258Bitmap_s		(sprite_S257width_s*sprite_S257height_s)+sprite_S257Bitmap_s	
//
//#define		sprite_S259width_s		50
//#define		sprite_S259height_s		30
//#define		sprite_S259Bitmap_s		(sprite_S258width_s*sprite_S258height_s)+sprite_S258Bitmap_s	
//
//#define		sprite_S260width_s		50
//#define		sprite_S260height_s		30
//#define		sprite_S260Bitmap_s		(sprite_S259width_s*sprite_S259height_s)+sprite_S259Bitmap_s	
//
//#define		sprite_S261width_s		50
//#define		sprite_S261height_s		30
//#define		sprite_S261Bitmap_s		(sprite_S260width_s*sprite_S260height_s)+sprite_S260Bitmap_s	
//
//#define		sprite_S262width_s		50
//#define		sprite_S262height_s		30
//#define		sprite_S262Bitmap_s		0
//
//#define		sprite_S263width_s		50
//#define		sprite_S263height_s		30
//#define		sprite_S263Bitmap_s		(sprite_S262width_s*sprite_S262height_s)+sprite_S262Bitmap_s	
//
//#define		sprite_S264width_s		50
//#define		sprite_S264height_s		30
//#define		sprite_S264Bitmap_s		(sprite_S263width_s*sprite_S263height_s)+sprite_S263Bitmap_s	
//
//#define		sprite_S265width_s		50
//#define		sprite_S265height_s		30
//#define		sprite_S265Bitmap_s		(sprite_S264width_s*sprite_S264height_s)+sprite_S264Bitmap_s	
//
//#define		sprite_S266width_s		50
//#define		sprite_S266height_s		30
//#define		sprite_S266Bitmap_s		(sprite_S265width_s*sprite_S265height_s)+sprite_S265Bitmap_s	
//
//#define		sprite_S267width_s		50
//#define		sprite_S267height_s		30
//#define		sprite_S267Bitmap_s		(sprite_S266width_s*sprite_S266height_s)+sprite_S266Bitmap_s	
//
//#define		sprite_S268width_s		50
//#define		sprite_S268height_s		30
//#define		sprite_S268Bitmap_s		(sprite_S267width_s*sprite_S267height_s)+sprite_S267Bitmap_s	
//
//#define		sprite_S269width_s		50
//#define		sprite_S269height_s		30
//#define		sprite_S269Bitmap_s		(sprite_S268width_s*sprite_S268height_s)+sprite_S268Bitmap_s	
//
//#define		sprite_S270width_s		50
//#define		sprite_S270height_s		30
//#define		sprite_S270Bitmap_s		0
//
//#define		sprite_S271width_s		50
//#define		sprite_S271height_s		30
//#define		sprite_S271Bitmap_s		(sprite_S270width_s*sprite_S270height_s)+sprite_S270Bitmap_s	
//
//#define		sprite_S272width_s		50
//#define		sprite_S272height_s		30
//#define		sprite_S272Bitmap_s		(sprite_S271width_s*sprite_S271height_s)+sprite_S271Bitmap_s	
//
//#define		sprite_S273width_s		50
//#define		sprite_S273height_s		30
//#define		sprite_S273Bitmap_s		(sprite_S272width_s*sprite_S272height_s)+sprite_S272Bitmap_s	
//
//#define		sprite_S274width_s		50
//#define		sprite_S274height_s		30
//#define		sprite_S274Bitmap_s		(sprite_S273width_s*sprite_S273height_s)+sprite_S273Bitmap_s	
//
//#define		sprite_S275width_s		50
//#define		sprite_S275height_s		30
//#define		sprite_S275Bitmap_s		(sprite_S274width_s*sprite_S274height_s)+sprite_S274Bitmap_s	
//
//#define		sprite_S276width_s		50
//#define		sprite_S276height_s		30
//#define		sprite_S276Bitmap_s		(sprite_S275width_s*sprite_S275height_s)+sprite_S275Bitmap_s	
//
//#define		sprite_S277width_s		50
//#define		sprite_S277height_s		30
//#define		sprite_S277Bitmap_s		(sprite_S276width_s*sprite_S276height_s)+sprite_S276Bitmap_s	
//
//#define		sprite_S278width_s		50
//#define		sprite_S278height_s		30
//#define		sprite_S278Bitmap_s		0
//
//#define		sprite_S279width_s		50
//#define		sprite_S279height_s		30
//#define		sprite_S279Bitmap_s		(sprite_S278width_s*sprite_S278height_s)+sprite_S278Bitmap_s	
//
//#define		sprite_S280width_s		50
//#define		sprite_S280height_s		30
//#define		sprite_S280Bitmap_s		(sprite_S279width_s*sprite_S279height_s)+sprite_S279Bitmap_s	
//
//#define		sprite_S281width_s		50
//#define		sprite_S281height_s		30
//#define		sprite_S281Bitmap_s		(sprite_S280width_s*sprite_S280height_s)+sprite_S280Bitmap_s	
//
//#define		sprite_S282width_s		50
//#define		sprite_S282height_s		30
//#define		sprite_S282Bitmap_s		(sprite_S281width_s*sprite_S281height_s)+sprite_S281Bitmap_s	
//
//#define		sprite_S283width_s		50
//#define		sprite_S283height_s		30
//#define		sprite_S283Bitmap_s		(sprite_S282width_s*sprite_S282height_s)+sprite_S282Bitmap_s	
//
//#define		sprite_S284width_s		50
//#define		sprite_S284height_s		30
//#define		sprite_S284Bitmap_s		(sprite_S283width_s*sprite_S283height_s)+sprite_S283Bitmap_s	
//
//#define		sprite_S285width_s		50
//#define		sprite_S285height_s		30
//#define		sprite_S285Bitmap_s		(sprite_S284width_s*sprite_S284height_s)+sprite_S284Bitmap_s	
//
//#define		sprite_S286width_s		50
//#define		sprite_S286height_s		30
//#define		sprite_S286Bitmap_s		0
//
//#define		sprite_S287width_s		50
//#define		sprite_S287height_s		30
//#define		sprite_S287Bitmap_s		(sprite_S286width_s*sprite_S286height_s)+sprite_S286Bitmap_s	
//
//#define		sprite_S288width_s		50
//#define		sprite_S288height_s		30
//#define		sprite_S288Bitmap_s		(sprite_S287width_s*sprite_S287height_s)+sprite_S287Bitmap_s	
//
//#define		sprite_S289width_s		50
//#define		sprite_S289height_s		30
//#define		sprite_S289Bitmap_s		(sprite_S288width_s*sprite_S288height_s)+sprite_S288Bitmap_s	
//
//#define		sprite_S290width_s		50
//#define		sprite_S290height_s		30
//#define		sprite_S290Bitmap_s		(sprite_S289width_s*sprite_S289height_s)+sprite_S289Bitmap_s	
//
//#define		sprite_S291width_s		50
//#define		sprite_S291height_s		30
//#define		sprite_S291Bitmap_s		(sprite_S290width_s*sprite_S290height_s)+sprite_S290Bitmap_s	
//
//#define		sprite_S292width_s		50
//#define		sprite_S292height_s		30
//#define		sprite_S292Bitmap_s		(sprite_S291width_s*sprite_S291height_s)+sprite_S291Bitmap_s	
//
//#define		sprite_S293width_s		50
//#define		sprite_S293height_s		30
//#define		sprite_S293Bitmap_s		(sprite_S292width_s*sprite_S292height_s)+sprite_S292Bitmap_s	
//
//#define		sprite_S294width_s		50
//#define		sprite_S294height_s		30
//#define		sprite_S294Bitmap_s		0
//
//#define		sprite_S295width_s		50
//#define		sprite_S295height_s		30
//#define		sprite_S295Bitmap_s		(sprite_S294width_s*sprite_S294height_s)+sprite_S294Bitmap_s	
//
//#define		sprite_S296width_s		50
//#define		sprite_S296height_s		30
//#define		sprite_S296Bitmap_s		(sprite_S295width_s*sprite_S295height_s)+sprite_S295Bitmap_s	
//
//#define		sprite_S297width_s		50
//#define		sprite_S297height_s		30
//#define		sprite_S297Bitmap_s		(sprite_S296width_s*sprite_S296height_s)+sprite_S296Bitmap_s	
//
//#define		sprite_S298width_s		50
//#define		sprite_S298height_s		30
//#define		sprite_S298Bitmap_s		(sprite_S297width_s*sprite_S297height_s)+sprite_S297Bitmap_s	
//
//#define		sprite_S299width_s		50
//#define		sprite_S299height_s		30
//#define		sprite_S299Bitmap_s		(sprite_S298width_s*sprite_S298height_s)+sprite_S298Bitmap_s	
//
//#define		sprite_S300width_s		50
//#define		sprite_S300height_s		30
//#define		sprite_S300Bitmap_s		(sprite_S299width_s*sprite_S299height_s)+sprite_S299Bitmap_s	
//
//#define		sprite_S301width_s		50
//#define		sprite_S301height_s		30
//#define		sprite_S301Bitmap_s		(sprite_S300width_s*sprite_S300height_s)+sprite_S300Bitmap_s	
//
//#define		sprite_S302width_s		50
//#define		sprite_S302height_s		30
//#define		sprite_S302Bitmap_s		0
//
//#define		sprite_S303width_s		50
//#define		sprite_S303height_s		30
//#define		sprite_S303Bitmap_s		(sprite_S302width_s*sprite_S302height_s)+sprite_S302Bitmap_s	
//
//#define		sprite_S304width_s		50
//#define		sprite_S304height_s		30
//#define		sprite_S304Bitmap_s		(sprite_S303width_s*sprite_S303height_s)+sprite_S303Bitmap_s	
//
//#define		sprite_S305width_s		50
//#define		sprite_S305height_s		30
//#define		sprite_S305Bitmap_s		(sprite_S304width_s*sprite_S304height_s)+sprite_S304Bitmap_s	
//												 
//#define		sprite_S306width_s		50
//#define		sprite_S306height_s		30
//#define		sprite_S306Bitmap_s		(sprite_S305width_s*sprite_S305height_s)+sprite_S305Bitmap_s	
//
//#define		sprite_S307width_s		50
//#define		sprite_S307height_s		30
//#define		sprite_S307Bitmap_s		(sprite_S306width_s*sprite_S306height_s)+sprite_S306Bitmap_s	
//
//#define		sprite_S308width_s		50
//#define		sprite_S308height_s		30
//#define		sprite_S308Bitmap_s		(sprite_S307width_s*sprite_S307height_s)+sprite_S307Bitmap_s	
//
//#define		sprite_S309width_s		50
//#define		sprite_S309height_s		30
//#define		sprite_S309Bitmap_s		(sprite_S308width_s*sprite_S308height_s)+sprite_S308Bitmap_s	
//
//
//#define		sprite_S310width_s		50
//#define		sprite_S310height_s		30
//#define		sprite_S310Bitmap_s		0
//
//#define		sprite_S311width_s		50
//#define		sprite_S311height_s		30
//#define		sprite_S311Bitmap_s		(sprite_S310width_s*sprite_S310height_s)+sprite_S310Bitmap_s	
//
//#define		sprite_S312width_s		50
//#define		sprite_S312height_s		30
//#define		sprite_S312Bitmap_s		(sprite_S311width_s*sprite_S311height_s)+sprite_S311Bitmap_s	
//
//#define		sprite_S313width_s		50
//#define		sprite_S313height_s		30
//#define		sprite_S313Bitmap_s		(sprite_S312width_s*sprite_S312height_s)+sprite_S312Bitmap_s	
//
//#define		sprite_S314width_s		50
//#define		sprite_S314height_s		30
//#define		sprite_S314Bitmap_s		(sprite_S313width_s*sprite_S313height_s)+sprite_S313Bitmap_s	
//
//#define		sprite_S315width_s		50
//#define		sprite_S315height_s		30
//#define		sprite_S315Bitmap_s		(sprite_S314width_s*sprite_S314height_s)+sprite_S314Bitmap_s	
//
//#define		sprite_S316width_s		50
//#define		sprite_S316height_s		30
//#define		sprite_S316Bitmap_s		(sprite_S315width_s*sprite_S315height_s)+sprite_S315Bitmap_s	
//
//#define		sprite_S317width_s		50
//#define		sprite_S317height_s		30
//#define		sprite_S317Bitmap_s		(sprite_S316width_s*sprite_S316height_s)+sprite_S316Bitmap_s	
//
//#define		sprite_S318width_s		50
//#define		sprite_S318height_s		30
//#define		sprite_S318Bitmap_s		0
//
//#define		sprite_S319width_s		50
//#define		sprite_S319height_s		30
//#define		sprite_S319Bitmap_s		(sprite_S318width_s*sprite_S318height_s)+sprite_S318Bitmap_s	
//
//#define		sprite_S320width_s		50
//#define		sprite_S320height_s		30
//#define		sprite_S320Bitmap_s		(sprite_S319width_s*sprite_S319height_s)+sprite_S319Bitmap_s	
//
//#define		sprite_S321width_s		50
//#define		sprite_S321height_s		30
//#define		sprite_S321Bitmap_s		(sprite_S320width_s*sprite_S320height_s)+sprite_S320Bitmap_s	
//
//#define		sprite_S322width_s		50
//#define		sprite_S322height_s		30
//#define		sprite_S322Bitmap_s		(sprite_S321width_s*sprite_S321height_s)+sprite_S321Bitmap_s	
//
//#define		sprite_S323width_s		50
//#define		sprite_S323height_s		30
//#define		sprite_S323Bitmap_s		(sprite_S322width_s*sprite_S322height_s)+sprite_S322Bitmap_s	
//
//#define		sprite_S324width_s		50
//#define		sprite_S324height_s		30
//#define		sprite_S324Bitmap_s		(sprite_S323width_s*sprite_S323height_s)+sprite_S323Bitmap_s	
//
//#define		sprite_S325width_s		50
//#define		sprite_S325height_s		30
//#define		sprite_S325Bitmap_s		(sprite_S324width_s*sprite_S324height_s)+sprite_S324Bitmap_s	
//
//#define		sprite_S326width_s		50
//#define		sprite_S326height_s		30
//#define		sprite_S326Bitmap_s		0
//
//#define		sprite_S327width_s		50
//#define		sprite_S327height_s		30
//#define		sprite_S327Bitmap_s		(sprite_S326width_s*sprite_S326height_s)+sprite_S326Bitmap_s	
//
//#define		sprite_S328width_s		50
//#define		sprite_S328height_s		30
//#define		sprite_S328Bitmap_s		(sprite_S327width_s*sprite_S327height_s)+sprite_S327Bitmap_s	
//
//#define		sprite_S329width_s		50
//#define		sprite_S329height_s		30
//#define		sprite_S329Bitmap_s		(sprite_S328width_s*sprite_S328height_s)+sprite_S328Bitmap_s	
//
//#define		sprite_S330width_s		50
//#define		sprite_S330height_s		30
//#define		sprite_S330Bitmap_s		(sprite_S329width_s*sprite_S329height_s)+sprite_S329Bitmap_s	
//
//#define		sprite_S331width_s		50
//#define		sprite_S331height_s		30
//#define		sprite_S331Bitmap_s		(sprite_S330width_s*sprite_S330height_s)+sprite_S330Bitmap_s	
//
//#define		sprite_S332width_s		50
//#define		sprite_S332height_s		30
//#define		sprite_S332Bitmap_s		(sprite_S331width_s*sprite_S331height_s)+sprite_S331Bitmap_s	
//
//#define		sprite_S333width_s		50
//#define		sprite_S333height_s		30
//#define		sprite_S333Bitmap_s		(sprite_S332width_s*sprite_S332height_s)+sprite_S332Bitmap_s	
//
//
//
//#define		sprite_S334width_s		50
//#define		sprite_S334height_s		30
//#define		sprite_S334Bitmap_s		0
//
//#define		sprite_S335width_s		50
//#define		sprite_S335height_s		30
//#define		sprite_S335Bitmap_s		(sprite_S334width_s*sprite_S334height_s)+sprite_S334Bitmap_s	
//
//#define		sprite_S336width_s		50
//#define		sprite_S336height_s		30
//#define		sprite_S336Bitmap_s		(sprite_S335width_s*sprite_S335height_s)+sprite_S335Bitmap_s	
//
//#define		sprite_S337width_s		50
//#define		sprite_S337height_s		30
//#define		sprite_S337Bitmap_s		(sprite_S336width_s*sprite_S336height_s)+sprite_S336Bitmap_s	
//
//#define		sprite_S338width_s		50
//#define		sprite_S338height_s		30
//#define		sprite_S338Bitmap_s		(sprite_S337width_s*sprite_S337height_s)+sprite_S337Bitmap_s	
//
//#define		sprite_S339width_s		50
//#define		sprite_S339height_s		30
//#define		sprite_S339Bitmap_s		(sprite_S338width_s*sprite_S338height_s)+sprite_S338Bitmap_s	
//
//#define		sprite_S340width_s		50
//#define		sprite_S340height_s		30
//#define		sprite_S340Bitmap_s		(sprite_S339width_s*sprite_S339height_s)+sprite_S339Bitmap_s	
//
//#define		sprite_S341width_s		50
//#define		sprite_S341height_s		30
//#define		sprite_S341Bitmap_s		(sprite_S340width_s*sprite_S340height_s)+sprite_S340Bitmap_s	
//
//#define		sprite_S342width_s		50
//#define		sprite_S342height_s		30
//#define		sprite_S342Bitmap_s		0
//
//#define		sprite_S343width_s		50
//#define		sprite_S343height_s		30
//#define		sprite_S343Bitmap_s		(sprite_S342width_s*sprite_S342height_s)+sprite_S342Bitmap_s	
//
//#define		sprite_S344width_s		50
//#define		sprite_S344height_s		30
//#define		sprite_S344Bitmap_s		(sprite_S343width_s*sprite_S343height_s)+sprite_S343Bitmap_s	
//
//#define		sprite_S345width_s		50
//#define		sprite_S345height_s		30
//#define		sprite_S345Bitmap_s		(sprite_S344width_s*sprite_S344height_s)+sprite_S344Bitmap_s	
//
//#define		sprite_S346width_s		50
//#define		sprite_S346height_s		30
//#define		sprite_S346Bitmap_s		(sprite_S345width_s*sprite_S345height_s)+sprite_S345Bitmap_s	
//
//#define		sprite_S347width_s		50
//#define		sprite_S347height_s		30
//#define		sprite_S347Bitmap_s		(sprite_S346width_s*sprite_S346height_s)+sprite_S346Bitmap_s	
//
//#define		sprite_S348width_s		50
//#define		sprite_S348height_s		30
//#define		sprite_S348Bitmap_s		(sprite_S347width_s*sprite_S347height_s)+sprite_S347Bitmap_s	
//
//#define		sprite_S349width_s		50
//#define		sprite_S349height_s		30
//#define		sprite_S349Bitmap_s		(sprite_S348width_s*sprite_S348height_s)+sprite_S348Bitmap_s	
//
//#define		sprite_S350width_s		50
//#define		sprite_S350height_s		30
//#define		sprite_S350Bitmap_s		0
//
//#define		sprite_S351width_s		50
//#define		sprite_S351height_s		30
//#define		sprite_S351Bitmap_s		(sprite_S350width_s*sprite_S350height_s)+sprite_S350Bitmap_s	
//
//#define		sprite_S352width_s		50
//#define		sprite_S352height_s		30
//#define		sprite_S352Bitmap_s		(sprite_S351width_s*sprite_S351height_s)+sprite_S351Bitmap_s	
//
//#define		sprite_S353width_s		50
//#define		sprite_S353height_s		30
//#define		sprite_S353Bitmap_s		(sprite_S352width_s*sprite_S352height_s)+sprite_S352Bitmap_s	
//
//#define		sprite_S354width_s		50
//#define		sprite_S354height_s		30
//#define		sprite_S354Bitmap_s		(sprite_S353width_s*sprite_S353height_s)+sprite_S353Bitmap_s	
//
//#define		sprite_S355width_s		50
//#define		sprite_S355height_s		30
//#define		sprite_S355Bitmap_s		(sprite_S354width_s*sprite_S354height_s)+sprite_S354Bitmap_s	
//
//#define		sprite_S356width_s		50
//#define		sprite_S356height_s		30
//#define		sprite_S356Bitmap_s		(sprite_S355width_s*sprite_S355height_s)+sprite_S355Bitmap_s	
//
//#define		sprite_S357width_s		50
//#define		sprite_S357height_s		30
//#define		sprite_S357Bitmap_s		(sprite_S356width_s*sprite_S356height_s)+sprite_S356Bitmap_s	
//
//#define		sprite_S358width_s		50
//#define		sprite_S358height_s		30
//#define		sprite_S358Bitmap_s		0
//
//#define		sprite_S359width_s		50
//#define		sprite_S359height_s		30
//#define		sprite_S359Bitmap_s		(sprite_S358width_s*sprite_S358height_s)+sprite_S358Bitmap_s	
//
//#define		sprite_S360width_s		50
//#define		sprite_S360height_s		30
//#define		sprite_S360Bitmap_s		(sprite_S359width_s*sprite_S359height_s)+sprite_S359Bitmap_s	
//
//#define		sprite_S361width_s		50
//#define		sprite_S361height_s		30
//#define		sprite_S361Bitmap_s		(sprite_S360width_s*sprite_S360height_s)+sprite_S360Bitmap_s	
//
//#define		sprite_S362width_s		50
//#define		sprite_S362height_s		30
//#define		sprite_S362Bitmap_s		(sprite_S361width_s*sprite_S361height_s)+sprite_S361Bitmap_s	
//
//#define		sprite_S363width_s		50
//#define		sprite_S363height_s		30
//#define		sprite_S363Bitmap_s		(sprite_S362width_s*sprite_S362height_s)+sprite_S362Bitmap_s	
//
//#define		sprite_S364width_s		50
//#define		sprite_S364height_s		30
//#define		sprite_S364Bitmap_s		(sprite_S363width_s*sprite_S363height_s)+sprite_S363Bitmap_s	
//
//#define		sprite_S365width_s		50
//#define		sprite_S365height_s		30
//#define		sprite_S365Bitmap_s		(sprite_S364width_s*sprite_S364height_s)+sprite_S364Bitmap_s	
//
//#define		sprite_S366width_s		50
//#define		sprite_S366height_s		30
//#define		sprite_S366Bitmap_s		0
//
//#define		sprite_S367width_s		50
//#define		sprite_S367height_s		30
//#define		sprite_S367Bitmap_s		(sprite_S366width_s*sprite_S366height_s)+sprite_S366Bitmap_s	
//
//#define		sprite_S368width_s		50
//#define		sprite_S368height_s		30
//#define		sprite_S368Bitmap_s		(sprite_S367width_s*sprite_S367height_s)+sprite_S367Bitmap_s	
//
//#define		sprite_S369width_s		50
//#define		sprite_S369height_s		30
//#define		sprite_S369Bitmap_s		(sprite_S368width_s*sprite_S368height_s)+sprite_S368Bitmap_s	
//
//#define		sprite_S370width_s		50
//#define		sprite_S370height_s		30
//#define		sprite_S370Bitmap_s		(sprite_S369width_s*sprite_S369height_s)+sprite_S369Bitmap_s	
//
//#define		sprite_S371width_s		50
//#define		sprite_S371height_s		30
//#define		sprite_S371Bitmap_s		(sprite_S370width_s*sprite_S370height_s)+sprite_S370Bitmap_s	
//
//#define		sprite_S372width_s		50
//#define		sprite_S372height_s		30
//#define		sprite_S372Bitmap_s		(sprite_S371width_s*sprite_S371height_s)+sprite_S371Bitmap_s	
//
//#define		sprite_S373width_s		50
//#define		sprite_S373height_s		30
//#define		sprite_S373Bitmap_s		(sprite_S372width_s*sprite_S372height_s)+sprite_S372Bitmap_s	
//
//#define		sprite_S374width_s		50
//#define		sprite_S374height_s		30
//#define		sprite_S374Bitmap_s		0
//
//#define		sprite_S375width_s		50
//#define		sprite_S375height_s		30
//#define		sprite_S375Bitmap_s		(sprite_S374width_s*sprite_S374height_s)+sprite_S374Bitmap_s	
//
//#define		sprite_S376width_s		50
//#define		sprite_S376height_s		30
//#define		sprite_S376Bitmap_s		(sprite_S375width_s*sprite_S375height_s)+sprite_S375Bitmap_s	
//
//#define		sprite_S377width_s		50
//#define		sprite_S377height_s		30
//#define		sprite_S377Bitmap_s		(sprite_S376width_s*sprite_S376height_s)+sprite_S376Bitmap_s	
//
//#define		sprite_S378width_s		50
//#define		sprite_S378height_s		30
//#define		sprite_S378Bitmap_s		(sprite_S377width_s*sprite_S377height_s)+sprite_S377Bitmap_s	
//
//#define		sprite_S379width_s		50
//#define		sprite_S379height_s		30
//#define		sprite_S379Bitmap_s		(sprite_S378width_s*sprite_S378height_s)+sprite_S378Bitmap_s	
//
//#define		sprite_S380width_s		50
//#define		sprite_S380height_s		30
//#define		sprite_S380Bitmap_s		(sprite_S379width_s*sprite_S379height_s)+sprite_S379Bitmap_s	
//
//#define		sprite_S381width_s		50
//#define		sprite_S381height_s		30
//#define		sprite_S381Bitmap_s		(sprite_S380width_s*sprite_S380height_s)+sprite_S380Bitmap_s	
//
//#define		sprite_S382width_s		50
//#define		sprite_S382height_s		30
//#define		sprite_S382Bitmap_s		0
//
//#define		sprite_S383width_s		50
//#define		sprite_S383height_s		30
//#define		sprite_S383Bitmap_s		(sprite_S382width_s*sprite_S382height_s)+sprite_S382Bitmap_s	
//
//#define		sprite_S384width_s		50
//#define		sprite_S384height_s		30
//#define		sprite_S384Bitmap_s		(sprite_S383width_s*sprite_S383height_s)+sprite_S383Bitmap_s	
//
//#define		sprite_S385width_s		50
//#define		sprite_S385height_s		30
//#define		sprite_S385Bitmap_s		(sprite_S384width_s*sprite_S384height_s)+sprite_S384Bitmap_s	
//
//#define		sprite_S386width_s		50
//#define		sprite_S386height_s		30
//#define		sprite_S386Bitmap_s		(sprite_S385width_s*sprite_S385height_s)+sprite_S385Bitmap_s	
//
//#define		sprite_S387width_s		50
//#define		sprite_S387height_s		30
//#define		sprite_S387Bitmap_s		(sprite_S386width_s*sprite_S386height_s)+sprite_S386Bitmap_s	
//
//#define		sprite_S388width_s		50
//#define		sprite_S388height_s		30
//#define		sprite_S388Bitmap_s		(sprite_S387width_s*sprite_S387height_s)+sprite_S387Bitmap_s	
//
//#define		sprite_S389width_s		50
//#define		sprite_S389height_s		30
//#define		sprite_S389Bitmap_s		(sprite_S388width_s*sprite_S388height_s)+sprite_S388Bitmap_s	
//
//#define		sprite_S390width_s		50
//#define		sprite_S390height_s		30
//#define		sprite_S390Bitmap_s		0
//
//#define		sprite_S391width_s		50
//#define		sprite_S391height_s		30
//#define		sprite_S391Bitmap_s		(sprite_S390width_s*sprite_S390height_s)+sprite_S390Bitmap_s	
//
//#define		sprite_S392width_s		50
//#define		sprite_S392height_s		30
//#define		sprite_S392Bitmap_s		(sprite_S391width_s*sprite_S391height_s)+sprite_S391Bitmap_s	
//
//#define		sprite_S393width_s		50
//#define		sprite_S393height_s		30
//#define		sprite_S393Bitmap_s		(sprite_S392width_s*sprite_S392height_s)+sprite_S392Bitmap_s	
//
//#define		sprite_S394width_s		50
//#define		sprite_S394height_s		30
//#define		sprite_S394Bitmap_s		(sprite_S393width_s*sprite_S393height_s)+sprite_S393Bitmap_s	
//
//#define		sprite_S395width_s		50
//#define		sprite_S395height_s		30
//#define		sprite_S395Bitmap_s		(sprite_S394width_s*sprite_S394height_s)+sprite_S394Bitmap_s	
//
//#define		sprite_S396width_s		50
//#define		sprite_S396height_s		30
//#define		sprite_S396Bitmap_s		(sprite_S395width_s*sprite_S395height_s)+sprite_S395Bitmap_s	
//
//#define		sprite_S397width_s		50
//#define		sprite_S397height_s		30
//#define		sprite_S397Bitmap_s		(sprite_S396width_s*sprite_S396height_s)+sprite_S396Bitmap_s	
//
//#define		sprite_S398width_s		50
//#define		sprite_S398height_s		30
//#define		sprite_S398Bitmap_s		0
//
//#define		sprite_S399width_s		50
//#define		sprite_S399height_s		30
//#define		sprite_S399Bitmap_s		(sprite_S398width_s*sprite_S398height_s)+sprite_S398Bitmap_s	
//
//#define		sprite_S400width_s		50
//#define		sprite_S400height_s		30
//#define		sprite_S400Bitmap_s		(sprite_S399width_s*sprite_S399height_s)+sprite_S399Bitmap_s	
//
//#define		sprite_S401width_s		50
//#define		sprite_S401height_s		30
//#define		sprite_S401Bitmap_s		(sprite_S400width_s*sprite_S400height_s)+sprite_S400Bitmap_s	
//
//#define		sprite_S402width_s		50
//#define		sprite_S402height_s		30
//#define		sprite_S402Bitmap_s		(sprite_S401width_s*sprite_S401height_s)+sprite_S401Bitmap_s	
//
//#define		sprite_S403width_s		50
//#define		sprite_S403height_s		30
//#define		sprite_S403Bitmap_s		(sprite_S402width_s*sprite_S402height_s)+sprite_S402Bitmap_s	
//
//#define		sprite_S404width_s		50
//#define		sprite_S404height_s		30
//#define		sprite_S404Bitmap_s		(sprite_S403width_s*sprite_S403height_s)+sprite_S403Bitmap_s	
//
//#define		sprite_S405width_s		50
//#define		sprite_S405height_s		30
//#define		sprite_S405Bitmap_s		(sprite_S404width_s*sprite_S404height_s)+sprite_S404Bitmap_s	
//
//#define		sprite_S406width_s		50
//#define		sprite_S406height_s		30
//#define		sprite_S406Bitmap_s		0
//
//#define		sprite_S407width_s		50
//#define		sprite_S407height_s		30
//#define		sprite_S407Bitmap_s		(sprite_S406width_s*sprite_S406height_s)+sprite_S406Bitmap_s	
//
//#define		sprite_S408width_s		50
//#define		sprite_S408height_s		30
//#define		sprite_S408Bitmap_s		(sprite_S407width_s*sprite_S407height_s)+sprite_S407Bitmap_s	
//
//#define		sprite_S409width_s		50
//#define		sprite_S409height_s		30
//#define		sprite_S409Bitmap_s		(sprite_S408width_s*sprite_S408height_s)+sprite_S408Bitmap_s	
//
//#define		sprite_S410width_s		50
//#define		sprite_S410height_s		30
//#define		sprite_S410Bitmap_s		(sprite_S409width_s*sprite_S409height_s)+sprite_S409Bitmap_s	
//
//#define		sprite_S411width_s		50
//#define		sprite_S411height_s		30
//#define		sprite_S411Bitmap_s		(sprite_S410width_s*sprite_S410height_s)+sprite_S410Bitmap_s	
//
//#define		sprite_S412width_s		50
//#define		sprite_S412height_s		30
//#define		sprite_S412Bitmap_s		(sprite_S411width_s*sprite_S411height_s)+sprite_S411Bitmap_s	
//
//#define		sprite_S413width_s		50
//#define		sprite_S413height_s		30
//#define		sprite_S413Bitmap_s		(sprite_S412width_s*sprite_S412height_s)+sprite_S412Bitmap_s	
//
//#define		sprite_S414width_s		50
//#define		sprite_S414height_s		30
//#define		sprite_S414Bitmap_s		0	
//
//#define		sprite_S415width_s		50
//#define		sprite_S415height_s		30
//#define		sprite_S415Bitmap_s		(sprite_S414width_s*sprite_S414height_s)+sprite_S414Bitmap_s	
//
//#define		sprite_S416width_s		50
//#define		sprite_S416height_s		30
//#define		sprite_S416Bitmap_s		(sprite_S415width_s*sprite_S415height_s)+sprite_S415Bitmap_s	
//
//#define		sprite_S417width_s		50
//#define		sprite_S417height_s		30
//#define		sprite_S417Bitmap_s		(sprite_S416width_s*sprite_S416height_s)+sprite_S416Bitmap_s	
//
//#define		sprite_S418width_s		50
//#define		sprite_S418height_s		30
//#define		sprite_S418Bitmap_s		(sprite_S417width_s*sprite_S417height_s)+sprite_S417Bitmap_s	
//
//#define		sprite_S419width_s		50
//#define		sprite_S419height_s		30
//#define		sprite_S419Bitmap_s		(sprite_S418width_s*sprite_S418height_s)+sprite_S418Bitmap_s	
//
//#define		sprite_S420width_s		50
//#define		sprite_S420height_s		30
//#define		sprite_S420Bitmap_s		(sprite_S419width_s*sprite_S419height_s)+sprite_S419Bitmap_s	
//
//#define		sprite_S421width_s		50
//#define		sprite_S421height_s		30
//#define		sprite_S421Bitmap_s		(sprite_S420width_s*sprite_S420height_s)+sprite_S420Bitmap_s	
//
//#define		sprite_999width_s			96
//#define		sprite_999height_s		54
//#define		sprite_999Bitmap_s		0
//

struct choose_setup
{
	int			str_flags;
	int			spr_flags;
	short			type;
	short			xposn;
	short			yposn;
	short			spr_xposn;
	short			spr_yposn;
	short 		BoundingBoxLeft;
	short 		BoundingBoxTop;
	short 		BoundingBoxRight;
	short 		BoundingBoxBottom;
	short			CopyAreaX;
	short			CopyAreaY;
	short			CopyWidth;
	short			CopyHeight;
};

struct choose_offsets
{
	short			x_off;
	short			y_off;
};
struct choose_info
{
	choose_offsets	offsets[3];
	choose_setup	choose[44];
};


//				DATA STRUCTURES TO BE SAVED


typedef struct {
					int	cheat_mode;
					int	Port_toggle;
					int	Ranking_Division;
					int 	PointsForWin;
					int	match_number;
					int	round_up_page;
					char	roundup_games;
					char	league_rndup;
					int	cup_tie; 
					int	Round_index;
					int	Round_counter;
					int	RoundPrint;
					int	cup_match_number;
					char	GDVres;
 					char	winners;
					char	runners_up;
					short	cup_team_a;
					short	cup_team_b;
					int	OldCTRL1, OldCTRL2;
					int	number_of_cup_teams;
					int	gdv_gran;
 					char	which_gdv;
 
					int	keys_used[12];

					char	DEMOflag;
					int	PlayerCount;
					char	floppy;
					char	rolling_demo;

            	}batch_data;				


typedef struct {

	short			sky_toggle;
	short			stadium_toggle;
	short			line_toggle;
	short			vidi_toggle;
	short			players_toggle;
	short			pitch_toggle;
	short			res_toggle;
	short			camera_toggle;
	short			size_toggle;
	short			audio_toggle;

	short			menu_res;
	short			camera;
	short			audio;
	int			crowd;
	int			pitch;
	int			commentary;
	int			music;
	int			master;

	short			timeit;											 	
	short			vidi;

	char			match_number;	 		// match/league week number.	  -1 = needs initialising.
	int			team_a_score;			// score for team_a
	int			team_b_score;			// score for team_b

	int			penalties;
	int 			extra;

	int			team_a_penalties;
	int			team_b_penalties;
	int			venue;
	char			tac_1;
	char			tac_2;

	short			offside;
	short			substitutes;
	short			freekicks;
	short			time;
	short			bookings;
	short			wind;

	short			offside_toggle;
	short			substitutes_toggle;
	short			freekicks_toggle;
	short			time_toggle;
	short			bookings_toggle;
	short			wind_toggle;

	int			CompetitionType;
	int			CompetitionType_toggle;
	int			NoOfPlayers;
	int			NoOfPlayers_toggle;
	int			GameType;
	int			GameType_toggle;

	int			CROWD;
	int			COMMENTRY;
	int			MASTER;
	int			PITCH;
	int			MUSIC;

	int			referee;
	int			match_referee;
	int			referee_vision;
	int			referee_discipline;

	char			control_methods[4];
	char			tga_enable;
	
	int			return_mins;
	int			rand;	
  	char			language;
											
            	}match_data;				








struct fixture_info1	{
					int	home_team;
					int	away_team;
					int	league_table;
	     					};

typedef struct {
					fixture_info1		fixture_data;	
					}fixture_table;



struct result_info	{
//					int	team_a_score;
//					int	team_b_score;
//					int	team_a;
//					int	team_b;
//					int	penalties;
//					int 	extra;
//					int	team_a_penalties;
//					int	team_b_penalties;

					char	team_a_score;
					char	team_b_score;
					char	team_a;
					char	team_b;
					char	penalties;
					char	extra;
					char	team_a_penalties;
					char	team_b_penalties;
	     					};

typedef struct {
					result_info		result_data;	
					}result_table;







struct goal_info	{
					char	used;
					int	scorer;
					int	time;
	     			  	};

typedef struct		{

					goal_info		goal_data;	

						}goal_table;




typedef struct {
					int control_p1;
					int control_p2;
					int control_p3;
					int control_p4;
					}a_control_table;

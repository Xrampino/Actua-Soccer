extern	char				*EuroDATfile;
extern	char				*EuroOFFSETfile;
extern	char				*EuroSCRIPTfile;

extern	char				version;
extern	char				sub_version;
extern	char				day;
extern	char				month;
extern	short				year; 
extern	char				EUROsymbol;
extern	int				EUROerror;
extern	char				EUROverbose;
extern	char				EUROfrontend;
extern	char				EUROconsole;

extern	char				*EuroGDVfile;
extern	volatile	char	LogicState;
extern	unsigned int 	EuroHandle;
extern	BYTE				*EuroPseudoBuffer;
extern	BYTE				*EuroBackgroundBuffer;
extern	char				TexturePagesAvailable;
extern	BYTE				*TexturePages;
extern	BYTE				*TexturePageMemHandle;
extern	BYTE				*TextStrings;
extern	BYTE				*TextStringMemHandle;
extern	int				Image_Xcoords[];
extern	int				Image_Ycoords[];
extern	int				Image_Widths[];
extern	int		  		Image_Heights[];
extern	char				Image_Pages[];
extern	BYTE				*Text[];
extern	BYTE				*Clubnames[];
extern	BYTE				*SPEECH_identifier[];
extern	char				PlayerPosns[];
extern	char				StarPlayers[];
extern 	char				LinkPlayers[];
extern	char				DOBday[];
extern	char				DOBmonth[];
extern	char				DOByear[];
extern	char				NamePREFIXtbl[16*20];

extern	offset_defn		Offset_table[];
extern	texture_info 	FrontendTextureDEFN;
extern	pseudo_info 	FrontendPseudoDEFN;
extern	pseudo_info 	FrontendBackgroundDEFN;
extern	slider_info		ModemSelectDEFN;
extern	char 				StringBuffer[];
extern	char				Templete[];
extern	char 				BuildBuffer[];
extern	char				EUROammount[];

extern	char				KeyInput[];
extern	char				TextEditBuffer[];
extern	short				TextEditXposn;
extern	char				EuroTextEditState;

extern	BYTE  			PaletteBuffer[];
extern   BYTE 				FilterBuffer[];
extern	BYTE 				SparePaletteBuffer[];
extern	fixed				DivisionTable[];
extern	fixed				CurrentPalette[];
extern	fixed				FadeCounter;

extern	char		 		svalue;
extern	unsigned char  pmin, pmax;
extern	BYTE				*ftable;
extern	signed char		box;

extern	char				Team;
extern	char				Menu;
extern	signed char		MarkPlayer;
extern	signed char		ViewPlyrStats;
extern	signed short	SquadBuffer1yposn;
extern	float				EuroReDrawCounter;
extern	signed char 	EuroReDrawFlag;

extern	int				TeamTactics[(32*2)+6][10][2];
extern	signed char  	Bounding_box;
extern	signed char		ClickBOX;
extern	animation_info	Animation_table[];

extern	float				SelectionCounter;
extern	float				SelectionSpeed;
extern	signed char		SelectionFlag;
extern	signed int 		SelectionAim;
extern	signed char		SelectDir;
extern	fixed				SelectFrame;
extern	fixed				CursorDisplaySpeed;

extern	char				EuroVideoStatus;
extern	int				EUROvideoMode[];

extern	short				SelectFilterTBL[];
extern	short				QuestionHandle;
extern	short				EuroDrawHandle;
extern	short				RedrawHandle;
extern	short				GrpFixHandle;
extern	short				FormationHandle;
extern	short				TeamHandle;
extern	short				PlayerSetupHandle;
extern	short				TeamSelectHandle;
extern	short				TeamSetupHandle;
extern	short				ReturnSqdHandle;
extern	short				ReturnStatHandle;
extern	short				ViewTeamHandle;
extern	short				ReturnTeamHandle;
extern	short				NetSelectionHandle;
extern	short				NetStartHandle;
extern	short				StartMatchHandle;
extern	short				UserSelectTeamHandle;
extern	short				StartEuro96Handle;
extern	short				NoOfUsersHandle;
extern	short				DefaultHandle;
extern	short				NextMatchHandle;
extern	short				SpinningCupHandle;
extern	short				SelectTeamsHandle;

extern	char				UserHighlight;
extern	char				SelectHighlight;
extern	char				RedrawHighlight;
extern	char				RedrawdoneHighlight;
extern	char				DefaultdrawHighlight;
extern	char				TeamSelectHighlight;
extern	char				StartMatchHighlight;
extern	char				TeamSetupHighlight;
extern	char				PlyrSetupHighlight;
extern	char				RetnTstatHighlight;
extern	char				NextMatchHighlight;
extern	char				SelectTeamsHighlight;
extern	char				NetStartHighlight;

extern	char				OVERRIDEpal1;
extern	char				OVERRIDEpal2;

extern	short				VersusLength;
extern	Coord_info		LeaguePosnDEFN[];
extern	Coord_info		WinPosnDEFN[];
extern  	Coord_info		DrawPosnDEFN[];
extern	Coord_info		LosePosnDEFN[];
extern  	Coord_info		PointsPosnDEFN[];
extern  	Coord_info		VersusPosnDEFN[];
extern	Coord_info		ReDrawPosnDEFN[];
extern	Coord_info		ReDrawHeadPosnDEFN[];
extern	Coord_info		QualifierHeadPosnDEFN[];
extern	Coord_info		CountryOutlinePosnDEFN[];
extern	Coord_info		TSTATCountryPosnDEFN[];
extern	TeamSel_Info 	CountryImageDEFN[];
extern	header_info 	GroupFixtureDEFN[];
extern	dump_info		Dump_list[];

extern	char				LeaguePositions[];
extern	qualify_info  	qualifiers[];
extern	fixture_info	Fixtures[];
extern	char				MatchVenues[];
extern	char				CountryTBL[];
extern	char				AimTBL[];
extern	char				CtrlFlags[];
extern	char				PlrSetupPanelHght[];
extern	char				PreviousEuroYearsTBL[];
extern	char				PreviousEuroHistory[];
extern	int				MouseDriverInstalled;
extern	char				EUROmaxPlayers;
extern	char				EUROplyrSetup;
extern	char				EUROteamView;
extern	char				EUROstatTeam;
extern	char				EUROuserSelection;					// player to choose his team 0 - 15
extern	euro_info		EURO96setup[];							// one entry per country.
extern	char				GroupDrawCode[];
extern	signed char		GroupVenues[];
extern	int				NextXposn;
extern	char				RunMatch;	
extern	char				EUROmatchUsers;

	// ---> Frontend Vars to be linked with main game <---

extern	unsigned char	EUROcamera;
extern	short				EUROaudio;
extern	int				EUROcrowd;
extern	int				EUROpitch;
extern	int				EUROcommentary;
extern	int				EUROmusic;
extern	int				EUROmaster;
extern	short				EUROtimeit;
extern	short				EUROvidi;
extern	char				EUROoffside;
extern	char				EUROsubs;
extern	char				EUROfouls;
extern	char				EUROtime;
extern	char				EURObookings;
extern	char				EUROwind;
extern	char				EUROref_vision;
extern	char				EUROref_discipline;
extern	char				EUROtga;
extern	short				EUROscrSize;
extern	short				EUROvenue;	
extern	short				EUROsky;
extern	short				EUROstadia;
extern	short				EUROlineDetail;
extern	short				EUROvidiType;
extern	short				EUROplyrDetail;
extern	short				EUROptchDetail;
extern	short				EUROresoln;
extern	char				EUROcontrol_methods[];

	// ---> Frontend Random number variables <---

// Randomize variables...

extern  	long	 			EUROseed1;
extern	unsigned short EUROseed3;

	// ---> Selector Variables <---

extern	short				ButtonState;
extern	short				SelectorXcoord;
extern	short				SelectorYcoord;
extern	short				DeBounce;

	// ---> Network / Serial / Wireplay / Modem specific variables <---

extern	char				EUROcommTYPE;			// 0 network 1 serial 2 modem 3 wireplay
extern	char				EUROcommOVERIDE;
extern	char				EURO_Did_I_ChooseTeams;
extern	"C"	char 		EUROnetInitialise;
extern	char				EURO_NetSelectionMade;
extern	char				UserNetList[];
extern	char				TeamA_AUTOplayers;
extern	char				TeamB_AUTOplayers;
extern	char				EUROoveride;
extern	char				ModemInitList[];
extern	BYTE				*Modems[];
extern	BYTE				*ModemInitStrs[];
extern	int				EuroNETseed;
extern	short				ModemXposn;
extern	char				ModemYpage;
extern	signed short 	EUROmodemType;
extern	char				EUROmodemDialType;
extern	char				EUROmodemCommType;
extern	char				DialNumber[];
extern	char				InitStr[];
extern	short				DialX;
extern	short				InitX;

	// ---> Windows '95 variables <---

extern	int				w95;

//******************************************************************

extern	char				SquadInfo[];
extern	signed char		FormationInfo[];
extern	signed char		GroupDrawInfo[];
extern	signed char		GroupDrawDefaultInfo[];
extern	League_info		LeagueTable[16];
extern	short				PlayersCaps[16*20];
extern	short				PlayersGoals[16*20];

extern	char				Pace[];
extern	char				Power[];
extern	char				Control[];
extern	char				Flair[];
extern	char				Vision[];
extern	char				Accuracy[];
extern	char				Stamina[];
extern	char				Discipline[];
extern	char				Fitness[];
extern	char				FitnessDefault[];
extern	char				DiscPts[];

extern	user_info		UserList[];
extern	signed char 	UserSetupList[];

extern	char				NoOfSubs, UsableSubs;
extern	char				WinPts;
extern	char				DrawPts;
extern	char				MatchNumber;	

extern	char				EUROday;
extern	char				EUROmonth;
extern	char				EUROyear;
extern	char				EUROgameType;

extern	char				EUROnoOfMatchPlyrs;

extern	char				EUROteamA, EUROteamB, EUROchampTeam;
extern	history_info	PastScores[];
extern	results_info	Results[];

//******************************************************************

extern	char				Finish;
extern	signed char		ChangeMenu;

extern	box_info			Bounding_table[];
extern	char 				KeyToggle[];
extern	signed 	char	IsUpper[];
extern	unsigned char	ToLower[];
extern	unsigned char 	ToUpper[];
extern	unsigned char	ASCtoImageTBL[];
extern	unsigned char 	LegalDial[];

//******************************************************************

extern	void	Euro96initialise();


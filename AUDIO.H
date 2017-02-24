/* Header File for Actua Soccer Audio */

#if     !defined(__AUDIO_H)
#define __AUDIO_H

//************************************************************************************************
// General
//************************************************************************************************

extern short int CrowdVolume;
extern short int PitchVolume;
extern short int CommentaryVolume;
extern short int MusicVolume;
extern short int MasterVolume;

typedef struct tagmadfile
	{
	char name[16];
	unsigned long int offset;
	unsigned long int length;
	}madfile;

enum							// Team names
	{
	HOME_TEAM,
	AWAY_TEAM
	};

struct memstatus
	{
	unsigned long int ext;				// Running total for Extended memory allocations
	unsigned long int base;				// Running total for Base memory allocations
	unsigned long int fail;				// Running total for Failed memory allocations
	};

// Structure for storing a sample in memory

typedef struct tagmemsam
	{
	char *name;								// Name of the samples disk file
	unsigned char *mem;					// Pointer to the sample when in memory
	long int size;							// Length of the sample when in memory
	unsigned short int flags;
	}memsam;

// Memory Sample Flags

#define MSF_LOADING	0x01				// Sample is currently loading (ie dont play)
#define MSF_DONTKEEP	0x02				// Sample should not be kept in memory after use (ie free it)
#define MSF_PLAYED	0x04				// Sample has already been played.

//************************************************************************************************
// Front End
//************************************************************************************************

#define MAX_FRONTEND_SAMPLES 4

enum
	{
	FS_CROWD,				// Crowd sample
	FS_PITCH,				// Pitch Sample
	FS_COMMENT,				// Commetary
	FS_CHEAT					// Cheat Sample
	};

//************************************************************************************************
// Pitch
//************************************************************************************************

#define MAX_PITCH_SAMPLES 20

enum
	{
	MS_AMBI2,				// Low Crowd Ambience
	MS_AMBI4,				// Low Crowd Ambience (Alternative)
	MS_AMBI6,				// Low Crowd Ambience (Alternative)
	MS_AMBI8,				// Low Crowd Ambience (Alternative)
	MS_GOAL,					// Crowd Cheers for a goal
	MS_MISS,					// Crowd Just Missed (Ooooh)
	MS_SAVE,					// Great Save (Claps)
	MS_LAUGH,				// Fluff (Laughs)
	MS_FOWL,
	MS_RESTLESS,			// Crowd Cheers for a goal
	MS_LNGREF,				// Long referee whistle
	MS_SHRTREF,				// Short referee whistle
	MS_HRDKICK,				// Hard Kick
	MS_KICK1,				// Kick
	MS_PASS1,				// Kick
	MS_BOOT,					// Kick
	MS_BOUNCE,				// Bounce
	MS_FALL,					// Sliding Tackle
	MS_FULL,					// Full time whistle
	MS_HALF					// Half time whistle
//	MS_C_FOWL,
//	MS_C_MISS,
//	MS_CHANT0,				// Random Chant for Variety
//	MS_CHANT1,				// Random Chant for Variety
//	MS_CHANT2,				// Random Chant for Variety
//	MS_CHANT3,				// Random Chant for Variety
//	MS_CHANT4,				// Random Chant for Variety
//	MS_CHANT5				// Random Chant for Variety
	};

// Sound effects for on the pitch, The frequency will be altered slightly for variety

enum
{
	PS_NULL,						// Diddly Squat

	PS_LONGWHISTLE,			// Various Whistles
	PS_SHORTWHISTLE,
	PS_HALFTIMEWHISTLE,
	PS_FULLTIMEWHISTLE,

	PS_SOFTKICK,				// Various Ball Kicks
	PS_MEDKICK,
	PS_HARDKICK,

	PS_SOFTHEAD,				// Various Headers
	PS_HARDHEAD,

	PS_SOFTCATCH,				// Various Handling of the Ball
	PS_HARDCATCH,
	PS_PUNCH,

	PS_SOFTBOUNCE,				// Various Ball Bounces
	PS_HARDBOUNCE,

	PS_SOFTWOOD,				// Various Ball Rebounds off the Woodwork
	PS_HARDWOOD,

//	PS_SOFTFOUL,				// Various Fouls
//	PS_MEDFOUL,
//	PS_HARDFOUL,

	PS_SLIDING,					// Sliding Tackle

	PS_SOFTGOAL,				// Various Balls Hitting the back of the net
	PS_HARDGOAL
};

typedef struct tagpitchsam
	{
	memsam *info;
	short int amp;							// Amplitude of Sample (volume 0x0 - 0x7fff)
	long int freq;							// Frequency Divider (typically 0x8000 - half)
	unsigned short int flags;
	}pitchsam;

#define PSF_THREED	0x01				// Use Pan and Volume from the call (3D Sound)
#define PSF_APPROX	0x02				// Play the sample at approximately the correct freqeuncy for Variety

//************************************************************************************************
// Crowd
//************************************************************************************************

enum
{
	CS_NULL,						// Diddly Squat

	CS_AMBIENCE1,				// Various Ambience levels
	CS_AMBIENCE2,
	CS_AMBIENCE3,
	CS_AMBIENCE4,
	CS_GOAL,						// Triggerd cheers
	CS_RESTLESS,
	CS_MISS,
	CS_SAVE,
	CS_LAUGH,
	CS_FOWL
//	CS_CHANT0,					// Crowd Chants
//	CS_CHANT1,					// Crowd Chants
//	CS_CHANT2,					// Crowd Chants
//	CS_CHANT3,					// Crowd Chants
//	CS_CHANT4,					// Crowd Chants
//	CS_CHANT5					// Crowd Chants
};

// Crowd noise definitions... (mood)

enum
{
	CN_OFF,

	CN_NORMAL,
	CN_PENSIVE,
	CN_ENCOURAGING,
	CN_EXCITED,
	CN_CELEBRATE,
	CN_BOO,
	CN_SAVE,
	CN_MISS,
	CN_LAUGH,
	CN_FOWL
};

struct crowdsam
{
	long int mood;					// Current mood of Crowd
	long int tranmood;			// Mood in for transition to
	long int mainhandle;			// Main sample handle of crowd sample
	long int mainvol;				// Volume of main crowd sample
	long int maindelta;			// Volume difference of main crowd sample
	long int mergehandle;		// Sample handle of Merging Crowd Sample
	long int mergevol;			// Volume of Merging Crowd Sample
	long int mergedelta;			// Volume Difference of Merging Sample
	long int volmax;				// Maximum volume crowd can reach
	long int pan;					// Pan Position of Crowd Sample
	long int pandelta;			// Pan Difference of Crowd Sample
	long int ticks;				// Number of Ticks since last random event
	long int nextevent;			// Number of Ticks to next event
	short int flags;				// Flags to control the above
};

// Events currently happening in the Crowd Update

#define CF_PAN 	0x01
#define CF_TRAN	0x02

//************************************************************************************************
// Commentary
//************************************************************************************************

#define MAX_REPEAT_BUFFER 64		// Amount of samples that must be played before a repeat
#define MAX_REPEAT_ATTEMPTS 4		// Amount of attempts to find a sample that does not repeat

#define MAX_LINKS 4					// Maximum amount of samples that can be load into link buffer

#define MAX_COMMENTARY_CATEGORIES 35

// Maximum Samples for each commentary category

enum							// Team Intonation
	{
	TI_WELCOME,
	TI_AND_NAME,
	TI_NAME
	};

enum							// Player Intonation
	{
	PI_OWN_HALF,
	PI_OPPONENTS_HALF,
	PI_SHOOTING
	};

enum
	{
	CM_NULL,

	SP_CORNER,				// Set piece
	SP_GOALKICK,
	SP_THROWIN,
	SP_LONGTHROWIN,
	SP_PENALTY,

	FU_FREEKICK,			// Foul
	FU_WALL,
	FU_BADFOUL,
	FU_YELLOWCARD,
	FU_REDCARD,
	FU_INJURY,
	FU_DIVE,

	CP_LONG,					// Completed pass
	CP_SHORT,
	CP_TARGET,
	CP_HEAD,
	CP_NICEMOVE,
	CP_SETPIECE,

	FP_LONG,					// Failed Pass
	FP_SHORT,
	FP_LOOSE,

	GL_GENERIC,				// Goal
	GL_DEFLECT,
	GL_HARDKICK,
	GL_HEADER,
	GL_KEEPER,
	GL_POST,
	GL_CURVE,
	GL_CURVEWALL,

	PM_CATCH,				// Player missed goal attempt
	PM_BLOCK,
	PM_WIDE,
	PM_CLOSE,
	PM_POST,
	PM_CROSSBAR,

	MC_PREMATCH,
	OT_GOODPLAY,
	OT_POORPLAY,

	SU_ONFOR,
	SU_TEAM,
	SU_INJURED,

	TI_HALFTIME,
	TI_FULLTIME,

	CM_LINKBANK
	};

#define MAX_SP_CORNER 		12
#define MAX_SP_GOALKICK		8
#define MAX_SP_THROWIN 		5
#define MAX_SP_LONGTHROWIN 6
#define MAX_SP_PENALTY		24

#define MAX_FU_FREEKICK		9
#define MAX_FU_WALL			9
#define MAX_FU_BADFOUL		15
#define MAX_FU_YELLOWCARD	8
#define MAX_FU_REDCARD		9
#define MAX_FU_INJURY		8
#define MAX_FU_DIVE			8

#define MAX_CP_LONG			6
#define MAX_CP_SHORT			4
#define MAX_CP_TARGET		20
#define MAX_CP_HEAD			2
#define MAX_CP_NICEMOVE		7
#define MAX_CP_SETPIECE		13

#define MAX_FP_LONG			3
#define MAX_FP_SHORT			2
#define MAX_FP_LOOSE			8

#define MAX_GL_GENERIC		36
#define MAX_GL_DEFLECT		8
#define MAX_GL_HARDKICK		8
#define MAX_GL_HEADER		15
#define MAX_GL_KEEPER		9
#define MAX_GL_POST			8
#define MAX_GL_CURVE			7
#define MAX_GL_CURVEWALL	4

#define MAX_PM_CATCH			21
#define MAX_PM_BLOCK			14
#define MAX_PM_WIDE			21
#define MAX_PM_CLOSE			16
#define MAX_PM_POST			8
#define MAX_PM_CROSSBAR		11

#define MAX_MC_PREMATCH		19
#define MAX_OT_GOODPLAY		26
#define MAX_OT_POORPLAY		13

#define MAX_SU_ONFOR			4
#define MAX_SU_TEAM			5
#define MAX_SU_INJURED		4

struct commcat
	{
	char name[4];
	short int count;
	};

typedef struct tagintonsam
	{
	memsam x;		// x,y,z are types of Intonation
	memsam y;
	memsam z;
	}intonsam;

typedef struct tagteamsam
	{
	int team;				// Number of team in game data
	intonsam country;
	intonsam manager;
	intonsam players[11];
	}teamsam;

//************************************************************************************************
// External Functions
//************************************************************************************************

extern unsigned long int InitMatchAudio(unsigned long int seed);
extern void UpdateVolumeLevels(void);

extern long int StartMusic(char *name,int volume);
extern void StopMusic(void);
extern long int UpdateMusic(void);
extern int CheckMusic(void);

extern unsigned long int LoadPitchSamples(void);
extern void FreePitchSamples(void);
extern long int PlayPitchSample(int sam,short int amp,short int pan);

extern void StartCrowd(int team);
extern void StopAudio(void);
extern long int PlayCrowdSample(int sam);
extern void UpdateCrowd(int mood,int team);

extern unsigned long int LoadTeamSamples(int team_num,int team);
extern void FreeTeamSamples(int team);

extern unsigned long int LoadFrontEndSamples(void);
extern void FreeFrontEndSamples(void);

extern unsigned long int LoadCommentarySamples(void);
extern void FreeCommentarySamples(void);
extern void UpdateCommentary(void);
extern void PauseCommentary(void);
extern void ResumeCommentary(void);

extern long int PlayTeamSample(int player,int intonation);
extern void PlayWelcomeMessage(void);
extern void PlaySubstitutionMessage(int team,int player_off,int player_on,int injured);
extern void PlayScoreSample(int home,int away);
extern void PlayCommentaryMessage(int type);
extern void PlayPossessionSample(int team);
extern long int PlayFrontEndSample(int sam,int amp);

//************************************************************************************************
// Internal Functions
//************************************************************************************************

void FreeLinkBank(void);
short int CheckCommentary(void);

void CreateMusicFileName(char *name,char *dest);
void CreateScoreFileName(char *home,char *away,char *mad,char *dest);
void CreatePitchFileName(char *name,char *mad,char *dest);
void CreatePlayerFileName(char *country,char *number,char *intonation,char *mad,char *dest);
void CreateCommentaryFileName(char *category,char *number,char *mad,char *dest);
void CreateFrontEndFileName(char *category,char *name,char *mad,char *dest);

int LoadSample(char *mad,char *name,memsam *bank,struct memstatus *MemStatus);
void FreeSample(memsam *bank);
void LoadCommentarySample(char *category,int samples,memsam *bank);
int MADFindFile(FILE *fp,char *name);
int CheckRepeatBuffer(char *category,int num);
void ShowMemoryUsage(memstatus MemStatus,char *title);
void LogText(char *format,...);

#endif  /* __AUDIO_H */

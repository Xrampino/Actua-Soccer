#define	MAX_USERS	20

extern	"C"	volatile int Team_A,Team_B;
extern	"C"	int	TeamChoice;	
extern	"C"	int  	PlayerChoice;	
extern	"C"	int	TeamOveride;
extern	"C"	int	PlayerOveride;
extern	"C"	int 	netsetup_on;
extern	"C"	char  *InitString, *DialString;
extern	"C"	int	Call, Tone, CommPort, BaudRate;
extern	"C" 	int	network_on;
extern	"C"	volatile int NetTeams[MAX_USERS],Players[MAX_USERS];
extern	"C"	void  TickPause();
extern	"C"	int	Start_Network_Game();
extern	"C"	void	SendPlayerInfo();
extern	"C"	void	InitEUROnet();
extern	"C"	void	UnInitEUROnet();
extern	"C"	void	SendTeamInfo();
extern	"C"	char	CountNumberOfNETstarts();
extern	"C"	void	Set_Comm_Type( char ); 
extern	"C"	void	End_Net_Init();
extern	"C"	void	Initial_Quit();											
extern 	"C" 	volatile char keys[];
extern 	"C" 	volatile char key_togs[];



// NETWORK.C
extern "C" void read_joystick(char j,int *x, int *y, int *sw);
extern "C" void read_joy1(int *x, int *y, int *sw);
extern "C" void read_joy2(int *x, int *y, int *sw);
extern "C" void calibrate_joy(char j,unsigned short *x,unsigned short *y);
extern "C" void get_joy_dir1(int *x,int *y,int *f);
extern "C" void get_joy_dir2(int *x,int *y,int *f);
extern "C" void get_user_inputs();
extern "C" void process_user_inputs();

extern "C" volatile int NetTeams[MAX_USERS],Players[MAX_USERS];
extern "C" volatile int net_quit;
extern "C" volatile char paused;
extern "C" volatile char pause_request;
extern "C" volatile char keys[256];
extern "C" volatile char key_togs[256];
//extern "C" void setdigivar(short handle);

extern	"C" short net_game_no;
extern	"C" volatile short net_error;
extern	"C" char cd_in;
extern	"C" volatile char net_cd_in;

extern "C" void NetTest(void);
extern "C" void Network_Play_Ready();
extern "C" void Quit_Network_Play();
extern "C" void End_Network_Game();

extern "C" void __far nethandler(void);
extern "C" unsigned int NetworkHandle;
extern "C" short wConsoleNode;
extern "C" int network_on;
extern "C" volatile int count;
extern "C" volatile int tick;
extern "C" volatile int ftick;

extern "C" volatile int writeptr;
extern "C" volatile int readptr;
extern "C" int game_speed;		// Currently declared in network.c


extern "C" void ConfigControl();	

extern "C" unsigned short joy1_cnt_x,joy1_cnt_y;
extern "C" unsigned short joy2_cnt_x,joy2_cnt_y;
extern "C" void	ConfigControl();	

extern "C" void	InitCalibration(int j);
extern "C" void	CalibrateJoy(int j);	
extern "C" char	calibrate_flag,redefine_flag;
extern "C" char	print_joy_message,print_red_message;


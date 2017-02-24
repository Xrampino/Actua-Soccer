
#define TRUE 1
#define FALSE 0

enum {
	NET_ONLINE,
	NET_GO,
	NET_MESSAGE,
	NET_QUIT,
	NET_SINGLE,
	NET_MULTIPLE,
	NET_READY,
	NET_SEED,
	NET_PAUSE,
	NET_INFO
	};

typedef struct		// Header packet
{
	int dwSequence; // reserved by NetNow!
	short	player;	 // player
	short type;		 // type
	int frame;		 // frame number when issued (not always used)
}	packet_header;

typedef struct		// Setup info packet
{
	_NETNOW_NODE_ADDR address;	//node received info from.
	int Team_A,Team_B;
	int Team;
	int Player;
}	packet_info;

typedef struct		// Input data packet
{
	short x,y;		// 15 bits of signed directional data + lowest bits for two buttons
}	packet_single;

typedef struct		// Multiple input data packet
{
	packet_single inp[20];
}	packet_multiple;

typedef struct		// Message packet
{
	char mes[12];
}	packet_data;

typedef struct		// Random seed packet
{
	int	num;
}	packet_seed;

typedef	struct	// Pause key packet
{
	int	paused;
}	packet_pause;

extern packet_header	in_header;
extern packet_data	in_data[8];
extern short			wConsoleNode;
extern volatile int	writeptr,readptr;
extern volatile		packet_multiple copy_multiple[512];
extern short 			master;
extern volatile int	active_nodes;
extern volatile int	net_quit;

void	__far nethandler(void);

void	Initialise_Network();
void	send_quit();
void	send_mes(char *m);
int	receive_mes();
void	close_network();

void	send_seed(int num);
void	send_ready();
void	send_single(int plyr);
void	send_multiple();
void	receive_multiple();
void	receive_all_singles();
void	send_name(char *m);
void	TransmitInit(void);
int	FindNodes();
void	send_pause();
void	transmitpausetoslaves(void);

void	NetInitialisation();
void	FoundNodes();
void	SendNetDone();
void	SendPlayerInfo();



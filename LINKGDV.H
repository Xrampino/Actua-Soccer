//
// PLAYGDV.H
//
// Structures & types etc. needed for the player setup stuff
//

// Sound and video parameters (These must be set up before cgdv is called)
#define DEFAULT_DIGIRATE 216

#define NAME "LinkGDV"

// Globals
char gl_error[200];
unsigned short sound_flag,ldmasize,lfps,lsample_rate;
int volume,curmode;
extern unsigned char gl_shutdown;
char lsos_path[100],lconfig_file[100];
WORD DIGIDriverHandle; 
WORD DIGITimerHandle;  
int digirate;

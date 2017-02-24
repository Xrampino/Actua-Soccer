//
// CGDV.H
//
// Include file for cgdv(): Function version of gdv player
//

// Set to not return to current video mode but leave screen on
//#define HOLD_VIDMODE

// Possible values for play_flags: (OR them together. Some are unavailable
//                                             e.g. fades on 32k colour GDV's)
#define PL_SOUND      (1<<0)   // Plays anim with sound if available
#define PL_FADE_IN    (1<<1)   // Fade anim in before playing
#define PL_FADE_OUT   (1<<2)   // Fade anim out after playing
#define PL_INFO       (1<<3)   // Display info before playing
#define PL_HOLD       (1<<4)   // Holds image for PL_HOLD_TIME seconds before fade/exit
#define PL_REPEAT     (1<<5)   // Loops gdv continuously
#define PL_NO_STOP    (1<<6)   // Disables keyboard/mouse exit
#define PL_VGA        (1<<7)   // Uses 320x200 VGA rather than SVGA screen
#define PL_NO_DECODE  (1<<8)	 // Turns frame decoding off } For debugging 
#define PL_NO_DISPLAY (1<<9)	 // Turns screen update off  }	 only!

// Return codes from cgdv
#define PL_OKAY         0	 // No problems
#define PL_NO_FILE      1   // Could not find file
#define PL_NOT_GDV      2	 // File specified is not a GDV file
#define PL_READ_ERROR   3	 // Error while reading disk / CD
#define PL_UNPLAYABLE   4	 // GDV has wrong video/sound type, version etc.
#define PL_NO_MEM       5	 // Not enough memory to show anim
#define PL_STOPPED      6	 // Interrupted by key press or mouse click
#define PL_BAD_FRAME    7	 // Frame had bad magic number or type
#define PL_NO_TIMER     8	 // SOS could not allocate video timer event
#define PL_CRITICAL     9   // Critical error returned by DOS

#define PL_HOLD_TIME    2   // Hold time in seconds for PL_HOLD

#define GDV_MEM   2097152   // 2 Megabytes expected by cgdv()

// Prototype for playback routine
int cgdv(char *fname, unsigned short play_flags, unsigned char *memory);

//
//	GDV.H
//
//	Structures/types/defines for compresser and player
//
// Versions 3 and 4 (8 and 15 bit colour)
//

// Audio/Video data types
#define NO_SOUND             0
#define A_STANDARD_SOUND (1<<0)
#define A_STEREO         (1<<1)
#define A_16_BIT         (1<<2)
#define A_COMPRESSED     (1<<3)

#define NO_VIDEO             0
#define V_256_VIDEO      (1<<0)
#define V_32K_VIDEO      (1<<1)

// Sound and video parameters
#define SOUNDSIZE  (sample_rate/fps) 
#define FRAMESIZE  (videosize+SOUNDSIZE)

// Filenames
#define CONFIG_FILE     "config.ini" // } Unless overridden by env. var.
#define SOS_PATH        ".\\"        // } settings
#define file_type       "gdv"
#define VERSION         "4.0"

// Frame types within animation file
#define FRM_PALETTE        0 // New palette only (used for fades)
#define FRM_JOINER         1 // Blank screen
#define FRM_DELTA1         2 // Complete frame differences from last frame
#define FRM_HOLD		      3 // Hold frame; Do nothing.
#define FRM_PALETTE_DELTA1 4 // New palette and frame data (in that order)

// Token types within packed data
#define TKN_PIXEL     0             // 16 bit colour value (No match possible)
#define TKN_STRING    1             // 16 bit string (position and length) 
#define TKN_SAME8     2             // 8 bit 'no change' length
#define TKN_END       3             // Token signifying end of frame or block

// Standard VGA screen stats
#define VGA_256        0x13
#define VGA_256_WIDTH  320
#define VGA_256_HEIGHT 200
#define VGA_256_BANKS  1

// Super VGA mode 101h stats
#define SVGA_256        0x101
#define SVGA_256_WIDTH  640
#define SVGA_256_HEIGHT 480
#define SVGA_256_BANKS  5

// Super VGA mode 110h stats
#define SVGA_32K        0x110
#define SVGA_32K_WIDTH  640
#define SVGA_32K_HEIGHT 480
#define SVGA_32K_BANKS  10

#ifdef VGA_SCREEN
#undef VGA_SCREEN
#define VGA_SCREEN   (unsigned short *)0xa0000
#endif

// Compression stuff
#define DICT_BITS	 12
#define BUFF_BITS	 4
#define DICT_SIZE  (1<<DICT_BITS)
#define BUFF_SIZE  (1<<BUFF_BITS)
#define TOTAL_SIZE (DICT_SIZE+BUFF_SIZE)

// Magic numbers for headers
#define FRM_MAGIC	0x1305
#define GDV_MAGIC	0x29111994

// gl_shutdown error codes
#define GL_READ_ERROR  1<<0
#define GL_MAGIC_ERROR 1<<1
#define GL_FRAME_ERROR 1<<2
#define GL_TOKEN_ERROR 1<<3
#define GL_STOPPED     1<<4

// Main header for animation file [24 bytes]
struct gdv_header
{
	unsigned long magic;                         // Magic number for GDV files
   unsigned short dimensions;                   // Image dimension code
	unsigned short no_frames;                    // Total number of frames
	unsigned short fps;                          // Frames per second 
	unsigned short audio_type;                   // Type of audio data 
	unsigned short sample_rate;                  // Sound sample rate
	unsigned short video_type;                   // Type of video data 
	unsigned short video_size;                   // (Max.) Size of video/frame
	unsigned char version;                       // Version number
   unsigned char lossyness;                     // Quality
   unsigned char reserved[4];                   // For later...       UNUSED
};

// Header for each frame of the animation [8 bytes]
struct frame_header
{
	unsigned short magic;								// Magic frame number
	unsigned short	frame_size;							// Size of DATA in bytes
	unsigned char type;                          // Type of frame
	unsigned char reserved[3];							// For later 			 UNUSED
};

#define GAMMA_CORRECT 1.4

#define DIMENSIONS 32
#define MAX_256    16
                    
#ifdef CGDV
#ifndef GLOBAL
unsigned short widths[DIMENSIONS]=
{
   320,
   640,
   320,
   320,
   320,
   320,
   160,
   160,
   160,
	280,
	320,
   320,
	0,0,0,0,
   640,
   640,
   640,
   640,
   640,
   320,
	0,0,0,0,0,0,0,0,0,0
};

unsigned short heights[DIMENSIONS]=
{
   200,
   200,
   167,
   180,
   400,
   170,
   85,
   83,
   90,
	128,
   240,
	201,
	0,0,0,0,
   400,
   200,
   180,
   167,
   170,
   240,
	0,0,0,0,0,0,0,0,0,0
};
#else
extern unsigned short widths[],heights[];
#endif
#endif
   

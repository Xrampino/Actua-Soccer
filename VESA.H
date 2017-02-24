typedef char CHAR;
typedef short SHORT;

unsigned char *VESASource(int offset,int x,int y);
unsigned char *VESADest(int offset,int x,int y);
int VESAmode(int *modelist);		// pointer to modes in order of preference, returns mode
/*
Modes are:
0x06a 800x600   Graphic 16 (== Vesa 0x102)
0x100 640x400   Graphic 256
0x101 640x480   Graphic 256
0x102 800x600   Graphic 16 (== Mode 0x6a)
0x103 800x600   Graphic 256
0x104 1024x768  Graphic 16 
0x105 1024x768  Graphic 256
0x106 1280x1024 Graphic 16 
0x107 1280x1024 Graphic 256
0x108 80  x 60  Text
0x109 132 x 25  Text
0x10A 132 x 43  Text
0x10B 132 x 50  Text
0x10C 132 x 60  Text
0x10D 320x200   Graphic 32K   (1:5:5:5)
0x10E 320x200   Graphic 64K   (5:6:5)
0x10F 320x200   Graphic 16.8M (8:8:8)
0x110 640x480   Graphic 32K   (1:5:5:5)
0x111 640x480   Graphic 64K   (5:6:5)
0x112 640x480   Graphic 16.8M (8:8:8)
0x113 800x600   Graphic 32K   (1:5:5:5)
0x114 800x600   Graphic 64K   (5:6:5)
0x115 800x600   Graphic 16.8M (8:8:8)
0x116 1024x768  Graphic 32K   (1:5:5:5)
0x117 1024x768  Graphic 64K   (5:6:5)
0x118 1024x768  Graphic 16.8M (8:8:8)
0x119 1280x1024 Graphic 32K   (1:5:5:5)
0x11A 1280x1024 Graphic 64K   (5:6:5)
0x11B 1280x1024 Graphic 16.8M (8:8:8)

 */
int vesastart(int x, int y);	// Set start pixel of display
extern int winrange;
extern int Vbytesperline;
////////////////////////////////////////////////////////////
//// VESA STRUCTURES
// 
struct VESA_INF
	{																  
	char VESASignature[4];				// 4 signature bytes = "VESA" 
	SHORT VESAVersion;					// VESA version number
	long *OEMStringPtr;					// Pointer to OEM string
	CHAR Capabilities[4];				// capabilities of the video environment
	long *VideoModePtr;					// pointer to supported Super VGA modes
	SHORT TotalMemory;					// Number of 64kb memory blocks on board
	};

struct ModeInfoBlock
	{
	// mandatory information
    SHORT ModeAttributes;		// mode attributes
    CHAR WinAAttributes;		// window A attributes
    CHAR WinBAttributes;		// window B attributes
    short WinGranularity;		// window granularity SHORT
    SHORT WinSize;				// window size
    unsigned short WinASegment;	// window A start segment
    unsigned short WinBSegment;	// window B start segment
    long WinFuncPtr;			// pointer to windor function
    SHORT BytesPerScanLine;		// bytes per scan line
	// formerly optional information (now mandatory)
    SHORT XResolution;			// horizontal resolution
    SHORT YResolution;			// vertical resolution
    CHAR XCharSize;				// character cell width
    CHAR YCharSize;				// character cell height
    CHAR NumberOfPlanes;		// number of memory planes
    CHAR BitsPerPixel;			// bits per pixel
    CHAR NumberOfBanks;			// number of banks
    CHAR MemoryModel;			// memory model type
    CHAR BankSize;	 			// bank size in kb
    CHAR NumberOfImagePages;	// number of images
    CHAR Reserved;	 			// reserved for page function
	// new Direct Color fields
    CHAR RedMaskSize;			// size of direct color red mask in bits
    CHAR RedFieldPosition;		// bit position of LSB of red mask
    CHAR GreenMaskSize;			// size of direct color green mask in bits
    CHAR GreenFieldPosition;	// bit position of LSB of green mask
    CHAR BlueMaskSize;			// size of direct color blue mask in bits
    CHAR BlueFieldPosition;		// bit position of LSB of blue mask
    CHAR RsvdMaskSize;			// size of direct color reserved mask in bits
    CHAR DirectColorModeInfo;	// Direct Color mode attributes
	};


#ifndef _vesa_gen
extern struct VESA_INF *vesa_inf;
extern struct ModeInfoBlock *vmode_inf;
#endif


														  //
														////
////////////////////////////////////////////////////////////


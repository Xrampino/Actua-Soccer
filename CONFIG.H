/* Header File for Gremlin Standard Config File*/

#if     !defined(__CONFIG_H)
#define __CONFIG_H

#define CONFIG_FILE "CONFIG.INI"			// Name of Config File

struct configint
	{
	char *name;
	unsigned short int *var;
	unsigned short int def;
	};

// Names to search for
#define SOURCE_PATH "SourcePath"
#define DEST_PATH "DestinationPath"
#define INSTALL_TYPE "Installation"
#define LANGUAGE "Language"
#define SOUND_CARD "SoundCard"
#define SOUND_PORT "SoundPort"
#define SOUND_IRQ "SoundIRQ"
#define SOUND_DMA "SoundDMA"
#define SOUND_FREQUENCY "SoundFrequency"
#define SOUND_RATE "SoundIntRate"
#define SOUND_HARD_BUFFER "SoundHardDiskBuffer"
#define SOUND_DMA_BUFFER "SoundDMABuffer"
#define MUSIC_CARD "MusicCard"
#define MUSIC_PORT "MusicPort"
#define MUSIC_IRQ "MusicIRQ"

// Detail Level Defines
enum
{
	HIRES,
	LORES,
	HIRES_LORES
};

// Speech/Text Defines
enum
{
	SPEECH,
	TEXT,
	SPEECH_TEXT
};

// Installation Size Defines
enum
{
	STANDARD,
	MINIMUM,
	MAXIMUM,
};

// Language Defines
enum
{
	ENGLISH,
	FRANCAIS,
	DEUTSCH,
	AMERICAN,
	CANADIAN,
	NORWEGIAN
};

// Directory Configuration
extern char SourcePath[64];
extern char DestinationPath[64];

// Installation Size
extern unsigned short int Installation;

// Language
extern unsigned short int Language;

// Sound Card Configuration
extern unsigned short int SoundCard;				// SOS ID of Sound Card
extern unsigned short int SoundPort;				// Port Address
extern unsigned short int SoundIRQ;					// Interrupt
extern unsigned short int SoundDMA;					// DMA Channel
extern unsigned short int SoundFrequency;			// Base Frequency for samples
extern unsigned short int SoundIntRate;			// Digital timer interrupt rate
extern unsigned short int SoundHardDiskBuffer;	// Hard Disk Buffer Size
extern unsigned short int SoundDMABuffer;			// Digital DMA Buffer Size

// Music Card Configuration
extern unsigned short int MusicCard;		// SOS ID of Music Card
extern unsigned short int MusicPort;		// Music Port
extern unsigned short int MusicIRQ;			// Music IRQ

// Reads config file and fills in variables appropriately
extern short int ReadConfigFile(void);

// Used internally to find a config string
char *FindConfigVar(char *ptr,char *def);

#endif  /* __CONFIG_H */

/****************************************************************************

   File              : sosm.h

   Programmer(s)     : Don Fowler, Nick Skrepetos
   Date              :

   Purpose           : Include Files For Zortech C++ Compiler

   Last Updated      :

****************************************************************************
               Copyright(c) 1993,1994 Human Machine Interfaces 
                            All Rights Reserved
****************************************************************************/

#ifndef  _SOS_MIDI_DEFINED   
#define  _SOS_MIDI_DEFINED   

#include "sosdefs.h"
#include "sos.h"

#pragma pack(4)

#define  _SOS_MIDI_ERR          -1

// number of drivers allowed to be open at one time
#define  _SOS_MIDI_MAX_DRIVERS  5

// maximum number of allowed channels
#define  _SOS_MIDI_MAX_CHANNELS    0x10

// structure definition for the capabilities
typedef struct
{
   BYTE     szDeviceName[ 32 ];  // device name
   WORD     wDeviceVersion;      // device version
   WORD     wFlags;              // miscellaneous flags   
   WORD     wProcessData;        // process data before sending to driver
   short far *   lpPortList;          // list of usable ports
   short far *   lpIRQList;           // list of usable irq channels
   WORD     wDeviceID;           // ID for the device
   
} _SOS_MIDI_CAPABILITIES; 

#define  LPSOSMIDIDEVICECAPS  _SOS_MIDI_CAPABILITIES far *

// call indexes for the loadable drivers
enum
{ 
   _DRV_MIDI_GET_CAPS,
   _DRV_MIDI_GET_CALL_TABLE,
   _DRV_MIDI_SPECIAL1
};

// file header for the driver
typedef struct
{
   // name ID
   BYTE  szName[ 32 ];

   // number of drivers in the file
   WORD  wDrivers;

   // offset of first driver
   WORD  lOffset;

   // size of the file
   WORD  lFileSize;

} _MIDIFILEHEADER;

// driver header structure
typedef struct
{
   // name ID
   BYTE  szName[ 32 ];

   // offset of next driver
   WORD  lNextDriver;

   // size of current driver
   WORD  wSize;

   // id for the current device
   WORD  wDeviceID;

   // id for the extender type
   WORD  wExtenderType;

} _MIDIDRIVERHEADER;

// device hardware information
typedef struct
{
   // port to be used
   WORD  wPort;

   // IRQ for the board
   WORD  wIRQ;

   // extra parameter
   WORD  wParam;

} _SOS_MIDI_HARDWARE;

// structure for initializing a digital driver 
typedef struct
{
   // ID for the digital driver
   WORD  wDriverID;

   // timer rate to use
   WORD  wTimerRate;

   // timer callback rate to use
   WORD  wTimerCallbackRate;

   // max voices for the driver to use
   WORD  wMaxVoices;

   // velocity sensing flag
   WORD  wVelocitySensing;

   // init driver info
   _SOS_INIT_DRIVER far * sDIGIDriverInfo;

   // hardware information
   _SOS_HARDWARE far *  sDIGIHardwareInfo;    

} _SOS_MIDI_DIGI_INIT_DRIVER;

// structure for initializing a driver
typedef struct
{  
   // type of driver to use if using a digital driver
   WORD        wDIGIDriverID;

   // pointer to driver memory
   VOID far * lpDriverMemory;
   VOID far * lpDriverMemoryCS;

   // pointer to digital driver initialization information
   _SOS_MIDI_DIGI_INIT_DRIVER far * sDIGIInitInfo;

   // miscellaneous WORD parameter for driver
   WORD  wParam;

   // miscellaneous DWORD parameter for driver
   DWORD dwParam;

} _SOS_MIDI_INIT_DRIVER;

// structure for starting a song
typedef struct
{  
   // pointer to song memory 
   BYTE _huge * lpSongData;

   // pointer to callback function for pertinent song information
   VOID ( far * lpSongCallback )( WORD );

} _SOS_MIDI_INIT_SONG;

// define to indicate that track mapping can be used
// from the midi file for the song
#define  _MIDI_MAP_TRACK   0xff
  
// MIDI channel to device mapping structure
typedef struct
{
   // track to device mapping information
   WORD wTrackDevice[ 32 ];
     
} _SOS_MIDI_TRACK_DEVICE;

// MIDI channel to device mapping structure
typedef struct
{
   // track to device mapping information
   WORD wTrackDevice[ 32 ][ 5 ];
     
} _SOS_MIDI_TRACK_DEVICE1;

// NEW
// header for the NDMF format MIDI file 
typedef struct
{
   // ID for the file
   BYTE  szFileID[ 32 ];

   WORD dwBranchOffset;
   WORD temp1;
   WORD temp2;
   WORD temp3;

//   // name of the instrument file to use with the song   
//   BYTE  szInstrumentFile[ 16 ];

   // number of tracks in the song
   WORD  wNDMFTracks;

   // ticks/quarter note song is used at
   WORD  wTicksQuarterNote;

   // tempo
   WORD  wTempo;

   // time for song to play at current tempo
   WORD  wTimeToPlay;

   // channel mapping priority information
   WORD  wChannelPriority[ _SOS_MIDI_MAX_CHANNELS ];

   // channel mapping information
   _SOS_MIDI_TRACK_DEVICE1 sTrackMap;

   // array of flags for which controllers to restore on a loop/branch
   BYTE  bCtrlRestore[ 128 ];

   // pointer to callback function for song to call with 
   // pertinent information
   VOID ( far * lpSongCallback )( WORD ); 

} _NDMF_FILE_HEADER;
// END

// header for the tracks in the NDMF format MIDI file
typedef struct
{
   // track number
   WORD  wTrackNumber;

   // length of the track
   WORD  wTrackLength;

   // channel used on the track
   WORD  wChannel;

} _NDMF_TRACK_HEADER;

// MIDI event structure
typedef struct
{
   // dummy name to access midi data from
   BYTE  bMidiData[ 256 ];

} _NDMF_MIDI_EVENT;

// maximum number of songs that can be played at any time
#define  _SOS_MIDI_MAX_SONGS     8

// maximum number of tracks that can be used
#define  _SOS_MIDI_MAX_TRACKS    32

// number of driver functions
#define  _SOS_MIDI_DRV_FUNCTIONS 12

// enumeration for all of the drv functions
enum
{
   _MIDI_DRV_SEND_DATA,
   _MIDI_DRV_INIT,
   _MIDI_DRV_UNINIT,
   _MIDI_DRV_RESET,
   _MIDI_DRV_SET_INST_DATA
};

// defines for the loadable driver ids
#define  _MIDI_SOUND_MASTER_II      0xa000
#define  _MIDI_MPU_401              0xa001
#define  _MIDI_FM                   0xa002
#define  _MIDI_OPL2                 0xa002
#define  _MIDI_CALLBACK             0xa003
#define  _MIDI_MT_32                0xa004
#define  _MIDI_DIGI                 0xa005  
#define  _MIDI_INTERNAL_SPEAKER     0xa006
#define  _MIDI_WAVE_TABLE_SYNTH     0xa007  
#define  _MIDI_AWE32                0xa008  
#define  _MIDI_OPL3                 0xa009  
#define  _MIDI_GUS                  0xa00a  

// structure for the hmi instrument file header
typedef struct
{
   // file id type
   BYTE  szFileID[ 32 ];

   // file version
   WORD  wFileVersion;

   // size of the file
   WORD dwFileSize;

} _HMI_INS_FILE_HEADER;


// define for identifying a drum instrument  
#define  _SOS_MIDI_DRUM_INS   ( short )0x8000

// maximum number of timer events that can be registered 
#define  _TIMER_MAX_EVENTS    0x10  

// structure for digital driver queue element
typedef struct _tagQueueElement
{
   // handle for the sample
   WORD  wSampleHandle;

   // id for the sample
   WORD  wSampleID;

   // velocity for the sample
   WORD  wVelocity;

   // channel for the sample
   WORD  wChannel;

} _DIGI_QUEUE_ELEMENT;

// maximum number of instruments that can be set in the 
// digital driver
#define  _MAX_INS    128

// define for the maximum number of times a channel can be stolen
#define  _SOS_MIDI_MAX_LEVELS    0x04

// structure for MIDI information to be stored on the local stack
// when a channel is stolen
typedef struct
{
   // used element
   BYTE  bUsed;

   // last pitch bend information sent
   BYTE  bPitchBend;

   // channel volume
   BYTE  bChannelVolume;

   // instrument information
   BYTE  bInstrument;

   // sustain pedal
   BYTE  bSustain;

} _SOS_MIDI_CHANNEL_DATA;
 
// flags for the debugging system
#define  _SOS_DEBUG_NORMAL       0x0000
#define  _SOS_DEBUG_NO_TIMER     0x0001

// ID for 32 bit MIDI file
#define  _SOS_MIDI_FILE_ID       "HMIMIDIP"  

// structure for branch location controller
typedef struct
{
   // offset from start of track data
   WORD     dwOffset;

   // branch ID number
   BYTE     bBranchID;

   // current instrument
   BYTE     bInstrument;

   // current loop count for temporary storage
   // so that a track can be looped without 
   // needing any data from the program
   BYTE     bLoopCount;

   // number of controller messages stored
   BYTE     bCtrlChangeCount;

   // offset of control change information from start of file
   WORD     lpCtrlChangeData;   
   WORD     lpCtrlChangeDataTemp;
   
   // reserved fields
   WORD     wReserved1;
   WORD     wReserved2;

} _SOS_BRANCH_POINT;

#define  _SOS_MIDI_FADE_IN          0x01  
#define  _SOS_MIDI_FADE_OUT         0x02  
#define  _SOS_MIDI_FADE_OUT_STOP    0x04  

// structure for digital drums to use to store midi information
typedef struct
{
   // current volume
   WORD  wVolume;

   // current pan position
   WORD  wPanPosition;

   // reserved
   DWORD dwReserved;
   
} _SOS_MIDI_DIGI_CHANNEL;

// instrument file header structure
typedef struct
{
   // file ID
   BYTE  szID[ 32 ];

   // file version
   WORD  wVersion;

   // instruments in file
   WORD  wInstruments;

   // list of pointers to start sample structures
   _SOS_START_SAMPLE far * lpStartSample[ _MAX_INS ];

   DWORD temp1;
   DWORD temp2;

} _WAVE_FILE_HEADER;

#pragma pack()

// define for the busy error returned from send data
#define  _ERR_DRIVER_BUSY  0xf000

// NEW
// defines for the looping branch controllers
#define  _SOS_SET_FLAG   103
#define  _SOS_RESET_FLAG 104
#define  _SOS_BRANCH1   108
#define  _SOS_BRANCH2   109
#define  _SOS_BRANCH3   110
#define  _SOS_BRANCH4   111
#define  _SOS_BRANCH5   112
#define  _SOS_BRANCH6   113
#define  _SOS_BRANCH7   114
#define  _SOS_BRANCH8   115
#define  _SOS_BRANCH9   116
#define  _SOS_BRANCH10  117
#define  _SOS_BRANCH11  118
#define  _SOS_BRANCH12  119
#define  _SOS_BRANCH13  120
#define  _SOS_BRANCH14  121

// define for the program change controller flag
#define  _SOS_PROGRAM_CHANGE_FLAG   108

// END
#include "sosmdata.h"
#include "sosmfnct.h"

#endif

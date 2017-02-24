/****************************************************************************

   File              : sosmdata.h

   Programmer(s)     : Don Fowler, Nick Skrepetos
   Date              :

   Purpose           : Include Files For Zortech C++ Compiler

   Last Updated      :

****************************************************************************
               Copyright(c) 1993,1994 Human Machine Interfaces 
                            All Rights Reserved
****************************************************************************/


#ifndef  _SOS_MIDI_DATA
#define  _SOS_MIDI_DATA

#include "sos.h"

#pragma pack(4)

extern   WORD     _wSOSMIDIDriverLinear[];
extern   LPSTR    _lpSOSMIDIDriver[];
extern   LPSTR    _lpSOSMIDIDriverCS[];
extern   WORD     _wSOSMIDIMemHandle[];
extern   BOOL     _wSOSMIDIDriverLoaded[];
extern   WORD     _wSOSMIDIDriverType[];
extern   WORD     _wSOSMIDIDriverID[];
extern   DWORD    _dwSOSMIDITrackDeltaCurrent[][_SOS_MIDI_MAX_TRACKS];
extern   WORD     _wSOSMIDIActiveTracks[];
extern   WORD     _wSOSMIDITotalTracks[];
extern   DWORD    _dwSOSMIDITrackDeltaTime[][_SOS_MIDI_MAX_TRACKS];
extern   WORD     _wSOSMIDISongPaused[];
extern   WORD     _wSOSMIDISongMuted[];
extern   BOOL     _wSOSMIDISongActive[];
extern   BYTE     _bSOSMIDIEventSize[];
extern   BYTE     _bSOSMIDIEventSizeControl[];
extern   _SOS_MIDI_CAPABILITIES far * _lpSOSMIDIDriverCaps[];
extern   _SOS_MIDI_TRACK_DEVICE far * _sSOSMIDITrackMap[];   
extern   _NDMF_MIDI_EVENT _huge *  _lpSOSMIDITrack[][_SOS_MIDI_MAX_TRACKS];
extern   WORD  ( cdecl far *_lpSOSMIDIDrvFunction[ _SOS_MIDI_MAX_DRIVERS ][ _SOS_MIDI_DRV_FUNCTIONS ] )( LPSTR, WORD, WORD );   
extern   _NDMF_FILE_HEADER far * _sSOSMIDISongHeader[];
extern   _SOS_INIT_DRIVER        _sSOSDIGIInitDriver[];
extern   WORD _wSOSMIDIEventHandle[];
extern   BYTE  _szSOSMIDIDrvFile[];
extern   _MIDIFILEHEADER    _sSOSMIDIDRVFileHeader;
extern   _MIDIDRIVERHEADER  _sSOSMIDIDRVDriverHeader;
extern   BOOL  _wSOSMIDISysInititalized;
extern   WORD ( cdecl far *_lpSOSMIDICBCKDrvFunctions[] )( LPSTR, WORD, WORD );
extern   VOID ( cdecl far *_lpSOSMIDICBCKFunctions )( LPSTR, WORD, WORD );
extern   WORD _wMIDIDIGISampleQueueHead[];
extern   WORD _wMIDIDIGISampleQueueTail[];
extern   WORD _wMIDIDIGIMaxSamples[];
extern   WORD _wMIDIDIGIUsedSamples[];
extern   _DIGI_QUEUE_ELEMENT _sMIDIDIGIQueue[][ _MAX_VOICES ];


extern   WORD ( cdecl far *_lpMIDIDIGIDrvFunctions[] )( LPSTR, WORD, WORD );
extern   _SOS_START_SAMPLE far * _sMIDIDIGIStartSample[][ _MAX_INS ];
extern   _HMI_INS_FILE_HEADER far * _sMIDIDIGIInsFileHeader[];
extern   WORD _wMIDIDIGIDriverHandle[];
extern   WORD _wMIDIDIGIDriverInitialized[];
extern   WORD _wMIDIDIGITimerEventHandle[];
extern   WORD _wMIDIDIGIDriverInitMIDI[];
extern   WORD _wMIDIDIGIVelocitySensing[];
extern   BYTE _szMIDIDIGIInsFileID[];

extern   BYTE  _bSOSMIDIMasterVolume;
extern   BYTE  _bSOSMIDIDeviceChannelVolume[][ _SOS_MIDI_MAX_CHANNELS ];
extern   BYTE  _bSOSMIDIMT32SendData;

extern   LPSTR lpFake;
extern   WORD  wFake;

extern   _NDMF_TRACK_HEADER _huge *_lpSOSMIDITrackHeaders[][ _SOS_MIDI_MAX_TRACKS ];
extern   BYTE  _bSOSMIDIChannelRemap[][ _SOS_MIDI_MAX_SONGS ][ _SOS_MIDI_MAX_CHANNELS ];
extern   BYTE  _bSOSMIDIChannelPriority[][ _SOS_MIDI_MAX_CHANNELS ];
extern   BYTE  _bSOSMIDIOwnerChannel[][ _SOS_MIDI_MAX_CHANNELS ];
extern   BYTE  _bSOSMIDIOwnerSong[][ _SOS_MIDI_MAX_CHANNELS ];
extern   _SOS_MIDI_CHANNEL_DATA _sSOSMIDIChannelData[][ _SOS_MIDI_MAX_CHANNELS ][ _SOS_MIDI_MAX_LEVELS ];
extern   BYTE  _bSOSMIDIChannelDataIndex[][ _SOS_MIDI_MAX_SONGS ][ _SOS_MIDI_MAX_CHANNELS ];
extern   BYTE  _bSOSMIDIData[];
extern   BYTE  _bSOSMIDIData1[];
extern   BYTE  _bSOSMIDIDeviceLowPriority[];
extern   WORD  _wSOSMIDIChannelStealing;
extern   BYTE  _bSOSMIDIDeviceChannelActive[][ _SOS_MIDI_MAX_CHANNELS ];
extern   BYTE  _bSOSMIDIDeviceChannelAvailable[][ _SOS_MIDI_MAX_CHANNELS ];
extern   BYTE  _bSOSMIDISongHandle;
extern   BYTE  _szMIDIMIDIFileID[];
extern   BYTE  _pSOSMIDIDriverPath[];
extern   BYTE  _pSOSMIDITempDriverPath[];
extern   WORD  sosMIDIData_Start;
extern   WORD  sosMIDIData_End;
extern   WORD  ( cdecl far *_lpSOSMIDIAWEDrvFunctions[5] )( LPSTR, WORD, WORD );
extern   WORD  _wSOSGravisTimerHandle;
extern   WORD  _wSOSMIDISongVolume[];

extern   _SOS_BRANCH_POINT far * _lpMIDIBranchData[][ _SOS_MIDI_MAX_TRACKS ];
extern   WORD ( far *_lpSOSMIDIBranchCallback[] )( WORD, BYTE, BYTE );
extern   WORD ( far *_lpSOSMIDILoopCallback[] )( WORD, BYTE, BYTE, BYTE );
extern   WORD ( far *_lpSOSMIDITriggerCallback[][ 127 ] )( WORD, BYTE, BYTE );
extern   BYTE _bSOSMIDIBranchOccurred;

extern   WORD  _wSOSMIDIVolumeFadeDirection[];
extern   DWORD _dwSOSMIDIVolumeFadeFraction[];
extern   DWORD _dwSOSMIDIVolumeFadeVolume[];
extern   WORD  _wSOSMIDIVolumeFadeTicks[];
extern   BYTE  _bSOSMIDIHandleVolumeFade[];
extern   WORD  _wSOSDIGIMIDIHandle[];

extern   _SOS_MIDI_DIGI_CHANNEL _sMIDIDIGIChannel[];

extern   WORD ( cdecl far *_lpMIDIWAVEDrvFunctions[] )( LPSTR, WORD, WORD );
extern   WORD  _wSOSMIDIChannelMuted[][ _SOS_MIDI_MAX_CHANNELS ];

extern   BYTE  _szPLYMIDIBuffer[];
extern   WORD  _wPLYMIDIBufferIndex;
extern   WORD  _wSOSMIDIDriverSize[];

#pragma pack()

#endif

/****************************************************************************

   File              : sosmfnct.h

   Programmer(s)     : Don Fowler, Nick Skrepetos
   Date              :

   Purpose           : Include Files For Zortech C++ Compiler

   Last Updated      :

****************************************************************************
               Copyright(c) 1993,1994 Human Machine Interfaces 
                            All Rights Reserved
****************************************************************************/

#ifndef  _SOS_MIDI_FUNCTIONS
#define  _SOS_MIDI_FUNCTIONS

#pragma pack(4)

VOID interrupt far sosMIDITimerHandler (  VOID  );
WORD  sosMIDILockMemory                (  VOID  );
WORD  sosMIDIUnLockMemory              (  VOID  );
WORD  sosMIDIGetDeviceCaps             (  WORD, LPSOSMIDIDEVICECAPS  );
WORD  sosMIDIInitSystem                (  LPSTR, WORD  );
WORD  sosMIDIUnInitSystem              (  VOID  );
WORD  sosMIDIInitDriver                (  WORD, _SOS_MIDI_HARDWARE far *,
                                         _SOS_MIDI_INIT_DRIVER far *, WORD far *  );
WORD  sosMIDIUnInitDriver              (  WORD, BOOL  );
WORD  sosMIDILoadDriver                (  WORD, WORD, LPSTR far *, LPSTR far *, PSTR, PSTR, WORD * );
WORD  sosMIDIUnLoadDriver              (  WORD  );
WORD  sosMIDIInitSong                  (  _SOS_MIDI_INIT_SONG far *,
                                          _SOS_MIDI_TRACK_DEVICE far *,
                                          WORD far * );
WORD  sosMIDIUnInitSong                (  WORD  );
WORD  sosMIDIResetSong                 (  WORD, _SOS_MIDI_INIT_SONG far *  );
WORD  sosMIDIStartSong                 (  WORD  );  
WORD  sosMIDIStopSong                  (  WORD  );  
WORD  sosMIDIPauseSong                 (  WORD, WORD  );
WORD  sosMIDIMuteSong                  (  WORD  );
WORD  sosMIDIUnMuteSong                (  WORD  );
WORD  sosMIDIResumeSong                (  WORD  );
BOOL  sosMIDISongDone                  (  WORD  );  
WORD  sosMIDISongAlterTempo            (  WORD, WORD  );  
WORD  sosMIDIGetDeltaTime              (  LPSTR, DWORD far *  );
WORD  sosMIDISongGetTimeToPlay         (  WORD  );  
BYTE _huge * sosMIDINormalizePtr       (  BYTE _huge *  );
WORD  sosMIDISetInsData                (  WORD, LPSTR, WORD  );
WORD  sosMIDIResetDriver               (  WORD  );
BOOL  sosMIDIHandleMIDIData            (  WORD, LPSTR, WORD, WORD  );
WORD  sosMIDISendMIDIData              (  WORD, LPSTR, WORD  );
// NEW
VOID  sosMIDISetTrackState             (  WORD, WORD, WORD  );
// END

// compiled in drivers function interface
LPSTR digiGetCallTable                 (  VOID  );
LPSTR callbackGetCallTable             (  VOID  );
LPSTR aweGetCallTable                  (  VOID  );

WORD cdecl far callbackSendData             (  LPSTR, WORD, WORD  );
WORD cdecl far callbackInit                 (  LPSTR, WORD, WORD  );
WORD cdecl far callbackUnInit               (  LPSTR, WORD, WORD  );
WORD cdecl far callbackReset                (  LPSTR, WORD, WORD  );
WORD cdecl far callbackSetInstrumentData    (  LPSTR, WORD, WORD  );

WORD cdecl far aweSendData             (  LPSTR, WORD, WORD  );
WORD cdecl far aweInit                 (  LPSTR, WORD, WORD  );
WORD cdecl far aweUnInit               (  LPSTR, WORD, WORD  );
WORD cdecl far aweReset                (  LPSTR, WORD, WORD  );
WORD cdecl far aweSetInstrumentData    (  LPSTR, WORD, WORD  );

// function prototypes
WORD cdecl far digiSendData             (  LPSTR, WORD, WORD  );
WORD cdecl far digiInit                 (  LPSTR, WORD, WORD  );
WORD cdecl far digiUnInit               (  LPSTR, WORD, WORD  );
WORD cdecl far digiReset                (  LPSTR, WORD, WORD  );
WORD cdecl far digiSetInstrumentData    (  LPSTR, WORD, WORD  );

LPSTR waveGetCallTable                 (  VOID  );
WORD cdecl far waveSendData             (  LPSTR, WORD, WORD  );
WORD cdecl far waveInit                 (  LPSTR, WORD, WORD  );
WORD cdecl far waveUnInit               (  LPSTR, WORD, WORD  );
WORD cdecl far waveReset                (  LPSTR, WORD, WORD  );
WORD cdecl far waveSetInstrumentData    (  LPSTR, WORD, WORD  );
VOID cdecl far waveSampleCallback(  WORD, WORD, WORD  );

VOID        digiQueueInit           (  WORD, WORD  );
VOID        digiQueueUnInit         (  WORD  );
WORD        digiQueueAddItem        (  WORD, WORD, WORD, WORD, WORD );
WORD        digiQueueGetItem        (  WORD, WORD  );
WORD        digiQueueGetItemWAVE    (  WORD  );
WORD        digiQueueDeleteItem     (  WORD, WORD  );
WORD        digiQueueDeleteItemWAVE (  WORD, WORD  );
WORD        digiQueueDeleteItemMIDI (  WORD, WORD, WORD  );
WORD        digiQueueFindItemMIDI   (  WORD, WORD, WORD  );

// function prototypes
VOID cdecl far digiSampleCallback(  WORD, WORD, WORD  );

WORD        sosMIDIRegisterBranchFunction (  WORD, WORD ( far * )( WORD, BYTE, BYTE )  );
WORD        sosMIDIRegisterLoopFunction   (  WORD, WORD ( far * )( WORD, BYTE, BYTE, BYTE )  );
WORD        sosMIDIRegisterTriggerFunction(  WORD, BYTE, WORD ( far * )( WORD, BYTE, BYTE ) );
WORD        sosMIDIBranchToTrackLocation  (  WORD, BYTE, BYTE  );
WORD        sosMIDIBranchToSongLocation   (  WORD, BYTE  );

#ifdef __cplusplus
extern "C" {
#endif

extern   void  cdecl sosMIDIDRVGetCapsInfo( LPSTR, LPSTR, _SOS_MIDI_CAPABILITIES far * );
extern   void  cdecl sosMIDIDRVGetCapsPtr ( LPSTR, LPSTR, _SOS_MIDI_CAPABILITIES far * );
extern   void  cdecl sosMIDIDRVGetFuncsPtr( LPSTR, LPSTR, LPSTR );
extern   LPSTR cdecl sosMIDIDRVSpecialFunction( LPSTR, LPSTR, WORD );
extern   WORD cdecl xgetES( void );

#ifdef __cplusplus
}
#endif 

BOOL sosMIDIResetChannelStealing (  WORD  );
WORD sosMIDIEnableChannelStealing(  WORD  );
VOID far sosMIDISongHandler( VOID );

WORD sosMIDISetMT32InsData       (  WORD, LPSTR, WORD  );
WORD sosMIDISetMasterVolume      (  BYTE  );
VOID far sosMIDIMT32Timer        (  VOID  );

WORD sosMIDISetSongVolume        (  WORD, BYTE  );
WORD        sosMIDIFadeSong            (  WORD, WORD, WORD, BYTE, BYTE, WORD  );       

// functions for memory locking
VOID  sosMIDICaps_Start( VOID );
VOID  sosMIDICaps_End( VOID );
VOID  sosMIDICbck_Start( VOID );
VOID  sosMIDICbck_End( VOID );
VOID  sosMIDIDigi_Start( VOID );
VOID  sosMIDIDigi_End( VOID );
VOID  sosMIDIDone_Start( VOID );
VOID  sosMIDIDone_End( VOID );
VOID  sosMIDIDq_Start( VOID );
VOID  sosMIDIDq_End( VOID );
VOID  sosMIDIInit_Start( VOID );
VOID  sosMIDIInit_End( VOID );
VOID  sosMIDIIns_Start( VOID );
VOID  sosMIDIIns_End( VOID );
VOID  sosMIDILoad_Start( VOID );
VOID  sosMIDILoad_End( VOID );
VOID  sosMIDIPause_Start( VOID );
VOID  sosMIDIPause_End( VOID );
VOID  sosMIDIPtr_Start( VOID );
VOID  sosMIDIPtr_End( VOID );
VOID  sosMIDISong_Start( VOID );
VOID  sosMIDISong_End( VOID );
VOID  sosMIDISt_Start( VOID );
VOID  sosMIDISt_End( VOID );
VOID  sosMIDITmpo_Start( VOID );
VOID  sosMIDITmpo_End( VOID );
VOID  sosMIDITmr_Start( VOID );
VOID  sosMIDITmr_End( VOID );

void 	StringOut( BYTE X, BYTE Y, BYTE * String, BYTE Color );

#pragma pack()

#endif

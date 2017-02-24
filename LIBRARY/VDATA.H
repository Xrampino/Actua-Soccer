/****************************************************************************
*
*  File              : vdata.h
*  Date Created      : 1/31/95
*  Description       : voice chat data module header file
*
*  Programmer(s)     : Nick Skrepetos
*  Last Modification : 1/31/95 - 10:50:50 AM
*  Additional Notes  :
*
*****************************************************************************
*            Copyright (c) 1994,  HMI, Inc.  All Rights Reserved            *
****************************************************************************/

// various flags
extern   BOOL     wNETDebugFlag;
extern   BOOL     wNETAutoDetectFlag;
extern   BOOL     wNETAutoSettingsFlag;
extern   BOOL     wNETQuietFlag;
extern   BOOL     wNETInfoFlag;
extern   BOOL     wNETASyncFlag;
extern   BOOL     wNETRecordEnableFlag;

// number of nodes to search for
extern   WORD     wNETNodes;

// default socket number 
extern   WORD     wNETSocket;

// play back device
extern   WORD     wNETPlayDeviceID;

// record device
extern   WORD     wNETRecordDeviceID;

// dma buffer size
extern   WORD     wNETDMABufferSize;

// sample rate
extern   WORD     wNETSampleRate;

// timer rate
extern   WORD     wNETTimerRate;

// voice buffer size
extern   WORD     wNETVoiceBufferSize;

// number of voice buffers
extern   WORD     wNETVoiceBuffers;

// record buffer size
extern   WORD     wNETRecordBufferSize;

// hardware settings
extern   _SOS_HARDWARE     sNETPlaySettings;
extern   _SOS_HARDWARE     sNETRecordSettings;

// init driver structures
extern   _SOS_INIT_DRIVER  sNETPlayDriver;
extern   _SOS_INIT_DRIVER  sNETRecordDriver;

// handles to play and record drivers
extern   WORD     hNETPlayDriver;
extern   WORD     hNETPlayTimer;
extern   WORD     hNETRecordDriver;
extern   WORD     hNETRecordTimer;

// sample structures
extern   _SOS_START_SAMPLE    sNETPlaySample;
extern   _SOS_START_SAMPLE    sNETRecordSample;


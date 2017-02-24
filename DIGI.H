/* Header File for PEPSI Digital Audio */

#if     !defined(__DIGI_H)
#define __DIGI_H

#include <stdio.h>
#include "sos.h"

#define HSF_MONO 0
#define HSF_STEREO _STEREOTOMONO
#define HSF_8BIT _TRANSLATE8TO16
#define HSF_16BIT _TRANSLATE16TO8

#define DIGI_PATH "DIGI\\"
#define GDV_FPS 12									// Digital Video Frames/Second

#define IDF_VERBOSE 0x1

extern short int InitialiseDIGI(int freq,int flags);
extern short int UnInitialiseDIGI(void);
extern long int StartSample(void *mem,long int length,short int amp=0x7fff,short int pan=0x8000,long int freq=0x10000);
extern void StopSample(long int handle);
extern short int CheckSample(long int handle);
extern unsigned long int GetSamplePosition(long int handle);
extern void InitHardDiskSample(FILE *fp,long int offset,long int length,long int rate,long int volume,int flags,void(callback)(void)=NULL);
extern long int ContinueHardDiskSample();
extern void SetDIGIVolume(short int Master,short int HardDisk);

#define StopHardDiskSample() StopSample(HardDiskHandle)
#define CheckHardDiskSample() CheckSample(HardDiskHandle)
#define GetHardDiskSamplePosition() GetSamplePosition(HardDiskHandle)

void far cdecl HardDiskSampleCallBack(WORD wDriverHandle,WORD wAction,WORD wSampleHandle);

extern _SOS_START_SAMPLE	 HardDiskSampleData;
extern WORD DIGIDriverHandle;						// Handle of driver for playing samples
extern WORD DIGITimerHandle;						// Handle of timer
extern long int HardDiskHandle;					// Store for Hard Disk Sample handle

extern _SOS_CAPABILITIES DIGICapabilities;	// Capabilites of Sound Board;

#endif  /* __DIGI_H */

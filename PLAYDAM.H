#ifndef _PLAYDAM_H_INCLUDED
/*
 ษออออออออออออป
 บ AUTOHEADER บ
 ฬออออออออออออสออออออออออออออออออป
 บ Filename     PLAYDAM.H        บ
 วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
 บ Creation     11/5/1995        บ
 ฬอออออออออออออออออออออออออออออออน
 บ                               บ
 บ Updated: Fri 20/10/1995 18:59 บ
 บ                               บ
 บ Version: 1.080                บ
 บ                               บ
 ศอออออออออออออออออออออออออออออออผ
*/
//this file is the same as damlink.i to wasm

#include "sos.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef    struct _PlayAnimBlock {  // Used by InitAnim, StartAnim,StopAnim
           char  * FileName;        // address of a file name (term in zero)
           char  * DrvPath;         // driver path 0 = current CD used if player is opening SOS
                                    //    if not null must end in '\', 0
           unsigned char * MemBlock;// approx 2meg in size
           long  int MemBlockSize; 	// if 2meg then set to 2meg
           long  int DIGIHandle_SOS;// PAF_NotOpened = no sound
_SOS_CAPABILITIES * DriveCap_SOS;   // pointer to drive capability struc
           long  int Flags;         // see PAF_??

           void  * CallBack;        // Callback address 0=no callback see below

           short int FadeIn;        // 0=no fade (1=slow 64=VFast)
           short int FadeOut;       // 0=no fade
           short int DelayExit;     // hold last frame (ticks)


           //    screen defs are used by StartAnim, not InitAnim
           //    Screen mode if none 0 should be able to display GDV colour count
           //    see GDV_Header after InitAnim
			  //    note on this version BytesPerScan must match ScreenXSize 

           short int Screen;        // VGA mode or VESA 0=Auto, 0x13=VGA, 0x101=VESA (BIT 9 set)
                                    //    0x8000 = ModeX 320x200 : 0x8001 ModeX 320x400
           unsigned char ScreenWindow;// 0=UseWin(A) 1=UseWin(A+B)
           unsigned char ScreenGran;// used by vesa modes (will auto detect if 0)
												// this values = calc as (64/VESA_Gran)
           short int ScreenXSize;   
           short int ScreenYSize;   
           short int ScreenPage;    // mode X current page


           long  int SNDID;         // e000?
           long  int SNDPort;       // 0x220
           long  int SNDIRQ;        // 0x5
           long  int SNDDMA;        // 0x1
           long  int SNDPara;       // 0x0

           long  int FrameSize;     // These are filled in by InitANIM for info before you start the anim
           long  int ManyRead;      //	many frames ..
           long  int SampleSize;    //	adjusted for stereo and 16bit

           void  * GDV_Header;      // pointer to this GDV header

}          _PlayAnimBlock;


//#define  PAF_Abort 0x001    // key + mouse stops anim USE CallBack CBX_Abort
#define    PAF_UseTOD 0x002   // use TOD, no sound
#define    PAF_NoINT 0x004    // overrides UseTOD uses no IRQs at all (Test debug)
#define    PAF_LoopPlay 0x008 // No end... (does not work with NoINT)
#define    PAF_NoAudio 0x010  // turn off sound
#define    PAF_Interlace 0x020

#define    PAF_UseModeX 0x040 // Only needed if PlayAnimBlock.screen=0
#define    PAF_DontClip 0x080 // If picture dont fit on y uses every other scan
                              //    used for playing MODEX_HI on MODEX_LO
#define    PAF_ClearScreen 0x0100 // Force it to clear all the screen prior 
											 //  Start Anim, else will clear anim area only
											 // in the case of mode X clears both pages
#define    PAF_NotOpened 0x0DEAD // DIGIHandle_SOS = not opened


//PAE_Errors ....return from InitAnim and StartAnim...

#define    PAE_NoError 0x00

//system
#define    PAE_NoInit 0x001

//memory
#define    PAE_BadMemoryDEF 0x010
#define    PAE_NoMemory 0x011
#define    PAE_BuffTooSmall 0x012

//read
#define    PAE_FileNotFound 0x020
           //header
#define    PAE_BadFileRead1 0x021
           //frame head + sample
#define    PAE_BadFileRead2 0x022
           //pack data
#define    PAE_BadFileRead3 0x023

//data
#define    PAE_MAGICNotFound 0x030
#define    PAE_MAGICNotFound2 0x031
#define    PAE_PackSizeTooBig 0x032

//SOS
#define    PAE_SOS_Error 0x080000000
//and it 0x7ffffff and call SOSErrorString



//         your  callback macros =
//
// long  int CallBack ( long int CBM_???mode,
//                      gdv_header *,
//                      void  * PictureData,
//                      short int FrameNo)
//
//         return (CBX_???)   // see below for types..
//

#define    CBM_PreCopy 0      // IRQ Call
#define    CBM_AftCopy 1      // IRQ Call
#define    CBM_LookForAbort 2 // none IRQ call
#define    CBM_SetPalette 3   // IRQ Call, PictureData = R,G,B_Pack(63)x256

//Anim callback return flags

#define    CBX_Normal 0
#define    CBX_NoScreenCopy 1	// used if you are to handle the screen copy
                              //    only valid if CBM_PreCopy
#define    CBX_Abort 2	      // used when you detect an abort Input
#define    CBX_DonePalette 3	// when SetPalatte if you set the pal
                              //    return this to skip my code





#define    _PLAYDAM_H_INCLUDED
#ifdef     __cplusplus
};
#endif
#endif

#ifndef __CGL__
#define __CGL__
     /*********************************************************************
     
     cgl.h
     
     Copyright (c) Creative Technology Ltd. 1994-1995. All Rights Reserved.
     
     THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
     KIND,  EITHER EXPRESSED OR IMPLIED,  INCLUDING BUT NOT LIMITED TO THE 
     IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR 
     PURPOSE.
     
     *********************************************************************/

/*
 * @@ SOURCE DOCUMENTATION
 *
 * TITLE    : cgl.h
 * 
 * VERSION  : 0.01
 *
 * DATE     : 1 December 1994
 *
 * AUTHOR   : Philip Teo
 *            Toh Chin Kok
 *            Burak Alp
 *
 * BRIEF    : This file includes the function prototypes of all
 *            the graphic library supported
 *
 * @@ LOG CHANGE
 * DATE         VERSION   REV          DESCRIPTION
 * 13 Feb 95     1.0      Philip Teo   First library version
 * 11 Mar 95     1.1      Philip Teo   Second library version
 * 11 Apr 95     1.2      Philip Teo   Third library fixed point version
 */

#if (defined(__WATCOMC__) || defined(__SC__))
#define __32BIT_COMPILER__
#elif defined(WIN32)
#define __W32BIT_COMPILER__
#endif

#include "cgltype.h"
#include "cglerr.h"
#include "cgldef.h"

#ifdef WIN32
#include "cglwin.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/////////////////////////////
// Prototypes declaration  //
/////////////////////////////



////////////////////////////////////////////////////////////////////
// Primitive Operation Function                                   //
////////////////////////////////////////////////////////////////////
//                                                                //
// cglSendStream    - Function to perform block operation for     //
//                    render, copy, upload and download           //
// cglGetPixel      - Function to get pixel color                 //
// cglPutPixel      - Function to put pixel color                 //
//                                                                //
//                                                                //
////////////////////////////////////////////////////////////////////

extern CGL_INT16 CGL_API(cglSendStream)(CGL_PTR, CGL_UINT16);
extern CGL_INT16 CGL_API(cglGetPixel)(CGL_TYPE, CGL_TYPE, CGL_COLOR_PST);
extern CGL_INT16 CGL_API(cglPutPixel)(CGL_TYPE, CGL_TYPE ,CGL_COLOR_PST);

////////////////////////////////////////////////////////////////////
// Screen/Window Functions                                        //
////////////////////////////////////////////////////////////////////
//                                                                //
// cglInitScreen     - Initialise screen device &  configuration  //
// cglQueryScreen    - Query for valid screen configuration       //
// cglClearScreen    - Clear thes screen                          //
// cglCloseScreen    - Close the screen device                    //
// cglSetWindowClip  - Set the clipping window within the screen  //
// cglInitPan        - Initialise pan mode                        //
// cglSetPanPos      - Set panning position                       //
//                                                                //
////////////////////////////////////////////////////////////////////

extern CGL_INT16 CGL_API(cglInitScreen)(CGL_SCREEN_PST);
extern CGL_INT16 CGL_API(cglQueryScreen)(CGL_SCREEN_PST);
extern CGL_INT16 CGL_API(cglClearScreen)(void);
extern CGL_INT16 CGL_API(cglCloseScreen)(void);
extern CGL_INT16 CGL_API(cglSetWindowClip)(CGL_RECT_PST);
extern CGL_INT16 CGL_API(cglInitPan)(CGL_UINT16 *);
extern CGL_INT16 CGL_API(cglPanPos)(CGL_UINT16, CGL_UINT16);

////////////////////////////////////////////////////////////////////
// Primitive Property Functions                                   //
////////////////////////////////////////////////////////////////////
//                                                                //
//  cglSetLineStyle       - Set the line style pattern for line   //
//                          primitive                             //
//  cglSetFillPattern     - Set the fill area pattern for area    //
//                          primitive                             //
//  cglSetStipplePattern  - Set the stipple pattern for area      //
//                          primitive                             //
//  cglSetDepthMode       - Set the depth comparision mode for    //
//                          depth test.                           //
//  cglSetStencilMode     - Set the stencil comparision and       //
//                          update methods for stencil test.      //
//  cglSetLogicalOpsMode  - Set the comparision mode for logical  //
//                          operation for frame buffer            //
//  cglSetDitherMode      - Enable or disable dither function     //
//                                                                //
////////////////////////////////////////////////////////////////////

extern CGL_INT16 CGL_API(cglSetLineStyle)(CGL_PTR, CGL_UINT32);
extern CGL_INT16 CGL_API(cglSetFillPattern)(CGL_PTR, CGL_UINT32);
extern CGL_INT16 CGL_API(cglSetStipplePattern)(CGL_UINT8 *);
extern CGL_INT16 CGL_API(cglSetDepthMode)(CGL_UINT16);
extern CGL_INT16 CGL_API(cglSetStencilMode)(CGL_UINT16,CGL_UINT16,
                                           CGL_UINT16,CGL_UINT16);
extern CGL_INT16 CGL_API(cglSetLogicalOpsMode)(CGL_UINT16);
extern CGL_INT16 CGL_API(cglSetDepthCueColor)(CGL_COLOR_PST);
extern CGL_INT16 CGL_API(cglSetDitherMode)(CGL_UINT16);


///////////////////////////////////////////////////////////////////
// Texture Mangement Function                                    //
///////////////////////////////////////////////////////////////////
//                                                               //
//  cglLoadTextureMap     - Load the texture into free memory    //
//                          space.                               //
//                                                               //
///////////////////////////////////////////////////////////////////

extern CGL_INT16 CGL_API(cglLoadTextureMap)(CGL_TEXTURELD_PST);


//////////////////////////////////////////////////////////////////          
// Buffer Management Function                                   //
//////////////////////////////////////////////////////////////////
//                                                              //
//  cglSelectRenderBuffer - select render to front/back buffer  //
//                                                              //
//  cglCopyDisplayBuffer  - copy front/back buffer              //
//                                                              //
//  cglSetConstant        - Set the constant value for clear    //
//                          buffers.                            //
//  cglClearBuffer        - Clear multiple buffers to constant  //
//                          value respectively                  //
//                                                              //
//  cglSwapBuffer         - Swap buffers for double buffering   //
//                                                              //
//////////////////////////////////////////////////////////////////


extern CGL_INT16 CGL_API(cglSelectRenderBuffer)(CGL_UINT16);
extern CGL_INT16 CGL_API(cglCopyDisplayBuffer)(CGL_UINT16);
extern CGL_INT16 CGL_API(cglLockBuffer)(CGL_UINT16,CGL_FPTR *);
extern CGL_INT16 CGL_API(cglClearBuffer)(CGL_UINT32,CGL_RECT_PST);
extern CGL_INT16 CGL_API(cglSetConstant)(CGL_COLOR_PST,CGL_UINT32,CGL_UINT32);
extern CGL_INT16 CGL_API(cglSwapBuffer)(void);


//////////////////////////////////////////////////////////////////
// Color Management Function                                    //                             
//////////////////////////////////////////////////////////////////
//                                                              //
// cglUpLoad         - Retrieve data to host buffer             //
// cglDownLoad       - Send data from host buffer               //
// cglSetPalette     - Set the color palette table              //
// cglGetPalette     - Retrieve color data from palette table   //
//                                                              //
////////////////////////////////////////////////////////////////// 

extern CGL_INT16 CGL_API(cglUpLoad)(CGL_UPDN_PST);
extern CGL_INT16 CGL_API(cglDownLoad)(CGL_UPDN_PST);
extern CGL_INT16 CGL_API(cglSetPalette)(CGL_PTR, CGL_UINT16, CGL_UINT16);
extern CGL_INT16 CGL_API(cglGetPalette)(CGL_PTR, CGL_UINT16, CGL_UINT16);


//////////////////////////////////////////////////////////////////
// Querey Control Function                                      //
//////////////////////////////////////////////////////////////////
//                                                              //
//  cglSetPickRegion   - Set the condition and region of        //
//                       interest to pick                       //
//  cglSetExtentRegion - Set the extent condition               // 
//  cglGetPickResult   - Get the result of picking              //
//  cglGetExtentRegion - Get the extented region                //
//  cglGetConfig       - Get the version of software and        //
//                       hardware supported information         //
//  cglSetCursor       - Set cursor on/off,color and pattern    //
//  cglSetCursorPos    - Set cursor position                    //
//////////////////////////////////////////////////////////////////

extern CGL_INT16 CGL_API(cglSetPickRegion)(CGL_PICK_PST);
extern CGL_INT16 CGL_API(cglGetPickResult)(CGL_UINT8P);
extern CGL_INT16 CGL_API(cglSetExtent)(CGL_EXTENT_PST);
extern CGL_INT16 CGL_API(cglGetExtentResult)(CGL_RECT_PST);
extern CGL_INT16 CGL_API(cglGetConfig)(CGL_GPCONFIG_PST);
extern CGL_INT16 CGL_API(cglSetCursor)(CGL_UINT8, CGL_COLOR_PST, CGL_UINT8 *);
extern CGL_INT16 CGL_API(cglSetCursorPos)(CGL_UINT16,CGL_UINT16);
extern CGL_INT16 CGL_API(cglSetupInterrupt)(CGL_UINT32, CGL_ISRPROC, CGL_PTR);
extern CGL_INT16 CGL_API(cglReleaseInterrupt)(CGL_UINT32);

//-- For Dynmaic Library

#ifdef CGLCDL
extern CGL_INT16 cglStub();
int    cglLoad(char *path);
int    cglUnload(void);
#endif

#ifdef __cplusplus
}
#endif

#endif  // __CGL_


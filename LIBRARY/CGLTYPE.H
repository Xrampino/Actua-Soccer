#ifndef __CGL_TYPE__
#define __CGL_TYPE__

     /*********************************************************************
     
     cgltype.h
     
     Copyright (c) Creative Technology Ltd. 1994-1995. All Rights Reserved.
     
     THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
     KIND,  EITHER EXPRESSED OR IMPLIED,  INCLUDING BUT NOT LIMITED TO THE 
     IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR 
     PURPOSE.
     
     *********************************************************************/

/*
 * @@ SOURCE DOCUMENTATION
 *
 * TITLE    : cgltype.h
 * 
 * VERSION  : 0.01
 *
 * DATE     : 1 December 1994
 *
 * AUTHOR   : Philip Teo
 *            Toh Chin Kok
 *            Burak Alp
 *
 * BRIEF    : This file includes all definition of structure and
 *            data type used.
 *
 * @@ LOG CHANGE
 * DATE         VERSION   REV          DESCRIPTION
 * 13 Feb 95     1.0      Philip Teo   First library version
 * 11 Mar 95     1.1      Philip Teo   Remove CGL_CI_ST structure.
 *                                     Red component of CGL_COLOR_ST
 *                                     structure will be used as index
 *                                     for color index mode.
 * 24 Jul 95     1.2      Loy Y.C.     Added in macros for WIN32
 */

/////////////////////////
// Type Definition     //
/////////////////////////

#if (defined(__32BIT_COMPILER__) || defined(__W32BIT_COMPILER__))

#if defined(__W32BIT_COMPILER__)

#define CGL_API(f)        __stdcall f
#define CGLAPI            __stdcall
#define FPOINTER          *

#else

#if defined(CGLCDL)
#define CGL_API(f)        (*f)
#else
#define CGL_API(f)        f
#endif

#define CGLAPI
#define FPOINTER          far *

#endif   //-- 32BIT_COMPILER

#define PTR               *

#else

#define PTR               far *
#define FPOINTER          far *
#define CGL_API(f)        f
#define CGLAPI

#endif

typedef void PTR          CGL_PTR;
typedef void FPOINTER     CGL_FPTR;

typedef unsigned char    CGL_UINT8, PTR CGL_UINT8P;
typedef unsigned char    CGL_STRING;
typedef short            CGL_INT16, PTR CGL_INT16P;
typedef unsigned short   CGL_UINT16, PTR CGL_UINT16P;
typedef long             CGL_INT32, PTR CGL_INT32P;
typedef unsigned long    CGL_UINT32, PTR CGL_UINT32P;

/////////////////////////
// Fixed Point Version //
/////////////////////////

#if defined(CGLFLOAT)
typedef float         CGL_FLOAT32;
typedef CGL_FLOAT32   CGL_TYPE;
#else
typedef long          CGL_TYPE;
#endif

//////////////////////////
//  Vertices Structure  //
//////////////////////////

typedef struct CGL_VERTEX3D
{   CGL_TYPE x,y,z;
}    CGL_VERTEX3D_ST,
 PTR CGL_VERTEX3D_PST;

typedef struct CGL_VERTEX2D
{   CGL_TYPE  x,y;
}    CGL_VERTEX2D_ST,
 PTR CGL_VERTEX2D_PST;

typedef struct CGL_SPAN2D
{   CGL_TYPE  x;
}    CGL_SPAN2D_ST,
 PTR CGL_SPAN2D_PST;
          
typedef struct CGL_SPAN3D
{   CGL_TYPE x;
    CGL_TYPE z;
}    CGL_SPAN3D_ST,
 PTR CGL_SPAN3D_PST;

typedef struct CGL_TEXTURE2D
{
    CGL_TYPE s,t;
}    CGL_TEXTURE2D_ST,
 PTR CGL_TEXTURE2D_PST;

typedef struct CGL_TEXTURE3D
{
    CGL_TYPE s,t,q;
}    CGL_TEXTURE3D_ST,
 PTR CGL_TEXTURE3D_PST;

typedef struct CGL_COLOR
{
     CGL_UINT8 bBlue,bGreen,bRed,bAlpha;
}    CGL_COLOR_ST,
 PTR CGL_COLOR_PST;


typedef struct CGL_DEPTHCUE
{   CGL_TYPE d;
}    CGL_DEPTHCUE_ST,
 PTR CGL_DEPTHCUE_PST;


////////////////////////////
// Primitive Operation    //
////////////////////////////

//*************************
//  Property Enable Mask
//*************************

union CGL_PROPERTY
{
    CGL_UINT16  i;
    struct {
        unsigned shade          : 1;
        unsigned depth          : 1;
        unsigned stencil        : 1;
        unsigned blend          : 1;
        unsigned texture        : 1;
        unsigned depthcue       : 1;
        unsigned logicalOps     : 1;
        unsigned bitMask        : 1;
        unsigned stipple        : 1;
        unsigned perspective    : 1;
        unsigned reserved       : 6;
    } u;
};

//***********************
//  Primitive Property
//***********************

///////////////////////////////
// Stencil Structure         //
///////////////////////////////

typedef struct CGL_STENCIL
{
    CGL_UINT16 writeMask;
    CGL_UINT32 dwStencilRef;
     
}    CGL_STENCIL_ST,
 PTR CGL_STENCIL_PST;
                    
                    
///////////////////////////////
// Depth Structure           //
///////////////////////////////

typedef struct CGL_DEPTH
{
    CGL_UINT16 writeEnable;
    
}    CGL_DEPTH_ST,
 PTR CGL_DEPTH_PST;

///////////////////////////////
// Alpha Blending Structure  //
///////////////////////////////

typedef struct CGL_ALPHABLEND
{
     CGL_UINT8  bSrcAlphaValue;

}    CGL_ALPHABLEND_ST,
 PTR CGL_ALPHABLEND_PST;

////////////////////////////////////
// Texture Environment Structure  //
////////////////////////////////////

typedef struct CGL_TEXTUREENV
{
    CGL_UINT32     dwTextureAddress;
    CGL_UINT16     wBufferWidth;
    CGL_UINT16     wWidth;
    CGL_UINT16     wHeight;
    CGL_UINT16     wColorOrder;
    CGL_UINT16     wColorFormat;
    CGL_UINT16     wTextureMode;
    CGL_UINT16     wS_Wrap;
    CGL_UINT16     wT_Wrap;
    CGL_UINT16     wOverlay;
    CGL_UINT16     wChroma;
    CGL_COLOR_ST   stChromaColor;
    CGL_INT16      wTextureFilter;

}     CGL_TEXTUREENV_ST,
  PTR CGL_TEXTUREENV_PST;

//////////////////////////////////////////////////////

/////////////////////////
// Render Fixed Header //
/////////////////////////

typedef struct CGL_RENDERFIX
{
    CGL_UINT16           wOperation;
    CGL_UINT32           dwNoOfVertices;
    CGL_UINT16           wPrimitiveType;
    union CGL_PROPERTY   uPropertyEnableMask;
    CGL_DEPTH_PST        pDepth;
    CGL_STENCIL_PST      pStencil;
    CGL_ALPHABLEND_PST   pBlend;
    CGL_TEXTUREENV_PST   pTextureEnv;
    CGL_PTR              pVertex;
    CGL_PTR              pTexture;
    CGL_PTR              pColor;
    CGL_PTR              pDepthCue;
}     CGL_RENDERFIX_ST,
  PTR CGL_RENDERFIX_PST;


///////////////////////
// Copy Fixed Header //
///////////////////////


typedef struct CGL_COPYFIX
{
    CGL_UINT16          wOperation;
    CGL_UINT32          dwNoOfVertices;
    CGL_UINT16          wPrimitiveType;
    CGL_UINT16          wBufferMask;
    CGL_TYPE            wXSrc;
    CGL_TYPE            wYSrc;
    CGL_VERTEX2D_PST    pVertex2D;
}     CGL_COPYFIX_ST,
  PTR CGL_COPYFIX_PST;


/////////////////////////////
//  Texture Management     //
/////////////////////////////

typedef struct CGL_TEXTURELD
{
    CGL_UINT32    dwFreeByteAddress;
    CGL_UINT32    dwTextureAddress;
    CGL_UINT16    wBufferWidth;
    CGL_UINT16    wWidth;
    CGL_UINT16    wHeight;
    CGL_UINT16    wColorFormat;
    CGL_UINT32    dwMemoryLeft;
    CGL_PTR       pHostBuffer;
    
}     CGL_TEXTURELD_ST,
  PTR CGL_TEXTURELD_PST;


/////////////////////////
//  Buffer Management  //
/////////////////////////

typedef struct CGL_RECT {
    CGL_UINT16  wX;
    CGL_UINT16  wY;
    CGL_UINT16  wWidth;
    CGL_UINT16  wHeight;
}     CGL_RECT_ST,
  PTR CGL_RECT_PST;


typedef struct CGL_UPDN {
    CGL_UINT16   wBufferType;
    CGL_UINT16   wColorFormat;
    CGL_PTR      pHostBuffer;
    CGL_RECT_ST  stBox;
    CGL_UINT16   wXSrc;
    CGL_UINT16   wYSrc;
    CGL_UINT16   wBufferWidth;
    CGL_UINT16   wPixelOps;
    CGL_UINT8    bConstantAlpha;   //-- for CGL_BLEND_IMAGE only
}    CGL_UPDN_ST,
 PTR CGL_UPDN_PST;



////////////////////////////
//  Screen Management     //
////////////////////////////


typedef struct CGL_SCREEN
{                 
  CGL_UINT16 wReference;            
  CGL_UINT16 wMode;
  CGL_UINT16 wColorFormat;
  CGL_UINT16 wBuffers;
  CGL_UINT16 wOption;
  CGL_UINT32 dwUB_BufferSize;
}    CGL_SCREEN_ST,
 PTR CGL_SCREEN_PST;



                                
//////////////////////////////////
// Query Mangement              //
//////////////////////////////////

// Pick/Extent

typedef struct CGL_PICK {
    CGL_RECT_ST   stRect;
    CGL_UINT16    wStatistic;
}     CGL_PICK_ST,
 PTR  CGL_PICK_PST;
  
typedef struct CGL_EXTENT {
    CGL_UINT16    wStatistic;
}     CGL_EXTENT_ST,
 PTR  CGL_EXTENT_PST;


//  Hardware Configuration

union CGL_HARDWARE
{     CGL_UINT32 i;
      struct
      {
      unsigned Texture     : 1;
      unsigned Stipple     : 1;
      unsigned LineStipple : 1;
      unsigned DepthCue    : 1;
      unsigned Shade       : 1;
      unsigned Overlay     : 1;
      unsigned Chroma      : 1;
      unsigned Dither      : 1;
      unsigned AlphaBlend  : 1;
      unsigned Pick        : 1;
      unsigned Extent      : 1;                                   
      unsigned Bitmask     : 1;
      unsigned LogicOps    : 1;
      unsigned DepthTest   : 1;
      unsigned Clipping    : 1;
      unsigned Stencil     : 1;
      unsigned reserved    : 16;
     } u;
};

typedef struct CGL_GPCONFIG
{
   CGL_STRING          Version[80];
   CGL_UINT16          wBoard_ID;
   CGL_UINT32          dwVRAM_Size;
   CGL_UINT32          dwDRAM_Size;
   CGL_UINT16          wMaxColorFormat;
   CGL_UINT16          wCurrentMode;
   union CGL_HARDWARE  uHardwareSupport;

}     CGL_GPCONFIG_ST,
  PTR CGL_GPCONFIG_PST;

typedef void (*CGL_ISRPROC)(CGL_UINT32 ulMask);

#endif // __CGL_TYPE__

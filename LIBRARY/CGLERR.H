#ifndef __CGL_ERR__
#define __CGL_ERR__

     /*********************************************************************
     
     cglerr.h
     
     Copyright (c) Creative Technology Ltd. 1994-1995. All Rights Reserved.
     
     THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
     KIND,  EITHER EXPRESSED OR IMPLIED,  INCLUDING BUT NOT LIMITED TO THE 
     IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR 
     PURPOSE.
     
     *********************************************************************/

/*
 * @@ SOURCE DOCUMENTATION
 *
 * TITLE    : cglerr.h
 * 
 * VERSION  : 0.01
 *
 * DATE     : 1 December 1994
 *
 * AUTHOR   : Philip Teo
 *            Toh Chin Kok
 *            Burak Alp
 *
 * BRIEF    : This file includes all the error code for function
 *            calls.
 *
 * @@ LOG CHANGE
 * DATE         VERSION   REV          DESCRIPTION
 * 13 Feb 95     1.0      Philip Teo   First library version
 * 11 Mar 95     1.1      Philip Teo   Second library version
 */
                                                                     
enum {

 CGL_SUCCESS = 0,
 
/////////////////////////////////////
// Hardware Related Error          //
/////////////////////////////////////

CGL_PCI_BIOS32_NOT_FOUND,
CGL_PCI_BIOS_NOT_PRESENT,
CGL_CM_INIT_FAILED, 
CGL_GIGI_NOT_FOUND,
CGL_GIGI_NOT_INIT,                              /*5*/
CGL_GIGI_GENERAL_FAILURE,
CGL_INVALID_VENDOR_ID,
CGL_INVALID_DEVICE_ID,
CGL_INVALID_REVISION_ID,
CGL_INVALID_CLASS_CODE,                        /*10*/
CGL_SET_GIGI_CONTROL_SPACE_ADDR_FAILED, 
CGL_SET_GIGI_LOCAL_BUFFER_0_ADDR_FAILED,    
CGL_SET_GIGI_FRAME_BUFFER_0_ADDR_FAILED,     
CGL_SET_GIGI_LOCAL_BUFFER_1_ADDR_FAILED,      
CGL_SET_GIGI_FRAME_BUFFER_1_ADDR_FAILED,        /*15*/
CGL_SET_GIGI_EXPANSION_ROM_ADDR_FAILED,
CGL_SET_GIGI_COMMAND_REGISTER_FAILED,
CGL_READ_GIGI_CONTROL_SPACE_ADDR_FAILED, 
CGL_READ_GIGI_LOCAL_BUFFER_0_ADDR_FAILED,    
CGL_READ_GIGI_FRAME_BUFFER_0_ADDR_FAILED,       /*20*/
CGL_READ_GIGI_LOCAL_BUFFER_1_ADDR_FAILED,      
CGL_READ_GIGI_FRAME_BUFFER_1_ADDR_FAILED,      
CGL_READ_GIGI_COMMAND_REGISTER_FAILED,
CGL_MAP_GIGI_CONTROL_SPACE_ADDR_FAILED, 
CGL_MAP_LOCALBUFFER_FAILED,                     /*25*/
CGL_MAP_FRAMEBUFFER_FAILED,     
CGL_MAP_GIGI_EXPANSION_ROM_ADDR_FAILED,
CGL_UNKNOWN_FB_SIZE,
CGL_UNKNOWN_LB_SIZE,
CGL_SCREEN_RESOLUTION_NOT_SUPPORTED,            /*30*/
CGL_COLOR_RESOLUTION_NOT_SUPPORTED,
CGL_UNKNOWN_RAMDAC_FOUND,
CGL_MEMORY_ALLOCATION_FAILED,
CGL_INSTALL_INTERRUPT_FAILED,
CGL_INVALID_INTERRUPT_RETURN,                   /*35*/
CGL_INVALID_ERROR_INTERRUPT_RETURN, 
CGL_INITFILE_NOT_FOUND,
CGL_INVALID_PAN_WIDTH,


/////////////////
// Reserved    //
/////////////////

CGL_RESERVED                = 512,

/////////////////////////////////////
// Library Related Error           //
/////////////////////////////////////
CGL_ERR_FAILURE             = 995,
CGL_ERR_CDL_FAILURE         = 999,

CGL_UNUSED                  = 1000,
 
/////////////////////////////////////
// Primitive Operation Management  //
/////////////////////////////////////

// cglSendStream

CGL_ERR_STREAM_BEGIN_NULL,              // stream buffer pointer error
CGL_ERR_STREAM_TEXTURE_NULL,            // error in Texture Vertex
CGL_ERR_STREAM_VERTEX_NULL,             // error in Spatial Vertex
CGL_ERR_STREAM_COLOR_NULL,              // error in Color Vertex
CGL_ERR_STREAM_DEPTHCUE_NULL,           // error in DepthCue Vertex
CGL_ERR_NOT_CONFIGURE_FOR_DEPTH,        // error in Screen Configuration
CGL_ERR_NOT_CONFIGURE_FOR_STENCIL,      // error in Screen Configuration
CGL_ERR_PROPERTYMASK_TEXTUREENV_NULL,   // error in TextureEnv Structure
CGL_ERR_PROPERTYMASK_DEPTH,             // error in Depth Structure
CGL_ERR_PROPERTYMASK_STENCIL,           // error in Stencil Structure
CGL_ERR_PROPERTYMASK_BLEND,             // error in Blend Strcture
CGL_ERR_STREAM_VERTICE_NO,              // error in No of Vertices
CGL_ERR_OPERATION,                      // Invalid operation

CGL_ERR_STREAM_COPYFIX_NULL      = 1100, // null pointer for fix header
CGL_ERR_STREAM_UPLOADFIX_NULL,           // null pointer for fix header
CGL_ERR_STREAM_DOWNLOADFIX_NULL,          // null pointer for fix header
CGL_ERR_UPLOAD_PRIMITIVE_NOT_SUPPORT,    // primitive not supported
CGL_ERR_DOWNLOAD_PRIMITIVE_NOT_SUPPORT,  // primitive not supported

// cglPutPixel & cglGetPixel  (CGL_ERR_MUST_INIT_SCREEN)

// cglInitScreen

CGL_ERR_INIT_NOT_ENOUGH_MEMORY   = 1200, // Graph Memory insufficient
CGL_ERR_INIT_NOT_ENOUGH_DRAM,            // DRAM insufficient
CGL_ERR_INIT_NOT_ENOUGH_VRAM,            // VRAM insufficient
CGL_ERR_SCREEN_MODE,                     // Invalid screen mode
CGL_ERR_DEPTH_STENCIL_OPTION,            // Invalid configure option
CGL_ERR_COLOR_FORMAT,                    // Invalid color format
CGL_ERR_UNKNOWN_HARDWARE,                // Unable to init hardware

// cglSetLinePattern

CGL_ERR_SET_LINE_PATTERN          = 1300, // insufficient memory to
                                          // save the line pattern
// cglSetFillPattern

CGL_ERR_SET_FILL_PATTERN          = 1400, // insufficient memory to 
                                          // save the fill pattern
// cglSetStipplePattern
CGL_ERR_NULL_STIPPLE_PATTERN      = 1500, // null pattern array

// cglSetDepthMode

CGL_ERR_NO_DEPTH_BUFFER           = 1500, // no depth buffer 

// cglSetStencilMode

CGL_ERR_NO_STENCIL_BUFFER         = 1600, // no stencil buffer

// cglSetTextureFilter

CGL_ERR_SET_TEXTURE_FILTER        = 1700, // error in filter selection

// cglLoadTextureMap  

CGL_ERR_TEXTURE_INVAID_HOSTBUFFER   = 1800,    // Null pointer
CGL_ERR_TEXTURE_INVALID_SIZE,                  // invalid width/height
CGL_ERR_TEXTURE_INVALID_BASEADDR,              // wrong addr
CGL_ERR_TEXTURE_BASEADDR_EXCEED,               // wrong addr

// cglUpLoad

CGL_ERR_UPLOAD_INVALID_SIZE          =  1900,   // invalid buffer size
CGL_ERR_UPLOAD_HOSTBUFFER,                      // invalid host buffer
CGL_ERR_UPLOAD_STENCIL_NOT_AVAILABLE,           // no stencil buffer
CGL_ERR_UPLOAD_DEPTH_NOT_AVAILABLE,              // no depth buffer

// cglDownLoad

CGL_ERR_DOWNLOAD_INVALID_SIZE        =  2000,    // invalid buffer size
CGL_ERR_DOWNLOAD_HOSTBUFFER,                     // invalid host buffer
CGL_ERR_DOWNLOAD_STENCIL_NOT_AVAILABLE,          // no stencil buffer
CGL_ERR_DOWNLOAD_DEPTH_NOT_AVAILABLE,            // no depth buffer
CGL_ERR_DOWNLOAD_INVALID_OPERATION,              // invalid operation

// cglLockBuffer

CGL_ERR_INVALID_BUFFER_TYPE          =  2100,

// cglGetPickResult & cglGetExtentResult
                                                               
CGL_ERR_NOT_IN_PICK_MODE             =  3000,  
CGL_ERR_NOT_IN_EXTENT_MODE,
CGL_ERR_QUERY_MEMORY_NO_ENOUGH,
CGL_ERR_UNKNOWN_REVISION,
CGL_ERR_UNKNOWN_IN_HARDWARE, 
CGL_ERR_UNABLE_TO_GET_MAX_COLOR,

CGL_ERR_UNKNOWN_GLHW                 = 31999,    // Unknown Hardware Error Detected

// Common Error

CGL_ERR_MUST_INIT_SCREEN             = 32000,    // First must call cglInitScreen

};

#endif // __CGL_ERR__

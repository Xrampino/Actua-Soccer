/****************************************************************************
*
*  File              : hmixfer.h
*  Date Created      : 1/12/95
*  Description       : transfer system
*
*  Programmer(s)     : Nick Skrepetos
*  Last Modification : 1/24/95 - 9:51:39 AM
*  Additional Notes  :
*
*****************************************************************************
*            Copyright (c) 1994-5,  HMI, Inc.  All Rights Reserved          *
****************************************************************************/


#ifndef  _HMI_XFER_DEFINED
#define  _HMI_XFER_DEFINED

// set structure packing
#pragma  pack(1)

// transfer block ID types
enum
   {
      _XFER_BLOCK_DATA,                            // block of raw data
      _XFER_BLOCK_REQUEST_ID,                      // request ID direct
      _XFER_BLOCK_ID,                              // contains local target data
      _XFER_BLOCK_REQUEST_RESEND,                  // request resend of block
      _XFER_BLOCK_NAME,                            // user name
      _XFER_BLOCK_VOICE,                           // voice data
      _XFER_BLOCK_VOICE_HEADER,                    // voice header
      _XFER_BLOCK_VOICE_END,                       // end of voice chunk
   };

// communication structure
typedef  struct   _tagXFER_BLOCK_HEADER
         {

            W32     wSequence;                    // sequence ID
            W32     wType;                        // block type
            W32     wID;                          // block ID
            W32     wLength;                      // block length
            W32     wNode;                        // which node?

            W32     wUser1;                       // user area

         } _XFER_BLOCK_HEADER;

// reset structure packing
#pragma  pack()

#endif


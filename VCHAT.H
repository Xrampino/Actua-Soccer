/****************************************************************************
*
*  File              : vchat.h
*  Date Created      : 1/17/95
*  Description       : voice chat module header file
*
*  Programmer(s)     : Nick Skrepetos
*  Last Modification : 2/2/95 - 4:49:33 PM
*  Additional Notes  :
*
*****************************************************************************
*            Copyright (c) 1994,  HMI, Inc.  All Rights Reserved            *
****************************************************************************/

// function prototypes
BOOL	cdecl	hmiVCHATGetSettings        ( WORD wDeviceID, _SOS_HARDWARE * sSettings );
BOOL	cdecl	hmiVCHATPlayInit           ( WORD wDeviceID, _SOS_HARDWARE * sSettings );
BOOL	cdecl	hmiVCHATPlayEnable         ( VOID );
BOOL	cdecl	hmiVCHATPlayDisable        ( VOID );
BOOL	cdecl	hmiVCHATRecordInit         ( WORD wDeviceID, _SOS_HARDWARE * sSettings );
BOOL	cdecl	hmiVCHATRecordEnable       ( VOID );
BOOL	cdecl	hmiVCHATRecordDisable      ( VOID );
VOID  cdecl hmiVCHATModule             ( VOID );
BOOL	cdecl	hmiVCHATInitQueue          ( WORD wNode );
BOOL	cdecl	hmiVCHATQueueNextBuffer    ( WORD wNode );
PSTR	cdecl hmiVCHATQueueGetBuffer     ( WORD wNode, WORD * wSize );
PSTR	cdecl hmiVCHATQueueAddBuffer     ( WORD wNode, WORD wSize );
VOID	cdecl	_far	hmiVCHATDigitalHandler( WORD hDriver, 
                                          WORD wAction,
                                          WORD hSample );
VOID	cdecl	hmiVCHATSendData           ( WORD wNode, PSTR pData, WORD wSize );
VOID	cdecl	hmiVCHATQueueSetSize       ( WORD wNode, WORD wSize );


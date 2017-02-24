/****************************************************************************
*
*  File              : netbios.c
*  Date Created      : 1/18/95
*  Description       : NETBIOS support library header file
*
*  Programmer(s)     : Nick Skrepetos
*  Last Modification : 9/11/95 - 2:41:22 PM
*  Additional Notes  :
*
*****************************************************************************
*          Copyright (c) 1994-95,  HMI, Inc.  All Rights Reserved           *
****************************************************************************/

#ifndef  _HMI_NETBIOS_DEFINED
#define  _HMI_NETBIOS_DEFINED

// equates for interrupts used
#define  _NETBIOS_INT         0x5c

// maximum nodes supported at once
#define  _NETBIOS_MAX_NODES            _NETNOW_MAX_NODES

// broadcast command
#define  _NETBIOS_BROADCAST            _NETBIOS_MAX_NODES + 1

// maximum number of packets that can be in packet queue
#define  _NETBIOS_MAX_SEND_PACKETS     _NETNOW_MAX_SEND_PACKETS
#define  _NETBIOS_MAX_LISTEN_PACKETS   _NETNOW_MAX_LISTEN_PACKETS

// size of the packet for transmission
#define  _NETBIOS_DATA_PACKET          _NETNOW_DATA_PACKET

// offset of data 
#define  _NETBIOS_DATA_OFFSET          sizeof( _NETBIOS_NCB )

// real mode memory sizes fro sending and receiving
// datagrams.
#define  _NETBIOS_REAL_SEND_SIZE       _NETBIOS_MAX_SEND_PACKETS * \
                                       ( _NETBIOS_DATA_PACKET + _NETBIOS_DATA_OFFSET )
#define  _NETBIOS_REAL_LISTEN_SIZE     _NETBIOS_MAX_LISTEN_PACKETS * \
                                       ( _NETBIOS_DATA_PACKET + _NETBIOS_DATA_OFFSET )

// set structure packing to byte packing
#pragma  pack(1)

// protected mode pointer
typedef  struct
               {

                  PSTR     pData;            // pointer to data

               } _PROT_PTR;

// real mode pointer
typedef  struct
               {

                  SHORT    wOffset;          // address offset
                  SHORT    wSegment;         // address segment

               } _REAL_PTR;

// real/protected pointer
typedef  union
         {

            _PROT_PTR   sPointer;
            _REAL_PTR   sRealPtr;

         } _PTR;

// network control block (NCB)
typedef  struct   _tag_NETBIOS_NCB
         {

            BYTE     bCommand;               // command
            BYTE     bReturnCode;            // return code from command
            BYTE     bLocalSession;          // local session number
            BYTE     bNetworkNameNumber;     // network name number
            _PTR     sPtr;                   // pointer to buffer
            USHORT   wLength;                // length of buffer
            BYTE     bCallName[ 16 ];        // destination computer
            BYTE     bName[ 16 ];            // source computer
            BYTE     bReceiveTimeOut;        // receive time out, 500 ms increments
            BYTE     bSendTimeOut;           // send time out, 500 ms increments
            PSTR     pPostFunction;          // pointer to post function
            BYTE     bAdapter;               // adapter 0 or 1
            BYTE     bCompletionCode;        // return code ( completion )
            BYTE     bReserve[ 14 ];         // reserved for system

         } _NETBIOS_NCB;

// NetBIOS adapter status information
typedef  struct   _tagNETBIOS_ADAPTER_STATUS
         {

            BYTE     bCardID[ 6 ];                 // card id ( node addr )
            BYTE     bReleaseLevel;                // release level
            BYTE     bReserved1;                   // reserved
            BYTE     bTypeOfAdapter;               // adapter type
            BYTE     bOldOrNewParameters;          // parameters
            USHORT   wReportingPeriodMinutes;      // reporting period
            USHORT   wFrameRejectReceivedCount;    // rejected count
            USHORT   wFrameRejectSentCount;        // rejected send count
            USHORT   wReceivedDataFrameErrors;     // receive errors
            USHORT   wUnsuccessfulTransmissions;   // unsuccessful transmissions
            LONG     dwGoodTransmissions;          // good transmissions
            LONG     dwGoodReceptions;             // good receptions
            USHORT   wRetransmissions;             // retry transmissions
            USHORT   wExhaustedResourceCount;      //
            USHORT   wT1TimerExpiredCount;         //
            USHORT   wTITimerExpiredCount;         //
            BYTE     bReserved2[4];                // reserved
            USHORT   wAvailableNCBS;               //
            USHORT   wMaxNCBSConfigured;           //
            USHORT   wMaxNCBSPossible;             //
            USHORT   wBufferOrStationBusyCount;    //
            USHORT   wMaxDatagramSize;             // max datagram size
            USHORT   wPendingSessions;             //
            USHORT   wMaxSessionsConfigured;       //
            USHORT   wMaxSessionsPossible;         //
            USHORT   wMaxFrameSize;                //
            USHORT   wNameCount;                   //

            struct
                  {

                     BYTE  bName[ 16 ];            // name
                     BYTE  bNameNumber;            // name number in list
                     BYTE  bNameStatus;            // status

                  } sNameTable[ 20 ];

         } _NETBIOS_ADAPTER_STATUS;


// flags for send/listen element
#define  _NETBIOS_ELEMENT_ACTIVE     0x8000        // element is active
#define  _NETBIOS_ELEMENT_DATA       0x4000        // element has data waiting
#define  _NETBIOS_ELEMENT_LISTENING  0x2000        // element is listening for packet
#define  _NETBIOS_ELEMENT_SENDING    0x1000        // element is sending packet

// structure for send/listen elements
typedef  struct   _tagNETBIOS_ELEMENT
         {

            USHORT         wFlags;                 // misc flags
            USHORT         wOffset;                // offset into data area
            _NETBIOS_NCB   sNCB;                   // control block
            _NETBIOS_NCB * pNCB;                   // pointer to NCB
            PSTR           pHeader;                // application specific header
            USHORT         wHSize;                 // application header size

         } _NETBIOS_ELEMENT;

// address structure for NetBIOS
typedef  struct   _tagNETBIOS_LOCAL_TARGET
         {

            BYTE  bNode[ 16 ];                      // node address

         } _NETBIOS_LOCAL_TARGET;

// equates for node addition
enum
   {
      _NETBIOS_ADD_COMPLETE,
      _NETBIOS_ADD_DUPLICATE,
      _NETBIOS_ADD_LIST_FULL
   };

// equates for node deletion
enum
   {
      _NETBIOS_DELETE_COMPLETE,
      _NETBIOS_DELETE_INVALID,
   };

// equates for init error
enum
   {
      _NETBIOS_INIT_NO_ERROR,
      _NETBIOS_INIT_NO_MEMORY,
      _NETBIOS_INIT_NO_NETBIOS,
      _NETBIOS_INIT_NO_TEMPNAME
   };

// reset structure packing
#pragma  pack()

// NetBIOS commands
#define  _NETBIOS_RESET                         0x32
#define  _NETBIOS_CANCEL                        0x35
#define  _NETBIOS_STATUS                        0xb3
#define  _NETBIOS_STATUS_WAIT                   0x33
#define  _NETBIOS_UNLINK                        0x70
#define  _NETBIOS_ADD_NAME                      0xb0
#define  _NETBIOS_ADD_NAME_WAIT                 0x30
#define  _NETBIOS_ADD_GROUP_NAME                0xb6
#define  _NETBIOS_ADD_GROUP_NAME_WAIT           0x36
#define  _NETBIOS_DELETE_NAME                   0xb1
#define  _NETBIOS_DELETE_NAME_WAIT              0x31
#define  _NETBIOS_CALL                          0x90
#define  _NETBIOS_CALL_WAIT                     0x10
#define  _NETBIOS_LISTEN                        0x91
#define  _NETBIOS_LISTEN_WAIT                   0x11
#define  _NETBIOS_HANG_UP                       0x92
#define  _NETBIOS_HANG_UP_WAIT                  0x12
#define  _NETBIOS_SEND                          0x94
#define  _NETBIOS_SEND_WAIT                     0x14
#define  _NETBIOS_SEND_NO_ACK                   0xf1
#define  _NETBIOS_SEND_NO_ACK_WAIT              0x71
#define  _NETBIOS_CHAIN_SEND                    0x97
#define  _NETBIOS_CHAIN_SEND_WAIT               0x17
#define  _NETBIOS_CHAIN_SEND_NO_ACK             0xf2
#define  _NETBIOS_CHAIN_SEND_NO_ACK_W           0x72
#define  _NETBIOS_RECEIVE                       0x95
#define  _NETBIOS_RECEIVE_WAIT                  0x15
#define  _NETBIOS_RECEIVE_ANY                   0x96
#define  _NETBIOS_RECEIVE_ANY_WAIT              0x16
#define  _NETBIOS_SESSION_STATUS                0xb4
#define  _NETBIOS_SESSION_STATUS_WAIT           0x34
#define  _NETBIOS_SEND_DATAGRAM                 0xa0
#define  _NETBIOS_SEND_DATAGRAM_WAIT            0x20
#define  _NETBIOS_SEND_BROADCAST_DATAGRAM       0xa2
#define  _NETBIOS_SEND_BROADCAST_DATAGRAM_W     0x22
#define  _NETBIOS_RECEIVE_DATAGRAM              0xa1
#define  _NETBIOS_RECEIVE_DATAGRAM_WAIT         0x21
#define  _NETBIOS_RECEIVE_BROADCAST_DATAGRAM    0xa3
#define  _NETBIOS_RECEIVE_BROADCAST_DATAGRAM_W  0x23

#endif

// function prototypes
BOOL	cdecl	hmiNETBIOSInitSystem             ( W32 wNodes );
BOOL  cdecl hmiNETBIOSUnInitSystem           ( VOID );
W32	cdecl hmiNETBIOSGetActiveNodes         ( VOID );
BOOL	cdecl hmiNETBIOSPostListen             ( VOID );
BOOL	cdecl hmiNETBIOSInstalled              ( VOID );
BOOL	cdecl	hmiNETBIOSAddName                ( PSTR szName );
BOOL	cdecl	hmiNETBIOSDeleteName             ( PSTR szName );
BOOL	cdecl	hmiNETBIOSGetAdapterStatus       ( VOID );
VOID	cdecl hmiNETBIOSSortNodes              ( VOID );
W32	cdecl hmiNETBIOSGetConsoleNode         ( VOID );
VOID	cdecl hmiNETBIOSListenForPacket        ( _NETBIOS_NCB *  sNCB,
                                               _NETBIOS_NCB ** pPacket );
VOID	cdecl hmiNETBIOSSendPacket             ( _NETBIOS_NCB *  sNCB,
                                               _NETBIOS_NCB ** pPacket, 
                                               PSTR  pHeader, 
                                               W32  wSize  );
BOOL	cdecl hmiNETBIOSSendData               ( PSTR pHeader, W32 wHSize, 
                                               PSTR pData,   W32 wDSize,
                                               W32 wNode );
BOOL	cdecl hmiNETBIOSGetData                ( PSTR pHeader,  W32 wHSize, 
                                               PSTR pData,    W32 wDSize );
BOOL	cdecl	hmiNETBIOSCancelAll              ( VOID );
BOOL	cdecl hmiNETBIOSGetHeader              ( PSTR pHeader,   W32 wHSize, 
                                               PSTR * pPacket );
W32	cdecl hmiNETBIOSDeleteNode             ( W32 wNode );


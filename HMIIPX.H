/****************************************************************************
*
*  File              : hmiipx.h
*  Date Created      : 12/21/94
*  Description       : ipx header information including data structures
*
*  Programmer(s)     : Nick Skrepetos
*  Last Modification : 9/15/95 - 10:1:15 AM
*  Additional Notes  :
*
*****************************************************************************
*           Copyright (c) 1994-95,  HMI, Inc.  All Rights Reserved          *
****************************************************************************/

#ifndef  _HMI_IPX_DEFINED
#define  _HMI_IPX_DEFINED

// equates
#define  _IPX_INT                0x7a

// maximum number of nodes to support at once
#define  _IPX_MAX_NODES          _NETNOW_MAX_NODES

// broadcast command
#define  _IPX_BROADCAST          _IPX_MAX_NODES + 1

// maximum number of packets that can be in packet queue
#define  _IPX_MAX_SEND_PACKETS   _NETNOW_MAX_SEND_PACKETS
#define  _IPX_MAX_LISTEN_PACKETS _NETNOW_MAX_LISTEN_PACKETS

// size of the packet for transmission
#define  _IPX_DATA_PACKET        _NETNOW_DATA_PACKET

// socket number for our use
#define  _IPX_SOCKET             0x4545

// offset for ipx header from start of ECB area
#define  _IPX_HEADER_OFFSET      sizeof( _IPX_ECB )

// offset for ipx data packet 
#define  _IPX_DATA_OFFSET        _IPX_HEADER_OFFSET + sizeof( _IPX_HEADER )

// real mode memory sizes for sending and receiving
// packets.
#define  _IPX_REAL_SEND_SIZE     _IPX_MAX_SEND_PACKETS * \
                                 ( _IPX_DATA_PACKET + _IPX_DATA_OFFSET )
#define  _IPX_REAL_LISTEN_SIZE   _IPX_MAX_LISTEN_PACKETS * \
                                 ( _IPX_DATA_PACKET + _IPX_DATA_OFFSET )

// ipx commands
#define  _IPX_OPEN_SOCKET              0x00
#define  _IPX_CLOSE_SOCKET             0x01
#define  _IPX_GET_LOCAL_TARGET         0x02
#define  _IPX_SEND_PACKET              0x03
#define  _IPX_LISTEN_FOR_PACKET        0x04
#define  _IPX_SCHEDULE_IPX_EVENT       0x05
#define  _IPX_CANCEL_EVENT             0x06
#define  _IPX_GET_INTERVAL_MARKER      0x08
#define  _IPX_GET_INTERWORK_ADDRESS    0x09
#define  _IPX_RELINQUISH_CONTROL       0x0a
#define  _IPX_DISCONNECT_FROM_TARGET   0x0b

// ipx packet types
#define  _IPX_PACKET_UNKNOWN           0x00
#define  _IPX_PACKET_ROUTING_INFO      0x01
#define  _IPX_PACKET_ECHO              0x02
#define  _IPX_PACKET_ERROR             0x03
#define  _IPX_PACKET_IPX               0x04
#define  _IPX_PACKET_SPX               0x05

// socket types
#define  _IPX_SOCKET_DYNAMIC           0x00
#define  _IPX_SOCKET_SHORT_LIVED       0x00
#define  _IPX_SOCKET_LONG_LIVED        0xff

// set structure packing to byte packing
#pragma  pack(1)

// ipx header structure
typedef  struct   _tagIPX_HEADER
         {

            USHORT   wChecksum;                 // checksum, 0xffff
            USHORT   wLength;                   // length
            BYTE     bTransportControl;         // 
            BYTE     bPacketType;               // usually type _IPX_PACKET_IPX
            BYTE     bDestNetworkNumber[ 4 ];   // destination network
            BYTE     bDestNetworkNode[ 6 ];     // destination node
            USHORT   wDestNetworkSocket;        // destination socket
            BYTE     bSourceNetworkNumber[ 4 ]; // source network
            BYTE     bSourceNetworkNode[ 6 ];   // source node
            USHORT   wSourceNetworkSocket;      // source socket

         } _IPX_HEADER;

// packet header for protected mode
typedef  struct   
               {

                  PSTR     pData;            // pointer to data
                  USHORT   wLength;          // length of packet

               } _PACKET;

// real mode packet structure
typedef  struct   
               {

                  SHORT    wOffset;          // address of header
                  SHORT    wSegment;         // address of header
                  USHORT   wLength;          // length of packet

               } _REAL_PACKET;

// packet information
typedef  union
      {

         _PACKET        sPacket;             // protected mode version
         _REAL_PACKET   sRealPacket;         // real mode version

      }  _ECB_PACKET;

// ECB structure
typedef  struct   _tagIPX_ECB
         {

            PSTR     pLinkAddress;              // link address
            PSTR     pESRRoutine;               // ESR service routine

            BYTE     bInUse;                    // in use flag
            BYTE     bCompletionCode;           // completion code

            USHORT   wSocket;                   // socket
            USHORT   wConnectionID;             // returned by listen

            USHORT   wWorkSpace;                // temp work space
            BYTE     bDriverWorkSpace[ 12 ];    // temp work space for driver

            BYTE     bImmediateAddress[ 6 ];    // address

            USHORT   wPacketCount;              // number of packets

            _ECB_PACKET sPacket[ 2 ];           // packets 386/real

         }  _IPX_ECB;

// internet address
typedef  struct   _tagIPX_INTERNET_ADDR
         {

            BYTE     bNetwork[ 4 ];             // network address
            BYTE     bNode[ 6 ];                // node address

         } _IPX_INTERNET_ADDR;

// network address
typedef  struct   _tagIPX_NETWORK_ADDR
         {

            _IPX_INTERNET_ADDR   sInternetAddr; // internet address
            BYTE                 bSocket[ 2 ];  // socket

         } _IPX_NETWORK_ADDR;

// local target immediate address
typedef  struct   _tagIPX_LOCAL_TARGET
         {

            _IPX_INTERNET_ADDR   sInternetAddr;    // internet address
            BYTE                 bImmediate[ 6 ];  // immediate address

         } _IPX_LOCAL_TARGET;

// flags for send/listen element
#define  _IPX_ELEMENT_ACTIVE     0x8000            // element is active
#define  _IPX_ELEMENT_DATA       0x4000            // element has data waiting
#define  _IPX_ELEMENT_LISTENING  0x2000            // element is listening for packet
#define  _IPX_ELEMENT_SENDING    0x1000            // element is sending packet

// structure for send/listen elements
typedef  struct   _tagIPX_ELEMENT
         {

            USHORT         wFlags;                 // misc flags
            USHORT         wOffset;                // offset into data area
            _IPX_HEADER    sHeader;                // IPX header
            _IPX_ECB       sECB;                   // IPX ECB
            _IPX_ECB *     pECB;                   // pointer to ECB
            _IPX_HEADER *  pIPXHeader;             // pointer to IPX header
            PSTR           pHeader;                // application specific header
            USHORT         wHSize;                 // application header size

         } _IPX_ELEMENT;

// equates for node addition
enum
   {
      _IPX_ADD_COMPLETE,
      _IPX_ADD_DUPLICATE,
      _IPX_ADD_LIST_FULL
   };

// equates for node deletion
enum
   {
      _IPX_DELETE_COMPLETE,
      _IPX_DELETE_INVALID,
   };

// equates for init error
enum
   {
      _IPX_INIT_NO_ERROR,
      _IPX_INIT_NO_MEMORY,
      _IPX_INIT_NO_IPX,
      _IPX_INIT_NO_SOCKET
   };

// reset structure packing
#pragma  pack()

#endif

// function prototypes
BOOL	cdecl hmiIPXInitSystem           ( W32 wNodes, W32 wSocket );
BOOL	cdecl hmiIPXUnInitSystem         ( VOID );
BOOL	cdecl hmiIPXInstalled            ( VOID );
BOOL	cdecl hmiIPXOpenSocket           ( W32	wSocket );
BOOL	cdecl hmiIPXCloseSocket          ( W32	wSocket );
VOID	cdecl hmiIPXRelinquishControl    ( VOID );
VOID	cdecl hmiIPXListenForPacket      ( _IPX_ECB * sECB, _IPX_ECB ** pPacket );
VOID	cdecl hmiIPXSendPacket           ( _IPX_ECB * sECB, _IPX_ECB ** pPacket, PSTR pHeader, W32 wSize  );
VOID	cdecl hmiIPXGetInternetworkAddr  ( _IPX_INTERNET_ADDR * sInterworkAddr );
VOID	cdecl hmiIPXGetLocalTarget       ( _IPX_LOCAL_TARGET * sNetworkAddr );
BOOL	cdecl hmiIPXSendData             ( PSTR pHeader, W32 wHSize,
                                         PSTR pData,   W32 wDSize,
                                         W32 wNode );
BOOL	cdecl hmiIPXGetData              ( PSTR pHeader, W32 wHSize,
                                         PSTR pData,   W32 wDSize );
BOOL	cdecl hmiIPXPostListen           ( VOID );
W32	cdecl hmiIPXServiceSend          ( VOID );
VOID	cdecl hmiIPXGetListenData        ( _IPX_ECB * sECB, PSTR pHeader, W32 wSize );
VOID	cdecl hmiIPXSortNodes            ( VOID );
W32	cdecl hmiIPXGetConsoleNode       ( VOID );
W32	cdecl hmiIPXGetActiveNodes       ( VOID );
BOOL	cdecl hmiIPXGetHeader            (  PSTR pHeader,     W32 wHSize, 
                                          PSTR * pPacket );

W32	cdecl hmiIPXDeleteNode           ( W32 wNode );

/****************************************************************************
*
*  File              : test.c
*  Date Created      : 1/3/95
*  Description       : sample code for the NetNOW! system
*
*  Programmer(s)     : Nick Skrepetos
*  Last Modification : 3/22/95 - 8:28:16 AM
*  Additional Notes  :
*
*****************************************************************************
*            Copyright (c) 1994,  HMI, Inc.  All Rights Reserved            *
****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hmistd.h"
#include "netnow.h"
#include "vdata.h"
#include "vchat.h"

// local functions
VOID	hmiNetworkDemo          ( VOID );

/****************************************************************************
*
*  Syntax
*
*     VOID	main( WORD wArgc, PSTR szArgv[] )
*
*  Description
*
*        main function for testing ipx drivers
*
*  Parameters
*
*        Type           Description
*        --------------------------
*        wArgc          Arguement count
*        szArgv         Arguements
*
*  Return
*
*     nothing
*
****************************************************************************/
VOID	main( WORD wArgc, PSTR szArgv[] )
	{
      // read the .ini file
      if ( !hmiVCHATInit() )
      {
         // print error
         printf( "ERROR: Could not read NETNOW.INI\n" );

         // exit
         exit( 1 );
      }

      // display message
      printf( "NetNOW! system initialization started.\n" );

      // check if NetNOW! is present
      if ( hmiNETNOWInitSystem( 8 ) != _NETNOW_NO_ERROR )
      {
         // print error
         printf( "ERROR: NetNOW! could not locate IPX or NetBIOS!\n" );

         // error
         exit( 1 );
      }

      // display
      printf( "\nNetNOW! system initialized!\n\n" );

      // check for information display
      if ( wNETInfoFlag )
         switch( hmiNETNOWGetNetworkType() )
         {
            case  _NETNOW_IPX    :
                                    // display type
                                    printf( "Network is using a IPX based protocol.\n" );
                                    break;
            case  _NETNOW_NETBIOS:
                                    // display type
                                    printf( "Network is using a NetBIOS based protocol.\n" );
                                    break;
         }

      // find nodes
      printf( "\nAttempting to Locate %d Nodes.\n", wNETNodes );

      // find the requested nodes
      if ( hmiNETNOWFindNodes( wNETNodes ) )
         printf( "\n\nLocated all requested nodes!\n" );
      else
      {
         printf( "\n\nERROR: could not locate the requested nodes.\n" );
      }

      // network demo
      hmiNetworkDemo();

      // uninit system
      hmiNETNOWUnInitSystem();
	}

/****************************************************************************
*
*  Syntax
*
*     VOID	hmiNetworkDemo( VOID )
*
*  Description
*
*     simple example of sending messages from one machine to another
*
*  Parameters
*
*     none
*
*  Return
*
*     nothing
*
****************************************************************************/
VOID	hmiNetworkDemo( VOID )
	{
      WORD                 wExitFlag;
      PSTR                 pPacket;
      WORD                 wActiveNodes;
      WORD                 wConsoleNode;
      _XFER_BLOCK_HEADER   sBlock;
      BYTE                 szMessage[ 128 ];

      // initialize exit flag
      wExitFlag      =  _FALSE;

      // get active nodes
      wActiveNodes   =  hmiNETNOWGetActiveNodes();

      // get console node
      wConsoleNode   =  hmiNETNOWGetConsoleNode();

      // display banner
      printf( "\n\n*********  NetNOW! Demonstration *********\n\n" );

      // display console node
      printf( "Number of Active Nodes       : %d\n", wActiveNodes );
      printf( "Node Number of this Computer : %d\n", wConsoleNode );

      // display message
      printf( "\n(S)end to station, (Q)uit\n" );

      // wait for exit flag
      while( !wExitFlag )
      {
         // check if we have data
         if ( hmiNETNOWGetHeader( (PSTR)&sBlock, sizeof( _XFER_BLOCK_HEADER ), &pPacket ) )
         {
            // check header type
            switch( sBlock.wType )
            {
               case  _XFER_BLOCK_DATA  :
                                          // get data block
                                          hmiNETNOWGetBlock( pPacket, szMessage, sBlock.wLength );

                                          // print message
                                          printf( "%s\n", szMessage );
                                          break;
            }

            // post listen
            hmiNETNOWPostListen();
         }

         // check for key press
         if ( kbhit() )
            switch( tolower( getch() ) )
            {
               case  's'   :
                              // set up header type
                              sBlock.wType   =  _XFER_BLOCK_DATA;

                              // display
                              printf( "Enter Message : \n" );

                              // get message
                              gets( szMessage );

                              // set block length
                              sBlock.wLength =  strlen( szMessage ) + 1;

                              // send data
                              while( !hmiNETNOWSendData( (PSTR)&sBlock, sizeof( _XFER_BLOCK_HEADER ), (PSTR)szMessage,
                                      sBlock.wLength, wConsoleNode ^ 0x01 ) );
                              break;
               case  'q'   :
                              // set exit flag
                              wExitFlag   =  _TRUE;
                              break;
            }
      }
		
	}



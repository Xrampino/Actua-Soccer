#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "defines.h"
#include "data.equ"
#include "3deng.h"
#include "intronet.h"
#include "sos.h"
#include "audio.h"
#include "digi.h"
#include "midi.h"
#include "config.h"
#include "timer.h"
#include "mallocx.h"
#include "unmangle.h"
#include "gamedata.h"

#include "eurodefs.h"
#include "euro_fxd.h"
#include "mallocx.h"
#include "euro_sym.h"
#include "euro_def.h"
#include "euro_var.h"
#include "euro_dsk.h"
#include "euro_grf.h"

void	EuroHelp();

//********************************************************************************************************************************

void	ProcessCommandLine(int argc, char **argv)
	{
		char	command[127];
		char	setting[127];
		signed char CommandLineTEAM;
		EUROverbose	= 	0;
		EUROconsole	= 	0;
		EUROcommOVERIDE	=	128;
		
		for (int i=1; i<argc; i++)
// Inputs...
		{
			strcpy( command, argv[i] );
			strupr( command );			

			if ( i < (argc-1) )			
			{
				strcpy( setting, argv[i+1] );
				strupr( setting );			
				setting[3] = 0;			
				CommandLineTEAM  =   -1;
			
				if (!strcmp( setting, "BUL"))
					CommandLineTEAM = Bulgaria;				
				if (!strcmp( setting, "CRO"))
					CommandLineTEAM = Croatia;				
				if (!strcmp( setting, "CZE"))
					CommandLineTEAM = Czech;				
				if (!strcmp( setting, "DEN"))
					CommandLineTEAM = Denmark;				
				if (!strcmp( setting, "ENG"))
					CommandLineTEAM = England;				
				if (!strcmp( setting, "FRA"))
					CommandLineTEAM = France;				
				if (!strcmp( setting, "GER"))
					CommandLineTEAM = Germany;				
				if (!strcmp( setting, "HOL"))
					CommandLineTEAM = Holland;				
				if (!strcmp( setting, "ITA"))
					CommandLineTEAM = Italy;				
				if (!strcmp( setting, "POR"))
					CommandLineTEAM = Portugal;				
				if (!strcmp( setting, "ROM"))
					CommandLineTEAM = Romania;				
				if (!strcmp( setting, "RUS"))
					CommandLineTEAM = Russia;				
				if (!strcmp( setting, "SCO"))
					CommandLineTEAM = Scotland;				
				if (!strcmp( setting, "SPA"))
					CommandLineTEAM = Spain;				
				if (!strcmp( setting, "SWI"))
					CommandLineTEAM = Switzerland;				
				if (!strcmp( setting, "TUR"))
					CommandLineTEAM = Turkey;				
			}
			
			//ษอออออออออออออออออออออออออออป 
			//บ                           บ
			//บ     WIREPLAY COMMANDS     บ
			//บ                           บ
			//ศอออออออออออออออออออออออออออผ 

			if (!strcmp( command, "-WIREPLAY"))
			{
				printf	("þ Attempting WIREPLAY game.\n");
				EUROgameType	=	EURO_wireplay;
  			}

			if (!strcmp( command, "-NETWORK"))
			{
				printf	("þ Attempting NETWORK game.\n");
				EUROgameType	=	EURO_network_game;
  			}

			if (!strcmp( command, "-FRIENDLY"))
			{
				printf	("þ Attempting FRIENDLY game.\n");
				EUROgameType	=	EURO_friendly;
  			}

			if ( EUROgameType == EURO_wireplay )
			{
				if (!strcmp( command, "-HOME"))
				{
				 	if ( CommandLineTEAM != -1 )
						EUROteamA = CommandLineTEAM;
				}					

				if (!strcmp( command, "-AWAY"))
				{
				 	if ( CommandLineTEAM != -1 )
						EUROteamB = CommandLineTEAM;
				}					
			}

			//ษอออออออออออออออออออออออออออป 
			//บ                           บ
			//บ      GENERAL COMMANDS     บ
			//บ                           บ
			//ศอออออออออออออออออออออออออออผ 

			if (!strcmp( command, "-1PLAYER"))
				EUROnoOfMatchPlyrs = 1;
			if (!strcmp( command, "-2PLAYERS"))
				EUROnoOfMatchPlyrs = 2;
			if (!strcmp( command, "-3PLAYERS"))
				EUROnoOfMatchPlyrs = 3;
			if (!strcmp( command, "-4PLAYERS"))
				EUROnoOfMatchPlyrs = 4;

			if ( EUROgameType == EURO_championship )
			{
				if (!strcmp( command, "-5PLAYER"))
					EUROnoOfMatchPlyrs = 5;
				if (!strcmp( command, "-6PLAYERS"))
					EUROnoOfMatchPlyrs = 6;
				if (!strcmp( command, "-7PLAYERS"))
					EUROnoOfMatchPlyrs = 7;
				if (!strcmp( command, "-8PLAYERS"))
					EUROnoOfMatchPlyrs = 8;
				if (!strcmp( command, "-9PLAYER"))
					EUROnoOfMatchPlyrs = 9;
				if (!strcmp( command, "-10PLAYERS"))
					EUROnoOfMatchPlyrs = 10;
				if (!strcmp( command, "-11PLAYERS"))
					EUROnoOfMatchPlyrs = 11;
				if (!strcmp( command, "-12PLAYERS"))
					EUROnoOfMatchPlyrs = 12;
				if (!strcmp( command, "-13PLAYER"))
					EUROnoOfMatchPlyrs = 13;
				if (!strcmp( command, "-14PLAYERS"))
					EUROnoOfMatchPlyrs = 14;
				if (!strcmp( command, "-15PLAYERS"))
					EUROnoOfMatchPlyrs = 15;
				if (!strcmp( command, "-16PLAYERS"))
					EUROnoOfMatchPlyrs = 16;
			}			

			if (!strcmp( command, "-GROUPS"))
				Menu = GROUP_FIXTURES;
			if (!strcmp( command, "-WEMBLEY"))
				Menu = VENUE_FLYTHRU;
			if (!strcmp( command, "-MODEM"))
				Menu = MODEM_SETUP;
			if (!strcmp( command, "-SYMBOLS"))
				EUROsymbol	= 	1;
			if (!strcmp( command, "-V1"))
				EUROverbose	= 	1;
			if (!strcmp( command, "-CONSOLE"))
				EUROconsole	= 	1;

			if (!strcmp( command, "-COMMTYPE0"))
				EUROcommOVERIDE	=	0;
			if (!strcmp( command, "-COMMTYPE1"))
				EUROcommOVERIDE	=	1;
			if (!strcmp( command, "-COMMTYPE2"))
				EUROcommOVERIDE	=	2;
			if (!strcmp( command, "-COMMTYPE3"))
				EUROcommOVERIDE	=	3;
			
			if (!strcmp( command, "?"))
				EuroHelp();
		}

		setup.verbose		=	EUROverbose;

		if ( EUROverbose != 0 )
		{
			printf	("þ Outputting VERBOSE information.\n");
		}
	}

//********************************************************************************************************************************

void	EuroHelp()
	{

	printf	("  -friendly			Defaults to friendly game on execution.\n");
	printf	("  -network			Defaults to network game on execution.\n\n");
	printf	("  -wireplay			Defaults to wireplay game on execution.\n");

	}

//********************************************************************************************************************************

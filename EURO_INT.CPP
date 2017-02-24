#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "eurodefs.h"
#include "euro_sym.h"
#include "euro_def.h"
#include "euro_int.h"
#include "euro_mem.h"
#include "euro_dsk.h"
#include "euro_spt.h"

		//ษอออออออออออออออออออป 
		//บ                   บ
		//บ EURO 96 LINK DATA บ
		//บ                   บ
		//ศอออออออออออออออออออผ 

interface_data	EUROmatch_info;

extern	char	EUROsymbol;
extern	BYTE	*TextStringMemHandle;
extern	void	Euro96initialise();
extern	char 	EUROteamA, EUROteamB;
extern	void	TransferDataToMatchInfo();



void	TempFrontend()
	{
		EUROsymbol = 1;
		TextStringMemHandle	=	0;
		TextStringMemHandle  =					// Set up memory handle.
			AllocateTextStringMemory();			// Allocate memory for text strings..

		printf	("þ %d Bytes allocated for script file text.\n", TEXT_STRING_BUFFER_LEN);
		fflush(stdout);

		if ( EUROsymbol == 1 )
		{
			printf	("þ Symbol creation flag set.\n");

					
			fp2=fopen( "euro_sym.h", "wb" );
				if(fp2==NULL)
				{
					EUROsymbol = 0;
					printf	("þ Error trying to create symbol table.\n");
					fflush(stdout);
				}
		}

		process_script_file("..\\script\\script.96");		// Reads script file and compiles relevent data for game.

		if ( EUROsymbol == 1 )
		{
			fclose(fp2);						
		 	printf	("þ Symbol table created.\n");
			fflush(stdout);
		}				

		Euro96initialise();


	// additions for laurent.

		strcpy( &EUROmatch_info.TeamAname[0], GetTEAMname( 0, 11) );
		strcpy( &EUROmatch_info.TeamBname[0], GetTEAMname( 1, 11) );
		for ( char t=0; t < 16; t++ )						// Reset all squads, making team
		{for ( char p=0; p < 20; p++ ){SquadInfo[ (t*20)+p ] = p;}}		// lists run from plyr 1 to 20.

		TransferDataToMatchInfo();

	// ------------------------------------
	}

void	ExitFrontend()
	{
		DeAllocateMemory(TextStringMemHandle);
	}




//********************************************************************************************************************************

void	TransferDataToMatchInfo()
	{
		short	PlyrIndex1, PlyrIndex2;		

			for (char p=0; p<20; p++)
			{		
				PlyrIndex1 = NormalisePlayer( p, EUROteamA );
				PlyrIndex2 = NormalisePlayer( p, EUROteamB );
				
				EUROmatch_info.TeamA[p].pace	   	=	Pace[ PlyrIndex1 ];
				EUROmatch_info.TeamA[p].power	   	=	Power[ PlyrIndex1 ];
				EUROmatch_info.TeamA[p].control	   	=	Control[ PlyrIndex1 ];
				EUROmatch_info.TeamA[p].flair	   	=	Flair[ PlyrIndex1 ];
				EUROmatch_info.TeamA[p].vision	   	=	Vision[ PlyrIndex1 ];
				EUROmatch_info.TeamA[p].accuracy   	=	Accuracy[ PlyrIndex1 ];
				EUROmatch_info.TeamA[p].stamina   	=	Stamina[ PlyrIndex1 ];
				EUROmatch_info.TeamA[p].discipline 	=	Discipline[ PlyrIndex1 ];
				EUROmatch_info.TeamA[p].fitness 	=	Fitness[ PlyrIndex1 ];

				EUROmatch_info.TeamB[p].pace		=	Pace[ PlyrIndex2 ];
				EUROmatch_info.TeamB[p].power		=	Power[ PlyrIndex2 ];
				EUROmatch_info.TeamB[p].control		=	Control[ PlyrIndex2 ];
				EUROmatch_info.TeamB[p].flair		=	Flair[ PlyrIndex2 ];
				EUROmatch_info.TeamB[p].vision		=	Vision[ PlyrIndex2 ];
				EUROmatch_info.TeamB[p].accuracy	=	Accuracy[ PlyrIndex2 ];
				EUROmatch_info.TeamB[p].stamina  	=	Stamina[ PlyrIndex2 ];
				EUROmatch_info.TeamB[p].discipline 	=	Discipline[ PlyrIndex2 ];
				EUROmatch_info.TeamB[p].fitness 	=	Fitness[ PlyrIndex2 ];
			}

		}

//********************************************************************************************************************************

short	NormalisePlayer( char plyr, char team )
	{
		short	PlyrIndex, P;
		P	  =	(team*20)+plyr;
		PlyrIndex =	(team*20)+SquadInfo[ P ];
		return(PlyrIndex);
	}

//********************************************************************************************************************************

char	*GetTEXT( short StringNumber )
{
	return( (char *)Text[ StringNumber ] );
}

//********************************************************************************************************************************

char	*GetPLAYERSname( char player, char team, char format )
	{
		short	Prefix		=	(team*20)+player;
		char	*Search		=	GetTEXT( PLYR_NMES+Prefix );
		char	NAMEoffset	=	0;
		char	Searchlen	=	strlen(&Search[0]);
		unsigned char 	c;
		
		if ( format == FULL_NAME )
		{	
			for ( char x=0; x < Searchlen ; x++ )
				{StringBuffer[x]	= *(Search+x);}
			StringBuffer[x]	= 0;
		}


		if ( format == INITIAL_SURNAME )
		{	
			// *** Get players initials ***
		
			for ( char x=0; x < Searchlen ; x++ )
				{
					if ( IsUpper[ *(Search+x) ] == up && 
					     IsUpper[ *(Search+(x+1)) ] == lw && 
						NAMEoffset < (NAME_BUFFER_LEN-3) ) 
					{
						StringBuffer[NAMEoffset] 	= *(Search+x);
						NAMEoffset++;
		
						if ((*(Search+x))=='-')
							StringBuffer[NAMEoffset] 	= '-';
						else									
							StringBuffer[NAMEoffset] 	= '.';
		
						StringBuffer[NAMEoffset+1] 	= 32;
						NAMEoffset+=	2;
					}
		
					if ((*(Search+x))=='-' && NAMEoffset >1 )
					{
			      			StringBuffer[NAMEoffset-2] 	= '-';
			      			NAMEoffset--;
					}
				}	
		}
		
		if ( format == INITIAL_SURNAME || format == SURNAME )
		{	
		
			// *** Get players surname ***
		
			for ( char y=0; y < Searchlen ; y++ )
				{
					if ( IsUpper[ *(Search+y) ] == up && 
					     IsUpper[ *(Search+(y+1)) ] == up && 
						NAMEoffset < (NAME_BUFFER_LEN-3) ) 

					{
						StringBuffer[NAMEoffset] 	= *(Search+y);
		
//						if ( (IsUpper[ *(Search+(y-1) ) ] == up && y>0) && 
//						     NamePREFIXtbl[Prefix] == 1 &&
//						     ( (StringBuffer[NAMEoffset-1]!='c' || 
//							StringBuffer[NAMEoffset-2]!='M' && NAMEoffset>1 ) ) )
//							{								
//								c = StringBuffer[NAMEoffset];
//								StringBuffer[NAMEoffset] = ToLower[c];
//							}



						if ( (IsUpper[ *(Search+(y-1) ) ] == up && y>0) )
						{
							c = StringBuffer[NAMEoffset];

							if ( ( StringBuffer[NAMEoffset-2]=='M' &&
							       StringBuffer[NAMEoffset-1]=='c' && 
							       NAMEoffset>1 && NamePREFIXtbl[Prefix] == 1 )
							   )

								c = StringBuffer[NAMEoffset];

							else

							   {								
								c = StringBuffer[NAMEoffset];
								StringBuffer[NAMEoffset] = ToLower[c];
							   }

						}
						
						NAMEoffset++;
					}
		
					else
					
						if ( IsUpper[ *(Search+y) ] == up && 
						     IsUpper[ *(Search+(y-1)) ] == up && 
							NAMEoffset < (NAME_BUFFER_LEN-3) && y>0 ) 
						{
							StringBuffer[NAMEoffset] 	= *(Search+y);
		
							if ( IsUpper[ *(Search+(y-1)) ] == up && y>0 )
							{								
								c = StringBuffer[NAMEoffset];
								StringBuffer[NAMEoffset] = ToLower[c];
							}
		
							NAMEoffset++;
					
				    			if ( (*(Search+(y+1)))==' ')
								{
									StringBuffer[NAMEoffset] 	= 32;
									NAMEoffset++;
								}
						}
				}	

			StringBuffer[NAMEoffset]	=	0;	// end of line.
		}

		return	( &StringBuffer[0] );
	}

//********************************************************************************************************************************

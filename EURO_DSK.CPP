#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "eurodefs.h"
#include "euro_fxd.h"
#include "mallocx.h"
#include "euro_sym.h"
#include "euro_def.h"
#include "euro_var.h"
#include "euro.equ"


	FILE 		*fp2;			// symbol creation file.

//********************************************************************************************************************************

signed int ReadLine( FILE *fp, char *buf )
	{
	signed char c;
	buf[0]	= 0;
	int nc = 0;

	while( (( (c=fgetc(fp)) !=LF)&&(c!=EOF)))
		{

		if (c==EOF || c==LF || c==255)
			*(buf++)=0;
		else
			{
				*(buf++)=c;
				nc++;
			}
		}
		if(c==EOF) nc=-1;
		return(nc);
	}

//********************************************************************************************************************************

void	ReadDataOffsetFile( char *filename )
	{
	FILE *fp1;

	fp1=fopen( filename, "rb" );

	if ( fp1 != NULL )
		{
			fread( Offset_table, sizeof(BYTE), 512*4, fp1 );
			fclose(fp1);
		      	printf("þ Data Offset file loaded.\n");
		}
	else
	       	printf("þ Error loading Data Offset file.\n");
	}


//********************************************************************************************************************************

void	ReadData( int file, char *filename, BYTE *buffer )
	{
		long	seek_pos, file_size, len;
		FILE	*fd;
		fd = fopen( filename, "rb" );

		if(fd!=NULL)
		{
			seek_pos	=	Offset_table[file/8].offset;
			file_size	=	Offset_table[file/8].size;
			fseek( fd, seek_pos , SEEK_SET );	
			fread( buffer, sizeof(BYTE), file_size, fd );
		}	
		else
		       	printf("þ Error loading from Datafile.\n");

		fclose( fd );
	}

//********************************************************************************************************************************

void	LoadTexturePage( int file, char *filename, unsigned char Page, texture_info *texture )
	{
		if ( Page < TexturePagesAvailable )

	      		ReadData( file, filename, texture->page_start + (texture->page_width*texture->page_height*Page) );
		
		else

			printf("ERROR... trying to access texture page: %d, when only %d page(s) exist\n", 
				Page, TexturePagesAvailable);
	}

//********************************************************************************************************************************

void	LoadPalette( int file, char *filename, int offset )
	{
      		ReadData( file, filename, &PaletteBuffer[ (offset*3) ] );
	}

//********************************************************************************************************************************

void	LoadTactics( int tactic, char *filename, int *buffer)
	{
      		ReadData( (tactic*8)+TAC_TAC_316, filename, (BYTE *)buffer );
	}

//********************************************************************************************************************************

void	SaveGameData(char *filename)
	{
		FILE *fp=fopen(filename,"wb");

		if(fp!=NULL)
		{
			fwrite(SquadInfo, 	sizeof(char), 		16*20, fp);
			fwrite(FormationInfo, 	sizeof(char), 		16,    fp);
			fwrite(GroupDrawInfo, 	sizeof(char), 		16,    fp);
			fwrite(LeagueTable, 	sizeof(League_info), 	16,    fp);
			fwrite(&NoOfSubs, 	sizeof(char), 		1,     fp);
			fwrite(&WinPts,		sizeof(char), 		1,     fp);
			fwrite(&DrawPts, 	sizeof(char), 		1,     fp);
			fwrite(&MatchNumber, 	sizeof(MatchNumber), 	1,     fp);
			fclose(fp);						
		}

	}

//********************************************************************************************************************************

void	LoadGameData(char *filename)
	{
		FILE *fp=fopen(filename,"rb");

		if(fp!=NULL)
		{
			fread(SquadInfo, 	sizeof(char), 		16*20, fp);
			fread(FormationInfo, 	sizeof(char), 		16,    fp);
			fread(GroupDrawInfo, 	sizeof(char), 		16,    fp);
			fread(LeagueTable, 	sizeof(League_info), 	16,    fp);
			fread(&NoOfSubs, 	sizeof(char), 		1,     fp);
			fread(&WinPts, 		sizeof(char), 		1,     fp);
			fread(&DrawPts, 	sizeof(char), 		1,     fp);
			fread(&MatchNumber, 	sizeof(MatchNumber), 	1,     fp);
			fclose(fp);						
		}			

	}

//********************************************************************************************************************************




















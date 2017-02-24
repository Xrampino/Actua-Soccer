#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mallocx.h"
#include "euro_def.h"
#include "euro_var.h"
#include "euro_dsk.h"

char	*script_buffer;
FILE 	*script_in;
char	line[256];
char	variable;
int	variable_value;

void		Getvariable( char *buf );
int 		GetVariableValue( char *buf );
void		ConvertLine(char *buf);
void 		GetTextString( char *buf);
short 		GetClubString( char *buf );
char	 	GetFormationType( char *buf );
char 		GetTeamsCodeNumber( char *buf );

short	ImageXcount	=	0;
short	ImageYcount	=	0;
short	ImageWcount	=	0;
short	ImageHcount	=	0;
short	Pagecount	=	0;
short	Stringcount	=	0;
short	Clubcount	=	0;
int	StringOffset	=	0;
int	TempOffset	=	0;
short	Formationcount	=	0;
char	GroupDrawcount	=	0;

short	inst;

#define NO_INSTRUCTION	 	0
#define IMAGE_xCOORD	 	1
#define IMAGE_yCOORD	 	2
#define IMAGE_WIDTH	 	3
#define IMAGE_HEIGHT	 	4
#define IMAGE_PAGE	 	5
#define	TEXT_STRING	 	10
#define	FORMATION_TYPE	 	100
#define	GROUP_DRAW_TYPE	 	101
#define	PLAYERS_CLUB_NAME	102
#define	NULL_INSTRUCTION 	255


//********************************************************************************************************************************

char    process_script_file( char *file)
	{

	script_buffer = (char *) mallocx(32768);

	if( script_buffer==NULL )
		{ 
			printf("\nERROR: Unable to malloc script buffer...");
			return(1);
		}


	else

		{
			if( script_in = fopen ( file, "rt" ), script_in != NULL )
			{
				while( ReadLine ( script_in, &line[0] ) >= 0 )
				{
					inst	=	0;
					ConvertLine(&line[0]);
					memset( line, 0, 256 );
				}
				fclose(script_in);
			}
			freex(script_buffer);
		}
	return(0);
	}

//********************************************************************************************************************************

void	ConvertLine(char *buf)
{
	Getvariable(buf);

	while( variable != NO_INSTRUCTION )
	{

		if ( variable == IMAGE_xCOORD )
			{ Image_Xcoords[ImageXcount] = GetVariableValue(buf); ImageXcount++;  }

		if ( variable == IMAGE_yCOORD )
			{ Image_Ycoords[ImageYcount] = GetVariableValue(buf); ImageYcount++; }

		if ( variable == IMAGE_WIDTH )
			{ Image_Widths[ImageWcount] = GetVariableValue(buf); ImageWcount++; }

		if ( variable == IMAGE_HEIGHT )
			{ Image_Heights[ImageHcount] = GetVariableValue(buf); ImageHcount++; }

		if ( variable == IMAGE_PAGE )
			{ Image_Pages[Pagecount] = GetVariableValue(buf); Pagecount++; }

		if ( variable == TEXT_STRING )
			{ Text[Stringcount] = TextStrings+StringOffset; GetTextString(buf); Stringcount++; }

		if ( variable == FORMATION_TYPE )
			{ FormationInfo[Formationcount] = GetFormationType(buf); Formationcount++; }

		if ( variable == GROUP_DRAW_TYPE )
			{ GroupDrawInfo[GroupDrawcount] = GetTeamsCodeNumber(buf); GroupDrawcount++; }

		if ( variable == PLAYERS_CLUB_NAME )
			{ 
				TempOffset	  = StringOffset;
				Text[Stringcount] = TextStrings+StringOffset; 

				short	Clubnum   = GetClubString(buf);
				
				if ( Clubnum == NOT_FOUND )
				{
					Clubs[Clubcount] = Stringcount;
					Stringcount++;  					
				} 

				else

				{
					Clubs[Clubcount] = Clubnum;
					StringOffset	 = TempOffset;
				}
				
				Clubcount++; 
			}


		Getvariable(buf);
	}	
}

//********************************************************************************************************************************

int 	GetVariableValue( char *buf )	//, int inst )
	{
		int  	val, offset;
		char 	number[10];
		offset	=	0;			
		val	=	0;			
		
		while ( buf[inst] > ('0'-1) && buf[inst] < ('9'+1) )
		{
			number[offset]	=	buf[inst];
			inst++;
			offset++;
		}	
			number[offset]	=	0;

		val 		= 	atoi(number);
		return	( val );
	}

//********************************************************************************************************************************

char 	GetFormationType( char *buf )
	{
		int  	val, offset;
		char	form	=	0;
		char 	number[10];
		offset	=	0;			
		val	=	0;			
		
		if (buf[inst]==' ')
			inst++;
				
		while ( buf[inst] > ('0'-1) && buf[inst] < ('9'+1) )
		{
			number[offset]	=	buf[inst];
			inst++;
			if (buf[inst]=='-')
				inst++;
			offset++;
		}	
			number[offset]	=	0;
			
		val 		= 	atoi(number);

		switch (val)
		{
			case(316):
				form	=	0;
				break;
			case(406):
				form	=	1;
				break;
			case(415):
				form	=	2;
				break;
			case(424):
				form	=	3;
				break;
			case(433):
				form	=	4;
				break;
			case(442):
				form	=	5;
				break;
			case(514):
				form	=	6;
				break;
			case(523):
				form	=	7;
				break;
			case(532):
				form	=	8;
				break;
			case(631):
				form	=	9;
				break;

		}

		return	( form );
	}

//********************************************************************************************************************************

char 	GetTeamsCodeNumber( char *buf )
	{
		char  	val;
		val	=	0;			
		
		if (buf[inst]==' ')
			inst++;
				
		while ( buf[inst] > ('0'-1) && buf[inst] < ('9'+1) )
		{
			if ( buf[inst+1] < 'a' )
				val	= 	((buf[inst+1]-'A')*4);
			else
				val	= 	((buf[inst+1]-'a')*4);

			val+=	(buf[inst]-'1');
			inst+=	2;
		}	

		printf	("val	=	%d\n", val);

	return	( val );
	}

//********************************************************************************************************************************

void 	GetTextString( char *buf )	//, int inst )
	{
		char	CRflag	=	2;

		while ( CRflag!=0 )
		{
		 	if ( buf[inst] == '"' )
				CRflag--;
		 	if ( buf[inst] > 31 && buf[inst] != '/' && buf[inst]!='"' && CRflag==1)
				{
				TextStrings[StringOffset] = buf[inst];
				StringOffset++;
				}
		 	if ( buf[inst+1] > 31 && buf[inst] == '/' && CRflag==1)
				{
				TextStrings[StringOffset] = buf[inst+1];
				StringOffset++;
				inst++;
				}					
		 	if ( (buf[inst] < 31 && CRflag==1) || StringOffset>16383 )
				CRflag = 0;
		inst++;
		}

		TextStrings[StringOffset] = 0;
		StringOffset++;
	}

//********************************************************************************************************************************

short 	GetClubString( char *buf )	
	{



	// ****** GET PLAYERS CLUB ******		



		char	PlayerClub[25];
		char	string[25];
		int	ClubOffset 	= 	0;
		char	CRflag		=	2;
		int	CompareOffset	=	0;
		short	ClubFound	=	NOT_FOUND;
		CRflag			=	1;
		

		while ( CRflag!=0 )
		{
		 	if ( buf[inst] == '"' )
				CRflag--;

		 	if ( buf[inst] > 31 && buf[inst]!='"' && CRflag==1)
				{
					PlayerClub[ClubOffset] = buf[inst];
					ClubOffset++;
				}

		 	if ( buf[inst] < 31 && CRflag==1 )
					CRflag = 0;

		 	inst++;
		}

		PlayerClub[ClubOffset] = 0;
		ClubOffset++;



	// ****** SEARCH THROUGH STRING LIST FOR REPEAT OF CLUB NAME ******



		for ( short s=0; s < Stringcount ; s++ )	    	 
		{
			int CopyOffset	=	0;

			while ( CRflag!=0 )
			{
				if ( TextStrings[CompareOffset] == 0 )
				{
					string[CopyOffset] = 0;
			 		CRflag	=	0;
				}

				else
				{   
					string[CopyOffset] = TextStrings[CompareOffset];
				}

				CopyOffset++;
				CompareOffset++;
			}
			
			if ( strcmpi( PlayerClub, string ) == 0 )
				{
					ClubFound	=	s;		
//					break;
				}				
		}


	// ****** THROW CLUB STRING INTO TEXT LIST ******

			
			if ( ClubFound == NOT_FOUND )
			{
				GetTextString( PlayerClub );
			}		
		
		return(ClubFound);
	}

//********************************************************************************************************************************

void 	Getvariable( char *buf )      
	{
		variable = NO_INSTRUCTION;
			    	
		while ( buf[inst] != 0 && variable == NO_INSTRUCTION )
		{

			if ( buf[inst+1] == ':')
			{
				if ( buf[inst] == 'x' )
				     {variable = IMAGE_xCOORD; inst+=2;} 
				if ( buf[inst] == 'y' )
				     {variable = IMAGE_yCOORD; inst+=2;}
				if ( buf[inst] == 'w' )
				     {variable = IMAGE_WIDTH; inst+=2;}
				if ( buf[inst] == 'h' )
				     {variable = IMAGE_HEIGHT; inst+=2;}
				if ( buf[inst] == 'p' )
				     {variable = IMAGE_PAGE; inst+=2;}
				if ( buf[inst] == 't' )
				     {variable = TEXT_STRING; inst+=2;}
			}

			if ( buf[inst+4] == ':')
			{
				if ( buf[inst] == 'f' && buf[inst+1] == 'o' && buf[inst+2] == 'r' && buf[inst+3] == 'm' )
				     {variable = FORMATION_TYPE; inst+=5;}
				if ( buf[inst] == 'd' && buf[inst+1] == 'r' && buf[inst+2] == 'a' && buf[inst+3] == 'w' )
				     {variable = GROUP_DRAW_TYPE; inst+=5;}
				if ( buf[inst] == 'c' && buf[inst+1] == 'l' && buf[inst+2] == 'u' && buf[inst+3] == 'b' )
				     {variable = PLAYERS_CLUB_NAME; inst+=5;}
			}

			if (variable == NO_INSTRUCTION)
				inst++;
		}	
	}

//********************************************************************************************************************************

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "eurodefs.h"
#include "euro_fxd.h"
#include "mallocx.h"
#include "euro_sym.h"
#include "euro_def.h"
#include "euro_var.h"
#include "euro_dsk.h"

char	*script_buffer;
FILE 	*script_in;
char	line[512];
char	variable;
int	variable_value;

void		Getvariable( char *buf );
int 		GetVariableValue( char *buf );
void		ConvertLine(char *buf);
void 		GetTextString( char *buf);
short 		GetClubString( char *buf );
char	 	GetFormationType( char *buf );
char 		GetTeamsCodeNumber( char *buf );
char	 	GetPositionType( char *buf );
void 		GetAscCharacter( char *buf );
char 		GetCharacter( char *buf );
short		GetDefine( char *buf );
short		GetSwitch( char *buf );

short	ImageXcount	=	0;
short	ImageYcount	=	0;
short	ImageWcount	=	0;
short	ImageHcount	=	0;
short	Pagecount	=	0;
short	Stringcount	=	0;
short	Clubcount	=	0;
short	Speechcount	=	0;
short	Posncount	=	0;
short	Capscount	=	0;
short	Goalscount	=	0;
short	Datecount	=	0;
short	Starcount	=	0;
char	Starplyr	=	0;
short	Pacecount	=	0;
short	Powercount	=	0;
short	Controlcount	=	0;
short	Flaircount	=	0;
short	Visioncount	=	0;
short	Accuracycount	=	0;
short	Staminacount	=	0;
short	Disciplinecount	=	0;
short	Fitnesscount	=	0;
short	LowerCasecount	=	32;
short	Dialcount	=	32;
short	Modemcount	=	0;
short	ModemInitcount	=	0;
short	ModemStrcount	=	0;
short	Value;	

int	StringOffset	=	0;
int	TempOffset	=	0;
short	Formationcount	=	0;
char	GroupDrawcount	=	0;

short	inst, tmpinst;
	
#define	ImgSym	0
#define	TxtSym	1

char	Switch[128];
char	Definition[16];
char	DefType	= ImgSym;

#define NO_INSTRUCTION	 	0
#define IMAGE_xCOORD	 	1
#define IMAGE_yCOORD	 	2
#define IMAGE_WIDTH	 	3
#define IMAGE_HEIGHT	 	4
#define IMAGE_PAGE	 	5
#define	TEXT_STRING	 	10
#define	SPEECH_ID_STRING	11
//#define	STAR_MAN		12
#define	LOWER_CASE		13
#define	DIAL_TYPE		14

#define	FORMATION_TYPE	 	100
#define	GROUP_DRAW_TYPE	 	101
#define	PLAYERS_CLUB_NAME	102
#define	PLAYERS_POSITION	103
#define	CAPS_TYPE 		104
#define	GOALS_TYPE 		105

#define	PACE_TYPE		106
#define	POWER_TYPE		107
#define	CONTROL_TYPE		108
#define	FLAIR_TYPE		109
#define	VISION_TYPE		110
#define	ACCURACY_TYPE		111
#define	STAMINA_TYPE		112
#define	DISCIPLINE_TYPE		113
#define	FITNESS_TYPE		114
#define	DOB_TYPE		115
#define	MODEM_INIT_TYPE		116
#define	MODEM_STR_TYPE		117
#define	MODEM_TYPE		118

#define	DEFINITION_ID		127

#define	NULL_INSTRUCTION 	255


//********************************************************************************************************************************

char    process_script_file( char *file)
	{


	script_buffer = (char *) mallocx(32768);

	if( script_buffer==NULL )
		{ 
			printf	("þ ERROR.. Unable to allocate memory for script file.\n");
		 	fflush(stdout);
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
				printf	("þ %d Bytes used for script file text.\n", StringOffset);
			 	fflush(stdout);
			}

			else
			
			{
				printf	("þ ERROR.. Trying to read script file.\n");
			 	fflush(stdout);
			}

			freex(script_buffer);
		}

//	printf("ImageXcount  =  %d\n",ImageXcount);
//	printf("ImageYcount  =  %d\n",ImageYcount);
//	printf("ImageWcount  =  %d\n",ImageWcount);
//	printf("ImageHcount  =  %d\n",ImageHcount);
//	printf("Pagecount  =  %d\n",Pagecount);
//	printf("Stringcount  =  %d\n",Stringcount);
//	printf("Clubcount  =  %d\n",Clubcount);
//	printf("Speechcount  =  %d\n",Speechcount);
//	printf("Posncount  =  %d\n",Posncount);
//	printf("Capscount  =  %d\n",Capscount);
//	printf("Goalscount  =  %d\n",Goalscount);
//	printf("Datecount  =  %d\n",Datecount);
//	printf("Starcount  =  %d\n",Starcount);
//	printf("Starplyr  =  %d\n",Starplyr);
//	printf("Pacecount  =  %d\n",Pacecount);
//	printf("Powercount  =  %d\n",Powercount);
//	printf("Controlcount  =  %d\n",Controlcount);
//	printf("Flaircount  =  %d\n",Flaircount);
//	printf("Visioncount  =  %d\n",Visioncount);
//	printf("Accuracycount  =  %d\n",Accuracycount);
//	printf("Staminacount  =  %d\n",Staminacount);
//	printf("Disciplinecount  =  %d\n",Disciplinecount);
//	printf("Fitnesscount  =  %d\n",Fitnesscount);
//	printf("LowerCasecount  =  %d\n",LowerCasecount);
//
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
			{ 
			  Text[Stringcount] = TextStrings+StringOffset; 
			  GetTextString(buf); 
			  if ( Stringcount < 320 )
				NamePREFIXtbl[Stringcount] = 0;
			  Stringcount++; 
			}

//		if ( variable == LOWER_CASE )
//			{ GetAscCharacter(buf); LowerCasecount++;}
			 	
		if ( variable == DIAL_TYPE )
			{ LegalDial[Dialcount] = GetCharacter(buf); Dialcount++;}
			 	
		if ( variable == FORMATION_TYPE )
			{ FormationInfo[Formationcount] = GetFormationType(buf); Formationcount++; }

		if ( variable == GROUP_DRAW_TYPE )
			{ GroupDrawInfo[GroupDrawcount] = GetTeamsCodeNumber(buf); 
			  GroupDrawDefaultInfo[GroupDrawcount] = GroupDrawInfo[GroupDrawcount];
				GroupDrawcount++; }

		if ( variable == PLAYERS_CLUB_NAME )
			{ 
				TempOffset	     = StringOffset;
				Clubnames[Clubcount] = TextStrings+StringOffset; 

				short	Clubnum      = GetClubString(buf);
				
				if ( Clubnum != NOT_FOUND )
					StringOffset	     = TempOffset;
				Clubcount++; 
			}

		if ( variable == PLAYERS_POSITION )
			{ PlayerPosns[Posncount] = GetPositionType(buf); Posncount++; }

		if ( variable == CAPS_TYPE )
			{ PlayersCaps[Capscount] = GetFormationType(buf); Capscount++; }

		if ( variable == GOALS_TYPE )
			{ PlayersGoals[Goalscount] = GetFormationType(buf); Goalscount++; }

		if ( variable == DOB_TYPE )
			{ 
				DOBday[Datecount] = GetFormationType(buf); 
				inst++;
				DOBmonth[Datecount] = GetFormationType(buf); 
				inst++;
				DOByear[Datecount] = GetFormationType(buf); 
				Datecount++; 
			}

		if ( variable == PACE_TYPE )
			{ Pace[Pacecount] = GetVariableValue(buf); Pacecount++; }
		if ( variable == POWER_TYPE )
			{ Power[Powercount] = GetVariableValue(buf); Powercount++; }
		if ( variable == CONTROL_TYPE )
			{ Control[Controlcount] = GetVariableValue(buf); Controlcount++; }
		if ( variable == FLAIR_TYPE )
			{ Flair[Flaircount] = GetVariableValue(buf); Flaircount++; }
		if ( variable == VISION_TYPE )
			{ Vision[Visioncount] = GetVariableValue(buf); Visioncount++; }
		if ( variable == ACCURACY_TYPE )
			{ Accuracy[Accuracycount] = GetVariableValue(buf); Accuracycount++; }
		if ( variable == STAMINA_TYPE )
			{ Stamina[Staminacount] = GetVariableValue(buf); Staminacount++; }
		if ( variable == DISCIPLINE_TYPE )
			{ Discipline[Disciplinecount] = GetVariableValue(buf); Disciplinecount++; }
		if ( variable == FITNESS_TYPE )
			{ Fitness[Fitnesscount] = GetVariableValue(buf); 
			  FitnessDefault[Fitnesscount] = Fitness[Fitnesscount];
			  Fitnesscount++; }

		if ( variable == MODEM_TYPE )
			{ 
				Modems[Modemcount] = TextStrings+StringOffset; 
				GetTextString(buf);
				Modemcount++; 
			}

		if ( variable == MODEM_STR_TYPE )
			{ 
				ModemInitStrs[ModemStrcount] = TextStrings+StringOffset; 
				GetTextString(buf);
				ModemStrcount++; 
			}

		if ( variable == MODEM_INIT_TYPE )
			{ ModemInitList[ModemInitcount] = GetVariableValue(buf);  ModemInitcount++; }



		if ( variable == SPEECH_ID_STRING )
			{ 
				SPEECH_identifier[Speechcount] = TextStrings+StringOffset; 
				GetTextString(buf);
				Speechcount++; 

				    Starplyr++;
				    if ( Starplyr>=20 )
				  	Starplyr = 0;
			}

//		if ( variable == STAR_MAN )
//			{
//				StarPlayers[Starcount] = Starplyr;
//				Starcount++;
//			}
//
		if ( variable == DEFINITION_ID )
			{
				Value	=	GetDefine(buf);
				fprintf( fp2, "#define	%s	%d\r\n", Definition, Value);
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

		if (buf[inst]==' ')
			inst++;
		
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

		if (val<200)
			form	=	val;

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
	  return( val );
	}

//********************************************************************************************************************************

char 	GetPositionType( char *buf )
	{
		char  	val;
		val	=	0;			
		
		if (buf[inst]==' ')
			inst++;
				
		if ( buf[inst] == 'D' && buf[inst+1] == 'F' )
			val	=	1;			
		if ( buf[inst] == 'M' && buf[inst+1] == 'D' )
			val	=	2;			
		if ( buf[inst] == 'F' && buf[inst+1] == 'D' )
			val	=	3;			

		return	( val );
	}

//********************************************************************************************************************************

short	GetDefine( char *buf )
	{
		char	Doffset	=	0;					
		short	Value;

		if ( buf[inst] == ' ' )
			inst++;

		while ( buf[inst] > 32 )
		{
			Definition[Doffset] = buf[inst];
			if (Doffset<15)
				Doffset++;
			inst++;
		}

		Definition[Doffset] = 0;

			if ( DefType == ImgSym )
				Value	=	Pagecount;
		else
			if ( DefType == TxtSym )
				Value	=	Stringcount;			
		
		return(Value);
   	}

//********************************************************************************************************************************

short	GetSwitch( char *buf )
	{
		char	Soffset	= 0;					
	 	tmpinst 	= inst;
	       	strcpy( Switch, "No Switch" );

		if ( buf[inst] == '[' )
		{
			inst++;
			
			if ( buf[inst] == ' ' )
				inst++;

			while ( buf[inst]!=']' && Soffset< 127 )
			{
				Switch[Soffset] = buf[inst];
				if (Soffset<127)
					Soffset++;
				inst++;

				if ( buf[inst]==' ' && buf[inst+1]==']' )
					inst++;
			}

			Switch[Soffset] = 0;
			strupr( Switch );			
		}

	 	inst = tmpinst;
		inst++;
		return(Value);
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
		 	if ( (buf[inst] < 31 && CRflag==1) || StringOffset> TEXT_STRING_BUFFER_LEN )
				CRflag = 0;
		inst++;
		}

		TextStrings[StringOffset] = 0;
		StringOffset++;
	}

//********************************************************************************************************************************

void 	GetAscCharacter( char *buf )
	{
		char	CRflag	=	1;

		while ( CRflag!=0 )
		{
		 	if ( buf[inst] == '"' && buf[inst+2]== '"' )
			{
				CRflag	=	0;
				ToLower[LowerCasecount] = buf[inst+1];
			}
		inst++;
		}
	}

//********************************************************************************************************************************

char 	GetCharacter( char *buf )
	{
		char	character;
		char	CRflag	=	1;

		while ( CRflag!=0 )
		{
		 	if ( buf[inst] == '"' && buf[inst+2]== '"' )
			{
				CRflag	=	0;
				character = buf[inst+1];
			}
		inst++;
		}
	return(character);
	}

//********************************************************************************************************************************

short 	GetClubString( char *buf )	
	{



	// ****** GET PLAYERS CLUB ******		



		char	PlayerClub[32];
		char	string[32];
		int	ClubOffset 	= 	0;
		char	CRflag		=	2;
		int	CompareOffset	=	0;
		short	ClubFound	=	NOT_FOUND;
		

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
			CRflag		=	1;

			Clubnames[Clubcount] = TextStrings+CompareOffset; 

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
				break;
			}
		}


	// ****** THROW CLUB STRING INTO TEXT LIST ******

			
			if ( ClubFound == NOT_FOUND )
			{
				Clubnames[Clubcount] = TextStrings+StringOffset; 

				for ( char t=0; t < (strlen(PlayerClub)); t++ )	    	 
				{
					TextStrings[StringOffset] = PlayerClub[t];
					StringOffset++;
				}

			       	TextStrings[StringOffset] = 0;
			       	StringOffset++;
			}		



		
		return(ClubFound);
	}

//********************************************************************************************************************************

void 	Getvariable( char *buf )      
	{
		variable = NO_INSTRUCTION;
			    	
		while ( buf[inst] != 0 && variable == NO_INSTRUCTION )
		{

			if ( buf[inst+1] == ':' && buf[inst-1] <= ' ')
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

		    	if ( buf[inst] == '' && EUROsymbol == 1 )
		    	     {variable = DEFINITION_ID; inst+=2;}

			if ( buf[inst+4] == ':' || buf[inst+3] == ':' || buf[inst+5] == ':' )
			{
				if ( buf[inst] == 'f' && buf[inst+1] == 'o' && buf[inst+2] == 'r' && buf[inst+3] == 'm' )
				     {variable = FORMATION_TYPE; inst+=5; break;}
				if ( buf[inst] == 'd' && buf[inst+1] == 'r' && buf[inst+2] == 'a' && buf[inst+3] == 'w' )
				     {variable = GROUP_DRAW_TYPE; inst+=5; break;}
				if ( buf[inst] == 'c' && buf[inst+1] == 'l' && buf[inst+2] == 'u' && buf[inst+3] == 'b' && Datecount < 320 )
				     {variable = PLAYERS_CLUB_NAME; inst+=5; break;}
				if ( buf[inst] == 'p' && buf[inst+1] == 'o' && buf[inst+2] == 's' && buf[inst+3] == 'n' && Posncount < 320 )
				     {variable = PLAYERS_POSITION; inst+=5; break;}
				if ( buf[inst] == 'c' && buf[inst+1] == 'a' && buf[inst+2] == 'p' && buf[inst+3] == 's' && Capscount < 320 )
				     {variable = CAPS_TYPE; inst+=5; break;}
				if ( buf[inst] == 'g' && buf[inst+1] == 'o' && buf[inst+2] == 'a' && buf[inst+3] == 'l' && Goalscount < 320 )
				     {variable = GOALS_TYPE; inst+=5; break;}
				if ( buf[inst] == 'p' && buf[inst+1] == 'a' && buf[inst+2] == 'c' && buf[inst+3] == 'e' && Pacecount < 320 )
				     {variable = PACE_TYPE; inst+=5; break;}
				if ( buf[inst] == 'p' && buf[inst+1] == 'o' && buf[inst+2] == 'w' && Powercount < 320 )
				     {variable = POWER_TYPE; inst+=4; break;}
				if ( buf[inst] == 'c' && buf[inst+1] == 'n' && buf[inst+2] == 't' && buf[inst+3] == 'l' && Controlcount < 320 )
				     {variable = CONTROL_TYPE; inst+=5; break;}
				if ( buf[inst] == 'f' && buf[inst+1] == 'l' && buf[inst+2] == 'a' && buf[inst+3] == 'r' && Flaircount < 320 )
				     {variable = FLAIR_TYPE; inst+=5; break;}
				if ( buf[inst] == 'v' && buf[inst+1] == 'i' && buf[inst+2] == 's' && buf[inst+3] == 'n' && Visioncount < 320 )
				     {variable = VISION_TYPE; inst+=5; break;}
				if ( buf[inst] == 'a' && buf[inst+1] == 'c' && buf[inst+2] == 'c' && Accuracycount < 320 )
				     {variable = ACCURACY_TYPE; inst+=4; break;}
				if ( buf[inst] == 's' && buf[inst+1] == 't' && buf[inst+2] == 'a' && buf[inst+3] == 'm' && Staminacount < 320 )
				     {variable = STAMINA_TYPE; inst+=5; break;}
				if ( buf[inst] == 'd' && buf[inst+1] == 'i' && buf[inst+2] == 's' && buf[inst+3] == 'c' && Disciplinecount < 320 )
				     {variable = DISCIPLINE_TYPE; inst+=5; break;}
  				if ( buf[inst] == 'f' && buf[inst+1] == 'i' && buf[inst+2] == 't' && Fitnesscount < 320 )
				     {variable = FITNESS_TYPE; inst+=4; break;}
				if ( buf[inst] == 'd' && buf[inst+1] == 'o' && buf[inst+2] == 'b' && Datecount < 320 )
				     {variable = DOB_TYPE; inst+=4; break;}
				if ( buf[inst] == 'n' && buf[inst+1] == 'a' && buf[inst+2] == 'm' && buf[inst+3] == 'e' && Speechcount < 320 )
				     {variable = SPEECH_ID_STRING; inst+=5; break;}
				if ( buf[inst] == 'l' && buf[inst+1] == 'o' && buf[inst+2] == 'w' )
				     {variable = LOWER_CASE; inst+=4; break;}
				if ( buf[inst] == 'd' && buf[inst+1] == 'i' && buf[inst+2] == 'a' && buf[inst+3] == 'l' &&
						Dialcount < 129 )
				     {variable = DIAL_TYPE; inst+=5; break;}

				if ( buf[inst] == 'i' && buf[inst+1] == 'n' && buf[inst+2] == 'i' && buf[inst+3] == 't' )
				     {variable = MODEM_INIT_TYPE; inst+=5;break;}
				if ( buf[inst] == 'm' && buf[inst+1] == 'o' && buf[inst+2] == 'd' && buf[inst+3] == 'e' 
					&& buf[inst+4] == 'm'  )
				     {variable = MODEM_TYPE; inst+=6; break;}
				if ( buf[inst] == 'm' && buf[inst+1] == 's' && buf[inst+2] == 't' && buf[inst+3] == 'r' )
				     {variable = MODEM_STR_TYPE; inst+=5; break;}
			}

//			if ( buf[inst] == '(' && buf[inst+1] == '*' && buf[inst+2] == ')' )
//				     {variable = STAR_MAN; inst+=3; break;}



			// *** Preccess SWITCH Command ***

			if (variable == NO_INSTRUCTION)
			{
				GetSwitch(buf);

				if ( !strcmp( Switch, "IMAGE DATA") )
					DefType	=	ImgSym;
				
				if ( !strcmp( Switch, "TEXT DATA") )
					DefType	=	TxtSym;

				if ( !strcmp( Switch, "ANDY'S TEXT DATA") )
				{
			    		Stringcount = ANDYF_TEXT_START;
					DefType	    = TxtSym;
				}

				if ( !strcmp( Switch, "LAURENT'S TEXT DATA") )
				{
			    		Stringcount = LAURENT_TEXT_START;
					DefType	    = TxtSym;
				}


				if ( (!strcmp( Switch, "MC")) || 
				     (!strcmp( Switch, "LE")) )
					NamePREFIXtbl[Stringcount-1] = 1;

				if ( !strcmp( Switch, "*") )
				{
					StarPlayers[Starcount] = Starplyr;
					Starcount++;
				}
			}
		}	
	}

//********************************************************************************************************************************

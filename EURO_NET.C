#include <stdio.h>

#include "c:\netnow\hmistd.h"
#include "c:\netnow\netnow.h"
#include "c:\netnow\vdata.h"
#include "c:\netnow\vchat.h"
#include "cgdv.h"
#include "c:\sos\include\sosm.h"

#define	MAX_USERS	20
#define	No	  			0
#define	Yes  			1

extern	int	network_on;
extern	volatile int NetTeams[MAX_USERS],Players[MAX_USERS];

	char	EUROnetInitialise	 =	No;

//********************************************************************************************************************************

void	InitEUROnet()
	{

		if ( ( hmiNETNOWInitSystem(20)!=_NETNOW_NO_ERROR) )
		{
			EUROnetInitialise	= No;
			printf	("þ Network cannot be initialised.\n");
			fflush(stdout);
		}

		else

		{
			EUROnetInitialise	= Yes;
			printf	("þ Network initialised okay.\n");
			fflush(stdout);
		}

	}
	
//********************************************************************************************************************************

void	UnInitEUROnet()
	{
		if ( EUROnetInitialise == Yes )
			hmiNETNOWUnInitSystem();
		EUROnetInitialise	= No;
	}
	
//********************************************************************************************************************************

char	CountNumberOfNETstarts()
	{
		char	Starts	=	0;
		char	i;

 		for ( i=0; i < network_on; i++ )
 			{
 				if (NetTeams[i] >= 2)
 					 Starts++;
 			} 
		return( network_on-Starts );
	}

//********************************************************************************************************************************


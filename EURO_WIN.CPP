#include <i86.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "eurodefs.h"
#include "euro_fxd.h"
#include "euro_sym.h"
#include "euro_def.h"
#include "euro_var.h"

//********************************************************************************************************************************

void	TestForWindows95()
	{
	//
	union REGS regs;
	struct SREGS sregs;

	memset(&sregs,0,sizeof(sregs));		//clr sregs
	regs.w.ax=0x1600;
	int386x(0x2F,&regs,&regs,&sregs);

	w95=regs.w.ax & 0xff;

	if (w95==3 || w95==4)
		{
		//running in windows 95!!!
			w95 = Yes;
		      	printf("þ Running windows 95 version.\n");
		}
	else
		{
			w95 = No;
	    		printf("þ Running DOS version.\n");
		}
	}

//********************************************************************************************************************************


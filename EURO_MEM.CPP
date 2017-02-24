#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "eurodefs.h"
#include "euro_fxd.h"
#include "euro_sym.h"
#include "euro_def.h"
#include "euro_var.h"
#include "mallocx.h"

//********************************************************************************************************************************

void	DeAllocateMemory( BYTE* MemAlloc )
	{
		if ( MemAlloc != 0 ) 
			freex( MemAlloc );

		if ( EUROverbose != 0 )
		{
			printf ("þ Memory check: %d\n",get_mem_info() );
		 	fflush(stdout);
		}
	}

//********************************************************************************************************************************

void	Euro96_MemoryInitialise()
	{
		TexturePageMemHandle	=	0;
		TextStringMemHandle	=	0;
	}

//********************************************************************************************************************************

void	AllocateDisplayBuffers()
	{
		EuroPseudoBuffer = (BYTE *) mallocx( 307200);

		if ( EuroPseudoBuffer == 0 )
		{
			printf	("þ Unable to allocate memory for Pseudo buffer.\n");
		 	fflush(stdout);
		}

		else
		{
			if ( EUROverbose != 0 )
			{
				printf ("þ Memory allocated for Pseudo buffer.\n");
			 	fflush(stdout);
				printf ("þ Memory check: %d\n",get_mem_info() );
	 			fflush(stdout);
			}
		}

		EuroBackgroundBuffer = (BYTE *) mallocx( 307200);

		if ( EuroBackgroundBuffer == 0 )
		{
			printf	("þ Unable to allocate memory for Background buffer.\n");
		 	fflush(stdout);
		}

		else

		{
			if ( EUROverbose != 0 )
			{
				printf	("þ Memory allocated for Background buffer.\n");
			 	fflush(stdout);
				printf ("þ Memory check: %d\n",get_mem_info() );
			 	fflush(stdout);
			}
		}
	}

//********************************************************************************************************************************

void	DeAllocateDisplayBuffers()
	{
		if ( EuroBackgroundBuffer != 0 )
		{
			DeAllocateMemory(EuroBackgroundBuffer);
			if ( EUROverbose != 0 )
			{
	      			printf ("þ Memory for Background buffer DeAllocated.\n");
		 		printf ("þ Memory check: %d\n",get_mem_info() );
			 	fflush(stdout);
			}
		}

		else

		{
      			printf	("þ ERROR.. Unable to deAllocate memory for Background Buffer (This could cause a crash).\n");
			fflush(stdout);
 		}
		

		if ( EuroPseudoBuffer != 0 )
		{
			DeAllocateMemory(EuroPseudoBuffer);
			if ( EUROverbose != 0 )
			{
	      			printf ("þ Memory for Pseudo buffer DeAllocated.\n");
				fflush(stdout);
		 		printf ("þ Memory check: %d\n",get_mem_info() );
				fflush(stdout);
			}
		}

		else

		{
      			printf	("þ ERROR.. Unable to deAllocate memory for Pseudo Buffer (This could cause a crash).\n");
			fflush(stdout);
		}
	}

//********************************************************************************************************************************

BYTE*	AllocateTexturePageMemory( unsigned char NoOfTexturePages, texture_info *texture )
	{
		unsigned int size = texture->page_width*texture->page_height*NoOfTexturePages;
		TexturePages	  = (BYTE *) mallocx( size );
		
		if ( TexturePages==0 )
		{
      			printf	("þ ERROR.. Unable to reserve memory for Texture Pages (This could cause a crash).\n");
			fflush(stdout);
		 	TexturePagesAvailable	=	0;
		}
		
		else

		 	TexturePagesAvailable	=	NoOfTexturePages;

			if ( EUROverbose != 0 )
			{
	      			printf ("þ Memory allocated for Texture Pages.\n");
				fflush(stdout);
		 		printf ("þ Memory check: %d\n",get_mem_info() );
				fflush(stdout);
			}

		return ( TexturePages );
	}

//********************************************************************************************************************************

void	DeAllocateTexturePages()
	{
		if ( TexturePageMemHandle != 0 )
		{
			DeAllocateMemory(TexturePageMemHandle);
			if ( EUROverbose != 0 )
			{
	      			printf ("þ Memory for Texture Pages DeAllocated.\n");
				fflush(stdout);
		 		printf ("þ Memory check: %d\n",get_mem_info() );
				fflush(stdout);
			}
		}

		else	
		
		{
      			printf	("þ ERROR.. Unable to deAllocate memory for Texture Pages (This could cause a crash).\n");
		 	fflush(stdout);
		}
	}

//********************************************************************************************************************************

BYTE*	AllocateTextStringMemory()
	{
		TextStrings  = (BYTE *) mallocx( TEXT_STRING_BUFFER_LEN );
		
		if ( TextStrings==0 )
		{
			printf	("þ Unable to allocate memory for Text buffer.\n");
		 	fflush(stdout);
		}
		else
		{
			printf	("þ Memory allocated for Text buffer.\n");
		 	fflush(stdout);

			{		 	
				if ( EUROverbose != 0 )
	 				printf ("þ Memory check: %d\n",get_mem_info() );
					fflush(stdout);
			}
		}

		return ( TextStrings );
	}

//********************************************************************************************************************************
//
//int DisplayFree()
//	{
//		int	M8;
//		int buff[20];
//		union	REGS regs;
//		struct SREGS sregs;
//
//		memset(&sregs,0,sizeof(sregs));                 //clr sregs
//		regs.x.eax=0x500;                               //DPMI get free mem info
//		sregs.es=FP_SEG(buff);                          //Gets SELECTOR in fact.
//		regs.x.edi=FP_OFF(buff);                        //offset from selector.
//		int386x(0x31,&regs,&regs,&sregs);               //Get free memory info
//
//		M8=( (buff[7]*4096) >= MEM8 );
//
//		if (setup.verbose!=0)
//		{
//			printf("\nLargest block: %d\n",buff[0]);
//			printf("Total free   : %d\n\n",buff[7]*4096);
//			if (M8)
//				puts("Initialising 8 meg game");
//			else
//			{
//				puts("Initialising 4 meg game");
//				printf("Need to free %d more bytes to run 8 meg version\n",MEM8-(buff[7]*4096) );
//			}
//		}
//		return	(M8);
//	}
//
//********************************************************************************************************************************

#include <iostream.h>
#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
#include <i86.h>
#include <dos.h>
#include <conio.h>
#include <float.h>
#include <time.h>
#include <math.h>
#include <string.h>



	char	*palette_buffer[768];


void	main(int argc, char **argv)
{
	read_palette()
	write_palette()
}




void	write_palette()
{
	char	*filename	=	"STRIP.BIN";
	
	FILE *fp5=fopen(filename,"wb");

	if(fp5!=NULL)
	{
		fwrite(&palette_buffer+48, sizeof(char), 48, fp5);
		fclose(fp5);						
	}
}



void	read_palette()
{
	char	*filename	=	"TEMP.BIN";
	
	FILE *fp5=fopen(filename,"rb");

	if(fp5!=NULL)
	{
		fread( &palette_buffer, sizeof(char), 768, fp5);
		fclose(fp5);						
	}
}




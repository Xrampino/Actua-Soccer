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

	
char	*GetText(int text_number)
{
	return	("");
}
	
	
char *GetSTRING(int string_type,int array_number)
{
	return("");
}


int	GetSPRITEnumber(int sprite_type,int number,int LastSpriteNO)
{
	return(0);
}

//ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป 
//บ																 บ
//บ  SetToTEXTmode()														 บ
//บ                                                                                                                              บ
//บ  		Sets video mode to a test mode ready to return back to DOS.                                                      บ
//บ																 บ
//ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ 

void	SetToTEXTmode()		
{
		union REGS r;
		r.x.eax = 0x0003;
		int386(0x10, &r, &r);
}



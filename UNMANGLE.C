/* UNMANGLE 13/11/94 for WATCOM C
 * Assumes Intel data in mangled file (no method set in mangle)
 * Converted by P.Hiley.
 * Modified by Kevin Dudley.
 */

#include <conio.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "unmangle.h"

//************************************************************************************************
//
// UnMangle from Memory to Memory
//
// unsigned char *source - pointer to start of unmangled data (not the header)
// unsigned char *dest - pointer to area of memory for destination (make sure it is big enough)
//
// returns - length of data
// 
//************************************************************************************************

extern long int UnMangleMemToMem(unsigned char *source, unsigned char *dest)
	{

	int c;
	int u,v;
	unsigned char *pt;
	unsigned char *start=dest;

	while ((c=*source++)!=0)
		{
		if (c & 128)
			{
			// Bit 7 : 1 : BLOCK
			if (c & 64)
				{
				// Bit 6 : 1 Block size
				if (c & 32)
					{
					// Bit 5 : 1 Long
					pt= dest-((c & 31)<<8) -*source++ -3;	// offset
					c= *source++ + 5;						// size
					while (c--)
						*dest++=*pt++;
					}
				else
					{
					// Bit 5 : 0 Medium
					pt= dest-((c & 3)<<8) -*source++ -3;	// offset
					c= ((c>>2) & 7) + 4;					// size
					while (c--)
						*dest++=*pt++;

					}
				}
			else
				{
				// Bit 6 : 0 : Short
				pt= dest-(c & 63) -3;
				*dest    = *pt;
				*(dest+1)= *(pt+1);
				*(dest+2)= *(pt+2);
				dest+=3;
				}
			}
		else
			{
			// Bit 7 : 0
			if (c & 64)
				{
				// Bit 6 : 1 Seq/Diff or String
				if (c & 32)
					{
					// Bit 5 : 1 : Sequence
						if (c & 16)
						{
						// Bit 4 : 1 : Word sequence
						c= (c & 15) + 2;	// bits 3-0 = len 2->17
						v= *(short *)(dest-2);
						while (c--)
							{
							*(short *)dest=(short)v;
							dest+=2;
							}
						}
					else
						{
						// Bit 4 : 0 : Byte sequence
						c= (c & 15) + 3;	// bits 3-0 = len 3->18
						v= *(dest-1);
						while (c--)
							*dest++=(signed char) v;
						}
					}
				else
					{
					// Bit 5 : 0 : Difference
						if (c & 16)
						{
						// Bit 4 : 1 : Word difference
						c= (c & 15) + 2;			// bits 3-0 = len 2->17
						u= *(short *)(dest-2);		// start word
						v= u -*(short *)(dest-4);	// dif
						while (c--)
							{
							u+=v;
							*(short *)dest=(short)u;
							dest+=2;
							}
						}
					else
						{
						// Bit 4 : 0 : Byte difference
						c= (c & 15) + 3;	// bits 3-0 = len 3->18
						u= *(dest-1);		// start byte
						v= u - *(dest-2);	// dif
						
						while (c--)
							{
							u+=v;
							*dest++=(char)u;
							}
						}
					}
				}
			else
				{
				// Bit 6 : 0 : String
				c &= 63;	// len
				memcpy(dest,source,c);
				dest+=c;
				source+=c;
				}
			}
		}
	return (dest-start);
	}

//************************************************************************************************
//
// UnMangle from File to Memory
//
// *srcfile - 	pointer to the source filename (make sure there is no header)
// *dest - pointer to area of memory for destination (make sure it is big enough)
//
// returns	- Negative on error
//
//************************************************************************************************

unsigned char *unmanglebuf;
unsigned char *unmangleinbuf;
unsigned char *unmangledst;			// unmangle output address into it's buffer
unsigned long unmangleinpoff;			// offset position reading from mangled file
unsigned long unmanglebufpos;			// offset position of input buffer in mangled file
FILE *unmanglefile;

extern long int UnMangleFileToMem(char *srcfile,unsigned char *dest)
	{

	int c;
	int u,v;
	unsigned char *pt;

// Initialise the unmangle

	unmanglebuf=(unsigned char *)malloc(LOOKBACK+BLOCKSIZE+260);
	unmangleinbuf=(unsigned char *)malloc(INPUTBLOCK);

	unmanglefile=fopen(srcfile,"rb");

	unmangledst=dest;

	unmangleinpoff=0;
	unmanglebufpos=0;

	fseek(unmanglefile,unmanglebufpos,SEEK_SET);
	fread(unmangleinbuf,1,INPUTBLOCK,unmanglefile);

// Do the unmangle
	for(;;)
		{
		c=*unmangleGet(unmangleinpoff++,1);
		if (!c) break;		// done

		if (c & 128)
			{
			// Bit 7 : 1 : BLOCK
			if (c & 64)
				{
				// Bit 6 : 1 Block size
				if (c & 32)
					{
					// Bit 5 : 1 Long
					pt= unmangledst-((c & 31)<<8) -*unmangleGet(unmangleinpoff++,1) -3;	// offset
					c= *unmangleGet(unmangleinpoff++,1) + 5;						// size

					while (c--)
						*unmangledst++=*pt++;
					}
				else
					{
					// Bit 5 : 0 Medium
					pt= unmangledst-((c & 3)<<8) -*unmangleGet(unmangleinpoff++,1) -3;	// offset
					c= ((c>>2) & 7) + 4;					// size
					while (c--)
						*unmangledst++=*pt++;

					}
				}
			else
				{
				// Bit 6 : 0 : Short
				pt= unmangledst-(c & 63) -3;
				*unmangledst    = *pt;
				*(unmangledst+1)= *(pt+1);
				*(unmangledst+2)= *(pt+2);
				unmangledst+=3;
				}
			}
		else
			{
			// Bit 7 : 0
			if (c & 64)
				{
				// Bit 6 : 1 Seq/Diff or String
				if (c & 32)
					{
					// Bit 5 : 1 : Sequence
						if (c & 16)
						{
						// Bit 4 : 1 : Word sequence
						c= (c & 15) + 2;	// bits 3-0 = len 2->17
						v= *(short *)(unmangledst-2);
						while (c--)
							{
							*(short *)unmangledst=(short)v;
							unmangledst+=2;
							}
						}
					else
						{
						// Bit 4 : 0 : Byte sequence
						c= (c & 15) + 3;	// bits 3-0 = len 3->18
						v= *(unmangledst-1);
						while (c--)
							*unmangledst++=(signed char) v;
						}
					}
				else
					{
					// Bit 5 : 0 : Difference
						if (c & 16)
						{
						// Bit 4 : 1 : Word difference
						c= (c & 15) + 2;			// bits 3-0 = len 2->17
						u= *(short *)(unmangledst-2);		// start word
						v= u -*(short *)(unmangledst-4);	// dif
						while (c--)
							{
							u+=v;
							*(short *)unmangledst=(short)u;
							unmangledst+=2;
							}
						}
					else
						{
						// Bit 4 : 0 : Byte difference
						c= (c & 15) + 3;	// bits 3-0 = len 3->18
						u= *(unmangledst-1);		// start byte
						v= u - *(unmangledst-2);	// dif
						
						while (c--)
							{
							u+=v;
							*unmangledst++=(char)u;
							}
						}
					}
				}
			else
				{
				// Bit 6 : 0 : String
				c &= 63;	// len
				memcpy(unmangledst,unmangleGet(unmangleinpoff,c),c);
				unmangledst+=c;
				unmangleinpoff+=c;
				}
			}
		}

	fclose(unmanglefile);

	free(unmanglebuf);
	free(unmangleinbuf);

	return(EZERO);
	}

//************************************************************************************************
//
// UnMangle from file to another file
//
// *srcfile - 	pointer to the source filename (make sure there is no header)
// *destfile - name of destfile
//
// returns	- currently always zero
//
//************************************************************************************************


extern long int UnMangleFileToFile(char *srcfile,char *destfile)
	{

	int c;
	int u,v;
	int len;
	unsigned char *pt;
	FILE *outfile;


// Initialise the unmangle

	unmanglebuf=(unsigned char *)malloc(LOOKBACK+BLOCKSIZE+260);
	unmangleinbuf=(unsigned char *)malloc(INPUTBLOCK);

	unmanglefile=fopen(srcfile,"rb");

	outfile=fopen(destfile,"wb");
	unmangledst=unmanglebuf+LOOKBACK;

	unmangleinpoff=0;
	unmanglebufpos=0;

	fseek(unmanglefile,unmanglebufpos,SEEK_SET);
	fread(unmangleinbuf,1,INPUTBLOCK,unmanglefile);

// Do the unmangle
	for(;;)
		{
		c=*unmangleGet(unmangleinpoff++,1);
		if (!c) break;		// done

		len=unmangledst-(unmanglebuf+LOOKBACK);
		if (len>BLOCKSIZE)
			{
			// output this block
			fwrite(unmanglebuf+LOOKBACK,1,len,outfile);

			// copy back to keep just the LOOKBACK amount

			memcpy(unmanglebuf,unmangledst-LOOKBACK,LOOKBACK);

			unmangledst=unmanglebuf+LOOKBACK;
			}

		if (c & 128)
			{
			// Bit 7 : 1 : BLOCK
			if (c & 64)
				{
				// Bit 6 : 1 Block size
				if (c & 32)
					{
					// Bit 5 : 1 Long
					pt= unmangledst-((c & 31)<<8) -*unmangleGet(unmangleinpoff++,1) -3;	// offset
					c= *unmangleGet(unmangleinpoff++,1) + 5;						// size

					while (c--)
						*unmangledst++=*pt++;
					}
				else
					{
					// Bit 5 : 0 Medium
					pt= unmangledst-((c & 3)<<8) -*unmangleGet(unmangleinpoff++,1) -3;	// offset
					c= ((c>>2) & 7) + 4;					// size
					while (c--)
						*unmangledst++=*pt++;

					}
				}
			else
				{
				// Bit 6 : 0 : Short
				pt= unmangledst-(c & 63) -3;
				*unmangledst    = *pt;
				*(unmangledst+1)= *(pt+1);
				*(unmangledst+2)= *(pt+2);
				unmangledst+=3;
				}
			}
		else
			{
			// Bit 7 : 0
			if (c & 64)
				{
				// Bit 6 : 1 Seq/Diff or String
				if (c & 32)
					{
					// Bit 5 : 1 : Sequence
						if (c & 16)
						{
						// Bit 4 : 1 : Word sequence
						c= (c & 15) + 2;	// bits 3-0 = len 2->17
						v= *(short *)(unmangledst-2);
						while (c--)
							{
							*(short *)unmangledst=(short)v;
							unmangledst+=2;
							}
						}
					else
						{
						// Bit 4 : 0 : Byte sequence
						c= (c & 15) + 3;	// bits 3-0 = len 3->18
						v= *(unmangledst-1);
						while (c--)
							*unmangledst++=(signed char) v;
						}
					}
				else
					{
					// Bit 5 : 0 : Difference
						if (c & 16)
						{
						// Bit 4 : 1 : Word difference
						c= (c & 15) + 2;			// bits 3-0 = len 2->17
						u= *(short *)(unmangledst-2);		// start word
						v= u -*(short *)(unmangledst-4);	// dif
						while (c--)
							{
							u+=v;
							*(short *)unmangledst=(short)u;
							unmangledst+=2;
							}
						}
					else
						{
						// Bit 4 : 0 : Byte difference
						c= (c & 15) + 3;	// bits 3-0 = len 3->18
						u= *(unmangledst-1);		// start byte
						v= u - *(unmangledst-2);	// dif
						
						while (c--)
							{
							u+=v;
							*unmangledst++=(char)u;
							}
						}
					}
				}
			else
				{
				// Bit 6 : 0 : String
				c &= 63;	// len
				memcpy(unmangledst,unmangleGet(unmangleinpoff,c),c);
				unmangledst+=c;
				unmangleinpoff+=c;
				}
			}
		}

//	output any remaining stuff
	
	len=unmangledst-(unmanglebuf+LOOKBACK);
	if (len>0)
		fwrite(unmanglebuf+LOOKBACK,1,len,outfile);

	fclose(unmanglefile);

	free(unmanglebuf);
	free(unmangleinbuf);

	return(EZERO);
	}


//************************************************************************************************


unsigned char *
unmangleGet(unsigned long offset,unsigned long size)
	{
	// Returns a pointer to the mangled data at 'offset' in the mangled file
	// 'size' bytes must be available

	if (offset<unmanglebufpos || size+offset>unmanglebufpos+INPUTBLOCK)
		{
		unmanglebufpos=offset;
		fseek(unmanglefile,unmanglebufpos,SEEK_SET);
		fread(unmangleinbuf,1,INPUTBLOCK,unmanglefile);
		}

	return(unmangleinbuf+offset-unmanglebufpos);

	}

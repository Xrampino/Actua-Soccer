/* Header File for unmangle decompression */

#if     !defined(__UNMANGLE_H)
#define __UNMANGLE_H

#define LOOKBACK 8196		// biggest lookback
#define BLOCKSIZE 10240		// output block size (keep > LOOKBACK to avoid overlap copies)
#define INPUTBLOCK 1024		// Size of the mangled data block to load

extern long int UnMangleMemToMem(unsigned char *source, unsigned char *dest);
extern long int UnMangleFileToMem(char *srcfile,unsigned char *dest);
extern long int UnMangleFileToFile(char *srcfile,char *destfile);

unsigned char *unmangleGet(unsigned long offset,unsigned long size);

#endif  /* __UNMANGLE_H */


// Substitute malloc functions...

#include <i86.h>
#include <dos.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

extern int w95;

struct meminfo {
	unsigned LargestBlockAvail;
	unsigned MaxUnlockedPage;
	unsigned LargestLockablePage;
	unsigned LinAddrSpace;
	unsigned NumFreePagesAvail;
	unsigned NumPhysicalPagesFree;
	unsigned TotalPhysicalPages;
	unsigned FreeLinAddrSpace;
	unsigned SizeOfPageFile;
	unsigned Reserved[3];
	} MemInfo;
		 
unsigned int get_mem_info()
{
	union REGS regs;
	struct SREGS sregs;

	regs.x.eax=0x500;
	memset(&sregs,0,sizeof(sregs));
	sregs.es=FP_SEG(&MemInfo);
	regs.x.edi=FP_OFF(&MemInfo);
	int386x(0x31,&regs,&regs,&sregs);

	return (MemInfo.LargestBlockAvail);
}

void *mallocx(unsigned int size)
{
	union REGS regs;
	unsigned int *address;
	unsigned int handle;

	if (0)//w95)
		return(malloc(size));

	if (size==0) return (NULL);

	size+=4; // Reserve 4 bytes for handle

	regs.x.eax=0x501;
	regs.w.bx=size/65536;
	regs.w.cx=size%65536;

	int386(0x31,&regs,&regs);

	if (regs.w.cflag&1)
		return (NULL);

	address=(unsigned int *)(regs.w.cx+regs.w.bx*65536);
	handle=(unsigned int)(regs.w.di+regs.w.si*65536);
	*address++=handle;

//	printf("Reserve handle = %d\n",handle);

	return ((void *)address);
}

void freex(void *address)
{
	union REGS regs;
	unsigned int handle;

	if (0)//w95) 
	{
		free(address);
		return;
	}				

	if (address!=NULL)
	{
		handle=*((unsigned int *)address-1);

//		printf("Free handle = %d\n",handle);

		regs.x.eax=0x502;
		regs.w.si=handle/65536;
		regs.w.di=handle%65536;

		int386(0x31,&regs,&regs);

//		if (regs.w.cflag&1)
//			puts("Error freeing linear memory");
	}
}



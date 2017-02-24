/* Header File for PEPSI Base Memory */

#if     !defined(__BASEMEM_H)
#define __BASEMEM_H

extern void *BaseAlloc(unsigned long int size);
extern void BaseFree(void *mem);
extern unsigned char *BaseLoadFile(char *name);

#endif  /* __BASEMEM_H */

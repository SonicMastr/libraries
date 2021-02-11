#ifndef _PSP2_KERNEL_CLIB_H_
#define _PSP2_KERNEL_CLIB_H_

#include_next <kernel/libkernel.h>

#include <stdarg.h>

SCE_CDECL_BEGIN

/**
 * Run bkpt #0x88 and end the process in state -1
 *
 * @return none
 */
__attribute__((__noreturn__))
void sceClibAbort(void);

char sceClibLookCtypeTable(char ch);

int sceClibTolower(char ch);
int sceClibToupper(char ch);

__attribute__((__format__(__printf__, 1, 2)))
int sceClibPrintf(const char *fmt, ...);

int sceClibVprintf(const char *fmt, va_list args);

__attribute__((__format__(__printf__, 3, 4)))
int sceClibSnprintf(char *dst, SceSize dst_max_size, const char *fmt, ...);

int sceClibVsnprintf(char *dst, SceSize dst_max_size, const char *fmt, va_list args);

char *sceClibStrncpy(char *dst, const char *src, SceSize len);
char *sceClibStrncat(char *dst, const char *src, SceSize len);

char *sceClibStrrchr(const char *src, int ch);
char *sceClibStrstr(const char *s1, const char *s2);

int sceClibStrcmp(const char *s1, const char *s2);
int sceClibStrncmp(const char *s1, const char *s2, SceSize len);
int sceClibStrncasecmp(const char *s1, const char *s2, SceSize len);

SceSize sceClibStrnlen(const char *s1, SceSize max_len);

void *sceClibMemcpy_safe(void *dst, const void *src, SceSize len);

long long sceClibStrtoll(const char *str, char **endptr, int base);

/* mspace functions */

typedef void* SceClibMspace;

typedef struct SceClibMspaceStats {
  SceSize maxSystemSize;
  SceSize currentSystemSize;
  SceSize maxInUseSize;
  SceSize currentInUseSize;
  SceSize reserved[4];
} SceClibMspaceStats;

/* create and destroy mspace */
SceClibMspace sceClibMspaceCreate(void *base, SceSize capacity);
SceInt32      sceClibMspaceDestroy(SceClibMspace msp);

/* allocator and deallocator */
void *sceClibMspaceMalloc(SceClibMspace msp, SceSize size);
void  sceClibMspaceFree(SceClibMspace msp, void *ptr);
void *sceClibMspaceCalloc(SceClibMspace msp, SceSize nelem, SceSize size);
void *sceClibMspaceMemalign(SceClibMspace msp, SceSize boundary, SceSize size);
void *sceClibMspaceRealloc(SceClibMspace msp, void *ptr, SceSize size);
void *sceClibMspaceReallocalign(SceClibMspace msp, void *ptr, SceSize size, SceSize boundary);

/* utility */
SceSize  sceClibMspaceMallocUsableSize(void *p);
SceInt32 sceClibMspaceMallocStats(SceClibMspace msp, SceClibMspaceStats *buf);
SceInt32 sceClibMspaceMallocStatsFast(SceClibMspace msp, SceClibMspaceStats *buf);
SceInt32 sceClibMspaceIsHeapEmpty(SceClibMspace msp);

SCE_CDECL_END

#endif /* _PSP2_KERNEL_CLIB_H_ */


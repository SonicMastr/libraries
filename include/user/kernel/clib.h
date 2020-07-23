#ifndef _PSP2_KERNEL_CLIB_H_
#define _PSP2_KERNEL_CLIB_H_

#include <psp2/types.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Run bkpt #0x88 and end the process in state -1
 *
 * @return none
 */
void sceClibAbort(void);

char sceClibLookCtypeTable(char ch);

int sceClibTolower(char ch);
int sceClibToupper(char ch);

int sceClibPrintf(const char *fmt, ...);
int sceClibVprintf(const char *fmt, va_list args);
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

void *sceClibMemset(void *dst, int ch, SceSize len);
void *sceClibMemcpy(void *dst, const void *src, SceSize len);
void *sceClibMemcpy_safe(void *dst, const void *src, SceSize len);
void *sceClibMemmove(void *dst, const void *src, SceSize len);

int sceClibMemcmp(const void *s1, const void *s2, SceSize len);

void *sceClibMemchr(const void *src, int ch, SceSize len);

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

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_CLIB_H_ */


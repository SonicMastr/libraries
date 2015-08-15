#ifndef _PSP2_KERNEL_CLIB_H_
#define _PSP2_KERNEL_CLIB_H_

#include <psp2/types.h>
#include <stdarg.h>

int sceClibStrcmp(const char *, const char *);

int sceClibSnprintf(char *, SceSize, const char *, ...);
int sceClibVsnprintf(char *, SceSize, const char *, va_list);

#endif

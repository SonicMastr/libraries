/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_KERNEL_KERNEL_SYSMEM_DEBUG_H
#define _VDSUITE_KERNEL_KERNEL_SYSMEM_DEBUG_H

#include <stdarg.h>

#include <cdefs.h>
#include <scetypes.h>

SCE_CDECL_BEGIN

__attribute__((__format__(__printf__, 1, 2)))
int sceDebugPrintf(const char *fmt, ...);

typedef struct SceKernelDebugMessageContext {
  int hex_value0_hi;
  int hex_value0_lo;
  int hex_value1;
  char *msg0;
  SceSize num;
  char *msg1;
} SceKernelDebugMessageContext;

// msg_type_flag : 0 or 0xB
__attribute__((__format__(__printf__, 3, 4)))
int sceDebugPrintf2(int msg_type_flag, const SceKernelDebugMessageContext *ctx, const char *fmt, ...);

int sceDebugVprintf(const char *fmt, va_list args);

int sceDebugPrintKernelPanic(const SceKernelDebugMessageContext *ctx, void *some_address);

__attribute__((__format__(__printf__, 3, 4)))
int sceDebugPrintfKernelPanic(const SceKernelDebugMessageContext *ctx, void *some_address, const char *fmt, ...);

int sceDebugPrintKernelAssertion(int condition, const SceKernelDebugMessageContext *ctx, void *some_address);

__attribute__((__format__(__printf__, 5, 6)))
int sceDebugPrintfKernelAssertion(int unk, int condition, const SceKernelDebugMessageContext *ctx, int some_address, const char *fmt, ...);

int sceDebugSetHandlers(int (*func)(int unk, const char *format, const va_list args), void *args);

int sceDebugRegisterPutcharHandler(int (*func)(void *args, char c), void *args);

void *sceDebugGetPutcharHandler(void);

int sceDebugPutchar(int character);

int sceDebugDisableInfoDump(int flag);

SCE_CDECL_END

#endif /* _VDSUITE_KERNEL_KERNEL_SYSMEM_DEBUG_H */

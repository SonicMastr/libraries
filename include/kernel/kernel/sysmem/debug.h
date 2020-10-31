/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_KERNEL_KERNEL_SYSMEM_DEBUG_H
#define _VDSUITE_KERNEL_KERNEL_SYSMEM_DEBUG_H

#include <stdarg.h>

#include <cdefs.h>
#include <libdbg.h>
#include <scetypes.h>

SCE_CDECL_BEGIN

/**
 * @brief Print log
 *
 * @param[in] fmt - print fmt
 *
 * @return 0 on success, < 0 on error.
 *
 * @note - log is pass to sceDebugRegisterPutcharHandler's handler.
 */
__attribute__((__format__(__printf__, 1, 2)))
int sceDebugPrintf(const char *fmt, ...);

typedef struct SceKernelDebugMessageContext {
	SceUInt32 hex_value0_hi;
	SceUInt32 hex_value0_lo;
	SceUInt32 hex_value1;
	const char *func;
	SceSize line;
	const char *file;
} SceKernelDebugMessageContext;

typedef enum SceKernelDebugPrintFlags {
	SCE_DBG_PRINT_FLAG_NONE = 0,
	SCE_DBG_PRINT_FLAG_CORE = 1,
	SCE_DBG_PRINT_FLAG_FUNC = 2,
	SCE_DBG_PRINT_FLAG_LINE = 4,
	SCE_DBG_PRINT_FLAG_FILE = 8
} SceKernelDebugPrintFlags;

/**
 * @brief Print log with ctx
 *
 * @param[in] flags - ctx print flags, see:SceKernelDebugPrintFlags
 * @param[in] ctx   - debug msg ctx
 * @param[in] fmt   - print fmt
 *
 * @return 0 on success, < 0 on error.
 *
 * @note - main log is pass to sceDebugRegisterPutcharHandler's handler.
 *         ctx  log is pass to sceDebugSetHandlers's handler.
 */
__attribute__((__format__(__printf__, 3, 4)))
int sceDebugPrintf2(int flags, const SceKernelDebugMessageContext *ctx, const char *fmt, ...);

int sceDebugVprintf(const char *fmt, va_list args);

__attribute__((__noreturn__))
int sceDebugPrintKernelPanic(const SceKernelDebugMessageContext *ctx, const void *lr);

__attribute__((__noreturn__, __format__(__printf__, 3, 4)))
int sceDebugPrintfKernelPanic(const SceKernelDebugMessageContext *ctx, const void *lr, const char *fmt, ...);

/**
 * @brief Assertion with ctx
 *
 * @param[in] condition - condition
 * @param[in] ctx       - debug msg ctx
 * @param[in] lr        - The link register
 *
 * @return 0 on success, < 0 on error.
 */
int sceDebugPrintKernelAssertion(int condition, const SceKernelDebugMessageContext *ctx, const void *lr);

/**
 * @brief Assertion with ctx and Print
 *
 * @param[in] level     - print level, see:SceDbgLogLevel
 * @param[in] condition - condition
 * @param[in] ctx       - debug msg ctx
 * @param[in] lr        - The link register
 * @param[in] fmt       - print fmt
 *
 * @return 0 on success, < 0 on error.
 */
__attribute__((__format__(__printf__, 5, 6)))
int sceDebugPrintfKernelAssertion(int level, int condition, const SceKernelDebugMessageContext *ctx, const void *lr, const char *fmt, ...);

int sceDebugSetHandlers(int (*func)(int unk, const char *format, const va_list args), void *args);

int sceDebugRegisterPutcharHandler(int (*func)(void *args, char c), void *args);

void *sceDebugGetPutcharHandler(void);

int sceDebugPutchar(int character);

/**
 * @brief Set kpanic flag
 *
 * @param[in] flag - If pass not zero to flag, kpanic is not stopped and do smc 0x122.
 *
 * @return previous flag.
 */
int sceDebugDisableInfoDump(int flag);

/**
 * @brief Get current minimum assertion level
 *
 * @return current minimum assertion level.
 */
int sceKernelGetMinimumAssertionLevel(void);

/**
 * @brief Get current minimum assertion level
 *
 * @param[in] level - new minimum assertion level
 *
 * @return previous minimum assertion level.
 */
int sceKernelSetMinimumAssertionLevel(int level);

SCE_CDECL_END

#endif /* _VDSUITE_KERNEL_KERNEL_SYSMEM_DEBUG_H */

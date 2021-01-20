#ifndef _DOLCESDK_PSP2_KERNEL_IOFILEMGR_H_
#define _DOLCESDK_PSP2_KERNEL_IOFILEMGR_H_

#include_next <kernel/iofilemgr.h>

#include <kernel/iofilemgr_async.h>

#ifdef __cplusplus
extern "C" {
#endif

/*--------------------IO Priority--------------------*/

/*Valid priority values range: 1 (highest) - 15 (lowest). Default priority value is 14*/

/**
 * Set IO operations priority for file descriptor
 *
 * @param fd - File UID
 * @param priority - IO operations priority
 *
 * @return < 0 on error.
 */
int sceIoSetPriority(SceUID fd, int priority);

/**
 * Get IO operations priority for file descriptor
 *
 * @param fd - File UID
 *
 * @return A non-negative integer is a valid priority, anything else an error
 */
int sceIoGetPriority(SceUID fd);

/**
 * Set IO operations priority for caller process (will be default for all new IO operations)
 *
 * @param priority - New default IO operations priority
 *
 * @return < 0 on error.
 */
int sceIoSetProcessDefaultPriority(int priority);

/**
 * Get IO operations priority for process
 *
 * @return A non-negative integer is a valid priority, anything else an error
 */
int sceIoGetProcessDefaultPriority(void);

/**
 * Set IO operations priority for caller thread (will be default for all new IO operations)
 *
 * @param priority - New default IO operations priority
 *
 * @return < 0 on error.
 */
int sceIoSetThreadDefaultPriority(int priority);

/**
 * Get IO operations priority for thread
 *
 * @return A non-negative integer is a valid priority, anything else an error
 */
int sceIoGetThreadDefaultPriority(void);

#ifdef __cplusplus
}
#endif

#endif	/* _DOLCESDK_PSP2_KERNEL_IOFILEMGR_H_ */

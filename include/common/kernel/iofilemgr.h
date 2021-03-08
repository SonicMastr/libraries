/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_COMMON_KERNEL_IOFILEMGR_H
#define _VDSUITE_COMMON_KERNEL_IOFILEMGR_H

#include_next <kernel/iofilemgr.h>

#include <kernel/iofilemgr_async.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * May be used with sceIoDevctl()
 */
typedef struct SceIoDevInfo {
  SceOff max_size;
  SceOff free_size;
  SceSize cluster_size;
  void *unk;
} SceIoDevInfo;

/*--------------------IO Priority--------------------*/

/*Valid priority values range: 1 (highest) - 15 (lowest). Default priority value is 14*/

/**
 * Set IO operations priority for file descriptor for non-game application
 *
 * @param fd - File UID
 * @param priority - IO operations priority
 *
 * @return < 0 on error.
 */
int sceIoSetPriorityForSystem(SceUID fd, int priority);

/**
 * Get IO operations priority for file descriptor for non-game application
 *
 * @param fd - File UID
 *
 * @return A non-negative integer is a valid priority, anything else an error
 */
int sceIoGetPriorityForSystem(SceUID fd);

/**
 * Set IO operations priority for caller thread for non-game
 * application (will be default for all new IO operations)
 *
 * @param priority - New default IO operations priority
 *
 * @return < 0 on error.
 */
int sceIoSetThreadDefaultPriorityForSystem(int priority);

/**
 * Get IO operations priority for thread for non-game application
 *
 * @return A non-negative integer is a valid priority, anything else an error
 */
int sceIoGetThreadDefaultPriorityForSystem(void);

#ifdef __cplusplus
}
#endif

#endif	/* _VDSUITE_COMMON_KERNEL_IOFILEMGR_H */

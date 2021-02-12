/*
	Vita Development Suite Libraries
*/

#ifndef _DOLCESDK_PSP2KERN_KERNEL_IOFILEMGR_H_
#define _DOLCESDK_PSP2KERN_KERNEL_IOFILEMGR_H_

#include_next <kernel/iofilemgr.h>

#ifdef __cplusplus
extern "C" {
#endif

/*--------------------IO Priority--------------------*/

/*Valid priority values range: 1 (highest) - 15 (lowest). Default priority value is 14*/

/**
 * Set IO operations priority for caller process (will be default for all new IO operations)
 *
 * @param priority - New default IO operations priority
 *
 * @return < 0 on error.
 */
int sceIoSetProcessDefaultPriorityForSystem(int priority);

/**
 * Get IO operations priority for process
 *
 * @return A non-negative integer is a valid priority, anything else an error
 */
int sceIoGetProcessDefaultPriorityForSystem(void);

/*--------------------Device mount functions--------------------*/

/**
  * Mounts a device
  *
  * @param[in]  id          Device to mount
  * @param[in]  path        Where to mount to
  * @param[in]  permission  Permission flags
  * @param      a4          Unknown, set to 0
  * @param      a5          Unknown, set to 0
  * @param      a6          Unknown, set to 0
  *
  * @return < 0 on error.
  */
int sceIoMount(int id, const char *path, int permission, int a4, int a5, int a6);

/**
  * Unmounts a device
  *
  * @param[in]  id    Device to unmount
  * @param[in]  a2    Unknown, set to 0
  * @param[in]  a3    Unknown, set to 0
  * @param[in]  a4    Unknown, set to 0
  *
  * @return < 0 on error.
  */
int sceIoUmount(int id, int a2, int a3, int a4);

#ifdef __cplusplus
}
#endif

#endif	/* _DOLCESDK_PSP2KERN_KERNEL_IOFILEMGR_H_ */

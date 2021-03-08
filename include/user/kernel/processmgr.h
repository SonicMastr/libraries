/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_USER_KERNEL_PROCESSMGR_H
#define _VDSUITE_USER_KERNEL_PROCESSMGR_H

#include_next <kernel/processmgr.h>

SCE_CDECL_BEGIN

/**
 * Locks certain timers from triggering.
 *
 * @param[in] type - One of ::SceKernelPowerTickType
 *
 * @return 0
  */
int sceKernelPowerLock(SceInt32 type);

/**
 * Unlocks certain timers.
 *
 * @param[in] type - One of ::SceKernelPowerTickType
 *
 * @return 0
 */
int sceKernelPowerUnlock(SceInt32 type);

SCE_CDECL_END

#endif /* _VDSUITE_USER_KERNEL_PROCESSMGR_H */


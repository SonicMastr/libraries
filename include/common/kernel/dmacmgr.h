/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_COMMON_KERNEL_DMACMGR_H
#define _VDSUITE_COMMON_KERNEL_DMACMGR_H

#include <cdefs.h>
#include <scetypes.h>

SCE_CDECL_BEGIN

/**
 * DMA memcpy
 *
 * @param[in] dst - Destination
 * @param[in] src - Source
 * @param[in] size - Size
 *
 * @return dst.
*/
void *sceDmacMemcpy(void *dst, const void *src, SceSize size);

/**
 * DMA memset
 *
 * @param[in] dst - Destination
 * @param[in] c - Constant
 * @param[in] size - Size
 *
 * @return dst.
*/
void *sceDmacMemset(void *dst, int c, SceSize size);

SCE_CDECL_END

#endif /* _VDSUITE_COMMON_KERNEL_DMACMGR_H */

/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_COMMON_KERNEL_IOFILEMGR_STAT_H
#define _VDSUITE_COMMON_KERNEL_IOFILEMGR_STAT_H

#include_next <kernel/iofilemgr_stat.h>

SCE_CDECL_BEGIN

/*@{*/

/** @name Stat 関連マクロ
 *
 */

/* for SceMode */
#define SCE_STM_RWXU		00700
#define SCE_STM_RUSR		00400
#define SCE_STM_WUSR		00200
#define SCE_STM_XUSR		00100

#define SCE_STM_RWXS		00007
#define SCE_STM_RSYS		00004
#define SCE_STM_WSYS		00002
#define SCE_STM_XSYS		00001

/*@}*/

SCE_CDECL_END

#endif	/* _VDSUITE_COMMON_KERNEL_IOFILEMGR_STAT_H */

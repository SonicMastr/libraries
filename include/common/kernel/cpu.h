/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_COMMON_KERNEL_CPU_H
#define _VDSUITE_COMMON_KERNEL_CPU_H

#include_next <kernel/cpu.h>

/**
 * @brief システム向けプロセッサ番号3
 */
#define SCE_KERNEL_CPU_MASK_USER_3		(0x08 << SCE_KERNEL_CPU_MASK_SHIFT)

/**
 * @j @brief システム向けCPUのマスク設定です @ej
 */
#define SCE_KERNEL_CPU_MASK_USER_QUAD	\
			(SCE_KERNEL_CPU_MASK_USER_0 | SCE_KERNEL_CPU_MASK_USER_1 | SCE_KERNEL_CPU_MASK_USER_2　| SCE_KERNEL_CPU_MASK_USER_3)

#endif // _VDSUITE_COMMON_KERNEL_CPU_H

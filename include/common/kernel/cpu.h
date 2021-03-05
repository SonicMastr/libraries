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

SCE_CDECL_BEGIN

#if !defined(_LANGUAGE_ASSEMBLY)

/**
 * @j
 * @brief CPUの物理コア番号を取得するAPIです。デバッグ目的のみに限定してください。
 *
 * @retval 0-3  cpu core number
 * @ej
 */
SceUInt			sceKernelCpuId(void);

#endif	/* !defined(_LANGUAGE_ASSEMBLY) */

SCE_CDECL_END

#endif // _VDSUITE_COMMON_KERNEL_CPU_H

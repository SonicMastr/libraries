/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_COMMON_KERNEL_SYSMEM_MEMBLOCK_H
#define _VDSUITE_COMMON_KERNEL_SYSMEM_MEMBLOCK_H

#include_next <kernel/sysmem/memblock.h>

/** @name sceKernelAllocMemBlockで指定可能なメモリタイプ
 */
/*@{*/

#define SCE_KERNEL_MEMBLOCK_TYPE_USER_RX					0x0c20d050U

#define SCE_KERNEL_MEMBLOCK_TYPE_SHARED_RX					0x0390d050U
#define SCE_KERNEL_MEMBLOCK_TYPE_KERNEL_RX					0x1020d005U
#define SCE_KERNEL_MEMBLOCK_TYPE_KERNEL_RW					0x1020d006U
#define SCE_KERNEL_MEMBLOCK_TYPE_RW_UNK0					0x6020d006U

/*@}*/

/*----- memory access permission -----*/

/**
 * executable memory
 */
#define SCE_KERNEL_MEMORY_ACCESS_X		0x01U

#endif  /* _VDSUITE_COMMON_KERNEL_SYSMEM_MEMBLOCK_H */

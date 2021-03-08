/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_COMMON_KERNEL_THREADMGR_H
#define _VDSUITE_COMMON_KERNEL_THREADMGR_H

#include_next <kernel/threadmgr.h>

SCE_CDECL_BEGIN

typedef struct _SceKernelThreadOptParamInternal {
	/** Size of the ::SceKernelThreadOptParam structure. */
	SceSize               size;
	SceUInt32             attr;
	SceKernelMemBlockType memType1;
	SceKernelMemBlockType memType2;
	SceInt32              unk0x10;
	SceInt32              unk0x14;
	SceInt32              unk0x1C;
} SceKernelThreadOptParamInternal;

SCE_CDECL_END

#endif

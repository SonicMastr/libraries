/*
	Vita Development Suite Libraries
*/

#ifndef _DOLCESDK_PSP2COMMON_KERNEL_THREADMGR_H_
#define _DOLCESDK_PSP2COMMON_KERNEL_THREADMGR_H_

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

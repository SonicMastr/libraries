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

typedef enum _SceKernelTLS {
	SCE_THREAD_TLS_UNK_0,
	SCE_THREAD_TLS_ID,
	SCE_THREAD_TLS_STACK_START_ADDRESS,
	SCE_THREAD_TLS_STACK_END_ADDRESS,
	SCE_THREAD_TLS_VFP_EXCEPTION,
	SCE_THREAD_TLS_LWMUTEX_STATUS,
	SCE_THREAD_TLS_UNK_6,
	SCE_THREAD_TLS_UNK_7,
	SCE_THREAD_TLS_PRIORITY,
	SCE_THREAD_TLS_AFFINITY,
} SceKernelTLS;

/**
 * @brief sceKernelGetThreadTLSAddr gets an address to a 4 bytes area of TLS memory for the specified thread
 * @param thid - The UID of the thread to access TLS
 * @param key - the TLS keyslot index
 * @return pointer to TLS memory
 */
void *sceKernelGetThreadTLSAddr(SceUID thid, SceKernelTLS key);

SCE_CDECL_END

#endif

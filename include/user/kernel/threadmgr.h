/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_USER_KERNEL_THREADMGR_H
#define _VDSUITE_USER_KERNEL_THREADMGR_H

#include_next <kernel/threadmgr.h>

SCE_CDECL_BEGIN

/* Threads. */

/* Sure there must be more than this, but haven't seen them */
typedef enum SceThreadStatus {
	SCE_THREAD_RUNNING = 1,
	SCE_THREAD_READY   = 2,
	SCE_THREAD_WAITING = 4,
	SCE_THREAD_SUSPEND = 8,
	SCE_THREAD_STOPPED = 16,
	SCE_THREAD_KILLED  = 32, /* Thread manager has killed the thread (stack overflow) */
} SceThreadStatus;

/**
 * Get the free stack size for a thread.
 *
 * @param threadId - The thread ID
 *
 * @return The free size.
 */
SceSize sceKernelGetThreadStackFreeSize(SceUID threadId);

/* Misc. */

typedef struct SceKernelWaitSignalOptParam {
	SceUInt32 unk;
} SceKernelWaitSignalOptParam;

/**
 * @brief Sleep current thread and wait for a signal. After it receives a signal, the thread wakes up.
 *
 * This is like a semphore with limit 1.
 * If signal was sent before and not consumed before, the function will immediately return.
 *
 * @param params - extra parameters
 * @return 0 on success
 */
int sceKernelWaitSignal(SceUInt32 unk0, SceUInt32 unk1, SceKernelWaitSignalOptParam *params);

/**
 * @brief Send a signal to another thread specified by thid.
 *
 * @param thid - the id of the thread to send a signal to
 * @return 0 on success
 * @return SCE_KERNEL_ERROR_ALREADY_SENT if the last signal was not consumed by sceKernelWaitSignal
 */
int sceKernelSendSignal(SceUID thid);

/*
 * Mono thread support functions
 */

typedef SceKernelThreadOptParamInternal SceKernelThreadOptParamForMono;

int sceKernelSuspendThreadForMono(SceUID threadId);

int sceKernelResumeThreadForMono(SceUID threadId);

int sceKernelGetThreadContextForMono(
	SceUID threadId,
	SceKernelThreadCpuRegisterInfo* pCpuRegisterInfo,
	SceKernelThreadVfpRegisterInfo* pVfpRegisterInfo);

int sceKernelSetThreadContextForMono(
	SceUID threadId,
	SceKernelThreadCpuRegisterInfo* pCpuRegisterInfo,
	SceKernelThreadVfpRegisterInfo* pVfpRegisterInfo);

SCE_CDECL_END

#endif /* _VDSUITE_USER_KERNEL_THREADMGR_H */


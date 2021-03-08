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

/* Condition variables */

/**
 * Open a condition variable
 *
 * @param pName - The name of the condition variable to open
 * @return Returns an UID if successful, otherwise < 0
 */
SceUID sceKernelOpenCond(const char *pName);

/**
 * Close a condition variable
 *
 * @param condition variableid - The condition variable id returned from ::sceKernelCreateCond
 * @return Returns the value 0 if it's successful, otherwise < 0
 */
SceInt32 sceKernelCloseCond(SceUID condId);

/**
 * Waits for a signal of a condition variable (with callbacks)
 *
 * @param condId - The condition variable id returned from ::sceKernelCreateCond
 * @param pTimeout - Timeout in microseconds
 * @return < 0 On error.
 */
SceInt32 sceKernelWaitCondCB(SceUID condId, SceUInt32 *pTimeout);

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

/**
 * Get the system time (wide version)
 *
 * @return The system time
 */
SceInt64 sceKernelGetSystemTimeWide(void);

/**
 * @brief sceKernelGetThreadTLSAddr gets an address to a 4 bytes area of TLS memory for the specified thread
 * @param thid - The UID of the thread to access TLS
 * @param key - the TLS keyslot index
 * @return pointer to TLS memory
 */
void *sceKernelGetThreadTLSAddr(SceUID thid, int key);

/**
 * @brief sceKernelGetTLSAddr get pointer to TLS key area for current thread
 * @param key - the TLS keyslot index
 * @return pointer to TLS key value
 */
void *sceKernelGetTLSAddr(int key);

typedef enum _SceKernelThreadSpecificInfo {
	SCE_THREAD_SPECIFIC_INFO_UNK_0,
	SCE_THREAD_SPECIFIC_INFO_ID,
	SCE_THREAD_SPECIFIC_INFO_STACK_START_ADDRESS,
	SCE_THREAD_SPECIFIC_INFO_STACK_END_ADDRESS,
	SCE_THREAD_SPECIFIC_INFO_VFP_EXCEPTION,
	SCE_THREAD_SPECIFIC_INFO_LWMUTEX_STATUS,
	SCE_THREAD_SPECIFIC_INFO_UNK_6,
	SCE_THREAD_SPECIFIC_INFO_UNK_7,
	SCE_THREAD_SPECIFIC_INFO_PRIORITY,
	SCE_THREAD_SPECIFIC_INFO_AFFINITY,
} SceKernelThreadSpecificInfo;

SceUnion32 sceKernelGetThreadSpecificInfo(SceUID threadId, SceKernelThreadSpecificInfo info);

/*
 * Mono thread support functions
 */

typedef struct SceKernelThreadContextForMono1 {
	SceSize size;
	char unk[0x54];
} SceKernelThreadContextForMono1;

typedef struct SceKernelThreadContextForMono2 {
	SceSize size;
	char unk[0x104];
} SceKernelThreadContextForMono2;

int sceKernelSuspendThreadForMono(SceUID threadId);

int sceKernelResumeThreadForMono(SceUID threadId);

int sceKernelGetThreadContextForMono(
	SceUID threadId,
	SceKernelThreadContextForMono1* outContext1,
	SceKernelThreadContextForMono2* outContext2);

int sceKernelSetThreadContextForMono(
	SceUID threadId,
	SceKernelThreadContextForMono1* inContext1,
	SceKernelThreadContextForMono2* inContext2);

SCE_CDECL_END

#endif /* _VDSUITE_USER_KERNEL_THREADMGR_H */


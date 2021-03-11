/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_KERNEL_KERNEL_THREADMGR_H
#define _VDSUITE_KERNEL_KERNEL_THREADMGR_H

#include_next <kernel/threadmgr.h>

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

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

typedef struct SceKernelFaultingProcessInfo {
    SceUID pid;
    uint32_t unk;
} SceKernelFaultingProcessInfo;

/**
 * Get the free stack size for a thread.
 *
 * @param thid - The thread ID. Seem to take current thread
 * if set to 0.
 *
 * @return The free size.
 */
int sceKernelGetThreadStackFreeSize(SceUID thid);

/* Fast mutex */

typedef struct SceKernelFastMutexWork {
	SceInt64 data[8];
} SceKernelFastMutexWork;

typedef enum SceKernelFastMutexAttr {
	SCE_KERNEL_FAST_MUTEX_ATTR_RECURSIVE   = 0x00000002,
	SCE_KERNEL_FAST_MUTEX_ATTR_CEILING     = 0x00000004,
	SCE_KERNEL_FAST_MUTEX_ATTR_UNK_3       = 0x00000008,
	SCE_KERNEL_FAST_MUTEX_ATTR_TH_FIFO     = 0x00000000,
	SCE_KERNEL_FAST_MUTEX_ATTR_TH_PRIO     = 0x00002000,
	SCE_KERNEL_FAST_MUTEX_ATTR_UNK_15      = 0x00008000,
	// All other flags are invalid
} SceKernelFastMutexAttr;

typedef struct SceKernelFastMutexOptParam {
	SceSize size;
	SceInt32 ceilingPriority;
} SceKernelFastMutexOptParam;

SceInt32 sceKernelInitializeFastMutex(
	SceKernelFastMutexWork *pWork,
	const char *pName,
	SceKernelFastMutexAttr attr,
	const SceKernelFastMutexOptParam *pOptParam);

SceInt32 sceKernelLockFastMutex(SceKernelFastMutexWork *pWork);

SceInt32 sceKernelTryLockFastMutex(SceKernelFastMutexWork *pWork);

SceInt32 sceKernelUnlockFastMutex(SceKernelFastMutexWork *pWork);

SceInt32 sceKernelFinalizeFastMutex(SceKernelFastMutexWork *pWork);

typedef struct SceKernelFastMutexInfo {
// 0x00
	SceSize size;
	SceUID uid;
	char name[SCE_UID_NAMELEN + 1];
	SceKernelFastMutexAttr attr;
	SceKernelFastMutexWork *pWork;
// 0x30
	SceInt32 currentCount;
	SceUID currentOwnerId;
	SceInt32 ceilingPriority;
	SceInt32 unk3C;
// 0x40
	SceUInt32 numWaitThreads;
// 0x44
} SceKernelFastMutexInfo;

SceInt32 sceKernelGetFastMutexInfo(SceKernelFastMutexWork *pWork, SceKernelFastMutexInfo *pInfo);

SceInt32 sceKernelGetFastMutexInfoById(SceUID uid, SceKernelFastMutexInfo *pInfo);

/* Misc. */

/**
 * Get the system time (wide version)
 *
 * @return The system time
 */
SceInt64 sceKernelGetSystemTimeWide(void);

/** Type of function used with sceKernelExtendKernelStack */
typedef SceInt32 (*SceKernelExtendKernelStackFunction)(void *pArg);

/** Type of function used with sceKernelExtendKernelStackWide */
typedef SceInt64 (*SceKernelExtendKernelStackWideFunction)(void *pArg);

/**
 * @brief		Changes the stack address range and calls extendKernelStackFunc
 *
 * @param[in]	stackSize					Size of the changed stack
 * @param[in]	extendKernelStackFunc		Function to call
 * @param[in]	pCommon						Argument to pass to extendKernelStackFunc
 *
 * @return		Return value of extendKernelStackFunc
 */
SceInt32 sceKernelExtendKernelStack(
	SceSize									stackSize,
	SceKernelExtendKernelStackFunction		extendKernelStackFunc,
	void									*pCommon
);

/**
 * @brief		Changes the stack address range and calls extendKernelStackWideFunc
 *
 * @param[in]	stackSize					Size of the changed stack
 * @param[in]	extendKernelStackWideFunc	Function to call
 * @param[in]	pCommon						Argument to pass to extendKernelStackWideFunc
 *
 * @return		Return value of extendKernelStackWideFunc
 */
SceInt64 sceKernelExtendKernelStackWide(
	SceSize									stackSize,
	SceKernelExtendKernelStackWideFunction	extendKernelStackWideFunc,
	void									*pCommon
);

/**
 * @brief      Call from an abort handler to get info on faulting process
 *
 * @param      info  Output info
 *
 * @return     Zero on success
 */
int sceKernelGetFaultingProcess(SceKernelFaultingProcessInfo *info);

/* Workqueues */

typedef int (* SceKernelWorkQueueWorkFunction)(void *args);

/**
 * @brief      Enqueue work to a workqueue
 *
 * @param[in]  uid  UID of the workqueue (0x10023 for the SceKernelGlobalWorkQueue)
 * @param[in]  name Name of the work to enqueue
 * @param[in]  work Work function to enqueue
 * @param[in]  args Argument to pass to the work function
 *
 * @return     Zero on success
 */
int sceKernelEnqueueWorkQueue(SceUID uid, const char *name, SceKernelWorkQueueWorkFunction work, void *args);

/**
 * @brief       Get the main thread for a given process.
 * @param[in]   pid The process id to query for.
 * @return      The thread UID on success, else < 0 on error.
 */
SceUID sceKernelGetProcessMainThread(SceUID pid);

/**
 * @brief       Retrieve a list of all threads belonging to a process.
 * @param[in]   pid         The process to query.
 * @param[out]  ids         The list of thread ids. Can be NULL if output is not required.
 * @param[in]   n           The max number of thread ids to copy out.
 * @param[out]  copy_count  The number of thread ids copied.
 * @return      The number of threads within the process, else < 0 on error.
 */
int sceKernelGetThreadIdList(SceUID pid, SceUID *ids, int n, int *copy_count);

/** Structure representing all ARM registers */
typedef struct ArmCpuRegisters
{
    uint32_t    r0;
    uint32_t    r1;
    uint32_t    r2;
    uint32_t    r3;
    uint32_t    r4;
    uint32_t    r5;
    uint32_t    r6;
    uint32_t    r7;
    uint32_t    r8;
    uint32_t    r9;
    uint32_t    r10;
    uint32_t    r11;
    uint32_t    r12;
    uint32_t    sp;
    uint32_t    lr;
    uint32_t    pc;
    uint32_t    cpsr;
    uint32_t    unk;
} ArmCpuRegisters;

/** Structure containing a threads register states. */
typedef struct ThreadCpuRegisters
{
    /** Set of registers used for user mode. */
    ArmCpuRegisters user;

    /** Set of registers used for kernel mode. */
    ArmCpuRegisters kernel;
} ThreadCpuRegisters;

/**
 * @brief       Query the state of the registers for a suspended thread.
 *
 * The registers returned are the user/kernel set for the requested thread.
 * It's not certain that user/kernel is correct representation, instead it could be current/exception.
 * The thread provided must be suspended for this function to succeed.
 *
 * @param[in]   thid        The thread to query.
 * @param[out]  registers   The set of registers belonging to the thread.
 * @return      Zero on success, else < 0 on error.
 */
int sceKernelGetThreadCpuRegisters(SceUID thid, ThreadCpuRegisters *registers);


/**
 * @brief       Change the thread suspension status to another value.
 *
 * More research needs to be done to find out exactly what each status actually means. Some examples of useful scenarios:
 * When handling an exception changing the status to 0x1002 (on a newly suspended thread) will stop the kernel rethrowing the same exception.
 * When resuming a suspended thread changing the status to 2 will allow it to resume.
 *
 * @param[in]   thid    The thread to change.
 * @param[in]   status  The new status for suspension.
 * @return      Zero on success, else < 0 on error.
 */
int sceKernelChangeThreadSuspendStatus(SceUID thid, int status);

#ifdef __cplusplus
}
#endif

#endif /* _VDSUITE_KERNEL_KERNEL_THREADMGR_H */


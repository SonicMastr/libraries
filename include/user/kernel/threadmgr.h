#ifndef _PSP2_KERNEL_THREADMGR_H_
#define _PSP2_KERNEL_THREADMGR_H_

#include <psp2common/kernel/threadmgr.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Threads. */

/** Structure to hold the status information for a thread
  * @see sceKernelGetThreadInfo
  */
typedef struct _SceKernelThreadInfo {
	/** Size of the structure */
	SceSize              size;
	SceUID               processId;
	char                 name[SCE_UID_NAMELEN+1];
	SceUInt32            attr;
	SceUInt32            status;
	SceKernelThreadEntry entry;
	void                 *pStack;
	SceSize              stackSize;
	SceInt32             initPriority;
	SceInt32             currentPriority;
	SceInt32             initCpuAffinityMask;
	SceInt32             currentCpuAffinityMask;
	SceInt32             currentCpuId;
	SceInt32             lastExecutedCpuId;
	SceUInt32            waitType;
	SceUID               waitId;
	SceInt32             exitStatus;
	SceKernelSysClock    runClocks;
	SceUInt32            intrPreemptCount;
	SceUInt32            threadPreemptCount;
	SceUInt32            threadReleaseCount;
	SceInt32             changeCpuCount;
	/** Function notify callback UID */
	SceInt32             fNotifyCallback;
	SceInt32             reserved;
} SceKernelThreadInfo;

/** Statistics about a running thread.
 * @see sceKernelGetThreadRunStatus.
 */
typedef struct SceKernelThreadRunStatus {
	SceSize        size;
	struct {
		SceUID processId;
		SceUID threadId;
		int    priority;
	} cpuInfo[SCE_KERNEL_MAX_CPU];
} SceKernelThreadRunStatus;

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
 * Create a thread
 *
 * @param pName - An arbitrary thread name.
 * @param entry - The thread function to run when started.
 * @param initPriority - The initial priority of the thread. Less if higher priority.
 * @param stackSize - The size of the initial stack.
 * @param attr - The thread attributes, zero or more of ::SceThreadAttributes.
 * @param cpuAffinityMask - The CPU affinity mask
 * @param pOptParam - Additional options specified by ::SceKernelThreadOptParam.

 * @return UID of the created thread, or an error code.
 */
SceUID	sceKernelCreateThread(
	const char                    *pName,
	SceKernelThreadEntry          entry,
	SceInt32                      initPriority,
	SceSize                       stackSize,
	SceUInt32                     attr,
	SceInt32                      cpuAffinityMask,
	const SceKernelThreadOptParam *pOptParam);

/**
 * Delate a thread
 *
 * @param threadId - UID of the thread to be deleted.
 *
 * @return < 0 on error.
 */
SceInt32 sceKernelDeleteThread(SceUID threadId);

/**
 * Start a created thread
 *
 * @param threadId - Thread id from ::sceKernelCreateThread
 * @param argSize - Length of the data pointed to by argp, in bytes
 * @param pArgBlock - Pointer to the arguments.
 */
SceInt32 sceKernelStartThread(SceUID threadId, SceSize argSize, const void *pArgBlock);

/**
 * Exit a thread
 *
 * @param exitStatus - Exit status.
 */
SceInt32 sceKernelExitThread(SceInt32 exitStatus);

/**
  * Exit a thread and delete itself.
  *
  * @param exitStatus - Exit status
  */
SceInt32 sceKernelExitDeleteThread(SceInt32 exitStatus);

/**
  * Wait until a thread has ended.
  *
  * @param threadId - Id of the thread to wait for.
  * @param pExitStatus - Exit status.
  * @param pTimeout - Timeout in microseconds.
  *
  * @return < 0 on error.
  */
SceInt32 sceKernelWaitThreadEnd(SceUID threadId, SceInt32 *pExitStatus, SceUInt32 *pTimeout);

/**
  * Wait until a thread has ended and handle callbacks if necessary.
  *
  * @param threadId - Id of the thread to wait for.
  * @param pExitStatus - Exit status.
  * @param pTimeout - Timeout in microseconds.
  *
  * @return < 0 on error.
  */
SceInt32 sceKernelWaitThreadEndCB(SceUID threadId, SceInt32 *pExitStatus, SceUInt32 *pTimeout);

/**
  * Delay the current thread by a specified number of microseconds
  *
  * @param usec - Delay in microseconds.
  *
  * @par Example:
  * @code
  * sceKernelDelayThread(1000000); // Delay for a second
  * @endcode
  */
SceInt32 sceKernelDelayThread(SceUInt32 usec);

/**
  * Delay the current thread by a specified number of microseconds and handle any callbacks.
  *
  * @param usec - Delay in microseconds.
  *
  * @par Example:
  * @code
  * sceKernelDelayThread(1000000); // Delay for a second
  * @endcode
  */
SceInt32 sceKernelDelayThreadCB(SceUInt32 usec);

/**
 * Modify the attributes of the current thread.
 *
 * @param clearAttr - Bits to clear
 * @param setAttr - Bits to set
 *
 * @return < 0 on error.
 */
SceInt32 sceKernelChangeCurrentThreadAttr(SceUInt32 clearAttr, SceUInt32 setAttr);

/**
  * Change the threads current priority.
  *
  * @param threadId - The ID of the thread (from ::sceKernelCreateThread or ::sceKernelGetThreadId)
  * @param priority - The new priority (the lower the number the higher the priority)
  *
  * @par Example:
  * @code
  * int threadId = sceKernelGetThreadId();
  * // Change priority of current thread to 16
  * sceKernelChangeThreadPriority(thid, 16);
  * @endcode
  *
  * @return 0 if successful, otherwise the error code.
  */
SceInt32 sceKernelChangeThreadPriority(SceUID threadId, SceInt32 priority);

/**
  * Change the threads current priority.
  *
  * @param threadId - The ID of the thread (from ::sceKernelCreateThread or ::sceKernelGetThreadId)
  * @param priority - The new priority (the lower the number the higher the priority)
  *
  * @return old priority or error code
  */
SceInt32 sceKernelChangeThreadPriority2(SceUID threadId, SceInt32 priority);

/**
  * Get the current thread Id
  *
  * @return The thread id of the calling thread.
  */
SceUID sceKernelGetThreadId(void);

/**
 * Get the current priority of the thread you are in.
 *
 * @return The current thread priority
 */
SceInt32 sceKernelGetThreadCurrentPriority(void);

/**
 * Get the exit status of a thread.
 *
 * @param threadId - The UID of the thread to check.
 * @param pExitStatus - pointer to area to store result
 *
 * @return 0 or <0 on error
 */
SceInt32 sceKernelGetThreadExitStatus(SceUID threadId, SceInt32 *pExitStatus);

/**
 * Check remaining thread stack size
 *
 * @return Stack size at the time of function call
 */
SceSize sceKernelCheckThreadStack(void);

/**
 * Get the free stack size for a thread.
 *
 * @param threadId - The thread ID
 *
 * @return The free size.
 */
SceSize sceKernelGetThreadStackFreeSize(SceUID threadId);

/**
  * Get the status information for the specified thread.
  *
  * @param threadId - Id of the thread to get status
  * @param pInfo - Pointer to the info structure to receive the data.
  * Note: The structures size field should be set to
  * sizeof(SceKernelThreadInfo) before calling this function.
  *
  * @par Example:
  * @code
  * SceKernelThreadInfo status;
  * status.size = sizeof(SceKernelThreadInfo);
  * if(sceKernelGetThreadInfo(thid, &status) == 0)
  * { Do something... }
  * @endcode
  * @return 0 if successful, otherwise the error code.
  */
SceInt32 sceKernelGetThreadInfo(SceUID threadId, SceKernelThreadInfo *pInfo);

/**
 * Retrive the runtime status of a thread.
 *
 * @param pStatus - Pointer to a ::SceKernelThreadRunStatus struct to receive the runtime status.
 *
 * @return 0 if successful, otherwise the error code.
 */
SceInt32 sceKernelGetThreadRunStatus(SceKernelThreadRunStatus *pStatus);

typedef SceInt32 (*SceKernelChangeStackFunction)(void *pArg);

SceInt32 sceKernelCallWithChangeStack(
	void *pBase,
	SceSize size,
	SceKernelChangeStackFunction changeStackFunc,
	void *pCommon);

SceInt32 sceKernelChangeThreadCpuAffinityMask(SceUID threadId, SceInt32 cpuAffinityMask);

SceInt32 sceKernelGetThreadCpuAffinityMask(SceUID threadId);

/**
 * Get the process ID of the current thread.
 *
 * @return process ID of the current thread
 */
SceUID sceKernelGetProcessId(void);

SceInt32 sceKernelCheckWaitableStatus(void);

SceInt32 sceKernelChangeThreadVfpException(SceInt32 clearMask, SceInt32 setMask);

SceInt32 sceKernelGetCurrentThreadVfpException(void);


/* Semaphores. */

/** Additional options used when creating semaphores. */
typedef struct SceKernelSemaOptParam {
	/** Size of the ::SceKernelSemaOptParam structure. */
	SceSize 	size;
} SceKernelSemaOptParam;

/** Current state of a semaphore.
 * @see sceKernelGetSemaInfo.
 */
typedef struct SceKernelSemaInfo {
	/** Size of the ::SceKernelSemaInfo structure. */
	SceSize         size;
	/** The UID of the semaphore */
	SceUID          semaId;
	/** NUL-terminated name of the semaphore. */
	char            name[SCE_UID_NAMELEN + 1];
	/** Attributes. */
	SceUInt         attr;
	/** The initial count the semaphore was created with. */
	int             initCount;
	/** The current count. */
	int             currentCount;
	/** The maximum count. */
	int             maxCount;
	/** The number of threads waiting on the semaphore. */
	int             numWaitThreads;
} SceKernelSemaInfo;

/**
 * Creates a new semaphore
 *
 * @par Example:
 * @code
 * int semaid;
 * semaid = sceKernelCreateSema("MySema", 0, 1, 1, NULL);
 * @endcode
 *
 * @param name - Specifies the name of the sema
 * @param attr - Sema attribute flags (normally set to 0)
 * @param initCount - Sema initial value
 * @param maxCount - Sema maximum value
 * @param pOptParam - Sema options (normally set to 0)
 * @return A semaphore id
 */
SceUID sceKernelCreateSema(
	const char *name,
	SceUInt32 attr,
	SceInt32 initCount,
	SceInt32 maxCount,
	SceKernelSemaOptParam *pOptParam);

/**
 * Destroy a semaphore
 *
 * @param semaId - The semaid returned from a previous create call.
 * @return Returns the value 0 if it's successful, otherwise negative
 */
SceInt32 sceKernelDeleteSema(SceUID semaId);

/**
 * Send a signal to a semaphore
 *
 * @par Example:
 * @code
 * // Signal the sema
 * sceKernelSignalSema(semaId, 1);
 * @endcode
 *
 * @param semaId - The sema ID returned from ::sceKernelCreateSema
 * @param signalCount - The amount to signal the sema (i.e. if 2 then increment the sema by 2)
 *
 * @return < 0 On error.
 */
SceInt32 sceKernelSignalSema(SceUID semaId, SceInt32 signalCount);

/**
 * Lock a semaphore
 *
 * @par Example:
 * @code
 * sceKernelWaitSema(semaId, 1, 0);
 * @endcode
 *
 * @param semaId - The sema id returned from ::sceKernelCreateSema
 * @param needCount - The value to wait for (i.e. if 1 then wait till reaches a signal state of 1)
 * @param pTimeout - Timeout in microseconds.
 *
 * @return < 0 on error.
 */
SceInt32 sceKernelWaitSema(SceUID semaId, SceInt32 needCount, SceUInt32 *pTimeout);

/**
 * Lock a semaphore and handle callbacks if necessary.
 *
 * @par Example:
 * @code
 * sceKernelWaitSemaCB(semaId, 1, 0);
 * @endcode
 *
 * @param semaId - The sema id returned from ::sceKernelCreateSema
 * @param needCount - The value to wait for (i.e. if 1 then wait till reaches a signal state of 1)
 * @param pTimeout - Timeout in microseconds.
 *
 * @return < 0 on error.
 */
SceInt32 sceKernelWaitSemaCB(SceUID semaId, SceInt32 needCount, SceUInt32 *pTimeout);

/**
 * Poll a semaphore.
 *
 * @param semaId - UID of the semaphore to poll.
 * @param needCount - The value to test for.
 *
 * @return < 0 on error.
 */
SceInt32 sceKernelPollSema(SceUID semaId, SceInt32 needCount);

/**
 * Cancels a semaphore
 *
 * @param semaId - The sema id returned from ::sceKernelCreateSema
 * @param setCount - The new lock count of the semaphore
 * @param pNumWaitThreads - Number of threads waiting for the semaphore
 * @return < 0 On error.
 */
SceInt32 sceKernelCancelSema(SceUID semaId, SceInt32 setCount, SceUInt32 *pNumWaitThreads);

/**
 * Retrieve information about a semaphore.
 *
 * @param semaId - UID of the semaphore to retrieve info for.
 * @param pInfo - Pointer to a ::SceKernelSemaInfo struct to receive the info.
 *
 * @return < 0 on error.
 */
SceInt32 sceKernelGetSemaInfo(SceUID semaId, SceKernelSemaInfo *pInfo);

SceUID sceKernelOpenSema(const char *pName);

SceInt32 sceKernelCloseSema(SceUID semaId);


/* Mutexes. */

/** Additional options used when creating mutexes. */
typedef struct SceKernelMutexOptParam {
	/** Size of the ::SceKernelMutexOptParam structure. */
	SceSize     size;
	SceInt32    ceilingPriority;
} SceKernelMutexOptParam;

/** Current state of a mutex.
 * @see sceKernelGetMutexInfo.
 */
typedef struct SceKernelMutexInfo {
	/** Size of the ::SceKernelMutexInfo structure. */
	SceSize         size;
	/** The UID of the mutex. */
	SceUID          mutexId;
	/** NUL-terminated name of the mutex. */
	char            name[SCE_UID_NAMELEN + 1];
	/** Attributes. */
	SceUInt32       attr;
	/** The initial count the mutex was created with. */
	SceInt32        initCount;
	/** The current count. */
	SceInt32        currentCount;
	/** The UID of the current owner of the mutex. */
	SceUID          currentOwnerId;
	/** The number of threads waiting on the mutex. */
	SceUInt32       numWaitThreads;
	SceInt32        ceilingPriority;
} SceKernelMutexInfo;

/**
 * Creates a new mutex
 *
 * @par Example:
 * @code
 * int mutexid;
 * mutexid = sceKernelCreateMutex("MyMutex", 0, 1, NULL);
 * @endcode
 *
 * @param pName - Specifies the name of the mutex
 * @param attr - Mutex attribute flags (normally set to 0)
 * @param initCount - Mutex initial value
 * @param pOptParam - Mutex options (normally set to 0)
 * @return A mutex id
 */
SceUID sceKernelCreateMutex(
	const char *pName,
	SceUInt32 attr,
	SceInt32 initCount,
	const SceKernelMutexOptParam *pOptParam);

/**
 * Destroy a mutex
 *
 * @param mutexId - The mutex id returned from ::sceKernelCreateMutex
 * @return Returns the value 0 if it's successful, otherwise < 0
 */
SceInt32 sceKernelDeleteMutex(SceUID mutexId);

/**
 * Open a mutex
 *
 * @param pName - The name of the mutex to open
 * @return Returns an UID if successful, otherwise < 0
 */
SceUID sceKernelOpenMutex(const char *pName);

/**
 * Close a mutex
 *
 * @param mutexId - The mutex id returned from ::sceKernelCreateMutex
 * @return Returns the value 0 if it's successful, otherwise < 0
 */
SceInt32 sceKernelCloseMutex(SceUID mutexId);

/**
 * Lock a mutex
 *
 * @param mutexId - The mutex id returned from ::sceKernelCreateMutex
 * @param lockCount - The value to increment to the lock count of the mutex
 * @param pTimeout - Timeout in microseconds
 * @return < 0 On error.
 */
SceInt32 sceKernelLockMutex(SceUID mutexId, SceInt32 lockCount, SceUInt32 *pTimeout);

/**
 * Lock a mutex and handle callbacks if necessary.
 *
 * @param mutexId - The mutex id returned from ::sceKernelCreateMutex
 * @param lockCount - The value to increment to the lock count of the mutex
 * @param pTimeout - Timeout in microseconds
 * @return < 0 On error.
 */
SceInt32 sceKernelLockMutexCB(SceUID mutexId, SceInt32 lockCount, SceUInt32 *pTimeout);

/**
 * Try to lock a mutex (non-blocking)
 *
 * @param mutexId - The mutex id returned from ::sceKernelCreateMutex
 * @param lockCount - The value to increment to the lock count of the mutex
 * @return < 0 On error.
 */
SceInt32 sceKernelTryLockMutex(SceUID mutexId, SceInt32 lockCount);

/**
 * Try to unlock a mutex (non-blocking)
 *
 * @param mutexId - The mutex id returned from ::sceKernelCreateMutex
 * @param unlockCount - The value to decrement to the lock count of the mutex
 * @return < 0 On error.
 */
SceInt32 sceKernelUnlockMutex(SceUID mutexId, SceInt32 unlockCount);

/**
 * Cancels a mutex
 *
 * @param mutexId - The mutex id returned from ::sceKernelCreateMutex
 * @param newCount - The new lock count of the mutex
 * @param pNumWaitThreads - Number of threads waiting for the mutex
 * @return < 0 On error.
 */
SceInt32 sceKernelCancelMutex(SceUID mutexId, SceInt32 newCount, SceUInt32 *pNumWaitThreads);

/**
 * Retrieve information about a mutex.
 *
 * @param mutexId - UID of the mutex to retrieve info for.
 * @param pInfo - Pointer to a ::SceKernelMutexInfo struct to receive the info.
 *
 * @return < 0 on error.
 */
SceInt32 sceKernelGetMutexInfo(SceUID mutexId, SceKernelMutexInfo *pInfo);


/* Event flags. */

/** Structure to hold the event flag information */
typedef struct SceKernelEventFlagInfo {
	SceSize   size;
	SceUID    evfId;
	char      name[SCE_UID_NAMELEN + 1];
	SceUInt32 attr;
	SceUInt32 initPattern;
	SceUInt32 currentPattern;
	SceUInt32 numWaitThreads;
} SceKernelEventFlagInfo;

typedef struct SceKernelEventFlagOptParam {
	SceSize         size;
} SceKernelEventFlagOptParam;

/**
  * Create an event flag.
  *
  * @param pName - The name of the event flag.
  * @param attr - Attributes from ::SceEventFlagAttributes
  * @param initPattern - Initial bit pattern.
  * @param pOptParam  - Options, set to NULL
  * @return < 0 on error. >= 0 event flag id.
  *
  * @par Example:
  * @code
  * int evid;
  * evid = sceKernelCreateEventFlag("wait_event", 0, 0, NULL);
  * @endcode
  */
SceUID sceKernelCreateEventFlag(
	const char *pName,
	SceUInt32 attr,
	SceUInt32 initPattern,
	const SceKernelEventFlagOptParam *pOptParam);

/**
  * Set an event flag bit pattern.
  *
  * @param evfId - The event id returned by ::sceKernelCreateEventFlag.
  * @param bitPattern - The bit pattern to set.
  *
  * @return < 0 On error
  */
SceInt32 sceKernelSetEventFlag(SceUID evfId, SceUInt32 bitPattern);

/**
 * Clear a event flag bit pattern
 *
 * @param evfId - The event id returned by ::sceKernelCreateEventFlag
 * @param bitPattern - The bits to unset
 *
 * @return < 0 on Error
 */
SceInt32 sceKernelClearEventFlag(SceUID evfId, SceUInt32 bitPattern);

/**
  * Poll an event flag for a given bit pattern.
  *
  * @param evfId - The event id returned by ::sceKernelCreateEventFlag.
  * @param bitPattern - The bit pattern to poll for.
  * @param waitMode - Wait type, one or more of ::SceEventFlagWaitTypes or'ed together
  * @param pResultPat - The bit pattern that was matched.
  * @return < 0 On error
  */
SceInt32 sceKernelPollEventFlag(SceUID evfId, SceUInt32 bitPattern, SceUInt32 waitMode, SceUInt32 *pResultPat);

/**
  * Wait for an event flag for a given bit pattern.
  *
  * @param evfId - The event id returned by ::sceKernelCreateEventFlag.
  * @param bitPattern - The bit pattern to poll for.
  * @param waitMode - Wait type, one or more of ::SceEventFlagWaitTypes or'ed together
  * @param pResultPat - The bit pattern that was matched.
  * @param pTimeout  - Timeout in microseconds
  * @return < 0 On error
  */
SceInt32 sceKernelWaitEventFlag(
	SceUID evfId,
	SceUInt32 bitPattern,
	SceUInt32 waitMode,
	SceUInt32 *pResultPat,
	SceUInt32 *pTimeout);

/**
  * Wait for an event flag for a given bit pattern with callback.
  *
  * @param evfId - The event id returned by ::sceKernelCreateEventFlag.
  * @param bitPattern - The bit pattern to poll for.
  * @param waitMode - Wait type, one or more of ::SceEventFlagWaitTypes or'ed together
  * @param pResultPat - The bit pattern that was matched.
  * @param pTimeout  - Timeout in microseconds
  * @return < 0 On error
  */
SceInt32 sceKernelWaitEventFlagCB(
	SceUID evfId,
	SceUInt32 bitPattern,
	SceUInt32 waitMode,
	SceUInt32 *pResultPat,
	SceUInt32 *pTimeout);

/**
  * Delete an event flag
  *
  * @param evfId - The event id returned by ::sceKernelCreateEventFlag.
  *
  * @return < 0 On error
  */
SceInt32 sceKernelDeleteEventFlag(SceUID evfId);

/**
  * Get the status of an event flag.
  *
  * @param evfId - The UID of the event.
  * @param pInfo - A pointer to a ::SceKernelEventFlagInfo structure.
  *
  * @return < 0 on error.
  */
SceInt32 sceKernelGetEventFlagInfo(SceUID evfId, SceKernelEventFlagInfo *pInfo);

SceUID sceKernelOpenEventFlag(const char *pName);

SceInt32 sceKernelCloseEventFlag(SceUID evfId);

SceInt32 sceKernelCancelEventFlag(SceUID evfId, SceUInt32 setPattern, SceUInt32 *pNumWaitThreads);

/* Condition variables */

/** Additional options used when creating condition variables. */
typedef struct SceKernelCondOptParam {
	/** Size of the ::SceKernelCondOptParam structure. */
	SceSize 	size;
} SceKernelCondOptParam;

/** Current state of a condition variable.
 * @see sceKernelGetCondInfo.
 */
typedef struct SceKernelCondInfo {
	/** Size of the ::SceKernelCondInfo structure. */
	SceSize         size;
	/** The UID of the condition variable. */
	SceUID          condId;
	/** NUL-terminated name of the condition variable. */
	char            name[SCE_UID_NAMELEN + 1];
	/** Attributes. */
	SceUInt         attr;
	/** Mutex associated with the condition variable. */
	SceUID          mutexId;
	/** The number of threads waiting on the condition variable. */
	int             numWaitThreads;
} SceKernelCondInfo;

/**
 * Creates a new condition variable
 *
 * @par Example:
 * @code
 * SceUID condId;
 * condId = sceKernelCreateCond("MyCond", 0, mutexId, NULL);
 * @endcode
 *
 * @param pName - Specifies the name of the condition variable
 * @param attr - Condition variable attribute flags (normally set to 0)
 * @param mutexId - Mutex to be related to the condition variable
 * @param pOptParam - Condition variable options (normally set to 0)
 * @return A condition variable id
 */
SceUID sceKernelCreateCond(
	const char *pName,
	SceUInt32 attr,
	SceUID mutexId,
	const SceKernelCondOptParam *pOptParam);

/**
 * Destroy a condition variable
 *
 * @param condition variableid - The condition variable id returned from ::sceKernelCreateCond
 * @return Returns the value 0 if it's successful, otherwise < 0
 */
SceInt32 sceKernelDeleteCond(SceUID condId);

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
 * Waits for a signal of a condition variable
 *
 * @param condId - The condition variable id returned from ::sceKernelCreateCond
 * @param pTimeout - Timeout in microseconds
 * @return < 0 On error.
 */
SceInt32 sceKernelWaitCond(SceUID condId, SceUInt32 *pTimeout);

/**
 * Waits for a signal of a condition variable (with callbacks)
 *
 * @param condId - The condition variable id returned from ::sceKernelCreateCond
 * @param pTimeout - Timeout in microseconds
 * @return < 0 On error.
 */
SceInt32 sceKernelWaitCondCB(SceUID condId, SceUInt32 *pTimeout);

/**
 * Signals a condition variable
 *
 * @param condId - The condition variable id returned from ::sceKernelCreateCond
 * @return < 0 On error.
 */
SceInt32 sceKernelSignalCond(SceUID condId);

/**
 * Signals a condition variable to all threads waiting for it
 *
 * @param condId - The condition variable id returned from ::sceKernelCreateCond
 * @return < 0 On error.
 */
SceInt32 sceKernelSignalCondAll(SceUID condId);

/**
 * Signals a condition variable to a specific thread waiting for it
 *
 * @param condId - The condition variable id returned from ::sceKernelCreateCond
 * @param threadId - The thread id returned from ::sceKernelCreateThread
 * @return < 0 On error.
 */
SceInt32 sceKernelSignalCondTo(SceUID condId, SceUID threadId);

SceInt32 sceKernelGetCondInfo(SceUID condId, SceKernelCondInfo *pInfo);

/* Callbacks. */

/** Callback function prototype */
typedef SceInt32 (*SceKernelCallbackFunction)(
	SceUID notifyId,
	SceInt32 notifyCount,
	SceInt32 notifyArg,
	void *pCommon);

/** Structure to hold the status information for a callback */
typedef struct SceKernelCallbackInfo {
	/** Size of the structure (i.e. sizeof(SceKernelCallbackInfo)) */
	SceSize                   size;
	/** The UID of the callback. */
	SceUID                    callbackId;
	/** The name given to the callback */
	char                      name[SCE_UID_NAMELEN + 1];
	SceUInt32                 attr;
	/** The thread id associated with the callback */
	SceUID                    threadId;
	/** Pointer to the callback function */
	SceKernelCallbackFunction callbackFunc;
	SceUID                    notifyId;
	SceInt32                  notifyCount;
	SceInt32                  notifyArg;
	/** User supplied argument for the callback */
	void                      *pCommon;
} SceKernelCallbackInfo;

/**
 * Create callback
 *
 * @par Example:
 * @code
 * int cbid;
 * cbid = sceKernelCreateCallback("Exit Callback", 0, exit_cb, NULL);
 * @endcode
 *
 * @param name - A textual name for the callback
 * @param attr - Set to 0. There are no attributes.
 * @param callbackFunc - A pointer to a function that will be called as the callback
 * @param pCommon  - Common data for the callback
 *
 * @return >= 0 A callback id which can be used in subsequent functions, < 0 an error.
 */
SceUID sceKernelCreateCallback(
	const char *name,
	SceUInt32 attr,
	SceKernelCallbackFunction callbackFunc,
	void *pCommon);

/**
  * Gets the status of a specified callback.
  *
  * @param callbackId - The UID of the callback to retrieve info for.
  * @param pInfo - Pointer to a status structure. The size parameter should be
  * initialised before calling.
  *
  * @return < 0 on error.
  */
SceInt32 sceKernelGetCallbackInfo(SceUID callbackId, SceKernelCallbackInfo *pInfo);

/**
 * Delete a callback
 *
 * @param callbackId - The UID of the specified callback
 *
 * @return 0 on success, < 0 on error
 */
SceInt32 sceKernelDeleteCallback(SceUID callbackId);

/**
 * Notify a callback
 *
 * @param callbackId - The UID of the specified callback
 * @param notifyArg - Passed as arg2 into the callback function
 *
 * @return 0 on success, < 0 on error
 */
SceInt32 sceKernelNotifyCallback(SceUID callbackId, SceInt32 notifyArg);

/**
 * Cancel a callback ?
 *
 * @param callbackId - The UID of the specified callback
 *
 * @return 0 on success, < 0 on error
 */
SceInt32 sceKernelCancelCallback(SceUID callbackId);

/**
 * Get the callback count
 *
 * @param callbackId - The UID of the specified callback
 *
 * @return The callback count, < 0 on error
 */
SceInt32 sceKernelGetCallbackCount(SceUID callbackId);

/**
 * Check callback notification
 *
 * @return Callback notification count or < 0 on error
 */
SceInt32 sceKernelCheckCallback(void);


/* Message pipes */

typedef struct _SceKernelMsgPipeOptParam {
	SceSize size;
	SceUInt32 attr;
	SceInt32 reserved[2];
	SceUInt32 openLimit;
} SceKernelMsgPipeOptParam;

/**
 * Create a message pipe
 *
 * @param pName - Name of the pipe
 * @param type - Message pipe memory type
 * @param attr - Message pipe attribute
 * @param bufSize - The size of the internal buffer in multiples of 0x1000 (4KiB) up to 32MiB
 * @param pOptParam  - Message pipe options
 *
 * @return The UID of the created pipe, < 0 on error
 */
SceUID sceKernelCreateMsgPipe(
	const char *pName,
	SceUInt32 type,
	SceUInt32 attr,
	SceSize bufSize,
	const SceKernelMsgPipeOptParam *pOptParam);

/**
 * Delete a message pipe
 *
 * @param msgPipeId - The UID of the pipe
 *
 * @return 0 on success, < 0 on error
 */
SceInt32 sceKernelDeleteMsgPipe(SceUID msgPipeId);

/**
 * Send a message to a pipe
 *
 * @param msgPipeId - The UID of the pipe
 * @param pSendBuf - Pointer to the message
 * @param sendSize - Size of the message
 * @param waitMode - Wait mode when sending
 * @param pResult - Pointer to area to store sent size
 * @param pTimeout - Timeout in microseconds
 *
 * @return 0 on success, < 0 on error
 */
SceInt32 sceKernelSendMsgPipe(
	SceUID msgPipeId,
	const void *pSendBuf,
	SceSize sendSize,
	SceUInt32 waitMode,
	SceSize *pResult,
	SceUInt32 *pTimeout);

/**
 * Send a message to a pipe (with callback)
 *
 * @param msgPipeId - The UID of the pipe
 * @param pSendBuf - Pointer to the message
 * @param sendSize - Size of the message
 * @param waitMode - Wait mode when sending
 * @param pResult - Pointer to area to store sent size
 * @param pTimeout - Timeout in microseconds
 *
 * @return 0 on success, < 0 on error
 */
SceInt32 sceKernelSendMsgPipeCB(
	SceUID msgPipeId,
	const void *pSendBuf,
	SceSize sendSize,
	SceUInt32 waitMode,
	SceSize *pResult,
	SceUInt32 *pTimeout);

/**
 * Send a message to a pipe (non blocking)
 *
 * @param msgPipeId - The UID of the pipe
 * @param pSendBuf - Pointer to the message
 * @param sendSize - Size of the message
 * @param waitMode - Wait mode when sending
 * @param pResult - Pointer to area to store sent size
 *
 * @return 0 on success, < 0 on error
 */
SceInt32 sceKernelTrySendMsgPipe(
	SceUID msgPipeId,
	const void *pSendBuf,
	SceSize sendSize,
	SceUInt32 waitMode,
	SceSize *pResult);

/**
 * Receive a message from a pipe
 *
 * @param msgPipeId - The UID of the pipe
 * @param pRecvBuf - Pointer to the message
 * @param recvSize - Size of the message
 * @param waitMode - Wait mode when receiving
 * @param pResult - Pointer to area to store received size
 * @param pTimeout - Timeout in microseconds
 *
 * @return 0 on success, < 0 on error
 */
SceInt32 sceKernelReceiveMsgPipe(
	SceUID msgPipeId,
	const void *pRecvBuf,
	SceSize recvSize,
	SceUInt32 waitMode,
	SceSize *pResult,
	SceUInt32 *pTimeout);

/**
 * Receive a message from a pipe (with callback)
 *
 * @param msgPipeId - The UID of the pipe
 * @param pRecvBuf - Pointer to the message
 * @param recvSize - Size of the message
 * @param waitMode - Wait mode when receiving
 * @param pResult - Pointer to area to store received size
 * @param pTimeout - Timeout in microseconds
 *
 * @return 0 on success, < 0 on error
 */
SceInt32 sceKernelReceiveMsgPipeCB(
	SceUID msgPipeId,
	const void *pRecvBuf,
	SceSize recvSize,
	SceUInt32 waitMode,
	SceSize *pResult,
	SceUInt32 *pTimeout);

/**
 * Receive a message from a pipe (non blocking)
 *
 * @param msgPipeId - The UID of the pipe
 * @param pRecvBuf - Pointer to the message
 * @param recvSize - Size of the message
 * @param waitMode - Wait mode when receiving
 * @param pResult - Pointer to area to store received size
 *
 * @return 0 on success, < 0 on error
 */
SceInt32 sceKernelTryReceiveMsgPipe(
	SceUID msgPipeId,
	void *pRecvBuf,
	SceSize recvSize,
	SceUInt32 waitMode,
	SceSize *pResult);

/**
 * Cancel a message pipe
 *
 * @param msgPipeId - UID of the pipe to cancel
 * @param pNumSendWaitThreads - Receive number of sending threads, NULL is valid
 * @param pNumReceiveWaitThreads - Receive number of receiving threads, NULL is valid
 *
 * @return 0 on success, < 0 on error
 */
SceInt32 sceKernelCancelMsgPipe(
	SceUID msgPipeId,
	SceUInt32 *pNumSendWaitThreads,
	SceUInt32 *pNumReceiveWaitThreads);

/** Message Pipe status info */
typedef struct SceKernelMppInfo {
	SceSize   size;
	SceUID    msgPipeId;
	char      name[SCE_UID_NAMELEN + 1];
	SceUInt32 attr;
	SceSize   bufSize;
	SceSize   freeSize;
	SceUInt32 numSendWaitThreads;
	SceUInt32 numReceiveWaitThreads;
} SceKernelMppInfo;

/**
 * Get the status of a Message Pipe
 *
 * @param msgPipeId - The uid of the Message Pipe
 * @param pInfo - Pointer to a ::SceKernelMppInfo structure
 *
 * @return 0 on success, < 0 on error
 */
SceInt32 sceKernelGetMsgPipeInfo(SceUID msgPipeId, SceKernelMppInfo *pInfo);

SceUID sceKernelOpenMsgPipe(const char *pName);

SceInt32 sceKernelCloseMsgPipe(SceUID msgPipeId);

typedef struct _SceKernelMsgPipeVector {
	void *pBase;
	SceSize bufSize;
} SceKernelMsgPipeVector;

SceInt32 sceKernelSendMsgPipeVector(
	SceUID msgPipeId,
	const SceKernelMsgPipeVector *pVector,
	SceUInt32 numVector,
	SceUInt32 waitMode,
	SceSize *pResult,
	SceUInt32 *pTimeout
);

SceInt32 sceKernelSendMsgPipeVectorCB(
	SceUID msgPipeId,
	const SceKernelMsgPipeVector *pVector,
	SceUInt32 numVector,
	SceUInt32 waitMode,
	SceSize *pResult,
	SceUInt32 *pTimeout);

SceInt32 sceKernelTrySendMsgPipeVector(
	SceUID msgPipeId,
	const SceKernelMsgPipeVector *pVector,
	SceUInt32 numVector,
	SceUInt32 waitMode,
	SceSize *pResult);

SceInt32 sceKernelReceiveMsgPipeVector(
	SceUID msgPipeId,
	const SceKernelMsgPipeVector *pVector,
	SceUInt32 numVector,
	SceUInt32 waitMode,
	SceSize *pResult,
	SceUInt32 *pTimeout);

SceInt32 sceKernelReceiveMsgPipeVectorCB(
	SceUID msgPipeId,
	const SceKernelMsgPipeVector *pVector,
	SceUInt32 numVector,
	SceUInt32 waitMode,
	SceSize *pResult,
	SceUInt32 *pTimeout);

SceInt32 sceKernelTryReceiveMsgPipeVector(
	SceUID msgPipeId,
	const SceKernelMsgPipeVector *pVector,
	SceUInt32 numVector,
	SceUInt32 waitMode,
	SceSize *pResult);

/* Thread event */

SceInt32 sceKernelRegisterCallbackToEvent(SceUID eventId, SceUID callbackId);

SceInt32 sceKernelUnregisterCallbackFromEvent(SceUID eventId, SceUID callbackId);

SceInt32 sceKernelUnregisterCallbackFromEventAll(SceUID eventId);

typedef SceInt32 (*SceKernelThreadEventHandler)(SceInt32 type, SceUID threadId, SceInt32 arg, void *pCommon);

typedef struct _SceKernelEventInfo {
	SceSize size;
	SceUID eventId;
	char name[SCE_UID_NAMELEN + 1];
	SceUInt32 attr;
	SceUInt32 eventPattern;
	SceUInt64 userData;
	SceUInt32 numWaitThreads;
	SceInt32 reserved[1];
} SceKernelEventInfo;

SceInt32 sceKernelWaitEvent(
	SceUID eventId,
	SceUInt32 waitPattern,
	SceUInt32 *pResultPattern,
	SceUInt64 *pUserData,
	SceUInt32 *pTimeout
);

SceInt32 sceKernelWaitEventCB(
	SceUID eventId,
	SceUInt32 waitPattern,
	SceUInt32 *pResultPattern,
	SceUInt64 *pUserData,
	SceUInt32 *pTimeout
);

SceInt32 sceKernelPollEvent(
	SceUID eventId,
	SceUInt32 bitPattern,
	SceUInt32 *pResultPattern,
	SceUInt64 *pUserData
);

typedef struct	_SceKernelWaitEvent {
	SceUID eventId;
	SceUInt32 eventPattern;
} SceKernelWaitEvent;

typedef struct	_SceKernelResultEvent {
	SceUID eventId;
	SceInt32 result;
	SceUInt32 resultPattern;
	SceInt32 reserved[1];
	SceUInt64 userData;
} SceKernelResultEvent;

SceInt32 sceKernelWaitMultipleEvents(
	SceKernelWaitEvent *pWaitEventList,
	SceUInt32 numEvents,
	SceUInt32 waitMode,
	SceKernelResultEvent *pResultEventList,
	SceUInt32 *pTimeout);

SceInt32 sceKernelWaitMultipleEventsCB(
	SceKernelWaitEvent *pWaitEventList,
	SceUInt32 numEvents,
	SceUInt32 waitMode,
	SceKernelResultEvent *pResultEventList,
	SceUInt32 *pTimeout);

SceInt32 sceKernelSetEvent(
	SceUID eventId,
	SceUInt32 setPattern,
	SceUInt64 userData);

SceInt32 sceKernelSetEventWithNotifyCallback(
	SceUID eventId,
	SceUInt32 setPattern,
	SceUInt64 userData,
	SceInt32 notifyArg);

SceInt32 sceKernelPulseEvent(
	SceUID eventId,
	SceUInt32 pulsePattern,
	SceUInt64 userData);

SceInt32 sceKernelPulseEventWithNotifyCallback(
	SceUID eventId,
	SceUInt32 pulsePattern,
	SceUInt64 userData,
	SceInt32 notifyArg);

SceInt32 sceKernelClearEvent(
	SceUID eventId,
	SceUInt32 clearPattern);

SceInt32 sceKernelCancelEventWithSetPattern(
	SceUID eventId,
	SceUInt32 setPattern,
	SceUInt64 userData,
	SceUInt32 *pNumWaitThreads);

SceInt32 sceKernelGetEventPattern(
	SceUID eventId,
	SceUInt32 *pPattern);

SceInt32 sceKernelCancelEvent(
	SceUID eventId,
	SceUInt32 *pNumWaitThreads);

SceInt32 sceKernelGetEventInfo(
	SceUID eventId,
	SceKernelEventInfo *pInfo);

/* Reader/writer lock */

typedef struct _SceKernelRWLockOptParam {
	SceSize	size;
} SceKernelRWLockOptParam;

typedef struct _SceKernelRWLockInfo {
	SceSize size;
	SceUID rwLockId;
	char name[SCE_UID_NAMELEN + 1];
	SceUInt32 attr;
	SceInt32 lockCount;
	SceUID writeOwnerId;
	SceUInt32 numReadWaitThreads;
	SceUInt32 numWriteWaitThreads;
} SceKernelRWLockInfo;

SceUID sceKernelCreateRWLock(
	const char *pName,
	SceUInt32 attr,
	const SceKernelRWLockOptParam*pOptParam);

SceInt32 sceKernelDeleteRWLock(SceUID rwLockId);

SceUID sceKernelOpenRWLock(const char pName);

SceInt32 sceKernelCloseRWLock(SceUID rwLockId);

SceInt32 sceKernelLockReadRWLock(SceUID rwLockId, SceUInt32 *pTimeout);

SceInt32 sceKernelLockReadRWLockCB(SceUID rwLockId, SceUInt32 *pTimeout);

SceInt32 sceKernelTryLockReadRWLock(SceUID rwLockId);

SceInt32 sceKernelUnlockReadRWLock(SceUID rwLockId);

SceInt32 sceKernelLockWriteRWLock(SceUID rwLockId, SceUInt32 *pTimeout);

SceInt32 sceKernelLockWriteRWLockCB(SceUID rwLockId, SceUInt32 *pTimeout);

SceInt32 sceKernelTryLockWriteRWLock(SceUID rwLockId);

SceInt32 sceKernelUnlockWriteRWLock(SceUID rwLockId);

SceInt32 sceKernelCancelRWLock(
	SceUID rwLockId,
	SceUInt32 *pNumReadWaitThreads,
	SceUInt32 *pNumWriteWaitThreads,
	SceInt32 flag);

SceInt32 sceKernelGetRWLockInfo(SceUID rwLockId, SceKernelRWLockInfo *pInfo);

/* Thread timer */

typedef struct _SceKernelTimerOptParam {
	SceSize size;
} SceKernelTimerOptParam;

typedef struct _SceKernelTimerInfo {
	SceSize           size;
	SceUID            timerId;
	char              name[SCE_UID_NAMELEN + 1];
	SceUInt32         attr;
	SceInt32          fActive;
	SceKernelSysClock baseTime;
	SceKernelSysClock currentTime;
	SceKernelSysClock schedule;
	SceKernelSysClock interval;
	SceInt32          type;
	SceInt32          fRepeat;
	SceUInt32         numWaitThreads;
	SceInt32          reserved[1];
} SceKernelTimerInfo;

SceUID sceKernelCreateTimer(
	const char *pName,
	SceUInt32 attr,
	const SceKernelTimerOptParam *pOptParam);

SceInt32 sceKernelDeleteTimer(SceUID timerId);

SceUID sceKernelOpenTimer(const char *pName);

SceInt32 sceKernelCloseTimer(SceUID timerId);

SceInt32 sceKernelStartTimer(SceUID timerId);

SceInt32 sceKernelStopTimer(SceUID timerId);

SceInt32 sceKernelGetTimerBase(SceUID timerId, SceKernelSysClock *pBase);

SceUInt64 sceKernelGetTimerBaseWide(SceUID timerId);

SceInt32 sceKernelGetTimerTime(SceUID timerId, SceKernelSysClock *pClock);

SceUInt64 sceKernelGetTimerTimeWide(SceUID timerId);

SceInt32 sceKernelSetTimerTime(SceUID timerId, SceKernelSysClock *pClock);

SceUInt64 sceKernelSetTimerTimeWide(SceUID timerId, SceUInt64 clock);

SceInt32 sceKernelSetTimerEvent(
	SceUID timerId,
	SceInt32 type,
	SceKernelSysClock *pInterval,
	SceInt32 fRepeat);

SceInt32 sceKernelCancelTimer(SceUID timerId, SceUInt32 *pNumWaitThreads);

SceInt32 sceKernelGetTimerInfo(SceUID timerId, SceKernelTimerInfo *pInfo);

SceInt32 sceKernelGetTimerEventRemainingTime(SceUID timerId, SceKernelSysClock *pClock);

/* Simple event */

typedef struct _SceKernelSimpleEventOptParam {
	SceSize size;
} SceKernelSimpleEventOptParam;

SceUID sceKernelCreateSimpleEvent(
	const char *pName,
	SceUInt32 attr,
	SceUInt32 initPattern,
	const SceKernelSimpleEventOptParam *pOptParam);

SceInt32 sceKernelDeleteSimpleEvent(SceUID simpleEventId);

SceUID sceKernelOpenSimpleEvent(const char *pName);

SceInt32 sceKernelCloseSimpleEvent(SceUID simpleEventId);

/* Misc. */

typedef struct SceKernelSystemInfo {
	SceSize   size;
	SceUInt32 activeCpuMask;

	struct {
		SceKernelSysClock idleClock;
		SceUInt32         comesOutOfIdleCount;
		SceUInt32         threadSwitchCount;
	} cpuInfo[SCE_KERNEL_MAX_CPU];
} SceKernelSystemInfo;

/**
 * Get the system information
 *
 * @param pInfo - Pointer to a ::SceKernelSystemInfo structure
 *
 * @return 0 on success, < 0 on error
 */
SceInt32 sceKernelGetSystemInfo(SceKernelSystemInfo *pInfo);

/* Misc. */

/** Threadmgr types */
typedef enum SceKernelIdListType {
	SCE_KERNEL_TMID_Thread             = 1,
	SCE_KERNEL_TMID_Semaphore          = 2,
	SCE_KERNEL_TMID_EventFlag          = 3,
	SCE_KERNEL_TMID_Mbox               = 4,
	SCE_KERNEL_TMID_Vpl                = 5,
	SCE_KERNEL_TMID_Fpl                = 6,
	SCE_KERNEL_TMID_Mpipe              = 7,
	SCE_KERNEL_TMID_Callback           = 8,
	SCE_KERNEL_TMID_ThreadEventHandler = 9,
	SCE_KERNEL_TMID_Alarm              = 10,
	SCE_KERNEL_TMID_VTimer             = 11,
	SCE_KERNEL_TMID_SleepThread        = 64,
	SCE_KERNEL_TMID_DelayThread        = 65,
	SCE_KERNEL_TMID_SuspendThread      = 66,
	SCE_KERNEL_TMID_DormantThread      = 67
} SceKernelIdListType;

/**
 * Get the type of a Threadmgr uid
 *
 * @param uid - The uid to get the type from
 *
 * @return The type, < 0 on error
 */
SceKernelIdListType sceKernelGetThreadmgrUIDClass(SceUID uid);

/* Lightweight mutex */

typedef struct SceKernelLwMutexWork {
	SceInt64 data[4];
} SceKernelLwMutexWork;

typedef struct SceKernelLwMutexOptParam {
	SceSize size;
} SceKernelLwMutexOptParam;

typedef struct _SceKernelLwMutexInfo {
	SceSize              size;
	SceUID               uid;
	char                 name[SCE_UID_NAMELEN + 1];
	SceUInt32            attr;
	SceKernelLwMutexWork *pWork;
	SceInt32             initCount;
	SceInt32             currentCount;
	SceUID               currentOwnerId;
	SceUInt32            numWaitThreads;
} SceKernelLwMutexInfo;

SceInt32 sceKernelCreateLwMutex(
	SceKernelLwMutexWork *pWork,
	const char *pName,
	SceUInt32 attr,
	SceInt32 initCount,
	const SceKernelLwMutexOptParam *pOptParam);

SceInt32 sceKernelDeleteLwMutex(SceKernelLwMutexWork *pWork);

SceInt32 sceKernelLockLwMutex(SceKernelLwMutexWork *pWork, SceInt32 lockCount, SceUInt32 *pTimeout);

SceInt32 sceKernelLockLwMutexCB(SceKernelLwMutexWork *pWork, SceInt32 lockCount, SceUInt32 *pTimeout);

SceInt32 sceKernelTryLockLwMutex(SceKernelLwMutexWork *pWork, SceInt32 lockCount);

SceInt32 sceKernelUnlockLwMutex(SceKernelLwMutexWork *pWork, SceInt32 unlockCount);

SceInt32 sceKernelGetLwMutexInfo(SceKernelLwMutexWork *pWork, SceKernelLwMutexInfo *pInfo);

SceInt32 sceKernelGetLwMutexInfoById(SceUID lwMutexId, SceKernelLwMutexInfo *pInfo);

/* Lightweight condition */

typedef struct SceKernelLwCondWork {
	SceInt64 data[4];
} SceKernelLwCondWork;

typedef struct SceKernelLwCondOptParam {
	SceSize	size;
} SceKernelLwCondOptParam;

typedef struct _SceKernelLwCondInfo {
	SceSize size;
	SceUID uid;
	char name[SCE_UID_NAMELEN + 1];
	SceUInt32 attr;
	SceKernelLwCondWork *pWork;
	SceKernelLwMutexWork *pLwMutex;
	SceUInt32 numWaitThreads;
} SceKernelLwCondInfo;

SceInt32 sceKernelCreateLwCond(
	SceKernelLwCondWork	          *pWork,
	const char                    *pName,
	SceUInt32                      attr,
	SceKernelLwMutexWork          *pLwMutex,
	const SceKernelLwCondOptParam *pOptParam
);

SceInt32 sceKernelDeleteLwCond(SceKernelLwCondWork *pWork);

SceInt32 sceKernelSignalLwCond(SceKernelLwCondWork *pWork);

SceInt32 sceKernelWaitLwCond(SceKernelLwCondWork *pWork, SceUInt32 *pTimeout);

SceInt32 sceKernelSignalLwCondAll(SceKernelLwCondWork *pWork);

SceInt32 sceKernelSignalLwCondTo(SceKernelLwCondWork *pWork, SceUID threadId);

SceInt32 sceKernelGetLwCondInfo (SceKernelLwCondWork *pWork, SceKernelLwCondInfo *pInfo);

SceInt32 sceKernelGetLwCondInfoById(SceUID lwCondId, SceKernelLwCondInfo *pInfo);

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

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_THREADMGR_H_ */


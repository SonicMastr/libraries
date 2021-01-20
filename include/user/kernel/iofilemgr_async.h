#ifndef _DOLCESDK_PSP2_KERNEL_IOFILEMGR_ASYNC_H_
#define _DOLCESDK_PSP2_KERNEL_IOFILEMGR_ASYNC_H_

#include <psp2common/kernel/iofilemgr/async.h>
#include <psp2/kernel/threadmgr.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Async IO operations are scheduled automatically, similar to FIOS2.
 * You can make calls to sceIoOpenAsync(), sceIoReadAsync(),
 * sceIoCloseAsync() right after each other, they will be put in a schedule
 * and performed automatically.
 *
 * All async IO functions return UID of operation handle, not file descriptor UID.
 */

/**
  * Cancel an asynchronous operation.
  *
  * @param opHandle - The operation handle to perform cancel on.
  *
  * @return < 0 on error. If operation has been canceled(finished) already, returns 0x80010002
  */
int sceIoCancel(SceUID opHandle);

/**
  * Complete an asynchronous operation.
  *
  * @param opHandle - The operation handle to complete.
  *
  * @return < 0 on error.
  */
int sceIoComplete(SceUID opHandle);

/**
  * Complete multiple asynchronous operations.
  *
  * @param asyncParam - Array of ::SceIoAsyncParam representing IO operations to complete. retVal member must have opHandle value assigned to it.
  * @param numOfParam - Number of ::SceIoAsyncParam structs in asyncParam array
  * @param numOfCompleted - Number of operations that has been completed successfully
  *
  * @return < 0 on last encountered error.
  */
int sceIoCompleteMultiple(SceIoAsyncParam* asyncParam, int numOfParam, int* numOfCompleted);

/**
  * Wait until asynchronous operation has been finished.
  *
  * @param opHandle - The operation handle to wait for.
  *
  * @return < 0 on error.
  */
inline
int sceIoWaitAsync(SceUID opHandle)
{
	int ret = sceKernelWaitEvent(opHandle, 1, NULL, NULL, NULL);
	if (ret == 0)
		return sceIoComplete(opHandle);
	else
		return ret;
}

/**
  * Wait until asynchronous operation has been finished with callbacks.
  *
  * @param opHandle - The operation handle to wait for.
  *
  * @return < 0 on error.
  */
inline
int sceIoWaitAsyncCB(SceUID opHandle)
{
	int ret = sceKernelWaitEventCB(opHandle, 1, NULL, NULL, NULL);
	if (ret == 0)
		return sceIoComplete(opHandle);
	else
		return ret;
}

/**
  * Poll asynchronous operation status.
  *
  * @param opHandle - The operation handle to poll status for.
  *
  * @return < 0 on error or if operation is not finished.
  */
inline
int sceIoPollAsync(SceUID opHandle)
{
	int ret = sceKernelPollEvent(opHandle, 1, NULL, NULL);
	if (ret == 0)
		return sceIoComplete(opHandle);
	else
		return ret;
}

#ifdef __cplusplus
}
#endif

#endif	/* _DOLCESDK_PSP2_KERNEL_IOFILEMGR_ASYNC_H_ */

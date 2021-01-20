#ifndef _DOLCESDK_PSP2_KERNEL_IOFILEMGR_ASYNC_H_
#define _DOLCESDK_PSP2_KERNEL_IOFILEMGR_ASYNC_H_

#include_next <kernel/iofilemgr_async.h>

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
  * Complete multiple asynchronous operations.
  *
  * @param asyncParam - Array of ::SceIoAsyncParam representing IO operations to complete. retVal member must have opHandle value assigned to it.
  * @param numOfParam - Number of ::SceIoAsyncParam structs in asyncParam array
  * @param numOfCompleted - Number of operations that has been completed successfully
  *
  * @return < 0 on last encountered error.
  */
int sceIoCompleteMultiple(SceIoAsyncParam* asyncParam, int numOfParam, int* numOfCompleted);

#ifdef __cplusplus
}
#endif

#endif	/* _DOLCESDK_PSP2_KERNEL_IOFILEMGR_ASYNC_H_ */

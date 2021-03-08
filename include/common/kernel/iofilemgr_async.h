/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_COMMON_KERNEL_IOFILEMGR_ASYNC_H
#define _VDSUITE_COMMON_KERNEL_IOFILEMGR_ASYNC_H

#include <stddef.h>
#include <kernel/iofilemgr.h>
#include <kernel/threadmgr.h>

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

typedef struct SceIoAsyncParam {
  int result; // [out] result of the IO operation (e.g. UID, read/wrote size, error code)
  int unk_04; // [out]
  int unk_08; // [in]
  int unk_0C; // [out]
  int unk_10; // [out]
  int unk_14; // [out]
} SceIoAsyncParam;

/**
 * Remove directory entry (asynchronous)
 *
 * @param file - Path to the file to remove
 * @param asyncParam - parameters related to async operation.
 *
 * @return A non-negative integer is a valid op handle, anything else an error
 */
int sceIoRemoveAsync(const char *file, SceIoAsyncParam* asyncParam);

/**
 * Change the name of a file (asynchronous)
 *
 * @param oldname - The old filename
 * @param newname - The new filename
 * @param asyncParam - parameters related to async operation.
 *
 * @return A non-negative integer is a valid op handle, anything else an error
 */
SceUID sceIoRenameAsync(const char *oldname, const char *newname, SceIoAsyncParam* asyncParam);

/**
 * Open or create a file for reading or writing (asynchronous)
 *
 * @param file - Pointer to a string holding the name of the file to open
 * @param flags - Libc styled flags that are or'ed together
 * @param mode - File access mode (One or more ::SceIoMode).
 * @param asyncParam - parameters related to async operation.
 *
 * @return A non-negative integer is a valid op handle, anything else an error
 */
SceUID sceIoOpenAsync(const char *file, int flags, SceMode mode, SceIoAsyncParam* asyncParam);

/**
 * Delete a descriptor (asynchronous)
 *
 * @param fd - File descriptor to close
 * @param asyncParam - parameters related to async operation.
 *
 * @return A non-negative integer is a valid op handle, anything else an error
 */
SceUID sceIoCloseAsync(SceUID fd, SceIoAsyncParam* asyncParam);

/**
 * Read input (asynchronous)
 *
 * @param fd - Opened file descriptor to read from
 * @param data - Pointer to the buffer where the read data will be placed
 * @param size - Size of the read in bytes
 * @param asyncParam - parameters related to async operation.
 *
 * @return A non-negative integer is a valid op handle, anything else an error
 */
SceUID sceIoReadAsync(SceUID fd, void *data, SceSize size, SceIoAsyncParam* asyncParam);

/**
 * Read input at offset (asynchronous)
 *
 * @param fd - Opened file descriptor to read from
 * @param data - Pointer to the buffer where the read data will be placed
 * @param size - Size of the read in bytes
 * @param offset - Offset to read
 * @param asyncParam - parameters related to async operation.
 *
 * @return A non-negative integer is a valid op handle, anything else an error
 */
SceUID sceIoPreadAsync(SceUID fd, void *data, SceSize size, SceOff offset, SceIoAsyncParam* asyncParam);

/**
 * Write output (asynchronous)
 *
 * @param fd - Opened file descriptor to write to
 * @param data - Pointer to the data to write
 * @param size - Size of data to write
 * @param asyncParam - parameters related to async operation.
 *
 * @return A non-negative integer is a valid op handle, anything else an error
 */
SceUID sceIoWriteAsync(SceUID fd, const void *data, SceSize size, SceIoAsyncParam* asyncParam);

/**
 * Write output at offset (asynchronous)
 *
 * @param fd - Opened file descriptor to write to
 * @param data - Pointer to the data to write
 * @param size - Size of data to write
 * @param offset - Offset to write
 * @param asyncParam - parameters related to async operation.
 *
 * @return A non-negative integer is a valid op handle, anything else an error
 */
SceUID sceIoPwriteAsync(SceUID fd, const void *data, SceSize size, SceOff offset, SceIoAsyncParam* asyncParam);

/**
 * Reposition read/write file descriptor offset (asynchronous)
 *
 * @param fd - Opened file descriptor with which to seek
 * @param offset - Relative offset from the start position given by whence
 * @param whence - One of ::SceIoSeekMode.
 * @param asyncParam - parameters related to async operation.
 *
 * @return A non-negative integer is a valid op handle, anything else an error
 */
SceUID sceIoLseekAsync(SceUID fd, SceOff offset, int whence, SceIoAsyncParam* asyncParam);

/**
 * Synchronize device state with state of file or directory being opened
 *
 * @param fd - Opened file descriptor to sync
 * @param fd - Device-dependent flag
 * @param asyncParam - parameters related to async operation.
 *
 * @return A non-negative integer is a valid op handle, anything else an error
 */
SceUID sceIoSyncByFdAsync(SceUID fd, int flag, SceIoAsyncParam* asyncParam);

/**
 * Synchronize device state with memory state
 *
 * @param fd - Device name
 * @param fd - Device-dependent flag
 * @param asyncParam - parameters related to async operation.
 *
 * @return A non-negative integer is a valid op handle, anything else an error
 */
SceUID sceIoSyncAsync(const char* device, int flag, SceIoAsyncParam* asyncParam);

/**
  * This function is unimplemented.
  *
  * @return SCE_KERNEL_ERROR_UNSUP (0x80020004)
  */
int sceIoIoctlAsync(
  SceUID fd,
  int cmd,
  const void *argp,
  SceSize arglen,
  void *bufp,
  SceSize buflen,
  SceIoAsyncParam* asyncParam);

/**
  * This function is unimplemented.
  *
  * @return SCE_KERNEL_ERROR_UNSUP (0x80020004)
  */
int sceIoDevctlAsync(
  const char *devname,
  int cmd,
  const void *arg,
  SceSize arglen,
  void *bufp,
  SceSize buflen,
  SceIoAsyncParam* asyncParam);

/**
  * Open a directory (asynchronous)
  *
  * @param dirname - The directory to open for reading.
  * @param asyncParam - parameters related to async operation.
  *
  * @return If >= 0 then a valid op handle, otherwise a Sony error code.
  */
SceUID sceIoDopenAsync(const char *dirname, SceIoAsyncParam* asyncParam);

/**
  * Reads an entry from an opened file descriptor (asynchronous)
  *
  * @param fd - Already opened file descriptor (using ::sceIoDopen or ::sceIoDopenAsync)
  * @param dir - Pointer to a ::SceIoDirent structure to hold the file information
  * @param asyncParam - parameters related to async operation.
  *
  * @return If >= 0 then a valid op handle, otherwise a Sony error code.
  */
SceUID sceIoDreadAsync(SceUID fd, SceIoDirent *dir, SceIoAsyncParam* asyncParam);

/**
  * Close an opened directory file descriptor (asynchronous)
  *
  * @param fd - Already opened file descriptor (using ::sceIoDopen or ::sceIoDopenAsync)
  * @param asyncParam - parameters related to async operation.
  *
  * @return If >= 0 then a valid op handle, otherwise a Sony error code.
  */
SceUID sceIoDcloseAsync(SceUID fd, SceIoAsyncParam* asyncParam);

/**
 * Make a directory file (asynchronous)
 *
 * @param dir - The path to the directory
 * @param mode - Access mode (One or more ::SceIoAccessMode).
 * @param asyncParam - parameters related to async operation.
 *
 * @return A non-negative integer is a valid op handle, anything else an error
 */
SceUID sceIoMkdirAsync(const char *dir, SceMode mode, SceIoAsyncParam* asyncParam);

/**
 * Remove a directory file (asynchronous)
 *
 * @param path - Removes a directory file pointed by the string path
 * @param asyncParam - parameters related to async operation.
 *
 * @return A non-negative integer is a valid op handle, anything else an error
 */
SceUID sceIoRmdirAsync(const char *path, SceIoAsyncParam* asyncParam);

/**
  * Get the status of a file (asynchronous)
  *
  * @param file - The path to the file.
  * @param stat - A pointer to a ::SceIoStat structure.
  * @param asyncParam - parameters related to async operation.
  *
  * @return A non-negative integer is a valid op handle, anything else an error
  */
SceUID sceIoGetstatAsync(const char *file, SceIoStat *stat, SceIoAsyncParam* asyncParam);

/**
  * Change the status of a file (asynchronous)
  *
  * @param file - The path to the file.
  * @param stat - A pointer to a ::SceIoStat structure.
  * @param bits - Bitmask defining which bits to change.
  * @param asyncParam - parameters related to async operation.
  *
  * @return A non-negative integer is a valid op handle, anything else an error
  */
SceUID sceIoChstatAsync(const char *file, SceIoStat *stat, int bits, SceIoAsyncParam* asyncParam);

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
  * Wait until asynchronous operation has been finished.
  *
  * @param opHandle - The operation handle to wait for.
  *
  * @return < 0 on error.
  */
static __inline__
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
static __inline__
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
static __inline__
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

#endif	/* _VDSUITE_COMMON_KERNEL_IOFILEMGR_ASYNC_H */

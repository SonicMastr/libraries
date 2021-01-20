#ifndef _DOLCESDK_PSP2KERN_KERNEL_IOFILEMGR_H_
#define _DOLCESDK_PSP2KERN_KERNEL_IOFILEMGR_H_

#include_next <kernel/iofilemgr.h>

#include <kernel/iofilemgr_async.h>

#ifdef __cplusplus
extern "C" {
#endif

/*--------------------Async IO--------------------*/

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

/*--------------------IO Priority--------------------*/

/*Valid priority values range: 1 (highest) - 15 (lowest). Default priority value is 14*/

/**
 * Set IO operations priority for file descriptor for non-game application
 *
 * @param fd - File UID
 * @param priority - IO operations priority
 *
 * @return < 0 on error.
 */
int sceIoSetPriorityForSystem(SceUID fd, int priority);

/**
 * Get IO operations priority for file descriptor for non-game application
 *
 * @param fd - File UID
 *
 * @return A non-negative integer is a valid priority, anything else an error
 */
int sceIoGetPriorityForSystem(SceUID fd);

/**
 * Set IO operations priority for caller process (will be default for all new IO operations)
 *
 * @param priority - New default IO operations priority
 *
 * @return < 0 on error.
 */
int sceIoSetProcessDefaultPriorityForSystem(int priority);

/**
 * Get IO operations priority for process
 *
 * @return A non-negative integer is a valid priority, anything else an error
 */
int sceIoGetProcessDefaultPriorityForSystem(void);

/**
 * Set IO operations priority for caller thread for non-game
 * application (will be default for all new IO operations)
 *
 * @param priority - New default IO operations priority
 *
 * @return < 0 on error.
 */
int sceIoSetThreadDefaultPriorityForSystem(int priority);

/**
 * Get IO operations priority for thread for non-game application
 *
 * @return A non-negative integer is a valid priority, anything else an error
 */
int sceIoGetThreadDefaultPriorityForSystem(void);

/*--------------------Device mount functions--------------------*/

/**
  * Mounts a device
  *
  * @param[in]  id          Device to mount
  * @param[in]  path        Where to mount to
  * @param[in]  permission  Permission flags
  * @param      a4          Unknown, set to 0
  * @param      a5          Unknown, set to 0
  * @param      a6          Unknown, set to 0
  *
  * @return < 0 on error.
  */
int sceIoMount(int id, const char *path, int permission, int a4, int a5, int a6);

/**
  * Unmounts a device
  *
  * @param[in]  id    Device to unmount
  * @param[in]  a2    Unknown, set to 0
  * @param[in]  a3    Unknown, set to 0
  * @param[in]  a4    Unknown, set to 0
  *
  * @return < 0 on error.
  */
int sceIoUmount(int id, int a2, int a3, int a4);

#ifdef __cplusplus
}
#endif

#endif	/* _DOLCESDK_PSP2KERN_KERNEL_IOFILEMGR_H_ */

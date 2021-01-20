#ifndef _DOLCESDK_PSP2KERN_KERNEL_IOFILEMGR_DIRENT_H_
#define _DOLCESDK_PSP2KERN_KERNEL_IOFILEMGR_DIRENT_H_

#include_next <kernel/iofilemgr_dirent.h>

#include <kernel/iofilemgr_async.h>

#ifdef __cplusplus
extern "C" {
#endif

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

#ifdef __cplusplus
}
#endif

#endif	/* _DOLCESDK_PSP2KERN_KERNEL_IOFILEMGR_DIRENT_H_ */

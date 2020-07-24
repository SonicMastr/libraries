#ifndef _DOLCESDK_PSP2KERN_KERNEL_IOFILEMGR_STAT_H_
#define _DOLCESDK_PSP2KERN_KERNEL_IOFILEMGR_STAT_H_

#include <psp2common/kernel/iofilemgr/stat.h>
#include <psp2kern/kernel/iofilemgr/async.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
  * Change the status of a file.
  *
  * @param name - The path to the file.
  * @param buf - A pointer to a ::SceIoStat structure.
  * @param cbit - Bitmask defining which bits to change.
  *
  * @return < 0 on error.
  */
int sceIoChstat(const char *name, const SceIoStat *buf, unsigned int cbit);

/**
  * Get the status of a file.
  *
  * @param name - The path to the file.
  * @param buf - A pointer to a ::SceIoStat structure.
  *
  * @return < 0 on error.
  */
int sceIoGetstat(const char *name, SceIoStat *buf);

/**
  * Get the status of a file descriptor.
  *
  * @param fd - The file descriptor.
  * @param buf - A pointer to a ::SceIoStat structure.
  *
  * @return < 0 on error.
  */
int sceIoGetstatByFd(SceUID fd, SceIoStat *buf);

/**
  * Change the status of a file descriptor.
  *
  * @param fd - The file descriptor.
  * @param buf - A pointer to an io_stat_t structure.
  * @param cbit - Bitmask defining which bits to change.
  *
  * @return < 0 on error.
  */
int sceIoChstatByFd(SceUID fd, const SceIoStat *buf, unsigned int cbit);

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

#ifdef __cplusplus
}
#endif

#endif	/* _DOLCESDK_PSP2KERN_KERNEL_IOFILEMGR_STAT_H_ */

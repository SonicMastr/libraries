#ifndef _DOLCESDK_PSP2KERN_KERNEL_IOFILEMGR_STAT_H_
#define _DOLCESDK_PSP2KERN_KERNEL_IOFILEMGR_STAT_H_

#include <psp2kern/kernel/types.h>
#include <psp2kern/kernel/iofilemgr/async.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Filetypes and Protection bits */
#define SCE_STM_FMT         (0xf << 12)
#define SCE_STM_FREG        (0x2 << 12)    /* regular file */
#define SCE_STM_FDIR        (0x1 << 12)    /* directory */
#define SCE_STM_ISREG(m)    (((m) & SCE_STM_FMT) == SCE_STM_FREG)
#define SCE_STM_ISDIR(m)    (((m) & SCE_STM_FMT) == SCE_STM_FDIR)

/* for SceMode */
#define SCE_STM_RWU         00600
#define SCE_STM_RU          00400

/* for chstat cbit */
#define SCE_CST_MODE        0x0001
#define SCE_CST_ATTR        0x0000    /* not supported */
#define SCE_CST_SIZE        0x0004
#define SCE_CST_CT          0x0008
#define SCE_CST_AT          0x0010
#define SCE_CST_MT          0x0020

/**
 * See sceIoChstat(), sceIoGetstat(), sceIoChstatByFd(), sceIoGetstatByFd()
 */
typedef struct SceIoStat {
	SceIoMode    st_mode;        //!< File access mode
	unsigned int st_attr;        //!< Device-specific attribute
	SceOff       st_size;        //!< File size
	SceDateTime  st_ctime;       //!< File creation time
	SceDateTime  st_atime;       //!< File last accessed time
	SceDateTime  st_mtime;       //!< File last modified time
	unsigned int st_private[6];  //!< Reserved
} SceIoStat;

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

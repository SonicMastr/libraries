#ifndef _DOLCESDK_PSP2COMMON_KERNEL_IOFILEMGR_STAT_H_
#define _DOLCESDK_PSP2COMMON_KERNEL_IOFILEMGR_STAT_H_

#include <psp2common/kernel/types.h>

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

#ifdef __cplusplus
}
#endif

#endif	/* _DOLCESDK_PSP2COMMON_KERNEL_IOFILEMGR_STAT_H_ */

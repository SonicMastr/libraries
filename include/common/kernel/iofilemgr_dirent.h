#ifndef _DOLCESDK_PSP2COMMON_KERNEL_IOFILEMGR_DIRENT_H_
#define _DOLCESDK_PSP2COMMON_KERNEL_IOFILEMGR_DIRENT_H_

#include <psp2common/kernel/types.h>
#include <psp2common/kernel/iofilemgr/stat.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Describes a single directory entry */
typedef struct SceIoDirent {
	SceIoStat d_stat;      //!< File status
	char      d_name[256]; //!< File name (not file path)
	void      *d_private;  //!< Reserved (set to 0)
	int       dummy;       //!< Padding
} SceIoDirent;

#ifdef __cplusplus
}
#endif

#endif	/* _DOLCESDK_PSP2COMMON_KERNEL_IOFILEMGR_DIRENT_H_ */

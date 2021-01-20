#ifndef _DOLCESDK_PSP2COMMON_KERNEL_IOFILEMGR_H_
#define _DOLCESDK_PSP2COMMON_KERNEL_IOFILEMGR_H_

#include_next <kernel/iofilemgr.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * May be used with sceIoDevctl()
 */
typedef struct SceIoDevInfo {
  SceOff max_size;
  SceOff free_size;
  SceSize cluster_size;
  void *unk;
} SceIoDevInfo;

#ifdef __cplusplus
}
#endif

#endif	/* _DOLCESDK_PSP2COMMON_KERNEL_IOFILEMGR_H_ */

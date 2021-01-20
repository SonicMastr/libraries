#ifndef _DOLCESDK_PSP2COMMON_KERNEL_IOFILEMGR_ASYNC_H_
#define _DOLCESDK_PSP2COMMON_KERNEL_IOFILEMGR_ASYNC_H_

#include <kernel/threadmgr.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceIoAsyncParam {
  int result; // [out] result of the IO operation (e.g. UID, read/wrote size, error code)
  int unk_04; // [out]
  int unk_08; // [in]
  int unk_0C; // [out]
  int unk_10; // [out]
  int unk_14; // [out]
} SceIoAsyncParam;

#ifdef __cplusplus
}
#endif

#endif	/* _DOLCESDK_PSP2COMMON_KERNEL_IOFILEMGR_ASYNC_H_ */

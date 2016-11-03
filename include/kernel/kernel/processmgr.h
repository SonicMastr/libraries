#ifndef _PSP2_KERNEL_PROCESSMGR_H_
#define _PSP2_KERNEL_PROCESSMGR_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

void *sceKernelGetProcessKernelBuf(SceUID pid);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_PROCESSMGR_H_ */

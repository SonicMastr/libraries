/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_USER_KERNEL_SYSMEM_H
#define _VDSUITE_USER_KERNEL_SYSMEM_H

#include_next <kernel/sysmem.h>

SCE_CDECL_BEGIN

typedef enum SceKernelModel {
	SCE_KERNEL_MODEL_VITA   = 0x10000,
	SCE_KERNEL_MODEL_VITATV = 0x20000
} SceKernelModel;

SceUID sceKernelAllocMemBlockForVM(const char *name, SceSize size);
int sceKernelSyncVMDomain(SceUID uid, void *data, SceSize size);
int sceKernelOpenVMDomain(void);
int sceKernelCloseVMDomain(void);

int sceKernelOpenMemBlock(const char *name, int flags);
int sceKernelCloseMemBlock(SceUID uid);

/**
 * Get the model number of the device
 *
 * @return A value from SCE_KERNEL_MODEL
*/
int sceKernelGetModelForCDialog(void);

/**
 * Get the model number of the device
 *
 * @return A value from SCE_KERNEL_MODEL
*/
int sceKernelGetModel(void);

int sceKernelIsPSVitaTV(void);

SCE_CDECL_END

#endif /* _VDSUITE_USER_KERNEL_SYSMEM_H */


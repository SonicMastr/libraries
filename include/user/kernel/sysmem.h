#ifndef _PSP2_KERNEL_SYSMEM_H_
#define _PSP2_KERNEL_SYSMEM_H_

#include <psp2/kernel/sysmem/memblock.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceKernelFreeMemorySizeInfo {
	int size;         //!< sizeof(SceKernelFreeMemorySizeInfo)
	int size_user;    //!< Free memory size for *_USER_RW memory
	int size_cdram;   //!< Free memory size for USER_CDRAM_RW memory
	int size_phycont; //!< Free memory size for USER_MAIN_PHYCONT_*_RW memory
} SceKernelFreeMemorySizeInfo;

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

/**
 * Get free memory size in bytes
 *
 * @param[out] info - Returned free memory size for different kind of memory block types
 * @return 0 on success, < 0 on error.
*/
int sceKernelGetFreeMemorySize(SceKernelFreeMemorySizeInfo *info);

int sceKernelIsPSVitaTV(void);

#ifdef __cplusplus
}
#endif

#endif


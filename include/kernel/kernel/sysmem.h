#ifndef _PSP2_KERNEL_SYSMEM_H_
#define _PSP2_KERNEL_SYSMEM_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int SceKernelMemBlockType;

enum {
  SCE_KERNEL_MEMBLOCK_TYPE_USER_RW  = 0x0c20d060,
  SCE_KERNEL_MEMBLOCK_TYPE_USER_RW_UNCACHE  = 0x0c208060,
  SCE_KERNEL_MEMBLOCK_TYPE_USER_MAIN_PHYCONT_RW = 0x0c80d060,
  SCE_KERNEL_MEMBLOCK_TYPE_USER_MAIN_PHYCONT_NC_RW  = 0x0d808060,
  SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW  = 0x09408060,
  SCE_KERNEL_MEMBLOCK_TYPE_KERNEL_RX = 0x1020D005,
  SCE_KERNEL_MEMBLOCK_TYPE_KERNEL_RW = 0x1020D006,
  SCE_KERNEL_MEMBLOCK_TYPE_SHARED_RX = 0x390D050,
  SCE_KERNEL_MEMBLOCK_TYPE_USER_RX = 0xC20D050,
  SCE_KERNEL_MEMBLOCK_TYPE_RW_UNK0 = 0x6020D006
};

// specific to 3.60
typedef struct SceKernelAllocMemBlockKernelOpt {
  SceSize size;
  SceUInt32 field_4;
  SceUInt32 attr;
  SceUInt32 field_C;
  SceUInt32 paddr;
  SceSize alignment;
  SceUInt32 field_18;
  SceUInt32 field_1C;
  SceUInt32 mirror_blkid;
  SceUID pid;
  SceUInt32 field_28;
  SceUInt32 field_2C;
  SceUInt32 field_30;
  SceUInt32 field_34;
  SceUInt32 field_38;
  SceUInt32 field_3C;
  SceUInt32 field_40;
  SceUInt32 field_44;
  SceUInt32 field_48;
  SceUInt32 field_4C;
  SceUInt32 field_50;
  SceUInt32 field_54;
} SceKernelAllocMemBlockKernelOpt;

typedef struct SceKernelHeapCreateOpt {
  SceSize size;
  SceUInt32 uselock;
  SceUInt32 field_8;
  SceUInt32 field_C;
  SceUInt32 field_10;
  SceUInt32 field_14;
  SceUInt32 field_18;
} SceKernelHeapCreateOpt;

typedef struct SceCreateUidObjOpt {
  SceUInt32 flags;
  SceUInt32 field_4;
  SceUInt32 field_8;
  SceUInt32 pid;
  SceUInt32 field_10;
  SceUInt32 field_14;
  SceUInt32 field_18;
} SceCreateUidObjOpt;

enum {
  SCE_KERNEL_MODEL_VITA = 0x10000,
  SCE_KERNEL_MODEL_VITATV = 0x20000
};

#define SCE_KERNEL_ALLOC_MEMBLOCK_ATTR_HAS_ALIGNMENT    0x00000004U

/***
 * Allocates a new memory block
 *
 * @param[in] name - Name for the memory block
 * @param[in] type - Type of the memory to allocate
 * @param[in] size - Size of the memory to allocate
 * @param[in] optp - Memory block options?
 *
 * @return SceUID of the memory block on success, < 0 on error.
*/
SceUID sceKernelAllocMemBlock(const char *name, SceKernelMemBlockType type, int size, SceKernelAllocMemBlockKernelOpt *optp);

/***
 * Frees new memory block
 *
 * @param[in] uid - SceUID of the memory block to free
 *
 * @return 0 on success, < 0 on error.
*/
int sceKernelFreeMemBlock(SceUID uid);

/***
 * Gets the base address of a memory block
 *
 * @param[in] uid - SceUID of the memory block to free
 * @param[out] basep - Base address of the memory block identified by SceUID
 *
 * @return 0 on success, < 0 on error.
*/
int sceKernelGetMemBlockBase(SceUID uid, void **basep);

/**
 * Changes the block type
 *
 * @param[in] uid - SceUID of the memory block to change
 * @param[in] type - Type of the memory to change to
 *
 * @return 0 on success, < 0 on error.
 */
int sceKernelRemapBlock(SceUID uid, SceKernelMemBlockType type);

SceUID sceKernelCreateHeap(const char *name, SceSize size, SceKernelHeapCreateOpt *opt);
int sceKernelDeleteHeap(SceUID uid);
void *sceKernelAllocHeapMemory(SceUID uid, SceSize size);
void sceKernelFreeHeapMemory(SceUID uid, void *ptr);

int sceKernelMemcpyUserToKernelForPid(SceUID pid, void *dst, uintptr_t src, size_t len);
int sceKernelMemcpyUserToKernel(void *dst, uintptr_t src, size_t len);
int sceKernelMemcpyKernelToUser(uintptr_t dst, const void *src, size_t len);
int sceKernelRxMemcpyKernelToUserForPid(SceUID pid, uintptr_t dst, const void *src, size_t len);

int sceKernelStrncpyUserToKernel(void *dst, uintptr_t src, size_t len);
int sceKernelStrncpyKernelToUser(uintptr_t dst, const void *src, size_t len);
int sceKernelStrncpyUserForPid(SceUID pid, void *dst, uintptr_t src, size_t len);

typedef struct {
  char data[0x2C];
} SceClass;

typedef struct {
  uint32_t sce_reserved[2];
} SceObjectBase;

SceUID sceKernelKernelUidForUserUid(SceUID pid, SceUID user_uid);
SceUID sceKernelCreateUserUid(SceUID pid, SceUID kern_uid);
SceUID sceKernelCreateUidObj(SceClass *cls, const char *name, SceCreateUidObjOpt *opt, SceObjectBase **obj);

/**
 * Gets an object from a UID.
 * 
 * This retains the object internally! You must call `sceKernelUidRelease` 
 * after you are done using it.
 *
 * @param[in]  uid   The uid
 * @param      cls   The class
 * @param      obj   The object
 *
 * @return 0 on success, < 0 on error.
 */
int sceKernelGetObjForUid(SceUID uid, SceClass *cls, SceObjectBase **obj);

/**
 * Retains an object referenced by the UID.
 * 
 * This increases the internal reference count.
 *
 * @param[in]  uid   The uid
 *
 * @return 0 on success, < 0 on error.
 */
int sceKernelUidRetain(SceUID uid);

/**
 * Releases an object referenced by the UID.
 * 
 * This decreases the internal reference count.
 *
 * @param[in]  uid   The uid
 *
 * @return 0 on success, < 0 on error.
 */
int sceKernelUidRelease(SceUID uid);

SceClass *sceKernelGetUidClass(void);
typedef int (*SceClassCallback)(void *item);
int sceKernelCreateClass(SceClass *cls, const char *name, void *uidclass, size_t itemsize, SceClassCallback create, SceClassCallback destroy);
int sceKernelDeleteUserUid(SceUID pid, SceUID user_uid);
int sceKernelDeleteUid(SceUID uid);

int sceKernelSwitchVmaForPid(SceUID pid);

void *sceKernelGetSysrootBuffer(void);
int sceKernelGetPidContext(SceUID pid, int **ctx);

int sceKernelGetProcessTitleId(SceUID pid, char *titleid, size_t len);

int sceKernelMapBlockUserVisible(SceUID uid);

int sceKernelGetPaddr(void *addr, uintptr_t *paddr);

int sceSysrootIsManufacturingMode(void);

#ifdef __cplusplus
}
#endif

#endif


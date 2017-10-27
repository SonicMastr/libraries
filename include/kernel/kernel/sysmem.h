#ifndef _PSP2_KERNEL_SYSMEM_H_
#define _PSP2_KERNEL_SYSMEM_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceKernelMemBlockType {
	SCE_KERNEL_MEMBLOCK_TYPE_SHARED_RX                = 0x0390D050,
	SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW            = 0x09408060,
	SCE_KERNEL_MEMBLOCK_TYPE_USER_RW_UNCACHE          = 0x0C208060,
	SCE_KERNEL_MEMBLOCK_TYPE_USER_RX                  = 0x0C20D050,
	SCE_KERNEL_MEMBLOCK_TYPE_USER_RW                  = 0x0C20D060,
	SCE_KERNEL_MEMBLOCK_TYPE_USER_MAIN_PHYCONT_RW     = 0x0C80D060,
	SCE_KERNEL_MEMBLOCK_TYPE_USER_MAIN_PHYCONT_NC_RW  = 0x0D808060,
	SCE_KERNEL_MEMBLOCK_TYPE_KERNEL_RX                = 0x1020D005,
	SCE_KERNEL_MEMBLOCK_TYPE_KERNEL_RW                = 0x1020D006,
	SCE_KERNEL_MEMBLOCK_TYPE_RW_UNK0                  = 0x6020D006
} SceKernelMemBlockType;

#define SCE_KERNEL_ALLOC_MEMBLOCK_ATTR_HAS_PADDR            0x00000002U
#define SCE_KERNEL_ALLOC_MEMBLOCK_ATTR_HAS_ALIGNMENT        0x00000004U
#define SCE_KERNEL_ALLOC_MEMBLOCK_ATTR_HAS_MIRROR_BLOCKID   0x00000040U
#define SCE_KERNEL_ALLOC_MEMBLOCK_ATTR_HAS_PID              0x00000080U

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

typedef enum SceKernelModel {
	SCE_KERNEL_MODEL_VITA   = 0x10000,
	SCE_KERNEL_MODEL_VITATV = 0x20000
} SceKernelModel;

typedef struct SceClass {
	char data[0x2C];
} SceClass;

typedef struct SceObjectBase {
	uint32_t sce_reserved[2];
	uint32_t data[];
} SceObjectBase;

typedef struct SceKernelAddrPair {
	uint32_t addr;                  //!< Address
	uint32_t length;                //!< Length
} SceKernelAddrPair;

typedef struct SceKernelPaddrList {
	uint32_t size;                  //!< sizeof(SceKernelPaddrList)
	uint32_t list_size;             //!< Size in elements of the list array
	uint32_t ret_length;            //!< Total physical size of the memory pairs
	uint32_t ret_count;             //!< Number of elements of list filled by sceKernelGetPaddrList
	SceKernelAddrPair *list;        //!< Array of physical addresses and their lengths pairs
} SceKernelPaddrList;

typedef struct SceKernelProcessContext {
	SceUInt32 TTBR1;
	SceUInt32 DACR;
	SceUInt32 CONTEXTIDR;
} SceKernelProcessContext;

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

/***
 * Find the SceUID of a memory block
 *
 * @param[in] addr - Base address of the memory block
 * @param[in] size - Size to search for (usally set to 0)
 *
 * @return SceUID of the memory block on success, < 0 on error.
*/
SceUID sceKernelFindMemBlockByAddr(const void *addr, SceSize size);

/***
 * Find the SceUID of a memory block for a PID
 *
 * @param[in] pid - PID of the process
 * @param[in] addr - Base address of the memory block
 * @param[in] size - Size to search for (usally set to 0)
 *
 * @return SceUID of the memory block on success, < 0 on error.
*/
SceUID sceKernelFindMemBlockByAddrForPid(SceUID pid, const void *addr, SceSize size);

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
int sceKernelGetPidContext(SceUID pid, SceKernelProcessContext **ctx);

int sceKernelGetProcessTitleId(SceUID pid, char *titleid, size_t len);

int sceKernelMapBlockUserVisible(SceUID uid);

/**
 * Get the physical address of a given virtual address
 *
 * @param[in] addr - The virtual address
 * @param[out] paddr - The physical address
 *
 * @return 0 on success, < 0 on error.
 */
int sceKernelGetPaddr(void *addr, uintptr_t *paddr);

/**
 * Get the physical address list of a given virtual address range
 *
 * @param[in] input - The virtual address range
 * @param[out] list - The list of physical addresses
 *
 * @return 0 on success, < 0 on error.
 */
int sceKernelGetPaddrList(const SceKernelAddrPair *input, SceKernelPaddrList *list);

int sceSysrootIsManufacturingMode(void);

int sceDebugPrintf(const char *fmt, ...);

int sceDebugPrintf2(int unk0, int unk1, const char *fmt, ...);

int sceDebugSetHandlers(int (*func)(void *args, char c), void *args);

int sceDebugRegisterPutcharHandler(int (*func)(void *args, char c), void *args);

void *sceDebugGetPutcharHandler(void);

int sceDebugPutchar(int character);

#ifdef __cplusplus
}
#endif

#endif


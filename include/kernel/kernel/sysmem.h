/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_KERNEL_KERNEL_SYSMEM_H
#define _VDSUITE_KERNEL_KERNEL_SYSMEM_H

#include_next <kernel/sysmem.h>

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SCE_KERNEL_MEMBLOCK_TYPE_SHARED_RX                 0x0390D050
#define SCE_KERNEL_MEMBLOCK_TYPE_USER_RX                   0x0C20D050
#define SCE_KERNEL_MEMBLOCK_TYPE_KERNEL_RX                 0x1020D005
#define SCE_KERNEL_MEMBLOCK_TYPE_KERNEL_RW                 0x1020D006
#define SCE_KERNEL_MEMBLOCK_TYPE_RW_UNK0                   0x6020D006

typedef enum SceKernelAllocMemBlockAttr {
	SCE_KERNEL_ALLOC_MEMBLOCK_ATTR_HAS_PADDR          = 0x00000002U,
	SCE_KERNEL_ALLOC_MEMBLOCK_ATTR_HAS_MIRROR_BLOCKID = 0x00000040U,
	SCE_KERNEL_ALLOC_MEMBLOCK_ATTR_HAS_PID            = 0x00000080U,
	SCE_KERNEL_ALLOC_MEMBLOCK_ATTR_HAS_PADDR_LIST     = 0x00001000U,
	SCE_KERNEL_ALLOC_MEMBLOCK_ATTR_ALLOW_PARTIAL_OP   = 0x04000000U
} SceKernelAllocMemBlockAttr;

typedef enum SceKernelMemoryRefPerm {
	SCE_KERNEL_MEMORY_REF_PERM_ANY		= 0,
	SCE_KERNEL_MEMORY_REF_PERM_USER_R	= 0x01,
	SCE_KERNEL_MEMORY_REF_PERM_USER_W	= 0x02,
	SCE_KERNEL_MEMORY_REF_PERM_USER_X	= 0x04,
	SCE_KERNEL_MEMORY_REF_PERM_KERN_R	= 0x10,
	SCE_KERNEL_MEMORY_REF_PERM_KERN_W	= 0x20,
	SCE_KERNEL_MEMORY_REF_PERM_KERN_X	= 0x40,
} SceKernelMemoryRefPerm;

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

// specific to 3.60
typedef struct SceKernelAllocMemBlockKernelOpt {
	SceSize size;                   //!< sizeof(SceKernelAllocMemBlockKernelOpt)
	SceUInt32 field_4;
	SceUInt32 attr;                 //!< OR of SceKernelAllocMemBlockAttr
	SceUInt32 field_C;
	SceUInt32 paddr;
	SceSize alignment;
	SceUInt32 extraLow;
	SceUInt32 extraHigh;
	SceUInt32 mirror_blockid;
	SceUID pid;
	SceKernelPaddrList *paddr_list;
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

#define SCE_KERNEL_CREATE_HEAP_FLAG_AUTO_EXTEND				(1 << 0)
#define SCE_KERNEL_CREATE_HEAP_FLAG_1						(1 << 1)
#define SCE_KERNEL_CREATE_HEAP_FLAG_4						(1 << 4)
#define SCE_KERNEL_CREATE_HEAP_FLAG_WITH_MAX_SIZE			(1 << 8)
#define SCE_KERNEL_CREATE_HEAP_FLAG_WITH_BASE				(1 << 9)
#define SCE_KERNEL_CREATE_HEAP_FLAG_WITH_MEMORY_TYPE		(1 << 10)
#define SCE_KERNEL_CREATE_HEAP_FLAG_11						(1 << 11)
#define SCE_KERNEL_CREATE_HEAP_FLAG_12						(1 << 12)
// All other flags are invalid

typedef struct SceKernelHeapCreateOpt {
	SceSize size;
	SceUInt32 flags;
	SceUInt32 maxSize;
	void *pBase;
	SceKernelMemoryType memoryType;
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

typedef int (* SceClassCallback)(void *item);

typedef struct SceClass {
	struct SceClass *next;
	struct SceClass *root;
	struct SceClass *prev;
	const char *name;
	struct SceClass *uidclass;
	unsigned int attributes;
	unsigned short itemsize;
	unsigned short unk1A;
	unsigned int unk1C;
	SceClassCallback create_cb;
	SceClassCallback destroy_cb;
	unsigned int magic; /* 0xABCE9DA5 */
} SceClass; /* size = 0x2C */

typedef struct SceObjectBase {
	uint32_t sce_reserved[2];
	uint32_t data[];
} SceObjectBase;

typedef struct SceKernelProcessContext {
	SceUInt32 TTBR1;
	SceUInt32 DACR;
	SceUInt32 CONTEXTIDR;
} SceKernelProcessContext;

typedef enum SceKernelSysrootSelfIndex {
	SCE_KERNEL_SYSROOT_SELF_INDEX_GCAUTHMGR_SM		= 0,
	SCE_KERNEL_SYSROOT_SELF_INDEX_RMAUTH_SM			= 1,
	SCE_KERNEL_SYSROOT_SELF_INDEX_ENCDEC_W_PORTABILITY_SM	= 2
} SceKernelSysrootSelfIndex;

typedef struct SceKernelSysrootSelfInfo {
	uint32_t size;
	void *self_data;
	uint32_t self_size;
} SceKernelSysrootSelfInfo;

/**
 * Gets the memory block type of a memory block
 *
 * @param[in] uid - SceUID of the memory block
 * @param[out] type - Type of the memory block identified by uid
 *
 * @return 0 on success, < 0 on error.
*/
int sceKernelGetMemBlockType(SceUID uid, unsigned int *type);

/**
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

int sceKernelMemcpyUserToKernelForPid(SceUID pid, void *dst, uintptr_t src, SceSize len);
int sceKernelMemcpyUserToKernel(void *dst, uintptr_t src, SceSize len);
int sceKernelMemcpyKernelToUser(uintptr_t dst, const void *src, SceSize len);
int sceKernelRxMemcpyKernelToUserForPid(SceUID pid, uintptr_t dst, const void *src, SceSize len);

int sceKernelStrncpyUserToKernel(void *dst, uintptr_t src, SceSize len);
int sceKernelStrncpyKernelToUser(uintptr_t dst, const void *src, SceSize len);
int sceKernelStrncpyUserForPid(SceUID pid, void *dst, uintptr_t src, SceSize len);

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
SceClass *sceKernelGetUidDLinkClass(void);
SceClass *sceKernelGetUidHeapClass(void);
SceClass *sceKernelGetUidMemBlockClass(void);

int sceKernelCreateClass(SceClass *cls, const char *name, void *uidclass, SceSize itemsize, SceClassCallback create, SceClassCallback destroy);
int sceKernelDeleteUserUid(SceUID pid, SceUID user_uid);
int sceKernelDeleteUid(SceUID uid);
int sceKernelFindClassByName(const char *name, SceClass **cls);

void *sceKernelGetSysrootBuffer(void);
int sceKernelGetPidContext(SceUID pid, SceKernelProcessContext **ctx);
int sceKernelSwitchPidContext(SceKernelProcessContext *ctx, SceKernelProcessContext *current_ctx);

int sceKernelGetProcessTitleId(SceUID pid, char *titleid, SceSize len);

int sceKernelMapBlockUserVisible(SceUID uid);
int sceKernelMapUserBlock(const char *name, int permission, int type,
			   const void *user_buf, SceSize size, void **kernel_page,
			   SceSize *kernel_size, unsigned int *kernel_offset);
int sceKernelMapUserBlockDefaultType(const char *name, int permission, const void *user_buf,
				      SceSize size, void **kernel_page,
				      SceSize *kernel_size, unsigned int *kernel_offset);
int sceKernelMapUserBlockDefaultTypeForPid(int pid, const char *name, int permission,
					    const void *user_buf, SceSize size, void **kernel_page,
					    SceSize *kernel_size, unsigned int *kernel_offset);

int sceSysrootGetSelfInfo(SceKernelSysrootSelfIndex index, SceKernelSysrootSelfInfo *info);

/**
 * Get the physical address of a given virtual address
 *
 * @param[in] addr - The virtual address
 * @param[out] paddr - The physical address
 *
 * @return 0 on success, < 0 on error.
 */
int sceKernelGetPaddr(const void *addr, uintptr_t *paddr);

/**
 * Get the physical address list of a given virtual address range
 *
 * @param[in] input - The virtual address range
 * @param[out] list - The list of physical addresses
 *
 * @return 0 on success, < 0 on error.
 */
int sceKernelGetPaddrList(const SceKernelAddrPair *input, SceKernelPaddrList *list);

/**
 * Releases a memblock referenced by the UID.
 *
 * This decreases the internal reference count.
 *
 * @param[in]  uid   The uid of the memblock
 *
 * @return 0 on success, < 0 on error.
 */
int sceKernelMemBlockRelease(SceUID uid);

/**
 * Retains a memory range
 *
 * This increases the internal reference count of the memblocks belonging to the range.
 *
 * Note: It uses ::SCE_KERNEL_MEMORY_REF_PERM_ANY as the reference permission.
 *
 * @param[in]  addr   The start address
 * @param[in]  size   The memory range size
 *
 * @return 0 on success, < 0 on error.
 */
int sceKernelMemRangeRetain(void *addr, SceSize size);

/**
 * Retains a memory range for a process (pid)
 *
 * This increases the internal reference count of the memblocks belonging to the range.
 *
 * Note: It uses ::SCE_KERNEL_MEMORY_REF_PERM_ANY as the reference permission.
 *
 * @param[in]  pid    The pid of the process
 * @param[in]  addr   The start address
 * @param[in]  size   The memory range size
 *
 * @return 0 on success, < 0 on error.
 */
int sceKernelMemRangeRetainForPid(SceUID pid, void *addr, SceSize size);

/**
 * Retains a memory range checking for a given permission
 *
 * This increases the internal reference count of the memblocks belonging to the range.
 * If the memory blocks belonging to the range don't have the required memory access permission,
 * it returns an error.
 *
 * @param[in]  perm   The required permission of the memory blocks belonging to the range
 * @param[in]  addr   The start address
 * @param[in]  size   The memory range size
 *
 * @return 0 on success, < 0 on error.
 */
int sceKernelMemRangeRetainWithPerm(SceKernelMemoryRefPerm perm, void *addr, SceSize size);

/**
 * Releases a memory range
 *
 * This decreases the internal reference count of the memblocks belonging to the range.
 *
 * Note: It uses ::SCE_KERNEL_MEMORY_REF_PERM_ANY as the reference permission.
 *
 * @param[in]  addr   The start address
 * @param[in]  size   The memory range size
 *
 * @return 0 on success, < 0 on error.
 */
int sceKernelMemRangeRelease(void *addr, SceSize size);

/**
 * Releases a memory range for a process (pid)
 *
 * This decreases the internal reference count of the memblocks belonging to the range.
 *
 * Note: It uses ::SCE_KERNEL_MEMORY_REF_PERM_ANY as the reference permission.
 *
 * @param[in]  pid    The pid of the process
 * @param[in]  addr   The start address
 * @param[in]  size   The memory range size
 *
 * @return 0 on success, < 0 on error.
 */
int sceKernelMemRangeReleaseForPid(SceUID pid, void *addr, SceSize size);

/**
 * Releases a memory range checking for a given permission
 *
 * This decreases the internal reference count of the memblocks belonging to the range.
 * If the memory blocks belonging to the range don't have the required memory access permission,
 * it returns an error.
 *
 * @param[in]  perm   The required permission of the memory blocks belonging to the range
 * @param[in]  addr   The start address
 * @param[in]  size   The memory range size
 *
 * @return 0 on success, < 0 on error.
 */
int sceKernelMemRangeReleaseWithPerm(SceKernelMemoryRefPerm perm, void *addr, SceSize size);

int sceSysrootUseExternalStorage(void);

#define sceSysrootIsManufacturingMode() sceSysrootUseExternalStorage()

int sceSysrootUseInternalStorage(void);

__attribute__((__format__(__printf__, 1, 2)))
int sceDebugPrintf(const char *fmt, ...);

typedef struct SceKernelDebugMessageContext {
  int hex_value0_hi;
  int hex_value0_lo;
  int hex_value1;
  char *msg0;
  SceSize num;
  char *msg1;
} SceKernelDebugMessageContext;

// msg_type_flag : 0 or 0xB
__attribute__((__format__(__printf__, 3, 4)))
int sceDebugPrintf2(int msg_type_flag, const SceKernelDebugMessageContext *ctx, const char *fmt, ...);

int sceDebugVprintf(const char *fmt, va_list args);

int sceDebugPrintKernelPanic(const SceKernelDebugMessageContext *ctx, void *some_address);

__attribute__((__format__(__printf__, 3, 4)))
int sceDebugPrintfKernelPanic(const SceKernelDebugMessageContext *ctx, void *some_address, const char *fmt, ...);

int sceDebugPrintKernelAssertion(int condition, const SceKernelDebugMessageContext *ctx, void *some_address);

__attribute__((__format__(__printf__, 5, 6)))
int sceDebugPrintfKernelAssertion(int unk, int condition, const SceKernelDebugMessageContext *ctx, int some_address, const char *fmt, ...);

int sceDebugSetHandlers(int (*func)(int unk, const char *format, const va_list args), void *args);

int sceDebugRegisterPutcharHandler(int (*func)(void *args, char c), void *args);

void *sceDebugGetPutcharHandler(void);

int sceDebugPutchar(int character);

int sceDebugDisableInfoDump(int flag);

typedef struct
{
    size_t size; //!< sizeof(SceSysrootProcessHandler)
    int (* unk_4)(void);
    int (* unk_8)(void);
    int (* unk_C)(void);
    int (* unk_10)(void);
    int (* unk_14)(void);
    int (* unk_18)(void);
    int (* on_process_created)(void); //!< called when process is created
    int (* unk_20)(void);
    int (* unk_24)(void);
} SceSysrootProcessHandler;

/**
 * Set handlers for the process lifecycle.
 *
 * This internal function allows a developer to introspect and receive events based
 * on the process lifecycle.
 *
 * @param[in]  handlers   Pointer to struct containing the handlers. This function does not copy the handlers, so this pointer must remain valid after a successful call.
 *
 * @return 0 on success, < 0 on error.
 */
int sceKernelSysrootSetProcessHandler(const SceSysrootProcessHandler *handlers);

/**
 * Get the process UID of shell.
 *
 * @return UID or -1 if shell is not started.
 */
SceUID sceKernelSysrootGetShellPid(void);

#ifdef __cplusplus
}
#endif

#endif /* _VDSUITE_KERNEL_KERNEL_SYSMEM_H */

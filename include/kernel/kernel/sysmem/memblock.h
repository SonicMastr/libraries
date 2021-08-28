/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_KERNEL_KERNEL_SYSMEM_MEMBLOCK_H
#define _VDSUITE_KERNEL_KERNEL_SYSMEM_MEMBLOCK_H

#include_next <kernel/sysmem/memblock.h>

#include <stdint.h>

SCE_CDECL_BEGIN

typedef enum SceKernelAllocMemBlockAttr {
	SCE_KERNEL_ALLOC_MEMBLOCK_ATTR_HAS_VBASE          = 0x00000001U,
	SCE_KERNEL_ALLOC_MEMBLOCK_ATTR_HAS_PBASE          = 0x00000002U,
	SCE_KERNEL_ALLOC_MEMBLOCK_ATTR_HAS_EXTRA_LOW      = 0x00000008U,
	SCE_KERNEL_ALLOC_MEMBLOCK_ATTR_HAS_EXTRA_HIGH     = 0x00000010U,
	SCE_KERNEL_ALLOC_MEMBLOCK_ATTR_HAS_MIRROR_BLOCKID = 0x00000040U,
	SCE_KERNEL_ALLOC_MEMBLOCK_ATTR_HAS_PID            = 0x00000080U,
	SCE_KERNEL_ALLOC_MEMBLOCK_ATTR_HAS_PVECTOR        = 0x00001000U,
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
	uint32_t ret_count;             //!< Number of elements of list filled by sceKernelVARangeToPAVector
	SceKernelAddrPair *list;        //!< Array of physical addresses and their lengths pairs
} SceKernelPaddrList;

// specific to 3.60
typedef struct SceKernelAllocMemBlockKernelOpt {
	SceSize size;                   //!< sizeof(SceKernelAllocMemBlockKernelOpt)
	SceUInt32 field_4;
	SceUInt32 attr;                 //!< OR of SceKernelAllocMemBlockAttr
	void *vbase;
	void *pbase;
	SceSize alignment;
	SceUInt32 extraLow;
	SceUInt32 extraHigh;
	SceUInt32 mirror_blockid;
	SceUID pid;
	SceKernelPaddrList *pVector;
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
SceUID sceKernelFindProcMemBlockByAddr(SceUID pid, const void *addr, SceSize size);

/**
 * Changes the block type
 *
 * @param[in] uid - SceUID of the memory block to change
 * @param[in] type - Type of the memory to change to
 *
 * @return 0 on success, < 0 on error.
 */
int sceKernelRemapBlock(SceUID uid, SceKernelMemBlockType type);

int sceKernelMapMemBlock(SceUID uid);

int sceKernelMapUserBlock(const char *name, int permission, int type,
	const void *user_buf, SceSize size, void **kernel_page,
	SceSize *kernel_size, unsigned int *kernel_offset);

int sceKernelUserMap(const char *name, int permission, const void *user_buf,
	SceSize size, void **kernel_page,
	SceSize *kernel_size, unsigned int *kernel_offset);

int sceKernelMapUserBlockDefaultTypeForPid(int pid, const char *name, int permission,
	const void *user_buf, SceSize size, void **kernel_page,
	SceSize *kernel_size, unsigned int *kernel_offset);

/**
 * Get the physical address of a given virtual address
 *
 * @param[in] addr - The virtual address
 * @param[out] paddr - The physical address
 *
 * @return 0 on success, < 0 on error.
 */
int sceKernelVAtoPA(const void *addr, uintptr_t *paddr);

/**
 * Get the physical address list of a given virtual address range
 *
 * @param[in] input - The virtual address range
 * @param[out] list - The list of physical addresses
 *
 * @return 0 on success, < 0 on error.
 */
int sceKernelVARangeToPAVector(const SceKernelAddrPair *input, SceKernelPaddrList *list);

/**
 * Releases a memblock referenced by the UID.
 *
 * This decreases the internal reference count.
 *
 * @param[in]  uid   The uid of the memblock
 *
 * @return 0 on success, < 0 on error.
 */
int sceKernelUserUnmap(SceUID uid);

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

int sceKernelIsAccessibleRangeProc(SceUID pid, SceKernelMemoryRefPerm perm, void *addr, SceSize size);

SCE_CDECL_END

#endif  /* _VDSUITE_KERNEL_KERNEL_SYSMEM_MEMBLOCK_H */

/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_KERNEL_KERNEL_SYSMEM_H
#define _VDSUITE_KERNEL_KERNEL_SYSMEM_H

#include_next <kernel/sysmem.h>

#include <kernel/sysmem/debug.h>
#include <kernel/sysmem/sysroot.h>

SCE_CDECL_BEGIN

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

SceUID sceKernelCreateHeap(const char *name, SceSize size, SceKernelHeapCreateOpt *opt);
int sceKernelDeleteHeap(SceUID uid);
void *sceKernelAllocHeapMemory(SceUID uid, SceSize size);
void sceKernelFreeHeapMemory(SceUID uid, void *ptr);

int sceKernelCopyFromUserProc(SceUID pid, void *dst, uintptr_t src, SceSize len);
int sceKernelCopyFromUser(void *dst, uintptr_t src, SceSize len);
int sceKernelCopyToUser(uintptr_t dst, const void *src, SceSize len);
int sceKernelCopyToUserProcTextDomain(SceUID pid, uintptr_t dst, const void *src, SceSize len);

int sceKernelStrncpyUserToKernel(void *dst, uintptr_t src, SceSize len);
int sceKernelStrncpyKernelToUser(uintptr_t dst, const void *src, SceSize len);
int sceKernelStrncpyUserForPid(SceUID pid, void *dst, uintptr_t src, SceSize len);

SceUID scePUIDtoGUID(SceUID pid, SceUID user_uid);
SceUID scePUIDOpenByGUID(SceUID pid, SceUID kern_uid);
SceUID sceKernelCreateUidObj(SceClass *cls, const char *name, SceCreateUidObjOpt *opt, SceObjectBase **obj);

/**
 * Gets an object from a UID.
 *
 * This retains the object internally! You must call `sceGUIDReleaseObject`
 * after you are done using it.
 *
 * @param[in]  uid   The uid
 * @param      cls   The class
 * @param      obj   The object
 *
 * @return 0 on success, < 0 on error.
 */
int sceGUIDReferObjectWithClass(SceUID uid, SceClass *cls, SceObjectBase **obj);

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
int sceGUIDReleaseObject(SceUID uid);

SceClass *sceKernelGetUidClass(void);
SceClass *sceKernelGetUidDLinkClass(void);
SceClass *sceKernelGetUidHeapClass(void);
SceClass *sceKernelGetUidMemBlockClass(void);

int sceKernelCreateClass(SceClass *cls, const char *name, void *uidclass, SceSize itemsize, SceClassCallback create, SceClassCallback destroy);
int scePUIDClose(SceUID pid, SceUID user_uid);
int sceGUIDClose(SceUID uid);
int sceKernelFindClassByName(const char *name, SceClass **cls);

int sceKernelGetPidContext(SceUID pid, SceKernelProcessContext **ctx);
int sceKernelSwitchPidContext(SceKernelProcessContext *ctx, SceKernelProcessContext *current_ctx);

SCE_CDECL_END

#endif /* _VDSUITE_KERNEL_KERNEL_SYSMEM_H */

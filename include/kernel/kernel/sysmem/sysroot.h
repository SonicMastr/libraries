/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_KERNEL_KERNEL_SYSMEM_SYSROOT_H
#define _VDSUITE_KERNEL_KERNEL_SYSMEM_SYSROOT_H

#include <stddef.h>
#include <stdint.h>

#include <cdefs.h>
#include <scetypes.h>

SCE_CDECL_BEGIN

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

void *sceKernelGetSysrootBuffer(void);

int sceKernelGetProcessTitleId(SceUID pid, char *titleid, SceSize len);

int sceSysrootGetSelfInfo(SceKernelSysrootSelfIndex index, SceKernelSysrootSelfInfo *info);

int sceSysrootUseExternalStorage(void);

int sceSysrootUseInternalStorage(void);

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

SCE_CDECL_END

#endif /* _VDSUITE_KERNEL_KERNEL_SYSMEM_SYSROOT_H */

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

void *sceKernelSysrootGetKblParam(void);

int sceKernelGetProcessTitleId(SceUID pid, char *titleid, SceSize len);

int sceSysrootGetSelfInfo(SceKernelSysrootSelfIndex index, SceKernelSysrootSelfInfo *info);

/**
 * Get UseExternalStorage status.
 *
 * Returns 1 if an external device(sdcard) is available.
 *
 * @return 0 or 1.
 */
int sceSysrootUseExternalStorage(void);

/**
 * Get UseInternalStorage status.
 *
 * Returns 1 if using an internal device(pre-memcard).
 *
 * @return 0 or 1.
 */
int sceSysrootUseInternalStorage(void);

typedef struct SceSysrootProcessHandler {
    SceSize size;                                                       //!< sizeof(SceSysrootProcessHandler)
    void (* unk_4)(SceUID pid, SceUID modid, int flags, uint64_t time); //!< process start shared modules
    void (* exit)(SceUID pid, int flags, uint64_t time);
    void (* kill)(SceUID pid);                                          //!< by SceShell
    void (* unk_10)(SceUID pid, SceUID modid, uint64_t time);
    void (* unk_14)(SceUID pid, SceUID modid, uint64_t time);
    void (* unk_18)(SceUID pid, SceUID modid, uint64_t time);
    int (* on_process_created)(int a1, int a2, int a3);                 //!< called when process is created
    void (* unk_20)(SceUID pid, SceUID modid, uint64_t time);
    void (* unk_24)(SceUID pid, SceUID modid, int flags, uint64_t time);
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

typedef struct SceSysrootDbgpHandler {
    SceSize size; //!< sizeof(SceSysrootDbgpHandler):0x5C
    void (* unk_0x04)(int a1, int a2, int a3, int a4);
    void (* unk_0x08)(int a1, int a2, int a3, int a4);
    void (* unk_0x0C)(int a1);
    void (* unk_0x10)(int a1, int a2, int a3, int a4);
    void (* unk_0x14)(int a1, int a2, int a3, int a4);
    void (* unk_0x18)(SceUID pid, SceUID modid, int flags, uint64_t time);
    void (* unk_0x1C)(int a1, int a2, int a3);
    void (* unk_0x20)(int a1, int a2, int a3);
    void (* unk_0x24)(int a1, int a2, int a3);
    void (* unk_0x28)(SceUID pid, SceUID modid, uint64_t time);
    void (* unk_0x2C)(SceUID pid, SceUID modid, uint64_t time);
    int  (* unk_0x30)(SceUID pid);
    int  (* unk_0x34)(int a1, int a2, int a3);
    int  (* unk_0x38)(int a1, int a2, void *a3);
    int  (* unk_0x3C)(int a1, int a2, int a3);
    int  (* unk_0x40)(SceUID pid, int *some_flag);
    int  (* unk_0x44)(SceUID pid, SceUID modid, int flags, uint64_t time);
    int  (* unk_0x48)(int a1, int a2, int a3);
    void (* unk_0x4C)(void);
    void (* unk_0x50)(void);
    int  (* unk_0x54)(int a1, int a2, int a3, int a4, int a5);
    int  (* unk_0x58)(int a1, int a2, int a3);
} SceSysrootDbgpHandler;

/**
 * Register Dbgp handlers.
 *
 * @param[in]  handlers   pointer of handlers
 *
 * @return 0 on success, < 0 on error.
 */
int sceKernelSysrootRegisterDbgpHandler(const SceSysrootDbgpHandler *handlers);

/**
 * Unregister Dbgp handlers.
 *
 * @return none.
 */
void sceKernelSysrootUnregisterDbgpHandler(void);

/**
 * Get the process UID of shell.
 *
 * @return UID or -1 if shell is not started.
 */
SceUID sceKernelSysrootGetShellPid(void);

/**
 * Get hardware flags.
 *
 * @param[out] flags - The flags output buffer. size is 0x10 byte
 *
 * @return always 0.
 */
SceInt32 sceSysrootGetHardwareFlags(SceUInt32 flags[4]);

int sceSysrootIsBsodReboot(void);

int sceSysrootIsSafeMode(void);

int sceSysrootIsUpdateMode(void);

int sceSysrootIsUsbEnumWakeup(void);

int sceSysrootIsExternalBootMode(void);

SCE_CDECL_END

#endif /* _VDSUITE_KERNEL_KERNEL_SYSMEM_SYSROOT_H */

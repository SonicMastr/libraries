/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_KERNEL_KERNEL_MODULEMGR_H
#define _VDSUITE_KERNEL_KERNEL_MODULEMGR_H

#include_next <kernel/modulemgr.h>

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceKernelModuleState {
    SCE_KERNEL_MODULE_STATE_READY   = 0x00000002,
    SCE_KERNEL_MODULE_STATE_STARTED = 0x00000006,
    SCE_KERNEL_MODULE_STATE_ENDED   = 0x00000009
} SceKernelModuleState;

typedef struct SceKernelModuleName {
  char s[0x1C];
} SceKernelModuleName;

typedef struct SceKernelSegmentInfo {
  SceSize size;   //!< this structure size (0x18)
  SceUInt perms;  //!< probably rwx in low bits
  void *vaddr;    //!< address in memory
  SceSize memsz;  //!< size in memory
  SceSize filesz; //!< original size of memsz
  SceUInt res;    //!< unused
} SceKernelSegmentInfo;

typedef struct SceKernelModuleInfo {
  SceSize size;                       //!< 0x1B8 for Vita 1.x
  SceUID modid;
  uint16_t modattr;
  uint8_t  modver[2];
  char module_name[28];
  SceUInt unk28;
  void *start_entry;
  void *stop_entry;
  void *exit_entry;
  void *exidx_top;
  void *exidx_btm;
  void *extab_top;
  void *extab_btm;
  void *tlsInit;
  SceSize tlsInitSize;
  SceSize tlsAreaSize;
  char path[256];
  SceKernelSegmentInfo segments[4];
  SceUInt state;                       //!< see:SceKernelModuleState
} SceKernelModuleInfo;

typedef struct {
  SceSize size;
  char versionString[0x1C];
  SceUInt version;
  SceUInt unk_24;
} SceKernelFwInfo;

typedef struct {
  SceSize size; //!< sizeof(SceKernelSegmentInfo2) (0x14)
  int perm;
  void *vaddr;
  uint32_t memsz;
  int unk_10;
} SceKernelSegmentInfo2;

typedef struct {
  SceSize size;
  SceUID modid;
  uint32_t version;
  uint32_t module_version;
  uint32_t unk10;
  void *unk14;
  uint32_t unk18;
  void *unk1C;
  void *unk20;
  char module_name[28];
  uint32_t unk40;
  uint32_t unk44;
  uint32_t nid;
  SceSize segments_num;
  union {
    struct {
      SceKernelSegmentInfo2 SegmentInfo[1];
      uint32_t addr[4];
    } seg1;
    struct {
      SceKernelSegmentInfo2 SegmentInfo[2];
      uint32_t addr[4];
    } seg2;
    struct {
      SceKernelSegmentInfo2 SegmentInfo[3];
      uint32_t addr[4];
    } seg3;
    struct {
      SceKernelSegmentInfo2 SegmentInfo[4];
      uint32_t addr[4];
    } seg4;
  };
} SceKernelModuleListInfo;

typedef struct SceKernelModuleLibraryInfo {
  SceSize size; //!< sizeof(SceKernelModuleLibraryInfo) : 0x120
  SceUID library_id;
  uint32_t libnid;
  uint16_t version;
  uint16_t attribute;
  uint16_t entry_num_function;
  uint16_t entry_num_variable;
  uint16_t unk_0x14;
  uint16_t unk_0x16;
  char library_name[0x100];
  SceSize number_of_imported;
  SceUID modid2;
} SceKernelModuleLibraryInfo;

/**
 * @brief Register syscall function
 *
 * @param[in] syscall_id - register syscall id (Must be less than 0x1000)
 * @param[in] func       - syscall function
 *
 * @return none
 */
void sceKernelRegisterSyscall(SceSize syscall_id, const void *func);

/**
 * @brief Setup kernel for modulemgr
 *
 * @note - allocate and initialize syscall table
 *
 * @return none
 */
void sceKernelSetupForModulemgr(void);

/**
 * @brief Get module id list
 *
 * @param[in]    pid    - target pid
 * @param[in]    flags1 - unknown, use 0x7FFFFFFF
 * @param[in]    flags2 - unknown, use 1
 * @param[out]   modids - info output pointer
 * @param[inout] num    - in:list max num, out:get modid num
 *
 * @return 0 on success, < 0 on error.
 */
int sceKernelGetModuleList(SceUID pid, int flags1, int flags2, SceUID *modids, SceSize *num);

/**
 * @par Example1: Get max to 10 kernel module info
 * @code
 * SceKernelModuleListInfo infolists[10];
 * size_t num = 10;// Get max
 * uint32_t offset = 0;
 * SceKernelModuleListInfo *info = &infolists[0];
 *
 * sceKernelGetModuleList2(0x10005, infolists, &num);
 *
 * for(int i=0;i<num;i++){
 *   printf("name : %s\n", info->module_name);
 *
 *   if(info->segments_num == 1){
 *     printf("vaddr:0x%08X\n", info->seg1.SegmentInfo[0].vaddr);
 *   }else if(info->segments_num == 2){
 *     printf("vaddr:0x%08X\n", info->seg2.SegmentInfo[0].vaddr);
 *   }
 *   info = ((char *)info) + info->size;
 * }
 * @endcode
 *
 * @param[in]    pid       - target pid
 * @param[out]   infolists - infolists output
 * @param[inout] num       - Specify the maximum number of modinfolist to retrieve. If the function returns 0, it returns the number of modules loaded in the target pid in num
 *
 * @return 0 on success, < 0 on error.
 */
int sceKernelGetModuleList2(SceUID pid, SceKernelModuleListInfo *infolists, SceSize *num);

/**
 * @brief Get module info
 *
 * @param[in]  pid   - target pid
 * @param[in]  modid - target module id
 * @param[out] info  - info output pointer
 *
 * @return 0 on success, < 0 on error.
 */
int sceKernelGetModuleInfo(SceUID pid, SceUID modid, SceKernelModuleInfo *info);

/**
 * @brief Get module info mini by module address
 *
 * @param[in]  pid               - target pid
 * @param[in]  module_addr       - target module address, Also possible with data segment address
 * @param[out] module_nid        - can also set NULL, module nid output
 * @param[out] program_text_addr - can also set NULL, program text addr output
 * @param[out] module_name       - can also set NULL, module name output
 *
 * @return 0 on success, < 0 on error.
 */
int sceKernelGetModuleInfoMinByAddr(SceUID pid, const void *module_addr, uint32_t *module_nid, const void **program_text_addr, SceKernelModuleName *module_name);

/**
 * @brief Get module info (internal)
 *
 * @param[in]  modid       - target module id
 * @param[out] module_info - module_info output pointer
 *
 * @return 0 on success, < 0 on error.
 */
int sceKernelGetModuleInternal(SceUID modid, void **info);

/**
 * @brief Get module id by module address
 *
 * @param[in] pid         - target pid
 * @param[in] module_addr - target module address
 *
 * @return modid on success, < 0 on error.
 */
SceUID sceKernelGetModuleIdByAddr(SceUID pid, const void *module_addr);

/**
 * @brief search kernel module by module name
 *
 * @param[in] module_name - target module name
 *
 * @return modid on success, < 0 on error.
 */
SceUID sceKernelSearchModuleByName(const char *module_name);

/**
 * @brief Get fw info
 *
 * @param[out] data - fw info output pointer
 *
 * @return 0 on success, < 0 on error.
 */
int sceKernelGetSystemSwVersion(SceKernelFwInfo *data);

/**
 * @brief load module
 *
 * @param[in]  pid    - target pid
 * @param[in]  path   - module path
 * @param[in]  flags  - unknown, set zero
 * @param[in]  option - unknown
 *
 * @return modid on success, < 0 on error.
 */
SceUID sceKernelLoadModuleForPid(SceUID pid, const char *path, int flags, const SceKernelLoadModuleOpt *option);

/**
 * @brief start module
 *
 * @param[in]  pid    - target pid
 * @param[in]  modid  - target module id
 * @param[in]  args   - module start args
 * @param[in]  argp   - module start argp
 * @param[in]  flags  - unknown, set zero
 * @param[in]  option - unknown
 * @param[out] status - module_start res, SCE_KERNEL_START_SUCCESS etc...
 *
 * @return 0 on success, < 0 on error.
 */
int sceKernelStartModuleForPid(SceUID pid, SceUID modid, SceSize args, const void *argp, int flags, const SceKernelStartModuleOpt *option, int *status);

/**
 * @brief load and start module
 *
 * @param[in]  pid    - target pid
 * @param[in]  path   - module path
 * @param[in]  args   - module start args
 * @param[in]  argp   - module start argp
 * @param[in]  flags  - unknown, set zero
 * @param[in]  option - unknown
 * @param[out] status - module_start res, SCE_KERNEL_START_SUCCESS etc...
 *
 * @return modid on success, < 0 on error.
 */
SceUID sceKernelLoadStartModuleForPid(SceUID pid, const char *path, SceSize args, const void *argp, int flags, const SceKernelLoadModuleOpt *option, int *status);

/**
 * @brief stop module
 *
 * @param[in]  pid    - target pid
 * @param[in]  modid  - target module id
 * @param[in]  args   - module stop args
 * @param[in]  argp   - module stop argp
 * @param[in]  flags  - unknown, set zero
 * @param[in]  option - unknown
 * @param[out] status - module_stop res, SCE_KERNEL_STOP_SUCCESS etc...
 *
 * @return 0 on success, < 0 on error.
 */
int sceKernelStopModuleForPid(SceUID pid, SceUID modid, SceSize args, const void *argp, int flags, const SceKernelStopModuleOpt *option, int *status);

/**
 * @brief unload module
 *
 * @param[in]  pid    - target pid
 * @param[in]  modid  - target module id
 * @param[in]  flags  - unknown, set zero
 * @param[in]  option - unknown
 *
 * @return 0 on success, < 0 on error.
 */
int sceKernelUnloadModuleForPid(SceUID pid, SceUID modid, int flags, const SceKernelUnloadModuleOpt *option);

/**
 * @brief stop and unload module
 *
 * @param[in]  pid    - target pid
 * @param[in]  modid  - target module id
 * @param[in]  args   - module stop args
 * @param[in]  argp   - module stop argp
 * @param[in]  flags  - unknown, set zero
 * @param[in]  option - unknown
 * @param[out] status - module_stop res, SCE_KERNEL_STOP_SUCCESS etc...
 *
 * @return 0 on success, < 0 on error.
 */
int sceKernelStopUnloadModuleForPid(SceUID pid, SceUID modid, SceSize args, const void *argp, int flags, const SceKernelUnloadModuleOpt *option, int *status);

/**
 * @brief load and start module as shared module
 *
 * @param[in]  pid    - target pid
 * @param[in]  path   - module path
 * @param[in]  args   - module start args
 * @param[in]  argp   - module start argp
 * @param[in]  flags  - unknown, set zero
 * @param[in]  option - unknown
 * @param[out] status - module_start res, SCE_KERNEL_START_SUCCESS etc...
 *
 * @return modid on success, < 0 on error.
 */
SceUID sceKernelLoadStartSharedModuleForPid(SceUID pid, const char *path, SceSize args, const void *argp, int flags, const SceKernelLoadModuleOpt *option, int *status);

/**
 * @brief stop and unload module as shared module
 *
 * @param[in]  pid    - target pid
 * @param[in]  modid  - target module id
 * @param[in]  args   - module stop args
 * @param[in]  argp   - module stop argp
 * @param[in]  flags  - unknown, set zero
 * @param[in]  option - unknown
 * @param[out] status - module_stop res, SCE_KERNEL_STOP_SUCCESS etc...
 *
 * @return 0 on success, < 0 on error.
 */
int sceKernelStopUnloadSharedModuleForPid(SceUID pid, SceUID modid, SceSize args, const void *argp, int flags, const SceKernelUnloadModuleOpt *option, int *status);

/**
 * @brief mount bootfs (load bootfs module)
 *
 * @param[in] bootImagePath - bootfs module path
 *
 * @return 0 on success, < 0 on error.
 */
int sceKernelMountBootfs(const char *bootImagePath);

/**
 * @brief unmount bootfs (unload bootfs module)
 *
 * @return 0 on success, < 0 on error.
 */
int sceKernelUmountBootfs(void);

/**
 * @brief Get the main module for a given process.
 * @param pid The process to query.
 * @return the UID of the module else < 0 for an error.
 */
SceUID sceKernelGetProcessMainModule(SceUID pid);

/**
 * @brief Get the module path
 *
 * @param[in]  pid     - target pid
 * @param[out] path    - module path output
 * @param[in]  pathlen - path output max len
 *
 * @return 0 on success, < 0 on error.
 */
int sceKernelGetModulePath(SceUID modid, char *path, SceSize pathlen);

/**
 * @brief Get library info
 *
 * @param[in]  pid   - target pid
 * @param[in]  modid - target library id
 * @param[out] info  - info output
 *
 * @return 0 on success, < 0 on error.
 */
int sceKernelGetModuleLibraryInfo(SceUID pid, SceUID library_id, SceKernelModuleLibraryInfo *info);

typedef struct SceKernelModuleExportEntry {
	uint32_t libnid;
	const void *entry; // function ptr. or vars?
} SceKernelModuleExportEntry;

/**
 * @brief Get module export entry
 *
 * @param[in]    pid          - target pid
 * @param[in]    libid        - target library uid
 * @param[out]   list         - data output
 * @param[inout] num          - in:list max num, out:get entry num
 * @param[in]    cpy_skip_num - The index at which to start copying
 *
 * @return 0 on success, < 0 on error.
 */
int sceKernelGetModuleLibExportList(SceUID pid, SceUID library_id, SceKernelModuleExportEntry *list, SceSize *num, SceSize cpy_skip_num);

/**
 * @brief Get module id list by import
 *
 * @param[in]    pid          - target pid
 * @param[in]    library_id   - target library uid
 * @param[out]   modids       - module id output list
 * @param[inout] num          - in:list max num, out:get entry num
 * @param[in]    cpy_skip_num - The index at which to start copying
 *
 * @return 0 on success, < 0 on error.
 */
int sceKernelGetModuleListByImport(SceUID pid, SceUID library_id, SceUID *modids, SceSize *num, SceSize cpy_skip_num);

/**
 * @brief Get module export list
 *
 * @param[in]    pid         - target pid
 * @param[out]   library_ids - library id output list
 * @param[inout] num         - in:list max num, out:get entry num
 *
 * @return 0 on success, < 0 on error.
 */
int sceKernelGetProcessLibraryIdList(SceUID pid, SceUID *library_ids, SceSize *num);

#ifdef __cplusplus
}
#endif

#endif /* _VDSUITE_KERNEL_KERNEL_MODULEMGR_H */

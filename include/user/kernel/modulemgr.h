/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_USER_KERNEL_MODULEMGR_H
#define _VDSUITE_USER_KERNEL_MODULEMGR_H

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

int sceKernelGetModuleList(int flags, SceUID *modids, SceSize *num);
int sceKernelGetModuleInfo(SceUID modid, SceKernelModuleInfo *info);

typedef struct SceKernelFwInfo {
	SceSize size;
	char versionString[0x1C];
	SceUInt version;
	SceUInt unk_24;
} SceKernelFwInfo;

/**
 * Gets system firmware information.
 *
 * @param[out] data - firmware information.
 *
 * @note - If you spoofed the firmware version it will return the spoofed firmware.
 */
int sceKernelGetSystemSwVersion(SceKernelFwInfo *data);

#ifdef __cplusplus
}
#endif

#endif /* _VDSUITE_USER_KERNEL_MODULEMGR_H */


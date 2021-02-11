#ifndef _DOLCESDK_PSP2_KERNEL_IOFILEMGR_SYSCALL_H_
#define _DOLCESDK_PSP2_KERNEL_IOFILEMGR_SYSCALL_H_

#include <kernel/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Struct definitions */

typedef struct SceIoUnusedSyscallParam0x8 {
	char unused[0x8];
} SceIoUnusedSyscallParam0x8;

typedef struct SceIoUnusedSyscallParam0x10 {
	char unused[0x10];
} SceIoUnusedSyscallParam0x10;

typedef struct SceIoDevctlSyscallParam {
	SceSize arglen;
	void *bufp;
	SceSize buflen;
	char unused[0xC];
	// size 0x18
} SceIoDevctlSyscallParam;

typedef struct SceIoIoctlSyscallParam {
	SceSize arglen;
	void *bufp;
	SceSize buflen;
	char unused[0x4];
	// size 0x10
} SceIoIoctlSyscallParam;

typedef struct SceIoLseekSyscallParam {
	SceOff offset;
	int whence;
	char unused[0x4];
	// size 0x10
} SceIoLseekSyscallParam;

typedef struct SceIoPreadSyscallParam {
	SceOff offset;
	char unused[0x8];
	// size 0x10
} SceIoPreadSyscallParam;

typedef SceIoPreadSyscallParam SceIoPwriteSyscallParam;

/* Function declarations */

SceUID _sceIoRemove(const char *filename, SceIoUnusedSyscallParam0x8* param);

int _sceIoMkdir(const char *dirname, SceIoMode mode, SceIoUnusedSyscallParam0x8* param);

int _sceIoRmdir(const char *dirname, SceIoUnusedSyscallParam0x8* param);

int _sceIoRename(const char *oldname, const char *newname, SceIoUnusedSyscallParam0x10* param);

int _sceIoDevctl(const char *devname, int cmd, const void *arg, SceIoDevctlSyscallParam* param);

int _sceIoSync(const char *devname, int flag, SceIoUnusedSyscallParam0x8* param);

SceUID _sceIoOpen(const char *filename, int flag, SceIoMode mode, SceIoUnusedSyscallParam0x8* param);

int _sceIoIoctl(SceUID fd, int cmd, const void *argp, SceIoIoctlSyscallParam* param);

SceOff _sceIoLseek(SceUID fd, SceIoLseekSyscallParam* param);

SceSSize _sceIoPread(SceUID fd, void *buf, SceSize nbyte, SceIoPreadSyscallParam* param);

SceSSize _sceIoPwrite(SceUID fd, const void *buf, SceSize nbyte, SceIoPwriteSyscallParam* param);

#ifdef __cplusplus
}
#endif

#endif	/* _DOLCESDK_PSP2_KERNEL_IOFILEMGR_SYSCALL_H_ */

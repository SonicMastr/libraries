#ifndef _PSP2_KERNEL_PROCESSMGR_H_
#define _PSP2_KERNEL_PROCESSMGR_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceKernelProcessInfo {
	SceSize size; // size of this struct, make sure it's 0xE8
	SceUID pid; // our process ID
	int unk1;
	int unk2;
	int unk3;
	SceUID ppid; // parent process ID
	// the rest is unknown
} SceKernelProcessInfo;

void *sceKernelGetProcessKernelBuf(SceUID pid);

int sceKernelGetProcessInfo(SceUID pid, SceKernelProcessInfo *info);

int sceKernelCreateProcessLocalStorage(const char *name, SceSize size);
void *sceKernelGetProcessLocalStorageAddr(int key);
int sceKernelGetPidProcessLocalStorageAddr(SceUID pid, int key, void **out_addr, int create_if_doesnt_exist);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_PROCESSMGR_H_ */


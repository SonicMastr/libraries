#ifndef _PSP2_KERNEL_INTRMGR_H_
#define _PSP2_KERNEL_INTRMGR_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*SceKernelIntrOptParam2Callback)(int code, int arg);

typedef struct SceKernelIntrOptParam2 {
	uint32_t size; // 0x28
	uint32_t unk_4;
	uint32_t unk_8;
	uint32_t unk_C;
	SceKernelIntrOptParam2Callback *fptr0; // function pointer
	SceKernelIntrOptParam2Callback *fptr1; // function pointer
	SceKernelIntrOptParam2Callback *fptr2; // function pointer
	uint32_t unk_1C;
	uint32_t unk_20;
	uint32_t unk_24;
} SceKernelIntrOptParam2;

typedef struct SceKernelIntrOptParam {
	uint32_t size; // 0x14
	uint32_t num;
	SceKernelIntrOptParam2 *opt2;
	uint32_t unk_C;
	uint32_t unk_10;
} SceKernelIntrOptParam;

typedef int (*SceKernelIntrHandler)(int unk, void *userCtx);
typedef int (*SceKernelSubIntrHandler)(void *arg, int unk0, int unk1);

int sceKernelRegisterIntrHandler(int intr_code, const char *name, int interrupt_type,
	SceKernelIntrHandler *handler, void *userCtx, int priority, int targetcpu, SceKernelIntrOptParam *opt);
int sceKernelReleaseIntrHandler(int intr_code);
int sceKernelMaskIntr(int intr_code);
int sceKernelUnmaskIntr(int intr_code);
int sceKernelSetIntrMasked(int intr_code, int masked);
int sceKernelGetIntrMasked(int intr_code, int *masked);
int sceKernelIsIntrPending(int intr_code);
int sceKernelClearIntrPending(int intr_code);
int sceKernelSetIntrPriority(int intr_code, unsigned char priority);
int sceKernelSetIntrTarget(int intr_code, int cpu_target_list);
int sceKernelTriggerSGI(int intr_code, unsigned int target_list_filter, unsigned int cpu_target_list);
int sceKernelIsIntrAllowedInCurrentContext(int intr_code);
int sceKernelRegisterSubIntrHandler(int intr_code, int subintr_code, const char *name,
	SceKernelSubIntrHandler handler, void *register_arg);
int sceKernelTriggerSubIntr(int intr_code, int subintr_code, void *subintr_arg);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_INTRMGR_H_ */


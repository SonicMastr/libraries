/*
	Vita Development Suite Libraries
*/

#ifndef _PSP2_KERNEL_INTRMGR_H_
#define _PSP2_KERNEL_INTRMGR_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*SceKernelIntrHandler)(int unk, void *userCtx);
typedef int (*SceKernelSubIntrHandler)(void *subintr_arg, void *register_arg, unsigned char intr_priority);

typedef int (*SceKernelIntrOptHandlersCb1)(int intr_code, int subintr_code);
typedef int (*SceKernelIntrOptHandlersCb2)(int intr_code, int subintr_code, void *arg);
typedef int (*SceKernelIntrOptHandlersCb3)(int intr_code, int subintr_code, SceKernelSubIntrHandler handler, void *register_arg);

typedef struct SceKernelIntrOptHandlers {
	uint32_t size; // 0x28
	SceKernelIntrOptHandlersCb3 *pre_register_subintr_cb;
	SceKernelIntrOptHandlersCb3 *post_register_subintr_cb;
	SceKernelIntrOptHandlersCb1 *release_subintr_cb;
	SceKernelIntrOptHandlersCb1 *fptr0;
	SceKernelIntrOptHandlersCb1 *enable_subintr_cb;
	SceKernelIntrOptHandlersCb1 *disable_subintr_cb;
	SceKernelIntrOptHandlersCb2 *fptr3;
	SceKernelIntrOptHandlersCb1 *fptr4;
	SceKernelIntrOptHandlersCb1 *fptr5;
} SceKernelIntrOptHandlers;

typedef struct SceKernelIntrOptParam {
	uint32_t size; // 0x14
	uint32_t num;
	SceKernelIntrOptHandlers *handlers;
	uint32_t unk_C;
	uint32_t unk_10;
} SceKernelIntrOptParam;

int sceKernelRegisterIntrHandler(int intr_code, const char *name, int interrupt_type,
	SceKernelIntrHandler *handler, void *userCtx, int priority, int targetcpu, SceKernelIntrOptParam *opt);
int sceKernelReleaseIntrHandler(int intr_code);
int sceKernelDisableIntr(int intr_code);
int sceKernelEnableIntr(int intr_code);
int sceKernelSuspendIntr(int intr_code, int *masked);
int sceKernelIsIntrPending(int intr_code);
int sceKernelClearIntrPending(int intr_code);
int sceKernelSetIntrPriority(int intr_code, int priority);
int sceKernelGetIntrPriority(int intr_code, int *priority);
int sceKernelSetIntrTargetCpu(int intr_code, int cpu_target_list);
int sceKernelGetIntrTargetCpu(int intr_code, int *cpu_target_list);
int sceKernelGenerateSoftIntr(int intr_code, unsigned int target_list_filter, unsigned int cpu_target_list);
int sceKernelIsIntrContext(int intr_code);
int sceKernelRegisterSubIntrHandler(int intr_code, int subintr_code, const char *name,
	SceKernelSubIntrHandler handler, void *register_arg);
int sceKernelReleaseSubIntrHandler(int intr_code, int subintr_code);
int sceKernelCallSubIntrHandler(int intr_code, int subintr_code, void *subintr_arg);
int sceKernelEnableSubIntr(int intr_code, int subintr_code);
int sceKernelDisableSubIntr(int intr_code, int subintr_code);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_INTRMGR_H_ */


#ifndef _PSP2_KERNEL_INTRMGR_H_
#define _PSP2_KERNEL_INTRMGR_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*intr_callback)(int code, int arg);

typedef struct reg_intr_opt2 {
	uint32_t size; // 0x28
	uint32_t unk_4;
	uint32_t unk_8;
	uint32_t unk_C;
	intr_callback *fptr0; // function pointer
	intr_callback *fptr1; // function pointer
	intr_callback *fptr2; // function pointer
	uint32_t unk_1C;
	uint32_t unk_20;
	uint32_t unk_24;
} reg_intr_opt2;

typedef struct reg_intr_opt {
	uint32_t size; // 0x14
	uint32_t num;
	reg_intr_opt2 *opt2;
	uint32_t unk_C;
	uint32_t unk_10;
} reg_intr_opt;

typedef int (*intr_callback_func)(int unk, void *userCtx);

int sceKernelRegisterIntrHandler(int intr_code, const char *name, int interrupt_type,
	intr_callback_func *func, void *userCtx, int priority, int targetcpu, reg_intr_opt *opt);

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

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_INTRMGR_H_ */


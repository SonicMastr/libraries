/*
	Vita Development Suite Libraries
*/

#include <string.h>
#include <kernel/cpu.h>

#define ALIGN(x) ((((x) + 0x1F) >> 5) << 5)
#define ALIGN_BACK(x) (((x) >> 5) << 5)

// Copied from sysmem.skprx 3.600
// Unavailable in 3.650
int sceKernelCpuUnrestrictedMemcpy(void *dst, const void *src, SceSize len) {
	int dacr =	__builtin_mrc(15, 0, 3, 0, 0);
	__builtin_mcr(15, 0, 3, 0, 0, 0xFFFF0000);
	memcpy(dst, src, len);
	len =  ALIGN((SceSize)dst + len) - ALIGN_BACK((SceSize)dst);
	dst = (void*)ALIGN_BACK((SceSize)dst);
	sceKernelCpuDcacheWritebackRange(dst, len);
	__builtin_mcr(15, 0, 3, 0, 0, dacr);
	return 0;
}

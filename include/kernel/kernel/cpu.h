#ifndef _PSP2_KERNEL_CPU_H_
#define _PSP2_KERNEL_CPU_H_

#include_next <kernel/cpu.h>

#include <string.h>
#include <scetypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief      Call this when entering a syscall
 *
 * @param      state  The state
 */
#define ENTER_SYSCALL(state) \
	do { \
		asm volatile ("mrc p15, 0, %0, c13, c0, 3" : "=r" (state)); \
		asm volatile ("mcr p15, 0, %0, c13, c0, 3" :: "r" (state << 16) : "memory"); \
	} while(0)

/**
 * @brief      Call this when exiting a syscall
 *
 * @param      state  The state
 */
#define EXIT_SYSCALL(state) \
	do { \
		asm volatile ("mcr p15, 0, %0, c13, c0, 3" :: "r" (state) : "memory"); \
	} while (0)


/**
 * @brief      Writeback a range of L1 dcache (without L2)
 *
 * @param      ptr   The pointer
 * @param[in]  len   The length
 */
void sceKernelCpuDcacheWritebackRange(const void *ptr, SceSize len);


/**
 * @brief      Save process context
 *
 * @param      context  The context
 */
static inline void sceKernelCpuSaveContext(int context[3])
{
	asm ("mrc p15, 0, %0, c2, c0, 1" : "=r" (context[0]));
	asm ("mrc p15, 0, %0, c3, c0, 0" : "=r" (context[1]));
	asm ("mrc p15, 0, %0, c13, c0, 1" : "=r" (context[2]));
}

/**
 * @brief      Restore process context
 *
 * @param      context  The context, can be from ::sceKernelGetPidContext
 */
static inline void sceKernelCpuRestoreContext(int context[3])
{
	int cpsr, tmp;

	asm volatile ("mrs %0, cpsr" : "=r" (cpsr));
	if (!(cpsr & 0x80))
		asm volatile ("cpsid i" ::: "memory");
	asm volatile ("mrc p15, 0, %0, c13, c0, 1" : "=r" (tmp));
	tmp = (tmp & 0xFFFFFF00) | context[2];
	asm volatile ("mcr p15, 0, %0, c13, c0, 1" :: "r" (0));
	asm volatile ("isb" ::: "memory");
	asm volatile ("mcr p15, 0, %0, c2, c0, 1" :: "r" (context[0] | 0x4A));
	asm volatile ("isb" ::: "memory");
	asm volatile ("mcr p15, 0, %0, c13, c0, 1" :: "r" (tmp));
	asm volatile ("mcr p15, 0, %0, c3, c0, 0" :: "r" (context[1] & 0x55555555));
	if (!(cpsr & 0x80))
		asm volatile ("cpsie i" ::: "memory");
}

/**
 * @brief      MMU permission bypassing memcpy
 *
 * This works by writing to the DACR before and after the memcpy.
 *
 * @param      dst   The destination
 * @param[in]  src   The source
 * @param[in]  len   The length
 *
 * @return     Zero on success.
 */
static inline int sceKernelCpuUnrestrictedMemcpy(void *dst, const void *src, SceSize len)
{
	int prev_dacr;

	asm volatile("mrc p15, 0, %0, c3, c0, 0" : "=r" (prev_dacr));
	asm volatile("mcr p15, 0, %0, c3, c0, 0" :: "r" (0xFFFF0000));

	memcpy(dst, src, len);

	len += (SceSize)(((uintptr_t)dst) & 0x1F);

	dst = (void *)(((uintptr_t)dst) & ~0x1F);
	len = (len + 0x1F) & ~0x1F;

	sceKernelCpuDcacheWritebackRange(dst, len);

	asm volatile("mcr p15, 0, %0, c3, c0, 0" :: "r" (prev_dacr));
	return 0;
}

/**
 * @brief      Returns the CPU ID of the calling processor
 *
 * @return     The CPU ID
 */
int sceKernelCpuGetCpuId(void);

/**
 * @brief      Disabled interrupts
 *
 * @return     Interrupt masks before disabling
 */
int sceKernelCpuDisableInterrupts(void);

/**
 * @brief      Enable interrupts
 *
 * @param[in]  flags  Interrupt masks
 *
 * @return     Zero on success
 */
int sceKernelCpuEnableInterrupts(int flags);

/**
 * @brief      Invalidate a range of L1 dcache (without L2)
 *
 * @param      ptr   The pointer
 * @param[in]  len   The length
 */
void sceKernelCpuDcacheInvalidateRange(const void *ptr, SceSize len);

/**
 * @brief      Writeback and invalidate a range of L1 dcache (without L2)
 *
 * @param      ptr   The pointer
 * @param[in]  len   The length
 */
void sceKernelCpuDcacheWritebackInvalidateRange(const void *ptr, SceSize len);

/**
 * @brief      Invalidate all the L1 dcache (without L2)
 */
void sceKernelCpuDcacheInvalidateAll(void);

/**
 * @brief      Writeback all the L1 dcache (without L2)
 */
void sceKernelCpuDcacheWritebackAll(void);

/**
 * @brief      Writeback and invalidate all the L1 dcache (without L2)
 */
void sceKernelCpuDcacheWritebackInvalidateAll(void);

/**
 * @brief      Writeback a range of L1 dcache and L2
 *
 * @param      ptr   The pointer
 * @param[in]  len   The length
 */
void sceKernelCpuDcacheAndL2WritebackRange(const void *ptr, SceSize len);

/**
 * @brief      Writeback and invalidate a range of L1 dcache and L2
 *
 * @param      ptr   The pointer
 * @param[in]  len   The length
 */
void sceKernelCpuDcacheAndL2InvalidateRange(const void *ptr, SceSize len);

/**
 * @brief      Writeback and invalidate a range of L1 dcache and L2
 *
 * @param      ptr   The pointer
 * @param[in]  len   The length
 *
 * @return     Zero on success
 */
void sceKernelCpuDcacheAndL2WritebackInvalidateRange(const void *ptr, SceSize len);

/**
 * @brief      Invalidate a range of L1 icache (without L2)
 *
 * @param      ptr   The pointer
 * @param[in]  len   The length
 */
void sceKernelCpuIcacheInvalidateRange(const void *ptr, SceSize len);

/**
 * @brief      Invalidate all the L1 icache (without L2)
 *
 * @return     Zero on success
 */
int sceKernelCpuIcacheInvalidateAll(void);

/**
 * @brief      Writeback and invalidate a range of L1 icache and L2
 *
 * @param      ptr   The pointer
 * @param[in]  len   The length
 */
void sceKernelCpuIcacheAndL2WritebackInvalidateRange(const void *ptr, SceSize len);

/**
 * @brief      Suspend all interrupts (disables IRQs)
 *
 * @param[in]  addr   Mutex associated to the suspend-resume pair
 *
 * @return     The current state of the interrupt controller, to be used with ::sceKernelCpuResumeIntr.
 */
int sceKernelCpuSuspendIntr(int *addr);

/**
 * @brief      Resume all interrupts (enables IRQs)
 *
 * @param[in]  addr   Mutex associated to the suspend-resume pair
 * @param[in]  prev_state   State obtained from ::sceKernelCpuSuspendIntr.
 *
 * @return     The previous state of the interrupt controller.
 */
int sceKernelCpuResumeIntr(int *addr, int prev_state);

/**
 * @brief      Disable interrupts (IRQs) and spin-lock
 *
 * @param[in]  addr   Mutex associated to the lock-unlock pair
 *
 * @return     The current state of the interrupt controller, to be passed to ::sceKernelCpuSpinLockIrqRestore
 */
int sceKernelCpuSpinLockIrqSave(int *addr);

/**
 * @brief      Spin-unlock and restore interrupt state
 *
 * @param[in]  addr   Mutex associated to the lock-unlock pair
 * @param[in]  flags   Previous interrupt state to be restored (returned by ::sceKernelCpuSpinLockIrqSave)
 *
 * @return     Zero on success
 */
int sceKernelCpuSpinLockIrqRestore(int *addr, int flags);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_CPU_H_ */


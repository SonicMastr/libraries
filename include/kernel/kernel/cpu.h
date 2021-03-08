/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_KERNEL_KERNEL_CPU_H
#define _VDSUITE_KERNEL_KERNEL_CPU_H

#include_next <kernel/cpu.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief      Writeback a range of L1 dcache (without L2)
 *
 * @param      ptr   The pointer
 * @param[in]  len   The length
 */
void sceKernelCpuDcacheWritebackRange(const void *ptr, SceSize len);

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
int sceKernelCpuUnrestrictedMemcpy(void *dst, const void *src, SceSize len);

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

#endif /* _VDSUITE_KERNEL_KERNEL_CPU_H */


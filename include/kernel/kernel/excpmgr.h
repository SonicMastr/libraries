/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_KERNEL_KERNEL_EXCPMGR_H
#define _VDSUITE_KERNEL_KERNEL_EXCPMGR_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceExcpKind {
	SCE_EXCP_RESET                = 0,
	SCE_EXCP_UNDEF_INSTRUCTION    = 1,
	SCE_EXCP_SVC                  = 2,
	SCE_EXCP_PABT                 = 3,
	SCE_EXCP_DABT                 = 4,
	SCE_EXCP_UNUSED               = 5,
	SCE_EXCP_IRQ                  = 6,
	SCE_EXCP_FIQ                  = 7
} SceExcpKind;

/**
 * Get a pointer to SceExcpmgr's internal data
 * 
 * This is only used by exception handlers.
 *
 * @return pointer to excpmgr data section.
*/
void *sceExcpmgrGetData(void);

/**
 * Register an exception handler
 *
 * `handler` must point to eight bytes of space followed by the handler code.
 * The space will be used in the internal linked list structure.
 *
 * @param[in]  kind      The kind of exception
 * @param[in]  priority  The priority (must be 0 <= priority < 8), 0 highest
 * @param      handler   The handler
 *
 * @return     Error code or zero on success
 */
int sceExcpmgrRegisterHandler(SceExcpKind kind, int priority, void *handler);

#ifdef __cplusplus
}
#endif

#endif /* _VDSUITE_KERNEL_KERNEL_EXCPMGR_H */

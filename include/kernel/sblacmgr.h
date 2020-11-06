/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_KERNEL_SBLACMGR_H
#define _VDSUITE_KERNEL_SBLACMGR_H

#include <scetypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Get process type state
 *
 * @param[in]  pid - The target process id
 *
 * @return If root mode process, 1. else 0.
 */
int sceSblACMgrIsRootProgram(SceUID pid);

/**
 * @brief Get process type state
 *
 * @param[in]  pid - The target process id
 *
 * @return If system mode process, 1. else 0.
 */
int sceSblACMgrIsSystemProgram(SceUID pid);

/**
 * @brief Get process type state
 *
 * @param[in]  pid - The target process id
 *
 * @return If pspemu process, 1. else 0.
 */
int sceSblACMgrIsPspEmu(SceUID pid);

/**
 * @brief Get process type state
 *
 * @param[in]  pid - The target process id
 *
 * @return If game mode process, 1. else 0.
 */
int sceSblACMgrIsGameProgram(SceUID pid);

/**
 * @brief Get process type state
 *
 * @param[in]  pid - The target process id
 *
 * @return If non game mode process, 1. else 0.
 */
int sceSblACMgrIsNonGameProgram(SceUID pid);

/**
 * @brief Get process type state
 *
 * @param[in]  pid - The target process id
 *
 * @return If SceShell process(authid:0x2800000000000001), 1. else 0.
 */
int sceSblACMgrIsSceShell(SceUID pid);

/**
 * @brief Get process type state
 *
 * @param[in]  pid - The target process id
 *
 * @return If fake self process, 1. else 0.
 */
int sceSblACMgrIsFself(SceUID pid);

/**
 * @brief Get process authority id
 *
 * @param[in]  pid    - The target process id
 * @param[out] authid - The authid output pointer
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblACMgrGetProcessProgramAuthId(SceUID pid, SceUInt64 *authid);

/**
 * @brief Get development mode state
 *
 * @return If development mode, 1. else 0.
 */
int sceSblACMgrIsDevelopmentMode(void);

#ifdef __cplusplus
}
#endif

#endif /* _VDSUITE_KERNEL_SBLACMGR_H */


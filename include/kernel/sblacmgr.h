/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_KERNEL_SBLACMGR_H
#define _VDSUITE_KERNEL_SBLACMGR_H

#include <scetypes.h>

#ifdef __cplusplus
extern "C" {
#endif

int sceSblACMgrIsSystemProgram(SceUID pid);
int sceSblACMgrIsPspEmu(SceUID pid);
int sceSblACMgrIsGameProgram(SceUID pid);
int sceSblACMgrIsNonGameProgram(SceUID pid);
int sceSblACMgrIsDevelopmentMode(void);

#ifdef __cplusplus
}
#endif

#endif /* _VDSUITE_KERNEL_SBLACMGR_H */


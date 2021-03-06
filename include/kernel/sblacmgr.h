/*
	Vita Development Suite Libraries
*/

#ifndef _PSP2_KERNEL_SBLACMGR_H_
#define _PSP2_KERNEL_SBLACMGR_H_

#include <scetypes.h>

#ifdef __cplusplus
extern "C" {
#endif

int sceSblACMgrIsShell(SceUID pid);
int sceSblACMgrIsPspEmu(SceUID pid);
int sceSblACMgrIsGameProgram(SceUID pid);
int sceSblACMgrIsNonGameProgram(SceUID pid);
int sceSblACMgrIsDevelopmentMode(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_SBLACMGR_H_ */


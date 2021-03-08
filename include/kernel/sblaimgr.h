/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_KERNEL_SBLAIMGR_H
#define _VDSUITE_KERNEL_SBLAIMGR_H

#ifdef __cplusplus
extern "C" {
#endif

int sceSblAimgrGetSMI(void);
int sceSblAimgrGetTargetId(void);
int sceSblAimgrIsTest(void);
int sceSblAimgrIsTool(void);
int sceSblAimgrIsDEX(void);
int sceSblAimgrIsCEX(void);
int sceSblAimgrIsVITA(void);
int sceSblAimgrIsDolce(void);
int sceSblAimgrIsGenuineVITA(void);
int sceSblAimgrIsGenuineDolce(void);

#ifdef __cplusplus
}
#endif

#endif /* _VDSUITE_KERNEL_SBLAIMGR_H */


/*
	Vita Development Suite Libraries
*/

#ifndef _PSP2_KERNEL_SBLAUTHMGR_H_
#define _PSP2_KERNEL_SBLAUTHMGR_H_

#include <scetypes.h>

#ifdef __cplusplus
extern "C" {
#endif

int sceSblAuthMgrClearDmac5Key(int slot_id, int val);
int sceSblAuthMgrSetDmac5Key(const void *key, SceSize keylen, int slot_id, int key_id);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_SBLAUTHMGR_H_ */


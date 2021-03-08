/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_KERNEL_SBLAUTHMGR_H
#define _VDSUITE_KERNEL_SBLAUTHMGR_H

#include <scetypes.h>

#ifdef __cplusplus
extern "C" {
#endif

int sceSblAuthMgrClearDmac5Key(int slot_id, int val);
int sceSblAuthMgrSetDmac5Key(const void *key, SceSize keylen, int slot_id, int key_id);

#ifdef __cplusplus
}
#endif

#endif /* _VDSUITE_KERNEL_SBLAUTHMGR_H */


/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_KERNEL_IDSTORAGE_H
#define _VDSUITE_KERNEL_IDSTORAGE_H

#include <scetypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @param[in]  leafnum - 0x0 ~ 0x80 / leafnum > 0x80 = error
 * @param[out] buf     - Leaf data, size is 512 byte
 *
 * @return 0 on success, < 0 on error.
 */
int sceIdStorageReadLeaf(SceSize leafnum, void *buf);
  
/**
 * @param[in] leafnum - 0x0 ~ 0x80 / leafnum > 0x80 = error
 * @param[in] buf     - Leaf data, size is 512 byte
 *
 * @return 0 on success, < 0 on error.
 */
int sceIdStorageWriteLeaf(SceSize leafnum, const void *buf);

#ifdef __cplusplus
}
#endif

#endif /* _VDSUITE_KERNEL_IDSTORAGE_H */

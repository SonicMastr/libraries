/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_USER_KERNEL_RNG_H
#define _VDSUITE_USER_KERNEL_RNG_H

#include <scetypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Fills the output buffer with random data.
 *
 * @param[out] output - Output buffer
 * @param[in] size - Size of the output buffer, 64 bytes maximum
 *
 * @return 0 on success, < 0 on error.
*/
int sceKernelGetRandomNumber(void *output, SceSize size);

#ifdef __cplusplus
}
#endif

#endif /* _VDSUITE_USER_KERNEL_RNG_H */


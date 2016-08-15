#ifndef _PSP2_KERNEL_RNG_H_
#define _PSP2_KERNEL_RNG_H_

/***
 * Fills the output buffer with random data.
 *
 * @param[out] output - Output buffer
 * @param[in] size - Size of the output buffer, 64 bytes maximum
 *
 * @return 0 on success, < 0 on error.
*/
int sceKernelGetRandomNumber(void *output, unsigned size);

#endif

/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_KERNEL_KERNEL_SYSCLIB_H
#define _VDSUITE_KERNEL_KERNEL_SYSCLIB_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Like memcmp but checks all n bytes of s1 and s2 without early return.
 */
int memcmp_consttime(const void *s1, const void *s2, size_t n);

/**
 * Like strncpy but puts 0 or 1 zero bytes after copying src to dest,
 * rather than filling dest with zero bytes up to n.
 */
char *strncpy_fast(char *dest, const char *src, size_t n);

#ifdef __cplusplus
}
#endif

#endif /* _VDSUITE_KERNEL_KERNEL_SYSCLIB_H */

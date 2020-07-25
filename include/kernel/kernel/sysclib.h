#ifndef _DOLCESDK_PSP2KERN_KERNEL_SYSCLIB_H_
#define _DOLCESDK_PSP2KERN_KERNEL_SYSCLIB_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Left shift with only register operations (no memory access).
 */
SceInt64 lshift(SceInt64 value, int shift);

/**
 * Arithmetic right shift with only register operations (no memory access).
 */
SceInt64 rshift(SceInt64 value, int shift);

/**
 * Arithmetic right shift with only register operations (no memory access).
 * May be faster than rshift for shift less than 32.
 */
SceInt64 rshift_fast(SceInt64 value, int shift);

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

#endif /* _DOLCESDK_PSP2KERN_KERNEL_SYSCLIB_H_ */

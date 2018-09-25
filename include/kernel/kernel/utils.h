#ifndef _PSP2_KERNEL_UTILS_H_
#define _PSP2_KERNEL_UTILS_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SCE_SHA1_BLOCK_SIZE    64
#define SCE_SHA1_DIGEST_SIZE   20
#define SCE_SHA224_BLOCK_SIZE  64
#define SCE_SHA224_DIGEST_SIZE 28
#define SCE_SHA256_BLOCK_SIZE  64
#define SCE_SHA256_DIGEST_SIZE 32

typedef struct SceSha1Context {
	uint32_t h[5];
	uint16_t usRemains;
	uint16_t usComputed;
	uint64_t ullTotalLen;
	char buf[SCE_SHA1_BLOCK_SIZE];
	char result[SCE_SHA1_DIGEST_SIZE];
	uint32_t pad;
} SceSha1Context;

typedef struct SceSha224Context {
	uint32_t h[8];
	uint32_t pad;
	uint16_t usRemains;
	uint16_t usComputed;
	uint64_t ullTotalLen;
	char buf[SCE_SHA224_BLOCK_SIZE];
	char result[SCE_SHA224_DIGEST_SIZE];
	uint32_t pad2;
} SceSha224Context;

typedef struct SceSha256Context {
	uint32_t h[8];
	uint32_t pad;
	uint16_t usRemains;
	uint16_t usComputed;
	uint64_t ullTotalLen;
	char buf[SCE_SHA256_BLOCK_SIZE];
	char result[SCE_SHA256_DIGEST_SIZE];
} SceSha256Context;

int sceSha1BlockInit(SceSha1Context *pContext);
int sceSha1BlockUpdate(SceSha1Context *pContext, const void *plain, uint32_t len);
int sceSha1BlockResult(SceSha1Context *pContext, char *digest);
int sceSha1Digest(const void *plain, uint32_t len, char *result);

int sceSha224BlockInit(SceSha224Context *pContext);
int sceSha224BlockUpdate(SceSha224Context *pContext, const void *plain, uint32_t len);
int sceSha224BlockResult(SceSha224Context *pContext, char *digest);
int sceSha224Digest(const void *plain, uint32_t len, char *result);

int sceSha256BlockInit(SceSha256Context *pContext);
int sceSha256BlockUpdate(SceSha256Context *pContext, const void *plain, uint32_t len);
int sceSha256BlockResult(SceSha256Context *pContext, char *digest);
int sceSha256Digest(const void *plain, uint32_t len, char *result);

int sceHmacSha1Digest(const unsigned char *key, uint32_t key_len, const void *plain, uint32_t len, char *result);
int sceHmacSha224Digest(const unsigned char *key, uint32_t key_len, const void *plain, uint32_t len, char *result);
int sceHmacSha256Digest(const unsigned char *key, uint32_t key_len, const void *plain, uint32_t len, char *result);

/**
 * @param[out] dst - dst buf
 * @param[in] dst_size - Size when decompressed
 * @param[in] src - Gzip compressed data
 * @param[out] crc32 - crc32 when decompressed
 *
 * @return dst_size on success, < 0 on error.
 */
int sceGzipDecompress(void *dst, int dst_size, const void *src, int *crc32);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_UTILS_H_ */

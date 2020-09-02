#ifndef _PSP2_PAF_H_
#define _PSP2_PAF_H_

#include <psp2/types.h>
#include <psp2/ces/error.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ScePafString {
	char *data;
	SceSize length;
} ScePafString;

typedef struct ScePafWString {
	SceWChar16 *data;
	SceSize length;
} ScePafWString;

/**
 * std C functions
 */

void sce_paf_free(void *ptr);
void *sce_paf_malloc(SceSize size);
void *sce_paf_bzero(void *ptr, SceSize num);
void *sce_paf_memchr(const void *ptr, int value, SceSize num);
int sce_paf_memcmp(const void *ptr1, const void *ptr2, SceSize num);
int sce_paf_bcmp(const void *ptr1, const void *ptr2, SceSize num);
void *sce_paf_memcpy(void *destination, const void *source, SceSize num);
void *sce_paf_memcpy2(void *destination, const void *source, SceSize num);
void *sce_paf_memmove(void *destination, const void *source, SceSize num);
void *sce_paf_bcopy(void *destination, const void *source, SceSize num);
void *sce_paf_memset(void *ptr, int value, SceSize num);
int sce_paf_snprintf(char *s, SceSize n, const char *format, ...);
int sce_paf_strcasecmp(const char *str1, const char *str2);
char *sce_paf_strchr(const char *str, int character);
int sce_paf_strcmp(const char *str1, const char *str2);
size_t sce_paf_strlen(const char *str);
int sce_paf_strncasecmp(const char *str1, const char *str2, SceSize num);
int sce_paf_strncmp(const char *str1, const char *str2, SceSize num);
char *sce_paf_strncpy(char *destination, const char *source, SceSize num);
char *sce_paf_strrchr(const char *str, int character);

/**
 * CES functions
 */

#define SCE_PAF_CES_ALLOW_ILLEGAL_CODE      0x2
#define SCE_PAF_CES_ALLOW_OUT_OF_CODE_RANGE 0x4
#define SCE_PAF_CES_ALLOW_INVALID_ENCODE    0x8
#define SCE_PAF_CES_ALLOW_SRC_BUFFER_END    0x10

/* UTF8 to UTF16 */

SceSSize scePafCesUtf8ToUtf16(const ScePafString *utf8, ScePafWString *utf16);

SceSSize scePafCesUtf8ToUtf16WithFlag(const ScePafString *utf8, ScePafWString *utf16, SceUInt32 flags);

SceSSize scePafCesUtf8CharToUtf16(const char *utf8, ScePafWString *utf16);

SceSSize scePafCesUtf8CharToUtf16WithFlag(const char *utf8, ScePafWString *utf16, SceUInt32 flags);

ScePafWString *scePafCesUtf8CharToUtf16WithAlloc(const char *utf8, ScePafWString *utf16);

/* UTF16 to UTF8 */

SceSSize scePafCesUtf16ToUtf8(const ScePafWString *utf16, ScePafString *utf8);

SceSSize scePafCesUtf16ToUtf8WithFlag(const ScePafWString *utf16, ScePafString *utf8, SceUInt32 flags);

SceSSize scePafCesUtf16CharToUtf8(const SceWChar16 *utf16, ScePafString *utf8);

SceSSize scePafCesUtf16CharToUtf8WithFlag(const SceWChar16 *utf16, ScePafString *utf8, SceUInt32 flags);

ScePafString *scePafCesUtf16CharToUtf8WithAlloc(const SceWChar16 *utf16, ScePafString *utf8);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_PAF_H_ */


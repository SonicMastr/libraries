/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_KERNEL_SBLAIMGR_H
#define _VDSUITE_KERNEL_SBLAIMGR_H

#include <scetypes.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceProductCode {
	SCE_PRODUCT_CODE_NONE     = 0x00000000,
	SCE_PRODUCT_CODE_TEST     = 0x100, // Internal Test Unit
	SCE_PRODUCT_CODE_TOOL     = 0x101, // Development kit
	SCE_PRODUCT_CODE_DEX      = 0x102, // Testing kit
	SCE_PRODUCT_CODE_CEX_J1   = 0x103, // Japan
	SCE_PRODUCT_CODE_CEX_UC2  = 0x104, // united ctates
	SCE_PRODUCT_CODE_CEX_CEL  = 0x105,
	SCE_PRODUCT_CODE_CEX_KR2  = 0x106,
	SCE_PRODUCT_CODE_CEX_CEK  = 0x107,
	SCE_PRODUCT_CODE_CEX_MX2  = 0x108,
	SCE_PRODUCT_CODE_CEX_AU3  = 0x109,
	SCE_PRODUCT_CODE_CEX_E12  = 0x10A,
	SCE_PRODUCT_CODE_CEX_TW1  = 0x10B, // taiwan
	SCE_PRODUCT_CODE_CEX_RU3  = 0x10C,
	SCE_PRODUCT_CODE_CEX_CN9  = 0x10D,
	SCE_PRODUCT_CODE_CEX_HK5  = 0x10E,
	SCE_PRODUCT_CODE_CEX_RSV1 = 0x10F,
	SCE_PRODUCT_CODE_CEX_RSV2 = 0x110,
	SCE_PRODUCT_CODE_CEX_RSV3 = 0x111
} SceProductCode;

/**
 * @brief Get service/manufacturing information(factory fw).
 *
 * @param[out] info - The info output pointer
 *
 * @return 0 on success, < 0 on error.
 */
int sceSblAimgrGetSMI(SceUInt32 *info);

/**
 * @brief Get product code.
 *
 * @return see:SceProductCode.
 */
int sceSblAimgrGetProductCode(void);

/**
 * @brief Get system type state.
 *
 * @return If product code is TEST, 1. else 0.
 */
int sceSblAimgrIsTest(void);

/**
 * @brief Get system type state.
 *
 * @return If product code is TOOL, 1. else 0.
 */
int sceSblAimgrIsTool(void);

/**
 * @brief Get system type state.
 *
 * @return If product code is DEX, 1. else 0.
 */
int sceSblAimgrIsDEX(void);

/**
 * @brief Get system type state.
 *
 * @return If product code is CEX, 1. else 0.
 */
int sceSblAimgrIsCEX(void);

/**
 * @brief Get system type state.
 *
 * @return If device is vita, 1. else 0.
 */
int sceSblAimgrIsVITA(void);

/**
 * @brief Get system type state.
 *
 * @return If device is dolce, or PSTV emu enabled, 1. else 0.
 */
int sceSblAimgrIsDolce(void);

/**
 * @brief Get system type state.
 *
 * @return If device is vita, 1. else 0.
 */
int sceSblAimgrIsGenuineVITA(void);

/**
 * @brief Get system type state.
 *
 * @return If device is dolce, 1. else 0.
 */
int sceSblAimgrIsGenuineDolce(void);

#ifdef __cplusplus
}
#endif

#endif /* _VDSUITE_KERNEL_SBLAIMGR_H */


/*
	Vita Development Suite Libraries
*/

#ifndef _DOLCESDK_PSP2_JPEGARM_H_
#define _DOLCESDK_PSP2_JPEGARM_H_

#include <scejpeg.h>

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif

/* Error codes */
#define SCE_JPEG_ARM_OK                          (SCE_JPEG_OK)

#define SCE_JPEG_ARM_ERROR_IMAGE_EMPTY           (SCE_JPEG_ERROR_IMAGE_EMPTY           | 0x100)
#define SCE_JPEG_ARM_ERROR_BAD_MARKER_LENGTH     (SCE_JPEG_ERROR_BAD_MARKER_LENGTH     | 0x100)
#define SCE_JPEG_ARM_ERROR_BAD_DHT_COUNTS        (SCE_JPEG_ERROR_BAD_DHT_COUNTS        | 0x100)
#define SCE_JPEG_ARM_ERROR_BAD_DHT_INDEX         (SCE_JPEG_ERROR_BAD_DHT_INDEX         | 0x100)
#define SCE_JPEG_ARM_ERROR_BAD_DQT_INDEX         (SCE_JPEG_ERROR_BAD_DQT_INDEX         | 0x100)
#define SCE_JPEG_ARM_ERROR_DECODE_ERROR          (SCE_JPEG_ERROR_DECODE_ERROR          | 0x100)
#define SCE_JPEG_ARM_ERROR_INVALID_POINTER       (SCE_JPEG_ERROR_INVALID_POINTER       | 0x100)
#define SCE_JPEG_ARM_ERROR_BAD_COMPONENT_ID      (SCE_JPEG_ERROR_BAD_COMPONENT_ID      | 0x100)
#define SCE_JPEG_ARM_ERROR_UNSUPPORT_COLORSPACE  (SCE_JPEG_ERROR_UNSUPPORT_COLORSPACE  | 0x100)
#define SCE_JPEG_ARM_ERROR_BAD_MCU_SIZE          (SCE_JPEG_ERROR_BAD_MCU_SIZE          | 0x100)
#define SCE_JPEG_ARM_ERROR_BAD_PRECISION         (SCE_JPEG_ERROR_BAD_PRECISION         | 0x100)
#define SCE_JPEG_ARM_ERROR_UNSUPPORT_SAMPLING    (SCE_JPEG_ERROR_UNSUPPORT_SAMPLING    | 0x100)
#define SCE_JPEG_ARM_ERROR_COMPONENT_COUNT       (SCE_JPEG_ERROR_COMPONENT_COUNT       | 0x100)
#define SCE_JPEG_ARM_ERROR_EOI_EXPECTED          (SCE_JPEG_ERROR_EOI_EXPECTED          | 0x100)
#define SCE_JPEG_ARM_ERROR_UNSUPPORT_IMAGE_SIZE  (SCE_JPEG_ERROR_UNSUPPORT_IMAGE_SIZE  | 0x100)
#define SCE_JPEG_ARM_ERROR_NO_HUFF_TABLE         (SCE_JPEG_ERROR_NO_HUFF_TABLE         | 0x100)
#define SCE_JPEG_ARM_ERROR_NO_QUANT_TABLE        (SCE_JPEG_ERROR_NO_QUANT_TABLE        | 0x100)
#define SCE_JPEG_ARM_ERROR_NO_SOI                (SCE_JPEG_ERROR_NO_SOI                | 0x100)
#define SCE_JPEG_ARM_ERROR_BAD_DHT_MARKER        (SCE_JPEG_ERROR_BAD_DHT_MARKER        | 0x100)
#define SCE_JPEG_ARM_ERROR_BAD_DRI_MARKER        (SCE_JPEG_ERROR_BAD_DRI_MARKER        | 0x100)
#define SCE_JPEG_ARM_ERROR_BAD_SOF_MARKER        (SCE_JPEG_ERROR_BAD_SOF_MARKER        | 0x100)
#define SCE_JPEG_ARM_ERROR_BAD_SOS_MARKER        (SCE_JPEG_ERROR_BAD_SOS_MARKER        | 0x100)
#define SCE_JPEG_ARM_ERROR_SOF_DUPLICATE         (SCE_JPEG_ERROR_SOF_DUPLICATE         | 0x100)
#define SCE_JPEG_ARM_ERROR_NO_LOSSLESS_SUPPORT   (SCE_JPEG_ERROR_NO_LOSSLESS_SUPPORT   | 0x100)
#define SCE_JPEG_ARM_ERROR_NO_ARITH_SUPPORT      (SCE_JPEG_ERROR_NO_ARITH_SUPPORT      | 0x100)
#define SCE_JPEG_ARM_ERROR_UNKNOWN_MARKER        (SCE_JPEG_ERROR_UNKNOWN_MARKER        | 0x100)
#define SCE_JPEG_ARM_ERROR_BAD_RESTART_MARKER    (SCE_JPEG_ERROR_BAD_RESTART_MARKER    | 0x100)
#define SCE_JPEG_ARM_ERROR_UNEXPECTED_MARKER     (SCE_JPEG_ERROR_UNEXPECTED_MARKER     | 0x100)
#define SCE_JPEG_ARM_ERROR_INVALID_REGION        (SCE_JPEG_ERROR_INVALID_REGION        | 0x100)
#define SCE_JPEG_ARM_ERROR_INVALID_STATE         (SCE_JPEG_ERROR_INVALID_STATE         | 0x100)
#define SCE_JPEG_ARM_ERROR_CANNOT_CONTINUE       (SCE_JPEG_ERROR_CANNOT_CONTINUE       | 0x100)
#define SCE_JPEG_ARM_ERROR_MEMORY_SIZE           (SCE_JPEG_ERROR_MEMORY_SIZE           | 0x100)
#define SCE_JPEG_ARM_ERROR_INVALID_COLOR_FORMAT  (SCE_JPEG_ERROR_INVALID_COLOR_FORMAT  | 0x100)
#define SCE_JPEG_ARM_ERROR_INVALID_DECODE_MODE   (SCE_JPEG_ERROR_INVALID_DECODE_MODE   | 0x100)
#define SCE_JPEG_ARM_ERROR_BAD_PROGRESSIVE_PARAM (SCE_JPEG_ERROR_BAD_PROGRESSIVE_PARAM | 0x100)
#define SCE_JPEG_ARM_ERROR_INIT_DONE             (SCE_JPEG_ERROR_INIT_DONE             | 0x100)
#define SCE_JPEG_ARM_ERROR_INPUT_SUSPENDED       (SCE_JPEG_ERROR_INPUT_SUSPENDED       | 0x100)
#define SCE_JPEG_ARM_ERROR_INPUT_DATA_TOO_BIG    (SCE_JPEG_ERROR_INPUT_DATA_TOO_BIG    | 0x100)
#define SCE_JPEG_ARM_ERROR_INVALID_DATA_SIZE     (SCE_JPEG_ERROR_INVALID_DATA_SIZE     | 0x100)

/* for backward compatibility */
#define SCE_JPEG_ARM_ERROR_UNSUPPORT_DOWNSCALE   (SCE_JPEG_ARM_ERROR_INVALID_DECODE_MODE)
#define SCE_JPEG_ARM_ERROR_OUT_OF_MEMORY         (SCE_JPEG_ARM_ERROR_MEMORY_SIZE)

/* Decode JPEG data to RGBA format */
int sceJpegArmDecodeMJpeg(
		const unsigned char *pJpeg,
		SceSize isize,
		void *pRGBA,
		SceSize osize,
		int decodeMode,
		void *pCoefBuffer,
		SceSize coefBufferSize);

/* Decode JPEG data (no color conversion) */
int sceJpegArmDecodeMJpegYCbCr(
		const unsigned char *pJpeg,
		SceSize isize,
		unsigned char *pYCbCr,
		SceSize osize,
		int decodeMode,
		void *pCoefBuffer,
		SceSize coefBufferSize);

/* tempBufferSize is always 0, even when using colour space conversion */
typedef SceJpegOutputInfo SceJpegArmOutputInfo;

/* Return color space and each buffer sizes required when decoding a JPEG image */
int sceJpegArmGetOutputInfo(
		const unsigned char *pJpeg,
		SceSize isize,
		int outputFormat,
		int decodeMode,
		SceJpegArmOutputInfo *pOutputInfo);

/* Split decoder (control struct is different from sceJpeg, no reference anywhere in the apps)
 * These functions cannot be used at the moment.
 */

int sceJpegArmCreateSplitDecoder(void *pCtrl);
int sceJpegArmDeleteSplitDecoder(void *pCtrl);

int sceJpegArmSplitDecodeMJpeg(void *pCtrl);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif /* _DOLCESDK_PSP2_JPEGARM_H_ */


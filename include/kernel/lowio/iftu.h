/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_KERNEL_LOWIO_IFTU_H
#define _VDSUITE_KERNEL_LOWIO_IFTU_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceIftuErrorCode {
	SCE_IFTU_ERROR_INVALID_PLANE		= (int)0x803F0700,
	SCE_IFTU_ERROR_INVALID_PARAM		= (int)0x803F0701,
	SCE_IFTU_ERROR_INVALID_PIXELFORMAT	= (int)0x803F0703,
	SCE_IFTU_ERROR_PLANE_BUSY		= (int)0x803F0704,
} SceIftuErrorCode;

typedef enum SceIftuPixelformat {
	SCE_IFTU_PIXELFORMAT_BGR565		= 0x01,
	SCE_IFTU_PIXELFORMAT_RGB565		= 0x02,
	SCE_IFTU_PIXELFORMAT_BGRA5551		= 0x04,
	SCE_IFTU_PIXELFORMAT_RGBA5551		= 0x08,
	SCE_IFTU_PIXELFORMAT_BGRX8888		= 0x10,
	SCE_IFTU_PIXELFORMAT_RGBX8888		= 0x20,
	SCE_IFTU_PIXELFORMAT_BGRA1010102	= 0x40,
	SCE_IFTU_PIXELFORMAT_RGBA1010102	= 0x80,
	SCE_IFTU_PIXELFORMAT_BGRP		= 0x100,	/* 3 planes - R, G, B */
	SCE_IFTU_PIXELFORMAT_RGBX8888_MULT	= 0x1000,
	SCE_IFTU_PIXELFORMAT_BGRX8888_MULT	= 0x2000,
	SCE_IFTU_PIXELFORMAT_RGBA1010102_MULT	= 0x4000,
	SCE_IFTU_PIXELFORMAT_BGRA1010102_MULT	= 0x8000,
	SCE_IFTU_PIXELFORMAT_NV12		= 0x10000,	/* 2 planes - Y, Cb + Cr interleaved */
	SCE_IFTU_PIXELFORMAT_YUV420		= 0x20000,	/* 3 planes - Y, Cb, Cr */
	SCE_IFTU_PIXELFORMAT_YUV422		= 0x200000,	/* 3 planes - Y, Cb, Cr */
} SceIftuPixelformat;

typedef struct SceIftuCscParams {
	unsigned int post_add_0;		/* 10-bit integer */
	unsigned int post_add_1_2;		/* 10-bit integer */
	unsigned int post_clamp_max_0;		/* 10-bit integer */
	unsigned int post_clamp_min_0;		/* 10-bit integer */
	unsigned int post_clamp_max_1_2;	/* 10-bit integer */
	unsigned int post_clamp_min_1_2;	/* 10-bit integer */
	unsigned int ctm[3][3];			/* S3.9 fixed point format */
} SceIftuCscParams;

typedef struct SceIftuConvParams {
	unsigned int size;
	unsigned int unk04;
	SceIftuCscParams *csc_params1;
	SceIftuCscParams *csc_params2;
	unsigned int csc_control;
	unsigned int unk14;
	unsigned int unk18;
	unsigned int unk1C;
	unsigned int alpha;
	unsigned int unk24;
} SceIftuConvParams;

typedef struct SceIftuFrameBuf {
	unsigned int pixelformat;
	unsigned int width;		/* Aligned to 16 */
	unsigned int height;		/* Aligned to 8 */
	unsigned int leftover_stride;	/* (pitch - aligned_w) * bpp */
	unsigned int leftover_align;	/* if YCbCr: (width >> 1) & 0xF [chroma align?] */
	unsigned int paddr0;		/* Physical address of the first plane */
	unsigned int paddr1;		/* Physical address of the second plane */
	unsigned int paddr2;		/* Physical address of the third plane */
} SceIftuFrameBuf;

typedef struct SceIftuPlaneState {
	SceIftuFrameBuf fb;
	unsigned int unk20;             /* not observed to be non-zero */
	unsigned int unk24;             /* not observed to be non-zero */
	unsigned int unk28;             /* not observed to be non-zero */
	unsigned int src_w;             /* inverse scaling factor in 16.16 fixed point, greater than or equal to 0.25 */
	unsigned int src_h;             /* inverse scaling factor in 16.16 fixed point, greater than or equal to 0.25 */
	unsigned int dst_x;             /* offset into the destination buffer */
	unsigned int dst_y;             /* offset into the destination buffer */
	unsigned int src_x;             /* offset into the source buffer in 8.8 fixed point, strictly less than 4.0 */
	unsigned int src_y;             /* offset into the source buffer in 8.8 fixed point, strictly less than 4.0 */
	unsigned int crop_top;
	unsigned int crop_bot;
	unsigned int crop_left;
	unsigned int crop_right;
} SceIftuPlaneState;

int sceIftuCsc(SceIftuFrameBuf *dst, SceIftuPlaneState *src, SceIftuConvParams *params);

#ifdef __cplusplus
}
#endif

#endif /* _VDSUITE_KERNEL_LOWIO_IFTU_H */


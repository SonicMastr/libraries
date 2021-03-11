/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_USER_AVCDEC_H
#define _VDSUITE_USER_AVCDEC_H

#include <videodec.h>
#include_next <avcdec.h>

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif /* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

/* For use in sceAvcdecSetDecodeMode() */
#define SCE_AVCDEC_MODE_EXTENDED				(0x80U)

/* For use in sceAvcdecSetLowDelayModeNongameapp() */
#define SCE_AVCDEC_DELAY_MODE_LOW					(0)
#define SCE_AVCDEC_DELAY_MODE_1						(2)
#define SCE_AVCDEC_DELAY_MODE_2						(4)
#define SCE_AVCDEC_DELAY_MODE_HIGH					(6)

extern SceInt32 sceAvcdecSetDecodeMode(SceUInt32 codecType, SceInt32 mode);

/* Internal */

extern SceInt32 sceAvcdecSetDecodeModeInternal(SceUInt32 codecType, SceInt32 mode);
extern SceInt32 sceAvcdecRegisterCallbackInternal(SceAvcdecCtrl *pCtrl, SceUID cbId, int unk);
extern SceInt32 sceAvcdecUnregisterCallbackInternal(SceAvcdecCtrl *pCtrl);
extern SceInt32 sceAvcdecUnregisterCallbackWithCbidInternal(SceAvcdecCtrl *pCtrl, SceUID cbId);

extern SceInt32 sceAvcdecQueryDecoderMemSizeInternal(SceUInt32 codecType, const SceAvcdecQueryDecoderInfo *pDecoderInfo, SceAvcdecDecoderInfo *pMemInfo);
extern SceInt32 sceAvcdecCreateDecoderInternal(SceUInt32 codecType, SceAvcdecCtrl *pCtrl, const SceAvcdecQueryDecoderInfo *pDecoderInfo);

extern SceInt32 sceAvcdecDecodeAuInternal(SceAvcdecCtrl *pCtrl, const SceAvcdecAu *pAu, int *pTimeout);
extern SceInt32 sceAvcdecDecodeGetPictureInternal(SceAvcdecCtrl *pCtrl, SceAvcdecArrayPicture *pArrayPicture, int* pTimeout);
extern SceInt32 sceAvcdecDecodeGetPictureWithWorkPictureInternal(SceAvcdecCtrl *pCtrl, SceAvcdecArrayPicture *pArrayPicture, SceAvcdecArrayPicture *pArrayWorkPicture, int* pTimeout);

/* Nongame and SceVideodecAsyncUser */

extern SceInt32 sceAvcdecSetRecoveryPointSEIMode(SceUInt32 codecType, SceInt32 mode);

extern SceInt32 sceAvcdecDecodeSetTrickModeNongameapp(SceUInt32 codecType, SceInt32 mode);
extern SceInt32 sceAvcdecSetLowDelayModeNongameapp(SceUInt32 codecType, SceInt32 mode);
extern SceInt32 sceAvcdecRegisterCallbackNongameapp(SceAvcdecCtrl *pCtrl, SceUID cbId, int unk);
extern SceInt32 sceAvcdecUnregisterCallbackNongameapp(SceAvcdecCtrl *pCtrl);
extern SceInt32 sceAvcdecUnregisterCallbackWithCbidNongameapp(SceAvcdecCtrl *pCtrl, SceUID cbId);

extern SceInt32 sceAvcdecCreateDecoderNongameapp(SceUInt32 codecType, SceAvcdecCtrl *pCtrl, const SceAvcdecQueryDecoderInfo *pDecoderInfo);
extern SceInt32 sceAvcdecQueryDecoderMemSizeNongameapp(SceUInt32 codecType, const SceAvcdecQueryDecoderInfo *pDecoderInfo, SceAvcdecDecoderInfo *pMemInfo);

extern SceInt32 sceAvcdecDecodeAuNongameapp(SceAvcdecCtrl *pCtrl, const SceAvcdecAu *pAu, int *pTimeout);
extern SceInt32 sceAvcdecDecodeGetPictureNongameapp(SceAvcdecCtrl *pCtrl, SceAvcdecArrayPicture *pArrayPicture, int* pTimeout);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif /* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

#endif /* _VDSUITE_USER_AVCDEC_H */


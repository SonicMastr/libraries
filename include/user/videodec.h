#ifndef _DOLCESDK_PSP2_VIDEODEC_H_
#define _DOLCESDK_PSP2_VIDEODEC_H_

#include_next <videodec.h>

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif /* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

/* decoder init type */
#define SCE_VIDEODEC_TYPE_HW_MPEG4	(0x1002U)

extern SceInt32 sceVideodecSetConfig(SceUInt32 codecType, SceInt32 config);

/* Internal */

extern SceInt32 sceVideodecSetConfigInternal(SceUInt32 codecType, SceInt32 config);

extern SceInt32 sceVideodecQueryMemSizeInternal(SceUInt32 codecType, const SceVideodecQueryInitInfo *pInitInfo, SceVideodecMemInfo *pMemInfo);
extern SceInt32 sceVideodecInitLibraryInternal(SceUInt32 codecType, const SceVideodecQueryInitInfoHwAvcdec *pInitInfo);
extern SceInt32 sceVideodecInitLibraryWithUnmapMemInternal(SceUInt32 codecType, SceVideodecCtrl *pCtrl, const SceVideodecQueryInitInfo *pInitInfo);

/* Nongame */

extern SceInt32 sceVideodecQueryMemSizeNongameapp(SceUInt32 codecType, const SceVideodecQueryInitInfo *pInitInfo, SceVideodecMemInfo *pMemInfo);
extern SceInt32 sceVideodecInitLibraryNongameapp(SceUInt32 codecType, const SceVideodecQueryInitInfoHwAvcdec *pInitInfo);
extern SceInt32 sceVideodecInitLibraryWithUnmapMemNongameapp(SceUInt32 codecType, SceVideodecCtrl *pCtrl, const SceVideodecQueryInitInfo *pInitInfo);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif /* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

#endif /* _DOLCESDK_PSP2_VIDEODEC_H_ */


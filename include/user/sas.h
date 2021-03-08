/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_USER_SAS_H
#define _VDSUITE_USER_SAS_H

#include_next <sas.h>

#ifdef __cplusplus
extern "C" {
#endif

SceSasResult sceSasCheckGrain(SceUInt32 grain);

/* SAS internal functions */

SceSasResult sceSasGetNeededMemorySizeInternal(const char *config, SceSize *outSize);
SceSasResult sceSasInitInternal(const char *config, void *buffer, SceSize bufferSize, SceUID *sasCoreId);
SceSasResult sceSasExitInternal(SceUID sasCoreId, void **outBuffer, SceSize *outBufferSize);

SceSasResult sceSasSetGrainInternal(SceUID sasCoreId, SceUInt32 grain);
SceSasResult sceSasGetGrainInternal(SceUID sasCoreId);
SceSasResult sceSasSetOutputmodeInternal(SceUID sasCoreId, SceUInt32 outputmode);
SceSasResult sceSasGetOutputmodeInternal(SceUID sasCoreId);

SceSasResult sceSasCoreInternal(SceUID sasCoreId, SceInt16 *inOut, SceInt32 lvol, SceInt32 rvol);

SceSasResult sceSasSetVoiceInternal(SceUID sasCoreId, SceInt32 iVoiceNum, const void *vagBuf, SceSize size, SceUInt32 loopflag);
SceSasResult sceSasSetVoicePCMInternal(SceUID sasCoreId, SceInt32 iVoiceNum, const void *pcmBuf, SceSize size, SceInt32 loopsize);
SceSasResult sceSasSetNoiseInternal(SceUID sasCoreId, SceInt32 iVoiceNum, SceUInt32 uClk);
SceSasResult sceSasSetVolumeInternal(SceUID sasCoreId, SceInt32 iVoiceNum, SceInt32 l, SceInt32 r, SceInt32 wl, SceInt32 wr);
SceSasResult sceSasSetPitchInternal(SceUID sasCoreId, SceInt32 iVoiceNum, SceInt32 pitch);
SceSasResult sceSasSetADSRInternal(SceUID sasCoreId, SceInt32 iVoiceNum, SceUInt32 flag, SceUInt32 ar, SceUInt32 dr, SceUInt32 sr, SceUInt32 rr);
SceSasResult sceSasSetADSRmodeInternal(SceUID sasCoreId, SceInt32 iVoiceNum, SceUInt32 flag, SceUInt32 am, SceUInt32 dm, SceUInt32 sm, SceUInt32 rm);
SceSasResult sceSasSetSLInternal(SceUID sasCoreId, SceInt32 iVoiceNum, SceUInt32 sl);
SceSasResult sceSasSetSimpleADSRInternal(SceUID sasCoreId, SceInt32 iVoiceNum, SceUInt16 adsr1, SceUInt16 adsr2);

SceSasResult sceSasSetKeyOnInternal(SceUID sasCoreId, SceInt32 iVoiceNum);
SceSasResult sceSasSetKeyOffInternal(SceUID sasCoreId, SceInt32 iVoiceNum);

SceSasResult sceSasSetPauseInternal(SceUID sasCoreId, SceInt32 iVoiceNum, SceUInt32 pauseFlag);

SceSasResult sceSasGetPauseStateInternal(SceUID sasCoreId, SceInt32 iVoiceNum);
SceSasResult sceSasGetEndStateInternal(SceUID sasCoreId, SceInt32 iVoiceNum);
SceSasResult sceSasGetEnvelopeInternal(SceUID sasCoreId, SceInt32 iVoiceNum);

SceSasResult sceSasSetEffectInternal(SceUID sasCoreId, SceInt32 drySwitch, SceInt32 wetSwitch);
SceSasResult sceSasSetEffectTypeInternal(SceUID sasCoreId, SceInt32 type);
SceSasResult sceSasSetEffectVolumeInternal(SceUID sasCoreId, SceInt32 valL, SceInt32 valR);
SceSasResult sceSasSetEffectParamInternal(SceUID sasCoreId, SceUInt32 delayTime, SceUInt32 feedback);

#ifdef __cplusplus
}
#endif

#endif /* _VDSUITE_USER_SAS_H */

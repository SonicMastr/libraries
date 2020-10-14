#ifndef _DOLCESDK_PSP2_AUDIOCODEC_H_
#define _DOLCESDK_PSP2_AUDIOCODEC_H_

#ifdef	__cplusplus
extern "C" {
#endif

#define SCE_AUDIOCODEC_ATX        (0x00001000) //AT3PLUS?
#define SCE_AUDIOCODEC_AT3        (0x00001001)
#define SCE_AUDIOCODEC_MP3        (0x00001002)
#define SCE_AUDIOCODEC_AAC        (0x00001003)
#define SCE_AUDIOCODEC_AT9        (0x00001004)

typedef struct SceAudiocodecControl SceAudiocodecControl;

int sceAudiocodecInit(SceAudiocodecControl *ctrl, int codecType);

int sceAudiocodecQueryMemSize(SceAudiocodecControl *ctrl, int codecType);

int sceAudiocodecDecode(SceAudiocodecControl *ctrl, int codecType);

#ifdef	__cplusplus
}
#endif

#endif /* _DOLCESDK_PSP2_AUDIOCODEC_H_ */

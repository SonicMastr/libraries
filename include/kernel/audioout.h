#ifndef _PSP2_KERNEL_AUDIOOUT_H_
#define _PSP2_KERNEL_AUDIOOUT_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceAudioOutPortType {
	//! Used for main audio output, freq must be set to 48000 Hz
	SCE_AUDIO_OUT_PORT_TYPE_MAIN    = 0,
	//! Used for Background Music port
	SCE_AUDIO_OUT_PORT_TYPE_BGM     = 1,
	//! Used for voice chat port
	SCE_AUDIO_OUT_PORT_TYPE_VOICE   = 2
} SceAudioOutPortType;

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_AUDIOOUT_H_ */

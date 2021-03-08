/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_KERNEL_AUDIOOUT_H
#define _VDSUITE_KERNEL_AUDIOOUT_H

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

#endif /* _VDSUITE_KERNEL_AUDIOOUT_H */

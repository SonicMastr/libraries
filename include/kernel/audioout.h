/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_KERNEL_AUDIOOUT_H
#define _VDSUITE_KERNEL_AUDIOOUT_H

#include_next <audioout.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*SceAudioOutPortEventCallback)(SceUID processId);

int sceAudioOutSetPortOpenCallback(SceAudioOutPortEventCallback callbackFunc);

int sceAudioOutSetPortReleaseCallback(SceAudioOutPortEventCallback callbackFunc);

#ifdef __cplusplus
}
#endif

#endif /* _VDSUITE_KERNEL_AUDIOOUT_H */

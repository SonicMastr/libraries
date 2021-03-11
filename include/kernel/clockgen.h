/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_KERNEL_CLOCKGEN_H
#define _VDSUITE_KERNEL_CLOCKGEN_H

#include <stdint.h>
#include <stdbool.h>

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif  /* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

int sceClockgenGetRevision(void);

// idx < 3
int sceClockgenGetRegValue(uint32_t idx);

// 44100 or 48000, default 48000
int sceClockgenAudioClkSetSamplingFreq(uint32_t frequency);

int sceClockgenSetSpectrumSpreading(int mode);

// changes behaviour of sceClockgenInit(), default true
int sceClockgenSetProtocol(bool protocol);

int sceClockgenInit(void);

int sceClockgenAudioClkEnable(void);

int sceClockgenAudioClkDisable(void);

int sceClockgenCameraClkEnable(void);

int sceClockgenCameraClkDisable(void);

int sceClockgenWlanBtClkEnable(void);

int sceClockgenWlanBtClkDisable(void);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif  /* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

#endif /* _VDSUITE_KERNEL_CLOCKGEN_H */

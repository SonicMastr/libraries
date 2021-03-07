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

// idx < 3
int sceClockgenGetRegValue(uint32_t idx);

// 44100 or 48000, default 48000
int sceClockgenAudioClkSetSamplingFreq(uint32_t frequency);

int sceClockgenSetSpectrumSpreading(int mode);

// changes behaviour of sceClockgenInit(), default true
int sceClockgenSetProtocol(bool protocol);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif  /* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

#endif /* _VDSUITE_KERNEL_CLOCKGEN_H */

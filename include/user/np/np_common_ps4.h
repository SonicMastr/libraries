/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_USER_NP_NP_COMMON_PS4_H
#define _VDSUITE_USER_NP_NP_COMMON_PS4_H

#include <scetypes.h>

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif  /* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

SceInt32 sceNpGetSystemClockUsec(SceUInt64 *pClock);

SceInt32 sceNpGetSystemClockLowUsec(SceUInt32 *pClock);

SceInt32 sceNpDbgDumpText(const char *pText, SceSize size);

SceInt32 sceNpDbgDumpBinary(const void *pBinary, SceSize size);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif  /* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

#endif /* _VDSUITE_USER_NP_NP_COMMON_PS4_H */

/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_USER_NP_NP_COMMON_H
#define _VDSUITE_USER_NP_NP_COMMON_H

#include_next <np/np_common.h>

#define SCE_NP_ENVIRONMENT_MAX_LENGTH	15

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif  /* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

int
sceNpGetEnvironment(
	char *env
	);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif  /* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

#endif /* _VDSUITE_USER_NP_NP_COMMON_H */

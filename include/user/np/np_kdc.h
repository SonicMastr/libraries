/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_USER_NP_NP_KDC_H
#define _VDSUITE_USER_NP_NP_KDC_H

#include <scetypes.h>

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif  /* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

int
sceNpKdcInit(
	SceSize poolSize,
	void *poolBase
	);

int
sceNpKdcTerm(
	void
	);

int
sceNpKdcAbortReq(
	void
	);

int
sceNpKdcActivateConsole(
	int *maxConsole,
	int *currentConsole,
	const char *epassword
	);

int
sceNpKdcDeactivateConsole(
	int *maxConsole,
	int *currentConsole,
	const char *epassword,
	SceBool forceReq
	);

int
sceNpKdcGetProductRif(
	const char *productId,
	const char *epassword,
	void *rifBuf,
	SceSize rifBufSize,
	SceSize *rifSize,
	int *maxConsole,
	int *currentConsole
	);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif  /* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

#endif /* _VDSUITE_USER_NP_NP_KDC_H */

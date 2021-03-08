/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_USER_BGAPPUTIL_H
#define _VDSUITE_USER_BGAPPUTIL_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Errors
 */
#define SCE_BGAPPUTIL_ERROR_INVALID_ARG ((int)0x80106501)

/**
 * Start BG application (eboot2.bin)
 *
 * @param[in] mode - must be 0
 *
 * @return 0 on success, <0 otherwise.
 */
int sceBgAppUtilStartBgApp(int mode);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _VDSUITE_USER_BGAPPUTIL_H */

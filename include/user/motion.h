/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_USER_MOTION_H
#define _VDSUITE_USER_MOTION_H

#include_next <motion.h>

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif	/* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

/* Extended functions */

/*
 * Initialize libMotion for extended use
 * @retval SCE_OK success
 *			<SCE_OK Error
 */

int sceMotionInitLibraryExt(void);

/*
 * Terminate libMotion for extended use
 * @retval SCE_OK success
 *			<SCE_OK Error
 */

int sceMotionTermLibraryExt(void);

/*
 * Calculate and update the new motion states
 * @retval SCE_OK success
 *			<SCE_OK Error
 */

int sceMotionGetStateExt(int port, SceMotionState *motionState);

/*
 * Retrieve the status of tilt correction filter settings
 * @retval SCE_OK success
 *			<SCE_OK Error
 */

int sceMotionGetTiltCorrectionExt(int port, SceBool *getValue);

/*
 * Set the tilt correction filter settings
 * @retval SCE_OK success
 *			<SCE_OK Error
 */

int sceMotionSetTiltCorrectionExt(int port, SceBool setValue);

/*
 * Retrieve the status of deadband filter mode
 * @retval SCE_OK success
 *			<SCE_OK Error
 */

int sceMotionGetDeadbandExt(int port, SceBool *getValue);

/*
 * Set the deadbanding filter mode
 * @retval SCE_OK success
 *			<SCE_OK Error
 */

int sceMotionSetDeadbandExt(int port, SceBool setValue);

/*
 * Reset the device posture and filter settings.
 * @retval  SCE_OK success
 *			<SCE_OK Error
 */

int sceMotionResetExt(void);

/*
 * Begin sampling data.
 * @retval SCE_OK success
 *			<SCE_OK Error
 */

int sceMotionStartSamplingExt(int port);

/*
 * Stop sampling data.
 * @retval SCE_OK success
 *			<SCE_OK Error
 */

int sceMotionStopSamplingExt(int port);

/* Internal functions */

/*
 * Calculate and update the new motion states
 * @param *motionState : State Pointer to save data into
 * @retval SCE_OK success
 *			<SCE_OK Error
 */

int sceMotionGetStateInternal(SceMotionState *motionState);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif  /* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

#endif /* _VDSUITE_USER_MOTION_H */



/*
	Vita Development Suite Libraries
*/

#ifndef _PSP2_DISPLAY_H_
#define _PSP2_DISPLAY_H_

#include_next <display.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Primary display index
 */
int sceDisplayGetPrimaryHead(void);

/**
 * Get current number of fps for the current screen mode.
 *
 * @param[out] pFps - Pointer to a float variable to store current number of fps.
 *
 * @return 0 on success, < 0 on error.
 * @note - This function returns a theoretical value, this might not be the exact frame rate.
*/
int sceDisplayGetRefreshRate(float *pFps);

/**
 * Get maximum framebuffer resolution
 *
 * @param[out] width - Maximum width
 * @param[out] height - Maximum height
 *
 * @return 0 on success, < 0 on error.
*/
int sceDisplayGetMaximumFrameBufResolution(int *width, int *height);

/**
 * Number of vertical blank pulses up to now
 */
int sceDisplayGetVcount(void);

/**
 * Number of vertical blank pulses up to now for a display
 *
 * @param[in] display - Display index
 */
int sceDisplayGetVcountInternal(int display);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_DISPLAY_H_ */


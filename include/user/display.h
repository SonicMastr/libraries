/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_USER_DISPLAY_H
#define _VDSUITE_USER_DISPLAY_H

#include_next <display.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Primary display index
 */
int sceDisplayGetPrimaryHead(void);

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
 * Number of vertical blank pulses up to now for a display
 *
 * @param[in] display - Display index
 */
int sceDisplayGetVcountInternal(int display);

#ifdef __cplusplus
}
#endif

#endif /* _VDSUITE_USER_DISPLAY_H */


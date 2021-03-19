/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_COMMON_DISPLAY_H
#define _VDSUITE_COMMON_DISPLAY_H

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

/**
 * Set/Update framebuffer parameters for display
 *
 * @param[in] head - Use 0 for OLED/LCD and 1 for HDMI
 * @param[in] index - Can be 0 or 1
 * @param[in] pParam - Pointer to a ::SceDisplayFrameBuf structure.
 * @param[in] sync - One of ::DisplaySetBufSync
 *
 * @return 0 on success, < 0 on error.
 * @note - If NULL is provided as pParam pointer, output is blacked out.
*/
int sceDisplaySetFrameBufInternal(int head, int index, const SceDisplayFrameBuf *pParam, int sync);

#ifdef __cplusplus
}
#endif

#endif	/* _VDSUITE_COMMON_DISPLAY_H */


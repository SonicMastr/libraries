/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_KERNEL_DISPLAY_H
#define _VDSUITE_KERNEL_DISPLAY_H

#include_next <display.h>

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Extended framebuffer information
*/
typedef struct SceDisplayFrameBufInfo {
	SceSize size;                //!< sizeof(SceDisplayFrameBufInfo)
	SceUID pid;                  //!< PID of the process owning this framebuffer
	unsigned int vblankcount;    //!< Amount of VBlanks this framebuffer has been displayed
	uintptr_t paddr;             //!< Physical address
	SceDisplayFrameBuf framebuf; //!< SceDisplayFrameBuf information
	unsigned int resolution;     //!< Resolution
} SceDisplayFrameBufInfo;

/**
 * Get the configured framebuffer information of a head and its framebuffer index for a PID
 *
 * @param[in] pid - PID of the process to get the framebuffer information from.
 *                  It can either be a vallid PID, -1 to use the current configured
 *                  framebuffer for the head and index, or 0 to use the PID of the caller.
 * @param[in] head - Use 0 for OLED/LCD and 1 for HDMI
 * @param[in] index - Can be 0 or 1
 * @param[out] info - Pointer to a ::SceDisplayFrameBufInfo structure
 * which will receive the framebuffer information.
 *
 * @return 0 on success, < 0 on error.
*/
int sceDisplayGetProcFrameBufInternal(SceUID pid, int head, int index, SceDisplayFrameBufInfo *info);

/**
 * Wait for vertical blank start for display
 *
 * @param[in] display - Display index
 */
int sceDisplayWaitVblankStartInternal(int display);

/**
 * Wait for vertical blank start with callback for display
 *
 * @param[in] display - Display index
 */
int sceDisplayWaitVblankStartCBInternal(int display);

/**
 * Wait for vertical blank start after specified number of vertical periods for display
 *
 * @param[in] display - Display index
 * @param[in] vcount - Number of vertical periods before waiting for vertical blank start
 */
int sceDisplayWaitVblankStartMultiInternal(int display, unsigned int vcount);

/**
 * Wait for vertical blank start with callback after specified number of vertical periods for display
 *
 * @param[in] display - Display index
 * @param[in] vcount - Number of vertical periods before waiting for vertical blank start
 */
int sceDisplayWaitVblankStartMultiCBInternal(int display, unsigned int vcount);

/**
 * Register callback to be used at each vertical blank start for a display
 *
 * @param[in] display - Display index
 * @param[in] uid - Callback UID
 */
int sceDisplayRegisterVblankStartCallbackInternal(int display, SceUID uid);

/**
 * Unregister callback used at each vertical blank start for a display
 *
 * @param[in] display - Display index
 * @param[in] uid - Callback UID
 */
int sceDisplayUnregisterVblankStartCallbackInternal(int display, SceUID uid);

/**
 * Register callback to be used when the framebuffer changes
 *
 * @param[in] uid - Callback UID
 */
int sceDisplayRegisterFrameBufCallback(SceUID uid);

/**
 * Register callback to be used when the framebuffer changes for a display
 *
 * @param[in] display - Display index
 * @param[in] uid - Callback UID
 */
int sceDisplayRegisterFrameBufCallbackInternal(int display, SceUID uid);

/**
 * Enable/disable color inversion for a display.
 *
 * @param[in] display - Display index
 * @param[in] enable - Enable/disable color inversion
 */
int sceDisplaySetInvertColors(int display, int enable);

/**
 * Set display plane owner
 *
 * @param[in] head - Use 0 for OLED/LCD and 1 for HDMI
 * @param[in] index - Can be 0 or 1
 * @param[in] pid - PID of the new owner
 *
 * @return 0 on success, < 0 on error.
*/
int sceDisplaySetOwner(int head, int index, SceUID pid);

/**
 * Set display scaling configuration
 *
 * @param[in] scale - Scaling factor between 0.80000001 and 1.20000005
 * @param[in] head - Use 0 for OLED/LCD and 1 for HDMI
 * @param[in] index - Can be 0 or 1
 * @param[in] flags - Returns error if ((flags & 1) && (flags & 0xC0))
 *
 * @return 0 on success, < 0 on error.
*/
int sceDisplaySetScaleConf(float scale, int head, int index, int flags);

#ifdef __cplusplus
}
#endif

#endif /* _VDSUITE_KERNEL_DISPLAY_H */


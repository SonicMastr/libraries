/*
	Vita Development Suite Libraries
*/

#ifndef _PSP2_KERNEL_DISPLAY_H_
#define _PSP2_KERNEL_DISPLAY_H_

#include <stdint.h>
#include <scetypes.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceDisplayErrorCode {
	SCE_DISPLAY_ERROR_OK                    = 0,
	SCE_DISPLAY_ERROR_INVALID_HEAD          = (int)0x80290000,
	SCE_DISPLAY_ERROR_INVALID_VALUE         = (int)0x80290001,
	SCE_DISPLAY_ERROR_INVALID_ADDR          = (int)0x80290002,
	SCE_DISPLAY_ERROR_INVALID_PIXELFORMAT   = (int)0x80290003,
	SCE_DISPLAY_ERROR_INVALID_PITCH         = (int)0x80290004,
	SCE_DISPLAY_ERROR_INVALID_RESOLUTION    = (int)0x80290005,
	SCE_DISPLAY_ERROR_INVALID_UPDATETIMING  = (int)0x80290006,
	SCE_DISPLAY_ERROR_NO_FRAME_BUFFER       = (int)0x80290007,
	SCE_DISPLAY_ERROR_NO_PIXEL_DATA         = (int)0x80290008
} SceDisplayErrorCode;

typedef enum SceDisplayPixelFormat {
	SCE_DISPLAY_PIXELFORMAT_A8B8G8R8 = 0x00000000U
} SceDisplayPixelFormat;

#define SCE_DISPLAY_UPDATETIMING_NEXTHSYNC	0
#define SCE_DISPLAY_UPDATETIMING_NEXTVSYNC	1

// This enum is for backward compatibility with Vitasdk
typedef enum SceDisplaySetBufSync {
	SCE_DISPLAY_SETBUF_IMMEDIATE = SCE_DISPLAY_UPDATETIMING_NEXTHSYNC,
	SCE_DISPLAY_SETBUF_NEXTFRAME = SCE_DISPLAY_UPDATETIMING_NEXTVSYNC,
} SceDisplaySetBufSync;

/**
 * Structure used with ::sceDisplaySetFrameBuf to set/update framebuffer.
 * Original screen resolution is 960x544, but the following resolutions
 * can also be supplied as width and height :
 * 480x272, 640x368, 720x408
 *
 * @note - This structure is returned by ::sceDisplayGetFrameBuf
*/
typedef struct SceDisplayFrameBuf {
	SceSize size;               //!< sizeof(SceDisplayFrameBuf)
	void *base;                 //!< Pointer to framebuffer
	unsigned int pitch;         //!< pitch pixels
	unsigned int pixelformat;   //!< pixel format (one of ::SceDisplayPixelFormat)
	unsigned int width;         //!< framebuffer width
	unsigned int height;        //!< framebuffer height
} SceDisplayFrameBuf;

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
 * Set/Update framebuffer parameters
 *
 * @param[in] pParam - Pointer to a ::SceDisplayFrameBuf structure.
 * @param[in] sync - One of ::DisplaySetBufSync
 *
 * @return 0 on success, < 0 on error.
 * @note - If NULL is provided as pParam pointer, output is blacked out.
*/
int sceDisplaySetFrameBuf(const SceDisplayFrameBuf *pParam, int sync);

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

/**
 * Get current framebuffer parameters
 *
 * @param[out] pParam - Pointer to a ::SceDisplayFrameBuf structure
 * which will receive framebuffer parameters.
 *
 * @param[in] sync - One of ::DisplaySetBufSync
 *
 * @return 0 on success, < 0 on error.
*/
int sceDisplayGetFrameBuf(SceDisplayFrameBuf *pParam, int sync);

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
 * Get maximum framebuffer resolution
 *
 * @param[out] width - Maximum width
 * @param[out] height - Maximum height
 *
 * @return 0 on success, < 0 on error.
*/
int sceDisplayGetMaximumFrameBufResolution(int *width, int *height);

/**
 * Primary display index
 */
int sceDisplayGetPrimaryHead(void);

/**
 * Number of vertical blank pulses up to now for a display
 *
 * @param[in] display - Display index
 */
int sceDisplayGetVcountInternal(int display);

/**
 * Wait for vertical blank start
 */
int sceDisplayWaitVblankStart(void);

/**
 * Wait for vertical blank start for display
 *
 * @param[in] display - Display index
 */
int sceDisplayWaitVblankStartInternal(int display);

/**
 * Wait for vertical blank start with callback
 */
int sceDisplayWaitVblankStartCB(void);

/**
 * Wait for vertical blank start with callback for display
 *
 * @param[in] display - Display index
 */
int sceDisplayWaitVblankStartCBInternal(int display);

/**
 * Wait for vertical blank start after specified number of vertical periods
 *
 * @param[in] vcount - Number of vertical periods before waiting for vertical blank start
 */
int sceDisplayWaitVblankStartMulti(unsigned int vcount);

/**
 * Wait for vertical blank start after specified number of vertical periods for display
 *
 * @param[in] display - Display index
 * @param[in] vcount - Number of vertical periods before waiting for vertical blank start
 */
int sceDisplayWaitVblankStartMultiInternal(int display, unsigned int vcount);

/**
 * Wait for vertical blank start with callback after specified number of vertical periods
 *
 * @param[in] vcount - Number of vertical periods before waiting for vertical blank start
 */
int sceDisplayWaitVblankStartMultiCB(unsigned int vcount);

/**
 * Wait for vertical blank start with callback after specified number of vertical periods for display
 *
 * @param[in] display - Display index
 * @param[in] vcount - Number of vertical periods before waiting for vertical blank start
 */
int sceDisplayWaitVblankStartMultiCBInternal(int display, unsigned int vcount);

/**
 * Wait for vertical blank start since last update of framebuffer
 */
int sceDisplayWaitSetFrameBuf(void);

/**
 * Wait for vertical blank start with callback since last update of framebuffer
 */
int sceDisplayWaitSetFrameBufCB(void);

/**
 * Wait for vertical blank start after specified number of vertical periods
 * since last update of framebuffer.
 *
 * @param[in] vcount - Number of vertical periods before waiting for vertical blank start
 */
int sceDisplayWaitSetFrameBufMulti(unsigned int vcount);

/**
 * Wait for vertical blank start with callback after specified number of vertical periods
 * since last update of framebuffer.
 *
 * @param[in] vcount - Number of vertical periods before waiting for vertical blank start
 */
int sceDisplayWaitSetFrameBufMultiCB(unsigned int vcount);

/**
 * Register callback to be used at each vertical blank start
 *
 * @param[in] uid - Callback UID
 */
int sceDisplayRegisterVblankStartCallback(SceUID uid);

/**
 * Register callback to be used at each vertical blank start for a display
 *
 * @param[in] display - Display index
 * @param[in] uid - Callback UID
 */
int sceDisplayRegisterVblankStartCallbackInternal(int display, SceUID uid);

/**
 * Unregister callback used at each vertical blank start
 *
 * @param[in] uid - Callback UID
 */
int sceDisplayUnregisterVblankStartCallback(SceUID uid);

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

#endif /* _PSP2_KERNEL_DISPLAY_H_ */


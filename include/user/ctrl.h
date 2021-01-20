#ifndef _PSP2_CTRL_H_
#define _PSP2_CTRL_H_

#include_next <ctrl.h>

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SCE_CTRL_PSBUTTON     SCE_CTRL_INTERCEPTED  //!< Playstation (Home) button.
#define SCE_CTRL_HEADPHONE    0x00080000            //!< Headphone plugged in.
#define SCE_CTRL_VOLUP        0x00100000            //!< Volume up button.
#define SCE_CTRL_VOLDOWN      0x00200000            //!< Volume down button.
#define SCE_CTRL_POWER        0x40000000             //!< Power button.

/** Enumeration for the controller types. */
typedef enum SceCtrlExternalInputMode {
	SCE_CTRL_TYPE_UNPAIRED  = 0, //!< Unpaired controller
	SCE_CTRL_TYPE_PHY       = 1, //!< Physical controller for VITA
	SCE_CTRL_TYPE_VIRT      = 2, //!< Virtual controller for PSTV
	SCE_CTRL_TYPE_DS3       = 4, //!< DualShock 3
	SCE_CTRL_TYPE_DS4       = 8  //!< DualShock 4
} SceCtrlExternalInputMode;

/** Structure to pass as argument to ::sceCtrlSetActuator */
typedef struct SceCtrlActuator {
	unsigned char small; //!< Vibration strength of the small motor
	unsigned char large; //!< Vibration strength of the large motor
	uint8_t unk[6];      //!< Unknown
} SceCtrlActuator;

/** Structure to pass as argument to ::sceCtrlGetControllerPortInfo */
typedef struct SceCtrlPortInfo {
	uint8_t port[5];  //!< Controller type of each port (See ::SceCtrlExternalInputMode)
	uint8_t unk[11];  //!< Unknown
} SceCtrlPortInfo;

/**
 * Set the controller extend mode.
 *
 * @param[in] mode - One of ::SceCtrlPadInputMode.
 *
 * @return The previous mode, <0 on error.
 */
int sceCtrlSetSamplingModeExt(SceUInt32 mode);

/**
 * Get the controller state information (polling, positive logic).
 *
 * This function will bind L/R trigger value to L1/R1 instead of LTRIGGER/RTRIGGER
 *
 * @param[in] port - use 0.
 * @param[out] *pad_data - see ::SceCtrlData.
 * @param[in] count - Buffers count.
 *
 * @return Buffers count, between 1 and 'count'. <0 on error.
 */
int sceCtrlPeekBufferPositiveExt2(int port, SceCtrlData *pad_data, int count);

/**
 * Get the controller extended state information (blocking, positive logic).
 *
 * This function will bind L/R trigger value to L1/R1 instead of LTRIGGER/RTRIGGER
 *
 * @param[in] port - use 0.
 * @param[out] *pad_data - see ::SceCtrlData.
 * @param[in] count - Buffers count.
 *
 * @return Buffers count, between 1 and 'count'. <0 on error.
 */
int sceCtrlReadBufferPositiveExt2(int port, SceCtrlData *pad_data, int count);

/**
 * Control the actuator (vibrate) on paired controllers.
 *
 * @param[in] port - use 1 for the first paired controller, etc.
 * @param[in] state - see ::SceCtrlActuator
 *
 * @return 0, <0 on error.
 */
int sceCtrlSetActuator(int port, const SceCtrlActuator* pState);

/**
 * Control the light bar on paired controllers.
 *
 * @param[in] port - use 1 for the first paired controller, etc.
 * @param[in] r - red intensity
 * @param[in] g - green intensity
 * @param[in] b - blue intensity
 *
 * @return 0, <0 on error.
 */
int sceCtrlSetLightBar(int port, SceUInt8 r, SceUInt8 g, SceUInt8 b);

/**
 * Get controller port information.
 *
 * @param[out] info - see ::SceCtrlPortInfo
 * @return 0, <0 on error
 */
int sceCtrlGetControllerPortInfo(SceCtrlPortInfo *info);

/**
 * Get controller battery information.
 *
 * @param[in] port - use 1 for the first paired controller, etc.
 * @param[out] batt - battery level, between 0-5, 0xEE charging, 0xEF charged
 *
 * @return 0, <0 on error.
 */
int sceCtrlGetBatteryInfo(int port, SceUInt8 *batt);

/**
 * Sets intercept
 *
 * If true, allows the current thread to intercept controls. The use case
 * might be, for example, a game plugin that wishes to capture input without
 * having the input sent to the game thread.
 * @param[in]  intercept  Boolean value
 *
 * @return 0, < 0 on error
 */
int sceCtrlSetButtonIntercept(int intercept);

/**
 * Gets intercept
 *
 * @param[out]  intercept  Boolean value
 *
 * @return 0, < 0 on error
 */
int sceCtrlGetButtonIntercept(int *intercept);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2CTRL_H_ */

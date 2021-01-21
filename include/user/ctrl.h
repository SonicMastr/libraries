#ifndef _PSP2_CTRL_H_
#define _PSP2_CTRL_H_

#include_next <ctrl.h>

#ifdef __cplusplus
extern "C" {
#endif

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
 * Get controller battery information.
 *
 * @param[in] port - use 1 for the first paired controller, etc.
 * @param[out] batt - battery level, between 0-5, 0xEE charging, 0xEF charged
 *
 * @return 0, <0 on error.
 */
int sceCtrlGetBatteryInfo(int port, SceUInt8 *batt);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2CTRL_H_ */

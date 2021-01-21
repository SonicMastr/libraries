#ifndef _PSP2_KERN_CTRL_H_
#define _PSP2_KERN_CTRL_H_

#include_next <ctrl.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Structure to pass as argument to ::sceCtrlRegisterVirtualControllerDriver */
typedef struct SceCtrlVirtualControllerDriver {
	int (*readButtons)(int port, SceCtrlData *pad_data, int count);
	int (*setActuator)(int port, const SceCtrlActuator* pState);
	int (*getBatteryInfo)(int port, SceUInt8 *batt);
	int (*disconnect)(int port);
	int (*setTurnOffInterval)(int port);
	int (*getActiveControllerPort)(void);
	int (*changePortAssign)(int port1, int port2);
	int (*unk0)(void);
	int (*getControllerPortInfo)(SceCtrlPortInfo *info);
	int (*setLightBar)(int port, SceUInt8 r, SceUInt8 g, SceUInt8 b);
	int (*resetLightBar)(int port);
	int (*unk1)(int port);
	int (*singleControllerMode)(int port);
} SceCtrlVirtualControllerDriver;

/**
 * Emulate buttons for the digital pad.
 * @param port Use 0
 * @param slot The slot used to set the custom values. Between 0 - 3. If multiple slots are used,
 *             their settings are combined.
 * @param userButtons Emulated user buttons of ::SceCtrlButtons. You cannot emulate kernel
 *                    buttons and the emulated buttons will only be applied for applications
 *                    running in user mode.
 * @param kernelButtons Emulated buttons of ::SceCtrlButtons (you can emulate both user and
 *                      kernel buttons). The emulated buttons will only be applied for applications
 *                      running in kernel mode.
 * @param uiMake Specifies the duration of the emulation. Measured in sampling counts.
 *
 * @return 0 on success.
 */
int sceCtrlSetButtonEmulation(unsigned int port, unsigned char slot,
			       unsigned int userButtons, unsigned int kernelButtons,
			       unsigned int uiMake);

/**
 * Emulate values for the analog pad's X- and Y-axis.
 *
 * @param port Use 0
 * @param slot The slot used to set the custom values. Between 0 - 3. If multiple slots are used,
 *             their settings are combined.
 * @param user_lX New emulated value for the left joystick's X-axis (userspace). Between 0 - 0xFF.
 * @param user_lY New emulate value for the left joystick's Y-axis (userspace). Between 0 - 0xFF.
 * @param user_rX New emulated value for the right joystick's X-axis (userspace). Between 0 - 0xFF.
 * @param user_rY New emulate value for the right joystick's Y-axis (userspace). Between 0 - 0xFF.
 * @param kernel_lX New emulated value for the left joystick's X-axis (kernelspace). Between 0 - 0xFF.
 * @param kernel_lY New emulate value for the left joystick's Y-axis (kernelspace). Between 0 - 0xFF.
 * @param kernel_rX New emulated value for the right joystick's X-axis (kernelspace). Between 0 - 0xFF.
 * @param kernel_rY New emulate value for the right joystick's Y-axis (kernelspace). Between 0 - 0xFF.
 * @param uiMake Specifies the duration of the emulation. Measured in sampling counts.
 *
 * @return 0 on success.
 */
int sceCtrlSetAnalogEmulation(unsigned int port, unsigned char slot,
			      unsigned char user_lX, unsigned char user_lY,
			      unsigned char user_rX, unsigned char user_rY,
			      unsigned char kernel_lX, unsigned char kernel_lY,
			      unsigned char kernel_rX, unsigned char kernel_rY,
			      unsigned int uiMake);

/**
 * Register virtual controller driver.
 *
 * This function always overwrites global settings and not exist unregister method.
 *
 * @param[in] driver - See ::SceCtrlVirtualControllerDriver
 *
 * @return 0 on success. <0 on error
 */
int sceCtrlRegisterVirtualControllerDriver(SceCtrlVirtualControllerDriver *driver);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERN_CTRL_H_ */

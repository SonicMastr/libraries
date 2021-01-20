#ifndef _PSP2_KERN_CTRL_H_
#define _PSP2_KERN_CTRL_H_

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
	unsigned char small;  //!< Vibration strength of the small motor
	unsigned char large;  //!< Vibration strength of the large motor
	uint8_t       unk[6]; //!< Unknown
} SceCtrlActuator;

/** Structure to pass as argument to ::sceCtrlGetControllerPortInfo */
typedef struct SceCtrlPortInfo {
	uint8_t port[5];  //!< Controller type of each ports
	uint8_t unk[11];  //!< Unknown
} SceCtrlPortInfo;

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
 * Get controller port information.
 *
 * @param[out] info - see ::SceCtrlPortInfo
 * @return 0, <0 on error
 */
int sceCtrlGetControllerPortInfo(SceCtrlPortInfo *info);

/**
 * Sets intercept
 *
 * If true, allows the current thread to intercept controls. The use case
 * might be, for example, a game plugin that wishes to capture input without
 * having the input sent to the game thread.
 * @param[in]  intercept  Boolean value
 *
 * @return     0, < 0 on error
 */
int sceCtrlSetButtonIntercept(int intercept);

/**
 * Gets intercept
 *
 * @param[out]  intercept  Boolean value
 *
 * @return     0, < 0 on error
 */
int sceCtrlGetButtonIntercept(int *intercept);

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

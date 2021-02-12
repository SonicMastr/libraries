/*
	Vita Development Suite Libraries
*/

/*                 -*- mode: c; tab-width: 4; indent-tabs-mode: t; -*- */
/*
 *
 *
 *
 *
 *
 *
 *                     Controller Service
 *
 *                           ctrl.h
 */


#ifndef _VDSUITE_COMMON_CTRL_H
#define _VDSUITE_COMMON_CTRL_H

#include_next <ctrl.h>

#include <stdint.h>


#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif	/* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

#define SCE_CTRL_PSBUTTON     SCE_CTRL_INTERCEPTED  //!< Playstation (Home) button.
#define SCE_CTRL_HEADPHONE    0x00080000            //!< Headphone plugged in.
#define SCE_CTRL_VOLUP        0x00100000            //!< Volume up button.
#define SCE_CTRL_VOLDOWN      0x00200000            //!< Volume down button.
#define SCE_CTRL_POWER        0x40000000            //!< Power button.

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

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif	/* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

#endif	/* _VDSUITE_COMMON_CTRL_H */


/* Local variables: */
/* tab-width: 4 */
/* End: */
/* vi:set tabstop=4: */

/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_KERNEL_POWER_H
#define _VDSUITE_KERNEL_POWER_H

#include_next <power.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Prototypes */

/**
 * Returns Sys clock frequency
 *
 * @return Sys clock frequency in Mhz
 */
int scePowerGetSysClockFrequency(void);

/**
 * Requests PS Vita to do a soft reset
 *
 * @return always 0
 */
int scePowerRequestSoftReset(void);

/**
 * Set the screen brightness.
 * @see ::sceAVConfigSetDisplayBrightness for userland counterpart.
 *
 * @param brightness Brightness that the screen will be set to (range 21-65536, 0 turns off the screen).
 *
 * @return ?
 */
int scePowerSetDisplayBrightness(int brightness);

/**
 * Sets the time before idle callback is notified.
 *
 * @param callback_slot - Callback slot from 0 to 7.
 * @param time - Time in microseconds.
 *
 * @return 0 on success, < 0 on error
 */
int scePowerSetIdleTimer(int callback_slot, SceUInt64 time);

/**
 * Sets the PS button hold time for showing the quick menu.
 *
 * @param time - Time in microseconds.
 *
 * @return 0 always
 */
int scePowerSetPsButtonPushTime(int time);

#ifdef __cplusplus
}
#endif

#endif /* _VDSUITE_KERNEL_POWER_H */

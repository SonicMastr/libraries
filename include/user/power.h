/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_USER_POWER_H
#define _VDSUITE_USER_POWER_H

#include_next <power.h>


#ifdef __cplusplus
extern "C" {
#endif

/**
 * Returns GPU clock frequency
 *
 * @return GPU clock frequency in Mhz
 */
int scePowerGetGpuClockFrequency(void);

/**
 * Sets GPU clock frequency
 *
 * @param freq - Frequency to set in Mhz
 *
 * @return 0 on success, < 0 on error
 */
int scePowerSetGpuClockFrequency(int freq);

/**
 * Sets wireless features usage
 *
 * @param enabled - SCE_TRUE to enable, SCE_FALSE to disable
 *
 * @return 0 on success, < 0 on error
 */
int scePowerSetUsingWireless(SceBool enabled);

/**
 * Gets wireless features usage
 *
 * @return SCE_TRUE if enabled, SCE_FALSE otherwise
 */
int scePowerGetUsingWireless(void);

#ifdef __cplusplus
}
#endif

#endif /* _VDSUITE_USER_POWER_H */

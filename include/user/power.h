/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_USER_POWER_H
#define _VDSUITE_USER_POWER_H

#include_next <power.h>


#ifdef __cplusplus
extern "C" {
#endif

typedef enum ScePowerCallbackType {
	/** indicates the power button was pushed, putting the unit into suspend mode */
	SCE_POWER_CB_POWER_SWITCH     = 0x80000000,
	/** indicates the unit has finish resuming from suspend mode */
	SCE_POWER_CB_RESUME_COMPLETE  = 0x00040000,
	/** indicates the unit is resuming from suspend mode */
	SCE_POWER_CB_RESUMING         = 0x00020000,
	/** indicates the unit is suspending, seems to occur due to inactivity */
	SCE_POWER_CB_SUSPENDING       = 0x00010000,
} ScePowerCallbackType;

/**
 * Returns battery life percentage
 *
 * @return Battery life percentage
 */
int scePowerGetBatteryLifePercent(void);

/**
 * Check if a suspend is required
 *
 * @return SCE_TRUE if suspend is required, SCE_FALSE otherwise
 */
SceBool scePowerIsSuspendRequired(void);

/**
 * Returns battery life time
 *
 * @return Battery life time in seconds
 */
int scePowerGetBatteryLifeTime(void);

/**
 * Returns battery remaining capacity
 *
 * @return battery remaining capacity in mAh (milliampere hour)
 */
int scePowerGetBatteryRemainCapacity(void);

/**
 * Returns battery full capacity
 *
 * @return battery full capacity in mAh (milliampere hour)
 */
int scePowerGetBatteryFullCapacity(void);

/**
 * Returns battery temperature
 *
 * @return temperature in degrees celcius * 100
 */
int scePowerGetBatteryTemp(void);

/**
 * Returns battery voltage
 *
 * @return battery voltage in mV (millivolts)
 */
int scePowerGetBatteryVolt(void);

/**
 * Returns battery state of health
 *
 * @return battery state of health percent
 */
int scePowerGetBatterySOH(void);

/**
 * Returns battery cycle count
 *
 * @return battery cycle count
 */
int scePowerGetBatteryCycleCount(void);

/**
 * Returns CPU clock frequency
 *
 * @return CPU clock frequency in Mhz
 */
int scePowerGetArmClockFrequency(void);

/**
 * Returns BUS clock frequency
 *
 * @return BUS clock frequency in Mhz
 */
int scePowerGetBusClockFrequency(void);

/**
 * Returns GPU clock frequency
 *
 * @return GPU clock frequency in Mhz
 */
int scePowerGetGpuClockFrequency(void);

/**
 * Returns GPU crossbar clock frequency
 *
 * @return GPU crossbar clock frequency in Mhz
 */
int scePowerGetGpuXbarClockFrequency(void);

/**
 * Requests PS Vita to do a cold reset
 *
 * @return always 0
 */
int scePowerRequestColdReset(void);

/**
 * Requests PS Vita to go into standby
 *
 * @return always 0
 */
int scePowerRequestStandby(void);

/**
 * Requests PS Vita to suspend
 *
 * @return always 0
 */
int scePowerRequestSuspend(void);

/**
 * Request display on
 *
 * @return always 0
 */
int scePowerRequestDisplayOn(void);

/**
 * Request display off
 *
 * @return always 0
 */
int scePowerRequestDisplayOff(void);

/**
 * Sets CPU clock frequency
 *
 * @param freq - Frequency to set in Mhz
 *
 * @return 0 on success, < 0 on error
 */
int scePowerSetArmClockFrequency(int freq);

/**
 * Sets BUS clock frequency
 *
 * @param freq - Frequency to set in Mhz
 *
 * @return 0 on success, < 0 on error
 */
int scePowerSetBusClockFrequency(int freq);

/**
 * Sets GPU clock frequency
 *
 * @param freq - Frequency to set in Mhz
 *
 * @return 0 on success, < 0 on error
 */
int scePowerSetGpuClockFrequency(int freq);

/**
 * Sets GPU crossbar clock frequency
 *
 * @param freq - Frequency to set in Mhz
 *
 * @return 0 on success, < 0 on error
 */
int scePowerSetGpuXbarClockFrequency(int freq);

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

/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_KERNEL_SYSCON_H
#define _VDSUITE_KERNEL_SYSCON_H

#include <scetypes.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SCE_SYSCON_PACKET_TX_CMD_LO	0
#define SCE_SYSCON_PACKET_TX_CMD_HI	1
#define SCE_SYSCON_PACKET_TX_LENGTH	2
#define SCE_SYSCON_PACKET_TX_DATA(i)	(3 + (i))

#define SCE_SYSCON_PACKET_RX_STATUS_LO	0
#define SCE_SYSCON_PACKET_RX_STATUS_HI	1
#define SCE_SYSCON_PACKET_RX_LENGTH	2
#define SCE_SYSCON_PACKET_RX_RESULT	3
#define SCE_SYSCON_PACKET_RX_DATA(i)	(4 + (i))

typedef enum SceSysconCmd {
	SCE_SYSCON_CMD_RESET_DEVICE = 0x0C
} SceSysconCmd;

typedef enum SceSysconResetType {
	SCE_SYSCON_RESET_TYPE_POWEROFF		= 0x00,
	SCE_SYSCON_RESET_TYPE_SUSPEND		= 0x01,
	SCE_SYSCON_RESET_TYPE_COLD_RESET	= 0x02,
	SCE_SYSCON_RESET_TYPE_SOFT_RESET	= 0x11
} SceSysconResetType;

typedef struct SceSysconPacket {
	struct SceSysconPacket *next;
	unsigned int status;
	SceUID semaId;
	unsigned int unk;
	unsigned char tx[32];
	unsigned char rx[32];
	unsigned int unk1[4];
	int (*callback)(struct SceSysconPacket *packet, void *argp);
	void *argp;
	unsigned int time;
	unsigned int unk2[5];
} SceSysconPacket; /* size 0x80 */

/** A set of debug handlers for syscon, that you can set in sceSysconSetDebugHandlers(). */
typedef struct SceSysconDebugHandlers {
	/** Structure size (probably, unused). */
	int size;
	/** Callback ran right before running a packet, with a pointer to it passed as the first argument. */
	void (*start)(SceSysconPacket *packet);
	/** Callback ran right after finishing running a packet, with a pointer to it passed as the first argument. */
	void (*end)(SceSysconPacket *packet);
} SceSysconDebugHandlers;

typedef int (*SceSysconCmdExecAsyncCallback)(SceSysconPacket *packet, void *argp);

typedef void (*SceSysconCallback)(int enable, void *argp);

/**
 * Waits until the syscon is initialized.
 *
 * @return 0 on success.
 */
int sceSysconWaitInitialized(void);

/**
 * Execute synchronously a syscon packet.
 *
 * @param packet The packet to execute. Its tx member needs to be initialized.
 * @param flags The packet flags. Check SceSysconPacketFlags.
 *
 * @return 0 on success.
 */
int sceSysconCmdExec(SceSysconPacket *packet, unsigned int flags);

/**
 * Execute asynchronously a syscon packet.
 *
 * @param packet The packet to execute. Its tx member needs to be initialized.
 * @param flags The packet flags. Check SceSysconPacketFlags.
 * @param callback The packet callback. Check the callback member of SceSysconPacket.
 * @param argp The second argument that will be passed to the callback when executed.
 *
 * @return 0 on success.
 */
int sceSysconCmdExecAsync(SceSysconPacket *packet, unsigned int flags, SceSysconCmdExecAsyncCallback cb, void *argp);

/**
 * Wait for the currently queued syscon packets to be executed, or check if any are in the queue.
 *
 * @param packet The packet you want to check or wait for, or NULL if you want to check or wait for all the currently running packets.
 * @param noWait Set to 1 if you just want to check the packet status, or 0 if you want the function to return only when the packet queue is empty.
 *
 * @return 1 if packets are still running (and noWait was set to 1), 0 on success, < 0 otherwise.
 */
int sceSysconCmdSync(SceSysconPacket *packet, int noWait);

/**
 * Reset the device.
 *
 * @param type The reset type value, one of SceSysconResetType.
 * @param mode The resetting mode (?).
 *
 * @return 0 on success.
 */
int sceSysconSetPowerMode(int type, int mode);

int sceSysconReadCommand(unsigned short cmd, void *buffer, SceSize size);
int sceSysconSendCommand(unsigned short cmd, const void *buffer, SceSize size);

/**
 * Set the debug handlers.
 *
 * @return 0.
 */
int sceSysconSetDebugHandlers(const SceSysconDebugHandlers *handlers);

/**
 * Turn a LED on or off.
 *
 * @param led The LED id.
 * @param enable Set this value to 1 if you want the LED to turn on, or 0 if you want it to turn off.
 *
 * @return 0 on success.
 */
int sceSysconCtrlLED(int led, int enable);

/**
 * Set PSTV LED mode.
 *
 * @param mode Set to 0 for on, 1 for slow blink, 2 for fast blink.
 *
 * @return 0 on success.
 */
int sceSysconCtrlDolceLED(int mode);

/**
 * Set the memory stick power.
 *
 * @param power The new power value.
 *
 * @return 0 on success.
 */
int sceSysconCtrlRMRPower(int power);

/**
 * Set the SD power.
 *
 * @param power The new power value.
 *
 * @return 0 on success.
 */
int sceSysconCtrlSdPower(int power);

/**
 * Set the ADV7533 HDMI CEC power.
 *
 * @param power The new power value.
 *
 * @return 0 on success.
 */
int sceSysconCtrlHdmiCecPower(int power);

int sceSysconCtrlManualChargeMode(int);

int sceSysconEnableHibernateIO(int);

int sceSysconIduModeClear(void);
int sceSysconIduModeSet(void);
int sceSysconIsDownLoaderMode(void);

int sceSysconLogStart(void);
int sceSysconLogStartWaiting(void);
int sceSysconLogReadData(unsigned short, void *buff, SceSize size);

int sceSysconShowModeClear(void);
int sceSysconShowModeSet(void);

/**
 * Get the baryon version.
 *
 * @return The baryon version.
 */
int sceSysconGetBaryonVersion(void);

/**
 * Get the baryon timestamp.
 *
 * @return The baryon timestamp.
 */
unsigned long long sceSysconGetBaryonTimestamp();

int sceSysconGetBatteryCalibData(int *, int *, int *, int *);
int sceSysconGetHardwareInfo(void);
int sceSysconGetHardwareInfo2(int *, int *, int *);
int sceSysconGetLogInfo(int *);
int sceSysconGetManualChargeMode(int *);
int sceSysconGetManufacturesStatus(int *);
int sceSysconGetTemperatureLog(int *);
int sceSysconGetUsbDetStatus(int *);

int sceSysconClearTemperatureLog(int);

int sceSysconBeginConfigstorageTransaction(void);
int sceSysconCommitConfigstorageTransaction(void);
int sceSysconEndConfigstorageTransaction(void);
int sceSysconLoadConfigstorageScript(unsigned short, const void *buff, SceSize size);
int sceSysconVerifyConfigstorageScript(unsigned short, const void *buff, SceSize size);

/**
 * Set the alarm callback, that will be ran when the alarm timer is passed.
 *
 * @param callback The callback function.
 * @param argp The second argument that will be passed to the callback.
 *
 * @return 0.
 */
int sceSysconSetAlarmCallback(SceSysconCallback callback, void *argp);

/**
 * Set the low battery callback, that will be ran when the battery is low.
 *
 * @param callback The callback function.
 * @param argp The second argument that will be passed to the callback.
 *
 * @return 0.
 */
int sceSysconSetLowBatteryCallback(SceSysconCallback callback, void *argp);

/**
 * Set the thermal alert callback, that will be ran when the temperature reaches a critical point.
 *
 * @param callback The callback function.
 * @param argp The second argument that will be passed to the callback.
 *
 * @return 0.
 */
int sceSysconSetThermalAlertCallback(SceSysconCallback callback, void *argp);

#ifdef __cplusplus
}
#endif

#endif /* _VDSUITE_KERNEL_SYSCON_H */


#ifndef _PSP2_AVCONFIG_H_
#define _PSP2_AVCONFIG_H_

#include <scetypes.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SCE_AVCONFIG_VOLUME_MAX      30
#define SCE_AVCONFIG_VOLUME_AVLS_MAX 21

#define SCE_AVCONFIG_VOLCTRL_UNK_0     0
#define SCE_AVCONFIG_VOLCTRL_ONBOARD   1
#define SCE_AVCONFIG_VOLCTRL_BLUETOOTH 2
#define SCE_AVCONFIG_VOLCTRL_UNK_3     3
#define SCE_AVCONFIG_VOLCTRL_UNK_4     4

#define SCE_AVCONFIG_AUDIO_DEVICE_VITA_0       0x001 //!< Not Dolce
#define SCE_AVCONFIG_AUDIO_DEVICE_MULTI_CN     0x002 //!< (sceSysconGetMultiCnInfo & 0xff00) == 0x300 (from SceHpremoteForDriver_2229EF51)
#define SCE_AVCONFIG_AUDIO_DEVICE_AUDIO_OUT    0x004 //!< 3.5mm audio out
#define SCE_AVCONFIG_AUDIO_DEVICE_HDMI         0x008 //!< HDMI audio out
#define SCE_AVCONFIG_AUDIO_DEVICE_BT_AUDIO_OUT 0x010 //!< Bluetooth audio out
#define SCE_AVCONFIG_AUDIO_DEVICE_VITA_8       0x100 //!< Not Dolce
#define SCE_AVCONFIG_AUDIO_DEVICE_AUDIO_IN     0x400 //!< 3.5mm audio in
#define SCE_AVCONFIG_AUDIO_DEVICE_BT_AUDIO_IN  0x800 //!< Bluetooth audio in

#define SCE_AVCONFIG_REG_BT_MIC       0
#define SCE_AVCONFIG_REG_AVLS         1
#define SCE_AVCONFIG_REG_SOUND_OUTPUT 2
#define SCE_AVCONFIG_REG_AVLS_TIMER   3
#define SCE_AVCONFIG_REG_SPEAKER_MUTE 4

#define SCE_AVCONFIG_VOLKEY_END  0
#define SCE_AVCONFIG_VOLKEY_UP   1
#define SCE_AVCONFIG_VOLKEY_DOWN 2

#define SCE_AVCONFIG_CB_FLAG_UNK_1      0x01
#define SCE_AVCONFIG_CB_FLAG_BT_VOL     0x02
#define SCE_AVCONFIG_CB_FLAG_AVLS       0x04
#define SCE_AVCONFIG_CB_FLAG_FORCE_AVLS 0x08
#define SCE_AVCONFIG_CB_FLAG_MUTED      0x10

/**
 * Get the maximum brightness.
 *
 * @param[out] maxBrightness - Maximum brightness.
 *
 * @return 0 on success, < 0 on error.
 */
int sceAVConfigGetDisplayMaxBrightness(int *maxBrightness);

/**
 * Set the screen brightness.
 *
 * @param brightness - Brightness that the screen will be set to (range 21-65536, 0 turns off the screen).
 *
 * @return 0 on success, < 0 on error.
 */
int sceAVConfigSetDisplayBrightness(int brightness);

/**
 * Get the shutter volume.
 *
 * @param[out] volume - shutter volume.
 *
 * @return 0 on success, < 0 on error.
 */
int sceAVConfigGetShutterVol(int *volume);

/**
 * Get the system volume.
 *
 * @param[out] volume - System volume.
 *
 * @return 0 on success, < 0 on error.
 */
int sceAVConfigGetSystemVol(int *volume);

/**
 * Set the system volume.
 *
 * @param volume - volume that the device will be set to (range 0-30).
 *
 * @return 0 on success, < 0 on error.
 */
int sceAVConfigSetSystemVol(int volume);

/**
 * Turns on mute.
 *
 * @return 0 on success, < 0 on error.
 *
 */
int sceAVConfigMuteOn(void);

/**
 * Write to the registry key /CONFIG/SOUND/main_volume.
 *
 * @param vol - Volume level 0 to 30
 *
 * @return 0 on success, < 0 on error.
 */
int sceAVConfigWriteRegSystemVol(SceUInt32 vol);

/**
 * Get volume control information.
 *
 * @param[out] volCtrl - Device which has volume controlled. If the volume
 * cannot be controlled, then this address is not written to.
 * @param[out] muted - Deviced muted state
 * @param[out] avls - Device AVLS state
 *
 * @return 0 on success, < 0 on error.
 */
int sceAVConfigGetVolCtrlEnable(SceUInt32 *volCtrl, SceBool *muted, SceBool *avls);

/**
 * Get connected audio devices.
 *
 * @param[out] flags - Bitwise OR of device flags
 *
 * @return 0 on success, < 0 on error.
 */
int sceAVConfigGetConnectedAudioDevice(SceUInt32 *flags);

/**
 * Set configuration values which correspond to registry entries. Does not change the registry.
 *
 * @param key - Registry derived value to change
 * @param value - Value to set to
 *
 * @return 0 on success, < 0 on error.
 */
int sceAVConfigChangeReg(SceUInt32 key, int value);

/**
 * Send Bluetooth volume key
 *
 * @param key - Key to send
 *
 * @return 0 on success, < 0 on error.
 */
int sceAVConfigSendVolKey(SceUInt32 key);

/**
 * Get Bluetooth volume information
 *
 * @param[out] unk - Unknown
 * @param[out] vol - Volume
 *
 * @return 0 on success, < 0 on error.
 */
int sceAVConfigGetBtVol(int *unk, SceUInt32 *vol);

/**
 * Set OLED/LCD colour space mode
 *
 * @param mode - 0 default, 1 high saturation
 *
 * @return 0 on success, < 0 on error.
 */
int sceAVConfigSetDisplayColorSpaceMode(SceUInt32 mode);

#ifdef __cplusplus
}
#endif

#endif


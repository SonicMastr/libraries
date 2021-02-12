/*
	Vita Development Suite Libraries
*/

#ifndef _DOLCESDK_PSP2_SHELLSVC_H_
#define _DOLCESDK_PSP2_SHELLSVC_H_

#include <scetypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/* SceShellUtil */

typedef enum SceShellUtilLockType {
	SCE_SHELL_UTIL_LOCK_TYPE_PS_BTN             = 0x1,
	SCE_SHELL_UTIL_LOCK_TYPE_QUICK_MENU         = 0x2,
	SCE_SHELL_UTIL_LOCK_TYPE_POWEROFF_MENU      = 0x4,
	SCE_SHELL_UTIL_LOCK_TYPE_UNK8               = 0x8,
	SCE_SHELL_UTIL_LOCK_TYPE_USB_CONNECTION     = 0x10,
	SCE_SHELL_UTIL_LOCK_TYPE_MC_INSERTED        = 0x20,
	SCE_SHELL_UTIL_LOCK_TYPE_MC_REMOVED         = 0x40,
	SCE_SHELL_UTIL_LOCK_TYPE_UNK80              = 0x80,
	SCE_SHELL_UTIL_LOCK_TYPE_UNK100             = 0x100,
	SCE_SHELL_UTIL_LOCK_TYPE_UNK200             = 0x200,
	SCE_SHELL_UTIL_LOCK_TYPE_MUSIC_PLAYER       = 0x400,
	SCE_SHELL_UTIL_LOCK_TYPE_PS_BTN_2           = 0x800 //! without the stop symbol
} SceShellUtilLockType;

typedef enum SceShellUtilLockMode {
	SCE_SHELL_UTIL_LOCK_MODE_LOCK       = 1,
	SCE_SHELL_UTIL_LOCK_MODE_UNLOCK     = 2
} SceShellUtilLockMode;

typedef void (SceShellUtilEventHandler)(int result, SceShellUtilLockMode mode, SceShellUtilLockType type, void *userData);

/**
 * Init events
 *
 * @param[in] unk - Unknown, use 0
 *
 * @return 0 on success, < 0 on error.
*/
int sceShellUtilInitEvents(int unk);

/**
 * Register event handler
 *
 * @param[in] handler - Event handler
 *
 * @param[in] userData - The user data passed to the handler
 *
 * @return 0 on success, < 0 on error.
*/
int sceShellUtilRegisterEventHandler(SceShellUtilEventHandler *handler, void *userData);

/**
 * Lock event
 *
 * @param[in] type - One of ::SceShellUtilLockType
 *
 * @return 0 on success, < 0 on error.
*/
int sceShellUtilLock(SceShellUtilLockType type);

/**
 * Unlock event
 *
 * @param[in] type - One of ::SceShellUtilLockType
 *
 * @return 0 on success, < 0 on error.
*/
int sceShellUtilUnlock(SceShellUtilLockType type);

/**
 * Reboot the device
 *
 * @param[in] unk - pass 0
 */
void sceShellUtilRequestColdReset(int unk);

/**
 * Poweroff the device
 *
 * @param[in] unk - pass 0
 */
void sceShellUtilRequestStandby(int unk);

/**
 * Show "A serious error has occured" message and reboot
 *
 * @param[in] safeModeType - sets type of safemode to reboot into, 0 to reboot normally
 * @param[in] errorCode - error code to display in the message
 * @param[in] errorMessageType - ex. 0 "Contact technical support"
 */
void sceShellUtilRequestColdResetWithError(int safeModeType, int errorCode, int errorMessageType);

/**
 * SceTextClipboardStorage is cached memory block with usable size of 0x1FFD bytes
 * allocated by SceShellSvc on startup. Normally you would access this storage with
 * clipboard sysmodule, however it can also be accessed directly with SceShellSvc
 * functions. This memory can be accesed from any part of the system and is managed
 * by SceShell. For example, you can write to it in one application and access
 * written data from the other. Or you can write to it in application and access
 * written data from the plugin.
 *
 * @param[in] data - pointer to the data to write
 * @param[in] size - size of data to write. Must not exceed 0x1FFD.
 */

SceInt32 sceShellUtilTextClipboardWrite(const void* data, SceSize size);

/**
 * Read from text clipboard
 *
 * @param[in] data - pointer to the buffer where the read data will be placed
 * @param[in] size - size of data to read
 * @param[out] textlen - length actually read
 */

SceInt32 sceShellUtilTextClipboardRead(void* data, SceSize size, SceSize *textlen);

/**
 * Returns size of the data that was written to clipboard with
 * sceShellUtilTextClipboardWrite
 */

SceUInt32 sceShellUtilTextClipboardGetUsedSize(void);

/**
 * Sets text in time display, UTF-16 (remains until reboot?)
 */

SceInt32 sceShellUtilSetTimeText(SceWChar16* unk, SceWChar16* text);

/**
 * Set airplane icon visibility
 *
 * @param[in] mode - 0 to hide, 1 to show
 */

SceInt32 sceShellUtilSetAirplaneIconMode(SceUInt32 mode);

/**
 * Set Bluetooth icon visibility
 *
 * @param[in] mode - 0 to hide, 1 to show
 */

SceInt32 sceShellUtilSetBtIconMode(SceUInt32 mode);

/**
 * Set BGM mode
 *
 * @param[in] mode - 0 to disable, 1 to enable
 */

SceInt32 sceShellUtilSetBGMMode(SceUInt32 mode);

/**
 * Set system language. Takes about 5 sec to apply.
 */

SceInt32 sceShellUtilSetSystemLanguage(SceUInt32 languageId);

/* SceShellSvc */

typedef struct SceShellSvcSvcObjVtable SceShellSvcSvcObjVtable;

typedef struct SceShellSvcSvcObj {
	SceShellSvcSvcObjVtable *vptr;
	// more ...
} SceShellSvcSvcObj;

SceShellSvcSvcObj *sceShellSvcGetSvcObj(void);

#ifdef __cplusplus
}
#endif

#endif /* _DOLCESDK_PSP2_SHELLSVC_H_ */


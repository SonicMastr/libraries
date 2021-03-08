/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_USER_INCOMING_DIALOG_H
#define _VDSUITE_USER_INCOMING_DIALOG_H

#include <kernel/libkernel.h>
#include <scetypes.h>
#include <sdk_version.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Dialog status
 */
typedef enum SceIncomingDialogStatus {
	SCE_INCOMING_DIALOG_STATUS_NONE,
	SCE_INCOMING_DIALOG_STATUS_BUSY,
	SCE_INCOMING_DIALOG_STATUS_RUNNING,
	SCE_INCOMING_DIALOG_STATUS_ACCEPTED,
	SCE_INCOMING_DIALOG_STATUS_REJECTED,
	SCE_INCOMING_DIALOG_STATUS_CLOSED,
	SCE_INCOMING_DIALOG_STATUS_TIMEOUT,
} SceIncomingDialogStatus;

/**
 * Errors
 */
#define SCE_INCOMING_DIALOG_ERROR_NOT_INITIALIZED			-2146409983 /* 0x80106201 */
#define SCE_INCOMING_DIALOG_ERROR_INVALID_ARGUMENT			-2146409982 /* 0x80106202 */

typedef struct SceIncomingDialogParam {
	SceInt32 sdkVersion;
	SceChar8 titleId[0x10];				/*	Title ID of the application to open when "accept" button has been pressed.
											The icon of this application is shown in the dialog. Can be empty. */
	SceChar8 audioPath[0x80];			/*	Path to audio file that plays when the dialog is opened. File types can be
											mp3, at9, m4a. Can be empty. */
	SceUInt32 timeout;					/*	Time in seconds before the dialog closes automatically. */
	SceChar8 unk1;						/*	Set to zero. */
	SceWChar16 unk2[0x20];				/*	Set to zero. */
	SceWChar16 acceptText[0x20];		/*	Text for "accept" button. */
	SceWChar16 rejectText[0x20];		/*	Text for "reject" button. If empty, this button will not be displayed. */
	SceWChar16 dialogText[0x40];		/*	Text for dialog window. When the dialog is opened, a notification with the
											same text will be displayed. */
	SceWChar16 notificationText[0x40];	/*	Text for a notification that shows after the dialog is closed for any
											reason. If empty, the notification will not be shown. */
	SceChar8 appParam[];				/*	String to pass to the application that is opened when the "accept" button
											is pressed. Can be a string of length zero but must not have size zero.
											The opened application can retrieve this with sceAppMgrGetAppParam. */
} SceIncomingDialogParam;

/**
 * Initialize incoming dialog library, initType must be 0.
 */
SceInt32 sceIncomingDialogInit(int initType);

/**
 * Open incoming dialog.
 */
SceInt32 sceIncomingDialogOpen(const SceIncomingDialogParam* dialogParam);

/**
 * Returns current status of incoming dialog.
 */
SceInt32 sceIncomingDialogGetStatus(void);

/**
 * Force exit to LiveArea and show dialog window
 */
SceInt32 sceIncomingDialogSwitchToDialog(void);

/**
 * Close incoming dialog.
 */
SceInt32 sceIncomingDialogClose(void);

/**
 * Terminate incoming dialog library
 */
SceInt32 sceIncomingDialogTerm(void);

static inline
void sceIncomingDialogParamInit(SceIncomingDialogParam* dialogParam)
{
	sceClibMemset(dialogParam, 0x0, sizeof(SceIncomingDialogParam));
	dialogParam->sdkVersion = SCE_PSP2_SDK_VERSION;
	dialogParam->appParam[0] = 0;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _VDSUITE_USER_INCOMING_DIALOG_H */

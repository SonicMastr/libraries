/*
	Vita Development Suite Libraries
*/

#ifndef _DOLCESDK_PSP2_INCOMING_DIALOG_H_
#define _DOLCESDK_PSP2_INCOMING_DIALOG_H_

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
	SCE_INCOMING_DIALOG_NOT_RUNNING,
	SCE_INCOMING_DIALOG_BUSY,
	SCE_INCOMING_DIALOG_RUNNING,
	SCE_INCOMING_DIALOG_ACCEPTED,
	SCE_INCOMING_DIALOG_REJECTED,
	SCE_INCOMING_DIALOG_CLOSED,
	SCE_INCOMING_DIALOG_TIMEOUT,
} SceIncomingDialogStatus;

/**
 * Errors
 */
#define SCE_INCOMING_DIALOG_ERROR_INVALID_ARG               ((int)0x80106202)

typedef struct SceIncomingDialogParam {
	SceInt32 sdkVersion;
	SceChar8 titleid[0x10];              // TitleId of the application to open when "accept" button has been pressed. Can be all zero.
	SceChar8 audioPath[0x80];            // Path to audio file that will be played during dialog, .mp3, .at9, m4a. Can be all zero.
	SceUInt32 dialogTimer;               // Time to show dialog in seconds
	SceInt32 unk_BC;                     // Can be set to 0
	SceChar8 reserved1[0x3E];
	SceWChar16 buttonRightText[0x20];    // Text for "accept" button. Must be null-terminated.
	SceWChar16 buttonLeftText[0x20];     // Text for "reject" button. Must be null-terminated. If all zero, only "accept" button will be created.
	SceWChar16 dialogText[0x81];         // Text for dialog window, also shared with notification. Must be null-terminated.
} SceIncomingDialogParam;

/**
 * Initialize incoming dialog library, initType must be 0.
 */
SceInt32 sceIncomingDialogInit(int initType);

/**
 * Open incoming dialog.
 */
SceInt32 sceIncomingDialogOpen(SceIncomingDialogParam* dialogParam);

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
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _DOLCESDK_PSP2_INCOMING_DIALOG_H_ */

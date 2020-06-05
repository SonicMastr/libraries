#ifndef _DOLCESDK_PSP2_NOTIFICATION_UTIL_H_
#define _DOLCESDK_PSP2_NOTIFICATION_UTIL_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Errors
 */
#define SCE_NOTIFICATIONUTIL_ERROR_INTERNAL               0x80106301

/**
 * BGDL-type notification event handler function
 */
typedef void (*SceNotificationUtilProgressEventHandler)(SceUInt32 eventId);

typedef struct SceNotificationUtilProgressInitParam {
	SceWChar16 notificationText[0x273];
	SceInt16 separator0;                                     // must be 0
	SceNotificationUtilProgressEventHandler eventHandler;
	SceInt32 unk_4EC;                                        // can be set to 0
	SceWChar16 cancelDialogText[0x3E];
	SceInt16 separator1;                                     // must be 0
} SceNotificationUtilProgressInitParam;

typedef struct SceNotificationUtilProgressUpdateParam {
	SceWChar16 notificationText[0x7E];
	SceInt16 separator0;                  //must be 0
	SceFloat targetProgress;
	SceChar8 reserved[0x3C];
} SceNotificationUtilProgressUpdateParam;

typedef struct SceNotificationUtilProgressFinishParam {
	SceWChar16 notificationText[0x273];
	SceInt16 separator0; //must be 0
} SceNotificationUtilProgressFinishParam;

/**
 * Initialize notification util for use with BG application.
 *
 * Does not need to be called for normal applications.
 */
SceInt32 sceNotificationUtilBgAppInitialize(void);

/**
 * Send notification.
 *
 * Text buffer size must be 0x470.
 */
SceInt32 sceNotificationUtilSendNotification(const SceWChar16* text);

/**
 * Clean notifications for calling app from notification history.
 */
SceInt32 sceNotificationUtilCleanHistory(void);

/**
 * Start BGDL-type notification.
 */
SceInt32 sceNotificationUtilProgressBegin(SceNotificationUtilProgressInitParam* initParam);

/**
 * Update BGDL-type notification.
 */
SceInt32 sceNotificationUtilProgressUpdate(SceNotificationUtilProgressUpdateParam* updateParam);

/**
 * Finish BGDL-type notification.
 */
SceInt32 sceNotificationUtilProgressFinish(SceNotificationUtilProgressFinishParam* finishParam);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _DOLCESDK_PSP2_NOTIFICATION_UTIL_H_ */

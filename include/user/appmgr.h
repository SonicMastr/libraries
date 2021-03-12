/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_USER_APPMGR_H
#define _VDSUITE_USER_APPMGR_H

#include_next <appmgr.h>

#include <stdint.h>

#include <fios2/fios2_types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceAppMgrExecOptParam SceAppMgrExecOptParam; // Missing struct
typedef struct SceAppMgrLaunchAppOptParam SceAppMgrLaunchAppOptParam; // Missing struct

#define SCE_APPMGR_BUDGET_MODE_MAIN              2 // Main LPDDR2 only
#define SCE_APPMGR_BUDGET_MODE_MAIN_PHYCONT      3 // Main and phycont or CDLG which is also contiguous
#define SCE_APPMGR_BUDGET_MODE_MAIN_PHYCONT_CDLG 4 // Main and phycont and CDLG

typedef struct SceAppMgrBudgetInfo {
// 0x00
	SceSize size;              //!< Sizes if 0x88 bytes
	SceUInt32 mode;            //!< Application budget mode
	SceUInt32 unk_8;
	SceUInt32 budgetMain;      //!< Main LPDDR2 budget in bytes
// 0x10
	SceUInt32 freeMain;        //!< Free main LPDDR2 in bytes
	SceUInt32 hasCdlg;         //!< Has CDLG memory type in budget
	SceUInt32 unk_14;          //!< Non-zero if CDLG is used, otherwise 0
	SceUInt32 budgetCdlg;      //!< CDLG budget in bytes
// 0x20
	SceUInt32 freeCdlg;        //!< Free CDLG in bytes
	SceUInt32 unk_24;          //!< always 0
	SceUInt32 unk_28;          //!< Non-zero if phycont is used, otherwise 0
	SceUInt32 budgetPhycont;   //!< Phycont budget in bytes
// 0x30
	SceUInt32 freePhycont;     //!< Free phycont in bytes
	SceUInt32 allow;           //!< Some memory type?
	SceUChar8 unk_38[0x20];    //!< Some memory type?
	SceUInt32 unk_58;
	SceUInt32 budgetCdram;     //!< Cdram budget in bytes
// 0x60
	SceUInt32 freeCdram;       //!< Free Cdram in bytes
	SceUChar8 reserved_64[0x24];
// 0x88
} SceAppMgrBudgetInfo;

typedef struct SceAppMgrTrcNotification {
    int unk;                           //!< Set to 0
    char message[0x3C];                //!< Must be null-terminated
} SceAppMgrTrcNotification;

/**
 * Get Process ID by Title ID
 *
 * @param[out] pid - Process ID
 * @param[in] name - Title ID
 *
 * @return 0 on success, < 0 on error.
 */
int sceAppMgrGetIdByName(SceUID *pid, const char *name);

/**
 * Get Title ID by Process ID
 *
 * @param[in] pid - Process ID
 * @param[out] name - Title ID
 *
 * @return 0 on success, < 0 on error.
 */
int sceAppMgrGetNameById(SceUID pid, char *name);

/**
 * Destroy other apps
 *
 * @return 0 on success, < 0 on error.
 */
int sceAppMgrDestroyOtherApp(void);

/**
 * Destroy an application by Title ID
 *
 * @param[in] name - Title ID of the application
 *
 * @return 0 on success, < 0 on error.
 */
int sceAppMgrDestroyAppByName(const char *name);

/**
 * Destroy an application by Application ID
 *
 * @param[in] appId - Application ID of the application
 *
 * @return 0 on success, < 0 on error.
 */
int sceAppMgrDestroyAppByAppId(SceUID appId);

/**
 * Get PID of an application for Shell
 *
 * @param[in] appId - Application ID of the application
 *
 * @return The PID on success, < 0 on error.
 */
SceUID sceAppMgrGetProcessIdByAppIdForShell(SceUID appId);

/**
 * Get a list of running applications
 *
 * @param[out] appIds - Array of running application IDs
 * @param[in] count - Max number of running applications to search
 *
 * @return Number of running applications.
 */
int sceAppMgrGetRunningAppIdListForShell(SceUID *appIds, int count);

/**
 * Copies app param to an array
 *
 * @param[out] param - pointer to a 1024 byte location to store the app param
 *
 * @return 0 on success, < 0 on error.
 *
 * @note App param example: type=LAUNCH_APP_BY_URI&uri=psgm:play?titleid=NPXS10031
 */
int sceAppMgrGetAppParam(char *param);

/**
 * Start an application by URI
 *
 * @param[in] flags - Must be 0x20000
 * @param[in] uri - Uri to launch
 *
 * @return 0 on success, < 0 on error.
 *
 * @note If flags != 0x20000, Livearea is opened.
 */
int sceAppMgrLaunchAppByUri(int flags, const char *uri);

/**
 * Start an application by Title ID
 *
 * @param[in] name - Title ID of the application
 * @param[in] param - The params passed to the application which can be retrieved with ::sceAppMgrGetAppParam
 * @param[in] optParam - Optional params
 *
 * @return 0 on success, < 0 on error.
 */
int sceAppMgrLaunchAppByName2(const char *name, const char *param, SceAppMgrLaunchAppOptParam *optParam);

/**
 * Start an application by Title ID for Shell
 *
 * @param[in] name - Title ID of the application
 * @param[in] param - The params passed to the application which can be retrieved with ::sceAppMgrGetAppParam
 * @param[in] optParam - Optional params
 *
 * @return Application ID (?)
 */
SceUID sceAppMgrLaunchAppByName2ForShell(const char *name, const char *param, SceAppMgrLaunchAppOptParam *optParam);

/**
 * Mount game data
 *
 * @param[in] path - ux0:app/TITLEID
 * @param[in] unk1 - Unknown, set 0
 * @param[in] unk2 - Unknown, set 0
 * @param[in] mount_point - Mountpoint to use
 *
 * @return 0 on success, < 0 on error.
 *
 */
int sceAppMgrGameDataMount(const char *path, int unk1, int unk2, const char *mount_point);

/**
 * Mount application data
 *
 * @param[in] id - App data ID
 * @param[in] mount_point - Mountpoint to use
 *
 * @return 0 on success, < 0 on error.
 *
 * @note id: 100 (photo0), 101 (friends), 102 (messages), 103 (near), 105 (music), 108 (calendar)
 */
int sceAppMgrAppDataMount(int id, const char *mount_point);

/**
 * Mount application data by Title ID
 *
 * @param[in] id - App data ID
 * @param[in] titleid - Application title ID
 * @param[in] mount_point - Mountpoint to use
 *
 * @return 0 on success, < 0 on error.
 *
 * @note id: 106 (ad), 107 (ad)
 */
int sceAppMgrAppDataMountById(int id, const char *titleid, const char *mount_point);

/**
 * Get application params from SFO descriptor
 *
 * @param[in] pid - Process ID
 * @param[in] param - Param ID in the SFO descriptor
 * @param[out] string - Param data
 * @param[in] length - Length of the param data
 *
 * @return 0 on success, < 0 on error.
 *
 * @note param: 6 (contentid) 8 (category), 9 (stitle/title?), 10 (title/stitle?), 12 (titleid)
 */
int sceAppMgrAppParamGetString(int pid, int param, char *string, SceSize length);

/**
 * Get device info
 *
 * @param[in] dev - Device to get info about
 * @param[out] max_size - Capacity of the device
 * @param[out] free_size - Free space of the device
 *
 * @return 0 on success, < 0 on error.
 *
 * @note dev: ux0:
 */
int sceAppMgrGetDevInfo(const char *dev, uint64_t *max_size, uint64_t *free_size);

/**
 * Mount application data (PSPEmu)
 *
 * @param[in] id - App data ID
 * @param[in] mount_point - Mountpoint to use
 *
 * @return 0 on success, < 0 on error.
 *
 * @note id: 400 (ad), 401 (ad), 402 (ad)
 */
int sceAppMgrMmsMount(int id, const char *mount_point);

/**
 * Mount PSPEmu virtual memory stick
 *
 * @param[in] mount_point - Mountpoint to use
 *
 * @return 0 on success, < 0 on error.
 *
 * @note mount_point: ms
 */
int sceAppMgrPspSaveDataRootMount(const char *mount_point);

/**
 * Mount working directory
 *
 * @param[in] id - Working directory ID
 * @param[in] mount_point - Mountpoint to use
 *
 * @return 0 on success, < 0 on error.
 *
 * @note id: 200 (td), 201 (td), 203 (td), 204 (td), 206 (td)
 */
int sceAppMgrWorkDirMount(int id, const char *mount_point);

/**
 * Mount working directory by Title ID
 *
 * @param[in] id - Working directory ID
 * @param[in] titleid - Application Title ID
 * @param[in] mount_point - Mountpoint to use
 *
 * @return 0 on success, < 0 on error.
 *
 * @note id: 205 (cache0), 207 (td)
 */
int sceAppMgrWorkDirMountById(int id, const char *titleid, const char *mount_point);

/**
 * Unmount a mountpoint
 *
 * @param[in] mount_point - Mountpoint to unmount
 *
 * @return 0 on success, < 0 on error.
 *
 * @note Unmount app0: for example to enable write access to ux0:app/TITLEID
 */
int sceAppMgrUmount(const char *mount_point);

/**
 * Convert vs0 path string to a new one usable by applications
 *
 * @param[in] path - Path to convert
 * @param[in] mount_point - Mountpoint to use
 * @param[in] unk - Unknown
 *
 * @return 0 on success, < 0 on error.
 */
int sceAppMgrConvertVs0UserDrivePath(char *path, char *mount_point, int unk);

/**
 * Resolve a path to the corresponding true path (uses ::sceFiosKernelOverlayResolveSync underneath).
 *
 * @param[in] path - Path to convert (e.g. app0:)
 * @param[out] resolved_path - True resolved path
 * @param[in] resolved_path_size - size of the resolved_path buffer
 *
 * @return 0 on success, < 0 on error.
 */
int sceAppMgrGetRawPath(const char *path, char *resolved_path, int resolved_path_size);

/**
 * Get the real/resolved path of app0: (where it's actually mounted)
 *
 * @param[in] appId - Use -2 for the current application
 * @param[out] resolved_path - Buffer that will hold the resolved path.
 *
 * @return 0 on success.
 */
int sceAppMgrGetRawPathOfApp0ByAppIdForShell(int appId, char resolved_path[SCE_FIOS_OVERLAY_POINT_MAX]);

/**
 * Get application memory budget info.
 *
 * @return 0 on success, < 0 on error.
 *
 */
int sceAppMgrGetBudgetInfo(SceAppMgrBudgetInfo *info);

/**
 * Send TRC notification. Only visible if TRC notifications are enabled.
 *
 * @param[in] notification - pointer to struct containing notification text
 * @param[in] blocking - Will wait for semaphore if set to true, otherwise will poll semaphore.
 *
 * @return 0 on success, < 0 on error.
 */
int sceAppMgrSendNotificationRequest(SceAppMgrTrcNotification *notification, SceBool blocking);

/**
 * Grows main memory budget of system mode app.
 *
 * @param[in] size - size to grow to
 * @param[in] unk - set to 1
 */
int sceAppMgrGrowMemory(SceSize size, int unk);

/**
 * Grows main memory budget of system mode app.
 *
 * @param[in] size - size to grow to
 * @param[in] unk - set to 1
 */
int sceAppMgrGrowMemory3(SceSize size, int unk);

/**
 * Shared Framebuffer
 */

typedef struct SceSharedFbInfo SceSharedFbInfo;

SceUID _sceSharedFbOpen(int index, SceUInt32 buildVersion);

static __inline__
SceUID sceSharedFbOpen(int index) {
	return _sceSharedFbOpen(index, SCE_PSP2_SDK_VERSION);
}

int sceSharedFbClose(SceUID fbId);

int sceSharedFbBegin(SceUID fbId, SceSharedFbInfo *fbInfo);

int sceSharedFbEnd(SceUID fbId);

int sceSharedFbGetInfo(SceUID fbId, SceSharedFbInfo *fbInfo);

#ifdef __cplusplus
}
#endif

#endif /* _VDSUITE_USER_APPMGR_H */


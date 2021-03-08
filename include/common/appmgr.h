/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_COMMON_APPMGR_H
#define _VDSUITE_COMMON_APPMGR_H

#include_next <appmgr.h>

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif

#define SCE_APPMGR_MOUNTPOINT_DATA_MAXSIZE 16

#define SCE_APPMGR_SAVEDATA_SLOT_TITLE_MAXSIZE     64
#define SCE_APPMGR_SAVEDATA_SLOT_SUBTITLE_MAXSIZE  128
#define SCE_APPMGR_SAVEDATA_SLOT_DETAIL_MAXSIZE    512
#define SCE_APPMGR_SAVEDATA_SLOT_ICON_PATH_MAXSIZE 64

#define SCE_APPMGR_NP_DRM_ADDCONT_ID_SIZE 17

typedef SceUInt32 SceAppMgrSaveDataSlotStatus;
typedef SceUInt32 SceAppMgrSaveDataDataSaveMode;

typedef struct SceAppMgrMountPoint {
	SceChar8 data[SCE_APPMGR_MOUNTPOINT_DATA_MAXSIZE];
} SceAppMgrMountPoint;

typedef struct SceAppMgrSaveDataSlotParam {
	SceAppMgrSaveDataSlotStatus status;
	SceChar8 title[SCE_APPMGR_SAVEDATA_SLOT_TITLE_MAXSIZE];
	SceChar8 subTitle[SCE_APPMGR_SAVEDATA_SLOT_SUBTITLE_MAXSIZE];
	SceChar8 detail[SCE_APPMGR_SAVEDATA_SLOT_DETAIL_MAXSIZE];
	SceChar8 iconPath[SCE_APPMGR_SAVEDATA_SLOT_ICON_PATH_MAXSIZE];
	SceInt32 userParam;
	SceUInt32 sizeKiB;
	SceDateTime modifiedTime;
	SceChar8 reserved[48];
} SceAppMgrSaveDataSlotParam;

typedef struct SceAppMgrSaveDataDataSaveItem {
	const SceChar8 *dataPath;
	const void *buf;
	SceSize bufSize;
	SceChar8 padding[4];
	SceOff offset;
	SceAppMgrSaveDataDataSaveMode mode;
	SceChar8 reserved[36];
} SceAppMgrSaveDataDataSaveItem;

typedef struct SceAppMgrDrmAddcontId {
	SceChar8 data[SCE_APPMGR_NP_DRM_ADDCONT_ID_SIZE];
	SceChar8 padding[3];
} SceAppMgrDrmAddcontId;

typedef struct SceAppMgrDrmAddcontParam {
	SceSize size;
	SceAppMgrDrmAddcontId dirName;
	SceAppMgrMountPoint mountPoint;
} SceAppMgrDrmAddcontParam;

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif // _VDSUITE_COMMON_APPMGR_H

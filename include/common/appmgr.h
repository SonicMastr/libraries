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

#define SCE_APPMGR_NP_DRM_ADDCONT_ID_SIZE 17

typedef struct SceAppMgrMountPoint {
	SceChar8 data[SCE_APPMGR_MOUNTPOINT_DATA_MAXSIZE];
} SceAppMgrMountPoint;

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

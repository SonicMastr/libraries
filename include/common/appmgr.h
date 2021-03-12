/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_COMMON_APPMGR_H
#define _VDSUITE_COMMON_APPMGR_H

#include_next <appmgr.h>

#include <apputil.h>

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif

/*J 定数 --------------------------------------------------------------------------------- */
/*E Constants ---------------------------------------------------------------------------- */

/*J エラー番号 */
/*E Error code */
#define SCE_APPMGR_ERROR_NOSYS				(-2139086817) /* 0x8080201F */

/*J 構造体 -------------------------------------------------------------------------------- */
/*E Structures ---------------------------------------------------------------------------- */

typedef struct SceAppMgrDrmAddcontParam {
	SceSize size;
	SceAppUtilDrmAddcontId dirName;
	SceAppUtilMountPoint mountPoint;
} SceAppMgrDrmAddcontParam;

/*J 関数 -------------------------------------------------------------------------------- */
/*E Functions --------------------------------------------------------------------------- */

SceInt32 sceAppMgrDrmOpen(const SceAppMgrDrmAddcontParam *pParam);

SceInt32 sceAppMgrDrmClose(const SceAppMgrDrmAddcontParam *pParam);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif // _VDSUITE_COMMON_APPMGR_H

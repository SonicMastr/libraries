/*
	Vita Development Suite Libraries
*/

#ifndef _PSP2_KERNEL_APPMGR_H_
#define _PSP2_KERNEL_APPMGR_H_

#include_next <appmgr.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief       Kill a process.
 * @param[in]   pid The process to kill.
 * @return      Zero on success, else < 0.
 */
int sceAppMgrKillProcess(SceUID pid);

typedef struct
{
    SceSize size;
    unsigned int unk_4; //<! set to 0x80000000 to break on launch
    unsigned int unk_8;
    unsigned int unk_C;
    unsigned int unk_10;
    unsigned int unk_14;
    unsigned int unk_18;
    unsigned int unk_1C;
    unsigned int unk_20;
    unsigned int unk_24;
    unsigned int unk_28;
    unsigned int unk_2C;
    unsigned int unk_30;
} SceAppMgrLaunchParam;

/**
 * @brief       Launch an application for debugging
 *
 * @param[in] path  Path to the executable to load
 * @param[in] args  Arguments to pass to the executable and to configure appmgr
 * @param[in] arg_size  The size of the args passed in
 * @param[in] type  Set to 0x80000000 for debugging launch
 * @param[in] param pointer to launch params
 * @param unk unknown, set to nullptr
 *
 * @return   pid on success, else < 0.
 */
int sceAppMgrLaunchAppByPath(const char *path, const char *args, SceSize arg_size, unsigned int type, const SceAppMgrLaunchParam *param, void *unk);

SceInt32 sceAppMgrDrmOpen(const SceAppMgrDrmAddcontParam *pParam);

SceInt32 sceAppMgrDrmClose(const SceAppMgrDrmAddcontParam *pParam);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_APPMGR_H_ */

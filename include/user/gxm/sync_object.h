#ifndef _DOLCESDK_PSP2_GXM_SYNC_OBJECT_INTERNAL_H_
#define _DOLCESDK_PSP2_GXM_SYNC_OBJECT_INTERNAL_H_

/** @file
*/

#include <psp2/gxm/sync_object.h>

#ifdef	__cplusplus
extern "C" {
#endif	// def __cplusplus

/** Creates a shared sync object.  Currently sync objects are used purely to
	synchronize rendering with display operations in the display queue.

	@param[in]	key				The key for the shared sync object.
	@param[out]	syncObject		A pointer to storage for a sync object pointer.

	@retval
	SCE_OK		The operation was completed successfully.
	@retval
	SCE_GXM_ERROR_UNINITIALIZED The operation failed as libgxm is not initialized, or not initialized to allow shared sync objects.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed as the <c><i>key</i></c> parameter was 0.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed as the sync object pointer was <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_DRIVER The operation failed due to a driver error.

	@ingroup render
*/
SceGxmErrorCode sceGxmSyncObjectCreateShared(uint32_t key, SceGxmSyncObject **syncObject);

/** Deletes a shared sync object.

	@param[in]	key				The key for the shared sync object.

	@retval
	SCE_OK		The operation was completed successfully.
	@retval
	SCE_GXM_ERROR_UNINITIALIZED The operation failed as libgxm is not initialized.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed as the <c><i>key</i></c> parameter was 0.
	@retval
	SCE_GXM_ERROR_DRIVER The operation failed due to a driver error.

	@ingroup render
*/
SceGxmErrorCode sceGxmSyncObjectDeleteShared(uint32_t key);

/** Opens a shared sync object.

	@param[in]	key				The key for the shared sync object.
	@param[out]	syncObject		A pointer to storage for a sync object pointer.

	@retval
	SCE_OK		The operation was completed successfully.
	@retval
	SCE_GXM_ERROR_UNINITIALIZED The operation failed as libgxm is not initialized, or not initialized to allow shared sync objects.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed as the <c><i>key</i></c> parameter was 0.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed as the sync object pointer was <c>NULL</c>, or the <c><i>key</i></c> parameter was invalid.
	@retval
	SCE_GXM_ERROR_DRIVER The operation failed due to a driver error.

	@ingroup render
*/
SceGxmErrorCode sceGxmSyncObjectOpenShared(uint32_t key, SceGxmSyncObject **syncObject);

/** Closes a shared sync object.

	@param[in]		key			The key for the shared sync object.
	@param[in,out]	syncObject	A sync object pointer.

	@retval
	SCE_OK		The operation was completed successfully.
	@retval
	SCE_GXM_ERROR_UNINITIALIZED The operation failed as libgxm is not initialized.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed as the <c><i>key</i></c> parameter was 0.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed as the sync object pointer was <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_DRIVER The operation failed due to a driver error.

	@ingroup render
*/
SceGxmErrorCode sceGxmSyncObjectCloseShared(uint32_t key, SceGxmSyncObject *syncObject);

#ifdef	__cplusplus
}
#endif	// def __cplusplus

#endif /* _DOLCESDK_PSP2_GXM_SYNC_OBJECT_INTERNAL_H_ */

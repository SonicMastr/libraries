#ifndef _DOLCESDK_PSP2_GXM_INIT_INTERNAL_H_
#define _DOLCESDK_PSP2_GXM_INIT_INTERNAL_H_

/** @file
*/

#include <psp2/gxm/init.h>

#ifdef	__cplusplus
extern "C" {
#endif	// def __cplusplus

/** Initializes the libgxm library for shared sync objects.

	Internally this function will prepare this process for rendering, creating
	the parameter buffer with the given size.

	This function must be called before any other libgxm object is created, such
	as a context, or sync object.

	@param[in]	params					A pointer to a populated SceGxmInitializeParams structure.

	@retval
	SCE_OK	The operation completed successfully.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER		The SceGxmInitializeParams pointer was <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE			One or more parameters were invalid.
	@retval
	SCE_GXM_ERROR_ALREADY_INITIALIZED	The operation failed because libgxm is already initialized.
	@retval
	SCE_GXM_ERROR_OUT_OF_MEMORY			There was no memory to perform the operation.
	@retval
	SCE_GXM_ERROR_DRIVER				The operation failed due to a driver error.

	@ingroup render
*/
SceGxmErrorCode sceGxmInitializeInternal(const SceGxmInitializeParams *params);

/** Checks if the libgxm library was initialized for shared sync objects.

	@return
	Returns <c>true</c> if the libgxm library was initialized for shared sync objects; otherwise <c>false</c> is returned.

	@ingroup render
*/
bool sceGxmIsInitializedInternal(void);

#ifdef	__cplusplus
}
#endif	// def __cplusplus

#endif /* _DOLCESDK_PSP2_GXM_INIT_INTERNAL_H_ */

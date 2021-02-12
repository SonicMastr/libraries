/*
	Vita Development Suite Libraries
*/

#ifndef _DOLCESDK_PSP2_GXM_RENDER_TARGET_INTERNAL_H_
#define _DOLCESDK_PSP2_GXM_RENDER_TARGET_INTERNAL_H_

/** @file
*/

#include_next <gxm/render_target.h>

#ifdef	__cplusplus
extern "C" {
#endif	// def __cplusplus

/** Computes the driver memory size needed for the given set of render
	target parameters.  The memory will be used for render target GPU data structures should
	be allocated as an uncached LPDDR memblock using <c>sceKernelAllocMemBlock()</c>.

	@param[in]	params			A pointer to render target parameters.
	@param[out]	driverMemSize	A pointer to storage for the driver memory size.

	@retval
	SCE_OK The operation was completed successfully.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed due to an invalid parameter value.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed due to a <c>NULL</c> pointer.

	@ingroup render
*/
SceGxmErrorCode sceGxmGetRenderTargetMemSizeInternal(
	const SceGxmRenderTargetParams *params,
	uint32_t* driverMemSize);

/** Creates a render target object.  A render target defines the layout for tiled
	rendering and is needed to start a scene and draw geometry.  Render targets
	should ideally be created at load time, since creating them requires resources
	from the OS.

	Once the render target is no longer needed, call #sceGxmDestroyRenderTarget()
	to destroy it.

	@param[in]	params			The creation parameters for the render target.
	@param[out]	renderTarget	A pointer to storage for the render target pointer.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_UNINITIALIZED The operation failed as libgxm is not initialized.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed due to an invalid parameter value.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed due to a <c>NULL</c> pointer.
	@retval
	SCE_GXM_ERROR_OUT_OF_RENDER_TARGETS The operation failed because the maximum number
	of render targets have already been created.
	@retval
	SCE_GXM_ERROR_DRIVER The operation failed due to a driver error.

	@ingroup render
*/
SceGxmErrorCode sceGxmCreateRenderTargetInternal(
	const SceGxmRenderTargetParams *params,
	SceGxmRenderTarget **renderTarget);

#ifdef	__cplusplus
}
#endif	// def __cplusplus

#endif /* _DOLCESDK_PSP2_GXM_RENDER_TARGET_INTERNAL_H_ */

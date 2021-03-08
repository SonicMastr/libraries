/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_USER_GXM_SHADER_PATCHER_H
#define _VDSUITE_USER_GXM_SHADER_PATCHER_H

/** @file
*/

#include_next <gxm/shader_patcher.h>

#ifdef	__cplusplus
extern "C" {
#endif	// def __cplusplus

/** Finds or creates a final fragment program.

	The fragment program is constructed by appending the shader compiler output
	with output register conversion and blending code.

	When this program is no longer needed, it should be released by calling
	#sceGxmShaderPatcherReleaseFragmentProgram().  The caller is responsible for ensuring that
	the GPU is no longer using this program before it is released.

	Blending/masking is only supported for the output register formats
	#SCE_GXM_OUTPUT_REGISTER_FORMAT_UCHAR4 or #SCE_GXM_OUTPUT_REGISTER_FORMAT_HALF4.
	If the <c><i>blendInfo</i></c> structure has an active blend or non-trivial mask when using
	unsupported output register format, the error code #SCE_GXM_ERROR_UNSUPPORTED
	will be returned.

	The parameter <c><i>vertexProgram</i></c> is only required to remap texture coordinates.  If all
	vertex programs that will be used with this fragment program write a contiguous range of
	texture coordinates starting at <c>TEXCOORD0</c> (or do not write texture coordinates), then the
	<c><i>vertexProgram</i></c> parameter may be <c>NULL</c>.  Any vertex program that uses texture coordinates
	that either start at a non-zero binding (such as <c>TEXCOORD1</c>) or form a non-contiguous range
	must be explicitly linked by passing the program as the <c><i>vertexProgram</i></c> parameter.

	The parameter <c><i>texcoordMap</i></c> can provide an explicit remapping of texture coordinates.

	@param[in,out]	shaderPatcher			A pointer to the shader patcher.
	@param[in]		programId				The ID for a program registered with this shader patcher.
	@param[in]		outputFormat			The format for the fragment program <c>COLOR0</c> output.
	@param[in]		multisampleMode			The multisample mode.
	@param[in]		blendInfo				A pointer to the blend info structure or <c>NULL</c>. This
											structure is copied by the function and therefore does not need to
											persist after the call.
	@param[in]		vertexProgram			A pointer to the vertex program or <c>NULL</c>. This
											structure does not need to persist after the call.
	@param[in]		texcoordMap				A pointer to explicit remapping of texture coordinates or <c>NULL</c>.
	@param[out]		fragmentProgram			A pointer to storage for a fragment program pointer.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_UNSUPPORTED Blending or masking is enabled for an unsupported
	output register format.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because one or more of the pointers supplied was <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed due to an invalid input parameter.
	@retval
	SCE_GXM_ERROR_INVALID_ALIGNMENT The operation failed because some allocated memory did not have the required alignment.
	@retval
	SCE_GXM_ERROR_OUT_OF_HOST_MEMORY The operation failed because a host memory allocation failed.
	@retval
	SCE_GXM_ERROR_OUT_OF_FRAGMENT_USSE_MEMORY The operation failed because a fragment USSE memory allocation failed.

	@ingroup shaderpatcher
*/
SceGxmErrorCode sceGxmShaderPatcherCreateFragmentProgramInternal(
	SceGxmShaderPatcher *shaderPatcher,
	SceGxmShaderPatcherId programId,
	SceGxmOutputRegisterFormat outputFormat,
	SceGxmMultisampleMode multisampleMode,
	const SceGxmBlendInfo *blendInfo,
	const SceGxmProgram *vertexProgram,
	const uint32_t *texcoordMap,
	SceGxmFragmentProgram **fragmentProgram);

#ifdef	__cplusplus
}
#endif	// def __cplusplus

#endif /* _VDSUITE_USER_GXM_SHADER_PATCHER_H */

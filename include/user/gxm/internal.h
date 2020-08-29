#ifndef _DOLCESDK_PSP2_GXM_INTERNAL_H_
#define _DOLCESDK_PSP2_GXM_INTERNAL_H_

#include <stdbool.h>
#include <psp2/types.h>
#include <psp2/gxm/constants.h>
#include <psp2/gxm/errors.h>
#include <psp2/gxm/structs.h>

#ifdef __cplusplus
extern "C" {
#endif

SceGxmErrorCode sceGxmInternalMapVertexUsseMemory(void *base, uint32_t size, uint32_t *offset);

SceGxmErrorCode sceGxmInternalUnmapVertexUsseMemory(void *base);

SceGxmErrorCode sceGxmInternalMapFragmentUsseMemory(void *base, uint32_t size, uint32_t *offset);

SceGxmErrorCode sceGxmInternalUnmapFragmentUsseMemory(void *base);

SceGxmErrorCode sceGxmInternalGetRenderTargetMemSize(
	const SceGxmRenderTargetParams *params,
	uint32_t* driverMemSize);

SceGxmErrorCode sceGxmInternalCreateRenderTarget(
	const SceGxmRenderTargetParams *params,
	SceGxmRenderTarget **renderTarget);

SceBool sceGxmInternalIsInitialized(void);

#ifdef __cplusplus
}
#endif

#endif /* _DOLCESDK_PSP2_GXM_INTERNAL_H_ */

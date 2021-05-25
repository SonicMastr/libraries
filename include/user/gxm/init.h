/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_USER_GXM_INIT_H
#define _VDSUITE_USER_GXM_INIT_H

/** @file
*/

#include_next <gxm/init.h>

#include <gxm/context.h>
#include <gxm/structs.h>

#ifdef	__cplusplus
extern "C" {
#endif	// def __cplusplus

/** Flags for libgxm initialization.

	@ingroup render
*/
typedef enum SceGxmInitializeFlagsInternal
{
	SCE_GXM_INITIALIZE_FLAG_PB_USE_USER_MEMORY			=	0x00000001U,	///< Use uncached main memory for the parameter buffer.
	SCE_GXM_INITIALIZE_FLAG_PBDESCFLAGS_ZLS_OVERRIDE	=	0x00000002U,
	SCE_GXM_INITIALIZE_FLAG_PBDESCFLAGS_SHARED			=	0x00000004U,	///< The parameter buffer can be shared between rendering contexts.
	SCE_GXM_INITIALIZE_FLAG_DRIVER_MEM_SHARE			=	0x00000008U		///< Use shared driver memory for the parameter buffer.
} SceGxmInitializeFlagsInternal;

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

/** Gets PowerVR service device data.

	@return
	Pointer to device data.

	@ingroup render
*/
void *sceGxmGetDeviceData(void);

// Use for sceGxmSetRazorCallbacks
#define SCE_GXM_RAZOR_TRACE_CALLBACK_VERSION					0x00010005
#define SCE_GXM_RAZOR_CAPTURE_CALLBACK_VERSION					0x00010005

// Flags are written to (kuIoGpuTraceBuffer + 0x20)
#define SCE_GXM_STATE_FLAG_BEGIN_SCENE							0x10000000
#define SCE_GXM_STATE_FLAG_END_SCENE							0x11000000
#define SCE_GXM_STATE_FLAG_MID_SCENE_FLUSH						0x12000000
#define SCE_GXM_STATE_FLAG_FINISH_BEGIN							0x13000000
#define SCE_GXM_STATE_FLAG_FINISH_END							0x14000000
#define SCE_GXM_STATE_FLAG_DISPLAY_QUEUE_OP_WAIT_BEGIN			0x15000000
#define SCE_GXM_STATE_FLAG_DISPLAY_QUEUE_OP_WAIT_END			0x16000000
#define SCE_GXM_STATE_FLAG_DISPLAY_QUEUE_FINISH_OP_WAIT_BEGIN	0x17000000
#define SCE_GXM_STATE_FLAG_DISPLAY_QUEUE_FINISH_OP_WAIT_END		0x17000000
#define SCE_GXM_STATE_FLAG_TRANSFER_SUBMIT_BEGIN				0x19000000
#define SCE_GXM_STATE_FLAG_TRANSFER_SUBMIT_END					0x1A000000
#define SCE_GXM_STATE_FLAG_NOTIFICATION_WAIT_BEGIN				0x1B000000
#define SCE_GXM_STATE_FLAG_NOTIFICATION_WAIT_END				0x1C000000
#define SCE_GXM_STATE_FLAG_CONTEXT_KICK_BEGIN					0x1D000000
#define SCE_GXM_STATE_FLAG_CONTEXT_KICK_END						0x1E000000

typedef void(*SceGxmVoid_CB)(void);

typedef void(*SceGxmPadHeartbeat_CB)(const SceGxmColorSurface *displaySurface, SceGxmSyncObject *displaySyncObject);

typedef void(*SceGxmBeginScene_CB)(uint32_t debugStateFlags);

typedef void(*SceGxmDisplayQueueAddEntry_CB)(uint32_t zero);

typedef void(*SceGxmMemoryAllocMapOp_CB)(uint32_t memType, void* memBase, uint32_t offset, uint32_t size);

typedef void(*SceGxmMemoryFreeUnmapOp_CB)(uint32_t memType, void* memBase);

typedef void(*SceGxmContextKickStage1DebugMid_CB)(int contextUnk1, void* contextUnk2, int contextUnk3, void* contextUnk4);

typedef void(*SceGxmContextKickStage1DebugBegin_CB)(SceGxmContext **context);

typedef void(*SceGxmInitStage2_CB)(uint32_t paramBufferSize, uint32_t usseBufferThreshold);

typedef void(*SceGxmInitStage1_1ForTrace_CB)(uint32_t parameterBufferThresholdSize);

typedef void(*SceGxmInitStage1_2ForTrace_CB)(uint32_t parameterBufferSize, uint32_t mgmtAndPartialRenderReserveSize);

typedef void(*SceGxmContextKickStage2OKForTrace_CB)(
	SceBool vdmRingBufferHighWaterWarning,
	SceBool vertexRingBufferHighWaterWarning,
	SceBool fragmentRingBufferHighWaterWarning,
	SceBool fragmentUsseRingBufferHighWaterWarning);

typedef void(*SceGxmBeginSceneDoneForTrace_CB)(
	uint32_t vdmRingBufferSize,
	uint32_t vertexRingBufferSize,
	uint32_t fragmentRingBufferSize,
	uint32_t fragmentUsseRingBufferSize);

typedef void(*SceGxmRingBufferFillForTrace_CB)(
	uint32_t vdmRingBufferUsageSize,
	uint32_t vertexRingBufferUsageSize,
	uint32_t fragmentRingBufferUsageSize,
	uint32_t fragmentUsseRingBufferUsageSize);

typedef struct SceGxmCallbacksForCapture { //size is 0x48
	SceGxmVoid_CB initStage1;
	SceGxmVoid_CB term;
	SceGxmVoid_CB endSceneDone;
	SceGxmBeginScene_CB beginSceneDone;
	SceGxmDisplayQueueAddEntry_CB displayQueueAddEntryDone;
	SceGxmVoid_CB contextKickStage2OK;
	SceGxmVoid_CB userMarkerPushNoHUD;
	SceGxmMemoryAllocMapOp_CB memoryAllocMapOp; //Including internal allocations
	SceGxmMemoryFreeUnmapOp_CB memoryFreeUnmapOp;
	SceGxmVoid_CB commandListOp; //Called when operations on command list are performed. Return 1 to use user debug markers, 0 otherwise
	SceGxmVoid_CB contextKickStage1; //Called before SGXKickTA(). Return 1 to enable some debug calls, 0 otherwise
	SceGxmVoid_CB contextKickStage1DebugDone; //Only used if contextKickStage1() returns 1
	SceGxmVoid_CB contextKickStage2Fail;
	SceGxmContextKickStage1DebugMid_CB contextKickStage1DebugMid; //Only used if contextKickStage1() returns 1
	SceGxmContextKickStage1DebugBegin_CB contextKickStage1DebugBegin; //Only used if contextKickStage1() returns 1
	SceGxmVoid_CB addRazorGpuCaptureBuffer; //Must return 1 for this GXM call to succeed
	SceGxmVoid_CB removeRazorGpuCaptureBuffer; //Must return 1 for this GXM call to succeed
	SceGxmInitStage2_CB initStage2;
} SceGxmCallbacksForCapture;

void sceGxmSetRazorCallbacksForCapture(int callbackVersion, SceGxmCallbacksForCapture *pCallbacks);

typedef struct SceGxmCallbacksForTrace { //size is 0x48
	SceGxmInitStage1_1ForTrace_CB initStage1_1;
	SceGxmVoid_CB term;
	SceGxmInitStage1_2ForTrace_CB initStage1_2;
	SceGxmDisplayQueueAddEntry_CB displayQueueAddEntryDone;
	SceGxmPadHeartbeat_CB padHeartbeat;
	SceGxmContextKickStage2OKForTrace_CB contextKickStage2OK;
	SceGxmBeginSceneDoneForTrace_CB beginSceneDone;
	SceGxmRingBufferFillForTrace_CB ringBufferFill;
	SceGxmVoid_CB unused_cb;
	SceVoid **kuIoGpuTraceBuffer;
} SceGxmCallbacksForTrace;

void sceGxmSetRazorCallbacksForTrace(int callbackVersion, SceGxmCallbacksForTrace *pCallbacks);

#ifdef	__cplusplus
}
#endif	// def __cplusplus

#endif /* _VDSUITE_USER_GXM_INIT_H */

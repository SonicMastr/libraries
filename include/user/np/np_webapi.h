/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_USER_NP_NP_WEBAPI_H
#define _VDSUITE_USER_NP_NP_WEBAPI_H

#include_next <np/np_webapi.h>

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif  /* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

/* -----------------------------------------------
 * Initialize/Terminate
 * ----------------------------------------------- */
int32_t
sceNpWebApiIntInitialize(
	void *pMemPool,
	size_t poolSize,
	const char *pModuleName
	);

int32_t
sceNpWebApiInitializeForSceShell(
	void *pMemPool,
	size_t poolSize
	);

int32_t
sceNpWebApiIntTerminate(
	int32_t libCtxId
	);

/* -----------------------------------------------
 * Request
 * ----------------------------------------------- */
int32_t
sceNpWebApiIntCreateRequest(
	int32_t libCtxId,
	const char *pApiGroup,
	const char *pPath,
	SceNpWebApiHttpMethod method,
	const SceNpWebApiContentParameter *pContentParameter,
	const char unk[0x410],
	int64_t *pRequestId
	);

/* -----------------------------------------------
 * Memory
 * ----------------------------------------------- */
int32_t
sceNpWebApiIntGetMemoryPoolStats(
	int32_t libCtxId,
	SceNpWebApiMemoryPoolStats *pCurrentStat
	);

/* -----------------------------------------------
 * Handle
 * ----------------------------------------------- */
int32_t
sceNpWebApiIntCreateHandle(
	int32_t libCtxId
	);

int32_t
sceNpWebApiIntDeleteHandle(
	int32_t libCtxId,
	int32_t handleId
	);

int32_t
sceNpWebApiIntAbortHandle(
	int32_t libCtxId,
	int32_t handleId
	);

/* -----------------------------------------------
 * Multi Part
 * ----------------------------------------------- */
int32_t
sceNpWebApiIntCreateMultipartRequest(
	int32_t libCtxId,
	const char *pApiGroup,
	const char *pPath,
	SceNpWebApiHttpMethod method,
	int64_t *pRequestId
	);

/* -----------------------------------------------
 * Push Event
 * ----------------------------------------------- */
int32_t
sceNpWebApiIntCreatePushEventFilter(
	int32_t libCtxId,
	const SceNpWebApiPushEventDataType *pDataType,
	size_t dataTypeNum
	);

int32_t
sceNpWebApiIntDeletePushEventFilter(
	int32_t libCtxId,
	int32_t filterId
	);

int32_t
sceNpWebApiIntRegisterPushEventCallback(
	int32_t libCtxId,
	int32_t filterId,
	SceNpWebApiPushEventCallback cbFunc,
	void *pUserArg
	);

int32_t
sceNpWebApiIntUnregisterPushEventCallback(
	int32_t libCtxId,
	int32_t callbackId
	);

/* -----------------------------------------------
 * Service Push Event
 * ----------------------------------------------- */
int32_t
sceNpWebApiIntCreateServicePushEventFilter(
	int32_t libCtxId,
	int32_t handleId,
	const char *pNpServiceName,
	SceNpServiceLabel npServiceLabel,
	const SceNpWebApiPushEventDataType *pDataType,
	size_t dataTypeNum
	);

int32_t
sceNpWebApiIntDeleteServicePushEventFilter(
	int32_t libCtxId,
	int32_t filterId
	);

int32_t
sceNpWebApiIntRegisterServicePushEventCallback(
	int32_t libCtxId,
	int32_t filterId,
	SceNpWebApiServicePushEventCallback cbFunc,
	void *pUserArg
	);

int32_t
sceNpWebApiIntUnregisterServicePushEventCallback(
	int32_t libCtxId,
	int32_t callbackId
	);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif  /* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

#endif /* _VDSUITE_USER_NP_NP_WEBAPI_H */

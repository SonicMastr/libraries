/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_COMMON_KERNEL_THREADMGR_H
#define _VDSUITE_COMMON_KERNEL_THREADMGR_H

#include_next <kernel/threadmgr.h>

SCE_CDECL_BEGIN

typedef struct _SceKernelThreadOptParamInternal {
	/** Size of the ::SceKernelThreadOptParam structure. */
	SceSize               size;
	SceUInt32             attr;
	SceKernelMemBlockType memType1;
	SceKernelMemBlockType memType2;
	SceInt32              unk0x10;
	SceInt32              unk0x14;
	SceInt32              unk0x1C;
} SceKernelThreadOptParamInternal;

typedef enum _SceKernelTLS {
	SCE_THREAD_TLS_UNK_0,
	SCE_THREAD_TLS_ID,
	SCE_THREAD_TLS_STACK_START_ADDRESS,
	SCE_THREAD_TLS_STACK_END_ADDRESS,
	SCE_THREAD_TLS_VFP_EXCEPTION,
	SCE_THREAD_TLS_LWMUTEX_STATUS,
	SCE_THREAD_TLS_UNK_6,
	SCE_THREAD_TLS_UNK_7,
	SCE_THREAD_TLS_PRIORITY,
	SCE_THREAD_TLS_AFFINITY,
} SceKernelTLS;

/**
 * @brief sceKernelGetThreadTLSAddr gets an address to a 4 bytes area of TLS memory for the specified thread
 * @param thid - The UID of the thread to access TLS
 * @param key - the TLS keyslot index
 * @return pointer to TLS memory
 */
void *sceKernelGetThreadTLSAddr(SceUID thid, SceKernelTLS key);

/** @name	システム時間
 */
/*@{*/

/**
 * @brief システム時間の取得
 *
 * システム稼働開始時からの経過時間(システム時間)を取得します。
 * システム時間はシステムサスペンド期間中は停止しています。
 * システム時間はマイクロ秒単位です。
 *
 * @param[out]	pClock	システム時間を受け取る構造体変数へのポインタを指定します。
 * @retval		SCE_OK	成功
 * @retval		負の値	エラーコード
 */
SceInt32	sceKernelGetSystemTime(SceKernelSysClock *pClock);

/**
 * @brief システム時間を64bit幅で取得
 *
 * システム稼働開始時からの経過時間(システム時間)を取得します。
 * システム時間はシステムサスペンド期間中は停止しています。
 * システム時間はマイクロ秒単位です。
 *
 * sceKernelGetSystemTime()との違いは、結果を直接SceUInt64値で返すことです。
 *
 * @return	システム時間
 */
SceUInt64	sceKernelGetSystemTimeWide(void);

/**
 * @brief システム時間の下位32bit部分の取得
 *
 * システム稼働開始時からの経過時間(システム時間)の下位32bitを取得します。
 * システム時間はシステムサスペンド期間中は停止しています。
 * システム時間はマイクロ秒単位です。
 *
 * @return	システム時間の下位32ビット
 */
SceUInt32	sceKernelGetSystemTimeLow(void);

/*@}*//*J システム時間 */

SCE_CDECL_END

#endif

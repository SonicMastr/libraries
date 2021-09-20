/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_COMMON_KERNEL_THREADMGR_H
#define _VDSUITE_COMMON_KERNEL_THREADMGR_H

#include_next <kernel/threadmgr.h>

SCE_CDECL_BEGIN

#define SCE_KERNEL_THREAD_ATTR_NOTIFY_EXCEPTION							0x04000000U

#define SCE_KERNEL_THREAD_OPT_ATTR_STACK_MEMBLOCK_TYPE_1_MASK			0x00000001U
#define SCE_KERNEL_THREAD_OPT_ATTR_STACK_MEMBLOCK_TYPE_2_MASK			0x00000002U
#define SCE_KERNEL_THREAD_OPT_ATTR_TLS_MEMBLOCK_TYPE_MASK				0x00000004U
#define SCE_KERNEL_THREAD_OPT_ATTR_STACK_MEMBLOCK_UID_MASK				0x00000008U
#define SCE_KERNEL_THREAD_OPT_ATTR_NOTIFY_EXCP_MASK						0x00070000U

// For SceKernelThreadOptParamInternal.notifyExcpMask
#define SCE_KERNEL_EXCEPTION_TYPE_DABT_PAGE_FAULT						0x00000001U
#define SCE_KERNEL_EXCEPTION_TYPE_PABT_PAGE_FAULT						0x00000100U

typedef struct _SceKernelThreadOptParamInternal {
	SceSize						size;
    SceUInt32					attr;
    SceKernelMemBlockType		stackMemType1;
    SceKernelMemBlockType		stackMemType2;
    SceKernelMemBlockType		tlsMemblockType;
    SceUID						stackMemblockUID;
    SceUInt32					notifyExcpMask;
} SceKernelThreadOptParamInternal;

typedef struct SceKernelThreadCpuRegisterInfo{
	SceSize		size;
	SceUInt32	cpsr;
	SceUInt32	reg[16];
	SceUInt32	tpidrurw;
	SceUInt32	teehbr;
	SceUInt32	sb;
	SceUInt32	st;
} SceKernelThreadCpuRegisterInfo;

typedef struct SceKernelThreadVfpRegisterInfo {
	SceSize		size;
	SceUInt32	fpscr;
	struct {
		SceUInt32	word[4];
	} reg[16];
} SceKernelThreadVfpRegisterInfo;

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
 * @brief sceKernelGetTLSAddr get pointer to TLS key area for current thread
 * @param key - the TLS keyslot index
 * @return pointer to TLS key value
 */
void *sceKernelGetTLSAddr(SceKernelTLS key);

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

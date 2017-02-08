#ifndef _PSP2_USBD_H_
#define _PSP2_USBD_H_

#include <psp2/kernel/threadmgr.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SCE_USBD_ERROR_ACCESS 0x80240003
#define SCE_USBD_ERROR_BUSY 0x80240006
#define SCE_USBD_ERROR_FATAL 0x802400ff
#define SCE_USBD_ERROR_INTERRUPTED 0x8024000a
#define SCE_USBD_ERROR_INVALID_ARG 0x80240002
#define SCE_USBD_ERROR_IO 0x80240001
#define SCE_USBD_ERROR_NO_DEVICE 0x80240004
#define SCE_USBD_ERROR_NO_MEM 0x8024000b
#define SCE_USBD_ERROR_NOT_FOUND 0x80240005
#define SCE_USBD_ERROR_NOT_SUPPORTED 0x8024000c
#define SCE_USBD_ERROR_OVERFLOW 0x80240008
#define SCE_USBD_ERROR_PIPE 0x80240009
#define SCE_USBD_ERROR_TIMEOUT 0x80240007

typedef struct SceUsbdDeviceInfo {
	unsigned int unk0;
	unsigned int unk1;
	unsigned int unk2;
} SceUsbdDeviceInfo; /* size = 0xC */

typedef struct SceUsbdDeviceAddress {
	unsigned int unk0;
	unsigned short unk1;
} SceUsbdDeviceAddress; /* size = 0x6 */

int sceUsbdInit(SceUID *uid);
int sceUsbdEnd(SceUID uid);

int sceUsbdRegisterCallback(SceUID cbid, int);
int sceUsbdUnregisterCallback(SceUID cbid);

int sceUsbdResetDevice();
int sceUsbdAttach();

int sceUsbdOpenDefaultPipe();
int sceUsbdOpenPipe();
int sceUsbdClosePipe();

int sceUsbdGetDeviceList(SceUID uid, unsigned int num, SceUsbdDeviceInfo *info);
int sceUsbdGetDescriptor(SceUID uid, unsigned int descriptor_id, void *descriptor, unsigned int size);
int sceUsbdGetDescriptorSize(SceUID uid, unsigned int descriptor_id);
int sceUsbdGetDeviceAddress(SceUID uid, int, SceUsbdDeviceAddress *addr);
int sceUsbdGetDeviceSpeed();
int sceUsbdGetTransferStatus();
int sceUsbdGetIsochTransferStatus();

int sceUsbdTransferData();
int sceUsbdIsochTransferData();
int sceUsbdReceiveEvent();

int sceUsbdRegisterLdd();
int sceUsbdUnregisterLdd();
int sceUsbdRegisterCompositeLdd();
int sceUsbdAttachCompositeLdd();

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_USBD_H_ */

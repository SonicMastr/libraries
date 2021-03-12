/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_USER_USBD_H
#define _VDSUITE_USER_USBD_H

#include <scetypes.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceUsbdErrorCode {
	SCE_USBD_ERROR_IO            = (int)0x80240001,
	SCE_USBD_ERROR_INVALID_ARG   = (int)0x80240002,
	SCE_USBD_ERROR_ACCESS        = (int)0x80240003,
	SCE_USBD_ERROR_NO_DEVICE     = (int)0x80240004,
	SCE_USBD_ERROR_NOT_FOUND     = (int)0x80240005,
	SCE_USBD_ERROR_BUSY          = (int)0x80240006,
	SCE_USBD_ERROR_TIMEOUT       = (int)0x80240007,
	SCE_USBD_ERROR_OVERFLOW      = (int)0x80240008,
	SCE_USBD_ERROR_PIPE          = (int)0x80240009,
	SCE_USBD_ERROR_INTERRUPTED   = (int)0x8024000A,
	SCE_USBD_ERROR_NO_MEM        = (int)0x8024000B,
	SCE_USBD_ERROR_NOT_SUPPORTED = (int)0x8024000C,
	SCE_USBD_ERROR_FATAL         = (int)0x802400FF
} SceUsbdErrorCode;

typedef struct SceUsbdDeviceInfo {
	unsigned int unk0;
	unsigned int device_id;
	unsigned int unk2;
} SceUsbdDeviceInfo; /* size = 0xC */

typedef struct SceUsbdDeviceAddress {
	unsigned int unk0;
	unsigned short unk1;
} SceUsbdDeviceAddress; /* size = 0x6 */

typedef struct SceUsbdTransferData {
	unsigned int pipe;
	const void *buff1;
	unsigned int size1;
	void *buff2;
	unsigned int size2;
} SceUsbdTransferData; /* size = 0x14 */

typedef struct SceUsbdReceiveEvent {
	unsigned int unk0;
	unsigned int unk1;
	unsigned int unk2;
	unsigned int unk3;
	unsigned int unk4;
	unsigned int unk5;
	unsigned int transfer_id;
} SceUsbdReceiveEvent; /* size = 0x1C */

int sceUsbdInitForUser(SceUID *uid);
int sceUsbdEndForUser(SceUID uid);

int sceUsbdRegisterCallbackForUser(SceUID cbid, int);
int sceUsbdUnregisterCallbackForUser(SceUID cbid);

int sceUsbdResetDeviceForUser(SceUID uid, unsigned int device_id);
int sceUsbdAttachForUser(SceUID uid, int, int, int);

int sceUsbdGetDeviceListForUser(SceUID uid, unsigned int num, SceUsbdDeviceInfo *info);
int sceUsbdGetDescriptorForUser(SceUID uid, unsigned int device_id, unsigned char *descriptor, unsigned int size);
int sceUsbdGetDescriptorSizeForUser(SceUID uid, unsigned int device_id);
int sceUsbdGetDeviceLocationForUser(SceUID uid, unsigned int device_id, SceUsbdDeviceAddress *addr);
int sceUsbdGetDeviceSpeedForUser(SceUID uid, unsigned int device_id, unsigned int *speed);
int sceUsbdGetTransferStatusForUser(SceUID uid, unsigned char buff[0x10]);
int sceUsbdGetIsochTransferStatusForUser(SceUID uid, unsigned char buff[0x10]);

int sceUsbdOpenDefaultPipeForUser(SceUID uid, unsigned int device_id);
int sceUsbdOpenPipeForUser(SceUID uid, unsigned char unk[0x18]);
int sceUsbdClosePipeForUserForUser(SceUID uid, unsigned int device_id);

int sceUsbdTransferDataForUser(SceUID uid, SceUsbdTransferData *data);
int sceUsbdIsochTransferDataForUser(SceUID uid, int unk, unsigned char buff[0x28]);
int sceUsbdReceiveEventForUser(SceUID uid, SceUsbdReceiveEvent *event);

int sceUsbdRegisterLddForUser(SceUID uid, const char str[0x100]);
int sceUsbdUnregisterLddForUser(SceUID uid, const char str[0x100]);
int sceUsbdRegisterCompositeLddForUser(SceUID uid, const char str[0x100]);
int sceUsbdAttachCompositeLddForUser(SceUID, unsigned char unk[0x14]);

#ifdef __cplusplus
}
#endif

#endif /* _VDSUITE_USER_USBD_H */

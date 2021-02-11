#ifndef _PSP2_KERNEL_USBD_H_
#define _PSP2_KERNEL_USBD_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceUsbdErrorCode {
	SCE_USBD_ERROR_IO             = (int)0x80240001,
	SCE_USBD_ERROR_INVALID_ARG    = (int)0x80240002,
	SCE_USBD_ERROR_ACCESS         = (int)0x80240003,
	SCE_USBD_ERROR_NO_DEVICE      = (int)0x80240004,
	SCE_USBD_ERROR_NOT_FOUND      = (int)0x80240005,
	SCE_USBD_ERROR_BUSY           = (int)0x80240006,
	SCE_USBD_ERROR_TIMEOUT        = (int)0x80240007,
	SCE_USBD_ERROR_OVERFLOW       = (int)0x80240008,
	SCE_USBD_ERROR_PIPE           = (int)0x80240009,
	SCE_USBD_ERROR_INTERRUPTED    = (int)0x8024000A,
	SCE_USBD_ERROR_NO_MEM         = (int)0x8024000B,
	SCE_USBD_ERROR_NOT_SUPPORTED  = (int)0x8024000C,
	SCE_USBD_ERROR_FATAL          = (int)0x802400FF
} SceUsbdErrorCode;

typedef struct SceUsbdDeviceDescriptor {
	unsigned char  bLength;
	unsigned char  bDescriptorType;
	unsigned short bcdUSB;
	unsigned char  bDeviceClass;
	unsigned char  bDeviceSubClass;
	unsigned char  bDeviceProtocol;
	unsigned char  bMaxPacketSize0;
	unsigned short idVendor;
	unsigned short idProduct;
	unsigned short bcdDevice;
	unsigned char  iManufacturer;
	unsigned char  iProduct;
	unsigned char  iSerialNumber;
	unsigned char  bNumConfigurations;
} SceUsbdDeviceDescriptor;

typedef struct SceUsbdEndpointDescriptor {
	unsigned char  bLength;
	unsigned char  bDescriptorType;
	unsigned char  bEndpointAddress;
	unsigned char  bmAttributes;
	unsigned short wMaxPacketSize;
	unsigned char  bInterval;
	unsigned char *extra;             //!< Extra descriptors
	int extraLength;
} SceUsbdEndpointDescriptor;

typedef struct SceUsbdDeviceAddress {
	unsigned int   unk0;
	unsigned short unk1;
} SceUsbdDeviceAddress;

typedef struct SceUsbdDriver {
	const char *name;
	int (*probe)(int device_id);
	int (*attach)(int device_id);
	int (*detach)(int device_id);
} SceUsbdDriver;

typedef struct SceUsbdControlTransferRequest {
	unsigned char bmRequestType;
	unsigned char bRequest;
	unsigned short wValue;
	unsigned short wIndex;
	unsigned short wLength;
} SceUsbdControlTransferRequest;

int sceUsbdRegisterDriver(const SceUsbdDriver *driver);
int sceUsbdRegisterCompositeLdd(const SceUsbdDriver *driver);
int sceUsbdUnregisterDriver(const SceUsbdDriver *driver);

void *sceUsbdGetDescriptor(int device_id, void *prevDescriptor, unsigned char bDescriptorType);

// endpoint = NULL to open the default control endpoint
int sceUsbdOpenEndpoint(int device_id, SceUsbdEndpointDescriptor *endpoint);
int sceUsbdCloseEndpoint(int endpoint_id);

int sceUsbdControlTransfer(int endpoint_id,
	const SceUsbdControlTransferRequest *req,
	unsigned char *buffer,
	int (*cb)(int, int, int),
	void *user_data);

int sceUsbdInterruptTransfer(int endpoint_id,
	unsigned char *buffer,
	unsigned int length,
	int (*cb)(int, int, int),
	void *user_data);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_USBD_H_ */

/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_KERNEL_LOWIO_GPIO_H
#define _VDSUITE_KERNEL_LOWIO_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceGpioErrorCode {
	SCE_GPIO_ERROR_INVALID_BUS	= (int)0x803F0100,
	SCE_GPIO_ERROR_INVALID_PORT	= (int)0x803F0101,
	SCE_GPIO_ERROR_INVALID_MODE	= (int)0x803F0102
} SceGpioErrorCode;

typedef enum SceGpioPortMasks {
	SCE_GPIO_PORT_MASK_LED_GAMECARD		= 1 << 6,
	SCE_GPIO_PORT_MASK_LED_PS_BUTTON	= 1 << 7
} SceGpioPortMasks;

typedef enum SceGpioPortMode {
	SCE_GPIO_PORT_MODE_OUTPUT	= 0,
	SCE_GPIO_PORT_MODE_INPUT	= 1
} SceGpioPortMode;

int sceGpioPortRead(int bus, int port);
int sceGpioPortSet(int bus, int port);
int sceGpioPortClear(int bus, int port);
int sceGpioPortReset(int bus, int port);
int sceGpioSetPortMode(int bus, int port, int mode);
int sceGpioGetPortMode(int bus, int port);
int sceGpioSetIntrMode(int bus, int port, int intr_mode);
int sceGpioGetIntrMode(int bus, int port);
int sceGpioAcquireIntr(int bus, int port);
int sceGpioQueryIntr(int bus, int port);

#ifdef __cplusplus
}
#endif

#endif /* _VDSUITE_KERNEL_LOWIO_GPIO_H */


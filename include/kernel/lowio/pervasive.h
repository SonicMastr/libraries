/*
	Vita Development Suite Libraries
*/

#ifndef _PSP2_KERN_LOWIO_PERVASIVE_H_
#define _PSP2_KERN_LOWIO_PERVASIVE_H_

#ifdef __cplusplus
extern "C" {
#endif

int scePervasiveUartClockDisable(int port);
int scePervasiveUartResetEnable(int port);
int scePervasiveUartResetDisable(int port);
int scePervasiveUartClockEnable(int port);
int scePervasiveUartSetBaudrate(int port, unsigned int baudrate);

int scePervasiveGpioResetEnable(void);
int scePervasiveGpioResetDisable(void);
int scePervasiveGpioClockEnable(void);
int scePervasiveGpioClockDisable(void);

int scePervasiveSpiResetEnable(int port);
int scePervasiveSpiResetDisable(int port);
int scePervasiveSpiClockDisable(int port);
int scePervasiveSpiClockEnable(int port);

int scePervasiveDsiResetEnable(int port, unsigned int mask);
int scePervasiveDsiResetDisable(int port, unsigned int mask);
int scePervasiveDsiClockEnable(int port, unsigned int mask);
int scePervasiveDsiClockDisable(int port, unsigned int mask);
int scePervasiveDsiSetPixelClock(int port, int pixelclock);

int scePervasiveMsifResetEnable(void);
int scePervasiveMsifResetDisable(void);
int scePervasiveMsifClockEnable(void);
int scePervasiveMsifClockDisable(void);
int scePervasiveMsifSetClock(unsigned int clock);

int scePervasiveRemovableMemoryGetCardInsertState(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERN_LOWIO_PERVASIVE_H_ */


#ifndef _PSP2_KERN_UART_H_
#define _PSP2_KERN_UART_H_

#include <psp2kern/types.h>

#ifdef __cplusplus
extern "C" {
#endif

int sceUartInit(int port);
int sceUartReadAvailable(int port);
int sceUartRead(int port);
int sceUartWrite(int port, char data);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERN_UART_H_ */


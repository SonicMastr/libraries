/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_KERNEL_UART_H
#define _VDSUITE_KERNEL_UART_H

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

#endif /* _VDSUITE_KERNEL_UART_H */


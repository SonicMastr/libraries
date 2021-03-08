/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_KERNEL_LOWIO_I2C_H
#define _VDSUITE_KERNEL_LOWIO_I2C_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceI2cErrorCode {
	SCE_I2C_ERROR_INVALID_BUS	= (int)0x803F0300,
	SCE_I2C_ERROR_INVALID_SIZE	= (int)0x803F0302,
	SCE_I2C_ERROR_INVALID_ADDR	= (int)0x803F0303
} SceI2cErrorCode;

typedef struct SceI2cDebugHandlers {
	unsigned int size;
	void (*write_start)(int bus, int addr, unsigned char *buffer, int size);
	void (*write_end)(int bus, int error, int result);
	void (*read_start)(int bus, int addr, unsigned char *buffer, int size);
	void (*read_end)(int bus, int error, int result);
	void (*write_read_start)(int bus, int write_addr, unsigned char *write_buffer, int write_size,
		unsigned int read_addr, unsigned char *read_buffer, int read_size);
	void (*write_read_end)(int bus, int error, int result);
} SceI2cDebugHandlers;

int sceI2cInit(int bus);
int sceI2cReset(int bus);
int sceI2cTransferRead(int bus, unsigned int addr, unsigned char *buffer, int size);
int sceI2cTransferWrite(int bus, unsigned int addr, const unsigned char *buffer, int size);
int sceI2cTransferWriteRead(int bus,
	unsigned int write_addr, unsigned char *write_buffer, int write_size,
	unsigned int read_addr, unsigned char *read_buffer, int read_size);

int sceI2cSetDebugHandlers(int bus, SceI2cDebugHandlers *debug_handlers);

#ifdef __cplusplus
}
#endif

#endif /* _VDSUITE_KERNEL_LOWIO_I2C_H */


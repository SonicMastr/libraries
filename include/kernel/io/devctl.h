#ifndef _PSP2_IO_DEVCTL_H_
#define _PSP2_IO_DEVCTL_H_

#include <psp2kern/kernel/iofilemgr.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceIoDevInfo {
	SceOff max_size;
	SceOff free_size;
	SceSize cluster_size;
	void *unk;
} SceIoDevInfo;

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_IO_DEVCTL_H_ */


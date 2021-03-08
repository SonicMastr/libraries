/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_USER_NET_NET_SYSCALLS_H
#define _VDSUITE_USER_NET_NET_SYSCALLS_H

#include <net.h>

#ifdef __cplusplus
extern "C" {
#endif

int sceNetSyscallConnect(int s, const SceNetSockaddr *name, unsigned int namelen);

#ifdef __cplusplus
}
#endif

#endif /* _VDSUITE_USER_NET_NET_SYSCALLS_H */

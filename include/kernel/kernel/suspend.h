#ifndef _PSP2_KERNEL_SUSPEND_H_
#define _PSP2_KERNEL_SUSPEND_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef int (* SceSysEventHandler)(int resume, int eventid, void *args, void *opt);

/**
 * Cancel specified idle timers to prevent entering in power save processing.
 *
 * @param[in] type - One of ::SceKernelPowerTickType
 *
 * @return 0
*/
int sceKernelPowerTick(int type);

/**
 * Register system event handler
 *
 * @param[in] name - Name of handler
 * @param[in] handler - The handler
 * @param[in] args - Handler arguments
 *
 * @return 0 on success, < 0 on error.
*/
int sceKernelRegisterSysEventHandler(const char *name, SceSysEventHandler handler, void *args);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_SUSPEND_H_ */

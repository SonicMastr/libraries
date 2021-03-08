/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_USER_MTPIF_H
#define _VDSUITE_USER_MTPIF_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Start MTP driver
 *
 * @param[in] flags - Set to 1
 *
 * @return 0 on success, < 0 on error.
*/
int sceMtpIfStartDriver(int flags);

/**
 * Stop MTP driver
 *
 * @param[in] flags - Set to 1
 *
 * @return 0 on success, < 0 on error.
*/
int sceMtpIfStopDriver(int flags);

#ifdef __cplusplus
}
#endif

#endif /* _VDSUITE_USER_MTPIF_H */

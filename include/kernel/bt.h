/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_KERNEL_BT_H
#define _VDSUITE_KERNEL_BT_H

#include <stdint.h>
#include <scetypes.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceBtErrorCode {
	SCE_BT_ERROR_REG_NOT_READY                                  	 = (int)0x802F0101,
	SCE_BT_ERROR_REG_DELETE_NO_ENTRY                            	 = (int)0x802F0102,
	SCE_BT_ERROR_REG_UPDATE_CANNOT_SAVE                         	 = (int)0x802F0103,
	SCE_BT_ERROR_REG_SET_HID_DESC_BAD_ARG                       	 = (int)0x802F0105,
	SCE_BT_ERROR_REG_SET_HID_DESC_NO_REG                        	 = (int)0x802F0106,
	SCE_BT_ERROR_REG_GET_HID_DESC_NO_REG                        	 = (int)0x802F0107,
	SCE_BT_ERROR_REG_GET_HID_DESC_TOO_SHORT                     	 = (int)0x802F0108,
	SCE_BT_ERROR_REG_DELETE_CONNECTING                          	 = (int)0x802F0109,
	SCE_BT_ERROR_REG_CANNOT_LOAD                                	 = (int)0x802F010A,
	SCE_BT_ERROR_REG_CANNOT_OPEN                                	 = (int)0x802F010B,
	SCE_BT_ERROR_REG_CANNOT_READ                                	 = (int)0x802F010C,
	SCE_BT_ERROR_REG_CANNOT_WRITE                               	 = (int)0x802F010D,
	SCE_BT_ERROR_INQUIRY_START_BUSY                             	 = (int)0x802F0201,
	SCE_BT_ERROR_CONNECT_START_NO_REG                           	 = (int)0x802F0202,
	SCE_BT_ERROR_CONNECT_START_NOT_CONNECTABLE                  	 = (int)0x802F0203,
	SCE_BT_ERROR_CONNECT_START_BUSY                             	 = (int)0x802F0204,
	SCE_BT_ERROR_DISCONNECT_START_NOT_CONNECTED                 	 = (int)0x802F0205,
	SCE_BT_ERROR_PIN_INVALID_LENGTH                             	 = (int)0x802F0206,
	SCE_BT_ERROR_USER_CONFIRM_NOT_CONNECTED                     	 = (int)0x802F0207,
	SCE_BT_ERROR_SDP_OPEN_NO_L2C                                	 = (int)0x802F0208,
	SCE_BT_ERROR_CONNECT_START_REG_FULL                         	 = (int)0x802F0209,
	SCE_BT_ERROR_CONNECT_START_CONNECTED                        	 = (int)0x802F020A,
	SCE_BT_ERROR_CONNECT_START_TOO_MANY                         	 = (int)0x802F020D,
	SCE_BT_ERROR_CONNECT_START_DELETING                         	 = (int)0x802F020E,
	SCE_BT_ERROR_AVDTP_OPEN_NO_L2C                              	 = (int)0x802F0501,
	SCE_BT_ERROR_AVDTP_CLOSE_BAD_SERV                           	 = (int)0x802F0502,
	SCE_BT_ERROR_AVDTP_CLOSE_BAD_STATE                          	 = (int)0x802F0503,
	SCE_BT_ERROR_AVDTP_START_BAD_SERV                           	 = (int)0x802F0504,
	SCE_BT_ERROR_AVDTP_START_BAD_STATE                          	 = (int)0x802F0505,
	SCE_BT_ERROR_AVDTP_STOP_BAD_SERV                            	 = (int)0x802F0506,
	SCE_BT_ERROR_AVDTP_STOP_BAD_STATE                           	 = (int)0x802F0507,
	SCE_BT_ERROR_AVDTP_SEND_BAD_STATE                           	 = (int)0x802F0508,
	SCE_BT_ERROR_AVDTP_RECONF_BAD_SERV                          	 = (int)0x802F0509,
	SCE_BT_ERROR_AVDTP_RECONF_BAD_STATE                         	 = (int)0x802F050A,
	SCE_BT_ERROR_AVCTP_OPEN_NO_L2C                              	 = (int)0x802F0601,
	SCE_BT_ERROR_AVCTP_SEND_NO_L2C                              	 = (int)0x802F0603,
	SCE_BT_ERROR_AVCTP_NOT_CONNECTED                            	 = (int)0x802F0604,
	SCE_BT_ERROR_AVCTP_SEND_BUSY                                	 = (int)0x802F0605,
	SCE_BT_ERROR_AVCTP_SEND_NO_PRESS                            	 = (int)0x802F0606,
	SCE_BT_ERROR_AVCTP_SEND_NO_RELEASE                          	 = (int)0x802F0607,
	SCE_BT_ERROR_AVCTP_READ_NO_VOLUME                           	 = (int)0x802F0608,
	SCE_BT_ERROR_AVCTP_SEND_NOT_RUBY                            	 = (int)0x802F0609,
	SCE_BT_ERROR_HID_OPEN_NO_L2C                                	 = (int)0x802F0901,
	SCE_BT_ERROR_HID_CLOSE_NO_L2C                               	 = (int)0x802F0902,
	SCE_BT_ERROR_HID_SEND_NO_L2C                                	 = (int)0x802F0903,
	SCE_BT_ERROR_HID_NOT_CONNECTED                              	 = (int)0x802F0904,
	SCE_BT_ERROR_HID_NO_CAP                                     	 = (int)0x802F0905,
	SCE_BT_ERROR_HID_INVALID_REQUEST_TYPE                       	 = (int)0x802F0906,
	SCE_BT_ERROR_HID_INVALID_BUFFER_ADDRESS                     	 = (int)0x802F0907,
	SCE_BT_ERROR_HID_INVALID_PROTOCOL                           	 = (int)0x802F0908,
	SCE_BT_ERROR_HID_INVALID_IDLE                               	 = (int)0x802F0909,
	SCE_BT_ERROR_HID_NOT_YET                                    	 = (int)0x802F090C,
	SCE_BT_ERROR_HID_INVALID_LENGTH                             	 = (int)0x802F090D,
	SCE_BT_ERROR_HID_INVALID_REPORT_ID                          	 = (int)0x802F090E,
	SCE_BT_ERROR_HID_OVERWRITE_REQ                              	 = (int)0x802F090F,
	SCE_BT_ERROR_JUMBO_UNLOCK_NOT_OWNER                         	 = (int)0x802F0B01,
	SCE_BT_ERROR_HCI_TX_OVERFLOW                                	 = (int)0x802F0B02,
	SCE_BT_ERROR_ACL_TX_BUF_OVERFLOW                            	 = (int)0x802F0B03,
	SCE_BT_ERROR_ACL_TX_CB_OVERFLOW                             	 = (int)0x802F0B04,
	SCE_BT_ERROR_TIMER_CANCEL_BAD_ID                            	 = (int)0x802F0B05,
	SCE_BT_ERROR_TIMER_CANCEL_NOT_INITIALIZED                   	 = (int)0x802F0B06,
	SCE_BT_ERROR_TIMER_SET_NOT_INITIALIZED                      	 = (int)0x802F0B07,
	SCE_BT_ERROR_TIMER_SET_NO_SPACE                             	 = (int)0x802F0B08,
	SCE_BT_ERROR_COPYIN_FAILED                                  	 = (int)0x802F0B09,
	SCE_BT_ERROR_COPYOUT_FAILED                                 	 = (int)0x802F0B0A,
	SCE_BT_ERROR_GET_NAME_NO_DEVICE                             	 = (int)0x802F0C01,
	SCE_BT_ERROR_CB_TOO_MANY                                    	 = (int)0x802F0C02,
	SCE_BT_ERROR_CB_NOT_REGISTERED                              	 = (int)0x802F0C03,
	SCE_BT_ERROR_CB_OVERFLOW                                    	 = (int)0x802F0C04,
	SCE_BT_ERROR_AUDIO_START_NOT_CONNECTED                      	 = (int)0x802F0D01,
	SCE_BT_ERROR_AUDIO_START_NO_CAP                             	 = (int)0x802F0D02,
	SCE_BT_ERROR_AUDIO_STOP_NOT_CONNECTED                       	 = (int)0x802F0D03,
	SCE_BT_ERROR_AUDIO_STOP_NO_CAP                              	 = (int)0x802F0D04,
	SCE_BT_ERROR_AUDIO_SEND_NOT_CONNECTED                       	 = (int)0x802F0D05,
	SCE_BT_ERROR_AUDIO_SEND_NOT_STARTED                         	 = (int)0x802F0D06,
	SCE_BT_ERROR_AUDIO_SEND_INVALID_LENGTH                      	 = (int)0x802F0D07,
	SCE_BT_ERROR_AUDIO_RECV_NOT_CONNECTED                       	 = (int)0x802F0D08,
	SCE_BT_ERROR_AUDIO_RECV_NOT_STARTED                         	 = (int)0x802F0D09,
	SCE_BT_ERROR_AUDIO_RECV_INVALID_LENGTH                      	 = (int)0x802F0D0A,
	SCE_BT_ERROR_AUDIO_START_INVALID_SERV                       	 = (int)0x802F0D0B,
	SCE_BT_ERROR_AUDIO_STOP_INVALID_SERV                        	 = (int)0x802F0D0C,
	SCE_BT_ERROR_AUDIO_START_SERV_FAILED                        	 = (int)0x802F0D0D,
	SCE_BT_ERROR_AUDIO_STOP_SERV_FAILED                         	 = (int)0x802F0D0E,
	SCE_BT_ERROR_AUDIO_FREQ_NOT_CONNECTED                       	 = (int)0x802F0D0F,
	SCE_BT_ERROR_AUDIO_SEND_NO_CP                               	 = (int)0x802F0D10,
	SCE_BT_ERROR_AUDIO_SEND_BAD_TYPE                            	 = (int)0x802F0D11,
	SCE_BT_ERROR_AUDIO_RECV_BAD_TYPE                            	 = (int)0x802F0D12,
	SCE_BT_ERROR_AUDIO_COMBI_NOT_FOUND                          	 = (int)0x802F0D16,
	SCE_BT_ERROR_AUDIO_SEND_NO_L2C                              	 = (int)0x802F0D17,
	SCE_BT_ERROR_AUDIO_INTERNAL_1                               	 = (int)0x802F0D18,
	SCE_BT_ERROR_AUDIO_SEND_BUSY                                	 = (int)0x802F0D19,
	SCE_BT_ERROR_AUDIO_RECV_BUSY                                	 = (int)0x802F0D1A,
	SCE_BT_ERROR_AUDIO_SEND_NO_CAP                              	 = (int)0x802F0D1B,
	SCE_BT_ERROR_AUDIO_SEND_SERV_FAILED                         	 = (int)0x802F0D1C,
	SCE_BT_ERROR_AUDIO_RECV_NO_CAP                              	 = (int)0x802F0D1D,
	SCE_BT_ERROR_AUDIO_RECV_SERV_FAILED                         	 = (int)0x802F0D1E,
	SCE_BT_ERROR_HID_RECV_NOT_CONNECTED                         	 = (int)0x802F0E01,
	SCE_BT_ERROR_HID_RECV_INVALID_LENGTH                        	 = (int)0x802F0E02,
	SCE_BT_ERROR_AVRCP_TOO_LONG_TITLE                           	 = (int)0x802F1201,
	SCE_BT_ERROR_AVRCP_INVALID_PLAY_STATUS                      	 = (int)0x802F1202,
	SCE_BT_ERROR_CONF_NOT_READY                                 	 = (int)0x802F1501,
	SCE_BT_ERROR_CONF_INVALID_VALUE                             	 = (int)0x802F1502,
	SCE_BT_ERROR_CONF_BT_INACTIVE                               	 = (int)0x802F1503,
	SCE_BT_ERROR_CONF_TIMEOUT                                   	 = (int)0x802F1504,
	SCE_BT_ERROR_CONF_CARD_NOT_FOUND                            	 = (int)0x802F1505,
	SCE_BT_ERROR_CONF_FUNCTION_NOT_FOUND                        	 = (int)0x802F1506,
	SCE_BT_ERROR_CONF_CANT_ENABLE_FUNCTION                      	 = (int)0x802F1507,
	SCE_BT_ERROR_CONF_CANT_DISABLE_FUNCTION                     	 = (int)0x802F1508,
	SCE_BT_ERROR_CONF_REGISTER_SUBINTR_HANDLER                  	 = (int)0x802F1509,
	SCE_BT_ERROR_CONF_RELEASE_SUBINTR_HANDLER                   	 = (int)0x802F150A,
	SCE_BT_ERROR_CONF_ENABLE_SUBINTR                            	 = (int)0x802F150B,
	SCE_BT_ERROR_CONF_DISABLE_SUBINTR                           	 = (int)0x802F150C,
	SCE_BT_ERROR_CONF_ON_TIMEOUT                                	 = (int)0x802F150D,
	SCE_BT_ERROR_CONF_OFF_TIMEOUT                               	 = (int)0x802F150E,
	SCE_BT_ERROR_CONF_SUSPEND_TIMEOUT                           	 = (int)0x802F150F,
	SCE_BT_ERROR_CONF_CANT_ENTER                                	 = (int)0x802F1520,
	SCE_BT_ERROR_NOTIMP                                         	 = (int)0x802F2001,
	SCE_BT_ERROR_KPROC_CREATE                                   	 = (int)0x802F2002,
	SCE_BT_ERROR_SDIO_GET_FUNCTION                              	 = (int)0x802F2003,
	SCE_BT_ERROR_SDIO_REGISTER_INTR_HANDLER                     	 = (int)0x802F2004,
	SCE_BT_ERROR_SDIO_UNREGISTER_INTR_HANDLER                   	 = (int)0x802F2005,
	SCE_BT_ERROR_SDIO_LOCK                                      	 = (int)0x802F2006,
	SCE_BT_ERROR_SDIO_UNLOCK                                    	 = (int)0x802F2007,
	SCE_BT_ERROR_SDIO_ENABLE_FUNCTION                           	 = (int)0x802F2008,
	SCE_BT_ERROR_SDIO_DISABLE_FUNCTION                          	 = (int)0x802F2009,
	SCE_BT_ERROR_SDIO_SET_BLOCK_LEN                             	 = (int)0x802F200A,
	SCE_BT_ERROR_SDIO_SET_BUS_SPEED                             	 = (int)0x802F200B,
	SCE_BT_ERROR_SDIO_READ_DIR                                  	 = (int)0x802F200C,
	SCE_BT_ERROR_SDIO_WRITE_DIR                                 	 = (int)0x802F200D,
	SCE_BT_ERROR_SDIO_READ_FIX                                  	 = (int)0x802F200E,
	SCE_BT_ERROR_SDIO_WRITE_FIX                                 	 = (int)0x802F200F,
	SCE_BT_ERROR_TSLEEP                                         	 = (int)0x802F2010,
	SCE_BT_ERROR_GET_DEBUG_INFO_INVALID_REQUEST                 	 = (int)0x802F2101,
	SCE_BT_ERROR_SET_DEBUG_INFO_INVALID_REQUEST                 	 = (int)0x802F2102,
	SCE_BT_ERROR_GET_DEBUG_INFO_INVALID_SIZE                    	 = (int)0x802F2103,
	SCE_BT_ERROR_SET_DEBUG_INFO_INVALID_SIZE                    	 = (int)0x802F2104,
	SCE_BT_ERROR_GET_DEBUG_INFO_INVALID_ARGUMENT                	 = (int)0x802F2105,
	SCE_BT_ERROR_SET_DEBUG_INFO_INVALID_ARGUMENT                	 = (int)0x802F2106,
	SCE_BT_ERROR_GET_DEBUG_INFO_INVALID_STATE                   	 = (int)0x802F2107,
	SCE_BT_ERROR_SET_DEBUG_INFO_INVALID_STATE                   	 = (int)0x802F2108,
	SCE_BT_ERROR_GET_DEBUG_INFO_NOT_CONNECTED                   	 = (int)0x802F2109,
	SCE_BT_ERROR_SET_DEBUG_INFO_NOT_CONNECTED                   	 = (int)0x802F210A,
	SCE_BT_ERROR_PIN_IS_LE                                      	 = (int)0x802F2201,
	SCE_BT_ERROR_CONNECT_START_IS_LE                            	 = (int)0x802F2202,
	SCE_BT_ERROR_AVCTP_IS_LE                                    	 = (int)0x802F2203,
	SCE_BT_ERROR_HID_IS_LE                                      	 = (int)0x802F2204,
	SCE_BT_ERROR_AUDIO_START_IS_LE                              	 = (int)0x802F2205,
	SCE_BT_ERROR_AUDIO_STOP_IS_LE                               	 = (int)0x802F2206,
	SCE_BT_ERROR_AUDIO_SEND_IS_LE                               	 = (int)0x802F2207,
	SCE_BT_ERROR_AUDIO_RECV_IS_LE                               	 = (int)0x802F2208,
	SCE_BT_ERROR_AUDIO_FREQ_IS_LE                               	 = (int)0x802F2209,
	SCE_BT_ERROR_ATT_BASE                                       	 = (int)0x802F2300,
	SCE_BT_ERROR_ATT_INVALID_HANDLE                             	 = (int)0x802F2301,
	SCE_BT_ERROR_ATT_READ_NOT_PERMITTED                         	 = (int)0x802F2302,
	SCE_BT_ERROR_ATT_WRITE_NOT_PERMITTED                        	 = (int)0x802F2303,
	SCE_BT_ERROR_ATT_INVALID_PDU                                	 = (int)0x802F2304,
	SCE_BT_ERROR_ATT_INSUFFICIENT_AUTHENTICATION                	 = (int)0x802F2305,
	SCE_BT_ERROR_ATT_REQUEST_NOT_SUPPORTED                      	 = (int)0x802F2306,
	SCE_BT_ERROR_ATT_INVALID_OFFSET                             	 = (int)0x802F2307,
	SCE_BT_ERROR_ATT_INSUFFICIENT_AUTHORIZATION                 	 = (int)0x802F2308,
	SCE_BT_ERROR_ATT_PEPARE_QUEUE_FULL                          	 = (int)0x802F2309,
	SCE_BT_ERROR_ATT_ATTRIBUTE_NOT_FOUND                        	 = (int)0x802F230A,
	SCE_BT_ERROR_ATT_ATTRIBUTE_NOT_LONG                         	 = (int)0x802F230B,
	SCE_BT_ERROR_ATT_INSUFFICIENT_ENCRYPTION_KEY_SIZE           	 = (int)0x802F230C,
	SCE_BT_ERROR_ATT_INVALID_ATTRIBUTE_VALUE_LENGTH             	 = (int)0x802F230D,
	SCE_BT_ERROR_ATT_UNLIKELY_ERROR                             	 = (int)0x802F230E,
	SCE_BT_ERROR_ATT_INSUFFICIENT_ENCRYPTION                    	 = (int)0x802F230F,
	SCE_BT_ERROR_ATT_UNSUPPORTED_GROUP_TYPE                     	 = (int)0x802F2310,
	SCE_BT_ERROR_ATT_INSUFFICIENT_RESOURCES                     	 = (int)0x802F2311,
	SCE_BT_ERROR_ATT_APPLICATION_ERROR_LO                       	 = (int)0x802F2380,
	SCE_BT_ERROR_ATT_APPLICATION_ERROR_HI                       	 = (int)0x802F23FF,
	SCE_BT_ERROR_GATT_INVALID_NO                                	 = (int)0x802F2401,
	SCE_BT_ERROR_GATT_NOT_CONNECTED                             	 = (int)0x802F2402,
	SCE_BT_ERROR_GATT_BUSY                                      	 = (int)0x802F2403,
	SCE_BT_ERROR_GATT_INVALID_HANDLE                            	 = (int)0x802F2404,
	SCE_BT_ERROR_GATT_INVALID_FLAGS                             	 = (int)0x802F2405,
	SCE_BT_ERROR_GATT_INVALID_SIZE                              	 = (int)0x802F2406,
	SCE_BT_ERROR_GATT_NOT_LE                                    	 = (int)0x802F2407,
	SCE_BT_ERROR_GATT_TOO_BIG_RECORD                            	 = (int)0x802F2408,
	SCE_BT_ERROR_GATT_NOT_YET                                   	 = (int)0x802F2409,
	SCE_BT_ERROR_GATT_DISCONNECT                                	 = (int)0x802F240A,
	SCE_BT_ERROR_GATT_TSLEEP                                    	 = (int)0x802F240B,
	SCE_BT_ERROR_GATT_ENTER                                     	 = (int)0x802F240C,
	SCE_BT_ERROR_GATT_TOO_BIG_BUFFER                            	 = (int)0x802F240D,
	SCE_BT_ERROR_SM_INVALID_KEY_LENGTH                          	 = (int)0x802F2501,
	SCE_BT_ERROR_SM_NOT_DIGIT                                   	 = (int)0x802F2502,
	SCE_BT_ERROR_SM_NO_REQ                                      	 = (int)0x802F2503,
	SCE_BT_ERROR_SM_NOT_NEEDED_PIN                              	 = (int)0x802F2504,
	SCE_BT_ERROR_SM_INVALID_CONFIRM_REPLY                       	 = (int)0x802F2505,
	SCE_BT_ERROR_LE_SET_ADVERTISING_INVALID_REQ                 	 = (int)0x802F2601,
	SCE_BT_ERROR_LE_SET_ADVERTISING_INVALID_LENGTH              	 = (int)0x802F2602,
	SCE_BT_ERROR_LE_SET_ADVERTISING_INVALID_INTERVAL_MIN        	 = (int)0x802F2603,
	SCE_BT_ERROR_LE_SET_ADVERTISING_INVALID_INTERVAL_MAX        	 = (int)0x802F2604,
	SCE_BT_ERROR_LE_SET_ADVERTISING_INVALID_OWN_ADDRESS_TYPE    	 = (int)0x802F2605,
	SCE_BT_ERROR_LE_SET_ADVERTISING_INVALID_DIRECT_ADDRESS_TYPE 	 = (int)0x802F2606,
	SCE_BT_ERROR_LE_SET_ADVERTISING_INVALID_DIRECT_ADDRESS      	 = (int)0x802F2607,
	SCE_BT_ERROR_LE_SET_SCAN_INVALID_REQ                        	 = (int)0x802F2701,
	SCE_BT_ERROR_LE_SET_SCAN_INVALID_LENGTH                     	 = (int)0x802F2702,
	SCE_BT_ERROR_LE_SET_SCAN_INVALID_INTERVAL                   	 = (int)0x802F2703,
	SCE_BT_ERROR_LE_SET_SCAN_INVALID_WINDOW                     	 = (int)0x802F2704,
	SCE_BT_ERROR_LE_SET_SCAN_INVALID_OWN_ADDRESS_TYPE           	 = (int)0x802F2705,
	SCE_BT_ERROR_LE_GET_ADVERTISING_NOT_FOUND                   	 = (int)0x802F2801,
	SCE_BT_ERROR_LE_CREATE_CONNECTION_INVALID_SCAN_INTERVAL     	 = (int)0x802F2901,
	SCE_BT_ERROR_LE_CREATE_CONNECTION_INVALID_SCAN_WINDOW       	 = (int)0x802F2902,
	SCE_BT_ERROR_LE_CREATE_CONNECTION_INVALID_PEER_ADDRESS      	 = (int)0x802F2903,
	SCE_BT_ERROR_LE_CREATE_CONNECTION_INVALID_OWN_ADDRESS_TYPE  	 = (int)0x802F2904,
	SCE_BT_ERROR_LE_CREATE_CONNECTION_INVALID_INTERVAL_MIN      	 = (int)0x802F2905,
	SCE_BT_ERROR_LE_CREATE_CONNECTION_INVALID_INTERVAL_MAX      	 = (int)0x802F2906,
	SCE_BT_ERROR_LE_CREATE_CONNECTION_INVALID_LATENCY           	 = (int)0x802F2907,
	SCE_BT_ERROR_LE_CREATE_CONNECTION_INVALID_TIMEOUT           	 = (int)0x802F2908,
	SCE_BT_ERROR_LE_CREATE_CONNECTION_REG_FULL                  	 = (int)0x802F2909,
	SCE_BT_ERROR_LE_CREATE_CONNECTION_REG_ERROR                 	 = (int)0x802F290A,
	SCE_BT_ERROR_LE_CREATE_CONNECTION_CONNECTED                 	 = (int)0x802F290B,
	SCE_BT_ERROR_LE_CREATE_CONNECTION_FULL                      	 = (int)0x802F290C,
	SCE_BT_ERROR_LE_CREATE_CONNECTION_BUSY                      	 = (int)0x802F290D,
	SCE_BT_ERROR_ATT_READ_INVALID_NO                            	 = (int)0x802F2A01,
	SCE_BT_ERROR_ATT_READ_INVALID_LENGTH                        	 = (int)0x802F2A02,
	SCE_BT_ERROR_ATT_READ_INVALID_INTERNAL                      	 = (int)0x802F2A03,
	SCE_BT_ERROR_ATT_WRITE_INVALID_NO                           	 = (int)0x802F2A04,
	SCE_BT_ERROR_ATT_WRITE_INVALID_LENGTH                       	 = (int)0x802F2A05,
	SCE_BT_ERROR_ATT_WRITE_INVALID_INTERNAL                     	 = (int)0x802F2A06,
	SCE_BT_ERROR_ATT_NOT_YET                                    	 = (int)0x802F2A07,
	SCE_BT_ERROR_LE_NOT_SUPPORTED                               	 = (int)0x802F2B01,
	SCE_BT_ERROR_PAIRING_OOB_TIMEOUT                            	 = (int)0x802F3101,
	SCE_BT_ERROR_PAIRING_OOB_FULL                               	 = (int)0x802F3102,
	SCE_BT_ERROR_PAIRING_OOB_CAN_NOT_DISCONNECT                 	 = (int)0x802F3103,
	SCE_BT_ERROR_PAIRING_OOB_INTERNAL_ERROR                     	 = (int)0x802F3104,
	SCE_BT_ERROR_NOT_READY                                      	 = (int)0x802F3201,
	SCE_BT_ERROR_GET_JACK_STATUS_NOT_CONNECTED                  	 = (int)0x802F3301,
	SCE_BT_ERROR_TOO_MANY_CONNECTION                            	 = (int)0x802F3401,
	SCE_BT_ERROR_TOO_MANY_HID                                   	 = (int)0x802F3402,
	SCE_BT_ERROR_NOT_SUPPORTED_DEVICE                           	 = (int)0x802F3403,
	SCE_BT_ERROR_JEDI_VOLUME_GAIN_NOT_CONNECTED                 	 = (int)0x802F3501,
	SCE_BT_ERROR_JEDI_SNIFF_NOT_CONNECTED                       	 = (int)0x802F3601,
	SCE_BT_ERROR_JEDI_SNIFF_NOT_JEDI                            	 = (int)0x802F3602
} SceBtErrorCode;

typedef struct SceBtRegisteredInfo {
	unsigned char  mac[6];
	unsigned short unk0;
	unsigned int   bt_class;
	unsigned int   unk1;
	unsigned int   unk2;
	unsigned short vid;
	unsigned short pid;
	unsigned int   unk3;
	unsigned int   unk4;
	char           name[128];
	unsigned char  unk5[0x60];
} SceBtRegisteredInfo;

typedef struct SceBtEvent {
	union {
		unsigned char data[0x10];
		struct {
			unsigned char  id;
			unsigned char  unk1;
			unsigned short unk2;
			unsigned int   unk3;
			unsigned int   mac0;
			unsigned int   mac1;
		};
	};
} SceBtEvent;

typedef void (*SceBtCallback)(int r0, int r1, int r2, int r3);

typedef struct _SceBtHidRequest {
	uint32_t unk00;
	uint32_t unk04;
	uint8_t  type;    //!< 0 = read?, 1 = write?, 2 = feature?, 3 = ?
	uint8_t  unk09;
	uint8_t  unk0A;
	uint8_t  unk0B;
	void     *buffer;
	uint32_t length;
	struct   _SceBtHidRequest *next;
} __attribute__((packed)) SceBtHidRequest;

int sceBtAvrcpReadVolume(int r0, int r1, int r2, int r3);
int sceBtAvrcpSendButton(int r0, int r1, int r2, int r3);
int sceBtAvrcpSendVolume(int r0, int r1, int r2, int r3);
int sceBtAvrcpSetPlayStatus(int r0, int r1, int r2, int r3);
int sceBtAvrcpSetTitle(int r0, int r1, int r2, int r3);
int sceBtDeleteRegisteredInfo(unsigned int mac0, unsigned int mac1);
int sceBtFreqAudio(int r0, int r1, int r2, int r3);
int sceBtGetConfiguration(void); // returns 0x0 BT disabled, 0x9 if enabled
int sceBtGetConnectingInfo(unsigned int mac0, unsigned int mac1); // 1 = disconnected?, 2 = connecting?, 5 = connected?
int sceBtGetDeviceName(unsigned int mac0, unsigned int mac1, char name[0x79]);
int sceBtGetInfoForTest(int r0, int r1, int r2, int r3);
int sceBtGetLastError(void);
int sceBtGetRegisteredInfo(int device, int unk, SceBtRegisteredInfo *info, SceSize info_size);
int sceBtGetStatusForTest(int r0, int r1, int r2, int r3);
int sceBtGetVidPid(unsigned int mac0, unsigned int mac1, unsigned short vid_pid[2]);
int sceBtHfpGetCurrentPhoneNumber(int r0, int r1, int r2, int r3);
int sceBtHfpRequest(int r0, int r1, int r2, int r3);
int sceBtHidGetReportDescriptor(unsigned int mac0, unsigned int mac1, void *buffer, SceSize size);
int sceBtHidTransfer(unsigned int mac0, unsigned int mac1, SceBtHidRequest *request);
int sceBtPushBip(int r0, int r1, int r2, int r3);
int sceBtPushOpp(int r0, int r1, int r2, int r3);
int sceBtReadEvent(SceBtEvent *events, int num_events);
int sceBtRecvAudio(int r0, int r1, int r2, int r3);
int sceBtRecvBip(int r0, int r1, int r2, int r3);
int sceBtRecvOpp(int r0, int r1, int r2, int r3);
int sceBtRecvSpp(int r0, int r1, int r2, int r3);
int sceBtRegisterCallback(SceUID cb, int unused, int flags1, int flags2); // looks like flags1 is a mask for permitted MACs
int sceBtReplyPinCode(unsigned int mac0, unsigned int mac1, unsigned char *code, SceSize length);
int sceBtReplyUserConfirmation(unsigned int mac0, unsigned int mac1, int unk);
int sceBtSendAudio(int r0, int r1, int r2, int r3);
int sceBtSendL2capEchoRequestForTest(int r0, int r1, int r2, int r3);
int sceBtSendSpp(int r0, int r1, int r2, int r3);
int sceBtSetConfiguration(int r0); //0 = disable bt, 1 = enabling, 2 = enabled 3 = disabling?
int sceBtSetContentProtection(int r0);
int sceBtSetInquiryResultForTest(unsigned char *);
int sceBtSetInquiryScan(int r0);
int sceBtSetL2capEchoResponseBufferForTest(int r0, int r1, int r2, int r3);
int sceBtSetStatusForTest(int r0, int r1, int r2, int r3);
int sceBtStartAudio(int r0, int r1, int r2, int r3);
int sceBtStartConnect(unsigned int mac0, unsigned int mac1); // mac0 can be used as a device index (already paired devices)?
int sceBtStartDisconnect(unsigned int mac0, unsigned int mac1);
int sceBtStartInquiry(void);
int sceBtStopAudio(int r0, int r1, int r2, int r3);
int sceBtStopInquiry(void);
int sceBtUnregisterCallback(SceUID cb);

#ifdef __cplusplus
}
#endif

#endif /* _VDSUITE_KERNEL_BT_H */

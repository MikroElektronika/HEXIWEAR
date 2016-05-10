/**
 * global device functions
 * Project HEXIWEAR, 2015
 */

#ifndef HG_HEXIWEAR_DRIVER
#define HG_HEXIWEAR_DRIVER

#include "HEXIWEAR_driver.h"

#include "sensor_driver.h"
#include "host_mcu_interface.h"
#include "gui_driver.h"
#include "rtc_driver.h"

/**
 * initialize the tasks
 * @return status flag
 */
hexiwear_status_t HEXIWEAR_Init();

/**
 * reset the MCU
 */
void HEXIWEAR_ResetMCU();

/**
 * [HEXIWEAR_GetBackupList description]
 */
void* HEXIWEAR_GetAppBackupList();

/**
 * [HEXIWEAR_GetTargetApp description]
 */
packet_pushTarget_t HEXIWEAR_GetAppTarget();

/**
 * [HEXIWEAR_SetBackupList description]
 */
void HEXIWEAR_SetBackupList( packet_pushTarget_t* currentBackupList );

/**
 * [HEXIWEAR_SetTargetApp description]
 */
void HEXIWEAR_SetTargetApp( packet_pushTarget_t currentApp );

/**
 * set application-specific flags
 * @param  flashAddress flash address for programming
 * @param  flags        data to be programmed into flash
 * @param  flagSize     data size, must be multiple of 8 bytes
 * @return              status flag
 */
hexiwear_status_t HEXIWEAR_SetFlags (
                                         uint32_t flashAddress,
                                            void* flags,
                                         uint32_t flagSize
                                    );

/**
 * [HEXIWEAR_CreateVersionEvent description]
 */
void HEXIWEAR_CreateVersionEvent();

/**
 * [HEXIWEAR_CreateVersionEvent description]
 */
void HEXIWEAR_SendVersionReq();

/**
 * [HEXIWEAR_WaitForVersionUpdate description]
 * @param  timeout [description]
 * @return         [description]
 */
osa_status_t HEXIWEAR_WaitForVersionUpdate(uint32_t timeout);

/**
 * update KW40 version
 * @return status flag
 */
osa_status_t HEXIWEAR_UpdateVersion();

#endif

/**
 * Project HEXIWEAR, 2015
 * sensors wrapper routines
 */

#ifndef HG_SENSORS
#define HG_SENSORS

#include "fsl_os_abstraction.h"

#include "sensor_types.h"
#include "HEXIWEAR_types.h"

#include "FXAS_driver.h"
#include "FXOS_driver.h"
#include "HTU_driver.h"
#include "MPL_driver.h"
#include "TSL_driver.h"
#include "MAXIM_driver.h"

#define registerFormatters( sensType )\
sensor_fmtDef2Float = sensType##_fmtDef2Float;\
sensor_fmtDef2Me    = sensType##_fmtDef2Me

/**
 * initialize sensor  task
 */
osa_status_t sensor_Init();

/**
 * format sensor data to other formats
 * @param sensorData data to be formatted
 * @param fmtOptions options include:
 *                   - data type
 *                   - original format
 *                   - new format
 */

/**
 * initialize sensors' modules
 * @return bit-vector with sensor initialization success flags
 */
sensor_mask_t sensor_InitModules(
                                  sensor_mask_t sensorList
                                );


/**
 * [sensor_SetPushTargets description]
 * @param sensorToUpdate [description]
 * @param newPushTarget  [description]
 */
void sensor_SetPushTargets(
                                sensor_packet_t sensorToUpdate,
                            sensor_pushTarget_t newPushTarget
                          );

/**
 * [sensor_SetPushTargets  description]
 * @param  sensorToUpdate [description]
 * @return                [description]
 */
sensor_pushTarget_t sensor_GetPushTargets (
                                            sensor_packet_t sensorToUpdate
                                          );

/**
 * [sensor_FormatData description]
 * @param src        [description]
 * @param dst        [description]
 * @param fmtOptions [description]
 */
void sensor_FormatData(
                          const void* src,
                                void* dst,
                        const uint8_t fmtOptions
                      );

/**
 * format raw to float
 * @param src original data array
 * @param dst new format data array
 * @param idx index of the sample to be formatted
 */
void bat_fmtDef2Float(
                        const void* src,
                              void* dst,
                           uint32_t idx
                      );

/**
 * format raw to mE format
 * @param src original data array
 * @param dst new format data array
 * @param idx index of the sample to be formatted
 */
void bat_fmtDef2Me (
                      const void* src,
                            void* dst,
                         uint32_t idx
                    );

#endif

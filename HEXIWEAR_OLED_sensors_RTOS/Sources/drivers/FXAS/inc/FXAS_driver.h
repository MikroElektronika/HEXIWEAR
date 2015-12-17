/**
 * FXAS driver functions
 * Project HEXIWEAR, 2015
 */

#ifndef HG_FXAS_DRIVER
#define HG_FXAS_DRIVER

#include "FXAS_types.h"

/**
 * initialize the sensor
 * @param  fxasHandle    handle to be populated with sensor info
 * @param  fxasSettings  user settings
 * @return status flag
 */
statusFXAS_t FXAS_Init(
                                handleFXAS_t* self,
                        const settingsFXAS_t* settings
                      );

/**
 * turn off the sensor
 */
statusFXAS_t FXAS_Deinit();

/**
 * read raw data from the sensor
 */
statusFXAS_t FXAS_ReadRawData (
                                int16_t* sensorData
                              );

/**
 * put the FXAS21002C into standby mode
 * standby mode is necessary before attempting to modify most of the registers
 */
void FXAS_GotoStandby();

/**
 * set the FXAS21000 to Ready mode
 * it's necessary to be in this mode to output data
 */
void FXAS_GetReady();

/**
 * put the FXAS21002C into active mode
 * it's necessary to be in this mode to output data
 */
void FXAS_SetActive();

/**
 * reset the module
 */
void FXAS_Reset();

/**
 * format data from raw to float
 * @param src original data array
 * @param dst new format data array
 * @param idx index of the sample to be formatted
 */
void gyro_fmtDef2Float(
                        const void* src,
                              void* dst,
                           uint32_t idx
                      );

/**
 * format data from raw to mE format
 * @param src original data array
 * @param dst new format data array
 * @param idx index of the sample to be formatted
 */
void gyro_fmtDef2Me (
                      const void* src,
                            void* dst,
                         uint32_t idx
                    );

#endif

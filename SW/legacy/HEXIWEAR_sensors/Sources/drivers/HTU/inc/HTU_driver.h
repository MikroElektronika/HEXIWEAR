/**
 * HTU driver functions
 * Project HEXIWEAR, 2015
 */

#ifndef HG_HTU_DRIVER
#define HG_HTU_DRIVER

#include "HTU_types.h"

/**
 * initialize i2c interface to HTU21D sensor and reset the module
 * @return status flag
 */
statusHTU_t HTU_Init(
                        handleHTU_t* self,
                      settingsHTU_t* settings
                    );
/**
 * initialize i2c interface to HTU21D sensor and reset the module
 * @return status flag
 */
statusHTU_t HTU_Deinit();

/**
 * reset the sensor
 * @return status flag
 */
statusHTU_t HTU_Reset ();

/**
 * configure the measurement resolution
 * @return status flag
 */
statusHTU_t HTU_SetUserRegister();

/**
 * retrieve temperature data
 * @param  sensorData data to be filled
 * @return            status flag
 */
statusHTU_t HTU_GetTemp (
                          int16_t* tempData
                        );

/**
 * retrieve humidity data
 * @param  humData  data to be filled
 * @return          status flag
 */
statusHTU_t HTU_GetHum(
                        int16_t* humData
                      );

/**
 * retrieve temperature and humidity data
 */
statusHTU_t HTU_ReadRawData (
                              int16_t* temperature,
                              int16_t* humidity
                            );

/**
 * format raw to float
 * @param src original data array
 * @param dst new format data array
 * @param idx index of the sample to be formatted
 */
void hum_fmtDef2Float (
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
void hum_fmtDef2Me (
                      const void* src,
                            void* dst,
                         uint32_t idx
                    );

#endif

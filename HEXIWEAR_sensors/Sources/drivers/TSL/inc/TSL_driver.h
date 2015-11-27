/**
 * TSL driver functions
 * Project HEXIWEAR, 2015
 */

#ifndef HG_TSL_DRIVER
#define HG_TSL_DRIVER

#include "TSL_types.h"

/**
 * initialize the sensor
 * @param  tslHandle    handle to be populated with sensor info
 * @param  tslSettings  user settings
 * @return  status flag
 */
statusTSL_t TSL_Init(
                              handleTSL_t* self,
                      const settingsTSL_t* settings
                    );

/**
 * shut down the sensor
 */
statusTSL_t TSL_Deinit();

/**
 * enable the sensor
 */
void TSL_Enable ();

/**
 * disable the sensor
 */
void TSL_Disable();

/**
 * set sensor gain
 * @param  gain [description]
 * @return      status flag
 */
statusTSL_t TSL_SetGain (
                           gainTSL_t gain
                        );

/**
 * set sensor integration time
 * @param  integration integration time
 * @return             status flag
 */
statusTSL_t TSL_SetTiming (
                            integrationTSL_t integration
                          );

/**
 * read raw sensor data
 * @param  channel    TSL channel (red or infrared)
 * @param  sensorData sensor data to be filled
 * @return            status flag
 */
statusTSL_t TSL_ReadRawData (
                              channelTSL_t channel,
                                 uint16_t* sensorData
                            );

/**
 * calculate luminance
 */
statusTSL_t TSL_CalculateLux(
                               uint16_t ch0,
                               uint16_t ch1,
                              uint32_t* luxVal
                            );

/**
 * formatting functions
 */

/**
 * format raw to float
 * @param src original data array
 * @param dst new format data array
 * @param idx index of the sample to be formatted
 */
void ambi_fmtDef2Float(
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
void ambi_fmtDef2Me (
                      const void* src,
                            void* dst,
                         uint32_t idx
                    );

#endif

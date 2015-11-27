/**
 * MAXIM-related driver functions
 * Project HEXIWEAR, 2015
 */

#include "MAXIM_types.h"

#ifndef HG_MAXIM_DRIVER
#define HG_MAXIM_DRIVER

/**
 * initialize MAXIM module
 */
statusMAXIM_t MAXIM_Init(
                                  handleMAXIM_t* maximHandle,
                          const settingsMAXIM_t* maximSettings
                        );

/**
 * shutdown the sensor
 */
statusMAXIM_t MAXIM_Deinit();

/**
 * reset the module
 * when the reset-bit is set to one, all configuration, threshold,
 * and data registers are reset to their power-on-state through
 * a power-on reset
 *
 * the reset bit is cleared automatically back to zero after the reset sequence is completed
 */
statusMAXIM_t MAXIM_Reset();


/**
 * read FIFO buffer
 */
statusMAXIM_t MAXIM_ReadFIFO(
                              uint32_t* ledVal
                            );


/**
 * format raw to float
 * @param src original data array
 * @param dst new format data array
 * @param idx index of the sample to be formatted
 */
void hr_fmtDef2Float(
                      const void* src,
                            void* dst,
                         uint32_t idx
                    );

/**
 * read raw sensor data
 */
statusMAXIM_t MAXIM_ReadRawData (
                                  uint32_t* sensorData,
                                  uint32_t* sampleNum
                                );
/**
 * format raw to mE format
 * @param src original data array
 * @param dst new format data array
 * @param idx index of the sample to be formatted
 */
void hr_fmtDef2Me (
                    const void* src,
                          void* dst,
                       uint32_t idx
                  );

#endif

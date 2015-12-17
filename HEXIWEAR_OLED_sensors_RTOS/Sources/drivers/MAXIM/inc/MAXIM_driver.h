/**
 * MAXIM-related driver functions
 * Project HEXIWEAR, 2015
 */

#ifndef HG_MAXIM_DRIVER
#define HG_MAXIM_DRIVER

#include "MAXIM_types.h"
#include "arm_math.h"

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
                                  dataMAXIM_t* redData,
                                  dataMAXIM_t* irData,
                                  dataMAXIM_t* greenData,

                                     uint32_t* sampleNum
                                );

/**
 * find the HR peak in the desired part of the spectrum
 * @param  spectrum  heart-rate frequenct spectrum
 * @param  minFreq   lower frequency border
 * @param  maxFreq   upper frequency border
 * @param  heartRate heart rate to be calculated
 * @return           status flag
 */
statusMAXIM_t MAXIM_GetHR (
                            float32_t* spectrum,
                             float32_t minFreq,
                             float32_t maxFreq,
                            float32_t* heartRate
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

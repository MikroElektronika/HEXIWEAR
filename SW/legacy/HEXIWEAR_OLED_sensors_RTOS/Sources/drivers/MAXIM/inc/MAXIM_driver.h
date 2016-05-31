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
maxim_status_t MAXIM_Init(
                                  handleMAXIM_t* maximHandle,
                          const settingsMAXIM_t* maximSettings
                        );

/**
 * shutdown the sensor
 */
maxim_status_t MAXIM_Deinit();

/**
 * reset the module
 * when the reset-bit is set to one, all configuration, threshold,
 * and data registers are reset to their power-on-state through
 * a power-on reset
 *
 * the reset bit is cleared automatically back to zero after the reset sequence is completed
 */
maxim_status_t MAXIM_Reset();

/**
 * read raw sensor data
 */
maxim_status_t MAXIM_ReadRawData(
                                    uint8_t* dataBuff,
                                    uint8_t* sampleNum
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

/**
 * [MAXIM_Enable description]
 * @return [description]
 */
maxim_status_t MAXIM_Enable();

/**
 * [MAXIM_Disable description]
 * @return [description]
 */
maxim_status_t MAXIM_Disable();

/**
 * [MAXIM_InstallCallback description]
 * @param callback [description]
 */
void MAXIM_InstallCallback( maxim_callback_t callback );

/**
 * testing HR sensor
 */
void MAXIM_Test();

#endif

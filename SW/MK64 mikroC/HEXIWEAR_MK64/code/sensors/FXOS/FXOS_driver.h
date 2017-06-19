// File: FXOS_driver.h

// Declarations of main functionalities in the FXOS sensor module.

#ifndef _FXOS_driver_h_
#define _FXOS_driver_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include <stdbool.h>

#include "FXOS/FXOS_info.h"
#include "FXOS/FXOS_types.h"

////////////////////////////////////////////////////////////////////////////////
// Global function declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

// Initialises the FXOS sensor.
void FXOS_Init();

// Reads raw data from the sensor. Requires a 6 element array.
void FXOS_ReadRawData( int16_t* sensorData );

//  Accelerometer offset calibration.
void FXOS_CalibrateAcc();

//  Magnetometer offset calibration.
void FXOS_CalibrateMag();

// Puts the sensor into standby mode.
void FXOS_GotoStandby();

// Puts the sensor into active mode.
void FXOS_SetActive();

// Resets the module.
void FXOS_SoftReset();

// Reads raw temperature value.
void FXOS_ReadRawTemp( uint8_t *tempVal );

// Configures the FXOS tap event.
void FXOS_ConfigureTapEvent();

// Enable tap detection.
void FXOS_EnableTap();

// Disable tap detection.
void FXOS_DisableTap();

// Check if tap is enabled.
bool FXOS_IsTapEnabled();

// Callback for the interrupt.
void FXOS_Callback();

// Read the status of the tap source register.
void FXOS_TapHandler();

// Read FXOS status register.
void FXOS_ReadStatus( uint8_t* sensorStatus );

// Check if tap is enabled.
bool FXOS_CheckForTap();

// Formats raw accelerometer data to float.
float FXOS_AccFormatFloat( int16_t input );

// Formats raw accelerometer data to int.
int16_t FXOS_AccFormatInt( int16_t input );

// Formats raw magnetometer data to float.
float FXOS_MagFormatFloat( int16_t input );

// Formats raw magnetometer data to int.
int16_t FXOS_MagFormatInt( int16_t input );

// Formats raw to float.
void acc_fmtDef2Float(
                       const void* src,
                             void* dst,
                          uint32_t idx
                     );

// Formats raw to mE format.
void acc_fmtDef2Me(
                    const void* src,
                          void* dst,
                       uint32_t idx
                  );

// Formats raw to byte - currently unimplemented.
void acc_fmtDef2Byte(
                      const void* src,
                            void* dst,
                         uint32_t idx
                    );

void acc_fmtMe2Def(
                    const void* src,
                          void* dst
                  );

// Formats raw to float.
void mag_fmtDef2Float(
                       const void* src,
                             void* dst,
                          uint32_t idx
                     );

// Formats raw to mE format.
void mag_fmtDef2Me(
                    const void* src,
                          void* dst,
                       uint32_t idx
                  );

// Formats raw to byte - currently unimplemented.
void mag_fmtDef2Byte(
                      const void* src,
                            void* dst,
                         uint32_t idx
                    );

#endif
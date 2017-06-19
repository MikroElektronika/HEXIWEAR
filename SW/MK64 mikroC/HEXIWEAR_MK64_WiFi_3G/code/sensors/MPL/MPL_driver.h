// File: MPL_driver.h

// Declarations of main functionalities in the MPL sensor module.

#ifndef _MPL_driver_h_
#define _MPL_driver_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "MPL/MPL_info.h"
#include "MPL/MPL_types.h"

////////////////////////////////////////////////////////////////////////////////
// Global function declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

// Initialises the MAXIM sensor.
void MPL_Init();

// Performs a software reset of the sensor.
uint8_t MPL_SoftReset();

// Clears then sets the OST bit which causes the sensor
// to immediately take another reading.
void MPL_ToggleOneShot();

// Sets the device to be barometer or altimeter.
void MPL_SetMode( modeMPL_t mode );

// Puts the sensor in stand-by mode.
// This is needed so that we can modify the major control registers.
void MPL_GotoStandby();

// Puts the sensor in active mode.
void MPL_SetActive();

// Sets the oversample rate.
void MPL_SetOversampleRate( uint8_t sampleRate );

// Enables the pressure and temp measurement event flags
// so that we can test against them.
void MPL_EnableEventFlags();

// Reads raw sensor data.
uint8_t MPL_ReadRawData( modeMPL_t mode, int16_t* sensorData );

// Formats raw data to float.
float MPL_FormatFloat( int32_t input );

// Formats raw data to int.
int16_t MPL_FormatInt( int32_t input );

// Formats raw to float.
void pres_fmtDef2Float(
                        const void* src,
                              void* dst,
                           uint32_t idx
                      );

// Formats raw to mE format.
void pres_fmtDef2Me(
                     const void* src,
                           void* dst,
                        uint32_t idx
                   );

// Formats raw to byte - currently unimplemented.
void pres_fmtDef2Byte(
                       const void* src,
                             void* dst,
                          uint32_t idx
                     );

#endif
// File: TSL_driver.h

// Declarations of main functionalities in the TSL sensor module.

#ifndef _TSL_driver_h_
#define _TSL_driver_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "TSL/TSL_info.h"
#include "TSL/TSL_types.h"

////////////////////////////////////////////////////////////////////////////////
// Global function declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

// Initialises the TSL sensor.
void TSL_Init();

// Deinitialises the sensor.
void TSL_Deinit();

// Enables the sensor.
void TSL_Enable();

// Disables the sensor.
void TSL_Disable();

// Sets sensor gain.
void TSL_SetGain( gainTSL_t gain );

// Sets sensor integration time.
void TSL_SetTiming( integrationTSL_t integration );

// Reads raw sensor data.
void TSL_ReadRawData( channelTSL_t channel, uint16_t* sensorData );

// Calculates luminance.
void TSL_CalculateLux( uint16_t* channelValues, uint32_t* luxVal );

// Converts lux value to light percentage.
void TSL_FormatLux( uint32_t luxVal, uint8_t* ambLight );

// Formats raw to float.
void ambi_fmtDef2Float(
                        const void* src,
                              void* dst,
                           uint32_t idx
                      );

// Formats raw to mE format - currently unimplemented.
void ambi_fmtDef2Me(
                     const void* src,
                           void* dst,
                        uint32_t idx
                   );

// Formats raw to byte format.
void ambi_fmtDef2Byte(
                       const void* src,
                             void* dst,
                          uint32_t idx
                     );

#endif
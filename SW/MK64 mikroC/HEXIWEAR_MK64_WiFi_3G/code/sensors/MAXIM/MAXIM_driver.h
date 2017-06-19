// File: MAXIM_driver.h

// Declarations of main functionalities in the MAXIM sensor module.

#ifndef _MAXIM_driver_h_
#define _MAXIM_driver_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "MAXIM/MAXIM_info.h"
#include "MAXIM/MAXIM_types.h"

////////////////////////////////////////////////////////////////////////////////
// Global function declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

// Initialises the MAXIM sensor.
void MAXIM_Init();

// Shutdowns the sensor.
void MAXIM_Deinit();

// Resets the module.
uint8_t MAXIM_Reset();

// Reads raw sensor data.
void MAXIM_ReadRawData( uint8_t* dataBuff, uint8_t* sampleNum );

// Enables the sensor.
void MAXIM_Enable();

// Disables the sensor.
void MAXIM_Disable();

// Installs callback to be called during sensor's read.
void MAXIM_InstallCallback( maxim_callback_t callback );

// Tests the sensor.
void MAXIM_Test();

// Formats raw to float.
void hr_fmtDef2Float(
                      const void* src,
                            void* dst,
                         uint32_t idx
                    );

// Formats raw to mE format.
void hr_fmtDef2Me(
                   const void* src,
                         void* dst,
                      uint32_t idx
                 );

// Formats raw to byte - currently unimplemented.
void hr_fmtDef2Byte(
                     const void* src,
                           void* dst,
                        uint32_t idx
                   );

#endif
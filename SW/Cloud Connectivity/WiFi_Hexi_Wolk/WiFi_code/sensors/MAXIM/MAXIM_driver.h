// File: MAXIM_driver.h

// Declarations of main functionalities in the MAXIM sensor module.

#ifndef _MAXIM_driver_h_
#define _MAXIM_driver_h_

/******************************************************************************
 * Header file inclusions.                                                    *
 ******************************************************************************/

#include "MAXIM_info.h"
#include "MAXIM_types.h"

/******************************************************************************
 * Global function declarations.                                              *
 ******************************************************************************/

// Initialises the MAXIM sensor.
void MAXIM_Init();

// Resets the module.
uint8_t MAXIM_Reset();

// Reads raw sensor data.
void MAXIM_ReadRawData( uint8_t* dataBuff, uint8_t* sampleNum );

// Enables the sensor.
void MAXIM_Enable();

// Installs callback to be called during sensor's read.
void MAXIM_InstallCallback( maxim_callback_t callback );

// Tests the sensor.
void MAXIM_Test();

#endif
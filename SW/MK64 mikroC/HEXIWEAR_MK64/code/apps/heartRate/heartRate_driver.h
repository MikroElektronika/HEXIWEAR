// File: heartRate_driver.h

// Declarations of main functionalities in the heart rate module.

#ifndef _heartRate_driver_h_
#define _heartRate_driver_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include <string.h>

#include "heartRate_info.h"
#include "heartRate_types.h"
#include "OSA.h"
#include "host_mcu_interface.h"

////////////////////////////////////////////////////////////////////////////////
// Global function declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

// Registers heart-rate sensor and FFT.
void heartRate_Init();

// Unregisters from HR sensor and frees used memory.
void heartRate_Deinit();

// Reallocates the buffers and resets the relevant variables.
void heartRate_Resume();

/// Frees used memory and unregisters from HR sensor.
void heartRate_Pause();

// Processes available HR data.
void heartRate_Process(
        void* sampleBuf, uint8_t numAvailSam, void* param );

#endif
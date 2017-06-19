// File: sensor_defs.h

// Declarations of some commonly used variables in the sensors module.

#ifndef _sensor_defs_h_
#define _sensor_defs_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "sensor_types.h"

#include "HEXIWEAR.h"

////////////////////////////////////////////////////////////////////////////////
// Global variable declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

//extern sensor_pins_t sensor_powerPins;

// sensor tasks
extern task_handler_t hexiwear_sensor_TAG_handler;
extern task_handler_t hexiwear_sensor_FITNESS_handler;

// Sensor category buffers.

extern motionData_t motionData;

extern weatherData_t weatherData;

extern dataConversion_t sensor_fmtDef2Float;
extern dataConversion_t sensor_fmtDef2Me;
extern dataConversion_t sensor_fmtDef2Byte;

extern dataConversion_t sensor_fmtFloat2Def;
extern dataConversion_t sensor_fmtFloat2Me;

extern dataConversion_t sensor_fmtMe2Def;
extern dataConversion_t sensor_fmtMe2Float;

extern mutex_t sensor_i2cAccessMutex;

#endif
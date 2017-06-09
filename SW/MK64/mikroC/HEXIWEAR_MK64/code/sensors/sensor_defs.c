// File: sensor_defs.c

// Definitions of some commonly used variables in the sensors module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "sensor_defs.h"
#include "HEXIWEAR_info.h"

////////////////////////////////////////////////////////////////////////////////
// Global variable declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

//sensor_pins_t sensor_powerPins =  {
    // power options
//    .B_EN_pin        = PWR_SENSORS_NF,
//    .LDO_EN_pin      = PWR_HR,
//    .BAT_SENS_EN_pin = PWR_BAT_SENS,
//
    // vibro-motor options
//    .VIBRO_pin       = VIBRO
//};

// Sensor tasks.
task_handler_t hexiwear_sensor_TAG_handler;
task_handler_t hexiwear_sensor_FITNESS_handler;

// Sensor category buffers.

motionData_t motionData;

weatherData_t weatherData;

dataConversion_t sensor_fmtDef2Float = ( void* )( 0 );
dataConversion_t sensor_fmtDef2Me    = ( void* )( 0 );
dataConversion_t sensor_fmtDef2Byte  = ( void* )( 0 );

dataConversion_t sensor_fmtFloat2Def = ( void* )( 0 );
dataConversion_t sensor_fmtFloat2Me  = ( void* )( 0 );

dataConversion_t sensor_fmtMe2Def    = ( void* )( 0 );
dataConversion_t sensor_fmtMe2Float  = ( void* )( 0 );

mutex_t sensor_i2cAccessMutex;
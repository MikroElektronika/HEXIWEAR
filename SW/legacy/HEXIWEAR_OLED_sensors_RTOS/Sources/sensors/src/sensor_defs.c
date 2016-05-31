/**
 * sensor-related global variables
 * Project HEXIWEAR, 2015
 */

#include "sensor_defs.h"
#include "GPIO.h"
#include "HEXIWEAR_info.h"

sensor_pins_t
  sensor_powerPins =  {
                      // power options
                      .B_EN_pin        = PWR_SENSORS_NF,
                      .LDO_EN_pin      = PWR_HR,
                      .BAT_SENS_EN_pin = PWR_BAT_SENS,

                      // vibro-motor options
                      .VIBRO_pin       = VIBRO
                    };

// sensor tasks
task_handler_t
  hexiwear_sensor_TAG_handler,
  hexiwear_sensor_FITNESS_handler;

/**
 * sensor category buffers
 */

motionData_t
  motionData;

weatherData_t
  weatherData;

healthData_t
  healthData;

dataConversion_t
  sensor_fmtDef2Float = (void*)(0),
  sensor_fmtDef2Me    = (void*)(0),
  sensor_fmtDef2Byte  = (void*)(0),

  sensor_fmtFloat2Def = (void*)(0),
  sensor_fmtFloat2Me  = (void*)(0),

  sensor_fmtMe2Def    = (void*)(0),
  sensor_fmtMe2Float  = (void*)(0);

mutex_t
  sensor_i2cAccessMutex;

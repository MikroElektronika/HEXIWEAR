/**
 * sensor-related global variables
 * Project HEXIWEAR, 2015
 */

#ifndef HG_SENSOR_DEFS
#define HG_SENSOR_DEFS

#include "sensor_types.h"

#include "FXOS_defs.h"
#include "FXAS_defs.h"
#include "HTU_defs.h"
#include "MPL_defs.h"
#include "TSL_defs.h"
#include "MAXIM_defs.h"

extern sensor_pins_t
  sensor_powerPins;

// sensor tasks
extern task_handler_t
  hexiwear_sensor_TAG_handler,
  hexiwear_sensor_FITNESS_handler;

/**
 * sensor category buffers
 */

extern motionData_t
  motionData;

extern weatherData_t
  weatherData;

extern healthData_t
  healthData;

extern dataConversion_t
  sensor_fmtDef2Float,
  sensor_fmtDef2Me,
  sensor_fmtFloat2Def,
  sensor_fmtFloat2Me,
  sensor_fmtMe2Def,
  sensor_fmtMe2Float;

#endif

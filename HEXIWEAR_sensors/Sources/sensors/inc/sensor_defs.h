/**
 * sensor-related global variables
 * Project HEXIWEAR, 2015
 */

#ifndef HG_SENSOR_DEFS
#define HG_SENSOR_DEFS

#include <stdint.h>
#include "sensor_types.h"

extern settingsSENSOR_t
  sensorSettings;

extern dataConversion_t
  sensor_fmtDef2Float,
  sensor_fmtDef2Me,
  sensor_fmtFloat2Def,
  sensor_fmtFloat2Me,
  sensor_fmtMe2Def,
  sensor_fmtMe2Float;

#endif

/**
 * sensor-related global variables
 * Project HEXIWEAR, 2015
 */

#include "sensor_defs.h"
#include "gpio1.h"

settingsSENSOR_t
  sensorSettings =  {
                      .B_EN_pin        = PTB12,
                      .LDO_EN_pin      = PTA29,
                      .BAT_SENS_EN_pin = J199_3,
                      .VIBRO_pin       = J1_5
                    };

dataConversion_t
  sensor_fmtDef2Float = (void*)(0),
  sensor_fmtDef2Me    = (void*)(0),
  sensor_fmtFloat2Def = (void*)(0),
  sensor_fmtFloat2Me  = (void*)(0),
  sensor_fmtMe2Def    = (void*)(0),
  sensor_fmtMe2Float  = (void*)(0);

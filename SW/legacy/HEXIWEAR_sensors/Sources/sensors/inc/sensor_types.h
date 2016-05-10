/**
 * data-types related to sensors and their communication
 */

#ifndef HG_SENSOR_TYPES
#define HG_SENSOR_TYPES

#include <stdint.h>
#include "host_mcu_interface.h"

// particular sensor modules
typedef enum
{
  /**
   * sensor successful completion is noted by the presence of 1 on the particular bit-field
   * sensor failure is noted by the absence of 1 on the particular bit-field
   */
  SENSOR_SUCCESS_NONE  =   0,
  SENSOR_SUCCESS_FXOS  =   1 << 0, // compass
  SENSOR_SUCCESS_FXAS  =   1 << 1, // gyroscope
  SENSOR_SUCCESS_MPL   =   1 << 2, // pressure & temperature
  SENSOR_SUCCESS_HTU   =   1 << 3, // humidity
  SENSOR_SUCCESS_TSL   =   1 << 4, // ambient light
  SENSOR_SUCCESS_MAXIM =   1 << 5, // heart-rate
  SENSOR_SUCCESS_ALL   = ( 1 << 6 ) - 1

} sensorScoreboard_t;

typedef enum
{
  SEND_YES,
  SEND_NO,
  SEND_SKIP

} send_t;


typedef struct
{
  uint32_t B_EN_pin;
  uint32_t LDO_EN_pin;
  uint32_t BAT_SENS_EN_pin;
  uint32_t VIBRO_pin;

} settingsSENSOR_t;

// formatting pointer
typedef void (*dataConversion_t)(
                                  const void* src,
                                        void* dst,
                                     uint32_t idx
                                );
#endif


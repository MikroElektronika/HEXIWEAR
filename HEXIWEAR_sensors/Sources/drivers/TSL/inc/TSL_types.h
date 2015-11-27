/**
 * TSL2561-related data structures
 * Project HEXIWEAR, 2015
 */

#ifndef HG_TSL_TYPES
#define HG_TSL_TYPES

#include <stdint.h>
#include "generic_i2c_types.h"

typedef enum
{
  TSL_INTEGRATION_TIME_13MS  = 0, // 13.7ms
  TSL_INTEGRATION_TIME_101MS = 1, // 101ms
  TSL_INTEGRATION_TIME_402MS = 2  // 402ms

} integrationTSL_t;

typedef enum
{
  TSL_GAIN_0X  = 0x00, // no gain
  TSL_GAIN_16X = 0x10  // 16x gain

} gainTSL_t;

typedef enum
{
  CHANNEL_TSL_FULL     = 0,
  CHANNEL_TSL_INFRARED = 1

} channelTSL_t;

typedef enum
{
  STATUS_TSL_SUCCESS,        // success
  STATUS_TSL_ERROR,          // fail
  STATUS_TSL_PROTOCOL_ERROR, // I2C failure
  STATUS_TSL_INIT_ERROR      // initialization error

} statusTSL_t;

typedef struct
{
  integrationTSL_t timing;
         gainTSL_t gain;
           uint8_t address;

} settingsTSL_t;

typedef struct
{
  /**
   * I2C relevant information
   */
  genericI2cHandle_t protocol;

} handleTSL_t;

#endif

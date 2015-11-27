/**
 * HTU-related data structures
 * Project HEXIWEAR, 2015
 */

#ifndef HG_HTU_TYPES
#define HG_HTU_TYPES

#include <stdint.h>
#include "generic_i2c_types.h"

typedef enum
{
  STATUS_HTU_SUCCESS,
  STATUS_HTU_ERROR,
  STATUS_HTU_PROTOCOL_ERROR,
  STATUS_HTU_INIT_ERROR,
  STATUS_HTU_TIMEOUT

} statusHTU_t;

typedef enum
{
  BITRES_HTU_RH_12_TEMP14 = 0,
  BITRES_HTU_RH_8_TEMP12,
  BITRES_HTU_RH_10_TEMP13,
  BITRES_HTU_RH_11_TEMP11,

} bitResHTU_t;

typedef struct
{
  /**
   * I2C relevant information
   */
  genericI2cHandle_t protocol;

} handleHTU_t;

typedef struct
{
  bitResHTU_t bitRes;
      uint8_t address;

} settingsHTU_t;

#endif

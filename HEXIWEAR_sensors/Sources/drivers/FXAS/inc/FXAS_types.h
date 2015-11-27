/**
 * FXAS21002C definitions
 * Project HEXIWEAR, 2015
 */

#ifndef HG_FXAS_TYPES
#define HG_FXAS_TYPES

#include <stdint.h>
#include "generic_i2c_types.h"

typedef enum
{
  GODR_800HZ = 0,
  GODR_400HZ,
  GODR_200HZ,
  GODR_100HZ,
  GODR_50HZ,
  GODR_12_5HZ,
  GODR_6_25HZ,
  GODR_1_56HZ

} gyroODR_t;

// Set initial input parameters
typedef enum
{
  GFSR_2000DPS,
  GFSR_1000DPS,
  GFSR_500DPS,
  GFSR_250DPS

} gyroFSR_t;

// device handle
typedef struct
{
  /**
   * I2C relevant information
   */
  genericI2cHandle_t protocol;

} handleFXAS_t;


typedef struct
{
  gyroODR_t odr;     // output data rate selection
  gyroFSR_t fsr;     // degrees per second
    uint8_t address; // I2C address

} settingsFXAS_t;

typedef struct
{
  uint8_t gyroXMSB;
  uint8_t gyroXLSB;
  uint8_t gyroYMSB;
  uint8_t gyroYLSB;
  uint8_t gyroZMSB;
  uint8_t gyroZLSB;

} dataFXAS_t;

typedef enum
{
  STATUS_FXAS_SUCCESS,        // success
  STATUS_FXAS_ERROR,          // fail
  STATUS_FXAS_PROTOCOL_ERROR, // I2C failure
  STATUS_FXAS_INIT_ERROR,     // initialization error
  STATUS_FXAS_PARAM_ERROR     // invalid parameter is given

} statusFXAS_t;

#endif

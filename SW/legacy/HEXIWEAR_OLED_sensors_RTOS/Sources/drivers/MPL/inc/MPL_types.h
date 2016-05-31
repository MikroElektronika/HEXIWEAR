/*
 * MPL3115A2 definitions
 */

#ifndef HG_MPL_TYPES
#define HG_MPL_TYPES

#include <stdint.h>
#include "generic_i2c_types.h"

typedef enum
{
  STATUS_MPL_SUCCESS,
  STATUS_MPL_ERROR,
  STATUS_MPL_PROTOCOL_ERROR,
  STATUS_MPL_INIT_ERROR,
  STATUS_MPL_TIMEOUT

} mpl_status_t;

typedef enum
{
// oversample factor
  MPL_OS_0,
  MPL_OS_1,
  MPL_OS_2,
  MPL_OS_3,
  MPL_OS_4,
  MPL_OS_5,
  MPL_OS_6,
  MPL_OS_7

} overSampleMPL_t;

typedef enum
{
  MPL_MODE_PRESSURE    = 0,
  MPL_MODE_ALTITUDE    = 1,
  MPL_MODE_TEMPERATURE = 2,
  MPL_MODE_CURRENT     = 0xFF

} modeMPL_t;

typedef struct
{
  /**
   * I2C relevant information
   */
  genericI2cHandle_t protocol;

} handleMPL_t;

typedef struct
{
        modeMPL_t mode;       // device mode, altimeter or barometer
  overSampleMPL_t oversample; // oversampling ratio
          uint8_t address;    // device I2C address
	     uint16_t baudRate_kbps; // I2C baud-rate

} settingsMPL_t;

typedef struct
{
  /**
   * pressure / altitude data
   */
  uint8_t presAltDataMSB;
  uint8_t presAltDataCSB;
  uint8_t presAltDataLSB;

  /**
   * temperature data
   */
  uint8_t tempDataMSB;
  uint8_t tempDataLSB;

} dataMPL_t;

#endif

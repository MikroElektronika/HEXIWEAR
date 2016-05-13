/*
 * FXOS8700-related types
 */

#include "generic_i2c_types.h"
#include "FXOS_info.h"

#ifndef HG_FXOS_TYPES
#define HG_FXOS_TYPES

// FXOS8700 output logic data rate selection
typedef enum
{
  fxosODR0 = ( 0 << FXOS_ODR_SHIFT ),
  fxosODR1 = ( 1 << FXOS_ODR_SHIFT ),
  fxosODR2 = ( 2 << FXOS_ODR_SHIFT ),
  fxosODR3 = ( 3 << FXOS_ODR_SHIFT ),
  fxosODR4 = ( 4 << FXOS_ODR_SHIFT ),
  fxosODR5 = ( 5 << FXOS_ODR_SHIFT ),
  fxosODR6 = ( 6 << FXOS_ODR_SHIFT ),
  fxosODR7 = ( 7 << FXOS_ODR_SHIFT )

} odrFXOS_t;

// FXOS8700 oversample ratio selection
typedef enum
{
  fxosOSR0 = ( 0 << FXOS_OSR_SHIFT ),
  fxosOSR1 = ( 1 << FXOS_OSR_SHIFT ),
  fxosOSR2 = ( 2 << FXOS_OSR_SHIFT ),
  fxosOSR3 = ( 3 << FXOS_OSR_SHIFT ),
  fxosOSR4 = ( 4 << FXOS_OSR_SHIFT ),
  fxosOSR5 = ( 5 << FXOS_OSR_SHIFT ),
  fxosOSR6 = ( 6 << FXOS_OSR_SHIFT ),
  fxosOSR7 = ( 7 << FXOS_OSR_SHIFT )

} osrFXOS_t;

// FXOS8700 accelerometer/magnetometer selection
typedef enum
{
  fxosAccOnly = ( 0 << FXOS_MODE_SHIFT ), // accelerometer only
  fxosMagOnly = ( 1 << FXOS_MODE_SHIFT ), // magnetometer only
  fxosBoth    = ( 3 << FXOS_MODE_SHIFT )  // select both accelerometer and magnetometer

} modeFXOS_t;

// FXOS8700 accelerometer full-scale range
typedef enum
{
  fxosRange2g = ( 0 << FXOS_ACCRANGE_SHIFT ), // 2g mode
  fxosRange4g = ( 1 << FXOS_ACCRANGE_SHIFT ), // 4g mode
  fxosRange8g = ( 2 << FXOS_ACCRANGE_SHIFT )  // 8g mode

} accRangeFXOS_t;

// FXOS8700 return status
typedef enum
{
  STATUS_FXOS_SUCCESS,        // success
  STATUS_FXOS_ERROR,          // general failure
  STATUS_FXOS_PROTOCOL_ERROR, // I2C failure
  STATUS_FXOS_INIT_ERROR,     // initialization failure
  STATUS_FXOS_PARAM_ERROR     // invalid parameter is given

} fxos_status_t;

// device handle
typedef struct
{
  /**
   * I2C relevant information
   */

  genericI2cHandle_t protocol;

} handleFXOS_t;

// FXOS8700 settings
typedef struct
{
        odrFXOS_t odr;     // output data-rate selection
        osrFXOS_t osr;     // over-sample ratio selection
       modeFXOS_t mode;    // accelerometer/magnetometer selection
   accRangeFXOS_t range;   // accelerometer full scale range selection
          uint8_t address; // I2C address
         uint16_t baudRate_kbps; // I2C baud-rate

} settingsFXOS_t;

// FXOS8700 accelerometer and magnetometer data struct
typedef struct
{
  /**
   * accelerometer data
   */
  uint8_t accDataXMSB;
  uint8_t accDataXLSB;
  uint8_t accDataYMSB;
  uint8_t accDataYLSB;
  uint8_t accDataZMSB;
  uint8_t accDataZLSB;

  /**
   * magnetometer data
   */
  uint8_t magDataXMSB;
  uint8_t magDataXLSB;
  uint8_t magDataYMSB;
  uint8_t magDataYLSB;
  uint8_t magDataZMSB;
  uint8_t magDataZLSB;

} dataFXOS_t;

#endif

/**
 * project-specific data types
 * Project HEXIWEAR, 2015
 */

#ifndef HG_HEXIWEAR_TYPES
#define HG_HEXIWEAR_TYPES

#include <stdint.h>

#include "MAXIM_info.h"
#include "MAXIM_types.h"

/**
 * raw data structures
 */

typedef union
{
  // vector data
  struct
  {
    // FXOS
    int16_t accData[3];
    int16_t magData[3];

    // FXAS
    int16_t gyroData[3];

  };

  uint8_t allData[ 3*sizeof(int16_t) + 3*sizeof(int16_t) + 3*sizeof(int16_t) ];

} motionData_t;

typedef union
{
  // scalar data
  struct
  {
    // MPL
    int32_t presAltData;
    int16_t tempData;

    // TSL
    uint16_t ambiData[2];

    // HTU
    int16_t humidData;
  };

  uint8_t allData[ sizeof(int32_t) + sizeof(int16_t) + 2*sizeof(uint16_t) + sizeof(int16_t) ];

} weatherData_t;


typedef union
{
  // scalar data
  struct
  {
    // MAXIM
    dataMAXIM_t redLedData  [ MAXIM_FIFO_DEPTH ];
    dataMAXIM_t irLedData   [ MAXIM_FIFO_DEPTH ];
    dataMAXIM_t greenLedData[ MAXIM_FIFO_DEPTH ];
       uint32_t sampNum;
  };

  uint8_t allData[ 3*MAXIM_FIFO_DEPTH*sizeof(dataMAXIM_t) + sizeof(uint32_t) ];

} healthData_t;

typedef int16_t mE_t;

typedef enum
{
  HEXIWEAR_STATUS_SUCCESS,    // success
  HEXIWEAR_STATUS_ERROR,      // fail
  HEXIWEAR_STATUS_INIT_ERROR, // initialization error
  HEXIWEAR_STATUS_POWER_ERROR // power mode error

} hexiwear_status_t;



#endif

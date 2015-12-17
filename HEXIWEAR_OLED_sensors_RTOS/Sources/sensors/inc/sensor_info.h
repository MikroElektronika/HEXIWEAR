/**
 * info related to sensors and their communication
 */

#ifndef HG_SENSOR_INFO
#define HG_SENSOR_INFO

#include "host_mcu_interface.h"

/**
 * define sensors which are present in the system
 */

#define SENSOR_FXOS
#define SENSOR_FXAS
#define SENSOR_MPL
#define SENSOR_HTU
#define SENSOR_TSL
#define SENSOR_MAXIM

/**
 * sensors' tasks stack sizes
 */
#define SENSOR_GET_DATA_STACK_SIZE ( 0x4000 )

/**
 * sensors' tasks priorities
 */
#define SENSOR_GET_DATA_PRIO     ( 11 )

/**
 * motion data format parameters
 *
 * OR the parameters below to create a bit-vector with complete info
 * regarding formatting data
 */

/**
 * sensor data types eligible for format conversions
 * use existing enumerations from hostInterface_packetType_t type
 * occupy bits [3:0] in the bit-vector
 */

#define DATA_TYPE_SHIFT ( 0 )
#define DATA_TYPE_MASK  ( 0x0F << DATA_TYPE_SHIFT )

// battery service
#define DATA_TYPE_BATTERYLEVEL ( packetType_batteryLevel )

// motion service
#define DATA_TYPE_ACCEL ( packetType_accel )
#define DATA_TYPE_MAG   ( packetType_magnet )
#define DATA_TYPE_GYRO  ( packetType_gyro )

// weather service
#define DATA_TYPE_AMBI  ( packetType_ambiLight )
#define DATA_TYPE_TEMP  ( packetType_temperature )
#define DATA_TYPE_HUMID ( packetType_humidity )
#define DATA_TYPE_PRES  ( packetType_pressure )
//#define DATA_TYPE_ALT   ( packetType_altitude )

// health service
#define DATA_TYPE_HR     ( packetType_heartRate )
#define DATA_TYPE_STEPS  ( packetType_steps )
#define DATA_TYPE_ACTIVE ( packetType_activityTime )

/**
 * data formats
 */

// occupy bits [5:4] in the bit-vector
#define DATA_FORMAT_FROM_SHIFT   ( 4 )
#define DATA_FORMAT_FROM_MASK    ( 0x3 << DATA_FORMAT_FROM_SHIFT )
#define DATA_FORMAT_FROM_DEFAULT ( 1 )
#define DATA_FORMAT_FROM_FLOAT   ( 2 )
#define DATA_FORMAT_FROM_mE      ( 3 )


// occupy bits [7:6] in the bit-vector
#define DATA_FORMAT_TO_SHIFT   ( 6 )
#define DATA_FORMAT_TO_MASK    ( 0x3 << DATA_FORMAT_TO_SHIFT )
#define DATA_FORMAT_TO_DEFAULT ( 1 )
#define DATA_FORMAT_TO_FLOAT   ( 2 )
#define DATA_FORMAT_TO_mE      ( 3 )

#endif

// File: sensor_info.h

// Some commonly used macros in the sensors module.

#ifndef _sensor_info_h_
#define _sensor_info_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "host_mcu_interface.h"

////////////////////////////////////////////////////////////////////////////////
// Macro definitions.                                                         //
////////////////////////////////////////////////////////////////////////////////

// Define sensors which are present in the system.

#define SENSOR_FXOS_PRESENT
#define SENSOR_FXAS_PRESENT
#define SENSOR_MPL_PRESENT
#define SENSOR_HTU_PRESENT
#define SENSOR_TSL_PRESENT
#define SENSOR_MAXIM_PRESENT

// Sensors' tasks stack sizes.
#define SENSOR_GET_DATA_STACK_SIZE ( 0x1000 )

#define SENSOR_TAG_BLINK_PERIOD ( 99 )

// Sensors' tasks priorities.
#define SENSOR_GET_DATA_PRIO     ( HEXIWEAR_SENSOR_PRIO )

// Number of retries for sensor read.
#define SENSOR_RETRY_NUM ( 3 )

// Motion data format parameters

// OR the parameters below to create a bit-vector
// with complete info regarding formatting data.

// Sensor data types eligible for format conversions.
// Use existing enumerations from hostInterface_packetType_t type.
// Occupy bits [3:0] in the bit-vector.

#define DATA_TYPE_SHIFT ( 0 )
#define DATA_TYPE_MASK  ( 0x0F << DATA_TYPE_SHIFT )

// Battery service.
#define DATA_TYPE_BATTERYLEVEL ( packetType_batteryLevel )

// Motion service.
#define DATA_TYPE_ACCEL ( packetType_accel )
#define DATA_TYPE_MAG   ( packetType_magnet )
#define DATA_TYPE_GYRO  ( packetType_gyro )

// Weather service.
#define DATA_TYPE_AMBI  ( packetType_ambiLight )
#define DATA_TYPE_TEMP  ( packetType_temperature )
#define DATA_TYPE_HUMID ( packetType_humidity )
#define DATA_TYPE_PRES  ( packetType_pressure )
//#define DATA_TYPE_ALT   ( packetType_altitude )

// Health service.
#define DATA_TYPE_HR       ( packetType_heartRate )
#define DATA_TYPE_STEPS    ( packetType_steps )
#define DATA_TYPE_CALORIES ( packetType_calories )

// Data formats.

// Occupy bits [5:4] in the bit-vector.
#define DATA_FORMAT_FROM_SHIFT   ( 4 )
#define DATA_FORMAT_FROM_MASK    ( 0x3 << DATA_FORMAT_FROM_SHIFT )
#define DATA_FORMAT_FROM_DEFAULT ( 1 )
#define DATA_FORMAT_FROM_FLOAT   ( 2 )
#define DATA_FORMAT_FROM_mE      ( 3 )


// Occupy bits [7:6] in the bit-vector.
#define DATA_FORMAT_TO_SHIFT   ( 6 )
#define DATA_FORMAT_TO_MASK    ( 0x3 << DATA_FORMAT_TO_SHIFT )
#define DATA_FORMAT_TO_DEFAULT ( 0 )
#define DATA_FORMAT_TO_BYTE    ( 1 )
#define DATA_FORMAT_TO_mE      ( 2 )
#define DATA_FORMAT_TO_FLOAT   ( 3 )

// Sensor power constants.
#define SENSOR_ACTIVE_FSL   ( 1 << 0 )
#define SENSOR_ACTIVE_NFSL  ( 1 << 1 )
#define SENSOR_ACTIVE_MAXIM ( 1 << 2 )
#define ADC_ACTIVE_BAT      ( 1 << 3 )

// Default polling periods.

#define ACC_DEFAULT_POLL_PERIOD_MS  ( 400 )
#define MAG_DEFAULT_POLL_PERIOD_MS  ( 400 )
#define GYRO_DEFAULT_POLL_PERIOD_MS ( 400 )

#define TEMP_DEFAULT_POLL_PERIOD_MS ( 60000 )
#define BAT_DEFAULT_POLL_PERIOD_MS  ( 61000 )
#define PRES_DEFAULT_POLL_PERIOD_MS ( 62000 )
#define HUM_DEFAULT_POLL_PERIOD_MS  ( 63000 )
#define LUX_DEFAULT_POLL_PERIOD_MS  ( 64000 )
//#define HR_DEFAULT_POLL_PERIOD_MS   ( 400 )

// Default minimum delay.
#define SENSOR_DEFAULT_MINIMUM_DELAY_MS ( 400 )

#endif
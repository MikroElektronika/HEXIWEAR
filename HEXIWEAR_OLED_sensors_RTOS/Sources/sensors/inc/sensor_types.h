/**
 * data-types related to sensors and their communication
 */

#ifndef HG_SENSOR_TYPES
#define HG_SENSOR_TYPES

#include <stdint.h>
#include "host_mcu_interface.h"
#include "HEXIWEAR_info.h"

#include "TSL_types.h"

/**
 * list of particular sensors
 */
typedef enum
{
  SENSOR_MASK_NONE  =   0,
  SENSOR_MASK_FXOS  =   1 << 0, // compass
  SENSOR_MASK_FXAS  =   1 << 1, // gyroscope
  SENSOR_MASK_MPL   =   1 << 2, // pressure & temperature
  SENSOR_MASK_HTU   =   1 << 3, // humidity
  SENSOR_MASK_TSL   =   1 << 4, // ambient light
  SENSOR_MASK_MAXIM =   1 << 5, // heart-rate

  SENSOR_MASK_ALL   = ( 1 << 6 ) - 1

} sensor_mask_t;

/**
 * list of sensors and other peripherals which feature in data packets
 */
typedef enum
{
  SENSOR_PACKET_ACC,  // compass
  SENSOR_PACKET_MAG,  // compass
  SENSOR_PACKET_GYRO, // gyroscope
  SENSOR_PACKET_PRES, // pressure
  SENSOR_PACKET_TEMP, // temperature
  SENSOR_PACKET_HUM,  // humidity
  SENSOR_PACKET_LUX,  // ambient light
  SENSOR_PACKET_HR,   // heart-rate
  SENSOR_PACKET_BAT,  // battery

  SENSOR_PACKET_ALL

} sensor_packet_t;

typedef enum
{
  SEND_YES,
  SEND_NO,
  SEND_SKIP

} hexiwear_send_t;

typedef struct
{
  uint32_t B_EN_pin;
  uint32_t LDO_EN_pin;
  uint32_t BAT_SENS_EN_pin;
  uint32_t VIBRO_pin;

} sensor_pins_t;

typedef enum
{
  SENSOR_PUSH_NONE  = 0,
  SENSOR_PUSH_KW40  = 0x1 << 0,
  SENSOR_PUSH_OLED  = 0x1 << 1,
  SENSOR_PUSH_FLASH = 0x1 << 2,

  SENSOR_PUSH_ALL   = 0xFF,

} sensor_pushTarget_t;

typedef struct
{
              uint8_t isActive;
  sensor_pushTarget_t targets;
              uint8_t dataType;

} sensor_settings_t;

// formatting pointer
typedef void (*dataConversion_t)(
                                  const void* src,
                                        void* dst,
                                     uint32_t idx
                                );
#endif


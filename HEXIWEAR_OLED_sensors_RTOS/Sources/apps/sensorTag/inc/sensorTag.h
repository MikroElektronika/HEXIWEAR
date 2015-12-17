#ifndef HG_SENSOR_TAG
#define HG_SENSOR_TAG

#include "sensor_driver.h"
#include "sensor_defs.h"

#include "menu_driver.h"

#define SENSOR_TAG_STACK_SIZE ( 0x1000 )
#define SENSOR_TAG_PRIO       ( 10 )

// resources
extern const uint8_t
  sensorTag_bmp[ SCREEN_BYTE_SIZE+6 ];

// screens
extern const menuItem_t
  sensorTag_item;

// task handlers
extern task_handler_t
  sensorTag_handler;

#endif

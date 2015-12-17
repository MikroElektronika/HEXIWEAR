/**
 * global device functions
 * Project HEXIWEAR, 2015
 */

#ifndef HG_HEXIWEAR_DRIVER
#define HG_HEXIWEAR_DRIVER

#include "HEXIWEAR_driver.h"

#include "sensor_driver.h"
#include "host_mcu_interface.h"
#include "menu_driver.h"

/**
 * initialize the tasks
 * @return status flag
 */
hexiwear_status_t HEXIWEAR_Init();

#endif
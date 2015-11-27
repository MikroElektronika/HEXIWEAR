/**
 * Power management
 * Project HEXIWEAR, 2015
 */

#ifndef HG_POWER_DRIVER
#define HG_POWER_DRIVER

#include "power_types.h"

/**
 * [POWER_putToSleep description]
 * @param  peripheral [description]
 * @return            [description]
 */
statusPOWER_t power_putToSleep(
                                periphPOWER_t peripheral
                              );

#endif

/**
 * project-specific data structures
 * Project HEXIWEAR, 2015
 */

#include "HEXIWEAR_defs.h"

/**
 * convert milliseconds to ticks
 */

#define MSEC_TO_TICK(msec)  (((uint32_t)(msec)+500ul/(uint32_t)configTICK_RATE_HZ) \
                             *(uint32_t)configTICK_RATE_HZ/1000ul)
#define TICKS_TO_MSEC(tick) ((tick)*1000ul/(uint32_t)configTICK_RATE_HZ)

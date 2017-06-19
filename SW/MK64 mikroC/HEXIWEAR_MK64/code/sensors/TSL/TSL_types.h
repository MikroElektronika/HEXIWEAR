// File: TSL_types.h

// Some commonly used types in the TSL sensor module.

#ifndef _TSL_types_h_
#define _TSL_types_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>

////////////////////////////////////////////////////////////////////////////////
// Type definitions.                                                          //
////////////////////////////////////////////////////////////////////////////////

typedef enum
{
    TSL_INTEGRATION_TIME_13MS  = 0, // 13.7ms
    TSL_INTEGRATION_TIME_101MS = 1, // 101ms
    TSL_INTEGRATION_TIME_402MS = 2  // 402ms

} integrationTSL_t;

typedef enum
{
    TSL_GAIN_0X  = 0x00, // no gain
    TSL_GAIN_16X = 0x10  // 16x gain

} gainTSL_t;

typedef enum
{
    TSL_CHANNEL_FULL     = 0,
    TSL_CHANNEL_INFRARED = 1

} channelTSL_t;

#endif
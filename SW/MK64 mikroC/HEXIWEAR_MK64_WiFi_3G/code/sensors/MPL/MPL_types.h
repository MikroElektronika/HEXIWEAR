// File: MPL_types.h

// Some commonly used types in the MPL sensor module.

#ifndef _MPL_types_h_
#define _MPL_types_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>

////////////////////////////////////////////////////////////////////////////////
// Type definitions.                                                          //
////////////////////////////////////////////////////////////////////////////////

typedef enum
{
    // oversample factor
    MPL_OS_0,
    MPL_OS_1,
    MPL_OS_2,
    MPL_OS_3,
    MPL_OS_4,
    MPL_OS_5,
    MPL_OS_6,
    MPL_OS_7

} overSampleMPL_t;

typedef enum
{
    MPL_MODE_PRESSURE    = 0,
    MPL_MODE_ALTITUDE    = 1,
    MPL_MODE_TEMPERATURE = 2,
    MPL_MODE_CURRENT     = 0xFF

} modeMPL_t;

#endif
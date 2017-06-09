// File: FXOS_types.h

// Some commonly used types in the FXOS sensor module.

#ifndef _FXOS_types_h_
#define _FXOS_types_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>

#include "FXOS/FXOS_info.h"

////////////////////////////////////////////////////////////////////////////////
// Type definitions.                                                          //
////////////////////////////////////////////////////////////////////////////////

// FXOS8700 output logic data rate selection
typedef enum
{
    fxosODR0 = ( 0 << FXOS_ODR_SHIFT ),
    fxosODR1 = ( 1 << FXOS_ODR_SHIFT ),
    fxosODR2 = ( 2 << FXOS_ODR_SHIFT ),
    fxosODR3 = ( 3 << FXOS_ODR_SHIFT ),
    fxosODR4 = ( 4 << FXOS_ODR_SHIFT ),
    fxosODR5 = ( 5 << FXOS_ODR_SHIFT ),
    fxosODR6 = ( 6 << FXOS_ODR_SHIFT ),
    fxosODR7 = ( 7 << FXOS_ODR_SHIFT )

} odrFXOS_t;

// FXOS8700 oversample ratio selection
typedef enum
{
    fxosOSR0 = ( 0 << FXOS_OSR_SHIFT ),
    fxosOSR1 = ( 1 << FXOS_OSR_SHIFT ),
    fxosOSR2 = ( 2 << FXOS_OSR_SHIFT ),
    fxosOSR3 = ( 3 << FXOS_OSR_SHIFT ),
    fxosOSR4 = ( 4 << FXOS_OSR_SHIFT ),
    fxosOSR5 = ( 5 << FXOS_OSR_SHIFT ),
    fxosOSR6 = ( 6 << FXOS_OSR_SHIFT ),
    fxosOSR7 = ( 7 << FXOS_OSR_SHIFT )

} osrFXOS_t;

// FXOS8700 accelerometer/magnetometer selection
typedef enum
{
    fxosAccOnly = ( 0 << FXOS_MODE_SHIFT ), // accelerometer only
    fxosMagOnly = ( 1 << FXOS_MODE_SHIFT ), // magnetometer only
    fxosBoth    = ( 3 << FXOS_MODE_SHIFT )  // select both accel and magnet

} modeFXOS_t;

// FXOS8700 accelerometer full-scale range
typedef enum
{
    fxosRange2g = ( 0 << FXOS_ACCRANGE_SHIFT ), // 2g mode
    fxosRange4g = ( 1 << FXOS_ACCRANGE_SHIFT ), // 4g mode
    fxosRange8g = ( 2 << FXOS_ACCRANGE_SHIFT )  // 8g mode

} accRangeFXOS_t;

#endif
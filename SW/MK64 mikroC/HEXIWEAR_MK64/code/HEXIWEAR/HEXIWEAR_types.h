// File: HEXIWEAR_types.h

// Some commonly used types in the HEXIWEAR module.

#ifndef _HEXIWEAR_types_h_
#define _HEXIWEAR_types_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>

#include "..\sensors\MAXIM\MAXIM_info.h"
#include "..\sensors\MAXIM\MAXIM_types.h"

////////////////////////////////////////////////////////////////////////////////
// Type definitions.                                                          //
////////////////////////////////////////////////////////////////////////////////

// Raw data structures.

typedef union
{
    // vector data
    struct
    {
        // FXOS
        int16_t accData[3];
        int16_t magData[3];

        // FXAS
        int16_t gyroData[3];
    };

    uint8_t allData[ 3 * sizeof( int16_t )
        + 3 * sizeof( int16_t ) + 3 * sizeof( int16_t ) ];
    
} motionData_t;

typedef union
{
    // scalar data
    struct
    {
        // MPL
        int32_t presAltData;

        // TSL
        uint8_t ambiData;

        // HTU
        uint16_t humidData;
        int16_t tempData;
    };

    uint8_t allData[ sizeof( int32_t ) + sizeof( uint8_t )
        + sizeof( uint16_t ) + sizeof( int16_t ) ];

} weatherData_t;

typedef int16_t mE_t;

typedef enum
{
    HEXIWEAR_STATUS_SUCCESS,    // success
    HEXIWEAR_STATUS_ERROR,      // fail
    HEXIWEAR_STATUS_INIT_ERROR, // initialization error
    HEXIWEAR_STATUS_POWER_ERROR // power mode error

} hexiwear_status_t;

typedef struct
{
    uint8_t isON_SensorTag;
    uint8_t isON_Haptic;

    // space for additional flags
    uint8_t padding[6];

} hexiwear_flags_t;

typedef enum
{
    HEXIWEAR_TIMER_SENSOR

} hexiwear_timer_t;

typedef struct name
{
    uint8_t ver_patchNumber;
    uint8_t ver_minorNumber;
    uint8_t ver_majorNumber;

} hexiwear_version_t;

typedef struct
{
    uint8_t hexiwear_major_ver; // hexiwear version
    uint8_t hexiwear_minor_ver; // hexiwear version
    uint8_t hexiwear_patch_ver; // hexiwear version
    uint8_t hexiwear_build_ver; // hexiwear version

    uint8_t pcb_main_ver; // main pcb version
    uint8_t pcb_hr_ver;   // heart-rate pcb version
    uint8_t pcb_cs_ver;   // capSense pcb version

    uint8_t padding;

} hexiwear_hw_rev_t;

#endif
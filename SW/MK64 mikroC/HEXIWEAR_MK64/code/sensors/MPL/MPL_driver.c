// File: MPL_driver.c

// Definitions of main functionalities in the MPL sensor module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////
 
#include <string.h>

#include "MPL_info.h"
#include "MPL_types.h"
#include "MPL_driver.h"

#include "OSA.h"

#include "HEXIWEAR_types.h"

////////////////////////////////////////////////////////////////////////////////
// Static variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Variable which denotes the sensor working as altimeter/barometer.
static modeMPL_t selectedMode;

static uint16_t selectedSampleRate;
static uint16_t selectedDelay;

// oversample factor
static uint16_t overSampleFactors[] = { 1,  2,  4,  8, 16,  32,  64, 128 };
// min. time between data samples in [ms]
static uint16_t overSampleDelays[]  = { 6, 10, 18, 34, 66, 130, 258, 512 };

// Buffer for I2C data.
static uint8_t buffer[2];

////////////////////////////////////////////////////////////////////////////////
// Static function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Reads a single byte from the sensor register at the given address.
static uint8_t MPL_ReadSingle( uint8_t rdAddr )
{
    buffer[0] = rdAddr;
    I2C1_Start();
    I2C1_Write( MPL_I2C_ADDRESS, buffer, 1, END_MODE_RESTART );
    I2C1_Read( MPL_I2C_ADDRESS, buffer, 1, END_MODE_STOP );

    return buffer[0];
}

// Writes the given byte to the sensor register at the given address.
static void MPL_WriteSingle( uint8_t wrAddr, uint8_t wrData )
{
    buffer[1] = wrData;
    buffer[0] = wrAddr;
    I2C1_Start();
    I2C1_Write( MPL_I2C_ADDRESS, buffer, 2, END_MODE_STOP );
}

////////////////////////////////////////////////////////////////////////////////
// Global function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Initialises the MAXIM sensor.
void MPL_Init()
{
    I2C1_Init_Advanced( 400000, &_GPIO_Module_I2C1_PC10_11 );
    
    // Reset.
    MPL_SoftReset();
    
    // Goto standby.
    MPL_GotoStandby();
    
    // Set the mode.
    MPL_SetMode( MPL_MODE_PRESSURE );
    
    // Set over-sampling.
    MPL_SetOversampleRate( MPL_OS_0 );
    
    // Enable the flags.
    MPL_EnableEventFlags();
    
    // Goto active state.
    MPL_SetActive();
}

// Performs a software reset of the sensor.
uint8_t MPL_SoftReset()
{
    uint8_t counter         = 0;
    uint8_t controlSettings = 0;
    
    controlSettings = MPL_ReadSingle( MPL_CTRL_REG1 );
    
    // Set RST bit and write it back.
    controlSettings |= ( 1 << MPL_RST_SHIFT );
    
    MPL_WriteSingle( MPL_CTRL_REG1, controlSettings );

    OSA_TimeDelay( 15 );
    
    // By the end of the boot process the RST bit should be de-asserted to 0.
    while( 1 )
    {
        controlSettings = MPL_ReadSingle( MPL_CTRL_REG1 );
        
        if( ( controlSettings & ( 1 << MPL_RST_SHIFT ) ) != 0 )
        {
            // Error out after ~0.5 s for a read.
            if( ++counter > 5 )
            {
                return 1;
            }
        }
        else
        {
            return 0;
        }
    }
}

// Clears then sets the OST bit which causes the sensor
// to immediately take another reading.
void MPL_ToggleOneShot()
{
    uint8_t controlSettings = 0;
    
    // Read current settings.
    controlSettings = MPL_ReadSingle( MPL_CTRL_REG1 );
    
    // Clear OST bit and write it back.
    controlSettings &= ~( 1 << MPL_OST_SHIFT );
    MPL_WriteSingle( MPL_CTRL_REG1, controlSettings );
    
    // Read the settings again, just to be safe.
    controlSettings = MPL_ReadSingle( MPL_CTRL_REG1 );
    
    // Set OST bit and write it back.
    controlSettings |= ( 1 << MPL_OST_SHIFT );
    MPL_WriteSingle( MPL_CTRL_REG1, controlSettings );
}

// Sets the device to be barometer or altimeter.
void MPL_SetMode( modeMPL_t mode )
{
    uint8_t controlSettings;
    
    controlSettings = MPL_ReadSingle( MPL_CTRL_REG1 );
    
    // Set/clear ALT bit.
    if( mode == MPL_MODE_PRESSURE )
        controlSettings &= ~( ( uint8_t )( 1 << 7 ) );
    else
        controlSettings |= ( 1 << 7 );

    MPL_WriteSingle( MPL_CTRL_REG1, controlSettings );
    
    // Update the static variable.
    selectedMode = mode;
}

// Puts the sensor in stand-by mode.
// This is needed so that we can modify the major control registers.
void MPL_GotoStandby()
{
    uint8_t controlSettings;
    
    controlSettings = MPL_ReadSingle( MPL_CTRL_REG1 );
    
    // Clear SBYB bit for entering stand-by mode.
    controlSettings &= ~( ( uint8_t )( 1 << MPL_SBYB_SHIFT ) );
    MPL_WriteSingle( MPL_CTRL_REG1, controlSettings );
}

// Puts the sensor in active mode.
void MPL_SetActive()
{
    uint8_t controlSettings;

    controlSettings = MPL_ReadSingle( MPL_CTRL_REG1 );
    
    // set SBYB bit for entering active mode
    controlSettings |= ( 1 << MPL_SBYB_SHIFT );
    MPL_WriteSingle( MPL_CTRL_REG1, controlSettings );
}

// Sets the oversample rate.
void MPL_SetOversampleRate( uint8_t sampleRate )
{
    uint8_t controlSettings;
    
    if( sampleRate > 7 )
    {
        // Rate cannot be larger than 7.
        sampleRate = 7;
    }
    
    selectedSampleRate = overSampleFactors[sampleRate];
    selectedDelay      = overSampleDelays[sampleRate];
    
    controlSettings = MPL_ReadSingle( MPL_CTRL_REG1 );
    
    // Clear out old OS bits.
    controlSettings &= ~MPL_OS_MASK;
    // Mask in new OS bits.
    controlSettings |= ( sampleRate << MPL_OS_SHIFT );
    MPL_WriteSingle( MPL_CTRL_REG1, controlSettings );
}

// Enables the pressure and temp measurement event flags
// so that we can test against them.
void MPL_EnableEventFlags()
{
    uint8_t controlSettings = 0x07;
    
    MPL_WriteSingle( PT_DATA_CFG, controlSettings );
}

// Reads raw sensor data.
uint8_t MPL_ReadRawData( modeMPL_t mode, uint16_t* sensorData )
{
    uint8_t dataReadyFlag;
    uint8_t readAddr;
    uint8_t statVal;

    uint32_t tmp;
    int16_t counter;

    // Buffer for pressure/altitude and temperature sensor.
    uint8_t buf[5];
    
    // Set the new working mode, if given one.
    if( ( mode > MPL_MODE_TEMPERATURE ) && ( mode < MPL_MODE_CURRENT ) )
    {
        return 1; // error
    }
    
    if( ( MPL_MODE_CURRENT != mode ) && ( selectedMode != mode ) )
    {
        // Goto standby.
        MPL_GotoStandby();
        // Set the mode.
        MPL_SetMode( mode );
        // Goto active state.
        MPL_SetActive();
    }
    
    // Prepare for reading data.
    switch( selectedMode )
    {
        case MPL_MODE_PRESSURE:
        case MPL_MODE_ALTITUDE:
            dataReadyFlag  = 1 << MPL_PDR_SHIFT;
            break;

        case MPL_MODE_TEMPERATURE:
            dataReadyFlag = 1 << MPL_TDR_SHIFT;
            break;

        default:
            break;
    }

    statVal = MPL_ReadSingle( REG_STATUS );
    
    // Check PDR/TDR bit; if it's not set, toggle OST.
    if( ( statVal & dataReadyFlag ) == 0 )
    {
        // Toggle the OST bit.
        MPL_ToggleOneShot();
    }
    
    // Wait for the data acquisition time.
    OSA_TimeDelay( selectedDelay + 5 );

    counter = 0;
    // Wait for PDR/PTR bit, which indicates that we have new data.
    while( 1 )
    {
        statVal = MPL_ReadSingle( REG_STATUS );
        
        if( ( statVal & dataReadyFlag ) == 0 )
        {
            // Error out after more than 0.5s for a read op.
            if( ++counter > 5 )
            {
                return 1; // error
            }
        }
        else
        {
            // Continue with the program.
            break;
        }
    }

    // Read sensor data.
    readAddr = OUT_P_MSB;
    I2C1_Start();
    I2C1_Write( MPL_I2C_ADDRESS, &readAddr, 1, END_MODE_RESTART );
    I2C1_Read( MPL_I2C_ADDRESS, buf, 5, END_MODE_STOP );

    // Save data.
    switch( selectedMode )
    {
        // Pressure value is a Q18.2 right-aligned number in [Pa].
        case MPL_MODE_PRESSURE:
        // Altitude value is a Q16.4 right-aligned number in [m].
        case MPL_MODE_ALTITUDE:
        {
            // save pressure/altitude
            //                   MSB
            tmp = ( ( ( int32_t )buf[0] << 16 )
            //                   CSB
                  | ( ( int32_t )buf[1] << 8 )
            //                   LSB
                  | ( ( int32_t )buf[2] )
            //    discard first 4 bits
                  ) >> 4;

            // Pack it into the first two integers in the output array.
            memcpy( sensorData, &tmp, sizeof( tmp ) );

            break;
        }

        // temperature value is a Q8.4 right-aligned number in [C]
        case MPL_MODE_TEMPERATURE:
        {
            // save temperature         
            //                          MSB
            *sensorData =( ( ( int16_t )buf[3] << 4 )
            //                          LSB
                         | ( ( int16_t )buf[4] >> 4 ) );

            break;
        }

        default:
            break;
    }
    
    return 0;
}

// Formats raw data to float.
float MPL_FormatFloat( int32_t input )
{
    return ( float )input / 4.0;
}

// Formats raw data to int.
int16_t MPL_FormatInt( int32_t input )
{
    // Convert data to [kPa].
    return ( int16_t )( ( ( float )input / ( 4.0 * 1000 ) ) * 100 );
}

// Formats raw to float.
void pres_fmtDef2Float(
                        const void* src,
                              void* dst,
                           uint32_t idx
                      )
{
    // helper pointers
    int32_t* input = ( int32_t* )src;
    float* output = ( float* )dst;

    // convert data
    output[idx] = MPL_FormatFloat( input[idx] );
}

// Formats raw to mE format.
void pres_fmtDef2Me(
                     const void* src,
                           void* dst,
                        uint32_t idx
                   )
{
    // helper pointers
    int32_t* input = ( int32_t* )src;
    mE_t* output = ( mE_t* )dst;

    // convert data to [kPa]
    output[idx] = ( mE_t )MPL_FormatInt( input[idx] );
}

// Formats raw to byte - currently unimplemented.
void pres_fmtDef2Byte(
                       const void* src,
                             void* dst,
                          uint32_t idx
                     )
{}
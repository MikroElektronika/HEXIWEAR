// File: TSL_driver.c

// Definitions of main functionalities in the TSL sensor module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include <string.h>

#include "TSL_info.h"
#include "TSL_types.h"
#include "TSL_driver.h"

#include "OSA.h"

#include "HEXIWEAR_types.h"

////////////////////////////////////////////////////////////////////////////////
// Static variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

static gainTSL_t selectedGain;

static integrationTSL_t selectedTiming;

// Buffer for I2C data.
static uint8_t buffer[2];

////////////////////////////////////////////////////////////////////////////////
// Static function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Reads a single byte from the sensor register at the given address.
static uint8_t TSL_ReadSingle( uint8_t rdAddr )
{
    buffer[0] = rdAddr;
    I2C0_Start();
    I2C0_Write( TSL_I2C_ADDRESS, buffer, 1, END_MODE_RESTART );
    I2C0_Read( TSL_I2C_ADDRESS, buffer, 1, END_MODE_STOP );

    return buffer[0];
}

// Writes the given byte to the sensor register at the given address.
static void TSL_WriteSingle( uint8_t wrAddr, uint8_t wrData )
{
    buffer[1] = wrData;
    buffer[0] = wrAddr;
    I2C0_Start();
    I2C0_Write( TSL_I2C_ADDRESS, buffer, 2, END_MODE_STOP );
}

////////////////////////////////////////////////////////////////////////////////
// Global function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Initialises the TSL sensor.
void TSL_Init()
{
    I2C0_Init_Advanced( 400000, &_GPIO_Module_I2C0_PB0_1 );
    
    // Power cycle the module.
    TSL_Disable();
    TSL_Enable();
    
    // Set default integration time and gain.
    TSL_SetGain( TSL_GAIN_16X );
    TSL_SetTiming( TSL_INTEGRATION_TIME_13MS );
}

// Deinitialises the sensor.
void TSL_Deinit()
{
    TSL_Disable();
}

// Enables the sensor.
void TSL_Enable()
{
    TSL_WriteSingle( TSL_COMMAND_BIT | TSL_REG_CONTROL, TSL_CONTROL_POWERON );
}

// Disables the sensor.
void TSL_Disable()
{
    TSL_WriteSingle( TSL_COMMAND_BIT | TSL_REG_CONTROL, TSL_CONTROL_POWEROFF );
}

// Sets sensor gain.
void TSL_SetGain( gainTSL_t gain )
{
    TSL_WriteSingle(
        TSL_COMMAND_BIT | TSL_REG_TIMING, selectedGain | selectedTiming );

    selectedGain = gain;
}

// Sets sensor integration time.
void TSL_SetTiming( integrationTSL_t integration )
{
    TSL_WriteSingle(
        TSL_COMMAND_BIT | TSL_REG_TIMING, selectedGain | selectedTiming );

    selectedTiming = integration;
}

// Reads raw sensor data.
void TSL_ReadRawData( channelTSL_t channel, uint16_t* sensorData )
{
    uint8_t regData[1];
    uint8_t dataLow  = 0;
    uint8_t dataHigh = 0;

    switch( channel )
    {
        // Read ADC channel 0 (Visible and IR).
        case TSL_CHANNEL_FULL:
            dataLow = TSL_ReadSingle( TSL_COMMAND_BIT | TSL_REG_CHAN0_LOW );
            dataHigh = TSL_ReadSingle( TSL_COMMAND_BIT | TSL_REG_CHAN0_HIGH );
            
            *sensorData++ = ( dataLow | ( ( uint16_t )dataHigh << 8 ) );

        // Read ADC channel 1 (IR only).
        case TSL_CHANNEL_INFRARED:
            dataLow = TSL_ReadSingle( TSL_COMMAND_BIT | TSL_REG_CHAN1_LOW );
            dataHigh = TSL_ReadSingle( TSL_COMMAND_BIT | TSL_REG_CHAN1_HIGH );
            
            *sensorData = ( dataLow | ( ( uint16_t )dataHigh << 8 ) );
            
            break;

        default:
            break;
    }
}

// Calculates luminance.
void TSL_CalculateLux( uint16_t* channelValues, uint32_t* luxVal )
{
    uint32_t chScale;
    uint32_t channel0;
    uint32_t channel1;
    uint32_t temp;
    uint32_t ratio;

    uint32_t ratio1 = 0;

    uint16_t b;
    uint16_t m;

    uint16_t ch0 = channelValues[0];
    uint16_t ch1 = channelValues[1];
    
    switch( selectedTiming )
    {
        // 13.7 msec
        case 0:
            chScale = TSL_CHSCALE_TINT0;
            break;

        // 101 msec
        case 1:
            chScale = TSL_CHSCALE_TINT1;
            break;

        // no scaling ... integration time = 402ms
        default:
            chScale = 1 << TSL_CHSCALE;
            break;
    }
    
    // Scale for gain (1x or 16x).
    if( selectedGain == 0 )
    {
        chScale <<= 4;
    }
    
    // Scale the channel values.
    channel0 = ( ch0 * chScale ) >> TSL_CHSCALE;
    channel1 = ( ch1 * chScale ) >> TSL_CHSCALE;
    
    // Find the ratio of the channel values (Channel1/Channel0).
    // Protect against divide by zero.
    if( channel0 != 0 )
    {
        ratio1 = ( channel1 << ( 1 + TSL_RATIO_SCALE ) ) / channel0;
    }
    
    // Round the ratio value.
    ratio = ( 1 + ratio1 ) >> 1;
    
    if( ( ratio >= 0 ) && ( ratio <= TSL_K1T ) )
    {
        b = TSL_B1T;
        m = TSL_M1T;
    }
    else if ( ratio <= TSL_K2T )
    {
        b = TSL_B2T;
        m = TSL_M2T;
    }
    else if ( ratio <= TSL_K3T )
    {
        b = TSL_B3T;
        m = TSL_M3T;
    }
    else if ( ratio <= TSL_K4T )
    {
        b = TSL_B4T;
        m = TSL_M4T;
    }
    else if ( ratio <= TSL_K5T )
    {
        b = TSL_B5T;
        m = TSL_M5T;
    }
    else if ( ratio <= TSL_K6T )
    {
        b = TSL_B6T;
        m = TSL_M6T;
    }
    else if ( ratio <= TSL_K7T )
    {
        b = TSL_B7T;
        m = TSL_M7T;
    }
    else if ( ratio > TSL_K8T )
    {
        b = TSL_B8T;
        m = TSL_M8T;
    }
    
    temp = ( ( channel0 * b ) - ( channel1 * m ) );
    
    // Do not allow negative lux value.
    if( temp < 0 )
    {
        temp = 0;
    }
    
    // Round lsb ( 2^(LUX_SCALE-1) ).
    temp = temp + ( 1 << ( TSL_LUX_SCALE -1 ) );

    // Strip off fractional portion.
    *luxVal = temp >> TSL_LUX_SCALE;
}

// Converts lux value to light percentage.
void TSL_FormatLux( uint32_t luxVal, uint8_t* ambLight )
{
    if( luxVal < 128 )
    {
        *ambLight = ( luxVal * 100 ) >> 7;
    }
    else
    {
        *ambLight = 100;
    }
}

// Formats raw to float.
void ambi_fmtDef2Float(
                        const void* src,
                              void* dst,
                           uint32_t idx
                      )
{
    // helper pointers
    uint16_t* input = ( uint16_t* )src;
    float* output = ( float* )dst;

    // convert data
    output[idx] = ( float )input[idx];
}

// Formats raw to mE format - currently unimplemented.
void ambi_fmtDef2Me(
                     const void* src,
                           void* dst,
                        uint32_t idx
                   )
{}

// Formats raw to byte format.
void ambi_fmtDef2Byte(
                       const void* src,
                             void* dst,
                          uint32_t idx
                     )
{
    // helper pointers
    uint8_t* input = ( uint8_t* )src;
    uint8_t* output = ( uint8_t* )dst;

    // convert data
    output[idx] = ( uint8_t )( input[idx] );
}
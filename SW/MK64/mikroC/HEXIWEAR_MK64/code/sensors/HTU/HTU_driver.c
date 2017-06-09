// File: HTU_driver.c

// Definitions of main functionalities in the HTU sensor module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include <string.h>

#include "HTU_info.h"
#include "HTU_types.h"
#include "HTU_driver.h"

#include "OSA.h"

#include "HEXIWEAR_types.h"

////////////////////////////////////////////////////////////////////////////////
// Static variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// bit resolution
static bitResHTU_t bitRes;

// measurement time for temperature and humidity (in ms)
static uint16_t temp_meas_time;
static uint16_t hum_meas_time;

// buffer for I2C data
static uint8_t buffer[2];

////////////////////////////////////////////////////////////////////////////////
// Static function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////
 
// Reads a single byte from the sensor register at the given address.
static uint8_t HTU_ReadSingle( uint8_t rdAddr )
{
    buffer[0] = rdAddr;
    I2C0_Start();
    I2C0_Write( HTU_I2C_ADDRESS, buffer, 1, END_MODE_RESTART );
    I2C0_Read( HTU_I2C_ADDRESS, buffer, 1, END_MODE_STOP );

    return buffer[0];
}

// Writes the given byte to the sensor register at the given address.
static void HTU_WriteSingle( uint8_t wrAddr, uint8_t wrData )
{
    buffer[1] = wrData;
    buffer[0] = wrAddr;
    I2C0_Start();
    I2C0_Write( HTU_I2C_ADDRESS, buffer, 2, END_MODE_STOP );
}

////////////////////////////////////////////////////////////////////////////////
// Global function declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

// Initialises the HTU sensor.
void HTU_Init()
{
    bitRes = BITRES_HTU_RH_8_TEMP12;
    
    I2C0_Init_Advanced( 400000, &_GPIO_Module_I2C0_PB0_1 );
    
    HTU_SoftReset();
    HTU_SetUserRegister();
}

// Resets the sensor.
void HTU_SoftReset()
{
    buffer[0] = HTU21D_SOFT_RESET;
    I2C0_Start();
    I2C0_Write( HTU_I2C_ADDRESS, buffer, 1, END_MODE_STOP );
}

// Configures the measurement resolution.
void HTU_SetUserRegister()
{
    uint8_t txBuff;
    
    switch( bitRes )
    {
        // RH: 12bit, TEMP: 14bit
        case BITRES_HTU_RH_12_TEMP14:
            txBuff         = 0x2;
            temp_meas_time = 50;
            hum_meas_time  = 16;
            break;
        
        // RH: 8bit, TEMP: 12bit
        case BITRES_HTU_RH_8_TEMP12:
            txBuff         = 0x3;
            temp_meas_time = 13;
            hum_meas_time  = 3;
            break;
            
        // RH: 10bit, TEMP: 13bit
        case BITRES_HTU_RH_10_TEMP13:
            txBuff         = 0x82;
            temp_meas_time = 25;
            hum_meas_time  = 5;
            break;
            
        // RH: 11bit, TEMP: 11bit
        case BITRES_HTU_RH_11_TEMP11:
            txBuff         = 0x83;
            temp_meas_time = 7;
            hum_meas_time  = 8;
            break;

        default:
            break;
    }
    
    HTU_WriteSingle( HTU21D_WRITE_USER_REG, txBuff );
}

// Retrieves temperature data.
void HTU_GetTemp( int16_t* tempData )
{
    uint8_t regAddr;
    uint8_t rxBuff[3];

    *tempData = - 1;

    regAddr = HTU21D_TRIGGER_TEMP_NOHOLD;
    I2C0_Start();
    I2C0_Write( HTU_I2C_ADDRESS, &regAddr, 1, END_MODE_RESTART );
    OSA_TimeDelay( temp_meas_time + 5 );
    I2C0_Read( HTU_I2C_ADDRESS, rxBuff, 3, END_MODE_STOP );

    // Convert to final value.
    // Discard the third received byte (checksum).
    *tempData = ( ( uint16_t )rxBuff[0] << 8 )
              | ( ( uint16_t )rxBuff[1] & 0xFC );
}

// Retrieves humidity data.
void HTU_GetHum( int16_t* humData )
{
    uint8_t regAddr;
    uint8_t rxBuff[3];

    *humData = - 1;

    regAddr = HTU21D_TRIGGER_HUMD_NOHOLD;
    I2C0_Start();
    I2C0_Write( HTU_I2C_ADDRESS, &regAddr, 1, END_MODE_RESTART );
    OSA_TimeDelay( hum_meas_time + 5 );
    I2C0_Read( HTU_I2C_ADDRESS, rxBuff, 3, END_MODE_STOP );

    // Convert to final value.
    // Discard the third received byte (checksum).
    *humData = ( ( uint16_t )rxBuff[0] << 8 )
             | ( ( uint16_t )rxBuff[1] & 0xFC );
}

// Retrieves temperature and humidity data.
void HTU_ReadRawData( int16_t* temperature, int16_t* humidity )
{
    HTU_GetTemp( temperature );
    HTU_GetHum( humidity );
}

// Formats raw humidity data to float.
float HTU_HumFormatFloat( uint16_t input )
{
    float temp;

    // Convert data.
    temp = -6 + 125 * ( ( float )input / 0x10000 );

    if( temp > 100 )
    {
        temp = 100;
    }
    else if ( temp < 0 )
    {
        temp = 0;
    }
    
    return temp;
}

// Formats raw humidity data to int.
int16_t HTU_HumFormatInt( uint16_t input )
{
    float temp;

    // Convert data.
    temp = HTU_HumFormatFloat( input );

    return ( int16_t )( temp * 100 );
}

// Formats raw temperature data to int.
float HTU_TempFormatFloat( uint16_t input )
{
    // Convert data.
    return ( float )( ( ( 175.72 * ( float )input ) / 65536.0 ) - 46.85 );
}

// Formats raw temperature data to int.
int16_t HTU_TempFormatInt( uint16_t input )
{
    float temp;
    uint8_t calibConst;

    // Convert data.
    temp = HTU_TempFormatFloat( input );

    if ( temp < 16 )
    {
        calibConst = HTU_TEMP_CALIB_OFFSET_0;
    }
    else if ( temp < 32 )
    {
        calibConst = HTU_TEMP_CALIB_OFFSET_1;
    }
    else
    {
        calibConst = HTU_TEMP_CALIB_OFFSET_2;
    }

    return ( int16_t )( ( temp - calibConst ) * 100 );
}

// Formats raw to float.
void hum_fmtDef2Float(
                       const void* src,
                             void* dst,
                          uint32_t idx
                     )
{
    // helper pointers
    int16_t* input = ( int16_t* )src;
    float* output = ( float* )dst;

    // convert data
    output[idx] = HTU_HumFormatFloat( input[idx] );
}

// Formats raw to mE format.
void hum_fmtDef2Me(
                    const void* src,
                          void* dst,
                       uint32_t idx
                  )
{
    // helper pointers
    uint16_t* input = ( uint16_t* )src;
    mE_t* output = ( mE_t* )dst;

    // convert data
    output[idx] = ( mE_t )HTU_HumFormatInt( input[idx] );
}

// Formats raw to byte - currently unimplemented.
void hum_fmtDef2Byte(
                      const void* src,
                            void* dst,
                         uint32_t idx
                    )
{}

// Formats raw to float.
void temp_fmtDef2Float(
                        const void* src,
                              void* dst,
                           uint32_t idx
                      )
{
    // helper pointers
    int16_t* input = ( int16_t* )src;
    float* output = ( float* )dst;

    // convert data
    output[idx] = HTU_TempFormatFloat( input[idx] );
}

// Formats raw to mE format.
void temp_fmtDef2Me(
                     const void* src,
                           void* dst,
                        uint32_t idx
                   )
{
    // helper pointers
    uint16_t* input = ( uint16_t* )src;
    mE_t* output = ( mE_t* )dst;

    // convert data
    output[idx] = HTU_TempFormatInt( input[idx] );
}

// Formats raw to byte - currently unimplemented.
void temp_fmtDef2Byte(
                       const void* src,
                             void* dst,
                          uint32_t idx
                     )
{}
// File: FXAS_driver.c

// Definitions of main functionalities in the FXAS sensor module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <string.h>

#include "FXAS_info.h"
#include "FXAS_types.h"
#include "FXAS_driver.h"

#include "OSA.h"

#include "HEXIWEAR_types.h"

////////////////////////////////////////////////////////////////////////////////
// Static variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////
 
static uint16_t selectedDPS = GFSR_2000DPS;

// sensitivity coefficients
static float gyro_sensCoefs[] =  {
    0.0625,    // 1000 dps
    0.03125,   // 500  dps
    0.015625,  // 250  dps
    0.0078125  // 125  dps
};

// Buffer for I2C data.
static uint8_t buffer[2];

////////////////////////////////////////////////////////////////////////////////
// Global function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Reads a single byte from the sensor register at the given address.
static uint8_t FXAS_ReadSingle( uint8_t rdAddr )
{
    buffer[0] = rdAddr;
    I2C1_Start();
    I2C1_Write( FXAS_I2C_ADDR, buffer, 1, END_MODE_RESTART );
    I2C1_Read( FXAS_I2C_ADDR, buffer, 1, END_MODE_STOP );
    
    return buffer[0];
}

// Writes the given byte to the sensor register at the given address.
static void FXAS_WriteSingle( uint8_t wrAddr, uint8_t wrData )
{
    buffer[1] = wrData;
    buffer[0] = wrAddr;
    I2C1_Start();
    I2C1_Write( FXAS_I2C_ADDR, buffer, 2, END_MODE_STOP );
}

////////////////////////////////////////////////////////////////////////////////
// Global function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////
 
// Initialises the FXAS sensor.
void FXAS_Init()
{
    I2C1_Init_Advanced( 400000, &_GPIO_Module_I2C1_PC10_11 );
    
    FXAS_GotoStandby();
    
    // Setup the scale range in dps (degrees per second).
    selectedDPS = GFSR_250DPS;
    FXAS_WriteSingle( FXAS_H_CTRL_REG0, selectedDPS );
    
    // Setup the data rate bits [4:2].
    FXAS_WriteSingle( FXAS_H_CTRL_REG1, GODR_200HZ << 2 );
    
    // Disable FIFO, route FIFO and rate threshold interrupts to INT2,
    // enable data ready interrupt, route to INT1 active HIGH,
    // push-pull output driver on interrupts.
    FXAS_WriteSingle( FXAS_H_CTRL_REG2, 0x0E );
    
    // Set up rate threshold detection;
    // at max rate threshold = FSR;  rate threshold = THS*FSR/128.
    // Enable rate threshold detection on all axes.
    FXAS_WriteSingle( FXAS_H_RT_CFG, 0x07 );
    
    // Unsigned 7-bit THS, set to one-tenth FSR; set clearing debounce counter.
    FXAS_WriteSingle( FXAS_H_RT_THS, 0x0D );
    
    // Set to 4 (can set up to 255).
    FXAS_WriteSingle( FXAS_H_RT_COUNT, 0x04 );

    // Set the sensor to active mode.
    FXAS_SetActive();
}

// Reads raw data from the sensor. Requires a 3 element array.
void FXAS_ReadRawData( int16_t* sensorData )
{
    uint8_t tmp;
    uint8_t fxasData[6];

    tmp = FXAS_H_OUT_X_MSB;
    I2C1_Start();
    I2C1_Write( FXAS_I2C_ADDR, &tmp, 1, END_MODE_RESTART );
    I2C1_Read( FXAS_I2C_ADDR, fxasData, 6, END_MODE_STOP );

    sensorData[0] = ( ( uint16_t )fxasData[0] << 8 ) | fxasData[1];
    sensorData[1] = ( ( uint16_t )fxasData[2] << 8 ) | fxasData[3];
    sensorData[2] = ( ( uint16_t )fxasData[4] << 8 ) | fxasData[5];
}

// Puts the sensor into standby mode.
void FXAS_GotoStandby()
{
    uint8_t tmp;

    // Read the control register 1.
    tmp = FXAS_ReadSingle( FXAS_H_CTRL_REG1 );
    
    // Clear bits 0 and 1 to enter standby mode.
    tmp &= ~0x03;
    FXAS_WriteSingle( FXAS_H_CTRL_REG1, tmp );
}

// Sets the sensor to ready mode.
void FXAS_GetReady()
{
    uint8_t tmp;

    // Read the control register 1.
    tmp = FXAS_ReadSingle( FXAS_H_CTRL_REG1 );
    
    // Clear bits 0 and 1 to enter standby mode.
    FXAS_WriteSingle( FXAS_H_CTRL_REG1, tmp & ~0x03 );
    
    // Set bit 0 to 1, ready mode.
    FXAS_WriteSingle( FXAS_H_CTRL_REG1, tmp | 0x01 );
}

// Puts the sensor into active mode.
void FXAS_SetActive()
{
    uint8_t tmp;

    // Read the control register 1.
    tmp = FXAS_ReadSingle( FXAS_H_CTRL_REG1 );
    
    // Clear bits 0 and 1 to enter standby mode.
    FXAS_WriteSingle( FXAS_H_CTRL_REG1, tmp & ~0x03 );

    // Set bit 1 to 1, active mode, data acquisition enabled.
    FXAS_WriteSingle( FXAS_H_CTRL_REG1, tmp | 0x02 );
}

// Resets the module.
void FXAS_SoftReset()
{
    // Set reset bit to 1 to assert software reset to zero
    // at end of boot process.
    FXAS_WriteSingle( FXAS_H_CTRL_REG1, 0x40 );
    
    OSA_TimeDelay( 100 );
    
    // Wait for boot end flag to be set.
    do
    {
        buffer[0] = FXAS_ReadSingle( FXAS_H_INT_SRC_FLAG );
    }
    while( ( buffer[0] & 0x08 ) == 0 );
}

// Get current sensitivity.
float FXAS_GetSens()
{
    return gyro_sensCoefs[selectedDPS];
}

// Formats raw data to float.
float FXAS_FormatFloat( int16_t input )
{
    // Convert data.
    return ( float )input * gyro_sensCoefs[selectedDPS];
}

// Formats raw data to int.
int16_t FXAS_FormatInt( int16_t input )
{
    // Convert data.
    return ( int16_t )FXAS_FormatFloat( input );
}

// Formats data from raw to float.
void gyro_fmtDef2Float(
                        const void* src,
                              void* dst,
                           uint32_t idx
                      )
{
    // helper pointers
    int16_t* input = ( int16_t* )src;
    float* output = ( float* )dst;
    
    // convert data
    output[idx] = FXAS_FormatFloat( input[idx] );
}

// Formats data from raw to mE format.
void gyro_fmtDef2Me(
                     const void* src,
                           void* dst,
                        uint32_t idx
                   )
{
    // helper pointers
    int16_t* input  = ( int16_t* )src;
    mE_t* output = ( mE_t* )dst;

    // convert data
    output[idx] = ( mE_t )FXAS_FormatInt( input[idx] ) /* * 100 */;
}

// Formats raw to byte - currently unimplemented.
void gyro_fmtDef2Byte(
                       const void* src,
                             void* dst,
                          uint32_t idx
                     )
{}
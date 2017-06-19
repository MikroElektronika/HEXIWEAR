// File: MAXIM_driver.c

// Definitions of main functionalities in the MAXIM sensor module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "error.h"

#include "MAXIM_info.h"
#include "MAXIM_types.h"
#include "MAXIM_driver.h"

#include "OSA.h"

#include "HEXIWEAR_types.h"

////////////////////////////////////////////////////////////////////////////////
// Static variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

static dataMAXIM_t** ledBuffers = 0;

static bool isMaximEnabled = false;

static maxim_callback_t maxim_callback = NULL;

static uint8_t maxim_bytesPerSample;

static uint32_t maxim_bitMask;

// Buffer for I2C data.
static uint8_t buffer[2];

////////////////////////////////////////////////////////////////////////////////
// Static function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Reads a single byte from the sensor register at the given address.
static uint8_t MAXIM_ReadSingle( uint8_t rdAddr )
{
    buffer[0] = rdAddr;
    I2C0_Start();
    I2C0_Write( MAXIM_I2C_ADDRESS, buffer, 1, END_MODE_RESTART );
    I2C0_Read( MAXIM_I2C_ADDRESS, buffer, 1, END_MODE_STOP );

    return buffer[0];
}

// Writes the given byte to the sensor register at the given address.
static void MAXIM_WriteSingle( uint8_t wrAddr, uint8_t wrData )
{
    buffer[1] = wrData;
    buffer[0] = wrAddr;
    I2C0_Start();
    I2C0_Write( MAXIM_I2C_ADDRESS, buffer, 2, END_MODE_STOP );
}

////////////////////////////////////////////////////////////////////////////////
// Global function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Initialises the MAXIM sensor.
void MAXIM_Init()
{
    I2C0_Init_Advanced( 400000, &_GPIO_Module_I2C0_PB0_1 );

    MAXIM_Reset();

    OSA_TimeDelay(50);
    
    MAXIM_WriteSingle( MAXIM_REG_LED_RED_PA, 0xFF );
    MAXIM_WriteSingle( MAXIM_REG_LED_IR_PA, 0x33 );
    MAXIM_WriteSingle( MAXIM_REG_LED_GREEN_PA, 0xFF );
    MAXIM_WriteSingle( MAXIM_REG_PROXY_PA, 0x19 );

    MAXIM_WriteSingle( MAXIM_REG_MULTILED_MODE_CR_12, 0x03 );
    MAXIM_WriteSingle( MAXIM_REG_MULTILED_MODE_CR_34, 0x00 );

    MAXIM_WriteSingle( MAXIM_REG_FIFO_CFG, 0x06 );
    MAXIM_WriteSingle( MAXIM_REG_SPO2_CFG, 0x43 );

    MAXIM_WriteSingle( MAXIM_REG_PROXY_INT_THR, 0x14 );
    
    MAXIM_WriteSingle( MAXIM_REG_FIFO_WR_PTR, 0x00 );
    MAXIM_WriteSingle( MAXIM_REG_FIFO_RD_PTR, 0x00 );
    MAXIM_WriteSingle( MAXIM_REG_FIFO_OV_PTR, 0x00 );
    
    // read only green LED valus
    maxim_bytesPerSample = MAXIM_BYTES_PER_ADC_VALUE * 1;
    maxim_bitMask        = 0x00003FFFF;
}

// Shutdowns the sensor.
void MAXIM_Deinit()
{
    // dealocate memory
    if( ledBuffers != NULL )
    {
        free( ledBuffers );
    }
}

// Resets the module.
uint8_t MAXIM_Reset()
{
    uint8_t timeoutCnt = 0;
    uint8_t temp;

    MAXIM_WriteSingle( MAXIM_REG_MODE_CFG, MAXIM_MODE_CFGBIT_RST );
    
    // Poll the RESET bit until it's cleared by hardware.
    while( 1 )
    {
        temp = MAXIM_ReadSingle( MAXIM_REG_MODE_CFG );
        
        if( ( temp & MAXIM_MODE_CFGBIT_RST ) != 0 )
        {
            // Wait a bit.
            OSA_TimeDelay( 15 );
            timeoutCnt++;

            // Exit if the module is stuck.
            if( timeoutCnt > 5 )
            {
                error_catch( 11 );
                return 1;
            }
        }
        else
        {
            return 0;
        }
    }
}

// Reads raw sensor data.
void MAXIM_ReadRawData( uint8_t* dataBuff, uint8_t* sampleNum )
{
    uint8_t fifoWrPtr = 0;
    uint8_t fifoRdPtr = 0;
    uint8_t fifoOvPtr = 0;

    // Temporary buffer to read samples from the FIFO buffer.
    uint8_t tmpBuf[ MAXIM_FIFO_DEPTH * MAXIM_BYTES_PER_ADC_VALUE ];
    
    uint8_t numAvailSam;
    
    // Read FIFO pointers.
    fifoWrPtr = MAXIM_ReadSingle( MAXIM_REG_FIFO_WR_PTR );
    fifoRdPtr = MAXIM_ReadSingle( MAXIM_REG_FIFO_RD_PTR );
    fifoOvPtr = MAXIM_ReadSingle( MAXIM_REG_FIFO_OV_PTR );
    
    // Overflow happened.
    if( fifoOvPtr > 0 )
    {
        uint8_t tmp;
        
        error_catch( CATCH_HEALTH );

        // Dummy read.
        tmp = MAXIM_REG_FIFO_DATA;
        I2C0_Start();
        I2C0_Write( MAXIM_I2C_ADDRESS, &tmp, 1, END_MODE_RESTART );
        I2C0_Read( MAXIM_I2C_ADDRESS, tmpBuf,
            MAXIM_FIFO_DEPTH * MAXIM_BYTES_PER_ADC_VALUE, END_MODE_STOP );

        numAvailSam = 0xFF;
    }
    else
    {
        if( fifoWrPtr > fifoRdPtr )
        {
            // NUM_SAMPLES_TO_READ <= NUM_AVAILABLE_SAMPLES
            numAvailSam = fifoWrPtr - fifoRdPtr;
        }
        else if ( fifoWrPtr < fifoRdPtr )
        {
            // Pointer wrap around should be taken into account.
            numAvailSam = fifoWrPtr + MAXIM_FIFO_DEPTH - fifoRdPtr;
        }
        else
        {
            // No new samples available.
            numAvailSam = 0;
        }
        
        if( numAvailSam > 0 )
        {
            uint8_t tmp;
            
            tmp = MAXIM_REG_FIFO_DATA;
            I2C0_Start();
            I2C0_Write( MAXIM_I2C_ADDRESS, &tmp, 1, END_MODE_RESTART );
            I2C0_Read( MAXIM_I2C_ADDRESS, tmpBuf,
                numAvailSam * MAXIM_BYTES_PER_ADC_VALUE, END_MODE_STOP );

            if( dataBuff != NULL )
            {
                memcpy( dataBuff, tmpBuf,
                    numAvailSam * MAXIM_BYTES_PER_ADC_VALUE );
            }
        }
    }
    
    // Save data.
    if( sampleNum != NULL )
    {
        *sampleNum = numAvailSam;
    }

    if( maxim_callback != NULL )
        maxim_callback( tmpBuf, numAvailSam, 0 );
}

// Enables the sensor.
void MAXIM_Enable()
{
    MAXIM_WriteSingle( MAXIM_REG_INTERRUPT_ENABLE_1, 0x10 );
    MAXIM_WriteSingle( MAXIM_REG_MODE_CFG , 0x07 );
    isMaximEnabled = true;
}

// Disables the sensor.
void MAXIM_Disable()
{
    if( isMaximEnabled )
        isMaximEnabled = false;
}

// Installs callback to be called during sensor's read.
void MAXIM_InstallCallback( maxim_callback_t callback )
{
    maxim_callback = callback;
}

// Tests the sensor.
void MAXIM_Test()
{
    MAXIM_Init();
    MAXIM_Enable();
    OSA_TimeDelay( 500 );
    MAXIM_Disable();
    MAXIM_Reset();
}

// Formats raw to float.
void hr_fmtDef2Float(
                      const void* src,
                            void* dst,
                         uint32_t idx
                    )
{}

// Formats raw to mE format.
void hr_fmtDef2Me(
                   const void* src,
                         void* dst,
                      uint32_t idx
                 )
{}

// Formats raw to byte - currently unimplemented.
void hr_fmtDef2Byte(
                     const void* src,
                           void* dst,
                        uint32_t idx
                   )
{}
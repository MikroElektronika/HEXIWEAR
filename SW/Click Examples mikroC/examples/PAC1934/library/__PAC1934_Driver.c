/*

    __PAC1934_Driver.c

    Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

------------------------------------------------------------------------------*/

/**
@file           __PAC1934_Driver.c
@addtogroup     PAC1934
@{
------------------------------------------------------------------------------*/

#include "__PAC1934_Hal.h"
#include "__PAC1934_Hal.c"
#include "__PAC1934_Driver.h"

uint8_t PAC1934_I2CAddress = 0x10;

/**
 * @name    PAC1934 Click GPIO
 *//*-------------------------------------------------------------------------*/
///@{


///@}
/**
 * @name    PAC1934 Click Return Values
 *//*-------------------------------------------------------------------------*/
///@{

uint8_t _PAC1934_OK     = 0;                                              /**< NO ERROR */
uint8_t _PAC1934_ERR    = 1;                                              /**< ERROR OCCURED */

///@}
/**
 * @name    PAC1934 Click Registers
 *//*-------------------------------------------------------------------------*/
///@{

uint8_t _PAC1934_REFRESH_CMD    = 0x00;                             /**< Refresh command */
uint8_t _PAC1934_CTRL_REG       = 0x01;                             /**< Control register */

uint8_t _PAC1934_ACC_COUNT      = 0x02;                             /**< Accumulator count */
uint8_t _PAC1934_VPOWER1_ACC    = 0x03;                             /**< Accumulated power 1 */
uint8_t _PAC1934_VPOWER2_ACC    = 0x04;                             /**< Accumulated power 2 */
uint8_t _PAC1934_VPOWER3_ACC    = 0x05;                             /**< Accumulated power 3 */
uint8_t _PAC1934_VPOWER4_ACC    = 0x06;                             /**< Accumulated power 4 */

uint8_t _PAC1934_VBUS1          = 0x07;                             /**< Most recent Vbus sample 1 */
uint8_t _PAC1934_VBUS2          = 0x08;                             /**< Most recent Vbus sample 2 */
uint8_t _PAC1934_VBUS3          = 0x09;                             /**< Most recent Vbus sample 3 */
uint8_t _PAC1934_VBUS4          = 0x0A;                             /**< Most recent Vbus sample 4 */
uint8_t _PAC1934_VSENSE1        = 0x0B;                             /**< Most recent Vsense sample 1 */
uint8_t _PAC1934_VSENSE2        = 0x0C;                             /**< Most recent Vsense sample 2 */
uint8_t _PAC1934_VSENSE3        = 0x0D;                             /**< Most recent Vsense sample 3 */
uint8_t _PAC1934_VSENSE4        = 0x0E;                             /**< Most recent Vsense sample 4 */

uint8_t _PAC1934_VBUS1_AVG          = 0x0F;                             /**< Average Vbus sample 1 */
uint8_t _PAC1934_VBUS2_AVG          = 0x10;                             /**< Average Vbus sample 2 */
uint8_t _PAC1934_VBUS3_AVG          = 0x11;                             /**< Average Vbus sample 3 */
uint8_t _PAC1934_VBUS4_AVG          = 0x12;                             /**< Average Vbus sample 4 */
uint8_t _PAC1934_VSENSE1_AVG        = 0x13;                             /**< Average Vsense sample 1 */
uint8_t _PAC1934_VSENSE2_AVG        = 0x14;                             /**< Average Vsense sample 2 */
uint8_t _PAC1934_VSENSE3_AVG        = 0x15;                             /**< Average Vsense sample 3 */
uint8_t _PAC1934_VSENSE4_AVG        = 0x16;                             /**< Average Vsense sample 4 */

uint8_t _PAC1934_VPOWER1        = 0x17;                             /**< Vbus and Vsense product 1 */
uint8_t _PAC1934_VPOWER2        = 0x18;                             /**< Vbus and Vsense product 2 */
uint8_t _PAC1934_VPOWER3        = 0x19;                             /**< Vbus and Vsense product 3 */
uint8_t _PAC1934_VPOWER4        = 0x1A;                             /**< Vbus and Vsense product 4 */

uint8_t _PAC1934_CHANNEL_DIS        = 0x1C;                         /**< Channel disable and other settings */
uint8_t _PAC1934_NEG_PWR            = 0x1D;                         /**< Bidirectional measurements settings */

uint8_t _PAC1934_REFRESH_G_CMD    = 0x1E;                             /**< Refresh G command */
uint8_t _PAC1934_REFRESH_V_CMD    = 0x1F;                             /**< Refresh V command */

uint8_t _PAC1934_SLOW           = 0x20;                             /**< Slow pin state and settings */

uint8_t _PAC1934_CTRL_ACT        = 0x21;                           /**< Actual state of CTRL register*/
uint8_t _PAC1934_DIS_ACT         = 0x22;                           /**< Actual state of CHANNEL_DIS register*/
uint8_t _PAC1934_NEG_PWR_ACT     = 0x23;                           /**< Actual state of NEG_PWR register*/

uint8_t _PAC1934_CTRL_LAT        = 0x24;                           /**< Latched state of CTRL register*/
uint8_t _PAC1934_DIS_LAT         = 0x25;                           /**< Latched state of CHANNEL_DIS register*/
uint8_t _PAC1934_NEG_PWR_LAT     = 0x26;                           /**< Latched state of NEG_PWR register*/

uint8_t _PAC1934_PRODUCT_ID        = 0x24;                           /**< Product ID register*/
uint8_t _PAC1934_MANUFACT_ID       = 0x25;                           /**< Manufacturer ID register*/
uint8_t _PAC1934_REVISION_ID       = 0x26;                           /**< Revision ID register*/

///@}
/** @cond PORTING_GUIDE */
/*--------------------------------------------- PRIVATE FUNCTION DECLARATIONS */



/*---------------------------------------------- PRIVATE FUNCTION DEFINITIONS */



/*---------------------------------------------------------- PUBLIC FUNCTIONS */

/*  EXAMPLE OF GPIO INIT
void TEST_GPIOmap( T_TEST_GPIO_Set ctlAN, T_TEST_GPIO_Get ctlRST )
{
    fpAN    =   ctlAN;
    fpRST   =   ctlRST;
}
*/

#if PAC1934_SPI_CLICK == 1
void PAC1934_SPIdriverInit( T_PAC1934_SPI_Write     fnWrite,
                                  T_PAC1934_SPI_Read      fnRead )
{
    fpWriteSPI = fnWrite;
    fpReadSPI  = fnRead;
}
#endif
#if PAC1934_I2C_CLICK == 1
void PAC1934_I2CdriverInit( T_PAC1934_I2C_Start     fnStart,
                                  T_PAC1934_I2C_Stop      fnStop,
                                  T_PAC1934_I2C_Restart   fnRestart,
                                  T_PAC1934_I2C_Write     fnWrite,
                                  T_PAC1934_I2C_Read      fnRead )
{
    fpStartI2C    = fnStart;
    fpStopI2C     = fnStop;
    fpRestartI2C  = fnRestart;
    fpWriteI2C    = fnWrite;
    fpReadI2C     = fnRead;
}
#endif
#if PAC1934_UART_CLICK == 1
void PAC1934_UARTdriverInit( T_PAC1934_UART_Write   fnWrite,
                                   T_PAC1934_UART_Read    fnRead,
                                   T_PAC1934_UART_Ready   fnReady )
{
    fpWriteUART = fnWrite;
    fpReadUART  = fnRead;
    fpReadyUART = fnReady;
}
#endif


void PAC1934_sendCommand (uint8_t command)
{
    uint8_t input [1];

    input [0] = command;

    if (command == _PAC1934_REFRESH_G_CMD)
    {
        HAL_i2cStart ();
        HAL_i2cWrite (0x00, input, 1, END_MODE_STOP);
    }
    else
    {
        HAL_i2cStart ();
        HAL_i2cWrite (PAC1934_I2CAddress, input, 1, END_MODE_STOP);
    }
}

void PAC1934_writeReg (uint8_t inputAddress, uint8_t inputData)
{
    uint8_t input [2];

    input [0] = inputAddress;
    input [1] = inputData;

    HAL_i2cStart ();
    HAL_i2cWrite (PAC1934_I2CAddress, input, 2, END_MODE_STOP);
}

void PAC1934_readReg (uint8_t inputAddress, uint8_t *outputData, uint8_t count)
{
    uint8_t regAddress [1];
    uint8_t *readData = outputData;

    regAddress [0] = inputAddress;

    HAL_i2cStart ();
    HAL_i2cWrite (PAC1934_I2CAddress, regAddress, 1, END_MODE_RESTART);
    HAL_i2cRead (PAC1934_I2CAddress, readData, count, END_MODE_STOP);
}



float PAC1934_measureVoltage (uint8_t channel)
{
    uint8_t regAddress [1];
    uint8_t readValue [2];
    uint16_t returnInt = 0;
    float returnValue;


    regAddress [0] = channel + 0x06;

    HAL_i2cStart ();
    HAL_i2cWrite (PAC1934_I2CAddress, regAddress, 1, END_MODE_RESTART);
    HAL_i2cRead (PAC1934_I2CAddress, readValue, 2, END_MODE_STOP);


    returnInt = readValue [0];
    returnInt <<= 8;
    returnInt |= readValue [1];

    returnValue = returnInt;
    returnValue = returnValue * 32;                  //FSV
    returnValue = returnValue / 0xFFFF;

    return returnValue;
}

float PAC1934_measureCurrent (uint8_t channel)
{
    uint8_t regAddress [1];
    uint8_t readValue [2];
    uint16_t returnInt = 0;
    float returnValue;


    regAddress [0] = channel + 0x0A;

    HAL_i2cStart ();
    HAL_i2cWrite (PAC1934_I2CAddress, regAddress, 1, END_MODE_RESTART);
    HAL_i2cRead (PAC1934_I2CAddress, readValue, 2, END_MODE_STOP);


    returnInt = readValue [0];
    returnInt <<= 8;
    returnInt |= readValue [1];

    returnValue = returnInt;
    returnValue = returnValue * 25000;              // FSC
    returnValue = returnValue / 0xFFFF;

    return returnValue;
}


float PAC1934_measurePower (uint8_t channel)
{
    uint8_t regAddress [1];
    uint8_t readValue [2];
    uint32_t returnInt = 0;
    float returnValue;


    regAddress [0] = channel + 0x16;

    HAL_i2cStart ();
    HAL_i2cWrite (PAC1934_I2CAddress, regAddress, 1, END_MODE_RESTART);
    HAL_i2cRead (PAC1934_I2CAddress, readValue, 4, END_MODE_STOP);


    returnInt = readValue [0];
    returnInt <<= 8;
    returnInt |= readValue [1];
    returnInt <<= 8;
    returnInt |= readValue [2];
    returnInt <<= 4;
    readValue [3] >>= 4;
    returnInt |= readValue [3];

    returnValue = returnInt;
    returnValue = returnValue * 800;            // PowerFSR
    returnValue = returnValue / 0xFFFFFFF;

    return returnValue;
}

#if defined ( __MIKROC_PRO_FOR_AVR__ ) || defined ( __MIKROC_PRO_FOR_PIC__ ) \
              || defined ( __MIKROC_PRO_FOR_DSPIC__ )
//uint64 not supported
#elif 1
float PAC1934_measureEnergy (uint8_t channel, uint16_t sampleRate)
{
    uint8_t regAddress [1];
    uint8_t readValue [2];
    uint64_t accumulatorValue = 0;
    float returnValue;

    //Count register needs to be read, even when not used.
    regAddress [0] = 0x02;
    HAL_i2cStart ();
    HAL_i2cWrite (PAC1934_I2CAddress, regAddress, 1, END_MODE_RESTART);
    HAL_i2cRead (PAC1934_I2CAddress, readValue, 3, END_MODE_STOP);
    
    regAddress [0] = channel + 0x02;

    HAL_i2cStart ();
    HAL_i2cWrite (PAC1934_I2CAddress, regAddress, 1, END_MODE_RESTART);
    HAL_i2cRead (PAC1934_I2CAddress, readValue, 6, END_MODE_STOP);


    accumulatorValue = readValue [0];
    accumulatorValue <<= 8;
    accumulatorValue |= readValue [1];
    accumulatorValue <<= 8;
    accumulatorValue |= readValue [2];
    accumulatorValue <<= 8;
    accumulatorValue |= readValue [3];
    accumulatorValue <<= 8;
    accumulatorValue |= readValue [4];
    accumulatorValue <<= 8;
    accumulatorValue |= readValue [5];

    returnValue = accumulatorValue;
    returnValue = returnValue * 800;                           // PowerFSR
    returnValue = returnValue / 0xFFFFFFF;
    returnValue = returnValue / sampleRate;                    // 1/sample rate
    
    return returnValue;
}
#endif
/** @endcond */
/** @} */
/*------------------------------------------------------------------------------

  __PAC1934_Driver.c

  Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

    This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.

------------------------------------------------------------------------------*/
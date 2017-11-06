/*

    __QIRCV_Driver.c

    Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

------------------------------------------------------------------------------*/

/**
@file           __QIRCV_Driver.c
@addtogroup     QIRCV
@{
------------------------------------------------------------------------------*/

#include "__QIRCV_Hal.h"
#include "__QIRCV_Hal.c"
#include "__QIRCV_Driver.h"

uint8_t QIRCV_I2CAddress = 0x25;
/**
 * @name    Qi_Receiver Click GPIO
 *//*-------------------------------------------------------------------------*/
///@{


///@}
/**
 * @name    Qi_Receiver Click Return Values
 *//*-------------------------------------------------------------------------*/
///@{

uint8_t _QIRCV_OK     = 0;                                              /**< NO ERROR */
uint8_t _QIRCV_ERR    = 1;                                              /**< ERROR OCCURED */

///@}
/**
 * @name    Qi_Receiver Click Registers
 *//*-------------------------------------------------------------------------*/
///@{

uint8_t _QIRCV_STATUS = 0x00;                                           /**< Status Register Address */

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

#if QIRCV_SPI_CLICK == 1
void QIRCV_SPIdriverInit( T_QIRCV_SPI_Write     fnWrite,
                                  T_QIRCV_SPI_Read      fnRead )
{
    fpWriteSPI = fnWrite;
    fpReadSPI  = fnRead;
}
#endif
#if QIRCV_I2C_CLICK == 1
void QIRCV_I2CdriverInit( T_QIRCV_I2C_Start     fnStart,
                                  T_QIRCV_I2C_Stop      fnStop,
                                  T_QIRCV_I2C_Restart   fnRestart,
                                  T_QIRCV_I2C_Write     fnWrite,
                                  T_QIRCV_I2C_Read      fnRead )
{
    fpStartI2C    = fnStart;
    fpStopI2C     = fnStop;
    fpRestartI2C  = fnRestart;
    fpWriteI2C    = fnWrite;
    fpReadI2C     = fnRead;
}
#endif
#if QIRCV_UART_CLICK == 1
void QIRCV_UARTdriverInit( T_QIRCV_UART_Write   fnWrite,
                                   T_QIRCV_UART_Read    fnRead,
                                   T_QIRCV_UART_Ready   fnReady )
{
    fpWriteUART = fnWrite;
    fpReadUART  = fnRead;
    fpReadyUART = fnReady;
}
#endif

float QIRCV_readV ()
{
    uint8_t regAddress [1];
    uint8_t readValue [2];
    uint16_t returnInt = 0;
    float returnValue;

   
    regAddress [0] = 0x40;

    HAL_i2cStart ();
    HAL_i2cWrite (QIRCV_I2CAddress, regAddress, 1, END_MODE_RESTART);
    HAL_i2cRead (QIRCV_I2CAddress, readValue, 1, END_MODE_STOP);

    
    returnInt = readValue [0];
    returnInt <<= 4;
   
    regAddress [0] = 0x41;

    HAL_i2cStart ();
    HAL_i2cWrite (QIRCV_I2CAddress, regAddress, 1, END_MODE_RESTART);
    HAL_i2cRead (QIRCV_I2CAddress, readValue, 1, END_MODE_STOP);

    readValue [0] >>= 4;
    readValue [0] &= 0x0F;
    returnInt |= readValue [0];
    
    returnValue = returnInt;
    returnValue = returnValue * 1.8;
    returnValue = returnValue * 5;
    returnValue = returnValue / 4096;
    
    return returnValue;
}

float QIRCV_readI ()
{
    uint8_t regAddress [1];
    uint8_t readValue [2];
    uint16_t returnInt = 0;
    float returnValue;

    regAddress [0] = 0x42;

    HAL_i2cStart ();
    HAL_i2cWrite (QIRCV_I2CAddress, regAddress, 1, END_MODE_RESTART);
    HAL_i2cRead (QIRCV_I2CAddress, readValue, 1, END_MODE_STOP);


    returnInt = readValue [0];
    returnInt <<= 4;
    
    regAddress [0] = 0x43;

    HAL_i2cStart ();
    HAL_i2cWrite (QIRCV_I2CAddress, regAddress, 1, END_MODE_RESTART);
    HAL_i2cRead (QIRCV_I2CAddress, readValue, 1, END_MODE_STOP);
    
    readValue [0] >>= 4;
    readValue [0] &= 0x0F;
    returnInt |= readValue [0];
    

    returnValue = returnInt;
    returnValue = returnValue * 1.8;
    returnValue = returnValue / 4.096;


    return returnValue;
}

uint8_t QIRCV_readReg (uint8_t inputAddress)
{
    uint8_t regAddress [1];
    uint8_t readValue [1];

    regAddress [0] = inputAddress;

    HAL_i2cStart ();
    HAL_i2cWrite (QIRCV_I2CAddress, regAddress, 1, END_MODE_RESTART);
    HAL_i2cRead (QIRCV_I2CAddress, readValue, 1, END_MODE_STOP);

    return readValue [0];
}

void QIRCV_writeReg (uint8_t inputAddress, uint8_t inputData)
{
    uint8_t input [2];

    input [0] = inputAddress;
    input [1] = inputData;

    HAL_i2cStart ();
    HAL_i2cWrite (QIRCV_I2CAddress, input, 2, END_MODE_STOP);
}

/** @endcond */
/** @} */
/*------------------------------------------------------------------------------

  __QIRCV_Driver.c

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
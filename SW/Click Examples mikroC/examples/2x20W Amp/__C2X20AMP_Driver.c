/*

    __C2X20AMP_Driver.c

    Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

----------------------------------------------------------------------------- */

/**
@file         __C2X20AMP_Driver.c
@brief          C2X20AMP Driver Source
@addtogroup     C2X20AMP
@{

*/
/* -------------------------------------------------------------------------- */

#include "__C2X20AMP_Hal.h"
#include "__C2X20AMP_Hal.c"
#include "__C2X20AMP_Driver.h"

/* ---------------------------------------------------------------- VARIABLES */



/* -------------------------------------------- PRIVATE FUNCTION DECLARATIONS */



/* --------------------------------------------- PRIVATE FUNCTION DEFINITIONS */



/* --------------------------------------------------------- PUBLIC FUNCTIONS */

void C2X20AMP_init ()
{
    fpMT( 0 );
}

void C2X20AMP_setVolume (uint8_t newVolume)
{
    uint8_t inputData [1];
    uint8_t i2cAddress;
    
    i2cAddress = 0x48;
    if (fpAD1())
       i2cAddress |= 0x01;
    if (fpAD2())
       i2cAddress |= 0x02;
    
    newVolume &= 0x3F;
    inputData [0] = newVolume;
   
    hal_i2cStart ();
    hal_i2cWrite(i2cAddress, inputData, 1, END_MODE_STOP);
}

void C2X20AMP_increaseVolume ()
{
    uint8_t inputData [1];
    uint8_t i2cAddress;

    i2cAddress = 0x48;
    if (fpAD1())
       i2cAddress |= 0x01;
    if (fpAD2())
       i2cAddress |= 0x02;
       
    inputData [0] = 0xC4;

    hal_i2cStart ();
    hal_i2cWrite(i2cAddress, inputData, 1, END_MODE_STOP);
}

void C2X20AMP_decreaseVolume ()
{
    uint8_t inputData [1];
    uint8_t i2cAddress;

    i2cAddress = 0x48;
    if (fpAD1())
       i2cAddress |= 0x01;
    if (fpAD2())
       i2cAddress |= 0x02;

    inputData [0] = 0xC5;

    hal_i2cStart ();
    hal_i2cWrite(i2cAddress, inputData, 1, END_MODE_STOP);
}

void C2X20AMP_filterlessModulation ()
{
    uint8_t inputData [1];
    uint8_t i2cAddress;

    i2cAddress = 0x48;
    if (fpAD1())
       i2cAddress |= 0x01;
    if (fpAD2())
       i2cAddress |= 0x02;

    inputData [0] = 0x40;

    hal_i2cStart ();
    hal_i2cWrite(i2cAddress, inputData, 1, END_MODE_STOP);
}

void C2X20AMP_classicPWM ()
{
    uint8_t inputData [1];
    uint8_t i2cAddress;

    i2cAddress = 0x48;
    if (fpAD1())
       i2cAddress |= 0x01;
    if (fpAD2())
       i2cAddress |= 0x02;

    inputData [0] = 0x41;

    hal_i2cStart ();
    hal_i2cWrite(i2cAddress, inputData, 1, END_MODE_STOP);
}

/* ----------------------------------------------------- HAL PUBLIC FUNCTIONS */

#ifdef __C2X20AMP_GPIO

#define _AN_PIN   0
#define _RST_PIN  1
#define _CS_PIN   2
#define _SCK_PIN  3
#define _MISO_PIN 4
#define _MOSI_PIN 5
#define _PWM_PIN  6
#define _INT_PIN  7
#define _RX_PIN   8
#define _TX_PIN   9
#define _SCL_PIN  10
#define _SDA_PIN  11

void 
HAL_C2X20AMP_gpioInit
( 
        T_C2X20AMP_GPIO_Get      ctlAD1,
        T_C2X20AMP_GPIO_Get      ctlAD2,
        T_C2X20AMP_GPIO_Set      ctlMT
)
{
    fpAD1   = ctlAD1;
    fpAD2   = ctlAD2;
    fpMT   = ctlMT;
}

/*void HAL_C2X20AMP_gpioInit(T_C2X20AMP_gpioObj *gpioObj)
{
    fpAN   = gpioObj->gpioSet[ _AN_PIN ];   // Just an example
    fpRST  = gpioObj->gpioGet[ _RST_PIN ];
}*/

#undef _AN_PIN   
#undef _RST_PIN  
#undef _CS_PIN   
#undef _SCK_PIN  
#undef _MISO_PIN 
#undef _MOSI_PIN 
#undef _PWM_PIN  
#undef _INT_PIN  
#undef _RX_PIN   
#undef _TX_PIN   
#undef _SCL_PIN  
#undef _SDA_PIN  
#endif
#ifdef __C2X20AMP_SPI
void 
HAL_C2X20AMP_spiInit
( 
        T_C2X20AMP_SPI_Write     fnWrite,
        T_C2X20AMP_SPI_Read      fnRead 
)
{
    fpWriteSPI = fnWrite;
    fpReadSPI  = fnRead;
}

// RESERVED
//void HAL_C2X20AMP_spiInit(const T_C2X20AMP_spiObj *spiObj)
//{
//    fpWriteSPI = spiObj->spiWrite;
//    fpReadSPI  = spiObj->spiRead;
//}
#endif
#ifdef __C2X20AMP_I2C
void 
HAL_C2X20AMP_i2cInit
( 
        T_C2X20AMP_I2C_Start     fnStart,
        T_C2X20AMP_I2C_Stop      fnStop,
        T_C2X20AMP_I2C_Restart   fnRestart,
        T_C2X20AMP_I2C_Write     fnWrite,
        T_C2X20AMP_I2C_Read      fnRead 
)
{
    fpStartI2C    = fnStart;
    fpStopI2C     = fnStop;
    fpRestartI2C  = fnRestart;
    fpWriteI2C    = fnWrite;
    fpReadI2C     = fnRead;
}

// RESERVED
//void HAL_C2X20AMP_i2cInit(const T_C2X20AMP_i2cObj *i2cObj)
//{
//    fpStartI2C    = i2cObj->i2cStart;
//    fpStopI2C     = i2cObj->i2cStop;
//    fpRestartI2C  = i2cObj->i2cRestart;
//    fpWriteI2C    = i2cObj->i2cWrite;
//    fpReadI2C     = i2cObj->i2cRead;
//}

#endif
#ifdef __C2X20AMP_UART
void 
HAL_C2X20AMP_uartInit
( 
        T_C2X20AMP_UART_Write   fnWrite,
        T_C2X20AMP_UART_Read    fnRead,
        T_C2X20AMP_UART_Ready   fnReady 
)
{
    fpWriteUART = fnWrite;
    fpReadUART  = fnRead;
    fpReadyUART = fnReady;
}

// RESERVED
//void HAL_C2X20AMP_uartInit(const T_C2X20AMP_uartObj *uartObj)
//{
//    fpWriteUART = uartObj->uartWrite;
//    fpReadUART  = uartObj->uartRead;
//    fpReadyUART = uartObj->uartReady;
//}
#endif

/// @}
/* -------------------------------------------------------------------------- */
/*
  __C2X20AMP_Driver.c

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

----------------------------------------------------------------------------- */
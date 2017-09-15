/*

    __BRUSHLESS_3_Driver.c

    Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

------------------------------------------------------------------------------*/

/**
@file           __BRUSHLESS_3_Driver.c
@addtogroup     BRUSHLESS_3
@{
------------------------------------------------------------------------------*/

#include "__BRUSHLESS_3_Hal.h"
#include "__BRUSHLESS_3_Hal.c"
#include "__BRUSHLESS_3_Driver.h"

/**
 * @name    Brushless_3 Click GPIO
 *//*-------------------------------------------------------------------------*/
///@{

//extern GPIO_TYPE BRUSHLESS_3_SOME_PIN;                                        /**< Brushless_3 Some Pin */

///@}

/*----------------------------------------------------------------- VARIABLES */

/** Brushless_3 click slave interface address */
const uint8_t _BRUSHLESS_3_ADDRESS         = 0x52;

/**
 * @name    Brushless_3 Click Return Values
 *//*-------------------------------------------------------------------------*/
///@{

uint8_t _BRUSHLESS_3_OK     = 0;                                              /**< NO ERROR */
uint8_t _BRUSHLESS_3_ERR    = 1;                                              /**< ERROR OCCURED */

///@}
/**
 * @name    Brushless_3 Click Read/Write Registers
 *//*-------------------------------------------------------------------------*/
///@{
const uint8_t _BRUSHLESS_3_SPEED_CTRL_1 = 0x00;     /**< Speed Control Register 1 Address */
const uint8_t _BRUSHLESS_3_SPEED_CTRL_2 = 0x01;     /**< Speed Control Register 2 Address */
const uint8_t _BRUSHLESS_3_DEV_CTRL = 0x02;         /**< Device Control Register  Address */
const uint8_t _BRUSHLESS_3_EE_CTRL = 0x03;          /**< EEPROM Control Register Address */

///@}

/**
 * @name    Brushless_3 Click Read Registers
 *//*-------------------------------------------------------------------------*/
///@{
const uint8_t _BRUSHLESS_3_STATUS = 0x10;             /**< Status Register Address */
const uint8_t _BRUSHLESS_3_MOTOR_SPEED_1 = 0x11;      /**< Motor Speed 1 Register Address */
const uint8_t _BRUSHLESS_3_MOTOR_SPEED_2 = 0x12;      /**< Motor Speed 2 Register Address */
const uint8_t _BRUSHLESS_3_MOTOR_PERIOD_1 = 0x13;     /**< Motor Period 1 Register Address */
const uint8_t _BRUSHLESS_3_MOTOR_PERIOD_2 = 0x14;     /**< Motor Period 2 Register Address */
const uint8_t _BRUSHLESS_3_MOTOR_KT_1 = 0x15;         /**< Motor Kt 1 Register Address */
const uint8_t _BRUSHLESS_3_MOTOR_KT_2 = 0x16;         /**< Motor Kt 2 Register Address */
const uint8_t _BRUSHLESS_3_IPD_POSITION = 0x19;       /**< IPD Position Register Address */
const uint8_t _BRUSHLESS_3_SUPPLY_VOLTAGE = 0x1A;     /**< Supply Voltage Register Address */
const uint8_t _BRUSHLESS_3_SPEED_CMD = 0x1B;          /**< Speed Cmd Register Address */
const uint8_t _BRUSHLESS_3_SPD_CMD_BUFFER = 0x1C;     /**< Speed Cmd Buffer Register Address */
const uint8_t _BRUSHLESS_3_FAULT_CODE = 0x1E;         /**< Fault Code Register Address */
///@}

/**
 * @name    Brushless_3 Click EEPROM Registers
 *//*-------------------------------------------------------------------------*/
///@{
const uint8_t _BRUSHLESS_3_MOTOR_PARAM_1 = 0x20;      /**<  Motor Parameters 1 Register Address */
const uint8_t _BRUSHLESS_3_MOTOR_PARAM_2 = 0x21;      /**<  Motor Parameters 2 Register Address */
const uint8_t _BRUSHLESS_3_MOTOR_PARAM_3 = 0x22;      /**<  Motor Parameters 3 Register Address */
const uint8_t _BRUSHLESS_3_SYS_OPT_1 = 0x23;          /**< System Options 1 Register Address */
const uint8_t _BRUSHLESS_3_SYS_OPT_2 = 0x24;          /**< System Options 2 Register Address */
const uint8_t _BRUSHLESS_3_SYS_OPT_3 = 0x25;          /**< System Options 3 Register Address */
const uint8_t _BRUSHLESS_3_SYS_OPT_4 = 0x26;          /**< System Options 4 Register Address */
const uint8_t _BRUSHLESS_3_SYS_OPT_5 = 0x27;          /**< System Options 5 Register Address */
const uint8_t _BRUSHLESS_3_SYS_OPT_6 = 0x28;          /**< System Options 6 Register Address */
const uint8_t _BRUSHLESS_3_SYS_OPT_7 = 0x29;          /**< System Options 7 Register Address */
const uint8_t _BRUSHLESS_3_SYS_OPT_8 = 0x2A;          /**< System Options 8 Register Address */
const uint8_t _BRUSHLESS_3_SYS_OPT_9 = 0x2B;          /**< System Options 9 Register Address */
///@}


/** @cond PORTING_GUIDE */
/*--------------------------------------------- PRIVATE FUNCTION DECLARATIONS */



/*---------------------------------------------- PRIVATE FUNCTION DEFINITIONS */



/*---------------------------------------------------------- PUBLIC FUNCTIONS */

int writeReg(uint8_t regAddr, uint8_t value)
{
    int err = 0;
    uint8_t tmp[2];
    tmp[0] = regAddr;
    tmp[1] = value;

    err |= HAL_i2cStart();
    err |= HAL_i2cWrite(_BRUSHLESS_3_ADDRESS, tmp, 2, END_MODE_STOP);

    return err;
}

int readReg(uint8_t regAddr, uint8_t *value)
{
    int err = 0;
    uint8_t tmp[1];
    uint8_t val[1];

    tmp[0] = regAddr;

    err |= HAL_i2cStart();
    err |= HAL_i2cWrite(_BRUSHLESS_3_ADDRESS, tmp, 1, END_MODE_RESTART);
    err |= HAL_i2cRead(_BRUSHLESS_3_ADDRESS, val, 1, END_MODE_STOP);

    *value = 0;
    *value = val[0];

    return err;
}

int writeParameters(uint8_t *parameters)
{
    int err = 0;
    uint8_t tmp[2];

    tmp[0] = _BRUSHLESS_3_EE_CTRL;
    tmp[1] = 0x40;

    err |= HAL_i2cStart();
    err |= HAL_i2cWrite(_BRUSHLESS_3_ADDRESS, tmp, 2, END_MODE_STOP);
    
    tmp[0] = _BRUSHLESS_3_MOTOR_PARAM_1;
    tmp[1] = parameters[0];

    err |= HAL_i2cStart();
    err |= HAL_i2cWrite(_BRUSHLESS_3_ADDRESS, tmp, 2, END_MODE_STOP);

    tmp[0] = _BRUSHLESS_3_MOTOR_PARAM_2;
    tmp[1] = parameters[1];

    err |= HAL_i2cStart();
    err |= HAL_i2cWrite(_BRUSHLESS_3_ADDRESS, tmp, 2, END_MODE_STOP);    
    
    tmp[0] = _BRUSHLESS_3_MOTOR_PARAM_3;
    tmp[1] = parameters[2];

    err |= HAL_i2cStart();
    err |= HAL_i2cWrite(_BRUSHLESS_3_ADDRESS, tmp, 2, END_MODE_STOP);
    
    tmp[0] = _BRUSHLESS_3_SYS_OPT_1;
    tmp[1] = parameters[3];

    err |= HAL_i2cStart();
    err |= HAL_i2cWrite(_BRUSHLESS_3_ADDRESS, tmp, 2, END_MODE_STOP);  
    
    tmp[0] = _BRUSHLESS_3_SYS_OPT_2;
    tmp[1] = parameters[4];

    err |= HAL_i2cStart();
    err |= HAL_i2cWrite(_BRUSHLESS_3_ADDRESS, tmp, 2, END_MODE_STOP);
    
    tmp[0] = _BRUSHLESS_3_SYS_OPT_3;
    tmp[1] = parameters[5];
    
    err |= HAL_i2cStart();
    err |= HAL_i2cWrite(_BRUSHLESS_3_ADDRESS, tmp, 2, END_MODE_STOP); 
    
    tmp[0] = _BRUSHLESS_3_SYS_OPT_4;
    tmp[1] = parameters[6];
    
    err |= HAL_i2cStart();
    err |= HAL_i2cWrite(_BRUSHLESS_3_ADDRESS, tmp, 2, END_MODE_STOP); 
    
    tmp[0] = _BRUSHLESS_3_SYS_OPT_5;
    tmp[1] = parameters[7];
    
    err |= HAL_i2cStart();
    err |= HAL_i2cWrite(_BRUSHLESS_3_ADDRESS, tmp, 2, END_MODE_STOP); 
    
    tmp[0] = _BRUSHLESS_3_SYS_OPT_6;
    tmp[1] = parameters[8];
    
    err |= HAL_i2cStart();
    err |= HAL_i2cWrite(_BRUSHLESS_3_ADDRESS, tmp, 2, END_MODE_STOP);  
    
    tmp[0] = _BRUSHLESS_3_SYS_OPT_7;
    tmp[1] = parameters[9];
    
    err |= HAL_i2cStart();
    err |= HAL_i2cWrite(_BRUSHLESS_3_ADDRESS, tmp, 2, END_MODE_STOP); 
   
    tmp[0] = _BRUSHLESS_3_SYS_OPT_8;
    tmp[1] = parameters[10];
   
    err |= HAL_i2cStart();
    err |= HAL_i2cWrite(_BRUSHLESS_3_ADDRESS, tmp, 2, END_MODE_STOP); 
    
    tmp[0] = _BRUSHLESS_3_SYS_OPT_9;
    tmp[1] = parameters[11];
    
    err |= HAL_i2cStart();
    err |= HAL_i2cWrite(_BRUSHLESS_3_ADDRESS, tmp, 2, END_MODE_STOP); 
    
    tmp[0] = _BRUSHLESS_3_DEV_CTRL;
    tmp[1] = 0xB6;
    
    err |= HAL_i2cStart();
    err |= HAL_i2cWrite(_BRUSHLESS_3_ADDRESS, tmp, 2, END_MODE_STOP); 
    
    tmp[0] = _BRUSHLESS_3_EE_CTRL;
    tmp[1] = 0x50;
    
    err |= HAL_i2cStart();
    err |= HAL_i2cWrite(_BRUSHLESS_3_ADDRESS, tmp, 2, END_MODE_STOP);

    return err;
}


int getSpeed(uint16_t *speedValue)
{
    int err = 0;
    uint8_t val;
    uint16_t speed = 0;
    
    readReg(_BRUSHLESS_3_MOTOR_SPEED_1, &val);
    speed |= (uint16_t) val << 8;

    readReg(_BRUSHLESS_3_MOTOR_SPEED_2, &val);
    speed |= ((uint16_t) val);
   
    speed /= 10;
    *speedValue = speed;
    
    return err;
}




/*  EXAMPLE OF GPIO INIT
void TEST_GPIOmap( T_TEST_GPIO_Set ctlAN, T_TEST_GPIO_Get ctlRST )
{
    fpAN    =   ctlAN;
    fpRST   =   ctlRST;
}
*/

#if BRUSHLESS_3_SPI_CLICK == 1
void BRUSHLESS_3_SPIdriverInit( T_BRUSHLESS_3_SPI_Write     fnWrite,
                                  T_BRUSHLESS_3_SPI_Read      fnRead )
{
    fpWriteSPI = fnWrite;
    fpReadSPI  = fnRead;
}
#endif
#if BRUSHLESS_3_I2C_CLICK == 1
void BRUSHLESS_3_I2CdriverInit( T_BRUSHLESS_3_I2C_Start     fnStart,
                                  T_BRUSHLESS_3_I2C_Stop      fnStop,
                                  T_BRUSHLESS_3_I2C_Restart   fnRestart,
                                  T_BRUSHLESS_3_I2C_Write     fnWrite,
                                  T_BRUSHLESS_3_I2C_Read      fnRead )
{
    fpStartI2C    = fnStart;
    fpStopI2C     = fnStop;
    fpRestartI2C  = fnRestart;
    fpWriteI2C    = fnWrite;
    fpReadI2C     = fnRead;
}
#endif
#if BRUSHLESS_3_UART_CLICK == 1
void BRUSHLESS_3_UARTdriverInit( T_BRUSHLESS_3_UART_Write   fnWrite,
                                   T_BRUSHLESS_3_UART_Read    fnRead,
                                   T_BRUSHLESS_3_UART_Ready   fnReady )
{
    fpWriteUART = fnWrite;
    fpReadUART  = fnRead;
    fpReadyUART = fnReady;
}
#endif

// IMPLEMENTATION






/** @endcond */
/** @} */
/*------------------------------------------------------------------------------

  __BRUSHLESS_3_Driver.c

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
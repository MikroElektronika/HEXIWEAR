/*

    __FAN2_Driver.c

    Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

------------------------------------------------------------------------------*/

/**
@file           __FAN2_Driver.c
@addtogroup     FAN2
@{
------------------------------------------------------------------------------*/

#include "__FAN2_Hal.h"
#include "__FAN2_Hal.c"
#include "__FAN2_Driver.h"

/**
 * @name    Fan_2 Click GPIO
 *//*-------------------------------------------------------------------------*/
///@{


///@}
/*----------------------------------------------------------------- VARIABLES */

/** FLIR I2C slave interface address */
const uint8_t _FAN2_I2C_ADDRESS         = 0x50;


/**
 * @name    Fan_2 Click Return Values
 *//*-------------------------------------------------------------------------*/
///@{

uint8_t _FAN2_OK     = 0;               /**< NO ERROR */
uint8_t _FAN2_ERR    = 1;               /**< ERROR OCCURED */

///@}
/**
 * @name    Fan_2 Click Read/Write Registers
 *//*-------------------------------------------------------------------------*/
///@{

const uint8_t _FAN2_CONTROL_REGISTER_1 = 0x00;     /**< Control Register 1 Address */
const uint8_t _FAN2_CONTROL_REGISTER_2 = 0x01;     /**< Control Register 2 Address */
const uint8_t _FAN2_CONTROL_REGISTER_3 = 0x02;     /**< Control Register 3 Address */

const uint8_t _FAN2_FAIL_DUTY_REGISTER = 0x03;     /**< Fail Duty Cycle Reg Address */
const uint8_t _FAN2_ALERT_MASK_REGISTER = 0x04;    /**< Alert Mask Register Address */
const uint8_t _FAN2_IDEALITY_FACTOR_REGISTER = 0x05;  /**< Ideality Factor Register Address */

const uint8_t _FAN2_RHSH_REGISTER = 0x06;   /**< Remote High Set-point MSB */
const uint8_t _FAN2_RHSL_REGISTER = 0x07;   /**< Remote High Set-point LSB */
const uint8_t _FAN2_LOTSH_REGISTER = 0x08;  /**< Local Overtemperature Set-point MSB */
const uint8_t _FAN2_LOTSL_REGISTER = 0x09;  /**< Local Overtemperature Set-point LSB */
const uint8_t _FAN2_ROTSH_REGISTER = 0x0A;  /**< Remote Overtemperature Set-point MSB */
const uint8_t _FAN2_ROTSL_REGISTER = 0x0B;  /**< Remote Overtemperature Set-point LSB */
const uint8_t _FAN2_LHSH_REGISTER = 0x0C;  /**< Local High Set-point MSB */
const uint8_t _FAN2_LHSL_REGISTER = 0x0D;  /**< Local High Set-point LSB */

const uint8_t _FAN2_TCTH_REGISTER = 0x0E;  /**< TACH Count Threshold Register MSB */
const uint8_t _FAN2_TCTL_REGISTER = 0x0F;  /**< TACH Count Threshold Register LSB */

const uint8_t _FAN2_DIRECT_CONTROL_REGISTER = 0x50;  /**< Direct Duty-Cycle Control Register */

///@}
/**
 * @name    Fan_2 Click Read Only Registers
 *//*-------------------------------------------------------------------------*/
///@{

const uint8_t _FAN2_PWMV_REGISTER = 0x51;   /**< Current PWM Duty-Cycle Register */
const uint8_t _FAN2_TC1H_REGISTER = 0x52;   /**< TACH1 Count Register, MSB */
const uint8_t _FAN2_TC1L_REGISTER = 0x53;  /**< TACH1 Count Register, LSB */
const uint8_t _FAN2_TC2H_REGISTER = 0x54;  /**< TACH2 Count Register, MSB */
const uint8_t _FAN2_TC2L_REGISTER = 0x55;  /**< TACH2 Count Register, LSB */
const uint8_t _FAN2_RTH_REGISTER = 0x56;  /**< Remote Temperature Reading Register, MSB */
const uint8_t _FAN2_RTL_REGISTER = 0x57;  /**< Remote Temperature Reading Register, LSB */
const uint8_t _FAN2_LTH_REGISTER = 0x58;  /**< Local Temperature Reading Register, MSB */
const uint8_t _FAN2_LTL_REGISTER = 0x59;  /**< Local Temperature Reading Register, LSB */
const uint8_t _FAN2_SR_REGISTER =  0x5A;  /**< Status Register */


///@}
/**
 * @name    Fan_2 Rotation Speed Values
 *//*-------------------------------------------------------------------------*/
///@{
const uint8_t _FAN2_DUTYCYCLE_100 = 0xFF;     /**< 100 percent duty cycle */
const uint8_t _FAN2_DUTYCYCLE_75  = 0xC0;     /**< 75 percent duty cycle */
const uint8_t _FAN2_DUTYCYCLE_50  = 0x80;     /**< 50 percent duty cycle */
const uint8_t _FAN2_DUTYCYCLE_25  = 0x40;     /**< 25 percent duty cycle */
const uint8_t _FAN2_DUTYCYCLE_12  = 0x20;     /**< 12 percent duty cycle */
const uint8_t _FAN2_DUTYCYCLE_0   = 0x00;     /**< duty cycle off */

///@}
/**
 * @name    Fan_2 Command Register Values
 *//*-------------------------------------------------------------------------*/
///@{

const uint8_t _FAN2_CMD1_DEFAULT = 0x01;     /**< Control Register 1 Default Values */
const uint8_t _FAN2_CMD2_DEFAULT = 0x10;     /**< Control Register 2 Default Values */
const uint8_t _FAN2_CMD3_DEFAULT = 0x01;     /**< Control Register 3 Default Values */


const uint8_t _FAN2_CMD1_REMOTE_TEMPERATURE = 0x01;     /**< Use remote temperature */
const uint8_t _FAN2_CMD1_LOCAL_TEMPERATURE = 0x00;      /**< Use local temperature */

const uint8_t _FAN2_CMD2_DIRECT_CONTROL = 0x01;        /**< Direct fan control */
const uint8_t _FAN2_CMD2_AUTOMATIC_CONTROL = 0x00;     /**< Automatic fan control */

const uint8_t _FAN2_CMD3_SLOW_RAMP = 0x00;        /**< Fan speed changes slowly */
const uint8_t _FAN2_CMD3_MEDIUM_RAMP = 0x10;      /**< Fan speed changes at moderate rate */
const uint8_t _FAN2_CMD3_FAST_RAMP = 0x20;        /**< Fan speed changes at high rate */
const uint8_t _FAN2_CMD3_INSTANT_RAMP = 0x30;     /**< Fan speed changes instantly */


///@}
/** @cond PORTING_GUIDE */
/*--------------------------------------------- PRIVATE FUNCTION DECLARATIONS */


static int writeReg(uint8_t regAddr, uint8_t value);
static int readReg(uint8_t regAddr, uint8_t *value);

/*---------------------------------------------- PRIVATE FUNCTION DEFINITIONS */

static int writeReg(uint8_t regAddr, uint8_t value)
{
    int err = 0;
    uint8_t tmp[2];
    tmp[0] = regAddr;
    tmp[1] = value;

    err |= HAL_i2cStart();
    err |= HAL_i2cWrite(_FAN2_I2C_ADDRESS, tmp, 2, END_MODE_STOP);

    return err;
}

static int readReg(uint8_t regAddr, uint8_t *value)
{
    int err = 0;
    uint8_t tmp[1];
    uint8_t val[1];

    tmp[0] = regAddr;

    err |= HAL_i2cStart();
    err |= HAL_i2cWrite(_FAN2_I2C_ADDRESS, tmp, 1, END_MODE_RESTART);
    err |= HAL_i2cRead(_FAN2_I2C_ADDRESS, val, 1, END_MODE_STOP);

    *value = 0;
    *value = val[0];

    return err;
}

/*---------------------------------------------------------- PUBLIC FUNCTIONS */

#ifdef PLD_SPI_CLICK
void FAN2_SPIdriverInit( T_FAN2_SPI_Write     fnWrite,
                                  T_FAN2_SPI_Read      fnRead )
{
    fpWriteSPI = fnWrite;
    fpReadSPI  = fnRead;
} 
#endif
#ifdef PLD_I2C_CLICK
void FAN2_I2CdriverInit( T_FAN2_I2C_Start     fnStart, 
                                  T_FAN2_I2C_Stop      fnStop,
                                  T_FAN2_I2C_Restart   fnRestart,
                                  T_FAN2_I2C_Write     fnWrite, 
                                  T_FAN2_I2C_Read      fnRead )
{
    fpStartI2C    = fnStart;
    fpStopI2C     = fnStop;
    fpRestartI2C  = fnRestart;
    fpWriteI2C    = fnWrite;
    fpReadI2C     = fnRead;
}
#endif
#ifdef PLD_UART_CLICK
void FAN2_UARTdriverInit( T_FAN2_UART_Write   fnWrite,
                                   T_FAN2_UART_Read    fnRead,
                                   T_FAN2_UART_Ready   fnReady )
{
    fpWriteUART = fnWrite;
    fpReadUART  = fnRead;
    fpReadyUART = fnReady;
}
#endif


int FAN2_sendCommand( uint8_t regAddr, uint8_t command )
{
    int err = 0;
    err |= writeReg(regAddr, command);
    return err;
}

int FAN2_readRegister(uint8_t regAddr, uint8_t *pValue)
{
    int err = 0;
    err |= readReg(regAddr, pValue);
    return err;
}

int FAN2_setupLUT(uint8_t *pValue)
{
    int err = 0;
    int i;
    
    for (i = 0x20; i < 0x4F; i++)
    {
        err |= writeReg(i, pValue[i-0x20]);
    }

    return err;
}


/** @endcond */
/** @} */
/*------------------------------------------------------------------------------

  __FAN2_Driver.c

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
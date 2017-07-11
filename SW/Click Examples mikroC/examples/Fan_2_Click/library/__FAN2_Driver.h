/*

    __FAN2_Driver.h

    Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

------------------------------------------------------------------------------*/

/**
@file           __FAN2_Driver.h
@brief                         Fan_2 Click

@mainpage Fan_2 Click
@{

### Click Description ###

The MAX31760 integrates temperature sensing along
with precision PWM fan control. It accurately measures
its local die temperature and the remote temperature of
a discrete diode-connected transistor, such as a 2N3906,
or a thermal diode commonly found on CPUs, graphics
processor units (GPUs), and other ASICs. Multiple temperature
thresholds, such as local high/overtemperature
(OT) and remote high/overtemperature, can be set by an
I2C-compatible interface.

@}

@defgroup    FAN2
@brief       Fan_2 Click Driver
@{

| Global Library Prefix | **FAN2** |
|:---------------------:|:-----------------:|
| Version               | **1.0.0**    |
| Date                  | **Jul 2017.**      |
| Developer             | *Djordje Rosic*       |


### Library Descritption ###

This library contains functions for basic and advanced operation of FAN 2 click.

@}
*//*--------------------------------------------------------------------------*/
/**
    @example Click_Fan_2_STM.c
    @example Click_Fan_2_TIVA.c
    @example Click_Fan_2_CEC.c
    @example Click_Fan_2_KINETIS.c
    @example Click_Fan_2_MSP.c
    @example Click_Fan_2_PIC.c
    @example Click_Fan_2_PIC32.c
    @example Click_Fan_2_DSPIC.c
    @example Click_Fan_2_AVR.c
    @example Click_Fan_2_FT90x.c
    @example Click_Fan_2_STM.mbas
    @example Click_Fan_2_TIVA.mbas
    @example Click_Fan_2_CEC.mbas
    @example Click_Fan_2_KINETIS.mbas
    @example Click_Fan_2_MSP.mbas
    @example Click_Fan_2_PIC.mbas
    @example Click_Fan_2_PIC32.mbas
    @example Click_Fan_2_DSPIC.mbas
    @example Click_Fan_2_AVR.mbas
    @example Click_Fan_2_FT90x.mbas
    @example Click_Fan_2_STM.mpas
    @example Click_Fan_2_TIVA.mpas
    @example Click_Fan_2_CEC.mpas
    @example Click_Fan_2_KINETIS.mpas
    @example Click_Fan_2_MSP.mpas
    @example Click_Fan_2_PIC.pas
    @example Click_Fan_2_PIC32.pas
    @example Click_Fan_2_DSPIC.pas
    @example Click_Fan_2_AVR.pas
    @example Click_Fan_2_FT90x.pas

*//*--------------------------------------------------------------------------*/

#ifndef _FAN2_H_
#define _FAN2_H_

#include <stdint.h>
#include "__FAN2_Hal.h"


extern uint8_t _FAN2_OK;
extern uint8_t _FAN2_ERR;


/*
 *   Fan_2 Click Read/Write Registers
 *//*-------------------------------------------------------------------------*/

extern const uint8_t _FAN2_CONTROL_REGISTER_1;    /**< Control Register 1 Address */
extern const uint8_t _FAN2_CONTROL_REGISTER_2;     /**< Control Register 2 Address */
extern const uint8_t _FAN2_CONTROL_REGISTER_3;   /**< Control Register 3 Address */

extern const uint8_t _FAN2_FAIL_DUTY_REGISTER;    /**< Fail Duty Cycle Reg Address */
extern const uint8_t _FAN2_ALERT_MASK_REGISTER;    /**< Alert Mask Register Address */
extern const uint8_t _FAN2_IDEALITY_FACTOR_REGISTER; /**< Ideality Factor Register Address */

extern const uint8_t _FAN2_RHSH_REGISTER; /**< Remote High Set-point MSB */
extern const uint8_t _FAN2_RHSL_REGISTER;  /**< Remote High Set-point LSB */
extern const uint8_t _FAN2_LOTSH_REGISTER;  /**< Local Overtemperature Set-point MSB */
extern const uint8_t _FAN2_LOTSL_REGISTER; /**< Local Overtemperature Set-point LSB */
extern const uint8_t _FAN2_ROTSH_REGISTER;  /**< Remote Overtemperature Set-point MSB */
extern const uint8_t _FAN2_ROTSL_REGISTER; /**< Remote Overtemperature Set-point LSB */
extern const uint8_t _FAN2_LHSH_REGISTER; /**< Local High Set-point MSB */
extern const uint8_t _FAN2_LHSL_REGISTER;  /**< Local High Set-point LSB */

extern const uint8_t _FAN2_TCTH_REGISTER;  /**< TACH Count Threshold Register MSB */
extern const uint8_t _FAN2_TCTL_REGISTER;  /**< TACH Count Threshold Register LSB */

extern const uint8_t _FAN2_DIRECT_CONTROL_REGISTER;  /**< Direct Duty-Cycle Control Register */

/*
 *   Fan_2 Click Read Only Registers
 *//*-------------------------------------------------------------------------*/


extern const uint8_t _FAN2_PWMV_REGISTER;   /**< Current PWM Duty-Cycle Register */
extern const uint8_t _FAN2_TC1H_REGISTER;   /**< TACH1 Count Register, MSB */
extern const uint8_t _FAN2_TC1L_REGISTER;   /**< TACH1 Count Register, LSB */
extern const uint8_t _FAN2_TC2H_REGISTER;   /**< TACH2 Count Register, MSB */
extern const uint8_t _FAN2_TC2L_REGISTER;   /**< TACH2 Count Register, LSB */
extern const uint8_t _FAN2_RTH_REGISTER;    /**< Remote Temperature Reading Register, MSB */
extern const uint8_t _FAN2_RTL_REGISTER;    /**< Remote Temperature Reading Register, LSB */
extern const uint8_t _FAN2_LTH_REGISTER;    /**< Local Temperature Reading Register, MSB */
extern const uint8_t _FAN2_LTL_REGISTER;    /**< Local Temperature Reading Register, LSB */
extern const uint8_t _FAN2_SR_REGISTER;     /**< Status Register */



/*
 *     Fan_2 Rotation Speed Values
 *//*-------------------------------------------------------------------------*/

extern const uint8_t _FAN2_DUTYCYCLE_100;     /**< 100 percent duty cycle */
extern const uint8_t _FAN2_DUTYCYCLE_75;      /**< 75 percent duty cycle */
extern const uint8_t _FAN2_DUTYCYCLE_50;      /**< 50 percent duty cycle */
extern const uint8_t _FAN2_DUTYCYCLE_25;      /**< 25 percent duty cycle */
extern const uint8_t _FAN2_DUTYCYCLE_12;      /**< 12 percent duty cycle */
extern const uint8_t _FAN2_DUTYCYCLE_0;       /**< Duty cycle off */


/*
 *    Fan_2 Command Register Values
 *//*-------------------------------------------------------------------------*/


extern const uint8_t _FAN2_CMD1_DEFAULT;
extern const uint8_t _FAN2_CMD2_DEFAULT;
extern const uint8_t _FAN2_CMD3_DEFAULT;

extern const uint8_t _FAN2_CMD1_REMOTE_TEMPERATURE;     /**< Use remote temperature */
extern const uint8_t _FAN2_CMD1_LOCAL_TEMPERATURE;      /**< Use local temperature  */

extern const uint8_t _FAN2_CMD2_DIRECT_CONTROL;       /**< Direct fan control */
extern const uint8_t _FAN2_CMD2_AUTOMATIC_CONTROL;    /**< Automatic fan control */

extern const uint8_t _FAN2_CMD3_SLOW_RAMP;        /**< Fan speed changes slowly */
extern const uint8_t _FAN2_CMD3_MEDIUM_RAMP;        /**< Fan speed changes at moderate rate */
extern const uint8_t _FAN2_CMD3_FAST_RAMP;        /**< Fan speed changes at high rate */
extern const uint8_t _FAN2_CMD3_INSTANT_RAMP;     /**< Fan speed changes instantly */

/** @addtogroup FAN2 */
///@{
/**
 * @name                 Fan_2 Click Types
 *//*-------------------------------------------------------------------------*/
///@{


///@}
/**
 * @name                 Fan_2 Click Driver Functions
 *//*-------------------------------------------------------------------------*/
///@{
#ifdef __cplusplus
extern "C"{
#endif
#ifdef PLD_SPI_CLICK
/**
 * @brief FAN2 SPI Driver Initialization
 *
 * @param[in] fnWrite   SPI Write Function
 * @param[in] fnRead    SPI Read  Function
 *
 * Initialization of FAN2 SPI driver.
 *
 * @note
 * This function must be called first.
 *
 */
void FAN2_SPIdriverInit( T_FAN2_SPI_Write     fnWrite,
                                  T_FAN2_SPI_Read      fnRead );
#endif
#ifdef PLD_I2C_CLICK
/**
 * @brief FAN2 I2C Driver Initialization
 *
 * @param[in] fnStart    I2C Start   Function
 * @param[in] fnStop     I2C Stop    Function
 * @param[in] fnReastart I2C Restart Function
 * @param[in] fnWrite    I2C Write   Function
 * @param[in] fnRead     I2C Read    Function
 *
 * Initialization of FAN2 I2C driver.
 *
 * @note
 * This function must be called first.
 *
 * @note
 * Some compilers don't have all the function pointers, for example
 * mikroE ARM compilers don't have the I2C_Stop function, in that case
 * it is enough to provide NULL pointer.
 */
void FAN2_I2CdriverInit( T_FAN2_I2C_Start        fnStart,
                                  T_FAN2_I2C_Stop         fnStop,
                                  T_FAN2_I2C_Restart      fnRestart,
                                  T_FAN2_I2C_Write        fnWrite,
                                  T_FAN2_I2C_Read         fnRead );
#endif
#ifdef PLD_UART_CLICK
/**
 * @brief FAN2 UART Driver Initialization
 *
 * @param[in] fnWrite   UART Write Function
 * @param[in] fnRead    UART Ready Function
 * @param[in] fnReady   UART Data Ready Function
 *
 * Initialization of FAN2 UART driver.
 *
 * @note
 * This function must be called first.
 *
 */
void FAN2_UARTdriverInit( T_FAN2_UART_Write   fnWrite,
                                   T_FAN2_UART_Read    fnRead,
                                   T_FAN2_UART_Ready   fnReady );
#endif



/**
 * @brief FAN2 Write Command
 *
 * @param[in] regAddr    Register to write to
 * @param[out] command    Write data
 *
 * Generic write function for Fan 2 click.
 *
 * @note
 * Registers 0x51 - 0x5A are read only, do not use this function on them.
 *
 */
int FAN2_sendCommand( uint8_t regAddr, uint8_t command );

/**
 * @brief FAN2 Read Register
 *
 * @param[in] regAddr    Register to read
 * @param[out] pValue    Read data
 *
 * Generic read function for Fan 2 click.
 *
 * @note
 * Register 0x5B (EEX) is write only, any other register can be read using this
 * function.
 *
 */
int FAN2_readRegister(uint8_t regAddr, uint8_t *pValue);

/**
 * @brief FAN2 Look-up Table Setup
 *
 * @param[in] pValue   48 bytes array of input
 *
 * This function fills the LUT registers with passed values.
 *
 * @note
 * This function controls the dependancy of fan rotation speed on temperature.
 * Fan 2 click must also be configured for automatic control, and the proper
 * temperature source (remote or local) must be set.
 *
 */
int FAN2_setupLUT(uint8_t *pValue);


#ifdef __cplusplus
} // extern "C"
#endif
#endif
///@}
///@}
/*------------------------------------------------------------------------------

  __FAN2_Driver.h

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
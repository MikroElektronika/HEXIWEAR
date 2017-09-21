/*

    __PAC1934_Driver.h

    Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

------------------------------------------------------------------------------*/

/**
@file           __PAC1934_Driver.h
@brief                         PAC1934 Click

@mainpage PAC1934 Click
@{

### Click Description ###

The PAC1932, PAC1933 and PAC1934 products are
two, three and four channel energy monitors, with bus
voltage monitors and current sense amplifiers that feed
high resolution ADCs. Digital circuitry performs power
calculations and energy accumulation.
This enables energy monitoring with integration periods
from 1 mS up to 36 hours or longer.

@}

@defgroup    PAC1934
@brief       PAC1934 Click Driver
@{

| Global Library Prefix | **PAC1934** |
|:---------------------:|:-----------------:|
| Version               | **1.0.0**    |
| Date                  | **Aug 2017.**      |
| Developer             | *Djordje Rosic*       |


### Library Descritption ###

This library contains basic read/write/command functions that enable flexible
communication with the PAC1934 click, as well as advanced read functions for
energy, power, current and voltage calculation.

@}
*//*--------------------------------------------------------------------------*/
/**
    @example Click_PAC1934_STM.c
    @example Click_PAC1934_TIVA.c
    @example Click_PAC1934_CEC.c
    @example Click_PAC1934_KIN.c
    @example Click_PAC1934_MSP.c
    @example Click_PAC1934_PIC.c
    @example Click_PAC1934_PIC32.c
    @example Click_PAC1934_DSPIC.c
    @example Click_PAC1934_AVR.c
    @example Click_PAC1934_FT90x.c
    @example Click_PAC1934_STM.mbas
    @example Click_PAC1934_TIVA.mbas
    @example Click_PAC1934_CEC.mbas
    @example Click_PAC1934_KIN.mbas
    @example Click_PAC1934_MSP.mbas
    @example Click_PAC1934_PIC.mbas
    @example Click_PAC1934_PIC32.mbas
    @example Click_PAC1934_DSPIC.mbas
    @example Click_PAC1934_AVR.mbas
    @example Click_PAC1934_FT90x.mbas
    @example Click_PAC1934_STM.mpas
    @example Click_PAC1934_TIVA.mpas
    @example Click_PAC1934_CEC.mpas
    @example Click_PAC1934_KIN.mpas
    @example Click_PAC1934_MSP.mpas
    @example Click_PAC1934_PIC.pas
    @example Click_PAC1934_PIC32.pas
    @example Click_PAC1934_DSPIC.pas
    @example Click_PAC1934_AVR.pas
    @example Click_PAC1934_FT90x.pas

*//*--------------------------------------------------------------------------*/

#ifndef _PAC1934_H_
#define _PAC1934_H_

#include <stdint.h>
#include "__PAC1934_Hal.h"


extern uint8_t _PAC1934_OK;
extern uint8_t _PAC1934_ERR;


/** @addtogroup PAC1934 */
///@{
/**
 * @name                 PAC1934 Click Types
 *//*-------------------------------------------------------------------------*/
///@{


///@}

/**
 * @name    PAC1934 Click Registers
 *//*-------------------------------------------------------------------------*/
///@{

extern uint8_t _PAC1934_REFRESH_CMD;                             /**< Refresh command */
extern uint8_t _PAC1934_CTRL_REG;                             /**< Control register */

extern uint8_t _PAC1934_ACC_COUNT;                             /**< Accumulator count */
extern uint8_t _PAC1934_VPOWER1_ACC;                             /**< Accumulated power 1 */
extern uint8_t _PAC1934_VPOWER2_ACC;                             /**< Accumulated power 2 */
extern uint8_t _PAC1934_VPOWER3_ACC;                             /**< Accumulated power 3 */
extern uint8_t _PAC1934_VPOWER4_ACC;                             /**< Accumulated power 4 */

extern uint8_t _PAC1934_VBUS1;                             /**< Most recent Vbus sample 1 */
extern uint8_t _PAC1934_VBUS2;                             /**< Most recent Vbus sample 2 */
extern uint8_t _PAC1934_VBUS3;                             /**< Most recent Vbus sample 3 */
extern uint8_t _PAC1934_VBUS4;                             /**< Most recent Vbus sample 4 */
extern uint8_t _PAC1934_VSENSE1;                             /**< Most recent Vsense sample 1 */
extern uint8_t _PAC1934_VSENSE2;                             /**< Most recent Vsense sample 2 */
extern uint8_t _PAC1934_VSENSE3;                             /**< Most recent Vsense sample 3 */
extern uint8_t _PAC1934_VSENSE4;                             /**< Most recent Vsense sample 4 */

extern uint8_t _PAC1934_VBUS1_AVG;                             /**< Average Vbus sample 1 */
extern uint8_t _PAC1934_VBUS2_AVG;                             /**< Average Vbus sample 2 */
extern uint8_t _PAC1934_VBUS3_AVG;                             /**< Average Vbus sample 3 */
extern uint8_t _PAC1934_VBUS4_AVG;                             /**< Average Vbus sample 4 */
extern uint8_t _PAC1934_VSENSE1_AVG;                             /**< Average Vsense sample 1 */
extern uint8_t _PAC1934_VSENSE2_AVG;                             /**< Average Vsense sample 2 */
extern uint8_t _PAC1934_VSENSE3_AVG;                             /**< Average Vsense sample 3 */
extern uint8_t _PAC1934_VSENSE4_AVG;                             /**< Average Vsense sample 4 */

extern uint8_t _PAC1934_VPOWER1;                             /**< Vbus and Vsense product 1 */
extern uint8_t _PAC1934_VPOWER2;                             /**< Vbus and Vsense product 2 */
extern uint8_t _PAC1934_VPOWER3;                             /**< Vbus and Vsense product 3 */
extern uint8_t _PAC1934_VPOWER4;                             /**< Vbus and Vsense product 4 */

extern uint8_t _PAC1934_CHANNEL_DIS;                         /**< Channel disable and other settings */
extern uint8_t _PAC1934_NEG_PWR;                         /**< Bidirectional measurements settings */

extern uint8_t _PAC1934_REFRESH_G_CMD;                             /**< Refresh G command */
extern uint8_t _PAC1934_REFRESH_V_CMD;                             /**< Refresh V command */

extern uint8_t _PAC1934_SLOW;                             /**< Slow pin state and settings */

extern uint8_t _PAC1934_CTRL_ACT;                           /**< Actual state of CTRL register*/
extern uint8_t _PAC1934_DIS_ACT;                           /**< Actual state of CHANNEL_DIS register*/
extern uint8_t _PAC1934_NEG_PWR_ACT;                           /**< Actual state of NEG_PWR register*/

extern uint8_t _PAC1934_CTRL_LAT;                           /**< Latched state of CTRL register*/
extern uint8_t _PAC1934_DIS_LAT;                           /**< Latched state of CHANNEL_DIS register*/
extern uint8_t _PAC1934_NEG_PWR_LAT;                           /**< Latched state of NEG_PWR register*/

extern uint8_t _PAC1934_PRODUCT_ID;                           /**< Product ID register*/
extern uint8_t _PAC1934_MANUFACT_ID;                           /**< Manufacturer ID register*/
extern uint8_t _PAC1934_REVISION_ID;                           /**< Revision ID register*/

///@}
/**
 * @name                 PAC1934 Click Driver Functions
 *//*-------------------------------------------------------------------------*/
///@{
#ifdef __cplusplus
extern "C"{
#endif


#if PAC1934_SPI_CLICK == 1
/**
 * @brief PAC1934 SPI Driver Initialization
 *
 * @param[in] fnWrite   SPI Write Function
 * @param[in] fnRead    SPI Read  Function
 *
 * Initialization of PAC1934 SPI driver.
 *
 * @note
 * This function must be called first.
 *
 */
void PAC1934_SPIdriverInit( T_PAC1934_SPI_Write     fnWrite,
                                  T_PAC1934_SPI_Read      fnRead );
#endif
#if PAC1934_I2C_CLICK == 1
/**
 * @brief PAC1934 I2C Driver Initialization
 *
 * @param[in] fnStart    I2C Start   Function
 * @param[in] fnStop     I2C Stop    Function
 * @param[in] fnReastart I2C Restart Function
 * @param[in] fnWrite    I2C Write   Function
 * @param[in] fnRead     I2C Read    Function
 *
 * Initialization of PAC1934 I2C driver.
 *
 * @note
 * This function must be called first.
 *
 * @note
 * Some compilers don't have all the function pointers, for example
 * mikroE ARM compilers don't have the I2C_Stop function, in that case
 * it is enough to provide NULL pointer.
 */
void PAC1934_I2CdriverInit( T_PAC1934_I2C_Start        fnStart,
                                  T_PAC1934_I2C_Stop         fnStop,
                                  T_PAC1934_I2C_Restart      fnRestart,
                                  T_PAC1934_I2C_Write        fnWrite,
                                  T_PAC1934_I2C_Read         fnRead );
#endif
#if PAC1934_UART_CLICK == 1
/**
 * @brief PAC1934 UART Driver Initialization
 *
 * @param[in] fnWrite   UART Write Function
 * @param[in] fnRead    UART Ready Function
 * @param[in] fnReady   UART Data Ready Function
 *
 * Initialization of PAC1934 UART driver.
 *
 * @note
 * This function must be called first.
 *
 */
void PAC1934_UARTdriverInit( T_PAC1934_UART_Write   fnWrite,
                                   T_PAC1934_UART_Read    fnRead,
                                   T_PAC1934_UART_Ready   fnReady );
#endif


/**
 * @brief PAC1934 Send Command
 *
 * @param[in] command   Command to execute
 *
 * Executes PAC1934 refresh commands.
 *
 * @note
 * Calling this function with _PAC1934_REFRESH_G_CMD parameter will issue a
 * global command to all the devices on the bus.
 */
void PAC1934_sendCommand (uint8_t command);

/**
 * @brief PAC1934 Write Register
 *
 * @param[in] inputAddress   Address of register
 * @param[in] inputData      Data to write
 *
 * Writes the data into selected PAC1934 register.
 */
void PAC1934_writeReg (uint8_t inputAddress, uint8_t inputData);

/**
 * @brief PAC1934 Read Register(s)
 *
 * @param[in] inputAddress   Address of first register to read
 * @param[in] count          Number of bytes to read
 * @param[out] outputData    Read Data
 *
 * Reads the data from PAC1934 registers. Internal address pointer auto-
 * increments, so it is possible to read multiple registers at once.
 *
 * @note
 * If some of the channels are disabled in the _PAC1934_CHANNEL_DIS register,
 * address pointer auto-increment will skip them. This behaviour can be changed
 * by writing 1 to the NO SKIP bit in the same register. Values read from
 * disabled channels will always be 0xFF however.
 */
void PAC1934_readReg (uint8_t inputAddress, uint8_t *outputData, uint8_t count);

/**
 * @brief PAC1934 Measure Voltage
 *
 * @param[in] channel   Channel from which to read
 *
 * Reads the voltage data from one of the _PAC1934_VBUS registers, depending 
 * on the selected channel and converts it into float value expressed in Volts.
 *
 * @note
 * This command reads voltage from the time of the most recent refresh command.
 */
float PAC1934_measureVoltage (uint8_t channel);
/**
 * @brief PAC1934 Measure Current
 *
 * @param[in] channel   Channel from which to read
 *
 * Reads the current data from one of the _PAC1934_VSENSE registers, depending
 * on the selected channel and converts it into float value expressed in mA.
 *
 * @note
 * This command reads current from the time of the most recent refresh command.
 */
float PAC1934_measureCurrent (uint8_t channel);
/**
 * @brief PAC1934 Measure Power
 *
 * @param[in] channel   Channel from which to read
 *
 * Reads the power data from one of the _PAC1934_VPOWER registers, depending
 * on the selected channel and converts it into float value expressed in Watts.
 *
 * @note
 * This command reads power from the time of the most recent refresh command.
 */
float PAC1934_measurePower (uint8_t channel);


#if defined __MIKROC_PRO_FOR_AVR__  || defined ( __MIKROC_PRO_FOR_PIC__ )     \
              || defined ( __MIKROC_PRO_FOR_DSPIC__ )
//uint64 not supported
#elif 1
/**
 * @brief PAC1934 Measure Energy
 *
 * @param[in] channel      Channel from which to read
 * @param[in] sampleRate   Selected sample rate
 *
 * Reads the energy data from one of the accumulator registers, depending
 * on the selected channel and converts it into float value expressed in Joules.
 *
 * @note
 * This command reads energy from the time of the most recent refresh command.
 */
float PAC1934_measureEnergy (uint8_t channel, uint16_t sampleRate);
#endif

#ifdef __cplusplus
} // extern "C"
#endif
#endif
///@}
///@}
/*------------------------------------------------------------------------------

  __PAC1934_Driver.h

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
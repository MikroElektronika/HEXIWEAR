/*

    __STEPPER_Driver.h

    Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

------------------------------------------------------------------------------*/

/**
@file           __STEPPER_Driver.h
@brief                         Stepper 4 Click

@mainpage Stepper 4 Click
@{

### Click Description ###

Stepper 4 is a click with a CLOCK-in controlled bipolar stepping motor driver.

@}

@defgroup    STEPPER
@brief       Stepper 4 Click Driver
@{

| Global Library Prefix | **STEPPER**        |
|:---------------------:|:------------------:|
| Version               | **1.0.0**          |
| Date                  | **August 2017**    |
| Developer             | *Irena Blagojevic* |


### Library Descritption ###

Library covers all stepper motor drivers.

@}
*//*--------------------------------------------------------------------------*/
/**
    @example Click_Stepper_4_STM.c
    @example Click_Stepper_4_TIVA.c
    @example Click_Stepper_4_KINETIS.c
    @example Click_Stepper_4_PIC.c
    @example Click_Stepper_4_PIC32.c
    @example Click_Stepper_4_DSPIC.c
    @example Click_Stepper_4_AVR.c
    @example Click_Stepper_4_FT90x.c

*//*--------------------------------------------------------------------------*/

#ifndef _STEPPER_H_
#define _STEPPER_H_

#include <stdint.h>
#include "__STEPPER_Hal.h"


/** @addtogroup STEPPER */
///@{
/**
 * @name                 Stepper 4 Click Types
 *//*-------------------------------------------------------------------------*/
///@{

/**
 * @enum T_STEPPER_direction
 * @brief Direction Indicator
 *
 * + DIR_CCW - Counter Clockwise
 * + DIR_CW - Clockwise
 */
typedef enum
{
    STEPPER_DIR_CCW = 0,
    STEPPER_DIR_CW  = 1

} T_STEPPER_direction;

///@}
/**
 * @name                 Stepper 4 Click Driver Functions
 *//*-------------------------------------------------------------------------*/
///@{
#ifdef __cplusplus
extern "C"{
#endif

void STEPPER_GPIOmap( T_STEPPER_GPIO_Set ctlDIR, T_STEPPER_GPIO_Set ctlEN,
                      T_STEPPER_GPIO_Set ctlST, T_STEPPER_GPIO_Set ctlRST,
                      T_STEPPER_GPIO_Set ctlINT );

#if STEPPER_SPI_CLICK == 1
/**
 * @brief STEPPER SPI Driver Initialization
 *
 * @param[in] fnWrite   SPI Write Function
 * @param[in] fnRead    SPI Read  Function
 *
 * Initialization of STEPPER SPI driver.
 *
 * @note
 * This function must be called first.
 *
 */
void STEPPER_SPIdriverInit( T_STEPPER_SPI_Write     fnWrite,
                                  T_STEPPER_SPI_Read      fnRead );
#endif
#if STEPPER_I2C_CLICK == 1
/**
 * @brief STEPPER I2C Driver Initialization
 *
 * @param[in] fnStart    I2C Start   Function
 * @param[in] fnStop     I2C Stop    Function
 * @param[in] fnReastart I2C Restart Function
 * @param[in] fnWrite    I2C Write   Function
 * @param[in] fnRead     I2C Read    Function
 *
 * Initialization of STEPPER I2C driver.
 *
 * @note
 * This function must be called first.
 *
 * @note
 * Some compilers don't have all the function pointers, for example
 * mikroE ARM compilers don't have the I2C_Stop function, in that case
 * it is enough to provide NULL pointer.
 */
void STEPPER_I2CdriverInit( T_STEPPER_I2C_Start        fnStart,
                                  T_STEPPER_I2C_Stop         fnStop,
                                  T_STEPPER_I2C_Restart      fnRestart,
                                  T_STEPPER_I2C_Write        fnWrite,
                                  T_STEPPER_I2C_Read         fnRead );
#endif
#if STEPPER_UART_CLICK == 1
/**
 * @brief STEPPER UART Driver Initialization
 *
 * @param[in] fnWrite   UART Write Function
 * @param[in] fnRead    UART Ready Function
 * @param[in] fnReady   UART Data Ready Function
 *
 * Initialization of STEPPER UART driver.
 *
 * @note
 * This function must be called first.
 *
 */
void STEPPER_UARTdriverInit( T_STEPPER_UART_Write   fnWrite,
                                   T_STEPPER_UART_Read    fnRead,
                                   T_STEPPER_UART_Ready   fnReady );
#endif

/**
 * @brief <h3> HW Layer Initialization </h3>
 *
 * @par Prepares library for usage and sets needed values to default.
 *
 * @param[in] numOfSteps           number of steps per revolution of used motor
 * @param[in] timer                timer speed in microseconds
 *
 * @note This function must be called first.
 *
 * Example :
 * @code
 * STEPPER_init( 200, 100 );
 * @endcode
 */
void STEPPER_init( uint8_t numOfSteps, uint16_t timer );
    
/**
 * @brief Moving functions pointers initilisation
 *
 * @par Set pointers to functions implementing clockwise and counterclockwise
 * movements.
 *
 * @note This function must be called if STEPPER_MOTORIF_FUNCTION interface
 * is selected. @link STEPPER_right @endlink and @link STEPPER_left @endlink
 * functions are provided in this library.
 */
void STEPPER_initFp( void ( *fpFwd )(  ), void ( *fpBckwd )(  ));

/**
 * @brief Set motor speed
 *
 * @par Set speed at which the motor should run.
 *
 * @param[in] newSpeed        speed in steps per second
 *
 * @note Maximal speeds depends on the motor and common sense
 */
void STEPPER_setSpeed(uint16_t newSpeed);

/**
 * @brief Set acceleration
 *
 * @par Set the acceleration rate.
 *
 * @param[in] newAcc       accel. rate in steps per second per step made
 *
 * @note Acceleration rate should be greater than zero.
 * First step is made at speed equal to \a acc. Following every next step, 
 * speed increases by \a acc, until it reaches previously set speed.
 */    
void STEPPER_setAcc(uint16_t newAcc);

/**
 * @brief Set decelration
 *
 * @par Set the deceleration rate.
 *
 * @param[in] newDec       decel. rate in steps per second per step made
 *
 * @note Deceleration rate should be greater than zero. Deceleration starts at
 * a certain point - after each step the previously set speed decreases by
 * \a dec value, until the motor completely stops.
 */
void STEPPER_setDec(uint16_t newDec);

/**
 * @brief Move a given number of steps
 *
 * @param[in] stepsToMove       number of steps to move
 *
 * @note Must be called after @link STEPPER_setSpeed @endlink.
 * If \a stepsToMove is greater than zero, it indicates clockwise movement,
 * otherwise motor will move counterclockwise.
 */
void STEPPER_step(int32_t stepsToMove);

/**
 * @brief Current Speed
 *
 * @return The most recently set speed.
 */
uint16_t STEPPER_readSpeed();


/**
 * @brief The currently motor position.
 *
 * @return Current motor position relative to initial (zero) position.
 *
 * @note Positive is clockwise from the 0 position in steps.
 */
int32_t STEPPER_readCurrentPos();

/**
 * @brief Make a clockwise step.
 */
void STEPPER_right();

/**
 * @brief Make a counterclockwise step.
 */
void STEPPER_left();

/**
 * @brief Interrupt service routine.
 *
 * @note Increment a counter representing timer ticks.
 */
void STEPPER_handler();

/**
 * @brief Read timer ticks.
 *
 * @return Current timer state in microseconds.
 */    
uint32_t STEPPER_readMicros();
  
#ifdef __cplusplus
} // extern "C"
#endif
#endif
///@}
///@}
/*------------------------------------------------------------------------------

  __STEPPER_Driver.h

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

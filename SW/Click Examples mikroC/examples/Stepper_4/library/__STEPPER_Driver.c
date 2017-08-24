/*

  __STEPPER_Driver.c

  Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

------------------------------------------------------------------------------*/

/**
   @file           __STEPPER_Driver.c
   @addtogroup     STEPPER
   @{
------------------------------------------------------------------------------*/

#include "__STEPPER_Hal.h"
#include "__STEPPER_Hal.c"
#include "__STEPPER_Driver.h"

uint8_t HIGH = 1;
uint8_t LOW = 0;

/**
 * @name    Stepper 4 Click Return Values
 *//*-------------------------------------------------------------------------*/
///@{

uint8_t _STEPPER_OK     = 0;                                              /**< NO ERROR */
uint8_t _STEPPER_ERR    = 1;                                              /**< ERROR OCCURED */

///@}
/**
 * @name    Stepper 4 Click Registers
 *//*-------------------------------------------------------------------------*/
///@{

///@}
/** @cond PORTING_GUIDE */
/*----------------------------------------------------------------- VARIABLES */

static void( *fpForward )();
static void( *fpBackward )();

static volatile uint32_t counter;

static uint16_t speed;
static T_STEPPER_direction direction;
static uint16_t timerSpeed;
static uint16_t currSpeed;
static uint16_t acc;
static uint16_t dec;
static uint32_t stepDelay;
static uint32_t lastStepTime;
static uint8_t motorSteps;
static int32_t stepCount;
static int32_t stepNumber;
static int32_t currentPos;
static uint32_t stepsToStop;
static uint32_t stepsToSpeed;


/*--------------------------------------------- PRIVATE FUNCTION DECLARATIONS */

static void step();

/*---------------------------------------------- PRIVATE FUNCTION DEFINITIONS */

static void step()
{
    if( direction == STEPPER_DIR_CW )
        fpForward();
    else
        fpBackward();
}
/*---------------------------------------------------------- PUBLIC FUNCTIONS */

void STEPPER_GPIOmap( T_STEPPER_GPIO_Set ctlDIR, T_STEPPER_GPIO_Set ctlEN,
                      T_STEPPER_GPIO_Set ctlST, T_STEPPER_GPIO_Set ctlRST,
                      T_STEPPER_GPIO_Set ctlINT )
{
    fpEN    =   ctlEN;
    fpRST   =   ctlRST;
    fpDIR   =   ctlDIR;
    fpINT   =   ctlINT;
    fpST    =   ctlST;
}


#if STEPPER_SPI_CLICK == 1
void STEPPER_SPIdriverInit( T_STEPPER_SPI_Write     fnWrite,
                            T_STEPPER_SPI_Read      fnRead )
{
    fpWriteSPI = fnWrite;
    fpReadSPI  = fnRead;
}
#endif
#if STEPPER_I2C_CLICK == 1
void STEPPER_I2CdriverInit( T_STEPPER_I2C_Start     fnStart,
                            T_STEPPER_I2C_Stop      fnStop,
                            T_STEPPER_I2C_Restart   fnRestart,
                            T_STEPPER_I2C_Write     fnWrite,
                            T_STEPPER_I2C_Read      fnRead )
{
    fpStartI2C    = fnStart;
    fpStopI2C     = fnStop;
    fpRestartI2C  = fnRestart;
    fpWriteI2C    = fnWrite;
    fpReadI2C     = fnRead;
}
#endif
#if STEPPER_UART_CLICK == 1
void STEPPER_UARTdriverInit( T_STEPPER_UART_Write   fnWrite,
                             T_STEPPER_UART_Read    fnRead,
                             T_STEPPER_UART_Ready   fnReady )
{
    fpWriteUART = fnWrite;
    fpReadUART  = fnRead;
    fpReadyUART = fnReady;
}
#endif

// IMPLEMENTATION

void STEPPER_init( uint8_t numOfSteps, uint16_t timer )
{
    motorSteps = numOfSteps;
    currentPos = 0;
    speed = 0;
    currSpeed = 0;
    stepDelay = 0;
    lastStepTime = 0;
    stepsToStop = 0;
    stepsToSpeed = 0;
    direction = STEPPER_DIR_CW;
    acc = 1;
    dec = 1;
    timerSpeed = timer;

    stepCount = 0;
    stepNumber = 0;
    
    STEPPER_initFp( STEPPER_right, STEPPER_left );
    STEPPER_restartHAL();
    STEPPER_enableHAL( 1 );

}

void STEPPER_initFp(void(*fpFwd )( ), void(*fpBckwd)( ))
{
    fpForward = fpFwd;
    fpBackward = fpBckwd;
}

void STEPPER_setSpeed(uint16_t newSpeed)
{
    speed = newSpeed;
    stepDelay = 1000000 / newSpeed;
}

void STEPPER_setAcc(uint16_t newAcc)
{
    if (newAcc > 0)
    {
        acc = newAcc;
    }
}

void STEPPER_setDec(uint16_t newDec)
{
    if (newDec > 0)
    {
        dec = newDec;
    }
}

uint16_t STEPPER_readSpeed()
{
    return speed;
}

void STEPPER_step(int32_t stepsToMove)
{
    uint32_t stepsLeft = fabs(stepsToMove);
    uint8_t stepMade = 1;
    
    stepsToSpeed = (uint32_t)speed / acc;
    stepsToStop = (uint32_t)speed / dec - 1;

    if (stepsToMove > 0)
    {
        direction = STEPPER_DIR_CW;
    }
    else
    {
        direction = STEPPER_DIR_CCW;
    }
    
    while (stepsLeft > 0)
    {
        uint32_t now = STEPPER_readMicros();
        // When not enough time, this order in if-statement ensures
        // deceleration will begin even if target speed is not achieved
        if (currSpeed <= speed && stepsLeft <= stepsToStop && stepMade)
        { // time for deceleration until stop
            currSpeed = (currSpeed-dec) > 0 ? currSpeed-dec : dec;
            stepDelay = 1000000 / currSpeed;
            stepMade = 0;
        }
        else if (currSpeed < speed && stepMade)
        { // target speed not yet achieved
            currSpeed = (currSpeed+acc) <= speed ? currSpeed+acc : speed;
            stepDelay = 1000000 / currSpeed;
            stepMade = 0;
        }
        if ((now > lastStepTime && now - lastStepTime >= stepDelay)
            || (now < lastStepTime
                && UINT32_MAX - lastStepTime + now >= stepDelay))
        {
            lastStepTime = now;
            if (direction == STEPPER_DIR_CW)
            {
                stepNumber++;
                if (stepNumber == motorSteps)
                    stepNumber = 0;
            }
            else
            {
                if (stepNumber == 0)
                {
                    stepNumber = motorSteps;
                }
                stepNumber--;
            }
            stepsLeft--;
            stepMade = 1;
            step();
        }
    }
    stepNumber = 0;
    currSpeed = 0;
}
int32_t STEPPER_readCurrentPos()
{
    return currentPos;
}

void STEPPER_left()
{
    fpDIR( 0 );
    fpST( 1 );
    Delay_us(1);
    fpST( 0 );
}

void STEPPER_right()
{
    fpDIR( 1 );
    fpST( 1 );
    Delay_us(1);
    fpST( 0 );
}

void STEPPER_handler()
{
    counter++;
    Delay_us( 1 );
}

uint32_t STEPPER_readMicros()
{
    return counter * timerSpeed;
}


/** @endcond */
/** @} */
/*------------------------------------------------------------------------------

  __STEPPER_Driver.c

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

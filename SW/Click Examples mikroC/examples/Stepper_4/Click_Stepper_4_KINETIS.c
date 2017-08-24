/*
  Example for Stepper 4 Click

  Date          : August 2017
  Author        : Irena Blagojevic

  Test configuration KINETIS :
    
  MCU              : MK64
  Dev. Board       : HEXIWEAR
  ARM Compiler ver : v.5.1.0

  Description :

  Demonstrates how to use Stepper 4 click to move a stepper motor. First
  the speed is set, given in number of steps per revolution. Afterwards
  the motor is moved using STEPPER_step function, passing it the number
  of desired steps. If that number is negative, the motor moves CCW,
  otherwise it moves CW.

*/

#include "__STEPPER_Driver.h"
#include "MIKROBUS_framework.h"

void InitTimer1()
{
    SIM_SCGC6 |= (1 << PIT);
    NVIC_IntEnable(IVT_INT_PIT1);
    PIT_MCR = 0x00;
    PIT_LDVAL1 = 5999;
    PIT_TCTRL1 |= 2;
    PIT_TCTRL1 |= 1;
}

void systemInit()
{
    STEPPER_GPIOmap( MIKROBUS1_setAN, MIKROBUS1_setCS, MIKROBUS1_setPWM,
                     MIKROBUS1_setRST, MIKROBUS1_setINT );
    MIKROBUS_gpioDirection( MIKROBUS1, MIKROBUS_AN_PIN, GPIO_OUTPUT );
    MIKROBUS_gpioDirection( MIKROBUS1, MIKROBUS_CS_PIN, GPIO_OUTPUT );
    MIKROBUS_gpioDirection( MIKROBUS1, MIKROBUS_PWM_PIN, GPIO_OUTPUT );
    MIKROBUS_gpioDirection( MIKROBUS1, MIKROBUS_RST_PIN, GPIO_OUTPUT );
    MIKROBUS_gpioDirection( MIKROBUS1, MIKROBUS_INT_PIN, GPIO_OUTPUT );

    InitTimer1();
}

void Stepper_4_Init()
{
    STEPPER_init( 200, 100 );

    STEPPER_setAcc( 5 );
    STEPPER_setDec( 5 );
}

void Stepper_4_Task()
{
    STEPPER_setSpeed( 200 );
    STEPPER_step( 400 );
    Delay_ms( 200 );
    STEPPER_setSpeed( 100 );
    STEPPER_step( -600 );
}

void main()
{
    systemInit();
    Stepper_4_Init();

    Stepper_4_Task();
}

void Timer1_interrupt() iv IVT_INT_PIT1
{
    PIT_TFLG1.TIF = 1;
    STEPPER_handler();
}

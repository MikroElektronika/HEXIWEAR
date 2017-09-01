/*
Example for Brushless_2 Click

    Date          : jul 2017.
    Author        : MikroE Team

Test configuration KINETIS :
    
    MCU             : MK64
    Dev. Board      : HEXIWEAR
    SW              : mikroC PRO for ARM v5.1.0

Description :

    This simple example demonstrates driving the motor with Brushless 2 click, 
    direction of motor is controled via MOTOR_DIR_PIN and speed is regulated with PWM.

*/
#include "stdint.h"

sbit MOTOR_DIR_PIN at PTB_PDOR.B10;

uint16_t const maxPwmDuty = 25000;
uint16_t currentDuty = 0;
uint8_t oldstate = 0;

void systemInit()
{
    GPIO_Digital_Output(&PTB_PDOR, _GPIO_PINMASK_10);
    currentDuty = PWM_FTM0_Init(1000,_PWM_INPUT_COMPARE, _PWM_CHANNEL_1, &_GPIO_Module_PWM0_PTA4);
    PWM_FTM0_Set_Duty(currentDuty,  _PWM_NON_INVERTED, _PWM_CHANNEL_1);
    PWM_FTM0_Start( _PWM_CHANNEL_1 );
}

void Brushless_2_Init()
{
    MOTOR_DIR_PIN = 1;  
}

void Brushless_2_Task()
{
    MOTOR_DIR_PIN  = 0;
    //Forward fast
    currentDuty = PWM_FTM0_Init(1000,_PWM_INPUT_COMPARE, _PWM_CHANNEL_1, &_GPIO_Module_PWM0_PTA4);
    PWM_FTM0_Set_Duty(currentDuty,  _PWM_NON_INVERTED, _PWM_CHANNEL_1);
    PWM_FTM0_Start( _PWM_CHANNEL_1 );
    Delay_ms (3000);
    //Forward slow
    currentDuty = PWM_FTM0_Init(1000,_PWM_CENTER_ALIGNED_PWM, _PWM_CHANNEL_1, &_GPIO_Module_PWM0_PTA4);
    PWM_FTM0_Set_Duty(currentDuty/2,  _PWM_NON_INVERTED, _PWM_CHANNEL_1);
    PWM_FTM0_Start( _PWM_CHANNEL_1 );
    Delay_ms (3000);
    //Reverse
    MOTOR_DIR_PIN = 1;
    //Reverse fast
    currentDuty = PWM_FTM0_Init(1000,_PWM_INPUT_COMPARE, _PWM_CHANNEL_1, &_GPIO_Module_PWM0_PTA4);
    PWM_FTM0_Set_Duty(currentDuty,  _PWM_NON_INVERTED, _PWM_CHANNEL_1);
     PWM_FTM0_Start( _PWM_CHANNEL_1 );
    Delay_ms (3000);
    //Reverse slow
    currentDuty = PWM_FTM0_Init(1000,_PWM_CENTER_ALIGNED_PWM, _PWM_CHANNEL_1, &_GPIO_Module_PWM0_PTA4);
    PWM_FTM0_Set_Duty(currentDuty/2,  _PWM_NON_INVERTED, _PWM_CHANNEL_1);
    PWM_FTM0_Start( _PWM_CHANNEL_1 );
    Delay_ms (3000);
}

void main()
{
    systemInit();
    Brushless_2_Init();

    while( 1 )
    {
    	Brushless_2_Task();
    }
}
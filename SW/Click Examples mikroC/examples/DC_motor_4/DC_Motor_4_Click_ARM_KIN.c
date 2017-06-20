/*
 * Example for DC Motor 4 click
 *
 * Date         Apr 2017
 * Author       Djordje Rosic
 *
 * Test configuration KINETIS :
 *  MCU           :        MK64
 *  Dev. Board    :        Hexiwear docking station
 *  SW            :        mikroC PRO for ARM v5.0.0
 *
 * Description :
 *
 * This example shows basic controls of DC motor using DC motor 4 click.
 * It shows forward and reverse movement, and high and low rotation speed.
 *
 * Note: Put the click into slot 3 on the hexiwear docking station.
 *
 ******************************************************************************/

#include <stdint.h>

uint16_t pwmPeriod;
sbit DIR_PIN at  PTB_PDOR.B6;


/*
 * System Initialization
 */
void systemInit()
{
    GPIO_Digital_Output(&PTB_PDOR, _GPIO_PINMASK_6);
}

void main()
{

    systemInit();

    while (1)
    {
        //Forward
        DIR_PIN = 0;
        //Forward fast
        pwmPeriod = PWM_FTM0_Init(1000,_PWM_INPUT_COMPARE, _PWM_CHANNEL_1, &_GPIO_Module_PWM0_PTA4);
        PWM_FTM0_Set_Duty(pwmPeriod,  _PWM_NON_INVERTED, _PWM_CHANNEL_1);
        PWM_FTM0_Start( _PWM_CHANNEL_1 );
        Delay_ms (3000);
        //Forward slow
        pwmPeriod = PWM_FTM0_Init(1000,_PWM_CENTER_ALIGNED_PWM, _PWM_CHANNEL_1, &_GPIO_Module_PWM0_PTA4);
        PWM_FTM0_Set_Duty(pwmPeriod/2,  _PWM_NON_INVERTED, _PWM_CHANNEL_1);
        PWM_FTM0_Start( _PWM_CHANNEL_1 );
        Delay_ms (3000);
        //Reverse
        DIR_PIN = 1;
        //Reverse fast
        pwmPeriod = PWM_FTM0_Init(1000,_PWM_INPUT_COMPARE, _PWM_CHANNEL_1, &_GPIO_Module_PWM0_PTA4);
        PWM_FTM0_Set_Duty(pwmPeriod,  _PWM_NON_INVERTED, _PWM_CHANNEL_1);
        PWM_FTM0_Start( _PWM_CHANNEL_1 );
        Delay_ms (3000);
        //Reverse slow
        pwmPeriod = PWM_FTM0_Init(1000,_PWM_CENTER_ALIGNED_PWM, _PWM_CHANNEL_1, &_GPIO_Module_PWM0_PTA4);
        PWM_FTM0_Set_Duty(pwmPeriod/2,  _PWM_NON_INVERTED, _PWM_CHANNEL_1);
        PWM_FTM0_Start( _PWM_CHANNEL_1 );
        Delay_ms (3000);

    }
}
/************************************************************ END OF FILE *****/
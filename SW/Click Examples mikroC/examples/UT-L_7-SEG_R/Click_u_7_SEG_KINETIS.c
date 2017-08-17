/*
Example for UT_7_SEG Click

    Date          : Jun 2017.
    Author        : Danilo M.

Test configuration KINETIS :
    
    MCU             : MK64
    Dev. Board      : HEXIWEAR
    SW              : mikroC PRO for ARM v5.1.0

Description :

    This example shows countdown from 99 to 00, the LED driver Max6969 is programmed via SPI,
    and the brightness of 7 seg display is regulated by duty cycle of PWM.
    Place click in MBus socket 3.

*/

#include "stdint.h"

sbit   MAX6969_LE_PIN   at  PTC_PDOR.B2;

uint16_t pwmPeriod;
static const uint8_t minus_char = 0x40;

void systemInit()
{
    GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_2);
    pwmPeriod = PWM_FTM0_Init(1000,_PWM_INPUT_COMPARE, _PWM_CHANNEL_1, &_GPIO_Module_PWM0_PTA4);
    PWM_FTM0_Set_Duty(pwmPeriod,  _PWM_NON_INVERTED, _PWM_CHANNEL_1);
    PWM_FTM0_Start( _PWM_CHANNEL_1 );
    SPI0_Init_Advanced( 4000000, _SPI_CFG_MASTER | _SPI_CFG_SELECT_CTAR0 |
                         _SPI_CFG_FRAME_SIZE_8BITS | _SPI_CFG_CLK_IDLE_LOW |
                         _SPI_CFG_CLK_PHASE_CAPT_LEADING | _SPI_CFG_MSB_FIRST,
                         &_GPIO_Module_SPI0_PC5_7_6);


}

void MAX6969_Chip_Select()
{
    MAX6969_LE_PIN = 1;
    asm nop
    asm nop
    asm nop
    MAX6969_LE_PIN = 0;
}

static void U7SEG_Write(uint8_t number)
{
    char numbers[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
    uint8_t tens = number / 10;
    uint8_t ones = number % 10;
    if (number > 99) return;

    SPI_Wr_Ptr(numbers[ones]);
    SPI_Wr_Ptr(numbers[tens]);
}

void main()
{
    uint8_t counter;

    systemInit();
    counter = 100;

    while(counter--)
    {
        U7SEG_Write(counter);
        MAX6969_Chip_Select();
        Delay_ms(500);
    }

    SPI_Wr_Ptr(minus_char);
    SPI_Wr_Ptr(minus_char);
    MAX6969_Chip_Select();
}
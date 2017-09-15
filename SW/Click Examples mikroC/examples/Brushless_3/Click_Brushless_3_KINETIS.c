/*
Example for Brushless_3 Click

    Date          : jul 2017.
    Author        : MikroE Team

Test configuration KINETIS :
    
    MCU              : MK64
    Dev. Board       : HEXIWEAR
    ARM Compiler ver : v5.1.0.0

Description :

    ${EXAMPLE_DESCRIPTION}

*/

#include "__BRUSHLESS_3_Driver.h"

sbit BRUSHLESS_3_DIR_PIN at PTB_PDOR.B11;

sbit BRUSHLESS_3_PWM_PIN at PTA_PDOR.B10;

uint8_t motorParameters [12] = { 0x39, 0x1E, 0x3A, 0x08, 0x50, 0xDA, 0x8B, 0x10, 0x27, 0x37, 0x04, 0x0C} ;
uint16_t Velocity;

char text[10];
void systemInit()
{
    GPIO_Digital_Output(&PTB_PDOR, _GPIO_PINMASK_11);
    GPIO_Digital_Output(&PTA_PDOR, _GPIO_PINMASK_10);
    I2C0_Init_Advanced( 100000, &_GPIO_Module_I2C0_PD8_9 );
    Delay_ms(100);
    BRUSHLESS_3_I2CdriverInit( I2C0_Start, 0, 0, I2C0_Write, I2C0_Read);
    UART0_Init(9600);
    Delay_ms(100);
    UART0_Write_Text("Init");
}

void Brushless_3_Init()
{
    BRUSHLESS_3_DIR_PIN = 0;
    BRUSHLESS_3_PWM_PIN = 1;
    writeParameters(motorParameters);
}

void Brushless_3_Task()
{
    getSpeed(&Velocity);
    IntToStr(Velocity,text);
    UART0_Write_Text( "Motor freq :" );
    UART0_Write_Text(text);
    UART0_Write_Text( "Hz\r\n" );
    delay_ms(1000);
}

void main()
{
    systemInit();
    Brushless_3_Init();

    while( 1 )
    {
            Brushless_3_Task();
    }
}
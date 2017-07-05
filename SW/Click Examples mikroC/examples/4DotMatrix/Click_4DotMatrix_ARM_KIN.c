/*
    Example for 4DotMatrix click

        Date          : 08.06.2017.
        Author        : Aleksandar Zecevic

    Test configuration KINETIS :

        MCU           :        MK64
        Dev. Board    :        HEXIWEAR
        SW            :        mikroC PRO for ARM v.5.1.0

    Description :

        This example demonstrates the usage of the 4DotMatrix driver on an STM
ARM MCU. After the initialization, several messages are displayed periodically.
These include text slide in-out, as well as positive and negative numbers.

    NOTES:
    - Place the 4Dot-Matrix click in MikroBUS socket 1
    on Hexiwear Docking Station.

*/

#include "__C4DOT_Driver.h"

#include <stdint.h>

sfr sbit C4DOT_WR_PIN at PTC_PDOR.B4;
sfr sbit C4DOT_CLR_PIN at PTB_PDOR.B11;
sfr sbit C4DOT_BL_PIN at PTA_PDOR.B10;

// Period of the PWM. Calculated upon PWM initialization.
uint16_t pwmPeriod;

// Text to slide in on the display.
uint8_t text[] = "    MikroElektronika    ";

// Initializes I2C communication, 4Dot-Matrix click, and PWM.
void systemInit()
{
    // Set C4 (WR) as output.
    GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_4);
    C4DOT_WR_PIN = 1;
    // Set B11 (CLR) as output.
    GPIO_Digital_Output(&PTB_PDOR, _GPIO_PINMASK_11);
    C4DOT_CLR_PIN = 1;
    // Set A10 (BL) as output.
    GPIO_Digital_Output(&PTA_PDOR, _GPIO_PINMASK_10);
    C4DOT_BL_PIN = 1;

    Delay_ms(10);
    
    // Initialize I2C0 module for communication with 4DotMatrix.
    I2C0_Init_Advanced(400000, &_GPIO_Module_I2C0_PD8_9);
    
    // Call the 4DotMatrix initialization routine,
    // and pass the I2C address as well as functions for communication.
    C4DOT_initDriver(_C4DOT_I2C_ADDRESS, I2C0_Start, I2C0_Write, I2C0_Read);
}

// Main function.
void main()
{
    int8_t i;
    uint8_t length;

    // Initialize the system.
    systemInit();

    length = strlen(text) - 3;
    while (1)
    {
        // Slide some text in from the right.
        for (i = 0; i < length; i++)
        {
            C4DOT_writeText(text + i);
            Delay_ms(150);
        }
        
        // Clear and delay.
        C4DOT_clearDisplay();
        Delay_ms(500);
        
        // Write some numbers on the display.
        for (i = -20; i <= 20; i++)
        {
            C4DOT_writeIntDec(i);
            Delay_ms(150);
        }

        // Clear and delay.
        C4DOT_clearDisplay();
        Delay_ms(500);
    }
}
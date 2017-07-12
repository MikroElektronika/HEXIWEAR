/*
        Example for IR Sence click

        Date          : May 2017
        Author        : Djordje Rosic

        Test configuration KINETIS :
        
                 MCU           :        MK64
                Dev. Board    :        HEXIWEAR
                 SW            :        mikroC PRO for ARM v5.0.0

    Description :

        This example will show how to use basic IR Sence click functions to
        initialize the device, and get IR readings. Data is displayed via UART.

*/

#include "__IRGRID2_Driver.h"

sbit IRGRID2_PON_PIN at PTC_PDOR.B4;

void systemInit()
{
    Delay_ms( 1000 );

    UART0_Init(9600);
    
    Delay_ms( 200 );
    UART0_Write_Text ("\r\n------------------\r\nInitializing...");

    GPIO_Digital_Output( &PTC_PDOR, _GPIO_PINMASK_4 );
    I2C0_Init_Advanced( 100000, &_GPIO_Module_I2C0_PD8_9 );

    IRGRID2_PON_PIN = 1;
    Delay_ms( 200 );
}

void main()
{
    uint16_t tempValue;
    char uartText [20];
    uint8_t readData [20];

    systemInit();
    IRGRID2_initDriver (0x64, I2C0_Start, I2C0_Write, I2C0_Read );
    Delay_ms( 2000 );

    IRGRID2_setConfig ( _IRGRID2_MODE_SETTING, _IRGRID2_EFC_0600mHZ |
                                               _IRGRID2_MODE_CONT0 );
    UART0_Write_Text ("\r\nInitialized");
    Delay_ms( 2000 );
    UART0_Write_Text ("\r\nStarting measurements:");



    while( 1 )
    {
        Delay_ms (5000);

        IRGRID2_readAll (readData);
        
        
        //Upper area sensor value
        UART0_Write_Text ("\r\n      ");
        tempValue = readData [5] + ( readData [6] << 8 );
        IntToStr (tempValue, uartText);
        UART0_Write_Text (uartText);

        //Left area sensor value
        UART0_Write_Text ("\r\n");
        tempValue = readData [3] + ( readData [4] << 8 );
        IntToStr (tempValue, uartText);
        UART0_Write_Text (uartText);
        //Right area sensor value
        UART0_Write_Text ("     ");
        tempValue = readData [7] + ( readData [8] << 8 );
        IntToStr (tempValue, uartText);
        UART0_Write_Text (uartText);

        //Lower area sensor value
        UART0_Write_Text ("\r\n      ");
        tempValue = readData [1] + ( readData [2] << 8 );
        IntToStr (tempValue, uartText);
        UART0_Write_Text (uartText);
        UART0_Write_Text ("\r\n-------------");
    }
}
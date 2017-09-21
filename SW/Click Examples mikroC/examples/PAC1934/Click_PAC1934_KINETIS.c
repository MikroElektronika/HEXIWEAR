/*
Example for PAC1934 Click

    Date          : Aug 2017.
    Author        : Djordje Rosic

Test configuration KINETIS :
    
    MCU              : MK64
    Dev. Board       : HEXIWEAR
    ARM Compiler ver : v5.1.0.0

Description :

    This example will read Voltage, Current, Power and Energy data from channel
    4 every 10 seconds.

*/

#include "__PAC1934_Driver.h"
#define LOG UART0_Write_Text

void systemInit()
{
    GPIO_Digital_Output( &PTB_PDOR, _GPIO_PINMASK_13 );
    PTB_PDOR.B13 = 0;

    UART0_Init(9600);
    Delay_ms(100);
    LOG("\r\nInitialization...\r\n");
    I2C0_Init_Advanced( 100000, &_GPIO_Module_I2C0_PD8_9 );
    Delay_ms(100);
}

void PAC1934_Init()
{
    PAC1934_I2CdriverInit (I2C0_Start, 0, 0, I2C0_Write, I2C0_Read);
    PAC1934_sendCommand (_PAC1934_REFRESH_CMD);
    delay_ms (200);
}

void PAC1934_Task()
{
    char txt [20];
    float readValue;
    PAC1934_sendCommand (_PAC1934_REFRESH_CMD);
    delay_ms (200);

    readValue = PAC1934_measureVoltage(4);
    FloatToStr(readValue, txt);
    LOG ("VBUS 4:      ");
    LOG (txt);
    LOG (" V\r\n");

    readValue = PAC1934_measureCurrent(4);
    FloatToStr(readValue, txt);
    LOG ("Current 4:   ");
    LOG (txt);
    LOG (" mA\r\n");

    readValue = PAC1934_measurePower(4);
    FloatToStr(readValue, txt);
    LOG ("Power 4:     ");
    LOG (txt);
    LOG (" W\r\n");

    readValue = PAC1934_measureEnergy(4, 1024);
    FloatToStr(readValue, txt);
    LOG ("Energy 4:    ");
    LOG (txt);
    LOG (" J\r\n");

    LOG ("____________________\r\n");
    delay_ms (10000);
}

void main()
{
    systemInit();
    PAC1934_Init();

    while( 1 )
    {
        PAC1934_Task();
    }
}
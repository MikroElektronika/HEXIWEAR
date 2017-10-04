/*
Example for Thermo_6 Click

    Date          : sep 2017.
    Author        : MikroE Team

Test configuration KINETIS :
    
    MCU              : MK64
    Dev. Board       : HEXIWEAR
    ARM Compiler ver : v5.1.0.0

Description :

    This example sets measuring temperature to 12 bit resolution, and read the data from MAX31875 sensor via I2C.

*/

#include "__THERMO6_Driver.h"

uint8_t text[20];
float temperature;

void systemInit()
{
    I2C0_Init_Advanced( 100000, &_GPIO_Module_I2C0_PD8_9 );
    HAL_THERMO6_i2cInit(I2C0_Start, 0, 0, I2C0_Write, I2C0_Read);
    UART0_Init(9600);
}

void Thermo_6_Init()
{
    THERMO6_writeRegCfg(CFG_HIGH_12_BIT,CFG_LOW_12_BIT);    // configure 12bit Temperature resolution
}

void Thermo_6_Task()
{
   temperature = THERMO6_getTemperature();
   FloatToStr(temperature,text);
   UART0_Write_Text("Temperature: ");
   UART0_Write_Text(text);
   Delay_ms(1000);
   UART0_write(13);
   UART0_write(10);
}

void main()
{
    systemInit();
    Thermo_6_Init();

    while( 1 )
    {
            Thermo_6_Task();
    }
}
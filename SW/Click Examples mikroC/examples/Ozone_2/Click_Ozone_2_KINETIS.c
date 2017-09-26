/*
Example for Ozone_2 Click

    Date          : Sep 2017.
    Author        : Djordje Rosic

Test configuration KINETIS :
    
    MCU              : MK64
    Dev. Board       : HEXIWEAR
    ARM Compiler ver : v5.1.0.0

Description :

    This example outputs ADC value from Ozone 2 click.

*/

#include <stdint.h>

void setCS(uint8_t value)
{
    PTC_PDOR.B4  = value;
}
uint8_t getRDY()
{
    return PTC_PDIR.B7 ;
}

void systemInit()
{
    GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_4 );
    GPIO_Digital_Input(&PTC_PDIR, _GPIO_PINMASK_7 );
    SPI0_Init_Advanced( 1000000, _SPI_CFG_CLK_PHASE_CAPT_LEADING | 
    _SPI_CFG_CLK_IDLE_LOW | _SPI_CFG_MASTER | _SPI_CFG_MSB_FIRST |
    _SPI_CFG_FRAME_SIZE_8BITS | _SPI_CFG_SELECT_CTAR0, 
    &_GPIO_Module_SPI0_PC5_7_6);
    HAL_OZONE2_gpioInit(&setCS, &getRDY);

    UART0_Init(9600);
    UART0_write_text("\r\nInitialized");
}

void Ozone_2_Init()
{
    HAL_OZONE2_spiInit(&SPI0_Write, &SPI0_Read);
}

void Ozone_2_Task()
{
    uint32_t readValue;
    char loggerTxt [40];
    readValue = OZONE2_Read();
    LongToStr(readValue, &loggerTxt);
    UART0_write_text("\r\nRead value:");
    UART0_write_text(loggerTXT);

    delay_ms(1000);
}

void main()
{
    systemInit();
    Ozone_2_Init();

    while( 1 )
    {
            Ozone_2_Task();
    }
}
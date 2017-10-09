/*
Example for Fram_2 Click

    Date          : Jul 2017.
    Author        : Djordje Rosic

Test configuration KINETIS :
    
    MCU             : MK64
    Dev. Board      : HEXIWEAR
    SW              : mikroC PRO for ARM v5.1.0

Description :

    This example demonstrates the use of FRAM 2 click. It will first initialize
    peripherals and enable writing to FRAM. It will then write the value 42
    into register 0x10, and then read that value and output it via UART.

    Note: Turn on the UART switches on the board to enable uart output.

*/


#include <stdint.h>

sbit FRAM2_CS at PTC_PDOR.B4;


static void Fram_2_Write (uint8_t address1, uint8_t address2,
                          uint8_t address3, uint8_t writeData);
static uint8_t Fram_2_Read (uint8_t address1,
                            uint8_t address2, uint8_t address3);

void systemInit()
{
    GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_4);
    SPI0_Init_Advanced( 5000000, _SPI_CFG_MASTER | _SPI_CFG_SELECT_CTAR0 |
                         _SPI_CFG_FRAME_SIZE_8BITS | _SPI_CFG_CLK_IDLE_HIGH |
                         _SPI_CFG_CLK_PHASE_CHG_LEADING | _SPI_CFG_MSB_FIRST,
                         &_GPIO_Module_SPI0_PC5_7_6);

    UART0_Init(9600);
    UART_Write_Text ("\r\nInitialized");
}

void Fram_2_Init()
{
    FRAM2_CS = 0;
    SPI_Write (0x06); //Write enable command is required prior to any write.
    FRAM2_CS = 1;
}

void Fram_2_Task()
{
    uint8_t readData;
    char outputText [5];
    memset ( outputText, 0, 5);
    UART_Write_Text ("\r\nWriting value 42 into register 0x10...");
    Fram_2_Write (0x00, 0x00, 0x10, 42 );

    UART_Write_Text ("\r\nReading from register 0x10...");
    readData = Fram_2_Read  (0x00, 0x00, 0x10);
    ShortToStr (readData, outputText);
    UART_Write_Text ("\r\nRead value: ");
    UART_Write_Text (outputText);
}

void main()
{
    systemInit();
    Fram_2_Init();

    Fram_2_Task();
}

static void Fram_2_Write (uint8_t address1, uint8_t address2,
                          uint8_t address3, uint8_t writeData)
{
    FRAM2_CS = 0;
    SPI_Write (0x02);             //Write OPcode
    SPI_Write (address1);
    SPI_Write (address2);
    SPI_Write (address3);
    SPI_Write (writeData);
    //More data can be written after this. Address pointer is auto-incremented.
    FRAM2_CS = 1;
}
static uint8_t Fram_2_Read (uint8_t address1,
                            uint8_t address2, uint8_t address3)
{
    FRAM2_CS = 0;
    SPI_Write (0x03);             //Read OPcode
    SPI_Write (address1);
    SPI_Write (address2);
    SPI_Write (address3);
    return SPI_Read (0x00);
    //More data can be read after this. Address pointer is auto-incremented.
    FRAM2_CS = 1;
}
/*
Example for One_Wire_I2C Click

    Date          : Aug 2017.
    Author        : Djordje Rosic

Test configuration KINETIS :
    
    MCU              : MK64
    Dev. Board       : HEXIWEAR
    ARM Compiler ver : v5.1.0.0

Description :

    This example demonstrates the basic functions of 1-Wire I2C click.
    It will send and receive data from I2C, communicating with Thermo 4 click.
    1-wire I2C will first send thermo click address and register address via
    I2C, and then read 2 bytes of data from that click.

*/

#include "__OWI2C_Driver.h"

void systemInit()
{
    UART0_Init (9600);
}

void One_Wire_I2C_Init()
{
    OWI2C_pinSet (&PTB_PDOR, 0x02);

    UART_Write_Text("Initialized...");
}

void One_Wire_I2C_Task()
{
    char uartText [20];
    char IWireData [20];

    IWireData [0] = 0x00;   //Thermo 4 temperature register address

    OWI2C_skipRom ();
    OWI2C_writeI2C ( OWI2C_WRITE_NORMAL_NOSTOP, 0x48, 1, &IWireData);   //0x48 is unshifted I2C address of Thermo 4 click
    OWI2C_skipRom ();
    OWI2C_readI2C ( 0x48, 2, &IWireData);

    UART_Write (13);
    UART_Write (10);
    UART_Write_Text("Current temperature is: ");
    ByteToStr(IWireData[0], uartText);
    UART_Write_Text(uartText);

    Delay_ms (2000);
}

void main()
{
    systemInit();
    One_Wire_I2C_Init();

    while( 1 )
    {
        One_Wire_I2C_Task();
    }
}
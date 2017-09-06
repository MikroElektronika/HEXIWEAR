/*
        Example for Angle3 click

        Date          : 18.5.2017.
        Author        : Aleksandar Zecevic

        Test configuration KINETIS :
        
                MCU           :        MK64
                Dev. Board    :        HEXIWEAR
                SW            :        mikroC PRO for ARM v.5.0.0

    Description :

        This example demonstrates the use of Angle3 driver on a KINETIS ARM MCU.
After the initialization, angle data from the click is being read each second,
checked for errors, converted to degrees, and then being sent via UART to USB.
        Therefore, the device receiving via USB will get a new angle measurement
every second, or an error message ("error") indicating there is an error with
angle data.
        UART data is being sent at the frequency of 56000 bits per second.

    NOTES:
    - Place Angle3 click in MikroBUS socket 1 on HEXIWEAR docking station.
    - Place USB UART click im MikroBUS socket 2 on HEXIWEAR docking station.

*/

#include "__ANGLE3_Driver.h"

#include <stdint.h>

sfr sbit ANGLE3_CS_PIN at PTC_PDOR.B4;
sfr sbit ANGLE3_ERR_PIN at PTB_PDOR.B13;

// Initializes SPI communication, Angle3 click, and UART.
void systemInit()
{
    GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_4); // Set C4 (CS) as output.
    PTC_PDOR.B4 = 1;
    GPIO_Digital_Input(&PTB_PDIR, _GPIO_PINMASK_13); // Set B13 (ERR) as input.

    // Initialize SPI0 module for communication with Angle3.
    SPI0_Init_Advanced(4000000, _SPI_CFG_FRAME_SIZE_8BITS | _SPI_CFG_MASTER |
        _SPI_CFG_CLK_IDLE_LOW | _SPI_CFG_CLK_PHASE_CHG_LEADING |
        _SPI_CFG_MSB_FIRST, &_GPIO_Module_SPI0_PC5_7_6);

    // Call the Angle3 initialization routine,
    // and pass pointers to functions for reading and writing on SPI0.
    ANGLE3_initDriver(SPI0_Write, SPI0_Read);

    // Initialize UART module at 56000 bps.
    UART3_Init_Advanced(56000, _UART_8_BIT_DATA, _UART_NOPARITY,
        _UART_ONE_STOPBIT, &_GPIO_Module_UART3_PC16_17);
    Delay_ms(100);     // Wait for UART module to stabilize.
}

// Main function.
void main()
{
    uint16_t angleData;        // Angle data read from Angle3.
    uint16_t angleDataDegrees; // Angle data converted to degrees.
    uint8_t buffer[20];        // Buffer for characters to send via UART.

    // Initialize the system.
    systemInit();
    
    // First write to UART.
    UART3_Write_Text("Start");
    UART3_Write(13);
    UART3_Write(10);

    // Main loop.
    while( 1 )
    {
        // Some delay.
        Delay_ms(1000);
    
        // Read angle data and convert.
        angleData = ANGLE3_readAngleData();
        
        // Check the error bit.
        if ((angleData & _ANGLE3_ERR_BITMASK) == 0)
        {
            // Send error message via UART.
            UART3_Write_Text("   error");
            
            // Continue with next loop iteration.
            continue;
        }

        // Convert angle data to degrees.
        angleData &= 0x0FFF; // Actual data is in the lower 12 bits.
        angleDataDegrees = ANGLE3_calculateDegrees(angleData);
        
        // Send angle data via UART.
        IntToStr(angleDataDegrees, buffer);
        UART3_Write_Text(buffer);
    }
}
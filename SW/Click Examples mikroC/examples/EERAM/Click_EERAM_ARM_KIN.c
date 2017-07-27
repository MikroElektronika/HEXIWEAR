/*
        Example for EERAM click

        Date          : Jun 2017
        Author        : Djordje Rosic

        Test configuration KINETIS :
        
                 MCU           :        MK64
                Dev. Board    :        HEXIWEAR
                 SW            :        mikroC PRO for ARM v5.1.0

    Description :

        This example shows the use of EERAM click library. It demonstrates
        reading and writing from the SRAM array, storing the data from SRAM to
        EERAM, and recalling that data back to SRAM, as well as checking if
        the data in SRAM and EERAM matches.
        
        Put the EERAM click into mikroBUS slot 1.
*/

#include <stdint.h>
#include "__EERAM_Driver.h"

static void outputHex (uint8_t * pData, uint8_t count);

void systemInit()
{
    UART0_Init(9600);
    I2C0_Init_Advanced( 100000, &_GPIO_Module_I2C0_PD8_9 );
    Delay_ms(100);
    LOG ("\r\n--------------------------------");
    LOG ("\r\nInitialization...\r\n");
    Delay_ms(100);
    

}

void main()
{
    char writeData [20];
    char readData [20];
    systemInit();
    EERAM_initDriver (I2C0_Start, I2C0_Write, I2C0_Read );



    //Read and write test
    LOG ("\r\n\r\nReading 11 bytes of SRAM memory, from addresses 0x0100:");
    EERAM_read (0x01, 0x00, readData, 11);
    outputHex (readData, 11);
    Delay_ms(100);
    LOG ("\r\n\r\nWriting values 0x42 to SRAM memory");
    LOG (", at addresses 0x0100 - 0x010A...");
    memset (writeData, 0x42, 11);
    EERAM_write (0x01, 0x00, writeData, 11);
    Delay_ms(100);
    LOG ("\r\n\r\nReading 11 bytes of SRAM memory, from addresses 0x0100:");
    EERAM_read (0x01, 0x00, readData, 11);
    outputHex (readData, 11);
    Delay_ms(100);
    //Storing test
    LOG ("\r\n\r\nStoring SRAM data to EERAM memory...");
    EERAM_command (_EERAM_CMD_STORE);
    Delay_ms(100);
    LOG ("\r\n\r\nChecking if data in SRAM array matches EERAM data");
    readData [0] = EERAM_statusRead ();
    if (readData [0] & 0x80)
        LOG ("\r\nSram has been modified since the last Store/Recall operation");
    else LOG ("\r\nEERAM data matches SRAM data");
    Delay_ms(100);
    LOG ("\r\n\r\nWriting values 0x24 to SRAM memory");
    LOG (", at addresses 0x0106 - 0x010A...");
    memset (writeData, 0x24, 5);
    EERAM_write (0x01, 0x06, writeData, 5);
    Delay_ms(100);
    LOG ("\r\n\r\nReading 11 bytes of SRAM memory, from addresses 0x0100:");
    EERAM_read (0x01, 0x00, readData, 11);
    outputHex (readData, 11);
    Delay_ms(100);
    LOG ("\r\n\r\nChecking if data in SRAM array matches EERAM data");
    readData [0] = EERAM_statusRead ();
    if (readData [0] & 0x80)
        LOG ("\r\nSram has been modified since the last Store/Recall operation");
    else LOG ("\r\nEERAM data matches SRAM data");
    Delay_ms(100);
    //Recalling test
    LOG ("\r\n\r\nRecalling EERAM data to SRAM array...");
    EERAM_command (_EERAM_CMD_RECALL);
    Delay_ms(100);
    LOG ("\r\n\r\nReading 11 bytes of SRAM memory, from addresses 0x0100:");
    EERAM_read (0x01, 0x00, readData, 11);
    outputHex (readData, 11);
    
    

}

//Outputs the string as an array of hex values
static void outputHex (uint8_t * pData, uint8_t count)
{
    char writeData [3];
    uint8_t i;
    LOG ("\r\n");
    for (i = 0; i < count; i++)
    {
        ByteToHex (pData [i], writeData);
        LOG (writeData);
        LOG (" ");
    }
}
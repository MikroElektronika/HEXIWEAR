/*
Example for Secure_2 Click

    Date          : Jul 2017.
    Author        : Djordje Rosic

Test configuration KINETIS :

    MCU              : MK64
    Dev. Board       : HEXIWEAR
    ARM Compiler ver : v5.1.0.0

Description :

    Following example demonstrates sending commands to Secure 2 click using
    ATAES132 Library.
    It shows correct initialization of the device, as well as three sample
    functions that can be used to test the device without locking it.

    All advanced operation requires the configuration zone of the device to be
    locked. This is irreversible, so it is not included in the basic example.
    Function "additionalTests", that is commented out, shows how to lock the
    config zone, and contains additional test function that outputs a random
    number.

    All output is via USB UART, turn on the required switches on the board.
*/

#include <stdint.h>
#include "aes132_comm_marshaling.h"
#include "__SECURE2_Driver.h"
#define LOG(x) UART0_Write_Text(x)

static void outputHex (uint8_t * pOutput, uint8_t length);
static void additionalTests ();
uint8_t txBuffer[84];
uint8_t rxBuffer[36];
uint8_t inputBuffer [16];

/*
   System Initialization
   Initializes UART output and I2C connection.
 */
void systemInit()
{
    UART0_Init(9600);
    I2C0_Init_Advanced( 100000, &_GPIO_Module_I2C0_PD8_9 );
    LOG ("\r\nInitialized");
    delay_ms (100);

}
/*
   Secure 2 Initialization
   Initializes driver and sets buffer to 0.
 */
void Secure_2_Init()
{
    SECURE2_I2CdriverInit( I2C0_Start, 0, 0, I2C0_Write, I2C0_Read);

    memset (txBuffer, 0, 84);
    memset (rxBuffer, 0, 36);

    //This function resets the address pointer, in case there was an error
    aes132c_reset_io_address ();
}

void main()
{
    systemInit();
    Secure_2_Init();

    LOG( "\r\nStarting device testing...\r\n" );

    //First test - Reading serial number
    if (aes132m_execute(AES132_BLOCK_READ, 0x00, 0xF000, 0x0008,
                        0, 0, 0, 0, 0, 0, 0, 0, txBuffer, rxBuffer)
                        == AES132_FUNCTION_RETCODE_SUCCESS)
    {
        LOG( "\r\n Serial number: " );
        outputHex (&rxBuffer[2], 8);
    }
    else  LOG( "\r\n Reading serial number failed..." );

    memset (txBuffer, 0, 84);
    memset (rxBuffer, 0, 36);


    //Second test - Reading device info
    delay_ms (1500);
    if (aes132m_execute(AES132_INFO, 0x00, 0x0006, 0x0000,
                        0, 0, 0, 0, 0, 0, 0, 0, txBuffer, rxBuffer)
                        == AES132_FUNCTION_RETCODE_SUCCESS)
    {
        LOG( "\r\n\r\n Device num register: " );
        outputHex (&rxBuffer[2], 2);
    }
    else  LOG( "\r\n\r\n Reading device information..." );

    memset (txBuffer, 0, 84);
    memset (rxBuffer, 0, 36);

    //Third test - Crunch function for a given input
    delay_ms (1500);
    memset (inputBuffer, 42, 16);
    if (aes132m_execute(AES132_CRUNCH, 0x00, 0x0001, 0x0000,
                        16, inputBuffer, 0, 0, 0, 0, 0, 0, txBuffer, rxBuffer)
                        == AES132_FUNCTION_RETCODE_SUCCESS)
    {
        LOG( "\r\n\r\n Crunch operation output: " );
        outputHex (&rxBuffer[2], 16);

        LOG( "\r\n Expected Crunch output: 7A 78 A9 7D 27 47 90 7D ");
        LOG("7A A6 20 5B 14 AB 58 73");
    }
    else  LOG( "\r\n\r\n Crunch operation failed.." );

    memset (txBuffer, 0, 84);
    memset (rxBuffer, 0, 36);


/*
  IMPORTANT: Uncommenting these lines permanently locks the config zone of the
  device.

  This is irreversible, so make sure configuration is set according to your
  needs. All the following tests won't work unless config zone is locked.

  additionalTests ();
 */

    LOG( "\r\n\r\n--------------------------------------------" );
    LOG( "\r\nEND" );
}


/*
  IMPORTANT: Following functions permanently lock the config zone of the
  device. Do not use them if you are not sure what you're doing.


    This function WILL LOCK THE CONFIG ZONE. After that it will generate a
    random number, and output it.
*/

static void additionalTests ()
{
    //Configuration zone locking
    if (aes132m_execute(AES132_LOCK, 0x02, 0x0000, 0x0000,
                        0, 0, 0, 0, 0, 0, 0, 0, txBuffer, rxBuffer)
                        == AES132_FUNCTION_RETCODE_SUCCESS)
    {
        LOG( "\r\n\r\n Configuration zone locked! " );
    }
    else
    {
        LOG( "\r\n\r\n Configuration zone locking failed" );
        LOG( " or it is already locked." );
    }
    memset (txBuffer, 0, 84);
    memset (rxBuffer, 0, 36);
/*
    Fourth test - Random number generator
    Will only return 0xA5 unless config zone is locked first.
*/
    if (aes132m_execute(AES132_RANDOM, 0x00, 0x0000, 0x0000,
                        0, 0, 0, 0, 0, 0, 0, 0, txBuffer, rxBuffer)
                        == AES132_FUNCTION_RETCODE_SUCCESS)
    {
        LOG( "\r\n\r\n Generated random number: " );
        outputHex (&rxBuffer[2], 16);
    }
    else  LOG( "\r\n\r\n Random number generation failed..." );

    memset (txBuffer, 0, 84);
    memset (rxBuffer, 0, 36);
}




//Help function for outputing data in hex format
static void outputHex (uint8_t * pOutput, uint8_t length)
{
    uint8_t i;
    char text [10];
    for( i = 0; i < length; i++ )
    {
        ByteToHex( pOutput[ i ], text );
        LOG( Ltrim(text) );
        LOG( " " );
    }
}
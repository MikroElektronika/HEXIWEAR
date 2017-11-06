/*
Example for Qi_Receiver Click

    Date          : Aug 2017.
    Author        : Djordje Rosic

Test configuration KINETIS :
    
    MCU              : MK64
    Dev. Board       : HEXIWEAR
    ARM Compiler ver : v5.1.0.0

Description :

    This example demonstrates reading of Qi receiver registers. It will output
    VRECT value, and IOUT value. VRECT can be used to indicate how well the
    receiver is placed, where higher values mean that the position is better.
    IOUT is the output current of the system.

    This example will only work if receiver is powered by the transmitter.
    Receiver is powered if STAT led is turned on.

*/
#include <stdint.h>
#include "__QIRCV_Driver.h"
#define LOG UART0_Write_Text
void systemInit()
{
   UART0_Init( 9600 );
   Delay_ms (100);
   I2C0_Init_Advanced( 100000, &_GPIO_Module_I2C0_PD8_9 );
   Delay_ms (100);
   LOG( "\r\n Initializing...  \r\n" );
}

void Qi_Receiver_Init()
{
    QIRCV_I2CdriverInit (I2C0_Start, 0, 0, I2C0_Write, I2C0_Read);
    Delay_ms (100);
    LOG( "\r\n Initialized  \r\n" );
}

void Qi_Receiver_Task()
{
    float readValue;
    uint8_t txt [15];

    readValue = QIRCV_readV ();
    FloatToStr (readValue, txt);
    LOG ("\r\n Current Voltage: ");
    LOG (txt);
    LOG (" V. ");

    readValue = QIRCV_readI ();
    FloatToStr (readValue, txt);
    LOG ("\r\n Current Current: ");
    LOG (txt);
    LOG (" mA. ");

    Delay_ms (2000);
}

void main()
{
    systemInit();
    Qi_Receiver_Init();

    while( 1 )
    {
            Qi_Receiver_Task();
    }
}
/*
        Example for Thermo 4 click

        Date          : May 2017
        Author        : Djordje Rosic

        Test configuration KINETIS :

                 MCU           :        MK64
                Dev. Board    :        HEXIWEAR
                SW            :        mikroC PRO for ARM v5.0.0

    Description :

    This example demonstrates the use of Thermo 4 click library.
*/

#include "thermo_4_Click.h"

uint16_t temp_value;
char uart_text [15];
uint8_t i;
float _fh_value;

static void system_init( void )
{

   UART0_Init( 115200 );
   Delay_ms (100);
   I2C0_Init_Advanced(100000, &_GPIO_Module_I2C0_PD8_9);
   Delay_ms (100);
   UART0_Write_Text( "\r\n INITIALIZED  \r\n" );
   
}



void main()
{

    system_init();
    thermo_init(0x55);
    Delay_ms (100);
    i=5;


    /*sets the temperature limit to specified float value*/
    thermo_write_temperature (65.5, THERMO_TOS);
    /*reads stored temperature limit*/
    thermo_read_temperature_text (uart_text, THERMO_TOS);
    Delay_ms (100);
        
    UART0_Write_Text("\r\n Current temperature limit for output signal: ");
    UART0_Write_Text(uart_text);
    Delay_ms( 1000 );

        /*reads current temperature in fahrenheit*/
    _fh_value = thermo_read_temperature_fh (THERMO_TEMP);
    FloatToStr (_fh_value , uart_text);
    uart_text [5] = 0;
    Delay_ms (100);
    UART0_Write_Text("\r\n \r\n Current temperature in Fahrenheit: ");
    UART0_Write_Text(uart_text);
    Delay_ms( 1000 );

        

    /*Measures temperature 5 times in normal operating mode*/
    while( i-- )
    {
            UART0_Write_Text( "\r\n Current TEMP value: " );
            thermo_read_temperature_text (uart_text, THERMO_TEMP);
            UART0_Write_Text(uart_text);
            Delay_ms( 2000 );
    }

    /*Reads temperature 5 times in
    shutdown mode (measured temperature won't change)*/
    thermo_config (THERMO_SHUTDOWN);
    UART0_Write_Text( "\r\n SHUTDOWN MODE" );
    Delay_ms( 350 );       /*measure time is up to 300 ms*/
    i=5;
    while( i-- )
    {
            UART0_Write_Text( "\r\n Current TEMP value: " );
            thermo_read_temperature_text (uart_text, THERMO_TEMP);
            UART0_Write_Text(uart_text);
            Delay_ms( 2000 );
    }


    /*System leaves shutdown mode, and reads five more measurements*/
    thermo_config (THERMO_POWERUP);
    UART0_Write_Text( "\r\n POWERING UP..." );
    Delay_ms( 350 );
    i=5;
    while( i-- )
    {
            UART0_Write_Text( "\r\n Current TEMP value: " );
            thermo_read_temperature_text (uart_text, THERMO_TEMP);
            UART0_Write_Text(uart_text);
            Delay_ms( 2000 );
    }

}

/************************************************************ END OF FILE *****/
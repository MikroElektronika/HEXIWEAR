/*
 * Example for GNSS 4 click
 *
 * Date         Apr 2017
 * Author       Djordje Rosic
 *
 * Test configuration KINETIS :
 *  MCU           :        MK64
 *  Dev. Board    :        Hexiwear docking station
 *  SW            :        mikroC PRO for ARM v5.0.0
 *
 * Description :
 *
 *   This example initializes GNSS 4 click and GPS parser library, and displays
 *   gps data via UART click every 5 seconds.
 *   GNSS 4 click is in microbus slot 1, and USB UART click is in slot 2.
 ******************************************************************************/
#include "__GPS_parser.h"
#define MSG( TXT ) UART3_Write_Text( TXT )
sbit GPS_RST_PIN at PTB_PDOR.B11;

static void checkGps()
{

    char text[80];
    T_GPS_location *position;

    position = GPS_getLatitude();

    MSG(" \r\n\r\nLatitude\r\n\tDegrees: \t");
    IntToStr (position->degrees, text);
    MSG( text );
    MSG(" \r\n\tMinutes: \t");
    FloatToStr ( position->minutes, text);
    MSG( text );
    MSG(" \r\n\tDirection: \t");
    IntToStr (position->azmuth, text);
    MSG( text );

    position = GPS_getLongitude();

    MSG(" \r\n\r\nLongitude\r\n\tDegrees: \t");
    IntToStr (position->degrees, text);
    MSG( text );
    MSG(" \r\n\tMinutes: \t");
    FloatToStr ( position->minutes, text);
    MSG( text );
    MSG(" \r\n\tDirection: \t");
    IntToStr (position->azmuth, text);
    MSG( text );

    MSG(" \r\n\r\nNumber of sats used for solution: ");
    IntToStr (GPS_getGgaSatCount(), text);
    MSG( text );

    MSG(" \r\n\r\nAltitude: \t\t");
    FloatToStr (GPS_getGgaAltitude(), text);
    MSG( text );
    MSG(" \r\n\r\n------------------\r\n");

}


static void gpsInitialize()
{
    GPS_RST_PIN = 0;
    Delay_ms( 300 );
    GPS_RST_PIN = 1;

}
/*
 * System Initialization
 */
static void systemInit()
{
    GPIO_Digital_Output( &PTB_PDOR, _GPIO_PINMASK_11 );

    /*sends data via uart click */
    UART3_Init_Advanced( 115200, _UART_8_BIT_DATA, _UART_NOPARITY,
                         _UART_ONE_STOPBIT, &_GPIO_Module_UART3_PC16_17 );


    /*receives data from device */
    UART2_Init_Advanced(  9600, _UART_8_BIT_DATA, _UART_NOPARITY,
                          _UART_ONE_STOPBIT,  &_GPIO_Module_UART2_PD3_2 );

    UART2_C2 |= 1 << 5;
    Delay_ms( 100 );

    gpsInitialize();

    NVIC_IntEnable(IVT_INT_UART2_RX_TX );
    EnableInterrupts();


    MSG ("Initialized");
}


void main()
{
    int i;
    systemInit();

/*
 * GNSS initialization and position tracking may last up to a couple of minutes.
 * First few values shown might be incorrect.
 */

    i = 0;
    while(1)
    {
        GPS_parse();
        if (i%5000 == 0)
        checkGps();
        Delay_ms (1);
        i++;
    }
}

void UART2_RX_ISR() iv IVT_INT_UART2_RX_TX ics ICS_AUTO
{
    if( UART2_S1 & ( 1 << 5 ) )
    {
        char tmp = UART2_D;
        GPS_put( tmp );

        //Uncomment to see uart input in real time
        //UART3_Write( tmp );
    }
}

/************************************************************ END OF FILE *****/
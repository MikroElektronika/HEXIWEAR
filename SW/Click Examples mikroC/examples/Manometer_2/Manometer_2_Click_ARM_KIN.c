/*
 * Example for Manometer 2 click
 *
 * Date         May 2017
 * Author       Djordje Rosic
 *
 * Test configuration KINETIS :
 *  MCU           :        MK64
 *  Dev. Board    :        HEXIWEAR
 *  SW            :        mikroC PRO for ARM v5.0.0
 *
 * Description :
 *
 *     Device will output current temperature and relative pressure via usb
 *     uart every 2 seconds.
 *
 ******************************************************************************/

#include "__MMETER2_Driver.h"
#define I2CAddress 0x76

/*
 * Sensor type
 */
#define pp001GS 0
#define pp002GS 1
#define pp002DS 2
#define pp005DS 3
#define pp0015AS 4
#define pp0015GS 4
#define pp0015DS 5
#define pp0030AS 6
#define pp0030GS 6
#define pp0030DS 7


/*
 * System Initialization
 */
void systemInit()
{
    UART0_Init(9600);


    Delay_ms(100);
    UART0_Write_Text("\n\rInitialization...\n\r");
    I2C0_Init_Advanced( 100000, &_GPIO_Module_I2C0_PD8_9 );
    Delay_ms( 1000 );

    MMETER2_initDriver(pp001GS ,0x76, I2C0_Start, I2C0_Write, I2C0_Read );

}

void main()
{
    char uartText [60];
    float measureResult;
    systemInit();
    UART0_Write_Text("Initialized\n\r");

    while( 1 )
    {
        measureResult = MMETER2_getTemperature(CONVERT_4096);
        sprintf(uartText, "Temperature is: %3.3f Celsius\r\n", measureResult);
        UART0_Write_Text(uartText);

        measureResult = MMETER2_getPressure(CONVERT_4096);
        sprintf(uartText, "Pressure is:    %3.3f PSI\r\n\r\n", measureResult);
        UART0_Write_Text(uartText);

        Delay_ms( 2000 );
    }
    
}
/************************************************************ END OF FILE *****/
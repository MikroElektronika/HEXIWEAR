/*
        Example for LSM303AGR click

        Date          : ${DATE}
        Author        : ${SW_ENG}

        Test configuration KINETIS :
        
                 MCU           :        MK64
                 Dev. Board    :        HEXIWEAR
                 SW            :        mikroC PRO for ARM v.5.0.0

    Description :

        ${EXAMPLE_DESCRIPTION}

*/

#include "__LSM303AGR_Driver.h"

#define LOG(x) UART3_Write_Text(x)

void systemInit()
{
    I2C0_Init_Advanced( 100000, &_GPIO_Module_I2C0_PD8_9 );
    Delay_ms( 200 );

    UART3_Init_Advanced( 115200, _UART_8_BIT_DATA, _UART_NOPARITY,
                       _UART_ONE_STOPBIT, &_GPIO_Module_UART3_PC16_17 );

    Delay_ms( 1000 );
    LOG( "UART initialized\n\r" );
}

void main()
{
    uint16_t output[ 3 ];
    unsigned char txt[ 256 ];
    systemInit();
    LOG( "Driver initialized\n\r" );
    LSM303AGR_initDriver( 0x19, 0x1E, I2C0_Start,
                          I2C0_Write, I2C0_Read );
    LSM303AGR_disableAcc();
    LOG( "Accelerometer disabled\n\r" );
    LSM303AGR_setPowerMode( LSM303AGR_MAG, LSM303AGR_LOW_POWER );
    LOG( "Magnetometer power mode set to low-power\n\r" );
    LSM303AGR_setMeasureMode( LSM303AGR_CONT );
    LOG( "Magnetometer measuring mode set to continuous\n\r" );
    LSM303AGR_SetDataRate( LSM303AGR_MAG, 0x00 );
    LOG( "Magnetometer data rate set to 10Hz\n\r" );

    LSM303AGR_readOutput( LSM303AGR_MAG, output );
    LOG( "Reading magnetometer output\n\r" );
    Delay_ms( 200 );
    WordToHex( output[0], txt );
    LOG( "X: " );
    LOG( txt );
    WordToHex( output[1], txt );
    LOG( "\n\rY: " );
    LOG( txt );
    WordToHex( output[2], txt );
    LOG( "\n\rZ: " );
    LOG( txt );
    LOG( "\n\r" );

    while( 1 );
}
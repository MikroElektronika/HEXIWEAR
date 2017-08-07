/*
Example for MAC_Address Click

    Date          : Aug 2017.
    Author        : MikroE Team

Test configuration KINETIS :
    
    MCU              : MK64
    Dev. Board       : HEXIWEAR
    ARM Compiler ver : vCANT_FIND_VERSION

Description :

    Simple demonstration how to use library.

*/

#include "__MACADDRESS_Driver.h"

#define LOG(x) UART3_Write_Text(x)

uint8_t loop = 0;
uint8_t multi[ 12 ] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };

void systemInit()
{
    I2C0_Init_Advanced( 100000, &_GPIO_Module_I2C0_PD8_9 );
    UART3_Init_Advanced( 115200, _UART_8_BIT_DATA, _UART_NOPARITY,
                         _UART_ONE_STOPBIT, &_GPIO_Module_UART3_PC16_17 );
    Delay_100ms();

    LOG( "\r\n System Initialized" );
}

void MAC_Address_Init()
{
    HAL_MACADDRESS_i2cInit( &I2C0_Start, 0, 0, &I2C0_Write, &I2C0_Read );
    MACADDRESS_init( 0x50 );

    LOG( "\r\n MAC Address Click Initialized" );
    LOG( "\r\n ------------------------------------------------------------ " );
    LOG( "\r\n ------------------------------------------------------------ " );
}

void MAC_Address_Task()
{
    int     cnt;
    uint8_t read;
    uint8_t mread[12];
    uint8_t var[10];
    char    txt[50];

    LOG( "\r\n ------------------------------------------------------------ " );
    LOG( "\r\n\r\n Test Loop" );
    LOG( "\r\n ------------------------------------------------------------ " );

    LOG( "\r\n MAC Read Test" );
    LOG( "\r\n ------------------------------------------------------------ " );
    if( !MACADDRESS_readMAC( var ) )
    {
        LOG( "\r\n MAC Address : " );
        for( cnt = 0; cnt < 6; cnt++ )
        {
            ByteToHex( var[cnt], txt );
            Ltrim( txt );
            LOG( txt );
            if( cnt != 5 )
                LOG( ":" );
        }
    }
    else
    {
        LOG( "\r\n MAC Read Error" );
    }

    LOG( "\r\n -------------------------------------------------------- \r\n" );
    LOG( "\r\n Write Single Byte Test" );
    LOG( "\r\n ------------------------------------------------------------ " );
    if( !MACADDRESS_writeByte( loop, loop + 1 ) )
    {
        LOG( "\r\n Byte value [ " );
        ByteToHex( loop + 1, txt );
        Ltrim( txt );
        LOG( txt );
        LOG( " ] succeessfully written to [ " );
        ByteToHex( loop, txt );
        Ltrim( txt );
        LOG( txt );
        LOG( " ] address" );
    }
    else
    {
        LOG( "\r\n Write Byte Error" );
    }

    LOG( "\r\n -------------------------------------------------------- \r\n" );
    LOG( "\r\n Read Single Byte Test" );
    LOG( "\r\n ------------------------------------------------------------ " );
    if( !MACADDRESS_readByte( loop, &read ) )
    {
        LOG( "\r\n Byte value [ " );
        ByteToHex( read, txt );
        Ltrim( txt );
        LOG( txt );
        LOG( " ] succeessfully read from [ " );
        ByteToHex( loop, txt );
        Ltrim( txt );
        LOG( txt );
        LOG( " ] address" );
    }
    else
    {
        LOG( "\r\n Read Byte Error" );
    }
    LOG( "\r\n -------------------------------------------------------- \r\n" );
    LOG( "\r\n Write Multiple Bytes Test" );
    LOG( "\r\n ------------------------------------------------------------ " );
    if( !MACADDRESS_writeMulti( loop, multi, 12 ) )
    {
        LOG( "\r\n Array values " );
        for( cnt = 0; cnt < 12; cnt++ )
        {
            ByteToHex( multi[cnt], txt );
            Ltrim( txt );
            LOG( "[ " );
            LOG( txt );
            LOG( " ]" );
        }
        LOG( " succeessfully written to [ " );
        ByteToHex( loop, txt );
        Ltrim( txt );
        LOG( txt );
        LOG( " ] address and forward" );
    }
    else
    {
        LOG( "\r\n Write Byte Error" );
    }
    LOG( "\r\n -------------------------------------------------------- \r\n" );
    LOG( "\r\n Read Multiple Bytes Test" );
    LOG( "\r\n ------------------------------------------------------------ " );
    if( !MACADDRESS_readMulti( loop, mread, 12 ) )
    {
        LOG( "\r\n Array values " );
        for( cnt = 0; cnt < 12; cnt++ )
        {
            ByteToHex( mread[cnt], txt );
            Ltrim( txt );
            LOG( "[ " );
            LOG( txt );
            LOG( " ]" );
        }
        LOG( " succeessfully read from [ " );
        ByteToHex( loop, txt );
        Ltrim( txt );
        LOG( txt );
        LOG( " ] address and forward" );
    }
    else
    {
        LOG( "\r\n Read Byte Error" );
    }

    loop++;
    Delay_ms( 5000 );
}

void main()
{
    systemInit();
    MAC_Address_Init();

    while( 1 )
    {
        MAC_Address_Task();
    }
}
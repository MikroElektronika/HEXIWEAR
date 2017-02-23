/*
 * Example for NFC Tag 2 click
 *
 * Date        Dec 2016
 * Author      MilosV
 * Copyright   GNU Public License
 *
 * Test configuration HEXI :
 * MCU           :        MK64
 * Dev. Board    :        Hexiwear
 * Ext. Modules  :        NFC Tag 2 click ( mikroBUS 1 )
 * SW            :        mikroC PRO for ARM v4.9.0
 *
 * Include example.pld file.
 *
 ******************************************************************************/

#include "nfc_tag2.h"

nfctag2_click NT2_click;

void system_init( void );
void print_mem( uint8_t *ptr, uint16_t len );
void test_read_common( void );
void test_write_common( void );
void test_read_config( void );
void test_write_config( void );
void test_read_session( void );
void test_write_session( void );

/*
 * MCU Peripherals Initialization
 *
 *  - UART3 used for data dump
 *  - I2C1 used for NTC Tag 2
 *
 */
void system_init( void )
{
    UART3_Init_Advanced( 115200, _UART_8_BIT_DATA, _UART_NOPARITY,
                         _UART_ONE_STOPBIT, &_GPIO_Module_UART3_PC16_17 );
    Delay_ms( 200 );

    I2C0_Init_Advanced( 400000, &_GPIO_Module_I2C0_PD8_9 );
    Delay_ms( 200 );
    LOG( "\r\n< < System Initialized > >\r\n" );
}

void print_mem( uint8_t *ptr, uint16_t len )
{
int         reg_cnt;
char        tmp[ 15 ];
    LOG( "\t" );
    for( reg_cnt = 0; reg_cnt < len; reg_cnt++ )
    {
        ByteToHex( *( ptr + reg_cnt ), tmp );
        LOG( Ltrim( tmp ) );
        LOG( " " );
        if( reg_cnt % 16 ) LOG( "\r\n" );
    }
    LOG( "\r\n" );
}

/*
 * Example how to use :
 *        - nfctag2_get
 *        - nfctag2_set
 *
 * Dumps the content of the Serial Number registers and SRAM memory
 *
 */
void test_read_common( void )
{
    LOG( "Read Serial number :" );
    if( !nfctag2_get( NT2_SET_SERIAL_NO, NT2_click.serial_num ) )
            print_mem( NT2_click.serial_num, sizeof( NT2_click.serial_num ) );
    LOG( "Read SRAM :" );
    if( !nfctag2_get( NT2_SET_SRAM_MEMORY, NT2_click.sram_memory ) )
            print_mem( NT2_click.sram_memory, sizeof( NT2_click.sram_memory ) );
    LOG( "Reading SRAM Finished\r\n" );
}

void test_write_common( void )
{
uint8_t default_CC[ 4 ] = { 0xE1, 0xC0, 0x01, 0x00 };
    memcpy( NT2_click.cap_containter, default_CC,
            sizeof( NT2_click.cap_containter ) );
    if( !nfctag2_set( NT2_SET_CAP_CONTAINER, NT2_click.cap_containter ) )
        LOG( "New CC writing finished\r\n" );
}

/*
 * Example how to use :
 *  - nfctag2_config_get
 *  - nfctag2_config_set
 *
 * Checks the I2C Clock Strentching
 * Configuring the device NC register
 */
void test_read_config( void )
{
    LOG( "CLK Stretching " );
    if( nfctag2_config_get( NT2_CFG_STR ) | NT2_I2C_CLK_STR_ON )
        LOG( "ON\r\n" );
    else
        LOG( "OFF\r\n");
}

void test_write_config( void )
{
    LOG( "Writing new NC reg content");
    if( !nfctag2_config_set( NT2_CFG_NC_REG, NT2_I2C_RST_OFF         |
                                             NT2_FD_OFF_MODE_0       |
                                             NT2_FD_ON_MODE_0        |
                                             NT2_DIRECTION_I2C_TO_RF ) )
        LOG( "NC Configuration Written\r\n" );
}

/*
 * Example how to use :
 *  - nfctag2_session_get
 *  - nfctag2_session_set
 *
 * Dumps the content of Session Watchdog Timer
 * Changing of session settings
 */
void test_read_session( void )
{
uint8_t temp[ 2 ];

    LOG( "< Watchdog Timer >\r\n" );
    temp[ 0 ] = nfctag2_session_get( NT2_CFG_WDT_MS );
    temp[ 1 ] = nfctag2_session_get( NT2_CFG_WDT_LS );
    print_mem( temp, 2 );
}

void test_write_session( void )
{
    if( !nfctag2_session_set( NT2_CFG_NC_REG, NT2_MASK_NC_I2C_RST,
                                              NT2_I2C_RST_OFF ) )
        LOG( "Restart the module on I2C Repeated start ON\r\n");
    if( !nfctag2_session_set( NT2_SES_NS_REG, NT2_MASK_NS_EEPROM_MASK,
                                              NT2_EEPROM_ERR_CLEAR ) )
        LOG( "EEPROM Error flag removed\r\n");
}

/*
 * Example how to use :
 *  - nfctag2_memory_write
 *
 * Raw Writting of NDEF message to user memory
 */
void write_ndef( void )
{
uint8_t ndef_rec[] = { 0x03,        // NDEF Message
                       15,          // Message size

                       0xD1,        // Record header
                       1,           // Type Length - 1 byte
                       11,          // Payload Length - 11 bytes
                       'U',         // Type / URI
                       0x01,        // Payload
                       'm', 'i', 'k', 'r', 'o', 'e', '.', 'c', 'o', 'm',
                       0xFE };      // NDEF Message End Mark

    memset( NT2_click.user_memory, 0, 888 );
    nfctag2_memory_write( 0, NT2_click.user_memory, 888 );
    nfctag2_memory_write( 0, ndef_rec, sizeof( ndef_rec ) );
}


void main()
{
    system_init();
    nfctag2_init( 0x04 );

    //test_read_common();
    //test_write_common();

    //test_read_config();
    //test_write_config();

    //test_read_session();
    //test_write_session();

    write_ndef();

    while( 1 );
}
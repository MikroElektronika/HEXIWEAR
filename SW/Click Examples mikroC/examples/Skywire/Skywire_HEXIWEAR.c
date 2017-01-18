/*
 * Example for Skywire click with HE910 module & Thermo 3 click
 *
 * Date         Dec 2016
 * Author       MilosV
 * Copyright    GNU Public License v2
 *
 * Test configuration :
 *  Dev. Board    :        Hexiwear
 *  SW            :        mikroC PRO for ARM v4.9.0
 *
 * Include example.pld file in your project.
 *
 ******************************************************************************/

#include "at_engine.h"

/*
 * Skywire  pins
 */
sbit SKYWIRE_EN           at PTB_PDOR.B2;
sbit SKYWIRE_RST          at PTB_PDOR.B11;

/*
 * Ring Flag
 */
bool measure_f;

/*
 * Response buffer
 */
uint8_t buffer[ 1024 ] = { 0 };

/*
 * Caller ID
 */
char caller_id[ 20 ] = { 0 };

/*
 * Thermo 3 measurement
 */
float temperature  = 0.0F;

/*
 * System Initialization
 *    - GPIO Initialization
 *        + HE910 EN pin
 *        + HE910 RST pin
 *    - Peripherals Initialization
 *        + UART3 for data dump
 *        + UART2 for HE910
 *        + I2C0 for Thermo 3 click
 *    - Interrupt Initialization
 *        + Timer
 *        + UART
 */
static void system_init( void )
{
    GPIO_Digital_Output( &PTB_PDOR, _GPIO_PINMASK_11 | _GPIO_PINMASK_2 );
    UART2_Init_Advanced( 115200, _UART_8_BIT_DATA, _UART_NOPARITY,
                         _UART_ONE_STOPBIT, &_GPIO_Module_UART2_PD3_2 );
    UART3_Init_Advanced( 115200, _UART_8_BIT_DATA, _UART_NOPARITY,
                         _UART_ONE_STOPBIT, &_GPIO_Module_UART3_PC16_17 );
    I2C0_Init_Advanced( 400000, &_GPIO_Module_I2C0_PD8_9 );
    
    SIM_SCGC6 |= ( 1 << PIT );
    PIT_MCR = 0x00;
    PIT_LDVAL0 = 59999;
    PIT_TCTRL0 |= 2;
    PIT_TCTRL0 |= 1;
    UART2_C2 |= 1 << 5;
    NVIC_IntEnable(IVT_INT_PIT0);
    NVIC_IntEnable( IVT_INT_UART2_RX_TX );
    EnableInterrupts();
    LOG( "\r\n_______________________________\r\n System Initialized\r\n" );
}

/*
 * Power ON routine for HE910
 */
static void skywire_power_on( void )
{
    SKYWIRE_EN = 0;
    Delay_ms( 5000 );
    SKYWIRE_EN = 1;
    Delay_ms( 3000 );
    LOG( "\r\nSkywire Initialized\r\n" );
}


/*
 * Default response handler
 */
void rsp_handler( char *rsp )
{
    char tmp[ 25 ] = { 0 };

    LOG( "Response : \r\n" );
    LOG( rsp );
    LOG( "\r\n" );
    if( !strncmp( "\r\nRING", rsp, 6 ) )
        measure_f = true;
}

/*
 * Caller ID handler used to store caller ID in global var
 */
void callerid_handler( char *rsp )
{
    char *tmp_s;
    char *tmp_e;

    tmp_s = strchr( rsp, '\"' );
    tmp_e = strchr( tmp_s + 1, '\"' );
    strncpy( caller_id, tmp_s, tmp_e - tmp_s + 1 );
}

/*
 * Temperature measurement with Thermo 3
 */
void measure_temp( void )
{
    int raw_temp;
    uint8_t tmp_data[ 2 ] = { 0x00 };

    I2C_Start();
    I2C_Write( 0x48, tmp_data, 1, END_MODE_RESTART );
    I2C_Read( 0x48, tmp_data, 2, END_MODE_STOP );
    raw_temp = ( ( tmp_data[ 0 ] << 8 ) | tmp_data[ 1 ] ) >> 4;

    if( raw_temp & ( 1 << 11 ) )
        raw_temp |= 0xF800;

    temperature = ( float )( raw_temp * 0.0625 );
}

/*
 * Composing Command and SMS content
 */
void reply_to_caller( void )
{
    char tmp[ 30 ] = { 0 };
    char cmd_content[ 30 ] = { 0 };                                             // Send SMS command
    char reply_content[ 256 ] = { 0 };                                          // SMS content
    
    strcat( cmd_content, "AT+CMGS=" );
    strcat( cmd_content, caller_id );
    strcat( reply_content, "Temperature : " );
    FloatToStr( temperature, tmp );
    strcat( reply_content, Ltrim( tmp ) );
    strcat( reply_content, " C" );
    at_cmd_double( cmd_content, reply_content );
}


void main()
{
    measure_f = false;
    system_init();
    skywire_power_on();
    at_init( rsp_handler, UART2_Write, buffer, sizeof( buffer ) );
    at_cmd_save( "+CLCC", 1000, NULL, NULL, NULL, callerid_handler );           // Assign caller ID handler
    at_cmd_single( "AT" );
    at_cmd_single( "AT+CSCS=\"GSM\"" );
    at_cmd_single( "AT+CMGF=1" );

    while( 1 )
    {
        at_process();
        
        if( measure_f )
        {
            measure_temp();
            at_cmd_single( "AT+CLCC" );
            at_cmd_single( "ATH" );
            Delay_ms( 2000 );                                                   // Delay needed after ATH
            reply_to_caller();
            measure_f = false;
        }
    }
}

/*
 * Timer Interrupt
 */
void Timer0_interrupt() iv IVT_INT_PIT0 
{
    PIT_TFLG0.TIF = 1;
    at_tick();
}

/*
 * UART Interrupt
 */
void UART2_RX_ISR() iv IVT_INT_UART2_RX_TX ics ICS_OFF
{
     char foo = UART2_S1;
     char tmp = UART2_D;

     if( foo & ( 1 << 5 ) )
        at_rx( tmp );
}
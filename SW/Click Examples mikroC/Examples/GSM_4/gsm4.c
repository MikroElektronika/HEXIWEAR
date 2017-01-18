#include "gsm4.h"

extern bool ring_f;
extern bool sent_f;

static char tmp_num[ 20 ] = { 0 };

void gsm4_init( void )
{
    engine_init( gsm4_evn_default );
    
    at_cmd_save( "RING",          1000, NULL, NULL, NULL, gsm4_ev_ring );
    
    at_cmd( "AT" );
    at_cmd( "AT+CSCS=\"GSM\"" );
    at_cmd( "AT+CMGF=1" );
}

void gsm4_evn_default( char *response )
{
    UART3_Write_Text( response );
}

void gsm4_ev_ring( char *response )
{
    ring_f = true;
}

void gsm4_send_sms( uint8_t* rsp, uint8_t rsp_len )
{
    at_cmd( "AT+CMGS=\"0643280993\"" );
    at_cmd_addition( "Hello it's me, Hexiwear! :)" );
    Delay_ms( 1000 );
    sent_f = true;
}
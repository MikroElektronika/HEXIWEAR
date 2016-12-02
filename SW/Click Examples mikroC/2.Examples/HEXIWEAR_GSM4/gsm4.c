#include "gsm4.h"

extern bool req_pend_f;
extern bool ring_f;

static char tmp_num[ 20 ] = { 0 };

void gsm4_init( void )
{
    engine_init( gsm4_evn_default );
    
    at_cmd_save( "RING", 1000, NULL, NULL, NULL, gsm4_ev_ring );
    
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

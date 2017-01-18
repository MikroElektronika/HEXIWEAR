#include <stdbool.h>
#include "hexiwear_uart_messaging.h"

static bool response_f;

static uint8_t rx_idx          = 0;
static uint8_t rx_len          = 0;
static uint8_t tmp_len         = 0;

static uint8_t rx_data[ 25 ] = { 0 };

static event_type_t event;
static event_handler handlers[ 4 ];

/***************************************************************************//**
 *
 */
void hexiwear_uart_messaging_process( void )
{
    if( response_f )
    {
        handlers[ event ]( rx_data, rx_len );
        response_f = false;
    }
}

/***************************************************************************//**
 *
 */
void add_event_handler( event_type_t type, event_handler callback )
{
    handlers[ type ] = callback;
}

/***************************************************************************//**
 *
 */
 
void msg_rx( char input )
{
    if( rx_idx > 3 )
    {
        if( tmp_len ) 
        {
            rx_data[ rx_idx - 3 ] = input;
            tmp_len--;
            rx_idx++;
        }
        else if( tmp_len == 0 && input == 0x45 )
        {
            response_f = true;
        }
        else
        {
            rx_idx = 0;
        }
    }
    else
    {
        if( rx_idx == 3 )
        {
            rx_len = tmp_len = input;
            rx_idx++;
        }
        else if ( rx_idx == 2 )
        {
            event = input;
            rx_idx++;
        }
        else if( rx_idx == 1 && ( ( input == 0xAA ) || ( input == 0xAB ) ) )
        {
            rx_idx++;
        }
        else if( rx_idx == 0 && input == 0x55 )
        {
            rx_idx++;
        } 
        else 
        {
            rx_idx = 0;
        }
    }
}












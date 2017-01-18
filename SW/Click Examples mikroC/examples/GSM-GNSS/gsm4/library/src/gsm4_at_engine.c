/**
 * @file                                                    gsm4_at_engine.c
 * @cond INTERNAL_DOC
 *
 * @brief                       GSM Engine
 *
 * Version : 0.0.1
 *
 * Revision Log :
 * - 0.0.1 (Nov/2016) Module created                        Milos Vidojevic
 *
 ******************************************************************************/

#include "gsm4_at_engine.h"

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/

/* TEMPS */
static uint32_t                 temp_timer;
static at_cmd_cb                temp_cb;

/* FLAGS */
volatile bool                   timeout_f;
volatile bool                   exception_f;
volatile bool                   response_f;
volatile bool                   cue_f;

/* CALLBACKS */
static volatile at_cmd_cb       cb;
static volatile at_cmd_cb       cb_default;

/* BUFFERS */
volatile char                   tx_buffer[ AT_TRANSFER_SIZE ];
volatile char                   rx_buffer[ AT_TRANSFER_SIZE ];

/******************************************************************************
* Public Function Definitions
*******************************************************************************/

void engine_init( at_cmd_cb default_callback )
{
    cb_default = default_callback;
    
    dev_adapter_init();
    dev_timer_init();
    at_parser_init();

    at_cmd_save( "+CMS ERROR:", AT_DEFAULT_TIMEOUT, default_callback,
                                                  default_callback, 
                                                  default_callback, 
                                                  default_callback );

    exception_f   = false;
    response_f    = false;
    cue_f         = false;

    memset( ( void* )tx_buffer, 0, AT_TRANSFER_SIZE );
}

void at_cmd( char *input )
{
    char* temp_input = input;

    Delay_ms( 100 );
    at_parse( temp_input, &temp_cb, &temp_timer );
    dev_timer_load( temp_timer );

    while( cue_f )
        at_process();

    while( !dev_tx( *( temp_input++ ) ) );

    dev_adapter_reset();
    dev_timer_start();
}

void at_cmd_addition( char *input )
{
    char* temp_input = input;

    Delay_ms( 100 );
    while( !exception_f )
        at_process();

    dev_timer_stop();

    while( !dev_tx( *( temp_input++ ) ) );

    dev_adapter_reset();
    dev_timer_restart();
}

void at_cmd_save
(
        char *cmd,
        uint32_t timeout,
        at_cmd_cb getter,
        at_cmd_cb setter,
        at_cmd_cb tester,
        at_cmd_cb executer
)
{
    if ( !setter )
        setter = cb_default;

    if( !getter )
        getter = cb_default;

    if( !tester )
        tester = cb_default;

    if( !executer )
        executer = cb_default;

    if( !timeout )
        timeout = AT_DEFAULT_TIMEOUT;

    at_parser_store( cmd, timeout, getter, setter, tester, executer );
}

void at_process( void )
{
    if( response_f )
    {
        dev_hal_cts_ctl( false );
        dev_timer_stop();
        at_parse( rx_buffer, &cb, &temp_timer );
        cb( rx_buffer );
        dev_adapter_reset();

        timeout_f = false;
        exception_f = false;
        response_f = false;
        cue_f = false;
    }

    if( timeout_f )
    {
        dev_hal_cts_ctl( false );
        dev_timer_stop();
        at_parse( rx_buffer, &cb, &temp_timer );
        cb( rx_buffer );
        dev_adapter_reset();

        timeout_f = false;
        exception_f = false;
        response_f = true;
        cue_f = false;
    }
}

/**
 * @endcond
 */
/*************** END OF FUNCTIONS *********************************************/
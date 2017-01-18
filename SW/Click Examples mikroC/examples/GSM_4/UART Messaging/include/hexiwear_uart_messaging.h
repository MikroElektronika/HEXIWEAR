/**
 * @file hexiwear_uart_messaging.h
 * @brief <h2>  The serial interface between host processor MK64 and bluetooth 
 *              processor KW40 UART communication library. </h2>
 *
 *
 * @date        05 Dec 2016
 * @author      Branislav Marton
 *
 ******************************************************************************/

#ifndef HEXIWEAR_UART_MESSAGIGN_H
#define HEXIWEAR_UART_MESSAGIGN_H

#include <stdint.h>

/*******************************************************************************
 * TYPEDEFS
 ******************************************************************************/

typedef enum
{
    PT_PRESS_UP     = 0, /**< touch press up */
    PT_PRESS_DOWN   = 1, /**< touch press down */
    PT_PRESS_LEFT   = 2, /**< touch press left */
    PT_PRESS_RIGHT  = 3, /**< touch press right */
    
} event_type_t;

typedef void ( *event_handler )( uint8_t* response, uint8_t len );

/*******************************************************************************
 * FUNCTIONS
 ******************************************************************************/

void msg_rx( char input );
 
void add_event_handler( event_type_t type, event_handler handler );

void hexiwear_uart_messaging_process( void );

void gsm4_send_sms( uint8_t* rsp, uint8_t rsp_len );

#endif // !HEXIWEAR_UART_MESSAGIGN_H
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

#ifndef HEXIWEAR_UART_MESSAGING_H
#define HEXIWEAR_UART_MESSAGING_H

#include <stdint.h>

#define NULL 0
/*******************************************************************************
 * TYPEDEFS
 ******************************************************************************/

typedef enum
{
    PT_PRESS_UP     = 0, /**< touch press up */
    PT_PRESS_DOWN   = 1, /**< touch press down */
    PT_PRESS_LEFT   = 2, /**< touch press left */
    PT_PRESS_RIGHT  = 3, /**< touch press right */
} packet_type;

typedef void (*packet_msg_callback)( void );

/*******************************************************************************
 * FUNCTIONS
 ******************************************************************************/
void hexiwear_uart_messaging_callback(
    packet_type type,
    packet_msg_callback callback
);

void hexiwear_uart_messaging_init( void );
void hexiwear_uart_messaging_process( void );

#endif // !HEXIWEAR_UART_MESSAGING_H
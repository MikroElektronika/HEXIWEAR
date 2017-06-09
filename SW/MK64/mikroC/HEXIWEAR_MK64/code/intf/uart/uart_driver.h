// File: uart_driver.h

// Declarations of main functionalities in the UART module.

#ifndef _uart_driver_h_
#define _uart_driver_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <stdbool.h>
#include "OSA.h"

////////////////////////////////////////////////////////////////////////////////
// Type definitions.                                                          //
////////////////////////////////////////////////////////////////////////////////

// UART receive callback function type.
typedef void ( *uart_rx_callback_t )( uint32_t instance, void *uartState );

// UART transmit callback function type.
typedef void ( *uart_tx_callback_t )( uint32_t instance, void *uartState );

// @brief Runtime state of the UART driver.
typedef struct UartState {
    // Number of data word entries in TX FIFO.
    uint8_t txFifoEntryCount;
    // The buffer of data being sent.
    const uint8_t * txBuff;
    // The buffer of received data.
    uint8_t * rxBuff;
    // The remaining number of bytes to be transmitted.
    volatile size_t txSize;
    // The remaining number of bytes to be received.
    volatile size_t rxSize;
    // True if there is an active transmit.
    volatile bool isTxBusy;
    // True if there is an active receive.
    volatile bool isRxBusy;
    // True if transmit is blocking transaction.
    volatile bool isTxBlocking;
    // True if receive is blocking transaction.
    volatile bool isRxBlocking;
    // Used to wait for ISR to complete its TX business.
    semaphore_t txIrqSync;
    // Used to wait for ISR to complete its RX business.
    semaphore_t rxIrqSync;
    // Callback to invoke after receiving byte.
    uart_rx_callback_t rxCallback;
    // Receive callback parameter pointer.
    void * rxCallbackParam;
    // Callback to invoke after transmitting byte.
    uart_tx_callback_t txCallback;
    // Transmit callback parameter pointer.
    void * txCallbackParam;
} uart_state_t;

////////////////////////////////////////////////////////////////////////////////
// Global function declarations.                                              //
////////////////////////////////////////////////////////////////////////////////
 
uint32_t CLOCK_SYS_GetBusClockFreq();

// Initialises UART4 module.
void UART_DRV_Init( uart_state_t* uartStatePtr );

#endif
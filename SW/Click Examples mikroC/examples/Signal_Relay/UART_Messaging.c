#include "UART_Messaging.h"

static uint8_t msg_buffer[28] = { 0 };
static uint8_t msg_index = 0;

static volatile uint8_t ble_rx_buffer[256] = { 0 };
static volatile uint8_t rx_head_ind  = 0;
static volatile uint8_t rx_tail_ind  = 0;

static uint8_t trailer_flag = 0;

static packet_msg_callback callbacks[4] = { NULL };

/***************************************************************************//**
 *
 */
void hexiwear_uart_messaging_init( void )
{
  UART4_Init_Advanced(
           230400,
           _UART_8_BIT_DATA,
           _UART_NOPARITY,
           _UART_TWO_STOPBITS,
           &_GPIO_Module_UART4_PE24_25
       );
       
       Delay_ms( 100 );

    // Enable interrupt
    EnableInterrupts();
    NVIC_IntEnable( IVT_INT_UART4_RX_TX );
    UART4_C2 |= 1 << 5;
}
 
void hexiwear_uart_messaging_process( void )
{
    uint8_t tmp = 0;

    while(rx_tail_ind != rx_head_ind)
    {
        tmp = ble_rx_buffer[rx_tail_ind++];
        msg_buffer[msg_index++] = tmp;

        if(tmp == 0x45)
        {
            trailer_flag = 1;
        }
    }

    if (trailer_flag)
    {
        if(msg_buffer[0] == 0x55)
        {
            tmp = msg_buffer[2];

            if(tmp < 4 && tmp >= 0 && callbacks[tmp] != 0)
                callbacks[tmp]();
        }

        msg_index = 0;
        trailer_flag = 0;
    }
}

/***************************************************************************//**
 *
 */
void hexiwear_uart_messaging_callback(
    packet_type type,
    packet_msg_callback callback
)
{
    callbacks[type] = callback;
}

/***************************************************************************//**
 *
 */
void BLE_RX_ISR() iv IVT_INT_UART4_RX_TX ics ICS_AUTO
{
    if(  UART4_S1 & ( 1 << 5 )  )
    {
        uint8_t tmp = UART4_D;

        ble_rx_buffer[rx_head_ind++] = tmp;

    }
}
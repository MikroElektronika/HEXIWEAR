#line 1 "C:/Users/djordje.rosic/Desktop/Archive/mic_24045_click/example/ARM/UART_Messaging.c"
#line 1 "c:/users/djordje.rosic/desktop/archive/mic_24045_click/library/include/uart_messaging.h"
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for arm/include/stdint.h"





typedef signed char int8_t;
typedef signed int int16_t;
typedef signed long int int32_t;
typedef signed long long int64_t;


typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long int uint32_t;
typedef unsigned long long uint64_t;


typedef signed char int_least8_t;
typedef signed int int_least16_t;
typedef signed long int int_least32_t;
typedef signed long long int_least64_t;


typedef unsigned char uint_least8_t;
typedef unsigned int uint_least16_t;
typedef unsigned long int uint_least32_t;
typedef unsigned long long uint_least64_t;



typedef signed long int int_fast8_t;
typedef signed long int int_fast16_t;
typedef signed long int int_fast32_t;
typedef signed long long int_fast64_t;


typedef unsigned long int uint_fast8_t;
typedef unsigned long int uint_fast16_t;
typedef unsigned long int uint_fast32_t;
typedef unsigned long long uint_fast64_t;


typedef signed long int intptr_t;
typedef unsigned long int uintptr_t;


typedef signed long long intmax_t;
typedef unsigned long long uintmax_t;
#line 22 "c:/users/djordje.rosic/desktop/archive/mic_24045_click/library/include/uart_messaging.h"
typedef enum
{
 PT_PRESS_UP = 0,
 PT_PRESS_DOWN = 1,
 PT_PRESS_LEFT = 2,
 PT_PRESS_RIGHT = 3,
} packet_type;

typedef void (*packet_msg_callback)( void );
#line 35 "c:/users/djordje.rosic/desktop/archive/mic_24045_click/library/include/uart_messaging.h"
void hexiwear_uart_messaging_callback(
 packet_type type,
 packet_msg_callback callback
);

void hexiwear_uart_messaging_init( void );
void hexiwear_uart_messaging_process( void );
#line 3 "C:/Users/djordje.rosic/Desktop/Archive/mic_24045_click/example/ARM/UART_Messaging.c"
static uint8_t msg_buffer[28] = { 0 };
static uint8_t msg_index = 0;

static volatile uint8_t ble_rx_buffer[256] = { 0 };
static volatile uint8_t rx_head_ind = 0;
static volatile uint8_t rx_tail_ind = 0;

static uint8_t trailer_flag = 0;

static packet_msg_callback callbacks[4] = {  0  };
#line 17 "C:/Users/djordje.rosic/Desktop/Archive/mic_24045_click/example/ARM/UART_Messaging.c"
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
#line 68 "C:/Users/djordje.rosic/Desktop/Archive/mic_24045_click/example/ARM/UART_Messaging.c"
void hexiwear_uart_messaging_callback(
 packet_type type,
 packet_msg_callback callback
)
{
 callbacks[type] = callback;
}
#line 79 "C:/Users/djordje.rosic/Desktop/Archive/mic_24045_click/example/ARM/UART_Messaging.c"
void BLE_RX_ISR() iv IVT_INT_UART4_RX_TX ics ICS_AUTO
{
 if( UART4_S1 & ( 1 << 5 ) )
 {
 uint8_t tmp = UART4_D;

 ble_rx_buffer[rx_head_ind++] = tmp;

 }
}

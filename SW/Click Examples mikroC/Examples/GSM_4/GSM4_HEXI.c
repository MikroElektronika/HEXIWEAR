#include "hexiwear_uart_messaging.h"
#include "OLED_driver.h"
#include "gsm4.h"
#include "pic.h"

sbit GSM_PWR at PTB_PDOR.B11;
sbit GSM_CTS at PTB_PDIR.B13;
sbit GSM_RTS at PTC_PDOR.B4;
sbit GSM_RING at PTA_PDIR.B10;
sbit GSM_STAT at PTB_PDIR.B2;

sbit LED3 at PTA_PDOR.B14;

bool ring_f;
bool sent_f;

void system_init() 
{
    GPIO_Digital_Output( &PTA_PDOR, _GPIO_PINMASK_14 );
    GPIO_Digital_Output( &PTB_PDOR, _GPIO_PINMASK_11 );
    GPIO_Digital_Output( &PTC_PDOR, _GPIO_PINMASK_4 );
    GPIO_Digital_Input( &PTB_PDIR, _GPIO_PINMASK_13 );
    GPIO_Digital_Input( &PTA_PDIR, _GPIO_PINMASK_10 | _GPIO_PINMASK_12 );
    GPIO_Digital_Input( &PTB_PDIR, _GPIO_PINMASK_2 );
    
    PORTA_PCR12 |= 0x00000002;                                                  // PULLDOWN A12
    
    UART4_Init_Advanced( 230400, _UART_8_BIT_DATA, _UART_NOPARITY,
                         _UART_TWO_STOPBITS, &_GPIO_Module_UART4_PE24_25 );
    
    UART3_Init_Advanced( 230400, _UART_8_BIT_DATA, _UART_NOPARITY,
                         _UART_ONE_STOPBIT, &_GPIO_Module_UART3_PC16_17 );
                         
    UART2_Init_Advanced( 9600, _UART_8_BIT_DATA, _UART_NOPARITY,
                         _UART_ONE_STOPBIT, &_GPIO_Module_UART2_PD3_2 );

    UART4_C2 |= 1 << 5;
    NVIC_IntEnable( IVT_INT_UART4_RX_TX );
    UART2_C2 |= 1 << 5;
    NVIC_IntEnable( IVT_INT_UART2_RX_TX );
    
    EnableInterrupts();
    Delay_ms( 500 );
    
    UART3_Write_Text( "INITIALIZED\r\n" );
}

void main() {

    system_init();
    gsm4_init();
    
    add_event_handler( PT_PRESS_LEFT, gsm4_send_sms );
    
    OLED_Init();
    OLED_DrawImage( gsm_4_bmp, 0 , 0 );
    
    LED3 = 1;
    
    while( 1 ) 
    {
        at_process();
        hexiwear_uart_messaging_process();
        
        if( ring_f ) 
        {
             LED3 = ~LED3;
             ring_f = false;
        }
        
        if( sent_f )
        {
            OLED_DrawImage( msg_sent_bmp, 0 , 0 );
            Delay_ms( 1500 );
            OLED_DrawImage( gsm_4_bmp, 0 , 0 );
            sent_f = false;
        }
    }
}

void UART2_RX_ISR() iv IVT_INT_UART2_RX_TX ics ICS_OFF
{
     char foo = UART2_S1;
     char tmp = UART2_D;

     if( foo & ( 1 << 5 ) )
        dev_rx( tmp );
}

void UART4_RX_ISR() iv IVT_INT_UART4_RX_TX ics ICS_OFF
{
    char foo = UART4_S1;
    char tmp = UART4_D;

    if( foo & ( 1 << 5 ) )
        msg_rx( tmp );
}
#include "OLED_driver.h"
#include "gsm4.h"

sbit GSM_PWR at PTB_PDOR.B11;
sbit GSM_CTS at PTB_PDIR.B13;
sbit GSM_RTS at PTC_PDOR.B4;
sbit GSM_RING at PTA_PDIR.B10;
sbit GSM_STAT at PTB_PDIR.B2;

sbit LED3 at PTA_PDOR.B14;

bool ring_f;

void system_init() 
{
    GPIO_Digital_Output( &PTA_PDOR, _GPIO_PINMASK_14 );
    GPIO_Digital_Output( &PTB_PDOR, _GPIO_PINMASK_11 );
    GPIO_Digital_Output( &PTC_PDOR, _GPIO_PINMASK_4 );
    GPIO_Digital_Input( &PTB_PDIR, _GPIO_PINMASK_13 );
    GPIO_Digital_Input( &PTA_PDIR, _GPIO_PINMASK_10 );
    GPIO_Digital_Input( &PTB_PDIR, _GPIO_PINMASK_2 );
    
    UART3_Init_Advanced( 115200, _UART_8_BIT_DATA, _UART_NOPARITY,
                         _UART_ONE_STOPBIT, &_GPIO_Module_UART3_PC16_17 );
                         
    UART2_Init_Advanced( 9600, _UART_8_BIT_DATA, _UART_NOPARITY,
                         _UART_ONE_STOPBIT, &_GPIO_Module_UART2_PD3_2 );

    EnableInterrupts();
    NVIC_IntEnable( IVT_INT_UART2_RX_TX );
    UART2_C2 |= 1 << 5;

    Delay_ms( 500 );
    UART3_Write_Text( "INITIALIZED\r\n" );
}

void main() {

    system_init();
    gsm4_init();
    
    LED3 = 1;
    
    while( 1 ) {
    
        at_process();
        
        if( ring_f ) {
        
             LED3 = ~LED3;
             ring_f = false;
        }
    }
}

void UART_RX_ISR() iv IVT_INT_UART2_RX_TX ics ICS_AUTO
{
     char foo = UART2_S1;
     char tmp = UART2_D;
     
     if( foo & ( 1 << 5 ) )
        dev_rx( tmp );
}
/*
Example for 7x10 G Click

    Date          : Jul 2017.
    Author        : MikroE Team

Test configuration STM32 :

    MCU              : MK64FN1M0XXX12
    Dev. Board       : EasyMx PRO v7 for STM32 ARM
    ARM Compiler ver : v.5.1.0

Description :

    Example of multiplexed 7 x 10 led matrix control shown through scrolling
    text over the matrix, showing numbers and specific pixels

*/

#include <stdint.h>
#include <stdbool.h>
#include "__S7X10G_Driver.h"

sbit S7X10G_CS at PTC_PDOR.B4;
sbit S7X10G_RST at PTB_PDOR.B11;
sbit S7X10G_ROW_RST at PTA_PDOR.B10;
sbit S7X10G_ROW_CLK at PTB_PDOR.B2;

void systemInit()
{
    GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_4);    // Set CS pin as output
    GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_11);   // Set RST pin as output
    GPIO_Digital_Output(&PTA_PDOR, _GPIO_PINMASK_10);   // Set PWM pin as output
    GPIO_Digital_Output(&PTB_PDOR, _GPIO_PINMASK_2);    // Set PWM pin as output

    // Initialize SPI
    SPI0_Init_Advanced( 8000000, _SPI_CFG_MASTER | _SPI_CFG_FRAME_SIZE_8BITS |
                        _SPI_CFG_CLK_IDLE_LOW | _SPI_CFG_MSB_FIRST |
                        _SPI_CFG_CLK_PHASE_CAPT_LEADING,
                        &_GPIO_Module_SPI0_PC5_7_6 );
                        
    S7X10G_init();
}

void S7X10G_Task()
{
    bool ind;
    static bool called = false;
    int i, j;
    S7X10G_clearDisplay();
    
    // scrolls given text
    if ( !called )
    {
        S7X10G_drawText( "  Mikro Elektronika" );
        S7X10G_scrollEnable( S7X10G_SPEED_MED );
        called = true;
    }
    do
    {
        ind = S7X10G_refreshDisplay();
        S7X10G_tick();
        Delay_ms( 10 );
    } while( ind );
    called = false;
    
    // writes numbers from 0 to 10
    for( i = 0; i < 11; ++i )
    {
        S7X10G_clearDisplay();
        S7X10G_drawNumber( i );
        for( j = 0; j < 30; ++j )
        {
            S7X10G_refreshDisplay();
            Delay_ms( 10 );
        }
    }
    
    // draws a few pixels
    S7X10G_clearDisplay();
    S7X10G_drawPixel( 6, 3 );
    S7X10G_drawPixel( 6, 8 );
    S7X10G_drawPixel( 2, 3 );
    S7X10G_drawPixel( 2, 8 );
    for( j = 0; j < 100; ++j )
    {
        S7X10G_refreshDisplay();
        Delay_ms( 10 );
    }
    
}

void main()
{
    systemInit();

    while( 1 )
    {
        S7X10G_Task();
    }
}
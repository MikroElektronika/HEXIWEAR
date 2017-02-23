/*
 * Example for 2x5W AMP click
 *
 *  Date         Jan 2017
 *  Author       Marton B.
 *  Copyright    GNU Public License v2
 *
 * Test configuration STM32 :
 *
 *  MCU           :	STM32F107VCT6
 *  Dev. Board    :	EasyMx PRO v7 for STM32 ARM
 *  SW            :	mikroC PRO for ARM v4.9.0
 *
 *
 *
 ******************************************************************************/

#include "click_2x5w_amp.h"

/***************************************************************************//**
 *  Variables.
 */
sbit CLICK_2X5W_AMP_GAIN0 at PTB_PDOR.B2;
sbit CLICK_2X5W_AMP_GAIN1 at PTB_PDOR.B11;
sbit CLICK_2X5W_AMP_STBY at PTC_PDOR.B4;
sbit CLICK_2X5W_AMP_MUTE at PTA_PDOR.B10;


static unsigned int gain = 0;

/***************************************************************************//**
 *  Function prototypes.
 */
static void system_init( void );

/***************************************************************************//**
 *
 */
static void system_init( void )
{
    GPIO_Digital_Output( &PTB_PDOR, _GPIO_PINMASK_2 );
    GPIO_Digital_Output( &PTB_PDOR, _GPIO_PINMASK_11 );
    GPIO_Digital_Output( &PTC_PDOR, _GPIO_PINMASK_4 );
    GPIO_Digital_Output( &PTA_PDOR, _GPIO_PINMASK_10 );

    GPIO_Digital_Input( &PTA_PDIR, _GPIO_PINMASK_12 );
    PORTA_PCR12 |= 0x00000002;

    click_2x5W_init();
}

/***************************************************************************//**
 *
 */
void main()
{
    system_init();

    click_2x5W_gain(CLICK_2X5W_AMP_20_DB);
    click_2x5W_mode(CLICK_2X5W_AMP_MODE_PLAY);

    while( 1 )
    {
        if(Button(&PTA_PDIR, 12, 100, 1))
        {
            click_2x5W_gain((click_2x5w_amp_gain_t)(++gain % 4));
        }
    }
}

/************************************************************ END OF FILE *****/
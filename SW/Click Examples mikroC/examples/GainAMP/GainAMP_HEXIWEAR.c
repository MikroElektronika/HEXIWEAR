/*
 * Example for GainAMP click
 *
 * Date         Jan 2017
 * Author       Marton B.
 * Copyright    GNU Public License v2
 *
 * Test configuration Kinetis:
 *  MCU           :	MK64FN1M0XXX12
 *  Dev. Board    :	HEXIWEAR DOCKING STATION
 *  SW            :	mikroC PRO for ARM v4.9.0
 *
 * 
 *
 ******************************************************************************/

#include "gain_amp.h"

sbit GAIN_AMP_CS at PTC_PDOR.B4;
sbit GAIN_AMP_SHDN at PTB_PDOR.B11;

static uint8_t gain;
static uint8_t byte;

static void system_init( void );


static void system_init( void )
{
    GPIO_Digital_Output( &PTB_PDOR, _GPIO_PINMASK_11 );
    GPIO_Digital_Output( &PTC_PDOR, _GPIO_PINMASK_4 );
    GAIN_AMP_CS = 1;

    GPIO_Digital_Input( &PTA_PDIR, _GPIO_PINMASK_12  );
    GPIO_Digital_Input( &PTA_PDIR, _GPIO_PINMASK_13  );

    PORTA_PCR12 |= 0x00000002;
    PORTA_PCR13 |= 0x00000002;

    //GPIO_Digital_Output( &GPIOD_BASE, _GPIO_PINMASK_LOW );

    SPI0_Init_Advanced(
        500000, 
        _SPI_CFG_MASTER | 
        _SPI_CFG_FRAME_SIZE_8BITS | 
        _SPI_CFG_CLK_IDLE_LOW |
        _SPI_CFG_CLK_PHASE_CAPT_LEADING | 
        _SPI_CFG_MSB_FIRST, 
        &_GPIO_Module_SPI0_PC5_7_6
    );

    
    gain_amp_init( SPI0_Write );

    gain = 0;
}

void main()
{
    system_init();

    gain_amp_set(GAIN_AMP_NOMINAL_0, GAIN_AMP_SW_SHUTDOWN);

    while( 1 )
    {
        if(Button(&PTA_PDIR, 12, 100, 1))
        {
            byte = gain_amp_set(++gain & 0x07, GAIN_AMP_SW_SHUTDOWN);
            //GPIOD_ODR = (GPIOD_ODR & 0xFF00) | byte;
        }
        if(Button(&PTA_PDIR, 13, 100, 1))
        {
            byte = gain_amp_set(--gain & 0x07, GAIN_AMP_SW_SHUTDOWN);
            //GPIOD_ODR = (GPIOD_ODR & 0xFF00) | byte;
        }
    }
}

/************************************************************ END OF FILE *****/
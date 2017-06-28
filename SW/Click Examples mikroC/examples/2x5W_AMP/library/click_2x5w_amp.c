/*
 * click_2x5w_amp.c
 *
 * Version : 0.0.1
 *
 * Revision Log :
 * 0.0.1 (Jan/2017) Module created
 *
 * To Do List :
 *
 ******************************************************************************/

#include "click_2x5w_amp.h"


extern sfr sbit CLICK_2X5W_AMP_GAIN0;
extern sfr sbit CLICK_2X5W_AMP_GAIN1;
extern sfr sbit CLICK_2X5W_AMP_STBY;
extern sfr sbit CLICK_2X5W_AMP_MUTE;


/* 		Preprocessors
 ******************************************************************************/

#define LOW     0
#define HIGH    1

#define BIT0_MASK   0b00000001
#define BIT1_MASK   0b00000010


/*		Public Function Definitions
 ******************************************************************************/

void click_2x5W_init( void )
{
    CLICK_2X5W_AMP_GAIN0 = LOW;
    CLICK_2X5W_AMP_GAIN1 = LOW;
    CLICK_2X5W_AMP_STBY = LOW;
    CLICK_2X5W_AMP_MUTE = LOW;
}

void click_2x5W_gain( click_2x5w_amp_gain_t gain )
{
    CLICK_2X5W_AMP_GAIN0 = (gain & BIT1_MASK) ? HIGH : LOW;
    CLICK_2X5W_AMP_GAIN1 = (gain & BIT0_MASK) ? HIGH : LOW;
}

void click_2x5W_mode( click_2x5w_amp_mode_t mode )
{
    CLICK_2X5W_AMP_MUTE = (mode & BIT0_MASK) ? HIGH : LOW;
    CLICK_2X5W_AMP_STBY = (mode & BIT1_MASK) ? HIGH : LOW;
}

/* 								End of File
 ******************************************************************************/
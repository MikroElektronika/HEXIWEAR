/*
 * gain_amp.c
 *
 * Version : 0.0.1
 *
 * Revision Log :
 * 0.0.1 (Feb/2017) Module created
 *
 * To Do List :
 *
 ******************************************************************************/

#include "gain_amp.h"

/* 		Preprocessors
 ******************************************************************************/

#define GAIN_AMP_MASK (0x07)

/*		Typedefs
 ******************************************************************************/



/*		Variables
 ******************************************************************************/

extern sfr sbit GAIN_AMP_CS;
extern sfr sbit GAIN_AMP_SHDN;

static gainamp_write_spi_t write_spi_p;

/* 		Private Function Prototypes
 ******************************************************************************/



/* 		Private Function Definitions
 ******************************************************************************/



/*		Public Function Definitions
 ******************************************************************************/

void gain_amp_init( gainamp_write_spi_t write_spi  )
{
    write_spi_p = write_spi;

    GAIN_AMP_CS = 1;
    GAIN_AMP_SHDN = 0;
}

uint8_t gain_amp_set( uint8_t channel_a, uint8_t channel_b )
{
    uint8_t byte;

    if(channel_b != GAIN_AMP_SW_SHUTDOWN)
        byte = (channel_b & GAIN_AMP_MASK) << 4;
    else
        byte = GAIN_AMP_SW_SHUTDOWN;

    if(channel_a != GAIN_AMP_SW_SHUTDOWN)
        byte = byte | (channel_a & GAIN_AMP_MASK);
    else
        byte = byte | ((GAIN_AMP_SW_SHUTDOWN >> 4) & GAIN_AMP_MASK);

    GAIN_AMP_CS = 0;
    write_spi_p(byte);
    GAIN_AMP_CS = 1;

    return byte;
}

void gain_amp_shutdown( bool flag )
{
    GAIN_AMP_SHDN = flag;
}

/* 								End of File
 ******************************************************************************/
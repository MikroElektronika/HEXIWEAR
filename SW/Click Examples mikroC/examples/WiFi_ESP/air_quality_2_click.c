/*
 * XXX.c
 *
 * Version : 0.0.1
 *
 * Revision Log :
 * 0.0.1 (Sep/2016) Module created                          __________________
 *
 * To Do List :
 *
 ******************************************************************************/

#include "air_quality_2_click.h"

#include "air_quality_2_hal.h"

/*                 Preprocessors
 ******************************************************************************/



/*                Typedefs
 ******************************************************************************/



/*                Variables
 ******************************************************************************/

static uint8_t buffer[9];

/*                 Private Function Prototypes
 ******************************************************************************/



/*                 Private Function Definitions
 ******************************************************************************/



/*                Public Function Definitions
 ******************************************************************************/

void air_quality_2_click_init( void )
{
    hal_air_quality_2_init();

    memset(buffer, 0x00, 9);
}

iaq_status_t air_quality_2_click_info( iaq_info_t* info )
{
    hal_air_quality_2_read(AIR_QUAL_I2C_ADDRESS, buffer, 9);

    info->co2_eq =  ((uint16_t)buffer[0] << 8) + (uint16_t)buffer[1]; 
    info->tvoc_eq = ((uint16_t)buffer[7] << 8) + (uint16_t)buffer[8]; 

    info->resistance =  ((int32_t)buffer[4] << 16) +
                        ((int32_t)buffer[5] << 8) +
                        (int32_t)buffer[6];

    return buffer[2];
}

/*                                                                 End of File
 ******************************************************************************/
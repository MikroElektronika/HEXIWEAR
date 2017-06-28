/****************************************************************************
* Title                 :   I2C Hardware Access Layer
* Filename              :   ir_gesture_hal.c
* Author                :   Nikola Golubovic
* Origin Date           :   15/12/2015
* Notes                 :   None
*****************************************************************************/
/*************** MODULE REVISION LOG ******************************************
*
*    Date    Software Version    Initials    Description
*  15/12/15         1.0            NG
*
*****************************************************************************/
/** 
 * @file ir_gesture_hal.c
 * @brief IR GESTURE Hardware Access Layer
 */
/******************************************************************************
* Includes
*******************************************************************************/
#include "ir_gesture_hal.h"
#include <stdint.h>
#include <string.h>

/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/
/******************************************************************************
* Module Static Variable Definitions
*******************************************************************************/
static uint8_t _i2c_hw_address;


static unsigned int( *start_i2c_p )( void );
static unsigned int( *write_i2c_p )( unsigned char slave_address,
                                     unsigned char *buffer,
                                     unsigned long count,
                                     unsigned long end_mode );
static void( *read_i2c_p )( unsigned char slave_address,
                            unsigned char *buffer,
                            unsigned long count,
                            unsigned long end_mode );


/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Function Definitions
*******************************************************************************/

int ir_gesture_i2c_init( uint8_t address_id )
{

    start_i2c_p = I2C_Start_Ptr;
    write_i2c_p = I2C_Write_Ptr;
    read_i2c_p = I2C_Read_Ptr;

    _i2c_hw_address = address_id;
    return ( _i2c_hw_address == 0 ) ? -1 : 0;
}

void ir_gesture_hal_delay( uint8_t ms )
{
#if defined( __GNUC__ )

#else
    while( ms-- )
        Delay_1ms();
#endif

}

void ir_gesture_i2c_hal_write( uint8_t address, uint8_t const *buff , uint16_t count )
{
    uint8_t temp_buff[ I2C_MAX_BUFFER ];
    uint8_t *temp_ptr = ( uint8_t *)buff;

    temp_buff[0] = address;
    memcpy( &temp_buff[1], temp_ptr, count );

    start_i2c_p();
    write_i2c_p( _i2c_hw_address, temp_buff, count + 1, END_MODE_STOP );
}

void ir_gesture_i2c_hal_read( uint8_t address, uint8_t const *buffer, uint16_t count )
{
   uint8_t *ptr = ( uint8_t *)buffer;

    start_i2c_p();
    write_i2c_p( _i2c_hw_address, &address, 1, END_MODE_RESTART );
    read_i2c_p( _i2c_hw_address, ptr, count, END_MODE_STOP );
}
                                                                /****************************************************************************
* Title                 :   I2C Hardware Access Layer
* Filename              :   heartrate1_hal.c
* Author                :   Nikola Golubovic
* Origin Date           :   23/10/2015
* Notes                 :   None
*****************************************************************************/
/*************** MODULE REVISION LOG ******************************************
*
*    Date    Software Version    Initials    Description
*  10/26/15         1.0            NG
*
*****************************************************************************/
/** @file heartrate1_hal.c
 *  @brief Heartrate 1 [MAX30100]  Hardware Access Layer
 */
/******************************************************************************
* Includes
*******************************************************************************/
#include "fan_click_hal.h"

#if defined( __GNUC__ )
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#endif

/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/
/**
 * Doxygen tag for documenting variables and constants
 */

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/
#define WRITE 0
#define READ  1

/******************************************************************************
* Module statics
*******************************************************************************/
#if defined(__MIKROC_PRO_FOR_ARM__)
static unsigned int ( *i2c_start_p )( void );
static void ( *i2c_read_p )( char slave_address, char *ptrdata,
                             unsigned long count, unsigned long END_mode );
static unsigned int ( *i2c_write_p )( unsigned char slave_address,
                                      unsigned char *buf,
                                      unsigned long count,
                                      unsigned long END_mode );

#elif defined(__MIKROC_PRO_FOR_AVR__)
static unsigned char ( *i2c_start_p )( void );
static unsigned char ( *i2c_read_p )( unsigned char ack );
static void ( *i2c_write_p )( unsigned char data_ );
static void ( *i2c_stop_p )( void );

#elif defined(__MIKROC_PRO_FOR_8051__)

#elif defined(__MIKROC_PRO_FOR_FT90x__)
static char ( *i2c_read_p )( char *bufferIn, unsigned int numBytesToReceive );
static char ( *i2c_write_p )( char *bufferOut, unsigned int numBytesToWrite );

#elif defined(__MIKROC_PRO_FOR_PIC__)
static unsigned char ( *i2c_start_p )( void );
static unsigned char ( *i2c_read_p )( unsigned char ack );
static unsigned char ( *i2c_write_p )( unsigned char data_ );
static void ( *i2c_stop_p )( void );
static void ( *i2c_repeat_p )( void );

#elif defined(__MIKROC_PRO_FOR_DSPIC__)
static unsigned int ( *i2c_start_p )( void );
static unsigned char ( *i2c_read_p )( unsigned int ack );
static unsigned int ( *i2c_write_p )( unsigned char data_ );
static void ( *i2c_stop_p )( void );
static void ( *i2c_repeat_p )( void );

#elif defined(__MIKROC_PRO_FOR_PIC32__)
static unsigned int ( *i2c_start_p )( void );
static unsigned char ( *i2c_read_p )( unsigned int ack );
static unsigned int ( *i2c_write_p )( unsigned char data_ );
static void ( *i2c_stop_p )( void );

#endif

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
static uint8_t i2c_address;

#if defined(__GNUC__)
#define i2c_start_p 1
#define i2c_read_p  1
#define i2c_write_p 1
#endif

/******************************************************************************
* Function Prototypes
*******************************************************************************/
#if defined( __GNUC__ )
const char *byte_to_binary( int x );
#endif

/******************************************************************************
* Function Definitions
*******************************************************************************/
#if defined( __GNUC__ )
const char *byte_to_binary( int x )
{
    static char b[9];
    b[0] = '\0';

    int z;

    for ( z = 128; z > 0; z >>= 1 )
        strcat( b, ( ( x & z ) == z ) ? "1" : "0" );

    return b;
}
#endif


int fan_i2c_init( uint8_t address_id )
{
#if defined( __MIKROC_PRO_FOR_ARM__ ) || \
    defined(__MIKROC_PRO_FOR_FT90x__)
    i2c_address = address_id;
#else
    i2c_address = ( address_id << 1 );
#endif

#if defined(__MIKROC_PRO_FOR_AVR__)
    i2c_start_p = TWI_Start;
    i2c_read_p  = TWI_Read;
    i2c_write_p = TWI_Write;
    i2c_stop_p  = TWI_Stop;

#elif defined(__MIKROC_PRO_FOR_ARM__ )
    i2c_start_p = I2C_Start_Ptr;
    i2c_read_p  = I2C_Read_Ptr;
    i2c_write_p = I2C_Write_Ptr;

#elif defined(__MIKROC_PRO_FOR_8051__)

#elif defined(__MIKROC_PRO_FOR_FT90x__)
    i2c_read_p = I2CM_Read_Bytes_Ptr;
    i2c_write_p = I2CM_Write_Bytes_Ptr;
#define i2c_start_p 1

#elif defined(__MIKROC_PRO_FOR_DSPIC__)
    i2c_start_p = I2C1_Start;
    i2c_read_p  = I2C1_Read;
    i2c_write_p = I2C1_Write;
    i2c_stop_p  = I2C1_Stop;
    i2c_repeat_p= I2C1_Restart;

#elif defined(__MIKROC_PRO_FOR_PIC__)
    i2c_start_p = I2C1_Start;
    i2c_read_p  = I2C1_Rd;
    i2c_write_p = I2C1_Wr;
    i2c_stop_p  = I2C1_Stop;
    i2c_repeat_p= I2C1_Repeated_Start;

#elif defined(__MIKROC_PRO_FOR_PIC32__)
    i2c_start_p = I2C_Start_Ptr;
    i2c_read_p  = I2C_Read_Ptr;
    i2c_write_p = I2C_Write_Ptr;
    i2c_stop_p  = I2C_Stop_Ptr;

#endif

    if( i2c_start_p == 0 || i2c_read_p == 0 || i2c_write_p == 0 )
        return -1;

    return 0;
}

void fan_i2c_hal_write( uint8_t address, uint16_t num, uint8_t *buff )
{
    uint8_t buffer[MAX_READ_SIZE];
    uint8_t *ptr = buff;

    buffer[0] = address;
    memcpy( &buffer[1], ptr, num );
#if defined(__MIKROC_PRO_FOR_ARM__)
    i2c_start_p();
    i2c_write_p( i2c_address, buffer, num + 1, END_MODE_STOP );

#elif defined(__MIKROC_PRO_FOR_FT90x__)
    I2CM1_Set_Slave_Address( i2c_address );
    i2c_write_p( buffer, num + 1 );

#elif defined(__MIKROC_PRO_FOR_AVR__)   || \
      defined(__MIKROC_PRO_FOR_8051__)  || \
      defined(__MIKROC_PRO_FOR_DSPIC__) || \
      defined(__MIKROC_PRO_FOR_PIC32__) || \
      defined(__MIKROC_PRO_FOR_PIC__)
    i2c_start_p();
    i2c_write_p( i2c_address | WRITE );
    i2c_write_p( address );

    while( num-- )
        i2c_write_p( *( ptr++ ) );

    i2c_stop_p();

#elif defined( __GNUC__)
    printf( "Start\n" );
    printf( "Address: 0x%02x\n", address );
    while( num-- )
        printf( "\tData: 0x%02x\n", *ptr++ );
#endif
}


void fan_i2c_hal_read(  uint8_t address, uint16_t num, uint8_t *buff )
{
    uint8_t buffer[1];
    buffer[0] = address;

#if defined( __MIKROC_PRO_FOR_ARM__ )
    i2c_start_p();              // issue I2C start signal
    i2c_write_p( i2c_address, buffer, 1, END_MODE_RESTART );
    i2c_read_p( i2c_address, buff, num, END_MODE_STOP );

#elif defined(__MIKROC_PRO_FOR_FT90x__)
    I2CM1_Set_Slave_Address( i2c_address );

    i2c_write_p( buffer[0], 1 );
    i2c_read_p( buff, num );

#elif defined(__MIKROC_PRO_FOR_AVR__) || \
      defined(__MIKROC_PRO_FOR_PIC32__)
    i2c_start_p();
    i2c_write_p( i2c_address | WRITE );
    i2c_write_p( buffer[0] );
    i2c_start_p();

    i2c_write_p( i2c_address | READ );

    while( num >= 2 )
    {
        *( buff++ ) = i2c_read_p( 1 );
        num--;
    }

    *buff = i2c_read_p( 0 );
    i2c_stop_p();

#elif defined(__MIKROC_PRO_FOR_PIC__)  || \
      defined(__MIKROC_PRO_FOR_DSPIC__)
      i2c_start_p();
      i2c_write_p( i2c_address | WRITE );
      i2c_write_p( buffer[0] );
      i2c_repeat_p();
      i2c_write_p( i2c_address | READ );

      while( num >= 2 )
      {
          *( buff++ ) = i2c_read_p( 1 );
      }

      *buff = i2c_read_p( 0 );
      i2c_stop_p();

#elif defined( __GNUC__ )
    int input;

    printf( "Read from address 0x%02x\n", buffer[0] );

    while( num-- )
    {
        scanf( "%d", &input );
        *( buff++ ) = input;
    }
#endif
}

/*************** END OF FUNCTIONS ***************************************************************************/
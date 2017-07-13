/*

    __S7X10G_Hal.c

    Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

------------------------------------------------------------------------------*/

/**
@file           __S7X10G_Hal.c
@addtogroup     S7X10G_HAL
@{
*/

#include "__S7X10G_Hal.h"

/*----------------------------------------------------------------- SPI TYPES */
#if defined( __MIKROC_PRO_FOR_ARM__ )
static void ( *fpWriteSPI )( unsigned int dataOut );

#elif defined( __MIKROC_PRO_FOR_AVR__ )
static void ( *fpWriteSPI )( unsigned char dataOut );

#elif defined( __MIKROC_PRO_FOR_PIC__ )
static void ( *fpWriteSPI )( unsigned char dataOut );

#elif defined( __MIKROC_PRO_FOR_PIC32__ )
static void ( *fpWriteSPI )( unsigned long dataOut );

#elif defined( __MIKROC_PRO_FOR_DSPIC__ )
static void ( *fpWriteSPI )( unsigned int dataOut );

#elif defined( __MIKROC_PRO_FOR_8051__ )

#elif defined( __MIKROC_PRO_FOR_FT90x__ )
static void( *fpWriteSPI )( unsigned char dataOut );
#elif defined ( __GNUC__ )

#define fpWriteSPI

#endif

#if defined(__MIKROC_PRO_FOR_ARM__)   || \
    defined(__MIKROC_PRO_FOR_AVR__)   || \
    defined(__MIKROC_PRO_FOR_8051__)  || \
    defined(__MIKROC_PRO_FOR_FT90x__)  || \
    defined(__MIKROC_PRO_FOR_DSPIC__) || \
    defined(__MIKROC_PRO_FOR_PIC32__) || \
    defined(__MIKROC_PRO_FOR_PIC__)
    
// Pin Definitions
extern sfr sbit S7X10G_CS;
extern sfr sbit S7X10G_RST;
extern sfr sbit S7X10G_ROW_RST;
extern sfr sbit S7X10G_ROW_CLK;

#elif defined(__GNUC__)
// SPI bus variables
extern uint8_t bits;
extern uint32_t speed;
extern uint16_t delay;
extern char *spiFileDescriptor;

#endif

/*--------------------------------------------- PRIVATE FUNCTION DECLARATIONS */

static void latch( void );
static void rowReset( void );
static void rowClock( void );
static void halReset( void );

#if defined( __GNUC__ )
static void transfer( int fd, uint8_t const * tx,
                      uint8_t const *rx, size_t len );
const char *byteToBinary( int x );
#endif

/*---------------------------------------------- PRIVATE FUNCTION DEFINITIONS */

static void latch()
{
#if __GNUC__

#else
    S7X10G_CS = 0;
    Delay_us( 1 );
    S7X10G_CS = 1;
    #if defined (__MIKROC_PRO_FOR_8051__ )
    Delay_ms( 1 );
    #else
    Delay_ms( 1 );
    #endif
#endif
}

static void rowReset()
{
#if __GNUC__

#else
    S7X10G_ROW_RST = 1;
    Delay_us( 1 );
    S7X10G_ROW_RST = 0;
#endif
}

static void rowClock()
{
#if __GNUC__

#else
    S7X10G_ROW_CLK = 1;
    Delay_us( 1 );
    S7X10G_ROW_CLK = 0;
#endif
}

static void halReset()
{
#if __GNUC__

#else
    S7X10G_RST = 0;
    Delay_us( 1 );
    S7X10G_RST = 1;
#endif
}

/*---------------------------------------------------------- PUBLIC FUNCTIONS */

int HAL_spiInit()
{
#if defined( __MIKROC_PRO_FOR_ARM__ )   || \
    defined( __MIKROC_PRO_FOR_AVR__ )   || \
    defined( __MIKROC_PRO_FOR_PIC__ )   || \
    defined( __MIKROC_PRO_FOR_PIC32__ ) || \
    defined( __MIKROC_PRO_FOR_DSPIC__ ) || \
    defined( __MIKROC_PRO_FOR_8051__ )
        fpWriteSPI = SPI_Wr_Ptr;
#elif defined( __MIKROC_PRO_FOR_FT90x__ )
        fpWriteSPI = SPIM_Wr_Ptr;
#endif
    if( fpWriteSPI == 0 )
        return -1;

    halReset();

    return 0;
}

void HAL_spiReset()
{
    halReset();
}

void HAL_spiWrite( uint8_t *buff )
{
#if defined( __GNUC__ )
       
#else
    uint8_t *ptr = buff;
    int i;

    halReset();
    rowReset();

    for( i = 0; i < 7; i++ )
    {
        fpWriteSPI( *( ptr++ ) );
        fpWriteSPI( *( ptr++ ) );
        latch();
        rowClock();
    }

#endif
    return;
}

///@}
/*------------------------------------------------------------------------------

  __S7X10G_Hal.c

  Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

    This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.

------------------------------------------------------------------------------*/

/*

    __S7X10G_Driver.c

    Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

------------------------------------------------------------------------------*/

/**
@file           __S7X10G_Driver.c
@addtogroup     S7X10G_DRIVER
@{
------------------------------------------------------------------------------*/

#include <string.h>
#include <stdbool.h>
#include "__S7X10G_Driver.h"
#include "__S7X10G_Hal.h"
#include "7x5font.h"

/*----------------------------------------------------------------- VARIABLES */

static uint8_t frame[7][2];
static uint8_t textFrame[7][40];
static uint8_t textLength;

static bool scroll;
/**
 * Number of ticks for controlling scroll speed.
 */
volatile uint16_t timerTick;
static T_S7X10G_speed scrollSpeed;

/*--------------------------------------------- PRIVATE FUNCTION DECLARATIONS */

static void shiftFrame( void );

/*---------------------------------------------- PRIVATE FUNCTION DEFINITIONS */

static void shiftFrame()
{
    /*
    1. Shift right 1 from index 1
    2. Capture shifted bit from index 1
    3. Mask 0x40 from index 0 and or captured value
    4. Shift index 0 1
    */
    static uint16_t position = 0;
    static uint8_t character = 0;
    uint8_t carry;
    int row, col;

    for( row = 0; row < 7; row++ )
    {
        for( col = 1; col > -1; col-- )
        {
            frame[row][col] >>= 1;           // Pop the bit off

            if( col == 1 )
            {
                carry = frame[row][0];
                carry &= 0x01;
                carry <<= 4;
            }
            else
            {
                int tmp = !( character % 2 ) ? character + 3 : character + 1;
                carry = textFrame[row][tmp];
                carry &= ( 1 << position );
                carry <<= ( 4 - position );
            }

            frame[row][col] |= carry;
        }
    }

    position++;

    if( position > 4 )
    {
        position = 0;
        character++;

        if( character > textLength )
        {
            for( row = 0; row < 7; row++ )
            {
                for( col = 0; col < 2; col++ )
                {
                    frame[row][col] = textFrame[row][col];
                }
            }
            character = 0;
            scroll = false;
        }
    }
}

/*---------------------------------------------------------- PUBLIC FUNCTIONS */

void S7X10G_init()
{
     HAL_spiInit();
}

bool S7X10G_refreshDisplay()
{
     if( scroll )
    {
        switch( scrollSpeed )
        {
        case S7X10G_SPEED_SLOW:
            if( timerTick > 7 )
            {
                shiftFrame();
                timerTick = 0;
            }
            break;
        case S7X10G_SPEED_MED:
            if( timerTick > 5 )
            {
                shiftFrame();
                timerTick = 0;
            }
            break;
        case S7X10G_SPEED_FAST:
            if( timerTick > 1 )
            {
                shiftFrame();
                timerTick = 0;
            }
            break;
        }

        HAL_spiWrite( frame );
        return scroll;
    } else {
        HAL_spiWrite( frame );
        return true;
    }
}

void S7X10G_clearDisplay()
{
    memset( frame, 0, sizeof( frame ) );
}

void S7X10G_drawPixel( uint8_t row, uint8_t col )
{
    if( row > 7 || col > 10 || row == 0 || col == 0 )
        return;

    if( col < 6 )
        frame[ row - 1 ][ 1 ] |= 0x01 << ( col - 1 );
    else
        frame[ row - 1 ][ 0 ] |= 0x01 << ( col - 6 );
}

void S7X10G_drawText( char* txt )
{
    char *ptext = txt;
    uint8_t const *pfont = font;
    int i, j, charCount;
    textLength = strlen( txt );

    if( textLength > 40 )
        textLength = 40;

    memset( textFrame, 0, sizeof( textFrame ) );

    for( charCount = 0; charCount < textLength; charCount++ )
    {
        pfont = &font[ *( ptext++ ) * 8 ];

        if( !( charCount % 2 ) ) {
            for( i = 0; i < 7; i++ )
                textFrame[i][ ( charCount + 1 ) ] = *( pfont++ );
        } else {
            for( i = 0; i < 7; i++ )
                textFrame[i][ ( charCount - 1 ) ] = *( pfont++ );
        }
    }

    for( i = 0; i < 7; i++ )
        for( j = 0; j < 2; j++ )
            frame[i][j] = textFrame[i][j];
}


void S7X10G_drawNumber( uint8_t num )
{
    uint8_t const *pfont = font;
    int i;

    if( num > 99 )
        return;

    if( num < 10 )
    {
        pfont = &font[( num + 48 ) * 8 ];

        for( i = 0; i < 7; i++ )
            frame[i][0] = *( pfont++ );
    } else {
        int tmpNum = num / 10;
        pfont = &font[( tmpNum + 48 ) * 8 ];

        for( i = 0; i < 7; i++ )
            frame[i][1] = *( pfont++ );

        tmpNum = num % 10;
        pfont = &font[( tmpNum + 48 ) * 8 ];

        for( i = 0; i < 7; i++ )
            frame[i][0] = *( pfont++ );
    }
}

void S7X10G_scrollEnable( T_S7X10G_speed speed )
{
    scroll = true;
    scrollSpeed = speed;
    timerTick = 0;
}

void S7X10G_scrollDisable()
{
    scroll = false;
}

void S7X10G_tick()
{
    timerTick++;
}

///@}
/*------------------------------------------------------------------------------

  __S7X10G_Driver.c

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

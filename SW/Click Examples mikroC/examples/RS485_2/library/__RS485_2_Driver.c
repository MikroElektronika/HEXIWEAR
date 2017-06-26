/*

    __CLICKNAME_Driver.h

    Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

--------------------------------------------------------------------------------

    Version : 0.0.1

    Revision Log :

 - 0.0.1 (Sep/2016) Module created                   SW_ENG

    To Do List :

 -

*******************************************************************************/

#include "__RS485_2_Driver.h"

extern sfr sbit _RS485_2_RE_PIN;
extern sfr sbit _RS485_2_DE_PIN;

/*----------------------------- UART HAL -------------------------------------*/

static T_RS485_2_UART_Write fpWriteUART;
static T_RS485_2_UART_Tx_Idle fpTxIdle;


/*----------------------------- UART HAL END ---------------------------------*/

/*                 Preprocessors
 ******************************************************************************/
#define RECEIVE_ENABLE (0)
#define RECEIVE_DISABLE (1)

#define TRANSMIT_ENABLE (1)
#define TRANSMIT_DISABLE (0)

/*                Typedefs
 ******************************************************************************/


/*                Variables
 ******************************************************************************/


/*                 Private Function Prototypes
 ******************************************************************************/


/*                 Private Function Definitions
 ******************************************************************************/


/*                Public Function Definitions
 ******************************************************************************/

void RS485_2_driverInit(
    T_RS485_2_UART_Write fpWrite, 
    T_RS485_2_UART_Tx_Idle fpIdle
)
{
    fpWriteUART = fpWrite;
    fpTxIdle = fpIdle;

    // Pins to initial state
    _RS485_2_DE_PIN = TRANSMIT_DISABLE;
    _RS485_2_RE_PIN = RECEIVE_ENABLE;
}

void RS485_2_transmit(uint8_t *pData, uint32_t size)
{
    _RS485_2_RE_PIN = RECEIVE_DISABLE;
    _RS485_2_DE_PIN = TRANSMIT_ENABLE;

    while (size--)
        fpWriteUART(*pData++);

    while (!fpTxIdle()) {}
    
    _RS485_2_DE_PIN = TRANSMIT_DISABLE;
    _RS485_2_RE_PIN = RECEIVE_ENABLE;
}

/*------------------------------------------------------------------------------

  __CLICKNAME_Driver.c

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
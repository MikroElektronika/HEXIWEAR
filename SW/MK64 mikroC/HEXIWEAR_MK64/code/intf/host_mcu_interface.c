// File: host_mcu_interface.c

// Definitions of main functionalities of the MCU interface module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <stddef.h>

#include "OSA.h"

#include "host_mcu_interface.h"
#include "error.h"

#include "HEXIWEAR_info.h"

#include "uart/uart_driver.h"

////////////////////////////////////////////////////////////////////////////////
// Global variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

uart_state_t KW40_UART_State;

////////////////////////////////////////////////////////////////////////////////
// Global function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Initialises comm module and sets necessary objects.
osa_status_t HostInterface_Init()
{
    osa_status_t status = kStatus_OSA_Success;
    
    UART4_Init_Advanced( 230400, _UART_8_BIT_DATA, _UART_NOPARITY,
        _UART_TWO_STOPBITS, &_GPIO_Module_UART4_PE24_25 );
//    UART_DRV_Init( &KW40_UART_State );

    status |= HostInterface_EventsInit();
    status |= HostInterface_TxInit();
    status |= HostInterface_RxInit();
    
    if( status != kStatus_OSA_Success )
    {
        error_catch( 3 );
    }
    
    return kStatus_OSA_Success;
}
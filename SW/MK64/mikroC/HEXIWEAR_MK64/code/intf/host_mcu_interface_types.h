// File: host_mcu_interface_types.h

// Some commonly used types for the MCU interface module.

#ifndef _host_mcu_interface_types_h_
#define _host_mcu_interface_types_h_

////////////////////////////////////////////////////////////////////////////////
// Type definitions.                                                          //
////////////////////////////////////////////////////////////////////////////////

// Rx state-machine enum.
typedef enum
{
    hostInterface_rxState_idle           = 0, // state idle
    hostInterface_rxState_headerReceived = 3, // header received
    hostInterface_rxState_dataWait       = 4, // wait for data
    hostInterface_rxState_trailerWait    = 5  // wait for trailing byte
} hostInterface_rxState_t;

#endif
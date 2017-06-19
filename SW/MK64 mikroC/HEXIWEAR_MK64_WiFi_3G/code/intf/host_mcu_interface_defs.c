// File: host_mcu_interface_defs.c

// Definitions of some commonly used variables in the MCU interface module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "host_mcu_interface_defs.h"

////////////////////////////////////////////////////////////////////////////////
// Global variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Interface task handlers.
task_handler_t hexiwear_intf_TX_handler; // outgoing traffic handler
task_handler_t hexiwear_intf_RX_handler; // incoming traffic handler
task_handler_t hexiwear_intf_OK_handler; // OK packet handler
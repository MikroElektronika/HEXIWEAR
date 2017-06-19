// File: host_mcu_interface_defs.h

// Declarations of some commonly used variables in the MCU interface module.

#ifndef _host_mcu_interface_defs_h_
#define _host_mcu_interface_defs_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "OSA.h"

////////////////////////////////////////////////////////////////////////////////
// Global variable declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

// Interface task handlers.
extern task_handler_t hexiwear_intf_TX_handler; // outgoing traffic handler
extern task_handler_t hexiwear_intf_RX_handler; // incoming traffic handler
extern task_handler_t hexiwear_intf_OK_handler; // OK packet handler

#endif
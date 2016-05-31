/**
 * global interface components
 * Project HEXIWEAR, 2015
 *
 */

#ifndef HG_HOST_MCU_INTERFACE_DEFS
#define HG_HOST_MCU_INTERFACE_DEFS

#include "fsl_os_abstraction.h"

extern task_handler_t
  hexiwear_intf_TX_handler,
  hexiwear_intf_RX_handler,
  hexiwear_intf_OK_handler;

#endif

/**
 * HEXIWEAR global data structrures
 * Project HEXIWEAR, 2015
 */

#ifndef HG_HEXIWEAR_DEFS
#define HG_HEXIWEAR_DEFS

#include "fsl_os_abstraction.h"
#include "fsl_os_abstraction_free_rtos.h"
#include "HEXIWEAR_types.h"

extern task_handler_t
  hexiwear_startup_handler;

hexiwear_version_t
    hexiwear_kw40version;

extern hexiwear_hw_rev_t
	hexiwear_hwRev;

#endif

/**
 * HEXIWEAR global data structrures
 * Project HEXIWEAR, 2015
 */

#include "HEXIWEAR_defs.h"

task_handler_t
  hexiwear_startup_handler;

hexiwear_version_t
    hexiwear_kw40version =
    {
      .ver_patchNumber = 0,
      .ver_minorNumber = 0,
      .ver_majorNumber = 0
    };

hexiwear_hw_rev_t
	hexiwear_hwRev;

// File: gui_pedometer_private.h

// Declarations of resources used in the pedometer gui module.

#ifndef _gui_pedometer_private_h_
#define _gui_pedometer_private_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include "gui_driver.h"

////////////////////////////////////////////////////////////////////////////////
// Macro definitions.                                                         //
////////////////////////////////////////////////////////////////////////////////

#define GUI_PEDOMETER_PRIO ( HEXIWEAR_GUI_PRIO )
#define GUI_PEDOMETER_STACK_SIZE ( 0x400 )

#define GUI_PEDOMETER_STEP_COUNTER_PRIO ( HEXIWEAR_GUI_PRIO )
#define GUI_PEDOMETER_STEP_COUNTER_STACK_SIZE ( 0x400 )

////////////////////////////////////////////////////////////////////////////////
// Global variable declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

extern const uint8_t pedometer_screen_bmp[18438];
extern const uint8_t pedometer_icon_bmp[4806];

extern guiLabel_t gui_pedometer_stepCounter_label;
extern guiLabel_t gui_pedometer_stepText_label;

extern guiLabel_t gui_pedometer_calCounter_label;
extern guiLabel_t gui_pedometer_calText_label;

extern guiImage_t gui_pedometer_icon;

#endif
// File: gui_heartRate_private.h

// Declarations of resources used in the heart rate gui module.

#ifndef _gui_heartRate_private_h_
#define _gui_heartRate_private_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include "gui_driver.h"

////////////////////////////////////////////////////////////////////////////////
// Macro definitions.                                                         //
////////////////////////////////////////////////////////////////////////////////

#define GUI_HEARTRATE_PRIO ( HEXIWEAR_GUI_PRIO )
#define GUI_HEARTRATE_STACK_SIZE ( 0x400 )

#define GUI_HEARTRATE_STEP_COUNTER_PRIO ( HEXIWEAR_GUI_PRIO )
#define GUI_HEARTRATE_STEP_COUNTER_STACK_SIZE ( 0x400 )

////////////////////////////////////////////////////////////////////////////////
// Global variable declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

extern const uint8_t heartRate_screen_bmp[18438];
extern const uint8_t heartRate_icon_bmp[4806];

extern guiLabel_t gui_heartRate_bpmVal_label;
extern guiLabel_t gui_heartRate_bpmText_label;

extern guiImage_t gui_heartRate_icon;

#endif
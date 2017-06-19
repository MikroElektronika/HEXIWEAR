// File: gui_motionControl_private.h

// Declarations of resources used in the motion control gui module.

#ifndef _motionControl_private_h_
#define _motionControl_private_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include "gui_driver.h"

////////////////////////////////////////////////////////////////////////////////
// Global variable declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

extern const uint8_t gui_motionControl_cover_bmp[18438];
extern const uint8_t gui_motionControl_appScreen_bmp[18438];
extern const uint8_t gui_motionControl_acc_bmp[18438];
extern const uint8_t gui_motionControl_gyro_bmp[18438];

extern guiLabel_t gui_motionControl_label;
extern guiLabel_t gui_motionControl_labelX;
extern guiLabel_t gui_motionControl_labelY;
extern guiLabel_t gui_motionControl_labelZ;

#endif
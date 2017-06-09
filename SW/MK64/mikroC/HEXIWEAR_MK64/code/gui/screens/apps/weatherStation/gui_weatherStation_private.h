// File: gui_weatherStation_private.h

// Declarations of resources used in the weather station gui module.

#ifndef _gui_weatherStation_private_h_
#define _gui_weatherStation_private_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include "gui_driver.h"

////////////////////////////////////////////////////////////////////////////////
// Global variable declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

extern const uint8_t gui_weatherStation_cover_bmp[18438];
extern const uint8_t gui_weatherStation_appScreen_bmp[18438];

extern guiLabel_t gui_weatherStation_label;
extern guiLabel_t gui_weatherStation_labelTemp;
extern guiLabel_t gui_weatherStation_labelHum;
extern guiLabel_t gui_weatherStation_labelPress;

#endif
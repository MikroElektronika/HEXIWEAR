/**
 * pedometer GUI private objects
 * Project HEXIWEAR, 2015
 */

#pragma once

#include <stdint.h>
#include "gui_driver.h"

#define GUI_PEDOMETER_PRIO ( HEXIWEAR_GUI_PRIO )
#define GUI_PEDOMETER_STACK_SIZE ( 0x400 )

#define GUI_PEDOMETER_STEP_COUNTER_PRIO ( HEXIWEAR_GUI_PRIO )
#define GUI_PEDOMETER_STEP_COUNTER_STACK_SIZE ( 0x400 )

extern const uint8_t
    pedometer_screen_bmp[18438],
	pedometer_icon_bmp[4806];

extern guiLabel_t
    gui_pedometer_stepCounter_label,
    gui_pedometer_stepText_label;

extern guiLabel_t
	gui_pedometer_calCounter_label,
    gui_pedometer_calText_label;

extern guiImage_t
	gui_pedometer_icon;

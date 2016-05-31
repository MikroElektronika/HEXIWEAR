/**
 * heartRate GUI private objects
 * Project HEXIWEAR, 2015
 */

#pragma once

#include <stdint.h>
#include "gui_driver.h"

#define GUI_HEARTRATE_PRIO ( HEXIWEAR_GUI_PRIO )
#define GUI_HEARTRATE_STACK_SIZE ( 0x400 )

#define GUI_HEARTRATE_STEP_COUNTER_PRIO ( HEXIWEAR_GUI_PRIO )
#define GUI_HEARTRATE_STEP_COUNTER_STACK_SIZE ( 0x400 )

extern const uint8_t
    heartRate_screen_bmp[18438],
	heartRate_icon_bmp[4806];

extern guiLabel_t
	gui_heartRate_bpmVal_label,
	gui_heartRate_bpmText_label;

extern guiImage_t
	gui_heartRate_icon;

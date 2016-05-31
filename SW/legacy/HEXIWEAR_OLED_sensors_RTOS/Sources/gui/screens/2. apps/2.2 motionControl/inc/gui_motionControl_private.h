#pragma once

#include "gui_driver.h"
#include <stdint.h>

extern const uint8_t
    gui_motionControl_cover_bmp[18438],
    gui_motionControl_appScreen_bmp[18438],
	gui_motionControl_acc_bmp[18438],
    gui_motionControl_gyro_bmp[18438];

extern guiLabel_t
    gui_motionControl_label,
    gui_motionControl_labelX,
    gui_motionControl_labelY,
    gui_motionControl_labelZ;

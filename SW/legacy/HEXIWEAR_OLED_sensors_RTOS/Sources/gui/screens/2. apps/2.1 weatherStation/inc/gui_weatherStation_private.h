#pragma once

#include "gui_driver.h"
#include <stdint.h>

extern const uint8_t
    gui_weatherStation_cover_bmp[18438],
    gui_weatherStation_appScreen_bmp[18438];

extern guiLabel_t
    gui_weatherStation_label,
    gui_weatherStation_labelTemp,
    gui_weatherStation_labelHum,
    gui_weatherStation_labelPress;

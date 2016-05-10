/**
 * sensor tag private objects
 * Project HEXIWEAR, 2015
 */

#pragma once

#include "gui_driver.h"
#include <stdint.h>

#define GUI_SENSOR_TAG_STACK_SIZE ( 0x400 )
#define GUI_SENSOR_TAG_PRIO ( HEXIWEAR_GUI_PRIO )

extern const uint8_t
    gui_sensorTag_blank_bmp[18438],
    gui_sensorTag_off_bmp[4806],
    gui_sensorTag_on_bmp[4806];

extern guiImage_t
    gui_sensorTag_icon;

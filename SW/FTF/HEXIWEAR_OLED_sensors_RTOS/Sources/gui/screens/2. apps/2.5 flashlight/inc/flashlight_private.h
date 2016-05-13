#pragma once

#include "gui_driver.h"
#include <stdint.h>

#define FLASHLIGHT_STACK_SIZE ( 0x400 )
#define FLASHLIGHT_PRIO       ( HEXIWEAR_APP_PRIO )

extern guiImage_t
     flashlight_icon;

extern const uint8_t
    flashlight_screen_bmp[18438],
    flashlight_off_bmp[4806],
    flashlight_on_bmp[4806];

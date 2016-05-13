#pragma once

#include "gui_driver.h"

#define RESET_STACK_SIZE ( 0x400 )
#define RESET_PRIO       ( HEXIWEAR_APP_PRIO )

// Resources
extern const uint8_t
  reset_screen_bmp[ OLED_GRAM_SIZE+6 ];


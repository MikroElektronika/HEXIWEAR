#pragma once

#include "gui_driver.h"

// Resources
extern const uint8_t
	bluetooth_icon_white_bmp[ 4806 ],
	bluetooth_icon_blue_bmp[ 4806 ],
    bluetooth_screen_bmp[ OLED_GRAM_SIZE+6 ];

extern guiImage_t
	bluetooth_icon;

// Callbacks
void bluetooth_Init( void *param );
void bluetooth_CreateTasks( void *param );
void bluetooth_DestroyTasks( void *param );

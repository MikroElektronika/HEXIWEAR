#pragma once

#include "gui_driver.h"

// Resources
extern const uint8_t
	haptic_icon_white_bmp[ 4806 ],
	haptic_icon_blue_bmp[ 4806 ],
    haptic_screen_bmp[ OLED_GRAM_SIZE+6 ];

extern guiImage_t
	haptic_icon;

// Callbacks
void haptic_Init( void *param );
void haptic_CreateTasks( void *param );
void haptic_DestroyTasks( void *param );

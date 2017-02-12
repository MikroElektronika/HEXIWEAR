/**
 * \file MultipleChoice_private.h
 * \version 1.00
 */

#pragma once

#include "gui_driver.h"

// Resources
extern const uint8_t MultipleChoice_screen_bmp[ OLED_GRAM_SIZE+6 ];

// Objects
extern guiLabel_t MultipleChoice_label;

// Callbacks
void MultipleChoice_Init( void *param );
void MultipleChoice_DestroyTasks( void *param );
void MultipleChoice_CreateTasks(void* param);

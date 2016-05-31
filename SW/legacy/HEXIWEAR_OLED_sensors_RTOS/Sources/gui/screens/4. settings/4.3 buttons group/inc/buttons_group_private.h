#pragma once

#include "gui_driver.h"

// Resources
extern const uint8_t
  buttons_group_screen_bmp[ OLED_GRAM_SIZE+6 ],
  buttonGroup_rightSelected_bmp[4806],
  buttonGroup_leftSelected_bmp[4806];

// Objects
extern guiImage_t buttonsGroup_img;

// Callbacks
void buttonsGroup_Init( void *param );
void buttonsGroup_CreateTasks( void *param );
void buttonsGroup_DestroyTasks( void *param );

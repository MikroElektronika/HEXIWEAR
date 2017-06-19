// File: buttons_group_private.h

// Declarations of resources used in the buttons group gui module.

#ifndef _buttons_group_private_h_
#define _buttons_group_private_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "gui_driver.h"

////////////////////////////////////////////////////////////////////////////////
// Global variable declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

// Resources
extern const uint8_t buttons_group_screen_bmp[ OLED_GRAM_SIZE + 6 ];
extern const uint8_t   buttonGroup_rightSelected_bmp[4806];
extern const uint8_t buttonGroup_leftSelected_bmp[4806];

// Objects
extern guiImage_t buttonsGroup_img;

////////////////////////////////////////////////////////////////////////////////
// Global function declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

void buttonsGroup_Init( void *param );
void buttonsGroup_CreateTasks( void *param );
void buttonsGroup_DestroyTasks( void *param );

#endif
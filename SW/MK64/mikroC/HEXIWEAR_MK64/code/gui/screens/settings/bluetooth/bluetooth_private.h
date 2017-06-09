// File: bluetooth_private.h

// Declarations of resources in the bluetooth gui module.

#ifndef _bluetooth_private_h_
#define _bluetooth_private_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "gui_driver.h"

////////////////////////////////////////////////////////////////////////////////
// Global variable declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

extern const uint8_t bluetooth_icon_white_bmp[ 4806 ];
extern const uint8_t bluetooth_icon_blue_bmp[ 4806 ];
extern const uint8_t bluetooth_screen_bmp[ OLED_GRAM_SIZE + 6 ];

extern guiImage_t bluetooth_icon;

////////////////////////////////////////////////////////////////////////////////
// Global function declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

void bluetooth_Init( void *param );
void bluetooth_CreateTasks( void *param );
void bluetooth_DestroyTasks( void *param );

#endif
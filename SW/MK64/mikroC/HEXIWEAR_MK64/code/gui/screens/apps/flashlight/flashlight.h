// File: flashlight.h

// Declarations of main functionalities in the flashlight gui module.

#ifndef _flashlight_h_
#define _flashlight_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include <stdbool.h>
#include "gui_driver.h"

////////////////////////////////////////////////////////////////////////////////
// Macro definitions.                                                         //
////////////////////////////////////////////////////////////////////////////////

#define RED_LED   PDO8_PTC_PDOR_bit
#define GREEN_LED PDO0_PTD_PDOR_bit
#define BLUE_LED  PDO9_PTC_PDOR_bit

#define RED_LED_ON()   RED_LED   = 0
#define GREEN_LED_ON() GREEN_LED = 0
#define BLUE_LED_ON()  BLUE_LED  = 0

#define RED_LED_OFF()   RED_LED   = 1
#define GREEN_LED_OFF() GREEN_LED = 1
#define BLUE_LED_OFF()  BLUE_LED  = 1

#define RED_LED_TOGGLE()   RED_LED   = !RED_LED
#define GREEN_LED_TOGGLE() GREEN_LED = !GREEN_LED
#define BLUE_LED_TOGGLE()  BLUE_LED  = !BLUE_LED

#define FLASH_Toggle() RED_LED_TOGGLE(); GREEN_LED_TOGGLE(); BLUE_LED_TOGGLE()
#define FLASH_SetON()  RED_LED_ON(); GREEN_LED_ON(); BLUE_LED_ON()
#define FLASH_SetOFF() RED_LED_OFF(); GREEN_LED_OFF(); BLUE_LED_OFF()

////////////////////////////////////////////////////////////////////////////////
// Global variable declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

extern guiScreen_t flashlightScreen;

extern task_handler_t flashlight_taskHandler;

////////////////////////////////////////////////////////////////////////////////
// Global function declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

void flashlight_Init( void* param );
void flashlight_CreateTasks( void* param );
void flashlight_DestroyTasks( void* param );

bool flashlight_isFlashlightOn();

#endif
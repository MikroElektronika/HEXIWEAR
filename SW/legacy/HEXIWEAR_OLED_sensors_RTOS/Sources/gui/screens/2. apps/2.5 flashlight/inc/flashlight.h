#pragma once

#include "gui_driver.h"
#include <stdbool.h>

extern guiScreen_t
	flashlightScreen;

extern task_handler_t
	flashlight_taskHandler;

#define RED_LED_ON()   GPIO_DRV_ClearPinOutput( RED_LED );
#define GREEN_LED_ON() GPIO_DRV_ClearPinOutput( GREEN_LED );
#define BLUE_LED_ON()  GPIO_DRV_ClearPinOutput( BLUE_LED );

#define RED_LED_OFF()   GPIO_DRV_SetPinOutput( RED_LED );
#define GREEN_LED_OFF() GPIO_DRV_SetPinOutput( GREEN_LED );
#define BLUE_LED_OFF()  GPIO_DRV_SetPinOutput( BLUE_LED );

#define RED_LED_TOGGLE()   GPIO_DRV_TogglePinOutput( RED_LED );
#define GREEN_LED_TOGGLE() GPIO_DRV_TogglePinOutput( GREEN_LED );
#define BLUE_LED_TOGGLE()  GPIO_DRV_TogglePinOutput( BLUE_LED );

#define FLASH_Toggle() RED_LED_TOGGLE(); GREEN_LED_TOGGLE(); BLUE_LED_TOGGLE()
#define FLASH_SetON() RED_LED_ON(); GREEN_LED_ON(); BLUE_LED_ON()
#define FLASH_SetOFF() RED_LED_OFF(); GREEN_LED_OFF(); BLUE_LED_OFF()

/**
 * [flashlight_Init description]
 * @param param [description]
 */
void flashlight_Init( void* param );
/**
 * [flashlight_CreateTasks description]
 * @param param [description]
 */
void flashlight_CreateTasks( void* param );
/**
 * [flashlight_DestroyTasks description]
 * @param param [description]
 */
void flashlight_DestroyTasks( void* param );

/**
 * check if the app is active
 */
bool flashlight_isFlashlightOn();

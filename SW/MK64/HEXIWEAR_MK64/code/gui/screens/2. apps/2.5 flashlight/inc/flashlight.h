/**
 * \file flashlight.h
 * \version 1.00
 * \brief this file contains flashlight app related public objects' declarations and constants
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * Neither the name of NXP, nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * visit: http://www.mikroe.com and http://www.nxp.com
 *
 * get support at: http://www.mikroe.com/forum and https://community.nxp.com
 *
 * Project HEXIWEAR, 2015
 */

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

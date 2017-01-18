/*
 * LEDs.h
 *
 *  Created on: 08.11.2016
 *      Author: Patrick
 */

#ifndef CODE_GUI_SCREENS_7__LEDS_INC_LEDS_H_
#define CODE_GUI_SCREENS_7__LEDS_INC_LEDS_H_



#endif /* CODE_GUI_SCREENS_7__LEDS_INC_LEDS_H_ */

#pragma once

#include "gui_driver.h"

extern task_handler_t
	control_taskHandler;

extern guiScreen_t
	control_Screen;

void control_Init(void* param);

void control_CreateTasks(void* param);

void control_DestroyTasks(void* param);

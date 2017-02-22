#pragma once

#include "gui_driver.h"
#include <stdbool.h>

extern guiScreen_t
	relay_click_Screen;

/**
 * [relay_click_Init description]
 * @param param [description]
 */
void relay_click_Init( void* param );
/**
 * [relay_click_CreateTasks description]
 * @param param [description]
 */
void relay_click_CreateTasks( void* param );
/**
 * [relay_click_DestroyTasks description]
 * @param param [description]
 */
void relay_click_DestroyTasks( void* param );

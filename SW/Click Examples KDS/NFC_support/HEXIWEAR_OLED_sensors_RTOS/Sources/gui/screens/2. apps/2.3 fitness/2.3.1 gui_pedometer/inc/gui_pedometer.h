/**
 * pedometer public objects
 * Project HEXIWEAR, 2015
 */

#pragma once

#include "gui_driver.h"

typedef enum
{
    GUI_PEDOMETER_STATUS_SUCCESS,
    GUI_PEDOMETER_STATUS_ERROR

} gui_pedometer_status_t;

extern guiScreen_t
	pedometerScreen;

 /**
  * [gui_pedometer_Init description]
  * @param param [description]
  */
void gui_pedometer_Init( void* param );

/**
 * [gui_pedometer_CreateTasks description]
 * @param param [description]
 */
void gui_pedometer_CreateTasks( void* param );

/**
 * [gui_pedometer_DestroyTasks description]
 * @param param [description]
 */
void gui_pedometer_DestroyTasks( void* param );

/**
 * [gui_pedometer_QueueMsgPut description]
 * @param  packet [description]
 * @return        [description]
 */
gui_pedometer_status_t gui_pedometer_QueueMsgPut( uint32_t* packet );

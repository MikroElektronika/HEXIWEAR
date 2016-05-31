/**
 * heart-rate public objects
 * Project HEXIWEAR, 2015
 */

#pragma once

#include "gui_driver.h"

typedef enum
{
    GUI_HEART_RATE_STATUS_SUCCESS,
    GUI_HEART_RATE_STATUS_ERROR

} gui_heartRate_status_t;

extern guiScreen_t
	heartRateScreen;

 /**
  * [gui_heartRate_Init description]
  * @param param [description]
  */
void gui_heartRate_Init( void* param );

/**
 * [gui_heartRate_CreateTasks description]
 * @param param [description]
 */
void gui_heartRate_CreateTasks( void* param );

/**
 * [gui_heartRate_DestroyTasks description]
 * @param param [description]
 */
void gui_heartRate_DestroyTasks( void* param );

/**
 * [gui_heartRate_QueueMsgPut description]
 * @param  packet [description]
 * @return        [description]
 */
gui_heartRate_status_t gui_heartRate_QueueMsgPut( uint32_t* packet );

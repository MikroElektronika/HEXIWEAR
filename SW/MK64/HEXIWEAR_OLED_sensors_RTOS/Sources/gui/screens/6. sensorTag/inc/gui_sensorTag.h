/**
 * sensor tag global objects
 * Project HEXIWEAR, 2015
 */

#pragma once

#include "gui_driver.h"

extern guiScreen_t
  gui_sensorTag_screen;


/**
 * [sensorTag_Init description]
 * @param param [description]
 */
void gui_sensorTag_Init( void* param );

/**
 * [sensorTag_CreateTasks description]
 * @param param [description]
 */
void gui_sensorTag_CreateTasks( void* param );

/**
 * [sensorTag_DestroyTasks description]
 * @param param [description]
 */
void gui_sensorTag_DestroyTasks( void* param );

/**
 * return task state
 */
bool gui_sensorTag_IsActive();

/**
 * [gui_sensorTag_TurnOFF description]
 */
void gui_sensorTag_TurnOFF();

/**
 * [gui_sensorTag_TurnON description]
 */
void gui_sensorTag_TurnON();

/**
 * check if sensor tag should be enabled at startup
 */
void gui_sensorTag_CheckAtStartup();

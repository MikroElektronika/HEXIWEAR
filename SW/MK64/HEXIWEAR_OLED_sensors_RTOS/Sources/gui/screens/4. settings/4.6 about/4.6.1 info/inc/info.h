#pragma once

#include "gui_driver.h"

#define INFO_STACK_SIZE ( 0x400 )
#define INFO_PRIO ( HEXIWEAR_APP_PRIO )

// screens
extern guiScreen_t infoScreen;

/**
  * [about_Init description]
  * @param param [description]
  */
void info_Init( void* param );
/**
 * [about_CreateTasks description]
 * @param param [description]
 */
void info_CreateTasks( void* param );
/**
 * [about_DestroyTasks description]
 * @param param [description]
 */
void info_DestroyTasks( void* param );

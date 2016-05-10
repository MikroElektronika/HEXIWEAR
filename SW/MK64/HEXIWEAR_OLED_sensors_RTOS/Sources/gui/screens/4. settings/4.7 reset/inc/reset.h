#pragma once

#include "gui_driver.h"

// callbacks
void reset_Init( void* param );
void reset_CreateTasks( void* param );
void reset_DestroyTasks( void* param );

// screens
extern guiScreen_t resetScreen;

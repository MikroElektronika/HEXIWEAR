/*
 * watch_set.h
 *
 *  Created on: Aug 30, 2016
 *      Author: denes
 */

#pragma once

#include "gui_driver.h"

// callbacks
void watchSet_Init( void* param );
void watchSet_CreateTasks( void* param );
void watchSet_DestroyTasks( void* param );

// screens
extern guiScreen_t watchSetScreen;
extern guiScreen_t watchSetScreen_mainScreen;

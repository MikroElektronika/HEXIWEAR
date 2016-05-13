#pragma once

#include "gui_driver.h"

#define GUI_MOTION_CONTROL_STACK_SIZE ( 0x500 )
#define GUI_MOTION_CONTROL_PRIO       ( HEXIWEAR_GUI_PRIO )

extern guiScreen_t
	gui_motionControl_coverScreen,
    gui_motionControl_accScreen,
    gui_motionControl_gyroScreen;

void gui_motionControl_Init();
void gui_motionControl_CreateTasks();
void gui_motionControl_DestroyTasks();

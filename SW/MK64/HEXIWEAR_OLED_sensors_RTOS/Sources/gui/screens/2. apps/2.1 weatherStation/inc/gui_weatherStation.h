#pragma once

#include "gui_driver.h"

#define GUI_WEATHER_STATION_STACK_SIZE ( 0x500 )
#define GUI_WEATHER_STATION_PRIO       ( HEXIWEAR_GUI_PRIO )

extern guiScreen_t
    gui_weatherStation_coverScreen;

void gui_weatherStation_Init();
void gui_weatherStation_CreateTasks();
void gui_weatherStation_DestroyTasks();

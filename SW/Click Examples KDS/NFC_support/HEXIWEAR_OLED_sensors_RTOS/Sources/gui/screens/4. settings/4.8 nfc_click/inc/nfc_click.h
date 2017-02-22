#pragma once

#include "gui_driver.h"
#include <stdbool.h>

extern guiScreen_t nfc_click_Screen;
extern guiImage_t nfc_click_OFF_icon, nfc_click_ON_icon;

/**
 * [relay_click_Init description]
 * @param param [description]
 */
void nfc_click_Init( void* param );
/**
 * [relay_click_CreateTasks description]
 * @param param [description]
 */
void nfc_click_CreateTasks( void* param );
/**
 * [relay_click_DestroyTasks description]
 * @param param [description]
 */
void nfc_click_DestroyTasks( void* param );

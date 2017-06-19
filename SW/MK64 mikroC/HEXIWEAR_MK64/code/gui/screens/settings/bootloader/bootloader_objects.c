// File: bootloader_objects.c

// Definitions of objects used in the bootloader gui module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "gui_driver.h"
#include "screens_common.h"
#include "bootloader.h"
#include "bootloader_private.h"

////////////////////////////////////////////////////////////////////////////////
// Global variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// screens

static guiScreen_t bootloaderMainScreen =
{
    NULL,                    // .navigation.up
    NULL,                    // .navigation.down
    &bootloaderCoverScreen,  // .navigation.left
    NULL,                    // .navigation.right

    otap_mainScreen_bmp,     // .image

    bootloader_Init,         // .initFunction
    bootloader_CreateTasks,  // .createTaskFunction
    bootloader_DestroyTasks  // .destroyTaskFunction
};

guiScreen_t bootloaderCoverScreen =
{
    &bluetoothScreen,      // .navigation.up
    &buttonsGroupScreen,   // .navigation.down
    &settingsScreen,       // .navigation.left
    &bootloaderMainScreen, // .navigation.right

    otap_coverScreen_bmp,  // .image

    NULL,                  // .initFunction
    NULL,                  // .createTaskFunction
    NULL                   // .destroyTaskFunction
};

// labels

guiLabel_t bootloader_labelLoad =
{
    25,                        // .dynamicArea.xCrd
    6,                         // .dynamicArea.yCrd
    50,                        // .dynamicArea.width
    20,                        // .dynamicArea.height
    0,                         // .dynamicArea.areaBuffer

    guiFont_Tahoma_10_Regular, // .textProperties.font
    GUI_COLOR_WHITE,           // .textProperties.fontColor
    OLED_TEXT_ALIGN_CENTER,    // .textProperties.alignParam
    NULL,                      // .textProperties.background

    NULL,                      // .caption
    8                          // .captionLength
};


// images

guiImage_t bootloader_selectMK64 =
{
    24,                   // .dynamicArea.xCrd
    23,                   // .dynamicArea.yCrd
    0,                    // .dynamicArea.width
    0,                    // .dynamicArea.height
    0,                    // .dynamicArea.areaBuffer

    otap_select_mk64_bmp  // .img
};

guiImage_t bootloader_selectKW40 =
{
    24,                   // .dynamicArea.xCrd
    23,                   // .dynamicArea.yCrd
    0,                    // .dynamicArea.width
    0,                    // .dynamicArea.height
    0,                    // .dynamicArea.areaBuffer

    otap_select_kw40_bmp  // .img
};

guiImage_t bootloader_loadImg_white =
{
    20,                       // .dynamicArea.xCrd
    20,                       // .dynamicArea.yCrd
    0,                        // .dynamicArea.width
    0,                        // .dynamicArea.height
    0,                        // .dynamicArea.areaBuffer

    bootloader_loadWhite_bmp  // .img
};

guiImage_t bootloader_loadImg_blue =
{
    20,                      // .dynamicArea.xCrd
    20,                      // .dynamicArea.yCrd
    0,                       // .dynamicArea.width
    0,                       // .dynamicArea.height
    0,                       // .dynamicArea.areaBuffer

    bootloader_loadBlue_bmp  // .img
};

guiImage_t bootloader_success =
{
    0,                      // .dynamicArea.xCrd
    0,                      // .dynamicArea.yCrd
    0,                      // .dynamicArea.width
    0,                      // .dynamicArea.height
    0,                      // .dynamicArea.areaBuffer

    bootloader_success_bmp  // .img
};

guiImage_t bootloader_failure =
{
    0,                      // .dynamicArea.xCrd
    0,                      // .dynamicArea.yCrd
    0,                      // .dynamicArea.width
    0,                      // .dynamicArea.height
    0,                      // .dynamicArea.areaBuffer

    bootloader_failure_bmp  // .img
};
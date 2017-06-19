// File: watch_objects.c

// Definitions of objects used in the watch gui module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "gui_driver.h"
#include "screens_common.h"
#include "watch_private.h"

////////////////////////////////////////////////////////////////////////////////
// Global variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Definition of watch screen.
guiScreen_t watchScreen =
{
    NULL,               // .navigation.up
    NULL,               // .navigation.down
    NULL,               // .navigation.left
    &appsScreen,        // .navigation.right

    NULL,               // .image

    watch_Init,         // .initFunction
    watch_CreateTasks,  // .createTaskFunction
    watch_DestroyTasks  // .destroyTaskFunction
};

// definitions of screen objects

// battery image GUI object
guiImage_t watch_imgBattery =
{
    74,            // .dynamicArea.xCrd
    0,             // .dynamicArea.yCrd
    0,             // .dynamicArea.width
    0,             // .dynamicArea.height
    NULL,          // .dynamicArea.areaBuffer
    battery_0_bmp  // .img
};


// notification sms image GUI object
guiImage_t watch_imgSms =
{
    21,           // .dynamicArea.xCrd
    4,            // .dynamicArea.yCrd
    0,            // .dynamicArea.width
    0,            // .dynamicArea.height
    NULL,         // .dynamicArea.areaBuffer
    NULL          // .img
};

// notification mail image GUI object
guiImage_t watch_imgMail =
{
    3,            // .dynamicArea.xCrd
    6,            // .dynamicArea.yCrd
    0,            // .dynamicArea.width
    0,            // .dynamicArea.height
    NULL,         // .dynamicArea.areaBuffer
    NULL          // .img
};

// notification call image GUI object
guiImage_t watch_imgCall =
{
    37,           // .dynamicArea.xCrd
    3,            // .dynamicArea.yCrd
    0,            // .dynamicArea.width
    0,            // .dynamicArea.height
    NULL,         // .dynamicArea.areaBuffer
    NULL          // .img
};

// bluetooth link GUI object
guiImage_t watch_imgBluetoothLogo =
{
    36,                            // .dynamicArea.xCrd
    72,                            // .dynamicArea.yCrd
    0,                             // .dynamicArea.width
    0,                             // .dynamicArea.height
    NULL,                          // .dynamicArea.areaBuffer
    watch_bluetooth_logo_white_bmp // .img
};

// bluetooth link GUI object
guiImage_t watch_imgWiFiLogo =
{
    6,                            // .dynamicArea.xCrd
    72,                            // .dynamicArea.yCrd
    0,                             // .dynamicArea.width
    0,                             // .dynamicArea.height
    NULL,                          // .dynamicArea.areaBuffer
    wifi_logo_white_bmp // .img
};

// bluetooth link GUI object
guiImage_t watch_img3gLogo =
{
    6,                            // .dynamicArea.xCrd
    72,                            // .dynamicArea.yCrd
    0,                             // .dynamicArea.width
    0,                             // .dynamicArea.height
    NULL,                          // .dynamicArea.areaBuffer
    _3g_logo_white_bmp // .img
};

// bluetooth link GUI object
guiImage_t watch_blackImg =
{
    31,                            // .dynamicArea.xCrd
    72,                            // .dynamicArea.yCrd
    0,                             // .dynamicArea.width
    0,                             // .dynamicArea.height
    NULL,                          // .dynamicArea.areaBuffer
    black_screen_bmp // .img
};

// temperature unit GUI object
guiImage_t watch_imgTempUnit =
{
    19,                            // .dynamicArea.xCrd
    81,                            // .dynamicArea.yCrd
    0,                             // .dynamicArea.width
    0,                             // .dynamicArea.height
    NULL,                          // .dynamicArea.areaBuffer
    celsius_bmp                    // .img
};

// time GUI object
guiLabel_t watch_labelTime =
{
    0,                         // .dynamicArea.xCrd
    38,                        // .dynamicArea.yCrd
    96,                        // .dynamicArea.width
    32,                        // .dynamicArea.height
    NULL,                      // .dynamicArea.areaBuffer

    guiFont_Tahoma_18_Regular, // .textProperties.font
    GUI_COLOR_WHITE,           // .textProperties.fontColor
    OLED_TEXT_ALIGN_CENTER,    // .textProperties.alignParam
    NULL,                      // .textProperties.background
    
    NULL,                      // .caption
    15                         // .captionLength
};

// date GUI object
guiLabel_t watch_labelDate =
{
    0,                         // .dynamicArea.xCrd
    23,                        // .dynamicArea.yCrd
    96,                        // .dynamicArea.width
    15,                        // .dynamicArea.height
    NULL,                      // .dynamicArea.areaBuffer

    guiFont_Tahoma_8_Regular,  // .textProperties.font
    GUI_COLOR_GRAY,            // .textProperties.fontColor
    OLED_TEXT_ALIGN_CENTER,    // .textProperties.alignParam
    NULL,                      // .textProperties.background

    NULL,                      // .caption
    12                         // .captionLength
};

// temperature GUI object
guiLabel_t watch_labelTemp =
{
    0,                         // .dynamicArea.xCrd
    80,                        // .dynamicArea.yCrd
    19,                        // .dynamicArea.width
    15,                        // .dynamicArea.height
    NULL,                      // .dynamicArea.areaBuffer

    guiFont_Tahoma_8_Regular,  // .textProperties.font
    GUI_COLOR_WHITE,           // .textProperties.fontColor
    OLED_TEXT_ALIGN_RIGHT,     // .textProperties.alignParam
    NULL,                      // .textProperties.background

    NULL,                      // .caption
    6                          // .captionLength
};

// menu label GUI object
guiLabel_t watch_labelEnter =
{
    65,                        // .dynamicArea.xCrd
    80,                        // .dynamicArea.yCrd
    30,                        // .dynamicArea.width
    15,                        // .dynamicArea.height
    NULL,                      // .dynamicArea.areaBuffer

    guiFont_Tahoma_8_Regular,  // .textProperties.font
    GUI_COLOR_WHITE,           // .textProperties.fontColor
    OLED_TEXT_ALIGN_LEFT,      // .textProperties.alignParam
    NULL,                      // .textProperties.background

    NULL,                      // .caption
    6                          // .captionLength
};
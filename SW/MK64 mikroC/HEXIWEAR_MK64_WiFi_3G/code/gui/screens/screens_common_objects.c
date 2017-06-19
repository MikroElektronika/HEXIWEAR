// File: screens_common_objects.c

// Common objects for the screen gui modules.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "screens_common.h"

////////////////////////////////////////////////////////////////////////////////
// Global variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

guiLabel_t screen_labelEnter =
{
    53,                       // .dynamicArea.xCrd
    81,                       // .dynamicArea.yCrd
    43,                       // .dynamicArea.width
    15,                       // .dynamicArea.height
    guiFont_Tahoma_8_Regular, // .textProperties.font
    GUI_COLOR_WHITE,          // .textProperties.fontColor
    OLED_TEXT_ALIGN_CENTER,   // .textProperties.alignParam
    NULL,                     // .textProperties.background
    NULL,                     // .caption
    8                         // .captionLength
};



// Back label

guiLabel_t screen_labelBack =
{
    0,                        // .dynamicArea.xCrd
    81,                       // .dynamicArea.yCrd
    43,                       // .dynamicArea.width
    15,                       // .dynamicArea.height
    guiFont_Tahoma_8_Regular, // .textProperties.font
    GUI_COLOR_WHITE,          // .textProperties.fontColor
    OLED_TEXT_ALIGN_CENTER,   // .textProperties.alignParam
    NULL,                     // .textProperties.background
    NULL,                     // .caption
    8                         // .captionLength
};

guiScreen_t splashScreen = {
    NULL,              // .navigation.up
    NULL,              // .navigation.down
    NULL,              // .navigation.left
    NULL,              // .navigation.right
    hexiwear_logo_bmp, // .image
    NULL,              // .initFunction
    NULL,              // .createTaskFunction
    NULL               // .destroyTaskFunction
};

//

guiImage_t screen_buttonStartDisabled =
{
    50,                       // .dynamicArea.xCrd
    81,                       // .dynamicArea.yCrd
    0,                        // .dynamicArea.width
    0,                        // .dynamicArea.height
    NULL,                     // .dynamicArea.areaBuffer
    button_start_disabled_bmp // .img
};

guiImage_t screen_buttonStart =
{
    50,              // .dynamicArea.xCrd
    81,              // .dynamicArea.yCrd
    0,               // .dynamicArea.width
    0,               // .dynamicArea.height
    NULL,            // .dynamicArea.areaBuffer
    button_start_bmp // .img
};

guiImage_t screen_buttonStop =
{
    50,              // .dynamicArea.xCrd
    81,              // .dynamicArea.yCrd
    0,               // .dynamicArea.width
    0,               // .dynamicArea.height
    NULL,            // .dynamicArea.areaBuffer
    button_stop_bmp  // .img
};

guiImage_t screen_buttonReset =
{
    50,               // .dynamicArea.xCrd
    81,               // .dynamicArea.yCrd
    0,               // .dynamicArea.width
    0,               // .dynamicArea.height
    NULL,            // .dynamicArea.areaBuffer
    button_reset_bmp  // .img
};

guiImage_t screen_buttonBack =
{
    0,               // .dynamicArea.xCrd
    81,              // .dynamicArea.yCrd
    0,               // .dynamicArea.width
    0,               // .dynamicArea.height
    NULL,            // .dynamicArea.areaBuffer
    button_back_bmp  // .img
};

guiImage_t screen_buttonBackDisabled =
{
    0,                        // .dynamicArea.xCrd
    81,                       // .dynamicArea.yCrd
    0,                        // .dynamicArea.width
    0,                        // .dynamicArea.height
    NULL,                     // .dynamicArea.areaBuffer
    button_back_disabled_bmp  // .img
};

guiImage_t screen_buttonRightUp =
{
    92,                   // .dynamicArea.xCrd
    30,                   // .dynamicArea.yCrd
    0,                    // .dynamicArea.width
    0,                    // .dynamicArea.height
    NULL,                 // .dynamicArea.areaBuffer
    buttonGroup_right_bmp // .img
};

guiImage_t screen_buttonRightDown =
{
    92,                   // .dynamicArea.xCrd
    57,                   // .dynamicArea.yCrd
    0,                    // .dynamicArea.width
    0,                    // .dynamicArea.height
    NULL,                 // .dynamicArea.areaBuffer
    buttonGroup_right_bmp // .img
};

guiImage_t screen_buttonLeftUp =
{
    2,                   // .dynamicArea.xCrd
    30,                  // .dynamicArea.yCrd
    0,                   // .dynamicArea.width
    0,                   // .dynamicArea.height
    NULL,                // .dynamicArea.areaBuffer
    buttonGroup_left_bmp // .img
};

guiImage_t screen_buttonLeftDown =
{
    2,                   // .dynamicArea.xCrd
    57,                  // .dynamicArea.yCrd
    0,                   // .dynamicArea.width
    0,                   // .dynamicArea.height
    NULL,                // .dynamicArea.areaBuffer
    buttonGroup_left_bmp // .img
};
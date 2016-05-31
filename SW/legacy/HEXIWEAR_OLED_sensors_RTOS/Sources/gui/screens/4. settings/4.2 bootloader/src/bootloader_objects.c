#include "gui_driver.h"
#include "screens_common.h"
#include "bootloader.h"
#include "bootloader_private.h"

/**
 * screens
 */

static guiScreen_t bootloaderMainScreen =
{
  .navigation =
  {
          .up     = NULL,
          .down   = NULL,
          .left   = &bootloaderCoverScreen,
          .right  = NULL
  },

  .image = otap_mainScreen_bmp,

  .initFunction        = bootloader_Init,
  .createTaskFunction  = bootloader_CreateTasks,
  .destroyTaskFunction = bootloader_DestroyTasks
};

guiScreen_t bootloaderCoverScreen =
{
  .navigation =
  {
          .up     = &bluetoothScreen,
          .down   = &buttonsGroupScreen,
          .left   = &settingsScreen,
          .right  = &bootloaderMainScreen
  },

  .image = otap_coverScreen_bmp,

  .initFunction        = NULL,
  .createTaskFunction  = NULL,
  .destroyTaskFunction = NULL
};

/**
 * labels
 */

guiLabel_t bootloader_labelLoad =
{
  .dynamicArea =
  {
          .xCrd   = 25,
          .yCrd   = 6,
          .width  = 50,
          .height = 20
  },

  .textProperties =
  {
          .font       = guiFont_Tahoma_10_Regular,
          .fontColor  = GUI_COLOR_WHITE,
          .alignParam = OLED_TEXT_ALIGN_CENTER,
          .background = NULL
  },

  .caption = NULL,
  .captionLength = 8
};


/**
 * images
 */

guiImage_t bootloader_selectMK64 =
{
  .dynamicArea =
  {
    .xCrd = 24,
    .yCrd = 23,
  },

  .img = otap_select_mk64_bmp
};

guiImage_t bootloader_selectKW40 =
{
  .dynamicArea =
  {
    .xCrd = 24,
    .yCrd = 23,
  },

  .img = otap_select_kw40_bmp
};

guiImage_t bootloader_loadImg_white =
{
  .dynamicArea =
  {
    .xCrd = 20,
    .yCrd = 20,
  },

  .img = bootloader_loadWhite_bmp
};

guiImage_t bootloader_loadImg_blue =
{
  .dynamicArea =
  {
    .xCrd = 20,
    .yCrd = 20,
  },

  .img = bootloader_loadBlue_bmp
};

guiImage_t bootloader_success =
{
  .dynamicArea =
  {
    .xCrd = 0,
    .yCrd = 0
  },

  .img = bootloader_success_bmp
};

guiImage_t bootloader_failure =
{
  .dynamicArea =
  {
    .xCrd = 0,
    .yCrd = 0
  },

  .img = bootloader_failure_bmp
};


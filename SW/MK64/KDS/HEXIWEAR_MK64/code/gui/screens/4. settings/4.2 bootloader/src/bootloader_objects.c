/**
 * \file bootloader_objects.c
 * \version 1.00
 * \brief this file contains bootloader GUI related objects
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * Neither the name of NXP, nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * visit: http://www.mikroe.com and http://www.nxp.com
 *
 * get support at: http://www.mikroe.com/forum and https://community.nxp.com
 *
 * Project HEXIWEAR, 2015
 */

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


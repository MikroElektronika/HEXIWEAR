/**
 * \file info_objects.c
 * \version 1.00
 * \brief this file contains HEXIWEAR About Screen GUI objects
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
#include "info_private.h"

guiScreen_t infoScreen =
{
  .navigation =
  {
          .up     = NULL,
          .down   = NULL,
          .left   = &aboutScreen,
          .right  = NULL
  },

  .image = 	NULL,

  .initFunction        = info_Init,
  .createTaskFunction  = info_CreateTasks,
  .destroyTaskFunction = info_DestroyTasks
};

guiLabel_t info_labelTitle =
{
  .dynamicArea =
  {
          .xCrd   = 8,
          .yCrd   = 21,
          .width  = 80,
          .height = 15
  },

  .textProperties =
  {
          .font       = guiFont_Tahoma_8_Regular,
          .fontColor  = GUI_COLOR_GRAY,
          .alignParam = OLED_TEXT_ALIGN_CENTER,
          .background = NULL
  },

  .caption = NULL,
  .captionLength = 14
};

guiLabel_t info_labelData =
{
  .dynamicArea =
  {
          .xCrd   = 4,
          .yCrd   = 37,
          .width  = 89,
          .height = 13
  },

  .textProperties =
  {
          .font       = guiFont_Tahoma_8_Regular,
          .fontColor  = GUI_COLOR_BLUE_1,
          .alignParam = OLED_TEXT_ALIGN_CENTER,
          .background = NULL
  },

  .caption = NULL,
  .captionLength = 18
};

guiLabel_t info_labelData2 =
{
  .dynamicArea =
  {
          .xCrd   = 0,
          .yCrd   = 60,
          .width  = 96,
          .height = 13
  },

  .textProperties =
  {
          .font       = guiFont_Tahoma_8_Regular,
          .fontColor  = GUI_COLOR_GRAY,
          .alignParam = OLED_TEXT_ALIGN_CENTER,
          .background = NULL
  },

  .caption = NULL,
  .captionLength = 18
};

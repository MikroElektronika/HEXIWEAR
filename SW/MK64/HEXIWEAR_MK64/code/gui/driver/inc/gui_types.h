/**
 * \file gui_types.h
 * \version 1.00
 * \brief this file contains GUI menu-related data type structures and enums
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

#pragma once

#include <stdint.h>
#include "OLED_driver.h"
#include "gui_info.h"

/** GUI navigation pointers */
typedef struct GuiNavigation
{
  struct GuiItem *up;
  struct GuiItem *down;
  struct GuiItem *left;
  struct GuiItem *right;

} guiNavigation_t;

/** GUI screen navigation structure */
typedef struct GuiItem
{
  guiNavigation_t navigation;
    const uint8_t* image;
              void (*initFunction)(void *param);
              void (*createTaskFunction)(void *param);
              void (*destroyTaskFunction)(void *param);

} guiScreen_t;

/** GUI display structure */
typedef struct
{
  guiScreen_t* guiItem;
  uint8_t image[ GUI_IMAGE_SIZE ]; /**< OLED buffer screen */

} guiDisplay_t;

/** global GUI status enum */
typedef enum
{
  GUI_STATUS_SUCCESS,     // success
  GUI_STATUS_ERROR,       // fail

} gui_status_t;

typedef enum
{
	GUI_LABEL_CUT_FORMAT_NONE  = 0,
	GUI_LABEL_CUT_FORMAT_DOTS  = 1,
	GUI_LABEL_CUT_FORMAT_SPACE = 2,
} guiLabelCutFormat_t;

/** GUI navigation structure */
typedef enum
{
  GUI_NAVIGATION_WATCH        = 0,
  GUI_NAVIGATION_BOND         = 0x1 << 1,

  GUI_NAVIGATION_UP    	      = 0x1 << 2,
  GUI_NAVIGATION_DOWN         = 0x1 << 3,
  GUI_NAVIGATION_LEFT	      = 0x1 << 4,
  GUI_NAVIGATION_RIGHT	      = 0x1 << 5,

  GUI_NAVIGATION_SPLASH       = 0x1 << 7,

} guiNavigationDir_t;

/** color chart */
typedef enum
{
  GUI_COLOR_BLACK    = 0x0000,
  GUI_COLOR_BLUE_1   = 0x06FF,
  GUI_COLOR_BLUE     = 0x001F,
  GUI_COLOR_RED      = 0xF800,
  GUI_COLOR_GREEN    = 0x07E0,
  GUI_COLOR_CYAN     = 0x07FF,
  GUI_COLOR_MAGENTA  = 0xF81F,
  GUI_COLOR_YELLOW   = 0xFFE0,
  GUI_COLOR_GRAY     = 0x528A,
  GUI_COLOR_WHITE    = 0xFFFF

} guiColor_t;

/** GUI image structure */
typedef struct
{
	oled_dynamic_area_t  dynamicArea;
	const uint8_t       *img;

} guiImage_t;

/** GUI label */
typedef struct
{
	oled_dynamic_area_t    dynamicArea;
	oled_text_properties_t textProperties;
	uint8_t               *caption;
	uint8_t                captionLength;

} guiLabel_t;

/** current app enum */
typedef enum
{
  GUI_CURRENT_APP_IDLE                = 0, /**< no app active */
  GUI_CURRENT_APP_SENSOR_TAG          = 2, /**< sensor tag */
  GUI_CURRENT_APP_HEART_RATE          = 5, /**< heart rate */
  GUI_CURRENT_APP_PEDOMETER           = 6  /**< Pedometer */

} gui_current_app_t;
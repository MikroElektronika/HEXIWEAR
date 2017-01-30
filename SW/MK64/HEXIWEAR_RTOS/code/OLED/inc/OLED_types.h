/**
 * \file OLED_types.h
 * \version 1.00
 * \brief this file contains OLED-related data-types
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
#include "generic_spi_types.h"

#include "OLED_info.h"

/** image transition styles */
typedef enum
{
  OLED_TRANSITION_NONE,       /**< no image transition, just draw it */
  OLED_TRANSITION_TOP_DOWN,   /**< image transition from top to down */
  OLED_TRANSITION_DOWN_TOP,   /**< image transition from down to top */
  OLED_TRANSITION_LEFT_RIGHT, /**< image transition from left to right */
  OLED_TRANSITION_RIGHT_LEFT  /**< image transition from right to left */

} oled_transition_t;

/** status flags */
typedef enum
{
  OLED_STATUS_SUCCESS,        /**< success */
  OLED_STATUS_ERROR,          /**< fail */
  OLED_STATUS_PROTOCOL_ERROR, /**< SPI failure */
  OLED_STATUS_INIT_ERROR,     /**< initialization error */
  OLED_STATUS_DEINIT_ERROR    /**< deinitialization error */

} oled_status_t;

/** general purpose OLED handle data structure */
typedef struct
{
  genericSpiHandle_t protocol; /**<  protocol-relevant information */

} handleOLED_t;

typedef uint16_t* oled_pixel_t;

/** OLED specific settings */
typedef struct
{
  uint32_t DCpin;
  uint32_t CSpin;
  uint32_t RSTpin;
// uint32_t RWpin;
  uint32_t ENpin;

} settingsOLED_t;

/** text alignment options */
typedef enum
{
  OLED_TEXT_ALIGN_NONE = 0,

  OLED_TEXT_ALIGN_LEFT   = 0x1,
  OLED_TEXT_ALIGN_RIGHT  = 0x2,
  OLED_TEXT_ALIGN_CENTER = 0x3,

  OLED_TEXT_VALIGN_TOP    = 0x10,
  OLED_TEXT_VALIGN_BOTTOM = 0x20,
  OLED_TEXT_VALIGN_CENTER = 0x30

} oled_text_align_t;

/** text/image dynamic area structure */
typedef struct
{
	     uint8_t xCrd;        /**< desired x-coordinate */
	     uint8_t yCrd;        /**< desired y-coordinate */
	     uint8_t width;       /**< desired text/image width */
	     uint8_t height;      /**< desired text/image height */
	oled_pixel_t areaBuffer;  /**< desired memory buffer */

} oled_dynamic_area_t;

/** OLED text properties */
typedef struct
{
  const uint8_t* font;          /**< desired font */
  uint16_t fontColor;           /**< desired font color */
  oled_text_align_t alignParam; /**< desired font alignment */
  const uint8_t* background;    /**< desired font background */

} oled_text_properties_t;

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

/** GUI display structure */
typedef struct
{
  uint8_t image[ GUI_IMAGE_SIZE ]; /**< OLED buffer screen */

} guiDisplay_t;

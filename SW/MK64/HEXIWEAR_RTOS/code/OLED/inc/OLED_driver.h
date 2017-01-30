/**
 * \file OLED_driver.h
 * \version 1.00
 * \brief this file contains OLED driver functionality for
 * drawing images and text
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

#include "OLED_types.h"

/**
 * initialize OLED screen
 * @param  self     OLED handle
 * @param  settings specific OLED settings
 * @return          status flag
 */
oled_status_t OLED_Init(
                          handleOLED_t* self,
                        settingsOLED_t* settings
                      );

/**
 * deinitialize OLED (not used)
 * @param  self OLED handle
 * @return      status flag
 */
oled_status_t OLED_Deinit();

/**
 * return given image dimensions
 * @param width  given image's width
 * @param height given image's height
 * @param image  desired image
 */
void OLED_GetImageDimensions(uint8_t *width, uint8_t *height, const uint8_t* image);

/**
 * add image to the main screen buffer
 * @param  image      desired image
 * @return            status flag
 */
oled_status_t OLED_AddImage( const uint8_t* image );

/**
 * draw image, i.e. send image to OLED GRAM
 * @param  image      desired image
 * @param  transition desired transition for the image to appear
 * @return            status flag
 */
oled_status_t OLED_DrawImage( const uint8_t* image );

/**
 * send the command to OLED
 * @param  self    OLED handle
 * @param  cmd     OLED command from the datasheet
 * @param  isFirst designate if this is the first byte in the command
 * @return         status flag
 */
oled_status_t OLED_SendCmd (
                             uint32_t cmd,
                              uint8_t isFirst
                           );

/**
 * send data to OLED
 * @param  dataToSend data to send to OLED
 * @param  dataSize   data-size
 * @return            status flag
 */
oled_status_t OLED_SendData(
                            const uint8_t* dataToSend,
                                  uint32_t dataSize
                          );

/**
 * draw box on OLED
 * @param  xCrd   x-coordinate for box's uper left corner
 * @param  yCrd   y-coordinate for box's uper left corner
 * @param  width  box's width
 * @param  height box's height
 * @param  color  color of the box
 * @return        status flag
 */
oled_status_t OLED_DrawBox (
                            uint16_t xCrd,
                            uint16_t yCrd,
                            uint16_t width,
                            uint16_t height,
                            uint16_t color
                          );

/**
 * fill the entire screen
 * @param  color color to fill with
 * @return status flag
 */
oled_status_t OLED_FillScreen( uint16_t color );

/**
 * draw a single pixel
 * @param  xCrd  pixel's x coordinate
 * @param  yCrd  pixel's y coordinate
 * @param  color pixel's color
 * @return       status flag
 */
oled_status_t OLED_DrawPixel (
                               int16_t xCrd,
                               int16_t yCrd,
                              uint16_t color
                            );

/**
 * draw the whole screen
 * @param  image      image to draw
 * @param  xCrd       image x-coordinate
 * @param  yCrd       image y-coordinate
 * @param  width      image width
 * @param  height     image height
 * @param  transition transition style for the new image arrival
 * @return            status flag
 */
oled_status_t OLED_DrawScreen (
                                   const uint8_t* image,
                                          uint8_t xCrd,
                                          uint8_t yCrd,
                                          uint8_t width,
                                          uint8_t height,
                                oled_transition_t transition
                              );

/**
 * set the font to use
 * @param newFont  desired font
 * @param newColor desired color
 * @return         status flag
 */
oled_status_t OLED_SetFont (
                            const uint8_t* newFont,
                                  uint16_t newColor
                          );

/**
 * add text to the main screen buffer
 * @param  text text to add
 * @return      status flag
 */
oled_status_t OLED_AddText( const uint8_t* text );

/**
 * write text on OLED to given position
 * @param text desired text
 * @param x    x-coordinate for the given text
 * @param y    y-coordinate for the given text
 */
oled_status_t OLED_DrawText ( const uint8_t* text );

/**
 * set OLED dynamic area
 * @param dynamic_area data-structure with desired values
 */
void OLED_SetDynamicArea(oled_dynamic_area_t *dynamic_area);

/**
 * destroy current OLED dynamic area
 */
void OLED_DestroyDynamicArea(void);

/**
 * set OLED text properties
 * @param textProperties data-structure with desired properties
 */
void OLED_SetTextProperties(oled_text_properties_t *textProperties);

/**
 * count the characters
 * @param  width  text width
 * @param  font   text font
 * @param  text   given text string
 * @param  length text length
 * @return        character count
 */
uint8_t OLED_CharCount(uint8_t width, const uint8_t* font, const uint8_t* text, uint8_t length);

/**
 * return the width in [px] required for the given string to be displayed
 * @param  text desired string
 * @return      required text width in [px]
 */
uint8_t OLED_GetTextWidth(const uint8_t* text);

/**
 * swap image's bytes per pixel to obtain the correct color format
 * @param imgDst  desired image
 * @param imgSrc  original image
 * @param imgSize image's size
 */
void OLED_Swap  (
					oled_pixel_t imgSrc,
					const uint8_t* imgDst,
					uint16_t imgSize
				);

/**
 * dim OLED screen on
 */
void OLED_DimScreenON();

/**
 * return OLED back to full contrast
 */
void OLED_DimScreenOFF();

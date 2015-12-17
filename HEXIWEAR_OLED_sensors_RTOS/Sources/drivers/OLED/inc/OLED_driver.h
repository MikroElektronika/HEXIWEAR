/**
 * OLED driver functions
 * Project HEXIWEAR, 2015
 */

#ifndef HG_OLED_DRIVER
#define HG_OLED_DRIVER

#include "OLED_types.h"

/**
 * initialize OLED screen
 * @param  settings [description]
 * @return          [description]
 */
oled_status_t OLED_Init(
                          handleOLED_t* self,
                        settingsOLED_t* settings
                      );

/**
 * [OLED_Deinit description]
 * @param  self [description]
 * @return      [description]
 */
oled_status_t OLED_Deinit();

/**
 * set given image as active
 * @param  imgBuf [description]
 * @param  xPos   [description]
 * @param  yPos   [description]
 * @param  width  [description]
 * @param  height [description]
 * @return        [description]
 */
oled_status_t OLED_SetActiveImage(
                                  oled_pixel_t imgBuf,
                                       uint8_t xCrd,
                                       uint8_t yCrd,
                                       uint8_t width,
                                       uint8_t height
                                );

/**
 * create the buffer for a partial image
 * @param  imgBuf [description]
 * @param  width  [description]
 * @param  height [description]
 * @return        [description]
 */
oled_status_t OLED_CreatePartialImage(
                                      oled_pixel_t* imgBuf,
                                            uint8_t xCrd,
                                            uint8_t yCrd,
                                            uint8_t width,
                                            uint8_t height
                                    );

void OLED_GetImageDimensions(uint8_t *width, uint8_t *height, const uint8_t* image);

oled_status_t OLED_AddImage (
                              const uint8_t* image
                            );
oled_status_t OLED_DrawImage (
                              const uint8_t* image
                            );

/**
 * send the command to OLED
 * @param  self    [description]
 * @param  cmd     [description]
 * @param  isFirst [description]
 * @return         [description]
 */
oled_status_t OLED_SendCmd (
                            uint32_t cmd,
                             uint8_t isFirst
                          );
/**
 * [OLED_SendData description]
 * @param  self       [description]
 * @param  dataToSend [description]
 * @param  dataSize   [description]
 * @return            [description]
 */
oled_status_t OLED_SendData(
                            const uint8_t* dataToSend,
                                  uint32_t dataSize
                          );

/**
 * [OLED_DrawBox  description]
 * @param  self   [description]
 * @param  xCrd   [description]
 * @param  yCrd   [description]
 * @param  width  [description]
 * @param  height [description]
 * @param  color  [description]
 * @return        [description]
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
 * @return       status flag
 */
oled_status_t OLED_FillScreen(
                              uint16_t color
                            );

/**
 * draw a single pixel
 * @param  self  [description]
 * @param  xCrd  [description]
 * @param  yCrd  [description]
 * @param  color [description]
 * @return       [description]
 */
oled_status_t OLED_DrawPixel (
                               int16_t xCrd,
                               int16_t yCrd,
                              uint16_t color
                            );

/**
 * [OLED_DrawScreen  description]
 * @param  self       [description]
 * @param  image      [description]
 * @param  xCrd       [description]
 * @param  yCrd       [description]
 * @param  width      [description]
 * @param  height     [description]
 * @param  transition [description]
 * @return            [description]
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
 * @param activeFont [description]
 * @param newColor [description]
 */
oled_status_t OLED_SetFont (
                            const uint8_t* newFont,
                                  uint16_t newColor
                          );

/**
 * write character on the screen
 * @param charToWrite [description]
 * @param xPos        [description]
 * @param yPos        [description]
 */
oled_status_t OLED_WriteChar (
                              uint16_t charToWrite,
                              uint16_t xPos,
                              uint16_t yPos
                            );

oled_status_t OLED_AddText(
                            const uint8_t* text
                          );
/**
 * write text on current position
 * @param text [description]
 * @param x    [description]
 * @param y    [description]
 */
oled_status_t OLED_DrawText (
                              const uint8_t* text
                            );

void OLED_SetDynamicArea(oled_dynamic_area_t *dynamic_area);

void OLED_DestroyDynamicArea(void);

void OLED_SetTextProperties(oled_text_properties_t *textProperties);

void OLED_Swap(
		        oled_pixel_t imgSrc,
				const uint8_t* imgDst,
				uint16_t imgSize
			  );

#endif

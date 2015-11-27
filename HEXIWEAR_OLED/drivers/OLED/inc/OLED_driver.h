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
statusOLED_t OLED_Init(
                          handleOLED_t* self,
                        settingsOLED_t* settings
                      );

/**
 * [OLED_Deinit description]
 * @param  self [description]
 * @return      [description]
 */
statusOLED_t OLED_Deinit();

/**
 * send the command to OLED
 * @param  self    [description]
 * @param  cmd     [description]
 * @param  isFirst [description]
 * @return         [description]
 */
statusOLED_t OLED_SendCmd (
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
statusOLED_t OLED_SendData(
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
statusOLED_t OLED_DrawBox (
                            uint16_t xCrd,
                            uint16_t yCrd,
                            uint16_t width,
                            uint16_t height,
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
statusOLED_t OLED_DrawPixel (
                               int16_t xCrd,
                               int16_t yCrd,
                              uint16_t color
                            );

/**
 * [OLED_DrawImage  description]
 * @param  self       [description]
 * @param  image      [description]
 * @param  xCrd       [description]
 * @param  yCrd       [description]
 * @param  width      [description]
 * @param  height     [description]
 * @param  transition [description]
 * @return            [description]
 */
statusOLED_t OLED_DrawImage (
                              const uint8_t* image,
                                transition_t transition
                            );

#endif

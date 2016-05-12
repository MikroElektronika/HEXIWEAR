/**
 * OLED-related data structures
 * Project HEXIWEAR, 2015
 */

#ifndef HG_OLED_TYPES
#define HG_OLED_TYPES

#include <stdint.h>
#include "generic_spi_types.h"

typedef enum
{
  OLED_TRANSITION_NONE,
  OLED_TRANSITION_TOP_DOWN,
  OLED_TRANSITION_DOWN_TOP,
  OLED_TRANSITION_LEFT_RIGHT,
  OLED_TRANSITION_RIGHT_LEFT

} oled_transition_t;

typedef enum
{
  OLED_STATUS_SUCCESS,        // success
  OLED_STATUS_ERROR,          // fail
  OLED_STATUS_PROTOCOL_ERROR, // SPI failure
  OLED_STATUS_INIT_ERROR,     // initialization error
  OLED_STATUS_DEINIT_ERROR    // deinitialization error

} oled_status_t;

typedef struct
{
  /**
   * SPI relevant information
   */
  genericSpiHandle_t protocol;

} handleOLED_t;

typedef uint16_t* oled_pixel_t;

typedef struct
{
  uint32_t DCpin;
  uint32_t CSpin;
  uint32_t RSTpin;
//  uint32_t RWpin;
  uint32_t ENpin;

} settingsOLED_t;

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

typedef struct
{
	     uint8_t xCrd;
	     uint8_t yCrd;
	     uint8_t width;
	     uint8_t height;
	oled_pixel_t areaBuffer;

} oled_dynamic_area_t;

typedef struct
{
  const uint8_t* font;
  uint16_t fontColor;
  oled_text_align_t alignParam;
  const uint8_t* background;

} oled_text_properties_t;

#endif

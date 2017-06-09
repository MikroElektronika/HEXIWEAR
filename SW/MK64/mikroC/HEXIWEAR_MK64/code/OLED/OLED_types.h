// File: OLED_types.h

// Definitions of types used in the OLED module.

#ifndef _OLED_types_h_
#define _OLED_types_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////
 
#include <stdint.h>

#include "OSA.h"
#include "generic_spi_types.h"

////////////////////////////////////////////////////////////////////////////////
// Type definitions.                                                          //
////////////////////////////////////////////////////////////////////////////////

// Image transition styles.
typedef enum
{
    OLED_TRANSITION_NONE,       // no image transition, just draw it
    OLED_TRANSITION_TOP_DOWN,   // image transition from top to down
    OLED_TRANSITION_DOWN_TOP,   // image transition from down to top
    OLED_TRANSITION_LEFT_RIGHT, // image transition from left to right
    OLED_TRANSITION_RIGHT_LEFT  // image transition from right to left
} oled_transition_t;

// Status flags.
typedef enum
{
    OLED_STATUS_SUCCESS,        // success
    OLED_STATUS_ERROR,          // fail
    OLED_STATUS_PROTOCOL_ERROR, // SPI failure
    OLED_STATUS_INIT_ERROR,     // initialization error
    OLED_STATUS_DEINIT_ERROR    // deinitialization error

} oled_status_t;

// general purpose OLED handle data structure
typedef struct
{
    genericSpiHandle_t protocol; //  protocol-relevant information

} handleOLED_t;

typedef uint16_t* oled_pixel_t;

// OLED specific settings.
typedef struct
{
    uint32_t DCpin;
    uint32_t CSpin;
    uint32_t RSTpin;
    // uint32_t RWpin;
    uint32_t ENpin;
} settingsOLED_t;

// Text alignment options.
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

// OLED colors.
typedef enum
{
  OLED_COLOR_BLACK    = 0x0000,
  OLED_COLOR_BLUE_1   = 0x06FF,
  OLED_COLOR_BLUE     = 0x001F,
  OLED_COLOR_RED      = 0xF800,
  OLED_COLOR_GREEN    = 0x07E0,
  OLED_COLOR_CYAN     = 0x07FF,
  OLED_COLOR_MAGENTA  = 0xF81F,
  OLED_COLOR_YELLOW   = 0xFFE0,
  OLED_COLOR_GRAY     = 0x528A,
  OLED_COLOR_WHITE    = 0xFFFF

} oled_color_t;

// Text/image dynamic area structure.
typedef struct
{
    uint8_t xCrd;            // desired x-coordinate
    uint8_t yCrd;            // desired y-coordinate
    uint8_t width;           // desired text/image width
    uint8_t height;          // desired text/image height
    oled_pixel_t areaBuffer; // desired memory buffer
} oled_dynamic_area_t;

// OLED text properties.
typedef struct
{
    const uint8_t *font;          // desired font
    uint16_t fontColor;           // desired font color
    oled_text_align_t alignParam; // desired font alignment
    const uint8_t *background;    // desired font background
} oled_text_properties_t;

#endif
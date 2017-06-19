// File: OLED_driver.h

// Declarations of user functionalities of the OLED module.

#ifndef _OLED_driver_h_
#define _OLED_driver_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "OLED_types.h"
#include "OLED_info.h"
#include "gui_resources.h"

////////////////////////////////////////////////////////////////////////////////
// Global function declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

// Initialises the OLED screen.
oled_status_t OLED_Init( handleOLED_t* oledHandle );

// Deinitialises the OLED screen. (not used)
oled_status_t OLED_Deinit();

// Returns dimensions of the given image.
void OLED_GetImageDimensions(
    uint8_t *width,
    uint8_t *height,
    const uint8_t *image );

// Adds image to the image buffer.
oled_status_t OLED_AddImage( const uint8_t *image );

// Draws an image on the display.
oled_status_t OLED_DrawImage(
    const uint8_t *image );

// Sends a command to the OLED.
oled_status_t OLED_SendCmd( uint32_t cmd, uint8_t isFirst );

// Sends data to the OLED.
oled_status_t OLED_SendData( const uint8_t *dataToSend, uint32_t dataSize );

// Draws a box on the screen.
oled_status_t OLED_DrawBox(
    uint16_t xCrd,
    uint16_t yCrd,
    uint16_t width,
    uint16_t height,
    uint16_t color );

// Fills the screen with the given color.
oled_status_t OLED_FillScreen( uint16_t color );

// Draws a pixel on the screen.
oled_status_t OLED_DrawPixel(
    uint16_t xCrd,
    uint16_t yCrd,
    uint16_t color );

// Draws a screen in the desired direction.
oled_status_t OLED_DrawScreen(
    const uint8_t *image,
    uint8_t xCrd,
    uint8_t yCrd,
    uint8_t width,
    uint8_t height,
    oled_transition_t transition );

// Sets font of the OLED display.
oled_status_t OLED_SetFont(
    const uint8_t *activeFont,
    uint16_t font_color );

// Adds text to the text buffer.
oled_status_t OLED_AddText( const uint8_t *text );

// Writes text to OLED.
oled_status_t OLED_DrawText( uint8_t *text );

// Sets the dynamic area of the OLED display.
void OLED_SetDynamicArea( oled_dynamic_area_t *dynamic_area );

// Destroys the dynamic area of the OLED display.
void OLED_DestroyDynamicArea();

// Sets text properties.
void OLED_SetTextProperties( oled_text_properties_t *textProperties );

// Counts the characters in a text of a given font
// that can fit on the given width.
uint8_t OLED_CharCount(
    uint8_t width,
    const uint8_t *font,
    const uint8_t *text,
    uint8_t length );

// Returns the width that the given text would take on the screen.
uint8_t OLED_GetTextWidth( const uint8_t *text );

// Transfers source image to destination image
// so that bytes in each pixel are inverted,
// which is how they should be sent to the display.
void OLED_Swap( oled_pixel_t imgDst,
    const uint8_t* imgSrc, uint16_t imgSize );

// Dim the OLED screen.
void OLED_DimScreenON();

// Return the OLED screen back to full contrast.
void OLED_DimScreenOFF();

#endif
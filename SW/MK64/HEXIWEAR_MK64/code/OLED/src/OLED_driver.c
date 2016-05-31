/**
 * \file OLED_driver.c
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

#include "HEXIWEAR_info.h"

#include "OLED_Driver.h"
#include "string.h"
#include <stdlib.h>
#include "error.h"

#include "generic_spi_driver.h"
#include "generic_spi_info.h"

#include "fsl_dspi_edma_master_driver.h"

#include "fsl_gpio_driver.h"

#include "OLED_Defs.h"
#include "OLED_Info.h"

#include "gui_resources.h"

#include "gui_driver.h"
#include "gui_defs.h"

#include "power_driver.h"

/**
 * intern variables
 */

static uint8_t
  isFontInitialized = 0;

static const uint8_t*
  selectedFont;

static uint16_t
  selectedFont_color,
  selectedFont_firstChar, // first character in the font table
  selectedFont_lastChar,  // last character in the font table
  selectedFont_height;

static oled_dynamic_area_t
  oled_dynamic_area;

static oled_text_properties_t
  oled_text_properties =  {
                            .alignParam = OLED_TEXT_ALIGN_CENTER,
                            .background = NULL
                          };

static uint8_t
  screenBuf[ OLED_GRAM_SIZE ];

static uint8_t
  currentChar_width  = 0,
  currentChar_height = 0;

static uint16_t
	colorMask = GUI_COLOR_WHITE;

#include "GPIO.h"

/**
 * macros and consts
 */
#define OLED_REMAP_SETTINGS ( REMAP_ORDER_ABC | REMAP_COM_SPLIT_ODD_EVEN_EN | REMAP_COLOR_RGB565 | REMAP_COLUMNS_LEFT_TO_RIGHT | REMAP_SCAN_UP_TO_DOWN | REMAP_HORIZONTAL_INCREMENT )

#define OLED_AdjustRowOffset(y)    y += OLED_ROW_OFFSET
#define OLED_AdjustColumnOffset(x) x += OLED_COLUMN_OFFSET

#define CheckLimits( x, y, w, h ) ( ( ( x + w - 1 ) > OLED_SCREEN_WIDTH ) || ( x < 0 ) || ( ( y + h - 1 ) > OLED_SCREEN_HEIGHT ) || ( y < 0 ) )
#define AreCoordsValid( x, y, w, h )    ( 0 == CheckLimits( x, y, w ,h ) )
#define AreCoordsNotValid( x, y, w, h ) ( 0 != CheckLimits( x, y, w, h ) )

/** intern variables */

static handleOLED_t
  self;
static settingsOLED_t
  settings;

/** intern functions' declarations */

static void Transpose( oled_pixel_t transImage, const oled_pixel_t image, uint8_t width, uint8_t height );

static oled_status_t RightLeft ( const uint8_t* image, uint8_t xCrd, uint8_t yCrd, uint8_t width, uint8_t height );
static oled_status_t LeftRight ( const uint8_t* image, uint8_t xCrd, uint8_t yCrd, uint8_t width, uint8_t height );
static oled_status_t DownTop   ( const uint8_t* image, uint8_t xCrd, uint8_t yCrd, uint8_t width, uint8_t height );
static oled_status_t TopDown   ( const uint8_t* image, uint8_t xCrd, uint8_t yCrd, uint8_t width, uint8_t height );

static void SetBorders( uint8_t xCrd, uint8_t yCrd, uint8_t width, uint8_t height );
static oled_status_t CreateTextBackground();
static void WriteCharToBuf( uint16_t charToWrite, oled_pixel_t* chrBuf );
static oled_status_t AddCharToTextArea( oled_pixel_t chrPtr, uint8_t chrWidth, uint8_t chrHeight, oled_pixel_t copyAddr, uint8_t imgWidth );
static void* AllocateDynamicArea( uint32_t area );
static oled_status_t DestroyDynamicArea(void * ptr);

static oled_status_t SendViaSPI( const uint8_t* bufPtr, uint32_t txSize );

/** Public API */

/**
 * initialize OLED screen
 * @param  self     OLED handle
 * @param  settings specific OLED settings
 * @return          status flag
 */
oled_status_t OLED_Init(
                          handleOLED_t* oledHandle,
                        settingsOLED_t* oledSettings
                      )
{
  statusSPI_t
    status = SPI_Init( &(oledHandle->protocol) );

  if ( STATUS_SPI_SUCCESS != status )
  {
    catch( CATCH_INIT );
    return OLED_STATUS_PROTOCOL_ERROR;
  }

  else
  {
    /**
     * initialize intern OLED structures,
     * which will be used from now on
     */

    memcpy( (void*)&self,     (void*)oledHandle,   sizeof(self) );
    memcpy( (void*)&settings, (void*)oledSettings, sizeof(settings) );

    status = OLED_STATUS_SUCCESS;

    /** set IRQ priority */

    NVIC_SetPriority( HEXIWEAR_OLED_SPI_IRQn,    HEXIWEAR_OLED_SPI_IRQ_PRIO );
    NVIC_SetPriority( HEXIWEAR_OLED_DMA_RX_IRQn, HEXIWEAR_OLED_DMA_RX_IRQ_PRIO );
    NVIC_SetPriority( HEXIWEAR_OLED_DMA_TX_IRQn, HEXIWEAR_OLED_DMA_TX_IRQ_PRIO );

	  // create mutex for using the spi comm
    osa_status_t
        spiStatus = OSA_MutexCreate( &spiAccessMutex );

    /** power sequence */

    power_TurnOFF( POWER_OLED );
    OSA_TimeDelay(1);
    GPIO_DRV_ClearPinOutput( settings.RSTpin );
    OSA_TimeDelay(1);
    GPIO_DRV_SetPinOutput( settings.RSTpin );
    OSA_TimeDelay(1);
    power_TurnON( POWER_OLED );

    if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_SET_CMD_LOCK, FIRST_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_UNLOCK, OTHER_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }

    if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_SET_CMD_LOCK, FIRST_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_ACC_TO_CMD_YES, OTHER_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }

    if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_DISPLAYOFF, FIRST_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }

    if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_SET_OSC_FREQ_AND_CLOCKDIV, FIRST_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0xF1, OTHER_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }

    if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_SET_MUX_RATIO, FIRST_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x5F, OTHER_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }

    if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_SET_REMAP, FIRST_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_REMAP_SETTINGS, OTHER_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }

    if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_SET_COLUMN, FIRST_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x00, OTHER_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x5F, OTHER_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }

    if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_SET_ROW, FIRST_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x00, OTHER_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x5F, OTHER_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }

    if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_STARTLINE, FIRST_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x80, OTHER_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }

    if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_DISPLAYOFFSET, FIRST_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x60, OTHER_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }

    if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_PRECHARGE, FIRST_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x32, FIRST_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }

    if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_VCOMH, FIRST_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x05, FIRST_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }

    if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_NORMALDISPLAY, FIRST_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }

    if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_CONTRASTABC, FIRST_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x8A, OTHER_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x51, OTHER_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x8A, OTHER_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }

    if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_CONTRASTMASTER, FIRST_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0xCF, OTHER_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }

    if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_SETVSL, FIRST_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0xA0, OTHER_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0xB5, OTHER_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x55, OTHER_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }

    if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_PRECHARGE2, FIRST_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x01, OTHER_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }

    if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_DISPLAYON, FIRST_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
 }

  return OLED_STATUS_SUCCESS;
}

/**
 * deinitialize OLED (not used)
 * @param  self OLED handle
 * @return      status flag
 */
oled_status_t OLED_Deinit()
{
  return SPI_Deinit( &(self.protocol) );
}

/**
 * send the command to OLED
 * @param  self    OLED handle
 * @param  cmd     OLED command from the datasheet
 * @param  isFirst designate if this is the first byte in the command
 * @return         status flag
 */
oled_status_t OLED_SendCmd(
                            uint32_t cmd,
                             uint8_t isFirst
                          )
{
  uint8_t
    txSize = 1,
    txBuf[4];

  genericSpiHandle_t
    spiProtocol = self.protocol;

  dspi_status_t
    status;

  memcpy( (void*)txBuf, (void*)&cmd, txSize );

  if ( isFirst )
  {
    GPIO_DRV_ClearPinOutput( settings.DCpin );
  }
  else
  {
    GPIO_DRV_SetPinOutput( settings.DCpin );
  }

	  GPIO_DRV_ClearPinOutput( settings.CSpin );
	  oled_status_t
	  	  spiStatus = SendViaSPI( txBuf, txSize );

	if ( OLED_STATUS_SUCCESS == spiStatus )
    {
      GPIO_DRV_SetPinOutput( settings.CSpin );
      return OLED_STATUS_SUCCESS;
    }

    else
    {
      catch( CATCH_OLED );
      GPIO_DRV_SetPinOutput( settings.CSpin );
      return OLED_STATUS_PROTOCOL_ERROR;
    }
}

/**
 * send data to OLED
 * @param  dataToSend data to send to OLED
 * @param  dataSize   data-size
 * @return            status flag
 */
oled_status_t OLED_SendData (
                              const uint8_t* dataToSend,
                                    uint32_t dataSize
								                     // bool shouldApplyBlend
                            )
{
	oled_status_t
		spiStatus;

  if  (
		  	  ( GUI_COLOR_WHITE != colorMask )
		  // &&  ( true == shouldApplyBlend )
	    )
  {
	  uint16_t*
	  	  arrayPtr = (uint16_t*)dataToSend;

	  for( uint32_t i = 0; i < dataSize/2; i++ )
	  {
		  arrayPtr[i] &= colorMask;
	  }
  }

  if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_WRITERAM, FIRST_BYTE ) )
  {
      return OLED_STATUS_PROTOCOL_ERROR;
  }

  // sending data -> set DC pin
  GPIO_DRV_SetPinOutput( settings.DCpin );
  GPIO_DRV_ClearPinOutput( settings.CSpin );

  const uint8_t*
    // traversing pointer
    bufPtr = dataToSend;

  uint16_t
    // determine the number of chunks and the last chunk size to send
    numChunks      = dataSize / OLED_SPI_CHUNK,
    lastChunkSize  = dataSize % OLED_SPI_CHUNK;

  if ( numChunks > 0 )
  {
    for ( uint16_t i = 0; i < numChunks; i++)
    {
		spiStatus = SendViaSPI( bufPtr, OLED_SPI_CHUNK );

			if ( OLED_STATUS_SUCCESS == spiStatus )
			{
			  bufPtr += OLED_SPI_CHUNK;
			}

			else
			{
			  catch( CATCH_OLED );
			  GPIO_DRV_SetPinOutput( settings.CSpin );
			  return OLED_STATUS_PROTOCOL_ERROR;
			}
    }
  }

  if ( lastChunkSize > 0 )
  {
	  spiStatus = SendViaSPI( bufPtr, lastChunkSize );

		if ( OLED_STATUS_SUCCESS != spiStatus )
		{
		  catch( CATCH_OLED );
		  GPIO_DRV_SetPinOutput( settings.CSpin );
		  return OLED_STATUS_PROTOCOL_ERROR;
		}
  }

  GPIO_DRV_SetPinOutput( settings.CSpin );
  return OLED_STATUS_SUCCESS;
}

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
                          )
{
  oled_status_t
    status = OLED_STATUS_SUCCESS;

  oled_dynamic_area_t
	  boxArea;

  boxArea.xCrd   = xCrd;
  boxArea.yCrd   = yCrd;
  boxArea.width  = width;
  boxArea.height = height;

  uint32_t
    boxSize = width*height;

  OLED_SetDynamicArea( &boxArea );

  // helper pointer
  uint8_t*
    boxBuf = (uint8_t*)oled_dynamic_area.areaBuffer;

  if ( NULL == boxBuf )
  {
    catch(9);
    return OLED_STATUS_ERROR;
  }

  // check the bounds
  if AreCoordsNotValid( xCrd, yCrd, width, height )
  {
    status = OLED_STATUS_INIT_ERROR;
  }

  else
  {
    /** fill the buffer with color */

    for ( uint16_t i = 0; i < boxSize; i++ )
    {
      boxBuf[ 2*i ]     = color >> 8;
      boxBuf[ 2*i + 1 ] = color;
    }

    /** set the locations */

    // adjust for the offset
    OLED_AdjustColumnOffset(xCrd);
    OLED_AdjustRowOffset(yCrd);

    if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_SET_COLUMN, FIRST_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    if ( OLED_STATUS_SUCCESS != OLED_SendCmd( xCrd, OTHER_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    if ( OLED_STATUS_SUCCESS != OLED_SendCmd( xCrd + (width-1), OTHER_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }

    if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_SET_ROW, FIRST_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    if ( OLED_STATUS_SUCCESS != OLED_SendCmd( yCrd, OTHER_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    if ( OLED_STATUS_SUCCESS != OLED_SendCmd( yCrd + (height-1), OTHER_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }

    // fill the GRAM
    if ( OLED_STATUS_SUCCESS != OLED_SendData( (uint8_t*)boxBuf, boxSize*OLED_BYTES_PER_PIXEL ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }

    OLED_DestroyDynamicArea();
    status = OLED_STATUS_SUCCESS;
  }

  return status;
}

/**
 * fill the entire screen
 * @param  color color to fill with
 * @return status flag
 */
oled_status_t OLED_FillScreen( uint16_t color )
{
  /** fill the screen buffer with color */
  for ( uint16_t i = 0; i < ( OLED_SCREEN_WIDTH * OLED_SCREEN_HEIGHT ); i++ )
  {
    screenBuf[ 2*i ]     = color >> 8;
    screenBuf[ 2*i + 1 ] = color;
  }

  /** set the locations */
  SetBorders( 0, 0, OLED_SCREEN_WIDTH, OLED_SCREEN_HEIGHT );

  /** fill GRAM */
  if ( OLED_STATUS_SUCCESS != OLED_SendData( (uint8_t*)screenBuf, OLED_SCREEN_WIDTH * OLED_SCREEN_HEIGHT * OLED_BYTES_PER_PIXEL ) )
  {
      return OLED_STATUS_PROTOCOL_ERROR;
  }
  return OLED_STATUS_SUCCESS;
}

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
                            )
{
  // check the bounds
  if AreCoordsNotValid( xCrd, yCrd, 1, 1 )
  {
    return OLED_STATUS_INIT_ERROR;
  }

  else
  {
    // set directions
    SetBorders( xCrd, yCrd, OLED_SCREEN_WIDTH, OLED_SCREEN_HEIGHT);

    uint16_t
      // swap bytes
      dot = color;

    OLED_SwapMe(dot);

    // fill the GRAM
    if ( OLED_STATUS_SUCCESS != OLED_SendData( (uint8_t*)&dot, 2 ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    return OLED_STATUS_SUCCESS;
  }
}

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
                              )
{
  oled_status_t
    status = OLED_STATUS_SUCCESS;

  if AreCoordsNotValid( xCrd, yCrd, width, height )
  {
    return OLED_STATUS_INIT_ERROR;
  }

  switch ( transition )
  {
    case OLED_TRANSITION_NONE:        {
                                        /** set the locations */
                                        SetBorders( xCrd, yCrd, width, height );

                                        // fill the GRAM
                                        if ( OLED_STATUS_SUCCESS != OLED_SendData( (const uint8_t*)image, width * height * OLED_BYTES_PER_PIXEL ) )
                                        {
                                            return OLED_STATUS_PROTOCOL_ERROR;
                                        }
                                        break;
                                      }

    case OLED_TRANSITION_TOP_DOWN:    {
                                        TopDown( image, xCrd, yCrd, width, height );
                                        break;
                                      }

    case OLED_TRANSITION_DOWN_TOP:    {
                                        DownTop( image, xCrd, yCrd, width, height );
                                        break;
                                      }

    case OLED_TRANSITION_LEFT_RIGHT:  {
                                        LeftRight( image, xCrd, yCrd, width, height );
                                        break;
                                      }

    case OLED_TRANSITION_RIGHT_LEFT:  {
                                        RightLeft( image, xCrd, yCrd, width, height );
                                        break;
                                      }

    default: {}
  }

  return status;
}

/**
 * set the font to use
 * @param newFont  desired font
 * @param newColor desired color
 * @return         status flag
 */
oled_status_t OLED_SetFont(
                            const uint8_t* newFont,
                                  uint16_t newColor
                          )
{
  /** save the new values in intern variables */

  selectedFont           = newFont;
  // selectedFont_firstChar = newFont[2] + (newFont[3] << 8);
  selectedFont_firstChar = newFont[2] | ( (uint16_t)newFont[3] << 8 );
  // selectedFont_lastChar  = newFont[4] + (newFont[5] << 8);
  selectedFont_lastChar  = newFont[4] | ( (uint16_t)newFont[5] << 8 );
  selectedFont_height    = newFont[6];
  selectedFont_color     = newColor;

  OLED_SwapMe( selectedFont_color );

  isFontInitialized = 1;
  return OLED_STATUS_SUCCESS;
}

/**
 * set OLED dynamic area
 * @param dynamic_area data-structure with desired values
 */
void OLED_SetDynamicArea(oled_dynamic_area_t *dynamic_area)
{

  if( NULL == oled_dynamic_area.areaBuffer )
  {
	  oled_dynamic_area.areaBuffer = (oled_pixel_t)AllocateDynamicArea( dynamic_area->width * dynamic_area->height );
  }
  else if(
          ( dynamic_area->height != oled_dynamic_area.height ) ||
          ( dynamic_area->width != oled_dynamic_area.width )
         )
  {
    OLED_DestroyDynamicArea();
    oled_dynamic_area.areaBuffer = (oled_pixel_t)AllocateDynamicArea( dynamic_area->width * dynamic_area->height );
  }

  oled_dynamic_area.xCrd   = dynamic_area->xCrd;
  oled_dynamic_area.yCrd   = dynamic_area->yCrd;
  oled_dynamic_area.width  = dynamic_area->width;
  oled_dynamic_area.height = dynamic_area->height;
}

/**
 * destroy current OLED dynamic area
 */
void OLED_DestroyDynamicArea()
{
	if ( NULL != oled_dynamic_area.areaBuffer )
	{
		DestroyDynamicArea( oled_dynamic_area.areaBuffer );
		oled_dynamic_area.areaBuffer = NULL;
	}
}

/**
 * set OLED text properties
 * @param textProperties data-structure with desired properties
 */
void OLED_SetTextProperties(oled_text_properties_t *textProperties)
{
  oled_text_properties.font       = textProperties->font;
  oled_text_properties.fontColor  = textProperties->fontColor;
  oled_text_properties.alignParam = textProperties->alignParam;
  oled_text_properties.background = textProperties->background;

  OLED_SetFont( oled_text_properties.font, oled_text_properties.fontColor );
}

/**
 * return the width in [px] required for the given string to be displayed
 * @param  text desired string
 * @return      required text width in [px]
 */
uint8_t OLED_GetTextWidth(const uint8_t* text)
{
	uint8_t chrCnt = 0;
	uint8_t text_width  = 0;

	while ( 0 != text[chrCnt] )
	{
		text_width += *( selectedFont + 8 + (uint16_t)( ( text[chrCnt++] - selectedFont_firstChar ) << 2 ) );
		// make 1px space between chars
		text_width++;
	}
	// remove the final space
	text_width--;

	return text_width;
}

/**
 * count the characters
 * @param  width  text width
 * @param  font   text font
 * @param  text   given text string
 * @param  length text length
 * @return        character count
 */
uint8_t OLED_CharCount(uint8_t width, const uint8_t* font, const uint8_t* text, uint8_t length)
{
	uint8_t chrCnt = 0;
	uint8_t text_width  = 0;
	uint16_t firstChar;

	firstChar = font[2] | ( (uint16_t)font[3] << 8 );

	while ( chrCnt < length )
	{
		text_width += *( font + 8 + (uint16_t)( ( text[chrCnt++] - firstChar ) << 2 ) );
		if(text_width > width)
		{
			chrCnt--;
			break;
		}
		// make 1px space between chars
		text_width++;
	}

	return chrCnt;
}

/**
 * add text to the main screen buffer
 * @param  text text to add
 * @return      status flag
 */
oled_status_t OLED_AddText( const uint8_t* text )
{
	uint16_t
		chrCnt = 0;
	oled_pixel_t
		chrBuf = NULL;

	uint8_t
		currentChar_x = 0,
		currentChar_y = 0;

	uint8_t
		text_height = 0,
		text_width  = 0;

	text_width = OLED_GetTextWidth(text);

	/**
	 * set default values, if necessary
	 */

	text_height = selectedFont_height;

	if	(
				( oled_dynamic_area.width  < text_width )
			||  ( oled_dynamic_area.height < text_height )
		)
	{
		oled_dynamic_area_t
		  textArea;

		textArea.width  = text_width;
		textArea.height = text_height;
		OLED_SetDynamicArea( &textArea );
	}

		// oled_dynamic_area.width  = text_width;
		// oled_dynamic_area.height = text_height;
		// // malloc new text space
		// OLED_DestroyDynamicArea();
		// oled_dynamic_area.areaBuffer = (oled_pixel_t)AllocateDynamicArea( oled_dynamic_area.width  * oled_dynamic_area.height );

		// if ( NULL == oled_dynamic_area.areaBuffer )
		// {
		//   return OLED_STATUS_INIT_ERROR;
		// }

	currentChar_y = ( oled_dynamic_area.height - text_height ) >> 1;

	switch ( oled_text_properties.alignParam & OLED_TEXT_HALIGN_MASK )
	{
		case OLED_TEXT_ALIGN_LEFT:
		{
			currentChar_x = 0;
			break;
		}

		case OLED_TEXT_ALIGN_RIGHT:
		{
			currentChar_x = ( oled_dynamic_area.width - text_width );
			break;
		}

		case OLED_TEXT_ALIGN_CENTER:
		{
			currentChar_x += ( oled_dynamic_area.width - text_width ) >> 1 ;
			break;
		}

		case OLED_TEXT_ALIGN_NONE:
		{
			break;
		}

		default: {}
	}

	if ( CreateTextBackground() != OLED_STATUS_SUCCESS )
	{
		return OLED_STATUS_ERROR;
	}

	/**
	* write the characters into designated space, one by one
	*/

	chrCnt = 0;
	while ( 0 != text[chrCnt] )
	{
		WriteCharToBuf( text[chrCnt++], &chrBuf );

		if ( NULL == chrBuf )
		{
		  return OLED_STATUS_INIT_ERROR;
		}

		else
		{
		  if  (
						( ( currentChar_x + currentChar_width )  > oled_dynamic_area.width )
					||  ( ( currentChar_y + currentChar_height ) > oled_dynamic_area.height )
			  )
		  {
			DestroyDynamicArea( chrBuf );
			chrBuf = NULL;
			return OLED_STATUS_ERROR;
		  }

		  // copy data
		  oled_pixel_t
			  copyAddr = oled_dynamic_area.areaBuffer + ( currentChar_y * oled_dynamic_area.width + currentChar_x );
		  AddCharToTextArea( chrBuf, currentChar_width, currentChar_height, copyAddr, oled_dynamic_area.width );

		  currentChar_x += ( currentChar_width+1 );
		  currentChar_y += 0;

		  DestroyDynamicArea( chrBuf );
		  chrBuf = NULL;
		}
	}

	GuiDriver_UpdateScreen(
              							oled_dynamic_area.xCrd,
              							oled_dynamic_area.yCrd,
              							oled_dynamic_area.width,
              							oled_dynamic_area.height,
              							(const uint8_t*)oled_dynamic_area.areaBuffer
            						);

	return OLED_STATUS_SUCCESS;
}

/**
 * write text on OLED to given position
 * @param text desired text
 * @param x    x-coordinate for the given text
 * @param y    y-coordinate for the given text
 */
oled_status_t OLED_DrawText ( const uint8_t* text )
{

  if ( NULL == text )
  {
    return OLED_STATUS_ERROR;
  }

  OLED_AddText( text );

  // set the locations
  SetBorders( oled_dynamic_area.xCrd, oled_dynamic_area.yCrd, oled_dynamic_area.width, oled_dynamic_area.height );

  // fill the GRAM
  if ( OLED_STATUS_SUCCESS != OLED_SendData( (const uint8_t*)oled_dynamic_area.areaBuffer, oled_dynamic_area.width * oled_dynamic_area.height * OLED_BYTES_PER_PIXEL ) )
  {
      return OLED_STATUS_PROTOCOL_ERROR;
  }

//  free( currentTextAreaImage );
  return OLED_STATUS_SUCCESS;
}

/**
 * return given image dimensions
 * @param width  given image's width
 * @param height given image's height
 * @param image  desired image
 */
void OLED_GetImageDimensions(uint8_t *width, uint8_t *height, const uint8_t* image)
{
  *height = image[2] + (image[3] << 8);
  *width  = image[4] + (image[5] << 8);
}

/**
 * add image to the main screen buffer
 * @param  image      desired image
 * @return            status flag
 */
oled_status_t OLED_AddImage ( const uint8_t* image )
{
  oled_status_t
    status = OLED_STATUS_SUCCESS;

  // check the bounds
  if AreCoordsNotValid( oled_dynamic_area.xCrd, oled_dynamic_area.yCrd, oled_dynamic_area.width, oled_dynamic_area.height )
  {
    status = OLED_STATUS_INIT_ERROR;
  }

  else
  {
    OLED_Swap( (oled_pixel_t)oled_dynamic_area.areaBuffer, GuiDriver_SkipHeader(image), oled_dynamic_area.width*oled_dynamic_area.height );

    // update the main screen buffer
    GuiDriver_UpdateScreen( oled_dynamic_area.xCrd, oled_dynamic_area.yCrd, oled_dynamic_area.width, oled_dynamic_area.height, (const uint8_t *)oled_dynamic_area.areaBuffer );
  }

  return status;
}

/**
 * draw image, i.e. send image to OLED GRAM
 * @param  image      desired image
 * @param  transition desired transition style for the new image
 * @return            status flag
 */
oled_status_t OLED_DrawImage ( const uint8_t* image )
{
  OLED_AddImage( image );

  // set the locations
  SetBorders( oled_dynamic_area.xCrd, oled_dynamic_area.yCrd, oled_dynamic_area.width, oled_dynamic_area.height );

  // fill the GRAM
  if ( OLED_STATUS_SUCCESS != OLED_SendData( (const uint8_t*)oled_dynamic_area.areaBuffer, oled_dynamic_area.width * oled_dynamic_area.height * OLED_BYTES_PER_PIXEL ) )
  {
      return OLED_STATUS_PROTOCOL_ERROR;
  }

  return OLED_STATUS_SUCCESS;
}

/**
 * set borders for the box-like object to draw
 * @param  xCrd   x-coordinate for the object
 * @param  yCrd   y-coordinate for the object
 * @param  width  object's width
 * @param  height object's height
 */
static void SetBorders(
                        uint8_t xCrd,
                        uint8_t yCrd,
                        uint8_t width,
                        uint8_t height
                      )
{
  // adjust for the offset
  OLED_AdjustColumnOffset(xCrd);
  OLED_AdjustRowOffset(yCrd);

  oled_status_t
    oledStatus;

  while (1)
  {
    oledStatus = OLED_STATUS_SUCCESS;

    oledStatus |= OLED_SendCmd( OLED_CMD_SET_COLUMN, FIRST_BYTE );
    oledStatus |= OLED_SendCmd( xCrd, OTHER_BYTE );
    oledStatus |= OLED_SendCmd( xCrd + (width-1), OTHER_BYTE );
    oledStatus |= OLED_SendCmd( OLED_CMD_SET_ROW, FIRST_BYTE );
    oledStatus |= OLED_SendCmd( yCrd, OTHER_BYTE );
    oledStatus |= OLED_SendCmd( yCrd + (height-1), OTHER_BYTE );

    if ( OLED_STATUS_SUCCESS == oledStatus)
    {
      break;
    }
  }
}

/**
 * dim OLED screen on
 */
void OLED_DimScreenON()
{
    for ( int i = 0; i < 16; i++ )
    {
        OLED_SendCmd( OLED_CMD_CONTRASTMASTER, FIRST_BYTE );
        OLED_SendCmd( 0xC0 | (0xF-i), OTHER_BYTE );
        OSA_TimeDelay( 20 );
    }
}

/**
 * return OLED back to full contrast
 */
void OLED_DimScreenOFF()
{
  OLED_SendCmd( OLED_CMD_CONTRASTMASTER, FIRST_BYTE );
  OLED_SendCmd( 0xC0 | 0xF, OTHER_BYTE );
}

/** intern functions */

/**
 * write the character
 * @param charToWrite character to be written
 * @param chrBuf      given pointer for buffer for the character
 */
static void WriteCharToBuf(
                            uint16_t charToWrite,
                            oled_pixel_t* chrBuf
                          )
{
  uint8_t
    foo = 0,
    mask;

  const uint8_t*
    pChTable = selectedFont + 8 + (uint16_t)( ( charToWrite - selectedFont_firstChar ) << 2 );

  currentChar_width  = *pChTable,
  currentChar_height = selectedFont_height;

  uint32_t
    offset =      (uint32_t)pChTable[1]
              | ( (uint32_t)pChTable[2] << 8 )
              | ( (uint32_t)pChTable[3] << 16 );

  const uint8_t*
    pChBitMap = selectedFont + offset;

  if ( 0 == isFontInitialized )
  {
    // default font
    OLED_SetFont( guiFont_Tahoma_8_Regular, 0xFFFF );
  }

  // allocate space for char image
  *chrBuf = (oled_pixel_t)AllocateDynamicArea( currentChar_height * currentChar_width );

  if ( NULL == *chrBuf )
  {
    return;
  }

  for ( uint8_t yCnt = 0; yCnt < currentChar_height; yCnt++ )
  {
    mask = 0;

    for ( uint8_t xCnt = 0; xCnt < currentChar_width; xCnt++ )
    {
      if ( 0 == mask )
      {
        mask = 1;
        foo  = *pChBitMap++;
      }

      if ( 0 != ( foo & mask ) )
      {
        *( *chrBuf + yCnt*currentChar_width + xCnt ) = selectedFont_color;
      }

       else
       {
           *( *chrBuf + yCnt*currentChar_width + xCnt ) = 0;
       }

      mask <<= 1;
    }
  }
}

/**
 * transpose the image
 * @param image      given image
 * @param transImage new image
 */
static void Transpose(
                             oled_pixel_t transImage,
                       const oled_pixel_t image,
                                  uint8_t width,
                                  uint8_t height
                     )
{
  for ( uint8_t i = 0; i < height; i++ )
  {
    for ( uint8_t j = 0; j < width ; j++ )
    {
      transImage[ j*height + i ] = image[ i*width + j ];
    }
  }
}

/**
 * top-down transition
 * @param  image  given image
 * @param  xCrd   image's x-coordinate
 * @param  yCrd   image's y-coordinate
 * @param  width  image's width
 * @param  height image's height
 * @return        status flag
 */
static oled_status_t TopDown(
                                const uint8_t* image,
                                       uint8_t xCrd,
                                       uint8_t yCrd,
                                       uint8_t width,
                                       uint8_t height
                            )
{
  uint16_t
    transStep = OLED_TRANSITION_STEP;

  uint16_t
    partImgSize = width*transStep;

  oled_status_t
    status = OLED_STATUS_SUCCESS;

  uint8_t*
    partImgPtr = (uint8_t*)image + ( height - transStep ) * ( width * OLED_BYTES_PER_PIXEL );

  /**
   * set locations
   */

  while (1)
  {
    SetBorders( xCrd, yCrd, width, height );

    if ( partImgSize > width*height )
    {
      if ( OLED_STATUS_SUCCESS != OLED_SendData( (const uint8_t*)image, width * height * OLED_BYTES_PER_PIXEL ) )
      {
          return OLED_STATUS_PROTOCOL_ERROR;
      }
      break;
    }
    else
    {
      if ( OLED_STATUS_SUCCESS != OLED_SendData( (const uint8_t*)partImgPtr, partImgSize * OLED_BYTES_PER_PIXEL ) )
      {
          return OLED_STATUS_PROTOCOL_ERROR;
      }
    }

    if ( OLED_STATUS_SUCCESS != status )
    {
      return status;
    }

    /**
     * update variables
     */

    partImgPtr  -= ( width * transStep ) * OLED_BYTES_PER_PIXEL;
    partImgSize += ( width * transStep );
    transStep++;
  }

  return status;
}

/**
 * down-top transition
 * @param  image  given image
 * @param  xCrd   image's x-coordinate
 * @param  yCrd   image's y-coordinate
 * @param  width  image's width
 * @param  height image's height
 * @return        status flag
 */
static oled_status_t DownTop(
                                const uint8_t* image,
                                      uint8_t xCrd,
                                      uint8_t yCrd,
                                      uint8_t width,
                                      uint8_t height
                            )
{
  uint16_t
    transStep = OLED_TRANSITION_STEP;

  uint16_t
    partImgSize = width*transStep;

  oled_status_t
    status = OLED_STATUS_SUCCESS;

  uint8_t*
    partImgPtr = (uint8_t*)image;

  uint8_t
    yCrd_moving = ( yCrd + height ) - 1;

  /**
   * set locations
   */

  while (1)
  {
    if  (
             ( partImgSize > OLED_SCREEN_SIZE )
          ||        ( yCrd_moving < yCrd )
        )
    {
      // draw full image
      SetBorders( xCrd, yCrd, width, height );
      if ( OLED_STATUS_SUCCESS != OLED_SendData( (const uint8_t*)image, width * height * OLED_BYTES_PER_PIXEL ) )
      {
          return OLED_STATUS_PROTOCOL_ERROR;
      }
      break;
    }

    else
    {
      SetBorders( xCrd, yCrd_moving, width, ( yCrd + height ) - yCrd_moving );
      if ( OLED_STATUS_SUCCESS != OLED_SendData( (const uint8_t*)partImgPtr, partImgSize * OLED_BYTES_PER_PIXEL ) )
      {
          return OLED_STATUS_PROTOCOL_ERROR;
      }
    }

    /**
     * update variables
     */

    yCrd_moving -= transStep;
    partImgSize += ( width * transStep );
    transStep++;
  }

  return status;
}

/**
 * left-right transition
 * @param  image  given image
 * @param  xCrd   image's x-coordinate
 * @param  yCrd   image's y-coordinate
 * @param  width  image's width
 * @param  height image's height
 * @return        status flag
 */
static oled_status_t LeftRight(
                                 const uint8_t* image,
                                        uint8_t xCrd,
                                        uint8_t yCrd,
                                        uint8_t width,
                                        uint8_t height
                              )
{
  oled_status_t
    status = OLED_STATUS_SUCCESS;

  oled_dynamic_area_t
  	  transImageArea =
  	  {
		  .xCrd = 0,
		  .yCrd = 0,

		  .width = 96,
		  .height= 96
  	  };

  OLED_SetDynamicArea( &transImageArea );

  // helper pointer
  oled_pixel_t
    transImage = (oled_pixel_t)oled_dynamic_area.areaBuffer;

  if ( NULL == transImage )
  {
    return OLED_STATUS_INIT_ERROR;
  }

  Transpose( (oled_pixel_t)transImage, (const oled_pixel_t)image, width, height );

  if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_SET_REMAP, FIRST_BYTE ) )
  {
      return OLED_STATUS_PROTOCOL_ERROR;
  }
  if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_REMAP_SETTINGS | REMAP_VERTICAL_INCREMENT, OTHER_BYTE ) )
  {
      return OLED_STATUS_PROTOCOL_ERROR;
  }

  uint16_t
    transStep = OLED_TRANSITION_STEP;

  uint16_t
    partImgSize = height*transStep;

  uint8_t*
    partImgPtr = (uint8_t*)transImage + ( width - transStep ) * ( height * OLED_BYTES_PER_PIXEL );

  /**
   * set locations
   */

  while (1)
  {
    SetBorders( xCrd, yCrd, width, height );

    if ( partImgSize > width*height )
    {
      if ( OLED_STATUS_SUCCESS != OLED_SendData( (const uint8_t*)transImage, width * height * OLED_BYTES_PER_PIXEL ) )
      {
          return OLED_STATUS_PROTOCOL_ERROR;
      }
      break;
    }
    else
    {
      if ( OLED_STATUS_SUCCESS != OLED_SendData( (const uint8_t*)partImgPtr, partImgSize * OLED_BYTES_PER_PIXEL ) )
      {
          return OLED_STATUS_PROTOCOL_ERROR;
      }
    }

    if ( OLED_STATUS_SUCCESS == status )
    {
    	/**
		 * update variables
		 */

		partImgPtr  -= ( transStep * height ) * OLED_BYTES_PER_PIXEL;
		partImgSize += ( transStep * height );
		transStep++;
    }
  }

  if ( OLED_STATUS_SUCCESS == status )
  {
	  if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_SET_REMAP, FIRST_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
	  if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_REMAP_SETTINGS, OTHER_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
  }

  OLED_DestroyDynamicArea();
  return status;
}

/**
 * right-left transition
 * @param  image  given image
 * @param  xCrd   image's x-coordinate
 * @param  yCrd   image's y-coordinate
 * @param  width  image's width
 * @param  height image's height
 * @return        status flag
 */
static oled_status_t RightLeft(
                                 const uint8_t* image,
                                        uint8_t xCrd,
                                        uint8_t yCrd,
                                        uint8_t width,
                                        uint8_t height
                              )
{
  oled_dynamic_area_t
  	  transImageArea =
  	  {
		  .xCrd = 0,
		  .yCrd = 0,

		  .width = 96,
		  .height= 96
  	  };

  OLED_SetDynamicArea( &transImageArea );

  // helper pointer
  oled_pixel_t
    transImage = oled_dynamic_area.areaBuffer;

  if ( NULL == transImage )
  {
    return OLED_STATUS_INIT_ERROR;
  }

  Transpose( (oled_pixel_t)transImage, (const oled_pixel_t)image, width, height );

  if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_SET_REMAP, FIRST_BYTE ) )
  {
      return OLED_STATUS_PROTOCOL_ERROR;
  }
  if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_REMAP_SETTINGS | REMAP_VERTICAL_INCREMENT, OTHER_BYTE ) )
  {
      return OLED_STATUS_PROTOCOL_ERROR;
  }

  uint16_t
    transStep = OLED_TRANSITION_STEP;

  uint16_t
    partImgSize = height * transStep;

  uint8_t*
    partImgPtr = (uint8_t*)transImage;

  uint8_t
    xCrd_moving = ( xCrd + width ) - 1;

  /** set locations */

  while (1)
  {
    if  (
             ( partImgSize > width*height )
          ||        ( xCrd_moving < xCrd )
        )
    {
      SetBorders( xCrd, yCrd, width, height );
       if ( OLED_STATUS_SUCCESS != OLED_SendData( (const uint8_t*)transImage, height * width * OLED_BYTES_PER_PIXEL ) )
       {
          return OLED_STATUS_PROTOCOL_ERROR;
       }
      break;
    }

    else
    {
      SetBorders( xCrd_moving, yCrd, ( xCrd + width ) - xCrd_moving, height );
       if ( OLED_STATUS_SUCCESS != OLED_SendData( (const uint8_t*)partImgPtr, partImgSize * OLED_BYTES_PER_PIXEL ) )
       {
          return OLED_STATUS_PROTOCOL_ERROR;
       }
    }

    /** update variables*/

    xCrd_moving -= transStep;
    partImgSize += ( height * transStep );
    transStep++;
  }

  if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_SET_REMAP, FIRST_BYTE ) )
  {
      return OLED_STATUS_PROTOCOL_ERROR;
  }
  if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_REMAP_SETTINGS, OTHER_BYTE ) )
  {
      return OLED_STATUS_PROTOCOL_ERROR;
  }

//  DestroyDynamicArea( transImage );

  OLED_DestroyDynamicArea();

  return OLED_STATUS_SUCCESS;
}

/**
 * spap image's bytes per pixel to obtain the correct color format
 * @param imgDst  desired image
 * @param imgSrc  original image
 * @param imgSize image's size
 */
void OLED_Swap(
                    oled_pixel_t imgDst,
                  const uint8_t* imgSrc,
                        uint16_t imgSize
                )
{
  for ( int var = 0; var < imgSize; var++ )
  {
    *imgDst = *imgSrc << 8;
    imgSrc++;
    *imgDst |= *imgSrc;
    imgDst++;
    imgSrc++;
  }
}

/**
 * create the buffer for a partial image and fill it
 * with the chosen background
 * @return status flag
 */
static oled_status_t CreateTextBackground()
{
  uint8_t
    xCrd   = oled_dynamic_area.xCrd,
    yCrd   = oled_dynamic_area.yCrd,
    width  = oled_dynamic_area.width,
    height = oled_dynamic_area.height;

  oled_pixel_t
    imgBuf = oled_dynamic_area.areaBuffer,
    copyAddr;

  const uint8_t*
    background = oled_text_properties.background;

  /** copy data */

  if  (
            ( NULL == imgBuf )
        ||  ( ( xCrd + width )  > OLED_SCREEN_WIDTH )
        ||  ( ( yCrd + height ) > OLED_SCREEN_HEIGHT )
      )
  {
    return OLED_STATUS_INIT_ERROR;
  }

  if ( NULL == background )
  {
    for ( uint8_t i = 0; i < height; i++ )
    {
      memset( (void*)imgBuf, 0, width*OLED_BYTES_PER_PIXEL );
      imgBuf   += width;
    }
  }

  else
  {
    copyAddr = (oled_pixel_t)( GuiDriver_SkipHeader( background ) ) + ( yCrd*OLED_SCREEN_WIDTH + xCrd );
    for ( uint8_t i = 0; i < height; i++ )
    {
      OLED_Swap( (oled_pixel_t)imgBuf, (const uint8_t*)copyAddr, width );
      imgBuf   += width;
      copyAddr += OLED_SCREEN_WIDTH;
    }
  }

  return OLED_STATUS_SUCCESS;
}

/**
 * add subimage/character to the active image buffer
 * @param  xOffset offset for the x-coordinate
 * @param  yOffset offset for the y-coordinate
 * @param  width   desired width
 * @param  height  desired height
 * @return         status flag
 */
static oled_status_t AddCharToTextArea(
                                        oled_pixel_t chrPtr,
                                             uint8_t chrWidth,
                                             uint8_t chrHeight,

                                        oled_pixel_t copyAddr,
                                             uint8_t imgWidth
                                      )
{
  if ( NULL == copyAddr )
  {
    return OLED_STATUS_INIT_ERROR;
  }

  for ( uint8_t i = 0; i < chrHeight; i++ )
  {
    for ( uint8_t j = 0; j < chrWidth; j++ )
    {
      if ( 0 != chrPtr[j] )
      {
          copyAddr[j] = chrPtr[j];
      }
    }
    copyAddr += imgWidth;
    chrPtr   += chrWidth;
  }
  return OLED_STATUS_SUCCESS;
}

/**
 * allocate memory for the desired image/character
 * @param area desired area dimensions
 */
static void* AllocateDynamicArea( uint32_t area )
{
  void*
  	  ptr = OSA_MemAlloc( area * OLED_BYTES_PER_PIXEL );

  if ( NULL == ptr )
  {
	  catch( CATCH_MEM_ALLOC );
	  return NULL;
  }

  return ptr;
}


/**
 * deallocate current area
 * @param area pointer to current area
 */
static oled_status_t DestroyDynamicArea( void* ptr )
{
  if ( NULL == ptr )
  {
	  catch ( CATCH_MEM_ALLOC );
	  return OLED_STATUS_INIT_ERROR;
  }

  if( kStatus_OSA_Success != OSA_MemFree(ptr) )
  {
	  catch( CATCH_MEM_ALLOC );
	  return OLED_STATUS_ERROR;
  }
  else
  {
	  return OLED_STATUS_SUCCESS;
  }
}

/**
 * assert the SPI bus and send data
 * @param  bufPtr pointer to data
 * @param  txSize data-size
 * @return        status flag
 */
static oled_status_t SendViaSPI (
                                    const uint8_t* bufPtr,
                                          uint32_t txSize
                                )
{
	oled_status_t
		status = OLED_STATUS_SUCCESS;

	genericSpiHandle_t
		spiProtocol = self.protocol;

    osa_status_t
        mutexStatus = OSA_MutexLock( &spiAccessMutex, OSA_WAIT_FOREVER );

    if ( kStatus_OSA_Success == mutexStatus )
    {
        dspi_status_t
            spiStatus = DSPI_DRV_EdmaMasterTransferBlocking (
                                                                spiProtocol.instance,
                                                                NULL,

                                                                bufPtr,
                                                                NULL,

                                                                txSize,

                                                                spiProtocol.timeout
                                                            );

        if ( kStatus_DSPI_Success != spiStatus )
        {
        	catch( CATCH_OLED );
            status = OLED_STATUS_PROTOCOL_ERROR;
        }
        else
        {
        	status = OLED_STATUS_SUCCESS;
        }
    }

    else
    {
    	catch( CATCH_MUTEX );
    	status = OLED_STATUS_INIT_ERROR;

    }

    OSA_MutexUnlock( &spiAccessMutex );
    return status;
}

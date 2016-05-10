/**
 * OLED driver functions
 * Project HEXIWEAR, 2015
 */

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

#include "GPIO.h"

/**
 * macros and consts
 */
#define REMAP_SETTINGS ( REMAP_ORDER_ABC | REMAP_COM_SPLIT_ODD_EVEN_EN | REMAP_COLOR_RGB565 | REMAP_COLUMNS_LEFT_TO_RIGHT | REMAP_SCAN_UP_TO_DOWN | REMAP_HORIZONTAL_INCREMENT )

#define OLED_AdjustRowOffset(x)    x += OLED_ROW_OFFSET
#define OLED_AdjustColumnOffset(x) x += OLED_COLUMN_OFFSET

#define checkLimits( x, y, w, h ) ( ( (x+w-1) > OLED_SCREEN_WIDTH_END ) || ( x < OLED_COLUMN_OFFSET ) || ( (y+h-1) > OLED_SCREEN_HEIGHT_END ) || ( y < OLED_ROW_OFFSET ) )
#define areCoordsValid( x, y, w, h )    ( 0 == checkLimits( x, y, w ,h ) )
#define areCoordsNotValid( x, y, w, h ) ( 0 != checkLimits( x, y, w, h ) )

/**
 * intern variables
 */

static handleOLED_t
  self;
static settingsOLED_t
  settings;

/**
 * intern functions
 */

/**
 * [setDirection description]
 * @param  self [description]
 * @param  xCrd [description]
 * @param  yCrd [description]
 * @return      [description]
 */
static statusOLED_t goTo(
                          uint16_t xCrd,
                          uint16_t yCrd,
                           uint8_t direction
                        )
{
  statusOLED_t
    status = STATUS_OLED_SUCCESS;

  switch ( direction )
  {
    case OLED_DIRECTION_HORIZONTAL: {
                                      status |= OLED_SendCmd( OLED_CMD_SET_COLUMN, FIRST_BYTE );
                                      status |= OLED_SendCmd( xCrd, OTHER_BYTE );
                                      status |= OLED_SendCmd( OLED_SCREEN_WIDTH_END, OTHER_BYTE );

                                      status |= OLED_SendCmd( OLED_CMD_SET_ROW, FIRST_BYTE );
                                      status |= OLED_SendCmd( yCrd, OTHER_BYTE );
                                      status |= OLED_SendCmd( OLED_SCREEN_HEIGHT_END, OTHER_BYTE );
                                    }

    case OLED_DIRECTION_VERTICAL:  {}

    default: {}
  }

  return status;
}

/**
 * [drawImage_topDown description]
 * @param  self  [description]
 * @param  image [description]
 * @param  xCrd  [description]
 * @param  yCrd  [description]
 * @return       [description]
 */
static statusOLED_t drawImage_topDown (
                                          const uint8_t* image,
                                                uint16_t xCrd,
                                                uint16_t yCrd
                                      )
{
  uint16_t
    transStep = OLED_TRAN_STEP;

  uint16_t
    partImgSize = OLED_SCREEN_WIDTH*transStep;

  statusOLED_t
    status = STATUS_OLED_SUCCESS;

  uint8_t*
    partImgPtr = (uint8_t*)image + (OLED_SCREEN_WIDTH*OLED_BYTES_PER_PIXEL) * (OLED_SCREEN_HEIGHT-transStep);

  /**
   * set locations
   */

  OLED_AdjustColumnOffset(xCrd);
  OLED_AdjustRowOffset(yCrd);

  while (1)
  {
    status = goTo( xCrd, yCrd, OLED_DIRECTION_HORIZONTAL );

    if ( STATUS_OLED_SUCCESS != status )
    {
      return status;
    }

    else
    {
      /**
       * fill the GRAM
       */

      status |= OLED_SendData( (uint8_t*)partImgPtr, partImgSize*OLED_BYTES_PER_PIXEL );
    }

    /**
     * update variables
     */

    partImgPtr  -= (OLED_SCREEN_WIDTH*OLED_BYTES_PER_PIXEL)*transStep;
    partImgSize += OLED_SCREEN_WIDTH*transStep;
    transStep++;

    if ( partImgSize > OLED_SCREEN_SIZE )
    {
      // draw full picture, just to be sure
      status = goTo( OLED_COLUMN_OFFSET, OLED_ROW_OFFSET, OLED_DIRECTION_HORIZONTAL );
      if ( STATUS_OLED_SUCCESS != status )
      {
        return status;
      }

      else
      {
        /**
         * fill the GRAM
         */

        status |= OLED_SendData( (uint8_t*)image, OLED_SCREEN_SIZE*OLED_BYTES_PER_PIXEL );
        break;
      }
    }
  }

  return status;
}

/**
 * [drawImage_topDown description]
 * @param  self  [description]
 * @param  image [description]
 * @param  xCrd  [description]
 * @param  yCrd  [description]
 * @return       [description]
 */
static statusOLED_t drawImage_downTop (
                                          const uint8_t* image,
                                                uint16_t xCrd,
                                                uint16_t yCrd
                                      )
{
  uint16_t
    transStep = OLED_TRAN_STEP;

  uint16_t
    partImgSize = OLED_SCREEN_WIDTH*transStep;

  statusOLED_t
    status = STATUS_OLED_SUCCESS;

  uint8_t*
    partImgPtr = (uint8_t*)image;

  /**
   * set locations
   */

  OLED_AdjustColumnOffset(xCrd);
  OLED_AdjustRowOffset(yCrd);

  while (1)
  {
    status = goTo( xCrd, yCrd, OLED_DIRECTION_HORIZONTAL );

    if ( STATUS_OLED_SUCCESS != status )
    {
      return status;
    }

    else
    {
      /**
       * fill the GRAM
       */

      status |= OLED_SendData( (uint8_t*)partImgPtr, partImgSize*OLED_BYTES_PER_PIXEL );
    }

    /**
     * update variables
     */

    yCrd -= transStep;
    partImgSize += OLED_SCREEN_WIDTH*transStep;
    transStep++;

    if  (
             ( partImgSize > OLED_SCREEN_SIZE )
          || ( yCrd < 0 )
        )
    {
      // draw full picture, just to be sure
      status = goTo( OLED_COLUMN_OFFSET, OLED_ROW_OFFSET, OLED_DIRECTION_HORIZONTAL );
      if ( STATUS_OLED_SUCCESS != status )
      {
        return status;
      }

      else
      {
        /**
         * fill the GRAM
         */

        status |= OLED_SendData( (uint8_t*)image, OLED_SCREEN_SIZE*OLED_BYTES_PER_PIXEL );
        break;
      }
    }
  }

  return status;
}

/**
 * [transpose description]
 * @param image      [description]
 * @param transImage [description]
 */
static void transpose(
                       const uint16_t* image,
                             uint16_t* transImage
                     )
{
  for (int i = 0; i < OLED_SCREEN_WIDTH; ++i)
  {
    for (int j = 0; j < OLED_SCREEN_HEIGHT; ++j)
    {
      transImage[ i + j*OLED_SCREEN_WIDTH ] = image[ j + i*OLED_SCREEN_HEIGHT ];
    }
  }
}

static uint8_t
  transImage[ OLED_GRAM_SIZE ];

/**
 * [drawImage_leftRight  description]
 * @param  self  [description]
 * @param  image [description]
 * @param  xCrd  [description]
 * @param  yCrd  [description]
 * @return       [description]
 */
static statusOLED_t drawImage_leftRight (
                                           const uint8_t* image,
                                                 uint16_t xCrd,
                                                 uint16_t yCrd
                                        )
{
  statusOLED_t
    status = STATUS_OLED_SUCCESS;

  transpose( (const uint16_t*)image, (uint16_t*)transImage );

  status |= OLED_SendCmd( OLED_CMD_SET_REMAP, FIRST_BYTE );
  status |= OLED_SendCmd( REMAP_SETTINGS | REMAP_VERTICAL_INCREMENT, OTHER_BYTE );

  drawImage_topDown ( transImage, xCrd, yCrd );

  status |= OLED_SendCmd( OLED_CMD_SET_REMAP, FIRST_BYTE );
  status |= OLED_SendCmd( REMAP_SETTINGS, OTHER_BYTE );

  return status;
}

/**
 * [drawImage_rightLeft  description]
 * @param  self  [description]
 * @param  image [description]
 * @param  xCrd  [description]
 * @param  yCrd  [description]
 * @return       [description]
 */
static statusOLED_t drawImage_rightLeft (
                                           const uint8_t* image,
                                                 uint16_t xCrd,
                                                 uint16_t yCrd
                                        )
{
  statusOLED_t
    status = STATUS_OLED_SUCCESS;

  transpose( (const uint16_t*)image, (uint16_t*)transImage );

  status |= OLED_SendCmd( OLED_CMD_SET_REMAP, FIRST_BYTE );
  status |= OLED_SendCmd( REMAP_SETTINGS | REMAP_VERTICAL_INCREMENT, OTHER_BYTE );

  // drawImage_downTop( self, transImage, xCrd, yCrd );

  uint16_t
    transStep = OLED_TRAN_STEP;

  uint16_t
    partImgSize = OLED_SCREEN_WIDTH*transStep;

  uint8_t*
    partImgPtr = (uint8_t*)transImage;

  /**
   * set locations
   */

  OLED_AdjustColumnOffset(xCrd);
  OLED_AdjustRowOffset(yCrd);

  while (1)
  {
    status = goTo( xCrd, yCrd, OLED_DIRECTION_HORIZONTAL );

    if ( STATUS_OLED_SUCCESS != status )
    {
      return status;
    }

    else
    {
      /**
       * fill the GRAM
       */

      status |= OLED_SendData( (uint8_t*)partImgPtr, partImgSize*OLED_BYTES_PER_PIXEL );
    }

    /**
     * update variables
     */

    xCrd -= transStep;
    partImgSize += OLED_SCREEN_HEIGHT*transStep;
    transStep++;

    if  (
             ( partImgSize > OLED_SCREEN_SIZE )
          || ( xCrd < 0 )
        )
    {
      // draw full picture, just to be sure
      status = goTo( OLED_COLUMN_OFFSET, OLED_ROW_OFFSET, OLED_DIRECTION_HORIZONTAL );
      if ( STATUS_OLED_SUCCESS != status )
      {
        return status;
      }

      else
      {
        /**
         * fill the GRAM
         */

        status |= OLED_SendData( (uint8_t*)transImage, OLED_SCREEN_SIZE*OLED_BYTES_PER_PIXEL );
        break;
      }
    }
  }

  status |= OLED_SendCmd( OLED_CMD_SET_REMAP, FIRST_BYTE );
  status |= OLED_SendCmd( REMAP_SETTINGS, OTHER_BYTE );

  return status;
}


/**
 * initialize OLED screen
 * @param  self     [description]
 * @param  settings [description]
 * @return          [description]
 */
statusOLED_t OLED_Init(
                          handleOLED_t* oledHandle,
                        settingsOLED_t* oledSettings
                      )
{
  statusSPI_t
    status = SPI_Init( &(oledHandle->protocol) );

  if ( STATUS_SPI_SUCCESS != status )
  {
    catch(10);
    return STATUS_OLED_PROTOCOL_ERROR;
  }

  else
  {
    /**
     * inititalize intern OLED structures,
     * which will be used from now on
     */

    memcpy( (void*)&self,     (void*)oledHandle,   sizeof(self) );
    memcpy( (void*)&settings, (void*)oledSettings, sizeof(settings) );

    status = STATUS_OLED_SUCCESS;

    GPIO_DRV_ClearPinOutput( settings.ENpin );
    OSA_TimeDelay(1);
    GPIO_DRV_ClearPinOutput( settings.RSTpin );
    OSA_TimeDelay(1);
    GPIO_DRV_SetPinOutput( settings.RSTpin );
    OSA_TimeDelay(1);
    GPIO_DRV_SetPinOutput( settings.ENpin );

    status |= OLED_SendCmd( OLED_CMD_SET_CMD_LOCK, FIRST_BYTE );
    status |= OLED_SendCmd( OLED_UNLOCK, OTHER_BYTE );

    status |= OLED_SendCmd( OLED_CMD_SET_CMD_LOCK, FIRST_BYTE );
    status |= OLED_SendCmd( OLED_ACC_TO_CMD_YES, OTHER_BYTE );

    status |= OLED_SendCmd( OLED_CMD_DISPLAYOFF, FIRST_BYTE );

    status |= OLED_SendCmd( OLED_CMD_SET_OSC_FREQ_AND_CLOCKDIV, FIRST_BYTE );
    status |= OLED_SendCmd( 0xF1, OTHER_BYTE );

    status |= OLED_SendCmd( OLED_CMD_SET_MUX_RATIO, FIRST_BYTE );
    status |= OLED_SendCmd( 0x5F, OTHER_BYTE );

    status |= OLED_SendCmd( OLED_CMD_SET_REMAP, FIRST_BYTE );
    status |= OLED_SendCmd( REMAP_SETTINGS, OTHER_BYTE );

    status |= OLED_SendCmd( OLED_CMD_SET_COLUMN, FIRST_BYTE );
    status |= OLED_SendCmd( 0x00, OTHER_BYTE );
    status |= OLED_SendCmd( 0x5F, OTHER_BYTE );

    status |= OLED_SendCmd( OLED_CMD_SET_ROW, FIRST_BYTE );
    status |= OLED_SendCmd( 0x00, OTHER_BYTE );
    status |= OLED_SendCmd( 0x5F, OTHER_BYTE );

    status |= OLED_SendCmd( OLED_CMD_STARTLINE, FIRST_BYTE );
    status |= OLED_SendCmd( 0x80, OTHER_BYTE );

    status |= OLED_SendCmd( OLED_CMD_DISPLAYOFFSET, FIRST_BYTE );
    status |= OLED_SendCmd( 0x60, OTHER_BYTE );

    status |= OLED_SendCmd( OLED_CMD_PRECHARGE, FIRST_BYTE );
    status |= OLED_SendCmd( 0x32, FIRST_BYTE );

    status |= OLED_SendCmd( OLED_CMD_VCOMH, FIRST_BYTE );
    status |= OLED_SendCmd( 0x05, FIRST_BYTE );

    status |= OLED_SendCmd( OLED_CMD_NORMALDISPLAY, FIRST_BYTE );

    status |= OLED_SendCmd( OLED_CMD_CONTRASTABC, FIRST_BYTE );
    status |= OLED_SendCmd( 0xC8, OTHER_BYTE );
    status |= OLED_SendCmd( 0xC0, OTHER_BYTE );
//    status |= OLED_SendCmd( 0xC8, OTHER_BYTE );
    status |= OLED_SendCmd( 0xC0, OTHER_BYTE );
//    status |= OLED_SendCmd( 0xC8, OTHER_BYTE );
    status |= OLED_SendCmd( 0xC0, OTHER_BYTE );

    status |= OLED_SendCmd( OLED_CMD_CONTRASTMASTER, FIRST_BYTE );
//    status |= OLED_SendCmd( 0xCF, OTHER_BYTE );
    status |= OLED_SendCmd( 0xC0, OTHER_BYTE );

    status |= OLED_SendCmd( OLED_CMD_SETVSL, FIRST_BYTE );
    status |= OLED_SendCmd( 0xA0, OTHER_BYTE );
    status |= OLED_SendCmd( 0xB5, OTHER_BYTE );
    status |= OLED_SendCmd( 0x55, OTHER_BYTE );

    status |= OLED_SendCmd( OLED_CMD_PRECHARGE2, FIRST_BYTE );
    status |= OLED_SendCmd( 0x01, OTHER_BYTE );

    status |= OLED_SendCmd( OLED_CMD_DISPLAYON, FIRST_BYTE );

    return status;
  }
}

/**
 * [OLED_Deinit description]
 * @param  self [description]
 * @return      [description]
 */
statusOLED_t OLED_Deinit()
{
  return SPI_Deinit( &(self.protocol) );
}

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
  status = DSPI_DRV_EdmaMasterTransferBlocking(
                                                spiProtocol.instance,
                                                NULL,

                                                txBuf,
                                                NULL,

                                                txSize,

                                                spiProtocol.timeout
                                              );
  GPIO_DRV_SetPinOutput( settings.CSpin );


  if ( kStatus_DSPI_Success != status )
  {
    catch(8);
    return STATUS_OLED_PROTOCOL_ERROR;
  }
  else
  {
    return STATUS_OLED_SUCCESS;
  }
}

/**
 * send data to OLED
 * @param dataToSend [description]
 */
statusOLED_t OLED_SendData(
                            const uint8_t* dataToSend,
                                  uint32_t dataSize
                          )
{
  genericSpiHandle_t
    spiProtocol = self.protocol;

  dspi_status_t
    status;

  status = OLED_SendCmd( OLED_CMD_WRITERAM, FIRST_BYTE );

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
      status |= DSPI_DRV_EdmaMasterTransferBlocking (
                                                      spiProtocol.instance,
                                                      NULL,

                                                      (uint8_t*)bufPtr,
                                                      NULL,

                                                      OLED_SPI_CHUNK,

                                                      spiProtocol.timeout
                                                    );
      bufPtr += OLED_SPI_CHUNK;
    }
  }

  if ( lastChunkSize > 0 )
  {
    status |= DSPI_DRV_EdmaMasterTransferBlocking (
                                                    spiProtocol.instance,
                                                    NULL,

                                                    (uint8_t*)bufPtr,
                                                    NULL,

                                                    lastChunkSize,

                                                    spiProtocol.timeout
                                                  );
  }
  GPIO_DRV_SetPinOutput( settings.CSpin );

  if ( kStatus_DSPI_Success != status )
  {
    catch(8);
    return STATUS_OLED_PROTOCOL_ERROR;
  }
  else
  {
    return STATUS_OLED_SUCCESS;
  }
}

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
                          )
{
  statusOLED_t
    status = STATUS_OLED_SUCCESS;

  uint16_t
    boxSize = width*height;

  uint8_t*
    boxBuf = NULL;

  // adjust for the offset
  OLED_AdjustColumnOffset(xCrd);
  OLED_AdjustRowOffset(yCrd);

  boxBuf = (uint8_t*)malloc( boxSize*OLED_BYTES_PER_PIXEL );
  if ( NULL == boxBuf )
  {
    catch(9);
    return STATUS_OLED_ERROR;
  }

  // check the bounds
  if areCoordsNotValid( xCrd, yCrd, width, height )
  {
    status = STATUS_OLED_INIT_ERROR;
  }

  else
  {
    /**
     * fill the buffer with color
     */

    for ( uint16_t i = 0; i < boxSize; i++ )
    {
      boxBuf[ 2*i ]     = color >> 8;
      boxBuf[ 2*i + 1 ] = color;
    }

    /**
     * set the locations
     */

    status |= OLED_SendCmd( OLED_CMD_SET_COLUMN, FIRST_BYTE );
    status |= OLED_SendCmd( xCrd, OTHER_BYTE );
    status |= OLED_SendCmd( xCrd + (width-1), OTHER_BYTE );

    status |= OLED_SendCmd( OLED_CMD_SET_ROW, FIRST_BYTE );
    status |= OLED_SendCmd( yCrd, OTHER_BYTE );
    status |= OLED_SendCmd( yCrd + (height-1), OTHER_BYTE );

    if ( STATUS_OLED_SUCCESS != status )
    {
      status = STATUS_OLED_PROTOCOL_ERROR;
    }

    else
    {
      // fill the GRAM
      status |= OLED_SendData( (uint8_t*)boxBuf, boxSize*OLED_BYTES_PER_PIXEL );
    }
  }

  free( (void*)boxBuf );
  return status;
}

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
                            )
{
  statusOLED_t
   status = STATUS_OLED_SUCCESS;

  // adjust for the offset
  OLED_AdjustColumnOffset(xCrd);
  OLED_AdjustRowOffset(yCrd);

  // check the bounds
  if areCoordsNotValid( xCrd, yCrd, 1, 1 )
  {
    return STATUS_OLED_INIT_ERROR;
  }

  else
  {
    // set directions
    goTo( xCrd, yCrd, OLED_DIRECTION_HORIZONTAL );

    uint16_t
      // swap bytes
      dot;

    swapMe(dot);

    // fill the GRAM
    status |= OLED_SendData( (uint8_t*)&dot, 2 );
  }

  return status;
}

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
                            )
{
  statusOLED_t
    status = STATUS_OLED_SUCCESS;

  switch ( transition )
  {
    case OLED_TRANSITION_NONE:  {
                                  /**
                                   * set the locations
                                   */

                                  status = goTo( OLED_COLUMN_OFFSET, OLED_ROW_OFFSET, OLED_DIRECTION_HORIZONTAL );

                                  if ( STATUS_OLED_SUCCESS == status )
                                  {
                                    // fill the GRAM
                                    status |= OLED_SendData( (const uint8_t*)image, OLED_GRAM_SIZE );
                                  }
                                  break;
                                }

    case OLED_TRANSITION_TOP_DOWN:    {
                                        drawImage_topDown( image, 0, 0 );
                                        break;
                                      }

    case OLED_TRANSITION_DOWN_TOP:    {
                                        drawImage_downTop( image, 0, 95 );
                                        break;
                                      }

    case OLED_TRANSITION_LEFT_RIGHT:  {
                                        drawImage_leftRight( image, 0, 0 );
                                        break;
                                      }

    case OLED_TRANSITION_RIGHT_LEFT:  {
                                        drawImage_rightLeft( image, 95, 0 );
                                        break;
                                      }

    default: {}
  }

  return status;
}

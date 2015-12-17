/**
 * OLED driver functions
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

#include "apps_resources.h"

#include "menu_driver.h"
#include "menu_defs.h"

/**
 * pen's info
 */

static uint8_t
  fontInitialized = 0;

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
  oled_text_properties = {
		  .alignParam = OLED_TEXT_ALIGN_CENTER,
		  .background = NULL
  };



static uint8_t
  screenBuf[ OLED_SCREEN_WIDTH * OLED_SCREEN_HEIGHT * OLED_BYTES_PER_PIXEL ];

static uint8_t
  currentChar_width  = 0,
  currentChar_height = 0;

#include "GPIO.h"

/**
 * macros and consts
 */
#define OLED_REMAP_SETTINGS ( REMAP_ORDER_ABC | REMAP_COM_SPLIT_ODD_EVEN_EN | REMAP_COLOR_RGB565 | REMAP_COLUMNS_LEFT_TO_RIGHT | REMAP_SCAN_UP_TO_DOWN | REMAP_HORIZONTAL_INCREMENT )

#define OLED_AdjustRowOffset(y)    y += OLED_ROW_OFFSET
#define OLED_AdjustColumnOffset(x) x += OLED_COLUMN_OFFSET

#define CheckLimits( x, y, w, h ) ( ( ( x + w ) > OLED_SCREEN_WIDTH ) || ( x < 0 ) || ( ( y + h ) > OLED_SCREEN_HEIGHT ) || ( y < 0 ) )
#define AreCoordsValid( x, y, w, h )    ( 0 == CheckLimits( x, y, w ,h ) )
#define AreCoordsNotValid( x, y, w, h ) ( 0 != CheckLimits( x, y, w, h ) )

/**
 * intern variables
 */

static handleOLED_t
  self;
static settingsOLED_t
  settings;

/* Pointer to runtime state structure.*/
extern void * g_dspiStatePtr[SPI_INSTANCE_COUNT];

/**
 * intern functions' declarations
 */
// static void WriteChar ( uint16_t charToWrite );
static void Transpose ( oled_pixel_t transImage, const oled_pixel_t image, uint8_t width, uint8_t height );

static oled_status_t RightLeft ( const uint8_t* image, uint8_t xCrd, uint8_t yCrd, uint8_t width, uint8_t height );
static oled_status_t LeftRight ( const uint8_t* image, uint8_t xCrd, uint8_t yCrd, uint8_t width, uint8_t height );
static oled_status_t DownTop   ( const uint8_t* image, uint8_t xCrd, uint8_t yCrd, uint8_t width, uint8_t height );
static oled_status_t TopDown   ( const uint8_t* image, uint8_t xCrd, uint8_t yCrd, uint8_t width, uint8_t height );

static void SetBorders( uint8_t xCrd, uint8_t yCrd, uint8_t width, uint8_t height );

/**
 * Public API
 */

/**
 * create the buffer for a partial image
 * @param  imgBuf [description]
 * @param  width  [description]
 * @param  height [description]
 * @return        [description]
 */
static oled_status_t OLED_CreateTextBackground()
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

  /**
   * copy data
   */

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
    copyAddr = (oled_pixel_t)( menuDriver_screen.image ) + ( yCrd*OLED_SCREEN_WIDTH + xCrd );
    for ( uint8_t i = 0; i < height; i++ )
    {
      memcpy( (void*)imgBuf, (void*)copyAddr, width*OLED_BYTES_PER_PIXEL );
      imgBuf   += width;
      copyAddr += OLED_SCREEN_WIDTH;
    }
  }

  else
  {
    copyAddr = (oled_pixel_t)( MenuDriver_SkipHeader( background ) ) + ( yCrd*OLED_SCREEN_WIDTH + xCrd );
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
 * add subimage to the active image buffer
 * @param  xOffset [description]
 * @param  yOffset [description]
 * @param  width   [description]
 * @param  height  [description]
 * @return         [description]
 */
static oled_status_t OLED_AddCharToTextArea(
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
 * initialize OLED screen
 * @param  self     [description]
 * @param  settings [description]
 * @return          [description]
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
    catch(10);
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

    /**
     * set IRQ priority
     */

    NVIC_SetPriority( HEXIWEAR_OLED_SPI_IRQn,    HEXIWEAR_OLED_SPI_IRQ_PRIO );
    NVIC_SetPriority( HEXIWEAR_OLED_DMA_RX_IRQn, HEXIWEAR_OLED_DMA_RX_IRQ_PRIO );
    NVIC_SetPriority( HEXIWEAR_OLED_DMA_TX_IRQn, HEXIWEAR_OLED_DMA_TX_IRQ_PRIO );

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
    status |= OLED_SendCmd( OLED_REMAP_SETTINGS, OTHER_BYTE );

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
    status |= OLED_SendCmd( 0x8A, OTHER_BYTE );
    status |= OLED_SendCmd( 0x51, OTHER_BYTE );
    status |= OLED_SendCmd( 0x8A, OTHER_BYTE );

    status |= OLED_SendCmd( OLED_CMD_CONTRASTMASTER, FIRST_BYTE );
    status |= OLED_SendCmd( 0xCF, OTHER_BYTE );

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
oled_status_t OLED_Deinit()
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
oled_status_t OLED_SendCmd (
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
    return OLED_STATUS_PROTOCOL_ERROR;
  }
  else
  {
    return OLED_STATUS_SUCCESS;
  }
}

/**
 * send data to OLED
 * @param dataToSend [description]
 */
oled_status_t OLED_SendData(
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

                                                      (const uint8_t*)bufPtr,
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

                                                    (const uint8_t*)bufPtr,
                                                    NULL,

                                                    lastChunkSize,

                                                    spiProtocol.timeout
                                                  );
  }
  GPIO_DRV_SetPinOutput( settings.CSpin );

  if ( kStatus_DSPI_Success != status )
  {
    catch(8);
    return OLED_STATUS_PROTOCOL_ERROR;
  }
  else
  {
    return OLED_STATUS_SUCCESS;
  }
}

/**
 * [OLED_DrawBox  description]
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
                          )
{
  oled_status_t
    status = OLED_STATUS_SUCCESS;

  uint16_t
    boxSize = width*height;

  uint8_t*
    boxBuf = NULL;

  boxBuf = (uint8_t*)malloc( boxSize*OLED_BYTES_PER_PIXEL*sizeof( *boxBuf ) );
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

    // adjust for the offset
    OLED_AdjustColumnOffset(xCrd);
    OLED_AdjustRowOffset(yCrd);

    status |= OLED_SendCmd( OLED_CMD_SET_COLUMN, FIRST_BYTE );
    status |= OLED_SendCmd( xCrd, OTHER_BYTE );
    status |= OLED_SendCmd( xCrd + (width-1), OTHER_BYTE );

    status |= OLED_SendCmd( OLED_CMD_SET_ROW, FIRST_BYTE );
    status |= OLED_SendCmd( yCrd, OTHER_BYTE );
    status |= OLED_SendCmd( yCrd + (height-1), OTHER_BYTE );

    if ( OLED_STATUS_SUCCESS != status )
    {
      status = OLED_STATUS_PROTOCOL_ERROR;
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
 * fill the entire screen
 * @param  color color to fill with
 * @return       status flag
 */
oled_status_t OLED_FillScreen(
                              uint16_t color
                            )
{
  /**
   * fill the screen buffer with color
   */

  for ( uint16_t i = 0; i < ( OLED_SCREEN_WIDTH * OLED_SCREEN_HEIGHT ); i++ )
  {
    screenBuf[ 2*i ]     = color >> 8;
    screenBuf[ 2*i + 1 ] = color;
  }

  /**
   * set the locations
   */
  SetBorders( 0, 0, OLED_SCREEN_WIDTH_END, OLED_SCREEN_HEIGHT_END );
  // fill the GRAM
  return OLED_SendData( (uint8_t*)screenBuf, OLED_SCREEN_WIDTH * OLED_SCREEN_HEIGHT * OLED_BYTES_PER_PIXEL );
}

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
                            )
{
  oled_status_t
   status = OLED_STATUS_SUCCESS;



  // check the bounds
  if AreCoordsNotValid( xCrd, yCrd, 1, 1 )
  {
    return OLED_STATUS_INIT_ERROR;
  }

  else
  {
    // set directions
    SetBorders( xCrd, yCrd, OLED_SCREEN_WIDTH_END, OLED_SCREEN_HEIGHT_END );

    uint16_t
      // swap bytes
      dot = color;

    OLED_SwapMe(dot);

    // fill the GRAM
//    status |= OLED_SendData( (uint8_t*)&dot, 2 );

//    OLED_SendCmd( OLED_CMD_WRITERAM, FIRST_BYTE );
//    GPIO_DRV_SetPinOutput( settings.DCpin );
//    GPIO_DRV_ClearPinOutput( settings.CSpin );

    dspi_status_t
      pixelStatus = kStatus_DSPI_Success;
    uint32_t
      framesNum;
    uint8_t
      cmd[1] = { OLED_CMD_WRITERAM };

    // send cmd
    GPIO_DRV_ClearPinOutput( settings.DCpin );
    GPIO_DRV_ClearPinOutput( settings.CSpin );
    DSPI_DRV_EdmaMasterTransfer( self.protocol.instance, NULL, (const uint8_t*)cmd, NULL, ArraySize(cmd) );

    while (1)
    {
      pixelStatus = DSPI_DRV_EdmaMasterGetTransferStatus( self.protocol.instance, &framesNum );

      if ( kStatus_DSPI_Success ==  pixelStatus )
      {
        GPIO_DRV_SetPinOutput( settings.CSpin );
        break;
      }
    }

    // send data
    GPIO_DRV_SetPinOutput  ( settings.DCpin );
    GPIO_DRV_ClearPinOutput( settings.CSpin );
    DSPI_DRV_EdmaMasterTransfer( self.protocol.instance, NULL, (const uint8_t*)&dot, NULL, sizeof(dot) );

    while (1)
    {
      pixelStatus = DSPI_DRV_EdmaMasterGetTransferStatus( self.protocol.instance, &framesNum );
      if ( kStatus_DSPI_Success ==  pixelStatus )
      {
        GPIO_DRV_SetPinOutput( settings.CSpin );
        break;
      }
    }
  }

  return status;
}

/**
 * [OLED_DrawScreen  description]
 * @param  image      [description]
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
                                        /**
                                         * set the locations
                                         */

                                        SetBorders( xCrd, yCrd, width, height );

                                        // fill the GRAM
                                        status |= OLED_SendData( (const uint8_t*)image, width * height * OLED_BYTES_PER_PIXEL );
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
 * @param activeFont [description]
 * @param newColor [description]
 */
oled_status_t OLED_SetFont (
                            const uint8_t* newFont,
                                  uint16_t newColor
                          )
{
  /**
   * save the new values in intern variables
   */

  selectedFont           = newFont;
  // selectedFont_firstChar = newFont[2] + (newFont[3] << 8);
  selectedFont_firstChar = newFont[2] | ( (uint16_t)newFont[3] << 8 );
  // selectedFont_lastChar  = newFont[4] + (newFont[5] << 8);
  selectedFont_lastChar  = newFont[4] | ( (uint16_t)newFont[5] << 8 );
  selectedFont_height    = newFont[6];
  selectedFont_color     = newColor;

  OLED_SwapMe( selectedFont_color );

  fontInitialized = 1;
  return OLED_STATUS_SUCCESS;
}

///**
// * [MoveCursor description]
// * @param x [description]
// * @param y [description]
// */
//static void MoveCursor(
//                        uint16_t xPos,
//                        uint16_t yPos
//                        )
//{
//  selectedPos_x = xPos;
//  selectedPos_y = yPos;
//}

/**
 * write the character
 * @param charToWrite character to be written
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

  if ( 0 == fontInitialized )
  {
    // default font
    OLED_SetFont( appsFont_Tahoma11x13_Regular, 0xFFFF );
  }

  // allocate space for char image
  *chrBuf = (oled_pixel_t)calloc( currentChar_height * currentChar_width, sizeof( **chrBuf ) );

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

// /**
//  * write character on the screen
//  * @param charToWrite [description]
//  * @param xPos        [description]
//  * @param yPos        [description]
//  */
// statusOLED_t OLED_WriteChar (
//                               uint16_t charToWrite,
//                               uint16_t xPos,
//                               uint16_t yPos
//                             )
// {
//   MoveCursor( xPos, yPos );
// //  WriteCharToBuf( charToWrite );
//   return STATUS_OLED_SUCCESS;
// }

void OLED_SetDynamicArea(oled_dynamic_area_t *dynamic_area)
{
    if(
    		(dynamic_area->height != oled_dynamic_area.height) &&
    		(dynamic_area->width != oled_dynamic_area.width)
    	 )
	{

		OLED_DestroyDynamicArea();
		oled_dynamic_area.areaBuffer = (oled_pixel_t)malloc(dynamic_area->width * dynamic_area->height * OLED_BYTES_PER_PIXEL);
	}

    oled_dynamic_area.xCrd = dynamic_area->xCrd;
	oled_dynamic_area.yCrd = dynamic_area->yCrd;
	oled_dynamic_area.width = dynamic_area->width;
	oled_dynamic_area.height = dynamic_area->height;
}

void OLED_DestroyDynamicArea(void)
{
	if ( NULL != oled_dynamic_area.areaBuffer )
	{
		free( oled_dynamic_area.areaBuffer );
		oled_dynamic_area.areaBuffer = NULL;
	}
}

void OLED_SetTextProperties(oled_text_properties_t *textProperties)
{
	oled_text_properties.font = textProperties->font;
	oled_text_properties.fontColor = textProperties->fontColor;
    oled_text_properties.alignParam = textProperties->alignParam;
	oled_text_properties.background = textProperties->background;

	OLED_SetFont( oled_text_properties.font, oled_text_properties.fontColor );
}

oled_status_t OLED_AddText(
                            const uint8_t* text
                          )
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

	while ( 0 != text[chrCnt] )
	{
	text_width += *( selectedFont + 8 + (uint16_t)( ( text[chrCnt++] - selectedFont_firstChar ) << 2 ) );
	// make 1px space between chars
	text_width++;
	}
	// remove the final space
	text_width--;

	/**
	 * set default values, if necessary
	 */

	text_height = selectedFont_height;

	if ( oled_dynamic_area.width < text_width )
	{
		oled_dynamic_area.width = text_width;
	}

	if ( oled_dynamic_area.height < text_height )
	{
		oled_dynamic_area.height = text_height;
	}

	currentChar_y = ( oled_dynamic_area.height - text_height ) >> 1;

	switch ( oled_text_properties.alignParam & OLED_TEXT_HALIGN_MASK )
	{

	case OLED_TEXT_ALIGN_RIGHT:  {
									currentChar_x = ( oled_dynamic_area.width - text_width );
									break;
								  }

	case OLED_TEXT_ALIGN_LEFT:   {
									currentChar_x = 0;
									break;
								  }

	case OLED_TEXT_ALIGN_CENTER: {
									currentChar_x += ( oled_dynamic_area.width - text_width ) >> 1 ;
									break;
								  }

	case OLED_TEXT_ALIGN_NONE:    {
									break;
								  }

	default: {}
	}


	if ( OLED_STATUS_SUCCESS != OLED_CreateTextBackground() )
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
				( ( currentChar_x + currentChar_width ) > oled_dynamic_area.width )
			|| ( ( currentChar_y + currentChar_height ) > oled_dynamic_area.height )
		  )
	  {
            return OLED_STATUS_ERROR;
	  }

	  // copy data
	  oled_pixel_t
		copyAddr = oled_dynamic_area.areaBuffer + ( currentChar_y * oled_dynamic_area.width + currentChar_x );
	  OLED_AddCharToTextArea( chrBuf, currentChar_width, currentChar_height, copyAddr, oled_dynamic_area.width );

	  currentChar_x += ( currentChar_width+1 );
	  currentChar_y += 0;

	  free( chrBuf );
	  chrBuf = NULL;
	}
	}

	MenuDriver_UpdateScreen( oled_dynamic_area.xCrd, oled_dynamic_area.yCrd, oled_dynamic_area.width, oled_dynamic_area.height, (const uint8_t*)oled_dynamic_area.areaBuffer );
	return OLED_STATUS_SUCCESS;
}

/**
 * write text on current position
 * @param text [description]
 * @param x    [description]
 * @param y    [description]
 */
oled_status_t OLED_DrawText (
                              const uint8_t* text
                            )
{
  OLED_AddText( text );

  // set the locations
  SetBorders( oled_dynamic_area.xCrd, oled_dynamic_area.yCrd, oled_dynamic_area.width, oled_dynamic_area.height );

  // fill the GRAM
  OLED_SendData( (const uint8_t*)oled_dynamic_area.areaBuffer, oled_dynamic_area.width * oled_dynamic_area.height * OLED_BYTES_PER_PIXEL );

//  free( currentTextAreaImage );
  return OLED_STATUS_SUCCESS;
}

void OLED_GetImageDimensions(uint8_t *width, uint8_t *height, const uint8_t* image)
{
	*height = image[2] + (image[3] << 8);
	*width  = image[4] + (image[5] << 8);
}


/**
 * [OLED_DrawImage description]
 * @param  xCrd       [description]
 * @param  yCrd       [description]
 * @param  width      [description]
 * @param  height     [description]
 * @param  image      [description]
 * @param  transition [description]
 * @return            [description]
 */
oled_status_t OLED_AddImage (
                              const uint8_t* image
                            )
{
  oled_status_t
    status = OLED_STATUS_SUCCESS;
//  uint8_t
//    width,
//    height;

//  height = image[2] + (image[3] << 8);
//  width  = image[4] + (image[5] << 8);

  // check the bounds
  if AreCoordsNotValid( oled_dynamic_area.xCrd, oled_dynamic_area.yCrd, oled_dynamic_area.width, oled_dynamic_area.height )
  {
    status = OLED_STATUS_INIT_ERROR;
  }

  else
  {
    OLED_Swap( (oled_pixel_t)oled_dynamic_area.areaBuffer, MenuDriver_SkipHeader(image), oled_dynamic_area.width*oled_dynamic_area.height );

    // update the main screen buffer
    MenuDriver_UpdateScreen( oled_dynamic_area.xCrd, oled_dynamic_area.yCrd, oled_dynamic_area.width, oled_dynamic_area.height, (const uint8_t *)oled_dynamic_area.areaBuffer );
  }

  return status;
}

/**
 * [OLED_DrawImage description]
 * @param  xCrd       [description]
 * @param  yCrd       [description]
 * @param  width      [description]
 * @param  height     [description]
 * @param  image      [description]
 * @param  transition [description]
 * @return            [description]
 */
oled_status_t OLED_DrawImage (
                              const uint8_t* image
                            )
{
  OLED_AddImage( image );

  // set the locations
  SetBorders( oled_dynamic_area.xCrd, oled_dynamic_area.yCrd, oled_dynamic_area.width, oled_dynamic_area.height );

  // fill the GRAM
  OLED_SendData( (const uint8_t*)oled_dynamic_area.areaBuffer, oled_dynamic_area.width * oled_dynamic_area.height * OLED_BYTES_PER_PIXEL );

  return OLED_STATUS_SUCCESS;
}

/**
 * [setDirection description]
 * @param  self [description]
 * @param  xCrd [description]
 * @param  yCrd [description]
 * @return      [description]
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

  OLED_SendCmd( OLED_CMD_SET_COLUMN, FIRST_BYTE );
  OLED_SendCmd( xCrd, OTHER_BYTE );
  OLED_SendCmd( xCrd + (width-1), OTHER_BYTE );

  OLED_SendCmd( OLED_CMD_SET_ROW, FIRST_BYTE );
  OLED_SendCmd( yCrd, OTHER_BYTE );
  OLED_SendCmd( yCrd + (height-1), OTHER_BYTE );
}

/**
 * intern functions
 */

/**
 * [transpose description]
 * @param image      [description]
 * @param transImage [description]
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
 * [drawImage_topDown description]
 * @param  self  [description]
 * @param  image [description]
 * @param  xCrd  [description]
 * @param  yCrd  [description]
 * @return       [description]
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
      status |= OLED_SendData( (const uint8_t*)image, width * height * OLED_BYTES_PER_PIXEL );
      break;
    }
    else
    {
      status |= OLED_SendData( (const uint8_t*)partImgPtr, partImgSize * OLED_BYTES_PER_PIXEL );
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
 * [drawImage_topDown description]
 * @param  self  [description]
 * @param  image [description]
 * @param  xCrd  [description]
 * @param  yCrd  [description]
 * @return       [description]
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
      status |= OLED_SendData( (const uint8_t*)image, width * height * OLED_BYTES_PER_PIXEL );
      break;
    }

    else
    {
      SetBorders( xCrd, yCrd_moving, width, ( yCrd + height ) - yCrd_moving );
      status |= OLED_SendData( (const uint8_t*)partImgPtr, partImgSize * OLED_BYTES_PER_PIXEL );
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
 * [drawImage_leftRight  description]
 * @param  self  [description]
 * @param  image [description]
 * @param  xCrd  [description]
 * @param  yCrd  [description]
 * @return       [description]
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

  oled_pixel_t
    transImage = (oled_pixel_t)malloc( width * height * OLED_BYTES_PER_PIXEL );

  if ( NULL == transImage )
  {
    return OLED_STATUS_INIT_ERROR;
  }

  Transpose( (oled_pixel_t)transImage, (const oled_pixel_t)image, width, height );

  status |= OLED_SendCmd( OLED_CMD_SET_REMAP, FIRST_BYTE );
  status |= OLED_SendCmd( OLED_REMAP_SETTINGS | REMAP_VERTICAL_INCREMENT, OTHER_BYTE );

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
      status |= OLED_SendData( (const uint8_t*)transImage, width * height * OLED_BYTES_PER_PIXEL );
      break;
    }
    else
    {
      status |= OLED_SendData( (const uint8_t*)partImgPtr, partImgSize * OLED_BYTES_PER_PIXEL );
    }

    if ( OLED_STATUS_SUCCESS != status )
    {
      return status;
    }

    /**
     * update variables
     */

    partImgPtr  -= ( transStep * height ) * OLED_BYTES_PER_PIXEL;
    partImgSize += ( transStep * height );
    transStep++;
  }

  status |= OLED_SendCmd( OLED_CMD_SET_REMAP, FIRST_BYTE );
  status |= OLED_SendCmd( OLED_REMAP_SETTINGS, OTHER_BYTE );

  free( transImage );
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
static oled_status_t RightLeft(
                                 const uint8_t* image,
                                        uint8_t xCrd,
                                        uint8_t yCrd,
                                        uint8_t width,
                                        uint8_t height
                              )
{
  oled_status_t
    status = OLED_STATUS_SUCCESS;

  oled_pixel_t
    transImage = (oled_pixel_t)malloc( width * height * OLED_BYTES_PER_PIXEL );

  if ( NULL == transImage )
  {
    return OLED_STATUS_INIT_ERROR;
  }

  Transpose( (oled_pixel_t)transImage, (const oled_pixel_t)image, width, height );

  status |= OLED_SendCmd( OLED_CMD_SET_REMAP, FIRST_BYTE );
  status |= OLED_SendCmd( OLED_REMAP_SETTINGS | REMAP_VERTICAL_INCREMENT, OTHER_BYTE );

  uint16_t
    transStep = OLED_TRANSITION_STEP;

  uint16_t
    partImgSize = height * transStep;

  uint8_t*
    partImgPtr = (uint8_t*)transImage;

  uint8_t
    xCrd_moving = ( xCrd + width ) - 1;

  /**
   * set locations
   */

  while (1)
  {
    if  (
             ( partImgSize > width*height )
          ||        ( xCrd_moving < xCrd )
        )
    {
      SetBorders( xCrd, yCrd, width, height );
      status |= OLED_SendData( (const uint8_t*)transImage, height * width * OLED_BYTES_PER_PIXEL );
      break;
    }

    else
    {
      SetBorders( xCrd_moving, yCrd, ( xCrd + width ) - xCrd_moving, height );
      status |= OLED_SendData( (const uint8_t*)partImgPtr, partImgSize * OLED_BYTES_PER_PIXEL );
    }

    /**
     * update variables
     */

    xCrd_moving -= transStep;
    partImgSize += ( height * transStep );
    transStep++;
  }

  status |= OLED_SendCmd( OLED_CMD_SET_REMAP, FIRST_BYTE );
  status |= OLED_SendCmd( OLED_REMAP_SETTINGS, OTHER_BYTE );

  free( transImage );
  return status;
}

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

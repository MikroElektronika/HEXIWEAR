#include "OLED_driver.h"
#include "OLED_info.h"

#define NULL (void*)0

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

static oled_text_properties_t oled_text_properties;

static uint8_t
  screenBuf[ OLED_GRAM_SIZE ];

static uint8_t
  currentChar_width  = 0,
  currentChar_height = 0;

static uint16_t FontColor;
static uint8_t FontOrientation;
const uint8_t FO_HORIZONTAL = 0;
const uint8_t FO_VERTICAL = 1;
const uint8_t FO_VERTICAL_COLUMN = 2;
char ExternalFontSet;
static uint8_t FontInitialized = 0;

static code const uint8_t *_font;
static uint16_t _fontFirstChar; // First character in the font table.
static uint16_t _fontLastChar; // Last character in the font table.
static uint16_t _fontHeight;

//uint16_t _red, _green, _blue;
static uint16_t x_cord, y_cord;

// Serial Flash Chip Select connection
sbit OLED_Pwr_bit           at PTC_PDOR.B13;
sbit OLED_DC_bit            at PTD_PDOR.B15;
sbit OLED_RST_bit           at PTE_PDOR.B6;
sbit OLED_CS_bit            at PTB_PDOR.B20;

/**
 * macros and consts
 */
#define OLED_REMAP_SETTINGS ( REMAP_ORDER_ABC | REMAP_COM_SPLIT_ODD_EVEN_EN | REMAP_COLOR_RGB565 | REMAP_COLUMNS_LEFT_TO_RIGHT | REMAP_SCAN_UP_TO_DOWN | REMAP_HORIZONTAL_INCREMENT )

#define OLED_AdjustRowOffset(y)    y += OLED_ROW_OFFSET
#define OLED_AdjustColumnOffset(x) x += OLED_COLUMN_OFFSET

#define CheckLimits( x, y, w, h ) ( ( ( x + w - 1 ) > OLED_SCREEN_WIDTH ) || ( x < 0 ) || ( ( y + h - 1 ) > OLED_SCREEN_HEIGHT ) || ( y < 0 ) )
#define AreCoordsValid( x, y, w, h )    ( 0 == CheckLimits( x, y, w ,h ) )
#define AreCoordsNotValid( x, y, w, h ) ( 0 != CheckLimits( x, y, w, h ) )

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////


static void SetBorders(uint8_t xCrd, uint8_t yCrd, uint8_t width, uint8_t height);
static void OLED_Swap(oled_pixel_t imgDst, const uint8_t* imgSrc, uint16_t imgSize);

static void OLED_WriteChar(uint16_t ch);
static void OLED_MoveCursor(uint16_t _x, uint16_t _y);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

void OLED_PowerOn(void)
{
    OLED_Pwr_bit = 1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

void OLED_PowerOff(void)
{
    OLED_Pwr_bit = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
    if ( isFirst )
    {
        OLED_DC_bit = 0;
    }
    else
    {
        OLED_DC_bit = 1;
    }

    OLED_CS_bit = 0;

    SPI2_Write((uint8_t)cmd);

    OLED_CS_bit = 1;
    
    return OLED_STATUS_SUCCESS;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * initialize OLED screen
 * @param  self     [description]
 * @param  settings [description]
 * @return          [description]
 */
 
oled_status_t OLED_Init(void)
{
    oled_text_properties.alignParam = OLED_TEXT_ALIGN_CENTER;
    oled_text_properties.background = NULL;
    
    GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_13);
    GPIO_Digital_Output(&PTD_PDOR, _GPIO_PINMASK_15);
    GPIO_Digital_Output(&PTE_PDOR, _GPIO_PINMASK_6);
    GPIO_Digital_Output(&PTB_PDOR, _GPIO_PINMASK_20);

    SPI2_Init_Advanced(18000000, _SPI_CFG_MASTER | _SPI_CFG_SELECT_CTAR0 | _SPI_CFG_FRAME_SIZE_8BITS |
                       _SPI_CFG_CLK_IDLE_HIGH | _SPI_CFG_CLK_PHASE_CHG_LEADING | _SPI_CFG_MSB_FIRST, &_GPIO_Module_SPI2_PB21_23_22);
    PORTB_PCR21bits.DSE = 1;
    PORTB_PCR22bits.DSE = 1;
    PORTB_PCR23bits.DSE = 1;

    /**
     * power sequence
     */
    OLED_PowerOff();
    Delay_1ms();
    OLED_RST_bit = 0;
    Delay_1ms();
    OLED_RST_bit = 1;
    Delay_1ms();
    OLED_PowerOn();

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

    return OLED_STATUS_SUCCESS;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * send data to OLED
 * @param dataToSend [description]
 */
oled_status_t OLED_SendData(
                            const uint8_t* dataToSend,
                                  uint32_t dataSize
                          )
{
    oled_status_t spiStatus;
    const uint8_t* bufPtr;

    if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_WRITERAM, FIRST_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }

    // sending data -> set DC pin
    OLED_DC_bit = 1;
    OLED_CS_bit = 0;

    bufPtr = dataToSend;

    while(dataSize--)
    {
        SPI2_Write(*(bufPtr++));
    }

    OLED_CS_bit = 1;
    return OLED_STATUS_SUCCESS;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
    oled_status_t status = OLED_STATUS_SUCCESS;
    uint32_t boxSize;

    boxSize = width*height;

    // check the bounds
    if (AreCoordsNotValid(xCrd, yCrd, width, height))
    {
        status = OLED_STATUS_INIT_ERROR;
    }
    else
    {
        /**
         * fill the buffer with color
         */
        uint16_t cnt;

        /**
         * set the locations
         */

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

        if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_WRITERAM, FIRST_BYTE ) )
        {
            return OLED_STATUS_PROTOCOL_ERROR;
        }
        // fill the GRAM
        OLED_DC_bit = 1;
        OLED_CS_bit = 0;
        for(cnt = 0; cnt < boxSize; cnt++)
        {
            SPI2_Write((uint8_t)(color >> 8));
            SPI2_Write((uint8_t)color);
        }
        OLED_CS_bit = 1;
        
        status = OLED_STATUS_SUCCESS;
    }

  return status;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * fill the entire screen
 * @param  color color to fill with
 * @return       status flag
 */
oled_status_t OLED_FillScreen( uint16_t color )
{
    return OLED_DrawBox(0, 0, 96, 96, color);;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
    // check the bounds
    if AreCoordsNotValid( xCrd, yCrd, 1, 1 )
    {
        return OLED_STATUS_INIT_ERROR;
    }

    else
    {
        uint16_t dot = color;
            
        // set directions
        SetBorders( xCrd, yCrd, OLED_SCREEN_WIDTH, OLED_SCREEN_HEIGHT);

        OLED_SwapMe(dot);

        // fill the GRAM
        if ( OLED_STATUS_SUCCESS != OLED_SendData( (uint8_t*)&dot, 2 ) )
        {
            return OLED_STATUS_PROTOCOL_ERROR;
        }
        return OLED_STATUS_SUCCESS;
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
    oled_status_t oledStatus;
    
    // adjust for the offset
    OLED_AdjustColumnOffset(xCrd);
    OLED_AdjustRowOffset(yCrd);

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



/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void OLED_Swap(
                    oled_pixel_t imgDst,
                  const uint8_t* imgSrc,
                        uint16_t imgSize
                )
{
    uint32_t var;
    for (var = 0; var < imgSize; var++)
    {
        *imgDst = *imgSrc << 8;
        imgSrc++;
        *imgDst |= *imgSrc;
        imgDst++;
        imgSrc++;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

void OLED_GetImageDimensions(uint8_t *width, uint8_t *height, const uint8_t* image)
{
  *height = image[2] + (image[3] << 8);
  *width  = image[4] + (image[5] << 8);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

oled_status_t OLED_DrawImage (const uint8_t* image, uint8_t xCrd, uint8_t yCrd)
{
    oled_status_t status = OLED_STATUS_SUCCESS;
    uint8_t *ptr;
    uint16_t width, height;
    
    ptr = image;
    
    ptr += 2;
    height = *ptr;
    ptr++;
    height += (*ptr) << 8;

    ptr++;
    width = *ptr;
    ptr++;
    width += (*ptr)<<8;

    // check the bounds
    if AreCoordsNotValid( xCrd, yCrd, width, height )
    {
        status = OLED_STATUS_INIT_ERROR;
    }

    else
    {
        OLED_Swap( screenBuf, (const uint8_t*)( image ) + 6 , width * height );

        // update the main screen buffer
        // GuiDriver_UpdateScreen( oled_dynamic_area.xCrd, oled_dynamic_area.yCrd, oled_dynamic_area.width, oled_dynamic_area.height, (const uint8_t *)oled_dynamic_area.areaBuffer );
    }
    
    // set the locations
    SetBorders( xCrd, yCrd, width, height );

    // fill the GRAM
    if ( OLED_STATUS_SUCCESS != OLED_SendData( (const uint8_t*)screenBuf, width * height * OLED_BYTES_PER_PIXEL ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }

    return OLED_STATUS_SUCCESS;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

void OLED_SetFont(const uint8_t *activeFont, uint16_t font_color, uint8_t font_orientation)
{
    _font = activeFont;
    _fontFirstChar = activeFont[2] + (activeFont[3] << 8);
    _fontLastChar = activeFont[4] + (activeFont[5] << 8);
    _fontHeight = activeFont[6];

    FontColor = font_color;
    FontOrientation = font_orientation;
    FontInitialized = 1;
    ExternalFontSet = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// write text on current position
void OLED_WriteText(uint8_t *text, uint16_t x, uint16_t y) {
  uint16_t i;

  if (x >= OLED_SCREEN_WIDTH)
    return;
  if (y >= OLED_SCREEN_HEIGHT)
    return;

  i = 0;
  OLED_MoveCursor(x, y);
  while (text[i])
      OLED_WriteChar(text[i++]);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void OLED_MoveCursor(uint16_t _x, uint16_t _y)
{
    x_cord = _x;
    y_cord = _y;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void OLED_WriteChar(uint16_t ch)
{
    uint8_t chWidth = 0;
    uint8_t xCnt, yCnt;
    uint16_t x = 0, y;
    uint8_t temp = 0, mask;
    uint32_t offset;
    const uint8_t *pChTable;
    const uint8_t *pChBitMap;
    uint16_t tmp;

    if(FontInitialized == 0)
    {
        OLED_SetFont(guiFont_Tahoma_8_Regular, OLED_COLOR_BLACK, FO_HORIZONTAL); //default font
        FontInitialized = 1;
    }

    if (ch < _fontFirstChar)
    {
        return;
    }
    if (ch > _fontLastChar)
    {
        return;
    }

    offset = 0;
    tmp = (ch - _fontFirstChar) << 2;
    pChTable = _font + 8 + tmp;
    chWidth = *pChTable;

    offset = (uint32_t) pChTable[1] + ((uint32_t)pChTable[2] << 8) + ((uint32_t)pChTable[3] << 16);

    pChBitMap = _font + offset;

    if ((FontOrientation == FO_HORIZONTAL) || (FontOrientation == FO_VERTICAL_COLUMN)) 
    {
        y = y_cord;
        for (yCnt = 0; yCnt < _fontHeight; yCnt++) 
        {
            x = x_cord;
            mask = 0;
            for (xCnt = 0; xCnt < chWidth; xCnt++) 
            {
                if (mask == 0) 
                {
                    temp = *pChBitMap++;
                    mask = 0x01;
                }

                if (temp & mask) 
                {
                    OLED_DrawPixel(x, y, FontColor);
                }

                x++;
                mask <<= 1;
            }
            y++;
        }

        // move cursor
        if (FontOrientation == FO_HORIZONTAL)
        {
            x_cord = x + 1;
        }
        else          // vec ispisujemo vertikalno, karakteri su dosta veci po
        {
            y_cord = y; // visini nego sirini, nema potrebe da se dodaje jedan pixel kao
        }
    }
    else 
    {
        y = x_cord;
        for (yCnt = 0; yCnt < _fontHeight; yCnt++) 
        {
            x = y_cord;
            mask = 0;
            for (xCnt = 0; xCnt < chWidth; xCnt++) 
            {
                if (mask == 0) 
                {
                    temp = *pChBitMap++;
                    mask = 0x01;
                }

                if (temp & mask) 
                {
                    OLED_DrawPixel(y, x, FontColor);
                }

                x--;
                mask <<= 1;
            }

            y++;
        }

        // move cursor
        y_cord = x - 1;
    }
}
// File: OLED_driver.c

// Definitions of user functionalities of the OLED module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>

#include "OLED_info.h"
#include "OLED_defs.h"
#include "OLED_driver.h"

#include "OSA.h"
#include "error.h"

#include "gui_types.h"
#include "gui_driver.h"

#include "generic_spi_driver.h"

#include "HEXIWEAR_driver.h"

////////////////////////////////////////////////////////////////////////////////
// Macro definitions                                                          //
////////////////////////////////////////////////////////////////////////////////

#define OLED_REMAP_SETTINGS (                                                  \
    REMAP_ORDER_ABC                                                            \
    | REMAP_COM_SPLIT_ODD_EVEN_EN                                              \
    | REMAP_COLOR_RGB565                                                       \
    | REMAP_COLUMNS_LEFT_TO_RIGHT                                              \
    | REMAP_SCAN_UP_TO_DOWN                                                    \
    | REMAP_HORIZONTAL_INCREMENT                                               \
    )

#define OLED_AdjustRowOffset(y)    y += OLED_ROW_OFFSET
#define OLED_AdjustColumnOffset(x) x += OLED_COLUMN_OFFSET

#define CheckLimits( x, y, w, h ) (                                            \
    ( ( x + w - 1 ) > OLED_SCREEN_WIDTH )                                      \
    || ( x < 0 )                                                               \
    || ( ( y + h - 1 ) > OLED_SCREEN_HEIGHT )                                  \
    || ( y < 0 ) )

#define AreCoordsValid( x, y, w, h )    ( 0 == CheckLimits( x, y, w ,h ) )
#define AreCoordsNotValid( x, y, w, h ) ( 0 != CheckLimits( x, y, w, h ) )

////////////////////////////////////////////////////////////////////////////////
// Static variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

static uint8_t isFontInitialised = 0;

static const uint8_t *selectedFont;

static uint16_t selectedFont_color;
static uint16_t selectedFont_firstChar; // first character in the font table
static uint16_t selectedFont_lastChar; // last characted in the font table
static uint16_t selectedFont_height;

static oled_dynamic_area_t oled_dynamic_area;

static oled_text_properties_t oled_text_properties = {
    NULL,                   // .font
    GUI_COLOR_WHITE,        // .fontColor
    OLED_TEXT_ALIGN_CENTER, // .alignParam
    NULL                    // .background
};

static uint8_t screenBuf[ OLED_GRAM_SIZE ];

static uint8_t currentChar_width = 0;
static uint8_t currentChar_height = 0;

static uint16_t colorMask = GUI_COLOR_WHITE;

//static handleOLED_t self;
//static settingsOLED_t settings;

// Serial Flash Chip Select connection
sbit OLED_Pwr_bit at PTC_PDOR.B13;
sbit OLED_DC_bit  at PTD_PDOR.B15;
sbit OLED_RST_bit at PTE_PDOR.B6;
sbit OLED_CS_bit  at PTB_PDOR.B20;

static handleOLED_t self;

////////////////////////////////////////////////////////////////////////////////
// Static function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Allocates the memory for the dynamic area.
static void *AllocateDynamicArea( uint32_t area )
{
    void *ptr;

    ptr = OSA_MemAlloc( area * OLED_BYTES_PER_PIXEL );

    if( ptr == NULL )
    {
        error_catch( CATCH_MEM_ALLOC );
        return NULL;
    }

    return ptr;
}

// Deallocates memory used of the dynamic area.
static oled_status_t DestroyDynamicArea( void *ptr, size_t size )
{
    if( ptr == NULL )
    {
        error_catch( CATCH_MEM_ALLOC );
        return OLED_STATUS_INIT_ERROR;
    }

    if( kStatus_OSA_Success != OSA_MemFree( ptr ) )
    {
        error_catch( CATCH_MEM_ALLOC );
        return OLED_STATUS_ERROR;
    }

    return OLED_STATUS_SUCCESS;
}

static osa_status_t mutexStatus;

// Sends data via SPI.
static oled_status_t SendViaSPI( const uint8_t* bufPtr, uint32_t txSize )
{
    oled_status_t status;
    dspi_status_t spiStatus;
    
    status = OLED_STATUS_SUCCESS;
    mutexStatus = OSA_MutexLock( &spiAccessMutex, OSA_WAIT_FOREVER );
    
    if( mutexStatus == kStatus_OSA_Success )
    {
        spiStatus = DSPI_DRV_EdmaMasterTransferBlocking(
            self.protocol.instance, // spiProtocol.instance,
            NULL,

            bufPtr,
            NULL,

            txSize, // 1

            self.protocol.timeout // spiProtocol.timeout
        );

        if( spiStatus != kStatus_DSPI_Success )
        {
            error_catch( CATCH_OLED );
            status = OLED_STATUS_PROTOCOL_ERROR;
        }
        else
        {
            status = OLED_STATUS_SUCCESS;
        }
    }
    else
    {
        error_catch( CATCH_MUTEX );
        status = OLED_STATUS_INIT_ERROR;
    }
    
    OSA_MutexUnlock( &spiAccessMutex );
    return status;
}

// Transposes an image.
static void Transpose(
    oled_pixel_t       transImage,
    const oled_pixel_t image,
    uint8_t            width,
    uint8_t            height )
{
    uint8_t i, j;
  
    for( i = 0; i < height; i++ )
    {
        for( j = 0; j < width ; j++ )
        {
            transImage[ j * height + i ] = image[ i * width + j ];
        }
    }
}

// Sets borders on the screen.
static void SetBorders( uint8_t xCrd, uint8_t yCrd,
    uint8_t width, uint8_t height )
{
    oled_status_t oledStatus;
    
    // Adjust for the offset.
    OLED_AdjustColumnOffset( xCrd );
    OLED_AdjustRowOffset( yCrd );
    
    while( 1 )
    {
        oledStatus = OLED_STATUS_SUCCESS;
        
        oledStatus |= OLED_SendCmd( OLED_CMD_SET_COLUMN, FIRST_BYTE );
        oledStatus |= OLED_SendCmd( xCrd, OTHER_BYTE );
        oledStatus |= OLED_SendCmd( xCrd + ( width - 1 ), OTHER_BYTE );
        oledStatus |= OLED_SendCmd( OLED_CMD_SET_ROW, FIRST_BYTE );
        oledStatus |= OLED_SendCmd( yCrd, OTHER_BYTE );
        oledStatus |= OLED_SendCmd( yCrd + ( height - 1 ), OTHER_BYTE );
        
        if( oledStatus == OLED_STATUS_SUCCESS )
            break;
    }
}

// Creates background for the text.
static oled_status_t CreateTextBackground()
{
    uint8_t xCrd   = oled_dynamic_area.xCrd;
    uint8_t yCrd   = oled_dynamic_area.yCrd;
    uint8_t width  = oled_dynamic_area.width;
    uint8_t height = oled_dynamic_area.height;
    
    oled_pixel_t imgBuf = oled_dynamic_area.areaBuffer;
    oled_pixel_t copyAddr;
    
    const uint8_t *background = oled_text_properties.background;

    // Copy data.
    if( ( imgBuf == NULL )
        || ( ( xCrd + width )  > OLED_SCREEN_WIDTH )
        || ( ( yCrd + height ) > OLED_SCREEN_HEIGHT ) )
    {
        return OLED_STATUS_INIT_ERROR;
    }
    
    if( background == NULL )
    {
        uint8_t i;
        for( i = 0; i < height; i++ )
        {
            memset( imgBuf, 0, width * OLED_BYTES_PER_PIXEL );
            imgBuf += width;
        }
    }
    else
    {
        uint8_t i;
        
        copyAddr = ( GuiDriver_SkipHeader( background ) )
            + ( yCrd * OLED_SCREEN_WIDTH + xCrd );
            
        for( i = 0; i < height; i++ )
        {
            OLED_Swap( imgBuf, copyAddr, width );
            imgBuf   += width;
            copyAddr += OLED_SCREEN_WIDTH;
        }
    }
    
    return OLED_STATUS_SUCCESS;
}

// Writes a character to the given buffer.
static void WriteCharToBuf( uint16_t charToWrite, oled_pixel_t* chrBuf )
{
    uint8_t xCnt, yCnt;
    uint8_t temp, mask;
    uint32_t offset;
    const uint8_t* pChTable;
    const uint8_t* pChBitMap;
    
    if( isFontInitialised == 0 )
    {
        // Default font.
        OLED_SetFont( guiFont_Tahoma_8_Regular, 0xFFFF );
    }
    
    pChTable = selectedFont + 8 +
        ( uint16_t )( ( charToWrite - selectedFont_firstChar ) << 2 );

    currentChar_width  = *pChTable;
    currentChar_height = selectedFont_height;
    
    offset = ( uint32_t )pChTable[1]
        | ( ( uint32_t )pChTable[2] << 8 )
        | ( ( uint32_t )pChTable[3] << 16 );

    pChBitMap = selectedFont + offset;
    
    // Allocate space for char image.
    *chrBuf = AllocateDynamicArea( currentChar_height * currentChar_width );
    
    if( chrBuf == NULL )
        return;

    for( yCnt = 0; yCnt < currentChar_height; yCnt++ )
    {
        mask = 0;
        
        for( xCnt = 0; xCnt < currentChar_width; xCnt++ )
        {
            if( mask == 0 )
            {
                mask = 1;
                temp = *pChBitMap++;
            }
            
            if( ( temp & mask ) != 0 )
            {
                *( *chrBuf + yCnt * currentChar_width + xCnt ) =
                    selectedFont_color;
            }
            else
            {
                *( *chrBuf + yCnt * currentChar_width + xCnt ) = 0;
            }
            
            mask = mask << 1;
        }
    }
}

// Adds a character to the text area.
static oled_status_t AddCharToTextArea(
    oled_pixel_t chrPtr,
    uint8_t      chrWidth,
    uint8_t      chrHeight,
    oled_pixel_t copyAddr,
    uint8_t      imgWidth )
{
    uint8_t i, j;

    if( copyAddr == NULL )
        return OLED_STATUS_INIT_ERROR;

    for( i = 0; i < chrHeight; i++ )
    {
        for( j = 0; j < chrWidth; j++ )
        {
            if( chrPtr[j] != 0 )
                copyAddr[j] = chrPtr[j];
        }
        
        copyAddr += imgWidth;
        chrPtr   += chrWidth;
    }
    
    return OLED_STATUS_SUCCESS;
}

// Slides an image into the screen from right to left.
static oled_status_t RightLeft(
    const uint8_t *image,
    uint8_t        xCrd,
    uint8_t        yCrd,
    uint8_t        width,
    uint8_t        height )
{
    oled_dynamic_area_t transImageArea;
    oled_pixel_t        transImage;
    
    uint16_t            transStep;
    uint16_t            partImgSize;
    uint8_t            *partImgPtr;
    uint8_t             xCrd_moving;
    
    transImageArea.xCrd   = 0;
    transImageArea.yCrd   = 0;
    transImageArea.width  = 96;
    transImageArea.height = 96;
    
    OLED_SetDynamicArea( &transImageArea );
    
    transImage = oled_dynamic_area.areaBuffer;
    if( transImage == NULL )
        return OLED_STATUS_INIT_ERROR;

    Transpose( transImage, image, width, height );
    
    if( OLED_SendCmd( OLED_CMD_SET_REMAP, FIRST_BYTE ) != OLED_STATUS_SUCCESS )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    if( OLED_SendCmd( OLED_REMAP_SETTINGS | REMAP_VERTICAL_INCREMENT,
        OTHER_BYTE ) != OLED_STATUS_SUCCESS )
    {
       return OLED_STATUS_PROTOCOL_ERROR;
    }

    transStep = OLED_TRANSITION_STEP;
    partImgSize = height * transStep;
    partImgPtr = transImage;
    xCrd_moving = ( xCrd + width ) - 1;
    
    // Set locations.
    while( 1 )
    {
        if( ( partImgSize > width * height ) || ( xCrd_moving < xCrd ) )
        {
            SetBorders( xCrd, yCrd, width, height );
            if( OLED_SendData( transImage, height * width
                * OLED_BYTES_PER_PIXEL ) != OLED_STATUS_SUCCESS )
            {
                return OLED_STATUS_PROTOCOL_ERROR;
            }
            break;
        }
        else
        {
            SetBorders( xCrd_moving, yCrd,
                ( xCrd + width ) - xCrd_moving, height );
            if( OLED_SendData( partImgPtr, partImgSize * OLED_BYTES_PER_PIXEL )
                != OLED_STATUS_SUCCESS )
            {
                return OLED_STATUS_PROTOCOL_ERROR;
            }
            
        }
        
        // Update varaibles.
        xCrd_moving -= transStep;
        partImgSize += ( height * transStep );
        transStep++;
    }
    
    if( OLED_SendCmd( OLED_CMD_SET_REMAP, FIRST_BYTE ) != OLED_STATUS_SUCCESS )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    if( OLED_SendCmd( OLED_REMAP_SETTINGS, OTHER_BYTE ) != OLED_STATUS_SUCCESS )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    
    OLED_DestroyDynamicArea();
    
    return OLED_STATUS_SUCCESS;
}

// Slides an image into the screen from left to right.
static oled_status_t LeftRight(
    const uint8_t *image,
    uint8_t        xCrd,
    uint8_t        yCrd,
    uint8_t        width,
    uint8_t        height )
{
    oled_dynamic_area_t transImageArea;
    oled_pixel_t        transImage;

    uint16_t            transStep;
    uint16_t            partImgSize;
    uint8_t            *partImgPtr;

    transImageArea.xCrd   = 0;
    transImageArea.yCrd   = 0;
    transImageArea.width  = 96;
    transImageArea.height = 96;

    OLED_SetDynamicArea( &transImageArea );

    transImage = oled_dynamic_area.areaBuffer;
    if( transImage == NULL )
        return OLED_STATUS_INIT_ERROR;

    Transpose( transImage, image, width, height );

    if( OLED_SendCmd( OLED_CMD_SET_REMAP, FIRST_BYTE ) != OLED_STATUS_SUCCESS )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    if( OLED_SendCmd( OLED_REMAP_SETTINGS | REMAP_VERTICAL_INCREMENT,
        OTHER_BYTE ) != OLED_STATUS_SUCCESS )
    {
       return OLED_STATUS_PROTOCOL_ERROR;
    }

    transStep = OLED_TRANSITION_STEP;
    partImgSize = height * transStep;
    partImgPtr = ( uint8_t* ) transImage
        + ( width - transStep ) * ( height * OLED_BYTES_PER_PIXEL );


    // Set locations.
    while( 1 )
    {
        if( partImgSize > width * height )
        {
        SetBorders( xCrd, yCrd, width, height );
            if( OLED_SendData( transImage, height * width
                * OLED_BYTES_PER_PIXEL ) != OLED_STATUS_SUCCESS )
            {
                return OLED_STATUS_PROTOCOL_ERROR;
            }
            break;
        }
        else
        {
        SetBorders( xCrd, yCrd, partImgSize / height, height );
            if( OLED_SendData( partImgPtr, partImgSize * OLED_BYTES_PER_PIXEL )
                != OLED_STATUS_SUCCESS )
            {
                return OLED_STATUS_PROTOCOL_ERROR;
            }

        }

        // Update varaibles.
        partImgPtr = partImgPtr - ( transStep * height ) * OLED_BYTES_PER_PIXEL;
        partImgSize += ( transStep * height );
        transStep++;
    }

    if( OLED_SendCmd( OLED_CMD_SET_REMAP, FIRST_BYTE ) != OLED_STATUS_SUCCESS )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    if( OLED_SendCmd( OLED_REMAP_SETTINGS, OTHER_BYTE ) != OLED_STATUS_SUCCESS )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }

    OLED_DestroyDynamicArea();

    return OLED_STATUS_SUCCESS;
}

// Slides an image into the screen from down to top.s
static oled_status_t DownTop(
    const uint8_t *image,
          uint8_t  xCrd,
          uint8_t  yCrd,
          uint8_t  width,
          uint8_t  height )
{
    uint16_t transStep   = OLED_TRANSITION_STEP;
    uint16_t partImgSize = width * transStep;
    uint8_t *partImgPtr  = image;
    uint8_t yCrd_moving  = ( yCrd + height ) - 1;
    
    // Set locations.
    while( 1 )
    {
        if( ( partImgSize > width * height ) || ( yCrd_moving < yCrd ) )
        {
            SetBorders( xCrd, yCrd, width, height );
            if( OLED_SendData( image, width * height * OLED_BYTES_PER_PIXEL )
                != OLED_STATUS_SUCCESS )
            {
                return OLED_STATUS_PROTOCOL_ERROR;
            }
            break;
        }
        else
        {
            SetBorders( xCrd, yCrd_moving,
                width, ( yCrd + height ) - yCrd_moving );
            if( OLED_SendData( partImgPtr, partImgSize * OLED_BYTES_PER_PIXEL )
                != OLED_STATUS_SUCCESS )
            {
                return OLED_STATUS_PROTOCOL_ERROR;
            }
        }
        
        // Update variables.
        yCrd_moving -= transStep;
        partImgSize += ( width * transStep );
        transStep++;
    }
    
    return OLED_STATUS_SUCCESS;
}


// Slides an image into the screen from top to down.
static oled_status_t TopDown(
    const uint8_t *image,
          uint8_t  xCrd,
          uint8_t  yCrd,
          uint8_t  width,
          uint8_t  height )
{
    uint16_t transStep   = OLED_TRANSITION_STEP;
    uint16_t partImgSize = width * transStep;
    uint8_t *partImgPtr  = ( uint8_t* )image +
        ( height - transStep ) * ( width * OLED_BYTES_PER_PIXEL );

    // Set locations.
    while( 1 )
    {
        SetBorders( xCrd, yCrd, width, height );
        if( ( partImgSize > width * height ) )
        {
            if( OLED_SendData( image, width * height * OLED_BYTES_PER_PIXEL )
                != OLED_STATUS_SUCCESS )
            {
                return OLED_STATUS_PROTOCOL_ERROR;
            }
            break;
        }
        else
        {
            if( OLED_SendData( partImgPtr, partImgSize * OLED_BYTES_PER_PIXEL )
                != OLED_STATUS_SUCCESS )
            {
                return OLED_STATUS_PROTOCOL_ERROR;
            }
        }

        // Update variables.
        partImgPtr  -= ( width * transStep ) * OLED_BYTES_PER_PIXEL;
        partImgSize += ( width * transStep );
        transStep++;
    }

    return OLED_STATUS_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////
// Global function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Initialises the OLED screen.
oled_status_t OLED_Init( handleOLED_t* oledHandle )
{
    statusSPI_t status;
    osa_status_t spiStatus;

    oled_text_properties.alignParam = OLED_TEXT_ALIGN_CENTER;
    oled_text_properties.background = NULL;

    GPIO_Digital_Output( &PTC_PDOR, _GPIO_PINMASK_13 );
    GPIO_Digital_Output( &PTD_PDOR, _GPIO_PINMASK_15 );
    GPIO_Digital_Output( &PTE_PDOR, _GPIO_PINMASK_6 );
    GPIO_Digital_Output( &PTB_PDOR, _GPIO_PINMASK_20 );

    status = SPI_Init( &( oledHandle->protocol ) );
    
    if( status != STATUS_SPI_SUCCESS )
    {
        error_catch( CATCH_INIT );
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    
//    SPI2_Init_Advanced( 18000000, _SPI_CFG_MASTER | _SPI_CFG_SELECT_CTAR0
//        | _SPI_CFG_FRAME_SIZE_8BITS | _SPI_CFG_CLK_IDLE_HIGH
//        | _SPI_CFG_CLK_PHASE_CHG_LEADING | _SPI_CFG_MSB_FIRST,
//        &_GPIO_Module_SPI2_PB21_23_22 );
        
//    PORTB_PCR21bits.DSE = 1;
//    PORTB_PCR22bits.DSE = 1;
//    PORTB_PCR23bits.DSE = 1;
    
    memcpy( ( void* )&self, ( void* )oledHandle, sizeof( self ) );
    
    status = OLED_STATUS_SUCCESS;
    
    // set IRQ priority
    HEXIWEAR_SetIntPriority(IVT_INT_SPI2, HEXIWEAR_OLED_SPI_IRQ_PRIO);
    HEXIWEAR_SetIntPriority(IVT_INT_DMA0, HEXIWEAR_OLED_DMA_RX_IRQ_PRIO);
    HEXIWEAR_SetIntPriority(IVT_INT_DMA1, HEXIWEAR_OLED_DMA_TX_IRQ_PRIO);

    // create mutex
    spiStatus = OSA_MutexCreate( &spiAccessMutex );
    
    // Power sequence.
    OLED_Pwr_bit = 0;
    OSA_TimeDelay( 1 );
    OLED_RST_bit = 0;
    OSA_TimeDelay( 1 );
    OLED_RST_bit = 1;
    OSA_TimeDelay( 1 );
    OLED_Pwr_bit = 1;
    
    if( OLED_STATUS_SUCCESS
        != OLED_SendCmd( OLED_CMD_SET_CMD_LOCK, FIRST_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    if( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_UNLOCK, OTHER_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }

    if( OLED_STATUS_SUCCESS
        != OLED_SendCmd( OLED_CMD_SET_CMD_LOCK, FIRST_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    if( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_ACC_TO_CMD_YES, OTHER_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }

    if( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_DISPLAYOFF, FIRST_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }

    if( OLED_STATUS_SUCCESS
        != OLED_SendCmd( OLED_CMD_SET_OSC_FREQ_AND_CLOCKDIV, FIRST_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    if( OLED_STATUS_SUCCESS != OLED_SendCmd( 0xF1, OTHER_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }

    if( OLED_STATUS_SUCCESS
        != OLED_SendCmd( OLED_CMD_SET_MUX_RATIO, FIRST_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    if( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x5F, OTHER_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }

    if( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_SET_REMAP, FIRST_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    if( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_REMAP_SETTINGS, OTHER_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }

    if( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_SET_COLUMN, FIRST_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    if( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x00, OTHER_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    if( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x5F, OTHER_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }

    if( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_SET_ROW, FIRST_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    if( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x00, OTHER_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    if( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x5F, OTHER_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }

    if( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_STARTLINE, FIRST_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    if( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x80, OTHER_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }

    if( OLED_STATUS_SUCCESS
        != OLED_SendCmd( OLED_CMD_DISPLAYOFFSET, FIRST_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    if( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x60, OTHER_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }

    if( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_PRECHARGE, FIRST_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    if( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x32, FIRST_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }

    if( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_VCOMH, FIRST_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    if( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x05, FIRST_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }

    if( OLED_STATUS_SUCCESS
        != OLED_SendCmd( OLED_CMD_NORMALDISPLAY, FIRST_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }

    if( OLED_STATUS_SUCCESS
        != OLED_SendCmd( OLED_CMD_CONTRASTABC, FIRST_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    if( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x8A, OTHER_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    if( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x51, OTHER_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    if( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x8A, OTHER_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }

    if( OLED_STATUS_SUCCESS
        != OLED_SendCmd( OLED_CMD_CONTRASTMASTER, FIRST_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    if( OLED_STATUS_SUCCESS != OLED_SendCmd( 0xCF, OTHER_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }

    if( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_SETVSL, FIRST_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    if( OLED_STATUS_SUCCESS != OLED_SendCmd( 0xA0, OTHER_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    if( OLED_STATUS_SUCCESS != OLED_SendCmd( 0xB5, OTHER_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    if( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x55, OTHER_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }

    if( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_PRECHARGE2, FIRST_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    if( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x01, OTHER_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }

    if( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_DISPLAYON, FIRST_BYTE ) )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }

    return OLED_STATUS_SUCCESS;
}

// Deinitialises the OLED screen. (not used)
oled_status_t OLED_Deinit()
{
    return SPI_Deinit( &( self.protocol ) );
}

// Returns dimensions of the given image.
void OLED_GetImageDimensions(
    uint8_t *width,
    uint8_t *height,
    const uint8_t *image )
{
    *height = image[2] + ( image[3] << 8 );
    *width  = image[4] + ( image[5] << 8 );
}

// Adds image to the image buffer.
oled_status_t OLED_AddImage( const uint8_t *image )
{
    // Check the bounds.
    if( AreCoordsNotValid( oled_dynamic_area.xCrd, oled_dynamic_area.yCrd,
        oled_dynamic_area.width, oled_dynamic_area.height ) )
        return OLED_STATUS_INIT_ERROR;
    
    OLED_Swap( oled_dynamic_area.areaBuffer, GuiDriver_SkipHeader(image),
        oled_dynamic_area.width * oled_dynamic_area.height );

    // Update the main screen buffer.
    GuiDriver_UpdateScreen(
        oled_dynamic_area.xCrd,
        oled_dynamic_area.yCrd,
        oled_dynamic_area.width,
        oled_dynamic_area.height,
        ( const uint8_t * )oled_dynamic_area.areaBuffer );
        
    return OLED_STATUS_SUCCESS;
}

// Draws an image on the display.
oled_status_t OLED_DrawImage(
    const uint8_t *image )
{
    OLED_AddImage( image );
    
    // Set the locations.
    SetBorders( oled_dynamic_area.xCrd, oled_dynamic_area.yCrd,
        oled_dynamic_area.width, oled_dynamic_area.height );
        
    // Fill the GRAM.
    if( OLED_SendData( oled_dynamic_area.areaBuffer, oled_dynamic_area.width
        * oled_dynamic_area.height * OLED_BYTES_PER_PIXEL ) 
        != OLED_STATUS_SUCCESS )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    
    return OLED_STATUS_SUCCESS;
}

// Sends a command to the OLED.
oled_status_t OLED_SendCmd( uint32_t cmd, uint8_t isFirst )
{
    oled_status_t spiStatus;

    uint8_t txBuf[1];
    
    txBuf[0] = ( uint8_t ) cmd;

    if( isFirst )
        OLED_DC_bit = 0;
    else
        OLED_DC_bit = 1;

    OLED_CS_bit = 0;

    spiStatus = SendViaSPI( txBuf, 1 );
    if( spiStatus != OLED_STATUS_SUCCESS )
    {
        error_catch( CATCH_OLED );
        OLED_CS_bit = 1;
        return OLED_STATUS_PROTOCOL_ERROR;
    }

    // SPI2_Write( ( uint8_t )cmd );

    OLED_CS_bit = 1;

    return OLED_STATUS_SUCCESS;
}

// Sends data to the OLED.
oled_status_t OLED_SendData( const uint8_t *dataToSend, uint32_t dataSize )
{
    oled_status_t spiStatus;

    const uint8_t *bufPtr;
    uint16_t numChunks;
    uint16_t lastChunkSize;
    uint16_t i;

    if( OLED_SendCmd( OLED_CMD_WRITERAM, FIRST_BYTE ) != OLED_STATUS_SUCCESS )
        return OLED_STATUS_PROTOCOL_ERROR;

    // Sending data so set DC pin.
    OLED_DC_bit = 1;
    OLED_CS_bit = 0;

    bufPtr = dataToSend;
    numChunks = dataSize / OLED_SPI_CHUNK;
    lastChunkSize = dataSize % OLED_SPI_CHUNK;

    if( numChunks > 0 )
    {
        for( i = 0; i < numChunks; i++ )
        {
            spiStatus = SendViaSPI( bufPtr, OLED_SPI_CHUNK );
            if( spiStatus == OLED_STATUS_SUCCESS )
            {
                bufPtr += OLED_SPI_CHUNK;
            }
            else
            {
                error_catch( CATCH_OLED );
                OLED_CS_bit = 1;
                return OLED_STATUS_PROTOCOL_ERROR;
            }
        }
    }
    
    if( lastChunkSize > 0 )
    {
        spiStatus = SendViaSPI( bufPtr, lastChunkSize );
        if( spiStatus != OLED_STATUS_SUCCESS )
        {
            error_catch( CATCH_OLED );
            OLED_CS_bit = 1;
            return OLED_STATUS_PROTOCOL_ERROR;
        }
    }

    /* while( dataSize-- )
    {
        SPI2_Write( *( bufPtr++ ) );
    } */

    OLED_CS_bit = 1;

    return OLED_STATUS_SUCCESS;
}

// Draws a box on the screen.
oled_status_t OLED_DrawBox(
    uint16_t xCrd,
    uint16_t yCrd,
    uint16_t width,
    uint16_t height,
    uint16_t color )
{
    uint16_t            i;
    
    oled_dynamic_area_t boxArea;
    uint32_t            boxSize;
    uint8_t            *boxBuf;

    boxArea.xCrd   = xCrd;
    boxArea.yCrd   = yCrd;
    boxArea.width  = width;
    boxArea.height = height;
    
    boxSize = width * height;
    
    OLED_SetDynamicArea( &boxArea );
    
    boxBuf = ( uint8_t* )oled_dynamic_area.areaBuffer;
    
    if( boxBuf == NULL )
    {
        error_catch( 9 );
        return OLED_STATUS_ERROR;
    }
    
    // Check the bounds.
    if( AreCoordsNotValid( xCrd, yCrd, width, height ) )
        return OLED_STATUS_INIT_ERROR;

    // Fill the buffer with color.
    for( i = 0; i < boxSize; i++ )
    {
        boxBuf[2 * i]     = color >> 8;
        boxBuf[2 * i + 1] = color;
    }
    
    // Set the locations.
    SetBorders( xCrd, yCrd, width, height );
    
    // Fill the GRAM.
    if( OLED_SendData( (uint8_t*)boxBuf, boxSize*OLED_BYTES_PER_PIXEL )
        != OLED_STATUS_SUCCESS )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    
    OLED_DestroyDynamicArea();
    
    return OLED_STATUS_SUCCESS;
}

// Fills the screen with the given color.
oled_status_t OLED_FillScreen( uint16_t color )
{
    uint16_t i;
    
    for( i = 0; i < ( OLED_SCREEN_WIDTH * OLED_SCREEN_HEIGHT ); i++ )
    {
        screenBuf[2 * i]     = color >> 8;
        screenBuf[2 * i + 1] = color;
    }
    
    // Set the locations.
    SetBorders( 0, 0, OLED_SCREEN_WIDTH, OLED_SCREEN_HEIGHT );
    
    // Fill the GRAM.
    if( OLED_SendData( (uint8_t*)screenBuf, OLED_SCREEN_WIDTH
        * OLED_SCREEN_HEIGHT * OLED_BYTES_PER_PIXEL )
        != OLED_STATUS_SUCCESS )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    
    return OLED_STATUS_SUCCESS;
}

// Draws a pixel on the screen.
oled_status_t OLED_DrawPixel(
    uint16_t xCrd,
    uint16_t yCrd,
    uint16_t color )
{
    uint16_t dot;

    // Check the bounds.
    if( AreCoordsNotValid( xCrd, yCrd, 1, 1 ) )
    {
        return OLED_STATUS_INIT_ERROR;
    }

    dot = color;

    // Set directions.
    SetBorders( xCrd, yCrd, OLED_SCREEN_WIDTH, OLED_SCREEN_HEIGHT );

    OLED_SwapMe(dot);

    // Fill the GRAM.
    if( OLED_SendData( ( uint8_t* )&dot, 2 ) != OLED_STATUS_SUCCESS )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }

    return OLED_STATUS_SUCCESS;
}

// Draws a screen in the desired direction.
oled_status_t OLED_DrawScreen(
    const uint8_t *image,
    uint8_t xCrd,
    uint8_t yCrd,
    uint8_t width,
    uint8_t height,
    oled_transition_t transition )
{
    // Check the bounds.
    if( AreCoordsNotValid( xCrd, yCrd, width, height ) )
        return OLED_STATUS_INIT_ERROR;

    switch( transition )
    {
        case OLED_TRANSITION_NONE:
            // Set directions.
            SetBorders( xCrd, yCrd, width, height );

            // Fill the GRAM.
            if( OLED_SendData( image, width * height * OLED_BYTES_PER_PIXEL )
                != OLED_STATUS_SUCCESS )
            {
                return OLED_STATUS_PROTOCOL_ERROR;
            }
            break;
        case OLED_TRANSITION_TOP_DOWN:
            TopDown( image, xCrd, yCrd, width, height );
            break;
        case OLED_TRANSITION_DOWN_TOP:
            DownTop( image, xCrd, yCrd, width, height );
            break;
        case OLED_TRANSITION_LEFT_RIGHT:
            LeftRight( image, xCrd, yCrd, width, height );
            break;
        case OLED_TRANSITION_RIGHT_LEFT:
            RightLeft( image, xCrd, yCrd, width, height );
            break;
        default:
            break;
    }

    return OLED_STATUS_SUCCESS;
}

// Sets font of the OLED display.
oled_status_t OLED_SetFont(
    const uint8_t *newFont,
    uint16_t       newColor )
{
    selectedFont           = newFont;
    selectedFont_firstChar = newFont[2] + ( newFont[3] << 8 );
    selectedFont_lastChar  = newFont[4] + ( newFont[5] << 8 );
    selectedFont_height    = newFont[6];
    selectedFont_color     = newColor;

    // No need to do this here,
    // the color will be switched when a character is written.
    OLED_SwapMe( selectedFont_color );

    isFontInitialised = 1;

    return OLED_STATUS_SUCCESS;
}

// Adds text to the text buffer.
oled_status_t OLED_AddText( const uint8_t *text )
{
    uint16_t chrCnt = 0;
    oled_pixel_t chrBuf = NULL;
    
    uint8_t currentChar_x = 0;
    uint8_t currentChar_y = 0;

    uint8_t text_height = 0;
    uint8_t text_width  = 0;
    
    oled_pixel_t copyAddr;
    
    text_width = OLED_GetTextWidth(text);
    
    // Set default values, if necessary.
    text_height = selectedFont_height;
    
    if( ( oled_dynamic_area.width  < text_width )
        || ( oled_dynamic_area.height < text_height ) )
    {
        oled_dynamic_area_t textArea;

        textArea.width  = text_width;
        textArea.height = text_height;
        OLED_SetDynamicArea( &textArea );
    }
    
    currentChar_y = ( oled_dynamic_area.height - text_height ) >> 1;
    
    switch( oled_text_properties.alignParam & OLED_TEXT_HALIGN_MASK )
    {
        case OLED_TEXT_ALIGN_LEFT:
            currentChar_x = 0;
            break;

        case OLED_TEXT_ALIGN_RIGHT:
            currentChar_x = ( oled_dynamic_area.width - text_width );
            break;

        case OLED_TEXT_ALIGN_CENTER:
            currentChar_x += ( oled_dynamic_area.width - text_width ) >> 1 ;
            break;

        case OLED_TEXT_ALIGN_NONE:
            break;

        default:
            break;
    }
    
    if( CreateTextBackground() != OLED_STATUS_SUCCESS )
        return OLED_STATUS_ERROR;

    chrCnt = 0;
    while( text[chrCnt] != 0 )
    {
        WriteCharToBuf( text[chrCnt++], &chrBuf );
        
        if( chrBuf == NULL )
            return OLED_STATUS_INIT_ERROR;

        if  (
            ( currentChar_x + currentChar_width > oled_dynamic_area.width ) ||
            ( currentChar_y + currentChar_height > oled_dynamic_area.height ) )
        {
            DestroyDynamicArea(
                chrBuf, currentChar_height * currentChar_width );
            chrBuf = NULL;
            return OLED_STATUS_ERROR;
        }
        
        // Copy data.
        copyAddr = oled_dynamic_area.areaBuffer
            + ( currentChar_y * oled_dynamic_area.width + currentChar_x );
        AddCharToTextArea( chrBuf, currentChar_width, currentChar_height,
            copyAddr, oled_dynamic_area.width );

        currentChar_x += (currentChar_width + 1); // 1px space between chars
        currentChar_y += 0;

        DestroyDynamicArea( chrBuf, currentChar_height * currentChar_width );
        chrBuf = NULL;
    }
    
    GuiDriver_UpdateScreen(
        oled_dynamic_area.xCrd,
        oled_dynamic_area.yCrd,
        oled_dynamic_area.width,
        oled_dynamic_area.height,
        ( const uint8_t* )oled_dynamic_area.areaBuffer );

    return OLED_STATUS_SUCCESS;
}

// Writes text to OLED.
oled_status_t OLED_DrawText( uint8_t *text )
{
    if( text == NULL )
        return OLED_STATUS_ERROR;

    OLED_AddText( text );
    
    // Set the locations.
    SetBorders( oled_dynamic_area.xCrd, oled_dynamic_area.yCrd,
        oled_dynamic_area.width, oled_dynamic_area.height );

    // fill the GRAM
    if ( OLED_SendData( oled_dynamic_area.areaBuffer,
        oled_dynamic_area.width * oled_dynamic_area.height
        * OLED_BYTES_PER_PIXEL ) != OLED_STATUS_SUCCESS )
    {
        return OLED_STATUS_PROTOCOL_ERROR;
    }
    
    return OLED_STATUS_SUCCESS;
}

// Sets the dynamic area of the OLED display.
void OLED_SetDynamicArea( oled_dynamic_area_t *dynamic_area )
{
    if( oled_dynamic_area.areaBuffer == NULL )
    {
        oled_dynamic_area.areaBuffer = ( oled_pixel_t )AllocateDynamicArea(
            dynamic_area->width * dynamic_area->height );
    }
    else if( ( dynamic_area->height != oled_dynamic_area.height )
        || ( dynamic_area->width != oled_dynamic_area.width ) )
    {
        OLED_DestroyDynamicArea();
        oled_dynamic_area.areaBuffer = ( oled_pixel_t )AllocateDynamicArea(
            dynamic_area->width * dynamic_area->height );
    }
    
    oled_dynamic_area.xCrd   = dynamic_area->xCrd;
    oled_dynamic_area.yCrd   = dynamic_area->yCrd;
    oled_dynamic_area.width  = dynamic_area->width;
    oled_dynamic_area.height = dynamic_area->height;
}

// Destroys the dynamic area of the OLED display.
void OLED_DestroyDynamicArea()
{
    if( oled_dynamic_area.areaBuffer != NULL )
    {
        DestroyDynamicArea( oled_dynamic_area.areaBuffer,
            oled_dynamic_area.width * oled_dynamic_area.height );
        oled_dynamic_area.areaBuffer = NULL;
    }
}

// Sets text properties.
void OLED_SetTextProperties( oled_text_properties_t *textProperties )
{
    oled_text_properties.font       = textProperties->font;
    oled_text_properties.fontColor  = textProperties->fontColor;
    oled_text_properties.alignParam = textProperties->alignParam;
    oled_text_properties.background = textProperties->background;
    
    OLED_SetFont( oled_text_properties.font, oled_text_properties.fontColor );
}

// Counts the characters in a text of a given font
// that can fit on the given width.
uint8_t OLED_CharCount(
    uint8_t width,
    const uint8_t *font,
    const uint8_t *text,
    uint8_t length )
{
    uint8_t chrCnt = 0;
    uint8_t text_width = 0;
    uint16_t firstChar;
    
    firstChar = font[2] | ( ( uint16_t )font[3] << 8 );
    
    while( chrCnt < length )
    {
        text_width += *( font + 8 +
            ( uint16_t )( ( text[ chrCnt++ ] - firstChar ) << 2 ) );
        if( text_width > width )
        {
            chrCnt--;
            break;
        }
        // Make 1px space between characters.
        text_width++;
    }
    
    return chrCnt;
}

// Returns the width that the given text would take on the screen.
uint8_t OLED_GetTextWidth( const uint8_t *text )
{
    uint8_t chrCnt = 0;
    uint8_t text_width = 0;
    
    while( text[chrCnt] != 0 )
    {
        text_width += *( selectedFont + 8 +
            (uint16_t)( ( text[chrCnt++] - selectedFont_firstChar ) << 2 ) );
        // Make 1px space between chars.
        text_width++;
    }
    // Remove the final space.
    text_width--;
    
    return text_width;
}

// Transfers source image to destination image
// so that bytes in each pixel are inverted,
// which is how they should be sent to the display.
void OLED_Swap( oled_pixel_t imgDst,
    const uint8_t* imgSrc, uint16_t imgSize )
{
    uint32_t var;
    for( var = 0; var < imgSize; var++ )
    {
        *imgDst = *imgSrc << 8;
        imgSrc++;
        *imgDst |= *imgSrc;
        imgDst++;
        imgSrc++;
    }
}

// Dim the OLED screen.
void OLED_DimScreenON()
{
    int i;
    for( i = 0; i < 16; i++ )
    {
        OLED_SendCmd( OLED_CMD_CONTRASTMASTER, FIRST_BYTE );
        OLED_SendCmd( 0xC0 | ( 0xF - i ), OTHER_BYTE );
        OSA_TimeDelay( 20 );
    }
}

// Return the OLED screen back to full contrast.
void OLED_DimScreenOFF()
{
    OLED_SendCmd( OLED_CMD_CONTRASTMASTER, FIRST_BYTE );
    OLED_SendCmd( 0xC0 | 0xF, OTHER_BYTE );
}
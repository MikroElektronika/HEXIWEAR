#line 1 "D:/Marko/tasks/freescale/svn/Hexiwear/MK64/5. Click Demos/1. mikroC/2. Primeri/HEXIWEAR_8x8_Click/example/ARM/OLED_driver.c"
#line 1 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_8x8_click/example/arm/oled_driver.h"
#line 1 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_8x8_click/example/arm/oled_types.h"
#line 1 "d:/work/mikroc pro for arm/include/stdint.h"





typedef signed char int8_t;
typedef signed int int16_t;
typedef signed long int int32_t;
typedef signed long long int64_t;


typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long int uint32_t;
typedef unsigned long long uint64_t;


typedef signed char int_least8_t;
typedef signed int int_least16_t;
typedef signed long int int_least32_t;
typedef signed long long int_least64_t;


typedef unsigned char uint_least8_t;
typedef unsigned int uint_least16_t;
typedef unsigned long int uint_least32_t;
typedef unsigned long long uint_least64_t;



typedef signed long int int_fast8_t;
typedef signed long int int_fast16_t;
typedef signed long int int_fast32_t;
typedef signed long long int_fast64_t;


typedef unsigned long int uint_fast8_t;
typedef unsigned long int uint_fast16_t;
typedef unsigned long int uint_fast32_t;
typedef unsigned long long uint_fast64_t;


typedef signed long int intptr_t;
typedef unsigned long int uintptr_t;


typedef signed long long intmax_t;
typedef unsigned long long uintmax_t;
#line 13 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_8x8_click/example/arm/oled_types.h"
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
 OLED_STATUS_SUCCESS,
 OLED_STATUS_ERROR,
 OLED_STATUS_PROTOCOL_ERROR,
 OLED_STATUS_INIT_ERROR,
 OLED_STATUS_DEINIT_ERROR

} oled_status_t;
#line 41 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_8x8_click/example/arm/oled_types.h"
typedef uint16_t* oled_pixel_t;

typedef struct
{
 uint32_t DCpin;
 uint32_t CSpin;
 uint32_t RSTpin;

 uint32_t ENpin;

} settingsOLED_t;

typedef enum
{
 OLED_TEXT_ALIGN_NONE = 0,

 OLED_TEXT_ALIGN_LEFT = 0x1,
 OLED_TEXT_ALIGN_RIGHT = 0x2,
 OLED_TEXT_ALIGN_CENTER = 0x3,

 OLED_TEXT_VALIGN_TOP = 0x10,
 OLED_TEXT_VALIGN_BOTTOM = 0x20,
 OLED_TEXT_VALIGN_CENTER = 0x30

} oled_text_align_t;

typedef enum
{
 OLED_COLOR_BLACK = 0x0000,
 OLED_COLOR_BLUE_1 = 0x06FF,
 OLED_COLOR_BLUE = 0x001F,
 OLED_COLOR_RED = 0xF800,
 OLED_COLOR_GREEN = 0x07E0,
 OLED_COLOR_CYAN = 0x07FF,
 OLED_COLOR_MAGENTA = 0xF81F,
 OLED_COLOR_YELLOW = 0xFFE0,
 OLED_COLOR_GRAY = 0x528A,
 OLED_COLOR_WHITE = 0xFFFF

} oled_color_t;

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
#line 1 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_8x8_click/example/arm/oled_resources.h"
#line 1 "d:/work/mikroc pro for arm/include/stdint.h"
#line 6 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_8x8_click/example/arm/oled_resources.h"
extern const uint8_t guiFont_Tahoma_8_Regular[];

extern const code char RGB8x8_bmp[18438];
#line 12 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_8x8_click/example/arm/oled_driver.h"
extern const uint8_t FO_HORIZONTAL;
extern const uint8_t FO_VERTICAL;
extern const uint8_t FO_VERTICAL_COLUMN;
#line 26 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_8x8_click/example/arm/oled_driver.h"
oled_status_t OLED_Init(void);
#line 41 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_8x8_click/example/arm/oled_driver.h"
oled_status_t OLED_DrawBox (
 uint16_t xCrd,
 uint16_t yCrd,
 uint16_t width,
 uint16_t height,
 uint16_t color
 );
#line 58 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_8x8_click/example/arm/oled_driver.h"
oled_status_t OLED_FillScreen( uint16_t color );
#line 72 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_8x8_click/example/arm/oled_driver.h"
oled_status_t OLED_DrawPixel (
 int16_t xCrd,
 int16_t yCrd,
 uint16_t color
 );





oled_status_t OLED_AddText( const uint8_t* text );





void OLED_SetTextProperties(oled_text_properties_t *textProperties);





uint8_t OLED_GetTextWidth(const uint8_t* text);





uint8_t OLED_CharCount(uint8_t width, const uint8_t* font, const uint8_t* text, uint8_t length);





void OLED_SetFont(const uint8_t *activeFont, uint16_t font_color, uint8_t font_orientation);





void OLED_SetDynamicArea(oled_dynamic_area_t *dynamic_area);





void OLED_WriteText(uint8_t *text, uint16_t x, uint16_t y);





oled_status_t OLED_DrawImage (const uint8_t* image, uint8_t xCrd, uint8_t yCrd);






void OLED_GetImageDimensions(uint8_t *width, uint8_t *height, const uint8_t* image);
#line 1 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_8x8_click/example/arm/oled_info.h"
#line 6 "D:/Marko/tasks/freescale/svn/Hexiwear/MK64/5. Click Demos/1. mikroC/2. Primeri/HEXIWEAR_8x8_Click/example/ARM/OLED_driver.c"
static uint8_t
 isFontInitialized = 0;

static const uint8_t*
 selectedFont;

static uint16_t
 selectedFont_color,
 selectedFont_firstChar,
 selectedFont_lastChar,
 selectedFont_height;

static oled_dynamic_area_t
 oled_dynamic_area;

static oled_text_properties_t oled_text_properties;

static uint8_t
 screenBuf[  ( (96)  * (96)  * ( 2 )  )  ];

static uint8_t
 currentChar_width = 0,
 currentChar_height = 0;

static uint16_t FontColor;
static uint8_t FontOrientation;
const uint8_t FO_HORIZONTAL = 0;
const uint8_t FO_VERTICAL = 1;
const uint8_t FO_VERTICAL_COLUMN = 2;
char ExternalFontSet;
static uint8_t FontInitialized = 0;

static code const uint8_t *_font;
static uint16_t _fontFirstChar;
static uint16_t _fontLastChar;
static uint16_t _fontHeight;


static uint16_t x_cord, y_cord;


sbit OLED_Pwr_bit at PTC_PDOR.B13;
sbit OLED_DC_bit at PTD_PDOR.B15;
sbit OLED_RST_bit at PTE_PDOR.B6;
sbit OLED_CS_bit at PTB_PDOR.B20;
#line 69 "D:/Marko/tasks/freescale/svn/Hexiwear/MK64/5. Click Demos/1. mikroC/2. Primeri/HEXIWEAR_8x8_Click/example/ARM/OLED_driver.c"
static void SetBorders(uint8_t xCrd, uint8_t yCrd, uint8_t width, uint8_t height);
static void OLED_Swap(oled_pixel_t imgDst, const uint8_t* imgSrc, uint16_t imgSize);

static void OLED_WriteChar(uint16_t ch);
static void OLED_MoveCursor(uint16_t _x, uint16_t _y);





void OLED_PowerOn(void)
{
 OLED_Pwr_bit = 1;
}





void OLED_PowerOff(void)
{
 OLED_Pwr_bit = 0;
}
#line 103 "D:/Marko/tasks/freescale/svn/Hexiwear/MK64/5. Click Demos/1. mikroC/2. Primeri/HEXIWEAR_8x8_Click/example/ARM/OLED_driver.c"
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
#line 136 "D:/Marko/tasks/freescale/svn/Hexiwear/MK64/5. Click Demos/1. mikroC/2. Primeri/HEXIWEAR_8x8_Click/example/ARM/OLED_driver.c"
oled_status_t OLED_Init(void)
{
 oled_text_properties.alignParam = OLED_TEXT_ALIGN_CENTER;
 oled_text_properties.background =  (void*)0 ;

 GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_13);
 GPIO_Digital_Output(&PTD_PDOR, _GPIO_PINMASK_15);
 GPIO_Digital_Output(&PTE_PDOR, _GPIO_PINMASK_6);
 GPIO_Digital_Output(&PTB_PDOR, _GPIO_PINMASK_20);

 SPI2_Init_Advanced(15000000, _SPI_CFG_MASTER | _SPI_CFG_SELECT_CTAR0 | _SPI_CFG_FRAME_SIZE_8BITS |
 _SPI_CFG_CLK_IDLE_HIGH | _SPI_CFG_CLK_PHASE_CAPT_LEADING | _SPI_CFG_MSB_FIRST, &_GPIO_Module_SPI2_PB21_23_22);
#line 152 "D:/Marko/tasks/freescale/svn/Hexiwear/MK64/5. Click Demos/1. mikroC/2. Primeri/HEXIWEAR_8x8_Click/example/ARM/OLED_driver.c"
 OLED_PowerOff();
 Delay_1ms();
 OLED_RST_bit = 0;
 Delay_1ms();
 OLED_RST_bit = 1;
 Delay_1ms();
 OLED_PowerOn();

 if ( OLED_STATUS_SUCCESS != OLED_SendCmd(  ( 0xFD ) ,  (1)  ) )
 {
 return OLED_STATUS_PROTOCOL_ERROR;
 }
 if ( OLED_STATUS_SUCCESS != OLED_SendCmd(  (0x12) ,  (0)  ) )
 {
 return OLED_STATUS_PROTOCOL_ERROR;
 }

 if ( OLED_STATUS_SUCCESS != OLED_SendCmd(  ( 0xFD ) ,  (1)  ) )
 {
 return OLED_STATUS_PROTOCOL_ERROR;
 }
 if ( OLED_STATUS_SUCCESS != OLED_SendCmd(  (0xB1) ,  (0)  ) )
 {
 return OLED_STATUS_PROTOCOL_ERROR;
 }

 if ( OLED_STATUS_SUCCESS != OLED_SendCmd(  (0xAE) ,  (1)  ) )
 {
 return OLED_STATUS_PROTOCOL_ERROR;
 }

 if ( OLED_STATUS_SUCCESS != OLED_SendCmd(  (0xB3) ,  (1)  ) )
 {
 return OLED_STATUS_PROTOCOL_ERROR;
 }
 if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0xF1,  (0)  ) )
 {
 return OLED_STATUS_PROTOCOL_ERROR;
 }

 if ( OLED_STATUS_SUCCESS != OLED_SendCmd(  (0xCA) ,  (1)  ) )
 {
 return OLED_STATUS_PROTOCOL_ERROR;
 }
 if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x5F,  (0)  ) )
 {
 return OLED_STATUS_PROTOCOL_ERROR;
 }

 if ( OLED_STATUS_SUCCESS != OLED_SendCmd(  ( 0xA0 ) ,  (1)  ) )
 {
 return OLED_STATUS_PROTOCOL_ERROR;
 }
 if ( OLED_STATUS_SUCCESS != OLED_SendCmd(  ( ( 0 )  | ( 1 << 5 )  | ( 1 << 6 )  | ( 0 )  | ( 0 )  | ( 0 )  ) ,  (0)  ) )
 {
 return OLED_STATUS_PROTOCOL_ERROR;
 }

 if ( OLED_STATUS_SUCCESS != OLED_SendCmd(  ( 0x15 ) ,  (1)  ) )
 {
 return OLED_STATUS_PROTOCOL_ERROR;
 }
 if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x00,  (0)  ) )
 {
 return OLED_STATUS_PROTOCOL_ERROR;
 }
 if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x5F,  (0)  ) )
 {
 return OLED_STATUS_PROTOCOL_ERROR;
 }

 if ( OLED_STATUS_SUCCESS != OLED_SendCmd(  ( 0x75 ) ,  (1)  ) )
 {
 return OLED_STATUS_PROTOCOL_ERROR;
 }
 if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x00,  (0)  ) )
 {
 return OLED_STATUS_PROTOCOL_ERROR;
 }
 if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x5F,  (0)  ) )
 {
 return OLED_STATUS_PROTOCOL_ERROR;
 }

 if ( OLED_STATUS_SUCCESS != OLED_SendCmd(  (0xA1) ,  (1)  ) )
 {
 return OLED_STATUS_PROTOCOL_ERROR;
 }
 if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x80,  (0)  ) )
 {
 return OLED_STATUS_PROTOCOL_ERROR;
 }

 if ( OLED_STATUS_SUCCESS != OLED_SendCmd(  (0xA2) ,  (1)  ) )
 {
 return OLED_STATUS_PROTOCOL_ERROR;
 }
 if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x60,  (0)  ) )
 {
 return OLED_STATUS_PROTOCOL_ERROR;
 }

 if ( OLED_STATUS_SUCCESS != OLED_SendCmd(  (0xB1) ,  (1)  ) )
 {
 return OLED_STATUS_PROTOCOL_ERROR;
 }
 if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x32,  (1)  ) )
 {
 return OLED_STATUS_PROTOCOL_ERROR;
 }

 if ( OLED_STATUS_SUCCESS != OLED_SendCmd(  (0xBE) ,  (1)  ) )
 {
 return OLED_STATUS_PROTOCOL_ERROR;
 }
 if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x05,  (1)  ) )
 {
 return OLED_STATUS_PROTOCOL_ERROR;
 }

 if ( OLED_STATUS_SUCCESS != OLED_SendCmd(  (0xA6) ,  (1)  ) )
 {
 return OLED_STATUS_PROTOCOL_ERROR;
 }

 if ( OLED_STATUS_SUCCESS != OLED_SendCmd(  (0xC1) ,  (1)  ) )
 {
 return OLED_STATUS_PROTOCOL_ERROR;
 }
 if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x8A,  (0)  ) )
 {
 return OLED_STATUS_PROTOCOL_ERROR;
 }
 if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x51,  (0)  ) )
 {
 return OLED_STATUS_PROTOCOL_ERROR;
 }
 if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x8A,  (0)  ) )
 {
 return OLED_STATUS_PROTOCOL_ERROR;
 }

 if ( OLED_STATUS_SUCCESS != OLED_SendCmd(  (0xC7) ,  (1)  ) )
 {
 return OLED_STATUS_PROTOCOL_ERROR;
 }
 if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0xCF,  (0)  ) )
 {
 return OLED_STATUS_PROTOCOL_ERROR;
 }

 if ( OLED_STATUS_SUCCESS != OLED_SendCmd(  (0xB4) ,  (1)  ) )
 {
 return OLED_STATUS_PROTOCOL_ERROR;
 }
 if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0xA0,  (0)  ) )
 {
 return OLED_STATUS_PROTOCOL_ERROR;
 }
 if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0xB5,  (0)  ) )
 {
 return OLED_STATUS_PROTOCOL_ERROR;
 }
 if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x55,  (0)  ) )
 {
 return OLED_STATUS_PROTOCOL_ERROR;
 }

 if ( OLED_STATUS_SUCCESS != OLED_SendCmd(  (0xB6) ,  (1)  ) )
 {
 return OLED_STATUS_PROTOCOL_ERROR;
 }
 if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x01,  (0)  ) )
 {
 return OLED_STATUS_PROTOCOL_ERROR;
 }

 if ( OLED_STATUS_SUCCESS != OLED_SendCmd(  (0xAF) ,  (1)  ) )
 {
 return OLED_STATUS_PROTOCOL_ERROR;
 }

 return OLED_STATUS_SUCCESS;
}
#line 345 "D:/Marko/tasks/freescale/svn/Hexiwear/MK64/5. Click Demos/1. mikroC/2. Primeri/HEXIWEAR_8x8_Click/example/ARM/OLED_driver.c"
oled_status_t OLED_SendData(
 const uint8_t* dataToSend,
 uint32_t dataSize
 )
{
 oled_status_t spiStatus;
 const uint8_t* bufPtr;

 if ( OLED_STATUS_SUCCESS != OLED_SendCmd(  (0x5C) ,  (1)  ) )
 {
 return OLED_STATUS_PROTOCOL_ERROR;
 }


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
#line 386 "D:/Marko/tasks/freescale/svn/Hexiwear/MK64/5. Click Demos/1. mikroC/2. Primeri/HEXIWEAR_8x8_Click/example/ARM/OLED_driver.c"
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


 if ( ( 0 != ( ( ( xCrd + width - 1 ) > (96)  ) || ( xCrd < 0 ) || ( ( yCrd + height - 1 ) > (96)  ) || ( yCrd < 0 ) )  ) )
 {
 status = OLED_STATUS_INIT_ERROR;
 }
 else
 {
#line 409 "D:/Marko/tasks/freescale/svn/Hexiwear/MK64/5. Click Demos/1. mikroC/2. Primeri/HEXIWEAR_8x8_Click/example/ARM/OLED_driver.c"
 uint16_t cnt;
#line 416 "D:/Marko/tasks/freescale/svn/Hexiwear/MK64/5. Click Demos/1. mikroC/2. Primeri/HEXIWEAR_8x8_Click/example/ARM/OLED_driver.c"
  xCrd += (16) ;
  yCrd += (0) ;

 if ( OLED_STATUS_SUCCESS != OLED_SendCmd(  ( 0x15 ) ,  (1)  ) )
 {
 return OLED_STATUS_PROTOCOL_ERROR;
 }
 if ( OLED_STATUS_SUCCESS != OLED_SendCmd( xCrd,  (0)  ) )
 {
 return OLED_STATUS_PROTOCOL_ERROR;
 }
 if ( OLED_STATUS_SUCCESS != OLED_SendCmd( xCrd + (width-1),  (0)  ) )
 {
 return OLED_STATUS_PROTOCOL_ERROR;
 }

 if ( OLED_STATUS_SUCCESS != OLED_SendCmd(  ( 0x75 ) ,  (1)  ) )
 {
 return OLED_STATUS_PROTOCOL_ERROR;
 }
 if ( OLED_STATUS_SUCCESS != OLED_SendCmd( yCrd,  (0)  ) )
 {
 return OLED_STATUS_PROTOCOL_ERROR;
 }
 if ( OLED_STATUS_SUCCESS != OLED_SendCmd( yCrd + (height-1),  (0)  ) )
 {
 return OLED_STATUS_PROTOCOL_ERROR;
 }

 if ( OLED_STATUS_SUCCESS != OLED_SendCmd(  (0x5C) ,  (1)  ) )
 {
 return OLED_STATUS_PROTOCOL_ERROR;
 }

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
#line 474 "D:/Marko/tasks/freescale/svn/Hexiwear/MK64/5. Click Demos/1. mikroC/2. Primeri/HEXIWEAR_8x8_Click/example/ARM/OLED_driver.c"
oled_status_t OLED_FillScreen( uint16_t color )
{
 return OLED_DrawBox(0, 0, 96, 96, color);;
}
#line 491 "D:/Marko/tasks/freescale/svn/Hexiwear/MK64/5. Click Demos/1. mikroC/2. Primeri/HEXIWEAR_8x8_Click/example/ARM/OLED_driver.c"
oled_status_t OLED_DrawPixel (
 int16_t xCrd,
 int16_t yCrd,
 uint16_t color
 )
{

 if  ( 0 != ( ( ( xCrd + 1 - 1 ) > (96)  ) || ( xCrd < 0 ) || ( ( yCrd + 1 - 1 ) > (96)  ) || ( yCrd < 0 ) )  ) 
 {
 return OLED_STATUS_INIT_ERROR;
 }

 else
 {
 uint16_t dot = color;


 SetBorders( xCrd, yCrd,  (96) ,  (96) );

  dot = ( ( dot & 0xFF00 ) >> 8 ) | ( ( dot & 0x00FF ) << 8 ) ;


 if ( OLED_STATUS_SUCCESS != OLED_SendData( (uint8_t*)&dot, 2 ) )
 {
 return OLED_STATUS_PROTOCOL_ERROR;
 }
 return OLED_STATUS_SUCCESS;
 }
}
#line 531 "D:/Marko/tasks/freescale/svn/Hexiwear/MK64/5. Click Demos/1. mikroC/2. Primeri/HEXIWEAR_8x8_Click/example/ARM/OLED_driver.c"
static void SetBorders(
 uint8_t xCrd,
 uint8_t yCrd,
 uint8_t width,
 uint8_t height
 )
{
 oled_status_t oledStatus;


  xCrd += (16) ;
  yCrd += (0) ;

 while (1)
 {
 oledStatus = OLED_STATUS_SUCCESS;

 oledStatus |= OLED_SendCmd(  ( 0x15 ) ,  (1)  );
 oledStatus |= OLED_SendCmd( xCrd,  (0)  );
 oledStatus |= OLED_SendCmd( xCrd + (width-1),  (0)  );
 oledStatus |= OLED_SendCmd(  ( 0x75 ) ,  (1)  );
 oledStatus |= OLED_SendCmd( yCrd,  (0)  );
 oledStatus |= OLED_SendCmd( yCrd + (height-1),  (0)  );

 if ( OLED_STATUS_SUCCESS == oledStatus)
 {
 break;
 }
 }
}







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





void OLED_GetImageDimensions(uint8_t *width, uint8_t *height, const uint8_t* image)
{
 *height = image[2] + (image[3] << 8);
 *width = image[4] + (image[5] << 8);
}





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


 if  ( 0 != ( ( ( xCrd + width - 1 ) > (96)  ) || ( xCrd < 0 ) || ( ( yCrd + height - 1 ) > (96)  ) || ( yCrd < 0 ) )  ) 
 {
 status = OLED_STATUS_INIT_ERROR;
 }

 else
 {
 OLED_Swap( screenBuf, (const uint8_t*)( image ) + 6 , width * height );



 }


 SetBorders( xCrd, yCrd, width, height );


 if ( OLED_STATUS_SUCCESS != OLED_SendData( (const uint8_t*)screenBuf, width * height *  ( 2 )  ) )
 {
 return OLED_STATUS_PROTOCOL_ERROR;
 }

 return OLED_STATUS_SUCCESS;
}





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






void OLED_WriteText(uint8_t *text, uint16_t x, uint16_t y) {
 uint16_t i;

 if (x >=  (96) )
 return;
 if (y >=  (96) )
 return;

 i = 0;
 OLED_MoveCursor(x, y);
 while (text[i])
 OLED_WriteChar(text[i++]);
}





static void OLED_MoveCursor(uint16_t _x, uint16_t _y)
{
 x_cord = _x;
 y_cord = _y;
}





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
 OLED_SetFont(guiFont_Tahoma_8_Regular, OLED_COLOR_BLACK, FO_HORIZONTAL);
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


 if (FontOrientation == FO_HORIZONTAL)
 {
 x_cord = x + 1;
 }
 else
 {
 y_cord = y;
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


 y_cord = x - 1;
 }
}

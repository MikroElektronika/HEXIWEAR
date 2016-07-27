#line 1 "D:/Marko/tasks/freescale/svn/Hexiwear/MK64/5. Click Demos/1. mikroC/2. Primeri/HEXIWEAR_8x8_Click/example/ARM/HEXIWEAR_8x8_Click.c"
#line 1 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_8x8_click/example/arm/eight_x_eight_hw.h"
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
#line 124 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_8x8_click/example/arm/eight_x_eight_hw.h"
void led_eight_init( void );
#line 136 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_8x8_click/example/arm/eight_x_eight_hw.h"
void led_eight_display_one_col( uint8_t row, uint8_t col );
#line 161 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_8x8_click/example/arm/eight_x_eight_hw.h"
void led_eight_display_image( uint8_t* image );
#line 186 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_8x8_click/example/arm/eight_x_eight_hw.h"
void led_eight_display_const_image( const uint8_t* image );
#line 201 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_8x8_click/example/arm/eight_x_eight_hw.h"
void led_eight_display_string( const uint8_t* images );
#line 210 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_8x8_click/example/arm/eight_x_eight_hw.h"
void led_eight_display_shift_left( void );
#line 238 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_8x8_click/example/arm/eight_x_eight_hw.h"
void led_eight_set_intensity( uint8_t intensity );
#line 258 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_8x8_click/example/arm/eight_x_eight_hw.h"
void led_eight_set_scan_limit( uint8_t scan_limit );
#line 270 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_8x8_click/example/arm/eight_x_eight_hw.h"
void led_eight_shut_down( void );

void led_eight_display_test( void );
#line 290 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_8x8_click/example/arm/eight_x_eight_hw.h"
void led_eight_scroll_text( uint8_t* str, uint8_t delay );
#line 1 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_8x8_click/example/arm/oled_driver.h"
#line 1 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_8x8_click/example/arm/oled_types.h"
#line 1 "d:/work/mikroc pro for arm/include/stdint.h"
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
#line 63 "D:/Marko/tasks/freescale/svn/Hexiwear/MK64/5. Click Demos/1. mikroC/2. Primeri/HEXIWEAR_8x8_Click/example/ARM/HEXIWEAR_8x8_Click.c"
sbit LED_EIGHT_CS at PTC_PDOR.B4;
#line 73 "D:/Marko/tasks/freescale/svn/Hexiwear/MK64/5. Click Demos/1. mikroC/2. Primeri/HEXIWEAR_8x8_Click/example/ARM/HEXIWEAR_8x8_Click.c"
uint8_t text_1[] = "HEXIWEAR ";
uint8_t text_2[] = "NXP ";
uint8_t text_3[] = "MIKROE ";
void main()
{
 OLED_Init();
 OLED_DrawImage( &RGB8x8_bmp, 0, 0 );

 GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_4);
 SPI0_Init_Advanced(5000000, _SPI_CFG_MASTER | _SPI_CFG_SELECT_CTAR0 | _SPI_CFG_FRAME_SIZE_8BITS |
 _SPI_CFG_CLK_IDLE_LOW | _SPI_CFG_CLK_PHASE_CAPT_LEADING | _SPI_CFG_MSB_FIRST, &_GPIO_Module_SPI0_PC5_7_6);

 Delay_ms(400);

 led_eight_init();

 while(1)
 {
 led_eight_scroll_text(text_1, 10);
 led_eight_scroll_text(text_2, 10);
 led_eight_scroll_text(text_3, 10);
 }
}

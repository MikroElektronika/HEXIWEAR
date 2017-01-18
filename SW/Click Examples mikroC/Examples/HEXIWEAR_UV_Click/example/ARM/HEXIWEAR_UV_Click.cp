#line 1 "D:/Marko/tasks/freescale/svn/Hexiwear/MK64/5. Click Demos/1. mikroC/2. Primeri/HEXIWEAR_UV_Click/example/ARM/HEXIWEAR_UV_Click.c"
#line 1 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_uv_click/example/arm/oled_driver.h"
#line 1 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_uv_click/example/arm/oled_types.h"
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
#line 13 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_uv_click/example/arm/oled_types.h"
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
#line 41 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_uv_click/example/arm/oled_types.h"
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
#line 1 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_uv_click/example/arm/oled_resources.h"
#line 1 "d:/work/mikroc pro for arm/include/stdint.h"
#line 6 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_uv_click/example/arm/oled_resources.h"
extern const uint8_t guiFont_Tahoma_8_Regular[];

extern const uint8_t uv_bmp[18438];
#line 12 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_uv_click/example/arm/oled_driver.h"
extern const uint8_t FO_HORIZONTAL;
extern const uint8_t FO_VERTICAL;
extern const uint8_t FO_VERTICAL_COLUMN;
#line 26 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_uv_click/example/arm/oled_driver.h"
oled_status_t OLED_Init(void);
#line 41 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_uv_click/example/arm/oled_driver.h"
oled_status_t OLED_DrawBox (
 uint16_t xCrd,
 uint16_t yCrd,
 uint16_t width,
 uint16_t height,
 uint16_t color
 );
#line 58 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_uv_click/example/arm/oled_driver.h"
oled_status_t OLED_FillScreen( uint16_t color );
#line 72 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_uv_click/example/arm/oled_driver.h"
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
#line 65 "D:/Marko/tasks/freescale/svn/Hexiwear/MK64/5. Click Demos/1. mikroC/2. Primeri/HEXIWEAR_UV_Click/example/ARM/HEXIWEAR_UV_Click.c"
sbit UV_Enable at PTB_PDOR.B19;
sbit UV_Input at PTB_PDOR.B3;

static uint8_t
 uvText[] = "UV ~ ",
 uvUnit[] = "mV";

static uint8_t
 uvLevel[6] = {0};
#line 78 "D:/Marko/tasks/freescale/svn/Hexiwear/MK64/5. Click Demos/1. mikroC/2. Primeri/HEXIWEAR_UV_Click/example/ARM/HEXIWEAR_UV_Click.c"
static uint16_t GetADC();
static void ProcessValue( uint16_t valueTemp );
static void InitModules();
#line 85 "D:/Marko/tasks/freescale/svn/Hexiwear/MK64/5. Click Demos/1. mikroC/2. Primeri/HEXIWEAR_UV_Click/example/ARM/HEXIWEAR_UV_Click.c"
void main() org 0x1000
{
 uint16_t
 measurement = 0;


 InitModules();

 while(1)
 {

 measurement = GetADC();


 ProcessValue( measurement );


 Delay_ms(500);
 }
}
#line 117 "D:/Marko/tasks/freescale/svn/Hexiwear/MK64/5. Click Demos/1. mikroC/2. Primeri/HEXIWEAR_UV_Click/example/ARM/HEXIWEAR_UV_Click.c"
static void InitModules()
{
 GPIO_Digital_Output( &PTB_PDOR, _GPIO_PINMASK_19 );

 OLED_Init();
 OLED_DrawImage( &uv_bmp, 0, 0 );

 OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_BLACK, 0 );
 OLED_WriteText( uvText, 20, 75 );
 OLED_WriteText( uvUnit, 72, 75 );


 ADC0_Init();

 Delay_ms(100);


 UV_Enable = 1;
}
#line 144 "D:/Marko/tasks/freescale/svn/Hexiwear/MK64/5. Click Demos/1. mikroC/2. Primeri/HEXIWEAR_UV_Click/example/ARM/HEXIWEAR_UV_Click.c"
static uint16_t GetADC()
{
 uint32_t
 i,
 adcVal = 0,
 avrg = 0;

 for ( i = 0; i < 16; i++ )
 {
 adcVal = ADC0_Get_Sample( 13 );
 avrg += adcVal;
 }

 return ( avrg >> 4 );
}
#line 167 "D:/Marko/tasks/freescale/svn/Hexiwear/MK64/5. Click Demos/1. mikroC/2. Primeri/HEXIWEAR_UV_Click/example/ARM/HEXIWEAR_UV_Click.c"
static void ProcessValue( uint16_t valueTemp )
{
 float
 UV_val;

 if ((valueTemp > 1100) && (valueTemp < 4095))
 {

 OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_WHITE, 0 );
 OLED_WriteText( uvLevel, 42, 75 );


 UV_val = valueTemp * 3300.0 / 4096.0;
 WordToStr( (uint16_t)UV_val, uvLevel );
 OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_BLACK, 0 );
 OLED_WriteText( uvLevel, 42, 75 );
 }
 else
 {
 UV_val = -1;
 }
}

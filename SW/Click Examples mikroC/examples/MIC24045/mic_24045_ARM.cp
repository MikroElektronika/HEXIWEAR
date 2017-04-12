#line 1 "C:/Users/djordje.rosic/Desktop/Archive/mic_24045_click/example/ARM/mic_24045_ARM.c"
#line 1 "c:/users/djordje.rosic/desktop/archive/mic_24045_click/library/include/oled_driver.h"
#line 1 "c:/users/djordje.rosic/desktop/archive/mic_24045_click/library/include/oled_types.h"
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for arm/include/stdint.h"





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
#line 13 "c:/users/djordje.rosic/desktop/archive/mic_24045_click/library/include/oled_types.h"
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
#line 41 "c:/users/djordje.rosic/desktop/archive/mic_24045_click/library/include/oled_types.h"
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
#line 1 "c:/users/djordje.rosic/desktop/archive/mic_24045_click/library/include/oled_resources.h"
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for arm/include/stdint.h"
#line 6 "c:/users/djordje.rosic/desktop/archive/mic_24045_click/library/include/oled_resources.h"
extern const uint8_t guiFont_Tahoma_18_Regular[];
extern const uint8_t guiFont_Tahoma_16_Regular[];
extern const uint8_t guiFont_Tahoma_14_Regular[];
extern const uint8_t guiFont_Tahoma_10_Regular[];
extern const uint8_t guiFont_Tahoma_8_Regular[];
extern const uint8_t guiFont_Tahoma_7_Regular[];
extern const uint8_t guiFont_Tahoma_6_Regular[];
extern const uint8_t guiFont_Roboto_Mono11x23_Regular[];
extern const uint8_t guiFont_Exo_2_Condensed10x16_Regular[];
extern const uint8_t guiFont_Exo_2_Condensed15x23_Regular[];
extern const uint8_t guiFont_Exo_2_Condensed21x32_Regular[];

extern const uint8_t hexiwearLogo_bmp[18438];
const code char heart_rate_bmp[18438];
#line 22 "c:/users/djordje.rosic/desktop/archive/mic_24045_click/library/include/oled_driver.h"
oled_status_t OLED_Init(void);
#line 37 "c:/users/djordje.rosic/desktop/archive/mic_24045_click/library/include/oled_driver.h"
oled_status_t OLED_DrawBox (
 uint16_t xCrd,
 uint16_t yCrd,
 uint16_t width,
 uint16_t height,
 uint16_t color
 );
#line 54 "c:/users/djordje.rosic/desktop/archive/mic_24045_click/library/include/oled_driver.h"
oled_status_t OLED_FillScreen( uint16_t color );
#line 68 "c:/users/djordje.rosic/desktop/archive/mic_24045_click/library/include/oled_driver.h"
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
#line 1 "c:/users/djordje.rosic/desktop/archive/mic_24045_click/library/include/oled_resources.h"
#line 1 "c:/users/djordje.rosic/desktop/archive/mic_24045_click/library/include/uart_messaging.h"
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for arm/include/stdint.h"
#line 22 "c:/users/djordje.rosic/desktop/archive/mic_24045_click/library/include/uart_messaging.h"
typedef enum
{
 PT_PRESS_UP = 0,
 PT_PRESS_DOWN = 1,
 PT_PRESS_LEFT = 2,
 PT_PRESS_RIGHT = 3,
} packet_type;

typedef void (*packet_msg_callback)( void );
#line 35 "c:/users/djordje.rosic/desktop/archive/mic_24045_click/library/include/uart_messaging.h"
void hexiwear_uart_messaging_callback(
 packet_type type,
 packet_msg_callback callback
);

void hexiwear_uart_messaging_init( void );
void hexiwear_uart_messaging_process( void );
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for arm/include/stdint.h"
#line 35 "C:/Users/djordje.rosic/Desktop/Archive/mic_24045_click/example/ARM/mic_24045_ARM.c"
sbit MIC24045_EN_PIN at PTB_PDOR.B11;
char read_value;
char write_text [15];
uint8_t i;
float write_1;
float read_2;

static void system_init( void )
{

 Delay_ms (100);

 SPI0_Init_Advanced( 16000000, _SPI_CFG_MASTER |
 _SPI_CFG_FRAME_SIZE_8BITS |
 _SPI_CFG_CLK_IDLE_LOW |
 _SPI_CFG_CLK_PHASE_CHG_LEADING |
 _SPI_CFG_MSB_FIRST,
 &_GPIO_Module_SPI0_PC5_7_6);


 I2C0_Init_Advanced( 400000, &_GPIO_Module_I2C0_PD8_9 );
 Delay_ms (100);
 GPIO_Digital_Output( &PTB_PDOR, _GPIO_PINMASK_11 );
}

void main()
{
 memset (write_text, 0, 15);
 system_init();
 mic_24045_init(0x50);
 Delay_ms (100);


 OLED_init();
 OLED_SetFont( guiFont_Exo_2_Condensed10x16_Regular, OLED_COLOR_WHITE, 0 );
 OLED_FillScreen( OLED_COLOR_BLACK );
 OLED_WriteText("Initialized", 20, 8 );
 Delay_ms (2000);
 i = 21;

 while (i)
 {
 write_1 = i*0.25;
 mic_24045_write_vout (write_1);
 MIC24045_EN_PIN = 1;
 Delay_ms (1000);

 read_2 = mic_24045_read_vout ();
 FloatToStr (read_2, &write_text);

 if (read_2 > 1)
 write_text [5] = 0;


 if (i == 18)
 {

 i-=3;
 }
 OLED_FillScreen( OLED_COLOR_BLACK );
 OLED_WriteText("Current voltage:", 1, 8 );
 strcat (write_text, " V");
 OLED_WriteText(write_text, 20, 28 );
 Delay_ms (1000);
#line 106 "C:/Users/djordje.rosic/Desktop/Archive/mic_24045_click/example/ARM/mic_24045_ARM.c"
 MIC24045_EN_PIN = 0;
 Delay_ms (1000);
 i--;
 }

}

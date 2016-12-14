#line 1 "D:/Uros/!!KONACNI PRIMERI/HEXIWEAR_4x4_RGB_Click/4x4 RGB click.c"
#line 1 "d:/uros/!!konacni primeri/hexiwear_4x4_rgb_click/oled/inc/oled_driver.h"
#line 1 "d:/uros/!!konacni primeri/hexiwear_4x4_rgb_click/oled/inc/oled_types.h"
#line 1 "d:/program files/nxp/mikroc pro for arm/include/stdint.h"





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
#line 13 "d:/uros/!!konacni primeri/hexiwear_4x4_rgb_click/oled/inc/oled_types.h"
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
#line 41 "d:/uros/!!konacni primeri/hexiwear_4x4_rgb_click/oled/inc/oled_types.h"
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
#line 1 "d:/uros/!!konacni primeri/hexiwear_4x4_rgb_click/oled/inc/oled_resources.h"
#line 1 "d:/program files/nxp/mikroc pro for arm/include/stdint.h"
#line 6 "d:/uros/!!konacni primeri/hexiwear_4x4_rgb_click/oled/inc/oled_resources.h"
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
extern const code char A4x4RGB_bmp[18438];
#line 22 "d:/uros/!!konacni primeri/hexiwear_4x4_rgb_click/oled/inc/oled_driver.h"
oled_status_t OLED_Init(void);
#line 37 "d:/uros/!!konacni primeri/hexiwear_4x4_rgb_click/oled/inc/oled_driver.h"
oled_status_t OLED_DrawBox (
 uint16_t xCrd,
 uint16_t yCrd,
 uint16_t width,
 uint16_t height,
 uint16_t color
 );
#line 54 "d:/uros/!!konacni primeri/hexiwear_4x4_rgb_click/oled/inc/oled_driver.h"
oled_status_t OLED_FillScreen( uint16_t color );
#line 68 "d:/uros/!!konacni primeri/hexiwear_4x4_rgb_click/oled/inc/oled_driver.h"
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
#line 73 "D:/Uros/!!KONACNI PRIMERI/HEXIWEAR_4x4_RGB_Click/4x4 RGB click.c"
int i;
int n;
unsigned long DiodeArray[ 16 ];
unsigned long TempColor;
sbit RGBLed_Data at PTB_PDOR.B11;
#line 83 "D:/Uros/!!KONACNI PRIMERI/HEXIWEAR_4x4_RGB_Click/4x4 RGB click.c"
void RGBLed_ZeroBit();
void RGBLed_OneBit();
void RGBLed_ResetDelay();
void RGBLed_InitDiode();
void RGBLed_SetColor();
void RGBLed_SetDiode();
void RGBLed_InitHW();
void Delay_time();
void Snake();
void Snake_return();
void FillScreen();
#line 102 "D:/Uros/!!KONACNI PRIMERI/HEXIWEAR_4x4_RGB_Click/4x4 RGB click.c"
void RGBLed_ZeroBit() {
 RGBLed_Data = 1;
 Delay_Cyc(3);
 RGBLed_Data = 0;
 Delay_Cyc(7);
}

void RGBLed_OneBit() {
 RGBLed_Data = 1;
 Delay_Cyc(7);
 RGBLed_Data = 0;
 Delay_Cyc(6);
}

void RGBLed_ResetDelay() {
 Delay_50us();
 Delay_10us();
}

void RGBLed_InitDiode(unsigned long ARGBColor, unsigned long * AdiodeArray) {
 *AdiodeArray = (ARGBColor & 0x000000FF) | ((ARGBColor >> 16) << 8) | ((ARGBColor >> 8) << 16);
}

void RGBLed_SetColor(unsigned long * AdiodeArray) {
 signed char i;

 for (i = 23; i >= 0; i--) {
 if (( (*AdiodeArray) & (1ul << i)) == 0) {
 RGBLed_ZeroBit();
 }
 else {
 RGBLed_OneBit();
 }
 }
}

void RGBLed_SetDiode(char ANum, unsigned long AColor, unsigned long * AdiodeArray) {
 char i;

 for (i = 0; i <  16 ; i++) {
 if (i == (ANum - 1)) {
 RGBLed_InitDiode(AColor, &AdiodeArray[i]);
 RGBLed_SetColor(&AdiodeArray[i]);
 }
 else {
 RGBLed_SetColor(&AdiodeArray[i]);
 }
 }
 RGBLed_ResetDelay();
}

void RGBLed_InitHW() {
 GPIO_Digital_Output( &PTB_PDOR, _GPIO_PINMASK_11);
}


void Delay_time() {
 unsigned int n1;
 for (n1=1; n1<=n; n1++)
 delay_ms(5);
}


void Snake() {
 RGBLed_SetDiode(4, TempColor, DiodeArray);
 Delay_time();
 RGBLed_SetDiode(3, TempColor, DiodeArray);
 Delay_time();
 RGBLed_SetDiode(2, TempColor, DiodeArray);
 Delay_time();
 RGBLed_SetDiode(1, TempColor, DiodeArray);
 Delay_time();
 RGBLed_SetDiode(5, TempColor, DiodeArray);
 Delay_time();
 RGBLed_SetDiode(9, TempColor, DiodeArray);
 Delay_time();
 RGBLed_SetDiode(13, TempColor, DiodeArray);
 Delay_time();
 RGBLed_SetDiode(14, TempColor, DiodeArray);
 Delay_time();
 RGBLed_SetDiode(15, TempColor, DiodeArray);
 Delay_time();
 RGBLed_SetDiode(16, TempColor, DiodeArray);
 Delay_time();
 RGBLed_SetDiode(12, TempColor, DiodeArray);
 Delay_time();
 RGBLed_SetDiode(8, TempColor, DiodeArray);
 Delay_time();
 RGBLed_SetDiode(7, TempColor, DiodeArray);
 Delay_time();
 RGBLed_SetDiode(6, TempColor, DiodeArray);
 Delay_time();
 RGBLed_SetDiode(10, TempColor, DiodeArray);
 Delay_time();
 RGBLed_SetDiode(11, TempColor, DiodeArray);
}

 void Snake_return () {
 RGBLed_SetDiode(11, TempColor, DiodeArray);
 Delay_time();
 RGBLed_SetDiode(10, TempColor, DiodeArray);
 Delay_time();
 RGBLed_SetDiode(6, TempColor, DiodeArray);
 Delay_time();
 RGBLed_SetDiode(7, TempColor, DiodeArray);
 Delay_time();
 RGBLed_SetDiode(8, TempColor, DiodeArray);
 Delay_time();
 RGBLed_SetDiode(12, TempColor, DiodeArray);
 Delay_time();
 RGBLed_SetDiode(16, TempColor, DiodeArray);
 Delay_time();
 RGBLed_SetDiode(15, TempColor, DiodeArray);
 Delay_time();
 RGBLed_SetDiode(14, TempColor, DiodeArray);
 Delay_time();
 RGBLed_SetDiode(13, TempColor, DiodeArray);
 Delay_time();
 RGBLed_SetDiode(9, TempColor, DiodeArray);
 Delay_time();
 RGBLed_SetDiode(5, TempColor, DiodeArray);
 Delay_time();
 RGBLed_SetDiode(1, TempColor, DiodeArray);
 Delay_time();
 RGBLed_SetDiode(2, TempColor, DiodeArray);
 Delay_time();
 RGBLed_SetDiode(3, TempColor, DiodeArray);
 Delay_time();
 RGBLed_SetDiode(4, TempColor, DiodeArray);
 Delay_time();
}


void FillScreen() {
 unsigned int n2;
 for (n2=1; n2<=16; n2++) {
 RGBLed_SetDiode(n2, TempColor, DiodeArray);
 delay_ms(100);
 }
}


void main()
 {
 OLED_Init();
 OLED_DrawImage( A4x4RGB_bmp, 0, 0 );
 RGBLed_InitHW();
 TempColor = 0x002F2F2F;
 FillScreen();
 while(1)
 {

 n=20;
 TempColor = 0x0000002F;
 Snake();
 TempColor = 0x00002F2F;
 Snake_return ();


 n=15;
 TempColor = 0x00002F00;
 Snake();
 TempColor = 0x002F2F00;
 Snake_return();


 TempColor = 0x002F0000;
 n=10;
 Snake();
 TempColor = 0x002F002F;
 Snake_return ();


 n=5;
 TempColor = 0x002F2F2F;
 Snake_return ();
 }
 }

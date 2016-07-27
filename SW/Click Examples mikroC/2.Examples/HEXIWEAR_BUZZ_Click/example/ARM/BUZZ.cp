#line 1 "D:/Uros/!!KONACNI PRIMERI/HEXIWEAR_BUZZ_Click/example/ARM/BUZZ.c"
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
#line 1 "d:/uros/!!konacni primeri/hexiwear_buzz_click/example/arm/buzz.h"
#line 1 "d:/uros/!!konacni primeri/hexiwear_buzz_click/example/arm/oled/inc/oled_driver.h"
#line 1 "d:/uros/!!konacni primeri/hexiwear_buzz_click/example/arm/oled/inc/oled_types.h"
#line 1 "d:/program files/nxp/mikroc pro for arm/include/stdint.h"
#line 13 "d:/uros/!!konacni primeri/hexiwear_buzz_click/example/arm/oled/inc/oled_types.h"
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
#line 41 "d:/uros/!!konacni primeri/hexiwear_buzz_click/example/arm/oled/inc/oled_types.h"
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
#line 1 "d:/uros/!!konacni primeri/hexiwear_buzz_click/example/arm/oled/inc/oled_resources.h"
#line 1 "d:/program files/nxp/mikroc pro for arm/include/stdint.h"
#line 6 "d:/uros/!!konacni primeri/hexiwear_buzz_click/example/arm/oled/inc/oled_resources.h"
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
#line 22 "d:/uros/!!konacni primeri/hexiwear_buzz_click/example/arm/oled/inc/oled_driver.h"
oled_status_t OLED_Init(void);
#line 37 "d:/uros/!!konacni primeri/hexiwear_buzz_click/example/arm/oled/inc/oled_driver.h"
oled_status_t OLED_DrawBox (
 uint16_t xCrd,
 uint16_t yCrd,
 uint16_t width,
 uint16_t height,
 uint16_t color
 );
#line 54 "d:/uros/!!konacni primeri/hexiwear_buzz_click/example/arm/oled/inc/oled_driver.h"
oled_status_t OLED_FillScreen( uint16_t color );
#line 68 "d:/uros/!!konacni primeri/hexiwear_buzz_click/example/arm/oled/inc/oled_driver.h"
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
#line 1 "d:/uros/!!konacni primeri/hexiwear_buzz_click/example/arm/common/inc/common_screen_objects.h"
#line 1 "d:/uros/!!konacni primeri/hexiwear_buzz_click/example/arm/oled/inc/oled_driver.h"
#line 8 "d:/uros/!!konacni primeri/hexiwear_buzz_click/example/arm/common/inc/common_screen_objects.h"
extern const uint8_t
 common_hexiwearLogo_bmp[18438];
extern const uint8_t
 BUZZ_bmp[18438];
#line 88 "D:/Uros/!!KONACNI PRIMERI/HEXIWEAR_BUZZ_Click/example/ARM/BUZZ.c"
typedef enum
{
 touch_left = 0,
 touch_right = 1,
 touch_invalid = 0xFF

} touch_type_t;
#line 101 "D:/Uros/!!KONACNI PRIMERI/HEXIWEAR_BUZZ_Click/example/ARM/BUZZ.c"
typedef enum
{
 packetType_pressUp = 0,
 packetType_pressDown = 1,
 packetType_pressLeft = 2,
 packetType_pressRight = 3,
 packetType_slide = 4,
} hostInterface_packetType_t;

typedef struct
{

 uint8_t start1;
 uint8_t start2;
 hostInterface_packetType_t type;
 uint8_t length;
 uint8_t  __data [ 23  + 1];

} hostInterface_packet_t;

typedef enum
{
 hostInterface_rxState_idle = 0,
 hostInterface_rxState_headerReceived = 3,
 hostInterface_rxState_dataWait = 4,
 hostInterface_rxState_trailerWait = 5

} hostInterface_rxState_t;

int cntr;

bit playing;

bit STOPED;

const STOP_PLAYING = 1;

sbit KW40_RST at PTB_PDOR.B23;

static touch_type_t pressedTouch = touch_invalid;

static hostInterface_packet_t hostInterface_rxPacket;

uint8_t * pktBuf = ( uint8_t * ) &hostInterface_rxPacket;

static hostInterface_rxState_t hostInterface_rxState = hostInterface_rxState_idle;
#line 151 "D:/Uros/!!KONACNI PRIMERI/HEXIWEAR_BUZZ_Click/example/ARM/BUZZ.c"
static void PacketParser();
char play(long int freq, int ddd);
void play_melody();
#line 160 "D:/Uros/!!KONACNI PRIMERI/HEXIWEAR_BUZZ_Click/example/ARM/BUZZ.c"
static void PacketParser()
{
 static uint8_t byteCount;

 switch ( hostInterface_rxState )
 {
 case hostInterface_rxState_idle:
 {
 if (  0x55  == hostInterface_rxPacket.start1 )
 {
 hostInterface_rxState++;
 pktBuf++;
 }

 break;
 }

 case hostInterface_rxState_headerReceived:
 {
 if (
 (  0x55  != hostInterface_rxPacket.start1 )
 || (  0xAA  != ( hostInterface_rxPacket.start2 &
 0xFE ) )
 || ( hostInterface_rxPacket.length >  23  )
 )
 {

 hostInterface_rxState = hostInterface_rxState_idle;

 pktBuf = ( uint8_t * )&hostInterface_rxPacket;
 }

 else
 {

 pktBuf++;

 if ( 0 == hostInterface_rxPacket.length )
 {

 hostInterface_rxState = hostInterface_rxState_trailerWait;
 }

 else
 {
 byteCount = 0;

 hostInterface_rxState = hostInterface_rxState_dataWait;
 }
 }

 break;
 }

 case hostInterface_rxState_dataWait:
 {
 byteCount++;
 pktBuf++;


 if ( hostInterface_rxPacket.length == byteCount )
 {

 hostInterface_rxState = hostInterface_rxState_trailerWait;
 }

 break;
 }

 case hostInterface_rxState_trailerWait:
 {
 if (  0x45  == *pktBuf )
 {
 switch ( hostInterface_rxPacket.type )
 {
 case packetType_pressRight:
 {
 pressedTouch = touch_right;
 break;
 }
 case packetType_pressLeft:
 {
 pressedTouch = touch_left;
 break;
 }
 default:
 {
 pressedTouch = touch_invalid;
 }
 }
 }


 hostInterface_rxState = hostInterface_rxState_idle;

 pktBuf = ( uint8_t * )&hostInterface_rxPacket;
 break;
 }

 default:
 {
 hostInterface_rxState++;
 pktBuf++;
 }
 }
}
#line 274 "D:/Uros/!!KONACNI PRIMERI/HEXIWEAR_BUZZ_Click/example/ARM/BUZZ.c"
char play(long int freq, int delay_in_miliseconds){
int i, r=0;

PWM_FTM0_Init(freq,_PWM_EDGE_ALIGNED_PWM, _PWM_CHANNEL_1, &_GPIO_Module_PWM0_PTA4);
PWM_FTM0_Set_Duty(5,_PWM_NON_INVERTED,1);
for(i=0; i < delay_in_miliseconds; i++){
 if (STOPED) {
 r = STOP_PLAYING;
 return r;
 break;
 }
 delay_ms(1);
 }
 PWM_FTM0_Stop(1);
 return r;
}


void play_melody(){
while(1){
 if (play(220, 300 ) == STOP_PLAYING)
 break;
 Delay_ms(1+ 300 );
 if (play(220, 300 ) == STOP_PLAYING)
 break;
 Delay_ms(1+ 300 );
 if (play(220, 300 ) == STOP_PLAYING)
 break;
 Delay_ms(1+ 300 );
 if (play( 174 , 150 + 75 ) == STOP_PLAYING)
 break;
 Delay_ms(1+ 150 + 75 );
 if (play( 261 , 75 ) == STOP_PLAYING)
 break;
 Delay_ms(1+ 75 );

 if (play( 220 , 300 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 300 );
 if (play( 174 , 150 + 75 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 150 + 75 );
 if (play( 261 , 75 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 75 );
 if (play( 220 , 600 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 600 );

 if (play( 329 , 300 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 300 );
 if (play( 329 , 300 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 300 );
 if (play( 329 , 300 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 300 );
 if (play( 349 , 150 + 75 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 150 + 75 );
 if (play( 261 , 75 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 75 );

 if (play( 207 , 300 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 300 );
 if (play( 174 , 150 + 75 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 150 + 75 );
 if (play( 261 , 75 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 75 );
 if (play( 220 , 600 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 600 );

 if (play( 440 , 300 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 300 );
 if (play( 220 , 150 + 75 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 150 + 75 );
 if (play( 220 , 75 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 75 );
 if (play( 440 , 300 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 300 );
 if (play( 415 , 150 + 75 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 150 + 75 );
 if (play( 392 , 75 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 75 );

 if (play( 369 , 75 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 75 );
 if (play( 329 , 75 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 75 );
 if (play( 349 , 150 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 150 );
 Delay_ms(1+ 150 );
 if (play( 233 , 150 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 150 );
 if (play( 311 , 300 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 300 );
 if (play( 293 , 150 + 75 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 150 + 75 );
 if (play( 277 , 75 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 75 );

 if (play( 261 , 75 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 75 );
 if (play( 246 , 75 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 75 );
 if (play( 261 , 150 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 150 );
 Delay_ms(1+ 150 );
 if (play( 174 , 150 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 150 );
 if (play( 207 , 300 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 300 );
 if (play( 174 , 150 + 75 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 150 + 75 );
 if (play( 220 , 75 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 75 );

 if (play( 261 , 300 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 300 );
 if (play( 220 , 150 + 75 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 150 + 75 );
 if (play( 261 , 75 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 75 );
 if (play( 329 , 600 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 600 );

 if (play( 440 , 300 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 300 );
 if (play( 220 , 150 + 75 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 150 + 75 );
 if (play( 220 , 75 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 75 );
 if (play( 440 , 300 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 300 );
 if (play( 415 , 150 + 75 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 150 + 75 );
 if (play( 392 , 75 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 75 );

 if (play( 369 , 75 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 75 );
 if (play( 329 , 75 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 75 );
 if (play( 349 , 150 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 150 );
 Delay_ms(1+ 150 );
 if (play( 233 , 150 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 150 );
 if (play( 311 , 300 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 300 );
 if (play( 293 , 150 + 75 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 150 + 75 );
 if (play( 277 , 75 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 75 );

 if (play( 261 , 75 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 75 );
 if (play( 246 , 75 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 75 );
 if (play( 261 , 150 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 150 );
 Delay_ms(1+ 150 );
 if (play( 174 , 150 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 150 );
 if (play( 207 , 300 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 300 );
 if (play( 174 , 150 + 75 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 150 + 75 );
 if (play( 261 , 75 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 75 );

 if (play( 220 , 300 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 300 );
 if (play( 174 , 150 + 75 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 150 + 75 );
 if (play( 261 , 75 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 75 );
 if (play( 220 , 600 )== STOP_PLAYING)
 break;
 Delay_ms(1+ 600 );

 Delay_ms(2* 600 );
 }
}



int main(void)
{
cntr = 0;
OLED_Init();
OLED_DrawImage( BUZZ_bmp, 0, 0 );


GPIO_Digital_Output( &PTB_PDOR, _GPIO_PINMASK_23 );


UART4_Init_Advanced( 230400, _UART_8_BIT_DATA, _UART_NOPARITY, _UART_TWO_STOPBITS, &_GPIO_Module_UART4_PE24_25 );

EnableInterrupts();
NVIC_IntEnable( IVT_INT_UART4_RX_TX );

 *( (unsigned char*)(0x400EA003) )  |= 1 << 5;


 PTB_PCOR.B23 = 1 ;
Delay_ms( 10 );
 PTB_PSOR.B23 = 1 ;
Delay_ms( 200 );
 while ( 1 )
 {



 if ( touch_invalid != pressedTouch )
 {
 switch ( pressedTouch )
 {
 case touch_left:
 {
 playing = 1;
 play_melody();
 break;
 }
 }
 }
 }
}



void IRQ_Uart4Handler() iv IVT_INT_UART4_RX_TX ics ICS_AUTO
{

 volatile uint8_t foo = UART4_S1;
 uint8_t readData = UART4_D;
 *pktBuf = readData;

 PacketParser();
 if(cntr != 0)
 if ( touch_invalid != pressedTouch )
 {
 switch ( pressedTouch )
 {
 case touch_left:
 {
 if(playing)
 {
 STOPED = ~STOPED;
 if(cntr == 50)
 cntr = 1;
 }

 }
 }
 }
 cntr++;
}

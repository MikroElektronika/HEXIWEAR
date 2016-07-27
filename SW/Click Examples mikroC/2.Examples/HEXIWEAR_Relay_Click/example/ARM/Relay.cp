#line 1 "D:/Marko/tasks/freescale/svn/Hexiwear/MK64/5. Click Demos/1. mikroC/2. Primeri/HEXIWEAR_Relay_Click/example/ARM/Relay.c"
#line 1 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_relay_click/example/arm/oled_driver.h"
#line 1 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_relay_click/example/arm/oled_types.h"
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
#line 13 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_relay_click/example/arm/oled_types.h"
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
#line 41 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_relay_click/example/arm/oled_types.h"
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
#line 1 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_relay_click/example/arm/oled_resources.h"
#line 1 "d:/work/mikroc pro for arm/include/stdint.h"
#line 6 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_relay_click/example/arm/oled_resources.h"
extern const uint8_t guiFont_Tahoma_8_Regular[];

extern const code char relay_bmp[18438];
#line 12 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_relay_click/example/arm/oled_driver.h"
extern const uint8_t FO_HORIZONTAL;
extern const uint8_t FO_VERTICAL;
extern const uint8_t FO_VERTICAL_COLUMN;
#line 26 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_relay_click/example/arm/oled_driver.h"
oled_status_t OLED_Init(void);
#line 41 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_relay_click/example/arm/oled_driver.h"
oled_status_t OLED_DrawBox (
 uint16_t xCrd,
 uint16_t yCrd,
 uint16_t width,
 uint16_t height,
 uint16_t color
 );
#line 58 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_relay_click/example/arm/oled_driver.h"
oled_status_t OLED_FillScreen( uint16_t color );
#line 72 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_relay_click/example/arm/oled_driver.h"
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
#line 87 "D:/Marko/tasks/freescale/svn/Hexiwear/MK64/5. Click Demos/1. mikroC/2. Primeri/HEXIWEAR_Relay_Click/example/ARM/Relay.c"
typedef enum
{
 touch_left = 0,
 touch_right = 1,
 touch_invalid = 0xFF

} touch_type_t;
#line 100 "D:/Marko/tasks/freescale/svn/Hexiwear/MK64/5. Click Demos/1. mikroC/2. Primeri/HEXIWEAR_Relay_Click/example/ARM/Relay.c"
typedef enum
{
 packetType_pressUp = 0,
 packetType_pressDown = 1,
 packetType_pressLeft = 2,
 packetType_pressRight = 3,
 packetType_slide = 4,


 packetType_batteryLevel = 5,

 packetType_accel = 6,
 packetType_ambiLight = 7,
 packetType_pressure = 8,


 packetType_gyro = 9,
 packetType_temperature = 10,
 packetType_humidity = 11,
 packetType_magnet = 12,

 packetType_heartRate = 13,
 packetType_steps = 14,
 packetType_calories = 15,


 packetType_alertIn = 16,
 packetType_alertOut = 17,


 packetType_passDisplay = 18,


 packetType_otapKW40Started = 19,
 packetType_otapMK64Started = 20,
 packetType_otapCompleted = 21,
 packetType_otapFailed = 22,


 packetType_buttonsGroupToggleActive = 23,
 packetType_buttonsGroupGetActive = 24,
 packetType_buttonsGroupSendActive = 25,


 packetType_advModeGet = 26,
 packetType_advModeSend = 27,
 packetType_advModeToggle = 28,


 packetType_appMode = 29,


 packetType_linkStateGet = 30,
 packetType_linkStateSend = 31,


 packetType_notification = 32,


 packetType_buildVersion = 33,


 packetType_sleepON = 34,


 packetType_sleepOFF = 35,


 packetType_OK = 255

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
#line 195 "D:/Marko/tasks/freescale/svn/Hexiwear/MK64/5. Click Demos/1. mikroC/2. Primeri/HEXIWEAR_Relay_Click/example/ARM/Relay.c"
sbit relay1 at PTC_PDOR.B4;
sbit relay2 at PTA_PDOR.B10;
sbit KW40_RST at PTB_PDOR.B23;

static touch_type_t pressedTouch = touch_invalid;

static hostInterface_packet_t hostInterface_rxPacket;

uint8_t * pktBuf = ( uint8_t * ) &hostInterface_rxPacket;

static hostInterface_rxState_t hostInterface_rxState = hostInterface_rxState_idle;
#line 210 "D:/Marko/tasks/freescale/svn/Hexiwear/MK64/5. Click Demos/1. mikroC/2. Primeri/HEXIWEAR_Relay_Click/example/ARM/Relay.c"
static void PacketParser();
#line 218 "D:/Marko/tasks/freescale/svn/Hexiwear/MK64/5. Click Demos/1. mikroC/2. Primeri/HEXIWEAR_Relay_Click/example/ARM/Relay.c"
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
#line 331 "D:/Marko/tasks/freescale/svn/Hexiwear/MK64/5. Click Demos/1. mikroC/2. Primeri/HEXIWEAR_Relay_Click/example/ARM/Relay.c"
void IRQ_Uart4Handler() iv IVT_INT_UART4_RX_TX ics ICS_AUTO
{

 volatile uint8_t foo = UART4_S1;
 uint8_t readData = UART4_D;
 *pktBuf = readData;

 PacketParser();
}

void main() org 0x1000
{

 GPIO_Digital_Output( &PTA_PDOR, _GPIO_PINMASK_10 );

 GPIO_Digital_Output( &PTC_PDOR, _GPIO_PINMASK_4 );


 GPIO_Digital_Output( &PTB_PDOR, _GPIO_PINMASK_23 );

 OLED_Init();


 UART4_Init_Advanced( 230400, _UART_8_BIT_DATA, _UART_NOPARITY, _UART_TWO_STOPBITS, &_GPIO_Module_UART4_PE24_25 );

 EnableInterrupts();
 NVIC_IntEnable( IVT_INT_UART4_RX_TX );

  *( (unsigned char*)(0x400EA003) )  |= 1 << 5;


  PTB_PCOR.B23 = 1 ;
 Delay_ms( 10 );
  PTB_PSOR.B23 = 1 ;
 Delay_ms( 200 );


 relay1 = 0;
 relay2 = 0;

 OLED_DrawImage( &relay_bmp, 0, 0 );

 while ( 1 )
 {
 if ( touch_invalid != pressedTouch )
 {
 switch ( pressedTouch )
 {
 case touch_left:
 {
  PTC_PTOR.B4 = 1 ;
 break;
 }

 case touch_right:
 {
  PTA_PTOR.B10 = 1 ;
 break;
 }

 default:
 {}
 }
 pressedTouch = touch_invalid;
 }
 }
}

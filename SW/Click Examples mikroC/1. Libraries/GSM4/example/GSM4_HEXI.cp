#line 1 "//VBOXSVR/storage/git/ClickLab/GSM4/example/Hexiwear/GSM4_HEXI.c"
#line 1 "//vboxsvr/storage/git/clicklab/gsm4/example/hexiwear/oled/oled_driver.h"
#line 1 "//vboxsvr/storage/git/clicklab/gsm4/example/hexiwear/oled/oled_types.h"
#line 1 "c:/c4w/mikroc pro for arm/include/stdint.h"





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
#line 13 "//vboxsvr/storage/git/clicklab/gsm4/example/hexiwear/oled/oled_types.h"
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
#line 41 "//vboxsvr/storage/git/clicklab/gsm4/example/hexiwear/oled/oled_types.h"
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
#line 1 "//vboxsvr/storage/git/clicklab/gsm4/example/hexiwear/oled/oled_resources.h"
#line 1 "c:/c4w/mikroc pro for arm/include/stdint.h"
#line 6 "//vboxsvr/storage/git/clicklab/gsm4/example/hexiwear/oled/oled_resources.h"
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
#line 22 "//vboxsvr/storage/git/clicklab/gsm4/example/hexiwear/oled/oled_driver.h"
oled_status_t OLED_Init(void);
#line 37 "//vboxsvr/storage/git/clicklab/gsm4/example/hexiwear/oled/oled_driver.h"
oled_status_t OLED_DrawBox (
 uint16_t xCrd,
 uint16_t yCrd,
 uint16_t width,
 uint16_t height,
 uint16_t color
 );
#line 54 "//vboxsvr/storage/git/clicklab/gsm4/example/hexiwear/oled/oled_driver.h"
oled_status_t OLED_FillScreen( uint16_t color );
#line 68 "//vboxsvr/storage/git/clicklab/gsm4/example/hexiwear/oled/oled_driver.h"
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
#line 1 "//vboxsvr/storage/git/clicklab/gsm4/example/hexiwear/gsm4.h"
#line 1 "//vboxsvr/storage/git/clicklab/gsm4/library/include/at_engine.h"
#line 1 "//vboxsvr/storage/git/clicklab/gsm4/library/include/config.h"
#line 1 "c:/c4w/mikroc pro for arm/include/stdint.h"
#line 1 "c:/c4w/mikroc pro for arm/include/stddef.h"



typedef long ptrdiff_t;


 typedef unsigned long size_t;

typedef unsigned long wchar_t;
#line 1 "c:/c4w/mikroc pro for arm/include/string.h"





void * memchr(void *p, char n, unsigned int v);
int memcmp(void *s1, void *s2, int n);
void * memcpy(void * d1, void * s1, int n);
void * memmove(void * to, void * from, int n);
void * memset(void * p1, char character, int n);
char * strcat(char * to, char * from);
char * strchr(char * ptr, char chr);
int strcmp(char * s1, char * s2);
char * strcpy(char * to, char * from);
int strlen(char * s);
char * strncat(char * to, char * from, int size);
char * strncpy(char * to, char * from, int size);
int strspn(char * str1, char * str2);
char strcspn(char * s1, char * s2);
int strncmp(char * s1, char * s2, char len);
char * strpbrk(char * s1, char * s2);
char * strrchr(char *ptr, char chr);
char * strstr(char * s1, char * s2);
char * strtok(char * s1, char * s2);
#line 1 "c:/c4w/mikroc pro for arm/include/stdbool.h"



 typedef char _Bool;
#line 62 "//vboxsvr/storage/git/clicklab/gsm4/library/include/config.h"
typedef enum
{
 AT_OK,
 AT_ERROR,
 AT_UNKNOWN

}at_t;

typedef void ( *at_cmd_cb )( char *buffer );
#line 1 "//vboxsvr/storage/git/clicklab/gsm4/library/include/at_parser.h"
#line 1 "c:/c4w/mikroc pro for arm/include/stdbool.h"
#line 1 "//vboxsvr/storage/git/clicklab/gsm4/library/include/config.h"
#line 27 "//vboxsvr/storage/git/clicklab/gsm4/library/include/at_parser.h"
typedef enum
{
#line 31 "//vboxsvr/storage/git/clicklab/gsm4/library/include/at_parser.h"
 AT_CMD_UNKNOWN = 0,
#line 34 "//vboxsvr/storage/git/clicklab/gsm4/library/include/at_parser.h"
 AT_CMD_GET = 1,
#line 37 "//vboxsvr/storage/git/clicklab/gsm4/library/include/at_parser.h"
 AT_CMD_SET = 2,
#line 40 "//vboxsvr/storage/git/clicklab/gsm4/library/include/at_parser.h"
 AT_CMD_TEST = 3,
#line 43 "//vboxsvr/storage/git/clicklab/gsm4/library/include/at_parser.h"
 AT_CMD_EXEC = 4,

}at_type_t;
#line 55 "//vboxsvr/storage/git/clicklab/gsm4/library/include/at_parser.h"
typedef struct
{
#line 59 "//vboxsvr/storage/git/clicklab/gsm4/library/include/at_parser.h"
 uint32_t hash;
#line 62 "//vboxsvr/storage/git/clicklab/gsm4/library/include/at_parser.h"
 uint32_t timeout;
#line 65 "//vboxsvr/storage/git/clicklab/gsm4/library/include/at_parser.h"
 at_cmd_cb getter;
#line 68 "//vboxsvr/storage/git/clicklab/gsm4/library/include/at_parser.h"
 at_cmd_cb setter;
#line 71 "//vboxsvr/storage/git/clicklab/gsm4/library/include/at_parser.h"
 at_cmd_cb tester;
#line 74 "//vboxsvr/storage/git/clicklab/gsm4/library/include/at_parser.h"
 at_cmd_cb executer;

}at_cmd_t;
#line 91 "//vboxsvr/storage/git/clicklab/gsm4/library/include/at_parser.h"
void at_parser_init
(
 void
);
#line 109 "//vboxsvr/storage/git/clicklab/gsm4/library/include/at_parser.h"
void at_parser_store
(
 char *command,
 uint32_t timeout,
 at_cmd_cb getter,
 at_cmd_cb setter,
 at_cmd_cb tester,
 at_cmd_cb execute
);
#line 129 "//vboxsvr/storage/git/clicklab/gsm4/library/include/at_parser.h"
void at_parse
(
 char *input,
 at_cmd_cb *cb,
 uint32_t *timeout
);
#line 1 "//vboxsvr/storage/git/clicklab/gsm4/library/include/dev_timer.h"
#line 1 "//vboxsvr/storage/git/clicklab/gsm4/library/include/config.h"
#line 23 "//vboxsvr/storage/git/clicklab/gsm4/library/include/dev_timer.h"
extern volatile  _Bool  timeout_f;
#line 39 "//vboxsvr/storage/git/clicklab/gsm4/library/include/dev_timer.h"
void dev_timer_init
(
 void
);
#line 51 "//vboxsvr/storage/git/clicklab/gsm4/library/include/dev_timer.h"
void dev_tick_isr
(
 void
);
#line 62 "//vboxsvr/storage/git/clicklab/gsm4/library/include/dev_timer.h"
void dev_timer_start
(
 void
);
#line 73 "//vboxsvr/storage/git/clicklab/gsm4/library/include/dev_timer.h"
void dev_timer_restart
(
 void
);
#line 84 "//vboxsvr/storage/git/clicklab/gsm4/library/include/dev_timer.h"
void dev_timer_stop
(
 void
);
#line 97 "//vboxsvr/storage/git/clicklab/gsm4/library/include/dev_timer.h"
void dev_timer_load
(
 uint32_t timeout
);
#line 1 "//vboxsvr/storage/git/clicklab/gsm4/library/include/dev_adapter.h"
#line 1 "//vboxsvr/storage/git/clicklab/gsm4/library/include/config.h"
#line 1 "//vboxsvr/storage/git/clicklab/gsm4/library/include/dev_hal.h"
#line 1 "c:/c4w/mikroc pro for arm/include/stdint.h"
#line 1 "c:/c4w/mikroc pro for arm/include/stdbool.h"
#line 1 "c:/c4w/mikroc pro for arm/include/stddef.h"
#line 37 "//vboxsvr/storage/git/clicklab/gsm4/library/include/dev_hal.h"
void dev_hal_pwr_ctl
(
  _Bool  state
);
#line 50 "//vboxsvr/storage/git/clicklab/gsm4/library/include/dev_hal.h"
 _Bool  dev_hal_rts_ctl
(
 void
);
#line 63 "//vboxsvr/storage/git/clicklab/gsm4/library/include/dev_hal.h"
void dev_hal_cts_ctl
(
  _Bool  state
);
#line 74 "//vboxsvr/storage/git/clicklab/gsm4/library/include/dev_hal.h"
void dev_hal_init
(
 void
);
#line 87 "//vboxsvr/storage/git/clicklab/gsm4/library/include/dev_hal.h"
void dev_hal_write
(
 char ch
);
#line 24 "//vboxsvr/storage/git/clicklab/gsm4/library/include/dev_adapter.h"
extern volatile  _Bool  exception_f;
extern volatile  _Bool  response_f;
extern volatile  _Bool  cue_f;

extern volatile char tx_buffer[  1024  ];
extern volatile char rx_buffer[  1024  ];
#line 42 "//vboxsvr/storage/git/clicklab/gsm4/library/include/dev_adapter.h"
void dev_adapter_init
(
 void
);
#line 50 "//vboxsvr/storage/git/clicklab/gsm4/library/include/dev_adapter.h"
void dev_adapter_reset
(
 void
);
#line 60 "//vboxsvr/storage/git/clicklab/gsm4/library/include/dev_adapter.h"
int dev_tx
(
 char tx_input
);
#line 72 "//vboxsvr/storage/git/clicklab/gsm4/library/include/dev_adapter.h"
void dev_rx
(
 char rx_input
);
#line 36 "//vboxsvr/storage/git/clicklab/gsm4/library/include/at_engine.h"
void engine_init( at_cmd_cb default_callback );
#line 46 "//vboxsvr/storage/git/clicklab/gsm4/library/include/at_engine.h"
void at_cmd( char *input );
#line 57 "//vboxsvr/storage/git/clicklab/gsm4/library/include/at_engine.h"
void at_cmd_addition( char *input );
#line 73 "//vboxsvr/storage/git/clicklab/gsm4/library/include/at_engine.h"
void at_cmd_save
(
 char *cmd,
 uint32_t timeout,
 at_cmd_cb getter,
 at_cmd_cb setter,
 at_cmd_cb tester,
 at_cmd_cb executer
);
#line 88 "//vboxsvr/storage/git/clicklab/gsm4/library/include/at_engine.h"
void at_process( void );
#line 35 "//vboxsvr/storage/git/clicklab/gsm4/example/hexiwear/gsm4.h"
void gsm4_init( void );
#line 40 "//vboxsvr/storage/git/clicklab/gsm4/example/hexiwear/gsm4.h"
void gsm4_evn_default( char *response );

void gsm4_ev_ring( char *response );

void gsm4_evn_call_id( char *response );
#line 50 "//vboxsvr/storage/git/clicklab/gsm4/example/hexiwear/gsm4.h"
void gsm_act_read_info( void );

void gsm_act_send_info( void );

void gps_act_pwr_control(  _Bool  state );
#line 4 "//VBOXSVR/storage/git/ClickLab/GSM4/example/Hexiwear/GSM4_HEXI.c"
sbit GSM_PWR at PTB_PDOR.B11;
sbit GSM_CTS at PTB_PDIR.B13;
sbit GSM_RTS at PTC_PDOR.B4;
sbit GSM_RING at PTA_PDIR.B10;
sbit GSM_STAT at PTB_PDIR.B2;

sbit LED3 at PTA_PDOR.B14;

 _Bool  ring_f;

void system_init()
{
 GPIO_Digital_Output( &PTA_PDOR, _GPIO_PINMASK_14 );
 GPIO_Digital_Output( &PTB_PDOR, _GPIO_PINMASK_11 );
 GPIO_Digital_Output( &PTC_PDOR, _GPIO_PINMASK_4 );
 GPIO_Digital_Input( &PTB_PDIR, _GPIO_PINMASK_13 );
 GPIO_Digital_Input( &PTA_PDIR, _GPIO_PINMASK_10 );
 GPIO_Digital_Input( &PTB_PDIR, _GPIO_PINMASK_2 );

 UART3_Init_Advanced( 115200, _UART_8_BIT_DATA, _UART_NOPARITY,
 _UART_ONE_STOPBIT, &_GPIO_Module_UART3_PC16_17 );

 UART2_Init_Advanced( 9600, _UART_8_BIT_DATA, _UART_NOPARITY,
 _UART_ONE_STOPBIT, &_GPIO_Module_UART2_PD3_2 );

 EnableInterrupts();
 NVIC_IntEnable( IVT_INT_UART2_RX_TX );
 UART2_C2 |= 1 << 5;

 Delay_ms( 500 );
 UART3_Write_Text( "INITIALIZED\r\n" );
}

void main() {

 system_init();
 gsm4_init();

 LED3 = 1;

 while( 1 ) {

 at_process();

 if( ring_f ) {

 LED3 = ~LED3;
 ring_f =  0 ;
 }
 }
}

void UART_RX_ISR() iv IVT_INT_UART2_RX_TX ics ICS_AUTO
{
 char foo = UART2_S1;
 char tmp = UART2_D;

 if( foo & ( 1 << 5 ) )
 dev_rx( tmp );
}

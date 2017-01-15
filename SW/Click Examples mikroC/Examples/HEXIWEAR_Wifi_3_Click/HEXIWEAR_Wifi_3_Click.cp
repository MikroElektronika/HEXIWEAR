#line 1 "E:/Darko/Projekti/HEXIWEAR/Click Demo/Projekti/HEXIWEAR_Wifi_3_Click/HEXIWEAR_Wifi_3_Click.c"
#line 1 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_wifi_3_click/oled_driver.h"
#line 1 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_wifi_3_click/oled_types.h"
#line 1 "c:/users/public/documents/mikroelektronika/arm/radni/mikroc pro for arm/include/stdint.h"





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
#line 13 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_wifi_3_click/oled_types.h"
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
#line 41 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_wifi_3_click/oled_types.h"
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
#line 1 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_wifi_3_click/oled_resources.h"
#line 1 "c:/users/public/documents/mikroelektronika/arm/radni/mikroc pro for arm/include/stdint.h"
#line 6 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_wifi_3_click/oled_resources.h"
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
extern const uint8_t WiFi_bmp[18438];
#line 22 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_wifi_3_click/oled_driver.h"
oled_status_t OLED_Init(void);
#line 37 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_wifi_3_click/oled_driver.h"
oled_status_t OLED_DrawBox (
 uint16_t xCrd,
 uint16_t yCrd,
 uint16_t width,
 uint16_t height,
 uint16_t color
 );
#line 54 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_wifi_3_click/oled_driver.h"
oled_status_t OLED_FillScreen( uint16_t color );
#line 68 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_wifi_3_click/oled_driver.h"
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
#line 58 "E:/Darko/Projekti/HEXIWEAR/Click Demo/Projekti/HEXIWEAR_Wifi_3_Click/HEXIWEAR_Wifi_3_Click.c"
sbit CH_PD at PTB_PDOR.B3;
sbit GPIO15 at PTB_PDIR.B19;

sbit REL1 at PTA_PDOR.B11;
sbit REL2 at PTC_PTOR.B3;

extern void WiFI_Configure();


const OK = 1;
const ERROR = 2;
const NO_CHANGE = 3;
const FAIL = 4;
const READY = 5;
const PRESSED = 6;
const CONNECTED = 7;

char received_data[450], ip_address[16];
unsigned short i, tmp, DataReady;

char state;
char response_rcvd;
char responseID, response = 0;


unsigned char *SSID = "HEXIWEAR_WiFi_3";
unsigned char *password = "123456";
unsigned char *port = "4040";







char data_ready = 0;
char rx_buff[1000];
unsigned int data_len = 0;


void IRQ_UartHandler() iv IVT_INT_UART2_RX_TX ics ICS_AUTO
{
 volatile uint8_t foo = UART2_S1;
 uint8_t readData = UART2_D;

 tmp = readData;
 switch(tmp) {
 case  0x0A :
 if(data_len > 1){
 data_ready = 1;
 }
 break;
 case  0x0D :
 rx_buff[data_len] = 0;
 break;
 default:
 rx_buff[data_len] = tmp;
 data_len++;
 }

}


void reset_buff() {
 memset(rx_buff,0,data_len);
 data_ready = 0;
 data_len=0;
}

void UART_Write_AT(char *CMD) {
 UART_Write_Text(CMD);
 UART_Write(0x0D);
 UART_Write(0x0A);
}

char response_success() {
 char result;
 while(!data_ready);
 if((strstr(rx_buff,"OK")) || (strstr(rx_buff,"no change")) || (strstr(rx_buff,"ready"))) {
 result = 1;
 }else result = 0;
 reset_buff();
 return result;
}

void Get_IP() {
 char response_cnt, conn_flg;

 UART_Write_AT("AT+CIFSR");
 while(!data_ready);
 reset_buff();
 while(!data_ready);
 reset_buff();
}


void WiFi3_Init() {
 GPIO_Digital_Output(&PTB_PDOR, _GPIO_PINMASK_3);
 GPIO_Digital_Output(&PTB_PDOR, _GPIO_PINMASK_19);

 GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_3);
 GPIO_Digital_Output(&PTA_PDOR, _GPIO_PINMASK_11);

 REL1 = 0;
 REL2 = 0;

 CH_PD = 1;
 GPIO15 = 0;
 Delay_ms(1000);
}

void WiFI_Configure() {

 OLED_WriteText("Resetting module", 5, 80 );

 UART_Write_AT("AT+RST");
 while(!response_success());
 delay_ms(1000);

 UART_Write_AT("AT+CWMODE=1");
 while(!response_success());
 delay_ms(1000);


 OLED_DrawBox( 0, 80, 96, 16, OLED_COLOR_BLACK );
 OLED_WriteText("Set connection", 15, 80 );

 UART_Write_AT("AT+CIPMUX=1");
 while(!response_success());
 delay_ms(1000);

 UART_Write_AT("AT+CWMODE=2");
 while(!response_success());
 delay_ms(1000);



 OLED_DrawBox( 0, 80, 96, 16, OLED_COLOR_BLACK );
 OLED_WriteText("Making SoftAP", 12, 80 );


 UART_Write_Text("AT+CWSAP=");
 UART_Write('"');
 UART_Write_Text(SSID);
 UART_Write('"');
 UART_Write(',');
 UART_Write('"');
 UART_Write_Text(password);
 UART_Write('"');
 UART_Write(',');
 UART_Write('5');
 UART_Write(',');
 UART_Write('0');
 UART_Write(0x0D);
 UART_Write(0x0A);
 while(!response_success());
 delay_ms(1000);

 UART_Write_Text("AT+CIPAP=");
 UART_Write('"');
 UART_Write_Text("192.168.0.1");
 UART_Write('"');
 UART_Write(0x0D);
 UART_Write(0x0A);

 while(!response_success());
 delay_ms(1000);

 OLED_DrawBox( 0, 80, 96, 16, OLED_COLOR_BLACK );
 OLED_WriteText("Set server/port", 10, 80 );
 UART_Write_Text("AT+CIPSERVER=1");
 UART_Write(',');
 UART_Write_Text(port);
 UART_Write(0x0D);
 UART_Write(0x0A);
 while(!response_success());
 Delay_ms(1000);

 OLED_DrawBox( 0, 80, 96, 16, OLED_COLOR_BLACK );
 OLED_WriteText("Listen...", 30, 80 );

 UART_Write_AT("AT+CIPSTO=30");
 while(!response_success());
 delay_ms(1000);

}

oled_text_properties_t
 textProperties;

void main() {

 state = 0;
 response_rcvd = 0;
 responseID = 0;
 response = 0;
 tmp = 0;
 i = 0;
 OLED_Init();

 OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_WHITE, 0 );

 OLED_DrawImage( WiFi_bmp, 0, 0 );

 UART2_init_Advanced( 115000, _UART_8_BIT_DATA, _UART_NOPARITY, _UART_ONE_STOPBIT, &_GPIO_Module_UART2_PD3_2);
 UART_Write_Text("Start");
 UART_Write(0x0D);
 UART_Write(0x0A);

 EnableInterrupts();
 NVIC_IntEnable( IVT_INT_UART2_RX_TX );
 UART2_C2 |= 1 << 5;


 WiFi3_Init();

 WiFI_Configure();

 while (1)
 {
 while(!data_ready);

 if(memcmp("+IPD", &rx_buff[0], 4) == 0)
 {
 if(strcmp("R1", &rx_buff[9]) == 0)
 {
 REL1 = ~REL1;
 }
 else if(strcmp("R2", &rx_buff[9]) == 0)
 {
 REL2 = ~REL2;
 }
 }

 reset_buff();
 }
}

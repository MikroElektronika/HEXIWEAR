#line 1 "E:/Darko/Projekti/HEXIWEAR/Click Demo/Projekti/HEXIWEAR_NFC_Click/example/ARM/HEXIWEAR_NFC_Click.c"
#line 1 "c:/users/public/documents/mikroelektronika/arm/radni/mikroc pro for arm/include/stdio.h"
#line 1 "c:/users/public/documents/mikroelektronika/arm/radni/mikroc pro for arm/include/string.h"





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
#line 1 "c:/users/public/documents/mikroelektronika/arm/radni/mikroc pro for arm/include/stdbool.h"



 typedef char _Bool;
#line 1 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_nfc_click/example/arm/nfc.h"
#line 1 "c:/users/public/documents/mikroelektronika/arm/radni/mikroc pro for arm/include/stdint.h"
#line 84 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_nfc_click/example/arm/nfc.h"
typedef struct
{
 uint8_t interface;
 uint8_t protocol;
 uint8_t mode_tech;
} nfc_interface_t;

typedef enum
{
 NFC_MODE_NONE = 0,
 NFC_MODE_CARDEMU = 0x01,
 NFC_MODE_P2P = 0x02,
 NFC_MODE_RW = 0x04
} nfc_mode_t;
#line 120 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_nfc_click/example/arm/nfc.h"
int nfc_init( uint8_t slave_address );

void nfc_rx_ready( void );

void nfc_timer_tick( void );
#line 132 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_nfc_click/example/arm/nfc.h"
int nfc_configure( nfc_mode_t mode );
#line 141 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_nfc_click/example/arm/nfc.h"
int nfc_start_discovery( uint8_t *p_tech_tab, uint8_t tech_tab_size );
#line 148 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_nfc_click/example/arm/nfc.h"
void nfc_wait_for_discovery_notification( nfc_interface_t *p_rf_intf );
#line 156 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_nfc_click/example/arm/nfc.h"
void nfc_process( uint8_t mode, nfc_interface_t *rf_intf );
#line 163 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_nfc_click/example/arm/nfc.h"
int nfc_restart_discovery( void );
#line 170 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_nfc_click/example/arm/nfc.h"
int nfc_stop_discovery( void );
#line 182 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_nfc_click/example/arm/nfc.h"
int nfc_reader_tag_cmd( uint8_t *command, uint8_t command_size,
 uint8_t *answer, uint8_t *answer_size );
#line 1 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_nfc_click/example/arm/oled_driver.h"
#line 1 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_nfc_click/example/arm/oled_types.h"
#line 1 "c:/users/public/documents/mikroelektronika/arm/radni/mikroc pro for arm/include/stdint.h"
#line 13 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_nfc_click/example/arm/oled_types.h"
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
#line 41 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_nfc_click/example/arm/oled_types.h"
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
#line 1 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_nfc_click/example/arm/oled_resources.h"
#line 1 "c:/users/public/documents/mikroelektronika/arm/radni/mikroc pro for arm/include/stdint.h"
#line 6 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_nfc_click/example/arm/oled_resources.h"
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
#line 22 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_nfc_click/example/arm/oled_driver.h"
oled_status_t OLED_Init(void);
#line 37 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_nfc_click/example/arm/oled_driver.h"
oled_status_t OLED_DrawBox (
 uint16_t xCrd,
 uint16_t yCrd,
 uint16_t width,
 uint16_t height,
 uint16_t color
 );
#line 54 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_nfc_click/example/arm/oled_driver.h"
oled_status_t OLED_FillScreen( uint16_t color );
#line 68 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_nfc_click/example/arm/oled_driver.h"
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
#line 1 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_nfc_click/example/arm/resources.h"

extern const char NFC_bmp[];
#line 1 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_nfc_click/example/arm/p2p_ndef.h"
#line 1 "c:/users/public/documents/mikroelektronika/arm/radni/mikroc pro for arm/include/stdint.h"
#line 1 "c:/users/public/documents/mikroelektronika/arm/radni/mikroc pro for arm/include/stdbool.h"
#line 72 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_nfc_click/example/arm/p2p_ndef.h"
void p2p_ndef_reset( void );
void p2p_ndef_next( uint8_t *p_cmd, uint16_t cmd_size,
 uint8_t *rsp, uint16_t *p_rsp_size );
 _Bool  p2p_ndef_set_record( uint8_t *p_record, uint16_t record_size,
 void *cb );
void p2p_ndef_register_pull_callback( void *p_cb );
#line 1 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_nfc_click/example/arm/rw_ndef.h"
#line 1 "c:/users/public/documents/mikroelektronika/arm/radni/mikroc pro for arm/include/stdint.h"
#line 60 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_nfc_click/example/arm/rw_ndef.h"
typedef void rw_ndef_callback_t( uint8_t *, uint16_t );
#line 65 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_nfc_click/example/arm/rw_ndef.h"
extern uint8_t ndef_buffer[ 240 ];
extern rw_ndef_callback_t *p_rw_ndef_pull_cb;
#line 79 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_nfc_click/example/arm/rw_ndef.h"
void rw_ndef_register_pull_callback( void *p_cb );
#line 85 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_nfc_click/example/arm/rw_ndef.h"
void rw_ndef_reset( uint8_t type );
#line 94 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_nfc_click/example/arm/rw_ndef.h"
void rw_ndef_read_next( uint8_t *p_cmd, uint16_t cmd_size,
 uint8_t *rsp, uint16_t *p_rsp_size );
#line 67 "E:/Darko/Projekti/HEXIWEAR/Click Demo/Projekti/HEXIWEAR_NFC_Click/example/ARM/HEXIWEAR_NFC_Click.c"
sbit NFC_RST_PIN at PTB_PDOR.B11;
sbit NFC_INT_PIN at PTB_PDIR.B13;



const char NDEF_RECORD[] = { 0xD1,
 0x01,
 0x07,
 'T',
 0x02,
 'e', 'n',
 'T', 'e', 's', 't'
 };


uint8_t discovery_technologies[] = {  0x00  |  0 
 ,  0x00  |  1 
 ,  0x00  |  2 

 ,  0x00  |  5 

 ,  0x80  |  0 

 ,  0x80  |  2 
 ,  0x80  |  3 
 ,  0x80  |  5 

 };

 _Bool  volatile incoming_flag;
#line 102 "E:/Darko/Projekti/HEXIWEAR/Click Demo/Projekti/HEXIWEAR_NFC_Click/example/ARM/HEXIWEAR_NFC_Click.c"
char *auth( uint8_t x );
char *encrypt( uint8_t x );
void ndef_pull_cb( uint8_t *p_ndef_record, uint16_t ndef_record_size );


void ndef_push_cb( uint8_t *p_ndef_record, uint16_t ndef_record_size );

void mi_fare_scenario( void );
void init_timer2( void );
int system_init( void );
void process_radio( nfc_interface_t *radio );
#line 118 "E:/Darko/Projekti/HEXIWEAR/Click Demo/Projekti/HEXIWEAR_NFC_Click/example/ARM/HEXIWEAR_NFC_Click.c"
char *auth( uint8_t x )
{
 switch( x )
 {
 case 0x01:
 return "Open";
 case 0x02:
 return "WPA-Personal";
 case 0x04:
 return "Shared";
 case 0x08:
 return "WPA-Entreprise";
 case 0x10:
 return "WPA2-Entreprise";
 case 0x20:
 return "WPA2-Personal";
 default:
 return "unknown";
 }
}

char *encrypt( uint8_t x )
{
 switch( x )
 {
 case 0x01:
 return "None";
 case 0x02:
 return "WEP";
 case 0x04:
 return "TKIP";
 case 0x08:
 return "AES";
 case 0x10:
 return "AES/TKIP";
 default:
 return "unknown";
 }
}

volatile uint8_t index;

void ndef_pull_cb( uint8_t *p_ndef_record, uint16_t ndef_record_size )
{

 char tmp_txt[80];



 if( p_ndef_record[0] == 0xD1 )
 {
 switch( p_ndef_record[3] )
 {
 case 'T':
 p_ndef_record[7 + p_ndef_record[2]] = '\0';
 sprinti( tmp_txt,
 "   Text record (language = %c%c): %s\n",
 p_ndef_record[5],
 p_ndef_record[6],
 &p_ndef_record[7] );


 OLED_SetFont(guiFont_Tahoma_8_Regular, 0x7BCF, 0);
 OLED_WriteText("Text record:", 4, 55);
 OLED_SetFont(guiFont_Tahoma_8_Regular, 0xffff, 0);
 OLED_WriteText(&p_ndef_record[7], 4, 70);

 break;

 case 'U':

  { switch(p_ndef_record[4]) { case 1: break; case 2: break; case 3: break; case 4: break; case 5: break; case 6: break; default: break; } } 
 p_ndef_record[4 + p_ndef_record[2]] = '\0';
 sprinti( tmp_txt, "%s\n", &p_ndef_record[5] );


 OLED_SetFont(guiFont_Tahoma_8_Regular, 0x7BCF, 0);
 OLED_WriteText("URI record:", 4, 55);
 OLED_SetFont(guiFont_Tahoma_8_Regular, 0xffff, 0);
 OLED_WriteText(tmp_txt, 4, 70);

 break;

 default:
 OLED_SetFont(guiFont_Tahoma_8_Regular, 0x7BCF, 0);
 OLED_WriteText("Unsupported", 4, 55);

 break;
 }
 }
#line 268 "E:/Darko/Projekti/HEXIWEAR/Click Demo/Projekti/HEXIWEAR_NFC_Click/example/ARM/HEXIWEAR_NFC_Click.c"
 else
 ;



}



void ndef_push_cb( uint8_t *p_ndef_record, uint16_t ndef_record_size )
{
 ;
}



void mi_fare_scenario()
{
  _Bool  status;
 uint8_t i;
 uint8_t resp[256];
 uint8_t resp_size;

 uint8_t auth[] = {0x40, 0x01, 0x10, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

 uint8_t read[] = {0x10, 0x30, 0x04};

 uint8_t write_part1[] = {0x10, 0xA0, 0x04};
 uint8_t write_part2[] =
 {
 0x10, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99,
 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff
 };
 char tmp_txt[80];


 status = nfc_reader_tag_cmd( auth, sizeof( auth ), resp, &resp_size );

 if( ( status == 1 ) || ( resp[resp_size - 1] != 0 ) )
 {
 sprinti( tmp_txt, " Authenticate sector %d failed with error 0x%02x\n",
 auth[1], resp[resp_size - 1] );

 return;
 }
 sprinti( tmp_txt, " Authenticate sector %d succeed\n", auth[1] );



 status = nfc_reader_tag_cmd( read, sizeof( read ), resp, &resp_size );

 if( ( status == 1 ) || ( resp[resp_size - 1] != 0 ) )
 {
 sprinti( tmp_txt, " Read block %d failed with error 0x%02x\n",
 read[2], resp[resp_size - 1] );

 return;
 }

 sprinti( tmp_txt, " Read block %d: ", read[2] );


 for( i = 0; i < resp_size - 2; i++ )
 {
 sprinti( tmp_txt, "0x%02X ", resp[i + 1] );

 }



 status = nfc_reader_tag_cmd( write_part1, sizeof( write_part1 ), resp,
 &resp_size );

 if( ( status == 1 ) || ( resp[resp_size - 1] != 0 ) )
 {
 sprinti( tmp_txt, " Write block %d failed with error 0x%02x\n",
 write_part1[2], resp[resp_size - 1] );

 return;
 }
 status = nfc_reader_tag_cmd( write_part2, sizeof( write_part2 ), resp,
 &resp_size );

 if( ( status == 1 ) || ( resp[resp_size - 1] != 0 ) )
 {
 sprinti( tmp_txt, " Write block %d failed with error 0x%02x\n",
 write_part1[2],
 resp[resp_size - 1] );

 return;
 }

 sprinti( tmp_txt, " Block %d written\n", write_part1[2] );


 status = nfc_reader_tag_cmd( read, sizeof( read ), resp, &resp_size );

 if( ( status == 1 ) || ( resp[resp_size - 1] != 0 ) )
 {
 sprinti( tmp_txt, " Read failed with error 0x%02x\n", resp[resp_size - 1] );

 return;
 }

 sprinti( tmp_txt, " Read block %d: ", read[2] );


 for( i = 0; i < resp_size - 2; i++ )
 {
 sprinti( tmp_txt, "0x%02X ", resp[i + 1] );

 }



 while( 1 )
 {
 Delay_ms( 500 );
 status = nfc_reader_tag_cmd( read, sizeof( read ), resp, &resp_size );

 if( ( status == 1 ) || ( resp[resp_size - 1] == 0xb2 ) )
 break;
 }
}

void init_ExtPinInt()
{
 GPIO_Digital_Input(&PTB_PDOR, _GPIO_PINMASK_13);
 NVIC_IntEnable( IVT_INT_PORTB );

 PORTB_PCR13 &= 0xFFF0FFFF;
 PORTB_PCR13 |= (((unsigned long)0x9) << 16);
}


void init_timer2()
{

 LPTMR_bit = 1;


 LPTMR0_PSR = 0XD;


 LPTMR0_CSR = 0X40;


 TIE_LPTMR0_CSR_bit = 1;
 NVIC_IntEnable( IVT_INT_LPTimer );


 LPTMR0_CMR = 10;


 TEN_LPTMR0_CSR_bit = 1;

}

int system_init()
{
 uint8_t mode = 0;

 OLED_Init();
 OLED_DrawImage(NFC_bmp, 0, 0);

 GPIO_Digital_Output(&PTB_PDOR, _GPIO_PINMASK_11);

 GPIO_Digital_Output(&PTA_PDOR, _GPIO_PINMASK_11);




 Delay_ms( 100 );



 OLED_SetFont(guiFont_Tahoma_8_Regular, 0xffff, 0);
 OLED_DrawBox(0, 80, 96, 15, 0);
 OLED_WriteText("Start Test Loop", 4, 80);

 I2C0_Init_Advanced( 100000, &_GPIO_Module_I2C0_PD8_9 );

 Delay_ms( 100 );







 init_ExtPinInt();
 init_timer2();
 EnableInterrupts();
#line 470 "E:/Darko/Projekti/HEXIWEAR/Click Demo/Projekti/HEXIWEAR_NFC_Click/example/ARM/HEXIWEAR_NFC_Click.c"
 p2p_ndef_set_record( ( uint8_t * )NDEF_RECORD, sizeof( NDEF_RECORD ),
 ( void * )ndef_push_cb );


 p2p_ndef_register_pull_callback( ( void * )ndef_pull_cb );




 rw_ndef_register_pull_callback( ( void * )ndef_pull_cb );
#line 486 "E:/Darko/Projekti/HEXIWEAR/Click Demo/Projekti/HEXIWEAR_NFC_Click/example/ARM/HEXIWEAR_NFC_Click.c"
 mode |= NFC_MODE_P2P;


 mode |= NFC_MODE_RW;



 if( nfc_init(  0x28  ) )
 {

 OLED_DrawBox(0, 80, 96, 15, 0);
 OLED_WriteText("Error!", 4, 80);
 return -1;
 }
 else if( nfc_configure( mode ) )
 {

 OLED_DrawBox(0, 80, 96, 15, 0);
 OLED_WriteText("Error!", 4, 80);
 return -1;
 }
 else if( nfc_start_discovery( discovery_technologies, sizeof( discovery_technologies ) ) ) {

 OLED_DrawBox(0, 80, 96, 15, 0);
 OLED_WriteText("Error!", 4, 80);
 return -1;
 }


 OLED_DrawBox(0, 80, 96, 15, 0);
 OLED_WriteText("Success!", 4, 80);
 incoming_flag =  0 ;
 return 0;
}

void process_radio( nfc_interface_t *radio )
{
 char tmp_txt[80];
#line 535 "E:/Darko/Projekti/HEXIWEAR/Click Demo/Projekti/HEXIWEAR_NFC_Click/example/ARM/HEXIWEAR_NFC_Click.c"
 if( radio->interface ==  0x3  )
 {

 if( ( radio->mode_tech &  0x80  ) ==  0x80  )
 ;
 else
 ;

 nfc_process( NFC_MODE_P2P, radio );

 }
 else


 if( ( radio->mode_tech &  0xF0  ) ==  0x00  )
 {

 if( radio->protocol ==  0x80  )
 {
#line 567 "E:/Darko/Projekti/HEXIWEAR/Click Demo/Projekti/HEXIWEAR_NFC_Click/example/ARM/HEXIWEAR_NFC_Click.c"
 OLED_DrawBox(0, 80, 96, 15, 0);
 OLED_WriteText("MIFARE card", 4, 80);

 nfc_restart_discovery();
 Delay_ms(1000);
 }

 else if( ( radio->protocol !=  0x5  )
 && ( radio->interface !=  0x0  ) )
 {
 sprinti( tmp_txt, " - POLL MODE: Remote T%dT activated\r\n", radio->protocol );


 sprinti( tmp_txt, "Type %d Tag", radio->protocol );

 OLED_DrawBox(0, 0, 96, 96, 0);
 OLED_SetFont(guiFont_Tahoma_8_Regular, 0x7BCF, 0);
 OLED_DrawBox(0, 80, 96, 15, 0);
 OLED_WriteText("Detected:", 4, 10);
 OLED_SetFont(guiFont_Tahoma_8_Regular, 0xffff, 0);
 OLED_DrawBox(0, 80, 96, 15, 0);
 OLED_DrawBox(0, 80, 96, 15, 0);
 OLED_WriteText(tmp_txt, 4, 25);

 nfc_process( NFC_MODE_RW, radio );

 }
 else
 {










 OLED_DrawBox(0, 80, 96, 15, 0);
 OLED_WriteText("Unknown dev", 4, 80);


 nfc_stop_discovery();
 nfc_start_discovery( discovery_technologies, sizeof( discovery_technologies ) );
 Delay_ms(1000);
 }


 OLED_DrawImage(NFC_bmp, 0, 0);
 OLED_DrawBox(0, 80, 96, 15, 0);
 OLED_WriteText("Wait for device", 4, 80);
 }
 else

 {

 }

}

void main()
{
 nfc_interface_t r_interface;

 if( system_init() )
 while( 1 );


 OLED_DrawBox(0, 80, 96, 15, 0);
 OLED_WriteText("Wait for device", 4, 80);

 while( 1 )
 {

 if( incoming_flag )
 {

 nfc_wait_for_discovery_notification( &r_interface );
 process_radio( &r_interface );
 incoming_flag =  0 ;
 }

 }
}


void card_rx_ISR() iv IVT_INT_PORTB ics ICS_AUTO
{
 PORTB_ISFR = 0xFFFFFFFF;
 nfc_rx_ready();
 incoming_flag =  1 ;
}


void timer2_interrupt() iv IVT_INT_LPTimer
{
 LPTMR0_CSR |= 0x80;
 PTA_PDOR.B11 = ~PTA_PDOR.B11;
 asm nop;
 nfc_timer_tick();
}

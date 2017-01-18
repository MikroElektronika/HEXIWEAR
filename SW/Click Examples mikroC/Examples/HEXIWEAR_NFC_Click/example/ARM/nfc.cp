#line 1 "//VBOXSVR/storage/git/MikroE/HEXIWEAR/SW/Click Examples mikroC/2.Examples/HEXIWEAR_NFC_Click/example/ARM/nfc.c"
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
#line 1 "c:/c4w/mikroc pro for arm/include/stdio.h"
#line 1 "c:/c4w/mikroc pro for arm/include/stdbool.h"



 typedef char _Bool;
#line 1 "//vboxsvr/storage/git/mikroe/hexiwear/sw/click examples mikroc/2.examples/hexiwear_nfc_click/example/arm/nfc.h"
#line 1 "c:/c4w/mikroc pro for arm/include/stdint.h"
#line 84 "//vboxsvr/storage/git/mikroe/hexiwear/sw/click examples mikroc/2.examples/hexiwear_nfc_click/example/arm/nfc.h"
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
#line 120 "//vboxsvr/storage/git/mikroe/hexiwear/sw/click examples mikroc/2.examples/hexiwear_nfc_click/example/arm/nfc.h"
int nfc_init( uint8_t slave_address );

void nfc_rx_ready( void );

void nfc_timer_tick( void );
#line 132 "//vboxsvr/storage/git/mikroe/hexiwear/sw/click examples mikroc/2.examples/hexiwear_nfc_click/example/arm/nfc.h"
int nfc_configure( nfc_mode_t mode );
#line 141 "//vboxsvr/storage/git/mikroe/hexiwear/sw/click examples mikroc/2.examples/hexiwear_nfc_click/example/arm/nfc.h"
int nfc_start_discovery( uint8_t *p_tech_tab, uint8_t tech_tab_size );
#line 148 "//vboxsvr/storage/git/mikroe/hexiwear/sw/click examples mikroc/2.examples/hexiwear_nfc_click/example/arm/nfc.h"
void nfc_wait_for_discovery_notification( nfc_interface_t *p_rf_intf );
#line 156 "//vboxsvr/storage/git/mikroe/hexiwear/sw/click examples mikroc/2.examples/hexiwear_nfc_click/example/arm/nfc.h"
void nfc_process( uint8_t mode, nfc_interface_t *rf_intf );
#line 163 "//vboxsvr/storage/git/mikroe/hexiwear/sw/click examples mikroc/2.examples/hexiwear_nfc_click/example/arm/nfc.h"
int nfc_restart_discovery( void );
#line 170 "//vboxsvr/storage/git/mikroe/hexiwear/sw/click examples mikroc/2.examples/hexiwear_nfc_click/example/arm/nfc.h"
int nfc_stop_discovery( void );
#line 182 "//vboxsvr/storage/git/mikroe/hexiwear/sw/click examples mikroc/2.examples/hexiwear_nfc_click/example/arm/nfc.h"
int nfc_reader_tag_cmd( uint8_t *command, uint8_t command_size,
 uint8_t *answer, uint8_t *answer_size );
#line 1 "//vboxsvr/storage/git/mikroe/hexiwear/sw/click examples mikroc/2.examples/hexiwear_nfc_click/example/arm/nfc_hal.h"
#line 1 "c:/c4w/mikroc pro for arm/include/stdint.h"
#line 69 "//vboxsvr/storage/git/mikroe/hexiwear/sw/click examples mikroc/2.examples/hexiwear_nfc_click/example/arm/nfc_hal.h"
void nfc_hal_init( uint8_t address_id );

void nfc_hal_delay( uint16_t ms );

void nfc_hal_reset( void );

int nfc_hal_write( uint8_t *data_out, uint16_t count );

int nfc_hal_read( uint8_t *data_in, uint16_t *nbytes_read,
 uint16_t count );
#line 1 "//vboxsvr/storage/git/mikroe/hexiwear/sw/click examples mikroc/2.examples/hexiwear_nfc_click/example/arm/oled_driver.h"
#line 1 "//vboxsvr/storage/git/mikroe/hexiwear/sw/click examples mikroc/2.examples/hexiwear_nfc_click/example/arm/oled_types.h"
#line 1 "c:/c4w/mikroc pro for arm/include/stdint.h"
#line 13 "//vboxsvr/storage/git/mikroe/hexiwear/sw/click examples mikroc/2.examples/hexiwear_nfc_click/example/arm/oled_types.h"
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
#line 41 "//vboxsvr/storage/git/mikroe/hexiwear/sw/click examples mikroc/2.examples/hexiwear_nfc_click/example/arm/oled_types.h"
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
#line 1 "//vboxsvr/storage/git/mikroe/hexiwear/sw/click examples mikroc/2.examples/hexiwear_nfc_click/example/arm/oled_resources.h"
#line 1 "c:/c4w/mikroc pro for arm/include/stdint.h"
#line 6 "//vboxsvr/storage/git/mikroe/hexiwear/sw/click examples mikroc/2.examples/hexiwear_nfc_click/example/arm/oled_resources.h"
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
#line 22 "//vboxsvr/storage/git/mikroe/hexiwear/sw/click examples mikroc/2.examples/hexiwear_nfc_click/example/arm/oled_driver.h"
oled_status_t OLED_Init(void);
#line 37 "//vboxsvr/storage/git/mikroe/hexiwear/sw/click examples mikroc/2.examples/hexiwear_nfc_click/example/arm/oled_driver.h"
oled_status_t OLED_DrawBox (
 uint16_t xCrd,
 uint16_t yCrd,
 uint16_t width,
 uint16_t height,
 uint16_t color
 );
#line 54 "//vboxsvr/storage/git/mikroe/hexiwear/sw/click examples mikroc/2.examples/hexiwear_nfc_click/example/arm/oled_driver.h"
oled_status_t OLED_FillScreen( uint16_t color );
#line 68 "//vboxsvr/storage/git/mikroe/hexiwear/sw/click examples mikroc/2.examples/hexiwear_nfc_click/example/arm/oled_driver.h"
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
#line 1 "//vboxsvr/storage/git/mikroe/hexiwear/sw/click examples mikroc/2.examples/hexiwear_nfc_click/example/arm/p2p_ndef.h"
#line 1 "c:/c4w/mikroc pro for arm/include/stdint.h"
#line 1 "c:/c4w/mikroc pro for arm/include/stdbool.h"
#line 72 "//vboxsvr/storage/git/mikroe/hexiwear/sw/click examples mikroc/2.examples/hexiwear_nfc_click/example/arm/p2p_ndef.h"
void p2p_ndef_reset( void );
void p2p_ndef_next( uint8_t *p_cmd, uint16_t cmd_size,
 uint8_t *rsp, uint16_t *p_rsp_size );
 _Bool  p2p_ndef_set_record( uint8_t *p_record, uint16_t record_size,
 void *cb );
void p2p_ndef_register_pull_callback( void *p_cb );
#line 1 "//vboxsvr/storage/git/mikroe/hexiwear/sw/click examples mikroc/2.examples/hexiwear_nfc_click/example/arm/rw_ndef.h"
#line 1 "c:/c4w/mikroc pro for arm/include/stdint.h"
#line 60 "//vboxsvr/storage/git/mikroe/hexiwear/sw/click examples mikroc/2.examples/hexiwear_nfc_click/example/arm/rw_ndef.h"
typedef void rw_ndef_callback_t( uint8_t *, uint16_t );
#line 65 "//vboxsvr/storage/git/mikroe/hexiwear/sw/click examples mikroc/2.examples/hexiwear_nfc_click/example/arm/rw_ndef.h"
extern uint8_t ndef_buffer[ 240 ];
extern rw_ndef_callback_t *p_rw_ndef_pull_cb;
#line 79 "//vboxsvr/storage/git/mikroe/hexiwear/sw/click examples mikroc/2.examples/hexiwear_nfc_click/example/arm/rw_ndef.h"
void rw_ndef_register_pull_callback( void *p_cb );
#line 85 "//vboxsvr/storage/git/mikroe/hexiwear/sw/click examples mikroc/2.examples/hexiwear_nfc_click/example/arm/rw_ndef.h"
void rw_ndef_reset( uint8_t type );
#line 94 "//vboxsvr/storage/git/mikroe/hexiwear/sw/click examples mikroc/2.examples/hexiwear_nfc_click/example/arm/rw_ndef.h"
void rw_ndef_read_next( uint8_t *p_cmd, uint16_t cmd_size,
 uint8_t *rsp, uint16_t *p_rsp_size );
#line 1 "//vboxsvr/storage/git/mikroe/hexiwear/sw/click examples mikroc/2.examples/hexiwear_nfc_click/example/arm/rw_ndef_t3t.h"
#line 1 "c:/c4w/mikroc pro for arm/include/stdint.h"
#line 75 "//vboxsvr/storage/git/mikroe/hexiwear/sw/click examples mikroc/2.examples/hexiwear_nfc_click/example/arm/rw_ndef_t3t.h"
void rw_ndef_t3t_reset( void );
#line 81 "//vboxsvr/storage/git/mikroe/hexiwear/sw/click examples mikroc/2.examples/hexiwear_nfc_click/example/arm/rw_ndef_t3t.h"
void rw_ndef_t3t_set_id_m( uint8_t *p_id_m );
#line 90 "//vboxsvr/storage/git/mikroe/hexiwear/sw/click examples mikroc/2.examples/hexiwear_nfc_click/example/arm/rw_ndef_t3t.h"
void rw_ndef_t3t_read_next( uint8_t *p_cmd, uint16_t cmd_size,
 uint8_t *rsp, uint16_t *p_rsp_size );
#line 57 "//VBOXSVR/storage/git/MikroE/HEXIWEAR/SW/Click Examples mikroC/2.Examples/HEXIWEAR_NFC_Click/example/ARM/nfc.c"
static  _Bool  volatile rx_flag;
static uint32_t volatile timer_tick;
#line 63 "//VBOXSVR/storage/git/MikroE/HEXIWEAR/SW/Click Examples mikroC/2.Examples/HEXIWEAR_NFC_Click/example/ARM/nfc.c"
static int host_rx( uint8_t *p_rx_buff, uint16_t rx_buff_size,
 uint16_t *p_nbytes_read, uint16_t timeout );
static int host_tx_rx( uint8_t *p_tx_buff, uint16_t tx_buff_len,
 uint8_t *p_rx_buff, uint16_t rx_buff_size,
 uint16_t *p_nbytes_read );
static int initialize_core( void );
#line 73 "//VBOXSVR/storage/git/MikroE/HEXIWEAR/SW/Click Examples mikroC/2.Examples/HEXIWEAR_NFC_Click/example/ARM/nfc.c"
static void p2p_mode( nfc_interface_t *rf_intf );


static void reader_mode( nfc_interface_t *rf_intf );

int nfc_reader_tag_cmd ( uint8_t *command, uint8_t commandSize,
 uint8_t *answer, uint8_t *answer_size );
#line 85 "//VBOXSVR/storage/git/MikroE/HEXIWEAR/SW/Click Examples mikroC/2.Examples/HEXIWEAR_NFC_Click/example/ARM/nfc.c"
static int host_rx( uint8_t *p_rx_buff, uint16_t rx_buff_size,
 uint16_t *p_nbytes_read, uint16_t timeout )
{
 timer_tick = 0;


 while( !rx_flag )
 {
 if( timer_tick > ( timeout / 10 ) )
 return  -1 ;
 }


 if( nfc_hal_read( p_rx_buff, p_nbytes_read, rx_buff_size ) )
 return  -1 ;

 rx_flag =  0 ;


 return  0 ;
}

static int host_tx_rx( uint8_t *p_tx_buff, uint16_t tx_buff_len,
 uint8_t *p_rx_buff, uint16_t rx_buff_size,
 uint16_t *p_nbytes_read )
{

 char tmp_txt[80];
 char hex[3];
 char *ptr = p_tx_buff;
 char *ptr_rx = p_rx_buff;
 int i;


 IntToStr( tx_buff_len, tmp_txt );



 for( i = 0; i < tx_buff_len; i++ )
 {
 ByteToHex( *ptr++, hex );
 sprinti( tmp_txt, "%s ", hex );

 }




 if( nfc_hal_write( p_tx_buff, tx_buff_len ) )
 return  -1 ;
 else if( host_rx( p_rx_buff, rx_buff_size, p_nbytes_read,  1000  ) )
 return  -1 ;



 IntToStr( *p_nbytes_read, tmp_txt );



 for( i = 0; i < *p_nbytes_read; i++ )
 {
 ByteToHex( *ptr_rx++, hex );
 sprinti( tmp_txt, "%s ", hex );

 }




 return  0 ;
}

static int initialize_core()
{
 uint8_t answer[ 258 ] = {0};
 uint16_t answer_size = 0;
 int i = 10;
 uint8_t CORE_RESET_CMD[] = { 0x20, 0x00, 0x01, 0x01 };
 uint8_t CORE_INIT_CMD[] = { 0x20, 0x01, 0x00 };



 OLED_DrawBox(0, 80, 96, 15, 0);
 OLED_WriteText("Reset and Init", 4, 80);


 while( host_tx_rx( CORE_RESET_CMD, sizeof( CORE_RESET_CMD ), answer, sizeof( answer ), &answer_size ) )
 {
 if( i-- == 0 )
 {
 return  -1 ;
 }
 nfc_hal_delay( 500 );
 }


 if( host_tx_rx( CORE_INIT_CMD, sizeof( CORE_INIT_CMD ), answer, sizeof( answer ), &answer_size ) )
 {
 return  -1 ;
 }
 else if( ( answer[0] != 0x40 ) || ( answer[1] != 0x01 ) || ( answer[3] != 0x00 ) )
 {
 return  -1 ;
 }
}
#line 231 "//VBOXSVR/storage/git/MikroE/HEXIWEAR/SW/Click Examples mikroC/2.Examples/HEXIWEAR_NFC_Click/example/ARM/nfc.c"
static void p2p_mode( nfc_interface_t *rf_intf )
{
 uint8_t answer[ 258 ] = {0};
 uint16_t answer_size = 0;
 uint8_t NCIL_LCP_SYMM[] = { 0x00, 0x00, 0x02, 0x00, 0x00 };
 uint8_t NCI_RESTART_DISCOVERY[] = { 0x21, 0x06, 0x01, 0x03 };


 p2p_ndef_reset();


 if( ( rf_intf->mode_tech &  0x80  ) !=  0x80  )
 {

 host_tx_rx( NCIL_LCP_SYMM, sizeof( NCIL_LCP_SYMM ), answer,
 sizeof( answer ), &answer_size );
 }


 while( host_rx( answer, sizeof( answer ), &answer_size,
  2000  ) ==  0  )
 {

 if( ( answer[0] == 0x00 ) && ( answer[1] == 0x00 ) )
 {
 uint8_t cmd[256] = {0};
 uint16_t cmd_size = 0;

 p2p_ndef_next( &answer[3], answer[2], &cmd[3],
 ( uint16_t * ) &cmd_size );


 cmd[0] = 0x00;
 cmd[1] = ( cmd_size & 0xFF00 ) >> 8;
 cmd[2] = cmd_size & 0x00FF;

 host_tx_rx( cmd, cmd_size + 3, answer, sizeof( answer ),
 &answer_size );
 }

 else if ( ( answer[0] == 0x60 ) && ( answer[1] == 0x08 ) )
 break;

 else if( ( answer[0] == 0x61 ) && ( answer[1] == 0x06 ) )
 {

 break;
 }
 }


 if( ( rf_intf->mode_tech &  0x80  ) !=  0x80  )
 {

 host_tx_rx( NCI_RESTART_DISCOVERY,
 sizeof( NCI_RESTART_DISCOVERY ),
 answer,
 sizeof( answer ),
 &answer_size );
 host_rx( answer,
 sizeof( answer ),
 &answer_size,
  2000  );
 }
}



static void reader_mode( nfc_interface_t *rf_intf )
{
 uint8_t answer[ 258 ];
 uint8_t cmd[256] = {0};
 uint16_t cmd_size = 0;
 uint16_t answer_size = 0;
 uint8_t NCI_PRES_CHECK_T1T[] =
 {
 0x00, 0x00, 0x07, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
 };
 uint8_t NCI_PRES_CHECK_T2T[] =
 {
 0x00, 0x00, 0x02, 0x30, 0x00
 };
 uint8_t NCI_POLLING_CMD_T3T[] =
 {
 0x21, 0x08, 0x04, 0x12, 0xFC, 0x00, 0x01
 };
 uint8_t NCI_PRES_CHECK_ISO_DEP[] =
 {
 0x2F, 0x11, 0x00
 };
 uint8_t NCI_RESTART_DISCOVERY[] = { 0x21, 0x06, 0x01, 0x03 };

 rw_ndef_reset( rf_intf->protocol );


 if ( rf_intf->protocol ==  0x3  )
 {
 host_tx_rx( NCI_POLLING_CMD_T3T,
 sizeof( NCI_POLLING_CMD_T3T ),
 answer,
 sizeof( answer ),
 &answer_size );
 host_rx( answer,
 sizeof( answer ),
 &answer_size,
  1000  );
 if ( ( answer[0] == 0x61 ) && ( answer[1] == 0x08 )
 && ( answer[3] == 0x00 ) )
 rw_ndef_t3t_set_id_m( &answer[6] );
 else
 goto restart_discovery;
 }

 while( 1 )
 {
 rw_ndef_read_next( &answer[3], answer[2], &cmd[3], ( uint16_t * ) &cmd_size );
 if( cmd_size == 0 )
 {

 break;
 } else {

 cmd[0] = 0x00;
 cmd[1] = ( cmd_size & 0xFF00 ) >> 8;
 cmd[2] = cmd_size & 0x00FF;

 host_tx_rx( cmd, cmd_size + 3, answer, sizeof( answer ), &answer_size );
 host_rx( answer, sizeof( answer ), &answer_size,  2000  );
 }
 }


 switch( rf_intf->protocol )
 {
 case  0x1 :
 do {
 nfc_hal_delay( 500 );
 host_tx_rx( NCI_PRES_CHECK_T1T,
 sizeof( NCI_PRES_CHECK_T1T ),
 answer,
 sizeof( answer ),
 &answer_size );
 host_rx( answer,
 sizeof( answer ),
 &answer_size,
  1000  );
 } while ( ( answer[0] == 0x00 ) && ( answer[1] == 0x00 ) );

 break;

 case  0x2 :
 do {
 nfc_hal_delay( 500 );
 host_tx_rx( NCI_PRES_CHECK_T2T,
 sizeof( NCI_PRES_CHECK_T2T ),
 answer,
 sizeof( answer ),
 &answer_size );
 host_rx( answer,
 sizeof( answer ),
 &answer_size,
  1000  );
 } while ( ( answer[0] == 0x00 ) && ( answer[1] == 0x00 ) &&
 ( answer[2] == 0x11 ) );
 break;

 case  0x4 :
 do {
 nfc_hal_delay( 500 );
 host_tx_rx( NCI_PRES_CHECK_ISO_DEP,
 sizeof( NCI_PRES_CHECK_ISO_DEP ),
 answer,
 sizeof( answer ),
 &answer_size );
 host_rx( answer, sizeof( answer ),&answer_size,  1000  );
 } while ( ( answer[0] == 0x6F ) && ( answer[1] == 0x11 ) &&
 ( answer[2] == 0x01 ) && ( answer[3] == 0x01 ) );
 break;

 default:

 break;
 }

restart_discovery:


 host_tx_rx( NCI_RESTART_DISCOVERY,
 sizeof( NCI_RESTART_DISCOVERY ),
 answer,
 sizeof( answer ),
 &answer_size );
 host_rx( answer,
 sizeof( answer ),
 &answer_size,
  1000  );
}

int nfc_reader_tag_cmd ( uint8_t *command, uint8_t command_size,
 uint8_t *answer, uint8_t *answer_size )
{
 int status =  -1 ;
 uint8_t cmd[256];
 uint8_t ans[ 258 ] = {0};
 uint16_t ans_size = 0;;


 cmd[0] = 0x00;
 cmd[1] = 0x00;
 cmd[2] = command_size;
 memcpy( &cmd[3], command, command_size );
 host_tx_rx( cmd, command_size + 3, ans, sizeof( ans ), &ans_size );


 host_rx( ans, sizeof( ans ), &ans_size,  2000  );

 if ( ( ans[0] == 0x0 ) && ( ans[1] == 0x0 ) )
 status =  0 ;

 *answer_size = ans[2];
 memcpy( answer, &ans[3], *answer_size );

 return status;
}


int nfc_init( uint8_t slave_address )
{

 uint8_t answer[ 258 ] = {0};
 uint16_t answer_size = 0;
 uint8_t CORE_SET_POWER_MODE_CMD[] = { 0x2f, 0x00, 0x01, 0x00 };
 uint8_t TEST_ANTENNA_CMD[] = { 0x2f, 0x3d, 0x05, 0x20, 0x00, 0x00, 0x00, 0x00 };
 uint8_t TEST_PRBS_CMD[] = { 0x2f, 0x30, 0x04, 0x00, 0x00, 0x00, 0x1f };
 int i, j;


 if( slave_address !=  0x28  && slave_address !=  0x29  )
 return  -1 ;


 nfc_hal_init( slave_address );



 OLED_DrawBox(0, 80, 96, 15, 0);
 OLED_WriteText("Start Test Mode", 4, 80);
 initialize_core();
#line 484 "//VBOXSVR/storage/git/MikroE/HEXIWEAR/SW/Click Examples mikroC/2.Examples/HEXIWEAR_NFC_Click/example/ARM/nfc.c"
 OLED_DrawBox(0, 80, 96, 15, 0);
 OLED_WriteText("Disabe Standby", 4, 80);
 host_tx_rx( CORE_SET_POWER_MODE_CMD, sizeof( CORE_SET_POWER_MODE_CMD ), answer, sizeof( answer ), &answer_size );

 if( answer[3] == 0x00 )
 {

 OLED_DrawBox(0, 80, 96, 15, 0);
 OLED_WriteText("Standby OFF", 4, 80);
 }

 for( i = 0, j = 4; i < 4; i++, j++ )
 {

 OLED_DrawBox(0, 80, 96, 15, 0);
 OLED_WriteText("Test Antenna", 4, 80);
 TEST_ANTENNA_CMD[ j ] |= 0x01;

 host_tx_rx( TEST_ANTENNA_CMD, sizeof( TEST_ANTENNA_CMD ), answer, sizeof( answer ), &answer_size );

 TEST_ANTENNA_CMD[ j ] &= ~0x01;

 host_tx_rx( TEST_ANTENNA_CMD, sizeof( TEST_ANTENNA_CMD ), answer, sizeof( answer ), &answer_size );

 host_tx_rx( TEST_ANTENNA_CMD, sizeof( TEST_ANTENNA_CMD ), answer, sizeof( answer ), &answer_size );

 TEST_ANTENNA_CMD[ j ] |= 0x01;

 host_tx_rx( TEST_ANTENNA_CMD, sizeof( TEST_ANTENNA_CMD ), answer, sizeof( answer ), &answer_size );
 }

 OLED_DrawBox(0, 80, 96, 15, 0);
 OLED_WriteText("Start Testing", 4, 80);
 host_tx_rx( TEST_PRBS_CMD, sizeof( TEST_PRBS_CMD ), answer, sizeof( answer ), &answer_size );

 if( answer[3] == 0x00 )
 {

 OLED_DrawBox(0, 80, 96, 15, 0);
 OLED_WriteText("Test Success", 4, 80);
 }
 else
 {

 OLED_DrawBox(0, 80, 96, 15, 0);
 OLED_WriteText("Test Fail", 4, 80);
 }

 nfc_hal_reset();



 if( initialize_core() )
 return  -1 ;

 return  0 ;
}

void nfc_rx_ready()
{
 rx_flag =  1 ;
}

void nfc_timer_tick()
{
 timer_tick++;
}

int nfc_configure( nfc_mode_t mode )
{
 uint8_t command[256];
 uint8_t answer[ 258 ] = {0};
 uint16_t answer_size = 0;
 uint8_t item = 0;

 uint8_t NCI_DISCOVER_MAP_CMD[] = { 0x21, 0x00 };
#line 565 "//VBOXSVR/storage/git/MikroE/HEXIWEAR/SW/Click Examples mikroC/2.Examples/HEXIWEAR_NFC_Click/example/ARM/nfc.c"
 uint8_t DM_P2P[] = { 0x5, 0x3, 0x3 };
 uint8_t R_P2P[] = { 0x1, 0x3, 0x0, 0x1, 0x5 };
 uint8_t NCI_SET_CONFIG_NFC[] =
 {
 0x20, 0x02, 0x1F, 0x02, 0x29, 0x0D, 0x46, 0x66, 0x6D, 0x01, 0x01,
 0x11, 0x03, 0x02, 0x00, 0x01, 0x04, 0x01, 0xFA, 0x61, 0x0D, 0x46,
 0x66, 0x6D, 0x01, 0x01, 0x11, 0x03, 0x02, 0x00, 0x01, 0x04, 0x01,
 0xFA
 };


 uint8_t DM_RW[] =
 {
 0x1, 0x1, 0x1, 0x2, 0x1, 0x1, 0x3, 0x1, 0x1, 0x4, 0x1, 0x2, 0x80,
 0x01, 0x80
 };
 uint8_t NCI_PROPRIETARY_ACT_CMD[] = { 0x2F, 0x02, 0x00 };


 uint8_t NCI_ROUTING[] =
 {
 0x21, 0x01, 0x07, 0x00, 0x01
 };
 uint8_t nci_set_config_nfca_selrsp[] =
 {
 0x20, 0x02, 0x04, 0x01, 0x32, 0x01, 0x00
 };


 if( mode == NFC_MODE_NONE )
 return  0 ;



 if( mode == NFC_MODE_RW )
 {
 if( host_tx_rx( NCI_PROPRIETARY_ACT_CMD, sizeof( NCI_PROPRIETARY_ACT_CMD ),
 answer, sizeof( answer ), &answer_size ) )
 return  -1 ;
 else if( ( answer[0] != 0x4F ) || ( answer[1] != 0x02 ) ||
 ( answer[3] != 0x00 ) )
 return  -1 ;
 }



 item = 0;
#line 620 "//VBOXSVR/storage/git/MikroE/HEXIWEAR/SW/Click Examples mikroC/2.Examples/HEXIWEAR_NFC_Click/example/ARM/nfc.c"
 if( mode & NFC_MODE_P2P )
 {
 memcpy( &command[4 + ( 3 * item )], ( void* )DM_P2P, sizeof( DM_P2P ) );
 item++;
 }


 if( mode & NFC_MODE_RW )
 {
 memcpy( &command[4 + ( 3 * item )], ( void* )DM_RW, sizeof( DM_RW ) );
 item += sizeof( DM_RW ) / 3;
 }


 if( item != 0 )
 {
 memcpy( command, ( void *)NCI_DISCOVER_MAP_CMD, sizeof( NCI_DISCOVER_MAP_CMD ) );
 command[2] = 1 + ( item * 3 );
 command[3] = item;

 if( host_tx_rx( command, 3 + command[2], answer, sizeof( answer ),
 &answer_size ) )
 return  -1 ;
 else if( ( answer[0] != 0x41 ) || ( answer[1] != 0x00 ) ||
 ( answer[3] != 0x00 ) )
 return  -1 ;
 }



 item = 0;
#line 659 "//VBOXSVR/storage/git/MikroE/HEXIWEAR/SW/Click Examples mikroC/2.Examples/HEXIWEAR_NFC_Click/example/ARM/nfc.c"
 if( mode & NFC_MODE_P2P )
 {
 memcpy( &command[5 + ( 5 * item )], ( void* )R_P2P, sizeof( R_P2P ) );
 item++;
 }


 if( item != 0 )
 {
 memcpy( command, ( void* )NCI_ROUTING, sizeof( NCI_ROUTING ) );
 command[2] = 2 + ( item * 5 );
 command[4] = item;
 if( host_tx_rx( command, 3 + command[2] , answer, sizeof( answer ),
 &answer_size ) )
 return  -1 ;
 else if( ( answer[0] != 0x41 ) || ( answer[1] != 0x01 ) ||
 ( answer[3] != 0x00 ) )
 return  -1 ;
 }
#line 686 "//VBOXSVR/storage/git/MikroE/HEXIWEAR/SW/Click Examples mikroC/2.Examples/HEXIWEAR_NFC_Click/example/ARM/nfc.c"
 if( mode & NFC_MODE_P2P )
 nci_set_config_nfca_selrsp[6] += 0x40;


 if( nci_set_config_nfca_selrsp[6] != 0x00 )
 {
 if( host_tx_rx( nci_set_config_nfca_selrsp,
 sizeof( nci_set_config_nfca_selrsp ),
 answer, sizeof( answer ), &answer_size ) )
 return  -1 ;
 else if( ( answer[0] != 0x40 ) || ( answer[1] != 0x02 ) ||
 ( answer[3] != 0x00 ) )
 return  -1 ;
 }




 if( mode & NFC_MODE_P2P )
 {
 if( host_tx_rx( NCI_SET_CONFIG_NFC, sizeof( NCI_SET_CONFIG_NFC ),
 answer, sizeof( answer ),&answer_size ) )
 return  -1 ;
 else if( ( answer[0] != 0x40 ) || ( answer[1] != 0x02 ) ||
 ( answer[3] != 0x00 ) )
 return  -1 ;
 }


 return  0 ;
}

int nfc_start_discovery( uint8_t *p_tech_tab, uint8_t tech_tab_size )
{
 uint8_t command[256];
 uint8_t answer[ 258 ] = {0};
 uint16_t answer_size = 0;
 uint8_t i;
 uint8_t NCI_DISCOVER_CMD[] = { 0x21, 0x03 };



 OLED_DrawBox(0, 80, 96, 15, 0);
 OLED_WriteText("Discovery Start", 4, 80);


 memcpy( command, ( void* )NCI_DISCOVER_CMD, sizeof( NCI_DISCOVER_CMD ) );


 command[2] = ( tech_tab_size * 2 ) + 1;
 command[3] = tech_tab_size;

 for ( i = 0; i < tech_tab_size; i++ )
 {
 command[( i * 2 ) + 4] = p_tech_tab[i];
 command[( i * 2 ) + 5] = 0x01;
 }

 if( host_tx_rx( command, ( tech_tab_size * 2 ) + 4, answer, sizeof( answer ),
 &answer_size ) )
 return  -1 ;
 else if ( ( answer[0] != 0x41 ) || ( answer[1] != 0x03 ) ||
 ( answer[3] != 0x00 ) )
 return  -1 ;

 return  0 ;
}

int nfc_restart_discovery( void )
{
 uint8_t answer[ 258 ] = {0};
 uint16_t answer_size = 0;
 uint8_t NCI_RESTART_DISCOVERY[] = { 0x21, 0x06, 0x01, 0x03 };

 if( host_tx_rx( NCI_RESTART_DISCOVERY, sizeof( NCI_RESTART_DISCOVERY ),
 answer, sizeof( answer ), &answer_size ) )
 return  -1 ;
 else if( host_rx( answer, sizeof( answer ), &answer_size,  1000  ) )
 return  -1 ;

 return  0 ;
}

int nfc_stop_discovery( void )
{
 uint8_t answer[ 258 ] = {0};
 uint16_t answer_size = 0;
 uint8_t NCI_STOP_DISCOVERY[] = { 0x21, 0x06, 0x01, 0x00 };

 if( host_tx_rx( NCI_STOP_DISCOVERY, sizeof( NCI_STOP_DISCOVERY ),
 answer,sizeof( answer ), &answer_size ) )
 return  -1 ;
 else if( host_rx( answer, sizeof( answer ), &answer_size,  1000  ) )
 return  -1 ;

 return  0 ;
}

volatile uint8_t answer[ 258 ] = {0};

void nfc_wait_for_discovery_notification( nfc_interface_t *prf_intf )
{

 uint16_t answer_size = 0;

 do
 {
 host_rx( answer, sizeof( answer), &answer_size,
  0  );
 } while( ( answer[0] != 0x61 ) || ( ( answer[1] != 0x05 ) &&
 ( answer[1] != 0x03 ) ) );


 if( answer[1] == 0x05 )
 {
 prf_intf->interface = answer[4];
 prf_intf->protocol = answer[5];
 prf_intf->mode_tech = answer[6];
 } else {
 prf_intf->interface =  0x0 ;
 prf_intf->protocol = answer[4];
 prf_intf->mode_tech = answer[5];


 while( answer[answer_size - 1] == 0x02 )
 host_rx( answer, sizeof( answer ), &answer_size,  1000  );
 }
}

void nfc_process( uint8_t mode, nfc_interface_t *rf_intf )
{
 switch ( mode )
 {
#line 826 "//VBOXSVR/storage/git/MikroE/HEXIWEAR/SW/Click Examples mikroC/2.Examples/HEXIWEAR_NFC_Click/example/ARM/nfc.c"
 case NFC_MODE_P2P:
 p2p_mode( rf_intf );
 break;



 case NFC_MODE_RW:
 reader_mode( rf_intf );
 break;


 default:
 break;
 }
}

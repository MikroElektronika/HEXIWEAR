#line 1 "C:/Users/richard/Desktop/WORKDIR/Skywire/example/ARM/at_engine/at_engine.c"
#line 1 "c:/users/richard/desktop/workdir/skywire/example/arm/at_engine/at_engine.h"
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
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for arm/include/stddef.h"



typedef long ptrdiff_t;


 typedef unsigned long size_t;

typedef unsigned long wchar_t;
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for arm/include/string.h"





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
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for arm/include/stdbool.h"



 typedef char _Bool;
#line 23 "c:/users/richard/desktop/workdir/skywire/example/arm/at_engine/at_engine.h"
typedef void ( *at_cmd_cb )( char *buffer );
#line 28 "c:/users/richard/desktop/workdir/skywire/example/arm/at_engine/at_engine.h"
typedef void ( *at_write_p )( unsigned int in );
#line 40 "c:/users/richard/desktop/workdir/skywire/example/arm/at_engine/at_engine.h"
typedef enum
{
#line 44 "c:/users/richard/desktop/workdir/skywire/example/arm/at_engine/at_engine.h"
 AT_CMD_UNKNOWN = 0,
#line 47 "c:/users/richard/desktop/workdir/skywire/example/arm/at_engine/at_engine.h"
 AT_CMD_GET = 1,
#line 50 "c:/users/richard/desktop/workdir/skywire/example/arm/at_engine/at_engine.h"
 AT_CMD_SET = 2,
#line 53 "c:/users/richard/desktop/workdir/skywire/example/arm/at_engine/at_engine.h"
 AT_CMD_TEST = 3,
#line 56 "c:/users/richard/desktop/workdir/skywire/example/arm/at_engine/at_engine.h"
 AT_CMD_EXEC = 4,

}at_type_t;
#line 68 "c:/users/richard/desktop/workdir/skywire/example/arm/at_engine/at_engine.h"
typedef struct
{
#line 72 "c:/users/richard/desktop/workdir/skywire/example/arm/at_engine/at_engine.h"
 uint32_t hash;
#line 75 "c:/users/richard/desktop/workdir/skywire/example/arm/at_engine/at_engine.h"
 uint32_t timeout;
#line 78 "c:/users/richard/desktop/workdir/skywire/example/arm/at_engine/at_engine.h"
 at_cmd_cb getter;
#line 81 "c:/users/richard/desktop/workdir/skywire/example/arm/at_engine/at_engine.h"
 at_cmd_cb setter;
#line 84 "c:/users/richard/desktop/workdir/skywire/example/arm/at_engine/at_engine.h"
 at_cmd_cb tester;
#line 87 "c:/users/richard/desktop/workdir/skywire/example/arm/at_engine/at_engine.h"
 at_cmd_cb executer;

}at_cmd_t;
#line 107 "c:/users/richard/desktop/workdir/skywire/example/arm/at_engine/at_engine.h"
void at_init( at_cmd_cb default_callback, at_write_p default_write,
 uint8_t *buffer_ptr, uint16_t buffer_size );
#line 119 "c:/users/richard/desktop/workdir/skywire/example/arm/at_engine/at_engine.h"
void at_rx( char rx_input );
#line 127 "c:/users/richard/desktop/workdir/skywire/example/arm/at_engine/at_engine.h"
void at_tick( void );
#line 137 "c:/users/richard/desktop/workdir/skywire/example/arm/at_engine/at_engine.h"
void at_cmd_single( char *cmd );
#line 149 "c:/users/richard/desktop/workdir/skywire/example/arm/at_engine/at_engine.h"
void at_cmd_double( char *cmd, char *arg_1 );
#line 162 "c:/users/richard/desktop/workdir/skywire/example/arm/at_engine/at_engine.h"
void at_cmd_triple( char *cmd, char *arg_1, char *arg_2 );
#line 178 "c:/users/richard/desktop/workdir/skywire/example/arm/at_engine/at_engine.h"
void at_cmd_save( char *cmd, uint32_t timeout,
 at_cmd_cb getter, at_cmd_cb setter,
 at_cmd_cb tester, at_cmd_cb executer );
#line 187 "c:/users/richard/desktop/workdir/skywire/example/arm/at_engine/at_engine.h"
void at_process( void );
#line 140 "C:/Users/richard/Desktop/WORKDIR/Skywire/example/ARM/at_engine/at_engine.c"
typedef enum
{
 AT_OK,
 AT_ERROR,
 AT_UNKNOWN

}at_t;
#line 159 "C:/Users/richard/Desktop/WORKDIR/Skywire/example/ARM/at_engine/at_engine.c"
extern sfr sbit CTS_PIN;
extern sfr sbit RTS_PIN;
#line 167 "C:/Users/richard/Desktop/WORKDIR/Skywire/example/ARM/at_engine/at_engine.c"
static void ( *write_uart_p ) ( unsigned int data_out );
#line 175 "C:/Users/richard/Desktop/WORKDIR/Skywire/example/ARM/at_engine/at_engine.c"
static const uint8_t header_size = 2;


static volatile uint8_t* p_rx_buf;
static volatile uint16_t rx_idx;
static uint16_t rx_max;


static volatile  _Bool  t_response_f;
static volatile  _Bool  t_char_f;


static volatile uint32_t t_response_c;
static volatile uint32_t t_char_c;


static volatile uint32_t t_response_l;
static volatile uint32_t t_char_l;


static at_cmd_cb tmp_cb;
static uint8_t tmp_cnt;
static uint32_t tmp_timer;


static volatile at_cmd_cb cb;
static volatile at_cmd_cb cb_default;


static uint8_t at_cmd_storage_used;
static at_cmd_t at_cmd_storage [  50  ];


static volatile  _Bool  cue_f;

static volatile  _Bool  response_f;

static volatile  _Bool  no_response_f;
#line 226 "C:/Users/richard/Desktop/WORKDIR/Skywire/example/ARM/at_engine/at_engine.c"
static void _tx( uint8_t *tx_input, uint8_t delimiter );
#line 237 "C:/Users/richard/Desktop/WORKDIR/Skywire/example/ARM/at_engine/at_engine.c"
static uint32_t _parse_hash( char *cmd );
#line 248 "C:/Users/richard/Desktop/WORKDIR/Skywire/example/ARM/at_engine/at_engine.c"
static uint16_t _parse_find( char* cmd );
#line 264 "C:/Users/richard/Desktop/WORKDIR/Skywire/example/ARM/at_engine/at_engine.c"
static void _parse_save( char *command, uint32_t timeout,
 at_cmd_cb getter, at_cmd_cb setter,
 at_cmd_cb tester, at_cmd_cb executer );
#line 282 "C:/Users/richard/Desktop/WORKDIR/Skywire/example/ARM/at_engine/at_engine.c"
static at_type_t _parse_pre( char *raw_in, char *clean_out );
#line 295 "C:/Users/richard/Desktop/WORKDIR/Skywire/example/ARM/at_engine/at_engine.c"
static void _parse_exe( char *input, at_cmd_cb *cb, uint32_t *timeout );
#line 299 "C:/Users/richard/Desktop/WORKDIR/Skywire/example/ARM/at_engine/at_engine.c"
static void _tx( uint8_t *tx_input, uint8_t delimiter )
{
#line 304 "C:/Users/richard/Desktop/WORKDIR/Skywire/example/ARM/at_engine/at_engine.c"
 while( *tx_input )
 {
#line 313 "C:/Users/richard/Desktop/WORKDIR/Skywire/example/ARM/at_engine/at_engine.c"
 write_uart_p( *tx_input++ );
 }

 write_uart_p( delimiter );
 write_uart_p( '\n' );
#line 322 "C:/Users/richard/Desktop/WORKDIR/Skywire/example/ARM/at_engine/at_engine.c"
}

static uint32_t _parse_hash( char *cmd )
{
 uint16_t ch = 0;
 uint32_t hash = 4321;
 while( ( ch = *( cmd++ ) ) )
 hash = ( ( hash << 5 ) + hash ) + ch;
 return hash;
}

static uint16_t _parse_find( char* cmd )
{
 uint8_t _cnt = 0;

 uint32_t tmp_hash = _parse_hash( cmd );
 for( _cnt = 0; _cnt < at_cmd_storage_used; _cnt++ )
 if( at_cmd_storage[ _cnt ].hash == tmp_hash )
 return _cnt;
 return 0;
}

static void _parse_save( char *command, uint32_t timeout,
 at_cmd_cb getter, at_cmd_cb setter,
 at_cmd_cb tester, at_cmd_cb executer )
{
 at_cmd_t cmd;

 cmd.hash = _parse_hash( command );
 cmd.timeout = timeout;
 cmd.getter = getter;
 cmd.setter = setter;
 cmd.tester = tester;
 cmd.executer = executer;

 if( strlen( command ) >=  15  +  2  )
 return;

 if( at_cmd_storage_used ==  50  )
 return;

 if( _parse_find( command ) )
 return;

 at_cmd_storage[ at_cmd_storage_used ] = cmd;
 at_cmd_storage_used++;
}

static at_type_t _parse_pre( char *raw_in, char *clean_out )
{
 uint8_t _cnt = 0;
 uint8_t end_pos = 0;
 uint8_t set_pos = 0;
 uint8_t get_pos = 0;
 uint8_t start_pos = 0;
 char* tmp_ptr = raw_in;
 char tmp_cmd[  15  ] = { 0 };

 if( strlen( tmp_ptr ) <=  2  )
 return AT_CMD_UNKNOWN;

 strncpy( tmp_cmd, tmp_ptr,  15  );

 for( _cnt = 0; _cnt <  15 ; _cnt++ )
 {
 if( tmp_cmd[ _cnt ] == '\0' )
 {
 if( !end_pos )
 end_pos = _cnt;
 break;
 }
#line 399 "C:/Users/richard/Desktop/WORKDIR/Skywire/example/ARM/at_engine/at_engine.c"
 if( ( tmp_cmd[ _cnt ] == '+') && !start_pos )
 start_pos = _cnt;

 if( ( tmp_cmd[ _cnt ] == '=' ) && !set_pos )
 set_pos = _cnt;

 if( ( tmp_cmd[ _cnt ] == '?' ) && !get_pos )
 get_pos = _cnt;

 if( ( ( ( tmp_cmd[ _cnt ] == '\r' ) ||
 ( tmp_cmd[ _cnt ] == '\n' ) ||
 ( tmp_cmd[ _cnt ] == ':' ) ) && !end_pos ) && start_pos )
 end_pos = _cnt;
 }

 if( !set_pos && !get_pos )
 {
 strncpy( clean_out, &tmp_cmd[ start_pos ], end_pos - start_pos );
 return AT_CMD_EXEC;

 } else if( !set_pos && get_pos ) {

 strncpy( clean_out, &tmp_cmd[ start_pos ], get_pos - start_pos );
 return AT_CMD_TEST;

 } else if( set_pos && !get_pos ) {

 strncpy( clean_out, &tmp_cmd[ start_pos ], set_pos - start_pos );
 return AT_CMD_SET;

 } else if( set_pos == get_pos - 1 ) {

 strncpy( clean_out, &tmp_cmd[ start_pos ], set_pos - start_pos );
 return AT_CMD_GET;
 }

 return AT_CMD_UNKNOWN;
}

void _parse_exe( char *input, at_cmd_cb *cb, uint32_t *timeout )
{
 at_type_t cmd_type = 0;
 uint16_t cmd_idx = 0;
 char cmd_temp[  15  ] = { 0 };

 if( !( cmd_type = _parse_pre( input, cmd_temp ) ) )
 {
 *cb = at_cmd_storage[ 0 ].tester;
 *timeout = at_cmd_storage[ 0 ].timeout;
 return;
 }

 if( !( cmd_idx = _parse_find( cmd_temp ) ) )
 {
 *cb = at_cmd_storage[ 0 ].tester;
 *timeout = at_cmd_storage[ 0 ].timeout;
 return;
 }

 switch ( cmd_type )
 {
 case AT_CMD_SET :
 *cb = at_cmd_storage[ cmd_idx ].setter;
 *timeout = at_cmd_storage[ cmd_idx ].timeout;
 break;
 case AT_CMD_GET :
 *cb = at_cmd_storage[ cmd_idx ].getter;
 *timeout = at_cmd_storage[ cmd_idx ].timeout;
 break;
 case AT_CMD_TEST :
 *cb = at_cmd_storage[ cmd_idx ].tester;
 *timeout = at_cmd_storage[ cmd_idx ].timeout;
 break;
 case AT_CMD_EXEC :
 *cb = at_cmd_storage[ cmd_idx ].executer;
 *timeout = at_cmd_storage[ cmd_idx ].timeout;
 break;
 case AT_CMD_UNKNOWN :
 *cb = at_cmd_storage[ 0 ].executer;
 *timeout = at_cmd_storage[ 0 ].timeout;
 break;
 }
 return;
}
#line 487 "C:/Users/richard/Desktop/WORKDIR/Skywire/example/ARM/at_engine/at_engine.c"
void at_init
(
 at_cmd_cb default_callback,
 at_write_p default_write,
 uint8_t *buffer_ptr,
 uint16_t buffer_size
)
{
 at_cmd_t cmd;

 cb_default = default_callback;
 write_uart_p = default_write;
  { t_response_l = 0; t_response_c = 0; t_char_l = 50; t_char_c = 0; tmp_cnt = 0; t_response_f = 0 ; t_char_f = 0 ; response_f = 0 ; no_response_f = 0 ; cue_f = 0 ; } ;
  { p_rx_buf = (buffer_ptr); rx_max = (buffer_size); rx_idx = 0; memset( ( void* )p_rx_buf, 0, rx_max ); } ;
  { at_cmd_storage_used = 0; for( tmp_cnt = 0; tmp_cnt < 50 ; tmp_cnt++ ) { at_cmd_storage[ tmp_cnt ].hash = 0; at_cmd_storage[ tmp_cnt ].timeout = 0; at_cmd_storage[ tmp_cnt ].getter = ((void *)0) ; at_cmd_storage[ tmp_cnt ].setter = ((void *)0) ; at_cmd_storage[ tmp_cnt ].tester = ((void *)0) ; at_cmd_storage[ tmp_cnt ].executer = ((void *)0) ; }} ;
 cmd.hash = _parse_hash( "" );
 cmd.timeout =  500 ;
 cmd.getter = default_callback;
 cmd.setter = default_callback;
 cmd.tester = default_callback;
 cmd.executer = default_callback;
 at_cmd_storage[ at_cmd_storage_used ] = cmd;
 at_cmd_storage_used++;
}

void at_rx( char rx_input )
{
  { no_response_f = 0 ; response_f = 0 ; cue_f = 1 ; } ;
  { t_char_c = 0; t_char_f = 1 ; } ;
 *( p_rx_buf + rx_idx++ ) = rx_input;
}

void at_tick( void )
{
 if( t_response_f )
 if( t_response_c++ > t_response_l )
 {
 t_response_f =  0 ;
 t_response_c = 0;
 *( p_rx_buf + rx_idx ) = 0;
 no_response_f =  1 ;
 }

 if( t_char_f )
 if( t_char_c++ > t_char_l )
 {
 t_char_f =  0 ;
 t_char_c = 0;
 *( p_rx_buf + rx_idx ) = 0;
 response_f =  1 ;
 }
}

void at_cmd_save( char *cmd, uint32_t timeout,
 at_cmd_cb getter, at_cmd_cb setter,
 at_cmd_cb tester, at_cmd_cb executer )
{
 if( !setter ) setter = cb_default;
 if( !getter ) getter = cb_default;
 if( !tester ) tester = cb_default;
 if( !executer ) executer = cb_default;
 if( !timeout ) timeout =  500 ;
 _parse_save( cmd, timeout, getter, setter, tester, executer );
}

void at_cmd_single( char *cmd )
{
 char* tmp = cmd;

  { while( cue_f ) at_process(); } ;
 _parse_exe( tmp, &tmp_cb, &tmp_timer );
 _tx( tmp,  0x0D  );
  { no_response_f = 0 ; response_f = 0 ; cue_f = 1 ; } ;
  { t_response_l = tmp_timer; t_response_c = 0; t_response_f = 1 ; } ;
}

void at_cmd_double( char *cmd, char *arg_1 )
{
 char *tmp = cmd;
 char *tmp_a1 = arg_1;

  { while( cue_f ) at_process(); } ;
 _parse_exe( tmp, &tmp_cb, &tmp_timer );
 _tx( tmp,  0x0D  );
  { no_response_f = 0 ; response_f = 0 ; cue_f = 1 ; } ;
  { t_response_l = tmp_timer; t_response_c = 0; t_response_f = 1 ; } ;
  { while( cue_f ) at_process(); } ;
  { t_response_f = 0 ; } ;
 _tx( tmp_a1,  0x1A  );
  { no_response_f = 0 ; response_f = 0 ; cue_f = 1 ; } ;
  { t_response_l = tmp_timer; t_response_c = 0; t_response_f = 1 ; } ;
}

void at_cmd_triple( char *cmd, char *arg_1, char *arg_2 )
{
 char *tmp = cmd;
 char *tmp_a1 = arg_1;
 char *tmp_a2 = arg_2;

  { while( cue_f ) at_process(); } ;
 _parse_exe( tmp, &tmp_cb, &tmp_timer );
 _tx( tmp,  0x0D  );
  { no_response_f = 0 ; response_f = 0 ; cue_f = 1 ; } ;
  { t_response_l = tmp_timer; t_response_c = 0; t_response_f = 1 ; } ;
  { while( cue_f ) at_process(); } ;
  { t_response_f = 0 ; } ;
 _tx( tmp_a1,  0x1A  );
  { no_response_f = 0 ; response_f = 0 ; cue_f = 1 ; } ;
  { t_response_l = tmp_timer; t_response_c = 0; t_response_f = 1 ; } ;
  { while( cue_f ) at_process(); } ;
  { t_response_f = 0 ; } ;
 _tx( tmp_a2,  0x1A  );
  { no_response_f = 0 ; response_f = 0 ; cue_f = 1 ; } ;
  { t_response_l = tmp_timer; t_response_c = 0; t_response_f = 1 ; } ;
}

void at_process( void )
{
#line 611 "C:/Users/richard/Desktop/WORKDIR/Skywire/example/ARM/at_engine/at_engine.c"
 if( response_f )
 {
#line 618 "C:/Users/richard/Desktop/WORKDIR/Skywire/example/ARM/at_engine/at_engine.c"
  { t_char_f = 0 ; } ;
  { t_response_f = 0 ; } ;
 _parse_exe( p_rx_buf, &cb, &tmp_timer );
 cb( p_rx_buf );
  { rx_idx = 0; *p_rx_buf = 0; } ;
  { no_response_f = 0 ; response_f = 0 ; cue_f = 0 ; } ;
 }

 if( no_response_f )
 {
#line 633 "C:/Users/richard/Desktop/WORKDIR/Skywire/example/ARM/at_engine/at_engine.c"
  { t_char_f = 0 ; } ;
  { t_response_f = 0 ; } ;
 _parse_exe( p_rx_buf, &cb, &tmp_timer );
 cb( p_rx_buf );
  { rx_idx = 0; *p_rx_buf = 0; } ;
  { no_response_f = 0 ; response_f = 0 ; cue_f = 0 ; } ;
 }
}

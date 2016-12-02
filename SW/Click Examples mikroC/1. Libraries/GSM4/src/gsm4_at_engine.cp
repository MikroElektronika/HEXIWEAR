#line 1 "C:/Users/richard/Desktop/GSM4/library/src/gsm4_at_engine.c"
#line 1 "c:/users/richard/desktop/gsm4/library/include/gsm4_at_engine.h"
#line 1 "c:/users/richard/desktop/gsm4/library/include/gsm4_config.h"
#line 1 "c:/c4w/mikroelektronika/mikroc pro for ft90x/include/stdint.h"





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
#line 1 "c:/c4w/mikroelektronika/mikroc pro for ft90x/include/stddef.h"



typedef long ptrdiff_t;


 typedef unsigned long size_t;

typedef unsigned long wchar_t;
#line 1 "c:/c4w/mikroelektronika/mikroc pro for ft90x/include/string.h"





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
#line 1 "c:/c4w/mikroelektronika/mikroc pro for ft90x/include/stdbool.h"



 typedef char _Bool;
#line 62 "c:/users/richard/desktop/gsm4/library/include/gsm4_config.h"
typedef enum
{
 AT_OK,
 AT_ERROR,
 AT_UNKNOWN

}at_t;

typedef void ( *at_cmd_cb )( char *buffer );
#line 1 "c:/users/richard/desktop/gsm4/library/include/gsm4_at_parser.h"
#line 1 "c:/users/richard/desktop/gsm4/library/include/gsm4_config.h"
#line 26 "c:/users/richard/desktop/gsm4/library/include/gsm4_at_parser.h"
typedef enum
{
#line 30 "c:/users/richard/desktop/gsm4/library/include/gsm4_at_parser.h"
 AT_CMD_UNKNOWN = 0,
#line 33 "c:/users/richard/desktop/gsm4/library/include/gsm4_at_parser.h"
 AT_CMD_GET = 1,
#line 36 "c:/users/richard/desktop/gsm4/library/include/gsm4_at_parser.h"
 AT_CMD_SET = 2,
#line 39 "c:/users/richard/desktop/gsm4/library/include/gsm4_at_parser.h"
 AT_CMD_TEST = 3,
#line 42 "c:/users/richard/desktop/gsm4/library/include/gsm4_at_parser.h"
 AT_CMD_EXEC = 4,

}at_type_t;
#line 54 "c:/users/richard/desktop/gsm4/library/include/gsm4_at_parser.h"
typedef struct
{
#line 58 "c:/users/richard/desktop/gsm4/library/include/gsm4_at_parser.h"
 uint32_t hash;
#line 61 "c:/users/richard/desktop/gsm4/library/include/gsm4_at_parser.h"
 uint32_t timeout;
#line 64 "c:/users/richard/desktop/gsm4/library/include/gsm4_at_parser.h"
 at_cmd_cb getter;
#line 67 "c:/users/richard/desktop/gsm4/library/include/gsm4_at_parser.h"
 at_cmd_cb setter;
#line 70 "c:/users/richard/desktop/gsm4/library/include/gsm4_at_parser.h"
 at_cmd_cb tester;
#line 73 "c:/users/richard/desktop/gsm4/library/include/gsm4_at_parser.h"
 at_cmd_cb executer;

}at_cmd_t;
#line 90 "c:/users/richard/desktop/gsm4/library/include/gsm4_at_parser.h"
void at_parser_init
(
 void
);
#line 108 "c:/users/richard/desktop/gsm4/library/include/gsm4_at_parser.h"
void at_parser_store
(
 char *command,
 uint32_t timeout,
 at_cmd_cb getter,
 at_cmd_cb setter,
 at_cmd_cb tester,
 at_cmd_cb execute
);
#line 128 "c:/users/richard/desktop/gsm4/library/include/gsm4_at_parser.h"
void at_parse
(
 char *input,
 at_cmd_cb *cb,
 uint32_t *timeout
);
#line 1 "c:/users/richard/desktop/gsm4/library/include/gsm4_dev_timer.h"
#line 1 "c:/users/richard/desktop/gsm4/library/include/gsm4_config.h"
#line 23 "c:/users/richard/desktop/gsm4/library/include/gsm4_dev_timer.h"
extern volatile  _Bool  timeout_f;
#line 39 "c:/users/richard/desktop/gsm4/library/include/gsm4_dev_timer.h"
void dev_timer_init
(
 void
);
#line 51 "c:/users/richard/desktop/gsm4/library/include/gsm4_dev_timer.h"
void dev_tick_isr
(
 void
);
#line 62 "c:/users/richard/desktop/gsm4/library/include/gsm4_dev_timer.h"
void dev_timer_start
(
 void
);
#line 73 "c:/users/richard/desktop/gsm4/library/include/gsm4_dev_timer.h"
void dev_timer_restart
(
 void
);
#line 84 "c:/users/richard/desktop/gsm4/library/include/gsm4_dev_timer.h"
void dev_timer_stop
(
 void
);
#line 97 "c:/users/richard/desktop/gsm4/library/include/gsm4_dev_timer.h"
void dev_timer_load
(
 uint32_t timeout
);
#line 1 "c:/users/richard/desktop/gsm4/library/include/gsm4_dev_adapter.h"
#line 1 "c:/users/richard/desktop/gsm4/library/include/gsm4_config.h"
#line 1 "c:/users/richard/desktop/gsm4/library/include/gsm4_dev_hal.h"
#line 1 "c:/c4w/mikroelektronika/mikroc pro for ft90x/include/stdint.h"
#line 1 "c:/c4w/mikroelektronika/mikroc pro for ft90x/include/stdbool.h"
#line 1 "c:/c4w/mikroelektronika/mikroc pro for ft90x/include/stddef.h"
#line 37 "c:/users/richard/desktop/gsm4/library/include/gsm4_dev_hal.h"
void dev_hal_pwr_ctl
(
  _Bool  state
);
#line 50 "c:/users/richard/desktop/gsm4/library/include/gsm4_dev_hal.h"
 _Bool  dev_hal_rts_ctl
(
 void
);
#line 63 "c:/users/richard/desktop/gsm4/library/include/gsm4_dev_hal.h"
void dev_hal_cts_ctl
(
  _Bool  state
);
#line 74 "c:/users/richard/desktop/gsm4/library/include/gsm4_dev_hal.h"
void dev_hal_init
(
 void
);
#line 87 "c:/users/richard/desktop/gsm4/library/include/gsm4_dev_hal.h"
void dev_hal_write( char ch );
#line 24 "c:/users/richard/desktop/gsm4/library/include/gsm4_dev_adapter.h"
extern volatile  _Bool  exception_f;
extern volatile  _Bool  response_f;
extern volatile  _Bool  cue_f;

extern volatile char tx_buffer[  256  ];
extern volatile char rx_buffer[  256  ];
#line 42 "c:/users/richard/desktop/gsm4/library/include/gsm4_dev_adapter.h"
void dev_adapter_init
(
 void
);
#line 50 "c:/users/richard/desktop/gsm4/library/include/gsm4_dev_adapter.h"
void dev_adapter_reset
(
 void
);
#line 60 "c:/users/richard/desktop/gsm4/library/include/gsm4_dev_adapter.h"
int dev_tx
(
 char tx_input
);
#line 72 "c:/users/richard/desktop/gsm4/library/include/gsm4_dev_adapter.h"
void dev_rx
(
 char rx_input
);
#line 36 "c:/users/richard/desktop/gsm4/library/include/gsm4_at_engine.h"
void engine_init( at_cmd_cb default_callback );
#line 46 "c:/users/richard/desktop/gsm4/library/include/gsm4_at_engine.h"
void at_cmd( char *input );
#line 57 "c:/users/richard/desktop/gsm4/library/include/gsm4_at_engine.h"
void at_cmd_addition( char *input );
#line 73 "c:/users/richard/desktop/gsm4/library/include/gsm4_at_engine.h"
void at_cmd_save
(
 char *cmd,
 uint32_t timeout,
 at_cmd_cb getter,
 at_cmd_cb setter,
 at_cmd_cb tester,
 at_cmd_cb executer
);
#line 88 "c:/users/richard/desktop/gsm4/library/include/gsm4_at_engine.h"
void at_process( void );
#line 21 "C:/Users/richard/Desktop/GSM4/library/src/gsm4_at_engine.c"
static uint32_t temp_timer;
static at_cmd_cb temp_cb;


volatile  _Bool  timeout_f;
volatile  _Bool  exception_f;
volatile  _Bool  response_f;
volatile  _Bool  cue_f;


static volatile at_cmd_cb cb;
static volatile at_cmd_cb cb_default;


volatile char tx_buffer[  256  ];
volatile char rx_buffer[  256  ];
#line 42 "C:/Users/richard/Desktop/GSM4/library/src/gsm4_at_engine.c"
void engine_init( at_cmd_cb default_callback )
{
 cb_default = default_callback;

 dev_adapter_init();
 dev_timer_init();
 at_parser_init();

 at_cmd_save( "+CMS ERROR :",  500 , default_callback,
 default_callback,
 default_callback,
 default_callback );

 exception_f =  0 ;
 response_f =  0 ;
 cue_f =  0 ;

 memset( ( void* )tx_buffer, 0,  256  );
}

void at_cmd( char *input )
{
 char* temp_input = input;

 Delay_ms( 100 );
 at_parse( temp_input, &temp_cb, &temp_timer );
 dev_timer_load( temp_timer );

 while( cue_f )
 at_process();

 while( !dev_tx( *( temp_input++ ) ) );

 dev_adapter_reset();
 dev_timer_start();
}

void at_cmd_addition( char *input )
{
 char* temp_input = input;

 Delay_ms( 100 );
 while( !exception_f )
 at_process();

 dev_timer_stop();

 while( !dev_tx( *( temp_input++ ) ) );

 dev_adapter_reset();
 dev_timer_restart();
}

void at_cmd_save
(
 char *cmd,
 uint32_t timeout,
 at_cmd_cb getter,
 at_cmd_cb setter,
 at_cmd_cb tester,
 at_cmd_cb executer
)
{
 if ( !setter )
 setter = cb_default;

 if( !getter )
 getter = cb_default;

 if( !tester )
 tester = cb_default;

 if( !executer )
 executer = cb_default;

 if( !timeout )
 timeout =  500 ;

 at_parser_store( cmd, timeout, getter, setter, tester, executer );
}

void at_process( void )
{
 if( response_f )
 {
 dev_hal_cts_ctl(  0  );
 dev_timer_stop();
 at_parse( rx_buffer, &cb, &temp_timer );
 cb( rx_buffer );
 dev_adapter_reset();

 timeout_f =  0 ;
 exception_f =  0 ;
 response_f =  0 ;
 cue_f =  0 ;
 }

 if( timeout_f )
 {
 dev_hal_cts_ctl(  0  );
 dev_timer_stop();
 at_parse( rx_buffer, &cb, &temp_timer );
 cb( rx_buffer );
 dev_adapter_reset();

 timeout_f =  0 ;
 exception_f =  0 ;
 response_f =  1 ;
 cue_f =  0 ;
 }
}

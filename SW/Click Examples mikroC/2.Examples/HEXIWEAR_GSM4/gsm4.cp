#line 1 "//VBOXSVR/storage/git/ClickLab/GSM4/example/Hexiwear/gsm4.c"
#line 1 "//vboxsvr/storage/git/clicklab/gsm4/example/hexiwear/gsm4.h"
#line 1 "//vboxsvr/storage/git/clicklab/gsm4/library/include/at_engine.h"
#line 1 "//vboxsvr/storage/git/clicklab/gsm4/library/include/config.h"
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
#line 3 "//VBOXSVR/storage/git/ClickLab/GSM4/example/Hexiwear/gsm4.c"
extern  _Bool  req_pend_f;
extern  _Bool  ring_f;

static char tmp_num[ 20 ] = { 0 };

void gsm4_init( void )
{
 engine_init( gsm4_evn_default );





 at_cmd_save( "RING", 1000,  ((void *)0) ,  ((void *)0) ,  ((void *)0) , gsm4_ev_ring );

 at_cmd( "AT" );
 at_cmd( "AT+CSCS=\"GSM\"" );
 at_cmd( "AT+CMGF=1" );
}

void gsm4_evn_default( char *response )
{
 UART3_Write_Text( response );
}

void gsm4_ev_ring( char *response )
{
 ring_f =  1 ;
}

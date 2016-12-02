#line 1 "C:/Users/richard/Desktop/GSM4/library/src/gsm4_dev_adapter.c"
#line 1 "c:/users/richard/desktop/gsm4/library/include/gsm4_dev_adapter.h"
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
#line 1 "c:/users/richard/desktop/gsm4/library/include/gsm4_dev_hal.h"
#line 21 "C:/Users/richard/Desktop/GSM4/library/src/gsm4_dev_adapter.c"
static volatile uint16_t rx_idx;
static volatile uint16_t tx_idx;


static volatile  _Bool  head_f;
static volatile  _Bool  data_f;
static volatile  _Bool  summ_f;


static volatile  _Bool  head_t;
static volatile  _Bool  data_t;
static volatile  _Bool  summ_t;


static volatile  _Bool  term_f;
static volatile  _Bool  frag_f;


static volatile uint8_t err_c;
static volatile  _Bool  err_f;
static char* data_ptr;
static char error[  15  ];
#line 48 "C:/Users/richard/Desktop/GSM4/library/src/gsm4_dev_adapter.c"
void dev_adapter_init
(
 void
)
{
 dev_hal_init();
 dev_adapter_reset();

 err_c = 0;
 err_f =  0 ;

 strcpy( error, ( char* ) "+CMS ERROR:"  );

 memset( ( void* )tx_buffer, 0,  256  );
 memset( ( void* )rx_buffer, 0,  256  );
}

void dev_adapter_reset
(
 void
)
{
 rx_idx = 0;

 term_f =  0 ;
 frag_f =  0 ;

 head_f =  0 ;
 data_f =  0 ;
 summ_f =  0 ;

 head_t =  0 ;
 data_t =  0 ;
 summ_t =  0 ;

 dev_hal_cts_ctl(  1  );
}

int dev_tx
(
 char tx_input
)
{
 if( tx_input != '\0' )
 {
 tx_buffer[ tx_idx++ ] = tx_input;

 }
 else {

 if( !exception_f )
 {
 tx_buffer[ tx_idx++ ] = '\r';
 tx_buffer[ tx_idx++ ] = '\n';
 tx_buffer[ tx_idx ] = '\0';
 }
 else {

 tx_buffer[ tx_idx++ ] = 0x1A;
 tx_buffer[ tx_idx++ ] = '\r';
 tx_buffer[ tx_idx ] = '\0';
 }

 tx_idx = 0;

 while( tx_buffer[ tx_idx ] )
 {



 char tmp = tx_buffer[ tx_idx ];
 dev_hal_write( tmp );
 tx_idx++;
 };

 tx_idx = 0;

 exception_f =  0 ;
 response_f =  0 ;
 cue_f =  1 ;

 return 1;
 }

 if ( tx_idx ==  256  )
 {
 tx_buffer[ tx_idx ] = '\0';

 tx_idx = 0;

 while( tx_buffer[ tx_idx ] )
 {



 char tmp = tx_buffer[ tx_idx ];
 dev_hal_write( tmp );
 tx_idx++;
 };

 tx_idx = 0;

 return 0;
 }

 return 0;
}

void dev_rx
(
 char rx_input
)
{
 if( rx_input == '\r' )
 term_f =  1 ;

 if( rx_input == '\n' && term_f )
 {
 term_f =  0 ;
 frag_f =  1 ;
 }

 if( !frag_f )
 {
 if( !head_f && !data_f && !summ_f )
 {
 if( rx_input == 'A' ) {

 head_f =  1 ;

 } else if( rx_input == 'O' || rx_input == 'E' ||
 rx_input == 'B' || rx_input == 'C' ||
 rx_input == 'R' || rx_input == 'N' || rx_input == 'P' ) {

 summ_f =  1 ;

 } else if ( rx_input == '+' || data_t ) {

 data_f =  1 ;
 }
 }

 if( rx_input == '>' )
 {
 exception_f =  1 ;
 }
 }

 if( head_f )
 {
 if( !head_t )
 head_t =  1 ;

 rx_buffer[ rx_idx++ ] = rx_input;
 }

 if( data_f )
 {
 if( !data_t )
 {
 data_t =  1 ;
 data_ptr = &rx_buffer[ rx_idx ];
 }

 rx_buffer[ rx_idx++ ] = rx_input;
 }

 if( summ_f )
 {
 if( !summ_t )
 summ_t =  1 ;

 rx_buffer[ rx_idx++ ] = rx_input;
 }

 if( frag_f )
 {
 if( head_f )
 head_f =  0 ;

 if( data_f )
 {
 while ( *error )
 {
 if( error[ err_c ] == *( data_ptr + err_c++ ) )
 {
 err_f =  1 ;

 } else {

 err_f =  0 ;
 break;
 }
 }

 if( err_f )
 {

 rx_buffer[ rx_idx ] = '\0';
 response_f =  1 ;
 }

 if( !head_t )
 {

 rx_buffer[ rx_idx ] = '\0';
 response_f =  1 ;
 }

 err_c = 0;
 data_f =  0 ;
 }

 if( summ_f )
 {

 rx_buffer[ rx_idx ] = '\0';
 response_f =  1 ;
 }

 frag_f =  0 ;
 }

 if( rx_idx ==  256  )
 {

 rx_buffer[ rx_idx ] = '\0';
 response_f =  1 ;
 }
}

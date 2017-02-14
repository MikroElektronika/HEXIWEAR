#line 1 "E:/Skywire/SARA_HEXIWEAR.c"
#line 1 "e:/skywire/at_engine/at_engine.h"
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
#line 23 "e:/skywire/at_engine/at_engine.h"
typedef void ( *at_cmd_cb )( char *buffer );
#line 28 "e:/skywire/at_engine/at_engine.h"
typedef void ( *at_write_p )( unsigned int in );
#line 40 "e:/skywire/at_engine/at_engine.h"
typedef enum
{
#line 44 "e:/skywire/at_engine/at_engine.h"
 AT_CMD_UNKNOWN = 0,
#line 47 "e:/skywire/at_engine/at_engine.h"
 AT_CMD_GET = 1,
#line 50 "e:/skywire/at_engine/at_engine.h"
 AT_CMD_SET = 2,
#line 53 "e:/skywire/at_engine/at_engine.h"
 AT_CMD_TEST = 3,
#line 56 "e:/skywire/at_engine/at_engine.h"
 AT_CMD_EXEC = 4,

}at_type_t;
#line 68 "e:/skywire/at_engine/at_engine.h"
typedef struct
{
#line 72 "e:/skywire/at_engine/at_engine.h"
 uint32_t hash;
#line 75 "e:/skywire/at_engine/at_engine.h"
 uint32_t timeout;
#line 78 "e:/skywire/at_engine/at_engine.h"
 at_cmd_cb getter;
#line 81 "e:/skywire/at_engine/at_engine.h"
 at_cmd_cb setter;
#line 84 "e:/skywire/at_engine/at_engine.h"
 at_cmd_cb tester;
#line 87 "e:/skywire/at_engine/at_engine.h"
 at_cmd_cb executer;

}at_cmd_t;
#line 107 "e:/skywire/at_engine/at_engine.h"
void at_init( at_cmd_cb default_callback, at_write_p default_write,
 uint8_t *buffer_ptr, uint16_t buffer_size );
#line 119 "e:/skywire/at_engine/at_engine.h"
void at_rx( char rx_input );
#line 127 "e:/skywire/at_engine/at_engine.h"
void at_tick( void );
#line 137 "e:/skywire/at_engine/at_engine.h"
void at_cmd_single( char *cmd );
#line 149 "e:/skywire/at_engine/at_engine.h"
void at_cmd_double( char *cmd, char *arg_1 );
#line 162 "e:/skywire/at_engine/at_engine.h"
void at_cmd_triple( char *cmd, char *arg_1, char *arg_2 );
#line 178 "e:/skywire/at_engine/at_engine.h"
void at_cmd_save( char *cmd, uint32_t timeout,
 at_cmd_cb getter, at_cmd_cb setter,
 at_cmd_cb tester, at_cmd_cb executer );
#line 187 "e:/skywire/at_engine/at_engine.h"
void at_process( void );
#line 21 "E:/Skywire/SARA_HEXIWEAR.c"
sbit SARA_PWR at PTB_PDOR.B11;
sbit SARA_STAT at PTB_PDIR.B2;


sbit SARA_RING at PTA_PDIR.B10;
#line 30 "E:/Skywire/SARA_HEXIWEAR.c"
 _Bool  measure_f;
#line 35 "E:/Skywire/SARA_HEXIWEAR.c"
uint8_t buffer[ 1024 ] = { 0 };
#line 40 "E:/Skywire/SARA_HEXIWEAR.c"
char caller_id[ 20 ] = { 0 };
#line 45 "E:/Skywire/SARA_HEXIWEAR.c"
float temperature = 0.0F;
#line 57 "E:/Skywire/SARA_HEXIWEAR.c"
static void system_init( void )
{
 GPIO_Digital_Output( &PTB_PDOR, _GPIO_PINMASK_11 | _GPIO_PINMASK_2 );
 UART2_Init_Advanced( 115200, _UART_8_BIT_DATA, _UART_NOPARITY,
 _UART_ONE_STOPBIT, &_GPIO_Module_UART2_PD3_2 );
 UART3_Init_Advanced( 115200, _UART_8_BIT_DATA, _UART_NOPARITY,
 _UART_ONE_STOPBIT, &_GPIO_Module_UART3_PC16_17 );

 SIM_SCGC6 |= ( 1 << PIT );
 PIT_MCR = 0x00;
 PIT_LDVAL0 = 59999;
 PIT_TCTRL0 |= 2;
 PIT_TCTRL0 |= 1;
 UART2_C2 |= 1 << 5;
 NVIC_IntEnable(IVT_INT_PIT0);
 NVIC_IntEnable( IVT_INT_UART2_RX_TX );
 EnableInterrupts();
  UART3_Write_Text("\r\n_______________________________\r\n System Initialized\r\n") ;
}
#line 80 "E:/Skywire/SARA_HEXIWEAR.c"
void sara_power_on( void )
{
 SARA_PWR = 0;
 Delay_ms( 50 );
 SARA_PWR = 1;
 Delay_ms( 50 );
 SARA_PWR = 0;
 Delay_ms( 10000 );
}
#line 93 "E:/Skywire/SARA_HEXIWEAR.c"
void rsp_handler( char *rsp )
{
 char tmp[ 25 ] = { 0 };

  UART3_Write_Text("Response : \r\n") ;
  UART3_Write_Text(rsp) ;
  UART3_Write_Text("\r\n") ;
 if( !strncmp( "\r\nRING", rsp, 6 ) )
 measure_f =  1 ;
}
#line 107 "E:/Skywire/SARA_HEXIWEAR.c"
void callerid_handler( char *rsp )
{
 char *tmp_s;
 char *tmp_e;

 tmp_s = strchr( rsp, '\"' );
 tmp_e = strchr( tmp_s + 1, '\"' );
 strncpy( caller_id, tmp_s, tmp_e - tmp_s + 1 );
}
#line 120 "E:/Skywire/SARA_HEXIWEAR.c"
void reply_to_caller( void )
{
 char tmp[ 30 ] = { 0 };
 char cmd_content[ 30 ] = { 0 };
 char reply_content[ 256 ] = { 0 };

 strcat( cmd_content, "AT+CMGS=" );
 strcat( cmd_content, caller_id );
 strcat( reply_content, "Hello it's me HEXIWEAR :)" );
 at_cmd_double( cmd_content, reply_content );
}


void main()
{
 measure_f =  0 ;
 system_init();
 sara_power_on();
 at_init( rsp_handler, UART2_Write, buffer, sizeof( buffer ) );
 at_cmd_save( "+CLCC", 1000,  ((void *)0) ,  ((void *)0) ,  ((void *)0) , callerid_handler );
 at_cmd_single( "AT" );
 at_cmd_single( "AT+CSCS=\"GSM\"" );
 at_cmd_single( "AT+CMGF=1" );

 while( 1 )
 {
 at_process();

 if( measure_f )
 {
 at_cmd_single( "AT+CLCC" );
 at_cmd_single( "ATH" );
 Delay_ms( 3000 );
 reply_to_caller();
 measure_f =  0 ;
 }
 }
}
#line 162 "E:/Skywire/SARA_HEXIWEAR.c"
void Timer0_interrupt() iv IVT_INT_PIT0
{
 PIT_TFLG0.TIF = 1;
 at_tick();
}
#line 171 "E:/Skywire/SARA_HEXIWEAR.c"
void UART2_RX_ISR() iv IVT_INT_UART2_RX_TX ics ICS_OFF
{
 char foo = UART2_S1;
 char tmp = UART2_D;

 if( foo & ( 1 << 5 ) )
 at_rx( tmp );
}

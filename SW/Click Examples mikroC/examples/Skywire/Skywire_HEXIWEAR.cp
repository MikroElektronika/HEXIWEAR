#line 1 "C:/Users/richard/Desktop/WORKDIR/Skywire/example/ARM/Skywire_HEXIWEAR.c"
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
#line 21 "C:/Users/richard/Desktop/WORKDIR/Skywire/example/ARM/Skywire_HEXIWEAR.c"
sbit SKYWIRE_EN at PTB_PDOR.B2;
sbit SKYWIRE_RST at PTB_PDOR.B11;
#line 27 "C:/Users/richard/Desktop/WORKDIR/Skywire/example/ARM/Skywire_HEXIWEAR.c"
 _Bool  measure_f;
#line 32 "C:/Users/richard/Desktop/WORKDIR/Skywire/example/ARM/Skywire_HEXIWEAR.c"
uint8_t buffer[ 1024 ] = { 0 };
#line 37 "C:/Users/richard/Desktop/WORKDIR/Skywire/example/ARM/Skywire_HEXIWEAR.c"
char caller_id[ 20 ] = { 0 };
#line 42 "C:/Users/richard/Desktop/WORKDIR/Skywire/example/ARM/Skywire_HEXIWEAR.c"
float temperature = 0.0F;
#line 57 "C:/Users/richard/Desktop/WORKDIR/Skywire/example/ARM/Skywire_HEXIWEAR.c"
static void system_init( void )
{
 GPIO_Digital_Output( &PTB_PDOR, _GPIO_PINMASK_11 | _GPIO_PINMASK_2 );
 UART2_Init_Advanced( 115200, _UART_8_BIT_DATA, _UART_NOPARITY,
 _UART_ONE_STOPBIT, &_GPIO_Module_UART2_PD3_2 );
 UART3_Init_Advanced( 115200, _UART_8_BIT_DATA, _UART_NOPARITY,
 _UART_ONE_STOPBIT, &_GPIO_Module_UART3_PC16_17 );
 I2C0_Init_Advanced( 400000, &_GPIO_Module_I2C0_PD8_9 );

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
#line 81 "C:/Users/richard/Desktop/WORKDIR/Skywire/example/ARM/Skywire_HEXIWEAR.c"
static void skywire_power_on( void )
{
 SKYWIRE_EN = 0;
 Delay_ms( 5000 );
 SKYWIRE_EN = 1;
 Delay_ms( 3000 );
  UART3_Write_Text("\r\nSkywire Initialized\r\n") ;
}
#line 94 "C:/Users/richard/Desktop/WORKDIR/Skywire/example/ARM/Skywire_HEXIWEAR.c"
void rsp_handler( char *rsp )
{
 char tmp[ 25 ] = { 0 };

  UART3_Write_Text("Response : \r\n") ;
  UART3_Write_Text(rsp) ;
  UART3_Write_Text("\r\n") ;
 if( !strncmp( "\r\nRING", rsp, 6 ) )
 measure_f =  1 ;
}
#line 108 "C:/Users/richard/Desktop/WORKDIR/Skywire/example/ARM/Skywire_HEXIWEAR.c"
void callerid_handler( char *rsp )
{
 char *tmp_s;
 char *tmp_e;

 tmp_s = strchr( rsp, '\"' );
 tmp_e = strchr( tmp_s + 1, '\"' );
 strncpy( caller_id, tmp_s, tmp_e - tmp_s + 1 );
}
#line 121 "C:/Users/richard/Desktop/WORKDIR/Skywire/example/ARM/Skywire_HEXIWEAR.c"
void measure_temp( void )
{
 int raw_temp;
 uint8_t tmp_data[ 2 ] = { 0x00 };

 I2C_Start();
 I2C_Write( 0x48, tmp_data, 1, END_MODE_RESTART );
 I2C_Read( 0x48, tmp_data, 2, END_MODE_STOP );
 raw_temp = ( ( tmp_data[ 0 ] << 8 ) | tmp_data[ 1 ] ) >> 4;

 if( raw_temp & ( 1 << 11 ) )
 raw_temp |= 0xF800;

 temperature = ( float )( raw_temp * 0.0625 );
}
#line 140 "C:/Users/richard/Desktop/WORKDIR/Skywire/example/ARM/Skywire_HEXIWEAR.c"
void reply_to_caller( void )
{
 char tmp[ 30 ] = { 0 };
 char cmd_content[ 30 ] = { 0 };
 char reply_content[ 256 ] = { 0 };

 strcat( cmd_content, "AT+CMGS=" );
 strcat( cmd_content, caller_id );
 strcat( reply_content, "Temperature : " );
 FloatToStr( temperature, tmp );
 strcat( reply_content, Ltrim( tmp ) );
 strcat( reply_content, " C" );
 at_cmd_double( cmd_content, reply_content );
}


void main()
{
 measure_f =  0 ;
 system_init();
 skywire_power_on();
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
 measure_temp();
 at_cmd_single( "AT+CLCC" );
 at_cmd_single( "ATH" );
 Delay_ms( 2000 );
 reply_to_caller();
 measure_f =  0 ;
 }
 }
}
#line 186 "C:/Users/richard/Desktop/WORKDIR/Skywire/example/ARM/Skywire_HEXIWEAR.c"
void Timer0_interrupt() iv IVT_INT_PIT0
{
 PIT_TFLG0.TIF = 1;
 at_tick();
}
#line 195 "C:/Users/richard/Desktop/WORKDIR/Skywire/example/ARM/Skywire_HEXIWEAR.c"
void UART2_RX_ISR() iv IVT_INT_UART2_RX_TX ics ICS_OFF
{
 char foo = UART2_S1;
 char tmp = UART2_D;

 if( foo & ( 1 << 5 ) )
 at_rx( tmp );
}

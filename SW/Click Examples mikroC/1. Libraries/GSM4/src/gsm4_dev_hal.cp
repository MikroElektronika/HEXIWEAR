#line 1 "C:/Users/richard/Desktop/GSM4/library/src/gsm4_dev_hal.c"
#line 1 "c:/users/richard/desktop/gsm4/library/include/gsm4_dev_hal.h"
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
#line 1 "c:/c4w/mikroelektronika/mikroc pro for ft90x/include/stdbool.h"



 typedef char _Bool;
#line 1 "c:/c4w/mikroelektronika/mikroc pro for ft90x/include/stddef.h"



typedef long ptrdiff_t;


 typedef unsigned long size_t;

typedef unsigned long wchar_t;
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
#line 29 "C:/Users/richard/Desktop/GSM4/library/src/gsm4_dev_hal.c"
static void ( *write_uart_p ) ( unsigned char data_out );
#line 39 "C:/Users/richard/Desktop/GSM4/library/src/gsm4_dev_hal.c"
extern sfr sbit GSM_PWR;
extern sfr sbit GSM_RTS;
extern sfr sbit GSM_CTS;
#line 48 "C:/Users/richard/Desktop/GSM4/library/src/gsm4_dev_hal.c"
void dev_hal_pwr_ctl(  _Bool  state )
{
#line 57 "C:/Users/richard/Desktop/GSM4/library/src/gsm4_dev_hal.c"
 if ( state )
 GSM_PWR = 1;
 else
 GSM_PWR = 0;

}

 _Bool  dev_hal_rts_ctl()
{
#line 73 "C:/Users/richard/Desktop/GSM4/library/src/gsm4_dev_hal.c"
 if( GSM_CTS )
 return  0 ;
 else
 return  1 ;

 return  1 ;
}

void dev_hal_cts_ctl(  _Bool  state )
{
#line 90 "C:/Users/richard/Desktop/GSM4/library/src/gsm4_dev_hal.c"
 if( state )
 GSM_RTS = 0;
 else
 GSM_RTS = 1;

}

void dev_hal_init()
{
 write_uart_p = UART_Wr_Ptr;
}

void dev_hal_write( char ch )
{
#line 111 "C:/Users/richard/Desktop/GSM4/library/src/gsm4_dev_hal.c"
 write_uart_p( ch );

}

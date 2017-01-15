#line 1 "D:/Marko/tasks/freescale/svn/Hexiwear/MK64/5. Click Demos/1. mikroC/2. Primeri/HEXIWEAR_8x8_Click/example/ARM/eight_x_eight_hal.c"
#line 1 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_8x8_click/example/arm/eight_x_eight_hal.h"
#line 1 "d:/work/mikroc pro for arm/include/stdint.h"





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
#line 1 "d:/work/mikroc pro for arm/include/stdbool.h"



 typedef char _Bool;
#line 1 "d:/work/mikroc pro for arm/include/stddef.h"



typedef long ptrdiff_t;


 typedef unsigned long size_t;

typedef unsigned long wchar_t;
#line 64 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_8x8_click/example/arm/eight_x_eight_hal.h"
void led_eight_hal_cs_high( void );
#line 72 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_8x8_click/example/arm/eight_x_eight_hal.h"
void led_eight_hal_cs_low( void );
#line 79 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_8x8_click/example/arm/eight_x_eight_hal.h"
void led_eight_hal_init( void );
#line 93 "d:/marko/tasks/freescale/svn/hexiwear/mk64/5. click demos/1. mikroc/2. primeri/hexiwear_8x8_click/example/arm/eight_x_eight_hal.h"
void led_eight_hal_write( uint8_t *buffer );
#line 38 "D:/Marko/tasks/freescale/svn/Hexiwear/MK64/5. Click Demos/1. mikroC/2. Primeri/HEXIWEAR_8x8_Click/example/ARM/eight_x_eight_hal.c"
static void ( *write_spi_p ) ( unsigned int data_out );
static unsigned long( *read_spi_p ) ( unsigned int buffer );

extern sfr sbit LED_EIGHT_CS;
#line 51 "D:/Marko/tasks/freescale/svn/Hexiwear/MK64/5. Click Demos/1. mikroC/2. Primeri/HEXIWEAR_8x8_Click/example/ARM/eight_x_eight_hal.c"
void led_eight_hal_cs_high()
{
 LED_EIGHT_CS = 1;
}

void led_eight_hal_cs_low()
{
 LED_EIGHT_CS = 0;
}

void led_eight_hal_init()
{
 write_spi_p = SPI_Wr_Ptr;
 read_spi_p = SPI_Rd_Ptr;
 led_eight_hal_cs_high();
}

void led_eight_hal_write( uint8_t *buffer )
{
 led_eight_hal_cs_low();
 write_spi_p( *( buffer )++ );
 write_spi_p( *buffer );
 led_eight_hal_cs_high();
}

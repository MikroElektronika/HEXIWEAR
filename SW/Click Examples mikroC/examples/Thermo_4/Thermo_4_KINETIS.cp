#line 1 "C:/Users/djordje.rosic/Desktop/Archive/Thermo_4_Click/example/KINETIS/Thermo_4_KINETIS.c"
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for arm/packages/click_thermo_4_arm/uses/thermo_4_click.h"
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for arm/include/stddef.h"



typedef long ptrdiff_t;


 typedef unsigned long size_t;

typedef unsigned long wchar_t;
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
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for arm/include/stdbool.h"



 typedef char _Bool;
#line 147 "c:/users/public/documents/mikroelektronika/mikroc pro for arm/packages/click_thermo_4_arm/uses/thermo_4_click.h"
uint16_t thermo_init(uint8_t i2c_address);
#line 164 "c:/users/public/documents/mikroelektronika/mikroc pro for arm/packages/click_thermo_4_arm/uses/thermo_4_click.h"
void thermo_config(uint8_t value);
#line 180 "c:/users/public/documents/mikroelektronika/mikroc pro for arm/packages/click_thermo_4_arm/uses/thermo_4_click.h"
void thermo_read_temperature_text( char *output [15], uint8_t _location );
#line 193 "c:/users/public/documents/mikroelektronika/mikroc pro for arm/packages/click_thermo_4_arm/uses/thermo_4_click.h"
uint16_t thermo_read_temperature_binary( uint8_t _location );
#line 212 "c:/users/public/documents/mikroelektronika/mikroc pro for arm/packages/click_thermo_4_arm/uses/thermo_4_click.h"
float thermo_read_temperature_fh ( uint8_t _location );
#line 230 "c:/users/public/documents/mikroelektronika/mikroc pro for arm/packages/click_thermo_4_arm/uses/thermo_4_click.h"
void thermo_write_temperature ( float _value, uint8_t _location );
#line 20 "C:/Users/djordje.rosic/Desktop/Archive/Thermo_4_Click/example/KINETIS/Thermo_4_KINETIS.c"
uint16_t temp_value;
char uart_text [15];
uint8_t i;
float _fh_value;

static void system_init( void )
{

 UART0_Init( 115200 );
 Delay_ms (100);
 I2C0_Init_Advanced(100000, &_GPIO_Module_I2C0_PD8_9);
 Delay_ms (100);
 UART0_Write_Text( "\r\n INITIALIZED  \r\n" );

}



void main()
{

 system_init();
 thermo_init(0x55);
 Delay_ms (100);
 i=5;



 thermo_write_temperature (65.5,  0x03 );

 thermo_read_temperature_text (uart_text,  0x03 );
 Delay_ms (100);

 UART0_Write_Text("\r\n Current temperature limit for output signal: ");
 UART0_Write_Text(uart_text);
 Delay_ms( 1000 );


 _fh_value = thermo_read_temperature_fh ( 0x00 );
 FloatToStr (_fh_value , uart_text);
 uart_text [5] = 0;
 Delay_ms (100);
 UART0_Write_Text("\r\n \r\n Current temperature in Fahrenheit: ");
 UART0_Write_Text(uart_text);
 Delay_ms( 1000 );




 while( i-- )
 {
 UART0_Write_Text( "\r\n Current TEMP value: " );
 thermo_read_temperature_text (uart_text,  0x00 );
 UART0_Write_Text(uart_text);
 Delay_ms( 2000 );
 }
#line 79 "C:/Users/djordje.rosic/Desktop/Archive/Thermo_4_Click/example/KINETIS/Thermo_4_KINETIS.c"
 thermo_config ( 0x01 );
 UART0_Write_Text( "\r\n SHUTDOWN MODE" );
 Delay_ms( 350 );
 i=5;
 while( i-- )
 {
 UART0_Write_Text( "\r\n Current TEMP value: " );
 thermo_read_temperature_text (uart_text,  0x00 );
 UART0_Write_Text(uart_text);
 Delay_ms( 2000 );
 }



 thermo_config ( 0xFE );
 UART0_Write_Text( "\r\n POWERING UP..." );
 Delay_ms( 350 );
 i=5;
 while( i-- )
 {
 UART0_Write_Text( "\r\n Current TEMP value: " );
 thermo_read_temperature_text (uart_text,  0x00 );
 UART0_Write_Text(uart_text);
 Delay_ms( 2000 );
 }

}

#line 1 "C:/Users/djordje.rosic/Desktop/Projects/MIC 24045/mic_24045_click/library/src/mic_24045_click.c"
#line 1 "c:/users/djordje.rosic/desktop/projects/mic 24045/mic_24045_click/library/include/mic_24045_click.h"
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for pic32/include/stddef.h"



typedef long ptrdiff_t;
typedef unsigned long size_t;
typedef unsigned long wchar_t;
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for pic32/include/stdint.h"




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
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for pic32/include/stdbool.h"



 typedef char _Bool;
#line 142 "c:/users/djordje.rosic/desktop/projects/mic 24045/mic_24045_click/library/include/mic_24045_click.h"
uint16_t mic_24045_init(uint8_t i2c_address);
#line 151 "c:/users/djordje.rosic/desktop/projects/mic 24045/mic_24045_click/library/include/mic_24045_click.h"
 _Bool  mic_24045_status (uint8_t cmd);
#line 157 "c:/users/djordje.rosic/desktop/projects/mic 24045/mic_24045_click/library/include/mic_24045_click.h"
void mic_24045_clear_flags ();
#line 167 "c:/users/djordje.rosic/desktop/projects/mic 24045/mic_24045_click/library/include/mic_24045_click.h"
float mic_24045_read_vout ();
#line 179 "c:/users/djordje.rosic/desktop/projects/mic 24045/mic_24045_click/library/include/mic_24045_click.h"
void mic_24045_write_vout (float vout);
#line 190 "c:/users/djordje.rosic/desktop/projects/mic 24045/mic_24045_click/library/include/mic_24045_click.h"
uint8_t mic_24045_read_settings (uint8_t reg);
#line 200 "c:/users/djordje.rosic/desktop/projects/mic 24045/mic_24045_click/library/include/mic_24045_click.h"
void mic_24045_write_settings (uint8_t reg, uint8_t set);
#line 1 "c:/users/djordje.rosic/desktop/projects/mic 24045/mic_24045_click/library/include/mic_24045_click_hal.h"
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for pic32/include/stdint.h"
#line 23 "c:/users/djordje.rosic/desktop/projects/mic 24045/mic_24045_click/library/include/mic_24045_click_hal.h"
void hal_delay( uint16_t ms );
#line 31 "c:/users/djordje.rosic/desktop/projects/mic 24045/mic_24045_click/library/include/mic_24045_click_hal.h"
uint16_t hal_init( uint8_t address_id );
#line 43 "c:/users/djordje.rosic/desktop/projects/mic 24045/mic_24045_click/library/include/mic_24045_click_hal.h"
uint16_t hal_write
(
 uint8_t i2c_address,
 uint8_t *buffer,
 uint16_t count
);
#line 64 "c:/users/djordje.rosic/desktop/projects/mic 24045/mic_24045_click/library/include/mic_24045_click_hal.h"
uint16_t hal_read
(
 uint8_t i2c_address,
 uint8_t *buffer,
 uint16_t count
);
#line 83 "c:/users/djordje.rosic/desktop/projects/mic 24045/mic_24045_click/library/include/mic_24045_click_hal.h"
uint16_t hal_transfer
(
 uint8_t i2c_address,
 uint8_t* input,
 uint16_t in_count,
 uint8_t* output,
 uint16_t out_count
);
#line 34 "C:/Users/djordje.rosic/Desktop/Projects/MIC 24045/mic_24045_click/library/src/mic_24045_click.c"
static uint16_t _mic_24045_read( uint8_t reg, uint8_t *output );
static uint16_t _mic_24045_write( uint8_t reg, uint8_t wr_data);
static float _mic_24045_bit2float (uint8_t _value);
static uint8_t _mic_24045_float2bit (float vout);
#line 42 "C:/Users/djordje.rosic/Desktop/Projects/MIC 24045/mic_24045_click/library/src/mic_24045_click.c"
static uint16_t _mic_24045_read ( uint8_t reg, uint8_t *output )
{
 uint8_t *out = output;
 *out = reg;
 hal_read(  0x50 , out ,1 );
 return  (0) ;
}


static uint16_t _mic_24045_write ( uint8_t reg, uint8_t wr_data)
{
 uint8_t input[ 2 ];
 input[ 0 ] = reg;
 input[ 1 ] = wr_data;
 hal_write(  0x50 , input, 2 );
 return  (0) ;
}

static uint8_t _mic_24045_float2bit (float vout)
{
 uint8_t _value = 0;
 if (vout >= 5.250)
 {
 _value = 0xff;
 return _value;
 }
 else if (vout >= 4.750)
 {
 _value = 0xf5;
 while (vout > 4.750)
 {
 _value++;
 vout -= 0.05;
 }
 return _value;
 }
 else if (vout >= 3.420)
 {
 _value = 0xf4;
 return _value;
 }
 else if (vout >= 1.980)
 {
 _value = 0xc4;
 while (vout > 1.980)
 {
 _value++;
 vout -= 0.03;
 }
 return _value;
 }
 else if (vout >= 1.290)
 {
 _value = 0x81;
 while (vout > 1.290)
 {
 _value++;
 vout -= 0.01;
 }
 return _value;
 }
 else if (vout >= 0.640)
 {
 _value = 0x00;
 while (vout > 0.640)
 {
 _value++;
 vout -= 0.005;
 }
 return _value;
 }
 else _value = 0x00;
 return _value;
}

static float _mic_24045_bit2float (uint8_t _value)
{
 float _retval = 0;
 if (_value >= 0 && _value <= 0x80)
 {
 _retval = 0.640;
 while (_value > 0)
 {
 _retval += 0.005;
 _value --;
 }
 return _retval;
 }
 else if (_value >= 0x81 && _value <= 0xC3)
 {
 _retval = 1.290;
 while (_value > 0x81)
 {
 _retval += 0.010;
 _value --;
 }
 return _retval;
 }
 else if (_value >= 0xC4 && _value <= 0xF4)
 {
 _retval = 1.980;
 while (_value > 0xC4)
 {
 _retval += 0.030;
 _value --;
 }
 return _retval;
 }
 else if (_value >= 0xF5 && _value <= 0xFF)
 {
 _retval = 4.750;
 while (_value > 0xF5)
 {
 _retval += 0.050;
 _value --;
 }
 return _retval;
 }
 return _retval;

}
#line 169 "C:/Users/djordje.rosic/Desktop/Projects/MIC 24045/mic_24045_click/library/src/mic_24045_click.c"
uint16_t mic_24045_init (uint8_t i2c_address )
{
 return hal_init( i2c_address);
}

 _Bool  mic_24045_status (uint8_t cmd)
{
 uint8_t _value = 0;
 _mic_24045_read ( 0x00 , &_value);
 if (cmd & _value)
 return  1 ;
 else return  0 ;
}

void mic_24045_clear_flags ()
{
 _mic_24045_write ( 0x04 ,  0x01 );
}


float mic_24045_read_vout ()
{
 uint8_t _value = 0;
 _mic_24045_read ( 0x03 , &_value);
 return _mic_24045_bit2float (_value);
}
void mic_24045_write_vout (float vout)
{
 uint8_t _value = 0;
 _value = _mic_24045_float2bit (vout);
 _mic_24045_write ( 0x03 , _value);
}



uint8_t mic_24045_read_settings (uint8_t reg)
{
 uint8_t _value = 0;
 _mic_24045_read (reg, &_value);
 return _value;
}
void mic_24045_write_settings (uint8_t reg, uint8_t set)
{
 _mic_24045_write (reg, set);
}

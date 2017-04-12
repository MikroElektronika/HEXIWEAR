#line 1 "C:/Users/djordje.rosic/Desktop/Projects/MIC 24045/mic_24045_click/library/src/mic_24045_click_Hal.c"
#line 1 "c:/users/djordje.rosic/desktop/projects/mic 24045/mic_24045_click/library/include/mic_24045_click_hal.h"
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
#line 1 "c:/users/djordje.rosic/desktop/projects/mic 24045/mic_24045_click/library/include/mic_24045_click.h"
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for pic32/include/stddef.h"



typedef long ptrdiff_t;
typedef unsigned long size_t;
typedef unsigned long wchar_t;
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for pic32/include/stdint.h"
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
#line 40 "C:/Users/djordje.rosic/Desktop/Projects/MIC 24045/mic_24045_click/library/src/mic_24045_click_Hal.c"
static uint8_t NACK_BIT = 0x01;
static uint8_t ACK_BIT = 0x00;
#line 87 "C:/Users/djordje.rosic/Desktop/Projects/MIC 24045/mic_24045_click/library/src/mic_24045_click_Hal.c"
static unsigned int ( *is_idle_i2c_p ) ( void );
static unsigned int ( *start_i2c_p ) ( void );
static void ( *stop_i2c_p ) ( void );
static unsigned int ( *restart_i2c_p ) ( void );
static unsigned int ( *write_i2c_p ) ( unsigned char data_out );
static unsigned char( *read_i2c_p ) ( unsigned int ack );
#line 122 "C:/Users/djordje.rosic/Desktop/Projects/MIC 24045/mic_24045_click/library/src/mic_24045_click_Hal.c"
void hal_delay( uint16_t ms )
{
#line 131 "C:/Users/djordje.rosic/Desktop/Projects/MIC 24045/mic_24045_click/library/src/mic_24045_click_Hal.c"
 while( ms-- )
 Delay_1ms();

}

uint16_t hal_init( uint8_t address_id )
{
#line 181 "C:/Users/djordje.rosic/Desktop/Projects/MIC 24045/mic_24045_click/library/src/mic_24045_click_Hal.c"
 is_idle_i2c_p = I2C_Is_Idle_Ptr;
 start_i2c_p = I2C_Start_Ptr;
 stop_i2c_p = I2C_Stop_Ptr;
 restart_i2c_p = I2C_Restart_Ptr;
 write_i2c_p = I2C_Write_Ptr;
 read_i2c_p = I2C_Read_Ptr;
#line 211 "C:/Users/djordje.rosic/Desktop/Projects/MIC 24045/mic_24045_click/library/src/mic_24045_click_Hal.c"
 return 0;
}

uint16_t hal_write
(
 uint8_t i2c_address,
 uint8_t* buffer,
 uint16_t count
)
{
 uint16_t res = 0;
 uint8_t *ptr = buffer;
#line 254 "C:/Users/djordje.rosic/Desktop/Projects/MIC 24045/mic_24045_click/library/src/mic_24045_click_Hal.c"
 res |= start_i2c_p();
 write_i2c_p( ( i2c_address << 1 ) |  0  );
 while( count-- )
 write_i2c_p( *ptr++ );
 stop_i2c_p();

 return res;
}

uint16_t hal_read
(
 uint8_t i2c_address,
 uint8_t* buffer,
 uint16_t count
)
{
 uint16_t res = 0;
 uint8_t *ptr = buffer;
#line 310 "C:/Users/djordje.rosic/Desktop/Projects/MIC 24045/mic_24045_click/library/src/mic_24045_click_Hal.c"
 res |= start_i2c_p();
 write_i2c_p( ( i2c_address << 1 ) |  0  );
 write_i2c_p( *ptr );
 stop_i2c_p();
 Delay_ms( 5 );
 res |= start_i2c_p();
 write_i2c_p( ( i2c_address << 1 ) |  1  );
 while( --count )
 *ptr++ = read_i2c_p( ACK_BIT );
 *ptr = read_i2c_p( NACK_BIT );
 stop_i2c_p();

 return res;
}

uint16_t hal_transfer
(
 uint8_t i2c_address,
 uint8_t* input,
 uint16_t in_count,
 uint8_t* output,
 uint16_t out_count
)
{
 uint16_t res = 0;
 uint8_t *in = input;
 uint8_t *out = output;
#line 404 "C:/Users/djordje.rosic/Desktop/Projects/MIC 24045/mic_24045_click/library/src/mic_24045_click_Hal.c"
 res |= start_i2c_p();
 write_i2c_p( ( i2c_address << 1 ) |  0  );
 while( in_count-- )
 write_i2c_p( *in++ );
 restart_i2c_p();
 write_i2c_p( ( i2c_address << 1 ) |  1  );
 while( --out_count )
 *out++ = read_i2c_p( ACK_BIT );
 *out = read_i2c_p( NACK_BIT );
 stop_i2c_p();


 return res;
}

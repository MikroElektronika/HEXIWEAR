#line 1 "D:/Uros/!!KONACNI PRIMERI/backup/HEXIWEAR_IR_GESTURE_Click/example/ARM/src/ir_gesture_hal.c"
#line 1 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hal.h"
#line 1 "d:/program files/nxp/mikroc pro for arm/include/stdint.h"





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
#line 73 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hal.h"
int ir_gesture_i2c_init( uint8_t address_id );
#line 79 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hal.h"
void ir_gesture_hal_delay( uint8_t ms );
#line 88 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hal.h"
void ir_gesture_i2c_hal_write( uint8_t address,
 uint8_t const *buff, uint16_t count );
#line 98 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hal.h"
void ir_gesture_i2c_hal_read( uint8_t address,
 uint8_t const *buff , uint16_t count );
#line 1 "d:/program files/nxp/mikroc pro for arm/include/stdint.h"
#line 1 "d:/program files/nxp/mikroc pro for arm/include/string.h"





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
#line 39 "D:/Uros/!!KONACNI PRIMERI/backup/HEXIWEAR_IR_GESTURE_Click/example/ARM/src/ir_gesture_hal.c"
static uint8_t _i2c_hw_address;


static unsigned int( *start_i2c_p )( void );
static unsigned int( *write_i2c_p )( unsigned char slave_address,
 unsigned char *buffer,
 unsigned long count,
 unsigned long end_mode );
static void( *read_i2c_p )( unsigned char slave_address,
 unsigned char *buffer,
 unsigned long count,
 unsigned long end_mode );
#line 64 "D:/Uros/!!KONACNI PRIMERI/backup/HEXIWEAR_IR_GESTURE_Click/example/ARM/src/ir_gesture_hal.c"
int ir_gesture_i2c_init( uint8_t address_id )
{

 start_i2c_p = I2C_Start_Ptr;
 write_i2c_p = I2C_Write_Ptr;
 read_i2c_p = I2C_Read_Ptr;

 _i2c_hw_address = address_id;
 return ( _i2c_hw_address == 0 ) ? -1 : 0;
}

void ir_gesture_hal_delay( uint8_t ms )
{



 while( ms-- )
 Delay_1ms();


}

void ir_gesture_i2c_hal_write( uint8_t address, uint8_t const *buff , uint16_t count )
{
 uint8_t temp_buff[  5  ];
 uint8_t *temp_ptr = ( uint8_t *)buff;

 temp_buff[0] = address;
 memcpy( &temp_buff[1], temp_ptr, count );

 start_i2c_p();
 write_i2c_p( _i2c_hw_address, temp_buff, count + 1, _I2C_END_MODE_STOP );
}

void ir_gesture_i2c_hal_read( uint8_t address, uint8_t const *buffer, uint16_t count )
{
 uint8_t *ptr = ( uint8_t *)buffer;

 start_i2c_p();
 write_i2c_p( _i2c_hw_address, &address, 1, _I2C_END_MODE_RESTART );
 read_i2c_p( _i2c_hw_address, ptr, count, _I2C_END_MODE_STOP );
}

#line 1 "//VBOXSVR/storage/git/MikroE/HEXIWEAR/SW/Click Examples mikroC/2.Examples/HEXIWEAR_NFC_Click/example/ARM/nfc_hal.c"
#line 1 "//vboxsvr/storage/git/mikroe/hexiwear/sw/click examples mikroc/2.examples/hexiwear_nfc_click/example/arm/nfc_hal.h"
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
#line 69 "//vboxsvr/storage/git/mikroe/hexiwear/sw/click examples mikroc/2.examples/hexiwear_nfc_click/example/arm/nfc_hal.h"
void nfc_hal_init( uint8_t address_id );

void nfc_hal_delay( uint16_t ms );

void nfc_hal_reset( void );

int nfc_hal_write( uint8_t *data_out, uint16_t count );

int nfc_hal_read( uint8_t *data_in, uint16_t *nbytes_read,
 uint16_t count );
#line 1 "c:/c4w/mikroc pro for arm/include/stdio.h"
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
#line 45 "//VBOXSVR/storage/git/MikroE/HEXIWEAR/SW/Click Examples mikroC/2.Examples/HEXIWEAR_NFC_Click/example/ARM/nfc_hal.c"
static uint8_t _i2c_hw_address;
#line 70 "//VBOXSVR/storage/git/MikroE/HEXIWEAR/SW/Click Examples mikroC/2.Examples/HEXIWEAR_NFC_Click/example/ARM/nfc_hal.c"
static unsigned int( *start_i2c_p )( void );
static unsigned int( *write_i2c_p )( unsigned char slave_address, unsigned char *buffer, unsigned long count, unsigned long end_mode );
static void( *read_i2c_p )( unsigned char slave_address, unsigned char *buffer, unsigned long count, unsigned long end_mode );
#line 142 "//VBOXSVR/storage/git/MikroE/HEXIWEAR/SW/Click Examples mikroC/2.Examples/HEXIWEAR_NFC_Click/example/ARM/nfc_hal.c"
extern sfr sbit NFC_RST_PIN;
extern sfr sbit NFC_INT_PIN;
#line 156 "//VBOXSVR/storage/git/MikroE/HEXIWEAR/SW/Click Examples mikroC/2.Examples/HEXIWEAR_NFC_Click/example/ARM/nfc_hal.c"
void nfc_hal_init( uint8_t address_id )
{
#line 171 "//VBOXSVR/storage/git/MikroE/HEXIWEAR/SW/Click Examples mikroC/2.Examples/HEXIWEAR_NFC_Click/example/ARM/nfc_hal.c"
 start_i2c_p = I2C_Start_Ptr;
 write_i2c_p = I2C_Write_Ptr;
 read_i2c_p = I2C_Read_Ptr;
#line 240 "//VBOXSVR/storage/git/MikroE/HEXIWEAR/SW/Click Examples mikroC/2.Examples/HEXIWEAR_NFC_Click/example/ARM/nfc_hal.c"
 _i2c_hw_address = address_id;
#line 244 "//VBOXSVR/storage/git/MikroE/HEXIWEAR/SW/Click Examples mikroC/2.Examples/HEXIWEAR_NFC_Click/example/ARM/nfc_hal.c"
 nfc_hal_reset();
}


void nfc_hal_reset()
{
#line 257 "//VBOXSVR/storage/git/MikroE/HEXIWEAR/SW/Click Examples mikroC/2.Examples/HEXIWEAR_NFC_Click/example/ARM/nfc_hal.c"
 NFC_RST_PIN =  1 ;
 Delay_10ms();
 NFC_RST_PIN =  0 ;
 Delay_10ms();
 NFC_RST_PIN =  1 ;
 Delay_10ms();


}


void nfc_hal_delay( uint16_t ms )
{
#line 277 "//VBOXSVR/storage/git/MikroE/HEXIWEAR/SW/Click Examples mikroC/2.Examples/HEXIWEAR_NFC_Click/example/ARM/nfc_hal.c"
 while( ms--)
 Delay_1ms();
#line 283 "//VBOXSVR/storage/git/MikroE/HEXIWEAR/SW/Click Examples mikroC/2.Examples/HEXIWEAR_NFC_Click/example/ARM/nfc_hal.c"
}

int nfc_hal_write( uint8_t *data_out, uint16_t count )
{
 if( data_out ==  ((void *)0)  )
 return -1;
#line 317 "//VBOXSVR/storage/git/MikroE/HEXIWEAR/SW/Click Examples mikroC/2.Examples/HEXIWEAR_NFC_Click/example/ARM/nfc_hal.c"
 start_i2c_p();
 return( write_i2c_p( _i2c_hw_address, data_out, count, END_MODE_STOP ) ) ? -1 : 0;
#line 344 "//VBOXSVR/storage/git/MikroE/HEXIWEAR/SW/Click Examples mikroC/2.Examples/HEXIWEAR_NFC_Click/example/ARM/nfc_hal.c"
 nfc_hal_delay( 10 );
 return 0;
}
#line 352 "//VBOXSVR/storage/git/MikroE/HEXIWEAR/SW/Click Examples mikroC/2.Examples/HEXIWEAR_NFC_Click/example/ARM/nfc_hal.c"
int nfc_hal_read( uint8_t *data_in,
 uint16_t *nbytes_read,
 uint16_t count )
{
#line 394 "//VBOXSVR/storage/git/MikroE/HEXIWEAR/SW/Click Examples mikroC/2.Examples/HEXIWEAR_NFC_Click/example/ARM/nfc_hal.c"
 start_i2c_p();
 read_i2c_p( _i2c_hw_address, data_in, 3, END_MODE_STOP );

 if( data_in[2] != 0 )
 {
 start_i2c_p();
 read_i2c_p( _i2c_hw_address, &data_in[3], data_in[2], END_MODE_STOP );
 *nbytes_read = data_in[2] + 3;

 } else {
 *nbytes_read = 3;
 }
#line 460 "//VBOXSVR/storage/git/MikroE/HEXIWEAR/SW/Click Examples mikroC/2.Examples/HEXIWEAR_NFC_Click/example/ARM/nfc_hal.c"
 return 0;
}

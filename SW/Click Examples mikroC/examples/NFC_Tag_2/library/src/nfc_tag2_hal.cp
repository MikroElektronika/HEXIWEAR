#line 1 "E:/git/ClickLab/NFC_Tag2_click/library/src/nfc_tag2_hal.c"
#line 1 "e:/git/clicklab/nfc_tag2_click/library/include/nfc_tag2_hal.h"
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
#line 20 "e:/git/clicklab/nfc_tag2_click/library/include/nfc_tag2_hal.h"
void hal_delay( uint16_t ms );
#line 30 "e:/git/clicklab/nfc_tag2_click/library/include/nfc_tag2_hal.h"
int hal_nfctag2_init( void );
#line 43 "e:/git/clicklab/nfc_tag2_click/library/include/nfc_tag2_hal.h"
int hal_nfctag2_write
(
 uint8_t i2c_address,
 uint8_t *buffer,
 uint16_t count
);
#line 63 "e:/git/clicklab/nfc_tag2_click/library/include/nfc_tag2_hal.h"
int hal_nfctag2_read
(
 uint8_t i2c_address,
 uint8_t *buffer,
 uint16_t count
);
#line 79 "e:/git/clicklab/nfc_tag2_click/library/include/nfc_tag2_hal.h"
int hal_nfctag2_transfer
(
 uint8_t i2c_address,
 uint8_t* input,
 uint16_t in_count,
 uint8_t* output,
 uint16_t out_count
);
#line 42 "E:/git/ClickLab/NFC_Tag2_click/library/src/nfc_tag2_hal.c"
static unsigned int ( *start_i2c_p ) ( void );
static unsigned int ( *write_i2c_p ) ( unsigned char slave_address,
 unsigned char *buffer,
 unsigned long count,
 unsigned long end_mode );
static void ( *read_i2c_p ) ( unsigned char slave_address,
 unsigned char *buffer,
 unsigned long count,
 unsigned long end_mode );
#line 115 "E:/git/ClickLab/NFC_Tag2_click/library/src/nfc_tag2_hal.c"
void hal_delay( uint16_t ms )
{
#line 124 "E:/git/ClickLab/NFC_Tag2_click/library/src/nfc_tag2_hal.c"
 while( ms-- )
 Delay_1ms();

}

int hal_nfctag2_init( void )
{


 start_i2c_p = I2C_Start_Ptr;
 write_i2c_p = I2C_Write_Ptr;
 read_i2c_p = I2C_Read_Ptr;
#line 203 "E:/git/ClickLab/NFC_Tag2_click/library/src/nfc_tag2_hal.c"
 return 0;
}

int hal_nfctag2_write
(
 uint8_t i2c_address,
 uint8_t* buffer,
 uint16_t count
)
{
 int res = 0;
 uint8_t *ptr = buffer;



 res |= start_i2c_p();
 res |= write_i2c_p( i2c_address, ptr, count, END_MODE_STOP );
#line 253 "E:/git/ClickLab/NFC_Tag2_click/library/src/nfc_tag2_hal.c"
 return res;
}

int hal_nfctag2_read
(
 uint8_t i2c_address,
 uint8_t* buffer,
 uint16_t count
)
{
 int res = 0;
 uint8_t *ptr = buffer;



 res |= start_i2c_p();
 res |= write_i2c_p( i2c_address, ptr, 1, END_MODE_STOP );
 res |= start_i2c_p();
 read_i2c_p( i2c_address, ptr, count, END_MODE_STOP );
#line 315 "E:/git/ClickLab/NFC_Tag2_click/library/src/nfc_tag2_hal.c"
 return res;
}

int hal_nfctag2_transfer
(
 uint8_t i2c_address,
 uint8_t* input,
 uint16_t in_count,
 uint8_t* output,
 uint16_t out_count
)
{
 int res = 0;
 uint8_t *in = input;
 uint8_t *out = output;



 res |= start_i2c_p();
 res |= write_i2c_p( i2c_address, in, in_count, END_MODE_STOP );
 res |= start_i2c_p();
 read_i2c_p( i2c_address, out, out_count, END_MODE_STOP );
#line 395 "E:/git/ClickLab/NFC_Tag2_click/library/src/nfc_tag2_hal.c"
 return res;
}

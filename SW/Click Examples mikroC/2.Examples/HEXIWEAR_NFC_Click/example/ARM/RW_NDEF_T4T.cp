#line 1 "E:/Darko/Projekti/HEXIWEAR/Click Demo/Projekti/HEXIWEAR_NFC_Click/example/ARM/RW_NDEF_T4T.c"
#line 1 "c:/users/public/documents/mikroelektronika/arm/radni/mikroc pro for arm/include/string.h"





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
#line 1 "c:/users/public/documents/mikroelektronika/arm/radni/mikroc pro for arm/include/stddef.h"



typedef long ptrdiff_t;


 typedef unsigned long size_t;

typedef unsigned long wchar_t;
#line 1 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_nfc_click/example/arm/rw_ndef.h"
#line 1 "c:/users/public/documents/mikroelektronika/arm/radni/mikroc pro for arm/include/stdint.h"





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
#line 60 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_nfc_click/example/arm/rw_ndef.h"
typedef void rw_ndef_callback_t( uint8_t *, uint16_t );
#line 65 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_nfc_click/example/arm/rw_ndef.h"
extern uint8_t ndef_buffer[ 240 ];
extern rw_ndef_callback_t *p_rw_ndef_pull_cb;
#line 79 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_nfc_click/example/arm/rw_ndef.h"
void rw_ndef_register_pull_callback( void *p_cb );
#line 85 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_nfc_click/example/arm/rw_ndef.h"
void rw_ndef_reset( uint8_t type );
#line 94 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_nfc_click/example/arm/rw_ndef.h"
void rw_ndef_read_next( uint8_t *p_cmd, uint16_t cmd_size,
 uint8_t *rsp, uint16_t *p_rsp_size );
#line 37 "E:/Darko/Projekti/HEXIWEAR/Click Demo/Projekti/HEXIWEAR_NFC_Click/example/ARM/RW_NDEF_T4T.c"
typedef enum
{
 INITIAL,
 SELECTING_NDEF_APPLICATION20,
 SELECTING_NDEF_APPLICATION10,
 SELECTING_CC,
 READING_CC,
 SELECTING_NDEF,
 READING_NDEF_SIZE,
 READING_NDEF
} rw_ndef_t4t_state_t;

typedef struct
{
 uint8_t mapping_version;
 uint16_t mle;
 uint16_t mlc;
 uint8_t file_id[2];
 uint16_t max_ndef_file_size;
 uint8_t rd_access;
 uint8_t wr_access;
 uint16_t record_ptr;
 uint16_t record_size;
 uint8_t *p_record;
} rw_ndef_t4t_ndef_t;
#line 66 "E:/Darko/Projekti/HEXIWEAR/Click Demo/Projekti/HEXIWEAR_NFC_Click/example/ARM/RW_NDEF_T4T.c"
static const uint8_t RW_NDEF_T4T_APP_SELECT[] =
{
 0x00, 0xA4, 0x04, 0x00, 0x07, 0xD2, 0x76, 0x00, 0x00, 0x85, 0x01, 0x01
};
static const uint8_t RW_NDEF_T4T_CC_SELECT[] =
{
 0x00, 0xA4, 0x00, 0x0C, 0x02, 0xE1, 0x03
};
static const uint8_t RW_NDEF_T4T_NDEF_SELECT[] =
{
 0x00, 0xA4, 0x00, 0x0C, 0x02, 0xE1, 0x04
};
static const uint8_t RW_NDEF_T4T_READ[] =
{
 0x00, 0xB0, 0x00, 0x00, 0x0F
};

static const uint8_t RW_NDEF_T4T_OK[] = {0x90, 0x00};

static rw_ndef_t4t_state_t e_rw_ndef_t4t_state = INITIAL;
static rw_ndef_t4t_ndef_t rw_ndef_t4t_ndef;
#line 95 "E:/Darko/Projekti/HEXIWEAR/Click Demo/Projekti/HEXIWEAR_NFC_Click/example/ARM/RW_NDEF_T4T.c"
void rw_ndef_t4t_reset( void )
{
 e_rw_ndef_t4t_state = INITIAL;
 rw_ndef_t4t_ndef.p_record = ndef_buffer;
}

void rw_ndef_t4t_read_next(uint8_t *p_cmd, uint16_t cmd_size,
 uint8_t *rsp, uint16_t *p_rsp_size )
{

 *p_rsp_size = 0;

 switch( e_rw_ndef_t4t_state )
 {
 case INITIAL:

 memcpy( rsp, ( uint8_t * )RW_NDEF_T4T_APP_SELECT, sizeof( RW_NDEF_T4T_APP_SELECT ) );
 *p_rsp_size = sizeof( RW_NDEF_T4T_APP_SELECT );
 e_rw_ndef_t4t_state = SELECTING_NDEF_APPLICATION20;
 break;

 case SELECTING_NDEF_APPLICATION20:

 if ( !memcmp( &p_cmd[cmd_size - 2], ( uint8_t * )RW_NDEF_T4T_OK,
 sizeof( RW_NDEF_T4T_OK ) ) )
 {

 memcpy( rsp, ( uint8_t * )RW_NDEF_T4T_CC_SELECT, sizeof( RW_NDEF_T4T_CC_SELECT ) );
 *p_rsp_size = sizeof( RW_NDEF_T4T_CC_SELECT );
 e_rw_ndef_t4t_state = SELECTING_CC;
 }
 else
 {

 memcpy( rsp, ( uint8_t * )RW_NDEF_T4T_APP_SELECT, sizeof( RW_NDEF_T4T_APP_SELECT ) );
 rsp[11] = 0x0;
 *p_rsp_size = sizeof( RW_NDEF_T4T_APP_SELECT );
 e_rw_ndef_t4t_state = SELECTING_NDEF_APPLICATION10;
 }
 break;

 case SELECTING_NDEF_APPLICATION10:

 if ( !memcmp( &p_cmd[cmd_size - 2], ( uint8_t * )RW_NDEF_T4T_OK,
 sizeof( RW_NDEF_T4T_OK ) ) )
 {

 memcpy( rsp, ( uint8_t * )RW_NDEF_T4T_CC_SELECT, sizeof( RW_NDEF_T4T_CC_SELECT ) );
 rsp[3] = 0x00;
 *p_rsp_size = sizeof( RW_NDEF_T4T_CC_SELECT );
 e_rw_ndef_t4t_state = SELECTING_CC;
 }
 break;

 case SELECTING_CC:

 if ( !memcmp( &p_cmd[cmd_size - 2], ( uint8_t * )RW_NDEF_T4T_OK,
 sizeof( RW_NDEF_T4T_OK ) ) )
 {

 memcpy( rsp, ( uint8_t * )RW_NDEF_T4T_READ, sizeof( RW_NDEF_T4T_READ ) );
 *p_rsp_size = sizeof( RW_NDEF_T4T_READ );
 e_rw_ndef_t4t_state = READING_CC;
 }
 break;

 case READING_CC:

 if ( ( !memcmp( &p_cmd[cmd_size - 2], ( uint8_t * )RW_NDEF_T4T_OK,
 sizeof( RW_NDEF_T4T_OK ) ) ) && ( cmd_size == 15 + 2 ) )
 {

 rw_ndef_t4t_ndef.mapping_version = p_cmd[2];
 rw_ndef_t4t_ndef.mle = ( p_cmd[3] << 8 ) + p_cmd[4];
 rw_ndef_t4t_ndef.mlc = ( p_cmd[5] << 8 ) + p_cmd[6];
 rw_ndef_t4t_ndef.file_id[0] = p_cmd[9];
 rw_ndef_t4t_ndef.file_id[1] = p_cmd[10];
 rw_ndef_t4t_ndef.max_ndef_file_size = ( p_cmd[11] << 8 ) + p_cmd[12];
 rw_ndef_t4t_ndef.rd_access = p_cmd[13];
 rw_ndef_t4t_ndef.wr_access = p_cmd[14];


 memcpy( rsp, ( uint8_t * )RW_NDEF_T4T_NDEF_SELECT, sizeof( RW_NDEF_T4T_NDEF_SELECT ) );
 if ( rw_ndef_t4t_ndef.mapping_version == 0x10 ) rsp[3] = 0x00;
 rsp[5] = rw_ndef_t4t_ndef.file_id[0];
 rsp[6] = rw_ndef_t4t_ndef.file_id[1];
 *p_rsp_size = sizeof( RW_NDEF_T4T_NDEF_SELECT );
 e_rw_ndef_t4t_state = SELECTING_NDEF;
 }
 break;

 case SELECTING_NDEF:

 if ( !memcmp( &p_cmd[cmd_size - 2], ( uint8_t * )RW_NDEF_T4T_OK,
 sizeof( RW_NDEF_T4T_OK ) ) )
 {

 memcpy( rsp, ( uint8_t * )RW_NDEF_T4T_READ, sizeof( RW_NDEF_T4T_READ ) );
 *p_rsp_size = sizeof( RW_NDEF_T4T_READ );
 rsp[4] = 2;
 e_rw_ndef_t4t_state = READING_NDEF_SIZE;
 }
 break;

 case READING_NDEF_SIZE:

 if ( !memcmp( &p_cmd[cmd_size - 2], ( uint8_t * )RW_NDEF_T4T_OK,
 sizeof( RW_NDEF_T4T_OK ) ) )
 {
 rw_ndef_t4t_ndef.record_size = ( p_cmd[0] << 8 ) + p_cmd[1];
 if( rw_ndef_t4t_ndef.record_size >  240  )
 {

 }
 else
 {
 rw_ndef_t4t_ndef.record_ptr = 0;


 memcpy( rsp, ( uint8_t * )RW_NDEF_T4T_READ, sizeof( RW_NDEF_T4T_READ ) );
 rsp[3] = 2;
 rsp[4] = ( rw_ndef_t4t_ndef.record_size > rw_ndef_t4t_ndef.mle - 1 ) ?
 rw_ndef_t4t_ndef.mle - 1 : ( uint8_t ) rw_ndef_t4t_ndef.record_size;
 *p_rsp_size = sizeof( RW_NDEF_T4T_READ );
 e_rw_ndef_t4t_state = READING_NDEF;
 }
 }
 break;

 case READING_NDEF:

 if ( !memcmp( &p_cmd[cmd_size - 2], ( uint8_t * )RW_NDEF_T4T_OK,
 sizeof( RW_NDEF_T4T_OK ) ) )
 {
 memcpy( &rw_ndef_t4t_ndef.p_record[rw_ndef_t4t_ndef.record_ptr], p_cmd,
 cmd_size - 2 );
 rw_ndef_t4t_ndef.record_ptr += cmd_size - 2;


 if ( rw_ndef_t4t_ndef.record_ptr == rw_ndef_t4t_ndef.record_size )
 {

 if( p_rw_ndef_pull_cb !=  ((void *)0)  ) p_rw_ndef_pull_cb( rw_ndef_t4t_ndef.p_record,
 rw_ndef_t4t_ndef.record_size );
 }
 else
 {

 memcpy( rsp, ( uint8_t * )RW_NDEF_T4T_READ, sizeof( RW_NDEF_T4T_READ ) );
 rsp[3] = rw_ndef_t4t_ndef.record_ptr + 2;
 rsp[4] = ( ( rw_ndef_t4t_ndef.record_size - rw_ndef_t4t_ndef.record_ptr ) >
 rw_ndef_t4t_ndef.mle - 1 ) ? rw_ndef_t4t_ndef.mle - 1 : ( uint8_t ) (
 rw_ndef_t4t_ndef.record_size - rw_ndef_t4t_ndef.record_ptr );
 *p_rsp_size = sizeof( RW_NDEF_T4T_READ );
 }
 }
 break;

 default:
 break;
 }
}

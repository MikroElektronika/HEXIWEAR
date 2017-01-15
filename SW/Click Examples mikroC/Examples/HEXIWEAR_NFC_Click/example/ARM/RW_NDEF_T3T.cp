#line 1 "//VBOXSVR/storage/git/MikroE/HEXIWEAR/SW/Click Examples mikroC/2.Examples/HEXIWEAR_NFC_Click/example/ARM/RW_NDEF_T3T.c"
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
#line 1 "c:/c4w/mikroc pro for arm/include/stddef.h"



typedef long ptrdiff_t;


 typedef unsigned long size_t;

typedef unsigned long wchar_t;
#line 1 "//vboxsvr/storage/git/mikroe/hexiwear/sw/click examples mikroc/2.examples/hexiwear_nfc_click/example/arm/rw_ndef.h"
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
#line 60 "//vboxsvr/storage/git/mikroe/hexiwear/sw/click examples mikroc/2.examples/hexiwear_nfc_click/example/arm/rw_ndef.h"
typedef void rw_ndef_callback_t( uint8_t *, uint16_t );
#line 65 "//vboxsvr/storage/git/mikroe/hexiwear/sw/click examples mikroc/2.examples/hexiwear_nfc_click/example/arm/rw_ndef.h"
extern uint8_t ndef_buffer[ 240 ];
extern rw_ndef_callback_t *p_rw_ndef_pull_cb;
#line 79 "//vboxsvr/storage/git/mikroe/hexiwear/sw/click examples mikroc/2.examples/hexiwear_nfc_click/example/arm/rw_ndef.h"
void rw_ndef_register_pull_callback( void *p_cb );
#line 85 "//vboxsvr/storage/git/mikroe/hexiwear/sw/click examples mikroc/2.examples/hexiwear_nfc_click/example/arm/rw_ndef.h"
void rw_ndef_reset( uint8_t type );
#line 94 "//vboxsvr/storage/git/mikroe/hexiwear/sw/click examples mikroc/2.examples/hexiwear_nfc_click/example/arm/rw_ndef.h"
void rw_ndef_read_next( uint8_t *p_cmd, uint16_t cmd_size,
 uint8_t *rsp, uint16_t *p_rsp_size );
#line 38 "//VBOXSVR/storage/git/MikroE/HEXIWEAR/SW/Click Examples mikroC/2.Examples/HEXIWEAR_NFC_Click/example/ARM/RW_NDEF_T3T.c"
typedef enum
{
 INITIAL,
 GETTING_ATTRIBUTE_INFO,
 READING_CARD_CONTENT
} rw_ndef_t3t_state_t;

typedef struct
{
 uint8_t id_m[8];
 uint8_t blk_nb;
 uint16_t record_ptr;
 uint16_t record_size;
 uint8_t *p_record;
} rw_ndef_t3t_ndef_t;
#line 57 "//VBOXSVR/storage/git/MikroE/HEXIWEAR/SW/Click Examples mikroC/2.Examples/HEXIWEAR_NFC_Click/example/ARM/RW_NDEF_T3T.c"
static uint8_t T3T_CHECK[] =
{
 0x10, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x0B,
 0x00, 0x1, 0x80, 0x00
};

static rw_ndef_t3t_state_t e_rw_ndef_t3t_state = INITIAL;
static rw_ndef_t3t_ndef_t rw_ndef_t3t_ndef;
#line 73 "//VBOXSVR/storage/git/MikroE/HEXIWEAR/SW/Click Examples mikroC/2.Examples/HEXIWEAR_NFC_Click/example/ARM/RW_NDEF_T3T.c"
void rw_ndef_t3t_reset( void )
{
 e_rw_ndef_t3t_state = INITIAL;
 rw_ndef_t3t_ndef.p_record = ndef_buffer;
}

void rw_ndef_t3t_set_id_m( uint8_t *pIDm )
{
 memcpy( rw_ndef_t3t_ndef.id_m, pIDm, sizeof( rw_ndef_t3t_ndef.id_m ) );
 memcpy( &T3T_CHECK[2], pIDm, sizeof( rw_ndef_t3t_ndef.id_m ) );
}

void rw_ndef_t3t_read_next( uint8_t *p_rsp, uint16_t rsp_size,
 uint8_t *p_cmd, uint16_t *p_cmd_size )
{

 *p_cmd_size = 0;

 switch( e_rw_ndef_t3t_state )
 {
 case INITIAL:

 memcpy ( p_cmd, T3T_CHECK, sizeof( T3T_CHECK ) );
 *p_cmd_size = sizeof( T3T_CHECK );
 e_rw_ndef_t3t_state = GETTING_ATTRIBUTE_INFO;
 break;

 case GETTING_ATTRIBUTE_INFO:

 if ( ( p_rsp[rsp_size - 1] == 0x00 ) && ( p_rsp[1] == 0x07 ) &&
 ( p_rsp[10] == 0x00 ) && ( p_rsp[11] == 0x00 ) )
 {

 rw_ndef_t3t_ndef.record_size = ( p_rsp[24] << 16 ) + ( p_rsp[25] << 16 ) +
 p_rsp[26];

 if( rw_ndef_t3t_ndef.record_size >  240  )
 {

 } else {
 rw_ndef_t3t_ndef.record_ptr = 0;
 rw_ndef_t3t_ndef.blk_nb = 1;


 memcpy ( p_cmd, T3T_CHECK, sizeof( T3T_CHECK ) );
 p_cmd[15] = 0x01;
 *p_cmd_size = sizeof( T3T_CHECK );
 e_rw_ndef_t3t_state = READING_CARD_CONTENT;
 }
 }
 break;

 case READING_CARD_CONTENT:

 if ( ( p_rsp[rsp_size - 1] == 0x00 ) && ( p_rsp[1] == 0x07 ) &&
 ( p_rsp[10] == 0x00 ) && ( p_rsp[11] == 0x00 ) )
 {

 if ( ( rw_ndef_t3t_ndef.record_size - rw_ndef_t3t_ndef.record_ptr ) <= 16 )
 {
 memcpy( &rw_ndef_t3t_ndef.p_record[rw_ndef_t3t_ndef.record_ptr], &p_rsp[13],
 ( rw_ndef_t3t_ndef.record_size - rw_ndef_t3t_ndef.record_ptr ) );

 if( p_rw_ndef_pull_cb !=  ((void *)0)  ) p_rw_ndef_pull_cb( rw_ndef_t3t_ndef.p_record,
 rw_ndef_t3t_ndef.record_size );
 } else {
 memcpy( &rw_ndef_t3t_ndef.p_record[rw_ndef_t3t_ndef.record_ptr], &p_rsp[13],
 16 );
 rw_ndef_t3t_ndef.record_ptr += 16;
 rw_ndef_t3t_ndef.blk_nb++;


 memcpy ( p_cmd, T3T_CHECK, sizeof( T3T_CHECK ) );
 p_cmd[15] = rw_ndef_t3t_ndef.blk_nb;
 *p_cmd_size = sizeof( T3T_CHECK );
 }
 }
 break;

 default:
 break;
 }
}

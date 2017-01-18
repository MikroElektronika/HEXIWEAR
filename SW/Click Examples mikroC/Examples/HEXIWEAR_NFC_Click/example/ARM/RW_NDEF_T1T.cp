#line 1 "//VBOXSVR/storage/git/MikroE/HEXIWEAR/SW/Click Examples mikroC/2.Examples/HEXIWEAR_NFC_Click/example/ARM/RW_NDEF_T1T.c"
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
#line 38 "//VBOXSVR/storage/git/MikroE/HEXIWEAR/SW/Click Examples mikroC/2.Examples/HEXIWEAR_NFC_Click/example/ARM/RW_NDEF_T1T.c"
typedef enum
{
 INITIAL,
 GETTING_ID,
 READING_CARD_CONTENT,
 READING_NDEF
} rw_ndef_t1t_state_t;

typedef struct
{
 uint8_t hr0;
 uint8_t hr1;
 uint8_t uid[4];
 uint8_t blk_nb;
 uint16_t record_ptr;
 uint16_t record_size;
 uint8_t *p_record;
} rw_ndef_t1t_ndef_t;
#line 60 "//VBOXSVR/storage/git/MikroE/HEXIWEAR/SW/Click Examples mikroC/2.Examples/HEXIWEAR_NFC_Click/example/ARM/RW_NDEF_T1T.c"
static const uint8_t T1T_RID[] = {0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
static const uint8_t T1T_RALL[] = {0x00, 0x00, 0x00};
static const uint8_t T1T_READ8[] =
{
 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static rw_ndef_t1t_state_t e_rw_ndef_t1t_state = INITIAL;
static rw_ndef_t1t_ndef_t rw_ndef_t1t_ndef;
#line 77 "//VBOXSVR/storage/git/MikroE/HEXIWEAR/SW/Click Examples mikroC/2.Examples/HEXIWEAR_NFC_Click/example/ARM/RW_NDEF_T1T.c"
void rw_ndef_t1t_reset( void )
{
 e_rw_ndef_t1t_state = INITIAL;
 rw_ndef_t1t_ndef.p_record = ndef_buffer;
}

void rw_ndef_t1t_read_next( uint8_t *p_cmd, uint16_t cmd_size,
 uint8_t *rsp, uint16_t *p_rsp_size )
{

 *p_rsp_size = 0;

 switch( e_rw_ndef_t1t_state )
 {
 case INITIAL:

 memcpy( rsp, ( uint8_t * )T1T_RID, sizeof( T1T_RID ) );
 *p_rsp_size = 7;
 e_rw_ndef_t1t_state = GETTING_ID;
 break;

 case GETTING_ID:

 if ( ( cmd_size == 7 ) && ( p_cmd[cmd_size - 1] == 0x00 ) )
 {

 rw_ndef_t1t_ndef.hr0 = p_cmd[0];
 rw_ndef_t1t_ndef.hr1 = p_cmd[1];
 memcpy( rw_ndef_t1t_ndef.uid, &p_cmd[2], sizeof( rw_ndef_t1t_ndef.uid ) );


 memcpy( rsp, ( uint8_t * )T1T_RALL, sizeof( T1T_RALL ) );
 memcpy( &rsp[3], rw_ndef_t1t_ndef.uid, sizeof( rw_ndef_t1t_ndef.uid ) );
 *p_rsp_size = sizeof( T1T_RALL ) + sizeof( rw_ndef_t1t_ndef.uid );
 e_rw_ndef_t1t_state = READING_CARD_CONTENT;
 }
 break;

 case READING_CARD_CONTENT:

 if ( ( cmd_size == 123 ) && ( p_cmd[cmd_size - 1] == 0x00 ) )
 {

 if ( p_cmd[10] ==  0xE1  )
 {
 uint8_t tmp = 14;
 uint8_t data_size;


 while ( p_cmd[tmp] !=  0x03  )
 {
 tmp += 2 + p_cmd[tmp + 1];
 if ( tmp > cmd_size ) return;
 }

 rw_ndef_t1t_ndef.record_size = p_cmd[tmp + 1];
 data_size = ( cmd_size - 1 ) - 16 - tmp - 2;


 if( rw_ndef_t1t_ndef.record_size <= data_size )
 {
 memcpy( rw_ndef_t1t_ndef.p_record, &p_cmd[tmp + 2],
 rw_ndef_t1t_ndef.record_size );


 if( p_rw_ndef_pull_cb !=  ((void *)0)  )
 p_rw_ndef_pull_cb( rw_ndef_t1t_ndef.p_record,
 rw_ndef_t1t_ndef.record_size );
 } else {
 rw_ndef_t1t_ndef.record_ptr = data_size;
 memcpy( rw_ndef_t1t_ndef.p_record, &p_cmd[tmp + 2],
 rw_ndef_t1t_ndef.record_ptr );
 rw_ndef_t1t_ndef.blk_nb = 0x10;


 memcpy( rsp, ( uint8_t * )T1T_READ8, sizeof( T1T_READ8 ) );
 rsp[1] = rw_ndef_t1t_ndef.blk_nb;
 memcpy( &rsp[10], rw_ndef_t1t_ndef.uid, sizeof( rw_ndef_t1t_ndef.uid ) );
 *p_rsp_size = sizeof( T1T_READ8 ) + sizeof( rw_ndef_t1t_ndef.uid );

 e_rw_ndef_t1t_state = READING_NDEF;
 }
 }
 }
 break;

 case READING_NDEF:

 if ( ( cmd_size == 10 ) && ( p_cmd[cmd_size - 1] == 0x00 ) )
 {

 if ( ( rw_ndef_t1t_ndef.record_size - rw_ndef_t1t_ndef.record_ptr ) < 8 )
 {
 memcpy ( &rw_ndef_t1t_ndef.p_record[rw_ndef_t1t_ndef.record_ptr], &p_cmd[1],
 rw_ndef_t1t_ndef.record_size - rw_ndef_t1t_ndef.record_ptr );


 if( p_rw_ndef_pull_cb !=  ((void *)0)  ) p_rw_ndef_pull_cb( rw_ndef_t1t_ndef.p_record,
 rw_ndef_t1t_ndef.record_size );
 }
 else
 {
 memcpy ( &rw_ndef_t1t_ndef.p_record[rw_ndef_t1t_ndef.record_ptr], &p_cmd[1], 8 );
 rw_ndef_t1t_ndef.record_ptr += 8;
 rw_ndef_t1t_ndef.blk_nb++;


 memcpy ( rsp, ( uint8_t * )T1T_READ8, sizeof( T1T_READ8 ) );
 rsp[1] = rw_ndef_t1t_ndef.blk_nb;
 memcpy ( &rsp[10], rw_ndef_t1t_ndef.uid, sizeof( rw_ndef_t1t_ndef.uid ) );
 *p_rsp_size = sizeof( T1T_READ8 ) + sizeof( rw_ndef_t1t_ndef.uid );
 }
 }
 break;

 default:
 break;
 }
}

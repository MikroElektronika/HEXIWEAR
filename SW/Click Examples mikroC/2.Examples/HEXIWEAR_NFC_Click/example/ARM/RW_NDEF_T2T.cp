#line 1 "E:/Darko/Projekti/HEXIWEAR/Click Demo/Projekti/HEXIWEAR_NFC_Click/example/ARM/RW_NDEF_T2T.c"
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
#line 40 "E:/Darko/Projekti/HEXIWEAR/Click Demo/Projekti/HEXIWEAR_NFC_Click/example/ARM/RW_NDEF_T2T.c"
typedef enum
{
 INITIAL,
 READING_CC,
 READING_DATA,
 READING_NDEF
} rw_ndef_t2t_state_t;

typedef struct
{
 uint8_t blk_nb;
 uint16_t record_ptr;
 uint16_t record_size;
 uint8_t *p_record;
} rw_ndef_t2t_ndef_t;
#line 59 "E:/Darko/Projekti/HEXIWEAR/Click Demo/Projekti/HEXIWEAR_NFC_Click/example/ARM/RW_NDEF_T2T.c"
static rw_ndef_t2t_state_t e_rw_ndef_t2t_state = INITIAL;
static rw_ndef_t2t_ndef_t rw_ndef_t2t_ndef;
#line 69 "E:/Darko/Projekti/HEXIWEAR/Click Demo/Projekti/HEXIWEAR_NFC_Click/example/ARM/RW_NDEF_T2T.c"
void rw_ndef_t2t_reset( void )
{
 e_rw_ndef_t2t_state = INITIAL;
 rw_ndef_t2t_ndef.p_record = ndef_buffer;
}

void rw_ndef_t2t_read_next(uint8_t *p_cmd, uint16_t cmd_size,
 uint8_t *rsp, uint16_t *p_rsp_size )
{

 *p_rsp_size = 0;

 switch( e_rw_ndef_t2t_state )
 {
 case INITIAL:

 rsp[0] = 0x30;
 rsp[1] = 0x03;
 *p_rsp_size = 2;
 e_rw_ndef_t2t_state = READING_CC;
 break;

 case READING_CC:

 if ( ( cmd_size == 17 ) && ( p_cmd[cmd_size - 1] == 0x00 ) &&
 ( p_cmd[0] ==  0xE1  ) )
 {

 rsp[0] = 0x30;
 rsp[1] = 0x04;
 *p_rsp_size = 2;

 e_rw_ndef_t2t_state = READING_DATA;
 }
 break;

 case READING_DATA:

 if ( ( cmd_size == 17 ) && ( p_cmd[cmd_size - 1] == 0x00 ) )
 {
 uint8_t Tmp = 0;

 while ( p_cmd[Tmp] !=  0x03  )
 {
 Tmp += 2 + p_cmd[Tmp + 1];
 if ( Tmp > cmd_size ) return;
 }

 if( p_cmd[Tmp + 1] == 0xFF ) rw_ndef_t2t_ndef.record_size =
 ( p_cmd[Tmp + 2] << 8 ) + p_cmd[Tmp + 3];
 else rw_ndef_t2t_ndef.record_size = p_cmd[Tmp + 1];


 if ( rw_ndef_t2t_ndef.record_size <= ( ( cmd_size - 1 ) - Tmp - 2 ) )
 {
 memcpy ( rw_ndef_t2t_ndef.p_record, &p_cmd[Tmp + 2],
 rw_ndef_t2t_ndef.record_size );


 if( p_rw_ndef_pull_cb !=  ((void *)0)  ) p_rw_ndef_pull_cb( rw_ndef_t2t_ndef.p_record,
 rw_ndef_t2t_ndef.record_size );
 }
 else
 {
 rw_ndef_t2t_ndef.record_ptr = ( cmd_size - 1 ) - Tmp - 2;
 memcpy ( rw_ndef_t2t_ndef.p_record, &p_cmd[Tmp + 2],
 rw_ndef_t2t_ndef.record_ptr );
 rw_ndef_t2t_ndef.blk_nb = 8;


 rsp[0] = 0x30;
 rsp[1] = rw_ndef_t2t_ndef.blk_nb;
 *p_rsp_size = 2;
 e_rw_ndef_t2t_state = READING_NDEF;
 }
 }
 break;

 case READING_NDEF:

 if ( ( cmd_size == 17 ) && ( p_cmd[cmd_size - 1] == 0x00 ) )
 {

 if ( ( rw_ndef_t2t_ndef.record_size - rw_ndef_t2t_ndef.record_ptr ) < 16 )
 {
 memcpy ( &rw_ndef_t2t_ndef.p_record[rw_ndef_t2t_ndef.record_ptr], p_cmd,
 rw_ndef_t2t_ndef.record_size - rw_ndef_t2t_ndef.record_ptr );


 if( p_rw_ndef_pull_cb !=  ((void *)0)  ) p_rw_ndef_pull_cb( rw_ndef_t2t_ndef.p_record,
 rw_ndef_t2t_ndef.record_size );
 }
 else
 {
 memcpy ( &rw_ndef_t2t_ndef.p_record[rw_ndef_t2t_ndef.record_ptr], p_cmd, 16 );
 rw_ndef_t2t_ndef.record_ptr += 16;
 rw_ndef_t2t_ndef.blk_nb += 4;


 rsp[0] = 0x30;
 rsp[1] = rw_ndef_t2t_ndef.blk_nb;
 *p_rsp_size = 2;
 }
 }
 break;

 default:
 break;
 }
}

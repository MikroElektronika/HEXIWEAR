#line 1 "E:/Darko/Projekti/HEXIWEAR/Click Demo/Projekti/HEXIWEAR_NFC_Click/example/ARM/RW_NDEF.c"
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
#line 1 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_nfc_click/example/arm/rw_ndef_t1t.h"
#line 1 "c:/users/public/documents/mikroelektronika/arm/radni/mikroc pro for arm/include/stdint.h"
#line 74 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_nfc_click/example/arm/rw_ndef_t1t.h"
void rw_ndef_t1t_reset( void );
#line 83 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_nfc_click/example/arm/rw_ndef_t1t.h"
void rw_ndef_t1t_read_next( uint8_t *p_cmd, uint16_t cmd_size,
 uint8_t *rsp, uint16_t *p_rsp_size );
#line 1 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_nfc_click/example/arm/rw_ndef_t2t.h"
#line 1 "c:/users/public/documents/mikroelektronika/arm/radni/mikroc pro for arm/include/stdint.h"
#line 75 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_nfc_click/example/arm/rw_ndef_t2t.h"
void rw_ndef_t2t_reset( void );
#line 84 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_nfc_click/example/arm/rw_ndef_t2t.h"
void rw_ndef_t2t_read_next( uint8_t *p_cmd, uint16_t cmd_size,
 uint8_t *rsp, uint16_t *p_rsp_size );
#line 1 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_nfc_click/example/arm/rw_ndef_t3t.h"
#line 1 "c:/users/public/documents/mikroelektronika/arm/radni/mikroc pro for arm/include/stdint.h"
#line 75 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_nfc_click/example/arm/rw_ndef_t3t.h"
void rw_ndef_t3t_reset( void );
#line 81 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_nfc_click/example/arm/rw_ndef_t3t.h"
void rw_ndef_t3t_set_id_m( uint8_t *p_id_m );
#line 90 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_nfc_click/example/arm/rw_ndef_t3t.h"
void rw_ndef_t3t_read_next( uint8_t *p_cmd, uint16_t cmd_size,
 uint8_t *rsp, uint16_t *p_rsp_size );
#line 1 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_nfc_click/example/arm/rw_ndef_t4t.h"
#line 1 "c:/users/public/documents/mikroelektronika/arm/radni/mikroc pro for arm/include/stdint.h"
#line 75 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_nfc_click/example/arm/rw_ndef_t4t.h"
void rw_ndef_t4t_reset( void );
#line 84 "e:/darko/projekti/hexiwear/click demo/projekti/hexiwear_nfc_click/example/arm/rw_ndef_t4t.h"
void rw_ndef_t4t_read_next( uint8_t *p_cmd, uint16_t cmd_size,
 uint8_t *rsp, uint16_t *p_rsp_size );
#line 40 "E:/Darko/Projekti/HEXIWEAR/Click Demo/Projekti/HEXIWEAR_NFC_Click/example/ARM/RW_NDEF.c"
typedef void rw_ndef_read_fct_t( uint8_t *p_cmd, uint16_t cmd_size,
 uint8_t *rsp, uint16_t *p_rsp_size );
#line 47 "E:/Darko/Projekti/HEXIWEAR/Click Demo/Projekti/HEXIWEAR_NFC_Click/example/ARM/RW_NDEF.c"
uint8_t ndef_buffer[ 240 ];

static rw_ndef_read_fct_t *p_read_fct =  ((void *)0) ;

rw_ndef_callback_t *p_rw_ndef_pull_cb;
#line 60 "E:/Darko/Projekti/HEXIWEAR/Click Demo/Projekti/HEXIWEAR_NFC_Click/example/ARM/RW_NDEF.c"
void rw_ndef_register_pull_callback( void *p_cb )
{
 p_rw_ndef_pull_cb = ( rw_ndef_callback_t * ) p_cb;
}

void rw_ndef_reset(uint8_t type )
{
 switch ( type )
 {
 case  0x1 :
 rw_ndef_t1t_reset();
 p_read_fct = rw_ndef_t1t_read_next;
 break;
 case  0x2 :
 rw_ndef_t2t_reset();
 p_read_fct = rw_ndef_t2t_read_next;
 break;
 case  0x3 :
 rw_ndef_t3t_reset();
 p_read_fct = rw_ndef_t3t_read_next;
 break;
 case  0x4 :
 rw_ndef_t4t_reset();
 p_read_fct = rw_ndef_t4t_read_next;
 break;
 default:
 p_read_fct =  ((void *)0) ;
 break;
 }
}

void rw_ndef_read_next( uint8_t *p_cmd, uint16_t cmd_size,
 uint8_t *rsp, uint16_t *p_rsp_size )
{
 if( p_read_fct !=  ((void *)0)  )
 p_read_fct( p_cmd, cmd_size, rsp, p_rsp_size );
}

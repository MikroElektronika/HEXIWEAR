#line 1 "//VBOXSVR/storage/git/MikroE/HEXIWEAR/SW/Click Examples mikroC/2.Examples/HEXIWEAR_NFC_Click/example/ARM/P2P_NDEF.c"
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
#line 1 "//vboxsvr/storage/git/mikroe/hexiwear/sw/click examples mikroc/2.examples/hexiwear_nfc_click/example/arm/p2p_ndef.h"
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
#line 1 "c:/c4w/mikroc pro for arm/include/stdbool.h"



 typedef char _Bool;
#line 72 "//vboxsvr/storage/git/mikroe/hexiwear/sw/click examples mikroc/2.examples/hexiwear_nfc_click/example/arm/p2p_ndef.h"
void p2p_ndef_reset( void );
void p2p_ndef_next( uint8_t *p_cmd, uint16_t cmd_size,
 uint8_t *rsp, uint16_t *p_rsp_size );
 _Bool  p2p_ndef_set_record( uint8_t *p_record, uint16_t record_size,
 void *cb );
void p2p_ndef_register_pull_callback( void *p_cb );
#line 1 "//vboxsvr/storage/git/mikroe/hexiwear/sw/click examples mikroc/2.examples/hexiwear_nfc_click/example/arm/nfc_hal.h"
#line 1 "c:/c4w/mikroc pro for arm/include/stdint.h"
#line 69 "//vboxsvr/storage/git/mikroe/hexiwear/sw/click examples mikroc/2.examples/hexiwear_nfc_click/example/arm/nfc_hal.h"
void nfc_hal_init( uint8_t address_id );

void nfc_hal_delay( uint16_t ms );

void nfc_hal_reset( void );

int nfc_hal_write( uint8_t *data_out, uint16_t count );

int nfc_hal_read( uint8_t *data_in, uint16_t *nbytes_read,
 uint16_t count );
#line 69 "//VBOXSVR/storage/git/MikroE/HEXIWEAR/SW/Click Examples mikroC/2.Examples/HEXIWEAR_NFC_Click/example/ARM/P2P_NDEF.c"
typedef enum
{
 IDLE_STATE,
 INITIAL,
 DELAYING_PUSH,
 INITIATE_PUSH,
 SNEP_CLIENT_CONNECTING,
 SNEP_CLIENT_CONNECTED,
 NDEF_MSG_SENT
} p2p_snep_client_state_t;

typedef struct
{
 uint8_t dsap;
 uint8_t pdu;
 uint8_t ssap;
} p2p_ndef_llcp_header_t;

typedef void p2p_ndef_callback_t ( uint8_t *, uint16_t );
#line 92 "//VBOXSVR/storage/git/MikroE/HEXIWEAR/SW/Click Examples mikroC/2.Examples/HEXIWEAR_NFC_Click/example/ARM/P2P_NDEF.c"
static const uint8_t SNEP_PUT_SUCCESS[] = { 0x10 ,  0x81 , 0x00, 0x00, 0x00, 0x00};
static const uint8_t LLCP_CONNECT_SNEP[] = {0x11, 0x20};
static const uint8_t LLCP_I_SNEP_PUT_HEADER[] = { 0x10 ,  0x2 , 0x00, 0x00, 0x00, 0x00};
static const uint8_t LLCP_SYMM[] = {0x00, 0x00};

static uint8_t *p_ndef_record;
static uint16_t ndef_record_size = 0;

static p2p_snep_client_state_t e_p2p_snep_client_state = INITIAL;
static p2p_ndef_callback_t *p_p2p_ndef_push_cb =  ((void *)0) ;
static p2p_ndef_callback_t *p_p2p_ndef_pull_cb =  ((void *)0) ;
static uint16_t p2p_snep_client_delay_count =  1 ;
#line 108 "//VBOXSVR/storage/git/MikroE/HEXIWEAR/SW/Click Examples mikroC/2.Examples/HEXIWEAR_NFC_Click/example/ARM/P2P_NDEF.c"
static void parse_llcp( uint8_t *p_buf,
 p2p_ndef_llcp_header_t *p_llcp_header );

static void fill_llcp( p2p_ndef_llcp_header_t llcp_header, uint8_t *p_buf );
#line 116 "//VBOXSVR/storage/git/MikroE/HEXIWEAR/SW/Click Examples mikroC/2.Examples/HEXIWEAR_NFC_Click/example/ARM/P2P_NDEF.c"
static void parse_llcp( uint8_t *p_buf,
 p2p_ndef_llcp_header_t *p_llcp_header )
{
 p_llcp_header->dsap = p_buf[0] >> 2;
 p_llcp_header->pdu = ( ( p_buf[0] & 3 ) << 2 ) + ( p_buf[1] >> 6 );
 p_llcp_header->ssap = p_buf[1] & 0x3F;
}

static void fill_llcp( p2p_ndef_llcp_header_t llcp_header, uint8_t *p_buf )
{
 p_buf[0] = ( llcp_header.ssap << 2 ) + ( ( llcp_header.pdu >> 2 ) & 3 );
 p_buf[1] = ( llcp_header.pdu << 6 ) + llcp_header.dsap;
}

 _Bool  p2p_ndef_set_record( uint8_t *p_record,
 uint16_t record_size, void *cb )
{
 if ( record_size <=  240  )
 {
 p_ndef_record = p_record;
 ndef_record_size = record_size;
 p_p2p_ndef_push_cb = ( p2p_ndef_callback_t * ) cb;
 return  1 ;
 }
 else
 {
 ndef_record_size = 0;
 p_p2p_ndef_push_cb =  ((void *)0) ;
 return  0 ;
 }
}

void p2p_ndef_register_pull_callback( void *p_cb )
{
 p_p2p_ndef_pull_cb = ( p2p_ndef_callback_t * ) p_cb;
}

void p2p_ndef_reset( void )
{
 if ( ndef_record_size != 0 )
 e_p2p_snep_client_state = INITIAL;
 else
 e_p2p_snep_client_state = IDLE_STATE;
}

void p2p_ndef_next( uint8_t *p_cmd, uint16_t cmd_size,
 uint8_t *p_rsp, uint16_t *p_rsp_size )
{
 p2p_ndef_llcp_header_t llcp_header;


 *p_rsp_size = 0;

 parse_llcp( p_cmd, &llcp_header );

 switch ( llcp_header.pdu )
 {
 case  0x4 :

 if ( llcp_header.dsap ==  4  )
 {

 if( p_p2p_ndef_pull_cb !=  ((void *)0)  )
 {
 llcp_header.pdu =  0x6 ;
 fill_llcp( llcp_header, p_rsp );
 *p_rsp_size = 2;
 }
 } else {

 llcp_header.pdu =  0x7 ;
 fill_llcp( llcp_header, p_rsp );
 *p_rsp_size = 2;
 }
 break;
 case  0xC :

 if ( ( p_cmd[3] ==  0x10  ) && ( p_cmd[4] ==  0x2  ) )
 {

 if( p_p2p_ndef_pull_cb !=  ((void *)0)  ) p_p2p_ndef_pull_cb( &p_cmd[9], p_cmd[8] );


 llcp_header.pdu =  0xC ;
 fill_llcp( llcp_header, p_rsp );
 p_rsp[2] = ( p_cmd[2] >> 4 ) + 1;
 memcpy( &p_rsp[3], ( uint8_t * )SNEP_PUT_SUCCESS, sizeof( SNEP_PUT_SUCCESS ) );
 *p_rsp_size = 9;
 }
 break;
 case  0x6 :

 e_p2p_snep_client_state = SNEP_CLIENT_CONNECTED;
 break;
 default:
 break;

 }


 if( *p_rsp_size == 0 )
 {
 switch( e_p2p_snep_client_state )
 {
 case INITIATE_PUSH:
 memcpy( p_rsp, ( uint8_t * )LLCP_CONNECT_SNEP, sizeof( LLCP_CONNECT_SNEP ) );
 *p_rsp_size = sizeof( LLCP_CONNECT_SNEP );
 e_p2p_snep_client_state = SNEP_CLIENT_CONNECTING;
 break;

 case SNEP_CLIENT_CONNECTED:
 llcp_header.pdu =  0xC ;
 fill_llcp( llcp_header, p_rsp );
 p_rsp[2] = 0;
 p_rsp[3] =  0x10 ;
 p_rsp[4] =  0x2 ;
 p_rsp[5] = 0;
 p_rsp[6] = 0;
 p_rsp[7] = 0;
 p_rsp[8] = ndef_record_size;
 memcpy( &p_rsp[9], p_ndef_record, ndef_record_size );
 *p_rsp_size = 9 + ndef_record_size;
 e_p2p_snep_client_state = NDEF_MSG_SENT;

 if( p_p2p_ndef_push_cb !=  ((void *)0)  )
 p_p2p_ndef_push_cb( p_ndef_record,
 ndef_record_size );
 break;
 case DELAYING_PUSH:
 p2p_snep_client_delay_count++;
 if( p2p_snep_client_delay_count ==  1  )
 e_p2p_snep_client_state = INITIATE_PUSH;

 nfc_hal_delay( 1000 );
 memcpy( p_rsp, ( uint8_t * )LLCP_SYMM, sizeof( LLCP_SYMM ) );
 *p_rsp_size = sizeof( LLCP_SYMM );
 break;

 case INITIAL:
 p2p_snep_client_delay_count = 0;
 e_p2p_snep_client_state = DELAYING_PUSH;
 default:

 nfc_hal_delay (  500  );
 memcpy( p_rsp, ( uint8_t * )LLCP_SYMM, sizeof( LLCP_SYMM ) );
 *p_rsp_size = sizeof( LLCP_SYMM );
 break;
 }
 }
}

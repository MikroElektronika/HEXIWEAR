#line 1 "E:/git/ClickLab/NFC_Tag2_click/example/HEXI/NT2_HEXI.c"
#line 1 "e:/git/clicklab/nfc_tag2_click/library/include/nfc_tag2.h"
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for arm/include/stdbool.h"



 typedef char _Bool;
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for arm/include/string.h"





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
#line 198 "e:/git/clicklab/nfc_tag2_click/library/include/nfc_tag2.h"
typedef enum {

 NT2_SET_SERIAL_NO = 0,
 NT2_SET_STATIC_LOCK = 1,
 NT2_SET_CAP_CONTAINER = 2,
 NT2_SET_DYNAMIC_LOCK = 3,
 NT2_SET_SRAM_MEMORY = 4

}NFCTAG2_SET;
#line 229 "e:/git/clicklab/nfc_tag2_click/library/include/nfc_tag2.h"
typedef enum {

 NT2_CFG_NC_REG = 0,
 NT2_CFG_LAST_NDEF = 1,
 NT2_CFG_SRAM_MIRROR = 2,
 NT2_CFG_WDT_LS = 3,
 NT2_CFG_WDT_MS = 4,
 NT2_CFG_STR = 5,
 NT2_CFG_LOCK = 6,
 NT2_SES_NS_REG = 6,

}NFCTAG2_CFG;
#line 250 "e:/git/clicklab/nfc_tag2_click/library/include/nfc_tag2.h"
typedef struct {
#line 254 "e:/git/clicklab/nfc_tag2_click/library/include/nfc_tag2.h"
 uint8_t i2c_address;
#line 257 "e:/git/clicklab/nfc_tag2_click/library/include/nfc_tag2.h"
 uint8_t serial_num[  7  ];
#line 260 "e:/git/clicklab/nfc_tag2_click/library/include/nfc_tag2.h"
 uint8_t static_lock[  2  ];
#line 263 "e:/git/clicklab/nfc_tag2_click/library/include/nfc_tag2.h"
 uint8_t dynamic_lock[  3  ];
#line 266 "e:/git/clicklab/nfc_tag2_click/library/include/nfc_tag2.h"
 uint8_t cap_containter[  4  ];
#line 269 "e:/git/clicklab/nfc_tag2_click/library/include/nfc_tag2.h"
 uint8_t sram_memory[  64  ];
#line 272 "e:/git/clicklab/nfc_tag2_click/library/include/nfc_tag2.h"
 uint8_t config[  8  ];
#line 275 "e:/git/clicklab/nfc_tag2_click/library/include/nfc_tag2.h"
 uint8_t session[  8  ];
#line 278 "e:/git/clicklab/nfc_tag2_click/library/include/nfc_tag2.h"
 uint8_t user_memory[  888  ];

}nfctag2_click;
#line 303 "e:/git/clicklab/nfc_tag2_click/library/include/nfc_tag2.h"
int nfctag2_init( uint8_t i2c_address );
#line 321 "e:/git/clicklab/nfc_tag2_click/library/include/nfc_tag2.h"
int nfctag2_i2c_addres( uint8_t new_address );
#line 338 "e:/git/clicklab/nfc_tag2_click/library/include/nfc_tag2.h"
int nfctag2_get( NFCTAG2_SET setting, uint8_t *output );
#line 361 "e:/git/clicklab/nfc_tag2_click/library/include/nfc_tag2.h"
int nfctag2_set( NFCTAG2_SET setting, uint8_t *input );
#line 373 "e:/git/clicklab/nfc_tag2_click/library/include/nfc_tag2.h"
uint8_t nfctag2_config_get( NFCTAG2_CFG reg );
#line 388 "e:/git/clicklab/nfc_tag2_click/library/include/nfc_tag2.h"
int nfctag2_config_set( NFCTAG2_CFG reg, uint8_t input );
#line 400 "e:/git/clicklab/nfc_tag2_click/library/include/nfc_tag2.h"
uint8_t nfctag2_session_get( NFCTAG2_CFG reg );
#line 417 "e:/git/clicklab/nfc_tag2_click/library/include/nfc_tag2.h"
int nfctag2_session_set( NFCTAG2_CFG reg, uint8_t mask, uint8_t value );
#line 434 "e:/git/clicklab/nfc_tag2_click/library/include/nfc_tag2.h"
int nfctag2_memory_read( uint16_t mem_offset, uint8_t *buffer, uint16_t count );
#line 451 "e:/git/clicklab/nfc_tag2_click/library/include/nfc_tag2.h"
int nfctag2_memory_write( uint16_t mem_offset, uint8_t *buffer, uint16_t count );
#line 20 "E:/git/ClickLab/NFC_Tag2_click/example/HEXI/NT2_HEXI.c"
nfctag2_click NT2_click;

void system_init( void );
void print_mem( uint8_t *ptr, uint16_t len );
void test_read_common( void );
void test_write_common( void );
void test_read_config( void );
void test_write_config( void );
void test_read_session( void );
void test_write_session( void );
#line 38 "E:/git/ClickLab/NFC_Tag2_click/example/HEXI/NT2_HEXI.c"
void system_init( void )
{
 UART3_Init_Advanced( 115200, _UART_8_BIT_DATA, _UART_NOPARITY,
 _UART_ONE_STOPBIT, &_GPIO_Module_UART3_PC16_17 );
 Delay_ms( 200 );

 I2C0_Init_Advanced( 400000, &_GPIO_Module_I2C0_PD8_9 );
 Delay_ms( 200 );
  UART1_Write_Text("\r\n< < System Initialized > >\r\n") ;
}

void print_mem( uint8_t *ptr, uint16_t len )
{
int reg_cnt;
char tmp[ 15 ];
  UART1_Write_Text("\t") ;
 for( reg_cnt = 0; reg_cnt < len; reg_cnt++ )
 {
 ByteToHex( *( ptr + reg_cnt ), tmp );
  UART1_Write_Text(Ltrim( tmp )) ;
  UART1_Write_Text(" ") ;
 if( reg_cnt % 16 )  UART1_Write_Text("\r\n") ;
 }
  UART1_Write_Text("\r\n") ;
}
#line 72 "E:/git/ClickLab/NFC_Tag2_click/example/HEXI/NT2_HEXI.c"
void test_read_common( void )
{
  UART1_Write_Text("Read Serial number :") ;
 if( !nfctag2_get( NT2_SET_SERIAL_NO, NT2_click.serial_num ) )
 print_mem( NT2_click.serial_num, sizeof( NT2_click.serial_num ) );
  UART1_Write_Text("Read SRAM :") ;
 if( !nfctag2_get( NT2_SET_SRAM_MEMORY, NT2_click.sram_memory ) )
 print_mem( NT2_click.sram_memory, sizeof( NT2_click.sram_memory ) );
  UART1_Write_Text("Reading SRAM Finished\r\n") ;
}

void test_write_common( void )
{
uint8_t default_CC[ 4 ] = { 0xE1, 0xC0, 0x01, 0x00 };
 memcpy( NT2_click.cap_containter, default_CC,
 sizeof( NT2_click.cap_containter ) );
 if( !nfctag2_set( NT2_SET_CAP_CONTAINER, NT2_click.cap_containter ) )
  UART1_Write_Text("New CC writing finished\r\n") ;
}
#line 100 "E:/git/ClickLab/NFC_Tag2_click/example/HEXI/NT2_HEXI.c"
void test_read_config( void )
{
  UART1_Write_Text("CLK Stretching ") ;
 if( nfctag2_config_get( NT2_CFG_STR ) |  0x01  )
  UART1_Write_Text("ON\r\n") ;
 else
  UART1_Write_Text("OFF\r\n") ;
}

void test_write_config( void )
{
  UART1_Write_Text("Writing new NC reg content") ;
 if( !nfctag2_config_set( NT2_CFG_NC_REG,  0x00  |
  0x00  |
  0x00  |
  0x00  ) )
  UART1_Write_Text("NC Configuration Written\r\n") ;
}
#line 127 "E:/git/ClickLab/NFC_Tag2_click/example/HEXI/NT2_HEXI.c"
void test_read_session( void )
{
uint8_t temp[ 2 ];

  UART1_Write_Text("< Watchdog Timer >\r\n") ;
 temp[ 0 ] = nfctag2_session_get( NT2_CFG_WDT_MS );
 temp[ 1 ] = nfctag2_session_get( NT2_CFG_WDT_LS );
 print_mem( temp, 2 );
}

void test_write_session( void )
{
 if( !nfctag2_session_set( NT2_CFG_NC_REG,  0x80 ,
  0x00  ) )
  UART1_Write_Text("Restart the module on I2C Repeated start ON\r\n") ;
 if( !nfctag2_session_set( NT2_SES_NS_REG,  0x04 ,
  0x00  ) )
  UART1_Write_Text("EEPROM Error flag removed\r\n") ;
}
#line 153 "E:/git/ClickLab/NFC_Tag2_click/example/HEXI/NT2_HEXI.c"
void write_ndef( void )
{
uint8_t ndef_rec[] = { 0x03,
 15,

 0xD1,
 1,
 11,
 'U',
 0x01,
 'm', 'i', 'k', 'r', 'o', 'e', '.', 'c', 'o', 'm',
 0xFE };

 memset( NT2_click.user_memory, 0, 888 );
 nfctag2_memory_write( 0, NT2_click.user_memory, 888 );
 nfctag2_memory_write( 0, ndef_rec, sizeof( ndef_rec ) );
}


void main()
{
 system_init();
 nfctag2_init( 0x04 );










 write_ndef();

 while( 1 );
}

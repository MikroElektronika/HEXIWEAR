#line 1 "E:/git/ClickLab/NFC_Tag2_click/library/src/nfc_tag2.c"
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
#line 25 "E:/git/ClickLab/NFC_Tag2_click/library/src/nfc_tag2.c"
typedef uint8_t NT2_MEM_MAP[ 3 ];
#line 30 "E:/git/ClickLab/NFC_Tag2_click/library/src/nfc_tag2.c"
enum NT2_MAP_PROP
{
 MM_BLOCK, MM_OFFSET, MM_SIZE
};
#line 38 "E:/git/ClickLab/NFC_Tag2_click/library/src/nfc_tag2.c"
static const NT2_MEM_MAP MEMORY[ 5 ] =
{
 { 0, 0, 7 },
 { 0, 10, 2 },
 { 0, 12, 4 },
 { 56, 8, 3 },
 { 248, 0, 64 }
};

static uint8_t _i2c_address;
#line 53 "E:/git/ClickLab/NFC_Tag2_click/library/src/nfc_tag2.c"
static int nt2_memblock_rd( uint8_t block, uint8_t *value );

static int nt2_memblock_wr( uint8_t block, uint8_t *value );

static int nt2_memreg_rd
(
 uint8_t block,
 uint8_t offset,
 uint16_t len,
 uint8_t *out
);

static int nt2_memreg_wr
(
 uint8_t block,
 uint8_t offset,
 uint16_t len,
 uint8_t *in
);
#line 77 "E:/git/ClickLab/NFC_Tag2_click/library/src/nfc_tag2.c"
static int nt2_memblock_rd
(
 uint8_t block,
 uint8_t *value
)
{
 uint8_t temp[  16  ] = { 0 };
 temp[ 0 ] = block;
 if( hal_nfctag2_read( _i2c_address, temp, sizeof( temp ) ) )
 return 1;
 memcpy( ( void* )value, ( void* )temp,  16  );
 hal_delay( 5 );
 return 0;
}

static int nt2_memblock_wr
(
 uint8_t block,
 uint8_t *value
)
{
 uint8_t temp[  16  + 1 ] = { 0 };
 temp[ 0 ] = block;
 memcpy( ( void* )( temp + 1 ), ( void* )value ,  16  );
 if( hal_nfctag2_write( _i2c_address, temp, sizeof( temp ) ) )
 return 1;
 hal_delay( 5 );
 return 0;
}

static int nt2_memreg_rd
(
 uint8_t block,
 uint8_t offset,
 uint16_t len,
 uint8_t *out
)
{
 uint8_t temp[  16  ] = { 0 };

 while( ( offset + len ) >  16  )
 {
 if( nt2_memblock_rd( block++, temp ) )
 return 1;
 memcpy( ( void* )out,
 ( void* )( temp + offset ),  16  - offset );
 len -=  16  - offset;
 out +=  16  - offset;
 offset = 0;
 }
 if( nt2_memblock_rd( block, temp ) )
 return 1;
 memcpy( ( void* )out, ( void* )( temp + offset ), len );
 return 0;
}

static int nt2_memreg_wr
(
 uint8_t block,
 uint8_t offset,
 uint16_t len,
 uint8_t *in
)
{
 uint8_t temp[  16  ] = { 0 };

 while( ( offset + len ) >  16  )
 {
 if( nt2_memblock_rd( block, temp ) )
 return 1;
 memcpy( ( void* )( temp + offset ),
 ( void* )in,  16  - offset );
 if( nt2_memblock_wr( block++, temp ) )
 return 1;
 len -=  16  - offset;
 in +=  16  - offset;
 offset = 0;
 }
 if( nt2_memblock_rd( block, temp ) )
 return 1;
 memcpy( ( void* )( temp + offset ), ( void* )in, len );
 if( nt2_memblock_wr( block, temp ) )
 return 1;
 return 0;
}
#line 167 "E:/git/ClickLab/NFC_Tag2_click/library/src/nfc_tag2.c"
int nfctag2_init( uint8_t i2c_address )
{
 _i2c_address = i2c_address >> 1;
 if( hal_nfctag2_init() )
 return -1;
 return  0 ;
}

int nfctag2_i2c_addres( uint8_t new_address )
{
 uint8_t tmp = new_address;
 if( nt2_memreg_wr( 0, 0, 1, &tmp ) )
 return  (-3) ;
 _i2c_address = tmp >> 1;
 return  0 ;
}

int nfctag2_get( NFCTAG2_SET reg, uint8_t *output )
{
 uint8_t *ptr = output;
 if( nt2_memreg_rd( MEMORY[ reg ][ MM_BLOCK ], MEMORY[ reg ][ MM_OFFSET ],
 MEMORY[ reg ][ MM_SIZE ], ptr ) )
 return  (-2) ;
 return  0 ;
}

int nfctag2_set( NFCTAG2_SET reg, uint8_t *value )
{
 uint8_t *ptr = value;
 if( nt2_memreg_wr( MEMORY[ reg ][ MM_BLOCK ], MEMORY[ reg ][ MM_OFFSET ],
 MEMORY[ reg ][ MM_SIZE ], ptr ) )
 return  (-3) ;
 return  0 ;
}

uint8_t nfctag2_config_get( NFCTAG2_CFG reg )
{
 uint8_t regdat;
 if( nt2_memreg_rd(  0x3A , reg, 1, &regdat ) )
 return  (-2) ;
 return regdat;
}

int nfctag2_config_set( NFCTAG2_CFG reg, uint8_t input )
{
 if( nt2_memreg_wr(  0x3A , reg, 1, &input ) )
 return  (-3) ;
 return  0 ;
}

uint8_t nfctag2_session_get( NFCTAG2_CFG reg )
{
 uint8_t regdat;
 uint8_t temp[ 2 ] = { 0 };
 temp[ 0 ] =  0xFE ;
 temp[ 1 ] = reg;
 if( hal_nfctag2_transfer( _i2c_address, temp, 2, &regdat, 1 ) )
 return  (-3) ;
 hal_delay( 5 );
 return regdat;
}

int nfctag2_session_set( NFCTAG2_CFG reg, uint8_t mask, uint8_t value )
{
 uint8_t temp[ 4 ] = { 0 };
 temp[ 0 ] =  0xFE ;
 temp[ 1 ] = reg;
 temp[ 2 ] = mask;
 temp[ 3 ] = value;
 if( hal_nfctag2_write( _i2c_address, temp, 4 ) )
 return  (-3) ;
 hal_delay( 5 );
 return  0 ;
}

int nfctag2_memory_read( uint16_t mem_offset, uint8_t *buffer, uint16_t count )
{
 uint8_t blk = ( mem_offset /  16  ) +  0x01 ;
 uint8_t off = mem_offset %  16 ;
 uint8_t *ptr = buffer;
 if( nt2_memreg_rd( blk, off, count, ptr ) )
 return  (-2) ;
 return  0 ;
}

int nfctag2_memory_write( uint16_t mem_offset, uint8_t *buffer, uint16_t count )
{
 uint8_t blk = ( mem_offset /  16  ) +  0x01 ;
 uint8_t off = mem_offset %  16 ;
 uint8_t *ptr = buffer;
 if( nt2_memreg_wr( blk, off, count, ptr ) )
 return  (-3) ;
 return  0 ;
}

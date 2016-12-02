#line 1 "C:/Users/richard/Desktop/GSM4/library/src/gsm4_at_parser.c"
#line 1 "c:/users/richard/desktop/gsm4/library/include/gsm4_at_parser.h"
#line 1 "c:/users/richard/desktop/gsm4/library/include/gsm4_config.h"
#line 1 "c:/c4w/mikroelektronika/mikroc pro for ft90x/include/stdint.h"





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
#line 1 "c:/c4w/mikroelektronika/mikroc pro for ft90x/include/stddef.h"



typedef long ptrdiff_t;


 typedef unsigned long size_t;

typedef unsigned long wchar_t;
#line 1 "c:/c4w/mikroelektronika/mikroc pro for ft90x/include/string.h"





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
#line 1 "c:/c4w/mikroelektronika/mikroc pro for ft90x/include/stdbool.h"



 typedef char _Bool;
#line 62 "c:/users/richard/desktop/gsm4/library/include/gsm4_config.h"
typedef enum
{
 AT_OK,
 AT_ERROR,
 AT_UNKNOWN

}at_t;

typedef void ( *at_cmd_cb )( char *buffer );
#line 26 "c:/users/richard/desktop/gsm4/library/include/gsm4_at_parser.h"
typedef enum
{
#line 30 "c:/users/richard/desktop/gsm4/library/include/gsm4_at_parser.h"
 AT_CMD_UNKNOWN = 0,
#line 33 "c:/users/richard/desktop/gsm4/library/include/gsm4_at_parser.h"
 AT_CMD_GET = 1,
#line 36 "c:/users/richard/desktop/gsm4/library/include/gsm4_at_parser.h"
 AT_CMD_SET = 2,
#line 39 "c:/users/richard/desktop/gsm4/library/include/gsm4_at_parser.h"
 AT_CMD_TEST = 3,
#line 42 "c:/users/richard/desktop/gsm4/library/include/gsm4_at_parser.h"
 AT_CMD_EXEC = 4,

}at_type_t;
#line 54 "c:/users/richard/desktop/gsm4/library/include/gsm4_at_parser.h"
typedef struct
{
#line 58 "c:/users/richard/desktop/gsm4/library/include/gsm4_at_parser.h"
 uint32_t hash;
#line 61 "c:/users/richard/desktop/gsm4/library/include/gsm4_at_parser.h"
 uint32_t timeout;
#line 64 "c:/users/richard/desktop/gsm4/library/include/gsm4_at_parser.h"
 at_cmd_cb getter;
#line 67 "c:/users/richard/desktop/gsm4/library/include/gsm4_at_parser.h"
 at_cmd_cb setter;
#line 70 "c:/users/richard/desktop/gsm4/library/include/gsm4_at_parser.h"
 at_cmd_cb tester;
#line 73 "c:/users/richard/desktop/gsm4/library/include/gsm4_at_parser.h"
 at_cmd_cb executer;

}at_cmd_t;
#line 90 "c:/users/richard/desktop/gsm4/library/include/gsm4_at_parser.h"
void at_parser_init
(
 void
);
#line 108 "c:/users/richard/desktop/gsm4/library/include/gsm4_at_parser.h"
void at_parser_store
(
 char *command,
 uint32_t timeout,
 at_cmd_cb getter,
 at_cmd_cb setter,
 at_cmd_cb tester,
 at_cmd_cb execute
);
#line 128 "c:/users/richard/desktop/gsm4/library/include/gsm4_at_parser.h"
void at_parse
(
 char *input,
 at_cmd_cb *cb,
 uint32_t *timeout
);
#line 20 "C:/Users/richard/Desktop/GSM4/library/src/gsm4_at_parser.c"
static uint8_t header_size;
static uint8_t at_cmd_storage_used;
static volatile at_cmd_t at_cmd_storage [  50  ];
static char at_start_chars [  2  ];
#line 29 "C:/Users/richard/Desktop/GSM4/library/src/gsm4_at_parser.c"
static uint32_t _at_hash
(
 char *cmd
);

static uint16_t _at_search
(
 char* cmd
);

static at_type_t _at_sub_parse
(
 char *raw_in,
 char *clean_out
);
#line 49 "C:/Users/richard/Desktop/GSM4/library/src/gsm4_at_parser.c"
static uint32_t _at_hash
(
 char *cmd
)
{
 uint16_t ch = 0;
 uint32_t hash = 4321;

 while( ( ch = *( cmd++ ) ) )
 hash = ( ( hash << 5 ) + hash ) + ch;

 return hash;
}

static uint16_t _at_search
(
 char* cmd
)
{
 uint16_t i;
 uint32_t tmp_hash = _at_hash( cmd );

 for( i = 0; i < at_cmd_storage_used; i++ )
 if( at_cmd_storage[ i ].hash == tmp_hash )
 return i;

 return 0;
}

static at_type_t _at_sub_parse
(
 char *raw_in,
 char *clean_out
)
{
 uint8_t c = 0;
 uint8_t end_pos = 0;
 uint8_t set_pos = 0;
 uint8_t get_pos = 0;
 uint8_t start_pos = 0;
 char* tmp_ptr = raw_in;
 char tmp_cmd[  15  ] = { 0 };

 if( strlen( tmp_ptr ) <=  2  )
 return AT_CMD_UNKNOWN;

 strncpy( tmp_cmd, tmp_ptr,  15  );

 for( c = 0; c <  15 ; c++ )
 {
 if( tmp_cmd[ c ] == '\0' )
 {
 if( !end_pos )
 end_pos = c;
 break;
 }

 if( ( tmp_cmd[ c ] == '+') && !start_pos )
 start_pos = c;

 if( ( tmp_cmd[ c ] == '=' ) && !set_pos )
 set_pos = c;

 if( ( tmp_cmd[ c ] == '?' ) && !get_pos )
 get_pos = c;

 if( ( ( tmp_cmd[ c ] == '\r' ) ||
 ( tmp_cmd[ c ] == '\n' ) ||
 ( tmp_cmd[ c ] == ':' ) ) && !end_pos )
 end_pos = c;
 }

 if( !set_pos && !get_pos )
 {
 strncpy( clean_out, &tmp_cmd[ start_pos ], end_pos - start_pos );
 return AT_CMD_EXEC;

 } else if( !set_pos && get_pos ) {

 strncpy( clean_out, &tmp_cmd[ start_pos ], get_pos - start_pos );
 return AT_CMD_TEST;

 } else if( set_pos && !get_pos ) {

 strncpy( clean_out, &tmp_cmd[ start_pos ], set_pos - start_pos );
 return AT_CMD_SET;

 } else if( set_pos == get_pos - 1 ) {

 strncpy( clean_out, &tmp_cmd[ start_pos ], set_pos - start_pos );
 return AT_CMD_GET;
 }
 return AT_CMD_UNKNOWN;
}
#line 148 "C:/Users/richard/Desktop/GSM4/library/src/gsm4_at_parser.c"
void at_parser_init
(
 void
)
{
 uint8_t c;

 header_size = strlen( ( char* ) "AT"  );
 at_cmd_storage_used = 0;

 for( c = 0; c <  50 ; c++ )
 {
 at_cmd_storage[ c ].hash = 0;
 at_cmd_storage[ c ].timeout = 0;
 at_cmd_storage[ c ].getter =  ((void *)0) ;
 at_cmd_storage[ c ].setter =  ((void *)0) ;
 at_cmd_storage[ c ].tester =  ((void *)0) ;
 at_cmd_storage[ c ].executer =  ((void *)0) ;
 }
}

void at_parser_store
(
 char *command,
 uint32_t timeout,
 at_cmd_cb getter,
 at_cmd_cb setter,
 at_cmd_cb tester,
 at_cmd_cb executer
)
{
 at_cmd_t cmd;

 cmd.hash = _at_hash( command );
 cmd.timeout = timeout;
 cmd.getter = getter;
 cmd.setter = setter;
 cmd.tester = tester;
 cmd.executer = executer;

 if( strlen( command ) >=  15  + header_size )
 return;

 if( at_cmd_storage_used ==  50  )
 return;

 if( _at_search( command ) )
 return;

 at_cmd_storage[ at_cmd_storage_used ] = cmd;
 at_cmd_storage_used++;
}

void at_parse
(
 char *input,
 at_cmd_cb *cb,
 uint32_t *timeout
)
{
 at_type_t cmd_type = 0;
 uint16_t cmd_idx = 0;
 char cmd_temp[  15  ] = { 0 };

 if( !( cmd_type = _at_sub_parse( input, cmd_temp ) ) )
 {
 *cb = at_cmd_storage[ 0 ].tester;
 *timeout = at_cmd_storage[ 0 ].timeout;
 return;
 }

 if( !( cmd_idx = _at_search( cmd_temp ) ) )
 {
 *cb = at_cmd_storage[ 0 ].tester;
 *timeout = at_cmd_storage[ 0 ].timeout;
 return;
 }

 switch ( cmd_type )
 {
 case AT_CMD_SET :
 *cb = at_cmd_storage[ cmd_idx ].setter;
 *timeout = at_cmd_storage[ cmd_idx ].timeout;
 break;
 case AT_CMD_GET :
 *cb = at_cmd_storage[ cmd_idx ].getter;
 *timeout = at_cmd_storage[ cmd_idx ].timeout;
 break;
 case AT_CMD_TEST :
 *cb = at_cmd_storage[ cmd_idx ].tester;
 *timeout = at_cmd_storage[ cmd_idx ].timeout;
 break;
 case AT_CMD_EXEC :
 *cb = at_cmd_storage[ cmd_idx ].executer;
 *timeout = at_cmd_storage[ cmd_idx ].timeout;
 break;
 case AT_CMD_UNKNOWN :
 *cb = at_cmd_storage[ 0 ].executer;
 *timeout = at_cmd_storage[ 0 ].timeout;
 break;
 }
 return;
}

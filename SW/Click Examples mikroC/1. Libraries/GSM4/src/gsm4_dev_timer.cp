#line 1 "C:/Users/richard/Desktop/GSM4/library/src/gsm4_dev_timer.c"
#line 1 "c:/users/richard/desktop/gsm4/library/include/gsm4_dev_timer.h"
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
#line 23 "c:/users/richard/desktop/gsm4/library/include/gsm4_dev_timer.h"
extern volatile  _Bool  timeout_f;
#line 39 "c:/users/richard/desktop/gsm4/library/include/gsm4_dev_timer.h"
void dev_timer_init
(
 void
);
#line 51 "c:/users/richard/desktop/gsm4/library/include/gsm4_dev_timer.h"
void dev_tick_isr
(
 void
);
#line 62 "c:/users/richard/desktop/gsm4/library/include/gsm4_dev_timer.h"
void dev_timer_start
(
 void
);
#line 73 "c:/users/richard/desktop/gsm4/library/include/gsm4_dev_timer.h"
void dev_timer_restart
(
 void
);
#line 84 "c:/users/richard/desktop/gsm4/library/include/gsm4_dev_timer.h"
void dev_timer_stop
(
 void
);
#line 97 "c:/users/richard/desktop/gsm4/library/include/gsm4_dev_timer.h"
void dev_timer_load
(
 uint32_t timeout
);
#line 20 "C:/Users/richard/Desktop/GSM4/library/src/gsm4_dev_timer.c"
static volatile  _Bool  timer_f;
static volatile uint32_t timer_c;
static volatile uint32_t timer;
#line 28 "C:/Users/richard/Desktop/GSM4/library/src/gsm4_dev_timer.c"
void dev_timer_init
(
 void
)
{
 uint8_t c;

 timer = 0;
 timer_c = 0;
 timeout_f =  0 ;
 timer_f =  0 ;
}

void dev_tick_isr
(
 void
)
{
 if( timer_f )
 if( timer_c++ > timer )
 timeout_f =  1 ;
}

void dev_timer_start
(
 void
)
{
 timer_f =  1 ;
 timer_c = 0;
}

void dev_timer_restart
(
 void
)
{
 timer_c = 0;
}

void dev_timer_stop
(
 void
)
{
 timer_f =  0 ;
 timer_c = 0;
}

void dev_timer_load
(
 uint32_t timeout
)
{
 timer = timeout;
}

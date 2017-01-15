#line 1 "D:/Uros/!!KONACNI PRIMERI/backup/HEXIWEAR_IR_GESTURE_Click/example/ARM/src/ir_gesture_hw.c"
#line 1 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hal.h"
#line 1 "d:/program files/nxp/mikroc pro for arm/include/stdint.h"





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
#line 73 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hal.h"
int ir_gesture_i2c_init( uint8_t address_id );
#line 79 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hal.h"
void ir_gesture_hal_delay( uint8_t ms );
#line 88 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hal.h"
void ir_gesture_i2c_hal_write( uint8_t address,
 uint8_t const *buff, uint16_t count );
#line 98 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hal.h"
void ir_gesture_i2c_hal_read( uint8_t address,
 uint8_t const *buff , uint16_t count );
#line 1 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
#line 1 "d:/program files/nxp/mikroc pro for arm/include/stdint.h"
#line 1 "d:/program files/nxp/mikroc pro for arm/include/stdbool.h"



 typedef char _Bool;
#line 165 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
typedef enum
{
 DIR_NONE,
 DIR_LEFT,
 DIR_RIGHT,
 DIR_UP,
 DIR_DOWN,
 DIR_NEAR,
 DIR_FAR,
 DIR_ALL
} gesture_dir_t;

typedef enum
{
 INT_GESTURE = 2,
 INT_AMBIENT_LIGHT = 4,
 INT_PROXIMITY = 5
} gesture_irq_t;
#line 202 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
int ir_gesture_init( uint8_t address );
#line 208 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
void ir_gesture_enable_power( void );
#line 213 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
void ir_gesture_disable_power( void );
#line 221 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
void ir_gesture_enable_light_sensor(  _Bool  interrupt );
#line 226 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
void ir_gesture_disable_light_sensor( void );
#line 233 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
void ir_gesture_enable_proximity_sensor(  _Bool  interrupt );
#line 238 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
void ir_gesture_disable_proximity_sensor( void );
#line 245 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
void ir_gesture_enable_gesture_sensor(  _Bool  interrupt );
#line 250 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
void ir_gesture_disable_gesture_sensor( void );
#line 264 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
uint8_t ir_gesture_get_led_drive( void );
#line 277 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
void ir_gesture_set_led_drive( uint8_t drive );
#line 290 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
uint8_t ir_gesture_get_gesture_led_drive();
#line 303 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
void ir_gesture_set_gesture_led_drive( uint8_t drive );
#line 317 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
uint8_t ir_gesture_get_ambient_light_gain();
#line 330 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
void ir_gesture_set_ambient_light_gain( uint8_t gain );
#line 343 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
uint8_t ir_gesture_get_proximity_gain( void );
#line 356 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
void ir_gesture_set_proximity_gain( uint8_t gain );
#line 369 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
uint8_t ir_gesture_get_gesture_gain( void );
#line 382 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
void ir_gesture_set_gesture_gain( uint8_t gain );
#line 390 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
uint16_t ir_gesture_get_light_int_low_threshold( void );
#line 397 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
void ir_gesture_set_light_int_low_threshold( uint16_t threshold );
#line 404 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
uint16_t ir_gesture_get_light_int_high_threshold( void );
#line 411 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
void ir_gesture_set_light_int_high_threshold( uint16_t threshold );
#line 419 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
uint8_t ir_gesture_get_proximity_int_low_threshold( void );
#line 426 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
void ir_gesture_set_proximity_int_low_threshold( uint8_t threshold );
#line 433 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
uint8_t ir_gesture_get_proximity_int_high_threshold( void );
#line 440 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
void ir_gesture_set_prox_int_high_threshold( uint8_t threshold );
#line 448 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
 _Bool  ir_gesture_is_ambient_light_int_enable();
#line 455 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
void ir_gesture_set_ambient_light_int_enable(  _Bool  enable );
#line 462 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
 _Bool  ir_gesture_is_proximity_int_enable();
#line 469 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
void ir_gesture_set_proximity_int_enable(  _Bool  enable );
#line 476 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
 _Bool  ir_gesture_is_gesture_int_enable( void );
#line 483 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
void ir_gesture_set_gesture_int_enable(  _Bool  enable );
#line 489 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
 _Bool  ir_gesture_is_interrupted( gesture_irq_t interrupt );
#line 494 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
void ir_gesture_clear_ambient_light_int( void );
#line 499 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
void ir_gesture_clear_proximity_int( void );
#line 504 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
void ir_gesture_clear_gesture_int( void );
#line 512 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
uint16_t ir_gesture_read_ambient_light( void );
#line 519 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
uint16_t ir_gesture_read_red_light(void );
#line 526 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
uint16_t ir_gesture_read_green_light(void );
#line 533 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
uint16_t ir_gesture_read_blue_light(void );
#line 547 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
uint8_t ir_gesture_get_led_boost( void );
#line 561 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
void ir_gesture_set_led_boost( uint8_t boost );
#line 569 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
uint8_t ir_gesture_read_proximity( void );
#line 577 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
uint8_t ir_gesture_get_prox_int_low_thresh();
#line 584 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
void ir_gesture_set_prox_int_low_thresh( uint8_t threshold );
#line 591 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
uint8_t ir_gesture_get_prox_int_high_thresh();
#line 598 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
void ir_gesture_set_prox_int_high_thresh( uint8_t threshold );
#line 605 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
 _Bool  ir_gesture_is_prox_gain_comp_enable( void );
#line 613 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
void ir_gesture_set_prox_gain_comp_enable(  _Bool  enable );
#line 627 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
uint8_t ir_gesture_get_prox_photo_mask( void );
#line 641 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
void ir_gesture_set_prox_photo_mask( uint8_t mask );
#line 649 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
 _Bool  ir_gesture_available( void );
#line 656 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
gesture_dir_t ir_gesture_read_gesture( void );
#line 664 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
uint8_t ir_gesture_get_gesture_mode( void );
#line 671 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
void ir_gesture_set_gesture_mode(  _Bool  mode );
#line 679 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
uint8_t ir_gesture_enter_thresh( void );
#line 686 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
void ir_gesture_set_enter_thresh( uint8_t threshold );
#line 693 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
uint8_t ir_gesture_get_exit_thresh( void );
#line 700 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
void ir_gesture_set_exit_thresh( uint8_t threshold );
#line 718 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
uint8_t ir_gesture_get_wait_time( void );
#line 736 "d:/uros/!!konacni primeri/backup/hexiwear_ir_gesture_click/example/arm/include/ir_gesture_hw.h"
void ir_gesture_set_wait_time( uint8_t time );
#line 1 "d:/program files/nxp/mikroc pro for arm/include/stdint.h"
#line 1 "d:/program files/nxp/mikroc pro for arm/include/stdlib.h"







 typedef struct divstruct {
 int quot;
 int rem;
 } div_t;

 typedef struct ldivstruct {
 long quot;
 long rem;
 } ldiv_t;

 typedef struct uldivstruct {
 unsigned long quot;
 unsigned long rem;
 } uldiv_t;

int abs(int a);
float atof(char * s);
int atoi(char * s);
long atol(char * s);
div_t div(int number, int denom);
ldiv_t ldiv(long number, long denom);
uldiv_t uldiv(unsigned long number, unsigned long denom);
long labs(long x);
long int max(long int a, long int b);
long int min(long int a, long int b);
void srand(unsigned x);
int rand();
int xtoi(char * s);
#line 1 "d:/program files/nxp/mikroc pro for arm/include/string.h"





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
#line 1 "d:/program files/nxp/mikroc pro for arm/include/math.h"





double fabs(double d);
double floor(double x);
double ceil(double x);
double frexp(double value, int * eptr);
double ldexp(double value, int newexp);
double modf(double val, double * iptr);
double sqrt(double x);
double atan(double f);
double asin(double x);
double acos(double x);
double atan2(double y,double x);
double sin(double f);
double cos(double f);
double tan(double x);
double exp(double x);
double log(double x);
double log10(double x);
double pow(double x, double y);
double sinh(double x);
double cosh(double x);
double tanh(double x);
#line 114 "D:/Uros/!!KONACNI PRIMERI/backup/HEXIWEAR_IR_GESTURE_Click/example/ARM/src/ir_gesture_hw.c"
typedef enum
{
 NA_STATE,
 NEAR_STATE,
 FAR_STATE,
 ALL_STATE
} gesture_prox_t;


typedef struct
{
 uint8_t u_data[32];
 uint8_t d_data[32];
 uint8_t l_data[32];
 uint8_t r_data[32];
 uint8_t index;
 uint8_t total_gestures;
 uint8_t in_threshold;
 uint8_t out_threshold;
 int ud_delta;
 int lr_delta;
 int ud_count;
 int lr_count;
 int near_count;
 int far_count;
 gesture_prox_t state;
 gesture_dir_t motion;
} gesture_data_t;

typedef enum
{

 POWER = 0,
 AMBIENT_LIGHT,
 PROXIMITY,
 WAIT,
 AMBIENT_LIGHT_INT,
 PROXIMITY_INT,
 GESTURE,
 ALL
} ir_mode_t;
#line 169 "D:/Uros/!!KONACNI PRIMERI/backup/HEXIWEAR_IR_GESTURE_Click/example/ARM/src/ir_gesture_hw.c"
static uint8_t get_mode( void );
#line 177 "D:/Uros/!!KONACNI PRIMERI/backup/HEXIWEAR_IR_GESTURE_Click/example/ARM/src/ir_gesture_hw.c"
static void set_mode( ir_mode_t mode,  _Bool  enable );
#line 185 "D:/Uros/!!KONACNI PRIMERI/backup/HEXIWEAR_IR_GESTURE_Click/example/ARM/src/ir_gesture_hw.c"
static uint8_t process_gesture_data( gesture_data_t *gesture_data );
#line 192 "D:/Uros/!!KONACNI PRIMERI/backup/HEXIWEAR_IR_GESTURE_Click/example/ARM/src/ir_gesture_hw.c"
static uint8_t decode_gesture( gesture_data_t *gesture_data );
#line 197 "D:/Uros/!!KONACNI PRIMERI/backup/HEXIWEAR_IR_GESTURE_Click/example/ARM/src/ir_gesture_hw.c"
static uint8_t get_mode()
{
 uint8_t enable_value;


 ir_gesture_i2c_hal_read(  0x80 , &enable_value, 1 );

 return enable_value;
}

static void set_mode( ir_mode_t mode,  _Bool  enable )
{

 uint8_t reg_val = get_mode();

 if( reg_val ==  0xFF  )
 return;

 mode =  (((mode) < (ALL)) ? (mode) : (ALL)) ;

 if( mode == ALL )
 {
 reg_val = 0x00;

 if( enable )
 reg_val = 0x7F;
 } else {
 reg_val &= ~( 1 << mode );

 if( enable )
 reg_val |= ( 1 << mode );
 }


 ir_gesture_i2c_hal_write(  0x80 , &reg_val, 1 );
}

static uint8_t process_gesture_data( gesture_data_t *gesture_data )
{
 uint8_t u_first = 0;
 uint8_t d_first = 0;
 uint8_t l_first = 0;
 uint8_t r_first = 0;
 uint8_t u_last = 0;
 uint8_t d_last = 0;
 uint8_t l_last = 0;
 uint8_t r_last = 0;
 int ud_ratio_first;
 int lr_ratio_first;
 int ud_ratio_last;
 int lr_ratio_last;
 int ud_delta;
 int lr_delta;
 int i;


 if( gesture_data->total_gestures <= 4 )
 return -1;


 if( ( gesture_data->total_gestures <= 32 ) && ( gesture_data->total_gestures > 0 ) )
 {

 for( i = 0; i < gesture_data->total_gestures; i++ )
 {
 if( ( gesture_data->u_data[i] >  10  ) &&
 ( gesture_data->d_data[i] >  10  ) &&
 ( gesture_data->l_data[i] >  10  ) &&
 ( gesture_data->r_data[i] >  10  ) )
 {

 u_first = gesture_data->u_data[i];
 d_first = gesture_data->d_data[i];
 l_first = gesture_data->l_data[i];
 r_first = gesture_data->r_data[i];
 break;
 }
 }


 if( ( u_first == 0 ) || ( d_first == 0 ) ||
 ( l_first == 0 ) || ( r_first == 0 ) )
 return -1;

 for( i = gesture_data->total_gestures - 1; i >= 0; i-- )
 {
 if( ( gesture_data->u_data[i] >  10  ) &&
 ( gesture_data->d_data[i] >  10  ) &&
 ( gesture_data->l_data[i] >  10  ) &&
 ( gesture_data->r_data[i] >  10  ) )
 {

 u_last = gesture_data->u_data[i];
 d_last = gesture_data->d_data[i];
 l_last = gesture_data->l_data[i];
 r_last = gesture_data->r_data[i];
 break;
 }
 }
 }


 ud_ratio_first = ( ( u_first - d_first ) * 100 ) / ( u_first + d_first );
 lr_ratio_first = ( ( l_first - r_first ) * 100 ) / ( l_first + r_first );
 ud_ratio_last = ( ( u_last - d_last ) * 100 ) / ( u_last + d_last );
 lr_ratio_last = ( ( l_last - r_last ) * 100 ) / ( l_last + r_last );


 ud_delta = ud_ratio_last - ud_ratio_first;
 lr_delta = lr_ratio_last - lr_ratio_first;


 gesture_data->ud_delta += ud_delta;
 gesture_data->lr_delta += lr_delta;


 if( gesture_data->ud_delta >=  50  )
 gesture_data->ud_count = 1;
 else if( gesture_data->ud_delta <= - 50  )
 gesture_data->ud_count = -1;
 else
 gesture_data->ud_count = 0;


 if( gesture_data->lr_delta >=  50  )
 gesture_data->lr_count = 1;
 else if( gesture_data->lr_delta <= - 50  )
 gesture_data->lr_count = -1;
 else
 gesture_data->lr_count = 0;


 if( ( gesture_data->ud_count == 0 ) && ( gesture_data->lr_count == 0 ) )
 {
 if( ( abs( ud_delta ) <  20  ) &&
 ( abs( lr_delta ) <  20  ) )
 {
 if( ( ud_delta == 0 ) && ( lr_delta == 0 ) )
 gesture_data->near_count++;
 else if( ( ud_delta != 0 ) || ( lr_delta != 0 ) )
 gesture_data->far_count++;

 if( ( gesture_data->near_count >= 10 ) &&
 ( gesture_data->far_count >= 2 ) )
 {
 if( ( ud_delta == 0 ) && ( lr_delta == 0 ) )
 gesture_data->state = NEAR_STATE;
 else if( ( ud_delta != 0 ) && ( lr_delta != 0 ) )
 gesture_data->state = FAR_STATE;
 return 0;
 }
 }
 } else {
 if( ( abs( ud_delta ) <  20  ) &&
 ( abs( lr_delta ) <  20  ) )
 {
 if( ( ud_delta == 0 ) && ( lr_delta == 0 ) )
 gesture_data->near_count++;

 if( gesture_data->near_count >= 10 )
 {
 gesture_data->ud_count = 0;
 gesture_data->lr_count = 0;
 gesture_data->ud_delta = 0;
 gesture_data->lr_delta = 0;
 }
 }
 }
 return -1;
}


static uint8_t decode_gesture( gesture_data_t *gesture_data )
{

 if( gesture_data->state == NEAR_STATE )
 {
 gesture_data->motion = DIR_NEAR;
 return 0;
 } else if ( gesture_data->state == FAR_STATE ) {
 gesture_data->motion = DIR_FAR;
 return 0;
 }


 if( ( gesture_data->ud_count == -1 ) && ( gesture_data->lr_count == 0 ) )
 gesture_data->motion = DIR_UP;
 else if( ( gesture_data->ud_count == 1 ) && ( gesture_data->lr_count == 0) )
 gesture_data->motion = DIR_DOWN;
 else if( ( gesture_data->ud_count == 0 ) && ( gesture_data->lr_count == 1) )
 gesture_data->motion = DIR_RIGHT;
 else if( ( gesture_data->ud_count == 0 ) && ( gesture_data->lr_count == -1) )
 gesture_data->motion = DIR_LEFT;
 else if( ( gesture_data->ud_count == -1 ) && ( gesture_data->lr_count == 1) )
 {
 if( abs( gesture_data->ud_delta ) > abs( gesture_data->lr_delta) )
 gesture_data->motion = DIR_UP;
 else
 gesture_data->motion = DIR_RIGHT;
 }
 else if( ( gesture_data->ud_count == 1 ) && ( gesture_data->lr_count == -1) )
 {
 if( abs( gesture_data->ud_delta ) > abs( gesture_data->lr_delta) )
 gesture_data->motion = DIR_DOWN;
 else
 gesture_data->motion = DIR_LEFT;
 }
 else if( ( gesture_data->ud_count == -1 ) && ( gesture_data->lr_count == -1) )
 {
 if( abs( gesture_data->ud_delta ) > abs( gesture_data->lr_delta) )
 gesture_data->motion = DIR_UP;
 else
 gesture_data->motion = DIR_LEFT;
 }
 else if( ( gesture_data->ud_count == 1 ) && ( gesture_data->lr_count == 1) )
 {
 if( abs( gesture_data->ud_delta ) > abs( gesture_data->lr_delta) )
 gesture_data->motion = DIR_DOWN;
 else
 gesture_data->motion = DIR_RIGHT;
 }
 else
 return -1;

 return 0;
}



int ir_gesture_init( uint8_t address )
{
 uint8_t temp;
 char buff[1];

 if( ir_gesture_i2c_init( address ) )
 return -1;

 ir_gesture_i2c_hal_read(  0x92 , &temp, 1 );

 if( !( temp ==  0xAB  || temp ==  0x9C  ) )
 return -1;


 set_mode( ALL,  0  );


 temp =  219 ;
 ir_gesture_i2c_hal_write(  0x81 , &temp, 1 );
 temp =  246 ;
 ir_gesture_i2c_hal_write(  0x83 , &temp, 1 );
 temp =  0x87 ;
 ir_gesture_i2c_hal_write(  0x8E , &temp, 1 );
 temp =  0 ;
 ir_gesture_i2c_hal_write(  0x9D , &temp, 1 );
 temp =  0 ;
 ir_gesture_i2c_hal_write(  0x9E , &temp, 1 );
 temp =  0x60 ;
 ir_gesture_i2c_hal_write(  0x8D , &temp, 1 );
 ir_gesture_set_led_drive(  0  );
 ir_gesture_set_proximity_gain(  2  );
 ir_gesture_set_ambient_light_gain(  1  );
 ir_gesture_set_prox_int_low_thresh(  0  );
 ir_gesture_set_prox_int_high_thresh(  50  );
 ir_gesture_set_light_int_low_threshold(  0xFFFF  );
 ir_gesture_set_light_int_high_threshold(  0  );
 temp =  0x11 ;
 ir_gesture_i2c_hal_write(  0x8C , &temp, 1 );
 temp =  0x01 ;
 ir_gesture_i2c_hal_write(  0x90 , &temp, 1 );
 temp =  0 ;
 ir_gesture_i2c_hal_write(  0x9F , &temp, 1 );


 ir_gesture_set_enter_thresh(  40  );
 ir_gesture_set_exit_thresh(  30  );
 temp =  0x40 ;
 ir_gesture_i2c_hal_write(  0xA2 , &temp, 1 );
 ir_gesture_set_gesture_gain(  2  );
 ir_gesture_set_gesture_led_drive(  0  );
 ir_gesture_set_wait_time(  1  );
 temp =  0 ;
 ir_gesture_i2c_hal_write(  0xA4 , &temp, 1 );
 temp =  0 ;
 ir_gesture_i2c_hal_write(  0xA5 , &temp, 1 );
 temp =  0 ;
 ir_gesture_i2c_hal_write(  0xA7 , &temp, 1 );
 temp =  0 ;
 ir_gesture_i2c_hal_write(  0xA9 , &temp, 1 );
 temp =  0xC9 ;
 ir_gesture_i2c_hal_write(  0xA6 , &temp, 1 );
 temp =  0 ;
 ir_gesture_i2c_hal_write(  0xAA , &temp, 1 );
 ir_gesture_set_gesture_int_enable(  0  );

 return 0;
}


void ir_gesture_enable_power()
{
 set_mode( POWER,  1  );
}

void ir_gesture_disable_power()
{
 set_mode( POWER,  0  );
}


void ir_gesture_enable_light_sensor(  _Bool  interrupt )
{

 ir_gesture_set_ambient_light_gain(  1  );

 ir_gesture_set_ambient_light_int_enable( interrupt );
 ir_gesture_enable_power();
 set_mode( AMBIENT_LIGHT,  1  );
}

void ir_gesture_disable_light_sensor()
{
 ir_gesture_set_ambient_light_int_enable(  0  );
 set_mode( AMBIENT_LIGHT,  0  );
}

void ir_gesture_enable_proximity_sensor(  _Bool  interrupt )
{

 ir_gesture_set_proximity_gain(  2  );
 ir_gesture_set_led_drive(  0  );

 ir_gesture_set_proximity_int_enable( interrupt );
 ir_gesture_enable_power();
 set_mode( PROXIMITY,  1  );
}

void ir_gesture_disable_proximity_sensor()
{
 ir_gesture_set_proximity_int_enable(  0  );
 set_mode( PROXIMITY,  0  );
}

void ir_gesture_enable_gesture_sensor(  _Bool  interrupt )
{
 uint8_t temp = 0xff;
#line 549 "D:/Uros/!!KONACNI PRIMERI/backup/HEXIWEAR_IR_GESTURE_Click/example/ARM/src/ir_gesture_hw.c"
 ir_gesture_i2c_hal_write(  0x83 , &temp, 1 );
 temp =  0x89 ;
 ir_gesture_i2c_hal_write(  0x8E , &temp, 1 );
 ir_gesture_set_led_boost(  3  );

 ir_gesture_set_gesture_int_enable( interrupt );

 ir_gesture_set_gesture_mode(  1  );
 ir_gesture_enable_power();
 set_mode( WAIT,  1  );
 set_mode( PROXIMITY,  1  );
 set_mode( GESTURE,  1  );
}

void ir_gesture_disable_gesture_sensor()
{

 ir_gesture_set_gesture_int_enable(  0  );
 ir_gesture_set_gesture_mode(  0  );
 set_mode( GESTURE,  0  );
}


uint8_t ir_gesture_get_led_drive()
{
 uint8_t val=0;


 ir_gesture_i2c_hal_read(  0x8F , &val, 1 );


 val = ( val >> 6 ) & 0x03;

 return val;
}

void ir_gesture_set_led_drive( uint8_t drive )
{
 uint8_t val;

 drive =  (((drive) < (0x03)) ? (drive) : (0x03)) ;


 ir_gesture_i2c_hal_read(  0x8F , &val, 1 );


 val &= ~( 1 << 6 ) | ( 1 << 7 );
 drive = ( drive << 6 ) | val;


 ir_gesture_i2c_hal_write(  0x8F , &drive, 1 );
}

uint8_t ir_gesture_get_gesture_led_drive()
{
 uint8_t val=0;


 ir_gesture_i2c_hal_read(  0xA3 , &val, 1 );


 val = ( val >> 3 ) & 0x03;

 return val;
}

void ir_gesture_set_gesture_led_drive( uint8_t drive )
{
 uint8_t val = 0;

 drive =  (((drive) < (0x03)) ? (drive) : (0x03)) ;


 ir_gesture_i2c_hal_read(  0xA3 , &val, 1 );


 val &= ~( 1 << 3 ) | ( 1 << 4 );
 drive = ( drive << 3 ) | val;


 ir_gesture_i2c_hal_write(  0xA3 , &drive, 1 );
}


uint8_t ir_gesture_get_ambient_light_gain()
{
 uint8_t val=0;


 ir_gesture_i2c_hal_read(  0x8F , &val, 1 );


 val &= 0x03;

 return val;
}

void ir_gesture_set_ambient_light_gain( uint8_t drive )
{
 uint8_t val=0;

 drive =  (((drive) < (0x03)) ? (drive) : (0x03)) ;


 ir_gesture_i2c_hal_read(  0x8F , &val, 1 );


 val &= ~( 1 << 0 ) | ( 1 << 1 );
 drive |= val;


 ir_gesture_i2c_hal_write(  0x8F , &drive, 1 );
}

uint8_t ir_gesture_get_proximity_gain()
{
 uint8_t val;


 ir_gesture_i2c_hal_read(  0x8F , &val, 1 );


 val = ( val >> 2 ) & 0x03;

 return val;
}

void ir_gesture_set_proximity_gain( uint8_t drive )
{
 uint8_t val=0;

 drive =  (((drive) < (0x03)) ? (drive) : (0x03)) ;


 ir_gesture_i2c_hal_read(  0x8F , &val, 1 );


 val &= ~( 1 << 2 ) | ( 1 << 3 );
 drive = ( drive << 2 ) | val;


 ir_gesture_i2c_hal_write(  0x8F , &drive, 1 );
}

uint8_t ir_gesture_get_gesture_gain()
{
 uint8_t val=0;


 ir_gesture_i2c_hal_read(  0xA3 , &val, 1 );


 val = ( val >> 5 ) & 0x03;

 return val;
}

void ir_gesture_set_gesture_gain( uint8_t gain )
{
 uint8_t val;

 gain =  (((gain) < (0x03)) ? (gain) : (0x03)) ;


 ir_gesture_i2c_hal_read(  0xA3 , &val, 1 );


 val &= ~( 1 << 5 ) | ( 1 << 6 );
 gain = ( gain << 5 ) | val;

 ir_gesture_i2c_hal_write(  0xA3 , &gain, 1 );
}


uint16_t ir_gesture_get_light_int_low_threshold()
{
 uint8_t val_byte;
 uint16_t return_val;


 ir_gesture_i2c_hal_read(  0x85 , &val_byte, 1 );

 return_val = ( uint16_t )( val_byte << 8 );


 ir_gesture_i2c_hal_read(  0x84 , &val_byte, 1 );

 return ( return_val | val_byte );
}

void ir_gesture_set_light_int_low_threshold( uint16_t threshold )
{
 uint8_t val_low;
 uint8_t val_high;


 val_low = threshold & 0x00FF;
 val_high = ( threshold & 0xFF00 ) >> 8;


 ir_gesture_i2c_hal_write(  0x84 , &val_low, 1 );


 ir_gesture_i2c_hal_write(  0x85 , &val_high, 1 );
}

uint16_t ir_gesture_get_light_int_high_threshold()
{
 uint8_t val_byte;
 uint16_t return_val;


 ir_gesture_i2c_hal_read(  0x87 , &val_byte, 1 );

 return_val = ( uint16_t )( val_byte << 8 );


 ir_gesture_i2c_hal_read(  0x86 , &val_byte, 1 );

 return ( return_val | val_byte );
}

void ir_gesture_set_light_int_high_threshold( uint16_t threshold )
{
 uint8_t val_low;
 uint8_t val_high;


 val_low = threshold & 0x00FF;
 val_high = ( threshold & 0xFF00 ) >> 8;


 ir_gesture_i2c_hal_write(  0x87 , &val_high, 1 );


 ir_gesture_i2c_hal_write(  0x86 , &val_low, 1 );
}


uint8_t ir_gesture_get_proximity_int_low_threshold()
{
 uint8_t threshold = 0;


 ir_gesture_i2c_hal_read(  0x89 , &threshold, 1 );

 return threshold;
}

void ir_gesture_set_proximity_int_low_threshold( uint8_t threshold )
{

 ir_gesture_i2c_hal_write(  0x89 , &threshold, 1 );
}

uint8_t ir_gesture_get_proximity_int_high_threshold( void )
{
 uint8_t threshold = 0;


 ir_gesture_i2c_hal_read(  0x8B , &threshold, 1 );

 return threshold;
}

void ir_gesture_set_prox_int_high_threshold( uint8_t threshold )
{

 ir_gesture_i2c_hal_write(  0x8B , &threshold, 1 );
}


 _Bool  ir_gesture_is_ambient_light_int_enable()
{
 uint8_t val = 0;


 ir_gesture_i2c_hal_read(  0x80 , &val, 1 );


 val = ( val >> 4 ) & 0x01;

 return ( val == 1 ) ?  1  :  0 ;
}

void ir_gesture_set_ambient_light_int_enable(  _Bool  enable )
{
 uint8_t val = 0;


 ir_gesture_i2c_hal_read(  0x80 , &val, 1 );


 val &= ~( 1 << 0 );

 if( enable )
 val |= ( 1 << 0 );


 ir_gesture_i2c_hal_write(  0x80 , &val, 1 );
}

 _Bool  ir_gesture_is_proximity_int_enable()
{
 uint8_t val = 0;


 ir_gesture_i2c_hal_read(  0x80 , &val, 1 );


 val = ( val >> 5 ) & 0x01;

 return ( val == 1 ) ?  1  :  0 ;
}

void ir_gesture_set_proximity_int_enable(  _Bool  enable )
{
 uint8_t val = 0;


 ir_gesture_i2c_hal_read(  0x80 , &val, 1 );


 val &= ~( 1 << 5 );

 if( enable )
 val |= ( 1 << 5 );


 ir_gesture_i2c_hal_write(  0x80 , &val, 1 );
}

 _Bool  ir_gesture_is_gesture_int_enable()
{
 uint8_t val = 0;


 ir_gesture_i2c_hal_read(  0xAB , &val, 1 );


 val = ( val >> 1 ) & 0x01;

 return ( val == 1 ) ?  1  :  0 ;
}

void ir_gesture_set_gesture_int_enable(  _Bool  enable )
{
 uint8_t val = 0;


 ir_gesture_i2c_hal_read(  0xAB , &val, 1 );


 val &= ~( 1 << 1 );

 if( enable )
 val |= ( 1 << 1 );


 ir_gesture_i2c_hal_write(  0xAB , &val, 1 );
}


 _Bool  ir_gesture_is_interrupted( gesture_irq_t interrupt )
{
 uint8_t status;

 if( interrupt != INT_AMBIENT_LIGHT && interrupt != INT_GESTURE &&
 interrupt != INT_PROXIMITY )
 return  0 ;

 ir_gesture_i2c_hal_read(  0x93 , &status, 1 );

 return ( status & ( 1 << interrupt ) ) ?  1  :  0 ;
}


void ir_gesture_clear_ambient_light_int()
{
 uint8_t throwaway;

 ir_gesture_i2c_hal_read(  0xE6 , &throwaway, 1 );
}

void ir_gesture_clear_proximity_int()
{
 uint8_t throwaway;

 ir_gesture_i2c_hal_read(  0xE5 , &throwaway, 1 );
}

void ir_gesture_clear_gesture_int()
{
 uint8_t throwaway;

 ir_gesture_i2c_hal_read(  0xE7 , &throwaway, 1 );
}


uint16_t ir_gesture_read_ambient_light( )
{
 uint8_t temp;
 uint16_t return_val;


 ir_gesture_i2c_hal_read(  0x95 , &temp, 1 );

 return_val = ( uint16_t )( temp << 8 );


 ir_gesture_i2c_hal_read(  0x94 , &temp, 1 );

 return ( return_val | temp );
}

uint16_t ir_gesture_read_red_light( void )
{
 uint8_t temp;
 uint16_t return_val;


 ir_gesture_i2c_hal_read(  0x97 , &temp, 1 );

 return_val = ( uint16_t )( temp << 8 );


 ir_gesture_i2c_hal_read(  0x96 , &temp, 1 );

 return ( return_val |= temp );
}

uint16_t ir_gesture_read_green_light( void )
{
 uint8_t temp;
 uint16_t return_val;


 ir_gesture_i2c_hal_read(  0x99 , &temp, 1 );

 return_val = ( uint16_t )( temp << 8 );


 ir_gesture_i2c_hal_read(  0x98 , &temp, 1 );

 return ( return_val |= temp );
}

uint16_t ir_gesture_read_blue_light( void )
{
 uint8_t temp;
 uint16_t return_val;


 ir_gesture_i2c_hal_read(  0x9B , &temp, 1 );

 return_val = ( uint16_t )( temp << 8 );


 ir_gesture_i2c_hal_read(  0x9A , &temp, 1 );

 return ( return_val |= temp );
}

uint8_t ir_gesture_get_led_boost()
{
 uint8_t val;


 ir_gesture_i2c_hal_read(  0x90 , &val, 1 );


 val = ( val >> 4 ) & 0x03;

 return val;
}

void ir_gesture_set_led_boost( uint8_t boost )
{
 uint8_t val;

 boost =  (((boost) < (0x03)) ? (boost) : (0x03)) ;


 ir_gesture_i2c_hal_read(  0x90 , &val, 1 );


 val &= ~( 1 << 4 ) | ( 1 << 5 );
 boost = ( boost << 4 ) | val;


 ir_gesture_i2c_hal_write(  0x90 , &boost, 1 );
}


uint8_t ir_gesture_read_proximity( void )
{
 uint8_t val = 0;


 ir_gesture_i2c_hal_read(  0x9C , &val, 1 );

 return val;
}

uint8_t ir_gesture_get_prox_int_low_thresh()
{
 uint8_t val = 0;


 ir_gesture_i2c_hal_read(  0x89 , &val, 1 );

 return val;
}

void ir_gesture_set_prox_int_low_thresh( uint8_t threshold )
{
 ir_gesture_i2c_hal_write(  0x89 , &threshold, 1 );
}

uint8_t ir_gesture_get_prox_int_high_thresh()
{
 uint8_t val=0;


 ir_gesture_i2c_hal_read(  0x8B , &val, 1 );

 return val;
}

void ir_gesture_set_prox_int_high_thresh( uint8_t threshold )
{
 ir_gesture_i2c_hal_write(  0x8B , &threshold, 1 );
}

 _Bool  ir_gesture_is_prox_gain_comp_enable()
{
 uint8_t val=0;


 ir_gesture_i2c_hal_read(  0x9F , &val, 1 );


 val = ( val >> 5 ) & 0x01;

 return ( val == 1 ) ?  1  :  0 ;
}

void ir_gesture_set_prox_gain_comp_enable(  _Bool  enable )
{
 uint8_t val=0;


 ir_gesture_i2c_hal_read(  0x9F , &val, 1 );


 val &= ~( 1 << 5 );

 if( enable )
 val |= ( 1 << 5 );


 ir_gesture_i2c_hal_write(  0x9F , &val, 1 );
}

uint8_t ir_gesture_get_prox_photo_mask()
{
 uint8_t val = 0;


 ir_gesture_i2c_hal_read(  0x9F , &val, 1 );


 val &= 0x0f;

 return val;
}

void ir_gesture_set_prox_photo_mask( uint8_t mask )
{
 uint8_t val=0;

 mask =  (((mask) < (0x03)) ? (mask) : (0x03)) ;


 ir_gesture_i2c_hal_read(  0x9F , &val, 1 );


 val &= ~( 1 << 0 ) | ( 1 << 1 )| ( 1 << 2 )| ( 1 << 3 );
 mask |= val;


 ir_gesture_i2c_hal_write(  0x9F , &mask, 1 );
}



 _Bool  ir_gesture_available()
{
 uint8_t val;


 ir_gesture_i2c_hal_read(  0xAF , &val, 1 );


 val &=  0b00000001 ;


 return ( val == 1 ) ?  1  :  0 ;
}

gesture_dir_t ir_gesture_read_gesture()
{
 uint8_t fifo_count = 0;
 gesture_data_t gesture_data = {0};
 uint8_t fifo_data[132] = {0};
 int i;


 if( !ir_gesture_available() || !( get_mode() & 0b01000001 ) )
 return DIR_NONE;

 while( 1 )
 {
 ir_gesture_hal_delay(  110  );

 if( ir_gesture_available() )
 {

 ir_gesture_i2c_hal_read(  0xAE , &fifo_count, 1 );

 if( fifo_count > 0 )
 {
 ir_gesture_i2c_hal_read(  0xFC , fifo_data, fifo_count * 4 );


 for( i = 0; i < fifo_count; i += 4 )
 {
 gesture_data.u_data[gesture_data.index] = fifo_data[i];
 gesture_data.d_data[gesture_data.index] = fifo_data[i + 1];
 gesture_data.l_data[gesture_data.index] = fifo_data[i + 2];
 gesture_data.r_data[gesture_data.index] = fifo_data[i + 3];
 gesture_data.index++;
 gesture_data.total_gestures++;
 }

 if( !process_gesture_data( &gesture_data ) )
 {
 if( !decode_gesture( &gesture_data ) )
 {

 }
 }

 gesture_data.index = 0;
 gesture_data.total_gestures = 0;
 }
 } else {
 ir_gesture_hal_delay(  110  );
 decode_gesture( &gesture_data );

 return gesture_data.motion;
 }
 }
}

uint8_t ir_gesture_get_gesture_mode()
{
 uint8_t val=0;


 ir_gesture_i2c_hal_read(  0xAB , &val, 1 );


 val &= 0x01;

 return val;
}

void ir_gesture_set_gesture_mode(  _Bool  mode )
{
 uint8_t val;


 ir_gesture_i2c_hal_read(  0xAB , &val, 1 );


 val &= ~( 1 << 0 );

 if( mode )
 val |= ( 1 << 0 );


 ir_gesture_i2c_hal_write(  0xAB , &val, 1 );
}

uint8_t ir_gesture_enter_thresh()
{
 uint8_t val=0;


 ir_gesture_i2c_hal_read(  0xA0 , &val, 1 );

 return val;
}

void ir_gesture_set_enter_thresh( uint8_t threshold )
{
 ir_gesture_i2c_hal_write(  0xA0 , &threshold , 1);
}

uint8_t ir_gesture_get_exit_thresh()
{
 uint8_t val = 0;


 ir_gesture_i2c_hal_read(  0xA1 , &val, 1 );

 return val;
}

void ir_gesture_set_exit_thresh( uint8_t threshold )
{
 ir_gesture_i2c_hal_write(  0xA1 , &threshold, 1 );
}

uint8_t ir_gesture_get_wait_time()
{
 uint8_t val=0;


 ir_gesture_i2c_hal_read(  0xA3 , &val, 1 );


 val &= 0x07;

 return val;
}

void ir_gesture_set_wait_time( uint8_t time )
{
 uint8_t val=0;

 time =  (((time) < (0x07)) ? (time) : (0x07)) ;


 ir_gesture_i2c_hal_read(  0xA3 , &val, 1 );


 val &= ~( 1 << 0 ) | ( 1 << 1 ) | ( 1 << 2 );
 time |= val;


 ir_gesture_i2c_hal_write(  0xA3 , &time, 1 );
}

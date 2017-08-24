#line 1 "D:/clicks/Stepper_4_Click/SW/framework/c/MIKROBUS_framework.c"
#line 1 "d:/clicks/stepper_4_click/sw/framework/c/mikrobus_framework.h"
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for dspic/include/stdint.h"




typedef signed char int8_t;
typedef signed int int16_t;
typedef signed long int int32_t;


typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long int uint32_t;


typedef signed char int_least8_t;
typedef signed int int_least16_t;
typedef signed long int int_least32_t;


typedef unsigned char uint_least8_t;
typedef unsigned int uint_least16_t;
typedef unsigned long int uint_least32_t;



typedef signed int int_fast8_t;
typedef signed int int_fast16_t;
typedef signed long int int_fast32_t;


typedef unsigned int uint_fast8_t;
typedef unsigned int uint_fast16_t;
typedef unsigned long int uint_fast32_t;


typedef signed int intptr_t;
typedef unsigned int uintptr_t;


typedef signed long int intmax_t;
typedef unsigned long int uintmax_t;
#line 17 "d:/clicks/stepper_4_click/sw/framework/c/mikrobus_framework.h"
typedef enum
{
 MIKROBUS1 = 0,
 MIKROBUS2 = 1,
 MIKROBUS3 = 2,
 MIKROBUS4 = 3

}T_MIKROBUS_slot;

typedef enum
{
 MIKROBUS_AN_PIN = 0,
 MIKROBUS_RST_PIN = 1,
 MIKROBUS_CS_PIN = 2,
 MIKROBUS_SCK_PIN = 3,
 MIKROBUS_MISO_PIN = 4,
 MIKROBUS_MOSI_PIN = 5,
 MIKROBUS_PWM_PIN = 6,
 MIKROBUS_INT_PIN = 7,
 MIKROBUS_RX_PIN = 8,
 MIKROBUS_TX_PIN = 9,
 MIKROBUS_SCL_PIN = 10,
 MIKROBUS_SDA_PIN = 11
}T_MIKROBUS_pin;
#line 1 "d:/clicks/stepper_4_click/sw/framework/c/arm/__arm_systems.h"
#line 1 "d:/clicks/stepper_4_click/sw/framework/c/avr/__avr_systems.h"
#line 1 "d:/clicks/stepper_4_click/sw/framework/c/pic/__pic_systems.h"
#line 1 "d:/clicks/stepper_4_click/sw/framework/c/pic32/__pic32_systems.h"
#line 1 "d:/clicks/stepper_4_click/sw/framework/c/dspic/__dspic_systems.h"
#line 16 "d:/clicks/stepper_4_click/sw/framework/c/dspic/__dspic_systems.h"
typedef enum
{
 GPIO_OUTPUT = 0,
 GPIO_INPUT = 1

}T_GPIO_direction;



typedef void (*T_GPIO_set) (char set);
typedef char (*T_GPIO_get) ();



typedef void (*T_SPI_write) (unsigned data_out);
typedef unsigned (*T_SPI_read) (unsigned buffer);



typedef unsigned int (*T_I2C_start) ();
typedef void (*T_I2C_stop) ();
typedef void (*T_I2C_restart) ();
typedef unsigned int (*T_I2C_write) (unsigned char data_);
typedef unsigned char (*T_I2C_read) (unsigned int ack);



typedef void (*T_UART_write) (unsigned int _data);
typedef unsigned int (*T_UART_read) ();
typedef unsigned (*T_UART_ready) ();
#line 1 "d:/clicks/stepper_4_click/sw/framework/c/ft90x/__ft90x_systems.h"
#line 62 "d:/clicks/stepper_4_click/sw/framework/c/mikrobus_framework.h"
char MIKROBUS1_getAN();
#line 66 "d:/clicks/stepper_4_click/sw/framework/c/mikrobus_framework.h"
void MIKROBUS1_setAN(char set);
#line 72 "d:/clicks/stepper_4_click/sw/framework/c/mikrobus_framework.h"
char MIKROBUS1_getRST();
#line 76 "d:/clicks/stepper_4_click/sw/framework/c/mikrobus_framework.h"
void MIKROBUS1_setRST(char set);
#line 82 "d:/clicks/stepper_4_click/sw/framework/c/mikrobus_framework.h"
char MIKROBUS1_getCS();
#line 86 "d:/clicks/stepper_4_click/sw/framework/c/mikrobus_framework.h"
void MIKROBUS1_setCS(char set);
#line 122 "d:/clicks/stepper_4_click/sw/framework/c/mikrobus_framework.h"
char MIKROBUS1_getPWM();
#line 126 "d:/clicks/stepper_4_click/sw/framework/c/mikrobus_framework.h"
void MIKROBUS1_setPWM(char set);
#line 132 "d:/clicks/stepper_4_click/sw/framework/c/mikrobus_framework.h"
char MIKROBUS1_getINT();
#line 136 "d:/clicks/stepper_4_click/sw/framework/c/mikrobus_framework.h"
void MIKROBUS1_setINT(char set);
#line 189 "d:/clicks/stepper_4_click/sw/framework/c/mikrobus_framework.h"
char MIKROBUS2_getAN();
#line 193 "d:/clicks/stepper_4_click/sw/framework/c/mikrobus_framework.h"
void MIKROBUS2_setAN(char set);
#line 199 "d:/clicks/stepper_4_click/sw/framework/c/mikrobus_framework.h"
char MIKROBUS2_getRST();
#line 203 "d:/clicks/stepper_4_click/sw/framework/c/mikrobus_framework.h"
void MIKROBUS2_setRST(char set);
#line 209 "d:/clicks/stepper_4_click/sw/framework/c/mikrobus_framework.h"
char MIKROBUS2_getCS();
#line 213 "d:/clicks/stepper_4_click/sw/framework/c/mikrobus_framework.h"
void MIKROBUS2_setCS(char set);
#line 249 "d:/clicks/stepper_4_click/sw/framework/c/mikrobus_framework.h"
char MIKROBUS2_getPWM();
#line 253 "d:/clicks/stepper_4_click/sw/framework/c/mikrobus_framework.h"
void MIKROBUS2_setPWM(char set);
#line 259 "d:/clicks/stepper_4_click/sw/framework/c/mikrobus_framework.h"
char MIKROBUS2_getINT();
#line 263 "d:/clicks/stepper_4_click/sw/framework/c/mikrobus_framework.h"
void MIKROBUS2_setINT(char set);
#line 562 "d:/clicks/stepper_4_click/sw/framework/c/mikrobus_framework.h"
void MIKROBUS_gpioDirection(T_MIKROBUS_slot bus, T_MIKROBUS_pin pin,
 T_GPIO_direction dir);
#line 575 "d:/clicks/stepper_4_click/sw/framework/c/mikrobus_framework.h"
typedef void (*T_SPI_initializer)(T_SPI_write wr, T_SPI_read rd);
#line 587 "d:/clicks/stepper_4_click/sw/framework/c/mikrobus_framework.h"
void MIKROBUS1_spiDriverMap(T_SPI_initializer fpInit, const uint32_t *cfg);
#line 599 "d:/clicks/stepper_4_click/sw/framework/c/mikrobus_framework.h"
void MIKROBUS2_spiDriverMap(T_SPI_initializer fpInit, const uint32_t *cfg);
#line 632 "d:/clicks/stepper_4_click/sw/framework/c/mikrobus_framework.h"
typedef void (*T_I2C_initializer)(T_I2C_start st, T_I2C_stop sto, T_I2C_restart rst, T_I2C_write wr, T_I2C_read rd);
#line 644 "d:/clicks/stepper_4_click/sw/framework/c/mikrobus_framework.h"
void MIKROBUS1_i2cDriverMap(T_I2C_initializer fpInit, const uint32_t *cfg);
#line 656 "d:/clicks/stepper_4_click/sw/framework/c/mikrobus_framework.h"
void MIKROBUS2_i2cDriverMap(T_I2C_initializer fpInit, const uint32_t *cfg);
#line 1 "d:/clicks/stepper_4_click/sw/framework/c/arm/__arm_systems.c"
#line 1 "d:/clicks/stepper_4_click/sw/framework/c/avr/__avr_systems.c"
#line 1 "d:/clicks/stepper_4_click/sw/framework/c/avr/boards/easyavr_atmega32.c"
#line 1 "d:/clicks/stepper_4_click/sw/framework/c/avr/__avr_systems.h"
#line 1 "d:/clicks/stepper_4_click/sw/framework/c/pic/__pic_systems.c"
#line 1 "d:/clicks/stepper_4_click/sw/framework/c/pic/boards/easypic_p18f45k22.c"
#line 1 "d:/clicks/stepper_4_click/sw/framework/c/pic/__pic_systems.h"
#line 1 "d:/clicks/stepper_4_click/sw/framework/c/pic/boards/easypic_pro_p18f87k22.c"
#line 1 "d:/clicks/stepper_4_click/sw/framework/c/mikrobus_framework.h"
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for dspic/include/stdint.h"
#line 1 "d:/clicks/stepper_4_click/sw/framework/c/pic32/__pic32_systems.c"
#line 1 "d:/clicks/stepper_4_click/sw/framework/c/pic32/systems/fusion_p32mx795f512l.c"
#line 1 "d:/clicks/stepper_4_click/sw/framework/c/mikrobus_framework.h"
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for dspic/include/stdint.h"
#line 1 "d:/clicks/stepper_4_click/sw/framework/c/pic32/systems/fusion_p32mx460f512l.c"
#line 1 "d:/clicks/stepper_4_click/sw/framework/c/mikrobus_framework.h"
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for dspic/include/stdint.h"
#line 1 "d:/clicks/stepper_4_click/sw/framework/c/pic32/systems/clicker_2_pic32mx.c"
#line 1 "d:/clicks/stepper_4_click/sw/framework/c/mikrobus_framework.h"
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for dspic/include/stdint.h"
#line 1 "d:/clicks/stepper_4_click/sw/framework/c/dspic/__dspic_systems.c"
#line 1 "d:/clicks/stepper_4_click/sw/framework/c/dspic/systems/fusion_p33fj256gp710a.c"
#line 1 "d:/clicks/stepper_4_click/sw/framework/c/mikrobus_framework.h"
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for dspic/include/stdint.h"
#line 5 "d:/clicks/stepper_4_click/sw/framework/c/dspic/systems/fusion_p33fj256gp710a.c"
void MIKROBUS_gpioDirection(T_MIKROBUS_slot bus, T_MIKROBUS_pin pin, T_GPIO_direction dir)
{
 if( bus == MIKROBUS1 )
 {
 switch( pin )
 {
 case MIKROBUS_AN_PIN : TRISB8_bit = dir; break;
 case MIKROBUS_RST_PIN : TRISC1_bit = dir; break;
 case MIKROBUS_CS_PIN : TRISC2_bit = dir; break;
 case MIKROBUS_SCK_PIN : TRISF6_bit = dir; break;
 case MIKROBUS_MISO_PIN : TRISF7_bit = dir; break;
 case MIKROBUS_MOSI_PIN : TRISF8_bit = dir; break;
 case MIKROBUS_PWM_PIN : TRISD0_bit = dir; break;
 case MIKROBUS_INT_PIN : break;
 case MIKROBUS_RX_PIN : TRISF4_bit = dir; break;
 case MIKROBUS_TX_PIN : TRISF5_bit = dir; break;
 case MIKROBUS_SCL_PIN : TRISA2_bit = dir; break;
 case MIKROBUS_SDA_PIN : TRISA3_bit = dir; break;
 default : break;
 }
 }
 if( bus == MIKROBUS2 )
 {
 switch( pin )
 {
 case MIKROBUS_AN_PIN : TRISB9_bit = dir; break;
 case MIKROBUS_RST_PIN : TRISC3_bit = dir; break;
 case MIKROBUS_CS_PIN : TRISC4_bit = dir; break;
 case MIKROBUS_SCK_PIN : TRISF6_bit = dir; break;
 case MIKROBUS_MISO_PIN : TRISF7_bit = dir; break;
 case MIKROBUS_MOSI_PIN : TRISF8_bit = dir; break;
 case MIKROBUS_PWM_PIN : TRISD1_bit = dir; break;
 case MIKROBUS_INT_PIN : break;
 case MIKROBUS_RX_PIN : TRISF12_bit = dir; break;
 case MIKROBUS_TX_PIN : TRISF13_bit = dir; break;
 case MIKROBUS_SCL_PIN : TRISA2_bit = dir; break;
 case MIKROBUS_SDA_PIN : TRISA3_bit = dir; break;
 default : break;
 }
 }
}


void MIKROBUS1_spiDriverMap(T_SPI_initializer fpInit, const uint32_t *cfg)
{
 T_SPI_initializer fCall = fpInit;
 SPI1_Init_Advanced( (unsigned int)cfg[0], (unsigned int)cfg[1],
 (unsigned int)cfg[2], (unsigned int)cfg[3],
 (unsigned int)cfg[4], (unsigned int)cfg[5],
 (unsigned int)cfg[6], (unsigned int)cfg[7] );
 fCall( SPI1_Write, SPI1_Read );
}
void MIKROBUS2_spiDriverMap(T_SPI_initializer fpInit, const uint32_t *cfg)
{
 T_SPI_initializer fCall = fpInit;
 SPI1_Init_Advanced( (unsigned int)cfg[0], (unsigned int)cfg[1],
 (unsigned int)cfg[2], (unsigned int)cfg[3],
 (unsigned int)cfg[4], (unsigned int)cfg[5],
 (unsigned int)cfg[6], (unsigned int)cfg[7] );
 fCall( SPI1_Write, SPI1_Read );
}


void MIKROBUS1_i2cDriverMap(T_I2C_initializer fpInit, const uint32_t *cfg)
{
 T_I2C_initializer fCall = fpInit;
 I2C2_Init( (unsigned long) cfg[0] );
 fCall( I2C2_Start, I2C2_Stop, I2C2_Restart, I2C2_Write, I2C2_Read );
}
void MIKROBUS2_i2cDriverMap(T_I2C_initializer fpInit, const uint32_t *cfg)
{
 T_I2C_initializer fCall = fpInit;
 I2C2_Init( (unsigned long) cfg[0] );
 fCall( I2C2_Start, I2C2_Stop, I2C2_Restart, I2C2_Write, I2C2_Read );
}
#line 96 "d:/clicks/stepper_4_click/sw/framework/c/dspic/systems/fusion_p33fj256gp710a.c"
char MIKROBUS1_getAN()
{
 return RB8_bit;
}
void MIKROBUS1_setAN(char set)
{
 LATB8_bit = set;
}
char MIKROBUS2_getAN()
{
 return RB9_bit;
}
void MIKROBUS2_setAN(char set)
{
 LATB9_bit = set;
}


char MIKROBUS1_getRST()
{
 return RC1_bit;
}
void MIKROBUS1_setRST(char set)
{
 LATC1_bit = set;
}
char MIKROBUS2_getRST()
{
 return RC3_bit;
}
void MIKROBUS2_setRST(char set)
{
 LATC3_bit = set;
}


char MIKROBUS1_getCS()
{
 return RC2_bit;
}
void MIKROBUS1_setCS(char set)
{
 LATC2_bit = set;
}
char MIKROBUS2_getCS()
{
 return RC4_bit;
}
void MIKROBUS2_setCS(char set)
{
 LATC4_bit = set;
}
#line 204 "d:/clicks/stepper_4_click/sw/framework/c/dspic/systems/fusion_p33fj256gp710a.c"
char MIKROBUS1_getPWM()
{
 return RD0_bit;
}
void MIKROBUS1_setPWM(char set)
{
 LATD0_bit = set;
}
char MIKROBUS2_getPWM()
{
 return RD1_bit;
}
void MIKROBUS2_setPWM(char set)
{
 LATD1_bit = set;
}


char MIKROBUS1_getINT()
{

}
void MIKROBUS1_setINT(char set)
{

}
char MIKROBUS2_getINT()
{

}
void MIKROBUS2_setINT(char set)
{

}
#line 1 "d:/clicks/stepper_4_click/sw/framework/c/ft90x/__ft90x_systems.c"
#line 1 "d:/clicks/stepper_4_click/sw/framework/c/ft90x/boards/easyft90x_ft900.c"
#line 1 "d:/clicks/stepper_4_click/sw/framework/c/mikrobus_framework.h"
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for dspic/include/stdint.h"

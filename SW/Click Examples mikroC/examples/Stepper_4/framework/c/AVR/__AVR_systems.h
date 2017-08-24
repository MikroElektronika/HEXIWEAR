/**
@file __AVR_systems.h
@defgroup AVR_SYSTEMS
@{

Supported systems :
- EASYAVR V7
 + ATMEGA32
*/
#ifdef __MIKROC_PRO_FOR_AVR__

#ifndef _AVR_SYSTEMS_
#define _AVR_SYSTEMS_

typedef enum
{     
	GPIO_OUTPUT	= 1,
	GPIO_INPUT	= 0

}T_GPIO_direction;

//---------------------------------------------------------------------------------------------------------------- GPIO

typedef void          	(*T_GPIO_set)      	(char set);
typedef char           	(*T_GPIO_get)  		();

//----------------------------------------------------------------------------------------------------------------- SPI

typedef void 				(*T_SPI_write)		(unsigned short data_out);
typedef unsigned short		(*T_SPI_read)		(unsigned short data_);

//----------------------------------------------------------------------------------------------------------------- I2C

typedef char 				(*T_I2C_start)		();
typedef void 				(*T_I2C_stop)		();
/* DUMMY */ typedef void 	(*T_I2C_restart)	();
typedef void 				(*T_I2C_write) 		(char data_);
typedef char 				(*T_I2C_read) 		(char ack);

//---------------------------------------------------------------------------------------------------------------- UART

typedef void 				(*T_UART_write)		(char data_);
typedef char				(*T_UART_read)      ();
typedef char				(*T_UART_ready)     ();

#ifdef EASYAVR_V7
#define __MIKROBUS_1
#define __MIKROBUS_2
#define __MIKROBUS_3
#endif

#endif
#endif
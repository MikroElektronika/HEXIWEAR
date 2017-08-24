/**
@file __PIC32_systems.h
@defgroup PIC32_SYSTEMS
@{

Supported systems :
- EASYPIC FUSION V7
 + P32MX795H512L
- Clicker 2 PIC32MX
*/
#ifdef __MIKROC_PRO_FOR_PIC32__

#ifndef _PIC32_SYSTEMS_
#define _PIC32_SYSTEMS_

typedef enum
{     
	GPIO_OUTPUT	= 0,
	GPIO_INPUT	= 1

}T_GPIO_direction;

//---------------------------------------------------------------------------------------------------------------- GPIO

typedef void          	(*T_GPIO_set)      	(char set);
typedef char           	(*T_GPIO_get)  		();

//----------------------------------------------------------------------------------------------------------------- SPI

typedef void         	(*T_SPI_write)  	(unsigned long data_out);
typedef unsigned long 	(*T_SPI_read)      	(unsigned long buffer);

//----------------------------------------------------------------------------------------------------------------- I2C

typedef unsigned        (*T_I2C_start)      ();
typedef void            (*T_I2C_stop)       ();
typedef unsigned		(*T_I2C_restart)    ();
typedef unsigned      	(*T_I2C_write)     	(unsigned char data_);
typedef unsigned char 	(*T_I2C_read)       (unsigned ack);

//---------------------------------------------------------------------------------------------------------------- UART

typedef void         	(*T_UART_write)     (unsigned _data);
typedef unsigned      	(*T_UART_read)      ();
typedef unsigned        (*T_UART_ready)     ();


#ifdef CLICKER_2_PIC32MX
#define __MIKROBUS_1
#define __MIKROBUS_2
#endif

#ifdef EASYPIC_FUSION_V7
#define __MIKROBUS_1
#define __MIKROBUS_2
#endif

#endif
#endif


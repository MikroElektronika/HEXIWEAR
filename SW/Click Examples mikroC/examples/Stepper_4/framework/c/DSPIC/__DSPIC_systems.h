/**
@file __DSPIC_systems.h
@defgroup DSPIC_SYSTEMS
@{

Supported systems :
- EASYPIC FUSION V7
 + P33FJ256GP710A
 
*/
#ifdef __MIKROC_PRO_FOR_DSPIC__

#ifndef _DSPIC_SYSTEMS_
#define _DSPIC_SYSTEMS_

typedef enum
{     
	GPIO_OUTPUT	= 0,
	GPIO_INPUT	= 1

}T_GPIO_direction;

//---------------------------------------------------------------------------------------------------------------- GPIO

typedef void          	(*T_GPIO_set)      	(char set);
typedef char           	(*T_GPIO_get)  		();

//----------------------------------------------------------------------------------------------------------------- SPI

typedef void         	(*T_SPI_write)  	(unsigned data_out);
typedef unsigned	 	(*T_SPI_read)      	(unsigned buffer);

//----------------------------------------------------------------------------------------------------------------- I2C

typedef unsigned int  	(*T_I2C_start)      ();
typedef void            (*T_I2C_stop)       ();
typedef void     		(*T_I2C_restart)    ();
typedef unsigned int   	(*T_I2C_write)     	(unsigned char data_);
typedef unsigned char 	(*T_I2C_read)       (unsigned int ack);

//---------------------------------------------------------------------------------------------------------------- UART

typedef void         	(*T_UART_write)     (unsigned int _data);
typedef unsigned int   	(*T_UART_read)      ();
typedef unsigned        (*T_UART_ready)     ();


#ifdef EASYPIC_FUSION_V7
#define __MIKROBUS_1
#define __MIKROBUS_2
#endif

#endif
#endif


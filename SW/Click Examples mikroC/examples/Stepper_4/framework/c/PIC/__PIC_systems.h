/**
@file __PIC_systems.h
@defgroup PIC_SYSTEMS
@{

Supported systems :
- EASYPIC PRO V7
 + P18F87K22
- EASYPIC V7
 + P18F45K22
*/
#ifdef __MIKROC_PRO_FOR_PIC__

#ifndef _PIC_SYSTEMS_
#define _PIC_SYSTEMS_

typedef enum
{     
	GPIO_OUTPUT	= 0,
	GPIO_INPUT	= 1

}T_GPIO_direction;

//---------------------------------------------------------------------------------------------------------------- GPIO

typedef void          	(*T_GPIO_set)      	(char set);
typedef char           	(*T_GPIO_get)  		();

//----------------------------------------------------------------------------------------------------------------- SPI

typedef void         	(*T_SPI_write)  	(unsigned short data_out);
typedef unsigned short 	(*T_SPI_read)      	(unsigned short buffer);

//----------------------------------------------------------------------------------------------------------------- I2C

typedef unsigned short 	(*T_I2C_start)		();
typedef void 			(*T_I2C_stop)		();
typedef void 			(*T_I2C_restart)	();
typedef unsigned short 	(*T_I2C_write) 		(unsigned short data_);
typedef unsigned short 	(*T_I2C_read) 		(unsigned short ack);

//---------------------------------------------------------------------------------------------------------------- UART

typedef void 			(*T_UART_write)		(char _data);
typedef char 			(*T_UART_read)      ();
typedef char 			(*T_UART_ready)     ();

#ifdef EASYPIC_V7
#define __MIKROBUS_1
#define __MIKROBUS_2
#endif

#ifdef EASYPIC_PRO_V7
#define __MIKROBUS_1
#define __MIKROBUS_2
#define __MIKROBUS_3
#endif

#endif
#endif
/**
@file __FT90x_systems.h
@defgroup FT90x_SYSTEMS
@{

Supported systems :
- EASYFT90x V7
 + FT900

*/
#ifdef __MIKROC_PRO_FOR_FT90x__

#ifndef _FT90x_SYSTEMS_
#define _FT90x_SYSTEMS_

typedef enum
{     
	GPIO_OUTPUT	= 0,
	GPIO_INPUT	= 1

}T_GPIO_direction;

//---------------------------------------------------------------------------------------------------------------- GPIO

typedef void          	(*T_GPIO_set)      	(char set);
typedef char           	(*T_GPIO_get)  		();

//----------------------------------------------------------------------------------------------------------------- SPI

typedef void 				(*T_SPI_write)		(unsigned int data_out);
typedef unsigned int		(*T_SPI_read)		(unsigned int data_);

//----------------------------------------------------------------------------------------------------------------- I2C

typedef void 				(*T_I2C_start)		(char slaveAddress);
typedef void 				(*T_I2C_stop)		();
typedef void 				(*T_I2C_restart)	();
typedef char 				(*T_I2C_write) 		(char *bufferOut, unsigned int numBytesToSend);
typedef char 				(*T_I2C_read) 		(char *bufferIn, unsigned int numBytesToReceive);

//---------------------------------------------------------------------------------------------------------------- UART

typedef void 				(*T_UART_write)		(unsigned _data);
typedef unsigned 			(*T_UART_read)      ();
typedef unsigned 			(*T_UART_ready)     ();

#ifdef EASY_FT90x_V7
#define __MIKROBUS_1
#define __MIKROBUS_2
#endif

#endif
#endif
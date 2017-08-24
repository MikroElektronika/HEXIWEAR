#ifndef _TIVA_SYSTEMS_
#define _TIVA_SYSTEMS_
#ifdef __TIVA

typedef enum
{     
	GPIO_OUTPUT	= 0,
	GPIO_INPUT	= 1

}T_GPIO_direction;

//---------------------------------------------------------------------------------------------------------------- GPIO

typedef void          		(*T_GPIO_set)      	(char set);
typedef char           		(*T_GPIO_get)  		();

//----------------------------------------------------------------------------------------------------------------- SPI

typedef void 				(*T_SPI_write)		(unsigned int data_out);
typedef unsigned int 		(*T_SPI_read)		(unsigned long data_);

//----------------------------------------------------------------------------------------------------------------- I2C

typedef void 				(*T_I2C_start)		(char slave_addr, char dir);
/* DUMMY */ typedef void 	(*T_I2C_stop)		();
/* DUMMY */ typedef void 	(*T_I2C_restart)	();
typedef unsigned  			(*T_I2C_write) 		(char dat, char mode);
typedef char 				(*T_I2C_read) 		(char *dat, char mode);

//---------------------------------------------------------------------------------------------------------------- UART

typedef void 				(*T_UART_write)		(unsigned int data_);
typedef unsigned int		(*T_UART_read)      ();
typedef unsigned int		(*T_UART_ready)     ();


#ifdef EASYMX_TIVA_V7
#define __MIKROBUS_1
#define __MIKROBUS_2
#endif

#ifdef EASY_MX_PRO_V7_TIVA
#define __MIKROBUS_1
#define __MIKROBUS_2
#endif

#endif
#endif

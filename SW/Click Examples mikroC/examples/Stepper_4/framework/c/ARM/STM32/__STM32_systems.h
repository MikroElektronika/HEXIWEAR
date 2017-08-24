#ifndef _STM32_SYSTEMS_
#define _STM32_SYSTEMS_
#ifdef __STM32


typedef enum
{     
	GPIO_OUTPUT	= 0,
	GPIO_INPUT	= 1

}T_GPIO_direction;

//---------------------------------------------------------------------------------------------------------------- GPIO

typedef void          		(*T_GPIO_set)      	(char set);
typedef char           		(*T_GPIO_get)  		();

//----------------------------------------------------------------------------------------------------------------- SPI

typedef void 				(*T_SPI_write)		(unsigned data_out);
typedef unsigned 			(*T_SPI_read)		(unsigned long data_);

//----------------------------------------------------------------------------------------------------------------- I2C

typedef unsigned int  		(*T_I2C_start)		();
/* DUMMY */ typedef void 	(*T_I2C_stop)		();
/* DUMMY */ typedef void 	(*T_I2C_restart)	();
typedef unsigned int 		(*T_I2C_write) 		(unsigned char slave_address, unsigned char* ptrdata, unsigned long count, unsigned long END_mode);
typedef void 				(*T_I2C_read) 		(unsigned char slave_address, unsigned char* ptrdata, unsigned long count, unsigned long END_mode);

//---------------------------------------------------------------------------------------------------------------- UART

typedef void 				(*T_UART_write)		(unsigned data_);
typedef unsigned 			(*T_UART_read)      ();
typedef unsigned 			(*T_UART_ready)     ();


#ifdef CLICKER_2_STM32
#define __MIKROBUS_1
#define __MIKROBUS_2
#endif
#ifdef EASYMX_STM32_V7
#define __MIKROBUS_1
#define __MIKROBUS_2
#endif

#endif
#endif
#ifndef _KINETIS_SYSTEMS_
#define _KINETIS_SYSTEMS_
#ifdef __KINETIS

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
typedef unsigned int		(*T_SPI_read)		(unsigned long data_);

//----------------------------------------------------------------------------------------------------------------- I2C

typedef unsigned long  		(*T_I2C_start)		();
/* DUMMY */ typedef void 	(*T_I2C_stop)		();
/* DUMMY */ typedef void 	(*T_I2C_restart)	();
typedef unsigned int 		(*T_I2C_write) 		(unsigned char slave_address, unsigned char* ptrdata, unsigned long count, unsigned long END_mode);
typedef void 				(*T_I2C_read) 		(unsigned char slave_address, unsigned char* ptrdata, unsigned long count, unsigned long END_mode);

//---------------------------------------------------------------------------------------------------------------- UART

typedef void 				(*T_UART_write)		(unsigned int data_);
typedef unsigned int 		(*T_UART_read)      ();
typedef unsigned int 		(*T_UART_ready)     ();


#ifdef HEXIWEAR_DOCKING
#define __MIKROBUS_1
#define __MIKROBUS_2
#define __MIKROBUS_3
#endif

#endif
#endif

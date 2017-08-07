/*

    __MACADDRESS_Hal.h

    Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

------------------------------------------------------------------------------*/
/**
@file       __MACADDRESS_Hal.h
@brief        MAC_Address HAL
@addtogroup   MACADDRESS
@{

@defgroup     MACADDRESS_HAL
@brief MAC_Address Click Hardware Abstract Layer
@{

| HAL Info              |                    |
|:---------------------:|:------------------:|
| Version               | **2.2.1**          |
| Date                  | **Jul 2017**       |
| Developer             | **MikroE FW Team** |

### HAL Description : ###

- Public Functions Prefix : ```HAL_MACADDRESS``` 
- Private Functions Prefix : ```hal_```

MikroC HAL covers all mikroE compilers and it can be divided to 4 parts :
 - GPIO
 - SPI
 - I2C
 - UART

HAL Selection can setup each of this parts to be compiled depend on peripherals
used by the driver (upper layer). For more details about how to use this library 
on non mikroE compilers check MACADDRESS_PORTING_GUIDE.

*/
/* -------------------------------------------------------------------------- */

#include <stdint.h>

#ifndef _MACADDRESS_HAL_
#define _MACADDRESS_HAL_

#ifdef __MIKROC_PRO_FOR_ARM__
#define __MIKROC__
#endif
#ifdef __MIKROC_PRO_FOR_DSPIC__
#define __MIKROC__
#endif
#ifdef __MIKROC_PRO_FOR_PIC__
#define __MIKROC__
#endif
#ifdef __MIKROC_PRO_FOR_PIC32__
#define __MIKROC__
#endif
#ifdef __MIKROC_PRO_FOR_AVR__
#define __MIKROC__
#endif
#ifdef __MIKROC_PRO_FOR_FT90x__
#define __MIKROC__
#endif

/** 
 * @name                                                         HAL Selection
 * @{                                                      *///----------------

//#define __MACADDRESS_GPIO                                             /**< @brief GPIO HAL Selection */
//#define  __MACADDRESS_SPI                                              /**< @brief SPI HAL Selection */
#define  __MACADDRESS_I2C                                              /**< @brief I2C HAL Selection */
//#define __MACADDRESS_UART                                             /**< @brief UART HAL Selection */

/// @} 
/** @name                                                Default Configuration
 *  @{                                             *///-------------------------

#ifdef __MACADDRESS_SPI
extern const uint8_t _MACADDRESS_SPI_CFG[];
#endif
#ifdef __MACADDRESS_I2C
extern const uint8_t _MACADDRESS_I2C_CFG[];
#endif
#ifdef __MACADDRESS_UART
extern const uint8_t _MACADDRESS_UART_CFG[];
#endif

/// @}
/** @name                                                       HAL_GPIO_Types
 *  @{                                                   *///-------------------

#ifdef __MACADDRESS_GPIO
typedef void (*T_MACADDRESS_GPIO_Set)(char);                         
typedef char (*T_MACADDRESS_GPIO_Get)();
#endif

/// @} 
/** @name                                                        HAL_SPI_Types
 *  @{                                                     *///-----------------

#ifdef __MACADDRESS_SPI
#ifdef __MIKROC_PRO_FOR_ARM__ 
typedef void          ( *T_MACADDRESS_SPI_Write )(unsigned int);
typedef unsigned int  ( *T_MACADDRESS_SPI_Read )(unsigned int);
#endif
#ifdef __MIKROC_PRO_FOR_DSPIC__
typedef void 		 	    ( *T_MACADDRESS_SPI_Write )(unsigned int);
typedef unsigned int 	( *T_MACADDRESS_SPI_Read )(unsigned int);
#endif
#ifdef __MIKROC_PRO_FOR_AVR__ 
typedef void          ( *T_MACADDRESS_SPI_Write )(unsigned char);
typedef unsigned char ( *T_MACADDRESS_SPI_Read )(unsigned char);
#endif
#ifdef __MIKROC_PRO_FOR_PIC__
typedef void 		  	  ( *T_MACADDRESS_SPI_Write )(unsigned char);
typedef unsigned char ( *T_MACADDRESS_SPI_Read )(unsigned char);
#endif
#ifdef __MIKROC_PRO_FOR_PIC32__
typedef void 			    ( *T_MACADDRESS_SPI_Write )(unsigned long);
typedef unsigned long	( *T_MACADDRESS_SPI_Read )(unsigned long);
#endif
#ifdef __MIKROC_PRO_FOR_FT90x__
typedef void 			    ( *T_MACADDRESS_SPI_Write )(unsigned char);
typedef unsigned char ( *T_MACADDRESS_SPI_Read )(unsigned char);
#endif
#endif

/// @} 
/** @name                                                        HAL_I2C_Types
 *  @{                                                     *///-----------------

#ifdef __MACADDRESS_I2C
#ifdef __MIKROC_PRO_FOR_ARM__
#if defined( __STM32__ ) || defined( __KINETIS__ ) || defined( __MCHP__ )
typedef unsigned int	( *T_MACADDRESS_I2C_Start )();
/* DUMMY */ typedef void ( *T_MACADDRESS_I2C_Stop )();
/* DUMMY */ typedef void ( *T_MACADDRESS_I2C_Restart )();						
typedef unsigned int 	( *T_MACADDRESS_I2C_Write )(unsigned char, unsigned char*, unsigned long, unsigned long);
typedef void 			    ( *T_MACADDRESS_I2C_Read )(unsigned char, unsigned char*, unsigned long, unsigned long);
    #elif defined( __MSP__ )
/* DUMMY */ typedef void ( *T_MACADDRESS_I2C_Start )();
/* DUMMY */ typedef void ( *T_MACADDRESS_I2C_Stop )();
/* DUMMY */ typedef void ( *T_MACADDRESS_I2C_Restart )();
typedef unsigned int 	( *T_MACADDRESS_I2C_Write )(unsigned char, unsigned char*, unsigned long, unsigned long);
typedef void 			    ( *T_MACADDRESS_I2C_Read )(unsigned char, unsigned char*, unsigned long, unsigned long);
    #elif defined( __TI__ )
typedef void 			    ( *T_MACADDRESS_I2C_Start )(char, char);
/* DUMMY */ typedef void ( *T_MACADDRESS_I2C_Stop )();
/* DUMMY */ typedef void ( *T_MACADDRESS_I2C_Restart )();
typedef unsigned char ( *T_MACADDRESS_I2C_Write )(unsigned char, unsigned char);
typedef unsigned char	( *T_MACADDRESS_I2C_Read )(unsigned char*, unsigned char);
#endif
#endif
#ifdef __MIKROC_PRO_FOR_AVR__
typedef unsigned char	( *T_MACADDRESS_I2C_Start )();
typedef void  		 	  ( *T_MACADDRESS_I2C_Stop )();
/* DUMMY */ typedef void ( *T_MACADDRESS_I2C_Restart )();
typedef void 			    ( *T_MACADDRESS_I2C_Write )(rx unsigned char);
typedef unsigned char ( *T_MACADDRESS_I2C_Read )(rx unsigned char);
#endif
#ifdef __MIKROC_PRO_FOR_PIC__
typedef unsigned char	( *T_MACADDRESS_I2C_Start )();
typedef void 			    ( *T_MACADDRESS_I2C_Stop )();
typedef void 			    ( *T_MACADDRESS_I2C_Restart )();
typedef unsigned char	( *T_MACADDRESS_I2C_Write )(unsigned char);
typedef unsigned char	( *T_MACADDRESS_I2C_Read )(unsigned char);
#endif
#ifdef __MIKROC_PRO_FOR_PIC32__
typedef unsigned int 	( *T_MACADDRESS_I2C_Start )();
typedef void 			    ( *T_MACADDRESS_I2C_Stop )();
typedef unsigned int 	( *T_MACADDRESS_I2C_Restart )();
typedef unsigned int 	( *T_MACADDRESS_I2C_Write )(unsigned char);
typedef unsigned char ( *T_MACADDRESS_I2C_Read )(unsigned int);
#endif
#ifdef __MIKROC_PRO_FOR_DSPIC__
typedef unsigned int 	( *T_MACADDRESS_I2C_Start )();
typedef void 			    ( *T_MACADDRESS_I2C_Stop )();
typedef void 			    ( *T_MACADDRESS_I2C_Restart )();
typedef unsigned int 	( *T_MACADDRESS_I2C_Write )(unsigned char);
typedef unsigned char ( *T_MACADDRESS_I2C_Read )(unsigned int);
#endif
#ifdef __MIKROC_PRO_FOR_FT90x__
typedef void 			    ( *T_MACADDRESS_I2C_Start )(unsigned char);
/* DUMMY */ typedef void ( *T_MACADDRESS_I2C_Stop )();
/* DUMMY */ typedef void ( *T_MACADDRESS_I2C_Restart )();
typedef unsigned char ( *T_MACADDRESS_I2C_Write )(unsigned char*, unsigned int);
typedef unsigned char ( *T_MACADDRESS_I2C_Read )(unsigned char*, unsigned int);
#endif
#endif

/// @} 
/** @name                                                       HAL_UART_Types
 *  @{                                                    *///------------------

#ifdef __MACADDRESS_UART
#ifdef __MIKROC_PRO_FOR_ARM__
typedef void          ( *T_MACADDRESS_UART_Write )(unsigned int);
typedef unsigned int  ( *T_MACADDRESS_UART_Read )();
typedef unsigned int  ( *T_MACADDRESS_UART_Ready )();
#endif
#ifdef __MIKROC_PRO_FOR_DSPIC__
typedef void          ( *T_MACADDRESS_UART_Write )(unsigned int);
typedef unsigned int  ( *T_MACADDRESS_UART_Read )();
typedef unsigned int  ( *T_MACADDRESS_UART_Ready )();
#endif 
#ifdef __MIKROC_PRO_FOR_PIC32__
typedef void 			    ( *T_MACADDRESS_UART_Write )(unsigned int);
typedef unsigned int 	( *T_MACADDRESS_UART_Read )();
typedef unsigned int 	( *T_MACADDRESS_UART_Ready )();
#endif
#ifdef __MIKROC_PRO_FOR_AVR__
typedef void          ( *T_MACADDRESS_UART_Write )(unsigned char);
typedef unsigned char ( *T_MACADDRESS_UART_Read )();
typedef unsigned char ( *T_MACADDRESS_UART_Ready )();
#endif
#ifdef __MIKROC_PRO_FOR_PIC__
typedef void          ( *T_MACADDRESS_UART_Write )(unsigned char);
typedef unsigned char ( *T_MACADDRESS_UART_Read )();
typedef unsigned char ( *T_MACADDRESS_UART_Ready )();
#endif
#ifdef __MIKROC_PRO_FOR_FT90x__
typedef void 			    ( *T_MACADDRESS_UART_Write )(unsigned char);
typedef unsigned char ( *T_MACADDRESS_UART_Read )();
typedef unsigned char ( *T_MACADDRESS_UART_Ready )();
#endif
#endif

/// @} 

#ifdef __cplusplus
extern "C"{
#endif
#ifdef __MACADDRESS_GPIO

/** @name                                                 HAL_Public_Functions
 *  @{                                              *///------------------------
/**
 * @brief MACADDRESS GPIO HAL Pointer Assignation
 *
 * @param[in] ctlAN     Set AN Pin Function Pointer
 * @param[in] ctlRST    Get RST Pin Function Pointer
 */
void 
HAL_MACADDRESS_gpioInit
( 
        T_MACADDRESS_GPIO_Set      ctlAN, 
        T_MACADDRESS_GPIO_Get      ctlRST 
);
#endif
#ifdef __MACADDRESS_SPI

/**
 * @brief MACADDRESS SPI HAL Pointer Assignation
 *
 * @param[in] fnWrite   SPI Write Function
 * @param[in] fnRead    SPI Read  Function
 *
 * Initialization of MACADDRESS SPI driver.
 *
 * @note
 * This function must before usage of other driver functions.
 */
void 
HAL_MACADDRESS_spiInit
( 
        T_MACADDRESS_SPI_Write     fnWrite,
        T_MACADDRESS_SPI_Read      fnRead 
);
#endif
#ifdef __MACADDRESS_I2C

/**
 * @brief MACADDRESS I2C Driver Initialization
 *
 * @param[in] fnStart   I2C Start   Function
 * @param[in] fnStop    I2C Stop    Function
 * @param[in] fnRestart I2C Restart Function
 * @param[in] fnWrite   I2C Write   Function
 * @param[in] fnRead    I2C Read    Function
 *
 * Initialization of MACADDRESS I2C driver.
 *
 * @note
 * This function must be called first.
 *
 * @note
 * Some compilers don't have all the function pointers, for example
 * mikroE ARM compilers don't have the I2C_Stop function, in that case
 * it is enough to provide NULL pointer.
 */
void 
HAL_MACADDRESS_i2cInit
( 
        T_MACADDRESS_I2C_Start     fnStart,
        T_MACADDRESS_I2C_Stop      fnStop,
        T_MACADDRESS_I2C_Restart   fnRestart,
        T_MACADDRESS_I2C_Write     fnWrite,
        T_MACADDRESS_I2C_Read      fnRead 
);
#endif
#ifdef __MACADDRESS_UART

/**
 * @brief MACADDRESS UART Driver Initialization
 *
 * @param[in] fnWrite   UART Write Function
 * @param[in] fnRead    UART Ready Function
 * @param[in] fnReady   UART Data Ready Function
 *
 * Initialization of MACADDRESS UART driver.
 *
 * @note
 * This function must be called first.
 */
void 
HAL_MACADDRESS_uartInit
( 
        T_MACADDRESS_UART_Write   fnWrite,
        T_MACADDRESS_UART_Read    fnRead,
        T_MACADDRESS_UART_Ready   fnReady 
);
#endif

/// @}

#ifdef __cplusplus
} // extern "C"
#endif
#endif

/// @}
/// @}
/* -------------------------------------------------------------------------- */ 
/*
  __MACADDRESS_Hal.h

  Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

    This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.

------------------------------------------------------------------------------*/

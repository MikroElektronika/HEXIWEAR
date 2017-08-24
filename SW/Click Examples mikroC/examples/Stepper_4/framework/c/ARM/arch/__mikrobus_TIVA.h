/**
@file __mikrobus_tiva.h
@brief TIVA MIKROBUS definitions
*/
/**
@defgroup TIVA_MIKROBUS
@ingroup ARM_MIKROBUS_SYSTEM
@brief TIVA MikroBUS systems definitions
*/
/**
@defgroup EASY_MX_PRO_V7_TIVA
@ingroup TIVA_MIKROBUS
@brief Easy MX PRO V7 For STM32  Development Board

**Full featured development board.**

- MikroBUS Sockets : 2
- Supported MCUs :
 + TM
*/
/**
@defgroup MIKROMEDIA_TIVA
@ingroup TIVA_MIKROBUS
@brief Mikromedia for TIVA

- MikroBUS Sockets : 2
- MCU :

@note
MikroBUS sockets available using mikroMedia sheld. 
*/
/**
@defgroup MIKROMEDIA_5_TIVA
@ingroup TIVA_MIKROBUS
@brief Mikromedia 5 for TIVA

- MikroBUS Sockets : 4
- MCU :

@note
MikroBUS sockets available using mikroMedia sheld. 
*/
#ifndef _MIKROBUS_TIVA_
#define _MIKROBUS_TIVA_
#ifdef EASY_MX_PRO_V7_TIVA
/**
@addtogroup 												EASY MX PRO V7 TIVA
@{
*/
#define __SPIBUS_MIKROBUS1          SPI0
#define __SPIMOD_MIKROBUS1          &_GPIO_MODULE_SPI0_A245_AHB
#define __SPIBUS_MIKROBUS2          SPI0
#define __SPIMOD_MIKROBUS2          &_GPIO_MODULE_SPI0_A245_AHB


/** @} */
#endif
#ifdef MIKROMEDIA_TIVA
/**
@addtogroup 													MIKROMEDIA TIVA
@{
*/
#ifdef MIKROMEDIA_TIVA
#define __SPIBUS_MIKROBUS1          SPI0
#define __SPIMOD_MIKROBUS1          &_GPIO_MODULE_SPI0_A245_AHB
#define __SPIBUS_MIKROBUS2          SPI0
#define __SPIMOD_MIKROBUS2          &_GPIO_MODULE_SPI0_A245_AHB


/** @} */
#endif
#ifdef MIKROMEDIA_5_TIVA
/**
@addtogroup 												  MIKROMEDIA 5 TIVA
@{
*/
#define __SPIBUS_MIKROBUS1          SPI3
#define __SPIMOD_MIKROBUS1          &_GPIO_MODULE_SPI3_Q023
#define __SPIBUS_MIKROBUS2          SPI3
#define __SPIMOD_MIKROBUS2          &_GPIO_MODULE_SPI3_Q023
#define __SPIBUS_MIKROBUS3          SPI2
#define __SPIMOD_MIKROBUS3          &_GPIO_MODULE_SPI2_G754_AHB
#define __SPIBUS_MIKROBUS4          SPI2
#define __SPIMOD_MIKROBUS4          &_GPIO_MODULE_SPI2_G754_AHB


/** @} */
#endif
#endif
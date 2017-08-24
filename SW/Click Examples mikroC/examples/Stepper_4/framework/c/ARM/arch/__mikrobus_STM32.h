/**
@file __mikrobus_stm32.h
@brief STM32 MIKROBUS definitions
*/
/**
@defgroup STM_MIKROBUS
@ingroup ARM_MIKROBUS_SYSTEM
@brief STM MikroBUS systems definitions
*/
/**
@defgroup EASY_MX_PRO_V7_STM32
@ingroup STM_MIKROBUS
@brief Easy MX PRO V7 For STM32 Development Board

Full featured development board.

- MikroBUS Sockets : 2
- Supported MCUs :
 + STM32F107VC
 + STM32F407VC
*/
/**
@defgroup STM32_M4_CLICKER
@ingroup STM_MIKROBUS
@brief Clicker for STM32 M4

- MikroBUS Sockets : 1
- MCU :
*/
/**
@defgroup CLICKER_2_STM32
@ingroup STM_MIKROBUS
@brief Clicker 2 for STM32

- MikroBUS Sockets : 2
- MCU :
*/
/**
@defgroup MIKROMEDIA_STM32_M3
@ingroup STM_MIKROBUS
@brief Mikromedia for STM32 M3

- MikroBUS Sockets : 2 
- MCU :

@note
MikroBUS sockets available using mikroMedia sheld. 
*/
/**
@defgroup MIKROMEDIA_STM32_M4
@ingroup STM_MIKROBUS
@brief Mikromedia for STM32 M3

- MikroBUS Sockets : 2 
- MCU :

@note
MikroBUS sockets available using mikroMedia sheld. 
*/
/**
@defgroup MIKROMEDIA_PLUS_STM32
@ingroup STM_MIKROBUS
@brief Mikromedia Plus for STM32

- MikroBUS Sockets : 4
- MCU :

@note
MikroBUS sockets available using mikroMedia sheld. 
*/
/**
@defgroup MIKROMEDIA_PLUS_STM32F7
@ingroup STM_MIKROBUS
@brief Mikromedia Plus for STM32 F7

- MikroBUS Sockets : 4
- MCU :

@note
MikroBUS sockets available using mikroMedia sheld. 
*/
#ifndef _MIKROBUS_STM32_
#define _MIKROBUS_STM32_
#ifdef EASY_MX_PRO_V7_STM32
/** 
@addtogroup 											   EASY MX PRO V7 STM32
@{ 
*/
#define __SPIBUS_MIKROBUS1          SPI3
#define __SPIMOD_MIKROBUS1          &_GPIO_MODULE_SPI3_PC10_11_12
#define __SPIBUS_MIKROBUS2          SPI3
#define __SPIMOD_MIKROBUS2          &_GPIO_MODULE_SPI3_PC10_11_12


/** @} */
#endif
#ifdef STM32_M4_CLICKER
/**
@addtogroup 												   STM32 M4 CLICKER
@{
*/
#define __SPIBUS_MIKROBUS1          SPI2
#define __SPIMOD_MIKROBUS1          &_GPIO_MODULE_SPI2_PB13_14_15


/** @} */
#endif
#ifdef CLICKER_2_STM32
/**
@addtogroup 												    CLICKER 2 STM32
@{
*/
#define __SPIBUS_MIKROBUS1          SPI3
#define __SPIMOD_MIKROBUS1          &_GPIO_MODULE_SPI3_PC10_11_12
#define __SPIBUS_MIKROBUS2          SPI2
#define __SPIMOD_MIKROBUS2          &_GPIO_MODULE_SPI2_PB13_14_15


/** @} */
#endif
#ifdef MIKROMEDIA_STM32_M3
/**
@addtogroup 												MIKROMEDIA STM32 M3
@{
*/
#define __SPIBUS_MIKROBUS1          SPI3
#define __SPIMOD_MIKROBUS1          &_GPIO_MODULE_SPI3_PC10_11_12
#define __SPIBUS_MIKROBUS2          SPI3
#define __SPIMOD_MIKROBUS2          &_GPIO_MODULE_SPI3_PC10_11_12


/** @} */
#endif
#ifdef MIKROMEDIA_STM32_M4
/**
@addtogroup 												MIKROMEDIA STM32 M4
@{
*/
#define __SPIBUS_MIKROBUS1          SPI3
#define __SPIMOD_MIKROBUS1          &_GPIO_MODULE_SPI3_PC10_11_12
#define __SPIBUS_MIKROBUS2          SPI3
#define __SPIMOD_MIKROBUS2          &_GPIO_MODULE_SPI3_PC10_11_12


/** @} */
#endif
#ifdef MIKROMEDIA_PLUS_STM32
/**
@addtogroup 											  MIKROMEDIA PLUS STM32
@{
*/
#define __SPIBUS_MIKROBUS1          SPI1
#define __SPIMOD_MIKROBUS1          &_GPIO_MODULE_SPI1_PA56_PB5
#define __SPIBUS_MIKROBUS2          SPI1
#define __SPIMOD_MIKROBUS2          &_GPIO_MODULE_SPI1_PA56_PB5
#define __SPIBUS_MIKROBUS3          SPI1
#define __SPIMOD_MIKROBUS3          &_GPIO_MODULE_SPI1_PA56_PB5
#define __SPIBUS_MIKROBUS4          SPI1
#define __SPIMOD_MIKROBUS4          &_GPIO_MODULE_SPI1_PA56_PB5


/** @} */
#endif
#ifdef MIKROMEDIA_PLUS_STM32F7
/**
@addtogroup 											MIKROMEDIA PLUS STM32F7
@{
*/
#define __SPIBUS_MIKROBUS1          SPI1
#define __SPIMOD_MIKROBUS1          &_GPIO_MODULE_SPI1_PA56_PB5
#define __SPIBUS_MIKROBUS2          SPI1
#define __SPIMOD_MIKROBUS2          &_GPIO_MODULE_SPI1_PA56_PB5
#define __SPIBUS_MIKROBUS3          SPI1
#define __SPIMOD_MIKROBUS3          &_GPIO_MODULE_SPI1_PA56_PB5
#define __SPIBUS_MIKROBUS4          SPI1
#define __SPIMOD_MIKROBUS4          &_GPIO_MODULE_SPI1_PA56_PB5


/** @} */
#endif
#endif
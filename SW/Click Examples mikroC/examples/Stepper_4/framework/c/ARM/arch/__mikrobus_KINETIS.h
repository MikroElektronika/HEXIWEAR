/**
@file __mikrobus_KINETIS.h
@brief KINETIS MIKROBUS definitions
@{
*/
/**
@defgroup KINETIS_MIKROBUS
@ingroup ARM_MIKROBUS_SYSTEM
@brief KINETIS MikroBUS systems GPIO definitions
*/
/**
@defgroup HEXIWEAR_DOCKING
@ingroup KINETIS_MIKROBUS
@brief HEXIWEAR Docking Station

Addition to HEXIWEAR development system.

- MikroBUS Sockets : 3
- MCUs : MK64
*/
/**
@defgroup HEXIWEAR_BATTERY_PACK
@ingroup KINETIS_MIKROBUS
@brief HEXIWEAR Battery Pack

Addition to HEXIWEAR development system.

- MikroBUS Sockets : 1
- MCUs : MK64
*/
/**
@defgroup KINETIS_CLICKER
@ingroup KINETIS_MIKROBUS
@brief KINETIS Clicker

Clicker for KINETIS development system.

- MikroBUS Sockets : 1
- MCUs : MK64
*/
/**
@defgroup CLICKER_2_KINETIS
@ingroup KINETIS_MIKROBUS
@brief Clicker 2 KINETIS

Clicker for KINETIS development system.

- MikroBUS Sockets : 2
- MCUs : MK64
*/
#ifndef _MIKROBUS_KINETIS_
#define _MIKROBUS_KINETIS_
#ifdef HEXIWEAR_DOCKING
/**
@addtogroup 												   HEXIWEAR_DOCKING
@{
*/
#define __SPIBUS_MIKROBUS1          SPI0
#define __SPIMOD_MIKROBUS1          &_GPIO_Module_SPI0_PC5_7_6
#define __SPIBUS_MIKROBUS2          SPI0
#define __SPIMOD_MIKROBUS2          &_GPIO_Module_SPI0_PC5_7_6
#define __SPIBUS_MIKROBUS3          SPI0
#define __SPIMOD_MIKROBUS3          &_GPIO_Module_SPI0_PC5_7_6


/** @} */
#endif
#ifdef HEXIWEAR_BATTERY_PACK
/**
@addtogroup 											  HEXIWEAR_BATTERY_PACK
@{
*/
#define __SPIBUS_MIKROBUS1          SPI0
#define __SPIMOD_MIKROBUS1          &_GPIO_Module_SPI0_PC5_7_6


/** @} */
#endif
#ifdef KINETIS_CLICKER
/**
@addtogroup 													KINETIS_CLICKER
@{
*/
#define __SPIBUS_MIKROBUS1          SPI0
#define __SPIMOD_MIKROBUS1          &_GPIO_Module_SPI0_PC5_7_6


/** @} */
#endif
#ifdef CLICKER_2_KINETIS
/**
@addtogroup 												  CLICKER_2_KINETIS
@{
*/
#define __SPIBUS_MIKROBUS1          SPI0
#define __SPIMOD_MIKROBUS1          &_GPIO_Module_SPI0_PC5_7_6
#define __SPIBUS_MIKROBUS2          SPI1
#define __SPIMOD_MIKROBUS2          &_GPIO_Module_SPI1_PD5_7_6


/** @} */
#endif
#endif
/**
@file __mikrobus_CEC.h
@brief CEC MIKROBUS definitions
*/
/**
@defgroup CEC_MIKROBUS
@ingroup ARM_MIKROBUS_SYSTEM
@brief CEC MikroBUS systems GPIO definitions
*/
/**
@defgroup CEC1302_CLICKER
@ingroup CEC_MIKROBUS
@brief CEC1302 Clicker

- MikroBUS Sockets : 1
- MCU : CEC1302
*/
/**
@defgroup CEC1702_CLICKER
@ingroup CEC_MIKROBUS
@brief CEC1702 Clicker

- MikroBUS Sockets : 1
- MCU : CEC1302
*/
/**
@defgroup CLICKER_2_CEC1302
@ingroup CEC_MIKROBUS
@brief Clicker 2 for CEC1302 

- MikroBUS Sockets : 2
- MCU : CEC1302
*/
/**
@defgroup CLICKER_2_CEC1702
@ingroup CEC_MIKROBUS
@brief Clicker 2 for CEC1702 

- MikroBUS Sockets : 2
- MCU : CEC1702
*/
#ifndef _MIKROBUS_CEC_
#define _MIKROBUS_CEC_
#ifdef CEC1302_CLICKER
/**
@addtogroup 													CEC1302_CLICKER
@{
*/
#define __SPIBUS_MIKROBUS1          SPI0
#define __SPIMOD_MIKROBUS1


/** @} */
#endif
#ifdef CEC1702_CLICKER
/**
@addtogroup 													CEC1702_CLICKER
@{
*/
#define __SPIBUS_MIKROBUS1          SPI0
#define __SPIMOD_MIKROBUS1


/** @} */
#endif
#ifdef CLICKER_2_CEC1302
/**
@addtogroup 												  CLICKER_2_CEC1302
@{
*/
#define __SPIBUS_MIKROBUS1          SPI0
#define __SPIMOD_MIKROBUS1
#define __SPIBUS_MIKROBUS2          SPI0
#define __SPIMOD_MIKROBUS2


/** @} */
#endif
#ifdef CLICKER_2_CEC1702
/**
@addtogroup 												  CLICKER_2_CEC1702
@{
*/
#define __SPIBUS_MIKROBUS1          SPI0
#define __SPIMOD_MIKROBUS1
#define __SPIBUS_MIKROBUS2          SPI0
#define __SPIMOD_MIKROBUS2


/** @} */
#endif
#endif
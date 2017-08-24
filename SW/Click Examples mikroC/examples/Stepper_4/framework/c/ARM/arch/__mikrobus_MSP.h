/**
@file __mikrobus_MSP.h
@brief MSP MIKROBUS definitions
*/
/**
@defgroup MSP_MIKROBUS
@ingroup ARM_MIKROBUS_SYSTEM
@brief MSP MikroBUS systems definitions
*/
/**
@defgroup MSP432_CLICKER
@ingroup MSP_MIKROBUS
@brief MSP 432 Clicker

- MikroBUS Sockets : 1
- MCU : MSP432
*/
/**
@defgroup CLICKER_2_MSP432
@ingroup MSP_MIKROBUS
@brief Clicker 2 for MSP432

- MikroBUS Sockets : 2
- MCU : MCP432
*/
#ifndef _MIKROBUS_MSP_
#define _MIKROBUS_MSP_
#ifdef MSP432_CLICKER
/**
@addtogroup 													 MSP432_CLICKER
@{
*/
#define __SPIBUS_MIKROBUS1          SPI5
#define __SPIMOD_MIKROBUS1          &_GPIO_MODULE_SPIB0_A576

#define __MIKROBUS1_AN_PIN_PORT         6
#define __MIKROBUS1_AN_PIN          0
#define __MIKROBUS1_RST_PIN_PORT        5
#define __MIKROBUS1_RST_PIN         6
#define __MIKROBUS1_CS_PIN_PORT         5
#define __MIKROBUS1_CS_PIN          0
#define __MIKROBUS1_PWM_PIN_PORT        2
#define __MIKROBUS1_PWM_PIN         7
#define __MIKROBUS1_PIN_PIN_PORT        2
#define __MIKROBUS1_INT_PIN         4

#define MIKROBUS1_PIN_AN_INPUT          DIO_P6IN.B0
#define MIKROBUS1_PIN_AN_OUTPUT         DIO_P6OUT.B0
#define MIKROBUS1_PIN_RST_INPUT         DIO_P5IN.B6
#define MIKROBUS1_PIN_RST_OUTPUT        DIO_P5OUT.B6
#define MIKROBUS1_PIN_CS_INPUT          DIO_P5IN.B0
#define MIKROBUS1_PIN_CS_OUTPUT         DIO_P5OUT.B0
#define MIKROBUS1_PIN_PWM_INPUT         DIO_P2IN.B7
#define MIKROBUS1_PIN_PWM_OUTPUT        DIO_P2OUT.B7
#define MIKROBUS1_PIN_INT_INPUT         DIO_P2IN.B4
#define MIKROBUS1_PIN_INT_OUTPUT        DIO_P2OUT.B4
/** @} */
#endif
#ifdef CLICKER_2_MSP432
/**
@addtogroup 												   CLICKER_2_MSP432
@{
*/
#define __SPIBUS_MIKROBUS1          SPI5
#define __SPIMOD_MIKROBUS1          &_GPIO_MODULE_SPIB0_A576
#define __SPIBUS_MIKROBUS2          SPI5
#define __SPIMOD_MIKROBUS2          &_GPIO_MODULE_SPIB0_A576

#define __MIKROBUS1_AN_PIN_PORT         6
#define __MIKROBUS1_AN_PIN          0
#define __MIKROBUS1_RST_PIN_PORT        5
#define __MIKROBUS1_RST_PIN         6
#define __MIKROBUS1_CS_PIN_PORT         5
#define __MIKROBUS1_CS_PIN          0
#define __MIKROBUS1_PWM_PIN_PORT        2
#define __MIKROBUS1_PWM_PIN         7
#define __MIKROBUS1_PIN_PIN_PORT        2
#define __MIKROBUS1_INT_PIN         4
#define __MIKROBUS2_AN_PIN_PORT         4
#define __MIKROBUS2_AN_PIN          3
#define __MIKROBUS2_RTS_PIN_PORT        6
#define __MIKROBUS2_RST_PIN         7
#define __MIKROBUS2_CS_PIN_PORT         5
#define __MIKROBUS2_CS_PIN          2
#define __MIKROBUS2_PWM_PIN_PORT        2
#define __MIKROBUS2_PWM_PIN         6
#define __MIKROBUS2_INT_PIN_PORT        6
#define __MIKROBUS2_INT_PIN         6

#define MIKROBUS1_PIN_AN_INPUT          DIO_P6IN.B0
#define MIKROBUS1_PIN_AN_OUTPUT         DIO_P6OUT.B0
#define MIKROBUS1_PIN_RST_INPUT         DIO_P5IN.B6
#define MIKROBUS1_PIN_RST_OUTPUT        DIO_P5OUT.B6
#define MIKROBUS1_PIN_CS_INPUT          DIO_P5IN.B0
#define MIKROBUS1_PIN_CS_OUTPUT         DIO_P5OUT.B0
#define MIKROBUS1_PIN_PWM_INPUT         DIO_P2IN.B7
#define MIKROBUS1_PIN_PWM_OUTPUT        DIO_P2OUT.B7
#define MIKROBUS1_PIN_INT_INPUT         DIO_P2IN.B4
#define MIKROBUS1_PIN_INT_OUTPUT        DIO_P2OUT.B4
#define MIKROBUS2_PIN_AN_INPUT          DIO_P4IN.B3
#define MIKROBUS2_PIN_AN_OUTPUT         DIO_P4OUT.B3
#define MIKROBUS2_PIN_RST_INPUT         DIO_P6IN.B7
#define MIKROBUS2_PIN_RST_OUTPUT        DIO_P6OUT.B7
#define MIKROBUS2_PIN_CS_INPUT          DIO_P5IN.B2
#define MIKROBUS2_PIN_CS_OUTPUT         DIO_P5OUT.B2
#define MIKROBUS2_PIN_PWM_INPUT         DIO_P2IN.B6
#define MIKROBUS2_PIN_PWM_OUTPUT        DIO_P2OUT.B6
#define MIKROBUS2_PIN_INT_INPUT         DIO_P6IN.B6
#define MIKROBUS2_PIN_INT_OUTPUT        DIO_P6OUT.B6
/** @} */
#endif
#endif
/**
@file MIKROBUS_framework.h
@brief MIKROBUS Framework

@defgroup MIKROBUS_FRAMEWORK
@{

*/
#include <stdint.h>

#ifndef _MIKROBUS_FRAMEWORK_
#define _MIKROBUS_FRAMEWORK_

//----------------------------------------------------------------------------------------------------------------------
//                                                                                              FRAMEWORK CONST & TYPES
//----------------------------------------------------------------------------------------------------------------------
typedef enum 
{
        MIKROBUS1   = 0,
        MIKROBUS2   = 1,
        MIKROBUS3   = 2,
        MIKROBUS4   = 3

}T_MIKROBUS_slot;

typedef enum 
{
        MIKROBUS_AN_PIN   = 0,
        MIKROBUS_RST_PIN  = 1,
        MIKROBUS_CS_PIN   = 2,
        MIKROBUS_SCK_PIN  = 3,
        MIKROBUS_MISO_PIN = 4,
        MIKROBUS_MOSI_PIN = 5,
        MIKROBUS_PWM_PIN  = 6,
        MIKROBUS_INT_PIN  = 7,
        MIKROBUS_RX_PIN   = 8,
        MIKROBUS_TX_PIN   = 9,
        MIKROBUS_SCL_PIN  = 10,
        MIKROBUS_SDA_PIN  = 11
}T_MIKROBUS_pin;

#include "ARM/__ARM_systems.h"
#include "AVR/__AVR_systems.h"
#include "PIC/__PIC_systems.h"
#include "PIC32/__PIC32_systems.h"
#include "DSPIC/__DSPIC_systems.h"
#include "FT90x/__FT90x_systems.h"

//----------------------------------------------------------------------------------------------------------------------
//                                                                                                  FRAMEWORK FUNCTIONS
//----------------------------------------------------------------------------------------------------------------------

/**
@name MIKROBUS1 GPIO Functions 
@{
*/
#ifdef __MIKROBUS_1
#ifdef PLD_AN_PIN
/**
@brief Get AN Pin State
*/
char MIKROBUS1_getAN();
/**
@brief Set AN Pin State
*/
void MIKROBUS1_setAN(char set);
#endif
#ifdef PLD_RST_PIN
/**
@brief Get RST Pin State
*/
char MIKROBUS1_getRST();
/**
@brief Set RST Pin State
*/
void MIKROBUS1_setRST(char set);
#endif
#ifdef PLD_CS_PIN
/**
@brief Get CS Pin State
*/
char MIKROBUS1_getCS();
/**
@brief Set CS Pin State
*/
void MIKROBUS1_setCS(char set);
#endif
#ifdef PLD_SCK_PIN
/**
@brief Get SCK Pin State
*/
char MIKROBUS1_getSCK();
/**
@brief Set SCK Pin State
*/
void MIKROBUS1_setSCK(char set);
#endif
#ifdef PLD_MISO_PIN
/**
@brief Get MISO Pin State
*/
char MIKROBUS1_getMISO();
/**
@brief Set MISO Pin State
*/
void MIKROBUS1_setMISO(char set);
#endif
#ifdef PLD_MOSI_PIN
/**
@brief Get MOSI Pin State
*/
char MIKROBUS1_getMOSI();
/**
@brief Set MOSI Pin State
*/
void MIKROBUS1_setMOSI(char set);
#endif
#ifdef PLD_PWM_PIN
/**
@brief Get PWM Pin State
*/
char MIKROBUS1_getPWM();
/**
@brief Set PWM Pin State
*/
void MIKROBUS1_setPWM(char set);
#endif
#ifdef PLD_INT_PIN
/**
@brief Get INT Pin State
*/
char MIKROBUS1_getINT();
/**
@brief Set INT Pin State
*/
void MIKROBUS1_setINT(char set);
#endif
#ifdef PLD_RX_PIN
/**
@brief Get RX Pin State
*/
char MIKROBUS1_getRX();
/**
@brief Set RX Pin State
*/
void MIKROBUS1_setRX(char set);
#endif
#ifdef PLD_TX_PIN
/**
@brief Get TX Pin State
*/
char MIKROBUS1_getTX();
/**
@brief Set TX Pin State
*/
void MIKROBUS1_setTX(char set);
#endif
#ifdef PLD_SCL_PIN
/**
@brief Get SCL Pin State
*/
char MIKROBUS1_getSCL();
/**
@brief Set SCL Pin State
*/
void MIKROBUS1_setSCL(char set);
#endif
#ifdef PLD_SDA_PIN
/**
@brief Get SDA Pin State
*/
char MIKROBUS1_getSDA();
/**
@brief Set SDA Pin State
*/
void MIKROBUS1_setSDA(char set);
/** @} */
#endif
#endif
/**
@name MIKROBUS2 GPIO Functions 
@{
*/
#ifdef __MIKROBUS_2
#ifdef PLD_AN_PIN
/**
@brief Get AN Pin State
*/
char MIKROBUS2_getAN();
/**
@brief Set AN Pin State
*/
void MIKROBUS2_setAN(char set);
#endif
#ifdef PLD_RST_PIN
/**
@brief Get RST Pin State
*/
char MIKROBUS2_getRST();
/**
@brief Set RST Pin State
*/
void MIKROBUS2_setRST(char set);
#endif
#ifdef PLD_CS_PIN
/**
@brief Get CS Pin State
*/
char MIKROBUS2_getCS();
/**
@brief Set CS Pin State
*/
void MIKROBUS2_setCS(char set);
#endif
#ifdef PLD_SCK_PIN
/**
@brief Get SCK Pin State
*/
char MIKROBUS2_getSCK();
/**
@brief Set SCK Pin State
*/
void MIKROBUS2_setSCK(char set);
#endif
#ifdef PLD_MISO_PIN
/**
@brief Get MISO Pin State
*/
char MIKROBUS2_getMISO();
/**
@brief Set MISO Pin State
*/
void MIKROBUS2_setMISO(char set);
#endif
#ifdef PLD_MOSI_PIN
/**
@brief Get MOSI Pin State
*/
char MIKROBUS2_getMOSI();
/**
@brief Set MOSI Pin State
*/
void MIKROBUS2_setMOSI(char set);
#endif
#ifdef PLD_PWM_PIN
/**
@brief Get PWM Pin State
*/
char MIKROBUS2_getPWM();
/**
@brief Set PWM Pin State
*/
void MIKROBUS2_setPWM(char set);
#endif
#ifdef PLD_INT_PIN
/**
@brief Get INT Pin State
*/
char MIKROBUS2_getINT();
/**
@brief Set INT Pin State
*/
void MIKROBUS2_setINT(char set);
#endif
#ifdef PLD_RX_PIN
/**
@brief Get RX Pin State
*/
char MIKROBUS2_getRX();
/**
@brief Set RX Pin State
*/
void MIKROBUS2_setRX(char set);
#endif
#ifdef PLD_TX_PIN
/**
@brief Get TX Pin State
*/
char MIKROBUS2_getTX();
/**
@brief Set TX Pin State
*/
void MIKROBUS2_setTX(char set);
#endif
#ifdef PLD_SCL_PIN
/**
@brief Get SCL Pin State
*/
char MIKROBUS2_getSCL();
/**
@brief Set SCL Pin State
*/
void MIKROBUS2_setSCL(char set);
#endif
#ifdef PLD_SDA_PIN
/**
@brief Get SDA Pin State
*/
char MIKROBUS2_getSDA();
/**
@brief Set SDA Pin State
*/
void MIKROBUS2_setSDA(char set);
/** @} */
#endif
#endif
/**
@name MIKROBUS3 GPIO Functions 
@{
*/
#ifdef __MIKROBUS_3
#ifdef PLD_AN_PIN
/**
@brief Get AN Pin State
*/
char MIKROBUS3_getAN();
/**
@brief Set AN Pin State
*/
void MIKROBUS3_setAN(char set);
#endif
#ifdef PLD_RST_PIN
/**
@brief Get RST Pin State
*/
char MIKROBUS3_getRST();
/**
@brief Set RST Pin State
*/
void MIKROBUS3_setRST(char set);
#endif
#ifdef PLD_CS_PIN
/**
@brief Get CS Pin State
*/
char MIKROBUS3_getCS();
/**
@brief Set CS Pin State
*/
void MIKROBUS3_setCS(char set);
#endif
#ifdef PLD_SCK_PIN
/**
@brief Get SCK Pin State
*/
char MIKROBUS3_getSCK();
/**
@brief Set SCK Pin State
*/
void MIKROBUS3_setSCK(char set);
#endif
#ifdef PLD_MISO_PIN
/**
@brief Get MISO Pin State
*/
char MIKROBUS3_getMISO();
/**
@brief Set MISO Pin State
*/
void MIKROBUS3_setMISO(char set);
#endif
#ifdef PLD_MOSI_PIN
/**
@brief Get MOSI Pin State
*/
char MIKROBUS3_getMOSI();
/**
@brief Set MOSI Pin State
*/
void MIKROBUS3_setMOSI(char set);
#endif
#ifdef PLD_PWM_PIN
/**
@brief Get PWM Pin State
*/
char MIKROBUS3_getPWM();
/**
@brief Set PWM Pin State
*/
void MIKROBUS3_setPWM(char set);
#endif
#ifdef PLD_INT_PIN
/**
@brief Get INT Pin State
*/
char MIKROBUS3_getINT();
/**
@brief Set INT Pin State
*/
void MIKROBUS3_setINT(char set);
#endif
#ifdef PLD_RX_PIN
/**
@brief Get RX Pin State
*/
char MIKROBUS3_getRX();
/**
@brief Set RX Pin State
*/
void MIKROBUS3_setRX(char set);
#endif
#ifdef PLD_TX_PIN
/**
@brief Get TX Pin State
*/
char MIKROBUS3_getTX();
/**
@brief Set TX Pin State
*/
void MIKROBUS3_setTX(char set);
#endif
#ifdef PLD_SCL_PIN
/**
@brief Get SCL Pin State
*/
char MIKROBUS3_getSCL();
/**
@brief Set SCL Pin State
*/
void MIKROBUS3_setSCL(char set);
#endif
#ifdef PLD_SDA_PIN
/**
@brief Get SDA Pin State
*/
char MIKROBUS3_getSDA();
/**
@brief Set SDA Pin State
*/
void MIKROBUS3_setSDA(char set);
/** @} */
#endif
#endif
/**
@name MIKROBUS4 GPIO Functions 
@{
*/
#ifdef __MIKROBUS_4
#ifdef PLD_AN_PIN
/**
@brief Get AN Pin State
*/
char MIKROBUS4_getAN();
/**
@brief Set AN Pin State
*/
void MIKROBUS4_setAN(char set);
#endif
#ifdef PLD_RST_PIN
/**
@brief Get RST Pin State
*/
char MIKROBUS4_getRST();
/**
@brief Set RST Pin State
*/
void MIKROBUS4_setRST(char set);
#endif
#ifdef PLD_CS_PIN
/**
@brief Get CS Pin State
*/
char MIKROBUS4_getCS();
/**
@brief Set CS Pin State
*/
void MIKROBUS4_setCS(char set);
#endif
#ifdef PLD_SCK_PIN
/**
@brief Get SCK Pin State
*/
char MIKROBUS4_getSCK();
/**
@brief Set SCK Pin State
*/
void MIKROBUS4_setSCK(char set);
#endif
#ifdef PLD_MISO_PIN
/**
@brief Get MISO Pin State
*/
char MIKROBUS4_getMISO();
/**
@brief Set MISO Pin State
*/
void MIKROBUS4_setMISO(char set);
#endif
#ifdef PLD_MOSI_PIN
/**
@brief Get MOSI Pin State
*/
char MIKROBUS4_getMOSI();
/**
@brief Set MOSI Pin State
*/
void MIKROBUS4_setMOSI(char set);
#endif
#ifdef PLD_PWM_PIN
/**
@brief Get PWM Pin State
*/
char MIKROBUS4_getPWM();
/**
@brief Set PWM Pin State
*/
void MIKROBUS4_setPWM(char set);
#endif
#ifdef PLD_INT_PIN
/**
@brief Get INT Pin State
*/
char MIKROBUS4_getINT();
/**
@brief Set INT Pin State
*/
void MIKROBUS4_setINT(char set);
#endif
#ifdef PLD_RX_PIN
/**
@brief Get RX Pin State
*/
char MIKROBUS4_getRX();
/**
@brief Set RX Pin State
*/
void MIKROBUS4_setRX(char set);
#endif
#ifdef PLD_TX_PIN
/**
@brief Get TX Pin State
*/
char MIKROBUS4_getTX();
/**
@brief Set TX Pin State
*/
void MIKROBUS4_setTX(char set);
#endif
#ifdef PLD_SCL_PIN
/**
@brief Get SCL Pin State
*/
char MIKROBUS4_getSCL();
/**
@brief Set SCL Pin State
*/
void MIKROBUS4_setSCL(char set);
#endif
#ifdef PLD_SDA_PIN
/**
@brief Get SDA Pin State
*/
char MIKROBUS4_getSDA();
/**
@brief Set SDA Pin State
*/
void MIKROBUS4_setSDA(char set);
/** @} */
#endif
#endif

void MIKROBUS_gpioDirection(T_MIKROBUS_slot bus, T_MIKROBUS_pin pin,
                            T_GPIO_direction dir);

/**
@name MIKROBUS_PERIPHERALS
@{
*/
#ifdef __SPI_CLICK
/**
@type SPI initDriver Prototype

Common prototype for all click board with SPI peripheral.
*/
typedef void (*T_SPI_initializer)(T_SPI_write wr, T_SPI_read rd);

#ifdef __MIKROBUS_1
/**
@brief MIKROBUS1 SPI Driver Initializer
 
@param[in] fpInit         pointer to initDriver function
@param[in] cfg                peripheral configuration

Function will initialize SPI peripheral on MIKROBUS1 and assign proper 
pointers to click driver.
*/
void MIKROBUS1_spiDriverMap(T_SPI_initializer fpInit, const uint32_t *cfg);
#endif
#ifdef __MIKROBUS_2
/**
@brief MIKROBUS2 SPI Driver Initializer
 
@param[in] fpInit         pointer to initDriver function
@param[in] cfg                peripheral configuration

Function will initialize SPI peripheral on MIKROBUS2 and assign proper 
pointers to click driver.
*/
void MIKROBUS2_spiDriverMap(T_SPI_initializer fpInit, const uint32_t *cfg);
#endif
#ifdef __MIKROBUS_3
/**
@brief MIKROBUS3 SPI Driver Initializer
 
@param[in] fpInit         pointer to initDriver function
@param[in] cfg                peripheral configuration

Function will initialize SPI peripheral on MIKROBUS3 and assign proper 
pointers to click driver.
*/
void MIKROBUS3_spiDriverMap(T_SPI_initializer fpInit, const uint32_t *cfg);
#endif
#ifdef __MIKROBUS_4
/**
@brief MIKROBUS4 SPI Driver Initializer
 
@param[in] fpInit         pointer to initDriver function
@param[in] cfg                peripheral configuration

Function will initialize SPI peripheral on MIKROBUS4 and assign proper 
pointers to click driver.
*/
void MIKROBUS4_spiDriverMap(T_SPI_initializer fpInit, const uint32_t *cfg);
#endif
#endif
#ifdef __I2C_CLICK
/**
@type I2C initDriver Prototype

Common prototype for all click board with I2C peripheral.
*/
typedef void (*T_I2C_initializer)(T_I2C_start st, T_I2C_stop sto, T_I2C_restart rst, T_I2C_write wr, T_I2C_read rd);

#ifdef __MIKROBUS_1
/**
@brief MIKROBUS1 I2C Driver Initializer
 
@param[in] fpInit         pointer to initDriver function
@param[in] cfg                peripheral configuration

Function will initialize I2C peripheral on MIKROBUS1 and assign proper 
pointers to click driver.
*/
void MIKROBUS1_i2cDriverMap(T_I2C_initializer fpInit, const uint32_t *cfg);
#endif
#ifdef __MIKROBUS_2
/**
@brief MIKROBUS2 I2C Driver Initializer
 
@param[in] fpInit         pointer to initDriver function
@param[in] cfg                peripheral configuration

Function will initialize I2C peripheral on MIKROBUS2 and assign proper 
pointers to click driver.
*/
void MIKROBUS2_i2cDriverMap(T_I2C_initializer fpInit, const uint32_t *cfg);
#endif
#ifdef __MIKROBUS_3
/**
@brief MIKROBUS3 I2C Driver Initializer
 
@param[in] fpInit         pointer to initDriver function
@param[in] cfg                peripheral configuration

Function will initialize I2C peripheral on MIKROBUS3 and assign proper 
pointers to click driver.
*/
void MIKROBUS3_i2cDriverMap(T_I2C_initializer fpInit, const uint32_t *cfg);
#endif
#ifdef __MIKROBUS_4
/**
@brief MIKROBUS4 I2C Driver Initializer
 
@param[in] fpInit         pointer to initDriver function
@param[in] cfg                peripheral configuration

Function will initialize I2C peripheral on MIKROBUS4 and assign proper 
pointers to click driver.
*/
void MIKROBUS4_i2cDriverMap(T_I2C_initializer fpInit, const uint32_t *cfg);
#endif
#endif
#ifdef __UART_CLICK
/**
@type I2C initDriver Prototype

Common prototype for all click board which using UART peripheral.
*/
typedef void (*T_UART_initializer)(T_UART_write wr, T_UART_read rd, T_UART_ready rdy);
#ifdef __MIKROBUS_1
/**
@brief MIKROBUS1 UART Driver Initializer
 
@param[in] fpInit         pointer to initDriver function
@param[in] cfg                peripheral configuration

Function will initialize UART peripheral on MIKROBUS1 and assign proper 
pointers to click driver.
*/
void MIKROBUS1_uartDriverMap(T_UART_initializer fpInit, const uint32_t *cfg);
#endif
#ifdef __MIKROBUS_2
/**
@brief MIKROBUS2 UART Driver Initializer
 
@param[in] fpInit         pointer to initDriver function
@param[in] cfg                peripheral configuration

Function will initialize UART peripheral on MIKROBUS2 and assign proper 
pointers to click driver.
*/
void MIKROBUS2_uartDriverMap(T_UART_initializer fpInit, const uint32_t *cfg);
#endif
#ifdef __MIKROBUS_3
/**
@brief MIKROBUS3 UART Driver Initializer
 
@param[in] fpInit         pointer to initDriver function
@param[in] cfg                peripheral configuration

Function will initialize UART peripheral on MIKROBUS3 and assign proper 
pointers to click driver.
*/
void MIKROBUS3_uartDriverMap(T_UART_initializer fpInit, const uint32_t *cfg);
#endif
#ifdef __MIKROBUS_4
/**
@brief MIKROBUS4 UART Driver Initializer
 
@param[in] fpInit         pointer to initDriver function
@param[in] cfg                peripheral configuration

Function will initialize UART peripheral on MIKROBUS4 and assign proper 
pointers to click driver.
*/
void MIKROBUS4_uartDriverMap(T_UART_initializer fpInit, const uint32_t *cfg);
#endif
#endif
/** @} */
#endif
/** @} */
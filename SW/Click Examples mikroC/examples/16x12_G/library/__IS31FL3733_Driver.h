/*

  __IS31FL3733.h

  Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

------------------------------------------------------------------------------*/

/**
   @file           __IS31FL3733_Driver.h
   @brief                         16x12_G Click

   @mainpage 16x12_G Click
   @{

   ### Click Description ###

   16x12 G click carries a matrix of 192 green LEDs and the IS31FL3733 LED
   driver with individual Auto Breath function. Each LED can be controlled
   individually - on/off and dimming with 8-bit PWM data. It also features
   3 Auto Breathing Modes, which can be assigned to individual LEDs. The click
   communicates with the target MCU through the mikroBUS™ I2C interface (SCL,
   SDA).

   ### Features ###

   - 16x12 green LEDs matrix
   - Selectable 3 Auto Breath Modes for each dot
   - Individual on/off control
   - I2C interface
   - 3.3V or 5V power supply
   @}

   @addtogroup  IS31FL3733
   @brief       16x12_G Click Driver
   @{

   Global Library Prefix : **IS31FL3733**
   Version               : **1.0.0**
   Date                  : July 2017
   Developer             : *Irena Blagojevic*

   This library constains functions for 16x12_G LED Matrix click board.
*/
/**
   @example Click_16x12_G_STM.c
   @example Click_16x12_G_TIVA.c
   @example Click_16x12_G_KINETIS.c
   @example Click_16x12_G_PIC.c
   @example Click_16x12_G_PIC32.c
   @example Click_16x12_G_DSPIC.c
   @example Click_16x12_G_AVR.c

*/
/*--------------------------------------------------------------------------*/

#ifndef _IS31FL3733_H_
#define _IS31FL3733_H_

#include <stdint.h>

///@cond
/*-------------------------------------------------------------- HAL POINTERS */
#if defined( __MIKROC_PRO_FOR_ARM__ )
#if defined( __STM32__ ) || defined( __KINETIS__ ) || defined( __MCHP__ )

typedef unsigned int ( *T_IS31FL3733_I2C_Start )();
typedef unsigned int ( *T_IS31FL3733_I2C_Write )( unsigned char slave_address,
                                                  unsigned char *buffer,
                                                  unsigned long count,
                                                  unsigned long end_mode );
typedef void ( *T_IS31FL3733_I2C_Read )( unsigned char slave_address,
                                         unsigned char *buffer,
                                         unsigned long count,
                                         unsigned long end_mode );
#elif defined( __MSP__ )

typedef unsigned int ( *T_IS31FL3733_I2C_Write )( unsigned char slave_address,
                                                  unsigned char *buffer,
                                                  unsigned long count,
                                                  unsigned long end_mode );

typedef void ( *T_IS31FL3733_I2C_Read )( unsigned char slave_address,
                                         unsigned char *buffer,
                                         unsigned long count,
                                         unsigned long end_mode );

#elif defined( __TI__ )

typedef void ( *T_IS31FL3733_I2C_SetSlaveAddress )( char slave_address,
                                                    char dir );

typedef unsigned char ( *T_IS31FL3733_I2C_Write )( unsigned char data_in,
                                                   unsigned char mode );
typedef unsigned char( *T_IS31FL3733_I2C_Read )( unsigned char *data_out,
                                                 unsigned char mode );
#endif

#elif  defined( __MIKROC_PRO_FOR_AVR__ )

typedef unsigned char( *T_IS31FL3733_I2C_Start )();
typedef void  ( *T_IS31FL3733_I2C_Stop )();
typedef void ( *T_IS31FL3733_I2C_Close )();
typedef void ( *T_IS31FL3733_I2C_Write )( unsigned char data_out );
typedef unsigned char ( *T_IS31FL3733_I2C_Read )( unsigned char ack );

#elif  defined( __MIKROC_PRO_FOR_PIC__ )

typedef unsigned char( *T_IS31FL3733_I2C_Start )();
typedef void ( *T_IS31FL3733_I2C_Stop )();
typedef void ( *T_IS31FL3733_I2C_Restart )();
typedef unsigned char( *T_IS31FL3733_I2C_Write )( unsigned char data_out );
typedef unsigned char( *T_IS31FL3733_I2C_Read )( unsigned char ack );

#elif defined( __MIKROC_PRO_FOR_PIC32__ )

typedef unsigned int ( *T_IS31FL3733_I2C_Idle )();
typedef unsigned int ( *T_IS31FL3733_I2C_Start )();
typedef void ( *T_IS31FL3733_I2C_Stop )();
typedef unsigned int ( *T_IS31FL3733_I2C_Restart )();
typedef unsigned int ( *T_IS31FL3733_I2C_Write )( unsigned char data_out );
typedef unsigned char ( *T_IS31FL3733_I2C_Read )( unsigned int ack );

#elif defined( __MIKROC_PRO_FOR_DSPIC__ )

typedef unsigned int ( *T_IS31FL3733_I2C_Start )();
typedef void ( *T_IS31FL3733_I2C_Stop )();
typedef void ( *T_IS31FL3733_I2C_Restart )();
typedef unsigned int ( *T_IS31FL3733_I2C_Write )( unsigned char data_out );
typedef unsigned char ( *T_IS31FL3733_I2C_Read )( unsigned int ack );

#elif defined( __MIKROC_PRO_FOR_8051__ )

typedef unsigned char( *T_IS31FL3733_I2C_Start )();
typedef void ( *T_IS31FL3733_I2C_Stop )();
typedef void ( *T_IS31FL3733_I2C_Write )( unsigned char data_out );
typedef unsigned char( *T_IS31FL3733_I2C_Read )( unsigned char ack );

#elif defined( __MIKROC_PRO_FOR_FT90x__ )

typedef void ( *T_IS31FL3733_I2C_SetSlaveAddress )
(uint8_t slave_address);
typedef unsigned char ( *T_IS31FL3733_I2C_Write )( unsigned char *buffer,
                                                   unsigned int count);
typedef unsigned char ( *T_IS31FL3733_I2C_Read )( unsigned char *buffer,
                                                  unsigned int count);
#else
typedef void ( *T_IS31FL3733_I2C_Start )();
typedef void ( *T_IS31FL3733_I2C_Stop )();
typedef void ( *T_IS31FL3733_I2C_Write )( uint8_t input);
typedef uint8_t ( *T_IS31FL3733_I2C_Read )( uint8_t input);
#endif
/*----------------------------------------------------------------------------*/
///@endcond
/**
 * @name                 16x12_G Click Registers
 *//*-------------------------------------------------------------------------*/
///@{


static const uint8_t _IS31FL3733_PSR = 0xFD;
/**< Page select register. Write only. */
static const uint8_t _IS31FL3733_PSWL = 0xFE;
/**< Page select register write lock. Read/Write. */
static const uint8_t _IS31FL3733_IMR = 0xF0;
/**< Interrupt mask register. Write only. */
static const uint8_t _IS31FL3733_ISR = 0xF1;
/**< Interrupt status register. Read only. */

static const uint8_t _IS31FL3733_PSWL_DISABLE = 0x00;
/**< PSWL register bit: Disable write to Page Select register. */
static const uint8_t _IS31FL3733_PSWL_ENABLE  = 0xC5;
/**< PSWL register bit: Enable write to Page select register. */

static const uint8_t _IS31FL3733_IMR_IAC = 0x08;
/**< IMR register bits. Auto Clear Interrupt bit.*/
static const uint8_t _IS31FL3733_IMR_IAB = 0x04;
/**< Auto Breath Interrupt bit. */
static const uint8_t _IS31FL3733_IMR_IS  = 0x02;
/**< Dot Short Interrupt bit. */
static const uint8_t _IS31FL3733_IMR_IO  = 0x01;
/**< Dot Open Interrupt bit. */

static const uint8_t _IS31FL3733_ISR_ABM3 = 0x10;
/**< ISR register bits. Auto Breath Mode 3 Finish Bit. */
static const uint8_t _IS31FL3733_ISR_ABM2 = 0x08;
/**< Auto Breath Mode 2 Finish Bit. */
static const uint8_t _IS31FL3733_ISR_ABM1 = 0x04;
/**< Auto Breath Mode 1 Finish Bit. */
static const uint8_t _IS31FL3733_ISR_SB   = 0x02;
/**< Short Bit. */
static const uint8_t _IS31FL3733_ISR_OB   = 0x01;
/**< Open Bit. */

static const uint8_t _IS31FL3733_CR_SYNC_MASTER = 0x40;
/**< CR register bits. Configure as clock master device. */
static const uint8_t _IS31FL3733_CR_SYNC_SLAVE  = 0x80;
/**< Configure as clock slave device. */
static const uint8_t _IS31FL3733_CR_OSD         = 0x04;
/**< Open/Short detection enable bit. */
static const uint8_t _IS31FL3733_CR_BEN         = 0x02;
/**< Auto breath mode enable bit. */
static const uint8_t _IS31FL3733_CR_SSD         = 0x01;
/**< Software shutdown bit. */

static const uint16_t _IS31FL3733_LEDONOFF = 0x0000;
/**< Registers in Page 0. ON/OFF state control for each LED. Write only. */
static const uint16_t _IS31FL3733_LEDOPEN = 0x0018;
/**< Open state for each LED. Read only. */
static const uint16_t _IS31FL3733_LEDSHORT = 0x0030;
/**< Short state for each LED. Read only. */

static const uint16_t _IS31FL3733_LEDPWM = 0x0100;
/**< Registers in Page 1. PWM duty for each LED. Write only. */
static const uint16_t _IS31FL3733_LEDABM = 0x0200;
/**< Registers in Page 2. Auto breath mode for each LED. Write only. */

static const uint16_t _IS31FL3733_CR    = 0x0300;
/**< Registers in Page 3. Configuration Register. Write only. */
static const uint16_t _IS31FL3733_GCC   = 0x0301;
/**< Global Current Control register. Write only. */

static const uint16_t _IS31FL3733_ABM1  = 0x0302;
/**< Auto breath control register for ABM-1. Write only. */
static const uint16_t _IS31FL3733_ABM2  = 0x0306;
/**< Auto breath control register for ABM-2. Write only. */
static const uint16_t _IS31FL3733_ABM3  = 0x030A;
/**< Auto breath control register for ABM-3. Write only. */
static const uint16_t _IS31FL3733_TUR   = 0x030E;
/**< Time update register. Write only. */
static const uint16_t _IS31FL3733_SWPUR = 0x030F;
/**< SWy Pull-Up Resistor selection register. Write only. */
static const uint16_t _IS31FL3733_CSPDR = 0x0310;
/**< CSx Pull-Down Resistor selection register. Write only. */
static const uint16_t _IS31FL3733_RESET = 0x0311;
/**< Reset register. Read only. */

///@}
/**
 * @name                 16x12_G Click Return Values
 *//*-------------------------------------------------------------------------*/
///@{



///@}
/**
 * @name                 16x12_G Click Constants
 *//*-------------------------------------------------------------------------*/
///@{

static const uint8_t _IS31FL3733_CS = 16;
/**< Number of CS lines. */
static const uint8_t  _IS31FL3733_SW = 12;
/**< Number of SW lines. */

static const uint8_t _IS31FL3733_GND_ADDR = 0x00;
/**< ADDRx pin connected to GND. */
static const uint8_t _IS31FL3733_SCL_ADDR = 0x01;
/**< ADDRx pin connected to SCL. */
static const uint8_t _IS31FL3733_SDA_ADDR = 0x02;
/**< ADDRx pin connected to SDA. */
static const uint8_t _IS31FL3733_VCC_ADDR = 0x03;
/**< ADDRx pin connected to VCC. */

static const uint16_t IS31FL3733_ABM_LOOP_TIMES_MAX = 0x0FFF;
/**< Maximum number of ABM loop times. */

static const uint16_t IS31FL3733_ABM_LOOP_FOREVER = 0x0000;
/**< Enter to ABM endless loop. */

///@}
/**
 * @name                 16x12_G Click Types
 *//*-------------------------------------------------------------------------*/
///@{

/** LED state enumeration. */
typedef enum {
    _IS31FL3733_LED_STATE_OFF = 0x00, ///< LED is off.
    _IS31FL3733_LED_STATE_ON  = 0x01  ///< LED is on.
} T_IS31FL3733_LED_STATE;

/** LED status enumeration. */
typedef enum {
    _IS31FL3733_LED_STATUS_NORMAL  = 0x00, ///< Normal LED status.
    _IS31FL3733_LED_STATUS_OPEN    = 0x01, ///< LED is open.
    _IS31FL3733_LED_STATUS_SHORT   = 0x02, ///< LED is short.
    _IS31FL3733_LED_STATUS_UNKNOWN = 0x03  ///< Unknown LED status.
} T_IS31FL3733_LED_STATUS;

/** Pull-Up or Pull-Down resistor value. */
typedef enum {
    _IS31FL3733_RESISTOR_OFF = 0x00, ///< No resistor.
    _IS31FL3733_RESISTOR_500 = 0x01, ///< 0.5 kOhm pull-up resistor.
    _IS31FL3733_RESISTOR_1K  = 0x02, ///< 1.0 kOhm pull-up resistor.
    _IS31FL3733_RESISTOR_2K  = 0x03, ///< 2.0 kOhm pull-up resistor.
    _IS31FL3733_RESISTOR_4K  = 0x04, ///< 4.0 kOhm pull-up resistor.
    _IS31FL3733_RESISTOR_8K  = 0x05, ///< 8.0 kOhm pull-up resistor.
    _IS31FL3733_RESISTOR_16K = 0x06, ///< 16 kOhm pull-up resistor.
    _IS31FL3733_RESISTOR_32K = 0x07  ///< 32 kOhm pull-up resistor.
} T_IS31FL3733_RESISTOR;

/** IS31FL3733 structure. */
typedef struct {
    /// Address on I2C bus.
    uint8_t address;
    /// State of individual LED's. Bitmask, that can't be read back from chip
    uint8_t leds[ _IS31FL3733_SW * _IS31FL3733_CS / 8 ];
    /// Pointer to I2C write register function.
    uint8_t (*i2cWriteReg) ( uint8_t i2cAddr, uint8_t regAddr,
                             uint8_t *buffer, uint8_t count );
    /// Pointer to I2C read register function.
    uint8_t (*i2cReadReg) ( uint8_t i2cAddr, uint8_t regAddr,
                            uint8_t *buffer, uint8_t count );
} T_IS31FL3733;

/** LED mode enumeration. */
typedef enum {
    IS31FL3733_LED_MODE_PWM  = 0x00, ///< PWM control mode.
    IS31FL3733_LED_MODE_ABM1 = 0x01, ///< Auto Breath Mode 1.
    IS31FL3733_LED_MODE_ABM2 = 0x02, ///< Auto Breath Mode 2.
    IS31FL3733_LED_MODE_ABM3 = 0x03  ///< Auto Breath Mode 3.
} T_IS31FL3733_LED_MODE;

/** ABM T1 period time, ms. */
typedef enum {
    IS31FL3733_ABM_T1_210MS   = 0x00, ///< T1 period 210ms
    IS31FL3733_ABM_T1_420MS   = 0x20, ///< T1 period 420ms
    IS31FL3733_ABM_T1_840MS   = 0x40, ///< T1 period 840ms
    IS31FL3733_ABM_T1_1680MS  = 0x60, ///< T1 period 1680ms
    IS31FL3733_ABM_T1_3360MS  = 0x80, ///< T1 period 3360ms
    IS31FL3733_ABM_T1_6720MS  = 0xA0, ///< T1 period 6720ms
    IS31FL3733_ABM_T1_13440MS = 0xC0, ///< T1 period 13440ms
    IS31FL3733_ABM_T1_26880MS = 0xE0  ///< T1 period 26880ms
} T_IS31FL3733_ABM_T1;

/** ABM T2 period time, ms. */
typedef enum {
    IS31FL3733_ABM_T2_0MS     = 0x00, ///< T1 period 0ms
    IS31FL3733_ABM_T2_210MS   = 0x02, ///< T1 period 210ms
    IS31FL3733_ABM_T2_420MS   = 0x04, ///< T1 period 420ms
    IS31FL3733_ABM_T2_840MS   = 0x06, ///< T1 period 840ms
    IS31FL3733_ABM_T2_1680MS  = 0x08, ///< T1 period 1680ms
    IS31FL3733_ABM_T2_3360MS  = 0x0A, ///< T1 period 3360ms
    IS31FL3733_ABM_T2_6720MS  = 0x0C, ///< T1 period 6720ms
    IS31FL3733_ABM_T2_13440MS = 0x0E, ///< T1 period 13440ms
    IS31FL3733_ABM_T2_26880MS = 0x10  ///< T1 period 26880ms
} T_IS31FL3733_ABM_T2;

/** ABM T3 period time, ms. */
typedef enum {
    IS31FL3733_ABM_T3_210MS   = 0x00, ///< T1 period 210ms
    IS31FL3733_ABM_T3_420MS   = 0x20, ///< T1 period 420ms
    IS31FL3733_ABM_T3_840MS   = 0x40, ///< T1 period 840ms
    IS31FL3733_ABM_T3_1680MS  = 0x60, ///< T1 period 1680ms
    IS31FL3733_ABM_T3_3360MS  = 0x80, ///< T1 period 3360ms
    IS31FL3733_ABM_T3_6720MS  = 0xA0, ///< T1 period 6720ms
    IS31FL3733_ABM_T3_13440MS = 0xC0, ///< T1 period 13440ms
    IS31FL3733_ABM_T3_26880MS = 0xE0  ///< T1 period 26880ms
} T_IS31FL3733_ABM_T3;

/** ABM T4 period time, ms. */
typedef enum {
    IS31FL3733_ABM_T4_0MS      = 0x00, ///< T1 period 0ms
    IS31FL3733_ABM_T4_210MS    = 0x02, ///< T1 period 210ms
    IS31FL3733_ABM_T4_420MS    = 0x04, ///< T1 period 420ms
    IS31FL3733_ABM_T4_840MS    = 0x06, ///< T1 period 840ms
    IS31FL3733_ABM_T4_1680MS   = 0x08, ///< T1 period 1680ms
    IS31FL3733_ABM_T4_3360MS   = 0x0A, ///< T1 period 3360ms
    IS31FL3733_ABM_T4_6720MS   = 0x0C, ///< T1 period 6720ms
    IS31FL3733_ABM_T4_13440MS  = 0x0E, ///< T1 period 13440ms
    IS31FL3733_ABM_T4_26880MS  = 0x10, ///< T1 period 26880ms
    IS31FL3733_ABM_T4_53760MS  = 0x12, ///< T1 period 53760ms
    IS31FL3733_ABM_T4_107520MS = 0x14  ///< T1 period 107520ms
} T_IS31FL3733_ABM_T4;

/** ABM loop beginning time.*/
typedef enum {
    IS31FL3733_ABM_LOOP_BEGIN_T1 = 0x00, ///< Loop begin from T1.
    IS31FL3733_ABM_LOOP_BEGIN_T2 = 0x10, ///< Loop begin from T2.
    IS31FL3733_ABM_LOOP_BEGIN_T3 = 0x20, ///< Loop begin from T3.
    IS31FL3733_ABM_LOOP_BEGIN_T4 = 0x30  ///< Loop begin from T4.
} T_IS31FL3733_ABM_LOOP_BEGIN;

/** ABM loop end time.*/
typedef enum {
    IS31FL3733_ABM_LOOP_END_T3 = 0x00, ///< Loop end at end of T3.
    IS31FL3733_ABM_LOOP_END_T1 = 0x40  ///< Loop end at end of T1.
} T_IS31FL3733_ABM_LOOP_END;

/** ABM function number (also used as register offset).*/
typedef enum {
    IS31FL3733_ABM_NUM_1 = _IS31FL3733_ABM1, ///< ABM-1
    IS31FL3733_ABM_NUM_2 = _IS31FL3733_ABM2, ///< ABM-2
    IS31FL3733_ABM_NUM_3 = _IS31FL3733_ABM3  ///< ABM-3
} T_IS31FL3733_ABM_NUM;

/** Auto Breath Mode (ABM) configuration structure.
    @verbatim
    +----+              +
    /      \            /
    /        \          /
    /          \        /
    /            \      /
    +              +----+
    | T1 | T2 | T3 | T4 | T1 |
    @endverbatim
*/
typedef struct {
    /// T1 time.
    T_IS31FL3733_ABM_T1 T1;
    /// T2 time.
    T_IS31FL3733_ABM_T2 T2;
    /// T3 time.
    T_IS31FL3733_ABM_T3 T3;
    /// T4 time.
    T_IS31FL3733_ABM_T4 T4;
    /// Loop beginning time.
    T_IS31FL3733_ABM_LOOP_BEGIN begin;
    /// Loop end time.
    T_IS31FL3733_ABM_LOOP_END end;
    /// Total loop times.
    uint16_t times;
} T_IS31FL3733_ABM;

///@}
/**
 * @name                 16x12_G Click Driver Functions
 *//*-------------------------------------------------------------------------*/
///@{
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Initializes 16x12_G click driver.
 *
 * @param[in] device      Pointer to the current device
 * @param[in] addr2       IS31FL3733 ADDR2 connection
 * @param[in] addr1       IS31FL3733 ADDR1 connection
 * @param others          I2C function pointers
 *
 * @note This function must be called first.
 */
    void IS31FL3733_init(
#if defined( __MIKROC_PRO_FOR_ARM__ )
#if defined( __STM32__ ) || defined( __KINETIS__ ) || defined( __MCHP__ )

        T_IS31FL3733 *device, uint8_t addr2, uint8_t addr1,
        T_IS31FL3733_I2C_Start fpStart,
        T_IS31FL3733_I2C_Write fpWrite, T_IS31FL3733_I2C_Read fpRead
#elif defined( __MSP__ )

        T_IS31FL3733 *device, uint8_t addr2, uint8_t addr1,
        T_IS31FL3733_I2C_Write fpWrite, T_IS31FL3733_I2C_Read fpRead
#elif defined( __TI__ )

        T_IS31FL3733 *device, uint8_t addr2, uint8_t addr1,
        T_IS31FL3733_I2C_SetSlaveAddress fpSlaveAddr,
        T_IS31FL3733_I2C_Write fpWrite, T_IS31FL3733_I2C_Read fpRead
#endif

#elif defined( __MIKROC_PRO_FOR_AVR__ )   ||    \
    defined( __MIKROC_PRO_FOR_8051__ )  ||      \
    defined( __MIKROC_PRO_FOR_DSPIC__ ) ||      \
    defined( __MIKROC_PRO_FOR_PIC32__ ) ||      \
    defined( __MIKROC_PRO_FOR_PIC__ )

        T_IS31FL3733 *device, uint8_t addr2, uint8_t addr1,
        T_IS31FL3733_I2C_Start fpStart, T_IS31FL3733_I2C_Stop fpStop,
        T_IS31FL3733_I2C_Write fpWrite, T_IS31FL3733_I2C_Read fpRead

#elif defined( __MIKROC_PRO_FOR_FT90x__ )

        T_IS31FL3733 *device, uint8_t addr2, uint8_t addr1,
        T_IS31FL3733_I2C_SetSlaveAddress fpSlaveAddr,
        T_IS31FL3733_I2C_Write fpWrite, T_IS31FL3733_I2C_Read fpRead

#else
        T_IS31FL3733 *device, uint8_t addr2, uint8_t addr1,
        T_IS31FL3733_I2C_Start fpStart, T_IS31FL3733_I2C_Stop fpStop,
        T_IS31FL3733_I2C_Write fpWrite, T_IS31FL3733_I2C_Read fpRead
#endif
        );

/**
 * @brief Read from common register.
 *
 * @param[in] device    Pointer to the current device
 * @param[in] regAddr   Register address
 *
 * @return              Value read from given register address
 */
uint8_t IS31FL3733_readCommonReg( T_IS31FL3733 *device, uint8_t regAddr );

/**
 * @brief Write to common register.
 *
 * @param[in] device    Pointer to the current device
 * @param[in] regAddr   Register address
 * @param[in] regValue  Value to be written
 */
void IS31FL3733_writeCommonReg( T_IS31FL3733 *device, uint8_t regAddr,
                                    uint8_t regValue );
/**
 * @brief Select active page.
 *
 * @param[in] device    Pointer to the current device
 * @param[in] page      Page number
 */
    void IS31FL3733_selectPage( T_IS31FL3733 *device, uint8_t page );

/**
 * @brief Read from paged register.
 *
 * @param[in] device    Pointer to the current device
 * @param[in] regAddr   Register address
 *
 * @return              Value read from given paged register
 */
uint8_t IS31FL3733_readPagedReg( T_IS31FL3733 *device, uint16_t regAddr );

/**
 * @brief Write to paged register.
 *
 * @param[in] device    Pointer to the current device
 * @param[in] regAddr   Register address
 * @param[in] regValue  Value to be written
 */
void IS31FL3733_writePagedReg( T_IS31FL3733 *device, uint16_t regAddr,
                                   uint8_t regValue );

/**
 * @brief Write array to sequentially allocated paged registers starting from
 *        specified address.
 * 
 * @param[in] device    Pointer to the current device
 * @param[in] regAddr   Register address
 * @param[in] values    Array of values to be written
 * @param[in] count     Number of values in \a values array
 */
void IS31FL3733_writePagedRegs( T_IS31FL3733 *device, uint16_t regAddr,
                                    uint8_t *values, uint8_t count );

/**
 * @brief Set global current control register.
 *
 * @param[in] device    Pointer to the current device
 * @param[in] gcc       Global current
 *
 * @note Scope for \a gcc is [0,127]
 */
void IS31FL3733_setGCC( T_IS31FL3733 *device, uint8_t gcc );

/**
 * @brief Set SW Pull-Up register.
 *
 * @param[in] device    Pointer to the current device
 * @param[in] resistor  Pull-up resistor value
 *
 * @note \a resistor takes values from \a T_IS31FL3733_RESISTOR
 *       enumeration.
 */
void IS31FL3733_setSWPUR( T_IS31FL3733 *device,
                              T_IS31FL3733_RESISTOR resistor );

/**
 * @brief Set CS Pull-Down register.
 *
 * @param[in] device    Pointer to the current device
 * @param[in] resistor  Pull-down resistor value
 *
 * @note \a resistor takes values from \a T_IS31FL3733_RESISTOR enumeration.
 */
void IS31FL3733_setCSPDR( T_IS31FL3733 *device,
                              T_IS31FL3733_RESISTOR resistor );

/**
 * @brief Set single LED state
 *
 * @details \a state take values from \a T_IS31FL3733_LED_STATE enumeration.
 *          Setting \a cs to its maximum value (i.e. \a _IS31FL3733_CS) turns on
 *          the entire row specified with \a cs. Similarly for setting \a sw to
 *          its maximum value (i.e. \a _IS31FL3733_SW). When both \a cs and
 *          \a sw have their maximum values, all LEDs are set to the given
 *          state.
 *
 * @param[in] device    Pointer to the current device
 * @param[in] cs        Row number
 * @param[in] sw        Column number
 * @param[in] state     LED state
 */

void IS31FL3733_setLEDState( T_IS31FL3733 *device, uint8_t cs, uint8_t sw,
                                 T_IS31FL3733_LED_STATE state );
/**
 * @brief Set LED PWM duty value
 *
 * @param[in] device    Pointer to the current device
 * @param[in] cs        Row number
 * @param[in] sw        Column number
 * @param[in] value     PWM duty value
 *
 * @note Similar to \a setLEDState, except it sets PWM duty value.
 */
    void IS31FL3733_setLEDPWM( T_IS31FL3733 *device, uint8_t cs, uint8_t sw,
                               uint8_t value );

/**
 * @brief Get status of LED.
 *
 * @param[in] device    Pointer to the current device
 * @param[in] cs        Row number
 * @param[in] sw        Column number
 */
    T_IS31FL3733_LED_STATUS IS31FL3733_getLEDStatus( T_IS31FL3733 *device,
                                                     uint8_t cs, uint8_t sw );

/**
 * @brief Set LED state for all LED's from buffer.
 *
 * @param[in] device    Pointer to the current device
 * @param[in] states    Buffer with LED states
 */
    void IS31FL3733_setState( T_IS31FL3733 *device, uint8_t *states );

/**
 * @brief Set LED PWM duty value for all LED's from buffer.
 *
 * @param[in] device    Pointer to the current device
 * @param[in] values    Buffer with LED PWM duty values
 */
    void IS31FL3733_setPWM( T_IS31FL3733 *device, uint8_t *values );

/**
 * @brief Clear the matrix
 *
 * @param[in] device    Pointer to the current device
 */
    void IS31FL3733_clearMatrix( T_IS31FL3733 *device);

/**
 * @brief Set LED operating mode
 *
 * @param[in] device    Pointer to the current device
 * @param[in] cs        Row number
 * @param[in] sw        Column number
 * @param[in] mode      LED mode
 *
 * @note \a mode takes values from \a T_IS31FL3733_LED_MODE enum. Similarly to
 *       \a setLEDState and \a setLEDPWM, it can be applied to entire row or
 *       column, or entire matrix.
 */
    void IS31FL3733_setLEDMode( T_IS31FL3733 *device, uint8_t cs, uint8_t sw,
                                T_IS31FL3733_LED_MODE mode );

/**
 * @brief Configure ABM Mode.
 *
 * @param[in] device    Pointer to the current device
 * @param[in] n         ABM function number
 * @param[in] config    Pointer to ABM configuration structure
 *
 * @note \a n takes values from \a T_IS31FL3733_ABM_NUM enum
 */
    void IS31FL3733_configABM( T_IS31FL3733 *device, T_IS31FL3733_ABM_NUM n,
                               T_IS31FL3733_ABM *config );

/**
 * @brief Start ABM operation.
 *
 * @param[in] device    Pointer to the current device
 */
    void IS31FL3733_startABM( T_IS31FL3733 *device );

#ifdef __cplusplus
} // extern "C"
#endif
#endif /* _IS31FL3733_H_ */
///@}
///@}
/*------------------------------------------------------------------------------

  __IS31FL3733_Driver.h

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

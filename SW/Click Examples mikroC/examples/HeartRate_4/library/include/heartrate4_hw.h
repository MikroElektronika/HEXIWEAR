
/**
  * @file                        heartrate4_hw.h
  * @brief                       Heart rate 4 driver
  *
  * @defgroup click Heart rate 4
  * @brief         Heart rate driver
  *
  * @{
  *
  * This is driver for Heart rate 4 click board.
  *
  * ### Device Description ###
  *
  * Heart rate 4 click board contains MAX30101 module, 
  * a MAX30101  is  an  integrated  pulse  oximetry  and  heart-rate
  * monitor  module.  It  includes  internal  LEDs,  photodetectors, 
  * optical elements, and low-noise electronics with  ambient  light  rejection. 
  * Digital output data can be stored in a 32-deep FIFO within the IC.
  * The FIFO allows the MAX30101 to be connected to a microcontroller
  * or processor on a shared bus, where the data is not being read continuously 
  * from the MAX30101’s registers.It also contains temperature sensor 
  * for calibrating the temperature dependence of the particle-sensing subsystem,
  * with an inherent resolution of 0.0625°C.
  *
  * ### Features ###
  *
  * - Supply voltage range: 2.7V to 5.5V
  * - MAX30101 operates on a single 1.8V power supply
  *    and a separate 5.0V power supply for the internal LEDs.
  * - 400kHz I2C-compatible interface
  * - 32-deep storage with FIFO policy for output data
  * - Particle sensing subsystem
  * - ADC sampling rate is 10.24MHz.The ADC output data rate 
  *    can be programmed from 50sps (samples per second) to 3200sps
  * - LED Driver: RED, GREEN and IR LEDs 
  * - Proximity Function
  *
  *
  * ### Library Description ###
  *      The library provides initialization and data collection from sensor in 
  *      Heart Rate working mode, with setters and getters for all registers
  *      of IC.
  *
  *
  * @example Heart_rate_4_ARM.c
  * @example Heart_rate_4_PIC.c
  * @example Heart_rate_4_PIC32.c
  * @example Heart_rate_4_dsPIC.c
  * @example Heart_rate_4_AVR.c
  * @example Heart_rate_4_FT90x.c
  *
 /*****************************************************************************/
 /*****************************************************************************/


#ifndef HEARTRATE4_HW_H
#define HEARTRATE4_HW_H

#include "heartrate4_hal.h"

 /*                 Preprocessors
*******************************************************************************/
//
// SMOKE I2C Address (7-bit)
//
#define HR4_I2C_ADDRESS 0x57

#include <stdint.h>
#include <stdbool.h>

/**
  * @name                 Functions
  *****************************************************************************/
///@{
#ifdef __cplusplus
extern "C"{ 
#endif

// HELPER FUNCTIONS 

/**
   * @brief Reads one byte from register
   *
   * @param[in]   reg  register address
   *
   * @retval      Returns register value
   */
uint8_t hr4_read_reg ( uint8_t reg );

/**
 * @brief Reads count number of bytes from register
 *
 * @param[in]	reg	 register address
 * @param[in/out] buffer 	Data buffer
 * @param[in] 	count 		Number of bytes to read
 *
 * @note
 */
void hr4_read_reg_multi ( uint8_t reg, uint8_t *buffer, uint8_t count );

/**
   * @brief Writes one byte to register
   *
   * @param[in]   reg  register address
   * @param[in]   reg_val  value to be set
   *
   * @note
   */
void hr4_write_reg( uint8_t reg, uint8_t reg_val );

// LIBRARY ROUTINES


/**
   * @brief Initializes function pointers and resets sensor
   *
   * Initialization
   *
   * @note Making the MAX30101 Sensor Ready for Work. Always called first.
   */
void hr4_init();

/**
   * @brief Configures Registers in Heart rate configuration mode (RED LED ONLY)
   *
   * Default Register Configuration 
   *
   * @note Default MAX30101 Settings: Called after hr4_init
   * Sample Average = 32
   * Mode = Heart Rate
   * Enabled PROX THRESHOLD Triggering
   * Sample rate = 1000
   */
void hr4_set_registers();

/**
   * @brief Reads the oldest 3B data from channel 
   *
   * Reading First 3B of FIFO Data in Heart rate mode
   *
   * @note Stores 3B for RED LED sample
   */
void hr4_read_fifo_oldest_sample();

/**
   * @brief Gets value of RED LED
   *
   * @retval      Returns 3B RED value 
   *
   * @note Reading sample from FIFO is expected before this function
   */
uint32_t hr4_get_red();

/**
   * @brief Returns value of Interrupt Status register, with FIFO Almost Full Flag
   *
   * @retval      Returns register value 
   */
uint8_t hr4_is_fifo_full();

/**
   * @brief Returns value of Interrupt Status register, with New FIFO Data Flag
   *
   * @retval      Returns register value 
   */
uint8_t hr4_is_new_fifo_data_ready();

/**
   * @brief Returns value of Interrupt Status register, with ALC Overflow Flag
   *
   * @retval      Returns register value 
   */
uint8_t hr4_is_alc_overflow();

/**
   * @brief Returns value of Interrupt Status register, with PROX_THRESH Flag
   *
   * @retval      Returns register value 
   */
uint8_t hr4_is_proximity_int();

/**
   * @brief Returns value of Interrupt Status register, with Power Ready Flag
   *
   * @retval      Returns register value 
   */
uint8_t hr4_is_powered_up();

/**
   * @brief Returns value of Interrupt Status register, with Temperature Ready Flag
   *
   * @retval      Returns register value 
   */
uint8_t hr4_is_internal_temp_ready();

/**
   * @brief Reads all FIFO data samples and returns average value
   *
   * @retval Returns 3 Bytes of averaged sample value
   */
uint32_t hr4_read_red (void );

void hr4_fifo_full_int_enable( bool enable );

/**
   * @brief Enable interrupt when there is a new sample in the data FIFO.
   *
   * @param[in]   enable  Enables or disables this interrupt
   *
   * @note This interrupt triggers when there is a new sample in the data FIFO.
   */
void hr4_new_fifo_data_int_enable( bool enable );

/**
   * @brief Enabling Ambient Light Cancellation Overflow
   *
   * Ambient Light Cancellation Overflow
   *
   * @param[in]   enable  Enabling or disabling ambient light
   *
   * @note Triggers when the ambient light cancellation function has reached maximum
   */
void hr4_alc_int_enable( bool enable );

/**
   * @brief Enables Proximity Threshold Triggering and Particle Sensing Mode has begun
   *
   * Proximity Threshold Triggered
   *
   * @param[in]   enable  Enables or disables this interrupt
   *
   * @note Triggers when the ambient light cancellation function has reached maximum
   */
void hr4_proximity_int_enable( bool enable );

/**
   * @brief Enabling the interrupt when internal die temperature conversion is finished
   *
   * @param[in]   enable  Enables or disables this interrupt
   * 
   * @note 
   */
void hr4_new_internal_temp_int_enable( bool enable );

/**
  * @brief FIFO Sample averaging
  *
  * @param[in]   sample_number  number of sample averaging  
  *
  * @retval      Returns -1 if value is out of range, 0 otherwise
  *
  * @note To reduce the amount of data throughput, adjacent samples are averaged
  */  
int8_t hr4_set_fifo_sample_averaging( uint8_t sample_number );

/**
   * @brief Controls the behavior of the FIFO when the it becomes completely filled with data
   *
   * Enabling or Disabling FIFO Rolls on Full
   *
   * @note FIFO Address rolls over to zero and the FIFO continues to fill with new data
   * or FIFO is not updated until FIFO_DATA is read or 
   * the WRITE/READ pointer positions are changed
   */
void hr4_fifo_rollover_enable( bool enable );

/**
   * @brief Setting the trigger for the FIFO_A_FULL interrupt
   *
   * @param[in]   samples  Setting value within range of 0x0 and 0xF
   *
   * @retval      Returns -1 if value is out of range, 0 otherwise
   *
   * @note If set to 0x0F, the interrupt triggers when there are 15 empty space left 
   */
int8_t hr4_set_fifo_almost_full_value (uint8_t full_value );

/**
   * @brief Putting I2C in Low Power Mode 
   *
   * Shut Down or Wake Up
   *
   * @param[in]   enable Enables or disables shutdown 
   *
   * @note During shutdown, the IC will continue to respond to I2C commands
   * but will not update with or take new readings ( such as temperature )
   */
void hr4_shut_down_enable( bool enable );

/**
   * @brief Software Reset
   *
   * Reset
   *
   * @note Reseting MAX30101 Sensor by writing into Mode Configuration register 
   */
void hr4_reset();

/**
   * @brief Setting desired LED Mode For Sampling
   *
   * @param[in]   modes: RED only (HR), RED and IR (SpO2) or multiLED
   *
   * @note       
   */
int8_t hr4_set_mode( uint8_t mode );

/**
   * @brief Setting ADC Full-scale Range
   *
   * @param[in]   range Particle-Sensing ADC Range 
   *
   * @note range varies from 00 - 2048 nA  to 03 - 16384 nA       
   */
int8_t hr4_set_spo2_range( uint8_t range );

/**
   * @brief Setting Number of Samples in Particle Sensing Mode ( SPO2 )
   *
   * @param[in]   sample_rate  Setting number of samples per second
   *
   * @note Can be limited by ADC resolution
   */
int8_t hr4_set_spo2_sample_rate( uint8_t rate );

/**
   * @brief Setting Pulse Width in ms for MultiLED mode
   *
   * @param[in]   pulse_width  Predefined constants are expected
   *
   * @note for MultiLED Slot Timing
   */
int8_t hr4_set_led_pulse_width( uint8_t pulse_width );

/**
   * @brief Setting Red Pulse Amplitude
   *
   * @param[in]   amplitude  Amplitude range of 0 - 255
   *
   * @note 
   */
void hr4_set_red_led_pulse_amplitude( uint8_t amplitude );

/**
   * @brief Setting IR Pulse Amplitude
   *
   * @param[in]   amplitude  Amplitude range of 0 - 255
   *
   * @note 
   */
void hr4_set_ir_led_pulse_amplitude( uint8_t amplitude );

/**
   * @brief Setting Green Pulse Amplitude
   *
   * @param[in]   amplitude  Amplitude range of 0 - 255
   *
   * @note 
   */
void hr4_set_green_led_pulse_amplitude( uint8_t amplitude );

/**
   * @brief Setting Proximity Pulse Amplitude
   *
   * @param[in]   amplitude  Amplitude range of 0 - 255
   *
   * @note 
   */
void hr4_set_proximity_led_pulse_amplitude( uint8_t amplitude );

/**
   * @brief Reads Current IC’s internal Temperature 
   *
   * Temperature reading ( C )
   *
   * @retval      Returns 2B value of temperature in celsius
   */
int16_t hr4_get_temperature();

/**
   * @brief Setting Proximity Threshold
   *
   * @param[in]   thresh_MSB  Set threshold value
   *
   * @note        Proximity interrupt is triggered when threshold is reached
   */
void hr4_set_proximity_threshold( uint8_t threshold );

 /**
   * @brief Getting Write Pointer ( Controls the Flow of Data in FIFO )
   *
   * Write Pointer
   *
   * @note The write pointer increments every time a new sample is added to the FIFO
   */
uint8_t hr4_get_write_pointer( void );

/**
   * @brief Getting Read Pointer ( Controls the Flow of Data in FIFO )
   *
   * Read Pointer
   *
   * @note The read pointer is incremented every time a sample is read from the FIFO
   */
uint8_t hr4_get_read_pointer( void );

#ifdef __cplusplus
  } // extern "C"
#endif
#endif
 ///@}
 /**
  * @}                                                              End of File
 ******************************************************************************/



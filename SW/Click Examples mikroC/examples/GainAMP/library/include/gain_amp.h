/**
 * @file    gain_amp.h
 * @brief   Library for GainAMP click board.
 *
 * @defgroup    gainamp GainAMP click
 * @brief       GainAMP module.
 *
 * This is driver for GainAMP click board.
 *
 * @{
 *
 * ### Device Description ###
 *
 * The LTC 6912 is a family of dual channel, low noise, digitally programmable 
 * gain amplifiers (PGA) that are easy to use and occupy very little PC board 
 * space. The gains for both channels are independently programmable using a 
 * 3-wire SPI interface to select voltage gains of 0, 1, 2, 5, 10, 20, 50, and 
 * 100V/V (LTC6912-1 ); and 0, 1, 2, 4, 8, 16, 32, and 64V/V (LTC6912-2). 
 * All gains are inverting.
 * 
 *
 * ### Features ###
 * - 2 Channels with Independent Gain Control
 *   LTC6912-1: (0, 1, 2, 5, 10, 20, 50, and 100V/V)
 *   LTC6912-2: (0, 1, 2, 4, 8, 16, 32, and 64V/V)
 * - Offset Voltage = 2mV Max (–40°C to 85°C)
 * - Channel-to-Channel Gain Matching of 0.1dB Max
 * - 3-Wire SPITM Interface
 * - Extended Gain-Bandwidth at High Gains
 *
 * ### Library Description
 *	The library has helper function for setting gain on each channel. 
 *
 * @example GainAMP_ARM.c
 * @example GainAMP_PIC.c
 * @example GainAMP_PIC32.c
 * @example GainAMP_dsPIC.c
 * @example GainAMP_AVR.c
 * @example GainAMP_FT90x.c
 *
 ******************************************************************************/

#ifndef GAIN_AMP_H
#define GAIN_AMP_H


#include <stdint.h>
#include <stdbool.h>


#if defined( __MIKROC_PRO_FOR_ARM__ )   || \
    defined( __MIKROC_PRO_FOR_DSPIC__ )
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>    
typedef void ( *gainamp_write_spi_t )( unsigned int data_out );
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<        
#elif defined( __MIKROC_PRO_FOR_AVR__ )     || \
      defined( __MIKROC_PRO_FOR_PIC__ )     || \
      defined( __MIKROC_PRO_FOR_8051__ )
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>    
typedef void ( *gainamp_write_spi_t )( unsigned char data_out );
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<        
#elif defined( __MIKROC_PRO_FOR_PIC32__ )
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>    
typedef void ( *gainamp_write_spi_t )( unsigned long data_out );
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<        
#elif defined( __MIKROC_PRO_FOR_FT90x__ )
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>    
typedef void ( *gainamp_write_spi_t )( unsigned char data_out );
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#endif

/**
 * @name 		Nominal gain
 * @brief       Nominal voltage gain
 ******************************************************************************/
///@{

#define GAIN_AMP_NOMINAL_0      (0x00)
#define GAIN_AMP_NOMINAL_1      (0x01)
#define GAIN_AMP_NOMINAL_2      (0x02)
#define GAIN_AMP_NOMINAL_5      (0x03)
#define GAIN_AMP_NOMINAL_10     (0x04)
#define GAIN_AMP_NOMINAL_20     (0x05)
#define GAIN_AMP_NOMINAL_50     (0x06)
#define GAIN_AMP_NOMINAL_100    (0x07)

#define GAIN_AMP_SW_SHUTDOWN    (0x80)

///@}

/**
 * @name 		Device Properties
 ******************************************************************************/
///@{


///@}
/**
 * @name 		Return Values
 ******************************************************************************/
///@{


///@}
/**
 * @name 		Types
 ******************************************************************************/
///@{



///@}
/**
 * @name 		Functions
 ******************************************************************************/
///@{
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief <h3> GainAMP click initialization </h3>
 *
 * @param[in]   write_spi - The pointer to the SPI write function.
 *
 *
 * Initializes GainAMP module. 
 *
 * @note
 * This function must be called first.
 *
 */
void gain_amp_init( gainamp_write_spi_t write_spi );

/**
 * @brief <h3> Gain setting </h3>
 *
 * @param[in]   channel_a - Gani value for channel A.
 * @param[in]   channel_b - Gani value for channel B.
 *
 * @return The function returns the byte writen to SPI.
 *
 * Sets gain for each channel.
 *
 * @note
 * The module must be initialized before calling this function.
 *
 */
uint8_t gain_amp_set( uint8_t channel_a, uint8_t channel_b );

/**
 * @brief <h3> Hardware shutdown </h3>
 *
 * @param[in]   flag - Flag.
 *
 *
 * Controls shutdown pin. 
 *
 */
void gain_amp_shutdown( bool flag );

#ifdef __cplusplus
} // extern "C"
#endif
#endif // GAIN_AMP_H

///@}
/**
 * @} 								End of File
 ******************************************************************************/

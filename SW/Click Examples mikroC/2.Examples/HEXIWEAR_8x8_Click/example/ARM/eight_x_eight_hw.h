/****************************************************************************
* Title                 :   8x8 CLICK
* Filename              :   eight_x_eight_hw.h
* Author                :   CAL
* Origin Date           :   03/29/2016
* Notes                 :   None
*****************************************************************************/
/**************************CHANGE LIST **************************************
*
*    Date    Software Version    Initials   Description
*  03/29/2016   XXXXXXXXXXX        CAL      Interface Created.
*
*****************************************************************************/
/**
 * @file 8x8_hw.h
 * @brief <h3> Hardware Layer </h3>
 *
 * @par
 * Low level functions for
 * <a href="http://www.mikroe.com">MikroElektronika's</a> 8x8 click
 * board.
 */

/**
 * @page LIB_INFO Library Info
 * @date 29 March 2016
 * @author Corey Lakey
 * @copyright GNU Public License
 * @version 1.0.0 - Initial testing and verification
 */

/**
 * @page TEST_CFG Test Configurations
 * <h3> Test configuration 1 : </h3>
 * @par
 * <ul>
 * <li><b>MCU</b> :             STM32F107VC</li>
 * <li><b>Dev. Board</b> :      EasyMx Pro v7</li>
 * <li><b>Oscillator</b> :      72 Mhz internal</li>
 * <li><b>Ext. Modules</b> :    8x8 Click</li>
 * <li><b>SW</b> :              MikroC PRO for ARM 4.7.1</li>
 * </ul>
 *
 * <h3> Test configuration 2 : </h3>
 * @par
 * <ul>
 * <li><b>MCU</b> :             PIC32MX795F512L</li>
 * <li><b>Dev. Board</b> :      EasyPic Fusion v7</li>
 * <li><b>Oscillator</b> :      80 Mhz internal</li>
 * <li><b>Ext. Modules</b> :    8x8 Click</li>
 * <li><b>SW</b> :              MikroC PRO for PIC 6.6.2</li>
 * </ul>
 *
 * <h3> Test configuration 3 : </h3>
 * @par
 * <ul>
 * <li><b>MCU</b> :             FT900Q</li>
 * <li><b>Dev. Board</b> :      EasyFT90x v7</li>
 * <li><b>Oscillator</b> :      100 Mhz internal</li>
 * <li><b>Ext. Modules</b> :    8x8 Click</li>
 * <li><b>SW</b> :              MikroC PRO for FT90x 1.2.1</li>
 * </ul>
 */

/**
 * @mainpage
 * <h3> General Description </h3>
 * @par
 *
 *
 * <h3> Features </h3>
 * @par
 *
 *
 */
#ifndef EIGHT_X_EIGHT_HW_H
#define EIGHT_X_EIGHT_HW_H
/******************************************************************************
* Includes
*******************************************************************************/
#include <stdint.h>

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Configuration Constants
*******************************************************************************/

/******************************************************************************
* Macros
*******************************************************************************/

/******************************************************************************
* Typedefs
*******************************************************************************/

/******************************************************************************
* Variables
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief <h3> HW Layer Initialization </h3>
 *
 * @par
 * Prepares library for usage and sets needed values to default.
 *
 * @note
 * This function must be called first.
 *
 * Example :
 * @code
 *
 * @endcode
 */
void led_eight_init( void );

 /**
 * @brief <h3> Display One Column </h3>
 *
 * @par
 *  Turns on LEDs in 1 column
 *
 * @param[in] row - Row of LED you want to turn on.
 * @param[in] col - Column of LED you want to turn on.
 *
 */
void led_eight_display_one_col( uint8_t row, uint8_t col );

 /**
 * @brief <h3> Display Image </h3>
 *
 * @par
 *  Displays image to 8x8 display.
 *
 * Example :
 * @code
 *   uint8_t *image[8]   = { 0xFF,
 *                           0x81,
 *                           0x81,
 *                           0x81,
 *                           0x81,
 *                           0x81,
 *                           0x81,
 *                           0xFF };
 *   eight_b_display_image( image );
 *
 * @endcode
 *
 * @param[in] image - Image to Display to the LEDs.
 *
 */
void led_eight_display_image( uint8_t* image );

 /**
 * @brief <h3> Display Const Image </h3>
 *
 * @par
 *  Displays const image to 8x8 display.
 *
 * Example :
 * @code
 *   const uint8_t *image[8]   = { 0xFF,
 *                                 0x81,
 *                                 0x81,
 *                                 0x81,
 *                                 0x81,
 *                                 0x81,
 *                                 0x81,
 *                                 0xFF };
 *   eight_b_display_image( image );
 *
 * @endcode
 *
 * @param[in] image - Const Image to Display to the LEDs.
 *
 */
void led_eight_display_const_image( const uint8_t* image );

/**
 * @brief <h3> Display String </h3>
 *
 * @par
 *  Displays a string of characters to display with no animation.
 *
 *
 * Example :
 * @code
 *    uint8_t text[] = "Hello World";
 *    eight_b_display_string( text );
 * @endcode
 */
void led_eight_display_string( const uint8_t* images );

/**
 * @brief <h3> Shift Left </h3>
 *
 * @par
 *  Shifts current image on 8x8 to the left.
 *
 */
void led_eight_display_shift_left( void );

/**
 * @brief <h3> Set Intensity </h3>
 *
 * @par
 *  Sets the intensity of the LEDs on the 8x8 display.
 *
 * @note
 *  Values are as follows:
 *  0 - 1/32 Duty Cycle
 *  1 - 3/32 Duty Cycle
 *  2 - 5/32 Duty Cycle
 *  3 - 7/32 Duty Cycle
 *  4 - 9/32 Duty Cycle
 *  5 - 11/32 Duty Cycle
 *  6 - 13/32 Duty Cycle
 *  7 - 15/32 Duty Cycle
 *  8 - 17/32 Duty Cycle
 *  9 - 19/32 Duty Cycle
 *  10 - 21/32 Duty Cycle
 *  11 - 23/32 Duty Cycle
 *  12 - 25/32 Duty Cycle
 *  13 - 27/32 Duty Cycle
 *  14 - 29/32 Duty Cycle
 *  15 - 31/32 Duty Cycle
 *
 */
void led_eight_set_intensity( uint8_t intensity );

 /**
 * @brief <h3> Set Scan Limit </h3>
 *
 * @par
 *  The scan-limit register sets how many digits are dis-
 * played, from 1 to 8.
 *
 * @note
 *   Display digit 0 only - 0
 *   Display digits 0 & 1 - 1
 *   Display digits 0 1 2 - 2
 *   Display digits 0 1 2 3 - 3
 *   Display digits 0 1 2 3 4 - 4
 *   Display digits 0 1 2 3 4 5 - 5
 *   Display digits 0 1 2 3 4 5 6 - 6
 *   Display digits 0 1 2 3 4 5 6 7 - 7
 *
 */
void led_eight_set_scan_limit( uint8_t scan_limit );

/**
 * @brief <h3> Shut Down </h3>
 *
 * @par
 *  Shuts Down the 8x8 LED Display.
 *
 * @note
 *  To turn 8x8 back on, call eight_b_init();
 *
 */
void led_eight_shut_down( void );

void led_eight_display_test( void );

 /**
 * @brief <h3> Scroll Text </h3>
 *
 * @par
 *  Displays text to 8x8 LEDs with scrolling animation..
 *
 * Example :
 * @code
 *    uint8_t text[] = "Hello World";
 *    eight_b_scroll_text( text );
 *
 * @endcode
 *
 * @param[in] image - Text to be scrolled through on 8x8 LEDs.
 *
 */
void led_eight_scroll_text( uint8_t* str, uint8_t delay );

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* EIGHT_B_HW_H */
/*** End of File **************************************************************/

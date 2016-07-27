/****************************************************************************
* Title                 :   IR GESTURE CLICK
* Filename              :   ir_gesture_hw.h
* Author                :   Nikola Golubovic
* Origin Date           :   15/12/2015
* Notes                 :   None
*****************************************************************************/
/**************************CHANGE LIST **************************************
*
*    Date    Software Version    Initials    Description
*   15/12/15         1.0            NG
*   13/01/16         2.0            RBL      Optimization of functions
*
*****************************************************************************/
/**
 * @file ir_gesture_hw.h
 * @brief IR GESTURE communication driver
 *
 * This driver supports I2C bus communication as well as full featured
 * access to the registers.
 *
 * @mainpage
 * @section General Description
 * @par
 * This library interfaces the Avago APDS-9960 to Arduino over I2C. The library
 * relies on the Arduino Wire (I2C) library. to use the library, instantiate an
 * APDS9960 object, call init(), and call the appropriate functions.
 *
 * @date 15 Dec 2015
 * @author Nikola Golubovic
 * @copyright GPL
 *
 * @version .1 - Initial testing and verification
 *
 * @note Test configuration:
 *   MCU:             STM32F107VC
 *   Dev.Board:       EasyMx Pro v7
 *   Oscillator:      72 Mhz internal
 *   Ext. Modules:    TouchPad_Click
 *   SW:              ARM 4.7
 *
 *   @ref specifications
 *
 *   @ref example
 */
#ifndef IRGESTURE_HW_H
#define IRGESTURE_HW_H

/******************************************************************************
* Includes
*******************************************************************************/
#include <stdint.h>
#include <stdbool.h>

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
/* Debug */
#define DEBUG                   0

/******************************************************************************
* Configuration Constants
*******************************************************************************/
/* APDS-9960 I2C address */
#define APDS9960_I2C_ADDR       0x39

/* Gesture parameters */
#define GESTURE_THRESHOLD_OUT   10
#define GESTURE_SENSITIVITY_1   50
#define GESTURE_SENSITIVITY_2   20

/* Acceptable device IDs */
#define APDS9960_ID_1           0xAB
#define APDS9960_ID_2           0x9C

/* Misc parameters */
#define FIFO_PAUSE_TIME         110      // Wait period (ms) between FIFO reads

/* On/Off definitions */
#define OFF                     0
#define ON                      1

/* LED Drive values */
#define LED_DRIVE_100MA         0
#define LED_DRIVE_50MA          1
#define LED_DRIVE_25MA          2
#define LED_DRIVE_12_5MA        3

/* Proximity Gain (PGAIN) values */
#define PGAIN_1X                0
#define PGAIN_2X                1
#define PGAIN_4X                2
#define PGAIN_8X                3

/* ALS Gain (AGAIN) values */
#define AGAIN_1X                0
#define AGAIN_4X                1
#define AGAIN_16X               2
#define AGAIN_64X               3

/* Gesture Gain (GGAIN) values */
#define GGAIN_1X                0
#define GGAIN_2X                1
#define GGAIN_4X                2
#define GGAIN_8X                3

/* LED Boost values */
#define LED_BOOST_100           0
#define LED_BOOST_150           1
#define LED_BOOST_200           2
#define LED_BOOST_300           3

/* Gesture wait time values */
#define GWTIME_0MS              0
#define GWTIME_2_8MS            1
#define GWTIME_5_6MS            2
#define GWTIME_8_4MS            3
#define GWTIME_14_0MS           4
#define GWTIME_22_4MS           5
#define GWTIME_30_8MS           6
#define GWTIME_39_2MS           7

/* Default values */
#define DEFAULT_ATIME           219     // 103ms
#define DEFAULT_WTIME           246     // 27ms
#define DEFAULT_PROX_PPULSE     0x87    // 16us, 8 pulses
#define DEFAULT_GESTURE_PPULSE  0x89    // 16us, 10 pulses
#define DEFAULT_POFFSET_UR      0       // 0 offset
#define DEFAULT_POFFSET_DL      0       // 0 offset
#define DEFAULT_CONFIG1         0x60    // No 12x wait (WTIME) factor
#define DEFAULT_LDRIVE          LED_DRIVE_100MA
#define DEFAULT_PGAIN           PGAIN_4X
#define DEFAULT_AGAIN           AGAIN_4X
#define DEFAULT_PILT            0       // Low proximity threshold
#define DEFAULT_PIHT            50      // High proximity threshold
#define DEFAULT_AILT            0xFFFF  // Force interrupt for calibration
#define DEFAULT_AIHT            0
#define DEFAULT_PERS            0x11    // 2 consecutive prox or ALS for int.
#define DEFAULT_CONFIG2         0x01    // No saturation interrupts or LED boost
#define DEFAULT_CONFIG3         0       // Enable all photodiodes, no SAI
#define DEFAULT_GPENTH          40      // Threshold for entering gesture mode
#define DEFAULT_GEXTH           30      // Threshold for exiting gesture mode
#define DEFAULT_GCONF1          0x40    // 4 gesture events for int., 1 for exit
#define DEFAULT_GGAIN           GGAIN_4X
#define DEFAULT_GLDRIVE         LED_DRIVE_100MA
#define DEFAULT_GWTIME          GWTIME_2_8MS
#define DEFAULT_GOFFSET         0       // No offset scaling for gesture mode
#define DEFAULT_GPULSE          0xC9    // 32us, 10 pulses
#define DEFAULT_GCONF3          0       // All photodiodes active during gesture
#define DEFAULT_GIEN            0       // Disable gesture interrupts

#define PROXIMITY_GAIN          0x0C
#define AP_CONFIG               0x71
#define P_DATA                  0x73

/*****************************************************************************
* Macros
*****************************************************************************/

/*****************************************************************************
* Typedefs
*****************************************************************************/

/* Direction definitions */
typedef enum
{
    DIR_NONE,
    DIR_LEFT,
    DIR_RIGHT,
    DIR_UP,
    DIR_DOWN,
    DIR_NEAR,
    DIR_FAR,
    DIR_ALL
} gesture_dir_t;

typedef enum
{
    INT_GESTURE = 2,
    INT_AMBIENT_LIGHT = 4,
    INT_PROXIMITY = 5
} gesture_irq_t;

/*******************************************************************************
* Variables
*******************************************************************************/

/*******************************************************************************
* Function Prototypes
*******************************************************************************/
/**
 * @brief Initialize IR GESTURE sensor.
 *
 * @param slave_address
 *
 * @return status
 * @retval -1 error in initialization
 * @retval 0 initialized successfully
 *
 * @note Need to call before called any additional functions.
 */
int ir_gesture_init( uint8_t address );

/* Turn the APDS-9960 on and off */
/**
 * @brief Turn the APDS-9960 on
 */
void ir_gesture_enable_power( void );

/**
 * Turn the APDS-9960 off
 */
void ir_gesture_disable_power( void );

/* Enable or disable specific sensors */
/**
 * @brief Starts the light (R/G/B/Ambient) sensor on the APDS-9960
 *
 * @param[in] interrupt true to enable hardware interrupt on high or low light
 */
void ir_gesture_enable_light_sensor( bool interrupt );

/**
 * @brief Disables the light sensor on the APDS-9960
 */
void ir_gesture_disable_light_sensor( void );

/**
 * @brief Starts the proximity sensor on the APDS-9960
 *
 * @param[in] interrupts true to enable hardware external interrupt on proximity
 */
void ir_gesture_enable_proximity_sensor( bool interrupt );

/**
 * @brief Ends the proximity sensor on the APDS-9960
 */
void ir_gesture_disable_proximity_sensor( void );

/**
 * @brief Starts the gesture recognition engine on the APDS-9960
 *
 * @param[in] interrupts true to enable hardware external interrupt on gesture
 */
void ir_gesture_enable_gesture_sensor( bool interrupt );

/**
 * @brief Ends the gesture recognition engine on the APDS-9960
 */
void ir_gesture_disable_gesture_sensor( void );

/* LED drive strength control */
/**
 * @brief Returns LED drive strength for proximity and ALS
 *
 * Value    LED Current
 *   0        100 mA
 *   1         50 mA
 *   2         25 mA
 *   3         12.5 mA
 *
 * @return the value of the LED drive strength. 0xFF on failure.
 */
uint8_t ir_gesture_get_led_drive( void );

/**
 * @brief Sets the LED drive strength for proximity and ALS
 *
 * Value    LED Current
 *   0        100 mA
 *   1         50 mA
 *   2         25 mA
 *   3         12.5 mA
 *
 * @param[in] drive the value (0-3) for the LED drive strength
 */
void ir_gesture_set_led_drive( uint8_t drive );

/**
 * @brief Gets the drive current of the LED during gesture mode
 *
 * Value    LED Current
 *   0        100 mA
 *   1         50 mA
 *   2         25 mA
 *   3         12.5 mA
 *
 * @return the LED drive current value. 0xFF on error.
 */
uint8_t ir_gesture_get_gesture_led_drive();

/**
 * @brief Sets the LED drive current during gesture mode
 *
 * Value    LED Current
 *   0        100 mA
 *   1         50 mA
 *   2         25 mA
 *   3         12.5 mA
 *
 * @param[in] drive the value for the LED drive current
 */
void ir_gesture_set_gesture_led_drive( uint8_t drive );

/* Gain control */
/**
 * @brief Returns receiver gain for the ambient light sensor (ALS)
 *
 * Value    Gain
 *   0        1x
 *   1        4x
 *   2       16x
 *   3       64x
 *
 * @return the value of the ALS gain. 0xFF on failure.
 */
uint8_t ir_gesture_get_ambient_light_gain();

/**
 * @brief Sets the receiver gain for the ambient light sensor (ALS)
 *
 * Value    Gain
 *   0        1x
 *   1        4x
 *   2       16x
 *   3       64x
 *
 * @param[in] drive the value (0-3) for the gain
 */
void ir_gesture_set_ambient_light_gain( uint8_t gain );

/**
 * @brief Returns receiver gain for proximity detection
 *
 * Value    Gain
 *   0       1x
 *   1       2x
 *   2       4x
 *   3       8x
 *
 * @return the value of the proximity gain. 0xFF on failure.
 */
uint8_t ir_gesture_get_proximity_gain( void );

/**
 * @brief Sets the receiver gain for proximity detection
 *
 * Value    Gain
 *   0       1x
 *   1       2x
 *   2       4x
 *   3       8x
 *
 * @param[in] drive the value (0-3) for the gain
 */
void ir_gesture_set_proximity_gain( uint8_t gain );

/**
 * @brief Gets the gain of the photodiode during gesture mode
 *
 * Value    Gain
 *   0       1x
 *   1       2x
 *   2       4x
 *   3       8x
 *
 * @return the current photodiode gain. 0xFF on error.
 */
uint8_t ir_gesture_get_gesture_gain( void );

/**
 * @brief Sets the gain of the photodiode during gesture mode
 *
 * Value    Gain
 *   0       1x
 *   1       2x
 *   2       4x
 *   3       8x
 *
 * @param[in] gain the value for the photodiode gain
 */
void ir_gesture_set_gesture_gain( uint8_t gain );

/* Get and set light interrupt thresholds */
/**
 * @brief Gets the low threshold for ambient light interrupts
 *
 * @return Low level interrupt threshold
 */
uint16_t ir_gesture_get_light_int_low_threshold( void );

/**
 * @brief Sets the low threshold for ambient light interrupts
 *
 * @param[in] threshold low threshold value for interrupt to trigger
 */
void ir_gesture_set_light_int_low_threshold( uint16_t threshold );

/**
 * @brief Gets the high threshold for ambient light interrupts
 *
 * @return Threshold current High threshold stored on the APDS-9960
 */
uint16_t ir_gesture_get_light_int_high_threshold( void );

/**
 * @brief Sets the high threshold for ambient light interrupts
 *
 * @param[in] threshold high threshold value for interrupt to trigger
 */
void ir_gesture_set_light_int_high_threshold( uint16_t threshold );

/* Get and set proximity interrupt thresholds */
/**
 * @brief Gets the low threshold for proximity interrupts
 *
 * @return Low value of threshold for proximity trigger
 */
uint8_t ir_gesture_get_proximity_int_low_threshold( void );

/**
 * @brief Sets the low threshold for proximity interrupts
 *
 * @param[in] threshold low threshold value for interrupt to trigger
 */
void ir_gesture_set_proximity_int_low_threshold( uint8_t threshold );

/**
 * @brief Gets the high threshold for proximity interrupts
 *
 * @return threshold current high threshold stored on the APDS-9960
 */
uint8_t ir_gesture_get_proximity_int_high_threshold( void );

/**
 * @brief Sets the high threshold for proximity interrupts
 *
 * @param[in] threshold high threshold value for interrupt to trigger
 */
void ir_gesture_set_prox_int_high_threshold( uint8_t threshold );

/* Get and set interrupt enables */
/**
 * @brief Gets if ambient light interrupts are enabled or not
 *
 * @return true if interrupts are enabled, 0 if not.
 */
bool ir_gesture_is_ambient_light_int_enable();

/**
 * @brief Turns ambient light interrupts on or off
 *
 * @param[in] enable true to enable interrupts, false to turn them off
 */
void ir_gesture_set_ambient_light_int_enable( bool enable );

/**
 * @brief Gets if proximity interrupts are enabled or not
 *
 * @return true if interrupts are enabled, false if not.
 */
bool ir_gesture_is_proximity_int_enable();

/**
 * @brief Turns proximity interrupts on or off
 *
 * @param[in] enable true to enable interrupts, false to turn them off
 */
void ir_gesture_set_proximity_int_enable( bool enable );

/**
 * @brief Gets if gesture interrupts are enabled or not
 *
 * @return true if interrupts are enabled, false if not.
 */
bool ir_gesture_is_gesture_int_enable( void );

/**
 * @brief Turns gesture-related interrupts on or off
 *
 * @param[in] enable true to enable interrupts, false to turn them off
 */
void ir_gesture_set_gesture_int_enable( bool enable );

/* Clear interrupts */
/**
 *
 */
bool ir_gesture_is_interrupted( gesture_irq_t interrupt );

/**
 * @brief Clears the ambient light interrupt
 */
void ir_gesture_clear_ambient_light_int( void );

/**
 * @brief Clears the proximity interrupt
 */
void ir_gesture_clear_proximity_int( void );

/**
 * @brief clear_gesture_int
 */
void ir_gesture_clear_gesture_int( void );

/* Ambient light methods */
/**
 * @brief Reads the ambient (clear) light level as a 16-bit value
 *
 * @return val value of the light sensor.
 */
uint16_t ir_gesture_read_ambient_light( void );

/**
 * @brief Reads the red light level as a 16-bit value
 *
 * @return val value of the light sensor.
 */
uint16_t ir_gesture_read_red_light(void );

/**
 * @brief Reads the green light level as a 16-bit value
 *
 * @return val value of the light sensor.
 */
uint16_t ir_gesture_read_green_light(void );

/**
 * @brief Reads the red light level as a 16-bit value
 *
 * @return val value of the light sensor.
 */
uint16_t ir_gesture_read_blue_light(void );

/* LED Boost Control */
/**
 * @brief Get the current LED boost value
 *
 * Value  Boost Current
 *   0        100%
 *   1        150%
 *   2        200%
 *   3        300%
 *
 * @return The LED boost value. 0xFF on failure.
 */
uint8_t ir_gesture_get_led_boost( void );

/**
 * @brief Sets the LED current boost value
 *
 * Value  Boost Current
 *   0        100%
 *   1        150%
 *   2        200%
 *   3        300%
 *
 * @param[in] drive the value (0-3) for current boost (100-300%)
 * @return 1 if operation successful. 0 otherwise.
 */
void ir_gesture_set_led_boost( uint8_t boost );

/* Proximity methods */
/**
 * @brief Reads the proximity level as an 8-bit value
 *
 * @return val value of the proximity sensor.
 */
uint8_t ir_gesture_read_proximity( void );

/* Proximity Interrupt Threshold */
/**
 * @brief Returns the lower threshold for proximity detection
 *
 * @return lower threshold
 */
uint8_t ir_gesture_get_prox_int_low_thresh();

/**
 * @brief Sets the lower threshold for proximity detection
 *
 * @param[in] threshold the lower proximity threshold
 */
void ir_gesture_set_prox_int_low_thresh( uint8_t threshold );

/**
 * @brief Returns the high threshold for proximity detection
 *
 * @return high threshold
 */
uint8_t ir_gesture_get_prox_int_high_thresh();

/**
 * @brief Sets the high threshold for proximity detection
 *
 * @param[in] threshold the high proximity threshold
 */
void ir_gesture_set_prox_int_high_thresh( uint8_t threshold );

/**
 * @brief Gets proximity gain compensation enable
 *
 * @return true if compensation is enabled. false if not.
 */
bool ir_gesture_is_prox_gain_comp_enable( void );

/* Proximity photodiode select */
/**
 * @brief Sets the proximity gain compensation enable
 *
 * @param[in] enable true to enable compensation. false to disable compensation.
 */
void ir_gesture_set_prox_gain_comp_enable( bool enable );

/**
 * @brief Gets the current mask for enabled/disabled proximity photodiodes
 *
 *  1 = disabled, 0 = enabled
 *  Bit    Photodiode
 *  3       UP
 *  2       DOWN
 *  1       LEFT
 *  0       RIGHT
 *
 * @return Current proximity mask for photodiodes. 0xFF on error.
 */
uint8_t ir_gesture_get_prox_photo_mask( void );

/**
 * @brief Sets the mask for enabling/disabling proximity photodiodes
 *
 * 1 = disabled, 0 = enabled
 * Bit    Photodiode
 *  3       UP
 *  2       DOWN
 *  1       LEFT
 *  0       RIGHT
 *
 * @param[in] mask 4-bit mask value
 */
void ir_gesture_set_prox_photo_mask( uint8_t mask );

/* Gesture methods */
/**
 * @brief Determines if there is a gesture available for reading
 *
 * @return true if gesture available. false otherwise.
 */
bool ir_gesture_available( void );

/**
 * @brief Processes a gesture event and returns best guessed gesture
 *
 * @return Number corresponding to gesture. -1 on error.
 */
gesture_dir_t ir_gesture_read_gesture( void );

/* Gesture mode */
/**
 * @brief Tells if the gesture state machine is currently running
 *
 * @return 1 if gesture state machine is running, 0 if not. 0xFF on error.
 */
uint8_t ir_gesture_get_gesture_mode( void );

/**
 * @brief Tells the state machine to either enter or exit gesture state machine
 *
 * @param[in] mode true to enter gesture state machine, false to exit.
 */
void ir_gesture_set_gesture_mode( bool mode );

/* Gesture threshold control */
/**
 * @brief Gets the entry proximity threshold for gesture sensing
 *
 * @return Current entry proximity threshold.
 */
uint8_t ir_gesture_enter_thresh( void );

/**
 * @brief Sets the entry proximity threshold for gesture sensing
 *
 * @param[in] threshold proximity value needed to start gesture mode
 */
void ir_gesture_set_enter_thresh( uint8_t threshold );

/**
 * @brief Gets the exit proximity threshold for gesture sensing
 *
 * @return Current exit proximity threshold.
 */
uint8_t ir_gesture_get_exit_thresh( void );

/**
 * @brief Sets the exit proximity threshold for gesture sensing
 *
 * @param[in] threshold proximity value needed to end gesture mode
 */
void ir_gesture_set_exit_thresh( uint8_t threshold );

/* Gesture LED, gain, and time control */
/**
 * @brief Gets the time in low power mode between gesture detections
 *
 * Value    Wait time
 *   0          0 ms
 *   1          2.8 ms
 *   2          5.6 ms
 *   3          8.4 ms
 *   4         14.0 ms
 *   5         22.4 ms
 *   6         30.8 ms
 *   7         39.2 ms
 *
 * @return the current wait time between gestures. 0xFF on error.
 */
uint8_t ir_gesture_get_wait_time( void );

/**
 * @brief Sets the time in low power mode between gesture detections
 *
 * Value    Wait time
 *   0          0 ms
 *   1          2.8 ms
 *   2          5.6 ms
 *   3          8.4 ms
 *   4         14.0 ms
 *   5         22.4 ms
 *   6         30.8 ms
 *   7         39.2 ms
 *
 * @param[in] the value for the wait time
 * @return 1 if operation successful. 0 otherwise.
 */
void ir_gesture_set_wait_time( uint8_t time );

#endif

/*** End of File **************************************************************/

/**
 * @page specifications Specifications
 * @par
 * <a href="http://ww1.microchip.com/downloads/en/DeviceDoc/40001750A.pdf">Datasheet</a>
 *
 */

/**
 * @page example Example
 *
 * @par Example created using the EasyMX Pro v7
 *
 * @code
 *
 * @endcode
 *  */
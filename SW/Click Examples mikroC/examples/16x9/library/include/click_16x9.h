/**
 * @file    click_16x9.h
 * @brief   Library for 16x9 click
 *
 * @defgroup 16x9click 16x9 click library
 * @brief	 Library for 16x9 click. 
 *
 * Driver for 16x9 click library.
 *
 * @{
 *
 * ### Device Description ###
 *
 * The IS31FL3731 is a compact LED driver for 144 single LEDs. The device can be
 * programmed via an I2C compatible interface. The IS31FL3731 offers two blocks 
 * each driving 72 LEDs with 1/9 cycle rate. The required lines to drive all 144
 * LEDs are reduced to 18 by using the cross-plexing feature optimizing space on
 * the PCB. Additionally each of the 144 LEDs can be dimmed individually with 
 * 8-bit allowing 256 steps of linear dimming.  
 * 
 *
 * ### Features ###
 *
 * - Supply voltage range: 2.7V to 5.5V
 * - 400kHz I2C-compatible interface
 * - 144 LEDs in dot matrix
 * - Individual blink control
 * - 8 frames memory for animations
 * - Picture mode and animation mode
 * - Auto intensity breathing during the switching of different frames
 * - LED frames displayed can be modulated with audio signal intensity
 * - LED light intensity can be modulated with audio signal intensity 
 *
 * ### Library Description
 *
 * Library can be used to access function registers of IC on click board, and to 
 * do basic graphic manipulation of each frame.
 *
 * @example click_16x9_ARM.c
 * @example click_16x9_PIC.c
 * @example click_16x9_PIC32.c
 * @example click_16x9_AVR.c
 * @example click_16x9_FT90x.c
 *
 ******************************************************************************/

/***************************************************************************//**
* Includes
*******************************************************************************/
#ifndef CLICK_16_9_h
#define CLICK_16_9_h

#include <stdint.h>
#include <stdbool.h>

/**
 * @name 		Function Registers
 * @brief       Function register addresses
 ******************************************************************************/
///@{

#define REG_CONFIG              0x00
#define REG_PICTURE_DISPLAY     0x01
#define REG_AUTO_PLAY_CTRL1     0x02
#define REG_AUTO_PLAY_CTRL2     0x03
#define REG_DISPLAY_OPTION      0x05
#define REG_AUDIO_SYNC          0x06
#define REG_FRAME_STATE         0x07
#define REG_BREATH_CTRL1        0x08
#define REG_BREATH_CTRL2        0x09
#define REG_SHUTDOWN            0x0A
#define REG_AGC_CTRL            0x0B
#define REG_AUDIO_ADC_RATE      0x0C

///@}

/**
 * @name 		Types
 ******************************************************************************/
///@{

/**
 * @enum control_t
 * @brief LED control selection.
 * Used to select control function.
 */
typedef enum {
    CTRL_LED,
    CTRL_BLINK
} control_t;

/**
 * @enum frame_t
 * @brief Frame selection.
 * Used to select available frame.
 */
typedef enum 
{
    FRAME_1 = 0x01,
    FRAME_2,
    FRAME_3,
    FRAME_4,
    FRAME_5,
    FRAME_6,
    FRAME_7,
    FRAME_8,
} frame_t;

///@}

/**
 * @name 		Functions
 ******************************************************************************/
///@{
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Initialization function.
 *
 * @param[in] i2c_addr Device I2C address.
 *
 * Function intializes library.
 *
 * @note This function must be called first before other library functions, and  
 * right after I2C initialization function.
 *
 */
void click_16x9_init( uint8_t i2c_addr );

/**
 * @brief Hardware shutdown.
 *
 * @param[in] flag Shutdown flag.
 *
 * Shutdown the chip when flag is true. 
 *
 */
void click_16x9_shutdown_hw(bool flag);

/**
 * @brief Software shutdown.
 *
 * @param[in] flag Shutdown flag.
 *
 * Shutdown mode when flag is true, and normal operation mode otherwise. 
 *
 */
void click_16x9_shutdown_sw(bool flag);

/**
 * @brief Writes to function register.
 *
 * @param[in] reg Function register address.
 * @param[in] data_ Byte to write.
 *
 * The function can be used to write function registers.
 *
 * @note The function should not be called between click_16x9_begin_frame and
 * click_16x9_end_frame functions.
 */
void click_16x9_func_reg(uint8_t reg, uint8_t data_);

/**
 * @brief Begin writing to selected frame.
 *
 * @param[in] frame Selects frame.
 *
 * The function writes to command register in witch frame to store data. Use 
 * this function to start writing to frame. 
 *
 * @note Call click_16x9_end_frame function to stop writing frame.
 */
void click_16x9_begin_frame(frame_t frame);

/**
 * @brief Stop writing to frame.
 *
 * @note Call this function to stop writing frame, after click_16x9_begin_frame
 * function.
 */
void click_16x9_end_frame();

/**
 * @brief Writes to led control register for all diodes.
 *
 * @param[in] ctrl Selects LED or BLINK control registers.
 * @param[in] state State to write (0 or 1) for all diodes.
 *
 * The function can be used to control all diodes at once (store on or off state
 * or control the blink function for each LED).
 *
 * @note The function must be called between click_16x9_begin_frame and 
 * click_16x9_end_frame functions.
 */
void click_16x9_control_all(control_t ctrl, bool state);

/**
 * @brief Writes to led control register for selected column.
 *
 * @param[in] ctrl Selects LED or BLINK control registers.
 * @param[in] column Column.
 * @param[in] states 16 bits to control individual diodes in column.
 *
 * The function can be used to control all diodes in single column (store on or 
 * off state or control the blink function for each LED).
 *
 * @note The function must be called between click_16x9_begin_frame and 
 * click_16x9_end_frame functions.
 */
void click_16x9_control(control_t ctrl, uint8_t column, uint16_t states);

/**
 * @brief Writes PWM value to (x, y) point.
 *
 * @param[in] x Column.
 * @param[in] y Row.
 * @param[in] pwm PWM value.
 *
 * The function writes PWM value for single diode in matrix.
 *
 * @note The function must be called between click_16x9_begin_frame and 
 * click_16x9_end_frame functions.
 */
void click_16x9_point(uint8_t x, uint8_t y, uint8_t pwm);

/**
 * @brief Fill screen.
 *
 * @param[in] pwm PWM value.
 *
 * The function writes PWM value for all diode in matrix.
 *
 * @note The function must be called between click_16x9_begin_frame and 
 * click_16x9_end_frame functions.
 */
void click_16x9_fill_screen(uint8_t pwm);

/**
 * @brief Draw rectangle.
 *
 * @param[in] x X coordinate of bottom-left corner.
 * @param[in] y Y coordinate of bottom-left corner.
 * @param[in] width Width.
 * @param[in] height Height.
 * @param[in] pwm PWM value.
 *
 * The function writes PWM values for rectangular area in matrix.
 *
 * @note The function must be called between click_16x9_begin_frame and 
 * click_16x9_end_frame functions.
 */
void click_16x9_rectangle(
    uint8_t x, 
    uint8_t y, 
    uint8_t width, 
    uint8_t height,
    uint8_t pwm
);

/**
 * @brief Draw circle.
 *
 * @param[in] x X coordinate of center.
 * @param[in] y Y coordinate of center.
 * @param[in] r Radius
 * @param[in] pwm PWM value.
 *
 * The function writes PWM values for circular area in matrix.
 *
 * @note The function must be called between click_16x9_begin_frame and 
 * click_16x9_end_frame functions.
 */
void click_16x9_circle(uint8_t x, uint8_t y, uint8_t r, uint8_t pwm);

#ifdef __cplusplus
} // extern "C"
#endif
#endif
///@}
/**
 * @} 								End of File
 ******************************************************************************/
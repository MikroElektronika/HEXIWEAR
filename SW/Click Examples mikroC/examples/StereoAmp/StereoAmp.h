/**
 * @file StereoAmp.h
 * @brief <h2> StereoAmp click Example </h2>
 *
 * @par
 * Example for <a href="http://www.mikroe.com">MikroElektronika's</a>
 * StereoAmp click board.
 *
 *
 *
 ******************************************************************************/

/**
 * @page        Example
 * @date        3 Nov 2016
 * @author      Branislav Marton
 * @copyright   GNU Public License
 * @version     1.0.0 - Initial testing and verification
 */

#ifndef STEREOAMP_H
#define STEREOAMP_H

/******************************************************************************
* Includes
*******************************************************************************/
#include <stdint.h>
#include <stdbool.h>


/******************************************************************************
* Preprocessors Constants
*******************************************************************************/ 
#define LEFT_CONTROL 6
#define RIGHT_CONTROL 1

#define MODE_CONTROL_REG        0b00000000
#define DIAGNOSTIC_CONTROL_REG  0b00100000
#define FAULT_DETECTION_REG     0b01000000
#define VOLUME_CONTROL1_REG     0b01100000
#define VOLUME_CONTROL2_REG     0b10000000

#define ILIMIT     0b00000010
#define DG_RESET   0b00000100
#define DG_CONT    0b00001000
#define DG_EN      0b00010000

#define POWER_OFF  0b00000000
#define POWER_ON   0b00010000
#define INPUT1     0b00000100
#define INPUT2     0b00001000

#define OUTPUT_SHT   0b00000001
#define OUTPUT_OPEN  0b00000010
#define RAIL_SHT     0b00000100
#define OVF          0b00001000
#define TSD          0b00010000

#define DATA_MASK      0b00011111
#define REG_ADDR_MASK  0b11100000

#ifdef AUTO_WR_BIT
    #define LEFT_SPEAKER   0XFC
    #define RIGHT_SPEAKER  0XFD
#else
    #define LEFT_SPEAKER   0XF8
    #define RIGHT_SPEAKER  0XFA
#endif

#ifdef __MIKROC_PRO_FOR_FT90x__
    #define POLLING_PERIOD 50
#else
    #define POLLING_PERIOD 5
#endif

#define I2C_CLK 200000

/******************************************************************************
* Variable Definitions
*******************************************************************************/
char* gain_text[] = {
     "  -80dB",
     "  -54dB",
     "-40.5dB",
     "-34.5dB",
     "  -30dB",
     "  -27dB",
     "  -24dB",
     "  -21dB",
     "  -18dB",
     "  -15dB",
     "-13.5dB",
     "  -12dB",
     "-10.5dB",
     "   -9dB",
     " -7.5dB",
     "   -6dB",
     " -4.5dB",
     "   -3dB",
     " -1.5dB",
     "    0dB",
     "  1.5dB",
     "    3dB",
     "  4.5dB",
     "    6dB",
     "  7.5dB",
     "    9dB",
     " 10.5dB",
     "   12dB",
     " 13.5dB",
     "   15dB",
     " 16.5dB",
     "   18dB"
};

#endif // STEREOAMP_H
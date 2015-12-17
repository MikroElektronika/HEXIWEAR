/**
 * MAXIM-related data types
 * Project HEXIWEAR, 2015
 */

#ifndef HG_MAXIM_TYPES
#define HG_MAXIM_TYPES

#include <stdint.h>
#include "generic_i2c_types.h"
#include "MAXIM_info.h"

typedef struct
{
  /**
   * I2C relevant information
   */
  genericI2cHandle_t protocol;

} handleMAXIM_t;

typedef enum
{
  modeHR        = 0x2,
  modeSPO2      = 0x3,
  modeMultiLED  = 0x7

} modeMAXIM_t;

typedef enum
{
  ledPower_69  = 0x0, // ADC -> 15 bit
  ledPower_118 = 0x1, // ADC -> 16 bit
  ledPower_215 = 0x2, // ADC -> 17 bit
  ledPower_411 = 0x3  // ADC -> 18 bit

} pwMAXIM_t;

typedef enum
{
  sampleRate_50   = 0x0,
  sampleRate_100  = 0x1,
  sampleRate_200  = 0x2,
  sampleRate_400  = 0x3,
  sampleRate_800  = 0x4,
  sampleRate_1000 = 0x5,
  sampleRate_1600 = 0x6,
  sampleRate_3200 = 0x7

} sampleRateMAXIM_t;

typedef enum
{
  LEDSlotNone  =  0x0,
  LEDSlotRed   =  0x1,
  LEDSlotIR    =  0x2,
  LEDSlotGreen =  0x3

} LEDSlotMAXIM_t;

typedef enum
{
  STATUS_MAXIM_SUCCESS,        // success
  STATUS_MAXIM_ERROR,          // fail
  STATUS_MAXIM_PROTOCOL_ERROR, // protocol failure
  STATUS_MAXIM_INIT_ERROR,     // initialization error
  STATUS_MAXIM_PARAM_ERROR,    // invalid parameter is given
  STATUS_MAXIM_TIMEOUT         // timeout occured

} statusMAXIM_t;

/**
 * use evaluation board software and datasheet to determine the desired current value
 */
typedef uint8_t LEDCurrentMAXIM_t;
typedef uint32_t dataMAXIM_t;


typedef enum
{
  adcRange2048  = 0x0,
  adcRange4096  = 0x1,
  adcRange8192  = 0x2,
  adcRange16384 = 0x3

} adcRangeMAXIM_t;

typedef enum
{
  ovsNone = 0x0, // no averaging
  ovs2    = 0x1, // average 2 samples
  ovs4    = 0x2, // average 4 samples
  ovs8    = 0x3, // average 8 samples
  ovs16   = 0x4, // average 16 samples
  ovs32   = 0x5  // average 32 samples

} ovsMAXIM_t;
/**
 * general module settings
 */

typedef struct
{
  // mode (HR, SpO2, or multi-led)
  modeMAXIM_t mode;

  // multiLED slots
  LEDSlotMAXIM_t LEDSlot[ MAXIM_SLOT_NUM ];
         uint8_t activeSlots;

  // LED currents
  LEDCurrentMAXIM_t LEDCurrentRed;
  LEDCurrentMAXIM_t LEDCurrentIR;
  LEDCurrentMAXIM_t LEDCurrentGreen;

  // timings
  sampleRateMAXIM_t sampleRate;
          pwMAXIM_t pulseWidth;

  // ADC range
    adcRangeMAXIM_t range;

  // averaging
        ovsMAXIM_t oversample;

  // device I2C address
  uint8_t address;

} settingsMAXIM_t;

#endif

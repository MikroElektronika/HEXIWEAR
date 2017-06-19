// File: MAXIM_types.h

// Some commonly used types in the MAXIM sensor module.

#ifndef _MAXIM_types_h_
#define _MAXIM_types_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>

#include "MAXIM/MAXIM_info.h"

////////////////////////////////////////////////////////////////////////////////
// Type definitions.                                                          //
////////////////////////////////////////////////////////////////////////////////

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

// use evaluation board software and datasheet
// to determine the desired current value
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

typedef void ( *maxim_callback_t )(
      void* sampleBuf,
    uint8_t numAvailSam,
      void* param );

#endif
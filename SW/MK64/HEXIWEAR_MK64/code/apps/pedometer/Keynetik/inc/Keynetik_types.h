/**
 * keynetik types
 */

#pragma once

#include <stdint.h>

typedef struct
{
  uint8_t steplength;       /** Step length in centimeters. If the value is 0 it will automatically calculate the user's step length from their gender and height. */
  uint8_t height;           /** Height in centimeters. This is used to estimate the step length if steplength is set to 0. */
  uint8_t weight;           /** Weight in kilograms. This is used to estimate the calories burned. */
  uint8_t filtersteps;      /** Number of steps that must occur within the filtertime in order to decide that the user is making steps. If this is set to 0, then the step filtering is disabled. */

  struct
  {
    uint8_t filtertime  :7;  /** Number of seconds in which filtersteps occur to decide that the user is making steps. If this is set to 0, then the step filtering is disabled. */
    uint8_t male        :1;  /** Set to 1 for a male user, or 0 for a female user. */

  } bits;

  /**
   * Length of the time window for speed calculation, in seconds. The allowable range is from 1 to 5.
   * If the value specified is greater than 5, it will be reset to 5, 0 will be reset to 1
   */
  uint8_t speedperiod;

  /** Step threshold value, in 1000ths of G. Set to 0 to use the default of 130 (0.13G).
   * Higher values will make the pedometer less sensitive, lower values may lead to false positives.
   */
  uint8_t stepthreshold;

} keynetikConfig_t;

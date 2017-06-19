/**
 * keynetik functions
 */

#pragma once

#include "keynetik_info.h"
#include "keynetik_defs.h"

/**
* Initialize the Keynetik library.
* @param oneG Value of 1G
* @param frequencyHz Accelerometer polling frequency, in readings per second
* @param isMale User's gender: 0 for female, non-0 for male
* @param heightCm User's height in centimeters. May be 0 if a custom stride length is to be used
* @param weightCm User's weight in kilograms
* @param strideCm Custom stride length in centimeters, or 0 for a standard stride length based on gender and height
* @param stepDelay Number of steps to expect before counting any steps (0 to turn off step filtering)
* @param delayWindow Amount of time within which these steps must be detected (in seconds; 0 to turn off step filtering)
 */
void KeynetikInitialize (
                              unsigned short oneG,
                              unsigned short frequencyHz,
			   keynetikConfig_t* config
                        );

/**
* Process an accelerometer reading and report detected events if any.
* \param x X axis reading
* \param y Y axis reading
* \param z Z axis reading
* \return combination of flags KEYNETIK_STEP and KEYNETIK_ACTIVITYCHANGED
 */
unsigned int KeynetikHandleIncomingEvent(int x, int y, int z);

/**
* Clear the collected data. Can be used after a period of skipped readings to re-initialize processing.
 */
void KeynetikReset();

/**
* Finalize the Keynetik library.
 */
void KeynetikTerminate();

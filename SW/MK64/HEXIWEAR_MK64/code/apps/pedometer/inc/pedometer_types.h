/**
 * \file pedometer_types.h
 * \version 1.00
 * \brief this file contains pedometer app related data-types
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * Neither the name of NXP, nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * visit: http://www.mikroe.com and http://www.nxp.com
 *
 * get support at: http://www.mikroe.com/forum and https://community.nxp.com
 *
 * Project HEXIWEAR, 2015
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "Keynetik_types.h"

typedef enum
{
  KeynetikActivityUnknown = 0,
  KeynetikActivityRest    = 1,
  KeynetikActivityWalking = 2,
  KeynetikActivityJogging = 3,
  KeynetikActivityRunning = 4

} activitylevel_t;

// todo: make enum
typedef uint8_t pedometer_status_t;

typedef uint16_t debounce_count_t;

/** pedometer handle */

typedef struct
{
  /** status */

  struct
  {
    union
    {
      struct
      {
        activitylevel_t activity       :3;  /**< Activity level */
                   bool suspend        :1;  /**< Pedometer autonomously suspended */
                   bool activitychange :1;  /**< Change in activity level */
                   bool stepchange     :1;  /**< Change in step count */
                   bool suspendchange  :1;  /**< Change in suspend state */
                   bool mergedflags    :1;  /**< Merged status flags */

      } bits;

      uint8_t byte;

    } status;

    uint8_t  version;    /**< Pedometer version number */
    uint16_t stepcount;  /**< Step count */
    uint16_t distance;   /**< Total distance in meters or activity state */
    uint16_t speed;      /**< Average speed in meters per hour. The value is updated on the completion of each step. */
    uint16_t calories;   /**< Calorie count expended */

    debounce_count_t sleepcount;   /**< Sleep debounce counter */

  } status;

  /** configuration */

  struct
  {
            uint16_t sleepminimum;          /**< Sleep vector magnitude minimum */
            uint16_t sleepmaximum;          /**< Sleep vector magnitude maximum */
    debounce_count_t sleepcount_threshold;  /**< Sleep debounce counter threshold */

    struct
    {
      uint8_t                :5;  /**< Reserved */
         bool sleep_dbcntm   :1;  /**< Sleep debounce counter mode. Set to 1 to clear the debounce counter when the test condition fails, otherwise decrement. */
         bool activity_dbcntm:1;  /**< Activity debounce counter mode. Set to 1 to clear the debounce counter when the test condition fails, otherwise decrement. */
         bool config         :1;  /**< Set to 1 to initialize the pedometer and configure it with the other configuration variables. */
    } bits;

    keynetikConfig_t keynetik;                 /**< Keynetik parameters (step length, height, weight, etc) */
    debounce_count_t activitycount_threshold;  /**< Activity debounce counter threshold */
             uint8_t stepcoalesce;             /**< Number of steps to coalesce for step interrupt_t */

  } config;

  /** privates */

  struct
  {
    debounce_count_t activitycount;      /**< Activity debounce counter */
            uint16_t stepchg_stepcount;  /**< Step count at last stepchange interrupt_t (for step coalesing) */

  } private;

} pedometer_t;

typedef enum
{
  PEDO_PROCESS_STATUS_SUCCESS,
  PEDO_PROCESS_STATUS_ERROR

} pedo_process_status_t;

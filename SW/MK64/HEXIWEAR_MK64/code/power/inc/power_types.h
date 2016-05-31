/**
 * \file power_types.h
 * \version 1.00
 * \brief power management, related data types
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

typedef enum
{
    POWER_OLED,
    POWER_MCU,
    POWER_HTU_TSL,
    POWER_MAXIM,
    POWER_BATTERY

} power_peripheral_t;

typedef enum
{
    POWER_STATUS_SUCCESS,    // success
    POWER_STATUS_INIT_ERROR, // error prior to function being executed
    POWER_STATUS_ERROR       // fail

} power_status_t;

typedef enum
{
    POWER_WAKE_SRC_NONE,
    POWER_WAKE_SRC_USER,
    POWER_WAKE_SRC_SENSOR_TIMER

} power_wake_src_t;

typedef enum
{
    POWER_SLEEP_SRC_NONE,
	POWER_SLEEP_SRC_SENSOR_TAG,
    POWER_SLEEP_SRC_RTC

} power_sleep_src_t;

typedef enum
{
    POWER_CURRENT_MODE_NORMAL,
    POWER_CURRENT_MODE_SLEEP_SHALLOW,   /**< only OLED */
    POWER_CURRENT_MODE_SLEEP_TOTAL,     /**< everything: OLED + non-NXP sensors + MCU */
    POWER_CURRENT_MODE_SLEEP_SENSOR_TAG /**< only MCU */

} power_current_mode_t;

typedef enum
{
    POWER_SLEEP_MODE_SHALLOW,    /**< only OLED */
    POWER_SLEEP_MODE_TOTAL,      /**< everything: OLED + non-NXP sensors + MCU */
    POWER_SLEEP_MODE_SENSOR_TAG  /**< only MCU */

} power_sleep_mode_t;

typedef enum
{
    POWER_SLEEP_STATE_ON,
    POWER_SLEEP_STATE_OFF

} power_sleepState_t;

/**
 * \file timer_driver.h
 * \version 1.00
 * \brief  this file contains functionality for timers used throughout HEXIWEAR
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

#include "sensor_timer.h"
#include "sensor_driver.h"
#include "HEXIWEAR_info.h"

#define TIMER_BLINKING_PERIOD_MS ( 8000 )

/**
 * initialize the timer
 * @param timerToUse selected timer peripheral
 */
void timer_Init( hexiwear_timer_t timerToUse );

/**
 * deinitialize the timer
 * @param timerToUse selected timer peripheral
 */
void timer_Deinit( hexiwear_timer_t timerToUse );

/**
 * start the timer
 * @param timerToUse selected timer peripheral
 */
void timer_Start( hexiwear_timer_t timerToUse );

/**
 * set the period for the chosen timer
 * @param timerToUse selected timer peripheral
 * @param newPeriod  new desired timer period
 */
void timer_SetPeriod( hexiwear_timer_t timerToUse, uint32_t newPeriod );

/**
 * stop the timer
 * @param timerToUse selected timer peripheral
 */
void timer_Stop( hexiwear_timer_t timerToUse );

/**
 * get timer state
 * @param timerToUse selected timer peripheral
 */
bool timer_IsActive( hexiwear_timer_t timerToUse );

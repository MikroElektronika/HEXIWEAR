/**
 * \file power_driver.h
 * \version 1.00
 * \brief this file contains power management routines
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

#include <stdbool.h>
#include "fsl_power_manager.h"
#include "power_types.h"

/**
 * initialize the power task and relevant power objects
 * @return status flag
 */
power_status_t power_Init();

/**
 * activate/deactivate power supplies for sensors
 */
void power_SensorManagement();

/**
 * turn the selected peripheral ON
 * @param  peripheral peripheral to turn on
 * @return            status flag
 */
power_status_t power_TurnON ( power_peripheral_t peripheral );

/**
 * turn the selected peripheral OFF
 * @param  peripheral peripheral to turn off
 * @return            status flag
 */
power_status_t power_TurnOFF( power_peripheral_t peripheral );

/**
 * set BLE_RST pin to 0 and then release it
 */
void power_ResetKW40();

/**
 * return power flags
 * @param peripheral peripheral which flags to return
 * @return flag
 */
bool power_IsActive( power_peripheral_t peripheral );

/**
 * enable the power save feature:
 * enable OLED
 * enable current sensor subscriptions
 */
void power_EnablePowerSave();

/**
 * disable the power save feature:
 * disable OLED
 * disable current sensor subscriptions
 */
void power_DisablePowerSave();

/**
 * set sleep source
 * @param sleepSrc entity which will put the MCU to sleep
 */
void power_SetSleepSource( power_sleep_src_t sleepSrc );

/**
 * get sleep source
 * @return current entity which will put the MCU to sleep
 */
power_sleep_src_t power_GetSleepSource();

/**
 * set wakeup source
 * @param wakeupSrc entity which wake up the MCU
 */
power_status_t power_SetWakeSource( power_wake_src_t wakeSrc );

/**
 * get wakeup source
 * @return current entity which will wake up the MCU
 */
power_wake_src_t power_GetWakeSource();

/**
 * check if this was the touch that woken the MCU
 * @return touch flag
 */
bool power_HasJustExitSleep();

/**
 * put HEXIWEAR to sleep
 */
void power_GotoSleep();

/**
 * set current HEXIWEAR mode
 * @param newMode mode to set
 */
void power_SetCurrentMode( power_current_mode_t newMode );

/**
 * get current HEXIWEAR mode
 * @return current mode
 */
power_current_mode_t power_GetCurrentMode();

/**
 * set new power mode
 * @param new desired power mode
 */
void power_SetSleepMode( power_sleep_mode_t newMode );

/**
 * get currently selected sleep mode
 * @return current sleep mode
 */
power_sleep_mode_t power_GetSleepMode();

/**
 * turn the screen off by sending the command
 * and turning off the power supply
 */
void power_TurnScreenOFF();

/**
 * turn the screen on by switching on the power supply
 * and sending the command
 */
void power_TurnScreenON();

power_status_t power_PostToSTSema();
power_status_t power_TakeFromSTSema();

/**
 * send sleep ON/OFF packet to KW40
 */
power_status_t power_AlertKW40( power_sleepState_t sleepState );

/**
 * call before entering sleep mode
 * @param notify optional parameters
 * @param callbackData optional parameters
 * @return status flag
 */
power_manager_error_code_t power_CallBeforeSleep(
													power_manager_notify_struct_t* notify,
													power_manager_callback_data_t* callbackData
												);

/**
 * call after exiting sleep mode
 * @param notify optional parameters
 * @param callbackData optional parameters
 * @return flag
 */
power_manager_error_code_t power_CallAfterSleep (
													power_manager_notify_struct_t* notify,
													power_manager_callback_data_t* callbackData
												);

/**
 * check for battery status
 * @return status flag
 */
bool power_IsBatteryLow();

/**
 * set battery status as low
 */
void power_SetBatteryLow();

/**
 * unset battery status as low
 */
void power_UnsetBatteryLow();

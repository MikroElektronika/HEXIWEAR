/**
 * @file sensor_driver.h
 * @brief sensor wrapper routines for manipulating sensor's data-packets, formatting and sending it
 * to different targets ( KW40, OLED... )
 *
 * @version 1.0.1
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
 * Neither the name of NXP Semiconductor, Inc. nor the names of its
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
 * support: http://www.mikroe.com/forum and https://community.freescale.com
 *
 * Project HEXIWEAR, 2015
 */

#pragma once

#include "fsl_os_abstraction.h"

#include "HEXIWEAR.h"

#include "FXAS_driver.h"
#include "FXOS_driver.h"
#include "HTU_driver.h"
#include "MPL_driver.h"
#include "TSL_driver.h"
#include "MAXIM_driver.h"

/**
 * create the sensor task
 */
osa_status_t sensor_Init();

/**
 * reset the packet counter, to trigger reading during the
 * next sensor loop
 * @param packetToUpdate packet to reset
 */
void sensor_ResetPacketcounter( packet_t packetToUpdate );


/**
 * set targets for the particular sensor packet
 * @param packetToUpdate packet which targets are to be updated
 * @param newPushTarget  new targets
 * @param shouldToggleTask  flag to check if sensor task should be triggered, if paused before
 */
void sensor_SetPacketTargets(
									   packet_t packetToUpdate,
                            packet_pushTarget_t newPushTarget,
										   bool shouldToggleTask
                          );

/**
 * retrieve particular sensor's targets
 * @param  sensorToUpdate packet which targets are to be returned
 * @return                desired packet targets
 */
packet_pushTarget_t sensor_GetPacketTargets ( packet_t sensorToUpdate );

/**
 * assign polling delay in [ms] to the particular packet
 * @param packetToUpdate packet which polling delay is to be updated
 * @param delay_ms       delay in [ms]
 */
void sensor_RegisterPacketDelay (
                                  packet_t packetToUpdate,
                                  uint32_t delay_ms
                                );

/**
 * set minimum delay for the sensor loop
 * @param delay in miliseconds
 */
void sensor_SetMinimumDelay ( uint32_t delay );

/**
 * backup all the sensors which have KW40 as its targets
 */
void sensor_SaveTargetsForKW40();

/**
 * restore all the sensors which have KW40 as its targets
 */
void sensor_RestoreTargetsForKW40();

/**
 * flush the backup KW40 list
 */
void sensor_ResetTargetsForKW40();

/**
 * check if there are sensor packets with KW40 as its target
 */
bool sensor_CheckForKW40Targets();

/**
 * initiate the accelerometer
 */
void sensor_InitAcc();

/**
 * reset LED counter
 */
void sensor_ResetLEDIndicator();

/**
 * turn LED off
 */
void sensor_ClearLEDIndicator();

/**
 * stop waiting for semaphore
 */
void sensor_StopWait();

/**
 * suspend the sensor task
 */
void sensor_Suspend();

/**
 * resume the sensor task
 */
void sensor_Resume();

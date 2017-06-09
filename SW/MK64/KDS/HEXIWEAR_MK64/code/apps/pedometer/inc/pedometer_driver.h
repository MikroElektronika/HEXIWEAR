/**
 * \file pedometer_driver.h
 * \version 1.00
 * \brief this file contains pedometer app functionality
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

#include "pedometer_info.h"
#include "pedometer_defs.h"
#include <string.h>
#include "fsl_os_abstraction.h"
#include "host_mcu_interface.h"

/**
 * reset the handle values to their default
 */
pedometer_status_t pedometer_Reset();

/**
 * debounce counter
 * @param  dbcntm    [description]
 * @param  condition [description]
 * @param  count     [description]
 * @param  threshold [description]
 * @return           [description]
 */
bool debounce_count (
                                   bool dbcntm,
                                   bool condition,
                      debounce_count_t* count,
                       debounce_count_t threshold
                    );

/**
 * [pedometer_Init description]
 */
void pedometer_Init();

/**
 * [pedometer_CreateTask description]
 */
void pedometer_CreateTask();

/**
 * [pedometer_Deinit description]
 */
void pedometer_Deinit();

/**
 * [fitness_pedometer_QueueMsgPut description]
 * @param  packet [description]
 * @return        [description]
 */
pedo_process_status_t pedometer_QueueMsgPut (
                                              hostInterface_packet_t* packet
                                            );

/**
 * get steps
 */
uint16_t pedometer_GetStepCounter();

/**
 * resume the pedometer step detection process
 */
void pedometer_Resume();

/**
 * pause the pedometer step detection process
 */
void pedometer_Pause();


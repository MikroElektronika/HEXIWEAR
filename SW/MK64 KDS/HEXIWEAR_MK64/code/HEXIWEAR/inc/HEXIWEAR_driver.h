/**
 * \file HEXIWEAR_driver.h
 * \version 1.00
 * \brief this file contains global HEXIWEAR functionality
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
 * get support at: http://www.mikroe.com/forum and https://community.freescale.com
 *
 * Project HEXIWEAR, 2015
 */

#pragma once

#include "sensor.h"
#include "host_mcu_interface.h"
#include "gui_driver.h"
#include "rtc_driver.h"

/**
 * initialize the tasks
 * @return status flag
 */
hexiwear_status_t HEXIWEAR_Init();

/**
 * reset the MCU
 */
void HEXIWEAR_ResetMCU();

/**
 * [HEXIWEAR_GetBackupList description]
 */
void* HEXIWEAR_GetAppBackupList();

/**
 * [HEXIWEAR_GetTargetApp description]
 */
packet_pushTarget_t HEXIWEAR_GetAppTarget();

/**
 * [HEXIWEAR_SetBackupList description]
 */
void HEXIWEAR_SetBackupList( packet_pushTarget_t* currentBackupList );

/**
 * [HEXIWEAR_SetTargetApp description]
 */
void HEXIWEAR_SetTargetApp( packet_pushTarget_t currentApp );

/**
 * set application-specific flags
 * @param  flashAddress flash address for programming
 * @param  flags        data to be programmed into flash
 * @param  flagSize     data size, must be multiple of 8 bytes
 * @return              status flag
 */
hexiwear_status_t HEXIWEAR_SetFlags (
                                         uint32_t flashAddress,
                                            void* flags,
                                         uint32_t flagSize
                                    );

/**
 * [HEXIWEAR_CreateVersionEvent description]
 */
void HEXIWEAR_CreateVersionEvent();

/**
 * [HEXIWEAR_CreateVersionEvent description]
 */
void HEXIWEAR_SendVersionReq();

/**
 * [HEXIWEAR_WaitForVersionUpdate description]
 * @param  timeout [description]
 * @return         [description]
 */
osa_status_t HEXIWEAR_WaitForVersionUpdate(uint32_t timeout);

/**
 * update KW40 version
 * @return status flag
 */
osa_status_t HEXIWEAR_UpdateVersion();

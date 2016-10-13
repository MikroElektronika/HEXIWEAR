/**
 * \file watch.h
 * \version 1.00
 * \brief this file contains watch screen objects and prototypes intended to be available
 * for the rest of the project
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

#include "fsl_rtc_driver.h"
#include "gui_driver.h"

#define WATCH_STACK_SIZE ( 0x500 )
#define WATCH_PRIO       ( 11 )

typedef enum
{
    linkState_disconnected = 0,
    linkState_connected    = 1,
} linkState_t;

// screens
extern guiScreen_t watchScreen;

/**
 * check charging status on the interrupt
 */
void watch_CheckBatteryStatus();

linkState_t watch_CurrentLinkStateGet(void);
void watch_SendGetLinkStateReq(void);
osa_status_t watch_WaitForLinkStateUpdate(uint32_t timeout);
osa_status_t watch_LinkStateUpdate(linkState_t new_linkState);
void watch_CreateLinkStateUpdateEvent(void);

void watch_SetBatteryEvent();
void watch_SetNotification();
bool watch_IsBatteryCharging();


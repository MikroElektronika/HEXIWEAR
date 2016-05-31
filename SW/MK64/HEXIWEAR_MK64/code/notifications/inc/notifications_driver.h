/**
 * \file notifications_driver.h
 * \version 1.00
 * \brief this file contains incoming alert routines
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

#include "fsl_os_abstraction.h"
#include "notifications_types.h"

/** public API prototypes */

/**
 * set the notifications' counter's value
 * @param notifType notification type
 * @param value     counter's value
 */
void Notification_SetUnreadCounter( notification_type_t notifType, uint8_t value );

/**
 * get the notifications' counter's value
 * @param notifType notification type
 * @return          counter's value
 */
uint8_t Notification_GetUnreadCounter( notification_type_t notifType );

/**
 * initialize the notification event
 * @return  status flag
 */
notification_status_t Notification_Init();

/**
 * wait for the notification event
 * @param  type    notification type
 * @param  timeout timeout value in [ms]
 * @return         status flag
 */
notification_status_t Notification_WaitForEvent( notification_type_t* notifType, uint32_t timeout );

/**
 * set the notification event
 * @param type notification type
 * @return     status flag
 */
notification_status_t Notification_SetEvent( notification_type_t notifType );
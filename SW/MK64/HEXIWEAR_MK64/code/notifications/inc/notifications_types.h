/**
 * \file notifications_types.h
 * \version 1.00
 * \brief this file contains data-types related to alerts and their communication
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
#include "fsl_os_abstraction.h"
#include "fsl_rtc_driver.h"
#include "host_mcu_interface.h"

typedef enum
{
	NOTIF_TYPE_SMS    = 1 << 1,
	NOTIF_TYPE_MAIL   = 1 << 2,
	NOTIF_TYPE_CALL   = 1 << 3,

} notification_type_t;

typedef enum
{
  NOTIF_STATUS_SUCCESS,     // success
  NOTIF_STATUS_ERROR,       // fail

} notification_status_t;

/** category for iOS notifications */
typedef enum
{
  ancCategoryId_other           = 0,
  ancCategoryId_incomingCall    = 1,
  ancCategoryId_missedCall      = 2,
  ancCategoryId_voiceMail       = 3,
  ancCategoryId_social          = 4,
  ancCategoryId_schedule        = 5,
  ancCategoryId_email           = 6,
  ancCategoryId_news            = 7,
  ancCategoryId_healthFitness   = 8,
  ancCategoryId_businessFinance = 9,
  ancCategoryId_location        = 10,
  ancCategoryId_entertainment   = 11

} ancCategoryId_t;

/** notifications actions */
typedef enum
{
  ancEventId_NotifAdded    = 0,
  ancEventId_NotifModified = 1,
  ancEventId_NotifRemoved  = 2

} ancEventId_t;

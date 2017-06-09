/**
 * \file gui_notifications_private.h
 * \version 1.00
 * \brief this file contains notifications related private GUI objects
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

#include "gui_driver.h"

#define GUI_NOTIFICATIONS_PRIO       ( HEXIWEAR_GUI_PRIO )
#define GUI_NOTIFICATIONS_STACK_SIZE ( 0x400 )

// resources
extern const uint8_t
	gui_notifications_screen_bmp[ OLED_GRAM_SIZE+6 ],
	gui_notifications_mainScreen_bmp[ OLED_GRAM_SIZE+6 ];

extern const uint8_t
    gui_notifications_mail_white_bmp[646];
extern const uint8_t
    gui_notifications_sms_white_bmp[516];
extern const uint8_t
    gui_notifications_call_white_bmp[652];
extern const uint8_t
    gui_notifications_mail_blue_bmp[646];
extern const uint8_t
    gui_notifications_sms_blue_bmp[516];
extern const uint8_t
    gui_notifications_call_blue_bmp[652];

// objects
extern guiImage_t
    gui_notifications_mailIcon,
    gui_notifications_smsIcon,
    gui_notifications_callIcon;

extern guiLabel_t
    gui_notifications_labelMail,
    gui_notifications_labelSms,
    gui_notifications_labelCall;

// callbacks
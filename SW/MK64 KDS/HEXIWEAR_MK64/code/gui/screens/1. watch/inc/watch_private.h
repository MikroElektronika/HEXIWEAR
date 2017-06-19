/**
 * \file watch_private.h
 * \version 1.00
 * \brief this file contains watch screen related resources and prototypes
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

// Resources
extern const uint8_t battery_0_bmp[ 588 + 6 ];
extern const uint8_t battery_1_bmp[ 588 + 6 ];
extern const uint8_t battery_2_bmp[ 588 + 6 ];
extern const uint8_t battery_3_bmp[ 588 + 6 ];
extern const uint8_t battery_4_bmp[ 588 + 6 ];
extern const uint8_t battery_5_bmp[ 588 + 6 ];
extern const uint8_t watch_sms_bmp[370];
extern const uint8_t watch_sms_gray_bmp[370];
extern const uint8_t watch_mail_bmp[306];
extern const uint8_t watch_mail_gray_bmp[306];
extern const uint8_t watch_phone_call_bmp[398];
extern const uint8_t watch_phone_call_gray_bmp[398];
extern const uint8_t watch_bluetooth_logo_white_bmp[1206];
extern const uint8_t watch_bluetooth_logo_blue_bmp[1206];
//extern const uint8_t celsius_bmp[204];
extern const uint8_t celsius_bmp[500];
extern const uint8_t battery_charge_bmp[1110];

// Objects
extern guiImage_t watch_imgBattery;
extern guiImage_t watch_imgSms;
extern guiImage_t watch_imgMail;
extern guiImage_t watch_imgCall;
extern guiImage_t watch_imgBluetoothLogo;
extern guiImage_t watch_imgTempUnit;

extern guiLabel_t watch_labelTime;
extern guiLabel_t watch_labelDate;
extern guiLabel_t watch_labelTemp;
extern guiLabel_t watch_labelEnter;

// Callbacks
void watch_Init( void *param );
void watch_CreateTasks(void *param);
void watch_DestroyTasks(void *param);
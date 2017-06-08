/**
 * \file screens_common.h
 * \version 1.00
 * \brief this file contains common screen objects' and structures' declarations
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
#include "OLED_driver.h"

#include "watch.h"

#include "apps.h"
#include "fitness.h"
#include "gui_pedometer.h"
#include "gui_heartRate.h"
#include "gui_sensorTag.h"
#include "gui_weatherStation.h"
#include "gui_motionControl.h"
#include "flashlight.h"

#include "bootloader.h"
#include "bluetooth.h"
#include "buttons_group.h"
#include "haptic.h"
#include "getApp.h"
#include "googleApp.h"
#include "iOSApp.h"
#include "about.h"
#include "info.h"
#include "reset.h"
#include "watch_set.h"

#include "power.h"

#include "gui_notifications.h"

#include "settings.h"
#include "bond.h"

#define SCREEN_BYTE_SIZE ( OLED_SCREEN_WIDTH * OLED_SCREEN_HEIGHT * OLED_BYTES_PER_PIXEL )

extern guiLabel_t screen_labelEnter;
extern guiLabel_t screen_labelBack;

extern const uint8_t button_start_bmp[1386];
extern const uint8_t button_stop_bmp[1386];
extern const uint8_t button_start_disabled_bmp[1386];
extern const uint8_t button_back_bmp[1416];
extern const uint8_t button_back_disabled_bmp[1416];
extern const uint8_t button_reset_bmp[1386];

extern guiImage_t screen_buttonStart;
extern guiImage_t screen_buttonStartDisabled;
extern guiImage_t screen_buttonStop;
extern guiImage_t screen_buttonReset;
extern guiImage_t screen_buttonBack;
extern guiImage_t screen_buttonBackDisabled;

extern guiImage_t screen_buttonRightUp;
extern guiImage_t screen_buttonRightDown;
extern guiImage_t screen_buttonLeftUp;
extern guiImage_t screen_buttonLeftDown;

extern const uint8_t
   hexiwear_logo_bmp[ OLED_GRAM_SIZE + 6 ],
   buttonGroup_right_bmp[36],
   buttonGroup_left_bmp[36];

extern guiScreen_t
  splashScreen;

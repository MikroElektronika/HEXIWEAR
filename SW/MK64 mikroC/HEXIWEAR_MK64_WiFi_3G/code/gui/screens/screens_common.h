// File: screens_common.h

// Common header for the screen gui modules.

#ifndef _screens_common_h_
#define _screens_common_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>

#include "projdefs.h"
#include "OLED_driver.h"
#include "gui_types.h"

#include "watch/watch.h"
#include "apps/apps.h"
#include "gui_notifications/gui_notifications.h"
#include "settings/settings.h"
#include "bond/bond.h"
#include "sensorTag/gui_sensorTag.h"
#include "settings/bluetooth/bluetooth.h"
#include "settings/wireless_conn/wireless.h"
#include "settings/bootloader/bootloader.h"
#include "settings/buttons_group/buttons_group.h"
#include "settings/haptic/haptic.h"
#include "settings/getApp/getApp.h"
#include "settings/getApp/googleApp/googleApp.h"
#include "settings/getApp/iOSApp/iOSApp.h"
#include "settings/about/about.h"
#include "settings/about/info/info.h"
#include "settings/reset/reset.h"
#include "apps/weatherStation/gui_weatherStation.h"
#include "apps/motionControl/gui_motionControl.h"
#include "apps/fitness/fitness.h"
#include "apps/fitness/gui_pedometer/gui_pedometer.h"
#include "apps/fitness/gui_heartRate/gui_heartRate.h"
#include "apps/flashlight/flashlight.h"
#include "message/message.h"

////////////////////////////////////////////////////////////////////////////////
// Macro definitions                                                          //
////////////////////////////////////////////////////////////////////////////////

#define SCREEN_BYTE_SIZE                                                       \
    ( OLED_SCREEN_WIDTH * OLED_SCREEN_HEIGHT * OLED_BYTES_PER_PIXEL )

////////////////////////////////////////////////////////////////////////////////
// Global variable declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

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

extern const uint8_t hexiwear_logo_bmp[ OLED_GRAM_SIZE + 6 ];
extern const uint8_t buttonGroup_right_bmp[36];
extern const uint8_t buttonGroup_left_bmp[36];

extern guiScreen_t splashScreen;

#endif
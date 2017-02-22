#ifndef HG_SCREENS_COMMON
#define HG_SCREENS_COMMON

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

#include "relay_click.h"

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

#endif

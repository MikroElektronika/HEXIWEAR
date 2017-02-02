#ifndef HG_SCREENS_COMMON
#define HG_SCREENS_COMMON

#include <stdint.h>
#include "OLED_driver.h"

#include "OLED_info.h"

#define SCREEN_BYTE_SIZE ( OLED_SCREEN_WIDTH * OLED_SCREEN_HEIGHT * OLED_BYTES_PER_PIXEL )
extern const uint8_t
   hexiwear_logo_bmp[18438],
   nfc_logo_bmp[18438],
   bluetooth_logo_bmp[18438],
   access_granted_bmp[9222],
   access_denied_bmp[9222],
   mood_status_bmp[5][18438];
#endif

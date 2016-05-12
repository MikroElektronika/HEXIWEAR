#ifndef HG_SCREENS_COMMON
#define HG_SCREENS_COMMON

#include <stdint.h>
#include "OLED_driver.h"

#include "OLED_info.h"

#define SCREEN_BYTE_SIZE ( OLED_SCREEN_WIDTH * OLED_SCREEN_HEIGHT * OLED_BYTES_PER_PIXEL )
extern const uint8_t
   hexiwear_logo_bmp[ OLED_GRAM_SIZE + 6 ],
   motion_detected_bmp[18438],
   motion_none_bmp[18438];

#endif

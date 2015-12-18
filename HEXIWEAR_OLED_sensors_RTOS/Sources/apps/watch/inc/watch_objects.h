#ifndef HG_WATCH_OBJECTS
#define HG_WATCH_OBJECTS

#include "apps.h"

// Resources
extern const uint8_t watch_bmp[ SCREEN_BYTE_SIZE+6 ];
extern const uint8_t battery_0_bmp[588 + 6];
extern const uint8_t battery_1_bmp[588 + 6];
extern const uint8_t battery_2_bmp[588 + 6];
extern const uint8_t battery_3_bmp[588 + 6];
extern const uint8_t battery_4_bmp[588 + 6];
extern const uint8_t battery_5_bmp[588 + 6];

// Objects
extern apps_image_t watch_imgBattery;
extern apps_label_t watch_labelTime;
extern apps_label_t watch_labelDate;
extern apps_label_t watch_labelTemp;

#endif

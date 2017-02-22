#ifndef HG_WATCH_PRIVATE
#define HG_WATCH_PRIVATE

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

#endif

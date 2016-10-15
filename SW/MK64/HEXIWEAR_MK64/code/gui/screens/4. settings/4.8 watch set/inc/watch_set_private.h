#pragma once

#include "gui_driver.h"

#define WATCH_SET_STACK_SIZE ( 0x400 )
#define WATCH_SET_PRIO       ( HEXIWEAR_APP_PRIO )

// Resources
// extern const uint8_t
//  watch_set_screen_bmp[ OLED_GRAM_SIZE+6 ];
extern const uint8_t main_screen_bmp[18438];
extern const uint8_t setting_screen_bmp[18438];

extern guiLabel_t gui_year_label;
extern guiLabel_t gui_month_label;
extern guiLabel_t gui_day_label;
extern guiLabel_t gui_time_colon_label;
extern guiLabel_t gui_hour_label;
extern guiLabel_t gui_minute_label;

extern char dayOfWeekStr[7][4];
extern char monthsOfYearStr[12][4];
extern uint8_t daysInMonth[12];

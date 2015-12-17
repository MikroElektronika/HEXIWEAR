#ifndef HG_WATCH
#define HG_WATCH

#include "fsl_rtc_driver.h"

#define WATCH_STACK_SIZE ( 0x500 )
#define WATCH_PRIO       ( 10 )

// resources
extern const uint8_t
  watch_bmp[ SCREEN_BYTE_SIZE+6 ],
  battery_0_bmp[588 + 6],
  battery_1_bmp[588 + 6],
  battery_2_bmp[588 + 6],
  battery_3_bmp[588 + 6],
  battery_4_bmp[588 + 6],
  battery_5_bmp[588 + 6];

// screens
extern const menuItem_t
  watch_item;

// task handlers
extern task_handler_t
  watch_handler;

#endif

#ifndef HG_WATCH
#define HG_WATCH

#include "fsl_rtc_driver.h"

#define WATCH_STACK_SIZE ( 0x500 )
#define WATCH_PRIO       ( 10 )

// screens
extern const menuItem_t watch_item;

// task handlers
task_handler_t watch_timeUpdate_handler;
task_handler_t watch_getPackets_handler;

#endif

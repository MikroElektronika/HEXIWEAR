/**
 * menu driver constants and info
 * Project HEXIWEAR, 2015
 */

#ifndef HG_MENU_INFO
#define HG_MENU_INFO

#include "OLED_info.h"

#define TASK_MENU_APP_RTC_STACK_SIZE ( 0x1000 )
#define TASK_MENU_APP_FIT_STACK_SIZE ( 0x2000 )
#define TASK_MENU_APP_ST_STACK_SIZE  ( 0x3000 )

#define TASK_MENU_APP_RTC_DATA_PRIO  ( 10 )
#define TASK_MENU_APP_ST_DATA_PRIO   ( 10 )
#define TASK_MENU_APP_FIT_DATA_PRIO  ( 10 )

#define QUEUE_MENU_LENGTH ( 3 )

#define BMP_HEADER_BYTE_SIZE (6)
#define MenuDriver_SkipHeader( imgPtr ) ( (const uint8_t*)(imgPtr) + BMP_HEADER_BYTE_SIZE )

#define MENU_IMAGE_SIZE ( OLED_SCREEN_WIDTH * OLED_SCREEN_HEIGHT * OLED_BYTES_PER_PIXEL )

#endif

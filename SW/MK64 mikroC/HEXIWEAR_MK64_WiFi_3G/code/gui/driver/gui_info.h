// File: gui_info.h

// Information for the gui driver module.

#ifndef _gui_info_h_
#define _gui_info_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "OLED_info.h"

////////////////////////////////////////////////////////////////////////////////
// Macro definitions                                                          //
////////////////////////////////////////////////////////////////////////////////

#define TASK_GUI_APP_RTC_STACK_SIZE ( 0x1000 )
#define TASK_GUI_APP_FIT_STACK_SIZE ( 0x2000 )
#define TASK_GUI_APP_ST_STACK_SIZE  ( 0x3000 )

#define TASK_GUI_APP_RTC_DATA_PRIO  ( 10 )
#define TASK_GUI_APP_ST_DATA_PRIO   ( 10 )
#define TASK_GUI_APP_FIT_DATA_PRIO  ( 10 )

#define QUEUE_GUI_LENGTH ( 3 )

#define BMP_HEADER_BYTE_SIZE ( 6 )
#define GuiDriver_SkipHeader( imgPtr )                                         \
    ( ( const uint8_t* )( imgPtr ) + BMP_HEADER_BYTE_SIZE )

#define GUI_IMAGE_SIZE                                                         \
    ( OLED_SCREEN_WIDTH * OLED_SCREEN_HEIGHT * OLED_BYTES_PER_PIXEL )

#endif
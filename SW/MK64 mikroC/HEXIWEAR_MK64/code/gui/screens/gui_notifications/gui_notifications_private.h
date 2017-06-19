// File: gui_notifications_private.h

// Declarations of resources in the notifications gui module.

#ifndef _gui_notifications_private_h_
#define _gui_notifications_private_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "gui_driver.h"

////////////////////////////////////////////////////////////////////////////////
// Macro definitions.                                                         //
////////////////////////////////////////////////////////////////////////////////

#define GUI_NOTIFICATIONS_PRIO       ( HEXIWEAR_GUI_PRIO )
#define GUI_NOTIFICATIONS_STACK_SIZE ( 0x400 )

////////////////////////////////////////////////////////////////////////////////
// Global variable declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

// resources
extern const uint8_t gui_notifications_screen_bmp[ OLED_GRAM_SIZE+6 ];
extern const uint8_t gui_notifications_mainScreen_bmp[ OLED_GRAM_SIZE+6 ];

extern const uint8_t gui_notifications_mail_white_bmp[646];
extern const uint8_t gui_notifications_sms_white_bmp[516];
extern const uint8_t gui_notifications_call_white_bmp[652];
extern const uint8_t gui_notifications_mail_blue_bmp[646];
extern const uint8_t gui_notifications_sms_blue_bmp[516];
extern const uint8_t gui_notifications_call_blue_bmp[652];

// objects
extern guiImage_t gui_notifications_mailIcon;
extern guiImage_t gui_notifications_smsIcon;
extern guiImage_t gui_notifications_callIcon;

extern guiLabel_t gui_notifications_labelMail;
extern guiLabel_t gui_notifications_labelSms;
extern guiLabel_t gui_notifications_labelCall;

#endif
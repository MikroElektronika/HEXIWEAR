#ifndef HG_NOTIF
#define HG_NOTIF

#include "fsl_rtc_driver.h"
#include "gui_driver.h"
#include "notifications_driver.h"
#include "screens_common.h"

// screens
extern guiScreen_t
	notifScreen,
	notifMainScreen;

/**
 * [gui_notifications_Init description]
 * @param param [description]
 */
void gui_notifications_Init( void* param );

/**
* [gui_notifications_CreateTasks description]
* @param param [description]
*/
void gui_notifications_CreateTasks( void* param );

/**
* [gui_notifications_DestroyTasks description]
* @param param [description]
*/
void gui_notifications_DestroyTasks( void* param );


#endif

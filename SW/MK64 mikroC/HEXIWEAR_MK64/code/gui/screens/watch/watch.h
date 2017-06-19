// File: watch.h

// Declarations of main functionalities in the watch gui module.

#ifndef _watch_h_
#define _watch_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "rtc_driver.h"
#include "gui_driver.h"

// screens
extern guiScreen_t watchScreen;

////////////////////////////////////////////////////////////////////////////////
// Macro definitions.                                                         //
////////////////////////////////////////////////////////////////////////////////
 
#define WATCH_STACK_SIZE ( 0x500 )
#define WATCH_PRIO       ( 11 )

////////////////////////////////////////////////////////////////////////////////
// Type definitions.                                                          //
////////////////////////////////////////////////////////////////////////////////

typedef enum
{
    linkState_disconnected = 0,
    linkState_connected    = 1,
} linkState_t;

////////////////////////////////////////////////////////////////////////////////
// Global function declarations.                                              //
////////////////////////////////////////////////////////////////////////////////
 
void watch_CheckBatteryStatus();

linkState_t watch_CurrentLinkStateGet();
void watch_SendGetLinkStateReq();
osa_status_t watch_WaitForLinkStateUpdate( uint32_t timeout );
osa_status_t watch_LinkStateUpdate( linkState_t new_linkState );
void watch_CreateLinkStateUpdateEvent();

void watch_SetBatteryEvent();
void watch_SetNotification();
bool watch_IsBatteryCharging();

#endif
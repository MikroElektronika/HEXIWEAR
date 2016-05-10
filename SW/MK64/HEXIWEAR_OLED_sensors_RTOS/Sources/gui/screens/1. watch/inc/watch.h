#ifndef HG_WATCH
#define HG_WATCH

#include "fsl_rtc_driver.h"
#include "gui_driver.h"

#define WATCH_STACK_SIZE ( 0x500 )
#define WATCH_PRIO       ( 11 )

typedef enum
{
    linkState_disconnected = 0,
    linkState_connected    = 1,
} linkState_t;

// screens
extern guiScreen_t watchScreen;

/**
 * check charging status on the interrupt
 */
void watch_CheckBatteryStatus();
linkState_t watch_CurrentLinkStateGet(void);
void watch_SendGetLinkStateReq(void);
osa_status_t watch_WaitForLinkStateUpdate(uint32_t timeout);
osa_status_t watch_LinkStateUpdate(linkState_t new_linkState);
void watch_CreateLinkStateUpdateEvent(void);

void watch_SetBatteryEvent();
void watch_SetNotification();
bool watch_IsBatteryCharging();

#endif

// File: host_mcu_interface_events.c

// Definitions of events functionalities of the MCU interface module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////
 
#include <stdint.h>
#include <stddef.h>

#include "host_mcu_interface.h"

////////////////////////////////////////////////////////////////////////////////
// Static variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

static event_t hostInterface_okConfirmEvent;

////////////////////////////////////////////////////////////////////////////////
// Global variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

const event_flags_t gHostInterface_eventSendOkPacketMask     = 1 << 1;
const event_flags_t gHostInterface_eventConfirmPacketMask    = 1 << 2;
const event_flags_t gHostInterface_eventConfirmAttPacketMask = 1 << 3;

////////////////////////////////////////////////////////////////////////////////
// Static function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Waits on the host interface events.
static osa_status_t HostInterface_EventWait (
    event_flags_t flagsToWait,
         uint32_t timeout,
    event_flags_t *setFlags )
{
    osa_status_t status;
  
    status = OSA_EventWait(
        &hostInterface_okConfirmEvent, flagsToWait, false, timeout, setFlags );

    return status;
}

// Clears the host interface events.
static osa_status_t HostInterface_EventClear( event_flags_t flagsToClear )
{
    osa_status_t status;
  
    status = OSA_EventClear( &hostInterface_okConfirmEvent, flagsToClear );

    return status;
}

// Sets the host interface events.
static osa_status_t HostInterface_EventSet( event_flags_t flagsToSet )
{
    osa_status_t status;
  
    status = OSA_EventSet( &hostInterface_okConfirmEvent, flagsToSet );

    return status;
}

////////////////////////////////////////////////////////////////////////////////
// Global function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Initialises host interface events.
osa_status_t HostInterface_EventsInit()
{
    osa_status_t status;
  
    status = OSA_EventCreate( &hostInterface_okConfirmEvent, kEventAutoClear );

    return status;
}

// Sets the confirm packet event.
osa_status_t HostInterface_EventConfirmPacketSet()
{
    return HostInterface_EventSet( gHostInterface_eventConfirmPacketMask );
}

// Waits for the confirm packet event.
osa_status_t HostInterface_EventConfirmPacketWait()
{
    event_flags_t setFlags;

    return HostInterface_EventWait(
        gHostInterface_eventConfirmPacketMask,
        gHostInterface_retransmitTimeout,
        &setFlags );
}

// Clears the confirm packet event.
osa_status_t HostInterface_EventConfirmPacketClear()
{
    return HostInterface_EventClear( gHostInterface_eventConfirmPacketMask );
}

// Sets the send OK packet event.
osa_status_t HostInterface_EventSendOkPacketSet()
{
    return HostInterface_EventSet( gHostInterface_eventSendOkPacketMask );
}

// Waits for the send OK packet event.
osa_status_t HostInterface_EventSendOkPacketWait()
{
    event_flags_t setFlags;

    return HostInterface_EventWait(
        gHostInterface_eventSendOkPacketMask,
        OSA_WAIT_FOREVER,
        &setFlags );
}
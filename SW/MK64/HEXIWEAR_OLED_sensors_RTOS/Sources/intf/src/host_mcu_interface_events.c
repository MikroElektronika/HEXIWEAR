/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include <stdint.h>
#include <stddef.h>
#include "board.h"
#include "host_mcu_interface.h"
#include "fsl_interrupt_manager.h"

const event_flags_t
  gHostInterface_eventSendOkPacketMask     = 1 << 1,
  gHostInterface_eventConfirmPacketMask    = 1 << 2,
  gHostInterface_eventConfirmAttPacketMask = 1 << 3;

/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/

static event_t
  hostInterface_okConfirmEvent;

/*! *********************************************************************************
*************************************************************************************
* Private prototypes
*************************************************************************************
********************************************************************************** */

/*! *********************************************************************************
*************************************************************************************
* Functions definitions
*************************************************************************************
********************************************************************************** */

/**
 *    This function creates event object which will be used to wait for confirmation
 *    (OK packet) for previously sent packet.
 *
 *    @return  OSA status
 */

osa_status_t HostInterface_EventsInit()
{
  osa_status_t
    status = OSA_EventCreate(&hostInterface_okConfirmEvent, kEventAutoClear);

  return (osa_status_t)status;
}

/**
 * intern functions
 */

static osa_status_t HostInterface_EventWait (
                                               event_flags_t flagsToWait,
                                                    uint32_t timeout,
                                              event_flags_t* setFlags
                                            )
{
  osa_status_t
    status = OSA_EventWait(&hostInterface_okConfirmEvent, flagsToWait, false, timeout, setFlags);

  return (osa_status_t)status;
}

static osa_status_t HostInterface_EventClear(
                                              event_flags_t flagsToClear
                                            )
{
  osa_status_t
    status = OSA_EventClear(&hostInterface_okConfirmEvent, flagsToClear);

  return (osa_status_t)status;
}

static osa_status_t HostInterface_EventSet(
                                            event_flags_t flagsToSet
                                          )
{
  osa_status_t
    status = OSA_EventSet(&hostInterface_okConfirmEvent, flagsToSet);

  return (osa_status_t)status;
}

/**
 * set the event ""confirm the packet arrived""
 * @return  event status
 */
osa_status_t HostInterface_EventConfirmPacketSet()
{
  return HostInterface_EventSet(gHostInterface_eventConfirmPacketMask);
}

/**
 * wait for the event ""confirm the packet arrived""
 * @return  event status
 */
osa_status_t HostInterface_EventConfirmPacketWait()
{
  event_flags_t
    setFlags;

  return HostInterface_EventWait(
                                  gHostInterface_eventConfirmPacketMask,
                                  gHostInterface_retransmitTimeout,
                                  &setFlags
                                );
}

/**
 * clear the event "confirm the packet arrived"
 * @return  event status
 */
osa_status_t HostInterface_EventConfirmPacketClear()
{
  return HostInterface_EventClear(gHostInterface_eventConfirmPacketMask);
}

/**
 * set the event "send OK packet"
 * @return  event status
 */
osa_status_t HostInterface_EventSendOkPacketSet()
{
  return HostInterface_EventSet(gHostInterface_eventSendOkPacketMask);
}

/**
 * wait for the event "send OK packet"
 * @return  event status
 */
osa_status_t HostInterface_EventSendOkPacketWait()
{
  event_flags_t
    setFlags;

  return HostInterface_EventWait(
                                  gHostInterface_eventSendOkPacketMask,
                                  OSA_WAIT_FOREVER,
                                  &setFlags
                                );
}

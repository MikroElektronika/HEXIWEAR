/**
 * \file host_mcu_interface_events.c
 * \version 1.00
 * \brief this file contains MCU-to-MCU interface events
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * Neither the name of NXP, nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * visit: http://www.mikroe.com and http://www.nxp.com
 *
 * get support at: http://www.mikroe.com/forum and https://community.nxp.com
 *
 * Project HEXIWEAR, 2015
 */

/** include */
#include <stdint.h>
#include <stddef.h>
#include "board.h"
#include "host_mcu_interface.h"
#include "fsl_interrupt_manager.h"

/** global constants declarations */
const event_flags_t
  gHostInterface_eventSendOkPacketMask     = 1 << 1,
  gHostInterface_eventConfirmPacketMask    = 1 << 2,
  gHostInterface_eventConfirmAttPacketMask = 1 << 3;

/** private variables declarations */
static event_t
  hostInterface_okConfirmEvent;

/** private prototypes */
/** functions definitions */

/**
 * This function creates event object which will be used to wait for confirmation
 * (OK packet) for previously sent packet
 * @return status flag
 */
osa_status_t HostInterface_EventsInit()
{
  osa_status_t
    status = OSA_EventCreate( &hostInterface_okConfirmEvent, kEventAutoClear );

  return (osa_status_t)status;
}

/** private API */

/**
 * wait for the OK packet reception event
 * @param  flagsToWait event flags
 * @param  timeout     timeout value
 * @param  setFlags    flags to check for
 * @return             status flag
 */
static osa_status_t HostInterface_EventWait (
                                               event_flags_t flagsToWait,
                                                    uint32_t timeout,
                                              event_flags_t* setFlags
                                            )
{
  osa_status_t
    status = OSA_EventWait( &hostInterface_okConfirmEvent, flagsToWait, false, timeout, setFlags );

  return (osa_status_t)status;
}

/**
 * clear the event for OK packet confirmation
 * @param  flagsToClear flags to clear
 * @return              status flag
 */
static osa_status_t HostInterface_EventClear( event_flags_t flagsToClear )
{
  osa_status_t
    status = OSA_EventClear(&hostInterface_okConfirmEvent, flagsToClear);

  return (osa_status_t)status;
}

/**
 * set the event for OK packet confirmation
 * @param  flagsToSet flags to set
 * @return            status flag
 */
static osa_status_t HostInterface_EventSet( event_flags_t flagsToSet )
{
  osa_status_t
    status = OSA_EventSet(&hostInterface_okConfirmEvent, flagsToSet);

  return (osa_status_t)status;
}

/**
 * set the OK packet event, i.e. confirm that the packet arrived
 * @return  status flag
 */
osa_status_t HostInterface_EventConfirmPacketSet()
{
  return HostInterface_EventSet(gHostInterface_eventConfirmPacketMask);
}

/**
 * wait for the OK packet event
 * @return  status flag
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
 * clear the OK packet event
 * @return  status flag
 */
osa_status_t HostInterface_EventConfirmPacketClear()
{
  return HostInterface_EventClear(gHostInterface_eventConfirmPacketMask);
}

/**
 * set the "send OK packet" event
 * @return  status flag
 */
osa_status_t HostInterface_EventSendOkPacketSet()
{
  return HostInterface_EventSet(gHostInterface_eventSendOkPacketMask);
}

/**
 * wait for the event "send OK packet"
 * @return  status flag
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

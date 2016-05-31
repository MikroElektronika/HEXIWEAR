/**
 *    @file host_mcu_interface_events.c
 */

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include <stdint.h>
#include <stddef.h>
#include "EmbeddedTypes.h"
#include "fsl_osa_ext.h"
#include "board.h"
#include "fsl_lpuart_dma_driver.h"
#include "fsl_lpuart_driver.h"
#include "fsl_dma_driver.h"
#include "panic.h"
#include "debug.h"
#include "host_mcu_interface.h"
#include "fsl_interrupt_manager.h"

const event_flags_t gHostInterface_eventSendOkPacketMask     = 0x2; /**< Flag that trigger sending confirm packet of host.*/
const event_flags_t gHostInterface_eventConfirmPacketMask    = 0x4; /**< Flag about confirm packet received. */
const event_flags_t gHostInterface_eventConfirmAttPacketMask = 0x8; /**< Flag about confirm packet received. Used in Attribute Written proceudre. */

/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/

static event_t hostInterface_okConfirmEvent;

/************************************************************************************
*************************************************************************************
* Private prototypes
*************************************************************************************
********************************************************************************** */

/************************************************************************************
*************************************************************************************
* Functions definitions
*************************************************************************************
********************************************************************************** */

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    This function creates event object which will be used to wait for confirmation 
 *    (OK packet) for previously sent pakcet.
 *
 *    @return  status of OSA's functions
 */

osaStatus_t HostInterface_EventsInit(void)
{
    osa_status_t status;
    status = OSA_EventCreate(&hostInterface_okConfirmEvent, kEventAutoClear);
    
    return (osaStatus_t) status;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    This function waits for a combination of flags to be set in an event object.
 *
 *    @param    flagsToWait   Flags that to wait.
 *    @param    timeout       The maximum number of milliseconds to wait for the event.
 *    @param    setFlags      Flags that wakeup the waiting task are obtained by this parameter.
 *
 *    @return                 osaStatus_Success    Success
 *    @return                 osaStatus_Error      Failed
 *    @return                 osaStatus_Timeout    Timeout occurs while waiting
 */

osaStatus_t HostInterface_EventWait(event_flags_t flagsToWait, uint32_t timeout, event_flags_t *setFlags)
{
    osa_status_t status;
    
    status = OSA_EventWait(&hostInterface_okConfirmEvent, flagsToWait, false, timeout, setFlags);
    
    return (osaStatus_t) status;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Clears specified flags of an event object.
 *
 *    @param    flagsToClear   Flags to be clear.
 *
 *    @return                 osaStatus_Success    Success
 *    @return                 osaStatus_Error      Failed
 *    @return                 osaStatus_Timeout    Timeout occurs while waiting
 */

osaStatus_t HostInterface_EventClear(event_flags_t flagsToClear)
{
    osa_status_t status;
    
    status = OSA_EventClear(&hostInterface_okConfirmEvent, flagsToClear);
    
    return (osaStatus_t) status;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Sets specified flags of an event object.
 *
 *    @param    flagsToSet   Flags to be set.
 *
 *    @return                 osaStatus_Success    Success
 *    @return                 osaStatus_Error      Failed
 *    @return                 osaStatus_Timeout    Timeout occurs while waiting
 */

osaStatus_t HostInterface_EventSet(event_flags_t flagsToSet)
{
    osa_status_t status;
    status = OSA_EventSet(&hostInterface_okConfirmEvent, flagsToSet);
    
    return (osaStatus_t) status;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Set flag about confirm packet received.
 *
 *    @return                 osaStatus_Success    Success
 *    @return                 osaStatus_Error      Failed
 *    @return                 osaStatus_Timeout    Timeout occurs while waiting
 */

osaStatus_t HostInterface_EventConfirmPacketSet(void)
{
    return HostInterface_EventSet(gHostInterface_eventConfirmPacketMask);
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Wait for confirm packet to be received.
 *
 *    @return                 osaStatus_Success    Success
 *    @return                 osaStatus_Error      Failed
 *    @return                 osaStatus_Timeout    Timeout occurs while waiting
 */

osaStatus_t HostInterface_EventConfirmPacketWait(void)
{
    event_flags_t setFlags;
    return HostInterface_EventWait(gHostInterface_eventConfirmPacketMask, gHostInterface_retransmitTimeout, &setFlags);
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Clear flag about confirm packet received.
 *
 *    @return                 osaStatus_Success    Success
 *    @return                 osaStatus_Error      Failed
 *    @return                 osaStatus_Timeout    Timeout occurs while waiting
 */

osaStatus_t HostInterface_EventConfirmPacketClear(void)
{
    return HostInterface_EventClear(gHostInterface_eventConfirmPacketMask);
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Set flag about confirm packet received (used for Attribute Written operation).
 *
 *    @return                 osaStatus_Success    Success
 *    @return                 osaStatus_Error      Failed
 *    @return                 osaStatus_Timeout    Timeout occurs while waiting
 */

osaStatus_t HostInterface_EventConfirmAttPacketSet(void)
{
    return HostInterface_EventSet(gHostInterface_eventConfirmAttPacketMask);
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Wait for confirm packet to be received (used for Attribute Written operation).
 *
 *    @return                 osaStatus_Success    Success
 *    @return                 osaStatus_Error      Failed
 *    @return                 osaStatus_Timeout    Timeout occurs while waiting
 */

osaStatus_t HostInterface_EventConfirmAttPacketWait(void)
{
    event_flags_t setFlags;
    return HostInterface_EventWait(gHostInterface_eventConfirmAttPacketMask, 
                                   gHostInterface_retransmitCount * gHostInterface_retransmitTimeout, &setFlags);
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Clear flag about confirm packet received (used for Attribute Written operation).
 *
 *    @return                 osaStatus_Success    Success
 *    @return                 osaStatus_Error      Failed
 *    @return                 osaStatus_Timeout    Timeout occurs while waiting
 */

osaStatus_t HostInterface_EventConfirmAttPacketClear(void)
{
    return HostInterface_EventClear(gHostInterface_eventConfirmAttPacketMask);
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Trigger event for start sending confirm pakcet.
 *
 *    @return                 osaStatus_Success    Success
 *    @return                 osaStatus_Error      Failed
 *    @return                 osaStatus_Timeout    Timeout occurs while waiting
 */

osaStatus_t HostInterface_EventSendOkPacketSet(void)
{
    return HostInterface_EventSet(gHostInterface_eventSendOkPacketMask);
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Wait for start sending confirm pakcet.
 *
 *    @return                 osaStatus_Success    Success
 *    @return                 osaStatus_Error      Failed
 *    @return                 osaStatus_Timeout    Timeout occurs while waiting
 */

osaStatus_t HostInterface_EventSendOkPacketWait(void)
{
    event_flags_t setFlags;
    return HostInterface_EventWait(gHostInterface_eventSendOkPacketMask, OSA_WAIT_FOREVER, &setFlags);
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

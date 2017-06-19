/**
 *    @file host_mcu_interface_tx.c
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
#include "PWR_Interface.h" 

#include "app.h" 

/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/

static hostInterface_packet_t   hostInterface_txPacket;           /** Tx host interface packet. */
static msg_queue_handler_t      hostInterface_txQueueHnd;         /** Tx queue handler. */
static task_handler_t           gHostInterface_TxTaskId;          /** Tx task ID. */
static task_handler_t           gHostInterface_OkTaskId;          /** Ok task ID. */
static mutex_t                  uartTxAccessMutex;

// Declare the message queue
MSG_QUEUE_DECLARE(hostInterface_txQueue, gHostInterface_msgNum, 0);	

/**
 *    Definition of confirmation packet.
 */

static hostInterface_packet_t   hostInterface_okPacket = {
    .start1 = 0x55,
    .start2 = 0xAA, 
    .type   = packetType_OK,
    .length = 0,
    .data[0] = gHostInterface_trailerByte
};

/************************************************************************************
*************************************************************************************
* Private prototypes
*************************************************************************************
********************************************************************************** */

static osaStatus_t HostInterface_TxQueueMsgGet(hostInterface_packet_t * pHostInterface_packet);
static void        HostInterface_FlushPacket(hostInterface_packet_t * pHostInterface_packet);
static void        HostInterface_TxTask(task_param_t param);
static void        HostInterface_OkTask(task_param_t param);
static void        HostInterface_ConfirmWaitHandler(void);

/************************************************************************************
*************************************************************************************
* Functions definitions
*************************************************************************************
********************************************************************************** */

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    This function initialize Tx queue and create corresponding task.
 *
 *
 *    @return                          osaStatus_Success  
 *                                     osaStatus_Error    
 */

osaStatus_t HostInterface_TxInit(void)
{
    osa_status_t status;
    
    status = OSA_MutexCreate(&uartTxAccessMutex);
    if( kStatus_OSA_Success != status )
    {
        panic(0,0,0,0);
    } 
        
    // Create Tx Message Queue
    hostInterface_txQueueHnd = OSA_MsgQCreate(hostInterface_txQueue, gHostInterface_msgNum, sizeof(hostInterface_packet_t) / 4);
    if(hostInterface_txQueueHnd == 0)
    {
        return osaStatus_Error;
    }
    
    // Create Tx Task
    status = OSA_TaskCreate(HostInterface_TxTask, "HostInterface_TxTask", gHostInterfaceTxTaskStackSize_c, 0,
                            gHostInterfaceTxPriority_c, (task_param_t)NULL, FALSE, &gHostInterface_TxTaskId); 
    if( kStatus_OSA_Success != status )
    {
        panic(0,0,0,0);
    } 
    
    // Create Tx Task
    status = OSA_TaskCreate(HostInterface_OkTask, "HostInterface_OkTask", gHostInterfaceOkTaskStackSize_c, 0,
                            gHostInterfaceOkPriority_c, (task_param_t)NULL, FALSE, &gHostInterface_OkTaskId); 
    if( kStatus_OSA_Success != status )
    {
        panic(0,0,0,0);
    } 
        
    return (osaStatus_t) status;
}
    
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    This function puts a message to the end of the Tx message queue.
 *
 *    @param    pHostInterface_packet   Packet that will be placed into Tx message queue.
 *
 *    @return                          osaStatus_Success  Message successfully put into the queue.
 *                                     osaStatus_Error    Process fail.
 */

osaStatus_t HostInterface_TxQueueMsgPut(hostInterface_packet_t * pHostInterface_packet, bool confirmationReq)
{
    osa_status_t status;
    
    pHostInterface_packet->start1  = gHostInterface_startByte1;
    pHostInterface_packet->start2  = gHostInterface_startByte2;
                    
    if(confirmationReq)
    {
        pHostInterface_packet->start2 |= 1;
    }
    
    status = OSA_MsgQPut(hostInterface_txQueueHnd, (hostInterface_packet_t *)pHostInterface_packet);
    if(status == kStatus_OSA_Error)
    {
        //panic(0,0,0,0);
    }
    
    return (osaStatus_t) status;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    This function gets a message from the head of the Tx message queue.
 *
 *    @param    pHostInterface_packet   Pointer to a memory to save the packet.
 *
 *    @return                          osaStatus_Success  Message successfully obtained from the queue.
 *                                     osaStatus_Error    Process fail.
 */

static osaStatus_t HostInterface_TxQueueMsgGet(hostInterface_packet_t * pHostInterface_packet)
{
    osa_status_t status;
    
    status = OSA_MsgQGet(hostInterface_txQueueHnd, (hostInterface_packet_t *)pHostInterface_packet, OSA_WAIT_FOREVER);
    if(status == kStatus_OSA_Error)
    {
        panic(0,0,0,0);
    }
    return (osaStatus_t) status;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Host MCU Interface Tx task.
 *
 *    @param   param   initialData
 */

static void HostInterface_TxTask(task_param_t param)
{
    osaStatus_t status;
    
    while(1)
    {   
        // Wait for outgoing packets. 
        status = HostInterface_TxQueueMsgGet(&hostInterface_txPacket);
        if(status == osaStatus_Success)
        {
            // Send packet.
            HostInterface_FlushPacket(&hostInterface_txPacket);  
            
#if gHostInterface_RxConfirmationEnable //..........................................
            if(hostInterface_txPacket.start2 & 1)
            {
                HostInterface_EventConfirmPacketClear();
                HostInterface_EventConfirmAttPacketClear();
                // Wait for confirmation.
                HostInterface_ConfirmWaitHandler();
            }
#endif //...........................................................................

        }   
    }
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Host MCU Interface Tx task.
 *
 *    @param   param   initialData
 */
//extern gpio_output_pin_user_config_t gpioPin;
static void HostInterface_OkTask(task_param_t param)
{
    osaStatus_t status;
    
    while(1)
    {
        status = HostInterface_EventSendOkPacketWait();
        if(status == osaStatus_Success)
        {
            HostInterface_FlushPacket(&hostInterface_okPacket);  
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    This function handle confirmation wait-timeout. If timeout ocures, function resend
 *    previously pakcet again (max "gHostInterface_retransmitCount" times).
 *
 */

static void HostInterface_ConfirmWaitHandler(void)
{
    char retransmitCnt;
    
    for(retransmitCnt = 0; retransmitCnt < gHostInterface_retransmitCount; retransmitCnt++)
    {   
        if(HostInterface_EventConfirmPacketWait() == osaStatus_Timeout)
        {
            HostInterface_FlushPacket(&hostInterface_txPacket);
        }
        else 
        {
            break;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Send packet through UART.
 *
 *    @param   pHostInterface_packet   Packet to be sent.
 */

static void HostInterface_FlushPacket(hostInterface_packet_t * pHostInterface_packet)
{
    osa_status_t status;
    
    status = OSA_MutexLock(&uartTxAccessMutex, OSA_WAIT_FOREVER);
    if(status == kStatus_OSA_Success)
    {   
        LPUART_DRV_SendDataBlocking(gHostInterface_instance, (uint8_t *)pHostInterface_packet, pHostInterface_packet->length + gHostInterface_headerSize + 1, OSA_WAIT_FOREVER);
        OSA_MutexUnlock(&uartTxAccessMutex);
    }    
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

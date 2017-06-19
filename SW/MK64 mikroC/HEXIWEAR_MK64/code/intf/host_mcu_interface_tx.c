// File: host_mcu_interface_tx.c

// Definitions of tx functionalities of the MCU interface module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <stddef.h>

#include "HEXIWEAR_info.h"

#include "host_mcu_interface.h"
#include "host_mcu_interface_defs.h"

#include "error.h"
#include "error_types.h"

#include "power_driver.h"

////////////////////////////////////////////////////////////////////////////////
// Static variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

static hostInterface_packet_t hostInterface_txPacket;
static msg_queue_handler_t hostInterface_txQueueHnd;
static mutex_t uartTxAccessMutex;
static semaphore_t uartTxSyncSema;

static hostInterface_packet_t hostInterface_okPacket =
{
    0x55,                       // .start1
    0xAA,                       // .start2
    packetType_OK,              // .type
    0,                          // .length
    gHostInterface_trailerByte  // .data[0]
};

// Message queues.
msg_queue_t *hostInterface_txQueue = NULL;

uint8_t *txBuffer;
uint8_t txSize;

////////////////////////////////////////////////////////////////////////////////
// Static function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Gets a message from the tx queue.
static osa_status_t HostInterface_TxQueueMsgGet(
    hostInterface_packet_t* pHostInterface_packet )
{
    osa_status_t status;
  
    status = OSA_MsgQGet(
        hostInterface_txQueueHnd, pHostInterface_packet, OSA_WAIT_FOREVER );

    if( status == kStatus_OSA_Error )
    {
        error_catch(2);
    }

    return status;
}

// Flushes a packet to the MKW40.
static void HostInterface_FlushPacket(
    hostInterface_packet_t *pHostInterface_packet )
{
    osa_status_t status;
  
    status = OSA_MutexLock( &uartTxAccessMutex, OSA_WAIT_FOREVER );

    if( status == kStatus_OSA_Success )
    {
        txBuffer = ( uint8_t* )pHostInterface_packet;
        txSize = 4 + pHostInterface_packet->length + 1;
        TIE_UART4_C2_bit = 1;
        
        do
        {
            status = OSA_SemaWait( &uartTxSyncSema, UART_TIMEOUT );
        } while( status == kStatus_OSA_Idle );
        
        if( status != kStatus_OSA_Success )
        {
            TIE_UART4_C2_bit = 0;
        }
        
        while( UART4_TCFIFO != 0 ) {}
        
//        while( ( txSize-- ) > 0 )
//        {
//            UART4_Write( *( txBuffer++ ) );
//        }
    }

    OSA_MutexUnlock( &uartTxAccessMutex );
}

// Flushes a number of packets indicated by the retransmit count.
static void HostInterface_ConfirmWaitHandler()
{
    uint8_t retransmitCnt;
    
    for( retransmitCnt = 0; retransmitCnt < gHostInterface_retransmitCount;
        retransmitCnt++ )
    {
        if( HostInterface_EventConfirmPacketWait() == kStatus_OSA_Timeout )
        {
            HostInterface_FlushPacket( &hostInterface_txPacket );
        }

        else
        {
            break;
        }
    }
}

// Host interface tx task.
// Pushes the received data packet through the selected comm packet.
static void HostInterface_TxTask( task_param_t param )
{
    osa_status_t status;
            
    while( 1 )
    {
        status = HostInterface_TxQueueMsgGet( &hostInterface_txPacket );

        if( status == kStatus_OSA_Success )
        {
            if( hostInterface_txPacket.type == packetType_accel )
                TOGGLE_PROBE();
                        
            HostInterface_FlushPacket( &hostInterface_txPacket );

#if gHostInterface_RxConfirmationEnable
            if( ( hostInterface_txPacket.start2 & 0x01 ) == 1 )
            {
                HostInterface_EventConfirmPacketClear();
                HostInterface_ConfirmWaitHandler();
            }
#endif

            // If the current mode is sensor tag sleep mode,
            // go to sleep upon finishing the data packet exchange.
            switch ( power_GetCurrentMode() )
            {
                case POWER_CURRENT_MODE_NORMAL:
                    power_TurnScreenON();
                    break;

                case POWER_CURRENT_MODE_SLEEP_SENSOR_TAG:
                    power_SetSleepSource( POWER_SLEEP_SRC_SENSOR_TAG );
                    power_GoToSleep();
                    break;

                default:
                    // For other power modes, do nothing.
                    break;
            }
        }
    }
}

// Host interface OK task.
// Flushes the send OK packets to the MKW40.
static void HostInterface_OkTask( task_param_t param )
{
    osa_status_t status;
      
    while( 1 )
    {
        status = HostInterface_EventSendOkPacketWait();

        if( status == kStatus_OSA_Success )
        {
            HostInterface_FlushPacket( &hostInterface_okPacket );
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
// Global function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Initialises host interface tx.
osa_status_t HostInterface_TxInit()
{
    osa_status_t status;
    
    OSA_SemaCreate( &uartTxSyncSema, 0 );
    
    status = OSA_MutexCreate( &uartTxAccessMutex );
    
    if( status != kStatus_OSA_Success )
        error_catch( CATCH_QUEUE );
        
        

    // Create TX message queue.
    hostInterface_txQueueHnd = OSA_MsgQCreate (
        hostInterface_txQueue,
        gHostInterface_msgNum,
        sizeof( hostInterface_packet_t ) / sizeof( uint32_t ) );

    if( hostInterface_txQueueHnd == NULL )
    {
        return kStatus_OSA_Error;
    }
    
    // Create tx-data task.
    status = OSA_TaskCreate(
                             HostInterface_TxTask,
                             "HostInterface_TxTask",
                             gHostInterfaceTxTaskStackSize_c,
                             NULL,
                             gHostInterfaceTxPriority_c,
                             NULL,
                             false,
                             &hexiwear_intf_TX_handler
                           );

    if( status != kStatus_OSA_Success )
    {
        error_catch( CATCH_TASK );
    }
    
    // Create tx-OK task.
    status = OSA_TaskCreate(
                             HostInterface_OkTask,
                             "HostInterface_OkTask",
                             gHostInterfaceOkTaskStackSize_c,
                             NULL,
                             gHostInterfaceOkPriority_c,
                             NULL,
                             false,
                             &hexiwear_intf_OK_handler
                           );

    if( status != kStatus_OSA_Success )
    {
        error_catch( CATCH_TASK );
    }
    
    return status;
}

// Puts a message to the tx queue.
osa_status_t HostInterface_TxQueueMsgPut(
    hostInterface_packet_t *pHostInterface_packet,
                      bool  confirmationReq )
{
    BaseType_t status;

    pHostInterface_packet->start1 = gHostInterface_startByte1;
    pHostInterface_packet->start2 = gHostInterface_startByte2;
    
    if( confirmationReq == true )
        pHostInterface_packet->start2 |= 1;

    status = xQueueSendToBack(
        hostInterface_txQueueHnd, pHostInterface_packet, OSA_WAIT_FOREVER );

    if( status != pdPASS )
        return kStatus_OSA_Error;

    return kStatus_OSA_Success;
}

// Host interface rx callback.
void HostInterface_TxCallback()
{
    uint8_t tmp;
    uint8_t emptyEntryCount;
    
    emptyEntryCount = txSize - UART4_TCFIFO;
    
    while( emptyEntryCount-- )
    {
        while( TDRE_UART4_S1_bit == 0 ) {}
        tmp = UART4_S1;
        tmp++;
        UART4_D = *txBuffer;
        
        txBuffer++;
        txSize--;
        
        if( txSize == 0 )
        {
            TIE_UART4_C2_bit = 0;
            OSA_SemaPost( &uartTxSyncSema );
            break;
        }
    }
}
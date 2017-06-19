/*! *********************************************************************************
 * \defgroup CONTROLLER
 * @{
 ********************************************************************************** */
/*!
* Copyright (c) 2014, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file ble_controller_task.c
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*
* o Redistributions of source code must retain the above copyright notice, this list
*   of conditions and the following disclaimer.
*
* o Redistributions in binary form must reproduce the above copyright notice, this
*   list of conditions and the following disclaimer in the documentation and/or
*   other materials provided with the distribution.
*
* o Neither the name of Freescale Semiconductor, Inc. nor the names of its
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
*/

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include "EmbeddedTypes.h"
#include "Messaging.h"
#include "fsl_osa_ext.h"
#include "fsl_os_abstraction.h"
#include "fsl_device_registers.h"
#include "ble_controller_task_config.h"
#include "panic.h"
#include "controller_interface.h"
/************************************************************************************
*************************************************************************************
* Public constants & macros
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Public memory declarations
*************************************************************************************
************************************************************************************/
task_handler_t  gControllerTaskId;
osaEventId_t mControllerTaskEvent;
msgQueue_t   controllerTaskQueue;
osaSemaphoreId_t gHciDataBufferingSem;
/************************************************************************************
*************************************************************************************
* Private prototypes
*************************************************************************************
************************************************************************************/
static void ControllerTask(task_param_t argument);

extern void Controller_TaskHandler(void * args);
extern void Controller_InterruptHandler(void);
/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/
OSA_TASK_DEFINE(CTRLR, gControllerTaskStackSize_c);

/* Public Device Address */
uint8_t gBDAddress_c[6] = {BD_ADDR};
/* Time between the beginning of two consecutive advertising PDU's */
const uint8_t gAdvertisingPacketInterval_c = mcAdvertisingPacketInterval_c;
/* Advertising channels that are enabled for scanning operation. */
const uint8_t gScanChannelMap_c = mcScanChannelMap_c;
/* Advertising channels that are enabled for initiator scanning operation. */
const uint8_t gInitiatorChannelMap_c = mcInitiatorChannelMap_c;
/* Offset to the first instant register */
const uint16_t gOffsetToFirstInstant_c = mcOffsetToFirstInstant_c;

/************************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
************************************************************************************/

static void ControllerTask(task_param_t argument)
{
    Controller_TaskHandler((void *) NULL);    
}

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/
/**
 * \fn 		Controller_TaskInit 
 * \brief   This Function
 * \return  osa_status_t
 */
osaStatus_t Controller_TaskInit(void)
{	  
    osa_status_t status;
    
    /* Initialization of task related objects */
    if(gControllerTaskId)
    {      
      return osaStatus_Error;
    }

    mControllerTaskEvent = OSA_EXT_EventCreate(TRUE);

    if(NULL == mControllerTaskEvent)
    {
        return osaStatus_Error;
    }
            
    gHciDataBufferingSem = OSA_EXT_SemaphoreCreate(0);    
    if (gHciDataBufferingSem == NULL)
    {
        return osaStatus_Error;
    }        
    
    /* Task creation */
    status = OSA_TaskCreate(ControllerTask, "CTRLR_Task", gControllerTaskStackSize_c, CTRLR_stack,
                            gControllerTaskPriority_c, (task_param_t)NULL, FALSE, &gControllerTaskId);
    if( kStatus_OSA_Success != status )
    {
        panic(0,0,0,0);
        return osaStatus_Error;
    }

    OSA_InstallIntHandler(BTLL_RSIM_IRQn, &Controller_InterruptHandler);
  
    NVIC_ClearPendingIRQ(BTLL_RSIM_IRQn);
    NVIC_EnableIRQ(BTLL_RSIM_IRQn);
    NVIC_SetPriority(BTLL_RSIM_IRQn, 0xC0);
    
    MSG_InitQueue ( &controllerTaskQueue );   
    
    /* Set Default Tx Power Level */
    Controller_SetTxPowerLevel(mAdvertisingDefaultTxPower_c, gAdvTxChannel_c);
    Controller_SetTxPowerLevel(mConnectionDefaultTxPower_c, gConnTxChannel_c);
          
    return osaStatus_Success;
}

/*! *********************************************************************************
* @}
********************************************************************************** */

/**
 *    @file tsi.c
 */


/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include "tsi.h"
#include "TimersManager.h"
#include "EmbeddedTypes.h"
#include "board.h"
#include "fsl_os_abstraction.h"
#include "fsl_osa_ext.h"
#include "fsl_tsi_driver.h"
#include "panic.h"
#include "debug.h"
#include "host_mcu_interface.h"
#include "Flash_Adapter.h"
#include "fsl_gpio_driver.h"
#include "ft_setup.h"
#include "fsl_pit_driver.h"

#include "app.h"

static hostInterface_packet_t tsiHostInterface_packet = 
{
    .length = 0,
    .data[0] = gHostInterface_trailerByte,
};

static task_handler_t     tsiTaskId;
static tmrTimerID_t       tsiTimerId;
static uint8_t            tsiFtMemoryPool[1500];
static tsiGroup_select_t  tsiGroupActive;

static mutex_t tsiMutex;

static msg_queue_handler_t tsiQueueHnd;
MSG_QUEUE_DECLARE(tsiQueue, 1, 1);

/************************************************************************************
*************************************************************************************
* Private prototypes
*************************************************************************************
********************************************************************************** */

static void            TouchSense_KeypadCallback(const struct ft_control *control, enum ft_control_keypad_event event, uint32_t index);
static void            TouchSense_Task(task_param_t param);
static osaStatus_t 	   TouchSense_TaskInit(void);
extern void 		   TSI_DRV_IRQHandler(uint32_t instance);    
static void            TsiTimerCallback(void * pParam);

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
********************************************************************************** */

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Return current active group of electrodes.
 *
 *    @return      tsiGroup_select_left
 *    @return      tsiGroup_select_right
 */

tsiGroup_select_t TouchSense_GetActiveGroup(void) 
{
    return tsiGroupActive;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Enables corresponding electrodes based on given electrodes-group.
 *
 *    @param   tsiGroup   Electrodes group to be enabled.
 */

void TouchSense_EnableElectrode(tsiGroup_select_t tsiGroup) 
{    
    tsiGroupActive = tsiGroup;
    
    TouchSense_MutexLock(OSA_WAIT_FOREVER);
    
    TSI_DRV_AbortMeasure(0);
    
    if(tsiGroupActive == tsiGroup_select_left) 
    {
        ft_electrode_disable(&electrode_rightUp);
        ft_electrode_disable(&electrode_rightDown);
        
        ft_electrode_enable(&electrode_leftUp, 0);
        ft_electrode_enable(&electrode_leftDown, 0);
    }
    else
    {
        ft_electrode_disable(&electrode_leftUp);
        ft_electrode_disable(&electrode_leftDown);
        
        ft_electrode_enable(&electrode_rightUp, 0);
        ft_electrode_enable(&electrode_rightDown, 0);
    }
    TouchSense_MutexUnlock();
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Function called from other tasks to set current active group of electrodes.
 *
 *    @param   tsiGroup   Group of electrodes to be set.
 */

void TouchSense_SetActiveGroup(tsiGroup_select_t tsiGroup) 
{
    osa_status_t status;
    uint32_t tmpTsiGroup;
    
    tmpTsiGroup = (uint32_t) tsiGroup;
    
    status = OSA_MsgQPut(tsiQueueHnd, (uint32_t *)&tmpTsiGroup);
    if(status == kStatus_OSA_Error)
    {
        panic(0,0,0,0);
    }
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Initialize module, and creates the TouchSense's task.
 */

void TouchSense_Init(void)
{   
    int32_t result;
    uint32_t     cnt;
    tsiGroup_select_t tsiGroup;
    osa_status_t status;

    status = OSA_MutexCreate(&tsiMutex);
    
    tsiQueueHnd = OSA_MsgQCreate(tsiQueue, 1, 1);
    if(tsiQueueHnd == 0)
    {
        panic(0,0,0,0);
    }
    
    if ((result = ft_init(&system_0, tsiFtMemoryPool, sizeof(tsiFtMemoryPool))) != FT_SUCCESS)
    {
        switch(result)
        {
            case FT_FAILURE:
              
              break;
            case FT_OUT_OF_MEMORY:
              
              break;
        }
        while(1); /* add code to handle this error */
    }
    
    // Get device parameters from FLASH.
    NV_ReadHWParameters(&gHardwareParameters);
    
    // Read current active group of electrodes from FLASH.
    if(gHardwareParameters.tsiGroupActive == 0xFF)       
    {
        // Not written yet to FLASH. Set default.
        tsiGroup = tsiGroup_select_right;
    }
    else
    {
        tsiGroup = (tsiGroup_select_t) gHardwareParameters.tsiGroupActive;
    }

    // Set corresponding group of electrodes.
    TouchSense_EnableElectrode(tsiGroup);
    
    // Create Touch Sense task.
    TouchSense_TaskInit();
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Lock tsi driver mutex.
 *
 *    @param    timeout   The maximum number of milliseconds to wait for the mutex.
 *
 *    @return             kStatus_OSA_Success   The mutex is locked successfully.
 *    @return             kStatus_OSA_Timeout   Timeout occurred.
 *    @return             kStatus_OSA_Error     Incorrect parameter was passed.
 */

osa_status_t TouchSense_MutexLock(uint32_t timeout)
{
    return OSA_MutexLock(&tsiMutex, timeout);
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Unlock tsi driver mutex.
 */

void TouchSense_MutexUnlock(void)
{
    OSA_MutexUnlock(&tsiMutex);
}

/*! *********************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
********************************************************************************** */

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Function waits for message about setting a new active group of electrodes.
 *
 *    @param    tsiGroup   Active group of electrodes to be set.
 *    @param    timeout    The number of milliseconds to wait for a message.
 *
 *    @return              osaStatus_Success    Success
 *    @return              osaStatus_Error      Failed
 *    @return              osaStatus_Timeout    Timeout occurs while waiting
 */

static osaStatus_t TouchSense_QueueMsgGet(tsiGroup_select_t * tsiGroup, uint32_t timeout)
{
    osa_status_t status;
    uint32_t tmpTsiGroup;
    
    status = OSA_MsgQGet(tsiQueueHnd, (uint32_t *)&tmpTsiGroup, timeout);
    if(status == kStatus_OSA_Error)
    {
        panic(0,0,0,0);
    }
    *tsiGroup = (tsiGroup_select_t) tmpTsiGroup;
    return (osaStatus_t) status;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Keypad event callback function
 *
 *    @param   control   The main structure representing the control instance
 *    @param   event     Keypad event
 *    @param   index     Index of keypad
 */

static void TouchSense_KeypadCallback(const struct ft_control *control, enum ft_control_keypad_event event, uint32_t index)
{    
    static enum ft_control_keypad_event oldEvent = FT_KEYPAD_RELEASE;
    
    // Check if touch event detected.
    if(
       (event == FT_KEYPAD_TOUCH) &&
       (oldEvent == FT_KEYPAD_RELEASE)
       )
    {
    	// Set corresponding type of packet.
        switch (index) 
        {
            case 0:
            case 2:
                tsiHostInterface_packet.type = packetType_pressUp;
                break;
                
            case 1:
            case 3:
                tsiHostInterface_packet.type = packetType_pressDown;
                break;
                
            case 4:
                tsiHostInterface_packet.type = packetType_pressLeft;
                break;
            case 5:
                tsiHostInterface_packet.type = packetType_pressRight;
                break;
                
            default:
                return;
        }
        oldEvent = FT_KEYPAD_TOUCH;
        HostInterface_TxQueueMsgPut((hostInterface_packet_t *)&tsiHostInterface_packet, false);
    }
    else if(event == FT_KEYPAD_RELEASE)
    {
        oldEvent = FT_KEYPAD_RELEASE;
    }
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Tsi timer callback.
 *
 *    @param   pParam   
 */

static void TsiTimerCallback(void * pParam)
{
    if(TouchSense_MutexLock(0) == kStatus_OSA_Success)
    {
        ft_trigger();
        TouchSense_MutexUnlock();
    }
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Function Creates Touch Sense task.
 *
 *    @return      Status of creating procedure.
 */

static osaStatus_t TouchSense_TaskInit(void)
{       
    osa_status_t status;
    
    status = OSA_TaskCreate(TouchSense_Task, "TouchSense_Task", gTouchSenseTaskStackSize_c, 0,
                            gTouchSensePriority_c, (task_param_t)NULL, FALSE, &tsiTaskId); 
    if( kStatus_OSA_Success != status )
    {
        panic(0,0,0,0);
        return osaStatus_Error;
    }
    
    return osaStatus_Success;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Touch Sense task.
 *
 *    @param   param   initialData
 */

static void TouchSense_Task(task_param_t param)
{   
    tsiGroup_select_t tmpTsiGroup;
    
    // FT Initialization
    ft_electrode_enable(&electrode_left, 0);
    ft_electrode_enable(&electrode_right, 0);
    ft_control_enable(&keypad_0);
    ft_control_keypad_only_one_key_valid(&keypad_0, 0);
    ft_control_keypad_set_autorepeat_rate(&keypad_0, 0, 0);
    ft_control_keypad_register_callback(&keypad_0, &TouchSense_KeypadCallback);

    // Creating tsi timer.
    tsiTimerId = TMR_AllocateTimer();
    TMR_StartLowPowerTimer(tsiTimerId, gTmrLowPowerIntervalMillisTimer_c, TmrMilliseconds(10), TsiTimerCallback, NULL);
    
    while(1)
    {
    	// Check if there is message about setting active group of electrodes.
        if(TouchSense_QueueMsgGet(&tmpTsiGroup, 0) == osaStatus_Success)
        {
            TouchSense_EnableElectrode(tmpTsiGroup);
        }
        
        if(TouchSense_MutexLock(10) == kStatus_OSA_Success)   
        {
            ft_task(); // do FT task 
            TouchSense_MutexUnlock();
        }
        
        // Stay in the loop during sleep.
        do
        {
            OSA_TimeDelay(5);
        }
        while(BleApp_GetSleepFlag() == true);
    }
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Implementation of TSI0 handler named in startup code.
 */

void TSI0_IRQHandler(void)
{
    TSI_DRV_IRQHandler(0);
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


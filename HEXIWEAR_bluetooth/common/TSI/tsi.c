/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include "tsi.h"
#include "EmbeddedTypes.h"
#include "board.h"
#include "fsl_os_abstraction.h"
#include "fsl_osa_ext.h"
#include "fsl_tsi_driver.h"
#include "panic.h"
#include "debug.h"
#include "host_mcu_interface.h"

// Set up TSI configurations
static const tsi_config_t tsiHwConfig =
{
    .ps      = kTsiElecOscPrescaler_2div,         // Prescaler.
    .extchrg = kTsiExtOscChargeCurrent_8uA,       // Electrode charge current.
    .refchrg = kTsiRefOscChargeCurrent_4uA,       // Reference charge current.
    .nscn    = kTsiConsecutiveScansNumber_10time, // Number of scans. 
    .mode    = kTsiAnalogModeSel_Capacitive,      // TSI analog modes in a TSI instance.
    .dvolt   = kTsiOscVolRails_Dv_043,            // Oscillator's voltage rails.
    .thresh  = 100,                               // High byte of threshold. 
    .thresl  = 200,                               // Low byte of threshold. 
};

// User configuration structure for TSI driver.
const tsi_user_config_t tsiConfig =
{
    .config        = (tsi_config_t*)&tsiHwConfig,
    .pCallBackFunc = NULL,
    .usrData       = 0,
};

static hostInterface_packet_t tsiHostInterface_packet = 
{
    .start1 = gHostInterface_startByte1, 
    .start2 = gHostInterface_startByte2
};

static task_handler_t gTouchSenseTaskId;
static tsi_state_t myTsiState;

/*! *********************************************************************************
*************************************************************************************
* Private prototypes
*************************************************************************************
********************************************************************************** */

static void                TouchSense_Task(task_param_t param);
static osaStatus_t 	   TouchSense_TaskInit(void);
static tsiElec_activeCnt_t TouchSense_ElecActiveCntProcess(tsiElec_t *pElectrode);
static osaStatus_t         TouchSense_ElecCheckIsActive(tsiElec_t *pElectrode);
static void                TouchSense_MeasureHandler(void);
static hostInterface_packetType_t TouchSense_GetPacketType(tsiElecId_t id);

extern void 		   TSI_DRV_IRQHandler(uint32_t instance);    

/*! *********************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
********************************************************************************** */

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Initialize module, and creates the TouchSense's task.
 */

void TouchSense_Init(void)
{   
    tsi_status_t result;
    uint32_t     cnt;
    
    TouchSense_SliderInit(tsiSlider_select_right);
    
    // Driver initialization
    result = TSI_DRV_Init(TSI_INSTANCE, &myTsiState, &tsiConfig);
    if(result != kStatus_TSI_Success)
    {
        panic(0,0,0,0);
        return;
    }

    // Enable electrodes for normal mode
    for(cnt = 0; cnt <  TSI_ELECTRODE_CNT; cnt++)
    {
        TSI_DRV_EnableElectrode(TSI_INSTANCE, tsiElec_Array[cnt]->channel, true);
    }
    
    // Start measuring level in untouched state.
    while(TSI_DRV_MeasureBlocking(TSI_INSTANCE) != kStatus_TSI_Success)
    {
        DebugPrint("The measure of TSI failed.");
    }
    
    // Get the last measured values in the previous measure cycle.
    for(cnt = 0; cnt <  TSI_ELECTRODE_CNT; cnt++)
    {
        result = TSI_DRV_GetCounter(TSI_INSTANCE, tsiElec_Array[cnt]->channel, &tsiElec_Array[cnt]->untouchMeas);
        if(result != kStatus_TSI_Success)
        {
            panic(0,0,0,0);
            return;
        }
    }
    
    // Create Touch Sense task.
    TouchSense_TaskInit();
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
 *    Function Creates Touch Sense task.
 *
 *    @return      Status of creating procedure.
 */

static osaStatus_t TouchSense_TaskInit(void)
{       
    osa_status_t status;
    
    status = OSA_TaskCreate(TouchSense_Task, "TouchSense_Task", gTouchSenseTaskStackSize_c, 0,
                            gTouchSensePriority_c, (task_param_t)NULL, FALSE, &gTouchSenseTaskId); 
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
    tsi_status_t result;
    uint32_t     cnt;
    
    // Print a note
    DebugPrint("Touch Sense is ready.");
    
    while(1)
    {
        // Start measuring level in touched state.
        while(TSI_DRV_MeasureBlocking(TSI_INSTANCE) != kStatus_TSI_Success)
        {
            DebugPrint("The measure of TSI failed.");
        }
        
        // Check whether electrode state is active or idle.
        for(cnt = 0; cnt <  TSI_ELECTRODE_CNT; cnt++)
        {
            TouchSense_ElecCheckIsActive(tsiElec_Array[cnt]);
        }
            
        // Processing of obtained state of electrodes.
        TouchSense_MeasureHandler();
            
        // Sampling time.
        OSA_TimeDelay(20u);
    }
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    This function process measured values from slider electrodes.
 *
 */

static void TouchSense_MeasureHandler(void)
{
    uint32_t cnt;
    
    // Check whether both slider electrodes are pressed?
    if(tsiSlider.elecUp->isActive && tsiSlider.elecDown->isActive)
    {
        if( (tsiSlider.state == tsiSlider_state_down) &&                         // Check is slider already in "down" state.
            (tsiSlider.lastActiveElec->activeCnt < TSI_TOUCH_CNT_SLIDE_MAX)     // Ignore too slow scrool.
          )
        {
            tsiSlider.state = tsiSlider_state_slide;                            // Go to slide state.
            
            // Set slide speed.
            tsiSlider.speed = (tsiSlider.lastActiveElec->activeCnt - TSI_TOUCH_CNT_SLIDE_MIN) * TSI_SLIDE_SPEED_MAX;
            tsiSlider.speed /= (TSI_TOUCH_CNT_SLIDE_MAX - TSI_TOUCH_CNT_SLIDE_MIN);
            
            tsiHostInterface_packet.type = packetType_slide;
            tsiHostInterface_packet.length = 1;
            tsiHostInterface_packet.data[0] = tsiSlider.speed;
            tsiHostInterface_packet.data[1] = gHostInterface_trailerByte;
                
            HostInterface_TxQueueMsgPut((hostInterface_packet_t *)&tsiHostInterface_packet);
            
            OSA_TimeDelay(100u);
        }
    }
    else
    {
        // Check whether both slider electrodes are released?
        if((tsiSlider.elecUp->isActive || tsiSlider.elecDown->isActive) == FALSE)
        {
            tsiSlider.state = tsiSlider_state_idle;                              // Go to "idle" state.
            tsiSlider.lastActiveElec = NULL;                                     // Clear lastActiveElec because there is no active electrode.
        }
        
        // If current state of slider is "slide" there is nothing else to do.
        if(tsiSlider.state != tsiSlider_state_slide)
        {
            tsiElec_t *tmpTsiElec;
            
            // Get active eletrode.
            tmpTsiElec = (tsiSlider.elecUp->isActive) ? tsiSlider.elecUp : tsiSlider.elecDown;
            
            // If active electrode changed from previous measurement, slider not in "idle" state, does nothing.
            // New electrode should be "process" only if it detected from "idle" slider state.
            if(
                (tmpTsiElec != tsiSlider.lastActiveElec) &&
                (tsiSlider.state != tsiSlider_state_idle)
              )
            {
                return;    
            }

            tsiSlider.lastActiveElec = tmpTsiElec;                               // Update elctrode which is detected as active.
            
            // Process states (counters) of all electrodes.
            for(cnt = 0; cnt <  TSI_ELECTRODE_CNT; cnt++)
            {
                tsiElec_activeCnt_t status;
                
                // Process active counter markers.
                status = TouchSense_ElecActiveCntProcess(tsiElec_Array[cnt]);
                
                if(
                    (tsiElec_Array[cnt]->id == tsiElecId_SlideUp) ||
                    (tsiElec_Array[cnt]->id == tsiElecId_SlideDown) 
                  )       
                {
                    // If counter of electrode reached  "down" or "pressed" values, update state of overall slider.
                    if(status == tsiElec_activeCnt_downDetect)
                    {
                        tsiSlider.state = tsiSlider_state_down;
                    }
                    else if(status == tsiElec_activeCnt_pressDetect)
                    {
                        tsiSlider.state = tsiSlider_state_press;
                    }
                }
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    This function compares current measurement value with corresponding "untouched" value,
 *    and decides whether electrode is active or not.
 *
 *    @param    pElectrode  Address of electrode object.
 *
 */

static osaStatus_t TouchSense_ElecCheckIsActive(tsiElec_t *pElectrode)
{
    uint16_t currentMeas;
    tsi_status_t result;
    
    // Get last measured value for corresponding channel.
    result = TSI_DRV_GetCounter(TSI_INSTANCE, pElectrode->channel, &currentMeas);
    if( kStatus_TSI_Success != result )
    {
        panic(0,0,0,0);
        return osaStatus_Error;
    } 
    
    // Compare with "untouched" value (use TSI_NOISE_THRESHOLD to minimize noise.
    if(currentMeas > pElectrode->untouchMeas + TSI_NOISE_THRESHOLD)
    {
        pElectrode->isActive = TRUE;
    }
    else
    {
        pElectrode->isActive = FALSE;
    }
    
    return osaStatus_Success;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    This function process active counter markers of electrode. Every successive measurement increments electrode active
 *    counter if electrode is active, or reset to 0, if electrode is idle. When counter reaches "tsiElec_activeCnt_downDetect" 
 *    or "tsiElec_activeCnt_pressDetect" value, function put corresponding host-interface-packet into queue.
 *
 *    @param    pElectrode  Address of electrode object.
 *
 *    @return   Last detected "count-event".
 */

static tsiElec_activeCnt_t TouchSense_ElecActiveCntProcess(tsiElec_t *pElectrode)
{
    tsiElec_activeCnt_t status;
    
    // If electrode is not active, reset active counter.
    if(!pElectrode->isActive)
    {
        pElectrode->activeCnt = tsiElec_activeCnt_idle;
        status = tsiElec_activeCnt_idle;
    }
    else
    {
        tsiHostInterface_packet.length = 0;
        tsiHostInterface_packet.data[0] = gHostInterface_trailerByte;
            
        // If active counter reach "tsiElec_activeCnt_pressDetect" value
        // put corresponding host-interface_Tx-packet into queue.
        if(pElectrode->activeCnt == tsiElec_activeCnt_pressDetect)
        {
            status = tsiElec_activeCnt_pressDetect;
            pElectrode->activeCnt -= tsiElec_activeCnt_downDetect;                    // Before next "PRESS" count detected, measure more "tsiElec_activeCnt_downDetect" times.
            
            tsiHostInterface_packet.type = TouchSense_GetPacketType(pElectrode->id);
            HostInterface_TxQueueMsgPut((hostInterface_packet_t *)&tsiHostInterface_packet);
        }
        else 
        {
            pElectrode->activeCnt++;                                             // Increment active counter.   
            
            // If active counter reach "tsiElec_activeCnt_downDetect" value
            // put corresponding host-interface_Tx-packet into queue.
            if(pElectrode->activeCnt == tsiElec_activeCnt_downDetect)
            {
                status = tsiElec_activeCnt_downDetect;
                 
                tsiHostInterface_packet.type = TouchSense_GetPacketType(pElectrode->id);
                HostInterface_TxQueueMsgPut((hostInterface_packet_t *)&tsiHostInterface_packet);
            }
        }
    }
    return status;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

static hostInterface_packetType_t TouchSense_GetPacketType(tsiElecId_t id) 
{
    return (hostInterface_packetType_t)id;
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

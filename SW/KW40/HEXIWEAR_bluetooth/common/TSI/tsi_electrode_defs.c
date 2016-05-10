/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include "tsi.h"
#include "tsi_electrode_defs.h"
#include "EmbeddedTypes.h"
#include "board.h"
#include "fsl_os_abstraction.h"
#include "fsl_osa_ext.h"
#include "fsl_tsi_driver.h"
#include "panic.h"
#include "debug.h"
#include "host_mcu_interface.h"



/*! *********************************************************************************
*************************************************************************************
* Private macros
*************************************************************************************
********************************************************************************** */

#ifdef TSI_ELECTRODE_DEFS

#define TSI_CHANNEL_0              (0)
#define TSI_CHANNEL_1              (1)
#define TSI_CHANNEL_4              (4)
#define TSI_CHANNEL_5              (5)
#define TSI_CHANNEL_6              (6)
#define TSI_CHANNEL_7              (7)
#define TSI_CHANNEL_12             (12)
#define TSI_CHANNEL_10             (10)

/************************************************************************************
*************************************************************************************
* Definitions of electrodes
*************************************************************************************
************************************************************************************/

static tsiElec_t tsiElec_SlideRightUp = 
{   
    .isActive       = FALSE,
    .activeCnt      = 0, 
    .idleCnt        = 0, 
    .channel        = TSI_CHANNEL_0,
    .untouchMeas    = TSI_RIGHT_UP_UNTOUCHED,
    .threshold      = TSI_RIGHT_UP_THRESHOLD,
    .id             = tsiElecId_SlideUp,
};

static tsiElec_t tsiElec_SlideRightDown = 
{
    .isActive       = FALSE,
    .activeCnt      = 0, 
    .idleCnt        = 0, 
    .channel        = TSI_CHANNEL_1,
    .untouchMeas    = TSI_RIGHT_DOWN_UNTOUCHED,
    .threshold      = TSI_RIGHT_DOWN_THRESHOLD,
    .id             = tsiElecId_SlideDown,
};

static tsiElec_t tsiElec_SlideLeftUp = 
{   
    .isActive       = FALSE,
    .activeCnt      = 0, 
    .idleCnt        = 0, 
    .channel        = TSI_CHANNEL_7,
    .untouchMeas    = TSI_LEFT_UP_UNTOUCHED,
    .threshold      = TSI_LEFT_UP_THRESHOLD,
    .id             = tsiElecId_SlideUp,
};

static tsiElec_t tsiElec_SlideLeftDown = 
{
    .isActive       = FALSE,
    .activeCnt      = 0, 
    .idleCnt        = 0, 
    .channel        = TSI_CHANNEL_6,
    .untouchMeas    = TSI_LEFT_DOWN_UNTOUCHED,
    .threshold      = TSI_LEFT_DOWN_THRESHOLD,
    .id             = tsiElecId_SlideDown,
};

static tsiElec_t tsiElec_Left = 
{   
    .isActive       = FALSE,
    .activeCnt      = 0, 
    .idleCnt        = 0, 
    .channel        = TSI_CHANNEL_5,
    .untouchMeas    = TSI_LEFT_UNTOUCHED,
    .threshold      = TSI_LEFT_THRESHOLD,
    .id             = tsiElecId_Left,
};

static tsiElec_t tsiElec_Right = 
{   
    .isActive       = FALSE,
    .activeCnt      = 0, 
    .idleCnt        = 0, 
    .channel        = TSI_CHANNEL_4,
    .untouchMeas    = TSI_RIGHT_UNTOUCHED,
    .threshold      = TSI_RIGHT_THRESHOLD,
    .id             = tsiElecId_Right,
};

static tsiSlider_select_t activeSlider;

/************************************************************************************
*************************************************************************************
* Definition of slider
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Definition of array of active electrodes
*************************************************************************************
************************************************************************************/

tsiElec_t *tsiElec_Array[TSI_ELECTRODE_CNT] =
{
    0,
    0,
    &tsiElec_Left,
    &tsiElec_Right,
};

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    
 */

tsiSlider_select_t TouchSense_SliderGetActive(void) 
{
    return activeSlider;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    
 */

void TouchSense_SliderSetActive(tsiSlider_select_t slider) 
{    
    TouchSense_MutexLock();
    
    if(slider == tsiSlider_select_left) 
    {
        TSI_DRV_EnableElectrode(TSI_INSTANCE, tsiElec_SlideRightUp.channel, false);
        TSI_DRV_EnableElectrode(TSI_INSTANCE, tsiElec_SlideRightDown.channel, false);
        
        TSI_DRV_EnableElectrode(TSI_INSTANCE, tsiElec_SlideLeftUp.channel, true);
        TSI_DRV_EnableElectrode(TSI_INSTANCE, tsiElec_SlideLeftDown.channel, true);
    
        tsiElec_Array[0] = &tsiElec_SlideLeftUp;
        tsiElec_Array[1] = &tsiElec_SlideLeftDown;
    }
    else if(slider == tsiSlider_select_right) 
    {
        TSI_DRV_EnableElectrode(TSI_INSTANCE, tsiElec_SlideLeftUp.channel, false);
        TSI_DRV_EnableElectrode(TSI_INSTANCE, tsiElec_SlideLeftDown.channel, false);
        
        TSI_DRV_EnableElectrode(TSI_INSTANCE, tsiElec_SlideRightUp.channel, true);
        TSI_DRV_EnableElectrode(TSI_INSTANCE, tsiElec_SlideRightDown.channel, true);
        
        tsiElec_Array[0] = &tsiElec_SlideRightUp;
        tsiElec_Array[1] = &tsiElec_SlideRightDown;
    }
    
#if (TSI_CALIBRATION_PRESET == FALSE)
    // Start measuring level in untouched state.
    while(TSI_DRV_MeasureBlocking(TSI_INSTANCE) != kStatus_TSI_Success)
    {
        ;//DebugPrint("The measure of TSI failed.");
    }
    
    // Get the last measured values in the previous measure cycle.
    TSI_DRV_GetCounter(TSI_INSTANCE, tsiElec_Array[0]->channel, &tsiElec_Array[0]->untouchMeas);
    TSI_DRV_GetCounter(TSI_INSTANCE, tsiElec_Array[1]->channel, &tsiElec_Array[1]->untouchMeas);
#endif
    
    TouchSense_MutexUnlock();
    
    activeSlider = slider;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    
 */

void TouchSense_LefRightInit(void)
{
    // Enable left and right electrode.
    TSI_DRV_EnableElectrode(TSI_INSTANCE, tsiElec_Left.channel, true);
    TSI_DRV_EnableElectrode(TSI_INSTANCE, tsiElec_Right.channel, true);
    
#if (TSI_CALIBRATION_PRESET == FALSE)
    // Start measuring level in untouched state.
    while(TSI_DRV_MeasureBlocking(TSI_INSTANCE) != kStatus_TSI_Success)
    {
        ;//DebugPrint("The measure of TSI failed.");
    }
    TSI_DRV_GetCounter(TSI_INSTANCE, tsiElec_Left.channel, &tsiElec_Left.untouchMeas);
    TSI_DRV_GetCounter(TSI_INSTANCE, tsiElec_Right.channel, &tsiElec_Right.untouchMeas);
#endif    
    
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

#endif
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
    .activeCnt      = tsiElec_activeCnt_idle, 
    .channel        = TSI_CHANNEL_0,
    .id             = tsiElecId_SlideUp,
};

static tsiElec_t tsiElec_SlideRightDown = 
{
    .isActive       = FALSE,
    .activeCnt      = tsiElec_activeCnt_idle, 
    .channel        = TSI_CHANNEL_1,
    .id             = tsiElecId_SlideDown,
};

static tsiElec_t tsiElec_SlideLeftUp = 
{   
    .isActive       = FALSE,
    .activeCnt      = tsiElec_activeCnt_idle, 
    .channel        = TSI_CHANNEL_7,
    .id             = tsiElecId_SlideUp,
};

static tsiElec_t tsiElec_SlideLeftDown = 
{
    .isActive       = FALSE,
    .activeCnt      = tsiElec_activeCnt_idle, 
    .channel        = TSI_CHANNEL_6,
    .id             = tsiElecId_SlideDown,
};

static tsiElec_t tsiElec_Left = 
{   
    .isActive       = FALSE,
    .activeCnt      = tsiElec_activeCnt_idle, 
    .channel        = TSI_CHANNEL_5,
    .id             = tsiElecId_Left,
};

static tsiElec_t tsiElec_Right = 
{   
    .isActive       = FALSE,
    .activeCnt      = tsiElec_activeCnt_idle, 
    .channel        = TSI_CHANNEL_4,
    .id             = tsiElecId_Right,
};

/************************************************************************************
*************************************************************************************
* Definition of slider
*************************************************************************************
************************************************************************************/

// Define slider object, which contains two electrodes.
tsiSlider_t tsiSlider;

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

void TouchSense_SliderInit(tsiSlider_select_t sliderSelect) {
    
    tsiSlider.state = tsiSlider_state_idle;
    tsiSlider.speed = 0;
    tsiSlider.lastActiveElec = NULL;
    
    if(sliderSelect == tsiSlider_select_left) 
    {
        tsiSlider.elecUp = &tsiElec_SlideLeftUp;
        tsiSlider.elecDown = &tsiElec_SlideLeftDown;
    }
    else if(sliderSelect == tsiSlider_select_right) 
    {
        tsiSlider.elecUp = &tsiElec_SlideRightUp;
        tsiSlider.elecDown = &tsiElec_SlideRightDown;
    }
    
    tsiElec_Array[0] = tsiSlider.elecUp;
    tsiElec_Array[1] = tsiSlider.elecDown;
    
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

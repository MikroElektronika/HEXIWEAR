
#ifndef _TSI_H_
#define _TSI_H_

#include <stdint.h>
#include "EmbeddedTypes.h"
#include "fsl_os_abstraction.h"
#include "fsl_osa_ext.h"
#include "host_mcu_interface.h"

#define gTouchSenseTaskStackSize_c  (400)
#define gTouchSensePriority_c       (9)

/*! *********************************************************************************
*************************************************************************************
* Public macros
*************************************************************************************
********************************************************************************** */

#define TSI_THRESHOLD_SAMPLING     (50u)
#define TSI_INSTANCE               (0)

#define TSI_NOISE_THRESHOLD        (20u)

#define TSI_ELECTRODE_CNT          (4u)
#define TSI_SLIDE_SPEED_MAX        (100u)
#define TSI_TOUCH_CNT_SLIDE_MIN    (3u)
#define TSI_TOUCH_CNT_SLIDE_MAX    (40u)

/*! *********************************************************************************
*************************************************************************************
* Type definitions
*************************************************************************************
********************************************************************************** */
// Possible threshold values for active counter properties of electrode objects.
typedef enum
{
    tsiElec_activeCnt_idle        = 0,
    tsiElec_activeCnt_downDetect  = 3,
    tsiElec_activeCnt_pressDetect = 70,
}
tsiElec_activeCnt_t;

// IDs of electrodes.
typedef enum
{
    tsiElecId_SlideUp    = packetType_pressUp,
    tsiElecId_SlideDown  = packetType_pressDown,
    tsiElecId_Left       = packetType_pressLeft,
    tsiElecId_Right      = packetType_pressRight,
    
}
tsiElecId_t;

// State values for slider object.
typedef enum
{
    tsiSlider_state_idle,
    tsiSlider_state_down,
    tsiSlider_state_press,
    tsiSlider_state_slide,
}
tsiSlider_state_t;

// Slider select values
typedef enum
{
    tsiSlider_select_left,
    tsiSlider_select_right,
}
tsiSlider_select_t;

// Definition of type for "electrode" object.
typedef struct 
{
    bool                isActive;      // Flag that contain information whether electrode is active or idle during last measurement.
    tsiElec_activeCnt_t activeCnt;     // Number of successive active samples of electrode.
    uint16_t            untouchMeas;   // Measured values of electrode in untouched state. 
    uint8_t             channel;       // Index of TSI channel.
    tsiElecId_t         id;            // ID of electrode.
}
tsiElec_t;

// Definition of type for "slider" object.
typedef struct
{
    tsiElec_t         *elecUp;
    tsiElec_t         *elecDown;
    tsiSlider_state_t state;                              // State of slider.      
    uint16_t          speed;                              // Speed of slide event.
    tsiElec_t        *lastActiveElec;                     // Address of active electrode from previous measurement.
                                                          // If previous measurement does not detect active electrode, this address should be NULL.
}
tsiSlider_t;

extern tsiElec_t *tsiElec_Array[TSI_ELECTRODE_CNT];
extern tsiSlider_t tsiSlider;

/************************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
************************************************************************************/

void TouchSense_Init(void);
void TouchSense_SliderInit(tsiSlider_select_t sliderSelect);

#endif /* _TSI_H_ */

/*! *********************************************************************************
 * @}
 ********************************************************************************** */


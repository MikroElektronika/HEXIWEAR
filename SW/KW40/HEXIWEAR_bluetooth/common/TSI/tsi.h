
#ifndef _TSI_H_
#define _TSI_H_

#include <stdint.h>
#include "EmbeddedTypes.h"
#include "fsl_os_abstraction.h"
#include "fsl_osa_ext.h"
#include "host_mcu_interface.h"

#define gTouchSenseTaskStackSize_c  (400)
#define gTouchSensePriority_c       (10)

/*! *********************************************************************************
*************************************************************************************
* Public macros
*************************************************************************************
********************************************************************************** */

/*! *********************************************************************************
*************************************************************************************
* Type definitions
*************************************************************************************
********************************************************************************** */

// IDs of electrodes.
typedef enum
{
    tsiElecId_SlideUp    = packetType_pressUp,
    tsiElecId_SlideDown  = packetType_pressDown,
    tsiElecId_Left       = packetType_pressLeft,
    tsiElecId_Right      = packetType_pressRight,
    
}
tsiElecId_t;


// Slider select values
typedef enum
{
    tsiGroup_select_left   = 0,
    tsiGroup_select_right  = 1,
}
tsiGroup_select_t;


/************************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
************************************************************************************/

void TouchSense_Init(void);
void TouchSense_LefRightInit(void);
void TouchSense_SetActiveGroup(tsiGroup_select_t tsiGroup);
tsiGroup_select_t TouchSense_GetActiveGroup(void);
osa_status_t TouchSense_MutexLock(uint32_t timeout);
void TouchSense_MutexUnlock(void);


#endif /* _TSI_H_ */

/*! *********************************************************************************
 * @}
 ********************************************************************************** */


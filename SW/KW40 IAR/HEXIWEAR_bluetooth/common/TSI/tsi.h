/**
 *    @file tsi.h
 */

#ifndef _TSI_H_
#define _TSI_H_

#include <stdint.h>
#include "EmbeddedTypes.h"
#include "fsl_os_abstraction.h"
#include "fsl_osa_ext.h"
#include "host_mcu_interface.h"

#define gTouchSenseTaskStackSize_c  (400)
#define gTouchSensePriority_c       (10)

/************************************************************************************
*************************************************************************************
* Public macros
*************************************************************************************
********************************************************************************** */

/************************************************************************************
*************************************************************************************
* Type definitions
*************************************************************************************
********************************************************************************** */

/** IDs of electrodes. */
typedef enum
{
    tsiElecId_SlideUp    = packetType_pressUp,  
    tsiElecId_SlideDown  = packetType_pressDown,
    tsiElecId_Left       = packetType_pressLeft,
    tsiElecId_Right      = packetType_pressRight,
    
}
tsiElecId_t;

/** Groups of vertically positioning electrodes. */
typedef enum
{
    tsiGroup_select_left   = 0,  /**< Left group. */
    tsiGroup_select_right  = 1,  /**< Right group. */
}
tsiGroup_select_t;


/************************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
************************************************************************************/

/**
 *    Initialize module, and creates the TouchSense's task.
 */
void TouchSense_Init(void);

/**
 *    Function called from other tasks to set current active group of electrodes.
 *
 *    @param   tsiGroup   Group of electrodes to be set.
 */
void TouchSense_SetActiveGroup(tsiGroup_select_t tsiGroup);

/**
 *    Return current active group of electrodes.
 *
 *    @return      tsiGroup_select_left
 *    @return      tsiGroup_select_right
 */
tsiGroup_select_t TouchSense_GetActiveGroup(void);

/**
 *    Lock tsi driver mutex.
 *
 *    @param    timeout   The maximum number of milliseconds to wait for the mutex.
 *
 *    @return             kStatus_OSA_Success   The mutex is locked successfully.
 *    @return             kStatus_OSA_Timeout   Timeout occurred.
 *    @return             kStatus_OSA_Error     Incorrect parameter was passed.
 */
osa_status_t TouchSense_MutexLock(uint32_t timeout);

/**
 *    Unlock tsi driver mutex.
 */
void TouchSense_MutexUnlock(void);


#endif /* _TSI_H_ */

/*! *********************************************************************************
 * @}
 ********************************************************************************** */


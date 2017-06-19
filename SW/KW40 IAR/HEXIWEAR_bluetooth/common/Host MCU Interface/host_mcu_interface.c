/**
 *    @file host_mcu_interface.c
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
#include "fsl_os_abstraction.h"
#include "fsl_os_abstraction.h"
#include "fsl_lpuart_dma_driver.h"
#include "fsl_lpuart_driver.h"
#include "fsl_dma_driver.h"
#include "panic.h"
#include "debug.h"
#include "host_mcu_interface.h"
#include "fsl_interrupt_manager.h"

/************************************************************************************
*************************************************************************************
* Extern functions
*************************************************************************************
************************************************************************************/
extern void LPUART_DRV_IRQHandler(uint32_t instance);

/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/

static lpuart_state_t       hostInterface_lpuartState;
static lpuart_user_config_t hostInterface_lpuartConfig;

/************************************************************************************
*************************************************************************************
* Private prototypes
*************************************************************************************
********************************************************************************** */



/************************************************************************************
*************************************************************************************
* Functions definitions
*************************************************************************************
********************************************************************************** */

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Initialize module.
 *
 *    @return                          osaStatus_Success  Successfully created tasks and  message queues.
 *    @return                          osaStatus_Error    Initialization fail.               	
 */

osaStatus_t HostInterface_Init(void)
{
    osaStatus_t status;
    
    HostInterface_EventsInit();
    
    HostInterface_UartInit();
    
    status = HostInterface_TxInit();
    if( osaStatus_Success != status )
    {
        panic(0,0,0,0);
        return status;
    } 
    
    status = HostInterface_RxInit();
    if( osaStatus_Success != status )
    {
        panic(0,0,0,0);
        return status;
    } 
        
    return osaStatus_Success;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Initialize UART module.
 */

void HostInterface_UartInit(void)
{     
    configure_lpuart_pins(gHostInterface_instance);
    
    hostInterface_lpuartConfig.baudRate = 230400;
    hostInterface_lpuartConfig.clockSource = kClockLpuartSrcOsc0erClk,
    hostInterface_lpuartConfig.bitCountPerChar = kLpuart8BitsPerChar;
    hostInterface_lpuartConfig.parityMode = kLpuartParityDisabled;
    hostInterface_lpuartConfig.stopBitCount = kLpuartTwoStopBit;
    
    LPUART_DRV_Init(gHostInterface_instance, &hostInterface_lpuartState, &hostInterface_lpuartConfig);
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *  Implementation of LPUART0 handler named in startup code.   
 */

void LPUART0_IRQHandler(void)
{
    LPUART_DRV_IRQHandler(0);
}
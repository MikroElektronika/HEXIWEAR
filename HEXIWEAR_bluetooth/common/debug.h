#ifndef _DEBUG_H_
#define _DEBUG_H_

#include "fsl_lpuart_driver.h"

/*************************************************************************************
**************************************************************************************
* Public macros
**************************************************************************************
*************************************************************************************/

/* App Configuration */
     
/*! Enable/disable debug capability */
#ifndef gDebugEnabled_d
#define gDebugEnabled_d  FALSE
#endif


#if gDebugEnabled_d
    #include <string.h>
    #define DebugPrint(text) \
                LPUART_DRV_SendDataBlocking(gHostInterface_instance, text, strlen(text), 100); \
                LPUART_DRV_SendData(gHostInterface_instance, "\r\n", 2)
#else
    extern uint8_t gAppSerMgrIf;
    #define DebugPrint(text)

#endif


#endif /* _DEBUG_H_ */
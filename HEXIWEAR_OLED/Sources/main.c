/* ###################################################################
**     Filename    : main.c
**     Project     : OLED_bm
**     Processor   : MK64FN1M0VDC12
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-11-24, 19:40, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/
/*!
**  @addtogroup main_module main module documentation
**  @{
*/
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "clkManager.h"
#include "pin_mux.h"
#include "osa1.h"
#include "OLED_SPI.h"
#include "FLASH_SPI.h"
#include "dmaController1.h"
#include "GPIO.h"
#include "PWR_Manager.h"
#if CPU_INIT_CONFIG
  #include "Init_Config.h"
#endif
/* User includes (#include below this line is not maintained by Processor Expert) */
#define HEXIWEAR_OLED
#define HEXIWEAR_FLASH
#define HEXIWEAR_PWR

//#include "OLED_defs.h"
#include "OLED_driver.h"
#include "OLED_info.h"

#include "FLASH_defs.h"
#include "FLASH_driver.h"

#include "menu_resources.h"
#include "menu_driver.h"
#include "error.h"

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */

#if defined (HEXIWEAR_OLED)
  GPIO_DRV_Init( NULL, OLED_cfg );
#endif

#if defined (HEXIWEAR_FLASH)
  GPIO_DRV_Init( NULL, FLASH_cfg );
#endif

#if defined (HEXIWEAR_PWR)
  GPIO_DRV_Init( NULL, PWR_cfg );
#endif

  MenuDriver_Init();
//  FLASH_Init( &flashModule, &flashSettings );

  /**
   * sleep mode test
   */

//  while (1)
//  {
//    POWER_SYS_SetMode( 1, kPowerManagerPolicyAgreement );
//    OLED_SendCmd( OLED_CMD_DISPLAYOFF, FIRST_BYTE );
//    OSA_TimeDelay(250);
//    OLED_SendCmd( OLED_CMD_DISPLAYON, FIRST_BYTE );
//    OSA_TimeDelay(250);
//  }

  /**
   * toggle throughout screens
   */

  while(1)
  {
    MenuDriver_LoadScreen(MENU_NAVIGATION_ENTER, NULL);
    OSA_TimeDelay(250);

    MenuDriver_LoadScreen(MENU_NAVIGATION_RIGHT, NULL);
    MenuDriver_LoadScreen(MENU_NAVIGATION_LEFT, NULL);

    MenuDriver_LoadScreen(MENU_NAVIGATION_BACK, NULL);
    OSA_TimeDelay(250);
  }

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/

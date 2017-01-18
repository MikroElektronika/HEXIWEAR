/****************************************************************************
* Title                 :   Proximity 2 click
* Filename              :   HEXIWEAR_Proximity_2_Click.c
* Author                :   ML
* Origin Date           :   12/05/2016
* Notes                 :   Proximity 2 Example
*****************************************************************************/
/**************************CHANGE LIST **************************************
*
*    Date    Software Version    Initials       Description
*  12/05/16       1.0.0          UC             Functional example finished.
*
*****************************************************************************/
/**
 * @file HEXIWEAR_Proximity_2_Click.c
 * @brief <h2> Proximity 2 Example </h2>
 *
 * @par
 * Example for <a href="http://www.mikroe.com">MikroElektronika's</a>
 * Proximity 2 click board.
 */

/**
 * @page Example Info
 * @date        12 May 2016
 * @author      Uros Cvetinovic
 * @copyright   GNU Public License
 * @version     1.0.0 - Initial testing and verification
 */

/**
 * @page Test Configuration
 * <h3> Test configuration : </h3>
 * @par
 * <ul>
 * <li><b> MCU           </b> :      MK64FN1M0XXX12              </li>
 * <li><b> Dev. Board    </b> :      HEXIWEAR                    </li>
 * <li><b> Oscillator    </b> :      12 MHz external             </li>
 * <li><b> Ext. Modules  </b> :      Proximity 2 Click                 </li>
 * <li><b> SW            </b> :      MikroC PRO for ARM 4.7.1    </li>
 * </ul>
 */

/**
 * @mainpage
 * <h3> Proximity 2 click example using HEXIWEAR </h3>
 * @par Place Proximity 2 Click into the mikroBUS socket 2 on the docking station.
 * It detects Distance up to ten centimeters.
 *
 * <h3> Proximity 2 Features </h3>
 * @par Proximity 2 click, Hexiwear Docking Station
 */

/******************************************************************************
* Includes
*******************************************************************************/

#include "OLED_driver.h"
#include "MAX44000_Reg.h"
#include "MAX44000_Driver.h"

/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/

unsigned char alsDataLow;
unsigned char alsDataHigh;
unsigned char ProxiValue;
unsigned char ProxiOldValue;
unsigned char AverageProxiValue;
unsigned int Light;
unsigned int Distance[4];
unsigned int Lux[6];
int value;
/******************************************************************************
* Function Prototypes
*******************************************************************************/

void screen_init();

/******************************************************************************
* Private Function Definitions
*******************************************************************************/

/******************************************************************************
* Public Function Definitions
*******************************************************************************/

void screen_init(){
OLED_Init();
OLED_FillScreen( OLED_COLOR_BLACK );
OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_WHITE, 0 );
OLED_DrawImage(Proximity2_bmp,0,0);
}


void main() {
 I2C0_Init_Advanced(400000, &_GPIO_Module_I2C0_PD8_9);

 delay_ms(200);

 screen_init();

 MAX44000_Init();
 
 while(1){
 ProxiValue = MAX44000_ReadRegister(PROX);
 ByteToStr(ProxiValue,Distance);
 value = (76-( ProxiValue / 3));
 OLED_DrawBox (10, 76, value, 3, OLED_COLOR_RED);
 if(ProxiOldValue != ProxiValue){
   OLED_DrawBox (10, 76, 76, 3, OLED_COLOR_WHITE);
   OLED_DrawBox (10, 76, value, 3, OLED_COLOR_RED);
   delay_ms(50);
   }
 ProxiOldValue = ProxiValue;
 }
}

/*************** END OF FUNCTIONS *********************************************/
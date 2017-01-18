/****************************************************************************
* Title                 :   Proto click
* Filename              :   HEXIWEAR_Proto_Click.c
* Author                :   ML
* Origin Date           :   27/04/2016
* Notes                 :   Proto Click Example
*****************************************************************************/
/**************************CHANGE LIST **************************************
*
*    Date    Software Version    Initials       Description
*  27/04/16       1.0.0            ML        Interface Created.
*
*****************************************************************************/
/**
 * @file HEXIWEAR_Proto_Click.c
 * @brief <h2> Proto Click Example </h2>
 *
 * @par
 * Example for <a href="http://www.mikroe.com">MikroElektronika's</a>
 * Proto click board.
 */

/**
 * @page LIB_INFO Library Info
 * @date        19 Feb 2016
 * @author      ML
 * @copyright   GNU Public License
 * @version     1.0.0 - Initial testing and verification
 */

/**
 * @page TEST_CFG Test Configurations
 * <h3> Test configuration : </h3>
 * @par
 * <ul>
 * <li><b> MCU           </b> :      MK64FN1M0XXX12               </li>
 * <li><b> Dev. Board    </b> :      HEXIWEAR                     </li>
 * <li><b> Oscillator    </b> :      12 MHz external              </li>
 * <li><b> Ext. Modules  </b> :      Proto Click on mikroBUS 1    </li>
 * <li><b> SW            </b> :      MikroC PRO for ARM 4.7.1     </li>
 * </ul>
 */

/**
 * @mainpage
 * <h3> Proto click example using HEXIWEAR </h3>
 * @par This example demonstrates usage of the Proto click board in mikroBUS socket 1.
 * Press the button soldered on the Proto Click to change the LED state.
 *
 * <h3> Proto Features </h3>
 * @par Proto click, Hexiwear docking station
 */

/******************************************************************************
* Includes
*******************************************************************************/
#include "OLED_Driver.h"

/******************************************************************************
* Macros
*******************************************************************************/
#define LED_ON()     PTA_PSOR.B10 = 1
#define LED_OFF()    PTA_PCOR.B10 = 1
#define LED_TOGGLE() PTA_PTOR.B10 = 1

#define BUTTON_ReadState() PTC_PDIR.B4
#define BUTTON_State_ON  ( 0 )
#define BUTTON_State_OFF ( 1 )

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
sbit LED_ctl   at PTA_PDOR.B10;
sbit BUT_input at PTC_PDOR.B4;

uint8_t
    oldState = BUTTON_State_OFF;

/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Public Function Definitions
*******************************************************************************/
void main() org 0x1000
{
    /** initialize GPIO */

    // set PTA10 as digital output
    GPIO_Digital_Output( &PTA_PDOR, _GPIO_PINMASK_10 );
    // set PTC4 as digital input
    GPIO_Digital_Input( &PTC_PDOR, _GPIO_PINMASK_4 );
    
    OLED_Init();
    OLED_DrawImage( &protoOFF_bmp, 0, 0 );

    while (1)
    {
        if ( BUTTON_ReadState() != oldState )
        {
            oldState = BUTTON_ReadState();
            switch ( oldState )
            {
                case BUTTON_State_ON:
                {
                    LED_ON();
                    OLED_DrawImage( &protoON_bmp, 0, 0 );
                    break;
                }

                case BUTTON_State_OFF:
                {
                    LED_OFF();
                    OLED_DrawImage( &protoOFF_bmp, 0, 0 );
                    break;
                }

                default: {}
            }
        }
    }
}

/*************** END OF FUNCTIONS *********************************************/
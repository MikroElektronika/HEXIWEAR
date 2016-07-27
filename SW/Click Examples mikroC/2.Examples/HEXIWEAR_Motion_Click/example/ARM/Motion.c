/****************************************************************************
* Title                 :   Motion click
* Filename              :   Motion.c
* Author                :   ML
* Origin Date           :   19/04/2016
* Notes                 :   Motion Example
*****************************************************************************/
/**************************CHANGE LIST **************************************
*
*    Date    Software Version    Initials       Description
*  19/04/16       1.0.0          ML             Functional example finished.
*
*****************************************************************************/
/**
 * @file Motion.c
 * @brief <h2> Motion Example </h2>
 *
 * @par
 * Example for <a href="http://www.mikroe.com">MikroElektronika's</a>
 * Motion click board.
 */

/**
 * @page Example Info
 * @date        19 Apr 2016
 * @author      Marko Lainovic
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
 * <li><b> Ext. Modules  </b> :      Motion Click                 </li>
 * <li><b> SW            </b> :      MikroC PRO for ARM 4.7.1    </li>
 * </ul>
 */

/**
 * @mainpage
 * <h3> Motion click example using HEXIWEAR </h3>
 * @par Place Motion Click into the mikroBUS socket 2 on the docking station.
 * Do a hand gesture and observe the movement being registered on-screen.
 *
 * <h3> Motion Features </h3>
 * @par Motion click, Hexiwear Docking Station
 */

/******************************************************************************
* Includes
*******************************************************************************/
#include "OLED_driver.h"

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
sbit Motion_Sens_EN  at PTB_PDOR.B19;
sbit Motion_Sens_PIN at PTB_PDIR.B8;

static uint8_t isMotionDetected = -1;

/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Private Function Definitions
*******************************************************************************/


/******************************************************************************
* Public Function Definitions
*******************************************************************************/
void main() org 0x1000
{
    /** initialize the OLED screen */
    OLED_Init();

    /** display logo */
    OLED_DrawImage( motion_none_bmp, 0, 0 );

    /** set INT pin as digital input */
    GPIO_Digital_Input( &PTB_PDOR, _GPIO_PINMASK_8 );

    /** set Motion_Sens_EN as digital output */
    GPIO_Digital_Output( &PTB_PDOR, _GPIO_PINMASK_19 );

    EnableInterrupts();
    NVIC_IntEnable( IVT_INT_PORTB );

    // enable interrupt at PTB8 on either edge
    PORTB_PCR8bits.IRQC = 0xB;

    /** Enable Motion sensor */
    Motion_Sens_EN = 1;

    while (1)
    {
        if ( 1 == isMotionDetected )
        {
            OLED_DrawImage( motion_detected_bmp, 0, 0 );
            isMotionDetected = -1;
        }
        else if ( 0 == isMotionDetected )
        {
            OLED_DrawImage( motion_none_bmp, 0, 0 );
            isMotionDetected = -1;
        }
    }
}

/**
 * Port B IRQ handler
 * detect the PB8 level change to update the current state
 */
void MotionDetect() iv IVT_INT_PORTB ics ICS_AUTO
{
    PORTB_ISFR = 0xFFFFFFFF;

    if ( 1 == Motion_Sens_PIN )
    {
        isMotionDetected = 1;
    }
    else
    {
        isMotionDetected = 0;
    }
}

/*************** END OF FUNCTIONS *********************************************/
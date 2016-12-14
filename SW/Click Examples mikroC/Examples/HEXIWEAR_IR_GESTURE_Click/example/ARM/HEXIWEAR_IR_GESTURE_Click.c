/****************************************************************************
* Title                 :   IR GESTURE click
* Filename              :   HEXIWEAR_IR_GESTURE.c
* Author                :   UC
* Origin Date           :   25/04/2016
* Notes                 :   IR GESTURE Example
*****************************************************************************/
/**************************CHANGE LIST **************************************
*
*    Date    Software Version    Initials       Description
*  25/04/16       1.0.0          UC             Functional example finished.
*
*****************************************************************************/
/**
 * @file IR GESTURE.c
 * @brief <h2> IR GESTURE Example </h2>
 *
 * @par
 * Example for <a href="http://www.mikroe.com">MikroElektronika's</a>
 * IR GESTURE click board.
 */

/**
 * @page Example Info
 * @date        25 Apr 2016
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
 * <li><b> Ext. Modules  </b> :      IR GESTURE Click                 </li>
 * <li><b> SW            </b> :      MikroC PRO for ARM 4.7.1    </li>
 * </ul>
 */

/**
 * @mainpage
 * <h3> IR GESTURE click example using HEXIWEAR </h3>
 * @par Place IR GESTURE Click into the mikroBUS socket 1 on the docking station.
 * You can activate it by moving some object, or hand over the sensor.
 *
 * <h3> IR GESTURE Features </h3>
 * @par IR GESTURE click, Hexiwear Docking Station
 */

/******************************************************************************
* Includes
*******************************************************************************/
#include <stdbool.h>
#include <stdint.h>
#include "ir_gesture_hw.h"
#include "resources.h"
#include "gesture.h"
#include "OLED_driver.h"
#include "common_screen_objects.h"

/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/
#define PROX_INT_HIGH   50 // Proximity level for interrupt
#define PROX_INT_LOW    0  // No far interrupt




/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
sbit APDS9960_INT at PTB_PDIR.B13;


/******************************************************************************
* Function Prototypes
*******************************************************************************/

static void handle_gesture( void );
static int system_init( void );
static bool volatile gesture_flag;


/******************************************************************************
* Private Function Definitions
*******************************************************************************/
/*
 * Handle the GUESTURE
 *
 * This function determines the guesture
 */
static void handle_gesture()
{
    if ( ir_gesture_available() )
    {
         switch ( ir_gesture_read_gesture() )
        {
          case DIR_UP:
          OLED_DrawImage( irgestureup_bmp, 0, 0 );
            break;
          case DIR_DOWN:
          OLED_DrawImage( irgesturedown_bmp, 0, 0 );
            break;
          case DIR_LEFT:
          OLED_DrawImage( irgestureleft_bmp, 0, 0 );
            break;
          case DIR_RIGHT:
          OLED_DrawImage( irgestureright_bmp, 0, 0 );
            break;
        }
    }
}

/*
 * System initialization
 *
 * This function initializes the system
 */
static int system_init()
{
    DisableInterrupts();
    GPIO_Digital_Input( &PTB_PDOR, _GPIO_PINMASK_13 );

    I2C0_Init_Advanced(400000, &_GPIO_Module_I2C0_PD8_9);
    Delay_ms( 100 );
    
    // Initialize APDS-9960 (configure I2C and initial values)
    ir_gesture_init( APDS9960_I2C_ADDR );
    ir_gesture_enable_gesture_sensor( true );
    
    // Initialize screen
    OLED_Init();
    OLED_DrawImage( irgesture_bmp, 0, 0 );
    OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_WHITE, 0 );

    PORTB_PCR13bits.IRQC = 0xB;
    NVIC_IntEnable( IVT_INT_PORTB );
    EnableInterrupts();

    return 0;
}


/******************************************************************************
* Public Function Definitions
*******************************************************************************/
void main()
{
    if( system_init() )
        return;
    DisableInterrupts();
    OLED_WriteText("Initialization", 20, 75);
    delay_ms(2000);
    OLED_DrawImage( irgesturen_bmp, 0, 0 );
    EnableInterrupts();
    while(1)
    {
        if( gesture_flag )
        {
            DisableInterrupts();
            handle_gesture();
            delay_ms(1000);
            OLED_DrawImage( irgesturen_bmp, 0, 0 );
            gesture_flag = false;
            EnableInterrupts();
        }
    }
}



void MotionDetect() iv IVT_INT_PORTB ics ICS_AUTO
{
    PORTB_ISFR = 0xFFFFFFFF;

    if( ir_gesture_is_interrupted( INT_GESTURE ) )
    {
        ir_gesture_clear_gesture_int();
        gesture_flag = true;

    }
}
/*************** END OF FUNCTIONS *********************************************/
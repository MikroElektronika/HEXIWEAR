/*******************************************************************************
* Title                 :   HEXIWEAR / Smoke Click / DOCKING STATION
* Filename              :   HEXIWEAR_Smoke_Click.c
* Author                :   Stefan Popovic
* Origin Date           :   Feb / 2017
* Notes                 :
*
*                          - Place Smoke click board on mikroBUS slot 1
*                          - This example demonstrates measuring of LED pulse
*                            amplitude and temperature from MAX30105 sensor
*                            in Multi-LED mode
*                          - Includes example.pld
/******************************************************************************
* Includes
*******************************************************************************/
#include "OLED_driver.h"
#include "OLED_resources.h"
#include "UART_Messaging.h"
#include "common_screen_objects.h"
#include "smoke.h"
/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/
#define PULSE_AMPLITUDE_THRESHOLD    2000000
/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
sbit SMOKE_INT       at PTB_PDIR.B13;
sbit HEXI_RED_LED    at PTC_PDOR.B8;
sbit HEXI_GREEN_LED  at PTD_PDOR.B0;

char txt_val[ 20 ];
/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Function Definitions
*******************************************************************************/
static void system_init()
{
  // OLED Init
  OLED_Init();
  OLED_FillScreen( OLED_COLOR_BLACK );

  // GPIO Init
  GPIO_Digital_Input( &PTB_PDIR, _GPIO_PINMASK_13 );
  GPIO_Digital_Output( &PTC_PDOR, _GPIO_PINMASK_8 );
  GPIO_Digital_Output( &PTD_PDOR, _GPIO_PINMASK_0 );

  // HEXIWEAR LEDs
  HEXI_RED_LED = 1;
  HEXI_GREEN_LED = 1;

  // I2C
  I2C0_Init_Advanced( 400000, &_GPIO_Module_I2C0_PD8_9 );

  // Display text
  BOX(0, 0, 96, 15, OLED_COLOR_GRAY);
  OLED_SetFont(guiFont_Exo_2_Condensed10x16_Regular, OLED_COLOR_WHITE, 0);
  LOG("SMOKE", 30, 0);
  OLED_SetFont(guiFont_Tahoma_7_Regular, OLED_COLOR_GRAY, 0);
}
// Writes current pulse amplitude and temperature on OLED
static void OLED_show( void )
{
    // Clear screen
    BOX(30, 15, 66, 81, OLED_COLOR_BLACK);
    
    LongToStr( smoke_get_red(), txt_val );
    OLED_SetFont(guiFont_Tahoma_7_Regular, OLED_COLOR_RED, 0);
    LOG ( "RED", 5, 20);
    LOG ( txt_val, 30, 20 );

    LongToStr( smoke_get_IR(), txt_val );
    OLED_SetFont(guiFont_Tahoma_7_Regular, OLED_COLOR_MAGENTA, 0);
    LOG ( "IR", 5, 40);
    LOG ( txt_val, 30, 40 );

    LongToStr( smoke_get_green(), txt_val );
    OLED_SetFont(guiFont_Tahoma_7_Regular, OLED_COLOR_GREEN, 0);
    LOG ( "GREEN", 5, 60);
    LOG ( txt_val, 30, 60 );

    OLED_SetFont(guiFont_Tahoma_7_Regular, OLED_COLOR_YELLOW, 0);
    LOG( "TEMP", 5, 80);
    FloatToStr( smoke_read_temp(), txt_val );
    LOG( txt_val, 50, 80 );
}
void main( void )
{
  system_init();
  smoke_init();
  smoke_set_registers_default();

  while ( true )
  {
    smoke_read_data();
    OLED_show();
    
    if( smoke_get_red()   > PULSE_AMPLITUDE_THRESHOLD  ||
        smoke_get_IR()    > PULSE_AMPLITUDE_THRESHOLD  ||
        smoke_get_green() > PULSE_AMPLITUDE_THRESHOLD )
    {
      HEXI_RED_LED = 0;
      HEXI_GREEN_LED = 1;
    }
    else
    {
      HEXI_RED_LED = 1;
      HEXI_GREEN_LED = 0;
    }
    Delay_ms( 1000 );
  }
}
/******************************************************************************
* End Of All Functions
*******************************************************************************/
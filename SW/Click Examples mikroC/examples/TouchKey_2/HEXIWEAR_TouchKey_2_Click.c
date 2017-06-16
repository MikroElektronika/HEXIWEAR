/*******************************************************************************
* Title                 :   HEXIWEAR / TouchKey 2 Click / DOCKING STATION
* Filename              :   HEXIWEAR_TouchKey_2_Click.c
* Author                :   Stefan Popovic
* Origin Date           :   Feb / 2017
* Notes                 :
*
*                          - Place TouchKey 2 click board on mikroBUS slot 1
*                          - This example demonstrates the functionality of
*                            TouchKey 2 click board by writing appropriate 
*                            key name after key press event
*                          - TouchKey 2 carries ATtiny817 MCU and sends 
*                            2 bytes via UART, on key pressed it
*                            sends KEY_Byte and on key release it sends 0x00
/******************************************************************************
* Includes
*******************************************************************************/
#include "OLED_driver.h"
#include "OLED_resources.h"
#include "UART_Messaging.h"
#include "common_screen_objects.h"
#include <stdbool.h>
#include <stdint.h>
/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/
#define KEY_A                0x01
#define KEY_B                0x02
#define KEY_C                0x04
#define KEY_D                0x08
#define KEY_RELEASE          0x00
/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
sbit TOUCH_KEY_2_RST at PTB_PDOR.B11;

bool key_A_pressed  = false;
bool key_B_pressed  = false;
bool key_C_pressed  = false;
bool key_D_pressed  = false;
bool key_released   = false;

char key;
char old_key;
/******************************************************************************
* Function Prototypes
*******************************************************************************/
static void system_init( void );
static void check_key_event( void );
static void display_key( char* key_name, unsigned int color );
/******************************************************************************
* Function Definitions
*******************************************************************************/
/*
 * System Initialization
 *
 * Configuring MCU ports, initializing UART, enabling interrupt, OLED init
 * and performing reset
 */
static void system_init( void )
{
    // Configuring RST pin as output
    GPIO_Digital_Input( &PTB_PDOR, _GPIO_PINMASK_11 );
    
    // UART Initialization
    UART2_Init_Advanced( 9600, _UART_8_BIT_DATA, _UART_NOPARITY,
                         _UART_ONE_STOPBIT, &_GPIO_Module_UART2_PD3_2 );
    Delay_ms( 100 );

    // UART Interrupt enabling
    UART2_C2 |= 1 << 5;
    NVIC_IntEnable( IVT_INT_UART2_RX_TX );
    EnableInterrupts();

    // OLED Init
    OLED_Init();
    OLED_FillScreen( OLED_COLOR_BLACK );
    // Display text
    BOX( 0, 0, 96, 15, OLED_COLOR_BLUE );
    OLED_SetFont( guiFont_Exo_2_Condensed10x16_Regular, OLED_COLOR_WHITE, 0 );
    LOG( "TouchKey 2", 20, 0 );
    LOG( "Touch any key", 10, 40 );
    OLED_SetFont( guiFont_Tahoma_7_Regular, OLED_COLOR_GRAY, 0 );

    // Perform TouchKey 2 board reset
    TOUCH_KEY_2_RST = 1;
    Delay_ms( 100 );
    TOUCH_KEY_2_RST = 0;
    Delay_ms( 100 );
    TOUCH_KEY_2_RST = 1;
}

/*
 * Checking for key pressed events
 *
 * Looking for Key ID and setting appropriate flags. Called inside interrupt
 */
static void check_key_event ( void )
{
        if ( key == KEY_A )
             {
                key_A_pressed = true;
             }
        else if ( key == KEY_B )
             {
                key_B_pressed = true;
             }
         else if ( key == KEY_C )
             {
                key_C_pressed = true;
             }
         else if ( key == KEY_D )
             {
                key_D_pressed = true;
             }
         else if ( key == KEY_RELEASE )
             {
                key_released = true;
             }
}

/*
 * Displaying key name with color
 */
void display_key( unsigned char* key_name, unsigned int color )
{
  OLED_SetFont( &LilyUPC57x120_Bold, color, 0);
  BOX( 10, 15, 86, 81, OLED_COLOR_BLACK );
  LOG( key_name, 20, 1 );
}

/*
 * Main function
 */
void main( void )
{
    system_init();
    
    while( true )
    {

        // Key A has been pressed
        if( key_A_pressed && old_key != KEY_A )
        {
            display_key( "A", OLED_COLOR_RED );
            key_A_pressed = false;
            old_key = KEY_A;
        }
        // Key B has been pressed
        else if( key_B_pressed && old_key != KEY_B )
        {
            display_key( "B", OLED_COLOR_GREEN );
            key_B_pressed = false;
            old_key = KEY_B;
        }
        // Key C has been pressed
        else if( key_C_pressed && old_key != KEY_C )
        {
            display_key( "C", OLED_COLOR_BLUE_1 );
            key_C_pressed = false;
            old_key = KEY_C;
        }
        // Key D has been pressed
        else if( key_D_pressed && old_key != KEY_D )
        {
            display_key( "D", OLED_COLOR_YELLOW );
            key_D_pressed = false;
            old_key = KEY_D;
        }
		
		 // Key released
        else if ( key_released && old_key != KEY_RELEASE )
        {
           key_released = false;
  
           if ( old_key == KEY_A )
           {
              display_key( "A", OLED_COLOR_GRAY );
           }
           else if ( old_key == KEY_B )
           {
              display_key( "B", OLED_COLOR_GRAY );
           }
           else if ( old_key == KEY_C )
           {
              display_key( "C", OLED_COLOR_GRAY );
           }
           else if ( old_key == KEY_D )
           {
              display_key( "D", OLED_COLOR_GRAY );
           }

           old_key = KEY_RELEASE;
        }
    }
}

void TOUCHKEY_2_RX_ISR() iv IVT_INT_UART2_RX_TX ics ICS_AUTO
{
    char s1 = UART2_S1;
    char tmp = UART2_D;

    if(  s1 & ( 1 << 5 )  )
    {
        key = tmp;
        check_key_event();
    }
}
/******************************************************************************
* End Of All Functions
*******************************************************************************/
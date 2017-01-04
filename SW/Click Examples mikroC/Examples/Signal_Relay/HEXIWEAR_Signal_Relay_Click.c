  /*******************************************************************************
  * Title                 :   HEXIWEAR / Signal Relay Click / DOCKING STATION
  * Filename              :   HEXIWEAR_Signal_Relay_Click.c
  * Author                :   Stefan Popovic
  * Origin Date           :   12/08/2016
  * Notes                 :   This example demonstrates button pressing
                              functionality by switching relays of Signal Relay 
                              Click board ON and OFF
 
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

  /******************************************************************************
  * Module Preprocessor Macros
  *******************************************************************************/

  /******************************************************************************
  * Module Typedefs
  *******************************************************************************/

  /******************************************************************************
  * Module Variable Definitions
  *******************************************************************************/
  sbit RE1 at PTB_PTOR.B2;
  sbit RE2 at PTB_PTOR.B11;
  sbit RE3 at PTC_PTOR.B4;
  sbit RE4 at PTA_PTOR.B10;
  /******************************************************************************
  * Function Prototypes
  *******************************************************************************/

  /******************************************************************************
  * Function Definitions
  *******************************************************************************/
  // MCU Init
  void system_init()
  {
      OLED_Init();
      OLED_DrawImage(&hexiwearLogo_bmp, 0, 0);
      // Setting PTA, PTB and PTC pins as output ( Buttons )
      GPIO_Digital_Output(&PTB_PDOR, _GPIO_PINMASK_2);
      GPIO_Digital_Output(&PTB_PDOR, _GPIO_PINMASK_11);
      GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_4);
      GPIO_Digital_Output(&PTA_PDOR, _GPIO_PINMASK_10);

      RE1 = 0;
      RE2 = 0;
      RE3 = 0;
      RE4 = 0;

      GPIO_Digital_Output(&PTB_PDOR, _GPIO_PINMASK_9); // Vibration PIN
      PTB_PDOR = 0;

      Delay_ms( 100 );
      
      // Display text
      OLED_SetFont(guiFont_Exo_2_Condensed10x16_Regular, OLED_COLOR_WHITE, 0);
      OLED_WriteText("SIGNAL RELAY", 12, 0);
      OLED_WriteText("  RE3          RE4", 15, 80);
      OLED_SetFont(guiFont_Exo_2_Condensed10x16_Regular, OLED_COLOR_WHITE, 1);
      OLED_WriteText("  RE2          RE1", 80, 80);

      // Init UART messaging
      hexiwear_uart_messaging_init();
  }
  
  // On button up pressed
  static void button_up( void )
  {
       PTB_PDOR.B9 = 1;
       RE1 = ~ RE1;
       Delay_ms( 50 );
       PTB_PDOR.B9 = 0;
  }

  // On button down pressed
  static void button_down( void )
  {
       PTB_PDOR.B9 = 1;
       RE2 = ~ RE2;
       Delay_ms( 50 );
       PTB_PDOR.B9 = 0;
  }

  // On button left pressed 
  static void button_left( void )
  {
       PTB_PDOR.B9 = 1;
       RE3 = ~ RE3;
       Delay_ms( 50 );
       PTB_PDOR.B9 = 0;
  }

  // On button right pressed
  static void button_right( void )
  {
       PTB_PDOR.B9 = 1;
       RE4 = ~ RE4;
       Delay_ms( 50 );
       PTB_PDOR.B9 = 0;
  }

  void main()
  {
      system_init();
      Delay_ms( 100 );
      // Callback functions
      hexiwear_uart_messaging_callback(PT_PRESS_UP, button_up);
      hexiwear_uart_messaging_callback(PT_PRESS_DOWN, button_down);
      hexiwear_uart_messaging_callback(PT_PRESS_LEFT, button_left);
      hexiwear_uart_messaging_callback(PT_PRESS_RIGHT, button_right);

      while( 1 )
      {
           hexiwear_uart_messaging_process();  // Registering button pressing actions
      }
  }
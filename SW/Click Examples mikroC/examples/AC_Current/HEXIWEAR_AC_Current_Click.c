  /*******************************************************************************
  * Title                 :   HEXIWEAR / AC Current Click / DOCKING STATION
  * Filename              :   HEXIWEAR_AC_Current_Click.c
  * Author                :   Stefan Popovic
  * Origin Date           :   Jan / 2017
  * Notes                 :
  *
  *                          - Place AC Current click board on mikroBUS slot 3
  *                          - This example demonstrates measuring of AC current
  *                            with the use of CT sensor
  /******************************************************************************
  * Includes
  *******************************************************************************/
  #include "OLED_driver.h"
  #include "OLED_resources.h"
  #include "UART_Messaging.h"
  #include "common_screen_objects.h"
  #include "ac_current.h"
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
  sbit AC_CURRENT_CS at PTC_PTOR.B2;

  char txt_value[ 20 ];
  char txt_unit[] = "mA";
  float ac_current;
  /******************************************************************************
  * Function Prototypes
  *******************************************************************************/

  /******************************************************************************
  * Function Definitions
  *******************************************************************************/

  void system_init()
{
    // OLED Init
    OLED_Init();
    OLED_FillScreen(OLED_COLOR_BLACK);

    // GPIO Init
    GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_2);

    // SPI Init
    SPI0_Init_Advanced(8000000, _SPI_CFG_MASTER |
                                _SPI_CFG_FRAME_SIZE_8BITS |
                                _SPI_CFG_CLK_IDLE_LOW |
                                _SPI_CFG_CLK_PHASE_CAPT_LEADING |
                                _SPI_CFG_MSB_FIRST,
                                &_GPIO_Module_SPI0_PC5_7_6);

    // Display text
    OLED_DrawBox(0, 0, 96, 15, OLED_COLOR_BLUE);
    OLED_SetFont(guiFont_Exo_2_Condensed10x16_Regular, OLED_COLOR_WHITE, 0);
    OLED_WriteText("AC   CURRENT", 15, 0);
    OLED_WriteText("AC current value", 5, 25);
    OLED_WriteText(txt_unit, 75, 60);
  }
  // Writes current ac current value on OLED
  static void write_ac_current_value( void )
  {
      OLED_DrawBox(15, 60, 60, 20, OLED_COLOR_BLACK);
      FloatToStr(ac_current, txt_value);
      OLED_WriteText(txt_value, 15, 60);           // Write text value on screen
  }

  void main()
  {
      system_init();
      ac_current_init();
      Delay_ms( 100 );

      // Reading and displaying AC current value in an endless loop
      while ( true )
      {
          ac_current = 0;
          ac_current = ac_current_get_mA( 220 );
          write_ac_current_value();
          Delay_ms( 1000 );
      }
  }

  /******************************************************************************
  * End Of All Functions
  *******************************************************************************/
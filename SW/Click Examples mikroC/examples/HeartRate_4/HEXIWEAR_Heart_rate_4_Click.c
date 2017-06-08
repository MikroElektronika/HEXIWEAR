/*******************************************************************************
* Title                 :   HEXIWEAR / Heart rate 4 Click / DOCKING STATION
* Filename              :   HEXIWEAR_Heart_rate_4_Click.c
* Author                :   Stefan Popovic
* Origin Date           :   Feb / 2017
* Notes                 :
*
*                          - Place Heart rate 4 click board on mikroBUS slot 1
*                          - Place USB UART click board on mikroBUS slot 2 or 3
*                          - This example demonstrates measuring of Heart rate
*                            pulse amplitude using RED LED and sending data to
*                            MikroPlot via UART module
*                          - Includes example.pld
/******************************************************************************
* Includes
*******************************************************************************/
#include "OLED_driver.h"
#include "OLED_resources.h"
#include "UART_Messaging.h"
#include "heartrate4_hw.h"
/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/
#define PROXIMITY_THRESHOLD    32000
/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
sbit HEART_RATE_4_INT   at PTB_PDIR.B13;
sbit HEXI_RED_LED    at PTC_PDOR.B8;
sbit HEXI_GREEN_LED  at PTD_PDOR.B0;

char txt_val[ 18 ];
char txt_milis[ 18 ];
uint8_t sample_num = 0;
bool read_f = false;
bool stop_f = false;
bool start_f = false;
bool no_finger_f = true;
static uint32_t miliseconds_counter = 0;
uint32_t red_sample = 0;
/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Function Definitions
*******************************************************************************/
static void system_init()
{
  // GPIO Init
  GPIO_Digital_Input( &PTB_PDIR, _GPIO_PINMASK_13 );
  GPIO_Digital_Output( &PTC_PDOR, _GPIO_PINMASK_8 );
  GPIO_Digital_Output( &PTD_PDOR, _GPIO_PINMASK_0 );
  
  // HEXIWEAR LEDs
  HEXI_RED_LED   = 1;
  HEXI_GREEN_LED = 1;
  
  // UART Initialization
  UART3_Init_Advanced( 57600, _UART_8_BIT_DATA, _UART_NOPARITY,
                       _UART_ONE_STOPBIT, &_GPIO_Module_UART3_PC16_17 );
  Delay_ms( 100 );

  // I2C Initialization
  I2C0_Init_Advanced( 400000, &_GPIO_Module_I2C0_PD8_9  );

  // OLED Init
  OLED_Init();
  OLED_SetFont( guiFont_Exo_2_Condensed10x16_Regular, OLED_COLOR_RED, 0 );
  OLED_DrawImage( heart_rate_bmp, 0, 0 );
  BOX( 0, 85, 96, 11, OLED_COLOR_WHITE );
  LOG_OLED( "PLACE FINGER", 12, 82 );
  }

  void InitTimer0()
  {
    SIM_SCGC6 |= (1 << PIT);
    NVIC_IntEnable(IVT_INT_PIT0);
    PIT_MCR = 0x00;
    PIT_LDVAL0 = 119999;
    PIT_TCTRL0 |= 2;
    PIT_TCTRL0 |= 1;
  }

  void main( void )
  {
    system_init();
    hr4_init();
    hr4_set_registers();
    
    // Polling for new data in an endless loop 
    while ( true )
    {
      // Polling for new data by reading the Interrupt Status 1 
      if ( hr4_is_new_fifo_data_ready() & 0x1 ) read_f = true;

      if ( read_f )                          // If new data is ready in FIFO
      {
         read_f = false;

         if ( !start_f )                     // First start
         {
            start_f = true;
            InitTimer0();                    // Initializing Timer 0
            LOG_UART("START\r\n");           // Sending START command to uPlot
         }

         red_sample = hr4_read_red();        // Read RED sensor data

         LongToStr(miliseconds_counter , txt_milis);
         LongToStr(red_sample , txt_val);
         Ltrim(txt_val);
         Ltrim(txt_milis);

         // If sample pulse amplitude is under threshold value ( PROX mode )
         if ( red_sample > 0 && red_sample < PROXIMITY_THRESHOLD )
         {
           stop_f = true;
           
           HEXI_GREEN_LED = 1;
           HEXI_RED_LED = 0;
           
           if ( !no_finger_f )
           {
             OLED_SetFont( guiFont_Exo_2_Condensed10x16_Regular,
                            OLED_COLOR_RED, 0 );
             BOX( 0, 85, 96, 11, OLED_COLOR_WHITE );
             LOG_OLED( "PLACE FINGER", 12, 82 );
           }

           no_finger_f = true;
           
         }

         // If finger is detected ( we are in active heart rate mode )
         else if( red_sample != 0)
         {
            stop_f = false;
            
            HEXI_GREEN_LED = 0;
            HEXI_RED_LED = 1;
            
            if ( no_finger_f )
            {
            OLED_SetFont( guiFont_Exo_2_Condensed10x16_Regular, 
                          OLED_COLOR_GREEN, 0 );
            BOX( 0, 85, 96, 11, OLED_COLOR_WHITE );
            LOG_OLED( "SENDING...", 25, 82 );
            }

            no_finger_f = false;

            // Sending data to MikroPlot in format: [ pulse_value, milis ]
            LOG_UART(txt_val);
            LOG_UART(",");
            LOG_UART(txt_milis);
            LOG_UART("\r\n");              
         }
      }
    }
  }
  void Timer0_interrupt() iv IVT_INT_PIT0 
  {
    PIT_TFLG0.TIF = 1;
    if (!stop_f)
      {
        miliseconds_counter++;
      }
  }
/******************************************************************************
* End Of All Functions
*******************************************************************************/
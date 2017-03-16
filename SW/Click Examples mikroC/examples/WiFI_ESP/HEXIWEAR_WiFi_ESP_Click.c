/*******************************************************************************
* Title                 :   HEXIWEAR / WiFi ESP Click / DOCKING STATION
* Filename              :   HEXIWEAR_WiFi_ESP_Click.c
* Author                :   Stefan Popovic
* Origin Date           :   Mar / 2017
* Notes                 :
*
*                          - Place WiFi ESP click board on mikroBUS slot 1
*                          - This example demonstrates the functionality of
*                            WiFi ESP as a server
*                          - Log is being sent by pressing left and right button
*                            which consequently changes LED state
*                          - Include example.pld
/******************************************************************************
* Includes
*******************************************************************************/
#include "OLED_driver.h"
#include "OLED_resources.h"
#include "UART_Messaging.h"
#include <stdbool.h>
/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/
#define WAIT_TIME_FOR_CONN          20
/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
// Module connections
sbit WIFI_ESP_EN     at PTC_PDOR.B4;
sbit WIFI_ESP_RST    at PTB_PDOR.B11;
sbit HEXI_RED_LED    at PTC_PDOR.B8;

// Responses to parse
const OK = 1;
const ERROR = 2;
const NO_CHANGE = 3;
const FAIL = 4;
const READY = 5;
const SEND = 6;

char ip_address[40];
unsigned short i;
unsigned short DataReady;
unsigned int oldstate;
unsigned int length;

char txt_val[ 10 ];
char state;
char response_rcvd;
char responseID, response = 0;
char is_receiving_data = 0;
char LED_switching = 0;
int cntr = 0;

// Change following information to match your network settings
unsigned char *SSID = "MikroE Public";
unsigned char *password = "mikroe.guest";
char txt1[] = "<a href=\"https://www.mikroe.com/\">MikroElektronika</a>";
char txt2[] = "<h1 style=\"color:red;\">WiFi ESP click board / HEXIWEAR </h1>";
char txt3[] = "<h1>Server example</h1";
char txt4[] = "<p> RED LED is ";
bool LED_change = false;
char txt_state[9] = "OFF</p>";
char data_[ 500 ] = { 0 };
/******************************************************************************
* Function Prototypes
*******************************************************************************/
extern void WiFI_Configure();
char Get_Response( void );
static void WiFi_Init( void );
static void sending_data( void );
static void WiFi_Send( void );
static void button_left( void );
static void button_right( void );
static void system_init( void );
/******************************************************************************
* Function Definitions
*******************************************************************************/

// Get response
 char Get_Response( void )
{
  if (response_rcvd)
  {
    response_rcvd = 0;
    return responseID;
  }
  else
    return 0;
}

static void WiFi_Init( void )
{
  WIFI_ESP_EN = 1;
  delay_ms(500);
  WIFI_ESP_RST = 0;                                     // Perform reset procedure
  delay_ms(500);
  WIFI_ESP_RST = 1;
  Delay_ms(2000);
}

void sending_data( void )
{
   UART2_Write_Text("AT+CIPSEND=0");
   UART2_Write_Text(",");
   UART2_Write_Text( txt_val );
   UART2_Write(0x0D);
   UART2_Write(0x0A);
   Delay_ms(100);
   UART2_Write_Text( data_ );

   Delay_ms( 200 );

   UART2_Write_Text("AT+CIPSEND=1");
   UART2_Write_Text(",");
   UART2_Write_Text( txt_val );
   UART2_Write(0x0D);
   UART2_Write(0x0A);
   Delay_ms(100);
   UART2_Write_Text( data_ );

   Delay_ms( 200 );

   UART2_Write_Text("AT+CIPSEND=2");
   UART2_Write_Text(",");
   UART2_Write_Text( txt_val );
   UART2_Write(0x0D);
   UART2_Write(0x0A);
   Delay_ms(100);
   UART2_Write_Text( data_ );

   Delay_ms( 200 );

   UART2_Write_Text("AT+CIPSEND=3");
   UART2_Write_Text(",");
   UART2_Write_Text( txt_val );
   UART2_Write(0x0D);
   UART2_Write(0x0A);
   Delay_ms(100);
   UART2_Write_Text( data_ );
}

static void WiFi_Send()
{
    if( !LED_switching ) {

    length += strlen( txt1 );
    length += strlen( txt2 );
    length += strlen( txt4 );
    length += strlen( txt_state );
    
    IntToStr( length, txt_val );
    Ltrim( txt_val );

    strcat( data_, txt1 );
    strcat( data_, txt2 );
    strcat( data_, txt4 );
    strcat( data_, txt_state );
    Rtrim( data_ );

    sending_data();
    }
    else
    {
       length += strlen( txt4 );
       length += strlen( txt_state );
       strcat( data_, txt4 );
       strcat( data_, txt_state );

       IntToStr( length, txt_val );
       Ltrim( txt_val );
       Rtrim( data_ );

       sending_data();
    }

    strcpy(data_, "");
    length = 0;

    Delay_ms(100);
}

  // On button left pressed
  static void button_left( void )
  {
       PTB_PDOR.B9 = 1;
       Delay_ms( 50 );
       PTB_PDOR.B9 = 0;
       HEXI_RED_LED = 0;
       if ( !strcmp( txt_state, "OFF</p>" ))
       {
          strncpy( txt_state, "ON</p>", 8 );
          WiFi_Send();
        }
  }

  // On button right pressed
  static void button_right( void )
  {
       PTB_PDOR.B9 = 1;
       Delay_ms( 50 );
       PTB_PDOR.B9 = 0;
       HEXI_RED_LED = 1;
        if ( !strcmp( txt_state, "ON</p>" ))
          {
            strncpy( txt_state, "OFF</p>", 8 );
            WiFi_Send();
          }
  }

static void system_init()
{
  // GPIO Direction Configuration
  GPIO_Digital_Output( &PTB_PDOR, _GPIO_PINMASK_11 );
  GPIO_Digital_Output( &PTC_PDOR, _GPIO_PINMASK_4 );
  GPIO_Digital_Output( &PTC_PDOR, _GPIO_PINMASK_8 );
  GPIO_Digital_Output( &PTB_PDOR, _GPIO_PINMASK_9 ); // Vibration PIN
  
  // HEXIWEAR VIBRATION PIN
  PTB_PDOR = 0;

  // HEXIWEAR RED LED
  HEXI_RED_LED = 1;
  
  // Initialize variables
  length = 0;
  state = 0;
  response_rcvd = 0;
  responseID = 0;
  response = 0;
  i = 0;

  // UART Initialization
  UART2_Init_Advanced( 115200, _UART_8_BIT_DATA, _UART_NOPARITY,
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
  BOX( 0, 0, 96, 15, OLED_COLOR_RED );
  OLED_SetFont( guiFont_Exo_2_Condensed10x16_Regular, OLED_COLOR_WHITE, 0 );
  LOG( "WiFi ESP ", 24, 0 );
  OLED_SetFont( guiFont_Tahoma_7_Regular, OLED_COLOR_WHITE, 0 );
  
  // Init UART messaging
  hexiwear_uart_messaging_init();
  }

  void main( void )
  {
    system_init();
    
    hexiwear_uart_messaging_callback(PT_PRESS_LEFT, button_left);
    hexiwear_uart_messaging_callback(PT_PRESS_RIGHT, button_right);
    
    // Initialize WiFI module
    WiFi_Init();

    //Setting WiFi Mode - station mode
    WiFI_Configure();

    state = 100;
    i = 0;
    OLED_SetFont( guiFont_Tahoma_7_Regular, OLED_COLOR_WHITE, 0 );
    LOG("Connect to STAIP", 5, 85);
    
    // Waiting for multiple connections to Server STAIP
    Delay_ms( WAIT_TIME_FOR_CONN * 1000);

    // Sending Initial data to server
    WiFi_Send();

    OLED_SetFont( guiFont_Tahoma_7_Regular, OLED_COLOR_BLACK, 0 );
    LOG("Connect to STAIP!", 5, 85);
    OLED_SetFont( guiFont_Tahoma_7_Regular, OLED_COLOR_RED, 0 );
    LOG("Use Buttons for Log", 5, 85);
    
    LED_switching = 1;

      while( 1 )
      {
        hexiwear_uart_messaging_process();// Registering button pressing actions
      }
  }
  
void WIFI_ESP_RX_ISR() iv IVT_INT_UART2_RX_TX ics ICS_AUTO
{
    char s1 = UART2_S1;
    char tmp = UART2_D;

    if(  s1 & ( 1 << 5 )  )
    {
        switch (state) {
      case 0: {
                response = 0;                     // Clear response
                if (tmp == 'O')
                  state = 1;
                if (tmp == 'E')
                  state = 10;
                if (tmp == 'n')
                  state = 20;
                if (tmp == 'F')
                  state = 30;
                if (tmp == 'A')
                  state = 40;
                if (tmp == '+')
                  state = 54;
                if (tmp == 'r')
                  state = 50;
                if (tmp == '>')
                {
                  state = 0;
                  response = SEND;
                  response_rcvd = 1;
                  responseID = response;
                }
                break;
      }
      case 1: {
                if (tmp == 'K'){
                  response = OK;                // OK
                  state = 2;
                }
                else
                  state = 0;
                break;
      }
      case 10: {
                if (tmp == 'R')
                  state = 11;
                else
                  state = 0;
                break;
      }
      case 11: {
                if (tmp == 'R')
                  state = 12;
                else
                  state = 0;
                break;
      }
      case 12: {
                if (tmp == 'O')
                  state = 13;
                else
                  state = 0;
                break;
      }
      case 13: {
                if (tmp == 'R') {
                  response = ERROR;             // ERROR
                  state = 2;
                }
                else
                  state = 0;
                break;
      }

      case 20: {
                if (tmp == 'o')
                  state = 21;
                else
                  state = 0;
                break;
      }

      case 21: {
                if (tmp == ' ')
                  state = 22;
                else
                  state = 0;
                break;
      }

      case 22: {
                if (tmp == 'c')
                  state = 23;
                else
                  state = 0;
                break;
      }

      case 23: {
                if (tmp == 'h')
                  state = 24;
                else
                  state = 0;
                break;
      }

      case 24: {
                if (tmp == 'a')
                  state = 25;
                else
                  state = 0;
                break;
      }

      case 25: {
                if (tmp == 'n')
                  state = 26;
                else
                  state = 0;
                break;
      }

      case 26: {
                if (tmp == 'g')
                  state = 27;
                else
                  state = 0;
                break;
      }

      case 27: {
                if (tmp == 'e'){
                  response = NO_CHANGE;         // NO CHANGE
                  state = 2;
                }
                else
                  state = 0;
                break;
      }

      case 30: {
                if (tmp == 'A')
                  state = 31;
                else
                  state = 0;
                break;
      }

      case 31: {
                if (tmp == 'I')
                  state = 32;
                else
                  state = 0;
                break;
      }

      case 32: {
                if (tmp == 'L') {
                  response = FAIL;              // FAIL
                  state = 2;
                }
                else
                  state = 0;
                break;
      }

      case 40: {
                if (tmp == 'T')
                  state = 41;
                else
                  state = 0;
                break;
      }

      case 41: {
                if (tmp == '+')
                  state = 42;
                else
                  state = 0;
                break;
      }

      case 42: {
                if (tmp == 'C')
                  state = 43;
                else
                  state = 0;
                break;
      }

      case 43: {
                if (tmp == 'I')
                  state = 44;
                else
                  state = 0;
                break;
      }

      case 44: {
                if (tmp == 'F')
                  state = 45;
                else
                  state = 0;
                break;
      }

      case 45: {
                if (tmp == 'S')
                  state = 46;
                else
                  state = 0;
                break;
      }

      case 46: {
                if (tmp == 'R')
                  state = 47;
                else
                  state = 0;
                break;
      }

      case 47: {
                if (tmp == 10) {
                  state = 48;
                  i = 0;
                }
                else if (tmp == 13){

                }
                else
                  state = 0;
                break;
      }

      case 48: {
                if (tmp == 13){
                  state = 3;
                  response = OK;
                }
                else {
                  ip_address[i] = tmp;              // get IP address
                  i++;
                }
                break;
      }

      case 50: {
                if (tmp == 'e')
                  state = 51;
                else
                  state = 0;
                break;
      }

      case 51: {
                if (tmp == 'a')
                  state = 52;
                else
                  state = 0;
                break;
      }

      case 52: {
                if (tmp == 'd')
                  state = 53;
                else
                  state = 0;
                break;
      }

      case 53: {
                if (tmp == 'y') {
                  response = READY;              // READY
                  state = 2;
                }
                else
                  state = 0;
                break;
      }

       case 54: {
                state = 0;
                response = SEND;
                response_rcvd = 1;
                responseID = response;
                break;
      }

      case 2: {
                if (tmp == 13)
                  state = 3;
                else
                  state = 0;
                break;
      }

      case 3: {
                if (tmp == 10){
                  response_rcvd = 1;
                  responseID = response;
                }
                state = 0;
                break;
      }

      default: {
                state = 0;
                break;
      }
    }

  }
}
  
/******************************************************************************
* End Of All Functions
*******************************************************************************/
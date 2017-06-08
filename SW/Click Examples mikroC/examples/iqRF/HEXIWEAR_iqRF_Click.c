/*******************************************************************************
* Title                 :   HEXIWEAR / iqRF click with Thermo K and FAN click
* Filename              :   HEXIWEAR_iqRF_Click.c
* Author                :   Stefan Popovic
* Origin Date           :   Apr / 2017
* Note                  : - This example demonstrates iqRF click working 
*                           as transciever by sending and receiving byte packets
*                         - Use it in combination with another iqRF example 
*                           
*                         - By reading temperature from the Thermo K click's
*                           sensor, we are periodically updating another distant 
*                           iqRF click about current temperature value while
*                           constantly listening for byte packets.
*                           In case of received value 1, FAN is turned ON
*                           to cool down the temperature, and in case of 0,
*                           FAN is turned OFF. To enable these functions, we 
*                           are using FAN click board.
*
* Setting               : - Place iqRF click board on mikroBUS slot 1
*                         - Place Thermo K click board on mikroBUS slot 2
*                         - Place FAN click board on mikroBUS slot 3
*
/******************************************************************************
* Includes
*******************************************************************************/
#include "OLED_driver.h"
#include "OLED_resources.h"
#include "UART_Messaging.h"
#include "MCP9600.h"
#include "fan_click.h"
#include <stdbool.h>
#include <stdint.h>

/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/*******************************************************************************
* Module Typedefs
*******************************************************************************/

/*******************************************************************************
* Module Variable Definitions
*******************************************************************************/
bool fanRunning = false;
uint8_t thermoStatus;
uint8_t textValue[10];
uint8_t label[10];
uint8_t oldText[10];
uint8_t tempData[10];
uint8_t tempDataRdy;
uint8_t res;
uint16_t fanRPM;
float temp;
double fanSpeed;

/*******************************************************************************
* Function Prototypes
*******************************************************************************/
static uint8_t writeData( uint8_t RegAddr, uint8_t _data );
static uint8_t readData( uint8_t RegAddr );
static uint8_t readStatus();
static float readTemperature();
static void updateLabel( uint8_t *pNewText, int x, int y, uint8_t* pLabel );
static void systemInit();
/*******************************************************************************
* Function Definitions
*******************************************************************************/

/*******************************************************************************
* Function writeData(RegAddr)
*-------------------------------------------------------------------------------
* Overview: Function writes Data to MCP9600
* Input: Register address, data
* Output: Nothing
*******************************************************************************/
uint8_t writeData( uint8_t RegAddr, uint8_t _data )
{
   // Register address
  tempData[0] = RegAddr; 
  // Data to be written into register                                                       
  tempData[1] = _data;
  Delay_us( 50 ); 
  // Issue I2C start signal  
  I2C_Start();     
  // Send two bytes (tempData[0] and tempData[1])                                                            
  I2C_Write( MCP9600_I2C_ADDR, tempData, 2, END_MODE_STOP );                    
}

/*******************************************************************************
* Function readData(RegAddr)
*-------------------------------------------------------------------------------
* Overview: Function gets Data from MCP9600
* Input: Register address
* Output: Value from desired register
*******************************************************************************/
uint8_t readData( uint8_t RegAddr )
{
  // Register address
  tempData[0] = RegAddr;                          

  // Issue I2C start signal
  I2C_Start();             
  // Send byte (tempData[0])                     
  I2C_Write( MCP9600_I2C_ADDR, tempData, 1, END_MODE_RESTART );              
  Delay_us( 50 );                                                
  // Read register data value and store it in tempData              
  I2C_Read( MCP9600_I2C_ADDR, tempData, 1, END_MODE_STOP );                      

  // Return MCP9600 Data value
  return tempData[ 0 ];                           
}

/*******************************************************************************
* Function readStatus
*-------------------------------------------------------------------------------
* Overview: Function gets Data from MCP9600
* Input: Register address
* Output: Value from desired register
*******************************************************************************/
uint8_t readStatus()
{
  uint8_t DataSum;

  // Register address
  tempData[0] = MCP9600_Status;                                                

  // Issue I2C start signal
  I2C_Start();                                                                  
  // Send byte (tempData[0])
  I2C_Write( MCP9600_I2C_ADDR, tempData, 1, END_MODE_RESTART );                 
  Delay_us( 50 );                                                               
  // Read register data value and store it in tempData
  I2C_Read( MCP9600_I2C_ADDR, tempData, 1, END_MODE_STOP );                     
  DataSum = tempData[ 0 ];
  // Return MCP9600 Data value
  return DataSum;                                                                
}

/*******************************************************************************
* Function readTemperature()
*-------------------------------------------------------------------------------
* Overview: Function gets Thermocouple Temperature from MCP9600
* Input: Nothing
* Output: Thermocouple Temperature
*******************************************************************************/
float readTemperature()
{
  float Temperature;

  // Thermocouple Temperature register
  tempData[0] = MCP9600_TH;                                                     

  // Issue I2C start signal
  I2C_Start();                                                                  
  // Send byte (tempData[0])
  I2C_Write( MCP9600_I2C_ADDR, tempData, 1, END_MODE_RESTART );                 
  Delay_us( 50 );                                                               
  // Read thermocouple temperature and store it in tempData
  I2C_Read( MCP9600_I2C_ADDR, tempData, 2, END_MODE_STOP );                     

  if( (tempData[0] & 0x80) == 0x80 )
  {    
    // TA < 0 C
    // Clearing sign
    tempData[0] = tempData[0] & 0x7F;                                           
    Temperature = 1024 - ( tempData[0] * 16 + tempData[1] / 16 );
  }
  else    
{   // TA > 0 C
    Temperature = ( tempData[0] * 16 + (float)tempData[1] / 16 );               
  }
  // Return Thermocouple temperature data
  return Temperature;                                                           
}

/*******************************************************************************
* Function updateLabel(uint8_t *newText, int x, int y, uint8_t* label)
*-------------------------------------------------------------------------------
* Overview: Function writes text on display and erase old text
* Input: Nothing
* Output: Updated text
*******************************************************************************/
void updateLabel( uint8_t *newText, int x, int y, uint8_t* label )
{
  OLED_SetFont( guiFont_Tahoma_10_Regular , OLED_COLOR_BLACK, 0 );
  OLED_WriteText( label, x, y );
  strcpy( label, newText );
  OLED_SetFont( guiFont_Tahoma_10_Regular , OLED_COLOR_WHITE, 0 );
  OLED_WriteText( label, x, y );
}

/*******************************************************************************
 * System Initialization
 *-------------------------------------------------------------------------------
 * Initializing I2C and UART,
 * enabling interrupt and OLED initialization
 ******************************************************************************/
static void systemInit( void )
{
    // I2C Initialization
    I2C0_Init_Advanced( 100000, &_GPIO_Module_I2C0_PD8_9 );
    delay_ms( 100 );

    // UART Initialization
    UART2_Init_Advanced( 9600, _UART_8_BIT_DATA, _UART_NOPARITY,
                         _UART_ONE_STOPBIT, &_GPIO_Module_UART2_PD3_2 );
    Delay_ms( 100 );

    // OLED Initialization
    OLED_Init();
    OLED_FillScreen( OLED_COLOR_BLACK );
    OLED_DrawImage( &thermo_K_bmp, 0, 25 );

    // Display text
    OLED_DrawBox( 0, 0, 96, 15, OLED_COLOR_YELLOW );
    OLED_SetFont( guiFont_Exo_2_Condensed10x16_Regular, OLED_COLOR_BLACK, 0 );
    OLED_WriteText( "iqRF click", 25, 0 );
    OLED_DrawBox( 46, 78, 21, 13, OLED_COLOR_YELLOW );
    OLED_WriteText( "FAN", 46, 77 );
    OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_RED, 0 );
    OLED_WriteText( "OFF", 75, 78 );
    OLED_SetFont( guiFont_Tahoma_7_Regular, OLED_COLOR_WHITE, 0 );

    // UART Interrupt enabling
    UART2_C2 |= 1 << 5;
    NVIC_IntEnable( IVT_INT_UART2_RX_TX );
    EnableInterrupts();
}

/*******************************************************************************
 * Main function
 ******************************************************************************/
void main( void )
{
    uint8_t byte_send = 0;
    uint8_t i = 0;
    
    systemInit();

    // FAN click Initialization and Setting 
    fan_click_init( EMC2301_I2C_ADDR );
    fan_click_config_range( RPM_MIN_4000 );
    fan_click_config_enableFSC( false );
    fan_click_set_valid_tach( 12000 );
    fan_click_settings( 0.0f );
    
    while( true )
   {

    // FAN control
    if(fanRunning)
    {
     OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_BLACK, 0 );
     OLED_WriteText("OFF", 75, 78);
     OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_GREEN, 0 );
     OLED_WriteText("ON", 75, 78);
     OLED_SetFont( guiFont_Tahoma_7_Regular, OLED_COLOR_WHITE, 0 );

     
     fanRPM = fan_click_get_tach();
     fan_click_set_target_tach( 12000 );
     fan_click_settings( 200.0f );
    }
    else
    {
     OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_BLACK, 0 );
     OLED_WriteText("ON", 75, 78);
     OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_RED, 0 );
     OLED_WriteText("OFF", 75, 78);
     OLED_SetFont( guiFont_Tahoma_7_Regular, OLED_COLOR_WHITE, 0 );

 
     fanRPM = fan_click_get_tach();
     fan_click_set_target_tach( 12000 );
     fan_click_settings( 0.0f );
     }

    
    // Reading ambient temperature from Thermo K click 
    thermoStatus = readStatus();
    tempDataRdy = ( thermoStatus & 0x40 );
    temp =  readTemperature();
    
    if( temp > 50 )
    {
     OLED_SetFont( guiFont_Tahoma_7_Regular, OLED_COLOR_RED, 0 );
    }
    else
    {
     OLED_SetFont( guiFont_Tahoma_7_Regular, OLED_COLOR_WHITE, 0 );
    }

    // Is Temperature Data ready?
    if ( tempDataRdy )
    {   
      // Format Temperature Data and store it to textual value                                                                       
      sprintf( textValue, "%2.1f  C", readTemperature() );  
      // Compare oldText and textual value                         
      res = strcmp( textValue, oldText );                                            

      // If oldText and current text value are not equal
      if( res != 0 )
      {  
        // Write temperature value on display                                                                    
        updateLabel( textValue, 55, 40, label );
        // Copy textual value to oldText string array                                     
        strcpy( oldText, textValue );                                             
      }
    }
    

    
    
    // Sending commands via UART so that iqRF TR can broadcast to other iqRF's
    byte_send = temp;
    UART2_Write( byte_send );
  
    // Delay before new reading
    Delay_ms( 400 );
   }
}

void iqRF_RX_ISR() iv IVT_INT_UART2_RX_TX ics ICS_AUTO
{
    uint8_t s1 = UART2_S1;
    uint8_t tmp = UART2_D;

    if(  s1 & ( 1 << 5 )  )
    {
        if( tmp == 1 )
        {
         // Start command received
         fanRunning = true;
        }
        else if( tmp == 0)
        {
         // Stop command received
         fanRunning = false;
        }

    }
}
/******************************************************************************
* End Of All Functions
*******************************************************************************/
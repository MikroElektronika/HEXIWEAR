/**
 * @file                                        	HEXIWEAR_THERMO_K_click.c
 * @brief                   THERMO K Example
 *
 * @par
 * Example for Thermo K click board on hexiwear docking station.
 *
 ******************************************************************************/

#include "MCP9600.h"
#include "OLED_driver.h"
#include "picture.h"

char tmp_data[10];

char _txt[10];
char old_txt[10];
char lab1[10] = {0};
char lab2[10] = {0};
char res;
char Temp_Data_Ready;
char status;

char debug;

/*******************************************************************************
* Function Write_MCP9600_Data(RegAddr)
* ------------------------------------------------------------------------------
* Overview: Function writes Data to MCP9600
* Input: Register address, data
* Output: Nothing
*******************************************************************************/
char Write_MCP9600_Data( char RegAddr, char _data )
{
  tmp_data[0] = RegAddr;                                                        // Register address
  tmp_data[1] = _data;

  I2C_Start();                                                                  // Issue I2C start signal
  I2C_Write( MCP9600_I2C_ADDR, tmp_data, 2, END_MODE_STOP );                    // Send two bytes (tmp_data[0] and tmp_data[1])
}

/*******************************************************************************
* Function Read_MCP9600_Data(RegAddr)
* ------------------------------------------------------------------------------
* Overview: Function gets Data from MCP9600
* Input: Register address
* Output: Value from desired register
*******************************************************************************/
char Read_MCP9600_Data( char RegAddr )
{
  tmp_data[0] = RegAddr;                                                        // Register address

  I2C_Start();                                                                  // Issue I2C start signal
  I2C_Write( MCP9600_I2C_ADDR, tmp_data, 1, END_MODE_RESTART );                 // Send byte (tmp_data[0])
  Delay_us( 50 );                                                               // delay 50 us
  I2C_Read( MCP9600_I2C_ADDR, tmp_data, 1, END_MODE_STOP);                      // Read register data value and store it in tmp_data

  return tmp_data[0];                                                           // Return MCP9600 Data value
}

/*******************************************************************************
* Function Read_MCP9600_Status
* ------------------------------------------------------------------------------
* Overview: Function gets Data from MCP9600
* Input: Register address
* Output: Value from desired register
*******************************************************************************/
char Read_MCP9600_Status()
{
  char DataSum;

  tmp_data[0] = MCP9600_Status;                                                 // Register address

  I2C_Start();                                                                  // Issue I2C start signal
  I2C_Write( MCP9600_I2C_ADDR, tmp_data, 1, END_MODE_RESTART );                 // Send byte (tmp_data[0])
  Delay_us( 50 );                                                               // delay 50 us
  I2C_Read( MCP9600_I2C_ADDR, tmp_data, 1, END_MODE_STOP );                     // Read register data value and store it in tmp_data

  DataSum = tmp_data[0];

  return DataSum;                                                                 // Return MCP9600 Data value
}

/*******************************************************************************
* Function Read_Temperature()
* ------------------------------------------------------------------------------
* Overview: Function gets Thermocouple Temperature from MCP9600
* Input: Nothing
* Output: Thermocouple Temperature
*******************************************************************************/
float Read_Temperature()
{
  float Temperature;

  tmp_data[0] = MCP9600_TH;                                                     // Thermocouple Temperature register

  I2C_Start();                                                                  // Issue I2C start signal
  I2C_Write( MCP9600_I2C_ADDR, tmp_data, 1, END_MODE_RESTART );                 // Send byte (tmp_data[0])
  Delay_us( 50 );                                                               // delay 50 us
  I2C_Read( MCP9600_I2C_ADDR, tmp_data, 2, END_MODE_STOP );                     // Read thermocouple temperature and store it in tmp_data

  if( (tmp_data[0] & 0x80) == 0x80 )
  {                                             // TA < 0°C
    tmp_data[0] = tmp_data[0] & 0x7F;                                           // Clear SIGN
    Temperature = 1024 - ( tmp_data[0] * 16 + tmp_data[1] / 16 );
  }
  else                                                                          // TA > 0°C
    Temperature = ( tmp_data[0] * 16 + (float)tmp_data[1] / 16 );               // Temperature = Ambient Temperature (°C)

  return Temperature;                                                           // Return Thermocouple temperature data
}

/*******************************************************************************
* Function updateLabel(char *newText, int x, int y, char* lbl)
* ------------------------------------------------------------------------------
* Overview: Function writes text on display and erase old text
* Input: Nothing
* Output: Updated text
*******************************************************************************/
void updateLabel( char *newText, int x, int y, char* lbl )
{
  OLED_SetFont( guiFont_Tahoma_10_Regular , OLED_COLOR_BLACK, 0 );
  OLED_WriteText( lbl, x, y );
  strcpy( lbl, newText );
  OLED_SetFont( guiFont_Tahoma_10_Regular, OLED_COLOR_WHITE, 0 );
  OLED_WriteText( lbl, x, y );
}

//******************************************************************************
// Main function
//******************************************************************************
void main()
{
  OLED_Init();                                                                  // Initialize OLED display
  I2C0_Init_Advanced( 100000, &_GPIO_Module_I2C0_PD8_9 );
  delay_ms( 200 );

  OLED_FillScreen( OLED_COLOR_BLACK );
  OLED_DrawImage( thermo_K_bmp, 0, 10 );
  OLED_SetFont( guiFont_Tahoma_10_Regular, OLED_COLOR_WHITE, 0 );
  OLED_WriteText( "Thermo K click", 5, 75 );

  while(1)
  {
    status = Read_MCP9600_Status();
    Temp_Data_Ready = (status & 0x40);

    if ( Temp_Data_Ready )
    {                                                                           // Check is Temperature Data ready
      sprintf( _txt, "%2.1fºC", Read_Temperature() );                           // Format Temperature Data and store it to txt
      res = strcmp( _txt, old_txt );                                            // Compare old_txt and txt

      if( res != 0 )
      {                                                                         // If old_txt and txt are not equal
        updateLabel( _txt, 55, 20, lab1 );                                      // Write temperature value on display
        strcpy( old_txt, _txt );                                                // Copy txt to old_txt string array
      }
    }
    delay_ms( 500 );
  }
}

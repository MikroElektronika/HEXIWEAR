/****************************************************************************
* Title                 :   BUZZ click
* Filename              :   BUZZ.c
* Author                :   UC
* Origin Date           :   12/05/2016
* Notes                 :   BUZZ Example
*****************************************************************************/
/**************************CHANGE LIST **************************************
*
*    Date    Software Version    Initials       Description
*  12/05/16       1.0.0            UC        Interface Created.
*
*****************************************************************************/
/**
 * @file BUZZ.c
 * @brief <h2> BUZZ Example </h2>
 *
 * @par
 * Example for <a href="http://www.mikroe.com">MikroElektronika's</a>
 * BUZZ click board.
 */

/**
 * @page LIB_INFO Library Info
 * @date        12 May 2016
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
 * <li><b> Ext. Modules  </b> :      BUZZ Click                 </li>
 * <li><b> SW            </b> :      MikroC PRO for ARM 4.7.1    </li>
 * </ul>
 */

/**
 * @mainpage
 * <h3> BUZZ click example using HEXIWEAR </h3>
 * @par Place BUZZ Click into the mikroBUS socket 3 on the docking station.
 * Press bottom-left button on hexiwear for playing a melody
 *
 * <h3> BUZZ Features </h3>
 * @par BUZZ click, Hexiwear Docking Station
 */

/******************************************************************************
* Includes
*******************************************************************************/

#include "OLED_driver.h"
#define MAX_SIZE  16

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/

int i;
int n;
unsigned long DiodeArray[MAX_SIZE];
unsigned long TempColor;
sbit RGBLed_Data at PTB_PDOR.B11;         // Set data port

/******************************************************************************
* Function Prototypes
*******************************************************************************/

void RGBLed_ZeroBit();
void RGBLed_OneBit();
void RGBLed_ResetDelay();
void RGBLed_InitDiode();
void RGBLed_SetColor();
void RGBLed_SetDiode();
void RGBLed_InitHW();
void Delay_time();
void Snake();
void Snake_return();
void FillScreen();
/******************************************************************************
* Private Function Definitions
*******************************************************************************/

/******************************************************************************
* Public Function Definitions
*******************************************************************************/

void RGBLed_ZeroBit() {
  RGBLed_Data = 1;
  Delay_Cyc(3);
  RGBLed_Data = 0;
  Delay_Cyc(7);
}

void RGBLed_OneBit() {
  RGBLed_Data = 1;
  Delay_Cyc(7);
  RGBLed_Data = 0;
  Delay_Cyc(6);
}

void RGBLed_ResetDelay() {
  Delay_50us();
  Delay_10us();
}

void RGBLed_InitDiode(unsigned long ARGBColor, unsigned long * AdiodeArray) {
  *AdiodeArray = (ARGBColor & 0x000000FF) | ((ARGBColor >> 16) << 8) | ((ARGBColor >> 8) << 16);
}

void RGBLed_SetColor(unsigned long * AdiodeArray) {
  signed char i;

  for (i = 23; i >= 0; i--) {
    if (( (*AdiodeArray) & (1ul << i)) == 0) {
      RGBLed_ZeroBit();
    }
    else {
      RGBLed_OneBit();
    }
  }
}

void RGBLed_SetDiode(char ANum, unsigned long AColor, unsigned long * AdiodeArray) {
  char i;

   for (i = 0; i < MAX_SIZE; i++) {
    if (i == (ANum - 1)) {
      RGBLed_InitDiode(AColor, &AdiodeArray[i]);
      RGBLed_SetColor(&AdiodeArray[i]);
    }
    else {
      RGBLed_SetColor(&AdiodeArray[i]);
    }
  }
  RGBLed_ResetDelay();
}

void RGBLed_InitHW() {
  GPIO_Digital_Output( &PTB_PDOR, _GPIO_PINMASK_11);        // Initialize data output pin
}
// Because delay_ms uses only constant variables, we will use this function to change the time delay.
// Change the delay by changing the n variable.
void Delay_time() {
  unsigned int n1;
  for (n1=1; n1<=n; n1++)
  delay_ms(5);
}

// Start snake
void Snake() {
  RGBLed_SetDiode(4, TempColor, DiodeArray);  // Turn on diode 4 with the desired color
  Delay_time();
  RGBLed_SetDiode(3, TempColor, DiodeArray);  // Turn on diode 3 with the desired color
  Delay_time();
  RGBLed_SetDiode(2, TempColor, DiodeArray);  // Turn on diode 2 with the desired color
  Delay_time();
  RGBLed_SetDiode(1, TempColor, DiodeArray);  // Turn on diode 1 with the desired color
  Delay_time();
  RGBLed_SetDiode(5, TempColor, DiodeArray);  // Turn on diode 5 with the desired color
  Delay_time();
  RGBLed_SetDiode(9, TempColor, DiodeArray);  // Turn on diode 9 with the desired color
  Delay_time();
  RGBLed_SetDiode(13, TempColor, DiodeArray); // Turn on diode 13 with the desired color
  Delay_time();
  RGBLed_SetDiode(14, TempColor, DiodeArray); // Turn on diode 14 with the desired color
  Delay_time();
  RGBLed_SetDiode(15, TempColor, DiodeArray); // Turn on diode 15 with the desired color
  Delay_time();
  RGBLed_SetDiode(16, TempColor, DiodeArray); // Turn on diode 16 with the desired color
  Delay_time();
  RGBLed_SetDiode(12, TempColor, DiodeArray); // Turn on diode 12 with the desired color
  Delay_time();
  RGBLed_SetDiode(8, TempColor, DiodeArray);  // Turn on diode 8 with the desired color
  Delay_time();
  RGBLed_SetDiode(7, TempColor, DiodeArray);  // Turn on diode 7 with the desired color
  Delay_time();
  RGBLed_SetDiode(6, TempColor, DiodeArray);  // Turn on diode 6 with the desired color
  Delay_time();
  RGBLed_SetDiode(10, TempColor, DiodeArray); // Turn on diode 10 with the desired color
  Delay_time();
  RGBLed_SetDiode(11, TempColor, DiodeArray); // Turn on diode 11 with the desired color
}
// Return Snake
 void Snake_return ()  {
  RGBLed_SetDiode(11, TempColor, DiodeArray); // Turn on diode 11 with the desired color
  Delay_time();
  RGBLed_SetDiode(10, TempColor, DiodeArray); // Turn on diode 10 with the desired color
  Delay_time();
  RGBLed_SetDiode(6, TempColor, DiodeArray);  // Turn on diode 6 with the desired color
  Delay_time();
  RGBLed_SetDiode(7, TempColor, DiodeArray);  // Turn on diode 7 with the desired color
  Delay_time();
  RGBLed_SetDiode(8, TempColor, DiodeArray);  // Turn on diode 8 with the desired color
  Delay_time();
  RGBLed_SetDiode(12, TempColor, DiodeArray); // Turn on diode 12 with the desired color
  Delay_time();
  RGBLed_SetDiode(16, TempColor, DiodeArray); // Turn on diode 16 with the desired color
  Delay_time();
  RGBLed_SetDiode(15, TempColor, DiodeArray); // Turn on diode 15 with the desired color
  Delay_time();
  RGBLed_SetDiode(14, TempColor, DiodeArray); // Turn on diode 14 with the desired color
  Delay_time();
  RGBLed_SetDiode(13, TempColor, DiodeArray); // Turn on diode 13 with the desired color
  Delay_time();
  RGBLed_SetDiode(9, TempColor, DiodeArray);  // Turn on diode 9 with the desired color
  Delay_time();
  RGBLed_SetDiode(5, TempColor, DiodeArray);  // Turn on diode 5 with the desired color
  Delay_time();
  RGBLed_SetDiode(1, TempColor, DiodeArray);  // Turn on diode 1 with the desired color
  Delay_time();
  RGBLed_SetDiode(2, TempColor, DiodeArray);  // Turn on diode 2 with the desired color
  Delay_time();
  RGBLed_SetDiode(3, TempColor, DiodeArray);  // Turn on diode 3 with the desired color
  Delay_time();
  RGBLed_SetDiode(4, TempColor, DiodeArray);  // Turn on diode 4 with the desired color
  Delay_time();
}

// Fill all the diodes with one color
void FillScreen() {
  unsigned int n2;
  for (n2=1; n2<=16; n2++) {
    RGBLed_SetDiode(n2, TempColor, DiodeArray);
    delay_ms(100);
  }
}

// Main function
 void main()
  {
  OLED_Init();
  OLED_DrawImage( A4x4RGB_bmp, 0, 0 );
  RGBLed_InitHW();            // Initialize RGB HW
  TempColor = 0x002F2F2F;     // White
  FillScreen();               // Fill screen with color
   while(1)
    {
    // Start Snake
    n=20;                       // 20*5ms = 100ms delay
    TempColor = 0x0000002F;     // Blue color
    Snake();
    TempColor = 0x00002F2F;     // Bright blue color
    Snake_return ();

    // Increase Snake Speed 1x
    n=15;                       // 15*5ms = 75ms delay
    TempColor = 0x00002F00;     // Green colcor
    Snake();
    TempColor = 0x002F2F00;     // Yellow color back
    Snake_return();

    // Increase Snake Speed 2x
    TempColor = 0x002F0000;     // Red color
    n=10;                       // 10*5ms = 50ms delay
    Snake();
    TempColor = 0x002F002F;     // Purple color back
    Snake_return ();

    // Increase Snake Speed 3x
    n=5;                        // 5*5ms = 25ms delay
    TempColor = 0x002F2F2F;     // White
    Snake_return ();
    }
  }

/*************** END OF FUNCTIONS *********************************************/
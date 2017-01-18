/****************************************************************************
* Title                 :   MP3 click
* Filename              :   HEXIWEAR_MP3_Click.c
* Author                :   UC
* Origin Date           :   26/04/2016
* Notes                 :   MP3 Click Example
*****************************************************************************/
/**************************CHANGE LIST **************************************
*
*    Date    Software Version    Initials       Description
*  26/04/16       1.0.0            UC        Interface Created.
*
*****************************************************************************/
/**
 * @file HEXIWEAR_MP3_Click.c
 * @brief <h2> MP3 Click Example </h2>
 *
 * @par
 * Example for <a href="http://www.mikroe.com">MikroElektronika's</a>
 * MP3 click board.
 */

/**
 * @page LIB_INFO Library Info
 * @date        26 Apr 2016
 * @author      Uros Cvetinovic
 * @copyright   GNU Public License
 * @version     1.0.0 - Initial testing and verification
 */

/**
 * @page TEST_CFG Test Configurations
 * <h3> Test configuration : </h3>
 * @par
 * <ul>
 * <li><b> MCU           </b> :      MK64FN1M0XXX12               </li>
 * <li><b> Dev. Board    </b> :      HEXIWEAR                     </li>
 * <li><b> Oscillator    </b> :      12 MHz external              </li>
 * <li><b> Ext. Modules  </b> :      MP3 Click on micro BUS 1 </li>
 * <li><b> SW            </b> :      MikroC PRO for ARM 4.7.1     </li>
 * </ul>
 */

/**
 * @mainpage
 * <h3> MP3 click example using HEXIWEAR </h3>
 * @par This example demonstrates usage of the MP3 click board.
 *
 * <h3> MP3 Features </h3>
 * @par MP3 click, Hexiwear docking station
 */

/******************************************************************************
* Includes
*******************************************************************************/

#include <built_in.h>
#include "MP3_Test.h"
#include "resources.h"
#include "OLED_driver.h"
#include "common_screen_objects.h"

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
sbit Mmc_Chip_Select           at PTC_PDOR.B3;
sbit MP3_CS                    at PTC_PDOR.B4;
sbit MP3_RST                   at PTB_PDOR.B11;
sbit BSYNC                     at PTB_PDOR.B13;
sbit DREQ1                     at PTB_PDIR.B2;
sbit Volume_Up                 at PTA_PDIR.B12;
sbit Volume_Down               at PTA_PDIR.B13;

/******************************************************************************
* Function Prototypes
*******************************************************************************/
 void InitMCU();
 void MP3_Init(void);
 void MP3_Start(void);
 
/******************************************************************************
* Private Function Definitions
*******************************************************************************/


/******************************************************************************
* Public Function Definitions
*******************************************************************************/

void InitMCU(){

  GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_4);
  GPIO_Digital_Output(&PTB_PDOR, _GPIO_PINMASK_11);
  GPIO_Digital_Output(&PTB_PDOR, _GPIO_PINMASK_13);
  GPIO_Digital_Input( &PTB_PDOR, _GPIO_PINMASK_2);

}


/**************************************************************************************************
* Function MC3_Init()
* -------------------------------------------------------------------------------------------------
* Overview: Function Initialize MP3 VS1053B codec
* Input: Nothing
* Output: Nothing
**************************************************************************************************/

void MP3_Init(void)
{
  BSYNC = 1;
  MP3_CS = 1;

  // Hardware reset
  MP3_RST = 0;
  Delay_ms(10);
  MP3_RST = 1;

  while (DREQ1 == 0);

  MP3_SCI_Write(SCI_MODE_ADDR, 0x0800);
  MP3_SCI_Write(SCI_BASS_ADDR, 0x7A00);
  MP3_SCI_Write(SCI_CLOCKF_ADDR, 0x2000);   // default 12 288 000 Hz

  // Maximum volume is 0x00 and total silence is 0xFE.
  volume_left  = 0x0D; //0x3F;
  volume_right = 0x0D; //0x3F;
  MP3_Set_Volume(volume_left, volume_right);
}

/**************************************************************************************************
* Function MP3_Start()
* -------------------------------------------------------------------------------------------------
* Overview: Function Initialize SPI to communicate with MP3 codec
* Input: Nothing
* Output: Nothing
**************************************************************************************************/
void MP3_Start(void)
{

  MP3_CS            = 1;               // Deselect MP3_CS
  MP3_RST           = 1;               // Set MP3_RST pin

  BSYNC             = 0;               // Clear BSYNC
  BSYNC             = 1;               // Clear BSYNC

  OLED_Init();
  OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_WHITE, 0 );
  OLED_DrawImage( common_hexiwearLogo_bmp, 0, 0 );

  SPI0_Init_Advanced(1000000, _SPI_CFG_MASTER | _SPI_CFG_SELECT_CTAR0 | _SPI_CFG_FRAME_SIZE_8BITS |
                       _SPI_CFG_CLK_IDLE_LOW | _SPI_CFG_CLK_PHASE_CAPT_LEADING | _SPI_CFG_MSB_FIRST, &_GPIO_Module_SPI0_PC5_7_6);

  SPI_Set_Active(SPI2_Read, SPI2_Write);
  OLED_DrawBox(5, 67, 91, 30, OLED_COLOR_BLACK);
  OLED_WriteText("1. Initializing", 22, 68 );
  OLED_WriteText("VS1053B", 34, 81 );
  MP3_Init();
  Delay_ms(1000);
}

/**************************************************************************************************
* Function MP3_Test()
* -------------------------------------------------------------------------------------------------
* Overview: Function run the MP3 test
* Input: Nothing
* Output: test status: 0 - skiped; 1 - pass; 2 - fail
**************************************************************************************************/
void MP3_Test(char *test)
{
  unsigned long i;

  // Reset error flag
  *test = 0;
  SPI_Set_Active(SPI2_Read, SPI2_Write);
  OLED_DrawBox(5, 67, 91, 30, OLED_COLOR_BLACK);
  OLED_WriteText("2. Initializing MMC", 5, 75);
  Delay_ms(1500);
  Mmc_Set_Interface(_MMC_INTERFACE_SDHC);
  if (Mmc_Fat_Init() == 0) {
   while(1)
   {
    OLED_DrawImage( common_hexiwearLogo_bmp, 0, 0 );
    if (Mmc_Fat_Assign(&mp3_filename, 0) ) {
      SPI_Set_Active(SPI2_Read, SPI2_Write);
      OLED_DrawBox(5, 67, 91, 30, OLED_COLOR_BLACK);
      OLED_WriteText("3. File Assigned", 10, 75);
      Delay_ms(1500);
      Mmc_Fat_Reset(&file_size);          // Call Reset before file reading,
                                          //   procedure returns size of the file
      SPI_Set_Active(SPI2_Read, SPI2_Write);
      OLED_DrawBox(5, 67, 91, 30, OLED_COLOR_BLACK);
      OLED_DrawImage( MP3_bmp, 0, 0 );
      OLED_WriteText("4. Play audio... :)", 5, 75);
      // send file blocks to MP3 SDI
      while (file_size > BUFFER_SIZE)
      {
        for (i=0; i<BUFFER_SIZE; i++)
        {
          Mmc_Fat_Read(mp3_buffer + i);
        }
        for (i=0; i<BUFFER_SIZE/BYTES_2_WRITE; i++) {
          MP3_SDI_Write_32(mp3_buffer + i*BYTES_2_WRITE);
        }

        file_size -= BUFFER_SIZE;

     }

      // send the rest of the file to MP3 SDI
      for (i=0; i<file_size; i++)
      {
        Mmc_Fat_Read(mp3_buffer + i);
      }

      for (i=0; i<file_size; i++)
      {
        MP3_SDI_Write(mp3_buffer[i]);
      }
      SPI_Set_Active(SPI2_Read, SPI2_Write);
      OLED_DrawBox(5, 67, 91, 30, OLED_COLOR_BLACK);
      OLED_WriteText("5. Finish!", 10, 75);
      delay_ms(1500);
      
    }
    else {
      SPI_Set_Active(SPI2_Read, SPI2_Write);
      OLED_DrawBox(5, 67, 91, 30, OLED_COLOR_BLACK);
      OLED_WriteText("3. File not assigned", 5, 75);
      *test = 2;
    }
   }
  }
  else {
    SPI_Set_Active(SPI2_Read, SPI2_Write);
    OLED_DrawBox(5, 67, 91, 30, OLED_COLOR_BLACK);
    OLED_WriteText("3. MMC FAT not", 12, 68);
    OLED_WriteText("initialized", 35, 81);
    *test = 2;
  }
}

/**************************************************************************************************
* main function
**************************************************************************************************/

void main(){
  InitMCU();
  MP3_Start();
  MP3_Test(&ucMP3_run_test);
}


/*************** END OF FUNCTIONS *********************************************/
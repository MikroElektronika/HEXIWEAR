/****************************************************************************
* Title                 :   Camera click
* Filename              :   HEXIWEAR_Camera_Click.c
* Author                :   DJ
* Origin Date           :   06/05/2016
* Notes                 :   Camera Click Example
*****************************************************************************/
/**************************CHANGE LIST **************************************
*
*    Date    Software Version    Initials       Description
*  06/05/16       1.0.0            DJ        Interface Created.
*
*****************************************************************************/
/**
 * @file HEXIWEAR_8x8_Click.c
 * @brief <h2> Camera Click Example </h2>
 *
 * @par
 * Example for <a href="http://www.mikroe.com">MikroElektronika's</a>
 * Camera click board.
 */

/**
 * @page LIB_INFO Library Info
 * @date        19 Feb 2016
 * @author      DJ
 * @copyright   GNU Public License
 * @version     1.0.0 - Initial testing and verification
 */

/**
 * @page TEST_CFG Test Configurations
 * <h3> Test configuration : </h3>
 * @par
 * <ul>
 * <li><b> MCU           </b> :      MK64FN1M0XXX12              </li>
 * <li><b> Dev. Board    </b> :      HEXIWEAR                    </li>
 * <li><b> Oscillator    </b> :      12 MHz external             </li>
 * <li><b> Ext. Modules  </b> :      Camera Click on mikroBUS 1  </li>
 * <li><b> SW            </b> :      MikroC PRO for ARM 4.7.1    </li>
 * </ul>
 */

/**
 * @mainpage
 * <h3> Camera click example using HEXIWEAR </h3>
 * @par Simple example which demonstrates working with Camera click boards.
 *
 * <h3> Camera Features </h3>
 * @par Camera click, Hexiwear docking station
 */

/******************************************************************************
* Includes
*******************************************************************************/

#include "common_screen_objects.h"
#include "OLED_driver.h"
#include "OLED_info.h"

#define QCIF_WIDTH  176
#define QCIF_HEIGHT 144
#define FRM_WIDTH   QCIF_WIDTH
#define FRM_HEIGHT  QCIF_HEIGHT


#define FRAME_SIZE FRM_WIDTH*FRM_HEIGHT*2

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/

sbit Cam_Chip_Select  at PTC_PDOR.B4;
sbit Ready_Pin at PTB_PDIR.B13;

uint8_t qcifImg[FRAME_SIZE];
uint8_t scaledImg_bmp[OLED_SCREEN_WIDTH * OLED_SCREEN_HEIGHT * 2 + 6] =
{
  0x00,0x10,
  0x60,0x00,
  0x60,0x00,
};

uint8_t *scaledImgPtr;
uint16_t columnCnt, rowCnt, color, cnt;
uint8_t *rowPtr;

const uint8_t __CMD_GET_FRAME_BUFFERED = 5;

/******************************************************************************
* Function Prototypes
*******************************************************************************/

void Init_MCU();
void SendCommand(uint8_t cmd);
void ReadBytes(uint8_t *ptr, unsigned long num);
void GetCamBuff(uint8_t* buff);

/******************************************************************************
* Public Function Definitions
*******************************************************************************/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Initialize MCU

void Init_MCU() 
{
    Delay_ms(200);
    GPIO_Digital_Input(&PTB_PDOR, _GPIO_PINMASK_13);  // Set Ready pin as input

    GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_4); // Set Chip Select pin as output
    Cam_Chip_Select = 1;
    Delay_ms(200);

    SPI0_Init_Advanced(20000000, _SPI_CFG_MASTER | _SPI_CFG_SELECT_CTAR0 | _SPI_CFG_FRAME_SIZE_8BITS |
                         _SPI_CFG_CLK_IDLE_LOW | _SPI_CFG_CLK_PHASE_CHG_LEADING | _SPI_CFG_MSB_FIRST, &_GPIO_Module_SPI0_PC5_7_6);

    OLED_Init();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SendCommand(uint8_t cmd) 
{
    while(Ready_Pin == 0);

    SPI0_Read(cmd);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Read bytes from camera via SPI

void ReadBytes(uint8_t *ptr, unsigned long num) 
{
    while(num)
    {
        num--;
        while(Ready_Pin == 0);
        *ptr = SPI0_Read(0);
        *ptr++;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GetCamBuff(uint8_t* buff)
{
    Cam_Chip_Select = 0;
    SendCommand(__CMD_GET_FRAME_BUFFERED);
    ReadBytes(buff, FRAME_SIZE);
    Cam_Chip_Select = 1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

void main()
{
    Init_MCU();
    OLED_DrawImage( camera_bmp, 0, 0);
    Delay_ms(2000);

    while (1)
    {

        GetCamBuff(&qcifImg);
        
        scaledImgPtr = scaledImg_bmp + 6;
        
        for(rowCnt = 0 + 48; rowCnt < 96 + 48; rowCnt++)
        {
            rowPtr = qcifImg + (176 * 2 * rowCnt);
            for(columnCnt = 0 + 60; columnCnt < 96 + 60; columnCnt++)
            {
                *(scaledImgPtr++) = (rowPtr[2*columnCnt]);
                *(scaledImgPtr++) = (rowPtr[2*columnCnt + 1]);
            }
        }
        OLED_DrawImage(scaledImg_bmp, 0, 0);
    }
}
/****************************************************************************
* Title                 :   Thunder click
* Filename              :   Thunder.c
* Author                :   ML
* Origin Date           :   21/04/2016
* Notes                 :   Thunder Example
*****************************************************************************/
/**************************CHANGE LIST **************************************
*
*    Date    Software Version    Initials       Description
*  21/04/16       1.0.0          UC             Functional example finished.
*
*****************************************************************************/
/**
 * @file Thunder.c
 * @brief <h2> Thunder Example </h2>
 *
 * @par
 * Example for <a href="http://www.mikroe.com">MikroElektronika's</a>
 * Thunder click board.
 */

/**
 * @page Example Info
 * @date        21 Apr 2016
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
 * <li><b> Ext. Modules  </b> :      Thunder Click                 </li>
 * <li><b> SW            </b> :      MikroC PRO for ARM 4.7.1    </li>
 * </ul>
 */

/**
 * @mainpage
 * <h3> Thunder click example using HEXIWEAR </h3>
 * @par Place Thunder Click into the mikroBUS socket 1 on the docking station.
 * You can activate it using some disturber, or if it thunders nearby.
 *
 * <h3> Thunder Features </h3>
 * @par Thunder click, Hexiwear Docking Station
 */

/******************************************************************************
* Includes
*******************************************************************************/
#include "common_screen_objects.h"
//#include "OLED_driver.h"
/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/
#define _INDOR 0x12
#define _OUTDOOR 0x0E
/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/

unsigned int distance;
int value;
int  value1;
char Out_Text[15];
char cSF_test_status;
char interrupt_source = 0;

sbit Thunder_Sens_PIN     at PTB_PDIR.B13;
sbit Thunder_CS           at PTC_PDOR.B4;
static uint8_t isThunderDetected = -1;


/******************************************************************************
* Function Prototypes
*******************************************************************************/
void Thunder_Write();
unsigned short Thunder_Read();
void Thunder_Init(void);
long int Thunder_Read_Energy();
unsigned int Thunder_Read_distance();

/******************************************************************************
* Private Function Definitions
*******************************************************************************/

/******************************************************************************
* Public Function Definitions
*******************************************************************************/

void Thunder_Write(unsigned short address, unsigned short data1)  
{

  address.B7 = 0;
  address.B6 = 0;
  Thunder_CS = 0;
  SPI_Wr_Ptr(address);
  SPI_Wr_Ptr(data1);
  Thunder_CS = 1;
}

unsigned short Thunder_Read(unsigned short address) 
{
  unsigned short tmp = 0;

  address.B7 = 0;
  address.B6 = 1;
  Thunder_CS = 0;
  SPI_Wr_Ptr(address);
  tmp = SPI_Rd_Ptr(0);
  Thunder_CS = 1;

  return tmp;
}


void Thunder_Init(void) 
{
unsigned short temp;
  SPI_Set_Active(SPI0_Read, SPI0_Write);
  Thunder_CS = 1;                      // Set CS to idle

  Thunder_Write(0x3C, 0x96);           // set all registers in default mode
  Thunder_Write(0x3D, 0x96);           // calibrate internal oscillator

  temp = Thunder_Read(0x00) & 0xC1;
  Thunder_Write(0x00, ((_INDOR << 1) | temp)); // set to indoor

  temp = Thunder_Read(0x01) & 0x80;
  Thunder_Write(0x01, 0x44 | temp);    // set NFL and WDTreshold

  temp = Thunder_Read(0x02) & 0x80;    // clear statistics, min number of ligtning, spike rejection
  Thunder_Write(0x02, 0x40 | temp);

  temp = Thunder_Read(0x03) & 0x1F;    // Frequency division ratio(antenna),mask disturber, interrupt
  Thunder_Write(0x03, 0x00 | temp);

  Thunder_Write(0x08, 0x00);           // LCO, SRCO, TRCO on IRQ, capacitors tuning
}

long int Thunder_Read_Energy() 
{
  unsigned short low_byte, mid_byte;
  long int Out_thunder_energy;

  Out_thunder_energy = Thunder_Read(0x06) & 0x1F;
  mid_byte = Thunder_Read(0x05);
  low_byte = Thunder_Read(0x04);

  Out_thunder_energy = (Out_thunder_energy << 8);
  Out_thunder_energy = (Out_thunder_energy | mid_byte);
  Out_thunder_energy = (Out_thunder_energy << 8);
  Out_thunder_energy = (Out_thunder_energy | low_byte);

  return Out_thunder_energy;
}


unsigned int Thunder_Read_distance() 
{
  int Out_thunder_distance;

  Out_thunder_distance = Thunder_Read(0x07) & 0x3F;

  return Out_thunder_distance;
}

void system_init()
{
GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_4);
GPIO_Digital_Input(&PTB_PDOR, _GPIO_PINMASK_13);
SPI0_Init_Advanced(1000000, _SPI_CFG_MASTER | _SPI_CFG_SELECT_CTAR0 | _SPI_CFG_FRAME_SIZE_8BITS |
                       _SPI_CFG_CLK_IDLE_LOW | _SPI_CFG_CLK_PHASE_CHG_LEADING | _SPI_CFG_MSB_FIRST, &_GPIO_Module_SPI0_PC5_7_6);
                       
}

void display_init()
{
SPI_Set_Active(SPI2_Read, SPI2_Write);
/** initialize the OLED screen */
OLED_Init();
OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_WHITE, 0 );
/** display logo */
OLED_DrawImage( thunder_bmp, 0, 0 );
}


void main() org 0x1000
{
system_init();
    
display_init();

Thunder_Init();

// enable interrupt at PTB13 on either edge
EnableInterrupts();
NVIC_IntEnable( IVT_INT_PORTB );
PORTB_PCR13bits.IRQC = 0xB;

  while (1)
  {
    if ( 1 == isThunderDetected )
    {
    NVIC_IntDisable( IVT_INT_PORTB );
    SPI_Set_Active(SPI0_Read, SPI0_Write);
    
    interrupt_source = Thunder_Read(0x03) & 0x0F;
    distance = Thunder_Read_distance();
    value = Thunder_Read_Energy();
    
    switch (interrupt_source){
      case 4:
       {
        IntToStr((distance*2), Out_Text);
    
        SPI_Set_Active(SPI2_Read, SPI2_Write);
        OLED_DrawImage( thundera_bmp, 0, 0 );
        OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_WHITE, 0 );
        OLED_WriteText(Out_Text, 41, 82 );
        OLED_WriteText("Distance:", 10, 82 );
        OLED_WriteText("Thundering", 17, 71 );
        OLED_WriteText("km", 70, 82 );

        delay_ms(3000);
        OLED_DrawImage( thunder_bmp, 0, 0 );
        break;
        }
      case 2:
       {
        SPI_Set_Active(SPI2_Read, SPI2_Write);
        OLED_DrawImage( thundera_bmp, 0, 0 );
        OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_WHITE, 0 );
        OLED_WriteText("Disturbance", 20, 75 );

        delay_ms(2000);
        OLED_DrawImage( thunder_bmp, 0, 0 );
        break;
        }
      }
    isThunderDetected = 0;
    NVIC_IntEnable( IVT_INT_PORTB );
    }
  }
}

/**
 * Port B IRQ handler
 * detect the PB13 level change to update the current state
 */
void External1Int() iv IVT_INT_PORTB ics ICS_AUTO
{
  PORTB_ISFR = 0xFFFFFFFF;
  isThunderDetected = 1;
}

/*************** END OF FUNCTIONS *********************************************/
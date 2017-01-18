/**************************************************************************************************
* File: MP3_driver.c
* File Type: C - Source Code File
* (C) mikroElektronika, 2012
* Revision History:
*     - Initial version
* Description:
*     This project demonstrates communication with VS1053B mp3 codec.
*     Program reads one mp3 file from MMC and sends it to VS1053B for decoding
*     and playing.
*     MMC and MP3_SCI share Hardware SPI module.
* Test configuration:
*       MCU:             STM32F107VC
*                        http://www.st.com/internet/com/TECHNICAL_RESOURCES/TECHNICAL_LITERATURE/DATASHEET/CD00220364.pdf
*       Dev.Board:       EasyMx PRO v7 for STM32
*                        http://www.mikroe.com/eng/products/view/852/easymx-pro-v7-for-stm32/
*       Modules:         MP3 click -  ac:MP3_Codec
*                        http://www.mikroe.com/eng/products/view/783/mp3-click/
*       Oscillator:      HS-PLL 72.0000 MHz, internal 8.0000 MHz RC
*       SW:              mikroC PRO for ARM
*                        http://www.mikroe.com/eng/products/view/228/mikroc-pro-for-arm/
* NOTES:
*     - Make sure that MMC card is properly formatted (to FAT16 or just FAT)
*       before testing it on this example.
*     - Make sure that MMC card contains appropriate mp3 file ( sound.mp3 ).
**************************************************************************************************/
#include <built_in.h>
#include "MP3_driver.h"

/**************************************************************************************************
* CODEC V1053E connections
**************************************************************************************************/
extern sfr sbit MP3_CS;
extern sfr sbit MP3_RST;
extern sfr sbit BSYNC;
extern sfr sbit DREQ1;

/**************************************************************************************************
* Function MP3_SCI_Write()
* -------------------------------------------------------------------------------------------------
* Overview: Function writes one byte to MP3 SCI
* Input: register address in codec, data
* Output: Nothing
**************************************************************************************************/
void MP3_SCI_Write(char address, unsigned int data_in) {
  BSYNC = 1;
  SPI_Set_Active(SPI0_Read, SPI0_Write);
  MP3_CS = 0;                    // select MP3 SCI
  SPI_Wr_Ptr(WRITE_CODE);
  SPI_Wr_Ptr(address);
  SPI_Wr_Ptr(Hi(data_in));       // high byte
  SPI_Wr_Ptr(Lo(data_in));       // low byte
  MP3_CS = 1;                    // deselect MP3 SCI
  while (DREQ1 == 0);             // wait until DREQ1 becomes 1, see MP3 codec datasheet, Serial Protocol for SCI
}

/**************************************************************************************************
* Function MP3_SCI_Read()
* -------------------------------------------------------------------------------------------------
* Overview: Function reads words_count words from MP3 SCI
* Input: start address, word count to be read
* Output: words are stored to data_buffer
**************************************************************************************************/
void MP3_SCI_Read(char start_address, char words_count, unsigned int *data_buffer) {
  unsigned int temp;

  SPI_Set_Active(SPI0_Read, SPI0_Write);
  MP3_CS = 0;                    // select MP3 SCI
  SPI_Wr_Ptr(READ_CODE);
  SPI_Wr_Ptr(start_address);

  while (words_count--) {        // read words_count words byte per byte
    temp = SPI_Rd_Ptr(0);
    temp <<= 8;
    temp += SPI_Rd_Ptr(0);
    *(data_buffer++) = temp;
  }
  MP3_CS = 1;                    // deselect MP3 SCI
  while (DREQ1 == 0);             // wait until DREQ1 becomes 1, see MP3 codec datasheet, Serial Protocol for SCI
}

/**************************************************************************************************
* Function MP3_SDI_Write()
* -------------------------------------------------------------------------------------------------
* Overview: Function write one byte to MP3 SDI
* Input: data to be writed
* Output: Nothing
**************************************************************************************************/
void MP3_SDI_Write(char data_) {
  SPI_Set_Active(SPI0_Read, SPI0_Write);
  MP3_CS = 1;
  BSYNC = 0;

  while (DREQ1 == 0);             // wait until DREQ1 becomes 1, see MP3 codec datasheet, Serial Protocol for SCI

  SPI_Wr_Ptr(data_);
  BSYNC = 1;
}

/**************************************************************************************************
* Function MP3_SDI_Write_32
* -------------------------------------------------------------------------------------------------
* Overview: Function Write 32 bytes to MP3 SDI
* Input: data buffer
* Output: Nothing
**************************************************************************************************/
void MP3_SDI_Write_32(char *data_) {
  char i;
  SPI_Set_Active(SPI0_Read, SPI0_Write);
  MP3_CS = 1;
  BSYNC = 0;

  while (DREQ1 == 0);             // wait until DREQ1 becomes 1, see MP3 codec datasheet, Serial Protocol for SCI

  for (i=0; i<32; i++)
  SPI_Wr_Ptr(data_[i]);
  BSYNC = 1;
}

/**************************************************************************************************
* Function MP3_Set_Volume()
* -------------------------------------------------------------------------------------------------
* Overview: Function set volume on the left and right channel
* Input: left channel volume, right channel volume
* Output: Nothing
**************************************************************************************************/
void MP3_Set_Volume(char left, char right) {
  unsigned int volume;

  volume = (left<<8) + right;             // calculate value
  MP3_SCI_Write(SCI_VOL_ADDR, volume);    // Write value to VOL register
}

/**************************************************************************************************
* End of File
**************************************************************************************************/
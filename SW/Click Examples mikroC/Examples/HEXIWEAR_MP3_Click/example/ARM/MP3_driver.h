/**************************************************************************************************
* File: MP3_driver.h
* File Type: C - Header File
* Project Name: BrmBrrrrm
* Company: (c) mikroElektronika, 2011
* Revision History:
*     20111118:
*       - modified for mikroMedia for XMEGA HW revision 1.10 (JK);
* Description:
*     This module contains a set of functions that are used for communication with
*     VS1053E mp3 codec.
*       MCU:             ATxmega128A1
*                        http://www.atmel.com/dyn/resources/prod_documents/doc8067.pdf
*       Dev.Board:       Mikromedia_for_XMEGA
*                        http://www.mikroe.com/eng/products/view/688/mikromedia-for-xmega/
*       Oscillator:      Internal Clock, 32.0000 MHz
*       SW:              mikroC PRO for AVR
*                        http://www.mikroe.com/eng/products/view/228/mikroc-pro-for-avr/
* NOTES:
*     Mp3 codec use SPI bus to communicate with MCU.
**************************************************************************************************/

// VS1053E constants
const char WRITE_CODE           = 0x02;
const char READ_CODE            = 0x03;

const char SCI_BASE_ADDR        = 0x00;
const char SCI_MODE_ADDR        = 0x00;
const char SCI_STATUS_ADDR      = 0x01;
const char SCI_BASS_ADDR        = 0x02;
const char SCI_CLOCKF_ADDR      = 0x03;
const char SCI_DECODE_TIME_ADDR = 0x04;
const char SCI_AUDATA_ADDR      = 0x05;
const char SCI_WRAM_ADDR        = 0x06;
const char SCI_WRAMADDR_ADDR    = 0x07;
const char SCI_HDAT0_ADDR       = 0x08;
const char SCI_HDAT1_ADDR       = 0x09;
const char SCI_AIADDR_ADDR      = 0x0A;
const char SCI_VOL_ADDR         = 0x0B;
const char SCI_AICTRL0_ADDR     = 0x0C;
const char SCI_AICTRL1_ADDR     = 0x0D;
const char SCI_AICTRL2_ADDR     = 0x0E;
const char SCI_AICTRL3_ADDR     = 0x0F;

// Writes one byte to MP3 SCI
void MP3_SCI_Write(char address, unsigned int data_in);
// Reads words_count words from MP3 SCI
void MP3_SCI_Read(char start_address, char words_count, unsigned int *data_buffer);
// Write one byte to MP3 SDI
void MP3_SDI_Write(char data_);
// Write 32 bytes to MP3 SDI
void MP3_SDI_Write_32(char *data_);
// Set volume
void MP3_Set_Volume(char left, char right);

/**************************************************************************************************
* End of File
**************************************************************************************************/
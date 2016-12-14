#line 1 "D:/Uros/!!KONACNI PRIMERI/HEXIWEAR_MP3_Click/example/ARM/MP3_driver.c"
#line 1 "d:/program files/nxp/mikroc pro for arm/include/built_in.h"
#line 1 "d:/uros/!!konacni primeri/hexiwear_mp3_click/example/arm/mp3_driver.h"
#line 24 "d:/uros/!!konacni primeri/hexiwear_mp3_click/example/arm/mp3_driver.h"
const char WRITE_CODE = 0x02;
const char READ_CODE = 0x03;

const char SCI_BASE_ADDR = 0x00;
const char SCI_MODE_ADDR = 0x00;
const char SCI_STATUS_ADDR = 0x01;
const char SCI_BASS_ADDR = 0x02;
const char SCI_CLOCKF_ADDR = 0x03;
const char SCI_DECODE_TIME_ADDR = 0x04;
const char SCI_AUDATA_ADDR = 0x05;
const char SCI_WRAM_ADDR = 0x06;
const char SCI_WRAMADDR_ADDR = 0x07;
const char SCI_HDAT0_ADDR = 0x08;
const char SCI_HDAT1_ADDR = 0x09;
const char SCI_AIADDR_ADDR = 0x0A;
const char SCI_VOL_ADDR = 0x0B;
const char SCI_AICTRL0_ADDR = 0x0C;
const char SCI_AICTRL1_ADDR = 0x0D;
const char SCI_AICTRL2_ADDR = 0x0E;
const char SCI_AICTRL3_ADDR = 0x0F;


void MP3_SCI_Write(char address, unsigned int data_in);

void MP3_SCI_Read(char start_address, char words_count, unsigned int *data_buffer);

void MP3_SDI_Write(char data_);

void MP3_SDI_Write_32(char *data_);

void MP3_Set_Volume(char left, char right);
#line 33 "D:/Uros/!!KONACNI PRIMERI/HEXIWEAR_MP3_Click/example/ARM/MP3_driver.c"
extern sfr sbit MP3_CS;
extern sfr sbit MP3_RST;
extern sfr sbit BSYNC;
extern sfr sbit DREQ1;
#line 45 "D:/Uros/!!KONACNI PRIMERI/HEXIWEAR_MP3_Click/example/ARM/MP3_driver.c"
void MP3_SCI_Write(char address, unsigned int data_in) {
 BSYNC = 1;
 SPI_Set_Active(SPI0_Read, SPI0_Write);
 MP3_CS = 0;
 SPI_Wr_Ptr(WRITE_CODE);
 SPI_Wr_Ptr(address);
 SPI_Wr_Ptr( ((char *)&data_in)[1] );
 SPI_Wr_Ptr( ((char *)&data_in)[0] );
 MP3_CS = 1;
 while (DREQ1 == 0);
}
#line 64 "D:/Uros/!!KONACNI PRIMERI/HEXIWEAR_MP3_Click/example/ARM/MP3_driver.c"
void MP3_SCI_Read(char start_address, char words_count, unsigned int *data_buffer) {
 unsigned int temp;

 SPI_Set_Active(SPI0_Read, SPI0_Write);
 MP3_CS = 0;
 SPI_Wr_Ptr(READ_CODE);
 SPI_Wr_Ptr(start_address);

 while (words_count--) {
 temp = SPI_Rd_Ptr(0);
 temp <<= 8;
 temp += SPI_Rd_Ptr(0);
 *(data_buffer++) = temp;
 }
 MP3_CS = 1;
 while (DREQ1 == 0);
}
#line 89 "D:/Uros/!!KONACNI PRIMERI/HEXIWEAR_MP3_Click/example/ARM/MP3_driver.c"
void MP3_SDI_Write(char data_) {
 SPI_Set_Active(SPI0_Read, SPI0_Write);
 MP3_CS = 1;
 BSYNC = 0;

 while (DREQ1 == 0);

 SPI_Wr_Ptr(data_);
 BSYNC = 1;
}
#line 107 "D:/Uros/!!KONACNI PRIMERI/HEXIWEAR_MP3_Click/example/ARM/MP3_driver.c"
void MP3_SDI_Write_32(char *data_) {
 char i;
 SPI_Set_Active(SPI0_Read, SPI0_Write);
 MP3_CS = 1;
 BSYNC = 0;

 while (DREQ1 == 0);

 for (i=0; i<32; i++)
 SPI_Wr_Ptr(data_[i]);
 BSYNC = 1;
}
#line 127 "D:/Uros/!!KONACNI PRIMERI/HEXIWEAR_MP3_Click/example/ARM/MP3_driver.c"
void MP3_Set_Volume(char left, char right) {
 unsigned int volume;

 volume = (left<<8) + right;
 MP3_SCI_Write(SCI_VOL_ADDR, volume);
}

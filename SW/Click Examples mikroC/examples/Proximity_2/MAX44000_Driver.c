#include "MAX44000_Reg.h"

char tmp_data[2];
//--------------- Writes data to device - single location
void MAX44000_WriteRegister(char wrAddr, char wrData) {
  tmp_data[0] = wrAddr;
  tmp_data[1] = wrData;
  I2C_Start();
  I2C_Write(MAX44000_I2C_Adr,tmp_data,2,END_MODE_STOP);
}

//--------------- Reads data from device - single location
char MAX44000_ReadRegister(char rAddr) {
  tmp_data[0] = rAddr;
  I2C_Start();              // issue I2C start signal
  I2C_Write(MAX44000_I2C_Adr,tmp_data,1,END_MODE_RESTART);
  I2C_Read (MAX44000_I2C_Adr,tmp_data,1,END_MODE_STOP);
  return tmp_data[0];
}

//--------------- Set configuration registers
char MAX44000_Init() {
  MAX44000_WriteRegister(RECEIVE_CFG, 0xF1); //Receive Register 1.5625ms
  MAX44000_WriteRegister(TRANSMIT_CFG,0x0F); //Transmit Register 110mA
  MAX44000_WriteRegister(MAIN_CFG,0x13);     //Main Config ALS/Prox Mode
  
}
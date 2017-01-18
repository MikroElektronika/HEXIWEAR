#line 1 "D:/Uros/!!KONACNI PRIMERI/HEXIWEAR_Proximity_2_Click/MAX44000_Driver.c"
#line 1 "d:/uros/!!konacni primeri/hexiwear_proximity_2_click/max44000_reg.h"
#line 3 "D:/Uros/!!KONACNI PRIMERI/HEXIWEAR_Proximity_2_Click/MAX44000_Driver.c"
char tmp_data[2];

void MAX44000_WriteRegister(char wrAddr, char wrData) {
 tmp_data[0] = wrAddr;
 tmp_data[1] = wrData;
 I2C_Start();
 I2C_Write( 0x4A ,tmp_data,2,_I2C_END_MODE_STOP);
}


char MAX44000_ReadRegister(char rAddr) {
 tmp_data[0] = rAddr;
 I2C_Start();
 I2C_Write( 0x4A ,tmp_data,1,_I2C_END_MODE_RESTART);
 I2C_Read ( 0x4A ,tmp_data,1,_I2C_END_MODE_STOP);
 return tmp_data[0];
}


char MAX44000_Init() {
 MAX44000_WriteRegister( 0x02 , 0xF1);
 MAX44000_WriteRegister( 0x03 ,0x0F);
 MAX44000_WriteRegister( 0x01 ,0x13);

}

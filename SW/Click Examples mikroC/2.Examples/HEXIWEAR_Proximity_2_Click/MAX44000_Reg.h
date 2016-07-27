
#define MAX44000_I2C_Adr        0x4A

//Status
#define INT_STATUS              0x00
//Configuration
#define MAIN_CFG                0x01
#define RECEIVE_CFG             0x02
#define TRANSMIT_CFG            0x03
//ADC Data
#define ALS_H                   0x04
#define ALS_L                   0x05
#define PROX                    0x16
//Threshold set
#define ALS_UT_H                0x06
#define ALS_UT_L                0x07
#define ALS_LT_H                0x08
#define ALS_LT_L                0x09
#define THR_PTMR                0x0A
#define PROX_THRI               0x0B
#define PROX_THR                0x0C
#define GREEN_GAIN              0x0F
#define IR_GAIN                 0x10
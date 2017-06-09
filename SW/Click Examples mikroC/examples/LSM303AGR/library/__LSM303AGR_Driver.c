/*

    __LSM303AGR_Driver.c

    Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

--------------------------------------------------------------------------------

    Version      : ${VER}
    Developer    : ${SW_ENG}
    Date         : ${DATE}

------------------------------------------------------------------------------*/

#include "__LSM303AGR_Driver.h"

/*----------------------------------------------------------------------- HAL */
static uint8_t i2cAddressA;
static uint8_t i2cAddressM;
extern sfr sbit LSM303AGR_PIN;

#if defined( __MIKROC_PRO_FOR_PIC32__ ) || \
    defined( __MIKROC_PRO_FOR_DSPIC__ )

#define READ_BIT                1
#define WRITE_BIT               0
static uint8_t NACK_BIT   = 0x01;
static uint8_t ACK_BIT    = 0x00;
#elif defined( __MIKROC_PRO_FOR_PIC__ ) || \
      defined( __MIKROC_PRO_FOR_AVR__ )

#define READ_BIT                1
#define WRITE_BIT               0
static uint8_t NACK_BIT   = 0x00;
static uint8_t ACK_BIT    = 0x01;
#endif

#if defined( __MIKROC_PRO_FOR_ARM__ )
    #if defined( __STM32__ ) || defined( __KINETIS__ ) || defined( __MCHP__ )

static unsigned int ( *fpStartI2C )();
static unsigned int ( *fpWriteI2C )(unsigned char slaveAddres,
                                    unsigned char *pBuf, unsigned long count, 
                                    unsigned long endMode);
static void ( *fpReadI2C )(unsigned char slaveAddress, unsigned char *pBuf,
                           unsigned long count, unsigned long endMode);

    #elif defined( __MSP__ )

static unsigned int ( *fpWriteI2C )(unsigned char slaveAddres,
                                    unsigned char *pBuf, unsigned long count,
                                    unsigned long endMode);
static void ( *fpReadI2C )(unsigned char slaveAddress, unsigned char *pBuf,
                           unsigned long count, unsigned long endMode);

    #elif defined( __TI__ )

static void ( *fpSetSlaveI2CA )(char slaveAddress, char dir);
static void ( *fpSetSlaveI2CM )(char slaveAddress, char dir);
static unsigned char ( *fpWriteI2C )(unsigned char in, unsigned char mode);
static unsigned char( *fpReadI2C )(unsigned char *pOut, unsigned char mode);
    #endif

#elif  defined( __MIKROC_PRO_FOR_AVR__ )

static unsigned char( *fpStartI2C )();
static void  ( *fpStopI2C )();
static void ( *fpWriteI2C )(unsigned char out);
static unsigned char ( *fpReadI2C )(unsigned char ack);

#elif  defined( __MIKROC_PRO_FOR_PIC__ )

static unsigned char( *fpStartI2C )();
static void ( *fpStopI2C )();
static void ( *fpRestartI2C )();
static unsigned char( *fpWriteI2C )(unsigned char out);
static unsigned char( *fpReadI2C )(unsigned char ack);

#elif defined( __MIKROC_PRO_FOR_PIC32__ )

static unsigned int ( *fpStartI2C )();
static void ( *fpStopI2C )();
static unsigned int ( *fpRestartI2C )();
static unsigned int ( *fpWriteI2C )(unsigned char out);
static unsigned char ( *fpReadI2C )(unsigned int ack);

#elif defined( __MIKROC_PRO_FOR_DSPIC__ )

static unsigned int ( *fpStartI2C )();
static void ( *fpStopI2C )();
static void ( *fpRestartI2C )();
static unsigned int ( *fpWriteI2C )(unsigned char out);
static unsigned char ( *fpReadI2C )(unsigned int ack);

#elif defined( __MIKROC_PRO_FOR_8051__ )

static unsigned char( *fpStartI2C )();
static void ( *fpStopI2C )();
static void ( *fpWriteI2C )(unsigned char out);
static unsigned char( *fpReadI2C )(unsigned char ack);

#elif defined( __MIKROC_PRO_FOR_FT90x__ )

static void ( *fpSetSlaveI2CA )(uint8_t slaveAddres);
static void ( *fpSetSlaveI2CM )(uint8_t slaveAddres);
static unsigned char ( *fpWriteI2C )(unsigned char *pBuf, unsigned int count);
static unsigned char ( *fpReadI2C )(unsigned char *pBuf, unsigned int count);
#else
static void ( *fpStartI2C )();
static void ( *fpStopI2C )();
static void ( *fpWriteI2C )(uint8_t input);
static uint8_t ( *fpReadI2C )(uint8_t input);
#endif

static int halWrite(T_LSM303AGR_device device, uint8_t *pBuf, uint16_t count)
{
    int res = 0;
    uint8_t *ptr = pBuf;
    uint8_t i2cAddress;
    if ( device == LSM303AGR_ACC )
      i2cAddress = i2cAddressA;
    else if ( device == LSM303AGR_MAG )
      i2cAddress = i2cAddressM;
        
#if defined(__MIKROC_PRO_FOR_ARM__)

    #if defined( __STM32__ ) || defined( __KINETIS__ ) || defined( __MCHP__ )

    res |= fpStartI2C();
    res |= fpWriteI2C(i2cAddress, ptr, count, END_MODE_STOP);

    #elif defined( __MSP__ )

    res |= fpWriteI2C(i2cAddress, ptr, count, END_MODE_STOP);

    #elif defined( __TI__ )

    fpSetSlaveI2CA(i2cAddressA, _I2C_DIR_MASTER_TRANSMIT);
    fpSetSlaveI2CM(i2cAddressM, _I2C_DIR_MASTER_TRANSMIT);
    if(count == 1){
        res |= fpWriteI2C( *ptr, _I2C_MASTER_MODE_SINGLE_SEND );
    }
    else if(count == 2){
        res |= fpWriteI2C( *ptr++, _I2C_MASTER_MODE_BURST_SEND_START );
        res |= fpWriteI2C( *ptr, _I2C_MASTER_MODE_BURST_SEND_FINISH );
    } else {
        res |= fpWriteI2C( *ptr++, _I2C_MASTER_MODE_BURST_SEND_START );
        while(--count > 1)
            res |= fpWriteI2C( *ptr++, _I2C_MASTER_MODE_BURST_SEND_CONT );
        res |= fpWriteI2C( *ptr, _I2C_MASTER_MODE_BURST_SEND_FINISH );
    }
    #endif

#elif defined( __MIKROC_PRO_FOR_FT90x__ )

    fpSetSlaveI2CA(i2cAddressA);
    fpSetSlaveI2CM(i2cAddressM);
    res |= fpWriteI2C(ptr, count);

#elif defined( __MIKROC_PRO_FOR_AVR__ )

    res |= fpStartI2C();
    fpWriteI2C( (i2cAddress << 1) | WRITE_BIT );
    while(count--)
        fpWriteI2C(*( ptr++ ));
    fpStopI2C();
#elif defined( __MIKROC_PRO_FOR_8051__ )  || \
      defined( __MIKROC_PRO_FOR_DSPIC__ ) || \
      defined( __MIKROC_PRO_FOR_PIC32__ ) || \
      defined( __MIKROC_PRO_FOR_PIC__ )
    res |= fpStartI2C();
    res |= fpWriteI2C( (i2cAddress << 1) | WRITE_BIT );
    while(count--)
        res |= fpWriteI2C(*( ptr++ ));
    fpStopI2C();
#endif
    return res;
}

static int halRead(T_LSM303AGR_device device, uint8_t *pBuf, uint16_t count)
{
    int res = 0;
    uint8_t *ptr = pBuf;
    uint8_t i2cAddress;
    if ( device == LSM303AGR_ACC )
      i2cAddress = i2cAddressA;
    else if ( device == LSM303AGR_MAG )
      i2cAddress = i2cAddressM;

#if defined( __MIKROC_PRO_FOR_ARM__ )

    #if defined( __STM32__ ) || defined( __KINETIS__ ) || defined( __MCHP__ )
    res |= fpStartI2C();
    res |= fpWriteI2C(i2cAddress, ptr, 1, END_MODE_STOP);
    res |= fpStartI2C();
    fpReadI2C(i2cAddress, ptr, count, END_MODE_STOP);
    
    #elif defined( __MSP__ )

    res |= fpWriteI2C(i2cAddress, ptr, 1, END_MODE_STOP);
    fpReadI2C(i2cAddress, ptr, count, END_MODE_STOP);

    #elif defined( __TI__ )

    fpSetSlaveI2CA(i2cAddressA, _I2C_DIR_MASTER_TRANSMIT);
    fpSetSlaveI2CM(i2cAddressM, _I2C_DIR_MASTER_TRANSMIT);
    res |= fpWriteI2C(*ptr, _I2C_MASTER_MODE_SINGLE_SEND);
    fpSetSlaveI2CA(i2cAddressA, _I2C_DIR_MASTER_RECEIVE);
    fpSetSlaveI2CM(i2cAddressM, _I2C_DIR_MASTER_RECEIVE);

    if(count == 1) {
        res |= fpReadI2C(ptr, _I2C_MASTER_MODE_SINGLE_RECEIVE);
    }
    else if(count == 2) {
        res |= fpReadI2C(ptr++, _I2C_MASTER_MODE_BURST_RECEIVE_START);
        res |= fpReadI2C(ptr, _I2C_MASTER_MODE_BURST_RECEIVE_FINISH);
    }
    else {
        res |= fpReadI2C(ptr++ , _I2C_MASTER_MODE_BURST_RECEIVE_START);
        while(--count > 1){
            res |= fpReadI2C(ptr++ , _I2C_MASTER_MODE_BURST_SEND_CONT);
        }
        res |= fpReadI2C(ptr, _I2C_MASTER_MODE_BURST_SEND_FINISH);
    }
    #endif

#elif defined( __MIKROC_PRO_FOR_FT90x__ )

    fpSetSlaveI2CA(i2cAddressA);
    fpSetSlaveI2CM(i2cAddressM);
    res |= fpWriteI2C(ptr, 1);
    res |= fpReadI2C(ptr, count);

#elif defined( __MIKROC_PRO_FOR_AVR__ )

    res |= fpStartI2C();
    fpWriteI2C((i2cAddress << 1) | WRITE_BIT);
    fpWriteI2C(*ptr);
    fpStopI2C();
    Delay_ms(5);
    res |= fpStartI2C();
    fpWriteI2C((i2cAddress << 1) | READ_BIT);
    while(--count)
        *ptr++ = fpReadI2C(ACK_BIT);
    *ptr = fpReadI2C(NACK_BIT);
    fpStopI2C();
    
#elif defined( __MIKROC_PRO_FOR_PIC32__ )  || \
      defined( __MIKROC_PRO_FOR_8051__ )   || \
      defined( __MIKROC_PRO_FOR_PIC__ )    || \
      defined( __MIKROC_PRO_FOR_DSPIC__ )

    res |= fpStartI2C();
    res |= fpWriteI2C((i2cAddress << 1) | WRITE_BIT);
    res |= fpWriteI2C(*ptr);
    fpStopI2C();
    Delay_ms(5);
    res |= fpStartI2C();
    res |= fpWriteI2C((i2cAddress << 1) | READ_BIT);
    while(--count)
        *ptr++ = fpReadI2C(ACK_BIT);
    *ptr = fpReadI2C(NACK_BIT);
    fpStopI2C();
#endif
    return res;
}

static int halTransfer(T_LSM303AGR_device device, uint8_t *pIn, uint16_t inCount, uint8_t *pOut, uint16_t outCount)
{
    int res      = 0;
    uint8_t *in  = pIn;
    uint8_t *out = pOut;
    uint8_t i2cAddress;
    if ( device == LSM303AGR_ACC )
      i2cAddress = i2cAddressA;
    else if ( device == LSM303AGR_MAG )
      i2cAddress = i2cAddressM;

#if defined(__MIKROC_PRO_FOR_ARM__)
    #if defined( __STM32__ ) || defined( __KINETIS__ ) || defined( __MCHP__ )

    res |= fpStartI2C();
    res |= fpWriteI2C(i2cAddress, in, inCount, END_MODE_STOP);
    res |= fpStartI2C();
    fpReadI2C(i2cAddress, out, outCount, END_MODE_STOP);
    
    #elif defined( __MSP__ )

    res |= fpWriteI2C(i2cAddress, in, inCount, END_MODE_STOP);
    fpReadI2C(i2cAddress, out, outCount, END_MODE_STOP);

    #elif defined( __TI__ )

    fpSetSlaveI2CA(i2cAddressA, _I2C_DIR_MASTER_TRANSMIT);
    fpSetSlaveI2CM(i2cAddressM, _I2C_DIR_MASTER_TRANSMIT);

    if(inCount == 1) {
        res |= fpWriteI2C(*in, _I2C_MASTER_MODE_SINGLE_SEND);
    }
    if(inCount == 2) {
        res |= fpWriteI2C(*in++, _I2C_MASTER_MODE_BURST_SEND_START);
        res |= fpWriteI2C(*in, _I2C_MASTER_MODE_BURST_SEND_FINISH);
    }
    else {
        res |= fpWriteI2C(*in++, _I2C_MASTER_MODE_BURST_SEND_START);
        while(--inCount > 1)
            res |= fpWriteI2C(*in++, _I2C_MASTER_MODE_BURST_SEND_CONT);
        res |= fpWriteI2C(*in, _I2C_MASTER_MODE_BURST_SEND_FINISH);
    }
    fpSetSlaveI2CA(i2cAddressA, _I2C_DIR_MASTER_RECEIVE);
    fpSetSlaveI2CM(i2cAddressM, _I2C_DIR_MASTER_RECEIVE);

    if(outCount == 1) {
        res |= fpReadI2C(out, _I2C_MASTER_MODE_SINGLE_RECEIVE);
    }
    else if( outCount == 2 ){
        res |= fpReadI2C(out++, _I2C_MASTER_MODE_BURST_RECEIVE_START);
        res |= fpReadI2C(out, _I2C_MASTER_MODE_BURST_RECEIVE_FINISH);
    }
    else {
        res |= fpReadI2C(out++ , _I2C_MASTER_MODE_BURST_RECEIVE_START);
        while(--outCount > 1)
            res |= fpReadI2C(out++ , _I2C_MASTER_MODE_BURST_SEND_CONT);
        res |= fpReadI2C(out, _I2C_MASTER_MODE_BURST_SEND_FINISH);
    }
    #endif

#elif defined( __MIKROC_PRO_FOR_FT90x__ )

    fpSetSlaveI2CA(i2cAddressA);
    fpSetSlaveI2CM(i2cAddressM);
    res |= fpWriteI2C(in, inCount);
    fpSetSlaveI2CA(i2cAddressA);
    fpSetSlaveI2CM(i2cAddressM);
    res |= fpReadI2C(out, outCount);

#elif defined( __MIKROC_PRO_FOR_AVR__ )

    res |= fpStartI2C();
    fpWriteI2C((i2cAddress << 1) | WRITE_BIT);
    while(inCount--)
        fpWriteI2C(*in++);
    fpStopI2C();
    res |= fpStartI2C();
    fpWriteI2C((i2cAddress << 1) | READ_BIT);
    while(--outCount)
        *out++ = fpReadI2C(ACK_BIT);
    *out = fpReadI2C(NACK_BIT);
    fpStopI2C();

#elif defined( __MIKROC_PRO_FOR_8051__ )  || \
      defined( __MIKROC_PRO_FOR_DSPIC__ ) || \
      defined( __MIKROC_PRO_FOR_PIC32__ ) || \
      defined( __MIKROC_PRO_FOR_PIC__ )

    res |= fpStartI2C();
    res |= fpWriteI2C((i2cAddress << 1) | WRITE_BIT);
    while(inCount--)
        res|= fpWriteI2C(*in++);
    fpStopI2C();
    res |= fpStartI2C();
    res |= fpWriteI2C((i2cAddress << 1) | READ_BIT);
    while(--outCount)
        *out++ = fpReadI2C(ACK_BIT);
    *out = fpReadI2C(NACK_BIT);
    fpStopI2C();
#endif
    return res;
}
/*------------------------------------------------------------- PREPROCESSORS */



/*--------------------------------------------------------------------- TYPES */



/*----------------------------------------------------------------- VARIABLES */



/*--------------------------------------------- PRIVATE FUNCTION DECLARATIONS */

static void setup_();
static uint8_t readReg( T_LSM303AGR_device device, uint8_t addr );
static void writeToReg( T_LSM303AGR_device device, uint8_t addr, uint8_t val );

/*---------------------------------------------- PRIVATE FUNCTION DEFINITIONS */

static void setup_()
{
  writeToReg( LSM303AGR_MAG, _LSM303AGR_CFG_REG_A_M, 0x00 );
  writeToReg( LSM303AGR_MAG, _LSM303AGR_CFG_REG_C_M, 0x01 );
  writeToReg( LSM303AGR_ACC, _LSM303AGR_CTRL_REG1_A, 0x57 );
}

static uint8_t readReg( T_LSM303AGR_device device, uint8_t addr )
{
        uint8_t buff;
        buff = addr;
        halRead( device, &buff, 1 );
        return buff;
}

static void writeToReg( T_LSM303AGR_device device, uint8_t addr, uint8_t val )
{
        uint8_t buff[2];
        buff[0] = addr;
        buff[1] = val;
        halWrite( device, buff, 2 );
}

/*---------------------------------------------------------- PUBLIC FUNCTIONS */

void LSM303AGR_initDriver
(
#if defined( __MIKROC_PRO_FOR_ARM__ )
    #if defined( __STM32__ ) || defined( __KINETIS__ ) || defined( __MCHP__ )

        uint8_t slaveAddressA, uint8_t slaveAddressM,
        T_LSM303AGR_I2C_Start fpStart,
        T_LSM303AGR_I2C_Write fpWrite, T_LSM303AGR_I2C_Read fpRead
    #elif defined( __MSP__ )

        uint8_t slaveAddressA, uint8_t slaveAddressM,
        T_LSM303AGR_I2C_Write fpWrite, T_LSM303AGR_I2C_Read fpRead
    #elif defined( __TI__ )

        uint8_t slaveAddressA, uint8_t slaveAddressM,
        T_LSM303AGR_I2C_SetSlaveAddressA fpSlaveAddrA,
        T_LSM303AGR_I2C_SetSlaveAddressM fpSlaveAddrM,
        T_LSM303AGR_I2C_Write fpWrite, T_LSM303AGR_I2C_Read fpRead
    #endif

#elif defined( __MIKROC_PRO_FOR_AVR__ )   || \
      defined( __MIKROC_PRO_FOR_8051__ )  || \
      defined( __MIKROC_PRO_FOR_DSPIC__ ) || \
      defined( __MIKROC_PRO_FOR_PIC32__ ) || \
      defined( __MIKROC_PRO_FOR_PIC__ )

        uint8_t slaveAddressA, uint8_t slaveAddressM,
        T_LSM303AGR_I2C_Start fpStart, T_LSM303AGR_I2C_Stop fpStop,
        T_LSM303AGR_I2C_Write fpWrite, T_LSM303AGR_I2C_Read fpRead

#elif defined( __MIKROC_PRO_FOR_FT90x__ )

        uint8_t slaveAddressA, uint8_t slaveAddressM,
        T_LSM303AGR_I2C_SetSlaveAddressA fpSlaveAddrA,
        T_LSM303AGR_I2C_SetSlaveAddressM fpSlaveAddrM,
        T_LSM303AGR_I2C_Write fpWrite, T_LSM303AGR_I2C_Read fpRead

#else
        uint8_t slaveAddressA, uint8_t slaveAddressM,
        T_LSM303AGR_I2C_Start fpStart, T_LSM303AGR_I2C_Stop fpStop,
        T_LSM303AGR_I2C_Write fpWrite, T_LSM303AGR_I2C_Read fpRead
#endif
)
{
#if defined( __MIKROC_PRO_FOR_ARM__ )
  #if defined( __STM32__ ) || defined( __KINETIS__ ) || defined( __MCHP__ )

    fpStartI2C      = fpStart;
    fpWriteI2C      = fpWrite;
    fpReadI2C       = fpRead;

  #elif defined( __MSP__ )

    fpWriteI2C      = fpWrite;
    fpReadI2C       = fpRead;
    
  #elif defined( __TI__ )

    fpSetSlaveI2CA  = fpSlaveAddrA;
    fpSetSlaveI2CM  = fpSlaveAddrM;
    fpWriteI2C      = fpWrite;
    fpReadI2C       = fpRead;
  #endif

#elif defined( __MIKROC_PRO_FOR_AVR__ )   || \
      defined( __MIKROC_PRO_FOR_8051__ )  || \
      defined( __MIKROC_PRO_FOR_DSPIC__ ) || \
      defined( __MIKROC_PRO_FOR_PIC32__ ) || \
      defined( __MIKROC_PRO_FOR_PIC__ )

    fpStopI2C       = fpStop;
    fpStartI2C      = fpStart;
    fpWriteI2C      = fpWrite;
    fpReadI2C       = fpRead;

#elif defined( __MIKROC_PRO_FOR_FT90x__ )

    fpSetSlaveI2CA  = fpSlaveAddrA;
    fpSetSlaveI2CM  = fpSlaveAddrM;
    fpWriteI2C      = fpWrite;
    fpReadI2C       = fpRead;

#else
    fpStartI2C      = fpStart;
    fpStopI2C       = fpStop;
    fpWriteI2C      = fpWrite;
    fpReadI2C       = fpRead;
#endif

    i2cAddressA     = slaveAddressA;
    i2cAddressM     = slaveAddressM;
    

    setup_();
}

void LSM303AGR_enableTempSensor()
{
  uint8_t buff;
  writeToReg( LSM303AGR_ACC, _LSM303AGR_TEMP_CFG_REG_A, 0xC0 );
  
  buff = readReg( LSM303AGR_ACC, _LSM303AGR_CTRL_REG4_A );
  buff = buff | 0x80;
  writeToReg( LSM303AGR_ACC, _LSM303AGR_CTRL_REG4_A, buff );
}

void LSM303AGR_rebootMem()
{
  uint8_t buff;
  readReg( LSM303AGR_MAG, _LSM303AGR_CFG_REG_A_M );
  buff = buff | 0x40;
  writeToReg( LSM303AGR_MAG, _LSM303AGR_CFG_REG_A_M, buff );

  buff = readReg( LSM303AGR_ACC, _LSM303AGR_CTRL_REG5_A );
  buff = buff | 0x80;
  writeToReg( LSM303AGR_ACC, _LSM303AGR_CTRL_REG5_A, buff );
}

void LSM303AGR_disableAcc()
{
  writeToReg( LSM303AGR_ACC, _LSM303AGR_CTRL_REG1_A, 0x00 );
}

void LSM303AGR_readOutput( T_LSM303AGR_device device, uint16_t *pOutput )
{
        uint16_t buff;
        if ( device == LSM303AGR_ACC )
        {
                buff = readReg( LSM303AGR_ACC, _LSM303AGR_OUT_X_L_A );
                pOutput[0] = buff << 8;
                buff = readReg( LSM303AGR_ACC, _LSM303AGR_OUT_X_H_A );
                pOutput[0] |= buff;
                
                buff = readReg( LSM303AGR_ACC, _LSM303AGR_OUT_Y_L_A );
                pOutput[1] = buff << 8;
                buff = readReg( LSM303AGR_ACC, _LSM303AGR_OUT_Y_H_A );
                pOutput[1] |= buff;
                
                buff = readReg( LSM303AGR_ACC, _LSM303AGR_OUT_Z_L_A );
                pOutput[2] = buff << 8;
                buff = readReg( LSM303AGR_ACC, _LSM303AGR_OUT_Z_H_A );
                pOutput[2] |= buff;
        }
        else if ( device == LSM303AGR_MAG )
        {
                buff = readReg( LSM303AGR_MAG, _LSM303AGR_OUTX_L_REG_M );
                pOutput[0] = buff << 8;
                buff = readReg( LSM303AGR_MAG, _LSM303AGR_OUTX_H_REG_M );
                pOutput[0] |= buff;
                
                buff = readReg( LSM303AGR_MAG, _LSM303AGR_OUTY_L_REG_M );
                pOutput[1] = buff << 8;
                buff = readReg( LSM303AGR_MAG, _LSM303AGR_OUTY_H_REG_M );
                pOutput[1] |= buff;
                
                buff = readReg( LSM303AGR_MAG, _LSM303AGR_OUTZ_L_REG_M );
                pOutput[2] = buff << 8;
                buff = readReg( LSM303AGR_MAG, _LSM303AGR_OUTZ_H_REG_M );
                pOutput[2] |= buff;
        }
}

void LSM303AGR_setPowerMode(
        T_LSM303AGR_device device, T_LSM303AGR_powerMode mode
)
{
        uint8_t buff;
        if ( device == LSM303AGR_ACC )
        {
                buff = readReg( LSM303AGR_ACC, _LSM303AGR_CTRL_REG1_A );
                if ( mode == LSM303AGR_NORMAL || mode == LSM303AGR_HIGH_RES )
                        buff = buff & 0xF7;
                else
                        buff = buff | 0x08;
                writeToReg( LSM303AGR_ACC, _LSM303AGR_CTRL_REG1_A, buff );
                
                buff = readReg( LSM303AGR_ACC, _LSM303AGR_CTRL_REG4_A );
                if ( mode == LSM303AGR_NORMAL || mode == LSM303AGR_LOW_POWER )
                        buff = buff | 0x08;
                else
                        buff = buff & 0xF7;
                writeToReg( LSM303AGR_ACC, _LSM303AGR_CTRL_REG1_A, buff );
        }
        else if ( device == LSM303AGR_MAG )
        {
                buff = readReg( LSM303AGR_MAG, _LSM303AGR_CFG_REG_A_M );
                if ( mode == LSM303AGR_LOW_POWER)
            buff = buff | 0x10;
                else
            buff = buff & 0xEF;
                writeToReg( LSM303AGR_MAG, _LSM303AGR_CFG_REG_A_M, buff );
        }
}

void LSM303AGR_setMeasureMode( T_LSM303AGR_sysMode mode )
{
    uint8_t buff;
        buff = readReg( LSM303AGR_MAG, _LSM303AGR_CFG_REG_A_M );
        
        buff = buff & 0xFC;
        buff = buff | mode;
        writeToReg( LSM303AGR_MAG, _LSM303AGR_CFG_REG_A_M, buff );
}

void LSM303AGR_SetDataRate( T_LSM303AGR_device device, uint8_t dataRate )
{
        uint8_t buff;
        if ( device == LSM303AGR_ACC && dataRate < 10 )
        {
                buff = readReg( LSM303AGR_ACC, _LSM303AGR_CTRL_REG1_A );
                buff = buff & 0x0F;  // deletes left nibble
                dataRate <<= 4;
                buff = buff | dataRate;
                writeToReg( LSM303AGR_ACC, _LSM303AGR_CTRL_REG1_A, buff );
        }
        else if ( device == LSM303AGR_MAG && dataRate < 4 )
        {
                readReg( LSM303AGR_MAG, _LSM303AGR_CFG_REG_A_M );
                buff = buff & 0xF3;  // deletes ODR bits
                dataRate <<= 2;
                buff = buff | dataRate;
                writeToReg( LSM303AGR_MAG, _LSM303AGR_CFG_REG_A_M, buff );
        }
}

void LSM303AGR_softResetMag()
{
        uint8_t buff;
        readReg( LSM303AGR_MAG, _LSM303AGR_CFG_REG_A_M );
        buff = buff | 0x20;
        writeToReg( LSM303AGR_MAG, _LSM303AGR_CFG_REG_A_M, buff );
}

bool LSM303AGR_selfTest( T_LSM303AGR_device device )
{
        uint8_t buff;
        if ( device == LSM303AGR_ACC )
        {
                // TODO: accelerometer self-test
        }
        else if ( device == LSM303AGR_MAG )
        {
        uint16_t ST_AVGX, ST_AVGY, ST_AVGZ;
                uint16_t AVGX, AVGY, AVGZ;
                uint16_t MIN_ST_X = 0, MIN_ST_Y = 0, MIN_ST_Z = 0;
                uint16_t MAX_ST_X = 0, MAX_ST_Y = 0, MAX_ST_Z = 0;
                uint16_t output[3];
        uint8_t i;
                
                writeToReg( LSM303AGR_MAG, _LSM303AGR_CFG_REG_A_M, 0x8C );
                writeToReg( LSM303AGR_MAG, _LSM303AGR_CFG_REG_B_M, 0x02 );
                writeToReg( LSM303AGR_MAG, _LSM303AGR_CFG_REG_C_M, 0x10 );
                
                Delay_ms( 20 );
                
                buff = readReg ( LSM303AGR_MAG, _LSM303AGR_STATUS_REG_M );
                if ( buff & 0x08 )
                        LSM303AGR_readOutput( LSM303AGR_MAG, output );
        
                for ( i = 0; i < 50; ++i )
                {
                        while ( !( buff & 0x08 ) )
                        {}
                
                        LSM303AGR_readOutput( LSM303AGR_MAG, output );
                        
                        AVGX += output[0];
                        AVGY += output[1];
                        AVGZ += output[2];
                }
                        
                AVGX /= 50.0;
                AVGY /= 50.0;
                AVGZ /= 50.0;
                
                // enable self-test
                writeToReg( LSM303AGR_MAG, _LSM303AGR_CFG_REG_C_M, 0x12 );
                Delay_ms( 60 );
                
                buff = readReg ( LSM303AGR_MAG, _LSM303AGR_STATUS_REG_M );
                if ( buff & 0x08 )
                        LSM303AGR_readOutput( LSM303AGR_MAG, output );
        
                for ( i = 0; i < 50; ++i )
                {
                        while ( !( buff & 0x08 ) )
                        {}
                
                        LSM303AGR_readOutput( LSM303AGR_MAG, output );
                        
                        ST_AVGX += output[0];
                        ST_AVGY += output[1];
                        ST_AVGZ += output[2];
                        
                        if ( output[0] < MIN_ST_X )
                                MIN_ST_X = output[0];
                        if ( output[1] < MIN_ST_Y )
                                MIN_ST_Y = output[1];
                        if ( output[2] < MIN_ST_Z )
                                MIN_ST_Z = output[2];
                        
                        if ( output[0] > MAX_ST_X )
                                MAX_ST_X = output[0];
                        if ( output[1] > MAX_ST_Y )
                                MAX_ST_Y = output[1];
                        if ( output[2] > MAX_ST_Z )
                                MAX_ST_Z = output[2];
                }
                        
                ST_AVGX /= 50.0;
                ST_AVGY /= 50.0;
                ST_AVGZ /= 50.0;
                
                if ( !( MIN_ST_X <= abs( AVGX - ST_AVGX ) &&
                                abs( AVGX - ST_AVGX ) <= MAX_ST_X ) )
                        return false;
                        
                if ( !( MIN_ST_Y <= abs( AVGY - ST_AVGY ) &&
                                abs( AVGY - ST_AVGY ) <= MAX_ST_Y ) )
                        return false;
                        
                if ( !( MIN_ST_Z <= abs( AVGZ - ST_AVGZ ) &&
                                abs( AVGZ - ST_AVGZ ) <= MAX_ST_Z ) )
                        return false;
                
                // disable self-test
                writeToReg( LSM303AGR_MAG, _LSM303AGR_CFG_REG_C_M, 0x10 );
        writeToReg( LSM303AGR_MAG, _LSM303AGR_CFG_REG_A_M, 0x83 );
        }
    return true;
}


/*------------------------------------------------------------------------------

  __LSM303AGR_Driver.c

  Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

    This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.

------------------------------------------------------------------------------*/
/*

    __MMETER2_Driver.c

    Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

--------------------------------------------------------------------------------

    Version : 0.0.1

    Revision Log :

 - 0.0.1 (May/2017) Module created                   Djordje Rosic

    To Do List :

*******************************************************************************/

#include "__MMETER2_Driver.h"

static uint8_t i2cAddress;

/*----------------------------- I2C HAL --------------------------------------*/
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
static unsigned int ( *fpWriteI2C )(unsigned char slaveAddres, unsigned char *pBuf, unsigned long count, unsigned long endMode);
static void ( *fpReadI2C )(unsigned char slaveAddress, unsigned char *pBuf, unsigned long count, unsigned long endMode);
    #elif defined( __MSP__ )
static unsigned int ( *fpWriteI2C )(unsigned char slaveAddres, unsigned char *pBuf, unsigned long count, unsigned long endMode);
static void ( *fpReadI2C )(unsigned char slaveAddress, unsigned char *pBuf, unsigned long count, unsigned long endMode);
    #elif defined( __TI__ )
static void ( *fpSetSlaveI2C )(char slaveAddress, char dir);
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
static void ( *fpSetSlaveI2C )(unsigned char slaveAddres);
static unsigned char ( *fpWriteI2C )(unsigned char *pBuf, unsigned int count);
static unsigned char ( *fpReadI2C )(unsigned char *pBuf, unsigned int count);
#else
static void ( *fpStartI2C )();
static void ( *fpStopI2C )();
static void ( *fpWriteI2C )(uint8_t input);
static uint8_t ( *fpReadI2C )(uint8_t input);
#endif

static int halWrite(uint8_t *pBuf, uint16_t count);
static int halRead(uint8_t *pBuf, uint16_t count);
static int halTransfer(uint8_t *pIn, uint16_t inCount, uint8_t *pOut, uint16_t outCount);

static int halWrite(uint8_t *pBuf, uint16_t count)
{
    int res = 0;
    uint8_t *ptr = pBuf;
#if defined(__MIKROC_PRO_FOR_ARM__)
    #if defined( __STM32__ ) || defined( __KINETIS__ ) || defined( __MCHP__ )
    res |= fpStartI2C();
    res |= fpWriteI2C(i2cAddress, ptr, count, END_MODE_STOP);
    #elif defined( __MSP__ )
    res |= fpWriteI2C(i2cAddress, ptr, count, END_MODE_STOP);
    #elif defined( __TI__ )
    fpSetSlaveI2C(i2cAddress, _I2C_DIR_MASTER_TRANSMIT);
    if(count == 1){
        res |= fpWriteI2C( *ptr, _I2C_MASTER_MODE_SINGLE_SEND );
        delay_ms (1);
    }
    else if(count == 2){
        res |= fpWriteI2C( *ptr++, _I2C_MASTER_MODE_BURST_SEND_START );
        delay_ms (1);
        res |= fpWriteI2C( *ptr, _I2C_MASTER_MODE_BURST_SEND_FINISH );
    } else {
        res |= fpWriteI2C( *ptr++, _I2C_MASTER_MODE_BURST_SEND_START );
        delay_ms (1);
        while(--count > 1)
            res |= fpWriteI2C( *ptr++, _I2C_MASTER_MODE_BURST_SEND_CONT );
        res |= fpWriteI2C( *ptr, _I2C_MASTER_MODE_BURST_SEND_FINISH );
    }
    #endif

#elif defined( __MIKROC_PRO_FOR_FT90x__ )
    fpSetSlaveI2C(i2cAddress);
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

static int halRead(uint8_t *pBuf, uint16_t count)
{
    int res = 0;
    uint8_t *ptr = pBuf;

#if defined(__MIKROC_PRO_FOR_ARM__)
    #if defined( __STM32__ ) || defined( __KINETIS__ )
    res |= fpStartI2C();
    res |= fpWriteI2C(i2cAddress, ptr, 1, END_MODE_STOP);
    res |= fpStartI2C();
    fpReadI2C(i2cAddress, ptr, count, END_MODE_STOP);
    
    #elif defined( __MCHP__ )
    res |= fpStartI2C();
    res |= fpWriteI2C(i2cAddress, ptr, 1, END_MODE_RESTART);
    fpReadI2C(i2cAddress, ptr, count, END_MODE_STOP);

    #elif defined( __MSP__ )
    res |= fpWriteI2C(i2cAddress, ptr, 1, END_MODE_RESTART);
    fpReadI2C(i2cAddress, ptr, count, END_MODE_STOP);
    #elif defined( __TI__ )
    fpSetSlaveI2C(i2cAddress, _I2C_DIR_MASTER_TRANSMIT);
    delay_ms (1);
    res |= fpWriteI2C(*ptr, _I2C_MASTER_MODE_SINGLE_SEND);
    delay_ms (1);
    fpSetSlaveI2C(i2cAddress, _I2C_DIR_MASTER_RECEIVE);
    delay_ms (1);

    if(count == 1) {
        res |= fpReadI2C(ptr, _I2C_MASTER_MODE_SINGLE_RECEIVE);
        delay_ms (1);
    }
    else if(count == 2) {
        res |= fpReadI2C(ptr++, _I2C_MASTER_MODE_BURST_RECEIVE_START);
        delay_ms (1);
        res |= fpReadI2C(ptr, _I2C_MASTER_MODE_BURST_RECEIVE_FINISH);
    }
    else {
        res |= fpReadI2C(ptr++ , _I2C_MASTER_MODE_BURST_RECEIVE_START);
        delay_ms (1);
        while(--count > 1){
            res |= fpReadI2C(ptr++ , _I2C_MASTER_MODE_BURST_SEND_CONT);
        }
        res |= fpReadI2C(ptr, _I2C_MASTER_MODE_BURST_SEND_FINISH);
    }
    #endif

#elif defined( __MIKROC_PRO_FOR_FT90x__ )
    fpSetSlaveI2C(i2cAddress);
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

static int halTransfer(uint8_t *pIn, uint16_t inCount, 
                               uint8_t *pOut, uint16_t outCount)
{
    int res      = 0;
    uint8_t *in  = pIn;
    uint8_t *out = pOut;

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
    fpSetSlaveI2C(i2cAddress, _I2C_DIR_MASTER_TRANSMIT);

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
    fpSetSlaveI2C(i2cAddress, _I2C_DIR_MASTER_RECEIVE);

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
    fpSetSlaveI2C(i2cAddress);
    res |= fpWriteI2C(in, inCount);
    fpSetSlaveI2C(i2cAddress);
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

/*----------------------------- I2C HAL END ----------------------------------*/

/*                 Preprocessors
 ******************************************************************************/


/*                Typedefs
 ******************************************************************************/


/*                Variables
 ******************************************************************************/
static uint16_t q1;
static uint16_t q2;
static uint16_t q3;
static uint16_t q4;
static uint16_t q5;
static uint16_t q6;
static uint16_t c1;
static uint16_t c2;
static uint16_t c3;
static uint16_t c4;
static uint16_t c5;
static uint16_t c6;

/*                 Private Function Prototypes
 ******************************************************************************/


/*                 Private Function Definitions
 ******************************************************************************/


/*                Public Function Definitions
 ******************************************************************************/


void MMETER2_initDriver
(
        uint8_t sensorType,
#if defined( __MIKROC_PRO_FOR_ARM__ )
    #if defined( __STM32__ ) || defined( __KINETIS__ ) || defined( __MCHP__ )
        uint8_t slaveAddress,
        T_MMETER2_I2C_Start fpStart,
        T_MMETER2_I2C_Write fpWrite, T_MMETER2_I2C_Read fpRead
    #elif defined( __MSP__ )
        uint8_t slaveAddress,
        T_MMETER2_I2C_Write fpWrite, T_MMETER2_I2C_Read fpRead
    #elif defined( __TI__ )
        uint8_t slaveAddress,
        T_MMETER2_I2C_SetSlaveAddress fpSlaveAddr,
        T_MMETER2_I2C_Write fpWrite, T_MMETER2_I2C_Read fpRead
    #endif

#elif defined( __MIKROC_PRO_FOR_AVR__ )   || \
      defined( __MIKROC_PRO_FOR_8051__ )  || \
      defined( __MIKROC_PRO_FOR_DSPIC__ ) || \
      defined( __MIKROC_PRO_FOR_PIC32__ ) || \
      defined( __MIKROC_PRO_FOR_PIC__ )
        uint8_t slaveAddress,
        T_MMETER2_I2C_Start fpStart, T_MMETER2_I2C_Stop fpStop,
        T_MMETER2_I2C_Write fpWrite, T_MMETER2_I2C_Read fpRead

#elif defined( __MIKROC_PRO_FOR_FT90x__ )
        uint8_t slaveAddress, T_MMETER2_I2C_SetSlaveAddress fpSlaveAddr,
        T_MMETER2_I2C_Write fpWrite, T_MMETER2_I2C_Read fpRead

#else
        uint8_t slaveAddress,
        T_MMETER2_I2C_Start fpStart, T_MMETER2_I2C_Stop fpStop,
        T_MMETER2_I2C_Write fpWrite, T_MMETER2_I2C_Read fpRead
#endif
)
{
    uint8_t readBytes[2];

#if defined( __MIKROC_PRO_FOR_ARM__ )
  #if defined( __STM32__ ) || defined( __KINETIS__ ) || defined( __MCHP__ )
    fpStartI2C      = fpStart;
    fpWriteI2C      = fpWrite;
    fpReadI2C       = fpRead;
  #elif defined( __MSP__ )
    fpWriteI2C      = fpWrite;
    fpReadI2C       = fpRead;
  #elif defined( __TI__ )
    fpSetSlaveI2C   = fpSlaveAddr;
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
    fpSetSlaveI2C   = fpSlaveAddr;
    fpWriteI2C      = fpWrite;
    fpReadI2C       = fpRead;

#else
    fpStartI2C      = fpStart;
    fpStopI2C       = fpStop;
    fpWriteI2C      = fpWrite;
    fpReadI2C       = fpRead;
#endif

    i2cAddress        = slaveAddress;

    switch (sensorType)
    {
        case 0:
        {
            q1 = 14;
            q2 = 16;
            q3 = 7;
            q4 = 5;
            q5 = 7;
            q6 = 21;
            break;
        }
        case 1:
        {
            q1 = 14;
            q2 = 15;
            q3 = 8;
            q4 = 6;
            q5 = 7;
            q6 = 22;
            break;
        }
        case 2:
        {
            q1 = 16;
            q2 = 18;
            q3 = 6;
            q4 = 4;
            q5 = 7;
            q6 = 22;
            break;
        }
        case 3:
        {
            q1 = 17;
            q2 = 19;
            q3 = 5;
            q4 = 3;
            q5 = 7;
            q6 = 22;
            break;
        }
        case 4:
        {
            q1 = 16;
            q2 = 17;
            q3 = 6;
            q4 = 5;
            q5 = 7;
            q6 = 22;
            break;
        }
        case 5:
        {
            q1 = 17;
            q2 = 19;
            q3 = 5;
            q4 = 3;
            q5 = 7;
            q6 = 22;
            break;
        }
        case 6:
        {
            q1 = 17;
            q2 = 18;
            q3 = 5;
            q4 = 4;
            q5 = 7;
            q6 = 22;
            break;
        }
        case 7:
        {
            q1 = 18;
            q2 = 20;
            q3 = 4;
            q4 = 1;
            q5 = 7;
            q6 = 22;
            break;
        }
    }


    readBytes[0] = RESET;
    halWrite(readBytes, 1);
    Delay_ms(3);

    readBytes[0] = C1_READ;
    halRead(readBytes, 2);
    c1 = 0 | readBytes[0]<<8 | readBytes[1];

    readBytes[0] = C2_READ;
    halRead(readBytes, 2);
    c2 = 0 | readBytes[0]<<8 | readBytes[1];

    readBytes[0] = C3_READ;
    halRead(readBytes, 2);
    c3 = 0 | readBytes[0]<<8 | readBytes[1];

    readBytes[0] = C4_READ;
    halRead(readBytes, 2);
    c4 = 0 | readBytes[0]<<8 | readBytes[1];

    readBytes[0] = C5_READ;
    halRead(readBytes, 2);
    c5 = 0 | readBytes[0]<<8 | readBytes[1];

    readBytes[0] = C6_READ;
    halRead(readBytes, 2);
    c6 = 0 | readBytes[0]<<8 | readBytes[1];

}


float MMETER2_getTemperature (uint8_t oversamplingRatio)
{
    uint8_t command;
    uint8_t temperatureBytes[3];
    uint32_t d2;
    int32_t dt;
    int32_t temperature;
    float result;
    
    switch (oversamplingRatio){
         case CONVERT_256:
              command = D2_CONVERT_256;
              break;
         case CONVERT_512:
              command = D2_CONVERT_512;
              break;
         case CONVERT_1024:
              command = D2_CONVERT_1024;
              break;
         case CONVERT_2048:
              command = D2_CONVERT_2048;
              break;
         case CONVERT_4096:
              command = D2_CONVERT_4096;
              break;
    }

    // Getting Digital Temperature Value
    halWrite(&command, 1);
    Delay_ms(100);
    temperatureBytes[0] = ADC_READ;
    halRead(temperatureBytes, 3);

    d2 = 0 | (((uint32_t)temperatureBytes[0]) << 16) |
    (((uint32_t)temperatureBytes[1]) << 8) | ((uint32_t)temperatureBytes[3]);

    //Difference between actual and reference temperature
    dt = d2 - (((int32_t)c5)<<q5);


//AVR, DSPIC and PIC don't support int64, so values are truncated to fit into
//int32. This reduces measuring accuracy.
#if defined( __MIKROC_PRO_FOR_AVR__ ) || \
    defined( __MIKROC_PRO_FOR_DSPIC__ ) || \
    defined( __MIKROC_PRO_FOR_PIC__ )
    dt = dt >> 9;
    temperature = 2000 + ((dt*c6)>> (q6 - 9));

#else
    temperature = 2000 + (((int64_t)dt*c6)>>q6);
#endif

    result = temperature;
    return result/100;
}


float MMETER2_getPressure (uint8_t oversamplingRatio)
{
    uint8_t pressureCommand;
    uint8_t temperatureCommand;
    uint8_t pressureBytes[3];
    uint8_t temperatureBytes[3];
    uint32_t d1;
    uint32_t d2;
    int32_t dt;
    int32_t pressure;

#if defined( __MIKROC_PRO_FOR_AVR__ ) || \
    defined( __MIKROC_PRO_FOR_DSPIC__ ) || \
    defined( __MIKROC_PRO_FOR_PIC__ )
    int32_t off;
    int32_t sens;

#else
    int64_t off;
    int64_t sens;
#endif
    float result;

    switch (oversamplingRatio){
         case CONVERT_256:
              pressureCommand = D1_CONVERT_256;
              temperatureCommand = D2_CONVERT_256;
              break;
         case CONVERT_512:
              pressureCommand = D1_CONVERT_512;
              temperatureCommand = D2_CONVERT_512;
              break;
         case CONVERT_1024:
              pressureCommand = D1_CONVERT_1024;
              temperatureCommand = D2_CONVERT_1024;
              break;
         case CONVERT_2048:
              pressureCommand = D1_CONVERT_2048;
              temperatureCommand = D2_CONVERT_2048;
              break;
         case CONVERT_4096:
              pressureCommand = D1_CONVERT_4096;
              temperatureCommand = D2_CONVERT_4096;
              break;
    }

    // Getting Digital Pressure Value
    halWrite(&pressureCommand, 1);
    Delay_ms(100);
    pressureBytes[0] = ADC_READ;
    halRead(pressureBytes, 3);
    d1 = 0 | (((uint32_t)pressureBytes[0]) << 16) |
    (((uint32_t)pressureBytes[1]) << 8) | ((uint32_t)pressureBytes[3]);

    // Getting Digital Temperature Value
    halWrite(&temperatureCommand, 1);
    Delay_ms(100);
    temperatureBytes[0] = ADC_READ;
    halRead(temperatureBytes, 3);
    d2 = 0 | (((uint32_t)temperatureBytes[0]) << 16) |
    (((uint32_t)temperatureBytes[1]) << 8) | ((uint32_t)temperatureBytes[3]);


    dt = d2 - (((int32_t)c5)<<q5);
/*
 * Offset at actual temperature
 */
//AVR, DSPIC and PIC don't support int64, so values are truncated to fit into
//int32. This reduces measuring accuracy.
#if defined( __MIKROC_PRO_FOR_AVR__ ) || \
    defined( __MIKROC_PRO_FOR_DSPIC__ ) || \
    defined( __MIKROC_PRO_FOR_PIC__ )
    dt = dt >> 10;
    
    // off is shifted by 10 bits to the right to fit into int32.
    off = ((int32_t)c2 << (q2 - 10)) + ((dt * (int32_t)c4) >> q4);
#else
    off = (((int64_t)c2)<<q2) + ((int64_t)dt)*(((int64_t)c4)>>q4);
#endif

/*
 * Sensitivity at actual temperature
 */
#if defined( __MIKROC_PRO_FOR_AVR__ ) || \
    defined( __MIKROC_PRO_FOR_DSPIC__ ) || \
    defined( __MIKROC_PRO_FOR_PIC__ )
    //dt is already shifted by 10!
    
    // sens is shifted by 10 bits to the right to fit into int32.
    sens = ((int32_t)c1 << (q1 - 10)) + ((dt * (int32_t)c3) >> q3);
#else
    sens = (((int64_t)c1)<<q1)+((int64_t)dt)*(((int64_t)c3)>>q3);
#endif

/*
 * Temperature Compensated Pressure
 */
#if defined( __MIKROC_PRO_FOR_AVR__ ) || \
    defined( __MIKROC_PRO_FOR_DSPIC__ ) || \
    defined( __MIKROC_PRO_FOR_PIC__ )
    d1 = d1 >> 9;
    sens = sens >> 10;
    pressure = d1*sens;
    pressure = pressure >> 2;
    pressure = pressure - off;
    pressure = pressure >> 5;

#else
    pressure = ((((int64_t)d1*sens)>>21)-off)>>15;
#endif

#if defined( __TI__ ) || defined( __MCHP__ )  || defined( __KINETIS__ )
    pressure++;
    pressure--;
#endif

    result = pressure;
    return  result/10000;
}

/*------------------------------------------------------------------------------

  __MMETER2_Driver.c

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
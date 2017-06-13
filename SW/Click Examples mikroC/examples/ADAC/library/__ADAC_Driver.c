/*

    __ADAC_Driver.c

    Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

--------------------------------------------------------------------------------

    Version : 0.0.1

    Revision Log :

 - 0.0.1 (May/2017) Module created                   Djordje Rosic

    To Do List :

 -

*******************************************************************************/

#include "__ADAC_Driver.h"

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
        Delay_ms (1);
    }
    else if(count == 2){
        res |= fpWriteI2C( *ptr++, _I2C_MASTER_MODE_BURST_SEND_START );
        Delay_ms (1);
        res |= fpWriteI2C( *ptr, _I2C_MASTER_MODE_BURST_SEND_FINISH );
    } else {
        res |= fpWriteI2C( *ptr++, _I2C_MASTER_MODE_BURST_SEND_START );
        Delay_ms (1);
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
    res |= fpWriteI2C(*ptr, _I2C_MASTER_MODE_SINGLE_SEND);
    fpSetSlaveI2C(i2cAddress, _I2C_DIR_MASTER_RECEIVE);

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

static int halTransfer(uint8_t *pIn, uint16_t inCount, uint8_t *pOut, uint16_t outCount)
{
    int res      = 0;
    uint8_t *in  = pIn;
    uint8_t *out = pOut;

#if defined(__MIKROC_PRO_FOR_ARM__)
    #if defined( __STM32__ ) || defined( __KINETIS__ )
    res |= fpStartI2C();
    res |= fpWriteI2C(i2cAddress, in, inCount, END_MODE_STOP);
    res |= fpStartI2C();
    fpReadI2C(i2cAddress, out, outCount, END_MODE_STOP);
    
    #elif defined( __MCHP__ )
    res |= fpStartI2C();
    res |= fpWriteI2C(i2cAddress, in, inCount, END_MODE_RESTART);
    fpReadI2C(i2cAddress, out, outCount, END_MODE_STOP);
    
    #elif defined( __MSP__ )
    res |= fpWriteI2C(i2cAddress, in, inCount, END_MODE_RESTART);
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


/*                 Private Function Prototypes
 ******************************************************************************/


/*                 Private Function Definitions
 ******************************************************************************/


/*                Public Function Definitions
 ******************************************************************************/


void ADAC_driverInit
(
#if defined( __MIKROC_PRO_FOR_ARM__ )
    #if defined( __STM32__ ) || defined( __KINETIS__ ) || defined( __MCHP__ )
        uint8_t slaveAddress,
        T_ADAC_I2C_Start fpStart,
        T_ADAC_I2C_Write fpWrite, T_ADAC_I2C_Read fpRead
    #elif defined( __MSP__ )
        uint8_t slaveAddress,
        T_ADAC_I2C_Write fpWrite, T_ADAC_I2C_Read fpRead
    #elif defined( __TI__ )
        uint8_t slaveAddress,
        T_ADAC_I2C_SetSlaveAddress fpSlaveAddr,
        T_ADAC_I2C_Write fpWrite, T_ADAC_I2C_Read fpRead
    #endif

#elif defined( __MIKROC_PRO_FOR_AVR__ )   || \
      defined( __MIKROC_PRO_FOR_8051__ )  || \
      defined( __MIKROC_PRO_FOR_DSPIC__ ) || \
      defined( __MIKROC_PRO_FOR_PIC32__ ) || \
      defined( __MIKROC_PRO_FOR_PIC__ )
        uint8_t slaveAddress,
        T_ADAC_I2C_Start fpStart, T_ADAC_I2C_Stop fpStop,
        T_ADAC_I2C_Write fpWrite, T_ADAC_I2C_Read fpRead

#elif defined( __MIKROC_PRO_FOR_FT90x__ )
        uint8_t slaveAddress, T_ADAC_I2C_SetSlaveAddress fpSlaveAddr,
        T_ADAC_I2C_Write fpWrite, T_ADAC_I2C_Read fpRead

#else
        uint8_t slaveAddress,
        T_ADAC_I2C_Start fpStart, T_ADAC_I2C_Stop fpStop,
        T_ADAC_I2C_Write fpWrite, T_ADAC_I2C_Read fpRead
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

}


void ADAC_setConfiguration (uint8_t pointerByte, uint8_t MSDataByte,
                                                 uint8_t LSDatabyte)
{
    char dataIn [3];
    dataIn [0] = pointerByte;
    dataIn [1] = MSDataByte;
    dataIn [2] = LSDatabyte;
    halWrite ( dataIn , 3 );
}


void ADAC_writeDAC (uint8_t pointerByte, uint8_t MSDataByte,
                                         uint8_t LSDatabyte)
{
    char dataIn [3];
    MSDataByte &= 0x0F;
    dataIn [0] = pointerByte;
    pointerByte = pointerByte << 4;
    dataIn [1] = 0x80 | pointerByte | MSDataByte;
    dataIn [2] = LSDatabyte;

    halWrite ( dataIn , 3 );
}

uint16_t ADAC_readADC (uint8_t pointerByte, uint8_t * IOChannel)
{
    char dataIn [1];
    char dataOut [2];
    uint16_t result;
    uint8_t channel;
    dataIn [0] = pointerByte;

    halTransfer (dataIn, 1, dataOut, 2 );
   
    channel = dataOut [0] >> 4;
    * IOChannel =  channel;

    dataOut [0] &= 0x0F;
    result = (dataOut [0] << 8) + dataOut [1];
    return result;
}

uint16_t ADAC_readDAC (uint8_t pointerByte, uint8_t * IOChannel)
{
    char dataIn [1];
    char dataOut [2];
    uint16_t result;
    uint8_t channel;
    dataIn [0] = pointerByte;

    halTransfer (dataIn, 1, dataOut, 2 );

    channel = dataOut [0] >> 4;
    * IOChannel =  channel;

    dataOut [0] &= 0x0F;
    result = (dataOut [0] << 8) + dataOut [1];
    return result;
}

uint16_t ADAC_readGPIO (uint8_t pointerByte)
{
    char dataIn [1];
    char dataOut [2];
    uint16_t result;
    dataIn [0] = pointerByte;

    halTransfer (dataIn, 1, dataOut, 2 );

    result = dataOut [1];
    return result;
}

uint16_t ADAC_readConfig (uint8_t pointerByte)
{
    char dataIn [1];
    char dataOut [2];
    uint16_t result;
    dataIn [0] = pointerByte;

    halTransfer (dataIn, 1, dataOut, 2 );

    result = (dataOut [0] << 8) + dataOut [1];
    return result;
}





/*------------------------------------------------------------------------------

  __ADAC_Driver.c

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
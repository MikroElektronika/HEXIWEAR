/*

    __IRGRID2_Driver.c

    Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

--------------------------------------------------------------------------------

    Version      : 1.0.0
    Developer    : Djordje Rosic
    Date         : May 2017

------------------------------------------------------------------------------*/

#include "__IRGRID2_Driver.h"

/*----------------------------------------------------------------------- HAL */
static uint8_t i2cAddress;

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
    if(count == 1)
    {
        res |= fpWriteI2C( *ptr, _I2C_MASTER_MODE_SINGLE_SEND );
        delay_ms (1);
    }
    else if(count == 2)
    {
        res |= fpWriteI2C( *ptr++, _I2C_MASTER_MODE_BURST_SEND_START );
        delay_ms (1);
        res |= fpWriteI2C( *ptr, _I2C_MASTER_MODE_BURST_SEND_FINISH );
    } 
    else 
    {
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

    if(count == 1) 
    {
        res |= fpReadI2C(ptr, _I2C_MASTER_MODE_SINGLE_RECEIVE);
        delay_ms (1);
    }
    else if(count == 2)
    {
        res |= fpReadI2C(ptr++, _I2C_MASTER_MODE_BURST_RECEIVE_START);
        delay_ms (1);
        res |= fpReadI2C(ptr, _I2C_MASTER_MODE_BURST_RECEIVE_FINISH);
    }
    else 
    {
        res |= fpReadI2C(ptr++ , _I2C_MASTER_MODE_BURST_RECEIVE_START);
        delay_ms (1);
        while(--count > 1){
            res |= fpReadI2C(ptr++ , _I2C_MASTER_MODE_BURST_RECEIVE_CONT);
            Delay_ms(1);
        }
        res |= fpReadI2C(ptr, _I2C_MASTER_MODE_BURST_RECEIVE_FINISH);
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


    if(inCount == 1) 
    {
        res |= fpWriteI2C(*in, _I2C_MASTER_MODE_SINGLE_SEND);
    }
    else if(inCount == 2)
    {
        res |= fpWriteI2C(*in++, _I2C_MASTER_MODE_BURST_SEND_START);
        delay_ms (1);
        res |= fpWriteI2C(*in, _I2C_MASTER_MODE_BURST_SEND_FINISH);
    }
    else
    {
        res |= fpWriteI2C(*in++, _I2C_MASTER_MODE_BURST_SEND_START);
        delay_ms (1);
        while(--inCount > 1)
            res |= fpWriteI2C(*in++, _I2C_MASTER_MODE_BURST_SEND_CONT);
        res |= fpWriteI2C(*in, _I2C_MASTER_MODE_BURST_SEND_FINISH);
    }
    
    
    fpSetSlaveI2C(i2cAddress, _I2C_DIR_MASTER_RECEIVE);
    delay_ms (1);

    if(outCount == 1) 
    {
        res |= fpReadI2C(out, _I2C_MASTER_MODE_SINGLE_RECEIVE);
        delay_ms (1);
    }
    else if( outCount == 2 )
    {
        res |= fpReadI2C(out++, _I2C_MASTER_MODE_BURST_RECEIVE_START);
        delay_ms (1);
        res |= fpReadI2C(out, _I2C_MASTER_MODE_BURST_RECEIVE_FINISH);
    }
    else 
    {
        res |= fpReadI2C(out++ , _I2C_MASTER_MODE_BURST_RECEIVE_START);
        delay_ms (1);
        while(--outCount > 1)
        {
            res |= fpReadI2C(out++ , _I2C_MASTER_MODE_BURST_RECEIVE_CONT);
            Delay_ms(1);
        }
        res |= fpReadI2C(out, _I2C_MASTER_MODE_BURST_RECEIVE_FINISH);
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
/*------------------------------------------------------------- PREPROCESSORS */



/*--------------------------------------------------------------------- TYPES */



/*----------------------------------------------------------------- VARIABLES */



/*--------------------------------------------- PRIVATE FUNCTION DECLARATIONS */



/*---------------------------------------------- PRIVATE FUNCTION DEFINITIONS */



/*---------------------------------------------------------- PUBLIC FUNCTIONS */

void IRGRID2_initDriver
(
#if defined( __MIKROC_PRO_FOR_ARM__ )
    #if defined( __STM32__ ) || defined( __KINETIS__ ) || defined( __MCHP__ )

        uint8_t slaveAddress,
        T_IRGRID2_I2C_Start fpStart,
        T_IRGRID2_I2C_Write fpWrite, T_IRGRID2_I2C_Read fpRead
    #elif defined( __MSP__ )

        uint8_t slaveAddress,
        T_IRGRID2_I2C_Write fpWrite, T_IRGRID2_I2C_Read fpRead
    #elif defined( __TI__ )

        uint8_t slaveAddress,
        T_IRGRID2_I2C_SetSlaveAddress fpSlaveAddr,
        T_IRGRID2_I2C_Write fpWrite, T_IRGRID2_I2C_Read fpRead
    #endif

#elif defined( __MIKROC_PRO_FOR_AVR__ )   || \
      defined( __MIKROC_PRO_FOR_8051__ )  || \
      defined( __MIKROC_PRO_FOR_DSPIC__ ) || \
      defined( __MIKROC_PRO_FOR_PIC32__ ) || \
      defined( __MIKROC_PRO_FOR_PIC__ )

        uint8_t slaveAddress,
        T_IRGRID2_I2C_Start fpStart, T_IRGRID2_I2C_Stop fpStop,
        T_IRGRID2_I2C_Write fpWrite, T_IRGRID2_I2C_Read fpRead

#elif defined( __MIKROC_PRO_FOR_FT90x__ )

        uint8_t slaveAddress, T_IRGRID2_I2C_SetSlaveAddress fpSlaveAddr,
        T_IRGRID2_I2C_Write fpWrite, T_IRGRID2_I2C_Read fpRead

#else
        uint8_t slaveAddress,
        T_IRGRID2_I2C_Start fpStart, T_IRGRID2_I2C_Stop fpStop,
        T_IRGRID2_I2C_Write fpWrite, T_IRGRID2_I2C_Read fpRead
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

    //Performs a soft reset of the click
    IRGRID2_setConfig (_IRGRID2_RESET, _IRGRID2_CMD_RESET);
}

void IRGRID2_setConfig (uint8_t registerAddress, uint8_t registerValue )
{
     uint8_t writeData [2];
     writeData [0] = registerAddress;
     writeData [1] = registerValue;
     halWrite(writeData, 2);
}


uint8_t IRGRID2_readSingle (uint8_t registerAddress)
{
    uint8_t readData [1];
    
    //Data from sensors is read
    if (registerAddress > 0x05 && registerAddress < 0x10)
    {
         //Reading STATUS 1 and 2 registers is required
         readData [0] = _IRGRID2_STATUS1;
         halRead(readData, 1);
         
         if (readData [0] != 255)
         {
             return 0;  //Data is not ready
         }
         
         readData [0] = registerAddress;
         halRead(readData, 1);
         readData [1] = readData [0];  //saves the value into unused byte
         
         readData [0] = _IRGRID2_STATUS2;
         halRead(readData, 1);
         
         readData [0] = readData [1]; //loads the value
    }
    //Other registers are read
    else
    {
        readData [0] = registerAddress;
        halRead(readData, 1);
    }
    return readData [0];
}


void IRGRID2_readAll (uint8_t *pDataOut)
{
    uint8_t writeData [1];
    uint8_t *readData = pDataOut;
    readData [0] = 0x05;


    halRead( readData, 12);



   /*uint8_t writeData [1];
    uint8_t *readData = pDataOut;
    writeData [0] = 0x05;


    halTransfer(writeData, 1, readData, 12);*/

}


/*------------------------------------------------------------------------------

  __IRGRID2_Driver.c

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
/*

    __C4DOT_Driver.c

    Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

--------------------------------------------------------------------------------

    Version      : 1.0.0
    Developer    : Aleksandar Zecevic
    Date         : 07.06.2017

------------------------------------------------------------------------------*/

#include "__C4DOT_Driver.h"

/*----------------------------------------------------------------------- HAL */

static uint8_t i2cAddress;

extern sfr sbit C4DOT_WR_PIN;
extern sfr sbit C4DOT_CLR_PIN;
extern sfr sbit C4DOT_BL_PIN;

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

/*------------------------------------------------------------- PREPROCESSORS */

// MCP23017 Register Addresses (IOCON.BANK = 0)
#define _C4DOT_R_IODIRA   0x00
#define _C4DOT_R_IODIRB   0x01
#define _C4DOT_R_IPOLA    0x02
#define _C4DOT_R_IPOLB    0x03
#define _C4DOT_R_GPINTENA 0x04
#define _C4DOT_R_GPINTENB 0x05
#define _C4DOT_R_DEFVALA  0x06
#define _C4DOT_R_DEFVALB  0x07
#define _C4DOT_R_INTCONA  0x08
#define _C4DOT_R_INTCONB  0x09
#define _C4DOT_R_IOCON    0x0A
#define _C4DOT_R_GPPUA    0x0C
#define _C4DOT_R_GPPUB    0x0D
#define _C4DOT_R_INTFA    0x0E
#define _C4DOT_R_INTFB    0x0F
#define _C4DOT_R_INTCAPA  0x10
#define _C4DOT_R_INTCAPB  0x11
#define _C4DOT_R_GPIOA    0x12
#define _C4DOT_R_GPIOB    0x13
#define _C4DOT_R_OLATA    0x14
#define _C4DOT_R_OLATB    0x15

/*--------------------------------------------------------------------- TYPES */



/*----------------------------------------------------------------- VARIABLES */



/*--------------------------------------------- PRIVATE FUNCTION DECLARATIONS */

static void setGpioOutput();

/*---------------------------------------------- PRIVATE FUNCTION DEFINITIONS */

static void setGpioOutput()
{
    uint8_t buffer[3];
 
    buffer[0] = _C4DOT_R_IODIRA; // start with IODIRA and write 2 bytes
    buffer[1] = 0x00;            // PORTA as output
    buffer[2] = 0x00;            // PORTB as output
    halWrite(buffer, 3);
}

/*---------------------------------------------------------- PUBLIC FUNCTIONS */

void C4DOT_initDriver
(
#if defined( __MIKROC_PRO_FOR_ARM__ )
    #if defined( __STM32__ ) || defined( __KINETIS__ ) || defined( __MCHP__ )

        uint8_t slaveAddress,
        T_C4DOT_I2C_Start fpStart,
        T_C4DOT_I2C_Write fpWrite, T_C4DOT_I2C_Read fpRead
    #elif defined( __MSP__ )

        uint8_t slaveAddress,
        T_C4DOT_I2C_Write fpWrite, T_C4DOT_I2C_Read fpRead
    #elif defined( __TI__ )

        uint8_t slaveAddress,
        T_C4DOT_I2C_SetSlaveAddress fpSlaveAddr,
        T_C4DOT_I2C_Write fpWrite, T_C4DOT_I2C_Read fpRead
    #endif

#elif defined( __MIKROC_PRO_FOR_AVR__ )   || \
      defined( __MIKROC_PRO_FOR_8051__ )  || \
      defined( __MIKROC_PRO_FOR_DSPIC__ ) || \
      defined( __MIKROC_PRO_FOR_PIC32__ ) || \
      defined( __MIKROC_PRO_FOR_PIC__ )

        uint8_t slaveAddress,
        T_C4DOT_I2C_Start fpStart, T_C4DOT_I2C_Stop fpStop,
        T_C4DOT_I2C_Write fpWrite, T_C4DOT_I2C_Read fpRead

#elif defined( __MIKROC_PRO_FOR_FT90x__ )

        uint8_t slaveAddress, T_C4DOT_I2C_SetSlaveAddress fpSlaveAddr,
        T_C4DOT_I2C_Write fpWrite, T_C4DOT_I2C_Read fpRead

#else
        uint8_t slaveAddress,
        T_C4DOT_I2C_Start fpStart, T_C4DOT_I2C_Stop fpStop,
        T_C4DOT_I2C_Write fpWrite, T_C4DOT_I2C_Read fpRead
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

    setGpioOutput();
}

void C4DOT_writeChar(uint8_t charNum, uint8_t charValue)
{
    uint8_t buffer[2];

    // Return if charNum or charValue are invalid.
    if ((charNum > 3) || charValue > 127)
        return;

    buffer[0] = _C4DOT_R_OLATA; // address lines are connected to GPIOA
    buffer[1] = charNum;
    halWrite(buffer, 2);        // set address
    Delay_us(1);

    C4DOT_WR_PIN = 0;           // enable write
    Delay_us(1);
    
    buffer[0] = _C4DOT_R_OLATB; // data lines are connected to GPIOB
    buffer[1] = charValue;
    halWrite(buffer, 2);        // set data
    Delay_us(1);

    C4DOT_WR_PIN = 1;           // disable write
    Delay_us(1);
}

void C4DOT_writeChar0(uint8_t charValue)
{
    C4DOT_writeChar(0, charValue);
}

void C4DOT_writeChar1(uint8_t charValue)
{
    C4DOT_writeChar(1, charValue);
}

void C4DOT_writeChar2(uint8_t charValue)
{
    C4DOT_writeChar(2, charValue);
}

void C4DOT_writeChar3(uint8_t charValue)
{
    C4DOT_writeChar(3, charValue);
}

void C4DOT_writeText(uint8_t *textToWrite)
{
    uint16_t textLength;
    uint8_t index;

    textLength = strlen(textToWrite);

    // Clip text length so it fits on four characters.
    if (textLength > 4)
        textLength = 4;

    // Write the characters of the given text.
    for (index = 0; index < (uint8_t)textLength; index++)
        C4DOT_writeChar(3 - index, textToWrite[index]);
    
    // Fill the remaining characters with whitespace.
    while (index < 4)
        C4DOT_writeChar(index++, ' ');
}

void C4DOT_writeInt(int32_t intToWrite, uint8_t intBase)
{
    uint8_t digitToWrite;
    uint8_t index;
    uint8_t sign; // 0 - positive; 1 - negative

    index = 0; // start at the rightmost position
    sign = 0;

    // Is the number zero?
    if (intToWrite == 0)
    {
        C4DOT_writeChar3(' ');
        C4DOT_writeChar2(' ');
        C4DOT_writeChar1(' ');
        C4DOT_writeChar0('0');

        return;
    }

    // Is the number negative?
    if (intToWrite < 0)
    {
        sign = 1;
        intToWrite = -intToWrite;
    }

    while (intToWrite > 0)
    {
        // Get the next digit to write.
        digitToWrite = intToWrite % intBase;
        if (digitToWrite > 9)
            digitToWrite += -10 + 'A';
        else
            digitToWrite += '0';
        intToWrite /= intBase;

        C4DOT_writeChar(index++, digitToWrite);

        // Break if there's no more space to write the digits.
        if (index == 4)
            break;
    }

    // Is there space left?
    if (index < 4)
    {
        // Fill the first space with either '-' or ' '.
        if (sign == 1)
            C4DOT_writeChar(index++, '-');
        else
            C4DOT_writeChar(index++,' ');
            
        // Fill the remaining spaces.
        while (index < 4)
            C4DOT_writeChar(index++, ' ');
    }
}

void C4DOT_writeIntBin(int32_t intToWrite)
{
    C4DOT_writeInt(intToWrite, 2);
}

void C4DOT_writeIntOct(int32_t intToWrite)
{
    C4DOT_writeInt(intToWrite, 8);
}

void C4DOT_writeIntDec(int32_t intToWrite)
{
    C4DOT_writeInt(intToWrite, 10);
}

void C4DOT_writeIntHex(int32_t intToWrite)
{
    C4DOT_writeInt(intToWrite, 16);
}

void C4DOT_clearDisplay()
{
    C4DOT_CLR_PIN = 0;
    Delay_ms(1);       // hold CLR low for 1 ms
    C4DOT_CLR_PIN = 1;
}

/*------------------------------------------------------------------------------

  __C4DOT_Driver.c

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
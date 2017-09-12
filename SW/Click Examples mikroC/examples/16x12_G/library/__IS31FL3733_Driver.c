/*

    __IS31FL3733_Driver.c

    Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

------------------------------------------------------------------------------*/

/**
@file           __IS31FL3733_Driver.c
@addtogroup     IS31FL3733
@{
------------------------------------------------------------------------------*/

#include "__IS31FL3733_Driver.h"

///@cond
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

static void ( *fpSetSlaveI2C )(uint8_t slaveAddres);
static unsigned char ( *fpWriteI2C )(unsigned char *pBuf, unsigned int count);
static unsigned char ( *fpReadI2C )(unsigned char *pBuf, unsigned int count);
#else
static void ( *fpStartI2C )();
static void ( *fpStopI2C )();
static void ( *fpWriteI2C )(uint8_t input);
static uint8_t ( *fpReadI2C )(uint8_t input);
#endif

static int halWrite( uint8_t *pBuf, uint16_t count)
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

static int halRead( uint8_t *pBuf, uint16_t count)
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

static int halTransfer( uint8_t *pIn, uint16_t inCount, uint8_t *pOut, uint16_t outCount)
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
///@endcond
/*----------------------------------------------------------------- VARIABLES */

/**
 * IS31FL3733 restart bit. Needs to be kept low for chip to operate normally.
 */
extern sfr sbit IS31FL3733_RST_PIN;
/**
 * IS31FL3733 shutdown bit. When pulled to low it shuts down the chip.
 */
extern sfr sbit IS31FL3733_SDB_PIN;
///@cond
/**
 * IS31FL3733 base address on I2C bus.
 */
static const uint8_t _IS31FL3733_I2C_BASE_ADDR = 0xA0;

/*--------------------------------------------- PRIVATE FUNCTION DECLARATIONS */

static uint8_t i2cRealAddr( uint8_t addr2, uint8_t addr1);
static uint8_t getRegPage( uint16_t regAddr );
static uint8_t getAddr( uint16_t regAddr );

static uint8_t i2cWriteReg( uint8_t i2cAddr, uint8_t regAddr,
                      uint8_t *buffer, uint8_t count);
static uint8_t i2cReadReg( uint8_t i2cAddr, uint8_t regAddr,
                      uint8_t *buffer, uint8_t count);

/*---------------------------------------------- PRIVATE FUNCTION DEFINITIONS */

static uint8_t i2cRealAddr( uint8_t addr2, uint8_t addr1)
{
    return (_IS31FL3733_I2C_BASE_ADDR | (addr2 << 3) | (addr1 << 1)) >> 1;
}

/// Get register page.
static uint8_t getRegPage( uint16_t regAddr )
{
    return (uint8_t)((regAddr) >> 8);
}
/// Get register 8-bit address.
static uint8_t getAddr( uint16_t regAddr )
{
    return (uint8_t)(regAddr);
}

static uint8_t i2cWriteReg( uint8_t i2cAddr, uint8_t regAddr,
                      uint8_t *buffer, uint8_t count)
{
     int i;
     uint8_t buff[2];
     i2cAddress = i2cAddr;
     for ( i = 0; i < count; ++i )
     {
       buff[0] = regAddr+i;
       buff[1] = buffer[i];
       halWrite( buff, 2 );
     }
     return count;
}

static uint8_t i2cReadReg( uint8_t i2cAddr, uint8_t regAddr,
                      uint8_t *buffer, uint8_t count)
{
     uint8_t buff[1];
     i2cAddress = i2cAddr;
     buff[0] = regAddr;
     halRead( buff, 1 );
     *buffer = buff[0];
     return buff[0];
}
///@endcond
/*---------------------------------------------------------- PUBLIC FUNCTIONS */

void IS31FL3733_init(
#if defined( __MIKROC_PRO_FOR_ARM__ )
    #if defined( __STM32__ ) || defined( __KINETIS__ ) || defined( __MCHP__ )

        T_IS31FL3733 *device, uint8_t addr2, uint8_t addr1,
        T_IS31FL3733_I2C_Start fpStart,
        T_IS31FL3733_I2C_Write fpWrite, T_IS31FL3733_I2C_Read fpRead
    #elif defined( __MSP__ )

        T_IS31FL3733 *device, uint8_t uint8_t addr2, uint8_t addr1,
        T_IS31FL3733_I2C_Write fpWrite, T_IS31FL3733_I2C_Read fpRead
    #elif defined( __TI__ )

        T_IS31FL3733 *device, uint8_t addr2, uint8_t addr1,
        T_IS31FL3733_I2C_SetSlaveAddress fpSlaveAddr,
        T_IS31FL3733_I2C_Write fpWrite, T_IS31FL3733_I2C_Read fpRead
    #endif

#elif defined( __MIKROC_PRO_FOR_AVR__ )   || \
      defined( __MIKROC_PRO_FOR_8051__ )  || \
      defined( __MIKROC_PRO_FOR_DSPIC__ ) || \
      defined( __MIKROC_PRO_FOR_PIC32__ ) || \
      defined( __MIKROC_PRO_FOR_PIC__ )

        T_IS31FL3733 *device, uint8_t addr2, uint8_t addr1,
        T_IS31FL3733_I2C_Start fpStart, T_IS31FL3733_I2C_Stop fpStop,
        T_IS31FL3733_I2C_Write fpWrite, T_IS31FL3733_I2C_Read fpRead

#elif defined( __MIKROC_PRO_FOR_FT90x__ )

        T_IS31FL3733 *device, uint8_t addr2, uint8_t addr1,
        T_IS31FL3733_I2C_SetSlaveAddress fpSlaveAddr,
        T_IS31FL3733_I2C_Write fpWrite, T_IS31FL3733_I2C_Read fpRead

#else
        T_IS31FL3733 *device, uint8_t addr2, uint8_t addr1,
        T_IS31FL3733_I2C_Start fpStart, T_IS31FL3733_I2C_Stop fpStop,
        T_IS31FL3733_I2C_Write fpWrite, T_IS31FL3733_I2C_Read fpRead
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

    i2cAddress     = i2cRealAddr(addr2, addr1);

    device->address = i2cAddress;
    device->i2cWriteReg = i2cWriteReg;
    device->i2cReadReg = i2cReadReg;
    // Read reset register to reset device.
    IS31FL3733_readPagedReg( device, _IS31FL3733_RESET );
    // Clear software reset in configuration register.
    IS31FL3733_writePagedReg( device, _IS31FL3733_CR, _IS31FL3733_CR_SSD );
    // Clear state of all LEDs in internal buffer and sync buffer to device.
    IS31FL3733_setLEDState( device, _IS31FL3733_CS, _IS31FL3733_SW,
                            _IS31FL3733_LED_STATE_OFF );
    IS31FL3733_SDB_PIN = 1;
}

uint8_t IS31FL3733_readCommonReg( T_IS31FL3733 *device, uint8_t regAddr )
{
  uint8_t regValue;
  
  // Read value from register.
  device->i2cReadReg( device->address, regAddr, &regValue, sizeof(uint8_t) );
  // Return register value.
  return regValue;
}

void IS31FL3733_writeCommonReg( T_IS31FL3733 *device, uint8_t regAddr,
                                uint8_t regValue )
{
  // Write value to register.
  device->i2cWriteReg( device->address, regAddr, &regValue, sizeof( uint8_t ) );
}

void IS31FL3733_selectPage( T_IS31FL3733 *device, uint8_t page )
{
  // Unlock Command Register.
  uint8_t buff;
  device->i2cReadReg( device->address, 0xFE, &buff, 1 );
  IS31FL3733_writeCommonReg ( device, _IS31FL3733_PSWL,
                            _IS31FL3733_PSWL_ENABLE );
  device->i2cReadReg( device->address, 0xFE, &buff, 1 );
  // Select requested page in Command Register.
  IS31FL3733_writeCommonReg ( device, _IS31FL3733_PSR, page );
}

uint8_t IS31FL3733_readPagedReg( T_IS31FL3733 *device, uint16_t regAddr )
{
  uint8_t regValue;
  
  // Select register page.
  IS31FL3733_selectPage( device, getRegPage(regAddr));
  // Read value from register.
  device->i2cReadReg( device->address, getAddr( regAddr ),
                      &regValue, sizeof( uint8_t ) );
  // Return register value.
  return regValue;
}

void IS31FL3733_writePagedReg( T_IS31FL3733 *device, uint16_t regAddr,
                               uint8_t regValue )
{
  // Select register page.
  IS31FL3733_selectPage( device, getRegPage( regAddr ) );
  // Write value to register.
  device->i2cWriteReg( device->address, getAddr( regAddr ),
                       &regValue, sizeof( uint8_t ) );
}

void IS31FL3733_writePagedRegs( T_IS31FL3733 *device, uint16_t regAddr,
                                uint8_t *values, uint8_t count )
{
  // Select registers page.
  IS31FL3733_selectPage( device, getRegPage( regAddr ) );
  // Write values to registers.
  device->i2cWriteReg( device->address, getAddr( regAddr ),
                       values, count );
}

void IS31FL3733_setGCC( T_IS31FL3733 *device, uint8_t gcc )
{
  // Write gcc value to Global Current Control (GCC) register.
  IS31FL3733_writePagedReg( device, _IS31FL3733_GCC, gcc );
}

void IS31FL3733_setSWPUR( T_IS31FL3733 *device,
                          T_IS31FL3733_RESISTOR resistor )
{
  // Write resistor value to SWPUR register.
  IS31FL3733_writePagedReg( device, _IS31FL3733_SWPUR, resistor );
}

void IS31FL3733_setCSPDR( T_IS31FL3733 *device, T_IS31FL3733_RESISTOR resistor )
{
  // Write resistor value to CSPDR register.
  IS31FL3733_writePagedReg( device, _IS31FL3733_CSPDR, resistor );
}

void IS31FL3733_setLEDState( T_IS31FL3733 *device, uint8_t cs, uint8_t sw,
                             T_IS31FL3733_LED_STATE state )
{
  uint8_t offset;
  
  // Check SW boundaries.
  if ( sw < _IS31FL3733_SW )
  {
    // Check CS boundaries.
    if ( cs < _IS31FL3733_CS )
    {
      // Set state of individual LED.
      // Calculate LED bit offset.
      offset = ( sw << 1 ) + ( cs / 8 );
      // Update state of LED in internal buffer.
      if ( state == _IS31FL3733_LED_STATE_OFF )
      {
        // Clear bit for selected LED.
        device->leds[ offset ] &= ~( 0x01 << ( cs % 8 ) );
      }
      else
      {
        // Set bit for selected LED.
        device->leds[ offset ] |= 0x01 << ( cs % 8 );
      }
      // Write updated LED state to device register.
      IS31FL3733_writePagedReg( device, _IS31FL3733_LEDONOFF + offset,
                                device->leds[ offset ] );
    }
    else
    {
      // Set state of full row selected by SW.
      // Calculate row offset.
      offset = sw << 1;
      // Update state of row LEDs in internal buffer.
      if ( state == _IS31FL3733_LED_STATE_OFF )
      {
        // Clear 16 bits for selected row LEDs.
        device->leds[ offset ] = 0x00;
        device->leds[ offset + 1 ] = 0x00;
      }
      else
      {
        // Set 16 bits for selected row LEDs.
        device->leds[ offset ] = 0xFF;
        device->leds[ offset + 1 ] = 0xFF;
      }
      // Write updated LEDs state to device registers.
      IS31FL3733_writePagedRegs( device, _IS31FL3733_LEDONOFF + offset,
                                 &device->leds[ offset ], _IS31FL3733_CS / 8);
    }
  }
  else
  {
    // Check CS boundaries.
    if ( cs < _IS31FL3733_CS )
    {
      // Set state of full column selected by CS.
      for ( sw = 0; sw < _IS31FL3733_SW; sw++ )
      {
        // Calculate LED bit offset.
        offset = ( sw << 1 ) + ( cs / 8 );
        // Update state of LED in internal buffer.
        if ( state == _IS31FL3733_LED_STATE_OFF )
        {
          // Clear bit for selected LED.
          device->leds[ offset ] &= ~( 0x01 << ( cs % 8 ) );
        }
        else
        {
          // Set bit for selected LED.
          device->leds[ offset ] |= 0x01 << ( cs % 8 );
        }
        // Write updated LED state to device register.
        IS31FL3733_writePagedReg( device, _IS31FL3733_LEDONOFF + offset,
                                  device->leds[ offset ] );
      }
    }
    else
    {
      // Set state of all LEDs.
      for ( sw = 0; sw < _IS31FL3733_SW; sw++ )
      {
        // Update state of all LEDs in internal buffer.
        if ( state == _IS31FL3733_LED_STATE_OFF )
        {
          // Clear all bits.
          device->leds[ ( sw << 1 ) ] = 0x00;
          device->leds[ ( sw << 1 ) + 1 ] = 0x00;
        }
        else
        {
          // Set all bits.
          device->leds[ ( sw << 1 ) ] = 0xFF;
          device->leds[ ( sw << 1 ) + 1 ] = 0xFF;
        }
      }
      // Write updated LEDs state to device registers.
      IS31FL3733_writePagedRegs( device, _IS31FL3733_LEDONOFF, device->leds,
                                 _IS31FL3733_SW * _IS31FL3733_CS / 8 );
    }
  }
}

void IS31FL3733_setLEDPWM( T_IS31FL3733 *device, uint8_t cs, uint8_t sw,
                           uint8_t value )
{
  uint8_t offset;
  
  // Check SW boundaries.
  if ( sw < _IS31FL3733_SW )
  {
    // Check CS boundaries.
    if ( cs < _IS31FL3733_CS )
    {
      // Set PWM of individual LED.
      // Calculate LED offset.
      offset = sw * _IS31FL3733_CS + cs;
      // Write LED PWM value to device register.
      IS31FL3733_writePagedReg( device, _IS31FL3733_LEDPWM + offset, value );
    }
    else
    {
      // Set PWM of full row selected by SW.
      for ( cs = 0; cs < _IS31FL3733_CS; cs++ )
      {
        // Calculate LED offset.
        offset = sw * _IS31FL3733_CS + cs;
        // Write LED PWM value to device register.
        IS31FL3733_writePagedReg( device, _IS31FL3733_LEDPWM + offset, value );
      }
    }
  }
  else
  {
    // Check CS boundaries.
    if ( cs < _IS31FL3733_CS )
    {
      // Set PWM of full column selected by CS.
      for ( sw = 0; sw < _IS31FL3733_SW; sw++ )
      {
          // Calculate LED offset.
          offset = sw * _IS31FL3733_CS + cs;
          // Write LED PWM value to device register.
          IS31FL3733_writePagedReg( device, _IS31FL3733_LEDPWM + offset,
                                    value );
      }
    }
    else
    {
      // Set PWM of all LEDs.
      for ( sw = 0; sw < _IS31FL3733_SW; sw++ )
      {
        for ( cs = 0; cs < _IS31FL3733_CS; cs++ )
        {
          // Calculate LED offset.
          offset = sw * _IS31FL3733_CS + cs;
          // Write LED PWM value to device register.
          IS31FL3733_writePagedReg( device, _IS31FL3733_LEDPWM + offset,
                                    value );
        }
      }
    }
  }
}

T_IS31FL3733_LED_STATUS IS31FL3733_getLEDStatus( T_IS31FL3733 *device,
                                                 uint8_t cs, uint8_t sw )
{
  uint8_t offset;
  
  // Check CS and SW boundaries.
  if ( ( cs < _IS31FL3733_CS ) && ( sw < _IS31FL3733_SW ) )
  {
    // Calculate LED bit offset.
    offset = ( sw << 1 ) + ( cs / 8 );
    // Get Open status from device register.
    if ( IS31FL3733_readPagedReg( device,
         _IS31FL3733_LEDOPEN + offset ) & ( 0x01 << ( cs % 8 ) ) )
    {
      return _IS31FL3733_LED_STATUS_OPEN;
    }
    // Get Short status from device register.
    if ( IS31FL3733_readPagedReg( device,
         _IS31FL3733_LEDSHORT + offset ) & ( 0x01 << ( cs % 8 ) ) )
    {
      return _IS31FL3733_LED_STATUS_SHORT;
    }
  }
  else
  {
    // Unknown status for nonexistent LED.
    return _IS31FL3733_LED_STATUS_UNKNOWN;
  }
  return _IS31FL3733_LED_STATUS_NORMAL;
}

void IS31FL3733_setState ( T_IS31FL3733 *device, uint8_t *states )
{
  uint8_t sw;
  uint8_t cs;
  uint8_t offset;
  
  // Set state of all LEDs.
  for ( sw = 0; sw < _IS31FL3733_SW; sw++ )
  {
    for ( cs = 0; cs < _IS31FL3733_CS; cs++ )
    {
      // Calculate LED bit offset.
      offset = ( sw << 1 ) + ( cs / 8 );
      // Update state of LED in internal buffer.
      if ( states[ sw * _IS31FL3733_CS + cs ] == 0 )
      {
        // Clear bit for selected LED.
        device->leds[ offset ] &= ~( 0x01 << ( cs % 8 ) );
      }
      else
      {
        // Set bit for selected LED.
        device->leds[ offset ] |= 0x01 << ( cs % 8 );
      }
    }
  }
  // Write updated LEDs state to device registers.
  IS31FL3733_writePagedRegs( device, _IS31FL3733_LEDONOFF, device->leds,
                             _IS31FL3733_SW * _IS31FL3733_CS / 8 );
}

void IS31FL3733_setPWM( T_IS31FL3733 *device, uint8_t *values )
{
  // Write LED PWM values to device registers.
  IS31FL3733_writePagedRegs( device, _IS31FL3733_LEDPWM, values,
                             _IS31FL3733_SW * _IS31FL3733_CS );
}

void IS31FL3733_clearMatrix( T_IS31FL3733 *device)
{
    uint8_t zeros[ _IS31FL3733_CS * _IS31FL3733_SW ];
    uint8_t i;
    memset( zeros, 0x00, _IS31FL3733_CS * _IS31FL3733_SW );
    // Set LED PWM values to zero
    IS31FL3733_setPWM( device, zeros );
    // Set LED state to OFF
    for ( i = 0; i < _IS31FL3733_SW; ++i )
    {
        IS31FL3733_setLEDState( device, _IS31FL3733_CS, i,
                                   _IS31FL3733_LED_STATE_OFF );
    }
}

void IS31FL3733_setLEDMode( T_IS31FL3733 *device, uint8_t cs, uint8_t sw,
                             T_IS31FL3733_LED_MODE mode )
{
  uint8_t offset;

  // Check SW boundaries.
  if (sw < _IS31FL3733_SW)
  {
    // Check CS boundaries.
    if (cs < _IS31FL3733_CS)
    {
      // Set mode of individual LED.
      // Calculate LED offset.
      offset = sw * _IS31FL3733_CS + cs;
      // Write LED mode to device register.
      IS31FL3733_writePagedReg( device, _IS31FL3733_LEDABM + offset, mode );
    }
    else
    {
      // Set mode of full row selected by SW.
      for (cs = 0; cs < _IS31FL3733_CS; cs++)
      {
        // Calculate LED offset.
        offset = sw * _IS31FL3733_CS + cs;
        // Write LED mode to device register.
        IS31FL3733_writePagedReg (device, _IS31FL3733_LEDABM + offset, mode);
      }
    }
  }
  else
  {
    // Check CS boundaries.
    if (cs < _IS31FL3733_CS)
    {
      // Set mode of full column selected by CS.
      for (sw = 0; sw < _IS31FL3733_SW; sw++)
      {
          // Calculate LED offset.
          offset = sw * _IS31FL3733_CS + cs;
          // Write LED mode to device register.
          IS31FL3733_writePagedReg (device, _IS31FL3733_LEDABM + offset, mode);
      }
    }
    else
    {
      // Set mode of all LEDs.
      for (sw = 0; sw < _IS31FL3733_SW; sw++)
      {
        for (cs = 0; cs < _IS31FL3733_CS; cs++)
        {
          // Calculate LED offset.
          offset = sw * _IS31FL3733_CS + cs;
          // Write LED mode to device register.
          IS31FL3733_writePagedReg (device, _IS31FL3733_LEDABM + offset, mode);
        }
      }
    }
  }
}

void IS31FL3733_configABM( T_IS31FL3733 *device, T_IS31FL3733_ABM_NUM n,
                           T_IS31FL3733_ABM *config )
{
  // Set fade in and fade out time.
  IS31FL3733_writePagedReg( device, n, config->T1 | config->T2 );
  // Set hold and off time.
  IS31FL3733_writePagedReg( device, n + 1, config->T3 | config->T4 );
  // Set loop begin/end time and high part of loop times.
  IS31FL3733_writePagedReg( device, n + 2,
                            config->end | config->begin
                            | ((config->times >> 8) & 0x0F) );
  // Set low part of loop times.
  IS31FL3733_writePagedReg( device, n + 3, config->times & 0xFF );
}

void IS31FL3733_startABM( T_IS31FL3733 *device )
{
  // Clear B_EN bit in configuration register.
  IS31FL3733_writePagedReg (device, _IS31FL3733_CR, _IS31FL3733_CR_SSD);
  // Set B_EN bit in configuration register.
  IS31FL3733_writePagedReg (device, _IS31FL3733_CR, _IS31FL3733_CR_BEN | _IS31FL3733_CR_SSD);
  // Write 0x00 to Time Update Register to update ABM settings.
  IS31FL3733_writePagedReg (device, _IS31FL3733_TUR, 0x00);
}

///@}
/*------------------------------------------------------------------------------

  __IS31FL3733_Driver.c

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
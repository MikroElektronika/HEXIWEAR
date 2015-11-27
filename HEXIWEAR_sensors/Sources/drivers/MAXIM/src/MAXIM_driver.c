/**
 * MAXIM-related driver functions
 * Project HEXIWEAR, 2015
 */

/**
 * intern variables
 */
#include "HEXIWEAR_types.h"

#include "MAXIM_driver.h"
#include "MAXIM_info.h"
#include "generic_i2c_driver.h"

#include "string.h"
#include "error.h"

static handleMAXIM_t
  self;

static settingsMAXIM_t
  settings;

static uint8_t
  channelsPerSample = 0;

/**
 * intern functions
 */

/**
 * visible functions
 */

/**
 * initialize MAXIM module
 */
statusMAXIM_t MAXIM_Init(
                                  handleMAXIM_t* maximHandle,
                          const settingsMAXIM_t* maximSettings
                        )
{
  statusI2C_t
    status = I2C_Init( &(maximHandle->protocol), maximSettings->address );

  if ( STATUS_I2C_SUCCESS != status )
  {
    return STATUS_MAXIM_INIT_ERROR;
  }

  else
  {
    /**
     * initialize intern structures,
     * which will be used from now on
     */

    memcpy( (void*)&self,     (void*)maximHandle,   sizeof(self) );
    memcpy( (void*)&settings, (void*)maximSettings, sizeof(settings) );

    uint8_t
      foo = 0;

    // read revision ID
    statusI2C_t
      i2cStatus = STATUS_I2C_SUCCESS;

    genericI2cHandle_t
      i2cProtocol = self.protocol;

    uint8_t
      revID  = 0,
      partID = 0;

    // read revision ID
    i2cStatus |= I2C_ReadReg( &i2cProtocol, MAXIM_REG_ID_REV, &revID );

    // read part ID
    i2cStatus |= I2C_ReadReg( &i2cProtocol, MAXIM_REG_ID_PART, &partID );

    /**
     * set up the registers
     */

    // reset the module
    i2cStatus |= MAXIM_Reset();

    // LED amplitude -> max
    i2cStatus |= I2C_WriteReg( &i2cProtocol, MAXIM_REG_LED1_PA , 0x7F );
    i2cStatus |= I2C_WriteReg( &i2cProtocol, MAXIM_REG_LED2_PA , 0x7F );
    i2cStatus |= I2C_WriteReg( &i2cProtocol, MAXIM_REG_LED3_PA , 0x7F );

    // set the slots
//    foo = ( settings.slot1 << MAXIM_SLOT_1_3_SHIFT ) | ( settings.slot2 << MAXIM_SLOT_2_4_SHIFT );
//    i2cStatus |= I2C_writeReg( &i2cProtocol, MAXIM_REG_MULTILED_MODE_CR_12 , foo );
//
//    foo = ( settings.slot3 << MAXIM_SLOT_1_3_SHIFT ) | ( settings.slot4 << MAXIM_SLOT_2_4_SHIFT );
//    i2cStatus |= I2C_writeReg( &i2cProtocol, MAXIM_REG_MULTILED_MODE_CR_34 , foo );

    foo = ( slotGreen << MAXIM_SLOT_1_3_SHIFT ) | ( slotGreen << MAXIM_SLOT_2_4_SHIFT );
    i2cStatus |= I2C_WriteReg( &i2cProtocol, MAXIM_REG_MULTILED_MODE_CR_12 , foo );
    foo = ( slotGreen << MAXIM_SLOT_1_3_SHIFT ) | ( slotGreen << MAXIM_SLOT_2_4_SHIFT );
    i2cStatus |= I2C_WriteReg( &i2cProtocol, MAXIM_REG_MULTILED_MODE_CR_34 , foo );

    // set the timings
    i2cStatus |= I2C_WriteReg( &i2cProtocol, MAXIM_REG_SPO2_CFG , settings.pulseWidth << MAXIM_SPO2_LED_PW_SHIFT );

    // clear FIFO pointers
    i2cStatus |= I2C_WriteReg( &i2cProtocol, MAXIM_REG_FIFO_WR_PTR , 0 );
    i2cStatus |= I2C_WriteReg( &i2cProtocol, MAXIM_REG_FIFO_RD_PTR , 0 );
    i2cStatus |= I2C_WriteReg( &i2cProtocol, MAXIM_REG_FIFO_OV_PTR , 0 );

    // set the mode
    i2cStatus |= I2C_WriteReg( &i2cProtocol, MAXIM_REG_MODE_CFG , settings.mode << MAXIM_MODE_SHIFT );
//    i2cStatus |= I2C_writeReg( &i2cProtocol, MAXIM_REG_MODE_CFG , modeMultiLED << MAXIM_MODE_SHIFT );

    switch ( settings.mode )
    {
      case modeHR:        {
                            channelsPerSample = 1;
                            break;
                          }

      case modeSPO2:      {
                            channelsPerSample = 2;
                            break;
                          }

      case modeMultiLED:  {
                            channelsPerSample = 3;
                            break;
                          }

      default: {}
    }

    // read FIFO pointers
    i2cStatus |= I2C_ReadReg( &i2cProtocol, MAXIM_REG_FIFO_WR_PTR , &foo );
    i2cStatus |= I2C_ReadReg( &i2cProtocol, MAXIM_REG_FIFO_RD_PTR , &foo );
    i2cStatus |= I2C_ReadReg( &i2cProtocol, MAXIM_REG_FIFO_OV_PTR , &foo );

    if ( STATUS_I2C_SUCCESS != i2cStatus )
    {
      catch(11);
      return STATUS_MAXIM_PROTOCOL_ERROR;
    }

    else
    {
      return STATUS_MAXIM_SUCCESS;
    }
  }
}

/**
 * shutdown the sensor
 */
statusMAXIM_t MAXIM_Deinit()
{
  statusI2C_t
    status = I2C_Deinit( &(self.protocol) );

  if ( STATUS_I2C_SUCCESS != status )
  {
    catch(11);
    return STATUS_MAXIM_PROTOCOL_ERROR;
  }

  else
  {
    return STATUS_MAXIM_SUCCESS;
  }
}

/**
 * reset the module
 * when the reset-bit is set to one, all configuration, threshold,
 * and data registers are reset to their power-on-state through
 * a power-on reset
 *
 * the reset bit is cleared automatically back to zero after the reset sequence is completed
 */
statusMAXIM_t MAXIM_Reset()
{
  uint8_t
    timeoutCnt = 0;

  statusI2C_t
    i2cStatus = 0;

  uint8_t
    foo = 0;

  // reset the module
  I2C_WriteReg( &(self.protocol), MAXIM_REG_MODE_CFG , MAXIM_MODE_RST_BIT );

  // poll the RESET bit until it's cleared by hardware
  while (1)
  {
    i2cStatus = I2C_ReadReg( &(self.protocol), MAXIM_REG_MODE_CFG , &foo );

    if ( STATUS_I2C_SUCCESS != i2cStatus )
    {
      catch(11);
      return STATUS_MAXIM_PROTOCOL_ERROR;
    }

    else
    {
      if ( 0 == ( foo & MAXIM_MODE_RST_BIT ) )
      {
        return STATUS_MAXIM_SUCCESS;
      }

      else
      {
        // wait a bit
        OSA_TimeDelay(10);
        timeoutCnt++;

        // leave if the module is stuck
        if ( timeoutCnt > 5)
        {
          catch(11);
          return STATUS_MAXIM_TIMEOUT;
        }
      }
    }
  }
}

/**
 * read FIFO buffer
 */
statusMAXIM_t MAXIM_ReadFIFO(
                              uint32_t* ledVal
                            )
{
  genericI2cHandle_t
    i2cProtocol = self.protocol;

  uint8_t
    cmd[1] =  {
                MAXIM_REG_FIFO_DATA
              };

  uint8_t
    dataBuff[MAXIM_BYTES_PER_SAMPLE];

  // read number of requested samples
  i2c_status_t
    status = I2C_DRV_MasterReceiveDataBlocking(
                                                i2cProtocol.instance,
                                                &(i2cProtocol.device),

                                                (const uint8_t*)cmd,
                                                sizeof(cmd) / sizeof(cmd[0]),

                                                (uint8_t*)dataBuff,
                                                MAXIM_BYTES_PER_SAMPLE,

                                                i2cProtocol.timeout
                                              );

  if ( kStatus_I2C_Success != status )
  {
    catch(11);
    return STATUS_MAXIM_PROTOCOL_ERROR;
  }
  else
  {
    *ledVal =   ( ( (uint32_t)dataBuff[0] ) << 16 )
              | ( ( (uint32_t)dataBuff[1] ) << 8 )
              | ( ( (uint32_t)dataBuff[2] ) << 0 );

    return STATUS_MAXIM_SUCCESS;
  }
}

/**
 * read raw sensor data
 */
statusMAXIM_t MAXIM_ReadRawData (
                                  uint32_t* sensorData,
                                  uint32_t* sampleNum
                                )
{
  statusI2C_t
    i2cStatus = STATUS_I2C_SUCCESS;

  uint8_t
    fifoWrPtr    = 0,
    fifoRdPtr    = 0,
    fifoOvPtr    = 0;

  uint32_t
    samIdx = 0;

  statusMAXIM_t
    devStatus = STATUS_MAXIM_SUCCESS;

  genericI2cHandle_t
    i2cProtocol = self.protocol;

  // read FIFO pointers
  i2cStatus |= I2C_ReadReg( &i2cProtocol, MAXIM_REG_FIFO_RD_PTR , &fifoRdPtr );
  i2cStatus |= I2C_ReadReg( &i2cProtocol, MAXIM_REG_FIFO_WR_PTR , &fifoWrPtr );
  i2cStatus |= I2C_ReadReg( &i2cProtocol, MAXIM_REG_FIFO_OV_PTR , &fifoOvPtr );

  if ( fifoOvPtr > 0 )
  {
    *sampleNum = MAXIM_FIFO_DEPTH;
  }

  else
  {
    if ( fifoWrPtr > fifoRdPtr )
    {
      *sampleNum = fifoWrPtr - fifoRdPtr;
    }

    // FIFO WR pointer rolled over
    else
    {
      *sampleNum = ( fifoWrPtr + MAXIM_FIFO_DEPTH ) - fifoRdPtr;
    }
  }

  while ( samIdx < *sampleNum )
  {
    switch ( settings.mode )
    {
      case modeHR:        {
                            devStatus |= MAXIM_ReadFIFO( &( sensorData[samIdx++] ) ); // RED diode
                            break;
                          }

      case modeSPO2:      {
                            devStatus |= MAXIM_ReadFIFO( &( sensorData[samIdx++] ) ); // RED diode
                            devStatus |= MAXIM_ReadFIFO( &( sensorData[samIdx++] ) ); // IR diode
                            break;
                          }

      case modeMultiLED:  {
                            break;
                          }

      default: {}
    }
  }

  if ( STATUS_MAXIM_SUCCESS != devStatus )
  {
    catch(11);
    return STATUS_MAXIM_ERROR;
  }
  else
  {
    return STATUS_MAXIM_SUCCESS;
  }
}

/**
 * format raw to float
 * @param src original data array
 * @param dst new format data array
 * @param idx index of the sample to be formatted
 */
void hr_fmtDef2Float(
                      const void* src,
                            void* dst,
                         uint32_t idx
                    )
{
  /**
   * helper pointers
   */

  uint16_t*
    input = (uint16_t*)src;
  float*
    output = (float*)dst;

  // convert data
  // ...
}

/**
 * format raw to mE format
 * @param src original data array
 * @param dst new format data array
 * @param idx index of the sample to be formatted
 */
void hr_fmtDef2Me (
                    const void* src,
                          void* dst,
                       uint32_t idx
                  )
{
  /**
   * helper pointers
   */

  uint32_t*
    input = (uint32_t*)src;
  mE_t*
    output = (mE_t*)dst;

  // convert data -- doing nothing atm
  output[idx] = input[idx];
}

/**
 * MAXIM-related driver functions
 * Project HEXIWEAR, 2015
 */

/**
 * intern variables
 */
#include "HEXIWEAR_types.h"
#include "HEXIWEAR_info.h"

#include "MAXIM_driver.h"
#include "MAXIM_defs.h"
#include "MAXIM_info.h"

#include "generic_i2c_driver.h"

#include "string.h"
#include "error.h"

#include "math.h"

#if defined (MAXIM_DEBUG)
#include "fsl_debug_console.h"
#endif

static handleMAXIM_t
  self;

static settingsMAXIM_t
  settings;

static dataMAXIM_t**
  ledBuffers = 0;

static bool
	isMaximEnabled = false;

static maxim_callback_t
    maxim_callback = NULL;

static uint8_t
    maxim_bytesPerSample;

static uint32_t
	maxim_bitMask;

/**
 * initialize MAXIM module
 */
maxim_status_t MAXIM_Init(
                                  handleMAXIM_t* maximHandle,
                          const settingsMAXIM_t* maximSettings
                        )
{
    /**
    * initialize intern structures,
    * which will be used from now on
    */

    memcpy( (void*)&self,     (void*)maximHandle,   sizeof(self) );
    memcpy( (void*)&settings, (void*)maximSettings, sizeof(settings) );

    statusI2C_t
    	status = I2C_Init( &(self.protocol), settings.address, settings.baudRate_kbps );

    if ( STATUS_I2C_SUCCESS != status )
    {
    return STATUS_MAXIM_INIT_ERROR;
    }

    else
    {
        // read revision ID
        statusI2C_t
          i2cStatus = STATUS_I2C_SUCCESS;

        genericI2cHandle_t
          i2cProtocol = self.protocol;

        /**
         * set up the registers
         */

        i2cStatus |= MAXIM_Reset();

        OSA_TimeDelay(50);

        i2cStatus |= I2C_WriteReg( &i2cProtocol, MAXIM_REG_LED_RED_PA,   0xFF );
        i2cStatus |= I2C_WriteReg( &i2cProtocol, MAXIM_REG_LED_IR_PA,    0x33 );
        i2cStatus |= I2C_WriteReg( &i2cProtocol, MAXIM_REG_LED_GREEN_PA, 0xFF );
        i2cStatus |= I2C_WriteReg( &i2cProtocol, MAXIM_REG_PROXY_PA,     0x19 );

        i2cStatus |= I2C_WriteReg( &i2cProtocol, MAXIM_REG_MULTILED_MODE_CR_12, 0x03 );
        i2cStatus |= I2C_WriteReg( &i2cProtocol, MAXIM_REG_MULTILED_MODE_CR_34, 0x00 );

        i2cStatus |= I2C_WriteReg( &i2cProtocol, MAXIM_REG_FIFO_CFG , 0x06 );
        i2cStatus |= I2C_WriteReg( &i2cProtocol, MAXIM_REG_SPO2_CFG , 0x43 );

        i2cStatus |= I2C_WriteReg( &i2cProtocol, MAXIM_REG_PROXY_INT_THR , 0x14 );

        /** clear FIFO pointers */
        i2cStatus |= I2C_WriteReg( &i2cProtocol, MAXIM_REG_FIFO_WR_PTR , 0 );
        i2cStatus |= I2C_WriteReg( &i2cProtocol, MAXIM_REG_FIFO_RD_PTR , 0 );
        i2cStatus |= I2C_WriteReg( &i2cProtocol, MAXIM_REG_FIFO_OV_PTR , 0 );

        // read only green LED valus
        maxim_bytesPerSample = MAXIM_BYTES_PER_ADC_VALUE * 1;
        maxim_bitMask        = 0x00003FFFF;

        return STATUS_MAXIM_SUCCESS;
    }
}

/**
 * shutdown the sensor
 */
maxim_status_t MAXIM_Deinit()
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
    // dealocate memory
    if ( NULL != ledBuffers )
    {
      free( ledBuffers );
    }

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
maxim_status_t MAXIM_Reset()
{
  uint8_t
    timeoutCnt = 0;

  statusI2C_t
    i2cStatus = 0;

  uint8_t
    foo = 0;

  // reset the module
  I2C_WriteReg( &(self.protocol), MAXIM_REG_MODE_CFG , MAXIM_MODE_CFGBIT_RST );

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
      if ( 0 == ( foo & MAXIM_MODE_CFGBIT_RST ) )
      {
        return STATUS_MAXIM_SUCCESS;
      }

      else
      {
        // wait a bit
        OSA_TimeDelay(10);
        timeoutCnt++;

        // exit if the module is stuck
        if ( timeoutCnt > 5 )
        {
          catch(11);
          return STATUS_MAXIM_TIMEOUT;
        }
      }
    }
  }
}

/**
 * read raw sensor data
 * @param  dataBuff  buffer to place the samples in
 * @param  sampleNum number of read samples
 * @return           [description]
 */
maxim_status_t MAXIM_ReadRawData(
                                    uint8_t* dataBuff,
                                    uint8_t* sampleNum
                                )
{
    statusI2C_t
        i2cStatus = STATUS_I2C_SUCCESS;

    uint8_t
        fifoWrPtr = 0,
        fifoRdPtr = 0,
        fifoOvPtr = 0;

    genericI2cHandle_t
        i2cProtocol = self.protocol;

    // temporary buffer to read samples from the FIFO buffer
    uint8_t
        tmpBuf[ MAXIM_FIFO_DEPTH * MAXIM_BYTES_PER_ADC_VALUE ];
    // uint8_t*
    //     tmpBuf = (uint8_t*)malloc( MAXIM_FIFO_DEPTH * maxim_bytesPerSample );

    uint8_t
        numAvailSam;

    if ( NULL == tmpBuf )
    {
        catch( CATCH_HEALTH);
    }


    // read FIFO pointers
    i2cStatus |= I2C_ReadReg( &i2cProtocol, MAXIM_REG_FIFO_WR_PTR , &fifoWrPtr );
    i2cStatus |= I2C_ReadReg( &i2cProtocol, MAXIM_REG_FIFO_RD_PTR , &fifoRdPtr );
    i2cStatus |= I2C_ReadReg( &i2cProtocol, MAXIM_REG_FIFO_OV_PTR , &fifoOvPtr );

    if ( STATUS_I2C_SUCCESS != i2cStatus )
    {
        catch( CATCH_HEALTH );
        return STATUS_MAXIM_PROTOCOL_ERROR;
    }

    // overflow happened
    if ( fifoOvPtr > 0 )
    {
        catch( CATCH_HEALTH );

        /** dummy read */

        uint8_t
            cmd[1] = { MAXIM_REG_FIFO_DATA };
        I2C_DRV_MasterReceiveDataBlocking   (
                                                i2cProtocol.instance,
                                                &(i2cProtocol.device),

                                                (const uint8_t*)cmd,
                                                ArraySize(cmd),

                                                (uint8_t*)tmpBuf,
												MAXIM_FIFO_DEPTH * MAXIM_BYTES_PER_ADC_VALUE,
                                                // numAvailSam * maxim_bytesPerSample,

                                                100
                                            );

        /** reset the pointers */
//        i2cStatus |= I2C_WriteReg( &i2cProtocol, MAXIM_REG_FIFO_WR_PTR , 0 );
//        i2cStatus |= I2C_WriteReg( &i2cProtocol, MAXIM_REG_FIFO_RD_PTR , 0 );
//        i2cStatus |= I2C_WriteReg( &i2cProtocol, MAXIM_REG_FIFO_OV_PTR , 0 );

        if ( STATUS_I2C_SUCCESS != i2cStatus )
        {
            catch( CATCH_HEALTH );
            return STATUS_MAXIM_PROTOCOL_ERROR;
        }

        numAvailSam = 0xFF;
    }

    else
    {
        if ( fifoWrPtr > fifoRdPtr )
        {
            /**
            * NUM_AVAILABLE_SAMPLES = FIFO_WR_PTR – FIFO_RD_PTR
            * NUM_SAMPLES_TO_READ   = < less than or equal to NUM_AVAILABLE_SAMPLES >
            */
            numAvailSam = fifoWrPtr - fifoRdPtr;
        }

        // note: pointer wrap around should be taken into account
        else if ( fifoWrPtr < fifoRdPtr )
        {
            numAvailSam = fifoWrPtr + MAXIM_FIFO_DEPTH - fifoRdPtr;
        }

        // no new samples available
        else
        {
            numAvailSam = 0;
        }

        if ( numAvailSam > 0 )
        {
            uint8_t
                cmd[1] = { MAXIM_REG_FIFO_DATA };

            /**
             * read all the available samples,
             * FIFO RD pointer is implicitly incremented after each successful sample read
             */

            I2C_DRV_MasterReceiveDataBlocking   (
                                                    i2cProtocol.instance,
                                                    &(i2cProtocol.device),

                                                    (const uint8_t*)cmd,
                                                    ArraySize(cmd),

                                                    (uint8_t*)tmpBuf,
                                                    numAvailSam * MAXIM_BYTES_PER_ADC_VALUE,
                                                    // numAvailSam * maxim_bytesPerSample,

                                                    100
                                                );

            if ( NULL != dataBuff )
            {
                memcpy  (
                            (void*)dataBuff,
                            (const void*)tmpBuf,
                            numAvailSam * MAXIM_BYTES_PER_ADC_VALUE
                            // numAvailSam * maxim_bytesPerSample
                        );
            }
        }
    }

    /** save data */

    if ( NULL != sampleNum )
    {
        *sampleNum = numAvailSam;
    }

    if ( NULL != maxim_callback )
    {
        maxim_callback( (void*)tmpBuf, (uint8_t)numAvailSam, NULL );
    }

    // free(tmpBuf);

    return STATUS_MAXIM_SUCCESS;
}

/**
 * [MAXIM_Enable description]
 * @return [description]
 */
maxim_status_t MAXIM_Enable()
{
//	if ( false == isMaximEnabled )
//	{
		genericI2cHandle_t
			i2cProtocol = self.protocol;

		statusI2C_t
			i2cStatus = STATUS_I2C_SUCCESS;

		i2cStatus |= I2C_WriteReg( &i2cProtocol, MAXIM_REG_INTERRUPT_ENABLE_1 , 0x10 );
		i2cStatus |= I2C_WriteReg( &i2cProtocol, MAXIM_REG_MODE_CFG , 0x07 );

		if ( STATUS_I2C_SUCCESS != i2cStatus )
		{
			// catch( CATCH_HEALTH );
			return STATUS_MAXIM_PROTOCOL_ERROR;
		}

		else
		{
			isMaximEnabled = true;
			return STATUS_MAXIM_SUCCESS;
		}
//	}

	return STATUS_MAXIM_SUCCESS;
}


/**
 * [MAXIM_Disable description]
 * @return [description]
 */
maxim_status_t MAXIM_Disable()
{
	if ( true == isMaximEnabled )
	{
//		genericI2cHandle_t
//			i2cProtocol = self.protocol;
//
//		statusI2C_t
//			i2cStatus = I2C_WriteReg( &i2cProtocol, MAXIM_REG_MODE_CFG , 0x00 );
//
//		if ( STATUS_I2C_SUCCESS != i2cStatus )
//		{
//			// catch( CATCH_HEALTH );
//			return STATUS_MAXIM_PROTOCOL_ERROR;
//		}
//
//		else
//		{
			isMaximEnabled = false;
//			return STATUS_MAXIM_SUCCESS;
//		}
	}

	return STATUS_MAXIM_SUCCESS;
}

/**
 * [MAXIM_InstallCallback description]
 * @param callback [description]
 */
void MAXIM_InstallCallback( maxim_callback_t callback )
{
    maxim_callback = callback;
}

/**
 * testing HR sensor
 */
void MAXIM_Test()
{
	MAXIM_Init( &maximModule,  &maximSettings );
	MAXIM_Enable();
	OSA_TimeDelay(500);
	MAXIM_Disable();
	MAXIM_Reset();

}

/**
 * formatting functions
 */

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
{}

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
{}

/**
 * Write the specified registers via I2C
 * Project HEXIWEAR, 2015
 */

#include "generic_i2c_driver.h"
#include "generic_i2c_types.h"
#include "generic_i2c_info.h"

#include "FS_I2C.h"
#include "NFS_I2C.h"
#include "pin_mux.h"

#include "error.h"

// initialized I2C modules
static bool
	initModules[ I2C_NUM_MAX ] = { false, false, false };

static mutex_t
	I2C_mutex = NULL;

/** private API */
static statusI2C_t I2C_Reset( genericI2cHandle_t* self );

static void I2C_HandleAlternate_IN(genericI2cHandle_t* self)
{
	if((self->alternate == true) && (self->instance == I2C0_IDX))
	{
		deinit_i2c_pins(I2C0_IDX);
		PORT_HAL_SetMuxMode( PORTD, 8UL, kPortMuxAlt2 );
		PORT_HAL_SetMuxMode( PORTD, 9UL, kPortMuxAlt2 );
	}
}

static void I2C_HandleAlternate_OUT(genericI2cHandle_t* self)
{
	if((self->alternate == true) && (self->instance == I2C0_IDX))
	{
		PORT_HAL_SetMuxMode( PORTD, 8UL, kPortPinDisabled );
	    PORT_HAL_SetMuxMode( PORTD, 9UL, kPortPinDisabled );
		init_i2c_pins(I2C0_IDX);
	}
}

/**
 * initialize I2C
 * @param  self          [description]
 * @param  devAddr       [description]
 * @param  baudrate_kbps [description]
 * @return               [description]
 */
statusI2C_t I2C_Init(
                      	  genericI2cHandle_t* self,
						  uint8_t devAddr,
						  uint16_t baudrate_kbps
                    )
{
  if(I2C_mutex == NULL) OSA_MutexCreate( &I2C_mutex );

  OSA_MutexLock( &I2C_mutex, OSA_WAIT_FOREVER );

  if ( true == initModules[ self->instance ] )
  {
    // set timeout again and baud-rate values
    self->timeout = I2C_TIMEOUT;
  }

  // given handle must contain all the necessary info
  else
  {
    initModules[ self->instance ] = true;

    switch( self->instance )
    {
      case FSL_FS_I2C:  {
                          NVIC_SetPriority( FSL_I2C_IRQn, FSL_I2C_IRQ_PRIO );
                          break;
                        }

      case FSL_NFS_I2C: {
                          NVIC_SetPriority( NFSL_I2C_IRQn, NFSL_I2C_IRQ_PRIO );
                          break;
                        }

      default: {}
    }

    I2C_DRV_MasterInit( self->instance, &(self->state) );
  }

  self->device.address       = devAddr;
  self->device.baudRate_kbps = baudrate_kbps;
  I2C_DRV_MasterSetBaudRate ( self->instance, &(self->device) );

  OSA_MutexUnlock( &I2C_mutex );

  return STATUS_I2C_SUCCESS;
}

/**
 * [I2C_deinit description]
 * @param  self [description]
 * @return      [description]
 */
statusI2C_t I2C_Deinit(
                        genericI2cHandle_t* self
                      )
{
  if ( false == initModules[ self->instance ] )
  {
    return STATUS_I2C_DEINIT_ERROR;
  }

  else
  {
//    i2c_status_t
//      status = I2C_DRV_MasterDeinit(self->instance);
//
//    if ( kStatus_I2C_Success != status )
//    {
//      return STATUS_I2C_ERROR;
//    }
//
//    else
    {
//	  initModules[ self->instance ] = false;
      return STATUS_I2C_SUCCESS;
    }
  }
}

/**
 * Write to the specified register
 * The writing process is done via I2C
 *
 * @param  self [description]
 * @param  reg  [description]
 * @param  val  [description]
 *
 * @return      [description]
 */
statusI2C_t I2C_WriteReg(
                          genericI2cHandle_t* self,
                                      uint8_t reg,
                                      uint8_t val
                        )
{
	OSA_MutexLock( &I2C_mutex, OSA_WAIT_FOREVER );

  uint8_t
    // the register address
    cmd[1]  = {
                reg
              },
    // data
    buff[1] = {
                val
              };

    statusI2C_t
      i2cstatus = STATUS_I2C_SUCCESS;

    {
      i2c_status_t
        status = I2C_DRV_MasterSendDataBlocking (
                                                  self->instance,
                                                  &(self->device),

                                                  cmd,
                                                  1,

                                                  buff,
                                                  1,

                                                  self->timeout
                                                );
      if ( kStatus_I2C_Success != status )
      {
        catch( CATCH_I2C );
        i2cstatus = STATUS_I2C_ERROR;
      }
      else
      {
        i2cstatus = STATUS_I2C_SUCCESS;
      }
    }

	OSA_MutexUnlock( &I2C_mutex );

    return i2cstatus;
}

/**
 * Read the specified register value
 * The reading process is done via I2C
 *
 * @param  self         [description]
 * @param  regAddr      [description]
 * @param  valToReceive [description]
 *
 * @return              [description]
 */
statusI2C_t I2C_ReadReg (
                          genericI2cHandle_t* self,
                                      uint8_t regAddr,
                                     uint8_t* valToReceive
                        )
{
	OSA_MutexLock( &I2C_mutex, OSA_WAIT_FOREVER );

  uint8_t
    cmd[1] =  {
                regAddr
              },
    buff[1];

    statusI2C_t
      i2cstatus = STATUS_I2C_SUCCESS;

    *valToReceive = 0xAE;

    i2c_status_t
      status = I2C_DRV_MasterReceiveDataBlocking(
                                                  self->instance,
                                                  &(self->device),

                                                  cmd,
                                                  1,

                                                  buff,
                                                  1,

                                                  self->timeout
                                                );
    if ( kStatus_I2C_Success != status )
    {
      catch( CATCH_I2C );
      i2cstatus = STATUS_I2C_ERROR;
    }
    else
    {
      *valToReceive = buff[0];
      i2cstatus = STATUS_I2C_SUCCESS;
    }

    OSA_MutexUnlock( &I2C_mutex );

    return i2cstatus;
}

/**
 * modify the specified register value
 * the process is done via I2C
 *
 * @param  self    [description]
 * @param  reg     [description]
 * @param  clrMask [description]
 * @param  setMask [description]
 *
 * @return         [description]
 */
statusI2C_t I2C_ModifyReg (
                            genericI2cHandle_t* self,
                                        uint8_t reg,
                                        uint8_t clrMask,
                                        uint8_t setMask
                          )
{
  uint8_t
    regVal;

  i2c_status_t
    status = I2C_ReadReg(self, reg, &regVal);

  if ( kStatus_I2C_Success != status )
  {
    return STATUS_I2C_ERROR;
  }
  else
  {

    regVal = ( 0 != clrMask )? regVal & ~clrMask : regVal;
    regVal = ( 0 != setMask )? regVal |  setMask : regVal;

    return I2C_WriteReg(self, reg, regVal);
  }
}

/**
 * bit bang I2C lines untill SDA line becomes free,
 * and then reinitialize given I2C module
 * @param  self [description]
 * @return      [description]
 */
static statusI2C_t I2C_Reset( genericI2cHandle_t* self )
{
    /** shut down the I2C module */
    I2C_DRV_MasterDeinit( self->instance );

    uint32_t
		tmtCnt = ( 2 * I2C_TIMEOUT )/10;

    /** configure I2C pins as GPIO */

    uint32_t
        sclPin,
        sdaPin;

    GPIO_Type*
        gpioBase;
    PORT_Type*
        portBase;

    /** select appropriate I2C pins */
    switch ( self->instance )
    {
        // I2C0 -- SCL: PTB0 & SDA: PTB1
        case FSL_NFS_I2C:
        {
            portBase = g_portBase[1];
            gpioBase = g_gpioBase[1];
            sclPin   = 0UL;
            sdaPin   = 1UL;
            break;
        }

        // I2C1 -- SCL: PTC10 & SDA: PTC11
        case FSL_FS_I2C:
        {
            portBase = g_portBase[2];
            gpioBase = g_gpioBase[2];
            sclPin   = 10UL;
            sdaPin   = 11UL;
            break;
        }

        default:
        {
            return STATUS_I2C_INIT_ERROR;
            break;
        }
    }

    /** set as gpio */
    PORT_HAL_SetMuxMode( portBase, sclPin, kPortMuxAsGpio);
    PORT_HAL_SetMuxMode( portBase, sdaPin, kPortMuxAsGpio);

    /** set as digital output */
    GPIO_HAL_SetPinDir( gpioBase, sclPin, kGpioDigitalOutput);
    GPIO_HAL_SetPinDir( gpioBase, sdaPin, kGpioDigitalOutput);

    /** set as open-drain */
    PORT_HAL_SetOpenDrainCmd( portBase, sclPin, true );
    PORT_HAL_SetOpenDrainCmd( portBase, sdaPin, true );

    /** bit bang SCL clock until SDA line becomes free ( i.e. logic high ) */

    while ( 0 == GPIO_HAL_ReadPinInput( gpioBase, sdaPin ) )
    {
        /** toggle SCL line */
        GPIO_HAL_TogglePinOutput( gpioBase, sclPin );
        OSA_TimeDelay( 10 );
        tmtCnt--;

        if ( 0 == tmtCnt )
        {
        	return STATUS_I2C_TIMEOUT_ERROR;
        }
    }

    /** reinit the I2C module */
    I2C_DRV_MasterInit( self->instance, &(self->state) );

    return STATUS_I2C_SUCCESS;
}

/**
 * if needed, recover I2C by resetting the state on the bus
 * @param  self i2c handle
 * @return      status flag
 */
statusI2C_t I2C_Recover( genericI2cHandle_t* self )
{
    i2c_master_state_t*
        masterState = (i2c_master_state_t*)g_i2cStatePtr[ self->instance ];

    i2c_status_t
        i2cStatus = kStatus_I2C_Success;

    uint32_t
		txBytesRemaining = 0,
		rxBytesRemaining = 0;

    i2cStatus |= I2C_DRV_MasterGetSendStatus   ( self->instance, &txBytesRemaining );
    i2cStatus |= I2C_DRV_MasterGetReceiveStatus( self->instance, &rxBytesRemaining );

    if ( kStatus_I2C_Success == i2cStatus )
    {
        if  (
                    ( false == ( masterState->i2cIdle ) )
                ||      ( 0 != rxBytesRemaining )
                ||      ( 0 != txBytesRemaining )
            )
        {
            /** reset I2C bus */
            statusI2C_t
                resetStatus = I2C_Reset( self );

            if ( STATUS_I2C_SUCCESS != resetStatus )
            {
				catch( CATCH_I2C );
            }

            return resetStatus;
        }
        else
        {
            return STATUS_I2C_SUCCESS;
        }
    }
    else
    {
    	catch( CATCH_I2C );
    	return STATUS_I2C_ERROR;
    }
}

statusI2C_t I2C_Send(genericI2cHandle_t* self, uint8_t *pCmd,  uint16_t CmdLen, uint8_t *pSnd,  uint16_t SndLen)
{
	statusI2C_t i2cstatus = STATUS_I2C_SUCCESS;
	i2c_status_t status;

	OSA_MutexLock( &I2C_mutex, OSA_WAIT_FOREVER );

	I2C_HandleAlternate_IN(self);

	status = I2C_DRV_MasterSendDataBlocking(self->instance,
			&(self->device),
			pCmd,
			CmdLen,
			pSnd,
			SndLen,
			self->timeout);

	if ( kStatus_I2C_Success != status )
	{
		catch( CATCH_I2C );
		i2cstatus = STATUS_I2C_ERROR;
	}
	else
	{
		i2cstatus = STATUS_I2C_SUCCESS;
	}

	I2C_HandleAlternate_OUT(self);

	OSA_MutexUnlock( &I2C_mutex );

    return i2cstatus;
}

statusI2C_t I2C_Receive (genericI2cHandle_t* self, uint8_t *pRcv, uint16_t RcvLen)
{
    statusI2C_t i2cstatus = STATUS_I2C_SUCCESS;
    i2c_status_t status;

    OSA_MutexLock( &I2C_mutex, OSA_WAIT_FOREVER );

	I2C_HandleAlternate_IN(self);

	status = I2C_DRV_MasterReceiveDataBlocking(self->instance,
                                               &(self->device),
                                               NULL,
                                               0,
                                               pRcv,
                                               RcvLen,
                                               self->timeout);
    if ( kStatus_I2C_Success != status )
    {
      catch( CATCH_I2C );
      i2cstatus = STATUS_I2C_ERROR;
    }
    else
    {
      i2cstatus = STATUS_I2C_SUCCESS;
    }

	I2C_HandleAlternate_OUT(self);

	OSA_MutexUnlock( &I2C_mutex );

    return i2cstatus;
}

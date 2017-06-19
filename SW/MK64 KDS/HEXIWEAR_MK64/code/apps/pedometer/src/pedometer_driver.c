/**
 * \file pedometer_driver.c
 * \version 1.00
 * \brief this file contains pedometer app functionality
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * Neither the name of NXP, nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * visit: http://www.mikroe.com and http://www.nxp.com
 *
 * get support at: http://www.mikroe.com/forum and https://community.nxp.com
 *
 * Project HEXIWEAR, 2015
 */

#include "pedometer_driver.h"

#include "keynetik_driver.h"
#include "error.h"
#include "sensor_driver.h"
#include "gui_sensorTag.h"

#include "watch.h"
#include "fitness.h"

#if defined( HEXIWEAR_DEBUG )
#include "GPIO.h"
#endif

/** private defines */

#define SQUARED(x) ( ( x ) * ( x ) )
#define ONEG       ( 4096 )
#define FREQHZ     ( 50 )

MSG_QUEUE_DECLARE( pedometer_queue, PEDOMETER_QUEUE_SIZE, sizeof(hostInterface_packet_t) );

/** private variable definitions */

static const pedometer_t
    pedometer_default =
    {
        .status =
        {
            .version = 2,
        },

      .config =
      {
          .sleepcount_threshold = 1,

          .bits =
          {
              .config = 1
          },

          .keynetik =
          {
              .height      = 175,
              .weight      = 80,
              .filtersteps = 4,

              .bits =
              {
                  .filtertime = 3,
              },

              .speedperiod   = 5,
              .stepthreshold = 130,
          },

          .stepcoalesce = 1,
      }
    };

static msg_queue_handler_t
  pedometer_queueHnd;

static task_handler_t
  pedometer_taskHandler;

static hostInterface_packet_t
  pedometer_dataPacket;

static pedometer_t
  pedometerHandle = {0};

static bool
	isSensorTagTurnedOff = false;

/** private functions' declarations */

static uint16_t uint32_to_uint16( uint32_t x );
static void status_update( pedometer_t* pedometerHandle, uint32_t events, bool suspend );
static void config_update( pedometer_t* pedometerHandle );
static bool suspend_compute( pedometer_t* pedometerHandle, int16_t x, int16_t y, int16_t z );
static pedo_process_status_t pedometer_QueueMsgGet ( uint32_t timeout );
static pedo_process_status_t pedometer_Process ( int16_t x, int16_t y, int16_t z );
static void pedometer_Task( task_param_t param );
static pedo_process_status_t pedometer_QueueMsgGet( uint32_t timeout );
static pedo_process_status_t pedometer_SendToKW40( uint32_t valToSend );

/** public API */

/**
 * reset the handle values to their default values
 */
pedo_process_status_t pedometer_Reset()
{
  memcpy( &pedometerHandle, &pedometer_default, sizeof(pedometer_t) );
  return 0;
}

/**
 * debounce the counter
 */
bool debounce_count (
                                   bool dbcntm,
                                   bool condition,
                      debounce_count_t* count,
                       debounce_count_t threshold
                    )
{
    if ( 0 != condition )
    {
        // increment count up to, but not above the threshold
        *count = (*count+1) < threshold ? *count+1 : threshold;
    }

    else
    {
      if ( 0 != dbcntm )
      {
        *count = 0;
      }

      else
      {
        // decrement count down to, but not below zero
        *count = (*count-1) > 0 ? *count-1 : 0;
      }
    }

    return (bool)( *count >= threshold );
}

/**
 * put acc data into the queue for pedometer app
 * @param  packet data to put
 * @return        status flag
 */
pedo_process_status_t pedometer_QueueMsgPut ( hostInterface_packet_t* packet )
{
  BaseType_t
    status = xQueueSendToBack( pedometer_queueHnd, (hostInterface_packet_t*)packet, OSA_WAIT_FOREVER );

    if ( pdPASS == status )
    {
      return PEDO_PROCESS_STATUS_SUCCESS;
    }

    else
    {
      catch( CATCH_QUEUE );
      return PEDO_PROCESS_STATUS_ERROR;
    }
}

/**
 * initialize pedometer objects,
 * reset relevant variables
 * and register to acc sensor
 */
void pedometer_Init()
{
	// create pedometer data packet queue
	pedometer_queueHnd = OSA_MsgQCreate (
										    pedometer_queue,
										    PEDOMETER_QUEUE_SIZE,
										    sizeof(hostInterface_packet_t) / sizeof(uint32_t)
										);
#if defined( HEXIWEAR_DEBUG )
	vQueueAddToRegistry( pedometer_queueHnd, (char*)"App Pedometer Queue" );
#endif

	// turn sensor tag off, if turned on
	if ( true == gui_sensorTag_IsActive() )
	{
		isSensorTagTurnedOff = true;
		gui_sensorTag_TurnOFF();
	}

	GuiDriver_RegisterMinPollDelay( 20 );
	sensor_RegisterPacketDelay( PACKET_ACC, 20 );

	pedometer_Reset();
}

void pedometer_CreateTask()
{
  osa_status_t
    taskStatus = OSA_TaskCreate (
                                  pedometer_Task,
                                  (uint8_t*) "pedometer process",
                                  PEDOMETER_STACK_SIZE,
                                  NULL,
                                  PEDOMETER_PRIO,
                                  (task_param_t)0,
                                  false,
                                  &pedometer_taskHandler
                                );
  if ( kStatus_OSA_Success != taskStatus )
  {
    catch( CATCH_INIT );
  }
  pedometer_Pause();
}

/**
 * deinitialize pedometer objects,
 * free used memory
 * and unregister from acc sensor
 */
void pedometer_Deinit()
{
  OSA_TaskDestroy( pedometer_taskHandler );

  // destroy pedometer data packet queue
  OSA_MsgQDestroy( pedometer_queueHnd );

  // unsubscribe from the accelerometer
  sensor_SetPacketTargets( PACKET_ACC, sensor_GetPacketTargets( PACKET_ACC ) & ~PACKET_PUSH_APP_PEDOMETER, true );

  // turn sensor tag back on upon pedometer app exit
  if ( true == isSensorTagTurnedOff )
  {
    isSensorTagTurnedOff = false;
    gui_sensorTag_TurnON();
  }

  OLED_DestroyDynamicArea();

  pedometer_SendToKW40( 0xFFFFFFFF );
}

/**
 * resume the pedometer task
 */
void pedometer_Resume()
{
	sensor_SetPacketTargets( PACKET_ACC, sensor_GetPacketTargets( PACKET_ACC ) | PACKET_PUSH_APP_PEDOMETER, true );
	vTaskResume( pedometer_taskHandler );
}

/**
 * pause the pedometer task
 */
void pedometer_Pause()
{
  vTaskSuspend( pedometer_taskHandler );
  sensor_SetPacketTargets( PACKET_ACC, sensor_GetPacketTargets( PACKET_ACC ) & ~PACKET_PUSH_APP_PEDOMETER, true );
}

/**
 * get steps
 */
uint16_t pedometer_GetStepCounter()
{
  return pedometerHandle.status.stepcount;
}

/**
 * get calories
 */
uint16_t pedometer_GetCalories()
{
  return pedometerHandle.status.calories;
}

static pedo_process_status_t pedometer_QueueMsgGet( uint32_t timeout )
{
  osa_status_t
    status = OSA_MsgQGet( pedometer_queueHnd, (hostInterface_packet_t*)&pedometer_dataPacket, timeout );

  if ( kStatus_OSA_Error == status )
  {
    catch( CATCH_QUEUE );
    return PEDO_PROCESS_STATUS_ERROR;
  }
  else
  {
    return PEDO_PROCESS_STATUS_SUCCESS;
  }
}

/**
 * process the acceleration data and feed into pedometer algorithm
 * @param x acceleration x-axis value
 * @param y acceleration y-axis value
 * @param z acceleration z-axis value
 */
static pedo_process_status_t pedometer_Process(
                                                int16_t x,
                                                int16_t y,
                                                int16_t z
                                              )
{
  uint32_t
    events = 0;

  config_update( &pedometerHandle );

  bool
    suspend = suspend_compute( &pedometerHandle, x, y, z );

  if ( 0 == suspend )
  {
    events = KeynetikHandleIncomingEvent( x, y, z );
  }

	uint16_t
		/** steps */
		oldStepsVal = pedometerHandle.status.stepcount,

		/** calories */
		oldCalVal = pedometerHandle.status.calories;

  uint32_t
		/** composite of two values (steps+calories) */
		valToSend = 0;

	/** update to get new values */
	status_update( &pedometerHandle, events, suspend );

  	/** send the packet */
	valToSend = ( oldStepsVal != pedometerHandle.status.stepcount ) ?
					valToSend | (uint32_t)pedometerHandle.status.stepcount :
					valToSend;

	valToSend = ( oldCalVal != pedometerHandle.status.calories ) ?
					valToSend | ( (uint32_t)pedometerHandle.status.calories << 16 ) :
					valToSend;

	/** send to OLED and KW40 */
    if ( 0 != valToSend )
  {
    	gui_pedometer_QueueMsgPut( &valToSend  );
    	pedometer_SendToKW40( valToSend );
  }

  return 0;
}

/**
 * reinitialize the keynetik library, if necessary
 */
static void config_update ( pedometer_t* pedometerHandle )
{
  if ( 0 != pedometerHandle->config.bits.config )
  {
    KeynetikInitialize( ONEG, FREQHZ, &(pedometerHandle->config.keynetik) );
    pedometerHandle->private.stepchg_stepcount = 0;
    pedometerHandle->config.bits.config        = 0;
  }
}

/**
 * determine autonomous suspend state
 */
static bool suspend_compute (
                              pedometer_t* pedometerHandle,
                                   int16_t xVal,
                                   int16_t yVal,
                                   int16_t zVal
                            )
{
  uint32_t
    magnitude = SQUARED( xVal ) + SQUARED( yVal ) + SQUARED( zVal );

  bool
    stationary =      ( magnitude > SQUARED( pedometerHandle->config.sleepminimum ) )
                  &&  ( magnitude < SQUARED( pedometerHandle->config.sleepmaximum ) );

  bool
    suspend = debounce_count(
                              pedometerHandle->config.bits.sleep_dbcntm,
                              stationary,
                              &pedometerHandle->status.sleepcount,
                              pedometerHandle->config.sleepcount_threshold
                            );
  return suspend;
}

/**
 * update status variables
 */
static void status_update (
                            pedometer_t* pedometerHandle,
                            uint32_t events,
                            bool suspend
                          )
{
  bool
    activity_stable = debounce_count(
                                      pedometerHandle->config.bits.activity_dbcntm,
                                      !(events & KEYNETIK_ACTIVITYCHANGED),
                                      &pedometerHandle->private.activitycount,
                                      pedometerHandle->config.activitycount_threshold
                                    );

  activitylevel_t
    activity = activity_stable ? keynetikActivityLevel : pedometerHandle->status.status.bits.activity;

  uint16_t
    stepcount = uint32_to_uint16( keynetikStepCount );

  uint8_t
    newstatus = ( activity << PEDOMETER_STATUS_ACTIVITY_BITNUM ) & PEDOMETER_STATUS_ACTIVITY_MASK;

  if ( 0 != ( ( newstatus ^ pedometerHandle->status.status.byte ) & PEDOMETER_STATUS_ACTIVITY_MASK ) )
  {
    newstatus |= PEDOMETER_STATUS_ACTCHG_MASK;
  }

  if  (
            ( 0 != pedometerHandle->config.stepcoalesce )
        &&  ( ( stepcount - pedometerHandle->private.stepchg_stepcount ) >= pedometerHandle->config.stepcoalesce )
      )
  {
    pedometerHandle->private.stepchg_stepcount = stepcount;
    newstatus |= PEDOMETER_STATUS_STEPCHG_MASK;
  }

  if ( 0 != suspend )
  {
    newstatus |= PEDOMETER_STATUS_SUSPEND_MASK;
  }

  if  ( 0 != ( ( newstatus ^ pedometerHandle->status.status.byte ) & PEDOMETER_STATUS_SUSPEND_MASK ) )
  {
    newstatus |= PEDOMETER_STATUS_SUSPCHG_MASK;
  }

  if ( 0 != ( newstatus & PEDOMETER_STATUS_CHG_MASK ) )
  {
    newstatus |= PEDOMETER_STATUS_MRGFLG_MASK;
  }

  OSA_EnterCritical( kCriticalDisableInt );

  pedometerHandle->status.stepcount   = uint32_to_uint16(keynetikStepCount);
  pedometerHandle->status.distance    = uint32_to_uint16(keynetikDistance);
  pedometerHandle->status.speed       = keynetikSpeed;
  pedometerHandle->status.calories    = uint32_to_uint16(keynetikCalories);
  pedometerHandle->status.status.byte = newstatus;

  OSA_ExitCritical( kCriticalDisableInt );
}

/**
 * cast uint32_t to uint16_t with saturate
 */
static uint16_t uint32_to_uint16( uint32_t x )
{
  return ( x > 0x0000FFFF ) ? 0xFFFF : (uint16_t)x;
}

static void pedometer_Task( task_param_t param )
{
  while (1)
  {
    pedometer_QueueMsgGet( OSA_WAIT_FOREVER );
    uint8_t*
      accData = pedometer_dataPacket.data;

    int16_t
      xVal,
      yVal,
      zVal;

    acc_fmtMe2Def( (const void*)(accData + 0), (void*)&xVal );
    acc_fmtMe2Def( (const void*)(accData + 2), (void*)&yVal );
    acc_fmtMe2Def( (const void*)(accData + 4), (void*)&zVal );

    pedometer_Process( xVal, yVal, zVal );
  }
}

/**
 * send steps packet to KW40
 */
static pedo_process_status_t pedometer_SendToKW40( uint32_t valToSend )
{
	uint16_t
		stepVal = (uint16_t)  ( valToSend & 0x0000FFFF ),
		calVal  = (uint16_t)( ( valToSend & 0xFFFF0000 ) >> 16 );

    hostInterface_packet_t
        packetToSend;

    linkState_t
  	  currentState = watch_CurrentLinkStateGet();

    if ( linkState_connected == currentState )
    {
		osa_status_t
			txStatus = kStatus_OSA_Success;

      if ( 0 != stepVal )
      {
        if ( 0xFFFF == stepVal )
        {
          stepVal = 0;
        }

      	packetToSend.type   = packetType_steps,
        packetToSend.length = sizeof(stepVal);
      	memcpy( (void*)&(packetToSend.data[0]), (void*)&stepVal, sizeof(stepVal) );
      	packetToSend.data[ packetToSend.length ] = gHostInterface_trailerByte;

    		txStatus = HostInterface_TxQueueMsgPut( &packetToSend, true );
    		if ( kStatus_OSA_Success != txStatus )
    		{
    			catch( CATCH_QUEUE );
    			return PEDO_PROCESS_STATUS_ERROR;
    		}
      }

	    if ( 0 != calVal )
	    {
        if ( 0XFFFF == calVal )
        {
          calVal = 0;
        }

	    	packetToSend.type   = packetType_calories,
        packetToSend.length = sizeof(calVal);
	    	memcpy( (void*)&(packetToSend.data[0]), (void*)&calVal, sizeof(calVal) );
	    	packetToSend.data[ packetToSend.length ] = gHostInterface_trailerByte;

    		txStatus = HostInterface_TxQueueMsgPut( &packetToSend, true );
    		if ( kStatus_OSA_Success != txStatus )
    		{
    			catch( CATCH_QUEUE );
    			return PEDO_PROCESS_STATUS_ERROR;
    		}
	    }

		return PEDO_PROCESS_STATUS_SUCCESS;
    }

    else
    {
    	return PEDO_PROCESS_STATUS_ERROR;
    }
}

#include "pedometer_driver.h"
#include "pedometer_private.h"

#include "keynetik_driver.h"
#include "error.h"
#include "sensor_driver.h"
#include "gui_sensorTag.h"

#include "watch.h"
#include "fitness.h"

#if defined( HEXIWEAR_DEBUG )
#include "GPIO.h"
#endif

/******************************************************************************
 * Private Defines
 *****************************************************************************/
#define SQUARED(x) ( ( x ) * ( x ) )
#define ONEG       ( 4096 )
#define FREQHZ     ( 50 )

MSG_QUEUE_DECLARE( pedometer_queue, PEDOMETER_QUEUE_SIZE, sizeof(hostInterface_packet_t) );

/******************************************************************************
 * Private Variable Definitions
 ******************************************************************************/
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

/******************************************************************************
 * Private Functions' Declarations
 ******************************************************************************/

/*
 * cast uint32 to uint16 with saturate
 */
static uint16_t uint32_to_uint16( uint32_t x );

/**
 * update status variables
 * @param pedometerHandle [description]
 * @param events          [description]
 * @param suspend         [description]
 */
static void status_update( pedometer_t* pedometerHandle, uint32_t events, bool suspend );

/**
 * reinitialize the keynetik library, if necessary
 * @param pedometerHandle [description]
 */
static void config_update( pedometer_t* pedometerHandle );

/**
 * determine autonomous suspend state
 * @param  pedometerHandle [description]
 * @param  x               [description]
 * @param  y               [description]
 * @param  z               [description]
 * @return                 [description]
 */
static bool suspend_compute( pedometer_t* pedometerHandle, int16_t x, int16_t y, int16_t z );

/**
 * [pedometer_QueueMsgGet  description]
 * @param  timeout [description]
 * @return         [description]
 */
static pedo_process_status_t pedometer_QueueMsgGet ( uint32_t timeout );

/**
 * [pedometer_Process  description]
 * @param  x [description]
 * @param  y [description]
 * @param  z [description]
 * @return   [description]
 */
static pedo_process_status_t pedometer_Process ( int16_t x, int16_t y, int16_t z );

/**
 * [pedometer_Task description]
 * @param param [description]
 */
static void pedometer_Task( task_param_t param );

/**
 * [pedometer_QueueMsgGet  description]
 * @param  timeout [description]
 * @return         [description]
 */
static pedo_process_status_t pedometer_QueueMsgGet( uint32_t timeout );
static pedo_process_status_t pedometer_SendToKW40( uint32_t valToSend );

/******************************************************************************
 * Public Functions' Definitions
 ******************************************************************************/

/**
 * reset the handle values to their default values
 */
pedo_process_status_t pedometer_Reset()
{
  memcpy( &pedometerHandle, &pedometer_default, sizeof(pedometer_t) );
  return 0;
}

/**
 * debounce counter
 * @param  dbcntm    [description]
 * @param  condition [description]
 * @param  count     [description]
 * @param  threshold [description]
 * @return           [description]
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
 * [fitness_pedometer_QueueMsgPut description]
 * @param  packet [description]
 * @return        [description]
 */
pedo_process_status_t pedometer_QueueMsgPut (
                                              hostInterface_packet_t* packet
                                            )
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

/******************************************************************************
 * Private Functions' Definitions
 ******************************************************************************/

/**
 * reinitialize the keynetik library, if necessary
 * @param pedometerHandle [description]
 */
static void config_update (
                            pedometer_t* pedometerHandle
                          )
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
 * @param  pedometer [description]
 * @param  xVal      [description]
 * @param  yVal      [description]
 * @param  zVal      [description]
 * @return           [description]
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
 * @param pedometer [description]
 * @param events    [description]
 * @param suspend   [description]
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
 * @param  x [description]
 * @return   [description]
 */
static uint16_t uint32_to_uint16(
                                  uint32_t x
                                )
{
  return ( x > 0x0000FFFF ) ? 0xFFFF : (uint16_t)x;
}

/**
 * [pedometer_Task description]
 * @param param [description]
 */
static void pedometer_Task(
                            task_param_t param
                          )
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
 * [pedometer_Init description]
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
 * resume the task
 */
void pedometer_Resume()
{
	sensor_SetPacketTargets( PACKET_ACC, sensor_GetPacketTargets( PACKET_ACC ) | PACKET_PUSH_APP_PEDOMETER, true );
	vTaskResume( pedometer_taskHandler );
}

/**
 * pause the task
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

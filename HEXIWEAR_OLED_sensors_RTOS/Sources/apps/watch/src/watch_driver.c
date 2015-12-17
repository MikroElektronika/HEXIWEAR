
/*! *********************************************************************************
*************************************************************************************
* Include
*************************************************************************************
********************************************************************************** */

#include "apps.h"
#include "watch_objects.h"

/************************************************************************************
*************************************************************************************
* Private type definitions
*************************************************************************************
************************************************************************************/

/*! *********************************************************************************
*************************************************************************************
* Private macros
*************************************************************************************
********************************************************************************** */

/*! @brief Converts milliseconds to ticks*/
#define MSEC_TO_TICK(msec)  (((uint32_t)(msec)+500uL/(uint32_t)configTICK_RATE_HZ) \
                             *(uint32_t)configTICK_RATE_HZ/1000uL)

typedef enum
{
  SCREEN_DIMMED,
  SCREEN_NOT_DIMMED,

} screen_t ;

/*! *********************************************************************************
*************************************************************************************
* Private prototypes
*************************************************************************************
********************************************************************************** */

static void watch_Init(void *param);
static void watch_CreateTasks(void *param);
static void watch_TimeUpdate(task_param_t param);
static void watch_GetPackets(task_param_t param);
static void watch_UpdateBatteryLevel(uint8_t level);

static screen_t
  watch_screenState = SCREEN_NOT_DIMMED;

/*! *********************************************************************************
*************************************************************************************
* Public memory declarations
*************************************************************************************
********************************************************************************** */

const menuItem_t watch_item =
{
	.navigation =
	{
		.enter  = NULL,
		.back   = NULL,
		.up     = NULL,
		.down   = NULL,
		.left   = &sensorTag_item,
		.right  = NULL
	},

	.image = watch_bmp,

	.initFunction       = watch_Init,
	.createTaskFunction = watch_CreateTasks,
};

task_handler_t watch_timeUpdate_handler;
task_handler_t watch_getPackets_handler;

/*! *********************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
********************************************************************************** */

static rtc_datetime_t watch_time =
{
	.year   = 2015,
	.month  = 12,
	.day    = 10,
	.hour   = 18,
	.minute = 24,
	.second = 0
};

static hostInterface_packet_t watch_dataPacket;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * [watch_Init description]
 * @param param [description]
 */

static void watch_Init( void *param )
{
	sensor_pushTarget_t targets;

	apps_InitImage(&watch_imgBattery);
	OLED_AddImage(watch_imgBattery.img);

	RTC_DRV_SetDatetime(0, &watch_time);

	snprintf(watch_labelTime.caption, 6, "%02d:%02d", watch_time.hour, watch_time.minute);
	watch_labelTime.textProperties.background = watch_item.image,
	apps_InitLabel(&watch_labelTime);
	OLED_AddText(watch_labelTime.caption);

	snprintf(watch_labelDate.caption, 9, "%02d/%02d/%02d", watch_time.day, watch_time.month, watch_time.year % 100);
	watch_labelDate.textProperties.background = watch_item.image,
	apps_InitLabel(&watch_labelDate);
	OLED_AddText(watch_labelDate.caption);

	targets = sensor_GetPushTargets( SENSOR_PACKET_BAT );
	sensor_SetPushTargets( SENSOR_PACKET_BAT, targets | SENSOR_PUSH_OLED );

        targets = sensor_GetPushTargets( SENSOR_PACKET_LUX );
        sensor_SetPushTargets( SENSOR_PACKET_LUX, targets | SENSOR_PUSH_OLED );

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * [watch_Callback description]
 * @param param [description]
 */

static void watch_CreateTasks( void *param )
{
	// initialize the watch task
	osa_status_t status;

	status = OSA_TaskCreate (
								watch_TimeUpdate,
							   (uint8_t *) "Time Update",
								WATCH_STACK_SIZE,
								NULL,
								WATCH_PRIO,
								(task_param_t)0,
								false,
								&watch_getPackets_handler
							 );

	if ( kStatus_OSA_Success != status )
	{
		catch( CATCH_INIT );
	}

	// initialize the watch task
	status = OSA_TaskCreate (
								watch_GetPackets,
							   (uint8_t*)"Get Packets",
								WATCH_STACK_SIZE,
								NULL,
								WATCH_PRIO,
								(task_param_t)0,
								false,
								&watch_getPackets_handler
					        );

	if ( kStatus_OSA_Success != status )
	{
		catch( CATCH_INIT );
	}
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 * [watch_App description]
 * @param param [description]
 */

static void watch_TimeUpdate(task_param_t param)
{
	uint16_t day;
	uint16_t minute;
	TickType_t previousTime = 0;

	while (1)
	{
		day = watch_time.day;
		minute = watch_time.minute;
		RTC_DRV_GetDatetime(0, &watch_time);

		if(minute != watch_time.minute)
		{
			snprintf( watch_labelTime.caption, 6, "%02d:%02d", watch_time.hour, watch_time.minute );
			apps_DrawLabel(&watch_labelTime);
		}

		if(day != watch_time.day)
		{
			snprintf(watch_labelDate.caption, 9, "%02d/%02d/%02d", watch_time.day, watch_time.month, watch_time.year % 100);
			apps_DrawLabel(&watch_labelDate);
		}

		vTaskDelayUntil( &previousTime, MSEC_TO_TICK(1000) );
	}
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 * [watch_App description]
 * @param param [description]
 */

static void watch_GetPackets(task_param_t param)
{
	mE_t sensorValue;

	while(1)
	{
		MenuDriver_QueueMsgGet( &watch_dataPacket , OSA_WAIT_FOREVER);

		// Extract the data
		sensorValue = (mE_t)( watch_dataPacket.data[0] | (mE_t)watch_dataPacket.data[1] << 8 );

		switch (watch_dataPacket.type)
		{
			// Battery Service
			case packetType_batteryLevel:
			{
				watch_UpdateBatteryLevel(sensorValue);
				break;
			}

			case packetType_ambiLight:
                        {
                          uint32_t
                            luxVal;

                          TSL_CalculateLux( &(watch_dataPacket.data[0]), (uint32_t*)&luxVal );

                          if  ( luxVal < 60 )
                          {
                            if ( SCREEN_NOT_DIMMED == watch_screenState )
                            {
                              watch_screenState = SCREEN_DIMMED;
                              for ( int i = 0; i < 16; i++ )
                              {
                                OLED_SendCmd( OLED_CMD_CONTRASTMASTER, FIRST_BYTE );
                                OLED_SendCmd( 0xC0 | (0xF-i), OTHER_BYTE );
                                OSA_TimeDelay( 10 );
                              }
                            }
                          }

                          else
                          {
                            if ( SCREEN_DIMMED == watch_screenState )
                            {
                              watch_screenState = SCREEN_NOT_DIMMED;
                              for ( int i = 0; i < 16; i++ )
                              {
                                OLED_SendCmd( OLED_CMD_CONTRASTMASTER, FIRST_BYTE );
                                OLED_SendCmd( 0xC0 | i, OTHER_BYTE );
                                OSA_TimeDelay( 10 );
                              }
                            }
                          }
                        }

			case packetType_temperature:
			{
                          break;
			}

			default:
			{
				;
			}
		}

	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * [watch_UpdateBatteryLevel description]
 * @param level [description]
 */

static void watch_UpdateBatteryLevel(uint8_t level)
{
	const uint8_t *img;

	if(level < 16)
	{
		img = battery_0_bmp;
	}
	else if(level < 33)
	{
		img = battery_1_bmp;
	}
	else if(level < 50)
	{
		img = battery_2_bmp;
	}
	else if(level < 66)
	{
		img = battery_3_bmp;
	}
	else if(level < 83)
	{
		img = battery_4_bmp;
	}
	else
	{
		img = battery_5_bmp;
	}

	if(watch_imgBattery.img != img)
	{
		watch_imgBattery.img = img;
		apps_DrawImage(&watch_imgBattery);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

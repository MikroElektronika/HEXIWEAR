
/*! *********************************************************************************
*************************************************************************************
* Include
*************************************************************************************
********************************************************************************** */

#include "apps.h"
#include "watch_objects.h"
#include "FLASH_driver.h"

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


/*! *********************************************************************************
*************************************************************************************
* Private prototypes
*************************************************************************************
********************************************************************************** */

static void watch_Init(void *param);

static void watch_TimeUpdateTask(task_param_t param);
static void watch_GetPacketsTask(task_param_t param);

static void watch_UpdateBatteryLevel(uint8_t level);

static void watch_CreateTasks(void *param);
static void watch_DestroyTasks(void *param);


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
          .left   = NULL,
          .right  = NULL
  },

  .image = watch_bmp,

  .initFunction        = watch_Init,
  .createTaskFunction  = watch_CreateTasks,
  .destroyTaskFunction = watch_DestroyTasks
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
  .day    = 18,
  .hour   = 10,
  .minute = 58,
  .second = 55
};

static hostInterface_packet_t watch_dataPacket;
static uint8_t celsiusStr[3] = " C";

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * [watch_Init description]
 * @param param [description]
 */

static void watch_Init( void *param )
{
  celsiusStr[0] = 176;

  // Init image which indicate battery level.
  apps_InitImage(&watch_imgBattery);
  OLED_AddImage(watch_imgBattery.img);

  RTC_DRV_GetDatetime(0, &watch_time);

  // Init label containing current time.
  snprintf(watch_labelTime.caption, 6, "%02d:%02d", watch_time.hour, watch_time.minute);
  watch_labelTime.textProperties.background = watch_item.image,
  apps_InitLabel(&watch_labelTime);
  OLED_AddText(watch_labelTime.caption);

  // Init label containing current date.
  snprintf(watch_labelDate.caption, 9, "%02d/%02d/%02d", watch_time.day, watch_time.month, watch_time.year % 100);
  watch_labelDate.textProperties.background = watch_item.image,
  apps_InitLabel(&watch_labelDate);
  OLED_AddText(watch_labelDate.caption);

  // Init label containing current temeperature.
  watch_labelTemp.textProperties.background = watch_item.image,
  apps_InitLabel(&watch_labelTemp);
  OLED_AddText(watch_labelTemp.caption);

  // Register for packets we want to receive.
  apps_Register(SENSOR_PACKET_BAT);
  apps_Register(SENSOR_PACKET_TEMP);
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 * [watch_App description]
 * @param param [description]
 */

static void watch_TimeUpdateTask(task_param_t param)
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

    /**
     * FLASH test
     */

    FLASH_WriteData( 106, (uint8_t*)&watch_time, sizeof( watch_time ) );
    memset( (void*)&watch_time, 0, sizeof( watch_time ) );
    FLASH_ReadData ( 106, (uint8_t*)&watch_time, sizeof( watch_time ) );

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

static void watch_GetPacketsTask(task_param_t param)
{
  mE_t sensorValue;

  while(1)
  {
    MenuDriver_QueueMsgGet(&watch_dataPacket , OSA_WAIT_FOREVER);

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

      case packetType_temperature:
      {
        sensorValue /= 100;
        snprintf(watch_labelTemp.caption, 4, "%d", sensorValue);
        // TODO: Degree ascii code is 176. Check if we want to increase font to 255 chars, so we can display such char.
        strcat(watch_labelTemp.caption, celsiusStr);
        apps_DrawLabel(&watch_labelTemp);
        break;
      }

      default: {}
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

  if( watch_imgBattery.img != img )
  {
    watch_imgBattery.img = img;
    apps_DrawImage(&watch_imgBattery);
  }
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
  osa_status_t status;

  status = OSA_TaskCreate (
                            watch_TimeUpdateTask,
                            (uint8_t *) "Time Update",
                            WATCH_STACK_SIZE,
                            NULL,
                            WATCH_PRIO,
                            (task_param_t)0,
                            false,
                            &watch_timeUpdate_handler
                          );

  if ( kStatus_OSA_Success != status )
  {
    catch( CATCH_INIT );
  }

  // initialize the watch task
  status = OSA_TaskCreate (
                            watch_GetPacketsTask,
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * [watch_Callback description]
 * @param param [description]
 */

static void watch_DestroyTasks( void *param )
{
  osa_status_t status;

  status = OSA_TaskDestroy(watch_timeUpdate_handler);
  status |= OSA_TaskDestroy(watch_getPackets_handler);

  if ( kStatus_OSA_Success != status )
  {
    catch( CATCH_INIT );
  }

  // Register for packets we want to receive.
  apps_Unregister(SENSOR_PACKET_BAT);
  apps_Unregister(SENSOR_PACKET_TEMP);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

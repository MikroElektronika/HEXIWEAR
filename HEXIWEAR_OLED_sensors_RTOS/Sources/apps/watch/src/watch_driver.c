
/*! *********************************************************************************
*************************************************************************************
* Include
*************************************************************************************
********************************************************************************** */

#include "apps.h"

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
static void watch_Callback(void *param);
static void watch_App(task_param_t param);

static void watch_BatteryLevelInit(void);
static void watch_BatteryLevelDraw(uint8_t level);

static void watch_DigitWatchInit(void);
static void watch_DigitWatchDraw(void);

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

	.initFunction     = watch_Init,
	.callbackFunction = watch_Callback,
};

task_handler_t watch_handler;

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

static screen_t
  watch_screenState = SCREEN_NOT_DIMMED;

/////////////////////////////////////////////////////////////////////////////////////
// Battery Image

static apps_image_t watch_imgBattery =
{
	.dynamicArea =
	{
		.xCrd = 71,
		.yCrd = 0,
	},

	.img = battery_0_bmp
};

/////////////////////////////////////////////////////////////////////////////////////
// Digital Watch Label

static uint8_t watch_labelDigitWatch_caption[15] = "hello";
static apps_label_t watch_labelDigitWatch =
{
	.dynamicArea =
	{
		.xCrd = 19,
		.yCrd = 41,
		.width = 60,
		.height = 30
	},
	.textProperties =
	{
		.font = menuFont_Tahoma21x25_Regular,
		.fontColor = MENU_COLOR_WHITE,
		.alignParam = OLED_TEXT_ALIGN_CENTER,
	},
	.caption = watch_labelDigitWatch_caption
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * [watch_Init description]
 * @param param [description]
 */

static void watch_Init( void *param )
{
	watch_BatteryLevelInit();
	watch_DigitWatchInit();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * [watch_Callback description]
 * @param param [description]
 */

static void watch_Callback( void *param )
{
  // initialize the watch task
  osa_status_t status = OSA_TaskCreate (
                                              watch_App,
                                         (uint8_t*)"Watch App",
                                              WATCH_STACK_SIZE,
                                              NULL,
                                              WATCH_PRIO,
                                              (task_param_t)0,
                                              false,
                                              &watch_handler
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

static void watch_App(task_param_t param)
{
  TickType_t
    previousTime = 0;

  RTC_DRV_SetDatetime( 0, &watch_time );
  while (1)
  {
    // RTC
    uint8_t clockBuf[9];

    RTC_DRV_GetDatetime( 0, &watch_time );
    snprintf( watch_labelDigitWatch_caption, 6, "%02d:%02d", watch_time.hour, watch_time.minute );
    watch_DigitWatchDraw();

#if defined(SENSOR_TSL)
    statusTSL_t
      tslStatus = TSL_ReadRawData( TSL_CHANNEL_FULL, &(weatherData.ambiData[0]) );

    if ( STATUS_TSL_SUCCESS == tslStatus )
    {
      uint32_t
        luxVal;

      TSL_CalculateLux( &(weatherData.ambiData[0]), (uint32_t*)&luxVal );

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
    #endif

    vTaskDelayUntil( &previousTime, MSEC_TO_TICK(1000) );
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * [watch_BatteryLevelInit description]
 */

static void watch_BatteryLevelInit(void)
{
  OLED_GetImageDimensions(&watch_imgBattery.dynamicArea.width, &watch_imgBattery.dynamicArea.height, watch_imgBattery.img);
  OLED_SetDynamicArea(&watch_imgBattery.dynamicArea);
  OLED_AddImage(watch_imgBattery.img);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * [watch_BatteryLevelDraw description]
 * @param level [description]
 */

static void watch_BatteryLevelDraw(uint8_t level)
{
  OLED_SetDynamicArea(&watch_imgBattery.dynamicArea);

  if(level < 16)
  {
          watch_imgBattery.img = battery_0_bmp;
  }
  else if(level < 33)
  {
          watch_imgBattery.img = battery_1_bmp;
  }
  else if(level < 50)
  {
          watch_imgBattery.img = battery_2_bmp;
  }
  else if(level < 66)
  {
          watch_imgBattery.img = battery_3_bmp;
  }
  else if(level < 83)
  {
          watch_imgBattery.img = battery_4_bmp;
  }
  else
  {
          watch_imgBattery.img = battery_5_bmp;
  }

  OLED_DrawImage(watch_imgBattery.img);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * [watch_DigitWatchInit description]
 */

static void watch_DigitWatchInit(void)
{
	watch_labelDigitWatch.textProperties.background = watch_item.image,

	OLED_SetTextProperties(&watch_labelDigitWatch.textProperties);
	OLED_SetDynamicArea(&watch_labelDigitWatch.dynamicArea);

	OLED_AddText(watch_labelDigitWatch.caption);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * [watch_DigitWatchDraw description]
 */

static void watch_DigitWatchDraw(void)
{
	OLED_SetTextProperties(&watch_labelDigitWatch.textProperties);
	OLED_SetDynamicArea(&watch_labelDigitWatch.dynamicArea);

	OLED_DrawText(watch_labelDigitWatch.caption);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
